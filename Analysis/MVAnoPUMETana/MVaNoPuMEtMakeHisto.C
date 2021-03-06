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
/*
  gSystem->CompileMacro("../EventSelection/TTsemiNT.C","k");
  gSystem->CompileMacro("../EventSelection/TTsemiBase.C","k");
  gSystem->CompileMacro("../EventSelection/TTsemiMET.C","k");

  gSystem->CompileMacro("../EventSelection/TT2HadNT.C","k");
  gSystem->CompileMacro("../EventSelection/TT2HadBase.C","k");
  gSystem->CompileMacro("../EventSelection/TT2HadMET.C","k");

  gSystem->CompileMacro("../EventSelection/MonoJetNT.C","k");
  gSystem->CompileMacro("../EventSelection/MonoJetBase.C","k");
  gSystem->CompileMacro("../EventSelection/MonoJetMET.C","k");
*/  
  gSystem->CompileMacro("../EventSelection/mSUGRANT.C","k");
  gSystem->CompileMacro("../EventSelection/mSUGRABase.C","k");
  gSystem->CompileMacro("../EventSelection/mSUGRAMET.C","k");
/*
  gSystem->CompileMacro("../EventSelection/MonoPhotonNT.C","k");
  gSystem->CompileMacro("../EventSelection/MonoPhotonBase.C","k");
  gSystem->CompileMacro("../EventSelection/MonoPhotonMET.C","k");

  gSystem->CompileMacro("../EventSelection/WlnuNT.C","k");
  gSystem->CompileMacro("../EventSelection/WlnuBase.C","k");
  gSystem->CompileMacro("../EventSelection/WlnuMET.C","k");
  gSystem->CompileMacro("../EventSelection/WlnuTemple.C","k");

  gSystem->CompileMacro("../EventSelection/ZllNT.C","k");
  gSystem->CompileMacro("../EventSelection/ZllBase.C","k");
  gSystem->CompileMacro("../EventSelection/ZllMET.C","k");

  gSystem->CompileMacro("../EventSelection/ZZ4LNT.C","k");
  gSystem->CompileMacro("../EventSelection/ZZ4LBase.C","k");
  gSystem->CompileMacro("../EventSelection/ZZ4LMET.C","k");

  gSystem->CompileMacro("../EventSelection/WWNT.C","k");
  gSystem->CompileMacro("../EventSelection/WWBase.C","k");
  gSystem->CompileMacro("../EventSelection/WWMET.C","k");

  gSystem->CompileMacro("../EventSelection/WZ3LNT.C","k");
  gSystem->CompileMacro("../EventSelection/WZ3LBase.C","k");
  gSystem->CompileMacro("../EventSelection/WZ3LMET.C","k");
*/

// For Electron analysis: use the lines FROM HERE
//Luminosity weight
  double LumiWeight = 1;

  /*********
  cout<<"TTsemi Muon S10============================"<<endl;
  TChain *TC_TTsemi_S10     = new TChain("TTsemiLept/tree","");
  TChain *TC_TTsemi_Muon       = new TChain("Muons/tree","");
  SetupTree("TTsemi_Muon_S10",TC_TTsemi_S10);
  SetupTree("TTsemi_Muon_S10",TC_TTsemi_Muon);
  TString DirName = "TTsemiMuon";
  TTsemiMET TTsemiMET_Mu(TC_TTsemi_S10,TC_TTsemi_Muon,
        LumiWeight, DirName, Mode, AnaChannelMu, 0, true, -999);
  TTsemiMET_Mu.Loop();
  ****/
  /*********
  cout<<"TTsemi Electron S10============================"<<endl;
  TChain *TC_TTsemi_S10     = new TChain("TTsemiLept/tree","");
  TChain *TC_TTsemi_Electron       = new TChain("Electrons/tree","");
  SetupTree("TTsemi_Electron_S10",TC_TTsemi_S10);
  SetupTree("TTsemi_Electron_S10",TC_TTsemi_Electron);
  TString DirName = "TTsemiElectron";
  TTsemiMET TTsemiMET_Ele(TC_TTsemi_S10,TC_TTsemi_Electron,
        LumiWeight, DirName, Mode, AnaChannelEle, 0, true, -999);
  TTsemiMET_Ele.Loop();
  *************/
  /*************
  cout<<"TT2Hadron S10============================"<<endl;
  TChain *TC_TT2Had_S10     = new TChain("TT2Hadron/tree","");
  SetupTree("TT2Had_S10",TC_TT2Had_S10);
  TString DirName = "TT2Hadron";
  TT2HadMET TT2HadMET_King(TC_TT2Had_S10,
        LumiWeight, DirName, Mode, AnaChannelEle, 0, true, -999);
  TT2HadMET_King.Loop();
  **************/
  /***************
  cout<<"MonoJet S10============================"<<endl;
  TChain *TC_MJet_S10     = new TChain("MonoJet/tree","");
  SetupTree("MJet_S10",TC_MJet_S10);
  TString DirName = "MonoJet";
  MonoJetMET MonoJet_King(TC_MJet_S10,
        LumiWeight, DirName, Mode, AnaChannelEle, 0, true, -999);
  MonoJet_King.Loop();
  *************/
  
  /*************/
  cout<<"mSUGRA S10============================"<<endl;
  TChain *TC_mSUGRA_S10     = new TChain("Susy/tree","");
  SetupTree("mSUGRA_S10",TC_mSUGRA_S10);
  TString DirName = "mSUGRA";
  mSUGRAMET mSUGRA_King(TC_mSUGRA_S10,
        LumiWeight, DirName, Mode, AnaChannelEle, 0, true, -999);
  mSUGRA_King.Loop();

  /************
  cout<<"MonoPhoton S10============================"<<endl;
  TChain *TC_MPhoton_S10     = new TChain("MonoPhoton/tree","");
  SetupTree("MPhoton_S10",TC_MPhoton_S10);
  TString DirName = "MonoPhoton";
  MonoPhotonMET MonoPhoton_King(TC_MPhoton_S10,
        LumiWeight, DirName, Mode, AnaChannelEle, 0, true, -999);
  MonoPhoton_King.Loop();
  *************/

  //
  /***************
  cout<<"Electron_WJetsToLNu_S10==========================="<<endl;
  TChain *TC_WToENu_S10     = new TChain("WEleNeu/tree","");
  SetupTree("WToENu_S10",TC_WToENu_S10);
  TString DirBase = "WToENu";
  WlnuMET WeleNuMET(TC_WToENu_S10,
        LumiWeight, DirBase, Mode, AnaChannelEle, 1234);
  WeleNuMET.Loop();
  *************/

  /*****************
  cout<<"Muon_WJetsToLNu_S10==========================="<<endl;
  TChain *TC_WToMuNu_S10     = new TChain("WMuNeu/tree","");
  SetupTree("WToMuNu_S10",TC_WToMuNu_S10);
  TString DirBase = "WToMuNu";
  WlnuMET WMuNuMET(TC_WToMuNu_S10,
        LumiWeight, DirBase, Mode, AnaChannelMu, 1234);
  WMuNuMET.Loop();
  ************/

  /***********
  cout<<"Ele_DYJetsToLL_S10============================"<<endl;
  TChain *TC_DYElEl_S10     = new TChain("ZElEl/tree","");
  TChain *TC_DYElEl_S10_Ele = new TChain("Electrons/tree","");
  SetupTree("DYElEl_S10",TC_DYElEl_S10);
  SetupTree("DYElEl_S10",TC_DYElEl_S10_Ele);
  TString DirBase = "DYElEl";
  ZllMET ZllMETking(TC_DYElEl_S10,TC_DYElEl_S10_Ele,
        LumiWeight, DirBase, Mode, AnaChannelEle);
  ZllMETking.Loop();
  ***********/
  /***************
  cout<<"ZZ4Mu_S10==========================="<<endl;
  TChain *TC_ZZ4L_S10     = new TChain("ZZ4L/tree","");
  TChain *TC_ZZ4L_S10_Muon = new TChain("Muons/tree","");
  SetupTree("ZZ4Mu_S10",TC_ZZ4L_S10);
  SetupTree("ZZ4Mu_S10",TC_ZZ4L_S10_Muon);
  TString DirBase = "ZZ4Mu";
  ZZ4LMET ZZ4LMETking(TC_ZZ4L_S10,TC_ZZ4L_S10_Muon,
        LumiWeight, DirBase, Mode, AnaChannelMu);
  ZZ4LMETking.Loop();
  ***********/
  /***************
  cout<<"ZZ4El_S10==========================="<<endl;
  TChain *TC_ZZ4L_S10     = new TChain("ZZ4L/tree","");
  TChain *TC_ZZ4L_S10_Electron = new TChain("Electrons/tree","");
  SetupTree("ZZ4El_S10",TC_ZZ4L_S10);
  SetupTree("ZZ4El_S10",TC_ZZ4L_S10_Electron);
  TString DirBase = "ZZ4El";
  ZZ4LMET ZZ4LMETking(TC_ZZ4L_S10,TC_ZZ4L_S10_Electron,
        LumiWeight, DirBase, Mode, AnaChannelEle);
  ZZ4LMETking.Loop();
  *************/

  /**************
  cout<<"ZZMuEl_S10==========================="<<endl;
  TChain *TC_ZZMuEl_S10     = new TChain("ZZ4L/tree","");
  TChain *TC_ZZMuEl_S10_Electron = new TChain("Electrons/tree","");
  SetupTree("ZZMuEl_S10",TC_ZZMuEl_S10);
  SetupTree("ZZMuEl_S10",TC_ZZMuEl_S10_Electron);
  TString DirBase = "ZZMuEl";
  ZZ4LMET ZZ4LMETking(TC_ZZMuEl_S10,TC_ZZMuEl_S10_Electron,
        LumiWeight, DirBase, Mode, AnaChannelEle);
  ZZ4LMETking.Loop();
  *************/

  /**********
  cout<<"ZZ2Mu2Nu_S10==========================="<<endl;
  TChain *TC_ZZ2Mu2Nu_S10     = new TChain("ZZ4L/tree","");
  TChain *TC_ZZ2Mu2Nu_S10_Muon = new TChain("Muons/tree","");
  SetupTree("ZZ2Mu2Nu_S10",TC_ZZ2Mu2Nu_S10);
  SetupTree("ZZ2Mu2Nu_S10",TC_ZZ2Mu2Nu_S10_Muon);
  TString DirBase = "ZZ2Mu2Nu";
  ZZ4LMET ZZ4LMETking(TC_ZZ2Mu2Nu_S10,TC_ZZ2Mu2Nu_S10_Muon,
        LumiWeight, DirBase, Mode, AnaChannelMu);
  ZZ4LMETking.Loop();
  ************/

  /***************
  cout<<"ZZ2El2Nu_S10==========================="<<endl;
  TChain *TC_ZZ2El2Nu_S10     = new TChain("ZZ4L/tree","");
  TChain *TC_ZZ2El2Nu_S10_Electron = new TChain("Electrons/tree","");
  SetupTree("ZZ2El2Nu_S10",TC_ZZ2El2Nu_S10);
  SetupTree("ZZ2El2Nu_S10",TC_ZZ2El2Nu_S10_Electron);
  TString DirBase = "ZZ2El2Nu";
  ZZ4LMET ZZ4LMETking(TC_ZZ2El2Nu_S10,TC_ZZ2El2Nu_S10_Electron,
      LumiWeight, DirBase, Mode, AnaChannelEle);
  ZZ4LMETking.Loop();
  ***************/

  /***************
  cout<<"WW_S10==========================="<<endl;
  TChain *TC_WW_S10     = new TChain("WW/tree","");
  TChain *TC_WW_S10_Electron = new TChain("Electrons/tree","");
  SetupTree("WW_S10",TC_WW_S10);
  SetupTree("WW_S10",TC_WW_S10_Electron);
  TString DirBase = "WW";
  WWMET WWMETking(TC_WW_S10,TC_WW_S10_Electron,
        LumiWeight, DirBase, Mode, AnaChannelEle);
  WWMETking.Loop();

  ************/
  /************
  cout<<"WZ_S10==========================="<<endl;
  TChain *TC_WZ_S10     = new TChain("WZ3LNu/tree","");
  TChain *TC_WZ_S10_Electron = new TChain("Electrons/tree","");
  SetupTree("WZ_S10",TC_WZ_S10);
  SetupTree("WZ_S10",TC_WZ_S10_Electron);
  TString DirBase = "WZ";
  WZ3LMET WZ3LMETking(TC_WZ_S10,TC_WZ_S10_Electron,
        LumiWeight, DirBase, Mode, AnaChannelEle);
  WZ3LMETking.Loop();
  **********/
  /**********
  cout<<"Muon_DYJetsToLL_S10==========================="<<endl;
  TChain *TC_DYMuMu_S10    = new TChain("ZMuMu/tree","");
  TChain *TC_DYMuMu_S10_Mu = new TChain("Muons/tree","");
  SetupTree("DYMuMu_S10",TC_DYMuMu_S10);
  SetupTree("DYMuMu_S10",TC_DYMuMu_S10_Mu);
  TString DirBase = "DYMuMu";
  ZllMET ZllMETking(TC_DYMuMu_S10,TC_DYMuMu_S10_Mu,
      LumiWeight, DirBase, Mode, AnaChannelMu);
  ZllMETking.Loop();
  ***********/

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
