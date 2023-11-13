#!/bin/bash
CONTINUE=1
COUNT=0
while (($CONTINUE)); do
    (( RND=${RANDOM}%10 ))
    if [[ $RND -eq "2" ]]; then
        CONTINUE=0
    fi
    (( COUNT=${COUNT}+1 ))
done
echo "${COUNT}"