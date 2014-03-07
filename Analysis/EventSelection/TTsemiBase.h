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

    bool Pass;
    int idxBest;
  }TTsemi;

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
  TTsemiNT::Init(tree);

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

   if (TTsemiBaseTree == 0 ) {
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
  if( ((*W_Lept1_chIso04)[i]+betaCor04)/(*W_Lept1_pt)[i] > 0.12) return -1;

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

  return 0;
}
#endif // #ifdef TTsemiBase_cxx


