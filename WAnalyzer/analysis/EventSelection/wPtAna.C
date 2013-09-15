#include <iostream>
#include "include/SetupTree.h"
using namespace std;
#define	RealLumi	(18.977) //pb
void wPtAna()
{
//======================================
// choose Mode and AnaChannel here  !!!
//======================================
TString AnaChannelEle = "ElectronLowPU"; //ElectronLowPU, ElectronHighPU
TString AnaChannelMu  = "MuonLowPU";

/// Uncomment to use Analysis mode
//  TString ModeMC = "Analysis";		//Analysis,RecoilRD, RecoilMC, RecoilCorrMC, AllCorrectionsMC,Unfold
//  TString ModeRD = "Analysis";		//Analysis,RecoilRD, RecoilMC, RecoilCorrMC, AllCorrectionsRD,Unfold

/// Uncomment to apply only RecoilCorr to W+ -->e+ nu and W- -->e- nu
//  TString ModeMC = "RecoilCorrMC";		//Analysis,RecoilRD, RecoilMC, RecoilCorrMC, SmearMC,Unfold

/// Uncomment to apply AllCorrections (Smear and RecoilCorr) to W+ -->e+ nu and W- -->e- nu MC and AllCorrections (Scale) to RD
  TString ModeMC = "AllCorrectionsMC";		//Analysis,RecoilRD, RecoilMC, RecoilCorrMC, AllCorrectionsMC,Unfold
  TString ModeRD = "AllCorrectionsRD";		//Analysis,RecoilRD, RecoilMC, RecoilCorrMC, AllCorrectionsRD,Unfold

/// Uncomment for Unfolding  
//  TString ModeMC = "Unfold";			//Analysis,RecoilRD, RecoilMC, RecoilCorrMC,AllCorrectionsMC,Unfold
//  TString ModeRD = "Unfold";			//Analysis,RecoilRD, RecoilMC, RecoilCorrMC,AllCorrectionsRD,Unfold

  
  gSystem->CompileMacro("WLepNeu.C","k");
//====================
/////////// Muon LowPU
//====================
// For Muon analysis: use the lines FROM HERE
//***************************
  //Luminosity weight
  double LumiWeight_Muon_WpToMuNu_S8 = RealLumi*1*6702.0/935446;
  double LumiWeight_Muon_WmToMuNu_S8 = RealLumi*1*4697.0/1.97346e6;
  double LumiWeight_Muon_DYToMuMu_S8 = RealLumi*1*1871.0/1.9802e6;
  double LumiWeight_Muon_WToTauNu_S8 = RealLumi*1*9170.0/2.13398e6;
  double LumiWeight_Muon_DYToTauTau_S8 = RealLumi*1*1510.0/1.98778e6;
  double LumiWeight_Muon_TTJets_S8 = RealLumi*1*136.3/6.73614e6;
  double LumiWeight_Muon_RD_LowPU = 1;

//RD========================================
/*
  cout<<"RD===================="<<endl;
  TChain *TC_Muon_RD_LowPU    = new TChain("WMuNeu/tree","");
  TChain *TC_Muon_RD_LowPU_Mu = new TChain("Muons/tree","");
  SetupTree("Muon_RD_LowPU",TC_Muon_RD_LowPU);
  SetupTree("Muon_RD_LowPU",TC_Muon_RD_LowPU_Mu);
  TString Muon_RD_LowPUFile = "Muon_RD_LowPU_"+ModeRD;
  WLepNeu WmuPt_Muon_RD_LowPU(
      TC_Muon_RD_LowPU,TC_Muon_RD_LowPU_Mu,LumiWeight_Muon_RD_LowPU,
      Muon_RD_LowPUFile,ModeRD,AnaChannelMu);
  WmuPt_Muon_RD_LowPU.Loop();
***/  

//WpToMuNu========================================
  /***
  cout<<"WpToMuNu_S8===================="<<endl;
  TChain *TC_Muon_WpToMuNu_S8    = new TChain("WMuNeu/tree","");
  TChain *TC_Muon_WpToMuNu_S8_Mu = new TChain("Muons/tree","");
  SetupTree("Muon_WpToMuNu_S8",TC_Muon_WpToMuNu_S8);
  SetupTree("Muon_WpToMuNu_S8",TC_Muon_WpToMuNu_S8_Mu);
  TString Muon_WpToMuNuFile = "Muon_WpToMuNu_S8_"+ModeMC;
  WLepNeu WmuPt_WpMuNu(TC_Muon_WpToMuNu_S8,TC_Muon_WpToMuNu_S8_Mu,
  	LumiWeight_Muon_WpToMuNu_S8, Muon_WpToMuNuFile,ModeMC,AnaChannelMu);
  WmuPt_WpMuNu.Loop();
  ***/
  
//WmToMuNu========================================
  /***
  cout<<"WmToMuNu_S8========================"<<endl;
  TChain *TC_Muon_WmToMuNu_S8    = new TChain("WMuNeu/tree","");
  TChain *TC_Muon_WmToMuNu_S8_Mu = new TChain("Muons/tree","");
  SetupTree("Muon_WmToMuNu_S8",TC_Muon_WmToMuNu_S8);
  SetupTree("Muon_WmToMuNu_S8",TC_Muon_WmToMuNu_S8_Mu);
  TString Muon_WmToMuNuFile = "Muon_WmToMuNu_S8_"+ModeMC;
  WLepNeu WmuPt_WmMuNu(TC_Muon_WmToMuNu_S8,TC_Muon_WmToMuNu_S8_Mu,
  	LumiWeight_Muon_WmToMuNu_S8, Muon_WmToMuNuFile,ModeMC,AnaChannelMu);
  WmuPt_WmMuNu.Loop();
  ***/

//DYToMuMu========================================
  /***
  cout<<"DYToMuMu_S8========================="<<endl;
  TChain *TC_Muon_DYToMuMu_S8	= new TChain("WMuNeu/tree","");
  TChain *TC_Muon_DYToMuMu_S8_Mu	= new TChain("Muons/tree","");
  SetupTree("Muon_DYToMuMu_S8",TC_Muon_DYToMuMu_S8);
  SetupTree("Muon_DYToMuMu_S8",TC_Muon_DYToMuMu_S8_Mu);
  TString Muon_DYToMuMuFile = "Muon_DYToMuMu_S8_"+ModeMC;
  WLepNeu WPt_DYMuMu(TC_Muon_DYToMuMu_S8,TC_Muon_DYToMuMu_S8_Mu,
  	LumiWeight_Muon_DYToMuMu_S8, Muon_DYToMuMuFile,ModeMC,AnaChannelMu);
  WPt_DYMuMu.Loop();
  ***/

//WToTauNu======================================
  /***
  cout<<"WToTauNu_S8=========================="<<endl;
  TChain *TC_Muon_WToTauNu_S8	= new TChain("WMuNeu/tree","");
  TChain *TC_Muon_WToTauNu_S8_Mu	= new TChain("Muons/tree","");
  SetupTree("Muon_WToTauNu_S8",TC_Muon_WToTauNu_S8);
  SetupTree("Muon_WToTauNu_S8",TC_Muon_WToTauNu_S8_Mu);
  TString Muon_WToTauNuFile = "Muon_WToTauNu_S8_"+ModeMC;
  WLepNeu WPt_WToTauNu(TC_Muon_WToTauNu_S8,TC_Muon_WToTauNu_S8_Mu,
  	LumiWeight_Muon_WToTauNu_S8, Muon_WToTauNuFile,ModeMC,AnaChannelMu);
  WPt_WToTauNu.Loop();
  ***/

//DYToTauTau======================================
  /***
  cout<<"DYToTauTau_S8======================="<<endl;
  TChain *TC_Muon_DYToTauTau_S8	= new TChain("WMuNeu/tree","");
  TChain *TC_Muon_DYToTauTau_S8_Mu	= new TChain("Muons/tree","");
  SetupTree("Muon_DYToTauTau_S8",TC_Muon_DYToTauTau_S8);
  SetupTree("Muon_DYToTauTau_S8",TC_Muon_DYToTauTau_S8_Mu);
  TString Muon_DYToTauTauFile = "Muon_DYToTauTau_S8_"+ModeMC;
  WLepNeu WPt_DYTauTau(TC_Muon_DYToTauTau_S8,TC_Muon_DYToTauTau_S8_Mu,
  	LumiWeight_Muon_DYToTauTau_S8, Muon_DYToTauTauFile,ModeMC,AnaChannelMu);
  WPt_DYTauTau.Loop();
  ***/
  
//TTJets======================================
  /***
  cout<<"TTJets_S8==========================="<<endl;
  TChain *TC_Muon_TTJets_S8	= new TChain("WMuNeu/tree","");
  TChain *TC_Muon_TTJets_S8_Mu	= new TChain("Muons/tree","");
  SetupTree("Muon_TTJets_S8",TC_Muon_TTJets_S8);
  SetupTree("Muon_TTJets_S8",TC_Muon_TTJets_S8_Mu);
  TString Muon_TTJetsFile = "Muon_TTJets_S8_"+ModeMC;
  WLepNeu WPt_TTJets(TC_Muon_TTJets_S8,TC_Muon_TTJets_S8_Mu,
  	LumiWeight_Muon_TTJets_S8, Muon_TTJetsFile,ModeMC,AnaChannelMu);
  WPt_TTJets.Loop();
  ****/
// For Muon analysis: TO HERE
//*********************/

//=========================
/////////// Electron LowPU
//=========================
// For Electron analysis: use the lines FROM HERE
//Luminosity weight
//***
  double LumiWeight_Ele_DYToEE_S8= RealLumi*1*1871.0/3297045;
  double LumiWeight_Ele_DYToTauTau_S8= RealLumi*1*1510.0/1987776;
  double LumiWeight_Ele_WpToEleNu_S8= RealLumi*1*6702.0/2401905;
  double LumiWeight_Ele_WmToEleNu_S8= RealLumi*1*4697.0/2127666;
  double LumiWeight_Ele_WToTauNu_S8= RealLumi*1*9170.0/2133983;
  double LumiWeight_Ele_TTJets_S8= RealLumi*1*136.3/6736135;
// ***/

  double LumiWeight_Ele_RD_LowPU = 1;

  //Ele_RD_LowPU========================================
 //***
  cout<<"Ele_RD_LowPU===================="<<endl;
  TChain *TC_Ele_RD_LowPU    = new TChain("WEleNeu/tree","");
  TChain *TC_Ele_RD_LowPU_Ele = new TChain("Electrons/tree","");
  SetupTree("Ele_RD_LowPU",TC_Ele_RD_LowPU);
  SetupTree("Ele_RD_LowPU",TC_Ele_RD_LowPU_Ele);
  TString Ele_RD_LowPUFile = "Ele_RD_LowPU_"+ModeRD;
  WLepNeu WelePt_Ele_RD_LowPU(TC_Ele_RD_LowPU,TC_Ele_RD_LowPU_Ele,LumiWeight_Ele_RD_LowPU, Ele_RD_LowPUFile, ModeRD, AnaChannelEle);
  WelePt_Ele_RD_LowPU.Loop();
 //***/

  //***
  cout<<"Ele_WminusToEleNu_S8==========================="<<endl;
  TChain *TC_Ele_WmToEleNu_S8    = new TChain("WEleNeu/tree","");
  TChain *TC_Ele_WmToEleNu_S8_Ele = new TChain("Electrons/tree","");
  SetupTree("Ele_WmToEleNu_S8",TC_Ele_WmToEleNu_S8);
  SetupTree("Ele_WmToEleNu_S8",TC_Ele_WmToEleNu_S8_Ele);
  TString Ele_WmToEleNu_S8File = "Ele_WmToEleNu_S8_"+ModeMC;
  WLepNeu WelePt_Ele_WmToEleNu_S8(TC_Ele_WmToEleNu_S8,TC_Ele_WmToEleNu_S8_Ele,
  	LumiWeight_Ele_WmToEleNu_S8, Ele_WmToEleNu_S8File,ModeMC,AnaChannelEle);
  WelePt_Ele_WmToEleNu_S8.Loop();
  /***/

  //***
  cout<<"Ele_WplusToEleNu_S8==========================="<<endl;
  TChain *TC_Ele_WpToEleNu_S8    = new TChain("WEleNeu/tree","");
  TChain *TC_Ele_WpToEleNu_S8_Ele = new TChain("Electrons/tree","");
  SetupTree("Ele_WpToEleNu_S8",TC_Ele_WpToEleNu_S8);
  SetupTree("Ele_WpToEleNu_S8",TC_Ele_WpToEleNu_S8_Ele);
  TString Ele_WpToEleNu_S8File = "Ele_WpToEleNu_S8_"+ModeMC;
  WLepNeu WelePt_Ele_WpToEleNu_S8(TC_Ele_WpToEleNu_S8,TC_Ele_WpToEleNu_S8_Ele,
  	LumiWeight_Ele_WpToEleNu_S8, Ele_WpToEleNu_S8File,ModeMC,AnaChannelEle);
  WelePt_Ele_WpToEleNu_S8.Loop();
  /***/
  
  /***
  cout<<"Ele_DYToEE_S8==========================="<<endl;
  TChain *TC_Ele_DYToEE_S8    = new TChain("WEleNeu/tree","");
  TChain *TC_Ele_DYToEE_S8_Ele = new TChain("Electrons/tree","");
  SetupTree("Ele_DYToEE_S8",TC_Ele_DYToEE_S8);
  SetupTree("Ele_DYToEE_S8",TC_Ele_DYToEE_S8_Ele);
  TString Ele_DYToEE_S8File = "Ele_DYToEE_S8_"+ModeMC;
  WLepNeu WelePt_Ele_DYToEE_S8(TC_Ele_DYToEE_S8,TC_Ele_DYToEE_S8_Ele,
  	LumiWeight_Ele_DYToEE_S8, Ele_DYToEE_S8File,ModeMC,AnaChannelEle);
  WelePt_Ele_DYToEE_S8.Loop();
  ***/

  /***
  cout<<"Ele_DYToTauTau_S8==========================="<<endl;
  TChain *TC_Ele_DYToTauTau_S8    = new TChain("WEleNeu/tree","");
  TChain *TC_Ele_DYToTauTau_S8_Ele = new TChain("Electrons/tree","");
  SetupTree("Ele_DYToTauTau_S8",TC_Ele_DYToTauTau_S8);
  SetupTree("Ele_DYToTauTau_S8",TC_Ele_DYToTauTau_S8_Ele);
  TString Ele_DYToTauTau_S8File = "Ele_DYToTauTau_S8_"+ModeMC;
  WLepNeu WelePt_Ele_DYToTauTau_S8(TC_Ele_DYToTauTau_S8,TC_Ele_DYToTauTau_S8_Ele,
  	LumiWeight_Ele_DYToTauTau_S8, Ele_DYToTauTau_S8File,ModeMC,AnaChannelEle);
  WelePt_Ele_DYToTauTau_S8.Loop();
  ***/


  /***
  cout<<"Ele_WToTauNu_S8==========================="<<endl;
  TChain *TC_Ele_WToTauNu_S8    = new TChain("WEleNeu/tree","");
  TChain *TC_Ele_WToTauNu_S8_Ele = new TChain("Electrons/tree","");
  SetupTree("Ele_WToTauNu_S8",TC_Ele_WToTauNu_S8);
  SetupTree("Ele_WToTauNu_S8",TC_Ele_WToTauNu_S8_Ele);
  TString Ele_WToTauNu_S8File = "Ele_WToTauNu_S8_"+ModeMC;
  WLepNeu WelePt_Ele_WToTauNu_S8(TC_Ele_WToTauNu_S8,TC_Ele_WToTauNu_S8_Ele,
  	LumiWeight_Ele_WToTauNu_S8, Ele_WToTauNu_S8File,ModeMC,AnaChannelEle);
  WelePt_Ele_WToTauNu_S8.Loop();
  ***/

  /***
  cout<<"Ele_TTJets_S8==========================="<<endl;
  TChain *TC_Ele_TTJets_S8    = new TChain("WEleNeu/tree","");
  TChain *TC_Ele_TTJets_S8_Ele = new TChain("Electrons/tree","");
  SetupTree("Ele_TTJets_S8",TC_Ele_TTJets_S8);
  SetupTree("Ele_TTJets_S8",TC_Ele_TTJets_S8_Ele);
  TString Ele_TTJets_S8File = "Ele_TTJets_S8_"+ModeMC;
  WLepNeu WelePt_Ele_TTJets_S8(TC_Ele_TTJets_S8,TC_Ele_TTJets_S8_Ele,
  	LumiWeight_Ele_TTJets_S8, Ele_TTJets_S8File,ModeMC,AnaChannelEle);
  WelePt_Ele_TTJets_S8.Loop();
  ***/
// For Electron analysis: TO HERE
}
