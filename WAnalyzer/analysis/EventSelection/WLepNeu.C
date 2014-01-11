// $Log: WLepNeu.C,v $
// Revision 1.8  2013/09/13 00:09:32  salee
// *** empty log message ***
//
//   In a ROOT session, you can do:
//      Root > .L WLepNeu.C
//      Root > WLepNeu t
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
#define WLepNeu_cxx
//#include <iostream>
//#include <TROOT.h>                        // access to gROOT, entry point to ROOT system
//#include <TSystem.h>                      // interface to OS
#include <TBenchmark.h>                   // class to track macro running statistics
#include <algorithm>
#include "WLepNeu.h"
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
int WLepNeu::InitVar()
{
  cout<<"Initialize variables at WLepNeu Class ==================="<<endl;
  return 0;
}
void WLepNeu::Loop()
{
  gBenchmark->Start("WLepNeu");
  gRandom->SetSeed(0);
//
  if (fChain == 0) return;
   //int Ntries = fChain->GetEntriesFast(); this gives 1234567890 kkk
  int Ntries = fChain->GetEntries();

  effSf_ = 1;
  cout<<"Total: "<<Ntries<<endl;
  double nSelect(0);
  TTW=1;
  

  int Vtx_nPrim;
  int Vtx_GoodN;
  double tmpVar;
  double ZLep2PtTmp;
  //Recoil Correction
  if( (Mode == "AllCorrectionsMC" || Mode == "RecoilCorrMC") ||Mode =="Unfold" )
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
    RecoilCorr= new RecoilCorrector(
      rcoil.ZRDfilename,
      rcoil.Wpfilename,rcoil.Wmfilename,
      rcoil.ZMCfilename,
      0x1234);
  //Int_t iSeed=0xDEADBEEF default seed for random number generator at constructor
  }
  //Scale Correction
  double lepScale(1);
  double lepScaleErr(0.005);
  double lepRes(0.5);
  double lepResErr(0.5);
  evtCnt = 0;
 
  int evtCnt_W(0);
  int evtCnt_Z(0);
  int evtCnt_Z_beforeCut(0);
  int evtCnt_Z_afterCut(0);

  bool Debug(false);

  TString resultDir = AnaChannel;
  if(AnaChannel == "MuonLowPU" )
    TString resultDir = "MuonLowPU";
  else if(AnaChannel == "ElectronLowPU")
    TString resultDir = "ElectronLowPU";

//  TString resultDir = "results";
  gSystem->mkdir(resultDir);
  
  //ofstream FSRout;
  //TString FSRName;
  //FSRName = resultDir+"/FSR_Summary.txt";
  //FSRout.open(FSRName);

  for (int i(0); i<Ntries;i++)
  //for (int i(0); i<20;i++)
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
    fChain->GetEntry(i);
    //===========================
    //Initialization of Variables
    //===========================
    InitVar4Evt();

  }//Ntries
  cout<<"Passed W evts: "<<evtCnt_W<<"   Passed Z evts: "<<evtCnt_Z<<endl;
  cout<<"Z (beforeCut): "<<evtCnt_Z_beforeCut<<"   Z (afterCut): "<<evtCnt_Z_afterCut<<endl;
  //Results======================

//  TString resultDir = AnaChannel;
////  TString resultDir = "results";
//  gSystem->mkdir(resultDir);
  TFile *myFile;
  char tempStr[30];
  sprintf(tempStr,"_Eta_%d",123);
  myFile=new TFile(resultDir+"/"+OutFileName+tempStr,"RECREATE");

  ofstream Fout;
  TString FoutName;
  FoutName = resultDir+"/"+OutFileName+tempStr+"_Summary.txt";
  Fout.open(FoutName);
  
  cout<<"selected converted: "<<nSelect<<" +- "<<TMath::Sqrt(nSelect)<<endl;
  Fout<<"selected converted: "<<nSelect<<" +- "<<TMath::Sqrt(nSelect)<<endl;

  Fout.close();


  h1_W_Multi->Write();
  h1_W_Acop->Write();
  h1_vtx_z->Write();
  h1_vtx_Rho->Write();
  h1_PuWeight->Write();
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

  if(Mode == "Unfold")
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
  
// MVAnoPUMETana study
  //if (Mode=="MVAnoPUMEt")
  //{
  //  h1_W_Met->Write();
  //  h1_W_NoPU_Met->Write();
  //  h1_W_MVA_Met->Write();
  //  h1_W_Gen_Met->Write();
  //}

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
  h1_Vtx_PrimPuW->Write();
  h1_Vtx_Good->Write();
  h1_Vtx_GoodPuW->Write();

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
  //  h1_Z_Met->Write();
  //  h1_Z_NoPU_Met->Write();
  //  h1_Z_MVA_Met->Write();
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
  gBenchmark->Show("WLepNeu");
}
int WLepNeu::CheckChannel()
{
  if(AnaChannel == "MuonLowPU" )if(fabs(Channel) != GenType::kMuon) return -1;
  if(AnaChannel == "MuonHighPU")if(fabs(Channel) != GenType::kMuon) return-1;
  if(AnaChannel == "ElectronLowPU")if(fabs(Channel) != GenType::kElectron) return-1;
  if(AnaChannel == "ElectronHighPU")if(fabs(Channel) != GenType::kElectron) return-1;
  if(AnaChannel == "TauHighPU")if(fabs(Channel) != GenType::kTau) return-1;
  return 0;
}
int WLepNeu::TriggerCut()
{
    if(AnaChannel == "MuonLowPU" )if( HLT_Mu15_eta2p1_fired < 1) return -1;
    if(AnaChannel == "ElectronLowPU" )if(HLT_Ele22_CaloIdL_CaloIsoVL_fired<1) return -1;
    if(AnaChannel=="ElectronHighPU")if(HLT_Ele27_WP80_fired<1) return -1;
  return 0;
}
int WLepNeu::DumpWbestCand(int idx)
{
  wCand.charge = (*W_Charge)[iw];
  //Muon Variable Study----------------------
  if(AnaChannel == "MuonLowPU" ){
    glbMuChi2 = (*W_Lept1_globalNormChi2)[iw];
    wCand.muonHit = (*W_Lept1_muonHits)[iw];
    wCand.matchStation = (*W_Lept1_matchStations)[iw];
    wCand.trkLayers = (*W_Lept1_trkLayers)[iw];
    wCand.pixelHits = (*W_Lept1_pixelHits)[iw];
    wCand.dB = fabs((*W_Lept1_dB)[iw]);
    wCand.chIso03 = (*W_Lept1_chIso03)[iw];
    wCand.chIso04 = (*W_Lept1_chIso04)[iw];
    wCand.nhIso03 = (*W_Lept1_nhIso03)[iw];
    wCand.nhIso04 = (*W_Lept1_nhIso04)[iw];
    wCand.phIso03 = (*W_Lept1_phIso03)[iw];
    wCand.phIso04 = (*W_Lept1_phIso04)[iw];
    wCand.pcIso03 = (*W_Lept1_pcIso03)[iw];
    wCand.pcIso04 = (*W_Lept1_pcIso04)[iw];
  }

  if(AnnaChannel == "TauHighPU")
  {
    wCand.dz = 1;// Tau channel has a problem!
  }else{
    wCand.dz = fabs((*W_Lept1_dz)[iw]);
  }

  wCand.Mt = (*W_Mt)[iw];
  wCand.Met = (*W_Neut_pt)[iw];
  return 0;
}
int DumpMETs()
{
// MVAnoPUMETana study
	//if (Mode=="MVAnoPUMEt")
	//{
	//  W_Met = (*W_Neut_pt)[iw];
	//  W_NoPU_Met = (*W_NoPU_Neut_pt)[iw];
	//  W_MVA_Met = (*W_MVA_Neut_pt)[iw];
	//  if (abs((*GenW_BornLept1_id)[0])==16)
	//  W_Gen_Met = (*GenW_BornLept1_pt)[iw];
	//  else if (abs((*GenW_BornLept2_id)[0])==16)
	//  W_Gen_Met = (*GenW_BornLept1_pt)[iw];
//	//  W_Gen_Met = (*W_Neut_pt)[iw];
	//  if (abs((*GenW_BornLept1_id)[0])!=16 && abs((*GenW_BornLept2_id)[0])!=16)
	//    //cout << "There is no genMEt" << endl;
	//  metCnt++;
	//}
  return 0;
}
