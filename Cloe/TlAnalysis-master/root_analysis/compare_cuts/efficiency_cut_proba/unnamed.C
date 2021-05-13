void unnamed()
{
//=========Macro generated from canvas: c1/c1
//=========  (Tue Sep 22 11:56:28 2020) by ROOT version6.08/06
   TCanvas *c1 = new TCanvas("c1", "c1",67,55,1853,1025);
   gStyle->SetOptStat(0);
   c1->Range(-26.84258,-22.55958,110.5098,108.6202);
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
   96.0177,
   88.9381,
   87.3894,
   85.6195,
   84.292,
   84.292,
   83.1858,
   82.5221,
   81.8584,
   80.9735,
   80.3097,
   79.646,
   79.646,
   79.646,
   0};
   Double_t Graph_fy1[15] = {
   1.546204,
   48.6271,
   63.6023,
   70.2652,
   74.5385,
   76.9094,
   78.7274,
   80.1893,
   81.2576,
   82.1385,
   82.7851,
   83.3568,
   83.919,
   84.4813,
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
   
   TH1F *Graph_Graph1 = new TH1F("Graph_Graph1","",100,0,105.6195);
   Graph_Graph1->SetMinimum(0);
   Graph_Graph1->SetMaximum(109.8454);
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
   99.7788,
   76.7699,
   68.5841,
   62.8319,
   57.9646,
   48.8938,
   42.6991,
   38.9381,
   35.8407,
   32.9646,
   30.3097,
   28.0973,
   26.7699,
   25.4425,
   0};
   Double_t Graph_fy2[15] = {
   0.07499695,
   49.7704,
   63.2556,
   70.1902,
   75.7474,
   82.2791,
   87.0209,
   89.7573,
   91.80958,
   93.33708,
   94.25546,
   94.93956,
   95.59554,
   96.16718,
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
   
   TH1F *Graph_Graph2 = new TH1F("Graph_Graph2","",100,0,109.7567);
   Graph_Graph2->SetMinimum(0);
   Graph_Graph2->SetMaximum(109.9925);
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
   98.4513,
   82.3009,
   75.4425,
   72.3451,
   70.1327,
   68.3628,
   66.1504,
   64.1593,
   61.0619,
   58.8496,
   57.3009,
   56.4159,
   55.3097,
   54.646,
   0};
   Double_t Graph_fy3[15] = {
   0.2342987,
   51.9445,
   64.3145,
   71.5678,
   75.8036,
   79.0273,
   81.445,
   83.8066,
   86.2243,
   87.8643,
   89.0919,
   90.17899,
   91.19108,
   91.87518,
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
   
   TH1F *Graph_Graph3 = new TH1F("Graph_Graph3","",100,0,108.2964);
   Graph_Graph3->SetMinimum(0);
   Graph_Graph3->SetMaximum(109.9766);
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
   100,
   87.6106,
   61.2832,
   44.9115,
   27.6549,
   21.0177,
   14.823,
   11.7257,
   10.6195,
   9.73451,
   8.18584,
   7.30088,
   6.63717,
   5.97345,
   0};
   Double_t Graph_fy4[15] = {
   0.009399414,
   25.7239,
   60.0975,
   70.3683,
   85.887,
   92.26877,
   95.01453,
   96.58889,
   97.38544,
   98.04142,
   98.45375,
   98.8286,
   98.99728,
   99.22219,
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
   
   TH1F *Graph_Graph4 = new TH1F("Graph_Graph4","",100,0,110);
   Graph_Graph4->SetMinimum(0);
   Graph_Graph4->SetMaximum(109.9991);
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
   100,
   81.4159,
   64.1593,
   55.9735,
   38.9381,
   29.8673,
   25.2212,
   22.5664,
   20.5752,
   18.5841,
   17.2566,
   15.9292,
   14.3805,
   12.6106,
   0};
   Double_t Graph_fy5[15] = {
   0.009399414,
   41.0458,
   61.4563,
   69.1969,
   80.5641,
   87.9486,
   91.81895,
   94.03992,
   95.37063,
   96.31712,
   96.96373,
   97.37607,
   97.69469,
   98.01331,
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
   
   TH1F *Graph_Graph5 = new TH1F("Graph_Graph5","",100,0,110);
   Graph_Graph5->SetMinimum(0);
   Graph_Graph5->SetMaximum(109.9991);
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
   TLegendEntry *entry=leg->AddEntry("Graph","#sigma_{t} = 0 ps","l");

   ci = TColor::GetColor("#009999");
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
   entry=leg->AddEntry("Graph","#sigma_{t} = 200 ps","l");

   ci = TColor::GetColor("#009900");
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
   entry=leg->AddEntry("Graph","#sigma_{t} = 400 ps","l");

   ci = TColor::GetColor("#ff9900");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   
   TPaveText *pt = new TPaveText(0.1734198,0.8985944,0.2323069,0.9186747,"brNDC");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetTextSize(0.045);
   TText *AText = pt->AddText("No cut");
   pt->Draw();
   
   pt = new TPaveText(0.7979943,0.1910828,0.8567335,0.2356688,"brNDC");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetTextSize(0.045);
   AText = pt->AddText("k=0.1");
   pt->Draw();
   
   pt = new TPaveText(0.2522961,0.939759,0.3106429,0.9598394,"brNDC");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetTextSize(0.045);
   AText = pt->AddText("k=2");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
