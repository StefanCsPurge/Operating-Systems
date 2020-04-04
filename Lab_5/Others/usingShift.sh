#!/bin/bash

echo Command:$0
echo First four args:$1 $2 $3 $4
echo All args:$@
echo Arg count $#

#for A in $@;
#do
#echo Arg A:$A
#done

echo

for A;
do
echo Arg B:$A
done

shift
echo Some args:$1 $2 $3 $4
echo All args:$@
echo Arg count:$#

shift 3
echo Some args:$1 $2 $3 $4
echo All args:$@
echo Arg count:$#
