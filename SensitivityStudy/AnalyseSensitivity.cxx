#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TROOT.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TLimit.h"
#include "TError.h"
#include "TLimitDataSource.h"
#include "TConfidenceLevel.h"
#include <iostream>

using namespace std;

double AVOGADRO=6.022140e23;
// For a complete analysis there should be a cut on the vertex separation too, at the very least. These are sensitivity module branches
string MAINCUT= "sensitivity.number_of_electrons==2 && sensitivity.passes_two_calorimeters && sensitivity.passes_associated_calorimeters && (sensitivity.higher_electron_energy != sensitivity.lower_electron_energy)";
// check these numbers are the right way round
string PROBCUT ="&& sensitivity.external_probability<0.01 && sensitivity.internal_probability>0.04";

// This class is to set up a source isotope eg Se82. This allows you to calculate sensitivities for different detector configs
class Isotope {
  int molarMass_;
  string isotopeName_;
public:
  Isotope(){};
  Isotope(string isotopeName, int molarMass); 
  void Initialize(string isotopeName, int molarMass);  
  int GetMolarMass (){return molarMass_;}
  string GetIsotopeName (){return isotopeName_;}
  string GetMolarMassText(){return Form("%d",molarMass_);}
  void SetIsotopeName(string val){isotopeName_=val;}
  void SetMolarMass (int val){molarMass_=val;}
};

Isotope::Isotope(string isotopeName, int molarMass)
{
  this->Initialize(isotopeName, molarMass);
}

void Isotope::Initialize(string isotopeName, int molarMass)
{
  this->SetIsotopeName(isotopeName);
  this->SetMolarMass(molarMass);
}

// Background isotopes could be Bi214 or Tl208 in the foil or radon in the tracker

class BackgroundIsotope : public Isotope{
  double activityMicroBq_;
  string rootFileName_;
  string isotopeLocation_;
public:
  BackgroundIsotope (string isotopeName, int molarMass,  double activityMicroBq, string rootFileName, string isotopeLocation);
  void SetActivityMicroBq  (double val) {activityMicroBq_=val;}
  double GetActivityMicroBq (){return activityMicroBq_;}
  void SetRootFileName(string val){rootFileName_=val;}
  string GetRootFileName (){return rootFileName_;}
  void SetIsotopeLocation(string val){isotopeLocation_=val;}
  string GetIsotopeLocation(){return isotopeLocation_;}
  void Initialize(string isotopeName, int molarMass, double activityMicroBq, string rootFileName, string isotopeLocation);
};

void BackgroundIsotope::Initialize(string isotopeName, int molarMass, double activityMicroBq, string rootFileName, string isotopeLocation)
{
  this->Isotope::Initialize(isotopeName, molarMass);
  this->SetActivityMicroBq(activityMicroBq);
  this->SetIsotopeLocation(isotopeLocation);
  this->SetRootFileName(rootFileName);
}
  
BackgroundIsotope::BackgroundIsotope(string isotopeName, int molarMass, double activityMicroBq, string rootFileName, string isotopeLocation)
{
  this->Initialize(isotopeName, molarMass, activityMicroBq, rootFileName, isotopeLocation);
}
  
class IsotopeSample : public Isotope{

  double backgroundHalfLife_, exposureYears_, minEnergy_,  maxEnergy_ ,fractionOfEventsIn2bbSample_, isotopeMassKg_;
  public:
  IsotopeSample(string isotopeName, int molarMass, double isotopeMassKg,double backgroundHalfLife,  double exposureYears,  double minEnergy,  double  maxEnergy, double fractionOfEventsIn2bbSample);
  IsotopeSample(){};
  IsotopeSample(string isotopeName);

  double GetBackgroundHalfLife (){return backgroundHalfLife_;}
  double GetExposureYears (){return exposureYears_;}
  double GetMinEnergy (){return minEnergy_;}
  double GetMaxEnergy (){return maxEnergy_;}
  double GetFractionOfEventsIn2bbSample (){return fractionOfEventsIn2bbSample_;}
  double GetIsotopeMassKg (){return isotopeMassKg_;}

  void SetBackgroundHalfLife (double val){backgroundHalfLife_=val;}
  void SetExposureYears (double val){exposureYears_=val;}
  void SetIsotopeMassKg  (double val){isotopeMassKg_=val;}
  void SetMinEnergy (double val){minEnergy_=val;}
  void SetMaxEnergy (double val){maxEnergy_=val;}
  void SetFractionOfEventsIn2bbSample (double val){fractionOfEventsIn2bbSample_=val;} 
  // I used this so I could make a cut on true energy in the 2nubb simulation. That allows me to use a smaller simulated file
  // that doesn't include events I would cut anyway. If you simulate like this, you can get the fraction of the total
  // spectrum that was retained from the brio file. Put that number in here. If you seimulate a full spectrum, it is 1.

  void Print();
  
  void Initialize(string isotopeName, int molarMass, double isotopeMassKg,double backgroundHalfLife,  double exposureYears,  double minEnergy,  double  maxEnergy, double fractionOfEventsIn2bbSample);
};

IsotopeSample::IsotopeSample(string isotopeName, int molarMass, double isotopeMassKg,double backgroundHalfLife,  double exposureYears,  double minEnergy,  double  maxEnergy, double fractionOfEventsIn2bbSample)
{
  this->Initialize (isotopeName, molarMass, isotopeMassKg, backgroundHalfLife, exposureYears, minEnergy, maxEnergy, fractionOfEventsIn2bbSample);
}

IsotopeSample::IsotopeSample(string isotopeName)
{
  if (isotopeName=="Se" || isotopeName=="se" || isotopeName=="SE")
    {
//      this->Initialize("Se",82,7.,10.07e19,2.5,2,3.2,4.39912675943585491e-02);
      // This is hardcoding some standard number for an Se82 sample
    // Element Se
    // Atomic mass 82
    // 2nubb Halflife 10.07e19 years - this is probably out of date
    // 2.5 years run time
    //2 - 3.2 MeV range to look at
    // We retained 0.04... fraction of the full spectrum in our 2MeV+ sample
      this->Initialize("Se",82,7.,10.07e19,2.5,2,3.2,0.0440500); // get fraction with true total energy over 2MeV
    }
  else if  (isotopeName=="Ca" || isotopeName=="ca" || isotopeName=="CA")
    { // Defaults for a Ca48 sample with a true energy cut on the 2nubb halflife
      this->Initialize("Ca",48,7.,4.3e19,2.5,3.2,4.4,9.41579993091566821e-03);
    }
  else if (isotopeName=="nd"|| isotopeName=="Nd" || isotopeName=="ND")
    {// Defaults for a Nd150 sample  with a true energy cut on the 2nubb halflife
      this->Initialize("Nd",150,7.,9.1e18,2.5,2.2,3.5,3.17395699176686516e-02);
    }
  else
    {
      cout<<"ERROR: Sample "<<isotopeName<<" not configured, please initialize"<<endl;
    }
}

void IsotopeSample::Print()
{
  cout<<"Isotope: "<<this->GetIsotopeName()<<"-"<<this->GetMolarMass()<<endl;
  cout<<"Mass: "<<this->GetIsotopeMassKg()<<" kg"<<endl; 
  cout<<"Exposure: "<<exposureYears_<<" years"<<endl;
  cout<<"2nubb halflife: "<<backgroundHalfLife_<<" years"<<endl;
  cout<<"Energy range "<<minEnergy_<<" - "<<maxEnergy_<<" MeV contains "<<fractionOfEventsIn2bbSample_<<" of total events"<<endl;
}
void IsotopeSample::Initialize (string isotopeName, int molarMass, double isotopeMassKg,double backgroundHalfLife,  double exposureYears,  double minEnergy,  double  maxEnergy, double fractionOfEventsIn2bbSample) {
  this->SetIsotopeName(isotopeName);
  this->SetMolarMass(molarMass);
  this->SetIsotopeMassKg(isotopeMassKg);
  backgroundHalfLife_=backgroundHalfLife;
  exposureYears_= exposureYears;
  minEnergy_=minEnergy;
  maxEnergy_=maxEnergy;
  fractionOfEventsIn2bbSample_=fractionOfEventsIn2bbSample;
  cout<<"Sample initialized: "<<endl;
  this->Print();
}

int CalculateEfficiencies(TTree *tree,  IsotopeSample *sample, bool is2nubb=false, int allEntries=0);
TH1D* PlotEfficiency(TTree *tree, double totalEntries, string additionalCut, double minEnergy, double maxEnergy);
double EstimateHalflifeSensitivity  (double signalEfficiency, double backgroundEfficiency, IsotopeSample *sample);
double EstimateBackgroundEvents(double backgroundEfficiency, IsotopeSample *sample);
void MakePlotsForIsotope(string filename0nubb, string filename2nubb, IsotopeSample *sample);
void MakePlotsForExtraCut(TTree *tree0nubb, double totalEntries0nubb, TTree *tree2nubb, double totalEntries2nubb, string extraCut, string cutTitle, string cutFilenameSuffix, IsotopeSample *sample);
double ExpectedLimitSigEvts(double ConfidenceLevel, TH1D* h_signal, TH1D* h_background, TH1D* h_data);
TH1D* EstimateSensitivity(TH1D *energy_0nubb, TH1D *energy_2nubb, IsotopeSample *sample, TH1D* efficiency_0nubb, TH1D* efficiency_2nubb);
double WindowMethodFindExpSigEvts(Double_t B);
TH1D* PlotBackgroundIsotopeEfficiency(BackgroundIsotope *bgIsotope, string additionalCut, double minEnergy, double maxEnergy);
TH1D* PlotBackgroundIsotopeEnergy(BackgroundIsotope *bgIsotope, string additionalCut, double minEnergy, double maxEnergy);

int main()
{ 
  IsotopeSample *se_sample= new IsotopeSample("Se");
  // I've hardcoded this so obviously you will need to change it
  MakePlotsForIsotope("/Users/cpatrick/SuperNEMO/MCC1_0_rootfiles/se82_0nubb_10M_sensitivity.root", "/Users/cpatrick/SuperNEMO/MCC1_0_rootfiles/se82_2nubb_10M_sensitivity.root", se_sample);
//  MakePlotsForIsotope("/Users/cpatrick/SuperNEMO/rootfiles/rootfiles_se82/se82_0nubb_1M_sensitivity.root", "/Users/cpatrick/SuperNEMO/rootfiles/rootfiles_se82/se82_2nubbHE_1M_sensitivity.root", se_sample);

  
  // IsotopeSample *ca_sample= new IsotopeSample("Ca");
  //  MakePlotsForIsotope("/Users/cpatrick/Dropbox/SuperNEMO/sensitivity/rootfiles/ca48_0nubb_100k_sensitivity.root", "/Users/cpatrick/Dropbox/SuperNEMO/sensitivity/rootfiles/ca48_2nubbHE_1M_sensitivity.root", ca_sample);
  
  //  IsotopeSample *nd_sample= new IsotopeSample("Nd");
  //  MakePlotsForIsotope("/Users/cpatrick/Dropbox/SuperNEMO/sensitivity/rootfiles/nd150_0nubb_100k.root", "/Users/cpatrick/Dropbox/SuperNEMO/sensitivity/rootfiles/nd150_2nubbHE_1M_sensitivity.root", nd_sample);
   
}

TH1D* PlotBackgroundIsotopeEfficiency(BackgroundIsotope *bgIsotope, string additionalCut, double minEnergy, double maxEnergy)
{
  TFile *f = new TFile((bgIsotope->GetRootFileName()).c_str());
  TTree *tree = (TTree*)f->Get("Sensitivity");
  int n_entries=tree->GetEntries();
  TH1D* efficiency= PlotEfficiency(tree, n_entries, additionalCut, minEnergy, maxEnergy);
  string title=bgIsotope->GetIsotopeName()+"-"+bgIsotope->GetMolarMassText()+" ("+bgIsotope->GetIsotopeLocation()+")";
  efficiency->SetTitle(title.c_str());
  return efficiency;
}


void MakePlotsForIsotope(string filename0nubb, string filename2nubb, IsotopeSample *sample)
{
  TFile *f0nubb=new TFile( filename0nubb.c_str());
  TTree *tree0nubb=(TTree*)f0nubb->Get("Sensitivity");
  
  TFile *f2nubb=new TFile( filename2nubb.c_str());
  TTree *tree2nubb=(TTree*)f2nubb->Get("Sensitivity");


  // Calculate efficiency at each cut stage

  cout<<"Sample: "<<sample->GetIsotopeName()<<"-"<<sample->GetMolarMass()<<endl;
  cout<<"---"<<endl<<"0nubb sample:"<<endl<<"---"<<endl;
  int totalEntries0nubb=CalculateEfficiencies(tree0nubb,sample,false);
  cout<<"---"<<endl<<"2nubb sample:"<<endl<<"---"<<endl;

  int totalEntries2nubb=CalculateEfficiencies(tree2nubb,sample,true);

  gStyle->SetOptStat(0);

 // MakePlotsForExtraCut(tree0nubb, totalEntries0nubb, tree2nubb, totalEntries2nubb, "&& sensitivity.number_of_electrons==2", "Two electron tracks required", "two_electron_cut", sample);

  //MakePlotsForExtraCut(tree0nubb, totalEntries0nubb, tree2nubb, totalEntries2nubb, "&& sensitivity.number_of_electrons>=1", "One or more negatively charged tracks required", "one_electron_cut", sample);
  
  MakePlotsForExtraCut(tree0nubb, totalEntries0nubb, tree2nubb, totalEntries2nubb, PROBCUT, "No charge requirement, NEMO3 internal/external prob cuts", "no_electron_cut_int_ext_prob", sample);
  
  MakePlotsForExtraCut(tree0nubb, totalEntries0nubb, tree2nubb, totalEntries2nubb, "", "No probability cuts", "no_electron_cut", sample);

  
 // MakePlotsForExtraCut(tree0nubb, totalEntries0nubb, tree2nubb, totalEntries2nubb, "&& sensitivity.number_of_electrons==2 && sensitivity.external_probability<0.01 && sensitivity.internal_probability>0.04", "Two -ve tracks,  NEMO3 internal/external prob cuts", "two_electron_int_ext_prob", sample);
  return;
}

TH1D* PlotBackgroundIsotopeEnergy(BackgroundIsotope *bgIsotope, string additionalCut, double minEnergy, double maxEnergy)
{
  TFile *f = new TFile((bgIsotope->GetRootFileName()).c_str());
  TTree *tree = (TTree*)f->Get("Sensitivity");
  int nbins=(int)(maxEnergy*20-minEnergy*20);
  string plotName="energy";
  TH1D *energyPlot=new TH1D(plotName.c_str(),plotName.c_str(),nbins,minEnergy,maxEnergy);
  string title=bgIsotope->GetIsotopeName()+"-"+bgIsotope->GetMolarMassText()+" ("+bgIsotope->GetIsotopeLocation()+")";
  energyPlot->SetTitle(title.c_str());
  
  tree->Draw("(sensitivity.total_calorimeter_energy)>>energy",(MAINCUT+additionalCut).c_str(),"HIST");
  //tree->Draw("(sensitivity.total_calorimeter_energy)>>energy",("sensitivity.number_of_electrons==2 && sensitivity.passes_two_calorimeters && sensitivity.passes_associated_calorimeters "+additionalCut ).c_str(),"HIST");
  return energyPlot;
}

void MakePlotsForExtraCut(TTree *tree0nubb, double totalEntries0nubb, TTree *tree2nubb, double totalEntries2nubb, string extraCut, string cutTitle, string cutFilenameSuffix, IsotopeSample *sample)
{
  int nbins=(int)((sample->GetMaxEnergy()*20-sample->GetMinEnergy()*20));

  TCanvas *c = new TCanvas("supernemo","supernemo",900,600);
  
  TH1D *energy0nubb=new TH1D("energy0nuBB","energy0nuBB",nbins,sample->GetMinEnergy(),sample->GetMaxEnergy());
  energy0nubb->SetLineColor(kBlack);
  energy0nubb->GetXaxis()->SetTitle("E_{1}+E_{2} (MeV)");
  energy0nubb->GetYaxis()->SetTitle("Count (area normalized to 0#nu#beta#beta)");
  energy0nubb->SetTitle(("^{"+sample->GetMolarMassText()+"}"+sample->GetIsotopeName()+" "+cutTitle).c_str());
  
  string totalcut=MAINCUT+extraCut;
  cout<<"Cut is "<<totalcut<<endl;
  tree0nubb->Draw("(sensitivity.total_calorimeter_energy)>>energy0nuBB",totalcut.c_str(),"HIST");
//  tree0nubb->Draw("(sensitivity.total_calorimeter_energy)>>energy0nuBB",("sensitivity.number_of_electrons==2 && sensitivity.passes_two_calorimeters && sensitivity.passes_associated_calorimeters && (sensitivity.higher_electron_energy != sensitivity.lower_electron_energy) "+extraCut ).c_str(),"HIST");
  
  TH1D *energy2nubb=new TH1D("energy2nuBB","energy2nuBB",nbins,sample->GetMinEnergy(),sample->GetMaxEnergy());

  energy2nubb->SetLineColor(kRed);
  tree2nubb->Draw("(sensitivity.total_calorimeter_energy)>>energy2nuBB",totalcut.c_str(),"HIST SAME");

  energy2nubb->Scale(energy0nubb->Integral()/energy2nubb->Integral());
  c->SaveAs(("plots/"+sample->GetIsotopeName()+sample->GetMolarMassText()+"_energy_"+cutFilenameSuffix+".png").c_str());

  TH1D *efficiency0nubb=PlotEfficiency(tree0nubb,totalEntries0nubb,extraCut,sample->GetMinEnergy(),sample->GetMaxEnergy());

  TH1D *efficiency2nubb=PlotEfficiency(tree2nubb,totalEntries2nubb,extraCut,sample->GetMinEnergy(),sample->GetMaxEnergy());


  // Plot efficiency for 0nubb and 2nubb
  efficiency0nubb->SetMarkerColor(kBlack);
  efficiency2nubb->SetMarkerColor(kRed);

  efficiency0nubb->SetTitle(("^{"+sample->GetMolarMassText()+"}"+sample->GetIsotopeName()+" "+cutTitle).c_str());
  efficiency0nubb->GetYaxis()->SetRangeUser (1e-8,1);
  efficiency0nubb->Draw("HIST P");
  efficiency2nubb->Scale(sample->GetFractionOfEventsIn2bbSample());
  efficiency2nubb->Draw("HIST P SAME");
  
  TLegend *efflegend = new TLegend(0.2,0.2,0.35,0.35);
  gStyle-> SetLegendBorderSize(0);
  efflegend->AddEntry(efficiency0nubb,"0#nu#beta#beta","p");
  efflegend->AddEntry(efficiency2nubb,"2#nu#beta#beta","p");
  c->SetLogy(true);
  
  efflegend->Draw();

  c->SaveAs(("plots/"+sample->GetIsotopeName()+sample->GetMolarMassText()+"_efficiency_"+cutFilenameSuffix+".png").c_str());

  // Calculate efficiencies for other background isotopes
  std::vector<TH1D*> backgroundIsotopeEfficiencies;
  std::vector<TH1D*> backgroundIsotopeEnergies;
  std::vector<BackgroundIsotope*> backgroundIsotopes;

  // #### Background isotopes go here

// Newest measurement 370uBq total
  backgroundIsotopes.push_back(new BackgroundIsotope("Tl", 208, 370.,"/Users/cpatrick/SuperNEMO/MCC1_0_rootfiles/tl208_foil_5M_sensitivity.root","foils"));
     // target is 2 uBq/kg (J Mott thesis)
//  backgroundIsotopes.push_back(new BackgroundIsotope("Tl", 208, 2.*7.,"/Users/cpatrick/SuperNEMO/rootfiles/rootfiles_backgrounds/tl208_foil_sensitivity.root","foils"));

  // From docDB 3947: 2200 uBq/kg * 7kg = 15400 uBq
  // However target is 10 uBq/kg (J Mott thesis)
  // (HOW ARE THESE SO DIFFERENT?) so try that for now
  // Using Dave's "typical measurement 300uBq per kilo"
  backgroundIsotopes.push_back(new BackgroundIsotope("Bi", 214, 300.*7.,"/Users/cpatrick/SuperNEMO/MCC1_0_rootfiles/bi214_foil_5M_sensitivity.root","foils"));
  
 // backgroundIsotopes.push_back(new BackgroundIsotope("Bi", 214, 10.*7.,"/Users/cpatrick/SuperNEMO/rootfiles/rootfiles_backgrounds/bi214_foil_sensitivity.root","foils"));
//
//  // From docDB 3947: Bi214 in mylar 210 uBq/kg * .88kg = 180uBq
//  // Calculated in docDB 3244 slide 22
//  backgroundIsotopes.push_back(new BackgroundIsotope("Bi", 214, 180.,"/Users/cpatrick/SuperNEMO/rootfiles/rootfiles_backgrounds/bi214_surf_sensitivity.root","foil_surface"));
//
//  
//  // Tl208 in mylar 34.2 uBq/kg * .88kg = 30uBq
//  // Calculated in docDB 3244 slide 21, mass of mylar from docDB 3947
//  backgroundIsotopes.push_back(new BackgroundIsotope("Tl", 208, 30.1,"/Users/cpatrick/SuperNEMO/rootfiles/rootfiles_backgrounds/tl208_surf_sensitivity.root","foil_surface"));
//
//  // Bi214 in the tracker itself.
//  // A gas flow-through rate will be picked to get the radon activity to the target of
//  // 0.15 mBq/m^3 (That looks like it will require 2m^3/hour of flow)
//  // Total activity is 0.15mBq times the volume of the tracker (4 C sections)
//  // Each tracker section is 3.8 m3
//  backgroundIsotopes.push_back(new BackgroundIsotope("Bi", 214, 150.*4.*3.8,"/Users/cpatrick/SuperNEMO/rootfiles/rootfiles_backgrounds/bi214_wires_sensitivity.root","wires"));
  
  for (int i=0;i<backgroundIsotopes.size();i++)
    {
      backgroundIsotopeEfficiencies.push_back(PlotBackgroundIsotopeEfficiency(backgroundIsotopes.at(i),extraCut,sample->GetMinEnergy(),sample->GetMaxEnergy()));
      backgroundIsotopeEnergies.push_back(PlotBackgroundIsotopeEnergy(backgroundIsotopes.at(i),extraCut,sample->GetMinEnergy(),sample->GetMaxEnergy()));
    }
  
  // Use the efficiencies to calculate a sensitivity
  
  TH1D *sensitivity=EstimateSensitivity(energy0nubb, energy2nubb,sample,efficiency0nubb,efficiency2nubb);
  c->SetLogy(false);
  sensitivity->GetYaxis()->SetRangeUser(0,1e25);
  sensitivity->SetTitle(("^{"+sample->GetMolarMassText()+"}"+sample->GetIsotopeName()+" "+cutTitle).c_str());
  sensitivity->Draw("HIST P");
  c->SaveAs(("plots/"+sample->GetIsotopeName()+sample->GetMolarMassText()+"_sensitivity_window_method_"+cutFilenameSuffix+".png").c_str());

  // Get an overall sensitivity from TLimit and compare

  TH1D *tempSignal=(TH1D*)energy0nubb->Clone();
  TH1D *scaledBkgd=(TH1D*)energy2nubb->Clone();
  // Expeccted number of background events in the plotted range
  double backgroundEvents=EstimateBackgroundEvents(efficiency2nubb->GetBinContent(1), sample);
  
  cout<<"Expected number of 2nubb events "<<backgroundEvents<<endl;
  scaledBkgd->Sumw2();
  // If we scale by this number for our initial plot, we have it correctly-normalized 
  scaledBkgd->Scale(backgroundEvents/scaledBkgd->Integral());
  TH1D *tempData=(TH1D*)scaledBkgd->Clone();
  
  double expectedSignalEventLimit=expectedSignalEventLimit=ExpectedLimitSigEvts(0.1, tempSignal,scaledBkgd, tempData);
  double tLimitSensitivity= efficiency0nubb->GetBinContent(1) *  sample->GetIsotopeMassKg()*1000 *  sample->GetExposureYears() * AVOGADRO * TMath::Log(2)/(sample->GetMolarMass() * expectedSignalEventLimit );

  // Plot them all together
  // energy 0nubb scaled to... expected number of events or something?
  // energy of 2nubb scaled
  // energy of each background scaled
  scaledBkgd->SetLineColor(kBlue);
  scaledBkgd->SetLineWidth(3);
  scaledBkgd->GetYaxis()->SetTitle("Expected events");
  scaledBkgd->GetXaxis()->SetTitle("Summed electron energies (MeV)");
  scaledBkgd->SetTitle("Signal and background energy spectra");
  scaledBkgd->Draw("HIST");
  TLegend *legend = new TLegend(0.6,0.65,0.9,0.85);
  gStyle-> SetLegendBorderSize(0);

  legend->AddEntry(scaledBkgd,"2#nu#beta#beta","l");
  
  // Get TLimit sensitivity with additional backgrounds
  TH1D *totalBkgd=(TH1D*)scaledBkgd->Clone();
  totalBkgd->Sumw2();
  int colours[]={kOrange,kGreen+2,kMagenta,kTeal,kPink};
  for (int i=0;i<backgroundIsotopes.size();i++)
    {
      BackgroundIsotope *thisIsotope=backgroundIsotopes.at(i);
      double thisIsotopeEfficiency=backgroundIsotopeEfficiencies.at(i)->GetBinContent(1);
      double thisIsotopeEvents=thisIsotope->GetActivityMicroBq()*1e-6 * thisIsotopeEfficiency  * (sample->GetExposureYears() * 3600 * 24 * 365.25); // Number of events; get the units right
      
      cout<<thisIsotope->GetIsotopeName()<<" "<<thisIsotope->GetIsotopeLocation()<<" Efficiency: "<<thisIsotopeEfficiency<<" Events: "<<thisIsotopeEvents<<endl;
      TH1D *thisIsotopeEnergy=backgroundIsotopeEnergies.at(i);
      thisIsotopeEnergy->Sumw2();
      thisIsotopeEnergy->Scale(thisIsotopeEvents/thisIsotopeEnergy->Integral());

      totalBkgd->Add(thisIsotopeEnergy);
      thisIsotopeEnergy->SetLineColor(colours[i]);
      thisIsotopeEnergy->SetLineWidth(3);
      thisIsotopeEnergy->Draw("HIST SAME");
      legend->AddEntry(thisIsotopeEnergy,("^{"+thisIsotope->GetMolarMassText()+"}"+thisIsotope->GetIsotopeName()+" ("+thisIsotope->GetIsotopeLocation()+")").c_str(),"l");
    }
  tempData=(TH1D*)totalBkgd->Clone();
  double totalExpectedSignalEventLimit=ExpectedLimitSigEvts(0.1, tempSignal,totalBkgd, tempData);
  double totalTLimitSensitivity= efficiency0nubb->GetBinContent(1) *  sample->GetIsotopeMassKg()*1000 *  sample->GetExposureYears() * AVOGADRO * TMath::Log(2)/(sample->GetMolarMass() * totalExpectedSignalEventLimit );
  
    
  // Print the results last because TLimit has masses of annoying output
  cout<<"Sensitivity from TLimit (no other isotopes): "<<tLimitSensitivity<<" years "<<endl;
  cout<<"Sensitivity from Window Method (no other isotopes): "<<sensitivity->GetBinContent(sensitivity->GetMaximumBin())<<" cutting at  "<<sensitivity->GetBinLowEdge(sensitivity->GetMaximumBin())<<"MeV"<<endl;
  cout<<"Sensitivity from TLimit including background isotopes: "<<totalTLimitSensitivity<<" years "<<endl; 

  TH1D *scaledSignal=(TH1D*)energy0nubb->Clone();
  scaledSignal->SetLineColor(kRed);
  scaledSignal->SetLineWidth(3);
  cout<<"Expected signal event limit "<< totalExpectedSignalEventLimit<<endl;
  scaledSignal->Scale(totalExpectedSignalEventLimit/energy0nubb->Integral());
  scaledSignal->Draw("HIST SAME");
  legend->AddEntry(scaledSignal,"0#nu#beta#beta","l");
  legend->Draw();
  c->SetLogy(true);
  c->SaveAs("plots/all_bkgds.png");
  c->SetLogy(false);
}


TH1D* PlotEfficiency(TTree *tree, double totalEntries, string additionalCut, double minEnergy, double maxEnergy)
{
  int nbins=(int)((maxEnergy*20)-(minEnergy*20));
  TH1D *efficiency= new TH1D("efficiency","efficiency",nbins,minEnergy,maxEnergy);
  for (int bin=1;bin<=efficiency->GetNbinsX();bin++)
  {
    double lowEnergyLimit=efficiency->GetXaxis()->GetBinLowEdge(bin);
    
    string cut= MAINCUT+PROBCUT+ Form(" &&(sensitivity.total_calorimeter_energy) >= %f && (sensitivity.total_calorimeter_energy) < %f", lowEnergyLimit,maxEnergy);
    cut = cut +additionalCut;
    double entriesPassingCut=tree->GetEntries(cut.c_str());
    efficiency->SetBinContent(bin,(double)entriesPassingCut/(double)totalEntries);
  }
  efficiency->SetMarkerSize(1);
  efficiency->SetMarkerStyle(kFullCircle);
  efficiency->GetYaxis()->SetTitle("Efficiency");
  string title=Form("Energy (MeV) #leq #Sigma_{12} E_{calibrated}#leq %.1f MeV",maxEnergy);
  efficiency->GetXaxis()->SetTitle(title.c_str());
  return efficiency;
  
}

TH1D* EstimateSensitivity(TH1D *energy0nubb, TH1D *energy2nubb, IsotopeSample *sample, TH1D* efficiency0nubb, TH1D* efficiency2nubb)
{
  
  TH1D *scaledBkgd=(TH1D*)energy2nubb->Clone();
  double backgroundEvents=EstimateBackgroundEvents(efficiency2nubb->GetBinContent(1), sample);
  scaledBkgd->Sumw2();
  // If we scale by this number for our initial plot, we have a correctly-normalized 
  scaledBkgd->Scale(backgroundEvents/scaledBkgd->Integral());
  TH1D *sensitivity=(TH1D*)energy0nubb->Clone();
  sensitivity->Reset();
  
  TH1D *signalEventLimit=(TH1D*)energy0nubb->Clone();
  signalEventLimit->Reset();
  
  cout<< "Window method"<<endl;
  for (int i=1;i<=energy0nubb->GetNbinsX();i++)
    {
      double expectedSignalEventLimit;
      expectedSignalEventLimit= WindowMethodFindExpSigEvts(scaledBkgd->Integral(i,energy0nubb->GetNbinsX()));
      cout<<"Bin "<<i<<": expected signal event limit: "<<expectedSignalEventLimit<<endl;
      double thisSensitivity= efficiency0nubb->GetBinContent(i) *  sample->GetIsotopeMassKg()*1000 *  sample->GetExposureYears() * AVOGADRO * TMath::Log(2)/(sample->GetMolarMass() * expectedSignalEventLimit );
      sensitivity->SetBinContent(i,thisSensitivity);
      signalEventLimit->SetBinContent(i,expectedSignalEventLimit);
    }
  
  sensitivity->SetMarkerSize(1);
  sensitivity->SetMarkerStyle(kFullCircle);
  sensitivity->GetYaxis()->SetTitle("0#nu#beta#beta halflife sensitivity");
  sensitivity->GetYaxis()->SetTitleOffset(1.2);
  string title=Form("Energy (MeV) #leq #Sigma_{12} E_{calibrated}#leq %.1f MeV",sample->GetMaxEnergy());
  sensitivity->GetXaxis()->SetTitle(title.c_str());

  signalEventLimit->Print("ALL");
  return sensitivity;
}

// Stolen from James Mott, thanks James
double WindowMethodFindExpSigEvts(Double_t B){

  //Find S using CL(S+B)/CL(B) = 0.1 with N_Obs = B
  Double_t Likelihood = 1.0;
  Double_t S = 0;
  Int_t NEvts = (int)B;

  while(Likelihood > 0.1){
    S += 0.001;
    Float_t CLsb = 0; Float_t CLb = 0; 
    for (Int_t i=0; i<=NEvts; i++) {
      CLsb+=TMath::Poisson(i,S+B);
      CLb+=TMath::Poisson(i,B);
    }
    Likelihood =  CLsb/CLb;
    //    cout << "S = " << S << "\tCLb = " << CLb << "\tCLsb = " << CLsb << "\tCLs = " << Likelihood << endl;
  }

  return S;
}

// Adapted from James Mott's LimitCalculationFunctions, thanks James!
double ExpectedLimitSigEvts(double ConfidenceLevel, TH1D* h_signal, TH1D* h_background, TH1D* h_data ) {

  double low_bound = 0.1/h_signal->Integral();
  double high_bound = 1000.0/h_signal->Integral();
  
  TH1D* null_hyp_signal = (TH1D*) h_signal->Clone("null_hyp_signal"); null_hyp_signal->Scale(low_bound);
  TH1D* disc_hyp_signal = (TH1D*) h_signal->Clone("disc_hyp_signal"); disc_hyp_signal->Scale(high_bound);

  TLimitDataSource* mydatasource = new TLimitDataSource(null_hyp_signal, h_background, h_data);

  TConfidenceLevel* myconfidence = TLimit::ComputeLimit(mydatasource, 50000);
  double low_bound_cl = myconfidence->CLs();
  
  delete mydatasource;

  mydatasource = new TLimitDataSource(disc_hyp_signal, h_background, h_data);
 
  myconfidence = TLimit::ComputeLimit(mydatasource, 50000);
  
  double high_bound_cl = myconfidence->CLs();

  delete mydatasource;

  double accuracy = 0.01;
  double this_cl = 0;
  double this_val = 0;

  while  (fabs(high_bound - low_bound) * h_signal->Integral() > accuracy) {
    // bisection
     this_val = low_bound+(high_bound - low_bound)/3;

    TH1D* this_signal = (TH1D*) h_signal->Clone("test_signal");
    this_signal->Scale(this_val);
    
    mydatasource = new TLimitDataSource(this_signal, h_background, h_data);
    myconfidence = TLimit::ComputeLimit(mydatasource, 50000);

    this_cl = myconfidence->GetExpectedCLs_b();
    if (this_cl > ConfidenceLevel) {
      low_bound = this_val;
      low_bound_cl = this_cl;
    } else {
      high_bound = this_val;
      high_bound_cl = this_cl;
    }

    delete mydatasource;
    delete this_signal;
    delete myconfidence;
  }

  delete null_hyp_signal;
  delete disc_hyp_signal;
  
  return h_signal->Integral() * this_val;
}

double EstimateHalflifeSensitivity  (double signalEfficiency, double backgroundEfficiency, IsotopeSample *sample)
{
  double numberOfSigma=4.;
  // Get the total number of background events we expect to see in the energy window, after all cuts
  double backgroundEvents=EstimateBackgroundEvents(backgroundEfficiency, sample);
  if (backgroundEvents==0) return 0; // Is this true? Maybe if there is no background there is no background and that is just great

   // Use formula from p7 of Reviews of Modern Physics vol 80 issue 2 pages 481-516 (2008)
   
   // Background per kilo per year = b Delta E in formula
   double backgroundRate=backgroundEvents / ( sample->GetIsotopeMassKg() *  sample->GetExposureYears());
   
   double sensitivity=(4.16e26 / numberOfSigma) * (signalEfficiency/sample->GetMolarMass()) *  TMath::Sqrt( sample->GetIsotopeMassKg() *  sample->GetExposureYears()/backgroundRate );
  
  return sensitivity;
}


double EstimateBackgroundEvents(double backgroundEfficiency, IsotopeSample *sample)
{
  // Get the number of atoms you start with
  double nSourceAtoms=AVOGADRO * (sample->GetIsotopeMassKg()*1000) /sample->GetMolarMass(); //Avogadro is grams

  // Get the number of atoms there will be remaining after the exposure time in years, based on the half life for 2nu double beta
  //n(t) = n(0) exp-(t/tau)  where tau=halflife/ln 2
  // double nRemainingAtoms=nSourceAtoms * TMath::Exp(-1*TMath::Log(2) * exposureYears / backgroundHalfLife);

  // The exponent is around 10^-20, it's too small for TMath::Exp to deal with
  // Can we just go for a Taylor expansion for 1-e^-x where x is v small?
  // 1( - e^-x) ~ x so...
  
  double totalDecays=nSourceAtoms * (TMath::Log(2) * sample->GetExposureYears() / sample->GetBackgroundHalfLife());

  // Multiply by the efficiency and that is the amount of background events you expect to see

  double events=totalDecays * backgroundEfficiency;
  
  //cout<<totalDecays<<" backgrounds, of which we see "<<events<<endl;
  return events;
}

int CalculateEfficiencies(TTree *tree,  IsotopeSample *sample, bool is2nubb, int allEntries)
{
  // Reconstructable events
  int totalEntries=tree->GetEntries();

  // In the 2nubb case, some simulated events are not reconstructed
  cout<<"Total events "<<totalEntries<<endl;
  cout<<"Reconstructable entries "<<totalEntries<<endl;

  // Our efficiency should be calculated as a fraction of the total events we generated, not as a fraction of the events we managed to reconstruct
  
  if (allEntries>0) totalEntries=allEntries; //Use this if not all entries were reconstructable
  
  int passesCalCut=tree->GetEntries("sensitivity.passes_two_calorimeters");
  cout<<"Two triggered calorimeters: "<<(double)passesCalCut/(double)totalEntries * 100<<"%"<<endl;

  // 2 tracker clusters
  int passesClusterCut=tree->GetEntries("sensitivity.passes_two_calorimeters && sensitivity.passes_two_clusters");
  cout<<"Two tracker clusters with a minimum of 3 cells: "<<(double)passesClusterCut/(double)totalEntries * 100<<"%"<<endl;
  
  // 2 reconstructed tracks
  int passesTrackCut=tree->GetEntries("sensitivity.passes_two_calorimeters && sensitivity.passes_two_clusters && sensitivity.passes_two_tracks ");
  cout<<"Two reconstructed tracks: "<<(double)passesTrackCut/(double)totalEntries * 100<<"%"<<endl;

  // Tracks have associated calorimeter hits
  
  int passesAssociatedCalCut=tree->GetEntries("sensitivity.passes_two_calorimeters && sensitivity.passes_two_clusters && sensitivity.passes_two_tracks && sensitivity.passes_associated_calorimeters");
  cout<<"Tracks have associated calorimeter hits: "<<(double)passesAssociatedCalCut/(double)totalEntries * 100<<"%"<<endl;

  // Passes NEMO3 internal/external probability cuts
  int passesProbabilityCut=tree->GetEntries("sensitivity.passes_two_calorimeters && sensitivity.passes_two_clusters && sensitivity.passes_two_tracks && sensitivity.passes_associated_calorimeters && sensitivity.external_probability<0.01 && sensitivity.internal_probability>0.04 ");
  cout<<"And passes internal/external probability cut: "<<(double)passesProbabilityCut/(double)totalEntries * 100<<"%"<<endl;

  // Passes NEMO3 internal/external probability cuts, 2-3.2 MeV
  int passesProbabilityAndRoI=tree->GetEntries("sensitivity.passes_two_calorimeters && sensitivity.passes_two_clusters && sensitivity.passes_two_tracks && sensitivity.passes_associated_calorimeters && sensitivity.external_probability<0.01 && sensitivity.internal_probability>0.04 &&  (sensitivity.total_calorimeter_energy)>=2 &&   (sensitivity.total_calorimeter_energy)< 3.2");
  cout<<"Passes internal/external probability in Se82ROI: "<<(double)passesProbabilityAndRoI/(double)totalEntries * 100<<"%"<<endl;

  // And both tracks have negative charge reconstruction
  
//  int passesTwoElectronCut=tree->GetEntries("sensitivity.passes_two_calorimeters && sensitivity.passes_two_clusters && sensitivity.passes_two_tracks && sensitivity.passes_associated_calorimeters && sensitivity.number_of_electrons==2  && sensitivity.external_probability<0.01 && sensitivity.internal_probability>0.04 &&  (sensitivity.total_calorimeter_energy)>=2 &&   (sensitivity.total_calorimeter_energy)< 3.2");
 // cout<<"And both tracks have negative charge: "<<(double)passesTwoElectronCut/(double)totalEntries * 100<<"%"<<endl;
  
  return totalEntries;
}
