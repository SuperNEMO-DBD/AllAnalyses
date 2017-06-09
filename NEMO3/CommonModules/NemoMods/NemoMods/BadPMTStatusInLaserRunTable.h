//
//  BadPMTStatusInLaserRunTable.h
//
//  Created by Stefano Torre on 19/01/12.
//

#ifndef NEMO_BADPMTSTATUSINLASERRUNTABLE_H_
#define NEMO_BADPMTSTATUSINLASERRUNTABLE_H_
#include <map>

struct PmtDataSummary {
    int pmtNumber;
    std::map<int, int> runCouples;
};

struct VersionDataSummary {
    int version;
    std::map<int, PmtDataSummary> pmtDataMap;
    
    void add(PmtDataSummary entry) {
        pmtDataMap.insert(std::pair<int, PmtDataSummary>
                          (entry.pmtNumber, entry));
    }
    
    int nEntries() { return pmtDataMap.size(); }
};

class BadPMTStatusInLaserRunTable {
    std::map<int, VersionDataSummary*> data_;
public:
    BadPMTStatusInLaserRunTable() {}
    ~BadPMTStatusInLaserRunTable() {data_.clear();}
    
    void add(VersionDataSummary* entry) {
        data_.insert(std::pair<int, VersionDataSummary*>
                     (entry->version, entry));
    }    
    
    void addPmtData(int version, PmtDataSummary entry) {
        data_[version]->add(entry);
    }
    
    void addEntry(int version, int pmtId, std::pair<int, int> entry) {
        data_[version]->pmtDataMap[pmtId].runCouples.insert(entry);
    }
    
    int nEntries()          {return data_.size();}

    bool contains(int version) {
        return (data_.find(version) != data_.end());
    }
    
    bool contains(int version, int pmt) {
        if (contains(version)) {
            return (data_[version]->pmtDataMap.find(pmt) !=
                    data_[version]->pmtDataMap.end());
        } else {
            return false;
        }
    }
    
    std::map<int, int> getRunCouplesForPmt(int version, int pmt) {
        if (contains(version, pmt)) {
            return data_[version]->pmtDataMap[pmt].runCouples;
        } else {
            return std::map<int, int>();
        }
    }

    int getLastRunForPmt(int version, int pmt, int firstRun) {
        if (contains(version, pmt)) {
            std::map<int, int>::iterator entryIter =
            data_[version]->pmtDataMap[pmt].runCouples.find(firstRun);
            if (entryIter !=
                data_[version]->pmtDataMap[pmt].runCouples.end()) {
                return entryIter->second;
            } else {
                return -1;
            }
        } else {
            return -1;
        }
    }
};


#endif
