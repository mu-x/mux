#!/bin/bash

set -e
cd "$(dirname "${BASH_SOURCE[0]}")"
source "scripts/resources/tools.sh"

function title()
{
    echo
    echo ">>>" $@
    echo
}

title Check GIT Repository
git pull --dry-run | grep objects && mux_fail "Update required, use: git pull"
git submodule update --init --recursive
echo Done

title Installing Scripts
if mux_is_linux || mux_is_osx; then
    sudo scripts/install.sh
else
    scripts/install.sh
fi

title Sync Configs
configs/manage.sh sync

if cat /etc/os-release 2>/dev/null | grep -q Ubuntu; then
    title Update Ubuntu Repository
    sudo apt-get update

    title Install Ubuntu Packages
    sudo apt-get install tmux build-essential vim-gtk p7zip sshfs sshpass silversearcher-ag
    grep 18.04 /etc/os-release && sudo apt-get install \
        gnome-tweaks gnome-shell-extension-dash-to-panel

    title Install Development Packages
    mux_confirm "Install VSCode?" && sudo snap install vscode --classic
    sudo apt-get install meld
fi

if mux_is_windows; then
    title Install Windows Packages
    if mux_confirm "Install chocolatey with $PACKAGES?"; then
        if ! which choco >/dev/null 2>&1; then
            title Install Chocolatey
            powershell -NoProfile -InputFormat None -ExecutionPolicy Bypass -Command \
                "iex ((New-Object System.Net.WebClient).DownloadString('https://chocolatey.org/install.ps1'))"
            PATH+=":/c/ProgramData/chocolatey/bin"
        fi
        
        function choco_install() {
            PACKAGES="$@"
            read -p "Install $PACKAGES? (y/n): " CONFIRM
            [[ $CONFIRM == *y* ]] && choco install -y $@
        }

        title Install Basic Packages
        choco_install cmder 7zip notepadplusplus meld
        
        title Install Development Packages
        choco_install virtualbox vscode
    fi

	title What to do next?
	echo "See $PWD/NOTES.md"
fi

if mux_is_osx; then
    title Update MacPorts
    sudo port install tmux p7zip
fi

title Done

