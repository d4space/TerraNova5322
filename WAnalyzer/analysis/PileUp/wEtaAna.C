#include <iostream>
#include "../EventSelection/include/SetupTreeHighPU.h"
//#include "../EventSelection/WLepNeu.h"
using namespace std;

//#define	RealLumi	(18.977) //pb
#define	RealLumi	(764.648) //pb
//test
//#define	RealLumi	(808.472) //pb
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
//====================
/////////// Muon LowPU
//====================
// For Muon analysis: use the lines FROM HERE
/***************************
  //Luminosity weight
  double LumiWeight_Muon_WpToMuNu_S8 = RealLumi*1*6702.0/935446;
  double LumiWeight_Muon_WmToMuNu_S8 = RealLumi*1*4697.0/1.97346e6;
  double LumiWeight_Muon_DYToMuMu_S8 = RealLumi*1*1871.0/1.9802e6;
  double LumiWeight_Muon_WToTauNu_S8 = RealLumi*1*9170.0/2.13398e6;
  double LumiWeight_Muon_DYToTauTau_S8 = RealLumi*1*1510.0/1.98778e6;
  double LumiWeight_Muon_TTJets_S8 = RealLumi*1*136.3/6.73614e6;
  double LumiWeight_Muon_RD_LowPU = 1;

//RD========================================
  cout<<"RD===================="<<endl;
  TChain *TC_Muon_RD_LowPU    = new TChain("WMuNeu/tree","");
  TChain *TC_Muon_RD_LowPU_Mu = new TChain("Muons/tree","");
  SetupTree("Muon_RD_LowPU",TC_Muon_RD_LowPU);
  SetupTree("Muon_RD_LowPU",TC_Muon_RD_LowPU_Mu);
  TString Muon_RD_LowPUFile = "Muon_RD_LowPU_"+Mode;
  WLepNeu WmuPt_Muon_RD_LowPU(TC_Muon_RD_LowPU,TC_Muon_RD_LowPU_Mu,LumiWeight_Muon_RD_LowPU, Muon_RD_LowPUFile,Mode,AnaChannelMu);
  WmuPt_Muon_RD_LowPU.Loop();
  
//WpToMuNu========================================
  cout<<"WpToMuNu_S8===================="<<endl;
  TChain *TC_Muon_WpToMuNu_S8    = new TChain("WMuNeu/tree","");
  TChain *TC_Muon_WpToMuNu_S8_Mu = new TChain("Muons/tree","");
  SetupTree("Muon_WpToMuNu_S8",TC_Muon_WpToMuNu_S8);
  SetupTree("Muon_WpToMuNu_S8",TC_Muon_WpToMuNu_S8_Mu);
  TString Muon_WpToMuNuFile = "Muon_WpToMuNu_S8_"+Mode;
  WLepNeu WmuPt_WpMuNu(TC_Muon_WpToMuNu_S8,TC_Muon_WpToMuNu_S8_Mu,
  	LumiWeight_Muon_WpToMuNu_S8, Muon_WpToMuNuFile,Mode,AnaChannelMu);
  WmuPt_WpMuNu.Loop();
  
//WmToMuNu========================================
  cout<<"WmToMuNu_S8========================"<<endl;
  TChain *TC_Muon_WmToMuNu_S8    = new TChain("WMuNeu/tree","");
  TChain *TC_Muon_WmToMuNu_S8_Mu = new TChain("Muons/tree","");
  SetupTree("Muon_WmToMuNu_S8",TC_Muon_WmToMuNu_S8);
  SetupTree("Muon_WmToMuNu_S8",TC_Muon_WmToMuNu_S8_Mu);
  TString Muon_WmToMuNuFile = "Muon_WmToMuNu_S8_"+Mode;
  WLepNeu WmuPt_WmMuNu(TC_Muon_WmToMuNu_S8,TC_Muon_WmToMuNu_S8_Mu,
  	LumiWeight_Muon_WmToMuNu_S8, Muon_WmToMuNuFile,Mode,AnaChannelMu);
  WmuPt_WmMuNu.Loop();

//DYToMuMu========================================
  cout<<"DYToMuMu_S8========================="<<endl;
  TChain *TC_Muon_DYToMuMu_S8	= new TChain("WMuNeu/tree","");
  TChain *TC_Muon_DYToMuMu_S8_Mu	= new TChain("Muons/tree","");
  SetupTree("Muon_DYToMuMu_S8",TC_Muon_DYToMuMu_S8);
  SetupTree("Muon_DYToMuMu_S8",TC_Muon_DYToMuMu_S8_Mu);
  TString Muon_DYToMuMuFile = "Muon_DYToMuMu_S8_"+Mode;
  WLepNeu WPt_DYMuMu(TC_Muon_DYToMuMu_S8,TC_Muon_DYToMuMu_S8_Mu,
  	LumiWeight_Muon_DYToMuMu_S8, Muon_DYToMuMuFile,Mode,AnaChannelMu);
  WPt_DYMuMu.Loop();

//WToTauNu======================================
  cout<<"WToTauNu_S8=========================="<<endl;
  TChain *TC_Muon_WToTauNu_S8	= new TChain("WMuNeu/tree","");
  TChain *TC_Muon_WToTauNu_S8_Mu	= new TChain("Muons/tree","");
  SetupTree("Muon_WToTauNu_S8",TC_Muon_WToTauNu_S8);
  SetupTree("Muon_WToTauNu_S8",TC_Muon_WToTauNu_S8_Mu);
  TString Muon_WToTauNuFile = "Muon_WToTauNu_S8_"+Mode;
  WLepNeu WPt_WToTauNu(TC_Muon_WToTauNu_S8,TC_Muon_WToTauNu_S8_Mu,
  	LumiWeight_Muon_WToTauNu_S8, Muon_WToTauNuFile,Mode,AnaChannelMu);
  WPt_WToTauNu.Loop();

//DYToTauTau======================================
  cout<<"DYToTauTau_S8======================="<<endl;
  TChain *TC_Muon_DYToTauTau_S8	= new TChain("WMuNeu/tree","");
  TChain *TC_Muon_DYToTauTau_S8_Mu	= new TChain("Muons/tree","");
  SetupTree("Muon_DYToTauTau_S8",TC_Muon_DYToTauTau_S8);
  SetupTree("Muon_DYToTauTau_S8",TC_Muon_DYToTauTau_S8_Mu);
  TString Muon_DYToTauTauFile = "Muon_DYToTauTau_S8_"+Mode;
  WLepNeu WPt_DYTauTau(TC_Muon_DYToTauTau_S8,TC_Muon_DYToTauTau_S8_Mu,
  	LumiWeight_Muon_DYToTauTau_S8, Muon_DYToTauTauFile,Mode,AnaChannelMu);
  WPt_DYTauTau.Loop();
  
//TTJets======================================
  cout<<"TTJets_S8==========================="<<endl;
  TChain *TC_Muon_TTJets_S8	= new TChain("WMuNeu/tree","");
  TChain *TC_Muon_TTJets_S8_Mu	= new TChain("Muons/tree","");
  SetupTree("Muon_TTJets_S8",TC_Muon_TTJets_S8);
  SetupTree("Muon_TTJets_S8",TC_Muon_TTJets_S8_Mu);
  TString Muon_TTJetsFile = "Muon_TTJets_S8_"+Mode;
  WLepNeu WPt_TTJets(TC_Muon_TTJets_S8,TC_Muon_TTJets_S8_Mu,
  	LumiWeight_Muon_TTJets_S8, Muon_TTJetsFile,Mode,AnaChannelMu);
  WPt_TTJets.Loop();
// For Muon analysis: TO HERE
**********************************/

//=========================
/////////// Electron LowPU
//=========================
// For Electron analysis: use the lines FROM HERE
//Luminosity weight
/***
  double LumiWeight_Ele_DYToEE_S8= RealLumi*1*1871.0/3297045;
  double LumiWeight_Ele_DYToTauTau_S8= RealLumi*1*1510.0/1987776;
  double LumiWeight_Ele_WpToEleNu_S8= RealLumi*1*6702.0/2401905;
  double LumiWeight_Ele_WmToEleNu_S8= RealLumi*1*4697.0/2127666;
  double LumiWeight_Ele_WToTauNu_S8= RealLumi*1*9170.0/2133983;
  double LumiWeight_Ele_TTJets_S8= RealLumi*1*136.3/6736135;
 ***/
//***
/*  double LumiWeight_Ele_DYToEE_S7	= RealLumi*1*1871.0/3325720;
  double LumiWeight_Ele_DYToTauTau_S7	= RealLumi*1*1871.0/9989370;
  double LumiWeight_Ele_WpToENu_S7	= RealLumi*1*6702.0/4718140;
  double LumiWeight_Ele_WmToENu_S7	= RealLumi*1*4697.0/4266660;
  double LumiWeight_Ele_WmToTauNu_S7    = RealLumi*1*4697.0/;
  double LumiWeight_Ele_WToTauNu_S7	= RealLumi*1*9710.0/5000740;
  double LumiWeight_Ele_WJetsToLNu_S7   = RealLumi*1*30400/105000;
  double LumiWeight_Ele_TTJets_S7	= RealLumi*1*136.3/1364780;
  double LumiWeight_Ele_TT_CT10_S7      = RealLumi*1*211.0/9468990;
  double LumiWeight_Ele_QCD30to50_S7    = RealLumi*1*66285328/4473390;
  double LumiWeight_Ele_QCD50to80_S7    = RealLumi*1*8148778/3998860;
  double LumiWeight_Ele_QCD80to120_S7   = RealLumi*1*1033680/1756080;
  double LumiWeight_Ele_QCD120to170_S7  = RealLumi*1*156293.3/4744420;
  double LumiWeight_Ele_G_Pt50to80_S7   = RealLumi*1*3322.309/1335060;
*/
//***/

 // double LumiWeight_Ele_RD_HighPU = 1;

double LumiWeight_Ele_WToENu_S10         = RealLumi*1*12503.0/4383520;
//***/

  double LumiWeight_Ele_RD_HighPU = 1;


//Ele_RD_HighPU========================================

  cout<<"Ele_RD_HighPU===================="<<endl;
  TChain *TC_Ele_RD_HighPU    = new TChain("WEleNeu/tree","");
  TChain *TC_Ele_RD_HighPU_Ele = new TChain("Electrons/tree","");
  SetupTreeHighPU("Ele_RD_HighPU",TC_Ele_RD_HighPU);
  SetupTreeHighPU("Ele_RD_HighPU",TC_Ele_RD_HighPU_Ele);
  TString Ele_RD_HighPUFile = "Ele_RD_HighPU_"+Mode;
  WLepNeu WelePt_Ele_RD_HighPU(TC_Ele_RD_HighPU,TC_Ele_RD_HighPU_Ele,
        LumiWeight_Ele_RD_HighPU, Ele_RD_HighPUFile,Mode,AnaChannelEle);
  WelePt_Ele_RD_HighPU.Loop();


  cout<<"Ele_WToENu_S10============================"<<endl;
  TChain *TC_Ele_WToENu_S10     = new TChain("WEleNeu/tree","");
  TChain *TC_Ele_WToENu_S10_Ele = new TChain("Electrons/tree","");
  SetupTreeHighPU("Ele_WToENu_S10",TC_Ele_WToENu_S10);
  SetupTreeHighPU("Ele_WToENu_S10",TC_Ele_WToENu_S10_Ele);
  TString Ele_WToENu_S10File = "Ele_WToENu_S10_"+Mode;
  WLepNeu WelePt_Ele_WToENu_S10(TC_Ele_WToENu_S10,TC_Ele_WToENu_S10_Ele,
        LumiWeight_Ele_WToENu_S10, Ele_WToENu_S10File,Mode,AnaChannelEle);
  WelePt_Ele_WToENu_S10.Loop();















//  double LumiWeight_Ele_RD_LowPU = 1;
/*
  cout<<"Ele_RD_LowPU===================="<<endl;
  TChain *TC_Ele_RD_LowPU    = new TChain("WEleNeu/tree","");
  TChain *TC_Ele_RD_LowPU_Ele = new TChain("Electrons/tree","");
  SetupTreeHighPU("Ele_RD_LowPU",TC_Ele_RD_LowPU);
  SetupTreeHighPU("Ele_RD_LowPU",TC_Ele_RD_LowPU_Ele);
  TString Ele_RD_LowPUFile = "Ele_RD_LowPU_"+Mode;
  WLepNeu WelePt_Ele_RD_LowPU(TC_Ele_RD_LowPU,TC_Ele_RD_LowPU_Ele,
        LumiWeight_Ele_RD_LowPU, Ele_RD_LowPUFile,Mode,AnaChannelEle);
  WelePt_Ele_RD_LowPU.Loop();

*/



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
*/
/*
  cout<<"Ele_DYToEE_S7==========================="<<endl;
  TChain *TC_Ele_DYToEE_S7    = new TChain("WEleNeu/tree","");
  TChain *TC_Ele_DYToEE_S7_Ele = new TChain("Electrons/tree","");
  SetupTreeHighPU("Ele_DYToEE_S7",TC_Ele_DYToEE_S7);
  SetupTreeHighPU("Ele_DYToEE_S7",TC_Ele_DYToEE_S7_Ele);
  TString Ele_DYToEE_S7File = "Ele_DYToEE_S7_"+Mode;
  WLepNeu WelePt_Ele_DYToEE_S7(TC_Ele_DYToEE_S7,TC_Ele_DYToEE_S7_Ele,
  	LumiWeight_Ele_DYToEE_S7, Ele_DYToEE_S7File,Mode,AnaChannelEle);
  WelePt_Ele_DYToEE_S7.Loop();

  cout<<"Ele_DYToTauTau_S7==========================="<<endl;
  TChain *TC_Ele_DYToTauTau_S7    = new TChain("WEleNeu/tree","");
  TChain *TC_Ele_DYToTauTau_S7_Ele = new TChain("Electrons/tree","");
  SetupTreeHighPU("Ele_DYToTauTau_S7",TC_Ele_DYToTauTau_S7);
  SetupTreeHighPU("Ele_DYToTauTau_S7",TC_Ele_DYToTauTau_S7_Ele);
  TString Ele_DYToTauTau_S7File = "Ele_DYToTauTau_S7_"+Mode;
  WLepNeu WelePt_Ele_DYToTauTau_S7(TC_Ele_DYToTauTau_S7,TC_Ele_DYToTauTau_S7_Ele,
  	LumiWeight_Ele_DYToTauTau_S7, Ele_DYToTauTau_S7File,Mode,AnaChannelEle);
  WelePt_Ele_DYToTauTau_S7.Loop();
*/
  cout<<"Ele_WminusToEleNu_S7==========================="<<endl;
  TChain *TC_Ele_WmToENu_S7    = new TChain("WEleNeu/tree","");
  TChain *TC_Ele_WmToENu_S7_Ele = new TChain("Electrons/tree","");
  SetupTreeHighPU("Ele_WmToENu_S7",TC_Ele_WmToENu_S7);
  SetupTreeHighPU("Ele_WmToENu_S7",TC_Ele_WmToENu_S7_Ele);
  TString Ele_WmToENu_S7File = "Ele_WmToENu_S7_"+Mode;
  WLepNeu WelePt_Ele_WmToENu_S7(TC_Ele_WmToENu_S7,TC_Ele_WmToENu_S7_Ele,
  	LumiWeight_Ele_WmToENu_S7, Ele_WmToENu_S7File,Mode,AnaChannelEle);
  WelePt_Ele_WmToENu_S7.Loop();

  cout<<"Ele_WplusToEleNu_S7==========================="<<endl;
  TChain *TC_Ele_WpToENu_S7    = new TChain("WEleNeu/tree","");
  TChain *TC_Ele_WpToENu_S7_Ele = new TChain("Electrons/tree","");
  SetupTreeHighPU("Ele_WpToENu_S7",TC_Ele_WpToENu_S7);
  SetupTreeHighPU("Ele_WpToENu_S7",TC_Ele_WpToENu_S7_Ele);
  TString Ele_WpToENu_S7File = "Ele_WpToENu_S7_"+Mode;
  WLepNeu WelePt_Ele_WpToENu_S7(TC_Ele_WpToENu_S7,TC_Ele_WpToENu_S7_Ele,
  	LumiWeight_Ele_WpToENu_S7, Ele_WpToENu_S7File,Mode,AnaChannelEle);
  WelePt_Ele_WpToENu_S7.Loop();
/*
  cout<<"Ele_WToTauNu_S7============================"<<endl;
  TChain *TC_Ele_WToTauNu_S7     = new TChain("WEleNeu/tree","");
  TChain *TC_Ele_WToTauNu_S7_Ele = new TChain("Electrons/tree","");
  SetupTreeHighPU("Ele_WToTauNu_S7",TC_Ele_WToTauNu_S7);
  SetupTreeHighPU("Ele_WToTauNu_S7",TC_Ele_WToTauNu_S7_Ele);
  TString Ele_WToTauNu_S7File = "Ele_WToTauNu_S7_"+Mode;
  WLepNeu WelePt_Ele_WToTauNu_S7(TC_Ele_WToTauNu_S7,TC_Ele_WToTauNu_S7_Ele,
  	LumiWeight_Ele_WToTauNu_S7, Ele_WToTauNu_S7File,Mode,AnaChannelEle);
  WelePt_Ele_WToTauNu_S7.Loop();

  cout<<"Ele_WmToTauNu_S7==========================="<<endl;
  TChain *TC_Ele_WmToTauNu_S7     = new TChain("WEleNeu/tree","");
  TChain *TC_Ele_WmToTauNu_S7_Ele = new TChain("Electrons/tree","");
  SetupTreeHighPU("Ele_WmToTauNu_S7",TC_Ele_WmToTauNu_S7);
  SetupTreeHighPU("Ele_WmToTauNu_S7",TC_Ele_WmToTauNu_S7_Ele);
  TString Ele_WmToTauNu_S7File = "Ele_WmToTauNu_S7_"+Mode;
  WLepNeu WelePt_Ele_WmToTauNu_S7(TC_Ele_WmToTauNu_S7,TC_Ele_WmToTauNu_S7_Ele,
        LumiWeight_Ele_WmToTauNu_S7, Ele_WmToTauNu_S7File,Mode,AnaChannelEle);
  WelePt_Ele_WmToTauNu_S7.Loop();

  cout<<"Ele_WJetsToLNu_S7==========================="<<endl;
  TChain *TC_Ele_WJetsToLNu_S7     = new TChain("WEleNeu/tree","");
  TChain *TC_Ele_WJetsToLNu_S7_Ele = new TChain("Electrons/tree","");
  SetupTreeHighPU("Ele_WJetsToLNu_S7",TC_Ele_WJetsToLNu_S7);
  SetupTreeHighPU("Ele_WJetsToLNu_S7",TC_Ele_WJetsToLNu_S7_Ele);
  TString Ele_WJetsToLNu_S7File = "Ele_WJetsToLNu_S7_"+Mode;
  WLepNeu WelePt_Ele_WJetsToLNu_S7(TC_Ele_WJetsToLNu_S7,TC_Ele_WJetsToLNu_S7_Ele,
        LumiWeight_Ele_WJetsToLNu_S7, Ele_WJetsToLNu_S7File,Mode,AnaChannelEle);
  WelePt_Ele_WJetsToLNu_S7.Loop();

  cout<<"Ele_TTJets_S7==========================="<<endl;
  TChain *TC_Ele_TTJets_S7    = new TChain("WEleNeu/tree","");
  TChain *TC_Ele_TTJets_S7_Ele = new TChain("Electrons/tree","");
  SetupTreeHighPU("Ele_TTJets_S7",TC_Ele_TTJets_S7);
  SetupTreeHighPU("Ele_TTJets_S7",TC_Ele_TTJets_S7_Ele);
  TString Ele_TTJets_S7File = "Ele_TTJets_S7_"+Mode;
  WLepNeu WelePt_Ele_TTJets_S7(TC_Ele_TTJets_S7,TC_Ele_TTJets_S7_Ele,
  	LumiWeight_Ele_TTJets_S7, Ele_TTJets_S7File,Mode,AnaChannelEle);
  WelePt_Ele_TTJets_S7.Loop();


  cout<<"Ele_TT_ST10_S7==========================="<<endl;
  TChain *TC_Ele_TT_CT10_S7    = new TChain("WEleNeu/tree","");
  TChain *TC_Ele_TT_CT10_S7_Ele = new TChain("Electrons/tree","");
  SetupTreeHighPU("Ele_TT_CT10_S7",TC_Ele_TTJets_S7);
  SetupTreeHighPU("Ele_TT_CT10_S7",TC_Ele_TTJets_S7_Ele);
  TString Ele_TT_CT10_S7File = "Ele_TT_CT10_S7_"+Mode;
  WLepNeu WelePt_Ele_TT_CT10_S7(TC_Ele_TT_CT10_S7,TC_Ele_TT_CT10_S7_Ele,
        LumiWeight_Ele_TT_CT10_S7, Ele_TT_CT10_S7File,Mode,AnaChannelEle);
  WelePt_Ele_TT_CT10_S7.Loop();
*/

  cout<<"Ele_QCD30to50_S7==========================="<<endl;
  TChain *TC_Ele_QCD30to50_S7    = new TChain("WEleNeu/tree","");
  TChain *TC_Ele_QCD30to50_S7_Ele = new TChain("Electrons/tree","");
  SetupTreeHighPU("Ele_QCD30to50_S7",TC_Ele_QCD30to50_S7);
  SetupTreeHighPU("Ele_QCD30to50_S7",TC_Ele_QCD30to50_S7_Ele);
  TString Ele_QCD30to50_S7File = "Ele_QCD30to50_S7_"+Mode;
  WLepNeu WelePt_Ele_QCD30to50_S7(TC_Ele_QCD30to50_S7,TC_Ele_QCD30to50_S7_Ele,
        LumiWeight_Ele_QCD30to50_S7, Ele_QCD30to50_S7File,Mode,AnaChannelEle);
  WelePt_Ele_QCD30to50_S7.Loop();

  cout<<"Ele_QCD50to80_S7==========================="<<endl;
  TChain *TC_Ele_QCD50to80_S7    = new TChain("WEleNeu/tree","");
  TChain *TC_Ele_QCD50to80_S7_Ele = new TChain("Electrons/tree","");
  SetupTreeHighPU("Ele_QCD50to80_S7",TC_Ele_QCD50to80_S7);
  SetupTreeHighPU("Ele_QCD50to80_S7",TC_Ele_QCD50to80_S7_Ele);
  TString Ele_QCD50to80_S7File = "Ele_QCD50to80_S7_"+Mode;
  WLepNeu WelePt_Ele_QCD50to80_S7(TC_Ele_QCD50to80_S7,TC_Ele_QCD50to80_S7_Ele,
        LumiWeight_Ele_QCD50to80_S7, Ele_QCD50to80_S7File,Mode,AnaChannelEle);
  WelePt_Ele_QCD50to80_S7.Loop();

  cout<<"Ele_QCD80to120_S7==========================="<<endl;
  TChain *TC_Ele_QCD80to120_S7    = new TChain("WEleNeu/tree","");
  TChain *TC_Ele_QCD80to120_S7_Ele = new TChain("Electrons/tree","");
  SetupTreeHighPU("Ele_QCD80to120_S7",TC_Ele_QCD80to120_S7);
  SetupTreeHighPU("Ele_QCD80to120_S7",TC_Ele_QCD80to120_S7_Ele);
  TString Ele_QCD80to120_S7File = "Ele_QCD80to120_S7_"+Mode;
  WLepNeu WelePt_Ele_QCD80to120_S7(TC_Ele_QCD80to120_S7,TC_Ele_QCD80to120_S7_Ele,
        LumiWeight_Ele_QCD80to120_S7, Ele_QCD80to120_S7File,Mode,AnaChannelEle);
  WelePt_Ele_QCD80to120_S7.Loop();

  cout<<"Ele_QCD120to170_S7==========================="<<endl;
  TChain *TC_Ele_QCD120to170_S7    = new TChain("WEleNeu/tree","");
  TChain *TC_Ele_QCD120to170_S7_Ele = new TChain("Electrons/tree","");
  SetupTreeHighPU("Ele_QCD120to170_S7",TC_Ele_QCD120to170_S7);
  SetupTreeHighPU("Ele_QCD120to170_S7",TC_Ele_QCD120to170_S7_Ele);
  TString Ele_QCD120to170_S7File = "Ele_QCD120to170_S7_"+Mode;
  WLepNeu WelePt_Ele_QCD120to170_S7(TC_Ele_QCD120to170_S7,TC_Ele_QCD120to170_S7_Ele,
        LumiWeight_Ele_QCD120to170_S7, Ele_QCD120to170_S7File,Mode,AnaChannelEle);
  WelePt_Ele_QCD120to170_S7.Loop();
/*
  cout<<"Ele_G_Pt50to80_S7==========================="<<endl;
  TChain *TC_Ele_G_Pt50to80_S7    = new TChain("WEleNeu/tree","");
  TChain *TC_Ele_G_Pt50to80_S7_Ele = new TChain("Electrons/tree","");
  SetupTreeHighPU("Ele_G_Pt50to80_S7",TC_Ele_G_Pt50to80_S7);
  SetupTreeHighPU("Ele_G_Pt50to80_S7",TC_Ele_G_Pt50to80_S7_Ele);
  TString Ele_G_Pt50to80_S7File = "Ele_G_Pt50to80_S7_"+Mode;
  WLepNeu WelePt_Ele_G_Pt50to80_S7(TC_Ele_G_Pt50to80_S7,TC_Ele_G_Pt50to80_S7_Ele,
        LumiWeight_Ele_G_Pt50to80_S7, Ele_G_Pt50to80_S7File,Mode,AnaChannelEle);
  WelePt_Ele_G_Pt50to80_S7.Loop();
*/

// For Electron analysis: TO HERE
}
