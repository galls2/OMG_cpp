#!/bin/sh

cp boost_1_68_0.tar.bz2 ~/Desktop
cd ~/Desktop

echo Initiating OMG installer.
echo This should be run wish SUDO

echo Installing Basic Programs

apt-get update
apt install git -y
apt install cmake -y

echo Installing boost 1.68
cd boost_1_68_0
./bootstrap.sh
./b2 install

cp ~/Desktop

echo Insalling z3

git clone https://github.com/Z3Prover/z3
cd z3
python scripts/mk_make.py
cd build
make
make install

echo Finished installation
echo In order to run OMG, run the script prep_omg.sh
