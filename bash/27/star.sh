#!/bin/bash
while read RIGA; [[ $? -eq 0 ]]; do
    echo "$RIGA" | (read -d "\t" a b c d; echo "${d} ${c}") 
done