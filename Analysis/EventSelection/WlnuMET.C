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

    //==================
    // Acceptance Study
    //==================
    if(Mode == "Acceptance")if(GenW_Born_Id->size() > 0)
    {
      if( FillAcceptInfo() != 0 ) exit(-1);
      // Don't go futher
      continue;
    }
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

//    ZbestSelect();

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
  cout<<"Passed W evts: "<<mNWevt<<"   Passed Z evts: "<<mNZevt<<endl;
  //Results======================

  cout<<"selected converted: "<<evtSelected<<" +- "<<TMath::Sqrt(evtSelected)<<endl;

  myFile->Write();
  gBenchmark->Show("WlnuMET");
}


void WlnuMET::Nselected4Bin()
{
  for(int i(0);i<NwPtBin;i++)
  {
    if( W.pt >= Bins[i] && W.pt <Bins[i+1]) mNselected4Bin[i]+=mTTW;
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
int WlnuMET::ZbestSelect()
{
  diLeptVtxProb = 0;
  double tmpVar(0);
  double ZLep2PtTmp;
  for(int iz(0); iz<mZ_size;iz++)
  {
    if(AnaChannel == "TauHighPU")if( TauCutZ(iz) == -1) continue;
    if(AnaChannel == "MuonLowPU" )if( MuonCutZ(iz) == -1) continue;
    if(AnaChannel == "MuonHighPU")if( MuonCutZ(iz) == -1) continue;
    if(AnaChannel == "ElectronLowPU" )if( ElectronCutZ(iz) == -1) continue;
    if(AnaChannel == "ElectronHighPU")if( ElectronCutZHighPU(iz) == -1) continue;
    if(Mode =="ScaleMakeRD")if((*Z_Lept2_pt)[iz] < 10 )continue;
    if(Mode =="ScaleMakeMC")if((*Z_Lept2_pt)[iz] < 10 )continue;
    if((Mode =="RecoilEvaRD")||(Mode == "RecoilEvaMC"))if((*Z_Lept2_pt)[iz] < 15 )continue;
    //MC truth Check or Z_pass = false
    //if(Mode == "RecoilMC")
    //{
	//Lepton MC truth
//	if( fabs((*Z_Lept1_genDeltaR)[iz]) > 0.025 ||
//	    fabs((*Z_Lept2_genDeltaR)[iz]) > 0.025)
//	{
//	  //cout<<"DeltaR Z_Lept1: "<<(*Z_Lept1_genDeltaR)[iz]<<
//	  ///  "DeltaR Z_Lept2: "<<(*Z_Lept2_genDeltaR)[iz]<<endl;
//	  continue;
//	}
//	if( (*Z_Lept1_genIdxMatch)[iz] != (*Z_Lept2_genIdxMatch)[iz] )continue;
//	if( (*Z_Lept1_genIdxMatch)[iz] <0) continue;
//	if( GenZ_id->size() == 0)continue;
//	if( abs((*GenZ_id)[iz]) != 23 //Z
//	    && abs((*GenZ_id)[iz]) != 22)continue; //Gamma
 //     }
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

	//cout<<"ZLep1 px: "<<(*Z_Lept1_px)[iz]<<" pt cos phi :"<<Zep1Pt*cos((*Z_Lept1_phi)[iz])<<endl;
	if(Mode == "RecoilEvaRD" || Mode =="RecoilEvaMC"){
	  //Recoil = -Met - Z
	  TVector2 RecoilVector(
	  	-(*Z_Neut_px)[iz]-(*Z_px)[iz],
	  	-(*Z_Neut_py)[iz]-(*Z_py)[iz]);
	  //if(Mode == "RecoilEvaRD")
	  //{
	    TVector2 DiLep2D(
	      (*Z_px)[iz],
	      (*Z_py)[iz]
	      );
	    ZptRecoil = (*Z_pt)[iz];
	    //u1 = B.u, u2=B cross u
	    Rcl.u1Z = RecoilVector*DiLep2D/DiLep2D.Mod();
	    Rcl.u2Z = (RecoilVector.Px()*DiLep2D.Py()-RecoilVector.Py()*DiLep2D.Px())/DiLep2D.Mod();
	    Rcl.u3Z = RecoilVector*DiLep2D/DiLep2D.Mod()+DiLep2D.Mod();
	    //Rcl.u1Z = ( (*Z_px)[iz]*Rcl.ux+(*Z_py)[iz]*Rcl.uy )/BosonNorm;
	    //Rcl.u2Z = ( (*Z_px)[iz]*Rcl.uy - (*Z_py)[iz]*Rcl.ux)/BosonNorm;
	  //}else if(Mode == "RecoilMC")
	  //{
	    //int gi = (*Z_Lept1_genIdxMatch)[iz];
	    //TVector2 genDiLep2D(
//		(*GenZ_Lept1_px)[gi]+(*GenZ_Lept2_px)[gi],
//		(*GenZ_Lept1_py)[gi]+(*GenZ_Lept2_py)[gi]);
//	    ZptRecoil = genDiLep2D.Mod();
//	    //u1 = B.u, u2=B cross u
//	    Rcl.u1Z = RecoilVector*genDiLep2D/genDiLep2D.Mod();
//	    Rcl.u2Z = (RecoilVector.Px()*genDiLep2D.Py()-RecoilVector.Py()*genDiLep2D.Px())/genDiLep2D.Mod();
	    //Rcl.u1Z = ((*GenZ_px)[iz]*Rcl.ux+(*GenZ_py)[iz]*Rcl.uy )/BosonNorm;
	    //Rcl.u2Z = ((*GenZ_px)[iz]*Rcl.uy-(*GenZ_py)[iz]*Rcl.ux)/BosonNorm;
//	  }
	}//fi Recoil or RecoilMC
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

	//cout<<"ZLep1 px: "<<(*Z_Lept1_px)[iz]<<" pt cos phi :"<<Zep1Pt*cos((*Z_Lept1_phi)[iz])<<endl;
	if(Mode == "RecoilEvaRD" || Mode =="RecoilEvaMC")
	{
	  //Recoil = -Met - Z
	  TVector2 RecoilVector(
	  	-(*Z_Neut_px)[iz]-(*Z_px)[iz],
	  	-(*Z_Neut_py)[iz]-(*Z_py)[iz]);
	  //if(Mode == "RecoilEvaRD")
	  //{
	    TVector2 DiLep2D(
	      (*Z_px)[iz],
	      (*Z_py)[iz]
	      );
	    ZptRecoil = (*Z_pt)[iz];
	    //u1 = B.u, u2=B cross u
	    Rcl.u1Z = RecoilVector*DiLep2D/DiLep2D.Mod();
	    Rcl.u2Z = (RecoilVector.Px()*DiLep2D.Py()-RecoilVector.Py()*DiLep2D.Px())/DiLep2D.Mod();
	    Rcl.u3Z = RecoilVector*DiLep2D/DiLep2D.Mod()+DiLep2D.Mod();
	    //Rcl.u1Z = ( (*Z_px)[iz]*Rcl.ux+(*Z_py)[iz]*Rcl.uy )/BosonNorm;
	    //Rcl.u2Z = ( (*Z_px)[iz]*Rcl.uy - (*Z_py)[iz]*Rcl.ux)/BosonNorm;
	  //}else if(Mode == "RecoilMC")
	  //{
	    //int gi = (*Z_Lept1_genIdxMatch)[iz];
	    //TVector2 genDiLep2D(
//		(*GenZ_Lept1_px)[gi]+(*GenZ_Lept2_px)[gi],
//		(*GenZ_Lept1_py)[gi]+(*GenZ_Lept2_py)[gi]);
//	    ZptRecoil = genDiLep2D.Mod();
//	    //u1 = B.u, u2=B cross u
//	    Rcl.u1Z = RecoilVector*genDiLep2D/genDiLep2D.Mod();
//	    Rcl.u2Z = (RecoilVector.Px()*genDiLep2D.Py()-RecoilVector.Py()*genDiLep2D.Px())/genDiLep2D.Mod();
	    //Rcl.u1Z = ((*GenZ_px)[iz]*Rcl.ux+(*GenZ_py)[iz]*Rcl.uy )/BosonNorm;
	    //Rcl.u2Z = ((*GenZ_px)[iz]*Rcl.uy-(*GenZ_py)[iz]*Rcl.ux)/BosonNorm;
//	  }
	}//fi Recoil or RecoilMC
    }//fi diLeptVtxProb
  }//Z

  return 0;
}
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
int WlnuMET::InitHistogram()
{
  myFile=new TFile(mResultDir+"/"+OutNameBase+".root","RECREATE");
  h1_PF_Met   = new TH1D("h1_PF_Met","PF MET",50,0.,100);
  h1_MVA_Met   = new TH1D("h1_MVA_Met","MVA MET",50,0.,100);
  h1_NoPU_Met  = new TH1D("h1_NoPU_Met","NoPU MET",50,0.,100);
  h1_genMEtTrue= new TH1D("h1_genMEtTrue","genMEtTrue",50,0.,100);

  hp_pfMet  = new TProfile("hp_pfMet","pf - genMetTrue",50,0.,100);
  hp_MVaMet = new TProfile("hp_MVaMet","MVA - genMetTrue",50,0.,100);
  hp_NoPuMet= new TProfile("hp_NoPuMet","NoPU - genMetTrue",50,0.,100);
  return 0;
}
int WlnuMET::Fill_METs()
{
  h1_PF_Met->Fill(pfMEtTL.Pt());
  h1_MVA_Met->Fill(MVaMEtTL.Pt());
  h1_NoPU_Met->Fill(NoPuMEtTL.Pt());
  h1_genMEtTrue->Fill(genMEtTrueTL.Pt());

  hp_pfMet  ->Fill(genMEtTrueTL.Pt(), pfMEtTL.Pt()-genMEtTrueTL.Pt());
  hp_MVaMet ->Fill(genMEtTrueTL.Pt(), MVaMEtTL.Pt()-genMEtTrueTL.Pt());
  hp_NoPuMet->Fill(genMEtTrueTL.Pt(), NoPuMEtTL.Pt()-genMEtTrueTL.Pt());

  return 0;
}
