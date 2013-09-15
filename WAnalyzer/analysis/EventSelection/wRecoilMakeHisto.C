#include <iostream>
#include "include/SetupTree.h"
using namespace std;
#define	RealLumi	(18.977) //pb
void wRecoilMakeHisto()
{
  //Luminosity weight
/****
 //Luminosity weight
  double LumiWeight_Muon_WpToMuNu_S8 = RealLumi*1*6702.0/935446;
  double LumiWeight_Muon_WmToMuNu_S8 = RealLumi*1*4697.0/1.97346e6;
  double LumiWeight_Muon_DYToMuMu_S8 = RealLumi*1*1871.0/1.9802e6;
  double LumiWeight_Muon_WToTauNu_S8 = RealLumi*1*9170.0/2.13398e6;
  double LumiWeight_Muon_DYToTauTau_S8 = RealLumi*1*1510.0/1.98778e6;
  double LumiWeight_Muon_TTJets_S8 = RealLumi*1*136.3/6.73614e6;
****/
  double LumiWeight_Muon_WpToMuNu_S8 = 1;
  double LumiWeight_Muon_WmToMuNu_S8 = 1;
  double LumiWeight_Muon_DYToMuMu_S8 = 1;
  double LumiWeight_Muon_RD_LowPU = 1;

  //AutoLibraryLoader::enable();
// gSystem->CompileMacro("WMuNeu.C","k");
 gSystem->CompileMacro("WLepNeu.C","k");
  //TChain *TC_SingleMu_LowPU = new TChain("WMuNeu/tree","");
  //SetupTree("SingleMu_LowPU",TC_SingleMu_LowPU);

/***********
//Muon RD========================================
  TChain *TC_Muon_RD_LowPU    = new TChain("WMuNeu/tree","");
  TChain *TC_Muon_RD_LowPU_Mu = new TChain("Muons/tree","");
  SetupTree("Muon_RD_LowPU",TC_Muon_RD_LowPU);
  SetupTree("Muon_RD_LowPU",TC_Muon_RD_LowPU_Mu);
  TString Muon_RD_LowPUFile = "RDRecoil";
  WLepNeu WPt_Muon_RD_LowPU(TC_Muon_RD_LowPU,TC_Muon_RD_LowPU_Mu,LumiWeight_Muon_RD_LowPU, Muon_RD_LowPUFile,"RecoilRD","MuonLowPU");
  WPt_Muon_RD_LowPU.Loop();

//WpToMuNu========================================
  cout<<"WpToMuNu_S8===================="<<endl;
  TChain *TC_Muon_WpToMuNu_S8    = new TChain("WMuNeu/tree","");
  TChain *TC_Muon_WpToMuNu_S8_Mu = new TChain("Muons/tree","");
  SetupTree("Muon_WpToMuNu_S8",TC_Muon_WpToMuNu_S8);
  SetupTree("Muon_WpToMuNu_S8",TC_Muon_WpToMuNu_S8_Mu);
  TString Muon_WpToMuNuFile = "WpToMuNuRecoil";
  WLepNeu WPt_WpMuNu(TC_Muon_WpToMuNu_S8,TC_Muon_WpToMuNu_S8_Mu,
        LumiWeight_Muon_WpToMuNu_S8, Muon_WpToMuNuFile,"RecoilMC", "MuonLowPU");
  WPt_WpMuNu.Loop();

//WmToMuNu========================================
  TChain *TC_Muon_WmToMuNu_S8    = new TChain("WMuNeu/tree","");
  TChain *TC_Muon_WmToMuNu_S8_Mu = new TChain("Muons/tree","");
  SetupTree("Muon_WmToMuNu_S8",TC_Muon_WmToMuNu_S8);
  SetupTree("Muon_WmToMuNu_S8",TC_Muon_WmToMuNu_S8_Mu);
  TString Muon_WmToMuNuFile = "WmToMuNuRecoil";
  WLepNeu WPt_WmMuNu(TC_Muon_WmToMuNu_S8,TC_Muon_WmToMuNu_S8_Mu,
        LumiWeight_Muon_WmToMuNu_S8, Muon_WmToMuNuFile,"RecoilMC","MuonLowPU");
  WPt_WmMuNu.Loop();

//DYToMuMu========================================
  cout<<"DYToMuMu_S8========================="<<endl;
  TChain *TC_Muon_DYToMuMu_S8   = new TChain("WMuNeu/tree","");
  TChain *TC_Muon_DYToMuMu_S8_Mu        = new TChain("Muons/tree","");
  SetupTree("Muon_DYToMuMu_S8",TC_Muon_DYToMuMu_S8);
  SetupTree("Muon_DYToMuMu_S8",TC_Muon_DYToMuMu_S8_Mu);
  TString Muon_DYToMuMuFile = "DYToMuMuRecoil";
  WLepNeu WPt_DYMuMu(TC_Muon_DYToMuMu_S8,TC_Muon_DYToMuMu_S8_Mu,
        LumiWeight_Muon_DYToMuMu_S8, Muon_DYToMuMuFile,"RecoilMC","MuonLowPU");
  WPt_DYMuMu.Loop();
***********/
/////////// Electron LowPU

//*************

//Luminosity weight
  double LumiWeight_Ele_DYToEE_S8= 1;
  double LumiWeight_Ele_WpToEleNu_S8= 1;
  double LumiWeight_Ele_WmToEleNu_S8= 1;
  double LumiWeight_Ele_RD_LowPU = 1;

  //Ele_RD_LowPU========================================
  cout<<"Ele_RD_LowPU===================="<<endl;
  TChain *TC_Ele_RD_LowPU    = new TChain("WEleNeu/tree","");
  TChain *TC_Ele_RD_LowPU_Ele = new TChain("Electrons/tree","");
  SetupTree("Ele_RD_LowPU",TC_Ele_RD_LowPU);
  SetupTree("Ele_RD_LowPU",TC_Ele_RD_LowPU_Ele);
  TString Ele_RD_LowPUFile = "Ele_RD_LowPU_Recoil";
  WLepNeu WelePt_Ele_RD_LowPU(TC_Ele_RD_LowPU,TC_Ele_RD_LowPU_Ele,LumiWeight_Ele_RD_LowPU, Ele_RD_LowPUFile,"RecoilRD","ElectronLowPU");
  WelePt_Ele_RD_LowPU.Loop();

  cout<<"Ele_DYToEE_S8==========================="<<endl;
  TChain *TC_Ele_DYToEE_S8    = new TChain("WEleNeu/tree","");
  TChain *TC_Ele_DYToEE_S8_Ele = new TChain("Electrons/tree","");
  SetupTree("Ele_DYToEE_S8",TC_Ele_DYToEE_S8);
  SetupTree("Ele_DYToEE_S8",TC_Ele_DYToEE_S8_Ele);
  TString Ele_DYToEE_S8File = "Ele_DYToEE_S8_Recoil";
  WLepNeu WelePt_Ele_DYToEE_S8(TC_Ele_DYToEE_S8,TC_Ele_DYToEE_S8_Ele,LumiWeight_Ele_DYToEE_S8, Ele_DYToEE_S8File,"RecoilMC","ElectronLowPU");
  WelePt_Ele_DYToEE_S8.Loop();

  cout<<"Ele_WminusToEleNu_S8==========================="<<endl;
  TChain *TC_Ele_WmToEleNu_S8    = new TChain("WEleNeu/tree","");
  TChain *TC_Ele_WmToEleNu_S8_Ele = new TChain("Electrons/tree","");
  SetupTree("Ele_WmToEleNu_S8",TC_Ele_WmToEleNu_S8);
  SetupTree("Ele_WmToEleNu_S8",TC_Ele_WmToEleNu_S8_Ele);
  TString Ele_WmToEleNu_S8File = "Ele_WmEleNu_S8_Recoil";
  WLepNeu WelePt_Ele_WmToEleNu_S8(TC_Ele_WmToEleNu_S8,TC_Ele_WmToEleNu_S8_Ele,LumiWeight_Ele_WmToEleNu_S8, Ele_WmToEleNu_S8File,"RecoilMC","ElectronLowPU");
  WelePt_Ele_WmToEleNu_S8.Loop();


  cout<<"Ele_WplusToEleNu_S8==========================="<<endl;
  TChain *TC_Ele_WpToEleNu_S8    = new TChain("WEleNeu/tree","");
  TChain *TC_Ele_WpToEleNu_S8_Ele = new TChain("Electrons/tree","");
  SetupTree("Ele_WpToEleNu_S8",TC_Ele_WpToEleNu_S8);
  SetupTree("Ele_WpToEleNu_S8",TC_Ele_WpToEleNu_S8_Ele);
  TString Ele_WpToEleNu_S8File = "Ele_WpEleNu_S8_Recoil";
  WLepNeu WelePt_Ele_WpToEleNu_S8(TC_Ele_WpToEleNu_S8,TC_Ele_WpToEleNu_S8_Ele,LumiWeight_Ele_WpToEleNu_S8, Ele_WpToEleNu_S8File,"RecoilMC","ElectronLowPU");
  WelePt_Ele_WpToEleNu_S8.Loop();
/*********/
}
