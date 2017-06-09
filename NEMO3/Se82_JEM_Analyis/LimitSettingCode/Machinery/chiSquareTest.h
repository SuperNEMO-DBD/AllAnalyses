#ifndef CHISQUARETEST_H
#define CHISQUARETEST_H

pair <Double_t, Int_t> ChiSquareTest(TH1D* hData, TH1D* hFit){

  Double_t ChiSquare = 0;
  Int_t NDF = 0;

  for(int i = (hFit->FindFirstBinAbove(0)); i <= hFit->GetNbinsX(); i++){
    Double_t O_i = hData->GetBinContent(i);
    Double_t E_i = hFit->GetBinContent(i);
    if(E_i > 0){
      ChiSquare += (O_i-E_i)*(O_i-E_i)/E_i;
      //      cout << "Bin = " << i << "\tO_i = " << O_i << "\tE_i = " << E_i << "\tChiSquare = " << ChiSquare << endl;
      NDF++;
    }
  }
      
  pair <Double_t, Int_t> TestResult (ChiSquare, NDF-1);
  return TestResult;
}

#endif
