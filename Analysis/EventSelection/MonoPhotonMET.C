// $Log: MonoPhotonMET.C,v $
// Revision 1.8  2013/09/13 00:09:32  salee
// *** empty log message ***
//
#define MonoPhotonMET_cxx
//#include <iostream>
//#include <TROOT.h>                        // access to gROOT, entry point to ROOT system
//#include <TSystem.h>                      // interface to OS
#include <TBenchmark.h>                   // class to track macro running statistics
#include <algorithm>
#include "MonoPhotonMET.h"
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

void MonoPhotonMET::Loop()
{
  //gSystem->Load("libMathCore");
  //gSystem->Load("libPhysics");
  //using namespace ROOT::Math;

  Debug=false;
  cout<<"==========================================================="<<endl;
  cout<<"MonoPhotonMET Analysis with Mode: "<<Mode<<"  AnaChannel: "<<AnaChannel<<endl;
  cout<<"==========================================================="<<endl;
  gBenchmark->Start("MonoPhotonMET");

  gRandom->SetSeed(0);

//
  if (fChain == 0) return;
   //int Ntries = fChain->GetEntriesFast(); this gives 1234567890 kkk
  Ntries = fChain->GetEntries();

  cout<<"Total: "<<Ntries<<endl;

  //============================================
  // Looping for each Event 
  //============================================
  for (int i(0); i<Ntries;i++)
  {
    evtCnt = i;
    if(i % 100000 == 0) cout<<i<<"th event"<<endl;

    fChain->GetEntry(i);
    //===========================
    //Initialization of Variables
    //===========================
    InitVar4Evt();

    DumpMETs();

    //===================
    // Check the channel : To check if the ntuple is for each lepton flavor
    //===================
    //if(MonoPhotonBase::CheckChannel()!=0) exit(-1); no channel

    //============
    //Trigger Cut
    //============
    //if(MonoPhotonBase::TriggerCut() !=0) continue;

    //Vertex Study===========================
    if(VertexCut() !=0) continue;

    //===================
    // Calculate Event Weight
    //=====================
    //mTTW = CalcEvtWeight();

    //cout<<"Muon size: "<<wMuons.pt->size()<<endl;
    //cout<<"W    size: "<<W_pt->size()<<endl;
    // Select the Best W boson
    Photonbest();

    if( MonoPhoton.Pass)
    {//cout<<"enent = "<<i<<endl;
      mNTTevt++;
      Fill_METs();
      // Dump MET informations
    }
  }//Ntries
  cout<<"Passed MonoPhoton evts: "<<mNTTevt<<endl;
  //Results======================

//  TString mResultDir = AnaChannel;
////  TString mResultDir = "results";
//  gSystem->mkdir(mResultDir);

  myFile->Write();
  gBenchmark->Show("MonoPhotonMET");
}
int MonoPhotonMET::InitVar()
{
  cout<<"Initialize variable at MonoPhotonMET class ==========="<<endl;
  evtCnt = 0;
  mNTTevt = 0;
  return 0;
}
int MonoPhotonMET::InitVar4Evt()
{
  //cout<<"MonoPhotonMET::InitVar4Evt ==========================="<<endl;
  MonoPhotonBase::InitVar4Evt();
  return 0;
}
int MonoPhotonMET::VertexCut()
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
double MonoPhotonMET::CalcEvtWeight()
{
  if(!RunOnMC){mTTW = 1;return mTTW;}
      //mTTW= LumiWeight*weightin; //weight is right but S8 strange
      //if (weightFSR<0) weightFSR=1.;
      //mTTW= LumiWeight*weightFSR; //weight is right but S8 strange
  mTTW= LumiWeight; //weight is right but S8 strange
  if(AnaChannel == "ElectronHighPU")
  {
    mTTW= LumiWeight*weight;} //reweighting value for S10
  return mTTW;
}

int MonoPhotonMET::Photonbest()
{
  double PhotonpT;
  for(int ip(0);ip<Pho_pt->size();ip++)
  {
    PhotonpT = (*Pho_pt)[ip];
    if( PhotonpT < (*Pho_pt)[ip])
    {
     MonoPhoton.idxBest = ip;
    }

    //h1_PhotonpT->Fill(MonoPhoton.PhotonpT);
    h1_PhotonpT->Fill((*Pho_pt)[MonoPhoton.idxBest]);
    //if(MonoPhoton.PhotonpT > 30)MonoPhoton.Pass = true;
    if((*Pho_pt)[MonoPhoton.idxBest] > 30)MonoPhoton.Pass = true;
   // if(MonoPhoton.Pass)
   // {cout<<"size = "<<Pho_pt->size()<<endl;}
  }
  return 0;
}

int MonoPhotonMET::InitHistogram()
{
  myFile=new TFile(mResultDir+"/"+OutNameBase+".root","RECREATE");
  //h1_nIdJets   = new TH1D("h1_nIdJets","number of pileupJets",10,0.,10);
  //h1_MPhotonPt   = new TH1D("h1_MPhotonPt","Bigest Photon Pt",60,3.,300);
  h1_PhotonpT   = new TH1D("h1_MPhotonPt","Bigest Photon Pt",50,0.,500);
  h1_PF_Met   = new TH1D("h1_PF_Met","PF MET",50,0.,100);
  h1_MVA_Met   = new TH1D("h1_MVA_Met","MVA MET",50,0.,100);
  h1_NoPU_Met  = new TH1D("h1_NoPU_Met","NoPU MET",50,0.,100);
  h1_genMEtTrue= new TH1D("h1_genMEtTrue","genMEtTrue",50,0.,100);

  h2_pfMET  = new TH2D("h2_pfMET","pf - genMETTrue",20,0.,80,2100,-100,2000);
  h2_MVaMET = new TH2D("h2_MVaMET","MVA - genMETTrue",20,0.,80,2100,-100,2000);
  h2_NoPuMET= new TH2D("h2_NoPuMET","NoPU - genMETTrue",20,0.,80,2100,-100,2000);
  
  hp_pfMet  = new TProfile("hp_pfMet","pf - genMetTrue",20,0.,80);
  hp_MVaMet = new TProfile("hp_MVaMet","MVA - genMetTrue",20,0.,80);
  hp_NoPuMet= new TProfile("hp_NoPuMet","NoPU - genMetTrue",20,0.,80);
  return 0;
}
int MonoPhotonMET::Fill_METs()
{
  //h1_nIdJets->Fill(nIdJets);
  h1_PF_Met->Fill(pfMEtTL.Pt());
  h1_MVA_Met->Fill(MVaMEtTL.Pt());
  h1_NoPU_Met->Fill(NoPuMEtTL.Pt());
  h1_genMEtTrue->Fill(genMEtTrueTL.Pt());
 // h1_MPhotonPt->Fill(MPhoton.pt);

  h2_pfMET  ->Fill(genMEtTrueTL.Pt(), pfMEtTL.Pt()-genMEtTrueTL.Pt());
  h2_MVaMET ->Fill(genMEtTrueTL.Pt(), MVaMEtTL.Pt()-genMEtTrueTL.Pt());
  h2_NoPuMET->Fill(genMEtTrueTL.Pt(), NoPuMEtTL.Pt()-genMEtTrueTL.Pt());
  
  h2_pfMET->ProfileX("pfMET",1,-1,"");
  h2_MVaMET->ProfileX("MVaMET",1,-1,"");
  h2_NoPuMET->ProfileX("NoPuMET",1,-1,"");

//  h2_NoPuMET->ProfileY("pfy",1,-1,"");
//  h2_NoPuMET->ProjectionX("px",1,-1,"");
//  h2_NoPuMET->ProjectionY("py",1,-1,"");
//  h2_NoPuMET->SetShowProjectionX(1);
//  h2_NoPuMET->SetShowProjectionY(1);

  hp_pfMet  ->Fill(genMEtTrueTL.Pt(), pfMEtTL.Pt()-genMEtTrueTL.Pt());
  hp_MVaMet ->Fill(genMEtTrueTL.Pt(), MVaMEtTL.Pt()-genMEtTrueTL.Pt());
  hp_NoPuMet->Fill(genMEtTrueTL.Pt(), NoPuMEtTL.Pt()-genMEtTrueTL.Pt());

  return 0;
}
