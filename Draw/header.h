/**
	Set of common methods that get used in analysis scripts.
*/

/** Here is the place we will save all output */
TString GetUnionPDFName()
{
	return TString("AllPlots.pdf");
}


/** Function that takes care of histogram Normalization*/
int NormalizeXaxis(TH1* histData)
{
	float first_max_bin_data = histData->GetBinContent(histData->GetBin(1));
	// cout<<first_max_bin_data<<endl;
	for (int i = 0; i <= (histData->GetNbinsX()); i++)
		histData->SetBinContent(i, float(histData->GetBinContent(i)) / first_max_bin_data);

	return 0;
}

/** Provides list of some nice colors */
int GetNiceColor(const int nHist)
{
	if (nHist >= 10)
		Fatal("GetNiceColor", "You are asking color for newNHist=%d, but %d is a limit.", nHist, 10);

	int arrColor[10] = { kRed, kOrange - 3, kGreen + 2, kCyan + 2, kBlue + 2, kMagenta + 2, 8, 28, 7, kYellow + 2 };
	cout << "GetNiceColor():: Return color " << arrColor[nHist];
	return arrColor[nHist];
}