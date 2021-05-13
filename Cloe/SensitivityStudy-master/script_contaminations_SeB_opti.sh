#!/bin/bash

rm "InfluenceContaminations/results.txt"

# no bkg
rm "contaminations/contaminations.h"
cp "EventSelection/Cuts_perso_nom_B.h" "EventSelection/Cuts.h"
echo "double A_208Tl = 0 ; double A_214Bi = 0 ; double A_222Rn = 0 ;" > "contaminations/contaminations.h"
root -l -b -q efficiency.cc\(\"82Se\",1\)

# nominal bkg
rm "contaminations/contaminations.h"
echo "double A_208Tl = 2*31.5 ; double A_214Bi = 10*31.5 ; double A_222Rn = 0.15e-3*31.5e6 ;" > "contaminations/contaminations.h"
root -l -b -q efficiency.cc\(\"82Se\",1\)

# measured bkg w/o Bi
rm "contaminations/contaminations.h"
cp "EventSelection/Cuts_perso_woBi_B.h" "EventSelection/Cuts.h"
echo "double A_208Tl = 54*31.5 ; double A_214Bi = 0 ; double A_222Rn = 0.15e-3*31.5e6 ;" > "contaminations/contaminations.h"
root -l -b -q efficiency.cc\(\"82Se\",1\)

# measured bkg w Bi
rm "contaminations/contaminations.h"
cp "EventSelection/Cuts_perso_wBi_B.h" "EventSelection/Cuts.h"
echo "double A_208Tl = 54*31.5 ; double A_214Bi = 290*31.5 ; double A_222Rn = 0.15e-3*31.5e6 ;" > "contaminations/contaminations.h"
root -l -b -q efficiency.cc\(\"82Se\",1\)

mv "InfluenceContaminations/results.txt" "InfluenceContaminations/results_Se_with_B.txt"

cp "contaminations/contaminations_nominales.h" "contaminations/contaminations.h"
cp "EventSelection/Cuts_perso_nom_B.h" "EventSelection/Cuts.h"
