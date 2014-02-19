//#include "../Utils/const.h"
//#include "../Utils/CPlot.hh"
//#include "../Utils/MitStyleRemix.hh"
#include <TSystem.h>	// gSystem
#include <iostream>
#include "../EventSelection/include/SetupTreeHighPU.h"
#include "../EventSelection/WLepNeu.h"
using namespace std;
#define	RealLumi	(19619) //pb
void scaleSmearMakeHistoHighPU(int Range)
{
//======================================
// choose Mode and AnaChannel here  !!!
//======================================
//  TString Mode = "Resolution";//Analysis,Recoil, RecoilMC, RecoilCorr, Resolution,
//  TString AnaChannel = "MuonLowPU"; //ElectronLowPU

  TString ModeMC = "ScaleMakeMC";//ScaleMakeRD,ScaleMakeMC,Analysis,Recoil, RecoilMC, RecoilCorr, Resolution,
  TString ModeRD = "ScaleMakeRD";//ScaleMakeRD,ScaleMakeMC,Analysis,Recoil, RecoilMC, RecoilCorr, Resolution,

  TString AnaChannelEle = "ElectronHighPU"; 
  //TString AnaChannelEle = "ElectronLowPU"; 

  //gSystem->CompileMacro("../EventSelection/WLepNeu.C","k");
  cout<<"Range is "<<Range<<endl;
//=========================
/////////// Electron LowPU
//=========================
// For Electron analysis: use the lines FROM HERE
//Luminosity weight
  double LumiWeight_Ele_DYToEE_S10         = RealLumi*1*1915.08/3277040;
  double LumiWeight_Ele_DYToTauTau_S10     = RealLumi*1*1581.419/9989370;
  double LumiWeight_Ele_WpToENu_S10        = RealLumi*1*7322.0/6554350;
  double LumiWeight_Ele_WmToENu_S10        = RealLumi*1*5181.0/6553050;
  double LumiWeight_Ele_WToTauNu_S10       = RealLumi*1*12503.0/5000740;
  double LumiWeight_Ele_TTJets_S10         = RealLumi*1*136.3/1364780;
  
  

  double LumiWeight_Ele_RD_HighPU = 1;
 
  cout<<"Ele_RD_HighPU===================="<<endl;
  TChain *TC_Ele_RD_HighPU    = new TChain("WEleNeu/tree","");
  TChain *TC_Ele_RD_HighPU_Ele = new TChain("Electrons/tree","");
  SetupTreeHighPU("Ele_RD_HighPU",TC_Ele_RD_HighPU);
  SetupTreeHighPU("Ele_RD_HighPU",TC_Ele_RD_HighPU_Ele);
  TString Ele_RD_HighPUFile = "Ele_RD_HighPU_"+ModeRD;
  WLepNeu WelePt_Ele_RD_HighPU(
  TC_Ele_RD_HighPU,TC_Ele_RD_HighPU_Ele,
  LumiWeight_Ele_RD_HighPU, Ele_RD_HighPUFile,ModeRD,AnaChannelEle,Range);
  WelePt_Ele_RD_HighPU.Loop();




  cout<<"Ele_DYToEE_S10==========================="<<endl;
  TChain *TC_Ele_DYToEE_S10    = new TChain("WEleNeu/tree","");
  TChain *TC_Ele_DYToEE_S10_Ele = new TChain("Electrons/tree","");
  SetupTreeHighPU("Ele_DYToEE_S10",TC_Ele_DYToEE_S10);
  SetupTreeHighPU("Ele_DYToEE_S10",TC_Ele_DYToEE_S10_Ele);
  TString Ele_DYToEE_S10File = "Ele_DYToEE_S10_"+ModeMC;
  WLepNeu WelePt_Ele_DYToEE_S10(TC_Ele_DYToEE_S10,TC_Ele_DYToEE_S10_Ele,
  LumiWeight_Ele_DYToEE_S10, Ele_DYToEE_S10File,ModeMC,AnaChannelEle,Range);
  WelePt_Ele_DYToEE_S10.Loop();
/*
 cout<<"Ele_DYToTauTau_S10==========================="<<endl;
 TChain *TC_Ele_DYToTauTau_S10    = new TChain("WEleNeu/tree","");
 TChain *TC_Ele_DYToTauTau_S10_Ele = new TChain("Electrons/tree","");
 SetupTreeHighPU("Ele_DYToTauTau_S10",TC_Ele_DYToTauTau_S10);
 SetupTreeHighPU("Ele_DYToTauTau_S10",TC_Ele_DYToTauTau_S10_Ele);
 TString Ele_DYToTauTau_S10File = "Ele_DYToTauTau_S10_"+ModeMC;
 WLepNeu WelePt_Ele_DYToTauTau_S10(TC_Ele_DYToTauTau_S10,TC_Ele_DYToTauTau_S10_Ele,
 LumiWeight_Ele_DYToTauTau_S10, Ele_DYToTauTau_S10File,ModeMC,AnaChannelEle,Range);
 WelePt_Ele_DYToTauTau_S10.Loop();

 cout<<"Ele_WminusToEleNu_S10==========================="<<endl;
 TChain *TC_Ele_WmToENu_S10    = new TChain("WEleNeu/tree","");
 TChain *TC_Ele_WmToENu_S10_Ele = new TChain("Electrons/tree","");
 SetupTreeHighPU("Ele_WmToENu_S10",TC_Ele_WmToENu_S10);
 SetupTreeHighPU("Ele_WmToENu_S10",TC_Ele_WmToENu_S10_Ele);
  TString Ele_WmToENu_S10File = "Ele_WmToENu_S10_"+ModeMC;
  WLepNeu WelePt_Ele_WmToENu_S10(TC_Ele_WmToENu_S10,TC_Ele_WmToENu_S10_Ele,
  LumiWeight_Ele_WmToENu_S10, Ele_WmToENu_S10File,ModeMC,AnaChannelEle,Range);
  WelePt_Ele_WmToENu_S10.Loop();

  cout<<"Ele_WplusToEleNu_S10==========================="<<endl;
  TChain *TC_Ele_WpToENu_S10    = new TChain("WEleNeu/tree","");
  TChain *TC_Ele_WpToENu_S10_Ele = new TChain("Electrons/tree","");
  SetupTreeHighPU("Ele_WpToENu_S10",TC_Ele_WpToENu_S10);
  SetupTreeHighPU("Ele_WpToENu_S10",TC_Ele_WpToENu_S10_Ele);
  TString Ele_WpToENu_S10File = "Ele_WpToENu_S10_"+ModeMC;
  WLepNeu WelePt_Ele_WpToENu_S10(TC_Ele_WpToENu_S10,TC_Ele_WpToENu_S10_Ele,
  LumiWeight_Ele_WpToENu_S10, Ele_WpToENu_S10File,ModeMC,AnaChannelEle,Range);
  WelePt_Ele_WpToENu_S10.Loop();

  cout<<"Ele_WToTauNu_S10============================"<<endl;
  TChain *TC_Ele_WToTauNu_S10     = new TChain("WEleNeu/tree","");
  TChain *TC_Ele_WToTauNu_S10_Ele = new TChain("Electrons/tree","");
  SetupTreeHighPU("Ele_WToTauNu_S10",TC_Ele_WToTauNu_S10);
  SetupTreeHighPU("Ele_WToTauNu_S10",TC_Ele_WToTauNu_S10_Ele);
  TString Ele_WToTauNu_S10File = "Ele_WToTauNu_S10_"+ModeMC;
  WLepNeu WelePt_Ele_WToTauNu_S10(TC_Ele_WToTauNu_S10,TC_Ele_WToTauNu_S10_Ele,
  LumiWeight_Ele_WToTauNu_S10, Ele_WToTauNu_S10File,ModeMC,AnaChannelEle,Range);
  WelePt_Ele_WToTauNu_S10.Loop();

  cout<<"Ele_TTJets_S10==========================="<<endl;
  TChain *TC_Ele_TTJets_S10    = new TChain("WEleNeu/tree","");
  TChain *TC_Ele_TTJets_S10_Ele = new TChain("Electrons/tree","");
  SetupTreeHighPU("Ele_TTJets_S10",TC_Ele_TTJets_S10);
  SetupTreeHighPU("Ele_TTJets_S10",TC_Ele_TTJets_S10_Ele);
  TString Ele_TTJets_S10File = "Ele_TTJets_S10_"+ModeMC;
  WLepNeu WelePt_Ele_TTJets_S10(TC_Ele_TTJets_S10,TC_Ele_TTJets_S10_Ele,
  LumiWeight_Ele_TTJets_S10, Ele_TTJets_S10File,ModeMC,AnaChannelEle,Range);
  WelePt_Ele_TTJets_S10.Loop();
*/








}
