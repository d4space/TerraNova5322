#include <iostream>
#include "../EventSelection/include/SetupTreeHighPU.h" 
using namespace std;
#define	RealLumi	(19619) //pb      //Whole
//#define	RealLumi	(890.608) //pb    //A
//#define	RealLumi	(4429) //pb             //B
//#define	RealLumi	(7026.245) //pb   //C
//#define	RealLumi	(7274) //pb       //D
void wEtaAna()
{
//======================================
// choose Mode and AnaChannel here  !!!
//======================================
//  TString Mode = "Resolution";//Analysis,Recoil, RecoilMC, RecoilCorr, Resolution,
//  TString AnaChannel = "MuonLowPU"; //ElectronLowPU

TString Mode = "Analysis";//Analysis,Recoil, RecoilMC, RecoilCorr, Resolution,
TString AnaChannelEle = "ElectronHighPU";//ElectronLowPU
TString AnaChannelMu  = "MuonLowPU";

  gSystem->CompileMacro("../EventSelection/WLepNeu.C","k");
// For Electron analysis: use the lines FROM HERE
//Luminosity weight
  double LumiWeight_Ele_DYToEE_S10	   = RealLumi*1*1915.08/3277040;
  double LumiWeight_Ele_DYJetsToLL_S10     = RealLumi*1*2950/28709500;
  double LumiWeight_Ele_DYToTauTau_S10     = RealLumi*1*1581.419/9989370;
  double LumiWeight_Ele_WToENu_S10         = RealLumi*1*12503.0/4383520;
  double LumiWeight_Ele_WpToENu_S10        = RealLumi*1*7322.0/6554350;
  double LumiWeight_Ele_WmToENu_S10        = RealLumi*1*5181.0/6553050;
  double LumiWeight_Ele_WpToTauNu_S10      = RealLumi*1*7322.0/5880570;
  double LumiWeight_Ele_WmToTauNu_S10      = RealLumi*1*5142.3/4601540;
  double LumiWeight_Ele_WToTauNu_S10       = RealLumi*1*12503.0/5000740;
  double LumiWeight_Ele_WJetsToLNu_S10     = RealLumi*1*30400/105000;
  double LumiWeight_Ele_TTJets_S10         = RealLumi*1*136.3/1364780;
  double LumiWeight_Ele_TT_CT10_S10        = RealLumi*1*225.197/2990940;
  double LumiWeight_Ele_QCD30to50_S10      = RealLumi*1*66285328/5800000;
  double LumiWeight_Ele_QCD50to80_S10      = RealLumi*1*8148778/5920350;
  double LumiWeight_Ele_QCD80to120_S10     = RealLumi*1*1033680/5994860;
  double LumiWeight_Ele_QCD120to170_S10    = RealLumi*1*156293.3/4744420;
  double LumiWeight_Ele_G_Pt50to80_S10     = RealLumi*1*3322.309/1995060;

  double LumiWeight_Ele_RD_HighPU = 1;
  double LumiWeight_Ele_RD_HighPU_A = 1;
  double LumiWeight_Ele_RD_HighPU_B = 1;
  double LumiWeight_Ele_RD_HighPU_C = 1;
  double LumiWeight_Ele_RD_HighPU_D = 1;


//Ele_RD_HighPU========================================
/*
  cout<<"Ele_RD_HighPU===================="<<endl;
  TChain *TC_Ele_RD_HighPU    = new TChain("WEleNeu/tree","");
  TChain *TC_Ele_RD_HighPU_Ele = new TChain("Electrons/tree","");
  SetupTreeHighPU("Ele_RD_HighPU",TC_Ele_RD_HighPU);
  SetupTreeHighPU("Ele_RD_HighPU",TC_Ele_RD_HighPU_Ele);
  TString Ele_RD_HighPUFile = "Ele_RD_HighPU_"+Mode;
  WLepNeu WelePt_Ele_RD_HighPU(TC_Ele_RD_HighPU,TC_Ele_RD_HighPU_Ele,
        LumiWeight_Ele_RD_HighPU, Ele_RD_HighPUFile,Mode,AnaChannelEle);
  WelePt_Ele_RD_HighPU.Loop();

cout<<"Ele_RD_HighPU_A===================="<<endl;
  TChain *TC_Ele_RD_HighPU_A    = new TChain("WEleNeu/tree","");
    TChain *TC_Ele_RD_HighPU_A_Ele = new TChain("Electrons/tree","");
      SetupTreeHighPU("Ele_RD_HighPU_A",TC_Ele_RD_HighPU_A);
        SetupTreeHighPU("Ele_RD_HighPU_A",TC_Ele_RD_HighPU_A_Ele);
	  TString Ele_RD_HighPU_AFile = "Ele_RD_HighPU_A_"+Mode;
	    WLepNeu WelePt_Ele_RD_HighPU_A(TC_Ele_RD_HighPU_A,TC_Ele_RD_HighPU_A_Ele,
		        LumiWeight_Ele_RD_HighPU_A, Ele_RD_HighPU_AFile,Mode,AnaChannelEle);
	      WelePt_Ele_RD_HighPU_A.Loop();

cout<<"Ele_RD_HighPU_B===================="<<endl;
  TChain *TC_Ele_RD_HighPU_B    = new TChain("WEleNeu/tree","");
    TChain *TC_Ele_RD_HighPU_B_Ele = new TChain("Electrons/tree","");
      SetupTreeHighPU("Ele_RD_HighPU_B",TC_Ele_RD_HighPU_B);
        SetupTreeHighPU("Ele_RD_HighPU_B",TC_Ele_RD_HighPU_B_Ele);
	  TString Ele_RD_HighPU_BFile = "Ele_RD_HighPU_B_"+Mode;
	    WLepNeu WelePt_Ele_RD_HighPU_B(TC_Ele_RD_HighPU_B,TC_Ele_RD_HighPU_B_Ele,
		        LumiWeight_Ele_RD_HighPU_B, Ele_RD_HighPU_BFile,Mode,AnaChannelEle);
	      WelePt_Ele_RD_HighPU_B.Loop();
*//*
  cout<<"Ele_RD_HighPU_C===================="<<endl;
  TChain *TC_Ele_RD_HighPU_C    = new TChain("WEleNeu/tree","");
    TChain *TC_Ele_RD_HighPU_C_Ele = new TChain("Electrons/tree","");
      SetupTreeHighPU("Ele_RD_HighPU_C",TC_Ele_RD_HighPU_C);
        SetupTreeHighPU("Ele_RD_HighPU_C",TC_Ele_RD_HighPU_C_Ele);
	  TString Ele_RD_HighPU_CFile = "Ele_RD_HighPU_C_"+Mode;
	    WLepNeu WelePt_Ele_RD_HighPU_C(TC_Ele_RD_HighPU_C,TC_Ele_RD_HighPU_C_Ele,
		        LumiWeight_Ele_RD_HighPU_C, Ele_RD_HighPU_CFile,Mode,AnaChannelEle);
	      WelePt_Ele_RD_HighPU_C.Loop();
*//*
cout<<"Ele_RD_HighPU_D===================="<<endl;
  TChain *TC_Ele_RD_HighPU_D    = new TChain("WEleNeu/tree","");
    TChain *TC_Ele_RD_HighPU_D_Ele = new TChain("Electrons/tree","");
      SetupTreeHighPU("Ele_RD_HighPU_D",TC_Ele_RD_HighPU_D);
        SetupTreeHighPU("Ele_RD_HighPU_D",TC_Ele_RD_HighPU_D_Ele);
	  TString Ele_RD_HighPU_DFile = "Ele_RD_HighPU_D_"+Mode;
	    WLepNeu WelePt_Ele_RD_HighPU_D(TC_Ele_RD_HighPU_D,TC_Ele_RD_HighPU_D_Ele,
		        LumiWeight_Ele_RD_HighPU_D, Ele_RD_HighPU_DFile,Mode,AnaChannelEle);
	      WelePt_Ele_RD_HighPU_D.Loop();

*/	      
  cout<<"Ele_DYToEE_S10==========================="<<endl;
  TChain *TC_Ele_DYToEE_S10    = new TChain("WEleNeu/tree","");
  TChain *TC_Ele_DYToEE_S10_Ele = new TChain("Electrons/tree","");
  SetupTreeHighPU("Ele_DYToEE_S10",TC_Ele_DYToEE_S10);
  SetupTreeHighPU("Ele_DYToEE_S10",TC_Ele_DYToEE_S10_Ele);
  TString Ele_DYToEE_S10File = "Ele_DYToEE_S10_"+Mode;
  WLepNeu WelePt_Ele_DYToEE_S10(TC_Ele_DYToEE_S10,TC_Ele_DYToEE_S10_Ele,
  	LumiWeight_Ele_DYToEE_S10, Ele_DYToEE_S10File,Mode,AnaChannelEle);
  WelePt_Ele_DYToEE_S10.Loop();
/*
  cout<<"Ele_DYJetsToLL_S10==========================="<<endl;
  TChain *TC_Ele_DYJetsToLL_S10    = new TChain("WEleNeu/tree","");
  TChain *TC_Ele_DYJetsToLL_S10_Ele = new TChain("Electrons/tree","");
  SetupTreeHighPU("Ele_DYJetsToLL_S10",TC_Ele_DYJetsToLL_S10);
  SetupTreeHighPU("Ele_DYJetsToLL_S10",TC_Ele_DYJetsToLL_S10_Ele);
  TString Ele_DYJetsToLL_S10File = "Ele_DYJetsToLL_S10_"+Mode;
  WLepNeu WelePt_Ele_DYJetsToLL_S10(TC_Ele_DYJetsToLL_S10,TC_Ele_DYJetsToLL_S10_Ele,
        LumiWeight_Ele_DYJetsToLL_S10, Ele_DYJetsToLL_S10File,Mode,AnaChannelEle);
  WelePt_Ele_DYJetsToLL_S10.Loop();
*/
  cout<<"Ele_DYToTauTau_S10==========================="<<endl;
  TChain *TC_Ele_DYToTauTau_S10    = new TChain("WEleNeu/tree","");
  TChain *TC_Ele_DYToTauTau_S10_Ele = new TChain("Electrons/tree","");
  SetupTreeHighPU("Ele_DYToTauTau_S10",TC_Ele_DYToTauTau_S10);
  SetupTreeHighPU("Ele_DYToTauTau_S10",TC_Ele_DYToTauTau_S10_Ele);
  TString Ele_DYToTauTau_S10File = "Ele_DYToTauTau_S10_"+Mode;
  WLepNeu WelePt_Ele_DYToTauTau_S10(TC_Ele_DYToTauTau_S10,TC_Ele_DYToTauTau_S10_Ele,
  	LumiWeight_Ele_DYToTauTau_S10, Ele_DYToTauTau_S10File,Mode,AnaChannelEle);
  WelePt_Ele_DYToTauTau_S10.Loop();

  cout<<"Ele_WminusToEleNu_S10==========================="<<endl;
  TChain *TC_Ele_WmToENu_S10    = new TChain("WEleNeu/tree","");
  TChain *TC_Ele_WmToENu_S10_Ele = new TChain("Electrons/tree","");
  SetupTreeHighPU("Ele_WmToENu_S10",TC_Ele_WmToENu_S10);
  SetupTreeHighPU("Ele_WmToENu_S10",TC_Ele_WmToENu_S10_Ele);
  TString Ele_WmToENu_S10File = "Ele_WmToENu_S10_"+Mode;
  WLepNeu WelePt_Ele_WmToENu_S10(TC_Ele_WmToENu_S10,TC_Ele_WmToENu_S10_Ele,
  	LumiWeight_Ele_WmToENu_S10, Ele_WmToENu_S10File,Mode,AnaChannelEle);
  WelePt_Ele_WmToENu_S10.Loop();

  cout<<"Ele_WplusToEleNu_S10==========================="<<endl;
  TChain *TC_Ele_WpToENu_S10    = new TChain("WEleNeu/tree","");
  TChain *TC_Ele_WpToENu_S10_Ele = new TChain("Electrons/tree","");
  SetupTreeHighPU("Ele_WpToENu_S10",TC_Ele_WpToENu_S10);
  SetupTreeHighPU("Ele_WpToENu_S10",TC_Ele_WpToENu_S10_Ele);
  TString Ele_WpToENu_S10File = "Ele_WpToENu_S10_"+Mode;
  WLepNeu WelePt_Ele_WpToENu_S10(TC_Ele_WpToENu_S10,TC_Ele_WpToENu_S10_Ele,
  	LumiWeight_Ele_WpToENu_S10, Ele_WpToENu_S10File,Mode,AnaChannelEle);
  WelePt_Ele_WpToENu_S10.Loop();

  cout<<"Ele_WToTauNu_S10============================"<<endl;
  TChain *TC_Ele_WToTauNu_S10     = new TChain("WEleNeu/tree","");
  TChain *TC_Ele_WToTauNu_S10_Ele = new TChain("Electrons/tree","");
  SetupTreeHighPU("Ele_WToTauNu_S10",TC_Ele_WToTauNu_S10);
  SetupTreeHighPU("Ele_WToTauNu_S10",TC_Ele_WToTauNu_S10_Ele);
  TString Ele_WToTauNu_S10File = "Ele_WToTauNu_S10_"+Mode;
  WLepNeu WelePt_Ele_WToTauNu_S10(TC_Ele_WToTauNu_S10,TC_Ele_WToTauNu_S10_Ele,
  	LumiWeight_Ele_WToTauNu_S10, Ele_WToTauNu_S10File,Mode,AnaChannelEle);
  WelePt_Ele_WToTauNu_S10.Loop();
/*
  cout<<"Ele_WToENu_S10============================"<<endl;
  TChain *TC_Ele_WToENu_S10     = new TChain("WEleNeu/tree","");
  TChain *TC_Ele_WToENu_S10_Ele = new TChain("Electrons/tree","");
  SetupTreeHighPU("Ele_WToENu_S10",TC_Ele_WToENu_S10);
  SetupTreeHighPU("Ele_WToENu_S10",TC_Ele_WToENu_S10_Ele);
  TString Ele_WToENu_S10File = "Ele_WToENu_S10_"+Mode;
  WLepNeu WelePt_Ele_WToENu_S10(TC_Ele_WToENu_S10,TC_Ele_WToENu_S10_Ele,
        LumiWeight_Ele_WToENu_S10, Ele_WToENu_S10File,Mode,AnaChannelEle);
  WelePt_Ele_WToENu_S10.Loop();

cout<<"Ele_WpToTauNu_S10==========================="<<endl;
  TChain *TC_Ele_WpToTauNu_S10     = new TChain("WEleNeu/tree","");
  TChain *TC_Ele_WpToTauNu_S10_Ele = new TChain("Electrons/tree","");
  SetupTreeHighPU("Ele_WpToTauNu_S10",TC_Ele_WpToTauNu_S10);
  SetupTreeHighPU("Ele_WpToTauNu_S10",TC_Ele_WpToTauNu_S10_Ele);
  TString Ele_WpToTauNu_S10File = "Ele_WpToTauNu_S10_"+Mode;
  WLepNeu WelePt_Ele_WpToTauNu_S10(TC_Ele_WpToTauNu_S10,TC_Ele_WpToTauNu_S10_Ele,
        LumiWeight_Ele_WpToTauNu_S10, Ele_WpToTauNu_S10File,Mode,AnaChannelEle);
  WelePt_Ele_WpToTauNu_S10.Loop();

  cout<<"Ele_WmToTauNu_S10==========================="<<endl;
  TChain *TC_Ele_WmToTauNu_S10     = new TChain("WEleNeu/tree","");
  TChain *TC_Ele_WmToTauNu_S10_Ele = new TChain("Electrons/tree","");
  SetupTreeHighPU("Ele_WmToTauNu_S10",TC_Ele_WmToTauNu_S10);
  SetupTreeHighPU("Ele_WmToTauNu_S10",TC_Ele_WmToTauNu_S10_Ele);
  TString Ele_WmToTauNu_S10File = "Ele_WmToTauNu_S10_"+Mode;
  WLepNeu WelePt_Ele_WmToTauNu_S10(TC_Ele_WmToTauNu_S10,TC_Ele_WmToTauNu_S10_Ele,
        LumiWeight_Ele_WmToTauNu_S10, Ele_WmToTauNu_S10File,Mode,AnaChannelEle);
  WelePt_Ele_WmToTauNu_S10.Loop();

  cout<<"Ele_WJetsToLNu_S10==========================="<<endl;
  TChain *TC_Ele_WJetsToLNu_S10     = new TChain("WEleNeu/tree","");
  TChain *TC_Ele_WJetsToLNu_S10_Ele = new TChain("Electrons/tree","");
  SetupTreeHighPU("Ele_WJetsToLNu_S10",TC_Ele_WJetsToLNu_S10);
  SetupTreeHighPU("Ele_WJetsToLNu_S10",TC_Ele_WJetsToLNu_S10_Ele);
  TString Ele_WJetsToLNu_S10File = "Ele_WJetsToLNu_S10_"+Mode;
  WLepNeu WelePt_Ele_WJetsToLNu_S10(TC_Ele_WJetsToLNu_S10,TC_Ele_WJetsToLNu_S10_Ele,
        LumiWeight_Ele_WJetsToLNu_S10, Ele_WJetsToLNu_S10File,Mode,AnaChannelEle);
  WelePt_Ele_WJetsToLNu_S10.Loop();
*/
  cout<<"Ele_TTJets_S10==========================="<<endl;
  TChain *TC_Ele_TTJets_S10    = new TChain("WEleNeu/tree","");
  TChain *TC_Ele_TTJets_S10_Ele = new TChain("Electrons/tree","");
  SetupTreeHighPU("Ele_TTJets_S10",TC_Ele_TTJets_S10);
  SetupTreeHighPU("Ele_TTJets_S10",TC_Ele_TTJets_S10_Ele);
  TString Ele_TTJets_S10File = "Ele_TTJets_S10_"+Mode;
  WLepNeu WelePt_Ele_TTJets_S10(TC_Ele_TTJets_S10,TC_Ele_TTJets_S10_Ele,
  	LumiWeight_Ele_TTJets_S10, Ele_TTJets_S10File,Mode,AnaChannelEle);
  WelePt_Ele_TTJets_S10.Loop();
/*
  cout<<"Ele_TT_CT10_S10==========================="<<endl;
  TChain *TC_Ele_TT_CT10_S10    = new TChain("WEleNeu/tree","");
  TChain *TC_Ele_TT_CT10_S10_Ele = new TChain("Electrons/tree","");
  SetupTreeHighPU("Ele_TT_CT10_S10",TC_Ele_TT_CT10_S10);
  SetupTreeHighPU("Ele_TT_CT10_S10",TC_Ele_TT_CT10_S10_Ele);
  TString Ele_TT_CT10_S10File = "Ele_TT_CT10_S10_"+Mode;
  WLepNeu WelePt_Ele_TT_CT10_S10(TC_Ele_TT_CT10_S10,TC_Ele_TT_CT10_S10_Ele,
        LumiWeight_Ele_TT_CT10_S10, Ele_TT_CT10_S10File,Mode,AnaChannelEle);
  WelePt_Ele_TT_CT10_S10.Loop();

  cout<<"Ele_QCD30to50_S10==========================="<<endl;
  TChain *TC_Ele_QCD30to50_S10    = new TChain("WEleNeu/tree","");
  TChain *TC_Ele_QCD30to50_S10_Ele = new TChain("Electrons/tree","");
  SetupTreeHighPU("Ele_QCD30to50_S10",TC_Ele_QCD30to50_S10);
  SetupTreeHighPU("Ele_QCD30to50_S10",TC_Ele_QCD30to50_S10_Ele);
  TString Ele_QCD30to50_S10File = "Ele_QCD30to50_S10_"+Mode;
  WLepNeu WelePt_Ele_QCD30to50_S10(TC_Ele_QCD30to50_S10,TC_Ele_QCD30to50_S10_Ele,
        LumiWeight_Ele_QCD30to50_S10, Ele_QCD30to50_S10File,Mode,AnaChannelEle);
  WelePt_Ele_QCD30to50_S10.Loop();

  cout<<"Ele_QCD50to80_S10==========================="<<endl;
  TChain *TC_Ele_QCD50to80_S10    = new TChain("WEleNeu/tree","");
  TChain *TC_Ele_QCD50to80_S10_Ele = new TChain("Electrons/tree","");
  SetupTreeHighPU("Ele_QCD50to80_S10",TC_Ele_QCD50to80_S10);
  SetupTreeHighPU("Ele_QCD50to80_S10",TC_Ele_QCD50to80_S10_Ele);
  TString Ele_QCD50to80_S10File = "Ele_QCD50to80_S10_"+Mode;
  WLepNeu WelePt_Ele_QCD50to80_S10(TC_Ele_QCD50to80_S10,TC_Ele_QCD50to80_S10_Ele,
        LumiWeight_Ele_QCD50to80_S10, Ele_QCD50to80_S10File,Mode,AnaChannelEle);
  WelePt_Ele_QCD50to80_S10.Loop();

  cout<<"Ele_QCD80to120_S10==========================="<<endl;
  TChain *TC_Ele_QCD80to120_S10    = new TChain("WEleNeu/tree","");
  TChain *TC_Ele_QCD80to120_S10_Ele = new TChain("Electrons/tree","");
  SetupTreeHighPU("Ele_QCD80to120_S10",TC_Ele_QCD80to120_S10);
  SetupTreeHighPU("Ele_QCD80to120_S10",TC_Ele_QCD80to120_S10_Ele);
  TString Ele_QCD80to120_S10File = "Ele_QCD80to120_S10_"+Mode;
  WLepNeu WelePt_Ele_QCD80to120_S10(TC_Ele_QCD80to120_S10,TC_Ele_QCD80to120_S10_Ele,
        LumiWeight_Ele_QCD80to120_S10, Ele_QCD80to120_S10File,Mode,AnaChannelEle);
  WelePt_Ele_QCD80to120_S10.Loop();

  cout<<"Ele_QCD120to170_S10==========================="<<endl;
  TChain *TC_Ele_QCD120to170_S10    = new TChain("WEleNeu/tree","");
  TChain *TC_Ele_QCD120to170_S10_Ele = new TChain("Electrons/tree","");
  SetupTreeHighPU("Ele_QCD120to170_S10",TC_Ele_QCD120to170_S10);
  SetupTreeHighPU("Ele_QCD120to170_S10",TC_Ele_QCD120to170_S10_Ele);
  TString Ele_QCD120to170_S10File = "Ele_QCD120to170_S10_"+Mode;
  WLepNeu WelePt_Ele_QCD120to170_S10(TC_Ele_QCD120to170_S10,TC_Ele_QCD120to170_S10_Ele,
        LumiWeight_Ele_QCD120to170_S10, Ele_QCD120to170_S10File,Mode,AnaChannelEle);
  WelePt_Ele_QCD120to170_S10.Loop();

  cout<<"Ele_G_Pt50to80_S10==========================="<<endl;
  TChain *TC_Ele_G_Pt50to80_S10    = new TChain("WEleNeu/tree","");
  TChain *TC_Ele_G_Pt50to80_S10_Ele = new TChain("Electrons/tree","");
  SetupTreeHighPU("Ele_G_Pt50to80_S10",TC_Ele_G_Pt50to80_S10);
  SetupTreeHighPU("Ele_G_Pt50to80_S10",TC_Ele_G_Pt50to80_S10_Ele);
  TString Ele_G_Pt50to80_S10File = "Ele_G_Pt50to80_S10_"+Mode;
  WLepNeu WelePt_Ele_G_Pt50to80_S10(TC_Ele_G_Pt50to80_S10,TC_Ele_G_Pt50to80_S10_Ele,
        LumiWeight_Ele_G_Pt50to80_S10, Ele_G_Pt50to80_S10File,Mode,AnaChannelEle);
  WelePt_Ele_G_Pt50to80_S10.Loop();
*/

}
