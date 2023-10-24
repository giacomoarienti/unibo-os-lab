#!/bin/bash
names=`ls`
for a in ${names}
do
    for b in ${names}
    do
        for c in ${names}
        do
            echo "$a $b $c"
        done
    done
done