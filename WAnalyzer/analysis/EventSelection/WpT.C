// $Log: WpT.C,v $
// Revision 1.8  2013/09/13 00:09:32  salee
// *** empty log message ***
//
// Revision 1.7  2013/09/12 05:10:29  sangilpark
// *** empty log message ***
//
// Revision 1.6  2013/08/31 06:56:40  khakim
// *** empty log message ***
//
//   In a ROOT session, you can do:
//      Root > .L WpT.C
//      Root > WpT t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
#define WpT_cxx
//#include <iostream>
//#include <TROOT.h>                        // access to gROOT, entry point to ROOT system
//#include <TSystem.h>                      // interface to OS
#include <TBenchmark.h>                   // class to track macro running statistics
#include <algorithm>
#include "WpT.h"
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

void WpT::Loop()
{
  gSystem->Load("libMathCore");
  gSystem->Load("libPhysics");
  using namespace ROOT::Math;

  Debug=false;
  cout<<"==========================================================="<<endl;
  cout<<"WpT Analysis with Mode: "<<Mode<<"  AnaChannel: "<<AnaChannel<<endl;
  cout<<"==========================================================="<<endl;
  gBenchmark->Start("WpT");
  gRandom->SetSeed(0);
//
  if (fChain == 0) return;
   //int Ntries = fChain->GetEntriesFast(); this gives 1234567890 kkk
  Ntries = fChain->GetEntries();

  cout<<"Total: "<<Ntries<<endl;
  
  // Recoil Correction Parameter Files
  if( (  Mode == "AllCorrectionsMC"
      || Mode == "RecoilCorrMC")
      || Mode =="DumpUnfInfo" )
  {
    //if(AnaChannel == "MuonLowPU")
    if(AnaChannel == "MuonLowPU" )
    {
      rcoil.ZRDfilename="../Recoil/ZmmData/fits.root";
      rcoil.ZMCfilename="../Recoil/ZmmMC/fits.root";
      rcoil.Wpfilename="../Recoil/WmpMC/fits.root";
      rcoil.Wmfilename="../Recoil/WmmMC/fits.root";
    }else if((AnaChannel == "ElectronLowPU" ) || AnaChannel == "ElectronHighPU" )
    {
      rcoil.ZRDfilename="../Recoil/ZeeData/fits.root";
      rcoil.ZMCfilename="../Recoil/ZeeMC/fits.root";
      rcoil.Wpfilename="../Recoil/WepMC/fits.root";
      rcoil.Wmfilename="../Recoil/WemMC/fits.root";
    }
    // RecoilCorrection Object.
    RecoilCorr= new RecoilCorrector(
      rcoil.ZRDfilename,
      rcoil.Wpfilename,rcoil.Wmfilename,
      rcoil.ZMCfilename,
      0x1234);
  //Int_t iSeed=0xDEADBEEF default seed for random number generator at constructor
  }

  TString resultDir = AnaChannel;
  if(AnaChannel == "MuonLowPU" )
    resultDir = "MuonLowPU";
  else if(AnaChannel == "ElectronLowPU")
    resultDir = "ElectronLowPU";

  gSystem->mkdir(resultDir);

  for (int i(0); i<20;i++)
  //for (int i(0); i<Ntries;i++)
  {
    evtCnt = i;
    //===============================
    //W study
    //===============================
    if(i % 100000 == 0) cout<<i<<"th event"<<endl;
    if(Debug)cout<<"check point 1"<<endl;
  //=========
    //dump tree
    //=========
    //pfMEt4V = 0;

    fChain->GetEntry(i);
    //===========================
    //Initialization of Variables
    //===========================
    InitVar4Evt();

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
    if(WLepNeu::CheckChannel()!=0) exit(-1);

    //============
    //Trigger Cut
    //============
    if(WLepNeu::TriggerCut() !=0) continue;

    //Vertex Study===========================
    if(VertexCut() !=0) continue;

    h1_Vtx_Prim->Fill(mVtxVar.nPrim);
    h1_Vtx_Good->Fill(mVtxVar.nGood);


    //===================
    // Calculate Event Weight
    //=====================
    mTTW = CalcEvtWeight();
    
    //cout<<"Muon size: "<<wMuons.pt->size()<<endl;
    //cout<<"W    size: "<<W_pt->size()<<endl;
    h1_W_Multi->Fill(wCand.size);

    //===========================
    // W best Candidate Selection
    //===========================
    //cout<<"pfMEtTL.pt: "<<pfMEtTL.Pt()<<" W_NuPt: "<<(*W_Neut_pt)[0]<<endl;
    //cout<<"NoPuMEtTL.pt: "<<NoPuMEtTL.Pt()<<endl;
    //cout<<"MVaMEtTL.pt: "<<MVaMEtTL.Pt()<<endl;
    //cout<<"genMEtTrueTL.pt: "<<genMEtTrueTL.Pt()<<endl;
    //cout<<"genMEtCaloTL.pt: "<<genMEtCaloTL.Pt()<<endl;
    //cout<<"genMEtCaloAndNonPromptTL.pt: "<<genMEtCaloAndNonPromptTL.Pt()<<endl;
    
    WbestSelect();
    
    ZLep2Pt = 0;
    u1Z=-999;u2Z=-999;u3Z=-999;

    ZbestSelect();


    //Fill the W==================
    if( wCand.Pass)
    {
      DumpWbestCand(wCand.idxBest);
      if(Mode == "DumpUnfInfo")
      {
        DumpUnfoldInfo(wCand.idxBest);
      }
    }
    if( wCand.Pass && addLepN <2 ){
      DumpWMETs();
      mNWevt++;
      if(wCand.pt > 600)
	cout<<"Check the wCand.pt is greater than 600: "<<wCand.pt<<endl;
      //Recoil Correction for W candidate of MC
      if((Mode == "AllCorrectionsMC" || Mode == "RecoilCorrMC")
	  || Mode == "DumpUnfInfo")
	if(GenW_Born_Id->size() >0)
	DoRecoilCorr();

      //cout<<"TruthRecoPost:"<<TruthRecoPost<<endl;
      if(Mode == "DumpUnfInfo")if(TruthRecoPost)if(WCHARGE == wCand.charge)
      {
	FillUnfoldInfo();
	// Don't go further
	//continue;
      }
      if( Mode == "RecoilMC")
      for( int ipt(0);ipt<u1Bin;ipt++)
      {
	if(genInfo.PostW_pt >=RecoilBins[ipt] && genInfo.PostW_pt<RecoilBins[ipt+1])
	//if(genInfo.BornW_pt >=RecoilBins[ipt] && genInfo.BornW_pt < RecoilBins[ipt+1])
	{
	  h1_u1W[ipt]->Fill(u1W);
	  h1_u2W[ipt]->Fill(u2W);
	  h1_u3W[ipt]->Fill(u3W);
	}
      }

      h1_GlbMuChi2->Fill(glbMuChi2,mTTW);
      h1_muonHits->Fill(wCand.muonHit,mTTW);
      h1_muMatchStation->Fill(wCand.matchStation,mTTW);
      h1_trkLayers->Fill(wCand.trkLayers,mTTW);
      h1_pixelHits->Fill(wCand.pixelHits,mTTW);
      h1_dB->Fill(wCand.dB,mTTW);
      h1_dz->Fill(wCand.dz,mTTW);
      h1_IsoCom03->Fill( (wCand.chIso03+wCand.nhIso03+wCand.phIso03)/wCand.lep_pt,mTTW);
      h1_IsoCom04->Fill( (wCand.chIso04+wCand.nhIso04+wCand.phIso04)/wCand.lep_pt,mTTW);
      h1_IsoHad03->Fill( (wCand.chIso03+wCand.nhIso03)/wCand.lep_pt,mTTW);
      h1_IsoHad04->Fill( (wCand.chIso04+wCand.nhIso04)/wCand.lep_pt,mTTW);
      h1_IsoBeta03->Fill( (wCand.chIso03+max(0.0, wCand.nhIso03+wCand.phIso03-0.5*wCand.pcIso03))/wCand.lep_pt,mTTW);
      h1_IsoBeta04->Fill( (wCand.chIso04+max(0.0, wCand.nhIso04+wCand.phIso04-0.5*wCand.pcIso04))/wCand.lep_pt,mTTW);

      //cout<<"effSf_(C) = "<<effSf_<<endl;
      h1_W_pt->Fill(wCand.pt,mTTW);
      h1_W_pt_EffCorr->Fill(wCand.pt,mTTW*effSf_);
      h2_WpT_lepPt->Fill(wCand.pt,wCand.lep_pt);

      h1_W_Acop->Fill(w_acop,mTTW);

      h1_W_Mt->Fill(wCand.Mt,mTTW);
      h1_W_Lept1_pt->Fill(wCand.lep_pt,mTTW);

      h1_Vtx_Prim1->Fill(mVtxVar.nPrim,mTTW);
      h1_Vtx_Good1->Fill(mVtxVar.nGood,mTTW);
      h1_W_Lept1_pt1->Fill(wCand.lep_pt,mTTW);
      h1_npileup1->Fill(npileup,mTTW);
      h1_W_Neut_pt1->Fill(wCand.Met,mTTW);
      
    if(AnaChannel == "ElectronHighPU" )
    {
      h1_W_Lep1_eta->Fill(wCand.lep_eta,mTTW);
      h1_W_Neu_All->Fill(wCand.Met,mTTW);

      for(int iEta=0;iEta<NWqaBins;iEta++){
	///////////////// Divide Eta Bins///////////
	////////Inclusive Case////////////
	if (fabs(wCand.lep_eta) > wqaMetMNBins[iEta] && fabs(wCand.lep_eta) < wqaMetMXBins[iEta] ) {
	  h1_W_Neu_Eta_I[iEta]->Fill(wCand.Met,mTTW);
	  
	  if ( wCand.charge > 0 ){ /////////Plus Case////////////
	    h1_W_Neu_Eta_P[iEta]->Fill(wCand.Met,mTTW);
	  }
	  else if ( wCand.charge < 0){ //////////Minus Case////////////////
	    h1_W_Neu_Eta_M[iEta]->Fill(wCand.Met,mTTW);
	  }
	}
      }
    }
   
    if( wCand.charge > 0)
    {
      h1_Wp_pt->Fill(wCand.pt,mTTW);
      h1_Wp_pt_EffCorr->Fill(wCand.pt,mTTW*effSf_);
      h1_Wp_pt_NoLumiWeight->Fill(wCand.pt);
      h2_WpT_lepPt_Plus->Fill(wCand.pt,wCand.lep_pt);

      if(Mode == "AllCorrectionsMC" || Mode == "RecoilCorrMC")
      {
	//cout<<"filling corrMet "<<corrMet<<endl;
	h1_W_Neu_pt[0]->Fill(corrMet,mTTW*effSf_);
	//h1_Wp_Neu_pt[0]->Fill(corrMet,mTTW);
	h1_Wp_Neu_pt[0]->Fill(corrMet,mTTW*effSf_);
	  
	if(corrMet > 25.)
	{
	  mNmetA[0]+=mTTW;
	  mNmetAp[0]+=mTTW;
	}else{
	  mNmetB[0]+=mTTW;
	  mNmetBp[0]+=mTTW;
	}
      }else{
	h1_W_Neu_pt[0]->Fill(wCand.Met,mTTW);
	h1_GenW_Neu_pt[0]->Fill(genInfo.BornW_Nu_Pt,mTTW);
        h2_Met_WpT[0]->Fill(wCand.pt,wCand.Met);
        h2_Met_LepPt[0]->Fill(wCand.lep_pt,wCand.Met);
	h1_Wp_Neu_pt[0]->Fill(wCand.Met,mTTW);
	h1_GenWp_Neu_pt[0]->Fill(genInfo.BornW_Nu_Pt,mTTW);

	if( wCand.Met > 25.)
	{
	  mNmetA[0]+=mTTW;
	  mNmetAp[0]+=mTTW;
	}else{
	  mNmetB[0]+=mTTW;
	  mNmetBp[0]+=mTTW;
	}
      }
      
      for(int iBin(0);iBin<NWptBinPlus-1;iBin++)
      {
	if( wCand.pt >= Bins[iBin] && wCand.pt < Bins[iBin+1] )
	{
	  if(Mode == "AllCorrectionsMC" || Mode == "RecoilCorrMC")
	  {
	    //if(corrMet < 0)cout<<"corrMet: "<<corrMet<<endl;
	    h1_W_Neu_pt[iBin+1]->Fill(corrMet,mTTW*effSf_);
	    //h1_Wp_Neu_pt[iBin+1]->Fill(corrMet,mTTW);
	    h1_Wp_Neu_pt[iBin+1]->Fill(corrMet,mTTW*effSf_);
	    
	    if(corrMet >25.)
	    {
	      mNmetA[iBin+1]+=mTTW;
	      mNmetAp[iBin+1]+=mTTW;
	    }else{
	      mNmetB[iBin+1]+=mTTW;
	      mNmetBp[iBin+1]+=mTTW;
	    }
	  }else{
	    h1_W_Neu_pt[iBin+1]->Fill(wCand.Met,mTTW);
	    h1_GenW_Neu_pt[iBin+1]->Fill(genInfo.BornW_Nu_Pt,mTTW);
            h2_Met_WpT[iBin+1]->Fill(wCand.pt,wCand.Met);
            h2_Met_LepPt[iBin+1]->Fill(wCand.lep_pt,wCand.Met);
	    h1_Wp_Neu_pt[iBin+1]->Fill(wCand.Met,mTTW);
	    h1_GenWp_Neu_pt[iBin+1]->Fill(genInfo.BornW_Nu_Pt,mTTW);

	    if(wCand.Met >25.)
	    {
	      mNmetA[iBin+1]+=mTTW;
	      mNmetAp[iBin+1]+=mTTW;
	    }else
	    {
	      mNmetB[iBin+1]+=mTTW;
	      mNmetBp[iBin+1]+=mTTW;
	    }
	  }
	}
      }
    }else if(wCand.charge <0){
      h1_Wm_pt->Fill(wCand.pt,mTTW);
      h1_Wm_pt_EffCorr->Fill(wCand.pt,mTTW*effSf_);
      h1_Wm_pt_NoLumiWeight->Fill(wCand.pt);
      h2_WpT_lepPt_Minus->Fill(wCand.pt,wCand.lep_pt);
	
      if(Mode == "AllCorrectionsMC" || Mode == "RecoilCorrMC")
      {
	h1_W_Neu_pt[0]->Fill(corrMet,mTTW*effSf_);
	//h1_Wm_Neu_pt[0]->Fill(corrMet,mTTW);
	h1_Wm_Neu_pt[0]->Fill(corrMet,mTTW*effSf_);
	
	if(corrMet > 25.)
	{
	  mNmetA[0]+=mTTW;
	  mNmetAm[0]+=mTTW;
	}else{
	  mNmetB[0]+=mTTW;
	  mNmetBm[0]+=mTTW;
	}
      }else{
	h1_W_Neu_pt[0]->Fill(wCand.Met,mTTW);
        h1_GenW_Neu_pt[0]->Fill(genInfo.BornW_Nu_Pt,mTTW);
        h2_Met_WpT[0]->Fill(wCand.pt,wCand.Met);
        h2_Met_LepPt[0]->Fill(wCand.lep_pt,wCand.Met);
	h1_Wm_Neu_pt[0]->Fill(wCand.Met,mTTW);
	h1_GenWm_Neu_pt[0]->Fill(genInfo.BornW_Nu_Pt,mTTW);

	if(wCand.Met >25.)
	{
	  mNmetA[0]+=mTTW;
	  mNmetAm[0]+=mTTW;
	}else
	{
	  mNmetB[0]+=mTTW;
	  mNmetBm[0]+=mTTW;
	}
      }
      for(int iBin(0);iBin<NWptBinPlus-1;iBin++)
      {
	if( wCand.pt >= Bins[iBin] && wCand.pt < Bins[iBin+1] )
	{
	  if(Mode == "AllCorrectionsMC" || Mode == "RecoilCorrMC")
	  {
	    h1_W_Neu_pt[iBin+1]->Fill(corrMet,mTTW*effSf_);
	    //h1_Wm_Neu_pt[iBin+1]->Fill(corrMet,mTTW);
	    h1_Wm_Neu_pt[iBin+1]->Fill(corrMet,mTTW*effSf_);

	    if(corrMet >25.)
	    {
	      mNmetA[iBin+1]+=mTTW;
	      mNmetAm[iBin+1]+=mTTW;
	    }else{
	      mNmetB[iBin+1]+=mTTW;
	      mNmetBm[iBin+1]+=mTTW;
	    }
	  }else{
	    h1_W_Neu_pt[iBin+1]->Fill(wCand.Met,mTTW);
	    h1_GenW_Neu_pt[iBin+1]->Fill(genInfo.BornW_Nu_Pt,mTTW);
            h2_Met_WpT[iBin+1]->Fill(wCand.pt,wCand.Met);
            h2_Met_LepPt[iBin+1]->Fill(wCand.lep_pt,wCand.Met);
	    h1_Wm_Neu_pt[iBin+1]->Fill(wCand.Met,mTTW);
	    h1_GenWm_Neu_pt[iBin+1]->Fill(genInfo.BornW_Nu_Pt,mTTW);

	    if(wCand.Met >25.)
	    {
	      mNmetA[iBin+1]+=mTTW;
	      mNmetAm[iBin+1]+=mTTW;
	    }else
	    {
	      mNmetB[iBin+1]+=mTTW;
	      mNmetBm[iBin+1]+=mTTW;
	    }
	  }
	}
      }
    }else{
      cout<<"stange case w_charge is "<<wCand.charge<<endl;
      exit(0);
    }
    
    //cout<<"mTTW: "<<mTTW<<endl;
    evtSelected+=mTTW;
    if(Debug)cout<<"check point 16"<<endl;
    Nselected4Bin();
    
    //cout<<"nselect: "<<evtSelected<<endl;
    }//good W

    if(Zboson.Pass)
    {
      DumpZMETs();
      mNZevt++;
      h1_diLeptVtxProb->Fill(diLeptVtxProb,mTTW);
      if(Mode == "ScaleMakeMC" || Mode == "ScaleMakeRD")
      {
	int etaRange1 = EtaRange(ZLep1etaSC);
	int etaRange2 = EtaRange(ZLep2etaSC);
	//      h1_ZmassDaughEta[etaRange1][etaRange2]->Fill(Zmass);
	if( (AnaChannel == "ElectronLowPU" ) || AnaChannel=="ElectronHighPU")
	{
	  FillEleZmassDaughEta(etaRange1,etaRange2);
	}

	if( (AnaChannel == "MuonLowPU" ) || AnaChannel=="MuonHighPU")
	{
	  FillMuZmassDaughEta(etaRange1,etaRange2);
	}
      }
      if(Mode == "ScaleMakeMC"||Mode == "ScaleMakeRD")
	if( (AnaChannel == "MuonLowPU" ) || AnaChannel=="MuonHighPU")
      {
	if(Mode == "ScaleMakeMC")
	{
	  PtEtaPhiMLorentzVector Zele1_4( ZLep1Pt,ZLep1etaSC,ZLep1Phi,muonmass);
	  PtEtaPhiMLorentzVector  Zele2_4( ZLep2Pt,ZLep2etaSC,ZLep2Phi,muonmass);
	  
	  corr1 = gRandom->Gaus(Zele1_4.E(), MuonSmearMC(ZLep1etaSC))/Zele1_4.E();
	  corr2 = gRandom->Gaus(Zele2_4.E(), MuonSmearMC(ZLep2etaSC))/Zele2_4.E();
	  
	  PtEtaPhiMLorentzVector Z_4 =  corr1*Zele1_4 + corr2* Zele2_4;
	  h1_ZmassCorr->Fill(Z_4.M(),mTTW);

	  // Barrel Barrel  
	  if(fabs(ZLep1etaSC) >= 0.0   && fabs(ZLep1etaSC) < 1.4442)
	  {
	    if(fabs(ZLep2etaSC) >= 0.0   && fabs(ZLep2etaSC) < 1.4442)
	      h1_ZmassCorr_BB->Fill(Z_4.M(),mTTW);
	  }

	  //Barrel Endcap
	  if(fabs(ZLep1etaSC) >= 0.0   && fabs(ZLep1etaSC) < 1.4442)
	  {
	    if(fabs(ZLep2etaSC) >= 1.566   && fabs(ZLep2etaSC) < 2.5)
	      h1_ZmassCorr_BE->Fill(Z_4.M(),mTTW);
	  }else if(fabs(ZLep1etaSC) >= 1.566   && fabs(ZLep1etaSC) < 2.5)
	  {
	    if(fabs(ZLep2etaSC) >= 0.0   && fabs(ZLep2etaSC) < 1.4442)
	      h1_ZmassCorr_BE->Fill(Z_4.M(),mTTW);
	  }
     
	  // Endcap Endcap
	  if(fabs(ZLep1etaSC) >= 1.566  && fabs(ZLep1etaSC) < 2.5)
	  {
	    if(fabs(ZLep2etaSC) >= 1.566   && fabs(ZLep2etaSC) < 2.5)
	      h1_ZmassCorr_EE->Fill(Z_4.M(),mTTW);
	  }
	}

  	//Simulation Mehtod
	//double etaRange_ = EtaRange(ZLep1etaSC);
	//double etaRange_ = EtaRange(ZLep1etaSC,ZLep2etaSC);
	//if( ETARANGE==etaRange_)
	//{
        //  if(Mode == "ScaleMakeMC")
	//  DoScaleSmearScan(ZLep1Pt,ZLep1Pz,ZLep1En,ZLep1Phi,
	//                   ZLep2Pt,ZLep2Pz,ZLep2En,ZLep2Phi,mTTW);
	//  if(Mode == "ScaleMakeRD")h1_ZmassDaughEtaRD->Fill(Zmass);
	//}
	//  //wCand.lep_pt_corr = gRandom->Gaus(wCand.lep_pt*lepScale,lepRes);
      }

      if(Mode == "ScaleMakeMC"||Mode == "ScaleMakeRD")
	if( (AnaChannel == "ElectronLowPU" ) || AnaChannel=="ElectronHighPU")
	{
	  if(Mode == "ScaleMakeMC")
	  {
	    newZlep1Pt = 1.0/EleScaleRD(ZLep1etaSC)*ZLep1Pt;
	    newZlep2Pt = 1.0/EleScaleRD(ZLep2etaSC)*ZLep2Pt;
	    
	    PtEtaPhiMLorentzVector Zele1_4(	  newZlep1Pt,ZLep1etaSC,ZLep1Phi,elemass);
	    PtEtaPhiMLorentzVector Zele2_4(   newZlep2Pt,ZLep2etaSC,ZLep2Phi,elemass);

	    corr1 = gRandom->Gaus(Zele1_4.E(), EleSmearMC(ZLep1etaSC))/Zele1_4.E();
	    corr2 = gRandom->Gaus(Zele2_4.E(), EleSmearMC(ZLep2etaSC))/Zele2_4.E();
	    
	    PtEtaPhiMLorentzVector Z_4 =  corr1*Zele1_4 + corr2* Zele2_4;
	    h1_ZmassCorr->Fill(Z_4.M(),mTTW);
	  
	    //Barrel Barrel
	    if(fabs(ZLep1etaSC) >= 0.0   && fabs(ZLep1etaSC) < 1.4442)
	    {
	      if(fabs(ZLep2etaSC) >= 0.0   && fabs(ZLep2etaSC) < 1.4442)
		h1_ZmassCorr_BB->Fill(Z_4.M(),mTTW);
	    }

	    //Barrel Endcap
	    if(fabs(ZLep1etaSC) >= 0.0   && fabs(ZLep1etaSC) < 1.4442)
	    {
	      if(fabs(ZLep2etaSC) >= 1.566   && fabs(ZLep2etaSC) < 2.5)
		h1_ZmassCorr_BE->Fill(Z_4.M(),mTTW);
	    }else if(fabs(ZLep1etaSC) >= 1.566   && fabs(ZLep1etaSC) < 2.5)
	    {
	      if(fabs(ZLep2etaSC) >= 0.0   && fabs(ZLep2etaSC) < 1.4442)
		h1_ZmassCorr_BE->Fill(Z_4.M(),mTTW);
	    }

	    // Endcap Endcap
	    if(fabs(ZLep1etaSC) >= 1.566  && fabs(ZLep1etaSC) < 2.5)
	    {
	      if(fabs(ZLep2etaSC) >= 1.566   && fabs(ZLep2etaSC) < 2.5)
		h1_ZmassCorr_EE->Fill(Z_4.M(),mTTW);
	    }
	  }
	}

      h2_ZLep1_ZLep2->Fill(ZLep1Pt,ZLep2Pt);
      h2_Zmass_ZLep1->Fill(Zmass,ZLep1Pt);
      h2_Zmass_ZLep2->Fill(Zmass,ZLep2Pt);
      
      h1_Zpt->Fill(Zpt,mTTW);
      h2_Zpt_ZLep1->Fill(Zpt,ZLep1Pt);
      h2_Zpt_ZLep2->Fill(Zpt,ZLep2Pt);

      h1_Zmass->Fill(Zmass,mTTW);


      //MisChargeStudy
  //    if(AnaChannel =="ElectronHighPU"){
  //    if( FillMisChargeInfo()) return;}

      // Barrel Barrel uncorrected
      if(fabs(ZLep1etaSC) >= 0.0   && fabs(ZLep1etaSC) < 1.4442)
      {
	if(fabs(ZLep2etaSC) >= 0.0   && fabs(ZLep2etaSC) < 1.4442)
	  h1_Zmass_BB->Fill(Zmass,mTTW);
      }

      //Barrel Endcap uncorrected
      if(fabs(ZLep1etaSC) >= 0.0   && fabs(ZLep1etaSC) < 1.4442)
      {
	if(fabs(ZLep2etaSC) >= 1.566   && fabs(ZLep2etaSC) < 2.5)
	  h1_Zmass_BE->Fill(Zmass,mTTW);
      }else if(fabs(ZLep1etaSC) >= 1.566   && fabs(ZLep1etaSC) < 2.5)
      {
	if(fabs(ZLep2etaSC) >= 0.0   && fabs(ZLep2etaSC) < 1.4442)
	  h1_Zmass_BE->Fill(Zmass,mTTW);
      }

      // Endcap Endcap uncorrected
      if(fabs(ZLep1etaSC) >= 1.566  && fabs(ZLep1etaSC) < 2.5)
      {
	if(fabs(ZLep2etaSC) >= 1.566   && fabs(ZLep2etaSC) < 2.5)
	  h1_Zmass_EE->Fill(Zmass,mTTW);
      }


      if(Mode == "RecoilRD" || Mode == "RecoilMC" )
      {
        //Z mass cut
        if( Zmass > ReCoil_MassLow && Zmass < ReCoil_MassHigh){
          h2_u1Zpt->Fill(ZptRecoil,u1Z);
          h2_u2Zpt->Fill(ZptRecoil,u2Z);
          h2_u3Zpt->Fill(ZptRecoil,u3Z);
	  for( int iPt(0);iPt<u1Bin;iPt++)
	  {
	    if( ZptRecoil>= RecoilBins[iPt] && ZptRecoil < RecoilBins[iPt+1])
	    {
	      h1_u1Z[iPt]->Fill(u1Z);
	      h1_u2Z[iPt]->Fill(u2Z);
	      h1_u3Z[iPt]->Fill(u3Z);
	    }
	  }
        }
      }
    }
  }//Ntries
  cout<<"Passed W evts: "<<mNWevt<<"   Passed Z evts: "<<mNZevt<<endl;
  //Results======================

//  TString resultDir = AnaChannel;
////  TString resultDir = "results";
//  gSystem->mkdir(resultDir);
  TFile *myFile;
  if(ETARANGE > -999)
  {
    char tempStr[30];
    sprintf(tempStr,"_Eta_%d.root",ETARANGE);
    myFile=new TFile(resultDir+"/"+OutFileName+tempStr,"RECREATE");
  }else{
    myFile=new TFile(resultDir+"/"+OutFileName+".root","RECREATE");
  }
  ofstream Fout;
  TString FoutName;
  if(ETARANGE > -999)
  {
    char tempStr[30];
    sprintf(tempStr,"_Eta_%d",ETARANGE);
    FoutName = resultDir+"/"+OutFileName+tempStr+"_Summary.txt";
  }else{
    FoutName = resultDir+"/"+OutFileName+"_Summary.txt";
  }
  Fout.open(FoutName);
  
  cout<<"selected converted: "<<evtSelected<<" +- "<<TMath::Sqrt(evtSelected)<<endl;
  Fout<<"Bin\t0\tSignal\t"<<evtSelected<<"\tError\t"<<TMath::Sqrt(evtSelected)<<endl;

  for(int i(0); i<NwPtBin;i++)
  {
    cout<<"Bin("<<i+1<<" selected converted: "<<mNselected4Bin[i]<< "+- "<<TMath::Sqrt(mNselected4Bin[i])<<endl;
    Fout<<"Bin("<<i+1<<") selected converted: "<<mNselected4Bin[i]<< "+- "<<TMath::Sqrt(mNselected4Bin[i])<<endl;
  }

  Fout.close();


  //W inclusive ABCD regions output txt files.
  if(ETARANGE > -999)
  {
    char tempStr[30];
    sprintf(tempStr,"_Eta_%d",ETARANGE);
    FoutName = resultDir+"/"+OutFileName+tempStr+"_SummaryA.txt";
    // FoutName = resultDir+"/"+OutFileName+tempStr+"_SummaryD.txt"; // ucomment this line for ABCD D region
  }else{
    FoutName = resultDir+"/"+OutFileName+"_SummaryA.txt";
    // FoutName = resultDir+"/"+OutFileName+"_SummaryD.txt"; // ucomment this line for ABCD D region
  }
  Fout.open(FoutName);
  for(int i(0); i<NWptBinPlus;i++)
  {
    Fout<<"Bin\t"<<i<<"\tSignal\t"<<mNmetA[i]<<"\tError\t"<<TMath::Sqrt(mNmetA[i])<<endl;
  }
  Fout.close();
 
  if(ETARANGE > -999)
  {
    char tempStr[30];
    sprintf(tempStr,"_Eta_%d",ETARANGE);
    FoutName = resultDir+"/"+OutFileName+tempStr+"_SummaryB.txt";
    // FoutName = resultDir+"/"+OutFileName+tempStr+"_SummaryC.txt"; // ucomment this line for ABCD C region

  }else{
    FoutName = resultDir+"/"+OutFileName+"_SummaryB.txt";
    // FoutName = resultDir+"/"+OutFileName+"_SummaryC.txt"; // ucomment this line for ABCD C region
  }
  Fout.open(FoutName);
  for(int i(0); i<NWptBinPlus;i++)
  {
    Fout<<"Bin\t"<<i<<"\tSignal\t"<<mNmetB[i]<<"\tError\t"<<TMath::Sqrt(mNmetB[i])<<endl;
  }
  Fout.close();


  //W+  ABCD regions output txt files
  if(ETARANGE > -999)
  {
    char tempStr[30];
    sprintf(tempStr,"_Eta_%d",ETARANGE);
    FoutName = resultDir+"/"+OutFileName+tempStr+"_Summary_Plus_A.txt";
    //FoutName = resultDir+"/"+OutFileName+tempStr+"_Summary_Plus_D.txt"; // ucomment this line for ABCD  D region
  }else{
    FoutName = resultDir+"/"+OutFileName+"_Summary_Plus_A.txt";
    //FoutName = resultDir+"/"+OutFileName+"_Summary_Plus_D.txt"; //  ucomment this line for ABCD D region
  }
  Fout.open(FoutName);
  for(int i(0); i<NWptBinPlus;i++)
  {
    Fout<<"Bin\t"<<i<<"\tSignal\t"<<mNmetAp[i]<<"\tError\t"<<TMath::Sqrt(mNmetAp[i])<<endl;
  }
  Fout.close();

  if(ETARANGE > -999)
  {
    char tempStr[30];
    sprintf(tempStr,"_Eta_%d",ETARANGE);
    FoutName = resultDir+"/"+OutFileName+tempStr+"_Summary_Plus_B.txt";
    //FoutName = resultDir+"/"+OutFileName+tempStr+"_Summary_Plus_C.txt"; //  ucomment this line for ABCD  C region
  }else{
    FoutName = resultDir+"/"+OutFileName+"_Summary_Plus_B.txt";
    //FoutName = resultDir+"/"+OutFileName+"_Summary_Plus_C.txt"; // ucomment this line for ABCD  C region
  }
  Fout.open(FoutName);
  for(int i(0); i<NWptBinPlus;i++)
  {
    Fout<<"Bin\t"<<i<<"\tSignal\t"<<mNmetBp[i]<<"\tError\t"<<TMath::Sqrt(mNmetBp[i])<<endl;
  }
  Fout.close();

  //W-  ABCD regions output txt files
   if(ETARANGE > -999)
   {
     char tempStr[30];
     sprintf(tempStr,"_Eta_%d",ETARANGE);
     FoutName = resultDir+"/"+OutFileName+tempStr+"_Summary_Minus_A.txt";
     //FoutName = resultDir+"/"+OutFileName+tempStr+"_Summary_Minus_D.txt"; // ucomment this line for ABCD D region
   }else{
     FoutName = resultDir+"/"+OutFileName+"_Summary_Minus_A.txt";
     //FoutName = resultDir+"/"+OutFileName+"_Summary_Minus_D.txt"; // ucomment this line for ABCD D region
   }
   Fout.open(FoutName);
   for(int i(0); i<NWptBinPlus;i++)
   {
     Fout<<"Bin\t"<<i<<"\tSignal\t"<<mNmetAm[i]<<"\tError\t"<<TMath::Sqrt(mNmetAm[i])<<endl;
   }
   Fout.close();

   if(ETARANGE > -999)
   {
     char tempStr[30];
     sprintf(tempStr,"_Eta_%d",ETARANGE);
     FoutName = resultDir+"/"+OutFileName+tempStr+"_Summary_Minus_B.txt";
     //FoutName = resultDir+"/"+OutFileName+tempStr+"_Summary_Minus_C.txt"; // ucomment this line for ABCD C region
   }else{
     FoutName = resultDir+"/"+OutFileName+"_Summary_Minus_B.txt";
     //FoutName = resultDir+"/"+OutFileName+"_Summary_Minus_C.txt"; // ucomment this line for ABCD C region
   }
   Fout.open(FoutName);
   for(int i(0); i<NWptBinPlus;i++)
   {
     Fout<<"Bin\t"<<i<<"\tSignal\t"<<mNmetBm[i]<<"\tError\t"<<TMath::Sqrt(mNmetBm[i])<<endl;
   }

  h1_W_Multi->Write();
  h1_W_Acop->Write();
  h1_GlbMuChi2->Write();
  h1_muonHits->Write();
  
  h1_W_pt->Write();
  h1_Wp_pt->Write();
  h1_Wm_pt->Write();
  h1_W_pt_EffCorr->Write();
  h1_Wp_pt_EffCorr->Write();
  h1_Wm_pt_EffCorr->Write();
  h1_Wp_pt_NoLumiWeight->Write();
  h1_Wm_pt_NoLumiWeight->Write();

  h2_WpT_lepPt->Write();
  h2_WpT_lepPt_Plus->Write();
  h2_WpT_lepPt_Minus->Write();

  if(Mode == "DumpUnfInfo")
  {
    h1_Truth_Rec->Write();
    h1_Truth_Rec_Even->Write();
    h1_Truth_Rec_Odd->Write();
    h1_Truth_Post->Write();
    h1_Truth_Post_Even->Write();
    h1_Truth_Post_Odd->Write();
    h1_Truth_Post_EffCorr->Write();
    h1_Truth_Post_EffCorr_weightFSR->Write();
    h2_Truth_Rec_AP_Post->Write();
    //for(int ipt(0);ipt<NWptBinPlus-1;ipt++)
    //{
    //  h1_pstFsr2ReconW_pt[ipt]->Write();
    //}
  }

  if(Mode == "Acceptance")
  {
    h1_Born_AP->Write();
    h1_Born_BornFid->Write();
    h1_Born_BornFid_Even->Write();
    h1_Born_BothFid->Write();
    h1_Born_BothFid_Even->Write();

    h1_Post_PostFid->Write();
    h1_Post_PostFid_Even->Write();
    h1_Post_BothFid->Write();
    h1_Post_BothFid_weightFSR->Write();
    h1_Post_BothFid_Even->Write();

    h2_PostBorn_BothFid->Write();

  }

  h1_muMatchStation->Write();
  h1_trkLayers->Write();
  h1_pixelHits->Write();
  h1_dB->Write();
  h1_dz->Write();
  h1_IsoCom03->Write();
  h1_IsoCom04->Write();
  h1_IsoHad03->Write();
  h1_IsoHad04->Write();
  h1_IsoBeta03->Write();
  h1_IsoBeta04->Write();
  h1_W_Lept1_pt->Write();

  h1_W_Lept1_pt1->Write();
  h1_W_Neut_pt1->Write();
  h1_npileup1->Write();
  h1_Vtx_Prim1->Write();
  h1_Vtx_Good1->Write();
  
  h1_W_Met->Write();
  h1_W_Born_Met->Write();
  h1_W_MVA_Met->Write();
  h1_W_NoPU_Met->Write();
  h1_W_genMEtTrue->Write();

  if(AnaChannel == "ElectronHighPU" )
  {
  h1_W_Lep1_eta->Write();
  h1_W_Mt->Write();
  h1_W_Neu_All->Write();
  for( int i(0);i<EtaBin;i++)
  {
    h1_W_Neu_Eta_I[i]->Write();
    h1_W_Neu_Eta_P[i]->Write();
    h1_W_Neu_Eta_M[i]->Write();
    h1_WSide_Neu_eta[i]->Write();
    h1_WpSide_Neu_eta[i]->Write();
    h1_WmSide_Neu_eta[i]->Write();
  }
  }
  if((AnaChannel == "ElectronLowPU" )|| (AnaChannel == "MuonLowPU" ) )
  for( int i=0;i<NWptBinPlus;i++)
  {
    h1_W_Neu_pt[i]->Write();
    h1_GenW_Neu_pt[i]->Write();
    h1_WSide_Neu_pt[i]->Write();
    h2_Met_WpT[i]->Write();
    h2_Met_LepPt[i]->Write();
    h1_Wp_Neu_pt[i]->Write();
    h1_GenWp_Neu_pt[i]->Write();
    h1_WpSide_Neu_pt[i]->Write();
    h1_Wm_Neu_pt[i]->Write();
    h1_GenWm_Neu_pt[i]->Write();
    h1_WmSide_Neu_pt[i]->Write();
    h1_W_pt_RecoPreFsrGenRes[i]->Write();
    h1_W_pt_RecoPstFsrGenRes[i]->Write();
  }
//MisChargeStudy
/*    if(AnaChannel=="ElectronHighPU"){
    h1_Zmass_QAll->Write();
    for( int i=0;i<lept1eta;i++)
    {
     for(int j=0;j<lept2eta;j++){
       h1_Zmass_QThree[i][j]->Write();
       h1_Zmass_QNo[i][j]->Write();
       h1_Zmass_QNoSame[i][j]->Write();
       h1_Zmass_QThreeSame[i][j]->Write();
       }
    }
    }
*/
//--------------

  h1_Vtx_Prim->Write();
  h1_Vtx_Good->Write();

  //Z----------
  h1_diLeptVtxProb->Write();
  h1_Zmass->Write();
  h1_Zmass_BB->Write();
  h1_Zmass_BE->Write();
  h1_Zmass_EE->Write();
  h1_ZmassCorr->Write();
  h1_ZmassCorr_BB->Write();
  h1_ZmassCorr_BE->Write();
  h1_ZmassCorr_EE->Write();

  h2_u1Zpt->Write();
  h2_u2Zpt->Write();
  h2_u3Zpt->Write();

  h2_ZLep1_ZLep2->Write();
  h2_Zmass_ZLep1->Write();
  h2_Zmass_ZLep2->Write();

  h1_Zpt->Write();
  h2_Zpt_ZLep1->Write();
  h2_Zpt_ZLep2->Write();

// MVAnoPUMETana study
  //if ("Mode==NoPUMEt")
  //{
  h1_Z_Met->Write();
  h1_Z_genMEtTrue->Write();
  h1_Z_MVA_Met->Write();
  h1_Z_NoPU_Met->Write();
  //  h1_Z_Gen_Met->Write();
  //}
  if(Mode == "RecoilRD" || Mode == "RecoilMC")
  for( int i(0);i<u1Bin;i++)
  {
    h1_u1Z[i]->Write();
    h1_u2Z[i]->Write();
    h1_u3Z[i]->Write();
    h1_u1W[i]->Write();
    h1_u2W[i]->Write();
    h1_u3W[i]->Write();
  }
  //Simulation Method
  if(Mode =="ScaleMakeMC" || Mode =="ScaleMakeRD")
  {
    if( AnaChannel == "ElectronLowPU" )
    {
      for(int i(0);i<ScElCombiBins;i++)
      {
	h1_ZmassDaughEta[i]->Write();
      }
    }

    if( AnaChannel=="ElectronHighPU")
    {
      for(int i(0);i<ScElCombiBinsHighPU;i++)
      {
        h1_ZmassDaughEta[i]->Write();
      }
    }

    if( (AnaChannel == "MuonLowPU" ) || AnaChannel=="MuonHighPU")
    {
      for(int i(0);i<ScMuCombiBins;i++)
      {
	h1_ZmassDaughEtaMu[i]->Write();
      }
    }
  }
  Fout.close();
  //FSRout.close();
  myFile->Write();
  gBenchmark->Show("WpT");
}
void WpT::Nselected4Bin()
{
  for(int i(0);i<NwPtBin;i++)
  {
    if( wCand.pt >= Bins[i] && wCand.pt <Bins[i+1]) mNselected4Bin[i]+=mTTW;
  }
}
int WpT::InitVar()
{
  cout<<"Initialize variable at WpT class ==========="<<endl;
  evtCnt = 0;
  mNWevt = 0;
  for(int i(0);i<NwPtBin;i++)
  {
    mNselected4Bin[i]=0;
  }
  for(int i(0);i<NWptBinPlus;i++)
  {
    mNmetA [i]= 0.0;
    mNmetB [i]= 0.0;
    mNmetAp[i]= 0.0;
    mNmetBp[i]= 0.0;
    mNmetAm[i]= 0.0;
    mNmetBm[i]= 0.0;

  }
  return 0;
}
int WpT::InitVar4Evt()
{
  //cout<<"WpT::InitVar4Evt ==========================="<<endl;
  WLepNeu::InitVar4Evt();
  return 0;
}
int WpT::VertexCut()
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
double WpT::CalcEvtWeight()
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
int WpT::WbestSelect()
{
  for(int iw(0); iw<wCand.size; iw++)
  {
    //additional lepton count
    if(AnaChannel == "MuonLowPU" )    if(AddMuonCut(iw)>0) addLepN++;
    if(AnaChannel == "MuonHighPU")    if(AddMuonCut(iw)>0) addLepN++;
    if(AnaChannel == "ElectronLowPU" )if(AddElectronCut(iw)>0) addLepN++;
    if(AnaChannel == "ElectronHighPU")if(AddElectronCutHighPU(iw)>0) addLepN++;
    if(AnaChannel == "TauHighPU")if(TauCut(iw)>0) addLepN++;

    if( ((AnaChannel == "MuonLowPU" ) && (MuonCut(iw) >0))||
	((AnaChannel == "MuonHighPU") && (MuonCut(iw) >0))||
	((AnaChannel == "ElectronLowPU" ) && (ElectronCut(iw) > 0))||
	((AnaChannel =="ElectronHighPU") &&  (ElectronCutHighPU(iw) > 0)) ||
	((AnaChannel =="TauHighPU") && (TauCut(iw)) > 0)
	  //Best Candidate selection
    )if( wCand.lep_pt < (*W_Lept1_pt)[iw])
    {
	wCand.idxBest = iw;
	wCand.Pass = true;
	if( RunOnMC)
	{
	  if((abs((*GenW_BornLept1_id)[0])==12)
	    || (abs((*GenW_BornLept1_id)[0])==14)
	    || (abs((*GenW_BornLept1_id)[0])==16))
	  {
	    genInfo.BornW_Nu_Pt = (*GenW_BornLept1_pt)[iw];
	    genInfo.BornW_Nu_Cnt ++;
	  }else if((abs((*GenW_BornLept2_id)[0])==12)
	   || (abs((*GenW_BornLept2_id)[0])==14)
	   || (abs((*GenW_BornLept2_id)[0])==16))
	  {
	    genInfo.BornW_Nu_Pt = (*GenW_BornLept2_pt)[iw];
	    genInfo.BornW_Nu_Cnt ++;
	  }else{
	    cout << "There is no BornW_Nu_Pt" << endl;
	  }
	}

	wCand.lep_pt = (*W_Lept1_pt)[iw];
	wCand.lep_phi = (*W_Lept1_phi)[iw];
	wCand.Nu_px	= pfMEt_x; //i->iw
	wCand.Nu_py	= pfMEt_y; //i->iw

	if(AnaChannel == "ElectronLowPU" )
	{
	  wCand.lep_etaSC = (*W_Lept1_etaSC)[iw];
	}
	wCand.lep_eta = (*W_Lept1_eta)[iw];
	wCand.pt = (*W_pt)[iw];
	w_acop= (*W_Acop)[iw];
if(Debug)cout<<"check point 7"<<endl;
	//wCand.charge = (*W_Charge)[iw];
	//Gen Neutrino distribution for selected events
	if(GenW_Born_Id->size()>0)
	{
	  if( abs((*GenW_PostLept1_id)[0])==14 || //Nuet_Mu
	      abs((*GenW_PostLept1_id)[0])==12) //Nuet_Ele
	    genInfo.BornW_Nu_Pt =(*GenW_PostLept1_pt)[0];

	  if( abs((*GenW_PostLept2_id)[0])==14 || 
	      abs((*GenW_PostLept2_id)[0])==12)
	    genInfo.BornW_Nu_Pt =(*GenW_PostLept2_pt)[0];
	}
	if(Mode == "AllCorrectionsMC" || Mode == "RecoilCorrMC")if(GenW_Born_Id->size()>0)
	{
          wCand.genIdx = (*W_Lept1_genIdxMatch)[iw];
	}//RecoilCorr
	if(Mode == "RecoilRD" || Mode == "RecoilMC")
	{
	  //Recoil = -Met -Lepts
	  TVector2 RecoilVector(
	  	-(*W_Neut_px)[iw]-(*W_Lept1_px)[iw],
	  	-(*W_Neut_py)[iw]-(*W_Lept1_py)[iw]);
	  //if( GenW_Born_Id->size() < 1)cout<<"GenW size is "<<GenW_Born_Id->size()<<endl;
	  if( Mode == "RecoilMC")if(GenW_Born_Id->size() > 0)
	  {
	    int gi = (*W_Lept1_genIdxMatch)[iw];
	    //if( gi != 0 || iw != 0)
	    //cout<<"Gen Idx: "<<gi<<" iw: "<<iw<<endl;
            if( fabs((*W_Lept1_genDeltaR)[iw]) > 0.025)
	    {
	      //cout<<"W not MC truth"<<endl;
	      gi = 0; //Let's use the one
	    }
	    if(gi < 0) gi = 0;
	    //genBeFsrW_pt = (*GenW_pt)[gi];

	    TVector2 genAfFsrW_pt_2D(
		(*GenW_PostLept1_px)[gi]+(*GenW_PostLept2_px)[gi],
		(*GenW_PostLept1_py)[gi]+(*GenW_PostLept2_py)[gi]);
	    genInfo.PostW_pt= genAfFsrW_pt_2D.Mod();
	    //BosonNorm = TMath::Sqrt(
	//	(*GenW_px)[gi]*(*GenW_px)[gi]+
	//	(*GenW_py)[gi]*(*GenW_py)[gi]);
	    //u1 = B.u, u2 = B cross u
	    u1W =RecoilVector*genAfFsrW_pt_2D/genInfo.PostW_pt;
	    u2W =(RecoilVector.Px()*genAfFsrW_pt_2D.Py()-RecoilVector.Py()*genAfFsrW_pt_2D.Px())/genInfo.PostW_pt;
	    u3W =RecoilVector*genAfFsrW_pt_2D/genInfo.PostW_pt+genInfo.PostW_pt;
	  }
	}
      }//Cut and Bigger pt

      //if(Mode == "AllCorrectionsRD" )
      //{
	//if(AnaChannel == "ElectronLowPU" )
	//{
	 // if( wCand.charge > 0)
	  //{
	   // TTW=TTW / ElePlusEffiCorrection(wCand.lep_pt,wCand.lep_etaSC);
	  //}else  if( wCand.charge < 0)
	  //{
	    //TTW=TTW / EleMinusEffiCorrection(wCand.lep_pt,wCand.lep_etaSC);
	  //}
	//}
	//if(AnaChannel == "MuonLowPU")
	//{
	  //if( wCand.charge > 0)
	  //{
	    //TTW=TTW / MuonPlusEffiCorrection(wCand.lep_pt,wCand.lep_eta);
	  //}else  if( wCand.charge < 0)
	  //{
	    //TTW=TTW / MuonMinusEffiCorrection(wCand.lep_pt,wCand.lep_eta);
	  //}
	//}
      //}

      if(AnaChannel == "ElectronLowPU" )
      {
	if( wCand.charge > 0)
	{
	  effSf_ = ElePlusEffiCorrection(wCand.lep_pt,wCand.lep_etaSC);
	}
	else  if( wCand.charge < 0)
	{
	  effSf_ = EleMinusEffiCorrection(wCand.lep_pt,wCand.lep_etaSC);
	}
      }
      if(AnaChannel == "MuonLowPU" )
      {
	if( wCand.charge > 0)
	{
	  effSf_ = MuonPlusEffiCorrection(wCand.lep_pt,wCand.lep_eta);
	}
	else  if( wCand.charge < 0)
	{
	  effSf_ = MuonMinusEffiCorrection(wCand.lep_pt,wCand.lep_eta);
	}
      }

if(Debug)cout<<"check point 8"<<endl;
      //Side Band
      if( ((AnaChannel == "MuonLowPU" ) && MuonCutSide(iw) >0)||
	  ((AnaChannel == "ElectronLowPU" ) && ElectronCutSide(iw) > 0)||
	  (AnaChannel =="ElectronHighPU" && ElectronCutSideHighPU(iw) > 0)
      )
      //if( CutSide(iw)> 0 && lep_pt_side < (*W_Lept1_pt)[iw])
      {
	w_pt_side = (*W_pt)[iw];
	wCand.Met_side = (*W_Neut_pt)[iw];

	if(Debug)cout<<"check point 9"<<endl;
	//lep_pt_side = (*W_Lept1_pt)[iw];
	if((*W_Charge)[iw]> 0)	  
	{
	  if(Mode == "AllCorrectionsMC" )
	  {
	    h1_WSide_Neu_pt[0]->Fill(wCand.Met_side,mTTW*effSf_);
	    h1_WpSide_Neu_pt[0]->Fill(wCand.Met_side,mTTW*effSf_);
	  }else{
	    h1_WSide_Neu_pt[0]->Fill(wCand.Met_side,mTTW);
	    h1_WpSide_Neu_pt[0]->Fill(wCand.Met_side,mTTW);
	  }

	  //Fill MET sideband for WQA, Wplus case
	  if(AnaChannel == "ElectronHighPU") {
	    for(int iEtaSD=0;iEtaSD<NWqaBins;iEtaSD++) {
	      if (fabs(wCand.lep_eta) > wqaMetMNBins[iEtaSD] && fabs(wCand.lep_eta) < wqaMetMXBins[iEtaSD] )  {
		h1_WSide_Neu_eta[iEtaSD]->Fill(wCand.Met_side,mTTW);
		h1_WpSide_Neu_eta[iEtaSD]->Fill(wCand.Met_side,mTTW);
		//	  h1_W_Neu_Eta_M[wqaWmIdx]->Fill(wCand.Met,mTTW);
	      }
	    }
	  }	    
if(Debug)cout<<"check point 11"<<endl;
	  //Wpt case
	  for(int iBin(0);iBin<NWptBinPlus-1;iBin++) {
	    if( w_pt_side >= Bins[iBin] && w_pt_side < Bins[iBin+1] ) {
	      
	      if(Mode == "AllCorrectionsMC" )
	      {
		h1_WSide_Neu_pt[iBin+1]->Fill(wCand.Met_side,mTTW*effSf_);
		h1_WpSide_Neu_pt[iBin+1]->Fill(wCand.Met_side,mTTW*effSf_);
	      }else{
		h1_WSide_Neu_pt[iBin+1]->Fill(wCand.Met_side,mTTW);
		h1_WpSide_Neu_pt[iBin+1]->Fill(wCand.Met_side,mTTW);
	      }
	  
	    }
	  }
	}
	else if( (*W_Charge)[iw] <0) 
	{
	  
	  if(Mode == "AllCorrectionsMC" )
	  {
	    h1_WSide_Neu_pt[0]->Fill(wCand.Met_side,mTTW*effSf_);
	    h1_WmSide_Neu_pt[0]->Fill(wCand.Met_side,mTTW*effSf_);
	  }else{
	    h1_WSide_Neu_pt[0]->Fill(wCand.Met_side,mTTW);
	    h1_WmSide_Neu_pt[0]->Fill(wCand.Met_side,mTTW);
	  }

	  if(Debug)cout<<"check point 12"<<endl;
	  //Fill MET sideband for WQA, Wminus case
	  if(AnaChannel == "ElectronHighPU") {
	    for(int iEtaSD=0;iEtaSD<NWqaBins;iEtaSD++) {
	      if (fabs(wCand.lep_eta) > wqaMetMNBins[iEtaSD] && fabs(wCand.lep_eta) < wqaMetMXBins[iEtaSD] ) {		
		h1_WSide_Neu_eta[iEtaSD]->Fill(wCand.Met_side,mTTW);
		h1_WmSide_Neu_eta[iEtaSD]->Fill(wCand.Met_side,mTTW);
	      }
	    }
	  }
	  if(Debug)cout<<"check point 13"<<endl;
	  //Wpt case
	  for(int iBin(0);iBin<NWptBinPlus-1;iBin++) {
	    if( w_pt_side >= Bins[iBin] && w_pt_side < Bins[iBin+1] ) {

	      if(Mode == "AllCorrectionsMC" )
	      {
		h1_WSide_Neu_pt[iBin+1]->Fill(wCand.Met_side,mTTW*effSf_);
		h1_WmSide_Neu_pt[iBin+1]->Fill(wCand.Met_side,mTTW*effSf_);
	      }else{
		h1_WSide_Neu_pt[iBin+1]->Fill(wCand.Met_side,mTTW);
		h1_WmSide_Neu_pt[iBin+1]->Fill(wCand.Met_side,mTTW);
	      }
	    }
	  }
	}else {
	    cout<<"strange case: charge = 0 ^^^^^^^^^^^^^^^^^^^^^^^^^"<<endl;
	    exit(0);}
	}
    }
  return 0;
}
int WpT::ZbestSelect()
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
    if((Mode =="RecoilRD")||(Mode == "RecoilMC"))if((*Z_Lept2_pt)[iz] < 15 )continue;
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
    Zboson.Pass=true;
    tmpVar = (*Z_diLeptVtxProb)[iz];

    if( fabs(Channel) != GenType::kTau) if( tmpVar > diLeptVtxProb )
    {
      Zboson.idxBest = iz;
      diLeptVtxProb = tmpVar;
	Zmass		= (*Z_Mass)[iz];
	ZLep1Pt		= (*Z_Lept1_pt)[iz];
	ZLep1Pz		= (*Z_Lept1_pz)[iz];
	ZLep1En		= (*Z_Lept1_en)[iz];
	ZLep1Phi	= (*Z_Lept1_phi)[iz];
	ZLep2Pt		= (*Z_Lept2_pt)[iz];
	ZLep2Pz		= (*Z_Lept2_pz)[iz];
	ZLep2En		= (*Z_Lept2_en)[iz];
	//cout<<"energy: "<<ZLep2En<<endl;
	ZLep2Phi	= (*Z_Lept2_phi)[iz];

	TVector2 ZDiLep2D(
                (*Z_Lept1_px)[iz]+(*Z_Lept2_px)[iz],
                (*Z_Lept1_py)[iz]+(*Z_Lept2_py)[iz]);
        Zpt = ZDiLep2D.Mod();

	if((AnaChannel == "ElectronLowPU" ) ||AnaChannel=="ElectronHighPU"){
	  ZLep1etaSC	= (*Z_Lept1_etaSC)[iz];
	  ZLep2etaSC	= (*Z_Lept2_etaSC)[iz];
	}else{
	  ZLep1etaSC	= (*Z_Lept1_eta)[iz];
	  ZLep2etaSC	= (*Z_Lept2_eta)[iz];
	}

	//cout<<"ZLep1 px: "<<(*Z_Lept1_px)[iz]<<" pt cos phi :"<<ZLep1Pt*cos((*Z_Lept1_phi)[iz])<<endl;
	if(Mode == "RecoilRD" || Mode =="RecoilMC"){
	  //Recoil = -Met - Z
	  TVector2 RecoilVector(
	  	-(*Z_Neut_px)[iz]-(*Z_px)[iz],
	  	-(*Z_Neut_py)[iz]-(*Z_py)[iz]);
	  //if(Mode == "RecoilRD")
	  //{
	    TVector2 DiLep2D(
	      (*Z_px)[iz],
	      (*Z_py)[iz]
	      );
	    ZptRecoil = (*Z_pt)[iz];
	    //u1 = B.u, u2=B cross u
	    u1Z = RecoilVector*DiLep2D/DiLep2D.Mod();
	    u2Z = (RecoilVector.Px()*DiLep2D.Py()-RecoilVector.Py()*DiLep2D.Px())/DiLep2D.Mod();
	    u3Z = RecoilVector*DiLep2D/DiLep2D.Mod()+DiLep2D.Mod();
	    //u1Z = ( (*Z_px)[iz]*ux+(*Z_py)[iz]*uy )/BosonNorm;
	    //u2Z = ( (*Z_px)[iz]*uy - (*Z_py)[iz]*ux)/BosonNorm;
	  //}else if(Mode == "RecoilMC")
	  //{
	    //int gi = (*Z_Lept1_genIdxMatch)[iz];
	    //TVector2 genDiLep2D(
//		(*GenZ_Lept1_px)[gi]+(*GenZ_Lept2_px)[gi],
//		(*GenZ_Lept1_py)[gi]+(*GenZ_Lept2_py)[gi]);
//	    ZptRecoil = genDiLep2D.Mod();
//	    //u1 = B.u, u2=B cross u
//	    u1Z = RecoilVector*genDiLep2D/genDiLep2D.Mod();
//	    u2Z = (RecoilVector.Px()*genDiLep2D.Py()-RecoilVector.Py()*genDiLep2D.Px())/genDiLep2D.Mod();
	    //u1Z = ((*GenZ_px)[iz]*ux+(*GenZ_py)[iz]*uy )/BosonNorm;
	    //u2Z = ((*GenZ_px)[iz]*uy-(*GenZ_py)[iz]*ux)/BosonNorm;
//	  }
	}//fi Recoil or RecoilMC
    }//fi diLeptVtxProb
    ZLep2PtTmp = (*Z_Lept2_pt)[iz];
    if( fabs(Channel) == GenType::kTau) if( ZLep2PtTmp > ZLep2Pt )
    {
      Zboson.idxBest = iz;
	Zmass		= (*Z_Mass)[iz];
	ZLep1Pt		= (*Z_Lept1_pt)[iz];
	ZLep1Pz		= (*Z_Lept1_pz)[iz];
	ZLep1En		= (*Z_Lept1_en)[iz];
	ZLep1Phi	= (*Z_Lept1_phi)[iz];
	ZLep2Pt		= (*Z_Lept2_pt)[iz];
	ZLep2Pz		= (*Z_Lept2_pz)[iz];
	ZLep2En		= (*Z_Lept2_en)[iz];
	//cout<<"energy: "<<ZLep2En<<endl;
	ZLep2Phi	= (*Z_Lept2_phi)[iz];

	TVector2 ZDiLep2D(
                (*Z_Lept1_px)[iz]+(*Z_Lept2_px)[iz],
                (*Z_Lept1_py)[iz]+(*Z_Lept2_py)[iz]);
        Zpt = ZDiLep2D.Mod();

	if((AnaChannel == "ElectronLowPU" ) ||AnaChannel=="ElectronHighPU"){
	  ZLep1etaSC	= (*Z_Lept1_etaSC)[iz];
	  ZLep2etaSC	= (*Z_Lept2_etaSC)[iz];
	}else{
	  ZLep1etaSC	= (*Z_Lept1_eta)[iz];
	  ZLep2etaSC	= (*Z_Lept2_eta)[iz];
	}

	//cout<<"ZLep1 px: "<<(*Z_Lept1_px)[iz]<<" pt cos phi :"<<ZLep1Pt*cos((*Z_Lept1_phi)[iz])<<endl;
	if(Mode == "RecoilRD" || Mode =="RecoilMC")
	{
	  //Recoil = -Met - Z
	  TVector2 RecoilVector(
	  	-(*Z_Neut_px)[iz]-(*Z_px)[iz],
	  	-(*Z_Neut_py)[iz]-(*Z_py)[iz]);
	  //if(Mode == "RecoilRD")
	  //{
	    TVector2 DiLep2D(
	      (*Z_px)[iz],
	      (*Z_py)[iz]
	      );
	    ZptRecoil = (*Z_pt)[iz];
	    //u1 = B.u, u2=B cross u
	    u1Z = RecoilVector*DiLep2D/DiLep2D.Mod();
	    u2Z = (RecoilVector.Px()*DiLep2D.Py()-RecoilVector.Py()*DiLep2D.Px())/DiLep2D.Mod();
	    u3Z = RecoilVector*DiLep2D/DiLep2D.Mod()+DiLep2D.Mod();
	    //u1Z = ( (*Z_px)[iz]*ux+(*Z_py)[iz]*uy )/BosonNorm;
	    //u2Z = ( (*Z_px)[iz]*uy - (*Z_py)[iz]*ux)/BosonNorm;
	  //}else if(Mode == "RecoilMC")
	  //{
	    //int gi = (*Z_Lept1_genIdxMatch)[iz];
	    //TVector2 genDiLep2D(
//		(*GenZ_Lept1_px)[gi]+(*GenZ_Lept2_px)[gi],
//		(*GenZ_Lept1_py)[gi]+(*GenZ_Lept2_py)[gi]);
//	    ZptRecoil = genDiLep2D.Mod();
//	    //u1 = B.u, u2=B cross u
//	    u1Z = RecoilVector*genDiLep2D/genDiLep2D.Mod();
//	    u2Z = (RecoilVector.Px()*genDiLep2D.Py()-RecoilVector.Py()*genDiLep2D.Px())/genDiLep2D.Mod();
	    //u1Z = ((*GenZ_px)[iz]*ux+(*GenZ_py)[iz]*uy )/BosonNorm;
	    //u2Z = ((*GenZ_px)[iz]*uy-(*GenZ_py)[iz]*ux)/BosonNorm;
//	  }
	}//fi Recoil or RecoilMC
    }//fi diLeptVtxProb
  }//Z

  return 0;
}
