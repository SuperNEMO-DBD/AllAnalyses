//
//  SectorData.cpp
//
//  Created by Stefano Torre on 01/03/12.
//

#include <iostream>
#include "NemoUtils/SectorData.h"
#define pi 3.14159265358979312

SectorData::SectorData() {
    FoilData foil;
    
    foil = FoilData(SourceType::MoMet, 
                    "mo", "Mo Metallic", 2545.17, 100, 2479.0); add(foil);
    foil = FoilData(SourceType::MoCom, 
                    "mo", "Mo Composite",5578.29, 100, 4435.0); add(foil);
    // Single selenium sample changed to SeOld and SeNew - JEM 15/11/12.
    foil = FoilData(SourceType::SeOld, 
                    "se", "Selenium Old",518.45,  82, 425.05);  add(foil);
    foil = FoilData(SourceType::SeNew, 
                    "se", "Selenium New",608.62,  82, 507.34);  add(foil);
    foil = FoilData(SourceType::Cd,    
                    "cd", "Cadmium",   491.18, 116, 405.0);     add(foil);
    foil = FoilData(SourceType::Nd,    
                    "nd", "Neodinium",  56.68, 150,  37.0);     add(foil);
    foil = FoilData(SourceType::Ca,    
                    "ca", "Calcium",    18.52,  48,  6.99);     add(foil);
    foil = FoilData(SourceType::Zr,    
                    "zr", "Zirconium",  26.51,  96,   9.4);     add(foil);
    foil = FoilData(SourceType::Te130, 
                    "te", "Tellurium", 756.38, 130, 453.9);     add(foil);
    foil = FoilData(SourceType::TeNat, 
                    "ten","Te Natural",893.62, 130, 166.34);    add(foil);
    foil = FoilData(SourceType::Cu,    
                    "cu", "Copper",     620.8,  50, 620.8);     add(foil); 
    
}

SectorData::~SectorData() {
    foils_.clear();
}

double SectorData::sectorNumber(CLHEP::Hep3Vector point) const {
  // first get the angle w.r.t. the x axis:
  double phi = sectorPhi(point);

  double sectorValue = phi * 20/(2*pi);
  return sectorValue;
}

double SectorData::sectorNumber(double x, double y, double z) const {
    return sectorNumber(CLHEP::Hep3Vector(x,y,z));
}

double SectorData::sectorPhi(CLHEP::Hep3Vector point) const {

    double phi = atan2(point.y(), point.x());
    phi = (phi < 0) ? phi+2*pi : phi;
    return phi;
}

SourceType SectorData::sourceOfVertex(CLHEP::Hep3Vector point) const {
    
    if (point == CLHEP::Hep3Vector(0,0,0)) return SourceType::None;
    
    double sectorValue = sectorNumber(point);

    //check calibration tube
    if ((sectorValue - (int)sectorValue) < 0.07) {
        return SourceType::Calib;
    }
    
    //mo metal 
	if ((sectorValue >= 1.      &&  sectorValue <= 1.736) || 
        (sectorValue >  2.      &&  sectorValue <  5.) ||
        (sectorValue >= 5.      &&  sectorValue <= 5.333)) { 
        return SourceType::MoMet;
	}
    
	//mo composit
    if ((sectorValue >= 1.736   &&  sectorValue <= 2) ||
        (sectorValue >= 5.333   &&  sectorValue <= 5.736) ||
        (sectorValue >= 10.     &&  sectorValue <= 17.)){
        return SourceType::MoCom;
	}
    
	//Se 82 foils
  	if ((sectorValue >=7.       &&  sectorValue <= 8.0) ||
        (sectorValue >=8.       &&  sectorValue <= 8.2 && point.z() <= -38.6)) {
	    //new se foils
	    return SourceType::SeNew;
    }
  	if ((sectorValue >= 6.      &&  sectorValue <= 7.) ||
        (sectorValue >= 8.      &&  sectorValue <= 8.2 && point.z() >= -38.6) ||
        (sectorValue >= 8.2     &&  sectorValue <= 8.33)) {
        //old se from NEMO 2
        return SourceType::SeOld;
	}
    
	// Cd 116 foils
	if (sectorValue >=  18.     &&  sectorValue <= 19.) {
        return SourceType::Cd;
	}
    
	// Nd 150 foils
	if (sectorValue >=  5.7371  &&  sectorValue <= 5.8706) {
        return SourceType::Nd;
	}
    
    // Sector 5
	if (sectorValue >=  5.8717  &&  sectorValue <= 6.0009) {
        // Ca-48
        if (point.z()   <= -5.  &&  point.z() >= -65.) {
            return SourceType::Ca;
        }
        // Zr-96
        if (point.z()   <= 115. &&  point.z() >=   2.) {
            return SourceType::Zr;
        }        
	}
    
	//Te-130
	if ((sectorValue    >=  9.  &&  sectorValue <=  10.) ||
        (sectorValue    >=  17. &&  sectorValue <=  18.)) { 
        return SourceType::Te130;
    }
    
	//Te nat
	if ((sectorValue    >=  19. &&  sectorValue <=  20.) ||
        (sectorValue    >= 8.33 &&  sectorValue <=   9.)) {
        return SourceType::TeNat;
	}
    
	//Cu
	if (sectorValue     >=   0. &&  sectorValue <=  1.) {
        return SourceType::Cu;
	}
    
	return SourceType::Error;
}

SourceType SectorData::sourceOfVertex(double x, double y, double z) const {
    return sourceOfVertex(CLHEP::Hep3Vector(x,y,z));
}

void SectorData::add(FoilData &aFoil) {
    if (foils_.find(aFoil.sourceId) == foils_.end()) {
        foils_.insert(std::pair<SourceType, FoilData>
                      (aFoil.sourceId, aFoil));
    }
}

