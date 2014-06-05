//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed May 16 17:32:24 2012 by ROOT version 5.32/00
// from TChain Wlnu12LoBase/tree/
//////////////////////////////////////////////////////////
//$Log: Wlnu12LoBase.h,v $
//Revision 1.13  2013/09/13 00:09:32  salee
//*** empty log message ***
//

#ifndef Wlnu12LoBase_h
#define Wlnu12LoBase_h

#include <TSystem.h>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TMath.h>
#include <TLorentzVector.h>
#include <TRandom3.h>

// Header file for the classes stored in the TTree if any.
#include <vector>

#include <iostream>
#include <fstream>
#include <iomanip>
#include "../Utils/const.h"
#include "../Utils/RecoilCorrector.hh"//class to handle recoil corrections for MET
#include "../Utils/MyTools.hh"
#include "Wlnu12LoNT.h"


#include "Math/PtEtaPhiE4D.h"
#include "Math/PtEtaPhiM4D.h"
#include "Math/LorentzVector.h"

typedef ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiM4D<double> > PtEtaPhiMLorentzVectorD;
typedef PtEtaPhiMLorentzVectorD PtEtaPhiMLorentzVector;


// Fixed size dimensions of array or collections stored in the TTree if any.
class Wlnu12LoBase: public Wlnu12LoNT {
public :
  //WMuons	wMuons;

   double	LumiWeight;
   double 	RecoilBins[U1Bin+1]; //Recoil Study Wpt bins
   double 	WptBins[NWptBinPlus]; //Wpt bins
     
   Wlnu12LoBase(TTree *tree=0,double weight=1,
       TString OutNameBase_ = "Output",TString Mode="analysis",
       TString AnaChannel ="Muon",double WCHARGE=0, bool runOnMC=true, int RndSeed=0);

   virtual ~Wlnu12LoBase();
   
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   //   virtual void     Loop_Recoil();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
protected:
  // Initialize
  int		    InitVar();
  virtual Int_t	    InitVar4Evt();

  // Selections
  double	    CalcEvtWeight();
  virtual Int_t	    WbestSelect();
  virtual Int_t	    ZbestSelect();
  virtual Int_t	    FillWSide(int entry);
  int		    DumpWbestCand(int entry);
  virtual Int_t	    DumpMETs();
  //Cuts
  int		    TriggerCut();
  int		    CheckChannel();
  int		    VertexCut();
  virtual Int_t     TauCut(int entry);
  virtual Int_t     MuonCut(int entry);
  virtual Int_t     MuonCutSide(int entry);
  virtual Int_t     AddMuonCut(int entry);
  virtual Int_t     ElectronCut(int entry);
  virtual Int_t     ElectronCutHighPU(int entry);
  virtual Int_t     ElectronCutSide(int entry);
  virtual Int_t     ElectronCutSideHighPU(int entry);
  virtual Int_t     AddElectronCut(int entry);
  virtual Int_t     AddElectronCutHighPU(int entry);
  virtual Int_t     MuonCutZ(int entry);
  virtual Int_t     ElectronCutZ(int entry);
  virtual Int_t     TauCutZ(int entry);
  virtual Int_t     DoScaleCorr(int entry);
  virtual Int_t     DoSmearCorr(int entry);
  virtual Int_t     DoRecoilCorr();
  virtual Double_t  CalcMt(double lep_pt, double lep_phi, double Met,double  Met_phi);
  virtual Double_t  DoEffiCorr();

  //------------------
  // Member Variables
  //------------------
  TRandom3 *smearRandom;
  int RandomSeed;
  bool Debug;
  // Miscal
  char histName[30];
  TString mResultDir;
  TLorentzVector pfMEtTL, NoPuMEtTL, MVaMEtTL,
		 genMEtTrueTL, genMEtCaloTL, genMEtCaloAndNonPromptTL;

  int Ntries;
  int evtCnt;
  int mNWevt;
  double evtSelected;
  bool TruthRecoPost;
  double mEffSf;
  double WCHARGE;

  struct VtxVar{
    int nPrim;
    int nGood;
  }mVtxVar;
  //Recoil Variables
  RecoilCorrector *RecoilCorr;
  struct RecoilVar{
    TString ZRDfilename;
    TString ZMCfilename;
    TString Wpfilename;
    TString Wmfilename;
    double ux, uy, u1Z, u2Z, u3Z, u1W, u2W, u3W;
  }Rcl;
  // Corrected lepton pt
  vector<double> W_Lept1_pt_Corr;

  //Gen Variables
  struct GenInfo{
    //bool W_MCtruth;
    double PostW_pt;
    double BornW_pt;
    double PostW_phi;
    double BornW_phi;
    double charge;
    double BornW_Nu_Pt;
    int    BornW_Nu_Cnt;
  }genInfo;
  //W boson Variables
  struct WCand{
    int    trthIdx;
    double pt;
    double Mt;
    double Met;
    double Met_phi;
    double Nu_px;
    double Nu_py;
    double acop;
    double pt_side;
    double Met_side;
    double Mt_side;
    int size;
    double charge;

    //int muonHit;
    double muonHit;
    int matchStation;
    int trkLayers;
    double dB,dz;
    int pixelHits;
    double chIso03, chIso04;
    double nhIso03, nhIso04;
    double phIso03, phIso04;
    double pcIso03, pcIso04;
    double lep_pt, lep_pt_corr;
    double lep_phi;
    double lep_eta, lep_etaSC;

    int genIdx;
    bool Pass;
    bool PassSide;
    int idxBest;
    TVector2 *PostT2;
    double Post_pt;
    TVector2 *RecoilT2;
  }W;
  
  //Z boson Variables
  struct Zboson{
    bool Pass;
    double pt;
    double ptRecoil;
    double mass;
    double Lep1Pt, Lep1Pz, Lep1Phi, Lep1En, Lep1etaSC;
    double Lep2Pt, Lep2Pz, Lep2Phi, Lep2En, Lep2etaSC;
    TVector2 *ZDiLep2D;
    TVector2 *DiLep2D;
    double DiLep_pt;
    TVector2 *RecoilT2;
    }Z;
  
  double diLeptVtxProb;
  //Lepton Variables
  double addLepN;
  double scalecorr,smearcorr;
  double smearSF;
  //Muon Variables
  double glbMuChi2;
  //Electron Variables
  //Muetrino
  double corrMet,corrMetPhi;
  //Miscell.
  TString	OutNameBase;
  TString	Mode;
  TString	AnaChannel;
  bool		RunOnMC;
  double	mTTW;

  struct UnfoldInfo{
    double recoPreFsrGenWptRes;
    double recoPstFsrGenWptRes;
  }unfoldInfo;
  bool isPostPassAcc;
  bool isBornPassAcc;
};

#endif

#ifdef Wlnu12LoBase_cxx

void Wlnu12LoBase::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).
   //
   // Initialization for the member
  Wlnu12LoNT::Init(tree);
  cout<<"Initialize variables at Wlnu12LoBase Class ==================="<<endl;
  //mResultDir = OutNameBase+"_"+Mode;
  mResultDir = AnaChannel;
  gSystem->mkdir(mResultDir);

  smearRandom = new TRandom3();
  smearRandom->SetSeed(RandomSeed);
  mEffSf = 1;

   Notify();
}
Wlnu12LoBase::Wlnu12LoBase(TTree *Wlnu12LoBaseTree, double lumiweight,
       TString OutNameBase_, TString mode_, TString AnaChannel_,
       double Wcharge, bool runOnMC, int Seed)
{
  fChain=0;
   cout<<"Wlnu12LoBase constructor"<<endl;
   cout<<"initialization for bins"<<endl;
   // Final Bins
   WptBins[0]  = 0.;
   WptBins[1]  = 7.5;
   WptBins[2]  = 12.5;
   WptBins[3]  = 17.5;
   WptBins[4]  = 24.;
   WptBins[5]  = 30.;
   WptBins[6]  = 40.;
   WptBins[7]  = 50.;
   WptBins[8]  = 70.;
   WptBins[9]  = 110.;
   WptBins[10] = 150.;
   WptBins[11] = 190.;
   WptBins[12] = 250.;
   WptBins[13] = 600.;

   cout<<"initialization for Recoil bins"<<endl;
   RecoilBins[0]  = 0.;
   RecoilBins[1]  = 5.;
   RecoilBins[2]  = 10.;
   RecoilBins[3]  = 15.;
   RecoilBins[4]  = 20.;
   RecoilBins[5]  = 25.;
   RecoilBins[6]  = 30.;
   RecoilBins[7]  = 35.;
   RecoilBins[8]  = 40.;
   RecoilBins[9]  = 50.;
   RecoilBins[10] = 60.;
   RecoilBins[11] = 70.;
   RecoilBins[12] = 80.;
   RecoilBins[13] = 90.;
   RecoilBins[14] = 100.;
   RecoilBins[15] = 120.;
   RecoilBins[16] = 150.;

   if (Wlnu12LoBaseTree == 0 ) {
     cout<<"Usage: Wlnu12LoBase(TTree*... ) "<<endl;
     exit(-1);
   }
     cout<<"Wlnu12LoBase.h: initializing the trees"<<endl;
   LumiWeight = lumiweight;
   cout<<"Input Value of Lumiweight = "<<lumiweight<<" Initialized as = "<<LumiWeight<<endl;
   OutNameBase = OutNameBase_;
   Mode = mode_;
   AnaChannel = AnaChannel_;
   WCHARGE = Wcharge;
   RunOnMC = runOnMC;
   RandomSeed = Seed;
   Init(Wlnu12LoBaseTree);
   InitVar();
}

   Wlnu12LoBase::~Wlnu12LoBase()
   {
     if (!fChain) return;
     delete fChain->GetCurrentFile();
   }

   Int_t Wlnu12LoBase::GetEntry(Long64_t entry)
   {
     // Read contents of entry.
     if (!fChain) return 0;
     return fChain->GetEntry(entry);
   }

   Long64_t Wlnu12LoBase::LoadTree(Long64_t entry)
   {
     // Set the environment to read one entry
     if (!fChain) return -5;
     Long64_t centry = fChain->LoadTree(entry);
     if (centry < 0) return centry;
     if (fChain->GetTreeNumber() != fCurrent) {
       fCurrent = fChain->GetTreeNumber();
       Notify();
     }
     return centry;
   }
   
   Bool_t Wlnu12LoBase::Notify()
   {
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

     return kTRUE;
   }


void Wlnu12LoBase::Show(Long64_t entry)
{
  // Print contents of entry.
  // If entry is not specified, print current entry
  if (!fChain) return;
  fChain->Show(entry);
}

// Lepton effi correction
Double_t Wlnu12LoBase::DoEffiCorr()
{
  if(AnaChannel == "Electron2012LoPU")
  {
    if(W.charge > 0)
    {
      if (W.lep_pt_corr>25. && W.lep_pt_corr <=40.)
      {
	if (W.lep_etaSC >-2.5 && W.lep_etaSC <= -1.5 )  {return 0.984562;}
        if (W.lep_etaSC >-1.5 && W.lep_etaSC <= -0.5 )  {return 0.941208;}
        if (W.lep_etaSC >-0.5 && W.lep_etaSC <= 0.0 )   {return 0.940745;}
        if (W.lep_etaSC > 0.0 && W.lep_etaSC <= 0.5 )   {return 0.92364;}
        if (W.lep_etaSC > 0.5 && W.lep_etaSC <= 1.5 )   {return 0.971993;}
        if (W.lep_etaSC > 1.5 && W.lep_etaSC < 2.5 )    {return 0.976109;}
      }else if (W.lep_pt_corr>40. && W.lep_pt_corr <=50.)
      {
        if (W.lep_etaSC >-2.5 && W.lep_etaSC <= -1.5 )  {return 1.01097;}
        if (W.lep_etaSC >-1.5 && W.lep_etaSC <= -0.5 )  {return 0.956088;}
        if (W.lep_etaSC >-0.5 && W.lep_etaSC <= 0.0 )   {return 0.947571;}
        if (W.lep_etaSC > 0.0 && W.lep_etaSC <= 0.5 )   {return 0.935623;}
        if (W.lep_etaSC > 0.5 && W.lep_etaSC <= 1.5 )   {return 0.972539;}
        if (W.lep_etaSC > 1.5 && W.lep_etaSC < 2.5 )    {return 1.00965;}
      }else if (W.lep_pt_corr>50.)
      {
        if (W.lep_etaSC >-2.5 && W.lep_etaSC <= -1.5 )  {return 1.02735;}
        if (W.lep_etaSC >-1.5 && W.lep_etaSC <= -0.5 )  {return 0.981588;}
        if (W.lep_etaSC >-0.5 && W.lep_etaSC <= 0.0 )   {return 1.02193;}
        if (W.lep_etaSC > 0.0 && W.lep_etaSC <= 0.5 )   {return 1.00219;}
        if (W.lep_etaSC > 0.5 && W.lep_etaSC <= 1.5 )   {return 1.01495;}
        if (W.lep_etaSC > 1.5 && W.lep_etaSC < 2.5 )    {return 1.02938;}
      }
    }
    if(W.charge < 0)
    {
      if (W.lep_pt_corr>25. && W.lep_pt_corr <=40.)
      {
        if (W.lep_etaSC >-2.5 && W.lep_etaSC <= -1.5 )  {return 0.98735;}
        if (W.lep_etaSC >-1.5 && W.lep_etaSC <= -0.5 )  {return 0.957324;}
        if (W.lep_etaSC >-0.5 && W.lep_etaSC <= 0.0 )   {return 0.96864;}
        if (W.lep_etaSC > 0.0 && W.lep_etaSC <= 0.5 )   {return 0.923753;}
        if (W.lep_etaSC > 0.5 && W.lep_etaSC <= 1.5 )   {return 0.977473;}
        if (W.lep_etaSC > 1.5 && W.lep_etaSC < 2.5 )    {return 0.976639;}
      }else if (W.lep_pt_corr>40. && W.lep_pt_corr <=50.)
      {
        if (W.lep_etaSC >-2.5 && W.lep_etaSC <= -1.5 )  {return 0.994031;}
        if (W.lep_etaSC >-1.5 && W.lep_etaSC <= -0.5 )  {return 0.956422;}
        if (W.lep_etaSC >-0.5 && W.lep_etaSC <= 0.0 )   {return 0.949236;}
        if (W.lep_etaSC > 0.0 && W.lep_etaSC <= 0.5 )   {return 0.945777;}
        if (W.lep_etaSC > 0.5 && W.lep_etaSC <= 1.5 )   {return 0.954156;}
        if (W.lep_etaSC > 1.5 && W.lep_etaSC < 2.5 )    {return 0.98203;}
      }else if (W.lep_pt_corr>50.)
      {
        if (W.lep_etaSC >-2.5 && W.lep_etaSC <= -1.5 )  {return 0.983318;}
        if (W.lep_etaSC >-1.5 && W.lep_etaSC <= -0.5 )  {return 0.957025;}
        if (W.lep_etaSC >-0.5 && W.lep_etaSC <= 0.0 )   {return 0.964789;}
        if (W.lep_etaSC > 0.0 && W.lep_etaSC <= 0.5 )   {return 0.956213;}
        if (W.lep_etaSC > 0.5 && W.lep_etaSC <= 1.5 )   {return 1.00699;}
        if (W.lep_etaSC > 1.5 && W.lep_etaSC < 2.5 )    {return 0.971778;}
      }
    }
  }
  if(AnaChannel == "Muon2012LoPU")
  {
    if(W.charge > 0)
    {
      if (W.lep_pt_corr>20. && W.lep_pt_corr <=40.)
      {
	if (W.lep_eta >-2.1 && W.lep_eta <= -1.6 )  {return 0.954504;}
        if (W.lep_eta >-1.6 && W.lep_eta <= -1.2 )  {return 0.965095;}
        if (W.lep_eta >-1.2 && W.lep_eta <= -0.8 )  {return 1.034190;}
        if (W.lep_eta >-0.8 && W.lep_eta <= -0.4 )  {return 0.991577;}
        if (W.lep_eta >-0.4 && W.lep_eta <= 0.0 )   {return 0.962334;}
        if (W.lep_eta > 0.0 && W.lep_eta <= 0.4 )   {return 0.958551;}
        if (W.lep_eta > 0.4 && W.lep_eta <= 0.8 )   {return 0.991061;}
        if (W.lep_eta > 0.8 && W.lep_eta <= 1.2 )   {return 0.940849;}
        if (W.lep_eta > 1.2 && W.lep_eta <= 1.6 )   {return 0.990681;}
        if (W.lep_eta > 1.6 && W.lep_eta < 2.1 )    {return 1.010380;}
      }else if (W.lep_pt_corr>40. && W.lep_pt_corr <=55.)
      { 
        if (W.lep_eta >-2.1 && W.lep_eta <= -1.6 )  {return 0.969176;}
        if (W.lep_eta >-1.6 && W.lep_eta <= -1.2 )  {return 0.972400;}
        if (W.lep_eta >-1.2 && W.lep_eta <= -0.8 )  {return 0.973228;}
        if (W.lep_eta >-0.8 && W.lep_eta <= -0.4 )  {return 0.999164;}
        if (W.lep_eta >-0.4 && W.lep_eta <= 0.0 )   {return 0.979990;}
        if (W.lep_eta > 0.0 && W.lep_eta <= 0.4 )   {return 0.968619;}
        if (W.lep_eta > 0.4 && W.lep_eta <= 0.8 )   {return 0.990016;}
        if (W.lep_eta > 0.8 && W.lep_eta <= 1.2 )   {return 0.974650;}
        if (W.lep_eta > 1.2 && W.lep_eta <= 1.6 )   {return 0.947018;}
        if (W.lep_eta > 1.6 && W.lep_eta < 2.1 )    {return 1.016190;}
      }else if (W.lep_pt_corr>55.)
      { 
        if (W.lep_eta >-2.1 && W.lep_eta <= -1.6 )  {return 0.994098;}
        if (W.lep_eta >-1.6 && W.lep_eta <= -1.2 )  {return 0.997404;}
        if (W.lep_eta >-1.2 && W.lep_eta <= -0.8 )  {return 0.991279;}
        if (W.lep_eta >-0.8 && W.lep_eta <= -0.4 )  {return 1.011360;}
        if (W.lep_eta >-0.4 && W.lep_eta <= 0.0 )   {return 0.991957;}
        if (W.lep_eta > 0.0 && W.lep_eta <= 0.4 )   {return 0.980447;}
        if (W.lep_eta > 0.4 && W.lep_eta <= 0.8 )   {return 1.002110;}
        if (W.lep_eta > 0.8 && W.lep_eta <= 1.2 )   {return 0.992727;}
        if (W.lep_eta > 1.2 && W.lep_eta <= 1.6 )   {return 0.971370;}
        if (W.lep_eta > 1.6 && W.lep_eta < 2.1 )    {return 1.042320;}
      }
    }
    if(W.charge < 0)
    {
      if (W.lep_pt_corr>20. && W.lep_pt_corr <=40.)
      {
        if (W.lep_eta >-2.1 && W.lep_eta <= -1.6 )  {return 0.970457;}
        if (W.lep_eta >-1.6 && W.lep_eta <= -1.2 )  {return 0.980821;}
        if (W.lep_eta >-1.2 && W.lep_eta <= -0.8 )  {return 0.938278;}
        if (W.lep_eta >-0.8 && W.lep_eta <= -0.4 )  {return 0.975069;}
        if (W.lep_eta >-0.4 && W.lep_eta <= 0.0 )   {return 0.946864;}
        if (W.lep_eta > 0.0 && W.lep_eta <= 0.4 )   {return 0.972747;}
        if (W.lep_eta > 0.4 && W.lep_eta <= 0.8 )   {return 0.966432;}
        if (W.lep_eta > 0.8 && W.lep_eta <= 1.2 )   {return 0.934198;}
        if (W.lep_eta > 1.2 && W.lep_eta <= 1.6 )   {return 1.000180;}
        if (W.lep_eta > 1.6 && W.lep_eta < 2.1 )    {return 1.037630;}
      }else if (W.lep_pt_corr>40. && W.lep_pt_corr <=55.)
      {
        if (W.lep_eta >-2.1 && W.lep_eta <= -1.6 )  {return 0.928815;}
        if (W.lep_eta >-1.6 && W.lep_eta <= -1.2 )  {return 0.993676;}
        if (W.lep_eta >-1.2 && W.lep_eta <= -0.8 )  {return 0.974560;}
        if (W.lep_eta >-0.8 && W.lep_eta <= -0.4 )  {return 0.989552;}
        if (W.lep_eta >-0.4 && W.lep_eta <= 0.0 )   {return 0.972247;}
        if (W.lep_eta > 0.0 && W.lep_eta <= 0.4 )   {return 0.982316;}
        if (W.lep_eta > 0.4 && W.lep_eta <= 0.8 )   {return 0.984550;}
        if (W.lep_eta > 0.8 && W.lep_eta <= 1.2 )   {return 0.973194;}
        if (W.lep_eta > 1.2 && W.lep_eta <= 1.6 )   {return 0.981252;}
        if (W.lep_eta > 1.6 && W.lep_eta < 2.1 )    {return 0.956579;}
      }else if (W.lep_pt_corr>55.)
      {
        if (W.lep_eta >-2.1 && W.lep_eta <= -1.6 )  {return 0.927956;}
        if (W.lep_eta >-1.6 && W.lep_eta <= -1.2 )  {return 0.992756;}
        if (W.lep_eta >-1.2 && W.lep_eta <= -0.8 )  {return 0.950278;}
        if (W.lep_eta >-0.8 && W.lep_eta <= -0.4 )  {return 0.986488;}
        if (W.lep_eta >-0.4 && W.lep_eta <= 0.0 )   {return 0.969236;}
        if (W.lep_eta > 0.0 && W.lep_eta <= 0.4 )   {return 0.979275;}
        if (W.lep_eta > 0.4 && W.lep_eta <= 0.8 )   {return 0.981501;}
        if (W.lep_eta > 0.8 && W.lep_eta <= 1.2 )   {return 0.948946;}
        if (W.lep_eta > 1.2 && W.lep_eta <= 1.6 )   {return 0.980344;}
        if (W.lep_eta > 1.6 && W.lep_eta < 2.1 )    {return 0.955694;}
      }
    }
  }
}

//RD Scale Correction
Int_t Wlnu12LoBase::DoScaleCorr(int i)
{
  if(AnaChannel == "Muon2012LoPU")
  {
    if(fabs((*W_Lept1_eta)[i]) >= 0.0 && fabs((*W_Lept1_eta)[i]) < 0.4) scalecorr = 1.0025;
    if(fabs((*W_Lept1_eta)[i]) >= 0.4 && fabs((*W_Lept1_eta)[i]) < 0.8) scalecorr = 1.0022;
    if(fabs((*W_Lept1_eta)[i]) >= 0.8 && fabs((*W_Lept1_eta)[i]) < 1.2) scalecorr = 0.9995;
    if(fabs((*W_Lept1_eta)[i]) >= 1.2 && fabs((*W_Lept1_eta)[i]) < 1.6) scalecorr = 1.0018;
    if(fabs((*W_Lept1_eta)[i]) >= 1.6 && fabs((*W_Lept1_eta)[i]) < 2.1) scalecorr = 1.0007;
    
    W.lep_pt_corr = scalecorr*(*W_Lept1_pt)[i];
  }
  if(AnaChannel == "Electron2012LoPU")
  {
    if(fabs((*W_Lept1_etaSC)[i]) >= 0.0   && fabs((*W_Lept1_etaSC)[i]) < 0.4) scalecorr = 0.999315;
    if(fabs((*W_Lept1_etaSC)[i]) >= 0.4   && fabs((*W_Lept1_etaSC)[i]) < 0.8) scalecorr = 1.00358;
    if(fabs((*W_Lept1_etaSC)[i]) >= 0.8   && fabs((*W_Lept1_etaSC)[i]) < 1.2) scalecorr = 1.00325;
    if(fabs((*W_Lept1_etaSC)[i]) >= 1.2   && fabs((*W_Lept1_etaSC)[i]) < 1.4442) scalecorr = 1.00244;
    if(fabs((*W_Lept1_etaSC)[i]) >= 1.566 && fabs((*W_Lept1_etaSC)[i]) < 2.0) scalecorr = 1.0067;
    if(fabs((*W_Lept1_etaSC)[i]) >= 2.0   && fabs((*W_Lept1_etaSC)[i]) < 2.5) scalecorr = 0.992737;
    W.lep_pt_corr = scalecorr*(*W_Lept1_pt)[i];
  }
  return 0;
}

Int_t Wlnu12LoBase::DoSmearCorr(int i)
{
  if(AnaChannel == "Muon2012LoPU")
  {
    if(fabs((*W_Lept1_eta)[i]) >= 0.0 && fabs((*W_Lept1_eta)[i]) < 0.4) smearcorr = 0.01;
    if(fabs((*W_Lept1_eta)[i]) >= 0.4 && fabs((*W_Lept1_eta)[i]) < 0.8) smearcorr = 0.381253;
    if(fabs((*W_Lept1_eta)[i]) >= 0.8 && fabs((*W_Lept1_eta)[i]) < 1.2) smearcorr = 0.743902;
    if(fabs((*W_Lept1_eta)[i]) >= 1.2 && fabs((*W_Lept1_eta)[i]) < 1.6) smearcorr = 0.637325;
    if(fabs((*W_Lept1_eta)[i]) >= 1.6 && fabs((*W_Lept1_eta)[i]) < 2.1) smearcorr = 0.611946;

    PtEtaPhiMLorentzVector WmuMC_4((*W_Lept1_pt)[i],(*W_Lept1_eta)[i],(*W_Lept1_phi)[i],0.1056);
    smearSF = smearRandom->Gaus(WmuMC_4.E(), smearcorr)/WmuMC_4.E();
    WmuMC_4= smearSF*WmuMC_4;
    W.lep_pt_corr=WmuMC_4.Pt();
    //cout<<"Smear gRandom: "<<smearRandom->Gaus(0,1)<<endl;
  }
  if(AnaChannel == "Electron2012LoPU")
  {
    if(fabs((*W_Lept1_etaSC)[i]) >= 0.0   && fabs((*W_Lept1_etaSC)[i]) < 0.4) smearcorr = 0.382443;
    if(fabs((*W_Lept1_etaSC)[i]) >= 0.4   && fabs((*W_Lept1_etaSC)[i]) < 0.8) smearcorr = 0.356171;
    if(fabs((*W_Lept1_etaSC)[i]) >= 0.8   && fabs((*W_Lept1_etaSC)[i]) < 1.2) smearcorr = 0.559123;
    if(fabs((*W_Lept1_etaSC)[i]) >= 1.2   && fabs((*W_Lept1_etaSC)[i]) < 1.4442) smearcorr = 0.01;
    if(fabs((*W_Lept1_etaSC)[i]) >= 1.566 && fabs((*W_Lept1_etaSC)[i]) < 2.0) smearcorr = 0.972944;
    if(fabs((*W_Lept1_etaSC)[i]) >= 2.0   && fabs((*W_Lept1_etaSC)[i]) < 2.5) smearcorr = 1.84788;
     
    PtEtaPhiMLorentzVector WeleMC_4((*W_Lept1_pt)[i],(*W_Lept1_eta)[i],(*W_Lept1_phi)[i],0.000511);
    smearSF = smearRandom->Gaus(WeleMC_4.E(), smearcorr)/WeleMC_4.E();
    WeleMC_4=smearSF*WeleMC_4;
    W.lep_pt_corr=WeleMC_4.Pt();
  }
  return 0;
}

Int_t Wlnu12LoBase::TauCut(int i)
{
  //if( (*W_Lept1_MedComIsoDelBetCorr3Hits)[i] < 0.5 )return -1;
  //if( (*W_Lept1_decModFind)[i] < 0.5 )return -1;
  if( fabs((*W_Lept1_eta)[i]) > 2.3 )return -1;
  if( fabs(W.lep_pt_corr) < 20 )return -1;
  return 1;
}

Int_t Wlnu12LoBase::MuonCut(int i)
{
  if( !(*W_Lept1_isGlobal)[i])return -1;
  //if((*W_Lept1_pt)[i] < 20) return -1;
  if(W.lep_pt_corr < 20) return -1;
  if(fabs((*W_Lept1_eta)[i])>2.1) return -1;
  if( (*W_Lept1_globalNormChi2)[i]<0 || (*W_Lept1_globalNormChi2)[i] >= 10) return -1;
  if( (*W_Lept1_muonHits)[i] <1) return -1;
  if( (*W_Lept1_matchStations)[i] <2 ) return -1;
  if( (*W_Lept1_trkLayers)[i] <6 )return -1;
  if( (*W_Lept1_pixelHits)[i] <1 )return -1;
  if( fabs( (*W_Lept1_dB)[i]) >0.02 )return -1;
  if( fabs( (*W_Lept1_dz)[i]) >0.5 )return -1;
  //if( ( (*W_Lept1_nhIso04)[i]+(*W_Lept1_chIso04)[i]+(*W_Lept1_phIso04)[i])/(*W_Lept1_pt)[i] > 0.12) return -1;
  double betaCor04= max(0.0,(*W_Lept1_nhIso04)[i]+(*W_Lept1_phIso04)[i]-0.5*(*W_Lept1_pcIso04)[i]);
  if( ((*W_Lept1_chIso04)[i]+betaCor04)/W.lep_pt_corr > 0.12) return -1;
  return 1;
}

Int_t Wlnu12LoBase::MuonCutSide(int i)
{
  if(!(*W_Lept1_isGlobal)[i])return -1;
  if(W_Lept1_pt_Corr[i] < 20) return -1;
  if(fabs((*W_Lept1_eta)[i])>2.1) return -1;
  if((*W_Lept1_globalNormChi2)[i]<0 || (*W_Lept1_globalNormChi2)[i] >= 10) return -1;
  if((*W_Lept1_muonHits)[i] <1) return -1;
  if((*W_Lept1_matchStations)[i] <2) return -1;
  if((*W_Lept1_trkLayers)[i] <6)return -1;
  if((*W_Lept1_pixelHits)[i] <1)return -1;
  if(fabs( (*W_Lept1_dB)[i]) >0.02)return -1;
  if(fabs( (*W_Lept1_dz)[i]) >0.5)return -1;
  double betaCor04= max(0.0,(*W_Lept1_nhIso04)[i]+(*W_Lept1_phIso04)[i]-0.5*(*W_Lept1_pcIso04)[i]);
  if(((*W_Lept1_chIso04)[i]+betaCor04)/W_Lept1_pt_Corr[i] < 0.3 || ((*W_Lept1_chIso04)[i]+betaCor04)/W_Lept1_pt_Corr[i] > 0.5) return -1; //Side Band

  return 1;
}

Int_t Wlnu12LoBase::AddMuonCut(int i)
{
  if(!(*W_Lept1_isTrker)[i] || !(*W_Lept1_isGlobal)[i]) return -1; //Signal Band only. For Side Band comment this line.
  if(W.lep_pt_corr <= 10) return -1;
  if(fabs((*W_Lept1_eta)[i])>=2.4) return -1;
  double betaCor04= max(0.0,(*W_Lept1_nhIso04)[i]+(*W_Lept1_phIso04)[i]-0.5*(*W_Lept1_pcIso04)[i]);
  if(((*W_Lept1_chIso04)[i]+betaCor04)/W.lep_pt_corr > 0.20) return -1;
  return 1;
}

Int_t Wlnu12LoBase::ElectronCut(int i)
{
  if(W.lep_pt_corr < 25) return -1;
  if(fabs((*W_Lept1_etaSC)[i])>2.5) return -1;
  if(fabs((*W_Lept1_etaSC)[i])>1.4442 && fabs((*W_Lept1_etaSC)[i])<1.566)return -1;
  if( fabs((*W_Lept1_etaSC)[i]) < 1.4442)
  {
    if((*W_Lept1_sigmaIEtaIEta)[i] > 0.01) return -1; // use this line to get n.of.events in AB area in  ABCD method
    if(fabs((*W_Lept1_dEtaIn)[i]) > 0.004) return -1;
    if(fabs((*W_Lept1_dPhiIn)[i]) > 0.06) return -1;
    if((*W_Lept1_HoverE)[i] > 0.12) return -1;
    if(fabs((*W_Lept1_dxy)[i]) > 0.02 ) return -1;
    if(fabs((*W_Lept1_dz)[i]) > 0.1 ) return -1;
    if(fabs((*W_Lept1_InvEminusInvP)[i]) > 0.05 ) return -1;
    if(fabs((*W_Lept1_mHits)[i]) > 1) return -1;
  }else{
    if((*W_Lept1_sigmaIEtaIEta)[i] > 0.03) return -1;   // use this line to get n.of.events in AB area in  ABCD method
    if(fabs((*W_Lept1_dEtaIn)[i]) > 0.007) return -1;
    if(fabs((*W_Lept1_dPhiIn)[i]) > 0.03) return -1;
    if((*W_Lept1_HoverE)[i] > 0.10) return -1;
    if(fabs((*W_Lept1_dxy)[i]) > 0.02) return -1;
    if(fabs((*W_Lept1_dz)[i]) > 0.1) return -1;
    if(fabs((*W_Lept1_InvEminusInvP)[i]) > 0.05) return -1;
    if(fabs((*W_Lept1_mHits)[i]) > 1) return -1;
  }
  
  if((*W_Lept1_hasConversion)[i]) return -1;
  if((*W_Lept1_relIsoRho03)[i] > 0.15) return -1;
  
  return 1;
}

Int_t Wlnu12LoBase::ElectronCutHighPU(int i)
{
  //////////////  Ele   V5 =======================================
  double RelComIsoEB = (*W_Lept1_RelisolPtTrks03)[i]+max(0.,((*W_Lept1_RelisoEm03)[i]*W.lep_pt_corr)-1.)+(*W_Lept1_RelisoHad03)[i];
  double RelComIsoEE = (*W_Lept1_RelisolPtTrks03)[i]+(*W_Lept1_RelisoEm03)[i]+(*W_Lept1_RelisoHad03)[i];
  if(W.lep_pt_corr < 30) return -1;
  if(fabs((*W_Lept1_etaSC)[i])>2.5) return -1;
  //W/Z
  if(fabs((*W_Lept1_etaSC)[i])>1.4442 && fabs((*W_Lept1_etaSC)[i])<1.566)return -1;
  
  if( fabs( (*W_Lept1_etaSC)[i]) < 1.4442)
  {
    if( (*W_Lept1_sigmaIEtaIEta)[i] > 0.01 ) return -1;
    if( fabs((*W_Lept1_dEtaIn)[i]) >  0.004 ) return -1;
    if( fabs((*W_Lept1_dPhiIn)[i])  > 0.06 ) return -1;
    if( (*W_Lept1_HoverE)[i] > 0.12 ) return -1;
    if( fabs((*W_Lept1_dxy)[i]) > 0.02 ) return -1;
    if( fabs((*W_Lept1_dz)[i]) > 0.1 ) return -1;
    if( fabs((*W_Lept1_InvEminusInvP)[i]) > 0.05 ) return -1;
    if( fabs((*W_Lept1_mHits)[i]) > 1) return -1;
    
    //# Detector based Isolation. for WP80 Variable 
    //if(RelComIsoEB>0.07) return -1;
    //if((*W_Lept1_RelisolPtTrks03)[i] > 0.05) return -1;
    //if((*W_Lept1_RelisoEm03)[i] > 0.15) return -1;
    //if((*W_Lept1_RelisoHad03)[i] > 0.10) return -1; 
  }else{
    if( (*W_Lept1_sigmaIEtaIEta)[i] > 0.03 ) return -1;
    if( fabs((*W_Lept1_dEtaIn)[i])  >   0.007 ) return -1;
    if( fabs((*W_Lept1_dPhiIn)[i])  > 0.03 ) return -1;
    if( (*W_Lept1_HoverE)[i] > 0.1 ) return -1;
    if( fabs((*W_Lept1_dxy)[i]) > 0.02 ) return -1;
    if( fabs((*W_Lept1_dz)[i]) > 0.1 ) return -1;
    if( fabs((*W_Lept1_InvEminusInvP)[i]) > 0.05) return -1;
    if( fabs((*W_Lept1_mHits)[i]) > 1) return -1;
    
    //# Detector based Isolation. for WP80 Variable 
    //if(RelComIsoEE>0.06) return -1;
    //if((*W_Lept1_RelisolPtTrks03)[i] > 0.05) return -1;
    //if((*W_Lept1_RelisoEm03)[i] > 0.1) return -1;
    //if((*W_Lept1_RelisoHad03)[i] > 0.1) return -1;
  }
  
  if( (*W_Lept1_hasConversion)[i] ) return -1;
  if( (*W_Lept1_relIsoRho03)[i] > 0.15 ) return -1;
  
  return 1;
}

Int_t Wlnu12LoBase::ElectronCutSide(int i)
{
  if(W_Lept1_pt_Corr[i] < 25) return -1;
  if(fabs((*W_Lept1_etaSC)[i])>2.5) return -1;
  if(fabs((*W_Lept1_etaSC)[i])>1.4442 && fabs((*W_Lept1_etaSC)[i]) < 1.566) return -1;
  
  if(fabs((*W_Lept1_etaSC)[i]) < 1.4442)
  {
    if((*W_Lept1_sigmaIEtaIEta)[i] > 0.01) return -1;
    if(fabs((*W_Lept1_dEtaIn)[i]) < 0.004) return -1;
    if(fabs((*W_Lept1_dPhiIn)[i]) < 0.06) return -1;
    if((*W_Lept1_HoverE)[i] > 0.12) return -1;
    if(fabs((*W_Lept1_dxy)[i]) > 0.02) return -1;
    if(fabs((*W_Lept1_dz)[i]) > 0.1) return -1;
    if(fabs((*W_Lept1_InvEminusInvP)[i]) > 0.05) return -1;
    if(fabs((*W_Lept1_mHits)[i]) > 1) return -1;
  }else{
    if((*W_Lept1_sigmaIEtaIEta)[i] > 0.03) return -1;
    if(fabs((*W_Lept1_dEtaIn)[i]) < 0.007) return -1;
    if(fabs((*W_Lept1_dPhiIn)[i]) < 0.03) return -1;
    if((*W_Lept1_HoverE)[i] > 0.10) return -1;
    if(fabs((*W_Lept1_dxy)[i]) > 0.02) return -1;
    if(fabs((*W_Lept1_dz)[i]) > 0.1) return -1;
    if(fabs((*W_Lept1_InvEminusInvP)[i]) > 0.05) return -1;
    if(fabs((*W_Lept1_mHits)[i]) > 1) return -1;
  }
  if((*W_Lept1_hasConversion)[i]) return -1;
  return 1;
}

Int_t Wlnu12LoBase::ElectronCutSideHighPU(int i)
{
  double RelComIsoEB = (*W_Lept1_RelisolPtTrks03)[i]+max(0.,((*W_Lept1_RelisoEm03)[i]*W.lep_pt_corr)-1.)+(*W_Lept1_RelisoHad03)[i];
  double RelComIsoEE = (*W_Lept1_RelisolPtTrks03)[i]+(*W_Lept1_RelisoEm03)[i]+(*W_Lept1_RelisoHad03)[i]; 
  if(W_Lept1_pt_Corr[i] < 30) return -1;
  if(fabs((*W_Lept1_etaSC)[i])>2.5) return -1;
  if(fabs((*W_Lept1_etaSC)[i])>1.4442 && fabs((*W_Lept1_etaSC)[i]) < 1.566) return -1;
  
  if(fabs((*W_Lept1_etaSC)[i]) < 1.4442)
  {
    if((*W_Lept1_sigmaIEtaIEta)[i] > 0.01) return -1;
    if(fabs((*W_Lept1_dEtaIn)[i]) < 0.004) return -1;
    if(fabs((*W_Lept1_dPhiIn)[i]) < 0.06) return -1;
    if((*W_Lept1_HoverE)[i] > 0.12) return -1;
    if(fabs((*W_Lept1_dxy)[i]) > 0.02) return -1;
    if(fabs((*W_Lept1_dz)[i]) > 0.1) return -1;
    if(fabs((*W_Lept1_InvEminusInvP)[i]) > 0.05) return -1;
    if(fabs((*W_Lept1_mHits)[i]) > 1) return -1;
    //if(RelComIsoEB<0.07) return -1;
    //if((*W_Lept1_RelisolPtTrks03)[i] < 0.09) return -1;
    //if((*W_Lept1_RelisoEm03)[i] < 0.07) return -1;
    //if((*W_Lept1_RelisoHad03)[i] < 0.10) return -1;
  } else{
    if((*W_Lept1_sigmaIEtaIEta)[i] > 0.03) return -1;
    if(fabs((*W_Lept1_dEtaIn)[i]) < 0.007) return -1;
    if(fabs((*W_Lept1_dPhiIn)[i]) < 0.03) return -1;
    if((*W_Lept1_HoverE)[i] > 0.10) return -1;
    if(fabs((*W_Lept1_dxy)[i]) > 0.02) return -1;
    if(fabs((*W_Lept1_dz)[i]) > 0.1) return -1;
    if(fabs((*W_Lept1_InvEminusInvP)[i]) > 0.05) return -1;
    if(fabs((*W_Lept1_mHits)[i]) > 1) return -1;
    //if(RelComIsoEE<0.06) return -1;
    //if((*W_Lept1_RelisolPtTrks03)[i] < 0.04) return -1;
    //if((*W_Lept1_RelisoEm03)[i] < 0.05) return -1;
    //if((*W_Lept1_RelisoHad03)[i] < 0.025) return -1;
  }
  
  if((*W_Lept1_hasConversion)[i]) return -1;
  if((*W_Lept1_relIsoRho03)[i] > 0.15) return -1;
  
  return 1;
}

Int_t Wlnu12LoBase::AddElectronCut(int i)
{
  if(W.lep_pt_corr < 20) return -1;
  if(fabs((*W_Lept1_etaSC)[i])>2.5) return -1;
  if(fabs((*W_Lept1_etaSC)[i])>1.4442 && fabs((*W_Lept1_etaSC)[i]) < 1.566) return -1;
  if(fabs((*W_Lept1_etaSC)[i]) < 1.4442)
  {
    if((*W_Lept1_sigmaIEtaIEta)[i] > 0.01) return -1;
    if(fabs((*W_Lept1_dEtaIn)[i]) > 0.007) return -1;
    if(fabs((*W_Lept1_dPhiIn)[i]) > 0.8) return -1;
    if((*W_Lept1_HoverE)[i] > 0.15) return -1;
    if(fabs((*W_Lept1_dxy)[i]) > 0.04) return -1;
    if(fabs((*W_Lept1_dz)[i]) > 0.2) return -1;
  }else{
    if((*W_Lept1_sigmaIEtaIEta)[i] > 0.03) return -1;
    if(fabs((*W_Lept1_dEtaIn)[i]) > 0.01) return -1;
    if(fabs((*W_Lept1_dPhiIn)[i]) > 0.7) return -1;
    if(fabs((*W_Lept1_dxy)[i]) > 0.04) return -1;
    if(fabs((*W_Lept1_dz)[i]) > 0.2) return -1;
  }
  
  if((*W_Lept1_relIsoRho03)[i] > 0.15) return -1;
  
  return 1;
}

Int_t Wlnu12LoBase::AddElectronCutHighPU(int i)
{
  if(W.lep_pt_corr < 25) return -1;
  if(fabs((*W_Lept1_etaSC)[i])>2.5) return -1;
  if(fabs((*W_Lept1_etaSC)[i])>1.4442 && fabs((*W_Lept1_etaSC)[i]) < 1.566) return -1;
  
  if( fabs( (*W_Lept1_etaSC)[i]) < 1.4442)
  {
    if((*W_Lept1_sigmaIEtaIEta)[i] > 0.01) return -1;
    if(fabs((*W_Lept1_dEtaIn)[i]) > 0.004) return -1;
    if(fabs((*W_Lept1_dPhiIn)[i]) > 0.06) return -1;
    if((*W_Lept1_HoverE)[i] > 0.12) return -1;
    if(fabs((*W_Lept1_dxy)[i]) > 0.02) return -1;
    if(fabs((*W_Lept1_dz)[i]) > 0.1) return -1;
  } else{
    if((*W_Lept1_sigmaIEtaIEta)[i] > 0.03) return -1;
    if(fabs((*W_Lept1_dEtaIn)[i]) > 0.007) return -1;
    if(fabs((*W_Lept1_dPhiIn)[i]) > 0.03) return -1;
    //if((*W_Lept1_HoverE)[i] > 0.10) return -1;
    if(fabs((*W_Lept1_dxy)[i]) > 0.02) return -1;
    if(fabs((*W_Lept1_dz)[i]) > 0.1) return -1;
  }

  if((*W_Lept1_relIsoRho03)[i] > 0.15) return -1;

  return 1;
}

Int_t Wlnu12LoBase::MuonCutZ(int i)
{
  if((*Z_Sign)[i] != 0) return -1;
  if(!(*Z_Lept1_isGlobal)[i])return -1;
  if(!(*Z_Lept2_isGlobal)[i])return -1;
  if((*Z_Lept1_pt)[i] < 20) return -1;//trigger SingleMu15 but we use 25 for Wpt
  if(fabs((*Z_Lept1_eta)[i])>2.1) return -1;
  if(fabs((*Z_Lept2_eta)[i])>2.1) return -1;
  if((*Z_Lept1_globalNormChi2)[i]<0 || (*Z_Lept1_globalNormChi2)[i] >= 10) return -1;
  if((*Z_Lept2_globalNormChi2)[i]<0 || (*Z_Lept2_globalNormChi2)[i] >= 10) return -1;
  if((*Z_Lept1_muonHits)[i] <1) return -1;
  if((*Z_Lept2_muonHits)[i] <1) return -1;
  if((*Z_Lept1_matchStations)[i] <2) return -1;
  if((*Z_Lept2_matchStations)[i] <2) return -1;
  if((*Z_Lept1_trkLayers)[i] <6)return -1;
  if((*Z_Lept2_trkLayers)[i] <6)return -1;
  if((*Z_Lept1_pixelHits)[i] <1)return -1;
  if((*Z_Lept2_pixelHits)[i] <1)return -1;
  if(fabs((*Z_Lept1_dB)[i]) >0.02)return -1;
  if(fabs((*Z_Lept2_dB)[i]) >0.02)return -1;
  if(fabs((*Z_Lept1_dz)[i]) >0.5)return -1;
  if(fabs((*Z_Lept2_dz)[i]) >0.5)return -1;
  double betaCor04 = max(0.0,(*Z_Lept1_nhIso04)[i]+(*Z_Lept1_phIso04)[i]-0.5*(*Z_Lept1_pcIso04)[i]);
  if(((*Z_Lept1_chIso04)[i]+betaCor04)/(*Z_Lept1_pt)[i] > 0.12) return -1; //Signal Band
  betaCor04= max(0.0,(*Z_Lept2_nhIso04)[i]+(*Z_Lept2_phIso04)[i]-0.5*(*Z_Lept2_pcIso04)[i]);
  if(((*Z_Lept2_chIso04)[i]+betaCor04)/(*Z_Lept2_pt)[i] > 0.12) return -1; //Signal Band
  return 1;
}

Int_t Wlnu12LoBase::ElectronCutZ(int i)
{
  if((*Z_Sign)[i] != 0) return -1;
  if((*Z_Lept1_pt)[i] < 25) return -1;
  if(fabs((*Z_Lept1_etaSC)[i])>2.5) return -1;
  if(fabs((*Z_Lept2_etaSC)[i])>2.5) return -1;
  
  if(fabs((*Z_Lept1_etaSC)[i])>1.4442 && fabs((*Z_Lept1_etaSC)[i])<1.566)return -1;
  if(fabs((*Z_Lept2_etaSC)[i])>1.4442 && fabs((*Z_Lept2_etaSC)[i])<1.566)return -1;
  
  if(fabs((*Z_Lept1_etaSC)[i]) < 1.4442)
  {
    if((*Z_Lept1_sigmaIEtaIEta)[i] > 0.01) return -1;
    if((*Z_Lept2_sigmaIEtaIEta)[i] > 0.01) return -1;
    if(fabs((*Z_Lept1_dEtaIn)[i]) > 0.004) return -1;
    if(fabs((*Z_Lept2_dEtaIn)[i]) > 0.004) return -1;
    if(fabs((*Z_Lept1_dPhiIn)[i]) > 0.06) return -1;
    if(fabs((*Z_Lept2_dPhiIn)[i]) > 0.06) return -1;
    if((*Z_Lept1_HoverE)[i] > 0.12) return -1;
    if((*Z_Lept2_HoverE)[i] > 0.12) return -1;
    if(fabs((*Z_Lept1_dxy)[i]) > 0.02) return -1;
    if(fabs((*Z_Lept2_dxy)[i]) > 0.02) return -1;
    if(fabs((*Z_Lept1_dz)[i]) > 0.1) return -1;
    if(fabs((*Z_Lept2_dz)[i]) > 0.1) return -1;
    if(fabs((*Z_Lept1_InvEminusInvP)[i]) > 0.05) return -1;
    if(fabs((*Z_Lept2_InvEminusInvP)[i]) > 0.05) return -1;
    if(fabs((*Z_Lept1_mHits)[i]) > 1) return -1;
    if(fabs((*Z_Lept2_mHits)[i]) > 1) return -1;
  }else{
    if((*Z_Lept1_sigmaIEtaIEta)[i] > 0.03) return -1;
    if((*Z_Lept2_sigmaIEtaIEta)[i] > 0.03) return -1;
    if(fabs((*Z_Lept1_dEtaIn)[i]) > 0.007) return -1;
    if(fabs((*Z_Lept2_dEtaIn)[i]) > 0.007) return -1;
    if(fabs((*Z_Lept1_dPhiIn)[i]) > 0.03) return -1;
    if(fabs((*Z_Lept2_dPhiIn)[i]) > 0.03) return -1;
    if((*Z_Lept1_HoverE)[i] > 0.10) return -1;
    if((*Z_Lept2_HoverE)[i] > 0.10) return -1;
    if(fabs((*Z_Lept1_dxy)[i]) > 0.02) return -1;
    if(fabs((*Z_Lept2_dxy)[i]) > 0.02) return -1;
    if(fabs((*Z_Lept1_dz)[i]) > 0.1) return -1;
    if(fabs((*Z_Lept2_dz)[i]) > 0.1) return -1;
    if(fabs((*Z_Lept1_InvEminusInvP)[i]) > 0.05) return -1;
    if(fabs((*Z_Lept2_InvEminusInvP)[i]) > 0.05) return -1;
    if(fabs((*Z_Lept1_mHits)[i]) > 1) return -1;
    if(fabs((*Z_Lept2_mHits)[i]) > 1) return -1;
  }
  if((*Z_Lept1_hasConversion)[i]) return -1;
  if((*Z_Lept2_hasConversion)[i]) return -1;
  if((*Z_Lept1_relIsoRho03)[i] > 0.15) return -1;
  if((*Z_Lept2_relIsoRho03)[i] > 0.15) return -1;
  return 1;
}

Int_t Wlnu12LoBase::TauCutZ(int i)
{
  if((*Z_Sign)[i] != 0) return -1;
  //if((*Z_Lept1_MedComIsoDelBetCorr3Hits)[i] < 0.5)return -1;
  //if((*Z_Lept2_MedComIsoDelBetCorr3Hits)[i] < 0.5)return -1;
  //if((*Z_Lept1_decModFind)[i] < 0.5)return -1;
  //if((*Z_Lept2_decModFind)[i] < 0.5)return -1;
  if(fabs((*Z_Lept1_eta)[i]) > 2.3)return -1;
  if(fabs((*Z_Lept2_eta)[i]) > 2.3)return -1;
  if(fabs((*Z_Lept1_pt)[i]) < 20)return -1;
  if(fabs((*Z_Lept2_pt)[i]) < 20)return -1;
  return 1;
}
Double_t Wlnu12LoBase::CalcMt(double lept, double leptPhi, double Met, double MetPhi)
{
  double ptSum = lept+Met;
  double pxSum = lept*TMath::Cos(leptPhi) + Met*TMath::Cos(MetPhi);
  double pySum = lept*TMath::Sin(leptPhi) + Met*TMath::Sin(MetPhi);
  double mt2 = ptSum*ptSum - pxSum*pxSum - pySum*pySum;
  double Mt = (mt2 > 0) ? TMath::Sqrt(mt2) : 0;
  return Mt;
}
Int_t Wlnu12LoBase::DoRecoilCorr()
{
  if(W.genIdx < 0) W.genIdx = 0;
  //genBeFsrW_pt = (*GenW_Born_pt)[WtruthIdx];
  //genW_phi = (*GenW_phi)[WtruthIdx];
  TVector2 genPost2D(
        (*GenW_PostLept1_px)[W.genIdx]+(*GenW_PostLept2_px)[W.genIdx],
        (*GenW_PostLept1_py)[W.genIdx]+(*GenW_PostLept2_py)[W.genIdx]);
  genInfo.PostW_pt= genPost2D.Mod();
  genInfo.PostW_phi= TVector2::Phi_mpi_pi(genPost2D.Phi());
  if( (*GenW_Born_Id)[W.genIdx] == 24 ){genInfo.charge = 1;}else{genInfo.charge = -1;}
  //TVector2 W2D_lepCorrOnly(
  //    W.Nu_px+W.lep_pt_corr*cos(W.lep_phi),
  //    W.Nu_py+W.lep_pt_corr*sin(W.lep_phi));
  //W.pt = W2D_lepCorrOnly.Mod();
  RecoilCorr->Correct(
      corrMet,corrMetPhi,
      genInfo.PostW_pt,genInfo.PostW_phi,//basedonthis,calculate correctedrecoilvectors
      //genBeFsrW_pt,genW_phi, 
      W.lep_pt_corr,W.lep_phi,
      0,genInfo.charge); //nsigma(0:nominal,1:up,-1:down), charge
  TVector2 w_p_corr(corrMet*cos(corrMetPhi)+W.lep_pt_corr*cos(W.lep_phi),
      corrMet*sin(corrMetPhi)+W.lep_pt_corr*sin(W.lep_phi));
  W.pt = w_p_corr.Mod();
  W.Met = corrMet;
  W.Met_phi = corrMetPhi;
  W.Mt = CalcMt(
      W.lep_pt_corr, W.lep_phi,
      W.Met, W.Met_phi);
  //}else{
  //  corrMet = W.Met;
  //}
  //
  //cout<<"Met:corrMet "<<Met<<":"<<corrMet<<endl;
  //TODO NNLO Correction
  //for( int ibin(1);ibin<=hNNLOCorr->GetNbinsX();ibin++)
  //{
  //  if(genBeFsrW_pt >= hNNLOCorr->GetBinLowEdge(ibin) &&
  //     genBeFsrW_pt < (hNNLOCorr->GetBinLowEdge(ibin)+hNNLOCorr->GetBinWidth(ibin))
  //     nnlocorr = hNNLOCorr->GetBinContent(ibin);
  //}
  return 0;
}
int Wlnu12LoBase::DumpMETs()
{
  // MET
  //pfMEtTL.SetPxPyPzE(pfMEt_x,pfMEt_y,0,toolbox::pT(pfMEt_x,pfMEt_y));
  //NoPuMEtTL.SetPxPyPzE(NoPuMEt_x,NoPuMEt_y,0,toolbox::pT(NoPuMEt_x,NoPuMEt_y));
  //MVaMEtTL.SetPxPyPzE(MVaMEt_x,MVaMEt_y,0,toolbox::pT(MVaMEt_x,MVaMEt_y));
  //genMEtTrueTL.SetPxPyPzE(genMEtTrue_x,genMEtTrue_y,0,toolbox::pT(genMEtTrue_x,genMEtTrue_y));
  //genMEtCaloTL.SetPxPyPzE(genMEtCalo_x,genMEtCalo_y,0,toolbox::pT(genMEtCalo_x,genMEtCalo_y));
  //genMEtCaloAndNonPromptTL.SetPxPyPzE(genMEtCaloAndNonPrompt_x,genMEtCaloAndNonPrompt_y,0,toolbox::pT(genMEtCaloAndNonPrompt_x,genMEtCaloAndNonPrompt_y));
  return 0;
}
Int_t Wlnu12LoBase::InitVar4Evt()
{
  W_Lept1_pt_Corr.clear();
  // Recoil
  mTTW = 1;
  mVtxVar.nPrim = 0;
  mVtxVar.nGood = 0;
  //cout<<"Wlnu12LoBase::InitVar4Evt ==========================="<<endl;
  W.size = W_pt->size();
  W.pt=0;
  W.Mt=0;
  W.Met=0;
  W.Met_phi=0;
  W.pt_side=0;
  W.Met_side=0;
  W.Mt_side=0;
  W.genIdx=-999;
  W.charge=0;
  W.lep_pt = 0;
  W.lep_pt_corr = 0;
  W.lep_phi = 0;
  W.lep_eta = 0;
  W.lep_etaSC = 0;
  W.Pass=0;
  W.PassSide=0;
    
  Z.pt = 0;
  Z.ptRecoil = 0;
  Z.Pass = 0;
  Z.mass = 0;
  Z.Lep1Pt = 0;
  Z.Lep1Pz = 0;
  Z.Lep1En = 0;
  Z.Lep2Pt = 0;
  Z.Lep2Pz = 0;
  Z.Lep2En = 0;
  Z.Lep1Phi = 0;
  Z.Lep2Phi = 0;
  Z.Lep1etaSC = 0;
  Z.Lep2etaSC = 0;
  
  glbMuChi2=0;
  addLepN=0;corrMet=0;
  smearSF=0;
  scalecorr=0;
  Rcl.u1W=-999;Rcl.u2W=-999;Rcl.u3W=-999;
  Rcl.u1Z=-999;Rcl.u2Z=-999;Rcl.u3Z=-999;
  //genInfo.W_MCtruth = 0;
  genInfo.BornW_pt = 0;
  genInfo.PostW_pt = 0;
  genInfo.BornW_Nu_Cnt = 0;

  return 0;
}
double Wlnu12LoBase::CalcEvtWeight()
{
  if(!RunOnMC){mTTW = 1;return mTTW;}
      //mTTW= LumiWeight*weightin; //weight is right but S8 strange
      //if (weightFSR<0) weightFSR=1.;
      //mTTW= LumiWeight*weightFSR; //weight is right but S8 strange
  mTTW= LumiWeight; //weight is right but S8 strange
  if(AnaChannel == "ElectronHighPU")
  {
    mTTW= LumiWeight*weight;} //reweighting value for S10
  return mTTW;
}

#endif // #ifdef Wlnu12LoBase_cxx


