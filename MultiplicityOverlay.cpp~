#include <TFile.h>
#include <TTree.h>
#include <TString.h>

using namespace std;

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <fstream>
#include <stdlib.h>

void GeneratorOverlay() {

	//------------------------------//

	TH1D::SetDefaultSumw2();
	TH2D::SetDefaultSumw2();
	gStyle->SetOptStat(0);

	int FontStyle = 132;
	double TextSize = 0.06;			

	TString OutFilePath = "/uboone/app/users/maxd/BuildEventGenerators/FlatTreeAnalyzer/OutputFiles/";

	//------------------------------//

	// Event generators

	std::vector<TString> Names; std::vector<TString> Labels; std::vector<int> Colors;
	
	Names.push_back(OutFilePath+"FlatTreeAnalyzerOutput_GENIE.root"); 
	Labels.push_back("GENIE");
	Colors.push_back(kBlue+2);	

	Names.push_back(OutFilePath+"FlatTreeAnalyzerOutput_NuWro.root"); 
	Labels.push_back("NuWro");
	Colors.push_back(kRed+1);

	Names.push_back(OutFilePath+"FlatTreeAnalyzerOutput_NEUT.root"); 
	Labels.push_back("NEUT");
	Colors.push_back(kOrange+7);

	Names.push_back(OutFilePath+"FlatTreeAnalyzerOutput_GiBUU.root"); 
	Labels.push_back("GiBUU");
	Colors.push_back(kGreen+1);			

	const int NSamples = Names.size();
	std::vector<TFile*> Files; Files.resize(NSamples);

	//------------------------------//

	// Plots to overlay

	std::vector<TString> PlotNames;
	///*
	//
	int NNeut = 6;
	for (int neut =0; neut < NNeut; neut++){
	  /*
	  PlotNames.push_back(Form("TrueMuonCosThetaPlot_Neutrons%d",neut));
	  PlotNames.push_back(Form("TrueDeltaPtPlot_Neutrons%d",neut));
	  PlotNames.push_back(Form("MECTrueDeltaPtPlot_Neutrons%d",neut));
	  PlotNames.push_back(Form("QETrueDeltaPtPlot_Neutrons%d",neut));
	  PlotNames.push_back(Form("RESTrueDeltaPtPlot_Neutrons%d",neut));
	  PlotNames.push_back(Form("DISTrueDeltaPtPlot_Neutrons%d",neut));
	  PlotNames.push_back(Form("COHTrueDeltaPtPlot_Neutrons%d",neut));
	//}

	  */
	PlotNames.push_back(Form("TrueNeutronMultiplicityPlot_Neutrons%d", neut));
	/*	
	PlotNames.push_back("QETrueNeutronMultiplicityPlot");	
	PlotNames.push_back("MECTrueNeutronMultiplicityPlot");
	PlotNames.push_back("RESTrueNeutronMultiplicityPlot");
	PlotNames.push_back("DISTrueNeutronMultiplicityPlot");
	PlotNames.push_back("COHTrueNeutronMultiplicityPlot");
	*/
	}
	const int NPlots = PlotNames.size();

	//------------------------------//	

	// Loop over the samples to open the files and the TTree

	for (int iSample = 0; iSample < NSamples; iSample++) {

		Files[iSample] = new TFile(Names[iSample],"readonly");

	} // End of the loop over the samples

	//------------------------------//

	// Loop over the plots to be compared

	for (int iPlot = 0; iPlot < NPlots; iPlot++) {

		TString CanvasName = "Canvas_" + PlotNames[iPlot];
		TCanvas* PlotCanvas = new TCanvas(CanvasName,CanvasName,205,34,1024,768);
		PlotCanvas->cd();
		PlotCanvas->SetTopMargin(0.12);
		PlotCanvas->SetLeftMargin(0.15);
		PlotCanvas->SetBottomMargin(0.15);		
		PlotCanvas->Draw();	

		TLegend* leg = new TLegend(0.2,0.7,0.55,0.83);
		leg->SetBorderSize(0);
		leg->SetNColumns(2);
		leg->SetTextSize(TextSize);	
		leg->SetTextFont(FontStyle);						

		// Loop over the samples to open the files and to get the corresponding plot

		std::vector<TH1D*> Histos; Histos.resize(NSamples);

		for (int iSample = 0; iSample < NSamples; iSample++) {	

		        Histos[iSample] = (TH1D*)(Files[iSample]->Get(PlotNames[iPlot]));

			Histos[iSample]->SetLineWidth(4);
			Histos[iSample]->SetLineColor( Colors.at(iSample) );	

			Histos[iSample]->GetXaxis()->SetTitleFont(FontStyle);
			Histos[iSample]->GetXaxis()->SetLabelFont(FontStyle);
			Histos[iSample]->GetXaxis()->SetNdivisions(8);
			Histos[iSample]->GetXaxis()->SetLabelSize(TextSize);
			Histos[iSample]->GetXaxis()->SetTitleSize(TextSize);	
			Histos[iSample]->GetXaxis()->SetTitleOffset(1.1);					
			Histos[iSample]->GetXaxis()->CenterTitle();						

			Histos[iSample]->GetYaxis()->SetTitleFont(FontStyle);
			Histos[iSample]->GetYaxis()->SetLabelFont(FontStyle);
			Histos[iSample]->GetYaxis()->SetNdivisions(6);
			Histos[iSample]->GetYaxis()->SetLabelSize(TextSize);
			Histos[iSample]->GetYaxis()->SetTitle("Cross Section [10^{-38} cm^{2}/Ar]");
			Histos[iSample]->GetYaxis()->SetTitleSize(TextSize);
			Histos[iSample]->GetYaxis()->SetTitleOffset(1.3);
			Histos[iSample]->GetYaxis()->SetTickSize(0);
			Histos[iSample]->GetYaxis()->CenterTitle();	

			double imax = TMath::Max(Histos[iSample]->GetMaximum(),Histos[0]->GetMaximum());			
			Histos[iSample]->GetYaxis()->SetRangeUser(0.,1.1*imax);
			Histos[0]->GetYaxis()->SetRangeUser(0.,1.1*imax);			

			PlotCanvas->cd();
			Histos[iSample]->Draw("hist same");
			Histos[0]->Draw("hist same");	

			leg->AddEntry(Histos[iSample],Labels[iSample],"l");
			
			//----------------------------------------//					

		} // End of the loop over the samples grabing the plots	

		PlotCanvas->cd();
		leg->Draw();

	} // End of the loop over the plots

	//------------------------------//

} // End of the program
