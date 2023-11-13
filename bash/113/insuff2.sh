#!/bin/bash
while read nome cognome matricola voto; do
    if [[ voto -lt "18" ]]; then
        FOUND=1
        while read nome1 cognome1 matricola1 voto1; do
            if [[ $matricola1 -eq $matricola ]]; then
                FOUND=0
            fi
        done < "RisultatoProvaPratica1.txt"
        if (( $FOUND )); then
            echo "${matricola} ${nome} ${cognome} ${voto}"
        fi
    fi
done < "RisultatoProvaPratica2.txt" | sort -k 3