#!/bin/bash
for (( i=0; i<10; i++ )); do
    mkdir "1.${i}"
done

for (( i=0; i<10; i++ )); do
    mv "1.${i}" "2.${i}"
done