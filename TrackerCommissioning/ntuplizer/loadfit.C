{
  cout << "\n**************************************************\n"
       <<   "*                                                *\n"
       <<   "*   Nothing To See Here: loading ntsh            *\n"
       <<   "*                                                *\n"
       <<   "*   Simple event display for commissioning       *\n"
       <<   "*                                                *\n"
       <<   "**************************************************\n\n";
  gROOT->ProcessLine(".L CellGeom.C+");
  gROOT->ProcessLine(".L GHbase.C+");
  gROOT->ProcessLine(".L ntsh.C+");
  gROOT->ProcessLine(".L EasyTrack.C+");
  gROOT->ProcessLine(".L drawTracks.C");
  cout << "\nStarting up...\n\n" << endl;
  ntsh dis; // event display object
  EasyTrack tra(&dis);  // simple track fitter
  dis.setRot(-1);  // select MSSL orientation
  dis.wires(true); // select display of anode wires
  drawEvent(&dis, &tra);  // fit tracks and draw on standard event views.
  dis.zoom(true);    // select zoomed in view
  drawEvent(&dis, &tra);  // fit tracks and draw on standard event views.
  cout << "\nEvent display object is: dis\n"
       << "Track fitter is: tra\n\n"
       << "The display is currently zoomed and shown in MSSL orientation.\n"
       << "The displayed hits are clickable to view all associated data.\n"
       << "\nTo draw next event: drawNext(&dis, &tra);\n"
       << "To re-draw the current event: drawEvent(&dis, &tra);\n"
       << "To access a specified event: dis.GetEntry(evno);\n";
}
