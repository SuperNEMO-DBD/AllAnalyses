#include "addChannelToStacks_OCE.h"
#include "chiSquareTest.h"

extern THStack* StackColl_OCE[];
extern THStack* ExtStackColl_OCE[];
extern THStack* RadStackColl_OCE[];
extern THStack* IntStackColl_OCE[];
extern THStack* SigStackColl_OCE[];
extern TH1D* h_OCE_Data_P1_Inner;
extern TH1D* h_OCE_Data_P1_Outer;
extern TH1D* h_OCE_Data_P1_Petal;
extern TH1D* h_OCE_Data_P2_Inner;
extern TH1D* h_OCE_Data_P2_Outer;
extern TH1D* h_OCE_Data_P2_Petal;
extern const Int_t AccptRunTime;
extern TFile* infile_OCE;
extern TLegend* Legend_OCE[];
extern TLegend* LegendLog_OCE[];
extern TPaveText* ChiSquares_OCE[];
extern TPaveText* ChiSquaresLog_OCE[];

void addBackgrounds_OCE(double *Activities_Ext, double *Activities_Ext_Err, double *Denominators_Ext, double *Activities_Rad, double *Activities_Rad_Err,  double *Denominators_Rad, double *Activities_Int, double *Activities_Int_Err,  double *Denominators_Int, double *Activities_Sig, double *Activities_Sig_Err, double *Denominators_Sig, double *AdjustActs, double *AdjustActs_Err){

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

  Double_t Act_PMT_K40_Err          = Activities_Ext_Err[0];
  Double_t Act_PMT_Bi214_Err        = Activities_Ext_Err[1];
  Double_t Act_PMT_Tl208_Err        = Activities_Ext_Err[2];
  Double_t Act_MuMetal_Co60_Err     = Activities_Ext_Err[4];
  Double_t Act_SteelFrame_K40_Err   = Activities_Ext_Err[5];
  Double_t Act_SteelFrame_Bi214_Err = Activities_Ext_Err[6];
  Double_t Act_SteelFrame_Tl208_Err = Activities_Ext_Err[7];
  Double_t Act_SteelFrame_Co60_Err  = Activities_Ext_Err[9];
  Double_t Act_CuPetals_Co60_Err    = Activities_Ext_Err[10];
  Double_t Act_CuTower_Co60_Err     = Activities_Ext_Err[11];
  Double_t Act_FeShield_Bi214_Err   = Activities_Ext_Err[12];
  Double_t Act_FeShield_Tl208_Err   = Activities_Ext_Err[13];
  Double_t Act_ScintInn_K40_Err     = Activities_Ext_Err[15];
  Double_t Act_ScintOut_K40_Err     = Activities_Ext_Err[16];
  Double_t Act_ScintPet_K40_Err     = Activities_Ext_Err[17];
  Double_t Act_SScin_Pa234m_Err     = Activities_Ext_Err[18];
  Double_t Act_MuMetal_g1000_P1_Err = Activities_Ext_Err[19];
  Double_t Act_MuMetal_g1000_P2_Err = Activities_Ext_Err[20];
  Double_t Act_Neutrons_P1_Err      = Activities_Ext_Err[21];
  Double_t Act_Neutrons_P2_Err      = Activities_Ext_Err[22];

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
  ExtStackColl_OCE[0] = new THStack("h_OCE_P1_Inner","Electron Energy");
  ExtStackColl_OCE[1] = new THStack("h_OCE_P1_Outer","Electron Energy");
  ExtStackColl_OCE[2] = new THStack("h_OCE_P1_Petal","Electron Energy");
  ExtStackColl_OCE[3] = new THStack("h_OCE_P2_Inner","Electron Energy");
  ExtStackColl_OCE[4] = new THStack("h_OCE_P2_Outer","Electron Energy");
  ExtStackColl_OCE[5] = new THStack("h_OCE_P2_Petal","Electron Energy");

  // Add External Backgrounds

  // 0) PMT_K40
  Double_t ScaleFactor_PMT_K40 = Act_PMT_K40*AccptRunTime/Denom_PMT_K40;
  addChannelToStacks_OCE("PMT_K40", ScaleFactor_PMT_K40, FillColor_PMT_K40, ExtStackColl_OCE, infile_OCE);

  // 1) PMT_Bi214
  Double_t ScaleFactor_PMT_Bi214 = Act_PMT_Bi214*AccptRunTime/Denom_PMT_Bi214;
  addChannelToStacks_OCE("PMT_Bi214", ScaleFactor_PMT_Bi214, FillColor_PMT_Bi214, ExtStackColl_OCE, infile_OCE);

  // 2) PMT_Tl208
  Double_t ScaleFactor_PMT_Tl208 = Act_PMT_Tl208*AccptRunTime/Denom_PMT_Tl208;
  addChannelToStacks_OCE("PMT_Tl208", ScaleFactor_PMT_Tl208, FillColor_PMT_Tl208, ExtStackColl_OCE, infile_OCE);

  // 3) PMT_Ac228
  Double_t ScaleFactor_PMT_Ac228 = Act_PMT_Ac228*AccptRunTime/Denom_PMT_Ac228;
  addChannelToStacks_OCE("PMT_Ac228", ScaleFactor_PMT_Ac228, FillColor_PMT_Ac228, ExtStackColl_OCE, infile_OCE);

  // 4) FeShield_Bi214
  Double_t ScaleFactor_FeShield_Bi214 = Act_FeShield_Bi214*AccptRunTime/Denom_FeShield_Bi214;
  addChannelToStacks_OCE("FeShield_Bi214", ScaleFactor_FeShield_Bi214, FillColor_FeShield_Bi214, ExtStackColl_OCE, infile_OCE);

  // 5) FeShield_Tl208
  Double_t ScaleFactor_FeShield_Tl208 = Act_FeShield_Tl208*AccptRunTime/Denom_FeShield_Tl208;
  addChannelToStacks_OCE("FeShield_Tl208", ScaleFactor_FeShield_Tl208, FillColor_FeShield_Tl208, ExtStackColl_OCE, infile_OCE);

  // 6) FeShield_Ac228
  Double_t ScaleFactor_FeShield_Ac228 = Act_FeShield_Ac228*AccptRunTime/Denom_FeShield_Ac228;
  addChannelToStacks_OCE("FeShield_Ac228", ScaleFactor_FeShield_Ac228, FillColor_FeShield_Ac228, ExtStackColl_OCE, infile_OCE);

  // 7) MuMetal_Co60
  Double_t ScaleFactor_MuMetal_Co60 = Act_MuMetal_Co60*AccptRunTime/Denom_MuMetal_Co60;
  addChannelToStacks_OCE("MuMetal_Co60", ScaleFactor_MuMetal_Co60, FillColor_MuMetal_Co60, ExtStackColl_OCE, infile_OCE);

  // 8) SteelFrame_K40
  Double_t ScaleFactor_SteelFrame_K40 = Act_SteelFrame_K40*AccptRunTime/Denom_SteelFrame_K40;
  addChannelToStacks_OCE("SteelFrame_K40", ScaleFactor_SteelFrame_K40, FillColor_SteelFrame_K40, ExtStackColl_OCE, infile_OCE);

  // 9) SteelFrame_Bi214
  Double_t ScaleFactor_SteelFrame_Bi214 = Act_SteelFrame_Bi214*AccptRunTime/Denom_SteelFrame_Bi214;
  addChannelToStacks_OCE("SteelFrame_Bi214", ScaleFactor_SteelFrame_Bi214, FillColor_SteelFrame_Bi214, ExtStackColl_OCE, infile_OCE);

  // 10) SteelFrame_Tl208
  Double_t ScaleFactor_SteelFrame_Tl208 = Act_SteelFrame_Tl208*AccptRunTime/Denom_SteelFrame_Tl208;
  addChannelToStacks_OCE("SteelFrame_Tl208", ScaleFactor_SteelFrame_Tl208, FillColor_SteelFrame_Tl208, ExtStackColl_OCE, infile_OCE);

  // 11) SteelFrame_Ac228
  Double_t ScaleFactor_SteelFrame_Ac228 = Act_SteelFrame_Ac228*AccptRunTime/Denom_SteelFrame_Ac228;
  addChannelToStacks_OCE("SteelFrame_Ac228", ScaleFactor_SteelFrame_Ac228, FillColor_SteelFrame_Ac228, ExtStackColl_OCE, infile_OCE);

  // 12) SteelFrame_Co60
  Double_t ScaleFactor_SteelFrame_Co60 = Act_SteelFrame_Co60*AccptRunTime/Denom_SteelFrame_Co60;
  addChannelToStacks_OCE("SteelFrame_Co60", ScaleFactor_SteelFrame_Co60, FillColor_SteelFrame_Co60, ExtStackColl_OCE, infile_OCE);

  // 13) CuPetals_Co60
  Double_t ScaleFactor_CuPetals_Co60 = Act_CuPetals_Co60*AccptRunTime/Denom_CuPetals_Co60;
  addChannelToStacks_OCE("CuPetals_Co60", ScaleFactor_CuPetals_Co60, FillColor_CuPetals_Co60, ExtStackColl_OCE, infile_OCE);

  // 14) CuTower_Co60
  Double_t ScaleFactor_CuTower_Co60 = Act_CuTower_Co60*AccptRunTime/Denom_CuTower_Co60;
  addChannelToStacks_OCE("CuTower_Co60", ScaleFactor_CuTower_Co60, FillColor_CuTower_Co60, ExtStackColl_OCE, infile_OCE);

  // 15) ScintInn_K40
  Double_t ScaleFactor_ScintInn_K40 = Act_ScintInn_K40*AccptRunTime/Denom_ScintInn_K40;
  addChannelToStacks_OCE("ScintInn_K40", ScaleFactor_ScintInn_K40, FillColor_ScintInn_K40, ExtStackColl_OCE, infile_OCE);

  // 16) ScintOut_K40
  Double_t ScaleFactor_ScintOut_K40 = Act_ScintOut_K40*AccptRunTime/Denom_ScintOut_K40;
  addChannelToStacks_OCE("ScintOut_K40", ScaleFactor_ScintOut_K40, FillColor_ScintOut_K40, ExtStackColl_OCE, infile_OCE);

  // 17) ScintPet_K40
  Double_t ScaleFactor_ScintPet_K40 = Act_ScintPet_K40*AccptRunTime/Denom_ScintPet_K40;
  addChannelToStacks_OCE("ScintPet_K40", ScaleFactor_ScintPet_K40, FillColor_ScintPet_K40, ExtStackColl_OCE, infile_OCE);

  // 18) SScin_Pa234m
  Double_t ScaleFactor_SScin_Pa234m = Act_SScin_Pa234m*AccptRunTime/Denom_SScin_Pa234m;
  addChannelToStacks_OCE("SScin_Pa234m", ScaleFactor_SScin_Pa234m, FillColor_SScin_Pa234m, ExtStackColl_OCE, infile_OCE);

  // 19) MuMetal_g1000
  Double_t ScaleFactor_MuMetal_g1000_P1 = Act_MuMetal_g1000_P1*AccptRunTime/Denom_MuMetal_g1000;
  addChannelToStacks_OCE("MuMetal_g1000_P1", ScaleFactor_MuMetal_g1000_P1, FillColor_MuMetal_g1000, ExtStackColl_OCE, infile_OCE);
  Double_t ScaleFactor_MuMetal_g1000_P2 = Act_MuMetal_g1000_P2*AccptRunTime/Denom_MuMetal_g1000;
  addChannelToStacks_OCE("MuMetal_g1000_P2", ScaleFactor_MuMetal_g1000_P2, FillColor_MuMetal_g1000, ExtStackColl_OCE, infile_OCE);

  // 20) Neutrons
  Double_t ScaleFactor_Neutrons_P1 = Act_Neutrons_P1*AccptRunTime/Denom_Neutrons;
  addChannelToStacks_OCE("Data_Neutrons_P1", ScaleFactor_Neutrons_P1, FillColor_Neutrons, ExtStackColl_OCE, infile_OCE);
  Double_t ScaleFactor_Neutrons_P2 = Act_Neutrons_P2*AccptRunTime/Denom_Neutrons;
  addChannelToStacks_OCE("Data_Neutrons_P2", ScaleFactor_Neutrons_P2, FillColor_Neutrons, ExtStackColl_OCE, infile_OCE);

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

  Double_t Act_SWire_Bi210_Err      = Activities_Rad_Err[8];
  Double_t Act_SScin_Bi210_Err      = Activities_Rad_Err[12];
  Double_t Act_SScin_Bi214_P1_Err   = Activities_Rad_Err[13];
  Double_t Act_SScin_Bi214_P2_Err   = Activities_Rad_Err[14];
  Double_t Act_Air_Bi214_P1_Err     = Activities_Rad_Err[15];
  Double_t Act_Air_Tl208_P1_Err     = Activities_Rad_Err[16];
  Double_t Act_Air_Bi214_P2_Err     = 0;
  Double_t Act_Air_Tl208_P2_Err     = 0;

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
  Int_t    FillColor_Air_Bi214   = kGreen+2;
  Int_t    FillColor_Air_Pb214   = kGreen+3;
  Int_t    FillColor_Air_Tl208   = kGreen+4;

  // Create collection of histogram stacks
  RadStackColl_OCE[0] = new THStack("h_OCE_P1_Inner","Electron Energy");
  RadStackColl_OCE[1] = new THStack("h_OCE_P1_Outer","Electron Energy");
  RadStackColl_OCE[2] = new THStack("h_OCE_P1_Petal","Electron Energy");
  RadStackColl_OCE[3] = new THStack("h_OCE_P2_Inner","Electron Energy");
  RadStackColl_OCE[4] = new THStack("h_OCE_P2_Outer","Electron Energy");
  RadStackColl_OCE[5] = new THStack("h_OCE_P2_Petal","Electron Energy");

  //  Add Radon Backgrounds

  // 0) SWire_Bi214
  Double_t Scale_SWire_Bi214_P1 = Act_SWire_Bi214_P1*AccptRunTime/Denom_SWire_Bi214;
  addChannelToStacks_OCE("SWire_Bi214_P1", Scale_SWire_Bi214_P1, FillColor_SWire_Bi214, RadStackColl_OCE, infile_OCE);
  Double_t Scale_SWire_Bi214_P2 = Act_SWire_Bi214_P2*AccptRunTime/Denom_SWire_Bi214;
  addChannelToStacks_OCE("SWire_Bi214_P2", Scale_SWire_Bi214_P2, FillColor_SWire_Bi214, RadStackColl_OCE, infile_OCE);

  // 1) SWire_Pb214
  Double_t Scale_SWire_Pb214_P1 = Act_SWire_Pb214_P1*AccptRunTime/Denom_SWire_Pb214;
  addChannelToStacks_OCE("SWire_Pb214_P1", Scale_SWire_Pb214_P1, FillColor_SWire_Pb214, RadStackColl_OCE, infile_OCE);
  Double_t Scale_SWire_Pb214_P2 = Act_SWire_Pb214_P2*AccptRunTime/Denom_SWire_Pb214;
  addChannelToStacks_OCE("SWire_Pb214_P2", Scale_SWire_Pb214_P2, FillColor_SWire_Pb214, RadStackColl_OCE, infile_OCE);

  // 2) SWire_Bi210 
  Double_t Scale_SWire_Bi210 = Act_SWire_Bi210*AccptRunTime/Denom_SWire_Bi210;
  addChannelToStacks_OCE("SWire_Bi210_P1", Scale_SWire_Bi210, FillColor_SWire_Bi210, RadStackColl_OCE, infile_OCE);
  addChannelToStacks_OCE("SWire_Bi210_P2", Scale_SWire_Bi210, FillColor_SWire_Bi210, RadStackColl_OCE, infile_OCE);

  // 3) SWire_Tl208 
  Double_t Scale_SWire_Tl208_P1 = Act_SWire_Tl208_P1*AccptRunTime/Denom_SWire_Tl208;
  addChannelToStacks_OCE("SWire_Tl208_P1", Scale_SWire_Tl208_P1, FillColor_SWire_Tl208, RadStackColl_OCE, infile_OCE);
  Double_t Scale_SWire_Tl208_P2 = Act_SWire_Tl208_P2*AccptRunTime/Denom_SWire_Tl208;
  addChannelToStacks_OCE("SWire_Tl208_P2", Scale_SWire_Tl208_P2, FillColor_SWire_Tl208, RadStackColl_OCE, infile_OCE);

  // 4) SFoil_Bi214_In
  Double_t ScaleFactor_SFoil_Bi214_In_P1 = Act_SFoil_Bi214_In_P1*AccptRunTime/Denom_SFoil_Bi214;
  addChannelToStacks_OCE("SFoil_Bi214_In_P1", ScaleFactor_SFoil_Bi214_In_P1, FillColor_SFoil_Bi214, RadStackColl_OCE, infile_OCE);
  Double_t ScaleFactor_SFoil_Bi214_In_P2 = Act_SFoil_Bi214_In_P2*AccptRunTime/Denom_SFoil_Bi214;
  addChannelToStacks_OCE("SFoil_Bi214_In_P2", ScaleFactor_SFoil_Bi214_In_P2, FillColor_SFoil_Bi214, RadStackColl_OCE, infile_OCE);

  // 5) SFoil_Bi214_Out
  Double_t ScaleFactor_SFoil_Bi214_Out_P1 = Act_SFoil_Bi214_Out_P1*AccptRunTime/Denom_SFoil_Bi214;
  addChannelToStacks_OCE("SFoil_Bi214_Out_P1", ScaleFactor_SFoil_Bi214_Out_P1, FillColor_SFoil_Bi214, RadStackColl_OCE, infile_OCE);
  Double_t ScaleFactor_SFoil_Bi214_Out_P2 = Act_SFoil_Bi214_Out_P2*AccptRunTime/Denom_SFoil_Bi214;
  addChannelToStacks_OCE("SFoil_Bi214_Out_P2", ScaleFactor_SFoil_Bi214_Out_P2, FillColor_SFoil_Bi214, RadStackColl_OCE, infile_OCE);

  // 6) SFoil_Pb214_In
  Double_t ScaleFactor_SFoil_Pb214_In_P1 = Act_SFoil_Pb214_In_P1*AccptRunTime/Denom_SFoil_Pb214;
  addChannelToStacks_OCE("SFoil_Pb214_In_P1", ScaleFactor_SFoil_Pb214_In_P1, FillColor_SFoil_Pb214, RadStackColl_OCE, infile_OCE);
  Double_t ScaleFactor_SFoil_Pb214_In_P2 = Act_SFoil_Pb214_In_P2*AccptRunTime/Denom_SFoil_Pb214;
  addChannelToStacks_OCE("SFoil_Pb214_In_P2", ScaleFactor_SFoil_Pb214_In_P2, FillColor_SFoil_Pb214, RadStackColl_OCE, infile_OCE);

  // 7) SFoil_Pb214_Out
  Double_t ScaleFactor_SFoil_Pb214_Out_P1 = Act_SFoil_Pb214_Out_P1*AccptRunTime/Denom_SFoil_Pb214;
  addChannelToStacks_OCE("SFoil_Pb214_Out_P1", ScaleFactor_SFoil_Pb214_Out_P1, FillColor_SFoil_Pb214, RadStackColl_OCE, infile_OCE);
  Double_t ScaleFactor_SFoil_Pb214_Out_P2 = Act_SFoil_Pb214_Out_P2*AccptRunTime/Denom_SFoil_Pb214;
  addChannelToStacks_OCE("SFoil_Pb214_Out_P2", ScaleFactor_SFoil_Pb214_Out_P2, FillColor_SFoil_Pb214, RadStackColl_OCE, infile_OCE);

  // 8) SFoil_SeNew_Bi210 
  Double_t ScaleFactor_SFoil_SeNew_Bi210 = Act_SFoil_SeNew_Bi210*AccptRunTime/Denom_SFoil_Bi210;
  addChannelToStacks_OCE("SFoil_SeNew_Bi210_P1", ScaleFactor_SFoil_SeNew_Bi210, FillColor_SFoil_Bi210, RadStackColl_OCE, infile_OCE);
  addChannelToStacks_OCE("SFoil_SeNew_Bi210_P2", ScaleFactor_SFoil_SeNew_Bi210, FillColor_SFoil_Bi210, RadStackColl_OCE, infile_OCE);

  // 9) SFoil_SeOld_Bi210 
  Double_t ScaleFactor_SFoil_SeOld_Bi210 = Act_SFoil_SeOld_Bi210*AccptRunTime/Denom_SFoil_Bi210;
  addChannelToStacks_OCE("SFoil_SeOld_Bi210_P1", ScaleFactor_SFoil_SeOld_Bi210, FillColor_SFoil_Bi210, RadStackColl_OCE, infile_OCE);
  addChannelToStacks_OCE("SFoil_SeOld_Bi210_P2", ScaleFactor_SFoil_SeOld_Bi210, FillColor_SFoil_Bi210, RadStackColl_OCE, infile_OCE);

  // 10) SFoil_Strip_Bi210 (in SeNew Dirty strip)
  Double_t ScaleFactor_SFoil_Strip_Bi210 = Act_SFoil_Strip_Bi210*AccptRunTime/Denom_SFoil_Bi210;
  addChannelToStacks_OCE("SFoil_Strip_Bi210_P1", ScaleFactor_SFoil_Strip_Bi210, FillColor_SFoil_Bi210, RadStackColl_OCE, infile_OCE);
  addChannelToStacks_OCE("SFoil_Strip_Bi210_P2", ScaleFactor_SFoil_Strip_Bi210, FillColor_SFoil_Bi210, RadStackColl_OCE, infile_OCE);

  // 11) SScin_Bi214
  Double_t ScaleFactor_SScin_Bi214_P1 = Act_SScin_Bi214_P1*AccptRunTime/Denom_SScin_Bi214;
  addChannelToStacks_OCE("SScin_Bi214_P1", ScaleFactor_SScin_Bi214_P1, FillColor_SScin_Bi214, RadStackColl_OCE, infile_OCE);
  Double_t ScaleFactor_SScin_Bi214_P2 = Act_SScin_Bi214_P2*AccptRunTime/Denom_SScin_Bi214;
  addChannelToStacks_OCE("SScin_Bi214_P2", ScaleFactor_SScin_Bi214_P2, FillColor_SScin_Bi214, RadStackColl_OCE, infile_OCE);

  // 12) SScin_Pb214
  Double_t ScaleFactor_SScin_Pb214_P1 = Act_SScin_Pb214_P1*AccptRunTime/Denom_SScin_Pb214;
  addChannelToStacks_OCE("SScin_Pb214_P1", ScaleFactor_SScin_Pb214_P1, FillColor_SScin_Pb214, RadStackColl_OCE, infile_OCE);
  Double_t ScaleFactor_SScin_Pb214_P2 = Act_SScin_Pb214_P2*AccptRunTime/Denom_SScin_Pb214;
  addChannelToStacks_OCE("SScin_Pb214_P2", ScaleFactor_SScin_Pb214_P2, FillColor_SScin_Pb214, RadStackColl_OCE, infile_OCE);

  // 13) SScin_Bi210
  Double_t ScaleFactor_SScin_Bi210 = Act_SScin_Bi210*AccptRunTime/Denom_SScin_Bi210;
  addChannelToStacks_OCE("SScin_Bi210_P1", ScaleFactor_SScin_Bi210, FillColor_SScin_Bi210, RadStackColl_OCE, infile_OCE);
  addChannelToStacks_OCE("SScin_Bi210_P2", ScaleFactor_SScin_Bi210, FillColor_SScin_Bi210, RadStackColl_OCE, infile_OCE);

  // 14) Air_Bi214
  Double_t ScaleFactor_Air_Bi214_P1 = Act_Air_Bi214_P1*AccptRunTime/Denom_Air_Bi214;
  addChannelToStacks_OCE("Air_Bi214_P1", ScaleFactor_Air_Bi214_P1, FillColor_Air_Bi214, RadStackColl_OCE, infile_OCE);
  Double_t ScaleFactor_Air_Bi214_P2 = Act_Air_Bi214_P2*AccptRunTime/Denom_Air_Bi214;
  addChannelToStacks_OCE("Air_Bi214_P2", ScaleFactor_Air_Bi214_P2, FillColor_Air_Bi214, RadStackColl_OCE, infile_OCE);

  // 15) Air_Pb214
  Double_t ScaleFactor_Air_Pb214_P1 = Act_Air_Pb214_P1*AccptRunTime/Denom_Air_Pb214;
  addChannelToStacks_OCE("Air_Pb214_P1", ScaleFactor_Air_Pb214_P1, FillColor_Air_Pb214, RadStackColl_OCE, infile_OCE);
  Double_t ScaleFactor_Air_Pb214_P2 = Act_Air_Pb214_P2*AccptRunTime/Denom_Air_Pb214;
  addChannelToStacks_OCE("Air_Pb214_P2", ScaleFactor_Air_Pb214_P2, FillColor_Air_Pb214, RadStackColl_OCE, infile_OCE);

  // 16) Air_Tl208
  Double_t ScaleFactor_Air_Tl208_P1 = Act_Air_Tl208_P1*AccptRunTime/Denom_Air_Tl208;
  addChannelToStacks_OCE("Air_Tl208_P1", ScaleFactor_Air_Tl208_P1, FillColor_Air_Tl208, RadStackColl_OCE, infile_OCE);
  Double_t ScaleFactor_Air_Tl208_P2 = Act_Air_Tl208_P2*AccptRunTime/Denom_Air_Tl208;
  addChannelToStacks_OCE("Air_Tl208_P2", ScaleFactor_Air_Tl208_P2, FillColor_Air_Tl208, RadStackColl_OCE, infile_OCE);


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
  IntStackColl_OCE[0] = new THStack("h_OCE_P1_Inner","Electron Energy");
  IntStackColl_OCE[1] = new THStack("h_OCE_P1_Outer","Electron Energy");
  IntStackColl_OCE[2] = new THStack("h_OCE_P1_Petal","Electron Energy");
  IntStackColl_OCE[3] = new THStack("h_OCE_P2_Inner","Electron Energy");
  IntStackColl_OCE[4] = new THStack("h_OCE_P2_Outer","Electron Energy");
  IntStackColl_OCE[5] = new THStack("h_OCE_P2_Petal","Electron Energy");

  // Add Internal Backgrounds

  // 0) SeNew_Bi214
  Double_t ScaleFactor_SeNew_Bi214 = Act_SeNew_Bi214*AccptRunTime/Denom_SeNew_Bi214;
  addChannelToStacks_OCE("SeNew_Bi214", ScaleFactor_SeNew_Bi214, FillColor_SeNew_Bi214, IntStackColl_OCE, infile_OCE);

  // 1) SeOld_Bi214
  Double_t ScaleFactor_SeOld_Bi214 = Act_SeOld_Bi214*AccptRunTime/Denom_SeOld_Bi214;
  addChannelToStacks_OCE("SeOld_Bi214", ScaleFactor_SeOld_Bi214, FillColor_SeOld_Bi214, IntStackColl_OCE, infile_OCE);

  // 2) Mylar_Bi214
  Double_t ScaleFactor_Mylar_Bi214 = Act_Mylar_Bi214*AccptRunTime/Denom_Mylar_Bi214;
  addChannelToStacks_OCE("Mylar_Bi214", ScaleFactor_Mylar_Bi214, FillColor_Mylar_Bi214, IntStackColl_OCE, infile_OCE);

  // 3) SeNew_Pb214
  Double_t ScaleFactor_SeNew_Pb214 = Act_SeNew_Pb214*AccptRunTime/Denom_SeNew_Pb214;
  addChannelToStacks_OCE("SeNew_Pb214", ScaleFactor_SeNew_Pb214, FillColor_SeNew_Pb214, IntStackColl_OCE, infile_OCE);

  // 4) SeOld_Pb214
  Double_t ScaleFactor_SeOld_Pb214 = Act_SeOld_Pb214*AccptRunTime/Denom_SeOld_Pb214;
  addChannelToStacks_OCE("SeOld_Pb214", ScaleFactor_SeOld_Pb214, FillColor_SeOld_Pb214, IntStackColl_OCE, infile_OCE);

  // 5) Mylar_Pb214
  Double_t ScaleFactor_Mylar_Pb214 = Act_Mylar_Pb214*AccptRunTime/Denom_Mylar_Pb214;
  addChannelToStacks_OCE("Mylar_Pb214", ScaleFactor_Mylar_Pb214, FillColor_Mylar_Pb214, IntStackColl_OCE, infile_OCE);

  // 6) SeNew_Tl208
  Double_t ScaleFactor_SeNew_Tl208 = Act_SeNew_Tl208*AccptRunTime/Denom_SeNew_Tl208;
  addChannelToStacks_OCE("SeNew_Tl208", ScaleFactor_SeNew_Tl208, FillColor_SeNew_Tl208, IntStackColl_OCE, infile_OCE);

  // 7) SeOld_Tl208
  Double_t ScaleFactor_SeOld_Tl208 = Act_SeOld_Tl208*AccptRunTime/Denom_SeOld_Tl208;
  addChannelToStacks_OCE("SeOld_Tl208", ScaleFactor_SeOld_Tl208, FillColor_SeOld_Tl208, IntStackColl_OCE, infile_OCE);

  // 8) SeNew_Bi212
  Double_t ScaleFactor_SeNew_Bi212 = Act_SeNew_Bi212*AccptRunTime/Denom_SeNew_Bi212;
  addChannelToStacks_OCE("SeNew_Bi212", ScaleFactor_SeNew_Bi212, FillColor_SeNew_Bi212, IntStackColl_OCE, infile_OCE);

  // 9) SeOld_Bi212
  Double_t ScaleFactor_SeOld_Bi212 = Act_SeOld_Bi212*AccptRunTime/Denom_SeOld_Bi212;
  addChannelToStacks_OCE("SeOld_Bi212", ScaleFactor_SeOld_Bi212, FillColor_SeOld_Bi212, IntStackColl_OCE, infile_OCE);

  // 10) SeNew_Ac228
  Double_t ScaleFactor_SeNew_Ac228 = Act_SeNew_Ac228*AccptRunTime/Denom_SeNew_Ac228;
  addChannelToStacks_OCE("SeNew_Ac228", ScaleFactor_SeNew_Ac228, FillColor_SeNew_Ac228, IntStackColl_OCE, infile_OCE);

  // 11) SeOld_Ac228
  Double_t ScaleFactor_SeOld_Ac228 = Act_SeOld_Ac228*AccptRunTime/Denom_SeOld_Ac228;
  addChannelToStacks_OCE("SeOld_Ac228", ScaleFactor_SeOld_Ac228, FillColor_SeOld_Ac228, IntStackColl_OCE, infile_OCE);

  // 12) SeNew_Pa234m
  Double_t ScaleFactor_SeNew_Pa234m = Act_SeNew_Pa234m*AccptRunTime/Denom_SeNew_Pa234m;
  addChannelToStacks_OCE("SeNew_Pa234m", ScaleFactor_SeNew_Pa234m, FillColor_SeNew_Pa234m, IntStackColl_OCE, infile_OCE);

  // 13) SeOld_Pa234m
  Double_t ScaleFactor_SeOld_Pa234m = Act_SeOld_Pa234m*AccptRunTime/Denom_SeOld_Pa234m;
  addChannelToStacks_OCE("SeOld_Pa234m", ScaleFactor_SeOld_Pa234m, FillColor_SeOld_Pa234m, IntStackColl_OCE, infile_OCE);

  // 14) SeNew_K40
  Double_t ScaleFactor_SeNew_K40 = Act_SeNew_K40*AccptRunTime/Denom_SeNew_K40;
  addChannelToStacks_OCE("SeNew_K40", ScaleFactor_SeNew_K40, FillColor_SeNew_K40, IntStackColl_OCE, infile_OCE);

  // 15) SeOld_K40
  Double_t ScaleFactor_SeOld_K40 = Act_SeOld_K40*AccptRunTime/Denom_SeOld_K40;
  addChannelToStacks_OCE("SeOld_K40", ScaleFactor_SeOld_K40, FillColor_SeOld_K40, IntStackColl_OCE, infile_OCE);


  // ADD SIGNAL
  Double_t Act_2b2n_SeNew   = Activities_Sig[0];
  Double_t Act_2b2n_SeOld   = Activities_Sig[0];
  Double_t Denom_2b2n_SeNew = Denominators_Sig[0];
  Double_t Denom_2b2n_SeOld = Denominators_Sig[0];
  Int_t    FillColor_2b2n = kRed;

  // Create collection of histogram stacks
  SigStackColl_OCE[0] = new THStack("h_OCE_P1_SeOld","Electron Energy");
  SigStackColl_OCE[1] = new THStack("h_OCE_P1_SeNew","Electron Energy");
  SigStackColl_OCE[2] = new THStack("h_OCE_P1_Strip","Electron Energy");
  SigStackColl_OCE[3] = new THStack("h_OCE_P2_SeOld","Electron Energy");
  SigStackColl_OCE[4] = new THStack("h_OCE_P2_SeNew","Electron Energy");
  SigStackColl_OCE[5] = new THStack("h_OCE_P2_Strip","Electron Energy");

  // 0) 2b2n - SeNew
  Double_t ScaleFactor_2b2n_SeNew = Act_2b2n_SeNew*AccptRunTime/Denom_2b2n_SeNew;
  addChannelToStacks_OCE("2b2n_SeNew", ScaleFactor_2b2n_SeNew, FillColor_2b2n, SigStackColl_OCE, infile_OCE);

  // 1) 2b2n - SeOld
  Double_t ScaleFactor_2b2n_SeOld = Act_2b2n_SeOld*AccptRunTime/Denom_2b2n_SeOld;
  addChannelToStacks_OCE("2b2n_SeOld", ScaleFactor_2b2n_SeOld, FillColor_2b2n, SigStackColl_OCE, infile_OCE);

  // External Backgrounds
  // 0) PMT_K40
  // 1) PMT_Bi214
  // 2) PMT_Tl208
  // 3) PMT_Ac228
  // 4) FeShield_Bi214
  // 5) FeShield_Tl208
  // 6) FeShield_Ac228
  // 7) MuMetal_Co60
  // 8) SteelFrame_K40
  // 9) SteelFrame_Bi214
  // 10) SteelFrame_Tl208
  // 11) SteelFrame_Ac228
  // 12) SteelFrame_Co60
  // 13) CuPetals_Co60
  // 14) CuTower_Co60
  // 15) ScintInn_K40
  // 16) ScintOut_K40
  // 17) ScintPet_K40
  // 18) SScin_Pa234m
  // 19) MuMetal_g1000
  // 20) Neutrons

  // RADON BACKGROUNDS
  // 0) SWire_Bi214
  // 1) SWire_Pb214
  // 2) SWire_Bi210 
  // 3) SWire_Tl208 
  // 4) SFoil_Bi214_In
  // 5) SFoil_Bi214_Out
  // 6) SFoil_Pb214_In
  // 7) SFoil_Pb214_Out
  // 8) SFoil_SeNew_Bi210 
  // 9) SFoil_SeOld_Bi210 
  // 10) SFoil_Strip_Bi210 (in SeNew Dirty strip)
  // 11) SScin_Bi214
  // 12) SScin_Pb214
  // 13) SScin_Bi210
  // 14) Air_Bi214
  // 15) Air_Pb214

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
  StackColl_OCE[0] = new THStack("h_OCE_P1_Inner","Electron Energy");
  StackColl_OCE[1] = new THStack("h_OCE_P1_Outer","Electron Energy");
  StackColl_OCE[2] = new THStack("h_OCE_P1_Petal","Electron Energy");
  StackColl_OCE[3] = new THStack("h_OCE_P2_Inner","Electron Energy");
  StackColl_OCE[4] = new THStack("h_OCE_P2_Outer","Electron Energy");
  StackColl_OCE[5] = new THStack("h_OCE_P2_Petal","Electron Energy");

  // 0) Start by adding small contributors
  for(int j = 0; j < 6; j++){

    // 1e1a Backgrounds
    TH1D* h1 = (TH1D*)RadStackColl_OCE[j]->GetStack()->At(1)->Clone("hSWire");
    TH1D* hSFoil_1e1a = (TH1D*)RadStackColl_OCE[j]->GetStack()->At(7)->Clone("hSFoil");
    hSFoil_1e1a->Add((TH1D*)RadStackColl_OCE[j]->GetStack()->At(3), -1);
    TH1D* hInternals_1e1a = (TH1D*)IntStackColl_OCE[j]->GetStack()->At(5)->Clone("hInternals");
    h1->Add(hInternals_1e1a);
    h1->Add(hSFoil_1e1a);

    // 1e2g samples
    TH1D* hSWire_1e2g = (TH1D*)RadStackColl_OCE[j]->GetStack()->At(3)->Clone("hSWire");
    hSWire_1e2g->Add((TH1D*)RadStackColl_OCE[j]->GetStack()->At(2), -1);
    TH1D* hInternals_1e2g = (TH1D*)IntStackColl_OCE[j]->GetStack()->At(11)->Clone("hInternals");
    hInternals_1e2g->Add((TH1D*)IntStackColl_OCE[j]->GetStack()->At(5), -1);
    h1->Add(hSWire_1e2g);
    h1->Add(hInternals_1e2g);

    // Bi210 SFoil SeNew
    TH1D* hSFoil_SeNew = (TH1D*)RadStackColl_OCE[j]->GetStack()->At(8)->Clone("hSFoil");
    hSFoil_SeNew->Add((TH1D*)RadStackColl_OCE[j]->GetStack()->At(7), -1);
    h1->Add(hSFoil_SeNew);

    // Bi210 SFoil SeOld
    TH1D* hSFoil_SeOld = (TH1D*)RadStackColl_OCE[j]->GetStack()->At(9)->Clone("hSFoil");
    hSFoil_SeOld->Add((TH1D*)RadStackColl_OCE[j]->GetStack()->At(8), -1);
    h1->Add(hSFoil_SeOld);

    // Bi210 SFoil Strip
    TH1D* hSFoil_Strip = (TH1D*)RadStackColl_OCE[j]->GetStack()->At(10)->Clone("hSFoil");
    hSFoil_Strip->Add((TH1D*)RadStackColl_OCE[j]->GetStack()->At(9), -1);
    h1->Add(hSFoil_Strip);

    // Pa234m - SeNew
    TH1D* hPa234m_SeNew = (TH1D*)IntStackColl_OCE[j]->GetStack()->At(12)->Clone("hPa234m");
    hPa234m_SeNew->Add((TH1D*)IntStackColl_OCE[j]->GetStack()->At(11), -1);
    h1->Add(hPa234m_SeNew);

    // Pa234m - SeOld
    TH1D* hPa234m_SeOld = (TH1D*)IntStackColl_OCE[j]->GetStack()->At(13)->Clone("hPa234m");
    hPa234m_SeOld->Add((TH1D*)IntStackColl_OCE[j]->GetStack()->At(12), -1);
    h1->Add(hPa234m_SeOld);

    // K40 - SeNew
    TH1D* hK40_SeNew = (TH1D*)IntStackColl_OCE[j]->GetStack()->At(14)->Clone("hK40");
    hK40_SeNew->Add((TH1D*)IntStackColl_OCE[j]->GetStack()->At(13), -1);
    h1->Add(hK40_SeNew);

    // K40 - SeOld
    TH1D* hK40_SeOld = (TH1D*)IntStackColl_OCE[j]->GetStack()->At(15)->Clone("hK40");
    hK40_SeOld->Add((TH1D*)IntStackColl_OCE[j]->GetStack()->At(14), -1);
    h1->Add(hK40_SeOld);

    // 2b2n
    TH1D* h2b2n = (TH1D*)SigStackColl_OCE[j]->GetStack()->Last()->Clone("h2b2n");
    h1->Add(h2b2n);

    h1->SetFillColor(kGray);
    StackColl_OCE[j]->Add(h1);

  }

  // 1) K40 PMT
  for(int j = 0; j < 6; j++){
    TH1D* hK40 = (TH1D*)ExtStackColl_OCE[j]->GetStack()->At(0)->Clone("hK40");
    hK40->SetFillColor(kSpring-6);
    StackColl_OCE[j]->Add(hK40);
  }

  // 2) K40 Steel Frame
  for(int j = 0; j < 6; j++){
    TH1D* hK40 = (TH1D*)ExtStackColl_OCE[j]->GetStack()->At(8)->Clone("hK40");
    hK40->Add((TH1D*)ExtStackColl_OCE[j]->GetStack()->At(7),-1);
    hK40->SetFillColor(kSpring-1);
    StackColl_OCE[j]->Add(hK40);
  }

  // 3) K40 Scint Inner
  for(int j = 0; j < 6; j++){
    TH1D* hK40 = (TH1D*)ExtStackColl_OCE[j]->GetStack()->At(15)->Clone("hK40");
    hK40->Add((TH1D*)ExtStackColl_OCE[j]->GetStack()->At(14),-1);
    hK40->SetFillColor(kSpring-3);
    StackColl_OCE[j]->Add(hK40);
  }

  // 4) K40 Scint Outer
  for(int j = 0; j < 6; j++){
    TH1D* hK40 = (TH1D*)ExtStackColl_OCE[j]->GetStack()->At(16)->Clone("hK40");
    hK40->Add((TH1D*)ExtStackColl_OCE[j]->GetStack()->At(15),-1);
    hK40->SetFillColor(kSpring-3);
    StackColl_OCE[j]->Add(hK40);
  }

  // 5) K40 Scint Petals
  for(int j = 0; j < 6; j++){
    TH1D* hK40 = (TH1D*)ExtStackColl_OCE[j]->GetStack()->At(17)->Clone("hK40");
    hK40->Add((TH1D*)ExtStackColl_OCE[j]->GetStack()->At(16),-1);
    hK40->SetFillColor(kSpring-3);
    StackColl_OCE[j]->Add(hK40);
  }

  // 6) Bi214 PMT
  for(int j = 0; j < 6; j++){
    TH1D* hBi214 = (TH1D*)ExtStackColl_OCE[j]->GetStack()->At(1)->Clone("hBi214");
    hBi214->Add((TH1D*)ExtStackColl_OCE[j]->GetStack()->At(0),-1);
    hBi214->SetFillColor(kRed);
    StackColl_OCE[j]->Add(hBi214);
  }

  // 7) Bi214 FeShield
  for(int j = 0; j < 6; j++){
    TH1D* hBi214 = (TH1D*)ExtStackColl_OCE[j]->GetStack()->At(4)->Clone("hBi214");
    hBi214->Add((TH1D*)ExtStackColl_OCE[j]->GetStack()->At(3),-1);
    hBi214->SetFillColor(kRed-4);
    StackColl_OCE[j]->Add(hBi214);
  }

  // 8) Bi214 SteelFrame
  for(int j = 0; j < 6; j++){
    TH1D* hBi214 = (TH1D*)ExtStackColl_OCE[j]->GetStack()->At(9)->Clone("hBi214");
    hBi214->Add((TH1D*)ExtStackColl_OCE[j]->GetStack()->At(8),-1);
    hBi214->SetFillColor(kRed+1);
    StackColl_OCE[j]->Add(hBi214);
  }

  // 9) Bi214 SScin
  for(int j = 0; j < 6; j++){
    TH1D* hSScin = (TH1D*)RadStackColl_OCE[j]->GetStack()->At(12)->Clone("hSScin");
    hSScin->Add((TH1D*)RadStackColl_OCE[j]->GetStack()->At(10), -1);
    hSScin->SetFillColor(kRed+2);
    StackColl_OCE[j]->Add(hSScin);
  }

  // 10)  Bi214 LSM Air
  for(int j = 0; j < 6; j++){
    TH1D* hAir = (TH1D*)RadStackColl_OCE[j]->GetStack()->At(15)->Clone("hAir");
    hAir->Add((TH1D*)RadStackColl_OCE[j]->GetStack()->At(13), -1);
    hAir->SetFillColor(kPink-1);
    StackColl_OCE[j]->Add(hAir);
  }

  // 11) Tl208 & Ac228 PMT
  for(int j = 0; j < 6; j++){
    TH1D* hTl208 = (TH1D*)ExtStackColl_OCE[j]->GetStack()->At(3)->Clone("hTl208");
    hTl208->Add((TH1D*)ExtStackColl_OCE[j]->GetStack()->At(1),-1);
    hTl208->SetFillColor(kAzure);
    StackColl_OCE[j]->Add(hTl208);
  }

  // 12) Tl208 & Ac228 FeShield
  for(int j = 0; j < 6; j++){
    TH1D* hTl208 = (TH1D*)ExtStackColl_OCE[j]->GetStack()->At(6)->Clone("hTl208");
    hTl208->Add((TH1D*)ExtStackColl_OCE[j]->GetStack()->At(4),-1);
    hTl208->SetFillColor(kAzure+1);
    StackColl_OCE[j]->Add(hTl208);
  }

  // 13) Tl208 & Ac228 SteelFrame
  for(int j = 0; j < 6; j++){
    TH1D* hTl208 = (TH1D*)ExtStackColl_OCE[j]->GetStack()->At(11)->Clone("hTl208");
    hTl208->Add((TH1D*)ExtStackColl_OCE[j]->GetStack()->At(9),-1);
    hTl208->SetFillColor(kAzure+2);
    StackColl_OCE[j]->Add(hTl208);
  }

  // 14) Tl208 LSM Air
  for(int j = 0; j < 6; j++){
    TH1D* hTl208 = (TH1D*)RadStackColl_OCE[j]->GetStack()->At(16)->Clone("hTl208");
    hTl208->Add((TH1D*)RadStackColl_OCE[j]->GetStack()->At(15),-1);
    hTl208->SetFillColor(kAzure+3);
    StackColl_OCE[j]->Add(hTl208);
  }

  // 15) Co60 MuMetal
  for(int j = 0; j < 6; j++){
    TH1D* hCo60 = (TH1D*)ExtStackColl_OCE[j]->GetStack()->At(7)->Clone("hCo60");
    hCo60->Add((TH1D*)ExtStackColl_OCE[j]->GetStack()->At(6),-1);
    hCo60->SetFillColor(kTeal+9);
    StackColl_OCE[j]->Add(hCo60);
  }

  // 16) Co60 SteelFrame
  for(int j = 0; j < 6; j++){
    TH1D* hCo60 = (TH1D*)ExtStackColl_OCE[j]->GetStack()->At(12)->Clone("hCo60");
    hCo60->Add((TH1D*)ExtStackColl_OCE[j]->GetStack()->At(11),-1);
    hCo60->SetFillColor(kTeal+5);
    StackColl_OCE[j]->Add(hCo60);
  }

  // 17) Co60 CuPetals
  for(int j = 0; j < 6; j++){
    TH1D* hCo60 = (TH1D*)ExtStackColl_OCE[j]->GetStack()->At(13)->Clone("hCo60");
    hCo60->Add((TH1D*)ExtStackColl_OCE[j]->GetStack()->At(12),-1);
    hCo60->SetFillColor(kTeal-1);
    StackColl_OCE[j]->Add(hCo60);
  }

  // 18) Co60 CuTower
  for(int j = 0; j < 6; j++){
    TH1D* hCo60 = (TH1D*)ExtStackColl_OCE[j]->GetStack()->At(14)->Clone("hCo60");
    hCo60->Add((TH1D*)ExtStackColl_OCE[j]->GetStack()->At(13),-1);
    hCo60->SetFillColor(kTeal);
    StackColl_OCE[j]->Add(hCo60);
  }

  // 19) Bi210 SScin
  for(int j = 0; j < 6; j++){
    TH1D* hSScin = (TH1D*)RadStackColl_OCE[j]->GetStack()->At(13)->Clone("hSScin");
    hSScin->Add((TH1D*)RadStackColl_OCE[j]->GetStack()->At(12), -1);
    hSScin->SetFillColor(kOrange-1);
    StackColl_OCE[j]->Add(hSScin);
  }

  // 20) SWire-B210
  for(int j = 0; j < 6; j++){
    TH1D* hSWire = (TH1D*)RadStackColl_OCE[j]->GetStack()->At(2)->Clone("hSWire");
    hSWire->Add((TH1D*)RadStackColl_OCE[j]->GetStack()->At(1), -1);
    hSWire->SetFillColor(kOrange);
    StackColl_OCE[j]->Add(hSWire);
  }

  // 21) SScin-Pa234m
  for(int j = 0; j < 6; j++){
    TH1D* hSScin = (TH1D*)ExtStackColl_OCE[j]->GetStack()->At(18)->Clone("hSScin");
    hSScin->Add((TH1D*)ExtStackColl_OCE[j]->GetStack()->At(17), -1);
    hSScin->SetFillColor(kYellow);
    StackColl_OCE[j]->Add(hSScin);
  }

  // 22) MuMetal-g1000
  for(int j = 0; j < 6; j++){
    TH1D* hGFlux = (TH1D*)ExtStackColl_OCE[j]->GetStack()->At(19)->Clone("hGFlux");
    hGFlux->Add((TH1D*)ExtStackColl_OCE[j]->GetStack()->At(18), -1);
    hGFlux->SetFillColor(kYellow-2);
    StackColl_OCE[j]->Add(hGFlux);
  }

  // 23) Neutrons
  for(int j = 0; j < 6; j++){
    TH1D* hNeutrons = (TH1D*)ExtStackColl_OCE[j]->GetStack()->At(20)->Clone("hNeutrons");
    hNeutrons->Add((TH1D*)ExtStackColl_OCE[j]->GetStack()->At(19), -1);
    hNeutrons->SetFillColor(kSpring+9);
    StackColl_OCE[j]->Add(hNeutrons);
  }

  // 0) Other MC
  // 1) K40 PMT
  // 2) K40 Steel Frame
  // 3) K40 Scint Inner
  // 4) K40 Scint Outer
  // 5) K40 Scint Petals
  // 6) Bi214 PMT
  // 7) Bi214 FeShield
  // 8) Bi214 SteelFrame
  // 9) Bi214 SScin
  // 10) Bi214 LSM Air
  // 11) Tl208 & Ac228 PMT
  // 12) Tl208 & Ac228 FeShield
  // 13) Tl208 & Ac228 SteelFrame
  // 14) Tl208 LSM Air
  // 15) Co60 MuMetal
  // 16) Co60 SteelFrame
  // 17) Co60 CuPetals
  // 18) Co60 CuTower
  // 19) Bi210 SScin
  // 20) Bi210 SWire
  // 21) Pa234m SScin
  // 22) g1000 MuMetal

  // Create legend to put on plots
  string LegIsotopes_P1[24];
  string LegEntries_P1[24];
  string LegIsotopes_P2[24];
  string LegEntries_P2[24];
  char buffer[200];

  LegIsotopes_P1[0] = "Other MC";
  sprintf (buffer, " ");
  LegEntries_P1[0] = buffer;
  LegIsotopes_P1[1] = "^{40}K PMT";
  if(Act_PMT_K40_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_PMT_K40, Act_PMT_K40_Err);}
  else{sprintf (buffer, "A = %.1f Bq", Act_PMT_K40);}
  LegEntries_P1[1] = buffer;
  LegIsotopes_P1[2] = "^{40}K Steel Frame";
  if(Act_SteelFrame_K40_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_SteelFrame_K40, Act_SteelFrame_K40_Err);}
  else{sprintf (buffer, "A = %.1f Bq", Act_SteelFrame_K40);}
  LegEntries_P1[2] = buffer;
  LegIsotopes_P1[3] = "^{40}K Scint Inner";
  if(Act_ScintInn_K40_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_ScintInn_K40, Act_ScintInn_K40_Err);}
  else{sprintf (buffer, "A = %.1f Bq", Act_ScintInn_K40);}
  LegEntries_P1[3] = buffer;
  LegIsotopes_P1[4] = "^{40}K Scint Outer";
  if(Act_ScintOut_K40_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_ScintOut_K40, Act_ScintOut_K40_Err);}
  else{sprintf (buffer, "A = %.1f Bq", Act_ScintOut_K40);}
  LegEntries_P1[4] = buffer;
  LegIsotopes_P1[5] = "^{40}K Scint Petals";
  if(Act_ScintPet_K40_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_ScintPet_K40, Act_ScintPet_K40_Err);}
  else{sprintf (buffer, "A = %.1f Bq", Act_ScintPet_K40);}
  LegEntries_P1[5] = buffer;
  LegIsotopes_P1[6] = "^{214}Bi PMT";
  if(Act_PMT_Bi214_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_PMT_Bi214, Act_PMT_Bi214_Err);}
  else{sprintf (buffer, "A = %.2f Bq", Act_PMT_Bi214);}
  LegEntries_P1[6] = buffer;
  LegIsotopes_P1[7] = "^{214}Bi Fe Shield";
  if(Act_FeShield_Bi214_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_FeShield_Bi214, Act_FeShield_Bi214_Err);}
  else{sprintf (buffer, "A = %.2f Bq", Act_FeShield_Bi214);}
  LegEntries_P1[7] = buffer;
  LegIsotopes_P1[8] = "^{214}Bi Steel Frame";
  if(Act_SteelFrame_Bi214_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_SteelFrame_Bi214, Act_SteelFrame_Bi214_Err);}
  else{sprintf (buffer, "A = %.2f Bq", Act_SteelFrame_Bi214);}
  LegEntries_P1[8] = buffer;
  LegIsotopes_P1[9] = "^{214}Bi SScin P1";
  if(Act_SScin_Bi214_P1_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_SScin_Bi214_P1, Act_SScin_Bi214_P1_Err);}
  else{sprintf (buffer, "A = %.2f Bq", Act_SScin_Bi214_P1);}
  LegEntries_P1[9] = buffer;
  LegIsotopes_P1[10] = "^{214}Bi LSM Air P1";
  if(Act_Air_Bi214_P1_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_Air_Bi214_P1, Act_Air_Bi214_P1_Err);}
  else{sprintf (buffer, "A = %.2f Bq", Act_Air_Bi214_P1);}
  LegEntries_P1[10] = buffer;
  LegIsotopes_P1[11] = "^{208}Tl PMT";
  if(Act_PMT_Tl208_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_PMT_Tl208, Act_PMT_Tl208_Err);}
  else{sprintf (buffer, "A = %.2f Bq", Act_PMT_Tl208);}
  LegEntries_P1[11] = buffer;
  LegIsotopes_P1[12] = "^{208}Tl Fe Shield";
  if(Act_FeShield_Tl208_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_FeShield_Tl208, Act_FeShield_Tl208_Err);}
  else{sprintf (buffer, "A = %.2f Bq", Act_FeShield_Tl208);}
  LegEntries_P1[12] = buffer;
  LegIsotopes_P1[13] = "^{208}Tl Steel Frame";
  if(Act_SteelFrame_Tl208_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_SteelFrame_Tl208, Act_SteelFrame_Tl208_Err);}
  else{sprintf (buffer, "A = %.2f Bq", Act_SteelFrame_Tl208);}
  LegEntries_P1[13] = buffer;
  LegIsotopes_P1[14] = "^{208}Tl LSM Air P1";
  if(Act_Air_Tl208_P1_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_Air_Tl208_P1, Act_Air_Tl208_P1_Err);}
  else{sprintf (buffer, "A = %.2f Bq", Act_Air_Tl208_P1);}
  LegEntries_P1[14] = buffer;
  LegIsotopes_P1[15] = "^{60}Co Mu Metal";
  if(Act_MuMetal_Co60_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_MuMetal_Co60, Act_MuMetal_Co60_Err);}
  else{sprintf (buffer, "A = %.2f Bq", Act_MuMetal_Co60);}
  LegEntries_P1[15] = buffer;
  LegIsotopes_P1[16] = "^{60}Co Steel Frame";
  if(Act_SteelFrame_Co60_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_SteelFrame_Co60, Act_SteelFrame_Co60_Err);}
  else{sprintf (buffer, "A = %.2f Bq", Act_SteelFrame_Co60);}
  LegEntries_P1[16] = buffer;
  LegIsotopes_P1[17] = "^{60}Co Cu Petals";
  if(Act_CuPetals_Co60_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_CuPetals_Co60, Act_CuPetals_Co60_Err);}
  else{sprintf (buffer, "A = %.2f Bq", Act_CuPetals_Co60);}
  LegEntries_P1[17] = buffer;
  LegIsotopes_P1[18] = "^{60}Co Cu Tower";
  if(Act_CuTower_Co60_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_CuTower_Co60, Act_CuTower_Co60_Err);}
  else{sprintf (buffer, "A = %.2f Bq", Act_CuTower_Co60);}
  LegEntries_P1[18] = buffer;
  LegIsotopes_P1[19] = "^{210}Bi SScin";
  if(Act_SScin_Bi210_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_SScin_Bi210, Act_SScin_Bi210_Err);}
  else{sprintf (buffer, "A = %.2f Bq", Act_SScin_Bi210);}
  LegEntries_P1[19] = buffer;
  LegIsotopes_P1[20] = "^{210}Bi SWire";
  if(Act_SWire_Bi210_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_SWire_Bi210, Act_SWire_Bi210_Err);}
  else{sprintf (buffer, "A = %.2f Bq", Act_SWire_Bi210);}
  LegEntries_P1[20] = buffer;
  LegIsotopes_P1[21] = "^{234m}Pa SScin";
  if(Act_SScin_Pa234m_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_SScin_Pa234m, Act_SScin_Pa234m_Err);}
  else{sprintf (buffer, "A = %.2f Bq", Act_SScin_Pa234m);}
  LegEntries_P1[21] = buffer;
  LegIsotopes_P1[22] = "1 MeV #gamma (MuMetal)";
  if(Act_MuMetal_g1000_P1_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_MuMetal_g1000_P1, Act_MuMetal_g1000_P1_Err);}
  else{sprintf (buffer, "A = %.2f Bq", Act_MuMetal_g1000_P1);}
  LegEntries_P1[22] = buffer;
  LegIsotopes_P1[23] = "Neutrons";
  if(Act_Neutrons_P1_Err > 0){sprintf (buffer, "S = %.1f #pm %.1f x10^{-3}", 1000*Act_Neutrons_P1, 1000*Act_Neutrons_P1_Err);}
  else{sprintf (buffer, "S = %.1f x10^{-3}", 1000*Act_Neutrons_P1);}
  LegEntries_P1[23] = buffer;

  LegIsotopes_P2[0] = "Other MC";
  sprintf (buffer, " ");
  LegEntries_P2[0] = buffer;
  LegIsotopes_P2[1] = "^{40}K PMT";
  if(Act_PMT_K40_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_PMT_K40, Act_PMT_K40_Err);}
  else{sprintf (buffer, "A = %.1f Bq", Act_PMT_K40);}
  LegEntries_P2[1] = buffer;
  LegIsotopes_P2[2] = "^{40}K Steel Frame";
  if(Act_SteelFrame_K40_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_SteelFrame_K40, Act_SteelFrame_K40_Err);}
  else{sprintf (buffer, "A = %.1f Bq", Act_SteelFrame_K40);}
  LegEntries_P2[2] = buffer;
  LegIsotopes_P2[3] = "^{40}K Scint Inner";
  if(Act_ScintInn_K40_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_ScintInn_K40, Act_ScintInn_K40_Err);}
  else{sprintf (buffer, "A = %.1f Bq", Act_ScintInn_K40);}
  LegEntries_P2[3] = buffer;
  LegIsotopes_P2[4] = "^{40}K Scint Outer";
  if(Act_ScintOut_K40_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_ScintOut_K40, Act_ScintOut_K40_Err);}
  else{sprintf (buffer, "A = %.1f Bq", Act_ScintOut_K40);}
  LegEntries_P2[4] = buffer;
  LegIsotopes_P2[5] = "^{40}K Scint Petals";
  if(Act_ScintPet_K40_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_ScintPet_K40, Act_ScintPet_K40_Err);}
  else{sprintf (buffer, "A = %.1f Bq", Act_ScintPet_K40);}
  LegEntries_P2[5] = buffer;
  LegIsotopes_P2[6] = "^{214}Bi PMT";
  if(Act_PMT_Bi214_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_PMT_Bi214, Act_PMT_Bi214_Err);}
  else{sprintf (buffer, "A = %.2f Bq", Act_PMT_Bi214);}
  LegEntries_P2[6] = buffer;
  LegIsotopes_P2[7] = "^{214}Bi Fe Shield";
  if(Act_FeShield_Bi214_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_FeShield_Bi214, Act_FeShield_Bi214_Err);}
  else{sprintf (buffer, "A = %.2f Bq", Act_FeShield_Bi214);}
  LegEntries_P2[7] = buffer;
  LegIsotopes_P2[8] = "^{214}Bi Steel Frame";
  if(Act_SteelFrame_Bi214_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_SteelFrame_Bi214, Act_SteelFrame_Bi214_Err);}
  else{sprintf (buffer, "A = %.2f Bq", Act_SteelFrame_Bi214);}
  LegEntries_P2[8] = buffer;
  LegIsotopes_P2[9] = "^{214}Bi SScin P2";
  if(Act_SScin_Bi214_P2_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_SScin_Bi214_P2, Act_SScin_Bi214_P2_Err);}
  else{sprintf (buffer, "A = %.2f Bq", Act_SScin_Bi214_P2);}
  LegEntries_P2[9] = buffer;
  LegIsotopes_P2[10] = "^{214}Bi LSM Air P2";
  if(Act_Air_Bi214_P2_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_Air_Bi214_P2, Act_Air_Bi214_P2_Err);}
  else{sprintf (buffer, "A = %.2f Bq", Act_Air_Bi214_P2);}
  LegEntries_P2[10] = buffer;
  LegIsotopes_P2[11] = "^{208}Tl PMT";
  if(Act_PMT_Tl208_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_PMT_Tl208, Act_PMT_Tl208_Err);}
  else{sprintf (buffer, "A = %.2f Bq", Act_PMT_Tl208);}
  LegEntries_P2[11] = buffer;
  LegIsotopes_P2[12] = "^{208}Tl Fe Shield";
  if(Act_FeShield_Tl208_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_FeShield_Tl208, Act_FeShield_Tl208_Err);}
  else{sprintf (buffer, "A = %.2f Bq", Act_FeShield_Tl208);}
  LegEntries_P2[12] = buffer;
  LegIsotopes_P2[13] = "^{208}Tl Steel Frame";
  if(Act_SteelFrame_Tl208_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_SteelFrame_Tl208, Act_SteelFrame_Tl208_Err);}
  else{sprintf (buffer, "A = %.2f Bq", Act_SteelFrame_Tl208);}
  LegEntries_P2[13] = buffer;
  LegIsotopes_P2[14] = "^{208}Tl LSM Air P2";
  if(Act_Air_Tl208_P2_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_Air_Tl208_P2, Act_Air_Tl208_P2_Err);}
  else{sprintf (buffer, "A = %.2f Bq", Act_Air_Tl208_P2);}
  LegEntries_P2[14] = buffer;
  LegIsotopes_P2[15] = "^{60}Co Mu Metal";
  if(Act_MuMetal_Co60_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_MuMetal_Co60, Act_MuMetal_Co60_Err);}
  else{sprintf (buffer, "A = %.2f Bq", Act_MuMetal_Co60);}
  LegEntries_P2[15] = buffer;
  LegIsotopes_P2[16] = "^{60}Co Steel Frame";
  if(Act_SteelFrame_Co60_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_SteelFrame_Co60, Act_SteelFrame_Co60_Err);}
  else{sprintf (buffer, "A = %.2f Bq", Act_SteelFrame_Co60);}
  LegEntries_P2[16] = buffer;
  LegIsotopes_P2[17] = "^{60}Co Cu Petals";
  if(Act_CuPetals_Co60_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_CuPetals_Co60, Act_CuPetals_Co60_Err);}
  else{sprintf (buffer, "A = %.2f Bq", Act_CuPetals_Co60);}
  LegEntries_P2[17] = buffer;
  LegIsotopes_P2[18] = "^{60}Co Cu Tower";
  if(Act_CuTower_Co60_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_CuTower_Co60, Act_CuTower_Co60_Err);}
  else{sprintf (buffer, "A = %.2f Bq", Act_CuTower_Co60);}
  LegEntries_P2[18] = buffer;
  LegIsotopes_P2[19] = "^{210}Bi SScin";
  if(Act_SScin_Bi210_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_SScin_Bi210, Act_SScin_Bi210_Err);}
  else{sprintf (buffer, "A = %.2f Bq", Act_SScin_Bi210);}
  LegEntries_P2[19] = buffer;
  LegIsotopes_P2[20] = "^{210}Bi SWire";
  if(Act_SWire_Bi210_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_SWire_Bi210, Act_SWire_Bi210_Err);}
  else{sprintf (buffer, "A = %.2f Bq", Act_SWire_Bi210);}
  LegEntries_P2[20] = buffer;
  LegIsotopes_P2[21] = "^{234m}Pa SScin";
  if(Act_SScin_Pa234m_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_SScin_Pa234m, Act_SScin_Pa234m_Err);}
  else{sprintf (buffer, "A = %.2f Bq", Act_SScin_Pa234m);}
  LegEntries_P2[21] = buffer;
  LegIsotopes_P2[22] = "1 MeV #gamma (MuMetal)";
  if(Act_MuMetal_g1000_P2_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_MuMetal_g1000_P2, Act_MuMetal_g1000_P2_Err);}
  else{sprintf (buffer, "A = %.2f Bq", Act_MuMetal_g1000_P2);}
  LegEntries_P2[22] = buffer;
  LegIsotopes_P2[23] = "Neutrons";
  if(Act_Neutrons_P2_Err > 0){sprintf (buffer, "S = %.1f #pm %.1f x10^{-3}", 1000*Act_Neutrons_P2, 1000*Act_Neutrons_P2_Err);}
  else{sprintf (buffer, "S = %.1f x10^{-3}", 1000*Act_Neutrons_P2);}
  LegEntries_P2[23] = buffer;

  // Make legends
  for(int i = 0; i < 6; i++){
    Legend_OCE[i] = new TLegend(0.540,0.4845,0.947,0.947);
    Legend_OCE[i]->SetNColumns(2);
    Legend_OCE[i]->SetColumnSeparation(-0.05);
    Legend_OCE[i]->SetFillColor(0);
    Legend_OCE[i]->SetLineColor(0);
    Legend_OCE[i]->SetBorderSize(0);
    LegendLog_OCE[i] = new TLegend(0.7199,0.4845,0.947,0.947);
    LegendLog_OCE[i]->SetFillColor(0);
    LegendLog_OCE[i]->SetLineColor(0);
    LegendLog_OCE[i]->SetBorderSize(0);
  }

  char Num_Events[40];

  sprintf (Num_Events, "%d Events", (int) h_OCE_Data_P1_Inner->GetEntries());
  Legend_OCE[0]->AddEntry(h_OCE_Data_P1_Inner, "Data", "lpe");
  Legend_OCE[0]->AddEntry(h_OCE_Data_P1_Inner, Num_Events, "");
  LegendLog_OCE[0]->AddEntry(h_OCE_Data_P1_Inner, "Data", "lpe");

  sprintf (Num_Events, "%d Events", (int) h_OCE_Data_P1_Outer->GetEntries());
  Legend_OCE[1]->AddEntry(h_OCE_Data_P1_Outer, "Data", "lpe");
  Legend_OCE[1]->AddEntry(h_OCE_Data_P1_Outer, Num_Events, "");
  LegendLog_OCE[1]->AddEntry(h_OCE_Data_P1_Outer, "Data", "lpe");

  sprintf (Num_Events, "%d Events", (int) h_OCE_Data_P1_Petal->GetEntries());
  Legend_OCE[2]->AddEntry(h_OCE_Data_P1_Petal, "Data", "lpe");
  Legend_OCE[2]->AddEntry(h_OCE_Data_P1_Petal, Num_Events, "");
  LegendLog_OCE[2]->AddEntry(h_OCE_Data_P1_Petal, "Data", "lpe");

  sprintf (Num_Events, "%d Events", (int) h_OCE_Data_P2_Inner->GetEntries());
  Legend_OCE[3]->AddEntry(h_OCE_Data_P2_Inner, "Data", "lpe");
  Legend_OCE[3]->AddEntry(h_OCE_Data_P2_Inner, Num_Events, "");
  LegendLog_OCE[3]->AddEntry(h_OCE_Data_P2_Inner, "Data", "lpe");

  sprintf (Num_Events, "%d Events", (int) h_OCE_Data_P2_Outer->GetEntries());
  Legend_OCE[4]->AddEntry(h_OCE_Data_P2_Outer, "Data", "lpe");
  Legend_OCE[4]->AddEntry(h_OCE_Data_P2_Outer, Num_Events, "");
  LegendLog_OCE[4]->AddEntry(h_OCE_Data_P2_Outer, "Data", "lpe");

  sprintf (Num_Events, "%d Events", (int) h_OCE_Data_P2_Petal->GetEntries());
  Legend_OCE[5]->AddEntry(h_OCE_Data_P2_Petal, "Data", "lpe");
  Legend_OCE[5]->AddEntry(h_OCE_Data_P2_Petal, Num_Events, "");
  LegendLog_OCE[5]->AddEntry(h_OCE_Data_P2_Petal, "Data", "lpe");

  for(int j = 0; j < 6; j++){

    if(j < 3){
      TH1 *h;
      TIter   next(StackColl_OCE[j]->GetHists());
      for(int i = 0; i < 24; i++){
	h = (TH1*) next();
	Legend_OCE[j]->AddEntry(h, LegIsotopes_P1[i].c_str(), "f");
	Legend_OCE[j]->AddEntry(h, LegEntries_P1[i].c_str(), "");
	LegendLog_OCE[j]->AddEntry(h, LegIsotopes_P1[i].c_str(), "f");
      }
    } else{
      TH1 *h;
      TIter   next(StackColl_OCE[j]->GetHists());
      for(int i = 0; i < 24; i++){
	h = (TH1*) next();
	Legend_OCE[j]->AddEntry(h, LegIsotopes_P2[i].c_str(), "f");
	Legend_OCE[j]->AddEntry(h, LegEntries_P2[i].c_str(), "");
	LegendLog_OCE[j]->AddEntry(h, LegIsotopes_P2[i].c_str(), "f");
      }
    }
  }

  // Make chi square template
  for (int i = 0; i < 6; i++){
    ChiSquares_OCE[i] = new TPaveText(0.587,0.435,0.762,0.475,"LNDC");
    ChiSquares_OCE[i]->SetFillColor(0);
    ChiSquares_OCE[i]->SetLineColor(0);
    ChiSquares_OCE[i]->SetBorderSize(0);
    ChiSquares_OCE[i]->SetTextAlign(12);

    ChiSquaresLog_OCE[i] = new TPaveText(0.737,0.427,0.921,0.467,"LNDC");
    ChiSquaresLog_OCE[i]->SetFillColor(0);
    ChiSquaresLog_OCE[i]->SetLineColor(0);
    ChiSquaresLog_OCE[i]->SetBorderSize(0);
    ChiSquaresLog_OCE[i]->SetTextAlign(12);
  }

  char ChiSquareText[100];
  pair<Double_t,Int_t> ChiSquareResult;

  ChiSquareResult = ChiSquareTest(h_OCE_Data_P1_Inner, (TH1D*)StackColl_OCE[0]->GetStack()->Last());
  sprintf(ChiSquareText, "#chi^{2} / ndf = %.2f / %.d", ChiSquareResult.first, ChiSquareResult.second);
  ChiSquares_OCE[0]->AddText(ChiSquareText);
  ChiSquaresLog_OCE[0]->AddText(ChiSquareText);

  ChiSquareResult = ChiSquareTest(h_OCE_Data_P1_Outer, (TH1D*)StackColl_OCE[1]->GetStack()->Last());
  sprintf(ChiSquareText, "#chi^{2} / ndf = %.2f / %.d", ChiSquareResult.first, ChiSquareResult.second);
  ChiSquares_OCE[1]->AddText(ChiSquareText);
  ChiSquaresLog_OCE[1]->AddText(ChiSquareText);

  ChiSquareResult = ChiSquareTest(h_OCE_Data_P1_Petal, (TH1D*)StackColl_OCE[2]->GetStack()->Last());
  sprintf(ChiSquareText, "#chi^{2} / ndf = %.2f / %.d", ChiSquareResult.first, ChiSquareResult.second);
  ChiSquares_OCE[2]->AddText(ChiSquareText);
  ChiSquaresLog_OCE[2]->AddText(ChiSquareText);

  ChiSquareResult = ChiSquareTest(h_OCE_Data_P2_Inner, (TH1D*)StackColl_OCE[3]->GetStack()->Last());
  sprintf(ChiSquareText, "#chi^{2} / ndf = %.2f / %.d", ChiSquareResult.first, ChiSquareResult.second);
  ChiSquares_OCE[3]->AddText(ChiSquareText);
  ChiSquaresLog_OCE[3]->AddText(ChiSquareText);

  ChiSquareResult = ChiSquareTest(h_OCE_Data_P2_Outer, (TH1D*)StackColl_OCE[4]->GetStack()->Last());
  sprintf(ChiSquareText, "#chi^{2} / ndf = %.2f / %.d", ChiSquareResult.first, ChiSquareResult.second);
  ChiSquares_OCE[4]->AddText(ChiSquareText);
  ChiSquaresLog_OCE[4]->AddText(ChiSquareText);

  ChiSquareResult = ChiSquareTest(h_OCE_Data_P2_Petal, (TH1D*)StackColl_OCE[5]->GetStack()->Last());
  sprintf(ChiSquareText, "#chi^{2} / ndf = %.2f / %.d", ChiSquareResult.first, ChiSquareResult.second);
  ChiSquares_OCE[5]->AddText(ChiSquareText);
  ChiSquaresLog_OCE[5]->AddText(ChiSquareText);

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
