#include <TVirtualFitter.h>
#include"TotalMC_1e.h"
#include"TotalMC_1e1g.h"
#include"TotalMC_1e2g.h"
#include"TotalMC_1e1a.h"
#include"TotalMC_OCE.h"
#include"TotalMC_ExtEG.h"
#include"TotalMC_2b2n.h"

// 1e
extern TH1D* h_1e_Data_P1_SeOld;
extern TH1D* h_1e_Data_P1_SeNew;
extern TH1D* h_1e_Data_P1_Strip;
extern TH1D* h_1e_Data_P2_SeOld;
extern TH1D* h_1e_Data_P2_SeNew;
extern TH1D* h_1e_Data_P2_Strip;
// 1e1g
extern TH1D* h_1e1g_Data_P1_SeOld;
extern TH1D* h_1e1g_Data_P1_SeNew;
extern TH1D* h_1e1g_Data_P1_Strip;
extern TH1D* h_1e1g_Data_P2_SeOld;
extern TH1D* h_1e1g_Data_P2_SeNew;
extern TH1D* h_1e1g_Data_P2_Strip;
// 1e2g
extern TH1D* h_1e2g_Data_SeOld;
extern TH1D* h_1e2g_Data_SeNew;
// 1e1a
extern TH1D* h_1e1a_Data_P1_aOuteOut_Sector6; 
extern TH1D* h_1e1a_Data_P1_aIneOut_Sector6;  
extern TH1D* h_1e1a_Data_P1_aOuteIn_Sector6;  
extern TH1D* h_1e1a_Data_P1_aIneIn_Sector6;   
extern TH1D* h_1e1a_Data_P1_aOuteOut_Sector7; 
extern TH1D* h_1e1a_Data_P1_aIneOut_Sector7;  
extern TH1D* h_1e1a_Data_P1_aOuteIn_Sector7;  
extern TH1D* h_1e1a_Data_P1_aIneIn_Sector7;   
extern TH1D* h_1e1a_Data_P1_aOuteOut_Sector8; 
extern TH1D* h_1e1a_Data_P1_aIneOut_Sector8;  
extern TH1D* h_1e1a_Data_P1_aOuteIn_Sector8;  
extern TH1D* h_1e1a_Data_P1_aIneIn_Sector8;   
extern TH1D* h_1e1a_Data_P1_AllEvents_Sector6;
extern TH1D* h_1e1a_Data_P1_AllEvents_Sector7;
extern TH1D* h_1e1a_Data_P1_AllEvents_Sector8;
extern TH1D* h_1e1a_Data_P2_aOuteOut_Sector6;
extern TH1D* h_1e1a_Data_P2_aIneOut_Sector6;  
extern TH1D* h_1e1a_Data_P2_aOuteIn_Sector6;  
extern TH1D* h_1e1a_Data_P2_aIneIn_Sector6;  
extern TH1D* h_1e1a_Data_P2_aOuteOut_Sector7; 
extern TH1D* h_1e1a_Data_P2_aIneOut_Sector7;  
extern TH1D* h_1e1a_Data_P2_aOuteIn_Sector7;  
extern TH1D* h_1e1a_Data_P2_aIneIn_Sector7;   
extern TH1D* h_1e1a_Data_P2_aOuteOut_Sector8; 
extern TH1D* h_1e1a_Data_P2_aIneOut_Sector8;  
extern TH1D* h_1e1a_Data_P2_aOuteIn_Sector8;  
extern TH1D* h_1e1a_Data_P2_aIneIn_Sector8;  
extern TH1D* h_1e1a_Data_P2_AllEvents_Sector6;
extern TH1D* h_1e1a_Data_P2_AllEvents_Sector7;
extern TH1D* h_1e1a_Data_P2_AllEvents_Sector8;
// OCE
extern TH1D* h_OCE_Data_P1_Inner;
extern TH1D* h_OCE_Data_P1_Outer;
extern TH1D* h_OCE_Data_P1_Petal;
extern TH1D* h_OCE_Data_P2_Inner;
extern TH1D* h_OCE_Data_P2_Outer;
extern TH1D* h_OCE_Data_P2_Petal;
// ExtEG
extern TH1D* h_ExtEG_Data_P1_Inner;
extern TH1D* h_ExtEG_Data_P1_Outer;
extern TH1D* h_ExtEG_Data_P1_Petal;
extern TH1D* h_ExtEG_Data_P2_Inner;
extern TH1D* h_ExtEG_Data_P2_Outer;
extern TH1D* h_ExtEG_Data_P2_Petal;
// 2b2n
extern TH1D* h_2b2n_Data_SeOld; 
extern TH1D* h_2b2n_Data_SeNew; 

void logLikelihood(Int_t & /*nPar*/, Double_t * /*grad*/ , Double_t &fval, Double_t *p, Int_t /*iflag */  );

void fitBackgrounds(double *AdjustActs, double *AdjustActs_Err, Double_t CovMatrix[][44]){

  // Set Minuit2 as fitting algorithm and declare fitter
  TVirtualFitter::SetDefaultFitter("Minuit2");
  TVirtualFitter * minuit2 = TVirtualFitter::Fitter(0,44);

  // Set parameters and minimising function

  //1e1a Samples
  minuit2->SetParameter(0, "Bi-214 SeNew"          , AdjustActs[0],  AdjustActs[0]*0.1,  0, 1000);
  minuit2->SetParameter(1, "Bi-214 SeOld"          , AdjustActs[1],  AdjustActs[1]*0.1,  0, 1000);
  minuit2->SetParameter(2, "Bi-214 Mylar"          , AdjustActs[2],  AdjustActs[2]*0.1,  0, 1000);
  minuit2->SetParameter(3, "Phase Radon Ratio"     , AdjustActs[3],  AdjustActs[3]*0.1,  0, 1000);
  minuit2->SetParameter(4, "Bi-214 SWire P2"       , AdjustActs[4],  AdjustActs[4]*0.1,  0, 1000);
  minuit2->SetParameter(5, "Bi-214 SFoil In P2"    , AdjustActs[5],  AdjustActs[5]*0.1,  0, 1000);
  minuit2->SetParameter(6, "Bi-214 SFoil Out P2"   , AdjustActs[6],  AdjustActs[6]*0.1,  0, 1000);

  // 1e2g Samples 
  minuit2->SetParameter(7, "Tl-208 SWire P1"       , AdjustActs[7],  AdjustActs[7]*0.1,  0, 1000);
  minuit2->SetParameter(8, "Tl-208 SWire P2"       , AdjustActs[8],  AdjustActs[8]*0.1,  0, 1000);
  minuit2->SetParameter(9, "Tl-208 SeNew"          , AdjustActs[9],  AdjustActs[9]*0.1,  0, 1000);
  minuit2->SetParameter(10,"Tl-208 SeOld"          , AdjustActs[10], AdjustActs[10]*0.1, 0, 1000);
										  								  						  
  // External/1e1g Samples							  					  			  
  minuit2->SetParameter(11,"K-40 PMT"              , AdjustActs[11], AdjustActs[11]*0.1, 0, 1000);
  minuit2->SetParameter(12,"K-40 Steel Frame"      , AdjustActs[12], AdjustActs[12]*0.1, 0, 1000);
  minuit2->SetParameter(13,"K-40 Scint Inner"      , AdjustActs[13], AdjustActs[13]*0.1, 0, 1000);
  minuit2->SetParameter(14,"K-40 Scint Outer"      , AdjustActs[14], AdjustActs[14]*0.1, 0, 1000);
  minuit2->SetParameter(15,"K-40 Scint Petals"     , AdjustActs[15], AdjustActs[15]*0.1, 0, 1000);
  minuit2->SetParameter(16,"Bi-214 PMT"            , AdjustActs[16], AdjustActs[16]*0.1, 0, 1000);
  minuit2->SetParameter(17,"Bi-214 Fe Shield"      , AdjustActs[17], AdjustActs[17]*0.1, 0, 1000);
  minuit2->SetParameter(18,"Bi-214 Steel Frame"    , AdjustActs[18], AdjustActs[18]*0.1, 0, 1000);
  minuit2->SetParameter(19,"Bi-214 SScin P2"       , AdjustActs[19], AdjustActs[19]*0.1, 0, 1000);
  minuit2->SetParameter(20,"Bi-214 LSM Air"        , AdjustActs[20], AdjustActs[20]*0.1, 0, 1000);
  minuit2->SetParameter(21,"Tl-208 PMT"            , AdjustActs[21], AdjustActs[21]*0.1, 0, 1000);
  minuit2->SetParameter(22,"Tl-208 Fe Shield"      , AdjustActs[22], AdjustActs[22]*0.1, 0, 1000);
  minuit2->SetParameter(23,"Tl-208 Steel Frame"    , AdjustActs[23], AdjustActs[23]*0.1, 0, 1000);
  minuit2->SetParameter(24,"Tl-208 LSM Air"        , AdjustActs[24], AdjustActs[24]*0.1, 0, 1000);
  minuit2->SetParameter(25,"Co-60 Mu Metal"        , AdjustActs[25], AdjustActs[25]*0.1, 0, 1000);
  minuit2->SetParameter(26,"Co-60 Steel Frame"     , AdjustActs[26], AdjustActs[26]*0.1, 0, 1000);
  minuit2->SetParameter(27,"Co-60 Cu Petals"       , AdjustActs[27], AdjustActs[27]*0.1, 0, 1000);
  minuit2->SetParameter(28,"Co-60 Cu Tower"        , AdjustActs[28], AdjustActs[28]*0.1, 0, 1000);
  minuit2->SetParameter(29,"Bi-210 SScin"          , AdjustActs[29], AdjustActs[29]*0.1, 0, 1000);
  minuit2->SetParameter(30,"Bi-210 SWire"          , AdjustActs[30], AdjustActs[30]*0.1, 0, 1000);
  minuit2->SetParameter(31,"Pa-234m SScin"         , AdjustActs[31], AdjustActs[31]*0.1, 0, 1000);
  minuit2->SetParameter(32,"g-1000 MuMetal P1"     , AdjustActs[32], AdjustActs[32]*0.1, 0, 1000);
  minuit2->SetParameter(33,"g-1000 MuMetal P2"     , AdjustActs[33], AdjustActs[33]*0.1, 0, 1000);
  minuit2->SetParameter(34,"Neutrons P1"           , AdjustActs[34], AdjustActs[34]*0.1, 0, 1000);
  minuit2->SetParameter(35,"Neutrons P2"           , AdjustActs[35], AdjustActs[35]*0.1, 0, 1000);
										  								  						  
  // 1e Samples									  							  					  
  minuit2->SetParameter(36,"Bi-210 SFoil SeNew"    , AdjustActs[36], AdjustActs[36]*0.1, 0, 1000);
  minuit2->SetParameter(37,"Bi-210 SFoil SeOld"    , AdjustActs[37], AdjustActs[37]*0.1, 0, 1000);
  minuit2->SetParameter(38,"Bi-210 SFoil Strip"    , AdjustActs[38], AdjustActs[38]*0.1, 0, 1000);
  minuit2->SetParameter(39,"Pa-234m SeNew"         , AdjustActs[39], AdjustActs[39]*0.1, 0, 1000);
  minuit2->SetParameter(40,"Pa-234m SeOld"         , AdjustActs[40], AdjustActs[40]*0.1, 0, 1000);
  minuit2->SetParameter(41,"K-40 SeNew"            , AdjustActs[41], AdjustActs[41]*0.1, 0, 1000);
  minuit2->SetParameter(42,"K-40 SeOld"            , AdjustActs[42], AdjustActs[42]*0.1, 0, 1000);
										  								  						  
  // Signal Sample								  						  				  
  minuit2->SetParameter(43,"Se 2b2n"               , AdjustActs[43], AdjustActs[43]*0.1, 0, 1000);
										  								  						  
  minuit2->SetFCN(logLikelihood);

  // Array to pass arguments to fitter
  double arglist[100];
  arglist[0] = 0;

  // Set print level
  //  minuit2->ExecuteCommand("SET PRINT",arglist,2);

  // Do minimisation
  arglist[0] = 100000;  // number of function calls
  arglist[1] = 0.01;  // tolerance
  minuit2->ExecuteCommand("MIGRAD",arglist,2);

  // Then get results
  for(int i = 0; i < 44; i++){
    AdjustActs[i]     = minuit2->GetParameter(i);
    AdjustActs_Err[i] = minuit2->GetParError(i);
  }

  for(int i = 0; i < 44; i++){
    for(int j = 0; j < 44; j++){
      CovMatrix[i][j] = minuit2->GetCovarianceMatrixElement(i,j);
    }
  }

}

void logLikelihood(Int_t & /*nPar*/, Double_t * /*grad*/ , Double_t &fval, Double_t *par, Int_t /*iflag */  ){

  TH1D* h1  = h_1e1a_Data_P1_aOuteOut_Sector6; 
  TH1D* h2  = h_1e1a_Data_P1_aIneOut_Sector6;  
  TH1D* h3  = h_1e1a_Data_P1_aOuteIn_Sector6;  
  TH1D* h4  = h_1e1a_Data_P1_aIneIn_Sector6;   
  TH1D* h5  = h_1e1a_Data_P1_aOuteOut_Sector7; 
  TH1D* h6  = h_1e1a_Data_P1_aIneOut_Sector7;  
  TH1D* h7  = h_1e1a_Data_P1_aOuteIn_Sector7;  
  TH1D* h8  = h_1e1a_Data_P1_aIneIn_Sector7;   
  TH1D* h9  = h_1e1a_Data_P1_aOuteOut_Sector8; 
  TH1D* h10 = h_1e1a_Data_P1_aIneOut_Sector8;  
  TH1D* h11 = h_1e1a_Data_P1_aOuteIn_Sector8;  
  TH1D* h12 = h_1e1a_Data_P1_aIneIn_Sector8;   
  TH1D* h13 = h_1e1a_Data_P2_aOuteOut_Sector6;
  TH1D* h14 = h_1e1a_Data_P2_aIneOut_Sector6;  
  TH1D* h15 = h_1e1a_Data_P2_aOuteIn_Sector6;  
  TH1D* h16 = h_1e1a_Data_P2_aIneIn_Sector6;  
  TH1D* h17 = h_1e1a_Data_P2_aOuteOut_Sector7; 
  TH1D* h18 = h_1e1a_Data_P2_aIneOut_Sector7;  
  TH1D* h19 = h_1e1a_Data_P2_aOuteIn_Sector7;  
  TH1D* h20 = h_1e1a_Data_P2_aIneIn_Sector7;   
  TH1D* h21 = h_1e1a_Data_P2_aOuteOut_Sector8; 
  TH1D* h22 = h_1e1a_Data_P2_aIneOut_Sector8;  
  TH1D* h23 = h_1e1a_Data_P2_aOuteIn_Sector8;  
  TH1D* h24 = h_1e1a_Data_P2_aIneIn_Sector8;  

  TH1D* h25 = h_1e2g_Data_SeOld;  
  TH1D* h26 = h_1e2g_Data_SeNew;  

  TH1D* h27 = h_1e1g_Data_P1_SeOld;
  TH1D* h28 = h_1e1g_Data_P1_SeNew;
  TH1D* h29 = h_1e1g_Data_P1_Strip;
  TH1D* h30 = h_1e1g_Data_P2_SeOld;
  TH1D* h31 = h_1e1g_Data_P2_SeNew;
  TH1D* h32 = h_1e1g_Data_P2_Strip;

  TH1D* h33 = h_1e_Data_P1_SeOld;
  TH1D* h34 = h_1e_Data_P1_SeNew;
  TH1D* h35 = h_1e_Data_P1_Strip;
  TH1D* h36 = h_1e_Data_P2_SeOld;
  TH1D* h37 = h_1e_Data_P2_SeNew;
  TH1D* h38 = h_1e_Data_P2_Strip;

  TH1D* h39 = h_OCE_Data_P1_Inner;
  TH1D* h40 = h_OCE_Data_P1_Outer;
  TH1D* h41 = h_OCE_Data_P1_Petal;
  TH1D* h42 = h_OCE_Data_P2_Inner;
  TH1D* h43 = h_OCE_Data_P2_Outer;
  TH1D* h44 = h_OCE_Data_P2_Petal;

  TH1D* h45 = h_ExtEG_Data_P1_Inner;
  TH1D* h46 = h_ExtEG_Data_P1_Outer;
  TH1D* h47 = h_ExtEG_Data_P1_Petal;
  TH1D* h48 = h_ExtEG_Data_P2_Inner;
  TH1D* h49 = h_ExtEG_Data_P2_Outer;
  TH1D* h50 = h_ExtEG_Data_P2_Petal;

  TH1D* h51 = h_2b2n_Data_SeOld;
  TH1D* h52 = h_2b2n_Data_SeNew;

  int nBins_1e1a = h1->GetNbinsX(); 
  int nBins_1e2g = h25->GetNbinsX(); 
  int nBins_1e1g = h27->GetNbinsX(); 
  int nBins_1e   = h33->GetNbinsX(); 
  int nBins_OCE  = h39->GetNbinsX(); 
  int nBins_ExtEG= h45->GetNbinsX(); 
  int nBins_2b2n = h51->GetNbinsX(); 

  double LogL = 0; 

  // 1e1a

  for (int i = 1; i <= nBins_1e1a; i++) {
    double x = h1->GetXaxis()->GetBinCenter(i);
    Int_t d_i = (Int_t)h1->GetBinContent(i);
    Double_t mc_i = TotalMC_1e1a_P1_aOuteOut_Sector6(x,par);
    if(mc_i > 0 && TMath::Poisson(d_i,mc_i) > 0){ LogL += log(TMath::Poisson(d_i,mc_i));}
    else{ LogL -= 10;}
    //    cout << "h1: d_i = " << d_i << "\tmc_i = " << mc_i << "\tLogL = " << LogL << endl;
  }

  for (int i = 1; i <= nBins_1e1a; i++) {
    double x = h2->GetXaxis()->GetBinCenter(i);
    Int_t d_i = (Int_t)h2->GetBinContent(i);
    Double_t mc_i = TotalMC_1e1a_P1_aIneOut_Sector6(x,par);
    if(mc_i > 0 && TMath::Poisson(d_i,mc_i) > 0){ LogL += log(TMath::Poisson(d_i,mc_i));}
    else{ LogL -= 10;}
    //    cout << "h2: d_i = " << d_i << "\tmc_i = " << mc_i << "\tLogL = " << LogL << endl;
  }

  for (int i = 1; i <= nBins_1e1a; i++) {
    double x = h3->GetXaxis()->GetBinCenter(i);
    Int_t d_i = (Int_t)h3->GetBinContent(i);
    Double_t mc_i = TotalMC_1e1a_P1_aOuteIn_Sector6(x,par);
    if(mc_i > 0 && TMath::Poisson(d_i,mc_i) > 0){ LogL += log(TMath::Poisson(d_i,mc_i));}
    else{ LogL -= 10;}
    //    cout << "h3: d_i = " << d_i << "\tmc_i = " << mc_i << "\tLogL = " << LogL << endl;
  }

  for (int i = 1; i <= nBins_1e1a; i++) {
    double x = h4->GetXaxis()->GetBinCenter(i);
    Int_t d_i = (Int_t)h4->GetBinContent(i);
    Double_t mc_i = TotalMC_1e1a_P1_aIneIn_Sector6(x,par);
    if(mc_i > 0 && TMath::Poisson(d_i,mc_i) > 0){ LogL += log(TMath::Poisson(d_i,mc_i));}
    else{ LogL -= 10;}
    //    cout << "h4: d_i = " << d_i << "\tmc_i = " << mc_i << "\tLogL = " << LogL << endl;
  }

  for (int i = 1; i <= nBins_1e1a; i++) {
    double x = h5->GetXaxis()->GetBinCenter(i);
    Int_t d_i = (Int_t)h5->GetBinContent(i);
    Double_t mc_i = TotalMC_1e1a_P1_aOuteOut_Sector7(x,par);
    if(mc_i > 0 && TMath::Poisson(d_i,mc_i) > 0){ LogL += log(TMath::Poisson(d_i,mc_i));}
    else{ LogL -= 10;}
    //    cout << "h5: d_i = " << d_i << "\tmc_i = " << mc_i << "\tLogL = " << LogL << endl;
  }

  for (int i = 1; i <= nBins_1e1a; i++) {
    double x = h6->GetXaxis()->GetBinCenter(i);
    Int_t d_i = (Int_t)h6->GetBinContent(i);
    Double_t mc_i = TotalMC_1e1a_P1_aIneOut_Sector7(x,par);
    if(mc_i > 0 && TMath::Poisson(d_i,mc_i) > 0){ LogL += log(TMath::Poisson(d_i,mc_i));}
    else{ LogL -= 10;}
    //    cout << "h6: d_i = " << d_i << "\tmc_i = " << mc_i << "\tLogL = " << LogL << endl;
  }

  for (int i = 1; i <= nBins_1e1a; i++) {
    double x = h7->GetXaxis()->GetBinCenter(i);
    Int_t d_i = (Int_t)h7->GetBinContent(i);
    Double_t mc_i = TotalMC_1e1a_P1_aOuteIn_Sector7(x,par);
    if(mc_i > 0 && TMath::Poisson(d_i,mc_i) > 0){ LogL += log(TMath::Poisson(d_i,mc_i));}
    else{ LogL -= 10;}
    //    cout << "h7: d_i = " << d_i << "\tmc_i = " << mc_i << "\tLogL = " << LogL << endl;
  }

  for (int i = 1; i <= nBins_1e1a; i++) {
    double x = h8->GetXaxis()->GetBinCenter(i);
    Int_t d_i = (Int_t)h8->GetBinContent(i);
    Double_t mc_i = TotalMC_1e1a_P1_aIneIn_Sector7(x,par);
    if(mc_i > 0 && TMath::Poisson(d_i,mc_i) > 0){ LogL += log(TMath::Poisson(d_i,mc_i));}
    else{ LogL -= 10;}
    //    cout << "h8: d_i = " << d_i << "\tmc_i = " << mc_i << "\tLogL = " << LogL << endl;
  }

  for (int i = 1; i <= nBins_1e1a; i++) {
    double x = h9->GetXaxis()->GetBinCenter(i);
    Int_t d_i = (Int_t)h9->GetBinContent(i);
    Double_t mc_i = TotalMC_1e1a_P1_aOuteOut_Sector8(x,par);
    if(mc_i > 0 && TMath::Poisson(d_i,mc_i) > 0){ LogL += log(TMath::Poisson(d_i,mc_i));}
    else{ LogL -= 10;}
    //    cout << "h9: d_i = " << d_i << "\tmc_i = " << mc_i << "\tLogL = " << LogL << endl;
  }

  for (int i = 1; i <= nBins_1e1a; i++) {
    double x = h10->GetXaxis()->GetBinCenter(i);
    Int_t d_i = (Int_t)h10->GetBinContent(i);
    Double_t mc_i = TotalMC_1e1a_P1_aIneOut_Sector8(x,par);
    if(mc_i > 0 && TMath::Poisson(d_i,mc_i) > 0){ LogL += log(TMath::Poisson(d_i,mc_i));}
    else{ LogL -= 10;}
    //    cout << "h10: d_i = " << d_i << "\tmc_i = " << mc_i << "\tLogL = " << LogL << endl;
  }

  for (int i = 1; i <= nBins_1e1a; i++) {
    double x = h11->GetXaxis()->GetBinCenter(i);
    Int_t d_i = (Int_t)h11->GetBinContent(i);
    Double_t mc_i = TotalMC_1e1a_P1_aOuteIn_Sector8(x,par);
    if(mc_i > 0 && TMath::Poisson(d_i,mc_i) > 0){ LogL += log(TMath::Poisson(d_i,mc_i));}
    else{ LogL -= 10;}
    //    cout << "h11: d_i = " << d_i << "\tmc_i = " << mc_i << "\tLogL = " << LogL << endl;
  }

  for (int i = 1; i <= nBins_1e1a; i++) {
    double x = h12->GetXaxis()->GetBinCenter(i);
    Int_t d_i = (Int_t)h12->GetBinContent(i);
    Double_t mc_i = TotalMC_1e1a_P1_aIneIn_Sector8(x,par);
    if(mc_i > 0 && TMath::Poisson(d_i,mc_i) > 0){ LogL += log(TMath::Poisson(d_i,mc_i));}
    else{ LogL -= 10;}
    //    cout << "h12: d_i = " << d_i << "\tmc_i = " << mc_i << "\tLogL = " << LogL << endl;
  }

  for (int i = 1; i <= nBins_1e1a; i++) {
    double x = h13->GetXaxis()->GetBinCenter(i);
    Int_t d_i = (Int_t)h13->GetBinContent(i);
    Double_t mc_i = TotalMC_1e1a_P2_aOuteOut_Sector6(x,par);
    if(mc_i > 0 && TMath::Poisson(d_i,mc_i) > 0){ LogL += log(TMath::Poisson(d_i,mc_i));}
    else{ LogL -= 10;}
    //    cout << "h13: d_i = " << d_i << "\tmc_i = " << mc_i << "\tLogL = " << LogL << endl;
  }

  for (int i = 1; i <= nBins_1e1a; i++) {
    double x = h14->GetXaxis()->GetBinCenter(i);
    Int_t d_i = (Int_t)h14->GetBinContent(i);
    Double_t mc_i = TotalMC_1e1a_P2_aIneOut_Sector6(x,par);
    if(mc_i > 0 && TMath::Poisson(d_i,mc_i) > 0){ LogL += log(TMath::Poisson(d_i,mc_i));}
    else{ LogL -= 10;}
    //    cout << "h14: d_i = " << d_i << "\tmc_i = " << mc_i << "\tLogL = " << LogL << endl;
  }

  for (int i = 1; i <= nBins_1e1a; i++) {
    double x = h15->GetXaxis()->GetBinCenter(i);
    Int_t d_i = (Int_t)h15->GetBinContent(i);
    Double_t mc_i = TotalMC_1e1a_P2_aOuteIn_Sector6(x,par);
    if(mc_i > 0 && TMath::Poisson(d_i,mc_i) > 0){ LogL += log(TMath::Poisson(d_i,mc_i));}
    else{ LogL -= 10;}
    //    cout << "h15: d_i = " << d_i << "\tmc_i = " << mc_i << "\tLogL = " << LogL << endl;
  }

  for (int i = 1; i <= nBins_1e1a; i++) {
    double x = h16->GetXaxis()->GetBinCenter(i);
    Int_t d_i = (Int_t)h16->GetBinContent(i);
    Double_t mc_i = TotalMC_1e1a_P2_aIneIn_Sector6(x,par);
    if(mc_i > 0 && TMath::Poisson(d_i,mc_i) > 0){ LogL += log(TMath::Poisson(d_i,mc_i));}
    else{ LogL -= 10;}
    //    cout << "h16: d_i = " << d_i << "\tmc_i = " << mc_i << "\tLogL = " << LogL << endl;
  }

  for (int i = 1; i <= nBins_1e1a; i++) {
    double x = h17->GetXaxis()->GetBinCenter(i);
    Int_t d_i = (Int_t)h17->GetBinContent(i);
    Double_t mc_i = TotalMC_1e1a_P2_aOuteOut_Sector7(x,par);
    if(mc_i > 0 && TMath::Poisson(d_i,mc_i) > 0){ LogL += log(TMath::Poisson(d_i,mc_i));}
    else{ LogL -= 10;}
    //    cout << "h17: d_i = " << d_i << "\tmc_i = " << mc_i << "\tLogL = " << LogL << endl;
  }

  for (int i = 1; i <= nBins_1e1a; i++) {
    double x = h18->GetXaxis()->GetBinCenter(i);
    Int_t d_i = (Int_t)h18->GetBinContent(i);
    Double_t mc_i = TotalMC_1e1a_P2_aIneOut_Sector7(x,par);
    if(mc_i > 0 && TMath::Poisson(d_i,mc_i) > 0){ LogL += log(TMath::Poisson(d_i,mc_i));}
    else{ LogL -= 10;}
    //    cout << "h18: d_i = " << d_i << "\tmc_i = " << mc_i << "\tLogL = " << LogL << endl;
  }

  for (int i = 1; i <= nBins_1e1a; i++) {
    double x = h19->GetXaxis()->GetBinCenter(i);
    Int_t d_i = (Int_t)h19->GetBinContent(i);
    Double_t mc_i = TotalMC_1e1a_P2_aOuteIn_Sector7(x,par);
    if(mc_i > 0 && TMath::Poisson(d_i,mc_i) > 0){ LogL += log(TMath::Poisson(d_i,mc_i));}
    else{ LogL -= 10;}
    //    cout << "h19: d_i = " << d_i << "\tmc_i = " << mc_i << "\tLogL = " << LogL << endl;
  }

  for (int i = 1; i <= nBins_1e1a; i++) {
    double x = h20->GetXaxis()->GetBinCenter(i);
    Int_t d_i = (Int_t)h20->GetBinContent(i);
    Double_t mc_i = TotalMC_1e1a_P2_aIneIn_Sector7(x,par);
    if(mc_i > 0 && TMath::Poisson(d_i,mc_i) > 0){ LogL += log(TMath::Poisson(d_i,mc_i));}
    else{ LogL -= 10;}
    //    cout << "h20: d_i = " << d_i << "\tmc_i = " << mc_i << "\tLogL = " << LogL << endl;
  }

  for (int i = 1; i <= nBins_1e1a; i++) {
    double x = h21->GetXaxis()->GetBinCenter(i);
    Int_t d_i = (Int_t)h21->GetBinContent(i);
    Double_t mc_i = TotalMC_1e1a_P2_aOuteOut_Sector8(x,par);
    if(mc_i > 0 && TMath::Poisson(d_i,mc_i) > 0){ LogL += log(TMath::Poisson(d_i,mc_i));}
    else{ LogL -= 10;}
    //    cout << "h21: d_i = " << d_i << "\tmc_i = " << mc_i << "\tLogL = " << LogL << endl;
  }

  for (int i = 1; i <= nBins_1e1a; i++) {
    double x = h22->GetXaxis()->GetBinCenter(i);
    Int_t d_i = (Int_t)h22->GetBinContent(i);
    Double_t mc_i = TotalMC_1e1a_P2_aIneOut_Sector8(x,par);
    if(mc_i > 0 && TMath::Poisson(d_i,mc_i) > 0){ LogL += log(TMath::Poisson(d_i,mc_i));}
    else{ LogL -= 10;}
    //    cout << "h22: d_i = " << d_i << "\tmc_i = " << mc_i << "\tLogL = " << LogL << endl;
  }

  for (int i = 1; i <= nBins_1e1a; i++) {
    double x = h23->GetXaxis()->GetBinCenter(i);
    Int_t d_i = (Int_t)h23->GetBinContent(i);
    Double_t mc_i = TotalMC_1e1a_P2_aOuteIn_Sector8(x,par);
    if(mc_i > 0 && TMath::Poisson(d_i,mc_i) > 0){ LogL += log(TMath::Poisson(d_i,mc_i));}
    else{ LogL -= 10;}
    //    cout << "h23: d_i = " << d_i << "\tmc_i = " << mc_i << "\tLogL = " << LogL << endl;
  }

  for (int i = 1; i <= nBins_1e1a; i++) {
    double x = h24->GetXaxis()->GetBinCenter(i);
    Int_t d_i = (Int_t)h24->GetBinContent(i);
    Double_t mc_i = TotalMC_1e1a_P2_aIneIn_Sector8(x,par);
    if(mc_i > 0 && TMath::Poisson(d_i,mc_i) > 0){ LogL += log(TMath::Poisson(d_i,mc_i));}
    else{ LogL -= 10;}
    //    cout << "h24: d_i = " << d_i << "\tmc_i = " << mc_i << "\tLogL = " << LogL << endl;
  }

  //1e2g

  for (int i = 1; i <= nBins_1e2g; i++) {
    double x = h25->GetXaxis()->GetBinCenter(i);
    Int_t d_i = (Int_t)h25->GetBinContent(i);
    Double_t mc_i = TotalMC_1e2g_SeOld(x,par);
    if(mc_i > 0 && TMath::Poisson(d_i,mc_i) > 0){ LogL += log(TMath::Poisson(d_i,mc_i));}
    else{ LogL -= 10;}
    //    cout << "h25: d_i = " << d_i << "\tmc_i = " << mc_i << "\tLogL = " << LogL << endl;
  }

  for (int i = 1; i <= nBins_1e2g; i++) {
    double x = h26->GetXaxis()->GetBinCenter(i);
    Int_t d_i = (Int_t)h26->GetBinContent(i);
    Double_t mc_i = TotalMC_1e2g_SeNew(x,par);
    if(mc_i > 0 && TMath::Poisson(d_i,mc_i) > 0){ LogL += log(TMath::Poisson(d_i,mc_i));}
    else{ LogL -= 10;}
    //    cout << "h26: d_i = " << d_i << "\tmc_i = " << mc_i << "\tLogL = " << LogL << endl;
  }

   //1e1g 

   for (int i = 1; i <= nBins_1e1g; i++) { 
     double x = h27->GetXaxis()->GetBinCenter(i); 
     Int_t d_i = (Int_t)h27->GetBinContent(i); 
     Double_t mc_i = TotalMC_1e1g_P1_SeOld(x,par); 
     if(mc_i > 0 && TMath::Poisson(d_i,mc_i) > 0){ LogL += log(TMath::Poisson(d_i,mc_i));} 
     else{ LogL -= 10;} 
     //    cout << "h27: d_i = " << d_i << "\tmc_i = " << mc_i << "\tLogL = " << LogL << endl; 
   } 

   for (int i = 1; i <= nBins_1e1g; i++) { 
     double x = h28->GetXaxis()->GetBinCenter(i); 
     Int_t d_i = (Int_t)h28->GetBinContent(i); 
     Double_t mc_i = TotalMC_1e1g_P1_SeNew(x,par); 
     if(mc_i > 0 && TMath::Poisson(d_i,mc_i) > 0){ LogL += log(TMath::Poisson(d_i,mc_i));} 
     else{ LogL -= 10;} 
     //    cout << "h28: d_i = " << d_i << "\tmc_i = " << mc_i << "\tLogL = " << LogL << endl; 
   } 

   for (int i = 1; i <= nBins_1e1g; i++) { 
     double x = h29->GetXaxis()->GetBinCenter(i); 
     Int_t d_i = (Int_t)h29->GetBinContent(i); 
     Double_t mc_i = TotalMC_1e1g_P1_Strip(x,par); 
     if(mc_i > 0 && TMath::Poisson(d_i,mc_i) > 0){ LogL += log(TMath::Poisson(d_i,mc_i));} 
     else{ LogL -= 10;} 
     //    cout << "h29: d_i = " << d_i << "\tmc_i = " << mc_i << "\tLogL = " << LogL << endl; 
   } 

   for (int i = 1; i <= nBins_1e1g; i++) { 
     double x = h30->GetXaxis()->GetBinCenter(i); 
     Int_t d_i = (Int_t)h30->GetBinContent(i); 
     Double_t mc_i = TotalMC_1e1g_P2_SeOld(x,par); 
     if(mc_i > 0 && TMath::Poisson(d_i,mc_i) > 0){ LogL += log(TMath::Poisson(d_i,mc_i));} 
     else{ LogL -= 10;} 
     //    cout << "h30: d_i = " << d_i << "\tmc_i = " << mc_i << "\tLogL = " << LogL << endl; 
   } 

   for (int i = 1; i <= nBins_1e1g; i++) { 
     double x = h31->GetXaxis()->GetBinCenter(i); 
     Int_t d_i = (Int_t)h31->GetBinContent(i); 
     Double_t mc_i = TotalMC_1e1g_P2_SeNew(x,par); 
     if(mc_i > 0 && TMath::Poisson(d_i,mc_i) > 0){ LogL += log(TMath::Poisson(d_i,mc_i));} 
     else{ LogL -= 10;} 
     //    cout << "h31: d_i = " << d_i << "\tmc_i = " << mc_i << "\tLogL = " << LogL << endl; 
   } 

   for (int i = 1; i <= nBins_1e1g; i++) { 
     double x = h32->GetXaxis()->GetBinCenter(i); 
     Int_t d_i = (Int_t)h32->GetBinContent(i); 
     Double_t mc_i = TotalMC_1e1g_P2_Strip(x,par); 
     if(mc_i > 0 && TMath::Poisson(d_i,mc_i) > 0){ LogL += log(TMath::Poisson(d_i,mc_i));} 
     else{ LogL -= 10;} 
     //    cout << "h32: d_i = " << d_i << "\tmc_i = " << mc_i << "\tLogL = " << LogL << endl; 
   } 


   //1e 

   for (int i = 1; i <= nBins_1e; i++) { 
     double x = h33->GetXaxis()->GetBinCenter(i); 
     Int_t d_i = (Int_t)h33->GetBinContent(i); 
     Double_t mc_i = TotalMC_1e_P1_SeOld(x,par); 
     if(mc_i > 0 && TMath::Poisson(d_i,mc_i) > 0){ LogL += log(TMath::Poisson(d_i,mc_i));} 
     else{ LogL -= 10;} 
     //    cout << "h33: d_i = " << d_i << "\tmc_i = " << mc_i << "\tLogL = " << LogL << endl; 
   } 

   for (int i = 1; i <= nBins_1e; i++) { 
     double x = h34->GetXaxis()->GetBinCenter(i); 
     Int_t d_i = (Int_t)h34->GetBinContent(i); 
     Double_t mc_i = TotalMC_1e_P1_SeNew(x,par); 
     if(mc_i > 0 && TMath::Poisson(d_i,mc_i) > 0){ LogL += log(TMath::Poisson(d_i,mc_i));} 
     else{ LogL -= 10;} 
     //    cout << "h34: d_i = " << d_i << "\tmc_i = " << mc_i << "\tLogL = " << LogL << endl; 
   } 

   for (int i = 1; i <= nBins_1e; i++) { 
     double x = h35->GetXaxis()->GetBinCenter(i); 
     Int_t d_i = (Int_t)h35->GetBinContent(i); 
     Double_t mc_i = TotalMC_1e_P1_Strip(x,par); 
     if(mc_i > 0 && TMath::Poisson(d_i,mc_i) > 0){ LogL += log(TMath::Poisson(d_i,mc_i));} 
     else{ LogL -= 10;} 
     //    cout << "h35: d_i = " << d_i << "\tmc_i = " << mc_i << "\tLogL = " << LogL << endl; 
   } 

   for (int i = 1; i <= nBins_1e; i++) { 
     double x = h36->GetXaxis()->GetBinCenter(i); 
     Int_t d_i = (Int_t)h36->GetBinContent(i); 
     Double_t mc_i = TotalMC_1e_P2_SeOld(x,par); 
     if(mc_i > 0 && TMath::Poisson(d_i,mc_i) > 0){ LogL += log(TMath::Poisson(d_i,mc_i));} 
     else{ LogL -= 10;} 
     //    cout << "h36: d_i = " << d_i << "\tmc_i = " << mc_i << "\tLogL = " << LogL << endl; 
   } 

   for (int i = 1; i <= nBins_1e; i++) { 
     double x = h37->GetXaxis()->GetBinCenter(i); 
     Int_t d_i = (Int_t)h37->GetBinContent(i); 
     Double_t mc_i = TotalMC_1e_P2_SeNew(x,par); 
     if(mc_i > 0 && TMath::Poisson(d_i,mc_i) > 0){ LogL += log(TMath::Poisson(d_i,mc_i));} 
     else{ LogL -= 10;} 
     //    cout << "h37: d_i = " << d_i << "\tmc_i = " << mc_i << "\tLogL = " << LogL << endl; 
   } 

   for (int i = 1; i <= nBins_1e; i++) { 
     double x = h38->GetXaxis()->GetBinCenter(i); 
     Int_t d_i = (Int_t)h38->GetBinContent(i); 
     Double_t mc_i = TotalMC_1e_P2_Strip(x,par); 
     if(mc_i > 0 && TMath::Poisson(d_i,mc_i) > 0){ LogL += log(TMath::Poisson(d_i,mc_i));} 
     else{ LogL -= 10;} 
     //    cout << "h38: d_i = " << d_i << "\tmc_i = " << mc_i << "\tLogL = " << LogL << endl; 
   } 

   //OCE 

   for (int i = 1; i <= nBins_OCE; i++) { 
     double x = h39->GetXaxis()->GetBinCenter(i); 
     Int_t d_i = (Int_t)h39->GetBinContent(i); 
     Double_t mc_i = TotalMC_OCE_P1_Inner(x,par); 
     if(mc_i > 0 && TMath::Poisson(d_i,mc_i) > 0){ LogL += log(TMath::Poisson(d_i,mc_i));} 
     else{ LogL -= 10;} 
     //    cout << "h39: d_i = " << d_i << "\tmc_i = " << mc_i << "\tLogL = " << LogL << endl; 
   } 

   for (int i = 1; i <= nBins_OCE; i++) { 
     double x = h40->GetXaxis()->GetBinCenter(i); 
     Int_t d_i = (Int_t)h40->GetBinContent(i); 
     Double_t mc_i = TotalMC_OCE_P1_Outer(x,par); 
     if(mc_i > 0 && TMath::Poisson(d_i,mc_i) > 0){ LogL += log(TMath::Poisson(d_i,mc_i));} 
     else{ LogL -= 10;} 
     //    cout << "h40: d_i = " << d_i << "\tmc_i = " << mc_i << "\tLogL = " << LogL << endl; 
   } 

   for (int i = 1; i <= nBins_OCE; i++) { 
     double x = h41->GetXaxis()->GetBinCenter(i); 
     Int_t d_i = (Int_t)h41->GetBinContent(i); 
     Double_t mc_i = TotalMC_OCE_P1_Petal(x,par); 
     if(mc_i > 0 && TMath::Poisson(d_i,mc_i) > 0){ LogL += log(TMath::Poisson(d_i,mc_i));} 
     else{ LogL -= 10;} 
     //    cout << "h41: d_i = " << d_i << "\tmc_i = " << mc_i << "\tLogL = " << LogL << endl; 
   } 

   for (int i = 1; i <= nBins_OCE; i++) { 
     double x = h42->GetXaxis()->GetBinCenter(i); 
     Int_t d_i = (Int_t)h42->GetBinContent(i); 
     Double_t mc_i = TotalMC_OCE_P2_Inner(x,par); 
     if(mc_i > 0 && TMath::Poisson(d_i,mc_i) > 0){ LogL += log(TMath::Poisson(d_i,mc_i));} 
     else{ LogL -= 10;} 
     //    cout << "h42: d_i = " << d_i << "\tmc_i = " << mc_i << "\tLogL = " << LogL << endl; 
   } 

   for (int i = 1; i <= nBins_OCE; i++) { 
     double x = h43->GetXaxis()->GetBinCenter(i); 
     Int_t d_i = (Int_t)h43->GetBinContent(i); 
     Double_t mc_i = TotalMC_OCE_P2_Outer(x,par); 
     if(mc_i > 0 && TMath::Poisson(d_i,mc_i) > 0){ LogL += log(TMath::Poisson(d_i,mc_i));} 
     else{ LogL -= 10;} 
     //    cout << "h43: d_i = " << d_i << "\tmc_i = " << mc_i << "\tLogL = " << LogL << endl; 
   } 

   for (int i = 1; i <= nBins_OCE; i++) { 
     double x = h44->GetXaxis()->GetBinCenter(i); 
     Int_t d_i = (Int_t)h44->GetBinContent(i); 
     Double_t mc_i = TotalMC_OCE_P2_Petal(x,par); 
     if(mc_i > 0 && TMath::Poisson(d_i,mc_i) > 0){ LogL += log(TMath::Poisson(d_i,mc_i));} 
     else{ LogL -= 10;} 
     //    cout << "h44: d_i = " << d_i << "\tmc_i = " << mc_i << "\tLogL = " << LogL << endl; 
   } 

   //ExtEG 

   for (int i = 1; i <= nBins_ExtEG; i++) { 
     double x = h45->GetXaxis()->GetBinCenter(i); 
     Int_t d_i = (Int_t)h45->GetBinContent(i); 
     Double_t mc_i = TotalMC_ExtEG_P1_Inner(x,par); 
     if(mc_i > 0 && TMath::Poisson(d_i,mc_i) > 0){ LogL += log(TMath::Poisson(d_i,mc_i));} 
     else{ LogL -= 10;} 
     //    cout << "h45: d_i = " << d_i << "\tmc_i = " << mc_i << "\tLogL = " << LogL << endl; 
   } 

   for (int i = 1; i <= nBins_ExtEG; i++) { 
     double x = h46->GetXaxis()->GetBinCenter(i); 
     Int_t d_i = (Int_t)h46->GetBinContent(i); 
     Double_t mc_i = TotalMC_ExtEG_P1_Outer(x,par); 
     if(mc_i > 0 && TMath::Poisson(d_i,mc_i) > 0){ LogL += log(TMath::Poisson(d_i,mc_i));} 
     else{ LogL -= 10;} 
     //    cout << "h46: d_i = " << d_i << "\tmc_i = " << mc_i << "\tLogL = " << LogL << endl; 
   } 

   for (int i = 1; i <= nBins_ExtEG; i++) { 
     double x = h47->GetXaxis()->GetBinCenter(i); 
     Int_t d_i = (Int_t)h47->GetBinContent(i); 
     Double_t mc_i = TotalMC_ExtEG_P1_Petal(x,par); 
     if(mc_i > 0 && TMath::Poisson(d_i,mc_i) > 0){ LogL += log(TMath::Poisson(d_i,mc_i));} 
     else{ LogL -= 10;} 
     //    cout << "h47: d_i = " << d_i << "\tmc_i = " << mc_i << "\tLogL = " << LogL << endl; 
   } 

   for (int i = 1; i <= nBins_ExtEG; i++) { 
     double x = h48->GetXaxis()->GetBinCenter(i); 
     Int_t d_i = (Int_t)h48->GetBinContent(i); 
     Double_t mc_i = TotalMC_ExtEG_P2_Inner(x,par); 
     if(mc_i > 0 && TMath::Poisson(d_i,mc_i) > 0){ LogL += log(TMath::Poisson(d_i,mc_i));} 
     else{ LogL -= 10;} 
     //    cout << "h48: d_i = " << d_i << "\tmc_i = " << mc_i << "\tLogL = " << LogL << endl; 
   } 

   for (int i = 1; i <= nBins_ExtEG; i++) { 
     double x = h49->GetXaxis()->GetBinCenter(i); 
     Int_t d_i = (Int_t)h49->GetBinContent(i); 
     Double_t mc_i = TotalMC_ExtEG_P2_Outer(x,par); 
     if(mc_i > 0 && TMath::Poisson(d_i,mc_i) > 0){ LogL += log(TMath::Poisson(d_i,mc_i));} 
     else{ LogL -= 10;} 
     //    cout << "h49: d_i = " << d_i << "\tmc_i = " << mc_i << "\tLogL = " << LogL << endl; 
   } 

   for (int i = 1; i <= nBins_ExtEG; i++) { 
     double x = h50->GetXaxis()->GetBinCenter(i); 
     Int_t d_i = (Int_t)h50->GetBinContent(i); 
     Double_t mc_i = TotalMC_ExtEG_P2_Petal(x,par); 
     if(mc_i > 0 && TMath::Poisson(d_i,mc_i) > 0){ LogL += log(TMath::Poisson(d_i,mc_i));} 
     else{ LogL -= 10;} 
     //    cout << "h50: d_i = " << d_i << "\tmc_i = " << mc_i << "\tLogL = " << LogL << endl; 
   } 

  // 2b2n
  for (int i = 1; i <= nBins_2b2n; i++) {
    double x = h51->GetXaxis()->GetBinCenter(i);
    Int_t d_i = (Int_t)h51->GetBinContent(i);
    Double_t mc_i = TotalMC_2b2n_SeOld(x,par);
    if(mc_i > 0 && TMath::Poisson(d_i,mc_i) > 0){ LogL += log(TMath::Poisson(d_i,mc_i));}
    else{ LogL -= 10;}
    //    cout << "h51: d_i = " << d_i << "\tmc_i = " << mc_i << "\tLogL = " << LogL << endl;
  }

  for (int i = 1; i <= nBins_2b2n; i++) {
    double x = h52->GetXaxis()->GetBinCenter(i);
    Int_t d_i = (Int_t)h52->GetBinContent(i);
    Double_t mc_i = TotalMC_2b2n_SeNew(x,par);
    if(mc_i > 0 && TMath::Poisson(d_i,mc_i) > 0){ LogL += log(TMath::Poisson(d_i,mc_i));}
    else{ LogL -= 10;}
    //    cout << "h52: d_i = " << d_i << "\tmc_i = " << mc_i << "\tLogL = " << LogL << endl;
  }


  // Add terms to constrain

  // SWire Tl208 from Vera
  LogL += log(TMath::Gaus(par[7],1,0.114,true));
  LogL += log(TMath::Gaus(par[8],1,0.138,true));

  // Fix SWire Bi210 from Vera or can't converge
  LogL += log(TMath::Gaus(par[30],1,0.001,true));

  // Encourage ScintPet K40 and FeShield Bi214 to be non-zero
  LogL += log(TMath::Gaus(par[15],1,0.15,true));
  LogL += log(TMath::Gaus(par[18],1,0.15,true));

  fval = -2*LogL;

}

