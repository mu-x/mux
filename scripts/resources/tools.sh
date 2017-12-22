#
# MUX Bash helper functions.
#

# Prints first existing file from arguments
function mux_first_existing_file() {
    for file in $@; do
        if [ -f "$file" ]; then
            echo "$file"
            return 0
        fi
    done
}

# Silent run COMMAND [ARGS...]
function mux_silent_run() {
    echo $@
    $@ >/dev/null 2>&1 &
}
# Setup BASH cross-terminal history with [limit]
function mux_bash_history() {
    export HISTCONTROL=ignoredups:erasedups
    export HISTSIZE=$1
    export HISTFILESIZE=$1
    shopt -s histappend
    export PROMPT_COMMAND="history -a; history -c; history -r; $PROMPT_COMMAND"
}

# Run first avalible GUI tool from space separated [list] with [args...]
function mux_first_gui_tool() {
    tools=$1
    shift
    for tool in $tools; do
        which $tool >/dev/null 2>&1 && \
            mux_silent_run $tool "$@" && \
            return 0
    done
}

# Adds SSH keys if publics are avaliable
function mux_use_ssh_keys() {
    for key in "$@"; do
        if [ -f "$key".pub ]; then
            eval $(ssh-agent -s)
            ssh-add "$key"
        fi
    done
}

# Execute avaliable terminal multiplexer
function mux_terminal_multiplexer() {
    if [ "$TERM" != "screen" ]; then
        if which tmux 2>/dev/null; then
            SESSION=$(tmux list-sessions | grep -v '(attached)' | head -1 | cut -f1 -d':')
            exec tmux $([ "$SESSION" ] && echo attach -t $SESSION)
        elif which screen 2>/dev/null; then
            exec screen
        fi
    fi
}

# Prints windows [path] as UNIX (assuming drives are mounted to /)
function mux_windows_path() {
    local path="${1//\\/\/}"
    if [ $(cut -c2-2 <<< "$path") == ":" ]; then
        local drive=/$(cut -c1-1 <<< "$path")
        path=${drive,,}$(cut -c3- <<< "$path")
    fi
    echo "$path"
}

