#!/bin/bash
ultimaMulta=0
numMulte=0
while read nome cognome importo data; do
    if [[ $ultimaMulta -eq 0 ]]; then
        ultimaMulta=$importo
    fi
    if [[ $ultimaMulta -eq $importo ]]; then
        ((numMulte=$numMulte+1))
    else
        echo "${ultimaMulta} ${numMulte}"
        numMulte=1
        ultimaMulta=$importo
    fi
done
echo "${ultimaMulta} ${numMulte}"