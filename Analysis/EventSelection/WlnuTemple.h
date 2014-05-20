//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed May 16 17:32:24 2012 by ROOT version 5.32/00
// from TChain WlnuTemple/tree/
//////////////////////////////////////////////////////////
//$Log: WlnuTemple.h,v $

#ifndef WlnuTemple_h
#define WlnuTemple_h

#include "WlnuBase.h"
#include "TProfile.h"

// Fixed size dimensions of array or collections stored in the TTree if any.
class WlnuTemple: public WlnuBase {
public :
   WlnuTemple(TTree *tree=0,double weight=1, TString OutFileName = "output.root",TString Mode="analysis", TString AnaChannel ="Muon",double WCHARGE=0, bool runOnMC=true, int Seed=0);//Electron
   ~WlnuTemple();
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

#ifdef WlnuTemple_cxx


WlnuTemple::WlnuTemple(
    TTree *WlnuTempleTree, double lumiweight,TString OutFileName_,
    TString mode_, TString AnaChannel_,double Wcharge, bool runOnMC,int Seed) :
WlnuBase::WlnuBase(
    WlnuTempleTree,lumiweight,OutFileName_, mode_, AnaChannel_,Wcharge, runOnMC, Seed)
{
  // Initialize Variables
  InitVar();
  InitHistogram();
}

WlnuTemple::~WlnuTemple()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}
#endif // #ifdef WlnuTemple_cxx

