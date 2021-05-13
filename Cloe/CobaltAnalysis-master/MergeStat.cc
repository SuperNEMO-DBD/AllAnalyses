// Author Cloé Girard-Carillo girardcarillo@lal.in2p3.fr

#include <limits>
#include <string>
#include <iostream>

#include <TTree.h>
#include <TFile.h>
#include <TObject.h>
#include <TH1.h>
#include <TH2.h>

using namespace std;

void MergeStat(){

  c1 = new TCanvas("c1","A Simple Graph with error bars",200,10,700,500);
  const Int_t n = 3;
  Double_t x[n]  = {1,2,3};
  Double_t y[n]  = {0.8232,0.8046,0.8035};
  Double_t ex[n] = {0,0,0};
  Double_t ey[n] = {0,4e-4,0};
  gr = new TGraphErrors(n,x,y,ex,ey);
  gr->SetTitle("Studying merging runs");
  gr->GetXaxis()->SetTitle("#Run");
  gr->GetYaxis()->SetTitle("#sigma_{t} (ns)");
  gr->SetMarkerStyle(21);
  gr->Draw("AP");
  c1->SaveAs("MergeStat_sigma.pdf");

  const Int_t n1 = 3;
  Double_t y1[n1]  = {8.0078,7.8255,7.8168};
  Double_t ex1[n1] = {0,0,0};
  Double_t ey1[n1] = {0,2.98e-3,0};
  gr1 = new TGraphErrors(n1,x,y1,ex1,ey1);
  gr1->SetTitle("Studying merging runs");
  gr1->GetXaxis()->SetTitle("#Run");
  gr1->GetYaxis()->SetTitle("Relative error on sigma_{t} (%)");
  gr1->SetMarkerStyle(21);
  gr1->Draw("AP");
  c1->SaveAs("MergeStat_sigmaError.pdf");
}
