//#include "../Utils/const.h"
//#include "../Utils/CPlot.hh"
//#include "../Utils/MitStyleRemix.hh"
#include <TSystem.h>	// gSystem
#include <iostream>
#include "../EventSelection/include/SetupTree.h"
#include "../EventSelection/WLepNeu.h"
using namespace std;
#define	RealLumi	(18.977) //pb
void scaleSmearMakeHisto(int Range)
{
//======================================
// choose Mode and AnaChannel here  !!!
//======================================
//  TString Mode = "Resolution";//Analysis,Recoil, RecoilMC, RecoilCorr, Resolution,
//  TString AnaChannel = "MuonLowPU"; //ElectronLowPU

  TString ModeMC = "ScaleMakeMC";//ScaleMakeRD,ScaleMakeMC,Analysis,Recoil, RecoilMC, RecoilCorr, Resolution,
  TString ModeRD = "ScaleMakeRD";//ScaleMakeRD,ScaleMakeMC,Analysis,Recoil, RecoilMC, RecoilCorr, Resolution,

  TString AnaChannelEle = "ElectronLowPU"; 
  TString AnaChannelMu  = "MuonLowPU";

  //gSystem->CompileMacro("../EventSelection/WLepNeu.C","k");
  cout<<"Range is "<<Range<<endl;
//====================
/////////// Muon LowPU
//====================
// For Muon analysis: use the lines FROM HERE
  //Luminosity weight
  //**
  double LumiWeight_Muon_WpToMuNu_S8 = RealLumi*1*6702.0/935446;
  double LumiWeight_Muon_WmToMuNu_S8 = RealLumi*1*4697.0/1.97346e6;
  double LumiWeight_Muon_DYToMuMu_S8 = RealLumi*1*1871.0/1.9802e6;
  double LumiWeight_Muon_WToTauNu_S8 = RealLumi*1*9170.0/2.13398e6;
  double LumiWeight_Muon_DYToTauTau_S8 = RealLumi*1*1510.0/1.98778e6;
  double LumiWeight_Muon_TTJets_S8 = RealLumi*1*136.3/6.73614e6;
  /***/

  /***
  double LumiWeight_Muon_WpToMuNu_S8	=1;
  double LumiWeight_Muon_WmToMuNu_S8	=1;
  double LumiWeight_Muon_DYToMuMu_S8	=1;
  double LumiWeight_Muon_WToTauNu_S8	=1;
  double LumiWeight_Muon_DYToTauTau_S8	=1;
  double LumiWeight_Muon_TTJets_S8	=1;
  ***/

  double LumiWeight_Muon_RD_LowPU = 1;

//RD==================================
  //***
  cout<<"RD===================="<<endl;
  TChain *TC_Muon_RD_LowPU    = new TChain("WMuNeu/tree","");
  TChain *TC_Muon_RD_LowPU_Mu = new TChain("Muons/tree","");
  SetupTree("Muon_RD_LowPU",TC_Muon_RD_LowPU);
  SetupTree("Muon_RD_LowPU",TC_Muon_RD_LowPU_Mu);
  TString Muon_RD_LowPUFile = "Muon_RD_LowPU_"+ModeRD;
  WLepNeu WmuPt_Muon_RD_LowPU(TC_Muon_RD_LowPU,TC_Muon_RD_LowPU_Mu,LumiWeight_Muon_RD_LowPU, Muon_RD_LowPUFile,ModeRD,AnaChannelMu,Range);
  WmuPt_Muon_RD_LowPU.Loop();
  //***/
 
//DYToMuMu========================================
 //***
  cout<<"DYToMuMu_S8========================="<<endl;
  TChain *TC_Muon_DYToMuMu_S8   = new TChain("WMuNeu/tree","");
  TChain *TC_Muon_DYToMuMu_S8_Mu        = new TChain("Muons/tree","");
  SetupTree("Muon_DYToMuMu_S8",TC_Muon_DYToMuMu_S8);
  SetupTree("Muon_DYToMuMu_S8",TC_Muon_DYToMuMu_S8_Mu);
  TString Muon_DYToMuMuFile = "Muon_DYToMuMu_S8_"+ModeMC;
  WLepNeu WPt_DYMuMu(TC_Muon_DYToMuMu_S8,TC_Muon_DYToMuMu_S8_Mu,
      LumiWeight_Muon_DYToMuMu_S8, Muon_DYToMuMuFile,ModeMC,AnaChannelMu,Range);
  WPt_DYMuMu.Loop();
 // ***/



//WpToMuNu========================================
  /***
  cout<<"WpToMuNu_S8===================="<<endl;
  TChain *TC_Muon_WpToMuNu_S8    = new TChain("WMuNeu/tree","");
  TChain *TC_Muon_WpToMuNu_S8_Mu = new TChain("Muons/tree","");
  SetupTree("Muon_WpToMuNu_S8",TC_Muon_WpToMuNu_S8);
  SetupTree("Muon_WpToMuNu_S8",TC_Muon_WpToMuNu_S8_Mu);
  TString Muon_WpToMuNuFile = "Muon_WpToMuNu_S8_"+Mode;
  WLepNeu WmuPt_WpMuNu(TC_Muon_WpToMuNu_S8,TC_Muon_WpToMuNu_S8_Mu,
  	LumiWeight_Muon_WpToMuNu_S8, Muon_WpToMuNuFile,Mode,AnaChannelMu);
  WmuPt_WpMuNu.Loop();
  ***/
  
//WmToMuNu========================================
  /***
  cout<<"WmToMuNu_S8========================"<<endl;
  TChain *TC_Muon_WmToMuNu_S8    = new TChain("WMuNeu/tree","");
  TChain *TC_Muon_WmToMuNu_S8_Mu = new TChain("Muons/tree","");
  SetupTree("Muon_WmToMuNu_S8",TC_Muon_WmToMuNu_S8);
  SetupTree("Muon_WmToMuNu_S8",TC_Muon_WmToMuNu_S8_Mu);
  TString Muon_WmToMuNuFile = "Muon_WmToMuNu_S8_"+Mode;
  WLepNeu WmuPt_WmMuNu(TC_Muon_WmToMuNu_S8,TC_Muon_WmToMuNu_S8_Mu,
  	LumiWeight_Muon_WmToMuNu_S8, Muon_WmToMuNuFile,Mode,AnaChannelMu);
  WmuPt_WmMuNu.Loop();
  ***/

//WToTauNu======================================
  /***
  cout<<"WToTauNu_S8=========================="<<endl;
  TChain *TC_Muon_WToTauNu_S8	= new TChain("WMuNeu/tree","");
  TChain *TC_Muon_WToTauNu_S8_Mu	= new TChain("Muons/tree","");
  SetupTree("Muon_WToTauNu_S8",TC_Muon_WToTauNu_S8);
  SetupTree("Muon_WToTauNu_S8",TC_Muon_WToTauNu_S8_Mu);
  TString Muon_WToTauNuFile = "Muon_WToTauNu_S8_"+Mode;
  WLepNeu WPt_WToTauNu(TC_Muon_WToTauNu_S8,TC_Muon_WToTauNu_S8_Mu,
  	LumiWeight_Muon_WToTauNu_S8, Muon_WToTauNuFile,Mode,AnaChannelMu);
  WPt_WToTauNu.Loop();
  ***/

//DYToTauTau======================================
  /***
  cout<<"DYToTauTau_S8======================="<<endl;
  TChain *TC_Muon_DYToTauTau_S8	= new TChain("WMuNeu/tree","");
  TChain *TC_Muon_DYToTauTau_S8_Mu	= new TChain("Muons/tree","");
  SetupTree("Muon_DYToTauTau_S8",TC_Muon_DYToTauTau_S8);
  SetupTree("Muon_DYToTauTau_S8",TC_Muon_DYToTauTau_S8_Mu);
  TString Muon_DYToTauTauFile = "Muon_DYToTauTau_S8_"+Mode;
  WLepNeu WPt_DYTauTau(TC_Muon_DYToTauTau_S8,TC_Muon_DYToTauTau_S8_Mu,
  	LumiWeight_Muon_DYToTauTau_S8, Muon_DYToTauTauFile,Mode,AnaChannelMu);
  WPt_DYTauTau.Loop();
  ***/
  
//TTJets======================================
  /***
  cout<<"TTJets_S8==========================="<<endl;
  TChain *TC_Muon_TTJets_S8	= new TChain("WMuNeu/tree","");
  TChain *TC_Muon_TTJets_S8_Mu	= new TChain("Muons/tree","");
  SetupTree("Muon_TTJets_S8",TC_Muon_TTJets_S8);
  SetupTree("Muon_TTJets_S8",TC_Muon_TTJets_S8_Mu);
  TString Muon_TTJetsFile = "Muon_TTJets_S8_"+Mode;
  WLepNeu WPt_TTJets(TC_Muon_TTJets_S8,TC_Muon_TTJets_S8_Mu,
  	LumiWeight_Muon_TTJets_S8, Muon_TTJetsFile,Mode,AnaChannelMu);
  WPt_TTJets.Loop();
  ***/
// For Muon analysis: TO HERE

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
  /***/
  /***
  double LumiWeight_Ele_DYToEE_S8	= 1;
  double LumiWeight_Ele_DYToTauTau_S8	= 1;
  double LumiWeight_Ele_WpToEleNu_S8	= 1;
  double LumiWeight_Ele_WmToEleNu_S8	= 1;
  double LumiWeight_Ele_WToTauNu_S8	= 1;
  double LumiWeight_Ele_TTJets_S8	= 1;
  ***/

  double LumiWeight_Ele_RD_LowPU = 1;

  //Ele_RD_LowPU========================================
 /***
  cout<<"Ele_RD_LowPU===================="<<endl;
  TChain *TC_Ele_RD_LowPU    = new TChain("WEleNeu/tree","");
  TChain *TC_Ele_RD_LowPU_Ele = new TChain("Electrons/tree","");
  SetupTree("Ele_RD_LowPU",TC_Ele_RD_LowPU);
  SetupTree("Ele_RD_LowPU",TC_Ele_RD_LowPU_Ele);
  TString Ele_RD_LowPUFile = "Ele_RD_LowPU_"+ModeRD;
  WLepNeu WelePt_Ele_RD_LowPU(
      TC_Ele_RD_LowPU,TC_Ele_RD_LowPU_Ele,LumiWeight_Ele_RD_LowPU, Ele_RD_LowPUFile,
      ModeRD, AnaChannelEle,Range);
  WelePt_Ele_RD_LowPU.Loop();
  /***/

 /***
  cout<<"Ele_DYToEE_S8==========================="<<endl;
  TChain *TC_Ele_DYToEE_S8    = new TChain("WEleNeu/tree","");
  TChain *TC_Ele_DYToEE_S8_Ele = new TChain("Electrons/tree","");
  SetupTree("Ele_DYToEE_S8",TC_Ele_DYToEE_S8);
  SetupTree("Ele_DYToEE_S8",TC_Ele_DYToEE_S8_Ele);
  TString Ele_DYToEE_S8File = "Ele_DYToEE_S8_"+ModeMC;
  WLepNeu WelePt_Ele_DYToEE_S8(
      TC_Ele_DYToEE_S8,TC_Ele_DYToEE_S8_Ele,LumiWeight_Ele_DYToEE_S8,Ele_DYToEE_S8File,
      ModeMC,AnaChannelEle,Range);
  WelePt_Ele_DYToEE_S8.Loop();
  /***/

  /***
  cout<<"Ele_DYToTauTau_S8==========================="<<endl;
  TChain *TC_Ele_DYToTauTau_S8    = new TChain("WEleNeu/tree","");
  TChain *TC_Ele_DYToTauTau_S8_Ele = new TChain("Electrons/tree","");
  SetupTree("Ele_DYToTauTau_S8",TC_Ele_DYToTauTau_S8);
  SetupTree("Ele_DYToTauTau_S8",TC_Ele_DYToTauTau_S8_Ele);
  TString Ele_DYToTauTau_S8File = "Ele_DYToTauTau_S8_"+Mode;
  WLepNeu WelePt_Ele_DYToTauTau_S8(TC_Ele_DYToTauTau_S8,TC_Ele_DYToTauTau_S8_Ele,
  	LumiWeight_Ele_DYToTauTau_S8, Ele_DYToTauTau_S8File,Mode,AnaChannelEle);
  WelePt_Ele_DYToTauTau_S8.Loop();
  ***/

  /***
  cout<<"Ele_WminusToEleNu_S8==========================="<<endl;
  TChain *TC_Ele_WmToEleNu_S8    = new TChain("WEleNeu/tree","");
  TChain *TC_Ele_WmToEleNu_S8_Ele = new TChain("Electrons/tree","");
  SetupTree("Ele_WmToEleNu_S8",TC_Ele_WmToEleNu_S8);
  SetupTree("Ele_WmToEleNu_S8",TC_Ele_WmToEleNu_S8_Ele);
  TString Ele_WmToEleNu_S8File = "Ele_WmToEleNu_S8_"+Mode;
  WLepNeu WelePt_Ele_WmToEleNu_S8(TC_Ele_WmToEleNu_S8,TC_Ele_WmToEleNu_S8_Ele,
  	LumiWeight_Ele_WmToEleNu_S8, Ele_WmToEleNu_S8File,Mode,AnaChannelEle);
  WelePt_Ele_WmToEleNu_S8.Loop();
  ***/

  /***
  cout<<"Ele_WplusToEleNu_S8==========================="<<endl;
  TChain *TC_Ele_WpToEleNu_S8    = new TChain("WEleNeu/tree","");
  TChain *TC_Ele_WpToEleNu_S8_Ele = new TChain("Electrons/tree","");
  SetupTree("Ele_WpToEleNu_S8",TC_Ele_WpToEleNu_S8);
  SetupTree("Ele_WpToEleNu_S8",TC_Ele_WpToEleNu_S8_Ele);
  TString Ele_WpToEleNu_S8File = "Ele_WpToEleNu_S8_"+Mode;
  WLepNeu WelePt_Ele_WpToEleNu_S8(TC_Ele_WpToEleNu_S8,TC_Ele_WpToEleNu_S8_Ele,
  	LumiWeight_Ele_WpToEleNu_S8, Ele_WpToEleNu_S8File,Mode,AnaChannelEle);
  WelePt_Ele_WpToEleNu_S8.Loop();
  ***/

  /***
  cout<<"Ele_WToTauNu_S8==========================="<<endl;
  TChain *TC_Ele_WToTauNu_S8    = new TChain("WEleNeu/tree","");
  TChain *TC_Ele_WToTauNu_S8_Ele = new TChain("Electrons/tree","");
  SetupTree("Ele_WToTauNu_S8",TC_Ele_WToTauNu_S8);
  SetupTree("Ele_WToTauNu_S8",TC_Ele_WToTauNu_S8_Ele);
  TString Ele_WToTauNu_S8File = "Ele_WToTauNu_S8_"+Mode;
  WLepNeu WelePt_Ele_WToTauNu_S8(TC_Ele_WToTauNu_S8,TC_Ele_WToTauNu_S8_Ele,
  	LumiWeight_Ele_WToTauNu_S8, Ele_WToTauNu_S8File,Mode,AnaChannelEle);
  WelePt_Ele_WToTauNu_S8.Loop();
  ***/

  /***
  cout<<"Ele_TTJets_S8==========================="<<endl;
  TChain *TC_Ele_TTJets_S8    = new TChain("WEleNeu/tree","");
  TChain *TC_Ele_TTJets_S8_Ele = new TChain("Electrons/tree","");
  SetupTree("Ele_TTJets_S8",TC_Ele_TTJets_S8);
  SetupTree("Ele_TTJets_S8",TC_Ele_TTJets_S8_Ele);
  TString Ele_TTJets_S8File = "Ele_TTJets_S8_"+Mode;
  WLepNeu WelePt_Ele_TTJets_S8(TC_Ele_TTJets_S8,TC_Ele_TTJets_S8_Ele,
  	LumiWeight_Ele_TTJets_S8, Ele_TTJets_S8File,Mode,AnaChannelEle);
  WelePt_Ele_TTJets_S8.Loop();
  ***/
// For Electron analysis: TO HERE
}
