// Author Cloé Girard-Carillo girardcarillo@lal.in2p3.fr

#include <limits>
#include <string>
#include <iostream>
#include <fstream>

#include <TTree.h>
#include <TFile.h>
#include <TObject.h>
#include <TH1.h>
#include <TH2.h>

#include "/home/girardcarillo/Workdir/SNPlot/RootDisplay.h"
#include "/home/girardcarillo/Workdir/SNPlot/EventTree.h"

void GainExtract(string DataFilename,string GainAmplFilename){

  TFile *theGainAmplFile = new TFile(GainAmplFilename.c_str());

  if ( theGainAmplFile->IsOpen() ) {
    cout << "File " << GainAmplFilename << " opened sucessfully" << endl ;
  }


  TH2D *hGainAmpl = (TH2D*)theGainAmplFile->Get("gain_vs_position_exp");

  TH2D *h2charge = new TH2D ("h2charge","", 290, 0, 289, 1000, 0,30) ;
  TH2D *h2amplitude = new TH2D ("h2amplitude","", 290, 0, 289, 1000, 80,1000) ;
  TH2D *h2CalibEnergyAmpl = new TH2D ("calib_charge","", 290, 0, 289, 500, 0, 10) ;

  TH1F *hamplitudeSpectrum1 = new TH1F("amplitude1","",100, 0, 4) ;
  TH1F *hamplitudeSpectrum2 = new TH1F("amplitude2","",100, 0, 4) ;

  //data file
  TFile *DataFile = new TFile(DataFilename.c_str(),"READ") ;
  TTree *theTree = nullptr ;
  DataFile->GetObject("T",theTree) ;

  if (DataFile->IsOpen()) {
    cout << "File " << DataFilename << " opened sucessfully" << endl ;
  }

  theTree = (TTree*)DataFile->Get("DataCut") ;

  theTree->SetBranchAddress("calo_energy",&calo_energy) ;
  theTree->SetBranchAddress("calo_row",&calo_row) ;
  theTree->SetBranchAddress("calo_column",&calo_column) ;
  theTree->SetBranchAddress("calo_peak",&calo_peak) ;

  for (Long64_t i=0 ;i<theTree->GetEntries() ;i++) {
    theTree->GetEntry(i) ;
    for (int j = 0; j < calo_energy->size(); ++j) {
      int calo_number = hGainAmpl->GetBin(calo_column->at(j),calo_row->at(j)) ;
      double calo_calib_energy_ampl =  calo_peak->at(j)*3.055/hGainAmpl->GetBinContent(calo_column->at(j)+1,calo_row->at(j)+1) ;

      h2charge->Fill(calo_number,calo_energy->at(j)) ;
      h2amplitude->Fill(calo_number,-calo_peak->at(j)) ;
      h2CalibEnergyAmpl->Fill(calo_number,-calo_calib_energy_ampl) ;
      if (calo_column->at(j) == 8 && calo_row->at(j) == 6) {
        hamplitudeSpectrum1->Fill(-calo_calib_energy_ampl) ;
      }
      if (calo_column->at(j) == 7 && calo_row->at(j) == 6) {
        hamplitudeSpectrum2->Fill(-calo_calib_energy_ampl) ;
      }
      // if (calo_number == 140) {
      //   if (calo_energy->at(j)) {

      //     cout << calo_column->at(j) << " " << calo_row->at(j) << endl ;
      //   }
      // }
    }


    // if (i > 10) {
    //   break ;
    // }

  }

  //Drawing
  gStyle->SetOptStat(0) ;

  TCanvas *c1 = new TCanvas("c1","c1",10,10,2000,1000) ;
  c1->Divide(1,2) ;

  c1->cd(1) ;
  config_histo2D(h2amplitude, "Amplitude (before calib)", "OM number","amplitude (mV)","COLZ") ;
  h2amplitude->SetMinimum(0);
  h2amplitude->SetMaximum(300);

  c1->cd(2) ;
  config_histo2D(h2CalibEnergyAmpl, "Calibrated energy (amplitude)", "OM number","Energy","COLZ") ;
  h2CalibEnergyAmpl->SetMinimum(0);
  h2CalibEnergyAmpl->SetMaximum(300);

  c1->SaveAs("calib_energy.pdf") ;

  // config_histo2D(h2CalibEnergyAmpl, "Calibrated energy (amplitude)", "OM number","Energy","COLZ") ;
  // h2CalibEnergyAmpl->SetMinimum(0);
  // h2CalibEnergyAmpl->SetMaximum(300);




  // TCanvas *c2 = new TCanvas("c2","c2",10,10,2000,1000) ;
  // config_histo2D(hGainAmpl, "Gain for each OM (from amplitude)", "column","row","COLZ") ;
  // c2->SaveAs("gain_ch_ampl.pdf") ;


  // TCanvas *c2 = new TCanvas("c2","c2",10,10,2000,1000) ;
  // hamplitudeSpectrum2->Draw() ;
  // hamplitudeSpectrum1->Draw("SAME") ;
  // hamplitudeSpectrum2->GetXaxis()->SetTitle("Energy (MeV)") ;
  // hamplitudeSpectrum2->SetLineColor(2) ;

}
