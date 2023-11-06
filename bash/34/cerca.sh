#!/bin/bash
for file in $(find "/usr/include/" -type f -print); do
    head -n3 $file
done