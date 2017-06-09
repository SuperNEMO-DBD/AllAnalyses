#ifndef ADDCHANNELTOSTACKS_1E2G_H
#define ADDCHANNELTOSTACKS_1E2G_H

void addChannelToStacks_1e2g(string SampleName, Double_t ScaleFactor, Int_t FillColor, THStack* FillStackColl[], TFile* infile){

  char buffer[200];

  strcpy(buffer,"hElectronEnergy_");
  TH1D* hElectronEnergy_SeOld  = (TH1D*)infile->Get(strcat(buffer,(SampleName+"_SeOld").c_str()));

  strcpy(buffer,"hElectronEnergy_");
  TH1D* hElectronEnergy_SeNew  = (TH1D*)infile->Get(strcat(buffer,(SampleName+"_SeNew").c_str()));


  if(hElectronEnergy_SeOld==0)  {cout << "ERROR:hElectronEnergy_"  << SampleName << "_SeOld not found"   << endl; exit(0);}
  if(hElectronEnergy_SeNew==0)  {cout << "ERROR:hElectronEnergy_"  << SampleName << "_SeNew not found"   << endl; exit(0);}

  TH1D* hElectronEnergy_SeOldClone  = (TH1D*)hElectronEnergy_SeOld->Clone("hElectronEnergy_SeOldClone");  
  TH1D* hElectronEnergy_SeNewClone  = (TH1D*)hElectronEnergy_SeNew->Clone("hElectronEnergy_SeNewClone");  

  hElectronEnergy_SeOldClone->Scale(ScaleFactor); 
  hElectronEnergy_SeNewClone->Scale(ScaleFactor); 

  hElectronEnergy_SeOldClone->SetFillColor(FillColor); 
  hElectronEnergy_SeNewClone->SetFillColor(FillColor); 

  FillStackColl[0]->Add(hElectronEnergy_SeOldClone);
  FillStackColl[1]->Add(hElectronEnergy_SeNewClone);

  return;
}

#endif
