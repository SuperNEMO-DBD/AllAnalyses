//
//  AlphaFinder.cpp
//
//  Created by Stefano Torre on 22/05/12.
//  Heavily modified by James Mott on 15/01/13.
//

// Nemo analysis modules and objects
#include "NemoMods/AlphaFinder.h"
#include "NemoObjects/CalibCaloHitColl.h"
#include "NemoObjects/NemorHeader.h"

// Hereward modules and objects
#include "Hereward/SuperNemoData/EventHeader.h"
#include "Hereward/SuperNemoProcessing/Constants.h"

// STL
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>

// Root classes
#include <TF1.h>
#include <TGraphErrors.h>

//-------------------------------------------------------------------------
// Constructor
//-------------------------------------------------------------------------
AlphaFinder::AlphaFinder(const std::string theName, 
			 const std::string theDescription) :
  AppModule(theName, theDescription),
  maxTimeBetweenHits_(2100),
  maxDistBetweenHits_(40),
  minTimeOfDelayedHit_(4000),
  maxTimeOfDelayedHit_(650000),
  minTimeOf1DelayedHit_(110000),
  minTimeOf2DelayedHits_(50000),
  minTimeOf3DelayedHits_(20000),
  minTimeOf4DelayedHits_(4000),
  minClusterDistSearch_(10),
  minClusterDistXYSearch_(5),
  minClusterDistZSearch_(10),
  minClusterDistVeto_(30),
  minClusterDistXYVeto_(25),
  minClusterDistZVeto_(30),
  useVetoCriteria_(true){
}

AlphaFinder::~AlphaFinder() {
}

//-------------------------------------------------------------------------
// Operations
//-------------------------------------------------------------------------
AppResult AlphaFinder::beginJob(AppEvent *aJob) {
  return AppResult::OK;
}

AppResult AlphaFinder::beginRun(AppEvent *aRun) {
  return AppResult::OK;
}

bool delayedHitTimeComp(AlphaFinder::DelayedTime i, AlphaFinder::DelayedTime j) {
  bool comparison;
  if(i.z == 0){
    if(j.z == 0){
      comparison = (i.time < j.time);
    } else {
      comparison = false;
    }
  } else {
    if(j.z == 0){
      comparison = true;
    } else {
      comparison = (i.time < j.time);
    }
  }
  return comparison;
}

AppResult AlphaFinder::makeClusters(AppEvent* anEvent) {

  delayedHitTimes_.clear();
  delayedHitIds_.clear();
  delayedClusters_.clear();

  StorableObject::SelectByClassName cName("EventHeader");
  EventRecord::ConstIterator eventHeader_ci(anEvent, cName);    
  if (!eventHeader_ci.is_valid()) {
    std::cout << "Error Accessing the EventHeader" << std::endl;
    anEvent->listObjects();
    return AppResult::ERROR;
  } 
  EventHeader_ch eventHeader(eventHeader_ci);

  if (!N3TrackColl::find(anEvent, theTrackColl_)) {        
    std::cout << "-- AlphaFinder - Tracks not found" << std::endl;
    return AppResult::ERROR;        
  }
    
  if (!N3GeigerHitColl::find(anEvent, theGgColl_)) {
    std::cout << "-- AlphaFinder - Geiger hits not found" << std::endl;
    return AppResult::ERROR;
  }

  // Find delayed GG hits and put them in vector containing hitID, time and z
  for (int i = 0; i < theGgColl_->contents().size(); i++) {
    if ( theGgColl_->contents().at(i).isDelayed() ) {
      DelayedTime delayedHitTemp(i, theGgColl_->contents().at(i).alphaTime(), theGgColl_->contents().at(i).z());
      delayedHitTimes_.push_back(delayedHitTemp);
    }
  }

  // If there are more than 150 delayed hits, don't run AlphaFinder as there's likely
  // lots of noise in the detector which means it's unlikely to work properly!
  if(delayedHitTimes_.size() > 150){
    std::cout << "-- AlphaFinder - More than 150 delayed hits in event. Skipping AlphaFinder..." << std::endl;
    return AppResult::OK;        
  }

  // Sort vector of delayed hit IDs, times and z into time order with the hits with no z information at the 
  // end.  This means if there's a hit with z information it will preferentially be the basis on which to form
  // the cluster even if it's later in time.  Once sorted, replace with vector containing IDs only
  sort (delayedHitTimes_.begin(), delayedHitTimes_.end(), delayedHitTimeComp);
  for (int i = 0; i < delayedHitTimes_.size(); i++) {
    delayedHitIds_.push_back(delayedHitTimes_.at(i).id);
  }

  // Now look for clusters amongst the delayed geiger hits
  std::vector<int>::iterator delayedHitIter = delayedHitIds_.begin();
  while (delayedHitIter != delayedHitIds_.end()) {

    N3GeigerHit delayedHit = theGgColl_->contents().at((*delayedHitIter));
    double delayedHitTime = delayedHit.alphaTime();
    
    // Ask for the time of the hit to be > 4 us to remove a large part of the refiring
    // cells. This will be more stringently applied for clusters with < 4 hits further on.
    // Also ask that time is less than 650 us and the majority of Po-214 has decay by then.
    if (delayedHitTime > minTimeOfDelayedHit_ and delayedHitTime < maxTimeOfDelayedHit_) {

      bool clusterFound = false;

      std::vector<std::vector<int> >::iterator clusterIter = delayedClusters_.begin();

      // Loop over the clusters
      while (clusterIter != delayedClusters_.end() && !clusterFound) {

	// Get hold of relevant information for two hits for cluster finding
	N3GeigerHit clusterHit = theGgColl_->contents().at((*(clusterIter->begin())));

	CLHEP::Hep3Vector clusterHitPosition(clusterHit.anodePosition().x(), clusterHit.anodePosition().y(), clusterHit.z());
	CLHEP::Hep3Vector delayedHitPosition(delayedHit.anodePosition().x(), delayedHit.anodePosition().y(), delayedHit.z());

	double timeToClusterHit     = delayedHitTime - clusterHit.alphaTime();
	double distanceToClusterHit = (delayedHitPosition - clusterHitPosition).mag();

	// If there's no z information about hit or cluster, things get complicated and we must recalculate time and distance.
	// Calculate distance in XY only.  Calculate times against all in cluster since these won't be in time order 
	// and you don't want to add a hit that makes the overall spread of the cluster greater than maxTimeBetweenHits_
	if(clusterHit.z() == 0 or delayedHit.z() == 0){
	  distanceToClusterHit = sqrt(pow(delayedHitPosition.x()-clusterHitPosition.x(),2)
				      + pow(delayedHitPosition.y()-clusterHitPosition.y(),2));
	  timeToClusterHit = 0;
	  std::vector<int>::iterator clusterHitIter = clusterIter->begin();
	  while (clusterHitIter != clusterIter->end()) {
	    double clusterHitTime = theGgColl_->contents().at((*clusterHitIter)).alphaTime();
	    if(fabs(delayedHitTime-clusterHitTime) > timeToClusterHit){
	      timeToClusterHit = fabs(delayedHitTime-clusterHitTime);
	    }
	    clusterHitIter++;
	  }
	}

	// Check if the hit is in time, on the same side and near the cluster first hit.
	// Add it to cluster if it passes the criteria.
	if (timeToClusterHit < maxTimeBetweenHits_ and distanceToClusterHit < maxDistBetweenHits_ 
	    and clusterHit.side() == delayedHit.side()) {
	  clusterFound = true;
	  clusterIter->push_back((*delayedHitIter));
	}
	clusterIter++;      
      }	

      // If no cluster is found for hit, start a new one
      if (!clusterFound) {
	std::vector<int> newCluster;
	newCluster.push_back((*delayedHitIter));
	delayedClusters_.push_back(newCluster);
      }
      
    }

    delayedHitIter++;
  }

//   // Output to check clustering, if required.
//   std::cout << std::endl;
//   std::cout << "Delayed Hits in event:" << std::endl;
//   for (int i = 0; i < delayedHitTimes_.size(); i++) {
//     std::cout << "id = " << delayedHitTimes_.at(i).id << "\tTime = " << delayedHitTimes_.at(i).time 
// 	      << "\tz = " << delayedHitTimes_.at(i).z << "\t(x,y) = (" << theGgColl_->contents().at(delayedHitTimes_.at(i).id).anodePosition().x() 
// 	      << "," << theGgColl_->contents().at(delayedHitTimes_.at(i).id).anodePosition().y()
// 	      << ")\tCathodes Sum = " << theGgColl_->contents().at(delayedHitTimes_.at(i).id).bottomTdcContent()
//                                          + theGgColl_->contents().at(delayedHitTimes_.at(i).id).topTdcContent() << std::endl;
//   }
//   std::cout << std::endl;
//   std::vector<std::vector<int> >::iterator clusterIter = delayedClusters_.begin();
//   int clusternum = 1;
//   while (clusterIter != delayedClusters_.end()) {
//     std::cout << "Cluster " << clusternum << " Hit Ids..." << std::endl;
//     std::vector<int>::iterator clusterHitIter = clusterIter->begin();
//     while (clusterHitIter != clusterIter->end()) {
//       std::cout << (*clusterHitIter) << "\t";
//       clusterHitIter++;
//     }
//     clusterIter++;
//     clusternum++;
//     std::cout << std::endl;
//   }

  return AppResult::OK;
}

void AlphaFinder::fitAlphaTrack(std::vector<double> x, std::vector<double>y, double x_err, double y_err,
				double &A, double &B){

  double x_arr[x.size()] , y_arr[y.size()], x_err_arr[x.size()], y_err_arr[y.size()];
  for(int i = 0; i < x.size(); i++){
    x_arr[i] = x.at(i);
    y_arr[i] = y.at(i);
    x_err_arr[i] = x_err;
    y_err_arr[i] = y_err;
  }

  if(x.size() < 2){
    A = 0;
    B = 0;
  } else if (x.size() == 2){
    if(x_arr[0] > x_arr[1]){
      A = (y_arr[0] - y_arr[1])/(x_arr[0] - x_arr[1]);
      B = y_arr[0] - A*x_arr[0];
    } else {
      A = (y_arr[1] - y_arr[0])/(x_arr[1] - x_arr[0]);
      B = y_arr[0] - A*x_arr[0];
    }
  } else {
    TGraphErrors* tg = new TGraphErrors(x.size(),x_arr,y_arr,x_err_arr,y_err_arr);
    TF1* f = new TF1("f","pol1",-210,210);
    tg->Fit(f,"NQ");
    A = f->GetParameter(1);
    B = f->GetParameter(0);
    delete tg;
    delete f;
  }

  return;

}

CLHEP::Hep3Vector AlphaFinder::findAlphaFoilVertex(double x, double y, double z, 
						   double A_xy, double B_xy, double A_xz, double B_xz){
  double r = 155.0;
  double vx,vy,vz;

  // Calculate intersection of line with foil - this is the discriminator of quadratic equation
  double Disc = 4*A_xy*A_xy*B_xy*B_xy - 4*(1+A_xy*A_xy)*(B_xy*B_xy - r*r);

  // If it intersects then find intersection that's closest to the point supplied (x,y,z).
  if(Disc >= 0){
    double x1 = (-2*A_xy*B_xy + sqrt(Disc))/(2*(1+A_xy*A_xy));
    double y1 = A_xy*x1 + B_xy;
    double z1 = A_xz*x1 + B_xz;
    double d1 = sqrt(pow(x1-x,2)+pow(y1-y,2)+pow(z1-z,2));
    double x2 = (-2*A_xy*B_xy - sqrt(Disc))/(2*(1+A_xy*A_xy));
    double y2 = A_xy*x2 + B_xy;
    double z2 = A_xz*x2 + B_xz;
    double d2 = sqrt(pow(x2-x,2)+pow(y2-y,2)+pow(z2-z,2));

    if(d1 < d2){
      vx = x1;
      vy = y1;
      vz = z1;
    } else {
      vx = x2;
      vy = y2;
      vz = z2;
    }

  } else {
    vx = 0;
    vy = 0;
    vz = 0;
  }
  return CLHEP::Hep3Vector(vx,vy,vz);
}

bool AlphaFinder::goodAlphaCandidate(Alpha& alpha) {

  // This member function fills all the alpha properties from the delayed clusters
  // and decides whether it fulfills the criteria to be considered a good alpha candidate.

  // Set distance parameters to use when deciding on whether it's an alpha based on useVetoCriteria flag
  double minClusterDist_, minClusterDistXY_, minClusterDistZ_;
  if(useVetoCriteria_){
    minClusterDist_        =  minClusterDistVeto_;
    minClusterDistXY_      =  minClusterDistXYVeto_;
    minClusterDistZ_       =  minClusterDistZVeto_;
  } else {
    minClusterDist_        =  minClusterDistSearch_;
    minClusterDistXY_      =  minClusterDistXYSearch_;
    minClusterDistZ_       =  minClusterDistZSearch_;
  }

  // If there's no track, then we've got no way to distinguish alphas
  // from detector noise.  This swamps any measurement, so we must require tracks.
  N3TrackColl::N3TrackList trackList = theTrackColl_->contents();
  if(trackList.size() == 0){return false;}

  // Initialise parameters that will be checked against in search for close clusters.
  int    trackId = -1;
  double minTrackHitDist  = 1e6;
  double minTrackHitDistXY = 1e6;
  double minTrackHitDistZ  = 1e6;
  int    minTrackHitId = -1;
  int    minTrackHitDelayedId = -1;
  double minTrackVertexDist   = 1e6;
  double minTrackVertexDistXY = 1e6;
  double minTrackVertexDistZ  = 1e6;
  int    minTrackVertexDelayedId = -1;

  // Loop over all hits in the cluster and find the closest hit to either first or
  // last hit in one of the prompt tracks.
  for(int i = 0; i < alpha.geigerHitList()->size(); i++) {
    N3GeigerHit delayedHit = theGgColl_->contents().at(alpha.geigerHitList()->at(i));

    // Loop over tracks to comparing each hit against all tracks
    for(int j = 0; j < trackList.size(); j++){

      // Check distance to first hit in prompt track and store closest.
      int firstTrackHitId = trackList.at(j).geigerHitList()->at(0);
      N3GeigerHit firstTrackHit = theGgColl_->contents().at(firstTrackHitId);
      double firstTrackDistXY = sqrt(pow(delayedHit.anodePosition().x()-firstTrackHit.anodePosition().x(),2)+
				     pow(delayedHit.anodePosition().y()-firstTrackHit.anodePosition().y(),2));
      double firstTrackDistZ  = fabs(delayedHit.z()-firstTrackHit.z());
      double firstTrackDist;
      if(firstTrackHit.z() == 0){
	firstTrackDist = firstTrackDistXY;
      } else {
	firstTrackDist = sqrt(pow(firstTrackDistXY,2)+pow(firstTrackDistZ,2));
      }
      if(firstTrackDist < minTrackHitDist){
	trackId = j;
	minTrackHitId = firstTrackHitId;
	minTrackHitDist = firstTrackDist;
	minTrackHitDistXY = firstTrackDistXY;
	minTrackHitDistZ  = firstTrackDistZ;
	minTrackHitDelayedId = alpha.geigerHitList()->at(i);
      }

      // Now check distance to last hit in prompt track and store closest.
      int lastTrackHitId = trackList.at(j).geigerHitList()->at((trackList.at(j).geigerHitList()->size()-1));
      N3GeigerHit lastTrackHit = theGgColl_->contents().at(lastTrackHitId);
      double lastTrackDistXY = sqrt(pow(delayedHit.anodePosition().x()-lastTrackHit.anodePosition().x(),2)+
				     pow(delayedHit.anodePosition().y()-lastTrackHit.anodePosition().y(),2));
      double lastTrackDistZ  = fabs(delayedHit.z()-lastTrackHit.z());
      double lastTrackDist;
      if(lastTrackHit.z() == 0){
	lastTrackDist = lastTrackDistXY;
      }else {
	lastTrackDist = sqrt(pow(lastTrackDistXY,2)+pow(lastTrackDistZ,2));
      }
      if(lastTrackDist < minTrackHitDist){
	trackId = j;
	minTrackHitId = lastTrackHitId;
	minTrackHitDist   = lastTrackDist;
	minTrackHitDistXY = lastTrackDistXY;
	minTrackHitDistZ  = lastTrackDistZ;
	minTrackHitDelayedId = alpha.geigerHitList()->at(i);
      }
    }
  }

  // Now we've decided which track to use, find the closest hit to the track vertex.
  for(int i = 0; i < alpha.geigerHitList()->size(); i++) {
    N3GeigerHit delayedHit = theGgColl_->contents().at(alpha.geigerHitList()->at(i));

    CLHEP::Hep3Vector trackVertex = trackList.at(trackId).intersectionOnFoil();

    // Compare each hit to track vertex (intersection on foil), as long as vertex is good.
    if(trackVertex.mag2() > 1e-4){

      double distXY = sqrt(pow(delayedHit.anodePosition().x()-trackVertex.x(),2)+
			   pow(delayedHit.anodePosition().y()-trackVertex.y(),2));
      double distZ  = fabs(delayedHit.z()-trackVertex.z());
      double dist;
      if(trackVertex.z() == 0 or delayedHit.z() == 0){
	dist = distXY;
      } else {
	dist = sqrt(pow(distXY,2)+pow(distZ,2));
      }
      // Store closest hit.
      if(dist < minTrackVertexDist){
	minTrackVertexDist   = dist;
	minTrackVertexDistXY = distXY;
	minTrackVertexDistZ  = distZ;
	minTrackVertexDelayedId = alpha.geigerHitList()->at(i);
      }
    }
  }

  // Once we know the closest hits, we can compare them to our alpha identification parameters
  // to determine whether or not accept this cluster as an alpha, either from the foil or from 
  // a wire.

  bool nearFoil = false;
  bool nearWire = false;

  // First check whether it fills foil criteria
  if((minTrackVertexDistXY < minClusterDistXY_ and minTrackVertexDistZ < minClusterDistZ_) or minTrackVertexDist < minClusterDist_){
    nearFoil = true;
  }
  // Then check whether it fills wire criteria
  if((minTrackHitDistXY < minClusterDistXY_ and minTrackHitDistZ < minClusterDistZ_) or minTrackHitDist < minClusterDist_){
    nearWire = true;
  }

  // If the cluster doesn't fulfill either the foil or wire criteria, then it's not a 
  // good candidate so don't keep it.
  if(!nearFoil && !nearWire){return false;}


  // The final selection is based on time of the delayed cluster. Start by finding first
  // hit time and using it as time of the alpha
  int nDelayedHits = alpha.geigerHitList()->size();
  double alphaTime = 1e6;
  for (unsigned int i = 0; i < alpha.geigerHitList()->size(); i++) {
    if(theGgColl_->contents().at(alpha.geigerHitList()->at(i)).alphaTime() < alphaTime){
      alphaTime = theGgColl_->contents().at(alpha.geigerHitList()->at(i)).alphaTime();
    }
  }

  // Then compare time against parameters.  Reject if it fails criteria.
  bool goodTime = false;
  if     (nDelayedHits == 1 && alphaTime > minTimeOf1DelayedHit_) {goodTime = true;}
  else if(nDelayedHits == 2 && alphaTime > minTimeOf2DelayedHits_){goodTime = true;}
  else if(nDelayedHits == 3 && alphaTime > minTimeOf3DelayedHits_){goodTime = true;}
  else if(nDelayedHits > 3  && alphaTime > minTimeOf4DelayedHits_){goodTime = true;}
  if(!goodTime){return false;}

  // If it's passed the above selection, we can consider it a good candidate and therefore
  // calculate all the relevant variables to store.  The remainder of this function does this.

  // Get side of alpha (0 is inner, 1 is outer detector)
  int alphaSide = theGgColl_->contents().at(alpha.geigerHitList()->at(0)).side();

  // Get lowest geiger layer that the cluster has hit
  int lowestLayer = 10;
  for (int i = 0; i < alpha.geigerHitList()->size(); i++){
    int layer = theGgColl_->contents().at(alpha.geigerHitList()->at(i)).layer();
    if(layer < lowestLayer){lowestLayer = layer;}
  }

  // Get maximum time difference between any two hits in cluster
  double MaxTimeDiff = 0;
  for (int i = 0; i < alpha.geigerHitList()->size(); i++){
    N3GeigerHit temphit1 = theGgColl_->contents().at(alpha.geigerHitList()->at(i));
    for (int j = i+1; j < alpha.geigerHitList()->size(); j++){
      N3GeigerHit temphit2 = theGgColl_->contents().at(alpha.geigerHitList()->at(j));
      double TimeDiff = fabs(temphit1.alphaTime() - temphit2.alphaTime());
      if(TimeDiff > MaxTimeDiff){MaxTimeDiff = TimeDiff;}
    }
  }

  // Find hits which are furthest away from foil and wire for each case.  These
  // are required to calculate lengths at user-analysis level.
  double maxTrackVertexDist   = 0;
  double maxTrackVertexDistXY = 0;
  double maxTrackVertexDistZ  = 0;
  int    maxTrackVertexDelayedId = -1;
  double maxTrackHitDist  = 0;
  double maxTrackHitDistXY = 0;
  double maxTrackHitDistZ  = 0;
  int    maxTrackHitDelayedId = -1;

  for(int i = 0; i < alpha.geigerHitList()->size(); i++) {
    N3GeigerHit delayedHit = theGgColl_->contents().at(alpha.geigerHitList()->at(i));

    // Only find furthest hit from foil if nearFoil flag is true.
    if(nearFoil){
      CLHEP::Hep3Vector trackVertex = trackList.at(trackId).intersectionOnFoil();
      double distXY = sqrt(pow(delayedHit.anodePosition().x()-trackVertex.x(),2)+
			   pow(delayedHit.anodePosition().y()-trackVertex.y(),2));
      double distZ  = fabs(delayedHit.z()-trackVertex.z());
      double dist;
      if(trackVertex.z() == 0 or delayedHit.z() == 0){
	dist = distXY;
      } else {
	dist = sqrt(pow(distXY,2)+pow(distZ,2));
      }
      // Store furthest hit.
      if(dist > maxTrackVertexDist){
	maxTrackVertexDist   = dist;
	maxTrackVertexDistXY = distXY;
	maxTrackVertexDistZ  = distZ;
	maxTrackVertexDelayedId = alpha.geigerHitList()->at(i);
      }
    }

    // If passes nearWire criteria, check distance to either first or last hit in prompt track
    // (as found earlier) and store furthest hit.
    if(nearWire){
      N3GeigerHit trackHit = theGgColl_->contents().at(minTrackHitId);
      double trackDistXY = sqrt(pow(delayedHit.anodePosition().x()-trackHit.anodePosition().x(),2)+
				pow(delayedHit.anodePosition().y()-trackHit.anodePosition().y(),2));
      double trackDistZ  = fabs(delayedHit.z()-trackHit.z());
      double trackDist;
      if(trackHit.z() == 0){
	trackDist = trackDistXY;
      } else {
	trackDist = sqrt(pow(trackDistXY,2)+pow(trackDistZ,2));
      }
      if(trackDist > maxTrackHitDist){
	maxTrackHitDist   = trackDist;
	maxTrackHitDistXY = trackDistXY;
	maxTrackHitDistZ  = trackDistZ;
	maxTrackHitDelayedId = alpha.geigerHitList()->at(i);
      }
    }
  }

  // Make Hep3Vectors for closest and furthest hit for both hypotheses.
  CLHEP::Hep3Vector foilClosestHitVector(0,0,0);
  CLHEP::Hep3Vector foilFurthestHitVector(0,0,0);
  CLHEP::Hep3Vector wireClosestHitVector(0,0,0);
  CLHEP::Hep3Vector wireFurthestHitVector(0,0,0);

  if(nearFoil){
    CLHEP::Hep3Vector trackVertex = trackList.at(trackId).intersectionOnFoil();

    N3GeigerHit foilClosestHit  = theGgColl_->contents().at(minTrackVertexDelayedId);
    foilClosestHitVector = CLHEP::Hep3Vector(foilClosestHit.anodePosition().x() - trackVertex.x(),
					     foilClosestHit.anodePosition().y() - trackVertex.y(),
					     foilClosestHit.z() - trackVertex.z());

    N3GeigerHit foilFurthestHit = theGgColl_->contents().at(maxTrackVertexDelayedId);
    foilFurthestHitVector = CLHEP::Hep3Vector(foilFurthestHit.anodePosition().x() - trackVertex.x(),
					      foilFurthestHit.anodePosition().y() - trackVertex.y(),
					      foilFurthestHit.z() - trackVertex.z());
  }
  if(nearWire){

    N3GeigerHit trackHit = theGgColl_->contents().at(minTrackHitId);

    N3GeigerHit wireClosestHit  = theGgColl_->contents().at(minTrackHitDelayedId);
    wireClosestHitVector = CLHEP::Hep3Vector (wireClosestHit.anodePosition().x() - trackHit.anodePosition().x(),
					      wireClosestHit.anodePosition().y() - trackHit.anodePosition().y(),
					      wireClosestHit.z() - trackHit.z());

    N3GeigerHit wireFurthestHit = theGgColl_->contents().at(maxTrackHitDelayedId);
    wireFurthestHitVector = CLHEP::Hep3Vector(wireFurthestHit.anodePosition().x() - trackHit.anodePosition().x(),
					      wireFurthestHit.anodePosition().y() - trackHit.anodePosition().y(),
					      wireFurthestHit.z() - trackHit.z());
  }

  // If there's more than one hit then we fit a straight line through the delayed hits to 
  // extrapolate back and find a vertex. First fit in XY then fit in XZ.

  // First put hits into vectors that we fit
  std::vector<double> x;
  std::vector<double> y;
  std::vector<double> z;
  std::vector<double> x_z;
  for(int i = 0; i < alpha.geigerHitList()->size(); i++){
    N3GeigerHit delayedHit = theGgColl_->contents().at(alpha.geigerHitList()->at(i));
    x.push_back(delayedHit.anodePosition().x());
    y.push_back(delayedHit.anodePosition().y());
    if(delayedHit.z() != 0){
      z.push_back(delayedHit.z());
      x_z.push_back(delayedHit.anodePosition().x());
    }
  }

  // Set errors on hit measurements (taken straight from Vera's code)
  double x_err = 0.9;
  double y_err = 0.9;
  double z_err = 0.6;

  // Fit line in xy plane
  double A_xy, B_xy;
  fitAlphaTrack(x, y, x_err, y_err, A_xy, B_xy);

  // Fit line in xz plane
  double A_xz, B_xz;
  fitAlphaTrack(x_z, z, x_err, z_err, A_xz, B_xz);

  CLHEP::Hep3Vector alphaFoilVertex(0,0,0);
  if(z.size() > 1){
    alphaFoilVertex = findAlphaFoilVertex(x.at(0),y.at(0),z.at(0), A_xy, B_xy, A_xz, B_xz);
  }

  // Find alpha track length by looking for longest extrapolation of fit
  double alphaTrackLength = 0;
  if(alphaFoilVertex.mag() > 0){
    for (int i = 0; i < alpha.geigerHitList()->size(); i++){

      N3GeigerHit temphit = theGgColl_->contents().at(alpha.geigerHitList()->at(i));
      double x,y,z;

      if(atan(fabs(A_xy)) < 1){
	x = temphit.anodePosition().x();
	y = A_xy*x+B_xy;
      } else {
	y = temphit.anodePosition().y();
	x = (y - B_xy)/A_xy;
      }
      z = A_xz*x + B_xz;

      CLHEP::Hep3Vector trackVertex = trackList.at(trackId).intersectionOnFoil();
      double trackLength = sqrt(pow(x-trackVertex.x(),2)
				+pow(y-trackVertex.y(),2)
				+pow(z-trackVertex.z(),2));

      if(trackLength > alphaTrackLength){
	alphaTrackLength = trackLength;
      }

    }
  }

  // Set alpha track direction
  CLHEP::Hep3Vector alphaTrackVector(0,0,0);

  // First just take gradients from fits
  if(A_xy != 0){
    alphaTrackVector.setX(1);
    alphaTrackVector.setY(A_xy);
    alphaTrackVector.setZ(A_xz);
    alphaTrackVector /= alphaTrackVector.mag();
  }

  // Then check scalar product to see whether the direction needs to be reversed
  double scalar_prod = alphaFoilVertex.x()*alphaTrackVector.x()
		       + alphaFoilVertex.y()*alphaTrackVector.y();

  if((alphaSide == 1 && scalar_prod < 0) or (alphaSide == 0 && scalar_prod > 0)){
    alphaTrackVector *= -1;
  }

  // Lastly, scale track vector by track length
  if(alphaTrackLength != 0){alphaTrackVector *= alphaTrackLength;}

  // Finally we store all the relevant variables in the alpha object.
  alpha.setTrackId(trackId);
  alpha.setNDelayedHits(nDelayedHits);
  alpha.setTime(alphaTime);
  alpha.setSide(alphaSide);
  alpha.setLowestLayer(lowestLayer);
  alpha.setMaxDelayedTimeDiff(MaxTimeDiff);
  alpha.setNearFoil(nearFoil);
  alpha.setFoilClosestHitId(minTrackVertexDelayedId);
  alpha.setFoilFurthestHitId(maxTrackVertexDelayedId);
  alpha.setFoilClosestHitVector(foilClosestHitVector);
  alpha.setFoilFurthestHitVector(foilFurthestHitVector);
  alpha.setNearWire(nearWire);
  alpha.setWireClosestHitId(minTrackHitDelayedId);
  alpha.setWireFurthestHitId(minTrackHitDelayedId);
  alpha.setWireClosestHitVector(wireClosestHitVector);
  alpha.setWireFurthestHitVector(wireFurthestHitVector);
  alpha.setFoilVertex(alphaFoilVertex);
  alpha.setTrackVector(alphaTrackVector);

  return true;
}

AppResult AlphaFinder::event(AppEvent *anEvent) {
  // std::cout << "========================= AlphaFinder::event(AppEvent* anEvent) - begin"
  // 	    << std::endl;
  std::ostream_iterator< int > output( std::cout, " " );

  StorableObject::SelectByClassName cName("EventHeader");
  EventRecord::ConstIterator eventHeader_ci(anEvent, cName);    
  if (!eventHeader_ci.is_valid()) {
    std::cout << "Error Accessing the EventHeader" << std::endl;
    anEvent->listObjects();
    return AppResult::ERROR;
  } 
  EventHeader_ch eventHeader(eventHeader_ci);

  if (makeClusters(anEvent) == AppResult::ERROR) {
    return AppResult::OK;
  }

  AlphaColl *aColl = new AlphaColl();

  // std::cout << "========================= begin loop over delayed clusters "
  // 	    << std::endl;

  for(std::vector<std::vector<int> >::iterator clusterIter = delayedClusters_.begin();
      clusterIter != delayedClusters_.end(); clusterIter++) {
    Alpha aCand;
    aCand.setGeigerHitList((*clusterIter));

    if(goodAlphaCandidate(aCand)){
      aColl->add(aCand);
    }

  }

  AlphaColl_ch handle(aColl);
  if ((anEvent->append(handle)).is_null()) {
    std::cout 
      << " ERROR - AlphaFinder - error loading collection of alphas "
      << std::endl;
    return AppResult::ERROR;
  }

  // std::cout << "========================= AlphaFinder::event(AppEvent* anEvent) - end"
  // 	    << std::endl << std::endl;

  return AppResult::OK;
}

AppResult AlphaFinder::endRun(AppEvent *aRun) {
  return AppResult::OK;
}

AppResult AlphaFinder::endJob(AppEvent *aJob) {
  return AppResult::OK;
}

//-------------------------------------------------------------------------
// Accessors
//-------------------------------------------------------------------------

