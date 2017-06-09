//
//  RadonWeight.h
//
//  Created by James Mott on 09/10/12.
//

#ifndef RADONWEIGHT_H_
#define RADONWEIGHT_H_
#include "CLHEP/Vector/ThreeVector.h"
#include "NemoUtils/SectorData.h"
#include "TRandom3.h"
#include "NemoMods/RunStatusController.h"
#include <map>

struct WirePosition {
  public:
  WirePosition() :
    side(-1), sector(-1), layer(-1){
  }
    
  WirePosition(int aSide, int aSector, int aLayer) :
    side(aSide), sector(aSector), layer(aLayer){        
  }
    
  WirePosition(const WirePosition &obj) :
    side(obj.side), sector(obj.sector), layer(obj.layer){
  }
    
  WirePosition &operator = (const WirePosition &obj) {
    if (this != &obj) {
      side    = obj.side;
      sector  = obj.sector;
      layer   = obj.layer;
    }
    return (*this);
  }

  bool operator<(const WirePosition &obj) const {
    if (side < obj.side){
      return true;
    }
    else if (side == obj.side){
      if(sector < obj.sector){
	return true;
      }
      else if(sector == obj.sector){
	if(layer < obj.layer){
	  return true;
	}
      }
    }
    return false;
  }

  int side;
  int sector;
  int layer;
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



class RadonWeight {
public:
    RadonWeight();
    ~RadonWeight();
    WirePosition getWirePosition(CLHEP::Hep3Vector vertex) const;
    WirePosition getWirePosition(double x, double y, double z) const;
    double       getRadonWeight(CLHEP::Hep3Vector trueVertex) const;
    double       getBi210Weight(CLHEP::Hep3Vector trueVertex) const;
    
private:
    void add_Rn_P1(WirePosition &aWirePosition, Activity &anActivity);
    void add_Rn_P2(WirePosition &aWirePosition, Activity &anActivity);
    void add_Bi210_P1(WirePosition &aWirePosition, Activity &anActivity);
    void add_Bi210_P2(WirePosition &aWirePosition, Activity &anActivity);
    std::map<WirePosition, Activity> activities_Rn_P1;
    std::map<WirePosition, Activity> activities_Rn_P2;
    std::map<WirePosition, Activity> activities_Bi210_P1;
    std::map<WirePosition, Activity> activities_Bi210_P2;
    double total_Rn_Act_P1;
    double total_Rn_Act_P2;
    double total_Bi210_Act_P1;
    double total_Bi210_Act_P2;
    TRandom3* RandomNumGen;

};

#endif
