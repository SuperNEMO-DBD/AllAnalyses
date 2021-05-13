// Author Cloé Girard-Carillo girardcarillo@lal.in2p3.fr

#include <limits>
#include <string>
#include <iostream>
#include <fstream>

#include <TTree.h>
#include <TProfile.h>
#include <TFile.h>
#include <TObject.h>
#include <TH1.h>
#include <TH2.h>

#include "/home/girardcarillo/Workdir/SNPlot/RootDisplay.h"
#include "/home/girardcarillo/Workdir/SNPlot/EventTree.h"

using namespace std ;

void ElectronInteraction(){

  // HV applied during run (official text file converted in a root readable version with 'ReadFile.py')
  TTree *tree = new TTree("data","data") ;

  tree->ReadFile("ElectronInteraction.txt","energy/F:col/F:rad/F:tot/F") ;

  Float_t energy,col,rad,tot ;
  tree->SetBranchAddress("energy",&energy) ;
  tree->SetBranchAddress("col",&col) ;
  tree->SetBranchAddress("rad",&rad) ;
  tree->SetBranchAddress("tot",&tot) ;

  vector <Float_t> v_energy,v_col,v_rad,v_tot ;

  for (unsigned int i_pulse = 0 ; i_pulse < tree->GetEntries() ; i_pulse++){
    tree->GetEntry(i_pulse) ;

    v_energy.push_back(energy) ;
    v_col.push_back(col) ;
    v_rad.push_back(rad) ;
    v_tot.push_back(1/tot) ;
  }

  int size = v_energy.size() ;

  // for (int i = 0; i < v_energy.size(); ++i) {
  //   cout << v_energy.at(i) << endl ;
  // }

  TGraph *g_col = new TGraph(size, &v_energy[0],&v_col[0]) ;
  TGraph *g_rad = new TGraph(size, &v_energy[0],&v_rad[0]) ;
  TGraph *g_tot = new TGraph(size, &v_energy[0],&v_tot[0]) ;

  // void config_graph(TGraph *graph, const char *graphTitle, const char * XaxisTitle, const char *YaxisTitle,const char * draw_type,double markersize=0,int markerstyle=0,Color_t markercolor=0)
  TCanvas *c1 = new TCanvas("c1","c1") ;
  config_canvas(c1) ;

  TMultiGraph *mg = new TMultiGraph();

  c1->SetLogy() ;  c1->SetLogx() ;
  mg->Add(g_tot);g_tot->SetLineColor(MultiPlotColors(5)) ;g_tot->SetLineStyle(1) ;g_tot->SetLineWidth(3) ;
  mg->Add(g_col);g_col->SetLineColor(MultiPlotColors(0)) ;g_col->SetLineStyle(2) ;g_col->SetLineWidth(3) ;
  mg->Add(g_rad);g_rad->SetLineColor(MultiPlotColors(1)) ;g_rad->SetLineStyle(7) ;g_rad->SetLineWidth(3) ;
  mg->Draw("a");
  mg->GetXaxis()->SetTitle("Electron energy (MeV)") ;
  mg->GetYaxis()->SetTitle("Radiation length (cm^{2}/g)") ;
  mg->GetXaxis()->SetTitleSize(0.06);
  mg->GetYaxis()->SetTitleSize(0.06);
  mg->GetXaxis()->SetLabelSize(0.06);
  mg->GetYaxis()->SetLabelSize(0.06);
  mg->GetXaxis()->SetLabelOffset(-0.01);
  mg->GetXaxis()->SetTitleOffset(1.3);
  mg->GetYaxis()->SetTitleOffset(1.3);
  mg->GetYaxis()->SetRangeUser(10e-9,30) ;
  auto legend = new TLegend(0.55,0.22,0.96,0.47);
  legend->AddEntry(g_tot,"Total","l");
  legend->AddEntry(g_col,"Coherent scattering","l");
  legend->AddEntry(g_rad,"Radiative effect","l");
  legend->Draw();

  c1->SaveAs("plots_data/ElectronInteraction.pdf") ;
}
