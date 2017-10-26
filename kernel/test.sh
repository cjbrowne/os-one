#!/bin/bash

make -C src clean
make -C src
./prepare_iso.sh
./run_bochs.sh
