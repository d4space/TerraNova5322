//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed May 16 17:32:24 2012 by ROOT version 5.32/00
// from TChain Wlnu12LoCtrPlt/tree/
//////////////////////////////////////////////////////////
//$Log: Wlnu12LoCtrPlt.h,v $

#ifndef Wlnu12LoCtrPlt_h
#define Wlnu12LoCtrPlt_h

#include "Wlnu12LoBase.h"
#include "TProfile.h"

// Fixed size dimensions of array or collections stored in the TTree if any.
class Wlnu12LoCtrPlt: public Wlnu12LoBase {
public :
   Wlnu12LoCtrPlt(TTree *tree=0,double weight=1, TString OutFileName = "output.root",TString Mode="analysis", TString AnaChannel ="Muon",double WCHARGE=0, bool runOnMC=true, int Seed=0);//Electron
   ~Wlnu12LoCtrPlt();
   virtual void     Loop();
protected:
  Int_t	    WreconEff();
  Int_t	    ZreconEff();
  void Nselected4Bin();
  int InitVar(); // Init for Class
  int InitVar4Evt(); // Init for every event
  int InitHistogram();
  int Fill_Histo();
  int FillFiducialCutHisto();
  int FillZmu1FiducialCutHist(int entry);
  int FillZmu2FiducialCutHist(int entry);
  int FillZmu1CutHist(int entry);
  int FillZmu2CutHist(int entry);
  int Write_Histo();
  ofstream Fout;
  TFile *myFile;
  //Wboson
  TH1D*	h1_W_pt;
  TH1D*	h1_Wp_pt;
  TH1D*	h1_Wm_pt;
  TH1D*	h1_PlusLepPtAllCutFullRange;
  TH1D*	h1_MinuLepPtAllCutFullRange;
  TH1D*	h1_PlusLepPtFidCutFullRange;
  TH1D*	h1_MinuLepPtFidCutFullRange;
  TH1D*	h1_PlusLepEtaAllCutFullRange;
  TH1D*	h1_MinuLepEtaAllCutFullRange;
  TH1D*	h1_PlusLepEtaFidCutFullRange;
  TH1D*	h1_MinuLepEtaFidCutFullRange;
  TH1D*	h1_PlusLepPtAllCut[3];
  TH1D*	h1_MinuLepPtAllCut[3];
  TH1D*	h1_PlusLepPtFidCut[3];
  TH1D*	h1_MinuLepPtFidCut[3];
  TH1D*	h1_PlusLepEtaAllCut[3];
  TH1D*	h1_MinuLepEtaAllCut[3];
  TH1D*	h1_PlusLepEtaFidCut[3];
  TH1D*	h1_MinuLepEtaFidCut[3];
  TH1D*	h1_PlusLepEtaAllCutTnPbins[3];
  TH1D*	h1_MinuLepEtaAllCutTnPbins[3];
  TH1D*	h1_PlusLepEtaFidCutTnPbins[3];
  TH1D*	h1_MinuLepEtaFidCutTnPbins[3];
  TH2D* h2_PlusLepPtEtaAllCut;
  TH2D* h2_MinuLepPtEtaAllCut;
  TH2D* h2_PlusLepPtEtaFidCut;
  TH2D* h2_MinuLepPtEtaFidCut;
  //Zboson
  //TH1D*	h1_ZPlusLepPtAllCut[3];
  //TH1D*	h1_ZMinuLepPtAllCut[3];
  //TH1D*	h1_ZPlusLepPtFidCut[3];
  //TH1D*	h1_ZMinuLepPtFidCut[3];
  //TH1D*	h1_ZPlusLepEtaAllCut[3];
  //TH1D*	h1_ZMinuLepEtaAllCut[3];
  //TH1D*	h1_ZPlusLepEtaFidCut[3];
  //TH1D*	h1_ZMinuLepEtaFidCut[3];
  //TH1D*	h1_ZPlusLepEtaAllCutTnPbins[3];
  //TH1D*	h1_ZMinuLepEtaAllCutTnPbins[3];
  //TH1D*	h1_ZPlusLepEtaFidCutTnPbins[3];
  //TH1D*	h1_ZMinuLepEtaFidCutTnPbins[3];
  //TH2D* h2_ZPlusLepPtEtaAllCut;
  //TH2D* h2_ZMinuLepPtEtaAllCut;
  //TH2D* h2_ZPlusLepPtEtaFidCut;
  //TH2D* h2_ZMinuLepPtEtaFidCut;
  //TH1D*	h1_ZPlusLepPtAllCutFullRange;
  //TH1D*	h1_ZMinuLepPtAllCutFullRange;
  //TH1D*	h1_ZPlusLepPtFidCutFullRange;
  //TH1D*	h1_ZMinuLepPtFidCutFullRange;
  //TH1D*	h1_ZPlusLepEtaAllCutFullRange;
  //TH1D*	h1_ZMinuLepEtaAllCutFullRange;
  //TH1D*	h1_ZPlusLepEtaFidCutFullRange;
  //TH1D*	h1_ZMinuLepEtaFidCutFullRange;
  // Member variables
  double mNselect4WptBin[NwPtBin];
  char histName[30];
};

#endif

#ifdef Wlnu12LoCtrPlt_cxx


Wlnu12LoCtrPlt::Wlnu12LoCtrPlt(
    TTree *Wlnu12LoCtrPltTree, double lumiweight,TString OutFileName_,
    TString mode_, TString AnaChannel_,double Wcharge, bool runOnMC,int Seed) :
Wlnu12LoBase::Wlnu12LoBase(
    Wlnu12LoCtrPltTree,lumiweight,OutFileName_, mode_, AnaChannel_,Wcharge, runOnMC, Seed)
{
  // Initialize Variables
  InitVar();
  InitHistogram();
}

Wlnu12LoCtrPlt::~Wlnu12LoCtrPlt()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}
#endif // #ifdef Wlnu12LoCtrPlt_cxx


