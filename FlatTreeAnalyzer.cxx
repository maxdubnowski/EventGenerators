#define FlatTreeAnalyzer_cxx
#include "FlatTreeAnalyzer.h"
 
#include <TH1D.h>
#include <TH2D.h>
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

//Function to divide by the bin width and to get xsecs (cross sections)
void Reweight(TH1D* h);


//Aha
void FlatTreeAnalyzer::Loop() {



	if (fChain == 0) return;
	Long64_t nentries = fChain->GetEntriesFast();
	Long64_t nbytes = 0, nb = 0;
	double Units = 1E38; // so that the extracted cross-section is in 10^{-38} cm^{2}
	double A = 40.; // so that we can have xsecs per nucleus
	int NNeut = 6; //Number of Neutrons
	int NInte = 6; // Interaction processes: All, QE, MEC, RES, DIS, COH

	std::vector<TString> InteractionLabels = {"","QE","MEC","RES","DIS","COH"};



        // Output file

	TString FileNameAndPath = "OutputFiles/FlatTreeAnalyzerOutput_"+fOutputFile+".root";
	TFile* file = new TFile(FileNameAndPath,"recreate");

	std::cout << std::endl << "------------------------------------------------" << std::endl << std::endl;
	std::cout << "File " << FileNameAndPath << " to be created" << std::endl << std::endl;
	
	static const int NBinsMuonCosTheta = 18;
	static const double ArrayNBinsMuonCosTheta[NBinsMuonCosTheta+1] = { -1.,-0.85,-0.7,-0.57,-0.45,-0.32,-0.2,-0.1,0.,0.1,0.2,0.3,0.4,0.5,0.6,0.72,0.84,0.95,1.}; //Original from Afro
	//static const double ArrayNBinsMuonCosTheta[NBinsMuonCosTheta+1] = { -1.,-0.85,-0.7,-0.57,-0.45,-0.32,-0.2,-0.1,0.,0.1,0.2,0.3,0.4,0.5,0.6,0.72,0.84,0.99,1.}; //Playing with parameters

	// Plot declaration

	TH1D* TrueMuonCosThetaPlot[NInte][NNeut+1]; //Finding the cos(theta) of the muon 
	TH1D* TrueDeltaPtPlot[NInte][NNeut+1]; //Find the transverse missing momentum plotted against many multiplicities and all neutrino interaction modes
	TH1D* TrueNeutronMultiplicityPlot[NInte]; //Find the Neutron Multiplicity of each interaction
	TH1D* TruePMissingCosThetaPlot[NInte][NNeut]; //Finding the difference between the two multiplicities of the missing momentum direction
	TH1D* TruePMissingMagnitudePlot[NInte][NNeut]; //Finding the difference between the two multiplicities of the missing momentum magnitude
	TH1D* TrueDeltaAlphaTPlot[NInte]; //Find the opening angle between deltaP_T and -p_mu
	TH2D* RecoCosThetaNeutronPlot[NInte]; //Checking the comparison between the reconstructed missing momentum direction to the true neutron direction in Neutron Mult. 1
	TH2D* RecoMagnitudeNeutronPlot[NInte]; //Checking the comparison between the reconstructed missing momentum magnitude to the true neutron momentum magnitude in Neutron Mult. 1
	TH2D* RecoMagnitudeLeadingNeutronPlot[NInte]; //Checking the comparison between the reconstructed missing momentum magnitude to the true leading neutron momentum magnitude in Neutron Mult. 2
	TH2D* RecoCosThetaLeadingNeutronPlot[NInte]; //Checking the comparison between the reconstructed missing momentum direction to the true leading neutron direction in Neutron Mult. 2
	TH2D* TruePMissingMagVsCosPlot[NInte][NNeut]; //Comparing the magnitude and direction of the missing momentum to create additional cuts
	TH2D* RecoNuMomentumMagnitudeVsTruePlot; //Compare the true momentum magnitude of the neutrino before interactions and the reconstructed neutrino momentum magnitude
	TH2D* RecoNuMomentumDirectionVsTruePlot; //Compare the true direction of the neutrino before interactions and the reconstructed neutrino direction



	// Initialize the different plots
	for(int inte=0; inte < NInte; inte++){
	  for (int neut =0; neut<NNeut; neut++){
	    TruePMissingCosThetaPlot[inte][neut] = new TH1D(InteractionLabels[inte] + Form("TruePMissingCosThetaPlot_Neutrons%d", neut), ";cos(#theta_{miss});#frac{d#sigma}{dcos(#theta_{miss})}  [10^{-38} cm^{2}/Ar]", 10,-1,1);
	    TruePMissingMagnitudePlot[inte][neut] = new TH1D(InteractionLabels[inte] + Form("TruePMissingMagnitudePlot_Neutrons%d",neut) , ";p_{miss}  [GeV/c] ;#frac{d#sigma}{dp_{miss}}  [10^{-38} cm^{2}/GeV/c Ar]", 10,0,1);
	  }
	}

	RecoNuMomentumMagnitudeVsTruePlot = new TH2D("RecoNuMomentumMagnitudeVsTruePlot", ";True Magnitude ;Reconstructed Magnitude", 20, 0,3, 20, 0,3);
	RecoNuMomentumDirectionVsTruePlot = new TH2D("RecoNuMomentumDirectionVsTruePlot", ";True Direction ;Reconstructed Direction", 20, -1,1, 20, -1,1);
	


	for (int inte = 0; inte < NInte; inte++) {

	  RecoCosThetaNeutronPlot[inte] = new TH2D(InteractionLabels[inte] + "RecoCosThetaNeutronPlot", ";true cos(#theta_{n});reco cos(#theta_{miss})" , 20,-1,1,20,-1,1);
	  RecoMagnitudeNeutronPlot[inte] = new TH2D(InteractionLabels[inte] + "RecoMagnitudeNeutronPlot", ";true Momentum Magnitude  [GeV/c];reco Momentum Magnitude  [GeV/c]" , 20,0,1.5,20,0,1.5);	  
	  RecoCosThetaLeadingNeutronPlot[inte] = new TH2D(InteractionLabels[inte] + "RecoCosThetaLeadingNeutronPlot", ";true cos(#theta_{n});reco cos(#theta_{mis})" , 20,-1,1,20,-1,1);
	  RecoMagnitudeLeadingNeutronPlot[inte] = new TH2D(InteractionLabels[inte] + "RecoMagnitudeLeadingNeutronPlot", ";true Momentum Magnitude;reco Momentum Magnitude" , 20,0,1.5,20,0,1.5);
	 
	  TrueNeutronMultiplicityPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueNeutronMultiplicityPlot",";Neutron Multiplicity;#frac{d#sigma}{dN}  [10^{-38} cm^{2}/N Ar] ",6,-0.5,5.5);
	  TrueDeltaPtPlot[inte][6] = new TH1D(InteractionLabels[inte] +"TrueDeltaPtPlotAllNeutrons",  ";#deltap_{T}  [GeV/c];#frac{d#sigma}{d#deltap_{T}}  [10^{-38} cm^{2}/GeV/c Ar]", 20,0,1.);
	  TrueDeltaAlphaTPlot[inte] = new TH1D(InteractionLabels[inte] +"TrueDeltaAlphaTPlot", ";#delta#alpha_{T} [deg];#frac{d#sigma}{d#delta#alpha_{T}}  [10^{-38} cm^{2}/deg Ar]", 10,0, 180);
	  //TrueMuonCosThetaPlot[inte][6] = new TH1D(InteractionLabels[inte]+TrueMuonCosThetaPlot",";cos(#theta_{#mu})",100,-1.,1.);
	  TrueMuonCosThetaPlot[inte][6] = new TH1D(InteractionLabels[inte]+"TrueMuonCosThetaPlot", ";cos(#theta_{#mu};#frac{d#sigma}{dcos(#theta_{#mu})}  [10^{-38} cm^{2}/Ar])",NBinsMuonCosTheta,ArrayNBinsMuonCosTheta);

	  for (int neut =0; neut < NNeut; neut++){

	    TrueMuonCosThetaPlot[inte][neut] = new TH1D(InteractionLabels[inte]+"TrueMuonCosThetaPlot_Neutrons"+to_string(neut),";cos(#theta_{#mu}); #frac{d#sigma}{dcos(#theta_{#mu}))}  [10^{-38} cm^{2}/Ar]",18,-1.,1.);
	    TrueDeltaPtPlot[inte][neut] = new TH1D(InteractionLabels[inte]+"TrueDeltaPtPlot_Neutrons"+to_string(neut),";#deltap_{t}  [GeV/c];#frac{d#sigma}{d#deltap_{t}}  [10^{-38} cm^{2}/GeV/c Ar]",20,0.,1.);
	    
	    TruePMissingMagVsCosPlot[inte][neut] = new TH2D(InteractionLabels[inte]+"TruePMissingMagVsCosPlot_Neutrons"+to_string(neut), ";cos(#theta_{miss});Magnitude of p_{missing}  [GeV/c]", 20, -1, 1, 20, 0, 1.5);

	  }
	} // End of the loop over the initialization of plots							





	

	// Counters
	int CounterEventsPassedSelection = 0;
	int CounterQEEventsPassedSelection = 0;
	int CounterMECEventsPassedSelection = 0;
	int CounterRESEventsPassedSelection = 0;
	int CounterDISEventsPassedSelection = 0;
	int CounterCOHEventsPassedSelection = 0;	



	
	// Loop over the events
	for (Long64_t jentry=0; jentry<nentries;jentry++) {
	
	  Long64_t ientry = LoadTree(jentry);
	  if (ientry < 0) break; nb = fChain->GetEntry(jentry); nbytes += nb;
	  if (jentry%1000 == 0) std::cout << jentry/1000 << " k " << std::setprecision(3) << double(jentry)/nentries*100. << " %"<< std::endl;
		
	  double weight = fScaleFactor*Units*A*Weight;	



	  // Signal definition
	  if (PDGLep != 13) { continue; } // make sure that we have only a muon in the final state
	  if (cc != 1) { continue; } // make sure that we have only CC interactions		

	  int ProtonTagging = 0, ChargedPionTagging = 0, NeutralPionTagging = 0, MuonTagging = 0, NeutronTagging = 0;
	  vector <int> ProtonID; ProtonID.clear();
	  vector <int> MuonID; MuonID.clear();
	  vector <int> NeutronID; NeutronID.clear();

	   

	  // Example selection with CC1p0pi (units in GeV/c)
	  // Loop over final state particles
	  
	  

	  for (int i = 0; i < nfsp; i++) {
	    double pf = TMath::Sqrt( px[i]*px[i] + py[i]*py[i] + pz[i]*pz[i]);

	    if (pdg[i] == 2112 ){
	      NeutronTagging++;
	      NeutronID.push_back(i);    
	    }


	    if (pdg[i] == 13 && (pf > 0.1 && pf<1.2)) {
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






	  // If the signal definition is not satisfied, continue
	  if ( ProtonTagging != 1 || ChargedPionTagging != 0 || NeutralPionTagging != 0 || MuonTagging !=1) { continue; }
	  CounterEventsPassedSelection++;
	  // https://arxiv.org/pdf/2106.15809.pdf   :)  
	  



	  // -- Creating the Transverse Missing Momentum Between Proton and Muon -- //
	  TLorentzVector proton4Vector(px[ProtonID[0]], py[ProtonID[0]], pz[ProtonID[0]], E[ProtonID[0]]);
	  TLorentzVector muon4Vector(px[MuonID[0]], py[MuonID[0]], pz[MuonID[0]], E[MuonID[0]]);
	  TVector3 muonTransVector(px[MuonID[0]], py[MuonID[0]],0);
	  double MuonCosTheta = muon4Vector.CosTheta();
	  TVector3 deltapt_vector(muon4Vector.X()+proton4Vector.X(),muon4Vector.Y()+proton4Vector.Y(),0 ); //transverse missing momentum vector
	  double transP = deltapt_vector.Mag(); //transverse missing momentum magnitude   


	  // Creating the missing momentum
	  double ProtonMass_GeV = 0.938272;
	  double protonKE = proton4Vector.E() - ProtonMass_GeV;
	  double CalEnergy = muon4Vector.E() + protonKE  +0.04; //Calorimetric Energy
	  TLorentzVector nu4Vector(0, 0, CalEnergy ,CalEnergy);
	  TVector3 pMissing = (nu4Vector-proton4Vector-muon4Vector).Vect();
	  double pMissingMagnitude = pMissing.Mag();
	  double pMissingDirection = pMissing.CosTheta();
	  
	  //Creating deltaAlphaT 
	  
	  double cosAlpha = (-1.0*(muonTransVector.Dot(deltapt_vector) )) / (muonTransVector.Mag() * deltapt_vector.Mag());
	  double deltaAlphaT = TMath::ACos(cosAlpha)*(180.0 /3.1415926); 

	  // -- Missing momentum cut to reduce the number of neutrons in the final state -- //
	  if (pMissingMagnitude > 0.3 ){ continue; }
	  


	  
	  //Creating the reconstructed and true neutrino energy to test how good the calorimetric energy is to recover energy 
	  TVector3 recoNu_vector = nu4Vector.Vect();
	  TVector3 trueNu_vector(px_init[0], py_init[0], pz_init[0]);
	  double recoNuMag = recoNu_vector.Mag();
	  double recoNuDirection = recoNu_vector.CosTheta();
	  double trueNuMag = trueNu_vector.Mag();
	  double trueNuDirection = trueNu_vector.CosTheta();
	  //cout << "PDG init 0: " << pdg_init[0] << "   PDG init 1: "<< pdg_init[1] << endl;


	
	  // Classify the events based on the interaction type
	  int genie_mode = -1.;
	  if (TMath::Abs(Mode) == 1) { CounterQEEventsPassedSelection++; genie_mode = 1; } // QE
	  else if (TMath::Abs(Mode) == 2) { CounterMECEventsPassedSelection++; genie_mode = 2; } // MEC
	  else if (
		   TMath::Abs(Mode) == 11 || TMath::Abs(Mode) == 12 || TMath::Abs(Mode) == 13 ||
		   TMath::Abs(Mode) == 17 || TMath::Abs(Mode) == 22 || TMath::Abs(Mode) == 23
		   ) { CounterRESEventsPassedSelection++; genie_mode = 3; } // RES
	  else if (TMath::Abs(Mode) == 21 || TMath::Abs(Mode) == 26) { CounterDISEventsPassedSelection++; genie_mode = 4; } // DIS
	  else if (TMath::Abs(Mode) == 16) { CounterCOHEventsPassedSelection++; genie_mode = 5;} // COH
	  else { continue; }  
	  // Feb 8 2022: Only case that is not covered is 15 = diffractive





	  //Fill in the various histograms  
	  RecoNuMomentumMagnitudeVsTruePlot->Fill(trueNuMag, recoNuMag,weight);
	  RecoNuMomentumDirectionVsTruePlot->Fill(trueNuDirection, recoNuDirection,weight);
	  TrueDeltaAlphaTPlot[genie_mode]->Fill(deltaAlphaT , weight);
	  TrueDeltaAlphaTPlot[0]->Fill(deltaAlphaT , weight);
	    
	  
	  
	  TruePMissingCosThetaPlot[genie_mode][NeutronTagging]->Fill(pMissingDirection, weight); 
	  TruePMissingMagnitudePlot[genie_mode][NeutronTagging]->Fill(pMissingMagnitude, weight);
	  

	  if (NeutronTagging ==1){
	    
	    TVector3 neutron_vector(px[NeutronID[0]], py[NeutronID[0]], pz[NeutronID[0]]);   
	    RecoCosThetaNeutronPlot[genie_mode]->Fill(neutron_vector.CosTheta(), pMissingDirection, weight);
	    RecoMagnitudeNeutronPlot[genie_mode]->Fill(neutron_vector.Mag(), pMissingMagnitude, weight);

	  }

	  if (NeutronTagging ==2){
	    TVector3 neutron1_vector(px[NeutronID[0]], py[NeutronID[0]], pz[NeutronID[0]]);
	    TVector3 neutron2_vector(px[NeutronID[1]], py[NeutronID[1]], pz[NeutronID[1]]);
	    TVector3 leadingNeutron = (neutron1_vector.Mag() > neutron2_vector.Mag()) ? neutron1_vector : neutron2_vector;
	    RecoCosThetaLeadingNeutronPlot[genie_mode]->Fill(leadingNeutron.CosTheta(), pMissingDirection, weight);
	    RecoMagnitudeLeadingNeutronPlot[genie_mode]->Fill(leadingNeutron.Mag(), pMissingMagnitude, weight);   
	  }  
	  
	  // filling in the histo regardless of interaction mode
	  TrueNeutronMultiplicityPlot[0]->Fill(NeutronTagging,weight);
      
	  // filling in the histo based on the interaction mode
	  TrueNeutronMultiplicityPlot[genie_mode]->Fill(NeutronTagging,weight);
	  TrueDeltaPtPlot[0][6]->Fill(transP,weight);
	  TrueDeltaPtPlot[genie_mode][6]->Fill(transP,weight);
	  //Filling in Neutron Tagging plots
	  
	  
	  //TrueMuonCosThetaPlot[0][6]->Fill(MuonCosTheta, weight);
	  //TrueMuonCosThetaPlot[genie_mode][6]->Fill(MuonCosTheta, weight);
	  TrueMuonCosThetaPlot[0][6]->Fill(MuonCosTheta, weight);
	  TrueMuonCosThetaPlot[genie_mode][6]->Fill(MuonCosTheta, weight);

	  if (NeutronTagging ==0){
	    TrueMuonCosThetaPlot[0][NeutronTagging]->Fill(MuonCosTheta,weight);
	    TrueDeltaPtPlot[0][NeutronTagging]->Fill(transP,weight);
	  	      	    
	    TrueMuonCosThetaPlot[genie_mode][NeutronTagging]->Fill(MuonCosTheta,weight);
	    TrueDeltaPtPlot[genie_mode][NeutronTagging]->Fill(transP,weight);
	  }


	  else if (NeutronTagging == 1){
	    TrueMuonCosThetaPlot[0][NeutronTagging]->Fill(MuonCosTheta,weight);
	    TrueDeltaPtPlot[0][NeutronTagging]->Fill(transP,weight);
	  	    
	    TrueMuonCosThetaPlot[genie_mode][NeutronTagging]->Fill(MuonCosTheta,weight);
	    TrueDeltaPtPlot[genie_mode][NeutronTagging]->Fill(transP,weight);
	  }


	  else if (NeutronTagging == 2){
	    TrueMuonCosThetaPlot[0][NeutronTagging]->Fill(MuonCosTheta,weight);
	    TrueDeltaPtPlot[0][NeutronTagging]->Fill(transP,weight);
	  	    
	    TrueMuonCosThetaPlot[genie_mode][NeutronTagging]->Fill(MuonCosTheta,weight);
	    TrueDeltaPtPlot[genie_mode][NeutronTagging]->Fill(transP,weight);
	  }


	  else if (NeutronTagging == 3){
	    TrueMuonCosThetaPlot[0][NeutronTagging]->Fill(MuonCosTheta,weight);
	    TrueDeltaPtPlot[0][NeutronTagging]->Fill(transP,weight);
	   
	    
	    TrueMuonCosThetaPlot[genie_mode][NeutronTagging]->Fill(MuonCosTheta,weight);
	    TrueDeltaPtPlot[genie_mode][NeutronTagging]->Fill(transP,weight);
	  }


	  else if (NeutronTagging == 4){
	    TrueMuonCosThetaPlot[0][NeutronTagging]->Fill(MuonCosTheta,weight);
	    TrueDeltaPtPlot[0][NeutronTagging]->Fill(transP,weight);
	   	    
	    TrueMuonCosThetaPlot[genie_mode][NeutronTagging]->Fill(MuonCosTheta,weight);
	    TrueDeltaPtPlot[genie_mode][NeutronTagging]->Fill(transP,weight);
	  }
	  

	  else if (NeutronTagging >=5){
	    TrueMuonCosThetaPlot[0][NeutronTagging]->Fill(MuonCosTheta,weight);
	    TrueDeltaPtPlot[0][NeutronTagging]->Fill(transP,weight);
	    
 	    TrueMuonCosThetaPlot[genie_mode][NeutronTagging]->Fill(MuonCosTheta,weight);
	    TrueDeltaPtPlot[genie_mode][NeutronTagging]->Fill(transP,weight);
	    
	  }

	  // Missing Momentum vs direction
	  if (NeutronTagging >=5) NeutronTagging =5; //Necessary to be last since I don't want to mess with the neutron tagging variable for other plots
	  TruePMissingMagVsCosPlot[genie_mode][NeutronTagging]->Fill(pMissingDirection, pMissingMagnitude, weight);

	} // End of the loop over the events






		
	//Checking Efficiency for the different interaction Mechanisms
	std::cout << "Percetage of events passing the selection cuts = " << 
	double(CounterEventsPassedSelection)/ double(nentries)*100. << " %" << std::endl; std::cout << std::endl;

	std::cout << "Success percetage in selecting QE events = " << 
	double(CounterQEEventsPassedSelection)/ double(CounterEventsPassedSelection)*100. << " %" << std::endl; std::cout << std::endl;

	std::cout << "Success percetage in selecting MEC events = " << 
	double(CounterMECEventsPassedSelection)/ double(CounterEventsPassedSelection)*100. << " %" << std::endl; std::cout << std::endl;

	std::cout << "Success percetage in selecting RES events = " << 
	double(CounterRESEventsPassedSelection)/ double(CounterEventsPassedSelection)*100. << " %" << std::endl; std::cout << std::endl;

	std::cout << "Success percetage in selecting DIS events = " << 
	double(CounterDISEventsPassedSelection)/ double(CounterEventsPassedSelection)*100. << " %" << std::endl; std::cout << std::endl;

	std::cout << "Success percetage in selecting COH events = " << 
	double(CounterCOHEventsPassedSelection)/ double(CounterEventsPassedSelection)*100. << " %" << std::endl; std::cout << std::endl;	






	// Division by bin width to get the cross sections	
	// Loop over the interaction processes and Neutron Multiplicities
	for (int inte = 0; inte < NInte; inte++) {
	  Reweight(TrueNeutronMultiplicityPlot[inte]);
	  Reweight(TrueDeltaAlphaTPlot[inte]);
	  for (int neut =0; neut < NNeut; neut++){
	    Reweight(TrueMuonCosThetaPlot[inte][neut]);
	    Reweight(TrueDeltaPtPlot[inte][neut]);
	    
	    Reweight(TruePMissingCosThetaPlot[inte][neut]);
	    Reweight(TruePMissingMagnitudePlot[inte][neut]);
	  }
	} // End of the loop over the interaction processes		

	


		
	file->cd();
	file->Write();
	fFile->Close();

	std::cout << std::endl;
	std::cout << "File " << FileNameAndPath +" has been created created " << std::endl; 
	std::cout << std::endl;

	std::cout << std::endl << "------------------------------------------------" << std::endl << std::endl;

} // End of the program





		

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


