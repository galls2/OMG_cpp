#!/bin/bash

cp ProofAttachment.cpp ~/Desktop

cd ~/Desktop

git clone https://github.com/mgudemann/iimc
cd iimc
apt install flex
apt install bison
apt install automake
apt-get install zlib1g-dev

apt-get install libboost-system-dev libboost-filesystem-dev libboost-chrono-dev libboost-program-options-dev libboost-test-dev libboost-thread-dev
apt-get install libboost-regex-dev
autoreconf -f -i
./configure
# changing the file src/mc/ProofAttachment.cpp as zyad saif
cp ~/Desktop/ProofAttachment.cpp src/mc/ProofAttachment.cpp
make


