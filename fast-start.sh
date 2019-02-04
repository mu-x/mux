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
git pull --dry-run | grep objects || mux_fail "Update required, use: git pull"
git submodule update --init --recursive

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
    sudo apt-get install tmux build-essential vim-gtk p7zip sshfs sshpass
    grep 18.04 /etc/os-release && sudo apt-get install \
        gnome-tweaks gnome-shell-extension-dash-to-panel
fi

if mux_is_windows; then
    title Install Windows Packages
    read -p "Continue? (y/n): " CONFIRM
    if [[ $CONFIRM == *y* ]]; then
        if ! which choco >/dev/null 2>&1; then
            title Install Chocolatey
            powershell -NoProfile -InputFormat None -ExecutionPolicy Bypass -Command \
                "iex ((New-Object System.Net.WebClient).DownloadString('https://chocolatey.org/install.ps1'))"
            PATH+=":/c/ProgramData/chocolatey/bin"
        fi

        title Install Basic Packages
        choco install -y cmder 7zip notepadplusplus meld
    fi

	title What to do next?
	echo "See $PWD/NOTES.md"
fi

if mux_is_osx; then
    title Update MacPorts
    sudo port install tmux p7zip
fi

title Done

