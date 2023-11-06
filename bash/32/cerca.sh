#!/bin/bash
DIR=$1
STR=$2
if [[ ! -d $1 ]]; then
    echo "Not a valid directory"
    exit
fi
if [[ ${#2} -eq 0 ]]; then
    echo "Invalid search string"
    exit
fi
find "$1" -name "$2" -print 