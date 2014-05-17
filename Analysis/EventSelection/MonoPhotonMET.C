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
  Fill_METprofiles();
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
    h1_PhotonpT[0]->Fill((*Pho_pt)[MonoPhoton.idxBest]);
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
  h2_pfMET_pxpy  = new TH2D("h2_pfMET_pxpy","pfMET pxpy",100,-1000,1000,100,-1000,1000);
  h2_MVaMET_pxpy  = new TH2D("h2_MVaMET_pxpy","MVaMET pxpy",100,-1000,1000,100,-1000,1000);
  h2_NoPuMET_pxpy  = new TH2D("h2_NoPuMET_pxpy","NoPuMET pxpy",100,-1000,1000,100,-1000,1000);
  for(int i(0);i<PUrangeBin;i++)
  {
  sprintf(histName,"h1_nIdJets_%d",i);
  h1_nIdJets[i]    = new TH1D(histName,"number of pileupJets",10,0.,10);
  sprintf(histName,"h1_PhotonpT_%d",i);
  h1_PhotonpT[i]   = new TH1D(histName,"Bigest Photon Pt",60,30.,300);
  sprintf(histName,"h1_PF_Met_%d",i);
  h1_PF_Met[i]     = new TH1D(histName,"PF MET",20,0.,80);
  sprintf(histName,"h1_MVA_Met_%d",i);
  h1_MVA_Met[i]    = new TH1D(histName,"MVA MET",20,0.,80);
  sprintf(histName,"h1_NoPU_Met_%d",i);
  h1_NoPU_Met[i]   = new TH1D(histName,"NoPU MET",20,0.,80);
  sprintf(histName,"h1_genMEtTrue_%d",i);
  h1_genMEtTrue[i] = new TH1D(histName,"genMEtTrue",20,0.,80);

  sprintf(histName,"h2_pfMET_%d",i);
  h2_pfMET[i]   = new TH2D(histName,"pf - genMETTrue",20,0.,80,2100,-100,2000);
  sprintf(histName,"h2_MVaMET_%d",i);
  h2_MVaMET[i]  = new TH2D(histName,"MVA - genMETTrue",20,0.,80,2100,-100,2000);
  sprintf(histName,"h2_NoPuMET_%d",i);
  h2_NoPuMET[i] = new TH2D(histName,"NoPU - genMETTrue",20,0.,80,2100,-100,2000);
  }

  return 0;
}
int MonoPhotonMET::Fill_METs()
{
  h2_pfMET_pxpy ->Fill(pfMEt_x, pfMEt_y);
  h2_MVaMET_pxpy ->Fill(MVaMEt_x, MVaMEt_y);
  h2_NoPuMET_pxpy ->Fill(NoPuMEt_x, NoPuMEt_y);

  //h1_nIdJets[0]->Fill(nIdJets);
  h1_PF_Met[0]->Fill(pfMEtTL.Pt());
  h1_MVA_Met[0]->Fill(MVaMEtTL.Pt());
  h1_NoPU_Met[0]->Fill(NoPuMEtTL.Pt());
  h1_genMEtTrue[0]->Fill(genMEtTrueTL.Pt());
  //h1_PhotonpT[0]->Fill(MPhoton.pt);

  h2_pfMET[0]  ->Fill(genMEtTrueTL.Pt(), pfMEtTL.Pt()-genMEtTrueTL.Pt());
  h2_MVaMET[0] ->Fill(genMEtTrueTL.Pt(), MVaMEtTL.Pt()-genMEtTrueTL.Pt());
  h2_NoPuMET[0]->Fill(genMEtTrueTL.Pt(), NoPuMEtTL.Pt()-genMEtTrueTL.Pt());

  if(mVtxVar.nGood>=0 && mVtxVar.nGood<7){
  //h1_nIdJets[1]->Fill(nIdJets);
  h1_PF_Met[1]->Fill(pfMEtTL.Pt());
  h1_MVA_Met[1]->Fill(MVaMEtTL.Pt());
  h1_NoPU_Met[1]->Fill(NoPuMEtTL.Pt());
  h1_genMEtTrue[1]->Fill(genMEtTrueTL.Pt());
  //h1_PhotonpT[1]->Fill(MPhoton.pt);

  h2_pfMET[1]  ->Fill(genMEtTrueTL.Pt(), pfMEtTL.Pt()-genMEtTrueTL.Pt());
  h2_MVaMET[1] ->Fill(genMEtTrueTL.Pt(), MVaMEtTL.Pt()-genMEtTrueTL.Pt());
  h2_NoPuMET[1]->Fill(genMEtTrueTL.Pt(), NoPuMEtTL.Pt()-genMEtTrueTL.Pt());
  }
  else if(mVtxVar.nGood>=7 && mVtxVar.nGood<21){
  //h1_nIdJets[2]->Fill(nIdJets);
  h1_PF_Met[2]->Fill(pfMEtTL.Pt());
  h1_MVA_Met[2]->Fill(MVaMEtTL.Pt());
  h1_NoPU_Met[2]->Fill(NoPuMEtTL.Pt());
  h1_genMEtTrue[2]->Fill(genMEtTrueTL.Pt());
  //h1_PhotonpT[3]->Fill(MPhoton.pt);

  h2_pfMET[2]  ->Fill(genMEtTrueTL.Pt(), pfMEtTL.Pt()-genMEtTrueTL.Pt());
  h2_MVaMET[2] ->Fill(genMEtTrueTL.Pt(), MVaMEtTL.Pt()-genMEtTrueTL.Pt());
  h2_NoPuMET[2]->Fill(genMEtTrueTL.Pt(), NoPuMEtTL.Pt()-genMEtTrueTL.Pt());
  }
  else if(mVtxVar.nGood>=21){
  //h1_nIdJets[3]->Fill(nIdJets);
  h1_PF_Met[3]->Fill(pfMEtTL.Pt());
  h1_MVA_Met[3]->Fill(MVaMEtTL.Pt());
  h1_NoPU_Met[3]->Fill(NoPuMEtTL.Pt());
  h1_genMEtTrue[3]->Fill(genMEtTrueTL.Pt());
  //h1_PhotonpT[3]->Fill(MPhoton.pt);

  h2_pfMET[3]  ->Fill(genMEtTrueTL.Pt(), pfMEtTL.Pt()-genMEtTrueTL.Pt());
  h2_MVaMET[3] ->Fill(genMEtTrueTL.Pt(), MVaMEtTL.Pt()-genMEtTrueTL.Pt());
  h2_NoPuMET[3]->Fill(genMEtTrueTL.Pt(), NoPuMEtTL.Pt()-genMEtTrueTL.Pt());
  }

  return 0;
}
int MonoPhotonMET::Fill_METprofiles()
{
 h2_pfMET[0]->ProfileX("pfMET_0",1,-1,"");
 h2_MVaMET[0]->ProfileX("MVaMET_0",1,-1,"");
 h2_NoPuMET[0]->ProfileX("NoPuMET_0",1,-1,"");
 h2_pfMET[1]->ProfileX("pfMET_1",1,-1,"");
 h2_MVaMET[1]->ProfileX("MVaMET_1",1,-1,"");
 h2_NoPuMET[1]->ProfileX("NoPuMET_1",1,-1,"");
 h2_pfMET[2]->ProfileX("pfMET_2",1,-1,"");
 h2_MVaMET[2]->ProfileX("MVaMET_2",1,-1,"");
 h2_NoPuMET[2]->ProfileX("NoPuMET_2",1,-1,"");
 h2_pfMET[3]->ProfileX("pfMET_3",1,-1,"");
 h2_MVaMET[3]->ProfileX("MVaMET_3",1,-1,"");
 h2_NoPuMET[3]->ProfileX("NoPuMET_3",1,-1,"");

 return 0;
}
