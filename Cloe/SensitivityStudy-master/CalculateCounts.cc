// Author Cloé Girard-Carillo girardcarillo@lal.in2p3.fr
// Small macro to calculate the numbers of background and signal events expected for SN and HyperNEMO

#include <limits>
#include <string>
#include <iostream>

#include <TTree.h>
#include <TFile.h>
#include <TObject.h>
#include <TH1.h>
#include <TH2.h>

using namespace std;

double twobeta (string process, string isotope, string exposure) ;
double contaminations (string activity, string nucleus, string exposure) ;

const double Na = 6.022e23 ;
const double twonu_half_life = 9.39e19 ;
const double zeronu_half_life = 2.5e23 ;

void CalculateCounts(){

  // SuperNEMO
  double n_2nu_Se_SN = twobeta ("2nubb","82Se","demonstrator") ;
  double n_0nu_Se_SN = twobeta ("0nubb","82Se","demonstrator") ;
  double n_Tl_Se_SN = contaminations ("nominal","208Tl","demonstrator") ;
  double n_Bi_Se_SN = contaminations ("nominal","214Bi","demonstrator") ;
  double n_Rn_Se_SN = contaminations ("nominal","222Rn","demonstrator") ;
  cout << "SuperNEMO" << endl ;
  cout << "2nubb Se = " << n_2nu_Se_SN << endl ;
  cout << "0nubb Se = " << n_0nu_Se_SN << endl ;
  cout << "214Bi Se = " << n_Bi_Se_SN << endl ;
  cout << "208Tl Se = " << n_Tl_Se_SN << endl ;
  cout << "222Rn Se = " << n_Rn_Se_SN << endl ;

  // HyperNEMO
  double n_2nu_Se_HN = twobeta ("2nubb","82Se","detector") ;
  double n_0nu_Se_HN = twobeta ("0nubb","82Se","detector") ;
  double n_Tl_Se_HN = contaminations ("nominal","208Tl","detector") ;
  double n_Bi_Se_HN = contaminations ("nominal","214Bi","detector") ;
  double n_Rn_Se_HN = contaminations ("nominal","222Rn","detector") ;
  cout << "HyperNEMO" << endl ;
  cout << "2nubb Se = " << n_2nu_Se_HN << endl ;
  cout << "0nubb Se = " << n_0nu_Se_HN << endl ;
  cout << "214Bi Se = " << n_Bi_Se_HN << endl ;
  cout << "208Tl Se = " << n_Tl_Se_HN << endl ;
  cout << "222Rn Se = " << n_Rn_Se_HN << endl ;


}

double contaminations (string activity, string nucleus, string exposure){

  double act = 0. ;
  double year = 0. ;
  double mass = 0. ;
  double conv = 31.5e6 ;
  double level = 0. ;
  double volume_tracker = 0. ;

  if (exposure == "demonstrator") {
    year = 2.5 ;
    mass = 7. ;
    volume_tracker = 15.3 ;
  }
  else if (exposure == "detector") {
    year = 5. ;
    mass = 100. ;
    volume_tracker = 15.3*20 ;
  }

  if (activity == "nominal") {
    if (nucleus == "214Bi") {
      act = 2.e-6 ;
    }
    else if (nucleus == "208Tl") {
      act = 10.e-6 ;
    }
    else if (nucleus == "222Rn") {
      act = 0.15e-3 ;
    }
    else {
      cout << "wrong nucleus" << endl ;
    }
  }
  else if (activity == "measured") {
    if (nucleus == "214Bi") {
      act = 200.e-6 ;
    }
    else if (nucleus == "208Tl") {
      act = 50.e-6 ;
    }
    else if (nucleus == "222Rn") {
      act = 0.15e-3 ;
    }
    else {
      cout << "wrong nucleus" << endl ;
    }
  }
  else {
    cout << "wrong activity" << endl ;
  }

  if (nucleus == "214Bi" || nucleus == "208Tl") {
    level = act*conv*year*mass ;
  }
  else if (nucleus == "222Rn") {
    level = act*conv*year*volume_tracker ;
  }
  return level  ;
}

double twobeta (string process, string isotope, string exposure){

  double mass = 0. ;
  double year = 0. ;
  double mass_mol = 0. ;
  double twobeta_half_life = 0. ;

  if (exposure == "demonstrator") {
    mass = 7.e3 ;
    year = 2.5 ;
  }
  else if (exposure == "detector") {
    mass = 100e3 ;
    year = 5. ;
  }
  else {
    cout << "wrong exposure" << endl ;
  }

  if (isotope == "82Se") {
    mass_mol = 82. ;

    if (process == "2nubb") {
      twobeta_half_life = twonu_half_life ;
    }
    else if (process == "0nubb") {
      twobeta_half_life = zeronu_half_life ;
    }
    else {
      cout << "wrong process" << endl ;
    }

  }

  else if (isotope == "150Nd") {
    mass_mol = 150 ;

    if (process == "2nubb") {
      twobeta_half_life = 9.11e18 ;
    }
    else if (process == "0nubb") {
      twobeta_half_life = 6.e24 ;
    }
    else {
      cout << "wrong process" << endl ;
    }

  }

  else {
    cout << "wrong isotope" << endl ;
  }


  return Na*mass/mass_mol*log(2)*year/twobeta_half_life ;

}
