{
 
	vector<TString> WhichSample; vector<TString> WhichName;

	//----------------------------------------//

	WhichSample.push_back("14_1000180400_CC_v3_4_0_G18_10a_02_11a.flat"); WhichName.push_back("GENIE");
	WhichSample.push_back("gntp.0.gprep_NoFSI.flat"); WhichName.push_back("GENIE_noFSI");
	//WhichSample.push_back("/pnfs/uboone/persistent/users/mastbaum/tuning2022/mc/bnb_ub/flat/bnb.ub.num.genie_v3_00_06.flat.root"); WhichName.push_back("GENIE");//"GENIE_v3_0_6");
	WhichSample.push_back("NEUT.flat"); WhichName.push_back("NEUT");
	WhichSample.push_back("NuWro.flat"); WhichName.push_back("NuWro");
	WhichSample.push_back("GiBUU.flat"); WhichName.push_back("GiBUU");				

	//----------------------------------------//

	gROOT->ProcessLine(".L FlatTreeAnalyzer.cxx+");

	for (int i =0;i < (int)(WhichSample.size()); i++) {

		gROOT->ProcessLine("FlatTreeAnalyzer(\""+WhichSample[i]+"\",\""+WhichName[i]+"\").Loop()");

	}
	//gROOT->ProcessLine(".q");
};
