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
  cout<<"Passed TTsemi evts: "<<mNTTevt<<endl;
  //Results======================
  Fill_METprofiles();
//  TString mResultDir = AnaChannel;
////  TString mResultDir = "results";
//  gSystem->mkdir(mResultDir);

  myFile->Write();
  gBenchmark->Show("TTsemiMET");
}
int TTsemiMET::InitVar()
{
  cout<<"Initialize variable at TTsemiMET class ==========="<<endl;
  evtCnt = 0;
  mNTTevt = 0;
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
    if( ((AnaChannel == "MuonLoPU" ) && (MuonCut2012LoPU(i) >0))||
	((AnaChannel == "Muon2012") && (MuonCut2012(i) >0))||
	((AnaChannel == "ElectronLoPU" ) && (ElectronCut2012LoPU(i) > 0))||
	((AnaChannel =="Electron2012") &&  (ElectronCut2012(i) > 0)) ||
	((AnaChannel =="Tau2012") && (TauCut(i)) > 0)
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
  myFile=new TFile(mResultDir+"/"+OutNameBase+".root","RECREATE");
  h1_nIdJets   = new TH1D("h1_nIdJets","number of pileupJets",10,0.,10);
  h1_PF_Met   = new TH1D("h1_PF_Met","PF MET",50,0.,200);
  h1_MVA_Met   = new TH1D("h1_MVA_Met","MVA MET",50,0.,200);
  h1_NoPU_Met  = new TH1D("h1_NoPU_Met","NoPU MET",50,0.,200);
  h1_genMEtTrue= new TH1D("h1_genMEtTrue","genMEtTrue",50,0.,200);

  h2_pfMET  = new TH2D("h2_pfMET","pf - genMETTrue",20,0.,80,2100,-100,2000);
  h2_MVaMET = new TH2D("h2_MVaMET","MVA - genMETTrue",20,0.,80,2100,-100,2000);
  h2_NoPuMET= new TH2D("h2_NoPuMET","NoPU - genMETTrue",20,0.,80,2100,-100,2000);

//  hp_pfMet  = new TProfile("hp_pfMet","pf - genMetTrue",50,0.,200);
//  hp_MVaMet = new TProfile("hp_MVaMet","MVA - genMetTrue",50,0.,200);
//  hp_NoPuMet= new TProfile("hp_NoPuMet","NoPU - genMetTrue",50,0.,200);
  return 0;
}
int TTsemiMET::Fill_METs()
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
int Fill_METprofiles()
{
  h2_pfMET->ProfileX("pfMET",1,-1,"");
  h2_MVaMET->ProfileX("MVaMET",1,-1,"");
  h2_NoPuMET->ProfileX("NoPuMET",1,-1,"");

  return 0;
}
