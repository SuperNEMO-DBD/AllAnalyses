#ifndef ADDCHANNELTOSTACKS_1E1A_H
#define ADDCHANNELTOSTACKS_1E1A_H

void addChannelToStacks_1e1a(string SampleName, Double_t ScaleFactor, Int_t FillColor, THStack* FillStackColl[], TFile* infile){

  char buffer[200];

  strcpy(buffer,"hAlphaLength_");
  TH1D* hAlphaLength_aOuteOut_Sector6 = (TH1D*)infile->Get(strcat(buffer,(SampleName+"_aOuteOut_Sector6").c_str()));
  strcpy(buffer,"hAlphaLength_");
  TH1D* hAlphaLength_aIneOut_Sector6  = (TH1D*)infile->Get(strcat(buffer,(SampleName+"_aIneOut_Sector6").c_str()));
  strcpy(buffer,"hAlphaLength_");
  TH1D* hAlphaLength_aOuteIn_Sector6  = (TH1D*)infile->Get(strcat(buffer,(SampleName+"_aOuteIn_Sector6").c_str()));
  strcpy(buffer,"hAlphaLength_");
  TH1D* hAlphaLength_aIneIn_Sector6   = (TH1D*)infile->Get(strcat(buffer,(SampleName+"_aIneIn_Sector6").c_str()));
  strcpy(buffer,"hAlphaLength_");
  TH1D* hAlphaLength_aOuteOut_Sector7 = (TH1D*)infile->Get(strcat(buffer,(SampleName+"_aOuteOut_Sector7").c_str()));
  strcpy(buffer,"hAlphaLength_");
  TH1D* hAlphaLength_aIneOut_Sector7  = (TH1D*)infile->Get(strcat(buffer,(SampleName+"_aIneOut_Sector7").c_str()));
  strcpy(buffer,"hAlphaLength_");
  TH1D* hAlphaLength_aOuteIn_Sector7  = (TH1D*)infile->Get(strcat(buffer,(SampleName+"_aOuteIn_Sector7").c_str()));
  strcpy(buffer,"hAlphaLength_");
  TH1D* hAlphaLength_aIneIn_Sector7   = (TH1D*)infile->Get(strcat(buffer,(SampleName+"_aIneIn_Sector7").c_str()));
  strcpy(buffer,"hAlphaLength_");
  TH1D* hAlphaLength_aOuteOut_Sector8 = (TH1D*)infile->Get(strcat(buffer,(SampleName+"_aOuteOut_Sector8").c_str()));
  strcpy(buffer,"hAlphaLength_");
  TH1D* hAlphaLength_aIneOut_Sector8  = (TH1D*)infile->Get(strcat(buffer,(SampleName+"_aIneOut_Sector8").c_str()));
  strcpy(buffer,"hAlphaLength_");
  TH1D* hAlphaLength_aOuteIn_Sector8  = (TH1D*)infile->Get(strcat(buffer,(SampleName+"_aOuteIn_Sector8").c_str()));
  strcpy(buffer,"hAlphaLength_");
  TH1D* hAlphaLength_aIneIn_Sector8   = (TH1D*)infile->Get(strcat(buffer,(SampleName+"_aIneIn_Sector8").c_str()));
  strcpy(buffer,"hAlphaLength_");
  TH1D* hAlphaLength_AllEvents_Sector6= (TH1D*)infile->Get(strcat(buffer,(SampleName+"_AllEvents_Sector6").c_str()));
  strcpy(buffer,"hAlphaLength_");
  TH1D* hAlphaLength_AllEvents_Sector7= (TH1D*)infile->Get(strcat(buffer,(SampleName+"_AllEvents_Sector7").c_str()));
  strcpy(buffer,"hAlphaLength_");
  TH1D* hAlphaLength_AllEvents_Sector8= (TH1D*)infile->Get(strcat(buffer,(SampleName+"_AllEvents_Sector8").c_str()));

  if(hAlphaLength_aOuteOut_Sector6==0) {cout << "ERROR: hAlphaLength_" << SampleName << "_aOuteOut_Sector6  not found"   << endl; exit(0);}
  if(hAlphaLength_aIneOut_Sector6==0)  {cout << "ERROR: hAlphaLength_" << SampleName << "_aIneOut_Sector6  not found"    << endl; exit(0);}
  if(hAlphaLength_aOuteIn_Sector6==0)  {cout << "ERROR: hAlphaLength_" << SampleName << "_aOuteIn_Sector6  not found"    << endl; exit(0);}
  if(hAlphaLength_aIneIn_Sector6==0)   {cout << "ERROR: hAlphaLength_" << SampleName << "_aIneIn_Sector6  not found"     << endl; exit(0);}
  if(hAlphaLength_aOuteOut_Sector7==0) {cout << "ERROR: hAlphaLength_" << SampleName << "_aOuteOut_Sector7  not found"   << endl; exit(0);}
  if(hAlphaLength_aIneOut_Sector7==0)  {cout << "ERROR: hAlphaLength_" << SampleName << "_aIneOut_Sector7  not found"    << endl; exit(0);}
  if(hAlphaLength_aOuteIn_Sector7==0)  {cout << "ERROR: hAlphaLength_" << SampleName << "_aOuteIn_Sector7  not found"    << endl; exit(0);}
  if(hAlphaLength_aIneIn_Sector7==0)   {cout << "ERROR: hAlphaLength_" << SampleName << "_aIneIn_Sector7  not found"     << endl; exit(0);}
  if(hAlphaLength_aOuteOut_Sector8==0) {cout << "ERROR: hAlphaLength_" << SampleName << "_aOuteOut_Sector8  not found"   << endl; exit(0);}
  if(hAlphaLength_aIneOut_Sector8==0)  {cout << "ERROR: hAlphaLength_" << SampleName << "_aIneOut_Sector8  not found"    << endl; exit(0);}
  if(hAlphaLength_aOuteIn_Sector8==0)  {cout << "ERROR: hAlphaLength_" << SampleName << "_aOuteIn_Sector8  not found"    << endl; exit(0);}
  if(hAlphaLength_aIneIn_Sector8==0)   {cout << "ERROR: hAlphaLength_" << SampleName << "_aIneIn_Sector8  not found"     << endl; exit(0);}
  if(hAlphaLength_AllEvents_Sector6==0){cout << "ERROR: hAlphaLength_" << SampleName << "_AllEvents_Sector6  not found"  << endl; exit(0);}
  if(hAlphaLength_AllEvents_Sector7==0){cout << "ERROR: hAlphaLength_" << SampleName << "_AllEvents_Sector7  not found"  << endl; exit(0);}
  if(hAlphaLength_AllEvents_Sector8==0){cout << "ERROR: hAlphaLength_" << SampleName << "_AllEvents_Sector8  not found"  << endl; exit(0);}

  TH1D* hAlphaLength_aOuteOut_Sector6_Clone = (TH1D*)hAlphaLength_aOuteOut_Sector6 ->Clone("hAlphaLength_aOuteOut_Sector6");
  TH1D* hAlphaLength_aIneOut_Sector6_Clone  = (TH1D*)hAlphaLength_aIneOut_Sector6  ->Clone("hAlphaLength_aIneOut_Sector6");
  TH1D* hAlphaLength_aOuteIn_Sector6_Clone  = (TH1D*)hAlphaLength_aOuteIn_Sector6  ->Clone("hAlphaLength_aOuteIn_Sector6");
  TH1D* hAlphaLength_aIneIn_Sector6_Clone   = (TH1D*)hAlphaLength_aIneIn_Sector6   ->Clone("hAlphaLength_aIneIn_Sector6");
  TH1D* hAlphaLength_aOuteOut_Sector7_Clone = (TH1D*)hAlphaLength_aOuteOut_Sector7 ->Clone("hAlphaLength_aOuteOut_Sector7");
  TH1D* hAlphaLength_aIneOut_Sector7_Clone  = (TH1D*)hAlphaLength_aIneOut_Sector7  ->Clone("hAlphaLength_aIneOut_Sector7");
  TH1D* hAlphaLength_aOuteIn_Sector7_Clone  = (TH1D*)hAlphaLength_aOuteIn_Sector7  ->Clone("hAlphaLength_aOuteIn_Sector7");
  TH1D* hAlphaLength_aIneIn_Sector7_Clone   = (TH1D*)hAlphaLength_aIneIn_Sector7   ->Clone("hAlphaLength_aIneIn_Sector7");
  TH1D* hAlphaLength_aOuteOut_Sector8_Clone = (TH1D*)hAlphaLength_aOuteOut_Sector8 ->Clone("hAlphaLength_aOuteOut_Sector8");
  TH1D* hAlphaLength_aIneOut_Sector8_Clone  = (TH1D*)hAlphaLength_aIneOut_Sector8  ->Clone("hAlphaLength_aIneOut_Sector8");
  TH1D* hAlphaLength_aOuteIn_Sector8_Clone  = (TH1D*)hAlphaLength_aOuteIn_Sector8  ->Clone("hAlphaLength_aOuteIn_Sector8");
  TH1D* hAlphaLength_aIneIn_Sector8_Clone   = (TH1D*)hAlphaLength_aIneIn_Sector8   ->Clone("hAlphaLength_aIneIn_Sector8");
  TH1D* hAlphaLength_AllEvents_Sector6_Clone= (TH1D*)hAlphaLength_AllEvents_Sector6->Clone("hAlphaLength_AllEvents_Sector6");
  TH1D* hAlphaLength_AllEvents_Sector7_Clone= (TH1D*)hAlphaLength_AllEvents_Sector7->Clone("hAlphaLength_AllEvents_Sector7");
  TH1D* hAlphaLength_AllEvents_Sector8_Clone= (TH1D*)hAlphaLength_AllEvents_Sector8->Clone("hAlphaLength_AllEvents_Sector8");

  hAlphaLength_aOuteOut_Sector6_Clone ->Scale(ScaleFactor);    
  hAlphaLength_aIneOut_Sector6_Clone  ->Scale(ScaleFactor);    
  hAlphaLength_aOuteIn_Sector6_Clone  ->Scale(ScaleFactor);
  hAlphaLength_aIneIn_Sector6_Clone   ->Scale(ScaleFactor);    
  hAlphaLength_aOuteOut_Sector7_Clone ->Scale(ScaleFactor);    
  hAlphaLength_aIneOut_Sector7_Clone  ->Scale(ScaleFactor);    
  hAlphaLength_aOuteIn_Sector7_Clone  ->Scale(ScaleFactor);
  hAlphaLength_aIneIn_Sector7_Clone   ->Scale(ScaleFactor);    
  hAlphaLength_aOuteOut_Sector8_Clone ->Scale(ScaleFactor);    
  hAlphaLength_aIneOut_Sector8_Clone  ->Scale(ScaleFactor);    
  hAlphaLength_aOuteIn_Sector8_Clone  ->Scale(ScaleFactor);
  hAlphaLength_aIneIn_Sector8_Clone   ->Scale(ScaleFactor);    
  hAlphaLength_AllEvents_Sector6_Clone->Scale(ScaleFactor);    
  hAlphaLength_AllEvents_Sector7_Clone->Scale(ScaleFactor);    
  hAlphaLength_AllEvents_Sector8_Clone->Scale(ScaleFactor);    

  hAlphaLength_aOuteOut_Sector6_Clone ->SetFillColor(FillColor);    
  hAlphaLength_aIneOut_Sector6_Clone  ->SetFillColor(FillColor);    
  hAlphaLength_aOuteIn_Sector6_Clone  ->SetFillColor(FillColor);
  hAlphaLength_aIneIn_Sector6_Clone   ->SetFillColor(FillColor);    
  hAlphaLength_aOuteOut_Sector7_Clone ->SetFillColor(FillColor);    
  hAlphaLength_aIneOut_Sector7_Clone  ->SetFillColor(FillColor);    
  hAlphaLength_aOuteIn_Sector7_Clone  ->SetFillColor(FillColor);
  hAlphaLength_aIneIn_Sector7_Clone   ->SetFillColor(FillColor);    
  hAlphaLength_aOuteOut_Sector8_Clone ->SetFillColor(FillColor);    
  hAlphaLength_aIneOut_Sector8_Clone  ->SetFillColor(FillColor);    
  hAlphaLength_aOuteIn_Sector8_Clone  ->SetFillColor(FillColor);
  hAlphaLength_aIneIn_Sector8_Clone   ->SetFillColor(FillColor);    
  hAlphaLength_AllEvents_Sector6_Clone->SetFillColor(FillColor);    
  hAlphaLength_AllEvents_Sector7_Clone->SetFillColor(FillColor);    
  hAlphaLength_AllEvents_Sector8_Clone->SetFillColor(FillColor);    

  FillStackColl[0]  ->Add(hAlphaLength_aOuteOut_Sector6_Clone);
  FillStackColl[1]  ->Add(hAlphaLength_aIneOut_Sector6_Clone);
  FillStackColl[2]  ->Add(hAlphaLength_aOuteIn_Sector6_Clone);
  FillStackColl[3]  ->Add(hAlphaLength_aIneIn_Sector6_Clone);
  FillStackColl[4]  ->Add(hAlphaLength_aOuteOut_Sector7_Clone);
  FillStackColl[5]  ->Add(hAlphaLength_aIneOut_Sector7_Clone);
  FillStackColl[6]  ->Add(hAlphaLength_aOuteIn_Sector7_Clone);
  FillStackColl[7]  ->Add(hAlphaLength_aIneIn_Sector7_Clone);
  FillStackColl[8]  ->Add(hAlphaLength_aOuteOut_Sector8_Clone);
  FillStackColl[9]  ->Add(hAlphaLength_aIneOut_Sector8_Clone);
  FillStackColl[10] ->Add(hAlphaLength_aOuteIn_Sector8_Clone);
  FillStackColl[11] ->Add(hAlphaLength_aIneIn_Sector8_Clone);
  FillStackColl[12] ->Add(hAlphaLength_AllEvents_Sector6_Clone);
  FillStackColl[13] ->Add(hAlphaLength_AllEvents_Sector7_Clone);
  FillStackColl[14] ->Add(hAlphaLength_AllEvents_Sector8_Clone);

  return;
}

#endif
