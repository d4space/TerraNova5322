//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed May 16 17:32:24 2012 by ROOT version 5.32/00
// from TChain ZllMET/tree/
//////////////////////////////////////////////////////////
//$Log: ZllMET.h,v $
//Revision 1.9  2013/08/19 15:11:26  jungmin
//*** empty log message ***

#ifndef ZllMET_h
#define ZllMET_h

#include <TSystem.h>
#include "ZllBase.h"
#include "TProfile.h"

// Fixed size dimensions of array or collections stored in the TTree if any.
class ZllMET: public ZllBase {
public :
   ZllMET(TTree *tree=0,TTree *WMuonTree=0, double weight=1, TString OutFileName = "output.root",TString Mode="analysis", TString AnaChannel ="Muon",double WCHARGE=0, bool runOnMC=true, int etaRange_=-999);//Electron
   ~ZllMET();
   virtual void     Loop();
protected:
   TH1D* h1_Zmass;
   TH1D* h1_PF_Met;
   TH1D* h1_MVA_Met;
   TH1D* h1_NoPU_Met;
   TH1D* h1_genMEtTrue;
   TProfile* hp_pfMet;
   TProfile* hp_MVaMet;
   TProfile* hp_NoPuMet;
  TFile *myFile;
  int Fill_METs();
   int InitVar(); // Init for Class
   int InitVar4Evt(); // Init for every event
   int VertexCut();
   double CalcEvtWeight();
   int ZbestSelect();
   int InitHistogram();
   // Member variables

};

#endif

#ifdef ZllMET_cxx


ZllMET::ZllMET(TTree *ZllMETTree,TTree *WLepTree, double lumiweight,TString OutNameBase_, TString mode_, TString AnaChannel_,double Wcharge, bool runOnMC,int etaRange_) :
ZllBase::ZllBase(ZllMETTree,WLepTree, lumiweight,OutNameBase_, mode_, AnaChannel_,Wcharge, runOnMC, etaRange_)
{
  // Initialize Variables
  InitVar();
  gSystem->mkdir(mResultDir);
  InitHistogram();
}

ZllMET::~ZllMET()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}
#endif // #ifdef ZllMET_cxx


