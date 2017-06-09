//
//  SFoilSide.h
//
//  Created by James Mott on 29/01/13.
//
//  24/4/2013 - Stefano Torre 
//  adding the position of hte strips as defined in the NEMO3 geometry files  

#ifndef SFOILSIDE_H_
#define SFOILSIDE_H_
#include "CLHEP/Vector/ThreeVector.h"
#include "NemoUtils/SectorData.h"
#include "TMath.h"

struct FoilStrip {
  FoilStrip(int a, int b, CLHEP::Hep3Vector c, double m, double d, double e, double f, double g, double h, double i, double l) {
    id = a;

    material = b;

    center = c;
    angle = m;

    low_vtx_num = e;
    high_vtx_num = f;

    low_z = g;
    high_z = h;

    inn_radius = i;
    out_radius = l;

    radius = d;
  }
  int id;
  int material;
  CLHEP::Hep3Vector center;
  double radius;
  double angle;
  double low_vtx_num;
  double high_vtx_num;
  double low_z;
  double high_z;
  double inn_radius;
  double out_radius;
};

class SFoilSide {
public:
    SFoilSide();
    ~SFoilSide();
    int    getSFoilSide(CLHEP::Hep3Vector trueVertex) const;
    double getSFoilPerpDist(CLHEP::Hep3Vector trueVertex) const;
 private:
    double getSFoilPerpDistFromApproximation(CLHEP::Hep3Vector trueVertex) const;
    double getSFoilPerpDistFromGeom(CLHEP::Hep3Vector trueVertex) const;
    std::map<int, std::vector<FoilStrip> > strips_dictionary;
    void   createStripsDictionary();
    SectorData sectorfinder_;
  
};

#endif
