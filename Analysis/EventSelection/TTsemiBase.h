//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed May 16 17:32:24 2012 by ROOT version 5.32/00
// from TChain TTsemiBase/tree/
//////////////////////////////////////////////////////////
//$Log: TTsemiBase.h,v $
//Revision 1.13  2013/09/13 00:09:32  salee
//*** empty log message ***
//

#ifndef TTsemiBase_h
#define TTsemiBase_h

#include "WMuons.h"
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1D.h>
#include <TMath.h>
#include <TLorentzVector.h>
#include <TRandom.h>

// Header file for the classes stored in the TTree if any.
#include <vector>

#include <iostream>
#include <fstream>
#include <iomanip>
#include "../Utils/const.h"
#include "../Utils/RecoilCorrector.hh"//class to handle recoil corrections for MET
#include "../Utils/MyTools.hh"
#include "TTsemiNT.h"


#include "Math/PtEtaPhiE4D.h"
#include "Math/PtEtaPhiM4D.h"
#include "Math/LorentzVector.h"

typedef ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiM4D<double> > PtEtaPhiMLorentzVectorD;
typedef PtEtaPhiMLorentzVectorD PtEtaPhiMLorentzVector;


// Fixed size dimensions of array or collections stored in the TTree if any.
class TTsemiBase: public TTsemiNT {
public :
  //WMuons	wMuons;

   double	LumiWeight;

   TTsemiBase(TTree *tree=0,TTree *WMuonTree=0, double weight=1,
       TString OutFileName = "output.root",TString Mode="analysis",
       TString AnaChannel ="Muon",double WCHARGE=0, bool runOnMC=true, int etaRange_=-999);

   virtual ~TTsemiBase();
   virtual Int_t    TauCut(int entry);
   virtual Int_t    MuonCut(int entry);
   virtual Int_t    ElectronCut(int entry);
   virtual Int_t    ElectronCutHighPU(int entry);
  
   
 //  virtual Int_t    FillMisChargeInfo();//MisChargeStudy
   virtual Int_t    InitVar4Evt();
   virtual Int_t    DumpMETs();
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   //   virtual void     Loop_Recoil();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
protected:
  bool Debug;
  int InitVar();
  int CheckChannel();
  int TriggerCut();
  double CalcEvtWeight(){mTTW =1; return mTTW;}
  //------------------
  // Member Variables
  //------------------
  // Miscal
  char histName[30];
  TString mResultDir;
  TLorentzVector pfMEtTL, NoPuMEtTL, MVaMEtTL, genMEtTrueTL, genMEtCaloTL, genMEtCaloAndNonPromptTL;
  int Ntries;
  int evtCnt;
  int mNTTevt;
  double evtSelected;
  bool TruthRecoPost;
  double mEffSf;
  double WCHARGE;
  struct VtxVar{
    int nPrim;
    int nGood;
  }mVtxVar;

  //W boson Variables
  struct TTsemiCand{
    int    trthIdx;
    double pt;
    double Mt;
    double Met;
    double Nu_px;
    double Nu_py;
    double Met_side;
    int size;
    double charge;

    int muonHit;
    int matchStation;
    int trkLayers;
    double dB,dz;
    int pixelHits;
    double chIso03, chIso04;
    double nhIso03, nhIso04;
    double phIso03, phIso04;
    double pcIso03, pcIso04;
    double lep_pt, lep_pt_corr;
    double lep_phi;
    double lep_eta, lep_etaSC;

    int genIdx;
    bool Pass;
    int idxBest;
    TVector2 *PostT2;
    double Post_pt;
    TVector2 *RecoilT2;
  }TTsemi;
  double w_pt_side, w_acop;

  double lep_pt,addLepN,lep_pt_corr;
  double glbMuChi2;
  //Electron Variables
  //Muetrino
  //Miscell.
  TString	OutFileName;
  TString	Mode;
  TString	AnaChannel;
  bool		RunOnMC;
  double	mTTW;
};

#endif

#ifdef TTsemiBase_cxx

void TTsemiBase::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).
   //
   // Initialization for the member
  TTsemiNT::Init(tree);

   mEffSf = 1;


   h1_Vtx_Prim	= new TH1D("h1_Vtx_Prim","N primary vertex",25,0,25);
   h1_Vtx_Good	= new TH1D("h1_Vtx_Good","N primary vertex",25,0,25);
   h1_W_Multi= new TH1D("h1_W_Multi","W Multiplicity",10,-0.5,9.5);

   h1_Vtx_Prim1 = new TH1D("h1_Vtx_Prim1","Vtx_Prim1",60,0,60);
   h1_Vtx_Good1 = new TH1D("h1_Vtx_Good1","Vtx_Good1",60,0,60);
   h1_W_Lept1_pt1 = new TH1D("h1_W_Lept1_pt1","W_Lept_pt1",50,0.,100);
   h1_npileup1 = new TH1D("h1_npileup1","npileup1",60,0.,60);
   h1_W_Neut_pt1 = new TH1D("h1_W_Neut_pt1","W_Neut_pt1",100,0.,100);

// MVAnoPUMETana study
   h1_W_Met = new TH1D("h1_W_Met","W_Neut_pt",20,0.,100);
   h1_W_Born_Met = new TH1D("h1_W_Born_Met","W_Born_Neut_pt",20,0.,100);
   h1_W_genMEtTrue = new TH1D("h1_W_genMEtTrue","W_genMEtTrue",20,0.,100);
   h1_W_MVA_Met = new TH1D("h1_W_MVA_Met","W_MVA_Neut_pt",20,0.,100);
   h1_W_NoPU_Met = new TH1D("h1_W_NoPU_Met","W_NoPU_Neut_pt",20,0.,100);
   h1_Z_Met = new TH1D("h1_Z_Met","Z_Neut_pt",20,0.,100);
   h1_Z_NoPU_Met = new TH1D("h1_Z_NoPU_Met","Z_NoPU_Neut_pt",20,0.,100);
   h1_Z_MVA_Met = new TH1D("h1_Z_MVA_Met","Z_MVA_Neut_pt",20,0.,100);
   h1_Z_genMEtTrue = new TH1D("h1_Z_genMEtTrue","Z_genMEtTrue",20,0.,100);

   if(AnaChannel == "ElectronHighPU" )
  {
   h1_W_Lep1_eta = new TH1D("h1_W_Lep1_eta","W_Lep1_eta",60,-3.,3.);
   h1_W_Neu_All = new TH1D("h1_W_Neu_All","W_Neu_pt_All",50,0.,100);
   for(int i(0);i<EtaBin;i++)
   {
     sprintf(histName,"h1_W_Neu_Eta_I_%d",i);
     h1_W_Neu_Eta_I[i] = new TH1D(histName,"h1_W_Neu_Eta_I",50,0.,100);
     sprintf(histName,"h1_W_Neu_Eta_P_%d",i);
     h1_W_Neu_Eta_P[i] = new TH1D(histName,"h1_W_Neu_Eta_P",50,0.,100);
     sprintf(histName,"h1_W_Neu_Eta_M_%d",i);
     h1_W_Neu_Eta_M[i] = new TH1D(histName,"h1_W_Neu_Eta_M",50,0.,100);
     sprintf(histName,"h1_WSide_Neu_eta_%d",i);
     h1_WSide_Neu_eta[i] = new TH1D(histName,"h1_WSide_Neu_eta",50,0.,100);
     sprintf(histName,"h1_WpSide_Neu_eta_%d",i);
     h1_WpSide_Neu_eta[i] = new TH1D(histName,"h1_WpSide_Neu_eta",50,0.,100);
     sprintf(histName,"h1_WmSide_Neu_eta_%d",i);
     h1_WmSide_Neu_eta[i] = new TH1D(histName,"h1_WmSide_Neu_eta",50,0.,100);
   }
  }
   h1_W_Lept1_pt = new TH1D("h1_W_Lept1_pt","W_Lept_pt",50,0.,100);
   h1_W_pt	= new TH1D("h1_W_pt","Wpt",NWptBinPlus-1,Bins);
   h1_W_pt_EffCorr = new TH1D("h1_W_pt_EffCorr","Wpt_EffCorr",NWptBinPlus-1,Bins);
   h2_WpT_lepPt =new TH2D("h2_WpT_lepPt","WpT_LepPt",600,0,600,600,0,600);
   h2_WpT_lepPt_Plus =new TH2D("h2_WpT_lepPt_Plus","WpT_LepPt-Plus Charge",600,0,600,600,0,600);
   h2_WpT_lepPt_Minus =new TH2D("h2_WpT_lepPt_Minus","WpT_LepPt-Minus Charge",600,0,600,600,0,600);

   h2_ZLep1_ZLep2 =new TH2D("h2_ZLep1_ZLep2","Z_LepPt1-LepPt2",600,0,600,600,0,600);
   h2_Zmass_ZLep1 =new TH2D("h2_Zmass_ZLep1","Zmass-LepPt1",600,0,600,600,0,600);
   h2_Zmass_ZLep2 =new TH2D("h2_Zmass_ZLep2","Zmass-LepPt2",600,0,600,600,0,600);

   h1_Zpt= new TH1D("h1_Zpt","Zpt",120,0,200);
   h2_Zpt_ZLep1 =new TH2D("h2_Zpt_ZLep1","Zpt-LepPt1",400,0,400,400,0,400);
   h2_Zpt_ZLep2 =new TH2D("h2_Zpt_ZLep2","Zpt-LepPt2",400,0,400,400,0,400);


   //Acceptance Histograms
   h1_Born_AP=new TH1D("h1_Born_AP","Born WpT All Phase",NWptBinPlus-1,Bins);
   h1_Born_BornFid=new TH1D("h1_Born_BornFid","Born WpT at BornFid",NWptBinPlus-1,Bins);
   h1_Born_BornFid_Even=new TH1D("h1_Born_BornFid_Even","Born WpT at BornFid",NWptBinPlus-1,Bins);
   h1_Born_BothFid=new TH1D("h1_Born_BothFid","Born WpT at BothFid",NWptBinPlus-1,Bins);
   h1_Born_BothFid_Even=new TH1D("h1_Born_BothFid_Even","Born WpT at BothFid",NWptBinPlus-1,Bins);

   h1_Post_PostFid=new TH1D("h1_Post_PostFid","Post WpT at PostFid",NWptBinPlus-1,Bins);
   h1_Post_PostFid_Even=new TH1D("h1_Post_PostFid_Even","Post WpT at PostFid",NWptBinPlus-1,Bins);
   h1_Post_BothFid=new TH1D("h1_Post_BothFid","Post WpT at BothFid",NWptBinPlus-1,Bins);
   h1_Post_BothFid_weightFSR=new TH1D("h1_Post_BothFid_weightFSR","Post WpT at BothFid weightFSR",NWptBinPlus-1,Bins);
   h1_Post_BothFid_Even=new TH1D("h1_Post_BothFid_Even","Post WpT at BothFid",NWptBinPlus-1,Bins);
   h2_PostBorn_BothFid=new TH2D("h2_PostBorn_BothFid","Post vs Born at BothFid",NWptBinPlus-1,Bins, NWptBinPlus-1,Bins);

   // MisChargeStudy 
/*   if(AnaChannel == "ElectronHighPU" )
     {
      h1_Zmass_QAll = new TH1D("h1_Zmass_QAll","Invariant mass for Z",120,60,120);
      for(int i(0);i<lept1eta;i++)
       {
        for(int j=0;j<lept2eta;j++){
        sprintf(histName,"h1_Zmass_QThree_%d_%d",i,j);
        h1_Zmass_QThree[i][j] = new TH1D(histName,"Three Charge Requirement",120,60,120);
        sprintf(histName,"h1_Zmass_QThreeSame_%d_%d",i,j);
        h1_Zmass_QThreeSame[i][j] = new TH1D(histName,"Three Charge Requirement",120,60,120);
        sprintf(histName,"h1_Zmass_QNo_%d_%d",i,j);
        h1_Zmass_QNo[i][j] = new TH1D(histName,"No Charge Requirement",120,60,120);
        sprintf(histName,"h1_Zmass_QNoSame_%d_%d",i,j);
        h1_Zmass_QNoSame[i][j] = new TH1D(histName,"No Charge Requirement",120,60,120);
        }
       }
     }
*/
   // Unfold
   h1_Truth_Rec		=new TH1D("h1_Truth_Rec","Simul Wpt Truth",NWptBinPlus-1,Bins);
   h1_Truth_Rec_Even	=new TH1D("h1_Truth_Rec_Even","Simul Wpt Truth_Even",NWptBinPlus-1,Bins);
   h1_Truth_Rec_Odd	=new TH1D("h1_Truth_Rec_Odd","Simul Wpt Truth_Odd",NWptBinPlus-1,Bins);
   h1_Truth_Post	=new TH1D("h1_Truth_Post","Post Wpt Truth",NWptBinPlus-1,Bins);
   h1_Truth_Post_Even	=new TH1D("h1_Truth_Post_Even","Post Wpt Truth_Even",NWptBinPlus-1,Bins);
   h1_Truth_Post_Odd	=new TH1D("h1_Truth_Post_Odd" ,"Post Wpt Truth_Odd",NWptBinPlus-1,Bins);
   h1_Truth_Post_EffCorr=new TH1D("h1_Truth_Post_EffCorr","Post Wpt Truth EffCorr",NWptBinPlus-1,Bins);
   h1_Truth_Post_EffCorr_weightFSR=new TH1D("h1_Truth_Post_EffCorr_weightFSR","Post Wpt Truth EffCorr weightFSR",NWptBinPlus-1,Bins);
   h2_Truth_Rec_AP_Post	=new TH2D("h2_Truth_Rec_AP_Post" ,"Truth Rec All Phase Post",NWptBinPlus-1,Bins,NWptBinPlus-1, Bins);

   h1_Wp_pt = new TH1D("h1_Wp_pt","WplusPt",NWptBinPlus-1,Bins);
   h1_Wm_pt = new TH1D("h1_Wm_pt","WminusPt",NWptBinPlus-1,Bins);
   h1_Wp_pt_EffCorr = new TH1D("h1_Wp_pt_EffCorr","WplusPt_EffCorr",NWptBinPlus-1,Bins);
   h1_Wm_pt_EffCorr = new TH1D("h1_Wm_pt_EffCorr","WminusPt_EffCorr",NWptBinPlus-1,Bins);
   h1_Wp_pt_NoLumiWeight = new TH1D("h1_Wp_pt_NoLumiWeight ","WplusPt",NWptBinPlus-1,Bins);
   h1_Wm_pt_NoLumiWeight = new TH1D("h1_Wm_pt_NoLumiWeight ","WminusPt",NWptBinPlus-1,Bins);
   //for( int i(0);i<NWptBinPlus-1;i++)
   //{
   //  sprintf(histName,"h1_pstFsr2ReconW_pt_%d",i);
   //  h1_pstFsr2ReconW_pt[i]=
   //    new TH1D(histName,"pstFsr2ReconW_pt",NWptBinPlus-1,Bins);
   //}
   sprintf(histName,"h2_WpT_ReconPstFsr");
   h2_WpT_ReconPstFsr=
       new TH2D(histName,histName,NWptBinPlus-1,Bins,NWptBinPlus-1,Bins);
   for( int i=0;i<NWptBinPlus;i++){
     if( i==1 || i==2)
     {
       sprintf(histName,"h1_W_pt_RecoPreFsrGenRes_%d",i);
       h1_W_pt_RecoPreFsrGenRes[i] = new TH1D(histName,"Reco Gen Resol",50,-1.1,3.1);
       sprintf(histName,"h1_W_pt_RecoPstFsrGenRes_%d",i);
       h1_W_pt_RecoPstFsrGenRes[i]=new TH1D(histName,"Reco Gen Resol",50,-1.1,3.1);
     }else{
       sprintf(histName,"h1_W_pt_RecoPreFsrGenRes_%d",i);
       h1_W_pt_RecoPreFsrGenRes[i] = new TH1D(histName,"Reco Gen Resol",50,-1.1,1.1);
       sprintf(histName,"h1_W_pt_RecoPstFsrGenRes_%d",i);
       h1_W_pt_RecoPstFsrGenRes[i] = new TH1D(histName,"Reco Gen Resol",50,-1.1,1.1);
     }

     if( i < NBIN_PT_DIVIDER_1and2 ){
       sprintf(histName,"h2_Met_LepPt_%d",i);
       h2_Met_LepPt[i] = new TH2D(histName,"Met_LepPt",200,0,200,200,0,200);
       sprintf(histName,"h2_Met_WpT_%d",i);
       h2_Met_WpT[i] = new TH2D(histName,"Met_WpT",200,0,200,200,0,200);
       sprintf(histName,"h1_W_Neu_pt_%d",i);
       h1_W_Neu_pt[i] = new TH1D(histName,"W_Neut_pt",NBINS_1,0,METMAX_1);
       sprintf(histName,"h1_GenW_Neu_pt_%d",i);
       h1_GenW_Neu_pt[i] = new TH1D(histName,"GenW_Neut_pt",NBINS_1,0,METMAX_1);
       sprintf(histName,"h1_WSide_Neu_pt_%d",i);
       h1_WSide_Neu_pt[i] = new TH1D(histName,"WSide_Neut_pt",NBINS_1,0,METMAX_1);
       sprintf(histName,"h1_Wp_Neu_pt_%d",i);
       h1_Wp_Neu_pt[i] = new TH1D(histName,"Wp_Neut_pt",NBINS_1,0,METMAX_1);
       sprintf(histName,"h1_GenWp_Neu_pt_%d",i);
       h1_GenWp_Neu_pt[i] = new TH1D(histName,"GenWp_Neut_pt",NBINS_1,0,METMAX_1);
       sprintf(histName,"h1_WpSide_Neu_pt_%d",i);
       h1_WpSide_Neu_pt[i] = new TH1D(histName,"WpSide_Neut_pt",NBINS_1,0,METMAX_1);
       sprintf(histName,"h1_Wm_Neu_pt_%d",i);
       h1_Wm_Neu_pt[i] = new TH1D(histName,"Wm_Neut_pt",NBINS_1,0,METMAX_1);
       sprintf(histName,"h1_GenWm_Neu_pt_%d",i);
       h1_GenWm_Neu_pt[i] = new TH1D(histName,"GenWm_Neut_pt",NBINS_1,0,METMAX_1);
       sprintf(histName,"h1_WmSide_Neu_pt_%d",i);
       h1_WmSide_Neu_pt[i] = new TH1D(histName,"WmSide_Neut_pt",NBINS_1,0,METMAX_1);
       
     } else if ( i < NBIN_PT_DIVIDER_2and3 ){
       sprintf(histName,"h2_Met_LepPt_%d",i);
       h2_Met_LepPt[i] = new TH2D(histName,"Met_LepPt",200,0,200,200,0,200);
       sprintf(histName,"h2_Met_WpT_%d",i);
       h2_Met_WpT[i] = new TH2D(histName,"Met_WpT",200,0,200,200,0,200);

       sprintf(histName,"h1_W_Neu_pt_%d",i);
       h1_W_Neu_pt[i] = new TH1D(histName,"W_Neut_pt",NBINS_2,0,METMAX_2);
       sprintf(histName,"h1_GenW_Neu_pt_%d",i);
       h1_GenW_Neu_pt[i] = new TH1D(histName,"GenW_Neut_pt",NBINS_2,0,METMAX_2);
       sprintf(histName,"h1_WSide_Neu_pt_%d",i);
       h1_WSide_Neu_pt[i] = new TH1D(histName,"WSide_Neut_pt",NBINS_2,0,METMAX_2);
       sprintf(histName,"h1_Wp_Neu_pt_%d",i);
       h1_Wp_Neu_pt[i] = new TH1D(histName,"Wp_Neut_pt",NBINS_2,0,METMAX_2);
       sprintf(histName,"h1_GenWp_Neu_pt_%d",i);
       h1_GenWp_Neu_pt[i] = new TH1D(histName,"GenWp_Neut_pt",NBINS_2,0,METMAX_2);
       sprintf(histName,"h1_WpSide_Neu_pt_%d",i);
       h1_WpSide_Neu_pt[i] = new TH1D(histName,"WpSide_Neut_pt",NBINS_2,0,METMAX_2);
       sprintf(histName,"h1_Wm_Neu_pt_%d",i);
       h1_Wm_Neu_pt[i] = new TH1D(histName,"Wm_Neut_pt",NBINS_2,0,METMAX_2);
       sprintf(histName,"h1_GenWm_Neu_pt_%d",i);
       h1_GenWm_Neu_pt[i] = new TH1D(histName,"GenWm_Neut_pt",NBINS_2,0,METMAX_2);
       sprintf(histName,"h1_WmSide_Neu_pt_%d",i);
       h1_WmSide_Neu_pt[i] = new TH1D(histName,"WmSide_Neut_pt",NBINS_2,0,METMAX_2);

     } else {
       sprintf(histName,"h2_Met_LepPt_%d",i);
       h2_Met_LepPt[i] = new TH2D(histName,"Met_LepPt",200,0,200,200,0,200);
       sprintf(histName,"h2_Met_WpT_%d",i);
       h2_Met_WpT[i] = new TH2D(histName,"Met_WpT",200,0,200,200,0,200);

       sprintf(histName,"h1_W_Neu_pt_%d",i);
       h1_W_Neu_pt[i] = new TH1D(histName,"W_Neut_pt",NBINS_3,0,METMAX_3);
       sprintf(histName,"h1_GenW_Neu_pt_%d",i);
       h1_GenW_Neu_pt[i] = new TH1D(histName,"GenW_Neut_pt",NBINS_3,0,METMAX_3);
       sprintf(histName,"h1_WSide_Neu_pt_%d",i);
       h1_WSide_Neu_pt[i] = new TH1D(histName,"WSide_Neut_pt",NBINS_3,0,METMAX_3);
       sprintf(histName,"h1_Wp_Neu_pt_%d",i);
       h1_Wp_Neu_pt[i] = new TH1D(histName,"Wp_Neut_pt",NBINS_3,0,METMAX_3);
       sprintf(histName,"h1_GenWp_Neu_pt_%d",i);
       h1_GenWp_Neu_pt[i] = new TH1D(histName,"GenWp_Neut_pt",NBINS_3,0,METMAX_3);
       sprintf(histName,"h1_WpSide_Neu_pt_%d",i);
       h1_WpSide_Neu_pt[i] = new TH1D(histName,"WpSide_Neut_pt",NBINS_3,0,METMAX_3);
       sprintf(histName,"h1_Wm_Neu_pt_%d",i);
       h1_Wm_Neu_pt[i] = new TH1D(histName,"Wm_Neut_pt",NBINS_3,0,METMAX_3);
       sprintf(histName,"h1_GenWm_Neu_pt_%d",i);
       h1_GenWm_Neu_pt[i] = new TH1D(histName,"GenWm_Neut_pt",NBINS_3,0,METMAX_3);
       sprintf(histName,"h1_WmSide_Neu_pt_%d",i);
       h1_WmSide_Neu_pt[i] = new TH1D(histName,"WmSide_Neut_pt",NBINS_3,0,METMAX_3);
     }
   }


   //---------------
   h1_W_Mt	= new TH1D("h1_W_Mt","W Mt",100,0.,100);
   h1_W_Acop	= new TH1D("h1_W_Acop","Mu vs MET Acop",30,0.,3.14);

   h1_GlbMuChi2	= new TH1D("h1_GlbMuChi2","global Mu chi2/ndof",60,0.,20);
   h1_muonHits	= new TH1D("h1_muonHits","muon chamber hits",11,0.,11);
   h1_muMatchStation= new TH1D("h1_muMatchStation","muon matched stations",5,0.,5);
   h1_trkLayers= new TH1D("h1_trkLayers","no. of trk layers",20,0.,20);
   h1_pixelHits= new TH1D("h1_pixelHits","no. of pixelHits",8,0.,8);
   h1_dB= new TH1D("h1_dB","dB",40,0.,0.14);
   h1_dz= new TH1D("h1_dz","dz",30,0.,0.7);
   h1_IsoCom03= new TH1D("h1_IsoCom03","ch nh ph",30,0.,0.3);
   h1_IsoCom04= new TH1D("h1_IsoCom04","ch nh ph",30,0.,0.3);
   h1_IsoHad03= new TH1D("h1_IsoHad03","ch nh ph",30,0.,0.3);
   h1_IsoHad04= new TH1D("h1_IsoHad04","ch nh ph",30,0.,0.3);
   h1_IsoBeta03= new TH1D("h1_IsoBeta03","ch beta",30,0.,0.3);
   h1_IsoBeta04= new TH1D("h1_IsoBeta04","ch beta",30,0.,0.3);
   //Z=============
   h1_diLeptVtxProb= new TH1D("h1_diLeptVtxProb","di-Lept vtx prob",60,0.,1);
   h1_Zmass= new TH1D("h1_Zmass","Inv Mass for dilepts",120,60,120);
   h1_Zmass_BB= new TH1D("h1_Zmass_BB","Inv Mass for dilepts BB",120,60,120);
   h1_Zmass_BE= new TH1D("h1_Zmass_BE","Inv Mass for dilepts BE",120,60,120);
   h1_Zmass_EE= new TH1D("h1_Zmass_EE","Inv Mass for dilepts EE",120,60,120);
   h1_ZmassCorr= new TH1D("h1_ZmassCorr","Inv Mass for dilepts after Scale&Smear",120,60,120);
   h1_ZmassCorr_BB= new TH1D("h1_ZmassCorr_BB","Inv Mass for dilepts after Scale&Smear BB",120,60,120);
   h1_ZmassCorr_BE= new TH1D("h1_ZmassCorr_BE","Inv Mass for dilepts after Scale&Smear BE",120,60,120);
   h1_ZmassCorr_EE= new TH1D("h1_ZmassCorr_EE","Inv Mass for dilepts after Scale&Smear EE",120,60,120);
   h2_u1Zpt= new TH2D("h2_u1Zpt","u1 vs Zpt",300,0,300,100,-150,50);
   h2_u2Zpt= new TH2D("h2_u2Zpt","u2 vs Zpt",300,0,300,80,-40,40);
   h2_u3Zpt= new TH2D("h2_u3Zpt","u3 vs Zpt",300,0,300,80,-40,40);
   //0,3,6,10,14,18,23,30,40,55,70,100

   if(Mode == "ScaleMakeMC")
   {
     cout<<"Setting Random Seed for ScaleMakeMC"<<endl;
     switch (ETARANGE)
     {
       case 0:
	 gRandom->SetSeed(0x12345);
	 break;
       case 1:
	 gRandom->SetSeed(0x12346);
	 break;
       case 2:
	 gRandom->SetSeed(0x12347);
	 break;
       case 3:
	 gRandom->SetSeed(0x12348);
	 break;
       case 4:
	 gRandom->SetSeed(0x12349);
	 break;
       case 5:
	 gRandom->SetSeed(0x12350);
	 break;
       default:
	 cout<<"ScaleMake MC: What is this Eta range?"<<endl;
	 exit(0);
     }
   }

   if(Mode == "ScaleMakeMC" || Mode == "ScaleMakeRD")
   {

     //h1_ZmassDaughEtaRD = new TH1D("h1_ZmassDaughEtaRD","h1_ZmassDaughEtaRD",60,60,120);
     //for(int i(0);i<=ScaleBins-1;i++)for(int j(0);j<=ScaleBins-1;j++)
     //  sprintf(histName,"h1_ZmassDaughEta_%d_%d",i,j);
     //  h1_ZmassDaughEta[i][j]=
     //	 new TH1D(histName,"ZmassDaughterEta",60,60,120);

     if( AnaChannel=="ElectronLowPU")
     {
       for(int i(0);i<ScElCombiBins;i++)
       {
	 sprintf(histName,"h1_ZmassDaughEta_%d",i);
	 h1_ZmassDaughEta[i]= new TH1D(histName,"ZmassDaughterEta",60,60,120);
       }
     }
     if( AnaChannel=="ElectronHighPU")
     {
       for(int i(0);i<ScElCombiBinsHighPU;i++)
       {
         sprintf(histName,"h1_ZmassDaughEta_%d",i);
         h1_ZmassDaughEta[i]= new TH1D(histName,"ZmassDaughterEta",60,60,120);
       }
     }
     if( AnaChannel=="MuonLowPU" || AnaChannel=="MuonHighPU")
     {
       for(int i(0);i<ScMuCombiBins;i++)
       {
	 sprintf(histName,"h1_ZmassDaughEtaMu_%d",i);
	 h1_ZmassDaughEtaMu[i]= new TH1D(histName,"ZmassDaughterEtaMu",60,60,120);
       }
     }
   }
   Notify();
}
TTsemiBase::TTsemiBase(TTree *TTsemiBaseTree,TTree *WLepTree, double lumiweight,
       TString OutFileName_, TString mode_, TString AnaChannel_,
       double Wcharge, bool runOnMC, int etaRange_)
{
  fChain=0;
    // if parameter tree is not specified (or zero), connect the file
    // // used to generate this class and read the Tree.
   cout<<"TTsemiBase constructor"<<endl;
   cout<<"initialization for bins"<<endl;
   //{0,2.5,5,7.5,10,12.5,15,17.5,20,30,40,50,70,90,150,190,250,600}; //Zpt Bins
   //0,4,8,15,23,30,38,46,55,65,75,85,95,107,120,132,145,160,175,192,210,250,300 Atlas 22 bins
   //{0,8,23,38,55,75,95,120,145,175,210,300};//Atlas Unfolding bin
   //
   //ZpT bins
  //Bins[0]=     0.;
  //Bins[1]=     2.5;
  //Bins[2]=     5;
  //Bins[3]=     7.5;
  //Bins[4]=     10;
  //Bins[5]=     12.5;
  //Bins[6]=     15;
  //Bins[7]=     17.5;
  //Bins[8]=     20.;
  //Bins[9]=     30.;
  //Bins[10]=    40.;
  //Bins[11]=    50.;
  //Bins[12]=    70.;
  //Bins[13]=    90.;
  //Bins[14]=    110.;
  //Bins[15]=    150.;
  //Bins[16]=    190.;
  //Bins[17]=    250.;
  //Bins[18]=    600.;
   // Final Bins
   Bins[0]=     0.;
   Bins[1]=     7.5;
   Bins[2]=     12.5;
   Bins[3]=     17.5;
   Bins[4]=     24.;
   Bins[5]=     30.;
   Bins[6]=    40.;
   Bins[7]=    50.;
   Bins[8]=    70.;
   Bins[9]=    110.;
   Bins[10]=    150.;
   Bins[11]=    190.;
   Bins[12]=    250.;
   Bins[13]=    600.;

   cout<<"initialization for Recoil bins"<<endl;
   RecoilBins[0]	= 0.;
   RecoilBins[1]	= 5.;
   RecoilBins[2]	= 10.;
   RecoilBins[3]	= 15.;
   RecoilBins[4]	= 20.;
   RecoilBins[5]	= 25.;
   RecoilBins[6]	= 30.;
   RecoilBins[7]	= 35.;
   RecoilBins[8]	= 40.;
   RecoilBins[9]	= 50.;
   RecoilBins[10]	= 60.;
   RecoilBins[11]	= 70.;
   RecoilBins[12]	= 80.;
   RecoilBins[13]	= 90.;
   RecoilBins[14]       = 100.;
   RecoilBins[15]       = 120.;
   RecoilBins[16]       = 150.;
/*
   wqaMetMXBins[0] = 0.1; wqaMetMXBins[1] = 0.2; wqaMetMXBins[2] = 0.3; wqaMetMXBins[3] = 0.4; wqaMetMXBins[4] = 0.5;
      wqaMetMXBins[5] = 0.6; wqaMetMXBins[6] = 0.7; wqaMetMXBins[7] = 0.8; wqaMetMXBins[8] = 0.9; wqaMetMXBins[9] = 1.0;
         wqaMetMXBins[10] = 1.1; wqaMetMXBins[11] = 1.2; wqaMetMXBins[12] = 1.3; wqaMetMXBins[13] = 1.4; wqaMetMXBins[14] = 1.5;
	    wqaMetMXBins[15] = 1.6; wqaMetMXBins[16] = 1.7; wqaMetMXBins[17] = 1.8; wqaMetMXBins[18] = 1.9; wqaMetMXBins[19] = 2.0;
	       wqaMetMXBins[20] = 2.1; wqaMetMXBins[21] = 2.2; wqaMetMXBins[22] = 2.3; wqaMetMXBins[23] = 2.4; wqaMetMXBins[24] = 2.5;

	          wqaMetMNBins[0] = 0.0; wqaMetMNBins[1] = 0.1; wqaMetMNBins[2] = 0.2; wqaMetMNBins[3] = 0.3;  wqaMetMNBins[4] = 0.4;
		     wqaMetMNBins[5] = 0.5; wqaMetMNBins[6] = 0.6; wqaMetMNBins[7] = 0.7; wqaMetMNBins[8] = 0.8;  wqaMetMNBins[9] = 0.9;
		        wqaMetMNBins[10] = 1.0; wqaMetMNBins[11] = 1.1; wqaMetMNBins[12] = 1.2; wqaMetMNBins[13] = 1.3;   wqaMetMNBins[14] = 1.4;
			   wqaMetMNBins[15] = 1.5; wqaMetMNBins[16] = 1.6; wqaMetMNBins[17] = 1.7; wqaMetMNBins[18] = 1.8;   wqaMetMNBins[19] = 1.9;
			      wqaMetMNBins[20] = 2.0; wqaMetMNBins[21] = 2.1; wqaMetMNBins[22] = 2.2; wqaMetMNBins[23] = 2.3;   wqaMetMNBins[24] = 2.4;
 */


   wqaMetMXBins[0] = 0.2; wqaMetMXBins[1] = 0.4; wqaMetMXBins[2] = 0.6; wqaMetMXBins[3] = 0.8; wqaMetMXBins[4] = 1.0;
   wqaMetMXBins[5] = 1.2; wqaMetMXBins[6] = 1.4; wqaMetMXBins[7] = 1.6; wqaMetMXBins[8] = 1.8; wqaMetMXBins[9] = 2.0;
   wqaMetMXBins[10] = 2.2; wqaMetMXBins[11] = 2.4; 

   wqaMetMNBins[0] = 0.0; wqaMetMNBins[1] = 0.2; wqaMetMNBins[2] = 0.4; wqaMetMNBins[3] = 0.6;  wqaMetMNBins[4] = 0.8;
   wqaMetMNBins[5] = 1.0; wqaMetMNBins[6] = 1.2; wqaMetMNBins[7] = 1.4; wqaMetMNBins[8] = 1.6;  wqaMetMNBins[9] = 1.8;
   wqaMetMNBins[10] = 2.0; wqaMetMNBins[11] = 2.2;

   if (TTsemiBaseTree == 0 ) {
     /****************
#ifdef SINGLE_TREE
      // The following code should be used if you want this class to access
      // a single tree instead of a chain
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Memory Directory");
      if (!f || !f->IsOpen()) {
         f = new TFile("Memory Directory");
      }
      f->GetObject("TTsemiBase/tree",tree);

#else // SINGLE_TREE

      // The following code should be used if you want this class to access a chain
      // of trees.
      TChain * chain = new TChain("TTsemiBase/tree","");
      chain->Add("/terranova_1/W_Ntuple/SingleMuRun2012APromptRecoV1Aod/wNtuple_01.root");
      tree = chain;
#endif // SINGLE_TREE

**********************/
     cout<<"Usage: TTsemiBase(TTree*... ) "<<endl;
     exit(-1);
   }else{
     cout<<"TTsemiBase.h: initializing the trees"<<endl;
   LumiWeight = lumiweight;
   cout<<"Input Value of Lumiweight = "<<lumiweight<<" Initialized as = "<<LumiWeight<<endl;
   OutFileName = OutFileName_;
   Mode = mode_;
   AnaChannel = AnaChannel_;
   WCHARGE = Wcharge;
   RunOnMC = runOnMC;
   ETARANGE = etaRange_;
   Init(TTsemiBaseTree);
   //wMuons.Init(WLepTree);
   }
   InitVar();
}


   TTsemiBase::~TTsemiBase()
   {
     if (!fChain) return;
     delete fChain->GetCurrentFile();
   }

   Int_t TTsemiBase::GetEntry(Long64_t entry)
   {
     // Read contents of entry.
     if (!fChain) return 0;
     return fChain->GetEntry(entry);
   }

   Long64_t TTsemiBase::LoadTree(Long64_t entry)
   {
     // Set the environment to read one entry
     if (!fChain) return -5;
     Long64_t centry = fChain->LoadTree(entry);
     if (centry < 0) return centry;
     if (fChain->GetTreeNumber() != fCurrent) {
       fCurrent = fChain->GetTreeNumber();
       Notify();
     }
     return centry;
   }
   
   Bool_t TTsemiBase::Notify()
   {
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

     return kTRUE;
   }


   void TTsemiBase::Show(Long64_t entry)
   {
     // Print contents of entry.
     // If entry is not specified, print current entry
     if (!fChain) return;
     fChain->Show(entry);
   }

   /// Scale Smear corrections

Int_t TTsemiBase::TauCut(int i)
{
  //if( (*W_Lept1_MedComIsoDelBetCorr3Hits)[i] < 0.5 )return -1;
  //if( (*W_Lept1_decModFind)[i] < 0.5 )return -1;
  if( fabs((*W_Lept1_eta)[i]) > 2.3 )return -1;
  if( fabs((*W_Lept1_pt)[i]) < 20 )return -1;
  return 1;
}

Int_t TTsemiBase::MuonCut(int i)
{
  if( !(*W_Lept1_isGlobal)[i])return -1;
  if((*W_Lept1_pt)[i] < 20) return -1;
  //if((*W_Lept1_pt)[i] < 25) return -1;

  if(fabs((*W_Lept1_eta)[i])>2.1) return -1;
  if( (*W_Lept1_globalNormChi2)[i]<0 || (*W_Lept1_globalNormChi2)[i] >= 10) return -1;
  if( (*W_Lept1_muonHits)[i] <1) return -1;
  if( (*W_Lept1_matchStations)[i] <2 ) return -1;
  if( (*W_Lept1_trkLayers)[i] <6 )return -1;
  if( (*W_Lept1_pixelHits)[i] <1 )return -1;
  if( fabs( (*W_Lept1_dB)[i]) >0.02 )return -1;
  if( fabs( (*W_Lept1_dz)[i]) >0.5 )return -1;
  //if( ( (*W_Lept1_nhIso04)[i]+(*W_Lept1_chIso04)[i]+(*W_Lept1_phIso04)[i])/(*W_Lept1_pt)[i] > 0.12) return -1;
  double betaCor04= max(0.0,(*W_Lept1_nhIso04)[i]+(*W_Lept1_phIso04)[i]-0.5*(*W_Lept1_pcIso04)[i]);
  if( ((*W_Lept1_chIso04)[i]+betaCor04)/(*W_Lept1_pt)[i] > 0.12) return -1; //Signal Band   // use this line to get n.of.events in AB area in  ABCD method


  // uncomment next line (Sideband)  to get n.of.events in DC area in  ABCD method
  //  if( ((*W_Lept1_chIso04)[i]+betaCor04)/(*W_Lept1_pt)[i] < 0.3 || ((*W_Lept1_chIso04)[i]+betaCor04)/(*W_Lept1_pt)[i] > 0.5) return -1; //Side Band

  
  
  //if( (*W_Neut_pt)[i] < 14 ) return -1;
  //if( (*W_Mt)[i] < 30 ) return -1;
  //if( (*W_Neut_pt)[i] < 25 ) return -1;
  //if( (*W_Mt)[i] < 40 ) return -1;

  return 1;
}


   Int_t TTsemiBase::ElectronCut(int i)
   {
     if((*W_Lept1_pt)[i] < 25) return -1;
     
     if(fabs((*W_Lept1_etaSC)[i])>2.5) return -1;
     //W/Z
     if(fabs((*W_Lept1_etaSC)[i])>1.4442 && fabs((*W_Lept1_etaSC)[i])<1.566)return -1;

     if( fabs( (*W_Lept1_etaSC)[i]) < 1.4442)
     {
	 if( (*W_Lept1_sigmaIEtaIEta)[i] > 0.01 ) return -1; 
     } else{
	 if( (*W_Lept1_sigmaIEtaIEta)[i] > 0.03 ) return -1;   
     }
     if( fabs( (*W_Lept1_etaSC)[i]) < 1.4442)
     {
	 if( fabs((*W_Lept1_dEtaIn)[i]) >  0.004 ) return -1;
     } else{
	 if( fabs((*W_Lept1_dEtaIn)[i])  >   0.007 ) return -1;
     }
     
     if( fabs( (*W_Lept1_etaSC)[i]) < 1.4442)
     {
	 if( fabs((*W_Lept1_dPhiIn)[i])  > 0.06 ) return -1;
     } else{
	 if( fabs((*W_Lept1_dPhiIn)[i])  > 0.03 ) return -1;
     }

     if( fabs( (*W_Lept1_etaSC)[i]) < 1.4442)
     {
	 if( (*W_Lept1_HoverE)[i] > 0.12 ) return -1;
     } else{
	 if( (*W_Lept1_HoverE)[i] > 0.10 ) return -1;
     }

     if( fabs( (*W_Lept1_etaSC)[i]) < 1.4442)
     {
	 if( fabs((*W_Lept1_dxy)[i]) > 0.02 ) return -1;
     } else{
	 if( fabs((*W_Lept1_dxy)[i]) > 0.02 ) return -1;
     }

     if( fabs( (*W_Lept1_etaSC)[i]) < 1.4442)
     {
	 if( fabs((*W_Lept1_dz)[i]) > 0.1 ) return -1;
     } else{
	 if( fabs((*W_Lept1_dz)[i]) > 0.1 ) return -1;
     }
     if( fabs( (*W_Lept1_etaSC)[i]) < 1.4442)
     {
	 if( fabs((*W_Lept1_InvEminusInvP)[i]) > 0.05 ) return -1;
     }else{
	 if( fabs((*W_Lept1_InvEminusInvP)[i]) > 0.05) return -1;
     }

     if( fabs( (*W_Lept1_etaSC)[i]) < 1.4442)
     {
	 if( fabs((*W_Lept1_mHits)[i]) > 1 ) return -1;
     } else{
	 if( fabs((*W_Lept1_mHits)[i]) > 1) return -1;
     }
 
     if( (*W_Lept1_hasConversion)[i] ) return -1;
     if( (*W_Lept1_relIsoRho03)[i] > 0.15 ) return -1;

     return 1;
   }

   Int_t TTsemiBase::ElectronCutHighPU(int i)
   {
     //////////////  Ele   V5 =======================================
     double RelComIsoEB = (*W_Lept1_RelisolPtTrks03)[i]+max(0.,((*W_Lept1_RelisoEm03)[i]*(*W_Lept1_pt)[i])-1.)+(*W_Lept1_RelisoHad03)[i];
     double RelComIsoEE = (*W_Lept1_RelisolPtTrks03)[i]+(*W_Lept1_RelisoEm03)[i]+(*W_Lept1_RelisoHad03)[i];
     if((*W_Lept1_pt)[i] < 30) return -1;
     if(fabs((*W_Lept1_etaSC)[i])>2.5) return -1;
     //W/Z
     if(fabs((*W_Lept1_etaSC)[i])>1.4442 && fabs((*W_Lept1_etaSC)[i])<1.566)return -1;

     if( fabs( (*W_Lept1_etaSC)[i]) < 1.4442)
     {
       if( (*W_Lept1_sigmaIEtaIEta)[i] > 0.01 ) return -1;
       if( fabs((*W_Lept1_dEtaIn)[i]) >  0.004 ) return -1;
       if( fabs((*W_Lept1_dPhiIn)[i])  > 0.06 ) return -1;
       if( (*W_Lept1_HoverE)[i] > 0.12 ) return -1;
       if( fabs((*W_Lept1_dxy)[i]) > 0.02 ) return -1;
       if( fabs((*W_Lept1_dz)[i]) > 0.1 ) return -1;
       if( fabs((*W_Lept1_InvEminusInvP)[i]) > 0.05 ) return -1;
       if( fabs((*W_Lept1_mHits)[i]) > 1) return -1;
     } else{ 
	 if( (*W_Lept1_sigmaIEtaIEta)[i] > 0.03 ) return -1;
	 if( fabs((*W_Lept1_dEtaIn)[i])  >   0.007 ) return -1;
	 if( fabs((*W_Lept1_dPhiIn)[i])  > 0.03 ) return -1;
	 if( (*W_Lept1_HoverE)[i] > 0.1 ) return -1;
	 if( fabs((*W_Lept1_dxy)[i]) > 0.02 ) return -1;
	 if( fabs((*W_Lept1_dz)[i]) > 0.1 ) return -1;
	 if( fabs((*W_Lept1_InvEminusInvP)[i]) > 0.05) return -1;
	 if( fabs((*W_Lept1_mHits)[i]) > 1) return -1;
     }

     if( (*W_Lept1_hasConversion)[i] ) return -1;
     if( (*W_Lept1_relIsoRho03)[i] > 0.15 ) return -1;

     return 1;
   }
//MisChargeStudy
/*Int_t TTsemiBase::FillMisChargeInfo()
{
  h1_Zmass_QAll->Fill(Z.mass,mTTW);
  for(int iz(0); iz<Z_size;iz++){
  ZLep1eta = (*Z_Lept1_eta)[iz];
  ZLep2eta = (*Z_Lept2_eta)[iz];
  ZLep1charge = (*Z_Lept1_charge)[iz];
  ZLep2charge = (*Z_Lept2_charge)[iz];
  ZLep1Requirement = (*Z_Lept1_GsfCtfScPixchargeConsistentcheck)[iz];
  ZLep2Requirement = (*Z_Lept2_GsfCtfScPixchargeConsistentcheck)[iz];
  for(int i=0;i<lept1eta;i++){
  for(int j=0;j<lept2eta;j++){
  if (fabs(ZLep1eta) > wqaMetMNBins[i] && fabs(ZLep1eta) < wqaMetMXBins[i] ) {
  if (fabs(ZLep2eta) > wqaMetMNBins[j] && fabs(ZLep2eta) < wqaMetMXBins[j] ) {
    h1_Zmass_QNo[i][j]->Fill(Z.mass,mTTW);
    if ( ZLep1Requirement == 1 && ZLep2Requirement == 1){
    h1_Zmass_QThree[i][j]->Fill(Z.mass,mTTW);
    }
    if(ZLep1charge*ZLep2charge==1){
    h1_Zmass_QNoSame[i][j]->Fill(Z.mass,mTTW);
    }
    if(ZLep1Requirement == 1 && ZLep2Requirement == 1 && ZLep1charge*ZLep2charge==1){
    h1_Zmass_QThreeSame[i][j]->Fill(Z.mass,mTTW);
    }
   }
   }
  }
  }
  }
  return 0;
}
*/
int TTsemiBase::DumpMETs()
{
  // MET
  pfMEtTL.SetPxPyPzE(pfMEt_x,pfMEt_y,0,toolbox::pT(pfMEt_x,pfMEt_y));
  NoPuMEtTL.SetPxPyPzE(NoPuMEt_x,NoPuMEt_y,0,toolbox::pT(NoPuMEt_x,NoPuMEt_y));
  MVaMEtTL.SetPxPyPzE(MVaMEt_x,MVaMEt_y,0,toolbox::pT(MVaMEt_x,MVaMEt_y));
  genMEtTrueTL.SetPxPyPzE(genMEtTrue_x,genMEtTrue_y,0,toolbox::pT(genMEtTrue_x,genMEtTrue_y));
  genMEtCaloTL.SetPxPyPzE(genMEtCalo_x,genMEtCalo_y,0,toolbox::pT(genMEtCalo_x,genMEtCalo_y));
  genMEtCaloAndNonPromptTL.SetPxPyPzE(genMEtCaloAndNonPrompt_x,genMEtCaloAndNonPrompt_y,0,toolbox::pT(genMEtCaloAndNonPrompt_x,genMEtCaloAndNonPrompt_y));
  return 0;
}
Int_t TTsemiBase::InitVar4Evt()
{
  // Recoil
  W.RecoilT2=0;
  W.PostT2 =0;
  mTTW = 1;
  mVtxVar.nPrim = 0;
  mVtxVar.nGood = 0;
  //cout<<"TTsemiBase::InitVar4Evt ==========================="<<endl;
  TTsemi.size = TT_Lept1_pt->size();
  TTsemi.pt=0;
  TTsemi.Mt=0;
  TTsemi.Met=0;
  TTsemi.Met_side=0;
  TTsemi.genIdx=-999;
  TTsemi.charge=0;
  TTsemi.lep_pt = 0;
  TTsemi.lep_phi = 0;
  TTsemi.lep_eta = 0;
  TTsemi.lep_etaSC = 0;
  TTsemi.Pass=0;
    
  glbMuChi2=0;
  addLepN=0;lep_pt=0;lep_pt_corr=0;corrMet=0;
  scalecorr1=0;
  corr1=0;
  corr2=0;
  scalecorr2=0;
  smearcorr1=0;
  smearcorr2=0;
  newZlep1Pt=0;
  newZlep2Pt=0;
  elemass=0.000511;
  muonmass=0.1056;

  // Z boson
  Z.Pass = false;
  mZ_size = Z_Mass->size();
  return 0;
}

#endif // #ifdef TTsemiBase_cxx


