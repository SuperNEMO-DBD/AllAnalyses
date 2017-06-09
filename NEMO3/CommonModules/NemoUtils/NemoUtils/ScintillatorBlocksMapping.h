//
//  ScintillatorBlocksMapping.h
//
//  Created by Stefano Torre on 01/06/12.
//

#ifndef NEMO_SCINTILLATORBLOCKSMAPPING_H_
#define NEMO_SCINTILLATORBLOCKSMAPPING_H_
#include "NemoObjects/N3CalorimeterHitColl.h"
#include "NemoObjects/CalibCaloHitColl.h"

class ScintillatorBlocksMapping {
 public:
  ScintillatorBlocksMapping();
  ScintillatorBlocksMapping(N3CalorimeterHitColl_ch& collection);
  void initMapping(N3CalorimeterHitColl_ch& collection);
  //-------------------------------------------------------------------------
  // Accessor to retrive topological informations
  //-------------------------------------------------------------------------    
  std::vector<int> all_neighbours(int& id) ;
  std::vector<int> diag_neighbours(int& id);
  std::vector<int> side_neighbours(int& id);

 private:
  bool mapping_done_;
  void build_neighbours_maps() ;
  std::map<int, std::vector<int> > all_neighbours_;
  std::map<int, std::vector<int> > diag_neighbours_;
  std::map<int, std::vector<int> > side_neighbours_;
  N3CalorimeterHitColl_ch collection_;
};

#endif
