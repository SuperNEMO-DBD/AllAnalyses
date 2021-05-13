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

void efficiency_delta_t(){

  int n=9 ;

  TTree *t_eff_0nu = new TTree("t_eff_0nu","efficiency") ;
  t_eff_0nu->ReadFile("efficiency_delta_t_0nubb.txt","sigma/F:eff_0nu/F") ;

  float eff_0nu, sigma ;
  t_eff_0nu->SetBranchAddress("sigma",&sigma) ;
  t_eff_0nu->SetBranchAddress("eff_0nu",&eff_0nu) ;


  double tab_eff_0nu[n] ;

  for (int k=0; k<t_eff_0nu->GetEntries(); k++){
    t_eff_0nu->GetEntry(k);

    tab_eff_0nu[k]=100-eff_0nu ;

  }

  TTree *t_eff_Tl = new TTree("t_eff_Tl","efficiency") ;
  t_eff_Tl->ReadFile("efficiency_delta_t_208Tl.txt","sigma/F:eff_Tl/F") ;

  float eff_Tl ;
  t_eff_Tl->SetBranchAddress("eff_Tl",&eff_Tl) ;


  double tab_eff_Tl[n] ;

  for (int k=0; k<t_eff_Tl->GetEntries(); k++){
    t_eff_Tl->GetEntry(k);

    tab_eff_Tl[k]=eff_Tl ;

  }

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
  c1->SetGridx() ;
  c1->SetGridy() ;

  config_graph(gr_eff,"","Efficiency ^{208}Tl (%)","Efficiency 0#nu#beta#beta (%)","AP",1,1,1) ;

  gr_eff->SetMarkerStyle(33) ;
  gr_eff->SetMarkerColor(kCyan+2) ;
  gr_eff->GetXaxis()->SetTitleSize(0.06) ;
  gr_eff->GetYaxis()->SetTitleSize(0.06) ;
  gr_eff->GetYaxis()->SetTitleOffset(0.9) ;
  gr_eff->GetXaxis()->SetTitleSize(0.06) ;
  gr_eff->GetXaxis()->SetTitleOffset(0.9) ;
  gr_eff->SetLineWidth(1) ;
  //gr_eff->SetLineColor(kCyan+2) ;

  c1->SaveAs("plots/efficiency_delta_t.pdf") ;

}
