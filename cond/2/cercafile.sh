#!/bin/bash
for name in `ls -d /usr/include/?[c-g]*`; do
    if [[ ${#name} -lt 18 || ${#name} -gt 23 ]]; then
        echo ${name}
    fi
done