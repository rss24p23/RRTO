#!/bin/bash
service rpcbind start
LD_PRELOAD='./RRTO/bin/libtirpc.so.3' ./RRTO/bin/RRTO-rpc-server
