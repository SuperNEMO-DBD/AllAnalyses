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
#include "/home/girardcarillo/Workdir/Analyses/SensitivityStudy/contaminations/contaminations.h"

using namespace std;


void Contaminations_SeNd(){

  TTree *SeWithB = new TTree("t_SeWithB","Se with B") ;
  TTree *NdWithB = new TTree("t_NdWithB","Nd with B") ;

  NdWithB->ReadFile("results_Nd_with_B.txt","NdBInf/F:NdBSup/F:NdBT12/F") ;
  SeWithB->ReadFile("results_Se_with_B.txt","SeBInf/F:SeBSup/F:SeBT12/F") ;

  float SeBInf, SeBSup, SeBT12 ;
  SeWithB->SetBranchAddress("SeBInf",&SeBInf) ;
  SeWithB->SetBranchAddress("SeBSup",&SeBSup) ;
  SeWithB->SetBranchAddress("SeBT12",&SeBT12) ;

  float NdBInf, NdBSup, NdBT12 ;
  NdWithB->SetBranchAddress("NdBInf",&NdBInf) ;
  NdWithB->SetBranchAddress("NdBSup",&NdBSup) ;
  NdWithB->SetBranchAddress("NdBT12",&NdBT12) ;

  const Int_t nx = 4;

  TH1F *hSe = new TH1F("hSe","",nx,0,2);
  TH1F *hSeBInf = new TH1F("hSeBInf","",nx,0,2);
  TH1F *hSeBSup = new TH1F("hSeBSup","",nx,0,2);
  TH1F *hNd = new TH1F("hNd","",nx,0,2);
  TH1F *hNdBInf = new TH1F("hNdBInf","",nx,0,2);
  TH1F *hNdBSup = new TH1F("hNdBSup","",nx,0,2);

  double tSeBInf[nx], tSeBSup[nx],tNdBInf[nx], tNdBSup[nx] ;
  const char *type[nx] = {"Zero act.","Specified act.","Measured act. (w/o ^{214}Bi)","Measured act. (w/ ^{214}Bi)"};

  for (int k=0; k<SeWithB->GetEntries(); k++){
    SeWithB->GetEntry(k);

    hSe->Fill(type[k],SeBT12) ;
    hSeBInf->Fill(type[k],SeBInf) ;
    hSeBSup->Fill(type[k],SeBSup) ;


    tSeBInf[k] = SeBInf ;
    tSeBSup[k] = SeBSup ;

  }

  for (int k=0; k<NdWithB->GetEntries(); k++){
    NdWithB->GetEntry(k);

    hNd->Fill(type[k],NdBT12) ;
    hNdBInf->Fill(type[k],NdBInf) ;
    hNdBSup->Fill(type[k],NdBSup) ;

    tNdBInf[k] = NdBInf ;
    tNdBSup[k] = NdBSup ;

  }


  TCanvas *c = new TCanvas("c","c",10,10,2000,1000) ;
  TGaxis::SetMaxDigits(2) ;




  // Define the Canvas
  gStyle->SetOptStat(0);
  // Upper plot will be in pad1
  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->Range(-0.25,-8.699719e+23,2.251351,1.203523e+25);
  pad1->SetFillColor(0);
  pad1->SetBorderMode(0);
  pad1->SetBorderSize(2);
  pad1->SetTopMargin(0.06626506);
  pad1->SetBottomMargin(0.06741251);
  pad1->SetFrameBorderMode(0);
  pad1->SetFrameBorderMode(0);
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->SetLogy() ;
  pad1->SetGridy() ;
  pad1->cd();               // pad1 becomes the current pad


  config_histo1D(hSe,"P","","Best limit on T_{1/2} (y)",0,1,0) ;
  config_histo1D(hNd,"Psame","","Best limit on T_{1/2} (y)",0,1,0) ;
  // hSe->GetYaxis()->SetNdivisions(610);
  hSe->SetMarkerStyle(8) ;
  hSe->SetMarkerSize(1.5) ;
  hSe->SetMarkerColor(kCyan-2) ;
  hNd->SetMarkerStyle(8) ;
  hNd->SetMarkerSize(1.5) ;
  hNd->SetMarkerColor(kOrange+2) ;
  hSe->GetXaxis()->SetLabelSize(0);
  hSe->GetYaxis()->SetRangeUser(9e23,1e25) ;

  auto legend = new TLegend(0.558,0.816,0.897,0.997);
  legend->AddEntry(hSe,"^{82}Se sources, with field 25 G","lep");
  legend->AddEntry(hNd,"^{150}Nd sources, with field 25 G","lep");
  legend->Draw();
  legend->SetBorderSize(1) ;
  c->cd();


  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.005, 1, 0.303);
  pad2->Range(-0.25,2.172143,2.251351,4.042782);
  pad2->SetTopMargin(0.02287);
  pad2->SetBottomMargin(0.1752648);
  pad2->SetGridy() ;
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad

  config_histo1D(hSeBInf,"P","","Energy (MeV)",0,1,kCyan-2) ; hSeBInf->SetMarkerColor(0) ;
  // config_histo1D(hNdBInf,"Psame","","Energy (MeV)",0,1,2) ;
  // hSeBInf->SetMarkerStyle(23) ;
  // hSeBInf->SetMarkerSize(2) ;
  // hSeBInf->SetMarkerColor(kCyan-2) ;
  // hNdBInf->SetMarkerStyle(23) ;
  // hNdBInf->SetMarkerSize(2) ;
  // hNdBInf->SetMarkerColor(kOrange+2) ;

  // config_histo1D(hSeBSup,"Psame","","Energy (MeV)",0,1,kCyan-2) ;
  // config_histo1D(hNdBSup,"Psame","","Energy (MeV)",0,1,2) ;
  // hSeBSup->SetMarkerStyle(22) ;
  // hSeBSup->SetMarkerSize(2) ;
  // hSeBSup->SetMarkerColor(kCyan-2) ;
  // hNdBSup->SetMarkerStyle(22) ;
  // hNdBSup->SetMarkerSize(2) ;
  // hNdBSup->SetMarkerColor(kOrange+2) ;
  hSeBInf->GetYaxis()->SetRangeUser(2.6,3.8) ;
  hSeBInf->GetXaxis()->SetLabelSize(0.17);
  hSeBInf->GetXaxis()->SetLabelOffset(0.03);
  hSeBInf->GetYaxis()->SetLabelSize(0.1);
  hSeBInf->GetYaxis()->SetTitleSize(0.12);
  hSeBInf->GetYaxis()->SetTitleOffset(0.42);
  hSeBInf->GetYaxis()->SetNdivisions(010);

  TLine* line0 = new TLine(0.25,tSeBInf[0],0.25,tSeBSup[0]) ;
  TLine* line1 = new TLine(0.75,tSeBInf[1],0.75,tSeBSup[1]) ;
  TLine* line2 = new TLine(1.25,tSeBInf[2],1.25,tSeBSup[2]) ;
  TLine* line2bis = new TLine(1.75,tSeBInf[3],1.75,tSeBSup[3]) ;
  line0->SetLineColor(kCyan-2) ;
  line0->SetLineWidth(2) ;
  line0->SetLineWidth(6) ;
  line1->SetLineColor(kCyan-2) ;
  line1->SetLineWidth(2) ;
  line1->SetLineWidth(6) ;
  line2->SetLineColor(kCyan-2) ;
  line2->SetLineWidth(2) ;
  line2->SetLineWidth(6) ;
  line2bis->SetLineColor(kCyan-2) ;
  line2bis->SetLineWidth(2) ;
  line2bis->SetLineWidth(6) ;
  line0->Draw("same") ;
  line1->Draw("same") ;
  line2->Draw("same") ;
  line2bis->Draw("same") ;

  TLine* line3 = new TLine(0.27,tNdBInf[0],0.27,tNdBSup[0]) ;
  TLine* line4 = new TLine(0.77,tNdBInf[1],0.77,tNdBSup[1]) ;
  TLine* line5 = new TLine(1.27,tNdBInf[2],1.27,tNdBSup[2]) ;
  TLine* line6 = new TLine(1.77,tNdBInf[3],1.77,tNdBSup[3]) ;
  line3->SetLineColor(kOrange+2) ;
  line3->SetLineWidth(2) ;
  line3->SetLineWidth(6) ;
  line4->SetLineColor(kOrange+2) ;
  line4->SetLineWidth(2) ;
  line4->SetLineWidth(6) ;
  line5->SetLineColor(kOrange+2) ;
  line5->SetLineWidth(2) ;
  line5->SetLineWidth(6) ;
  line6->SetLineColor(kOrange+2) ;
  line6->SetLineWidth(2) ;
  line6->SetLineWidth(6) ;
  line3->Draw("same") ;
  line4->Draw("same") ;
  line5->Draw("same") ;
  line6->Draw("same") ;

  c->SaveAs("plots/cont_level_isotope.pdf") ;

}
