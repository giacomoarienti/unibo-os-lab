#!/bin/bash
if (( $# != 3)); then
    echo "Numero argomenti sbagliato" 1>&2
    exit 1
fi
nome=$1
cognome=$2
matricola=$3
email=""
while read mat mail; do
    if [[ $mat -eq $matricola ]]; then
        email=$mail
    fi
done < email.txt

if [[ ${#email} -eq 0 ]]; then
    echo "email non trovata" 1>&2
    exit 1
fi

echo "la mail dello studente ${nome} ${cognome} ${matricola} e' ${email}"