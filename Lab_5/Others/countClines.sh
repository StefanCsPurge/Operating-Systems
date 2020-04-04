#!/bin/bash

S=0
for F in $1/*.c; do
	N=`grep "[^ \s]" $F | wc -l`
	echo $N
	S=`expr $S + $N`
done
echo $S
