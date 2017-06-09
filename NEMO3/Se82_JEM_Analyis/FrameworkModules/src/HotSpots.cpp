//
//  HotSpots.cpp
//
//  Created by James Mott on 14/11/12.
//
//  HotSpots defined for selenium foils and assigned by looking in the
//  1e channel
//

#include <iostream>
#include "JEM_Analysis/HotSpots.h"
#include "NemoUtils/SectorData.h"

HotSpots::HotSpots() {

  // Fill in details of HotSpots to arrays in constructor.
  // Base each HotSpot on an ellipse in Z and sector number.
  // Define centre and semi-major and semi-minor axes here:

  // Calibration tube in sector 6
  centre_Z[0]  = -91.0;   centre_Sect[0]  = 6.03;   semiAxis_Z[0]  = 19.0;  semiAxis_Sect[0]  = 0.06;
  centre_Z[1]  = -10.0;   centre_Sect[1]  = 6.03;   semiAxis_Z[1]  = 10.0;  semiAxis_Sect[1]  = 0.06;
  centre_Z[2]  =  7.0;    centre_Sect[2]  = 6.03;   semiAxis_Z[2]  = 6.0;   semiAxis_Sect[2]  = 0.06;
  centre_Z[3]  =  80.0;   centre_Sect[3]  = 6.03;   semiAxis_Z[3]  = 9.0;   semiAxis_Sect[3]  = 0.06;
  centre_Z[4]  =  97.0;   centre_Sect[4]  = 6.03;   semiAxis_Z[4]  = 7.5;   semiAxis_Sect[4]  = 0.06;

  // Calibration tube in sector 7
  centre_Z[5]  = -101.0;  centre_Sect[5]  = 7.045;  semiAxis_Z[5]  = 7.5;   semiAxis_Sect[5]  = 0.06;
  centre_Z[6]  = -90.0;   centre_Sect[6]  = 7.045;  semiAxis_Z[6]  = 4.0;   semiAxis_Sect[6]  = 0.06;
  centre_Z[7]  = -80.0;   centre_Sect[7]  = 7.045;  semiAxis_Z[7]  = 6.0;   semiAxis_Sect[7]  = 0.06;
  centre_Z[8]  = -63.0;   centre_Sect[8]  = 7.045;  semiAxis_Z[8]  = 4.5;   semiAxis_Sect[8]  = 0.06;
  centre_Z[9]  = -10.0;   centre_Sect[9]  = 7.05;   semiAxis_Z[9]  = 12.0;  semiAxis_Sect[9]  = 0.07;
  centre_Z[10] =  8.0;    centre_Sect[10] = 7.05;   semiAxis_Z[10] = 7.0;   semiAxis_Sect[10] = 0.06;
  centre_Z[11] =  77.0;   centre_Sect[11] = 7.04;   semiAxis_Z[11] = 16.0;  semiAxis_Sect[11] = 0.07;
  centre_Z[12] =  99.0;   centre_Sect[12] = 7.04;   semiAxis_Z[12] = 8.0;   semiAxis_Sect[12] = 0.06;

  // Calibration tube in sector 8
  centre_Z[13] = -103.0;  centre_Sect[13] = 8.045;  semiAxis_Z[13] = 7.0;   semiAxis_Sect[13] = 0.06;
  centre_Z[14] = -80.0;   centre_Sect[14] = 8.045;  semiAxis_Z[14] = 4.0;   semiAxis_Sect[14] = 0.06;
  centre_Z[15] = -15.0;   centre_Sect[15] = 8.050;  semiAxis_Z[15] = 10.0;  semiAxis_Sect[15] = 0.07;
  centre_Z[16] =  10.0;   centre_Sect[16] = 8.025;  semiAxis_Z[16] = 5.0;   semiAxis_Sect[16] = 0.06;
  centre_Z[17] =  75.0;   centre_Sect[17] = 8.045;  semiAxis_Z[17] = 10.0;  semiAxis_Sect[17] = 0.06;
  centre_Z[18] =  101.5;  centre_Sect[18] = 8.045;  semiAxis_Z[18] = 6.0;   semiAxis_Sect[18] = 0.06;
  centre_Z[19] =  110.0;  centre_Sect[19] = 8.045;  semiAxis_Z[19] = 2.5;   semiAxis_Sect[19] = 0.06;

  // HotSpots within foils
  centre_Z[20] = -45.5;   centre_Sect[20] = 6.595;  semiAxis_Z[20] = 1.75;  semiAxis_Sect[20] = 0.015;
  centre_Z[21] = -77.0;   centre_Sect[21] = 6.870;  semiAxis_Z[21] = 2.0;   semiAxis_Sect[21] = 0.015;
  centre_Z[22] = -100.5;  centre_Sect[22] = 7.430;  semiAxis_Z[22] = 1.5;   semiAxis_Sect[22] = 0.015;
  centre_Z[23] =  45.5;   centre_Sect[23] = 7.585;  semiAxis_Z[23] = 1.5;   semiAxis_Sect[23] = 0.015;
  centre_Z[24] = -95.5;   centre_Sect[24] = 7.545;  semiAxis_Z[24] = 1.0;   semiAxis_Sect[24] = 0.015;
  centre_Z[25] =  103.5;  centre_Sect[25] = 7.395;  semiAxis_Z[25] = 1.0;   semiAxis_Sect[25] = 0.015;

}

HotSpots::~HotSpots() {

}

bool HotSpots::InHotSpot(CLHEP::Hep3Vector vertex) const {

  SectorData SectorFinder;
  double Z = vertex.z();
  double Sect = SectorFinder.sectorNumber(vertex);

  // Check for HotSpots as defined in constructor
  for (int i = 0; i < 26; i++){
    if(pow((Sect-centre_Sect[i])/semiAxis_Sect[i],2) + pow((Z-centre_Z[i])/semiAxis_Z[i],2) < 1){ return true; }
  }

  return false;

}

