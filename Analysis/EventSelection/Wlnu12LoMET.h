//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed May 16 17:32:24 2012 by ROOT version 5.32/00
// from TChain Wlnu12LoMET/tree/
//////////////////////////////////////////////////////////
//$Log: Wlnu12LoMET.h,v $

#ifndef Wlnu12LoMET_h
#define Wlnu12LoMET_h

#include "Wlnu12LoBase.h"
#include "TProfile.h"

// Fixed size dimensions of array or collections stored in the TTree if any.
class Wlnu12LoMET: public Wlnu12LoBase {
public :
   Wlnu12LoMET(TTree *tree=0,double weight=1, TString OutFileName = "output.root",TString Mode="analysis", TString AnaChannel ="Muon",double WCHARGE=0, bool runOnMC=true, int Seed=0);//Electron
   ~Wlnu12LoMET();
   virtual void     Loop();
protected:
  void Nselected4Bin();
  int InitVar(); // Init for Class
  int InitVar4Evt(); // Init for every event
  int InitHistogram();
  int Fill_Histo();
  int Fill_SideHisto(); //Side Band histograms
  int DefineAcceptHist(); 
  int FillAcceptInfo(); 
  int Write_Histo();
  ofstream Fout;
  TFile *myFile;
  TH1D*	h1_W_pt;
  TH1D*	h1_Wp_pt;
  TH1D*	h1_Wm_pt;

   // Acceptance
   TH1D*	h1_Born_AP;
   TH1D*	h1_Born_BornFid;
   TH1D*	h1_Born_BornFid_Even;
   TH1D*	h1_Born_BothFid;
   TH1D*	h1_Born_BothFid_Even;

   TH1D*	h1_Post_PostFid;
   TH1D*	h1_Post_PostFid_Even;
   TH1D*	h1_Post_BothFid;
   TH1D*	h1_Post_BothFid_weightFSR;
   TH1D*	h1_Post_BothFid_Even;

   TH2D*	h2_PostBorn_BothFid;


   // Unfolding
   TH1D*	h1_Truth_Rec;
   TH1D*	h1_Truth_Rec_Even;
   TH1D*	h1_Truth_Rec_Odd;
   TH1D*	h1_Truth_Post;
   TH1D*	h1_Truth_Post_Even;
   TH1D*	h1_Truth_Post_Odd;
   TH1D*	h1_Truth_Post_EffCorr;
   TH1D*	h1_Truth_Post_EffCorr_weightFSR;
   TH2D*	h2_Truth_Rec_AP_Post;
   TH2D*	h2_Truth_Rec_AP_PostEffCorr;
   TH1D*	h1_Truth_Post_Fit;

   TH1D*	h1_W_pt_RecoPreFsrGenRes[NWptBinPlus];
   TH1D*	h1_W_pt_RecoPstFsrGenRes[NWptBinPlus];

   TH1D*        h1_W_Lep1_eta;
   TH1D*        h1_W_Neu_All;
   TH1D*        h1_W_Neu_Eta_I[EtaBin];
   TH1D*        h1_W_Neu_Eta_P[EtaBin];
   TH1D*        h1_W_Neu_Eta_M[EtaBin];
   TH1D*	h1_W_Neu_pt[NWptBinPlus];
   TH1D*	h1_GenW_Neu_pt[NWptBinPlus];
   TH1D*	h1_WSide_Neu_pt[NWptBinPlus];
   TH1D*	h1_WSide_Neu_eta[EtaBin];

   TH2D*	h2_Met_LepPt[NWptBinPlus];
   TH2D*	h2_Met_WpT[NWptBinPlus];

   TH1D*	h1_Wp_Neu_pt[NWptBinPlus];
   TH1D*	h1_GenWp_Neu_pt[NWptBinPlus];
   TH1D*	h1_WpSide_Neu_pt[NWptBinPlus];
   TH1D*	h1_WpSide_Neu_eta[EtaBin];

   TH1D*	h1_Wm_Neu_pt[NWptBinPlus];
   TH1D*	h1_GenWm_Neu_pt[NWptBinPlus];
   TH1D*	h1_WmSide_Neu_pt[NWptBinPlus];
   TH1D*	h1_WmSide_Neu_eta[EtaBin];
   
   TH1D*	h1_Wp_Lept_pt[NWptBinPlus];
   TH1D*	h1_Wm_Lept_pt[NWptBinPlus];

  // Member variables
  double mNselect4WptBin[NwPtBin];
  double Bins[NWptBinPlus];
  double TTW ; 
  double effiSF;

  struct GenInfo{
    //bool W_MCtruth;
    double BornW_pt;
    double PostW_pt;
    double PostW_phi;
    double BornW_phi;
    double charge;
    double genWmet;
  }genInfo;

};

#endif

#ifdef Wlnu12LoMET_cxx


Wlnu12LoMET::Wlnu12LoMET(
    TTree *Wlnu12LoMETTree, double lumiweight,TString OutFileName_,
    TString mode_, TString AnaChannel_,double Wcharge, bool runOnMC,int Seed) :
Wlnu12LoBase::Wlnu12LoBase(
    Wlnu12LoMETTree,lumiweight,OutFileName_, mode_, AnaChannel_,Wcharge, runOnMC, Seed)
{
  // Initialize Variables
  InitVar();
  InitHistogram();
}

Wlnu12LoMET::~Wlnu12LoMET()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}
#endif // #ifdef Wlnu12LoMET_cxx
