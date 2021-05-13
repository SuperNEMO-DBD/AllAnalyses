#include <typeinfo>
#include <TH1F.h>
#include <TGraph.h>
#include <TTree.h>
#include <string>
#include <gsl/gsl_cdf.h>
#include <cmath>
#include <vector>
#include <stdlib.h>

#include "/home/girardcarillo/Workdir/SNPlot/RootDisplay.h"
#include "/home/girardcarillo/Workdir/Analyses/SensitivityStudy/EventSelection/Cuts.h"

double T_2nubb_82Se = 9.39 * pow(10,19);
double T_0nubb_82Se = 2.5 * pow(10,23);
double A_208Tl = 2*31.5; // 31.5 = conv 1s en année
double A_214Bi = 10*31.5; // spec
double A_222Rn = 0.15e-3*31.5e6;
double exposure = 17.5 ;
double mass_mol_82Se = 0.082; // kg/mol
double Na = 6.022 * pow(10,23);
double volume_tracker = 15.3 ; //m^3
double nb_ev_Rn = 9.7e7 ;


void Vertex(string vertex){

  TCanvas *c = new TCanvas("canvas1","canvas1");
  c->Range(-0.4891892,-1.046424,4.513513,6.451694);
  c->SetFillColor(0);
  c->SetBorderMode(0);
  c->SetBorderSize(2);
  c->SetTopMargin(0.06024097);
  c->SetBottomMargin(0.1395582);
  c->SetFrameBorderMode(0);
  c->SetFrameBorderMode(0);
  c->SetLogy() ;

  auto legend = new TLegend(0.811,0.573,0.990,0.974);
  legend->SetBorderSize(1) ;

  string process ;
  int color ;

  for (int i = 0; i < 5; ++i) {
    if (i==0) {
      process = "0nubb" ;
      color = kGreen+4 ;
    }
    if (i==1) {
      process = "2nubb" ;
      color = kCyan+3 ;
    }
    if (i==2) {
      process = "208Tl" ;
      color = kOrange+2 ;
    }
    if (i==3) {
      process = "214Bi" ;
      color = kYellow-3 ;
    }
    if (i==4) {
      process = "222Rn" ;
      color = kTeal+2 ;
    }


    string file_data = Form("~/Workdir/Analyses/SensitivityStudy/Vertex/root_files/Vertex_%s_%s.root",vertex.c_str(),process.c_str()) ;
    TFile *theDataFile = new TFile(file_data.c_str(),"READ") ;

    TH1F *hvertex = (TH1F*)theDataFile->Get(Form("vertex%s",vertex.c_str()));
    legend->AddEntry(hvertex,process.c_str(),"l");



    if (i==0) {
      config_histo1D(hvertex,"HIST",Form("#Delta %s (mm)",vertex.c_str()),"Arbitrary normalisation",2,1,color) ;
      hvertex->GetYaxis()->SetRangeUser(1,3e6) ;
      hvertex->SetTitle("") ;
    }
    if (i==1) {
      config_histo1D(hvertex,"HISTSAME",Form("#Delta %s (mm)",vertex.c_str()),"Arbitrary normalisation",2,1,color) ;
    }
    else {
      config_histo1D(hvertex,"HISTSAME",Form("#Delta %s (mm)",vertex.c_str()),"Arbitrary normalisation",2,1,color) ;
    }



    // if (i==0) {
    //   config_histo1D(hvertex,"HIST",Form("#Delta %s (mm)",vertex.c_str()),"Arbitrary normalisation",2,1,color) ;
    //   hvertex->Draw() ;
    //   // hvertex->Scale(0.01) ;
    //   hvertex->Scale((((Na*log(2))/mass_mol_82Se)*(exposure/T_0nubb_82Se)*(1/1e7)));
    //   hvertex->GetYaxis()->SetRangeUser(1e-2,1e4) ;
    //   hvertex->SetTitle("") ;
    // }
    // if (i==1) {
    //   config_histo1D(hvertex,"HISTSAME",Form("#Delta %s (mm)",vertex.c_str()),"Arbitrary normalisation",2,1,color) ;
    //   // hvertex->Scale(0.01) ;
    //   hvertex->Scale((((Na*log(2))/mass_mol_82Se)*(exposure/T_2nubb_82Se)*(1/1e7)));
    // }
    // if (i==2) {
    //   config_histo1D(hvertex,"HISTSAME",Form("#Delta %s (mm)",vertex.c_str()),"Arbitrary normalisation",2,1,color) ;
    //   hvertex->Scale((A_208Tl*exposure)*(1/1e7));

    // }
    // if (i==3) {
    //   config_histo1D(hvertex,"HISTSAME",Form("#Delta %s (mm)",vertex.c_str()),"Arbitrary normalisation",2,1,color) ;
    //   hvertex->Scale((A_214Bi*exposure)*(1/1e7));

    // }
    // if (i==4) {
    //   config_histo1D(hvertex,"HISTSAME",Form("#Delta %s (mm)",vertex.c_str()),"Arbitrary normalisation",2,1,color) ;
    //   hvertex->Scale((A_222Rn*volume_tracker*2.5)*(1/nb_ev_Rn));

    // }


  }

  legend->Draw() ;

  c->SaveAs(Form("plots/Vertex_%s.eps",vertex.c_str())) ;

}
