// $Log: MonoJetMET.C,v $
// Revision 1.8  2013/09/13 00:09:32  salee
// *** empty log message ***
//
#define MonoJetMET_cxx
//#include <iostream>
//#include <TROOT.h>                        // access to gROOT, entry point to ROOT system
//#include <TSystem.h>                      // interface to OS
#include <TBenchmark.h>                   // class to track macro running statistics
#include <algorithm>
#include "MonoJetMET.h"
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

void MonoJetMET::Loop()
{
  //gSystem->Load("libMathCore");
  //gSystem->Load("libPhysics");
  //using namespace ROOT::Math;

  Debug=false;
  cout<<"==========================================================="<<endl;
  cout<<"MonoJetMET Analysis with Mode: "<<Mode<<"  AnaChannel: "<<AnaChannel<<endl;
  cout<<"==========================================================="<<endl;
  gBenchmark->Start("MonoJetMET");

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
    //if(MonoJetBase::CheckChannel()!=0) exit(-1); no channel

    //============
    //Trigger Cut
    //============
    //if(MonoJetBase::TriggerCut() !=0) continue;

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

    if( MonoJet.Pass)
    {
      mNTTevt++;
      Fill_METs();
      // Dump MET informations
    }
  }//Ntries
  cout<<"Passed MonoJet evts: "<<mNTTevt<<endl;
  //Results======================
  Fill_METprofiles();
//  TString mResultDir = AnaChannel;
////  TString mResultDir = "results";
//  gSystem->mkdir(mResultDir);

  myFile->Write();
  gBenchmark->Show("MonoJetMET");
}
int MonoJetMET::InitVar()
{
  cout<<"Initialize variable at MonoJetMET class ==========="<<endl;
  evtCnt = 0;
  mNTTevt = 0;
  return 0;
}
int MonoJetMET::InitVar4Evt()
{
  //cout<<"MonoJetMET::InitVar4Evt ==========================="<<endl;
  MonoJetBase::InitVar4Evt();
  return 0;
}
int MonoJetMET::VertexCut()
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
double MonoJetMET::CalcEvtWeight()
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
int MonoJetMET::TTbestSelect()
{
  if(nIdJets >= 1)MonoJet.Pass = true;
 
  MJet.pt = 0;
  for(int i(0);i<pt->size();i++)
  {
    if(MJet.pt < (*pt)[i]) MJet.pt = (*pt)[i];
  }

  return 0;
}
int MonoJetMET::InitHistogram()
{
  myFile=new TFile(mResultDir+"/"+OutNameBase+".root","RECREATE");
  for(int i(0);i<PUrangeBin;i++)
  {
  sprintf(histName,"h1_nIdJets_%d",i);
  h1_nIdJets[i]    = new TH1D(histName,"number of pileupJets",10,0.,10);
  sprintf(histName,"h1_MJetPt_%d",i);
  h1_MJetPt[i]   = new TH1D(histName,"Bigest Jet Pt",60,30.,300);
  sprintf(histName,"h1_PF_Met_%d",i);
  h1_PF_Met[i]     = new TH1D(histName,"PF MET",20,0.,100);
  sprintf(histName,"h1_MVA_Met_%d",i);
  h1_MVA_Met[i]    = new TH1D(histName,"MVA MET",20,0.,100);
  sprintf(histName,"h1_NoPU_Met_%d",i);
  h1_NoPU_Met[i]   = new TH1D(histName,"NoPU MET",20,0.,100);
  sprintf(histName,"h1_genMEtTrue_%d",i);
  h1_genMEtTrue[i] = new TH1D(histName,"genMEtTrue",20,0.,100);

  sprintf(histName,"h2_pfMET_%d",i);
  h2_pfMET[i]   = new TH2D(histName,"pf - genMETTrue",20,0.,100,2100,-100,2000);
  sprintf(histName,"h2_MVaMET_%d",i);
  h2_MVaMET[i]  = new TH2D(histName,"MVA - genMETTrue",20,0.,100,2100,-100,2000);
  sprintf(histName,"h2_NoPuMET_%d",i);
  h2_NoPuMET[i] = new TH2D(histName,"NoPU - genMETTrue",20,0.,100,2100,-100,2000);
  }
  return 0;
}
int MonoJetMET::Fill_METs()
{
  h1_nIdJets[0]->Fill(nIdJets);
  h1_PF_Met[0]->Fill(pfMEtTL.Pt());
  h1_MVA_Met[0]->Fill(MVaMEtTL.Pt());
  h1_NoPU_Met[0]->Fill(NoPuMEtTL.Pt());
  h1_genMEtTrue[0]->Fill(genMEtTrueTL.Pt());
  h1_MJetPt[0]->Fill(MJet.pt);

  h2_pfMET[0]  ->Fill(genMEtTrueTL.Pt(), pfMEtTL.Pt()-genMEtTrueTL.Pt());
  h2_MVaMET[0] ->Fill(genMEtTrueTL.Pt(), MVaMEtTL.Pt()-genMEtTrueTL.Pt());
  h2_NoPuMET[0]->Fill(genMEtTrueTL.Pt(), NoPuMEtTL.Pt()-genMEtTrueTL.Pt());

  if(mVtxVar.nGood>=0 && mVtxVar.nGood<7){
  h1_nIdJets[1]->Fill(nIdJets);
  h1_PF_Met[1]->Fill(pfMEtTL.Pt());
  h1_MVA_Met[1]->Fill(MVaMEtTL.Pt());
  h1_NoPU_Met[1]->Fill(NoPuMEtTL.Pt());
  h1_genMEtTrue[1]->Fill(genMEtTrueTL.Pt());
  h1_MJetPt[1]->Fill(MJet.pt);

  h2_pfMET[1]  ->Fill(genMEtTrueTL.Pt(), pfMEtTL.Pt()-genMEtTrueTL.Pt());
  h2_MVaMET[1] ->Fill(genMEtTrueTL.Pt(), MVaMEtTL.Pt()-genMEtTrueTL.Pt());
  h2_NoPuMET[1]->Fill(genMEtTrueTL.Pt(), NoPuMEtTL.Pt()-genMEtTrueTL.Pt());
  }
  else if(mVtxVar.nGood>=7 && mVtxVar.nGood<21){
  h1_nIdJets[2]->Fill(nIdJets);
  h1_PF_Met[2]->Fill(pfMEtTL.Pt());
  h1_MVA_Met[2]->Fill(MVaMEtTL.Pt());
  h1_NoPU_Met[2]->Fill(NoPuMEtTL.Pt());
  h1_genMEtTrue[2]->Fill(genMEtTrueTL.Pt());
  h1_MJetPt[2]->Fill(MJet.pt);

  h2_pfMET[2]  ->Fill(genMEtTrueTL.Pt(), pfMEtTL.Pt()-genMEtTrueTL.Pt());
  h2_MVaMET[2] ->Fill(genMEtTrueTL.Pt(), MVaMEtTL.Pt()-genMEtTrueTL.Pt());
  h2_NoPuMET[2]->Fill(genMEtTrueTL.Pt(), NoPuMEtTL.Pt()-genMEtTrueTL.Pt());
  }
  else if(mVtxVar.nGood>=21){
  h1_nIdJets[3]->Fill(nIdJets);
  h1_PF_Met[3]->Fill(pfMEtTL.Pt());
  h1_MVA_Met[3]->Fill(MVaMEtTL.Pt());
  h1_NoPU_Met[3]->Fill(NoPuMEtTL.Pt());
  h1_genMEtTrue[3]->Fill(genMEtTrueTL.Pt());
  h1_MJetPt[3]->Fill(MJet.pt);
  h2_pfMET[3]  ->Fill(genMEtTrueTL.Pt(), pfMEtTL.Pt()-genMEtTrueTL.Pt());
  h2_MVaMET[3] ->Fill(genMEtTrueTL.Pt(), MVaMEtTL.Pt()-genMEtTrueTL.Pt());
  h2_NoPuMET[3]->Fill(genMEtTrueTL.Pt(), NoPuMEtTL.Pt()-genMEtTrueTL.Pt());
  }

  return 0;
}
int MonoJetMET::Fill_METprofiles()
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

