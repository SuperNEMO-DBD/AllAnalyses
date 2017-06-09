#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <THStack.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TGaxis.h>
#include <TCanvas.h>
#include <TTree.h>
#include <TLegend.h>
#include <TRandom3.h>
#include <iostream>
#include <TF1.h>
#include <TVirtualFitter.h>
#include <TMath.h>
#include <TPaveText.h>
#include <TGraphErrors.h>
#include <TFrame.h>
#include <fstream>
#include "../Machinery/addBackgrounds_2b2n.h"
#include "../Machinery/ReadWriteActivities.h"
#include "../Machinery/calculateRatio.h"

// Set Global variables to be used by all
Int_t TotalAccptRunTime = 167629292;
Int_t TotalAccptDeadTime = 1867931;
const Int_t AccptRunTime = TotalAccptRunTime - TotalAccptDeadTime;
TFile* infile_2b2n = new TFile("../Histograms/Histograms_PaperPlots.root","READ");

// 2b2n
TH1D* h_2b2n_Data = (TH1D*)infile_2b2n->Get("hTotEnergy_Data");

// Declare collection of THStacks that all MC will go into
THStack* StackColl_2b2n[1];
THStack* ExtStackColl_2b2n[1];
THStack* RadStackColl_2b2n[1];
THStack* IntStackColl_2b2n[1];
THStack* Bi214StackColl_2b2n[1];
THStack* Tl208StackColl_2b2n[1];
THStack* SigStackColl_2b2n[1];
THStack* SigStackColl_2b0n[1];

// Declare legend and chi square TPaveText to be filled
TLegend* Legend_2b2n[1];
TLegend* LegendLog_2b2n[1];
TPaveText* ChiSquares_2b2n[1];
TPaveText* ChiSquaresLog_2b2n[1];

// Make arrays to pass other functions
Double_t Activities_Ext[23], Activities_Ext_Err[23], Denominators_Ext[21];
Double_t Activities_Rad[17], Activities_Rad_Err[17], Denominators_Rad[13];
Double_t Activities_Int[9],  Activities_Int_Err[9],  Denominators_Int[16];
Double_t Activities_Sig[2],  Activities_Sig_Err[2],  Denominators_Sig[2];
Double_t AdjustActs[44], AdjustActs_Err[44];
Double_t CovMatrix[44][44];

Int_t DrawPlots(){
  // Sort out root's horrible defaults
  gROOT->Reset();
  gROOT->SetStyle("Plain");
  gStyle->SetCanvasBorderMode(0);

  // Set canvas margins and stats options to make plots nicer
  gStyle->SetPadTopMargin(0.05);
  gStyle->SetPadRightMargin(0.05);
  gStyle->SetTitleOffset(1.2,"y");
  gStyle->SetStatBorderSize(0);
  gStyle->SetOptStat(0);
  gStyle->SetStatX(0.946);
  gStyle->SetStatY(0.936);
  gStyle->SetPalette(1);
  TGaxis::SetMaxDigits(4);
  gStyle->SetPaintTextFormat(".3f");

  // First, check data histogram pointer is OK
  if(h_2b2n_Data==0) {cout << "ERROR:h_2b2n_Data not found"   << endl; exit(0);}

  // Read information on activities and denominators from files
  readActivities("Activities.txt", Activities_Ext, Activities_Ext_Err, Activities_Rad, Activities_Rad_Err, Activities_Int, Activities_Int_Err, Activities_Sig, Activities_Sig_Err, AdjustActs, AdjustActs_Err);
  readDenominators("Denominators.txt", Denominators_Ext, Denominators_Rad, Denominators_Int, Denominators_Sig);
  readCovMatrix("CovMatrix.txt", CovMatrix);

  // Add all backgrounds (including 2b0n signal activity)
  addBackgrounds_2b2n (Activities_Ext, Activities_Ext_Err, Denominators_Ext, Activities_Rad, Activities_Rad_Err, Denominators_Rad, Activities_Int, Activities_Int_Err, Denominators_Int, Activities_Sig, Activities_Sig_Err, Denominators_Sig, AdjustActs, AdjustActs_Err, CovMatrix);

  // Draw Output - three pads here: 1) Main log plot 2) Ratio plot (excluding 2b0n) 3) Linear inset with legend

  // Make canvas and put pad1 in top 75%
  TCanvas* c1_2b2n = new TCanvas("c1_2b2n","Total Electron Energy - 2b2n",10,10,1080,960);
  TPad* pad1 = new TPad("pad1", "main",0.0,0.25,1.0,1.0);
  pad1->SetBottomMargin(0);
  pad1->SetLogy();
  pad1->Draw();
  pad1->cd();

  // First sort of 2b0n on plot to be dotted line
  ((TH1D*)StackColl_2b2n[0]->GetStack()->Last())->SetLineColor(((TH1D*)StackColl_2b2n[0]->GetStack()->Last())->GetFillColor());
  ((TH1D*)StackColl_2b2n[0]->GetStack()->Last())->SetLineStyle(2);
  ((TH1D*)StackColl_2b2n[0]->GetStack()->Last())->SetLineWidth(2);
  ((TH1D*)StackColl_2b2n[0]->GetStack()->Last())->SetFillColor(0);

  // Set ranges and draw data main log plot histogram
  h_2b2n_Data->SetMarkerStyle(20);
  h_2b2n_Data->GetXaxis()->SetRangeUser(1.5,5.0);
  h_2b2n_Data->GetYaxis()->SetRangeUser(0.3,2e3);
  h_2b2n_Data->Draw();
  StackColl_2b2n[0]->Draw("HISTSAME");
  h_2b2n_Data->Draw("SAME");
  gPad->RedrawAxis();
  c1_2b2n->Update();
  c1_2b2n->cd();

  // Create pad2 in bottom 25% where we'll put our ratio plot
  TPad *pad2 = new TPad("pad2", "ratio",0.0,0.0,1.0,0.25);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.3);
  pad2->Draw();
  pad2->cd();
  
  TGraphErrors* ratio = calculateRatio(h_2b2n_Data, 0);
  ratio->SetMarkerStyle(20);
  ratio->Draw("AP");
  ratio->GetXaxis()->SetLimits(pad1->GetUxmin(),pad1->GetUxmax());
  ratio->GetYaxis()->SetRangeUser(0.001,1.999);
  ratio->GetYaxis()->SetNdivisions(306);
  ratio->SetTitle("");
  ratio->GetYaxis()->SetTitle("Data/MC");
  ratio->GetXaxis()->SetTitle(h_2b2n_Data->GetXaxis()->GetTitle());
  ratio->GetXaxis()->SetTitleSize(h_2b2n_Data->GetXaxis()->GetTitleSize()*3);
  ratio->GetXaxis()->SetLabelSize(h_2b2n_Data->GetXaxis()->GetLabelSize()*3);
  ratio->GetYaxis()->SetTitleOffset(h_2b2n_Data->GetXaxis()->GetTitleOffset()/3);
  ratio->GetYaxis()->SetTitleSize(h_2b2n_Data->GetYaxis()->GetTitleSize()*3);
  ratio->GetYaxis()->SetLabelSize(h_2b2n_Data->GetYaxis()->GetLabelSize()*3);

  //If points are off plot, they just don't get drawn - put in errors as TLine by hand
  c1_2b2n->Update();
  for(int pt = 0; pt < ratio->GetN(); pt++){
    double x_tmp, y_tmp;
    ratio->GetPoint(pt,x_tmp,y_tmp);
    if(y_tmp > pad2->GetUymax()){
      double y_max = pad2->GetUymax();
      double y_min = (y_tmp-ratio->GetErrorY(pt) < pad2->GetUymin()) ? pad2->GetUymin() : y_tmp-ratio->GetErrorY(pt);
      TLine* error = new TLine(x_tmp,y_min, x_tmp, y_max);
      error->Draw();
    } else if (y_tmp < pad2->GetUymin()) {
      double y_min = pad2->GetUymin();
      double y_max = (y_tmp+ratio->GetErrorY(pt) > pad2->GetUymax()) ? pad2->GetUymax() : y_tmp+ratio->GetErrorY(pt);
      TLine* error = new TLine(x_tmp,y_min, x_tmp, y_max);
      error->Draw();
    }
  }

  TLine* unity = new TLine(pad1->GetUxmin(),1,pad1->GetUxmax(),1);
  unity->SetLineStyle(2);
  unity->Draw();
  c1_2b2n->cd();

  //Draw pad3 in top right for linear plot and legend
  TPad *pad3 = new TPad("pad3", "linear",0.45,0.45,0.95,0.962);
  pad3->SetLineColor(2);
  pad3->Draw();
  pad3->cd();

  // Reset plot ranges and draw data main log plot histogram
  TH1D* h_2b2n_Data_Lin = (TH1D*)h_2b2n_Data->Clone("h_2b2n_Data_Lin");
  h_2b2n_Data_Lin->SetMarkerStyle(20);
  h_2b2n_Data_Lin->SetTitle(";;");
  h_2b2n_Data_Lin->GetXaxis()->SetRangeUser(2.5,3.49);
  h_2b2n_Data_Lin->GetYaxis()->SetRangeUser(0.,15);
  h_2b2n_Data_Lin->GetXaxis()->SetNdivisions(5);
  h_2b2n_Data_Lin->GetXaxis()->SetLabelSize(h_2b2n_Data->GetXaxis()->GetLabelSize()*1.75);
  h_2b2n_Data_Lin->GetYaxis()->SetLabelSize(h_2b2n_Data->GetYaxis()->GetLabelSize()*1.75);
  h_2b2n_Data_Lin->Draw();
  StackColl_2b2n[0]->Draw("HISTSAME");
  h_2b2n_Data_Lin->Draw("SAME");
  gPad->RedrawAxis();

  //Make new legend for this plot
  TLegend* LegendPaper = new TLegend(0.47,0.33,0.99,0.947);
  LegendPaper->SetFillStyle(0);
  LegendPaper->SetLineColor(0);
  LegendPaper->SetBorderSize(0);

  // Add legend entries
  LegendPaper->AddEntry(h_2b2n_Data, Form("Data (%0.f)",h_2b2n_Data->GetEntries()), "lpe");
  TH1 *hTmp;
  TIter next(StackColl_2b2n[0]->GetHists());
  hTmp = (TH1*) next();
  LegendPaper->AddEntry(hTmp, "External BGs", "f");
  hTmp = (TH1*) next();
  LegendPaper->AddEntry(hTmp, "Radon BGs", "f");
  hTmp = (TH1*) next();
  LegendPaper->AddEntry(hTmp, "Internal ^{234m}Pa", "f");
  hTmp = (TH1*) next();
  LegendPaper->AddEntry(hTmp, "Internal ^{214}Bi", "f");
  hTmp = (TH1*) next();
  LegendPaper->AddEntry(hTmp, "Internal ^{208}Tl", "f");
  hTmp = (TH1*) next();
  LegendPaper->AddEntry(hTmp, "2#nu#beta#beta ^{82}Se", "f");
  hTmp = (TH1*) next();
  hTmp->SetFillColor(0);
  hTmp->SetLineColor(kViolet);
  hTmp->SetLineStyle(2);
  hTmp->SetLineWidth(2);
  LegendPaper->AddEntry(hTmp, "0#nu#beta#beta Limit", "f");

  LegendPaper->Draw();
  c1_2b2n->Update();
  c1_2b2n->cd();

  c1_2b2n->SaveAs("Images/png/1 - Total Electron Energy.png");
  c1_2b2n->SaveAs("Images/eps/1 - Total Electron Energy.eps");
  c1_2b2n->SaveAs("Images/gif/1 - Total Electron Energy.gif");

  
  return 0;
}

