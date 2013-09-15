#include <iostream>
#include "../EventSelection/include/SetupTreeAccept.h"

#define	RealLumi	(18.977) //pb

using namespace std;

void wAcceptMakeHisto()
{
//======================================
// choose Mode and AnaChannel here  !!!
//======================================
//  TString Mode = "Unfold";//Analysis,Recoil, RecoilMC, RecoilCorr, Unfold,
//  TString AnaChannel = "MuonLowPU"; //ElectronLowPU

TString Mode = "Acceptance";//Analysis,Recoil, RecoilMC, RecoilCorr, Unfold,
TString AnaChannelEle = "ElectronLowPU"; 
TString AnaChannelMu  = "MuonLowPU";

  gSystem->CompileMacro("../EventSelection/WLepNeu.C","k");
//====================
/////////// Muon LowPU
//====================
// For Muon analysis: use the lines FROM HERE
  //Luminosity weight   N = sigma * L, L = N/Sigma
  double LumiWeight_Muon_WpToMuNu_S8 = RealLumi*1*7322.0/935446;
  double LumiWeight_Muon_WmToMuNu_S8 = RealLumi*1*5181.0/1.97346e6;
  //double LumiWeight_Muon_WpToMuNu_S8 = RealLumi*1*6702.0/935446;
  //double LumiWeight_Muon_WmToMuNu_S8 = RealLumi*1*4697.0/1.97346e6;
  double LumiWeight_Muon_DYToMuMu_S8 = RealLumi*1*1871.0/1.9802e6;
  double LumiWeight_Muon_WToTauNu_S8 = RealLumi*1*9170.0/2.13398e6;
  double LumiWeight_Muon_DYToTauTau_S8 = RealLumi*1*1510.0/1.98778e6;
  double LumiWeight_Muon_TTJets_S8 = RealLumi*1*136.3/6.73614e6;

  LumiWeight_Muon_WmToMuNu_S8/=LumiWeight_Muon_WpToMuNu_S8;
  LumiWeight_Muon_WpToMuNu_S8 = 1;
  LumiWeight_Muon_WmToMuNu_S8 = 1;

  /***
  double LumiWeight_Muon_WpToMuNu_S8	=1;
  double LumiWeight_Muon_WmToMuNu_S8	=1;
  double LumiWeight_Muon_DYToMuMu_S8	=1;
  double LumiWeight_Muon_WToTauNu_S8	=1;
  double LumiWeight_Muon_DYToTauTau_S8	=1;
  double LumiWeight_Muon_TTJets_S8	=1;
  ***/

//WpToMuNu========================================
//***
  cout<<"WpToMuNu_S8===================="<<endl;
  TChain *TC_Muon_WpToMuNu_S8    = new TChain("WAcceptance/tree","");
  TChain *TC_Muon_WpToMuNu_S8_Mu = new TChain("Muons/tree","");
  SetupTreeAccept("Muon_WpToMuNu_S8",TC_Muon_WpToMuNu_S8);
  SetupTreeAccept("Muon_WpToMuNu_S8",TC_Muon_WpToMuNu_S8_Mu);
  TString Muon_WpToMuNuFile = "Muon_WpToMuNu_S8_"+Mode;
  WLepNeu WPt_WpMuNu(TC_Muon_WpToMuNu_S8,TC_Muon_WpToMuNu_S8_Mu,
  	LumiWeight_Muon_WpToMuNu_S8, Muon_WpToMuNuFile,Mode,AnaChannelMu);
  WPt_WpMuNu.Loop();
 //***/ 
//WmToMuNu========================================
  cout<<"WmToMuNu_S8========================"<<endl;
  TChain *TC_Muon_WmToMuNu_S8    = new TChain("WAcceptance/tree","");
  TChain *TC_Muon_WmToMuNu_S8_Mu = new TChain("Muons/tree","");
  SetupTreeAccept("Muon_WmToMuNu_S8",TC_Muon_WmToMuNu_S8);
  SetupTreeAccept("Muon_WmToMuNu_S8",TC_Muon_WmToMuNu_S8_Mu);
  TString Muon_WmToMuNuFile = "Muon_WmToMuNu_S8_"+Mode;
  WLepNeu WPt_WmMuNu(TC_Muon_WmToMuNu_S8,TC_Muon_WmToMuNu_S8_Mu,
  	LumiWeight_Muon_WmToMuNu_S8, Muon_WmToMuNuFile,Mode,AnaChannelMu);
  WPt_WmMuNu.Loop();
//***/

// For Muon analysis: TO HERE

//=========================
/////////// Electron LowPU
//=========================
// For Electron analysis: use the lines FROM HERE
//Luminosity weight
//***
  double LumiWeight_Ele_DYToEE_S8= RealLumi*1*1871.0/3297045;
  double LumiWeight_Ele_DYToTauTau_S8= RealLumi*1*1510.0/1987776;
  double LumiWeight_Ele_WpToEleNu_S8= RealLumi*1*7322.0/2401905;
  double LumiWeight_Ele_WmToEleNu_S8= RealLumi*1*5181.0/2127666;
  //double LumiWeight_Ele_WpToEleNu_S8= RealLumi*1*6702.0/2401905;
  //double LumiWeight_Ele_WmToEleNu_S8= RealLumi*1*4697.0/2127666;
  double LumiWeight_Ele_WToTauNu_S8= RealLumi*1*9170.0/2133983;
  double LumiWeight_Ele_TTJets_S8= RealLumi*1*136.3/6736135;
  LumiWeight_Ele_WmToEleNu_S8 /= LumiWeight_Ele_WpToEleNu_S8;
  LumiWeight_Ele_WpToEleNu_S8= 1;
  LumiWeight_Ele_WmToEleNu_S8= 1;
 //***/
/***
  double LumiWeight_Ele_DYToEE_S8	= 1;
  double LumiWeight_Ele_DYToTauTau_S8	= 1;
  double LumiWeight_Ele_WpToEleNu_S8	= 1;
  double LumiWeight_Ele_WmToEleNu_S8	= 1;
  double LumiWeight_Ele_WToTauNu_S8	= 1;
  double LumiWeight_Ele_TTJets_S8	= 1;
***/

  double LumiWeight_Ele_RD_LowPU = 1;

  //***
  cout<<"Ele_WminusToEleNu_S8==========================="<<endl;
  TChain *TC_Ele_WmToEleNu_S8    = new TChain("WAcceptance/tree","");
  TChain *TC_Ele_WmToEleNu_S8_Ele = new TChain("Electrons/tree","");
  SetupTreeAccept("Ele_WmToEleNu_S8",TC_Ele_WmToEleNu_S8);
  SetupTreeAccept("Ele_WmToEleNu_S8",TC_Ele_WmToEleNu_S8_Ele);
  TString Ele_WmToEleNu_S8File = "Ele_WmToEleNu_S8_"+Mode;
  WLepNeu Wpt_WmToEleNu_S8(TC_Ele_WmToEleNu_S8,TC_Ele_WmToEleNu_S8_Ele,
  	LumiWeight_Ele_WmToEleNu_S8, Ele_WmToEleNu_S8File,Mode,AnaChannelEle);
  Wpt_WmToEleNu_S8.Loop();
  //***/

  //***
  cout<<"Ele_WplusToEleNu_S8==========================="<<endl;
  TChain *TC_Ele_WpToEleNu_S8    = new TChain("WAcceptance/tree","");
  TChain *TC_Ele_WpToEleNu_S8_Ele = new TChain("Electrons/tree","");
  SetupTreeAccept("Ele_WpToEleNu_S8",TC_Ele_WpToEleNu_S8);
  SetupTreeAccept("Ele_WpToEleNu_S8",TC_Ele_WpToEleNu_S8_Ele);
  TString Ele_WpToEleNu_S8File = "Ele_WpToEleNu_S8_"+Mode;
  WLepNeu WPt_WpToEleNu_S8(TC_Ele_WpToEleNu_S8,TC_Ele_WpToEleNu_S8_Ele,
  	LumiWeight_Ele_WpToEleNu_S8, Ele_WpToEleNu_S8File,Mode,AnaChannelEle);
  WPt_WpToEleNu_S8.Loop();
  //***/
// For Electron analysis: TO HERE
}
