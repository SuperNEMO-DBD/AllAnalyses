# AllAnalyses
Temporary project for collating NEMO/SuperNEMO analysis scripts.

Index of projects:

* **SensitivityStudy** 
    * *Owner:* Cheryl Patrick c.patrick@ucl.ac.uk
    * *Language:* C++
    * *Experiment:* SuperNEMO
    * *Uses:* Falaise, ROOT
    * *Summary:* Includes a Falaise custom module (SensitivityModule) to generate a ROOT ntuple with some basic event information (energies, internal/external probablities, number of tracks and calorimeter hits etc). Overlaps with ParticleIdentification module. Also includes various scripts that use these ntuples, primarily one that calculates a sensitivity (AnalyseSensitivity) and a couple to look at the efficiencies of reconstructing possible gammas (alpha,n) reactions in the CuBe feedthroughs.
