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
  //TString ModeRD = "Analysis";
  //TString ModeMC = "AllCorrectionsMC";
  //TString ModeRD = "AllCorrectionsRD";
  TString ModeMC = "ScaleMakeMC";//ScaleMakeRD,ScaleMakeMC,Analysis,Recoil, RecoilMC, RecoilCorr, Resolution,
  TString ModeRD = "ScaleMakeRD";//ScaleMakeRD,ScaleMakeMC,Analysis,Recoil, RecoilMC, RecoilCorr, Resolution,
 
  TString AnaChannelEle = "Electron2012LoPU"; 
  TString AnaChannelMu  = "Muon2012LoPU";

  bool RunOnMC(true);
  bool RunOnRD(false);

  //gSystem->Load("libMathCore");
  //gSystem->Load("libPhysics");

 // gSystem->CompileMacro("../EventSelection/Wlnu12LoNT.C","k");
 // gSystem->CompileMacro("../EventSelection/Wlnu12LoBase.C","k");
 // gSystem->CompileMacro("../EventSelection/Wlnu12LoTempl.C","k");

  gSystem->CompileMacro("../EventSelection/Wlnu12LoNT.C","k");
  gSystem->CompileMacro("../EventSelection/Wlnu12LoBase.C","k");
  gSystem->CompileMacro("../EventSelection/Wlnu12LoScaleSmearCorr.C","k");



//====================
/////////// Muon LowPU
//====================
// For Muon analysis: use the lines FROM HERE
  //Luminosity weight
  double LumiW_Muon_DYToMuMu_S8 = Lumi_LowPU*1*1871.0/1.9802e6;
  double LumiW_Muon_RD_LowPU = 1;

/*  
//Muon_RD_LowPU========================================
  cout<<"Muon_RD_LowPU===================="<<endl;
  TChain *TC_Muon_RD_LowPU = new TChain("WMuNeu/tree","");
  SetupTree("Muon_RD_LowPU",TC_Muon_RD_LowPU);
  TString Muon_RD_LowPU_BaseName = "Muon_RD_LowPU";
  Wlnu12LoScaleSmearCorr Wmunu12LoRD(
      TC_Muon_RD_LowPU,LumiW_Muon_RD_LowPU, Muon_RD_LowPU_BaseName,ModeRD,AnaChannelMu,0,RunOnRD,0x1235);
  Wmunu12LoRD.Loop();
////*/
 
/*
//DYToMuMu========================================
  cout<<"DYToMuMu_S8========================="<<endl;
  TChain *TC_DYToMuMu_S8	= new TChain("WMuNeu/tree","");
  SetupTree("Muon_DYToMuMu_S8",TC_DYToMuMu_S8);
  TString DYToMuMu_BaseName = "Muon_DYToMuMu_S8";
  Wlnu12LoScaleSmearCorr Wmunu12LoDYToMuMu(
      TC_DYToMuMu_S8,LumiW_Muon_DYToMuMu_S8, DYToMuMu_BaseName,ModeMC,AnaChannelMu,0,RunOnMC,0x1235);
  Wmunu12LoDYToMuMu.Loop();
///*/
  
//====================
/////////// Electron LowPU
//====================
// For Electron analysis: use the lines FROM HERE
  //Luminosity weight
  double LumiW_Ele_DYToEE_S8= Lumi_LowPU*1*1871.0/3297045;
  double LumiW_Ele_RD_LowPU = 1;
//*
//Ele_RD_LowPU========================================
  cout<<"Ele_RD_LowPU===================="<<endl;
  TChain *TC_Ele_RD_LowPU = new TChain("WEleNeu/tree","");
  SetupTree("Ele_RD_LowPU",TC_Ele_RD_LowPU);
  TString Ele_RD_LowPU_BaseName = "Ele_RD_LowPU";
  Wlnu12LoScaleSmearCorr Wenu12LoRD(
      TC_Ele_RD_LowPU,LumiW_Ele_RD_LowPU, Ele_RD_LowPU_BaseName,ModeRD,AnaChannelEle,0,RunOnRD,0x1235);
  Wenu12LoRD.Loop();

//DYToEE========================================
  cout<<"DYToEE_S8========================="<<endl;
  TChain *TC_Ele_DYToEE_S8	= new TChain("WEleNeu/tree","");
  SetupTree("Ele_DYToEE_S8",TC_Ele_DYToEE_S8);
  TString Ele_DYToEE_BaseName = "Ele_DYToEE_S8";
  Wlnu12LoScaleSmearCorr Wenu12LoDYToEE(
      TC_Ele_DYToEE_S8,LumiW_Ele_DYToEE_S8, Ele_DYToEE_BaseName,ModeMC,AnaChannelEle,0,RunOnMC,0x1235);
  Wenu12LoDYToEE.Loop();
///*////

}
