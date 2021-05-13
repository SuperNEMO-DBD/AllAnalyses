#include <stdio.h>
#include <TMath.h>
#include <math.h>
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

using namespace std;

const double pi = 3.14159265358979323846 ;

void draw_chi2()
{

  TF1 *f_chi2_1 = new TF1("chi2_1","0.5*pow(x,-1/2)*exp(-x/2)",0,20); // (1/sqrt(2*pi))*
  TF1 *f_chi2_2 = new TF1("chi2_2","0.5*2*x*exp(-pow(x,2)/2)",-10,20);

  cout << f_chi2_1->Integral(0,20) << endl ;
  cout << f_chi2_2->Integral(0,20) << endl ;

  TCanvas *c1 = new TCanvas("c1", "c1",67,87,700,500);

  f_chi2_2->Draw() ;
  f_chi2_2->SetLineColor(1) ;
  f_chi2_1->Draw("SAME") ;

  f_chi2_2->SetTitle("") ;
  f_chi2_2->GetXaxis()->SetTitle("x") ;

  auto legend6 = new TLegend(0.673352,0.787686,0.949857,0.921444);
  // legend6->SetBorderSize(0) ;
  legend6->AddEntry(f_chi2_1,"chi2(x)","l");
  legend6->AddEntry(f_chi2_2,"chi2(u^{2})","l");
  legend6->Draw() ;



}
