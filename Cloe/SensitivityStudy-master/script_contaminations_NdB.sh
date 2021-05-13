#!/bin/bash

rm "InfluenceContaminations/results.txt"

# for ((j=0;j<51;j+=50))
# # for j in 0 10 54
# # for j in 0 10 290 # ((j=0;j<51;j+=10))
# do
#     rm "contaminations/contaminations.h"
#     echo "double A_208Tl = 2*31.5;double A_214Bi = 10*31.5;double A_222Rn = 0.15e-3*31.5e6;" > "contaminations/contaminations.h"
#     # echo "double A_208Tl = 2 *31.5;double A_214Bi = $j *31.5;double A_222Rn = 0.15e-3*31.5e6;" > "contaminations/contaminations.h"
#     root -l -b -q efficiency.cc\(\"150Nd\",1,\"zero\"\)
# done

# no bkg
rm "contaminations/contaminations.h"
echo "double A_208Tl = 0 ; double A_214Bi = 0 ; double A_222Rn = 0 ;" > "contaminations/contaminations.h"
root -l -b -q efficiency.cc\(\"150Nd\",1,\"zero\"\)

# nominal bkg
rm "contaminations/contaminations.h"
echo "double A_208Tl = 2*31.5 ; double A_214Bi = 10*31.5 ; double A_222Rn = 0.15e-3*31.5e6 ;" > "contaminations/contaminations.h"
root -l -b -q efficiency.cc\(\"150Nd\",1,\"zero\"\)

# measured bkg w/o Bi
rm "contaminations/contaminations.h"
echo "double A_208Tl = 54*31.5 ; double A_214Bi = 0 ; double A_222Rn = 0.15e-3*31.5e6 ;" > "contaminations/contaminations.h"
root -l -b -q efficiency.cc\(\"150Nd\",1,\"zero\"\)

# measured bkg w Bi
rm "contaminations/contaminations.h"
echo "double A_208Tl = 54*31.5 ; double A_214Bi = 290*31.5 ; double A_222Rn = 0.15e-3*31.5e6 ;" > "contaminations/contaminations.h"
root -l -b -q efficiency.cc\(\"150Nd\",1,\"zero\"\)

mv "InfluenceContaminations/results.txt" "InfluenceContaminations/results_Nd_with_B.txt"
cp "contaminations/contaminations_nominales.h" "contaminations/contaminations.h"
