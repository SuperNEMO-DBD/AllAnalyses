// RootPulsesMap.C
// Author: Mathieu Bongrand <bongrand@lal.in2p3.fr>
// Copyright: 2018 (C) SoLid - LAL (IN2P3/CNRS)

// root 'RootPulsesMap.C("data/test1/root_pulses_test1_run0.root")'
// root 'RootPulsesMap.C("data/root_run100_0.root")'
// root 'RootPulsesMap.C("data/root_run100_0_9.root")'
// root 'RootPulsesMap.C("data/root_run104_0_64.root")'

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

#include <TROOT.h>
#include <TStyle.h>

#include <TFile.h>
#include <TTree.h>

#include <TCanvas.h>
#include <TH2D.h>

#include "ReverseAxis.h"

using namespace std;

//----------------------------//



void RootPulsesMap (string filename_,string side)
{
  gROOT->Reset ();
  gStyle->SetHistFillColor (kAzure-8);
  gStyle->SetOptStat (0000);

  // Output tree:
  TFile *rootfile = new TFile (filename_.c_str (), "read");
  TTree *TPulses = (TTree*) rootfile->Get("pulses");

  cout << TPulses->GetEntries () << endl;

  // Declaration of leaf types
  Int_t pulse_slot;
  Int_t pulse_channel;
  Double_t pulse_time;
  Double_t pulse_amplitude;
  Double_t pulse_charge;
  Double_t pulse_baseline;

  // Branches:
  TPulses->SetBranchAddress ("pulse_slot", &pulse_slot);
  TPulses->SetBranchAddress ("pulse_channel", &pulse_channel);
  TPulses->SetBranchAddress ("pulse_time", &pulse_time);
  TPulses->SetBranchAddress ("pulse_amplitude", &pulse_amplitude);
  TPulses->SetBranchAddress ("pulse_charge", &pulse_charge);
  TPulses->SetBranchAddress ("pulse_baseline", &pulse_baseline);

  // Root histos:
  TH2D *h_counts = new TH2D ("counts","counts; Y; Z", 22, -1, 21, 15, -1, 14);

  int count_map [20][13];
  for (int i = 0; i<20; i++)
    {
      for (int j = 0; j<13; j++)
	{
	  count_map [i][j] = 0;
	}
    }

  for ( unsigned int i_pulse = 0; i_pulse < TPulses->GetEntries(); i_pulse++ )
    {
      TPulses->GetEntry (i_pulse);

      if (pulse_amplitude > -10.0) continue;
      //if (pulse_amplitude > -100.0) continue;

      count_map [pulse_slot][pulse_channel] ++;

      //h_charge->Fill (-1.0 * pulse_charge);

    }

  for (int i = 0; i<20; i++)
    {
      for (int j = 0; j<13; j++)
	{
	  h_counts->SetBinContent (i+2, j+2, count_map [i][j]);
	}
    }

  TCanvas *canvas = new TCanvas ("canvas", "canvas", 200, 200, 1100, 800);
  canvas->cd ();
  h_counts->Draw ("colztext");
  if (side=="it") {
    ReverseXAxis(h_counts);
  }
}
