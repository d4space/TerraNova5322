#include "TSystem.h"
#include <iostream>
#include "../EventSelection/include/Tree2012LoPU/SetupTree.h"
#include "../Utils/const.h"
//#include "../EventSelection/WpT.h"

using namespace std;

//using namespace ROOT::Math;
void WPtRecoilMakeHisto()
{
//======================================
// choose Mode and AnaChannel here  !!!
//======================================
//  TString AnaChannel = "MuonLowPU"; //ElectronLowPU

  TString ModeMC = "RecoilEvaMC";
  TString ModeRD = "RecoilEvaRD";
  TString AnaChannelEle = "Electron2012LoPU"; 
  TString AnaChannelMu  = "Muon2012LoPU";

  bool RunOnMC(true);
  bool RunOnRD(false);

  gSystem->CompileMacro("../EventSelection/Wlnu12LoNT.C","k");
  gSystem->CompileMacro("../EventSelection/Wlnu12LoBase.C","k");
  gSystem->CompileMacro("../EventSelection/Wlnu12LoRecoilCorr.C","k");

//====================
/////////// Muon LowPU
//====================
// For Muon analysis: use the lines FROM HERE
  //Luminosity weight
  double LumiW_Muon_RD_LowPU = 1;
  double LumiW_WpToMuNu = 1;
  double LumiW_WmToMuNu = 1;
  double LumiW_Muon_DYToMuMu_S8 = 1;

//Muon_RD_LowPU========================================
  cout<<"Muon_RD_LowPU===================="<<endl;
  TChain *TC_Muon_RD_LowPU = new TChain("WMuNeu/tree","");
  SetupTree("Muon_RD_LowPU",TC_Muon_RD_LowPU);
  TString Muon_RD_LowPU_BaseName = "Muon_RD_LowPU";
  Wlnu12LoRecoilCorr Wmunu12LoRD(
      TC_Muon_RD_LowPU,LumiW_Muon_RD_LowPU, Muon_RD_LowPU_BaseName,ModeRD,AnaChannelMu,0,RunOnRD,0x1235);
  Wmunu12LoRD.Loop();
 
//WpToMuNu========================================
  cout<<"WpToMuNu_S8===================="<<endl;
  TChain *TC_WpToMuNu_S8    = new TChain("WMuNeu/tree","");
  SetupTree("Muon_WpToMuNu_S8",TC_WpToMuNu_S8);
  TString WpToMuNu_BaseName = "WpToMuNu_S8";
  Wlnu12LoRecoilCorr Wmunu12LoWpMuNu(
      TC_WpToMuNu_S8,LumiW_WpToMuNu, WpToMuNu_BaseName,ModeMC,AnaChannelMu,1,RunOnMC,0x1235);
  Wmunu12LoWpMuNu.Loop();
  
//WmToMuNu========================================
  cout<<"WmToMuNu_S8===================="<<endl;
  TChain *TC_WmToMuNu_S8    = new TChain("WMuNeu/tree","");
  SetupTree("Muon_WmToMuNu_S8",TC_WmToMuNu_S8);
  TString WmToMuNu_BaseName = "WmToMuNu_S8";
  Wlnu12LoRecoilCorr Wmunu12LoWmMuNu(
      TC_WmToMuNu_S8,LumiW_WmToMuNu, WmToMuNu_BaseName,ModeMC,AnaChannelMu,-1,RunOnMC,0x1235);
  Wmunu12LoWmMuNu.Loop();

//DYToMuMu========================================
  cout<<"DYToMuMu_S8========================="<<endl;
  TChain *TC_Muon_DYToMuMu_S8	= new TChain("WMuNeu/tree","");
  SetupTree("Muon_DYToMuMu_S8",TC_Muon_DYToMuMu_S8);
  TString Muon_DYToMuMu_BaseName = "Muon_DYToMuMu_S8";
  Wlnu12LoRecoilCorr Wmunu12LoDYToMuMu(
      TC_Muon_DYToMuMu_S8,LumiW_Muon_DYToMuMu_S8, Muon_DYToMuMu_BaseName,ModeMC,AnaChannelMu,0,true,0x1235);
  Wmunu12LoDYToMuMu.Loop();

//====================
/////////// Electron LowPU
//====================
// For Electron analysis: use the lines FROM HERE
  //Luminosity weight
  double LumiW_Ele_RD_LowPU = 1;
  double LumiW_WpToEleNu = 1;
  double LumiW_WmToEleNu = 1;
  double LumiW_Ele_DYToEE_S8= 1;

//Ele_RD_LowPU========================================
  cout<<"Ele_RD_LowPU===================="<<endl;
  TChain *TC_Ele_RD_LowPU = new TChain("WEleNeu/tree","");
  SetupTree("Ele_RD_LowPU",TC_Ele_RD_LowPU);
  TString Ele_RD_LowPU_BaseName = "Ele_RD_LowPU";
  Wlnu12LoRecoilCorr Wenu12LoRD(
      TC_Ele_RD_LowPU,LumiW_Ele_RD_LowPU, Ele_RD_LowPU_BaseName,ModeRD,AnaChannelEle,0,false,0x1235);
  Wenu12LoRD.Loop();

//WpToEleNu========================================
  cout<<"WpToEleNu_S8===================="<<endl;
  TChain *TC_WpToEleNu_S8    = new TChain("WEleNeu/tree","");
  SetupTree("Ele_WpToEleNu_S8",TC_WpToEleNu_S8);
  TString WpToEleNu_BaseName = "WpToEleNu_S8";
  Wlnu12LoRecoilCorr Wenu12LoWpEleNu(
      TC_WpToEleNu_S8,LumiW_WpToEleNu, WpToEleNu_BaseName,ModeMC,AnaChannelEle,1,true,0x1235);
  Wenu12LoWpEleNu.Loop();

//WmToEleNu========================================
  cout<<"WmToEleNu_S8===================="<<endl;
  TChain *TC_WmToEleNu_S8    = new TChain("WEleNeu/tree","");
  SetupTree("Ele_WmToEleNu_S8",TC_WmToEleNu_S8);
  TString WmToEleNu_BaseName = "WmToEleNu_S8";
  Wlnu12LoRecoilCorr Wenu12LoWmEleNu(
      TC_WmToEleNu_S8,LumiW_WmToEleNu, WmToEleNu_BaseName,ModeMC,AnaChannelEle,-1,true,0x1235);
  Wenu12LoWmEleNu.Loop();

//DYToEE========================================
  cout<<"DYToEE_S8========================="<<endl;
  TChain *TC_Ele_DYToEE_S8	= new TChain("WEleNeu/tree","");
  SetupTree("Ele_DYToEE_S8",TC_Ele_DYToEE_S8);
  TString Ele_DYToEE_BaseName = "Ele_DYToEE_S8";
  Wlnu12LoRecoilCorr Wenu12LoDYToEE(
      TC_Ele_DYToEE_S8,LumiW_Ele_DYToEE_S8, Ele_DYToEE_BaseName,ModeMC,AnaChannelEle,0,true,0x1235);
  Wenu12LoDYToEE.Loop();

}
