//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed May 16 17:32:24 2012 by ROOT version 5.32/00
// from TChain MonoPhotonBase/tree/
//////////////////////////////////////////////////////////
//$Log: MonoPhotonBase.h,v $
//Revision 1.13  2013/09/13 00:09:32  salee
//*** empty log message ***
//

#ifndef MonoPhotonBase_h
#define MonoPhotonBase_h

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
#include "MonoPhotonNT.h"


#include "Math/PtEtaPhiE4D.h"
#include "Math/PtEtaPhiM4D.h"
#include "Math/LorentzVector.h"

typedef ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiM4D<double> > PtEtaPhiMLorentzVectorD;
typedef PtEtaPhiMLorentzVectorD PtEtaPhiMLorentzVector;

// Fixed size dimensions of array or collections stored in the TTree if any.
class MonoPhotonBase: public MonoPhotonNT {
public :
  //WMuons	wMuons;

   double	LumiWeight;

   MonoPhotonBase(TTree *tree=0,double weight=1,
       TString OutNameBase = "Haha",TString Mode="analysis",
       TString AnaChannel ="Muon",double WCHARGE=0, bool runOnMC=true, int etaRange_=-999);

   virtual ~MonoPhotonBase();
  
   
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
   struct MPhotonCand{
     double pt;
   }MPhoton;
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
  struct MonoPhotonCand{
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
    double PhotonpT;
  }MonoPhoton;

  TString	OutNameBase;
  TString	Mode;
  TString	AnaChannel;
  bool		RunOnMC;
  double	mTTW;
};

#endif

#ifdef MonoPhotonBase_cxx

void MonoPhotonBase::Init(TTree *tree)
{
  MonoPhotonNT::Init(tree);

   Notify();
}
MonoPhotonBase::MonoPhotonBase(TTree *MonoPhotonBaseTree,double lumiweight,
       TString OutNameBase_, TString mode_, TString AnaChannel_,
       double Wcharge, bool runOnMC, int etaRange_)
{
  fChain=0;
    // if parameter tree is not specified (or zero), connect the file
    // // used to generate this class and read the Tree.
   cout<<"MonoPhotonBase constructor"<<endl;

   if (MonoPhotonBaseTree == 0 ) {
     cout<<"Usage: MonoPhotonBase(TTree*... ) "<<endl;
     exit(-1);
   }else{
     cout<<"MonoPhotonBase.h: initializing the trees"<<endl;

     LumiWeight = lumiweight;
     cout<<"Input Value of Lumiweight = "<<lumiweight<<" Initialized as = "<<LumiWeight<<endl;
     OutNameBase = OutNameBase_;
     Mode = mode_;
     AnaChannel = AnaChannel_;
     RunOnMC = runOnMC;
     Init(MonoPhotonBaseTree);
     //wMuons.Init(WLepTree);
   }
   InitVar();
}

   MonoPhotonBase::~MonoPhotonBase()
   {
     if (!fChain) return;
     delete fChain->GetCurrentFile();
   }

   Int_t MonoPhotonBase::GetEntry(Long64_t entry)
   {
     // Read contents of entry.
     if (!fChain) return 0;
     return fChain->GetEntry(entry);
   }

   Long64_t MonoPhotonBase::LoadTree(Long64_t entry)
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
   
   Bool_t MonoPhotonBase::Notify()
   {
     return kTRUE;
   }

   void MonoPhotonBase::Show(Long64_t entry)
   {
     // Print contents of entry.
     // If entry is not specified, print current entry
     if (!fChain) return;
     fChain->Show(entry);
   }

   /// Scale Smear corrections

int MonoPhotonBase::DumpMETs()
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
Int_t MonoPhotonBase::InitVar4Evt()
{
  // Recoil
  mTTW = 1;
  mVtxVar.nPrim = 0;
  mVtxVar.nGood = 0;
  //cout<<"MonoPhotonBase::InitVar4Evt ==========================="<<endl;
  MonoPhoton.pt=0;
  MonoPhoton.Mt=0;
  MonoPhoton.Met=0;
  MonoPhoton.Met_side=0;
  MonoPhoton.charge=0;
  MonoPhoton.lep_pt = 0;
  MonoPhoton.lep_phi = 0;
  MonoPhoton.lep_eta = 0;
  MonoPhoton.lep_etaSC = 0;
  MonoPhoton.Pass=0;
  MonoPhoton.PhotonpT=0;

  return 0;
}
#endif // #ifdef MonoPhotonBase_cxx


