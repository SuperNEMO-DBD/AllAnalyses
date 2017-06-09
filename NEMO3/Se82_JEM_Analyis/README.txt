Code used by James Mott to perform a NEMO-3 analysis of Se82 data.

FrameworkModules contains all the modules that I used to run the different measurement channels.
This is for performing all the cuts on the data and producting trees of events for fitting.
This needs the NEMO-3 framework, but can be used for inspiration.

FittingCode is my personal fitting Macros (which are messy and cumbersome - please don't judge!).
The histgrams for each channel are made from the output trees and are placed in the Histograms folder.
Then the FitHistograms code fits the histograms with given activities.
This produces text files which can be read from the DrawHistogramsRatio folder.

LimitSettingCode contains limit setting code.  This uses collie v4_13.
