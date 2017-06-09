//
//  SFoilRadonWeight.cpp
//
//  Created by Stefano Torre on 20/05/13.
//
//  This module is intended to provide the appropriate weighting to take into account the fact that 
//  the distribtuion of radon on the surface of the foils is not uniform in reality, but is modelled 
//  this way in the MC.  

//  We calculate this weighting using activities for each phase, sector and side of the foil surface 
//  as measured in Mo100 and Se82 sectors. For other sectors the average activity is used as of 20/05/13

#include <iostream>
#include "NemoUtils/SFoilRadonWeight.h"
#include "Hereward/DataProcPipeline/AbsEnv.h"

SFoilRadonWeight::SFoilRadonWeight() {

  SurfacePosition foil;
  Activity rn_act_P1, rn_act_P2;

  total_Rn_Act_P1 = 0;
  avg_sfoil_act_P1 = 0; 
  avg_sfoil_act_P1_err = 0;
  total_Rn_Act_P2 = 0;
  avg_sfoil_act_P2 = 0; 
  avg_sfoil_act_P2_err = 0;

  foilSideChecker_ = new SFoilSide();
  sectorfinder_    = new SectorData();

  // ACTIVITIES ARE HARD-CODED HERE, BUT SHOULD PROBABLY BE ADDED TO A DATABASE AT AN OPPORTUNE MOMENT!
  foil = SurfacePosition(0, 0 );  rn_act_P1 = Activity(10.53, 0.61);  rn_act_P2 = Activity( 2.77, 0.18);  add_Rn_P1(foil, rn_act_P1); add_Rn_P2(foil, rn_act_P2);
  foil = SurfacePosition(0, 1 );  rn_act_P1 = Activity(10.09, 0.53);  rn_act_P2 = Activity( 2.39, 0.11);  add_Rn_P1(foil, rn_act_P1); add_Rn_P2(foil, rn_act_P2);
  foil = SurfacePosition(0, 2 );  rn_act_P1 = Activity(16.46, 0.61);  rn_act_P2 = Activity( 5.28, 0.13);  add_Rn_P1(foil, rn_act_P1); add_Rn_P2(foil, rn_act_P2);
  foil = SurfacePosition(0, 3 );  rn_act_P1 = Activity(20.32, 0.69);  rn_act_P2 = Activity(10.27, 0.18);  add_Rn_P1(foil, rn_act_P1); add_Rn_P2(foil, rn_act_P2);
  foil = SurfacePosition(0, 4 );  rn_act_P1 = Activity(11.64, 0.63);  rn_act_P2 = Activity( 4.76, 0.17);  add_Rn_P1(foil, rn_act_P1); add_Rn_P2(foil, rn_act_P2);
  foil = SurfacePosition(0, 5 );  rn_act_P1 = Activity( 5.74, 0.51);  rn_act_P2 = Activity( 2.29, 0.12);  add_Rn_P1(foil, rn_act_P1); add_Rn_P2(foil, rn_act_P2);
  foil = SurfacePosition(0, 6 );  rn_act_P1 = Activity( 9.09, 0.56);  rn_act_P2 = Activity( 1.43, 0.12);  add_Rn_P1(foil, rn_act_P1); add_Rn_P2(foil, rn_act_P2);
  foil = SurfacePosition(0, 7 );  rn_act_P1 = Activity( 8.59, 0.60);  rn_act_P2 = Activity( 1.46, 0.12);  add_Rn_P1(foil, rn_act_P1); add_Rn_P2(foil, rn_act_P2);
  foil = SurfacePosition(0, 8 );  rn_act_P1 = Activity( 8.08, 0.98);  rn_act_P2 = Activity( 1.35, 0.20);  add_Rn_P1(foil, rn_act_P1); add_Rn_P2(foil, rn_act_P2);
  foil = SurfacePosition(0, 9 );  rn_act_P1 = Activity(10.53, 0.61);  rn_act_P2 = Activity( 2.77, 0.18);  add_Rn_P1(foil, rn_act_P1); add_Rn_P2(foil, rn_act_P2);
  foil = SurfacePosition(0, 10);  rn_act_P1 = Activity( 9.00, 0.59);  rn_act_P2 = Activity( 2.03, 0.09);  add_Rn_P1(foil, rn_act_P1); add_Rn_P2(foil, rn_act_P2);
  foil = SurfacePosition(0, 11);  rn_act_P1 = Activity( 7.59, 0.56);  rn_act_P2 = Activity( 1.65, 0.10);  add_Rn_P1(foil, rn_act_P1); add_Rn_P2(foil, rn_act_P2);
  foil = SurfacePosition(0, 12);  rn_act_P1 = Activity( 7.03, 0.50);  rn_act_P2 = Activity( 1.27, 0.09);  add_Rn_P1(foil, rn_act_P1); add_Rn_P2(foil, rn_act_P2);
  foil = SurfacePosition(0, 13);  rn_act_P1 = Activity( 6.83, 0.47);  rn_act_P2 = Activity( 0.73, 0.12);  add_Rn_P1(foil, rn_act_P1); add_Rn_P2(foil, rn_act_P2);
  foil = SurfacePosition(0, 14);  rn_act_P1 = Activity( 7.67, 0.43);  rn_act_P2 = Activity( 1.27, 0.09);  add_Rn_P1(foil, rn_act_P1); add_Rn_P2(foil, rn_act_P2);
  foil = SurfacePosition(0, 15);  rn_act_P1 = Activity( 6.88, 0.48);  rn_act_P2 = Activity( 1.26, 0.10);  add_Rn_P1(foil, rn_act_P1); add_Rn_P2(foil, rn_act_P2);
  foil = SurfacePosition(0, 16);  rn_act_P1 = Activity(12.13, 0.59);  rn_act_P2 = Activity( 2.05, 0.11);  add_Rn_P1(foil, rn_act_P1); add_Rn_P2(foil, rn_act_P2);
  foil = SurfacePosition(0, 17);  rn_act_P1 = Activity(10.53, 0.61);  rn_act_P2 = Activity( 2.77, 0.18);  add_Rn_P1(foil, rn_act_P1); add_Rn_P2(foil, rn_act_P2);
  foil = SurfacePosition(0, 18);  rn_act_P1 = Activity(10.53, 0.61);  rn_act_P2 = Activity( 2.77, 0.18);  add_Rn_P1(foil, rn_act_P1); add_Rn_P2(foil, rn_act_P2);
  foil = SurfacePosition(0, 19);  rn_act_P1 = Activity(10.53, 0.61);  rn_act_P2 = Activity( 2.77, 0.18);  add_Rn_P1(foil, rn_act_P1); add_Rn_P2(foil, rn_act_P2);
  foil = SurfacePosition(1, 0 );  rn_act_P1 = Activity(10.53, 0.61);  rn_act_P2 = Activity( 2.77, 0.18);  add_Rn_P1(foil, rn_act_P1); add_Rn_P2(foil, rn_act_P2);
  foil = SurfacePosition(1, 1 );  rn_act_P1 = Activity(13.23, 0.53);  rn_act_P2 = Activity( 3.48, 0.11);  add_Rn_P1(foil, rn_act_P1); add_Rn_P2(foil, rn_act_P2);
  foil = SurfacePosition(1, 2 );  rn_act_P1 = Activity(17.48, 0.57);  rn_act_P2 = Activity( 5.74, 0.13);  add_Rn_P1(foil, rn_act_P1); add_Rn_P2(foil, rn_act_P2);
  foil = SurfacePosition(1, 3 );  rn_act_P1 = Activity(23.65, 0.62);  rn_act_P2 = Activity(13.43, 0.25);  add_Rn_P1(foil, rn_act_P1); add_Rn_P2(foil, rn_act_P2);
  foil = SurfacePosition(1, 4 );  rn_act_P1 = Activity(14.28, 0.53);  rn_act_P2 = Activity( 4.56, 0.13);  add_Rn_P1(foil, rn_act_P1); add_Rn_P2(foil, rn_act_P2);
  foil = SurfacePosition(1, 5 );  rn_act_P1 = Activity( 7.54, 0.48);  rn_act_P2 = Activity( 2.48, 0.12);  add_Rn_P1(foil, rn_act_P1); add_Rn_P2(foil, rn_act_P2);
  foil = SurfacePosition(1, 6 );  rn_act_P1 = Activity(11.02, 0.48);  rn_act_P2 = Activity( 1.58, 0.10);  add_Rn_P1(foil, rn_act_P1); add_Rn_P2(foil, rn_act_P2);
  foil = SurfacePosition(1, 7 );  rn_act_P1 = Activity(11.05, 0.48);  rn_act_P2 = Activity( 1.57, 0.11);  add_Rn_P1(foil, rn_act_P1); add_Rn_P2(foil, rn_act_P2);
  foil = SurfacePosition(1, 8 );  rn_act_P1 = Activity( 9.90, 0.87);  rn_act_P2 = Activity( 1.55, 0.18);  add_Rn_P1(foil, rn_act_P1); add_Rn_P2(foil, rn_act_P2);
  foil = SurfacePosition(1, 9 );  rn_act_P1 = Activity(10.53, 0.61);  rn_act_P2 = Activity( 2.77, 0.18);  add_Rn_P1(foil, rn_act_P1); add_Rn_P2(foil, rn_act_P2);
  foil = SurfacePosition(1, 10);  rn_act_P1 = Activity( 7.53, 0.44);  rn_act_P2 = Activity( 1.35, 0.12);  add_Rn_P1(foil, rn_act_P1); add_Rn_P2(foil, rn_act_P2);
  foil = SurfacePosition(1, 11);  rn_act_P1 = Activity(11.35, 0.45);  rn_act_P2 = Activity( 2.04, 0.09);  add_Rn_P1(foil, rn_act_P1); add_Rn_P2(foil, rn_act_P2);
  foil = SurfacePosition(1, 12);  rn_act_P1 = Activity( 7.13, 0.42);  rn_act_P2 = Activity( 1.11, 0.08);  add_Rn_P1(foil, rn_act_P1); add_Rn_P2(foil, rn_act_P2);
  foil = SurfacePosition(1, 13);  rn_act_P1 = Activity( 7.02, 0.46);  rn_act_P2 = Activity( 1.01, 0.11);  add_Rn_P1(foil, rn_act_P1); add_Rn_P2(foil, rn_act_P2);
  foil = SurfacePosition(1, 14);  rn_act_P1 = Activity( 8.48, 0.42);  rn_act_P2 = Activity( 1.37, 0.09);  add_Rn_P1(foil, rn_act_P1); add_Rn_P2(foil, rn_act_P2);
  foil = SurfacePosition(1, 15);  rn_act_P1 = Activity( 9.70, 0.46);  rn_act_P2 = Activity( 1.15, 0.09);  add_Rn_P1(foil, rn_act_P1); add_Rn_P2(foil, rn_act_P2);
  foil = SurfacePosition(1, 16);  rn_act_P1 = Activity( 9.28, 0.55);  rn_act_P2 = Activity( 1.16, 0.12);  add_Rn_P1(foil, rn_act_P1); add_Rn_P2(foil, rn_act_P2);
  foil = SurfacePosition(1, 17);  rn_act_P1 = Activity(10.53, 0.61);  rn_act_P2 = Activity( 2.77, 0.18);  add_Rn_P1(foil, rn_act_P1); add_Rn_P2(foil, rn_act_P2);
  foil = SurfacePosition(1, 18);  rn_act_P1 = Activity(10.53, 0.61);  rn_act_P2 = Activity( 2.77, 0.18);  add_Rn_P1(foil, rn_act_P1); add_Rn_P2(foil, rn_act_P2);
  foil = SurfacePosition(1, 19);  rn_act_P1 = Activity(10.53, 0.61);  rn_act_P2 = Activity( 2.77, 0.18);  add_Rn_P1(foil, rn_act_P1); add_Rn_P2(foil, rn_act_P2);


  std::cout << "-------- SFoilRadonWeigth - Initializing radon map -----------------------------------------\n"
	    << "- total Rn activity in phase 1: " << total_Rn_Act_P1 << "\n"
	    << "- total RN activity in phase 2: " << total_Rn_Act_P2 << "\n"
	    << "- average foil surface activity in phase 1: " << avg_sfoil_act_P1 
	    << " +- " << avg_sfoil_act_P1_err << "\n"
	    << "- average foil surface activity in phase 2: " << avg_sfoil_act_P2 
	    << " +- " << avg_sfoil_act_P2_err << "\n"
	    << "--------------------------------------------------------------------------------------------\n"
	    << std::endl;
  RandomNumGen = new TRandom3(108346);  
}

SFoilRadonWeight::~SFoilRadonWeight() {
  activities_Rn_P1.clear();
  activities_Rn_P2.clear();
  delete foilSideChecker_;
  delete sectorfinder_;
  delete RandomNumGen;
}

void SFoilRadonWeight::add_Rn_P1(SurfacePosition &aSurfacePosition, Activity &anActivity) {
  if (activities_Rn_P1.find(aSurfacePosition) == activities_Rn_P1.end()) {
    total_Rn_Act_P1 += anActivity.act;

    double this_pct_err = anActivity.act_error/anActivity.act;
    double act_percent_error = (activities_Rn_P1.size() == 0) ? 0 : avg_sfoil_act_P1_err/avg_sfoil_act_P1;

    activities_Rn_P1.insert(std::pair<SurfacePosition, Activity>(aSurfacePosition, anActivity));
    avg_sfoil_act_P1 = total_Rn_Act_P1/(activities_Rn_P1.size());
    act_percent_error = ((act_percent_error * 
			  (activities_Rn_P1.size() - 1) + this_pct_err) /
			 activities_Rn_P1.size());
    avg_sfoil_act_P1_err = act_percent_error * avg_sfoil_act_P1;
  }
}

void SFoilRadonWeight::add_Rn_P2(SurfacePosition &aSurfacePosition, Activity &anActivity) {
  if (activities_Rn_P2.find(aSurfacePosition) == activities_Rn_P2.end()) {
    total_Rn_Act_P2 += anActivity.act;

    double this_pct_err = anActivity.act_error/anActivity.act;
    double act_percent_error = (activities_Rn_P2.size() == 0) ? 0 : avg_sfoil_act_P2_err/avg_sfoil_act_P2;

    activities_Rn_P2.insert(std::pair<SurfacePosition, Activity>(aSurfacePosition, anActivity));
    avg_sfoil_act_P2 = total_Rn_Act_P2/(activities_Rn_P2.size());
    act_percent_error = ((act_percent_error * 
			  (activities_Rn_P2.size() - 1) + this_pct_err) /
			 activities_Rn_P2.size());
    avg_sfoil_act_P2_err = act_percent_error * avg_sfoil_act_P2;
  }
}

SFoilRadonWeight::SurfacePosition SFoilRadonWeight::getSurfacePosition(CLHEP::Hep3Vector trueVertex) const {

  int side   = foilSideChecker_->getSFoilSide(trueVertex);
  int sector = (int)sectorfinder_   ->sectorNumber(trueVertex);
  return SurfacePosition(side, sector);
}

SFoilRadonWeight::SurfacePosition SFoilRadonWeight::getSurfacePosition(double x, double y, double z) const {
  return getSurfacePosition(CLHEP::Hep3Vector(x,y,z));
}

double SFoilRadonWeight::getSFoilRadonWeight(CLHEP::Hep3Vector trueVertex) const{

  SurfacePosition wire = getSurfacePosition(trueVertex);

  double activity, activity_err;

  if (AbsEnv::instance()->runNumber() < 3396) {    
    std::map<SurfacePosition, Activity>::const_iterator entry = activities_Rn_P1.find(wire);
    if (entry == activities_Rn_P1.end()) {
      activity     = 1;
      activity_err = avg_sfoil_act_P1_err/avg_sfoil_act_P1;
    } else {
      activity     = (entry->second.act)/avg_sfoil_act_P1;
      activity_err = (entry->second.act_error)/avg_sfoil_act_P1;
    }
  } else {
    std::map<SurfacePosition, Activity>::const_iterator entry = activities_Rn_P2.find(wire);
    if (entry == activities_Rn_P2.end()) {
      activity     = 1;
      activity_err = avg_sfoil_act_P2_err/avg_sfoil_act_P2;
    } else {
      activity     = (entry->second.act)/avg_sfoil_act_P2;
      activity_err = (entry->second.act_error)/avg_sfoil_act_P2;
    }
  }

  double weight = RandomNumGen->Gaus(activity,activity_err);
  while (weight < 0){weight = RandomNumGen->Gaus(activity,activity_err);}

  return weight;
}
