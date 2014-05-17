//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed May 16 17:32:24 2012 by ROOT version 5.32/00
// from TChain WlnuMET/tree/
//////////////////////////////////////////////////////////
//$Log: WlnuMET.h,v $
//Revision 1.9  2013/08/19 15:11:26  jungmin
//*** empty log message ***

#ifndef WlnuMET_h
#define WlnuMET_h

#include <TSystem.h>
#include "WlnuBase.h"
#include "TProfile.h"

// Fixed size dimensions of array or collections stored in the TTree if any.
class WlnuMET: public WlnuBase {
public :
   WlnuMET(TTree *tree=0, double weight=1, TString OutNameBase = "Out",TString Mode="analysis", TString AnaChannel ="Muon",double WCHARGE=0, bool runOnMC=true, int Seed=0);//Electron
   ~WlnuMET();
   virtual void     Loop();
protected:
   TH1D* h1_PF_Met[PUrangeBin];
   TH1D* h1_MVA_Met[PUrangeBin];
   TH1D* h1_NoPU_Met[PUrangeBin];
   TH1D* h1_genMEtTrue[PUrangeBin];
   TH2D* h2_pfMET[PUrangeBin];
   TH2D* h2_MVaMET[PUrangeBin];
   TH2D* h2_NoPuMET[PUrangeBin];
   TH2D* h2_pfMET_pxpy;
   TH2D* h2_MVaMET_pxpy;
   TH2D* h2_NoPuMET_pxpy;

  TFile *myFile;
  int Fill_METs();
  int Fill_METprofiles();
  void Nselected4Bin();
   int InitVar(); // Init for Class
   int InitVar4Evt(); // Init for every event
   int VertexCut();
   double CalcEvtWeight();
   int WbestSelect();
   int FillUnfoldInfo();
   int InitHistogram();
   // Member variables
   double mNselected4Bin[NwPtBin];

};

#endif

#ifdef WlnuMET_cxx


WlnuMET::WlnuMET(TTree *WlnuMETTree, double lumiweight,TString OutNameBase, TString mode_, TString AnaChannel_,double Wcharge, bool runOnMC,int Seed) :
WlnuBase::WlnuBase(WlnuMETTree,lumiweight,OutNameBase, mode_, AnaChannel_,Wcharge, runOnMC, Seed)
{
  // Initialize Variables
  InitVar();
  //gSystem->mkdir(mResultDir);
  InitHistogram();
}

WlnuMET::~WlnuMET()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}
#endif // #ifdef WlnuMET_cxx


