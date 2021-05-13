void unnamed()
{
//=========Macro generated from canvas: c1/c1
//=========  (Tue Sep 22 11:19:35 2020) by ROOT version6.08/06
   TCanvas *c1 = new TCanvas("c1", "c1",67,87,700,500);
   gStyle->SetOptStat(0);
   c1->Range(-24.05143,27.97412,99.0188,104.9235);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetLeftMargin(0.1590258);
   c1->SetRightMargin(0.04011461);
   c1->SetTopMargin(0.02760085);
   c1->SetBottomMargin(0.1719745);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TMultiGraph *multigraph = new TMultiGraph();
   multigraph->SetName("");
   multigraph->SetTitle("");
   
   Double_t Graph_fx1[15] = {
   89.6018,
   82.9646,
   72.1239,
   65.9292,
   60.177,
   50.885,
   46.0177,
   41.8142,
   37.1681,
   33.4071,
   28.9823,
   25.2212,
   22.3451,
   19.9115,
   0};
   Double_t Graph_fy1[15] = {
   44.0071,
   81.0514,
   91.5753,
   95.61428,
   97.44166,
   98.33193,
   98.73489,
   98.9598,
   99.23156,
   99.40025,
   99.54081,
   99.59704,
   99.7095,
   99.75635,
   100};
   TGraph *graph = new TGraph(15,Graph_fx1,Graph_fy1);
   graph->SetName("Graph");
   graph->SetTitle("");
   graph->SetFillColor(1);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#009999");
   graph->SetLineColor(ci);
   graph->SetLineWidth(2);

   ci = TColor::GetColor("#009999");
   graph->SetMarkerColor(ci);
   graph->SetMarkerStyle(20);
   graph->SetMarkerSize(0.7);
   
   TH1F *Graph_Graph1 = new TH1F("Graph_Graph1","",100,0,98.56198);
   Graph_Graph1->SetMinimum(38.40781);
   Graph_Graph1->SetMaximum(105.5993);
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
   
   multigraph->Add(graph,"lp");
   
   Double_t Graph_fx2[15] = {
   76.7699,
   73.4513,
   69.2478,
   64.6018,
   60.3982,
   56.6372,
   51.7699,
   47.1239,
   42.2566,
   38.0531,
   34.0708,
   30.0885,
   27.4336,
   25,
   0};
   Double_t Graph_fy2[15] = {
   48.7208,
   56.4521,
   63.293,
   69.6467,
   75.4194,
   80.7516,
   85.2779,
   88.689,
   91.65027,
   93.74941,
   95.34252,
   96.57951,
   97.48852,
   98.17262,
   100};
   graph = new TGraph(15,Graph_fx2,Graph_fy2);
   graph->SetName("Graph");
   graph->SetTitle("");
   graph->SetFillColor(1);

   ci = TColor::GetColor("#009900");
   graph->SetLineColor(ci);
   graph->SetLineWidth(2);

   ci = TColor::GetColor("#009900");
   graph->SetMarkerColor(ci);
   graph->SetMarkerStyle(20);
   graph->SetMarkerSize(0.7);
   
   TH1F *Graph_Graph2 = new TH1F("Graph_Graph2","",100,0,84.44689);
   Graph_Graph2->SetMinimum(43.59288);
   Graph_Graph2->SetMaximum(105.1279);
   Graph_Graph2->SetDirectory(0);
   Graph_Graph2->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph2->SetLineColor(ci);
   Graph_Graph2->GetXaxis()->SetTitle("Rejection efficiency ^{208}Tl (%)");
   Graph_Graph2->GetXaxis()->SetNdivisions(110);
   Graph_Graph2->GetXaxis()->SetLabelFont(42);
   Graph_Graph2->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph2->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph2->GetXaxis()->SetTickLength(0.025);
   Graph_Graph2->GetXaxis()->SetTitleFont(42);
   Graph_Graph2->GetYaxis()->SetTitle("Selection efficiency 0#nu#beta#beta (%)");
   Graph_Graph2->GetYaxis()->SetNdivisions(110);
   Graph_Graph2->GetYaxis()->SetLabelFont(42);
   Graph_Graph2->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph2->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph2->GetYaxis()->SetTickLength(0.015);
   Graph_Graph2->GetYaxis()->SetTitleOffset(0.9);
   Graph_Graph2->GetYaxis()->SetTitleFont(42);
   Graph_Graph2->GetZaxis()->SetLabelFont(42);
   Graph_Graph2->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph2->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph2->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph2);
   
   multigraph->Add(graph,"lp");
   
   Double_t Graph_fx3[15] = {
   83.6283,
   76.7699,
   72.5664,
   67.0354,
   59.7345,
   55.7522,
   49.5575,
   43.1416,
   37.6106,
   32.7434,
   30.3097,
   26.9912,
   24.115,
   21.2389,
   0};
   Double_t Graph_fy3[15] = {
   48.3179,
   61.5219,
   73.442,
   82.6539,
   89.4106,
   93.49639,
   95.97039,
   97.51663,
   98.31319,
   98.87546,
   99.19408,
   99.35339,
   99.49396,
   99.58767,
   100};
   graph = new TGraph(15,Graph_fx3,Graph_fy3);
   graph->SetName("Graph");
   graph->SetTitle("");
   graph->SetFillColor(1);

   ci = TColor::GetColor("#cc0066");
   graph->SetLineColor(ci);
   graph->SetLineWidth(2);

   ci = TColor::GetColor("#cc0066");
   graph->SetMarkerColor(ci);
   graph->SetMarkerStyle(20);
   graph->SetMarkerSize(0.7);
   
   TH1F *Graph_Graph3 = new TH1F("Graph_Graph3","",100,0,91.99113);
   Graph_Graph3->SetMinimum(43.14969);
   Graph_Graph3->SetMaximum(105.1682);
   Graph_Graph3->SetDirectory(0);
   Graph_Graph3->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph3->SetLineColor(ci);
   Graph_Graph3->GetXaxis()->SetTitle("Rejection efficiency ^{208}Tl (%)");
   Graph_Graph3->GetXaxis()->SetNdivisions(110);
   Graph_Graph3->GetXaxis()->SetLabelFont(42);
   Graph_Graph3->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph3->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph3->GetXaxis()->SetTickLength(0.025);
   Graph_Graph3->GetXaxis()->SetTitleFont(42);
   Graph_Graph3->GetYaxis()->SetTitle("Selection efficiency 0#nu#beta#beta (%)");
   Graph_Graph3->GetYaxis()->SetNdivisions(110);
   Graph_Graph3->GetYaxis()->SetLabelFont(42);
   Graph_Graph3->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph3->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph3->GetYaxis()->SetTickLength(0.015);
   Graph_Graph3->GetYaxis()->SetTitleOffset(0.9);
   Graph_Graph3->GetYaxis()->SetTitleFont(42);
   Graph_Graph3->GetZaxis()->SetLabelFont(42);
   Graph_Graph3->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph3->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph3->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph3);
   
   multigraph->Add(graph,"lp");
   
   Double_t Graph_fx4[15] = {
   69.2478,
   66.5929,
   64.6018,
   61.7257,
   57.9646,
   54.646,
   50.885,
   48.0088,
   44.469,
   42.9204,
   41.1504,
   38.7168,
   35.6195,
   33.1858,
   0};
   Double_t Graph_fy4[15] = {
   49.4518,
   52.9191,
   56.9206,
   60.4161,
   63.8553,
   67.4351,
   70.462,
   73.517,
   76.4689,
   79.2897,
   81.7918,
   84.3126,
   86.2337,
   88.0517,
   100};
   graph = new TGraph(15,Graph_fx4,Graph_fy4);
   graph->SetName("Graph");
   graph->SetTitle("");
   graph->SetFillColor(1);

   ci = TColor::GetColor("#ff9900");
   graph->SetLineColor(ci);
   graph->SetLineWidth(2);

   ci = TColor::GetColor("#ff9900");
   graph->SetMarkerColor(ci);
   graph->SetMarkerStyle(20);
   graph->SetMarkerSize(0.7);
   
   TH1F *Graph_Graph4 = new TH1F("Graph_Graph4","",100,0,76.17258);
   Graph_Graph4->SetMinimum(44.39698);
   Graph_Graph4->SetMaximum(105.0548);
   Graph_Graph4->SetDirectory(0);
   Graph_Graph4->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph4->SetLineColor(ci);
   Graph_Graph4->GetXaxis()->SetTitle("Rejection efficiency ^{208}Tl (%)");
   Graph_Graph4->GetXaxis()->SetNdivisions(110);
   Graph_Graph4->GetXaxis()->SetLabelFont(42);
   Graph_Graph4->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph4->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph4->GetXaxis()->SetTickLength(0.025);
   Graph_Graph4->GetXaxis()->SetTitleFont(42);
   Graph_Graph4->GetYaxis()->SetTitle("Selection efficiency 0#nu#beta#beta (%)");
   Graph_Graph4->GetYaxis()->SetNdivisions(110);
   Graph_Graph4->GetYaxis()->SetLabelFont(42);
   Graph_Graph4->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph4->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph4->GetYaxis()->SetTickLength(0.015);
   Graph_Graph4->GetYaxis()->SetTitleOffset(0.9);
   Graph_Graph4->GetYaxis()->SetTitleFont(42);
   Graph_Graph4->GetZaxis()->SetLabelFont(42);
   Graph_Graph4->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph4->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph4->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph4);
   
   multigraph->Add(graph,"lp");
   
   Double_t Graph_fx5[15] = {
   71.9027,
   70.1327,
   65.9292,
   63.0531,
   59.0708,
   55.0885,
   51.9912,
   48.2301,
   45.354,
   41.1504,
   37.6106,
   34.9558,
   32.7434,
   29.4248,
   0};
   Double_t Graph_fy5[15] = {
   49.2456,
   53.9687,
   59.2728,
   63.6585,
   68.1192,
   72.1957,
   75.991,
   79.9456,
   83.0194,
   85.8964,
   88.2673,
   90.4695,
   92.32499,
   93.82438,
   100};
   graph = new TGraph(15,Graph_fx5,Graph_fy5);
   graph->SetName("Graph");
   graph->SetTitle("");
   graph->SetFillColor(1);

   ci = TColor::GetColor("#990099");
   graph->SetLineColor(ci);
   graph->SetLineWidth(2);

   ci = TColor::GetColor("#990099");
   graph->SetMarkerColor(ci);
   graph->SetMarkerStyle(20);
   graph->SetMarkerSize(0.7);
   
   TH1F *Graph_Graph5 = new TH1F("Graph_Graph5","",100,0,79.09297);
   Graph_Graph5->SetMinimum(44.17016);
   Graph_Graph5->SetMaximum(105.0754);
   Graph_Graph5->SetDirectory(0);
   Graph_Graph5->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph5->SetLineColor(ci);
   Graph_Graph5->GetXaxis()->SetTitle("Rejection efficiency ^{208}Tl (%)");
   Graph_Graph5->GetXaxis()->SetNdivisions(110);
   Graph_Graph5->GetXaxis()->SetLabelFont(42);
   Graph_Graph5->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph5->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph5->GetXaxis()->SetTickLength(0.025);
   Graph_Graph5->GetXaxis()->SetTitleFont(42);
   Graph_Graph5->GetYaxis()->SetTitle("Selection efficiency 0#nu#beta#beta (%)");
   Graph_Graph5->GetYaxis()->SetNdivisions(110);
   Graph_Graph5->GetYaxis()->SetLabelFont(42);
   Graph_Graph5->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph5->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph5->GetYaxis()->SetTickLength(0.015);
   Graph_Graph5->GetYaxis()->SetTitleOffset(0.9);
   Graph_Graph5->GetYaxis()->SetTitleFont(42);
   Graph_Graph5->GetZaxis()->SetLabelFont(42);
   Graph_Graph5->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph5->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph5->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph5);
   
   multigraph->Add(graph,"lp");
   multigraph->Draw("a");
   multigraph->GetXaxis()->SetTitle("Rejection efficiency ^{208}Tl (%)");
   multigraph->GetXaxis()->SetNdivisions(110);
   multigraph->GetXaxis()->SetLabelFont(42);
   multigraph->GetXaxis()->SetLabelSize(0.05);
   multigraph->GetXaxis()->SetTitleSize(0.06);
   multigraph->GetXaxis()->SetTickLength(0.025);
   multigraph->GetXaxis()->SetTitleFont(42);
   multigraph->GetYaxis()->SetTitle("Selection efficiency 0#nu#beta#beta (%)");
   multigraph->GetYaxis()->SetNdivisions(110);
   multigraph->GetYaxis()->SetLabelFont(42);
   multigraph->GetYaxis()->SetLabelSize(0.05);
   multigraph->GetYaxis()->SetTitleSize(0.06);
   multigraph->GetYaxis()->SetTickLength(0.015);
   multigraph->GetYaxis()->SetTitleOffset(1.1);
   multigraph->GetYaxis()->SetTitleFont(42);
   
   TLegend *leg = new TLegend(0.215559,0.230924,0.426256,0.495984,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("Graph","#sigma_{t} = 400 ps","l");

   ci = TColor::GetColor("#ff9900");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("Graph","#sigma_{t} = 300 ps","l");

   ci = TColor::GetColor("#990099");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("Graph","#sigma_{t} = 200 ps","l");

   ci = TColor::GetColor("#009900");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("Graph","#sigma_{t} = 100 ps","l");

   ci = TColor::GetColor("#cc0066");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("Graph","#sigma_{t} = 0 ps","l");

   ci = TColor::GetColor("#009999");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   
   TPaveText *pt = new TPaveText(0.1862464,0.8386412,0.2449857,0.8832272,"brNDC");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetTextSize(0.045);
   TText *AText = pt->AddText("No cut");
   pt->Draw();
   
   pt = new TPaveText(0.6647564,0.2271762,0.7234957,0.2717622,"brNDC");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetTextSize(0.045);
   AText = pt->AddText("k=0.45");
   pt->Draw();
   
   pt = new TPaveText(0.3868195,0.7261146,0.4455587,0.7707006,"brNDC");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetTextSize(0.045);
   AText = pt->AddText("k=0");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
