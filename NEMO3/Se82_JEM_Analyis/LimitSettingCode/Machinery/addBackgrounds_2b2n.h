#include "addChannelToStacks_2b2n.h"
#include "chiSquareTest.h"

extern THStack* StackColl_2b2n[];
extern THStack* IntStackColl_2b2n[];
extern THStack* Bi214StackColl_2b2n[];
extern THStack* Tl208StackColl_2b2n[];
extern THStack* ExtStackColl_2b2n[];
extern THStack* RadStackColl_2b2n[];
extern THStack* SigStackColl_2b2n[];
extern THStack* SigStackColl_2b0n[];
extern TH1D* h_2b2n_Data;
extern const Int_t AccptRunTime;
extern TFile* infile_2b2n;
extern TLegend* Legend_2b2n[];
extern TLegend* LegendLog_2b2n[];
extern TPaveText* ChiSquares_2b2n[];
extern TPaveText* ChiSquaresLog_2b2n[];

void addBackgrounds_2b2n(double *Activities_Ext, double *Activities_Ext_Err, double *Denominators_Ext, double *Activities_Rad, double *Activities_Rad_Err,  double *Denominators_Rad, double *Activities_Int, double *Activities_Int_Err,  double *Denominators_Int, double *Activities_Sig, double *Activities_Sig_Err, double *Denominators_Sig, double *AdjustActs, double *AdjustActs_Err, double CovMatrix[][44]){

  // ADD EXTERNAL BACKGROUNDS
  Double_t Act_PMT_K40          = Activities_Ext[0];
  Double_t Act_PMT_Bi214        = Activities_Ext[1];
  Double_t Act_PMT_Tl208        = Activities_Ext[2];
  Double_t Act_PMT_Ac228        = Activities_Ext[3];
  Double_t Act_MuMetal_Co60     = Activities_Ext[4];
  Double_t Act_SteelFrame_K40   = Activities_Ext[5];
  Double_t Act_SteelFrame_Bi214 = Activities_Ext[6];
  Double_t Act_SteelFrame_Tl208 = Activities_Ext[7];
  Double_t Act_SteelFrame_Ac228 = Activities_Ext[8];
  Double_t Act_SteelFrame_Co60  = Activities_Ext[9];
  Double_t Act_CuPetals_Co60    = Activities_Ext[10];
  Double_t Act_CuTower_Co60     = Activities_Ext[11];
  Double_t Act_FeShield_Bi214   = Activities_Ext[12];
  Double_t Act_FeShield_Tl208   = Activities_Ext[13];
  Double_t Act_FeShield_Ac228   = Activities_Ext[14];
  Double_t Act_ScintInn_K40     = Activities_Ext[15];
  Double_t Act_ScintOut_K40     = Activities_Ext[16];
  Double_t Act_ScintPet_K40     = Activities_Ext[17];
  Double_t Act_SScin_Pa234m     = Activities_Ext[18];
  Double_t Act_MuMetal_g1000_P1 = Activities_Ext[19];
  Double_t Act_MuMetal_g1000_P2 = Activities_Ext[20];
  Double_t Act_Neutrons_P1      = Activities_Ext[21];
  Double_t Act_Neutrons_P2      = Activities_Ext[22];

  Double_t Denom_PMT_K40          = Denominators_Ext[0];
  Double_t Denom_PMT_Bi214        = Denominators_Ext[1];
  Double_t Denom_PMT_Tl208        = Denominators_Ext[2];
  Double_t Denom_PMT_Ac228        = Denominators_Ext[3];
  Double_t Denom_MuMetal_Co60     = Denominators_Ext[4];
  Double_t Denom_SteelFrame_K40   = Denominators_Ext[5];
  Double_t Denom_SteelFrame_Bi214 = Denominators_Ext[6];
  Double_t Denom_SteelFrame_Tl208 = Denominators_Ext[7];
  Double_t Denom_SteelFrame_Ac228 = Denominators_Ext[8];
  Double_t Denom_SteelFrame_Co60  = Denominators_Ext[9];
  Double_t Denom_CuPetals_Co60    = Denominators_Ext[10];
  Double_t Denom_CuTower_Co60     = Denominators_Ext[11];
  Double_t Denom_FeShield_Bi214   = Denominators_Ext[12];
  Double_t Denom_FeShield_Tl208   = Denominators_Ext[13];
  Double_t Denom_FeShield_Ac228   = Denominators_Ext[14];
  Double_t Denom_ScintInn_K40     = Denominators_Ext[15];
  Double_t Denom_ScintOut_K40     = Denominators_Ext[16];
  Double_t Denom_ScintPet_K40     = Denominators_Ext[17];
  Double_t Denom_SScin_Pa234m     = Denominators_Ext[18];
  Double_t Denom_MuMetal_g1000    = Denominators_Ext[19];
  Double_t Denom_Neutrons         = Denominators_Ext[20];

  Int_t    FillColor_PMT_K40          = kRed;
  Int_t    FillColor_PMT_Bi214        = kRed+1;
  Int_t    FillColor_PMT_Tl208        = kRed+2;
  Int_t    FillColor_PMT_Ac228        = kRed+3;
  Int_t    FillColor_MuMetal_Co60     = kViolet;
  Int_t    FillColor_SteelFrame_K40   = kBlue;
  Int_t    FillColor_SteelFrame_Bi214 = kBlue+1;
  Int_t    FillColor_SteelFrame_Tl208 = kBlue+2;
  Int_t    FillColor_SteelFrame_Ac228 = kBlue+3;
  Int_t    FillColor_SteelFrame_Co60  = kBlue+4;
  Int_t    FillColor_CuPetals_Co60    = kMagenta;
  Int_t    FillColor_CuTower_Co60     = kCyan;
  Int_t    FillColor_FeShield_Bi214   = kOrange;
  Int_t    FillColor_FeShield_Tl208   = kOrange+1;
  Int_t    FillColor_FeShield_Ac228   = kOrange+2;
  Int_t    FillColor_ScintInn_K40     = kRed;
  Int_t    FillColor_ScintOut_K40     = kRed+2;
  Int_t    FillColor_ScintPet_K40     = kRed+4;
  Int_t    FillColor_SScin_Pa234m     = kYellow;
  Int_t    FillColor_MuMetal_g1000    = kViolet-1;
  Int_t    FillColor_Neutrons         = kViolet+1;

  // Create collection of histogram stacks
  ExtStackColl_2b2n[0] = new THStack("h_2b2n","Total Electron Energy");

  // Add External Backgrounds

  // 0) PMT_K40
  Double_t ScaleFactor_PMT_K40 = Act_PMT_K40*AccptRunTime/Denom_PMT_K40;
  addChannelToStacks_2b2n("PMT_K40", ScaleFactor_PMT_K40, FillColor_PMT_K40, ExtStackColl_2b2n, infile_2b2n);

  // 1) PMT_Bi214
  Double_t ScaleFactor_PMT_Bi214 = Act_PMT_Bi214*AccptRunTime/Denom_PMT_Bi214;
  addChannelToStacks_2b2n("PMT_Bi214", ScaleFactor_PMT_Bi214, FillColor_PMT_Bi214, ExtStackColl_2b2n, infile_2b2n);

  // 2) PMT_Tl208
  Double_t ScaleFactor_PMT_Tl208 = Act_PMT_Tl208*AccptRunTime/Denom_PMT_Tl208;
  addChannelToStacks_2b2n("PMT_Tl208", ScaleFactor_PMT_Tl208, FillColor_PMT_Tl208, ExtStackColl_2b2n, infile_2b2n);

  // 3) PMT_Ac228
  Double_t ScaleFactor_PMT_Ac228 = Act_PMT_Ac228*AccptRunTime/Denom_PMT_Ac228;
  addChannelToStacks_2b2n("PMT_Ac228", ScaleFactor_PMT_Ac228, FillColor_PMT_Ac228, ExtStackColl_2b2n, infile_2b2n);

  // 4) FeShield_Bi214
  Double_t ScaleFactor_FeShield_Bi214 = Act_FeShield_Bi214*AccptRunTime/Denom_FeShield_Bi214;
  addChannelToStacks_2b2n("FeShield_Bi214", ScaleFactor_FeShield_Bi214, FillColor_FeShield_Bi214, ExtStackColl_2b2n, infile_2b2n);

  // 5) FeShield_Tl208
  Double_t ScaleFactor_FeShield_Tl208 = Act_FeShield_Tl208*AccptRunTime/Denom_FeShield_Tl208;
  addChannelToStacks_2b2n("FeShield_Tl208", ScaleFactor_FeShield_Tl208, FillColor_FeShield_Tl208, ExtStackColl_2b2n, infile_2b2n);

  // 6) FeShield_Ac228
  Double_t ScaleFactor_FeShield_Ac228 = Act_FeShield_Ac228*AccptRunTime/Denom_FeShield_Ac228;
  addChannelToStacks_2b2n("FeShield_Ac228", ScaleFactor_FeShield_Ac228, FillColor_FeShield_Ac228, ExtStackColl_2b2n, infile_2b2n);

  // 7) MuMetal_Co60
  Double_t ScaleFactor_MuMetal_Co60 = Act_MuMetal_Co60*AccptRunTime/Denom_MuMetal_Co60;
  addChannelToStacks_2b2n("MuMetal_Co60", ScaleFactor_MuMetal_Co60, FillColor_MuMetal_Co60, ExtStackColl_2b2n, infile_2b2n);

  // 8) SteelFrame_K40
  Double_t ScaleFactor_SteelFrame_K40 = Act_SteelFrame_K40*AccptRunTime/Denom_SteelFrame_K40;
  addChannelToStacks_2b2n("SteelFrame_K40", ScaleFactor_SteelFrame_K40, FillColor_SteelFrame_K40, ExtStackColl_2b2n, infile_2b2n);

  // 9) SteelFrame_Bi214
  Double_t ScaleFactor_SteelFrame_Bi214 = Act_SteelFrame_Bi214*AccptRunTime/Denom_SteelFrame_Bi214;
  addChannelToStacks_2b2n("SteelFrame_Bi214", ScaleFactor_SteelFrame_Bi214, FillColor_SteelFrame_Bi214, ExtStackColl_2b2n, infile_2b2n);

  // 10) SteelFrame_Tl208
  Double_t ScaleFactor_SteelFrame_Tl208 = Act_SteelFrame_Tl208*AccptRunTime/Denom_SteelFrame_Tl208;
  addChannelToStacks_2b2n("SteelFrame_Tl208", ScaleFactor_SteelFrame_Tl208, FillColor_SteelFrame_Tl208, ExtStackColl_2b2n, infile_2b2n);

  // 11) SteelFrame_Ac228
  Double_t ScaleFactor_SteelFrame_Ac228 = Act_SteelFrame_Ac228*AccptRunTime/Denom_SteelFrame_Ac228;
  addChannelToStacks_2b2n("SteelFrame_Ac228", ScaleFactor_SteelFrame_Ac228, FillColor_SteelFrame_Ac228, ExtStackColl_2b2n, infile_2b2n);

  // 12) SteelFrame_Co60
  Double_t ScaleFactor_SteelFrame_Co60 = Act_SteelFrame_Co60*AccptRunTime/Denom_SteelFrame_Co60;
  addChannelToStacks_2b2n("SteelFrame_Co60", ScaleFactor_SteelFrame_Co60, FillColor_SteelFrame_Co60, ExtStackColl_2b2n, infile_2b2n);

  // 13) CuPetals_Co60
  Double_t ScaleFactor_CuPetals_Co60 = Act_CuPetals_Co60*AccptRunTime/Denom_CuPetals_Co60;
  addChannelToStacks_2b2n("CuPetals_Co60", ScaleFactor_CuPetals_Co60, FillColor_CuPetals_Co60, ExtStackColl_2b2n, infile_2b2n);

  // 14) CuTower_Co60
  Double_t ScaleFactor_CuTower_Co60 = Act_CuTower_Co60*AccptRunTime/Denom_CuTower_Co60;
  addChannelToStacks_2b2n("CuTower_Co60", ScaleFactor_CuTower_Co60, FillColor_CuTower_Co60, ExtStackColl_2b2n, infile_2b2n);

  // 15) ScintInn_K40
  Double_t ScaleFactor_ScintInn_K40 = Act_ScintInn_K40*AccptRunTime/Denom_ScintInn_K40;
  addChannelToStacks_2b2n("ScintInn_K40", ScaleFactor_ScintInn_K40, FillColor_ScintInn_K40, ExtStackColl_2b2n, infile_2b2n);

  // 16) ScintOut_K40
  Double_t ScaleFactor_ScintOut_K40 = Act_ScintOut_K40*AccptRunTime/Denom_ScintOut_K40;
  addChannelToStacks_2b2n("ScintOut_K40", ScaleFactor_ScintOut_K40, FillColor_ScintOut_K40, ExtStackColl_2b2n, infile_2b2n);

  // 17) ScintPet_K40
  Double_t ScaleFactor_ScintPet_K40 = Act_ScintPet_K40*AccptRunTime/Denom_ScintPet_K40;
  addChannelToStacks_2b2n("ScintPet_K40", ScaleFactor_ScintPet_K40, FillColor_ScintPet_K40, ExtStackColl_2b2n, infile_2b2n);

  // 18) SScin_Pa234m
  Double_t ScaleFactor_SScin_Pa234m = Act_SScin_Pa234m*AccptRunTime/Denom_SScin_Pa234m;
  addChannelToStacks_2b2n("SScin_Pa234m", ScaleFactor_SScin_Pa234m, FillColor_SScin_Pa234m, ExtStackColl_2b2n, infile_2b2n);

  // 19) MuMetal_g1000 P1
  Double_t ScaleFactor_MuMetal_g1000_P1 = Act_MuMetal_g1000_P1*AccptRunTime/Denom_MuMetal_g1000;
  addChannelToStacks_2b2n("MuMetal_g1000_P1", ScaleFactor_MuMetal_g1000_P1, FillColor_MuMetal_g1000, ExtStackColl_2b2n, infile_2b2n);

  // 20) MuMetal_g1000 P2
  Double_t ScaleFactor_MuMetal_g1000_P2 = Act_MuMetal_g1000_P2*AccptRunTime/Denom_MuMetal_g1000;
  addChannelToStacks_2b2n("MuMetal_g1000_P2", ScaleFactor_MuMetal_g1000_P2, FillColor_MuMetal_g1000, ExtStackColl_2b2n, infile_2b2n);

  // 21) Neutrons P1
  Double_t ScaleFactor_Neutrons_P1 = Act_Neutrons_P1*AccptRunTime/Denom_Neutrons;
  addChannelToStacks_2b2n("Data_Neutrons_P1", ScaleFactor_Neutrons_P1, FillColor_Neutrons, ExtStackColl_2b2n, infile_2b2n);

  // 22) Neutrons P2
  Double_t ScaleFactor_Neutrons_P2 = Act_Neutrons_P2*AccptRunTime/Denom_Neutrons;
  addChannelToStacks_2b2n("Data_Neutrons_P2", ScaleFactor_Neutrons_P2, FillColor_Neutrons, ExtStackColl_2b2n, infile_2b2n);

  // ADD RADON BACKGROUNDS
  Double_t Act_SWire_Bi214_P1       = Activities_Rad[0];
  Double_t Act_SWire_Pb214_P1       = Activities_Rad[0];
  Double_t Act_SWire_Tl208_P1       = Activities_Rad[1];
  Double_t Act_SFoil_Bi214_In_P1    = Activities_Rad[2];
  Double_t Act_SFoil_Bi214_Out_P1   = Activities_Rad[3];
  Double_t Act_SFoil_Pb214_In_P1    = Activities_Rad[2];
  Double_t Act_SFoil_Pb214_Out_P1   = Activities_Rad[3];
  Double_t Act_SWire_Bi214_P2       = Activities_Rad[4];
  Double_t Act_SWire_Pb214_P2       = Activities_Rad[4];
  Double_t Act_SWire_Tl208_P2       = Activities_Rad[5];
  Double_t Act_SFoil_Bi214_In_P2    = Activities_Rad[6];
  Double_t Act_SFoil_Bi214_Out_P2   = Activities_Rad[7];
  Double_t Act_SFoil_Pb214_In_P2    = Activities_Rad[6];
  Double_t Act_SFoil_Pb214_Out_P2   = Activities_Rad[7];
  Double_t Act_SWire_Bi210          = Activities_Rad[8];
  Double_t Act_SFoil_SeNew_Bi210    = Activities_Rad[9];
  Double_t Act_SFoil_SeOld_Bi210    = Activities_Rad[10];
  Double_t Act_SFoil_Strip_Bi210    = Activities_Rad[11];
  Double_t Act_SScin_Bi210          = Activities_Rad[12];
  Double_t Act_SScin_Bi214_P1       = Activities_Rad[13];
  Double_t Act_SScin_Pb214_P1       = Activities_Rad[13];
  Double_t Act_SScin_Bi214_P2       = Activities_Rad[14];
  Double_t Act_SScin_Pb214_P2       = Activities_Rad[14];
  Double_t Act_Air_Bi214_P1         = Activities_Rad[15];
  Double_t Act_Air_Pb214_P1         = Activities_Rad[15];
  Double_t Act_Air_Tl208_P1         = Activities_Rad[16];
  Double_t Act_Air_Bi214_P2         = 0;
  Double_t Act_Air_Pb214_P2         = 0;
  Double_t Act_Air_Tl208_P2         = 0;

  Double_t Denom_SWire_Bi214 = Denominators_Rad[0];
  Double_t Denom_SWire_Pb214 = Denominators_Rad[1];
  Double_t Denom_SWire_Bi210 = Denominators_Rad[2];
  Double_t Denom_SWire_Tl208 = Denominators_Rad[3];
  Double_t Denom_SFoil_Bi214 = Denominators_Rad[4];
  Double_t Denom_SFoil_Pb214 = Denominators_Rad[5];
  Double_t Denom_SFoil_Bi210 = Denominators_Rad[6];
  Double_t Denom_SScin_Bi214 = Denominators_Rad[7];
  Double_t Denom_SScin_Pb214 = Denominators_Rad[8];
  Double_t Denom_SScin_Bi210 = Denominators_Rad[9];
  Double_t Denom_Air_Bi214   = Denominators_Rad[10];
  Double_t Denom_Air_Pb214   = Denominators_Rad[11];
  Double_t Denom_Air_Tl208   = Denominators_Rad[12];

  Int_t    FillColor_SWire_Bi214 = kRed;
  Int_t    FillColor_SWire_Pb214 = kRed+1;
  Int_t    FillColor_SWire_Bi210 = kRed+2;
  Int_t    FillColor_SWire_Tl208 = kAzure+2;
  Int_t    FillColor_SFoil_Bi214 = kBlue;
  Int_t    FillColor_SFoil_Pb214 = kBlue+1;
  Int_t    FillColor_SFoil_Bi210 = kBlue+2;
  Int_t    FillColor_SScin_Bi214 = kOrange;
  Int_t    FillColor_SScin_Pb214 = kOrange+1;
  Int_t    FillColor_SScin_Bi210 = kOrange+2;
  Int_t    FillColor_Air_Bi214 = kGreen+2;
  Int_t    FillColor_Air_Pb214 = kGreen+3;
  Int_t    FillColor_Air_Tl208 = kGreen+4;

  // Create collection of histogram stacks
  RadStackColl_2b2n[0] = new THStack("h_2b2n","Total Electron Energy");

  //  Add Radon Backgrounds

  // 0) SWire_Bi214
  Double_t Scale_SWire_Bi214_P1 = Act_SWire_Bi214_P1*AccptRunTime/Denom_SWire_Bi214;
  addChannelToStacks_2b2n("SWire_Bi214_P1", Scale_SWire_Bi214_P1, FillColor_SWire_Bi214, RadStackColl_2b2n, infile_2b2n);
  Double_t Scale_SWire_Bi214_P2 = Act_SWire_Bi214_P2*AccptRunTime/Denom_SWire_Bi214;
  addChannelToStacks_2b2n("SWire_Bi214_P2", Scale_SWire_Bi214_P2, FillColor_SWire_Bi214, RadStackColl_2b2n, infile_2b2n);

  // 1) SWire_Pb214
  Double_t Scale_SWire_Pb214_P1 = Act_SWire_Pb214_P1*AccptRunTime/Denom_SWire_Pb214;
  addChannelToStacks_2b2n("SWire_Pb214_P1", Scale_SWire_Pb214_P1, FillColor_SWire_Pb214, RadStackColl_2b2n, infile_2b2n);
  Double_t Scale_SWire_Pb214_P2 = Act_SWire_Pb214_P2*AccptRunTime/Denom_SWire_Pb214;
  addChannelToStacks_2b2n("SWire_Pb214_P2", Scale_SWire_Pb214_P2, FillColor_SWire_Pb214, RadStackColl_2b2n, infile_2b2n);

  // 2) SWire_Bi210 
  Double_t Scale_SWire_Bi210 = Act_SWire_Bi210*AccptRunTime/Denom_SWire_Bi210;
  addChannelToStacks_2b2n("SWire_Bi210_P1", Scale_SWire_Bi210, FillColor_SWire_Bi210, RadStackColl_2b2n, infile_2b2n);
  addChannelToStacks_2b2n("SWire_Bi210_P2", Scale_SWire_Bi210, FillColor_SWire_Bi210, RadStackColl_2b2n, infile_2b2n);

  // 3) SWire_Tl208 
  Double_t Scale_SWire_Tl208_P1 = Act_SWire_Tl208_P1*AccptRunTime/Denom_SWire_Tl208;
  addChannelToStacks_2b2n("SWire_Tl208_P1", Scale_SWire_Tl208_P1, FillColor_SWire_Tl208, RadStackColl_2b2n, infile_2b2n);
  Double_t Scale_SWire_Tl208_P2 = Act_SWire_Tl208_P2*AccptRunTime/Denom_SWire_Tl208;
  addChannelToStacks_2b2n("SWire_Tl208_P2", Scale_SWire_Tl208_P2, FillColor_SWire_Tl208, RadStackColl_2b2n, infile_2b2n);

  // 4) SFoil_Bi214_In
  Double_t ScaleFactor_SFoil_Bi214_In_P1 = Act_SFoil_Bi214_In_P1*AccptRunTime/Denom_SFoil_Bi214;
  addChannelToStacks_2b2n("SFoil_Bi214_In_P1", ScaleFactor_SFoil_Bi214_In_P1, FillColor_SFoil_Bi214, RadStackColl_2b2n, infile_2b2n);
  Double_t ScaleFactor_SFoil_Bi214_In_P2 = Act_SFoil_Bi214_In_P2*AccptRunTime/Denom_SFoil_Bi214;
  addChannelToStacks_2b2n("SFoil_Bi214_In_P2", ScaleFactor_SFoil_Bi214_In_P2, FillColor_SFoil_Bi214, RadStackColl_2b2n, infile_2b2n);

  // 5) SFoil_Bi214_Out
  Double_t ScaleFactor_SFoil_Bi214_Out_P1 = Act_SFoil_Bi214_Out_P1*AccptRunTime/Denom_SFoil_Bi214;
  addChannelToStacks_2b2n("SFoil_Bi214_Out_P1", ScaleFactor_SFoil_Bi214_Out_P1, FillColor_SFoil_Bi214, RadStackColl_2b2n, infile_2b2n);
  Double_t ScaleFactor_SFoil_Bi214_Out_P2 = Act_SFoil_Bi214_Out_P2*AccptRunTime/Denom_SFoil_Bi214;
  addChannelToStacks_2b2n("SFoil_Bi214_Out_P2", ScaleFactor_SFoil_Bi214_Out_P2, FillColor_SFoil_Bi214, RadStackColl_2b2n, infile_2b2n);

  // 6) SFoil_Pb214_In
  Double_t ScaleFactor_SFoil_Pb214_In_P1 = Act_SFoil_Pb214_In_P1*AccptRunTime/Denom_SFoil_Pb214;
  addChannelToStacks_2b2n("SFoil_Pb214_In_P1", ScaleFactor_SFoil_Pb214_In_P1, FillColor_SFoil_Pb214, RadStackColl_2b2n, infile_2b2n);
  Double_t ScaleFactor_SFoil_Pb214_In_P2 = Act_SFoil_Pb214_In_P2*AccptRunTime/Denom_SFoil_Pb214;
  addChannelToStacks_2b2n("SFoil_Pb214_In_P2", ScaleFactor_SFoil_Pb214_In_P2, FillColor_SFoil_Pb214, RadStackColl_2b2n, infile_2b2n);

  // 7) SFoil_Pb214_Out
  Double_t ScaleFactor_SFoil_Pb214_Out_P1 = Act_SFoil_Pb214_Out_P1*AccptRunTime/Denom_SFoil_Pb214;
  addChannelToStacks_2b2n("SFoil_Pb214_Out_P1", ScaleFactor_SFoil_Pb214_Out_P1, FillColor_SFoil_Pb214, RadStackColl_2b2n, infile_2b2n);
  Double_t ScaleFactor_SFoil_Pb214_Out_P2 = Act_SFoil_Pb214_Out_P2*AccptRunTime/Denom_SFoil_Pb214;
  addChannelToStacks_2b2n("SFoil_Pb214_Out_P2", ScaleFactor_SFoil_Pb214_Out_P2, FillColor_SFoil_Pb214, RadStackColl_2b2n, infile_2b2n);

  // 8) SFoil_SeNew_Bi210 
  Double_t ScaleFactor_SFoil_SeNew_Bi210 = Act_SFoil_SeNew_Bi210*AccptRunTime/Denom_SFoil_Bi210;
  addChannelToStacks_2b2n("SFoil_SeNew_Bi210_P1", ScaleFactor_SFoil_SeNew_Bi210, FillColor_SFoil_Bi210, RadStackColl_2b2n, infile_2b2n);
  addChannelToStacks_2b2n("SFoil_SeNew_Bi210_P2", ScaleFactor_SFoil_SeNew_Bi210, FillColor_SFoil_Bi210, RadStackColl_2b2n, infile_2b2n);

  // 9) SFoil_SeOld_Bi210 
  Double_t ScaleFactor_SFoil_SeOld_Bi210 = Act_SFoil_SeOld_Bi210*AccptRunTime/Denom_SFoil_Bi210;
  addChannelToStacks_2b2n("SFoil_SeOld_Bi210_P1", ScaleFactor_SFoil_SeOld_Bi210, FillColor_SFoil_Bi210, RadStackColl_2b2n, infile_2b2n);
  addChannelToStacks_2b2n("SFoil_SeOld_Bi210_P2", ScaleFactor_SFoil_SeOld_Bi210, FillColor_SFoil_Bi210, RadStackColl_2b2n, infile_2b2n);

  // 10) SFoil_Strip_Bi210 (in SeNew Dirty strip)
  Double_t ScaleFactor_SFoil_Strip_Bi210 = Act_SFoil_Strip_Bi210*AccptRunTime/Denom_SFoil_Bi210;
  addChannelToStacks_2b2n("SFoil_Strip_Bi210_P1", ScaleFactor_SFoil_Strip_Bi210, FillColor_SFoil_Bi210, RadStackColl_2b2n, infile_2b2n);
  addChannelToStacks_2b2n("SFoil_Strip_Bi210_P2", ScaleFactor_SFoil_Strip_Bi210, FillColor_SFoil_Bi210, RadStackColl_2b2n, infile_2b2n);

  // 11) SScin_Bi214
  Double_t ScaleFactor_SScin_Bi214_P1 = Act_SScin_Bi214_P1*AccptRunTime/Denom_SScin_Bi214;
  addChannelToStacks_2b2n("SScin_Bi214_P1", ScaleFactor_SScin_Bi214_P1, FillColor_SScin_Bi214, RadStackColl_2b2n, infile_2b2n);
  Double_t ScaleFactor_SScin_Bi214_P2 = Act_SScin_Bi214_P2*AccptRunTime/Denom_SScin_Bi214;
  addChannelToStacks_2b2n("SScin_Bi214_P2", ScaleFactor_SScin_Bi214_P2, FillColor_SScin_Bi214, RadStackColl_2b2n, infile_2b2n);

  // 12) SScin_Pb214
  Double_t ScaleFactor_SScin_Pb214_P1 = Act_SScin_Pb214_P1*AccptRunTime/Denom_SScin_Pb214;
  addChannelToStacks_2b2n("SScin_Pb214_P1", ScaleFactor_SScin_Pb214_P1, FillColor_SScin_Pb214, RadStackColl_2b2n, infile_2b2n);
  Double_t ScaleFactor_SScin_Pb214_P2 = Act_SScin_Pb214_P2*AccptRunTime/Denom_SScin_Pb214;
  addChannelToStacks_2b2n("SScin_Pb214_P2", ScaleFactor_SScin_Pb214_P2, FillColor_SScin_Pb214, RadStackColl_2b2n, infile_2b2n);

  // 13) SScin_Bi210
  Double_t ScaleFactor_SScin_Bi210 = Act_SScin_Bi210*AccptRunTime/Denom_SScin_Bi210;
  addChannelToStacks_2b2n("SScin_Bi210_P1", ScaleFactor_SScin_Bi210, FillColor_SScin_Bi210, RadStackColl_2b2n, infile_2b2n);
  addChannelToStacks_2b2n("SScin_Bi210_P2", ScaleFactor_SScin_Bi210, FillColor_SScin_Bi210, RadStackColl_2b2n, infile_2b2n);

  // 14) Air_Bi214
  Double_t ScaleFactor_Air_Bi214_P1 = Act_Air_Bi214_P1*AccptRunTime/Denom_Air_Bi214;
  addChannelToStacks_2b2n("Air_Bi214_P1", ScaleFactor_Air_Bi214_P1, FillColor_Air_Bi214, RadStackColl_2b2n, infile_2b2n);
  Double_t ScaleFactor_Air_Bi214_P2 = Act_Air_Bi214_P2*AccptRunTime/Denom_Air_Bi214;
  addChannelToStacks_2b2n("Air_Bi214_P2", ScaleFactor_Air_Bi214_P2, FillColor_Air_Bi214, RadStackColl_2b2n, infile_2b2n);

  // 15) Air_Pb214
  Double_t ScaleFactor_Air_Pb214_P1 = Act_Air_Pb214_P1*AccptRunTime/Denom_Air_Pb214;
  addChannelToStacks_2b2n("Air_Pb214_P1", ScaleFactor_Air_Pb214_P1, FillColor_Air_Pb214, RadStackColl_2b2n, infile_2b2n);
  Double_t ScaleFactor_Air_Pb214_P2 = Act_Air_Pb214_P2*AccptRunTime/Denom_Air_Pb214;
  addChannelToStacks_2b2n("Air_Pb214_P2", ScaleFactor_Air_Pb214_P2, FillColor_Air_Pb214, RadStackColl_2b2n, infile_2b2n);

  // 16) Air_Tl208
  Double_t ScaleFactor_Air_Tl208_P1 = Act_Air_Tl208_P1*AccptRunTime/Denom_Air_Tl208;
  addChannelToStacks_2b2n("Air_Tl208_P1", ScaleFactor_Air_Tl208_P1, FillColor_Air_Tl208, RadStackColl_2b2n, infile_2b2n);
  Double_t ScaleFactor_Air_Tl208_P2 = Act_Air_Tl208_P2*AccptRunTime/Denom_Air_Tl208;
  addChannelToStacks_2b2n("Air_Tl208_P2", ScaleFactor_Air_Tl208_P2, FillColor_Air_Tl208, RadStackColl_2b2n, infile_2b2n);

  // ADD INTERNAL BACKGROUNDS
  Double_t Act_SeNew_Bi214  = Activities_Int[0];
  Double_t Act_SeOld_Bi214  = Activities_Int[1];
  Double_t Act_Mylar_Bi214  = Activities_Int[2];
  Double_t Act_SeNew_Pb214  = Activities_Int[0];
  Double_t Act_SeOld_Pb214  = Activities_Int[1];
  Double_t Act_Mylar_Pb214  = Activities_Int[2];
  Double_t Act_SeNew_Tl208  = Activities_Int[3];
  Double_t Act_SeOld_Tl208  = Activities_Int[4];
  Double_t Act_SeNew_Bi212  = 2.782*Activities_Int[3];
  Double_t Act_SeOld_Bi212  = 2.782*Activities_Int[4];
  Double_t Act_SeNew_Ac228  = 2.782*Activities_Int[3];
  Double_t Act_SeOld_Ac228  = 2.782*Activities_Int[4];
  Double_t Act_SeNew_Pa234m = Activities_Int[5];
  Double_t Act_SeOld_Pa234m = Activities_Int[6];
  Double_t Act_SeNew_K40    = Activities_Int[7];
  Double_t Act_SeOld_K40    = Activities_Int[8];

  Double_t Denom_SeNew_Bi214  = Denominators_Int[0];
  Double_t Denom_SeOld_Bi214  = Denominators_Int[1];
  Double_t Denom_Mylar_Bi214  = Denominators_Int[2];
  Double_t Denom_SeNew_Pb214  = Denominators_Int[3];
  Double_t Denom_SeOld_Pb214  = Denominators_Int[4];
  Double_t Denom_Mylar_Pb214  = Denominators_Int[5];
  Double_t Denom_SeNew_Tl208  = Denominators_Int[6];
  Double_t Denom_SeOld_Tl208  = Denominators_Int[7];
  Double_t Denom_SeNew_Bi212  = Denominators_Int[8];
  Double_t Denom_SeOld_Bi212  = Denominators_Int[9];
  Double_t Denom_SeNew_Ac228  = Denominators_Int[10];
  Double_t Denom_SeOld_Ac228  = Denominators_Int[11];
  Double_t Denom_SeNew_Pa234m = Denominators_Int[12];
  Double_t Denom_SeOld_Pa234m = Denominators_Int[13];
  Double_t Denom_SeNew_K40    = Denominators_Int[14];
  Double_t Denom_SeOld_K40    = Denominators_Int[15];

  Int_t    FillColor_SeNew_Bi214 = kRed;
  Int_t    FillColor_SeOld_Bi214 = kRed;
  Int_t    FillColor_Mylar_Bi214 = kRed+1;
  Int_t    FillColor_SeNew_Pb214 = kRed+2;
  Int_t    FillColor_SeOld_Pb214 = kRed+2;
  Int_t    FillColor_Mylar_Pb214 = kRed+3;
  Int_t    FillColor_SeNew_Tl208 = kGreen;
  Int_t    FillColor_SeOld_Tl208 = kGreen;
  Int_t    FillColor_SeNew_Bi212 = kGreen+2;
  Int_t    FillColor_SeOld_Bi212 = kGreen+2;
  Int_t    FillColor_SeNew_Ac228 = kGreen+4;
  Int_t    FillColor_SeOld_Ac228 = kGreen+4;
  Int_t    FillColor_SeNew_Pa234m = kCyan;
  Int_t    FillColor_SeOld_Pa234m = kCyan;
  Int_t    FillColor_SeNew_K40 = kMagenta;
  Int_t    FillColor_SeOld_K40 = kMagenta;

  // Create collection of histogram stacks
  IntStackColl_2b2n[0] = new THStack("h_2b2n","Total Electron Energy");
  Bi214StackColl_2b2n[0] = new THStack("h_2b2n","Total Electron Energy");
  Tl208StackColl_2b2n[0] = new THStack("h_2b2n","Total Electron Energy");

  // Add Internal Backgrounds

  // 0) SeNew_Bi214
  Double_t ScaleFactor_SeNew_Bi214 = Act_SeNew_Bi214*AccptRunTime/Denom_SeNew_Bi214;
  addChannelToStacks_2b2n("SeNew_Bi214", ScaleFactor_SeNew_Bi214, FillColor_SeNew_Bi214, Bi214StackColl_2b2n, infile_2b2n);

  // 1) SeOld_Bi214
  Double_t ScaleFactor_SeOld_Bi214 = Act_SeOld_Bi214*AccptRunTime/Denom_SeOld_Bi214;
  addChannelToStacks_2b2n("SeOld_Bi214", ScaleFactor_SeOld_Bi214, FillColor_SeOld_Bi214, Bi214StackColl_2b2n, infile_2b2n);

  // 2) Mylar_Bi214
  Double_t ScaleFactor_Mylar_Bi214 = Act_Mylar_Bi214*AccptRunTime/Denom_Mylar_Bi214;
  addChannelToStacks_2b2n("Mylar_Bi214", ScaleFactor_Mylar_Bi214, FillColor_Mylar_Bi214, Bi214StackColl_2b2n, infile_2b2n);

  // 3) SeNew_Pb214
  Double_t ScaleFactor_SeNew_Pb214 = Act_SeNew_Pb214*AccptRunTime/Denom_SeNew_Pb214;
  addChannelToStacks_2b2n("SeNew_Pb214", ScaleFactor_SeNew_Pb214, FillColor_SeNew_Pb214, Bi214StackColl_2b2n, infile_2b2n);

  // 4) SeOld_Pb214
  Double_t ScaleFactor_SeOld_Pb214 = Act_SeOld_Pb214*AccptRunTime/Denom_SeOld_Pb214;
  addChannelToStacks_2b2n("SeOld_Pb214", ScaleFactor_SeOld_Pb214, FillColor_SeOld_Pb214, Bi214StackColl_2b2n, infile_2b2n);

  // 5) Mylar_Pb214
  Double_t ScaleFactor_Mylar_Pb214 = Act_Mylar_Pb214*AccptRunTime/Denom_Mylar_Pb214;
  addChannelToStacks_2b2n("Mylar_Pb214", ScaleFactor_Mylar_Pb214, FillColor_Mylar_Pb214, Bi214StackColl_2b2n, infile_2b2n);

  // 6) SeNew_Tl208
  Double_t ScaleFactor_SeNew_Tl208 = Act_SeNew_Tl208*AccptRunTime/Denom_SeNew_Tl208;
  addChannelToStacks_2b2n("SeNew_Tl208", ScaleFactor_SeNew_Tl208, FillColor_SeNew_Tl208, Tl208StackColl_2b2n, infile_2b2n);

  // 7) SeOld_Tl208
  Double_t ScaleFactor_SeOld_Tl208 = Act_SeOld_Tl208*AccptRunTime/Denom_SeOld_Tl208;
  addChannelToStacks_2b2n("SeOld_Tl208", ScaleFactor_SeOld_Tl208, FillColor_SeOld_Tl208, Tl208StackColl_2b2n, infile_2b2n);

  // 8) SeNew_Bi212
  Double_t ScaleFactor_SeNew_Bi212 = Act_SeNew_Bi212*AccptRunTime/Denom_SeNew_Bi212;
  addChannelToStacks_2b2n("SeNew_Bi212", ScaleFactor_SeNew_Bi212, FillColor_SeNew_Bi212, Tl208StackColl_2b2n, infile_2b2n);

  // 9) SeOld_Bi212
  Double_t ScaleFactor_SeOld_Bi212 = Act_SeOld_Bi212*AccptRunTime/Denom_SeOld_Bi212;
  addChannelToStacks_2b2n("SeOld_Bi212", ScaleFactor_SeOld_Bi212, FillColor_SeOld_Bi212, Tl208StackColl_2b2n, infile_2b2n);

  // 10) SeNew_Ac228
  Double_t ScaleFactor_SeNew_Ac228 = Act_SeNew_Ac228*AccptRunTime/Denom_SeNew_Ac228;
  addChannelToStacks_2b2n("SeNew_Ac228", ScaleFactor_SeNew_Ac228, FillColor_SeNew_Ac228, Tl208StackColl_2b2n, infile_2b2n);

  // 11) SeOld_Ac228
  Double_t ScaleFactor_SeOld_Ac228 = Act_SeOld_Ac228*AccptRunTime/Denom_SeOld_Ac228;
  addChannelToStacks_2b2n("SeOld_Ac228", ScaleFactor_SeOld_Ac228, FillColor_SeOld_Ac228, Tl208StackColl_2b2n, infile_2b2n);

  // 12) SeNew_Pa234m
  Double_t ScaleFactor_SeNew_Pa234m = Act_SeNew_Pa234m*AccptRunTime/Denom_SeNew_Pa234m;
  addChannelToStacks_2b2n("SeNew_Pa234m", ScaleFactor_SeNew_Pa234m, FillColor_SeNew_Pa234m, IntStackColl_2b2n, infile_2b2n);

  // 13) SeOld_Pa234m
  Double_t ScaleFactor_SeOld_Pa234m = Act_SeOld_Pa234m*AccptRunTime/Denom_SeOld_Pa234m;
  addChannelToStacks_2b2n("SeOld_Pa234m", ScaleFactor_SeOld_Pa234m, FillColor_SeOld_Pa234m, IntStackColl_2b2n, infile_2b2n);

  // 14) SeNew_K40
  Double_t ScaleFactor_SeNew_K40 = Act_SeNew_K40*AccptRunTime/Denom_SeNew_K40;
  addChannelToStacks_2b2n("SeNew_K40", ScaleFactor_SeNew_K40, FillColor_SeNew_K40, IntStackColl_2b2n, infile_2b2n);

  // 15) SeOld_K40
  Double_t ScaleFactor_SeOld_K40 = Act_SeOld_K40*AccptRunTime/Denom_SeOld_K40;
  addChannelToStacks_2b2n("SeOld_K40", ScaleFactor_SeOld_K40, FillColor_SeOld_K40, IntStackColl_2b2n, infile_2b2n);

  // ADD SIGNALS
  Double_t Act_2b2n       = Activities_Sig[0];
  Double_t Act_2b0n       = Activities_Sig[1];

  Double_t Denom_2b2n     = Denominators_Sig[0];
  Double_t Denom_2b0n     = Denominators_Sig[1];

  Int_t    FillColor_2b2n = kRed;
  Int_t    FillColor_2b0n = kViolet-2;

  // Create collection of histogram stacks
  SigStackColl_2b2n[0] = new THStack("h_2b2n","Total Electron Energy");

  // 0) 2b2n - SeOld & SeNew
  Double_t ScaleFactor_2b2n = Act_2b2n*AccptRunTime/Denom_2b2n;
  addChannelToStacks_2b2n("2b2n", ScaleFactor_2b2n, FillColor_2b2n, SigStackColl_2b2n, infile_2b2n);

  // 1) 2b0n m1 - SeOld & SeNew
  Double_t ScaleFactor_2b0n = Act_2b0n*AccptRunTime/Denom_2b0n;
  addChannelToStacks_2b2n("2b0n_m1", ScaleFactor_2b0n, FillColor_2b0n, SigStackColl_2b2n, infile_2b2n);

  // Also add 2b0n to separate stack for calculations
  SigStackColl_2b0n[0] = new THStack("h_2b0n","Total Electron Energy");
  addChannelToStacks_2b2n("2b0n_m1", 1.0/Denom_2b0n, FillColor_2b0n, SigStackColl_2b0n, infile_2b2n);

  // RADON BACKGROUNDS:   P1 | P2
  // 0) SWire_Bi214	    // 1) SWire_Bi214	    
  // 2) SWire_Pb214	    // 3) SWire_Pb214	    
  // 4) SWire_Bi210 	    // 5) SWire_Bi210 	    
  // 6) SWire_Tl208 	    // 7) SWire_Tl208 	    
  // 8) SFoil_Bi214_In	    // 9) SFoil_Bi214_In	    
  // 10)SFoil_Bi214_Out	    // 11)SFoil_Bi214_Out	    
  // 12)SFoil_Pb214_In	    // 13)SFoil_Pb214_In	    
  // 14) SFoil_Pb214_Out    // 15) SFoil_Pb214_Out    
  // 16) SFoil_SeNew_Bi210  // 17) SFoil_SeNew_Bi210  
  // 18) SFoil_SeOld_Bi210  // 19) SFoil_SeOld_Bi210  
  // 20) SFoil_Strip_Bi210  // 21) SFoil_Strip_Bi210  
  // 22) SScin_Bi214	    // 23) SScin_Bi214	    
  // 24) SScin_Pb214	    // 25) SScin_Pb214	    
  // 26) SScin_Bi210	    // 27) SScin_Bi210	    
  // 28) Air_Bi214	    // 29) Air_Bi214	    
  // 30) Air_Pb214          // 31) Air_Pb214  
  // 32) Air_Tl208          // 33) Air_Tl208  

  // INTERNAL BACKGROUNDS
  // 0) SeNew_Bi214
  // 1) SeOld_Bi214
  // 2) Mylar_Bi214
  // 3) SeNew_Pb214
  // 4) SeOld_Pb214
  // 5) Mylar_Pb214
  // 6) SeNew_Tl208
  // 7) SeOld_Tl208
  // 8) SeNew_Bi212
  // 9) SeOld_Bi212
  // 10) SeNew_Ac228
  // 11) SeOld_Ac228
  // 12) SeNew_Pa234m
  // 13) SeOld_Pa234m
  // 14) SeNew_K40
  // 15) SeOld_K40

  // Make Stack Containing all histograms for plotting
  StackColl_2b2n[0] = new THStack("h_2b2n","Total Electron Energy");

  // 0) External Backgrounds
  for(int j = 0; j < 1; j++){
    TH1D* hExt = (TH1D*)ExtStackColl_2b2n[j]->GetStack()->Last();
    hExt->SetFillColor(kTeal-6);
    StackColl_2b2n[j]->Add(hExt);
  }

  // 1) Radon Backgrounds
  for(int j = 0; j < 1; j++){
    TH1D* hRad = (TH1D*)RadStackColl_2b2n[j]->GetStack()->Last();
    hRad->SetFillColor(kGreen);
    StackColl_2b2n[j]->Add(hRad);
  }

  // 2) Internal Backgrounds
  for(int j = 0; j < 1; j++){
    TH1D* hInt = (TH1D*)IntStackColl_2b2n[j]->GetStack()->Last();
    hInt->SetFillColor(kAzure);
    StackColl_2b2n[j]->Add(hInt);
  }

  // 3) Bi214 Internal
  for(int j = 0; j < 1; j++){
    TH1D* hBi214 = (TH1D*)Bi214StackColl_2b2n[j]->GetStack()->Last();
    hBi214->SetFillColor(kAzure-1);
    StackColl_2b2n[j]->Add(hBi214);
  }

  // 4) Tl208 Internal
  for(int j = 0; j < 1; j++){
    TH1D* hTl208 = (TH1D*)Tl208StackColl_2b2n[j]->GetStack()->Last();
    hTl208->SetFillColor(kAzure-2);
    StackColl_2b2n[j]->Add(hTl208);
  }

  // 5) 2b2n Signal
  for(int j = 0; j < 1; j++){
    TH1D* h2b2n = (TH1D*)SigStackColl_2b2n[j]->GetStack()->At(0)->Clone("h2b2n");
    h2b2n->SetFillColor(kRed);
    StackColl_2b2n[j]->Add(h2b2n);
  }

  // 6) 2b0n Signal
  for(int j = 0; j < 1; j++){
    TH1D* h2b0n = (TH1D*)SigStackColl_2b2n[j]->GetStack()->At(1)->Clone("h2b0n");
    h2b0n->Add((TH1D*)SigStackColl_2b2n[j]->GetStack()->At(0),-1);
    h2b0n->SetFillColor(kViolet-2);
    StackColl_2b2n[j]->Add(h2b0n);
  }

  // Create legend to put on plots
  string LegIsotopes[7];
  string LegEntries[7];
  char buffer[100];

  // Create correlation matrix of all fitted parameters to use when calculating errors
  double CorrMatrix[44][44];
  for(int i = 0; i < 44; i++){
    for(int j = 0; j < 44; j++){
      CorrMatrix[i][j] = CovMatrix[i][j]/(sqrt(CovMatrix[i][i])*sqrt(CovMatrix[j][j]));
    }
  }

  // Create correlation matrix and arrays of errors for external samples only
  int ExtFitIndex[23]   = {11, 16, 21, 21, 25, 12, 18, 23, 23, 26, 27, 28, 17, 22, 22, 13, 14, 15, 31, 32, 33, 34, 35};
  int ExtDenomIndex[23] = { 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 19, 20, 20};

  double ExtCorrMatrix[23][23];
  for(int i = 0; i < 23; i++){
    for(int j = 0; j < 23; j++){
      ExtCorrMatrix[i][j] = CorrMatrix[ExtFitIndex[i]][ExtFitIndex[j]];
    }
  }

  double ExtEvtsActErr[23];
  double ExtEvtsEffErr[23];
  for(int i = 0; i < 23; i++){
    double N, nEntries;
    if(i == 0){
      N        = ((TH1D*)ExtStackColl_2b2n[0]->GetStack()->At(0))->Integral();
      nEntries = ((TH1D*)ExtStackColl_2b2n[0]->GetStack()->At(0))->GetEntries();
    } else {
      N        = ((TH1D*)ExtStackColl_2b2n[0]->GetStack()->At(i))->Integral() - ((TH1D*)ExtStackColl_2b2n[0]->GetStack()->At(i-1))->Integral();
      nEntries = ((TH1D*)ExtStackColl_2b2n[0]->GetStack()->At(i))->GetEntries() - ((TH1D*)ExtStackColl_2b2n[0]->GetStack()->At(i-1))->GetEntries();
    }
    ExtEvtsActErr[i] = N * (AdjustActs_Err[ExtFitIndex[i]]/AdjustActs[ExtFitIndex[i]]);
    if(nEntries > 0){
      ExtEvtsEffErr[i] = N * sqrt( (1.0 - nEntries/Denominators_Ext[ExtDenomIndex[i]])/nEntries);
    } else {
      ExtEvtsEffErr[i] = 0;
    }
  }

  // Calculate error on num of external MC events from activity errors and efficiency errors
  Double_t NExtEvtsActErr2 = 0;
  Double_t NExtEvtsEffErr2 = 0;
  for(int i = 0; i < 23; i++){
    for(int j = i; j < 23; j++){
      NExtEvtsActErr2 += ExtCorrMatrix[i][j]*ExtEvtsActErr[i]*ExtEvtsActErr[j];
    }
    NExtEvtsEffErr2 += ExtEvtsEffErr[i]*ExtEvtsEffErr[i];
  }

  LegIsotopes[0] = "External BGs";
  sprintf (buffer, "%.1f #pm %.1f Entries", ((TH1D*)ExtStackColl_2b2n[0]->GetStack()->Last())->Integral(), sqrt(NExtEvtsActErr2+NExtEvtsEffErr2));
  LegEntries[0] = buffer;

  // Create correlation matrix and array of errors for radon samples only
  int RadFitIndex[34]   = { 3,  4,  3,  4, 30, 30,  7,  8,  3,  5,  3,  6,  3,  5,  3,  6,
			   36, 36, 37, 37, 38, 38,  3, 19,  3, 19, 29, 29, 20, 20, 20, 20, 24, 24};
  int RadDenomIndex[34] = { 0,  0,  1,  1,  2,  2,  3,  3,  4,  4,  4,  4,  5,  5,  5,  5,
			    6,  6,  6,  6,  6,  6,  7,  7,  8,  8,  9,  9, 10, 10, 11, 11, 12, 12};

  double RadCorrMatrix[34][34];
  for(int i = 0; i < 34; i++){
    for(int j = 0; j < 34; j++){
      RadCorrMatrix[i][j] = CorrMatrix[RadFitIndex[i]][RadFitIndex[j]];
    }
  }

  double RadEvtsActErr[34];
  double RadEvtsEffErr[34];
  for(int i = 0; i < 34; i++){
    double N, nEntries;
    if(i == 0){
      N        = ((TH1D*)RadStackColl_2b2n[0]->GetStack()->At(0))->Integral();
      nEntries = ((TH1D*)RadStackColl_2b2n[0]->GetStack()->At(0))->GetEntries();
    } else {
      N        = ((TH1D*)RadStackColl_2b2n[0]->GetStack()->At(i))->Integral() - ((TH1D*)RadStackColl_2b2n[0]->GetStack()->At(i-1))->Integral();
      nEntries = ((TH1D*)RadStackColl_2b2n[0]->GetStack()->At(i))->GetEntries() - ((TH1D*)RadStackColl_2b2n[0]->GetStack()->At(i-1))->GetEntries();
    }
    RadEvtsActErr[i] = N * (AdjustActs_Err[RadFitIndex[i]]/AdjustActs[RadFitIndex[i]]);
    if(nEntries > 0){
      RadEvtsEffErr[i] = N * sqrt( (1.0 - nEntries/Denominators_Rad[RadDenomIndex[i]])/nEntries);
    } else {
      RadEvtsEffErr[i] = 0;
    }
  }

  // Calculate error on num of radon MC events
  Double_t NRadEvtsActErr2 = 0;
  Double_t NRadEvtsEffErr2 = 0;
  for(int i = 0; i < 34; i++){
    for(int j = i; j < 34; j++){
      NRadEvtsActErr2 += RadCorrMatrix[i][j]*RadEvtsActErr[i]*RadEvtsActErr[j];
    }
    NRadEvtsEffErr2 += RadEvtsEffErr[i]*RadEvtsEffErr[i];
  }

  LegIsotopes[1] = "Radon BGs";
  sprintf (buffer, "%.1f #pm %.1f Entries", ((TH1D*)RadStackColl_2b2n[0]->GetStack()->Last())->Integral(), sqrt(NRadEvtsActErr2+NRadEvtsEffErr2));
  LegEntries[1] = buffer;

  // Create correlation matrix and array of errors for internal samples only
  int IntFitIndex[4]   = { 39, 40, 41, 42};
  int IntDenomIndex[4] = { 12, 13, 14, 15};

  double IntCorrMatrix[4][4];
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 4; j++){
      IntCorrMatrix[i][j] = CorrMatrix[IntFitIndex[i]][IntFitIndex[j]];
    }
  }

  double IntEvtsActErr[4];
  double IntEvtsEffErr[4];
  for(int i = 0; i < 4; i++){
    double N, nEntries;
    if(i == 0){
      N        = ((TH1D*)IntStackColl_2b2n[0]->GetStack()->At(0))->Integral();
      nEntries = ((TH1D*)IntStackColl_2b2n[0]->GetStack()->At(0))->GetEntries();
    } else {
      N        = ((TH1D*)IntStackColl_2b2n[0]->GetStack()->At(i))->Integral() - ((TH1D*)IntStackColl_2b2n[0]->GetStack()->At(i-1))->Integral();
      nEntries = ((TH1D*)IntStackColl_2b2n[0]->GetStack()->At(i))->GetEntries() - ((TH1D*)IntStackColl_2b2n[0]->GetStack()->At(i-1))->GetEntries();
    }

    IntEvtsActErr[i] = N * (AdjustActs_Err[IntFitIndex[i]]/AdjustActs[IntFitIndex[i]]);
    if(nEntries > 0){
      IntEvtsEffErr[i] = N * sqrt( (1.0 - nEntries/Denominators_Int[IntDenomIndex[i]])/nEntries);
    } else {
      IntEvtsEffErr[i] = 0;
    }
  }

  // Calculate error on num of internal MC events
  Double_t NIntEvtsActErr2 = 0;
  Double_t NIntEvtsEffErr2 = 0;
  for(int i = 0; i < 4; i++){
    for(int j = i; j < 4; j++){
      NIntEvtsActErr2 += IntCorrMatrix[i][j]*IntEvtsActErr[i]*IntEvtsActErr[j];
    }
    NIntEvtsEffErr2 += IntEvtsEffErr[i]*IntEvtsEffErr[i];
  }

  LegIsotopes[2] = "Internal ^{40}K & ^{234m}Pa";
  sprintf (buffer, "%.1f #pm %.1f Entries", ((TH1D*)IntStackColl_2b2n[0]->GetStack()->Last())->Integral(), sqrt(NIntEvtsActErr2+NIntEvtsEffErr2));
  LegEntries[2] = buffer;

  // Create correlation matrix and array of errors for internal Bi-214 samples only
  int Bi214FitIndex[6]   = { 0, 1, 2, 0, 1, 2};
  int Bi214DenomIndex[6] = { 0, 1, 2, 3, 4, 5};

  double Bi214CorrMatrix[6][6];
  for(int i = 0; i < 6; i++){
    for(int j = 0; j < 6; j++){
      Bi214CorrMatrix[i][j] = CorrMatrix[Bi214FitIndex[i]][Bi214FitIndex[j]];
    }
  }

  double Bi214EvtsActErr[6];
  double Bi214EvtsEffErr[6];
  for(int i = 0; i < 6; i++){
    double N, nEntries;
    if(i == 0){
      N        = ((TH1D*)Bi214StackColl_2b2n[0]->GetStack()->At(0))->Integral();
      nEntries = ((TH1D*)Bi214StackColl_2b2n[0]->GetStack()->At(0))->GetEntries();
    } else {
      N        = ((TH1D*)Bi214StackColl_2b2n[0]->GetStack()->At(i))->Integral() - ((TH1D*)Bi214StackColl_2b2n[0]->GetStack()->At(i-1))->Integral();
      nEntries = ((TH1D*)Bi214StackColl_2b2n[0]->GetStack()->At(i))->GetEntries() - ((TH1D*)Bi214StackColl_2b2n[0]->GetStack()->At(i-1))->GetEntries();
    }

    Bi214EvtsActErr[i] = N * (AdjustActs_Err[Bi214FitIndex[i]]/AdjustActs[Bi214FitIndex[i]]);
    if(nEntries > 0){
      Bi214EvtsEffErr[i] = N * sqrt( (1.0 - nEntries/Denominators_Int[Bi214DenomIndex[i]])/nEntries);
    } else {
      Bi214EvtsEffErr[i] = 0;
    }
  }

  // Calculate error on num of internal MC events
  Double_t NBi214EvtsActErr2 = 0;
  Double_t NBi214EvtsEffErr2 = 0;
  for(int i = 0; i < 6; i++){
    for(int j = i; j < 6; j++){
      NBi214EvtsActErr2 += Bi214CorrMatrix[i][j]*Bi214EvtsActErr[i]*Bi214EvtsActErr[j];
    }
    NBi214EvtsEffErr2 += Bi214EvtsEffErr[i]*Bi214EvtsEffErr[i];
  }

  LegIsotopes[3] = "Internal ^{214}Bi,^{214}Pb";
  sprintf (buffer, "%.1f #pm %.1f Entries", ((TH1D*)Bi214StackColl_2b2n[0]->GetStack()->Last())->Integral(), sqrt(NBi214EvtsActErr2+NBi214EvtsEffErr2));
  LegEntries[3] = buffer;

  // Create correlation matrix and array of errors for internal Tl208
  int Tl208FitIndex[6]   = { 9, 10, 9, 10, 9, 10};
  int Tl208DenomIndex[6] = { 6,  7, 8, 9, 10, 11};

  double Tl208CorrMatrix[6][6];
  for(int i = 0; i < 6; i++){
    for(int j = 0; j < 6; j++){
      Tl208CorrMatrix[i][j] = CorrMatrix[Tl208FitIndex[i]][Tl208FitIndex[j]];
    }
  }

  double Tl208EvtsActErr[6];
  double Tl208EvtsEffErr[6];
  for(int i = 0; i < 6; i++){
    double N, nEntries;
    if(i == 0){
      N        = ((TH1D*)Tl208StackColl_2b2n[0]->GetStack()->At(0))->Integral();
      nEntries = ((TH1D*)Tl208StackColl_2b2n[0]->GetStack()->At(0))->GetEntries();
    } else {
      N        = ((TH1D*)Tl208StackColl_2b2n[0]->GetStack()->At(i))->Integral() - ((TH1D*)Tl208StackColl_2b2n[0]->GetStack()->At(i-1))->Integral();
      nEntries = ((TH1D*)Tl208StackColl_2b2n[0]->GetStack()->At(i))->GetEntries() - ((TH1D*)Tl208StackColl_2b2n[0]->GetStack()->At(i-1))->GetEntries();
    }

    Tl208EvtsActErr[i] = N * (AdjustActs_Err[Tl208FitIndex[i]]/AdjustActs[Tl208FitIndex[i]]);
    if(nEntries > 0){
      Tl208EvtsEffErr[i] = N * sqrt( (1.0 - nEntries/Denominators_Int[Tl208DenomIndex[i]])/nEntries);
    } else {
      Tl208EvtsEffErr[i] = 0;
    }
  }

  // Calculate error on num of internal Tl208 events
  Double_t NTl208EvtsActErr2 = 0;
  Double_t NTl208EvtsEffErr2 = 0;
  for(int i = 0; i < 6; i++){
    for(int j = i; j < 6; j++){
      NTl208EvtsActErr2 += Tl208CorrMatrix[i][j]*Tl208EvtsActErr[i]*Tl208EvtsActErr[j];
    }
    NTl208EvtsEffErr2 += Tl208EvtsEffErr[i]*Tl208EvtsEffErr[i];
  }

  LegIsotopes[4] = "Internal ^{208}Tl,^{228}Ac,^{212}Bi";
  sprintf (buffer, "%.1f #pm %.1f Entries", ((TH1D*)Tl208StackColl_2b2n[0]->GetStack()->Last())->Integral(), sqrt(NTl208EvtsActErr2+NTl208EvtsEffErr2));
  LegEntries[4] = buffer;

  // Finally calculate error on number of signal events
  Double_t NSigEvts = ((TH1D*)SigStackColl_2b2n[0]->GetStack()->At(0))->Integral();
  Double_t nSigEntries = ((TH1D*)SigStackColl_2b2n[0]->GetStack()->At(0))->GetEntries();
  Double_t SigEvtsErr = NSigEvts*sqrt(pow(Activities_Sig_Err[0]/Activities_Sig[0],2) + pow((1.0 - nSigEntries/Denominators_Sig[0])/nSigEntries,2));

  LegIsotopes[5] = "2#beta2#nu Signal";
  sprintf (buffer, "%.1f #pm %.1f Entries", NSigEvts, SigEvtsErr);
  LegEntries[5] = buffer;

  Double_t NSigEvts_0n = ((TH1D*)SigStackColl_2b2n[0]->GetStack()->At(1))->Integral() - ((TH1D*)SigStackColl_2b2n[0]->GetStack()->At(0))->Integral();
  LegIsotopes[6] = "2#beta0#nu Limit";
  sprintf (buffer, "< %.1f Entries", NSigEvts_0n);
  LegEntries[6] = buffer;

  // Make legends
  for(int i = 0; i < 1; i++){
    Legend_2b2n[i] = new TLegend(0.595,0.6476,0.947,0.947);
    Legend_2b2n[i]->SetNColumns(2);
    Legend_2b2n[i]->SetColumnSeparation(-0.05);
    Legend_2b2n[i]->SetFillColor(0);
    Legend_2b2n[i]->SetLineColor(0);
    Legend_2b2n[i]->SetBorderSize(0);
    LegendLog_2b2n[i] = new TLegend(0.7199,0.4845,0.947,0.947);
    LegendLog_2b2n[i]->SetFillColor(0);
    LegendLog_2b2n[i]->SetLineColor(0);
    LegendLog_2b2n[i]->SetBorderSize(0);
  }
 
  char Num_Events[40];

  sprintf (Num_Events, "%d Entries", (int) h_2b2n_Data->GetEntries());
  Legend_2b2n[0]->AddEntry(h_2b2n_Data, "Data", "lpe");
  Legend_2b2n[0]->AddEntry(h_2b2n_Data, Num_Events, "");
  LegendLog_2b2n[0]->AddEntry(h_2b2n_Data, "Data", "lpe");

  for(int j = 0; j < 1; j++){
    TH1 *h;
    TIter   next(StackColl_2b2n[j]->GetHists());
    for(int i = 0; i < 7; i++){
      h = (TH1*) next();
      Legend_2b2n[j]->AddEntry(h, LegIsotopes[i].c_str(), "f");
      Legend_2b2n[j]->AddEntry(h, LegEntries[i].c_str(), "");
      LegendLog_2b2n[j]->AddEntry(h, LegIsotopes[i].c_str(), "f");
    }
  }

  // Make chi square template
  for (int i = 0; i < 1; i++){
    ChiSquares_2b2n[i] = new TPaveText(0.629,0.505,0.867,0.637,"LNDC");
    ChiSquares_2b2n[i]->SetFillColor(0);
    ChiSquares_2b2n[i]->SetLineColor(0);
    ChiSquares_2b2n[i]->SetBorderSize(0);
    ChiSquares_2b2n[i]->SetTextAlign(12);

    ChiSquaresLog_2b2n[i] = new TPaveText(0.693,0.51166,0.9298,0.6439,"LNDC");
    ChiSquaresLog_2b2n[i]->SetFillColor(0);
    ChiSquaresLog_2b2n[i]->SetLineColor(0);
    ChiSquaresLog_2b2n[i]->SetBorderSize(0);
    ChiSquaresLog_2b2n[i]->SetTextAlign(12);
  }

  char ChiSquareText[100];
  pair<Double_t,Int_t> ChiSquareResult;

  Double_t Halflife_2b2n     = (log(2)/(86400.0*365.25))/(Activities_Sig[0]*82.0/(6.022e23*932.4));
  Double_t Halflife_2b2n_Err = Halflife_2b2n*Activities_Sig_Err[0]/Activities_Sig[0];

  Double_t Halflife_2b0n     = (log(2)/(86400.0*365.25))/(Activities_Sig[1]*82.0/(6.022e23*932.4));

  char HalfLifeText[100];
  char HalfLifeText_0n[100];
  sprintf(HalfLifeText, "T_{1/2}^{2#nu} = (%.2f #pm %.2f) x 10^{19} yrs", Halflife_2b2n/1.0e19, Halflife_2b2n_Err/1.0e19);
  sprintf(HalfLifeText_0n, "T_{1/2}^{0#nu} > %.2f x 10^{23} yrs", Halflife_2b0n/1.0e23);

  ChiSquareResult = ChiSquareTest(h_2b2n_Data, (TH1D*)StackColl_2b2n[0]->GetStack()->Last());
  sprintf(ChiSquareText, "#chi^{2} / ndf = %.2f / %.d", ChiSquareResult.first, ChiSquareResult.second);
  ChiSquares_2b2n[0]->AddText(HalfLifeText);
  ChiSquares_2b2n[0]->AddText(HalfLifeText_0n);
  ChiSquares_2b2n[0]->AddText(ChiSquareText);
  ChiSquaresLog_2b2n[0]->AddText(HalfLifeText);
  ChiSquaresLog_2b2n[0]->AddText(HalfLifeText_0n);
  ChiSquaresLog_2b2n[0]->AddText(ChiSquareText);

  // Add lines to stop 'unused variable' warning when compiling
  Activities_Int[0] += 1;       Activities_Int[0] -= 1;
  Activities_Int_Err[0] += 1;   Activities_Int_Err[0] -= 1;
  Denominators_Int[0] += 1;     Denominators_Int[0] -= 1;
  Activities_Ext[0] += 1;       Activities_Ext[0] -= 1;
  Activities_Ext_Err[0] += 1;   Activities_Ext_Err[0] -= 1;
  Denominators_Ext[0] += 1;     Denominators_Ext[0] -= 1;
  Activities_Rad[0] += 1;       Activities_Rad[0] -= 1;
  Activities_Rad_Err[0] += 1;   Activities_Rad_Err[0] -= 1;
  Denominators_Rad[0] += 1;     Denominators_Rad[0] -= 1;
  Activities_Sig[0] += 1;       Activities_Sig[0] -= 1;
  Activities_Sig_Err[0] += 1;   Activities_Sig_Err[0] -= 1;
  Denominators_Sig[0] += 1;     Denominators_Sig[0] -= 1;
  AdjustActs[0] += 1;           AdjustActs[0] -= 1;
  AdjustActs_Err[0] += 1;       AdjustActs_Err[0] -= 1;

}
