#include "TSystem.h"
#include <iostream>
#include "../EventSelection/include/Tree2012LoPU/SetupTree.h"
#include "../Utils/const.h"
#define	RealLumi	(18.977) //pb
//#include "../EventSelection/WpT.h"

using namespace std;

//using namespace ROOT::Math;
void WPtMEtMakeHisto()
{
//======================================
// choose Mode and AnaChannel here  !!!
//======================================
//  TString AnaChannel = "MuonLowPU"; //ElectronLowPU

  TString ModeMC = "Unfold";//Analysis,Recoil, RecoilEvaMC,RecoilEvaRD, RecoilCorr, Unfold,DumpUnfInfo
  TString ModeRD = "Unfold";//Analysis,Recoil, RecoilEvaMC,RecoilEvaRD, RecoilCorr, Unfold,DumpUnfInfo
  TString AnaChannelEle = "Electron2012LoPU"; 
  TString AnaChannelMu  = "Muon2012LoPU";

  //gSystem->Load("libMathCore");
  //gSystem->Load("libPhysics");

  gSystem->CompileMacro("../EventSelection/Wlnu12LoNT.C","k");
  gSystem->CompileMacro("../EventSelection/Wlnu12LoBase.C","k");
  gSystem->CompileMacro("../EventSelection/Wlnu12LoMET.C","k");

//====================
/////////// Muon LowPU
//====================
// For Muon analysis: use the lines FROM HERE
  //Luminosity weight
  //double LumiWeight_Muon_WmToMuNu_S8 = Lumi_LowPU*1*4697.0/1.97346e6;
  //double LumiWeight_Muon_WpToMuNu_S8 = Lumi_LowPU*1*6702.0/935446;
  //double LumiW_Muon_DYToMuMu_S8 = Lumi_LowPU*1*1871.0/1.9802e6;
  //double LumiW_Muon_WToTauNu_S8 = Lumi_LowPU*1*9170.0/2.13398e6;
  //double LumiW_Muon_DYToTauTau_S8 = Lumi_LowPU*1*1510.0/1.98778e6;
  //double LumiW_Muon_TTJets_S8 = Lumi_LowPU*1*136.3/6.73614e6;
  //double LumiW_WpToMuNu = LumiWeight_Muon_WpToMuNu_S8;
  //double LumiW_WmToMuNu = LumiWeight_Muon_WmToMuNu_S8;
  //double LumiW_Muon_RD_LowPU = 1;

  //Luminosity weight
  double LumiW_WpToMuNu = LumiWeight_Muon_WpToMuNu_S8;
  double LumiW_WmToMuNu = LumiWeight_Muon_WmToMuNu_S8;
  //double LumiWeight_Muon_WpToMuNu_S8 = RealLumi*1*6702.0/935446;
  //double LumiWeight_Muon_WmToMuNu_S8 = RealLumi*1*4697.0/1.97346e6;
  LumiW_WpToMuNu = 1;
  LumiW_WmToMuNu = 1;
  
//WpToMuNu========================================
  cout<<"WpToMuNu_S8===================="<<endl;
  TChain *TC_WpToMuNu_S8    = new TChain("WMuNeu/tree","");
  TChain *TC_WpToMuNu_S8_Mu = new TChain("Muons/tree","");
  SetupTree("Muon_WpToMuNu_S8",TC_WpToMuNu_S8);
  SetupTree("Muon_WpToMuNu_S8",TC_WpToMuNu_S8_Mu);
  TString WpToMuNu_BaseName = "WpToMuNu_S8";
  Wlnu12LoMET Wmunu12LoWpMuNu(
      TC_WpToMuNu_S8,LumiW_WpToMuNu, WpToMuNu_BaseName,ModeMC,AnaChannelMu,1,true,0x1234);
  Wmunu12LoWpMuNu.Loop();

//WmToMuNu========================================
  cout<<"WmToMuNu_S8===================="<<endl;
  TChain *TC_WmToMuNu_S8    = new TChain("WMuNeu/tree","");
  TChain *TC_WmToMuNu_S8_Mu = new TChain("Muons/tree","");
  SetupTree("Muon_WmToMuNu_S8",TC_WmToMuNu_S8);
  SetupTree("Muon_WmToMuNu_S8",TC_WmToMuNu_S8_Mu);
  TString WmToMuNu_BaseName = "WmToMuNu_S8";
  Wlnu12LoMET Wmunu12LoWmMuNu(
      TC_WmToMuNu_S8,LumiW_WmToMuNu, WmToMuNu_BaseName,ModeMC,AnaChannelMu,-1,true,1234);
  Wmunu12LoWmMuNu.Loop();


  
//====================
/////////// Electron LowPU
//====================
// For Electron analysis: use the lines FROM HERE
  //Luminosity weight
  //double LumiWeight_Ele_WpToEleNu_S8= Lumi_LowPU*1*6702.0/2401905;
  //double LumiWeight_Ele_WmToEleNu_S8= Lumi_LowPU*1*4697.0/2127666;
  //double LumiW_Ele_DYToEE_S8= Lumi_LowPU*1*1871.0/3297045;
  //double LumiW_Ele_DYToTauTau_S8= Lumi_LowPU*1*1510.0/1987776;
  //double LumiW_Ele_WToTauNu_S8= Lumi_LowPU*1*9170.0/2133983;
  //double LumiW_Ele_TTJets_S8= Lumi_LowPU*1*136.3/6736135;
  //double LumiW_WpToEleNu = LumiWeight_Ele_WpToEleNu_S8;
  //double LumiW_WmToEleNu = LumiWeight_Ele_WmToEleNu_S8;
  //double LumiW_Ele_RD_LowPU = 1;

  double LumiW_WpToElNu = LumiWeight_Ele_WpToEleNu_S8;
  double LumiW_WmToElNu = LumiWeight_Ele_WmToEleNu_S8;
  //double LumiWeight_Ele_WpToEleNu_S8= RealLumi*1*6702.0/2401905;
  //double LumiWeight_Ele_WmToEleNu_S8= RealLumi*1*4697.0/2127666;
  LumiW_WpToElNu = 1;
  LumiW_WmToElNu = 1;
  
//WpToEleNu========================================
  cout<<"WpToEleNu_S8===================="<<endl;
  TChain *TC_WpToEleNu_S8     = new TChain("WEleNeu/tree","");
  TChain *TC_WpToEleNu_S8_Ele = new TChain("Electrons/tree","");
  SetupTree("Ele_WpToEleNu_S8",TC_WpToEleNu_S8);
  SetupTree("Ele_WpToEleNu_S8",TC_WpToEleNu_S8_Ele);
  TString WpToEleNu_BaseName = "WpToEleNu_S8";
  Wlnu12LoMET Wenu12LoWpEleNu(
      TC_WpToEleNu_S8,LumiW_WpToEleNu, WpToEleNu_BaseName,ModeMC,AnaChannelEle,1,true,1234);
  Wenu12LoWpEleNu.Loop();
//WmToEleNu========================================
  cout<<"WmToEleNu_S8===================="<<endl;
  TChain *TC_WmToEleNu_S8     = new TChain("WEleNeu/tree","");
  TChain *TC_WmToEleNu_S8_Ele = new TChain("Electrons/tree","");
  SetupTree("Ele_WmToEleNu_S8",TC_WmToEleNu_S8);
  SetupTree("Ele_WmToEleNu_S8",TC_WmToEleNu_S8_Ele);
  TString WmToEleNu_BaseName = "WmToEleNu_S8";
  Wlnu12LoMET Wenu12LoWmEleNu(
      TC_WmToEleNu_S8,LumiW_WmToEleNu, WmToEleNu_BaseName,ModeMC,AnaChannelEle,-1,true,1234);
  Wenu12LoWmEleNu.Loop();
}
