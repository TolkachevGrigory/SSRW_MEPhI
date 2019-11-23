void сreate_tree_and_cutflow()
{
    
  TFile* f1= new TFile("/Users/grigorijtolkacev/Desktop/ATLAS/SW/nom_mu/signal/minus.2.SM_WLepton.root", "READ");
  TFile* f2= new TFile("/Users/grigorijtolkacev/Desktop/ATLAS/SW/nom_mu/background/minus.1.SM_WLepton.root", "READ");

  auto taunu = (TTree*)f1->Get("NOMINAL");
  auto munu = (TTree*)f2->Get("NOMINAL");
    TCanvas *c = new TCanvas("c","",1900,1900);
    c->Divide(2);


 const int nbins = 7;
    
    TFile *f11 = new TFile("sandb_with_cuts_mu_minus.root","recreate");
       
       Double_t s_Pt;
       Double_t s_metE;
       Double_t s_dPhi;
       Double_t s_Mt;
       ULong64_t so_event;
       ULong64_t s_event;
    
       TTree *s_tree_with_cuts = new TTree("s_tree_with_cuts","Simple Tree");
       s_tree_with_cuts->Branch("EventBranch", &s_event, "EventBranch/I");
       s_tree_with_cuts->Branch("Pt",&s_Pt,"Pt/D");
       s_tree_with_cuts->Branch("metE",&s_metE,"metE/D");
       s_tree_with_cuts->Branch("dPhi",&s_dPhi,"dPhi/D");
       s_tree_with_cuts->Branch("Mt",&s_Mt,"Mt/D");
    
       Double_t b_Pt;
       Double_t b_metE;
       Double_t b_dPhi;
       Double_t  b_Mt;
       ULong64_t bo_event;
       ULong64_t b_event;
    
       TTree *b_tree_with_cuts = new TTree("b_tree_with_cuts","Simple Tree");
       b_tree_with_cuts->Branch("EventBranch", &b_event,"EventBranch/I");
       b_tree_with_cuts->Branch("Pt",&b_Pt,"Pt/D");
       b_tree_with_cuts->Branch("metE",&b_metE,"metE/D");
       b_tree_with_cuts->Branch("dPhi",&b_dPhi,"dPhi/D");
       b_tree_with_cuts->Branch("Mt",&b_Mt,"Mt/D");
    

       
       
    
       TH1D *signal_cutflowhisto = new TH1D ("cutflow","Events", nbins,1,nbins+1);
       TH1D *beackground_cutflowhisto = new TH1D ("cutflow","Events", nbins,1,nbins+1);
    
       signal_cutflowhisto->GetXaxis()->SetBinLabel(1,"All");
       signal_cutflowhisto->GetXaxis()->SetBinLabel(2,"tau_pt>25");
       signal_cutflowhisto->GetXaxis()->SetBinLabel(3,"taumet_energy>25");
       signal_cutflowhisto->GetXaxis()->SetBinLabel(4,"tau_medium == 1");
       signal_cutflowhisto->GetXaxis()->SetBinLabel(5,"taunu_mt > 40");
       signal_cutflowhisto->GetXaxis()->SetBinLabel(6,"tau_isoTight == 1");
       signal_cutflowhisto->GetXaxis()->SetBinLabel(7,"tau_n_bjets==0");
       
       
       beackground_cutflowhisto->GetXaxis()->SetBinLabel(1,"All");
       beackground_cutflowhisto->GetXaxis()->SetBinLabel(2,"tau_pt>25");
       beackground_cutflowhisto->GetXaxis()->SetBinLabel(3,"taumet_energy>25");
       beackground_cutflowhisto->GetXaxis()->SetBinLabel(4,"taunu_mt > 40");
       beackground_cutflowhisto->GetXaxis()->SetBinLabel(5,"tau_medium == 1");
       beackground_cutflowhisto->GetXaxis()->SetBinLabel(6,"tau_isoTight == 1");
       beackground_cutflowhisto->GetXaxis()->SetBinLabel(7,"tau_n_bjets == 0");
    
    
  TLorentzVector* lep_tau = 0;
  TLorentzVector* met_tau = 0;
  TLorentzVector* lep_mu = 0;
  TLorentzVector* met_mu = 0;
    
  Int_t tau_medium = 0;
  UInt_t tau_isoTight = 0;
  Int_t mu_medium = 0;
  UInt_t mu_isoTight = 0;
  int mu_n_bjets = 0;
  int tau_n_bjets = 0;
  int n_tau_e = 0 ;
  int n_tau_mu = 0;
  int n_tau_t = 0;
  int n_mu_e = 0;
  int n_mu_mu =0 ;
  int n_mu_t = 0;
  UInt_t lep1 = 0;
  UInt_t lep2 = 0;
  Float_t tau_mt = 0;
  Float_t mu_mt = 0;

  taunu->SetBranchAddress("event_number", &so_event);
  taunu->SetBranchAddress("lep_0_p4", &lep_tau);
  taunu->SetBranchAddress("met_reco_p4", &met_tau);
  taunu->SetBranchAddress("lep_0_id_medium", &tau_medium);
  taunu->SetBranchAddress("lep_0_iso_FCTight", &tau_isoTight);
  taunu->SetBranchAddress("n_bjets", &tau_n_bjets);
  taunu->SetBranchAddress("n_electrons", &n_tau_e);
  taunu->SetBranchAddress("n_muons", &n_tau_mu);
  taunu->SetBranchAddress("n_taus", &n_tau_t);
  taunu->SetBranchAddress("lep_0", &lep1);
  taunu->SetBranchAddress("lepmet_mt", &tau_mt);
    
  munu->SetBranchAddress("event_number", &bo_event);
  munu->SetBranchAddress("lep_0_p4", &lep_mu);
  munu->SetBranchAddress("met_reco_p4", &met_mu);
  munu->SetBranchAddress("lep_0_id_medium", &mu_medium);
  munu->SetBranchAddress("lep_0_iso_FCTight", &mu_isoTight);
  munu->SetBranchAddress("n_bjets", &mu_n_bjets);
  munu->SetBranchAddress("n_electrons", &n_mu_e);
  munu->SetBranchAddress("n_muons", &n_mu_mu);
  munu->SetBranchAddress("n_taus", &n_mu_t);
  munu->SetBranchAddress("lepmet_mt", &mu_mt);
    

  Long64_t N = taunu->GetEntries();
  std::cout<<"N events: "<< N << std::endl;
    for (Long64_t i = 0; i < N ; i++)
    {
        taunu->GetEntry(i);
        
        
        signal_cutflowhisto->Fill(1);
        
        double_t tau_pt = lep_tau->Pt();
        double_t tau_eta = lep_tau->Eta();
        double_t tau_phi = lep_tau->Phi();
        double_t tau_energy = lep_tau->E();
        double_t taumet_pt = met_tau->Pt();
        double_t taumet_phi = met_tau->Phi();
        double_t taumet_energy = met_tau->E();
        double_t phi_tau = fabs(tau_phi-taumet_phi);
       // double_t taunu_mt = sqrt(2*tau_pt*taumet_pt*(1-cos(phi_tau)));
        
       // if ( !(fabs(tau_eta)<1.37 || fabs(tau_eta)>1.52) && (fabs(tau_eta)<2.47) )continue;

       // if(!((n_tau_e+n_tau_mu)==0 && n_tau_t == 1))continue;
        // Cut for QCD
        s_event = so_event;
        if ( !(tau_pt > 25) ) continue;
        signal_cutflowhisto->Fill(2);
        s_Pt = tau_pt;
        
        if ( !(taumet_energy > 25) ) continue;
        s_metE = tau_energy;
        
        signal_cutflowhisto->Fill(3);
        if ( !(tau_mt > 40) ) continue;
        s_Mt = tau_mt;
        
        signal_cutflowhisto->Fill(4);
        if ( !(tau_medium == 1))continue;
        signal_cutflowhisto->Fill(5);
        
        if ( !(tau_isoTight == 1))continue;
        signal_cutflowhisto->Fill(6);
        
        if ( !(tau_n_bjets==0))continue;
        signal_cutflowhisto->Fill(7);
        
        
        
        if(phi_tau > 3.14159)
        {
            phi_tau = 2*3.14159 - phi_tau;
            s_dPhi=phi_tau;
        }
            else
            {
               s_dPhi=phi_tau;
            }
        
        s_tree_with_cuts->Fill();
    }
    
    Long64_t K = munu->GetEntries();
    std::cout<<"N events: "<< K << std::endl;
      
      for (Long64_t i = 0; i < K ; i++)
      {
          
             munu->GetEntry(i);
        
          b_event = bo_event;
          double_t mu_pt = lep_mu->Pt();
          double_t mu_eta = lep_mu->Eta();
          double_t mu_phi = lep_mu->Phi();
          double_t mu_energy = lep_mu->E();
          double_t mumet_pt = met_mu->Pt();
          double_t mumet_phi = met_mu->Phi();
          double_t mumet_energy = met_mu->E();
          double_t phi_mu = fabs(mu_phi-mumet_phi);
      //    double_t munu_mt = sqrt(2*mu_pt*mumet_pt*(1-cos(phi_mu)));
          //mu eta gap
        //  if ( !(fabs(mu_eta)<1.37 || fabs(mu_eta)>1.52) && (fabs(mu_eta)<2.47) )continue;
          
          //if(!((n_mu_e+n_mu_mu)==1 && n_mu_t == 0))continue;
          
         beackground_cutflowhisto->Fill(1);

          if ( !(mu_pt > 25) ) continue;
          beackground_cutflowhisto->Fill(2);
          b_Pt = mu_pt;

          if ( !(mumet_energy > 25) ) continue;
          beackground_cutflowhisto->Fill(3);
          b_metE =  mu_energy;
          
          if ( !(mu_mt > 40) ) continue;
          beackground_cutflowhisto->Fill(4);
          b_Mt=mu_mt;
          
          if( !(mu_medium == 1))continue;
          beackground_cutflowhisto->Fill(5);
          
          if( !(mu_isoTight == 1))continue;
          beackground_cutflowhisto->Fill(6);
          
          if( !(mu_n_bjets==0))continue;
          beackground_cutflowhisto->Fill(7);
          
          if(phi_mu > 3.14159)
                 {
                     phi_mu = 2*3.14159 - phi_mu;
                     b_dPhi=phi_mu;
                 }
                     else {
                      b_dPhi=phi_mu;
                 }
                 
          
          
          
          
     //   if ( !(fabs(phi_mu)<3.14 && fabs(phi_mu)>0))continue;
          
           b_tree_with_cuts->Fill();
      }
      
    
  f1->Close();
  f2->Close();
    
    c->cd(1);
    signal_cutflowhisto->Draw();
    signal_cutflowhisto->Write();
    s_tree_with_cuts->Write();
   
    
    c->cd(2);
       beackground_cutflowhisto->Draw();
       beackground_cutflowhisto->Write();
       b_tree_with_cuts->Write();

   // c->SaveAs("/Users/grigorijtolkacev/Desktop/ATLAS/SW/lep_eandtau_minus_pt.pdf");
 
    
}
