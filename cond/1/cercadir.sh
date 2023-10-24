#!/bin/bash
for name in /usr/include/* ; do
    if [[ -d ${name} && -r ${name} && ${name} -nt /usr/include/stdio.h ]] ;
    then
        echo ${name}
    fi
done