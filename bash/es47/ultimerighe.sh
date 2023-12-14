#!/bin/bash
# check arguments number
if [[ !($# -eq 1) ]]; then
    echo "numero argomenti errato" 1>&2
    exit 1
fi 
# check file exists
path=$1
if [[ !(-e $path) ]]; then
    echo "argomento non file" 1>&2
    exit 2
fi
# if file OUTPUT.txt not exists, create it
if [[ !(-e OUTPUT.txt)]]; then
    touch OUTPUT.txt
fi
# eseguo script
( sleep 2; tail -n 3 $path >> ./OUTPUT.txt ) &
exit 0