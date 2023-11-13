#!/bin/bash
NEWESTFILE=""
for file in `find /usr/include/linux -mindepth 2 -name "*.h"`; do
    if [[ ${#NEWESTFILE} -eq "0" ]]; then
        NEWESTFILE=$file
    fi
    if [[ $file -nt $NEWESTFILE ]]; then
        NEWESTFILE=$file
    fi
done
echo "${NEWESTFILE}"