#!/bin/bash

rm "InfluenceContaminations/results.txt"
# cp "contaminations/contaminations_nominales.h" "contaminations/contaminations.h"
# cp "contaminations/contaminations_measured_noBi.h" "contaminations/contaminations.h"
cp "contaminations/contaminations_measured_wBi.h" "contaminations/contaminations.h"

for ((j=0;j<500;j+=50))
 do
     rm "EventSelection/Cuts.h"
     # nominal
     # echo "double cut_proba_int = 0.01;double cut_vertex_y = 1e9;double cut_vertex_z = $j;" > "EventSelection/Cuts.h"
     # woBi
     # echo "double cut_proba_int = 0.05;double cut_vertex_y = 1e9;double cut_vertex_z = $j;" > "EventSelection/Cuts.h"
     # wBi
     echo "double cut_proba_int = 0.05;double cut_vertex_y = 1e9;double cut_vertex_z = $j;" > "EventSelection/Cuts.h"
     root -l -b -q efficiency.cc\(\"82Se\",1\)
done

mv "InfluenceContaminations/results.txt" "InfluenceContaminations/CutVertex/results_cuts.txt"
cp "EventSelection/Cuts_perso_nom_B.h" "EventSelection/Cuts.h"

cp "contaminations/contaminations_nominales.h" "contaminations/contaminations.h"
