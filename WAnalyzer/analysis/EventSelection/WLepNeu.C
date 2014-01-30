// $Log: WLepNeu.C,v $
// Revision 1.8  2013/09/13 00:09:32  salee
// *** empty log message ***
//
//   In a ROOT session, you can do:
//      Root > .L WLepNeu.C
//      Root > WLepNeu t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
#define WLepNeu_cxx
//#include <iostream>
//#include <TROOT.h>                        // access to gROOT, entry point to ROOT system
//#include <TSystem.h>                      // interface to OS
#include <TBenchmark.h>                   // class to track macro running statistics
#include <algorithm>
#include "WLepNeu.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TSystem.h>
#include <TVector2.h>
#include <TLorentzVector.h>
//#include "../Utils/MyTools.hh"	          // various helper functions

#include "Math/PtEtaPhiE4D.h"
#include "Math/PtEtaPhiM4D.h"
#include "Math/LorentzVector.h"

typedef ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiM4D<double> > PtEtaPhiMLorentzVectorD;
typedef PtEtaPhiMLorentzVectorD PtEtaPhiMLorentzVector;
int WLepNeu::InitVar()
{
  cout<<"Initialize variables at WLepNeu Class ==================="<<endl;
  return 0;
}
void WLepNeu::Loop()
{
  gBenchmark->Start("WLepNeu");
  gRandom->SetSeed(0);
//
  if (fChain == 0) return;
   //int Ntries = fChain->GetEntriesFast(); this gives 1234567890 kkk
  Ntries = fChain->GetEntries();
  gBenchmark->Show("WLepNeu");
}
int WLepNeu::CheckChannel()
{
  //cout<<"CheckChannel============"<<endl;
  //cout<<AnaChannel<<"\t"<<Channel<<endl;
  if(AnaChannel == "MuonLowPU" )if(fabs(Channel) != GenType::kMuon) return -1;
  if(AnaChannel == "MuonHighPU")if(fabs(Channel) != GenType::kMuon) return-1;
  if(AnaChannel == "ElectronLowPU")if(fabs(Channel) != GenType::kElectron) return-1;
  if(AnaChannel == "ElectronHighPU")if(fabs(Channel) != GenType::kElectron) return-1;
  if(AnaChannel == "TauHighPU")if(fabs(Channel) != GenType::kTau) return-1;
  return 0;
}
int WLepNeu::TriggerCut()
{
    if(AnaChannel == "MuonLowPU" )if( HLT_Mu15_eta2p1_fired < 1) return -1;
    if(AnaChannel == "ElectronLowPU" )if(HLT_Ele22_CaloIdL_CaloIsoVL_fired<1) return -1;
    if(AnaChannel=="ElectronHighPU")if(HLT_Ele27_WP80_fired<1) return -1;
  return 0;
}
int WLepNeu::DumpWbestCand(int idx)
{
  wCand.charge = (*W_Charge)[idx];
  //Muon Variable Study----------------------
  if(AnaChannel == "MuonLowPU" ){
    glbMuChi2 = (*W_Lept1_globalNormChi2)[idx];
    wCand.muonHit = (*W_Lept1_muonHits)[idx];
    wCand.matchStation = (*W_Lept1_matchStations)[idx];
    wCand.trkLayers = (*W_Lept1_trkLayers)[idx];
    wCand.pixelHits = (*W_Lept1_pixelHits)[idx];
    wCand.dB = fabs((*W_Lept1_dB)[idx]);
    wCand.chIso03 = (*W_Lept1_chIso03)[idx];
    wCand.chIso04 = (*W_Lept1_chIso04)[idx];
    wCand.nhIso03 = (*W_Lept1_nhIso03)[idx];
    wCand.nhIso04 = (*W_Lept1_nhIso04)[idx];
    wCand.phIso03 = (*W_Lept1_phIso03)[idx];
    wCand.phIso04 = (*W_Lept1_phIso04)[idx];
    wCand.pcIso03 = (*W_Lept1_pcIso03)[idx];
    wCand.pcIso04 = (*W_Lept1_pcIso04)[idx];
  }

  if(AnaChannel == "TauHighPU")
  {
    wCand.dz = 1;// Tau channel has a problem!
  }else{
    wCand.dz = fabs((*W_Lept1_dz)[idx]);
  }

  wCand.Mt = (*W_Mt)[idx];
  wCand.Met = (*W_Neut_pt)[idx];
  return 0;
}
int WLepNeu::DumpWMETs()
{
  h1_W_Met->Fill(pfMEtTL.Pt());
  h1_W_Born_Met->Fill(genInfo.BornW_Nu_Pt);
  h1_W_genMEtTrue->Fill(genMEtTrueTL.Pt());
  h1_W_MVA_Met->Fill(MVaMEtTL.Pt());
  h1_W_NoPU_Met->Fill(NoPuMEtTL.Pt());

  return 0;
}
int WLepNeu::DumpZMETs()
{
  h1_Z_Met->Fill(pfMEtTL.Pt());
  h1_Z_genMEtTrue->Fill(genMEtTrueTL.Pt());
  h1_Z_MVA_Met->Fill(MVaMEtTL.Pt());
  h1_Z_NoPU_Met->Fill(NoPuMEtTL.Pt());

  return 0;
}
