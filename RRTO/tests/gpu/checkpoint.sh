#!/bin/bash

RRTO_PATH=$(pwd)/../..
RRTO_BIN=${RRTO_PATH}/gpu/RRTO

if [ -z $1 ]; then
    CUDA_APP=${RRTO_PATH}/bin/tests/kernel.testapp
elif [ -f $1 ]; then
    CUDA_APP=$1
elif [ -f ${RRTO_PATH}/bin/tests/$1 ]; then
    CUDA_APP=${RRTO_PATH}/bin/tests/$1
else
    echo "file $1 does not exist"
    exit 1
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

rm -rf ${RRTO_CKP_DIR}/*
rm -rf ${CRIU_CKP_DIR}/*
mkdir -p ${CRIU_CKP_DIR}
sudo killall ${CUDA_APP_NAME}

${RRTO_BIN} start ${CUDA_APP} &

sleep 1
server_pid=$(pgrep ${CUDA_APP_NAME})
echo "server pid:" $server_pid

LD_PRELOAD=${RRTO_CLIENT} ${CUDA_APP} &
client_pid=$!
echo "client pid:" $client_pid

sleep 5

sudo ${CRIU} dump -vvvvvv -t $client_pid --tcp-established --shell-job --images-dir ${CRIU_CKP_DIR} -W ${CRIU_CKP_DIR} -o dump.log

echo $client_pid > ${CRIU_CKP_DIR}/client_pid

${RRTO_BIN} checkpoint $server_pid

sleep 2

kill $server_pid
