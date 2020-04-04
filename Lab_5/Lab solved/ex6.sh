#!/bin/bash

while [ ! -z "$1" ]; do
	F=$1; shift
	W=$1; shift
	K=$1; shift
	if [ -z $F ] || [ -z $W ] || [ -z $K ]; then break; fi
	awk -v kk=$K -v w=$W '{
	n=0
	for(i=1;i<=NF;i++)
		if($i==w) n++
	if(n==kk) print $0
	}' "$F"
done
