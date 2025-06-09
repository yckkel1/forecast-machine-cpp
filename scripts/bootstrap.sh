#!/bin/bash

date

set -e 

if ! xcode-select -p > /dev/null 2>&1; then
	echo "Installing Xcode"
	xcode-select --install
else 
	echo "Skip - Xcode already installed"
fi

if ! command -v cmake > /dev/null; then
	echo "Installing Cmake"
	brew install cmake
else
	echo "Skip - Cmake already installed"
fi

brew install gnuplot
brew install mysql
brew install mysql-connector-c++
brew services start mysql

date 
