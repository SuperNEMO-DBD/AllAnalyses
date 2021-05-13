// Author Cloé Girard-Carillo girardcarillo@lal.in2p3.fr

#include <limits>
#include <string>
#include <iostream>

#include <TTree.h>
#include <TFile.h>
#include <TObject.h>
#include <TH1.h>
#include <TH2.h>

#include "/home/girardcarillo/Workdir/SNPlot/RootDisplay.h"

using namespace std;

void Subtract_bdf(const char* file_data_bdf,const char* file_bdf){

  TFile *theDataFile = new TFile(file_data_bdf,"READ");
  TH1F *henergy_spectrum_data_bdf = new TH1F ("energy_spectrum_data_bdf","", 150,0,4);
  henergy_spectrum_data_bdf = (TH1F*)theDataFile->Get("Total_energy_spectrum");

  TFile *theBdfFile = new TFile(file_bdf,"READ");
  TH1F *henergy_spectrum_bdf = new TH1F ("energy_spectrum_bdf","", 150,0,4);
  henergy_spectrum_bdf = (TH1F*)theBdfFile->Get("Total_energy_spectrum");

  // corrigé efficiency
  // henergy_spectrum_bdf->Scale(0.29) ; // 0.29 fr ;
  // RatioCanvas(henergy_spectrum_data_bdf, henergy_spectrum_bdf, "Data+Background", "Background x efficiency", "Energy (MeV)", "Data/Bkg", "plots/Eff_data-bdf.pdf") ;

  // Pas corrigé efficiency
  // henergy_spectrum_data_bdf->Add(henergy_spectrum_bdf,-1) ;
  // RatioCanvas(henergy_spectrum_data_bdf, henergy_spectrum_bdf, "Data+Background", "Background", "Energy (MeV)", "Data/Bkg", "plots/Eff_data-bdf.pdf") ;
  // Comparison run 166 / run 167
  // henergy_spectrum_bdf->Scale(1.125) ;
  // RatioCanvas(henergy_spectrum_data_bdf, henergy_spectrum_bdf, "run 166", "run 167", "Energy (MeV)", "run166/run167", "plots/Eff_run166-run167.pdf") ;

  RatioCanvas(henergy_spectrum_data_bdf, henergy_spectrum_bdf, "[0:6] data", "others", "Energy (MeV)", "Data/Bkg", "plots/Eff_data-bdf.pdf") ;

}
