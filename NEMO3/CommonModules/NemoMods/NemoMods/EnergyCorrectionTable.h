//
//  EnergyCorrectionTable.h
//
//  Created by Stefano Torre on 19/01/12.
//

#ifndef NEMOMODS_ENERGYCORRECTIOTABLE_H_
#define NEMOMODS_ENERGYCORRECTIOTABLE_H_

struct ECPhotoMultiplierData {
    int pmNum;
    double resolution;
    double resolutionError;
    double alpha;
    double alphaError;
    double beta;
    double betaError;
    int status;
};

struct EnergyCorrectionEntry {
    int runId;
    int ecRelease;
    int ecVersion;
    SqlDate runDate;
    SqlDate endDate;
    SqlDate aplDate;
    int ecType;
    std::map<int, ECPhotoMultiplierData> pmtCorrections;
    void add(ECPhotoMultiplierData entry) {
        pmtCorrections.insert(std::pair<int, ECPhotoMultiplierData>(entry.pmNum, entry));
    }
    bool contains(int pmtId) {
        return (pmtCorrections.find(pmtId) != pmtCorrections.end());
    }
};

class EnergyCorrectionTable {
    std::map<int, EnergyCorrectionEntry> data_;
public:
    EnergyCorrectionTable() {};
    ~EnergyCorrectionTable() {data_.clear();}
    
    void add(EnergyCorrectionEntry entry) {
        data_.insert(std::pair<int, EnergyCorrectionEntry>(entry.runId, entry));
    }
    
    int     ecRelease(int runId)        {return data_[runId].ecRelease;}
    int     ecVersion(int runId)        {return data_[runId].ecVersion;}
    SqlDate runDate(int runId)          {return data_[runId].runDate;}
    SqlDate endDate(int runId)          {return data_[runId].endDate;}
    SqlDate aplDate(int runId)          {return data_[runId].aplDate;}
    int     ecType(int runId)           {return data_[runId].ecType;}
    
    bool    contains(int runId) {
        return (data_.find(runId) != data_.end());
    }
    
    ECPhotoMultiplierData getPmtData(int runId, int pmtId) {
        if (data_[runId].contains(pmtId)) {
            return data_[runId].pmtCorrections[pmtId];
        } else {
            ECPhotoMultiplierData tmp;
            tmp.pmNum = -1;
            return tmp;
        }
    }
    
    void addPmtData(int runId, ECPhotoMultiplierData entry) {
        data_[runId].add(entry);
    }
    int nEntries()                      {return data_.size();}
};



#endif
