#include <iostream>
#include "../EventSelection/include/OneSampleTest/SetupTree.h" 
using namespace std;
//#define	RealLumi	(19619) //pb
//#define	RealLumi	(890.608) //pb
//#define	RealLumi	(4429) //pb
//#define	RealLumi	(7026.245) //pb
#define	RealLumi	(7274) //pb
void MVaNoPuMEtMakeHisto()
{
//======================================
// choose Mode and AnaChannel here  !!!
//======================================
//  TString Mode = "Resolution";//Analysis,Recoil, RecoilMC, RecoilCorr, Resolution,
//  TString AnaChannel = "MuonLowPU"; //ElectronLowPU

TString Mode = "MET";//Analysis,Recoil, RecoilMC, RecoilCorr, Resolution,
TString AnaChannelEle = "Electron2012";//ElectronLowPU
TString AnaChannelMu  = "Muon2012";
TString AnaChannelTau  = "Tau2012";

  gSystem->CompileMacro("../EventSelection/TTsemiNT.C","k");
  gSystem->CompileMacro("../EventSelection/TTsemiBase.C","k");
  gSystem->CompileMacro("../EventSelection/TTsemiMET.C","k");
// For Electron analysis: use the lines FROM HERE
//Luminosity weight
  double LumiWeight = 1;

  cout<<"TTsemi Muon S10============================"<<endl;
  TChain *TC_TTsemi_S10     = new TChain("TTsemiLept/tree","");
  TChain *TC_TTsemi_Muon       = new TChain("Muons/tree","");
  SetupTree("Test",TC_TTsemi_S10);
  SetupTree("Test",TC_TTsemi_Muon);
  TString DirName = "TTsemiMuon";
  TTsemiMET TTsemiMET_Mu(TC_TTsemi_S10,TC_TTsemi_Muon,
        LumiWeight, DirName, Mode, AnaChannelMu, 0, true, -999);
  TTsemiMET_Mu.Loop();
  //
  //cout<<"Ele_WToENu_S10============================"<<endl;
  //TChain *TC_Ele_WToENu_S10     = new TChain("WEleNeu/tree","");
  //TChain *TC_Ele_WToENu_S10_Ele = new TChain("Electrons/tree","");
  //SetupTreeGenMEt("Ele_WToENu_S10",TC_Ele_WToENu_S10);
  //SetupTreeGenMEt("Ele_WToENu_S10",TC_Ele_WToENu_S10_Ele);
  //TString Ele_WToENu_S10File = "Ele_WToENu_S10_"+Mode;
  //WLepNeu WelePt_Ele_WToENu_S10(TC_Ele_WToENu_S10,TC_Ele_WToENu_S10_Ele,
  //      LumiWeight_Ele_WToENu_S10, Ele_WToENu_S10File,Mode,AnaChannelEle);
  //WelePt_Ele_WToENu_S10.Loop();

  //cout<<"Ele_DYJetsToLL_S10============================"<<endl;
  //TChain *TC_Ele_DYJetsToLL_S10     = new TChain("WEleNeu/tree","");
  //TChain *TC_Ele_DYJetsToLL_S10_Ele = new TChain("Electrons/tree","");
  //SetupTreeGenMEt("Ele_DYJetsToLL_S10",TC_Ele_DYJetsToLL_S10);
  //SetupTreeGenMEt("Ele_DYJetsToLL_S10",TC_Ele_DYJetsToLL_S10_Ele);
  //TString Ele_DYJetsToLL_S10File = "Ele_DYJetsToLL_S10_"+Mode;
  //WLepNeu WelePt_Ele_DYJetsToLL_S10(TC_Ele_DYJetsToLL_S10,TC_Ele_DYJetsToLL_S10_Ele,
  //      LumiWeight_Ele_DYJetsToLL_S10, Ele_DYJetsToLL_S10File,Mode,AnaChannelEle);
  //WelePt_Ele_DYJetsToLL_S10.Loop();

  //cout<<"Ele_WJetsToLNu_S10============================"<<endl;
  //TChain *TC_Ele_WJetsToLNu_S10     = new TChain("WEleNeu/tree","");
  //TChain *TC_Ele_WJetsToLNu_S10_Ele = new TChain("Electrons/tree","");
  //SetupTreeGenMEt("Ele_WJetsToLNu_S10",TC_Ele_WJetsToLNu_S10);
  //SetupTreeGenMEt("Ele_WJetsToLNu_S10",TC_Ele_WJetsToLNu_S10_Ele);
  //TString Ele_WJetsToLNu_S10File = "Ele_WJetsToLNu_S10_"+Mode;
  //WLepNeu WelePt_Ele_WJetsToLNu_S10(TC_Ele_WJetsToLNu_S10,TC_Ele_WJetsToLNu_S10_Ele,
  //      LumiWeight_Ele_WJetsToLNu_S10, Ele_WJetsToLNu_S10File,Mode,AnaChannelEle);
  //WelePt_Ele_WJetsToLNu_S10.Loop();
  //
  //cout<<"Muon_WJetsToLNu_S10==========================="<<endl;
  //TChain *TC_Muon_WJetsToLNu_S10    = new TChain("WMuNeu/tree","");
  //TChain *TC_Muon_WJetsToLNu_S10_Mu = new TChain("Muons/tree","");
  //SetupTreeGenMEt("Muon_WJetsToLNu_S10",TC_Muon_WJetsToLNu_S10);
  //SetupTreeGenMEt("Muon_WJetsToLNu_S10",TC_Muon_WJetsToLNu_S10_Mu);
  //TString Muon_WJetsToLNu_S10File = "Muon_WJetsToLNu_S10_"+Mode;
  //WLepNeu WmuPt_Muon_WJetsToLNu_S10(TC_Muon_WJetsToLNu_S10,TC_Muon_WJetsToLNu_S10_Mu,
  //    LumiWeight_Mu_WJetsToLNu_S10, Muon_WJetsToLNu_S10File,Mode,AnaChannelMu);
  //WmuPt_Muon_WJetsToLNu_S10.Loop();

  //cout<<"Muon_DYJetsToLL_S10==========================="<<endl;
  //TChain *TC_Muon_DYJetsToLL_S10    = new TChain("WMuNeu/tree","");
  //TChain *TC_Muon_DYJetsToLL_S10_Mu = new TChain("Muons/tree","");
  //SetupTreeGenMEt("Muon_DYJetsToLL_S10",TC_Muon_DYJetsToLL_S10);
  //SetupTreeGenMEt("Muon_DYJetsToLL_S10",TC_Muon_DYJetsToLL_S10_Mu);
  //TString Muon_DYJetsToLL_S10File = "Muon_DYJetsToLL_S10_"+Mode;
  //WLepNeu WmuPt_Muon_DYJetsToLL_S10(TC_Muon_DYJetsToLL_S10,TC_Muon_DYJetsToLL_S10_Mu,
  //    LumiWeight_Mu_DYJetsToLL_S10, Muon_DYJetsToLL_S10File,Mode,AnaChannelMu);
  //WmuPt_Muon_DYJetsToLL_S10.Loop();

  /**********
  cout<<"Tau_WJetsToLNu_S10==========================="<<endl;
  TChain *TC_Tau_WJetsToLNu_S10    = new TChain("WTauNeu/tree","");
  TChain *TC_Tau_WJetsToLNu_S10_Tau = new TChain("Tau/tree","");
  SetupTreeGenMEt("Tau_WJetsToLNu_S10",TC_Tau_WJetsToLNu_S10);
  SetupTreeGenMEt("Tau_WJetsToLNu_S10",TC_Tau_WJetsToLNu_S10_Tau);
  TString Tau_WJetsToLNu_S10File = "Tau_WJetsToLNu_S10_"+Mode;
  //WLepNeu WmuPt_Tau_WJetsToLNu_S10(TC_Tau_WJetsToLNu_S10,TC_Tau_WJetsToLNu_S10_Tau,
  WLepNeu WmuPt_Tau_WJetsToLNu_S10(TC_Tau_WJetsToLNu_S10,0,
      LumiWeight_Tau_WJetsToLNu_S10, Tau_WJetsToLNu_S10File,Mode,AnaChannelTau);
  ************/

  /***********
  cout<<"Tau_DYJetsToLL_S10==========================="<<endl;
  TChain *TC_Tau_DYJetsToLL_S10    = new TChain("WTauNeu/tree","");
  TChain *TC_Tau_DYJetsToLL_S10_Tau = new TChain("Tau/tree","");
  SetupTreeGenMEt("Tau_DYJetsToLL_S10",TC_Tau_DYJetsToLL_S10);
  SetupTreeGenMEt("Tau_DYJetsToLL_S10",TC_Tau_DYJetsToLL_S10_Tau);
  TString Tau_DYJetsToLL_S10File = "Tau_DYJetsToLL_S10_"+Mode;
  //WLepNeu WmuPt_Tau_DYJetsToLL_S10(TC_Tau_DYJetsToLL_S10,TC_Tau_DYJetsToLL_S10_Tau,
  WLepNeu WmuPt_Tau_DYJetsToLL_S10(TC_Tau_DYJetsToLL_S10,0,
      LumiWeight_Tau_DYJetsToLL_S10, Tau_DYJetsToLL_S10File,Mode,AnaChannelTau);
  WmuPt_Tau_DYJetsToLL_S10.Loop();
  **********/
}
