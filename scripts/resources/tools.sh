#
# MUX Bash helper functions.
#

# Requests confirmation with custom message.
function mux_confirm() {
    while true; do
        read -p "$@ (y/n): " answer
        [[ $answer == y* ]] && return 0
        [[ $answer == n* ]] && return 1
        echo "Wrong answer: $answer"
    done
}

# Prints fatal error to stderr and exits.
function mux_fail() {
    { set +x; } >/dev/null 2>&1
    echo ERROR: "$@" >&2
    exit 1
}

# Traces command with args and runs it.
function mux_trace_run() {
    echo -e "\033[0;35m>>>" "$@" "\033[0m" 1>&2
    "$@"
}

# Prints first existing file from arguments.
function mux_first_existing_file() {
    for file in $@; do
        if [ -f "$file" ]; then
            echo "$file"
            return 0
        fi
    done
}

# Silent run COMMAND [ARGS...].
function mux_silent_run() {
    if ! which "$1" 1>/dev/null 2>&1; then
        echo ERROR: Unable to find executable: "$1" >&2
        return 1
    fi

    if [ ! -z $USE_SUDO ]; then
        echo sudo "$@"
        sudo bash -c "$@ > /dev/null 2>&1 &"
    else
        echo "$@"
        "$@" >/dev/null 2>&1 &
    fi
}

function _mux_silent_run() {
    if [[ $COMP_CWORD == 1 ]]; then
        COMPREPLY=($(compgen -c ${COMP_WORDS[1]}))
    else
        COMPREPLY=($(echo "${COMP_WORDS[$COMP_CWORD]}*"))
    fi
}

# Setup BASH cross-terminal history with [limit].
function mux_bash_history() {
    export HISTCONTROL=ignoredups:erasedups
    export HISTSIZE=$1
    export HISTFILESIZE=$1
    shopt -s histappend
    if ! mux_is_osx; then
        # Work around for OS X Bug
        export PROMPT_COMMAND="history -a; $PROMPT_COMMAND"
    fi
}

# Run first avalible GUI tool from space separated [list] with [args...].
function mux_first_gui_tool() {
    local tools=$1
    shift
    for tool in $tools; do
        which $tool >/dev/null 2>&1 && \
            mux_silent_run $tool "$@" && \
            return 0
    done
    mux_fail "No tool found: $tools"
}

# Adds SSH keys if publics are avaliable.
function mux_use_ssh_keys() {
    eval $(ssh-agent -s)
    for key in "$@"; do
        if [ -f "$key".pub ]; then
            chmod 600 "$key"
            ssh-add "$key" || true
            echo SSH Key $key
        fi
    done
}

# Execute avaliable terminal multiplexer if [reqired].
function mux_tmux() {
    [ ! "$1" ] && return 0
    if [ "$TERM" != "screen" ]; then
        if which tmux 2>/dev/null; then
            SESSION=$(tmux list-sessions | grep -v '(attached)' | head -1 | cut -f1 -d':')
            exec tmux $([ "$SESSION" ] && echo attach -t $SESSION)
        elif which screen 2>/dev/null; then
            exec screen
        fi
    fi
}

function mux_is_linux() {
    uname | grep -q Linux
}

function mux_is_osx() {
    uname | grep -q Darwin
}

# Figures out if it is a bash on windows.
function mux_is_windows() {
    uname -s | grep -q "CYGWIN\|MINGW\|MSYS"
}

# Prints current process parents stack.
function mux_proc_stack() {
    local pid=$$
    while [ $pid != 1 ]; do
        pid=$(ps -h -o ppid -p $pid 2>/dev/null)
        name=$(ps -h -o comm -p $pid 2>/dev/null)
        printf "%7s  %s\n" "$pid" "$name"
    done
}

# Prints terminal if it is one.
function mux_is_terminal() {
    mux_proc_stack | grep "xterm\|terminal\|konsole"
}

# Prints windows [path] as UNIX (assuming drives are mounted to /).
function mux_windows_path() {
    local path="${1//\\/\/}"
    if [ $(cut -c2-2 <<< "$path") == ":" ]; then
        local drive=/$(cut -c1-1 <<< "$path")
        path=${drive,,}$(cut -c3- <<< "$path")
    fi
    echo "$path"
}

# Open develop environment for C++.
function mux_cpp() {
    if mux_is_windows; then
        mux_silent_run devenv ${@:-$(mux_first_existing_file *.sln build/*.sln)}
    else
        mux_silent_run qtcreator ${@:-$(mux_first_existing_file CMakeLists.txt *.pro)}
    fi
}

# Find for [name] in [path or .] with [type or any].
function mux_find() {
    find "${2:-.}" -name "$1" $([ "$3" ] && echo -type "$3")
}

# In [file] replaces [line_patern] with [line_patern] + [line], sets IS_CHANGED
function mux_replace_in_file() {
    local file="$1"
    local pattern="^$2"
    local replace="$2$3"
    if grep "$pattern" "$file"; then
        grep "^$replace$" "$file" >/dev/null && return
        grep -v "$pattern" "$file" > "$file"
    fi
    echo "$replace" >> "$file"
    MUX_IS_REPLACED="+$MUX_IS_REPLACED"
}

# Check local git repositories.
function mux_git_check() {
    for repository in "$@"; do
        cd "$repository"
        git fetch >/dev/null 2>&1 || true
        if ! git diff origin >/dev/null 2>&1; then
            echo Git $repository is out of origin >&2
        fi
        cd -
    done
}

# Upgrades $PATH with bin directories in [directory or ~/bins] with [exceptions or gcc].
function mux_local_PATH() {
    local dir=${1:-$HOME/bins}
    local ignore=${2:-gcc}
    if [ -d "$dir" ]; then
        local path=$(find -L "$dir" -name bin -type d | sort -r | grep -v "$ignore" | tr '\n' ':' )
        export PATH="$path$PATH"
    fi
    if which go > /dev/null 2>&1; then
        mkdir -p "$HOME/go"
        [ "$MUX_HOME" ] && export GOPATH="$HOME/go:$MUX_HOME/example/go"
    fi
}

# Change current directory to [diretory] on start if non-empty.
function mux_start_dir() {
    [ "$1" ] && [ "$PWD" == "$HOME" ] && cd "$1"
}

