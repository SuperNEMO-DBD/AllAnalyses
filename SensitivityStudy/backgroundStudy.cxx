#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TROOT.h"
#include "TCanvas.h"
#include "TInterpreter.h"
#include "TLine.h"
#include "TText.h"
#include "TMath.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TColor.h"
#include <iostream>
#include <vector>

using namespace std;
//string defaultfilename="/Users/cpatrick/uclnemo2/simulation/backgrounds/bi214_foils/run_1/Bi214_foil_1M_flrec_1.root";
//string tlfilename="/Users/cpatrick/uclnemo2/simulation/backgrounds/tl208_foils/run_1/Tl208_1M_flrec_1.root";

//string defaultfilename="/Users/cpatrick/uclnemo2/simulation/backgrounds/bi214_foils/bi214_foils_10M_rec.root";
//string tlfilename="/Users/cpatrick/uclnemo2/simulation/backgrounds/tl208_foils/tl208_foils_10M_rec.root";
string tlfilename="/Users/cpatrick/SuperNEMO/rootfiles/rootfiles_backgrounds/simulated/tl208_foils_10M_rec.root";
string defaultfilename="/Users/cpatrick/SuperNEMO/rootfiles/rootfiles_backgrounds/simulated/bi214_foils_10M_rec.root";

void
set_plot_style()
{
  const Int_t NRGBs = 5;
  const Int_t NCont = 255;
  
  
  Double_t stops[9] = { 0.0000, 0.1250, 0.2500, 0.3750, 0.5000, 0.6250, 0.7500, 0.8750, 1.0000};
  Double_t red[9]   = { 145./255., 166./255., 167./255., 156./255., 131./255., 114./255., 101./255., 112./255., 132./255.};
  Double_t green[9] = { 158./255., 178./255., 179./255., 181./255., 163./255., 154./255., 144./255., 152./255., 159./255.};
  Double_t blue[9]  = { 190./255., 199./255., 201./255., 192./255., 176./255., 169./255., 160./255., 166./255., 190./255.};
/*  Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
  Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
  Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
  Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };*/
  TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
  gStyle->SetNumberContours(NCont);
}

void FormatProjections(TH3D *plot3d,string headertext,string legendtext,string xtitle,  string ytitle, string filename)
{

  gStyle->SetOptStat(0);
  int colors[10]={kRed,kBlue,kGreen+2,kViolet-5,kOrange-3,kCyan-3,kOrange+3,kGray+1,kMagenta+3,kPink-9};
  TCanvas *c=new TCanvas("snemo","snemo",900,600);
  for (int electronbin=2;electronbin<=plot3d->GetNbinsZ();electronbin++)
  {
    TLegend *leg = new TLegend(0.55,0.7,0.88,0.85);
    leg->SetBorderSize(0);
    TH1D *firstplot=plot3d->ProjectionX("plot_1",1,1,electronbin,electronbin);
    firstplot->SetLineColor(colors[0]);
    firstplot->GetXaxis()->SetTitle(xtitle.c_str());
    firstplot->GetYaxis()->SetTitle(ytitle.c_str());
    firstplot->SetTitle(Form("%d %s",electronbin-1,headertext.c_str()));
    firstplot->Draw("HIST");
    leg->AddEntry(firstplot,("0 "+legendtext).c_str());

    double maxval=firstplot->GetBinContent(firstplot->GetMaximumBin());
    for (int i=2;i<=plot3d->GetNbinsY();i++)
    {
      TH1D *plot=plot3d->ProjectionX(Form("plot_%d",i),i,i,electronbin,electronbin);
      plot->SetLineColor(colors[i-1]);
      plot->Draw("HIST SAME");
      double thismax=plot->GetBinContent(plot->GetMaximumBin());
      if (thismax>maxval)
      {
          maxval=thismax;
      }
      string legtext=Form("%d ",i-1)+legendtext;
      leg->AddEntry(plot,legtext.c_str());
    }
    leg->Draw();
    firstplot->SetMaximum(maxval*1.1);
    c->Update();
    c->SaveAs(("background_study_plots/"+filename+Form("_%d.png",electronbin-1)).c_str());//bin 1 is 0 electrons
    c->SetLogy();
    c->SaveAs(("background_study_plots/"+filename+Form("_%d_log.png",electronbin-1)).c_str());//bin 1 is 0 electrons
    c->SetLogy(false);
  }
}

void FormatProjections(TH2D *plot2d,string legendtext,string xtitle,  string ytitle, string filename)
{
  
  gStyle->SetOptStat(0);
  int colors[10]={kRed,kBlue,kGreen+2,kViolet-5,kOrange-3,kCyan-3,kOrange+3,kGray+1,kMagenta+3,kPink-9};
  TCanvas *c=new TCanvas("snemo","snemo",900,600);
  TLegend *leg = new TLegend(0.55,0.7,0.88,0.85);
  leg->SetBorderSize(0);

  for (int i=1;i<=plot2d->GetNbinsY();i++)
  {
    TH1D *plot=plot2d->ProjectionX(Form("plot_%d",i),i,i);
    plot->SetLineColor(colors[i-1]);
    if (i==1)
    {
      plot->SetMaximum(plot2d->GetMaximum()*1.1);
      plot->GetXaxis()->SetTitle(xtitle.c_str());
      plot->GetYaxis()->SetTitle(ytitle.c_str());
      plot->Draw("HIST");
    }
    else{
      plot->Draw("HIST SAME");
    }
    string legtext=Form("%d ",i-1)+legendtext;
    leg->AddEntry(plot,legtext.c_str());
  }
  leg->Draw();
  c->SaveAs(("background_study_plots/"+filename+".png").c_str());
}

void FormatSingle(TH1D *plot, string xtitle, string ytitle, string filename)
{
  gStyle->SetOptStat(0);
  TCanvas *c=new TCanvas("snemo","snemo",900,600);
  plot->GetXaxis()->SetTitle(xtitle.c_str());
  plot->GetYaxis()->SetTitle(ytitle.c_str());
  plot->Draw("HIST");
  c->SaveAs(("background_study_plots/"+filename+".png").c_str());
}

void FormatPlots(string prefix)
{
  string filename="background_study_plots/"+prefix+"_plots.root";
  TFile *file=new TFile(filename.c_str());
  TH2D *electrons_gammas=(TH2D*)file->Get("electrons_vs_gammas");
  TH3D *electron_energies= (TH3D*)file->Get("electron_energy_v_gammas");
  TH2D *electron_energies2d=(TH2D*)file->Get("electron_energy_v_gammas2d");
  TH1D *electron_energy_detailed=(TH1D*)file->Get("electron_energy_detailed");
  TH1D *gamma_energy_detailed=(TH1D*)file->Get("gamma_energy_detailed");
  
  TCanvas *c=new TCanvas("snemo","snemo",900,600);
  electrons_gammas->GetXaxis()->SetTitle("Number of electrons");
  electrons_gammas->GetYaxis()->SetTitle("Number of gammas");
  set_plot_style();
  electrons_gammas->Draw("COLZ text");
  c->SaveAs(("background_study_plots/"+prefix+"_electrons_v_gammas.png").c_str());
  
  FormatProjections(electron_energies2d,"#gamma", "Electron energy spectrum (MeV)", "Events", prefix+"_electron_energies_v_gammas");
  FormatProjections(electron_energies ,"e^{-}","#gamma", "Electron energy spectrum (MeV)", "Events", prefix+"_electron_energies_v_gammas");
  FormatSingle(electron_energy_detailed,"Electron energy spectrum (MeV)", "Events",prefix+"_electron_energy_detailed");
  FormatSingle(gamma_energy_detailed,"Photon energy spectrum (MeV)", "Events",prefix+"_gamma_energy_detailed");
  return;
}

int process(string prefix, string filename)
{
  gROOT->ProcessLine("#include <vector>");
  gStyle->SetOptStat(0);
  set_plot_style();
  // Open the file and extract the SimData tree which includes the SD and CD banks
  TFile *file=new TFile(filename.c_str());
  TTree *tree= (TTree*)file->Get("SimData");

  
  int e_nparticles; // Container for number of particles
  // Set up branch bindings
  tree->SetBranchAddress("trueparticle.noparticles", &e_nparticles);
  
  vector<int> *e_particletype=0; // Container for calo hit type (main,x wall,gamma veto)
  tree->SetBranchAddress("trueparticle.type", &e_particletype);
  
  vector<double> *e_time=0;
  tree->SetBranchAddress("trueparticle.time", &e_time);
  
  vector<double> *e_energy=0;
  tree->SetBranchAddress("trueparticle.kinenergy", &e_energy);
  
  
  string outfilename="background_study_plots/"+prefix+"_plots.root";
  cout<<"Histograms are in "<<outfilename<<endl;
  TFile *outfile=new TFile(outfilename.c_str(),"RECREATE");
  // How many entries in the tree
  int entries=tree->GetEntries();
  
  // Print the number of entries
  cout<<"Examining "<<entries<<" events."<<endl;
  
  TH2D *electrons_gammas= new TH2D("electrons_vs_gammas","Number of electrons and gammas",5,-.5,4.5,5,-.5,4.5);

  TH2D *electron_energies2d=new TH2D("electron_energy_v_gammas2d","Electron energy v gamma multiplicity",500,0,4,5,0,5);
  TH3D *electron_energies=new TH3D("electron_energy_v_gammas","Electron energy v gamma multiplicity",500,0,4,5,0,5,4,0,4);
  TH1D *electron_energy_detailed=new TH1D("electron_energy_detailed","Individual electron energies",3500,0,3.5);
  TH1D *gamma_energy_detailed=new TH1D("gamma_energy_detailed","Individual photon energies",3500,0,3.5);

//  for( int entry = 9000000; entry < 9999999; entry++ )
  for( int entry = 0; entry < entries; entry++ )
  {
    if (entry%10000==0)cout<<"Entry "<<entry<<endl;
    tree->GetEntry(entry); // Populate nhits variable (and any others you linked to a branch in the same way)
    int ngammas=0;
    int nelectrons=0;
    std::vector<double> electron_e;
    for (int particle = 0 ; (particle < e_nparticles); particle++) // Loop through all particles
    {
      if (e_particletype->at(particle)==1)
      {
        ngammas++;
        gamma_energy_detailed->Fill(e_energy->at(particle));
      }
      if (e_particletype->at(particle)==3)
      {
        electron_e.push_back(e_energy->at(particle));
        nelectrons++;
      }
    }
    for (int i=0;i<electron_e.size();i++)
    {
      electron_energies->Fill(electron_e.at(i),ngammas,nelectrons);
      electron_energies2d->Fill(electron_e.at(i),ngammas);
      electron_energy_detailed->Fill(electron_e.at(i));
    }
    electrons_gammas->Fill(nelectrons,ngammas);
  }


  
  outfile->cd();
  electron_energies2d->Write("",TObject::kOverwrite);
  electrons_gammas->Write("",TObject::kOverwrite);
  electron_energies->Write("",TObject::kOverwrite);
  electron_energy_detailed->Write("",TObject::kOverwrite);
  gamma_energy_detailed->Write("",TObject::kOverwrite);
  outfile->Close();
  
  return 0;
}

int main(int argc, char *argv[])
{
  string prefix="bi214";
  string filename=defaultfilename;
  if (argc>1)
    {
      string arg1=argv[1];
      if (arg1=="-h" || arg1=="--help")
      {
        cout<<"usage: "<< argv[0] <<" <tl or bi> <input root file (or leave blank for tl or bi default) OR 'format' to format plots only>"<<endl;
        return 2;
      }
      if (arg1=="tl" || arg1=="tl208")
      {
        prefix="tl208";
        filename=tlfilename;
      }
      if (argc>2)
      {
        filename =argv[2];
        prefix=arg1;
      }

  }
  if (filename !="format")
    process(prefix,filename);
  FormatPlots(prefix);
  return 0;
}
