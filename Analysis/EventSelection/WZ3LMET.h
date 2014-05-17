//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed May 16 17:32:24 2012 by ROOT version 5.32/00
// from TChain WZ3LMET/tree/
//////////////////////////////////////////////////////////
//$Log: WZ3LMET.h,v $
//Revision 1.9  2013/08/19 15:11:26  jungmin
//*** empty log message ***

#ifndef WZ3LMET_h
#define WZ3LMET_h

#include <TSystem.h>
#include "WZ3LBase.h"
#include "TProfile.h"

// Fixed size dimensions of array or collections stored in the TTree if any.
class WZ3LMET: public WZ3LBase {
public :
   WZ3LMET(TTree *tree=0,TTree *WMuonTree=0, double weight=1, TString OutFileName = "output.root",TString Mode="analysis", TString AnaChannel ="Muon",double WCHARGE=0, bool runOnMC=true, int etaRange_=-999);//Electron
   ~WZ3LMET();
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
   int ZbestSelect();
   int FillUnfoldInfo();
   int InitHistogram();
   // Member variables
   double mNselected4Bin[NwPtBin];

};

#endif

#ifdef WZ3LMET_cxx


WZ3LMET::WZ3LMET(TTree *WZ3LMETTree,TTree *WLepTree, double lumiweight,TString OutFileName_, TString mode_, TString AnaChannel_,double Wcharge, bool runOnMC,int etaRange_) :
WZ3LBase::WZ3LBase(WZ3LMETTree,WLepTree, lumiweight,OutFileName_, mode_, AnaChannel_,Wcharge, runOnMC, etaRange_)
{
  // Initialize Variables
  InitVar();
  gSystem->mkdir(mResultDir);
  InitHistogram();
}

WZ3LMET::~WZ3LMET()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}
#endif // #ifdef WZ3LMET_cxx


