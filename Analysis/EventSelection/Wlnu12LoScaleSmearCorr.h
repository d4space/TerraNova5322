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
#include <TLorentzVector.h>
#include <TVector2.h>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TMath.h>
#include <vector>

#include <iostream>
#include <fstream>
#include <iomanip>

#include "Math/PtEtaPhiE4D.h"
#include "Math/PtEtaPhiM4D.h"
#include "Math/LorentzVector.h"


typedef ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiM4D<double> > PtEtaPhiMLorentzVectorD;
typedef PtEtaPhiMLorentzVectorD PtEtaPhiMLorentzVector;


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
  int Fill_CorrectedZHisto();
  
  int Write_Histo();
  int Write_ZHisto();


  ofstream Fout;
  TFile *myFile;
  
  
  TH1D*	h1_W_pt;

  TH1D*	h1_Zmass;
  TH1D*	h1_Zmass_BB;
  TH1D*	h1_Zmass_BE;
  TH1D*	h1_Zmass_EE;
  
  TH1D*	h1_ZmassCorr;
  TH1D*	h1_ZmassCorr_BB;
  TH1D*	h1_ZmassCorr_BE;
  TH1D*	h1_ZmassCorr_EE;
  

  TH1D* h1_ZmassDaughEtaEle[ScElCombiBins];
  TH1D* h1_ZmassDaughEtaEleDiag[ScElCombiBinsDiag];
  TH1D* h1_ZmassDaughEtaMu[ScMuCombiBins];
  
 int ZbestSelect();
 //int InitHistogram();

  //Cuts
 
  virtual Int_t    MuonCutZ(int entry);
  virtual Int_t    ElectronCutZ(int entry);
  virtual Int_t    TauCutZ(int entry);

 virtual Int_t    EtaRange(double lep1Eta);
 virtual Int_t    Fill_EleZmassDaughEta(int etaRange1, int etaRange2);
 virtual Int_t    Fill_MuZmassDaughEta(int etaRange1, int etaRange2);
 
 //Corrections on Z
 virtual Double_t    GetScaleCorr(double LepEta);
 virtual Double_t    GetSmearCorr(double LepEta);

  
  // Member variables
  double mNselect4WptBin[NwPtBin];

  int mNZevt;

  //Z boson Variables
  struct Zboson{
    bool Pass;
    int idxBest;
    double Lep1Pt, Lep1Pz, Lep1Phi, Lep1En, Lep1etaSC;
    double Lep2Pt, Lep2Pz, Lep2Phi, Lep2En, Lep2etaSC;
    double mass;
    }Z;
  
    int mZ_size;
    double Zpt,ZptRecoil,MEtZ,noPUMEtZ;//ZptRecoil==Zpt for real but gen dilep for MC

     double Scale_corrZlep1Pt;
     double Scale_corrZlep2Pt;

     double smearSFLep1;
     double smearSFLep2;
     //double eleMass=0.000510998902;
     //double muMass=0.105658389;
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


Int_t Wlnu12LoScaleSmearCorr::MuonCutZ(int i)
{
  if( (*Z_Sign)[i] != 0 ) return -1;
  if( !(*Z_Lept1_isGlobal)[i])return -1;
  if( !(*Z_Lept2_isGlobal)[i])return -1;
  if((*Z_Lept1_pt)[i] < 20) return -1;//trigger SingleMu15 but we use 25 for Wpt
  if(fabs((*Z_Lept1_eta)[i])>2.1) return -1;
  if(fabs((*Z_Lept2_eta)[i])>2.1) return -1;
  if( (*Z_Lept1_globalNormChi2)[i]<0 || (*Z_Lept1_globalNormChi2)[i] >= 10) return -1;
  if( (*Z_Lept2_globalNormChi2)[i]<0 || (*Z_Lept2_globalNormChi2)[i] >= 10) return -1;
  if( (*Z_Lept1_muonHits)[i] <1) return -1;
  if( (*Z_Lept2_muonHits)[i] <1) return -1;
  if( (*Z_Lept1_matchStations)[i] <2 ) return -1;
  if( (*Z_Lept2_matchStations)[i] <2 ) return -1;
  if( (*Z_Lept1_trkLayers)[i] <6 )return -1;
  if( (*Z_Lept2_trkLayers)[i] <6 )return -1;
  if( (*Z_Lept1_pixelHits)[i] <1 )return -1;
  if( (*Z_Lept2_pixelHits)[i] <1 )return -1;
  if( fabs( (*Z_Lept1_dB)[i]) >0.02 )return -1;
  if( fabs( (*Z_Lept2_dB)[i]) >0.02 )return -1;
  if( fabs( (*Z_Lept1_dz)[i]) >0.5 )return -1;
  if( fabs( (*Z_Lept2_dz)[i]) >0.5 )return -1;
  double betaCor04= max(0.0,(*Z_Lept1_nhIso04)[i]+(*Z_Lept1_phIso04)[i]-0.5*(*Z_Lept1_pcIso04)[i]);
  if( ((*Z_Lept1_chIso04)[i]+betaCor04)/(*Z_Lept1_pt)[i] > 0.12) return -1; //Signal Band
  betaCor04= max(0.0,(*Z_Lept2_nhIso04)[i]+(*Z_Lept2_phIso04)[i]-0.5*(*Z_Lept2_pcIso04)[i]);
  if( ((*Z_Lept2_chIso04)[i]+betaCor04)/(*Z_Lept2_pt)[i] > 0.12) return -1; //Signal Band

  return 1;
}

Int_t Wlnu12LoScaleSmearCorr::ElectronCutZ(int i)
{
     if( (*Z_Sign)[i] != 0 ) return -1;
     if((*Z_Lept1_pt)[i] < 25) return -1;
     if(fabs((*Z_Lept1_etaSC)[i])>2.5) return -1;
     if(fabs((*Z_Lept2_etaSC)[i])>2.5) return -1;

     if(fabs((*Z_Lept1_etaSC)[i])>1.4442 && fabs((*Z_Lept1_etaSC)[i])<1.566)return -1;
     if(fabs((*Z_Lept2_etaSC)[i])>1.4442 && fabs((*Z_Lept2_etaSC)[i])<1.566)return -1;
     
     if( fabs( (*Z_Lept1_etaSC)[i]) < 1.4442)
     {
         if( (*Z_Lept1_sigmaIEtaIEta)[i] > 0.01 ) return -1;
     }else{
         if( (*Z_Lept1_sigmaIEtaIEta)[i] > 0.03 ) return -1;
     }
     if( fabs( (*Z_Lept2_etaSC)[i]) < 1.4442)
     {
         if( (*Z_Lept2_sigmaIEtaIEta)[i] > 0.01 ) return -1;
     }else{
         if( (*Z_Lept2_sigmaIEtaIEta)[i] > 0.03 ) return -1;
     }
     
     if( fabs( (*Z_Lept1_etaSC)[i]) < 1.4442)
     {
         if( fabs((*Z_Lept1_dEtaIn)[i]) >  0.004 ) return -1;
     }else{
         if( fabs((*Z_Lept1_dEtaIn)[i])  >   0.007 ) return -1;
     }
     if( fabs( (*Z_Lept2_etaSC)[i]) < 1.4442)
     {
         if( fabs((*Z_Lept2_dEtaIn)[i]) >  0.004 ) return -1;
     }else{
         if( fabs((*Z_Lept2_dEtaIn)[i])  >   0.007 ) return -1;
     }
     
     if( fabs( (*Z_Lept1_etaSC)[i]) < 1.4442)
     {
         if( fabs((*Z_Lept1_dPhiIn)[i])  > 0.06 ) return -1;
     }else {
         if( fabs((*Z_Lept1_dPhiIn)[i])  > 0.03 ) return -1;
     }
     if( fabs( (*Z_Lept2_etaSC)[i]) < 1.4442)
     {
         if( fabs((*Z_Lept2_dPhiIn)[i])  > 0.06 ) return -1;
     } else {
         if( fabs((*Z_Lept2_dPhiIn)[i])  > 0.03 ) return -1;
     }
     
     if( fabs( (*Z_Lept1_etaSC)[i]) < 1.4442)
     {
         if( (*Z_Lept1_HoverE)[i] > 0.12 ) return -1;
     }else {
         if( (*Z_Lept1_HoverE)[i] > 0.10 ) return -1;
     }
     if( fabs( (*Z_Lept2_etaSC)[i]) < 1.4442)
     {
         if( (*Z_Lept2_HoverE)[i] > 0.12 ) return -1;
     }else {
         if( (*Z_Lept2_HoverE)[i] > 0.10 ) return -1;
     }
     
     if( fabs( (*Z_Lept1_etaSC)[i]) < 1.4442)
     {
         if( fabs((*Z_Lept1_dxy)[i]) > 0.02 ) return -1;
     }else {
         if( fabs((*Z_Lept1_dxy)[i]) > 0.02 ) return -1;
     }
     if( fabs( (*Z_Lept2_etaSC)[i]) < 1.4442)
     {
         if( fabs((*Z_Lept2_dxy)[i]) > 0.02 ) return -1;
     }else {
         if( fabs((*Z_Lept2_dxy)[i]) > 0.02 ) return -1;
     }
     
     if( fabs( (*Z_Lept1_etaSC)[i]) < 1.4442)
     {
         if( fabs((*Z_Lept1_dz)[i]) > 0.1 ) return -1;
     }else{
         if( fabs((*Z_Lept1_dz)[i]) > 0.1 ) return -1;
     }
     if( fabs( (*Z_Lept2_etaSC)[i]) < 1.4442)
     {
         if( fabs((*Z_Lept2_dz)[i]) > 0.1 ) return -1;
     }else{
         if( fabs((*Z_Lept2_dz)[i]) > 0.1 ) return -1;
     }
    
     if( fabs( (*Z_Lept1_etaSC)[i]) < 1.4442)
     {
         if( fabs((*Z_Lept1_InvEminusInvP)[i]) > 0.05 ) return -1;
     }else{
         if( fabs((*Z_Lept1_InvEminusInvP)[i]) > 0.05) return -1;
     }
     if( fabs( (*Z_Lept2_etaSC)[i]) < 1.4442)
     {
         if( fabs((*Z_Lept2_InvEminusInvP)[i]) > 0.05 ) return -1;
     }else{
         if( fabs((*Z_Lept2_InvEminusInvP)[i]) > 0.05) return -1;
     }
     
     if( fabs( (*Z_Lept1_etaSC)[i]) < 1.4442)
     {
         if( fabs((*Z_Lept1_mHits)[i]) > 1 ) return -1;
     }else{
         if( fabs((*Z_Lept1_mHits)[i]) > 1) return -1;
     }
     
     if( fabs( (*Z_Lept2_etaSC)[i]) < 1.4442)
     {
         if( fabs((*Z_Lept2_mHits)[i]) > 1 ) return -1;
     }else{
         if( fabs((*Z_Lept2_mHits)[i]) > 1) return -1;
     }

     if( (*Z_Lept1_hasConversion)[i] ) return -1;
     if( (*Z_Lept2_hasConversion)[i] ) return -1;
     if( (*Z_Lept1_relIsoRho03)[i] > 0.15 ) return -1;
     if( (*Z_Lept2_relIsoRho03)[i] > 0.15 ) return -1;

  return 1;
}

Int_t Wlnu12LoScaleSmearCorr::TauCutZ(int i)
{
  if( (*Z_Sign)[i] != 0 ) return -1;
  //if( (*Z_Lept1_MedComIsoDelBetCorr3Hits)[i] < 0.5 )return -1;
  //if( (*Z_Lept2_MedComIsoDelBetCorr3Hits)[i] < 0.5 )return -1;
  //if( (*Z_Lept1_decModFind)[i] < 0.5 )return -1;
  //if( (*Z_Lept2_decModFind)[i] < 0.5 )return -1;
  if( fabs((*Z_Lept1_eta)[i]) > 2.3 )return -1;
  if( fabs((*Z_Lept2_eta)[i]) > 2.3 )return -1;
  if( fabs((*Z_Lept1_pt)[i]) < 20 )return -1;
  if( fabs((*Z_Lept2_pt)[i]) < 20 )return -1;
  return 1;
}



#endif // #ifdef Wlnu12LoScaleSmearCorr_cxx


