#!/bin/bash

for i in {302..304};
do
	if [ -e ../data/MSSLTest$i.dat ]
		then
		echo $i
    ./plotraw ../data/MSSLTest$i.dat $i
    mv ./nothings.root ../analysis/goodRuns_C2/nothings$i.root
fi
done
