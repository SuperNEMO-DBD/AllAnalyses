#!/bin/bash

rm "InfluenceContaminations/results.txt"


 for ((j=0;j<300;j+=58))
 do
     rm "contaminations/contaminations.h"
     echo "double A_208Tl = 2*31.5;double A_214Bi = $j *31.5;double A_222Rn = 0.15e-3*31.5e6;" > "contaminations/contaminations.h"
     echo $j
     # echo "double A_208Tl = 2 *31.5;double A_214Bi = $j *31.5;double A_222Rn = 0.15e-3*31.5e6;" > "contaminations/contaminations.h"
     root -l -b -q efficiency.cc\(\"82Se\",1\)
 done

mv "InfluenceContaminations/results.txt" "InfluenceContaminations/results_Bi.txt"
cp "contaminations/contaminations_nominales.h" "contaminations/contaminations.h"
