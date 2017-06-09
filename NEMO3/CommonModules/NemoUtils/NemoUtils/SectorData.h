//
//  FoilData.h
//
//  Created by Stefano Torre on 01/03/12.
//

#ifndef FOILDATA_H_
#define FOILDATA_H_
#include "NemoUtils/SourceType.h"
#include "CLHEP/Vector/ThreeVector.h"
#include <string>
#include <map>

struct FoilData {
public:
    FoilData() :
    sourceId(SourceType::Error), nuclide(""), foilName(""), 
    mass(0), atomicNumber(0), isotopeMass(0){
    }
    
    FoilData(SourceType aType, 
             std::string aNuclide, std::string aFoil,
             double aMass, int aAtomicNumber, double aIsotopeMass) :
    sourceId(aType), nuclide(aNuclide), foilName(aFoil), mass(aMass),
    atomicNumber(aAtomicNumber), isotopeMass(aIsotopeMass) {        
    }
    
    FoilData(const FoilData& obj) :
    sourceId(obj.sourceId), nuclide(obj.nuclide), foilName(obj.foilName),
    mass(obj.mass), atomicNumber(obj.atomicNumber), 
    isotopeMass(obj.isotopeMass){
    }
    
    FoilData& operator = (const FoilData& obj) {
        if (this != &obj) {
            sourceId    = obj.sourceId;
            nuclide     = obj.nuclide;
            foilName    = obj.foilName;
            mass        = obj.mass;
            atomicNumber= obj.atomicNumber;
            isotopeMass = obj.isotopeMass;
        }
        return (*this);
    }

    SourceType  sourceId;
    std::string nuclide;
    std::string foilName;
    double      mass;
    int         atomicNumber;
    double      isotopeMass;
};

class SectorData {
public:
    SectorData();
    ~SectorData();
    double sectorNumber(CLHEP::Hep3Vector point) const;
    double sectorNumber(double x, double y, double z) const;
    double sectorPhi(CLHEP::Hep3Vector point) const;
    SourceType sourceOfVertex(CLHEP::Hep3Vector point) const;
    SourceType sourceOfVertex(double x, double y, double z) const;
    
private:
    void add(FoilData& aFoil);
    std::map<SourceType, FoilData> foils_;
//  "mo","mo","se","cd","nd","ca",
//  "zr","te","ten","cu","calib tube"
//  "mo metal","mo composit","se composit","cd metal","nd","ca",
//    "zr","te-130 enriched","te natural","copper","calib tube"
//    
//    // Source mass [g] and isotope  mass by source number.
//  2545.17, 5578.29, 1127.07, 491.18, 56.68, 18.52,   
//  26.51  ,  756.38,  893.62,  620.8, 0.1
//    Float_t Amass[11]={100,100,82,116,150,48,96,130,130,50,50};
//    Float_t Snmass[11]={2479.,4435.,934.6,405.,37.,6.99,9.4,453.9,166.34,620.8,0.1};

};

#endif
