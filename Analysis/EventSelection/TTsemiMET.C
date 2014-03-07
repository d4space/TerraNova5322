// $Log: TTsemiMET.C,v $
// Revision 1.8  2013/09/13 00:09:32  salee
// *** empty log message ***
//
#define TTsemiMET_cxx
//#include <iostream>
//#include <TROOT.h>                        // access to gROOT, entry point to ROOT system
//#include <TSystem.h>                      // interface to OS
#include <TBenchmark.h>                   // class to track macro running statistics
#include <algorithm>
#include "TTsemiMET.h"
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

void TTsemiMET::Loop()
{
  //gSystem->Load("libMathCore");
  //gSystem->Load("libPhysics");
  //using namespace ROOT::Math;

  Debug=false;
  cout<<"==========================================================="<<endl;
  cout<<"TTsemiMET Analysis with Mode: "<<Mode<<"  AnaChannel: "<<AnaChannel<<endl;
  cout<<"==========================================================="<<endl;
  gBenchmark->Start("TTsemiMET");

  gRandom->SetSeed(0);
//
  if (fChain == 0) return;
   //int Ntries = fChain->GetEntriesFast(); this gives 1234567890 kkk
  Ntries = fChain->GetEntries();

  cout<<"Total: "<<Ntries<<endl;

  gSystem->mkdir(mResultDir);

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
    if(TTsemiBase::CheckChannel()!=0) exit(-1);

    //============
    //Trigger Cut
    //============
    //if(TTsemiBase::TriggerCut() !=0) continue;

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

    if( TTsemi.Pass)
    {
      mNTTevt++;
      Fill_METs();
      // Dump MET informations
    }
  }//Ntries
  cout<<"Passed W evts: "<<mNTTevt<<"   Passed Z evts: "<<mNZevt<<endl;
  //Results======================

//  TString mResultDir = AnaChannel;
////  TString mResultDir = "results";
//  gSystem->mkdir(mResultDir);
  TFile *myFile;
    myFile=new TFile(mResultDir+"/"+OutFileName+".root","RECREATE");

  myFile->Write();
  gBenchmark->Show("TTsemiMET");
}
int TTsemiMET::InitVar()
{
  cout<<"Initialize variable at TTsemiMET class ==========="<<endl;
  evtCnt = 0;
  mNTTevet = 0;
  return 0;
}
int TTsemiMET::InitVar4Evt()
{
  //cout<<"TTsemiMET::InitVar4Evt ==========================="<<endl;
  TTsemiBase::InitVar4Evt();
  return 0;
}
int TTsemiMET::VertexCut()
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
double TTsemiMET::CalcEvtWeight()
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
int TTsemiMET::TTbestSelect()
{
  for(int i(0); i<TTsemi.size; i++)
  {
    if( ((AnaChannel == "MuonLowPU" ) && (MuonCut(i) >0))||
	((AnaChannel == "MuonHighPU") && (MuonCut(i) >0))||
	((AnaChannel == "ElectronLowPU" ) && (ElectronCut(i) > 0))||
	((AnaChannel =="ElectronHighPU") &&  (ElectronCutHighPU(i) > 0)) ||
	((AnaChannel =="TauHighPU") && (TauCut(i)) > 0)
	  //Best Candidate selection
    )
    {
	TTsemi.Pass = true;
    }//Cut and Bigger pt
  }

  return 0;
}
int TTsemiMET::InitHistogram()
{
  return 0;
}
int TTsemiMET::Fill_METs()
{
  return 0;
}
