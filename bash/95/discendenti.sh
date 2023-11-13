#!/bin/bash
if [[ $1 -gt "0" ]]; then
    (( FIGLI=${1}-1 ))
    for (( i=0; i<$1; i++)); do
        ./$0 $FIGLI &
    done
    wait
fi
echo $1
exit 0