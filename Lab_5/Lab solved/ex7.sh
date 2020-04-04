#!/bin/bash

for A in $@; do
	if [ -f $A ]; then
		cat $A| awk 'BEGIN {n}
		{ if (!f[$0]) lines[n++]=$0
		  f[$0]++ } 
	  	END{max=0
      		for(i=0;i<n;i++) if(f[lines[i]]>max){max=f[lines[i]]; mLine=lines[i]}
		print max " " mLine}'
	fi
done|sort -k1nr|cut -f2- -d' '	
