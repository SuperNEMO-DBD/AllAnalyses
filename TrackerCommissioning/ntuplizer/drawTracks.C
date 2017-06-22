void drawTracks(ntsh* eve, EasyTrack* tracker)
{
  int nt = tracker->nTracks();
  for (int i=0; i<nt; i++)
  {
    const EasyTrack::Track& t = tracker->getTrack(i);
    cout << "Track " << i << ": m=" << t.m << " c=" << t.c
      << " chisq=" << t.chisq << " mz=" << t.mz << " cz=" << t.cz << endl;

    // X-Y fit
    //
    double x1(45.), x2(0.0);
    double y1 = t.m*x1 + t.c;
    double y2 = t.m*x2 + t.c;
    eve->_xyCanvas->cd();
    TLine *lxy = eve->NTLine(x1,y1,x2,y2);
    lxy->SetLineColor(4);
    lxy->Draw();
    eve->_xyCanvas->Update();
    
    // X-Z fit
    //
    y1 = t.mz*x1 + t.cz;
    y2 = t.mz*x2 + t.cz;
    eve->_xzCanvas->cd();
    TLine *lxz = eve->NTLine(x1,y1,x2,y2);
    lxz->SetLineColor(4);
    lxz->Draw();
    eve->_xzCanvas->Update();
  }
}

void drawNext(ntsh* eve, EasyTrack* tracker)
{
  eve->next();
  drawEvent(eve, tracker);
}

void drawEvent(ntsh* eve, EasyTrack* tracker)
{
  eve->show();
  tracker->makeClusters();
  tracker->fitTracks();
  drawTracks(eve, tracker);
}
