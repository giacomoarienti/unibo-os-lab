#!/bin/bash

RIGA="1 * 2"
while [[ -n "${RIGA}" ]]; do
	WORD="${RIGA%% *}"
	if [[ "${WORD}" -eq "${RIGA}" ]]; then
		$RIGA=""
	else
		LEN="${#WORD}"
		RIGA="${RIGA:$LEN}"
	fi
	echo "${WORD}"
done
