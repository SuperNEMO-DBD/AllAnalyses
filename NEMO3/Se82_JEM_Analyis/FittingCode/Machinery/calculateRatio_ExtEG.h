extern THStack* StackColl_ExtEG[];
extern THStack* IntStackColl_ExtEG[];
extern THStack* RadStackColl_ExtEG[];
extern THStack* ExtStackColl_ExtEG[];
extern THStack* SigStackColl_ExtEG[];
extern Double_t Activities_Ext[], Activities_Ext_Err[], Denominators_Ext[];
extern Double_t Activities_Rad[], Activities_Rad_Err[], Denominators_Rad[];
extern Double_t Activities_Int[],  Activities_Int_Err[],  Denominators_Int[];
extern Double_t Activities_Sig[],  Activities_Sig_Err[],  Denominators_Sig[];
extern Double_t AdjustActs[], AdjustActs_Err[];
extern Double_t CovMatrix[][44];

// Function to calculate ratio between data and MC - complicated to calculate MC errors...
TGraphErrors* calculateRatio_ExtEG(TH1D* hData, int MCHist){

  // TGraphErrors that we're going to fill
  TGraphErrors* ratio = new TGraphErrors();

  // Loop over each bin in the data histogram
  for (int bin = 0; bin < hData->GetNbinsX()+1; bin++){

    // Only put in ratio if there's an entry in the data histogram
    if (hData->GetBinContent(bin) > 0){
      
      // Calculate ratio
      double dataValue = hData->GetBinContent(bin);
      double MCValue = ((TH1D*)StackColl_ExtEG[MCHist]->GetStack()->Last())->GetBinContent(bin);
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
      int FitIndex[56]   = {11, 16, 21, 21, 25, 12, 18, 23, 23, 26, 27, 28, 17, 22, 22, 13, 14, 15, 31, 32, 34,
			     3,  3, 30,  7,  3,  3,  3,  3, 36, 37, 38,  3,  3, 29, 20, 20, 24,
			     0,  1,  2,  0,  1,  2,  9, 10,  9, 10,  9, 10, 39, 40, 41, 42,
			    43, 43};
      int DenomIndex[56] = { 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
			     0,  1,  2,  3,  4,  4,  5,  5,  6,  6,  6,  7,  8,  9, 10, 11, 12,
			     0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
			     0,  0};

      //Indices are set for P1 parameters where there's a choice.  Update if we're in a P2 histogram.

      if(MCHist > 2){
	//External gamma flux and neutrons
	FitIndex[19] = 33;
	FitIndex[20] = 35;

	//Radon backgrounds
	FitIndex[21] = 4;
	FitIndex[22] = 4;
	FitIndex[24] = 8;
	FitIndex[25] = 5;
	FitIndex[26] = 6;
	FitIndex[27] = 5;
	FitIndex[28] = 6;
	FitIndex[32] = 19;
	FitIndex[33] = 19;
      }

      // Holders for error on numbers of events from activity and efficiency errors
      double EvtsActErr[56];
      double EvtsEffErr[56];

      // Holders for pointers in code
      THStack** histStack = 0;
      double* denominators = 0;

      // Loop over all 56 samples that make up the MC
      int histCnt = 0;
      for(int i = 0; i < 56; i++, histCnt++){

	// Switch to next sample at appropriate points (also reset histogram counter)
 	if (i == 0){
	  histStack = ExtStackColl_ExtEG;
	  denominators = Denominators_Ext;
	  histCnt = 0;
	} else if (i == 21) {
	  histStack = RadStackColl_ExtEG;
	  denominators = Denominators_Rad;
	  histCnt = 0;
	} else if (i == 38) {
	  histStack = IntStackColl_ExtEG;
	  denominators = Denominators_Int;
	  histCnt = 0;
	} else if (i == 54){
	  histStack = SigStackColl_ExtEG;
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
      for(int i = 0; i < 56; i++){
	for(int j = i; j < 56; j++){
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

void saveRatioPlots_ExtEG(TH1D* hData, int MCHist, double xMin, double xMax, double yMin, double yMaxScaler, string name, bool logScale = false){

  // Make canvas and put pad in top 75%
  TCanvas* c1 = new TCanvas("c1",name.c_str(),200,10,1080,960);
  TPad *pad1 = new TPad("pad1", "main",0.0,0.25,1.0,1.0);
  pad1->SetBottomMargin(0);
  if(logScale) pad1->SetLogy();
  pad1->Draw();
  pad1->cd();

  // Set ranges and draw data main histogram
  hData->SetMarkerStyle(20);
  hData->SetMaximum(hData->GetMaximum()*yMaxScaler);
  hData->SetMinimum(yMin);
  if(xMax > xMin) hData->GetXaxis()->SetRangeUser(xMin,xMax);
  hData->Draw();
  StackColl_ExtEG[MCHist]->Draw("HISTSAME");
  hData->Draw("SAME");
  if(!logScale){
    Legend_ExtEG[MCHist]->Draw();
    ChiSquares_ExtEG[MCHist]->Draw();
  } else {
    LegendLog_ExtEG[MCHist]->Draw();
    ChiSquaresLog_ExtEG[MCHist]->Draw();
  }
  c1->Update();
  c1->cd();

  TPad *pad2 = new TPad("pad2", "ratio",0.0,0.0,1.0,0.25);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.3);
  pad2->Draw();
  pad2->cd();

  TGraphErrors* ratio = calculateRatio_ExtEG(hData, MCHist);
  ratio->SetMarkerStyle(20);
  ratio->Draw("AP");
  ratio->GetXaxis()->SetLimits(pad1->GetUxmin(),pad1->GetUxmax());
  ratio->GetYaxis()->SetRangeUser(0.001,1.999);
  ratio->GetYaxis()->SetNdivisions(306);
  ratio->SetTitle("");
  ratio->GetYaxis()->SetTitle("Data/MC");
  ratio->GetXaxis()->SetTitle(hData->GetXaxis()->GetTitle());
  ratio->GetXaxis()->SetTitleSize(hData->GetXaxis()->GetTitleSize()*3);
  ratio->GetXaxis()->SetLabelSize(hData->GetXaxis()->GetLabelSize()*3);
  ratio->GetYaxis()->SetTitleOffset(hData->GetXaxis()->GetTitleOffset()/3);
  ratio->GetYaxis()->SetTitleSize(hData->GetYaxis()->GetTitleSize()*3);
  ratio->GetYaxis()->SetLabelSize(hData->GetYaxis()->GetLabelSize()*3);

  //If points are off plot, they just don't get drawn - put in errors as TLine by hand
  c1->Update();
  for(int pt = 0; pt < ratio->GetN(); pt++){
    double x_tmp, y_tmp;
    ratio->GetPoint(pt,x_tmp,y_tmp);
    if(y_tmp > pad2->GetUymax()){
      double y_max = pad2->GetUymax();
      double y_min = (y_tmp-ratio->GetErrorY(pt) < pad2->GetUymin()) ? pad2->GetUymin() : y_tmp-ratio->GetErrorY(pt);
      TLine* error = new TLine(x_tmp,y_min, x_tmp, y_max);
      error->Draw();
    } else if (y_tmp < pad2->GetUymin()) {
      double y_min = pad2->GetUymin();
      double y_max = (y_tmp+ratio->GetErrorY(pt) > pad2->GetUymax()) ? pad2->GetUymax() : y_tmp+ratio->GetErrorY(pt);
      TLine* error = new TLine(x_tmp,y_min, x_tmp, y_max);
      error->Draw();
    }
  }
  
  TLine* unity = new TLine(pad1->GetUxmin(),1,pad1->GetUxmax(),1);
  unity->SetLineStyle(2);
  unity->Draw();
  c1->cd();

  c1->SaveAs(("Images/png/"+name+".png").c_str());
  c1->SaveAs(("Images/eps/"+name+".eps").c_str());
  c1->SaveAs(("Images/gif/"+name+".gif").c_str());

  delete unity;
  delete pad1;
  delete pad2;
  delete c1;
}