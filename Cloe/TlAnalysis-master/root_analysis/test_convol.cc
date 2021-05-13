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

using namespace std;

void test_convol(double sigma_tot)
{
  //construction of histogram to fit
  // TH1F *h_ExpGauss = new TH1F("h_ExpGauss","Exponential convoluted by gaussian",100,0.,5.) ;

  double min_f = -6 ;
  double max_f = 20 ;

  TF1 *f_ExpGauss = new TF1("f_ExpGauss","([0]/2)*exp(([0]/2)*(2*[2]+[0]*pow([1],2)-2*(x)))*erfc(([2]+[0]*pow([1],2)-(x))/(sqrt(2)*[1]))",min_f,max_f);

  TH1F *h_ExpGauss = new TH1F("h_ExpGauss","Exponential convoluted by gaussian",100,min_f,max_f) ;
  TH1F *h_Exp = new TH1F("h_Exp","Exponential",100,min_f,max_f) ;
  TH1F *h_Gauss = new TH1F("h_Gauss","Gaussian",100,min_f,max_f) ;
  double random_gaus = 0. ;
  double random_exp = 0. ;
  Double_t x = 0. ;

  // TF1 *fexp = new TF1("fexp","expo", -5, 15);
  // TF1 *fgaus = new TF1("fgaus","gaus", -5, 15);

  // for (int i = 0; i < fexp->GetNpar(); ++i) {
  //   cout << fexp->GetParName(i) << endl ;
  // }

  // for (int i = 0; i < fgaus->GetNpar(); ++i) {
  //   cout << fgaus->GetParName(i) << endl ;
  // }

  double tau = 0.294 ;
  double slope = 1./tau ;

  for (int i=0;i<1e7;i++){
    random_exp = gRandom->Exp(slope) ;//gives a alpha of -0.3 in the exp
    // random_gaus = gRandom->Gaus(0.,0.5) ;
    random_gaus = gRandom->Gaus(0.,sigma_tot) ;
    x = random_gaus + random_exp ;
    h_ExpGauss->Fill(x);//probability density function of the addition of two variables is the convolution of 2 dens. functions
    h_Exp->Fill(random_exp) ;
    h_Gauss->Fill(random_gaus) ;
  }


  ///Normalization of probability histograms
  Double_t scale_h = 1./h_ExpGauss->Integral();
  TH1F *h_ExpGauss_norm = (TH1F*) h_ExpGauss->Clone() ;
  h_ExpGauss_norm->Scale(scale_h);
  h_ExpGauss->Scale(scale_h);
  // Double_t scale_f = 1./f_ExpGauss->Integral();
  // f_ExpGauss->Scale(scale_f);

  f_ExpGauss->SetParameters(slope,sigma_tot,0);

  //fit
  TCanvas *c = new TCanvas("c","c",800,1000);
  f_ExpGauss->Draw() ;
  h_ExpGauss->Draw("HISTSAME") ;
  // f_ExpGauss->Draw("SAME") ;

  // int binmax = h_ExpGauss->GetMaximumBin(); double maxx = h_ExpGauss->GetXaxis()->GetBinCenter(binmax);
  // maximum_f = f_ExpGauss->GetX(f_ExpGauss->GetMaximum(),min_f,max_f) ;

  // cout << maxx << " " << maximum_f << endl ;

  // TLine *l0 = new TLine(maxx,0,maxx,gPad->GetUymax()) ;
  // TLine *l1 = new TLine(maximum_f,0,maximum_f,gPad->GetUymax()) ;
  // l1->SetLineColor(2 ) ;
  // l0->Draw() ;
  // l1->Draw() ;

  gStyle->SetOptFit(1) ;
}
