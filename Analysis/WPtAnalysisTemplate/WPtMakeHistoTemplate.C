#include "TSystem.h"
#include <iostream>
#include "../EventSelection/include/Tree2012LoPU/SetupTree.h"
#include "../Utils/const.h"
//#include "../EventSelection/WpT.h"

using namespace std;

//using namespace ROOT::Math;
void WPtMakeHistoTemplate()
{
//======================================
// choose Mode and AnaChannel here  !!!
//======================================
//  TString AnaChannel = "MuonLowPU"; //ElectronLowPU

  TString Mode = "Analysis";//Analysis,Recoil, RecoilEvaMC,RecoilEvaRD, RecoilCorr, Unfold,DumpUnfInfo
  TString AnaChannelEle = "Electron2012LoPU"; 
  TString AnaChannelMu  = "Muon2012LoPU";

  //gSystem->Load("libMathCore");
  //gSystem->Load("libPhysics");

  gSystem->CompileMacro("../EventSelection/Wlnu12LoNT.C","k");
  gSystem->CompileMacro("../EventSelection/Wlnu12LoBase.C","k");
  gSystem->CompileMacro("../EventSelection/Wlnu12LoTemple.C","k");

//====================
/////////// Muon LowPU
//====================
// For Muon analysis: use the lines FROM HERE
  //Luminosity weight
  double LumiWeight_Muon_WmToMuNu_S8 = Lumi_LowPU*1*4697.0/1.97346e6;
  double LumiWeight_Muon_WpToMuNu_S8 = Lumi_LowPU*1*6702.0/935446;
  double LumiW_WpToMuNu = LumiWeight_Muon_WpToMuNu_S8;
  double LumiW_WmToMuNu = LumiWeight_Muon_WmToMuNu_S8;
  LumiW_WpToMuNu = 1;
  LumiW_WmToMuNu = 1;



//WpToMuNu========================================
  cout<<"WpToMuNu_S8===================="<<endl;
  TChain *TC_WpToMuNu_S8    = new TChain("WMuNeu/tree","");
  SetupTree("Muon_WpToMuNu_S8",TC_WpToMuNu_S8);
  TString WpToMuNu_BaseName = "WpToMuNu_S8";
  Wlnu12LoTemple Wlnu12LoTempleEG(
      TC_WpToMuNu_S8,LumiW_WpToMuNu, WpToMuNu_BaseName,Mode,AnaChannelMu,1,true,1234);
  Wlnu12LoTempleEG.Loop();
}
