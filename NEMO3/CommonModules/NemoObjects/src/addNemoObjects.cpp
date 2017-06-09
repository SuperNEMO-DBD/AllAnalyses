//
//  addNemoObjects.cpp
//
//  Created by Stefano Torre on 29/10/11.
//

#include "NemoObjects/addNemoObjects.h"
#include "NemoObjects/N3CalorimeterHitColl.h"
#include "NemoObjects/N3GeigerHitColl.h"
#include "NemoObjects/N3TrackColl.h"
#include "NemoObjects/NemorHeader.h"
#include "NemoObjects/CalibCaloHitColl.h"
#include "NemoObjects/ElectronColl.h"      
#include "NemoObjects/GammaColl.h"  
#include "NemoObjects/AlphaColl.h"  
#include "NemoObjects/GammaClusterColl.h"  
#include "NemoObjects/GammaCluster.h"
#include "NemoObjects/GammaTrack.h"  
#include "NemoObjects/N3TrueCalorimeterHitColl.h" 
#include "NemoObjects/N3TrueGeigerHitColl.h"
#include "NemoObjects/N3TrueParticleColl.h"
#include "NemoObjects/N3TrueVertexColl.h"

void addNemoObjects() {
  N3CalorimeterHitColl::Class_Name();
  N3GeigerHitColl::Class_Name();
  N3TrackColl::Class_Name();
  NemorHeader::Class_Name();
  CalibCaloHitColl::Class_Name();  
  ElectronColl::Class_Name();      
  GammaColl::Class_Name();  
  AlphaColl::Class_Name();  
  GammaClusterColl::Class_Name();  
  GammaCluster::Class_Name();  
  GammaTrack::Class_Name();  
  N3TrueCalorimeterHitColl::Class_Name(); 
  N3TrueGeigerHitColl::Class_Name();
  N3TrueParticleColl::Class_Name();
  N3TrueVertexColl::Class_Name();
}
