#!/bin/bash

D=`date +%Y%m`
T="${D}01000000"
cat last.fake -t $T | \
sed "s/ .*//" | \
sort | \
uniq -c | \
sort -n -r | \
while read L U; do \
	N=`grep "^$U:" passwd | cut -d: -f5`
	echo $L $N
done | \
less

