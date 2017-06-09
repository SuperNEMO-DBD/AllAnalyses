//
//  ScintillatorBlocksMapping.cpp
//
//  Created by Stefano Torre on 01/06/12.
//
#include "NemoUtils/ScintillatorBlocksMapping.h"

ScintillatorBlocksMapping::ScintillatorBlocksMapping() : 
  mapping_done_(false){
}

void ScintillatorBlocksMapping::initMapping(N3CalorimeterHitColl_ch& collection) {
  collection_ = collection;
  build_neighbours_maps();
}

ScintillatorBlocksMapping::
ScintillatorBlocksMapping(N3CalorimeterHitColl_ch& collection) {
  ScintillatorBlocksMapping();
  initMapping(collection);
}
//-------------------------------------------------------------------------
// Blocks mapping
//-------------------------------------------------------------------------
void ScintillatorBlocksMapping::build_neighbours_maps() {
  // loop over all the hits int he collection and find neighoutring hits
  for (unsigned int first = 0; first < collection_->contents().size(); ++first) {
    for (unsigned int second = first + 1; 
	 second < collection_->contents().size(); ++second) {
      int comparison = collection_->contents().at(first)
	.checkNeighbour(collection_->contents().at(second));

      if (comparison != 0) {
	// adjacent blocks
	std::map<int, std::vector<int> >::iterator allIt;
	std::map<int, std::vector<int> >::iterator sideIt;
	std::map<int, std::vector<int> >::iterator diagIt;
	allIt = all_neighbours_.find(first);
	sideIt = side_neighbours_.find(first);
	diagIt = diag_neighbours_.find(first);

	std::vector<int> newVec;

	// store mapping for first hit
	newVec.push_back(second);
	if (allIt == all_neighbours_.end()) {
	  // first time the first id passes the match
	  all_neighbours_.insert(std::pair<int, std::vector<int> >
				 (first, newVec));
	} else {
	  allIt->second.push_back(second);
	}

	if (comparison == 1) {
	  if (sideIt == side_neighbours_.end()) {
	    side_neighbours_.insert(std::pair<int, std::vector<int> >
				    (first, newVec));
	  } else {
	    sideIt->second.push_back(second);
	  }
	}
	
	if (comparison == 2) {
	  if (diagIt == diag_neighbours_.end()) {
	    diag_neighbours_.insert(std::pair<int, std::vector<int> >
				    (first, newVec));
	  } else {
	    diagIt->second.push_back(second);
	  }
	}
	
	newVec.clear();
	// store mapping for second hit
	allIt = all_neighbours_.find(second);
	sideIt = side_neighbours_.find(second);
	diagIt = diag_neighbours_.find(second);
	
	newVec.push_back(first);
	if (allIt == all_neighbours_.end()) {
	  // first time the second id is found
	  all_neighbours_.insert(std::pair<int, std::vector<int> >
				 (second, newVec));
	} else {
	  allIt->second.push_back(first);
	}

	if (comparison == 1) {
	  if (sideIt == side_neighbours_.end()) {
	    side_neighbours_.insert(std::pair<int, std::vector<int> >
				    (second, newVec));
	  } else {
	    sideIt->second.push_back(first);
	  }
	}

	if (comparison == 2) {
	  if (diagIt == diag_neighbours_.end()) {
	    diag_neighbours_.insert(std::pair<int, std::vector<int> >
				    (second, newVec));
	  } else {
	    diagIt->second.push_back(first);
	  }
	}
	
	newVec.clear();
      } // if (comparison != 0)
    }
  }

  mapping_done_ = true;
}

std::vector<int> ScintillatorBlocksMapping::all_neighbours(int& id) {
  if (!mapping_done_) build_neighbours_maps();
  std::map<int, std::vector<int> >::iterator it = 
    all_neighbours_.find(id);
  if (it == all_neighbours_.end()) {
    return std::vector<int>();
  } else {
    return it->second;
  }
}

std::vector<int> ScintillatorBlocksMapping::diag_neighbours(int& id) {
  if (!mapping_done_) build_neighbours_maps();
  std::map<int, std::vector<int> >::iterator it = 
    diag_neighbours_.find(id);
  if (it == diag_neighbours_.end()) {
    return std::vector<int>();
  } else {
    return it->second;
  }
}

std::vector<int> ScintillatorBlocksMapping::side_neighbours(int& id) {
  if (!mapping_done_) build_neighbours_maps();
  std::map<int, std::vector<int> >::iterator it = 
    side_neighbours_.find(id);
  if (it == side_neighbours_.end()) {
    return std::vector<int>();
  } else {
    return it->second;
  }
}

