#!/bin/bash

cd "$(dirname "${BASH_SOURCE[0]}")"

echo
echo ">>> Update repository"
echo
git pull

echo
echo ">>> Installing scripts"
echo
if uname -a | grep -q Linux; then
    sudo scripts/install.sh
else
    scripts/install.sh
fi

echo
echo ">>> Pulling configs"
echo
configs/manage.sh pull

if uname -a | grep -q Ubuntu; then
    echo
    echo ">>> Installing basic packages"
    echo
    sudo apt-get install tmux build-essential vim-gtk

    echo
    echo ">>> Install development packages"
    echo
    sudo apt-get install qtcreator konqueror
fi

echo
echo ">>> Done"
echo

