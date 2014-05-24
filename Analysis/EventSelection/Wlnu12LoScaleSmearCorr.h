//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed May 16 17:32:24 2012 by ROOT version 5.32/00
// from TChain Wlnu12LoScaleSmearCorr/tree/
//////////////////////////////////////////////////////////
//$Log: Wlnu12LoScaleSmearCorr.h,v $

#ifndef Wlnu12LoScaleSmearCorr_h
#define Wlnu12LoScaleSmearCorr_h

#include "Wlnu12LoBase.h"
#include "TProfile.h"


// Fixed size dimensions of array or collections stored in the TTree if any.
class Wlnu12LoScaleSmearCorr: public Wlnu12LoBase {
public :
   Wlnu12LoScaleSmearCorr(TTree *tree=0,double weight=1, TString OutFileName = "output.root",TString Mode="analysis", TString AnaChannel ="Muon",double WCHARGE=0, bool runOnMC=true, int Seed=0);//Electron
   ~Wlnu12LoScaleSmearCorr();
   virtual void     Loop();
protected:
  void Nselected4Bin();
  int InitVar(); // Init for Class
  int InitVar4Evt(); // Init for every event
  int InitHistogram();
  
  int Fill_Histo();
  int Fill_ZHisto();
  
  int Write_Histo();
  int Write_ZHisto();
  
  ofstream Fout;
  TFile *myFile;
  
  
  TH1D*	h1_W_pt;
  TH1D*	h1_Zmass;

  TH1D* h1_ZmassDaughEtaEle[ScElCombiBins];
  TH1D* h1_ZmassDaughEtaEleDiag[ScElCombiBinsDiag];
  TH1D* h1_ZmassDaughEtaMu[ScMuCombiBins];
  
 int ZbestSelect();
 //int InitHistogram();

 virtual Int_t    EtaRange(double lep1Eta);
 virtual Int_t    Fill_EleZmassDaughEta(int etaRange1, int etaRange2);
 virtual Int_t    Fill_MuZmassDaughEta(int etaRange1, int etaRange2);

  
  // Member variables
  double mNselect4WptBin[NwPtBin];

};

#endif

#ifdef Wlnu12LoScaleSmearCorr_cxx


Wlnu12LoScaleSmearCorr::Wlnu12LoScaleSmearCorr(
    TTree *Wlnu12LoScaleSmearCorrTree, double lumiweight,TString OutFileName_,
    TString mode_, TString AnaChannel_,double Wcharge, bool runOnMC,int Seed) :
Wlnu12LoBase::Wlnu12LoBase(
    Wlnu12LoScaleSmearCorrTree,lumiweight,OutFileName_, mode_, AnaChannel_,Wcharge, runOnMC, Seed)
{
  // Initialize Variables
  InitVar();
  InitHistogram();
}

Wlnu12LoScaleSmearCorr::~Wlnu12LoScaleSmearCorr()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}
#endif // #ifdef Wlnu12LoScaleSmearCorr_cxx


