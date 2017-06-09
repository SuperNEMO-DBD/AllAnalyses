#ifndef CHISQUARETEST_H
#define CHISQUARETEST_H

pair <Double_t, Int_t> ChiSquareTest(TH1D* hData, TH1D* hFit){

  Double_t ChiSquare = 0;
  Int_t NDF = 0;

  // Holder to make sure we've got at least 5 MC events (keep summing up bins until this is true)
  Double_t MCTotal = 0;
  Double_t DataTotal = 0;

  // Loop over all bins in histogram
  for(int i = (hFit->FindFirstBinAbove(0)); i <= hFit->GetNbinsX(); i++){

    //Get data and MC values for this bin
    DataTotal += hData->GetBinContent(i);
    MCTotal += hFit->GetBinContent(i);

    // If total MC is bigger than threshold, include this bin (or total so far)
    if(MCTotal > 5){

      //TODO: FIX ERROR ESTIMATE ON MC TOTAL - NEEDS TO TAKE INTO ACCOUNT CORRELATIONS BETWEEN BINS TOO
      // Calculate chi-squared value and increment NDF
      ChiSquare += pow(DataTotal-MCTotal, 2)/MCTotal;
      //      cout << "Bin: " << i << "\tData = " << DataTotal << "\tMC = " << MCTotal << "\tChiSquare = " << pow(DataTotal-MCTotal, 2)/MCTotal << "\tTotal = " << ChiSquare << endl;
      NDF++;

      // Reset running totals
      DataTotal = 0;
      MCTotal = 0;
    }
  }
      
  // Take one away from NDF as we fit signal activity here
  pair <Double_t, Int_t> TestResult (ChiSquare, NDF-1);
  return TestResult;
}

pair <Double_t, Int_t> ChiSquareTestBGSub(TH1D* hData, TH1D* hFit){

  Double_t ChiSquare = 0;
  Int_t NDF = 0;

  for(int i = (hFit->FindFirstBinAbove(0)); i <= hFit->GetNbinsX(); i++){
    Double_t O_i = hData->GetBinContent(i);
    Double_t E_i = hFit->GetBinContent(i);
    Double_t Err2 = pow(hData->GetBinError(i),2) + pow(hFit->GetBinError(i),2); // MC Error already adjusted for activity error
    if(E_i > 0){
      ChiSquare += (O_i-E_i)*(O_i-E_i)/Err2;
      //      cout << "Bin = " << i << "\tO_i = " << O_i << "\tE_i = " << E_i << "\tO_i - E_i = " << O_i-E_i << "\tO_i_Err = " << hData->GetBinError(i) << "\tE_i_Err = " << hFit->GetBinError(i) << "\tErr = " << sqrt(Err2) << "\tChiSquare = " << ChiSquare << endl;
      NDF++;
    }
  }
      
  pair <Double_t, Int_t> TestResult (ChiSquare, NDF-1);
  return TestResult;
}

#endif
