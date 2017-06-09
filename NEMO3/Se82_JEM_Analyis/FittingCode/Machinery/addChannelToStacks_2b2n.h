#ifndef ADDCHANNELTOSTACKS_2B2N_H
#define ADDCHANNELTOSTACKS_2B2N_H

void addChannelToStacks_2b2n(string SampleName, Double_t ScaleFactor, Int_t FillColor, THStack* FillStackColl[], TFile* infile){

  char buffer[200];

  TH1D* h_2b2n_SeOld; 
  TH1D* h_2b2n_SeNew; 
  TH1D* h_2b2n_SingleEnergy_SeOld; 
  TH1D* h_2b2n_SingleEnergy_SeNew; 
  TH1D* h_2b2n_MinEnergy_SeOld; 
  TH1D* h_2b2n_MinEnergy_SeNew; 
  TH1D* h_2b2n_MaxEnergy_SeOld; 
  TH1D* h_2b2n_MaxEnergy_SeNew; 

  strcpy(buffer,"hTotEnergySeOld_");
  h_2b2n_SeOld = (TH1D*)infile->Get(strcat(buffer,SampleName.c_str()));
  strcpy(buffer,"hTotEnergySeNew_");
  h_2b2n_SeNew = (TH1D*)infile->Get(strcat(buffer,SampleName.c_str()));
  strcpy(buffer,"hSingleEnergySeOld_");
  h_2b2n_SingleEnergy_SeOld = (TH1D*)infile->Get(strcat(buffer,SampleName.c_str()));
  strcpy(buffer,"hSingleEnergySeNew_");
  h_2b2n_SingleEnergy_SeNew = (TH1D*)infile->Get(strcat(buffer,SampleName.c_str()));
  strcpy(buffer,"hMinEnergySeOld_");
  h_2b2n_MinEnergy_SeOld = (TH1D*)infile->Get(strcat(buffer,SampleName.c_str()));
  strcpy(buffer,"hMinEnergySeNew_");
  h_2b2n_MinEnergy_SeNew = (TH1D*)infile->Get(strcat(buffer,SampleName.c_str()));
  strcpy(buffer,"hMaxEnergySeOld_");
  h_2b2n_MaxEnergy_SeOld = (TH1D*)infile->Get(strcat(buffer,SampleName.c_str()));
  strcpy(buffer,"hMaxEnergySeNew_");
  h_2b2n_MaxEnergy_SeNew = (TH1D*)infile->Get(strcat(buffer,SampleName.c_str()));

  if(h_2b2n_SeOld==0) {cout << "ERROR:  hTotEnergySeOld_"  << SampleName << " not found"     << endl; exit(0);}
  if(h_2b2n_SeNew==0) {cout << "ERROR:  hTotEnergySeNew_"  << SampleName << " not found"     << endl; exit(0);}
  if(h_2b2n_SingleEnergy_SeOld==0) {cout << "ERROR:  hSingleEnergySeOld_"  << SampleName << " not found"     << endl; exit(0);}
  if(h_2b2n_SingleEnergy_SeNew==0) {cout << "ERROR:  hSingleEnergySeNew_"  << SampleName << " not found"     << endl; exit(0);}
  if(h_2b2n_MinEnergy_SeOld==0) {cout << "ERROR:  hMinEnergySeOld_"  << SampleName << " not found"     << endl; exit(0);}
  if(h_2b2n_MinEnergy_SeNew==0) {cout << "ERROR:  hMinEnergySeNew_"  << SampleName << " not found"     << endl; exit(0);}
  if(h_2b2n_MaxEnergy_SeOld==0) {cout << "ERROR:  hMaxEnergySeOld_"  << SampleName << " not found"     << endl; exit(0);}
  if(h_2b2n_MaxEnergy_SeNew==0) {cout << "ERROR:  hMaxEnergySeNew_"  << SampleName << " not found"     << endl; exit(0);}

  TH1D* h_2b2n_SeOld_Clone = (TH1D*)h_2b2n_SeOld ->Clone("h_2b2n_SeOld_Clone");
  TH1D* h_2b2n_SeNew_Clone = (TH1D*)h_2b2n_SeNew ->Clone("h_2b2n_SeNew_Clone");
  TH1D* h_2b2n_SingleEnergy_SeOld_Clone = (TH1D*)h_2b2n_SingleEnergy_SeOld ->Clone("h_2b2n_SingleEnergy_SeOld_Clone");
  TH1D* h_2b2n_SingleEnergy_SeNew_Clone = (TH1D*)h_2b2n_SingleEnergy_SeNew ->Clone("h_2b2n_SingleEnergy_SeNew_Clone");
  TH1D* h_2b2n_MinEnergy_SeOld_Clone = (TH1D*)h_2b2n_MinEnergy_SeOld ->Clone("h_2b2n_MinEnergy_SeOld_Clone");
  TH1D* h_2b2n_MinEnergy_SeNew_Clone = (TH1D*)h_2b2n_MinEnergy_SeNew ->Clone("h_2b2n_MinEnergy_SeNew_Clone");
  TH1D* h_2b2n_MaxEnergy_SeOld_Clone = (TH1D*)h_2b2n_MaxEnergy_SeOld ->Clone("h_2b2n_MaxEnergy_SeOld_Clone");
  TH1D* h_2b2n_MaxEnergy_SeNew_Clone = (TH1D*)h_2b2n_MaxEnergy_SeNew ->Clone("h_2b2n_MaxEnergy_SeNew_Clone");

  h_2b2n_SeOld_Clone->Scale(ScaleFactor);
  h_2b2n_SeNew_Clone->Scale(ScaleFactor);
  h_2b2n_SingleEnergy_SeOld_Clone->Scale(ScaleFactor);
  h_2b2n_SingleEnergy_SeNew_Clone->Scale(ScaleFactor);
  h_2b2n_MinEnergy_SeOld_Clone->Scale(ScaleFactor);
  h_2b2n_MinEnergy_SeNew_Clone->Scale(ScaleFactor);
  h_2b2n_MaxEnergy_SeOld_Clone->Scale(ScaleFactor);
  h_2b2n_MaxEnergy_SeNew_Clone->Scale(ScaleFactor);

  h_2b2n_SeOld_Clone->SetFillColor(FillColor);
  h_2b2n_SeNew_Clone->SetFillColor(FillColor);
  h_2b2n_SingleEnergy_SeOld_Clone->SetFillColor(FillColor);
  h_2b2n_SingleEnergy_SeNew_Clone->SetFillColor(FillColor);
  h_2b2n_MinEnergy_SeOld_Clone->SetFillColor(FillColor);
  h_2b2n_MinEnergy_SeNew_Clone->SetFillColor(FillColor);
  h_2b2n_MaxEnergy_SeOld_Clone->SetFillColor(FillColor);
  h_2b2n_MaxEnergy_SeNew_Clone->SetFillColor(FillColor);

  FillStackColl[0]-> Add(h_2b2n_SeOld_Clone);
  FillStackColl[1]-> Add(h_2b2n_SeNew_Clone);
  FillStackColl[2]-> Add(h_2b2n_SingleEnergy_SeOld_Clone);
  FillStackColl[3]-> Add(h_2b2n_SingleEnergy_SeNew_Clone);
  FillStackColl[4]-> Add(h_2b2n_MinEnergy_SeOld_Clone);
  FillStackColl[5]-> Add(h_2b2n_MinEnergy_SeNew_Clone);
  FillStackColl[6]-> Add(h_2b2n_MaxEnergy_SeOld_Clone);
  FillStackColl[7]-> Add(h_2b2n_MaxEnergy_SeNew_Clone);

}

#endif
