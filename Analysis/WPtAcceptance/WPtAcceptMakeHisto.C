#include "TSystem.h"
#include <iostream>
#include "../EventSelection/include/Tree2012LoPU/SetupTreeAccept.h"
#include "../Utils/const.h"

using namespace std;

//using namespace ROOT::Math;
void WPtAcceptMakeHisto()
{
//======================================
// choose Mode and AnaChannel here  !!!
//======================================
//  TString AnaChannel = "MuonLowPU"; //ElectronLowPU

  TString ModeMC = "Acceptance";
  TString AnaChannelEle = "Electron2012LoPU"; 
  TString AnaChannelMu  = "Muon2012LoPU";

  bool RunOnMC(true);

  gSystem->CompileMacro("../EventSelection/Wlnu12LoNT.C","k");
  gSystem->CompileMacro("../EventSelection/Wlnu12LoBase.C","k");
  gSystem->CompileMacro("../EventSelection/Wlnu12LoAccept.C","k");

//====================
/////////// Muon LowPU
//====================
// For Muon analysis: use the lines FROM HERE
  //Luminosity weight
  double LumiW_WpToMuNu = 1;
  double LumiW_WmToMuNu = 1;

//WpToMuNu========================================
  cout<<"WpToMuNu_S8===================="<<endl;
  TChain *TC_WpToMuNu_S8 = new TChain("WAcceptanceMuon/tree","");
  SetupTreeAccept("Muon_WpToMuNu_S8",TC_WpToMuNu_S8);
  TString WpToMuNu_BaseName = "WpToMuNu_S8";
  Wlnu12LoAccept Wmunu12LoWpMuNu(
      TC_WpToMuNu_S8,LumiW_WpToMuNu,WpToMuNu_BaseName,ModeMC,AnaChannelMu,1,RunOnMC,0x1235);
  Wmunu12LoWpMuNu.Loop();

//WmToMuNu========================================
  cout<<"WmToMuNu_S8===================="<<endl;
  TChain *TC_WmToMuNu_S8 = new TChain("WAcceptanceMuon/tree","");
  SetupTreeAccept("Muon_WmToMuNu_S8",TC_WmToMuNu_S8);
  TString WmToMuNu_BaseName = "WmToMuNu_S8";
  Wlnu12LoAccept Wmunu12LoWmMuNu(
      TC_WmToMuNu_S8,LumiW_WmToMuNu,WmToMuNu_BaseName,ModeMC,AnaChannelMu,-1,RunOnMC,0x1235);
  Wmunu12LoWmMuNu.Loop();

//====================
/////////// Electron LowPU
//====================
// For Electron analysis: use the lines FROM HERE
  //Luminosity weight
  double LumiW_WpToEleNu = 1;
  double LumiW_WmToEleNu = 1;

//WpToEleNu========================================
  cout<<"WpToEleNu_S8===================="<<endl;
  TChain *TC_WpToEleNu_S8 = new TChain("WAcceptanceElectron/tree","");
  SetupTreeAccept("Ele_WpToEleNu_S8",TC_WpToEleNu_S8);
  TString WpToEleNu_BaseName = "WpToEleNu_S8";
  Wlnu12LoAccept Wenu12LoWpEleNu(
      TC_WpToEleNu_S8,LumiW_WpToEleNu,WpToEleNu_BaseName,ModeMC,AnaChannelEle,1,true,0x1235);
  Wenu12LoWpEleNu.Loop();

//WmToEleNu========================================
  cout<<"WmToEleNu_S8===================="<<endl;
  TChain *TC_WmToEleNu_S8 = new TChain("WAcceptanceElectron/tree","");
  SetupTreeAccept("Ele_WmToEleNu_S8",TC_WmToEleNu_S8);
  TString WmToEleNu_BaseName = "WmToEleNu_S8";
  Wlnu12LoAccept Wenu12LoWmEleNu(
      TC_WmToEleNu_S8,LumiW_WmToEleNu,WmToEleNu_BaseName,ModeMC,AnaChannelEle,-1,true,0x1235);
  Wenu12LoWmEleNu.Loop();
}
