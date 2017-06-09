extern THStack* StackColl_1e2g[];

Double_t TotalMC_1e2g(Int_t HistNum, Double_t x, const Double_t *par);

Double_t TotalMC_1e2g_SeOld(Double_t x, const Double_t *par){return TotalMC_1e2g(0,x,par);}
Double_t TotalMC_1e2g_SeNew(Double_t x, const Double_t *par){return TotalMC_1e2g(1,x,par);}

Double_t TotalMC_1e2g(Int_t HistNum, Double_t x, const Double_t *par){

  TObjArray* hMC_Stack = StackColl_1e2g[HistNum]->GetStack();

  TH1D* hMC = (TH1D*)hMC_Stack->At(0);
  Int_t bin = hMC->FindBin(x);

  // Bi214 SeNew
  double TotalMC = par[0]*(hMC->GetBinContent(bin));

  // Bi214 SeOld, Mylar
  for(int i = 1; i < 3; i++){
    hMC = (TH1D*)hMC_Stack->At(i);
    TH1D* hMC_1 = (TH1D*)hMC_Stack->At(i-1);
    TotalMC += par[i]*(hMC->GetBinContent(bin) - hMC_1->GetBinContent(bin));
  }

  // Bi214 SWire P1
  for(int i = 3; i < 4; i++){
    hMC = (TH1D*)hMC_Stack->At(i);
    TH1D* hMC_1 = (TH1D*)hMC_Stack->At(i-1);
    TotalMC += par[3]*par[i+1]*(hMC->GetBinContent(bin) - hMC_1->GetBinContent(bin));
  }

  // Bi214 SWire P2
  for(int i = 4; i < 5; i++){
    hMC = (TH1D*)hMC_Stack->At(i);
    TH1D* hMC_1 = (TH1D*)hMC_Stack->At(i-1);
    TotalMC += par[i]*(hMC->GetBinContent(bin) - hMC_1->GetBinContent(bin));
  }

  // Bi214 SFoil In/Out P1
  for(int i = 5; i < 7; i++){
    hMC = (TH1D*)hMC_Stack->At(i);
    TH1D* hMC_1 = (TH1D*)hMC_Stack->At(i-1);
    TotalMC += par[3]*par[i]*(hMC->GetBinContent(bin) - hMC_1->GetBinContent(bin));
  }

  // Bi214 SFoil In/Out P2
  for(int i = 7; i < 9; i++){
    hMC = (TH1D*)hMC_Stack->At(i);
    TH1D* hMC_1 = (TH1D*)hMC_Stack->At(i-1);
    TotalMC += par[i-2]*(hMC->GetBinContent(bin) - hMC_1->GetBinContent(bin));
  }

  // Neutrons P1
  for(int i = 9; i < 10; i++){
    hMC = (TH1D*)hMC_Stack->At(i);
    TH1D* hMC_1 = (TH1D*)hMC_Stack->At(i-1);
    TotalMC += par[34]*(hMC->GetBinContent(bin) - hMC_1->GetBinContent(bin));
  }

  // Neutrons P2
  for(int i = 10; i < 11; i++){
    hMC = (TH1D*)hMC_Stack->At(i);
    TH1D* hMC_1 = (TH1D*)hMC_Stack->At(i-1);
    TotalMC += par[35]*(hMC->GetBinContent(bin) - hMC_1->GetBinContent(bin));
  }

  // Tl208 PMT
  for(int i = 11; i < 12; i++){
    hMC = (TH1D*)hMC_Stack->At(i);
    TH1D* hMC_1 = (TH1D*)hMC_Stack->At(i-1);
    TotalMC += par[21]*(hMC->GetBinContent(bin) - hMC_1->GetBinContent(bin));
  }

  // Tl208 Steel Frame
  for(int i = 12; i < 13; i++){
    hMC = (TH1D*)hMC_Stack->At(i);
    TH1D* hMC_1 = (TH1D*)hMC_Stack->At(i-1);
    TotalMC += par[26]*(hMC->GetBinContent(bin) - hMC_1->GetBinContent(bin));
  }

  // Tl208 SWire P1, P2
  for(int i = 13; i < 15; i++){
    hMC = (TH1D*)hMC_Stack->At(i);
    TH1D* hMC_1 = (TH1D*)hMC_Stack->At(i-1);
    TotalMC += par[i-6]*(hMC->GetBinContent(bin) - hMC_1->GetBinContent(bin));
  }

  // Tl208 SeNew, SeOld
  for(int i = 15; i < 17; i++){
    hMC = (TH1D*)hMC_Stack->At(i);
    TH1D* hMC_1 = (TH1D*)hMC_Stack->At(i-1);
    TotalMC += par[i-6]*(hMC->GetBinContent(bin) - hMC_1->GetBinContent(bin));
  }

  return TotalMC;
}
