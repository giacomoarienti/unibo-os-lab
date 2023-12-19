#!/bin/bash
if [[ !($# -eq 2)]]; then
    echo "Numero argomenti errato" 1>&2
    exit 1
fi

minLarg=$1
maxAlt=$2

while read nome larg alt prof; do
    if [[ $larg -ge $minLarg && $alt -le $maxAlt ]]; then
        echo "${nome} ${larg} ${alt} ${prof}"
    fi
done < divani.txt;