#define FlatTreeAnalyzer_cxx
#include "FlatTreeAnalyzer.h"

#include <TH1D.h>
#include <TFile.h>
#include <TString.h>
#include <TMath.h>
#include <TVector3.h>
#include <TLorentzVector.h>

#include <iomanip>
#include <sstream>
#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

//Function to divide by the bin width and to get xsecs
void Reweight(TH1D* h);

//----------------------------------------//

void FlatTreeAnalyzer::Loop() {

	//----------------------------------------//	

	if (fChain == 0) return;
	Long64_t nentries = fChain->GetEntriesFast();
	Long64_t nbytes = 0, nb = 0;

	double Units = 1E38; // so that the extracted cross-section is in 10^{-38} cm^{2}
	double A = 40.; // so that we can have xsecs per nucleus

	int NInte = 6; // Interaction processes: All, QE, MEC, RES, DIS, COH
	std::vector<TString> InteractionLabels = {"","QE","MEC","RES","DIS","COH"};

	//----------------------------------------//	

        // Output file

	TString FileNameAndPath = "OutputFiles/STVAnalysis_"+fOutputFile+".root";
	TFile* file = new TFile(FileNameAndPath,"recreate");

	std::cout << std::endl << "------------------------------------------------" << std::endl << std::endl;
	std::cout << "File " << FileNameAndPath << " to be created" << std::endl << std::endl;
	
	//----------------------------------------//

	// Plot declaration

	TH1D* TrueMuonCosThetaPlot[NInte];

	//--------------------------------------------------//

	// Loop over the interaction processes

	for (int inte = 0; inte < NInte; inte++) {

	  //--------------------------------------------------//

	  TrueMuonCosThetaPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueMuonCosThetaPlot",";cos(#theta_{#mu})",10,-1.,1.);

	  //--------------------------------------------------//

	} // End of the loop over the interaction processes							

	//----------------------------------------//

	// Counters

	int CounterSTVlikeEventsPassedSelection = 0;
	int CounterSTVlikeQEEventsPassedSelection = 0;
	int CounterSTVlikeMECEventsPassedSelection = 0;
	int CounterSTVlikeRESEventsPassedSelection = 0;
	int CounterSTVlikeDISEventsPassedSelection = 0;
	int CounterSTVlikeCOHEventsPassedSelection = 0;	

	//----------------------------------------//
	
	// Loop over the events

	for (Long64_t jentry=0; jentry<nentries;jentry++) {

	  //----------------------------------------//	
	
	  Long64_t ientry = LoadTree(jentry);
	  if (ientry < 0) break; nb = fChain->GetEntry(jentry); nbytes += nb;
	  if (jentry%1000 == 0) std::cout << jentry/1000 << " k " << std::setprecision(3) << double(jentry)/nentries*100. << " %"<< std::endl;

	  //----------------------------------------//	
		
	  double weight = fScaleFactor*Units*A*Weight;	

	  //----------------------------------------//	

	  if (PDGLep != 13) { continue; } // make sure that we have only a muon in the final state
	  if (cc != 1) { continue; } // make sure that we have only CC interactions		

	  //----------------------------------------//	

	  int ProtonTagging = 0, ChargedPionTagging = 0, NeutralPionTagging = 0, MuonTagging = 0;
	  vector <int> ProtonID; ProtonID.clear();
	  vector <int> MuonID; MuonID.clear();		

	  // Example selection with CC1p0pi (units in GeV/c)

	  for (int i = 0; i < nfsp; i++) {
		
	    double pf = TMath::Sqrt( px[i]*px[i] + py[i]*py[i] + pz[i]*pz[i]);

	    if (pdg[i] == 13 && pf > 0.1) {

	      MuonTagging ++;
	      MuonID.push_back(i);

	    }

	    if (pdg[i] == 2212 && (pf > 0.3 || pf < 1.) ) {

	      ProtonTagging ++;
	      ProtonID.push_back(i);

	    }

	    if (fabs(pdg[i]) == 211 && pf > 0.07)  {

	      ChargedPionTagging ++;

	    }

	    if (pdg[i] == 111)  {

	      NeutralPionTagging ++;

	    }

	  } // End of the loop over the final state particles

	  //----------------------------------------//	

	  // If the signal definition is not satisfied, continue

	  if ( ProtonTagging != 1 || ChargedPionTagging != 0 || NeutralPionTagging != 0 || MuonTagging !=1) { continue; }

	  //----------------------------------------//	

	  // https://arxiv.org/pdf/2106.15809.pdf

	  CounterSTVlikeEventsPassedSelection++;
	
	  // Classify the events based on the interaction type

	  int genie_mode = -1.;
	  if (TMath::Abs(Mode) == 1) { CounterSTVlikeQEEventsPassedSelection++; genie_mode = 1; } // QE
	  else if (TMath::Abs(Mode) == 2) { CounterSTVlikeMECEventsPassedSelection++; genie_mode = 2; } // MEC
	  else if (
		   TMath::Abs(Mode) == 11 || TMath::Abs(Mode) == 12 || TMath::Abs(Mode) == 13 ||
		   TMath::Abs(Mode) == 17 || TMath::Abs(Mode) == 22 || TMath::Abs(Mode) == 23
		   ) { CounterSTVlikeRESEventsPassedSelection++; genie_mode = 3; } // RES
	  else if (TMath::Abs(Mode) == 21 || TMath::Abs(Mode) == 26) { CounterSTVlikeDISEventsPassedSelection++; genie_mode = 4; } // DIS
	  else if (TMath::Abs(Mode) == 16) { CounterSTVlikeCOHEventsPassedSelection++; genie_mode = 5;} // COH
	  else { continue; }  

	  // Feb 8 2022: Only case that is not covered is 15 = diffractive

	  //----------------------------------------//

	  // filling in the histo regardless of interaction mode

	  TrueMuonCosThetaPlot[0]->Fill(CosLep,weight);

	  //----------------------------------------//

	  // filling in the histo based on the interaction mode

	  TrueMuonCosThetaPlot[genie_mode]->Fill(CosLep,weight);

	  //----------------------------------------//
	
	} // End of the loop over the events

	//----------------------------------------//	

	std::cout << "Percetage of events passing the selection cuts = " << 
	double(CounterSTVlikeEventsPassedSelection)/ double(nentries)*100. << " %" << std::endl; std::cout << std::endl;

	std::cout << "Success percetage in selecting QE events = " << 
	double(CounterSTVlikeQEEventsPassedSelection)/ double(CounterSTVlikeEventsPassedSelection)*100. << " %" << std::endl; std::cout << std::endl;

	std::cout << "Success percetage in selecting MEC events = " << 
	double(CounterSTVlikeMECEventsPassedSelection)/ double(CounterSTVlikeEventsPassedSelection)*100. << " %" << std::endl; std::cout << std::endl;

	std::cout << "Success percetage in selecting RES events = " << 
	double(CounterSTVlikeRESEventsPassedSelection)/ double(CounterSTVlikeEventsPassedSelection)*100. << " %" << std::endl; std::cout << std::endl;

	std::cout << "Success percetage in selecting DIS events = " << 
	double(CounterSTVlikeDISEventsPassedSelection)/ double(CounterSTVlikeEventsPassedSelection)*100. << " %" << std::endl; std::cout << std::endl;

	std::cout << "Success percetage in selecting COH events = " << 
	double(CounterSTVlikeCOHEventsPassedSelection)/ double(CounterSTVlikeEventsPassedSelection)*100. << " %" << std::endl; std::cout << std::endl;	

	//----------------------------------------//	
	//----------------------------------------//	

	// Division by bin width to get the cross sections	
	// Loop over the interaction processes

	for (int inte = 0; inte < NInte; inte++) {

		//----------------------------------------//
	
		Reweight(TrueMuonCosThetaPlot[inte]);

		//----------------------------------------//

	} // End of the loop over the interaction processes		

	//----------------------------------------//		
		
	file->cd();
	file->Write();
	fFile->Close();

	std::cout << std::endl;
	std::cout << "File " << FileNameAndPath +" has been created created " << std::endl; 
	std::cout << std::endl;

	std::cout << std::endl << "------------------------------------------------" << std::endl << std::endl;

	//----------------------------------------//		

} // End of the program

//----------------------------------------//		

void Reweight(TH1D* h) {

  int NBins = h->GetXaxis()->GetNbins();

  for (int i = 0; i < NBins; i++) {

    double CurrentEntry = h->GetBinContent(i+1);
    double NewEntry = CurrentEntry / h->GetBinWidth(i+1);

    double CurrentError = h->GetBinError(i+1);
    double NewError = CurrentError / h->GetBinWidth(i+1);

    h->SetBinContent(i+1,NewEntry); 
    h->SetBinError(i+1,NewError); 
    //h->SetBinError(i+1,0.000001); 

  }

}

//----------------------------------------//		
