#!/bin/bash
# Script that minifies a css (all that it does is trims whitespace and \n\r duh!)
if [[ -n $1 ]]; then
	f=$(cat $1 | tr -d "\n\r\t ")
	if [[ -n $2 ]]; then
		echo $f > $2
	else
		echo "NOT DESTINATION FILE GIVEN :)"
	fi
else
	echo "NO FILE GIVEN"
fi
