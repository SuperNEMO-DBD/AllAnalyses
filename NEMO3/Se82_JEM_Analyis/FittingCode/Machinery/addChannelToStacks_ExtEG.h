#ifndef ADDCHANNELTOSTACKS_EXTEG_H
#define ADDCHANNELTOSTACKS_EXTEG_H

void addChannelToStacks_ExtEG(string SampleName, Double_t ScaleFactor, Int_t FillColor, THStack* FillStackColl[], TFile* infile){

  char buffer[200];

  TH1D* h_P1_ExtEG_Inner; 
  TH1D* h_P1_ExtEG_Outer; 
  TH1D* h_P1_ExtEG_Petal; 
  TH1D* h_P2_ExtEG_Inner; 
  TH1D* h_P2_ExtEG_Outer; 
  TH1D* h_P2_ExtEG_Petal; 

  if(std::string::npos != SampleName.find("P1") || std::string::npos != SampleName.find("P2") ){
    strcpy(buffer,"hTotEnergy_");
    h_P1_ExtEG_Inner = (TH1D*)infile->Get(strcat(buffer,(SampleName+"_Inner").c_str()));
    strcpy(buffer,"hTotEnergy_");
    h_P1_ExtEG_Outer = (TH1D*)infile->Get(strcat(buffer,(SampleName+"_Outer").c_str()));
    strcpy(buffer,"hTotEnergy_");
    h_P1_ExtEG_Petal = (TH1D*)infile->Get(strcat(buffer,(SampleName+"_Petal").c_str()));
    strcpy(buffer,"hTotEnergy_");
    h_P2_ExtEG_Inner = (TH1D*)infile->Get(strcat(buffer,(SampleName+"_Inner").c_str()));
    strcpy(buffer,"hTotEnergy_");
    h_P2_ExtEG_Outer = (TH1D*)infile->Get(strcat(buffer,(SampleName+"_Outer").c_str()));
    strcpy(buffer,"hTotEnergy_");
    h_P2_ExtEG_Petal = (TH1D*)infile->Get(strcat(buffer,(SampleName+"_Petal").c_str()));
  } else {
    strcpy(buffer,"hTotEnergy_");
    h_P1_ExtEG_Inner = (TH1D*)infile->Get(strcat(buffer,(SampleName+"_P1_Inner").c_str()));
    strcpy(buffer,"hTotEnergy_");
    h_P1_ExtEG_Outer = (TH1D*)infile->Get(strcat(buffer,(SampleName+"_P1_Outer").c_str()));
    strcpy(buffer,"hTotEnergy_");
    h_P1_ExtEG_Petal = (TH1D*)infile->Get(strcat(buffer,(SampleName+"_P1_Petal").c_str()));
    strcpy(buffer,"hTotEnergy_");
    h_P2_ExtEG_Inner = (TH1D*)infile->Get(strcat(buffer,(SampleName+"_P2_Inner").c_str()));
    strcpy(buffer,"hTotEnergy_");
    h_P2_ExtEG_Outer = (TH1D*)infile->Get(strcat(buffer,(SampleName+"_P2_Outer").c_str()));
    strcpy(buffer,"hTotEnergy_");
    h_P2_ExtEG_Petal = (TH1D*)infile->Get(strcat(buffer,(SampleName+"_P2_Petal").c_str()));
  }

  if(h_P1_ExtEG_Inner==0)    {cout << "ERROR:  hTotEnergy_"  << SampleName << "_P1_Inner not found"     << endl; exit(0);}
  if(h_P1_ExtEG_Outer==0)    {cout << "ERROR:  hTotEnergy_"  << SampleName << "_P1_Outer not found"     << endl; exit(0);}
  if(h_P1_ExtEG_Petal==0)    {cout << "ERROR:  hTotEnergy_"  << SampleName << "_P1_Petal not found"     << endl; exit(0);}
  if(h_P2_ExtEG_Inner==0)    {cout << "ERROR:  hTotEnergy_"  << SampleName << "_P2_Inner not found"     << endl; exit(0);}
  if(h_P2_ExtEG_Outer==0)    {cout << "ERROR:  hTotEnergy_"  << SampleName << "_P2_Outer not found"     << endl; exit(0);}
  if(h_P2_ExtEG_Petal==0)    {cout << "ERROR:  hTotEnergy_"  << SampleName << "_P2_Petal not found"     << endl; exit(0);}

  TH1D* h_P1_ExtEG_Inner_Clone    = (TH1D*)h_P1_ExtEG_Inner  ->Clone("h_P1_ExtEG_Inner_Clone");
  TH1D* h_P1_ExtEG_Outer_Clone    = (TH1D*)h_P1_ExtEG_Outer  ->Clone("h_P1_ExtEG_Outer_Clone");
  TH1D* h_P1_ExtEG_Petal_Clone    = (TH1D*)h_P1_ExtEG_Petal  ->Clone("h_P1_ExtEG_Petal_Clone");
  TH1D* h_P2_ExtEG_Inner_Clone    = (TH1D*)h_P2_ExtEG_Inner  ->Clone("h_P2_ExtEG_Inner_Clone");
  TH1D* h_P2_ExtEG_Outer_Clone    = (TH1D*)h_P2_ExtEG_Outer  ->Clone("h_P2_ExtEG_Outer_Clone");
  TH1D* h_P2_ExtEG_Petal_Clone    = (TH1D*)h_P2_ExtEG_Petal  ->Clone("h_P2_ExtEG_Petal_Clone");

  h_P1_ExtEG_Inner_Clone   ->Scale(ScaleFactor);
  h_P1_ExtEG_Outer_Clone   ->Scale(ScaleFactor);
  h_P1_ExtEG_Petal_Clone   ->Scale(ScaleFactor);
  h_P2_ExtEG_Inner_Clone   ->Scale(ScaleFactor);
  h_P2_ExtEG_Outer_Clone   ->Scale(ScaleFactor);
  h_P2_ExtEG_Petal_Clone   ->Scale(ScaleFactor);

  h_P1_ExtEG_Inner_Clone   ->SetFillColor(FillColor);
  h_P1_ExtEG_Outer_Clone   ->SetFillColor(FillColor);
  h_P1_ExtEG_Petal_Clone   ->SetFillColor(FillColor);
  h_P2_ExtEG_Inner_Clone   ->SetFillColor(FillColor);
  h_P2_ExtEG_Outer_Clone   ->SetFillColor(FillColor);
  h_P2_ExtEG_Petal_Clone   ->SetFillColor(FillColor);

  if(std::string::npos != SampleName.find("P2")){
    FillStackColl[3]-> Add(h_P2_ExtEG_Inner_Clone); 
    FillStackColl[4]-> Add(h_P2_ExtEG_Outer_Clone); 
    FillStackColl[5]-> Add(h_P2_ExtEG_Petal_Clone); 
  } else if(std::string::npos != SampleName.find("P1")){
    FillStackColl[0]-> Add(h_P1_ExtEG_Inner_Clone); 
    FillStackColl[1]-> Add(h_P1_ExtEG_Outer_Clone); 
    FillStackColl[2]-> Add(h_P1_ExtEG_Petal_Clone); 
  } else {
    FillStackColl[0]-> Add(h_P1_ExtEG_Inner_Clone); 
    FillStackColl[1]-> Add(h_P1_ExtEG_Outer_Clone); 
    FillStackColl[2]-> Add(h_P1_ExtEG_Petal_Clone); 
    FillStackColl[3]-> Add(h_P2_ExtEG_Inner_Clone); 
    FillStackColl[4]-> Add(h_P2_ExtEG_Outer_Clone); 
    FillStackColl[5]-> Add(h_P2_ExtEG_Petal_Clone); 
  }

}

#endif
