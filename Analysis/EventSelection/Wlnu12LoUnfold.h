//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed May 16 17:32:24 2012 by ROOT version 5.32/00
// from TChain Wlnu12LoUnfold/tree/
//////////////////////////////////////////////////////////
//$Log: Wlnu12LoUnfold.h,v $

#ifndef Wlnu12LoUnfold_h
#define Wlnu12LoUnfold_h

#include "Wlnu12LoBase.h"
#include "TProfile.h"

// Fixed size dimensions of array or collections stored in the TTree if any.
class Wlnu12LoUnfold: public Wlnu12LoBase {
public :
   Wlnu12LoUnfold(TTree *tree=0,double weight=1, TString OutFileName = "output.root",TString Mode="analysis", TString AnaChannel ="Muon",double WCHARGE=0, bool runOnMC=true, int Seed=0);//Electron
   ~Wlnu12LoUnfold();
   virtual void     Loop();
protected:
  void Nselected4Bin();
  int InitVar(); // Init for Class
  int InitVar4Evt(); // Init for every event
  int InitHistogram();
  int DumpUnfInfo(int entry);
  int FillUnfHisto();
  int Write_Histo();
  ofstream Fout;
  TFile *myFile;
  TH1D* h1_Truth_Rec;
  TH1D* h1_Truth_Rec_Even;
  TH1D* h1_Truth_Rec_Odd;
  TH1D* h1_Truth_Post;
  TH1D* h1_Truth_Post_Even;
  TH1D* h1_Truth_Post_Odd;
  TH1D* h1_Truth_Post_EffCorr;
  TH1D* h1_Truth_Post_EffCorr_weightFSR;
  TH2D* h2_Truth_Rec_AP_Post;
  TH2D* h2_Truth_Rec_AP_PostEffCorr;
  TH1D* h1_W_pt_RecoPreFsrGenRes[NWptBinPlus];
  TH1D* h1_W_pt_RecoPstFsrGenRes[NWptBinPlus];

  // Member variables
  double mNselect4WptBin[NwPtBin];
};

#endif

#ifdef Wlnu12LoUnfold_cxx


Wlnu12LoUnfold::Wlnu12LoUnfold(
    TTree *Wlnu12LoUnfoldTree, double lumiweight,TString OutFileName_,
    TString mode_, TString AnaChannel_,double Wcharge, bool runOnMC,int Seed) :
Wlnu12LoBase::Wlnu12LoBase(
    Wlnu12LoUnfoldTree,lumiweight,OutFileName_, mode_, AnaChannel_,Wcharge, runOnMC, Seed)
{
  // Initialize Variables
  InitVar();
  InitHistogram();
}

Wlnu12LoUnfold::~Wlnu12LoUnfold()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}
#endif // #ifdef Wlnu12LoUnfold_cxx
