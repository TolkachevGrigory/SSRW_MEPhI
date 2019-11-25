
#ifndef cutevent_h
#define cutevent_h

#include <TROOT.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "TVector3.h"
#include "TLorentzVector.h"
class cuteven {


int eventLoop(const char* inputFile, const char* outPutFile) {
TFile* f = new TFile("inputFile", "READ");
auto tree = (TTree*)f->Get("NOMINAL");
    
TCanvas *c = new TCanvas("c","",1900,1900);

    
const int nbins = 7;
    Double_t Pt;
    Double_t metE;
    Double_t dPhi;
    Double_t Mt;
    ULong64_t event;
    
    TFile *f11 = new TFile("outPutFile","recreate");
    TTree *tree_with_cuts = new TTree("tree_with_cuts","Simple Tree");
    tree_with_cuts->Branch("EventBranch", &event, "EventBranch/I");
    tree_with_cuts->Branch("Pt",&Pt,"Pt/D");
    tree_with_cuts->Branch("metE",&metE,"metE/D");
    tree_with_cuts->Branch("dPhi",&dPhi,"dPhi/D");
    tree_with_cuts->Branch("Mt",&Mt,"Mt/D");
    
    TH1D *cutflowhisto = new TH1D ("cutflow","Events", nbins,1,nbins+1);
    cutflowhisto->GetXaxis()->SetBinLabel(1,"All");
    cutflowhisto->GetXaxis()->SetBinLabel(2,"pt>25");
    cutflowhisto->GetXaxis()->SetBinLabel(3,"energy>25");
    cutflowhisto->GetXaxis()->SetBinLabel(4,"medium == 1");
    cutflowhisto->GetXaxis()->SetBinLabel(5,"mt > 40");
    cutflowhisto->GetXaxis()->SetBinLabel(6,"isoTight == 1");
    cutflowhisto->GetXaxis()->SetBinLabel(7,"n_bjets==0");
    
    TLorentzVector* lep = 0;
    TLorentzVector* met = 0;
    
        Int_t medium = 0;
    UInt_t isoTight = 0;
    int n_bjets = 0;
    int n_e = 0 ;
    int n_mu = 0;
    int n_t = 0;
    UInt_t lep2 = 0;
    Float_t mt = 0;
    ULong64_t o_event;
    
    tree->SetBranchAddress("event_number", &o_event);
    tree->SetBranchAddress("lep_0_p4", &lep);
    tree->SetBranchAddress("met_reco_p4", &met);
    tree->SetBranchAddress("lep_0_id_medium", &medium);
    tree->SetBranchAddress("lep_0_iso_FCTight", &isoTight);
    tree->SetBranchAddress("n_bjets", &n_bjets);
    tree->SetBranchAddress("n_electrons", &n_e);
    tree->SetBranchAddress("n_muons", &n_mu);
    tree->SetBranchAddress("n_taus", &n_t);
   // tree->SetBranchAddress("lep_0", &lep1);
    tree->SetBranchAddress("lepmet_mt", &mt);
    
    
    
    Long64_t N = tree->GetEntries();
     std::cout<<"N events: "<< N << std::endl;
       for (Long64_t i = 0; i < N ; i++)
       {
           tree->GetEntry(i);
           
           
           cutflowhisto->Fill(1);
           
           double_t pt = lep->Pt();
           double_t eta = lep->Eta();
           double_t phi = lep->Phi();
           double_t energy = lep->E();
           double_t met_pt = met->Pt();
           double_t met_phi = met->Phi();
           double_t met_energy = met->E();
           double_t phi_tau = fabs(phi-met_phi);
          // double_t taunu_mt = sqrt(2*tau_pt*taumet_pt*(1-cos(phi_tau)));
           
          // if ( !(fabs(tau_eta)<1.37 || fabs(tau_eta)>1.52) && (fabs(tau_eta)<2.47) )continue;

          // if(!((n_tau_e+n_tau_mu)==0 && n_tau_t == 1))continue;
           // Cut for QCD
           event = o_event;
           if ( !(pt > 25) ) continue;
           cutflowhisto->Fill(2);
           Pt = pt;
           
           if ( !(met_energy > 25) ) continue;
           metE = energy;
           
           cutflowhisto->Fill(3);
           if ( !(mt > 40) ) continue;
           Mt = mt;
           
           cutflowhisto->Fill(4);
           if ( !(medium == 1))continue;
           cutflowhisto->Fill(5);
           
           if ( !(isoTight == 1))continue;
           cutflowhisto->Fill(6);
           
           if ( !(n_bjets==0))continue;
           cutflowhisto->Fill(7);
           
           if(phi_tau > 3.14159)
        {
            phi_tau = 2*3.14159 - phi_tau;
            dPhi=phi_tau;
        }
            else
            {
              dPhi=phi_tau;
            }
           
           tree_with_cuts->Fill();
           
       }
    f->Close();
    c->cd();
    cutflowhisto->Draw();
    cutflowhisto->Write();
    tree_with_cuts->Write();
        return 0;
}

   
}
#endif // #ifdef
