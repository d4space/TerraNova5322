// $Log: WlnuMET.C,v $
// Revision 1.8  2013/09/13 00:09:32  salee
// *** empty log message ***
//
// Revision 1.7  2013/09/12 05:10:29  sangilpark
// *** empty log message ***
//
// Revision 1.6  2013/08/31 06:56:40  khakim
// *** empty log message ***
//
#define WlnuMET_cxx
//#include <iostream>
//#include <TROOT.h>                        // access to gROOT, entry point to ROOT system
//#include <TSystem.h>                      // interface to OS
#include <TBenchmark.h>                   // class to track macro running statistics
#include <algorithm>
#include "WlnuMET.h"
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

void WlnuMET::Loop()
{
  //gSystem->Load("libMathCore");
  //gSystem->Load("libPhysics");
  //using namespace ROOT::Math;

  Debug=false;
  cout<<"==========================================================="<<endl;
  cout<<"WlnuMET Analysis with Mode: "<<Mode<<"  AnaChannel: "<<AnaChannel<<endl;
  cout<<"==========================================================="<<endl;
  gBenchmark->Start("WlnuMET");

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
    //===============================
    //W study
    //===============================
    if(i % 100000 == 0) cout<<i<<"th event"<<endl;
    if(Debug)cout<<"check point 1"<<endl;

    fChain->GetEntry(i);
    //===========================
    //Initialization of Variables
    //===========================
    InitVar4Evt();

    // Dump MET informations
    DumpMETs();

    //===================
    // Check the channel : To check if the ntuple is for each lepton flavor
    //===================
    if(WlnuBase::CheckChannel()!=0) exit(-1);

    //============
    //Trigger Cut
    //============
    //if(WlnuBase::TriggerCut() !=0) continue;

    //Vertex Study===========================
    if(VertexCut() !=0) continue;


    //===================
    // Calculate Event Weight
    //=====================
    mTTW = 1;
    //mTTW = CalcEvtWeight();
    
    //cout<<"Muon size: "<<wMuons.pt->size()<<endl;
    //cout<<"W    size: "<<W_pt->size()<<endl;

   
    // Select the Best W boson
    WbestSelect();


    if( W.Pass)
    {
    }

    //Fill the W==================
    if( W.Pass && addLepN <2 ){
      //DumpWbestCand(W.idxBest);

      // Efficiency Correction
      Fill_METs();
    
    //cout<<"mTTW: "<<mTTW<<endl;
    evtSelected+=mTTW;
    
    }//good W

  }//Ntries
  cout<<"Passed W evts: "<<mNWevt<<endl;
  //Results======================
  Fill_METprofiles();
  cout<<"selected converted: "<<evtSelected<<" +- "<<TMath::Sqrt(evtSelected)<<endl;

  myFile->Write();
  gBenchmark->Show("WlnuMET");
}


void WlnuMET::Nselected4Bin()
{
  for(int i(0);i<NwPtBin;i++)
  {
    if( W.pt >= WptBins[i] && W.pt <WptBins[i+1]) mNselected4Bin[i]+=mTTW;
  }
}
int WlnuMET::InitVar()
{
  cout<<"Initialize variable at WlnuMET class ==========="<<endl;
  evtCnt = 0;
  mNWevt = 0;
  for(int i(0);i<NwPtBin;i++)
  {
    mNselected4Bin[i]=0;
  }
  // Recoil Correction initialization
  // Recoil Correction Parameter Files
  if( (  Mode == "AllCorrectionsMC"
      || Mode == "RecoilCorrMC")
      || Mode =="DumpUnfInfo" )
  {
    //if(AnaChannel == "MuonLowPU")
    if(AnaChannel == "MuonLowPU" )
    {
      Rcl.ZRDfilename="../Recoil/ZmmData/fits.root";
      Rcl.ZMCfilename="../Recoil/ZmmMC/fits.root";
      Rcl.Wpfilename="../Recoil/WmpMC/fits.root";
      Rcl.Wmfilename="../Recoil/WmmMC/fits.root";
    }else if((AnaChannel == "ElectronLowPU" ) || AnaChannel == "ElectronHighPU" )
    {
      Rcl.ZRDfilename="../Recoil/ZeeData/fits.root";
      Rcl.ZMCfilename="../Recoil/ZeeMC/fits.root";
      Rcl.Wpfilename="../Recoil/WepMC/fits.root";
      Rcl.Wmfilename="../Recoil/WemMC/fits.root";
    }
    // RecoilCorrection Object.
    RecoilCorr= new RecoilCorrector(
      Rcl.ZRDfilename,
      Rcl.Wpfilename,Rcl.Wmfilename,
      Rcl.ZMCfilename,
      0x1234);
  //Int_t iSeed=0xDEADBEEF default seed for random number generator at constructor
  }
  return 0;
}
int WlnuMET::InitVar4Evt()
{
  //cout<<"WlnuMET::InitVar4Evt ==========================="<<endl;
  WlnuBase::InitVar4Evt();
  return 0;
}
int WlnuMET::VertexCut()
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
double WlnuMET::CalcEvtWeight()
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
int WlnuMET::WbestSelect()
{
  for(int iw(0); iw<W.size; iw++)
  {
    //additional lepton count
    if(AnaChannel == "Muon2012LoPU" ) if(AddMuonCut(iw)>0) addLepN++;
    if(AnaChannel == "Muon2012")    if(AddMuonCut(iw)>0) addLepN++;
    if(AnaChannel == "Electron2012LoPU")if(AddElectronCut(iw)>0)addLepN++;
    if(AnaChannel == "Electron2012")if(AddElectronCutHighPU(iw)>0) addLepN++;
    if(AnaChannel == "Tau2012")if(TauCut(iw)>0) addLepN++;

    if( ((AnaChannel == "Muon2012LoPU" ) && (MuonCut(iw) >0))||
	((AnaChannel == "Muon2012") && (MuonCut(iw) >0))||
	((AnaChannel == "Electron2012LoPU")&& (ElectronCut(iw) > 0))||
	((AnaChannel =="Electron2012") &&(ElectronCutHighPU(iw) > 0)) ||
	((AnaChannel =="Tau2012") && (TauCut(iw)) > 0)
	  //Best Candidate selection
    )if( W.lep_pt < (*W_Lept1_pt)[iw])
    {
	W.idxBest = iw;
	W.Pass = true;

    }//Cut and Bigger pt

  }
  return 0;
}
/*
Int_t WlnuMET::FillUnfoldInfo()
{
  h1_Truth_Rec->Fill(W.pt,mTTW);
  h1_Truth_Post->Fill(genInfo.PostW_pt,mTTW);
  if( evtCnt % 2 == 0 )
  {
      h1_Truth_Rec_Even->Fill(W.pt,mTTW);
      h1_Truth_Post_Even->Fill(genInfo.PostW_pt,mTTW);
    }else{              
      h1_Truth_Rec_Odd->Fill(W.pt,mTTW);
      h1_Truth_Post_Odd->Fill(genInfo.PostW_pt,mTTW);
    }
    //h2_Truth_Rec_AP_Post->Fill(W.pt,genInfo.PostW_pt,mTTW);
    h2_Truth_Rec_AP_Post->Fill(W.pt,genInfo.PostW_pt);

    unfoldInfo.recoPreFsrGenWptRes = (W.pt-genInfo.BornW_pt)/genInfo.BornW_pt;
    unfoldInfo.recoPstFsrGenWptRes = (W.pt-genInfo.PostW_pt)/genInfo.PostW_pt;
    h1_W_pt_RecoPreFsrGenRes[0]->Fill(unfoldInfo.recoPreFsrGenWptRes);
    h1_W_pt_RecoPstFsrGenRes[0]->Fill(unfoldInfo.recoPstFsrGenWptRes);
    for(int ipt(0);ipt<NWptBinPlus-1;ipt++)
    {
      if(genInfo.BornW_pt > Bins[ipt] && genInfo.BornW_pt < Bins[ipt+1])
      {
        h1_W_pt_RecoPreFsrGenRes[ipt+1]->Fill(unfoldInfo.recoPreFsrGenWptRes);
        h1_W_pt_RecoPstFsrGenRes[ipt+1]->Fill(unfoldInfo.recoPstFsrGenWptRes);
      }
      //if(genInfo.PostW_pt > Bins[ipt] && genInfo.PostW_pt < Bins[ipt+1])
      //{
      //  h1_pstFsr2ReconW_pt[ipt]->Fill(W.pt);
      //}
    }
    //We've found the gen match, and get out of here
    //if( AnaChannel=="ElectronLowPU")
    //{
    //  if( W.charge > 0)
    //  {
    //    SF = ElePlusEffiCorrection(W.lep_pt,W.lep_etaSC);
    //  }
    //  else  if( W.charge < 0)
    //  {
    //    SF = EleMinusEffiCorrection(W.lep_pt,W.lep_etaSC);
    //  }
    //}
    //if( AnaChannel=="MuonLowPU" || AnaChannel=="MuonHighPU")
    //{
    //  if( W.charge > 0)
    //  {
    //    SF = MuonPlusEffiCorrection(W.lep_pt,W.lep_eta);
    //  }
    //  else  if( W.charge < 0)
    //  {
    //    SF = MuonMinusEffiCorrection(W.lep_pt,W.lep_eta);
    //  }
    //}
    h1_Truth_Post_EffCorr->Fill(genInfo.PostW_pt,mTTW*mEffSf);
    if(weightFSR<0) weightFSR=1;
    h1_Truth_Post_EffCorr_weightFSR->Fill(genInfo.PostW_pt,mTTW*mEffSf*weightFSR);
    return 0;
}
*/
int WlnuMET::InitHistogram()
{
  myFile=new TFile(mResultDir+"/"+OutNameBase+".root","RECREATE");
  for(int i(0);i<PUrangeBin;i++)
  {
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
int WlnuMET::WlnuMET::Fill_METs()
{
  h1_PF_Met[0]->Fill(pfMEtTL.Pt());
  h1_MVA_Met[0]->Fill(MVaMEtTL.Pt());
  h1_NoPU_Met[0]->Fill(NoPuMEtTL.Pt());
  h1_genMEtTrue[0]->Fill(genMEtTrueTL.Pt());

  h2_pfMET[0]  ->Fill(genMEtTrueTL.Pt(), pfMEtTL.Pt()-genMEtTrueTL.Pt());
  h2_MVaMET[0] ->Fill(genMEtTrueTL.Pt(), MVaMEtTL.Pt()-genMEtTrueTL.Pt());
  h2_NoPuMET[0]->Fill(genMEtTrueTL.Pt(), NoPuMEtTL.Pt()-genMEtTrueTL.Pt());

  if(mVtxVar.nGood>=0 && mVtxVar.nGood<7){
  h1_PF_Met[1]->Fill(pfMEtTL.Pt());
  h1_MVA_Met[1]->Fill(MVaMEtTL.Pt());
  h1_NoPU_Met[1]->Fill(NoPuMEtTL.Pt());
  h1_genMEtTrue[1]->Fill(genMEtTrueTL.Pt());

  h2_pfMET[1]  ->Fill(genMEtTrueTL.Pt(), pfMEtTL.Pt()-genMEtTrueTL.Pt());
  h2_MVaMET[1] ->Fill(genMEtTrueTL.Pt(), MVaMEtTL.Pt()-genMEtTrueTL.Pt());
  h2_NoPuMET[1]->Fill(genMEtTrueTL.Pt(), NoPuMEtTL.Pt()-genMEtTrueTL.Pt());
  }
  else if(mVtxVar.nGood>=7 && mVtxVar.nGood<21){
  h1_PF_Met[2]->Fill(pfMEtTL.Pt());
  h1_MVA_Met[2]->Fill(MVaMEtTL.Pt());
  h1_NoPU_Met[2]->Fill(NoPuMEtTL.Pt());
  h1_genMEtTrue[2]->Fill(genMEtTrueTL.Pt());
  h2_pfMET[2]  ->Fill(genMEtTrueTL.Pt(), pfMEtTL.Pt()-genMEtTrueTL.Pt());
  h2_MVaMET[2] ->Fill(genMEtTrueTL.Pt(), MVaMEtTL.Pt()-genMEtTrueTL.Pt());
  h2_NoPuMET[2]->Fill(genMEtTrueTL.Pt(), NoPuMEtTL.Pt()-genMEtTrueTL.Pt());
  }
  else if(mVtxVar.nGood>=21){
  h1_PF_Met[3]->Fill(pfMEtTL.Pt());
  h1_MVA_Met[3]->Fill(MVaMEtTL.Pt());
  h1_NoPU_Met[3]->Fill(NoPuMEtTL.Pt());
  h1_genMEtTrue[3]->Fill(genMEtTrueTL.Pt());
  h2_pfMET[3]  ->Fill(genMEtTrueTL.Pt(), pfMEtTL.Pt()-genMEtTrueTL.Pt());
  h2_MVaMET[3] ->Fill(genMEtTrueTL.Pt(), MVaMEtTL.Pt()-genMEtTrueTL.Pt());
  h2_NoPuMET[3]->Fill(genMEtTrueTL.Pt(), NoPuMEtTL.Pt()-genMEtTrueTL.Pt());
  }
  return 0;
}
int WlnuMET::Fill_METprofiles()
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
