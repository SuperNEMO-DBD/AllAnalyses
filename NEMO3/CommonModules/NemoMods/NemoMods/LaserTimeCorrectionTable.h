//
//  LaserTimeCorrectionTable.h
//
//  Created by Stefano Torre on 19/01/12.
//

#ifndef NEMOMODS_LASERTIMECORRECTIONTABLE_H_
#define NEMOMODS_LASERTIMECORRECTIONTABLE_H_

struct LaserTimeCorrectionEntry {
    int runId;
    int runNumber;
    int numberOfLasers;
    int version;
    double correction[1940];
};

class LaserTimeCorrectionTable {
    std::map<int, LaserTimeCorrectionEntry> data_;
public:
    LaserTimeCorrectionTable() {};
    ~LaserTimeCorrectionTable() {data_.clear();}
    
    void add(LaserTimeCorrectionEntry entry) {
        data_.insert(std::pair<int, LaserTimeCorrectionEntry>(entry.runId, entry));
    }
    
    int     runNumber(int runId)        {return data_[runId].runNumber; }
    int     numberOfLasers(int runId)   {return data_[runId].numberOfLasers; }
    int     version(int runId)          {return data_[runId].version;        }
    
    double  correction(int runId, unsigned int pmtNumber) {
        return data_[runId].correction[pmtNumber];
    }
    
    int     nEntries()  {return data_.size(); }
};

#endif
