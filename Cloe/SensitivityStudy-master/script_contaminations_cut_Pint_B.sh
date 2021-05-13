#!/bin/bash

rm "InfluenceContaminations/results.txt"
# cp "contaminations/contaminations_nominales.h" "contaminations/contaminations.h"
# cp "contaminations/contaminations_measured_noBi.h" "contaminations/contaminations.h"
cp "contaminations/contaminations_measured_wBi.h" "contaminations/contaminations.h"

for ((j=0;j<10;j+=1))
 do
     rm "EventSelection/Cuts.h"
     echo "double cut_proba_int = $j*0.01;double cut_vertex_y = 1e9;double cut_vertex_z = 1e9;" > "EventSelection/Cuts.h"
     root -l -b -q efficiency.cc\(\"82Se\",1\)
done

mv "InfluenceContaminations/results.txt" "InfluenceContaminations/CutPint/results_cuts.txt"
cp "EventSelection/Cuts_perso_aucun.h" "EventSelection/Cuts.h"

cp "contaminations/contaminations_nominales.h" "contaminations/contaminations.h"
