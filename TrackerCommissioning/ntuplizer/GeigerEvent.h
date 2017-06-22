#ifndef GEIGEREVENT_HPP
#define GEIGEREVENT_HPP
// GeigerEvent.h
//
// Simple container class for a collection of Geiger Hits from one event.
//
//  Author: R. Beuselinck, Imperial College London
// Created: 20110512
//
#include "RawGeigerHit.h"
#include <list>

class GeigerEvent
{
  public:
    typedef std::list<RawGeigerHit> HitList;

    GeigerEvent();  // does almost nothing.

    // event construction methods
    //
    void newEvent(int evno);
    void addHit(const RawGeigerHit &hit);

    // event access methods
    //
    int evtNumber() const { return _evtNum; }
    const HitList& getHits() const { return _hits; }

  private:
    int _evtNum; // event number from DAQ.
    HitList _hits;
};

#endif    /* GEIGEREVENT_HPP */
