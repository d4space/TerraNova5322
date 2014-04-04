//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed May 16 17:32:24 2012 by ROOT version 5.32/00
// from TChain WlnuTemple/tree/
//////////////////////////////////////////////////////////
//$Log: WlnuTemple.h,v $

#ifndef WlnuTemple_h
#define WlnuTemple_h

#include <TSystem.h>
#include "WlnuBase.h"
#include "TProfile.h"

// Fixed size dimensions of array or collections stored in the TTree if any.
class WlnuTemple: public WlnuBase {
public :
   WlnuTemple(TTree *tree=0,TTree *WMuonTree=0, double weight=1, TString OutFileName = "output.root",TString Mode="analysis", TString AnaChannel ="Muon",double WCHARGE=0, bool runOnMC=true, int etaRange_=-999);//Electron
   ~WlnuTemple();
   virtual void     Loop();
protected:
   TH1D* h1_PF_Met;
   TH1D* h1_MVA_Met;
   TH1D* h1_NoPU_Met;
   TH1D* h1_genMEtTrue;
   TH2D* h2_pfMET;
   TH2D* h2_MVaMET;
   TH2D* h2_NoPuMET;
//   TProfile* hp_pfMet;
//   TProfile* hp_MVaMet;
//   TProfile* hp_NoPuMet;
  TFile *myFile;
  int Fill_METs();
  int Fill_METprofiles();
  void Nselected4Bin();
   int InitVar(); // Init for Class
   int InitVar4Evt(); // Init for every event
   int VertexCut();
   double CalcEvtWeight();
   int WbestSelect();
   int ZbestSelect();
   int InitHistogram();
   // Member variables
   double mNselected4Bin[NwPtBin];

};

#endif

#ifdef WlnuTemple_cxx


WlnuTemple::WlnuTemple(TTree *WlnuTempleTree,TTree *WLepTree, double lumiweight,TString OutFileName_, TString mode_, TString AnaChannel_,double Wcharge, bool runOnMC,int etaRange_) :
WlnuBase::WlnuBase(WlnuTempleTree,WLepTree, lumiweight,OutFileName_, mode_, AnaChannel_,Wcharge, runOnMC, etaRange_)
{
  // Initialize Variables
  InitVar();
  gSystem->mkdir(mResultDir);
  InitHistogram();
}

WlnuTemple::~WlnuTemple()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}
#endif // #ifdef WlnuTemple_cxx


