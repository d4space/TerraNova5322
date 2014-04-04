//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed May 16 17:32:24 2012 by ROOT version 5.32/00
// from TChain WWMET/tree/
//////////////////////////////////////////////////////////
//$Log: WWMET.h,v $
//Revision 1.9  2013/08/19 15:11:26  jungmin
//*** empty log message ***

#ifndef WWMET_h
#define WWMET_h

#include <TSystem.h>
#include "WWBase.h"
#include "TProfile.h"

// Fixed size dimensions of array or collections stored in the TTree if any.
class WWMET: public WWBase {
public :
   WWMET(TTree *tree=0,TTree *WMuonTree=0, double weight=1, TString OutFileName = "output.root",TString Mode="analysis", TString AnaChannel ="Muon",double WCHARGE=0, bool runOnMC=true, int etaRange_=-999);//Electron
   ~WWMET();
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
   int WWbestSelect();
   int ZbestSelect();
   int FillUnfoldInfo();
   int InitHistogram();
   // Member variables
   double mNselected4Bin[NwPtBin];

};

#endif

#ifdef WWMET_cxx


WWMET::WWMET(TTree *WWMETTree,TTree *WLepTree, double lumiweight,TString OutFileName_, TString mode_, TString AnaChannel_,double Wcharge, bool runOnMC,int etaRange_) :
WWBase::WWBase(WWMETTree,WLepTree, lumiweight,OutFileName_, mode_, AnaChannel_,Wcharge, runOnMC, etaRange_)
{
  // Initialize Variables
  InitVar();
  gSystem->mkdir(mResultDir);
  InitHistogram();
}

WWMET::~WWMET()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}
#endif // #ifdef WWMET_cxx


