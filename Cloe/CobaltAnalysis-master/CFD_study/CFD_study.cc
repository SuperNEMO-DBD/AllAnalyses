// Author Cloé Girard-Carillo girardcarillo@lal.in2p3.fr

#include <limits>
#include <string>
#include <iostream>
#include <map>

#include <TTree.h>
#include <TFile.h>
#include <TObject.h>
#include <TH1.h>
#include <TH2.h>

#include "/home/girardcarillo/Workdir/SNPlot/RootDisplay.h"
#include "/home/girardcarillo/Workdir/SNPlot/EventTree.h"

using namespace std ;

void CFD_study(){

  TH1F *hDelta_t = new TH1F("Delta_t","",80, -1, 1);

  vector<double> sigmasErrors ;
  vector<double> sigmas ;
  vector<double> CFDs ;

  ///Loop on all .root files
  for ( int i = 15 ; i < 90 ; i+=5 ) {

    string filename = "run177_coinc_with_19:13_19:15_CFD_" ;

    stringstream ss ;
    ss << i ;
    string str = ss.str() ;

    filename = filename+str+".root" ;
    //TFile *theInFile = TFile::Open(filename.c_str(),"READ") ;
    TFile *theInFile = new TFile (filename.c_str());

    if ( theInFile->IsOpen() ) {
      cout << "File " << filename << " opened sucessfully" << endl ;
    }

    hDelta_t = (TH1F *)theInFile->Get("Delta_t") ;

    gStyle->SetOptStat(1110);
    gStyle->SetOptFit(1111);

    hDelta_t->Draw();

    TF1 *f1 = new TF1("f1","gaus",-0.20,0.20);
    hDelta_t->Fit("f1","R");
    sigmas.push_back(f1->GetParameter(2)) ;
    sigmasErrors.push_back(f1->GetParError(2)) ;
    CFDs.push_back(i) ;
    delete f1;

    // theInFile->Close() ;
    // theInFile->Delete() ;

    // if ( !theInFile->IsOpen() ) {
    //   cout << "File " << filename << " closed sucessfully" << endl ;
    // }

  }
  for ( int i = 0; i < sigmas.size(); ++i) {
    cout << sigmas.at(i) << endl;
    cout << sigmasErrors.at(i) << endl << endl;
  }

  TGraphErrors *graph = new TGraphErrors(sigmas.size(),&CFDs[0],&sigmas[0],0,&sigmasErrors[0]) ;
  graph->SetTitle("CFD vs sigma") ;
  graph->GetXaxis()->SetTitle("CFD (%)") ;
  graph->GetYaxis()->SetTitle("#sigma (ns)") ;
  graph->Draw("ACP") ;

}
