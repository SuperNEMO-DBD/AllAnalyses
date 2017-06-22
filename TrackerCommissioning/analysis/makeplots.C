//void makeplots(int mode == 0){
  { int mode = 4;
  #define DRAW_OPTS "COLZ TEXT90"
//  #define DRAW_OPTS "COL TEXT90"         /* without colour scale */
  int useDrawOptions=1;

  TH2* currentHist;
  
  gStyle->SetPadBottomMargin(0.2);
  // gStyle->SetPadRightMargin(0.2);
  //gStyle->SetPalette(1);
  gStyle->SetOptStat("0");
  gStyle->SetStatY(0.96); 
  gStyle->SetPaintTextFormat("5.2f"); //TWO DECIMAL PLACES
  gStyle->SetPaperSize(29.7, 20);
  gROOT->ProcessLine(".L GHbase.C+");
  gROOT->ProcessLine(".L AnalysisPlots.C+");
  
  TChain* chain = new TChain("raw");
  
  /************************************************/
  /*************C0 ALL GOOD RUNS  *****************/
  /************************************************/

  /*chain->Add("./goodRuns_C0/nothings98.root");
  chain->Add("./goodRuns_C0/nothings99.root");
  chain->Add("./goodRuns_C0/nothings100.root");
  chain->Add("./goodRuns_C0/nothings102.root");
  chain->Add("./goodRuns_C0/nothings103.root");
  chain->Add("./goodRuns_C0/nothings106.root");
  chain->Add("./goodRuns_C0/nothings107.root");
  chain->Add("./goodRuns_C0/nothings110.root");
  chain->Add("./goodRuns_C0/nothings111.root");
  chain->Add("./goodRuns_C0/nothings114.root");
  chain->Add("./goodRuns_C0/nothings115.root");

  /************************************************/

  /************************************************/
  /*************C1 ALL GOOD RUNS  *****************/
  /************************************************/

/*      chain->Add("./goodRuns_C1/nothings174.root");
      chain->Add("./goodRuns_C1/nothings184.root");
      chain->Add("./goodRuns_C1/nothings195.root");
      chain->Add("./goodRuns_C1/nothings196.root");
      chain->Add("./goodRuns_C1/nothings197.root");
      chain->Add("./goodRuns_C1/nothings198.root");
      chain->Add("./goodRuns_C1/nothings199.root");
      chain->Add("./goodRuns_C1/nothings200.root");
      chain->Add("./goodRuns_C1/nothings202.root");
      chain->Add("./goodRuns_C1/nothings206.root");
      chain->Add("./goodRuns_C1/nothings207.root");
      chain->Add("./goodRuns_C1/nothings208.root");
      chain->Add("./goodRuns_C1/nothings209.root");
      chain->Add("./goodRuns_C1/nothings210.root");
      chain->Add("./goodRuns_C1/nothings211.root");
      chain->Add("./goodRuns_C1/nothings212.root");
      chain->Add("./goodRuns_C1/nothings217.root");
      chain->Add("./goodRuns_C1/nothings225.root");
      chain->Add("./goodRuns_C1/nothings226.root");
      chain->Add("./goodRuns_C1/nothings227.root");
      chain->Add("./goodRuns_C1/nothings228.root");
      chain->Add("./goodRuns_C1/nothings229.root");
      chain->Add("./goodRuns_C1/nothings230.root");
      chain->Add("./goodRuns_C1/nothings231.root");
      chain->Add("./goodRuns_C1/nothings232.root");
      chain->Add("./goodRuns_C1/nothings233.root");
      chain->Add("./goodRuns_C1/nothings235.root");
      chain->Add("./goodRuns_C1/nothings236.root");
      chain->Add("./goodRuns_C1/nothings237.root");
      chain->Add("./goodRuns_C1/nothings240.root");
      chain->Add("./goodRuns_C1/nothings241.root");
      chain->Add("./goodRuns_C1/nothings242.root");
      chain->Add("./goodRuns_C1/nothings243.root");
      chain->Add("./goodRuns_C1/nothings244.root");
      chain->Add("./goodRuns_C1/nothings245.root");
      chain->Add("./goodRuns_C1/nothings246.root");
      chain->Add("./goodRuns_C1/nothings247.root");
      chain->Add("./goodRuns_C1/nothings248.root");
      chain->Add("./goodRuns_C1/nothings249.root");
      chain->Add("./goodRuns_C1/nothings250.root");
      chain->Add("./goodRuns_C1/nothings251.root");
      chain->Add("./goodRuns_C1/nothings252.root"); 

  /************************************************/

  /************************************************/
  /*************  C2 ALL GOOD RUNS  ***************/
  /************************************************/
  chain->Add("./goodRuns_C2/nothings259.root");
  chain->Add("./goodRuns_C2/nothings262.root");
  chain->Add("./goodRuns_C2/nothings264.root");
  chain->Add("./goodRuns_C2/nothings265.root");
  chain->Add("./goodRuns_C2/nothings266.root");
  chain->Add("./goodRuns_C2/nothings267.root");
  chain->Add("./goodRuns_C2/nothings269.root");
  chain->Add("./goodRuns_C2/nothings270.root");
  chain->Add("./goodRuns_C2/nothings271.root");
  chain->Add("./goodRuns_C2/nothings272.root");
  chain->Add("./goodRuns_C2/nothings273.root");
  chain->Add("./goodRuns_C2/nothings274.root");
  chain->Add("./goodRuns_C2/nothings275.root");
  chain->Add("./goodRuns_C2/nothings276.root");
  chain->Add("./goodRuns_C2/nothings277.root");
  chain->Add("./goodRuns_C2/nothings278.root");
  chain->Add("./goodRuns_C2/nothings279.root");
  chain->Add("./goodRuns_C2/nothings280.root");
  chain->Add("./goodRuns_C2/nothings281.root");
  chain->Add("./goodRuns_C2/nothings282.root");
  chain->Add("./goodRuns_C2/nothings283.root");
  chain->Add("./goodRuns_C2/nothings284.root");
  chain->Add("./goodRuns_C2/nothings285.root");
  chain->Add("./goodRuns_C2/nothings286.root");
  chain->Add("./goodRuns_C2/nothings287.root");
  chain->Add("./goodRuns_C2/nothings288.root");
  chain->Add("./goodRuns_C2/nothings289.root");
  chain->Add("./goodRuns_C2/nothings290.root");
  chain->Add("./goodRuns_C2/nothings291.root");
  chain->Add("./goodRuns_C2/nothings292.root");
  chain->Add("./goodRuns_C2/nothings293.root");
  chain->Add("./goodRuns_C2/nothings294.root");
  chain->Add("./goodRuns_C2/nothings297.root");
  chain->Add("./goodRuns_C2/nothings298.root");
  chain->Add("./goodRuns_C2/nothings299.root");
  chain->Add("./goodRuns_C2/nothings300.root");
  chain->Add("./goodRuns_C2/nothings301.root");
  chain->Add("./goodRuns_C2/nothings302.root");
  chain->Add("./goodRuns_C2/nothings303.root");
  chain->Add("./goodRuns_C2/nothings304.root");

  /************************************************/

      
  
  if (chain->GetNtrees()>0) {
    AnalysisPlots mon(chain);
  } else {
    AnalysisPlots mon;
  }

  mon.Loop();
  Long64_t nentries = mon.fChain->GetEntriesFast();
  TCanvas *c1 = new TCanvas("c1", "Occupancy Percentage", 1300, 707);

  switch( mode ) 
    {
      case 0: //occupancy percentage plot
        currentHist = mon.occupancyPercent;
        filename = "occupancyPercent.png";
        break;
      case 1 : //traffic light plot
        mon.occupancyPercent->SetTitle("Cell Status");
        useDrawOptions=0;
        currentHist = mon.occupancyPercent;
        currentHist->SetMaximum(15);
        const char * filename = "trafficLights.png";
        break;
      case 2: //either cathode good occupancy
        currentHist =  mon.occupancyAnodeCEitherGood;
        const char * filename = "occupancyEitherCathodeGood.png";
        break;
      case 3: //both cathodes good occupancy
        currentHist = mon.occupancyAnodeCBothGood;
        const char * filename = "occupancyBothCathodesGood.png";
        break;
      case 4: //top cathode good occupancy
        currentHist =  mon.occupancyAnodeCtGood;
        const char * filename = "occupancyTopCathodeGood.png";
        break;
      case 5: //bottom cathodes good occupancy
        currentHist = mon.occupancyAnodeCbGood;
        const char * filename = "occupancyBottomCathodesGood.png";
        break;
      case 6: //anode drift time
        currentHist = mon.driftTime;
        const char * filename = "driftTime.png";
        break;
      case 7: //plasma propogation time
        currentHist = mon.driftTimeCathodeTotal;
        const char * filename = "propagationTime.png";
        break;
    }

  if (useDrawOptions)
    currentHist->Draw(DRAW_OPTS);
  else
    currentHist->Draw();

//  TLegend *trafficLightsLegend = new TLegend(0.91,0.6,1,0.9);
  TLegend *trafficLightsLegend = new TLegend(0.91,0.65,1,0.9);
  trafficLightsLegend->SetLineColor(0);
  
  if (mode==1) {

    /* Traffic Lights:
      0: green (good) 
      1: dark green (good, hot)
      2: light green (no data, connected)
      3: amber (status uncertain)
      4: red (dead)
      5: dark red (channel trips)
      6: partially dark red/light green (one channel in this set of cells trips)
    */

    mon.trafficLights[0]->SetFillColor(kGreen-2);
    mon.trafficLights[1]->SetFillColor(kGreen+3);
    mon.trafficLights[2]->SetFillColor(kGreen);
    mon.trafficLights[3]->SetFillColor(kWhite);
    mon.trafficLights[4]->SetFillColor(kGray);
    mon.trafficLights[5]->SetFillColor(kRed+2);
    mon.trafficLights[6]->SetMarkerColor(kRed+2);
    mon.trafficLights[6]->SetMarkerStyle(23);
    mon.trafficLights[6]->SetMarkerSize(3);    
  
    //Drawn in this order to ensure partially tripping channels look right on plot
    mon.trafficLights[2]->Draw("same 5");
    mon.trafficLights[6]->Draw("same X P");
    mon.trafficLights[0]->Draw("same 5");
    mon.trafficLights[1]->Draw("same 5");
    mon.trafficLights[3]->Draw("same 5");
    mon.trafficLights[4]->Draw("same 5");
    mon.trafficLights[5]->Draw("same 5");

    trafficLightsLegend->AddEntry(mon.trafficLights[0],"Good");
    trafficLightsLegend->AddEntry(mon.trafficLights[1],"Good, hot");
    trafficLightsLegend->AddEntry(mon.trafficLights[2],"Connected");
 //   trafficLightsLegend->AddEntry(mon.trafficLights[3],"TBD");
    trafficLightsLegend->AddEntry(mon.trafficLights[4],"Disconnected");
    trafficLightsLegend->AddEntry(mon.trafficLights[5],"High Current");
    trafficLightsLegend->Draw();
  }

  if (mode >=10) {
    //black out off cells.
    mon.trafficLights[2]->SetFillColor(kBlack);
    mon.trafficLights[3]->SetFillColor(kBlack);
    mon.trafficLights[4]->SetFillColor(kBlack);
    mon.trafficLights[2]->Draw("same 2");
    mon.trafficLights[3]->Draw("same 2");
    mon.trafficLights[4]->Draw("same 2");

    //highlight hot cells
    mon.trafficLights[1]->SetFillColorAlpha(kPink,1);
    mon.trafficLights[1]->SetFillStyle(3344);
    mon.trafficLights[1]->SetLineColor(kPink);
    //mon.trafficLights[1]->SetLineWidth(10);
    mon.trafficLights[1]->Draw("same 2");
  }


  if (mode != 1){
    //black out off cells.

//    mon.trafficLights[1]->SetFillStyle(3144);
//    mon.trafficLights[1]->SetFillColor(kPink+9);
//    mon.trafficLights[1]->SetLineColor(kPink+9);
    mon.trafficLights[2]->SetFillColor(kBlack);
    mon.trafficLights[3]->SetFillColor(kBlack);
    mon.trafficLights[4]->SetFillColor(kBlack);


//    mon.trafficLights[1]->Draw("same 2");
    mon.trafficLights[2]->Draw("same 2");
    mon.trafficLights[3]->Draw("same 2");
    mon.trafficLights[4]->Draw("same 2"); 

  }

//  if (mode ==0) {
  if (mode > 10) {
    

    mon.trafficLights[0]->SetFillColor(kGreen-2);
//    mon.trafficLights[0]->Draw("same 5");
    mon.trafficLights[1]->SetFillColor(kGreen+3);
        mon.trafficLights[6]->SetMarkerColor(kGreen);
    mon.trafficLights[6]->SetMarkerStyle(30);
    mon.trafficLights[6]->SetMarkerSize(2);  
//    mon.trafficLights[1]->SetFillColorAlpha(kWhite,0.8);
//    mon.trafficLights[1]->Draw("same 5");

//    mon.trafficLights[2]->SetFillColorAlpha(kWhite,0.8);
    mon.trafficLights[2]->SetFillColor(kGreen);
    mon.trafficLights[4]->SetFillColor(kGray);
    mon.trafficLights[5]->SetFillColor(kRed+2);
//    mon.trafficLights[2]->Draw("same 5");
  //  mon.trafficLights[4]->Draw("same 5");
//    mon.trafficLights[5]->Draw("same 5");
//    mon.trafficLights[3]->Draw("same 5");

        mon.trafficLights[2]->Draw("same 5");
            mon.trafficLights[5]->Draw("same 5");
    mon.trafficLights[6]->Draw("same X P");
    mon.trafficLights[0]->Draw("same 5");
    mon.trafficLights[1]->Draw("same 5");
    mon.trafficLights[3]->Draw("same 5");
    mon.trafficLights[4]->Draw("same 5");


    mon.cellHighlight->SetFillColorAlpha(kPink+9,0.7);
    mon.cellHighlight->SetLineColor(kPink+9);
//    mon.cellHighlight->Draw("same 5");


    trafficLightsLegend->AddEntry(mon.trafficLights[0],"Good");
    trafficLightsLegend->AddEntry(mon.trafficLights[1],"Good, hot");
    trafficLightsLegend->AddEntry(mon.trafficLights[2],"Connected");
    trafficLightsLegend->AddEntry(mon.trafficLights[4],"Disconnected");
    trafficLightsLegend->AddEntry(mon.trafficLights[5],"Shorted");
    trafficLightsLegend->Draw();
  }

  //draw lines dividing sectors
  TLine *sectorLines[13];
  for (int i = 1; i <= 13; i++) {
    sectorLines[i-1] = new TLine(4*i,-0.2,4*i,9.2);
    sectorLines[i-1]->SetLineStyle(9);
    sectorLines[i-1]->SetLineColor(14);
    sectorLines[i-1]->SetLineWidth(2);
    sectorLines[i-1]->Draw("same");
  }

  //sector axis
  TGaxis *sectorAxis = new TGaxis(0,-1.2,56,-1.2,0,14,13,"+L");
  occupancyPercent->GetXaxis()->SetTitleOffset(0.8);
  sectorAxis->SetLabelFont(currentHist->GetXaxis()->GetLabelFont());
  sectorAxis->SetLabelSize(currentHist->GetXaxis()->GetLabelSize());
  sectorAxis->SetTitleFont(currentHist->GetXaxis()->GetTitleFont());
  sectorAxis->SetTitleSize(currentHist->GetXaxis()->GetTitleSize());
  sectorAxis->SetNdivisions(14);
  sectorAxis->SetTitle("Sector");
  sectorAxis->Draw("same");

  c1->Print(filename);
  
}
