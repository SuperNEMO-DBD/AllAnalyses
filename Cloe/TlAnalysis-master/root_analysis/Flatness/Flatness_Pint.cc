#include <TH1F.h>
#include <TH2F.h>
#include <TGraph.h>
#include <TTree.h>
#include <string>
#include <cmath>
#include <iostream>
#include <sstream>
#include <fstream>
#include <TList.h>
#include <TFile.h>
#include <TRandom.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TGaxis.h>
#include <TStyle.h>
#include <TLegend.h>

#include "/home/girardcarillo/Workdir/SNPlot/RootDisplay.h"

using namespace std;

void Flatness_Pint(string filename){


  TTree *t_slope = new TTree("t_slope","interbal proba") ;

  t_slope->ReadFile(filename.c_str(),"sigma_L/F:slope/F:err_slope/F") ;

  float sigma_L, slope, err_slope ;
  t_slope->SetBranchAddress("sigma_L",&sigma_L) ;
  t_slope->SetBranchAddress("slope",&slope) ;
  t_slope->SetBranchAddress("err_slope",&err_slope) ;

  int n=19 ;
  // int n=3 ;

  double tab_sigma[n],tab_slope[n],tab_err_slope[n],tab_err_up[n],tab_err_down[n] ;

  for (int k=0; k<t_slope->GetEntries(); k++){
    t_slope->GetEntry(k);

    tab_err_up[k]=slope+abs(err_slope/100.) ;
    tab_err_down[k]=slope-abs(err_slope/100.) ;

    tab_sigma[k]=sigma_L ;
    tab_slope[k]=slope/100. ;
    tab_err_slope[k]=err_slope/100. ;

  }

  TGraphErrors* gr = new TGraphErrors(n,tab_sigma,tab_slope,0,tab_err_slope);
  TGraph* gr_err_up = new TGraph(n,tab_sigma,tab_err_up);
  TGraph* gr_err_down = new TGraph(n,tab_sigma,tab_err_down);

  TCanvas *c1 = new TCanvas("c1", "c1",67,57,700,500);
  gStyle->SetOptStat(0);
  c1->Range(-0.02174329,-110.4217,0.1149848,183.3826);
  c1->SetFillColor(0);
  c1->SetBorderMode(0);
  c1->SetBorderSize(2);
  c1->SetLeftMargin(0.1590258);
  c1->SetRightMargin(0.04011461);
  c1->SetTopMargin(0.02760085);
  c1->SetBottomMargin(0.1719745);
  c1->SetFrameBorderMode(0);
  c1->SetFrameBorderMode(0);

  config_graph(gr,"","#sigma_{l} (ns)","a_{F} (Arbitrary normalisation)","AC E0",1,1,1) ;

  gr->GetXaxis()->SetTitleSize(0.06) ;
  gr->SetFillColorAlpha(kGray+2,0.35) ;
  gr->GetYaxis()->SetTitleSize(0.06) ;
  gr->GetYaxis()->SetTitleOffset(0.9) ;
  gr->SetLineWidth(1) ;
  //gr->SetLineColor(kCyan+2) ;

  TLine *l0 = new TLine(gPad->GetUxmin(),0,0.0278328,0) ;
  TLine *l1 = new TLine(0.0278328,gPad->GetUymin(),0.0278328,0) ;

  TLine *l2 = new TLine(0.07,gPad->GetUymin(),0.07,tab_slope[12]) ;
  TLine *l3 = new TLine(gPad->GetUxmin(),tab_slope[12],0.07,tab_slope[12]) ;

  l0->SetLineStyle(2) ;
  l0->SetLineWidth(2) ;
  l0->SetLineColor(kMagenta+2) ;
  l1->SetLineStyle(2) ;
  l1->SetLineWidth(2) ;
  l1->SetLineColor(kMagenta+2) ;
  l2->SetLineStyle(2) ;
  l2->SetLineWidth(2) ;
  l2->SetLineColor(kCyan+2) ;
  l3->SetLineStyle(2) ;
  l3->SetLineWidth(2) ;
  l3->SetLineColor(kCyan+2) ;

  l1->Draw() ;
  l0->Draw() ;
  l2->Draw() ;
  l3->Draw() ;

  c1->SaveAs("plots/flatness.pdf") ;

  // // // fitting graphs

  // TMultiGraph *mg = new TMultiGraph();
  // // mg->Add(gr_err_up,"cp");
  // // mg->Add(gr,"lp E3");
  // mg->Add(gr_err_down,"cp");
  // mg->Draw("a");

  // TF1 *f1 = new TF1("f1", "pol2");
  // mg->Fit("f1","R") ;
  // mg->GetFunction("f1")->SetLineColor(2);

  // cout << f1->GetX(0.,0,1) << endl ;

}
