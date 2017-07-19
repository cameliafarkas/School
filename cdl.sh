#!/bin/bash

dates () {

	sed -i "s/Jan/01/g" output4

		sed -i "s/Feb/02/g" output4

		sed -i "s/Mar/03/g" output4

		sed -i "s/Apr/04/g" output4

		sed -i "s/May/05/g" output4

		sed -i "s/Jun/06/g" output4

		sed -i "s/Jul/07/g" output4

		sed -i "s/Aug/08/g" output4

		sed -i "s/Sep/09/g" output4

		sed -i "s/Oct/10/g" output4

		sed -i "s/Nov/11/g" output4

		sed -i "s/Dec/12/g" output4

		sed -i "s:\([0-9][0-9]\+\)\/\([0-9]\+\)\/\([0-9]\+\):\3-2-1:g" output4

		sed -i "s/:/T/" output4

		data=$(cat output4)
}
gasit=0
if [ "$#" == 3 ]&&[ "$2" == "--interval" ]&&[ "$3" == 1 ]; then
	gasit=1
fi

if [ "$#" == 1 ]||[ "$gasit" == 1 ]; then

	rm -rf output2 output1 output3 output4

	while read -r line
	do
		
		aux1=$line;
		aux2=$line;
		aux3=$line;

		data=$(echo $aux1| cut -d " " -f4 | cut -d "[" -f2)

		endpoint=$(echo $aux2 | cut -d " " -f7 | cut -d "#" -f1 | cut -d "?" -f1)

		code=$(echo $aux3 | cut -d " " -f9)

		echo "$data" > output4

		dates

		data1=$(echo ${data%:*} )

		echo "$data1 $endpoint" >> output1

		echo "$data1 $endpoint $code" >> output2

	done < "$1"

	echo "$(cat output1 | sort -u)" > output1

	while read -r line
	do
		aux=$line
		aux1=$(echo $line | cut -d " " -f1)
		aux2=$(echo $aux | cut -d " " -f2)

		total=$(cat output2 | grep $aux1 | grep $aux2 | wc -l)

		necesare=$(cat output2 | grep $aux1 | grep $aux2 | cut -d " " -f3 | grep "^2" | wc -l)

		echo -n "$line " >> output3

		awk "BEGIN {printf \"%.2f\n\", 100*$necesare/$total}" >> output3
		
	done < "output1"

	cat output3

fi
