#!/bin/bash
ARGS=0
INDX=0
for (( NUM=1; $NUM<=$#; NUM=${NUM}+1 )); do
    TMP=${!NUM}
    (( TMP=${TMP}*${TMP} ))
    (( ARGS=${ARGS}+${TMP} ))
    (( INDX=${INDX}+${NUM} ))
done
(( TOT=${ARGS}-${INDX} ))
echo $TOT