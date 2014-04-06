//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed May 16 17:32:24 2012 by ROOT version 5.32/00
// from TChain Wlnu12LoTemple/tree/
//////////////////////////////////////////////////////////
//$Log: Wlnu12LoTemple.h,v $

#ifndef Wlnu12LoTemple_h
#define Wlnu12LoTemple_h

#include "Wlnu12LoBase.h"
#include "TProfile.h"

// Fixed size dimensions of array or collections stored in the TTree if any.
class Wlnu12LoTemple: public Wlnu12LoBase {
public :
   Wlnu12LoTemple(TTree *tree=0,double weight=1, TString OutFileName = "output.root",TString Mode="analysis", TString AnaChannel ="Muon",double WCHARGE=0, bool runOnMC=true, int Seed=0);//Electron
   ~Wlnu12LoTemple();
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
  TH1D*	h1_W_pt;
  // Member variables
  double mNselect4WptBin[NwPtBin];

};

#endif

#ifdef Wlnu12LoTemple_cxx


Wlnu12LoTemple::Wlnu12LoTemple(
    TTree *Wlnu12LoTempleTree, double lumiweight,TString OutFileName_,
    TString mode_, TString AnaChannel_,double Wcharge, bool runOnMC,int Seed) :
Wlnu12LoBase::Wlnu12LoBase(
    Wlnu12LoTempleTree,lumiweight,OutFileName_, mode_, AnaChannel_,Wcharge, runOnMC, Seed)
{
  // Initialize Variables
  InitVar();
  InitHistogram();
}

Wlnu12LoTemple::~Wlnu12LoTemple()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}
#endif // #ifdef Wlnu12LoTemple_cxx


