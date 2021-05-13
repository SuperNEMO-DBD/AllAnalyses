#include <stdio.h>
#include <TMath.h>
#include <TCanvas.h>
#include <iostream>
#include <TROOT.h>
#include <TChain.h>
#include <TObject.h>
#include <TRandom.h>
#include <TFile.h>
#include <math.h>
#include <TF1Convolution.h>
#include <TF1.h>
#include <TH1F.h>
#include <TGraph.h>
#include <TStopwatch.h>

#include "/home/girardcarillo/Workdir/SNPlot/RootDisplay.h"

using namespace std;

void draw_expo_proba(int sigma)
{
  gStyle->SetOptStat(0) ;

  string file_data_0nu = Form("~/Workdir/Analyses/TlAnalysis/root_analysis/ExpoProba/expo_proba_0nubb_%i_ps.root",sigma) ;
  TFile *theDataFile_0nu = new TFile(file_data_0nu.c_str(),"READ") ;

  string file_data_Tl = Form("~/Workdir/Analyses/TlAnalysis/root_analysis/ExpoProba/expo_proba_208Tl_%i_ps.root",sigma) ;
  TFile *theDataFile_Tl = new TFile(file_data_Tl.c_str(),"READ") ;

  TH1F *hTl = (TH1F*)theDataFile_Tl->Get("integrated_probability");
  TH1F *h0nu = (TH1F*)theDataFile_0nu->Get("integrated_probability");

  TCanvas *c = new TCanvas("canvas","canvas");
  c->Range(-0.1896243,-1696.148,1.059034,11844.29);
  c->SetFillColor(0);
  c->SetBorderMode(0);
  c->SetBorderSize(2);
  c->SetLeftMargin(0.1518625);
  c->SetRightMargin(0.04727794);
  c->SetTopMargin(0.07430998);
  c->SetBottomMargin(0.1252654);
  c->SetFrameBorderMode(0);
  c->SetFrameBorderMode(0);

  c->SetLogy() ;

  double scale = h0nu->GetMaximum() ;

  // h0nu->Scale(1./scale) ;
  config_histo1D(h0nu,"HIST E","P_{exp}","# Counts (Arbitrary normalisation)",2,1,kAzure+5) ;
  h0nu->GetYaxis()->SetRangeUser(1,1e5) ;
  h0nu->SetTitle("") ;

  // hTl->Scale(1./scale) ;
  config_histo1D(hTl,"HIST E SAME","P_{exp}","# Counts (Arbitrary normalisation)",2,1,kOrange+2) ;


  auto leg = new TLegend(0.5071633,0.6921444,0.9441261,0.8832272);
  leg->SetBorderSize(0) ;
  leg->AddEntry(h0nu,"0#nu#beta#beta simulations","le");
  leg->AddEntry(hTl,"^{208}Tl simulations","le");
  leg->Draw() ;

  c->SaveAs(Form("plots/proba_expo_%i.pdf",sigma)) ;

  cout << (h0nu->GetBinContent(1)/h0nu->GetEntries())*100 << endl ;
  cout << (hTl->GetBinContent(1)/hTl->GetEntries())*100 << endl ;


}
