#include "addChannelToStacks_1e2g.h"
#include "chiSquareTest.h"

extern THStack* StackColl_1e2g[];
extern TH1D* h_1e2g_Data_SeOld;
extern TH1D* h_1e2g_Data_SeNew;
extern const Int_t AccptRunTime;
extern TFile* infile_1e2g;
extern TLegend* Legend_1e2g[];
extern TPaveText* ChiSquares_1e2g[];

void addBackgrounds_1e2g(double *Activities_Ext, double *Activities_Ext_Err, double *Denominators_Ext, double *Activities_Rad, double *Activities_Rad_Err,  double *Denominators_Rad, double *Activities_Int, double *Activities_Int_Err,  double *Denominators_Int, double *Activities_Sig, double *Activities_Sig_Err, double *Denominators_Sig, double *AdjustActs, double *AdjustActs_Err){

  Double_t Act_PMT_Tl208          = Activities_Ext[2];
  Double_t Act_SteelFrame_Tl208   = Activities_Ext[7];
  Double_t Act_Neutrons_P1        = Activities_Ext[21];
  Double_t Act_Neutrons_P2        = Activities_Ext[22];
  Double_t Act_SWire_Bi214_P1     = Activities_Rad[0];
  Double_t Act_SWire_Tl208_P1     = Activities_Rad[1];
  Double_t Act_SFoil_Bi214_In_P1  = Activities_Rad[2];
  Double_t Act_SFoil_Bi214_Out_P1 = Activities_Rad[3];
  Double_t Act_SWire_Bi214_P2     = Activities_Rad[4];
  Double_t Act_SWire_Tl208_P2     = Activities_Rad[5];
  Double_t Act_SFoil_Bi214_In_P2  = Activities_Rad[6];
  Double_t Act_SFoil_Bi214_Out_P2 = Activities_Rad[7];
  Double_t Act_SeNew_Bi214        = Activities_Int[0];
  Double_t Act_SeOld_Bi214        = Activities_Int[1];
  Double_t Act_Mylar_Bi214        = Activities_Int[2];
  Double_t Act_SeNew_Tl208        = Activities_Int[3];
  Double_t Act_SeOld_Tl208        = Activities_Int[4];

  Double_t Act_PMT_Tl208_Err           = Activities_Ext_Err[2];
  Double_t Act_SteelFrame_Tl208_Err    = Activities_Ext_Err[7];
  Double_t Act_Neutrons_P1_Err         = Activities_Ext_Err[21];
  Double_t Act_Neutrons_P2_Err         = Activities_Ext_Err[22];
  Double_t Act_SWire_Tl208_P1_Err      = Activities_Rad_Err[1];
  Double_t Act_SWire_Tl208_P2_Err      = Activities_Rad_Err[5];
  Double_t Act_SeNew_Tl208_Err         = Activities_Int_Err[3];
  Double_t Act_SeOld_Tl208_Err         = Activities_Int_Err[4];

  Double_t Denom_PMT_Tl208        = Denominators_Ext[2];
  Double_t Denom_SteelFrame_Tl208 = Denominators_Ext[7];
  Double_t Denom_Neutrons         = Denominators_Ext[20];
  Double_t Denom_SWire_Bi214      = Denominators_Rad[0];
  Double_t Denom_SWire_Tl208      = Denominators_Rad[3];
  Double_t Denom_SFoil_Bi214      = Denominators_Rad[4];
  Double_t Denom_SeNew_Bi214      = Denominators_Int[0];
  Double_t Denom_SeOld_Bi214      = Denominators_Int[1];
  Double_t Denom_Mylar_Bi214      = Denominators_Int[2];
  Double_t Denom_SeNew_Tl208      = Denominators_Int[6];
  Double_t Denom_SeOld_Tl208      = Denominators_Int[7];

  Int_t    FillColor_SeNew_Bi214      = kRed;
  Int_t    FillColor_SeOld_Bi214      = kRed;
  Int_t    FillColor_Mylar_Bi214      = kRed;
  Int_t    FillColor_SWire_Bi214_P1   = kRed;
  Int_t    FillColor_SWire_Bi214_P2   = kRed;
  Int_t    FillColor_SFoil_Bi214_P1   = kRed;
  Int_t    FillColor_SFoil_Bi214_P2   = kRed;
  Int_t    FillColor_PMT_Tl208        = kOrange;
  Int_t    FillColor_SteelFrame_Tl208 = kYellow;
  Int_t    FillColor_Neutrons_P1      = kYellow+1;
  Int_t    FillColor_Neutrons_P2      = kYellow+1;
  Int_t    FillColor_SWire_Tl208_P1   = kAzure;
  Int_t    FillColor_SWire_Tl208_P2   = kAzure-2;
  Int_t    FillColor_SeNew_Tl208      = kGreen+2;
  Int_t    FillColor_SeOld_Tl208      = kSpring-1;

  // Create collection of histogram stacks
  StackColl_1e2g[0]  = new THStack("h_1e2g_SeOldStack"  ,"Electron Energy"); 
  StackColl_1e2g[1]  = new THStack("h_1e2g_SeNewStack"  ,"Electron Energy");  

  // Add Bi214 Backgrounds

  // 0) SeNew_Bi214
  Double_t ScaleFactor_SeNew_Bi214 = Act_SeNew_Bi214*AccptRunTime/Denom_SeNew_Bi214;
  addChannelToStacks_1e2g("SeNew_Bi214", ScaleFactor_SeNew_Bi214, FillColor_SeNew_Bi214, StackColl_1e2g, infile_1e2g);

  // 1) SeOld_Bi214
  Double_t ScaleFactor_SeOld_Bi214 = Act_SeOld_Bi214*AccptRunTime/Denom_SeOld_Bi214;
  addChannelToStacks_1e2g("SeOld_Bi214", ScaleFactor_SeOld_Bi214, FillColor_SeOld_Bi214, StackColl_1e2g, infile_1e2g);

  // 2) Mylar_Bi214
  Double_t ScaleFactor_Mylar_Bi214 = Act_Mylar_Bi214*AccptRunTime/Denom_Mylar_Bi214;
  addChannelToStacks_1e2g("Mylar_Bi214", ScaleFactor_Mylar_Bi214, FillColor_Mylar_Bi214, StackColl_1e2g, infile_1e2g);

  // 3) SWire_Bi214_P1
  Double_t ScaleFactor_SWire_Bi214_P1 = Act_SWire_Bi214_P1*AccptRunTime/Denom_SWire_Bi214;
  addChannelToStacks_1e2g("SWire_Bi214_P1", ScaleFactor_SWire_Bi214_P1, FillColor_SWire_Bi214_P1, StackColl_1e2g, infile_1e2g);

  // 4) SWire_Bi214_P2
  Double_t ScaleFactor_SWire_Bi214_P2 = Act_SWire_Bi214_P2*AccptRunTime/Denom_SWire_Bi214;
  addChannelToStacks_1e2g("SWire_Bi214_P2", ScaleFactor_SWire_Bi214_P2, FillColor_SWire_Bi214_P2, StackColl_1e2g, infile_1e2g);

  // 5) SFoil_Bi214_In_P1
  Double_t ScaleFactor_SFoil_Bi214_In_P1 = Act_SFoil_Bi214_In_P1*AccptRunTime/Denom_SFoil_Bi214;
  addChannelToStacks_1e2g("SFoil_Bi214_In_P1", ScaleFactor_SFoil_Bi214_In_P1, FillColor_SFoil_Bi214_P1, StackColl_1e2g, infile_1e2g);

  // 6) SFoil_Bi214_Out_P1
  Double_t ScaleFactor_SFoil_Bi214_Out_P1 = Act_SFoil_Bi214_Out_P1*AccptRunTime/Denom_SFoil_Bi214;
  addChannelToStacks_1e2g("SFoil_Bi214_Out_P1", ScaleFactor_SFoil_Bi214_Out_P1, FillColor_SFoil_Bi214_P1, StackColl_1e2g, infile_1e2g);

  // 7) SFoil_Bi214_In_P2
  Double_t ScaleFactor_SFoil_Bi214_In_P2 = Act_SFoil_Bi214_In_P2*AccptRunTime/Denom_SFoil_Bi214;
  addChannelToStacks_1e2g("SFoil_Bi214_In_P2", ScaleFactor_SFoil_Bi214_In_P2, FillColor_SFoil_Bi214_P2, StackColl_1e2g, infile_1e2g);

  // 8) SFoil_Bi214_Out_P2
  Double_t ScaleFactor_SFoil_Bi214_Out_P2 = Act_SFoil_Bi214_Out_P2*AccptRunTime/Denom_SFoil_Bi214;
  addChannelToStacks_1e2g("SFoil_Bi214_Out_P2", ScaleFactor_SFoil_Bi214_Out_P2, FillColor_SFoil_Bi214_P2, StackColl_1e2g, infile_1e2g);

  // Add Neutrons

  // 9) Neutrons_P1
  Double_t ScaleFactor_Neutrons_P1 = Act_Neutrons_P1*AccptRunTime/Denom_Neutrons;
  addChannelToStacks_1e2g("Data_Neutrons_P1", ScaleFactor_Neutrons_P1, FillColor_Neutrons_P1, StackColl_1e2g, infile_1e2g);

  // 10) Neutrons_P2
  Double_t ScaleFactor_Neutrons_P2 = Act_Neutrons_P2*AccptRunTime/Denom_Neutrons;
  addChannelToStacks_1e2g("Data_Neutrons_P2", ScaleFactor_Neutrons_P2, FillColor_Neutrons_P2, StackColl_1e2g, infile_1e2g);

  // Add Tl208 Backgrounds

  // 11) PMT_Tl208
  Double_t ScaleFactor_PMT_Tl208 = Act_PMT_Tl208*AccptRunTime/Denom_PMT_Tl208;
  addChannelToStacks_1e2g("PMT_Tl208", ScaleFactor_PMT_Tl208, FillColor_PMT_Tl208, StackColl_1e2g, infile_1e2g);

  // 12) SteelFrame_Tl208
  Double_t ScaleFactor_SteelFrame_Tl208 = Act_SteelFrame_Tl208*AccptRunTime/Denom_SteelFrame_Tl208;
  addChannelToStacks_1e2g("SteelFrame_Tl208", ScaleFactor_SteelFrame_Tl208, FillColor_SteelFrame_Tl208, StackColl_1e2g, infile_1e2g);

  // 13) SWire_Tl208_P1
  Double_t ScaleFactor_SWire_Tl208_P1 = Act_SWire_Tl208_P1*AccptRunTime/Denom_SWire_Tl208;
  addChannelToStacks_1e2g("SWire_Tl208_P1", ScaleFactor_SWire_Tl208_P1, FillColor_SWire_Tl208_P1, StackColl_1e2g, infile_1e2g);

  // 14) SWire_Tl208_P2
  Double_t ScaleFactor_SWire_Tl208_P2 = Act_SWire_Tl208_P2*AccptRunTime/Denom_SWire_Tl208;
  addChannelToStacks_1e2g("SWire_Tl208_P2", ScaleFactor_SWire_Tl208_P2, FillColor_SWire_Tl208_P2, StackColl_1e2g, infile_1e2g);

  // Finally add signals to be fitted

  // 15) SeNew_Tl208
  Double_t ScaleFactor_SeNew_Tl208 = Act_SeNew_Tl208*AccptRunTime/Denom_SeNew_Tl208;
  addChannelToStacks_1e2g("SeNew_Tl208", ScaleFactor_SeNew_Tl208, FillColor_SeNew_Tl208, StackColl_1e2g, infile_1e2g);

  // 16) SeOld_Tl208
  Double_t ScaleFactor_SeOld_Tl208 = Act_SeOld_Tl208*AccptRunTime/Denom_SeOld_Tl208;
  addChannelToStacks_1e2g("SeOld_Tl208", ScaleFactor_SeOld_Tl208, FillColor_SeOld_Tl208, StackColl_1e2g, infile_1e2g);

  // Create legend to put on plots
  string LegIsotopes[9];
  string LegEntries[9];
  char buffer[100];

  LegIsotopes[0] = "1e1#alpha (^{214}Bi)";
  sprintf (buffer, " ");
  LegEntries[0] = buffer;
  LegIsotopes[1] = "Neutrons P1";
  if(Act_Neutrons_P1_Err > 0){sprintf (buffer, "S = %.1f #pm %.1f x10^{-3}", 1000*Act_Neutrons_P1, 1000*Act_Neutrons_P1_Err );}
  else{sprintf (buffer, "S = %.1f x10^{-3}", 1000*Act_Neutrons_P1);}
  LegEntries[1] = buffer;
  LegIsotopes[2] = "Neutrons P2";
  if(Act_Neutrons_P2_Err > 0){sprintf (buffer, "S = %.1f #pm %.1f x10^{-3}", 1000*Act_Neutrons_P2, 1000*Act_Neutrons_P2_Err );}
  else{sprintf (buffer, "S = %.1f x10^{-3}", 1000*Act_Neutrons_P2);}
  LegEntries[2] = buffer;
  LegIsotopes[3] = "^{208}Tl PMT";
  if(Act_PMT_Tl208_Err > 0){sprintf (buffer, "A = %.2f #pm %.1f Bq", Act_PMT_Tl208, Act_PMT_Tl208_Err);}
  else{sprintf (buffer, "A = %.1f Bq", Act_PMT_Tl208);}
  LegEntries[3] = buffer;
  LegIsotopes[4] = "^{208}Tl Steel Frame";
  if(Act_SteelFrame_Tl208_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f Bq", Act_SteelFrame_Tl208, Act_SteelFrame_Tl208_Err );}
  else{sprintf (buffer, "A = %.1f Bq", Act_SteelFrame_Tl208);}
  LegEntries[4] = buffer;
  LegIsotopes[5] = "^{208}Tl SWire P1";
  if(Act_SWire_Tl208_P1_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f mBq", Act_SWire_Tl208_P1*1000, Act_SWire_Tl208_P1_Err*1000 );}
  else{sprintf (buffer, "A = %.1f mBq", Act_SWire_Tl208_P1*1000);}
  LegEntries[5] = buffer;
  LegIsotopes[6] = "^{208}Tl SWire P2";
  if(Act_SWire_Tl208_P2_Err > 0){sprintf (buffer, "A = %.1f #pm %.1f mBq", Act_SWire_Tl208_P2*1000, Act_SWire_Tl208_P2_Err*1000 );}
  else{sprintf (buffer, "A = %.1f mBq", Act_SWire_Tl208_P2*1000);}
  LegEntries[6] = buffer;
  LegIsotopes[7] = "^{208}Tl SeNew";
  if(Act_SeNew_Tl208_Err > 0){sprintf (buffer, "A = %.3f #pm %.3f mBq", Act_SeNew_Tl208*1000, Act_SeNew_Tl208_Err*1000 );}
  else{sprintf (buffer, "A = %.3f mBq", Act_SeNew_Tl208*1000);}
  LegEntries[7] = buffer;
  LegIsotopes[8] = "^{208}Tl SeOld";
  if(Act_SeOld_Tl208_Err > 0){sprintf (buffer, "A = %.3f #pm %.3f mBq", Act_SeOld_Tl208*1000, Act_SeOld_Tl208_Err*1000 );}
  else{sprintf (buffer, "A = %.3f mBq", Act_SeOld_Tl208*1000);}
  LegEntries[8] = buffer;

  // Make legends
  for(int i = 0; i < 2; i++){
    Legend_1e2g[i] = new TLegend(0.540,0.585,0.938,0.947);
    Legend_1e2g[i]->SetNColumns(2);
    Legend_1e2g[i]->SetColumnSeparation(-0.075);
    Legend_1e2g[i]->SetFillColor(0);
    Legend_1e2g[i]->SetLineColor(0);
    Legend_1e2g[i]->SetBorderSize(0);
  }

  char Num_Events[40];

  sprintf (Num_Events, "%d Events", (int) h_1e2g_Data_SeOld->GetEntries());
  Legend_1e2g[0]->AddEntry(h_1e2g_Data_SeOld, "Data", "lpe");
  Legend_1e2g[0]->AddEntry(h_1e2g_Data_SeOld, Num_Events, "");

  sprintf (Num_Events, "%d Events", (int) h_1e2g_Data_SeNew->GetEntries());
  Legend_1e2g[1]->AddEntry(h_1e2g_Data_SeNew, "Data", "lpe");
  Legend_1e2g[1]->AddEntry(h_1e2g_Data_SeNew, Num_Events, "");

  for(int j = 0; j < 2; j++){
    TH1 *h;
    TIter   next(StackColl_1e2g[j]->GetHists());

    for(int i = 0; i < 8; i++){
      h = (TH1*) next();
    }

    for(int i = 0; i < 9; i++){
      h = (TH1*) next();
      Legend_1e2g[j]->AddEntry(h, LegIsotopes[i].c_str(), "f");
      Legend_1e2g[j]->AddEntry(h, LegEntries[i].c_str(), "");
    }
  }

  // Make chi square template
  TPaveText* ChiSquaresTemp = new TPaveText(0.588,0.534,0.770,0.574,"LNDC");
  ChiSquaresTemp->SetFillColor(0);
  ChiSquaresTemp->SetLineColor(0);
  ChiSquaresTemp->SetBorderSize(0);
  ChiSquaresTemp->SetTextAlign(12);

  for(int i = 0; i < 2; i++){
    ChiSquares_1e2g[i] = new TPaveText(*ChiSquaresTemp);
  }

  pair <Double_t, Int_t> ChiSquareResult;
  char ChiSquareText[100];

  ChiSquareResult = ChiSquareTest( h_1e2g_Data_SeOld,(TH1D*)StackColl_1e2g[0]->GetStack()->Last());
  sprintf(ChiSquareText, "#chi^{2} / ndf = %.2f / %.d", ChiSquareResult.first, ChiSquareResult.second);
  ChiSquares_1e2g[0]->AddText(ChiSquareText);

  ChiSquareResult = ChiSquareTest( h_1e2g_Data_SeNew,(TH1D*)StackColl_1e2g[1]->GetStack()->Last());
  sprintf(ChiSquareText, "#chi^{2} / ndf = %.2f / %.d", ChiSquareResult.first, ChiSquareResult.second);
  ChiSquares_1e2g[1]->AddText(ChiSquareText);

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
