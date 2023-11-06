#!/bin/bash
PATHS=$PATH
while [[ ${#PATHS} -gt "0" ]]; do
    CURRPATH="${PATHS%%:*}"
    echo $CURRPATH
    PATHS="${PATHS:${#CURRPATH}+1}"
done