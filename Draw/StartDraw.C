#include "header.h"

#include "core/runEventLoop.C"


void StartDraw(TString signalFileName = "passToSignalRootFile", TString bkgFileName = "passToBkgRootFile")
{
	cout << "Signal:     " << signalFileName << "\n"
	     << "Background: " << bkgFileName << endl;

	// ATLAS Style
	// This code does not work anymore in ROOT 6. Proof:
	// https://root.cern.ch/root/html600/notes/release-notes.html#using-symbols-that-are-only-available-at-runtime-load-libfoo-foo
	if (gROOT->LoadMacro("AtlasUtils.C") != 0)
	{
		printf("AtlasUtils couldn't have been loaded, bailing out...\n");
		return;
	}

	TCanvas* canvas = new TCanvas("atlas_cu", "cu", 0., 0., 800, 600);
	canvas->Print(GetUnionPDFName() + "[");

	// Run loop over signal.
	/* TODO: replace with class
	Class have to perform following steps:
	 - initialize() - book histograms and initialize variables
	 - execute() - run loop over events
	 - finalyze() - combine histograms, draw plots, finalize analysis
	For now, we have simple one function implementation.
	*/

	// Signal
	if (runEventLoop(signalFileName, true))
		Fatal("StartDraw()", "runEventLoop() returns error status code for %s", signalFileName.Data());

	// Bakground
	if (runEventLoop(bkgFileName, false))
		Fatal("StartDraw()", "runEventLoop() returns error status code for %s", signalFileName.Data());

	// Close union pdf file.
	canvas->SetGridy(0);
	canvas->SetGridx(0);
	canvas->Print(GetUnionPDFName() + "]");
	printf("  Produced: %s\n\n", GetUnionPDFName().Data());
}
