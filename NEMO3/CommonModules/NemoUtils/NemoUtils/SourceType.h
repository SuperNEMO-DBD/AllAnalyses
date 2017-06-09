//
//  NemoSector.h
//
//  Created by Stefano Torre on 01/03/12.
//

#ifndef SOURCETYPE_H_
#define SOURCETYPE_H_
#include <string>

class SourceType {
public:
    // 0 -- mo metal
    // 1 -- mo composit
    // 2 -- se old from nemo 2
    // 3 -- se new sample for nemo3
    // 4 -- cd
    // 5 -- nd
    // 6 -- ca
    // 7 -- Zr
    // 8 -- Te-130
    // 9 -- Te natural
    // 10 -- Cu foil

    enum Code {
      MoMet, MoCom, SeOld, SeNew, Cd, Nd, Ca, Zr, Te130, TeNat, Cu, Calib, None, Error 
    };
    
    SourceType() : value_(Error) {
    }
    
    SourceType(Code x) : value_(x) {
        
    }
    
    SourceType (const SourceType& r) : value_(r.value_) {
        
    }
    
    SourceType& operator=(SourceType x) {
        value_ = x.value_;
        return *this;
    }
    
    bool operator==(Code x) const {
        return value_ == x;
    }
    
    bool operator==(const SourceType& r) const {
        return r.value_ == value_;
    }
    
    bool operator!=(Code x) const {
        return !operator==(x);
    }
    
    bool operator!=(const SourceType& r) const {
        return !operator==(r);
    }
    
    Code type() {
        return value_;
    }
    
    bool operator < (const SourceType& r) const {
        return (int)value_ < (int)r.value_;
    }
    
    
    bool operator >= (const SourceType& r) const {
        return !operator<(r);
    }
    
    bool operator > (const SourceType& r) const {
        return  (int)value_ > (int)r.value_;
    }
    
    bool operator <= (const SourceType& r) const {
        return  !operator>(r);
    }
    
private:
    Code value_;
};

#endif
