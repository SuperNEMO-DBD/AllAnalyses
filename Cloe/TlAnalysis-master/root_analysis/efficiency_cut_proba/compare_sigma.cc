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

void compare_sigma(){

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

  TTree *t_eff_no_cut = new TTree("t_eff_no_cut","efficiency") ;
  t_eff_no_cut->ReadFile("plots/efficiency_no_cut.txt","sigma/F:eff_0nu/F:eff_Tl/F") ;

  float eff_0nu, eff_Tl, sigma ;
  t_eff_no_cut->SetBranchAddress("eff_Tl",&eff_Tl) ;
  t_eff_no_cut->SetBranchAddress("eff_0nu",&eff_0nu) ;
  t_eff_no_cut->SetBranchAddress("sigma",&sigma) ;

  TMarker *m_0ps ;
  TMarker *m_100ps ;
  TMarker *m_200ps ;
  TMarker *m_300ps ;
  TMarker *m_400ps ;

  for (int k=0; k<t_eff_no_cut->GetEntries(); k++){
    t_eff_no_cut->GetEntry(k);


    if (k==0) {
      m_0ps = new TMarker(eff_Tl,eff_0nu,34);
    }
    if (k==1) {
      m_100ps = new TMarker(eff_Tl,eff_0nu,34);
    }
    if (k==2) {
      m_200ps = new TMarker(eff_Tl,eff_0nu,34);
    }
    if (k==3) {
      m_300ps = new TMarker(eff_Tl,eff_0nu,34);
    }
    if (k==4) {
      m_400ps = new TMarker(eff_Tl,eff_0nu,34);
    }

  }

  string file_data_0ps = "/home/girardcarillo/Workdir/Analyses/TlAnalysis/root_analysis/efficiency_cut_proba/plots/efficiency_cut_proba_0.root" ;
  TFile *theDataFile_0ps = new TFile(file_data_0ps.c_str(),"READ") ;

  TGraph *gr_eff_0ps = (TGraph*)theDataFile_0ps->Get("Graph");

  string file_data_400ps = "/home/girardcarillo/Workdir/Analyses/TlAnalysis/root_analysis/efficiency_cut_proba/plots/efficiency_cut_proba_4.root" ;
  TFile *theDataFile_400ps = new TFile(file_data_400ps.c_str(),"READ") ;

  TGraph *gr_eff_400ps = (TGraph*)theDataFile_400ps->Get("Graph");

  string file_data_300ps = "/home/girardcarillo/Workdir/Analyses/TlAnalysis/root_analysis/efficiency_cut_proba/plots/efficiency_cut_proba_3.root" ;
  TFile *theDataFile_300ps = new TFile(file_data_300ps.c_str(),"READ") ;

  TGraph *gr_eff_300ps = (TGraph*)theDataFile_300ps->Get("Graph");

  string file_data_200ps = "/home/girardcarillo/Workdir/Analyses/TlAnalysis/root_analysis/efficiency_cut_proba/plots/efficiency_cut_proba_2.root" ;
  TFile *theDataFile_200ps = new TFile(file_data_200ps.c_str(),"READ") ;

  TGraph *gr_eff_200ps = (TGraph*)theDataFile_200ps->Get("Graph");

  string file_data_100ps = "/home/girardcarillo/Workdir/Analyses/TlAnalysis/root_analysis/efficiency_cut_proba/plots/efficiency_cut_proba_1.root" ;
  TFile *theDataFile_100ps = new TFile(file_data_100ps.c_str(),"READ") ;

  TGraph *gr_eff_100ps = (TGraph*)theDataFile_100ps->Get("Graph");

  gr_eff_400ps->SetMarkerColor(kOrange-3) ;
  gr_eff_300ps->SetMarkerColor(kMagenta+2) ;
  gr_eff_200ps->SetMarkerColor(kGreen+2) ;
  gr_eff_100ps->SetMarkerColor(kPink-8) ;
  gr_eff_0ps->SetMarkerColor(kCyan+2) ;

  gr_eff_400ps->SetMarkerStyle(20) ;
  gr_eff_300ps->SetMarkerStyle(20) ;
  gr_eff_200ps->SetMarkerStyle(20) ;
  gr_eff_100ps->SetMarkerStyle(20) ;
  gr_eff_0ps->SetMarkerStyle(20) ;

  gr_eff_400ps->SetMarkerSize(0.7) ;
  gr_eff_300ps->SetMarkerSize(0.7) ;
  gr_eff_200ps->SetMarkerSize(0.7) ;
  gr_eff_100ps->SetMarkerSize(0.7) ;
  gr_eff_0ps->SetMarkerSize(0.7) ;

  gr_eff_400ps->SetLineColor(kOrange-3) ;
  gr_eff_300ps->SetLineColor(kMagenta+2) ;
  gr_eff_200ps->SetLineColor(kGreen+2) ;
  gr_eff_100ps->SetLineColor(kPink-8) ;
  gr_eff_0ps->SetLineColor(kCyan+2) ;

  gr_eff_400ps->SetLineWidth(2) ;
  gr_eff_300ps->SetLineWidth(2) ;
  gr_eff_200ps->SetLineWidth(2) ;
  gr_eff_100ps->SetLineWidth(2) ;
  gr_eff_0ps->SetLineWidth(2) ;


  m_0ps->SetMarkerColor(gr_eff_0ps->GetMarkerColor()) ;
  m_100ps->SetMarkerColor(gr_eff_100ps->GetMarkerColor()) ;
  m_200ps->SetMarkerColor(gr_eff_200ps->GetMarkerColor()) ;
  m_300ps->SetMarkerColor(gr_eff_300ps->GetMarkerColor()) ;
  m_400ps->SetMarkerColor(gr_eff_400ps->GetMarkerColor()) ;


  m_0ps->SetMarkerSize(1.5) ;
  m_100ps->SetMarkerSize(1.5) ;
  m_200ps->SetMarkerSize(1.5) ;
  m_300ps->SetMarkerSize(1.5) ;
  m_400ps->SetMarkerSize(1.5) ;


  TMultiGraph *mg = new TMultiGraph();

  mg->Add(gr_eff_0ps,"lp");
  mg->Add(gr_eff_100ps,"lp");
  mg->Add(gr_eff_200ps,"lp");
  mg->Add(gr_eff_300ps,"lp");
  mg->Add(gr_eff_400ps,"lp");
  mg->Draw("a");

  mg->GetXaxis()->SetLimits(5.,70.) ;

  m_0ps->Draw("SAME");
  m_100ps->Draw("SAME");
  m_200ps->Draw("SAME");
  m_300ps->Draw("SAME");
  m_400ps->Draw("SAME");


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

  auto leg = new TLegend(0.6747851,0.6199575,0.9555874,0.9681529);
  leg->SetBorderSize(1) ;
  TLegendEntry *le = leg->AddEntry((TObject*)0,"Only P_{int}>0.04","p");
  le->SetMarkerStyle(34) ;
  le->SetMarkerSize(1.5) ;
  leg->AddEntry(gr_eff_0ps,"#sigma_{t} = 0 ps","lp");
  leg->AddEntry(gr_eff_100ps,"#sigma_{t} = 100 ps","lp");
  leg->AddEntry(gr_eff_200ps,"#sigma_{t} = 200 ps","lp");
  leg->AddEntry(gr_eff_300ps,"#sigma_{t} = 300 ps","lp");
  leg->AddEntry(gr_eff_400ps,"#sigma_{t} = 400 ps","lp");
  leg->Draw() ;


  auto t1 = new TPaveText(0.52937,0.687898,0.588109,0.753715,"NDC");
  t1->SetBorderSize(0) ;
  t1->SetFillColor(0) ;
  t1->SetTextSize(0.045) ;
  t1->AddText("P_{exp}>0.95") ;
  t1->Draw() ;

  auto t2 = new TPaveText(0.777937,0.2356688,0.8366762,0.3014862,"NDC");
  t2->SetBorderSize(0) ;
  t2->SetFillColor(0) ;
  t2->SetTextSize(0.045) ;
  t2->AddText("P_{exp}>0") ;
  t2->Draw() ;

  // auto t3 = new TPaveText(0.2522961,0.939759,0.3106429,0.9598394,"NDC");
  // t3->SetBorderSize(0) ;
  // t3->SetFillColor(0) ;
  // t3->SetFillColor(0) ;
  // t3->SetTextSize(0.045) ;
  // t3->AddText("k=6") ;
  // t3->Draw() ;

  c1->SaveAs("plots/compare_sigma.pdf") ;

}
