#include <iostream>
#include "TSystem.h"
#include "../EventSelection/include/Tree2012LoPU/SetupTreeAccept.h"
#include "../Utils/const.h"

#define	RealLumi	(18.977) //pb

using namespace std;

void wAcceptMakeHisto()
{
//======================================
// choose Mode and AnaChannel here  !!!
//======================================
//  TString Mode = "Unfold";//Analysis,Recoil, RecoilMC, RecoilCorr, Unfold,
//  TString AnaChannel = "MuonLowPU"; //ElectronLowPU

TString ModeMC = "Acceptance";//Analysis,Recoil, RecoilMC, RecoilCorr, Unfold,
TString AnaChannelEle = "Electron2012LoPU"; 
TString AnaChannelMu  = "Muon2012LoPU";

  gSystem->CompileMacro("../EventSelection/Wlnu12LoNT.C","k");
  gSystem->CompileMacro("../EventSelection/Wlnu12LoBase.C","k");
  gSystem->CompileMacro("../EventSelection/Wlnu12LoMET.C","k");
//====================
/////////// Muon LowPU
//====================
// For Muon analysis: use the lines FROM HERE
  //Luminosity weight   N = sigma * L, L = N/Sigma
  //double LumiWeight_Muon_WpToMuNu_S8 = RealLumi*1*7322.0/935446;
  //double LumiWeight_Muon_WmToMuNu_S8 = RealLumi*1*5181.0/1.97346e6;
  //double LumiWeight_Muon_WpToMuNu_S8 = RealLumi*1*6702.0/935446;
  //double LumiWeight_Muon_WmToMuNu_S8 = RealLumi*1*4697.0/1.97346e6;
  //double LumiWeight_Muon_DYToMuMu_S8 = RealLumi*1*1871.0/1.9802e6;
  //double LumiWeight_Muon_WToTauNu_S8 = RealLumi*1*9170.0/2.13398e6;
  //double LumiWeight_Muon_DYToTauTau_S8 = RealLumi*1*1510.0/1.98778e6;
  //double LumiWeight_Muon_TTJets_S8 = RealLumi*1*136.3/6.73614e6;

  //LumiWeight_Muon_WmToMuNu_S8/=LumiWeight_Muon_WpToMuNu_S8;
  //LumiWeight_Muon_WpToMuNu_S8 = 1;
  //LumiWeight_Muon_WmToMuNu_S8 = 1;

  double LumiWeight_Muon_WmToMuNu_S8 = Lumi_LowPU*1*4697.0/1.97346e6;
  double LumiWeight_Muon_WpToMuNu_S8 = Lumi_LowPU*1*6702.0/935446;
  double LumiW_Muon_DYToMuMu_S8 = Lumi_LowPU*1*1871.0/1.9802e6;
  double LumiW_Muon_WToTauNu_S8 = Lumi_LowPU*1*9170.0/2.13398e6;
  double LumiW_Muon_DYToTauTau_S8 = Lumi_LowPU*1*1510.0/1.98778e6;
  double LumiW_Muon_TTJets_S8 = Lumi_LowPU*1*136.3/6.73614e6;
  double LumiW_WpToMuNu = LumiWeight_Muon_WpToMuNu_S8;
  double LumiW_WmToMuNu = LumiWeight_Muon_WmToMuNu_S8;
  double LumiW_Muon_RD_LowPU = 1;
  /***
  double LumiWeight_Muon_WpToMuNu_S8	=1;
  double LumiWeight_Muon_WmToMuNu_S8	=1;
  double LumiWeight_Muon_DYToMuMu_S8	=1;
  double LumiWeight_Muon_WToTauNu_S8	=1;
  double LumiWeight_Muon_DYToTauTau_S8	=1;
  double LumiWeight_Muon_TTJets_S8	=1;
  ***/

////WpToMuNu========================================
//  cout<<"WpToMuNu_S8===================="<<endl;
//  TChain *TC_WpToMuNu_S8    = new TChain("WAcceptanceMuon/tree","");
//  SetupTreeAccept("Muon_WpToMuNu_S8",TC_WpToMuNu_S8);
//  TString WpToMuNu_BaseName = "WpToMuNu_S8";
//  Wlnu12LoMET Wmunu12LoWpMuNu(
//      TC_WpToMuNu_S8,LumiW_WpToMuNu, WpToMuNu_BaseName,ModeMC,AnaChannelMu,1,true,0x1234);
//  Wmunu12LoWpMuNu.Loop();
//
//WmToMuNu========================================
  cout<<"WmToMuNu_S8===================="<<endl;
  TChain *TC_WmToMuNu_S8    = new TChain("WAcceptanceMuon/tree","");
  SetupTreeAccept("Muon_WmToMuNu_S8",TC_WmToMuNu_S8);
  TString WmToMuNu_BaseName = "WmToMuNu_S8";
  Wlnu12LoMET Wmunu12LoWmMuNu(
      TC_WmToMuNu_S8,LumiW_WmToMuNu, WmToMuNu_BaseName,ModeMC,AnaChannelMu,-1,true,1234);
  Wmunu12LoWmMuNu.Loop();

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
  //double LumiWeight_Ele_WpToEleNu_S8= RealLumi*1*7322.0/2401905;
  //double LumiWeight_Ele_WmToEleNu_S8= RealLumi*1*5181.0/2127666;
  double LumiWeight_Ele_WpToEleNu_S8= RealLumi*1*6702.0/2401905;
  double LumiWeight_Ele_WmToEleNu_S8= RealLumi*1*4697.0/2127666;
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

//WpToEleNu========================================
  cout<<"WpToEleNu_S8===================="<<endl;
  TChain *TC_WpToEleNu_S8    = new TChain("WAcceptanceElectron/tree","");
  SetupTreeAccept("Ele_WpToEleNu_S8",TC_WpToEleNu_S8);
  TString WpToEleNu_BaseName = "WpToEleNu_S8";
  Wlnu12LoMET Wenu12LoWpEleNu(
      TC_WpToEleNu_S8,LumiW_WpToEleNu, WpToEleNu_BaseName,ModeMC,AnaChannelEle,1,true,1234);
  Wenu12LoWpEleNu.Loop();
//WmToEleNu========================================
  cout<<"WmToEleNu_S8===================="<<endl;
  TChain *TC_WmToEleNu_S8    = new TChain("WAcceptanceElectron/tree","");
  SetupTreeAccept("Ele_WmToEleNu_S8",TC_WmToEleNu_S8);
  TString WmToEleNu_BaseName = "WmToEleNu_S8";
  Wlnu12LoMET Wenu12LoWmEleNu(
      TC_WmToEleNu_S8,LumiW_WmToEleNu, WmToEleNu_BaseName,ModeMC,AnaChannelEle,-1,true,1234);
  Wenu12LoWmEleNu.Loop();
//  ***/
// For Electron analysis: TO HERE
}
