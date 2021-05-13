// RootEventBuilder.C
// Author: Mathieu Bongrand <bongrand@lal.in2p3.fr>
// Copyright: 2018 (C) SoLid - LAL (IN2P3/CNRS)

// root 'RootEventBuilder.C("data/test1/RunData_12042018_13h36min27s_test1_Ascii.dat")'
// root 'RootEventBuilder.C("data/RunData_12042018_15h22min33s_Reflecto_Ascii/RunData_12042018_15h22min33s_Reflecto_Slot0_Ascii/RunData_12042018_15h22min33s_Reflecto_Slot0_Ascii.dat")'

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

#include "TFile.h"
#include "TROOT.h"

using namespace std;

//----------------------------//

struct pulse_t
{
  int slot;
  int channel;
  uint16_t lto;
  uint16_t ht;
  int time;
  double amplitude;
  double charge;
  double baseline;

  void clear ()
  {
    slot = 0;
    channel = 0;
    time = 0;
    lto = 0;
    ht = 0;
    amplitude = 0.0;
    charge = 0.0;
    baseline = 0.0;
  }
};

//----------------------------//

void RootEventBuilder (std::string filename_)
{
  const double tdc_to_ns = 0.390625;
  const double adc_to_mv = 0.610351563;

  // Read data file :

  ifstream file;

  file.open (filename_);

  if (!file.is_open ())
    {
      cerr << "ERROR: file isn't open !" << endl;
      return;
    }

  bool read_pulses = false;

  size_t pulse_read = 0;
  std::vector<pulse_t> pulse_list;

  while (!file.eof ())
    {
      if (pulse_read % 10000 == 0) cout << "Read pulse: " << pulse_read << endl;

      //if (pulse_read > 100) break;

      string file_line;
      getline (file, file_line);

      ostringstream oss_slot_channel;
      oss_slot_channel << "Slot ";

      // read the event:

      pulse_t new_pulse;
      new_pulse.clear ();

      size_t event_found = file_line.find (oss_slot_channel.str ());
      if (event_found != std::string::npos)
	{
	  string slot_str, channel_str, lt0_str, ht_str;
	  int slot, channel, lto, ht;

	  istringstream iss_line (file_line);
	  iss_line >> slot_str >> slot >> channel_str >> channel >> lt0_str >> lto >> ht_str >> ht;

	  string pulse_line;
	  getline (file, pulse_line);

	  istringstream iss_pulse (pulse_line);

	  int isample = 0;
	  double amplitude = 0.0, baseline = 0.0;
	  double time = 0.0, charge = 0.0;
	  double adc = 0.0;

	  vector<double> vec_adc;

	  while (iss_pulse >> adc >> ws)
	    {
	      vec_adc.push_back(adc);
	      if (isample < 150) baseline += adc;
	      isample++;
	    }

	  baseline /= 150.0;

	  size_t ibin = 1;
	  for (vector<double>::iterator it = vec_adc.begin(); it != vec_adc.end(); ++it)
	    {
	      double iamplitude = (*it - baseline)  * adc_to_mv;

	      if (iamplitude < amplitude)
		{
		  amplitude = iamplitude;
		  time = ibin * tdc_to_ns;
		}
	      if (ibin > 150) charge += iamplitude;

	      ibin++;
	    }

	  new_pulse.slot = slot;
	  new_pulse.channel = channel;
	  new_pulse.lto = lto;
	  new_pulse.ht = ht;
	  new_pulse.time = time;
	  new_pulse.amplitude = amplitude;
	  new_pulse.charge = charge / 1000.0;
	  new_pulse.baseline = baseline;

	  pulse_list.push_back (new_pulse);

	}

      pulse_read++;
    }
  file.close();

  // Output tree:
  TFile *outfile = new TFile ("root_pulse_file.root", "recreate");
  TTree *pulses = new TTree ("pulses", "tree generated from ascii file");

  // Declaration of leaf types
  Int_t pulse_slot;
  Int_t pulse_channel;
  Int_t pulse_lto;
  Int_t pulse_ht;
  Double_t pulse_time;
  Double_t pulse_amplitude;
  Double_t pulse_charge;
  Double_t pulse_baseline;

  // Branches:
  pulses->Branch ("pulse_slot", &pulse_slot, "pulse_slot/I");
  pulses->Branch ("pulse_channel", &pulse_channel, "pulse_channel/I");
  pulses->Branch ("pulse_lto", &pulse_lto, "pulse_lto/I");
  pulses->Branch ("pulse_ht", &pulse_ht, "pulse_ht/I");
  pulses->Branch ("pulse_time", &pulse_time, "pulse_time/D");
  pulses->Branch ("pulse_amplitude", &pulse_amplitude, "pulse_amplitude/D");
  pulses->Branch ("pulse_charge", &pulse_charge, "pulse_charge/D");
  pulses->Branch ("pulse_baseline", &pulse_baseline, "pulse_baseline/D");

  for (vector<pulse_t>::iterator it = pulse_list.begin (); it != pulse_list.end (); ++it)
    {
      pulse_t a_pulse = *it;

      pulse_slot = a_pulse.slot;
      pulse_channel = a_pulse.channel;
      pulse_lto = a_pulse.lto;
      pulse_ht = a_pulse.ht;
      pulse_time = a_pulse.time;
      pulse_amplitude = a_pulse.amplitude;
      pulse_charge = a_pulse.charge;
      pulse_baseline = a_pulse.baseline;

      pulses->Fill ();
    }

  pulses->Write ();
  outfile->Close ();


}
