{
  gStyle->SetPaperSize(29.7, 20.);
  gROOT->ProcessLine(".L GHbase.C+");
  gROOT->ProcessLine(".L Plots.C+");

  Plots mon;
  mon.Loop();
  Long64_t nentries = mon.fChain->GetEntriesFast();

  TCanvas *c1 = new TCanvas("c1", "Tracker Commissioning Plots", 1000, 707);
  c1->Divide(3,3);
  for (int i=0; i<9; i++)
  {
    c1->cd(i+1);
    mon.occu[i]->Draw();
  }
  c1->Print("test.pdf(","Title:Occupancy");

  c1->Clear();
  c1->Divide(3,3);
  for (int i=0; i<9; i++)
  {
    c1->cd(i+1);
    mon.occu[i]->Scale(1./nentries);
    mon.occu[i]->GetYaxis()->SetTitle("counts per event");
    mon.occu[i]->Draw();
  }
  c1->Print("test.pdf","Title:Occupancy/#events");

  c1->Clear();
  c1->Divide(3,3);
  for (int i=0; i<9; i++)
  {
    c1->cd(i+1);
    mon.anod[i]->Draw();
  }
  c1->Print("test.pdf","Title:Anode TDC");

  c1->Clear();
  c1->Divide(3,3);
  for (int i=0; i<9; i++)
  {
    c1->cd(i+1);
    mon.topc[i]->Draw();
  }
  c1->Print("test.pdf","Title:Top Cathode TDC");

  c1->Clear();
  c1->Divide(3,3);
  for (int i=0; i<9; i++)
  {
    c1->cd(i+1);
    mon.botc[i]->Draw();
  }
  c1->Print("test.pdf","Title:Bottom Cathode TDC");

  c1->Clear();
  c1->Divide(3,3);
  for (int i=0; i<9; i++)
  {
    c1->cd(i+1);
    mon.zpos[i]->Draw();
  }
  c1->Print("test.pdf","Title:Z Position");

  c1->Clear();
  c1->Divide(3,3);
  for (int i=0; i<9; i++)
  {
    c1->cd(i+1);
    mon.rpos[i]->Draw();
  }
  c1->Print("test.pdf)","Title:R Position");
}
