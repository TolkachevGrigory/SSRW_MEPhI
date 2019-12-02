void draw(){
  TCanvas *c = new TCanvas("c3","c3",600, 400);
  TMultiGraph * mg = new TMultiGraph("mg","mg");
    gStyle->SetOptTitle(kFALSE);
    gStyle->SetOptStat(0);
    
  TGraph *g1 = new TGraph("/Users/grigorijtolkacev/Desktop/depth2date50%.txt");
     g1->SetName("g1");
     g1->SetTitle("maximum depth of  tree 2");
     g1->SetMarkerStyle(21);
     g1->SetMarkerColor(2);
     g1->SetDrawOption("AP");
     g1->SetLineColor(2);
     g1->SetLineWidth(1);
     g1->SetFillStyle(0);
    
  TGraph *g2 = new TGraph("/Users/grigorijtolkacev/Desktop/depth3date50%.txt");
    g2->SetName("g2");
    g2->SetTitle("maximum depth of  tree 3");
    g2->SetMarkerStyle(22);
    g2->SetMarkerColor(8);
    g2->SetDrawOption("P");
    g2->SetLineColor(8);
    g2->SetLineWidth(1);
    g2->SetFillStyle(0);
    
  TGraph *g3 = new TGraph("/Users/grigorijtolkacev/Desktop/depth5date50%.txt");
    g3->SetName("g3");
    g3->SetTitle("maximum depth of  tree 5");
    g3->SetMarkerStyle(20);
    g3->SetMarkerColor(4);
    g3->SetDrawOption("AP");
    g3->SetLineColor(4);
    g3->SetLineWidth(1);
    g3->SetFillStyle(0);
    
    mg->Add( g1 );
    mg->Add( g2 );
    g3->Draw("ALP");
    mg->Draw("LP");
    g3->GetXaxis()->SetTitle("Number of trees");
    g3->GetYaxis()->SetTitle("ROC-integ");
    gPad->Modified();
    
    
    g3->GetYaxis()->SetLimits(0.6, 0.8);
    g3->SetMinimum(0.725);
    g3->SetMaximum(0.755);
    gPad->SetLogx(1);


    
    c->BuildLegend();
    

    
 
    
   


}
