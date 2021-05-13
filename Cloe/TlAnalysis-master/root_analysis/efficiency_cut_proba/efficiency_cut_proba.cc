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

std::ofstream file_eff;

void efficiency_cut_proba(string sigma){

  int n=20 ;

  TTree *t_eff_0nu = new TTree("t_eff_0nu","efficiency") ;
  t_eff_0nu->ReadFile(Form("efficiency_cut_proba_0nubb_%s.txt",sigma.c_str()),"level_cut/F:eff_0nu/F") ;

  float eff_0nu, level_cut ;
  t_eff_0nu->SetBranchAddress("level_cut",&level_cut) ;
  t_eff_0nu->SetBranchAddress("eff_0nu",&eff_0nu) ;

  double tab_eff_0nu[n] ;
  double tab_eff_0nu_first ;

  for (int k=0; k<t_eff_0nu->GetEntries(); k++){
    t_eff_0nu->GetEntry(k);

    // tab_eff_0nu[k]=100-eff_0nu ;

    if (k==0) {
      tab_eff_0nu_first=100-eff_0nu ;
    }
    else {
      tab_eff_0nu[k-1]=100-eff_0nu ;
    }

  }

  TTree *t_eff_Tl = new TTree("t_eff_Tl","efficiency") ;
  t_eff_Tl->ReadFile(Form("efficiency_cut_proba_208Tl_%s.txt",sigma.c_str()),"level_cut/F:eff_Tl/F") ;

  float eff_Tl ;
  t_eff_Tl->SetBranchAddress("eff_Tl",&eff_Tl) ;


  double tab_eff_Tl[n] ;
  double tab_eff_Tl_first ;

  for (int k=0; k<t_eff_Tl->GetEntries(); k++){
    t_eff_Tl->GetEntry(k);

    // tab_eff_Tl[k]=eff_Tl ;

    if (k==0) {
      tab_eff_Tl_first=eff_Tl ;
    }
    else {
      tab_eff_Tl[k-1]=eff_Tl ;
    }

  }

  file_eff.open (("plots/efficiency_no_cut.txt"), std::ofstream::out | std::ofstream::app) ;
  file_eff << sigma << " " << tab_eff_0nu_first << " " << tab_eff_Tl_first << endl ;
  file_eff.close() ;


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

  config_graph(gr_eff,"","Rejection efficiency ^{208}Tl (%)","Selection efficiency 0#nu#beta#beta (%)","APL",1,1,1) ;

  gr_eff->SetMarkerStyle(33) ;
  gr_eff->GetXaxis()->SetTitleSize(0.06) ;
  gr_eff->SetMarkerSize(1.5) ;
  gr_eff->SetMarkerColor(kCyan+2) ;
  gr_eff->GetYaxis()->SetTitleSize(0.06) ;
  gr_eff->GetYaxis()->SetTitleOffset(0.9) ;
  gr_eff->SetLineWidth(1) ;
  //gr_eff->SetLineColor(kCyan+2) ;

  // if (sigma=="0") {

  //   auto t1 = new TPaveText(0.1840974,0.8471338,0.2428367,0.8917197,"NDC");
  //   t1->SetBorderSize(0) ;
  //   t1->SetFillColor(0) ;
  //   t1->SetTextSize(0.045) ;
  //   t1->AddText("No cut") ;
  //   t1->Draw() ;

  //   auto t2 = new TPaveText(0.7951289,0.7685775,0.8309456,0.8386412,"NDC");
  //   t2->SetBorderSize(0) ;
  //   t2->SetFillColor(0) ;
  //   t2->SetTextSize(0.045) ;
  //   t2->AddText("k=4") ;
  //   t2->Draw() ;

  //   auto t3 = new TPaveText(0.7994269,0.1974522,0.8710602,0.2420382,"NDC");
  //   t3->SetBorderSize(0) ;
  //   t3->SetFillColor(0) ;
  //   t3->SetFillColor(0) ;
  //   t3->SetTextSize(0.045) ;
  //   t3->AddText("k=0.1") ;
  //   t3->Draw() ;

  // }

  // else if (sigma=="400") {

  //   auto t1 = new TPaveText(0.189112,0.915074,0.247851,0.95966,"NDC");
  //   t1->SetBorderSize(0) ;
  //   t1->SetFillColor(0) ;
  //   t1->SetTextSize(0.045) ;
  //   t1->AddText("No cut") ;
  //   t1->Draw() ;

  //   auto t2 = new TPaveText(0.209169,0.785563,0.267908,0.857749,"NDC");
  //   t2->SetBorderSize(0) ;
  //   t2->SetFillColor(0) ;
  //   t2->SetTextSize(0.045) ;
  //   t2->AddText("k=4") ;
  //   t2->Draw() ;

  //   auto t3 = new TPaveText(0.799427,0.18896,0.87106,0.233546,"NDC");
  //   t3->SetBorderSize(0) ;
  //   t3->SetFillColor(0) ;
  //   t3->SetFillColor(0) ;
  //   t3->SetTextSize(0.045) ;
  //   t3->AddText("k=0.1") ;
  //   t3->Draw() ;

  // }

  c1->SaveAs(Form("plots/efficiency_cut_proba_%s.pdf",sigma.c_str())) ;
  gr_eff->SaveAs(Form("plots/efficiency_cut_proba_%s.root",sigma.c_str())) ;

}
