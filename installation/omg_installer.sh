#!/bin/sh

cp boost_1_68_0.tar.bz2 ~/Desktop
cp cudd-3.0.0 -r ~/Desktop
cd ~/Desktop

echo Initiating OMG installer.
echo This should be run wish SUDO

echo Installing Basic Programs

apt-get update
apt install git -y
apt install cmake -y
apt install graphviz -y

echo Now Installing CUDD
#sudo apt install autoconf
#./autoreconf
#sudo ./configure --enable-*
#sudo make
#sudo make install
#  sudo cp OMG_cpp/cudd-3.0.0/cplusplus/cuddObj.hh OMG_cpp/cudd-3.0.0/cudd/cudd.h /usr/local/include/


echo Installing boost 1.68
tar -xvf boost_1_68_0.tar.bz2
cd boost_1_68_0
./bootstrap.sh
./b2 install

cd ~/Desktop

echo Insalling z3

git clone https://github.com/Z3Prover/z3
cd z3
python scripts/mk_make.py
cd build
make
make install

cd ~/Desktop

cp OMG_cpp/run_config.omg .
cp OMG_cpp/prep_omg.sh .

echo Finished installation
echo In order to run OMG, run the script prep_omg.sh
echo You may change the configuration file run_config.omg

echo In order to run IIMC, please go to installation/iimc and run WITH SUDO

