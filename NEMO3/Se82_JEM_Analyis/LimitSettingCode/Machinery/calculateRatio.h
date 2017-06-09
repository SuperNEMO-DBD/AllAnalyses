extern Double_t Denominators_Ext[];
extern Double_t Denominators_Rad[];
extern Double_t Denominators_Int[];
extern Double_t Denominators_Sig[];
extern Double_t AdjustActs[];
extern Double_t AdjustActs_Err[];
extern Double_t CovMatrix[][44];

// Function to calculate ratio between data and MC - complicated to calculate MC errors...
TGraphErrors* calculateRatio(TH1D* hData, int MCHist){

  // TGraphErrors that we're going to fill
  TGraphErrors* ratio = new TGraphErrors();

  // Get number of entries in stack for getting pentulimate one later
  int nStackEntries = StackColl_2b2n[MCHist]->GetStack()->GetEntries();

  // Loop over each bin in the data histogram
  for (int bin = 0; bin < hData->GetNbinsX()+1; bin++){

    // Only put in ratio if there's an entry in the data histogram
    if (hData->GetBinContent(bin) > 0){
      
      // Calculate ratio
      double dataValue = hData->GetBinContent(bin);
      double MCValue = ((TH1D*)StackColl_2b2n[MCHist]->GetStack()->At(nStackEntries-2))->GetBinContent(bin); //Penultimate to exclude 2b0n from ratio
      double dataOverMC = dataValue/MCValue;
      
      // Get error from data
      double dataError = hData->GetBinError(bin);
      
      // Calculate MC error - this is tricky due to all the correlations

      // Create correlation matrix of all fitted parameters to use when calculating errors
      double CorrMatrix[44][44];
      for(int i = 0; i < 44; i++){
	for(int j = 0; j < 44; j++){
	  CorrMatrix[i][j] = CovMatrix[i][j]/(sqrt(CovMatrix[i][i])*sqrt(CovMatrix[j][j]));
	}
      }
      
      // List all indices to relate fit parameters to histograms - new lines for ext, rad, int, sig samples
      int FitIndex[74]   = {11, 16, 21, 21, 25, 12, 18, 23, 23, 26, 27, 28, 17, 22, 22, 13, 14, 15, 31, 32, 33, 34, 35,
			     3,  4,  3,  4, 30, 30,  7,  8,  3,  5,  3,  6,  3,  5,  3,  6, 36, 36, 37, 37, 38, 38,  3, 19,  3, 19, 29, 29, 20, 20, 20, 20, 24, 24,
			     0,  1,  2,  0,  1,  2,  9, 10,  9, 10,  9, 10, 39, 40, 41, 42,
			     0};
      int DenomIndex[74] = { 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 19, 20, 20,
			     0,  0,  1,  1,  2,  2,  3,  3,  4,  4,  4,  4,  5,  5,  5,  5,  6,  6,  6,  6,  6,  6,  7,  7,  8,  8,  9,  9, 10, 10, 11, 11, 12, 12,
			     0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
			     0};

      // Holders for error on numbers of events from activity and efficiency errors
      double EvtsActErr[74];
      double EvtsEffErr[74];

      // Holders for pointers in code
      THStack** histStack = 0;
      double* denominators = 0;

      // Loop over all 74 samples that make up the MC (again excluding 2b0n)
      int histCnt = 0;
      for(int i = 0; i < 74; i++, histCnt++){

	// Switch to next sample at appropriate points (also reset histogram counter)
 	if (i == 0){
	  histStack = ExtStackColl_2b2n;
	  denominators = Denominators_Ext;
	  histCnt = 0;
	} else if (i == 23) {
	  histStack = RadStackColl_2b2n;
	  denominators = Denominators_Rad;
	  histCnt = 0;
	} else if (i == 57) {
	  histStack = Bi214StackColl_2b2n;
	  denominators = Denominators_Int;
	  histCnt = 0;
	} else if (i == 63) {
	  histStack = Tl208StackColl_2b2n;
	  denominators = Denominators_Int;
	  histCnt = 0;
	} else if (i == 69) {
	  histStack = IntStackColl_2b2n;
	  denominators = Denominators_Int;
	  histCnt = 0;
	} else if (i == 73){
	  histStack = SigStackColl_2b2n;
	  denominators = Denominators_Sig;
	  histCnt = 0;
	}

	double scale, N, nEntries;

	// Calculate number of MC events in this bin from this sample (denoted by i and histCnt)
	if(histCnt == 0){
	  scale = ((TH1D*)histStack[MCHist]->GetStack()->At(0))->Integral()/((TH1D*)histStack[MCHist]->GetStack()->At(0))->GetEntries();
	  N = ((TH1D*)histStack[MCHist]->GetStack()->At(0))->GetBinContent(bin);
	} else {
	  scale = (((TH1D*)histStack[MCHist]->GetStack()->At(histCnt))->Integral() - ((TH1D*)histStack[MCHist]->GetStack()->At(histCnt-1))->Integral())/(((TH1D*)histStack[MCHist]->GetStack()->At(histCnt))->GetEntries() - ((TH1D*)histStack[MCHist]->GetStack()->At(histCnt-1))->GetEntries());
	  N = ((TH1D*)histStack[MCHist]->GetStack()->At(histCnt))->GetBinContent(bin) - ((TH1D*)histStack[MCHist]->GetStack()->At(histCnt-1))->GetBinContent(bin);
	}

	// Calculate the number of entries in this bin (un-scaled) to calculate eff error
	if (scale > 0){
	  nEntries = N/scale;
	} else {
	  nEntries = 0;
	}

	// Calculate errors
	EvtsActErr[i] = N * (AdjustActs_Err[FitIndex[i]]/AdjustActs[FitIndex[i]]);
	if(nEntries > 0){
	  EvtsEffErr[i] = N * sqrt( (1.0 - nEntries/denominators[DenomIndex[i]])/nEntries);
	} else {
	  EvtsEffErr[i] = 0;
	}

      }

      // Calculate error on num of MC events from activity errors and efficiency errors
      Double_t NEvtsActErr2 = 0;
      Double_t NEvtsEffErr2 = 0;
      for(int i = 0; i < 74; i++){
	for(int j = i; j < 74; j++){
	  NEvtsActErr2 += CorrMatrix[FitIndex[i]][FitIndex[j]]*EvtsActErr[i]*EvtsActErr[j];
	}
	NEvtsEffErr2 += EvtsEffErr[i]*EvtsEffErr[i];
      }

      // Calculate total MC error from activity and efficiency errors
      double MCError = sqrt(NEvtsActErr2+NEvtsEffErr2);      

      // Add data and MC errors
      double totalError = dataOverMC*sqrt(pow(dataError/dataValue,2) + pow(MCError/MCValue,2));

      // Add current point to ratio plot
      int nPt = ratio->GetN();
      ratio->SetPoint(nPt, hData->GetBinCenter(bin), dataOverMC);
      ratio->SetPointError(nPt, 0.5*hData->GetBinWidth(bin), totalError);

    }

  }

  return ratio;
}
