#!/bin/bash
I=0
while read RIGA; do
    (( ISEVEN=$I%2 ))
    if [ $ISEVEN -eq "0" ]; then
        echo "${RIGA}"
    fi
    ((I=$I+1))  
done