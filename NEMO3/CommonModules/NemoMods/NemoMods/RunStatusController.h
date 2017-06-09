//
//  RunStatusController.h
//
//  Created by Stefano Torre on 23/01/12.
//
//  - 09/10/2012 - ST: 
//    - load summary of all run data in memory and provide interface for other modules
//    - add deadtime to the run info
//    

#ifndef NEMO_RUNSTATUSCONTROLLER_H_
#define NEMO_RUNSTATUSCONTROLLER_H_
#include "Hereward/DataProcPipeline/AppModule.h"
#include "NemoMods/NemoDataBaseManager.h"
#include "NemoMods/N3DbInterfaceModule.h"
#include "NemoMods/RunSummaryTable.h"
#include <TTimeStamp.h>
#include <map>
#include <vector>

class RunStatusController : public AppModule {
public:
   // Possible run periods:
   // Phase 1 period from Feb 2003 to Oct 2004
   // Phase 2 period a) from Oct 2004 to 22 may 2006
   // Phase 2 period b) from 22 may 2006 to 31 Dec 2007
   // PBA run list for blind analysis test from Yuriy 
   enum PhaseId { 
      P1, P2, P2a, P2b, PBA, P2007, P3, P1_0nu, P2_0nu, AllRuns, 
      Bi207_Runs_1, Bi207_Runs_2, Bi207_Runs_3, Bi207_Runs_4
   };

   struct DataTakingPhase{
      struct RunRange {
         RunRange(int a, int b) { firstRun = a; lastRun = b; }
         int firstRun;
         int lastRun;
      };
      std::string phaseName;
      PhaseId phaseId;
      std::vector<RunRange> runRanges;
      void print(std::ostream& output) const {
         output 
            << " Phase name : " << phaseName
            << "\t Phase id : " << phaseId
            << "\t N run ranges : " << runRanges.size() << "\n";
         for (unsigned int i = 0; i < runRanges.size(); ++i) {
            output << "\t\t Range " << i 
               << " : [ " << runRanges[i].firstRun 
               << " , " << runRanges[i].lastRun << " ]\n";
         }
      }
      ~DataTakingPhase() { runRanges.clear(); }
   };

   // Possible Run sets:
   // GOOD_RUN = Status 1
   // OK_RUN = Possibly good runs, exclude statuses 1,2,5,4,1000,6,100000,
   //                                    10000,20000,100000000,1000000000
   // NOAIR_RUN = Ventillation off (status 6 & 100000)
   // AFTER_EC_RUN = After absolute calibration (4 & 1000)
   // HV_RUN = Runs with HV problems, statuses 5 ,10000 ,20000 ,100000000, 1000000000
   // ALL_BUT_BAD_RUN = all except statuses 0, 6, 7, 100000
   // STANDARD_RUN = runs from starndard runlist, decided at Feb'07 Orsay analysis 
   // meeting. See meeting minutes.
   enum RunStatusClass {
     GOOD_RUN, OK_RUN, NOAIR_RUN, 
     AFTER_EC_RUN, HV_RUN, ALL_BUT_BAD_RUN, 
     STANDARD_RUN, BB0NU_RUN, BI207_RUNS
   };
    
   struct RunStatusClassCondition {
      ~RunStatusClassCondition() { 
         includedStates.clear(); 
         excludedStates.clear(); 
      }
      RunStatusClass statusId;
      std::vector<int> includedStates;
      std::vector<int> excludedStates;      
   };
    
   struct RunInfo {
      int number;
      int length;
      long generatedEvents;
      int observedEvents;
      int status;
      float activity;
      bool accepted;
      double deadTime;
      long assignedEvents;
   };
    
   //------------------------------------------------------------
   // Constructor and Destructor
   //------------------------------------------------------------
   RunStatusController(const std::string theName = "RunStatusController",
                     const std::string theDecription = 
                     "Manages the list of runs and provides run status informations to the pipeline");
   virtual ~RunStatusController();

   //-------------------------------------------------------------------------
   // Operations
   //-------------------------------------------------------------------------
   AppResult beginJob(AppEvent* aJob);
   AppResult beginRun(AppEvent* aRun);
   AppResult event(AppEvent* anEvent);
   AppResult endRun(AppEvent* aRun);
   AppResult endJob(AppEvent* aJob);

   //-------------------------------------------------------------------------
   // Accessors
   //-------------------------------------------------------------------------
   static const RunStatusController* instance();

   void setUseListFromFile(const bool aValue)  { useListFromFile_ = aValue; }
   void setUseRecoRunList(const bool aValue)   { useRecoRunList_  = aValue; }

   void setRunListFileName(const std::string aValue) {
     runListFileName_ = aValue;
   }
   void setRecoRunListFileName(const std::string aValue) {
     recoRunListFileName_ = aValue;
   }

   void setServerName(const std::string val) { serverName_ = val; }
   void setPort(const int val)               { port_ = val; }
   void setSocket(const std::string val)     { socket_ = val;}
   void setDbName(const std::string val)     { dbName_ = val;}
   void setUserName(const std::string val)   { userName_ = val; }
   void setPassword(const std::string val)   { password_ = val; }

   void addRequiredRunStatus(RunStatusClass aRunClass);
   void removeRequiredRunStatus(RunStatusClass aRunClass);

   void addRequiredDataTakingPhase(PhaseId aPhaseId);
   void removeDataTakingPhase(PhaseId aPhaseId);

   bool checkPhase(PhaseId aPhase) ;
   bool checkStatus(RunStatusClass aStatus) ;

   void setLoadRunSummary(const bool aValue) { loadBetaBetaRunSummary_ = aValue; }

   void setUseAssignedEventsFile(const bool aValue) {
      useAssignedEventsFile_ = aValue;
   }
   void setAssignedEventsFileName(const std::string aValue) {
      setUseAssignedEventsFile(true);
      assignedEventsFileName_ = aValue;
   }

   // 16/10/12 - JEM
   void setCorrectBadDeadTimes(const bool aValue){
      correctBadDeadTimes_ = aValue;
   }

   //-------------------------------------------------------------------------
   // Accessors to run informations
   //-------------------------------------------------------------------------
   bool currentRunIsAccepted() const { return currentRunIsAccepted_; }
   int  runStatus() const { return runInfos_.find(currentRun_)->second.status; }
   int  runLength() const { return runInfos_.find(currentRun_)->second.length; }
   long runGeneratedEvents() const {
      return runInfos_.find(currentRun_)->second.generatedEvents;
   }
   int  runObservedEvents() const { 
      return runInfos_.find(currentRun_)->second.observedEvents;
   }
   float  runActivity() const { return runInfos_.find(currentRun_)->second.activity; }
   double runDeadTime() const { return runInfos_.find(currentRun_)->second.deadTime; }
   int    runAssEvents() const { return runInfos_.find(currentRun_)->second.assignedEvents; }

   int totalRunTime() const;
   int totalAccRunTime() const;

   int totalRecoTime() const;
   int totalAccRecoTime() const;

   double totalDeadTime() const; 
   double totalAccDeadTime() const;

   long totalAssignedEvents() const;
   long totalAccAssignedEvents() const;

   long maxGeneratedEvents() const;

   // 11/10/12 - JEM
   int totalAccRunTime(std::string phase) const;
   double meanActivity(std::string phase) const;
   // 14/11/12 - JEM
   double totalAccDeadTime(std::string phase) const;
   int totalAccRecoTime(std::string phase) const;

   // 01/11/13 - JEM
   TTimeStamp runStart() const;

   // 09/10/2012 - ST
   const RunSummaryTable* runDataTable() const {return runTable_; };

private:
   static RunStatusController* runControl_;
   const NemoDataBaseManager* db_;
   const N3DbInterfaceModule* n3db_;

   void addPhase(DataTakingPhase aPhase);
   void addRunStatusCondition(RunStatusClassCondition aCondition);
   bool checkStatusBits(int runStatus, int aStatus);

   // 09/10/2012 - ST
   AppResult loadBetaBetaRunSummary();
   AppResult readEventsAssignedPerEvents();

   bool useListFromFile_;
   bool useN3Db_;
   std::string runListFileName_;

   std::map<RunStatusClass, RunStatusClassCondition>   runStatesDictionary_;
   std::map<PhaseId, DataTakingPhase>                  phasesDictionary_;
   std::vector<RunStatusClass>                         requiredRunStates_;
   std::vector<PhaseId>                                requiredPhases_;
   std::map<int, RunInfo>                              runInfos_;
   std::vector<int>                                    listOfRuns_;

   std::map<int, RunInfo>                              recoRunInfos_;
   bool useRecoRunList_;
   std::string recoRunListFileName_;

   bool currentRunIsAccepted_;
   int  currentRun_;    
   int  lastRun_;    

   // 09/10/2012 - ST
   bool          loadBetaBetaRunSummary_;
   MYSQL         mySqlConnection_;
   bool          isConnected_;
   int           maxConnectinAttempts_;
   int           port_;
   std::string   serverName_;
   std::string   socket_;
   std::string   dbName_;
   std::string   userName_;
   std::string   password_;

   RunSummaryTable* runTable_;
   std::string   assignedEventsFileName_;
   bool          useAssignedEventsFile_;
   std::map<unsigned int, unsigned int> assignedEventsMap_;

   // 16/10/12 - JEM
   bool correctBadDeadTimes_;

   // 24/10/13 - CV (for jobSummary.xml)
   bool isMC;
};

std::ostream& operator << (std::ostream& os, 
                           const RunStatusController::DataTakingPhase& obj);

#endif
