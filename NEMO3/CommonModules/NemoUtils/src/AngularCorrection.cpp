//
//  AngularCorrection.cpp
//
//  Created by James Mott on 08/10/12.
//
//  Correction factors were derived using Bi207 calibration sources and
//  calculated by Roger Arnold.

#include <iostream>
#include "NemoUtils/AngularCorrection.h"

AngularCorrection::AngularCorrection() {

  CorrFactor[0]  = 1.067043;	CorrFactor_Err[0]  = 0.006005325;
  CorrFactor[1]  = 1.069942;	CorrFactor_Err[1]  = 0.006233131; 
  CorrFactor[2]  = 1.055427;	CorrFactor_Err[2]  = 0.006378884; 
  CorrFactor[3]  = 1.055308;	CorrFactor_Err[3]  = 0.006604146; 
  CorrFactor[4]  = 1.074487;	CorrFactor_Err[4]  = 0.006960622; 
  CorrFactor[5]  = 1.063359;	CorrFactor_Err[5]  = 0.007149729; 
  CorrFactor[6]  = 1.050824;	CorrFactor_Err[6]  = 0.007279258; 
  CorrFactor[7]  = 1.035184;	CorrFactor_Err[7]  = 0.007404353; 
  CorrFactor[8]  = 1.079661;	CorrFactor_Err[8]  = 0.008020354; 
  CorrFactor[9]  = 1.068853;	CorrFactor_Err[9]  = 0.008216612; 
  CorrFactor[10] = 1.038082;	CorrFactor_Err[10] = 0.008253378; 
  CorrFactor[11] = 1.062424;	CorrFactor_Err[11] = 0.008745526; 
  CorrFactor[12] = 1.071192;	CorrFactor_Err[12] = 0.009112603; 
  CorrFactor[13] = 1.063575;	CorrFactor_Err[13] = 0.009339049; 
  CorrFactor[14] = 1.073323;	CorrFactor_Err[14] = 0.009805323; 
  CorrFactor[15] = 1.051867;	CorrFactor_Err[15] = 0.009856332;
  CorrFactor[16] = 1.044192;	CorrFactor_Err[16] = 0.01004235;  
  CorrFactor[17] = 1.038620;	CorrFactor_Err[17] = 0.01025492;  
  CorrFactor[18] = 1.020515;	CorrFactor_Err[18] = 0.01036705;  
  CorrFactor[19] = 1.045640;	CorrFactor_Err[19] = 0.01085948;  
  CorrFactor[20] = 1.023086;	CorrFactor_Err[20] = 0.01088298;  
  CorrFactor[21] = 1.022891;	CorrFactor_Err[21] = 0.01112025;  
  CorrFactor[22] = 1.003313;	CorrFactor_Err[22] = 0.01107003;  
  CorrFactor[23] = 0.9981433;	CorrFactor_Err[23] = 0.01103234;  
  CorrFactor[24] = 0.945641;	CorrFactor_Err[24] = 0.01046692;  
  CorrFactor[25] = 0.957726;	CorrFactor_Err[25] = 0.01071551;  
  CorrFactor[26] = 0.9681522;	CorrFactor_Err[26] = 0.01092401;  
  CorrFactor[27] = 0.9732051;	CorrFactor_Err[27] = 0.01083679;  
  CorrFactor[28] = 0.9408215;	CorrFactor_Err[28] = 0.01030189;  
  CorrFactor[29] = 0.9545705;	CorrFactor_Err[29] = 0.01032147; 
  CorrFactor[30] = 0.9280768;	CorrFactor_Err[30] = 0.009729304; 
  CorrFactor[31] = 0.9262086;	CorrFactor_Err[31] = 0.009528505; 
  CorrFactor[32] = 0.9103083;	CorrFactor_Err[32] = 0.009131829; 
  CorrFactor[33] = 0.9144621;	CorrFactor_Err[33] = 0.008928425; 
  CorrFactor[34] = 0.9115762;	CorrFactor_Err[34] = 0.008671014; 
  CorrFactor[35] = 0.9043642;	CorrFactor_Err[35] = 0.008368377; 
  CorrFactor[36] = 0.9291837;	CorrFactor_Err[36] = 0.008401383; 
  CorrFactor[37] = 0.9150791;	CorrFactor_Err[37] = 0.008079834; 
  CorrFactor[38] = 0.9181526;	CorrFactor_Err[38] = 0.007866745; 
  CorrFactor[39] = 0.9035271;	CorrFactor_Err[39] = 0.007577338; 
  CorrFactor[40] = 0.9263924;	CorrFactor_Err[40] = 0.007563424; 
  CorrFactor[41] = 0.9307034;	CorrFactor_Err[41] = 0.007441957; 
  CorrFactor[42] = 0.9122871;	CorrFactor_Err[42] = 0.007133725; 
  CorrFactor[43] = 0.9222511;	CorrFactor_Err[43] = 0.007080418; 
  CorrFactor[44] = 0.9166086;	CorrFactor_Err[44] = 0.006912713; 
  CorrFactor[45] = 0.9255552;	CorrFactor_Err[45] = 0.007050755; 
  CorrFactor[46] = 0.9359238;	CorrFactor_Err[46] = 0.007374856; 
  CorrFactor[47] = 0.9580276;	CorrFactor_Err[47] = 0.008226329; 
  CorrFactor[48] = 1.055162;	CorrFactor_Err[48] = 0.01097921;  
  CorrFactor[49] = 1.234777;	CorrFactor_Err[49] = 0.02077445;  

  RandomNumGen = new TRandom3(12345);
}

AngularCorrection::~AngularCorrection() {

}

double AngularCorrection::CosWeight(double cosine) const {

  // Find array entry to get correction - corrections go between
  // -1 and 1 and are divided into 50 bins
  int entry = (int)((100*cosine / 4) + 25);

  // Then use this entry to float a factor around the mean using provided error
  return RandomNumGen->Gaus(CorrFactor[entry],CorrFactor_Err[entry]);

}

