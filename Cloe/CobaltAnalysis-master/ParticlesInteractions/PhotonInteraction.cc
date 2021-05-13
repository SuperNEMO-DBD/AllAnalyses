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

void PhotonInteraction(){

  // HV applied during run (official text file converted in a root readable version with 'ReadFile.py')
  TTree *tree = new TTree("data","data") ;

  tree->ReadFile("PhotonInteraction.txt","energy/F:c_scat/F:i_scat/F:photo/F:nucl_pair/F:elec_pair/F:tot_w_c_scat/F:tot_wo_c_scat/F") ;

  Float_t energy,c_scat,i_scat,photo,nucl_pair,elec_pair,tot_w_c_scat,tot_wo_c_scat ;
  tree->SetBranchAddress("energy",&energy) ;
  tree->SetBranchAddress("c_scat",&c_scat) ;
  tree->SetBranchAddress("i_scat",&i_scat) ;
  tree->SetBranchAddress("photo",&photo) ;
  tree->SetBranchAddress("nucl_pair",&nucl_pair) ;
  tree->SetBranchAddress("elec_pair",&elec_pair) ;
  tree->SetBranchAddress("tot_w_c_scat",&tot_w_c_scat) ;
  tree->SetBranchAddress("tot_wo_c_scat",&tot_wo_c_scat) ;

  vector <Float_t> v_energy,v_c_scat,v_i_scat,v_photo,v_nucl_pair,v_elec_pair,v_tot_w_c_scat,v_tot_wo_c_scat ;

  for (unsigned int i_pulse = 0 ; i_pulse < tree->GetEntries() ; i_pulse++){
    tree->GetEntry(i_pulse) ;

    v_energy.push_back(energy) ;
    v_c_scat.push_back(c_scat) ;
    v_photo.push_back(photo) ;
    v_i_scat.push_back(i_scat) ;
    v_nucl_pair.push_back(nucl_pair) ;
    v_elec_pair.push_back(elec_pair) ;
    v_tot_w_c_scat.push_back(tot_w_c_scat) ;
    v_tot_wo_c_scat.push_back(tot_wo_c_scat) ;
  }

  int size = v_energy.size() ;

  // for (int i = 0; i < v_energy.size(); ++i) {
  //   cout << v_energy.at(i) << endl ;
  // }

  TGraph *g_c_scat = new TGraph(size, &v_energy[0],&v_c_scat[0]) ;
  TGraph *g_i_scat = new TGraph(size, &v_energy[0],&v_i_scat[0]) ;
  TGraph *g_photo = new TGraph(size, &v_energy[0],&v_photo[0]) ;
  TGraph *g_nucl_pair = new TGraph(size, &v_energy[0],&v_nucl_pair[0]) ;
  TGraph *g_elec_pair = new TGraph(size, &v_energy[0],&v_elec_pair[0]) ;
  TGraph *g_w_c_scat = new TGraph(size, &v_energy[0],&v_tot_w_c_scat[0]) ;
  TGraph *g_wo_c_scat = new TGraph(size, &v_energy[0],&v_tot_wo_c_scat[0]) ;

  // void config_graph(TGraph *graph, const char *graphTitle, const char * XaxisTitle, const char *YaxisTitle,const char * draw_type,double markersize=0,int markerstyle=0,Color_t markercolor=0)
  TCanvas *c1 = new TCanvas("c1","c1") ;
  config_canvas(c1) ;

  TMultiGraph *mg = new TMultiGraph();

  c1->SetLogy() ;  c1->SetLogx() ;
  mg->Add(g_w_c_scat);g_w_c_scat->SetLineColor(MultiPlotColors(5)) ;g_w_c_scat->SetLineStyle(1) ;g_w_c_scat->SetLineWidth(3) ;
  mg->Add(g_c_scat);g_c_scat->SetLineColor(MultiPlotColors(0)) ;g_c_scat->SetLineStyle(2) ;g_c_scat->SetLineWidth(3) ;
  mg->Add(g_i_scat);g_i_scat->SetLineColor(MultiPlotColors(1)) ;g_i_scat->SetLineStyle(7) ;g_i_scat->SetLineWidth(3) ;
  mg->Add(g_photo);g_photo->SetLineColor(MultiPlotColors(2)) ;g_photo->SetLineStyle(9) ;g_photo->SetLineWidth(3) ;
  // mg->Add(g_nucl_pair,"CSAME");g_nucl_pair->SetLineColor(MultiPlotColors(3)) ; g_nucl_pair->SetLineStyle(2) ;g_nucl_pair->SetLineWidth(3) ;
  // mg->Add(g_elec_pair,"CSAME");->SetLineColor(MultiPlotColors(0))
  // mg->Add(g_wo_c_scat,"CSAME");->SetLineColor(MultiPlotColors(0))
  mg->Draw("a");
  mg->GetXaxis()->SetTitle("Photon energy (MeV)") ;
  mg->GetYaxis()->SetTitle("Radiation length (cm^{2}/g)") ;
  mg->GetXaxis()->SetTitleSize(0.06);
  mg->GetYaxis()->SetTitleSize(0.06);
  mg->GetXaxis()->SetLabelSize(0.06);
  mg->GetYaxis()->SetLabelSize(0.06);
  mg->GetXaxis()->SetLabelOffset(-0.01);
  mg->GetXaxis()->SetTitleOffset(1.3);
  mg->GetYaxis()->SetTitleOffset(1.3);
  mg->GetYaxis()->SetRangeUser(10e-9,30) ;


  auto legend = new TLegend(0.19,0.19,0.58,0.48);
  legend->AddEntry(g_w_c_scat,"Total","l");
  legend->AddEntry(g_c_scat,"Coherent scattering","l");
  legend->AddEntry(g_i_scat,"Compton effect","l");
  legend->AddEntry(g_photo,"Photoelectric effect","l");
  // legend->AddEntry(g_nucl_pair,"Nuclear pair creation","l");
  legend->Draw();

  c1->SaveAs("plots_data/PhotonInteraction.pdf") ;
}
