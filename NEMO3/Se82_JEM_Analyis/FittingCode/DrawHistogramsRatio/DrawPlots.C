#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <THStack.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TGaxis.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <iostream>
#include <TF1.h>
#include <TVirtualFitter.h>
#include <TMath.h>
#include <TPaveText.h>
#include <fstream>
#include <TGraphErrors.h>
#include "../Machinery/addBackgrounds_1e.h"
#include "../Machinery/addBackgrounds_1e1g.h"
#include "../Machinery/addBackgrounds_1e2g.h"
#include "../Machinery/addBackgrounds_1e1a.h"
#include "../Machinery/addBackgrounds_ExtEG.h"
#include "../Machinery/addBackgrounds_OCE.h"
#include "../Machinery/addBackgrounds_2b2n.h"
#include "../Machinery/ReadWriteActivities.h"
#include "../Machinery/calculateRatio_1e.h"
#include "../Machinery/calculateRatio_1e1g.h"
#include "../Machinery/calculateRatio_1e2g.h"
#include "../Machinery/calculateRatio_1e1a.h"
#include "../Machinery/calculateRatio_ExtEG.h"
#include "../Machinery/calculateRatio_OCE.h"
#include "../Machinery/calculateRatio_2b2n.h"

// Set Global variables to be used by all
Int_t TotalAccptRunTime = 167629292;
Int_t TotalAccptDeadTime = 1868832;
const Int_t AccptRunTime = TotalAccptRunTime - TotalAccptDeadTime;
TFile* infile_1e   = new TFile("../Histograms/Histograms_1e.root",  "READ");
TFile* infile_1e1g = new TFile("../Histograms/Histograms_1e1g.root", "READ");
TFile* infile_1e2g = new TFile("../Histograms/Histograms_1e2g.root","READ");
TFile* infile_1e1a = new TFile("../Histograms/Histograms_1e1a.root","READ");
TFile* infile_OCE  = new TFile("../Histograms/Histograms_OCE.root","READ");
TFile* infile_ExtEG= new TFile("../Histograms/Histograms_ExtEG.root","READ");
TFile* infile_2b2n = new TFile("../Histograms/Histograms_2b2n.root","READ");

// Declare data histograms globally to be used for making legends/fitting etc
// 1e
TH1D* h_1e_Data_P1_SeOld    = (TH1D*)infile_1e->Get("hElectronEnergy_Data_P1_SeOld");
TH1D* h_1e_Data_P1_SeNew    = (TH1D*)infile_1e->Get("hElectronEnergy_Data_P1_SeNew");
TH1D* h_1e_Data_P1_Strip    = (TH1D*)infile_1e->Get("hElectronEnergy_Data_P1_Strip");
TH1D* h_1e_Data_P2_SeOld    = (TH1D*)infile_1e->Get("hElectronEnergy_Data_P2_SeOld");
TH1D* h_1e_Data_P2_SeNew    = (TH1D*)infile_1e->Get("hElectronEnergy_Data_P2_SeNew");
TH1D* h_1e_Data_P2_Strip    = (TH1D*)infile_1e->Get("hElectronEnergy_Data_P2_Strip");

// 1e1g
TH1D* h_1e1g_Data_P1_SeOld  = (TH1D*)infile_1e1g->Get("hEnergySum_Data_P1_SeOld");
TH1D* h_1e1g_Data_P1_SeNew  = (TH1D*)infile_1e1g->Get("hEnergySum_Data_P1_SeNew");
TH1D* h_1e1g_Data_P1_Strip  = (TH1D*)infile_1e1g->Get("hEnergySum_Data_P1_Strip");
TH1D* h_1e1g_Data_P2_SeOld  = (TH1D*)infile_1e1g->Get("hEnergySum_Data_P2_SeOld");
TH1D* h_1e1g_Data_P2_SeNew  = (TH1D*)infile_1e1g->Get("hEnergySum_Data_P2_SeNew");
TH1D* h_1e1g_Data_P2_Strip  = (TH1D*)infile_1e1g->Get("hEnergySum_Data_P2_Strip");

// 1e2g
TH1D* h_1e2g_Data_SeOld     = (TH1D*)infile_1e2g->Get("hElectronEnergy_Data_SeOld");
TH1D* h_1e2g_Data_SeNew     = (TH1D*)infile_1e2g->Get("hElectronEnergy_Data_SeNew");

// 1e1a
TH1D* h_1e1a_Data_P1_aOuteOut_Sector6 = (TH1D*)infile_1e1a->Get("hAlphaLength_Data_P1_aOuteOut_Sector6");
TH1D* h_1e1a_Data_P1_aIneOut_Sector6  = (TH1D*)infile_1e1a->Get("hAlphaLength_Data_P1_aIneOut_Sector6");
TH1D* h_1e1a_Data_P1_aOuteIn_Sector6  = (TH1D*)infile_1e1a->Get("hAlphaLength_Data_P1_aOuteIn_Sector6");
TH1D* h_1e1a_Data_P1_aIneIn_Sector6   = (TH1D*)infile_1e1a->Get("hAlphaLength_Data_P1_aIneIn_Sector6");
TH1D* h_1e1a_Data_P1_aOuteOut_Sector7 = (TH1D*)infile_1e1a->Get("hAlphaLength_Data_P1_aOuteOut_Sector7");
TH1D* h_1e1a_Data_P1_aIneOut_Sector7  = (TH1D*)infile_1e1a->Get("hAlphaLength_Data_P1_aIneOut_Sector7");
TH1D* h_1e1a_Data_P1_aOuteIn_Sector7  = (TH1D*)infile_1e1a->Get("hAlphaLength_Data_P1_aOuteIn_Sector7");
TH1D* h_1e1a_Data_P1_aIneIn_Sector7   = (TH1D*)infile_1e1a->Get("hAlphaLength_Data_P1_aIneIn_Sector7");
TH1D* h_1e1a_Data_P1_aOuteOut_Sector8 = (TH1D*)infile_1e1a->Get("hAlphaLength_Data_P1_aOuteOut_Sector8");
TH1D* h_1e1a_Data_P1_aIneOut_Sector8  = (TH1D*)infile_1e1a->Get("hAlphaLength_Data_P1_aIneOut_Sector8");
TH1D* h_1e1a_Data_P1_aOuteIn_Sector8  = (TH1D*)infile_1e1a->Get("hAlphaLength_Data_P1_aOuteIn_Sector8");
TH1D* h_1e1a_Data_P1_aIneIn_Sector8   = (TH1D*)infile_1e1a->Get("hAlphaLength_Data_P1_aIneIn_Sector8");
TH1D* h_1e1a_Data_P1_AllEvents_Sector6= (TH1D*)infile_1e1a->Get("hAlphaLength_Data_P1_AllEvents_Sector6");
TH1D* h_1e1a_Data_P1_AllEvents_Sector7= (TH1D*)infile_1e1a->Get("hAlphaLength_Data_P1_AllEvents_Sector7");
TH1D* h_1e1a_Data_P1_AllEvents_Sector8= (TH1D*)infile_1e1a->Get("hAlphaLength_Data_P1_AllEvents_Sector8");
TH1D* h_1e1a_Data_P2_aOuteOut_Sector6 = (TH1D*)infile_1e1a->Get("hAlphaLength_Data_P2_aOuteOut_Sector6");
TH1D* h_1e1a_Data_P2_aIneOut_Sector6  = (TH1D*)infile_1e1a->Get("hAlphaLength_Data_P2_aIneOut_Sector6");
TH1D* h_1e1a_Data_P2_aOuteIn_Sector6  = (TH1D*)infile_1e1a->Get("hAlphaLength_Data_P2_aOuteIn_Sector6");
TH1D* h_1e1a_Data_P2_aIneIn_Sector6   = (TH1D*)infile_1e1a->Get("hAlphaLength_Data_P2_aIneIn_Sector6");
TH1D* h_1e1a_Data_P2_aOuteOut_Sector7 = (TH1D*)infile_1e1a->Get("hAlphaLength_Data_P2_aOuteOut_Sector7");
TH1D* h_1e1a_Data_P2_aIneOut_Sector7  = (TH1D*)infile_1e1a->Get("hAlphaLength_Data_P2_aIneOut_Sector7");
TH1D* h_1e1a_Data_P2_aOuteIn_Sector7  = (TH1D*)infile_1e1a->Get("hAlphaLength_Data_P2_aOuteIn_Sector7");
TH1D* h_1e1a_Data_P2_aIneIn_Sector7   = (TH1D*)infile_1e1a->Get("hAlphaLength_Data_P2_aIneIn_Sector7");
TH1D* h_1e1a_Data_P2_aOuteOut_Sector8 = (TH1D*)infile_1e1a->Get("hAlphaLength_Data_P2_aOuteOut_Sector8");
TH1D* h_1e1a_Data_P2_aIneOut_Sector8  = (TH1D*)infile_1e1a->Get("hAlphaLength_Data_P2_aIneOut_Sector8");
TH1D* h_1e1a_Data_P2_aOuteIn_Sector8  = (TH1D*)infile_1e1a->Get("hAlphaLength_Data_P2_aOuteIn_Sector8");
TH1D* h_1e1a_Data_P2_aIneIn_Sector8   = (TH1D*)infile_1e1a->Get("hAlphaLength_Data_P2_aIneIn_Sector8");
TH1D* h_1e1a_Data_P2_AllEvents_Sector6= (TH1D*)infile_1e1a->Get("hAlphaLength_Data_P2_AllEvents_Sector6");
TH1D* h_1e1a_Data_P2_AllEvents_Sector7= (TH1D*)infile_1e1a->Get("hAlphaLength_Data_P2_AllEvents_Sector7");
TH1D* h_1e1a_Data_P2_AllEvents_Sector8= (TH1D*)infile_1e1a->Get("hAlphaLength_Data_P2_AllEvents_Sector8");

// OCE
TH1D* h_OCE_Data_P1_Inner = (TH1D*)infile_OCE->Get("hTotEnergy_Data_P1_Inner");
TH1D* h_OCE_Data_P1_Outer = (TH1D*)infile_OCE->Get("hTotEnergy_Data_P1_Outer");
TH1D* h_OCE_Data_P1_Petal = (TH1D*)infile_OCE->Get("hTotEnergy_Data_P1_Petal");
TH1D* h_OCE_Data_P2_Inner = (TH1D*)infile_OCE->Get("hTotEnergy_Data_P2_Inner");
TH1D* h_OCE_Data_P2_Outer = (TH1D*)infile_OCE->Get("hTotEnergy_Data_P2_Outer");
TH1D* h_OCE_Data_P2_Petal = (TH1D*)infile_OCE->Get("hTotEnergy_Data_P2_Petal");

// ExtEG
TH1D* h_ExtEG_Data_P1_Inner = (TH1D*)infile_ExtEG->Get("hTotEnergy_Data_P1_Inner");
TH1D* h_ExtEG_Data_P1_Outer = (TH1D*)infile_ExtEG->Get("hTotEnergy_Data_P1_Outer");
TH1D* h_ExtEG_Data_P1_Petal = (TH1D*)infile_ExtEG->Get("hTotEnergy_Data_P1_Petal");
TH1D* h_ExtEG_Data_P2_Inner = (TH1D*)infile_ExtEG->Get("hTotEnergy_Data_P2_Inner");
TH1D* h_ExtEG_Data_P2_Outer = (TH1D*)infile_ExtEG->Get("hTotEnergy_Data_P2_Outer");
TH1D* h_ExtEG_Data_P2_Petal = (TH1D*)infile_ExtEG->Get("hTotEnergy_Data_P2_Petal");

// 2b2n
TH1D* h_2b2n_Data_SeOld = (TH1D*)infile_2b2n->Get("hTotEnergySeOld_Data");
TH1D* h_2b2n_Data_SeNew = (TH1D*)infile_2b2n->Get("hTotEnergySeNew_Data");
TH1D* h_2b2n_SingleEnergy_Data_SeOld = (TH1D*)infile_2b2n->Get("hSingleEnergySeOld_Data");
TH1D* h_2b2n_SingleEnergy_Data_SeNew = (TH1D*)infile_2b2n->Get("hSingleEnergySeNew_Data");
TH1D* h_2b2n_MinEnergy_Data_SeOld = (TH1D*)infile_2b2n->Get("hMinEnergySeOld_Data");
TH1D* h_2b2n_MinEnergy_Data_SeNew = (TH1D*)infile_2b2n->Get("hMinEnergySeNew_Data");
TH1D* h_2b2n_MaxEnergy_Data_SeOld = (TH1D*)infile_2b2n->Get("hMaxEnergySeOld_Data");
TH1D* h_2b2n_MaxEnergy_Data_SeNew = (TH1D*)infile_2b2n->Get("hMaxEnergySeNew_Data");

// Declare collection of THStacks that all MC will go into
THStack* StackColl_1e[6];
THStack* IntStackColl_1e[6];
THStack* ExtStackColl_1e[6];
THStack* RadStackColl_1e[6];
THStack* SigStackColl_1e[6];

THStack* StackColl_1e1g[6];
THStack* IntStackColl_1e1g[6];
THStack* ExtStackColl_1e1g[6];
THStack* RadStackColl_1e1g[6];
THStack* SigStackColl_1e1g[6];

THStack* StackColl_1e2g[2];

THStack* StackColl_1e1a_P1[15];
THStack* StackColl_1e1a_P2[15];

THStack* StackColl_OCE[6];
THStack* IntStackColl_OCE[6];
THStack* ExtStackColl_OCE[6];
THStack* RadStackColl_OCE[6];
THStack* SigStackColl_OCE[6];

THStack* StackColl_ExtEG[6];
THStack* IntStackColl_ExtEG[6];
THStack* ExtStackColl_ExtEG[6];
THStack* RadStackColl_ExtEG[6];
THStack* SigStackColl_ExtEG[6];

THStack* StackColl_2b2n[8];
THStack* IntStackColl_2b2n[8];
THStack* ExtStackColl_2b2n[8];
THStack* RadStackColl_2b2n[8];
THStack* SigStackColl_2b2n[8];

// Declare legend and chi square TPaveText to be filled
TLegend* Legend_1e[6];
TLegend* LegendLog_1e[6];
TLegend* Legend_1e1g[6];
TLegend* LegendLog_1e1g[6];
TLegend* Legend_1e2g[2];
TLegend* Legend_1e1a_P1[15];
TLegend* Legend_1e1a_P2[15];
TLegend* Legend_OCE[6];
TLegend* LegendLog_OCE[6];
TLegend* Legend_ExtEG[6];
TLegend* LegendLog_ExtEG[6];
TLegend* Legend_2b2n[8];
TLegend* LegendLog_2b2n[8];
TPaveText* ChiSquares_1e[6];
TPaveText* ChiSquaresLog_1e[6];
TPaveText* ChiSquares_1e1g[6];
TPaveText* ChiSquaresLog_1e1g[6];
TPaveText* ChiSquares_1e2g[2];
TPaveText* ChiSquares_1e1a_P1[15];
TPaveText* ChiSquares_1e1a_P2[15];
TPaveText* ChiSquares_OCE[6];
TPaveText* ChiSquaresLog_OCE[6];
TPaveText* ChiSquares_ExtEG[6];
TPaveText* ChiSquaresLog_ExtEG[6];
TPaveText* ChiSquares_2b2n[8];
TPaveText* ChiSquaresLog_2b2n[8];

// Declare arrays of activities and denominators                                                                                                          
Double_t Activities_Ext[23];
Double_t Activities_Ext_Err[23];
Double_t Denominators_Ext[21];
Double_t Activities_Rad[17];
Double_t Activities_Rad_Err[17];
Double_t Denominators_Rad[13];
Double_t Activities_Int[9];
Double_t Activities_Int_Err[9];
Double_t Denominators_Int[16];
Double_t Activities_Sig[1];
Double_t Activities_Sig_Err[1];
Double_t Denominators_Sig[1];
Double_t AdjustActs[44];
Double_t AdjustActs_Err[44];
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

  //  Read in activities, denominators & covariance matrix
  readActivities("Activities.txt", Activities_Ext, Activities_Ext_Err, Activities_Rad, Activities_Rad_Err, Activities_Int, Activities_Int_Err, Activities_Sig, Activities_Sig_Err, AdjustActs, AdjustActs_Err);
  readDenominators("Denominators.txt", Denominators_Ext, Denominators_Rad, Denominators_Int, Denominators_Sig);
  readCovMatrix("CovMatrix.txt", CovMatrix);

  // Call functions to fill all histograms
  addBackgrounds_1e   (Activities_Ext, Activities_Ext_Err, Denominators_Ext, Activities_Rad, Activities_Rad_Err, Denominators_Rad, Activities_Int, Activities_Int_Err, Denominators_Int, Activities_Sig, Activities_Sig_Err, Denominators_Sig, AdjustActs, AdjustActs_Err);
  addBackgrounds_1e1g (Activities_Ext, Activities_Ext_Err, Denominators_Ext, Activities_Rad, Activities_Rad_Err, Denominators_Rad, Activities_Int, Activities_Int_Err, Denominators_Int, Activities_Sig, Activities_Sig_Err, Denominators_Sig, AdjustActs, AdjustActs_Err);
  addBackgrounds_1e2g (Activities_Ext, Activities_Ext_Err, Denominators_Ext, Activities_Rad, Activities_Rad_Err, Denominators_Rad, Activities_Int, Activities_Int_Err, Denominators_Int, Activities_Sig, Activities_Sig_Err, Denominators_Sig, AdjustActs, AdjustActs_Err);
  addBackgrounds_1e1a (Activities_Ext, Activities_Ext_Err, Denominators_Ext, Activities_Rad, Activities_Rad_Err, Denominators_Rad, Activities_Int, Activities_Int_Err, Denominators_Int, Activities_Sig, Activities_Sig_Err, Denominators_Sig, AdjustActs, AdjustActs_Err);
  addBackgrounds_OCE  (Activities_Ext, Activities_Ext_Err, Denominators_Ext, Activities_Rad, Activities_Rad_Err, Denominators_Rad, Activities_Int, Activities_Int_Err, Denominators_Int, Activities_Sig, Activities_Sig_Err, Denominators_Sig, AdjustActs, AdjustActs_Err);
  addBackgrounds_ExtEG(Activities_Ext, Activities_Ext_Err, Denominators_Ext, Activities_Rad, Activities_Rad_Err, Denominators_Rad, Activities_Int, Activities_Int_Err, Denominators_Int, Activities_Sig, Activities_Sig_Err, Denominators_Sig, AdjustActs, AdjustActs_Err);
  addBackgrounds_2b2n (Activities_Ext, Activities_Ext_Err, Denominators_Ext, Activities_Rad, Activities_Rad_Err, Denominators_Rad, Activities_Int, Activities_Int_Err, Denominators_Int, Activities_Sig, Activities_Sig_Err, Denominators_Sig, AdjustActs, AdjustActs_Err, CovMatrix);

  // Set which plots to draw
  bool DrawSummaryPlots = false;
  bool Draw1ePlots = false;
  bool Draw1e1gPlots = false;
  bool Draw1e2gPlots = false;
  bool Draw1e1aPlots = false;
  bool DrawOCEPlots = false;
  bool DrawExtEGPlots = false;
  bool Draw2b2nPlots = true;
  bool DrawCorrMatrix= false;
  
  // Draw Output - 1e
  if(Draw1ePlots){
    saveRatioPlots_1e(h_1e_Data_P1_SeOld,0, 0,-1, 0.1,1.1, "1e/1 - P1 Electron Energy SeOld");
    saveRatioPlots_1e(h_1e_Data_P1_SeNew,1, 0,-1, 0.1,1.1, "1e/2 - P1 Electron Energy SeNew");
    saveRatioPlots_1e(h_1e_Data_P1_Strip,2, 0,-1, 0.1,1.1, "1e/3 - P1 Electron Energy Strip");
    
    saveRatioPlots_1e(h_1e_Data_P2_SeOld,3, 0,-1, 0.1,1.1, "1e/4 - P2 Electron Energy SeOld");
    saveRatioPlots_1e(h_1e_Data_P2_SeNew,4, 0,-1, 0.1,1.1, "1e/5 - P2 Electron Energy SeNew");
    saveRatioPlots_1e(h_1e_Data_P2_Strip,5, 0,-1, 0.1,1.1, "1e/6 - P2 Electron Energy Strip");
    
    if(!DrawSummaryPlots){
      saveRatioPlots_1e(h_1e_Data_P1_SeOld,0, 0,-1, 0.101,1.1, "1e/1 - P1 Electron Energy SeOld Log",true);
      saveRatioPlots_1e(h_1e_Data_P1_SeNew,1, 0,-1, 0.101,1.1, "1e/2 - P1 Electron Energy SeNew Log",true);
      saveRatioPlots_1e(h_1e_Data_P1_Strip,2, 0,-1, 0.101,1.1, "1e/3 - P1 Electron Energy Strip Log",true);
      
      saveRatioPlots_1e(h_1e_Data_P2_SeOld,3, 0,-1, 0.101,1.1, "1e/4 - P2 Electron Energy SeOld Log",true);
      saveRatioPlots_1e(h_1e_Data_P2_SeNew,4, 0,-1, 0.101,1.1, "1e/5 - P2 Electron Energy SeNew Log",true);
      saveRatioPlots_1e(h_1e_Data_P2_Strip,5, 0,-1, 0.101,1.1, "1e/6 - P2 Electron Energy Strip Log",true);
    }
  }
  
  // Draw Output - 1e1g
  if(Draw1e1gPlots){
    saveRatioPlots_1e1g(h_1e1g_Data_P1_SeOld,0, 0,-1, 0.1,1.1, "1e1g/1 - P1 Electron Energy SeOld");
    saveRatioPlots_1e1g(h_1e1g_Data_P1_SeNew,1, 0,-1, 0.1,1.1, "1e1g/2 - P1 Electron Energy SeNew");
    saveRatioPlots_1e1g(h_1e1g_Data_P1_Strip,2, 0,-1, 0.1,1.1, "1e1g/3 - P1 Electron Energy Strip");
    
    saveRatioPlots_1e1g(h_1e1g_Data_P2_SeOld,3, 0,-1, 0.1,1.1, "1e1g/4 - P2 Electron Energy SeOld");
    saveRatioPlots_1e1g(h_1e1g_Data_P2_SeNew,4, 0,-1, 0.1,1.1, "1e1g/5 - P2 Electron Energy SeNew");
    saveRatioPlots_1e1g(h_1e1g_Data_P2_Strip,5, 0,-1, 0.1,1.1, "1e1g/6 - P2 Electron Energy Strip");
    
    if(!DrawSummaryPlots){
      saveRatioPlots_1e1g(h_1e1g_Data_P1_SeOld,0, 0,-1, 0.101,5, "1e1g/1 - P1 Electron Energy SeOld Log",true);
      saveRatioPlots_1e1g(h_1e1g_Data_P1_SeNew,1, 0,-1, 0.101,5, "1e1g/2 - P1 Electron Energy SeNew Log",true);
      saveRatioPlots_1e1g(h_1e1g_Data_P1_Strip,2, 0,-1, 0.101,5, "1e1g/3 - P1 Electron Energy Strip Log",true);
      
      saveRatioPlots_1e1g(h_1e1g_Data_P2_SeOld,3, 0,-1, 0.101,5, "1e1g/4 - P2 Electron Energy SeOld Log",true);
      saveRatioPlots_1e1g(h_1e1g_Data_P2_SeNew,4, 0,-1, 0.101,5, "1e1g/5 - P2 Electron Energy SeNew Log",true);
      saveRatioPlots_1e1g(h_1e1g_Data_P2_Strip,5, 0,-1, 0.101,5, "1e1g/6 - P2 Electron Energy Strip Log",true);
    }
  }

  // Draw Output - 1e2g
  if(Draw1e2gPlots){
    saveRatioPlots_1e2g(h_1e2g_Data_SeOld,0, 0,-1, 0.1,1.1, "1e2g/1 - Electron Energy SeOld");
    saveRatioPlots_1e2g(h_1e2g_Data_SeNew,1, 0,-1, 0.1,1.1, "1e2g/2 - Electron Energy SeNew");
  }

  // Draw Output - 1e1a
  if(Draw1e1aPlots){
    if(!DrawSummaryPlots){
      saveRatioPlots_1e1a(h_1e1a_Data_P1_aOuteOut_Sector6, 0, 0,-1, 0.1,120, "1e1a/P1/1 - Sector6 - Alpha Out Electron Out");
      saveRatioPlots_1e1a(h_1e1a_Data_P1_aIneOut_Sector6,  1, 0,-1, 0.1,120, "1e1a/P1/2 - Sector6 - Alpha In Electron Out");
      saveRatioPlots_1e1a(h_1e1a_Data_P1_aOuteIn_Sector6,  2, 0,-1, 0.1,120, "1e1a/P1/3 - Sector6 - Alpha Out Electron In");
      saveRatioPlots_1e1a(h_1e1a_Data_P1_aIneIn_Sector6,   3, 0,-1, 0.1,120, "1e1a/P1/4 - Sector6 - Alpha In Electron In");

      saveRatioPlots_1e1a(h_1e1a_Data_P1_aOuteOut_Sector7, 4, 0,-1, 0.1,120, "1e1a/P1/5 - Sector7 - Alpha Out Electron Out");
      saveRatioPlots_1e1a(h_1e1a_Data_P1_aIneOut_Sector7,  5, 0,-1, 0.1,120, "1e1a/P1/6 - Sector7 - Alpha In Electron Out");
      saveRatioPlots_1e1a(h_1e1a_Data_P1_aOuteIn_Sector7,  6, 0,-1, 0.1,120, "1e1a/P1/7 - Sector7 - Alpha Out Electron In");
      saveRatioPlots_1e1a(h_1e1a_Data_P1_aIneIn_Sector7,   7, 0,-1, 0.1,120, "1e1a/P1/8 - Sector7 - Alpha In Electron In");

      saveRatioPlots_1e1a(h_1e1a_Data_P1_aOuteOut_Sector8, 8, 0,-1, 0.1, 30, "1e1a/P1/9 - Sector8 - Alpha Out Electron Out");
      saveRatioPlots_1e1a(h_1e1a_Data_P1_aIneOut_Sector8,  9, 0,-1, 0.1, 30, "1e1a/P1/10 - Sector8 - Alpha In Electron Out");
      saveRatioPlots_1e1a(h_1e1a_Data_P1_aOuteIn_Sector8, 10, 0,-1, 0.1, 30, "1e1a/P1/11 - Sector8 - Alpha Out Electron In");
      saveRatioPlots_1e1a(h_1e1a_Data_P1_aIneIn_Sector8,  11, 0,-1, 0.1, 30, "1e1a/P1/12 - Sector8 - Alpha In Electron In");
    }

    saveRatioPlots_1e1a(h_1e1a_Data_P1_AllEvents_Sector6, 12, 0,-1, 0.1, 300, "1e1a/P1/13 - Sector6 - All Events");
    saveRatioPlots_1e1a(h_1e1a_Data_P1_AllEvents_Sector7, 13, 0,-1, 0.1, 300, "1e1a/P1/14 - Sector7 - All Events");
    saveRatioPlots_1e1a(h_1e1a_Data_P1_AllEvents_Sector8, 14, 0,-1, 0.1, 100, "1e1a/P1/15 - Sector8 - All Events");

    if(!DrawSummaryPlots){
      saveRatioPlots_1e1a(h_1e1a_Data_P2_aOuteOut_Sector6, 0, 0,-1, 0.1,80, "1e1a/P2/1 - Sector6 - Alpha Out Electron Out");
      saveRatioPlots_1e1a(h_1e1a_Data_P2_aIneOut_Sector6,  1, 0,-1, 0.1,80, "1e1a/P2/2 - Sector6 - Alpha In Electron Out");
      saveRatioPlots_1e1a(h_1e1a_Data_P2_aOuteIn_Sector6,  2, 0,-1, 0.1,80, "1e1a/P2/3 - Sector6 - Alpha Out Electron In");
      saveRatioPlots_1e1a(h_1e1a_Data_P2_aIneIn_Sector6,   3, 0,-1, 0.1,80, "1e1a/P2/4 - Sector6 - Alpha In Electron In");
      
      saveRatioPlots_1e1a(h_1e1a_Data_P2_aOuteOut_Sector7, 4, 0,-1, 0.1,80, "1e1a/P2/5 - Sector7 - Alpha Out Electron Out");
      saveRatioPlots_1e1a(h_1e1a_Data_P2_aIneOut_Sector7,  5, 0,-1, 0.1,80, "1e1a/P2/6 - Sector7 - Alpha In Electron Out");
      saveRatioPlots_1e1a(h_1e1a_Data_P2_aOuteIn_Sector7,  6, 0,-1, 0.1,80, "1e1a/P2/7 - Sector7 - Alpha Out Electron In");
      saveRatioPlots_1e1a(h_1e1a_Data_P2_aIneIn_Sector7,   7, 0,-1, 0.1,80, "1e1a/P2/8 - Sector7 - Alpha In Electron In");
      
      saveRatioPlots_1e1a(h_1e1a_Data_P2_aOuteOut_Sector8, 8, 0,-1, 0.1, 30, "1e1a/P2/9 - Sector8 - Alpha Out Electron Out");
      saveRatioPlots_1e1a(h_1e1a_Data_P2_aIneOut_Sector8,  9, 0,-1, 0.1, 30, "1e1a/P2/10 - Sector8 - Alpha In Electron Out");
      saveRatioPlots_1e1a(h_1e1a_Data_P2_aOuteIn_Sector8, 10, 0,-1, 0.1, 30, "1e1a/P2/11 - Sector8 - Alpha Out Electron In");
      saveRatioPlots_1e1a(h_1e1a_Data_P2_aIneIn_Sector8,  11, 0,-1, 0.1, 30, "1e1a/P2/12 - Sector8 - Alpha In Electron In");
    }
    
    saveRatioPlots_1e1a(h_1e1a_Data_P2_AllEvents_Sector6, 12, 0,-1, 0.1, 200, "1e1a/P2/13 - Sector6 - All Events");
    saveRatioPlots_1e1a(h_1e1a_Data_P2_AllEvents_Sector7, 13, 0,-1, 0.1, 200, "1e1a/P2/14 - Sector7 - All Events");
    saveRatioPlots_1e1a(h_1e1a_Data_P2_AllEvents_Sector8, 14, 0,-1, 0.1,  80, "1e1a/P2/15 - Sector8 - All Events");
  }
  
  // Draw Output - OCE
  if(DrawOCEPlots){
    saveRatioPlots_OCE(h_OCE_Data_P1_Inner, 0, 0,-1, 0.1, 1.1, "OCE/1 - P1 Total Energy Inner");
    saveRatioPlots_OCE(h_OCE_Data_P1_Outer, 1, 0,-1, 0.1, 1.1, "OCE/2 - P1 Total Energy Outer");
    saveRatioPlots_OCE(h_OCE_Data_P1_Petal, 2, 0,-1, 0.1, 1.1, "OCE/3 - P1 Total Energy Petal");

    saveRatioPlots_OCE(h_OCE_Data_P2_Inner, 3, 0,-1, 0.1, 1.1, "OCE/4 - P2 Total Energy Inner");
    saveRatioPlots_OCE(h_OCE_Data_P2_Outer, 4, 0,-1, 0.1, 1.1, "OCE/5 - P2 Total Energy Outer");
    saveRatioPlots_OCE(h_OCE_Data_P2_Petal, 5, 0,-1, 0.1, 1.1, "OCE/6 - P2 Total Energy Petal");

    if(!DrawSummaryPlots){
      saveRatioPlots_OCE(h_OCE_Data_P1_Inner, 0, 0,-1, 0.3, 1.1, "OCE/1 - P1 Total Energy Inner Log", true);
      saveRatioPlots_OCE(h_OCE_Data_P1_Outer, 1, 0,-1, 0.3, 1.1, "OCE/2 - P1 Total Energy Outer Log", true);
      saveRatioPlots_OCE(h_OCE_Data_P1_Petal, 2, 0,-1, 0.3, 1.1, "OCE/3 - P1 Total Energy Petal Log", true);
      
      saveRatioPlots_OCE(h_OCE_Data_P2_Inner, 3, 0,-1, 0.3, 1.1, "OCE/4 - P2 Total Energy Inner Log", true);
      saveRatioPlots_OCE(h_OCE_Data_P2_Outer, 4, 0,-1, 0.3, 1.1, "OCE/5 - P2 Total Energy Outer Log", true);
      saveRatioPlots_OCE(h_OCE_Data_P2_Petal, 5, 0,-1, 0.3, 1.1, "OCE/6 - P2 Total Energy Petal Log", true);
    }
  }

  // Draw Output - ExtEG
  if(DrawExtEGPlots){
    saveRatioPlots_ExtEG(h_ExtEG_Data_P1_Inner, 0, 0,-1, 0.1, 1.1, "ExtEG/1 - P1 Total Energy Inner");
    saveRatioPlots_ExtEG(h_ExtEG_Data_P1_Outer, 1, 0,-1, 0.1, 1.1, "ExtEG/2 - P1 Total Energy Outer");
    saveRatioPlots_ExtEG(h_ExtEG_Data_P1_Petal, 2, 0,-1, 0.1, 1.1, "ExtEG/3 - P1 Total Energy Petal");

    saveRatioPlots_ExtEG(h_ExtEG_Data_P2_Inner, 3, 0,-1, 0.1, 1.1, "ExtEG/4 - P2 Total Energy Inner");
    saveRatioPlots_ExtEG(h_ExtEG_Data_P2_Outer, 4, 0,-1, 0.1, 1.1, "ExtEG/5 - P2 Total Energy Outer");
    saveRatioPlots_ExtEG(h_ExtEG_Data_P2_Petal, 5, 0,-1, 0.1, 1.1, "ExtEG/6 - P2 Total Energy Petal");

    if(!DrawSummaryPlots){
      saveRatioPlots_ExtEG(h_ExtEG_Data_P1_Inner, 0, 0,-1, 0.3, 1.1, "ExtEG/1 - P1 Total Energy Inner Log", true);
      saveRatioPlots_ExtEG(h_ExtEG_Data_P1_Outer, 1, 0,-1, 0.3, 1.1, "ExtEG/2 - P1 Total Energy Outer Log", true);
      saveRatioPlots_ExtEG(h_ExtEG_Data_P1_Petal, 2, 0,-1, 0.3, 1.1, "ExtEG/3 - P1 Total Energy Petal Log", true);
      
      saveRatioPlots_ExtEG(h_ExtEG_Data_P2_Inner, 3, 0,-1, 0.3, 1.1, "ExtEG/4 - P2 Total Energy Inner Log", true);
      saveRatioPlots_ExtEG(h_ExtEG_Data_P2_Outer, 4, 0,-1, 0.3, 1.1, "ExtEG/5 - P2 Total Energy Outer Log", true);
      saveRatioPlots_ExtEG(h_ExtEG_Data_P2_Petal, 5, 0,-1, 0.3, 1.1, "ExtEG/6 - P2 Total Energy Petal Log", true);
    }
  }

  // Draw Output - 2b2n
   if(Draw2b2nPlots){
     saveRatioPlots_2b2n(h_2b2n_Data_SeOld,0, 0,3.5, 0.1,1.1, "2b2n/1 - Total Energy SeOld");
     saveRatioPlots_2b2n(h_2b2n_Data_SeNew,1, 0,3.5, 0.1,1.1, "2b2n/1 - Total Energy SeNew");

     saveRatioPlots_2b2n(h_2b2n_SingleEnergy_Data_SeOld,2, 0,3.5, 0.1,1.1, "2b2n/2 - Single Energy SeOld");
     saveRatioPlots_2b2n(h_2b2n_SingleEnergy_Data_SeNew,3, 0,3.5, 0.1,1.1, "2b2n/2 - Single Energy SeNew");

     saveRatioPlots_2b2n(h_2b2n_MinEnergy_Data_SeOld,4, 0,2.5, 0.1,1.1, "2b2n/3 - Minimum Energy SeOld");
     saveRatioPlots_2b2n(h_2b2n_MinEnergy_Data_SeNew,5, 0,2.5, 0.1,1.1, "2b2n/3 - Minimum Energy SeNew");

     saveRatioPlots_2b2n(h_2b2n_MaxEnergy_Data_SeOld,6, 0,2.5, 0.1,1.1, "2b2n/4 - Maximum Energy SeOld");
     saveRatioPlots_2b2n(h_2b2n_MaxEnergy_Data_SeNew,7, 0,2.5, 0.1,1.1, "2b2n/4 - Maximum Energy SeNew");

     if(!DrawSummaryPlots){
       saveRatioPlots_2b2n(h_2b2n_Data_SeOld,0, 0,3.5, 0.3,100, "2b2n/1 - Total Energy SeOld Log",true);
       saveRatioPlots_2b2n(h_2b2n_Data_SeNew,1, 0,3.5, 0.3,100, "2b2n/1 - Total Energy SeNew Log",true);

       saveRatioPlots_2b2n(h_2b2n_SingleEnergy_Data_SeOld,2, 0,3.5, 0.3,100, "2b2n/2 - Single Energy SeOld Log",true);
       saveRatioPlots_2b2n(h_2b2n_SingleEnergy_Data_SeNew,3, 0,3.5, 0.3,100, "2b2n/2 - Single Energy SeNew Log",true);
       
       saveRatioPlots_2b2n(h_2b2n_MinEnergy_Data_SeOld,4, 0,2.5, 0.3,100, "2b2n/3 - Minimum Energy SeOld Log",true);
       saveRatioPlots_2b2n(h_2b2n_MinEnergy_Data_SeNew,5, 0,2.5, 0.3,100, "2b2n/3 - Minimum Energy SeNew Log",true);
       
       saveRatioPlots_2b2n(h_2b2n_MaxEnergy_Data_SeOld,6, 0,2.5, 0.3,100, "2b2n/4 - Maximum Energy SeOld Log",true);
       saveRatioPlots_2b2n(h_2b2n_MaxEnergy_Data_SeNew,7, 0,2.5, 0.3,100, "2b2n/4 - Maximum Energy SeNew Log",true);
     }
   }

  if(DrawCorrMatrix){
    TCanvas* c1= new TCanvas("c1","Correlation Matrix",200,10,1013,885);
    c1->SetRightMargin(0.14);
    //  c1->SetLeftMargin(0.14);
    c1->SetLeftMargin(0.21);
    c1->SetBottomMargin(0.21);
    string samples[44] = {"^{214}Bi SeNew","^{214}Bi SeOld","^{214}Bi Mylar","P1:P2 Ratio", "^{214}Bi SWire P2", "^{214}Bi SFoil In P2", "^{214}Bi SFoil Out P2", "^{208}Tl SWire P1", "^{208}Tl SWire P2", "^{208}Tl SeNew", "^{208}Tl SeOld", "^{40}K PMT", "^{40}K Steel Frame", "^{40}K Scint Inner", "^{40}K Scint Outer", "^{40}K Scint Petals", "^{214}Bi PMT", "^{214}Bi Fe Shield", "^{214}Bi Steel Frame",  "^{214}Bi SScin P2", "^{214}Bi LSM Air", "^{208}Tl PMT", "^{208}Tl Fe Shield", "^{208}Tl Steel Frame", "^{208}Tl LSM Air", "^{60}Co Mu Metal", "^{60}Co Steel Frame", "^{60}Co Cu Petals", "^{60}Co Cu Tower", "^{210}Bi SScin", "^{210}Bi SWire", "^{234m}Pa SScin", "1 MeV #gamma P1", "1 MeV #gamma P2", "Neutrons P1", "Neutrons P2", "^{210}Bi SeNew", "^{210}Bi SeOld", "^{210}Bi Strip", "^{234m}Pa SeNew","^{234m}Pa SeOld","^{40}K SeNew","^{40}K SeOld", "^{82}Se 2#nu#beta#beta"};

    TH2D* hCorrMatrix = new TH2D("hCorrMatrix","Correlation Matrix", 44, 0, 44, 44, 0, 44);
    for(int i = 0; i < 44; i++){
      for(int j = 0; j < 44; j++){
	hCorrMatrix->Fill(samples[i].c_str(),samples[j].c_str(),CovMatrix[i][j]/(sqrt(CovMatrix[i][i])*sqrt(CovMatrix[j][j])));
      }
    }
    hCorrMatrix->LabelsDeflate();
    hCorrMatrix->GetZaxis()->SetRangeUser(-1,1);
    hCorrMatrix->GetXaxis()->SetLabelSize(0.035);
    hCorrMatrix->GetYaxis()->SetLabelSize(0.035);
    hCorrMatrix->SetTitle("");
    hCorrMatrix->Draw("COLZ");
    c1->SetGrid();
    gStyle->SetGridStyle(0);
    hCorrMatrix->GetXaxis()->LabelsOption("v");
    c1->SaveAs("Images/png/Correlation Matrix.png");
    c1->SaveAs("Images/eps/Correlation Matrix.eps");
    c1->SaveAs("Images/gif/Correlation Matrix.gif");
  }

  return 0;
}


//  LocalWords:  DrawSummaryPlots
