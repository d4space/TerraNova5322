// $Log: Wlnu12LoBase.C,v $
// Revision 1.8  2013/09/13 00:09:32  salee
// *** empty log message ***
//
#define Wlnu12LoBase_cxx
//#include <iostream>
//#include <TROOT.h>                        // access to gROOT, entry point to ROOT system
//#include <TSystem.h>                      // interface to OS
#include <TBenchmark.h>                   // class to track macro running statistics
#include <algorithm>
#include "Wlnu12LoBase.h"
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

void Wlnu12LoBase::Loop()
{
  gBenchmark->Start("Wlnu12LoBase");
  //gRandom->SetSeed(0);
  //gRandom->SetSeed(0x1234);
//
  if (fChain == 0) return;
   //int Ntries = fChain->GetEntriesFast(); this gives 1234567890 kkk
  Ntries = fChain->GetEntries();
  gBenchmark->Show("Wlnu12LoBase");
}
int Wlnu12LoBase::InitVar()
{ 
  W.RecoilT2 = new TVector2();
  W.PostT2 = new TVector2();
  return 0;
}
int Wlnu12LoBase::CheckChannel()
{
  //cout<<"CheckChannel============"<<endl;
  //cout<<AnaChannel<<"\t"<<Channel<<endl;
  if(AnaChannel == "Muon2012LoPU" )if(fabs(Channel) != GenType::kMuon) return -1;
  if(AnaChannel == "MuonHighPU")if(fabs(Channel) != GenType::kMuon) return-1;
  if(AnaChannel == "Electron2012LoPU")if(fabs(Channel) != GenType::kElectron) return-1;
  if(AnaChannel == "ElectronHighPU")if(fabs(Channel) != GenType::kElectron) return-1;
  if(AnaChannel == "TauHighPU")if(fabs(Channel) != GenType::kTau) return-1;
  return 0;
}
int Wlnu12LoBase::TriggerCut()
{
    if(AnaChannel == "Muon2012LoPU" )if( HLT_Mu15_eta2p1_fired < 1) return -1;
    if(AnaChannel == "Electron2012LoPU" )if(HLT_Ele22_CaloIdL_CaloIsoVL_fired<1) return -1;
    if(AnaChannel=="ElectronHighPU")if(HLT_Ele27_WP80_fired<1) return -1;
  return 0;
}
int Wlnu12LoBase::DumpWbestCand(int i)
{
  W.charge = (*W_Charge)[i];
  //Muon Variable Study----------------------
  if(AnaChannel == "Muon2012LoPU" ){
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
  if(AnaChannel == "Electron2012LoPU" )
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
  W.lep_eta = (*W_Lept1_eta)[i];
  W.Mt = (*W_Mt)[i];
  W.Met = (*W_Neut_pt)[i];
  
  TVector2 W_pt_corr(W.Met*cos((*W_Neut_phi)[i])+W.lep_pt_corr*cos(W.lep_phi),
      W.Met*sin((*W_Neut_phi)[i])+W.lep_pt_corr*sin(W.lep_phi));
  W.pt = W_pt_corr.Mod();
  //W.pt = (*W_pt)[i];
  W.acop= (*W_Acop)[i];

  if(Mode == "SmeaRecEffCorr" || Mode == "RecoilCorrMC")if(GenW_Born_Id->size()>0)
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
        //cout << "There is no BornW_Nu_Pt" << endl;
      }
    }
  }
  return 0;
}
int Wlnu12LoBase::WbestSelect()
{
  double lep_Big(0);
  for(int iw(0); iw<W.size; iw++)
  {
    //Cut to W.lep_pt_corr
    W.lep_pt_corr = (*W_Lept1_pt)[iw];
    if (Mode=="ScaleCorr")DoScaleCorr(iw);
    if((Mode == "SmeaRecEffCorr" || Mode == "SmeaEffCorr") || Mode == "Unfold")DoSmearCorr(iw);
    W_Lept1_pt_Corr.push_back(W.lep_pt_corr);
    //additional lepton count
    if(AnaChannel == "Muon2012LoPU")	if(AddMuonCut(iw)>0) addLepN++;
    if(AnaChannel == "Muon2012")	if(AddMuonCut(iw)>0) addLepN++;
    if(AnaChannel == "Electron2012LoPU")if(AddElectronCut(iw)>0)addLepN++;
    if(AnaChannel == "Electron2012")	if(AddElectronCutHighPU(iw)>0) addLepN++;
    if(AnaChannel == "Tau2012")		if(TauCut(iw)>0) addLepN++;

    if( ((AnaChannel == "Muon2012LoPU" ) && (MuonCut(iw) >0))||
	((AnaChannel == "Muon2012") && (MuonCut(iw) >0))||
	((AnaChannel == "Electron2012LoPU")&& (ElectronCut(iw) > 0))||
	((AnaChannel =="Electron2012") &&(ElectronCutHighPU(iw) > 0)) ||
	((AnaChannel =="Tau2012") && (TauCut(iw)) > 0)
	  //Best Candidate selection
    )if( lep_Big < W.lep_pt_corr)
    {
      lep_Big = W.lep_pt_corr;
      W.idxBest = iw;
      W.Pass = true;
    }//Cut and Bigger pt
  }
  W.lep_pt_corr = lep_Big;
  return 0;
}

int Wlnu12LoBase::FillWSide(int j)
{
  if(((AnaChannel == "Muon2012LoPU") && MuonCutSide(j) >0)||
      ((AnaChannel == "Electron2012LoPU") && ElectronCutSide(j) > 0)||
      (AnaChannel =="ElectronHighPU" && ElectronCutSideHighPU(j) > 0)
      )
  {
    W.Met_side = (*W_Neut_pt)[j];
    W.charge = (*W_Charge)[j];
    W.lep_pt_corr = W_Lept1_pt_Corr[j];
    TVector2 W_pt_corr(W.Met_side*cos((*W_Neut_phi)[j])+W.lep_pt_corr*cos((*W_Lept1_phi)[j]),
	W.Met_side*sin((*W_Neut_phi)[j])+W.lep_pt_corr*sin((*W_Lept1_phi)[j]));
    W.pt_side = W_pt_corr.Mod();
    if(Mode == "SmeaRecEffCorr")
    {
      DoRecoilCorr();
      W.Met_side = corrMet;
      W.pt_side = W.pt;
    }
  }
  return 0;
}

int Wlnu12LoBase::VertexCut()
{
  mVtxVar.nPrim = vtx_isFake->size();
  if(mVtxVar.nPrim < 1 ) return -1;

  // Check the VTX cuts for the largest Sum(Pt) vertex
  if( (*vtx_isFake)[0] ) return -1;
//  if( (*vtx_ndof)[0] <= 2 ) continue; // Our Study
  if( (*vtx_ndof)[0] <= 4 ) return -1; //W&Z Xsec study
  if( (*vtx_z)[0] >= 24 ) return -1;
  if( (*vtx_Rho)[0] >= 2 ) return -1;

  // Count the good vtx
  for( int ivtx(0);ivtx<mVtxVar.nPrim; ivtx++)
  {
    if( (*vtx_isFake)[ivtx] )continue;
//    if( (*vtx_ndof)[ivtx] <= 2 ) continue; // Our Study
    if( (*vtx_ndof)[ivtx] <= 4 ) continue; //W&Z Xsec study
    if( (*vtx_z)[ivtx] >= 24 ) continue;
    if( (*vtx_Rho)[ivtx] >= 2 ) continue;
    mVtxVar.nGood++;
  }
//    if( mVtxVar.nGood < 1 ) continue;
  return 0;
}
