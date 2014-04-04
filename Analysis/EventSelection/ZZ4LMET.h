//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed May 16 17:32:24 2012 by ROOT version 5.32/00
// from TChain ZZ4LMET/tree/
//////////////////////////////////////////////////////////
//$Log: ZZ4LMET.h,v $
//Revision 1.9  2013/08/19 15:11:26  jungmin
//*** empty log message ***

#ifndef ZZ4LMET_h
#define ZZ4LMET_h

#include <TSystem.h>
#include "ZZ4LBase.h"
#include "TProfile.h"
//#include "../Utils/const.h"

// Fixed size dimensions of array or collections stored in the TTree if any.
class ZZ4LMET: public ZZ4LBase {
public :
   ZZ4LMET(TTree *tree=0,TTree *WMuonTree=0, double weight=1, TString OutFileName = "output.root",TString Mode="analysis", TString AnaChannel ="Muon",double WCHARGE=0, bool runOnMC=true, int etaRange_=-999);//Electron
   ~ZZ4LMET();
   virtual void     Loop();
protected:
   TH1D* h1_Zmass;
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
  int InitVar(); // Init for Class
   int InitVar4Evt(); // Init for every event
   int VertexCut();
   double CalcEvtWeight();
   int ZbestSelect();
   int InitHistogram();
   // Member variables

};

#endif

#ifdef ZZ4LMET_cxx


ZZ4LMET::ZZ4LMET(TTree *ZZ4LMETTree,TTree *WLepTree, double lumiweight,TString OutNameBase_, TString mode_, TString AnaChannel_,double Wcharge, bool runOnMC,int etaRange_) :
ZZ4LBase::ZZ4LBase(ZZ4LMETTree,WLepTree, lumiweight,OutNameBase_, mode_, AnaChannel_,Wcharge, runOnMC, etaRange_)
{
  // Initialize Variables
  InitVar();
  gSystem->mkdir(mResultDir);
  InitHistogram();
}

ZZ4LMET::~ZZ4LMET()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}
#endif // #ifdef ZZ4LMET_cxx


