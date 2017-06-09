#include "addChannelToStacks_1e.h"
#include "chiSquareTest.h"

extern THStack* StackColl_1e[];
extern THStack* IntStackColl_1e[];
extern THStack* ExtStackColl_1e[];
extern THStack* RadStackColl_1e[];
extern THStack* SigStackColl_1e[];
extern TH1D* h_1e_Data_P1_SeOld;
extern TH1D* h_1e_Data_P1_SeNew;
extern TH1D* h_1e_Data_P1_Strip;
extern TH1D* h_1e_Data_P2_SeOld;
extern TH1D* h_1e_Data_P2_SeNew;
extern TH1D* h_1e_Data_P2_Strip;
extern const Int_t AccptRunTime;
extern TFile* infile_1e;
extern TLegend* Legend_1e[];
extern TLegend* LegendLog_1e[];
extern TPaveText* ChiSquares_1e[];
extern TPaveText* ChiSquaresLog_1e[];

void addBackgrounds_1e(double *Activities_Ext, double *Activities_Ext_Err, double *Denominators_Ext, double *Activities_Rad, double *Activities_Rad_Err,  double *Denominators_Rad, double *Activities_Int, double *Activities_Int_Err,  double *Denominators_Int, double *Activities_Sig, double *Activities_Sig_Err, double *Denominators_Sig, double *AdjustActs, double *AdjustActs_Err){

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
  Int_t    FillColor_MuMetal_g1000    = kYellow+1;
  Int_t    FillColor_Neutrons         = kViolet+1;

  // Create collection of histogram stacks
  ExtStackColl_1e[0] = new THStack("h_1e_P1_SeOld","Electron Energy");
  ExtStackColl_1e[1] = new THStack("h_1e_P1_SeNew","Electron Energy");
  ExtStackColl_1e[2] = new THStack("h_1e_P1_Strip","Electron Energy");
  ExtStackColl_1e[3] = new THStack("h_1e_P2_SeOld","Electron Energy");
  ExtStackColl_1e[4] = new THStack("h_1e_P2_SeNew","Electron Energy");
  ExtStackColl_1e[5] = new THStack("h_1e_P2_Strip","Electron Energy");

  // Add External Backgrounds

  // 0) PMT_K40
  Double_t ScaleFactor_PMT_K40 = Act_PMT_K40*AccptRunTime/Denom_PMT_K40;
  addChannelToStacks_1e("PMT_K40", ScaleFactor_PMT_K40, FillColor_PMT_K40, ExtStackColl_1e, infile_1e);

  // 1) PMT_Bi214
  Double_t ScaleFactor_PMT_Bi214 = Act_PMT_Bi214*AccptRunTime/Denom_PMT_Bi214;
  addChannelToStacks_1e("PMT_Bi214", ScaleFactor_PMT_Bi214, FillColor_PMT_Bi214, ExtStackColl_1e, infile_1e);

  // 2) PMT_Tl208
  Double_t ScaleFactor_PMT_Tl208 = Act_PMT_Tl208*AccptRunTime/Denom_PMT_Tl208;
  addChannelToStacks_1e("PMT_Tl208", ScaleFactor_PMT_Tl208, FillColor_PMT_Tl208, ExtStackColl_1e, infile_1e);

  // 3) PMT_Ac228
  Double_t ScaleFactor_PMT_Ac228 = Act_PMT_Ac228*AccptRunTime/Denom_PMT_Ac228;
  addChannelToStacks_1e("PMT_Ac228", ScaleFactor_PMT_Ac228, FillColor_PMT_Ac228, ExtStackColl_1e, infile_1e);

  // 4) FeShield_Bi214
  Double_t ScaleFactor_FeShield_Bi214 = Act_FeShield_Bi214*AccptRunTime/Denom_FeShield_Bi214;
  addChannelToStacks_1e("FeShield_Bi214", ScaleFactor_FeShield_Bi214, FillColor_FeShield_Bi214, ExtStackColl_1e, infile_1e);

  // 5) FeShield_Tl208
  Double_t ScaleFactor_FeShield_Tl208 = Act_FeShield_Tl208*AccptRunTime/Denom_FeShield_Tl208;
  addChannelToStacks_1e("FeShield_Tl208", ScaleFactor_FeShield_Tl208, FillColor_FeShield_Tl208, ExtStackColl_1e, infile_1e);

  // 6) FeShield_Ac228
  Double_t ScaleFactor_FeShield_Ac228 = Act_FeShield_Ac228*AccptRunTime/Denom_FeShield_Ac228;
  addChannelToStacks_1e("FeShield_Ac228", ScaleFactor_FeShield_Ac228, FillColor_FeShield_Ac228, ExtStackColl_1e, infile_1e);

  // 7) MuMetal_Co60
  Double_t ScaleFactor_MuMetal_Co60 = Act_MuMetal_Co60*AccptRunTime/Denom_MuMetal_Co60;
  addChannelToStacks_1e("MuMetal_Co60", ScaleFactor_MuMetal_Co60, FillColor_MuMetal_Co60, ExtStackColl_1e, infile_1e);

  // 8) SteelFrame_K40
  Double_t ScaleFactor_SteelFrame_K40 = Act_SteelFrame_K40*AccptRunTime/Denom_SteelFrame_K40;
  addChannelToStacks_1e("SteelFrame_K40", ScaleFactor_SteelFrame_K40, FillColor_SteelFrame_K40, ExtStackColl_1e, infile_1e);

  // 9) SteelFrame_Bi214
  Double_t ScaleFactor_SteelFrame_Bi214 = Act_SteelFrame_Bi214*AccptRunTime/Denom_SteelFrame_Bi214;
  addChannelToStacks_1e("SteelFrame_Bi214", ScaleFactor_SteelFrame_Bi214, FillColor_SteelFrame_Bi214, ExtStackColl_1e, infile_1e);

  // 10) SteelFrame_Tl208
  Double_t ScaleFactor_SteelFrame_Tl208 = Act_SteelFrame_Tl208*AccptRunTime/Denom_SteelFrame_Tl208;
  addChannelToStacks_1e("SteelFrame_Tl208", ScaleFactor_SteelFrame_Tl208, FillColor_SteelFrame_Tl208, ExtStackColl_1e, infile_1e);

  // 11) SteelFrame_Ac228
  Double_t ScaleFactor_SteelFrame_Ac228 = Act_SteelFrame_Ac228*AccptRunTime/Denom_SteelFrame_Ac228;
  addChannelToStacks_1e("SteelFrame_Ac228", ScaleFactor_SteelFrame_Ac228, FillColor_SteelFrame_Ac228, ExtStackColl_1e, infile_1e);

  // 12) SteelFrame_Co60
  Double_t ScaleFactor_SteelFrame_Co60 = Act_SteelFrame_Co60*AccptRunTime/Denom_SteelFrame_Co60;
  addChannelToStacks_1e("SteelFrame_Co60", ScaleFactor_SteelFrame_Co60, FillColor_SteelFrame_Co60, ExtStackColl_1e, infile_1e);

  // 13) CuPetals_Co60
  Double_t ScaleFactor_CuPetals_Co60 = Act_CuPetals_Co60*AccptRunTime/Denom_CuPetals_Co60;
  addChannelToStacks_1e("CuPetals_Co60", ScaleFactor_CuPetals_Co60, FillColor_CuPetals_Co60, ExtStackColl_1e, infile_1e);

  // 14) CuTower_Co60
  Double_t ScaleFactor_CuTower_Co60 = Act_CuTower_Co60*AccptRunTime/Denom_CuTower_Co60;
  addChannelToStacks_1e("CuTower_Co60", ScaleFactor_CuTower_Co60, FillColor_CuTower_Co60, ExtStackColl_1e, infile_1e);

  // 15) ScintInn_K40
  Double_t ScaleFactor_ScintInn_K40 = Act_ScintInn_K40*AccptRunTime/Denom_ScintInn_K40;
  addChannelToStacks_1e("ScintInn_K40", ScaleFactor_ScintInn_K40, FillColor_ScintInn_K40, ExtStackColl_1e, infile_1e);

  // 16) ScintOut_K40
  Double_t ScaleFactor_ScintOut_K40 = Act_ScintOut_K40*AccptRunTime/Denom_ScintOut_K40;
  addChannelToStacks_1e("ScintOut_K40", ScaleFactor_ScintOut_K40, FillColor_ScintOut_K40, ExtStackColl_1e, infile_1e);

  // 17) ScintPet_K40
  Double_t ScaleFactor_ScintPet_K40 = Act_ScintPet_K40*AccptRunTime/Denom_ScintPet_K40;
  addChannelToStacks_1e("ScintPet_K40", ScaleFactor_ScintPet_K40, FillColor_ScintPet_K40, ExtStackColl_1e, infile_1e);

  // 18) SScin_Pa234m
  Double_t ScaleFactor_SScin_Pa234m = Act_SScin_Pa234m*AccptRunTime/Denom_SScin_Pa234m;
  addChannelToStacks_1e("SScin_Pa234m", ScaleFactor_SScin_Pa234m, FillColor_SScin_Pa234m, ExtStackColl_1e, infile_1e);

  // 19) MuMetal_g1000
  Double_t ScaleFactor_MuMetal_g1000_P1 = Act_MuMetal_g1000_P1*AccptRunTime/Denom_MuMetal_g1000;
  addChannelToStacks_1e("MuMetal_g1000_P1", ScaleFactor_MuMetal_g1000_P1, FillColor_MuMetal_g1000, ExtStackColl_1e, infile_1e);
  Double_t ScaleFactor_MuMetal_g1000_P2 = Act_MuMetal_g1000_P2*AccptRunTime/Denom_MuMetal_g1000;
  addChannelToStacks_1e("MuMetal_g1000_P2", ScaleFactor_MuMetal_g1000_P2, FillColor_MuMetal_g1000, ExtStackColl_1e, infile_1e);

  // 20) Neutrons
  Double_t ScaleFactor_Neutrons_P1 = Act_Neutrons_P1*AccptRunTime/Denom_Neutrons;
  addChannelToStacks_1e("Data_Neutrons_P1", ScaleFactor_Neutrons_P1, FillColor_Neutrons, ExtStackColl_1e, infile_1e);
  Double_t ScaleFactor_Neutrons_P2 = Act_Neutrons_P2*AccptRunTime/Denom_Neutrons;
  addChannelToStacks_1e("Data_Neutrons_P2", ScaleFactor_Neutrons_P2, FillColor_Neutrons, ExtStackColl_1e, infile_1e);

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

  Double_t Act_SWire_Bi210_Err       = Activities_Rad_Err[8];
  Double_t Act_SFoil_SeNew_Bi210_Err = Activities_Rad_Err[9];
  Double_t Act_SFoil_SeOld_Bi210_Err = Activities_Rad_Err[10];
  Double_t Act_SFoil_Strip_Bi210_Err = Activities_Rad_Err[11];
  Double_t Act_SScin_Bi210_Err       = Activities_Rad_Err[12];
  Double_t Act_Air_Bi214_P1_Err      = Activities_Rad_Err[15];
  Double_t Act_Air_Tl208_P1_Err      = Activities_Rad_Err[16];
  Double_t Act_Air_Bi214_P2_Err      = 0;
  Double_t Act_Air_Tl208_P2_Err      = 0;

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
  RadStackColl_1e[0] = new THStack("h_1e_P1_SeOld","Electron Energy");
  RadStackColl_1e[1] = new THStack("h_1e_P1_SeNew","Electron Energy");
  RadStackColl_1e[2] = new THStack("h_1e_P1_Strip","Electron Energy");
  RadStackColl_1e[3] = new THStack("h_1e_P2_SeOld","Electron Energy");
  RadStackColl_1e[4] = new THStack("h_1e_P2_SeNew","Electron Energy");
  RadStackColl_1e[5] = new THStack("h_1e_P2_Strip","Electron Energy");

  //  Add Radon Backgrounds

  // 0) SWire_Bi214
  Double_t Scale_SWire_Bi214_P1 = Act_SWire_Bi214_P1*AccptRunTime/Denom_SWire_Bi214;
  addChannelToStacks_1e("SWire_Bi214_P1", Scale_SWire_Bi214_P1, FillColor_SWire_Bi214, RadStackColl_1e, infile_1e);
  Double_t Scale_SWire_Bi214_P2 = Act_SWire_Bi214_P2*AccptRunTime/Denom_SWire_Bi214;
  addChannelToStacks_1e("SWire_Bi214_P2", Scale_SWire_Bi214_P2, FillColor_SWire_Bi214, RadStackColl_1e, infile_1e);

  // 1) SWire_Pb214
  Double_t Scale_SWire_Pb214_P1 = Act_SWire_Pb214_P1*AccptRunTime/Denom_SWire_Pb214;
  addChannelToStacks_1e("SWire_Pb214_P1", Scale_SWire_Pb214_P1, FillColor_SWire_Pb214, RadStackColl_1e, infile_1e);
  Double_t Scale_SWire_Pb214_P2 = Act_SWire_Pb214_P2*AccptRunTime/Denom_SWire_Pb214;
  addChannelToStacks_1e("SWire_Pb214_P2", Scale_SWire_Pb214_P2, FillColor_SWire_Pb214, RadStackColl_1e, infile_1e);

  // 2) SWire_Bi210 
  Double_t Scale_SWire_Bi210 = Act_SWire_Bi210*AccptRunTime/Denom_SWire_Bi210;
  addChannelToStacks_1e("SWire_Bi210_P1", Scale_SWire_Bi210, FillColor_SWire_Bi210, RadStackColl_1e, infile_1e);
  addChannelToStacks_1e("SWire_Bi210_P2", Scale_SWire_Bi210, FillColor_SWire_Bi210, RadStackColl_1e, infile_1e);

  // 3) SWire_Tl208 
  Double_t Scale_SWire_Tl208_P1 = Act_SWire_Tl208_P1*AccptRunTime/Denom_SWire_Tl208;
  addChannelToStacks_1e("SWire_Tl208_P1", Scale_SWire_Tl208_P1, FillColor_SWire_Tl208, RadStackColl_1e, infile_1e);
  Double_t Scale_SWire_Tl208_P2 = Act_SWire_Tl208_P2*AccptRunTime/Denom_SWire_Tl208;
  addChannelToStacks_1e("SWire_Tl208_P2", Scale_SWire_Tl208_P2, FillColor_SWire_Tl208, RadStackColl_1e, infile_1e);

  // 4) SFoil_Bi214_In
  Double_t ScaleFactor_SFoil_Bi214_In_P1 = Act_SFoil_Bi214_In_P1*AccptRunTime/Denom_SFoil_Bi214;
  addChannelToStacks_1e("SFoil_Bi214_In_P1", ScaleFactor_SFoil_Bi214_In_P1, FillColor_SFoil_Bi214, RadStackColl_1e, infile_1e);
  Double_t ScaleFactor_SFoil_Bi214_In_P2 = Act_SFoil_Bi214_In_P2*AccptRunTime/Denom_SFoil_Bi214;
  addChannelToStacks_1e("SFoil_Bi214_In_P2", ScaleFactor_SFoil_Bi214_In_P2, FillColor_SFoil_Bi214, RadStackColl_1e, infile_1e);

  // 5) SFoil_Bi214_Out
  Double_t ScaleFactor_SFoil_Bi214_Out_P1 = Act_SFoil_Bi214_Out_P1*AccptRunTime/Denom_SFoil_Bi214;
  addChannelToStacks_1e("SFoil_Bi214_Out_P1", ScaleFactor_SFoil_Bi214_Out_P1, FillColor_SFoil_Bi214, RadStackColl_1e, infile_1e);
  Double_t ScaleFactor_SFoil_Bi214_Out_P2 = Act_SFoil_Bi214_Out_P2*AccptRunTime/Denom_SFoil_Bi214;
  addChannelToStacks_1e("SFoil_Bi214_Out_P2", ScaleFactor_SFoil_Bi214_Out_P2, FillColor_SFoil_Bi214, RadStackColl_1e, infile_1e);

  // 6) SFoil_Pb214_In
  Double_t ScaleFactor_SFoil_Pb214_In_P1 = Act_SFoil_Pb214_In_P1*AccptRunTime/Denom_SFoil_Pb214;
  addChannelToStacks_1e("SFoil_Pb214_In_P1", ScaleFactor_SFoil_Pb214_In_P1, FillColor_SFoil_Pb214, RadStackColl_1e, infile_1e);
  Double_t ScaleFactor_SFoil_Pb214_In_P2 = Act_SFoil_Pb214_In_P2*AccptRunTime/Denom_SFoil_Pb214;
  addChannelToStacks_1e("SFoil_Pb214_In_P2", ScaleFactor_SFoil_Pb214_In_P2, FillColor_SFoil_Pb214, RadStackColl_1e, infile_1e);

  // 7) SFoil_Pb214_Out
  Double_t ScaleFactor_SFoil_Pb214_Out_P1 = Act_SFoil_Pb214_Out_P1*AccptRunTime/Denom_SFoil_Pb214;
  addChannelToStacks_1e("SFoil_Pb214_Out_P1", ScaleFactor_SFoil_Pb214_Out_P1, FillColor_SFoil_Pb214, RadStackColl_1e, infile_1e);
  Double_t ScaleFactor_SFoil_Pb214_Out_P2 = Act_SFoil_Pb214_Out_P2*AccptRunTime/Denom_SFoil_Pb214;
  addChannelToStacks_1e("SFoil_Pb214_Out_P2", ScaleFactor_SFoil_Pb214_Out_P2, FillColor_SFoil_Pb214, RadStackColl_1e, infile_1e);

  // 8) SFoil_SeNew_Bi210 
  Double_t ScaleFactor_SFoil_SeNew_Bi210 = Act_SFoil_SeNew_Bi210*AccptRunTime/Denom_SFoil_Bi210;
  addChannelToStacks_1e("SFoil_SeNew_Bi210_P1", ScaleFactor_SFoil_SeNew_Bi210, FillColor_SFoil_Bi210, RadStackColl_1e, infile_1e);
  addChannelToStacks_1e("SFoil_SeNew_Bi210_P2", ScaleFactor_SFoil_SeNew_Bi210, FillColor_SFoil_Bi210, RadStackColl_1e, infile_1e);

  // 9) SFoil_SeOld_Bi210 
  Double_t ScaleFactor_SFoil_SeOld_Bi210 = Act_SFoil_SeOld_Bi210*AccptRunTime/Denom_SFoil_Bi210;
  addChannelToStacks_1e("SFoil_SeOld_Bi210_P1", ScaleFactor_SFoil_SeOld_Bi210, FillColor_SFoil_Bi210, RadStackColl_1e, infile_1e);
  addChannelToStacks_1e("SFoil_SeOld_Bi210_P2", ScaleFactor_SFoil_SeOld_Bi210, FillColor_SFoil_Bi210, RadStackColl_1e, infile_1e);

  // 10) SFoil_Strip_Bi210 (in SeNew Dirty strip)
  Double_t ScaleFactor_SFoil_Strip_Bi210 = Act_SFoil_Strip_Bi210*AccptRunTime/Denom_SFoil_Bi210;
  addChannelToStacks_1e("SFoil_Strip_Bi210_P1", ScaleFactor_SFoil_Strip_Bi210, FillColor_SFoil_Bi210, RadStackColl_1e, infile_1e);
  addChannelToStacks_1e("SFoil_Strip_Bi210_P2", ScaleFactor_SFoil_Strip_Bi210, FillColor_SFoil_Bi210, RadStackColl_1e, infile_1e);

  // 11) SScin_Bi214
  Double_t ScaleFactor_SScin_Bi214_P1 = Act_SScin_Bi214_P1*AccptRunTime/Denom_SScin_Bi214;
  addChannelToStacks_1e("SScin_Bi214_P1", ScaleFactor_SScin_Bi214_P1, FillColor_SScin_Bi214, RadStackColl_1e, infile_1e);
  Double_t ScaleFactor_SScin_Bi214_P2 = Act_SScin_Bi214_P2*AccptRunTime/Denom_SScin_Bi214;
  addChannelToStacks_1e("SScin_Bi214_P2", ScaleFactor_SScin_Bi214_P2, FillColor_SScin_Bi214, RadStackColl_1e, infile_1e);

  // 12) SScin_Pb214
  Double_t ScaleFactor_SScin_Pb214_P1 = Act_SScin_Pb214_P1*AccptRunTime/Denom_SScin_Pb214;
  addChannelToStacks_1e("SScin_Pb214_P1", ScaleFactor_SScin_Pb214_P1, FillColor_SScin_Pb214, RadStackColl_1e, infile_1e);
  Double_t ScaleFactor_SScin_Pb214_P2 = Act_SScin_Pb214_P2*AccptRunTime/Denom_SScin_Pb214;
  addChannelToStacks_1e("SScin_Pb214_P2", ScaleFactor_SScin_Pb214_P2, FillColor_SScin_Pb214, RadStackColl_1e, infile_1e);

  // 13) SScin_Bi210
  Double_t ScaleFactor_SScin_Bi210 = Act_SScin_Bi210*AccptRunTime/Denom_SScin_Bi210;
  addChannelToStacks_1e("SScin_Bi210_P1", ScaleFactor_SScin_Bi210, FillColor_SScin_Bi210, RadStackColl_1e, infile_1e);
  addChannelToStacks_1e("SScin_Bi210_P2", ScaleFactor_SScin_Bi210, FillColor_SScin_Bi210, RadStackColl_1e, infile_1e);

  // 14) Air_Bi214
  Double_t ScaleFactor_Air_Bi214_P1 = Act_Air_Bi214_P1*AccptRunTime/Denom_Air_Bi214;
  addChannelToStacks_1e("Air_Bi214_P1", ScaleFactor_Air_Bi214_P1, FillColor_Air_Bi214, RadStackColl_1e, infile_1e);
  Double_t ScaleFactor_Air_Bi214_P2 = Act_Air_Bi214_P2*AccptRunTime/Denom_Air_Bi214;
  addChannelToStacks_1e("Air_Bi214_P2", ScaleFactor_Air_Bi214_P2, FillColor_Air_Bi214, RadStackColl_1e, infile_1e);

  // 15) Air_Pb214
  Double_t ScaleFactor_Air_Pb214_P1 = Act_Air_Pb214_P1*AccptRunTime/Denom_Air_Pb214;
  addChannelToStacks_1e("Air_Pb214_P1", ScaleFactor_Air_Pb214_P1, FillColor_Air_Pb214, RadStackColl_1e, infile_1e);
  Double_t ScaleFactor_Air_Pb214_P2 = Act_Air_Pb214_P2*AccptRunTime/Denom_Air_Pb214;
  addChannelToStacks_1e("Air_Pb214_P2", ScaleFactor_Air_Pb214_P2, FillColor_Air_Pb214, RadStackColl_1e, infile_1e);

  // 16) Air_Tl208
  Double_t ScaleFactor_Air_Tl208_P1 = Act_Air_Tl208_P1*AccptRunTime/Denom_Air_Tl208;
  addChannelToStacks_1e("Air_Tl208_P1", ScaleFactor_Air_Tl208_P1, FillColor_Air_Tl208, RadStackColl_1e, infile_1e);
  Double_t ScaleFactor_Air_Tl208_P2 = Act_Air_Tl208_P2*AccptRunTime/Denom_Air_Tl208;
  addChannelToStacks_1e("Air_Tl208_P2", ScaleFactor_Air_Tl208_P2, FillColor_Air_Tl208, RadStackColl_1e, infile_1e);


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

  Double_t Act_SeNew_Pa234m_Err = Activities_Int_Err[5];
  Double_t Act_SeOld_Pa234m_Err = Activities_Int_Err[6];
  Double_t Act_SeNew_K40_Err    = Activities_Int_Err[7];
  Double_t Act_SeOld_K40_Err    = Activities_Int_Err[8];

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
  IntStackColl_1e[0] = new THStack("h_1e_P1_SeOld","Electron Energy");
  IntStackColl_1e[1] = new THStack("h_1e_P1_SeNew","Electron Energy");
  IntStackColl_1e[2] = new THStack("h_1e_P1_Strip","Electron Energy");
  IntStackColl_1e[3] = new THStack("h_1e_P2_SeOld","Electron Energy");
  IntStackColl_1e[4] = new THStack("h_1e_P2_SeNew","Electron Energy");
  IntStackColl_1e[5] = new THStack("h_1e_P2_Strip","Electron Energy");

  // Add Internal Backgrounds

  // 0) SeNew_Bi214
  Double_t ScaleFactor_SeNew_Bi214 = Act_SeNew_Bi214*AccptRunTime/Denom_SeNew_Bi214;
  addChannelToStacks_1e("SeNew_Bi214", ScaleFactor_SeNew_Bi214, FillColor_SeNew_Bi214, IntStackColl_1e, infile_1e);

  // 1) SeOld_Bi214
  Double_t ScaleFactor_SeOld_Bi214 = Act_SeOld_Bi214*AccptRunTime/Denom_SeOld_Bi214;
  addChannelToStacks_1e("SeOld_Bi214", ScaleFactor_SeOld_Bi214, FillColor_SeOld_Bi214, IntStackColl_1e, infile_1e);

  // 2) Mylar_Bi214
  Double_t ScaleFactor_Mylar_Bi214 = Act_Mylar_Bi214*AccptRunTime/Denom_Mylar_Bi214;
  addChannelToStacks_1e("Mylar_Bi214", ScaleFactor_Mylar_Bi214, FillColor_Mylar_Bi214, IntStackColl_1e, infile_1e);

  // 3) SeNew_Pb214
  Double_t ScaleFactor_SeNew_Pb214 = Act_SeNew_Pb214*AccptRunTime/Denom_SeNew_Pb214;
  addChannelToStacks_1e("SeNew_Pb214", ScaleFactor_SeNew_Pb214, FillColor_SeNew_Pb214, IntStackColl_1e, infile_1e);

  // 4) SeOld_Pb214
  Double_t ScaleFactor_SeOld_Pb214 = Act_SeOld_Pb214*AccptRunTime/Denom_SeOld_Pb214;
  addChannelToStacks_1e("SeOld_Pb214", ScaleFactor_SeOld_Pb214, FillColor_SeOld_Pb214, IntStackColl_1e, infile_1e);

  // 5) Mylar_Pb214
  Double_t ScaleFactor_Mylar_Pb214 = Act_Mylar_Pb214*AccptRunTime/Denom_Mylar_Pb214;
  addChannelToStacks_1e("Mylar_Pb214", ScaleFactor_Mylar_Pb214, FillColor_Mylar_Pb214, IntStackColl_1e, infile_1e);

  // 6) SeNew_Tl208
  Double_t ScaleFactor_SeNew_Tl208 = Act_SeNew_Tl208*AccptRunTime/Denom_SeNew_Tl208;
  addChannelToStacks_1e("SeNew_Tl208", ScaleFactor_SeNew_Tl208, FillColor_SeNew_Tl208, IntStackColl_1e, infile_1e);

  // 7) SeOld_Tl208
  Double_t ScaleFactor_SeOld_Tl208 = Act_SeOld_Tl208*AccptRunTime/Denom_SeOld_Tl208;
  addChannelToStacks_1e("SeOld_Tl208", ScaleFactor_SeOld_Tl208, FillColor_SeOld_Tl208, IntStackColl_1e, infile_1e);

  // 8) SeNew_Bi212
  Double_t ScaleFactor_SeNew_Bi212 = Act_SeNew_Bi212*AccptRunTime/Denom_SeNew_Bi212;
  addChannelToStacks_1e("SeNew_Bi212", ScaleFactor_SeNew_Bi212, FillColor_SeNew_Bi212, IntStackColl_1e, infile_1e);

  // 9) SeOld_Bi212
  Double_t ScaleFactor_SeOld_Bi212 = Act_SeOld_Bi212*AccptRunTime/Denom_SeOld_Bi212;
  addChannelToStacks_1e("SeOld_Bi212", ScaleFactor_SeOld_Bi212, FillColor_SeOld_Bi212, IntStackColl_1e, infile_1e);

  // 10) SeNew_Ac228
  Double_t ScaleFactor_SeNew_Ac228 = Act_SeNew_Ac228*AccptRunTime/Denom_SeNew_Ac228;
  addChannelToStacks_1e("SeNew_Ac228", ScaleFactor_SeNew_Ac228, FillColor_SeNew_Ac228, IntStackColl_1e, infile_1e);

  // 11) SeOld_Ac228
  Double_t ScaleFactor_SeOld_Ac228 = Act_SeOld_Ac228*AccptRunTime/Denom_SeOld_Ac228;
  addChannelToStacks_1e("SeOld_Ac228", ScaleFactor_SeOld_Ac228, FillColor_SeOld_Ac228, IntStackColl_1e, infile_1e);

  // 12) SeNew_Pa234m
  Double_t ScaleFactor_SeNew_Pa234m = Act_SeNew_Pa234m*AccptRunTime/Denom_SeNew_Pa234m;
  addChannelToStacks_1e("SeNew_Pa234m", ScaleFactor_SeNew_Pa234m, FillColor_SeNew_Pa234m, IntStackColl_1e, infile_1e);

  // 13) SeOld_Pa234m
  Double_t ScaleFactor_SeOld_Pa234m = Act_SeOld_Pa234m*AccptRunTime/Denom_SeOld_Pa234m;
  addChannelToStacks_1e("SeOld_Pa234m", ScaleFactor_SeOld_Pa234m, FillColor_SeOld_Pa234m, IntStackColl_1e, infile_1e);

  // 14) SeNew_K40
  Double_t ScaleFactor_SeNew_K40 = Act_SeNew_K40*AccptRunTime/Denom_SeNew_K40;
  addChannelToStacks_1e("SeNew_K40", ScaleFactor_SeNew_K40, FillColor_SeNew_K40, IntStackColl_1e, infile_1e);

  // 15) SeOld_K40
  Double_t ScaleFactor_SeOld_K40 = Act_SeOld_K40*AccptRunTime/Denom_SeOld_K40;
  addChannelToStacks_1e("SeOld_K40", ScaleFactor_SeOld_K40, FillColor_SeOld_K40, IntStackColl_1e, infile_1e);

  // ADD SIGNAL
  Double_t Act_2b2n_SeNew   = Activities_Sig[0];
  Double_t Act_2b2n_SeOld   = Activities_Sig[0];
  Double_t Denom_2b2n_SeNew = Denominators_Sig[0];
  Double_t Denom_2b2n_SeOld = Denominators_Sig[0];
  Int_t    FillColor_2b2n = kRed;

  // Create collection of histogram stacks
  SigStackColl_1e[0] = new THStack("h_1e_P1_SeOld","Electron Energy");
  SigStackColl_1e[1] = new THStack("h_1e_P1_SeNew","Electron Energy");
  SigStackColl_1e[2] = new THStack("h_1e_P1_Strip","Electron Energy");
  SigStackColl_1e[3] = new THStack("h_1e_P2_SeOld","Electron Energy");
  SigStackColl_1e[4] = new THStack("h_1e_P2_SeNew","Electron Energy");
  SigStackColl_1e[5] = new THStack("h_1e_P2_Strip","Electron Energy");

  // 0) 2b2n - SeNew
  Double_t ScaleFactor_2b2n_SeNew = Act_2b2n_SeNew*AccptRunTime/Denom_2b2n_SeNew;
  addChannelToStacks_1e("2b2n_SeNew", ScaleFactor_2b2n_SeNew, FillColor_2b2n, SigStackColl_1e, infile_1e);

  // 1) 2b2n - SeOld
  Double_t ScaleFactor_2b2n_SeOld = Act_2b2n_SeOld*AccptRunTime/Denom_2b2n_SeOld;
  addChannelToStacks_1e("2b2n_SeOld", ScaleFactor_2b2n_SeOld, FillColor_2b2n, SigStackColl_1e, infile_1e);

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
  // 16) Air_Tl208

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
  StackColl_1e[0] = new THStack("h_1e_P1_SeOld","Electron Energy");
  StackColl_1e[1] = new THStack("h_1e_P1_SeNew","Electron Energy");
  StackColl_1e[2] = new THStack("h_1e_P1_Strip","Electron Energy");
  StackColl_1e[3] = new THStack("h_1e_P2_SeOld","Electron Energy");
  StackColl_1e[4] = new THStack("h_1e_P2_SeNew","Electron Energy");
  StackColl_1e[5] = new THStack("h_1e_P2_Strip","Electron Energy");

  // 0) K40 External Backgrounds
  for(int j = 0; j < 6; j++){
    TH1D* hK40 = (TH1D*)ExtStackColl_1e[j]->GetStack()->At(0)->Clone("hK40");
    hK40->Add((TH1D*)ExtStackColl_1e[j]->GetStack()->At(8), 1);
    hK40->Add((TH1D*)ExtStackColl_1e[j]->GetStack()->At(7),-1);
    hK40->Add((TH1D*)ExtStackColl_1e[j]->GetStack()->At(17),1);
    hK40->Add((TH1D*)ExtStackColl_1e[j]->GetStack()->At(14),-1);
    hK40->SetFillColor(kSpring-6);
    StackColl_1e[j]->Add(hK40);
  }

  // 1) Bi214 External Backgrounds (include SScin here too)
  for(int j = 0; j < 6; j++){
    TH1D* hBi214 = (TH1D*)ExtStackColl_1e[j]->GetStack()->At(1)->Clone("hBi214");
    hBi214->Add((TH1D*)ExtStackColl_1e[j]->GetStack()->At(0),-1);
    hBi214->Add((TH1D*)ExtStackColl_1e[j]->GetStack()->At(4), 1);
    hBi214->Add((TH1D*)ExtStackColl_1e[j]->GetStack()->At(3),-1);
    hBi214->Add((TH1D*)ExtStackColl_1e[j]->GetStack()->At(9),1);
    hBi214->Add((TH1D*)ExtStackColl_1e[j]->GetStack()->At(8),-1);
    TH1D* hSScin = (TH1D*)RadStackColl_1e[j]->GetStack()->At(12)->Clone("hSScin");
    hSScin->Add((TH1D*)RadStackColl_1e[j]->GetStack()->At(10), -1);
    hBi214->Add(hSScin);
    hBi214->SetFillColor(kSpring-1);
    StackColl_1e[j]->Add(hBi214);
  }

  // 2) Tl208 & Ac228 External Backgrounds
  for(int j = 0; j < 6; j++){
    TH1D* hTl208 = (TH1D*)ExtStackColl_1e[j]->GetStack()->At(3)->Clone("hTl208");
    hTl208->Add((TH1D*)ExtStackColl_1e[j]->GetStack()->At(1),-1);
    hTl208->Add((TH1D*)ExtStackColl_1e[j]->GetStack()->At(6), 1);
    hTl208->Add((TH1D*)ExtStackColl_1e[j]->GetStack()->At(4),-1);
    hTl208->Add((TH1D*)ExtStackColl_1e[j]->GetStack()->At(11),1);
    hTl208->Add((TH1D*)ExtStackColl_1e[j]->GetStack()->At(9),-1);
    hTl208->SetFillColor(kSpring-3);
    StackColl_1e[j]->Add(hTl208);
  }

  // 3) Co60 External Backgrounds
  for(int j = 0; j < 6; j++){
    TH1D* hCo60 = (TH1D*)ExtStackColl_1e[j]->GetStack()->At(7)->Clone("hCo60");
    hCo60->Add((TH1D*)ExtStackColl_1e[j]->GetStack()->At(6),-1);
    hCo60->Add((TH1D*)ExtStackColl_1e[j]->GetStack()->At(14), 1);
    hCo60->Add((TH1D*)ExtStackColl_1e[j]->GetStack()->At(11),-1);
    hCo60->SetFillColor(kSpring-4);
    StackColl_1e[j]->Add(hCo60);
  }

  // 4) Pa234m_SScin External Backgrounds
  for(int j = 0; j < 6; j++){
    TH1D* hSScin_Pa234m = (TH1D*)ExtStackColl_1e[j]->GetStack()->At(18)->Clone("hSScin_Pa234m");
    hSScin_Pa234m->Add((TH1D*)ExtStackColl_1e[j]->GetStack()->At(17),-1);
    hSScin_Pa234m->SetFillColor(kSpring-5);
    StackColl_1e[j]->Add(hSScin_Pa234m);
  }

  // 5) MuMetal_g1000 External Backgrounds
  for(int j = 0; j < 6; j++){
    TH1D* hMuMetal_g100 = (TH1D*)ExtStackColl_1e[j]->GetStack()->At(19)->Clone("hMuMetal_g100");
    hMuMetal_g100->Add((TH1D*)ExtStackColl_1e[j]->GetStack()->At(18),-1);
    hMuMetal_g100->SetFillColor(kSpring-7);
    StackColl_1e[j]->Add(hMuMetal_g100);
  }

  // 6) Neutrons External Backgrounds
  for(int j = 0; j < 6; j++){
    TH1D* hNeutrons = (TH1D*)ExtStackColl_1e[j]->GetStack()->At(20)->Clone("hNeutrons");
    hNeutrons->Add((TH1D*)ExtStackColl_1e[j]->GetStack()->At(19),-1);
    hNeutrons->SetFillColor(kSpring-8);
    StackColl_1e[j]->Add(hNeutrons);
  }

  // 7)  Bi214 LSM Air
  for(int j = 0; j < 6; j++){
    TH1D* hAir = (TH1D*)RadStackColl_1e[j]->GetStack()->At(15)->Clone("hAir");
    hAir->Add((TH1D*)RadStackColl_1e[j]->GetStack()->At(13), -1);
    hAir->SetFillColor(kPink-1);
    StackColl_1e[j]->Add(hAir);
  }

  // 8)  Tl208 LSM Air
  for(int j = 0; j < 6; j++){
    TH1D* hAir = (TH1D*)RadStackColl_1e[j]->GetStack()->At(16)->Clone("hAir");
    hAir->Add((TH1D*)RadStackColl_1e[j]->GetStack()->At(15), -1);
    hAir->SetFillColor(kPink-2);
    StackColl_1e[j]->Add(hAir);
  }

  // 9) 1e1a Backgrounds
  for(int j = 0; j < 6; j++){
    TH1D* hSWire = (TH1D*)RadStackColl_1e[j]->GetStack()->At(1)->Clone("hSWire");

    TH1D* hSFoil = (TH1D*)RadStackColl_1e[j]->GetStack()->At(7)->Clone("hSFoil");
    hSFoil->Add((TH1D*)RadStackColl_1e[j]->GetStack()->At(3), -1);

    TH1D* hInternals = (TH1D*)IntStackColl_1e[j]->GetStack()->At(5)->Clone("hInternals");

    hSWire->Add(hInternals);
    hSWire->Add(hSFoil);
    hSWire->SetFillColor(kRed);
    StackColl_1e[j]->Add(hSWire);
  }

  // 10) 1e2g samples
  for(int j = 0; j < 6; j++){
    TH1D* hSWire = (TH1D*)RadStackColl_1e[j]->GetStack()->At(3)->Clone("hSWire");
    hSWire->Add((TH1D*)RadStackColl_1e[j]->GetStack()->At(2), -1);
    TH1D* hInternals = (TH1D*)IntStackColl_1e[j]->GetStack()->At(11)->Clone("hInternals");
    hInternals->Add((TH1D*)IntStackColl_1e[j]->GetStack()->At(5), -1);
    hSWire->Add(hInternals);
    hSWire->SetFillColor(kBlue);
    StackColl_1e[j]->Add(hSWire);
  }

  // 11) Bi210 SScin
  for(int j = 0; j < 6; j++){
    TH1D* hSScin = (TH1D*)RadStackColl_1e[j]->GetStack()->At(13)->Clone("hSScin");
    hSScin->Add((TH1D*)RadStackColl_1e[j]->GetStack()->At(12), -1);
    hSScin->SetFillColor(kOrange-1);
    StackColl_1e[j]->Add(hSScin);
  }

  // 12) SWire-B210
  for(int j = 0; j < 6; j++){
    TH1D* hSWire = (TH1D*)RadStackColl_1e[j]->GetStack()->At(2)->Clone("hSWire");
    hSWire->Add((TH1D*)RadStackColl_1e[j]->GetStack()->At(1), -1);
    hSWire->SetFillColor(kOrange);
    StackColl_1e[j]->Add(hSWire);
  }

  // 13) Bi210 SFoil SeNew
  for(int j = 0; j < 6; j++){
    TH1D* hSFoil = (TH1D*)RadStackColl_1e[j]->GetStack()->At(8)->Clone("hSFoil");
    hSFoil->Add((TH1D*)RadStackColl_1e[j]->GetStack()->At(7), -1);
    hSFoil->SetFillColor(kYellow);
    StackColl_1e[j]->Add(hSFoil);
  }

  // 14) Bi210 SFoil SeOld
  for(int j = 0; j < 6; j++){
    TH1D* hSFoil = (TH1D*)RadStackColl_1e[j]->GetStack()->At(9)->Clone("hSFoil");
    hSFoil->Add((TH1D*)RadStackColl_1e[j]->GetStack()->At(8), -1);
    hSFoil->SetFillColor(kYellow);
    StackColl_1e[j]->Add(hSFoil);
  }

  // 15) Bi210 SFoil Strip
  for(int j = 0; j < 6; j++){
    TH1D* hSFoil = (TH1D*)RadStackColl_1e[j]->GetStack()->At(10)->Clone("hSFoil");
    hSFoil->Add((TH1D*)RadStackColl_1e[j]->GetStack()->At(9), -1);
    hSFoil->SetFillColor(kYellow);
    StackColl_1e[j]->Add(hSFoil);
  }
 
  // 16) Pa234m - SeNew
  for(int j = 0; j < 6; j++){
    TH1D* hPa234m = (TH1D*)IntStackColl_1e[j]->GetStack()->At(12)->Clone("hPa234m");
    hPa234m->Add((TH1D*)IntStackColl_1e[j]->GetStack()->At(11), -1);
    hPa234m->SetFillColor(kAzure-2);
    StackColl_1e[j]->Add(hPa234m);
  }

  // 17) Pa234m - SeOld
  for(int j = 0; j < 6; j++){
    TH1D* hPa234m = (TH1D*)IntStackColl_1e[j]->GetStack()->At(13)->Clone("hPa234m");
    hPa234m->Add((TH1D*)IntStackColl_1e[j]->GetStack()->At(12), -1);
    hPa234m->SetFillColor(kAzure-2);
    StackColl_1e[j]->Add(hPa234m);
  }

  // 18) K40 - SeNew
  for(int j = 0; j < 6; j++){
    TH1D* hK40 = (TH1D*)IntStackColl_1e[j]->GetStack()->At(14)->Clone("hK40");
    hK40->Add((TH1D*)IntStackColl_1e[j]->GetStack()->At(13), -1);
    hK40->SetFillColor(kOrange+10);
    StackColl_1e[j]->Add(hK40);
  }

  // 19) K40 - SeOld
  for(int j = 0; j < 6; j++){
    TH1D* hK40 = (TH1D*)IntStackColl_1e[j]->GetStack()->At(15)->Clone("hK40");
    hK40->Add((TH1D*)IntStackColl_1e[j]->GetStack()->At(14), -1);
    hK40->SetFillColor(kOrange+10);
    StackColl_1e[j]->Add(hK40);
  }

  // 20) 2b2n - SeOld & SeNew
  for(int j = 0; j < 6; j++){
    TH1D* h2b2n = (TH1D*)SigStackColl_1e[j]->GetStack()->Last()->Clone("h2b2n");
    h2b2n->SetFillColor(kRed);
    StackColl_1e[j]->Add(h2b2n);
  }

  // Create legend to put on plots
  string LegIsotopes_SeOld_P1[16];
  string LegEntries_SeOld_P1[16];
  string LegIsotopes_SeOld_P2[16];
  string LegEntries_SeOld_P2[16];
  string LegIsotopes_SeNew_P1[16];
  string LegEntries_SeNew_P1[16];
  string LegIsotopes_SeNew_P2[16];
  string LegEntries_SeNew_P2[16];
  string LegIsotopes_Strip_P1[16];
  string LegEntries_Strip_P1[16];
  string LegIsotopes_Strip_P2[16];
  string LegEntries_Strip_P2[16];
  char buffer[200];

  LegIsotopes_SeOld_P1[0] = "^{40}K Externals";
  sprintf (buffer, " ");
  LegEntries_SeOld_P1[0] = buffer;
  LegIsotopes_SeOld_P1[1] = "^{214}Bi Externals";
  sprintf (buffer, " ");
  LegEntries_SeOld_P1[1] = buffer;
  LegIsotopes_SeOld_P1[2] = "^{208}Tl Externals";
  sprintf (buffer, " ");
  LegEntries_SeOld_P1[2] = buffer;
  LegIsotopes_SeOld_P1[3] = "^{60}Co Externals";
  sprintf (buffer, " ");
  LegEntries_SeOld_P1[3] = buffer;
  LegIsotopes_SeOld_P1[4] = "^{234m}Pa SScin";
  if(Act_SScin_Pa234m_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_SScin_Pa234m, Act_SScin_Pa234m_Err);}
  else{sprintf (buffer, "A = %.1f Bq", Act_SScin_Pa234m);}
  LegEntries_SeOld_P1[4] = buffer;
  LegIsotopes_SeOld_P1[5] = "1 MeV #gamma (MuMetal)";
  if(Act_MuMetal_g1000_P1_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_MuMetal_g1000_P1, Act_MuMetal_g1000_P1_Err);}
  else{sprintf (buffer, "A = %.1f Bq", Act_MuMetal_g1000_P1);}
  LegEntries_SeOld_P1[5] = buffer;
  LegIsotopes_SeOld_P1[6] = "Neutrons";
  if(Act_Neutrons_P1_Err > 0){sprintf (buffer, "S = %.1f #pm %.1f x10^{-3}", 1000*Act_Neutrons_P1, 1000*Act_Neutrons_P1_Err);}
  else{sprintf (buffer, "S = %.1f x10^{-3}", 1000*Act_Neutrons_P1);}
  LegEntries_SeOld_P1[6] = buffer;
  LegIsotopes_SeOld_P1[7] = "^{214}Bi LSM Air P1";
  if(Act_Air_Bi214_P1_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_Air_Bi214_P1, Act_Air_Bi214_P1_Err);}
  else{sprintf (buffer, "A = %.1f Bq", Act_Air_Bi214_P1);}
  LegEntries_SeOld_P1[7] = buffer;
  LegIsotopes_SeOld_P1[8] = "^{208}Tl LSM Air P1";
  if(Act_Air_Tl208_P1_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_Air_Tl208_P1, Act_Air_Tl208_P1_Err);}
  else{sprintf (buffer, "A = %.1f Bq", Act_Air_Tl208_P1);}
  LegEntries_SeOld_P1[8] = buffer;
  LegIsotopes_SeOld_P1[9] = "1e1#alpha";
  sprintf(buffer, " ");
  LegEntries_SeOld_P1[9] = buffer;
  LegIsotopes_SeOld_P1[10] = "1e2#gamma";
  sprintf (buffer, " ");
  LegEntries_SeOld_P1[10] = buffer;
  LegIsotopes_SeOld_P1[11] = "^{210}Bi SScin";
  if(Act_SScin_Bi210_Err > 0){sprintf (buffer, "A = %.2f #pm %.2f Bq", Act_SScin_Bi210, Act_SScin_Bi210_Err);}
  else{sprintf (buffer, "A = %.2f Bq", Act_SScin_Bi210);}
  LegEntries_SeOld_P1[11] = buffer;
  LegIsotopes_SeOld_P1[12] = "^{210}Bi SWire";
  if(Act_SWire_Bi210_Err > 0){sprintf (buffer, "A = %.2f #pm %.2f Bq", Act_SWire_Bi210, Act_SWire_Bi210_Err);}
  else{sprintf (buffer, "A = %.2f Bq", Act_SWire_Bi210);}
  LegEntries_SeOld_P1[12] = buffer;
  LegIsotopes_SeOld_P1[13] = "^{210}Bi SFoil";
  if(Act_SFoil_SeOld_Bi210_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f mBq", 1000*Act_SFoil_SeOld_Bi210, 1000*Act_SFoil_SeOld_Bi210_Err);}
  else{sprintf (buffer, "A = %.2f mBq", 1000*Act_SFoil_SeOld_Bi210);}
  LegEntries_SeOld_P1[13] = buffer;
  LegIsotopes_SeOld_P1[14] = "^{234m}Pa SeOld";
  if(Act_SeOld_Pa234m_Err > 0){sprintf (buffer, "A = %.2f #pm %.2f mBq", 1000*Act_SeOld_Pa234m, 1000*Act_SeOld_Pa234m_Err);}
  else{sprintf (buffer, "A = %.2f mBq", 1000*Act_SeOld_Pa234m);}
  LegEntries_SeOld_P1[14] = buffer;
  LegIsotopes_SeOld_P1[15] = "^{40}K SeOld";
  if(Act_SeOld_K40_Err > 0){sprintf (buffer, "A = %.2f #pm %.2f mBq", 1000*Act_SeOld_K40, 1000*Act_SeOld_K40_Err);}
  else{sprintf (buffer, "A = %.2f mBq", 1000*Act_SeOld_K40);}
  LegEntries_SeOld_P1[15] = buffer;

  LegIsotopes_SeNew_P1[0] = "^{40}K Externals";
  sprintf (buffer, " ");
  LegEntries_SeNew_P1[0] = buffer;
  LegIsotopes_SeNew_P1[1] = "^{214}Bi Externals";
  sprintf (buffer, " ");
  LegEntries_SeNew_P1[1] = buffer;
  LegIsotopes_SeNew_P1[2] = "^{208}Tl Externals";
  sprintf (buffer, " ");
  LegEntries_SeNew_P1[2] = buffer;
  LegIsotopes_SeNew_P1[3] = "^{60}Co Externals";
  sprintf (buffer, " ");
  LegEntries_SeNew_P1[3] = buffer;
  LegIsotopes_SeNew_P1[4] = "^{234m}Pa SScin";
  if(Act_SScin_Pa234m_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_SScin_Pa234m, Act_SScin_Pa234m_Err);}
  else{sprintf (buffer, "A = %.1f Bq", Act_SScin_Pa234m);}
  LegEntries_SeNew_P1[4] = buffer;
  LegIsotopes_SeNew_P1[5] = "1 MeV #gamma (MuMetal)";
  if(Act_MuMetal_g1000_P1_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_MuMetal_g1000_P1, Act_MuMetal_g1000_P1_Err);}
  else{sprintf (buffer, "A = %.1f Bq", Act_MuMetal_g1000_P1);}
  LegEntries_SeNew_P1[5] = buffer;
  LegIsotopes_SeNew_P1[6] = "Neutrons";
  if(Act_Neutrons_P1_Err > 0){sprintf (buffer, "S = %.1f #pm %.1f x10^{-3}", 1000*Act_Neutrons_P1, 1000*Act_Neutrons_P1_Err);}
  else{sprintf (buffer, "S = %.1f x10^{-3}", 1000*Act_Neutrons_P1);}
  LegEntries_SeNew_P1[6] = buffer;
  LegIsotopes_SeNew_P1[7] = "^{214}Bi LSM Air P1";
  if(Act_Air_Bi214_P1_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_Air_Bi214_P1, Act_Air_Bi214_P1_Err);}
  else{sprintf (buffer, "A = %.1f Bq", Act_Air_Bi214_P1);}
  LegEntries_SeNew_P1[7] = buffer;
  LegIsotopes_SeNew_P1[8] = "^{208}Tl LSM Air P1";
  if(Act_Air_Tl208_P1_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_Air_Tl208_P1, Act_Air_Tl208_P1_Err);}
  else{sprintf (buffer, "A = %.1f Bq", Act_Air_Tl208_P1);}
  LegEntries_SeNew_P1[8] = buffer;
  LegIsotopes_SeNew_P1[9] = "1e1#alpha";
  sprintf(buffer, " ");
  LegEntries_SeNew_P1[9] = buffer;
  LegIsotopes_SeNew_P1[10] = "1e2#gamma";
  sprintf (buffer, " ");
  LegEntries_SeNew_P1[10] = buffer;
  LegIsotopes_SeNew_P1[11] = "^{210}Bi SScin";
  if(Act_SScin_Bi210_Err > 0){sprintf (buffer, "A = %.2f #pm %.2f Bq", Act_SScin_Bi210, Act_SScin_Bi210_Err);}
  else{sprintf (buffer, "A = %.2f Bq", Act_SScin_Bi210);}
  LegEntries_SeNew_P1[11] = buffer;
  LegIsotopes_SeNew_P1[12] = "^{210}Bi SWire";
  if(Act_SWire_Bi210_Err > 0){sprintf (buffer, "A = %.2f #pm %.2f Bq", Act_SWire_Bi210, Act_SWire_Bi210_Err);}
  else{sprintf (buffer, "A = %.2f Bq", Act_SWire_Bi210);}
  LegEntries_SeNew_P1[12] = buffer;
  LegIsotopes_SeNew_P1[13] = "^{210}Bi SFoil";
  if(Act_SFoil_SeNew_Bi210_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f mBq", 1000*Act_SFoil_SeNew_Bi210, 1000*Act_SFoil_SeNew_Bi210_Err);}
  else{sprintf (buffer, "A = %.2f mBq", 1000*Act_SFoil_SeNew_Bi210);}
  LegEntries_SeNew_P1[13] = buffer;
  LegIsotopes_SeNew_P1[14] = "^{234m}Pa SeNew";
  if(Act_SeNew_Pa234m_Err > 0){sprintf (buffer, "A = %.2f #pm %.2f mBq", 1000*Act_SeNew_Pa234m, 1000*Act_SeNew_Pa234m_Err);}
  else{sprintf (buffer, "A = %.2f mBq", 1000*Act_SeNew_Pa234m);}
  LegEntries_SeNew_P1[14] = buffer;
  LegIsotopes_SeNew_P1[15] = "^{40}K SeNew";
  if(Act_SeNew_K40_Err > 0){sprintf (buffer, "A = %.2f #pm %.2f mBq", 1000*Act_SeNew_K40, 1000*Act_SeNew_K40_Err);}
  else{sprintf (buffer, "A = %.2f mBq", 1000*Act_SeNew_K40);}
  LegEntries_SeNew_P1[15] = buffer;

  LegIsotopes_Strip_P1[0] = "^{40}K Externals";
  sprintf (buffer, " ");
  LegEntries_Strip_P1[0] = buffer;
  LegIsotopes_Strip_P1[1] = "^{214}Bi Externals";
  sprintf (buffer, " ");
  LegEntries_Strip_P1[1] = buffer;
  LegIsotopes_Strip_P1[2] = "^{208}Tl Externals";
  sprintf (buffer, " ");
  LegEntries_Strip_P1[2] = buffer;
  LegIsotopes_Strip_P1[3] = "^{60}Co Externals";
  sprintf (buffer, " ");
  LegEntries_Strip_P1[3] = buffer;
  LegIsotopes_Strip_P1[4] = "^{234m}Pa SScin";
  if(Act_SScin_Pa234m_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_SScin_Pa234m, Act_SScin_Pa234m_Err);}
  else{sprintf (buffer, "A = %.1f Bq", Act_SScin_Pa234m);}
  LegEntries_Strip_P1[4] = buffer;
  LegIsotopes_Strip_P1[5] = "1 MeV #gamma (MuMetal)";
  if(Act_MuMetal_g1000_P1_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_MuMetal_g1000_P1, Act_MuMetal_g1000_P1_Err);}
  else{sprintf (buffer, "A = %.1f Bq", Act_MuMetal_g1000_P1);}
  LegEntries_Strip_P1[5] = buffer;
  LegIsotopes_Strip_P1[6] = "Neutrons";
  if(Act_Neutrons_P1_Err > 0){sprintf (buffer, "S = %.1f #pm %.1f x10^{-3}", 1000*Act_Neutrons_P1, 1000*Act_Neutrons_P1_Err);}
  else{sprintf (buffer, "S = %.1f x10^{-3}", 1000*Act_Neutrons_P1);}
  LegEntries_Strip_P1[6] = buffer;
  LegIsotopes_Strip_P1[7] = "^{214}Bi LSM Air P1";
  if(Act_Air_Bi214_P1_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_Air_Bi214_P1, Act_Air_Bi214_P1_Err);}
  else{sprintf (buffer, "A = %.1f Bq", Act_Air_Bi214_P1);}
  LegEntries_Strip_P1[7] = buffer;
  LegIsotopes_Strip_P1[8] = "^{208}Tl LSM Air P1";
  if(Act_Air_Tl208_P1_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_Air_Tl208_P1, Act_Air_Tl208_P1_Err);}
  else{sprintf (buffer, "A = %.1f Bq", Act_Air_Tl208_P1);}
  LegEntries_Strip_P1[8] = buffer;
  LegIsotopes_Strip_P1[9] = "1e1#alpha";
  sprintf(buffer, " ");
  LegEntries_Strip_P1[9] = buffer;
  LegIsotopes_Strip_P1[10] = "1e2#gamma";
  sprintf (buffer, " ");
  LegEntries_Strip_P1[10] = buffer;
  LegIsotopes_Strip_P1[11] = "^{210}Bi SScin";
  if(Act_SScin_Bi210_Err > 0){sprintf (buffer, "A = %.2f #pm %.2f Bq", Act_SScin_Bi210, Act_SScin_Bi210_Err);}
  else{sprintf (buffer, "A = %.2f Bq", Act_SScin_Bi210);}
  LegEntries_Strip_P1[11] = buffer;
  LegIsotopes_Strip_P1[12] = "^{210}Bi SWire";
  if(Act_SWire_Bi210_Err > 0){sprintf (buffer, "A = %.2f #pm %.2f Bq", Act_SWire_Bi210, Act_SWire_Bi210_Err);}
  else{sprintf (buffer, "A = %.2f Bq", Act_SWire_Bi210);}
  LegEntries_Strip_P1[12] = buffer;
  LegIsotopes_Strip_P1[13] = "^{210}Bi SFoil";
  if(Act_SFoil_Strip_Bi210_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f mBq", 1000*Act_SFoil_Strip_Bi210, 1000*Act_SFoil_Strip_Bi210_Err);}
  else{sprintf (buffer, "A = %.2f mBq", 1000*Act_SFoil_Strip_Bi210);}
  LegEntries_Strip_P1[13] = buffer;
  LegIsotopes_Strip_P1[14] = "^{234m}Pa SeNew";
  if(Act_SeNew_Pa234m_Err > 0){sprintf (buffer, "A = %.2f #pm %.2f mBq", 1000*Act_SeNew_Pa234m, 1000*Act_SeNew_Pa234m_Err);}
  else{sprintf (buffer, "A = %.2f mBq", 1000*Act_SeNew_Pa234m);}
  LegEntries_Strip_P1[14] = buffer;
  LegIsotopes_Strip_P1[15] = "^{40}K SeNew";
  if(Act_SeNew_K40_Err > 0){sprintf (buffer, "A = %.2f #pm %.2f mBq", 1000*Act_SeNew_K40, 1000*Act_SeNew_K40_Err);}
  else{sprintf (buffer, "A = %.2f mBq", 1000*Act_SeNew_K40);}
  LegEntries_Strip_P1[15] = buffer;

  LegIsotopes_SeOld_P2[0] = "^{40}K Externals";
  sprintf (buffer, " ");
  LegEntries_SeOld_P2[0] = buffer;
  LegIsotopes_SeOld_P2[1] = "^{214}Bi Externals";
  sprintf (buffer, " ");
  LegEntries_SeOld_P2[1] = buffer;
  LegIsotopes_SeOld_P2[2] = "^{208}Tl Externals";
  sprintf (buffer, " ");
  LegEntries_SeOld_P2[2] = buffer;
  LegIsotopes_SeOld_P2[3] = "^{60}Co Externals";
  sprintf (buffer, " ");
  LegEntries_SeOld_P2[3] = buffer;
  LegIsotopes_SeOld_P2[4] = "^{234m}Pa SScin";
  if(Act_SScin_Pa234m_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_SScin_Pa234m, Act_SScin_Pa234m_Err);}
  else{sprintf (buffer, "A = %.1f Bq", Act_SScin_Pa234m);}
  LegEntries_SeOld_P2[4] = buffer;
  LegIsotopes_SeOld_P2[5] = "1 MeV #gamma (MuMetal)";
  if(Act_MuMetal_g1000_P2_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_MuMetal_g1000_P2, Act_MuMetal_g1000_P2_Err);}
  else{sprintf (buffer, "A = %.1f Bq", Act_MuMetal_g1000_P2);}
  LegEntries_SeOld_P2[5] = buffer;
  LegIsotopes_SeOld_P2[6] = "Neutrons";
  if(Act_Neutrons_P2_Err > 0){sprintf (buffer, "S = %.1f #pm %.1f x10^{-3}", 1000*Act_Neutrons_P2, 1000*Act_Neutrons_P2_Err);}
  else{sprintf (buffer, "S = %.1f x10^{-3}", 1000*Act_Neutrons_P2);}
  LegEntries_SeOld_P2[6] = buffer;
  LegIsotopes_SeOld_P2[7] = "^{214}Bi LSM Air P2";
  if(Act_Air_Bi214_P2_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_Air_Bi214_P2, Act_Air_Bi214_P2_Err);}
  else{sprintf (buffer, "A = %.1f Bq", Act_Air_Bi214_P2);}
  LegEntries_SeOld_P2[7] = buffer;
  LegIsotopes_SeOld_P2[8] = "^{208}Tl LSM Air P2";
  if(Act_Air_Tl208_P2_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_Air_Tl208_P2, Act_Air_Tl208_P2_Err);}
  else{sprintf (buffer, "A = %.1f Bq", Act_Air_Tl208_P2);}
  LegEntries_SeOld_P2[8] = buffer;
  LegIsotopes_SeOld_P2[9] = "1e1#alpha";
  sprintf(buffer, " ");
  LegEntries_SeOld_P2[9] = buffer;
  LegIsotopes_SeOld_P2[10] = "1e2#gamma";
  sprintf (buffer, " ");
  LegEntries_SeOld_P2[10] = buffer;
  LegIsotopes_SeOld_P2[11] = "^{210}Bi SScin";
  if(Act_SScin_Bi210_Err > 0){sprintf (buffer, "A = %.2f #pm %.2f Bq", Act_SScin_Bi210, Act_SScin_Bi210_Err);}
  else{sprintf (buffer, "A = %.2f Bq", Act_SScin_Bi210);}
  LegEntries_SeOld_P2[11] = buffer;
  LegIsotopes_SeOld_P2[12] = "^{210}Bi SWire";
  if(Act_SWire_Bi210_Err > 0){sprintf (buffer, "A = %.2f #pm %.2f Bq", Act_SWire_Bi210, Act_SWire_Bi210_Err);}
  else{sprintf (buffer, "A = %.2f Bq", Act_SWire_Bi210);}
  LegEntries_SeOld_P2[12] = buffer;
  LegIsotopes_SeOld_P2[13] = "^{210}Bi SFoil";
  if(Act_SFoil_SeOld_Bi210_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f mBq", 1000*Act_SFoil_SeOld_Bi210, 1000*Act_SFoil_SeOld_Bi210_Err);}
  else{sprintf (buffer, "A = %.2f mBq", 1000*Act_SFoil_SeOld_Bi210);}
  LegEntries_SeOld_P2[13] = buffer;
  LegIsotopes_SeOld_P2[14] = "^{234m}Pa SeOld";
  if(Act_SeOld_Pa234m_Err > 0){sprintf (buffer, "A = %.2f #pm %.2f mBq", 1000*Act_SeOld_Pa234m, 1000*Act_SeOld_Pa234m_Err);}
  else{sprintf (buffer, "A = %.2f mBq", 1000*Act_SeOld_Pa234m);}
  LegEntries_SeOld_P2[14] = buffer;
  LegIsotopes_SeOld_P2[15] = "^{40}K SeOld";
  if(Act_SeOld_K40_Err > 0){sprintf (buffer, "A = %.2f #pm %.2f mBq", 1000*Act_SeOld_K40, 1000*Act_SeOld_K40_Err);}
  else{sprintf (buffer, "A = %.2f mBq", 1000*Act_SeOld_K40);}
  LegEntries_SeOld_P2[15] = buffer;

  LegIsotopes_SeNew_P2[0] = "^{40}K Externals";
  sprintf (buffer, " ");
  LegEntries_SeNew_P2[0] = buffer;
  LegIsotopes_SeNew_P2[1] = "^{214}Bi Externals";
  sprintf (buffer, " ");
  LegEntries_SeNew_P2[1] = buffer;
  LegIsotopes_SeNew_P2[2] = "^{208}Tl Externals";
  sprintf (buffer, " ");
  LegEntries_SeNew_P2[2] = buffer;
  LegIsotopes_SeNew_P2[3] = "^{60}Co Externals";
  sprintf (buffer, " ");
  LegEntries_SeNew_P2[3] = buffer;
  LegIsotopes_SeNew_P2[4] = "^{234m}Pa SScin";
  if(Act_SScin_Pa234m_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_SScin_Pa234m, Act_SScin_Pa234m_Err);}
  else{sprintf (buffer, "A = %.1f Bq", Act_SScin_Pa234m);}
  LegEntries_SeNew_P2[4] = buffer;
  LegIsotopes_SeNew_P2[5] = "1 MeV #gamma (MuMetal)";
  if(Act_MuMetal_g1000_P2_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_MuMetal_g1000_P2, Act_MuMetal_g1000_P2_Err);}
  else{sprintf (buffer, "A = %.1f Bq", Act_MuMetal_g1000_P2);}
  LegEntries_SeNew_P2[5] = buffer;
  LegIsotopes_SeNew_P2[6] = "Neutrons";
  if(Act_Neutrons_P2_Err > 0){sprintf (buffer, "S = %.1f #pm %.1f x10^{-3}", 1000*Act_Neutrons_P2, 1000*Act_Neutrons_P2_Err);}
  else{sprintf (buffer, "S = %.1f x10^{-3}", 1000*Act_Neutrons_P2);}
  LegEntries_SeNew_P2[6] = buffer;
  LegIsotopes_SeNew_P2[7] = "^{214}Bi LSM Air P2";
  if(Act_Air_Bi214_P2_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_Air_Bi214_P2, Act_Air_Bi214_P2_Err);}
  else{sprintf (buffer, "A = %.1f Bq", Act_Air_Bi214_P2);}
  LegEntries_SeNew_P2[7] = buffer;
  LegIsotopes_SeNew_P2[8] = "^{208}Tl LSM Air P2";
  if(Act_Air_Tl208_P2_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_Air_Tl208_P2, Act_Air_Tl208_P2_Err);}
  else{sprintf (buffer, "A = %.1f Bq", Act_Air_Tl208_P2);}
  LegEntries_SeNew_P2[8] = buffer;
  LegIsotopes_SeNew_P2[9] = "1e1#alpha";
  sprintf(buffer, " ");
  LegEntries_SeNew_P2[9] = buffer;
  LegIsotopes_SeNew_P2[10] = "1e2#gamma";
  sprintf (buffer, " ");
  LegEntries_SeNew_P2[10] = buffer;
  LegIsotopes_SeNew_P2[11] = "^{210}Bi SScin";
  if(Act_SScin_Bi210_Err > 0){sprintf (buffer, "A = %.2f #pm %.2f Bq", Act_SScin_Bi210, Act_SScin_Bi210_Err);}
  else{sprintf (buffer, "A = %.2f Bq", Act_SScin_Bi210);}
  LegEntries_SeNew_P2[11] = buffer;
  LegIsotopes_SeNew_P2[12] = "^{210}Bi SWire";
  if(Act_SWire_Bi210_Err > 0){sprintf (buffer, "A = %.2f #pm %.2f Bq", Act_SWire_Bi210, Act_SWire_Bi210_Err);}
  else{sprintf (buffer, "A = %.2f Bq", Act_SWire_Bi210);}
  LegEntries_SeNew_P2[12] = buffer;
  LegIsotopes_SeNew_P2[13] = "^{210}Bi SFoil";
  if(Act_SFoil_SeNew_Bi210_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f mBq", 1000*Act_SFoil_SeNew_Bi210, 1000*Act_SFoil_SeNew_Bi210_Err);}
  else{sprintf (buffer, "A = %.2f mBq", 1000*Act_SFoil_SeNew_Bi210);}
  LegEntries_SeNew_P2[13] = buffer;
  LegIsotopes_SeNew_P2[14] = "^{234m}Pa SeNew";
  if(Act_SeNew_Pa234m_Err > 0){sprintf (buffer, "A = %.2f #pm %.2f mBq", 1000*Act_SeNew_Pa234m, 1000*Act_SeNew_Pa234m_Err);}
  else{sprintf (buffer, "A = %.2f mBq", 1000*Act_SeNew_Pa234m);}
  LegEntries_SeNew_P2[14] = buffer;
  LegIsotopes_SeNew_P2[15] = "^{40}K SeNew";
  if(Act_SeNew_K40_Err > 0){sprintf (buffer, "A = %.2f #pm %.2f mBq", 1000*Act_SeNew_K40, 1000*Act_SeNew_K40_Err);}
  else{sprintf (buffer, "A = %.2f mBq", 1000*Act_SeNew_K40);}
  LegEntries_SeNew_P2[15] = buffer;

  LegIsotopes_Strip_P2[0] = "^{40}K Externals";
  sprintf (buffer, " ");
  LegEntries_Strip_P2[0] = buffer;
  LegIsotopes_Strip_P2[1] = "^{214}Bi Externals";
  sprintf (buffer, " ");
  LegEntries_Strip_P2[1] = buffer;
  LegIsotopes_Strip_P2[2] = "^{208}Tl Externals";
  sprintf (buffer, " ");
  LegEntries_Strip_P2[2] = buffer;
  LegIsotopes_Strip_P2[3] = "^{60}Co Externals";
  sprintf (buffer, " ");
  LegEntries_Strip_P2[3] = buffer;
  LegIsotopes_Strip_P2[4] = "^{234m}Pa SScin";
  if(Act_SScin_Pa234m_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_SScin_Pa234m, Act_SScin_Pa234m_Err);}
  else{sprintf (buffer, "A = %.1f Bq", Act_SScin_Pa234m);}
  LegEntries_Strip_P2[4] = buffer;
  LegIsotopes_Strip_P2[5] = "1 MeV #gamma (MuMetal)";
  if(Act_MuMetal_g1000_P2_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_MuMetal_g1000_P2, Act_MuMetal_g1000_P2_Err);}
  else{sprintf (buffer, "A = %.1f Bq", Act_MuMetal_g1000_P2);}
  LegEntries_Strip_P2[5] = buffer;
  LegIsotopes_Strip_P2[6] = "Neutrons";
  if(Act_Neutrons_P2_Err > 0){sprintf (buffer, "S = %.1f #pm %.1f x10^{-3}", 1000*Act_Neutrons_P2, 1000*Act_Neutrons_P2_Err);}
  else{sprintf (buffer, "S = %.1f x10^{-3}", 1000*Act_Neutrons_P2);}
  LegEntries_Strip_P2[6] = buffer;
  LegIsotopes_Strip_P2[7] = "^{214}Bi LSM Air P2";
  if(Act_Air_Bi214_P2_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_Air_Bi214_P2, Act_Air_Bi214_P2_Err);}
  else{sprintf (buffer, "A = %.1f Bq", Act_Air_Bi214_P2);}
  LegEntries_Strip_P2[7] = buffer;
  LegIsotopes_Strip_P2[8] = "^{208}Tl LSM Air P2";
  if(Act_Air_Tl208_P2_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_Air_Tl208_P2, Act_Air_Tl208_P2_Err);}
  else{sprintf (buffer, "A = %.1f Bq", Act_Air_Tl208_P2);}
  LegEntries_Strip_P2[8] = buffer;
  LegIsotopes_Strip_P2[9] = "1e1#alpha";
  sprintf(buffer, " ");
  LegEntries_Strip_P2[9] = buffer;
  LegIsotopes_Strip_P2[10] = "1e2#gamma";
  sprintf (buffer, " ");
  LegEntries_Strip_P2[10] = buffer;
  LegIsotopes_Strip_P2[11] = "^{210}Bi SScin";
  if(Act_SScin_Bi210_Err > 0){sprintf (buffer, "A = %.2f #pm %.2f Bq", Act_SScin_Bi210, Act_SScin_Bi210_Err);}
  else{sprintf (buffer, "A = %.2f Bq", Act_SScin_Bi210);}
  LegEntries_Strip_P2[11] = buffer;
  LegIsotopes_Strip_P2[12] = "^{210}Bi SWire";
  if(Act_SWire_Bi210_Err > 0){sprintf (buffer, "A = %.2f #pm %.2f Bq", Act_SWire_Bi210, Act_SWire_Bi210_Err);}
  else{sprintf (buffer, "A = %.2f Bq", Act_SWire_Bi210);}
  LegEntries_Strip_P2[12] = buffer;
  LegIsotopes_Strip_P2[13] = "^{210}Bi SFoil";
  if(Act_SFoil_Strip_Bi210_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f mBq", 1000*Act_SFoil_Strip_Bi210, 1000*Act_SFoil_Strip_Bi210_Err);}
  else{sprintf (buffer, "A = %.2f mBq", 1000*Act_SFoil_Strip_Bi210);}
  LegEntries_Strip_P2[13] = buffer;
  LegIsotopes_Strip_P2[14] = "^{234m}Pa SeNew";
  if(Act_SeNew_Pa234m_Err > 0){sprintf (buffer, "A = %.2f #pm %.2f mBq", 1000*Act_SeNew_Pa234m, 1000*Act_SeNew_Pa234m_Err);}
  else{sprintf (buffer, "A = %.2f mBq", 1000*Act_SeNew_Pa234m);}
  LegEntries_Strip_P2[14] = buffer;
  LegIsotopes_Strip_P2[15] = "^{40}K SeNew";
  if(Act_SeNew_K40_Err > 0){sprintf (buffer, "A = %.2f #pm %.2f mBq", 1000*Act_SeNew_K40, 1000*Act_SeNew_K40_Err);}
  else{sprintf (buffer, "A = %.2f mBq", 1000*Act_SeNew_K40);}
  LegEntries_Strip_P2[15] = buffer;

  // Make legends
  for(int i = 0; i < 6; i++){
    Legend_1e[i] = new TLegend(0.540,0.4845,0.947,0.947);
    Legend_1e[i]->SetNColumns(2);
    Legend_1e[i]->SetColumnSeparation(-0.05);
    Legend_1e[i]->SetFillColor(0);
    Legend_1e[i]->SetLineColor(0);
    Legend_1e[i]->SetBorderSize(0);
    LegendLog_1e[i] = new TLegend(0.7199,0.4845,0.947,0.947);
    LegendLog_1e[i]->SetFillColor(0);
    LegendLog_1e[i]->SetLineColor(0);
    LegendLog_1e[i]->SetBorderSize(0);
  }

  char Num_Events[40];

  sprintf (Num_Events, "%d Events", (int) h_1e_Data_P1_SeOld->GetEntries());
  Legend_1e[0]->AddEntry(h_1e_Data_P1_SeOld, "Data", "lpe");
  Legend_1e[0]->AddEntry(h_1e_Data_P1_SeOld, Num_Events, "");
  LegendLog_1e[0]->AddEntry(h_1e_Data_P1_SeOld, "Data", "lpe");

  sprintf (Num_Events, "%d Events", (int) h_1e_Data_P1_SeNew->GetEntries());
  Legend_1e[1]->AddEntry(h_1e_Data_P1_SeNew, "Data", "lpe");
  Legend_1e[1]->AddEntry(h_1e_Data_P1_SeNew, Num_Events, "");
  LegendLog_1e[1]->AddEntry(h_1e_Data_P1_SeNew, "Data", "lpe");

  sprintf (Num_Events, "%d Events", (int) h_1e_Data_P1_Strip->GetEntries());
  Legend_1e[2]->AddEntry(h_1e_Data_P1_Strip, "Data", "lpe");
  Legend_1e[2]->AddEntry(h_1e_Data_P1_Strip, Num_Events, "");
  LegendLog_1e[2]->AddEntry(h_1e_Data_P1_Strip, "Data", "lpe");

  sprintf (Num_Events, "%d Events", (int) h_1e_Data_P2_SeOld->GetEntries());
  Legend_1e[3]->AddEntry(h_1e_Data_P2_SeOld, "Data", "lpe");
  Legend_1e[3]->AddEntry(h_1e_Data_P2_SeOld, Num_Events, "");
  LegendLog_1e[3]->AddEntry(h_1e_Data_P2_SeOld, "Data", "lpe");

  sprintf (Num_Events, "%d Events", (int) h_1e_Data_P2_SeNew->GetEntries());
  Legend_1e[4]->AddEntry(h_1e_Data_P2_SeNew, "Data", "lpe");
  Legend_1e[4]->AddEntry(h_1e_Data_P2_SeNew, Num_Events, "");
  LegendLog_1e[4]->AddEntry(h_1e_Data_P2_SeNew, "Data", "lpe");

  sprintf (Num_Events, "%d Events", (int) h_1e_Data_P2_Strip->GetEntries());
  Legend_1e[5]->AddEntry(h_1e_Data_P2_Strip, "Data", "lpe");
  Legend_1e[5]->AddEntry(h_1e_Data_P2_Strip, Num_Events, "");
  LegendLog_1e[5]->AddEntry(h_1e_Data_P2_Strip, "Data", "lpe");

  for(int j = 0; j < 6; j++){

    if(j % 3 == 0){
      if(j < 3){
	TH1 *h;
	TIter   next(StackColl_1e[j]->GetHists());
	for(int i = 0; i < 13; i++){
	  h = (TH1*) next();
	  Legend_1e[j]->AddEntry(h, LegIsotopes_SeOld_P1[i].c_str(), "f");
	  Legend_1e[j]->AddEntry(h, LegEntries_SeOld_P1[i].c_str(), "");
	  LegendLog_1e[j]->AddEntry(h, LegIsotopes_SeOld_P1[i].c_str(), "f");
	}
 	h = (TH1*) next();
 	for(int i = 13; i < 16; i++){
 	  h = (TH1*) next(); 
 	  h = (TH1*) next(); 
 	  Legend_1e[j]->AddEntry(h, LegIsotopes_SeOld_P1[i].c_str(), "f"); 
 	  Legend_1e[j]->AddEntry(h, LegEntries_SeOld_P1[i].c_str(), ""); 
 	  LegendLog_1e[j]->AddEntry(h, LegIsotopes_SeOld_P1[i].c_str(), "f"); 
 	} 
      } else{
	TH1 *h;
	TIter   next(StackColl_1e[j]->GetHists());
	for(int i = 0; i < 13; i++){
	  h = (TH1*) next();
	  Legend_1e[j]->AddEntry(h, LegIsotopes_SeOld_P2[i].c_str(), "f");
	  Legend_1e[j]->AddEntry(h, LegEntries_SeOld_P2[i].c_str(), "");
	  LegendLog_1e[j]->AddEntry(h, LegIsotopes_SeOld_P2[i].c_str(), "f");
	}
 	h = (TH1*) next();
 	for(int i = 13; i < 16; i++){
 	  h = (TH1*) next(); 
 	  h = (TH1*) next(); 
 	  Legend_1e[j]->AddEntry(h, LegIsotopes_SeOld_P2[i].c_str(), "f"); 
 	  Legend_1e[j]->AddEntry(h, LegEntries_SeOld_P2[i].c_str(), ""); 
 	  LegendLog_1e[j]->AddEntry(h, LegIsotopes_SeOld_P2[i].c_str(), "f"); 
 	} 
      }
    }
    else if(j % 3 == 1){
      if(j < 3){
	TH1 *h;
	TIter   next(StackColl_1e[j]->GetHists());
	for(int i = 0; i < 13; i++){
	  h = (TH1*) next();
	  Legend_1e[j]->AddEntry(h, LegIsotopes_SeNew_P1[i].c_str(), "f");
	  Legend_1e[j]->AddEntry(h, LegEntries_SeNew_P1[i].c_str(), "");
	  LegendLog_1e[j]->AddEntry(h, LegIsotopes_SeNew_P1[i].c_str(), "f");
	}
 	h = (TH1*) next();
 	for(int i = 13; i < 16; i++){
 	  h = (TH1*) next(); 
 	  h = (TH1*) next(); 
 	  Legend_1e[j]->AddEntry(h, LegIsotopes_SeNew_P1[i].c_str(), "f"); 
 	  Legend_1e[j]->AddEntry(h, LegEntries_SeNew_P1[i].c_str(), ""); 
 	  LegendLog_1e[j]->AddEntry(h, LegIsotopes_SeNew_P1[i].c_str(), "f"); 
 	} 
      } else{
	TH1 *h;
	TIter   next(StackColl_1e[j]->GetHists());
	for(int i = 0; i < 13; i++){
	  h = (TH1*) next();
	  Legend_1e[j]->AddEntry(h, LegIsotopes_SeNew_P2[i].c_str(), "f");
	  Legend_1e[j]->AddEntry(h, LegEntries_SeNew_P2[i].c_str(), "");
	  LegendLog_1e[j]->AddEntry(h, LegIsotopes_SeNew_P2[i].c_str(), "f");
	}
 	h = (TH1*) next();
 	for(int i = 13; i < 16; i++){
 	  h = (TH1*) next(); 
 	  h = (TH1*) next(); 
 	  Legend_1e[j]->AddEntry(h, LegIsotopes_SeNew_P2[i].c_str(), "f"); 
 	  Legend_1e[j]->AddEntry(h, LegEntries_SeNew_P2[i].c_str(), ""); 
 	  LegendLog_1e[j]->AddEntry(h, LegIsotopes_SeNew_P2[i].c_str(), "f"); 
 	} 
      }
    } else {
      if(j < 3){
	TH1 *h;
	TIter   next(StackColl_1e[j]->GetHists());
	for(int i = 0; i < 13; i++){
	  h = (TH1*) next();
	  Legend_1e[j]->AddEntry(h, LegIsotopes_Strip_P1[i].c_str(), "f");
	  Legend_1e[j]->AddEntry(h, LegEntries_Strip_P1[i].c_str(), "");
	  LegendLog_1e[j]->AddEntry(h, LegIsotopes_Strip_P1[i].c_str(), "f");
	}
 	h = (TH1*) next();
 	for(int i = 13; i < 16; i++){
 	  h = (TH1*) next(); 
 	  h = (TH1*) next(); 
 	  Legend_1e[j]->AddEntry(h, LegIsotopes_Strip_P1[i].c_str(), "f"); 
 	  Legend_1e[j]->AddEntry(h, LegEntries_Strip_P1[i].c_str(), ""); 
 	  LegendLog_1e[j]->AddEntry(h, LegIsotopes_Strip_P1[i].c_str(), "f"); 
 	} 
      } else{
	TH1 *h;
	TIter   next(StackColl_1e[j]->GetHists());
	for(int i = 0; i < 13; i++){
	  h = (TH1*) next();
	  Legend_1e[j]->AddEntry(h, LegIsotopes_Strip_P2[i].c_str(), "f");
	  Legend_1e[j]->AddEntry(h, LegEntries_Strip_P2[i].c_str(), "");
	  LegendLog_1e[j]->AddEntry(h, LegIsotopes_Strip_P2[i].c_str(), "f");
	}
 	h = (TH1*) next();
 	for(int i = 13; i < 16; i++){
 	  h = (TH1*) next(); 
 	  h = (TH1*) next(); 
 	  Legend_1e[j]->AddEntry(h, LegIsotopes_Strip_P2[i].c_str(), "f"); 
 	  Legend_1e[j]->AddEntry(h, LegEntries_Strip_P2[i].c_str(), ""); 
 	  LegendLog_1e[j]->AddEntry(h, LegIsotopes_Strip_P2[i].c_str(), "f"); 
 	} 
      }
    }
  }

  // Make chi square template
  for (int i = 0; i < 6; i++){
    ChiSquares_1e[i] = new TPaveText(0.587,0.435,0.762,0.475,"LNDC");
    ChiSquares_1e[i]->SetFillColor(0);
    ChiSquares_1e[i]->SetLineColor(0);
    ChiSquares_1e[i]->SetBorderSize(0);
    ChiSquares_1e[i]->SetTextAlign(12);

    ChiSquaresLog_1e[i] = new TPaveText(0.737,0.427,0.921,0.467,"LNDC");
    ChiSquaresLog_1e[i]->SetFillColor(0);
    ChiSquaresLog_1e[i]->SetLineColor(0);
    ChiSquaresLog_1e[i]->SetBorderSize(0);
    ChiSquaresLog_1e[i]->SetTextAlign(12);
  }

  pair <Double_t, Int_t> ChiSquareResult;
  char ChiSquareText[100];

  ChiSquareResult = ChiSquareTest(h_1e_Data_P1_SeOld, (TH1D*)StackColl_1e[0]->GetStack()->Last());
  sprintf(ChiSquareText, "#chi^{2} / ndf = %.2f / %.d", ChiSquareResult.first, ChiSquareResult.second);
  ChiSquares_1e[0]->AddText(ChiSquareText);
  ChiSquaresLog_1e[0]->AddText(ChiSquareText);

  ChiSquareResult = ChiSquareTest(h_1e_Data_P1_SeNew, (TH1D*)StackColl_1e[1]->GetStack()->Last());
  sprintf(ChiSquareText, "#chi^{2} / ndf = %.2f / %.d", ChiSquareResult.first, ChiSquareResult.second);
  ChiSquares_1e[1]->AddText(ChiSquareText);
  ChiSquaresLog_1e[1]->AddText(ChiSquareText);

  ChiSquareResult = ChiSquareTest(h_1e_Data_P1_Strip, (TH1D*)StackColl_1e[2]->GetStack()->Last());
  sprintf(ChiSquareText, "#chi^{2} / ndf = %.2f / %.d", ChiSquareResult.first, ChiSquareResult.second);
  ChiSquares_1e[2]->AddText(ChiSquareText);
  ChiSquaresLog_1e[2]->AddText(ChiSquareText);

  ChiSquareResult = ChiSquareTest(h_1e_Data_P2_SeOld, (TH1D*)StackColl_1e[3]->GetStack()->Last());
  sprintf(ChiSquareText, "#chi^{2} / ndf = %.2f / %.d", ChiSquareResult.first, ChiSquareResult.second);
  ChiSquares_1e[3]->AddText(ChiSquareText);
  ChiSquaresLog_1e[3]->AddText(ChiSquareText);

  ChiSquareResult = ChiSquareTest(h_1e_Data_P2_SeNew, (TH1D*)StackColl_1e[4]->GetStack()->Last());
  sprintf(ChiSquareText, "#chi^{2} / ndf = %.2f / %.d", ChiSquareResult.first, ChiSquareResult.second);
  ChiSquares_1e[4]->AddText(ChiSquareText);
  ChiSquaresLog_1e[4]->AddText(ChiSquareText);

  ChiSquareResult = ChiSquareTest(h_1e_Data_P2_Strip, (TH1D*)StackColl_1e[5]->GetStack()->Last());
  sprintf(ChiSquareText, "#chi^{2} / ndf = %.2f / %.d", ChiSquareResult.first, ChiSquareResult.second);
  ChiSquares_1e[5]->AddText(ChiSquareText);
  ChiSquaresLog_1e[5]->AddText(ChiSquareText);

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
