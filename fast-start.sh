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

title Pulling configs
configs/manage.sh pull

if cat /etc/os-release 2>/dev/null | grep -q Ubuntu; then
    title Update repository
    sudo apt-get update

    title Install basic packages
    sudo apt-get install tmux build-essential vim-gtk p7zip sshfs

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

        title Suggested external packages
        echo "Total Commander: https://www.ghisler.com/download.htm"

        title Install development packages
        choco install -y virtualbox
    fi
fi

title Done

