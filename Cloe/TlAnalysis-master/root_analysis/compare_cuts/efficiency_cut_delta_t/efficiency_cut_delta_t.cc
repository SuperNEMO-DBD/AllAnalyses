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

void efficiency_cut_delta_t(string sigma){

  int n=15 ;

  TTree *t_eff_0nu = new TTree("t_eff_0nu","efficiency") ;
  t_eff_0nu->ReadFile(Form("efficiency_cut_delta_t_0nubb_%s.txt",sigma.c_str()),"level_cut/F:eff_0nu/F") ;

  float eff_0nu, level_cut ;
  t_eff_0nu->SetBranchAddress("level_cut",&level_cut) ;
  t_eff_0nu->SetBranchAddress("eff_0nu",&eff_0nu) ;

  double tab_eff_0nu[n] ;

  for (int k=0; k<t_eff_0nu->GetEntries(); k++){
    t_eff_0nu->GetEntry(k);

    if (k==n-1) {
      tab_eff_0nu[k]=eff_0nu ;
    }
    else {
      tab_eff_0nu[k]=100-eff_0nu ;
    }

  }

  TTree *t_eff_Tl = new TTree("t_eff_Tl","efficiency") ;
  t_eff_Tl->ReadFile(Form("efficiency_cut_delta_t_208Tl_%s.txt",sigma.c_str()),"level_cut/F:eff_Tl/F") ;

  float eff_Tl ;
  t_eff_Tl->SetBranchAddress("eff_Tl",&eff_Tl) ;


  double tab_eff_Tl[n] ;

  for (int k=0; k<t_eff_Tl->GetEntries(); k++){
    t_eff_Tl->GetEntry(k);

    if (k==n-1) {
      tab_eff_Tl[k]=100-eff_Tl ;
    }
    else {
      tab_eff_Tl[k]=eff_Tl ;
    }

  }

  for (int i = 0; i < n; ++i) {
    cout << i << " " << tab_eff_Tl[i] << " " << tab_eff_0nu[i] << endl ;
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

  config_graph(gr_eff,"","Rejection efficiency ^{208}Tl (%)","Selection efficiency 0#nu#beta#beta (%)","AP",1,1,1) ;

  gr_eff->SetMarkerStyle(33) ;
  gr_eff->GetXaxis()->SetTitleSize(0.06) ;
  gr_eff->SetMarkerSize(1.5) ;
  gr_eff->SetMarkerColor(kCyan+2) ;
  gr_eff->GetYaxis()->SetTitleSize(0.06) ;
  gr_eff->GetYaxis()->SetTitleOffset(0.9) ;
  gr_eff->SetLineWidth(1) ;
  //gr_eff->SetLineColor(kCyan+2) ;

  if (sigma=="0") {

    auto t1 = new TPaveText(0.1862464,0.8237792,0.2449857,0.8683652,"NDC");
    t1->SetBorderSize(0) ;
    t1->SetFillColor(0) ;
    t1->SetTextSize(0.045) ;
    t1->AddText("No cut") ;
    t1->Draw() ;

    auto t2 = new TPaveText(0.8810888,0.1974522,0.9398281,0.2675159,"NDC");
    t2->SetBorderSize(0) ;
    t2->SetFillColor(0) ;
    t2->SetTextSize(0.045) ;
    t2->AddText("k<0.45") ;
    t2->Draw() ;

    auto t3 = new TPaveText(0.2005731,0.5509554,0.2593123,0.5955414,"NDC");
    t3->SetBorderSize(0) ;
    t3->SetFillColor(0) ;
    t3->SetFillColor(0) ;
    t3->SetTextSize(0.045) ;
    t3->AddText("k<0") ;
    t3->Draw() ;

    auto t4 = new TPaveText(0.4083095,0.2590234,0.4670487,0.3036093,"NDC");
    t4->SetBorderSize(0) ;
    t4->SetFillColor(0) ;
    t4->SetFillColor(0) ;
    t4->SetTextSize(0.045) ;
    t4->AddText("k<0.10") ;
    t4->Draw() ;

  }

  else if (sigma=="400") {

    auto t1 = new TPaveText(0.1862464,0.8237792,0.2449857,0.8683652,"NDC");
    t1->SetBorderSize(0) ;
    t1->SetFillColor(0) ;
    t1->SetTextSize(0.045) ;
    t1->AddText("No cut") ;
    t1->Draw() ;

    auto t2 = new TPaveText(0.9040115,0.2653928,0.9627507,0.3099788,"NDC");
    t2->SetBorderSize(0) ;
    t2->SetFillColor(0) ;
    t2->SetTextSize(0.045) ;
    t2->AddText("k<0.45") ;
    t2->Draw() ;

    auto t3 = new TPaveText(0.4813754,0.4946921,0.5401146,0.5392781,"NDC");
    t3->SetBorderSize(0) ;
    t3->SetFillColor(0) ;
    t3->SetFillColor(0) ;
    t3->SetTextSize(0.045) ;
    t3->AddText("k<0") ;
    t3->Draw() ;

  }

  c1->SaveAs(Form("plots/efficiency_cut_delta_t_%s.pdf",sigma.c_str())) ;
  gr_eff->SaveAs(Form("plots/efficiency_cut_delta_t_%s.root",sigma.c_str())) ;

}
