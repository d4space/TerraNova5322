// $Log: TT2HadMET.C,v $
// Revision 1.8  2013/09/13 00:09:32  salee
// *** empty log message ***
//
#define TT2HadMET_cxx
//#include <iostream>
//#include <TROOT.h>                        // access to gROOT, entry point to ROOT system
//#include <TSystem.h>                      // interface to OS
#include <TBenchmark.h>                   // class to track macro running statistics
#include <algorithm>
#include "TT2HadMET.h"
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

void TT2HadMET::Loop()
{
  //gSystem->Load("libMathCore");
  //gSystem->Load("libPhysics");
  //using namespace ROOT::Math;

  Debug=false;
  cout<<"==========================================================="<<endl;
  cout<<"TT2HadMET Analysis with Mode: "<<Mode<<"  AnaChannel: "<<AnaChannel<<endl;
  cout<<"==========================================================="<<endl;
  gBenchmark->Start("TT2HadMET");

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
    //if(TT2HadBase::CheckChannel()!=0) exit(-1); no channel

    //============
    //Trigger Cut
    //============
    //if(TT2HadBase::TriggerCut() !=0) continue;

    //Vertex Study===========================
    if(VertexCut() !=0) continue;

    //===================
    // Calculate Event Weight
    //=====================
    //mTTW = CalcEvtWeight();
    
    //cout<<"Muon size: "<<wMuons.pt->size()<<endl;
    //cout<<"W    size: "<<W_pt->size()<<endl;
    // Select the Best W boson
    TTbestSelect();

    if( TT2Had.Pass)
    {
      mNTTevt++;
      Fill_METs();
      // Dump MET informations
    }
  }//Ntries
  cout<<"Passed TT2Had evts: "<<mNTTevt<<endl;
  //Results======================
  Fill_METprofiles();
//  TString mResultDir = AnaChannel;
////  TString mResultDir = "results";
//  gSystem->mkdir(mResultDir);

  myFile->Write();
  gBenchmark->Show("TT2HadMET");
}
int TT2HadMET::InitVar()
{
  cout<<"Initialize variable at TT2HadMET class ==========="<<endl;
  evtCnt = 0;
  mNTTevt = 0;
  return 0;
}
int TT2HadMET::InitVar4Evt()
{
  //cout<<"TT2HadMET::InitVar4Evt ==========================="<<endl;
  TT2HadBase::InitVar4Evt();
  return 0;
}
int TT2HadMET::VertexCut()
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
double TT2HadMET::CalcEvtWeight()
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
int TT2HadMET::TTbestSelect()
{
  if(TT_nIdJets >= 6)TT2Had.Pass = true;
  return 0;
}
int TT2HadMET::InitHistogram()
{
  myFile=new TFile(mResultDir+"/"+OutNameBase+".root","RECREATE");
  h1_nIdJets   = new TH1D("h1_nIdJets","number of pileupJets",10,0.,10);
  h1_PF_Met   = new TH1D("h1_PF_Met","PF MET",50,0.,100);
  h1_MVA_Met   = new TH1D("h1_MVA_Met","MVA MET",50,0.,100);
  h1_NoPU_Met  = new TH1D("h1_NoPU_Met","NoPU MET",50,0.,100);
  h1_genMEtTrue= new TH1D("h1_genMEtTrue","genMEtTrue",50,0.,100);

  h2_pfMET  = new TH2D("h2_pfMET","pf - genMETTrue",20,0.,100,2100,-100,2000);
  h2_MVaMET = new TH2D("h2_MVaMET","MVA - genMETTrue",20,0.,100,2100,-100,2000);
  h2_NoPuMET= new TH2D("h2_NoPuMET","NoPU - genMETTrue",20,0.,100,2100,-100,2000);

//  hp_pfMet  = new TProfile("hp_pfMet","pf - genMetTrue",50,0.,100);
//  hp_MVaMet = new TProfile("hp_MVaMet","MVA - genMetTrue",50,0.,100);
//  hp_NoPuMet= new TProfile("hp_NoPuMet","NoPU - genMetTrue",50,0.,100);
  return 0;
}
int TT2HadMET::Fill_METs()
{
  h1_nIdJets->Fill(TT_nIdJets);
  h1_PF_Met->Fill(pfMEtTL.Pt());
  h1_MVA_Met->Fill(MVaMEtTL.Pt());
  h1_NoPU_Met->Fill(NoPuMEtTL.Pt());
  h1_genMEtTrue->Fill(genMEtTrueTL.Pt());

  h2_pfMET  ->Fill(genMEtTrueTL.Pt(), pfMEtTL.Pt()-genMEtTrueTL.Pt());
  h2_MVaMET ->Fill(genMEtTrueTL.Pt(), MVaMEtTL.Pt()-genMEtTrueTL.Pt());
  h2_NoPuMET->Fill(genMEtTrueTL.Pt(), NoPuMEtTL.Pt()-genMEtTrueTL.Pt());

//  hp_pfMet  ->Fill(genMEtTrueTL.Pt(), pfMEtTL.Pt()-genMEtTrueTL.Pt());
//  hp_MVaMet ->Fill(genMEtTrueTL.Pt(), MVaMEtTL.Pt()-genMEtTrueTL.Pt());
//  hp_NoPuMet->Fill(genMEtTrueTL.Pt(), NoPuMEtTL.Pt()-genMEtTrueTL.Pt());

  return 0;
}
int TT2HadMET::Fill_METprofiles()
{
  h2_pfMET->ProfileX("pfMET",1,-1,"");
  h2_MVaMET->ProfileX("MVaMET",1,-1,"");
  h2_NoPuMET->ProfileX("NoPuMET",1,-1,"");
 
  return 0;
}
