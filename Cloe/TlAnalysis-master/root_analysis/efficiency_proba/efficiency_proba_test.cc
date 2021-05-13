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

void efficiency_proba_test(){

  int n=9 ;

  double tab_eff_0nu = {58.2,66.4,70.9,72.8,73.5,73.6,73.4,72.9,72.5} ;
  double tab_eff_Tl = {10.8,13.6,17.8,20.5,23.2,24.4,26,27.5,29} ;



  TGraph* gr_eff = new TGraph(n,tab_eff_Tl,tab_eff_0nu);

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

  config_graph(gr_eff,"","Efficiency ^{208}Tl (%)","Efficiency 0#nu#beta#beta (%)","AP",1,1,1) ;

  gr_eff->SetMarkerStyle(8) ;
  gr_eff->GetXaxis()->SetTitleSize(0.06) ;
  gr_eff->SetFillColorAlpha(kGray+2,0.35) ;
  gr_eff->GetYaxis()->SetTitleSize(0.06) ;
  gr_eff->GetYaxis()->SetTitleOffset(0.9) ;
  gr_eff->SetLineWidth(1) ;
  //gr_eff->SetLineColor(kCyan+2) ;

  c1->SaveAs("plots/efficiency_delta_t.pdf") ;

}
