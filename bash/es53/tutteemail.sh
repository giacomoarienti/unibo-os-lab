#!/bin/bash
while read nome cognome matricola campo; do
    ./cercaemail.sh $nome $cognome $matricola
done < matricola.txt