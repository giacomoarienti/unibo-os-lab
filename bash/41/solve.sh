#!/bin/bash
ROWS=`grep -d skip '*' /usr/include/*`
echo "${ROWS}"
echo "${ROWS}" | wc -l