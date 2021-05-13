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

void compare_cuts(string sigma){


  int color ;

  if (sigma=="0") {
    color = kCyan+2 ;
  }
  if (sigma=="1") {
    color = kPink-8 ;
  }
  if (sigma=="2") {
    color = kGreen+2 ;
  }
  if (sigma=="3") {
    color = kMagenta+2 ;
  }
  if (sigma=="4") {
    color = kOrange-3 ;
  }


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
  // c1->SetGridx() ;
  // c1->SetGridy() ;

  string file_data_proba = Form("/home/girardcarillo/Workdir/Analyses/TlAnalysis/root_analysis/compare_cuts/efficiency_cut_proba/plots/efficiency_cut_proba_%s.root",sigma.c_str()) ;
  TFile *theDataFile_proba = new TFile(file_data_proba.c_str(),"READ") ;

  TGraph *gr_eff_proba = (TGraph*)theDataFile_proba->Get("Graph");

  string file_data_delta_t = Form("/home/girardcarillo/Workdir/Analyses/TlAnalysis/root_analysis/compare_cuts/efficiency_cut_delta_t/plots/efficiency_cut_delta_t_%s.root",sigma.c_str()) ;
  TFile *theDataFile_delta_t = new TFile(file_data_delta_t.c_str(),"READ") ;

  TGraph *gr_eff_delta_t = (TGraph*)theDataFile_delta_t->Get("Graph");

  gr_eff_proba->SetMarkerColor(color) ;
  gr_eff_proba->SetMarkerStyle(20) ;
  gr_eff_proba->SetMarkerSize(0.7) ;
  gr_eff_proba->SetLineColor(color) ;
  gr_eff_proba->SetLineWidth(2) ;

  gr_eff_delta_t->SetMarkerColor(color) ;
  gr_eff_delta_t->SetMarkerStyle(23) ;
  gr_eff_delta_t->SetMarkerSize(0.7) ;
  gr_eff_delta_t->SetLineColor(color) ;
  gr_eff_delta_t->SetLineStyle(2) ;
  gr_eff_delta_t->SetLineWidth(2) ;

  TMultiGraph *mg = new TMultiGraph();
  mg->Add(gr_eff_proba,"lp");
  mg->Add(gr_eff_delta_t,"lp");
  mg->Draw("a");

  mg->SetTitle("") ;
  mg->GetXaxis()->SetTitle("Rejection efficiency ^{208}Tl (%)") ;
  mg->GetYaxis()->SetTitle("Selection efficiency 0#nu#beta#beta (%)") ;

  mg->GetXaxis()->SetNdivisions(110);
  mg->GetYaxis()->SetNdivisions(110);
  mg->GetXaxis()->SetLabelSize(0.05);
  mg->GetYaxis()->SetLabelSize(0.05);

  mg->GetYaxis()->SetTitleOffset(1.1) ;
  mg->GetYaxis()->SetTitleSize(0.06);
  mg->GetXaxis()->SetTitleSize(0.06);

  mg->GetXaxis()->SetTickSize(0.025) ;
  mg->GetYaxis()->SetTickSize(0.015) ;
  mg->GetXaxis()->SetLabelFont(42) ;
  mg->GetYaxis()->SetLabelFont(42) ;
  mg->GetXaxis()->SetTitleFont(42) ;
  mg->GetYaxis()->SetTitleFont(42) ;

  auto leg = new TLegend(0.196275,0.269639,0.593123,0.397028);
  leg->SetBorderSize(0) ;
  leg->AddEntry(gr_eff_proba,"Probability selection","l");
  leg->AddEntry(gr_eff_delta_t,"#Delta t selection","l");
  leg->Draw() ;


  // auto t1 = new TPaveText(0.1734198,0.8985944,0.2323069,0.9186747,"NDC");
  // t1->SetBorderSize(0) ;
  // t1->SetFillColor(0) ;
  // t1->SetTextSize(0.045) ;
  // t1->AddText("No cut") ;
  // t1->Draw() ;

  c1->SaveAs(Form("plots/compare_cuts_%s.pdf",sigma.c_str())) ;

}
