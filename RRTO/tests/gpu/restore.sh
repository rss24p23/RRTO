#!/bin/bash

RRTO_PATH=$(pwd)/../..
RRTO_BIN=${RRTO_PATH}/gpu/RRTO

if [ -f $1 ]; then
    CUDA_APP=$1
elif [ -f ${RRTO_PATH}/bin/tests/$1 ]; then
    CUDA_APP=${RRTO_PATH}/bin/tests/$1
else
    CUDA_APP=${RRTO_PATH}/bin/tests/kernel.testapp
fi
echo "using $CUDA_APP"

CUDA_APP_NAME="$(basename -- $CUDA_APP)"
RRTO_CLIENT=${RRTO_PATH}/cpu/RRTO-client.so
RRTO_SERVER=${RRTO_PATH}/cpu/RRTO-server.so
CRIU=/home/eiling/tmp/criu/criu/criu

export REMOTE_GPU_ADDRESS=localhost
export CUDA_VISIBLE_DEVICES=0

RRTO_CKP_DIR=/tmp/RRTO-ckp
CRIU_CKP_DIR=/tmp/criu-ckp

sudo killall ${CUDA_APP_NAME}
sudo killall patched_binary
rm -rf /tmp/RRTO-ckp/patched_binary

${RRTO_BIN} restore ${CUDA_APP} &

sleep 1
server_pid=$(pgrep patched_binary)
echo "server pid:" $server_pid

sleep 10

sudo ${CRIU} restore -vvvvvv --tcp-established --shell-job --images-dir ${CRIU_CKP_DIR} -W ${CRIU_CKP_DIR} --action-script ${RRTO_PATH}/criu-restore-hook.sh -o restore.log 

#sleep 5
#
#kill $server_pid
#
