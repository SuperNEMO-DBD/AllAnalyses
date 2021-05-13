# Script to run decorrelate_sigmas.py file in a loop
#!/usr/bin/bash

rm true_sigmas.txt

for j in 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19
do
    for i in 0 1 2 3 4 5 6 7 8 9 10 11 12
    do
# for j in 0 1 2 3 4
# do
#     for i in 0
#     do
        echo 'decorrelate_sigmas for OM ['$j':'$i']'
        python3 decorrelate_sigmas.py simus $j $i
    done
done
