//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed May 16 17:32:24 2012 by ROOT version 5.32/00
// from TChain Wlnu12LoTempl/tree/
//////////////////////////////////////////////////////////
//$Log: Wlnu12LoTempl.h,v $

#ifndef Wlnu12LoAccept_h
#define Wlnu12LoAccept_h

#include "Wlnu12LoBase.h"
#include "TProfile.h"
// Fixed size dimensions of array or collections stored in the TTree if any.
class Wlnu12LoAccept: public Wlnu12LoBase {
public :
   Wlnu12LoAccept(TTree *tree=0,double weight=1, TString OutFileName = "output.root",TString Mode="analysis", TString AnaChannel ="Muon",double WCHARGE=0, bool runOnMC=true, int Seed=0);//Electron
   ~Wlnu12LoAccept();
   virtual void     Loop();
protected:
  void Nselected4Bin();
  int InitVar(); // Init for Class
  int InitVar4Evt(); // Init for every event
  int InitHistogram();
  int FillAcceptInfo();
  int DoPDFsyst();
  int Write_Histo();
  ofstream Fout;
  TFile *myFile;
  
  // Member variables
  double mNselect4WptBin[NwPtBin];

  //PDF systematic uncertainty
  double weightedSelectedEvents[13,53];
  double weighted2SelectedEvents[13,53];
  double events_central[NWptBinPlus-1] = {0.0};
  double events2_central[NWptBinPlus-1] = {0.0};
  double wa[NWptBinPlus-1] = {0.0};
  double wb[NWptBinPlus-1] = {0.0};
  double wplus[NWptBinPlus-1] = {0.0};
  double wminus[NWptBinPlus-1] = {0.0};

  // Acceptance
  TH1D* h1_Born_AP;
  TH1D* h1_Born_BornFid;
  TH1D* h1_Born_BornFid_Even;
  TH1D* h1_Born_BothFid;
  TH1D* h1_Born_BothFid_Even;

  TH1D* h1_Post_PostFid;
  TH1D* h1_Post_PostFid_Even;
  TH1D* h1_Post_BothFid;
  TH1D* h1_Post_BothFid_weightFSR;
  TH1D* h1_Post_BothFid_Even;

  TH2D* h2_PostBorn_BothFid;
};

#endif

#ifdef Wlnu12LoAccept_cxx

Wlnu12LoAccept::Wlnu12LoAccept(
    TTree *Wlnu12LoAcceptTree, double lumiweight,TString OutFileName_,
    TString mode_, TString AnaChannel_,double Wcharge, bool runOnMC,int Seed) :
Wlnu12LoBase::Wlnu12LoBase(
    Wlnu12LoAcceptTree,lumiweight,OutFileName_, mode_, AnaChannel_,Wcharge, runOnMC, Seed)
{
  // Initialize Variables
  InitVar();
  InitHistogram();
}

Wlnu12LoAccept::~Wlnu12LoAccept()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}
#endif // #ifdef Wlnu12LoAccept_cxx


