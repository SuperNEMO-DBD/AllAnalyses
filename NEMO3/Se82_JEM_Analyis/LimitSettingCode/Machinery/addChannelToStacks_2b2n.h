#ifndef ADDCHANNELTOSTACKS_2B2N_H
#define ADDCHANNELTOSTACKS_2B2N_H

void addChannelToStacks_2b2n(string SampleName, Double_t ScaleFactor, Int_t FillColor, THStack* FillStackColl[], TFile* infile){

  char buffer[200];

  TH1D* h_2b2n; 

  strcpy(buffer,"hTotEnergy_");
  h_2b2n = (TH1D*)infile->Get(strcat(buffer,SampleName.c_str()));

  if(h_2b2n==0) {cout << "ERROR:  hTotEnergy_"  << SampleName << " not found"     << endl; exit(0);}

  TH1D* h_2b2n_Clone = (TH1D*)h_2b2n ->Clone("h_2b2n_Clone");

  h_2b2n_Clone->Scale(ScaleFactor);

  h_2b2n_Clone->SetFillColor(FillColor);

  FillStackColl[0]-> Add(h_2b2n_Clone);

}

#endif
