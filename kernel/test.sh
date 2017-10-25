#!/bin/bash

pushd src
make clean
make
popd
./install_kernel.sh
./run_bochs.sh
