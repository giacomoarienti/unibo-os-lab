#!/bin/bash
FILES=`ls`
LungNomiDirectory=0
NonDir=0
for FILE in $FILES; do
    if [[ -d $FILE ]]; then
        (( LungNomiDirectory=${LungNomiDirectory}+${#FILE} ))
    else
        (( NonDir=${NonDir}+1 ))
    fi
done
echo "${NonDir}"
echo "${LungNomiDirectory}"