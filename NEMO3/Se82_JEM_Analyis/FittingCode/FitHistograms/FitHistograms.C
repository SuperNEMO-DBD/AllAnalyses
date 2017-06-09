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
#include <TMath.h>
#include <TPaveText.h>
#include <fstream>
#include "../Machinery/addBackgrounds_1e.h"
#include "../Machinery/addBackgrounds_1e1g.h"
#include "../Machinery/addBackgrounds_1e2g.h"
#include "../Machinery/addBackgrounds_1e1a.h"
#include "../Machinery/addBackgrounds_ExtEG.h"
#include "../Machinery/addBackgrounds_OCE.h"
#include "../Machinery/addBackgrounds_2b2n.h"
#include "../Machinery/fitBackgrounds.h"
#include "../Machinery/ReadWriteActivities.h"

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

Int_t FitHistograms(){
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

  // First, check all data pointers are OK
  if(h_1e_Data_P1_SeOld==0)  {cout << "ERROR:h_1e_Data_P1_SeOld not found"   << endl; exit(0);}  
  if(h_1e_Data_P1_SeNew==0)  {cout << "ERROR:h_1e_Data_P1_SeNew not found"   << endl; exit(0);}
  if(h_1e_Data_P1_Strip==0)  {cout << "ERROR:h_1e_Data_P1_Strip not found"   << endl; exit(0);}
  if(h_1e_Data_P2_SeOld==0)  {cout << "ERROR:h_1e_Data_P2_SeOld not found"   << endl; exit(0);}
  if(h_1e_Data_P2_SeNew==0)  {cout << "ERROR:h_1e_Data_P2_SeNew not found"   << endl; exit(0);}
  if(h_1e_Data_P2_Strip==0)  {cout << "ERROR:h_1e_Data_P2_Strip not found"   << endl; exit(0);}
     			  		  			  
  if(h_1e1g_Data_P1_SeOld==0){cout << "ERROR:h_1e1g_Data_P1_SeOld not found"   << endl; exit(0);}
  if(h_1e1g_Data_P1_SeNew==0){cout << "ERROR:h_1e1g_Data_P1_SeNew not found"   << endl; exit(0);}
  if(h_1e1g_Data_P1_Strip==0){cout << "ERROR:h_1e1g_Data_P1_Strip not found"   << endl; exit(0);}
  if(h_1e1g_Data_P2_SeOld==0){cout << "ERROR:h_1e1g_Data_P2_SeOld not found"   << endl; exit(0);}
  if(h_1e1g_Data_P2_SeNew==0){cout << "ERROR:h_1e1g_Data_P2_SeNew not found"   << endl; exit(0);}
  if(h_1e1g_Data_P2_Strip==0){cout << "ERROR:h_1e1g_Data_P2_Strip not found"   << endl; exit(0);}

  if(h_1e2g_Data_SeOld==0)   {cout << "ERROR:h_1e2g_Data_SeOld not found"   << endl; exit(0);}
  if(h_1e2g_Data_SeNew==0)   {cout << "ERROR:h_1e2g_Data_SeNew not found"   << endl; exit(0);}

  if(h_1e1a_Data_P1_aOuteOut_Sector6==0) {cout << "ERROR: h_1e1a_Data_P1_aOuteOut_Sector6 not found"   << endl; exit(0);}
  if(h_1e1a_Data_P1_aIneOut_Sector6==0)  {cout << "ERROR: h_1e1a_Data_P1_aIneOut_Sector6 not found"   << endl; exit(0);}
  if(h_1e1a_Data_P1_aOuteIn_Sector6==0)  {cout << "ERROR: h_1e1a_Data_P1_aOuteIn_Sector6 not found"   << endl; exit(0);}
  if(h_1e1a_Data_P1_aIneIn_Sector6==0)   {cout << "ERROR: h_1e1a_Data_P1_aIneIn_Sector6 not found"   << endl; exit(0);}
  if(h_1e1a_Data_P1_aOuteOut_Sector7==0) {cout << "ERROR: h_1e1a_Data_P1_aOuteOut_Sector7 not found"   << endl; exit(0);}
  if(h_1e1a_Data_P1_aIneOut_Sector7==0)  {cout << "ERROR: h_1e1a_Data_P1_aIneOut_Sector7 not found"   << endl; exit(0);}
  if(h_1e1a_Data_P1_aOuteIn_Sector7==0)  {cout << "ERROR: h_1e1a_Data_P1_aOuteIn_Sector7 not found"   << endl; exit(0);}
  if(h_1e1a_Data_P1_aIneIn_Sector7==0)   {cout << "ERROR: h_1e1a_Data_P1_aIneIn_Sector7 not found"   << endl; exit(0);}
  if(h_1e1a_Data_P1_aOuteOut_Sector8==0) {cout << "ERROR: h_1e1a_Data_P1_aOuteOut_Sector8 not found"   << endl; exit(0);}
  if(h_1e1a_Data_P1_aIneOut_Sector8==0)  {cout << "ERROR: h_1e1a_Data_P1_aIneOut_Sector8 not found"   << endl; exit(0);}
  if(h_1e1a_Data_P1_aOuteIn_Sector8==0)  {cout << "ERROR: h_1e1a_Data_P1_aOuteIn_Sector8 not found"   << endl; exit(0);}
  if(h_1e1a_Data_P1_aIneIn_Sector8==0)   {cout << "ERROR: h_1e1a_Data_P1_aIneIn_Sector8 not found"   << endl; exit(0);}
  if(h_1e1a_Data_P1_AllEvents_Sector6==0){cout << "ERROR: h_1e1a_Data_P1_AllEvents_Sector6 not found"   << endl; exit(0);}
  if(h_1e1a_Data_P1_AllEvents_Sector7==0){cout << "ERROR: h_1e1a_Data_P1_AllEvents_Sector7 not found"   << endl; exit(0);}
  if(h_1e1a_Data_P1_AllEvents_Sector8==0){cout << "ERROR: h_1e1a_Data_P1_AllEvents_Sector8 not found"   << endl; exit(0);}
  if(h_1e1a_Data_P2_aOuteOut_Sector6==0) {cout << "ERROR: h_1e1a_Data_P2_aOuteOut_Sector6 not found"   << endl; exit(0);}
  if(h_1e1a_Data_P2_aIneOut_Sector6==0)  {cout << "ERROR: h_1e1a_Data_P2_aIneOut_Sector6 not found"   << endl; exit(0);}
  if(h_1e1a_Data_P2_aOuteIn_Sector6==0)  {cout << "ERROR: h_1e1a_Data_P2_aOuteIn_Sector6 not found"   << endl; exit(0);}
  if(h_1e1a_Data_P2_aIneIn_Sector6==0)   {cout << "ERROR: h_1e1a_Data_P2_aIneIn_Sector6 not found"   << endl; exit(0);}
  if(h_1e1a_Data_P2_aOuteOut_Sector7==0) {cout << "ERROR: h_1e1a_Data_P2_aOuteOut_Sector7 not found"   << endl; exit(0);}
  if(h_1e1a_Data_P2_aIneOut_Sector7==0)  {cout << "ERROR: h_1e1a_Data_P2_aIneOut_Sector7 not found"   << endl; exit(0);}
  if(h_1e1a_Data_P2_aOuteIn_Sector7==0)  {cout << "ERROR: h_1e1a_Data_P2_aOuteIn_Sector7 not found"   << endl; exit(0);}
  if(h_1e1a_Data_P2_aIneIn_Sector7==0)   {cout << "ERROR: h_1e1a_Data_P2_aIneIn_Sector7 not found"   << endl; exit(0);}
  if(h_1e1a_Data_P2_aOuteOut_Sector8==0) {cout << "ERROR: h_1e1a_Data_P2_aOuteOut_Sector8 not found"   << endl; exit(0);}
  if(h_1e1a_Data_P2_aIneOut_Sector8==0)  {cout << "ERROR: h_1e1a_Data_P2_aIneOut_Sector8 not found"   << endl; exit(0);}
  if(h_1e1a_Data_P2_aOuteIn_Sector8==0)  {cout << "ERROR: h_1e1a_Data_P2_aOuteIn_Sector8 not found"   << endl; exit(0);}
  if(h_1e1a_Data_P2_aIneIn_Sector8==0)   {cout << "ERROR: h_1e1a_Data_P2_aIneIn_Sector8 not found"   << endl; exit(0);}
  if(h_1e1a_Data_P2_AllEvents_Sector6==0){cout << "ERROR: h_1e1a_Data_P2_AllEvents_Sector6 not found"   << endl; exit(0);}
  if(h_1e1a_Data_P2_AllEvents_Sector7==0){cout << "ERROR: h_1e1a_Data_P2_AllEvents_Sector7 not found"   << endl; exit(0);}
  if(h_1e1a_Data_P2_AllEvents_Sector8==0){cout << "ERROR: h_1e1a_Data_P2_AllEvents_Sector8 not found"   << endl; exit(0);}

  if(h_OCE_Data_P1_Inner==0) {cout << "ERROR:h_OCE_Data_P1_Inner not found"   << endl; exit(0);}
  if(h_OCE_Data_P1_Outer==0) {cout << "ERROR:h_OCE_Data_P1_Outer not found"   << endl; exit(0);}
  if(h_OCE_Data_P1_Petal==0) {cout << "ERROR:h_OCE_Data_P1_Petal not found"   << endl; exit(0);}
  if(h_OCE_Data_P2_Inner==0) {cout << "ERROR:h_OCE_Data_P2_Inner not found"   << endl; exit(0);}
  if(h_OCE_Data_P2_Outer==0) {cout << "ERROR:h_OCE_Data_P2_Outer not found"   << endl; exit(0);}
  if(h_OCE_Data_P2_Petal==0) {cout << "ERROR:h_OCE_Data_P2_Petal not found"   << endl; exit(0);}

  if(h_ExtEG_Data_P1_Inner==0) {cout << "ERROR:h_ExtEG_Data_P1_Inner not found"   << endl; exit(0);}
  if(h_ExtEG_Data_P1_Outer==0) {cout << "ERROR:h_ExtEG_Data_P1_Outer not found"   << endl; exit(0);}
  if(h_ExtEG_Data_P1_Petal==0) {cout << "ERROR:h_ExtEG_Data_P1_Petal not found"   << endl; exit(0);}
  if(h_ExtEG_Data_P2_Inner==0) {cout << "ERROR:h_ExtEG_Data_P2_Inner not found"   << endl; exit(0);}
  if(h_ExtEG_Data_P2_Outer==0) {cout << "ERROR:h_ExtEG_Data_P2_Outer not found"   << endl; exit(0);}
  if(h_ExtEG_Data_P2_Petal==0) {cout << "ERROR:h_ExtEG_Data_P2_Petal not found"   << endl; exit(0);}

  if(h_2b2n_Data_SeOld==0) {cout << "ERROR:h_2b2n_Data_SeOld not found"   << endl; exit(0);}
  if(h_2b2n_Data_SeNew==0) {cout << "ERROR:h_2b2n_Data_SeNew not found"   << endl; exit(0);}
  if(h_2b2n_SingleEnergy_Data_SeOld==0) {cout << "ERROR:h_2b2n_SingleEnergy_Data_SeOld not found"   << endl; exit(0);}
  if(h_2b2n_SingleEnergy_Data_SeNew==0) {cout << "ERROR:h_2b2n_SingleEnergy_Data_SeNew not found"   << endl; exit(0);}
  if(h_2b2n_MinEnergy_Data_SeOld==0) {cout << "ERROR:h_2b2n_MinEnergy_Data_SeOld not found"   << endl; exit(0);}
  if(h_2b2n_MinEnergy_Data_SeNew==0) {cout << "ERROR:h_2b2n_MinEnergy_Data_SeNew not found"   << endl; exit(0);}
  if(h_2b2n_MaxEnergy_Data_SeOld==0) {cout << "ERROR:h_2b2n_MaxEnergy_Data_SeOld not found"   << endl; exit(0);}
  if(h_2b2n_MaxEnergy_Data_SeNew==0) {cout << "ERROR:h_2b2n_MaxEnergy_Data_SeNew not found"   << endl; exit(0);}

  // Set starting activities - External Backgrounds
  Double_t Act_PMT_K40          = 1078;
  Double_t Act_PMT_Bi214        = 324;
  Double_t Act_PMT_Tl208        = 27;
  Double_t Act_PMT_Ac228        = 72.7;
  Double_t Act_MuMetal_Co60     = 14.6;
  Double_t Act_SteelFrame_K40   = 100;
  Double_t Act_SteelFrame_Bi214 = 9.1;
  Double_t Act_SteelFrame_Tl208 = 3.1;
  Double_t Act_SteelFrame_Ac228 = 8.54;
  Double_t Act_SteelFrame_Co60  = 6.09;
  Double_t Act_CuPetals_Co60    = 47.6;
  Double_t Act_CuTower_Co60     = 18.4;
  Double_t Act_FeShield_Bi214   = 7360;
  Double_t Act_FeShield_Tl208   = 484;
  Double_t Act_FeShield_Ac228   = 1350;
  Double_t Act_ScintInn_K40     = 7.59;
  Double_t Act_ScintOut_K40     = 12.53;
  Double_t Act_ScintPet_K40     = 1.39;
  Double_t Act_SScin_Pa234m     = 2.4;
  Double_t Act_MuMetal_g1000_P1 = 100;
  Double_t Act_MuMetal_g1000_P2 = 50;
  Double_t Act_Neutrons_P1      = 1;  //These are really scaling factors of number of events
  Double_t Act_Neutrons_P2      = 1;  //These are really scaling factors of number of events

  // Set starting activities - Radon Backgrounds
  Double_t Act_SWire_Bi214_P2     = 0.1934;
  Double_t Act_SWire_Bi214_P1     = Act_SWire_Bi214_P2; // Scaled by 5.5 when adding backgrounds
  Double_t Act_SWire_Tl208_P2     = 2.9e-3;
  Double_t Act_SFoil_Bi214_P2_In  = 3e-3/2.0;
  Double_t Act_SFoil_Bi214_P2_Out = 3e-3/2.0;
  Double_t Act_SFoil_Bi214_P1_In  = Act_SFoil_Bi214_P2_In;   // Scaled by 5.5 when adding backgrounds
  Double_t Act_SFoil_Bi214_P1_Out = Act_SFoil_Bi214_P2_Out;  // Scaled by 5.5 when adding backgrounds
  Double_t Act_SWire_Tl208_P1     = 3.5e-3;
  Double_t Act_SWire_Bi210        = 10.2092;
  Double_t Act_SFoil_SeNew_Bi210  = 160e-3;
  Double_t Act_SFoil_SeOld_Bi210  = 160e-3;
  Double_t Act_SFoil_Strip_Bi210  = 160e-3;
  Double_t Act_SScin_Bi210        = (28.6*15.19 + 34.6*34.94 + 27.9*9.68)/59.81;
  Double_t Act_SScin_Bi214_P2     = (0.291*15.19 + 0.431*34.94 + 0.418*9.68)/59.81;
  Double_t Act_SScin_Bi214_P1     = Act_SScin_Bi214_P2;   // Scaled by 5.5 when adding backgrounds
  Double_t Act_Air_Bi214_P1       = 566.5;
  Double_t Act_Air_Tl208_P1       = 566.5/50.0;

  // Set starting activities - Internal Backgrounds
  Double_t Act_SeNew_Bi214 = 0.4e-3*0.6086;
  Double_t Act_SeOld_Bi214 = 1.0e-3*0.5185;
  Double_t Act_Mylar_Bi214 = 1.7e-3*0.88768; // Need to fix from HPGe measurement
  Double_t Act_SeNew_Tl208  = 0.44e-3*0.6086;
  Double_t Act_SeOld_Tl208  = 0.34e-3*0.5185;
  Double_t Act_SeNew_Pa234m = 16e-3/(1+(0.5185/0.6086)*(33./102.));             // Vlad's Note 16 mBq (TDR < 18 mBq/kg).  Sasha - SeOld = < 33, SeNew = 102
  Double_t Act_SeOld_Pa234m = 16e-3/(1+(0.6086/0.5185)*(102./33.));             // Vlad's Note 16 mBq (TDR < 18 mBq/kg).  Sasha - SeOld = < 33, SeNew = 102
  Double_t Act_SeNew_K40    = (55.0e-3*1.1271)/(1+(0.5185/0.6086)*(133./80.));  // TDR = 55 +/- 5 mBq/kg (p149).  Sasha - SeOld = 133, SeNew = 80.
  Double_t Act_SeOld_K40    = (55.0e-3*1.1271)/(1+(0.6086/0.5185)*(80./133.));  // TDR = 55 +/- 5 mBq/kg (p149).  Sasha - SeOld = 133, SeNew = 80.

  // Set starting activities - Signal
  //2b2n - halflife = 9.6 x 10^19 years
  Double_t Act_2b2n = log(2)/(9.6*86400.0*365.25)*6.022e4*932.4/82.0;

  // Set denominators - External Backgrounds
  Double_t Denom_PMT_K40          = 320000000000;
  Double_t Denom_PMT_Bi214        = 240000000000;
  Double_t Denom_PMT_Tl208        = 67900000000;
  Double_t Denom_PMT_Ac228        = 58000000000;
  Double_t Denom_MuMetal_Co60     = 24000000000;
  Double_t Denom_SteelFrame_K40   = 60000000000;
  Double_t Denom_SteelFrame_Bi214 = 15000000000;
  Double_t Denom_SteelFrame_Tl208 = 3000000000;
  Double_t Denom_SteelFrame_Ac228 = 7400000000;
  Double_t Denom_SteelFrame_Co60  = 8000000000;
  Double_t Denom_CuPetals_Co60    = 3200000000;
  Double_t Denom_CuTower_Co60     = 8000000000;
  Double_t Denom_FeShield_Bi214   = 4000000000000;
  Double_t Denom_FeShield_Tl208   = 200000000000;
  Double_t Denom_FeShield_Ac228   = 260000000000;
  Double_t Denom_ScintInn_K40     = 6000000000;
  Double_t Denom_ScintOut_K40     = 10000000000;
  Double_t Denom_ScintPet_K40     = 2000000000;
  Double_t Denom_SScin_Pa234m     = 300000000;
  Double_t Denom_MuMetal_g1000    = 30000000000;
  Double_t Denom_Neutrons         = AccptRunTime;  // So that activity just becomes scaling factor

  // Set denominators - Radon Backgrounds
  Double_t Denom_SWire_Bi214 = 1449500000;
  Double_t Denom_SWire_Pb214 = 1600000000;
  Double_t Denom_SWire_Bi210 = 8000000000;
  Double_t Denom_SWire_Tl208 = 100000000;
  Double_t Denom_SFoil_Bi214 = 109500000./2.;
  Double_t Denom_SFoil_Pb214 = 100000000./2.;
  Double_t Denom_SFoil_Bi210 = 100000000;
  Double_t Denom_SScin_Bi214 = 800000000;
  Double_t Denom_SScin_Pb214 = 1000000000;
  Double_t Denom_SScin_Bi210 = 2950000000;
  Double_t Denom_Air_Bi214   = 71000000000.*AccptRunTime/33401222.; // Scale by (P1+P2)/P1 as I only put them in P1
  Double_t Denom_Air_Pb214   = 20000000000.*AccptRunTime/33401222.; // Scale by (P1+P2)/P1 as I only put them in P1
  Double_t Denom_Air_Tl208   = 1000000000.*AccptRunTime/33401222.; // Scale by (P1+P2)/P1 as I only put them in P1

  // Set denominators - Internal Backgrounds
  Double_t Denom_SeNew_Bi214  = 100000000;
  Double_t Denom_SeOld_Bi214  = 100000000;
  Double_t Denom_Mylar_Bi214  = 100000000;
  Double_t Denom_SeNew_Pb214  = 20000000;
  Double_t Denom_SeOld_Pb214  = 20000000;
  Double_t Denom_Mylar_Pb214  = 100000000;
  Double_t Denom_SeNew_Tl208  = 100000000;
  Double_t Denom_SeOld_Tl208  = 100000000;
  Double_t Denom_SeNew_Bi212  = 5000000;
  Double_t Denom_SeOld_Bi212  = 5000000;
  Double_t Denom_SeNew_Ac228  = 5000000;
  Double_t Denom_SeOld_Ac228  = 5000000;
  Double_t Denom_SeNew_Pa234m = 50000000;
  Double_t Denom_SeOld_Pa234m = 50000000;
  Double_t Denom_SeNew_K40    = 100000000;
  Double_t Denom_SeOld_K40    = 100000000;

  // Set denominators - Signal
  Double_t Denom_2b2n = 100000000;

  // Make arrays to pass other functions - External Backgrounds
  Double_t Activities_Ext[23]     = {Act_PMT_K40, Act_PMT_Bi214, Act_PMT_Tl208, Act_PMT_Ac228,
				     Act_MuMetal_Co60, Act_SteelFrame_K40, Act_SteelFrame_Bi214, Act_SteelFrame_Tl208,
				     Act_SteelFrame_Ac228, Act_SteelFrame_Co60, Act_CuPetals_Co60, Act_CuTower_Co60,
				     Act_FeShield_Bi214, Act_FeShield_Tl208, Act_FeShield_Ac228, Act_ScintInn_K40,
				     Act_ScintOut_K40, Act_ScintPet_K40, Act_SScin_Pa234m,
				     Act_MuMetal_g1000_P1, Act_MuMetal_g1000_P2, Act_Neutrons_P1, Act_Neutrons_P2};
  Double_t Activities_Ext_Err[23] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  Double_t Denominators_Ext[21]   = {Denom_PMT_K40, Denom_PMT_Bi214, Denom_PMT_Tl208, Denom_PMT_Ac228,
				     Denom_MuMetal_Co60, Denom_SteelFrame_K40, Denom_SteelFrame_Bi214, Denom_SteelFrame_Tl208,
				     Denom_SteelFrame_Ac228, Denom_SteelFrame_Co60, Denom_CuPetals_Co60, Denom_CuTower_Co60,
				     Denom_FeShield_Bi214, Denom_FeShield_Tl208, Denom_FeShield_Ac228, Denom_ScintInn_K40, 
				     Denom_ScintOut_K40, Denom_ScintPet_K40, Denom_SScin_Pa234m, Denom_MuMetal_g1000, Denom_Neutrons};

  // Make arrays to pass other functions - Radon Backgrounds
  Double_t Activities_Rad[17]     = {Act_SWire_Bi214_P1, Act_SWire_Tl208_P1, Act_SFoil_Bi214_P1_In, Act_SFoil_Bi214_P1_Out,
				     Act_SWire_Bi214_P2, Act_SWire_Tl208_P2, Act_SFoil_Bi214_P2_In, Act_SFoil_Bi214_P2_Out,
				     Act_SWire_Bi210, Act_SFoil_SeNew_Bi210, Act_SFoil_SeOld_Bi210, Act_SFoil_Strip_Bi210,
				     Act_SScin_Bi210, Act_SScin_Bi214_P1, Act_SScin_Bi214_P2,  Act_Air_Bi214_P1, Act_Air_Tl208_P1};
  Double_t Activities_Rad_Err[17] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  Double_t Denominators_Rad[13]   = {Denom_SWire_Bi214, Denom_SWire_Pb214, Denom_SWire_Bi210, Denom_SWire_Tl208,
				     Denom_SFoil_Bi214, Denom_SFoil_Pb214, Denom_SFoil_Bi210, Denom_SScin_Bi214,
				     Denom_SScin_Pb214, Denom_SScin_Bi210, Denom_Air_Bi214  , Denom_Air_Pb214, Denom_Air_Tl208};

  // Make arrays to pass other functions - Internal Backgrounds
  Double_t Activities_Int[9]     =  {Act_SeNew_Bi214, Act_SeOld_Bi214, Act_Mylar_Bi214,
				     Act_SeNew_Tl208, Act_SeOld_Tl208, Act_SeNew_Pa234m,
				     Act_SeOld_Pa234m, Act_SeNew_K40,   Act_SeOld_K40};
  Double_t Activities_Int_Err[9] = {0,0,0,0,0,0,0};
  Double_t Denominators_Int[16]   = {Denom_SeNew_Bi214, Denom_SeOld_Bi214, Denom_Mylar_Bi214, Denom_SeNew_Pb214,
				     Denom_SeOld_Pb214, Denom_Mylar_Pb214, Denom_SeNew_Tl208, Denom_SeOld_Tl208,
				     Denom_SeNew_Bi212, Denom_SeOld_Bi212, Denom_SeNew_Ac228, Denom_SeOld_Ac228,
				     Denom_SeNew_Pa234m,Denom_SeOld_Pa234m,Denom_SeNew_K40  , Denom_SeOld_K40};

  // Make arrays to pass other functions - Signal
  Double_t Activities_Sig[1]     = {Act_2b2n};
  Double_t Activities_Sig_Err[1] = {0};
  Double_t Denominators_Sig[1]   = {Denom_2b2n};

  // Make array of activity adjustment parameters first
  Double_t AdjustActs[44]     = {3.0, 1.5, 1.0, 6.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
				 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
				 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
				 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 4.5, 4.3,41.0, 1.0,
				 1.0, 1.0, 1.0, 1.0};
  Double_t AdjustActs_Err[44] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  Double_t CovMatrix[44][44];

  // First call function to fill MC samples to be used when fitting.
  addBackgrounds_1e   (Activities_Ext, Activities_Ext_Err, Denominators_Ext, Activities_Rad, Activities_Rad_Err, Denominators_Rad, Activities_Int, Activities_Int_Err, Denominators_Int, Activities_Sig, Activities_Sig_Err, Denominators_Sig, AdjustActs, AdjustActs_Err);
  addBackgrounds_1e1g (Activities_Ext, Activities_Ext_Err, Denominators_Ext, Activities_Rad, Activities_Rad_Err, Denominators_Rad, Activities_Int, Activities_Int_Err, Denominators_Int, Activities_Sig, Activities_Sig_Err, Denominators_Sig, AdjustActs, AdjustActs_Err);
  addBackgrounds_1e2g (Activities_Ext, Activities_Ext_Err, Denominators_Ext, Activities_Rad, Activities_Rad_Err, Denominators_Rad, Activities_Int, Activities_Int_Err, Denominators_Int, Activities_Sig, Activities_Sig_Err, Denominators_Sig, AdjustActs, AdjustActs_Err);
  addBackgrounds_1e1a (Activities_Ext, Activities_Ext_Err, Denominators_Ext, Activities_Rad, Activities_Rad_Err, Denominators_Rad, Activities_Int, Activities_Int_Err, Denominators_Int, Activities_Sig, Activities_Sig_Err, Denominators_Sig, AdjustActs, AdjustActs_Err);
  addBackgrounds_OCE  (Activities_Ext, Activities_Ext_Err, Denominators_Ext, Activities_Rad, Activities_Rad_Err, Denominators_Rad, Activities_Int, Activities_Int_Err, Denominators_Int, Activities_Sig, Activities_Sig_Err, Denominators_Sig, AdjustActs, AdjustActs_Err);
  addBackgrounds_ExtEG(Activities_Ext, Activities_Ext_Err, Denominators_Ext, Activities_Rad, Activities_Rad_Err, Denominators_Rad, Activities_Int, Activities_Int_Err, Denominators_Int, Activities_Sig, Activities_Sig_Err, Denominators_Sig, AdjustActs, AdjustActs_Err);
  addBackgrounds_2b2n (Activities_Ext, Activities_Ext_Err, Denominators_Ext, Activities_Rad, Activities_Rad_Err, Denominators_Rad, Activities_Int, Activities_Int_Err, Denominators_Int, Activities_Sig, Activities_Sig_Err, Denominators_Sig, AdjustActs, AdjustActs_Err, CovMatrix);

  // Fit Samples
  fitBackgrounds(AdjustActs,AdjustActs_Err,CovMatrix);

  // Adjust Activities Based on Fit

  // 1e1a

  // Parameters 0, 1, 2 (Bi214 - SeNew, SeOld, Mylar)
  for(int i = 0; i < 3; i++){
     Activities_Int[i] *= AdjustActs[i];
     Activities_Int_Err[i] = Activities_Int[i] * AdjustActs_Err[i]/AdjustActs[i];
  }

  // Parameter 3, 4 - SWire P1, P2
  Activities_Rad[0] *= AdjustActs[3]*AdjustActs[4];
  Activities_Rad_Err[0] = Activities_Rad[0] * AdjustActs_Err[4]/AdjustActs[4];
  Activities_Rad[4] *= AdjustActs[4];
  Activities_Rad_Err[4] = Activities_Rad[4] * AdjustActs_Err[4]/AdjustActs[4];

  // Parameters 3, 5, 6 - SFoil P1, P2
  Activities_Rad[2] *= AdjustActs[3]*AdjustActs[5];
  Activities_Rad_Err[2] = Activities_Rad[2] * AdjustActs_Err[5]/AdjustActs[5];
  Activities_Rad[3] *= AdjustActs[3]*AdjustActs[6];
  Activities_Rad_Err[3] = Activities_Rad[3] * AdjustActs_Err[6]/AdjustActs[6];
  Activities_Rad[6] *= AdjustActs[5];
  Activities_Rad_Err[6] = Activities_Rad[6] * AdjustActs_Err[5]/AdjustActs[5];
  Activities_Rad[7] *= AdjustActs[6];
  Activities_Rad_Err[7] = Activities_Rad[7] * AdjustActs_Err[6]/AdjustActs[6];

  // 1e2g

  // Parameters 7, 8 - Tl-208 SWire P1 & P2
  Activities_Rad[1] *= AdjustActs[7];
  Activities_Rad_Err[1] = Activities_Rad[1] * AdjustActs_Err[7]/AdjustActs[7];
  Activities_Rad[5] *= AdjustActs[8];
  Activities_Rad_Err[5] = Activities_Rad[5] * AdjustActs_Err[8]/AdjustActs[8];

  // Parameters 9, 10 - Tl-208 SeNew, SeOld
  Activities_Int[3] *= AdjustActs[9];
  Activities_Int_Err[3] = Activities_Int[3] * AdjustActs_Err[9]/AdjustActs[9];
  Activities_Int[4] *= AdjustActs[10];
  Activities_Int_Err[4] = Activities_Int[4] * AdjustActs_Err[10]/AdjustActs[10];

  // Externals/1e1g

  // Parameters 11-15 - K-40 Externals
  Activities_Ext[0] *= AdjustActs[11];
  Activities_Ext_Err[0] = Activities_Ext[0] * AdjustActs_Err[11]/AdjustActs[11];
  Activities_Ext[5] *= AdjustActs[12];
  Activities_Ext_Err[5] = Activities_Ext[5] * AdjustActs_Err[12]/AdjustActs[12];
  for(int i = 15; i < 18; i++){
    Activities_Ext[i] *= AdjustActs[i-2];
    Activities_Ext_Err[i] = Activities_Ext[i] * AdjustActs_Err[i-2]/AdjustActs[i-2];
  }

  // Parameters 16-20 - Bi-214 Externals (including SScin and LSM Air)
  Activities_Ext[1] *= AdjustActs[16];
  Activities_Ext_Err[1] = Activities_Ext[1] * AdjustActs_Err[16]/AdjustActs[16];
  Activities_Ext[12] *= AdjustActs[17];
  Activities_Ext_Err[12] = Activities_Ext[12] * AdjustActs_Err[17]/AdjustActs[17];
  Activities_Ext[6] *= AdjustActs[18];
  Activities_Ext_Err[6] = Activities_Ext[6] * AdjustActs_Err[18]/AdjustActs[18];

  cout << "AdjuctActs[3] = " << AdjustActs[3] << " AdjustActs[19] = " << AdjustActs[19] << endl;

  Activities_Rad[13] *= AdjustActs[3]*AdjustActs[19];
  Activities_Rad_Err[13] = Activities_Rad[13] * AdjustActs_Err[19]/AdjustActs[19];
  Activities_Rad[14] *= AdjustActs[19];
  Activities_Rad_Err[14] = Activities_Rad[14] * AdjustActs_Err[19]/AdjustActs[19];
  Activities_Rad[15] *= AdjustActs[20];
  Activities_Rad_Err[15] = Activities_Rad[15] * AdjustActs_Err[20]/AdjustActs[20];
  cout << "SScin P1 = " << Activities_Rad[13] << " SScin P2 = " << Activities_Rad[14] << endl;
  // Parameters 21-24 - Tl-208 Externals/LSM Air (and Ac228)
  for(int i = 2; i < 4; i++){
    Activities_Ext[i] *= AdjustActs[21];
    Activities_Ext_Err[i] = Activities_Ext[i] * AdjustActs_Err[21]/AdjustActs[21];
  }
  for(int i = 13; i < 15; i++){
    Activities_Ext[i] *= AdjustActs[22];
    Activities_Ext_Err[i] = Activities_Ext[i] * AdjustActs_Err[22]/AdjustActs[22];
  }
  for(int i = 7; i < 9; i++){
    Activities_Ext[i] *= AdjustActs[23];
    Activities_Ext_Err[i] = Activities_Ext[i] * AdjustActs_Err[23]/AdjustActs[23];
  }
  Activities_Rad[16] *= AdjustActs[24];
  Activities_Rad_Err[16] = Activities_Rad[16] * AdjustActs_Err[24]/AdjustActs[24];

  // Parameters 25-28 - Co-60 Externals
  Activities_Ext[4] *= AdjustActs[25];
  Activities_Ext_Err[4] = Activities_Ext[4] * AdjustActs_Err[25]/AdjustActs[25];
  for(int i = 9; i < 12; i++){
    Activities_Ext[i] *= AdjustActs[17+i];
    Activities_Ext_Err[i] = Activities_Ext[i] * AdjustActs_Err[17+i]/AdjustActs[17+i];
  }

  // Parameter 29 - Bi-210 SScin
  Activities_Rad[12] *= AdjustActs[29];
  Activities_Rad_Err[12] = Activities_Rad[12] * AdjustActs_Err[29]/AdjustActs[29];

  // Parameter 30 - Bi-210 SWire
  Activities_Rad[8] *= AdjustActs[30];
  Activities_Rad_Err[8] = Activities_Rad[8] * AdjustActs_Err[30]/AdjustActs[30];

  // Parameter 31 - Pa-234m SScin
  Activities_Ext[18] *= AdjustActs[31];
  Activities_Ext_Err[18] = Activities_Ext[18] * AdjustActs_Err[31]/AdjustActs[31];

  // Parameters 32-33 - MuMetal g1000
  Activities_Ext[19] *= AdjustActs[32];
  Activities_Ext_Err[19] = Activities_Ext[19] * AdjustActs_Err[32]/AdjustActs[32];
  Activities_Ext[20] *= AdjustActs[33];
  Activities_Ext_Err[20] = Activities_Ext[20] * AdjustActs_Err[33]/AdjustActs[33];

  // Parameters 34-35 - Neutrons P1 & P2
  Activities_Ext[21] *= AdjustActs[34];
  Activities_Ext_Err[21] = Activities_Ext[21] * AdjustActs_Err[34]/AdjustActs[34];
  Activities_Ext[22] *= AdjustActs[35];
  Activities_Ext_Err[22] = Activities_Ext[22] * AdjustActs_Err[35]/AdjustActs[35];

  // 1e

  // Parameter 36 - Bi210 SFoil SeNew
  Activities_Rad[9] *= AdjustActs[36];
  Activities_Rad_Err[9] = Activities_Rad[9] * AdjustActs_Err[36]/AdjustActs[36];

  // Parameter 37 - Bi210 SFoil SeOld
  Activities_Rad[10] *= AdjustActs[37];
  Activities_Rad_Err[10] = Activities_Rad[10] * AdjustActs_Err[37]/AdjustActs[37];

  // Parameter 38 - Bi210 SFoil Strip
  Activities_Rad[11] *= AdjustActs[38];
  Activities_Rad_Err[11] = Activities_Rad[11] * AdjustActs_Err[38]/AdjustActs[38];

  // Parameter 39 - Pa234m SeNew
  Activities_Int[5] *= AdjustActs[39];
  Activities_Int_Err[5] = Activities_Int[5] * AdjustActs_Err[39]/AdjustActs[39];

  // Parameter 40 - Pa234m SeOld
  Activities_Int[6] *= AdjustActs[40];
  Activities_Int_Err[6] = Activities_Int[6] * AdjustActs_Err[40]/AdjustActs[40];

  // Parameter 41 - K40 SeNew
  Activities_Int[7] *= AdjustActs[41];
  Activities_Int_Err[7] = Activities_Int[7] * AdjustActs_Err[41]/AdjustActs[41];

  // Parameter 42 - K40 SeOld
  Activities_Int[8] *= AdjustActs[42];
  Activities_Int_Err[8] = Activities_Int[8] * AdjustActs_Err[42]/AdjustActs[42];

  // Signal

  // Parameter 43 - Se 2b2n (SeNew & SeOld)
  Activities_Sig[0] *= AdjustActs[43];
  Activities_Sig_Err[0] = Activities_Sig[0] * AdjustActs_Err[43]/AdjustActs[43];

  // Re-call functions to fill MC samples
  addBackgrounds_1e   (Activities_Ext, Activities_Ext_Err, Denominators_Ext, Activities_Rad, Activities_Rad_Err, Denominators_Rad, Activities_Int, Activities_Int_Err, Denominators_Int, Activities_Sig, Activities_Sig_Err, Denominators_Sig, AdjustActs, AdjustActs_Err);
  addBackgrounds_1e1g (Activities_Ext, Activities_Ext_Err, Denominators_Ext, Activities_Rad, Activities_Rad_Err, Denominators_Rad, Activities_Int, Activities_Int_Err, Denominators_Int, Activities_Sig, Activities_Sig_Err, Denominators_Sig, AdjustActs, AdjustActs_Err);
  addBackgrounds_1e2g (Activities_Ext, Activities_Ext_Err, Denominators_Ext, Activities_Rad, Activities_Rad_Err, Denominators_Rad, Activities_Int, Activities_Int_Err, Denominators_Int, Activities_Sig, Activities_Sig_Err, Denominators_Sig, AdjustActs, AdjustActs_Err);
  addBackgrounds_1e1a (Activities_Ext, Activities_Ext_Err, Denominators_Ext, Activities_Rad, Activities_Rad_Err, Denominators_Rad, Activities_Int, Activities_Int_Err, Denominators_Int, Activities_Sig, Activities_Sig_Err, Denominators_Sig, AdjustActs, AdjustActs_Err);
  addBackgrounds_OCE  (Activities_Ext, Activities_Ext_Err, Denominators_Ext, Activities_Rad, Activities_Rad_Err, Denominators_Rad, Activities_Int, Activities_Int_Err, Denominators_Int, Activities_Sig, Activities_Sig_Err, Denominators_Sig, AdjustActs, AdjustActs_Err);
  addBackgrounds_ExtEG(Activities_Ext, Activities_Ext_Err, Denominators_Ext, Activities_Rad, Activities_Rad_Err, Denominators_Rad, Activities_Int, Activities_Int_Err, Denominators_Int, Activities_Sig, Activities_Sig_Err, Denominators_Sig, AdjustActs, AdjustActs_Err);
  addBackgrounds_2b2n (Activities_Ext, Activities_Ext_Err, Denominators_Ext, Activities_Rad, Activities_Rad_Err, Denominators_Rad, Activities_Int, Activities_Int_Err, Denominators_Int, Activities_Sig, Activities_Sig_Err, Denominators_Sig, AdjustActs, AdjustActs_Err, CovMatrix);

  //  Output results to screen and files
  printActivities(Activities_Ext, Activities_Ext_Err, Activities_Rad, Activities_Rad_Err, Activities_Int, Activities_Int_Err, Activities_Sig, Activities_Sig_Err, AdjustActs, AdjustActs_Err);
  writeActivities("FitActivities.txt", Activities_Ext, Activities_Ext_Err, Activities_Rad, Activities_Rad_Err, Activities_Int, Activities_Int_Err, Activities_Sig, Activities_Sig_Err, AdjustActs, AdjustActs_Err);
  writeDenominators("Denominators.txt", Denominators_Ext, Denominators_Rad, Denominators_Int, Denominators_Sig);
  writeCovMatrix("CovMatrix.txt", CovMatrix);

  // Set which plots to draw
  bool DrawSummaryPlots = false;
  bool Draw1ePlots = true;
  bool Draw1e1gPlots = true;
  bool Draw1e2gPlots = true;
  bool Draw1e1aPlots = true;
  bool DrawOCEPlots = true;
  bool DrawExtEGPlots = true;
  bool Draw2b2nPlots = true;
  bool DrawCorrMatrix= true;

  // Draw Output - 1e
  if(Draw1ePlots){
    TCanvas* c1_1e = new TCanvas("c1_1e","Electron Energy - P1_1e_SeOld",10,10,1200,800);
    h_1e_Data_P1_SeOld->SetMarkerStyle(20);
    h_1e_Data_P1_SeOld->Draw();
    StackColl_1e[0]->Draw("HISTSAME");
    h_1e_Data_P1_SeOld->Draw("SAME");
    Legend_1e[0]->Draw();
    ChiSquares_1e[0]->Draw();
    c1_1e->SaveAs("Images/png/1e/1 - P1 Electron Energy SeOld.png");
    c1_1e->SaveAs("Images/eps/1e/1 - P1 Electron Energy SeOld.eps");
    c1_1e->SaveAs("Images/gif/1e/1 - P1 Electron Energy SeOld.gif");

    TCanvas* c2_1e = new TCanvas("c2_1e","Electron Energy - P1_1e_SeNew",10,10,1200,800);
    h_1e_Data_P1_SeNew->SetMarkerStyle(20);
    h_1e_Data_P1_SeNew->Draw();
    StackColl_1e[1]->Draw("HISTSAME");
    h_1e_Data_P1_SeNew->Draw("SAME");
    Legend_1e[1]->Draw();
    ChiSquares_1e[1]->Draw();
    c2_1e->SaveAs("Images/png/1e/2 - P1 Electron Energy SeNew.png");
    c2_1e->SaveAs("Images/eps/1e/2 - P1 Electron Energy SeNew.eps");
    c2_1e->SaveAs("Images/gif/1e/2 - P1 Electron Energy SeNew.gif");

    TCanvas* c3_1e = new TCanvas("c3_1e","Electron Energy - P1_1e_Strip",10,10,1200,800);
    h_1e_Data_P1_Strip->SetMarkerStyle(20);
    h_1e_Data_P1_Strip->Draw();
    StackColl_1e[2]->Draw("HISTSAME");
    h_1e_Data_P1_Strip->Draw("SAME");
    Legend_1e[2]->Draw();
    ChiSquares_1e[2]->Draw();
    c3_1e->SaveAs("Images/png/1e/3 - P1 Electron Energy Strip.png");
    c3_1e->SaveAs("Images/eps/1e/3 - P1 Electron Energy Strip.eps");
    c3_1e->SaveAs("Images/gif/1e/3 - P1 Electron Energy Strip.gif");

    TCanvas* c4_1e = new TCanvas("c4_1e","Electron Energy - P2_1e_SeOld",10,10,1200,800);
    h_1e_Data_P2_SeOld->SetMarkerStyle(20);
    h_1e_Data_P2_SeOld->Draw();
    StackColl_1e[3]->Draw("HISTSAME");
    h_1e_Data_P2_SeOld->Draw("SAME");
    Legend_1e[3]->Draw();
    ChiSquares_1e[3]->Draw();
    c4_1e->SaveAs("Images/png/1e/4 - P2 Electron Energy SeOld.png");
    c4_1e->SaveAs("Images/eps/1e/4 - P2 Electron Energy SeOld.eps");
    c4_1e->SaveAs("Images/gif/1e/4 - P2 Electron Energy SeOld.gif");

    TCanvas* c5_1e = new TCanvas("c5_1e","Electron Energy - P2_1e_SeNew",10,10,1200,800);
    h_1e_Data_P2_SeNew->SetMarkerStyle(20);
    h_1e_Data_P2_SeNew->Draw();
    StackColl_1e[4]->Draw("HISTSAME");
    h_1e_Data_P2_SeNew->Draw("SAME");
    Legend_1e[4]->Draw();
    ChiSquares_1e[4]->Draw();
    c5_1e->SaveAs("Images/png/1e/5 - P2 Electron Energy SeNew.png");
    c5_1e->SaveAs("Images/eps/1e/5 - P2 Electron Energy SeNew.eps");
    c5_1e->SaveAs("Images/gif/1e/5 - P2 Electron Energy SeNew.gif");

    TCanvas* c6_1e = new TCanvas("c6_1e","Electron Energy - P2_1e_Strip",10,10,1200,800);
    h_1e_Data_P2_Strip->SetMarkerStyle(20);
    h_1e_Data_P2_Strip->Draw();
    StackColl_1e[5]->Draw("HISTSAME");
    h_1e_Data_P2_Strip->Draw("SAME");
    Legend_1e[5]->Draw();
    ChiSquares_1e[5]->Draw();
    c6_1e->SaveAs("Images/png/1e/6 - P2 Electron Energy Strip.png");
    c6_1e->SaveAs("Images/eps/1e/6 - P2 Electron Energy Strip.eps");
    c6_1e->SaveAs("Images/gif/1e/6 - P2 Electron Energy Strip.gif");

    if(!DrawSummaryPlots){
      TCanvas* c1_1_1e = new TCanvas("c1_1_1e","Electron Energy - P1_1e_SeOld",10,10,1200,800);
      c1_1_1e->SetLogy();
      h_1e_Data_P1_SeOld->Draw();
      StackColl_1e[0]->Draw("HISTSAME");
      h_1e_Data_P1_SeOld->Draw("SAME");
      LegendLog_1e[0]->Draw();
      ChiSquaresLog_1e[0]->Draw();
      c1_1_1e->SaveAs("Images/png/1e/1 - P1 Electron Energy SeOld Log.png");
      c1_1_1e->SaveAs("Images/eps/1e/1 - P1 Electron Energy SeOld Log.eps");
      c1_1_1e->SaveAs("Images/gif/1e/1 - P1 Electron Energy SeOld Log.gif");

      TCanvas* c2_1_1e = new TCanvas("c2_1_1e","Electron Energy - P1_1e_SeNew",10,10,1200,800);
      c2_1_1e->SetLogy();
      h_1e_Data_P1_SeNew->Draw();
      StackColl_1e[1]->Draw("HISTSAME");
      h_1e_Data_P1_SeNew->Draw("SAME");
      LegendLog_1e[1]->Draw();
      ChiSquaresLog_1e[1]->Draw();
      c2_1_1e->SaveAs("Images/png/1e/2 - P1 Electron Energy SeNew Log.png");
      c2_1_1e->SaveAs("Images/eps/1e/2 - P1 Electron Energy SeNew Log.eps");
      c2_1_1e->SaveAs("Images/gif/1e/2 - P1 Electron Energy SeNew Log.gif");

      TCanvas* c3_1_1e = new TCanvas("c3_1_1e","Electron Energy - P1_1e_Strip",10,10,1200,800);
      c3_1_1e->SetLogy();
      h_1e_Data_P1_Strip->Draw();
      StackColl_1e[2]->Draw("HISTSAME");
      h_1e_Data_P1_Strip->Draw("SAME");
      LegendLog_1e[2]->Draw();
      ChiSquaresLog_1e[2]->Draw();
      c3_1_1e->SaveAs("Images/png/1e/3 - P1 Electron Energy Strip Log.png");
      c3_1_1e->SaveAs("Images/eps/1e/3 - P1 Electron Energy Strip Log.eps");
      c3_1_1e->SaveAs("Images/gif/1e/3 - P1 Electron Energy Strip Log.gif");

      TCanvas* c4_1_1e = new TCanvas("c4_1_1e","Electron Energy - P2_1e_SeOld",10,10,1200,800);
      c4_1_1e->SetLogy();
      h_1e_Data_P2_SeOld->Draw();
      StackColl_1e[3]->Draw("HISTSAME");
      h_1e_Data_P2_SeOld->Draw("SAME");
      LegendLog_1e[3]->Draw();
      ChiSquaresLog_1e[3]->Draw();
      c4_1_1e->SaveAs("Images/png/1e/4 - P2 Electron Energy SeOld Log.png");
      c4_1_1e->SaveAs("Images/eps/1e/4 - P2 Electron Energy SeOld Log.eps");
      c4_1_1e->SaveAs("Images/gif/1e/4 - P2 Electron Energy SeOld Log.gif");

      TCanvas* c5_1_1e = new TCanvas("c5_1_1e","Electron Energy - P2_1e_SeNew",10,10,1200,800);
      c5_1_1e->SetLogy();
      h_1e_Data_P2_SeNew->Draw();
      StackColl_1e[4]->Draw("HISTSAME");
      h_1e_Data_P2_SeNew->Draw("SAME");
      LegendLog_1e[4]->Draw();
      ChiSquaresLog_1e[4]->Draw();
      c5_1_1e->SaveAs("Images/png/1e/5 - P2 Electron Energy SeNew Log.png");
      c5_1_1e->SaveAs("Images/eps/1e/5 - P2 Electron Energy SeNew Log.eps");
      c5_1_1e->SaveAs("Images/gif/1e/5 - P2 Electron Energy SeNew Log.gif");

      TCanvas* c6_1_1e = new TCanvas("c6_1_1e","Electron Energy - P2_1e_Strip",10,10,1200,800);
      c6_1_1e->SetLogy();
      h_1e_Data_P2_Strip->Draw();
      StackColl_1e[5]->Draw("HISTSAME");
      h_1e_Data_P2_Strip->Draw("SAME");
      LegendLog_1e[5]->Draw();
      ChiSquaresLog_1e[5]->Draw();
      c6_1_1e->SaveAs("Images/png/1e/6 - P2 Electron Energy Strip Log.png");
      c6_1_1e->SaveAs("Images/eps/1e/6 - P2 Electron Energy Strip Log.eps");
      c6_1_1e->SaveAs("Images/gif/1e/6 - P2 Electron Energy Strip Log.gif");
    }
  }

  // Draw Output - 1e1g
  if(Draw1e1gPlots){
    TCanvas* c1_1e1g = new TCanvas("c1_1e1g","Electron Energy - P1_1e1g_SeOld",10,10,1200,800);
    h_1e1g_Data_P1_SeOld->SetMarkerStyle(20);
    h_1e1g_Data_P1_SeOld->Draw();
    StackColl_1e1g[0]->Draw("HISTSAME");
    h_1e1g_Data_P1_SeOld->Draw("SAME");
    Legend_1e1g[0]->Draw();
    ChiSquares_1e1g[0]->Draw();
    c1_1e1g->SaveAs("Images/png/1e1g/1 - P1 Electron Energy SeOld.png");
    c1_1e1g->SaveAs("Images/eps/1e1g/1 - P1 Electron Energy SeOld.eps");
    c1_1e1g->SaveAs("Images/gif/1e1g/1 - P1 Electron Energy SeOld.gif");

    TCanvas* c2_1e1g = new TCanvas("c2_1e1g","Electron Energy - P1_1e1g_SeNew",10,10,1200,800);
    h_1e1g_Data_P1_SeNew->SetMarkerStyle(20);
    h_1e1g_Data_P1_SeNew->Draw();
    StackColl_1e1g[1]->Draw("HISTSAME");
    h_1e1g_Data_P1_SeNew->Draw("SAME");
    Legend_1e1g[1]->Draw();
    ChiSquares_1e1g[1]->Draw();
    c2_1e1g->SaveAs("Images/png/1e1g/2 - P1 Electron Energy SeNew.png");
    c2_1e1g->SaveAs("Images/eps/1e1g/2 - P1 Electron Energy SeNew.eps");
    c2_1e1g->SaveAs("Images/gif/1e1g/2 - P1 Electron Energy SeNew.gif");

    TCanvas* c3_1e1g = new TCanvas("c3_1e1g","Electron Energy - P1_1e1g_Strip",10,10,1200,800);
    h_1e1g_Data_P1_Strip->SetMarkerStyle(20);
    h_1e1g_Data_P1_Strip->Draw();
    StackColl_1e1g[2]->Draw("HISTSAME");
    h_1e1g_Data_P1_Strip->Draw("SAME");
    Legend_1e1g[2]->Draw();
    ChiSquares_1e1g[2]->Draw();
    c3_1e1g->SaveAs("Images/png/1e1g/3 - P1 Electron Energy Strip.png");
    c3_1e1g->SaveAs("Images/eps/1e1g/3 - P1 Electron Energy Strip.eps");
    c3_1e1g->SaveAs("Images/gif/1e1g/3 - P1 Electron Energy Strip.gif");

    TCanvas* c4_1e1g = new TCanvas("c4_1e1g","Electron Energy - P2_1e1g_SeOld",10,10,1200,800);
    h_1e1g_Data_P2_SeOld->SetMarkerStyle(20);
    h_1e1g_Data_P2_SeOld->Draw();
    StackColl_1e1g[3]->Draw("HISTSAME");
    h_1e1g_Data_P2_SeOld->Draw("SAME");
    Legend_1e1g[3]->Draw();
    ChiSquares_1e1g[3]->Draw();
    c4_1e1g->SaveAs("Images/png/1e1g/4 - P2 Electron Energy SeOld.png");
    c4_1e1g->SaveAs("Images/eps/1e1g/4 - P2 Electron Energy SeOld.eps");
    c4_1e1g->SaveAs("Images/gif/1e1g/4 - P2 Electron Energy SeOld.gif");

    TCanvas* c5_1e1g = new TCanvas("c5_1e1g","Electron Energy - P2_1e1g_SeNew",10,10,1200,800);
    h_1e1g_Data_P2_SeNew->SetMarkerStyle(20);
    h_1e1g_Data_P2_SeNew->Draw();
    StackColl_1e1g[4]->Draw("HISTSAME");
    h_1e1g_Data_P2_SeNew->Draw("SAME");
    Legend_1e1g[4]->Draw();
    ChiSquares_1e1g[4]->Draw();
    c5_1e1g->SaveAs("Images/png/1e1g/5 - P2 Electron Energy SeNew.png");
    c5_1e1g->SaveAs("Images/eps/1e1g/5 - P2 Electron Energy SeNew.eps");
    c5_1e1g->SaveAs("Images/gif/1e1g/5 - P2 Electron Energy SeNew.gif");

    TCanvas* c6_1e1g = new TCanvas("c6_1e1g","Electron Energy - P2_1e1g_Strip",10,10,1200,800);
    h_1e1g_Data_P2_Strip->SetMarkerStyle(20);
    h_1e1g_Data_P2_Strip->Draw();
    StackColl_1e1g[5]->Draw("HISTSAME");
    h_1e1g_Data_P2_Strip->Draw("SAME");
    Legend_1e1g[5]->Draw();
    ChiSquares_1e1g[5]->Draw();
    c6_1e1g->SaveAs("Images/png/1e1g/6 - P2 Electron Energy Strip.png");
    c6_1e1g->SaveAs("Images/eps/1e1g/6 - P2 Electron Energy Strip.eps");
    c6_1e1g->SaveAs("Images/gif/1e1g/6 - P2 Electron Energy Strip.gif");

    if(!DrawSummaryPlots){
      TCanvas* c1_1_1e1g = new TCanvas("c1_1_1e1g","Electron Energy - P1_1e1g_SeOld",10,10,1200,800);
      c1_1_1e1g->SetLogy();
      h_1e1g_Data_P1_SeOld->Draw();
      StackColl_1e1g[0]->Draw("HISTSAME");
      h_1e1g_Data_P1_SeOld->Draw("SAME");
      LegendLog_1e1g[0]->Draw();
      ChiSquaresLog_1e1g[0]->Draw();
      c1_1_1e1g->SaveAs("Images/png/1e1g/1 - P1 Electron Energy SeOld Log.png");
      c1_1_1e1g->SaveAs("Images/eps/1e1g/1 - P1 Electron Energy SeOld Log.eps");
      c1_1_1e1g->SaveAs("Images/gif/1e1g/1 - P1 Electron Energy SeOld Log.gif");

      TCanvas* c2_1_1e1g = new TCanvas("c2_1_1e1g","Electron Energy - P1_1e1g_SeNew",10,10,1200,800);
      c2_1_1e1g->SetLogy();
      h_1e1g_Data_P1_SeNew->Draw();
      StackColl_1e1g[1]->Draw("HISTSAME");
      h_1e1g_Data_P1_SeNew->Draw("SAME");
      LegendLog_1e1g[1]->Draw();
      ChiSquaresLog_1e1g[1]->Draw();
      c2_1_1e1g->SaveAs("Images/png/1e1g/2 - P1 Electron Energy SeNew Log.png");
      c2_1_1e1g->SaveAs("Images/eps/1e1g/2 - P1 Electron Energy SeNew Log.eps");
      c2_1_1e1g->SaveAs("Images/gif/1e1g/2 - P1 Electron Energy SeNew Log.gif");

      TCanvas* c3_1_1e1g = new TCanvas("c3_1_1e1g","Electron Energy - P1_1e1g_Strip",10,10,1200,800);
      c3_1_1e1g->SetLogy();
      h_1e1g_Data_P1_Strip->Draw();
      StackColl_1e1g[2]->Draw("HISTSAME");
      h_1e1g_Data_P1_Strip->Draw("SAME");
      LegendLog_1e1g[2]->Draw();
      ChiSquaresLog_1e1g[2]->Draw();
      c3_1_1e1g->SaveAs("Images/png/1e1g/3 - P1 Electron Energy Strip Log.png");
      c3_1_1e1g->SaveAs("Images/eps/1e1g/3 - P1 Electron Energy Strip Log.eps");
      c3_1_1e1g->SaveAs("Images/gif/1e1g/3 - P1 Electron Energy Strip Log.gif");

      TCanvas* c4_1_1e1g = new TCanvas("c4_1_1e1g","Electron Energy - P2_1e1g_SeOld",10,10,1200,800);
      c4_1_1e1g->SetLogy();
      h_1e1g_Data_P2_SeOld->Draw();
      StackColl_1e1g[3]->Draw("HISTSAME");
      h_1e1g_Data_P2_SeOld->Draw("SAME");
      LegendLog_1e1g[3]->Draw();
      ChiSquaresLog_1e1g[3]->Draw();
      c4_1_1e1g->SaveAs("Images/png/1e1g/4 - P2 Electron Energy SeOld Log.png");
      c4_1_1e1g->SaveAs("Images/eps/1e1g/4 - P2 Electron Energy SeOld Log.eps");
      c4_1_1e1g->SaveAs("Images/gif/1e1g/4 - P2 Electron Energy SeOld Log.gif");

      TCanvas* c5_1_1e1g = new TCanvas("c5_1_1e1g","Electron Energy - P2_1e1g_SeNew",10,10,1200,800);
      c5_1_1e1g->SetLogy();
      h_1e1g_Data_P2_SeNew->Draw();
      StackColl_1e1g[4]->Draw("HISTSAME");
      h_1e1g_Data_P2_SeNew->Draw("SAME");
      LegendLog_1e1g[4]->Draw();
      ChiSquaresLog_1e1g[4]->Draw();
      c5_1_1e1g->SaveAs("Images/png/1e1g/5 - P2 Electron Energy SeNew Log.png");
      c5_1_1e1g->SaveAs("Images/eps/1e1g/5 - P2 Electron Energy SeNew Log.eps");
      c5_1_1e1g->SaveAs("Images/gif/1e1g/5 - P2 Electron Energy SeNew Log.gif");

      TCanvas* c6_1_1e1g = new TCanvas("c6_1_1e1g","Electron Energy - P2_1e1g_Strip",10,10,1200,800);
      c6_1_1e1g->SetLogy();
      h_1e1g_Data_P2_Strip->Draw();
      StackColl_1e1g[5]->Draw("HISTSAME");
      h_1e1g_Data_P2_Strip->Draw("SAME");
      LegendLog_1e1g[5]->Draw();
      ChiSquaresLog_1e1g[5]->Draw();
      c6_1_1e1g->SaveAs("Images/png/1e1g/6 - P2 Electron Energy Strip Log.png");
      c6_1_1e1g->SaveAs("Images/eps/1e1g/6 - P2 Electron Energy Strip Log.eps");
      c6_1_1e1g->SaveAs("Images/gif/1e1g/6 - P2 Electron Energy Strip Log.gif");
    }
  }

  // Draw Output - 1e2g
  if(Draw1e2gPlots){
    TCanvas* c1_1e2g = new TCanvas("c1_1e2g","Electron Energy - 1e2g SeOld",10,10,1200,800);
    h_1e2g_Data_SeOld->SetMarkerStyle(20);
    h_1e2g_Data_SeOld->Draw();
    StackColl_1e2g[0]->Draw("HISTSAME");
    h_1e2g_Data_SeOld->Draw("SAME");
    Legend_1e2g[0]->Draw();
    ChiSquares_1e2g[0]->Draw();
    c1_1e2g->SaveAs("Images/png/1e2g/1 - Electron Energy SeOld.png");
    c1_1e2g->SaveAs("Images/eps/1e2g/1 - Electron Energy SeOld.eps");
    c1_1e2g->SaveAs("Images/gif/1e2g/1 - Electron Energy SeOld.gif");

    TCanvas* c2_1e2g = new TCanvas("c2_1e2g","Electron Energy - 1e2g SeNew",10,10,1200,800);
    h_1e2g_Data_SeNew->SetMarkerStyle(20);
    h_1e2g_Data_SeNew->Draw();
    StackColl_1e2g[1]->Draw("HISTSAME");
    h_1e2g_Data_SeNew->Draw("SAME");
    Legend_1e2g[1]->Draw();
    ChiSquares_1e2g[1]->Draw();
    c2_1e2g->SaveAs("Images/png/1e2g/1 - Electron Energy SeNew.png");
    c2_1e2g->SaveAs("Images/eps/1e2g/1 - Electron Energy SeNew.eps");
    c2_1e2g->SaveAs("Images/gif/1e2g/1 - Electron Energy SeNew.gif");
  }

  // Draw Output - 1e1a
  if(Draw1e1aPlots){
    if(!DrawSummaryPlots){
      TCanvas* c1_1e1a = new TCanvas("c1_1e1a"," aOut eOut Sector6 P1",200,10,1200,800);
      h_1e1a_Data_P1_aOuteOut_Sector6->SetMarkerStyle(20);
      h_1e1a_Data_P1_aOuteOut_Sector6->GetYaxis()->SetRangeUser(0,120);
      h_1e1a_Data_P1_aOuteOut_Sector6->Draw();
      StackColl_1e1a_P1[0]->Draw("HISTSAME");
      h_1e1a_Data_P1_aOuteOut_Sector6->Draw("SAME");
      Legend_1e1a_P1[0]->Draw();
      ChiSquares_1e1a_P1[0]->Draw();
      c1_1e1a->SaveAs("Images/png/1e1a/P1/1 - Sector6 - Alpha Out Electron Out.png");
      c1_1e1a->SaveAs("Images/eps/1e1a/P1/1 - Sector6 - Alpha Out Electron Out.eps");
      c1_1e1a->SaveAs("Images/gif/1e1a/P1/1 - Sector6 - Alpha Out Electron Out.gif");

      TCanvas* c2_1e1a = new TCanvas("c2_1e1a"," aIn eOut Sector6 P1",200,10,1200,800);
      h_1e1a_Data_P1_aIneOut_Sector6->SetMarkerStyle(20);
      h_1e1a_Data_P1_aIneOut_Sector6->GetYaxis()->SetRangeUser(0,120);
      h_1e1a_Data_P1_aIneOut_Sector6->Draw();
      StackColl_1e1a_P1[1]->Draw("HISTSAME");
      h_1e1a_Data_P1_aIneOut_Sector6->Draw("SAME");
      Legend_1e1a_P1[1]->Draw();
      ChiSquares_1e1a_P1[1]->Draw();
      c2_1e1a->SaveAs("Images/png/1e1a/P1/2 - Sector6 - Alpha In Electron Out.png");
      c2_1e1a->SaveAs("Images/eps/1e1a/P1/2 - Sector6 - Alpha In Electron Out.eps");
      c2_1e1a->SaveAs("Images/gif/1e1a/P1/2 - Sector6 - Alpha In Electron Out.gif");

      TCanvas* c3_1e1a = new TCanvas("c3_1e1a"," aOut eIn Sector6 P1",200,10,1200,800);
      h_1e1a_Data_P1_aOuteIn_Sector6->SetMarkerStyle(20);
      h_1e1a_Data_P1_aOuteIn_Sector6->GetYaxis()->SetRangeUser(0,120);
      h_1e1a_Data_P1_aOuteIn_Sector6->Draw();
      StackColl_1e1a_P1[2]->Draw("HISTSAME");
      h_1e1a_Data_P1_aOuteIn_Sector6->Draw("SAME");
      Legend_1e1a_P1[2]->Draw();
      ChiSquares_1e1a_P1[2]->Draw();
      c3_1e1a->SaveAs("Images/png/1e1a/P1/3 - Sector6 - Alpha Out Electron In.png");
      c3_1e1a->SaveAs("Images/eps/1e1a/P1/3 - Sector6 - Alpha Out Electron In.eps");
      c3_1e1a->SaveAs("Images/gif/1e1a/P1/3 - Sector6 - Alpha Out Electron In.gif");

      TCanvas* c4_1e1a = new TCanvas("c4_1e1a"," aIn eIn Sector6 P1",200,10,1200,800);
      h_1e1a_Data_P1_aIneIn_Sector6->SetMarkerStyle(20);
      h_1e1a_Data_P1_aIneIn_Sector6->GetYaxis()->SetRangeUser(0,120);
      h_1e1a_Data_P1_aIneIn_Sector6->Draw();
      StackColl_1e1a_P1[3]->Draw("HISTSAME");
      h_1e1a_Data_P1_aIneIn_Sector6->Draw("SAME");
      Legend_1e1a_P1[3]->Draw();
      ChiSquares_1e1a_P1[3]->Draw();
      c4_1e1a->SaveAs("Images/png/1e1a/P1/4 - Sector6 - Alpha In Electron In.png");
      c4_1e1a->SaveAs("Images/eps/1e1a/P1/4 - Sector6 - Alpha In Electron In.eps");
      c4_1e1a->SaveAs("Images/gif/1e1a/P1/4 - Sector6 - Alpha In Electron In.gif");

      TCanvas* c5_1e1a = new TCanvas("c5_1e1a"," aOut eOut Sector7 P1",200,10,1200,800);
      h_1e1a_Data_P1_aOuteOut_Sector7->SetMarkerStyle(20);
      h_1e1a_Data_P1_aOuteOut_Sector7->GetYaxis()->SetRangeUser(0,120);
      h_1e1a_Data_P1_aOuteOut_Sector7->Draw();
      StackColl_1e1a_P1[4]->Draw("HISTSAME");
      h_1e1a_Data_P1_aOuteOut_Sector7->Draw("SAME");
      Legend_1e1a_P1[4]->Draw();
      ChiSquares_1e1a_P1[4]->Draw();
      c5_1e1a->SaveAs("Images/png/1e1a/P1/5 - Sector7 - Alpha Out Electron Out.png");
      c5_1e1a->SaveAs("Images/eps/1e1a/P1/5 - Sector7 - Alpha Out Electron Out.eps");
      c5_1e1a->SaveAs("Images/gif/1e1a/P1/5 - Sector7 - Alpha Out Electron Out.gif");

      TCanvas* c6_1e1a = new TCanvas("c6_1e1a"," aIn eOut Sector7 P1",200,10,1200,800);
      h_1e1a_Data_P1_aIneOut_Sector7->SetMarkerStyle(20);
      h_1e1a_Data_P1_aIneOut_Sector7->GetYaxis()->SetRangeUser(0,120);
      h_1e1a_Data_P1_aIneOut_Sector7->Draw();
      StackColl_1e1a_P1[5]->Draw("HISTSAME");
      h_1e1a_Data_P1_aIneOut_Sector7->Draw("SAME");
      Legend_1e1a_P1[5]->Draw();
      ChiSquares_1e1a_P1[5]->Draw();
      c6_1e1a->SaveAs("Images/png/1e1a/P1/6 - Sector7 - Alpha In Electron Out.png");
      c6_1e1a->SaveAs("Images/eps/1e1a/P1/6 - Sector7 - Alpha In Electron Out.eps");
      c6_1e1a->SaveAs("Images/gif/1e1a/P1/6 - Sector7 - Alpha In Electron Out.gif");

      TCanvas* c7_1e1a = new TCanvas("c7_1e1a"," aOut eIn Sector7 P1",200,10,1200,800);
      h_1e1a_Data_P1_aOuteIn_Sector7->SetMarkerStyle(20);
      h_1e1a_Data_P1_aOuteIn_Sector7->GetYaxis()->SetRangeUser(0,120);
      h_1e1a_Data_P1_aOuteIn_Sector7->Draw();
      StackColl_1e1a_P1[6]->Draw("HISTSAME");
      h_1e1a_Data_P1_aOuteIn_Sector7->Draw("SAME");
      Legend_1e1a_P1[6]->Draw();
      ChiSquares_1e1a_P1[6]->Draw();
      c7_1e1a->SaveAs("Images/png/1e1a/P1/7 - Sector7 - Alpha Out Electron In.png");
      c7_1e1a->SaveAs("Images/eps/1e1a/P1/7 - Sector7 - Alpha Out Electron In.eps");
      c7_1e1a->SaveAs("Images/gif/1e1a/P1/7 - Sector7 - Alpha Out Electron In.gif");

      TCanvas* c8_1e1a = new TCanvas("c8_1e1a"," aIn eIn Sector7 P1",200,10,1200,800);
      h_1e1a_Data_P1_aIneIn_Sector7->SetMarkerStyle(20);
      h_1e1a_Data_P1_aIneIn_Sector7->GetYaxis()->SetRangeUser(0,120);
      h_1e1a_Data_P1_aIneIn_Sector7->Draw();
      StackColl_1e1a_P1[7]->Draw("HISTSAME");
      h_1e1a_Data_P1_aIneIn_Sector7->Draw("SAME");
      Legend_1e1a_P1[7]->Draw();
      ChiSquares_1e1a_P1[7]->Draw();
      c8_1e1a->SaveAs("Images/png/1e1a/P1/8 - Sector7 - Alpha In Electron In.png");
      c8_1e1a->SaveAs("Images/eps/1e1a/P1/8 - Sector7 - Alpha In Electron In.eps");
      c8_1e1a->SaveAs("Images/gif/1e1a/P1/8 - Sector7 - Alpha In Electron In.gif");

      TCanvas* c9_1e1a = new TCanvas("c9_1e1a"," aOut eOut Sector8 P1",200,10,1200,800);
      h_1e1a_Data_P1_aOuteOut_Sector8->SetMarkerStyle(20);
      h_1e1a_Data_P1_aOuteOut_Sector8->GetYaxis()->SetRangeUser(0,30);
      h_1e1a_Data_P1_aOuteOut_Sector8->Draw();
      StackColl_1e1a_P1[8]->Draw("HISTSAME");
      h_1e1a_Data_P1_aOuteOut_Sector8->Draw("SAME");
      Legend_1e1a_P1[8]->Draw();
      ChiSquares_1e1a_P1[8]->Draw();
      c9_1e1a->SaveAs("Images/png/1e1a/P1/9 - Sector8 - Alpha Out Electron Out.png");
      c9_1e1a->SaveAs("Images/eps/1e1a/P1/9 - Sector8 - Alpha Out Electron Out.eps");
      c9_1e1a->SaveAs("Images/gif/1e1a/P1/9 - Sector8 - Alpha Out Electron Out.gif");

      TCanvas* c10_1e1a = new TCanvas("c10_1e1a"," aIn eOut Sector8 P1",200,10,1200,800);
      h_1e1a_Data_P1_aIneOut_Sector8->SetMarkerStyle(20);
      h_1e1a_Data_P1_aIneOut_Sector8->GetYaxis()->SetRangeUser(0,30);
      h_1e1a_Data_P1_aIneOut_Sector8->Draw();
      StackColl_1e1a_P1[9]->Draw("HISTSAME");
      h_1e1a_Data_P1_aIneOut_Sector8->Draw("SAME");
      Legend_1e1a_P1[9]->Draw();
      ChiSquares_1e1a_P1[9]->Draw();
      c10_1e1a->SaveAs("Images/png/1e1a/P1/10 - Sector8 - Alpha In Electron Out.png");
      c10_1e1a->SaveAs("Images/eps/1e1a/P1/10 - Sector8 - Alpha In Electron Out.eps");
      c10_1e1a->SaveAs("Images/gif/1e1a/P1/10 - Sector8 - Alpha In Electron Out.gif");

      TCanvas* c11_1e1a = new TCanvas("c11_1e1a"," aOut eIn Sector8 P1",200,10,1200,800);
      h_1e1a_Data_P1_aOuteIn_Sector8->SetMarkerStyle(20);
      h_1e1a_Data_P1_aOuteIn_Sector8->GetYaxis()->SetRangeUser(0,30);
      h_1e1a_Data_P1_aOuteIn_Sector8->Draw();
      StackColl_1e1a_P1[10]->Draw("HISTSAME");
      h_1e1a_Data_P1_aOuteIn_Sector8->Draw("SAME");
      Legend_1e1a_P1[10]->Draw();
      ChiSquares_1e1a_P1[10]->Draw();
      c11_1e1a->SaveAs("Images/png/1e1a/P1/11 - Sector8 - Alpha Out Electron In.png");
      c11_1e1a->SaveAs("Images/eps/1e1a/P1/11 - Sector8 - Alpha Out Electron In.eps");
      c11_1e1a->SaveAs("Images/gif/1e1a/P1/11 - Sector8 - Alpha Out Electron In.gif");

      TCanvas* c12_1e1a = new TCanvas("c12_1e1a"," aIn eIn Sector8 P1",200,10,1200,800);
      h_1e1a_Data_P1_aIneIn_Sector8->SetMarkerStyle(20);
      h_1e1a_Data_P1_aIneIn_Sector8->GetYaxis()->SetRangeUser(0,30);
      h_1e1a_Data_P1_aIneIn_Sector8->Draw();
      StackColl_1e1a_P1[11]->Draw("HISTSAME");
      h_1e1a_Data_P1_aIneIn_Sector8->Draw("SAME");
      Legend_1e1a_P1[11]->Draw();
      ChiSquares_1e1a_P1[11]->Draw();
      c12_1e1a->SaveAs("Images/png/1e1a/P1/12 - Sector8 - Alpha In Electron In.png");
      c12_1e1a->SaveAs("Images/eps/1e1a/P1/12 - Sector8 - Alpha In Electron In.eps");
      c12_1e1a->SaveAs("Images/gif/1e1a/P1/12 - Sector8 - Alpha In Electron In.gif");
    }

    TCanvas* c13_1e1a = new TCanvas("c13_1e1a"," All Events Sector6 P1",200,10,1200,800);
    h_1e1a_Data_P1_AllEvents_Sector6->SetMarkerStyle(20);
    h_1e1a_Data_P1_AllEvents_Sector6->GetYaxis()->SetRangeUser(0,300);
    h_1e1a_Data_P1_AllEvents_Sector6->Draw();
    StackColl_1e1a_P1[12]->Draw("HISTSAME");
    h_1e1a_Data_P1_AllEvents_Sector6->Draw("SAME");
    Legend_1e1a_P1[12]->Draw();
    ChiSquares_1e1a_P1[12]->Draw();
    c13_1e1a->SaveAs("Images/png/1e1a/P1/13 - Sector6 - All Events.png");
    c13_1e1a->SaveAs("Images/eps/1e1a/P1/13 - Sector6 - All Events.eps");
    c13_1e1a->SaveAs("Images/gif/1e1a/P1/13 - Sector6 - All Events.gif");

    TCanvas* c14_1e1a = new TCanvas("c14_1e1a"," All Events Sector7 P1",200,10,1200,800);
    h_1e1a_Data_P1_AllEvents_Sector7->SetMarkerStyle(20);
    h_1e1a_Data_P1_AllEvents_Sector7->GetYaxis()->SetRangeUser(0,300);
    h_1e1a_Data_P1_AllEvents_Sector7->Draw();
    StackColl_1e1a_P1[13]->Draw("HISTSAME");
    h_1e1a_Data_P1_AllEvents_Sector7->Draw("SAME");
    Legend_1e1a_P1[13]->Draw();
    ChiSquares_1e1a_P1[13]->Draw();
    c14_1e1a->SaveAs("Images/png/1e1a/P1/14 - Sector7 - All Events.png");
    c14_1e1a->SaveAs("Images/eps/1e1a/P1/14 - Sector7 - All Events.eps");
    c14_1e1a->SaveAs("Images/gif/1e1a/P1/14 - Sector7 - All Events.gif");

    TCanvas* c15_1e1a = new TCanvas("c15_1e1a"," All Events Sector8 P1",200,10,1200,800);
    h_1e1a_Data_P1_AllEvents_Sector8->SetMarkerStyle(20);
    h_1e1a_Data_P1_AllEvents_Sector8->GetYaxis()->SetRangeUser(0,100);
    h_1e1a_Data_P1_AllEvents_Sector8->Draw();
    StackColl_1e1a_P1[14]->Draw("HISTSAME");
    h_1e1a_Data_P1_AllEvents_Sector8->Draw("SAME");
    Legend_1e1a_P1[14]->Draw();
    ChiSquares_1e1a_P1[14]->Draw();
    c15_1e1a->SaveAs("Images/png/1e1a/P1/15 - Sector8 - All Events.png");
    c15_1e1a->SaveAs("Images/eps/1e1a/P1/15 - Sector8 - All Events.eps");
    c15_1e1a->SaveAs("Images/gif/1e1a/P1/15 - Sector8 - All Events.gif");

    if(!DrawSummaryPlots){
      TCanvas* c16_1e1a = new TCanvas("c16_1e1a"," aOut eOut Sector6 P2",200,10,1200,800);
      h_1e1a_Data_P2_aOuteOut_Sector6->SetMarkerStyle(20);
      h_1e1a_Data_P2_aOuteOut_Sector6->GetYaxis()->SetRangeUser(0,80);
      h_1e1a_Data_P2_aOuteOut_Sector6->Draw();
      StackColl_1e1a_P2[0]->Draw("HISTSAME");
      h_1e1a_Data_P2_aOuteOut_Sector6->Draw("SAME");
      Legend_1e1a_P2[0]->Draw();
      ChiSquares_1e1a_P2[0]->Draw();
      c16_1e1a->SaveAs("Images/png/1e1a/P2/1 - Sector6 - Alpha Out Electron Out.png");
      c16_1e1a->SaveAs("Images/eps/1e1a/P2/1 - Sector6 - Alpha Out Electron Out.eps");
      c16_1e1a->SaveAs("Images/gif/1e1a/P2/1 - Sector6 - Alpha Out Electron Out.gif");

      TCanvas* c17_1e1a = new TCanvas("c17_1e1a"," aIn eOut Sector6 P2",200,10,1200,800);
      h_1e1a_Data_P2_aIneOut_Sector6->SetMarkerStyle(20);
      h_1e1a_Data_P2_aIneOut_Sector6->GetYaxis()->SetRangeUser(0,80);
      h_1e1a_Data_P2_aIneOut_Sector6->Draw();
      StackColl_1e1a_P2[1]->Draw("HISTSAME");
      h_1e1a_Data_P2_aIneOut_Sector6->Draw("SAME");
      Legend_1e1a_P2[1]->Draw();
      ChiSquares_1e1a_P2[1]->Draw();
      c17_1e1a->SaveAs("Images/png/1e1a/P2/2 - Sector6 - Alpha In Electron Out.png");
      c17_1e1a->SaveAs("Images/eps/1e1a/P2/2 - Sector6 - Alpha In Electron Out.eps");
      c17_1e1a->SaveAs("Images/gif/1e1a/P2/2 - Sector6 - Alpha In Electron Out.gif");
      
      TCanvas* c18_1e1a = new TCanvas("c18_1e1a"," aOut eIn Sector6 P2",200,10,1200,800);
      h_1e1a_Data_P2_aOuteIn_Sector6->SetMarkerStyle(20);
      h_1e1a_Data_P2_aOuteIn_Sector6->GetYaxis()->SetRangeUser(0,80);
      h_1e1a_Data_P2_aOuteIn_Sector6->Draw();
      StackColl_1e1a_P2[2]->Draw("HISTSAME");
      h_1e1a_Data_P2_aOuteIn_Sector6->Draw("SAME");
      Legend_1e1a_P2[2]->Draw();
      ChiSquares_1e1a_P2[2]->Draw();
      c18_1e1a->SaveAs("Images/png/1e1a/P2/3 - Sector6 - Alpha Out Electron In.png");
      c18_1e1a->SaveAs("Images/eps/1e1a/P2/3 - Sector6 - Alpha Out Electron In.eps");
      c18_1e1a->SaveAs("Images/gif/1e1a/P2/3 - Sector6 - Alpha Out Electron In.gif");

      TCanvas* c19_1e1a = new TCanvas("c19_1e1a"," aIn eIn Sector6 P2",200,10,1200,800);
      h_1e1a_Data_P2_aIneIn_Sector6->SetMarkerStyle(20);
      h_1e1a_Data_P2_aIneIn_Sector6->GetYaxis()->SetRangeUser(0,80);
      h_1e1a_Data_P2_aIneIn_Sector6->Draw();
      StackColl_1e1a_P2[3]->Draw("HISTSAME");
      h_1e1a_Data_P2_aIneIn_Sector6->Draw("SAME");
      Legend_1e1a_P2[3]->Draw();
      ChiSquares_1e1a_P2[3]->Draw();
      c19_1e1a->SaveAs("Images/png/1e1a/P2/4 - Sector6 - Alpha In Electron In.png");
      c19_1e1a->SaveAs("Images/eps/1e1a/P2/4 - Sector6 - Alpha In Electron In.eps");
      c19_1e1a->SaveAs("Images/gif/1e1a/P2/4 - Sector6 - Alpha In Electron In.gif");

      TCanvas* c20_1e1a = new TCanvas("c20_1e1a"," aOut eOut Sector7 P2",200,10,1200,800);
      h_1e1a_Data_P2_aOuteOut_Sector7->SetMarkerStyle(20);
      h_1e1a_Data_P2_aOuteOut_Sector7->GetYaxis()->SetRangeUser(0,80);
      h_1e1a_Data_P2_aOuteOut_Sector7->Draw();
      StackColl_1e1a_P2[4]->Draw("HISTSAME");
      h_1e1a_Data_P2_aOuteOut_Sector7->Draw("SAME");
      Legend_1e1a_P2[4]->Draw();
      ChiSquares_1e1a_P2[4]->Draw();
      c20_1e1a->SaveAs("Images/png/1e1a/P2/5 - Sector7 - Alpha Out Electron Out.png");
      c20_1e1a->SaveAs("Images/eps/1e1a/P2/5 - Sector7 - Alpha Out Electron Out.eps");
      c20_1e1a->SaveAs("Images/gif/1e1a/P2/5 - Sector7 - Alpha Out Electron Out.gif");

      TCanvas* c21_1e1a = new TCanvas("c21_1e1a"," aIn eOut Sector7 P2",200,10,1200,800);
      h_1e1a_Data_P2_aIneOut_Sector7->SetMarkerStyle(20);
      h_1e1a_Data_P2_aIneOut_Sector7->GetYaxis()->SetRangeUser(0,80);
      h_1e1a_Data_P2_aIneOut_Sector7->Draw();
      StackColl_1e1a_P2[5]->Draw("HISTSAME");
      h_1e1a_Data_P2_aIneOut_Sector7->Draw("SAME");
      Legend_1e1a_P2[5]->Draw();
      ChiSquares_1e1a_P2[5]->Draw();
      c21_1e1a->SaveAs("Images/png/1e1a/P2/6 - Sector7 - Alpha In Electron Out.png");
      c21_1e1a->SaveAs("Images/eps/1e1a/P2/6 - Sector7 - Alpha In Electron Out.eps");
      c21_1e1a->SaveAs("Images/gif/1e1a/P2/6 - Sector7 - Alpha In Electron Out.gif");

      TCanvas* c22_1e1a = new TCanvas("c22_1e1a"," aOut eIn Sector7 P2",200,10,1200,800);
      h_1e1a_Data_P2_aOuteIn_Sector7->SetMarkerStyle(20);
      h_1e1a_Data_P2_aOuteIn_Sector7->GetYaxis()->SetRangeUser(0,80);
      h_1e1a_Data_P2_aOuteIn_Sector7->Draw();
      StackColl_1e1a_P2[6]->Draw("HISTSAME");
      h_1e1a_Data_P2_aOuteIn_Sector7->Draw("SAME");
      Legend_1e1a_P2[6]->Draw();
      ChiSquares_1e1a_P2[6]->Draw();
      c22_1e1a->SaveAs("Images/png/1e1a/P2/7 - Sector7 - Alpha Out Electron In.png");
      c22_1e1a->SaveAs("Images/eps/1e1a/P2/7 - Sector7 - Alpha Out Electron In.eps");
      c22_1e1a->SaveAs("Images/gif/1e1a/P2/7 - Sector7 - Alpha Out Electron In.gif");

      TCanvas* c23_1e1a = new TCanvas("c23_1e1a"," aIn eIn Sector7 P2",200,10,1200,800);
      h_1e1a_Data_P2_aIneIn_Sector7->SetMarkerStyle(20);
      h_1e1a_Data_P2_aIneIn_Sector7->GetYaxis()->SetRangeUser(0,80);
      h_1e1a_Data_P2_aIneIn_Sector7->Draw();
      StackColl_1e1a_P2[7]->Draw("HISTSAME");
      h_1e1a_Data_P2_aIneIn_Sector7->Draw("SAME");
      Legend_1e1a_P2[7]->Draw();
      ChiSquares_1e1a_P2[7]->Draw();
      c23_1e1a->SaveAs("Images/png/1e1a/P2/8 - Sector7 - Alpha In Electron In.png");
      c23_1e1a->SaveAs("Images/eps/1e1a/P2/8 - Sector7 - Alpha In Electron In.eps");
      c23_1e1a->SaveAs("Images/gif/1e1a/P2/8 - Sector7 - Alpha In Electron In.gif");

      TCanvas* c24_1e1a = new TCanvas("c24_1e1a"," aOut eOut Sector8 P2",200,10,1200,800);
      h_1e1a_Data_P2_aOuteOut_Sector8->SetMarkerStyle(20);
      h_1e1a_Data_P2_aOuteOut_Sector8->GetYaxis()->SetRangeUser(0,30);
      h_1e1a_Data_P2_aOuteOut_Sector8->Draw();
      StackColl_1e1a_P2[8]->Draw("HISTSAME");
      h_1e1a_Data_P2_aOuteOut_Sector8->Draw("SAME");
      Legend_1e1a_P2[8]->Draw();
      ChiSquares_1e1a_P2[8]->Draw();
      c24_1e1a->SaveAs("Images/png/1e1a/P2/9 - Sector8 - Alpha Out Electron Out.png");
      c24_1e1a->SaveAs("Images/eps/1e1a/P2/9 - Sector8 - Alpha Out Electron Out.eps");
      c24_1e1a->SaveAs("Images/gif/1e1a/P2/9 - Sector8 - Alpha Out Electron Out.gif");

      TCanvas* c25_1e1a = new TCanvas("c25_1e1a"," aIn eOut Sector8 P2",200,10,1200,800);
      h_1e1a_Data_P2_aIneOut_Sector8->SetMarkerStyle(20);
      h_1e1a_Data_P2_aIneOut_Sector8->GetYaxis()->SetRangeUser(0,30);
      h_1e1a_Data_P2_aIneOut_Sector8->Draw();
      StackColl_1e1a_P2[9]->Draw("HISTSAME");
      h_1e1a_Data_P2_aIneOut_Sector8->Draw("SAME");
      Legend_1e1a_P2[9]->Draw();
      ChiSquares_1e1a_P2[9]->Draw();
      c25_1e1a->SaveAs("Images/png/1e1a/P2/10 - Sector8 - Alpha In Electron Out.png");
      c25_1e1a->SaveAs("Images/eps/1e1a/P2/10 - Sector8 - Alpha In Electron Out.eps");
      c25_1e1a->SaveAs("Images/gif/1e1a/P2/10 - Sector8 - Alpha In Electron Out.gif");

      TCanvas* c26_1e1a = new TCanvas("c26_1e1a"," aOut eIn Sector8 P2",200,10,1200,800);
      h_1e1a_Data_P2_aOuteIn_Sector8->SetMarkerStyle(20);
      h_1e1a_Data_P2_aOuteIn_Sector8->GetYaxis()->SetRangeUser(0,30);
      h_1e1a_Data_P2_aOuteIn_Sector8->Draw();
      StackColl_1e1a_P2[10]->Draw("HISTSAME");
      h_1e1a_Data_P2_aOuteIn_Sector8->Draw("SAME");
      Legend_1e1a_P2[10]->Draw();
      ChiSquares_1e1a_P2[10]->Draw();
      c26_1e1a->SaveAs("Images/png/1e1a/P2/11 - Sector8 - Alpha Out Electron In.png");
      c26_1e1a->SaveAs("Images/eps/1e1a/P2/11 - Sector8 - Alpha Out Electron In.eps");
      c26_1e1a->SaveAs("Images/gif/1e1a/P2/11 - Sector8 - Alpha Out Electron In.gif");

      TCanvas* c27_1e1a = new TCanvas("c27_1e1a"," aIn eIn Sector8 P2",200,10,1200,800);
      h_1e1a_Data_P2_aIneIn_Sector8->SetMarkerStyle(20);
      h_1e1a_Data_P2_aIneIn_Sector8->GetYaxis()->SetRangeUser(0,30);
      h_1e1a_Data_P2_aIneIn_Sector8->Draw();
      StackColl_1e1a_P2[11]->Draw("HISTSAME");
      h_1e1a_Data_P2_aIneIn_Sector8->Draw("SAME");
      Legend_1e1a_P2[11]->Draw();
      ChiSquares_1e1a_P2[11]->Draw();
      c27_1e1a->SaveAs("Images/png/1e1a/P2/12 - Sector8 - Alpha In Electron In.png");
      c27_1e1a->SaveAs("Images/eps/1e1a/P2/12 - Sector8 - Alpha In Electron In.eps");
      c27_1e1a->SaveAs("Images/gif/1e1a/P2/12 - Sector8 - Alpha In Electron In.gif");
    }

    TCanvas* c28_1e1a = new TCanvas("c28_1e1a"," All Events Sector6 P2",200,10,1200,800);
    h_1e1a_Data_P2_AllEvents_Sector6->SetMarkerStyle(20);
    h_1e1a_Data_P2_AllEvents_Sector6->GetYaxis()->SetRangeUser(0,200);
    h_1e1a_Data_P2_AllEvents_Sector6->Draw();
    StackColl_1e1a_P2[12]->Draw("HISTSAME");
    h_1e1a_Data_P2_AllEvents_Sector6->Draw("SAME");
    Legend_1e1a_P2[12]->Draw();
    ChiSquares_1e1a_P2[12]->Draw();
    c28_1e1a->SaveAs("Images/png/1e1a/P2/13 - Sector6 - All Events.png");
    c28_1e1a->SaveAs("Images/eps/1e1a/P2/13 - Sector6 - All Events.eps");
    c28_1e1a->SaveAs("Images/gif/1e1a/P2/13 - Sector6 - All Events.gif");

    TCanvas* c29_1e1a = new TCanvas("c29_1e1a"," All Events Sector7 P2",200,10,1200,800);
    h_1e1a_Data_P2_AllEvents_Sector7->SetMarkerStyle(20);
    h_1e1a_Data_P2_AllEvents_Sector7->GetYaxis()->SetRangeUser(0,200);
    h_1e1a_Data_P2_AllEvents_Sector7->Draw();
    StackColl_1e1a_P2[13]->Draw("HISTSAME");
    h_1e1a_Data_P2_AllEvents_Sector7->Draw("SAME");
    Legend_1e1a_P2[13]->Draw();
    ChiSquares_1e1a_P2[13]->Draw();
    c29_1e1a->SaveAs("Images/png/1e1a/P2/14 - Sector7 - All Events.png");
    c29_1e1a->SaveAs("Images/eps/1e1a/P2/14 - Sector7 - All Events.eps");
    c29_1e1a->SaveAs("Images/gif/1e1a/P2/14 - Sector7 - All Events.gif");

    TCanvas* c30_1e1a = new TCanvas("c30_1e1a"," All Events Sector8 P2",200,10,1200,800);
    h_1e1a_Data_P2_AllEvents_Sector8->SetMarkerStyle(20);
    h_1e1a_Data_P2_AllEvents_Sector8->GetYaxis()->SetRangeUser(0,80);
    h_1e1a_Data_P2_AllEvents_Sector8->Draw();
    StackColl_1e1a_P2[14]->Draw("HISTSAME");
    h_1e1a_Data_P2_AllEvents_Sector8->Draw("SAME");
    Legend_1e1a_P2[14]->Draw();
    ChiSquares_1e1a_P2[14]->Draw();
    c30_1e1a->SaveAs("Images/png/1e1a/P2/15 - Sector8 - All Events.png");
    c30_1e1a->SaveAs("Images/eps/1e1a/P2/15 - Sector8 - All Events.eps");
    c30_1e1a->SaveAs("Images/gif/1e1a/P2/15 - Sector8 - All Events.gif");
  }

  // Draw Output - OCE
  if(DrawOCEPlots){
    TCanvas* c1_OCE = new TCanvas("c1_OCE","Total Energy - P1_OCE_Inner",10,10,1200,800);
    h_OCE_Data_P1_Inner->SetMarkerStyle(20);
    h_OCE_Data_P1_Inner->Draw();
    StackColl_OCE[0]->Draw("HISTSAME");
    h_OCE_Data_P1_Inner->Draw("SAME");
    Legend_OCE[0]->Draw();
    ChiSquares_OCE[0]->Draw();
    c1_OCE->SaveAs("Images/png/OCE/1 - P1 Total Energy Inner.png");
    c1_OCE->SaveAs("Images/eps/OCE/1 - P1 Total Energy Inner.eps");
    c1_OCE->SaveAs("Images/gif/OCE/1 - P1 Total Energy Inner.gif");

    TCanvas* c2_OCE = new TCanvas("c2_OCE","Total Energy - P1_OCE_Outer",10,10,1200,800);
    h_OCE_Data_P1_Outer->SetMarkerStyle(20);
    h_OCE_Data_P1_Outer->Draw();
    StackColl_OCE[1]->Draw("HISTSAME");
    h_OCE_Data_P1_Outer->Draw("SAME");
    Legend_OCE[1]->Draw();
    ChiSquares_OCE[1]->Draw();
    c2_OCE->SaveAs("Images/png/OCE/2 - P1 Total Energy Outer.png");
    c2_OCE->SaveAs("Images/eps/OCE/2 - P1 Total Energy Outer.eps");
    c2_OCE->SaveAs("Images/gif/OCE/2 - P1 Total Energy Outer.gif");

    TCanvas* c3_OCE = new TCanvas("c3_OCE","Total Energy - P1_OCE_Petal",10,10,1200,800);
    h_OCE_Data_P1_Petal->SetMarkerStyle(20);
    h_OCE_Data_P1_Petal->Draw();
    StackColl_OCE[2]->Draw("HISTSAME");
    h_OCE_Data_P1_Petal->Draw("SAME");
    Legend_OCE[2]->Draw();
    ChiSquares_OCE[2]->Draw();
    c3_OCE->SaveAs("Images/png/OCE/3 - P1 Total Energy Petal.png");
    c3_OCE->SaveAs("Images/eps/OCE/3 - P1 Total Energy Petal.eps");
    c3_OCE->SaveAs("Images/gif/OCE/3 - P1 Total Energy Petal.gif");

    TCanvas* c4_OCE = new TCanvas("c4_OCE","Total Energy - P2_OCE_Inner",10,10,1200,800);
    h_OCE_Data_P2_Inner->SetMarkerStyle(20);
    h_OCE_Data_P2_Inner->Draw();
    StackColl_OCE[3]->Draw("HISTSAME");
    h_OCE_Data_P2_Inner->Draw("SAME");
    Legend_OCE[3]->Draw();
    ChiSquares_OCE[3]->Draw();
    c4_OCE->SaveAs("Images/png/OCE/4 - P2 Total Energy Inner.png");
    c4_OCE->SaveAs("Images/eps/OCE/4 - P2 Total Energy Inner.eps");
    c4_OCE->SaveAs("Images/gif/OCE/4 - P2 Total Energy Inner.gif");

    TCanvas* c5_OCE = new TCanvas("c5_OCE","Total Energy - P2_OCE_Outer",10,10,1200,800);
    h_OCE_Data_P2_Outer->SetMarkerStyle(20);
    h_OCE_Data_P2_Outer->Draw();
    StackColl_OCE[4]->Draw("HISTSAME");
    h_OCE_Data_P2_Outer->Draw("SAME");
    Legend_OCE[4]->Draw();
    ChiSquares_OCE[4]->Draw();
    c5_OCE->SaveAs("Images/png/OCE/5 - P2 Total Energy Outer.png");
    c5_OCE->SaveAs("Images/eps/OCE/5 - P2 Total Energy Outer.eps");
    c5_OCE->SaveAs("Images/gif/OCE/5 - P2 Total Energy Outer.gif");

    TCanvas* c6_OCE = new TCanvas("c6_OCE","Total Energy - P2_OCE_Petal",10,10,1200,800);
    h_OCE_Data_P2_Petal->SetMarkerStyle(20);
    h_OCE_Data_P2_Petal->Draw();
    StackColl_OCE[5]->Draw("HISTSAME");
    h_OCE_Data_P2_Petal->Draw("SAME");
    Legend_OCE[5]->Draw();
    ChiSquares_OCE[5]->Draw();
    c6_OCE->SaveAs("Images/png/OCE/6 - P2 Total Energy Petal.png");
    c6_OCE->SaveAs("Images/eps/OCE/6 - P2 Total Energy Petal.eps");
    c6_OCE->SaveAs("Images/gif/OCE/6 - P2 Total Energy Petal.gif");

    if(!DrawSummaryPlots){
      TCanvas* c1_1_OCE = new TCanvas("c1_1_OCE","Total Energy - P1_OCE_Inner",10,10,1200,800);
      c1_1_OCE->SetLogy();
      h_OCE_Data_P1_Inner->Draw();
      StackColl_OCE[0]->Draw("HISTSAME");
      h_OCE_Data_P1_Inner->Draw("SAME");
      LegendLog_OCE[0]->Draw();
      ChiSquaresLog_OCE[0]->Draw();
      c1_1_OCE->SaveAs("Images/png/OCE/1 - P1 Total Energy Inner Log.png");
      c1_1_OCE->SaveAs("Images/eps/OCE/1 - P1 Total Energy Inner Log.eps");
      c1_1_OCE->SaveAs("Images/gif/OCE/1 - P1 Total Energy Inner Log.gif");

      TCanvas* c2_1_OCE = new TCanvas("c2_1_OCE","Total Energy - P1_OCE_Outer",10,10,1200,800);
      c2_1_OCE->SetLogy();
      h_OCE_Data_P1_Outer->Draw();
      StackColl_OCE[1]->Draw("HISTSAME");
      h_OCE_Data_P1_Outer->Draw("SAME");
      LegendLog_OCE[1]->Draw();
      ChiSquaresLog_OCE[1]->Draw();
      c2_1_OCE->SaveAs("Images/png/OCE/2 - P1 Total Energy Outer Log.png");
      c2_1_OCE->SaveAs("Images/eps/OCE/2 - P1 Total Energy Outer Log.eps");
      c2_1_OCE->SaveAs("Images/gif/OCE/2 - P1 Total Energy Outer Log.gif");

      TCanvas* c3_1_OCE = new TCanvas("c3_1_OCE","Total Energy - P1_OCE_Petal",10,10,1200,800);
      c3_1_OCE->SetLogy();
      h_OCE_Data_P1_Petal->Draw();
      StackColl_OCE[2]->Draw("HISTSAME");
      h_OCE_Data_P1_Petal->Draw("SAME");
      LegendLog_OCE[2]->Draw();
      ChiSquaresLog_OCE[2]->Draw();
      c3_1_OCE->SaveAs("Images/png/OCE/3 - P1 Total Energy Petal Log.png");
      c3_1_OCE->SaveAs("Images/eps/OCE/3 - P1 Total Energy Petal Log.eps");
      c3_1_OCE->SaveAs("Images/gif/OCE/3 - P1 Total Energy Petal Log.gif");

      TCanvas* c4_1_OCE = new TCanvas("c4_1_OCE","Total Energy - P2_OCE_Inner",10,10,1200,800);
      c4_1_OCE->SetLogy();
      h_OCE_Data_P2_Inner->Draw();
      StackColl_OCE[3]->Draw("HISTSAME");
      h_OCE_Data_P2_Inner->Draw("SAME");
      LegendLog_OCE[3]->Draw();
      ChiSquaresLog_OCE[3]->Draw();
      c4_1_OCE->SaveAs("Images/png/OCE/4 - P2 Total Energy Inner Log.png");
      c4_1_OCE->SaveAs("Images/eps/OCE/4 - P2 Total Energy Inner Log.eps");
      c4_1_OCE->SaveAs("Images/gif/OCE/4 - P2 Total Energy Inner Log.gif");

      TCanvas* c5_1_OCE = new TCanvas("c5_1_OCE","Total Energy - P2_OCE_Outer",10,10,1200,800);
      c5_1_OCE->SetLogy();
      h_OCE_Data_P2_Outer->Draw();
      StackColl_OCE[4]->Draw("HISTSAME");
      h_OCE_Data_P2_Outer->Draw("SAME");
      LegendLog_OCE[4]->Draw();
      ChiSquaresLog_OCE[4]->Draw();
      c5_1_OCE->SaveAs("Images/png/OCE/5 - P2 Total Energy Outer Log.png");
      c5_1_OCE->SaveAs("Images/eps/OCE/5 - P2 Total Energy Outer Log.eps");
      c5_1_OCE->SaveAs("Images/gif/OCE/5 - P2 Total Energy Outer Log.gif");

      TCanvas* c6_1_OCE = new TCanvas("c6_1_OCE","Total Energy - P2_OCE_Petal",10,10,1200,800);
      c6_1_OCE->SetLogy();
      h_OCE_Data_P2_Petal->Draw();
      StackColl_OCE[5]->Draw("HISTSAME");
      h_OCE_Data_P2_Petal->Draw("SAME");
      LegendLog_OCE[5]->Draw();
      ChiSquaresLog_OCE[5]->Draw();
      c6_1_OCE->SaveAs("Images/png/OCE/6 - P2 Total Energy Petal Log.png");
      c6_1_OCE->SaveAs("Images/eps/OCE/6 - P2 Total Energy Petal Log.eps");
      c6_1_OCE->SaveAs("Images/gif/OCE/6 - P2 Total Energy Petal Log.gif");
    }
  }

  // Draw Output - ExtEG
  if(DrawExtEGPlots){
    TCanvas* c1_ExtEG = new TCanvas("c1_ExtEG","Total Energy - P1_ExtEG_Inner",10,10,1200,800);
    h_ExtEG_Data_P1_Inner->SetMarkerStyle(20);
    h_ExtEG_Data_P1_Inner->Draw();
    StackColl_ExtEG[0]->Draw("HISTSAME");
    h_ExtEG_Data_P1_Inner->Draw("SAME");
    Legend_ExtEG[0]->Draw();
    ChiSquares_ExtEG[0]->Draw();
    c1_ExtEG->SaveAs("Images/png/ExtEG/1 - P1 Total Energy Inner.png");
    c1_ExtEG->SaveAs("Images/eps/ExtEG/1 - P1 Total Energy Inner.eps");
    c1_ExtEG->SaveAs("Images/gif/ExtEG/1 - P1 Total Energy Inner.gif");

    TCanvas* c2_ExtEG = new TCanvas("c2_ExtEG","Total Energy - P1_ExtEG_Outer",10,10,1200,800);
    h_ExtEG_Data_P1_Outer->SetMarkerStyle(20);
    h_ExtEG_Data_P1_Outer->Draw();
    StackColl_ExtEG[1]->Draw("HISTSAME");
    h_ExtEG_Data_P1_Outer->Draw("SAME");
    Legend_ExtEG[1]->Draw();
    ChiSquares_ExtEG[1]->Draw();
    c2_ExtEG->SaveAs("Images/png/ExtEG/2 - P1 Total Energy Outer.png");
    c2_ExtEG->SaveAs("Images/eps/ExtEG/2 - P1 Total Energy Outer.eps");
    c2_ExtEG->SaveAs("Images/gif/ExtEG/2 - P1 Total Energy Outer.gif");

    TCanvas* c3_ExtEG = new TCanvas("c3_ExtEG","Total Energy - P1_ExtEG_Petal",10,10,1200,800);
    h_ExtEG_Data_P1_Petal->SetMarkerStyle(20);
    h_ExtEG_Data_P1_Petal->Draw();
    StackColl_ExtEG[2]->Draw("HISTSAME");
    h_ExtEG_Data_P1_Petal->Draw("SAME");
    Legend_ExtEG[2]->Draw();
    ChiSquares_ExtEG[2]->Draw();
    c3_ExtEG->SaveAs("Images/png/ExtEG/3 - P1 Total Energy Petal.png");
    c3_ExtEG->SaveAs("Images/eps/ExtEG/3 - P1 Total Energy Petal.eps");
    c3_ExtEG->SaveAs("Images/gif/ExtEG/3 - P1 Total Energy Petal.gif");

    TCanvas* c4_ExtEG = new TCanvas("c4_ExtEG","Total Energy - P2_ExtEG_Inner",10,10,1200,800);
    h_ExtEG_Data_P2_Inner->SetMarkerStyle(20);
    h_ExtEG_Data_P2_Inner->Draw();
    StackColl_ExtEG[3]->Draw("HISTSAME");
    h_ExtEG_Data_P2_Inner->Draw("SAME");
    Legend_ExtEG[3]->Draw();
    ChiSquares_ExtEG[3]->Draw();
    c4_ExtEG->SaveAs("Images/png/ExtEG/4 - P2 Total Energy Inner.png");
    c4_ExtEG->SaveAs("Images/eps/ExtEG/4 - P2 Total Energy Inner.eps");
    c4_ExtEG->SaveAs("Images/gif/ExtEG/4 - P2 Total Energy Inner.gif");

    TCanvas* c5_ExtEG = new TCanvas("c5_ExtEG","Total Energy - P2_ExtEG_Outer",10,10,1200,800);
    h_ExtEG_Data_P2_Outer->SetMarkerStyle(20);
    h_ExtEG_Data_P2_Outer->Draw();
    StackColl_ExtEG[4]->Draw("HISTSAME");
    h_ExtEG_Data_P2_Outer->Draw("SAME");
    Legend_ExtEG[4]->Draw();
    ChiSquares_ExtEG[4]->Draw();
    c5_ExtEG->SaveAs("Images/png/ExtEG/5 - P2 Total Energy Outer.png");
    c5_ExtEG->SaveAs("Images/eps/ExtEG/5 - P2 Total Energy Outer.eps");
    c5_ExtEG->SaveAs("Images/gif/ExtEG/5 - P2 Total Energy Outer.gif");

    TCanvas* c6_ExtEG = new TCanvas("c6_ExtEG","Total Energy - P2_ExtEG_Petal",10,10,1200,800);
    h_ExtEG_Data_P2_Petal->SetMarkerStyle(20);
    h_ExtEG_Data_P2_Petal->Draw();
    StackColl_ExtEG[5]->Draw("HISTSAME");
    h_ExtEG_Data_P2_Petal->Draw("SAME");
    Legend_ExtEG[5]->Draw();
    ChiSquares_ExtEG[5]->Draw();
    c6_ExtEG->SaveAs("Images/png/ExtEG/6 - P2 Total Energy Petal.png");
    c6_ExtEG->SaveAs("Images/eps/ExtEG/6 - P2 Total Energy Petal.eps");
    c6_ExtEG->SaveAs("Images/gif/ExtEG/6 - P2 Total Energy Petal.gif");

    if(!DrawSummaryPlots){
      TCanvas* c1_1_ExtEG = new TCanvas("c1_1_ExtEG","Total Energy - P1_ExtEG_Inner",10,10,1200,800);
      c1_1_ExtEG->SetLogy();
      h_ExtEG_Data_P1_Inner->GetYaxis()->SetRangeUser(0.3,10000);
      h_ExtEG_Data_P1_Inner->Draw();
      StackColl_ExtEG[0]->Draw("HISTSAME");
      h_ExtEG_Data_P1_Inner->Draw("SAME");
      LegendLog_ExtEG[0]->Draw();
      ChiSquaresLog_ExtEG[0]->Draw();
      c1_1_ExtEG->SaveAs("Images/png/ExtEG/1 - P1 Total Energy Inner Log.png");
      c1_1_ExtEG->SaveAs("Images/eps/ExtEG/1 - P1 Total Energy Inner Log.eps");
      c1_1_ExtEG->SaveAs("Images/gif/ExtEG/1 - P1 Total Energy Inner Log.gif");

      TCanvas* c2_1_ExtEG = new TCanvas("c2_1_ExtEG","Total Energy - P1_ExtEG_Outer",10,10,1200,800);
      c2_1_ExtEG->SetLogy();
      h_ExtEG_Data_P1_Outer->GetYaxis()->SetRangeUser(0.3,10000);
      h_ExtEG_Data_P1_Outer->Draw();
      StackColl_ExtEG[1]->Draw("HISTSAME");
      h_ExtEG_Data_P1_Outer->Draw("SAME");
      LegendLog_ExtEG[1]->Draw();
      ChiSquaresLog_ExtEG[1]->Draw();
      c2_1_ExtEG->SaveAs("Images/png/ExtEG/2 - P1 Total Energy Outer Log.png");
      c2_1_ExtEG->SaveAs("Images/eps/ExtEG/2 - P1 Total Energy Outer Log.eps");
      c2_1_ExtEG->SaveAs("Images/gif/ExtEG/2 - P1 Total Energy Outer Log.gif");

      TCanvas* c3_1_ExtEG = new TCanvas("c3_1_ExtEG","Total Energy - P1_ExtEG_Petal",10,10,1200,800);
      c3_1_ExtEG->SetLogy();
      h_ExtEG_Data_P1_Petal->GetYaxis()->SetRangeUser(0.3,10000);
      h_ExtEG_Data_P1_Petal->Draw();
      StackColl_ExtEG[2]->Draw("HISTSAME");
      h_ExtEG_Data_P1_Petal->Draw("SAME");
      LegendLog_ExtEG[2]->Draw();
      ChiSquaresLog_ExtEG[2]->Draw();
      c3_1_ExtEG->SaveAs("Images/png/ExtEG/3 - P1 Total Energy Petal Log.png");
      c3_1_ExtEG->SaveAs("Images/eps/ExtEG/3 - P1 Total Energy Petal Log.eps");
      c3_1_ExtEG->SaveAs("Images/gif/ExtEG/3 - P1 Total Energy Petal Log.gif");

      TCanvas* c4_1_ExtEG = new TCanvas("c4_1_ExtEG","Total Energy - P2_ExtEG_Inner",10,10,1200,800);
      c4_1_ExtEG->SetLogy();
      h_ExtEG_Data_P2_Inner->GetYaxis()->SetRangeUser(0.3,10000);
      h_ExtEG_Data_P2_Inner->Draw();
      StackColl_ExtEG[3]->Draw("HISTSAME");
      h_ExtEG_Data_P2_Inner->Draw("SAME");
      LegendLog_ExtEG[3]->Draw();
      ChiSquaresLog_ExtEG[3]->Draw();
      c4_1_ExtEG->SaveAs("Images/png/ExtEG/4 - P2 Total Energy Inner Log.png");
      c4_1_ExtEG->SaveAs("Images/eps/ExtEG/4 - P2 Total Energy Inner Log.eps");
      c4_1_ExtEG->SaveAs("Images/gif/ExtEG/4 - P2 Total Energy Inner Log.gif");

      TCanvas* c5_1_ExtEG = new TCanvas("c5_1_ExtEG","Total Energy - P2_ExtEG_Outer",10,10,1200,800);
      c5_1_ExtEG->SetLogy();
      h_ExtEG_Data_P2_Outer->GetYaxis()->SetRangeUser(0.3,10000);
      h_ExtEG_Data_P2_Outer->Draw();
      StackColl_ExtEG[4]->Draw("HISTSAME");
      h_ExtEG_Data_P2_Outer->Draw("SAME");
      LegendLog_ExtEG[4]->Draw();
      ChiSquaresLog_ExtEG[4]->Draw();
      c5_1_ExtEG->SaveAs("Images/png/ExtEG/5 - P2 Total Energy Outer Log.png");
      c5_1_ExtEG->SaveAs("Images/eps/ExtEG/5 - P2 Total Energy Outer Log.eps");
      c5_1_ExtEG->SaveAs("Images/gif/ExtEG/5 - P2 Total Energy Outer Log.gif");

      TCanvas* c6_1_ExtEG = new TCanvas("c6_1_ExtEG","Total Energy - P2_ExtEG_Petal",10,10,1200,800);
      c6_1_ExtEG->SetLogy();
      h_ExtEG_Data_P2_Petal->GetYaxis()->SetRangeUser(0.3,10000);
      h_ExtEG_Data_P2_Petal->Draw();
      StackColl_ExtEG[5]->Draw("HISTSAME");
      h_ExtEG_Data_P2_Petal->Draw("SAME");
      LegendLog_ExtEG[5]->Draw();
      ChiSquaresLog_ExtEG[5]->Draw();
      c6_1_ExtEG->SaveAs("Images/png/ExtEG/6 - P2 Total Energy Petal Log.png");
      c6_1_ExtEG->SaveAs("Images/eps/ExtEG/6 - P2 Total Energy Petal Log.eps");
      c6_1_ExtEG->SaveAs("Images/gif/ExtEG/6 - P2 Total Energy Petal Log.gif");
    }
  }

  // Draw Output - 2b2n
  if(Draw2b2nPlots){
    TCanvas* c1_2b2n = new TCanvas("c1_2b2n","Total Energy - 2b2n SeOld",10,10,1200,800);
    h_2b2n_Data_SeOld->SetMarkerStyle(20);
    h_2b2n_Data_SeOld->Draw();
    StackColl_2b2n[0]->Draw("HISTSAME");
    h_2b2n_Data_SeOld->Draw("SAME");
    Legend_2b2n[0]->Draw();
    ChiSquares_2b2n[0]->Draw();
    c1_2b2n->SaveAs("Images/png/2b2n/1 - Total Energy SeOld.png");
    c1_2b2n->SaveAs("Images/eps/2b2n/1 - Total Energy SeOld.eps");
    c1_2b2n->SaveAs("Images/gif/2b2n/1 - Total Energy SeOld.gif");

    TCanvas* c2_2b2n = new TCanvas("c2_2b2n","Total Energy - 2b2n SeNew",10,10,1200,800);
    h_2b2n_Data_SeNew->SetMarkerStyle(20);
    h_2b2n_Data_SeNew->Draw();
    StackColl_2b2n[1]->Draw("HISTSAME");
    h_2b2n_Data_SeNew->Draw("SAME");
    Legend_2b2n[1]->Draw();
    ChiSquares_2b2n[1]->Draw();
    c2_2b2n->SaveAs("Images/png/2b2n/1 - Total Energy SeNew.png");
    c2_2b2n->SaveAs("Images/eps/2b2n/1 - Total Energy SeNew.eps");
    c2_2b2n->SaveAs("Images/gif/2b2n/1 - Total Energy SeNew.gif");

    TCanvas* c3_2b2n = new TCanvas("c3_2b2n","Total Energy - 2b2n SeOld",10,10,1200,800);
    h_2b2n_SingleEnergy_Data_SeOld->SetMarkerStyle(20);
    h_2b2n_SingleEnergy_Data_SeOld->SetMinimum(0);
    h_2b2n_SingleEnergy_Data_SeOld->Draw();
    StackColl_2b2n[2]->Draw("HISTSAME");
    h_2b2n_SingleEnergy_Data_SeOld->Draw("SAME");
    Legend_2b2n[2]->Draw();
    ChiSquares_2b2n[2]->Draw();
    c3_2b2n->SaveAs("Images/png/2b2n/2 - Single Energy SeOld.png");
    c3_2b2n->SaveAs("Images/eps/2b2n/2 - Single Energy SeOld.eps");
    c3_2b2n->SaveAs("Images/gif/2b2n/2 - Single Energy SeOld.gif");

    TCanvas* c4_2b2n = new TCanvas("c4_2b2n","Total Energy - 2b2n SeNew",10,10,1200,800);
    h_2b2n_SingleEnergy_Data_SeNew->SetMarkerStyle(20);
    h_2b2n_SingleEnergy_Data_SeNew->SetMinimum(0);
    h_2b2n_SingleEnergy_Data_SeNew->Draw();
    StackColl_2b2n[3]->Draw("HISTSAME");
    h_2b2n_SingleEnergy_Data_SeNew->Draw("SAME");
    Legend_2b2n[3]->Draw();
    ChiSquares_2b2n[3]->Draw();
    c4_2b2n->SaveAs("Images/png/2b2n/2 - Single Energy SeNew.png");
    c4_2b2n->SaveAs("Images/eps/2b2n/2 - Single Energy SeNew.eps");
    c4_2b2n->SaveAs("Images/gif/2b2n/2 - Single Energy SeNew.gif");

    TCanvas* c5_2b2n = new TCanvas("c5_2b2n","Min Energy - 2b2n SeOld",10,10,1200,800);
    h_2b2n_MinEnergy_Data_SeOld->SetMarkerStyle(20);
    h_2b2n_MinEnergy_Data_SeOld->SetMinimum(0);
    h_2b2n_MinEnergy_Data_SeOld->Draw();
    StackColl_2b2n[4]->Draw("HISTSAME");
    h_2b2n_MinEnergy_Data_SeOld->Draw("SAME");
    Legend_2b2n[4]->Draw();
    ChiSquares_2b2n[4]->Draw();
    c5_2b2n->SaveAs("Images/png/2b2n/3 - Min Energy SeOld.png");
    c5_2b2n->SaveAs("Images/eps/2b2n/3 - Min Energy SeOld.eps");
    c5_2b2n->SaveAs("Images/gif/2b2n/3 - Min Energy SeOld.gif");

    TCanvas* c6_2b2n = new TCanvas("c6_2b2n","Min Energy - 2b2n SeNew",10,10,1200,800);
    h_2b2n_MinEnergy_Data_SeNew->SetMarkerStyle(20);
    h_2b2n_MinEnergy_Data_SeNew->SetMinimum(0);
    h_2b2n_MinEnergy_Data_SeNew->Draw();
    StackColl_2b2n[5]->Draw("HISTSAME");
    h_2b2n_MinEnergy_Data_SeNew->Draw("SAME");
    Legend_2b2n[5]->Draw();
    ChiSquares_2b2n[5]->Draw();
    c6_2b2n->SaveAs("Images/png/2b2n/3 - Min Energy SeNew.png");
    c6_2b2n->SaveAs("Images/eps/2b2n/3 - Min Energy SeNew.eps");
    c6_2b2n->SaveAs("Images/gif/2b2n/3 - Min Energy SeNew.gif");

    TCanvas* c7_2b2n = new TCanvas("c7_2b2n","Max Energy - 2b2n SeOld",10,10,1200,800);
    h_2b2n_MaxEnergy_Data_SeOld->SetMarkerStyle(20);
    h_2b2n_MaxEnergy_Data_SeOld->SetMinimum(0);
    h_2b2n_MaxEnergy_Data_SeOld->Draw();
    StackColl_2b2n[6]->Draw("HISTSAME");
    h_2b2n_MaxEnergy_Data_SeOld->Draw("SAME");
    Legend_2b2n[6]->Draw();
    ChiSquares_2b2n[6]->Draw();
    c7_2b2n->SaveAs("Images/png/2b2n/4 - Max Energy SeOld.png");
    c7_2b2n->SaveAs("Images/eps/2b2n/4 - Max Energy SeOld.eps");
    c7_2b2n->SaveAs("Images/gif/2b2n/4 - Max Energy SeOld.gif");

    TCanvas* c8_2b2n = new TCanvas("c8_2b2n","Max Energy - 2b2n SeNew",10,10,1200,800);
    h_2b2n_MaxEnergy_Data_SeNew->SetMarkerStyle(20);
    h_2b2n_MaxEnergy_Data_SeNew->SetMinimum(0);
    h_2b2n_MaxEnergy_Data_SeNew->Draw();
    StackColl_2b2n[7]->Draw("HISTSAME");
    h_2b2n_MaxEnergy_Data_SeNew->Draw("SAME");
    Legend_2b2n[7]->Draw();
    ChiSquares_2b2n[7]->Draw();
    c8_2b2n->SaveAs("Images/png/2b2n/4 - Max Energy SeNew.png");
    c8_2b2n->SaveAs("Images/eps/2b2n/4 - Max Energy SeNew.eps");
    c8_2b2n->SaveAs("Images/gif/2b2n/4 - Max Energy SeNew.gif");

    if(!DrawSummaryPlots){
      TCanvas* c1_2b2n_log = new TCanvas("c1_2b2n_log","Total Total Energy - 2b2n SeOld",10,10,1200,800);
      c1_2b2n_log->SetLogy();
      h_2b2n_Data_SeOld->GetYaxis()->SetRangeUser(0.3,1e5);
      h_2b2n_Data_SeOld->Draw();
      StackColl_2b2n[0]->Draw("HISTSAME");
      h_2b2n_Data_SeOld->Draw("SAME");
      Legend_2b2n[0]->Draw();
      ChiSquares_2b2n[0]->Draw();
      c1_2b2n_log->SaveAs("Images/png/2b2n/1 - Total Energy SeOld Log.png");
      c1_2b2n_log->SaveAs("Images/eps/2b2n/1 - Total Energy SeOld Log.eps");
      c1_2b2n_log->SaveAs("Images/gif/2b2n/1 - Total Energy SeOld Log.gif");

      TCanvas* c2_2b2n_log = new TCanvas("c2_2b2n_log","Total Total Energy - 2b2n SeNew",10,10,1200,800);
      c2_2b2n_log->SetLogy();
      h_2b2n_Data_SeNew->GetYaxis()->SetRangeUser(0.3,1e5);
      h_2b2n_Data_SeNew->Draw();
      StackColl_2b2n[1]->Draw("HISTSAME");
      h_2b2n_Data_SeNew->Draw("SAME");
      Legend_2b2n[1]->Draw();
      ChiSquares_2b2n[1]->Draw();
      c2_2b2n_log->SaveAs("Images/png/2b2n/1 - Total Energy SeNew Log.png");
      c2_2b2n_log->SaveAs("Images/eps/2b2n/1 - Total Energy SeNew Log.eps");
      c2_2b2n_log->SaveAs("Images/gif/2b2n/1 - Total Energy SeNew Log.gif");
    
      TCanvas* c3_2b2n_log = new TCanvas("c3_2b2n_log","Single Energy - 2b2n SeOld",10,10,1200,800);
      c3_2b2n_log->SetLogy();
      h_2b2n_SingleEnergy_Data_SeOld->GetYaxis()->SetRangeUser(0.3,1e5);
      h_2b2n_SingleEnergy_Data_SeOld->Draw();
      StackColl_2b2n[2]->Draw("HISTSAME");
      h_2b2n_SingleEnergy_Data_SeOld->Draw("SAME");
      Legend_2b2n[2]->Draw();
      ChiSquares_2b2n[2]->Draw();
      c3_2b2n_log->SaveAs("Images/png/2b2n/2 - Single Energy SeOld Log.png");
      c3_2b2n_log->SaveAs("Images/eps/2b2n/2 - Single Energy SeOld Log.eps");
      c3_2b2n_log->SaveAs("Images/gif/2b2n/2 - Single Energy SeOld Log.gif");

      TCanvas* c4_2b2n_log = new TCanvas("c4_2b2n_log","Single Energy - 2b2n SeNew",10,10,1200,800);
      c4_2b2n_log->SetLogy();
      h_2b2n_SingleEnergy_Data_SeNew->GetYaxis()->SetRangeUser(0.3,1e5);
      h_2b2n_SingleEnergy_Data_SeNew->Draw();
      StackColl_2b2n[3]->Draw("HISTSAME");
      h_2b2n_SingleEnergy_Data_SeNew->Draw("SAME");
      Legend_2b2n[3]->Draw();
      ChiSquares_2b2n[3]->Draw();
      c4_2b2n_log->SaveAs("Images/png/2b2n/2 - Single Energy SeNew Log.png");
      c4_2b2n_log->SaveAs("Images/eps/2b2n/2 - Single Energy SeNew Log.eps");
      c4_2b2n_log->SaveAs("Images/gif/2b2n/2 - Single Energy SeNew Log.gif");

      TCanvas* c5_2b2n_log = new TCanvas("c5_2b2n_log","Min Energy - 2b2n SeOld",10,10,1200,800);
      c5_2b2n_log->SetLogy();
      h_2b2n_MinEnergy_Data_SeOld->GetYaxis()->SetRangeUser(0.3,1e5);
      h_2b2n_MinEnergy_Data_SeOld->Draw();
      StackColl_2b2n[4]->Draw("HISTSAME");
      h_2b2n_MinEnergy_Data_SeOld->Draw("SAME");
      Legend_2b2n[4]->Draw();
      ChiSquares_2b2n[4]->Draw();
      c5_2b2n_log->SaveAs("Images/png/2b2n/3 - Min Energy SeOld Log.png");
      c5_2b2n_log->SaveAs("Images/eps/2b2n/3 - Min Energy SeOld Log.eps");
      c5_2b2n_log->SaveAs("Images/gif/2b2n/3 - Min Energy SeOld Log.gif");

      TCanvas* c6_2b2n_log = new TCanvas("c6_2b2n_log","Min Energy - 2b2n SeNew",10,10,1200,800);
      c6_2b2n_log->SetLogy();
      h_2b2n_MinEnergy_Data_SeNew->GetYaxis()->SetRangeUser(0.3,1e5);
      h_2b2n_MinEnergy_Data_SeNew->Draw();
      StackColl_2b2n[5]->Draw("HISTSAME");
      h_2b2n_MinEnergy_Data_SeNew->Draw("SAME");
      Legend_2b2n[5]->Draw();
      ChiSquares_2b2n[5]->Draw();
      c6_2b2n_log->SaveAs("Images/png/2b2n/3 - Min Energy SeNew Log.png");
      c6_2b2n_log->SaveAs("Images/eps/2b2n/3 - Min Energy SeNew Log.eps");
      c6_2b2n_log->SaveAs("Images/gif/2b2n/3 - Min Energy SeNew Log.gif");

      TCanvas* c7_2b2n_log = new TCanvas("c7_2b2n_log","Max Energy - 2b2n SeOld",10,10,1200,800);
      c7_2b2n_log->SetLogy();
      h_2b2n_MaxEnergy_Data_SeOld->GetYaxis()->SetRangeUser(0.3,1e5);
      h_2b2n_MaxEnergy_Data_SeOld->Draw();
      StackColl_2b2n[6]->Draw("HISTSAME");
      h_2b2n_MaxEnergy_Data_SeOld->Draw("SAME");
      Legend_2b2n[6]->Draw();
      ChiSquares_2b2n[6]->Draw();
      c7_2b2n_log->SaveAs("Images/png/2b2n/4 - Max Energy SeOld Log.png");
      c7_2b2n_log->SaveAs("Images/eps/2b2n/4 - Max Energy SeOld Log.eps");
      c7_2b2n_log->SaveAs("Images/gif/2b2n/4 - Max Energy SeOld Log.gif");

      TCanvas* c8_2b2n_log = new TCanvas("c8_2b2n_log","Max Energy - 2b2n SeNew",10,10,1200,800);
      c8_2b2n_log->SetLogy();
      h_2b2n_MaxEnergy_Data_SeNew->GetYaxis()->SetRangeUser(0.3,1e5);
      h_2b2n_MaxEnergy_Data_SeNew->Draw();
      StackColl_2b2n[7]->Draw("HISTSAME");
      h_2b2n_MaxEnergy_Data_SeNew->Draw("SAME");
      Legend_2b2n[7]->Draw();
      ChiSquares_2b2n[7]->Draw();
      c8_2b2n_log->SaveAs("Images/png/2b2n/4 - Max Energy SeNew Log.png");
      c8_2b2n_log->SaveAs("Images/eps/2b2n/4 - Max Energy SeNew Log.eps");
      c8_2b2n_log->SaveAs("Images/gif/2b2n/4 - Max Energy SeNew Log.gif");
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

