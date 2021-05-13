void unnamed()
{
//=========Macro generated from canvas: c1/c1
//=========  (Sat Sep 19 18:20:46 2020) by ROOT version6.08/06
   TCanvas *c1 = new TCanvas("c1", "c1",67,87,700,500);
   gStyle->SetOptStat(0);
   c1->Range(4.010378,35.99451,40.1442,42.51335);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetGridx();
   c1->SetGridy();
   c1->SetLeftMargin(0.1590258);
   c1->SetRightMargin(0.04011461);
   c1->SetTopMargin(0.02760085);
   c1->SetBottomMargin(0.1719745);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   Double_t Graph0_fx1[9] = {
   12.1681,
   16.3717,
   24.3363,
   25.6637,
   30.531,
   32.0796,
   34.5133,
   35.3982,
   36.2832};
   Double_t Graph0_fy1[9] = {
   38.3001,
   38.0189,
   37.5504,
   37.8409,
   38.6562,
   39.4246,
   40.3992,
   41.2051,
   41.8986};
   TGraph *graph = new TGraph(9,Graph0_fx1,Graph0_fy1);
   graph->SetName("Graph0");
   graph->SetTitle("");
   graph->SetFillColor(1);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#009999");
   graph->SetMarkerColor(ci);
   graph->SetMarkerStyle(33);
   graph->SetMarkerSize(1.4);
   
   TH1F *Graph_Graph1 = new TH1F("Graph_Graph1","",100,9.756588,38.69471);
   Graph_Graph1->SetMinimum(37.11558);
   Graph_Graph1->SetMaximum(42.33342);
   Graph_Graph1->SetDirectory(0);
   Graph_Graph1->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph1->SetLineColor(ci);
   Graph_Graph1->GetXaxis()->SetTitle("Rejection efficiency ^{208}Tl (%)");
   Graph_Graph1->GetXaxis()->SetNdivisions(110);
   Graph_Graph1->GetXaxis()->SetLabelFont(42);
   Graph_Graph1->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph1->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph1->GetXaxis()->SetTickLength(0.025);
   Graph_Graph1->GetXaxis()->SetTitleFont(42);
   Graph_Graph1->GetYaxis()->SetTitle("Selection efficiency 0#nu#beta#beta (%)");
   Graph_Graph1->GetYaxis()->SetNdivisions(110);
   Graph_Graph1->GetYaxis()->SetLabelFont(42);
   Graph_Graph1->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph1->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph1->GetYaxis()->SetTickLength(0.015);
   Graph_Graph1->GetYaxis()->SetTitleOffset(0.9);
   Graph_Graph1->GetYaxis()->SetTitleFont(42);
   Graph_Graph1->GetZaxis()->SetLabelFont(42);
   Graph_Graph1->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph1->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph1->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph1);
   
   graph->Draw("ap");
   
   TPaveText *pt = new TPaveText(0.2005731,0.3800425,0.2593123,0.4246285,"brNDC");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetTextSize(0.045);
   TText *AText = pt->AddText("0 ps");
   pt->Draw();
   
   pt = new TPaveText(0.7621777,0.3683652,0.8338109,0.4384289,"brNDC");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetTextSize(0.045);
   AText = pt->AddText("200 ps");
   pt->Draw();
   
   pt = new TPaveText(0.8753582,0.9235669,0.9469914,0.9681529,"brNDC");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetTextSize(0.045);
   AText = pt->AddText("400 ps");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
