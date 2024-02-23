#!/bin/bash
# REMOTE_GPU_ADDRESS=202.45.128.184 LD_PRELOAD=./RRTO/bin/RRTO-client.so  ./RRTO/tests/test_apps/RRTO.testapp
LD_LIBRARY_PATH=./RRTO/cpu REMOTE_GPU_ADDRESS=192.168.50.11 LD_PRELOAD='./RRTO/bin/RRTO-client.so ./RRTO/bin/libtirpc.so.3' python3 ./RRTO/tests/test_apps/pytorch_minimal.py
