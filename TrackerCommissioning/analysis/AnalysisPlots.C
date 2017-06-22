#define AnalysisPlots_cxx
#include "AnalysisPlots.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>

using namespace std;

void AnalysisPlots::RemapColumns(){

  if (runnum!=1000) {
    for (size_t i=0; i<v_column->size(); i++){ 
      /****************** FOR C1 *********************/
      /* Reverses order of cassettes within a sector */
      /***********************************************/ 
      if (runnum >= 172) {
          //swap cassettes within a sector, and columns within a cassette
          (*v_column)[i] = 4*((*v_column)[i]/4) + (((*v_column)[i]%4)*-1)+3;
          //move last cassette back two columns
          if ((*v_column)[i] >= 54) (*v_column)[i] = (*v_column)[i]-2;
          //swap back columns within a cassette
          (*v_column)[i] = (*v_column)[i] + (((((*v_column)[i])%2)*2)-1)*-1;
      }
    }
  }
}

void AnalysisPlots::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L AnalysisPlots.C
//      Root > AnalysisPlots t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch


  if (fChain == 0) return;
  
  //read run number from root file if we are using multiple runs in one file/chain
  runnum=-1;
  TBranch     *b_runnum;
  if (multiRunMode==1){
       fChain->SetBranchAddress("runnum", &runnum, &b_runnum);
  }
   

  Long64_t nentries = fChain->GetEntries();

  cout << "nentries is " << nentries << endl;



  Long64_t nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++)
  {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);
    if (nb == 0) continue;

    cout << "\revent number " << jentry << " of " << nentries << "                      ";

    int nHits;
    nHits = v_column->size();
    occupiedCells->Fill((double)nHits);

    RemapColumns();

    
    //fill number of triggers on a per-cell basis
    for (int columns = startcolumn; columns < endcolumn; columns++) {
      for (Int_t layers = startlayer; layers < endlayer; layers++) {
  	    if (isCellOnForRun(columns,layers,runnum,multiRunMode) == 1) {
  	      numTriggers->Fill(columns,layers);
  	    } //if
      } //for (layer)
    } //for (col)

    //for ignoring events with very low or very high numbers of hits
    if ((nHits >= nHitsLow) && (nHits <= nHitsHigh )) {


      for (size_t i=0; (int)i < nHits; i++)
  	  {
  	    int layer = (*v_layer)[i];
  	    int col = (*v_column)[i];
  	    int ano = (*v_anode)[i];
  	    int tc  = (*v_cattop)[i];
  	    int tb  = (*v_catbot)[i];
  	    float zh  = (*v_z)[i];
  	    float rh  = (*v_r)[i];
  	    float time = (*v_time)[i];
  	    int address = (*v_asicval)[i];
  	    int asicStatus = (*v_asicstat)[i];


  	    //1512*20 = 30240 = STOP_A (7620 in hex)
  	    float anoTime = maxanodetime - ano*20;
  	    float tcTime = tc * 20;
  	    float tbTime = tb * 20;

  	    //decode anode and cathode status bits

  	    unsigned int cellAddr, nCard, nAsic, nCell;
  	    bool aStat, khStat, kbStat, asicStat;

  	    cellAddr = (unsigned int)address;

  	    nCard = cellAddr/100;
  	    nAsic = (cellAddr-100*nCard)/10;
  	    nCell = cellAddr - 100*nCard - 10* nAsic;

  	    aStat = (asicStatus >> (nCell*3 ))&1;
  	    khStat = (asicStatus >> (nCell*3 +1) )&1;
  	    kbStat = (asicStatus >> (nCell*3 +2) )&1;

  	    anStat->Fill(anoTime,aStat);
  	    ctStat->Fill(tcTime,khStat);
  	    cbStat->Fill(tbTime,kbStat);


  	    //occupancy plots
        //*****************HISTOGRAMS FILLED HERE************************//
  	    if ((col>=startcolumn) && (col<=endcolumn) && (isCellOnForRun(col,layer,runnum,multiRunMode) == 1))  {

  	      occupancy->Fill(float(col),float(layer));
  	      occupancyPercent->Fill(float(col),float(layer)); 

  	      driftTime->Fill(float(col),float(layer),((float)anoTime/1000));
  	      if (khStat==0) driftTimect->Fill(float(col),float(layer),((float)tcTime/1000));
  	      if (kbStat==0) driftTimecb->Fill(float(col),float(layer),((float)tbTime/1000));
  	      if ((kbStat==0) && (khStat==0)) driftTimeCathodeTotal->Fill(float(col),float(layer),((float)(tbTime+tcTime)/1000));

  	      if (khStat==0) occupancyAnodeCtGood->Fill(float(col),float(layer));
  	      if (kbStat==0) occupancyAnodeCbGood->Fill(float(col),float(layer));
  	      if ((kbStat==0) && (khStat==0)) occupancyAnodeCBothGood->Fill(float(col),float(layer));
  	      if ((kbStat==0) || (khStat==0)) occupancyAnodeCEitherGood->Fill(float(col),float(layer));


  	      if (layer==4 && col==45) hotCellTime->Fill(anoTime/(float)1000);
  	      if (layer==4 && col==47) normalCellTime->Fill(anoTime/(float)1000);


          for (size_t j=0; (int)j <nHits; j++)
          {
            if (i==j) continue;
            int layerj = (*v_layer)[j];
            int colj = (*v_column)[j];

          }

  	      
  	    } //if (start/end column)

  	  } //for i (hits)

    } //if (nHitsLow <= nHits <= nHitsHigh)
    
  } //for jentry (event)

  //scale histograms appropriately and set a sensible NEntries
  driftTime->Divide(occupancy);
  driftTime->SetEntries(occupancy->GetEntries());
  driftTimect->Divide(occupancyAnodeCtGood);
  driftTimect->SetEntries(occupancyAnodeCtGood->GetEntries());
  driftTimecb->Divide(occupancyAnodeCbGood);
  driftTimecb->SetEntries(occupancyAnodeCbGood->GetEntries());
  driftTimeCathodeTotal->Divide(occupancyAnodeCBothGood);
  driftTimeCathodeTotal->SetEntries(occupancyAnodeCBothGood->GetEntries());
  
  occupancyPercent->Divide(numTriggers);
  occupancyPercent->Scale(100);
  occupancyPercent->SetEntries(nentries);
  occupancyAnodeCtGood->Divide(occupancy);
  occupancyAnodeCtGood->Scale(100);
  occupancyAnodeCtGood->SetEntries(driftTimect->GetEntries());
  occupancyAnodeCbGood->Divide(occupancy);
  occupancyAnodeCbGood->Scale(100);
  occupancyAnodeCbGood->SetEntries(driftTimecb->GetEntries());
  occupancyAnodeCBothGood->Divide(occupancy);
  occupancyAnodeCBothGood->Scale(100);
  occupancyAnodeCBothGood->SetEntries(driftTimeCathodeTotal->GetEntries());
  occupancyAnodeCEitherGood->Divide(occupancy);
  occupancyAnodeCEitherGood->Scale(100);
  occupancyAnodeCEitherGood->SetEntries(driftTimect->GetEntries()+driftTimecb->GetEntries()-driftTimeCathodeTotal->GetEntries());
  occupancyCathodeSum->Add(occupancyAnodeCtGood);
  occupancyCathodeSum->Add(occupancyAnodeCbGood);

  //create overlays and calculate statistics
     double avOccupancy=0, avOccupancyGood=0, avOccupancyCEither=0, avOccupancyCBoth = 0;

     double avDriftTime=0, avPropTime=0;
     int nCells=layers*columns, nGoodCells=0, nGoodCellsCEither=0, nGoodCellsCBoth=0;
     Double_t binContent, binContentCEither, binContentCBoth, binContentCTop, binContentCBottom;
     int nGreenCells=0, nLightGreenCells=0, nDarkGreenCells=0;

     int nCatBothLow=0;
     int sectorCtLow[14]={0,0,0,0,0,0,0,0,0,0,0,0,0,0};
     int sectorCbLow[14]={0,0,0,0,0,0,0,0,0,0,0,0,0,0};
     int sectorAnLow[14]={0,0,0,0,0,0,0,0,0,0,0,0,0,0};
     
    for (Int_t ibx = startcolumn; ibx <= endcolumn; ibx++) {
      for (Int_t iby = startlayer; iby <= endlayer; iby++) {
	
      	if (!(occupancyPercent->IsBinUnderflow(occupancyPercent->GetBin(ibx,iby)) || occupancyPercent->IsBinOverflow(occupancyPercent->GetBin(ibx,iby))))
      	  {
      	    binContent = occupancyPercent->GetBinContent(ibx,iby);
      	    binContentCEither = occupancyAnodeCEitherGood->GetBinContent(ibx,iby);
      	    binContentCBoth = occupancyAnodeCBothGood->GetBinContent(ibx,iby);
      	    binContentCTop = occupancyAnodeCtGood->GetBinContent(ibx,iby);
      	    binContentCBottom = occupancyAnodeCbGood->GetBinContent(ibx,iby);
      	    
      	    avOccupancy+=binContent;
      	    
      	    // FEEDTHROUGH LAYOUT 
      	    // we subtract 1 from ibx, iby as bin 0 in each direction is underflow bin not bin at x,y=0.*/
        	  int xOffset,yOffset;
      	    cassette_to_FT((ibx-1)%2, 9 - (iby-1), &xOffset, &yOffset);
      	    occupancyFT->Fill(6*((int)(ibx-1)/4) + xOffset, 5-5*(((int)(ibx-1)/2)%2) + yOffset,binContent);


      	    Double_t xBinMin = occupancyPercent->GetXaxis()->GetBinLowEdge(ibx);
      	    Double_t xBinMax = occupancyPercent->GetXaxis()->GetBinUpEdge(ibx);
      	    Double_t yBinMin = occupancyPercent->GetYaxis()->GetBinLowEdge(iby);
      	    Double_t yBinMax = occupancyPercent->GetYaxis()->GetBinUpEdge(iby);

      	    if ((binContent <= hotcelloccupancy) && (binContent > coldcelloccupancy)) {
      	      	trafficLights[0]->SetPoint(nGreenCells+1, xBinMin + (xBinMax-xBinMin)/2, yBinMin + (yBinMax-yBinMin)/2);
      		      trafficLights[0]->SetPointError(nGreenCells+1,(xBinMax-xBinMin)/2,(yBinMax-yBinMin)/2);
      		      nGreenCells++;
      	    } else {           
              if (binContent > hotcelloccupancy) {
        	      	trafficLights[1]->SetPoint(nDarkGreenCells+1, xBinMin + (xBinMax-xBinMin)/2, yBinMin + (yBinMax-yBinMin)/2);
        		      trafficLights[1]->SetPointError(nDarkGreenCells+1,(xBinMax-xBinMin)/2,(yBinMax-yBinMin)/2);
        		      nDarkGreenCells++;
        	    }
            } //if else

      	    if (binContent <= coldcelloccupancy) {
              //****** "cold"/no data  ******
      	      	trafficLights[2]->SetPoint(nLightGreenCells+1, xBinMin + (xBinMax-xBinMin)/2, yBinMin + (yBinMax-yBinMin)/2);
      		      sectorAnLow[(int)(ibx-1)/4]++;
      		      trafficLights[2]->SetPointError(nLightGreenCells+1,(xBinMax-xBinMin)/2,(yBinMax-yBinMin)/2);
      		      nLightGreenCells++;
      	    } else
      	    {
              //****** good or hot cells ******
      	      if ((binContent <= hotcelloccupancy) /*&& ((ibx <12)||(ibx>=16))*/) {
            		avOccupancyGood+=binContent;
            		nGoodCells++;

            		if (binContentCEither > mincathodeoccupancy) {
                  nGoodCellsCEither++;
                  occupancyCEitherDist->Fill(occupancyAnodeCEitherGood->GetBinContent(ibx,iby));
                }

                if (binContentCTop > mincathodeoccupancy) {
                  occupancyCtDist->Fill(occupancyAnodeCtGood->GetBinContent(ibx,iby));
                }

                if (binContentCBottom > mincathodeoccupancy) {
                  occupancyCbDist->Fill(occupancyAnodeCbGood->GetBinContent(ibx,iby));
                }


            		avOccupancyCEither+=binContentCEither;

            		if (binContentCBoth > mincathodeoccupancy) {
            		  nGoodCellsCBoth++;
            		  avPropTime+=driftTimeCathodeTotal->GetBinContent(ibx,iby);
            		  propTimeDist->Fill(driftTimeCathodeTotal->GetBinContent(ibx,iby));
                  occupancyCBothDist->Fill(occupancyAnodeCBothGood->GetBinContent(ibx,iby));
            		}
            		avOccupancyCBoth+=binContentCBoth;

                occupancyDist->Fill(occupancyPercent->GetBinContent(ibx,iby));
            		avDriftTime+=driftTime->GetBinContent(ibx,iby);
            		driftTimeDist->Fill(driftTime->GetBinContent(ibx,iby));
      	      }
      	    } //if else

      	    if ((binContentCTop > 10) && (binContentCTop < 70) && (binContentCBottom > 10) && (binContentCBottom < 70)) nCatBothLow++;
      	    if (binContentCTop < 10) sectorCtLow[(int)(ibx-1)/4]++;
      	    if (binContentCBottom < 10) sectorCbLow[(int)(ibx-1)/4]++;


      	 } //if (not underflow/overflow)

      } //for iby (layers)

    } //for ibx (columns)

    if ((runnum==-1) && (multiRunMode==1)) {
      cout << "ERROR: Using multiple input files without specifying run numbers" << endl;
      return;
    }

    cout << endl;
    
    cout << "average occupancy of all cells " << avOccupancy/nCells << endl << endl;
    
    cout << "proportion of cells with good occupancy " << (double)nGoodCells/nCells << endl;
    cout << "proportion of cells connected " << (double)(nCells - nAmberCells - nRedCells - nAltRedCells)/nCells << endl;
    cout << "average occupancy of good cells "<< avOccupancyGood/nGoodCells << endl << endl;
    
    cout << "proportion of good cells with reasonable occupancy and either cathode good " << (double)nGoodCellsCEither/nGoodCells << endl;
    cout << "average % of anode hits "<< avOccupancyCEither/nGoodCells << endl << endl;
   
    cout << "proportion of good cells with reasonable occupancy and both cathodes good " << (double)nGoodCellsCBoth/nGoodCells << endl;
    cout << "average % of anode hits "<< avOccupancyCBoth/nGoodCells << endl << endl;

    cout << "average drift time (good cells) " << avDriftTime/nGoodCells << endl;
    cout << "average propagation time (good cells/cathodes) " << avPropTime/nGoodCellsCBoth<< endl;

    cout << "number of cold cells " << nLightGreenCells << endl;
    cout << "number of hot cells " << nDarkGreenCells << endl;

     for (int i=0;i<14;i++){
        cout << "sector "<<i<<" anLow "<<sectorAnLow[i] << " cTLow " << sectorCtLow[i] << " cBLow " << sectorCbLow[i] << endl;
     }
      						       						      
}

int AnalysisPlots::isCellOnForRun(int col, int layer, int runnum, int multiRunMode)
//lists which cells are taking data for which runs
{
  if (multiRunMode != 1) return 1;

  int isOn=0;
  
  switch( runnum ) 
    {
      /****************************************************/
      /*********-------------  C0  ---------***************/
      /****************************************************/
      case 98: if ((col >= 36) && (col<52)) /*sectors 9-12*/
      	{
      	  isOn=1;
      	  /*sector 10 - one bulk daughterboard disconnected*/
      	  if ((col==43) && ((layer > 0) && (layer < 8))) isOn=0;
      	}
      break;
      case 99 : /*same as 98*/
        if ((col >= 36) && (col<52)) /*sectors 9-12*/
      	{
      	  isOn=1;
      	  /*sector 10 - one bulk daughterboard disconnected*/
      	  if ((col==43) && ((layer > 0) && (layer < 8))) isOn=0;
      	}
      break;
      case 100 : if (((col >= 24) && (col<36)) || ((col >= 52) && (col < 56))) isOn=1; break;  /*sectors 6-8 and 13*/
      case 102 : if (((col >= 24) && (col<36)) || ((col >= 52) && (col < 56))) isOn=1; break;  /*sectors 6-8 and 13*/
      case 103 : if (((col >= 24) && (col<36)) || ((col >= 52) && (col < 56))) isOn=1; break;  /*sectors 6-8 and 13*/
      case 106 : if (((col >= 24) && (col<36)) || ((col >= 52) && (col < 56))) isOn=1; break;  /*sectors 6-8 and 13*/
      case 107 : if ((col >= 4) && (col<20)) isOn=1; break; /*sectors 1-4*/
      case 110 : if ((col >= 4) && (col<20)) isOn=1; break; /*sectors 1-4*/
      case 111 : if ((col >= 4) && (col<20)) isOn=1; break; /*sectors 1-4*/
      case 114 : if ( (col<4) || ((col >= 8) && (col < 16)) || ((col >= 20) && (col < 24)) ) isOn=1; break; /*sectors 0, 2-3 and 5*/
      case 115 : if ( (col<4) || ((col >= 8) && (col < 16)) || ((col >= 20) && (col < 24)) ) isOn=1; break; /*sectors 0, 2-3 and 5*/

      /****************************************************/
      /*********-------------  C1  ---------***************/
      /****************************************************/

      case 174 : if (col<4) isOn=1; break; /*sector 0*/
      case 182 : if ((col<4) || ((col >=8) && (col < 12)))  isOn=1; break; /*sectors 0 and 2*/
      case 184 : if ((col<4) || ((col >=8) && (col < 12)))  isOn=1; break; /*sectors 0 and 2*/
      case 195 : if ((col<4) || ((col >=8) && (col < 12)))  isOn=1; break; /*sectors 0 and 2*/
      case 196 : if ((col<4) || ((col >=8) && (col < 12)))  isOn=1; break; /*sectors 0 and 2*/
      case 197 : if ((col<4) || ((col >=8) && (col < 12)))  isOn=1; break; /*sectors 0 and 2*/
      case 198 : if ((col<4) || ((col >=8) && (col < 12)))  isOn=1; break; /*sectors 0 and 2*/
      case 199 : if ((col<4) || ((col >=8) && (col < 12)))  isOn=1; break; /*sectors 0 and 2*/
      case 200 : if ((col<4) || ((col >=8) && (col < 12)))  isOn=1; break; /*sectors 0 and 2*/
      case 202 : if (col<16)  isOn=1; break;                             /*sectors 0-3*/
      case 203 : if (col<12)  isOn=1; break;                             /*sectors 0-2*/
      case 206 : if (col<12)  isOn=1; break;                             /*sectors 0-2*/
      case 207 : if (col<12)  isOn=1; break;                             /*sectors 0-2*/
      case 208 : if ((col>=20) && (col < 32))  isOn=1; break;            /*sectors 5-7*/
      case 209 : if ((col>=16) && (col < 32))  isOn=1; break;            /*sectors 4-7*/
      case 210 : if ((col>=16) && (col < 32))  isOn=1; break;            /*sectors 4-7*/
      case 211 : if ((col>=16) && (col < 32))  isOn=1; break;            /*sectors 4-7*/
      case 212 : if ((col>=16) && (col < 32))  isOn=1; break;            /*sectors 4-7*/
      case 217 : if ((col>=32) && (col < 48))  isOn=1; break;            /*sectors 8-11*/
      case 222 : if ((col>=32) && (col < 48))  isOn=1; break;            /*sectors 8-11*/
      case 225 : if ((col>=32) && (col < 48))  isOn=1; break;            /*sectors 8-11*/
      case 226 : if ((col>=32) && (col < 48))  isOn=1; break;            /*sectors 8-11*/
      case 227 : if ((col>=32) && (col < 48))  isOn=1; break;            /*sectors 8-11*/
      case 228 : if ((col>=32) && (col < 48))  isOn=1; break;            /*sectors 8-11*/
      case 229 : if ((col>=32) && (col < 48))  isOn=1; break;            /*sectors 8-11*/
      case 230 : if ((col>=32) && (col < 48))  isOn=1; break;            /*sectors 8-11*/
      case 231 : if ((col>=32) && (col < 48))  isOn=1; break;            /*sectors 8-11*/
      case 232 : if ((col>=32) && (col < 48))  isOn=1; break;            /*sectors 8-11*/
      case 233 : if ((col>=32) && (col < 48))  isOn=1; break;            /*sectors 8-11*/
      case 235 : if (((col>=36) && (col < 44)) || ((col>=48) && (col < 56)))   isOn=1; break;  /*sectors 9,10,12 and half of 13*/
      case 236 : if (((col>=36) && (col < 44)) || ((col>=48) && (col < 56)))   isOn=1; break;  /*sectors 9,10,12 and half of 13*/
      case 237 : if (((col>=36) && (col < 44)) || ((col>=48) && (col < 56)))   isOn=1; break;  /*sectors 9,10,12 and half of 13*/
      case 240 : if (((col>=36) && (col < 44)) || ((col>=48) && (col < 56)))   isOn=1; break;  /*sectors 9,10,12 and half of 13*/
      case 241 : if (((col>=36) && (col < 44)) || ((col>=48) && (col < 56)))   isOn=1; break;  /*sectors 9,10,12 and half of 13*/
      case 242 : if (((col>=36) && (col < 44)) || ((col>=48) && (col < 56)))   isOn=1; break;  /*sectors 9,10,12 and half of 13*/
      case 243 : if (((col>=36) && (col < 40)) || ((col>=48) && (col < 56)))   isOn=1; break;  /*sectors 9,12 and half of 13*/
      case 246 : if (((col>=36) && (col < 40)) || ((col>=48) && (col < 56)))   isOn=1; break;  /*sectors 9,12 and half of 13*/
      case 247 : if (((col>=36) && (col < 40)) || ((col>=48) && (col < 56)))   isOn=1; break;  /*sectors 9,12 and half of 13*/
      case 248 : if (((col>=36) && (col < 40)) || ((col>=48) && (col < 56)))   isOn=1; break;  /*sectors 9,12 and half of 13*/
      case 249 : if (((col>=36) && (col < 40)) || ((col>=48) && (col < 56)))   isOn=1; break;  /*sectors 9,12 and half of 13*/
      case 250 : if (((col>=36) && (col < 40)) || ((col>=48) && (col < 56)))   isOn=1; break;  /*sectors 9,12 and half of 13*/
      case 251 : if (((col>=36) && (col < 40)) || ((col>=48) && (col < 56)))   isOn=1; break;  /*sectors 9,12 and half of 13*/
      case 252 : if (((col>=36) && (col < 40)) || ((col>=48) && (col < 56)))   isOn=1; break;  /*sectors 9,12 and half of 13*/     

      /****************************************************/
      /*********-------------  C2  ---------***************/
      /****************************************************/

      case 259 : if ((col>=12) && (col < 16))   isOn=1; break;    /*sector 3 only*/
      case 262 : /*same as 98*/
        if (col<16) /*sectors 0-3*/
        {
          isOn=1;
          /*sector 1 - bulk tripped, so ignore*/
          if (((col>=4) && (col < 8)) && ((layer > 0) && (layer < 8))) isOn=0;
        }
      break;
      case 264 : if (col<16)  isOn=1; break;  /*sectors 0-3*/
      case 265 : if (col<16)  isOn=1; break;  /*sectors 0-3*/
      case 266 : if (col<16)  isOn=1; break;  /*sectors 0-3*/
      case 267 : if (col<16)  isOn=1; break;  /*sectors 0-3*/
      case 269 : if (((col>=16) && (col < 20)) || ((col>=24) && (col < 32)))   isOn=1; break;  /*sectors 4,6,7*/     
      case 270 : if (((col>=16) && (col < 20)) || ((col>=24) && (col < 32)))   isOn=1; break;  /*sectors 4,6,7*/ 
      case 271 : if (((col>=16) && (col < 20)) || ((col>=24) && (col < 32)))   isOn=1; break;  /*sectors 4,6,7*/ 
      case 272 : if (((col>=16) && (col < 20)) || ((col>=24) && (col < 32)))   isOn=1; break;  /*sectors 4,6,7*/ 
      case 273 : if (((col>=16) && (col < 20)) || ((col>=24) && (col < 32)))   isOn=1; break;  /*sectors 4,6,7*/ 
      case 274 : if (((col>=16) && (col < 20)) || ((col>=24) && (col < 32)))   isOn=1; break;  /*sectors 4,6,7*/ 
      case 275 : if (((col>=16) && (col < 20)) || ((col>=24) && (col < 32)))   isOn=1; break;  /*sectors 4,6,7*/ 
      case 276 : if (((col>=16) && (col < 20)) || ((col>=24) && (col < 32)))   isOn=1; break;  /*sectors 4,6,7*/ 
      case 277 : if (((col>=16) && (col < 20)) || ((col>=24) && (col < 32)))   isOn=1; break;  /*sectors 4,6,7*/ 
      case 278 : if (((col>=16) && (col < 20)) || ((col>=24) && (col < 32)))   isOn=1; break;  /*sectors 4,6,7*/ 
      case 279 : if (((col>=16) && (col < 20)) || ((col>=24) && (col < 32)))   isOn=1; break;  /*sectors 4,6,7*/ 
      case 280 : if (((col>=16) && (col < 20)) || ((col>=24) && (col < 32)))   isOn=1; break;  /*sectors 4,6,7*/ 
      case 281 : if (((col>=16) && (col < 20)) || ((col>=24) && (col < 32)))   isOn=1; break;  /*sectors 4,6,7*/ 
      case 282 : if (((col>=16) && (col < 20)) || ((col>=24) && (col < 32)))   isOn=1; break;  /*sectors 4,6,7*/ 
      case 283 : if (((col>=16) && (col < 20)) || ((col>=24) && (col < 32)))   isOn=1; break;  /*sectors 4,6,7*/ 
      case 284 : if (((col>=16) && (col < 20)) || ((col>=24) && (col < 32)))   isOn=1; break;  /*sectors 4,6,7*/ 
      case 285 : if (((col>=16) && (col < 20)) || ((col>=24) && (col < 32)))   isOn=1; break;  /*sectors 4,6,7*/ 
      case 286 : if (((col>=16) && (col < 20)) || ((col>=24) && (col < 32)))   isOn=1; break;  /*sectors 4,6,7*/ 
      case 287 : if (((col>=16) && (col < 20)) || ((col>=24) && (col < 32)))   isOn=1; break;  /*sectors 4,6,7*/ 
      case 288 : if (((col>=16) && (col < 20)) || ((col>=24) && (col < 32)))   isOn=1; break;  /*sectors 4,6,7*/ 
      case 289 : if (((col>=16) && (col < 20)) || ((col>=24) && (col < 32)))   isOn=1; break;  /*sectors 4,6,7*/ 
      case 290 : if (((col>=16) && (col < 20)) || ((col>=24) && (col < 32)))   isOn=1; break;  /*sectors 4,6,7*/ 
      case 291 : if (((col>=16) && (col < 20)) || ((col>=24) && (col < 32)))   isOn=1; break;  /*sectors 4,6,7*/ 
      case 292 : if (((col>=16) && (col < 20)) || ((col>=24) && (col < 32)))   isOn=1; break;  /*sectors 4,6,7*/ 
      case 293 : if (((col>=16) && (col < 20)) || ((col>=24) && (col < 32)))   isOn=1; break;  /*sectors 4,6,7*/ 
      case 294 : if (((col>=16) && (col < 20)) || ((col>=24) && (col < 32)))   isOn=1; break;  /*sectors 4,6,7*/
      case 297 : if ((col>=20) && (col < 24))  isOn=1; break;  /*sector 5*/          
      case 298 : if ((col>=32) && (col < 48))  isOn=1; break;  /*sectors 8-11*/            
      case 299 : if ((col>=32) && (col < 48))  isOn=1; break;  /*sectors 8-11*/         
      case 300 : if ((col>=32) && (col < 48))  isOn=1; break;  /*sectors 8-11*/         
      case 301 : if ((col>=32) && (col < 48))  isOn=1; break;  /*sectors 8-11*/         
      case 302 : if (((col>=36) && (col < 40)) || ((col>=48) && (col < 54)))   isOn=1; break;  /*sectors 9, 12 and half of 13*/        
      case 303 : if ((col>=48) && (col < 54))  isOn=1; break;  /*sectors 8-11*/ 
      case 304 : if ((col>=48) && (col < 54))  isOn=1; break;  /*sectors 8-11*/ 
      default: return 1;
    }

  return isOn;
}

void AnalysisPlots::cassette_to_FT(int cassetteColA, int cassetteLayer, int* xOffset, int* yOffset){
//maps cassette cell locations to feedthrough pins  
  if (cassetteColA == 1){
    switch( cassetteLayer ) 
    {
    case 1:
      *xOffset=4;
      *yOffset=3;
      return;
    case 2:
      *xOffset=3;
      *yOffset=3;
      return;
    case 3:
      *xOffset=2;
      *yOffset=3;
      return;
    case 4:
      *xOffset=1;
      *yOffset=3;
      return;
    case 5:
      *xOffset=0;
      *yOffset=3;
      return;
    case 6:
      *xOffset=4;
      *yOffset=2;
      return;
    case 7:
      *xOffset=3;
      *yOffset=2;
      return;
    case 8:
      *xOffset=1;
      *yOffset=2;
      return;
    case 9:
      *xOffset=0;
      *yOffset=2;
      return;
    default:
      *xOffset=9999;
      *yOffset=9999;
      return;
    }
  }


  if (cassetteColA == 0){
    switch( cassetteLayer ) 
    {
    case 1:
      *xOffset=4;
      *yOffset=1;
      return;
    case 2:
      *xOffset=3;
      *yOffset=1;
      return;
    case 3:
      *xOffset=1;
      *yOffset=1;
      return;
    case 4:
      *xOffset=0;
      *yOffset=1;
      return;
    case 5:
      *xOffset=4;
      *yOffset=0;
      return;
    case 6:
      *xOffset=3;
      *yOffset=0;
      return;
    case 7:
      *xOffset=2;
      *yOffset=0;
      return;
    case 8:
      *xOffset=1;
      *yOffset=0;
      return;
    case 9:
      *xOffset=0;
      *yOffset=0;
      return;
    default:
      *xOffset=9999;
      *yOffset=9999;
      return;
    }
  }
}
