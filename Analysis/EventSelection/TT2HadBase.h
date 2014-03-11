//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed May 16 17:32:24 2012 by ROOT version 5.32/00
// from TChain TT2HadBase/tree/
//////////////////////////////////////////////////////////
//$Log: TT2HadBase.h,v $
//Revision 1.13  2013/09/13 00:09:32  salee
//*** empty log message ***
//

#ifndef TT2HadBase_h
#define TT2HadBase_h

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
#include "TT2HadNT.h"


#include "Math/PtEtaPhiE4D.h"
#include "Math/PtEtaPhiM4D.h"
#include "Math/LorentzVector.h"

typedef ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiM4D<double> > PtEtaPhiMLorentzVectorD;
typedef PtEtaPhiMLorentzVectorD PtEtaPhiMLorentzVector;

// Fixed size dimensions of array or collections stored in the TTree if any.
class TT2HadBase: public TT2HadNT {
public :
  //WMuons	wMuons;

   double	LumiWeight;

   TT2HadBase(TTree *tree=0,double weight=1,
       TString OutNameBase = "Haha",TString Mode="analysis",
       TString AnaChannel ="Muon",double WCHARGE=0, bool runOnMC=true, int etaRange_=-999);

   virtual ~TT2HadBase();
  
   
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
  struct TT2HadCand{
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
  }TT2Had;

  TString	OutNameBase;
  TString	Mode;
  TString	AnaChannel;
  bool		RunOnMC;
  double	mTTW;
};

#endif

#ifdef TT2HadBase_cxx

void TT2HadBase::Init(TTree *tree)
{
  TT2HadNT::Init(tree);

   Notify();
}
TT2HadBase::TT2HadBase(TTree *TT2HadBaseTree,double lumiweight,
       TString OutNameBase_, TString mode_, TString AnaChannel_,
       double Wcharge, bool runOnMC, int etaRange_)
{
  fChain=0;
    // if parameter tree is not specified (or zero), connect the file
    // // used to generate this class and read the Tree.
   cout<<"TT2HadBase constructor"<<endl;

   if (TT2HadBaseTree == 0 ) {
     cout<<"Usage: TT2HadBase(TTree*... ) "<<endl;
     exit(-1);
   }else{
     cout<<"TT2HadBase.h: initializing the trees"<<endl;

     LumiWeight = lumiweight;
     cout<<"Input Value of Lumiweight = "<<lumiweight<<" Initialized as = "<<LumiWeight<<endl;
     OutNameBase = OutNameBase_;
     Mode = mode_;
     AnaChannel = AnaChannel_;
     RunOnMC = runOnMC;
     Init(TT2HadBaseTree);
     //wMuons.Init(WLepTree);
   }
   InitVar();
}

   TT2HadBase::~TT2HadBase()
   {
     if (!fChain) return;
     delete fChain->GetCurrentFile();
   }

   Int_t TT2HadBase::GetEntry(Long64_t entry)
   {
     // Read contents of entry.
     if (!fChain) return 0;
     return fChain->GetEntry(entry);
   }

   Long64_t TT2HadBase::LoadTree(Long64_t entry)
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
   
   Bool_t TT2HadBase::Notify()
   {
     return kTRUE;
   }

   void TT2HadBase::Show(Long64_t entry)
   {
     // Print contents of entry.
     // If entry is not specified, print current entry
     if (!fChain) return;
     fChain->Show(entry);
   }

   /// Scale Smear corrections

int TT2HadBase::DumpMETs()
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
Int_t TT2HadBase::InitVar4Evt()
{
  // Recoil
  mTTW = 1;
  mVtxVar.nPrim = 0;
  mVtxVar.nGood = 0;
  //cout<<"TT2HadBase::InitVar4Evt ==========================="<<endl;
  TT2Had.pt=0;
  TT2Had.Mt=0;
  TT2Had.Met=0;
  TT2Had.Met_side=0;
  TT2Had.charge=0;
  TT2Had.lep_pt = 0;
  TT2Had.lep_phi = 0;
  TT2Had.lep_eta = 0;
  TT2Had.lep_etaSC = 0;
  TT2Had.Pass=0;

  return 0;
}
#endif // #ifdef TT2HadBase_cxx


