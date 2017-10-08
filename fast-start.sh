#!/bin/bash

cd "$(dirname "${BASH_SOURCE[0]}")"

function title()
{
    echo
    echo ">>>" $@
    echo
}

title Update repository
git pull

title Installing scripts
if uname -a | grep -q Linux; then
    sudo scripts/install.sh
else
    scripts/install.sh
fi

title Pulling configs
configs/manage.sh pull

if cat /etc/os-release 2>/dev/null | grep -q Ubuntu; then
    title Installing basic packages
    sudo apt-get install tmux build-essential vim-gtk p7zip

    title Install development packages
    sudo apt-get install qtcreator konqueror virtualbox
fi

if uname -a | grep -q MINGW; then
    title Install windows packages
    read -p "Continue? (y/n): " CONFIRM
    if [[ $CONFIRM == *y* ]]; then
        if ! which choco >/dev/null 2>&1; then
            title Install chocolatey
            powershell \
                -NoProfile -InputFormat None -ExecutionPolicy Bypass -Command \
                "iex ((New-Object System.Net.WebClient).DownloadString('https://chocolatey.org/install.ps1'))"
            SET "PATH=%PATH%;%ALLUSERSPROFILE%\chocolatey\bin"
        fi

        title Install basic packages
        choco install cmder 7zip totalcmd virtualbox
    fi
fi

title Done

