#include "TH1Flog.hh"
#include "TH2Flog.hh"

#include "TCanvas.h"
#include "TF1.h"
#include "TPad.h"
#include "TRandom3.h"
#include "TStyle.h"

void TH1log_demo()
{
  TH1F *classical_histo   = new TH1F ("c_histo_1d", "classical histo 1d;x;y",   200, 0.1, 10.);
  TH1F *logarithmic_histo = TH1Flog  ("l_histo_1d", "logarithmic histo 1d;x;y", 200, 0.1, 10.);

  new TF1 ("fill_func", "TMath::Power(x, -3.141593)", 0, 10);
  classical_histo->FillRandom("fill_func", 1E5);
  logarithmic_histo->FillRandom("fill_func", 1E5);

  TCanvas *C = new TCanvas ("C_1D", "1D", 5, 5, 1000, 500);

  C->Divide(2);

  TPad *pad_left = (TPad*)(C->cd(1));
  pad_left->SetLogx(); pad_left->SetLogy();
  classical_histo->Draw("e");

  TPad *pad_right = (TPad*)(C->cd(2));
  pad_right->SetLogx(); pad_right->SetLogy();
  logarithmic_histo->Draw("e");
}


void TH2log_demo()
{
  TH2F *classical_histo   = new TH2F  ("c_histo_2d", "classical histo 2d;x;y", 200, 0.1, 10., 200, 0.1, 10.);
  TH2F *logarithmic_histo = TH2Flogxy ("l_histo_2d", "logarithmic histo 2d;x;y", 200, 0.1, 10., 200, 0.1, 10.);
  
  TRandom3 rdm3;

  for (int entry=0; entry<1E5; ++entry) {

    float value_true = rdm3.Landau (0.5, 0.05);
    float value_x = rdm3.Gaus(value_true, TMath::Sqrt(value_true)/10.0);
    float value_y = rdm3.Gaus(value_true, TMath::Sqrt(value_true)/10.0);
  
    classical_histo->Fill(value_x, value_y);
    logarithmic_histo->Fill(value_x, value_y);

  }

  
  TCanvas *C = new TCanvas ("C_2D",  "2D", 55, 55, 1000, 500);
  C->Divide(2);

  TPad *pad_left = (TPad*)(C->cd(1));
  pad_left->SetLogx(); pad_left->SetLogy(); pad_left->SetLogz();
  classical_histo->Draw("colz");

  TPad *pad_right = (TPad*)(C->cd(2));
  pad_right->SetLogx(); pad_right->SetLogy(); pad_right->SetLogz();
  logarithmic_histo->Draw("colz");
}


void THlog_demo()
{
  gStyle->SetOptStat(0);
  gStyle->SetPalette(55);
  TH1::SetDefaultSumw2(true);
    
  TH1log_demo();
  TH2log_demo();
}
