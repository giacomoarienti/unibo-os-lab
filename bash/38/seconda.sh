#!/bin/bash
OUT=""
while read una due tre; do
    OUT="${OUT}${due}"
done < $1
echo "${OUT}"