#!/bin/bash
exec {FD}< ./miofileNoNL.txt
while read -u ${FD} RIGA ; [[ $? -eq 0 || ${RIGA} != "" ]] ; do
    echo $RIGA
done
exec {FD}>&-