#!/bin/bash
file="$1"
log="log.txt"
none=""
for file_name in $( ls );
	do
		filediff=$(diff $file $file_name);

		if [ "$filediff" == "" ];then
			echo $file "and" $file_name "are the same"
		else
			echo $filediff >> log.txt
		fi
	done
