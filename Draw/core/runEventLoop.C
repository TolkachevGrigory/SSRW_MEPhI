int runEventLoop(TString inputFilePath = "passToInputRootFile", bool isSignal = true)
{
	Info("runEventLoop()", " Running event loop analysis on  %s [signal: %d]", inputFilePath.Data(), isSignal);


	/** Aka initialize() **/

	// Used to control output destination
	TString name_affix = "Signal";
	if (!isSignal) {
		name_affix = "Background";
	}

	// Input Tfile
	TFile* inputFile = new TFile(inputFilePath, "READ");
	TTree* tree = (TTree*)inputFile->Get("NOMINAL");

	// Output TFile
	TFile *outputFile = new TFile("outPutFile.root", "recreate");

	TCanvas *canvas = new TCanvas(inputFilePath + "_cutflow", inputFilePath + "_cutflow", 900, 600);

	// Cutflow Hist
	const int nbins = 7;
	TH1D *cutflowhisto = new TH1D (name_affix + "_cutflow", "Events", nbins, 1, nbins + 1);
	cutflowhisto->GetXaxis()->SetBinLabel(1, "All");
	cutflowhisto->GetXaxis()->SetBinLabel(2, "pt>25");
	cutflowhisto->GetXaxis()->SetBinLabel(3, "energy>25");
	cutflowhisto->GetXaxis()->SetBinLabel(4, "medium == 1");
	cutflowhisto->GetXaxis()->SetBinLabel(5, "mt > 40");
	cutflowhisto->GetXaxis()->SetBinLabel(6, "isoTight == 1");
	cutflowhisto->GetXaxis()->SetBinLabel(7, "n_bjets==0");

	// Input TTree
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
	// tree->SetBranchAddress("lep_0_iso_FCTight", &isoTight);
	tree->SetBranchAddress("n_bjets", &n_bjets);
	tree->SetBranchAddress("n_electrons", &n_e);
	tree->SetBranchAddress("n_muons", &n_mu);
	tree->SetBranchAddress("n_taus", &n_t);
	// tree->SetBranchAddress("lep_0", &lep1);
	tree->SetBranchAddress("lepmet_mt", &mt);

	// Output TTree
	Double_t Pt;
	Double_t metE;
	Double_t dPhi;
	Double_t Mt;
	ULong64_t event;

	TString treeName = name_affix;
	TString treeTitle = name_affix + " tree";

	TTree *tree_with_cuts = new TTree(treeName, treeTitle);

	tree_with_cuts->Branch("EventBranch", &event, "EventBranch/I");
	tree_with_cuts->Branch("Pt", &Pt, "Pt/D");
	tree_with_cuts->Branch("metE", &metE, "metE/D");
	tree_with_cuts->Branch("dPhi", &dPhi, "dPhi/D");
	tree_with_cuts->Branch("Mt", &Mt, "Mt/D");


	/** Aka execute() **/

	Long64_t N = tree->GetEntries();
	std::cout << "runEventLoop() N events: " << N << std::endl;
	for (Long64_t i = 0; i < N ; i++)
	{
		// TODO: print this message every 100 events
		// std::cout << "runEventLoop() Processing event " << i << std::endl;
		tree->GetEntry(i);

		cutflowhisto->Fill(1);

		double_t pt = lep->Pt();
		double_t eta = lep->Eta();
		double_t phi = lep->Phi();
		double_t energy = lep->E();
		double_t met_pt = met->Pt();
		double_t met_phi = met->Phi();
		double_t met_energy = met->E();
		double_t phi_tau = fabs(phi - met_phi);
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

		if ( !(n_bjets == 0))continue;
		cutflowhisto->Fill(7);

		if (phi_tau > 3.14159) // TODO: what if phi_tau < -3.14159 ?
		{
			phi_tau = 2 * 3.14159 - phi_tau;
			dPhi = phi_tau;
		}
		else
		{
			dPhi = phi_tau;
		}

		// Fill event to the target tree
		tree_with_cuts->Fill();
	}

	/** Aka finalize() **/
	Info("runEventLoop()", "Take actions on finalize analysis");

	// Close input file
	inputFile->Close();

	// Place gDir pointer to the new TFile
	outputFile->cd();

	// Dump new TTree
	tree_with_cuts->Write();

	// Poing gPad to local canvas
	canvas->cd();

	// Draw
	cutflowhisto->Draw();
	
	cutflowhisto->Write();

	// // Save canvas to the union pdf file
	canvas->Print(GetUnionPDFName());

	return 0;
}
