// plotraw.cc - make plots from commissioning tracker raw data
//
//  Author: R. Beuselinck, Imperial College London
// Created: 20150104
//
#include "Unpack.h"
#include "DriftModel.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"

using namespace std;

double getHitZ(const RawGeigerHit& h);
time_t getEpoch(const string &stamp);

int main(int argc, char *argv[])
{
  if (argc < 2 )
  {
    cout << "Useage: ./plotraw input_file [anode_tdc_max]" << endl;
    return 1;
  }
  Unpack unp(argv[1]);  // file name specified on command line
  GeigerEvent ev;
  int tdc_max(0);
  if (argc == 3)
  {
    //  stringstream ss(argv[2]);
    //ss >> tdc_max;
  }

  // Check we have valid TRIGCONF data at the beginning.
  //
  if (unp.getTrigConfig() != Unpack::OK)
  {
    cout << "WARNING: valid TRIGCONF not found!!\n"
      << "Carrying on recklessly.\n" << endl;
  }
  double delay = unp.trigDelay();
  double alpha = unp.trigAlpha();
  cout << "Trigger delay (us): " << delay << endl
       << "Trigger alpha (us): " << alpha << endl;

  // setup drift model parameterisation
  //
  DriftModel drift;
  drift.setTDCRes(20.0);
  drift.setDelay(delay);

  // Set up root malarky.
  //
  gROOT->ProcessLine("#include <vector>");
  TFile *roof = new TFile("nothings.root", "recreate");
  TTree *tree = new TTree("raw", "Commissioning Raw Tracker Data"); 

  ULong64_t evnum, evtime;
  Int_t runnum;
  vector<int> *v_module = new vector<int>(10);
  vector<int> *v_side = new vector<int>(10);
  vector<int> *v_layer = new vector<int>(10);
  vector<int> *v_column = new vector<int>(10);
  vector<int> *v_asicval = new vector<int>(10);
  vector<int> *v_asicstat = new vector<int>(10);
  vector<int> *v_anode = new vector<int>(10);
  vector<int> *v_cattop = new vector<int>(10);
  vector<int> *v_catbot = new vector<int>(10);
  vector<int> *v_alpha = new vector<int>(10);
  vector<float> *v_time = new vector<float>(10);
  vector<float> *v_r = new vector<float>(10);
  vector<float> *v_z = new vector<float>(10);

  tree->Branch("evnum", &evnum, "evnum/l");
  tree->Branch("evtime", &evtime, "evtime/l");
  tree->Branch("runnum", &runnum, "runnum/I");
  tree->Branch("v_module", "vector<int>", &v_module);
  tree->Branch("v_side", "vector<int>", &v_side);
  tree->Branch("v_layer", "vector<int>", &v_layer);
  tree->Branch("v_column", "vector<int>", &v_column);
  tree->Branch("v_asicval", "vector<int>", &v_asicval);
  tree->Branch("v_asicstat", "vector<int>", &v_asicstat);
  tree->Branch("v_anode", "vector<int>", &v_anode);
  tree->Branch("v_cattop", "vector<int>", &v_cattop);
  tree->Branch("v_catbot", "vector<int>", &v_catbot);
  tree->Branch("v_alpha", "vector<int>", &v_alpha);
  tree->Branch("v_time", "vector<float>", &v_time);
  tree->Branch("v_r", "vector<float>", &v_r);
  tree->Branch("v_z", "vector<float>", &v_z);

  // Loop over events.
  //
  Unpack::status ret = Unpack::OK;
  int evno = -1;
  while (true)
  {
    ret = unp.getNextEvent(ev);
    if (ret == Unpack::END) break;
    evno = ev.evtNumber();
    if (ret != Unpack::OK)
    {
      cout << "WARNING: Bad status from event " << evno
          << " recorded at " << unp.getTimeStamp() << endl;
      cout << "Seconds since the Epoch: " << getEpoch(unp.getTimeStamp())
      << endl;
      const UnpackingErrors err = unp.getErrors();
      cout << "There are " << err.size() << " errors recorded" << endl;
      const UnpackingErrors::ErrorList el = err.getErrors();
      UnpackingErrors::ErrorList::const_iterator it = el.begin();
      for ( ; it != el.end(); ++it)
      {
        cout << "Error code: " << it->first << '\n'
            << "Error text: " << it->second;
      }
    }
    GeigerEvent::HitList hits = ev.getHits();
    GeigerEvent::HitList::iterator it = hits.begin();
    evnum = (ULong64_t) evno;
    evtime = (ULong64_t) getEpoch(unp.getTimeStamp());
    if (argc > 2) {
      runnum = (Int_t) atoi(argv[2]);
    } else
    {
      if (sscanf(argv[1],"MSSLTest%d.dat",&runnum) == 0) runnum=-1;
    }
    v_module->clear();
    v_side->clear();
    v_layer->clear();
    v_column->clear();
    v_asicval->clear();
    v_asicstat->clear();
    v_anode->clear();
    v_cattop->clear();
    v_catbot->clear();
    v_alpha->clear();
    v_time->clear();
    v_r->clear();
    v_z->clear();
    for ( ; it != hits.end(); ++it)
    {
      RawGeigerHit &rh = *it;
      int rh_m = rh.module();
      int rh_s = rh.side();
      int rh_l = rh.layer();
      int rh_c = rh.column();
      int rh_asv = rh.asicValue();
      int rh_ass = rh.asicStatus();
      int rh_an = rh.anodeTDC();
      int rh_ct = rh.cathodeTopTDC();
      int rh_cb = rh.cathodeBotTDC();
      int rh_al = rh.alphaTDC();
      double time;
      if (tdc_max == 0)
      {
        // stop time and delay taken from input data.
        //
        time =  drift.getDriftTime(rh);
      }
      else
      {
        // stop time specified on command line.
        //
        time = (tdc_max - rh_an)*20.;
        if (time < 0.) time = 0.; // keep all hits, even if nonsense.
      }
      double dr =  drift.getDist(time);
      double zhit = getHitZ(rh);
      v_module->push_back(rh_m);
      v_side->push_back(rh_s);
      v_layer->push_back(rh_l);
      v_column->push_back(rh_c);
      v_asicval->push_back(rh_asv);
      v_asicstat->push_back(rh_ass);
      v_anode->push_back(rh_an);
      v_cattop->push_back(rh_ct);
      v_catbot->push_back(rh_cb);
      v_alpha->push_back(rh_al);
      v_time->push_back(float(time));
      v_r->push_back(float(dr));
      v_z->push_back(float(zhit));
    }
    tree->Fill();
  }
  tree->Write();
  roof->Close();

  return 0;
}

double getHitZ(const RawGeigerHit& h)
{
  // Calculate the Z coordinate of the RawGeigerHit.
  // (This is copied from the static member hitCoords of EventViewer.)
  //
  // Calculate the physical location of a Geiger cell. (distances in cm).
  //
  const double pitch = 4.4;    // cell and anode wire pitch
  const double xoff = 1.4;     // offset from X wall (y=0)
  const double yoff = 1.0;     // offset from calorimeter wall (x=0)
  const double height = 290.;  // distance between top and bottom cathodes.
  const double zhalf = 0.5*height;  // set Z origin at the centre
  const int cattdcmax = 46666; // empirical!

  // Source foil lies in the y-z plane
  //
  //int module = h.module();  // ignoring this, always 0 for demonstrator.
  // int side = h.side();      // 0 = -ve X, 1 = +ve X.
  // int layer = h.layer();    // X index, 0 to 8.
  // int column = h.column();  // Y index, 0 to 112.

  // double x = (layer + 0.5)*pitch + xoff;
  // if (side == 0) x = -x;
  // double y = (column + 0.5)*pitch + yoff;

  // Calculate the z coordinate based on the top and bottom cathode tdc times
  // (assumed linear relation). Infer scale from cattdcmax if one of the tdc
  // values is missing.
  //
  int top = h.cathodeTopTDC();
  int bot = h.cathodeBotTDC();
  int updown;
  double z;
  if (top+bot == 0)
  {
    updown = -99; // no data
    z = -999.;
  }
  else if (top == 0)
  {
    updown = -1;
    z = (height*bot)/cattdcmax - zhalf;
  }
  else if (bot == 0)
  {
    updown = 1;
    z = height - (height*top)/cattdcmax - zhalf;
  }
  else
  {
    updown = 0;
    z = (height*bot)/(top+bot) - zhalf;
  }
  return z;
}

time_t getEpoch(const string &stamp)
{
  // Convert annoying ascii time stamp to seconds since the Epoch.
  //
  struct tm tm = {0};

  // Example: string stamp = "Tue Dec 16 00:35:27 2014";
  //
  string Swday, Smon, Shms;
  istringstream ss(stamp);
  ss >> Swday >> Smon >> tm.tm_mday >> Shms >> tm.tm_year;
  tm.tm_year -= 1900;

  // decode the month string.
  //
  static string smonths[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul",
      "Aug", "Sep", "Oct", "Nov", "Dec"};
  for (int i=0; i<12; i++) { if (Smon == smonths[i]) { tm.tm_mon = i; break; } }

  // replace ':' with ' ' in the hh:mm:ss field.
  //
  Shms[2] = ' ';
  Shms[5] = ' ';
  istringstream st(Shms);
  st >> tm.tm_hour >> tm.tm_min >> tm.tm_sec;
  tm.tm_isdst = -1;
  // tm_wday and tm_yday are ignored by mktime
  //
  time_t the_time = mktime(&tm);
  return the_time;
}
