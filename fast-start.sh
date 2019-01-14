#!/bin/bash

cd "$(dirname "${BASH_SOURCE[0]}")"
source "scripts/resources/tools.sh"

function title()
{
    echo
    echo ">>>" $@
    echo
}

title Update repository
git pull

title Installing scripts
if mux_is_linux || mux_is_osx; then
    sudo scripts/install.sh
else
    scripts/install.sh
fi

title Sync configs
configs/manage.sh sync

if cat /etc/os-release 2>/dev/null | grep -q Ubuntu; then
    title Update repository
    sudo apt-get update

    title Install basic packages
    sudo apt-get install tmux build-essential vim-gtk p7zip sshfs sshpass
    grep 18.04 /etc/os-release && sudo apt-get install \
        gnome-tweaks gnome-shell-extension-dash-to-panel

    title Install development packages
    sudo apt-get install qtcreator konqueror virtualbox
fi

if mux_is_windows; then
    title Install windows packages
    read -p "Continue? (y/n): " CONFIRM
    if [[ $CONFIRM == *y* ]]; then
        if ! which choco >/dev/null 2>&1; then
            title Install chocolatey
            powershell -NoProfile -InputFormat None -ExecutionPolicy Bypass -Command \
                "iex ((New-Object System.Net.WebClient).DownloadString('https://chocolatey.org/install.ps1'))"
            PATH+=":/c/ProgramData/chocolatey/bin"
        fi

        title Install basic packages
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

