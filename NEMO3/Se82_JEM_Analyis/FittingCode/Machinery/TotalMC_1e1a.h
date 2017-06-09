extern THStack* StackColl_1e1a_P1[];
extern THStack* StackColl_1e1a_P2[];

Double_t TotalMC_1e1a_P1(Int_t HistNum, Double_t x, const Double_t *par); 
Double_t TotalMC_1e1a_P2(Int_t HistNum, Double_t x, const Double_t *par); 

Double_t TotalMC_1e1a_P1_aOuteOut_Sector6(Double_t x, const Double_t *par){return TotalMC_1e1a_P1(0,x,par);} 
Double_t TotalMC_1e1a_P1_aIneOut_Sector6 (Double_t x, const Double_t *par){return TotalMC_1e1a_P1(1,x,par);} 
Double_t TotalMC_1e1a_P1_aOuteIn_Sector6 (Double_t x, const Double_t *par){return TotalMC_1e1a_P1(2,x,par);}  
Double_t TotalMC_1e1a_P1_aIneIn_Sector6  (Double_t x, const Double_t *par){return TotalMC_1e1a_P1(3,x,par);}   
Double_t TotalMC_1e1a_P1_aOuteOut_Sector7(Double_t x, const Double_t *par){return TotalMC_1e1a_P1(4,x,par);}
Double_t TotalMC_1e1a_P1_aIneOut_Sector7 (Double_t x, const Double_t *par){return TotalMC_1e1a_P1(5,x,par);}  
Double_t TotalMC_1e1a_P1_aOuteIn_Sector7 (Double_t x, const Double_t *par){return TotalMC_1e1a_P1(6,x,par);} 
Double_t TotalMC_1e1a_P1_aIneIn_Sector7  (Double_t x, const Double_t *par){return TotalMC_1e1a_P1(7,x,par);}   
Double_t TotalMC_1e1a_P1_aOuteOut_Sector8(Double_t x, const Double_t *par){return TotalMC_1e1a_P1(8,x,par);}
Double_t TotalMC_1e1a_P1_aIneOut_Sector8 (Double_t x, const Double_t *par){return TotalMC_1e1a_P1(9,x,par);}  
Double_t TotalMC_1e1a_P1_aOuteIn_Sector8 (Double_t x, const Double_t *par){return TotalMC_1e1a_P1(10,x,par);}  
Double_t TotalMC_1e1a_P1_aIneIn_Sector8  (Double_t x, const Double_t *par){return TotalMC_1e1a_P1(11,x,par);} 

Double_t TotalMC_1e1a_P2_aOuteOut_Sector6(Double_t x, const Double_t *par){return TotalMC_1e1a_P2(0,x,par);} 
Double_t TotalMC_1e1a_P2_aIneOut_Sector6 (Double_t x, const Double_t *par){return TotalMC_1e1a_P2(1,x,par);} 
Double_t TotalMC_1e1a_P2_aOuteIn_Sector6 (Double_t x, const Double_t *par){return TotalMC_1e1a_P2(2,x,par);}  
Double_t TotalMC_1e1a_P2_aIneIn_Sector6  (Double_t x, const Double_t *par){return TotalMC_1e1a_P2(3,x,par);}   
Double_t TotalMC_1e1a_P2_aOuteOut_Sector7(Double_t x, const Double_t *par){return TotalMC_1e1a_P2(4,x,par);}
Double_t TotalMC_1e1a_P2_aIneOut_Sector7 (Double_t x, const Double_t *par){return TotalMC_1e1a_P2(5,x,par);}  
Double_t TotalMC_1e1a_P2_aOuteIn_Sector7 (Double_t x, const Double_t *par){return TotalMC_1e1a_P2(6,x,par);} 
Double_t TotalMC_1e1a_P2_aIneIn_Sector7  (Double_t x, const Double_t *par){return TotalMC_1e1a_P2(7,x,par);}   
Double_t TotalMC_1e1a_P2_aOuteOut_Sector8(Double_t x, const Double_t *par){return TotalMC_1e1a_P2(8,x,par);}
Double_t TotalMC_1e1a_P2_aIneOut_Sector8 (Double_t x, const Double_t *par){return TotalMC_1e1a_P2(9,x,par);}  
Double_t TotalMC_1e1a_P2_aOuteIn_Sector8 (Double_t x, const Double_t *par){return TotalMC_1e1a_P2(10,x,par);}  
Double_t TotalMC_1e1a_P2_aIneIn_Sector8  (Double_t x, const Double_t *par){return TotalMC_1e1a_P2(11,x,par);} 

Double_t TotalMC_1e1a_P1(Int_t HistNum, Double_t x, const Double_t *par){

  TObjArray* hMC_Stack = StackColl_1e1a_P1[HistNum]->GetStack();

  TH1D* hMC = (TH1D*)hMC_Stack->At(0);
  Int_t bin = hMC->FindBin(x);

  // SeNew, SeOld, Mylar
  double TotalMC = par[0]*(hMC->GetBinContent(bin));
  for(int i = 1; i < 3; i++){
    hMC = (TH1D*)hMC_Stack->At(i);
    TH1D* hMC_1 = (TH1D*)hMC_Stack->At(i-1);
    TotalMC += par[i]*(hMC->GetBinContent(bin) - hMC_1->GetBinContent(bin));
  }

  // SWire, SFoil In, Out P1
  for(int i = 3; i < 6; i++){
    hMC = (TH1D*)hMC_Stack->At(i);
    TH1D* hMC_1 = (TH1D*)hMC_Stack->At(i-1);
    TotalMC += par[3]*par[i+1]*(hMC->GetBinContent(bin) - hMC_1->GetBinContent(bin));
  }

  return TotalMC;
}

Double_t TotalMC_1e1a_P2(Int_t HistNum, Double_t x, const Double_t *par){

  TObjArray* hMC_Stack = StackColl_1e1a_P2[HistNum]->GetStack();

  TH1D* hMC = (TH1D*)hMC_Stack->At(0);
  Int_t bin = hMC->FindBin(x);

  double TotalMC = par[0]*(hMC->GetBinContent(bin));

  for(int i = 1; i < 3; i++){
    hMC = (TH1D*)hMC_Stack->At(i);
    TH1D* hMC_1 = (TH1D*)hMC_Stack->At(i-1);
    TotalMC += par[i]*(hMC->GetBinContent(bin) - hMC_1->GetBinContent(bin));
  }

  for(int i = 3; i < 6; i++){
    hMC = (TH1D*)hMC_Stack->At(i);
    TH1D* hMC_1 = (TH1D*)hMC_Stack->At(i-1);
    TotalMC += par[i+1]*(hMC->GetBinContent(bin) - hMC_1->GetBinContent(bin));
  }

  return TotalMC;
}
