#!/bin/bash

cd "$(dirname "${BASH_SOURCE[0]}")"

echo
echo ">>> Update repository"
echo
git pull

echo
echo ">>> Installing scripts"
echo
sudo scripts/install.sh

echo
echo ">>> Pulling configs"
echo
configs/manage.sh pull

echo
echo ">>> Git Hub configuration"
echo
set -x
git config --global user.name "mu-x"
git config --global user.email "uskov.mikhail@gmail.com"
git config --global push.default simple
set +x

echo
echo ">>> Installing basic packages"
echo
sudo apt-get install tmux build-essential vim-gtk

echo
echo ">>> Install development packages"
echo
sudo apt-get install qtcreator konqueror

echo
echo ">>> Done"
echo

