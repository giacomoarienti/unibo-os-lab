#!/bin/bash
OUT=""
while read -n 1 char; do
    OUT="${char}${OUT}"
done <<< $1
echo "${OUT}"