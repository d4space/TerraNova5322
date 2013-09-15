#include <iostream>
#include "../EventSelection/includeMVaNoPuMET/SetupTree.h" 
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
TString AnaChannelTau = "TauHighPU";//ElectronLowPU
TString AnaChannelEle = "ElectronHighPU";//ElectronLowPU
TString AnaChannelMu  = "MuonLowPU";

  gSystem->CompileMacro("../EventSelection/WLepNeu.C","k");
// For Electron analysis: use the lines FROM HERE
//Luminosity weight
  double LumiWeight_Ele_DYToEE_S10	   = RealLumi*1*1915.08/3277040;
  double LumiWeight_Ele_DYJetsToLL_S10     = RealLumi*1*2950/28709500;
  double LumiWeight_Ele_DYToTauTau_S10     = RealLumi*1*1581.419/9989370;
  double LumiWeight_Ele_WToENu_S10         = RealLumi*1*12503.0/4383520;
  double LumiWeight_Ele_WpToENu_S10        = RealLumi*1*7322.0/6554350;
  double LumiWeight_Ele_WmToENu_S10        = RealLumi*1*5181.0/6553050;
  double LumiWeight_Ele_WpToTauNu_S10      = RealLumi*1*7322.0/5880570;
  double LumiWeight_Ele_WmToTauNu_S10      = RealLumi*1*5142.3/4601540;
  double LumiWeight_Ele_WToTauNu_S10       = RealLumi*1*12503.0/5000740;
  double LumiWeight_Ele_WJetsToLNu_S10     = RealLumi*1*30400/105000;
  double LumiWeight_Ele_TTJets_S10         = RealLumi*1*136.3/1364780;
  double LumiWeight_Ele_TT_CT10_S10        = RealLumi*1*225.197/2990940;
  double LumiWeight_Ele_QCD30to50_S10      = RealLumi*1*66285328/5800000;
  double LumiWeight_Ele_QCD50to80_S10      = RealLumi*1*8148778/5920350;
  double LumiWeight_Ele_QCD80to120_S10     = RealLumi*1*1033680/5994860;
  double LumiWeight_Ele_QCD120to170_S10    = RealLumi*1*156293.3/4744420;
  double LumiWeight_Ele_G_Pt50to80_S10     = RealLumi*1*3322.309/1995060;

  LumiWeight_Ele_DYToEE_S10	    = 1;
  LumiWeight_Ele_DYJetsToLL_S10     = 1;
  LumiWeight_Ele_DYToTauTau_S10     = 1;
  LumiWeight_Ele_WToENu_S10         = 1;
  LumiWeight_Ele_WpToENu_S10        = 1;
  LumiWeight_Ele_WmToENu_S10        = 1;
  LumiWeight_Ele_WpToTauNu_S10      = 1;
  LumiWeight_Ele_WmToTauNu_S10      = 1;
  LumiWeight_Ele_WToTauNu_S10       = 1;
  LumiWeight_Ele_WJetsToLNu_S10     = 1;
  LumiWeight_Ele_TTJets_S10         = 1;
  LumiWeight_Ele_TT_CT10_S10        = 1;
  LumiWeight_Ele_QCD30to50_S10      = 1;
  LumiWeight_Ele_QCD50to80_S10      = 1;
  LumiWeight_Ele_QCD80to120_S10     = 1;
  LumiWeight_Ele_QCD120to170_S10    = 1;
  LumiWeight_Ele_G_Pt50to80_S10     = 1;
  double oneLumi(1);

  cout<<"Tau_DYJetsToLL_S10============================"<<endl;
  TChain *TC_Tau_DYJetsToLL_S10     = new TChain("WTauNeu/tree","");
  SetupTree("Tau_DYJetsToLL_S10",TC_Tau_DYJetsToLL_S10);
  TString Tau_DYJetsToLL_S10File = "Tau_DYJetsToLL_S10_"+Mode;
  WLepNeu MVaMET_Tau_DYJetsToLL_S10(TC_Tau_DYJetsToLL_S10,0,
        oneLumi, Tau_DYJetsToLL_S10File,Mode,AnaChannelTau);
  MVaMET_Tau_DYJetsToLL_S10.Loop();
  /*********
  cout<<"Ele_WToENu_S10============================"<<endl;
  TChain *TC_Ele_WToENu_S10     = new TChain("WEleNeu/tree","");
  TChain *TC_Ele_WToENu_S10_Ele = new TChain("Electrons/tree","");
  SetupTreeHighPU("Ele_WToENu_S10",TC_Ele_WToENu_S10);
  SetupTreeHighPU("Ele_WToENu_S10",TC_Ele_WToENu_S10_Ele);
  TString Ele_WToENu_S10File = "Ele_WToENu_S10_"+Mode;
  WLepNeu WelePt_Ele_WToENu_S10(TC_Ele_WToENu_S10,TC_Ele_WToENu_S10_Ele,
        LumiWeight_Ele_WToENu_S10, Ele_WToENu_S10File,Mode,AnaChannelEle);
  WelePt_Ele_WToENu_S10.Loop();
  *************/
}
