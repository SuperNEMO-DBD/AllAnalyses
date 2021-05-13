#job to execute RootAnalyser.cc @ CC Lyon
#!/bin/bash

echo "Bash version ${BASH_VERSION}..."
for i in 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19
do
 for j in 0 1 2 3 4 5 6 7 8 9 10 11 12
 do
  cd ~/Workdir/Analyses/CobaltAnalysis
  root -b -l -q RootAnalyzer.cc\(\"Cut_root_files/data/60Co_runs/Cut_2e_runs_fr_centr_Calib.root\",$i,$j,0.7,0.7,0,0\)
 done
done

