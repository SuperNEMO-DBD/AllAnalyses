//
//  NemorHeader.h
//
//  Created by Stefano Torre on 26/04/12.
//
#ifndef SUPERNEMO_NEMORHEADER_H_
#define SUPERNEMO_NEMORHEADER_H_

#include "Edm/StorableObject.h"
#include "Edm/ConstHandle.h"
#include "Edm/Handle.h"
#include "Edm/Link.h"
#include "Edm/ConstLink.h"

#include <iostream>

#include "TTimeStamp.h" // cv - 7/3/13: Use ROOT class to store event timestamp

class NemorHeader;

typedef Handle<NemorHeader> NemorHeader_h;
typedef ConstHandle<NemorHeader> NemorHeader_ch;
typedef Link<NemorHeader> NemorHeader_l;
typedef ConstLink<NemorHeader> NemorHeader_cl;

class NemorHeader : public StorableObject {
public:
    //-------------------------------------------------------------------------
    // Constructors
    //-------------------------------------------------------------------------
    NemorHeader();
    NemorHeader(const NemorHeader& obj);
    NemorHeader& operator=(const NemorHeader& obj);
    
    //-------------------------------------------------------------------------
    // Destructor
    //-------------------------------------------------------------------------
    virtual ~NemorHeader() {};

    //-------------------------------------------------------------------------     
    // Getters and Setters
    //-------------------------------------------------------------------------
    int     runDuration() const;
    int     numberOfGeneratedEvents() const;
    double  scintillationTime() const;
    TTimeStamp  eventTimeStamp() const;
    
    void setRunDuration(int aRunDuration);
    void setNumberOfGeneratedEvents(int aNumber);
    void setScintillationTime(double aValue);
    void setEventTimeStamp(int evntime, int date);
    void setEventTimeStamp(TTimeStamp aTimeStamp);

    //-------------------------------------------------------------------------
    // Print
    //-------------------------------------------------------------------------
    void print(std::ostream & output = std::cout) const;
    
    //-------------------------------------------------------------------------
    // Classifiers
    //-------------------------------------------------------------------------
    std::string class_name(void) const;
    Version_t class_version(void) const;

private:
    int runDuration_;  
    int numberGeneratedEvents_;
    TTimeStamp eventTimeStamp_;
    double scintillationTime_;
    ClassDef(NemorHeader, 1);
};

std::ostream& operator << (std::ostream& os, const NemorHeader& obj);

#ifndef __CINT__
inline int NemorHeader::runDuration() const {
    return runDuration_;
}

inline void NemorHeader::setRunDuration(int aRunDuration) {
    runDuration_ = aRunDuration;
}

inline int NemorHeader::numberOfGeneratedEvents() const {
    return numberGeneratedEvents_;
}

inline void NemorHeader::setNumberOfGeneratedEvents(int aNumber) {
    numberGeneratedEvents_ = aNumber;
}

inline double NemorHeader::scintillationTime() const {
    return numberGeneratedEvents_;
}

inline void NemorHeader::setScintillationTime(double aValue) {
    scintillationTime_ = aValue;
}

inline TTimeStamp NemorHeader::eventTimeStamp() const {
  return eventTimeStamp_;
}

inline void NemorHeader::setEventTimeStamp(TTimeStamp aTimeStamp) {
  eventTimeStamp_ = aTimeStamp;
}

#endif

#endif
