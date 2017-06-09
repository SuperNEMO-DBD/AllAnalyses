//
//  RunSummaryTable.h
//
//  Created by Stefano Torre on 19/01/12.
//

#ifndef NEMOMODS_RUNSUMMARYTABLE_H_
#define NEMOMODS_RUNSUMMARYTABLE_H_

struct RunSummaryEntry {
  int         runNumber;
  SqlDate     runDate;
  long        numEvents;
  int         runStatus;
  SqlDate     runStart;	       
  SqlDate     runStop;	       
  long        deltaStartStop;  
  double      deadTime;	       
  long        runTime;	       
  SqlDate     firstEventDate;  
  SqlDate     lastEventDate;   
  long        deltaFirstLast;  
  int         field;	       
  int         trigger;         
}; 

class RunSummaryTable {
  std::map<int, RunSummaryEntry> data_;    
 public:
  RunSummaryTable() {};
  ~RunSummaryTable(){data_.clear();}
  void add(RunSummaryEntry entry) { 
    data_.insert(std::pair<int, RunSummaryEntry>(entry.runNumber, entry)); 
  }
  SqlDate     runDate(int runNumber) const {
    return (contains(runNumber) ? data_.find(runNumber)->second.runDate : SqlDate());
  }
  long        numEvents(int runNumber) const {
    return (contains(runNumber) ? data_.find(runNumber)->second.numEvents : -1);
  }
  int         runStatus(int runNumber) const {
    return (contains(runNumber) ? data_.find(runNumber)->second.runStatus : -1);
  }
  SqlDate     runStart(int runNumber) const {
    return (contains(runNumber) ? data_.find(runNumber)->second.runStart : SqlDate()); 
  }
  SqlDate     runStop(int runNumber) const {
    return (contains(runNumber) ? data_.find(runNumber)->second.runStop : SqlDate());
  }
  long        deltaStartStop(int runNumber) const {
    return (contains(runNumber) ? data_.find(runNumber)->second.deltaStartStop : -1);
  }
  double      deadTime(int runNumber) const {
    return (contains(runNumber) ? data_.find(runNumber)->second.deadTime : -1);
  }
  long        runTime(int runNumber) const {
    return (contains(runNumber) ? data_.find(runNumber)->second.runTime : -1);
  }
  SqlDate     firstEventDate(int runNumber) const {
    return (contains(runNumber) ? data_.find(runNumber)->second.firstEventDate : SqlDate());
  }
  SqlDate     lastEventDate(int runNumber) const {
    return (contains(runNumber) ? data_.find(runNumber)->second.lastEventDate : SqlDate());
  }
  long        deltaFirstLast(int runNumber) const {
    return (contains(runNumber) ? data_.find(runNumber)->second.deltaFirstLast : -1);
  }
  int         field(int runNumber)   const {
    return (contains(runNumber) ? data_.find(runNumber)->second.field : -1);
  }
  int         trigger(int runNumber) const {
    return (contains(runNumber) ? data_.find(runNumber)->second.trigger : -1);
  }
  int         nEntries()  const {return data_.size(); }
  bool        contains(int runNumber) const  {return data_.find(runNumber) != data_.end(); }
};

#endif
