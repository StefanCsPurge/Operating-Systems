#!/bin/bash

D=$1

sum=0
cnt=0

find $D -type f | (while read F; do
	if file "$F" | grep -q "ASCII text"; then
		c=`cat "$F"|wc -l`  # the number of lines from the current file
		sum=$(($sum+$c))
		cnt=$(($cnt+1))
	fi
done

echo "sum: $sum; cnt: $cnt; avg: $(($sum/$cnt))" )

