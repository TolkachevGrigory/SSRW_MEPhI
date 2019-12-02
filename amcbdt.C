void draw(){
  TCanvas *c = new TCanvas("c3","c3",1500, 900);
  TMultiGraph * mg = new TMultiGraph("mg","mg");
    gStyle->SetOptTitle(kFALSE);
    gStyle->SetOptStat(0);
    
    
    
    
    
    
    TGraph *g17 = new TGraph("/Users/grigorijtolkacev/Desktop/date70%depth2.txt");
         g17->SetName("g17");
         g17->SetTitle("train date 70% maximum depth of  tree 2");
         g17->SetMarkerStyle(21);
         g17->SetMarkerColor(12);
         g17->SetDrawOption("AP");
         g17->SetLineColor(12);
         g17->SetLineWidth(3);
         g17->SetFillStyle(0);
      
    TGraph *g27 = new TGraph("/Users/grigorijtolkacev/Desktop/date70%depth3.txt");
      g27->SetName("g27");
      g27->SetTitle("train date 70% maximum depth of  tree 3");
      g27->SetMarkerStyle(22);
      g27->SetMarkerColor(38);
      g27->SetDrawOption("P");
      g27->SetLineColor(38);
      g27->SetLineWidth(3);
      g27->SetFillStyle(0);
      
    TGraph *g37= new TGraph("/Users/grigorijtolkacev/Desktop/date70%depth5");
      g37->SetName("g37");
      g37->SetTitle("train date 70% maximum depth of  tree 5");
      g37->SetMarkerStyle(20);
      g37->SetMarkerColor(32);
      g37->SetDrawOption("AP");
      g37->SetLineColor(32);
      g37->SetLineWidth(3);
      g37->SetFillStyle(0);
    
    
    
    TGraph *g16 = new TGraph("/Users/grigorijtolkacev/Desktop/date60%depth2.txt");
         g16->SetName("g16");
         g16->SetTitle("train date 60% maximum depth of  tree 2");
         g16->SetMarkerStyle(21);
         g16->SetMarkerColor(5);
         g16->SetDrawOption("AP");
         g16->SetLineColor(5);
         g16->SetLineWidth(2);
         g16->SetFillStyle(0);
      
    TGraph *g26 = new TGraph("/Users/grigorijtolkacev/Desktop/date60%deth3.txt");
      g26->SetName("g26");
      g26->SetTitle("train date 60% maximum depth of  tree 3");
      g26->SetMarkerStyle(22);
      g26->SetMarkerColor(6);
      g26->SetDrawOption("P");
      g26->SetLineColor(6);
      g26->SetLineWidth(2);
      g26->SetFillStyle(0);
      
    TGraph *g36= new TGraph("/Users/grigorijtolkacev/Desktop/date60%depth5.txt");
      g36->SetName("g36");
      g36->SetTitle("train date 60% maximum depth of  tree 5");
      g36->SetMarkerStyle(20);
      g36->SetMarkerColor(7);
      g36->SetDrawOption("AP");
      g36->SetLineColor(7);
      g36->SetLineWidth(2);
      g36->SetFillStyle(0);
    
    
    
    
    
    TGraph *g1 = new TGraph("/Users/grigorijtolkacev/Desktop/depth2date50%.txt");
       g1->SetName("g1");
       g1->SetTitle("train date 50% maximum depth of  tree 2");
       g1->SetMarkerStyle(21);
       g1->SetMarkerColor(2);
       g1->SetDrawOption("AP");
       g1->SetLineColor(2);
       g1->SetLineWidth(1);
       g1->SetFillStyle(0);
    
  TGraph *g2 = new TGraph("/Users/grigorijtolkacev/Desktop/depth3date50%.txt");
    g2->SetName("g2");
    g2->SetTitle("train date 50% maximum depth of  tree 3");
    g2->SetMarkerStyle(22);
    g2->SetMarkerColor(8);
    g2->SetDrawOption("P");
    g2->SetLineColor(8);
    g2->SetLineWidth(1);
    g2->SetFillStyle(0);
    
  TGraph *g3 = new TGraph("/Users/grigorijtolkacev/Desktop/depth5date50%.txt");
    g3->SetName("g3");
    g3->SetTitle("train date 50% maximum depth of  tree 5");
    g3->SetMarkerStyle(20);
    g3->SetMarkerColor(4);
    g3->SetDrawOption("AP");
    g3->SetLineColor(4);
    g3->SetLineWidth(1);
    g3->SetFillStyle(0);
    
    mg->Add( g1 );
    mg->Add( g2 );
    mg->Add( g17 );
    mg->Add( g27 );
    mg->Add( g37 );
    mg->Add( g16 );
    mg->Add( g26 );
    mg->Add( g36 );
   
   
   
   
    g3->Draw("ALP");
    mg->Draw("LP");
    g3->GetXaxis()->SetTitle("Number of trees");
    g3->GetYaxis()->SetTitle("ROC-integ");
    gPad->Modified();
    
    
    g3->GetYaxis()->SetLimits(0.6, 0.8);
    g3->SetMinimum(0.709);
    g3->SetMaximum(0.752);
    gPad->SetLogx(1);


    
    c->BuildLegend();
    

    
 
    
   


}
