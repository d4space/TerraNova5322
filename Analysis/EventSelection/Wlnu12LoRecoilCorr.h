//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed May 16 17:32:24 2012 by ROOT version 5.32/00
// from TChain Wlnu12LoRecoilCorr/tree/
//////////////////////////////////////////////////////////
//$Log: Wlnu12LoRecoilCorr.h,v $

#ifndef Wlnu12LoRecoilCorr_h
#define Wlnu12LoRecoilCorr_h

#include "Wlnu12LoBase.h"
#include "TProfile.h"

// Fixed size dimensions of array or collections stored in the TTree if any.
class Wlnu12LoRecoilCorr: public Wlnu12LoBase {
public :
   Wlnu12LoRecoilCorr(TTree *tree=0,double weight=1, TString OutFileName = "output.root",TString Mode="analysis", TString AnaChannel ="Muon",double WCHARGE=0, bool runOnMC=true, int Seed=0);//Electron
   ~Wlnu12LoRecoilCorr();
   virtual void     Loop();
protected:
  void Nselected4Bin();
  int InitVar(); // Init for Class
  int InitVar4Evt(); // Init for every event
  int InitHistogram();
  int Fill_Histo();
  int Write_Histo();
  ofstream Fout;
  TFile *myFile;
  TH1D* h1_u1W[U1Bin];
  TH1D* h1_u2W[U2Bin];
  TH1D* h1_u3W[U1Bin];
  TH1D* h1_u1Z[U1Bin];
  TH1D* h1_u2Z[U2Bin];
  TH1D* h1_u3Z[U1Bin];
  TH2D* h2_u1Zpt;
  TH2D* h2_u2Zpt;
  TH2D* h2_u3Zpt;
  // Member variables
  double mNselect4WptBin[NwPtBin];

};

#endif

#ifdef Wlnu12LoRecoilCorr_cxx


Wlnu12LoRecoilCorr::Wlnu12LoRecoilCorr(
    TTree *Wlnu12LoRecoilCorrTree, double lumiweight,TString OutFileName_,
    TString mode_, TString AnaChannel_,double Wcharge, bool runOnMC,int Seed) :
Wlnu12LoBase::Wlnu12LoBase(
    Wlnu12LoRecoilCorrTree,lumiweight,OutFileName_, mode_, AnaChannel_,Wcharge, runOnMC, Seed)
{
  // Initialize Variables
  InitVar();
  InitHistogram();
}

Wlnu12LoRecoilCorr::~Wlnu12LoRecoilCorr()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}
#endif // #ifdef Wlnu12LoRecoilCorr_cxx


