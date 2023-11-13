#!/bin/bash

while read idProcesso descVerdetto; do
    while read idDenuncia idProcessoP; do
        if [[ $idProcesso -eq $idProcessoP ]]; then
            while read nome cognome idDenunciaD descReato; do
                if [[ $idDenuncia -eq $idDenunciaD ]]; then
                    echo "${nome} ${cognome}: ${descReato}, ${descVerdetto}"
                    break
                fi
            done < "denunce.txt";
            break
        fi
    done < "processi.txt"
done < "verdetti.txt"