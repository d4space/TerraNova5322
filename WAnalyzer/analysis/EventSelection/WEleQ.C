// $Log: WEleQ.C,v $
// Revision 1.0  2013/12/20 15:11:34  jungmin
// *** empty log message ***
#define WEleQ_cxx
//#include <iostream>
//#include <TROOT.h>                        // access to gROOT, entry point to ROOT system
//#include <TSystem.h>                      // interface to OS
#include <TBenchmark.h>                   // class to track macro running statistics
#include <algorithm>
#include "WEleQ.h"
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

void WEleQ::Loop()
{
  gBenchmark->Start("WEleQ");

  if (fChain == 0) return;
  int Ntries = fChain->GetEntries();

  wCand.size=0;
  cout<<"Total: "<<Ntries<<endl;
  double nSelect(0);
  TTW=1;
  

  int Vtx_nPrim;
  int Vtx_GoodN;
  evtCnt = 0;
  
  bool Debug(false);
  //bool Debug(true);

  for (int i(0); i<Ntries;i++)
  {
    evtCnt = i;
    //===============================
    //W study
    //===============================
    if(i % 100000 == 0) cout<<i<<"th event"<<endl;
   
    //=========
    //dump tree
    //=========
    fChain->GetEntry(i);
    //===========================
    //Initialization of Variables
    //===========================
    InitVar4Evt();

    if(AnaChannel == "ElectronHighPU")if(fabs(Channel) != GenType::kElectron) exit(-1);

    //============
    //Trigger Cut
    //============
  
    //before trigger event check.
    if(AnaChannel =="ElectronHighPU" && ElectronCutHighPUToTal(iw) > 0)
    { 
     for(int iEtaSD=0;iEtaSD<NWqaBins;iEtaSD++)
     {
      if (fabs((*W_Lept1_eta)[iw]) > wqaMetMNBins[iEtaSD] && fabs((*W_Lept1_eta)[iw]) < wqaMetMXBins[iEtaSD] ) {
       h1_W_Neu_pt_ToTal_beforeTrigger[iEtaSD]->Fill((*W_Neut_pt)[iw]);
       }
     }
    }

    if(AnaChannel=="ElectronHighPU")if(HLT_Ele27_WP80_fired<1)continue;
    //Vertex Study===========================
    Vtx_nPrim = vtx_isFake->size();
    if(Vtx_nPrim < 1 ) continue;
    // Check the VTX cuts for the largest Sum(Pt) vertex
    if( (*vtx_isFake)[0] )continue;
    if( (*vtx_ndof)[0] <= 2 ) continue; // Our Study
    if( (*vtx_z)[0] >= 24 ) continue;
    if( (*vtx_Rho)[0] >= 2 ) continue;

    Vtx_GoodN=0;
    for( int ivtx(0);ivtx<Vtx_nPrim; ivtx++)
    {
      if( (*vtx_isFake)[ivtx] )continue;
      if( (*vtx_ndof)[ivtx] <= 2 ) continue; // Our Study
      if( (*vtx_z)[ivtx] >= 24 ) continue;
      if( (*vtx_Rho)[ivtx] >= 2 ) continue;
      Vtx_GoodN++;
    }
    h1_Vtx_Prim->Fill(Vtx_nPrim);

    if(LumiWeight != 1){
      h1_Vtx_PrimPuW->Fill(Vtx_nPrim*weightin);
      h1_Vtx_GoodPuW->Fill(Vtx_GoodN*weightin);
      h1_PuWeight->Fill(weightin);
    }

    if( LumiWeight == 1)
    {
      TTW = 1;
    }else{
      TTW= LumiWeight*weight;
    }

    h1_W_Multi->Fill(wCand.size);

    /////////////////////////////
    // get the hardest Electron
    temp_elpT = -999;
    iw = -999;

    for(int ie(0); ie<wCand.size; ie++)
    {
      double current_elpT = (*W_Lept1_pt)[ie];
      if(AnaChannel == "ElectronHighPU")if(AddElectronCutHighPU(ie)>0) addLepN++;
      if(current_elpT > temp_elpT)
	{
	  temp_elpT = current_elpT;
	  iw = ie;
	}
    }
    /////////////////////////////


     // if(AnaChannel == "ElectronHighPU")if(AddElectronCutHighPU(iw)>0) addLepN++;
//cout<<"check if&if pt = "<<(*W_Lept1_pt)[iw]<<", event number = "<<i<<", eMulti = "<<wCand.size<<", sigmaIEtaIEta = "<<(*W_Lept1_sigmaIEtaIEta)[iw]<<", dEtaIn = "<<fabs((*W_Lept1_dEtaIn)[iw])<<", dPhiIn = "<<fabs((*W_Lept1_dPhiIn)[iw])<<", HoverE = "<<(*W_Lept1_HoverE)[iw]<<", dxy = "<<fabs((*W_Lept1_dxy)[iw])<<", dz = "<<fabs((*W_Lept1_dz)[iw])<<", InvE-InvP = "<<fabs((*W_Lept1_InvEminusInvP)[iw])<<", mHits = "<<fabs((*W_Lept1_mHits)[iw])<<", lep eta = "<<fabs(wCand.lep_eta)<<", W_Lept1_eta[iw] = "<<(*W_Lept1_eta)[iw]<<", lep SCeta = "<<fabs((*W_Lept1_etaSC)[iw])<<", SideCut pass ="<<ElectronCutSideHighPU(iw)<<", SignalCut pass ="<<ElectronCutHighPU(iw)<<", iw = "<<iw<<endl;

      if(AnaChannel =="ElectronHighPU" && ElectronCutHighPUToTal(iw) > 0)
       {
	 for(int iEtaSD=0;iEtaSD<NWqaBins;iEtaSD++) {
	 if (fabs((*W_Lept1_eta)[iw]) > wqaMetMNBins[iEtaSD] && fabs((*W_Lept1_eta)[iw]) < wqaMetMXBins[iEtaSD] ) {
	 h1_W_Neu_pt_ToTal[iEtaSD]->Fill((*W_Neut_pt)[iw],TTW);
	 h1_i_ToTal[iEtaSD]->Fill(i);
       }
       }
       }

      if(AnaChannel =="ElectronHighPU" && ElectronCutHighPUToTal(iw) > 0)
       {
      if(addLepN >1)
       {
	 for(int iEtaSD=0;iEtaSD<NWqaBins;iEtaSD++) {
	 if (fabs((*W_Lept1_eta)[iw]) > wqaMetMNBins[iEtaSD] && fabs((*W_Lept1_eta)[iw]) < wqaMetMXBins[iEtaSD] ) {
	 h1_W_Neu_AddElectron[iEtaSD]->Fill((*W_Neut_pt)[iw],TTW);
       }
       }
       }
       }

      if( (AnaChannel =="ElectronHighPU" && ElectronCutHighPU(iw) > 0)
      ){
if(Debug)cout<<"check point 6-2"<<endl;	
	W_pass = true;
	wCand.charge = (*W_Charge)[iw];
	//Muon Variable Study----------------------

	wCand.Met = (*W_Neut_pt)[iw];

      }//Cut and Bigger pt



      //Side Band
      if( (AnaChannel =="ElectronHighPU" && ElectronCutSideHighPU(iw) > 0)
      )
      {    
	wCand.Met_side = (*W_Neut_pt)[iw];
	for(int iEtaSD=0;iEtaSD<NWqaBins;iEtaSD++) {
	if (fabs((*W_Lept1_eta)[iw]) > wqaMetMNBins[iEtaSD] && fabs((*W_Lept1_eta)[iw]) < wqaMetMXBins[iEtaSD] )  {
	h1_W_Neu_pt_Side[iEtaSD]->Fill(wCand.Met_side,TTW);
	h1_i_Side[iEtaSD]->Fill(i);
	}
	}
if(Debug)cout<<"check point 9"<<endl;
	if((*W_Charge)[iw]> 0)	  {
	  h1_WSide_Neu_pt[0]->Fill(wCand.Met_side,TTW);
	  h1_WpSide_Neu_pt[0]->Fill(wCand.Met_side,TTW);
		if(Debug)cout<<"check point 10"<<endl;
	    for(int iEtaSD=0;iEtaSD<NWqaBins;iEtaSD++) {
	      if (fabs((*W_Lept1_eta)[iw]) > wqaMetMNBins[iEtaSD] && fabs((*W_Lept1_eta)[iw]) < wqaMetMXBins[iEtaSD] )  {
		h1_WSide_Neu_eta[iEtaSD]->Fill(wCand.Met_side,TTW);
		h1_WpSide_Neu_eta[iEtaSD]->Fill(wCand.Met_side,TTW);
	      //cut value check.	
	      if (fabs((*W_Lept1_eta)[iw]) > 0 && fabs((*W_Lept1_eta)[iw]) < 0.2 )  {
	      h1_check_side_iw->Fill(iw);
	      h1_check_side_pt->Fill((*W_Lept1_pt)[iw]);
	      h1_check_side_sigmaIetaIeta->Fill((*W_Lept1_sigmaIEtaIEta)[iw]);
              h1_check_side_dEtaIn->Fill(fabs((*W_Lept1_dEtaIn)[iw]));
	      h1_check_side_dPhiin->Fill(fabs((*W_Lept1_dPhiIn)[iw]));
	      h1_check_side_HoverE->Fill((*W_Lept1_HoverE)[iw]);
	      h1_check_side_dxy->Fill(fabs((*W_Lept1_dxy)[iw]));
	      h1_check_side_dz->Fill(fabs((*W_Lept1_dz)[iw]));
	      h1_check_side_InvE_InvP->Fill(fabs((*W_Lept1_InvEminusInvP)[iw]));
	      h1_check_side_mHits->Fill(fabs((*W_Lept1_mHits)[iw]));
	      h1_check_side_lep_eta->Fill(fabs((*W_Lept1_eta)[iw]));
	      }
	      }
	    }
	}
	else if( (*W_Charge)[iw] <0) {
	  h1_WSide_Neu_pt[0]->Fill(wCand.Met_side,TTW);
	  h1_WmSide_Neu_pt[0]->Fill(wCand.Met_side,TTW);
	  if(AnaChannel == "ElectronHighPU") {
	    for(int iEtaSD=0;iEtaSD<NWqaBins;iEtaSD++) {
	      if (fabs((*W_Lept1_eta)[iw]) > wqaMetMNBins[iEtaSD] && fabs((*W_Lept1_eta)[iw]) < wqaMetMXBins[iEtaSD] ) {		
		h1_WSide_Neu_eta[iEtaSD]->Fill(wCand.Met_side,TTW);
		h1_WmSide_Neu_eta[iEtaSD]->Fill(wCand.Met_side,TTW);
	      }
	    }
	  }
	}else {
	  cout<<"strange case: charge = 0 ^^^^^^^^^^^^^^^^^^^^^^^^^"<<endl;
	  exit(0);}
      }
    

   if(   (ElectronCutSideHighPU(iw)==-1)&&
         (ElectronCutHighPU(iw)==-1)&&
         (ElectronCutHighPUToTal(iw)==1)
      ){
        for(int iEtaSD=0;iEtaSD<NWqaBins;iEtaSD++) {
        if (fabs((*W_Lept1_eta)[iw]) > wqaMetMNBins[iEtaSD] && fabs((*W_Lept1_eta)[iw]) < wqaMetMXBins[iEtaSD] ) {
	 h1_W_Neu_other[iEtaSD]->Fill((*W_Neut_pt)[iw],TTW);
	 h1_i_other[iEtaSD]->Fill(i);
	}
	}
	}

    //Fill the W==================
    if( W_pass && addLepN <2 ){

    if(AnaChannel == "ElectronHighPU" )
    {
      h1_W_Lep1_eta->Fill(wCand.lep_eta,TTW);
      for(int iEta=0;iEta<NWqaBins;iEta++){
	if (fabs((*W_Lept1_eta)[iw]) > wqaMetMNBins[iEta] && fabs((*W_Lept1_eta)[iw]) < wqaMetMXBins[iEta] ) {
        h1_W_Neu_All[iEta]->Fill(wCand.Met,TTW);
	h1_i_All[iEta]->Fill(i);
        }
      } 
      for(int iEta=0;iEta<NWqaBins;iEta++){
	////////Inclusive Case////////////
	if (fabs((*W_Lept1_eta)[iw]) > wqaMetMNBins[iEta] && fabs((*W_Lept1_eta)[iw]) < wqaMetMXBins[iEta] ) {
	  h1_W_Neu_Eta_I[iEta]->Fill(wCand.Met,TTW);
	//cut value check.
	  if (fabs((*W_Lept1_eta)[iw]) > 0 && fabs((*W_Lept1_eta)[iw]) < 0.2 )  {
            h1_check_iw->Fill(iw);
            h1_check_pt->Fill((*W_Lept1_pt)[iw]);
            h1_check_sigmaIetaIeta->Fill((*W_Lept1_sigmaIEtaIEta)[iw]);
            h1_check_dEtaIn->Fill(fabs((*W_Lept1_dEtaIn)[iw]));
            h1_check_dPhiin->Fill(fabs((*W_Lept1_dPhiIn)[iw]));
            h1_check_HoverE->Fill((*W_Lept1_HoverE)[iw]);
            h1_check_dxy->Fill(fabs((*W_Lept1_dxy)[iw]));
            h1_check_dz->Fill(fabs((*W_Lept1_dz)[iw]));
            h1_check_InvE_InvP->Fill(fabs((*W_Lept1_InvEminusInvP)[iw]));
            h1_check_mHits->Fill(fabs((*W_Lept1_mHits)[iw]));
            h1_check_lep_eta->Fill(fabs(wCand.lep_eta));
	  }
	  if ( wCand.charge > 0 ){ /////////Plus Case////////////
	    h1_W_Neu_Eta_P[iEta]->Fill(wCand.Met,TTW);
	  }
	  else if ( wCand.charge < 0){ //////////Minus Case////////////////
	    h1_W_Neu_Eta_M[iEta]->Fill(wCand.Met,TTW);
	  }
	}
      }
    }
    
      nSelect+=TTW;

    }//good W

  }//Ntries
 
   
   //Results======================

  TString resultDir = AnaChannel;
  gSystem->mkdir(resultDir);
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




  //h1_npileup1->Write();
  //h1_Vtx_Prim1->Write();
  //h1_Vtx_Good1->Write();

  if(AnaChannel == "ElectronHighPU" )
  {
  
  //cut value check.
    h1_check_iw->Write();
    h1_check_side_iw->Write();
    h1_check_pt->Write();
    h1_check_side_pt->Write();
    h1_check_sigmaIetaIeta->Write();
    h1_check_side_sigmaIetaIeta->Write();
    h1_check_dEtaIn->Write();
    h1_check_side_dEtaIn->Write();
    h1_check_dPhiin->Write();
    h1_check_side_dPhiin->Write();
    h1_check_HoverE->Write();
    h1_check_side_HoverE->Write();
    h1_check_dxy->Write();
    h1_check_side_dxy->Write();
    h1_check_dz->Write();
    h1_check_side_dz->Write();
    h1_check_InvE_InvP->Write();
    h1_check_side_InvE_InvP->Write();
    h1_check_mHits->Write();
    h1_check_side_mHits->Write();
    h1_check_lep_eta->Write();
    h1_check_side_lep_eta->Write();
  for( int i(0);i<EtaBin;i++)
  {
  h1_W_Neu_All[i]->Write();
  h1_W_Neu_pt_Side[i]->Write();
  h1_W_Neu_pt_ToTal[i]->Write();
  h1_W_Neu_pt_ToTal_beforeTrigger[i]->Write();
  h1_W_Neu_other[i]->Write();
  h1_W_Neu_AddElectron[i]->Write();

  h1_W_Neu_Eta_I[i]->Write();
  h1_W_Neu_Eta_P[i]->Write();
  h1_W_Neu_Eta_M[i]->Write();
  h1_WSide_Neu_eta[i]->Write();
  h1_WpSide_Neu_eta[i]->Write();
  h1_WmSide_Neu_eta[i]->Write();
  
  h1_i_ToTal[i]->Write();
  h1_i_All[i]->Write();
  h1_i_other[i]->Write();
  h1_i_Side[i]->Write();

  }
  }

 // h1_Vtx_Prim->Write();
 // h1_Vtx_PrimPuW->Write();
 // h1_Vtx_Good->Write();
 // h1_Vtx_GoodPuW->Write();


  //Simulation Method
  Fout.close();
  myFile->Write();
  gBenchmark->Show("WEleQ");
}


