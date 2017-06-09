//
//  CaloClusterFinder.cpp
//
//  Created by Summer blot on 20/6/13.
//
//  Please look through the header file and also NemoObjects/GammaCluster.h
//  to find comments about which methods are useful and which are DANGEROUS/obsolete.
//  
//  DocDB is emminent. -SDB 24/2/14


// Nemo analysis modules and objects
#include "NemoMods/CaloClusterFinder.h"
#include "NemoObjects/NemorHeader.h"

// Hereward modules and objects
#include "Hereward/SuperNemoData/EventHeader.h"
#include "Hereward/SuperNemoProcessing/Constants.h"

// STL
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <cmath>

//ROOT
#include "TMath.h"

bool sort_by_time(const Gamma &hit1, const Gamma &hit2 ){
    double time_i = hit1.measTime();
    double time_j = hit2.measTime();
    if ( time_i < time_j ) return true; // more negative hits are actually earlier in time.
    else return false;
}
/*
bool sort_by_energy(const Gamma& hit1,const Gamma& hit2 ){
    double Ei = hit1.energy();
    double Ej = hit2.energy();
    if ( Ei > Ej ) return true; //  puts most energetic hit first
    else return false;
}
*/
//-------------------------------------------------------------------------
// Constructor
//-------------------------------------------------------------------------
CaloClusterFinder::CaloClusterFinder(const std::string theName, 
			       const std::string theDescription) :
  AppModule(theName, theDescription),
  debug(-1),
  allowNoiseInCluster_(false), // *ONLY* set to true if trying to assess systematic uncertainties.
  cutOnClusterProbability_(false), // should *never* cut on this.
  avgWeightedByEnergy_(false), // measured time error is default
  minAllowedClusterProb_(0.001), // again,should *not* cut on this.
  maxTimeDiff_(100.), // Should not lower this threshold without dedicated study.
                      // data/MC distribution shapes are very different!!!
  maxLDFlag_(0) {
  // maxHSFlag_(0),
  //allowedHSFlags_.push_back(0),
  //allowedHSFlags_.push_back(10) {

}

CaloClusterFinder::~CaloClusterFinder() {
}

//-------------------------------------------------------------------------
// Operations
//-------------------------------------------------------------------------
AppResult CaloClusterFinder::beginJob(AppEvent *aJob) {

  return AppResult::OK;
}

AppResult CaloClusterFinder::beginRun(AppEvent *aRun) {
  return AppResult::OK;
}

AppResult CaloClusterFinder::event(AppEvent *anEvent) {

  StorableObject::SelectByClassName cName("EventHeader");
  EventRecord::ConstIterator eventHeader_ci(anEvent, cName);    
  if (!eventHeader_ci.is_valid()) {
    std::cout << "Error Accessing the EventHeader" << std::endl;
    anEvent->listObjects();
    return AppResult::ERROR;
  } 
  EventHeader_ch eventHeader(eventHeader_ci);

  GammaColl::GammaList gammaList;
  if (!GammaColl::find(anEvent, gColl)) {
    /* std::cout 
    << "-- CaloClusterFinder - Gamma collection not found"
    << std::endl;*/
    return AppResult::OK;
  } else {
    gammaList = gColl->contents();
  }

  if ( debug > 1) {
     std::cout	
       << "--CailClusterFinder: Nentries in gammaList: " << gammaList.size() 
      << std::endl;
  }

  N3TrackColl::N3TrackList trackList;
  if (!N3TrackColl::find(anEvent, theTrackColl)) {        
    std::cout << "-- CaloClusterFinder - Tracks not found" << std::endl;
    return AppResult::OK;        
  } else {
    trackList = theTrackColl->contents();
  }

  if (!N3CalorimeterHitColl::find(anEvent, n3Calohits)) {
    std::cout << "-- CaloClusterFinder - N3 Calorimeter hits not found" << std::endl;
    return AppResult::OK;
  } else {
    rawCaloHitList = n3Calohits->contents();
  }

  if (!CalibCaloHitColl::find(anEvent, caloHits)) {
     std::cout 
     << "-- CaloClusterFinder - Calibrated calorimeter hits not found"
     << std::endl;
    return AppResult::OK;
  }

  // make the list of ids of blocks that have been hit by a track - we don't want to add these
  blocksWithTrack = std::vector<int>();
  for (N3TrackColl::const_iterator trackIt = trackList.begin(); trackIt != trackList.end(); ++trackIt) {
    if ((*trackIt).indexOfScintillator() < 0) continue;
    blocksWithTrack.push_back((*trackIt).indexOfScintillator());
  }

  //To hold the final list of clusters.
  GammaClusterColl *clusterColl = new GammaClusterColl();
  
  clusters = std::vector<GammaCluster>(); //deallocates the memory
  tooManyInCluster = false;
  for ( int it = 0; it < gammaList.size(); it++ ) {
    gammaHolder = std::vector<Gamma>();// free up memory

    int hitID = gammaList.at(it).rawHitId();
    
    if ( debug > 1 ) {
      std::cout << "# clusters  = " << clusters.size() << std::endl;
      std::cout << "Attempting to start a cluster with  raw hitID " << hitID <<std::endl;
    }

    //First we check if the hit is "noisy" (outside allowed in-time TDC range)
    if ( !allowNoiseInCluster_ && rawCaloHitList.at(hitID).isNoisy() ) {
      if (debug > 1) {std::cout << "\t Hit is noisy" << std::endl;}
      continue;
    }

    // Now make sure we haven't already put this hit into a cluster
    // need to change this to find function.
    clustered = checkIfClustered(gammaList.at(it).rawHitId());
    
    if ( clustered ) {
      if (debug > 1) {std::cout << "\t Hit is already clustered" << std::endl;}
      continue;
    }

    //now make sure its not from an electron hit
    bool hitByElectron = false;
    if (find(blocksWithTrack.begin(), blocksWithTrack.end(), hitID )
	!= blocksWithTrack.end()) { hitByElectron = true; }
    

  //    for ( int j = 0; j < blocksWithTrack.size(); j++ ) {
  //    if ( hitID == blocksWithTrack.at(j) ) hitByElectron = true;
  //  }
	
    if ( hitByElectron ) {
      if (debug > 1) {std::cout << "\t Hit associated to electron track " << std::endl;}
      continue;
    }

    if (debug > 1 ) std::cout << "Hit passes intial criteria. Proceed wih clustering..." << std::endl; 

    // Create a cluster for this hit we've picked up.
    gammaHolder.push_back(gammaList.at(it));

    // If all criteria are passed, then we look for neighboring hits to our seed hit
    //    for ( int j = 0; j < rawCaloHitList.size(); j++ ) {
    for ( int j = 0; j < gammaList.size(); j++ ) {
      //if ( hitID == j ) {continue;}
      if ( hitID == gammaList.at(j).rawHitId() ) {continue;}
 
      // check for neighbours ( 0 == no neighbours )
      //int compare = rawCaloHitList.at(hitID).checkNeighbour(rawCaloHitList.at(j));
      int compare = rawCaloHitList.at(hitID).checkNeighbour( rawCaloHitList.at(gammaList.at(j).rawHitId()) );
        
      if ( (compare > 0) // has neighbour
           && (allowNoiseInCluster_ || !rawCaloHitList.at(gammaList.at(j).rawHitId()).isNoisy()) // not noisy
           && (find(blocksWithTrack.begin(), blocksWithTrack.end(), gammaList.at(j).rawHitId()) == blocksWithTrack.end()) ) { // not assoc. to track

	if ( debug > 1 ) {std::cout << " \t Found Neighbor, raw hitID: " << gammaList.at(j).rawHitId() <<std::endl;}

        bool sameLayer = checkSamePetalLayer( hitID, gammaList.at(j).rawHitId());
	if ( !sameLayer) {continue;}
	
	// for ( std::vector<Gamma>::iterator k = gammaList.begin(); k != gammaList.end(); k++ ) {
        //  if ( k->rawHitId() != j ) {continue;}
                  
        if ( cutOnClusterProbability_ ) {
          tmpHolder = gammaHolder;
	  //  tmpHolder.push_back(*k);
          tmpHolder.push_back(gammaList.at(j));

          double probability;           
          bool goodProb = calculateClusterProb(tmpHolder, probability);
                  
          if ( goodProb ) {gammaHolder.push_back(gammaList.at(j));}
	  //          if ( goodProb ) {gammaHolder.push_back(*k);}
            
          if(debug > 1) {
           std::cout << "in-time probability = " << probability << std::endl;
          }
            
        } else if ( fabs(gammaList.at(it).measTime() - gammaList.at(j).measTime()) < maxTimeDiff_ ) {
	  //        gammaHolder.push_back(*k);
          gammaHolder.push_back(gammaList.at(j));
        }
        //}// k loop
      }// good status, has neighbours, isn't noisy (if no noise allowed), and is not assoc. to track
    }//~j gammaList.size()
 
    if ( debug > 1 ) {
      std::cout << " \t Pre-clustering complete. Cluster size is " << gammaHolder.size() <<std::endl;
    }

    // At this point we've looked at all of the neighbors of gammaList *it.  
    // Now let's check if any of the neighbors already found  also have neighbors.
    // -- cluster-building stage --
    for ( int j = 0; j < gammaHolder.size(); j++ ) {
      hitID = gammaHolder.at(j).rawHitId();
     
      if ( hitID == gammaList.at(it).rawHitId() ) {continue;}
      
      if ( debug > 1 ) {
        std::cout << "\t Now checking if raw hitID " << hitID << " has any neighbors..."<<std::endl;
      }

      for ( int k = 0; k < gammaList.size(); k++ ) {

      if ( debug > 1 ) {
        std::cout << "\t Picked up raw hitID " << gammaList.at(k).rawHitId() << " out of rawHits.size() = " << rawCaloHitList.size()<<std::endl;
      }
	//      for ( int k = 0; k < rawCaloHitList.size(); k++ ) {

        //make sure the hit isn't in another cluster or already picked up by this one
        clustered = checkIfClustered(gammaList.at(k).rawHitId());
        //clustered = checkIfClustered(k);
        
        if ( clustered ) {
	  if ( debug > 1 ) {std::cout<< "\t This hit is already in a cluster!" <<std::endl;}
	  continue;
	}

        int compare_to_others = rawCaloHitList.at(hitID).checkNeighbour( rawCaloHitList.at(gammaList.at(k).rawHitId()) );

        if ( (compare_to_others > 0) // has neighbour
             && (allowNoiseInCluster_ || !rawCaloHitList.at(gammaList.at(k).rawHitId()).isNoisy()) //not noisy
             && (find(blocksWithTrack.begin(), blocksWithTrack.end(), gammaList.at(k).rawHitId()) == blocksWithTrack.end()) ) {

	  if ( debug > 1 ) {std::cout << " \t Found Neighbor, raw hitID: " << gammaList.at(k).rawHitId() <<std::endl;}
	  
	  bool sameLayer = checkSamePetalLayer(hitID, gammaList.at(k).rawHitId());
	  if (!sameLayer) {
	    if ( debug > 1 ) {std::cout<< "\t these are petal hits, and not same layer" <<std::endl;}
	    continue;
	  }
  	    
	  //	   for ( std::vector<Gamma>::iterator m = gammaList.begin(); m != gammaList.end(); m++ ) {
          //  if ( m->rawHitId() != k ) {continue;}
                
          if ( cutOnClusterProbability_ ) {
            tmpHolder = gammaHolder;
            tmpHolder.push_back(gammaList.at(k));
	    //  tmpHolder.push_back(*m);
                    
            double probability;   
            bool goodProb = calculateClusterProb(tmpHolder, probability);
	    //              if ( goodProb ) {gammaHolder.push_back(*m);}
            if ( goodProb ) {
	      //gammaHolder.push_back(*m);
              gammaHolder.push_back(gammaList.at(k));

              if(debug > 1) {
               std::cout << "in-time probability = " << probability << std::endl;
              }

	    } else if ( !goodProb && debug > 1 ) {
              std::cout << "\t raw hitId "<< gammaList.at(k).rawHitId() <<" has bad probability = , " << probability <<", not adding to cluster" << std::endl;
	    }

	  } else if (fabs(gammaHolder.at(j).measTime() - gammaList.at(k).measTime()) < maxTimeDiff_) {
	    gammaHolder.push_back(gammaList.at(k));
	      //              gammaHolder.push_back(*m);
	  }           
	  // }//~m
	}//good status, has neighbours, isn't noisy (if no noise allowed), and is not assoc. to track
      }//~k gammaList.size()
    }//~checking others (~j)
  
    if ( debug > 1 ) {
      std::cout << "Cluster building complete." <<std::endl;
    }

    if ( debug > 1 ) {
      std::cout << std::endl;
    }
    
    GammaCluster thisCluster;

    //std::sort(gammaHolder.begin(),gammaHolder.end(), sort_by_time); // for gamma list sorted by time
    //std::sort(gammaHolder.begin(),gammaHolder.end(), sort_by_energy); // sorted by energy

    thisCluster.setCluster(gammaHolder);
    
    double totalProb;
    bool goodProbs = calculateClusterProb(gammaHolder, totalProb);
    thisCluster.setClusterProb(totalProb);
    thisCluster.setClusterId(clusters.size());

    //**************************************************************************************
    // 1/4/14 SDB - No, not an April fools joke.
    // We do not check any PMT LS/HS flags or status before clustering. So now, we need to
    // set the different cluster statuses based on the allowed LD/HS flags for analysis. 
    //**************************************************************************************

    bool pmtStatus_ = true;
    bool ldFlags_ = true;
    bool ldCorrs_ = true; 
    bool ldCorrErrs_ = true;
    bool hsFlags_ = true;
    for ( int hit_i = 0; hit_i < gammaHolder.size(); hit_i++ ) {
      int calibHitID = gammaHolder.at(hit_i).calibHitId();

      //First we check PMT statuses
      if ( !(caloHits->contents().at(calibHitID).goodFlag()) ) {
        if (debug > 1) {std::cout << "\t\t Hit had BAD STATUS, status =  "
			    << caloHits->contents().at(calibHitID).status() << std::endl;}
        pmtStatus_ = false;
      } 

      //Now we check for LD flags and missing corrections/errors which indicate issues with laser survey
      if ( caloHits->contents().at(calibHitID).ldFlag() > maxLDFlag_ ) {
        if (debug > 1) {std::cout << "\t\t  Hit had bad LD flag, LD = " 
				  << caloHits->contents().at(calibHitID).ldFlag() << std::endl;}
	ldFlags_ = false;
      } 
    
      if ( caloHits->contents().at(calibHitID).ldCorr() == 0 ) {
	if (debug > 1) {std::cout << "\t\t  Hit had no LD correction, LDCorr = "
				  << caloHits->contents().at(calibHitID).ldCorr() << std::endl;}
	ldCorrs_ = false;
      } 

      if ( caloHits->contents().at(calibHitID).ldCorrErr() == 0) {
	if (debug > 1) {std::cout << "\t\t  Hit had no LD corr. error, LDCorrErr = "
				  << caloHits->contents().at(calibHitID).ldCorrErr() << std::endl;}
         ldCorrErrs_ = false;
      } 

      // Now we check HS flags. Default settings are as follows:
      // --> if N hits/cluster == 1, then only HS = 0 is allowed
      // --> if N hits/cluster > 1, then HS = 10 (which indicates potentially noisy PM) should be
      //     allowed in the cluster because the likelihood of a noisy hit being associated with a cluster
      //     is very low, so even if HS = 10, its probably actually a real hit and we should keep it
      if ( gammaHolder.size() == 1 ) {
        if ( caloHits->contents().at(calibHitID).hsFlag() != 0 ) {
	  if (debug > 1) {std::cout << "\t\t  Nhits /cluster == 1 && hit has bad HS flag, HS = "
				    << caloHits->contents().at(calibHitID).hsFlag() << std::endl;}
	  hsFlags_ = false;
	}
      } else { // N hits/cluster > 1
  	if ( caloHits->contents().at(calibHitID).hsFlag() == 1 ) {
	  if (debug > 1) {std::cout << "\t\t  Nhits /cluster > 1 && Hit had bad HS flag, HS = "
				    << caloHits->contents().at(calibHitID).hsFlag() << std::endl;}
     	  hsFlags_ = false;
	}
      }

    }//~ hit_i, checking PMT statuses and flags for good quality.
    thisCluster.setGoodPMTStatuses(pmtStatus_);
    thisCluster.setGoodLDFlags(ldFlags_);
    thisCluster.setHasLDCorrs(ldCorrs_);
    thisCluster.setHasLDCorrErrs(ldCorrErrs_);
    thisCluster.setGoodHSFlags(hsFlags_);

    clusters.push_back(thisCluster);
   
  }//~ gammaList it
    
  if ( debug > 1 ) {std::cout << "Cluster module finished. Found " << clusters.size() << " clusters..." << std::endl;}

  // Last tasks: find the energy weighted average time and postion of each cluster, and check if there are neighbors
  for ( std::vector<GammaCluster>::iterator it = clusters.begin(); it != clusters.end(); it++ ) {

    int numNeighbours = checkForNeighbouringClusters(*it);
    it->setNumNeighbours(numNeighbours);

    findMeanTime(*it);
    findMeanPosition(*it);
    clusterColl->add(*it);
  }

  GammaClusterColl_ch handle(clusterColl);
  if ((anEvent->append(handle)).is_null()) {
    std::cout 
      << " ERROR - CaloClusterFinder - error loading collection of gammas clusters "
      << std::endl;
    return AppResult::ERROR;
   }
  
  return AppResult::OK;
}

AppResult CaloClusterFinder::endRun(AppEvent *aRun) {

  return AppResult::OK;
}

AppResult CaloClusterFinder::endJob(AppEvent *aJob) {
  return AppResult::OK;
}

//-------------------------------------------------------------------------
// Accessors
//-------------------------------------------------------------------------

void CaloClusterFinder::findMeanPosition(GammaCluster &theCluster) {
  // Finds the weighted mean position of a cluster, default weighting done by measured time error of hit

  double avgX = 0;
  double avgY = 0;
  double avgZin = 0;

  double weight = 0;
  double sumWeights = 0;
  
  double totEnergy = 0.;
  double dTotalE = 0;
  for ( int i = 0; i < theCluster.cluster().size(); i++ ) {
    Gamma gamma = theCluster.cluster().at(i);

    totEnergy += gamma.energy();
    dTotalE   += pow(gamma.dEnergy(),2);
 
    if ( avgWeightedByEnergy_ ) {
      weight = gamma.energy();
      sumWeights += gamma.energy();
    } else { //Default
      weight = 1./pow(gamma.dMeasTime(),2);
      sumWeights += 1./pow(gamma.dMeasTime(),2);
    }
 
    avgX       += (gamma.hitPosition().x() * weight);
    avgY       += (gamma.hitPosition().y() * weight);
    avgZin     += (gamma.hitPosition().z() * weight);

   if( debug > 1 ) {std::cout << " \t this hit energy = " << gamma.energy() << " +/- " << gamma.dEnergy()  << std::endl;}
   
  }

  if ( debug > 1 ) {
    std::cout << "So total energy is " << totEnergy << " +/- " << sqrt(dTotalE) << std::endl;
    std::cout << "------------------" << std::endl;
  }

  CLHEP::Hep3Vector position( avgX / sumWeights, avgY / sumWeights, avgZin / sumWeights);

  theCluster.setHitPosition(position);
  theCluster.setEnergy(totEnergy);
  theCluster.setDEnergy(sqrt(dTotalE));

  return;
}

void CaloClusterFinder::findMeanTime(GammaCluster &theCluster) {
  // Finds the weighted mean time of a cluster, default weighting is measured time error
  // 

  double avgTime = 0;
  double avgDTime = 0; 
  double avgScintToPMTTime = 0;
  double avgDPathLength = 0.;

  double weight = 0;
  double sumWeights = 0;
  
  //std::vector<Gamma> cluster = theCluster.cluster();
  double tmin = 100000000.;
  double tmax = -100000000.;
  int gammaMinT_id = theCluster.cluster().front().rawHitId();
  int gammaMaxT_id = theCluster.cluster().front().rawHitId();
  Gamma gammaMin = theCluster.cluster().front();
  Gamma gammaMax = theCluster.cluster().front();
  for ( int i = 0; i < theCluster.cluster().size(); i++ ) {  
    Gamma gamma = theCluster.cluster().at(i);

    if ( gamma.measTime() < tmin ) {
      tmin = gamma.measTime();
      gammaMin = gamma;
      gammaMinT_id = gamma.rawHitId();
    }

    if ( gamma.measTime() > tmax ) {
      tmax = gamma.measTime();
      gammaMax = gamma;
      gammaMaxT_id = gamma.rawHitId();
    }

    if ( avgWeightedByEnergy_ ) {
      weight = gamma.energy();
      sumWeights += gamma.energy();
    } else { //Default
      weight = 1./pow(gamma.dMeasTime(),2);
      sumWeights += 1./pow(gamma.dMeasTime(),2);
    }
    // error is dominated by energy, so this effectively gives more preference to higher energy hits    
    avgTime    += (gamma.measTime() * weight) ;
    avgDTime   += (pow(gamma.dMeasTime(), 2) * pow(weight,2));
    
    avgScintToPMTTime += gamma.scintToPMTTime() * weight;
    avgDPathLength += (pow(gamma.dPathLength(),2) * pow(weight,2));
  
    if( debug > 1 ) {std::cout << " \t this time = " << gamma.measTime() << " +/- " << gamma.dMeasTime() << std::endl;}

  }
       
  if ( debug > 1 ) {
    std::cout << "So weighted avg time is " << avgTime / sumWeights << " +/- " << sqrt(avgDTime/pow(sumWeights,2)) << std::endl;
    std::cout << "------------------" << std::endl;
  }

  theCluster.setMeasTime(avgTime / sumWeights);
  theCluster.setDMeasTime(sqrt(avgDTime/pow(sumWeights,2)));
  theCluster.setScintToPMTTime(sqrt(avgScintToPMTTime/pow(sumWeights,2)));
  theCluster.setDPathLength(sqrt(avgDPathLength/pow(sumWeights,2)));
  
  if ( theCluster.cluster().size() > 1 ) {theCluster.setTimeSpan(fabs(tmax - tmin));}
  else {theCluster.setTimeSpan(-1);}
 
  
  theCluster.setEarliestHit(gammaMin);
  theCluster.setLatestHit(gammaMax);
  
  int fcll = -1;
  if (rawCaloHitList.at(gammaMin.rawHitId()).iobtFlag() > 1) {
    fcll = rawCaloHitList.at(gammaMin.rawHitId()).fcll();
  }
  
  theCluster.setIOBT(rawCaloHitList.at(gammaMin.rawHitId()).iobtFlag());
  theCluster.setFCLL(fcll);

  return;
}

bool CaloClusterFinder::calculateClusterProb(std::vector<Gamma> gammaVec, double &prob) {
    bool goodProbWithAHit = false;
    double totalChiSq = 0;
    int ndf = 0;
    bool bad = false;
    std::sort(gammaVec.begin(),gammaVec.end(), sort_by_time); // for gamma list sorted by time
    for ( int i = 0; i < gammaVec.size() - 1; i++ ) {
      int j = i+1;
              
      Gamma gamma_i = gammaVec.at(i);
      Gamma gamma_j = gammaVec.at(j);
      
      CLHEP::Hep3Vector gammaVert_i = gamma_i.hitPosition();
      CLHEP::Hep3Vector gammaVert_j = gamma_j.hitPosition();

      double gammaTime_i = gamma_i.measTime();
      double gammaDTime_i = gamma_i.dMeasTime();

      double gammaTime_j = gamma_j.measTime();
      double gammaDTime_j = gamma_j.dMeasTime();
   
      double gammaDHypTime_i = gamma_i.dPathLength();
      double gammaDHypTime_j = gamma_j.dPathLength();
      
      double gammaLength = sqrt(pow(gammaVert_i.x()-gammaVert_j.x(),2)+pow(gammaVert_i.y()-gammaVert_j.y(),2)+pow(gammaVert_i.z()-gammaVert_j.z(),2));
    
      // double intHypoth = (gammaTime_i - gamma_i.scintToPMTTime()) - (gammaTime_j - gamma_j.scintToPMTTime()) + (gammaLength/(TMath::C() / 1.e7));
      double intHypoth = gammaTime_i - gammaTime_j + (gammaLength/(TMath::C() / 1.e7));
      double sigmaCombined = pow(gammaDTime_i,2) + pow(gammaDTime_j,2);
      double egPull = intHypoth / TMath::Sqrt(sigmaCombined);
        
      double thisChiSq = egPull*egPull;
        
      double thisProb = TMath::Prob(thisChiSq,1);
      if ( thisProb > minAllowedClusterProb_ ) {goodProbWithAHit = true;}
      
      totalChiSq += thisChiSq;
      ndf++;
    }
             
    double totalPint = TMath::Prob(totalChiSq,ndf);
    prob = totalPint;

    return goodProbWithAHit;
}

bool CaloClusterFinder::checkSamePetalLayer(int i, int j) {
  //extra check if its a petal block to make sure we aren't going across layers
  int iobt_i = rawCaloHitList.at(i).iobtFlag();
  int layer_i = rawCaloHitList.at(i).fcll();
  int iobt_j = rawCaloHitList.at(j).iobtFlag();
  int layer_j = rawCaloHitList.at(j).fcll();

  bool sameLayer_ = false;
  if ( iobt_i > 1 && iobt_i == iobt_j ) { // if both hits on either top/bottom petal
    if ( layer_i == layer_j ) {sameLayer_ = true;} //check that they are in the same layer
  }

  if (debug > 1 && iobt_i > 1) {std::cout<< "\t checking if petal blocks are same layer...." << sameLayer_ << std::endl;}

  sameLayer_ = sameLayer_ ||( iobt_i < 2);
  
  return sameLayer_;
}

int CaloClusterFinder::checkForNeighbouringClusters(GammaCluster &aCluster) {
// returns the number of clusters neighbouring thisCluster
  std::vector<Gamma> thisCluster = aCluster.cluster();

  if (debug > 1) {std::cout << "Checking if cluster " << aCluster.clusterId() << " has any neighhours."<<std::endl;}

  int nNeighbours_ = 0;
  std::vector<Gamma> otherCluster;
  for ( int i = 0; i < clusters.size(); i++ ) {
    if ( aCluster.clusterId() == clusters.at(i).clusterId() ) {continue;}
    else otherCluster = clusters.at(i).cluster();

    if (debug > 1) {std::cout << "\t Checking other cluster, ID = "<< clusters.at(i).clusterId() << std::endl;}

    bool foundNeighbour_ = false;      
    for( int hit_i = 0; hit_i < thisCluster.size(); hit_i++ ) {
      int hitID_i = thisCluster.at(hit_i).rawHitId();
      
      if (debug > 1) {std::cout << "\t Checking against hitID_i = "<< hitID_i <<": " << std::endl;}
      
      for( int hit_j = 0; hit_j < otherCluster.size(); hit_j++ ) {
        int hitID_j = otherCluster.at(hit_j).rawHitId();
        
        bool sameLayer = checkSamePetalLayer(hitID_i, hitID_j);
        if ( !sameLayer )  {
          if ( debug > 1 ) {std::cout << "hits not in same layer... continue" << std::endl;}
          
          continue;
        }
                
        int compare_to_other = rawCaloHitList.at(hitID_i).checkNeighbour(rawCaloHitList.at(hitID_j));
        if (debug > 1) {std::cout << "\t \t hitID_j = "<< hitID_j <<", neighbour status: " << compare_to_other << std::endl;}

        if ( compare_to_other > 0 ) foundNeighbour_ = true;
      }
    }
    if ( foundNeighbour_ ) {nNeighbours_++;}    
  }

  if (debug>1) {std::cout << "Checking complete: Found "<< nNeighbours_ << " neighbouring clusters to this one." << std::endl;}

  return nNeighbours_;
}

bool CaloClusterFinder::checkIfClustered(int aRawHitID) {
  if ( debug > 1 ) {std::cout <<"\t \t checking if hit "<< aRawHitID << " is already in a different cluster......";}

  bool isClustered_ = false;
  for ( int i = 0; i < clusters.size(); i++ ) {
    for ( int j = 0; j < clusters.at(i).cluster().size(); j++ ) {
      if ( clusters.at(i).cluster().at(j).rawHitId() == aRawHitID ) {isClustered_ = true;}
    }
  }
  
  if ( debug > 1 ) {
    std::cout << isClustered_ << std::endl;
    std::cout <<"\t \t checking if hit "<< aRawHitID << " is already in THIS cluster......";
  }

  for ( int i = 0; i < gammaHolder.size(); i++ ) {
    if ( gammaHolder.at(i).rawHitId() == aRawHitID ) {isClustered_ = true;}
  }

  if ( debug > 1 ) {std::cout << isClustered_ << std::endl;}

  return isClustered_;

}
