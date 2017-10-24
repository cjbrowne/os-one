#!/bin/bash

pushd src
make clean
make
popd
./update_image.sh
./run_bochs.sh
