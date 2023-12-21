#!/bin/bash
if [[ $# -ne 2 ]]; then
    echo "numero argomenti errato" 1>&2
    exit 1
fi
if [[ !(-e $1) ]]; then
    echo "argomento non file"
    exit 2
fi
( sleep 2; cat $1 | grep $2 | wc -l >> OUTPUT.txt ) &
exit 0
