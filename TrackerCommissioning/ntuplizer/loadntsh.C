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
  cout << "\nStarting up...\n\n" << endl;
  ntsh dis;
  dis.show();
  dis.zoom();
}
