#define myNEUTAnalysis_cxx
#include "myNEUTAnalysis.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH1D.h>
#include <TFile.h>
#include <iomanip>
#include <TString.h>
#include <TMath.h>
#include <TVector3.h>
#include <TLorentzVector.h>
#include <TRandom.h>

#include <sstream>
#include <iostream>
#include <vector>
#include <iterator>

#include "../myClasses/Tools.h"
#include "../myClasses/STV_Tools.h"
#include "../myClasses/Util.h"

using namespace std;

//----------------------------------------//

void myNEUTAnalysis::Loop() {

	//----------------------------------------//	

	if (fChain == 0) return;
	Long64_t nentries = fChain->GetEntriesFast();
	Long64_t nbytes = 0, nb = 0;

	//-----------------------------------------//

	Tools tools;	
	
	//----------------------------------------//	

	TString FileNameAndPath = "OutputFiles/STVAnalysis_"+fOutputFile+".root";
	TFile* file = new TFile(FileNameAndPath,"recreate");
	std::cout << std::endl << std::endl;
	
	//----------------------------------------//
	
	// 1D analysis

	TH1D* TrueVertexXPlot[NInte];
	TH1D* TrueVertexYPlot[NInte];
	TH1D* TrueVertexZPlot[NInte];	

	TH1D* TrueStruckNucleonMomPlot[NInte];

	TH1D* TrueDeltaPTPlot[NInte];
	TH1D* TrueDeltaAlphaTPlot[NInte];
	TH1D* TrueDeltaAlpha3DqPlot[NInte];
	TH1D* TrueDeltaAlpha3DMuPlot[NInte];		
	TH1D* TrueDeltaPhiTPlot[NInte];
	TH1D* TrueDeltaPhi3DPlot[NInte];	
	TH1D* TrueDeltaPLPlot[NInte];
	TH1D* TrueDeltaPnPlot[NInte];
	TH1D* TrueDeltaPnPerpPlot[NInte];
	TH1D* TrueDeltaPnPerpxPlot[NInte];
	TH1D* TrueDeltaPnPerpyPlot[NInte];		
	TH1D* TrueDeltaPnParPlot[NInte];		
	TH1D* TrueDeltaPtxPlot[NInte];
	TH1D* TrueDeltaPtyPlot[NInte];
	TH1D* TrueAPlot[NInte];
	TH1D* TrueMuonMomentumPlot[NInte];
	TH1D* TrueMuonPhiPlot[NInte];
	TH1D* TrueMuonCosThetaPlot[NInte];
	TH1D* TrueMuonCosThetaSingleBinPlot[NInte];
	TH1D* TrueProtonMomentumPlot[NInte];
	TH1D* TrueProtonPhiPlot[NInte];
	TH1D* TrueProtonCosThetaPlot[NInte];
	TH1D* TrueECalPlot[NInte];
	TH1D* TrueEQEPlot[NInte];
	TH1D* TrueQ2Plot[NInte];
	TH1D* TrueCCQEMuonMomentumPlot[NInte];
	TH1D* TrueCCQEMuonPhiPlot[NInte];
	TH1D* TrueCCQEMuonCosThetaPlot[NInte];	
	TH1D* TrueCCQEProtonMomentumPlot[NInte];
	TH1D* TrueCCQEProtonPhiPlot[NInte];
	TH1D* TrueCCQEProtonCosThetaPlot[NInte];
	TH1D* TrueCCQEECalPlot[NInte];
	TH1D* TrueCCQEQ2Plot[NInte];	
	TH1D* TruekMissPlot[NInte];
	TH1D* TruePMissMinusPlot[NInte];
	TH1D* TruePMissPlot[NInte];

	//--------------------------------------------------//

	// 2D analysis (uncorrelated)

	TH1D* TrueDeltaPT_InMuonCosThetaTwoDPlot[NInte][TwoDNBinsMuonCosTheta];
	TH1D* TrueDeltaPT_InProtonCosThetaTwoDPlot[NInte][TwoDNBinsProtonCosTheta];	
	TH1D* TrueDeltaPT_InDeltaAlphaTTwoDPlot[NInte][TwoDNBinsDeltaAlphaT];
	TH1D* TrueDeltaPn_InDeltaAlpha3DqTwoDPlot[NInte][TwoDNBinsDeltaAlpha3Dq];
	TH1D* TrueDeltaPn_InDeltaAlpha3DMuTwoDPlot[NInte][TwoDNBinsDeltaAlpha3DMu];		
	TH1D* TrueProtonMomentum_InDeltaAlphaTTwoDPlot[NInte][TwoDNBinsDeltaAlphaT];	
	TH1D* TrueDeltaPn_InDeltaAlphaTTwoDPlot[NInte][TwoDNBinsDeltaAlphaT];	
	TH1D* TrueMuonMomentum_InMuonCosThetaTwoDPlot[NInte][TwoDNBinsMuonCosTheta];
	TH1D* TrueProtonMomentum_InProtonCosThetaTwoDPlot[NInte][TwoDNBinsProtonCosTheta];			
	TH1D* TrueDeltaAlphaT_InMuonCosThetaTwoDPlot[NInte][TwoDNBinsMuonCosTheta];
	TH1D* TrueDeltaAlphaT_InMuonMomentumTwoDPlot[NInte][TwoDNBinsMuonMomentum];	
	TH1D* TrueDeltaAlphaT_InProtonCosThetaTwoDPlot[NInte][TwoDNBinsProtonCosTheta];
	TH1D* TrueDeltaAlphaT_InProtonMomentumTwoDPlot[NInte][TwoDNBinsProtonMomentum];			
	TH1D* TrueDeltaAlphaT_InDeltaPTTwoDPlot[NInte][TwoDNBinsDeltaPT];
	TH1D* TrueDeltaAlpha3Dq_InDeltaPnTwoDPlot[NInte][TwoDNBinsDeltaPn];
	TH1D* TrueDeltaAlpha3DMu_InDeltaPnTwoDPlot[NInte][TwoDNBinsDeltaPn];					
	TH1D* TrueProtonCosTheta_InMuonCosThetaTwoDPlot[NInte][TwoDNBinsProtonCosTheta];	
	TH1D* TrueDeltaPhiT_InDeltaPTTwoDPlot[NInte][TwoDNBinsDeltaPT];	
	TH1D* TrueDeltaPn_InDeltaPTTwoDPlot[NInte][TwoDNBinsDeltaPT];
	TH1D* TrueDeltaPty_InDeltaPtxTwoDPlot[NInte][TwoDNBinsDeltaPtx];
	TH1D* TrueDeltaPtx_InDeltaPtyTwoDPlot[NInte][TwoDNBinsDeltaPty];	
	TH1D* TrueECal_InDeltaAlphaTTwoDPlot[NInte][TwoDNBinsDeltaAlphaT];	
	TH1D* TrueECal_InDeltaPTTwoDPlot[NInte][TwoDNBinsDeltaPT];
	TH1D* TrueECal_InDeltaPtxTwoDPlot[NInte][TwoDNBinsDeltaPtx];
	TH1D* TrueECal_InDeltaPtyTwoDPlot[NInte][TwoDNBinsDeltaPty];	

	//--------------------------------------------------//	

	// 3D analysis (uncorrelated)	

	TH1D* TrueECal_InDeltaPTDeltaAlphaTTwoDPlot[NInte][TwoDNBinsDeltaPT][TwoDNBinsDeltaAlphaT];
	TH1D* TrueECal_InDeltaPtxDeltaPtyTwoDPlot[NInte][TwoDNBinsDeltaPT][TwoDNBinsDeltaAlphaT];	
	TH1D* TrueECal_InMuonCosThetaMuonMomentumTwoDPlot[NInte][TwoDNBinsMuonCosTheta][TwoDNBinsMuonMomentum];
	TH1D* TrueECal_InProtonCosThetaProtonMomentumTwoDPlot[NInte][TwoDNBinsProtonCosTheta][TwoDNBinsProtonMomentum];	

	//--------------------------------------------------//

	// 2D analysis in 1D grid	

	TH1D* SerialTrueDeltaPT_InMuonCosThetaPlot[NInte];
	TH1D* SerialTrueDeltaPT_InProtonCosThetaPlot[NInte];
	TH1D* SerialTrueDeltaPT_InDeltaAlphaTPlot[NInte];
	TH1D* SerialTrueDeltaPn_InDeltaAlpha3DqPlot[NInte];
	TH1D* SerialTrueDeltaPn_InDeltaAlpha3DMuPlot[NInte];		
	TH1D* SerialTrueProtonMomentum_InDeltaAlphaTPlot[NInte];	
	TH1D* SerialTrueMuonMomentum_InMuonCosThetaPlot[NInte];
	TH1D* SerialTrueProtonMomentum_InProtonCosThetaPlot[NInte];	
	TH1D* SerialTrueDeltaAlphaT_InMuonCosThetaPlot[NInte];
	TH1D* SerialTrueDeltaAlphaT_InMuonMomentumPlot[NInte];	
	TH1D* SerialTrueDeltaAlphaT_InProtonCosThetaPlot[NInte];
	TH1D* SerialTrueDeltaAlphaT_InProtonMomentumPlot[NInte];	
	TH1D* SerialTrueDeltaAlphaT_InDeltaPTPlot[NInte];
	TH1D* SerialTrueDeltaAlpha3Dq_InDeltaPnPlot[NInte];
	TH1D* SerialTrueDeltaAlpha3DMu_InDeltaPnPlot[NInte];				
	TH1D* SerialTrueDeltaPhiT_InDeltaPTPlot[NInte];
	TH1D* SerialTrueDeltaPn_InDeltaPTPlot[NInte];
	TH1D* SerialTrueDeltaPn_InDeltaAlphaTPlot[NInte];	
	TH1D* SerialTrueProtonCosTheta_InMuonCosThetaPlot[NInte];
	TH1D* SerialTrueDeltaPty_InDeltaPtxPlot[NInte];
	TH1D* SerialTrueDeltaPtx_InDeltaPtyPlot[NInte];
	TH1D* SerialTrueECal_InDeltaPTPlot[NInte];
	TH1D* SerialTrueECal_InDeltaPtxPlot[NInte];
	TH1D* SerialTrueECal_InDeltaPtyPlot[NInte];	
	TH1D* SerialTrueECal_InDeltaAlphaTPlot[NInte];

	//--------------------------------------------------//	

	// 3D analysis in 1D grid		
	
	TH1D* SerialTrueECal_InDeltaPTDeltaAlphaTPlot[NInte];
	TH1D* SerialTrueECal_InDeltaPtxDeltaPtyPlot[NInte];	
	TH1D* SerialTrueECal_InMuonCosThetaMuonMomentumPlot[NInte];
	TH1D* SerialTrueECal_InProtonCosThetaProtonMomentumPlot[NInte];

	//--------------------------------------------------//

	// Loop over the interaction processes

	for (int inte = 0; inte < NInte; inte++) {

		//--------------------------------------------------//

		// 1D analysis

		TrueVertexXPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueVertexXPlot",RecoLabelXAxisVertexX,NBinsVertexX,MinVertexX,MaxVertexX);
		TrueVertexYPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueVertexYPlot",RecoLabelXAxisVertexY,NBinsVertexY,MinVertexY,MaxVertexY);
		TrueVertexZPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueVertexZPlot",RecoLabelXAxisVertexZ,NBinsVertexZ,MinVertexZ,MaxVertexZ);		

		TrueStruckNucleonMomPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueStruckNucleonMomPlot",LabelXAxisDeltaPT,NBinsDeltaPT,ArrayNBinsDeltaPT);

		TrueDeltaPTPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueDeltaPTPlot",LabelXAxisDeltaPT,NBinsDeltaPT,ArrayNBinsDeltaPT);
		TrueDeltaAlphaTPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueDeltaAlphaTPlot",LabelXAxisDeltaAlphaT,NBinsDeltaAlphaT,ArrayNBinsDeltaAlphaT);
		TrueDeltaAlpha3DqPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueDeltaAlpha3DqPlot",LabelXAxisDeltaAlpha3Dq,NBinsDeltaAlpha3Dq,ArrayNBinsDeltaAlpha3Dq);
		TrueDeltaAlpha3DMuPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueDeltaAlpha3DMuPlot",LabelXAxisDeltaAlpha3DMu,NBinsDeltaAlpha3DMu,ArrayNBinsDeltaAlpha3DMu);				
		TrueDeltaPhiTPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueDeltaPhiTPlot",LabelXAxisDeltaPhiT,NBinsDeltaPhiT,ArrayNBinsDeltaPhiT);
		TrueDeltaPhi3DPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueDeltaPhi3DPlot",LabelXAxisDeltaPhi3D,NBinsDeltaPhi3D,ArrayNBinsDeltaPhi3D);		
		TrueDeltaPLPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueDeltaPLPlot",LabelXAxisDeltaPL,NBinsDeltaPL,ArrayNBinsDeltaPL);
		TrueDeltaPnPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueDeltaPnPlot",LabelXAxisDeltaPn,NBinsDeltaPn,ArrayNBinsDeltaPn);
		TrueDeltaPnPerpPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueDeltaPnPerpPlot",LabelXAxisDeltaPnPerp,NBinsDeltaPnPerp,ArrayNBinsDeltaPnPerp);
		TrueDeltaPnPerpxPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueDeltaPnPerpxPlot",LabelXAxisDeltaPnPerpx,NBinsDeltaPnPerpx,ArrayNBinsDeltaPnPerpx);
		TrueDeltaPnPerpyPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueDeltaPnPerpyPlot",LabelXAxisDeltaPnPerpy,NBinsDeltaPnPerpy,ArrayNBinsDeltaPnPerpy);				
		TrueDeltaPnParPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueDeltaPnParPlot",LabelXAxisDeltaPnPar,NBinsDeltaPnPar,ArrayNBinsDeltaPnPar);				
		TrueDeltaPtxPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueDeltaPtxPlot",LabelXAxisDeltaPtx,NBinsDeltaPtx,ArrayNBinsDeltaPtx);
		TrueDeltaPtyPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueDeltaPtyPlot",LabelXAxisDeltaPty,NBinsDeltaPty,ArrayNBinsDeltaPty);
		TrueAPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueAPlot",LabelXAxisA,NBinsA,ArrayNBinsA);
		TrueMuonMomentumPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueMuonMomentumPlot",LabelXAxisMuonMomentum,NBinsMuonMomentum,ArrayNBinsMuonMomentum);
		TrueMuonPhiPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueMuonPhiPlot",LabelXAxisMuonPhi,NBinsMuonPhi,ArrayNBinsMuonPhi);
		TrueMuonCosThetaPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueMuonCosThetaPlot",LabelXAxisMuonCosTheta,NBinsMuonCosTheta,ArrayNBinsMuonCosTheta);
		TrueMuonCosThetaSingleBinPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueMuonCosThetaSingleBinPlot",LabelXAxisMuonCosTheta,1,0.,1.);
		TrueProtonMomentumPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueProtonMomentumPlot",LabelXAxisProtonMomentum,NBinsProtonMomentum,ArrayNBinsProtonMomentum);
		TrueProtonPhiPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueProtonPhiPlot",LabelXAxisProtonPhi,NBinsProtonPhi,ArrayNBinsProtonPhi);
		TrueProtonCosThetaPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueProtonCosThetaPlot",LabelXAxisProtonCosTheta,NBinsProtonCosTheta,ArrayNBinsProtonCosTheta);
		TrueECalPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueECalPlot",LabelXAxisECal,NBinsECal,ArrayNBinsECal);
		TrueEQEPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueEQEPlot",LabelXAxisEQE,NBinsEQE,ArrayNBinsEQE);
		TrueQ2Plot[inte] = new TH1D(InteractionLabels[inte]+"TrueQ2Plot",LabelXAxisQ2,NBinsQ2,ArrayNBinsQ2);
		TrueCCQEMuonMomentumPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueCCQEMuonMomentumPlot",LabelXAxisMuonMomentum,CCQENBinsMuonMomentum,CCQEArrayNBinsMuonMomentum);
		TrueCCQEMuonPhiPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueCCQEMuonPhiPlot",LabelXAxisMuonPhi,CCQENBinsMuonPhi,CCQEArrayNBinsMuonPhi);
		TrueCCQEMuonCosThetaPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueCCQEMuonCosThetaPlot",LabelXAxisMuonCosTheta,CCQENBinsMuonCosTheta,CCQEArrayNBinsMuonCosTheta);	
		TrueCCQEProtonMomentumPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueCCQEProtonMomentumPlot",LabelXAxisProtonMomentum,CCQENBinsProtonMomentum,CCQEArrayNBinsProtonMomentum);
		TrueCCQEProtonPhiPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueCCQEProtonPhiPlot",LabelXAxisProtonPhi,CCQENBinsProtonPhi,CCQEArrayNBinsProtonPhi);
		TrueCCQEProtonCosThetaPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueCCQEProtonCosThetaPlot",LabelXAxisProtonCosTheta,CCQENBinsProtonCosTheta,CCQEArrayNBinsProtonCosTheta);
		TrueCCQEECalPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueCCQEECalPlot",LabelXAxisECal,CCQENBinsECal,CCQEArrayNBinsECal);
		TrueCCQEQ2Plot[inte] = new TH1D(InteractionLabels[inte]+"TrueCCQEQ2Plot",LabelXAxisQ2,CCQENBinsQ2,CCQEArrayNBinsQ2);	
		TruekMissPlot[inte] = new TH1D(InteractionLabels[inte]+"TruekMissPlot",LabelXAxiskMiss,NBinskMiss,ArrayNBinskMiss);
		TruePMissMinusPlot[inte] = new TH1D(InteractionLabels[inte]+"TruePMissMinusPlot",LabelXAxisPMissMinus,NBinsPMissMinus,ArrayNBinsPMissMinus);
		TruePMissPlot[inte] = new TH1D(InteractionLabels[inte]+"TruePMissPlot",LabelXAxisPMiss,NBinsPMiss,ArrayNBinsPMiss);

		//--------------------------------------------------//	

		// 2D & 3D analysis (uncorrelated)

		for (int WhichDeltaPn = 0; WhichDeltaPn < TwoDNBinsDeltaPn; WhichDeltaPn++) {

			TString DeltaAlpha3DqTwoDInDeltaPnLabel = "DeltaAlpha3Dq_DeltaPn_"+tools.ConvertToString(TwoDArrayNBinsDeltaPn[WhichDeltaPn])+"To"+tools.ConvertToString(TwoDArrayNBinsDeltaPn[WhichDeltaPn+1])+"Plot";			
			TrueDeltaAlpha3Dq_InDeltaPnTwoDPlot[inte][WhichDeltaPn] = new TH1D(InteractionLabels[inte]+"True"+DeltaAlpha3DqTwoDInDeltaPnLabel,LabelXAxisDeltaAlpha3Dq,TwoDArrayNBinsDeltaAlpha3DqInDeltaPnSlices[WhichDeltaPn].size()-1,&TwoDArrayNBinsDeltaAlpha3DqInDeltaPnSlices[WhichDeltaPn][0]);

			TString DeltaAlpha3DMuTwoDInDeltaPnLabel = "DeltaAlpha3DMu_DeltaPn_"+tools.ConvertToString(TwoDArrayNBinsDeltaPn[WhichDeltaPn])+"To"+tools.ConvertToString(TwoDArrayNBinsDeltaPn[WhichDeltaPn+1])+"Plot";			
			TrueDeltaAlpha3DMu_InDeltaPnTwoDPlot[inte][WhichDeltaPn] = new TH1D(InteractionLabels[inte]+"True"+DeltaAlpha3DMuTwoDInDeltaPnLabel,LabelXAxisDeltaAlpha3DMu,TwoDArrayNBinsDeltaAlpha3DMuInDeltaPnSlices[WhichDeltaPn].size()-1,&TwoDArrayNBinsDeltaAlpha3DMuInDeltaPnSlices[WhichDeltaPn][0]);			

		}

		for (int WhichDeltaPT = 0; WhichDeltaPT < TwoDNBinsDeltaPT; WhichDeltaPT++) {

			TString DeltaAlphaTTwoDInDeltaPTLabel = "DeltaAlphaT_DeltaPT_"+tools.ConvertToString(TwoDArrayNBinsDeltaPT[WhichDeltaPT])+"To"+tools.ConvertToString(TwoDArrayNBinsDeltaPT[WhichDeltaPT+1])+"Plot";			
			TrueDeltaAlphaT_InDeltaPTTwoDPlot[inte][WhichDeltaPT] = new TH1D(InteractionLabels[inte]+"True"+DeltaAlphaTTwoDInDeltaPTLabel,LabelXAxisDeltaAlphaT,TwoDArrayNBinsDeltaAlphaTInDeltaPTSlices[WhichDeltaPT].size()-1,&TwoDArrayNBinsDeltaAlphaTInDeltaPTSlices[WhichDeltaPT][0]);

			TString ECalTwoDInDeltaPTLabel = "ECal_DeltaPT_"+tools.ConvertToString(TwoDArrayNBinsDeltaPT[WhichDeltaPT])+"To"+tools.ConvertToString(TwoDArrayNBinsDeltaPT[WhichDeltaPT+1])+"Plot";			
			TrueECal_InDeltaPTTwoDPlot[inte][WhichDeltaPT] = new TH1D(InteractionLabels[inte]+"True"+ECalTwoDInDeltaPTLabel,LabelXAxisECal,TwoDArrayNBinsECalInDeltaPTSlices[WhichDeltaPT].size()-1,&TwoDArrayNBinsECalInDeltaPTSlices[WhichDeltaPT][0]);		


			TString DeltaPhiTTwoDInDeltaPTLabel = "DeltaPhiT_DeltaPT_"+tools.ConvertToString(TwoDArrayNBinsDeltaPT[WhichDeltaPT])+"To"+tools.ConvertToString(TwoDArrayNBinsDeltaPT[WhichDeltaPT+1])+"Plot";			
			TrueDeltaPhiT_InDeltaPTTwoDPlot[inte][WhichDeltaPT] = new TH1D(InteractionLabels[inte]+"True"+DeltaPhiTTwoDInDeltaPTLabel,LabelXAxisDeltaPhiT,TwoDArrayNBinsDeltaPhiTInDeltaPTSlices[WhichDeltaPT].size()-1,&TwoDArrayNBinsDeltaPhiTInDeltaPTSlices[WhichDeltaPT][0]);	

			TString DeltaPnTwoDInDeltaPTLabel = "DeltaPn_DeltaPT_"+tools.ConvertToString(TwoDArrayNBinsDeltaPT[WhichDeltaPT])+"To"+tools.ConvertToString(TwoDArrayNBinsDeltaPT[WhichDeltaPT+1])+"Plot";			
			TrueDeltaPn_InDeltaPTTwoDPlot[inte][WhichDeltaPT] = new TH1D(InteractionLabels[inte]+"True"+DeltaPnTwoDInDeltaPTLabel,LabelXAxisDeltaPn,TwoDArrayNBinsDeltaPnInDeltaPTSlices[WhichDeltaPT].size()-1,&TwoDArrayNBinsDeltaPnInDeltaPTSlices[WhichDeltaPT][0]);	

			for (int WhichDeltaAlphaT = 0; WhichDeltaAlphaT < TwoDNBinsDeltaAlphaT; WhichDeltaAlphaT++) {	

				TString ECalTwoDInDeltaPTDeltaAlphaTLabel = "ECal_DeltaPT_"+tools.ConvertToString(TwoDArrayNBinsDeltaPT[WhichDeltaPT])+"To"+tools.ConvertToString(TwoDArrayNBinsDeltaPT[WhichDeltaPT+1])+"_DeltaAlphaT_"+tools.ConvertToString(TwoDArrayNBinsDeltaAlphaT[WhichDeltaAlphaT])+"To"+tools.ConvertToString(TwoDArrayNBinsDeltaAlphaT[WhichDeltaAlphaT+1])+"Plot";
				TrueECal_InDeltaPTDeltaAlphaTTwoDPlot[inte][WhichDeltaPT][WhichDeltaAlphaT] = new TH1D(InteractionLabels[inte]+"True"+ECalTwoDInDeltaPTDeltaAlphaTLabel,LabelXAxisECal,TwoDArrayNBinsECalInDeltaPTDeltaAlphaTSlices[WhichDeltaPT][WhichDeltaAlphaT].size()-1,&TwoDArrayNBinsECalInDeltaPTDeltaAlphaTSlices[WhichDeltaPT][WhichDeltaAlphaT][0]);

			}

		}

		for (int WhichMuonMomentum = 0; WhichMuonMomentum < TwoDNBinsMuonMomentum; WhichMuonMomentum++) {

			TString DeltaAlphaTTwoDInMuonMomentumLabel = "DeltaAlphaT_MuonMomentum_"+tools.ConvertToString(TwoDArrayNBinsMuonMomentum[WhichMuonMomentum])+"To"+tools.ConvertToString(TwoDArrayNBinsMuonMomentum[WhichMuonMomentum+1])+"Plot";			
			TrueDeltaAlphaT_InMuonMomentumTwoDPlot[inte][WhichMuonMomentum] = new TH1D(InteractionLabels[inte]+"True"+DeltaAlphaTTwoDInMuonMomentumLabel,LabelXAxisDeltaAlphaT,TwoDArrayNBinsDeltaAlphaTInMuonMomentumSlices[WhichMuonMomentum].size()-1,&TwoDArrayNBinsDeltaAlphaTInMuonMomentumSlices[WhichMuonMomentum][0]);

		}

		for (int WhichMuonCosTheta = 0; WhichMuonCosTheta < TwoDNBinsMuonCosTheta; WhichMuonCosTheta++) {

			TString DeltaAlphaTTwoDInMuonCosThetaLabel = "DeltaAlphaT_MuonCosTheta_"+tools.ConvertToString(TwoDArrayNBinsMuonCosTheta[WhichMuonCosTheta])+"To"+tools.ConvertToString(TwoDArrayNBinsMuonCosTheta[WhichMuonCosTheta+1])+"Plot";			
			TrueDeltaAlphaT_InMuonCosThetaTwoDPlot[inte][WhichMuonCosTheta] = new TH1D(InteractionLabels[inte]+"True"+DeltaAlphaTTwoDInMuonCosThetaLabel,LabelXAxisDeltaAlphaT,TwoDArrayNBinsDeltaAlphaTInMuonCosThetaSlices[WhichMuonCosTheta].size()-1,&TwoDArrayNBinsDeltaAlphaTInMuonCosThetaSlices[WhichMuonCosTheta][0]);

			TString DeltaPTTwoDInMuonCosThetaLabel = "DeltaPT_MuonCosTheta_"+tools.ConvertToString(TwoDArrayNBinsMuonCosTheta[WhichMuonCosTheta])+"To"+tools.ConvertToString(TwoDArrayNBinsMuonCosTheta[WhichMuonCosTheta+1])+"Plot";			
			TrueDeltaPT_InMuonCosThetaTwoDPlot[inte][WhichMuonCosTheta] = new TH1D(InteractionLabels[inte]+"True"+DeltaPTTwoDInMuonCosThetaLabel,LabelXAxisDeltaPT,TwoDArrayNBinsDeltaPTInMuonCosThetaSlices[WhichMuonCosTheta].size()-1,&TwoDArrayNBinsDeltaPTInMuonCosThetaSlices[WhichMuonCosTheta][0]);		

			TString MuonMomentumTwoDInMuonCosThetaLabel = "MuonMomentum_MuonCosTheta_"+tools.ConvertToString(TwoDArrayNBinsMuonCosTheta[WhichMuonCosTheta])+"To"+tools.ConvertToString(TwoDArrayNBinsMuonCosTheta[WhichMuonCosTheta+1])+"Plot";			
			TrueMuonMomentum_InMuonCosThetaTwoDPlot[inte][WhichMuonCosTheta] = new TH1D(InteractionLabels[inte]+"True"+MuonMomentumTwoDInMuonCosThetaLabel,LabelXAxisMuonMomentum,TwoDArrayNBinsMuonMomentumInMuonCosThetaSlices[WhichMuonCosTheta].size()-1,&TwoDArrayNBinsMuonMomentumInMuonCosThetaSlices[WhichMuonCosTheta][0]);

			TString ProtonCosThetaTwoDInMuonCosThetaLabel = "ProtonCosTheta_MuonCosTheta_"+tools.ConvertToString(TwoDArrayNBinsMuonCosTheta[WhichMuonCosTheta])+"To"+tools.ConvertToString(TwoDArrayNBinsMuonCosTheta[WhichMuonCosTheta+1])+"Plot";			
			TrueProtonCosTheta_InMuonCosThetaTwoDPlot[inte][WhichMuonCosTheta] = new TH1D(InteractionLabels[inte]+"True"+ProtonCosThetaTwoDInMuonCosThetaLabel,LabelXAxisProtonCosTheta,TwoDArrayNBinsProtonCosThetaInMuonCosThetaSlices[WhichMuonCosTheta].size()-1,&TwoDArrayNBinsProtonCosThetaInMuonCosThetaSlices[WhichMuonCosTheta][0]);

			for (int WhichMuonMomentum = 0; WhichMuonMomentum < TwoDNBinsMuonMomentum; WhichMuonMomentum++) {	

				TString ECalTwoDInMuonCosThetaMuonMomentumLabel = "ECal_MuonCosTheta_"+tools.ConvertToString(TwoDArrayNBinsMuonCosTheta[WhichMuonCosTheta])+"To"+tools.ConvertToString(TwoDArrayNBinsMuonCosTheta[WhichMuonCosTheta+1])+"_MuonMomentum_"+tools.ConvertToString(TwoDArrayNBinsMuonMomentum[WhichMuonMomentum])+"To"+tools.ConvertToString(TwoDArrayNBinsMuonMomentum[WhichMuonMomentum+1])+"Plot";
				TrueECal_InMuonCosThetaMuonMomentumTwoDPlot[inte][WhichMuonCosTheta][WhichMuonMomentum] = new TH1D(InteractionLabels[inte]+"True"+ECalTwoDInMuonCosThetaMuonMomentumLabel,LabelXAxisECal,TwoDArrayNBinsECalInMuonCosThetaMuonMomentumSlices[WhichMuonCosTheta][WhichMuonMomentum].size()-1,&TwoDArrayNBinsECalInMuonCosThetaMuonMomentumSlices[WhichMuonCosTheta][WhichMuonMomentum][0]);

			}

		}

		for (int WhichProtonMomentum = 0; WhichProtonMomentum < TwoDNBinsProtonMomentum; WhichProtonMomentum++) {

			TString DeltaAlphaTTwoDInProtonMomentumLabel = "DeltaAlphaT_ProtonMomentum_"+tools.ConvertToString(TwoDArrayNBinsProtonMomentum[WhichProtonMomentum])+"To"+tools.ConvertToString(TwoDArrayNBinsProtonMomentum[WhichProtonMomentum+1])+"Plot";			
			TrueDeltaAlphaT_InProtonMomentumTwoDPlot[inte][WhichProtonMomentum] = new TH1D(InteractionLabels[inte]+"True"+DeltaAlphaTTwoDInProtonMomentumLabel,LabelXAxisDeltaAlphaT,TwoDArrayNBinsDeltaAlphaTInProtonMomentumSlices[WhichProtonMomentum].size()-1,&TwoDArrayNBinsDeltaAlphaTInProtonMomentumSlices[WhichProtonMomentum][0]);

		}				

		for (int WhichProtonCosTheta = 0; WhichProtonCosTheta < TwoDNBinsProtonCosTheta; WhichProtonCosTheta++) {

			TString ProtonMomentumTwoDInProtonCosThetaLabel = "ProtonMomentum_ProtonCosTheta_"+tools.ConvertToString(TwoDArrayNBinsProtonCosTheta[WhichProtonCosTheta])+"To"+tools.ConvertToString(TwoDArrayNBinsProtonCosTheta[WhichProtonCosTheta+1])+"Plot";			
			TrueProtonMomentum_InProtonCosThetaTwoDPlot[inte][WhichProtonCosTheta] = new TH1D(InteractionLabels[inte]+"True"+ProtonMomentumTwoDInProtonCosThetaLabel,LabelXAxisProtonMomentum,TwoDArrayNBinsProtonMomentumInProtonCosThetaSlices[WhichProtonCosTheta].size()-1,&TwoDArrayNBinsProtonMomentumInProtonCosThetaSlices[WhichProtonCosTheta][0]);

			TString DeltaAlphaTTwoDInProtonCosThetaLabel = "DeltaAlphaT_ProtonCosTheta_"+tools.ConvertToString(TwoDArrayNBinsProtonCosTheta[WhichProtonCosTheta])+"To"+tools.ConvertToString(TwoDArrayNBinsProtonCosTheta[WhichProtonCosTheta+1])+"Plot";			
			TrueDeltaAlphaT_InProtonCosThetaTwoDPlot[inte][WhichProtonCosTheta] = new TH1D(InteractionLabels[inte]+"True"+DeltaAlphaTTwoDInProtonCosThetaLabel,LabelXAxisDeltaAlphaT,TwoDArrayNBinsDeltaAlphaTInProtonCosThetaSlices[WhichProtonCosTheta].size()-1,&TwoDArrayNBinsDeltaAlphaTInProtonCosThetaSlices[WhichProtonCosTheta][0]);

			TString DeltaPTTwoDInProtonCosThetaLabel = "DeltaPT_ProtonCosTheta_"+tools.ConvertToString(TwoDArrayNBinsProtonCosTheta[WhichProtonCosTheta])+"To"+tools.ConvertToString(TwoDArrayNBinsProtonCosTheta[WhichProtonCosTheta+1])+"Plot";			
			TrueDeltaPT_InProtonCosThetaTwoDPlot[inte][WhichProtonCosTheta] = new TH1D(InteractionLabels[inte]+"True"+DeltaPTTwoDInProtonCosThetaLabel,LabelXAxisDeltaPT,TwoDArrayNBinsDeltaPTInProtonCosThetaSlices[WhichProtonCosTheta].size()-1,&TwoDArrayNBinsDeltaPTInProtonCosThetaSlices[WhichProtonCosTheta][0]);

			for (int WhichProtonMomentum = 0; WhichProtonMomentum < TwoDNBinsProtonMomentum; WhichProtonMomentum++) {	

				TString ECalTwoDInProtonCosThetaProtonMomentumLabel = "ECal_ProtonCosTheta_"+tools.ConvertToString(TwoDArrayNBinsProtonCosTheta[WhichProtonCosTheta])+"To"+tools.ConvertToString(TwoDArrayNBinsProtonCosTheta[WhichProtonCosTheta+1])+"_ProtonMomentum_"+tools.ConvertToString(TwoDArrayNBinsProtonMomentum[WhichProtonMomentum])+"To"+tools.ConvertToString(TwoDArrayNBinsProtonMomentum[WhichProtonMomentum+1])+"Plot";
				TrueECal_InProtonCosThetaProtonMomentumTwoDPlot[inte][WhichProtonCosTheta][WhichProtonMomentum] = new TH1D(InteractionLabels[inte]+"True"+ECalTwoDInProtonCosThetaProtonMomentumLabel,LabelXAxisECal,TwoDArrayNBinsECalInProtonCosThetaProtonMomentumSlices[WhichProtonCosTheta][WhichProtonMomentum].size()-1,&TwoDArrayNBinsECalInProtonCosThetaProtonMomentumSlices[WhichProtonCosTheta][WhichProtonMomentum][0]);

			}

		}

		for (int WhichDeltaPtx = 0; WhichDeltaPtx < TwoDNBinsDeltaPtx; WhichDeltaPtx++) {

			TString DeltaPtyTwoDInDeltaPtxLabel = "DeltaPty_DeltaPtx_"+tools.ConvertToString(TwoDArrayNBinsDeltaPtx[WhichDeltaPtx])+"To"+tools.ConvertToString(TwoDArrayNBinsDeltaPtx[WhichDeltaPtx+1])+"Plot";			
			TrueDeltaPty_InDeltaPtxTwoDPlot[inte][WhichDeltaPtx] = new TH1D(InteractionLabels[inte]+"True"+DeltaPtyTwoDInDeltaPtxLabel,LabelXAxisDeltaPty,NBinsDeltaPty,ArrayNBinsDeltaPty);	

			TString ECalTwoDInDeltaPtxLabel = "ECal_DeltaPtx_"+tools.ConvertToString(TwoDArrayNBinsDeltaPtx[WhichDeltaPtx])+"To"+tools.ConvertToString(TwoDArrayNBinsDeltaPtx[WhichDeltaPtx+1])+"Plot";			
			TrueECal_InDeltaPtxTwoDPlot[inte][WhichDeltaPtx] = new TH1D(InteractionLabels[inte]+"True"+ECalTwoDInDeltaPtxLabel,LabelXAxisECal,TwoDArrayNBinsECalInDeltaPtxSlices[WhichDeltaPtx].size()-1,&TwoDArrayNBinsECalInDeltaPtxSlices[WhichDeltaPtx][0]);

			for (int WhichDeltaPty = 0; WhichDeltaPty < TwoDNBinsDeltaPty; WhichDeltaPty++) {	

				TString ECalTwoDInDeltaPtxDeltaPtyLabel = "ECal_DeltaPtx_"+tools.ConvertToString(TwoDArrayNBinsDeltaPtx[WhichDeltaPtx])+"To"+tools.ConvertToString(TwoDArrayNBinsDeltaPtx[WhichDeltaPtx+1])+"_DeltaPty_"+tools.ConvertToString(TwoDArrayNBinsDeltaPty[WhichDeltaPty])+"To"+tools.ConvertToString(TwoDArrayNBinsDeltaPty[WhichDeltaPty+1])+"Plot";
				TrueECal_InDeltaPtxDeltaPtyTwoDPlot[inte][WhichDeltaPtx][WhichDeltaPty] = new TH1D(InteractionLabels[inte]+"True"+ECalTwoDInDeltaPtxDeltaPtyLabel,LabelXAxisECal,TwoDArrayNBinsECalInDeltaPtxDeltaPtySlices[WhichDeltaPtx][WhichDeltaPty].size()-1,&TwoDArrayNBinsECalInDeltaPtxDeltaPtySlices[WhichDeltaPtx][WhichDeltaPty][0]);

			}

		}	

		for (int WhichDeltaPty = 0; WhichDeltaPty < TwoDNBinsDeltaPty; WhichDeltaPty++) {

			TString DeltaPtxTwoDInDeltaPtyLabel = "DeltaPtx_DeltaPty_"+tools.ConvertToString(TwoDArrayNBinsDeltaPty[WhichDeltaPty])+"To"+tools.ConvertToString(TwoDArrayNBinsDeltaPty[WhichDeltaPty+1])+"Plot";			
			TrueDeltaPtx_InDeltaPtyTwoDPlot[inte][WhichDeltaPty] = new TH1D(InteractionLabels[inte]+"True"+DeltaPtxTwoDInDeltaPtyLabel,LabelXAxisDeltaPtx,TwoDArrayNBinsDeltaPtxInDeltaPtySlices[WhichDeltaPty].size()-1,&TwoDArrayNBinsDeltaPtxInDeltaPtySlices[WhichDeltaPty][0]);	

			TString ECalTwoDInDeltaPtyLabel = "ECal_DeltaPty_"+tools.ConvertToString(TwoDArrayNBinsDeltaPty[WhichDeltaPty])+"To"+tools.ConvertToString(TwoDArrayNBinsDeltaPty[WhichDeltaPty+1])+"Plot";			
			TrueECal_InDeltaPtyTwoDPlot[inte][WhichDeltaPty] = new TH1D(InteractionLabels[inte]+"True"+ECalTwoDInDeltaPtyLabel,LabelXAxisECal,TwoDArrayNBinsECalInDeltaPtySlices[WhichDeltaPty].size()-1,&TwoDArrayNBinsECalInDeltaPtySlices[WhichDeltaPty][0]);

		}		

		for (int WhichDeltaAlpha3Dq = 0; WhichDeltaAlpha3Dq < TwoDNBinsDeltaAlpha3Dq; WhichDeltaAlpha3Dq++) {

			TString DeltaPnTwoDInDeltaAlpha3DqLabel = "DeltaPn_DeltaAlpha3Dq_"+tools.ConvertToString(TwoDArrayNBinsDeltaAlpha3Dq[WhichDeltaAlpha3Dq])+"To"+tools.ConvertToString(TwoDArrayNBinsDeltaAlpha3Dq[WhichDeltaAlpha3Dq+1])+"Plot";			
			TrueDeltaPn_InDeltaAlpha3DqTwoDPlot[inte][WhichDeltaAlpha3Dq] = new TH1D(InteractionLabels[inte]+"True"+DeltaPnTwoDInDeltaAlpha3DqLabel,LabelXAxisDeltaPn,TwoDArrayNBinsDeltaPnInDeltaAlpha3DqSlices[WhichDeltaAlpha3Dq].size()-1,&TwoDArrayNBinsDeltaPnInDeltaAlpha3DqSlices[WhichDeltaAlpha3Dq][0]);

		}

		for (int WhichDeltaAlpha3DMu = 0; WhichDeltaAlpha3DMu < TwoDNBinsDeltaAlpha3DMu; WhichDeltaAlpha3DMu++) {

			TString DeltaPnTwoDInDeltaAlpha3DMuLabel = "DeltaPn_DeltaAlpha3DMu_"+tools.ConvertToString(TwoDArrayNBinsDeltaAlpha3DMu[WhichDeltaAlpha3DMu])+"To"+tools.ConvertToString(TwoDArrayNBinsDeltaAlpha3DMu[WhichDeltaAlpha3DMu+1])+"Plot";			
			TrueDeltaPn_InDeltaAlpha3DMuTwoDPlot[inte][WhichDeltaAlpha3DMu] = new TH1D(InteractionLabels[inte]+"True"+DeltaPnTwoDInDeltaAlpha3DMuLabel,LabelXAxisDeltaPn,TwoDArrayNBinsDeltaPnInDeltaAlpha3DMuSlices[WhichDeltaAlpha3DMu].size()-1,&TwoDArrayNBinsDeltaPnInDeltaAlpha3DMuSlices[WhichDeltaAlpha3DMu][0]);

		}		

		for (int WhichDeltaAlphaT = 0; WhichDeltaAlphaT < TwoDNBinsDeltaAlphaT; WhichDeltaAlphaT++) {

			TString DeltaPTTwoDInDeltaAlphaTLabel = "DeltaPT_DeltaAlphaT_"+tools.ConvertToString(TwoDArrayNBinsDeltaAlphaT[WhichDeltaAlphaT])+"To"+tools.ConvertToString(TwoDArrayNBinsDeltaAlphaT[WhichDeltaAlphaT+1])+"Plot";			
			TrueDeltaPT_InDeltaAlphaTTwoDPlot[inte][WhichDeltaAlphaT] = new TH1D(InteractionLabels[inte]+"True"+DeltaPTTwoDInDeltaAlphaTLabel,LabelXAxisDeltaPT,TwoDArrayNBinsDeltaPTInDeltaAlphaTSlices[WhichDeltaAlphaT].size()-1,&TwoDArrayNBinsDeltaPTInDeltaAlphaTSlices[WhichDeltaAlphaT][0]);

			TString ProtonMomentumTwoDInDeltaAlphaTLabel = "ProtonMomentum_DeltaAlphaT_"+tools.ConvertToString(TwoDArrayNBinsDeltaAlphaT[WhichDeltaAlphaT])+"To"+tools.ConvertToString(TwoDArrayNBinsDeltaAlphaT[WhichDeltaAlphaT+1])+"Plot";			
			TrueProtonMomentum_InDeltaAlphaTTwoDPlot[inte][WhichDeltaAlphaT] = new TH1D(InteractionLabels[inte]+"True"+ProtonMomentumTwoDInDeltaAlphaTLabel,LabelXAxisProtonMomentum,TwoDArrayNBinsProtonMomentumInDeltaAlphaTSlices[WhichDeltaAlphaT].size()-1,&TwoDArrayNBinsProtonMomentumInDeltaAlphaTSlices[WhichDeltaAlphaT][0]);			

			TString DeltaPnTwoDInDeltaAlphaTLabel = "DeltaPn_DeltaAlphaT_"+tools.ConvertToString(TwoDArrayNBinsDeltaAlphaT[WhichDeltaAlphaT])+"To"+tools.ConvertToString(TwoDArrayNBinsDeltaAlphaT[WhichDeltaAlphaT+1])+"Plot";			
			TrueDeltaPn_InDeltaAlphaTTwoDPlot[inte][WhichDeltaAlphaT] = new TH1D(InteractionLabels[inte]+"True"+DeltaPnTwoDInDeltaAlphaTLabel,LabelXAxisDeltaPn,TwoDArrayNBinsDeltaPnInDeltaAlphaTSlices[WhichDeltaAlphaT].size()-1,&TwoDArrayNBinsDeltaPnInDeltaAlphaTSlices[WhichDeltaAlphaT][0]);			

			TString ECalTwoDInDeltaAlphaTLabel = "ECal_DeltaAlphaT_"+tools.ConvertToString(TwoDArrayNBinsDeltaAlphaT[WhichDeltaAlphaT])+"To"+tools.ConvertToString(TwoDArrayNBinsDeltaAlphaT[WhichDeltaAlphaT+1])+"Plot";			
			TrueECal_InDeltaAlphaTTwoDPlot[inte][WhichDeltaAlphaT] = new TH1D(InteractionLabels[inte]+"True"+ECalTwoDInDeltaAlphaTLabel,LabelXAxisECal,TwoDArrayNBinsECalInDeltaAlphaTSlices[WhichDeltaAlphaT].size()-1,&TwoDArrayNBinsECalInDeltaAlphaTSlices[WhichDeltaAlphaT][0]);

		}

		//--------------------------------------------------//	

		// 2D analysis in 1D grid	

		SerialTrueDeltaPT_InMuonCosThetaPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueSerialDeltaPT_MuonCosThetaPlot",LabelXAxisDeltaPT,tools.Return2DNBins(TwoDArrayNBinsDeltaPTInMuonCosThetaSlices),&tools.Return2DBinIndices(TwoDArrayNBinsDeltaPTInMuonCosThetaSlices)[0]);
		SerialTrueDeltaPT_InProtonCosThetaPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueSerialDeltaPT_ProtonCosThetaPlot",LabelXAxisDeltaPT,tools.Return2DNBins(TwoDArrayNBinsDeltaPTInProtonCosThetaSlices),&tools.Return2DBinIndices(TwoDArrayNBinsDeltaPTInProtonCosThetaSlices)[0]);	
		SerialTrueDeltaPT_InDeltaAlphaTPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueSerialDeltaPT_DeltaAlphaTPlot",LabelXAxisDeltaPT,tools.Return2DNBins(TwoDArrayNBinsDeltaPTInDeltaAlphaTSlices),&tools.Return2DBinIndices(TwoDArrayNBinsDeltaPTInDeltaAlphaTSlices)[0]);
		SerialTrueDeltaPn_InDeltaAlpha3DqPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueSerialDeltaPn_DeltaAlpha3DqPlot",LabelXAxisDeltaPn,tools.Return2DNBins(TwoDArrayNBinsDeltaPnInDeltaAlpha3DqSlices),&tools.Return2DBinIndices(TwoDArrayNBinsDeltaPnInDeltaAlpha3DqSlices)[0]);
		SerialTrueDeltaPn_InDeltaAlpha3DMuPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueSerialDeltaPn_DeltaAlpha3DMuPlot",LabelXAxisDeltaPn,tools.Return2DNBins(TwoDArrayNBinsDeltaPnInDeltaAlpha3DMuSlices),&tools.Return2DBinIndices(TwoDArrayNBinsDeltaPnInDeltaAlpha3DMuSlices)[0]);				
		SerialTrueProtonMomentum_InDeltaAlphaTPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueSerialProtonMomentum_DeltaAlphaTPlot",LabelXAxisProtonMomentum,tools.Return2DNBins(TwoDArrayNBinsProtonMomentumInDeltaAlphaTSlices),&tools.Return2DBinIndices(TwoDArrayNBinsProtonMomentumInDeltaAlphaTSlices)[0]);		
		SerialTrueMuonMomentum_InMuonCosThetaPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueSerialMuonMomentum_MuonCosThetaPlot",LabelXAxisMuonMomentum,tools.Return2DNBins(TwoDArrayNBinsMuonMomentumInMuonCosThetaSlices),&tools.Return2DBinIndices(TwoDArrayNBinsMuonMomentumInMuonCosThetaSlices)[0]);
		SerialTrueProtonMomentum_InProtonCosThetaPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueSerialProtonMomentum_ProtonCosThetaPlot",LabelXAxisProtonMomentum,tools.Return2DNBins(TwoDArrayNBinsProtonMomentumInProtonCosThetaSlices),&tools.Return2DBinIndices(TwoDArrayNBinsProtonMomentumInProtonCosThetaSlices)[0]);	
		SerialTrueDeltaAlphaT_InMuonCosThetaPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueSerialDeltaAlphaT_MuonCosThetaPlot",LabelXAxisDeltaAlphaT,tools.Return2DNBins(TwoDArrayNBinsDeltaAlphaTInMuonCosThetaSlices),&tools.Return2DBinIndices(TwoDArrayNBinsDeltaAlphaTInMuonCosThetaSlices)[0]);
		SerialTrueDeltaAlphaT_InMuonMomentumPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueSerialDeltaAlphaT_MuonMomentumPlot",LabelXAxisDeltaAlphaT,tools.Return2DNBins(TwoDArrayNBinsDeltaAlphaTInMuonMomentumSlices),&tools.Return2DBinIndices(TwoDArrayNBinsDeltaAlphaTInMuonMomentumSlices)[0]);		
		SerialTrueDeltaAlphaT_InProtonCosThetaPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueSerialDeltaAlphaT_ProtonCosThetaPlot",LabelXAxisDeltaAlphaT,tools.Return2DNBins(TwoDArrayNBinsDeltaAlphaTInProtonCosThetaSlices),&tools.Return2DBinIndices(TwoDArrayNBinsDeltaAlphaTInProtonCosThetaSlices)[0]);
		SerialTrueDeltaAlphaT_InProtonMomentumPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueSerialDeltaAlphaT_ProtonMomentumPlot",LabelXAxisDeltaAlphaT,tools.Return2DNBins(TwoDArrayNBinsDeltaAlphaTInProtonMomentumSlices),&tools.Return2DBinIndices(TwoDArrayNBinsDeltaAlphaTInProtonMomentumSlices)[0]);		
		SerialTrueDeltaAlphaT_InDeltaPTPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueSerialDeltaAlphaT_DeltaPTPlot",LabelXAxisDeltaAlphaT,tools.Return2DNBins(TwoDArrayNBinsDeltaAlphaTInDeltaPTSlices),&tools.Return2DBinIndices(TwoDArrayNBinsDeltaAlphaTInDeltaPTSlices)[0]);
		SerialTrueDeltaAlpha3Dq_InDeltaPnPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueSerialDeltaAlpha3Dq_DeltaPnPlot",LabelXAxisDeltaAlpha3Dq,tools.Return2DNBins(TwoDArrayNBinsDeltaAlpha3DqInDeltaPnSlices),&tools.Return2DBinIndices(TwoDArrayNBinsDeltaAlpha3DqInDeltaPnSlices)[0]);
		SerialTrueDeltaAlpha3DMu_InDeltaPnPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueSerialDeltaAlpha3DMu_DeltaPnPlot",LabelXAxisDeltaAlpha3DMu,tools.Return2DNBins(TwoDArrayNBinsDeltaAlpha3DMuInDeltaPnSlices),&tools.Return2DBinIndices(TwoDArrayNBinsDeltaAlpha3DMuInDeltaPnSlices)[0]);						
		SerialTrueDeltaPhiT_InDeltaPTPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueSerialDeltaPhiT_DeltaPTPlot",LabelXAxisDeltaPhiT,tools.Return2DNBins(TwoDArrayNBinsDeltaPhiTInDeltaPTSlices),&tools.Return2DBinIndices(TwoDArrayNBinsDeltaPhiTInDeltaPTSlices)[0]);
		SerialTrueDeltaPn_InDeltaPTPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueSerialDeltaPn_DeltaPTPlot",LabelXAxisDeltaPn,tools.Return2DNBins(TwoDArrayNBinsDeltaPnInDeltaPTSlices),&tools.Return2DBinIndices(TwoDArrayNBinsDeltaPnInDeltaPTSlices)[0]);
		SerialTrueDeltaPn_InDeltaAlphaTPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueSerialDeltaPn_DeltaAlphaTPlot",LabelXAxisDeltaPn,tools.Return2DNBins(TwoDArrayNBinsDeltaPnInDeltaAlphaTSlices),&tools.Return2DBinIndices(TwoDArrayNBinsDeltaPnInDeltaAlphaTSlices)[0]);
		SerialTrueProtonCosTheta_InMuonCosThetaPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueSerialProtonCosTheta_MuonCosThetaPlot",LabelXAxisProtonCosTheta,tools.Return2DNBins(TwoDArrayNBinsProtonCosThetaInMuonCosThetaSlices),&tools.Return2DBinIndices(TwoDArrayNBinsProtonCosThetaInMuonCosThetaSlices)[0]);
		SerialTrueDeltaPty_InDeltaPtxPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueSerialDeltaPty_DeltaPtxPlot",LabelXAxisDeltaPty,tools.Return2DNBins(TwoDArrayNBinsDeltaPtyInDeltaPtxSlices),&tools.Return2DBinIndices(TwoDArrayNBinsDeltaPtyInDeltaPtxSlices)[0]);
		SerialTrueDeltaPtx_InDeltaPtyPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueSerialDeltaPtx_DeltaPtyPlot",LabelXAxisDeltaPtx,tools.Return2DNBins(TwoDArrayNBinsDeltaPtxInDeltaPtySlices),&tools.Return2DBinIndices(TwoDArrayNBinsDeltaPtxInDeltaPtySlices)[0]);
		SerialTrueECal_InDeltaPTPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueSerialECal_DeltaPTPlot",LabelXAxisECal,tools.Return2DNBins(TwoDArrayNBinsECalInDeltaPTSlices),&tools.Return2DBinIndices(TwoDArrayNBinsECalInDeltaPTSlices)[0]);
		SerialTrueECal_InDeltaPtxPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueSerialECal_DeltaPtxPlot",LabelXAxisECal,tools.Return2DNBins(TwoDArrayNBinsECalInDeltaPtxSlices),&tools.Return2DBinIndices(TwoDArrayNBinsECalInDeltaPtxSlices)[0]);
		SerialTrueECal_InDeltaPtyPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueSerialECal_DeltaPtyPlot",LabelXAxisECal,tools.Return2DNBins(TwoDArrayNBinsECalInDeltaPtySlices),&tools.Return2DBinIndices(TwoDArrayNBinsECalInDeltaPtySlices)[0]);
		SerialTrueECal_InDeltaAlphaTPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueSerialECal_DeltaAlphaTPlot",LabelXAxisECal,tools.Return2DNBins(TwoDArrayNBinsECalInDeltaAlphaTSlices),&tools.Return2DBinIndices(TwoDArrayNBinsECalInDeltaAlphaTSlices)[0]);

		//--------------------------------------------------//	

		// 3D analysis in 1D grid		
		
		SerialTrueECal_InDeltaPTDeltaAlphaTPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueSerialECal_DeltaPTDeltaAlphaTPlot",LabelXAxisECal,tools.Return3DNBins(TwoDArrayNBinsECalInDeltaPTDeltaAlphaTSlices),&tools.Return3DBinIndices(TwoDArrayNBinsECalInDeltaPTDeltaAlphaTSlices)[0]);
		SerialTrueECal_InDeltaPtxDeltaPtyPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueSerialECal_DeltaPtxDeltaPtyPlot",LabelXAxisECal,tools.Return3DNBins(TwoDArrayNBinsECalInDeltaPtxDeltaPtySlices),&tools.Return3DBinIndices(TwoDArrayNBinsECalInDeltaPtxDeltaPtySlices)[0]);
		SerialTrueECal_InMuonCosThetaMuonMomentumPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueSerialECal_MuonCosThetaMuonMomentumPlot",LabelXAxisECal,tools.Return3DNBins(TwoDArrayNBinsECalInMuonCosThetaMuonMomentumSlices),&tools.Return3DBinIndices(TwoDArrayNBinsECalInMuonCosThetaMuonMomentumSlices)[0]);
		SerialTrueECal_InProtonCosThetaProtonMomentumPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueSerialECal_ProtonCosThetaProtonMomentumPlot",LabelXAxisECal,tools.Return3DNBins(TwoDArrayNBinsECalInProtonCosThetaProtonMomentumSlices),&tools.Return3DBinIndices(TwoDArrayNBinsECalInProtonCosThetaProtonMomentumSlices)[0]);

		//--------------------------------------------------//

	} // End of the loop over the interaction processes							

	//----------------------------------------//

	// Counters STVlike analysis

	int CounterSTVlikeEventsPassedSelection = 0;
	int CounterSTVlikeQEEventsPassedSelection = 0;
	int CounterSTVlikeMECEventsPassedSelection = 0;
	int CounterSTVlikeRESEventsPassedSelection = 0;
	int CounterSTVlikeDISEventsPassedSelection = 0;
	int CounterSTVlikeCOHEventsPassedSelection = 0;	

	//--------------------------------------------------//	
	
	for (Long64_t jentry=0; jentry<nentries;jentry++) {
	
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break; nb = fChain->GetEntry(jentry); nbytes += nb;
		if (jentry%1000 == 0) std::cout << jentry/1000 << " k " << std::setprecision(3) << double(jentry)/nentries*100. << " %"<< std::endl;

		// ---------------------------------------------------------------------------------------------------------------------------------
		
//		double weight = 1.;	
		double A = 40.;
		double weight = fScaleFactor*Units*A*Weight;	

		// ---------------------------------------------------------------------------------------------------------------------------------

		if (PDGLep != 13) { continue; } // make sure that we have only CC interactions
		if (cc != 1) { continue; } // make sure that we have only CC interactions		

		// ---------------------------------------------------------------------------------------------------------------------------------

		int ProtonTagging = 0, ChargedPionTagging = 0, NeutralPionTagging = 0, ElectronTagging = 0, GammaTagging = 0, MuonTagging = 0, TrueHeavierMesonCounter = 0;
		vector <int> ProtonID; ProtonID.clear();
		vector <int> MuonID; MuonID.clear();		

		for (int i = 0; i < nfsp; i++) {
		
			double pf = TMath::Sqrt( px[i]*px[i] + py[i]*py[i] + pz[i]*pz[i]);

			if (pdg[i] == MuonPdg && pf > ArrayNBinsMuonMomentum[0]) {

				MuonTagging ++;
				MuonID.push_back(i);

			}

			if (pdg[i] == ProtonPdg && pf > ArrayNBinsProtonMomentum[0]) {

				ProtonTagging ++;
				ProtonID.push_back(i);

			}

			if (fabs(pdg[i]) == AbsChargedPionPdg && pf > ChargedPionMomentumThres)  {

				ChargedPionTagging ++;

			}

			if (pdg[i] == NeutralPionPdg)  {

				NeutralPionTagging ++;

			}

			if ( pdg[i] != NeutralPionPdg && fabs(pdg[i]) != AbsChargedPionPdg && tools.is_meson_or_antimeson(pdg[i]) ) { TrueHeavierMesonCounter++; }

		} // End of the loop over the final state particles

		if ( ProtonTagging != 1 || ChargedPionTagging != 0 || NeutralPionTagging != 0 || MuonTagging !=1) { continue; }
		if ( TrueHeavierMesonCounter != 0 ) { continue; }

		// ----------------------------------------------------------------------------------------------------------------------------------

		// Muon

		TVector3 Muon3Vector(px[MuonID.at(0)],py[MuonID.at(0)],pz[MuonID.at(0)]); // GeV
		TLorentzVector Muon4Vector(px[MuonID.at(0)],py[MuonID.at(0)],pz[MuonID.at(0)],ELep); // GeV
		double MuonMomentum = Muon3Vector.Mag(); // GeV / c
		double MuonCosTheta = CosLep;
		double MuonPhi = Muon4Vector.Phi() * 180. / TMath::Pi(); // deg

		// -------------------------------------------------------------------------------------------------------------------------------

		// Proton

		int ProtonIndex = ProtonID.at(0);
		TVector3 Proton3Vector(px[ProtonIndex],py[ProtonIndex],pz[ProtonIndex]); // GeV
		TLorentzVector Proton4Vector(px[ProtonIndex],py[ProtonIndex],pz[ProtonIndex],E[ProtonIndex]); // GeV
		double ProtonMomentum = Proton3Vector.Mag(); // GeV / c

		double ProtonCosTheta = Proton3Vector.CosTheta();
		double ProtonPhi = Proton4Vector.Phi() * 180. / TMath::Pi(); // deg
		double ProtonEnergy = Proton4Vector.E(); // GeV
		double ProtonKE = ProtonEnergy - ProtonMass_GeV; // GeV

		// ---------------------------------------------------------------------------------------------------------------------------------

		// Relative Proton - Muon Angles

		double DeltaThetaProtonMuon = Proton3Vector.Angle(Muon3Vector) * 180. / TMath::Pi();
		if (DeltaThetaProtonMuon < 0.) { DeltaThetaProtonMuon += 180.; }
		if (DeltaThetaProtonMuon > 180.) { DeltaThetaProtonMuon -= 180.; }

		double DeltaPhiProtonMuon = Muon3Vector.DeltaPhi(Proton3Vector)* 180. / TMath::Pi();
		if (DeltaPhiProtonMuon < 0.) { DeltaPhiProtonMuon += 360.; }
		if (DeltaPhiProtonMuon > 360.) { DeltaPhiProtonMuon -= 360.; }

		// ---------------------------------------------------------------------------------------------------------------------------------

		STV_Tools stv_tool(Muon3Vector,Proton3Vector,ELep,ProtonEnergy);

		double PTmissMomentum = stv_tool.ReturnPt();
		double TrueDeltaAlphaT = stv_tool.ReturnDeltaAlphaT();
		double TrueDeltaAlpha3Dq = stv_tool.ReturnDeltaAlpha3Dq();
		double TrueDeltaAlpha3DMu = stv_tool.ReturnDeltaAlpha3DMu();				
		double TrueDeltaPhiT = stv_tool.ReturnDeltaPhiT();
		double TrueDeltaPhi3D = stv_tool.ReturnDeltaPhi3D();		
		double ECal = stv_tool.ReturnECal();
		double EQE = stv_tool.ReturnEQE();
		double TrueQ2 = stv_tool.ReturnQ2();	

		double TruekMiss = stv_tool.ReturnkMiss();
		double TruePMissMinus = stv_tool.ReturnPMissMinus();
		double TrueMissMomentum = stv_tool.ReturnPMiss();

		double TruePL = stv_tool.ReturnPL();
		double TruePn = stv_tool.ReturnPn();
		double TruePnPerp = stv_tool.ReturnPnPerp();
		double TruePnPerpx = stv_tool.ReturnPnPerpx();
		double TruePnPerpy = stv_tool.ReturnPnPerpy();				
		double TruePnPar = stv_tool.ReturnPnPar();				
		double TruePtx = stv_tool.ReturnPtx();
		double TruePty = stv_tool.ReturnPty();
		double TrueA = stv_tool.ReturnA();

		// -----------------------------------------------------------------------------------------------------------------
		// -----------------------------------------------------------------------------------------------------------------	

		// Overflow bins
		// Affects

		// DeltaPT
		// DeltaPtx
		// DeltaPty
		// DeltaPL
		// DeltaPn
		// DeltaPnPerp
		// DeltaPnPerpx
		// DeltaPnPerpy				
		// DeltaPnPar				
		// Q2
		// ECal
		// EQE
		// alpha
		// kMiss
		// PMiss
		// PMissMinus


		if (PTmissMomentum > ArrayNBinsDeltaPT[NBinsDeltaPT]) { PTmissMomentum = 0.5 * (ArrayNBinsDeltaPT[NBinsDeltaPT] + ArrayNBinsDeltaPT[NBinsDeltaPT-1]); }
		if (TruePtx > ArrayNBinsDeltaPtx[NBinsDeltaPtx]) { TruePtx = 0.5 * (ArrayNBinsDeltaPtx[NBinsDeltaPtx] + ArrayNBinsDeltaPtx[NBinsDeltaPtx-1]); }
		if (TruePty > ArrayNBinsDeltaPty[NBinsDeltaPty]) { TruePty = 0.5 * (ArrayNBinsDeltaPty[NBinsDeltaPty] + ArrayNBinsDeltaPty[NBinsDeltaPty-1]); }
		if (TruePL > ArrayNBinsDeltaPL[NBinsDeltaPL]) { TruePL = 0.5 * (ArrayNBinsDeltaPL[NBinsDeltaPL] + ArrayNBinsDeltaPL[NBinsDeltaPL-1]); }						
		if (TruePn > ArrayNBinsDeltaPn[NBinsDeltaPn]) { TruePn = 0.5 * (ArrayNBinsDeltaPn[NBinsDeltaPn] + ArrayNBinsDeltaPn[NBinsDeltaPn-1]); }
		if (TruePnPerp > ArrayNBinsDeltaPnPerp[NBinsDeltaPnPerp]) { TruePnPerp = 0.5 * (ArrayNBinsDeltaPnPerp[NBinsDeltaPnPerp] + ArrayNBinsDeltaPnPerp[NBinsDeltaPnPerp-1]); }
		if (TruePnPerpx > ArrayNBinsDeltaPnPerpx[NBinsDeltaPnPerpx]) { TruePnPerpx = 0.5 * (ArrayNBinsDeltaPnPerpx[NBinsDeltaPnPerpx] + ArrayNBinsDeltaPnPerpx[NBinsDeltaPnPerpx-1]); }
		if (TruePnPerpy > ArrayNBinsDeltaPnPerpy[NBinsDeltaPnPerpy]) { TruePnPerpy = 0.5 * (ArrayNBinsDeltaPnPerpy[NBinsDeltaPnPerpy] + ArrayNBinsDeltaPnPerpy[NBinsDeltaPnPerpy-1]); }				
		if (TruePnPar > ArrayNBinsDeltaPnPar[NBinsDeltaPnPar]) { TruePnPar = 0.5 * (ArrayNBinsDeltaPnPar[NBinsDeltaPnPar] + ArrayNBinsDeltaPnPar[NBinsDeltaPnPar-1]); }				

		if (ECal > ArrayNBinsECal[NBinsECal]) { ECal = 0.5 * (ArrayNBinsECal[NBinsECal] + ArrayNBinsECal[NBinsECal-1]); }
		if (EQE > ArrayNBinsEQE[NBinsEQE]) { EQE = 0.5 * (ArrayNBinsEQE[NBinsEQE] + ArrayNBinsEQE[NBinsEQE-1]); }
		if (TrueQ2 > ArrayNBinsQ2[NBinsQ2]) { TrueQ2 = 0.5 * (ArrayNBinsQ2[NBinsQ2] + ArrayNBinsQ2[NBinsQ2-1]); }

		if (TrueA > ArrayNBinsA[NBinsA]) { TrueA = 0.5 * (ArrayNBinsA[NBinsA] + ArrayNBinsA[NBinsA-1]); }	
		if (TruekMiss > ArrayNBinskMiss[NBinskMiss]) { TruekMiss = 0.5 * (ArrayNBinskMiss[NBinskMiss] + ArrayNBinskMiss[NBinskMiss-1]); }														
		if (TrueMissMomentum > ArrayNBinsPMiss[NBinsPMiss]) { TrueMissMomentum = 0.5 * (ArrayNBinsPMiss[NBinsPMiss] + ArrayNBinsPMiss[NBinsPMiss-1]); }
		if (TruePMissMinus > ArrayNBinsPMissMinus[NBinsPMissMinus]) { TruePMissMinus = 0.5 * (ArrayNBinsPMissMinus[NBinsPMissMinus] + ArrayNBinsPMissMinus[NBinsPMissMinus-1]); }

		// ---------------------------------------------------------------------------------------------------------------------------

		// Underflow bins
		// Affects

		// ECal
		// EQE
		// DeltaPtx
		// DeltaPty
		// DeltaPL
		// DeltaPnPerp
		// DeltaPnPerpx
		// DeltaPnPerpy				
		// DeltaPnPar			
		// alpha
		// PMissMinus
			
		if (ECal < ArrayNBinsECal[0]) { ECal = 0.5 * (ArrayNBinsECal[0] + ArrayNBinsECal[1]); }			
		if (EQE < ArrayNBinsEQE[0]) { EQE = 0.5 * (ArrayNBinsEQE[0] + ArrayNBinsEQE[1]); }			
		if (TruePtx < ArrayNBinsDeltaPtx[0]) { TruePtx = 0.5 * (ArrayNBinsDeltaPtx[0] + ArrayNBinsDeltaPtx[1]); }
		if (TruePty < ArrayNBinsDeltaPty[0]) { TruePty = 0.5 * (ArrayNBinsDeltaPty[0] + ArrayNBinsDeltaPty[1]); }
		if (TruePL < ArrayNBinsDeltaPL[0]) { TruePL = 0.5 * (ArrayNBinsDeltaPL[0] + ArrayNBinsDeltaPL[1]); }
		if (TruePnPerp < ArrayNBinsDeltaPnPerp[0]) { TruePnPerp = 0.5 * (ArrayNBinsDeltaPnPerp[0] + ArrayNBinsDeltaPnPerp[1]); }
		if (TruePnPerpx < ArrayNBinsDeltaPnPerpx[0]) { TruePnPerpx = 0.5 * (ArrayNBinsDeltaPnPerpx[0] + ArrayNBinsDeltaPnPerpx[1]); }
		if (TruePnPerpy < ArrayNBinsDeltaPnPerpy[0]) { TruePnPerpy = 0.5 * (ArrayNBinsDeltaPnPerpy[0] + ArrayNBinsDeltaPnPerpy[1]); }				
		if (TruePnPar < ArrayNBinsDeltaPnPar[0]) { TruePnPar = 0.5 * (ArrayNBinsDeltaPnPar[0] + ArrayNBinsDeltaPnPar[1]); }										
		if (TrueA < ArrayNBinsA[0]) { TrueA = 0.5 * (ArrayNBinsA[0] + ArrayNBinsA[1]); }
		if (TruePMissMinus < ArrayNBinsPMissMinus[0]) { TruePMissMinus = 0.5 * (ArrayNBinsPMissMinus[0] + ArrayNBinsPMissMinus[1]); }		

		// ----------------------------------------------------------------------------------------------------------------------------
		// ---------------------------------------------------------------------------------------------------------------------------	
		if (MuonMomentum > ArrayNBinsMuonMomentum[0]
		    && ProtonMomentum > ArrayNBinsProtonMomentum[0]
		) {

			if (		
			    // Same evenst fill all the STVLike plots 
			    
			    PTmissMomentum > ArrayNBinsDeltaPT[0] //&& PTmissMomentum < ArrayNBinsDeltaPT[NBinsDeltaPT]
			    && TrueDeltaAlphaT > ArrayNBinsDeltaAlphaT[0] && TrueDeltaAlphaT < ArrayNBinsDeltaAlphaT[NBinsDeltaAlphaT]
		 	    && TrueDeltaPhiT > ArrayNBinsDeltaPhiT[0] && TrueDeltaPhiT < ArrayNBinsDeltaPhiT[NBinsDeltaPhiT]			    
			     
			    && MuonMomentum < ArrayNBinsMuonMomentum[NBinsMuonMomentum]  
			    && ProtonMomentum < ArrayNBinsProtonMomentum[NBinsProtonMomentum]
			    && MuonCosTheta > ArrayNBinsMuonCosTheta[0]
			    && MuonCosTheta < ArrayNBinsMuonCosTheta[NBinsMuonCosTheta]
			    && ProtonCosTheta > ArrayNBinsProtonCosTheta[0]
			    && ProtonCosTheta < ArrayNBinsProtonCosTheta[NBinsProtonCosTheta]
			    
//			    && ECal > ArrayNBinsECal[0] && ECal < ArrayNBinsECal[NBinsECal]
//			    && EQE > ArrayNBinsEQE[0] && EQE < ArrayNBinsEQE[NBinsEQE]
//			    && TrueQ2 > ArrayNBinsQ2[0] && TrueQ2 < ArrayNBinsQ2[NBinsQ2]			    

			) {

				//----------------------------------------//

				// https://arxiv.org/pdf/2106.15809.pdf

				CounterSTVlikeEventsPassedSelection++;
				int genie_mode = -1.;
				if (TMath::Abs(Mode) == 1) { CounterSTVlikeQEEventsPassedSelection++; genie_mode = 1; } // QE
				else if (TMath::Abs(Mode) == 2) { CounterSTVlikeMECEventsPassedSelection++; genie_mode = 2; } // MEC
				else if (
						TMath::Abs(Mode) == 11 || TMath::Abs(Mode) == 12 || TMath::Abs(Mode) == 13 ||
						TMath::Abs(Mode) == 17 || TMath::Abs(Mode) == 22 || TMath::Abs(Mode) == 23
				) { CounterSTVlikeRESEventsPassedSelection++; genie_mode = 3; } // RES
				else if (TMath::Abs(Mode) == 21 || TMath::Abs(Mode) == 26) { CounterSTVlikeDISEventsPassedSelection++; genie_mode = 4; } // DIS
				else if (TMath::Abs(Mode) == 16) { CounterSTVlikeCOHEventsPassedSelection++; genie_mode = 5;} // COH
				else { continue; }  // Feb 8 2022: Only case that is not covered is 15 = diffractive

				//----------------------------------------//

				// True Vertex

				TRandom* rd = new TRandom();
				rd->SetSeed(ientry);				
				double Vx = rd->Uniform(MinVertexX,MaxVertexX);
				double Vy = rd->Uniform(MinVertexY,MaxVertexY);	
				double Vz = rd->Uniform(MinVertexZ,MaxVertexZ);							

				TVector3 TrueVertex( Vx, Vy, Vz);					

				//----------------------------------------//

				// Indices for 2D analysis

				int DeltaPTTwoDIndex = tools.ReturnIndex(PTmissMomentum, TwoDArrayNBinsDeltaPT);
				int DeltaPnTwoDIndex = tools.ReturnIndex(TruePn, TwoDArrayNBinsDeltaPn);				
				int DeltaAlphaTTwoDIndex = tools.ReturnIndex(TrueDeltaAlphaT, TwoDArrayNBinsDeltaAlphaT);
				int DeltaAlpha3DqTwoDIndex = tools.ReturnIndex(TrueDeltaAlpha3Dq, TwoDArrayNBinsDeltaAlpha3Dq);
				int DeltaAlpha3DMuTwoDIndex = tools.ReturnIndex(TrueDeltaAlpha3DMu, TwoDArrayNBinsDeltaAlpha3DMu);								
				int MuonCosThetaTwoDIndex = tools.ReturnIndex(MuonCosTheta, TwoDArrayNBinsMuonCosTheta);
				int ProtonCosThetaTwoDIndex = tools.ReturnIndex(ProtonCosTheta, TwoDArrayNBinsProtonCosTheta);
				int DeltaPtxTwoDIndex = tools.ReturnIndex(TruePtx, TwoDArrayNBinsDeltaPtx);	
				int DeltaPtyTwoDIndex = tools.ReturnIndex(TruePty, TwoDArrayNBinsDeltaPty);	
				int MuonMomentumTwoDIndex = tools.ReturnIndex(MuonMomentum, TwoDArrayNBinsMuonMomentum);
				int ProtonMomentumTwoDIndex = tools.ReturnIndex(ProtonMomentum, TwoDArrayNBinsProtonMomentum);	

				int SerialMuonMomentumInMuonCosThetaIndex = tools.ReturnIndexIn2DList(TwoDArrayNBinsMuonMomentumInMuonCosThetaSlices,MuonCosThetaTwoDIndex,MuonMomentum);
				int SerialProtonMomentumInProtonCosThetaIndex = tools.ReturnIndexIn2DList(TwoDArrayNBinsProtonMomentumInProtonCosThetaSlices,ProtonCosThetaTwoDIndex,ProtonMomentum);				
				int SerialDeltaAlphaTInMuonCosThetaIndex = tools.ReturnIndexIn2DList(TwoDArrayNBinsDeltaAlphaTInMuonCosThetaSlices,MuonCosThetaTwoDIndex,TrueDeltaAlphaT);
				int SerialDeltaAlphaTInMuonMomentumIndex = tools.ReturnIndexIn2DList(TwoDArrayNBinsDeltaAlphaTInMuonMomentumSlices,MuonMomentumTwoDIndex,TrueDeltaAlphaT);				
				int SerialDeltaAlphaTInProtonCosThetaIndex = tools.ReturnIndexIn2DList(TwoDArrayNBinsDeltaAlphaTInProtonCosThetaSlices,ProtonCosThetaTwoDIndex,TrueDeltaAlphaT);
				int SerialDeltaAlphaTInProtonMomentumIndex = tools.ReturnIndexIn2DList(TwoDArrayNBinsDeltaAlphaTInProtonMomentumSlices,ProtonMomentumTwoDIndex,TrueDeltaAlphaT);				
				int SerialDeltaAlphaTInDeltaPTIndex = tools.ReturnIndexIn2DList(TwoDArrayNBinsDeltaAlphaTInDeltaPTSlices,DeltaPTTwoDIndex,TrueDeltaAlphaT);
				int SerialDeltaAlpha3DqInDeltaPnIndex = tools.ReturnIndexIn2DList(TwoDArrayNBinsDeltaAlpha3DqInDeltaPnSlices,DeltaPnTwoDIndex,TrueDeltaAlpha3Dq);
				int SerialDeltaAlpha3DMuInDeltaPnIndex = tools.ReturnIndexIn2DList(TwoDArrayNBinsDeltaAlpha3DMuInDeltaPnSlices,DeltaPnTwoDIndex,TrueDeltaAlpha3DMu);				
				int SerialDeltaPhiTInDeltaPTIndex = tools.ReturnIndexIn2DList(TwoDArrayNBinsDeltaPhiTInDeltaPTSlices,DeltaPTTwoDIndex,TrueDeltaPhiT);
				int SerialDeltaPnInDeltaPTIndex = tools.ReturnIndexIn2DList(TwoDArrayNBinsDeltaPnInDeltaPTSlices,DeltaPTTwoDIndex,TruePn);
				int SerialDeltaPnInDeltaAlphaTIndex = tools.ReturnIndexIn2DList(TwoDArrayNBinsDeltaPnInDeltaAlphaTSlices,DeltaAlphaTTwoDIndex,TruePn);					
				int SerialECalInDeltaPTIndex = tools.ReturnIndexIn2DList(TwoDArrayNBinsECalInDeltaPTSlices,DeltaPTTwoDIndex,ECal);															
				int SerialECalInDeltaPtxIndex = tools.ReturnIndexIn2DList(TwoDArrayNBinsECalInDeltaPtxSlices,DeltaPtxTwoDIndex,ECal);				
				int SerialECalInDeltaPtyIndex = tools.ReturnIndexIn2DList(TwoDArrayNBinsECalInDeltaPtySlices,DeltaPtyTwoDIndex,ECal);
				int SerialECalInDeltaAlphaTIndex = tools.ReturnIndexIn2DList(TwoDArrayNBinsECalInDeltaAlphaTSlices,DeltaAlphaTTwoDIndex,ECal);
				int SerialProtonCosThetaInMuonCosThetaIndex = tools.ReturnIndexIn2DList(TwoDArrayNBinsProtonCosThetaInMuonCosThetaSlices,MuonCosThetaTwoDIndex,ProtonCosTheta);
				int SerialDeltaPtyInDeltaPtxIndex = tools.ReturnIndexIn2DList(TwoDArrayNBinsDeltaPtyInDeltaPtxSlices,DeltaPtxTwoDIndex,TruePty);				
				int SerialDeltaPtxInDeltaPtyIndex = tools.ReturnIndexIn2DList(TwoDArrayNBinsDeltaPtxInDeltaPtySlices,DeltaPtyTwoDIndex,TruePtx);
				int SerialDeltaPTInMuonCosThetaIndex = tools.ReturnIndexIn2DList(TwoDArrayNBinsDeltaPTInMuonCosThetaSlices,MuonCosThetaTwoDIndex,PTmissMomentum);
				int SerialDeltaPTInProtonCosThetaIndex = tools.ReturnIndexIn2DList(TwoDArrayNBinsDeltaPTInProtonCosThetaSlices,ProtonCosThetaTwoDIndex,PTmissMomentum);
				int SerialDeltaPTInDeltaAlphaTIndex = tools.ReturnIndexIn2DList(TwoDArrayNBinsDeltaPTInDeltaAlphaTSlices,DeltaAlphaTTwoDIndex,PTmissMomentum);
				int SerialDeltaPnInDeltaAlpha3DqIndex = tools.ReturnIndexIn2DList(TwoDArrayNBinsDeltaPnInDeltaAlpha3DqSlices,DeltaAlpha3DqTwoDIndex,TruePn);
				int SerialDeltaPnInDeltaAlpha3DMuIndex = tools.ReturnIndexIn2DList(TwoDArrayNBinsDeltaPnInDeltaAlpha3DMuSlices,DeltaAlpha3DMuTwoDIndex,TruePn);								
				int SerialProtonMomentumInDeltaAlphaTIndex = tools.ReturnIndexIn2DList(TwoDArrayNBinsProtonMomentumInDeltaAlphaTSlices,DeltaAlphaTTwoDIndex,ProtonMomentum);				

				int SerialECalInDeltaPTDeltaAlphaTIndex = tools.ReturnIndexIn3DList(TwoDArrayNBinsECalInDeltaPTDeltaAlphaTSlices,DeltaPTTwoDIndex,DeltaAlphaTTwoDIndex,ECal);
				int SerialECalInDeltaPtxDeltaPtyIndex = tools.ReturnIndexIn3DList(TwoDArrayNBinsECalInDeltaPtxDeltaPtySlices,DeltaPtxTwoDIndex,DeltaPtyTwoDIndex,ECal);				
				int SerialECalInMuonCosThetaMuonMomentumIndex = tools.ReturnIndexIn3DList(TwoDArrayNBinsECalInMuonCosThetaMuonMomentumSlices,MuonCosThetaTwoDIndex,MuonMomentumTwoDIndex,ECal);
				int SerialECalInProtonCosThetaProtonMomentumIndex = tools.ReturnIndexIn3DList(TwoDArrayNBinsECalInProtonCosThetaProtonMomentumSlices,ProtonCosThetaTwoDIndex,ProtonMomentumTwoDIndex,ECal);																																																																

				//--------------------------------------------------//				

				// 1D analysis

				TrueVertexXPlot[0]->Fill(TrueVertex.X(),weight);
				TrueVertexYPlot[0]->Fill(TrueVertex.Y(),weight);
				TrueVertexZPlot[0]->Fill(TrueVertex.Z(),weight);				

				double pn = TMath::Sqrt(px_init[1]*px_init[1] + py_init[1]*py_init[1] + pz_init[1]*pz_init[1]);
				TrueStruckNucleonMomPlot[0]->Fill(pn,weight);

				TrueDeltaPTPlot[0]->Fill(PTmissMomentum,weight);
				TrueDeltaAlphaTPlot[0]->Fill(TrueDeltaAlphaT,weight);
				TrueDeltaAlpha3DqPlot[0]->Fill(TrueDeltaAlpha3Dq,weight);
				TrueDeltaAlpha3DMuPlot[0]->Fill(TrueDeltaAlpha3DMu,weight);								
				TrueDeltaPhiTPlot[0]->Fill(TrueDeltaPhiT,weight);
				TrueDeltaPhi3DPlot[0]->Fill(TrueDeltaPhi3D,weight);				
				TrueECalPlot[0]->Fill(ECal,weight);
				TrueEQEPlot[0]->Fill(EQE,weight);
				TrueQ2Plot[0]->Fill(TrueQ2,weight);				
				TrueMuonMomentumPlot[0]->Fill(MuonMomentum,weight);
				TrueMuonPhiPlot[0]->Fill(MuonPhi,weight);
				TrueMuonCosThetaPlot[0]->Fill(MuonCosTheta,weight);
				TrueMuonCosThetaSingleBinPlot[0]->Fill(0.5,weight);
				TrueProtonMomentumPlot[0]->Fill(ProtonMomentum,weight);
				TrueProtonPhiPlot[0]->Fill(ProtonPhi,weight);
				TrueProtonCosThetaPlot[0]->Fill(ProtonCosTheta,weight);			
				TruekMissPlot[0]->Fill(TruekMiss,weight);
				TruePMissMinusPlot[0]->Fill(TruePMissMinus,weight);
				TruePMissPlot[0]->Fill(TrueMissMomentum,weight);
				TrueDeltaPLPlot[0]->Fill(TruePL,weight);
				TrueDeltaPnPlot[0]->Fill(TruePn,weight);
				TrueDeltaPnPerpPlot[0]->Fill(TruePnPerp,weight);
				TrueDeltaPnPerpxPlot[0]->Fill(TruePnPerpx,weight);
				TrueDeltaPnPerpyPlot[0]->Fill(TruePnPerpy,weight);								
				TrueDeltaPnParPlot[0]->Fill(TruePnPar,weight);								
				TrueDeltaPtxPlot[0]->Fill(TruePtx,weight);
				TrueDeltaPtyPlot[0]->Fill(TruePty,weight);
				TrueAPlot[0]->Fill(TrueA,weight);

				TrueVertexXPlot[genie_mode]->Fill(TrueVertex.X(),weight);
				TrueVertexYPlot[genie_mode]->Fill(TrueVertex.Y(),weight);
				TrueVertexZPlot[genie_mode]->Fill(TrueVertex.Z(),weight);				

				TrueStruckNucleonMomPlot[genie_mode]->Fill(pn,weight);

				TrueDeltaPTPlot[genie_mode]->Fill(PTmissMomentum,weight);
				TrueDeltaAlphaTPlot[genie_mode]->Fill(TrueDeltaAlphaT,weight);
				TrueDeltaAlpha3DqPlot[genie_mode]->Fill(TrueDeltaAlpha3Dq,weight);
				TrueDeltaAlpha3DMuPlot[genie_mode]->Fill(TrueDeltaAlpha3DMu,weight);								
				TrueDeltaPhiTPlot[genie_mode]->Fill(TrueDeltaPhiT,weight);
				TrueDeltaPhi3DPlot[genie_mode]->Fill(TrueDeltaPhi3D,weight);				
				TrueECalPlot[genie_mode]->Fill(ECal,weight);
				TrueEQEPlot[genie_mode]->Fill(EQE,weight);
				TrueQ2Plot[genie_mode]->Fill(TrueQ2,weight);				
				TrueMuonMomentumPlot[genie_mode]->Fill(MuonMomentum,weight);
				TrueMuonPhiPlot[genie_mode]->Fill(MuonPhi,weight);
				TrueMuonCosThetaPlot[genie_mode]->Fill(MuonCosTheta,weight);
				TrueMuonCosThetaSingleBinPlot[genie_mode]->Fill(0.5,weight);
				TrueProtonMomentumPlot[genie_mode]->Fill(ProtonMomentum,weight);
				TrueProtonPhiPlot[genie_mode]->Fill(ProtonPhi,weight);
				TrueProtonCosThetaPlot[genie_mode]->Fill(ProtonCosTheta,weight);			
				TruekMissPlot[genie_mode]->Fill(TruekMiss,weight);
				TruePMissMinusPlot[genie_mode]->Fill(TruePMissMinus,weight);
				TruePMissPlot[genie_mode]->Fill(TrueMissMomentum,weight);
				TrueDeltaPLPlot[genie_mode]->Fill(TruePL,weight);
				TrueDeltaPnPlot[genie_mode]->Fill(TruePn,weight);
				TrueDeltaPnPerpPlot[genie_mode]->Fill(TruePnPerp,weight);
				TrueDeltaPnPerpxPlot[genie_mode]->Fill(TruePnPerpx,weight);
				TrueDeltaPnPerpyPlot[genie_mode]->Fill(TruePnPerpy,weight);								
				TrueDeltaPnParPlot[genie_mode]->Fill(TruePnPar,weight);								
				TrueDeltaPtxPlot[genie_mode]->Fill(TruePtx,weight);
				TrueDeltaPtyPlot[genie_mode]->Fill(TruePty,weight);
				TrueAPlot[genie_mode]->Fill(TrueA,weight);					

				//----------------------------------------//

				// 2D analysis (uncorrelated)
				
				TrueDeltaAlphaT_InDeltaPTTwoDPlot[0][DeltaPTTwoDIndex]->Fill(TrueDeltaAlphaT,weight);
				TrueDeltaAlpha3Dq_InDeltaPnTwoDPlot[0][DeltaPnTwoDIndex]->Fill(TrueDeltaAlpha3Dq,weight);
				TrueDeltaAlpha3DMu_InDeltaPnTwoDPlot[0][DeltaPnTwoDIndex]->Fill(TrueDeltaAlpha3DMu,weight);				
				TrueDeltaPhiT_InDeltaPTTwoDPlot[0][DeltaPTTwoDIndex]->Fill(TrueDeltaPhiT,weight);	
				TrueDeltaPn_InDeltaPTTwoDPlot[0][DeltaPTTwoDIndex]->Fill(TruePn,weight);
				TrueDeltaPn_InDeltaAlphaTTwoDPlot[0][DeltaAlphaTTwoDIndex]->Fill(TruePn,weight);				
				TrueDeltaAlphaT_InMuonCosThetaTwoDPlot[0][MuonCosThetaTwoDIndex]->Fill(TrueDeltaAlphaT,weight);
				TrueDeltaAlphaT_InMuonMomentumTwoDPlot[0][MuonMomentumTwoDIndex]->Fill(TrueDeltaAlphaT,weight);				
				TrueDeltaAlphaT_InProtonCosThetaTwoDPlot[0][ProtonCosThetaTwoDIndex]->Fill(TrueDeltaAlphaT,weight);
				TrueDeltaAlphaT_InProtonMomentumTwoDPlot[0][ProtonMomentumTwoDIndex]->Fill(TrueDeltaAlphaT,weight);								
				TrueDeltaPT_InMuonCosThetaTwoDPlot[0][MuonCosThetaTwoDIndex]->Fill(PTmissMomentum,weight);
				TrueDeltaPT_InProtonCosThetaTwoDPlot[0][ProtonCosThetaTwoDIndex]->Fill(PTmissMomentum,weight);				
				TrueMuonMomentum_InMuonCosThetaTwoDPlot[0][MuonCosThetaTwoDIndex]->Fill(MuonMomentum,weight);
				TrueProtonCosTheta_InMuonCosThetaTwoDPlot[0][MuonCosThetaTwoDIndex]->Fill(ProtonCosTheta,weight);				
				TrueProtonMomentum_InProtonCosThetaTwoDPlot[0][ProtonCosThetaTwoDIndex]->Fill(ProtonMomentum,weight);
				TrueDeltaPty_InDeltaPtxTwoDPlot[0][DeltaPtxTwoDIndex]->Fill(TruePty,weight);
				TrueDeltaPtx_InDeltaPtyTwoDPlot[0][DeltaPtyTwoDIndex]->Fill(TruePtx,weight);	
				TrueDeltaPT_InDeltaAlphaTTwoDPlot[0][DeltaAlphaTTwoDIndex]->Fill(PTmissMomentum,weight);
				TrueDeltaPn_InDeltaAlpha3DqTwoDPlot[0][DeltaAlpha3DqTwoDIndex]->Fill(TruePn,weight);
				TrueDeltaPn_InDeltaAlpha3DMuTwoDPlot[0][DeltaAlpha3DMuTwoDIndex]->Fill(TruePn,weight);								
				TrueProtonMomentum_InDeltaAlphaTTwoDPlot[0][DeltaAlphaTTwoDIndex]->Fill(ProtonMomentum,weight);				
				TrueECal_InDeltaAlphaTTwoDPlot[0][DeltaAlphaTTwoDIndex]->Fill(ECal,weight);
				TrueECal_InDeltaPTTwoDPlot[0][DeltaPTTwoDIndex]->Fill(ECal,weight);
				TrueECal_InDeltaPtxTwoDPlot[0][DeltaPtxTwoDIndex]->Fill(ECal,weight);
				TrueECal_InDeltaPtyTwoDPlot[0][DeltaPtyTwoDIndex]->Fill(ECal,weight);				

				TrueDeltaAlphaT_InDeltaPTTwoDPlot[genie_mode][DeltaPTTwoDIndex]->Fill(TrueDeltaAlphaT,weight);
				TrueDeltaAlpha3Dq_InDeltaPnTwoDPlot[genie_mode][DeltaPnTwoDIndex]->Fill(TrueDeltaAlpha3Dq,weight);
				TrueDeltaAlpha3DMu_InDeltaPnTwoDPlot[genie_mode][DeltaPnTwoDIndex]->Fill(TrueDeltaAlpha3DMu,weight);								
				TrueDeltaPhiT_InDeltaPTTwoDPlot[genie_mode][DeltaPTTwoDIndex]->Fill(TrueDeltaPhiT,weight);	
				TrueDeltaPn_InDeltaPTTwoDPlot[genie_mode][DeltaPTTwoDIndex]->Fill(TruePn,weight);
				TrueDeltaPn_InDeltaAlphaTTwoDPlot[genie_mode][DeltaAlphaTTwoDIndex]->Fill(TruePn,weight);				
				TrueDeltaAlphaT_InMuonCosThetaTwoDPlot[genie_mode][MuonCosThetaTwoDIndex]->Fill(TrueDeltaAlphaT,weight);
				TrueDeltaAlphaT_InMuonMomentumTwoDPlot[genie_mode][MuonMomentumTwoDIndex]->Fill(TrueDeltaAlphaT,weight);				
				TrueDeltaAlphaT_InProtonCosThetaTwoDPlot[genie_mode][ProtonCosThetaTwoDIndex]->Fill(TrueDeltaAlphaT,weight);	
				TrueDeltaAlphaT_InProtonMomentumTwoDPlot[genie_mode][ProtonMomentumTwoDIndex]->Fill(TrueDeltaAlphaT,weight);							
				TrueDeltaPT_InMuonCosThetaTwoDPlot[genie_mode][MuonCosThetaTwoDIndex]->Fill(PTmissMomentum,weight);
				TrueDeltaPT_InProtonCosThetaTwoDPlot[genie_mode][ProtonCosThetaTwoDIndex]->Fill(PTmissMomentum,weight);				
				TrueMuonMomentum_InMuonCosThetaTwoDPlot[genie_mode][MuonCosThetaTwoDIndex]->Fill(MuonMomentum,weight);
				TrueProtonCosTheta_InMuonCosThetaTwoDPlot[genie_mode][MuonCosThetaTwoDIndex]->Fill(ProtonCosTheta,weight);				
				TrueProtonMomentum_InProtonCosThetaTwoDPlot[genie_mode][ProtonCosThetaTwoDIndex]->Fill(ProtonMomentum,weight);
				TrueDeltaPty_InDeltaPtxTwoDPlot[genie_mode][DeltaPtxTwoDIndex]->Fill(TruePty,weight);
				TrueDeltaPtx_InDeltaPtyTwoDPlot[genie_mode][DeltaPtyTwoDIndex]->Fill(TruePtx,weight);	
				TrueDeltaPT_InDeltaAlphaTTwoDPlot[genie_mode][DeltaAlphaTTwoDIndex]->Fill(PTmissMomentum,weight);
				TrueDeltaPn_InDeltaAlpha3DqTwoDPlot[genie_mode][DeltaAlpha3DqTwoDIndex]->Fill(TruePn,weight);
				TrueDeltaPn_InDeltaAlpha3DMuTwoDPlot[genie_mode][DeltaAlpha3DMuTwoDIndex]->Fill(TruePn,weight);								
				TrueProtonMomentum_InDeltaAlphaTTwoDPlot[genie_mode][DeltaAlphaTTwoDIndex]->Fill(ProtonMomentum,weight);				
				TrueECal_InDeltaAlphaTTwoDPlot[genie_mode][DeltaAlphaTTwoDIndex]->Fill(ECal,weight);
				TrueECal_InDeltaPTTwoDPlot[genie_mode][DeltaPTTwoDIndex]->Fill(ECal,weight);
				TrueECal_InDeltaPtxTwoDPlot[genie_mode][DeltaPtxTwoDIndex]->Fill(ECal,weight);
				TrueECal_InDeltaPtyTwoDPlot[genie_mode][DeltaPtyTwoDIndex]->Fill(ECal,weight);				

				//----------------------------------------//

				// 3D analysis (uncorrelated)

				TrueECal_InDeltaPTDeltaAlphaTTwoDPlot[0][DeltaPTTwoDIndex][DeltaAlphaTTwoDIndex]->Fill(ECal,weight);
				TrueECal_InDeltaPtxDeltaPtyTwoDPlot[0][DeltaPtxTwoDIndex][DeltaPtyTwoDIndex]->Fill(ECal,weight);				
				TrueECal_InMuonCosThetaMuonMomentumTwoDPlot[0][MuonCosThetaTwoDIndex][MuonMomentumTwoDIndex]->Fill(ECal,weight);
				TrueECal_InProtonCosThetaProtonMomentumTwoDPlot[0][ProtonCosThetaTwoDIndex][ProtonMomentumTwoDIndex]->Fill(ECal,weight);

				TrueECal_InDeltaPTDeltaAlphaTTwoDPlot[genie_mode][DeltaPTTwoDIndex][DeltaAlphaTTwoDIndex]->Fill(ECal,weight);
				TrueECal_InDeltaPtxDeltaPtyTwoDPlot[genie_mode][DeltaPtxTwoDIndex][DeltaPtyTwoDIndex]->Fill(ECal,weight);				
				TrueECal_InMuonCosThetaMuonMomentumTwoDPlot[genie_mode][MuonCosThetaTwoDIndex][MuonMomentumTwoDIndex]->Fill(ECal,weight);
				TrueECal_InProtonCosThetaProtonMomentumTwoDPlot[genie_mode][ProtonCosThetaTwoDIndex][ProtonMomentumTwoDIndex]->Fill(ECal,weight);									

				//----------------------------------------//															

				// 2D analysis in 1D grid

				SerialTrueMuonMomentum_InMuonCosThetaPlot[0]->Fill(SerialMuonMomentumInMuonCosThetaIndex,weight);			
				SerialTrueProtonMomentum_InProtonCosThetaPlot[0]->Fill(SerialProtonMomentumInProtonCosThetaIndex,weight);
				SerialTrueDeltaAlphaT_InMuonCosThetaPlot[0]->Fill(SerialDeltaAlphaTInMuonCosThetaIndex,weight);
				SerialTrueDeltaAlphaT_InMuonMomentumPlot[0]->Fill(SerialDeltaAlphaTInMuonMomentumIndex,weight);				
				SerialTrueDeltaAlphaT_InProtonCosThetaPlot[0]->Fill(SerialDeltaAlphaTInProtonCosThetaIndex,weight);
				SerialTrueDeltaAlphaT_InProtonMomentumPlot[0]->Fill(SerialDeltaAlphaTInProtonMomentumIndex,weight);				
				SerialTrueDeltaAlphaT_InDeltaPTPlot[0]->Fill(SerialDeltaAlphaTInDeltaPTIndex,weight);
				SerialTrueDeltaAlpha3Dq_InDeltaPnPlot[0]->Fill(SerialDeltaAlpha3DqInDeltaPnIndex,weight);
				SerialTrueDeltaAlpha3DMu_InDeltaPnPlot[0]->Fill(SerialDeltaAlpha3DMuInDeltaPnIndex,weight);								
				SerialTrueDeltaPhiT_InDeltaPTPlot[0]->Fill(SerialDeltaPhiTInDeltaPTIndex,weight);
				SerialTrueDeltaPn_InDeltaPTPlot[0]->Fill(SerialDeltaPnInDeltaPTIndex,weight);
				SerialTrueDeltaPn_InDeltaAlphaTPlot[0]->Fill(SerialDeltaPnInDeltaAlphaTIndex,weight);					
				SerialTrueECal_InDeltaPTPlot[0]->Fill(SerialECalInDeltaPTIndex,weight);	
				SerialTrueECal_InDeltaPtxPlot[0]->Fill(SerialECalInDeltaPtxIndex,weight);
				SerialTrueECal_InDeltaPtyPlot[0]->Fill(SerialECalInDeltaPtyIndex,weight);																										
				SerialTrueProtonCosTheta_InMuonCosThetaPlot[0]->Fill(SerialProtonCosThetaInMuonCosThetaIndex,weight);
				SerialTrueDeltaPty_InDeltaPtxPlot[0]->Fill(SerialDeltaPtyInDeltaPtxIndex,weight);
				SerialTrueDeltaPtx_InDeltaPtyPlot[0]->Fill(SerialDeltaPtxInDeltaPtyIndex,weight);	
				SerialTrueDeltaPT_InMuonCosThetaPlot[0]->Fill(SerialDeltaPTInMuonCosThetaIndex,weight);
				SerialTrueDeltaPT_InProtonCosThetaPlot[0]->Fill(SerialDeltaPTInProtonCosThetaIndex,weight);
				SerialTrueDeltaPT_InDeltaAlphaTPlot[0]->Fill(SerialDeltaPTInDeltaAlphaTIndex,weight);
				SerialTrueDeltaPn_InDeltaAlpha3DqPlot[0]->Fill(SerialDeltaPnInDeltaAlpha3DqIndex,weight);
				SerialTrueDeltaPn_InDeltaAlpha3DMuPlot[0]->Fill(SerialDeltaPnInDeltaAlpha3DMuIndex,weight);								
				SerialTrueProtonMomentum_InDeltaAlphaTPlot[0]->Fill(SerialProtonMomentumInDeltaAlphaTIndex,weight);																							
				SerialTrueECal_InDeltaAlphaTPlot[0]->Fill(SerialECalInDeltaAlphaTIndex,weight);

				SerialTrueMuonMomentum_InMuonCosThetaPlot[genie_mode]->Fill(SerialMuonMomentumInMuonCosThetaIndex,weight);			
				SerialTrueProtonMomentum_InProtonCosThetaPlot[genie_mode]->Fill(SerialProtonMomentumInProtonCosThetaIndex,weight);
				SerialTrueDeltaAlphaT_InMuonCosThetaPlot[genie_mode]->Fill(SerialDeltaAlphaTInMuonCosThetaIndex,weight);
				SerialTrueDeltaAlphaT_InMuonMomentumPlot[genie_mode]->Fill(SerialDeltaAlphaTInMuonMomentumIndex,weight);			
				SerialTrueDeltaAlphaT_InProtonCosThetaPlot[genie_mode]->Fill(SerialDeltaAlphaTInProtonCosThetaIndex,weight);
				SerialTrueDeltaAlphaT_InProtonMomentumPlot[genie_mode]->Fill(SerialDeltaAlphaTInProtonMomentumIndex,weight);				
				SerialTrueDeltaAlphaT_InDeltaPTPlot[genie_mode]->Fill(SerialDeltaAlphaTInDeltaPTIndex,weight);
				SerialTrueDeltaAlpha3Dq_InDeltaPnPlot[genie_mode]->Fill(SerialDeltaAlpha3DqInDeltaPnIndex,weight);
				SerialTrueDeltaAlpha3DMu_InDeltaPnPlot[genie_mode]->Fill(SerialDeltaAlpha3DMuInDeltaPnIndex,weight);								
				SerialTrueDeltaPhiT_InDeltaPTPlot[genie_mode]->Fill(SerialDeltaPhiTInDeltaPTIndex,weight);
				SerialTrueDeltaPn_InDeltaPTPlot[genie_mode]->Fill(SerialDeltaPnInDeltaPTIndex,weight);	
				SerialTrueDeltaPn_InDeltaAlphaTPlot[genie_mode]->Fill(SerialDeltaPnInDeltaAlphaTIndex,weight);				
				SerialTrueECal_InDeltaPTPlot[genie_mode]->Fill(SerialECalInDeltaPTIndex,weight);
				SerialTrueECal_InDeltaPtxPlot[genie_mode]->Fill(SerialECalInDeltaPtxIndex,weight);
				SerialTrueECal_InDeltaPtyPlot[genie_mode]->Fill(SerialECalInDeltaPtyIndex,weight);																											
				SerialTrueProtonCosTheta_InMuonCosThetaPlot[genie_mode]->Fill(SerialProtonCosThetaInMuonCosThetaIndex,weight);
				SerialTrueDeltaPty_InDeltaPtxPlot[genie_mode]->Fill(SerialDeltaPtyInDeltaPtxIndex,weight);
				SerialTrueDeltaPtx_InDeltaPtyPlot[genie_mode]->Fill(SerialDeltaPtxInDeltaPtyIndex,weight);	
				SerialTrueDeltaPT_InMuonCosThetaPlot[genie_mode]->Fill(SerialDeltaPTInMuonCosThetaIndex,weight);
				SerialTrueDeltaPT_InProtonCosThetaPlot[genie_mode]->Fill(SerialDeltaPTInProtonCosThetaIndex,weight);
				SerialTrueDeltaPT_InDeltaAlphaTPlot[genie_mode]->Fill(SerialDeltaPTInDeltaAlphaTIndex,weight);
				SerialTrueDeltaPn_InDeltaAlpha3DqPlot[genie_mode]->Fill(SerialDeltaPnInDeltaAlpha3DqIndex,weight);
				SerialTrueDeltaPn_InDeltaAlpha3DMuPlot[genie_mode]->Fill(SerialDeltaPnInDeltaAlpha3DMuIndex,weight);								
				SerialTrueProtonMomentum_InDeltaAlphaTPlot[genie_mode]->Fill(SerialProtonMomentumInDeltaAlphaTIndex,weight);																							
				SerialTrueECal_InDeltaAlphaTPlot[genie_mode]->Fill(SerialECalInDeltaAlphaTIndex,weight);				

				//----------------------------------------//												

				// 3D analysis treated in 1D grid

				SerialTrueECal_InDeltaPTDeltaAlphaTPlot[0]->Fill(SerialECalInDeltaPTDeltaAlphaTIndex,weight);
				SerialTrueECal_InDeltaPtxDeltaPtyPlot[0]->Fill(SerialECalInDeltaPtxDeltaPtyIndex,weight);				
				SerialTrueECal_InMuonCosThetaMuonMomentumPlot[0]->Fill(SerialECalInMuonCosThetaMuonMomentumIndex,weight);
				SerialTrueECal_InProtonCosThetaProtonMomentumPlot[0]->Fill(SerialECalInProtonCosThetaProtonMomentumIndex,weight);

				SerialTrueECal_InDeltaPTDeltaAlphaTPlot[genie_mode]->Fill(SerialECalInDeltaPTDeltaAlphaTIndex,weight);
				SerialTrueECal_InDeltaPtxDeltaPtyPlot[genie_mode]->Fill(SerialECalInDeltaPtxDeltaPtyIndex,weight);				
				SerialTrueECal_InMuonCosThetaMuonMomentumPlot[genie_mode]->Fill(SerialECalInMuonCosThetaMuonMomentumIndex,weight);
				SerialTrueECal_InProtonCosThetaProtonMomentumPlot[genie_mode]->Fill(SerialECalInProtonCosThetaProtonMomentumIndex,weight);								

				//----------------------------------------//

				if (		
					// CCQElike measurement
							
					PTmissMomentum < 0.35
					&& TMath::Abs(DeltaPhiProtonMuon - 180) < 35
					&& TMath::Abs(DeltaThetaProtonMuon - 90) < 55

					&& MuonMomentum > CCQEArrayNBinsMuonMomentum[0]  
					&& ProtonMomentum > CCQEArrayNBinsProtonMomentum[0]					
					&& MuonMomentum < CCQEArrayNBinsMuonMomentum[CCQENBinsMuonMomentum]  
					&& ProtonMomentum < CCQEArrayNBinsProtonMomentum[CCQENBinsProtonMomentum]
						
					&& MuonCosTheta > CCQEArrayNBinsMuonCosTheta[0]
					&& MuonCosTheta < CCQEArrayNBinsMuonCosTheta[CCQENBinsMuonCosTheta]
					&& ProtonCosTheta > CCQEArrayNBinsProtonCosTheta[0]
					&& ProtonCosTheta < CCQEArrayNBinsProtonCosTheta[CCQENBinsProtonCosTheta]

				) {

					TrueCCQEMuonMomentumPlot[0]->Fill(MuonMomentum,weight);
					TrueCCQEMuonPhiPlot[0]->Fill(MuonPhi,weight);
					TrueCCQEMuonCosThetaPlot[0]->Fill(MuonCosTheta,weight);
					TrueCCQEProtonMomentumPlot[0]->Fill(ProtonMomentum,weight);
					TrueCCQEProtonPhiPlot[0]->Fill(ProtonPhi,weight);
					TrueCCQEProtonCosThetaPlot[0]->Fill(ProtonCosTheta,weight);	
					TrueCCQEECalPlot[0]->Fill(ECal,weight);
					TrueCCQEQ2Plot[0]->Fill(TrueQ2,weight);

					TrueCCQEMuonMomentumPlot[genie_mode]->Fill(MuonMomentum,weight);
					TrueCCQEMuonPhiPlot[genie_mode]->Fill(MuonPhi,weight);
					TrueCCQEMuonCosThetaPlot[genie_mode]->Fill(MuonCosTheta,weight);
					TrueCCQEProtonMomentumPlot[genie_mode]->Fill(ProtonMomentum,weight);
					TrueCCQEProtonPhiPlot[genie_mode]->Fill(ProtonPhi,weight);
					TrueCCQEProtonCosThetaPlot[genie_mode]->Fill(ProtonCosTheta,weight);	
					TrueCCQEECalPlot[genie_mode]->Fill(ECal,weight);
					TrueCCQEQ2Plot[genie_mode]->Fill(TrueQ2,weight);					
														
				}				


			} // End of the event selection
			
		} // End of the angle selection cuts && the demand that we fill the plots with the same events

		// ----------------------------------------------------------------------------------------------------------------------------------	

	} // End of the loop over the events
	
	// ----------------------------------------------------------------------------------------------------------------------------------------

	// STVlike analysis
	
	std::cout << std::endl << "----------------------- STVlike analysis -------------------------" << std::endl << std::endl;

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

	// ---------------------------------------------------------------------------------------------------------------------------------------
	// -------------------------------------------------------------------------------------------------------------------------------------------

	double ScalingFactor = 1.;

	// Division by bin width to get the cross sections
	
	// Division by bin width to get the cross sections
	
	// Loop over the interaction processes

	for (int inte = 0; inte < NInte; inte++) {

		//----------------------------------------//
	
		// 1D analysis

		tools.Reweight(TrueMuonMomentumPlot[inte],ScalingFactor);
		tools.Reweight(TrueMuonPhiPlot[inte],ScalingFactor);
		tools.Reweight(TrueMuonCosThetaPlot[inte],ScalingFactor);
		tools.Reweight(TrueMuonCosThetaSingleBinPlot[inte],ScalingFactor);
		tools.Reweight(TrueProtonMomentumPlot[inte],ScalingFactor);
		tools.Reweight(TrueProtonPhiPlot[inte],ScalingFactor);
		tools.Reweight(TrueProtonCosThetaPlot[inte],ScalingFactor);
		tools.Reweight(TrueECalPlot[inte],ScalingFactor);
		tools.Reweight(TrueEQEPlot[inte],ScalingFactor);	
		tools.Reweight(TrueQ2Plot[inte],ScalingFactor);
		tools.Reweight(TrueCCQEMuonMomentumPlot[inte],ScalingFactor);
		tools.Reweight(TrueCCQEMuonPhiPlot[inte],ScalingFactor);
		tools.Reweight(TrueCCQEMuonCosThetaPlot[inte],ScalingFactor);
		tools.Reweight(TrueCCQEProtonMomentumPlot[inte],ScalingFactor);
		tools.Reweight(TrueCCQEProtonPhiPlot[inte],ScalingFactor);
		tools.Reweight(TrueCCQEProtonCosThetaPlot[inte],ScalingFactor);
		tools.Reweight(TrueCCQEECalPlot[inte],ScalingFactor);
		tools.Reweight(TrueCCQEQ2Plot[inte],ScalingFactor);	
		tools.Reweight(TrueDeltaPTPlot[inte],ScalingFactor);
		tools.Reweight(TrueDeltaAlphaTPlot[inte],ScalingFactor);
		tools.Reweight(TrueDeltaAlpha3DqPlot[inte],ScalingFactor);
		tools.Reweight(TrueDeltaAlpha3DMuPlot[inte],ScalingFactor);				
		tools.Reweight(TrueDeltaPhiTPlot[inte],ScalingFactor);
		tools.Reweight(TrueDeltaPhi3DPlot[inte],ScalingFactor);		
		tools.Reweight(TrueDeltaPLPlot[inte],ScalingFactor);
		tools.Reweight(TrueDeltaPnPlot[inte],ScalingFactor);
		tools.Reweight(TrueDeltaPnPerpPlot[inte],ScalingFactor);
		tools.Reweight(TrueDeltaPnPerpxPlot[inte],ScalingFactor);
		tools.Reweight(TrueDeltaPnPerpyPlot[inte],ScalingFactor);				
		tools.Reweight(TrueDeltaPnParPlot[inte],ScalingFactor);				
		tools.Reweight(TrueDeltaPtxPlot[inte],ScalingFactor);
		tools.Reweight(TrueDeltaPtyPlot[inte],ScalingFactor);
		tools.Reweight(TrueAPlot[inte],ScalingFactor);
		tools.Reweight(TruekMissPlot[inte],ScalingFactor);
		tools.Reweight(TruePMissPlot[inte],ScalingFactor);
		tools.Reweight(TruePMissMinusPlot[inte],ScalingFactor);
		tools.Reweight(TrueVertexXPlot[inte],ScalingFactor);
		tools.Reweight(TrueVertexYPlot[inte],ScalingFactor);				
		tools.Reweight(TrueVertexZPlot[inte],ScalingFactor);		

		//----------------------------------------//

		// 2D & 3D analysis (uncorrelated)

		for (int WhichDeltaPn = 0; WhichDeltaPn < TwoDNBinsDeltaPn; WhichDeltaPn++) {

			tools.Reweight(TrueDeltaAlpha3Dq_InDeltaPnTwoDPlot[inte][WhichDeltaPn],ScalingFactor);
			tools.Reweight(TrueDeltaAlpha3DMu_InDeltaPnTwoDPlot[inte][WhichDeltaPn],ScalingFactor);			

		}		

		for (int WhichDeltaPT = 0; WhichDeltaPT < TwoDNBinsDeltaPT; WhichDeltaPT++) {

			tools.Reweight(TrueDeltaAlphaT_InDeltaPTTwoDPlot[inte][WhichDeltaPT],ScalingFactor);
			tools.Reweight(TrueDeltaPhiT_InDeltaPTTwoDPlot[inte][WhichDeltaPT],ScalingFactor);	
			tools.Reweight(TrueDeltaPn_InDeltaPTTwoDPlot[inte][WhichDeltaPT],ScalingFactor);	
			tools.Reweight(TrueECal_InDeltaPTTwoDPlot[inte][WhichDeltaPT],ScalingFactor);		

			for (int WhichDeltaAlphaT = 0; WhichDeltaAlphaT < TwoDNBinsDeltaAlphaT; WhichDeltaAlphaT++) {	

						tools.Reweight(TrueECal_InDeltaPTDeltaAlphaTTwoDPlot[inte][WhichDeltaPT][WhichDeltaAlphaT],ScalingFactor);

			}

		}

		for (int WhichDeltaAlpha3Dq = 0; WhichDeltaAlpha3Dq < TwoDNBinsDeltaAlpha3Dq; WhichDeltaAlpha3Dq++) {

			tools.Reweight(TrueDeltaPn_InDeltaAlpha3DqTwoDPlot[inte][WhichDeltaAlpha3Dq],ScalingFactor);

		}

		for (int WhichDeltaAlpha3DMu = 0; WhichDeltaAlpha3DMu < TwoDNBinsDeltaAlpha3DMu; WhichDeltaAlpha3DMu++) {

			tools.Reweight(TrueDeltaPn_InDeltaAlpha3DMuTwoDPlot[inte][WhichDeltaAlpha3DMu],ScalingFactor);

		}				

		for (int WhichDeltaAlphaT = 0; WhichDeltaAlphaT < TwoDNBinsDeltaAlphaT; WhichDeltaAlphaT++) {

			tools.Reweight(TrueDeltaPn_InDeltaAlphaTTwoDPlot[inte][WhichDeltaAlphaT],ScalingFactor);
			tools.Reweight(TrueDeltaPT_InDeltaAlphaTTwoDPlot[inte][WhichDeltaAlphaT],ScalingFactor);
			tools.Reweight(TrueProtonMomentum_InDeltaAlphaTTwoDPlot[inte][WhichDeltaAlphaT],ScalingFactor);			
			tools.Reweight(TrueECal_InDeltaAlphaTTwoDPlot[inte][WhichDeltaAlphaT],ScalingFactor);		

		}	

		for (int WhichMuonMomentum = 0; WhichMuonMomentum < TwoDNBinsMuonMomentum; WhichMuonMomentum++) {

			tools.Reweight(TrueDeltaAlphaT_InMuonMomentumTwoDPlot[inte][WhichMuonMomentum],ScalingFactor);

		}

		for (int WhichMuonCosTheta = 0; WhichMuonCosTheta < TwoDNBinsMuonCosTheta; WhichMuonCosTheta++) {

			tools.Reweight(TrueDeltaAlphaT_InMuonCosThetaTwoDPlot[inte][WhichMuonCosTheta],ScalingFactor);
			tools.Reweight(TrueDeltaPT_InMuonCosThetaTwoDPlot[inte][WhichMuonCosTheta],ScalingFactor);		
			tools.Reweight(TrueMuonMomentum_InMuonCosThetaTwoDPlot[inte][WhichMuonCosTheta],ScalingFactor);
			tools.Reweight(TrueProtonCosTheta_InMuonCosThetaTwoDPlot[inte][WhichMuonCosTheta],ScalingFactor);		

			for (int WhichMuonMomentum = 0; WhichMuonMomentum < TwoDNBinsMuonMomentum; WhichMuonMomentum++) {	

				tools.Reweight(TrueECal_InMuonCosThetaMuonMomentumTwoDPlot[inte][WhichMuonCosTheta][WhichMuonMomentum],ScalingFactor);

			}		

		}	

		for (int WhichProtonMomentum = 0; WhichProtonMomentum < TwoDNBinsProtonMomentum; WhichProtonMomentum++) {

			tools.Reweight(TrueDeltaAlphaT_InProtonMomentumTwoDPlot[inte][WhichProtonMomentum],ScalingFactor);

		}		

		for (int WhichProtonCosTheta = 0; WhichProtonCosTheta < TwoDNBinsProtonCosTheta; WhichProtonCosTheta++) {

			tools.Reweight(TrueProtonMomentum_InProtonCosThetaTwoDPlot[inte][WhichProtonCosTheta],ScalingFactor);	
			tools.Reweight(TrueDeltaAlphaT_InProtonCosThetaTwoDPlot[inte][WhichProtonCosTheta],ScalingFactor);
			tools.Reweight(TrueDeltaPT_InProtonCosThetaTwoDPlot[inte][WhichProtonCosTheta],ScalingFactor);				

			for (int WhichProtonMomentum = 0; WhichProtonMomentum < TwoDNBinsProtonMomentum; WhichProtonMomentum++) {	

						tools.Reweight(TrueECal_InProtonCosThetaProtonMomentumTwoDPlot[inte][WhichProtonCosTheta][WhichProtonMomentum],ScalingFactor);

			}		

		}

		for (int WhichDeltaPtx = 0; WhichDeltaPtx < TwoDNBinsDeltaPtx; WhichDeltaPtx++) {

			tools.Reweight(TrueDeltaPty_InDeltaPtxTwoDPlot[inte][WhichDeltaPtx],ScalingFactor);	
			tools.Reweight(TrueECal_InDeltaPtxTwoDPlot[inte][WhichDeltaPtx],ScalingFactor);	

			for (int WhichDeltaPty = 0; WhichDeltaPty < TwoDNBinsDeltaPty; WhichDeltaPty++) {	

						tools.Reweight(TrueECal_InDeltaPtxDeltaPtyTwoDPlot[inte][WhichDeltaPtx][WhichDeltaPty],ScalingFactor);

			}					

		}

		for (int WhichDeltaPty = 0; WhichDeltaPty < TwoDNBinsDeltaPty; WhichDeltaPty++) {

			tools.Reweight(TrueDeltaPtx_InDeltaPtyTwoDPlot[inte][WhichDeltaPty],ScalingFactor);
			tools.Reweight(TrueECal_InDeltaPtyTwoDPlot[inte][WhichDeltaPty],ScalingFactor);				

		}			

	} // End of the loop over the interaction processes		

	//----------------------------------------//		
		
	file->cd();
	file->Write();
	fFile->Close();

	std::cout << std::endl;
	std::cout << "File " << FileNameAndPath +" has been created created " << std::endl; 
	std::cout << std::endl;

} // End of the program
