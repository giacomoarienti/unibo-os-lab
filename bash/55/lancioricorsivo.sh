#!/bin/bash
PROCS=$1
if [[ $PROCS -gt "0" ]]; then
    ((PROCS=${PROCS}-1))
    ./$0 $PROCS &
    CPID=$!
    echo $CPID
    wait $CPID
fi