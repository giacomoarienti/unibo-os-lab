#!/bin/bash
while read RIGA; do
    PAROLA="${RIGA/ */}"
    if [[ ${#PAROLA} -gt "0" ]]; then
        echo "${PAROLA}" 1>&2
        echo "evviva"
    fi
done;
