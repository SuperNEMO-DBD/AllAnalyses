#define EventGenerator_cxx
#include "EventGenerator.h"

using namespace std;

void EventGenerator::GenerateEvents(int nEvents){

   for (Int_t ev = 0; ev < nEvents; ev++) {
      cout << "event " << ev << endl;

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

      GenerateEvent(ev);

      tree->Fill();
      if (ev <3) tree->Show(ev);
   }


   tree->Write();
   tree->Print();
   delete file;

}

//returns a randomly generated cosmic ray gradient with the angle following the function cosmicDistribution
void EventGenerator::GenerateEvent(int evno){

  TVector3 *rayVector = new TVector3(0,0,0);
  TVector3 *endPoint = new TVector3(0,0,0);

  GenerateRay(rayVector);
  GenerateEndPoint(endPoint);

/*  TPolyLine3D *track3D = new TPolyLine3D(2);

  track3D->SetNextPoint(endPoint[0],endPoint[1],scZOffset);
  track3D->SetNextPoint(endPoint[0]+rayVector[0]*500,endPoint[1]+rayVector[1]*500,rayVector[2]*500-scZOffset);
  track3D->SetLineWidth(3);
  track3D->SetLineStyle(9);
  track3D->SetLineColor(kGray+2);
  track3D->Draw("same");*/

  Int_t track_index = gGeoManager->AddTrack(1,13);
  TVirtualGeoTrack *track = gGeoManager->GetTrack(track_index);
  track->AddPoint(endPoint->X(),endPoint->Y(),endPoint->Z(),0);

  gGeoManager->InitTrack(endPoint->X(),endPoint->Y(),endPoint->Z(),rayVector->X(),rayVector->Y(),rayVector->Z());
  gGeoManager->FindNextBoundary();
  gGeoManager->Step();

  int nHits=0;

  Double_t *glob_pt;

  while (!(gGeoManager->IsOutside())){
    nHits++;
    glob_pt = (double *)gGeoManager->GetCurrentPoint();
    track->AddPoint(glob_pt[0],glob_pt[1],glob_pt[2],nHits);

    int cellNum = gGeoManager->GetCurrentNode()->GetNumber();
    int column = cellNum%numColumns;
    int layer = cellNum/numColumns;

    TVector3 cellPos(column*cellWidth + cellWidth/2, 0 , layer*cellWidth + cellWidth/2);
    TVector3 yVec(0,1,0);

    double driftDist = TMath::Abs((*endPoint - cellPos).Dot(rayVector->Cross(yVec)));

    v_module->push_back(0);
    v_side->push_back(0);
    v_asicval->push_back(0);
    v_asicstat->push_back(0);
    v_anode->push_back(0);
    v_cattop->push_back(0);
    v_catbot->push_back(0);
    v_alpha->push_back(0);

    v_layer->push_back(layer);
    v_column->push_back(column);

    v_r->push_back(driftDist);

    v_time->push_back(driftModel->GetX(driftDist));

    v_z->push_back(glob_pt[1]);

    evnum = (ULong64_t)evno;
    evtime = (ULong64_t)evno;
    runnum = 1000;

    gGeoManager->FindNextBoundary();
    gGeoManager->Step();
  }

  if (nHits > 0) track->AddPoint(glob_pt[0]+rayVector->X()*500,glob_pt[1]+rayVector->Y()*500,glob_pt[2]+rayVector->Z()*500,nHits);
  gGeoManager->DrawTracks();

}


//returns a randomly generated cosmic ray gradient with the angle following the function cosmicDistribution
//void EventGenerator::GenerateRay(double *rayVector){
void EventGenerator::GenerateRay(TVector3 *rayVector){

  double alpha = cosmicDistribution->GetRandom();
  double beta = cosmicDistribution->GetRandom();

  rayVector->SetXYZ(TMath::Sin(alpha)*TMath::Cos(beta),TMath::Sin(beta),TMath::Cos(alpha)*TMath::Cos(beta));

}

//returns a randomly generated (y,z) coordinate (in cm) for the cosmic hit position on the scintillator plane
void EventGenerator::GenerateEndPoint(TVector3 *endPoint){

  endPoint->SetXYZ(random->Uniform(100) + scXOffset - 50,random->Uniform(100) + scYOffset - 50,scZOffset);

}

