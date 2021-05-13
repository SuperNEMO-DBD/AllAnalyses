
void summary_masses()
{
  gStyle->SetOptStat(0);
  TH1F* summary_17kgan_nominal  = new TH1F("summary_17kgan_nominal" ,"",4,0,4);
  TH1F* summary_17kgan_no_bkg   = new TH1F("summary_17kgan_no_bkg"  ,"",4,0,4);
  TH1F* summary_17kgan_real     = new TH1F("summary_17kgan_real"    ,"",4,0,4);
  TH1F* summary_500kgan_nominal = new TH1F("summary_500kgan_nominal","Half lifes summary",4,0,4);

  summary_500kgan_nominal->SetBinContent(1,4.91E25);
  summary_500kgan_nominal->SetBinContent(2,4.25E25);
  summary_500kgan_nominal->SetBinContent(3,2.44E25);
  summary_500kgan_nominal->SetBinContent(4,2.84E25);
  // summary_500kgan_nominal->SetFillColorAlpha(kViolet, 0.1);
  summary_500kgan_nominal->SetLineColor(kViolet);
  summary_500kgan_nominal->GetYaxis()->SetRangeUser(1E24, 1E26);
  summary_500kgan_nominal->GetXaxis()->SetBinLabel(1,"Se82 with B");
  summary_500kgan_nominal->GetXaxis()->SetBinLabel(2,"Se82 no B");
  summary_500kgan_nominal->GetXaxis()->SetBinLabel(3,"Nd150 with B");
  summary_500kgan_nominal->GetXaxis()->SetBinLabel(4,"Nd150 no B");
  summary_500kgan_nominal->GetYaxis()->SetTitle("Half life (y)");

  summary_17kgan_nominal->SetBinContent(1,5.68E24);
  summary_17kgan_nominal->SetBinContent(2,7.59E24);
  summary_17kgan_nominal->SetBinContent(3,2.20E24);
  summary_17kgan_nominal->SetBinContent(4,2.87E24);
  // summary_17kgan_nominal->SetFillColorAlpha(kBlue, 0.1);
  summary_17kgan_nominal->SetLineColor(kBlue);

  summary_17kgan_real->SetBinContent(1,3.69E24);
  summary_17kgan_real->SetBinContent(2,4.44E24);
  summary_17kgan_real->SetBinContent(3,2.20E24);
  summary_17kgan_real->SetBinContent(4,1.30E24);
  // summary_17kgan_real->SetFillColorAlpha(kRed, 0.1);
  summary_17kgan_real->SetLineColor(kRed);

  summary_17kgan_no_bkg->SetBinContent(1,5.68E24);
  summary_17kgan_no_bkg->SetBinContent(2,7.59E24);
  summary_17kgan_no_bkg->SetBinContent(3,2.20E24);
  summary_17kgan_no_bkg->SetBinContent(4,2.87E24);
  // summary_17kgan_no_bkg->SetFillColorAlpha(kGreen, 0.1);
  summary_17kgan_no_bkg->SetLineColor(kGreen);


  TLegend* l = new TLegend(0.6,0.6,0.9,0.8);
  l->AddEntry(summary_17kgan_nominal , "17.5 kg.an - nominal bkg");
  // l->AddEntry(summary_17kgan_no_bkg  , "17.5 kg.an - no bkg");
  l->AddEntry(summary_17kgan_real    , "17.5 kg.an - real bkg");
  l->AddEntry(summary_500kgan_nominal, "500 kg.an - nominal bkg");

  TGaxis::SetMaxDigits(2);
  TCanvas* c = new TCanvas();
  c->SetLogy();
  summary_500kgan_nominal->Draw();
  summary_17kgan_nominal ->Draw("same");
  // summary_17kgan_no_bkg  ->Draw("same");
  summary_17kgan_real    ->Draw("same");
  l->Draw("lsame");


}
