#include <iostream>
#include "../EventSelection/include/SetupTreeGenMEt.h" 
using namespace std;
//#define	RealLumi	(19619) //pb
//#define	RealLumi	(890.608) //pb
//#define	RealLumi	(4429) //pb
//#define	RealLumi	(7026.245) //pb
#define	RealLumi	(7274) //pb
void MvaNoPuMEtAna()
{
//======================================
// choose Mode and AnaChannel here  !!!
//======================================
//  TString Mode = "Resolution";//Analysis,Recoil, RecoilMC, RecoilCorr, Resolution,
//  TString AnaChannel = "MuonLowPU"; //ElectronLowPU

TString Mode = "MVAnoPUMEt";//Analysis,Recoil, RecoilMC, RecoilCorr, Resolution,
TString AnaChannelEle = "ElectronHighPU";//ElectronLowPU
TString AnaChannelMu  = "MuonHighPU";
TString AnaChannelTau  = "TauHighPU";

  gSystem->CompileMacro("../EventSelection/WLepNeu.C","k");
// For Electron analysis: use the lines FROM HERE
//Luminosity weight
  double LumiWeight_Ele_WJetsToLNu_S10 = 1;
  double LumiWeight_Ele_DYJetsToLL_S10 = 1;
  double LumiWeight_Ele_TTJets_S10     = 1;
  double LumiWeight_Ele_ZGToNuNuG_S10  = 1;
  double LumiWeight_Ele_ZG_Incl_S10    = 1;
  double LumiWeight_Mu_WJetsToLNu_S10  = 1;
  double LumiWeight_Mu_DYJetsToLL_S10  = 1;
  double LumiWeight_Mu_TTJets_S10      = 1;
  double LumiWeight_Mu_ZGToNuNuG_S10   = 1;
  double LumiWeight_Mu_ZG_Incl_S10     = 1;
  double LumiWeight_Tau_WJetsToLNu_S10  = 1;
  double LumiWeight_Tau_WToTauNu_S10   = 1;
  double LumiWeight_Tau_DYJetsToLL_S10 = 1;
  double LumiWeight_Tau_TTJets_S10     = 1;
  double LumiWeight_Tau_ZGToNuNuG_S10  = 1;
  double LumiWeight_Tau_ZG_Incl_S10    = 1;

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

  cout<<"Tau_WJetsToLNu_S10==========================="<<endl;
  TChain *TC_Tau_WJetsToLNu_S10    = new TChain("WTauNeu/tree","");
  TChain *TC_Tau_WJetsToLNu_S10_Tau = new TChain("Tau/tree","");
  SetupTreeGenMEt("Tau_WJetsToLNu_S10",TC_Tau_WJetsToLNu_S10);
  SetupTreeGenMEt("Tau_WJetsToLNu_S10",TC_Tau_WJetsToLNu_S10_Tau);
  TString Tau_WJetsToLNu_S10File = "Tau_WJetsToLNu_S10_"+Mode;
  //WLepNeu WmuPt_Tau_WJetsToLNu_S10(TC_Tau_WJetsToLNu_S10,TC_Tau_WJetsToLNu_S10_Tau,
  WLepNeu WmuPt_Tau_WJetsToLNu_S10(TC_Tau_WJetsToLNu_S10,0,
      LumiWeight_Tau_WJetsToLNu_S10, Tau_WJetsToLNu_S10File,Mode,AnaChannelTau);
  
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
}
