//
//  SFoilRadonWeight.h
//
//  Created by James Mott on 09/10/12.
//

#ifndef SFOILRADONWEIGHT_H_
#define SFOILRADONWEIGHT_H_
#include "CLHEP/Vector/ThreeVector.h"
#include "NemoUtils/SectorData.h"
#include "NemoUtils/SFoilSide.h"

#include "TRandom3.h"

#include <map>

class SFoilRadonWeight {

  struct SurfacePosition {
  public:
  SurfacePosition() :
    side(-1), sector(-1) {
    }
    
  SurfacePosition(int aSide, int aSector) :
    side(aSide), sector(aSector){        
    }
    
  SurfacePosition(const SurfacePosition &obj) :
    side(obj.side), sector(obj.sector) {
    }
    
    SurfacePosition &operator = (const SurfacePosition &obj) {
      if (this != &obj) {
	side    = obj.side;
	sector  = obj.sector;
      }
      return (*this);
    }

      bool operator<(const SurfacePosition &obj) const {
	if (sector < obj.sector){
	  return true;
	}
	else if (sector == obj.sector){
	  if(side < obj.side){
	    return true;
	  }
	}
	return false;
      }

    int side;
    int sector;
  };


  struct Activity {
  public:
  Activity() :
    act(0), act_error(0){        
    }

  Activity(double anAct, double anError) :
    act(anAct), act_error(anError){        
    }
    
    Activity &operator = (const Activity &obj) {
      if (this != &obj) {
	act       = obj.act;
	act_error = obj.act_error;
      }
      return (*this);
    }

      double act;
    double act_error;
  };

 public:
  SFoilRadonWeight();
  ~SFoilRadonWeight();
  double  getSFoilRadonWeight(CLHEP::Hep3Vector trueVertex) const;
  double  getTotalRnActP1() const {return total_Rn_Act_P1;}
  double  getTotalRnActP2() const {return total_Rn_Act_P2;}

 private:
  SurfacePosition getSurfacePosition(CLHEP::Hep3Vector trueVertex) const;
  SurfacePosition getSurfacePosition(double x, double y, double z) const;
    
  void add_Rn_P1(SurfacePosition &aSurfacePosition, Activity &anActivity);
  void add_Rn_P2(SurfacePosition &aSurfacePosition, Activity &anActivity);
  std::map<SurfacePosition, Activity> activities_Rn_P1;
  std::map<SurfacePosition, Activity> activities_Rn_P2;

  double total_Rn_Act_P1;
  double avg_sfoil_act_P1, avg_sfoil_act_P1_err;
  double total_Rn_Act_P2;
  double avg_sfoil_act_P2, avg_sfoil_act_P2_err;
  SFoilSide* foilSideChecker_;
  SectorData* sectorfinder_;
  TRandom3* RandomNumGen;
};

#endif
