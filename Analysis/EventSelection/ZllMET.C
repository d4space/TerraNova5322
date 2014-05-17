// $Log: ZllMET.C,v $
// Revision 1.8  2013/09/13 00:09:32  salee
// *** empty log message ***
//
// Revision 1.7  2013/09/12 05:10:29  sangilpark
// *** empty log message ***
//
#define ZllMET_cxx
//#include <iostream>
//#include <TROOT.h>                        // access to gROOT, entry point to ROOT system
//#include <TSystem.h>                      // interface to OS
#include <TBenchmark.h>                   // class to track macro running statistics
#include <algorithm>
#include "ZllMET.h"
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

void ZllMET::Loop()
{
  //gSystem->Load("libMathCore");
  //gSystem->Load("libPhysics");
  //using namespace ROOT::Math;

  Debug=false;
  cout<<"==========================================================="<<endl;
  cout<<"ZllMET Analysis with Mode: "<<Mode<<"  AnaChannel: "<<AnaChannel<<endl;
  cout<<"==========================================================="<<endl;
  gBenchmark->Start("ZllMET");

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

    //==================
    // Acceptance Study
    //==================
    //===================
    // Check the channel : To check if the ntuple is for each lepton flavor
    //===================
    //if(ZllBase::CheckChannel()!=0) exit(-1);

    //============
    //Trigger Cut
    //============
    //if(ZllBase::TriggerCut() !=0) continue;

    //Vertex Study===========================
    if(VertexCut() !=0) continue;

    //===================
    // Calculate Event Weight
    //=====================
    //mTTW = CalcEvtWeight();
    mTTW = 1;

    //cout<<"Muon size: "<<wMuons.pt->size()<<endl;
    //cout<<"W    size: "<<W_pt->size()<<endl;
   
    ZbestSelect();

    if(Z.Pass)
    {
      mNZevt++;
      Fill_METs();

      h1_Zmass->Fill(Z.mass,mTTW);

    }
  }//Ntries
  cout<<"   Passed Z evts: "<<mNZevt<<endl;
  //Results======================
  Fill_METprofiles();
  cout<<"selected converted: "<<evtSelected<<" +- "<<TMath::Sqrt(evtSelected)<<endl;

  h1_Zmass->Write();
  myFile->Write();
  gBenchmark->Show("ZllMET");
}

int ZllMET::InitVar()
{
  cout<<"Initialize variable at ZllMET class ==========="<<endl;
  evtCnt = 0;
  mNWevt = 0;
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
int ZllMET::InitVar4Evt()
{
  //cout<<"ZllMET::InitVar4Evt ==========================="<<endl;
  ZllBase::InitVar4Evt();
  return 0;
}
int ZllMET::VertexCut()
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
double ZllMET::CalcEvtWeight()
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
int ZllMET::ZbestSelect()
{
  diLeptVtxProb = 0;
  double tmpVar(0);
  double ZLep2PtTmp;
  for(int iz(0); iz<mZ_size;iz++)
  {
    if(AnaChannel == "Tau2012")if( TauCutZ(iz) == -1) continue;
    if(AnaChannel == "Muon2012LoPU" )if( MuonCutZ(iz) == -1) continue;
    if(AnaChannel == "Muon2012")if( MuonCutZ(iz) == -1) continue;
    if(AnaChannel == "Electron2012LoPU" )if( ElectronCutZ(iz) == -1) continue;
    if(AnaChannel == "Electron2012")if( ElectronCutZHighPU(iz) == -1) continue;
    if(Mode =="ScaleMakeRD")if((*Z_Lept2_pt)[iz] < 10 )continue;
    if(Mode =="ScaleMakeMC")if((*Z_Lept2_pt)[iz] < 10 )continue;
    if((Mode =="RecoilEvaRD")||(Mode == "RecoilEvaMC"))if((*Z_Lept2_pt)[iz] < 15 )continue;

    Z.Pass=true;

    tmpVar = (*Z_diLeptVtxProb)[iz];

    if( fabs(Channel) != GenType::kTau) if( tmpVar > diLeptVtxProb )
    {
      Z.idxBest = iz;
      diLeptVtxProb = tmpVar;
	Z.mass		= (*Z_Mass)[iz];
	Z.Lep1Pt	= (*Z_Lept1_pt)[iz];
	Z.Lep1Pz	= (*Z_Lept1_pz)[iz];
	Z.Lep1En	= (*Z_Lept1_en)[iz];
	Z.Lep1Phi	= (*Z_Lept1_phi)[iz];
	Z.Lep2Pt	= (*Z_Lept2_pt)[iz];
	Z.Lep2Pz	= (*Z_Lept2_pz)[iz];
	Z.Lep2En	= (*Z_Lept2_en)[iz];
	Z.Lep2Phi	= (*Z_Lept2_phi)[iz];

	TVector2 ZDiLep2D(
                (*Z_Lept1_px)[iz]+(*Z_Lept2_px)[iz],
                (*Z_Lept1_py)[iz]+(*Z_Lept2_py)[iz]);
        Zpt = ZDiLep2D.Mod();

	if((AnaChannel == "ElectronLowPU" ) ||AnaChannel=="ElectronHighPU"){
	  Z.Lep1etaSC	= (*Z_Lept1_etaSC)[iz];
	  Z.Lep2etaSC	= (*Z_Lept2_etaSC)[iz];
	}else{
	  Z.Lep1etaSC	= (*Z_Lept1_eta)[iz];
	  Z.Lep2etaSC	= (*Z_Lept2_eta)[iz];
	}

    }//fi diLeptVtxProb
    ZLep2PtTmp = (*Z_Lept2_pt)[iz];
    if( fabs(Channel) == GenType::kTau) if( ZLep2PtTmp > Z.Lep2Pt )
    {
      Z.idxBest = iz;
	Z.mass		= (*Z_Mass)[iz];
	Z.Lep1Pt	= (*Z_Lept1_pt)[iz];
	Z.Lep1Pz	= (*Z_Lept1_pz)[iz];
	Z.Lep1En	= (*Z_Lept1_en)[iz];
	Z.Lep1Phi	= (*Z_Lept1_phi)[iz];
	Z.Lep2Pt	= (*Z_Lept2_pt)[iz];
	Z.Lep2Pz	= (*Z_Lept2_pz)[iz];
	Z.Lep2En	= (*Z_Lept2_en)[iz];
	Z.Lep2Phi	= (*Z_Lept2_phi)[iz];

	TVector2 ZDiLep2D(
                (*Z_Lept1_px)[iz]+(*Z_Lept2_px)[iz],
                (*Z_Lept1_py)[iz]+(*Z_Lept2_py)[iz]);
        Zpt = ZDiLep2D.Mod();

	if((AnaChannel == "ElectronLowPU" ) ||AnaChannel=="ElectronHighPU"){
	  Z.Lep1etaSC	= (*Z_Lept1_etaSC)[iz];
	  Z.Lep2etaSC	= (*Z_Lept2_etaSC)[iz];
	}else{
	  Z.Lep1etaSC	= (*Z_Lept1_eta)[iz];
	  Z.Lep2etaSC	= (*Z_Lept2_eta)[iz];
	}

    }//fi diLeptVtxProb
  }//Z

  return 0;
}
int ZllMET::InitHistogram()
{
  myFile=new TFile(mResultDir+"/"+OutNameBase+".root","RECREATE");
  h1_Zmass   = new TH1D("h1_Zmass","Z Mass",60,50.,130);
  h2_pfMET_pxpy  = new TH2D("h2_pfMET_pxpy","pfMET pxpy",100,-600,600,100,-600,600);
  h2_MVaMET_pxpy  = new TH2D("h2_MVaMET_pxpy","MVaMET pxpy",100,-600,600,100,-600,600);
  h2_NoPuMET_pxpy  = new TH2D("h2_NoPuMET_pxpy","NoPuMET pxpy",100,-600,600,100,-600,600);
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
int ZllMET::Fill_METs()
{
  h2_pfMET_pxpy ->Fill(pfMEt_x, pfMEt_y);
  h2_MVaMET_pxpy ->Fill(MVaMEt_x, MVaMEt_y);
  h2_NoPuMET_pxpy ->Fill(NoPuMEt_x, NoPuMEt_y);

  h1_Zmass->Fill(pfMEtTL.Pt());
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
int ZllMET::Fill_METprofiles()
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
