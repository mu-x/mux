#!/bin/bash

set -e
cd "$(dirname "${BASH_SOURCE[0]}")"
source "scripts/resources/tools.sh"

mux_title Check GIT Repository
if mux_confirm "Check for GIT repository updates?"; then
    git pull --dry-run | grep objects && mux_fail Update required, use: git pull
    git submodule update --init --recursive
    echo Done
fi

mux_title Installing Scripts
if mux_is_linux || mux_is_osx; then
    sudo scripts/install.sh
else
    scripts/install.sh
fi

mux_title Sync Configs
configs/manage.sh sync

if cat /etc/os-release 2>/dev/null | grep -q Ubuntu; then
    mux_title Update Ubuntu Repository
        if mux_confirm "Check for ubuntu packages updates?"; then
        sudo apt-get update

        mux_title Install Ubuntu Packages
        sudo apt-get install \
            tmux build-essential git-gui vim-gtk p7zip sshfs sshpass silversearcher-ag
        grep 18.04 /etc/os-release && sudo apt-get install \
            gnome-tweaks gnome-shell-extension-dash-to-panel

        mux_title Install Development Packages
        mux_confirm "Install VSCode?" && sudo snap install code --classic
        sudo apt-get install meld
    fi
fi

if mux_is_windows; then
    mux_title Windows Tweaks
    if mux_confirm "Apply windows tweaks?"; then
        sed -i 's/set bell-style visible/set bell-style none/g' /etc/inputrc
    fi

    mux_title Install Windows Packages
    if mux_confirm "Install chocolatey with $PACKAGES?"; then
        if ! which choco >/dev/null 2>&1; then
            mux_title Install Chocolatey
            powershell -NoProfile -InputFormat None -ExecutionPolicy Bypass -Command \
                "iex ((New-Object System.Net.WebClient).DownloadString('https://chocolatey.org/install.ps1'))"
            PATH+=":/c/ProgramData/chocolatey/bin"
        fi

        function choco_install() {
            PACKAGES="$@"
            read -p "Install $PACKAGES? (y/n): " CONFIRM
            [[ $CONFIRM == *y* ]] && choco install -y $@
        }

        mux_title Install Basic Packages
        choco_install cmder 7zip notepadplusplus meld

        mux_title Install Development Packages
        choco_install virtualbox vscode
    fi

	mux_title What to do next?
	echo "See $PWD/NOTES.md"
fi

if mux_is_osx; then
    mux_title Update MacPorts
    sudo port install tmux p7zip
fi

mux_title Done

