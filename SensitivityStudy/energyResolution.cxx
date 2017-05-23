#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TROOT.h"
#include "TCanvas.h"
#include "TInterpreter.h"
#include "TLine.h"
#include "TText.h"
#include "TMath.h"
#include "TLegend.h"
#include "TStyle.h"
#include <iostream>
#include <vector>

using namespace std;
string defaultfilename="/Users/cpatrick/SuperNEMO/test/201701/test_5000_0nubb.root";
//string defaultfilename="/Users/cpatrick/SuperNEMO/test/201701/test_1000_0nubb_rec.root";

void InitializePlotSet(TH2D **h_main, TH2D **h_xcalo, TH2D **h_veto, string name, string title, int nbinsx, double xlo, double xhi, int nbinsy, double ylo, double yhi)
{
  *h_main = new TH2D((name+"_main").c_str(),title.c_str(),nbinsx,xlo,xhi,nbinsy,ylo,yhi);
  (*h_main)->SetMarkerColor(kRed);
  (*h_main)->SetMarkerStyle( kFullDotSmall);
  (*h_main)->SetFillColor(kRed);
                    
  (*h_xcalo) = new TH2D((name+"_xcalo").c_str(),title.c_str(),nbinsx,xlo,xhi,nbinsy,ylo,yhi);
  (*h_xcalo)->SetMarkerColor(kBlue);
  (*h_xcalo)->SetMarkerStyle( kFullDotSmall);
  (*h_xcalo)->SetFillColor(kBlue);
  
  (*h_veto) = new TH2D((name+"_gveto").c_str(),title.c_str(),nbinsx,xlo,xhi,nbinsy,ylo,yhi);
  (*h_veto)->SetMarkerColor(kTeal+9);
  (*h_veto)->SetMarkerStyle( kFullDotSmall);
  (*h_veto)->SetFillColor(kTeal+9);

}
bool FillPlotSet(TH2D **h_main, TH2D **h_xcalo, TH2D **h_veto, int calo_type, double x, double y)
{
  switch (calo_type)
  {
    case 0:
      (*h_main)->Fill(x,y);
      return true;
    case 1:
      (*h_xcalo)->Fill(x,y);
      return true;
    case 2:
      (*h_veto)->Fill(x,y);
      return true;
    default:
      cout<<"Hit on a mystery wall"<<endl;
      return false;
  }
}

void FormatPlotSet(TH2D **h_main, TH2D **h_xcalo, TH2D **h_veto, string xtitle, string ytitle, string filename)
{
  TCanvas *c=new TCanvas("snemo","snemo",900,600);
  (*h_main)->GetXaxis()->SetTitle(xtitle.c_str());
  (*h_main)->GetYaxis()->SetTitle(ytitle.c_str());
  (*h_main)->Draw("");
  (*h_xcalo)->Draw("SAME");
  (*h_veto)->Draw("SAME");
  TLegend *leg = new TLegend(0.15,0.7,0.48,0.85);
  leg->SetBorderSize(0);
  leg->AddEntry((*h_main),"Main calo wall","f");
  leg->AddEntry((*h_xcalo),"X wall","f");
  leg->AddEntry((*h_veto),"Gamma veto","f");
  leg->Draw();
  c->SaveAs(("resolution_plots/"+filename+".png").c_str());

}

int process(string filename)
{
  gROOT->ProcessLine("#include <vector>");
  gStyle->SetOptStat(0);
  // Open the file and extract the SimData tree which includes the SD and CD banks
  TFile *file=new TFile(filename.c_str());
  TTree *tree= (TTree*)file->Get("SimData");

  
  int nhits; // Container for number of particles
  // Set up branch bindings
  tree->SetBranchAddress("calo.nohits", &nhits); // This links nhits variable to the branch it will be filled from
  
  vector<int> *calotype=0; // Container for calo hit type (main,x wall,gamma veto)
  tree->SetBranchAddress("calo.type", &calotype);
  
  vector<double> *energy=0;
  tree->SetBranchAddress("calo.energy", &energy);
  
  vector<double> *sigmaenergy=0;
  tree->SetBranchAddress("calo.sigmaenergy", &sigmaenergy);
  
  vector<double> *time=0;
  tree->SetBranchAddress("calo.time", &time);
  
  vector<double> *sigmatime=0;
  tree->SetBranchAddress("calo.sigmatime", &sigmatime);
  
  
  // How many entries in the tree
  int entries=tree->GetEntries();
  
  // Print the number of entries
  cout<<"Examining "<<entries<<" events."<<endl;
  
  TH2D* h_root_e_vs_sigma_main= new TH2D();
  TH2D* h_root_e_vs_sigma_xcalo=new TH2D();
  TH2D* h_root_e_vs_sigma_gveto=new TH2D();
  InitializePlotSet(&h_root_e_vs_sigma_main, &h_root_e_vs_sigma_xcalo, &h_root_e_vs_sigma_gveto,"h_root_e_vs_sigma", "Calorimeter resolution in MC", 1000,0,2,1000,0,0.1);

  TH2D* h_inv_root_e_vs_sigmat_main= new TH2D();
  TH2D* h_inv_root_e_vs_sigmat_xcalo=new TH2D();
  TH2D* h_inv_root_e_vs_sigmat_gveto=new TH2D();
  InitializePlotSet(&h_inv_root_e_vs_sigmat_main, &h_inv_root_e_vs_sigmat_xcalo, &h_inv_root_e_vs_sigmat_gveto,"h_inv_root_e_vs_sigmat", "Time resolution in MC", 1000,0,5,1000,0,2);
  
  
  for( int entry = 0; entry < entries; entry++ )
  {
    tree->GetEntry(entry); // Populate nhits variable (and any others you linked to a branch in the same way)

    for (int hit =0 ; (hit < nhits); hit++) // Loop through all calo hits and get energy
    {
      
      if (! FillPlotSet(&h_inv_root_e_vs_sigmat_main, &h_inv_root_e_vs_sigmat_xcalo, &h_inv_root_e_vs_sigmat_gveto, calotype->at(hit), 1.0/(TMath::Sqrt(energy->at(hit))), sigmatime->at(hit))) cout<<"Problem filling time plot for entry "<<entry<<endl;

      if (! FillPlotSet(&h_root_e_vs_sigma_main, &h_root_e_vs_sigma_xcalo, &h_root_e_vs_sigma_gveto, calotype->at(hit), TMath::Sqrt(energy->at(hit)), sigmaenergy->at(hit))) cout<<"Problem filling energy plot for entry "<<entry<<endl;
    }
  }
  
  FormatPlotSet(&h_root_e_vs_sigma_main, &h_root_e_vs_sigma_xcalo, &h_root_e_vs_sigma_gveto, "#sqrt{E (MeV)}", "#sigma E (MeV)", "h_root_e_vs_sigma");
  FormatPlotSet(&h_inv_root_e_vs_sigmat_main, &h_inv_root_e_vs_sigmat_xcalo, &h_inv_root_e_vs_sigmat_gveto, "1/#sqrt{E (MeV)}", "#sigma t (ns)", "h_inv_root_e_vs_sigmat");
  return 0;
}

int main(int argc, char *argv[])
{
  if (argc>1)
  {
    return process(argv[1]);
  }
  return process(defaultfilename);
}
