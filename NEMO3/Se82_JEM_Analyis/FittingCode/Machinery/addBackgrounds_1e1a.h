#include "addChannelToStacks_1e1a.h"
#include "chiSquareTest.h"

extern THStack* StackColl_1e1a_P1[];
extern THStack* StackColl_1e1a_P2[];
extern TH1D* h_1e1a_Data_P1_aOuteOut_Sector6;
extern TH1D* h_1e1a_Data_P1_aIneOut_Sector6;
extern TH1D* h_1e1a_Data_P1_aOuteIn_Sector6;
extern TH1D* h_1e1a_Data_P1_aIneIn_Sector6;
extern TH1D* h_1e1a_Data_P1_aOuteOut_Sector7;
extern TH1D* h_1e1a_Data_P1_aIneOut_Sector7;
extern TH1D* h_1e1a_Data_P1_aOuteIn_Sector7;
extern TH1D* h_1e1a_Data_P1_aIneIn_Sector7;
extern TH1D* h_1e1a_Data_P1_aOuteOut_Sector8;
extern TH1D* h_1e1a_Data_P1_aIneOut_Sector8;
extern TH1D* h_1e1a_Data_P1_aOuteIn_Sector8;
extern TH1D* h_1e1a_Data_P1_aIneIn_Sector8;
extern TH1D* h_1e1a_Data_P1_AllEvents_Sector6;
extern TH1D* h_1e1a_Data_P1_AllEvents_Sector7;
extern TH1D* h_1e1a_Data_P1_AllEvents_Sector8;
extern TH1D* h_1e1a_Data_P2_aOuteOut_Sector6;
extern TH1D* h_1e1a_Data_P2_aIneOut_Sector6;
extern TH1D* h_1e1a_Data_P2_aOuteIn_Sector6;
extern TH1D* h_1e1a_Data_P2_aIneIn_Sector6;
extern TH1D* h_1e1a_Data_P2_aOuteOut_Sector7;
extern TH1D* h_1e1a_Data_P2_aIneOut_Sector7;
extern TH1D* h_1e1a_Data_P2_aOuteIn_Sector7;
extern TH1D* h_1e1a_Data_P2_aIneIn_Sector7;
extern TH1D* h_1e1a_Data_P2_aOuteOut_Sector8;
extern TH1D* h_1e1a_Data_P2_aIneOut_Sector8;
extern TH1D* h_1e1a_Data_P2_aOuteIn_Sector8;
extern TH1D* h_1e1a_Data_P2_aIneIn_Sector8;
extern TH1D* h_1e1a_Data_P2_AllEvents_Sector6;
extern TH1D* h_1e1a_Data_P2_AllEvents_Sector7;
extern TH1D* h_1e1a_Data_P2_AllEvents_Sector8;
extern const Int_t AccptRunTime;
extern TFile* infile_1e1a;
extern TLegend* Legend_1e1a_P1[];
extern TLegend* Legend_1e1a_P2[];
extern TPaveText* ChiSquares_1e1a_P1[];
extern TPaveText* ChiSquares_1e1a_P2[];

void addBackgrounds_1e1a(double *Activities_Ext, double *Activities_Ext_Err, double *Denominators_Ext, double *Activities_Rad, double *Activities_Rad_Err,  double *Denominators_Rad, double *Activities_Int, double *Activities_Int_Err,  double *Denominators_Int, double *Activities_Sig, double *Activities_Sig_Err, double *Denominators_Sig, double *AdjustActs, double *AdjustActs_Err){

  Double_t Act_SeNew_Bi214             = Activities_Int[0];
  Double_t Act_SeNew_Bi214_Err         = Activities_Int_Err[0];
  Double_t Act_SeOld_Bi214             = Activities_Int[1];
  Double_t Act_SeOld_Bi214_Err         = Activities_Int_Err[1];
  Double_t Act_Mylar_Bi214             = Activities_Int[2];
  Double_t Act_Mylar_Bi214_Err         = Activities_Int_Err[2];
  Double_t Act_SWire_Bi214_P1          = Activities_Rad[0];
  Double_t Act_SWire_Bi214_P1_Err      = Activities_Rad_Err[0];
  Double_t Act_SFoil_Bi214_P1_In       = Activities_Rad[2];
  Double_t Act_SFoil_Bi214_P1_In_Err   = Activities_Rad_Err[2];
  Double_t Act_SFoil_Bi214_P1_Out      = Activities_Rad[3];
  Double_t Act_SFoil_Bi214_P1_Out_Err  = Activities_Rad_Err[3];
  Double_t Act_SWire_Bi214_P2          = Activities_Rad[4];
  Double_t Act_SWire_Bi214_P2_Err      = Activities_Rad_Err[4];
  Double_t Act_SFoil_Bi214_P2_In       = Activities_Rad[6];
  Double_t Act_SFoil_Bi214_P2_In_Err   = Activities_Rad_Err[6];
  Double_t Act_SFoil_Bi214_P2_Out      = Activities_Rad[7];
  Double_t Act_SFoil_Bi214_P2_Out_Err  = Activities_Rad_Err[7];

  Double_t Denom_SeNew_Bi214 = Denominators_Int[0];
  Double_t Denom_SeOld_Bi214 = Denominators_Int[1];
  Double_t Denom_Mylar_Bi214 = Denominators_Int[2];
  Double_t Denom_SWire_Bi214 = Denominators_Rad[0];
  Double_t Denom_SFoil_Bi214 = Denominators_Rad[4];

  Int_t    FillColor_SeNew_Bi214 = kRed;
  Int_t    FillColor_SeOld_Bi214 = kRed+1;
  Int_t    FillColor_Mylar_Bi214 = kYellow;
  Int_t    FillColor_SWire_Bi214_P1 = kSpring-2;
  Int_t    FillColor_SWire_Bi214_P2 = kSpring-1;
  Int_t    FillColor_SFoil_Bi214_P1_In = kCyan;
  Int_t    FillColor_SFoil_Bi214_P2_In = kAzure+10;
  Int_t    FillColor_SFoil_Bi214_P1_Out = kAzure+1;
  Int_t    FillColor_SFoil_Bi214_P2_Out = kAzure-2;

  // Create collection of histogram stacks
  StackColl_1e1a_P1[0]  = new THStack("h_1e1a_P1_aOuteOut_Sector6" ,"Length of Alpha Track");
  StackColl_1e1a_P1[1]  = new THStack("h_1e1a_P1_aIneOut_Sector6"  ,"Length of Alpha Track");
  StackColl_1e1a_P1[2]  = new THStack("h_1e1a_P1_aOuteIn_Sector6"  ,"Length of Alpha Track");
  StackColl_1e1a_P1[3]  = new THStack("h_1e1a_P1_aIneIn_Sector6"   ,"Length of Alpha Track");
  StackColl_1e1a_P1[4]  = new THStack("h_1e1a_P1_aOuteOut_Sector7" ,"Length of Alpha Track");
  StackColl_1e1a_P1[5]  = new THStack("h_1e1a_P1_aIneOut_Sector7"  ,"Length of Alpha Track");
  StackColl_1e1a_P1[6]  = new THStack("h_1e1a_P1_aOuteIn_Sector7"  ,"Length of Alpha Track");
  StackColl_1e1a_P1[7]  = new THStack("h_1e1a_P1_aIneIn_Sector7"   ,"Length of Alpha Track");
  StackColl_1e1a_P1[8]  = new THStack("h_1e1a_P1_aOuteOut_Sector8" ,"Length of Alpha Track");
  StackColl_1e1a_P1[9]  = new THStack("h_1e1a_P1_aIneOut_Sector8"  ,"Length of Alpha Track");
  StackColl_1e1a_P1[10] = new THStack("h_1e1a_P1_aOuteIn_Sector8"  ,"Length of Alpha Track");
  StackColl_1e1a_P1[11] = new THStack("h_1e1a_P1_aIneIn_Sector8"   ,"Length of Alpha Track");
  StackColl_1e1a_P1[12] = new THStack("h_1e1a_P1_AllEvents_Sector6","Length of Alpha Track");
  StackColl_1e1a_P1[13] = new THStack("h_1e1a_P1_AllEvents_Sector7","Length of Alpha Track");
  StackColl_1e1a_P1[14] = new THStack("h_1e1a_P1_AllEvents_Sector8","Length of Alpha Track");
  StackColl_1e1a_P2[0]  = new THStack("h_1e1a_P2_aOuteOut_Sector6" ,"Length of Alpha Track");
  StackColl_1e1a_P2[1]  = new THStack("h_1e1a_P2_aIneOut_Sector6"  ,"Length of Alpha Track");
  StackColl_1e1a_P2[2]  = new THStack("h_1e1a_P2_aOuteIn_Sector6"  ,"Length of Alpha Track");
  StackColl_1e1a_P2[3]  = new THStack("h_1e1a_P2_aIneIn_Sector6"   ,"Length of Alpha Track");
  StackColl_1e1a_P2[4]  = new THStack("h_1e1a_P2_aOuteOut_Sector7" ,"Length of Alpha Track");
  StackColl_1e1a_P2[5]  = new THStack("h_1e1a_P2_aIneOut_Sector7"  ,"Length of Alpha Track");
  StackColl_1e1a_P2[6]  = new THStack("h_1e1a_P2_aOuteIn_Sector7"  ,"Length of Alpha Track");
  StackColl_1e1a_P2[7]  = new THStack("h_1e1a_P2_aIneIn_Sector7"   ,"Length of Alpha Track");
  StackColl_1e1a_P2[8]  = new THStack("h_1e1a_P2_aOuteOut_Sector8" ,"Length of Alpha Track");
  StackColl_1e1a_P2[9]  = new THStack("h_1e1a_P2_aIneOut_Sector8"  ,"Length of Alpha Track");
  StackColl_1e1a_P2[10] = new THStack("h_1e1a_P2_aOuteIn_Sector8"  ,"Length of Alpha Track");
  StackColl_1e1a_P2[11] = new THStack("h_1e1a_P2_aIneIn_Sector8"   ,"Length of Alpha Track");
  StackColl_1e1a_P2[12] = new THStack("h_1e1a_P2_AllEvents_Sector6","Length of Alpha Track");
  StackColl_1e1a_P2[13] = new THStack("h_1e1a_P2_AllEvents_Sector7","Length of Alpha Track");
  StackColl_1e1a_P2[14] = new THStack("h_1e1a_P2_AllEvents_Sector8","Length of Alpha Track");

  // Add Backgrounds for P1

  // 1) SeNew_Bi214_P1
  Double_t ScaleFactor_SeNew_Bi214_P1 = Act_SeNew_Bi214*AccptRunTime/Denom_SeNew_Bi214;
  addChannelToStacks_1e1a("SeNew_Bi214_P1", ScaleFactor_SeNew_Bi214_P1, FillColor_SeNew_Bi214, StackColl_1e1a_P1, infile_1e1a);

  // 2) SeOld_Bi214_P1
  Double_t ScaleFactor_SeOld_Bi214_P1 = Act_SeOld_Bi214*AccptRunTime/Denom_SeOld_Bi214;
  addChannelToStacks_1e1a("SeOld_Bi214_P1", ScaleFactor_SeOld_Bi214_P1, FillColor_SeOld_Bi214, StackColl_1e1a_P1, infile_1e1a);

  // 3) Mylar_Bi214_P1
  Double_t ScaleFactor_Mylar_Bi214_P1 = Act_Mylar_Bi214*AccptRunTime/Denom_Mylar_Bi214;
  addChannelToStacks_1e1a("Mylar_Bi214_P1", ScaleFactor_Mylar_Bi214_P1, FillColor_Mylar_Bi214, StackColl_1e1a_P1, infile_1e1a);

  // Add Radon Backgrounds

  // 4) SWire_Bi214_P1
  Double_t Scale_SWire_Bi214_P1 = Act_SWire_Bi214_P1*AccptRunTime/Denom_SWire_Bi214;
  addChannelToStacks_1e1a("SWire_Bi214_P1", Scale_SWire_Bi214_P1, FillColor_SWire_Bi214_P1, StackColl_1e1a_P1, infile_1e1a);

  // 5) SFoil_Bi214_P1_In
  Double_t ScaleFactor_SFoil_Bi214_P1_In = Act_SFoil_Bi214_P1_In*AccptRunTime/Denom_SFoil_Bi214;
  addChannelToStacks_1e1a("SFoil_Bi214_P1_In", ScaleFactor_SFoil_Bi214_P1_In, FillColor_SFoil_Bi214_P1_In, StackColl_1e1a_P1, infile_1e1a);

  // 6) SFoil_Bi214_P1_Out
  Double_t ScaleFactor_SFoil_Bi214_P1_Out = Act_SFoil_Bi214_P1_Out*AccptRunTime/Denom_SFoil_Bi214;
  addChannelToStacks_1e1a("SFoil_Bi214_P1_Out", ScaleFactor_SFoil_Bi214_P1_Out, FillColor_SFoil_Bi214_P1_Out, StackColl_1e1a_P1, infile_1e1a);

  // Add Backgrounds for P2

  // 7) SeNew_Bi214_P2
  Double_t ScaleFactor_SeNew_Bi214_P2 = Act_SeNew_Bi214*AccptRunTime/Denom_SeNew_Bi214;
  addChannelToStacks_1e1a("SeNew_Bi214_P2", ScaleFactor_SeNew_Bi214_P2, FillColor_SeNew_Bi214, StackColl_1e1a_P2, infile_1e1a);

  // 8) SeOld_Bi214_P2
  Double_t ScaleFactor_SeOld_Bi214_P2 = Act_SeOld_Bi214*AccptRunTime/Denom_SeOld_Bi214;
  addChannelToStacks_1e1a("SeOld_Bi214_P2", ScaleFactor_SeOld_Bi214_P2, FillColor_SeOld_Bi214, StackColl_1e1a_P2, infile_1e1a);

  // 9) Mylar_Bi214_P2
  Double_t ScaleFactor_Mylar_Bi214_P2 = Act_Mylar_Bi214*AccptRunTime/Denom_Mylar_Bi214;
  addChannelToStacks_1e1a("Mylar_Bi214_P2", ScaleFactor_Mylar_Bi214_P2, FillColor_Mylar_Bi214, StackColl_1e1a_P2, infile_1e1a);

  // 10) SWire_Bi214_P2
  Double_t Scale_SWire_Bi214_P2 = Act_SWire_Bi214_P2*AccptRunTime/Denom_SWire_Bi214;
  addChannelToStacks_1e1a("SWire_Bi214_P2", Scale_SWire_Bi214_P2, FillColor_SWire_Bi214_P2, StackColl_1e1a_P2, infile_1e1a);

  // 11) SFoil_Bi214_P2_In
  Double_t ScaleFactor_SFoil_Bi214_P2_In = Act_SFoil_Bi214_P2_In*AccptRunTime/Denom_SFoil_Bi214;
  addChannelToStacks_1e1a("SFoil_Bi214_P2_In", ScaleFactor_SFoil_Bi214_P2_In, FillColor_SFoil_Bi214_P2_In, StackColl_1e1a_P2, infile_1e1a);

  // 12) SFoil_Bi214_P2_Out
  Double_t ScaleFactor_SFoil_Bi214_P2_Out = Act_SFoil_Bi214_P2_Out*AccptRunTime/Denom_SFoil_Bi214;
  addChannelToStacks_1e1a("SFoil_Bi214_P2_Out", ScaleFactor_SFoil_Bi214_P2_Out, FillColor_SFoil_Bi214_P2_Out, StackColl_1e1a_P2, infile_1e1a);

  // Create legend to put on plots
  char buffer[100];
  string LegIsotopes_P1[6];
  string LegEntries_P1[6];
  string LegIsotopes_P2[6];
  string LegEntries_P2[6];

  LegIsotopes_P1[0] = "^{214}Bi SeNew";
  if(Act_SeNew_Bi214_Err > 0){sprintf (buffer, "A = %.2f #pm %.2f mBq", Act_SeNew_Bi214*1000, Act_SeNew_Bi214_Err*1000);}
  else{sprintf (buffer, "A = %.2f mBq", Act_SeNew_Bi214*1000);}
  LegEntries_P1[0] = buffer;
  LegIsotopes_P1[1] = "^{214}Bi SeOld";
  if(Act_SeOld_Bi214_Err > 0){sprintf (buffer, "A = %.2f #pm %.2f mBq", Act_SeOld_Bi214*1000, Act_SeOld_Bi214_Err*1000);}
  else{sprintf (buffer, "A = %.2f mBq", Act_SeOld_Bi214*1000);}
  LegEntries_P1[1] = buffer;
  LegIsotopes_P1[2] = "^{214}Bi Mylar";
  if(Act_Mylar_Bi214_Err > 0){sprintf (buffer, "A = %.2f #pm %.2f mBq", Act_Mylar_Bi214*1000, Act_Mylar_Bi214_Err*1000);}
  else{sprintf (buffer, "A = %.2f mBq", Act_Mylar_Bi214*1000);}
  LegEntries_P1[2] = buffer;
  LegIsotopes_P1[3] = "^{214}Bi SWire";
  if(Act_SWire_Bi214_P1_Err > 0)   {sprintf (buffer, "A = %.2f #pm %.1f mBq",  Act_SWire_Bi214_P1*1000,   Act_SWire_Bi214_P1_Err*1000);}
  else{sprintf (buffer, "A = %.1f mBq", Act_SWire_Bi214_P1*1000);}
  LegEntries_P1[3] = buffer;
  LegIsotopes_P1[4] = "^{214}Bi SFoil In";
  if(Act_SFoil_Bi214_P1_In_Err > 0){sprintf (buffer, "A = %.2f #pm %.2f mBq", Act_SFoil_Bi214_P1_In*1000, Act_SFoil_Bi214_P1_In_Err*1000);}
  else{sprintf (buffer, "A = %.2f mBq", Act_SFoil_Bi214_P1_In*1000);}
  LegEntries_P1[4] = buffer;
  LegIsotopes_P1[5] = "^{214}Bi SFoil Out";
  if(Act_SFoil_Bi214_P1_Out_Err > 0){sprintf (buffer, "A = %.2f #pm %.2f mBq", Act_SFoil_Bi214_P1_Out*1000, Act_SFoil_Bi214_P1_Out_Err*1000);}
  else{sprintf (buffer, "A = %.2f mBq", Act_SFoil_Bi214_P1_Out*1000);}
  LegEntries_P1[5] = buffer;

  LegIsotopes_P2[0] = "^{214}Bi SeNew";
  if(Act_SeNew_Bi214_Err > 0){sprintf (buffer, "A = %.2f #pm %.2f mBq", Act_SeNew_Bi214*1000, Act_SeNew_Bi214_Err*1000);}
  else{sprintf (buffer, "A = %.2f mBq", Act_SeNew_Bi214*1000);}
  LegEntries_P2[0] = buffer;
  LegIsotopes_P2[1] = "^{214}Bi SeOld";
  if(Act_SeOld_Bi214_Err > 0){sprintf (buffer, "A = %.2f #pm %.2f mBq", Act_SeOld_Bi214*1000, Act_SeOld_Bi214_Err*1000);}
  else{sprintf (buffer, "A = %.2f mBq", Act_SeOld_Bi214*1000);}
  LegEntries_P2[1] = buffer;
  LegIsotopes_P2[2] = "^{214}Bi Mylar";
  if(Act_Mylar_Bi214_Err > 0){sprintf (buffer, "A = %.2f #pm %.2f mBq", Act_Mylar_Bi214*1000, Act_Mylar_Bi214_Err*1000);}
  else{sprintf (buffer, "A = %.2f mBq", Act_Mylar_Bi214*1000);}
  LegEntries_P2[2] = buffer;
  LegIsotopes_P2[3] = "^{214}Bi SWire";
  if(Act_SWire_Bi214_P2_Err > 0)   {sprintf (buffer, "A = %.2f #pm %.1f mBq",  Act_SWire_Bi214_P2*1000,         Act_SWire_Bi214_P2_Err*1000);}
  else{sprintf (buffer, "A = %.1f mBq", Act_SWire_Bi214_P2*1000);}
  LegEntries_P2[3] = buffer;
  LegIsotopes_P2[4] = "^{214}Bi SFoil In";
  if(Act_SFoil_Bi214_P2_In_Err > 0){sprintf (buffer, "A = %.2f #pm %.2f mBq", Act_SFoil_Bi214_P2_In*1000, Act_SFoil_Bi214_P2_In_Err*1000);}
  else{sprintf (buffer, "A = %.2f mBq", Act_SFoil_Bi214_P2_In*1000);}
  LegEntries_P2[4] = buffer;
  LegIsotopes_P2[5] = "^{214}Bi SFoil Out";
  if(Act_SFoil_Bi214_P2_Out_Err > 0){sprintf (buffer, "A = %.2f #pm %.2f mBq", Act_SFoil_Bi214_P2_Out*1000, Act_SFoil_Bi214_P2_Out_Err*1000);}
  else{sprintf (buffer, "A = %.2f mBq", Act_SFoil_Bi214_P2_Out*1000);}
  LegEntries_P2[5] = buffer;

  // Make legend template
  for(int i = 0; i < 15; i++){
    Legend_1e1a_P1[i] = new TLegend(0.668,0.585,0.947,0.947);
    Legend_1e1a_P1[i]->SetNColumns(2);
    Legend_1e1a_P1[i]->SetFillColor(0);
    Legend_1e1a_P1[i]->SetLineColor(0);
    Legend_1e1a_P1[i]->SetBorderSize(0);
  }
  for(int i = 0; i < 15; i++){
    Legend_1e1a_P2[i] = new TLegend(0.668,0.585,0.947,0.947);
    Legend_1e1a_P2[i]->SetNColumns(2);
    Legend_1e1a_P2[i]->SetFillColor(0);
    Legend_1e1a_P2[i]->SetLineColor(0);
    Legend_1e1a_P2[i]->SetBorderSize(0);
  }

  char Num_Events[40];

  sprintf (Num_Events, "%d Events", (int) h_1e1a_Data_P1_aOuteOut_Sector6->GetEntries());
  Legend_1e1a_P1[0]->AddEntry(h_1e1a_Data_P1_aOuteOut_Sector6, "Data", "lpe");
  Legend_1e1a_P1[0]->AddEntry(h_1e1a_Data_P1_aOuteOut_Sector6, Num_Events, "");

  sprintf (Num_Events, "%d Events", (int) h_1e1a_Data_P1_aIneOut_Sector6->GetEntries());
  Legend_1e1a_P1[1]->AddEntry(h_1e1a_Data_P1_aIneOut_Sector6, "Data", "lpe");
  Legend_1e1a_P1[1]->AddEntry(h_1e1a_Data_P1_aIneOut_Sector6, Num_Events, "");

  sprintf (Num_Events, "%d Events", (int) h_1e1a_Data_P1_aOuteIn_Sector6->GetEntries());
  Legend_1e1a_P1[2]->AddEntry(h_1e1a_Data_P1_aOuteIn_Sector6, "Data", "lpe");
  Legend_1e1a_P1[2]->AddEntry(h_1e1a_Data_P1_aOuteIn_Sector6, Num_Events, "");

  sprintf (Num_Events, "%d Events", (int) h_1e1a_Data_P1_aIneIn_Sector6->GetEntries());
  Legend_1e1a_P1[3]->AddEntry(h_1e1a_Data_P1_aIneIn_Sector6, "Data", "lpe");
  Legend_1e1a_P1[3]->AddEntry(h_1e1a_Data_P1_aIneIn_Sector6, Num_Events, "");

  sprintf (Num_Events, "%d Events", (int) h_1e1a_Data_P1_aOuteOut_Sector7->GetEntries());
  Legend_1e1a_P1[4]->AddEntry(h_1e1a_Data_P1_aOuteOut_Sector7, "Data", "lpe");
  Legend_1e1a_P1[4]->AddEntry(h_1e1a_Data_P1_aOuteOut_Sector7, Num_Events, "");

  sprintf (Num_Events, "%d Events", (int) h_1e1a_Data_P1_aIneOut_Sector7->GetEntries());
  Legend_1e1a_P1[5]->AddEntry(h_1e1a_Data_P1_aIneOut_Sector7, "Data", "lpe");
  Legend_1e1a_P1[5]->AddEntry(h_1e1a_Data_P1_aIneOut_Sector7, Num_Events, "");

  sprintf (Num_Events, "%d Events", (int) h_1e1a_Data_P1_aOuteIn_Sector7->GetEntries());
  Legend_1e1a_P1[6]->AddEntry(h_1e1a_Data_P1_aOuteIn_Sector7, "Data", "lpe");
  Legend_1e1a_P1[6]->AddEntry(h_1e1a_Data_P1_aOuteIn_Sector7, Num_Events, "");

  sprintf (Num_Events, "%d Events", (int) h_1e1a_Data_P1_aIneIn_Sector7->GetEntries());
  Legend_1e1a_P1[7]->AddEntry(h_1e1a_Data_P1_aIneIn_Sector7, "Data", "lpe");
  Legend_1e1a_P1[7]->AddEntry(h_1e1a_Data_P1_aIneIn_Sector7, Num_Events, "");

  sprintf (Num_Events, "%d Events", (int) h_1e1a_Data_P1_aOuteOut_Sector8->GetEntries());
  Legend_1e1a_P1[8]->AddEntry(h_1e1a_Data_P1_aOuteOut_Sector8, "Data", "lpe");
  Legend_1e1a_P1[8]->AddEntry(h_1e1a_Data_P1_aOuteOut_Sector8, Num_Events, "");

  sprintf (Num_Events, "%d Events", (int) h_1e1a_Data_P1_aIneOut_Sector8->GetEntries());
  Legend_1e1a_P1[9]->AddEntry(h_1e1a_Data_P1_aIneOut_Sector8, "Data", "lpe");
  Legend_1e1a_P1[9]->AddEntry(h_1e1a_Data_P1_aIneOut_Sector8, Num_Events, "");

  sprintf (Num_Events, "%d Events", (int) h_1e1a_Data_P1_aOuteIn_Sector8->GetEntries());
  Legend_1e1a_P1[10]->AddEntry(h_1e1a_Data_P1_aOuteIn_Sector8, "Data", "lpe");
  Legend_1e1a_P1[10]->AddEntry(h_1e1a_Data_P1_aOuteIn_Sector8, Num_Events, "");

  sprintf (Num_Events, "%d Events", (int) h_1e1a_Data_P1_aIneIn_Sector8->GetEntries());
  Legend_1e1a_P1[11]->AddEntry(h_1e1a_Data_P1_aIneIn_Sector8, "Data", "lpe");
  Legend_1e1a_P1[11]->AddEntry(h_1e1a_Data_P1_aIneIn_Sector8, Num_Events, "");

  sprintf (Num_Events, "%d Events", (int) h_1e1a_Data_P1_AllEvents_Sector6->GetEntries());
  Legend_1e1a_P1[12]->AddEntry(h_1e1a_Data_P1_AllEvents_Sector6, "Data", "lpe");
  Legend_1e1a_P1[12]->AddEntry(h_1e1a_Data_P1_AllEvents_Sector6, Num_Events, "");

  sprintf (Num_Events, "%d Events", (int) h_1e1a_Data_P1_AllEvents_Sector7->GetEntries());
  Legend_1e1a_P1[13]->AddEntry(h_1e1a_Data_P1_AllEvents_Sector7, "Data", "lpe");
  Legend_1e1a_P1[13]->AddEntry(h_1e1a_Data_P1_AllEvents_Sector7, Num_Events, "");

  sprintf (Num_Events, "%d Events", (int) h_1e1a_Data_P1_AllEvents_Sector8->GetEntries());
  Legend_1e1a_P1[14]->AddEntry(h_1e1a_Data_P1_AllEvents_Sector8, "Data", "lpe");
  Legend_1e1a_P1[14]->AddEntry(h_1e1a_Data_P1_AllEvents_Sector8, Num_Events, "");

  sprintf (Num_Events, "%d Events", (int) h_1e1a_Data_P2_aOuteOut_Sector6->GetEntries());
  Legend_1e1a_P2[0]->AddEntry(h_1e1a_Data_P2_aOuteOut_Sector6, "Data", "lpe");
  Legend_1e1a_P2[0]->AddEntry(h_1e1a_Data_P2_aOuteOut_Sector6, Num_Events, "");

  sprintf (Num_Events, "%d Events", (int) h_1e1a_Data_P2_aIneOut_Sector6->GetEntries());
  Legend_1e1a_P2[1]->AddEntry(h_1e1a_Data_P2_aIneOut_Sector6, "Data", "lpe");
  Legend_1e1a_P2[1]->AddEntry(h_1e1a_Data_P2_aIneOut_Sector6, Num_Events, "");

  sprintf (Num_Events, "%d Events", (int) h_1e1a_Data_P2_aOuteIn_Sector6->GetEntries());
  Legend_1e1a_P2[2]->AddEntry(h_1e1a_Data_P2_aOuteIn_Sector6, "Data", "lpe");
  Legend_1e1a_P2[2]->AddEntry(h_1e1a_Data_P2_aOuteIn_Sector6, Num_Events, "");

  sprintf (Num_Events, "%d Events", (int) h_1e1a_Data_P2_aIneIn_Sector6->GetEntries());
  Legend_1e1a_P2[3]->AddEntry(h_1e1a_Data_P2_aIneIn_Sector6, "Data", "lpe");
  Legend_1e1a_P2[3]->AddEntry(h_1e1a_Data_P2_aIneIn_Sector6, Num_Events, "");

  sprintf (Num_Events, "%d Events", (int) h_1e1a_Data_P2_aOuteOut_Sector7->GetEntries());
  Legend_1e1a_P2[4]->AddEntry(h_1e1a_Data_P2_aOuteOut_Sector7, "Data", "lpe");
  Legend_1e1a_P2[4]->AddEntry(h_1e1a_Data_P2_aOuteOut_Sector7, Num_Events, "");

  sprintf (Num_Events, "%d Events", (int) h_1e1a_Data_P2_aIneOut_Sector7->GetEntries());
  Legend_1e1a_P2[5]->AddEntry(h_1e1a_Data_P2_aIneOut_Sector7, "Data", "lpe");
  Legend_1e1a_P2[5]->AddEntry(h_1e1a_Data_P2_aIneOut_Sector7, Num_Events, "");

  sprintf (Num_Events, "%d Events", (int) h_1e1a_Data_P2_aOuteIn_Sector7->GetEntries());
  Legend_1e1a_P2[6]->AddEntry(h_1e1a_Data_P2_aOuteIn_Sector7, "Data", "lpe");
  Legend_1e1a_P2[6]->AddEntry(h_1e1a_Data_P2_aOuteIn_Sector7, Num_Events, "");

  sprintf (Num_Events, "%d Events", (int) h_1e1a_Data_P2_aIneIn_Sector7->GetEntries());
  Legend_1e1a_P2[7]->AddEntry(h_1e1a_Data_P2_aIneIn_Sector7, "Data", "lpe");
  Legend_1e1a_P2[7]->AddEntry(h_1e1a_Data_P2_aIneIn_Sector7, Num_Events, "");

  sprintf (Num_Events, "%d Events", (int) h_1e1a_Data_P2_aOuteOut_Sector8->GetEntries());
  Legend_1e1a_P2[8]->AddEntry(h_1e1a_Data_P2_aOuteOut_Sector8, "Data", "lpe");
  Legend_1e1a_P2[8]->AddEntry(h_1e1a_Data_P2_aOuteOut_Sector8, Num_Events, "");

  sprintf (Num_Events, "%d Events", (int) h_1e1a_Data_P2_aIneOut_Sector8->GetEntries());
  Legend_1e1a_P2[9]->AddEntry(h_1e1a_Data_P2_aIneOut_Sector8, "Data", "lpe");
  Legend_1e1a_P2[9]->AddEntry(h_1e1a_Data_P2_aIneOut_Sector8, Num_Events, "");

  sprintf (Num_Events, "%d Events", (int) h_1e1a_Data_P2_aOuteIn_Sector8->GetEntries());
  Legend_1e1a_P2[10]->AddEntry(h_1e1a_Data_P2_aOuteIn_Sector8, "Data", "lpe");
  Legend_1e1a_P2[10]->AddEntry(h_1e1a_Data_P2_aOuteIn_Sector8, Num_Events, "");

  sprintf (Num_Events, "%d Events", (int) h_1e1a_Data_P2_aIneIn_Sector8->GetEntries());
  Legend_1e1a_P2[11]->AddEntry(h_1e1a_Data_P2_aIneIn_Sector8, "Data", "lpe");
  Legend_1e1a_P2[11]->AddEntry(h_1e1a_Data_P2_aIneIn_Sector8, Num_Events, "");

  sprintf (Num_Events, "%d Events", (int) h_1e1a_Data_P2_AllEvents_Sector6->GetEntries());
  Legend_1e1a_P2[12]->AddEntry(h_1e1a_Data_P2_AllEvents_Sector6, "Data", "lpe");
  Legend_1e1a_P2[12]->AddEntry(h_1e1a_Data_P2_AllEvents_Sector6, Num_Events, "");

  sprintf (Num_Events, "%d Events", (int) h_1e1a_Data_P2_AllEvents_Sector7->GetEntries());
  Legend_1e1a_P2[13]->AddEntry(h_1e1a_Data_P2_AllEvents_Sector7, "Data", "lpe");
  Legend_1e1a_P2[13]->AddEntry(h_1e1a_Data_P2_AllEvents_Sector7, Num_Events, "");

  sprintf (Num_Events, "%d Events", (int) h_1e1a_Data_P2_AllEvents_Sector8->GetEntries());
  Legend_1e1a_P2[14]->AddEntry(h_1e1a_Data_P2_AllEvents_Sector8, "Data", "lpe");
  Legend_1e1a_P2[14]->AddEntry(h_1e1a_Data_P2_AllEvents_Sector8, Num_Events, "");

  for(int j = 0; j < 15; j++){
    TH1 *h;
    TIter   next(StackColl_1e1a_P1[j]->GetHists());
    for(int i = 0; i < 6; i++){
      h = (TH1*) next();
      Legend_1e1a_P1[j]->AddEntry(h, LegIsotopes_P1[i].c_str(), "f");
      Legend_1e1a_P1[j]->AddEntry(h, LegEntries_P1[i].c_str(), "");
    }
  }
  for(int j = 0; j < 15; j++){
    TH1 *h;
    TIter   next(StackColl_1e1a_P2[j]->GetHists());
    for(int i = 0; i < 6; i++){
      h = (TH1*) next();
      Legend_1e1a_P2[j]->AddEntry(h, LegIsotopes_P2[i].c_str(), "f");
      Legend_1e1a_P2[j]->AddEntry(h, LegEntries_P2[i].c_str(), "");
    }
  }

  // Make chi square template
  for(int i = 0; i < 15; i++){
    ChiSquares_1e1a_P1[i] = new TPaveText(0.7007,0.5389,0.8512,0.56995,"LNDC");
    ChiSquares_1e1a_P1[i]->SetFillColor(0);
    ChiSquares_1e1a_P1[i]->SetLineColor(0);
    ChiSquares_1e1a_P1[i]->SetBorderSize(0);
    ChiSquares_1e1a_P1[i]->SetTextAlign(12);
  }
  for(int i = 0; i < 15; i++){
    ChiSquares_1e1a_P2[i] = new TPaveText(0.7007,0.5389,0.8512,0.56995,"LNDC");
    ChiSquares_1e1a_P2[i]->SetFillColor(0);
    ChiSquares_1e1a_P2[i]->SetLineColor(0);
    ChiSquares_1e1a_P2[i]->SetBorderSize(0);
    ChiSquares_1e1a_P2[i]->SetTextAlign(12);
  }

  pair <Double_t, Int_t> ChiSquareResult;
  char ChiSquareText[100];

  ChiSquareResult = ChiSquareTest(h_1e1a_Data_P1_aOuteOut_Sector6, (TH1D*)StackColl_1e1a_P1[0]->GetStack()->Last());
  sprintf(ChiSquareText, "#chi^{2} / ndf = %.2f / %.d", ChiSquareResult.first, ChiSquareResult.second);
  ChiSquares_1e1a_P1[0]->AddText(ChiSquareText);

  ChiSquareResult = ChiSquareTest(h_1e1a_Data_P1_aIneOut_Sector6, (TH1D*)StackColl_1e1a_P1[1]->GetStack()->Last());
  sprintf(ChiSquareText, "#chi^{2} / ndf = %.2f / %.d", ChiSquareResult.first, ChiSquareResult.second);
  ChiSquares_1e1a_P1[1]->AddText(ChiSquareText);

  ChiSquareResult = ChiSquareTest(h_1e1a_Data_P1_aOuteIn_Sector6, (TH1D*)StackColl_1e1a_P1[2]->GetStack()->Last());
  sprintf(ChiSquareText, "#chi^{2} / ndf = %.2f / %.d", ChiSquareResult.first, ChiSquareResult.second);
  ChiSquares_1e1a_P1[2]->AddText(ChiSquareText);

  ChiSquareResult = ChiSquareTest(h_1e1a_Data_P1_aIneIn_Sector6, (TH1D*)StackColl_1e1a_P1[3]->GetStack()->Last());
  sprintf(ChiSquareText, "#chi^{2} / ndf = %.2f / %.d", ChiSquareResult.first, ChiSquareResult.second);
  ChiSquares_1e1a_P1[3]->AddText(ChiSquareText);

  ChiSquareResult = ChiSquareTest(h_1e1a_Data_P1_aOuteOut_Sector7, (TH1D*)StackColl_1e1a_P1[4]->GetStack()->Last());
  sprintf(ChiSquareText, "#chi^{2} / ndf = %.2f / %.d", ChiSquareResult.first, ChiSquareResult.second);
  ChiSquares_1e1a_P1[4]->AddText(ChiSquareText);

  ChiSquareResult = ChiSquareTest(h_1e1a_Data_P1_aIneOut_Sector7, (TH1D*)StackColl_1e1a_P1[5]->GetStack()->Last());
  sprintf(ChiSquareText, "#chi^{2} / ndf = %.2f / %.d", ChiSquareResult.first, ChiSquareResult.second);
  ChiSquares_1e1a_P1[5]->AddText(ChiSquareText);

  ChiSquareResult = ChiSquareTest(h_1e1a_Data_P1_aOuteIn_Sector7, (TH1D*)StackColl_1e1a_P1[6]->GetStack()->Last());
  sprintf(ChiSquareText, "#chi^{2} / ndf = %.2f / %.d", ChiSquareResult.first, ChiSquareResult.second);
  ChiSquares_1e1a_P1[6]->AddText(ChiSquareText);

  ChiSquareResult = ChiSquareTest(h_1e1a_Data_P1_aIneIn_Sector7, (TH1D*)StackColl_1e1a_P1[7]->GetStack()->Last());
  sprintf(ChiSquareText, "#chi^{2} / ndf = %.2f / %.d", ChiSquareResult.first, ChiSquareResult.second);
  ChiSquares_1e1a_P1[7]->AddText(ChiSquareText);

  ChiSquareResult = ChiSquareTest(h_1e1a_Data_P1_aOuteOut_Sector8, (TH1D*)StackColl_1e1a_P1[8]->GetStack()->Last());
  sprintf(ChiSquareText, "#chi^{2} / ndf = %.2f / %.d", ChiSquareResult.first, ChiSquareResult.second);
  ChiSquares_1e1a_P1[8]->AddText(ChiSquareText);

  ChiSquareResult = ChiSquareTest(h_1e1a_Data_P1_aIneOut_Sector8, (TH1D*)StackColl_1e1a_P1[9]->GetStack()->Last());
  sprintf(ChiSquareText, "#chi^{2} / ndf = %.2f / %.d", ChiSquareResult.first, ChiSquareResult.second);
  ChiSquares_1e1a_P1[9]->AddText(ChiSquareText);

  ChiSquareResult = ChiSquareTest(h_1e1a_Data_P1_aOuteIn_Sector8, (TH1D*)StackColl_1e1a_P1[10]->GetStack()->Last());
  sprintf(ChiSquareText, "#chi^{2} / ndf = %.2f / %.d", ChiSquareResult.first, ChiSquareResult.second);
  ChiSquares_1e1a_P1[10]->AddText(ChiSquareText);

  ChiSquareResult = ChiSquareTest(h_1e1a_Data_P1_aIneIn_Sector8, (TH1D*)StackColl_1e1a_P1[11]->GetStack()->Last());
  sprintf(ChiSquareText, "#chi^{2} / ndf = %.2f / %.d", ChiSquareResult.first, ChiSquareResult.second);
  ChiSquares_1e1a_P1[11]->AddText(ChiSquareText);

  ChiSquareResult = ChiSquareTest(h_1e1a_Data_P1_AllEvents_Sector6, (TH1D*)StackColl_1e1a_P1[12]->GetStack()->Last());
  sprintf(ChiSquareText, "#chi^{2} / ndf = %.2f / %.d", ChiSquareResult.first, ChiSquareResult.second);
  ChiSquares_1e1a_P1[12]->AddText(ChiSquareText);

  ChiSquareResult = ChiSquareTest(h_1e1a_Data_P1_AllEvents_Sector7, (TH1D*)StackColl_1e1a_P1[13]->GetStack()->Last());
  sprintf(ChiSquareText, "#chi^{2} / ndf = %.2f / %.d", ChiSquareResult.first, ChiSquareResult.second);
  ChiSquares_1e1a_P1[13]->AddText(ChiSquareText);

  ChiSquareResult = ChiSquareTest(h_1e1a_Data_P1_AllEvents_Sector8, (TH1D*)StackColl_1e1a_P1[14]->GetStack()->Last());
  sprintf(ChiSquareText, "#chi^{2} / ndf = %.2f / %.d", ChiSquareResult.first, ChiSquareResult.second);
  ChiSquares_1e1a_P1[14]->AddText(ChiSquareText);

  ChiSquareResult = ChiSquareTest(h_1e1a_Data_P2_aOuteOut_Sector6, (TH1D*)StackColl_1e1a_P2[0]->GetStack()->Last());
  sprintf(ChiSquareText, "#chi^{2} / ndf = %.2f / %.d", ChiSquareResult.first, ChiSquareResult.second);
  ChiSquares_1e1a_P2[0]->AddText(ChiSquareText);

  ChiSquareResult = ChiSquareTest(h_1e1a_Data_P2_aIneOut_Sector6, (TH1D*)StackColl_1e1a_P2[1]->GetStack()->Last());
  sprintf(ChiSquareText, "#chi^{2} / ndf = %.2f / %.d", ChiSquareResult.first, ChiSquareResult.second);
  ChiSquares_1e1a_P2[1]->AddText(ChiSquareText);

  ChiSquareResult = ChiSquareTest(h_1e1a_Data_P2_aOuteIn_Sector6, (TH1D*)StackColl_1e1a_P2[2]->GetStack()->Last());
  sprintf(ChiSquareText, "#chi^{2} / ndf = %.2f / %.d", ChiSquareResult.first, ChiSquareResult.second);
  ChiSquares_1e1a_P2[2]->AddText(ChiSquareText);

  ChiSquareResult = ChiSquareTest(h_1e1a_Data_P2_aIneIn_Sector6, (TH1D*)StackColl_1e1a_P2[3]->GetStack()->Last());
  sprintf(ChiSquareText, "#chi^{2} / ndf = %.2f / %.d", ChiSquareResult.first, ChiSquareResult.second);
  ChiSquares_1e1a_P2[3]->AddText(ChiSquareText);

  ChiSquareResult = ChiSquareTest(h_1e1a_Data_P2_aOuteOut_Sector7, (TH1D*)StackColl_1e1a_P2[4]->GetStack()->Last());
  sprintf(ChiSquareText, "#chi^{2} / ndf = %.2f / %.d", ChiSquareResult.first, ChiSquareResult.second);
  ChiSquares_1e1a_P2[4]->AddText(ChiSquareText);

  ChiSquareResult = ChiSquareTest(h_1e1a_Data_P2_aIneOut_Sector7, (TH1D*)StackColl_1e1a_P2[5]->GetStack()->Last());
  sprintf(ChiSquareText, "#chi^{2} / ndf = %.2f / %.d", ChiSquareResult.first, ChiSquareResult.second);
  ChiSquares_1e1a_P2[5]->AddText(ChiSquareText);

  ChiSquareResult = ChiSquareTest(h_1e1a_Data_P2_aOuteIn_Sector7, (TH1D*)StackColl_1e1a_P2[6]->GetStack()->Last());
  sprintf(ChiSquareText, "#chi^{2} / ndf = %.2f / %.d", ChiSquareResult.first, ChiSquareResult.second);
  ChiSquares_1e1a_P2[6]->AddText(ChiSquareText);

  ChiSquareResult = ChiSquareTest(h_1e1a_Data_P2_aIneIn_Sector7, (TH1D*)StackColl_1e1a_P2[7]->GetStack()->Last());
  sprintf(ChiSquareText, "#chi^{2} / ndf = %.2f / %.d", ChiSquareResult.first, ChiSquareResult.second);
  ChiSquares_1e1a_P2[7]->AddText(ChiSquareText);

  ChiSquareResult = ChiSquareTest(h_1e1a_Data_P2_aOuteOut_Sector8, (TH1D*)StackColl_1e1a_P2[8]->GetStack()->Last());
  sprintf(ChiSquareText, "#chi^{2} / ndf = %.2f / %.d", ChiSquareResult.first, ChiSquareResult.second);
  ChiSquares_1e1a_P2[8]->AddText(ChiSquareText);

  ChiSquareResult = ChiSquareTest(h_1e1a_Data_P2_aIneOut_Sector8, (TH1D*)StackColl_1e1a_P2[9]->GetStack()->Last());
  sprintf(ChiSquareText, "#chi^{2} / ndf = %.2f / %.d", ChiSquareResult.first, ChiSquareResult.second);
  ChiSquares_1e1a_P2[9]->AddText(ChiSquareText);

  ChiSquareResult = ChiSquareTest(h_1e1a_Data_P2_aOuteIn_Sector8, (TH1D*)StackColl_1e1a_P2[10]->GetStack()->Last());
  sprintf(ChiSquareText, "#chi^{2} / ndf = %.2f / %.d", ChiSquareResult.first, ChiSquareResult.second);
  ChiSquares_1e1a_P2[10]->AddText(ChiSquareText);

  ChiSquareResult = ChiSquareTest(h_1e1a_Data_P2_aIneIn_Sector8, (TH1D*)StackColl_1e1a_P2[11]->GetStack()->Last());
  sprintf(ChiSquareText, "#chi^{2} / ndf = %.2f / %.d", ChiSquareResult.first, ChiSquareResult.second);
  ChiSquares_1e1a_P2[11]->AddText(ChiSquareText);

  ChiSquareResult = ChiSquareTest(h_1e1a_Data_P2_AllEvents_Sector6, (TH1D*)StackColl_1e1a_P2[12]->GetStack()->Last());
  sprintf(ChiSquareText, "#chi^{2} / ndf = %.2f / %.d", ChiSquareResult.first, ChiSquareResult.second);
  ChiSquares_1e1a_P2[12]->AddText(ChiSquareText);

  ChiSquareResult = ChiSquareTest(h_1e1a_Data_P2_AllEvents_Sector7, (TH1D*)StackColl_1e1a_P2[13]->GetStack()->Last());
  sprintf(ChiSquareText, "#chi^{2} / ndf = %.2f / %.d", ChiSquareResult.first, ChiSquareResult.second);
  ChiSquares_1e1a_P2[13]->AddText(ChiSquareText);

  ChiSquareResult = ChiSquareTest(h_1e1a_Data_P2_AllEvents_Sector8, (TH1D*)StackColl_1e1a_P2[14]->GetStack()->Last());
  sprintf(ChiSquareText, "#chi^{2} / ndf = %.2f / %.d", ChiSquareResult.first, ChiSquareResult.second);
  ChiSquares_1e1a_P2[14]->AddText(ChiSquareText);
 
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
