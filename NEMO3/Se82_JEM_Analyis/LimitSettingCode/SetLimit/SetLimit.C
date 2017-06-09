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
#include <fstream>
#include "../Machinery/addBackgrounds_2b2n.h"
#include "../Machinery/ReadWriteActivities.h"
#include "../Machinery/LimitCalculationFunctions.h"

// Set Global variables to be used by all
Int_t TotalAccptRunTime = 167629292;
Int_t TotalAccptDeadTime = 1867931;
const Int_t AccptRunTime = TotalAccptRunTime - TotalAccptDeadTime;
TFile* infile_2b2n = new TFile("../Histograms/Histograms_2b2n.root","READ");

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

double WindowMethod_FindSigEvts(Double_t B, Int_t NEvts);
double WindowMethod_FindExpSigEvts(Double_t B);
double FullSpectrum_FindSigEvts(TH1D* hBG, TH1D* hSig, TH1D* hData);
double FullSpectrum_FindExpSigEvts(TH1D* hBG, TH1D* hSig);
void shellCommand(char* cmd);
void shellCommand(char* cmd, string &result);

Int_t SetLimit(){
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

  // Make arrays to pass other functions
  Double_t Activities_Ext[23], Activities_Ext_Err[23], Denominators_Ext[21];
  Double_t Activities_Rad[17], Activities_Rad_Err[17], Denominators_Rad[13];
  Double_t Activities_Int[9],  Activities_Int_Err[9],  Denominators_Int[16];
  Double_t Activities_Sig[2],  Activities_Sig_Err[2],  Denominators_Sig[2];
  Double_t AdjustActs[44], AdjustActs_Err[44];
  Double_t CovMatrix[44][44];

  // Read information on activities and denominators from files
  readActivities("Activities.txt", Activities_Ext, Activities_Ext_Err, Activities_Rad, Activities_Rad_Err, Activities_Int, Activities_Int_Err, Activities_Sig, Activities_Sig_Err, AdjustActs, AdjustActs_Err);
  readDenominators("Denominators.txt", Denominators_Ext, Denominators_Rad, Denominators_Int, Denominators_Sig);
  readCovMatrix("CovMatrix.txt", CovMatrix);

  // Set 2b0n activity to be 0 to get proper background for TLimit
  Activities_Sig[1] = 0;
  Activities_Sig_Err[1] = 0;

  // First call function to fill MC samples to be used when fitting.
  addBackgrounds_2b2n (Activities_Ext, Activities_Ext_Err, Denominators_Ext, Activities_Rad, Activities_Rad_Err, Denominators_Rad, Activities_Int, Activities_Int_Err, Denominators_Int, Activities_Sig, Activities_Sig_Err, Denominators_Sig, AdjustActs, AdjustActs_Err, CovMatrix);

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // 1) Window method
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////

  cout << "Window (Helene) Method:" << endl;

  // Calculate half-life using window method (2.6 - 3.2 MeV)
  Double_t LowerEdge = 2.6;
  Double_t UpperEdge = 3.199999;

  // Get expected number of background events and signal efficiency
  TH1D* hTotEnergy_BG = (TH1D*)((TH1D*)StackColl_2b2n[0]->GetStack()->Last())->Clone("hTotEnergyBG");
  TH1D* hTotEnergy_Sig = (TH1D*)((TH1D*)SigStackColl_2b0n[0]->GetStack()->Last())->Clone("hTotEnergySig");
  Double_t N_Evts_BG = hTotEnergy_BG->Integral(hTotEnergy_BG->FindBin(LowerEdge),hTotEnergy_BG->FindBin(UpperEdge));
  Double_t Sig_Eff = hTotEnergy_Sig->Integral(hTotEnergy_Sig->FindBin(LowerEdge),hTotEnergy_Sig->FindBin(UpperEdge));

  // Expected half-life
  Double_t N_Evts_Sig_Window_Exp = WindowMethod_FindExpSigEvts(N_Evts_BG);
  Double_t Halflife_Window_Exp = (Sig_Eff*log(2)*AccptRunTime/N_Evts_Sig_Window_Exp)*(6.02214e23*932.4/82.0)/(86400.0*365.25*1e23);

  // Observed half-life
  Int_t N_Evts_Data = (Int_t)h_2b2n_Data->Integral(h_2b2n_Data->FindBin(LowerEdge),h_2b2n_Data->FindBin(UpperEdge));
  Double_t N_Evts_Sig_Window_Obs = WindowMethod_FindSigEvts(N_Evts_BG, N_Evts_Data);
  Double_t Halflife_Window_Obs = (Sig_Eff*log(2)*AccptRunTime/N_Evts_Sig_Window_Obs)*(6.02214e23*932.4/82.0)/(86400.0*365.25*1e23);

  // Write results to text file and screen...
  ofstream textfile;
  textfile.open("./LimitResults.txt");
  if(textfile.is_open()){
    textfile << "Window (Helene) Method:" << endl;
    textfile << "Expected: BG = " << N_Evts_BG << "\tData = " << (int)N_Evts_BG << "\tSig < " << N_Evts_Sig_Window_Exp << "\tEff = " << 100.0*Sig_Eff << "%\t Halflife > " << Halflife_Window_Exp << " x 10^23 yrs" << endl;
    textfile << "Observed: BG = " << N_Evts_BG << "\tData = " <<    N_Evts_Data << "\tSig < " << N_Evts_Sig_Window_Obs << "\tEff = " << 100.0*Sig_Eff << "%\t Halflife > " << Halflife_Window_Obs << " x 10^23 yrs" << endl << endl;
  }
  cout << "Expected: BG = " << N_Evts_BG << "\tData = " << (int)N_Evts_BG << "\tSig < " << N_Evts_Sig_Window_Exp << "\tEff = " << 100.0*Sig_Eff << "%\t Halflife > " << Halflife_Window_Exp << " x 10^23 yrs" << endl;
  cout << "Observed: BG = " << N_Evts_BG << "\tData = " <<    N_Evts_Data << "\tSig < " << N_Evts_Sig_Window_Obs << "\tEff = " << 100.0*Sig_Eff << "%\t Halflife > " << Halflife_Window_Obs << " x 10^23 yrs" << endl << endl;

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // 2) TLimit method
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////

  cout << "TLimit Method:" << endl;

  // Start by getting signal efficiency
  Double_t Sig_Eff_Spectrum = hTotEnergy_Sig->Integral();

  // Calculate expected limit
  Double_t N_Evts_Sig_Spectrum_Exp = FullSpectrum_FindExpSigEvts(hTotEnergy_BG, hTotEnergy_Sig);
  Double_t Halflife_Spectrum_Exp = (Sig_Eff_Spectrum*log(2)*AccptRunTime/N_Evts_Sig_Spectrum_Exp)*(6.02214e23*932.4/82.0)/(86400.0*365.25*1e23);
  cout << "Expected: Events < " << N_Evts_Sig_Spectrum_Exp << "\tEff = " << 100*Sig_Eff_Spectrum <<"%\t Halflife > " << Halflife_Spectrum_Exp << " x 10^23 yrs" << endl << endl;

  // Calculate observed limit
  Double_t N_Evts_Sig_Spectrum_Obs = FullSpectrum_FindSigEvts(hTotEnergy_BG, hTotEnergy_Sig, h_2b2n_Data);
  Double_t Halflife_Spectrum_Obs = (Sig_Eff_Spectrum*log(2)*AccptRunTime/N_Evts_Sig_Spectrum_Obs)*(6.02214e23*932.4/82.0)/(86400.0*365.25*1e23);

  // Write results to text file and screen...
  if(textfile.is_open()){
    textfile << "TLimit Method:" << endl;
    textfile << "Expected: Events < " << N_Evts_Sig_Spectrum_Exp << "\tEff = " << 100*Sig_Eff_Spectrum <<"%\t Halflife > " << Halflife_Spectrum_Exp << " x 10^23 yrs" << endl;
    textfile << "Observed: Events < " << N_Evts_Sig_Spectrum_Obs << "\tEff = " << 100*Sig_Eff_Spectrum <<"%\t Halflife > " << Halflife_Spectrum_Obs << " x 10^23 yrs" << endl << endl;
  }
  cout << "Observed: Events < " << N_Evts_Sig_Spectrum_Obs << "\tEff = " << 100*Sig_Eff_Spectrum <<"%\t Halflife > " << Halflife_Spectrum_Obs << " x 10^23 yrs" << endl << endl;

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // 2) TLimit method
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////

  cout << "Collie Method:" << endl;

  // Start by clearing out collieMachinery folder
  shellCommand("cd collieMachinery && rm -f *");

  // Write out file that collie will use
  TFile* collieFile = new TFile("collieMachinery/InputHistograms.root", "RECREATE");
  TH1D* h0 = (TH1D*)h_2b2n_Data->Clone("hDataClone");     h0->Write("hData");
  TH1D* h1 = (TH1D*)StackColl_2b2n[0]->GetHists()->At(0); h1->Write("hExternal");
  TH1D* h2 = (TH1D*)StackColl_2b2n[0]->GetHists()->At(1); h2->Write("hRadon");
  TH1D* h3 = (TH1D*)StackColl_2b2n[0]->GetHists()->At(2); h3->Write("hInternal");
  TH1D* h4 = (TH1D*)StackColl_2b2n[0]->GetHists()->At(3); h4->Write("hBi214");
  TH1D* h5 = (TH1D*)StackColl_2b2n[0]->GetHists()->At(4); h5->Write("hTl208");
  TH1D* h6 = (TH1D*)StackColl_2b2n[0]->GetHists()->At(5); h6->Write("h2b2n");
  TH1D* h7 = (TH1D*)SigStackColl_2b0n[0]->GetHists()->At(0); h7->Write("h2b0n");
  collieFile->Write();
  collieFile->Close();

  // Copy collie executables into collieMachinery folder
  shellCommand("cp /home/jmott/Desktop/NEMO3/SeleniumAnalysis/Signals/2b0n/collie/v4_13/JEM_Analysis/*.exe ./collieMachinery/");

  // Make collie input file
  cout << "Making collie input file...";
  shellCommand("cd collieMachinery && ./makeCollieInput.exe > makeCollieInput.log");
  cout << "done" << endl;

  // Run statistical 
  cout << "Calculating limits..." << endl;
  shellCommand("cd collieMachinery && ./calculateCollieLimit_statOnly.exe collieOutput_statOnly.root collieIOFile.root 0 > calculateCollieLimit_statOnly.log &");
  shellCommand("cd collieMachinery && ./calculateCollieLimit.exe collieOutput_m2Sigma.root collieIOFile.root -2 > calculateCollieLimit_m2Sigma.log &");
  shellCommand("cd collieMachinery && ./calculateCollieLimit.exe collieOutput_m1Sigma.root collieIOFile.root -1 > calculateCollieLimit_m1Sigma.log &");
  shellCommand("cd collieMachinery && ./calculateCollieLimit.exe collieOutput_0Sigma.root  collieIOFile.root 0  > calculateCollieLimit_0Sigma.log &");
  shellCommand("cd collieMachinery && ./calculateCollieLimit.exe collieOutput_p1Sigma.root collieIOFile.root 1  > calculateCollieLimit_p1Sigma.log &");
  shellCommand("cd collieMachinery && ./calculateCollieLimit.exe collieOutput_p2Sigma.root collieIOFile.root 2  > calculateCollieLimit_p2Sigma.log &");

  // Check whether programs have finished before continuing
  bool statDone = false;
  bool m2SigmaDone = false;
  bool m1SigmaDone = false;
  bool m0SigmaDone = false;
  bool p1SigmaDone = false;
  bool p2SigmaDone = false;

  while (!statDone || !m2SigmaDone || !m1SigmaDone || !m0SigmaDone || !p1SigmaDone || !p2SigmaDone){

    sleep(15);

    string shell;

    shellCommand("ps -edf | grep statOnly | grep -v grep", shell);
    if(shell == "" && !statDone){
      cout << "Statistical limit complete." << endl;
      statDone = true;
    }

    shellCommand("ps -edf | grep m2Sigma | grep -v grep", shell);
    if(shell == "" && !m2SigmaDone){
      cout << "-2 sigma limit complete." << endl;
      m2SigmaDone = true;
    }

    shellCommand("ps -edf | grep m1Sigma | grep -v grep", shell);
    if(shell == "" && !m1SigmaDone){
      cout << "-1 sigma limit complete." << endl;
      m1SigmaDone = true;
    }

    shellCommand("ps -edf | grep 0Sigma | grep -v grep", shell);
    if(shell == "" && !m0SigmaDone){
      cout << "0 sigma limit complete." << endl;
      m0SigmaDone = true;
    }

    shellCommand("ps -edf | grep p1Sigma | grep -v grep", shell);
    if(shell == "" && !p1SigmaDone){
      cout << "+1 sigma limit complete." << endl;
      p1SigmaDone = true;
    }

    shellCommand("ps -edf | grep p2Sigma | grep -v grep", shell);
    if(shell == "" && !p2SigmaDone){
      cout << "+2 sigma limit complete." << endl;
      p2SigmaDone = true;
    }

  }

  // Get all limits from collie output files and store NLLR histograms for stat-only and systematic
  double obsLimit_stat, expLimit_stat;
  double obsLimit_0Sigma, expLimit_0Sigma, expLimit_m2Sigma, expLimit_m1Sigma, expLimit_p1Sigma, expLimit_p2Sigma;

  TFile* collieOutput_statOnly = new TFile ("collieMachinery/collieOutput_statOnly.root","READ");
  TTree* tree_statOnly = (TTree*)collieOutput_statOnly->Get("SCAN");
  tree_statOnly->SetBranchAddress("xsec_obsfactor", &obsLimit_stat);
  tree_statOnly->SetBranchAddress("xsec_medfactor", &expLimit_stat);
  tree_statOnly->GetEvent(0);
  double Halflife_stat_Obs = (Sig_Eff_Spectrum*log(2)*AccptRunTime/obsLimit_stat)*(6.02214e23*932.4/82.0)/(86400.0*365.25*1e23);
  double Halflife_stat_Exp = (Sig_Eff_Spectrum*log(2)*AccptRunTime/expLimit_stat)*(6.02214e23*932.4/82.0)/(86400.0*365.25*1e23);
  TH1D* hNLLRsb_statOnly = (TH1D*)(collieOutput_statOnly->Get("NLLR_SB"))->Clone("hNLLRsb_statOnly");
  TH1D* hNLLRb_statOnly  = (TH1D*)(collieOutput_statOnly->Get("NLLR_B")) ->Clone("hNLLRb_statOnly");
  TH1D* hNLLRd_statOnly  = (TH1D*)(collieOutput_statOnly->Get("NLLR_D")) ->Clone("hNLLRd_statOnly");

  TFile* collieOutput_0Sigma = new TFile ("collieMachinery/collieOutput_0Sigma.root","READ");
  TTree* tree_0Sigma = (TTree*)collieOutput_0Sigma->Get("SCAN");
  tree_0Sigma->SetBranchAddress("xsec_obsfactor", &obsLimit_0Sigma);
  tree_0Sigma->SetBranchAddress("xsec_medfactor", &expLimit_0Sigma);
  tree_0Sigma->GetEvent(0);
  double Halflife_0Sigma_Obs = (Sig_Eff_Spectrum*log(2)*AccptRunTime/obsLimit_0Sigma)*(6.02214e23*932.4/82.0)/(86400.0*365.25*1e23);
  double Halflife_0Sigma_Exp = (Sig_Eff_Spectrum*log(2)*AccptRunTime/expLimit_0Sigma)*(6.02214e23*932.4/82.0)/(86400.0*365.25*1e23);
  TH1D* hNLLRsb_0Sigma = (TH1D*)(collieOutput_0Sigma->Get("NLLR_SB"))->Clone("hNLLRsb_0Sigma");
  TH1D* hNLLRb_0Sigma  = (TH1D*)(collieOutput_0Sigma->Get("NLLR_B")) ->Clone("hNLLRb_0Sigma");
  TH1D* hNLLRd_0Sigma  = (TH1D*)(collieOutput_0Sigma->Get("NLLR_D")) ->Clone("hNLLRd_0Sigma");

  TFile* collieOutput_m2Sigma = new TFile ("collieMachinery/collieOutput_m2Sigma.root","READ");
  TTree* tree_m2Sigma = (TTree*)collieOutput_m2Sigma->Get("SCAN");
  tree_m2Sigma->SetBranchAddress("xsec_medfactor", &expLimit_m2Sigma);
  tree_m2Sigma->GetEvent(0);
  double Halflife_m2Sigma_Exp = (Sig_Eff_Spectrum*log(2)*AccptRunTime/expLimit_m2Sigma)*(6.02214e23*932.4/82.0)/(86400.0*365.25*1e23);

  TFile* collieOutput_m1Sigma = new TFile ("collieMachinery/collieOutput_m1Sigma.root","READ");
  TTree* tree_m1Sigma = (TTree*)collieOutput_m1Sigma->Get("SCAN");
  tree_m1Sigma->SetBranchAddress("xsec_medfactor", &expLimit_m1Sigma);
  tree_m1Sigma->GetEvent(0);
  double Halflife_m1Sigma_Exp = (Sig_Eff_Spectrum*log(2)*AccptRunTime/expLimit_m1Sigma)*(6.02214e23*932.4/82.0)/(86400.0*365.25*1e23);

  TFile* collieOutput_p1Sigma = new TFile ("collieMachinery/collieOutput_p1Sigma.root","READ");
  TTree* tree_p1Sigma = (TTree*)collieOutput_p1Sigma->Get("SCAN");
  tree_p1Sigma->SetBranchAddress("xsec_medfactor", &expLimit_p1Sigma);
  tree_p1Sigma->GetEvent(0);
  double Halflife_p1Sigma_Exp = (Sig_Eff_Spectrum*log(2)*AccptRunTime/expLimit_p1Sigma)*(6.02214e23*932.4/82.0)/(86400.0*365.25*1e23);

  TFile* collieOutput_p2Sigma = new TFile ("collieMachinery/collieOutput_p2Sigma.root","READ");
  TTree* tree_p2Sigma = (TTree*)collieOutput_p2Sigma->Get("SCAN");
  tree_p2Sigma->SetBranchAddress("xsec_medfactor", &expLimit_p2Sigma);
  tree_p2Sigma->GetEvent(0);
  double Halflife_p2Sigma_Exp = (Sig_Eff_Spectrum*log(2)*AccptRunTime/expLimit_p2Sigma)*(6.02214e23*932.4/82.0)/(86400.0*365.25*1e23);

  // Write results to file and screen
  if(textfile.is_open()){
    textfile << "Collie Method:" << endl;
    textfile << "Efficiency = " << 100*Sig_Eff_Spectrum <<"%" << endl;
    textfile << "Stat-only Expected:     Events < " << expLimit_stat    << "\t Halflife > " << Halflife_stat_Exp << " x 10^23 yrs" << endl;
    textfile << "Stat-only Observed:     Events < " << obsLimit_stat    << "\t Halflife > " << Halflife_stat_Obs << " x 10^23 yrs" << endl;
    textfile << "Syst -2 Sigma Expected: Events < " << expLimit_m2Sigma << "\t Halflife > " << Halflife_m2Sigma_Exp << " x 10^23 yrs" << endl;
    textfile << "Syst -1 Sigma Expected: Events < " << expLimit_m1Sigma << "\t Halflife > " << Halflife_m1Sigma_Exp << " x 10^23 yrs" << endl;
    textfile << "Syst  0 Sigma Expected: Events < " << expLimit_0Sigma  << "\t Halflife > " << Halflife_0Sigma_Exp << " x 10^23 yrs" << endl;
    textfile << "Syst +1 Sigma Expected: Events < " << expLimit_p1Sigma << "\t Halflife > " << Halflife_p1Sigma_Exp << " x 10^23 yrs" << endl;
    textfile << "Syst +2 Sigma Expected: Events < " << expLimit_p2Sigma << "\t Halflife > " << Halflife_p2Sigma_Exp << " x 10^23 yrs" << endl;
    textfile << "Syst  0 Sigma Observed: Events < " << obsLimit_0Sigma  << "\t Halflife > " << Halflife_0Sigma_Obs << " x 10^23 yrs" << endl;
    textfile.close();
  }
  cout << "Efficiency = " << 100*Sig_Eff_Spectrum <<"%" << endl;
  cout << "Stat-only Expected:     Events < " << expLimit_stat    << "\t Halflife > " << Halflife_stat_Exp << " x 10^23 yrs" << endl;
  cout << "Stat-only Observed:     Events < " << obsLimit_stat    << "\t Halflife > " << Halflife_stat_Obs << " x 10^23 yrs" << endl;
  cout << "Syst -2 Sigma Expected: Events < " << expLimit_m2Sigma << "\t Halflife > " << Halflife_m2Sigma_Exp << " x 10^23 yrs" << endl;
  cout << "Syst -1 Sigma Expected: Events < " << expLimit_m1Sigma << "\t Halflife > " << Halflife_m1Sigma_Exp << " x 10^23 yrs" << endl;
  cout << "Syst  0 Sigma Expected: Events < " << expLimit_0Sigma  << "\t Halflife > " << Halflife_0Sigma_Exp << " x 10^23 yrs" << endl;
  cout << "Syst +1 Sigma Expected: Events < " << expLimit_p1Sigma << "\t Halflife > " << Halflife_p1Sigma_Exp << " x 10^23 yrs" << endl;
  cout << "Syst +2 Sigma Expected: Events < " << expLimit_p2Sigma << "\t Halflife > " << Halflife_p2Sigma_Exp << " x 10^23 yrs" << endl;
  cout << "Syst  0 Sigma Observed: Events < " << obsLimit_0Sigma  << "\t Halflife > " << Halflife_0Sigma_Obs << " x 10^23 yrs" << endl;

  // Set activity to real limit from collie to put in plot
  Activities_Sig[1] = (log(2)/(86400.0*365.25))/(Halflife_0Sigma_Obs*82.0/(6.022*932.4));

  // Write information on activities and denominators from files
  writeActivities("Activities.txt", Activities_Ext, Activities_Ext_Err, Activities_Rad, Activities_Rad_Err, Activities_Int, Activities_Int_Err, Activities_Sig, Activities_Sig_Err, AdjustActs, AdjustActs_Err);
  writeDenominators("Denominators.txt", Denominators_Ext, Denominators_Rad, Denominators_Int, Denominators_Sig);

  // Re-add background with new limit for 2b0n
  addBackgrounds_2b2n (Activities_Ext, Activities_Ext_Err, Denominators_Ext, Activities_Rad, Activities_Rad_Err, Denominators_Rad, Activities_Int, Activities_Int_Err, Denominators_Int, Activities_Sig, Activities_Sig_Err, Denominators_Sig, AdjustActs, AdjustActs_Err, CovMatrix);

  // Draw Output - 2b2n
  TCanvas* c1_2b2n = new TCanvas("c1_2b2n","Total Electron Energy - 2b2n",10,10,1200,800);
  c1_2b2n->SetLogy();
  h_2b2n_Data->SetMarkerStyle(20);
  h_2b2n_Data->GetXaxis()->SetRangeUser(0.5,3.5);
  h_2b2n_Data->GetYaxis()->SetRangeUser(0.5,7e3);
  h_2b2n_Data->Draw();
  StackColl_2b2n[0]->Draw("HISTSAME");
  h_2b2n_Data->Draw("SAME");
  Legend_2b2n[0]->Draw();
  ChiSquares_2b2n[0]->Draw();
  c1_2b2n->SaveAs("Images/png/1 - Total Electron Energy.png");
  c1_2b2n->SaveAs("Images/eps/1 - Total Electron Energy.eps");
  c1_2b2n->SaveAs("Images/gif/1 - Total Electron Energy.gif");
  
  TCanvas* c1_1_2b2n = new TCanvas("c1_1_2b2n","Total Electron Energy - 2b2n",10,10,1200,800);
  h_2b2n_Data->GetXaxis()->SetRangeUser(2.5,3.5);
  h_2b2n_Data->GetYaxis()->SetRangeUser(0,15);
  h_2b2n_Data->Draw();
  StackColl_2b2n[0]->Draw("HISTSAME");
  h_2b2n_Data->Draw("SAME");
  Legend_2b2n[0]->Draw();
  ChiSquares_2b2n[0]->Draw();
  c1_1_2b2n->SaveAs("Images/png/1 - Total Electron Energy Linear.png");
  c1_1_2b2n->SaveAs("Images/eps/1 - Total Electron Energy Linear.eps");
  c1_1_2b2n->SaveAs("Images/gif/1 - Total Electron Energy Linear.gif");
  
  TCanvas* c2_NLLR_Stat = new TCanvas("c2_NLLR_Stat","NLLR - Stat Only",10,10,1200,800);
  hNLLRb_statOnly->SetTitle(";NLLR;Probability Density");
  hNLLRb_statOnly->GetYaxis()->SetTitleOffset(1.2);
  hNLLRb_statOnly->GetXaxis()->SetRangeUser(-30,30);
  hNLLRb_statOnly->SetLineColor(4);
  hNLLRb_statOnly->SetLineWidth(3);
  hNLLRb_statOnly->DrawNormalized();
  hNLLRsb_statOnly->SetLineColor(2);
  hNLLRsb_statOnly->SetLineWidth(3);
  hNLLRsb_statOnly->DrawNormalized("SAME");
  hNLLRd_statOnly->SetLineWidth(4);
  hNLLRd_statOnly->Draw("SAME");
  TLegend* leg_NLLR_Stat = new TLegend(0.75,0.65,0.95,0.95);
  leg_NLLR_Stat->AddEntry(hNLLRb_statOnly,"B-Only NLLR", "l");
  leg_NLLR_Stat->AddEntry(hNLLRsb_statOnly,"S+B NLLR", "l");
  leg_NLLR_Stat->AddEntry(hNLLRd_statOnly,"Observed NLLR", "l");
  leg_NLLR_Stat->SetFillStyle(0);
  leg_NLLR_Stat->SetBorderSize(0);
  leg_NLLR_Stat->Draw();
  c2_NLLR_Stat->SaveAs("Images/png/2 - NLLR Stat Only.png");
  c2_NLLR_Stat->SaveAs("Images/eps/2 - NLLR Stat Only.eps");
  c2_NLLR_Stat->SaveAs("Images/gif/2 - NLLR Stat Only.gif");

  TCanvas* c3_NLLR_Syst = new TCanvas("c3_NLLR_Syst","NLLR - Syst",10,10,1200,800);
  hNLLRb_0Sigma->SetTitle(";NLLR;Probability Density");
  hNLLRb_0Sigma->GetYaxis()->SetTitleOffset(1.2);
  hNLLRb_0Sigma->GetXaxis()->SetRangeUser(-30,30);
  hNLLRb_0Sigma->SetLineColor(4);
  hNLLRb_0Sigma->SetLineWidth(3);
  hNLLRb_0Sigma->DrawNormalized();
  hNLLRsb_0Sigma->SetLineColor(2);
  hNLLRsb_0Sigma->SetLineWidth(3);
  hNLLRsb_0Sigma->DrawNormalized("SAME");
  hNLLRd_0Sigma->SetLineWidth(4);
  hNLLRd_0Sigma->Draw("SAME");
  TLegend* leg_NLLR_Syst = new TLegend(0.75,0.65,0.95,0.95);
  leg_NLLR_Syst->AddEntry(hNLLRb_0Sigma,"B-Only NLLR", "l");
  leg_NLLR_Syst->AddEntry(hNLLRsb_0Sigma,"S+B NLLR", "l");
  leg_NLLR_Syst->AddEntry(hNLLRd_0Sigma,"Observed NLLR", "l");
  leg_NLLR_Syst->SetFillStyle(0);
  leg_NLLR_Syst->SetBorderSize(0);
  leg_NLLR_Syst->Draw();
  c3_NLLR_Syst->SaveAs("Images/png/3 - NLLR Syst.png");
  c3_NLLR_Syst->SaveAs("Images/eps/3 - NLLR Syst.eps");
  c3_NLLR_Syst->SaveAs("Images/gif/3 - NLLR Syst.gif");

  return 0;
}


double WindowMethod_FindSigEvts(Double_t B, Int_t NEvts){

  //Find S using CL(S+B)/CL(B) = 0.1
  Double_t Likelihood = 1.0;
  Double_t S = 0;

  while(Likelihood > 0.1){
    S += 0.001;
    Float_t CLsb = 0; Float_t CLb = 0; 
    for (Int_t i=0; i<=NEvts; i++) {
      CLsb+=TMath::Poisson(i,S+B);
      CLb+=TMath::Poisson(i,B);
    }
    Likelihood =  CLsb/CLb;
    //    cout << "S = " << S << "\tCLb = " << CLb << "\tCLsb = " << CLsb << "\tCLs = " << Likelihood << endl;
  }

  return S;
}

double WindowMethod_FindExpSigEvts(Double_t B){

  //Find S using CL(S+B)/CL(B) = 0.1 with N_Obs = B
  Double_t Likelihood = 1.0;
  Double_t S = 0;
  Int_t NEvts = (int)B;

  while(Likelihood > 0.1){
    S += 0.001;
    Float_t CLsb = 0; Float_t CLb = 0; 
    for (Int_t i=0; i<=NEvts; i++) {
      CLsb+=TMath::Poisson(i,S+B);
      CLb+=TMath::Poisson(i,B);
    }
    Likelihood =  CLsb/CLb;
    //    cout << "S = " << S << "\tCLb = " << CLb << "\tCLsb = " << CLsb << "\tCLs = " << Likelihood << endl;
  }

  return S;
}

double FullSpectrum_FindSigEvts(TH1D* hBG, TH1D* hSig, TH1D* hData){

  //Create data histogram to pass to TLimit (copy BG - as not actually used for limit)
  TH1D* hDataClone = (TH1D*)hData->Clone("hDataClone");

  TH1D* hSig_Clone = (TH1D*)hSig->Clone("hSig_scaled");

  double NSigEvts = Limit_Sig_Evts(0.1, hSig_Clone, hBG, hDataClone);

  delete hSig_Clone;
  delete hDataClone;

  return NSigEvts;
}


double FullSpectrum_FindExpSigEvts(TH1D* hBG, TH1D* hSig){

  //Create data histogram to pass to TLimit (copy BG - as not actually used for limit)
  TH1D* hData = (TH1D*)hBG->Clone("hData");

  TH1D* hSig_Clone = (TH1D*)hSig->Clone("hSig_scaled");

  double NSigEvts = Expected_Limit_Sig_Evts(0.1, hSig_Clone, hBG, hData);

  delete hSig_Clone;
  delete hData;

  return NSigEvts;
}

void shellCommand(char* cmd) {
  FILE* pipe = popen(cmd, "r");
  if (!pipe) return;
  pclose(pipe);
  return;
}

void shellCommand(char* cmd, string &result) {
  FILE* pipe = popen(cmd, "r");
  if (!pipe){
    result = "ERROR";
    return;
  }

  char buffer[128];
  result = "";
  while(!feof(pipe)) {
    if(fgets(buffer, 128, pipe) != NULL)
      result += buffer;
  }
  pclose(pipe);
  return;
}
