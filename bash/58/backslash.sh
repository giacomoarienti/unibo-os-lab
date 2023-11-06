#!/bin/bash
while read RIGA; do
    while read -n1 char; do
        if [[ "$char" -eq "*" || "$char" -eq "?" || "$char" -eq "[" || "$char" -eq "]" ]]; then
            echo -ne "\\"
        fi
        echo -n "$char"
    done <<< "${RIGA}"
    echo
done