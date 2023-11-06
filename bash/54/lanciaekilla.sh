#!/bin/bash
PIDS=$(./lanciaeprendipid.sh)
for pid in $PIDS; do
    kill -9 $pid
done