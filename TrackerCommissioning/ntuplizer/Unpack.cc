// Unpack.cc
//
//  Author: R. Beuselinck, Imperial College London
// Created: 20110512
//
#include "Unpack.h"
#include "rawkeys.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "mapping_anode_only.h" // I hate this code more than I can say!

Unpack::Unpack()
{
  _rawFile = 0;
  _iOpened = false;
  init();
}

Unpack::Unpack(std::ifstream& infile)
{
  _rawFile = &infile;
  _iOpened = false;
  init();
}

Unpack::Unpack(const std::string& fname)
{
  _rawFile = new std::ifstream(fname.c_str());
  _iOpened = true;
  init();
}

Unpack::~Unpack()
{
  if (_iOpened) _rawFile->close();
}

void Unpack::init()
{
  // finish initialisation for constructors.
  //
  _haveLine = false;
  _inEvent = false;
  _completedEvent = false;
  _line = "";
  _trigDriftDelay = -1.0;
  _alphaRegister = -1.0;
  _dateStamp = "";
  for (int i=0; i<14; i++) _csmap[i] = i; // default: no re-mapping.
  for (int i=14; i<20; i++) _csmap[i] = -1;
}

Unpack::status Unpack::getNextEvent(GeigerEvent& ev)
{
  // This is the main user interface. Unpack the next event from the input file
  // and return a reference to the caller.
  //
  _completedEvent = false;
  _errors.clear();
  status ret, retf = OK;
  while (!_completedEvent)
  {
    try
    {
      ret = parseNextRecord();
      if (ret == END)
      {
        _event.newEvent(-9999);
        ev = _event;
        return ret;
      }
      if (ret != OK) retf = ret;
    }
    catch (std::exception &e)
    {
      // handle logic_error, skip rest of current event.
      std::stringstream ss;
      ss << "Exception thrown during getNextEvent!! "
          << e.what() << "\nSkipping rest of the event..." << std::endl;
      int key = kD0;
      while (key == kD0 || key == kD1) key = whichKey(nextLine());
      _myHit = RawGeigerHit();  // ensure we leave things in a clean state.
      retf = BAD_SYNC;
      _errors.add(retf, ss.str());
    }
  }
  ev = _event;
  return retf;
}

std::string Unpack::nextLine()
{
  if (_haveLine) return _line;  // reuse buffered line.
  if (_rawFile) std::getline(*_rawFile, _line);
  return _line;
}

Unpack::status Unpack::parseNextRecord()
{
  // Get the next record and invoke the relevant parsing method.
  // If we are currently processing an event and detect a new Event tag push the
  // record back and call the end of event method.
  //
  status ret = OK;
  if (!_rawFile->eof())
  {
    std::string s = nextLine();
    int theKey = whichKey(s);
    if (theKey == kTRIGCONF) ret = setTrig(s);
    else if (theKey == kCSMAP) ret = parseSectorMap(s);
    else if (theKey == kRUNSTART) ret = parseRunStart(s);
    else if (theKey == kEvent) ret = parseEvent(s);
    else if (theKey == kD0) ret = parseD0(s);
    else if (theKey == kD1) ret = parseD1(s);
    else if (theKey == kENDRUN) ret = parseEndRun(s);

    return ret;
  }
  else return END; // end of file reached.
}

Unpack::status Unpack::getTrigConfig()
{
  // This method may be called before the first event. The intention is to
  // process input until a valid TRIGCONF card is reached.
  // If we see the first event before we have reached a TRIGCONF return a
  // bad status.
  //
  // However, if you don't care at all then you don't need to call this method.
  // Then it won't matter if there is no TRIGCONF.
  //
  if (_trigDriftDelay > 0.0) return OK; // already done.
  while (_trigDriftDelay < 0.0)
  {
    status ret = parseNextRecord();
    if (ret != OK) return ret;
  }
  return OK;
}

Unpack::status Unpack::parseSectorMap(std::string s)
{
  // Decode the CSMAP card specifying VME card to detector sector mapping.
  //
  std::istringstream cstr(s, std::ios_base::in);
  std::string key;
  cstr >> key;
  for (int i=0; i<20; i++) _csmap[i] = -1;  //set all slots as unused.
  for (int i=0; i<14; i++)
  {
    int slot;
    cstr >> slot;
    if (slot != -1) _csmap[slot] = i; // readout (slot) -> C-section sector (i).
  }
}

Unpack::status Unpack::setTrig(std::string s)
{
  // Unpack the TRIGCONF data.  The hitmask fields are ignored here.
  // This assumes a fixed 20ns binning on all TDCs.
  //
  std::istringstream cstr(s, std::ios_base::in);
  int delay, alpha;
  std::string key;
  cstr >> key;
  try
  {
    delay = getHexValue(cstr, s);
    alpha = getHexValue(cstr, s);
    getHexValue(cstr, s);  // just to check for error in previous item!
  }
  catch (std::exception &e)
  {
    std::stringstream ss;
    ss << "Bad TRIGCONF data: " << e.what() << std::endl;
    _errors.add(BAD_TRIG, ss.str());
    return BAD_TRIG;
  }
  _trigDriftDelay = delay/1000.;  // micro-seconds.
  _alphaRegister = alpha/1000.;
  return OK;
}

Unpack::status Unpack::parseRunStart(std::string /*s*/)
{
  // std::cout << "Processing RUNSTART" << std::endl;
  return OK;
}

Unpack::status Unpack::parseEvent(std::string s)
{
  if (_inEvent)
  {
    _haveLine = true;
    _inEvent = false;
    _completedEvent = true;
  }
  else
  {
    _inEvent = true;
    _haveLine = false;
    _completedEvent = false;
    std::string key;
    int eventNumber;
    std::istringstream cstr(s, std::ios_base::in);
    cstr >> key >> eventNumber;
    _event.newEvent(eventNumber); // reset to a new event.

    // Get the rest of the line as a single string
    std::getline(cstr, _dateStamp);
    // std::cout << "\nProcessing Event " << eventNumber
    //           << " written at " << dateStamp << std::endl;
  }

  // sanity check
  //
  if (_trigDriftDelay < 0.0)
  {
    std::stringstream ss;
    ss << "\nWARNING: Event record seen before valid TRIGCONF!!"
      << std::endl;
    _errors.add(BAD_SYNC, ss.str());
    return BAD_SYNC;
  }
  return OK;
}

Unpack::status Unpack::parseD0(std::string s)
{
  if (!_inEvent) throw std::logic_error("Unexpected TDC D0 card");
  std::istringstream cstr(s, std::ios_base::in);
  std::string key, sASIC;
  cstr >> key >> sASIC;
  int ASIC, oASIC;
  std::istringstream is(sASIC, std::ios_base::in);
  is >> ASIC;  //  card*100 + asic_id*10 + ch_id
  int ch_id, asic_id, card, sector;
  oASIC = ASIC; // save this to add to hit.
  ch_id   = ASIC%10;  ASIC /= 10;
  asic_id = ASIC%10;  ASIC /= 10;
  card    = ASIC%100;
  sector = _csmap[card];  // possible HV card to sector remapping.
  if (sector == -1) throw std::out_of_range("Card not mapped to a sector");

  // attempt to decode this cryptic nonsense.
  //
  int col, row;
  Geiger_to_cassette(asic_id, ch_id, col, row);
  /* ------------ debugging --------------------------------------
  std::cout << s << "\nD0 h/w address (ch_id, asic_id, card): "
    << ch_id << ", " << asic_id << ", " << card << std::endl
    << "--> (col, row): " << col << ", " << row
    << " --> (layer, column): " << 9-row << ", " << 4*card + col << std::endl;

  // NB. Following field will not be filled in production.
  //
  int address;  // physical address, Geiger cell address.
  try
  {
    // getHexValue(cstr, s);  // this was merely skipping the ASIC field.
    address = getHexValue(cstr, s);
    if (!cstr.eof()) throw std::invalid_argument(s.c_str());
  }
  catch (...)
  {
    std::stringstream ss;
    ss << "Skip Bad hit: " << s << std::endl;
    // Dump the next line which should be a D1 card
    //
    ss << "Ignoring: " << nextLine() << std::endl;
    _errors.add(BAD_HIT, ss.str());
    return BAD_HIT;
  }
  int column, layer, side, module;  // these are packed into address, DocB 1570
  column = address & 0x7f; address >>= 7;
  layer  = address & 0xf;  address >>= 4;
  side   = address & 0x1;  address >>= 1;
  module = address & 0xf;
  std::cout << "D0 phy address (side, layer, column): "
    << side << ", " << layer << ", " << column << std::endl;
  ----------- end debugging --------------------------------------*/

  int column, layer, side, module;
  side = 1; module = 0;  // commissioning doesn't bother with these.
  layer = 9 - row;    // manchester: 1->9 , commissioning: 8->0.
  if (layer == 9) {std::cout << asic_id << " " << ch_id << " " << col << " " << row << std::endl;}
  column = 4*sector + col;  // using card to sector map.
  _myHit.setAddress(module, side, layer, column, oASIC);
  return OK;
}

Unpack::status Unpack::parseD1(std::string s)
{
  if (!_inEvent) throw std::logic_error("Unexpected TDC D1 card");
  std::istringstream cstr(s, std::ios_base::in);
  std::string key;
  int stat, anode, cathodeT, cathodeB, alpha; // ASIC status + 4 TDC values.
  cstr >> key;
  try
  {
    // assume we have to use only the lowest 12 bits of the TDC values
    // and the rest are nonsense.
    //
    stat = 0xfff & getHexValue(cstr, s);
    anode = 0xfff & getHexValue(cstr, s);
    cathodeT = 0xfff & getHexValue(cstr, s);
    cathodeB = 0xfff & getHexValue(cstr, s);
    alpha = 0xfff & getHexValue(cstr, s);
    if (!cstr.eof()) throw std::invalid_argument(s.c_str());
  }
  catch (...)
  {
    std::stringstream ss;
    ss << "Skip Bad hit: " << s << std::endl;
    _errors.add(BAD_HIT, ss.str());
    _myHit.setData(0, 0, 0, 0, 0); // this is just to avoid a half-baked hit.
    return BAD_HIT;
  }
  _myHit.setData(anode, cathodeT, cathodeB, alpha, stat);
  _event.addHit(_myHit);
  return OK;
}

Unpack::status Unpack::parseEndRun(std::string /*s*/)
{
  if (_inEvent)
  {
    _completedEvent = true;
  }
  // std::cout << "Processing ENDRUN" << std::endl;
  return OK;
}

int Unpack::getHexValue(std::istringstream& cstr, std::string& s)
{
  int value(0);
  cstr >> std::hex >> value;
  if (cstr.fail()) throw std::invalid_argument(s.c_str());
  return value;
}
