#include "TSystem.h"
#include <iostream>
#include "../EventSelection/include/Tree2012LoPU/SetupTree.h"
#include "../Utils/const.h"
//#include "../EventSelection/WpT.h"

using namespace std;

//using namespace ROOT::Math;
void WPtTemplMakeHisto()
{
//======================================
// choose Mode and AnaChannel here  !!!
//======================================
//  TString AnaChannel = "MuonLowPU"; //ElectronLowPU

  //TString ModeMC = "Analysis";//Analysis,Recoil, RecoilEvaMC,RecoilEvaRD, RecoilCorr, Unfold,DumpUnfInfo
  TString ModeMC = "AllCorrectionsMC";
  TString ModeRD = "AllCorrectionsRD";
  TString AnaChannelEle = "Electron2012LoPU"; 
  TString AnaChannelMu  = "Muon2012LoPU";

  bool RunOnMC(true);
  bool RunOnRD(false);

  //gSystem->Load("libMathCore");
  //gSystem->Load("libPhysics");

  gSystem->CompileMacro("../EventSelection/Wlnu12LoNT.C","k");
  gSystem->CompileMacro("../EventSelection/Wlnu12LoBase.C","k");
  gSystem->CompileMacro("../EventSelection/Wlnu12LoTempl.C","k");

//====================
/////////// Muon LowPU
//====================
// For Muon analysis: use the lines FROM HERE
  //Luminosity weight
  double LumiWeight_Muon_WmToMuNu_S8 = Lumi_LowPU*1*4697.0/1.97346e6;
  double LumiWeight_Muon_WpToMuNu_S8 = Lumi_LowPU*1*6702.0/935446;
  double LumiW_Muon_DYToMuMu_S8 = Lumi_LowPU*1*1871.0/1.9802e6;
  double LumiW_Muon_WToTauNu_S8 = Lumi_LowPU*1*9170.0/2.13398e6;
  double LumiW_Muon_DYToTauTau_S8 = Lumi_LowPU*1*1510.0/1.98778e6;
  double LumiW_Muon_TTJets_S8 = Lumi_LowPU*1*136.3/6.73614e6;
  double LumiW_WpToMuNu = LumiWeight_Muon_WpToMuNu_S8;
  double LumiW_WmToMuNu = LumiWeight_Muon_WmToMuNu_S8;
  double LumiW_Muon_RD_LowPU = 1;

//Muon_RD_LowPU========================================
  cout<<"Muon_RD_LowPU===================="<<endl;
  TChain *TC_Muon_RD_LowPU = new TChain("WMuNeu/tree","");
  SetupTree("Muon_RD_LowPU",TC_Muon_RD_LowPU);
  TString Muon_RD_LowPU_BaseName = "Muon_RD_LowPU";
  Wlnu12LoTempl Wmunu12LoRD(
      TC_Muon_RD_LowPU,LumiW_Muon_RD_LowPU, Muon_RD_LowPU_BaseName,ModeRD,AnaChannelMu,0,RunOnRD,0x1235);
  Wmunu12LoRD.Loop();
  
//WpToMuNu========================================
  cout<<"WpToMuNu_S8===================="<<endl;
  TChain *TC_WpToMuNu_S8    = new TChain("WMuNeu/tree","");
  SetupTree("Muon_WpToMuNu_S8",TC_WpToMuNu_S8);
  TString WpToMuNu_BaseName = "WpToMuNu_S8";
  Wlnu12LoTempl Wmunu12LoWpMuNu(
      TC_WpToMuNu_S8,LumiW_WpToMuNu, WpToMuNu_BaseName,ModeMC,AnaChannelMu,1,RunOnMC,0x1235);
  Wmunu12LoWpMuNu.Loop();
  
//WmToMuNu========================================
  cout<<"WmToMuNu_S8===================="<<endl;
  TChain *TC_WmToMuNu_S8    = new TChain("WMuNeu/tree","");
  SetupTree("Muon_WmToMuNu_S8",TC_WmToMuNu_S8);
  TString WmToMuNu_BaseName = "WmToMuNu_S8";
  Wlnu12LoTempl Wmunu12LoWmMuNu(
      TC_WmToMuNu_S8,LumiW_WmToMuNu, WmToMuNu_BaseName,ModeMC,AnaChannelMu,-1,RunOnMC,0x1235);
  Wmunu12LoWmMuNu.Loop();
/*
//DYToMuMu========================================
  cout<<"DYToMuMu_S8========================="<<endl;
  TChain *TC_Muon_DYToMuMu_S8	= new TChain("WMuNeu/tree","");
  SetupTree("Muon_DYToMuMu_S8",TC_Muon_DYToMuMu_S8);
  TString Muon_DYToMuMu_BaseName = "Muon_DYToMuMu_S8";
  Wlnu12LoTempl Wmunu12LoDYToMuMu(
      TC_Muon_DYToMuMu_S8,LumiW_Muon_DYToMuMu_S8, Muon_DYToMuMu_BaseName,ModeMC,AnaChannelMu,0,true,0x1235);
  Wmunu12LoDYToMuMu.Loop();

//WToTauNu========================================
  cout<<"WToTauNu_S8========================="<<endl;
  TChain *TC_Muon_WToTauNu_S8	= new TChain("WMuNeu/tree","");
  SetupTree("Muon_WToTauNu_S8",TC_Muon_WToTauNu_S8);
  TString Muon_WToTauNu_BaseName = "Muon_WToTauNu_S8";
  Wlnu12LoTempl Wmunu12LoWToTauNu(
      TC_Muon_WToTauNu_S8,LumiW_Muon_WToTauNu_S8, Muon_WToTauNu_BaseName,ModeMC,AnaChannelMu,0,true,0x1235);
  Wmunu12LoWToTauNu.Loop();
//DYToTauTau========================================
  cout<<"DYToTauTau_S8========================="<<endl;
  TChain *TC_Muon_DYToTauTau_S8	= new TChain("WMuNeu/tree","");
  SetupTree("Muon_DYToTauTau_S8",TC_Muon_DYToTauTau_S8);
  TString Muon_DYToTauTau_BaseName = "Muon_DYToTauTau_S8";
  Wlnu12LoTempl Wmunu12LoDYToTauTau(
      TC_Muon_DYToTauTau_S8,LumiW_Muon_DYToTauTau_S8, Muon_DYToTauTau_BaseName,ModeMC,AnaChannelMu,0,true,0x1235);
  Wmunu12LoDYToTauTau.Loop();

//TTJets========================================
  cout<<"TTJets_S8========================="<<endl;
  TChain *TC_Muon_TTJets_S8	= new TChain("WMuNeu/tree","");
  SetupTree("Muon_TTJets_S8",TC_Muon_TTJets_S8);
  TString Muon_TTJets_BaseName = "Muon_TTJets_S8";
  Wlnu12LoTempl Wmunu12LoTTJets(
      TC_Muon_TTJets_S8,LumiW_Muon_TTJets_S8, Muon_TTJets_BaseName,ModeMC,AnaChannelMu,0,true,0x1235);
  Wmunu12LoTTJets.Loop();
*/
//====================
/////////// Electron LowPU
//====================
// For Electron analysis: use the lines FROM HERE
  //Luminosity weight
  double LumiWeight_Ele_WpToEleNu_S8= Lumi_LowPU*1*6702.0/2401905;
  double LumiWeight_Ele_WmToEleNu_S8= Lumi_LowPU*1*4697.0/2127666;
  double LumiW_Ele_DYToEE_S8= Lumi_LowPU*1*1871.0/3297045;
  double LumiW_Ele_DYToTauTau_S8= Lumi_LowPU*1*1510.0/1987776;
  double LumiW_Ele_WToTauNu_S8= Lumi_LowPU*1*9170.0/2133983;
  double LumiW_Ele_TTJets_S8= Lumi_LowPU*1*136.3/6736135;
  double LumiW_WpToEleNu = LumiWeight_Ele_WpToEleNu_S8;
  double LumiW_WmToEleNu = LumiWeight_Ele_WmToEleNu_S8;
  double LumiW_Ele_RD_LowPU = 1;
/*
//Ele_RD_LowPU========================================
  cout<<"Ele_RD_LowPU===================="<<endl;
  TChain *TC_Ele_RD_LowPU = new TChain("WEleNeu/tree","");
  SetupTree("Ele_RD_LowPU",TC_Ele_RD_LowPU);
  TString Ele_RD_LowPU_BaseName = "Ele_RD_LowPU";
  Wlnu12LoTempl Wenu12LoRD(
      TC_Ele_RD_LowPU,LumiW_Ele_RD_LowPU, Ele_RD_LowPU_BaseName,ModeRD,AnaChannelEle,0,false,0x1235);
  Wenu12LoRD.Loop();

//WpToEleNu========================================
  cout<<"WpToEleNu_S8===================="<<endl;
  TChain *TC_WpToEleNu_S8    = new TChain("WEleNeu/tree","");
  SetupTree("Ele_WpToEleNu_S8",TC_WpToEleNu_S8);
  TString WpToEleNu_BaseName = "WpToEleNu_S8";
  Wlnu12LoTempl Wenu12LoWpEleNu(
      TC_WpToEleNu_S8,LumiW_WpToEleNu, WpToEleNu_BaseName,ModeMC,AnaChannelEle,1,true,0x1235);
  Wenu12LoWpEleNu.Loop();

//WmToEleNu========================================
  cout<<"WmToEleNu_S8===================="<<endl;
  TChain *TC_WmToEleNu_S8    = new TChain("WEleNeu/tree","");
  SetupTree("Ele_WmToEleNu_S8",TC_WmToEleNu_S8);
  TString WmToEleNu_BaseName = "WmToEleNu_S8";
  Wlnu12LoTempl Wenu12LoWmEleNu(
      TC_WmToEleNu_S8,LumiW_WmToEleNu, WmToEleNu_BaseName,ModeMC,AnaChannelEle,-1,true,0x1235);
  Wenu12LoWmEleNu.Loop();

//DYToEE========================================
  cout<<"DYToEE_S8========================="<<endl;
  TChain *TC_Ele_DYToEE_S8	= new TChain("WEleNeu/tree","");
  SetupTree("Ele_DYToEE_S8",TC_Ele_DYToEE_S8);
  TString Ele_DYToEE_BaseName = "Ele_DYToEE_S8";
  Wlnu12LoTempl Wenu12LoDYToEE(
      TC_Ele_DYToEE_S8,LumiW_Ele_DYToEE_S8, Ele_DYToEE_BaseName,ModeMC,AnaChannelEle,0,true,0x1235);
  Wenu12LoDYToEE.Loop();

//DYToTauTau========================================
  cout<<"DYToTauTau_S8========================="<<endl;
  TChain *TC_Ele_DYToTauTau_S8	= new TChain("WEleNeu/tree","");
  SetupTree("Ele_DYToTauTau_S8",TC_Ele_DYToTauTau_S8);
  TString Ele_DYToTauTau_BaseName = "Ele_DYToTauTau_S8";
  Wlnu12LoTempl Wenu12LoDYToTauTau(
      TC_Ele_DYToTauTau_S8,LumiW_Ele_DYToTauTau_S8, Ele_DYToTauTau_BaseName,ModeMC,AnaChannelEle,0,true,0x1235);
  Wenu12LoDYToTauTau.Loop();

//WToTauNu========================================
  cout<<"WToTauNu_S8========================="<<endl;
  TChain *TC_Ele_WToTauNu_S8	= new TChain("WEleNeu/tree","");
  SetupTree("Ele_WToTauNu_S8",TC_Ele_WToTauNu_S8);
  TString Ele_WToTauNu_BaseName = "Ele_WToTauNu_S8";
  Wlnu12LoTempl Wenu12LoWToTauNu(
      TC_Ele_WToTauNu_S8,LumiW_Ele_WToTauNu_S8, Ele_WToTauNu_BaseName,ModeMC,AnaChannelEle,0,true,0x1235);
  Wenu12LoWToTauNu.Loop();

//TTJets========================================
  cout<<"TTJets_S8========================="<<endl;
  TChain *TC_Ele_TTJets_S8	= new TChain("WEleNeu/tree","");
  SetupTree("Ele_TTJets_S8",TC_Ele_TTJets_S8);
  TString Ele_TTJets_BaseName = "Ele_TTJets_S8";
  Wlnu12LoTempl Wenu12LoTTJets(
      TC_Ele_TTJets_S8,LumiW_Ele_TTJets_S8, Ele_TTJets_BaseName,ModeMC,AnaChannelEle,0,true,0x1235);
  Wenu12LoTTJets.Loop();
*/
}
