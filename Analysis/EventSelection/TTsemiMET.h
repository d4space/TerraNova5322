//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed May 16 17:32:24 2012 by ROOT version 5.32/00
// from TChain TTsemiMET/tree/
//////////////////////////////////////////////////////////
//$Log: TTsemiMET.h,v $
//Revision 1.9  2013/08/19 15:11:26  jungmin
//*** empty log message ***

#ifndef TTsemiMET_h
#define TTsemiMET_h

#include <TSystem.h>
#include "TTsemiBase.h"
#include "TProfile.h"

// Fixed size dimensions of array or collections stored in the TTree if any.
class TTsemiMET: public TTsemiBase {
public :
   TTsemiMET(TTree *tree=0,TTree *WMuonTree=0, double weight=1, TString OutNameBase = "output.root",TString Mode="analysis", TString AnaChannel ="Muon",double WCHARGE=0, bool runOnMC=true, int etaRange_=-999);//Electron
   ~TTsemiMET();
   virtual void     Loop();
   TH1D* h1_nIdJets;
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
protected:
  TFile *myFile;
  int Fill_METs();
  int Fill_METprofiles();
  int InitVar(); // Init for Class
   int InitVar4Evt(); // Init for every event
   int VertexCut();
   double CalcEvtWeight();
   int TTbestSelect();
   int InitHistogram();
   // Member variables
};

#endif

#ifdef TTsemiMET_cxx


TTsemiMET::TTsemiMET(TTree *TTsemiMETTree,TTree *WLepTree, double lumiweight,TString OutNameBase_, TString mode_, TString AnaChannel_,double Wcharge, bool runOnMC,int etaRange_) :
TTsemiBase::TTsemiBase(TTsemiMETTree,WLepTree, lumiweight,OutNameBase_, mode_, AnaChannel_,Wcharge, runOnMC, etaRange_)
{
  cout<<"Initializing TTsemiMET variables ========="<<endl;
  // Initialize Variables
  InitVar();
  gSystem->mkdir(mResultDir);
  InitHistogram();
}

TTsemiMET::~TTsemiMET()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}
#endif // #ifdef TTsemiMET_cxx
