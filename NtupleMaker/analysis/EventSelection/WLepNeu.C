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
  mResultDir = AnaChannel;

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
int WLepNeu::DumpWbestCand(int i)
{
  W.charge = (*W_Charge)[i];
  //Muon Variable Study----------------------
  if(AnaChannel == "MuonLowPU" ){
    glbMuChi2 = (*W_Lept1_globalNormChi2)[i];
    W.muonHit = (*W_Lept1_muonHits)[i];
    W.matchStation = (*W_Lept1_matchStations)[i];
    W.trkLayers = (*W_Lept1_trkLayers)[i];
    W.pixelHits = (*W_Lept1_pixelHits)[i];
    W.dB = fabs((*W_Lept1_dB)[i]);
    W.chIso03 = (*W_Lept1_chIso03)[i];
    W.chIso04 = (*W_Lept1_chIso04)[i];
    W.nhIso03 = (*W_Lept1_nhIso03)[i];
    W.nhIso04 = (*W_Lept1_nhIso04)[i];
    W.phIso03 = (*W_Lept1_phIso03)[i];
    W.phIso04 = (*W_Lept1_phIso04)[i];
    W.pcIso03 = (*W_Lept1_pcIso03)[i];
    W.pcIso04 = (*W_Lept1_pcIso04)[i];
  }
  if(AnaChannel == "ElectronLowPU" )
  {
    W.lep_etaSC = (*W_Lept1_etaSC)[i];
  }
  if(AnaChannel == "TauHighPU")
  {
    W.dz = 1;// Tau channel has a problem!
  }else{
    W.dz = fabs((*W_Lept1_dz)[i]);
  }
  // Common for all flavor of leptons
  W.lep_pt = (*W_Lept1_pt)[i];
  W.lep_phi = (*W_Lept1_phi)[i];
  W.Nu_px	= pfMEt_x;
  W.Nu_py	= pfMEt_y;
  W.lep_eta = (*W_Lept1_eta)[i];
  W.pt = (*W_pt)[i];
  w_acop= (*W_Acop)[i];

  W.Mt = (*W_Mt)[i];
  W.Met = (*W_Neut_pt)[i];
  if(Mode == "AllCorrectionsMC" || Mode == "RecoilCorrMC")if(GenW_Born_Id->size()>0)
  {
    W.genIdx = (*W_Lept1_genIdxMatch)[i];
  }//RecoilCorr

  if(Mode == "RecoilEvaRD" || Mode == "RecoilEvaMC")
  {
    //Recoil = -Met -Lepts
    W.RecoilT2->Set(
	  	-(*W_Neut_px)[i]-(*W_Lept1_px)[i],
	  	-(*W_Neut_py)[i]-(*W_Lept1_py)[i]);
    //if( GenW_Born_Id->size() < 1)cout<<"GenW size is "<<GenW_Born_Id->size()<<endl;
    if( Mode == "RecoilEvaMC")if(GenW_Born_Id->size() > 0)
    {
      W.trthIdx = (*W_Lept1_genIdxMatch)[i];
      //if( W.trthIdx != 0 || i != 0)
      //cout<<"Gen Idx: "<<W.trthIdx<<" i: "<<i<<endl;
      if( fabs((*W_Lept1_genDeltaR)[i]) > 0.025)
      {
        //cout<<"W not MC truth"<<endl;
        W.trthIdx = 0; //Let's use the one
      }
      if(W.trthIdx < 0) W.trthIdx = 0;
      //genBeFsrW_pt = (*GenW_pt)[W.trthIdx];

      W.PostT2->Set(
          (*GenW_PostLept1_px)[W.trthIdx]+(*GenW_PostLept2_px)[W.trthIdx],
          (*GenW_PostLept1_py)[W.trthIdx]+(*GenW_PostLept2_py)[W.trthIdx]);
      W.Post_pt= W.PostT2->Mod();
      //u1 = B.u, u2 = B cross u
      Rcl.u1W =(*W.RecoilT2) * (*W.PostT2)/W.Post_pt;
      Rcl.u2W =(W.RecoilT2->Px()*W.PostT2->Py()
          -W.RecoilT2->Py()*W.PostT2->Px())/W.Post_pt;
      Rcl.u3W =(*W.RecoilT2)*(*W.PostT2)/W.Post_pt+W.Post_pt;
    }
  }

  if( RunOnMC && (GenW_Born_Id->size() > 0))
  {
    if((abs((*GenW_BornLept1_id)[W.trthIdx])==12)
     ||(abs((*GenW_BornLept1_id)[W.trthIdx])==14)
     ||(abs((*GenW_BornLept1_id)[W.trthIdx])==16))
    {
      genInfo.BornW_Nu_Pt = (*GenW_BornLept1_pt)[W.trthIdx];
      genInfo.BornW_Nu_Cnt ++;
    }else if((abs((*GenW_BornLept2_id)[0])==12)
	   ||(abs((*GenW_BornLept2_id)[0])==14)
	   ||(abs((*GenW_BornLept2_id)[0])==16))
    {
      genInfo.BornW_Nu_Pt = (*GenW_BornLept2_pt)[W.trthIdx];
      genInfo.BornW_Nu_Cnt ++;
    }else{
      cout << "There is no BornW_Nu_Pt" << endl;
    }
  }
  return 0;
}
int WLepNeu::Fill_W_METs()
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
