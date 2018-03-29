# AllAnalyses
Temporary project for collating NEMO/SuperNEMO analysis scripts.

Index of projects:

* **SensitivityStudy**
    * *Owner:* Cheryl Patrick c.patrick@ucl.ac.uk
    * *Language:* C++
    * *Experiment:* SuperNEMO
    * *Uses:* Falaise, ROOT
    * *Summary:* Includes a Falaise custom module (SensitivityModule) to generate a ROOT ntuple with some basic event information (energies, internal/external probablities, number of tracks and calorimeter hits etc). Overlaps with ParticleIdentification module. Also includes various scripts that use these ntuples, primarily one that calculates a sensitivity (AnalyseSensitivity) and a couple to look at the efficiencies of reconstructing possible gammas (alpha,n) reactions in the CuBe feedthroughs.

* **NEMO-3**
    * *Owner:* James Mott jmott@bu.edu
    * *Language:* C++
    * *Experiment:* NEMO-3
    * *Uses:* Cadfael, ROOT
    * *Summary:* A lot of old modules from NEMO-3 analysis.  I don't think you'll be able to run many of them directly, but it might be useful to have the code for inspiration.

* **HalfCom_simu_analysis**
    * *Owner:* Guillaume Oliviéro goliviero@lpccaen.in2p3.fr
    * *Language:* C++
    * *Experiment:* SuperNEMO (Half Commissioning)
    * *Uses:* Cadfael, Bayeux, Falaise, ROOT
    * *Summary:* Sort and analyze data produced by flsimulate in the geometry Half Commissioning. For sorting, you have to give rules to the ID_selector to inhibit or not detectors (Optical Module and Geiger Cells). Then the sorted data can be analyzed and some ROOT histos are plot (programs is very preliminary, has to be improved). It embeds some scripts, specially for CCLyon.

* **ROOT-tools**
    * *Language:* C++
    * *Experiment:* SuperNEMO
    * *Uses:* ROOT
    * *Summary:* Any usefull ROOT macros proving generic tools for analysis.
