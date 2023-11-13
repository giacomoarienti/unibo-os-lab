#!/bin/bash
for (( i=0; i<10; i++ )); do
    mkdir "1.${i}"
done

for (( i=0; i<10; i++ )); do
    (( NEW=9-${i} ))
    mv "1.${i}" "2.${NEW}"
done