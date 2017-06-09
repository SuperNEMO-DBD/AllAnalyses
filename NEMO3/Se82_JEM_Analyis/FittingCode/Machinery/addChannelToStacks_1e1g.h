#ifndef ADDCHANNELTOSTACKS_1E1G_H
#define ADDCHANNELTOSTACKS_1E1G_H

void addChannelToStacks_1e1g(string SampleName, Double_t ScaleFactor, Int_t FillColor, THStack* FillStackColl[], TFile* infile){

  char buffer[200];

  TH1D* h_P1_1e1g_SeOld; 
  TH1D* h_P1_1e1g_SeNew;
  TH1D* h_P1_1e1g_Strip;
  TH1D* h_P2_1e1g_SeOld; 
  TH1D* h_P2_1e1g_SeNew;
  TH1D* h_P2_1e1g_Strip;

  if(std::string::npos != SampleName.find("P1") || std::string::npos != SampleName.find("P2") ){
    strcpy(buffer,"hEnergySum_");
    h_P1_1e1g_SeOld    = (TH1D*)infile->Get(strcat(buffer,(SampleName+"_SeOld").c_str()));
    strcpy(buffer,"hEnergySum_");
    h_P1_1e1g_SeNew    = (TH1D*)infile->Get(strcat(buffer,(SampleName+"_SeNew").c_str()));
    strcpy(buffer,"hEnergySum_");
    h_P1_1e1g_Strip    = (TH1D*)infile->Get(strcat(buffer,(SampleName+"_Strip").c_str()));
    strcpy(buffer,"hEnergySum_");
    h_P2_1e1g_SeOld    = (TH1D*)infile->Get(strcat(buffer,(SampleName+"_SeOld").c_str()));
    strcpy(buffer,"hEnergySum_");
    h_P2_1e1g_SeNew    = (TH1D*)infile->Get(strcat(buffer,(SampleName+"_SeNew").c_str()));
    strcpy(buffer,"hEnergySum_");
    h_P2_1e1g_Strip    = (TH1D*)infile->Get(strcat(buffer,(SampleName+"_Strip").c_str()));
  } else {
    strcpy(buffer,"hEnergySum_");
    h_P1_1e1g_SeOld    = (TH1D*)infile->Get(strcat(buffer,(SampleName+"_P1_SeOld").c_str()));
    strcpy(buffer,"hEnergySum_");
    h_P1_1e1g_SeNew    = (TH1D*)infile->Get(strcat(buffer,(SampleName+"_P1_SeNew").c_str()));
    strcpy(buffer,"hEnergySum_");
    h_P1_1e1g_Strip    = (TH1D*)infile->Get(strcat(buffer,(SampleName+"_P1_Strip").c_str()));
    strcpy(buffer,"hEnergySum_");
    h_P2_1e1g_SeOld    = (TH1D*)infile->Get(strcat(buffer,(SampleName+"_P2_SeOld").c_str()));
    strcpy(buffer,"hEnergySum_");
    h_P2_1e1g_SeNew    = (TH1D*)infile->Get(strcat(buffer,(SampleName+"_P2_SeNew").c_str()));
    strcpy(buffer,"hEnergySum_");
    h_P2_1e1g_Strip    = (TH1D*)infile->Get(strcat(buffer,(SampleName+"_P2_Strip").c_str()));
  }

  if(h_P1_1e1g_SeOld==0)    {cout << "ERROR:  hEnergySum_"  << SampleName << "_P1_SeOld not found"     << endl; exit(0);}
  if(h_P1_1e1g_SeNew==0)    {cout << "ERROR:  hEnergySum_"  << SampleName << "_P1_SeNew not found"     << endl; exit(0);}
  if(h_P1_1e1g_Strip==0)    {cout << "ERROR:  hEnergySum_"  << SampleName << "_P1_Strip not found"     << endl; exit(0);}
  if(h_P2_1e1g_SeOld==0)    {cout << "ERROR:  hEnergySum_"  << SampleName << "_P2_SeOld not found"     << endl; exit(0);}
  if(h_P2_1e1g_SeNew==0)    {cout << "ERROR:  hEnergySum_"  << SampleName << "_P2_SeNew not found"     << endl; exit(0);}
  if(h_P2_1e1g_Strip==0)    {cout << "ERROR:  hEnergySum_"  << SampleName << "_P2_Strip not found"     << endl; exit(0);}

  TH1D* h_P1_1e1g_SeOld_Clone    = (TH1D*)h_P1_1e1g_SeOld  ->Clone("h_P1_1e1g_SeOld_Clone");
  TH1D* h_P1_1e1g_SeNew_Clone    = (TH1D*)h_P1_1e1g_SeNew  ->Clone("h_P1_1e1g_SeNew_Clone");
  TH1D* h_P1_1e1g_Strip_Clone    = (TH1D*)h_P1_1e1g_Strip  ->Clone("h_P1_1e1g_Strip_Clone");
  TH1D* h_P2_1e1g_SeOld_Clone    = (TH1D*)h_P2_1e1g_SeOld  ->Clone("h_P2_1e1g_SeOld_Clone");
  TH1D* h_P2_1e1g_SeNew_Clone    = (TH1D*)h_P2_1e1g_SeNew  ->Clone("h_P2_1e1g_SeNew_Clone");
  TH1D* h_P2_1e1g_Strip_Clone    = (TH1D*)h_P2_1e1g_Strip  ->Clone("h_P2_1e1g_Strip_Clone");

  h_P1_1e1g_SeOld_Clone   ->Scale(ScaleFactor);
  h_P1_1e1g_SeNew_Clone   ->Scale(ScaleFactor);
  h_P1_1e1g_Strip_Clone   ->Scale(ScaleFactor);
  h_P2_1e1g_SeOld_Clone   ->Scale(ScaleFactor);
  h_P2_1e1g_SeNew_Clone   ->Scale(ScaleFactor);
  h_P2_1e1g_Strip_Clone   ->Scale(ScaleFactor);

  h_P1_1e1g_SeOld_Clone   ->SetFillColor(FillColor);
  h_P1_1e1g_SeNew_Clone   ->SetFillColor(FillColor);
  h_P1_1e1g_Strip_Clone   ->SetFillColor(FillColor);
  h_P2_1e1g_SeOld_Clone   ->SetFillColor(FillColor);
  h_P2_1e1g_SeNew_Clone   ->SetFillColor(FillColor);
  h_P2_1e1g_Strip_Clone   ->SetFillColor(FillColor);


  if(std::string::npos != SampleName.find("P2")){
    FillStackColl[3]-> Add(h_P2_1e1g_SeOld_Clone); 
    FillStackColl[4]-> Add(h_P2_1e1g_SeNew_Clone);
    FillStackColl[5]-> Add(h_P2_1e1g_Strip_Clone);
  } else if(std::string::npos != SampleName.find("P1")){
    FillStackColl[0]-> Add(h_P1_1e1g_SeOld_Clone); 
    FillStackColl[1]-> Add(h_P1_1e1g_SeNew_Clone);
    FillStackColl[2]-> Add(h_P1_1e1g_Strip_Clone);
  } else {
    FillStackColl[0]-> Add(h_P1_1e1g_SeOld_Clone); 
    FillStackColl[1]-> Add(h_P1_1e1g_SeNew_Clone);
    FillStackColl[2]-> Add(h_P1_1e1g_Strip_Clone);
    FillStackColl[3]-> Add(h_P2_1e1g_SeOld_Clone); 
    FillStackColl[4]-> Add(h_P2_1e1g_SeNew_Clone);
    FillStackColl[5]-> Add(h_P2_1e1g_Strip_Clone);
  }

}

#endif
