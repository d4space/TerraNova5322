//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed May 16 17:32:24 2012 by ROOT version 5.32/00
// from TChain ZZ4LBase/tree/
//////////////////////////////////////////////////////////
//$Log: ZZ4LBase.h,v $
//Revision 1.13  2013/09/13 00:09:32  salee
//*** empty log message ***
//

#ifndef ZZ4LBase_h
#define ZZ4LBase_h

#include "WMuons.h"
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1D.h>
#include <TMath.h>
#include <TLorentzVector.h>
#include <TRandom.h>

// Header file for the classes stored in the TTree if any.
#include <vector>

#include <iostream>
#include <fstream>
#include <iomanip>
#include "../Utils/const.h"
#include "../Utils/RecoilCorrector.hh"//class to handle recoil corrections for MET
#include "../Utils/MyTools.hh"
#include "ZZ4LNT.h"


#include "Math/PtEtaPhiE4D.h"
#include "Math/PtEtaPhiM4D.h"
#include "Math/LorentzVector.h"

typedef ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiM4D<double> > PtEtaPhiMLorentzVectorD;
typedef PtEtaPhiMLorentzVectorD PtEtaPhiMLorentzVector;


// Fixed size dimensions of array or collections stored in the TTree if any.
class ZZ4LBase: public ZZ4LNT {
public :
  //WMuons	wMuons;

   double	LumiWeight;
     
   ZZ4LBase(TTree *tree=0,TTree *MuonTree=0, double weight=1,
       TString OutNameBase = "Haha",TString Mode="analysis",
       TString AnaChannel ="Muon",double WCHARGE=0, bool runOnMC=true, int etaRange_=-999);

   virtual ~ZZ4LBase();
   virtual Int_t    TauCut(int entry);
   virtual Int_t    MuonCut(int entry);
   virtual Int_t    MuonCutSide(int entry);
   virtual Int_t    AddMuonCut(int entry);
   virtual Int_t    ElectronCut(int entry);
   virtual Int_t    ElectronCutHighPU(int entry);
   virtual Int_t    ElectronCutSide(int entry);
   virtual Int_t    ElectronCutSideHighPU(int entry);
   virtual Int_t    AddElectronCut(int entry);
   virtual Int_t    AddElectronCutHighPU(int entry);
   virtual Int_t    MuonCutZ(int entry);
   virtual Int_t    TauCutZ(int entry);
   virtual Int_t    ElectronCutZ(int entry);
   virtual Int_t    ElectronCutZHighPU(int entry);
   virtual Int_t    EtaRange(double lep1Eta,double lep2Eta);
   virtual Int_t    EtaRange(double lep1Eta);

  virtual Double_t    ElePlusEffiCorrection(double elePt, double eleEtaSC);
  virtual Double_t    EleMinusEffiCorrection(double elePt, double eleEtaSC);
  virtual Double_t    MuonPlusEffiCorrection(double muonPt, double muonEta);
  virtual Double_t    MuonMinusEffiCorrection(double muonPt, double muonEta);
  
  virtual Double_t    EleScaleRD(double ele_etaSC);
  virtual Double_t    EleSmearMC(double ele_etaSC);
  virtual Double_t    MuonSmearMC(double mu_eta);
   
   virtual Int_t    DumpTruthGenInfo(int i);
   virtual Int_t    FillAcceptInfo();
   virtual Int_t    DoRecoilCorr();
   virtual Int_t    InitVar4Evt();
   virtual Int_t    DumpMETs();
   virtual Int_t    DoScaleSmearScan(
    double zlep1Pt,double zlep1Pz,double zlep1En,double zlep1Phi,
    double zlep2Pt,double zlep2Pz,double zlep2En,double zlep2Phi, double TTW);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   //   virtual void     Loop_Recoil();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
protected:
  bool Debug;
  int InitVar();
  int CheckChannel();
  int TriggerCut();
  double CalcEvtWeight(){mTTW =1; return mTTW;}
  //------------------
  // Member Variables
  //------------------
  // Miscal
  char histName[30];
  TString mResultDir;
  TLorentzVector pfMEtTL, NoPuMEtTL, MVaMEtTL, genMEtTrueTL, genMEtCaloTL, genMEtCaloAndNonPromptTL;
  int Ntries;
  int evtCnt;
  int mNWevt;
  int mNZevt;
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

  //MisChargeStudy
 // double ZLep1eta;
 // double ZLep2eta;
 // double ZLep1Requirement;
 // double ZLep2Requirement;
 // double ZLep1charge;
 // double ZLep2charge;

  int ETARANGE;
  double diLeptVtxProb;
  //Lepton Variables
  double lep_pt,addLepN,lep_pt_corr;
  double scalecorr,scalecorr1,scalecorr2,smearcorr,smearcorr1,smearcorr2,newZlep1Pt, newZlep2Pt;
  double elemass,muonmass, corr1, corr2;
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

#ifdef ZZ4LBase_cxx

void ZZ4LBase::Init(TTree *tree)
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
  ZZ4LNT::Init(tree);

   mEffSf = 1;

   Notify();
}
ZZ4LBase::ZZ4LBase(TTree *ZZ4LBaseTree,TTree *WLepTree, double lumiweight,
       TString OutNameBase_, TString mode_, TString AnaChannel_,
       double Wcharge, bool runOnMC, int etaRange_)
{
  fChain=0;
    // if parameter tree is not specified (or zero), connect the file
    // // used to generate this class and read the Tree.
   cout<<"ZZ4LBase constructor"<<endl;
   cout<<"initialization for bins"<<endl;
   //{0,2.5,5,7.5,10,12.5,15,17.5,20,30,40,50,70,90,150,190,250,600}; //Zpt Bins
   //0,4,8,15,23,30,38,46,55,65,75,85,95,107,120,132,145,160,175,192,210,250,300 Atlas 22 bins
   //{0,8,23,38,55,75,95,120,145,175,210,300};//Atlas Unfolding bin
   //
   //ZpT bins
  //Bins[0]=     0.;
  //Bins[1]=     2.5;
  //Bins[2]=     5;
  //Bins[3]=     7.5;
  //Bins[4]=     10;
  //Bins[5]=     12.5;
  //Bins[6]=     15;
  //Bins[7]=     17.5;
  //Bins[8]=     20.;
  //Bins[9]=     30.;
  //Bins[10]=    40.;
  //Bins[11]=    50.;
  //Bins[12]=    70.;
  //Bins[13]=    90.;
  //Bins[14]=    110.;
  //Bins[15]=    150.;
  //Bins[16]=    190.;
  //Bins[17]=    250.;
  //Bins[18]=    600.;

   if (ZZ4LBaseTree == 0 ) {
     cout<<"Usage: ZZ4LBase(TTree*... ) "<<endl;
     exit(-1);
   }else{
     cout<<"ZZ4LBase.h: initializing the trees"<<endl;
   LumiWeight = lumiweight;
   cout<<"Input Value of Lumiweight = "<<lumiweight<<" Initialized as = "<<LumiWeight<<endl;
   OutNameBase = OutNameBase_;
   Mode = mode_;
   AnaChannel = AnaChannel_;
   WCHARGE = Wcharge;
   RunOnMC = runOnMC;
   ETARANGE = etaRange_;
   Init(ZZ4LBaseTree);
   //wMuons.Init(WLepTree);
   }
   InitVar();
}


   ZZ4LBase::~ZZ4LBase()
   {
     if (!fChain) return;
     delete fChain->GetCurrentFile();
   }

   Int_t ZZ4LBase::GetEntry(Long64_t entry)
   {
     // Read contents of entry.
     if (!fChain) return 0;
     return fChain->GetEntry(entry);
   }

   Long64_t ZZ4LBase::LoadTree(Long64_t entry)
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
   
   Bool_t ZZ4LBase::Notify()
   {
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

     return kTRUE;
   }


   void ZZ4LBase::Show(Long64_t entry)
   {
     // Print contents of entry.
     // If entry is not specified, print current entry
     if (!fChain) return;
     fChain->Show(entry);
   }

// Electron effi correction
Double_t ZZ4LBase::ElePlusEffiCorrection(double elePt, double eleEtaSC)
{
  if (elePt>25. && elePt <=35.)
  {
    if (eleEtaSC >-2.5 && eleEtaSC <= -1.5 )  {return 0.9495;}
    if (eleEtaSC >-1.5 && eleEtaSC <= -0.5 )  {return 0.9525;}
    if (eleEtaSC >-0.5 && eleEtaSC <= 0.0 )   {return 1.0784;}
    if (eleEtaSC > 0.0 && eleEtaSC <= 0.5 )   {return 0.8960;}
    if (eleEtaSC > 0.5 && eleEtaSC <= 1.5 )   {return 0.9862;}
    if (eleEtaSC > 1.5 && eleEtaSC < 2.5 )   {return 1.0142;}
  }else if (elePt>35. && elePt <=50.)
  {
    if (eleEtaSC >-2.5 && eleEtaSC <= -1.5 )  {return 1.0302;}
    if (eleEtaSC >-1.5 && eleEtaSC <= -0.5 )  {return 0.9831;}
    if (eleEtaSC >-0.5 && eleEtaSC <= 0.0 )   {return 0.9551;}
    if (eleEtaSC > 0.0 && eleEtaSC <= 0.5 )   {return 0.9446;}
    if (eleEtaSC > 0.5 && eleEtaSC <= 1.5 )   {return 0.9519;}
    if (eleEtaSC > 1.5 && eleEtaSC < 2.5 )   {return 1.0399;}
  }else if (elePt>50. )
  {
    if (eleEtaSC >-2.5 && eleEtaSC <= -1.5 )  {return 1.1285;}
    if (eleEtaSC >-1.5 && eleEtaSC <= -0.5 )  {return 0.9445;}
    if (eleEtaSC >-0.5 && eleEtaSC <= 0.0 )   {return 1.0736;}
    if (eleEtaSC > 0.0 && eleEtaSC <= 0.5 )   {return 0.9983;}
    if (eleEtaSC > 0.5 && eleEtaSC <= 1.5 )   {return 0.9693;}
    if (eleEtaSC > 1.5 && eleEtaSC < 2.5 )   {return 1.0308;}
  }
}
Double_t ZZ4LBase::EleMinusEffiCorrection(double elePt, double eleEtaSC)
{
  if (elePt>25. && elePt <=35.)
  {
    if (eleEtaSC >-2.5 && eleEtaSC <= -1.5 )  {return 1.0956;}
    if (eleEtaSC >-1.5 && eleEtaSC <= -0.5 )  {return 1.0238;}
    if (eleEtaSC >-0.5 && eleEtaSC <= 0.0 )   {return 1.0202;}
    if (eleEtaSC > 0.0 && eleEtaSC <= 0.5 )   {return 0.8692;}
    if (eleEtaSC > 0.5 && eleEtaSC <= 1.5 )   {return 1.0110;}
    if (eleEtaSC > 1.5 && eleEtaSC < 2.5 )   {return 1.1316;}
  }else if (elePt>35. && elePt <=50.)
  {
    if (eleEtaSC >-2.5 && eleEtaSC <= -1.5 )  {return 0.9949;}
    if (eleEtaSC >-1.5 && eleEtaSC <= -0.5 )  {return 0.9815;}
    if (eleEtaSC >-0.5 && eleEtaSC <= 0.0 )   {return 0.9563;}
    if (eleEtaSC > 0.0 && eleEtaSC <= 0.5 )   {return 0.9306;}
    if (eleEtaSC > 0.5 && eleEtaSC <= 1.5 )   {return 0.9892;}
    if (eleEtaSC > 1.5 && eleEtaSC < 2.5 )   {return 0.9255;}
  }else if (elePt>50. )
  {
    if (eleEtaSC >-2.5 && eleEtaSC <= -1.5 )  {return 0.9441;}
    if (eleEtaSC >-1.5 && eleEtaSC <= -0.5 )  {return 0.9553;}
    if (eleEtaSC >-0.5 && eleEtaSC <= 0.0 )   {return 0.9645;}
    if (eleEtaSC > 0.0 && eleEtaSC <= 0.5 )   {return 0.9695;}
    if (eleEtaSC > 0.5 && eleEtaSC <= 1.5 )   {return 0.9719;}
    if (eleEtaSC > 1.5 && eleEtaSC < 2.5 )   {return 0.8826;}
  }
}

// Muon effi correction
Double_t ZZ4LBase::MuonPlusEffiCorrection(double muonPt, double muonEta)
{
  if (muonPt>20. && muonPt <=40.)
  {
    if (muonEta >-2.1 && muonEta <= -1.2 )  {return 0.9534;}
    if (muonEta >-1.2 && muonEta <= -0.8 )  {return 1.0644;}
    if (muonEta >-0.8 && muonEta <= 0.0 )   {return 0.9775;}
    if (muonEta > 0.0 && muonEta <= 0.8 )   {return 0.9822;}
    if (muonEta > 0.8 && muonEta <= 1.2 )   {return 0.9064;}
    if (muonEta > 1.2 && muonEta < 2.1 )   {return 1.0013;}
  }else if (muonPt>40. && muonPt <=55.)
  {
    if (muonEta >-2.1 && muonEta <= -1.2 )  {return 0.9639;}
    if (muonEta >-1.2 && muonEta <= -0.8 )  {return 0.9755;}
    if (muonEta >-0.8 && muonEta <= 0.0 )   {return 0.9843;}
    if (muonEta > 0.0 && muonEta <= 0.8 )   {return 0.9837;}
    if (muonEta > 0.8 && muonEta <= 1.2 )   {return 0.9741;}
    if (muonEta > 1.2 && muonEta < 2.1 )   {return 0.9893;}
  }else if (muonPt>55. )
  {
    if (muonEta >-2.1 && muonEta <= -1.2 )  {return 1.0554;}
    if (muonEta >-1.2 && muonEta <= -0.8 )  {return 0.9995;}
    if (muonEta >-0.8 && muonEta <= 0.0 )   {return 0.9845;}
    if (muonEta > 0.0 && muonEta <= 0.8 )   {return 0.9923;}
    if (muonEta > 0.8 && muonEta <= 1.2 )   {return 1.0627;}
    if (muonEta > 1.2 && muonEta < 2.1 )   {return 1.0705;}
  }
}

Double_t ZZ4LBase::MuonMinusEffiCorrection(double muonPt, double muonEta)
{
  if (muonPt>20. && muonPt <=40.)
  {
    if (muonEta >-2.1 && muonEta <= -1.2 )  {return 0.9813;}
    if (muonEta >-1.2 && muonEta <= -0.8 )  {return 0.9363;}
    if (muonEta >-0.8 && muonEta <= 0.0 )   {return 0.9594;}
    if (muonEta > 0.0 && muonEta <= 0.8 )   {return 0.9816;}
    if (muonEta > 0.8 && muonEta <= 1.2 )   {return 0.9346;}
    if (muonEta > 1.2 && muonEta < 2.1 )   {return 1.0084;}
  }else if (muonPt>40. && muonPt <=55.)
  {
    if (muonEta >-2.1 && muonEta <= -1.2 )  {return 0.9718;}
    if (muonEta >-1.2 && muonEta <= -0.8 )  {return 0.9700;}
    if (muonEta >-0.8 && muonEta <= 0.0 )   {return 0.9803;}
    if (muonEta > 0.0 && muonEta <= 0.8 )   {return 0.9687;}
    if (muonEta > 0.8 && muonEta <= 1.2 )   {return 0.9732;}
    if (muonEta > 1.2 && muonEta < 2.1 )   {return 0.9731;}
  }else if (muonPt>55. )
  {
    if (muonEta >-2.1 && muonEta <= -1.2 )  {return 0.9412;}
    if (muonEta >-1.2 && muonEta <= -0.8 )  {return 0.9827;}
    if (muonEta >-0.8 && muonEta <= 0.0 )   {return 0.9988;}
    if (muonEta > 0.0 && muonEta <= 0.8 )   {return 0.9851;}
    if (muonEta > 0.8 && muonEta <= 1.2 )   {return 0.9435;}
    if (muonEta > 1.2 && muonEta < 2.1 )   {return 0.9206;}
  }
}



   /// Scale Smear corrections
   Double_t ZZ4LBase::EleScaleRD(double ele_etaSC)
   {
     if(fabs(ele_etaSC) >= 0.0   && fabs(ele_etaSC) < 0.4) {return 0.999315  ;}
     if(fabs(ele_etaSC) >= 0.4   && fabs(ele_etaSC) < 0.8) {return 1.00358   ;}
     if(fabs(ele_etaSC) >= 0.8   && fabs(ele_etaSC) < 1.2) {return 1.00325   ;}
     if(fabs(ele_etaSC) >= 1.2   && fabs(ele_etaSC) < 1.4442) {return 1.00244 ;}
     if(fabs(ele_etaSC) >= 1.566 && fabs(ele_etaSC) < 2.0) {return 1.0067   ; }
     if(fabs(ele_etaSC) >= 2.0   && fabs(ele_etaSC) < 2.5) {return 0.992737  ; }
   }

   Double_t ZZ4LBase::EleSmearMC(double ele_etaSC)
   {
     if(fabs(ele_etaSC) >= 0.0   && fabs(ele_etaSC) < 0.4) {return 0.382443   ;}
     if(fabs(ele_etaSC) >= 0.4   && fabs(ele_etaSC) < 0.8) {return 0.356171   ;}
     if(fabs(ele_etaSC) >= 0.8   && fabs(ele_etaSC) < 1.2) {return 0.559123   ;}
     if(fabs(ele_etaSC) >= 1.2   && fabs(ele_etaSC) < 1.4442) {return 0.01     ;}
     if(fabs(ele_etaSC) >= 1.566 && fabs(ele_etaSC) < 2.0) {return 0.972944    ;}
     if(fabs(ele_etaSC) >= 2.0   && fabs(ele_etaSC) < 2.5) {return 1.84788    ;}
   }

   Double_t ZZ4LBase::MuonSmearMC(double mu_eta)
   {
     if(fabs(mu_eta) >= 0.0   && fabs(mu_eta) < 0.4) { return 0.01   ;}
     if(fabs(mu_eta) >= 0.4   && fabs(mu_eta) < 0.8) { return 0.381253    ;}
     if(fabs(mu_eta) >= 0.8   && fabs(mu_eta) < 1.2) { return 0.743902     ;}
     if(fabs(mu_eta) >= 1.2   && fabs(mu_eta) < 1.6) { return 0.637325     ;}
     if(fabs(mu_eta) >= 1.6   && fabs(mu_eta) < 2.1) { return 0.611946     ;}
   }

Int_t ZZ4LBase::TauCut(int i)
{
  //if( (*Z_Lept1_MedComIsoDelBetCorr3Hits)[i] < 0.5 )return -1;
  //if( (*Z_Lept1_decModFind)[i] < 0.5 )return -1;
  if( fabs((*Z_Lept1_eta)[i]) > 2.3 )return -1;
  if( fabs((*Z_Lept1_pt)[i]) < 20 )return -1;
  return 1;
}

Int_t ZZ4LBase::MuonCut(int i)
{
  if( !(*Z_Lept1_isGlobal)[i])return -1;
  if((*Z_Lept1_pt)[i] < 20) return -1;
  //if((*Z_Lept1_pt)[i] < 25) return -1;

  //MC Smear Correction
  if(Mode == "AllCorrectionsMC" || Mode == "Unfold")
  {
    smearcorr= MuonSmearMC((*Z_Lept1_eta)[i]);
    PtEtaPhiMLorentzVector Wmu_4( (*Z_Lept1_pt)[i],(*Z_Lept1_eta)[i],(*Z_Lept1_phi)[i],0.1056);
    corr1 = gRandom->Gaus(Wmu_4.E(), smearcorr)/Wmu_4.E();
    Wmu_4=corr1*Wmu_4;
  }

  if(fabs((*Z_Lept1_eta)[i])>2.1) return -1;
  if( (*Z_Lept1_globalNormChi2)[i]<0 || (*Z_Lept1_globalNormChi2)[i] >= 10) return -1;
  if( (*Z_Lept1_muonHits)[i] <1) return -1;
  if( (*Z_Lept1_matchStations)[i] <2 ) return -1;
  if( (*Z_Lept1_trkLayers)[i] <6 )return -1;
  if( (*Z_Lept1_pixelHits)[i] <1 )return -1;
  if( fabs( (*Z_Lept1_dB)[i]) >0.02 )return -1;
  if( fabs( (*Z_Lept1_dz)[i]) >0.5 )return -1;
  //if( ( (*Z_Lept1_nhIso04)[i]+(*Z_Lept1_chIso04)[i]+(*Z_Lept1_phIso04)[i])/(*Z_Lept1_pt)[i] > 0.12) return -1;
  double betaCor04= max(0.0,(*Z_Lept1_nhIso04)[i]+(*Z_Lept1_phIso04)[i]-0.5*(*Z_Lept1_pcIso04)[i]);
  if( ((*Z_Lept1_chIso04)[i]+betaCor04)/(*Z_Lept1_pt)[i] > 0.12) return -1; //Signal Band   // use this line to get n.of.events in AB area in  ABCD method


  // uncomment next line (Sideband)  to get n.of.events in DC area in  ABCD method
  //  if( ((*Z_Lept1_chIso04)[i]+betaCor04)/(*Z_Lept1_pt)[i] < 0.3 || ((*Z_Lept1_chIso04)[i]+betaCor04)/(*Z_Lept1_pt)[i] > 0.5) return -1; //Side Band

  
  
  //if( (*W_Neut_pt)[i] < 14 ) return -1;
  //if( (*W_Mt)[i] < 30 ) return -1;
  //if( (*W_Neut_pt)[i] < 25 ) return -1;
  //if( (*W_Mt)[i] < 40 ) return -1;

  return 1;
}

Int_t ZZ4LBase::MuonCutSide(int i)
{
  if( !(*Z_Lept1_isGlobal)[i])return -1;
  if((*Z_Lept1_pt)[i] < 20) return -1;
  //if((*Z_Lept1_pt)[i] < 25) return -1;
     
  //MC Smear Correction
  if(Mode == "AllCorrectionsMC" || Mode == "Unfold")
  {
    smearcorr= MuonSmearMC((*Z_Lept1_eta)[i]);
    PtEtaPhiMLorentzVector Wmu_4( (*Z_Lept1_pt)[i],(*Z_Lept1_eta)[i],(*Z_Lept1_phi)[i],0.1056);
    corr1 = gRandom->Gaus(Wmu_4.E(), smearcorr)/Wmu_4.E();
    Wmu_4=corr1*Wmu_4;
  }
     
  if(fabs((*Z_Lept1_eta)[i])>2.1) return -1;
  if( (*Z_Lept1_globalNormChi2)[i]<0 || (*Z_Lept1_globalNormChi2)[i] >= 10) return -1;
  if( (*Z_Lept1_muonHits)[i] <1) return -1;
  if( (*Z_Lept1_matchStations)[i] <2 ) return -1;
  if( (*Z_Lept1_trkLayers)[i] <6 )return -1;
  if( (*Z_Lept1_pixelHits)[i] <1 )return -1;
  if( fabs( (*Z_Lept1_dB)[i]) >0.02 )return -1;
  if( fabs( (*Z_Lept1_dz)[i]) >0.5 )return -1;
  double betaCor04= max(0.0,(*Z_Lept1_nhIso04)[i]+(*Z_Lept1_phIso04)[i]-0.5*(*Z_Lept1_pcIso04)[i]);
  if( ((*Z_Lept1_chIso04)[i]+betaCor04)/(*Z_Lept1_pt)[i] < 0.3 || ((*Z_Lept1_chIso04)[i]+betaCor04)/(*Z_Lept1_pt)[i] > 0.5) return -1; //Side Band

  return 1;
}

Int_t ZZ4LBase::AddMuonCut(int i)
{
  if( !(*Z_Lept1_isTrker)[i] || !(*Z_Lept1_isGlobal)[i]) return -1; //Signal Band only. For Side Band comment this line.
  if((*Z_Lept1_pt)[i] <= 10) return -1;

  //MC Smear Correction
  if(Mode == "AllCorrectionsMC" || Mode == "Unfold")
  {
    smearcorr= MuonSmearMC((*Z_Lept1_eta)[i]);
    PtEtaPhiMLorentzVector Wmu_4( (*Z_Lept1_pt)[i],(*Z_Lept1_eta)[i],(*Z_Lept1_phi)[i],0.1056);
    corr1 = gRandom->Gaus(Wmu_4.E(), smearcorr)/Wmu_4.E();
    Wmu_4=corr1*Wmu_4;
  }

  if(fabs((*Z_Lept1_eta)[i])>=2.4) return -1;
  double betaCor04= max(0.0,(*Z_Lept1_nhIso04)[i]+(*Z_Lept1_phIso04)[i]-0.5*(*Z_Lept1_pcIso04)[i]);
  if( ((*Z_Lept1_chIso04)[i]+betaCor04)/(*Z_Lept1_pt)[i] > 0.20) return -1;
  return 1;
}

   Int_t ZZ4LBase::ElectronCut(int i)
   {
     //RD Scale Correction
     if(Mode == "AllCorrectionsRD")
     {
       scalecorr=EleScaleRD((*Z_Lept1_etaSC)[i]);
       (*Z_Lept1_pt)[i]= scalecorr*(*Z_Lept1_pt)[i];
       PtEtaPhiMLorentzVector WeleRD_4( (*Z_Lept1_pt)[i],(*Z_Lept1_etaSC)[i],(*Z_Lept1_phi)[i],0.000511);
       if(fabs( (*Z_Lept1_pt)[i]) < 25) return -1;
     }else{
       if((*Z_Lept1_pt)[i] < 25) return -1;
     }

     //MC Smear Correction
     if(Mode == "AllCorrectionsMC" || Mode == "Unfold")
     {
       if((*Z_Lept1_pt)[i] < 25) return -1;
       smearcorr=EleSmearMC((*Z_Lept1_etaSC)[i]);
       PtEtaPhiMLorentzVector WeleMC_4( (*Z_Lept1_pt)[i],(*Z_Lept1_etaSC)[i],(*Z_Lept1_phi)[i],0.000511);
       corr1 = gRandom->Gaus(WeleMC_4.E(), smearcorr)/WeleMC_4.E();
       WeleMC_4=corr1*WeleMC_4;
     }else{
       if((*Z_Lept1_pt)[i] < 25) return -1;
     }

     
     if(fabs((*Z_Lept1_etaSC)[i])>2.5) return -1;
     //if(fabs((*Z_Lept1_etaSC)[i])>2.1) return -1;
     //W/Z
     if(fabs((*Z_Lept1_etaSC)[i])>1.4442 && fabs((*Z_Lept1_etaSC)[i])<1.566)return -1;
     //if(fabs((*Z_Lept1_etaSC)[i])>1.47 && fabs((*Z_Lept1_etaSC)[i])<1.566)return -1;
     
     if( fabs( (*Z_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept1_etaSC)[i]) < 1.47)
     {
	 if( (*Z_Lept1_sigmaIEtaIEta)[i] > 0.01 ) return -1; // use this line to get n.of.events in AB area in  ABCD method
	 //if( (*Z_Lept1_sigmaIEtaIEta)[i] > 0.01 ) return -1; // use this line to get n.of.events in DC area in  ABCD method
     } else{
	 if( (*Z_Lept1_sigmaIEtaIEta)[i] > 0.03 ) return -1;   // use this line to get n.of.events in AB area in  ABCD method
	 //if( (*Z_Lept1_sigmaIEtaIEta)[i] > 0.03 ) return -1; // use this line to get n.of.events in DC area in  ABCD method
     }

     if( fabs( (*Z_Lept1_etaSC)[i]) < 1.4442)
         //if( fabs( (*Z_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs((*Z_Lept1_dEtaIn)[i]) >  0.004 ) return -1;
     } else{
	 if( fabs((*Z_Lept1_dEtaIn)[i])  >   0.007 ) return -1;
     }
     
     if( fabs( (*Z_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs((*Z_Lept1_dPhiIn)[i])  > 0.06 ) return -1;
     } else{
	 if( fabs((*Z_Lept1_dPhiIn)[i])  > 0.03 ) return -1;
     }

     if( fabs( (*Z_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept1_etaSC)[i]) < 1.47)
     {
	 if( (*Z_Lept1_HoverE)[i] > 0.12 ) return -1;
     } else{
	 if( (*Z_Lept1_HoverE)[i] > 0.10 ) return -1;
     }

     if( fabs( (*Z_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs((*Z_Lept1_dxy)[i]) > 0.02 ) return -1;
     } else{
	 if( fabs((*Z_Lept1_dxy)[i]) > 0.02 ) return -1;
     }

     if( fabs( (*Z_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs((*Z_Lept1_dz)[i]) > 0.1 ) return -1;
     } else{
	 if( fabs((*Z_Lept1_dz)[i]) > 0.1 ) return -1;
     }
     if( fabs( (*Z_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs((*Z_Lept1_InvEminusInvP)[i]) > 0.05 ) return -1;
     }else{
	 if( fabs((*Z_Lept1_InvEminusInvP)[i]) > 0.05) return -1;
     }

     if( fabs( (*Z_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs((*Z_Lept1_mHits)[i]) > 1 ) return -1;
     } else{
	 if( fabs((*Z_Lept1_mHits)[i]) > 1) return -1;
     }
 
     if( (*Z_Lept1_hasConversion)[i] ) return -1;
     if( (*Z_Lept1_relIsoRho03)[i] > 0.15 ) return -1;

     //       if( (*W_Neut_pt)[i] < 25 ) return -1;
     //          if( (*W_Mt)[i] < 40 ) return -1;
     return 1;
   }

   Int_t ZZ4LBase::ElectronCutHighPU(int i)
   {
     //////////////  Ele   V5 =======================================
     double RelComIsoEB = (*Z_Lept1_RelisolPtTrks03)[i]+max(0.,((*Z_Lept1_RelisoEm03)[i]*(*Z_Lept1_pt)[i])-1.)+(*Z_Lept1_RelisoHad03)[i];
     double RelComIsoEE = (*Z_Lept1_RelisolPtTrks03)[i]+(*Z_Lept1_RelisoEm03)[i]+(*Z_Lept1_RelisoHad03)[i];
     if((*Z_Lept1_pt)[i] < 30) return -1;
     if(fabs((*Z_Lept1_etaSC)[i])>2.5) return -1;
     //W/Z
     if(fabs((*Z_Lept1_etaSC)[i])>1.4442 && fabs((*Z_Lept1_etaSC)[i])<1.566)return -1;

     if( fabs( (*Z_Lept1_etaSC)[i]) < 1.4442)
     {
       if( (*Z_Lept1_sigmaIEtaIEta)[i] > 0.01 ) return -1;
       if( fabs((*Z_Lept1_dEtaIn)[i]) >  0.004 ) return -1;
       if( fabs((*Z_Lept1_dPhiIn)[i])  > 0.06 ) return -1;
       if( (*Z_Lept1_HoverE)[i] > 0.12 ) return -1;
       if( fabs((*Z_Lept1_dxy)[i]) > 0.02 ) return -1;
       if( fabs((*Z_Lept1_dz)[i]) > 0.1 ) return -1;
       if( fabs((*Z_Lept1_InvEminusInvP)[i]) > 0.05 ) return -1;
       if( fabs((*Z_Lept1_mHits)[i]) > 1) return -1;

       //# Detector based Isolation. for WP80 Variable 
       //if(RelComIsoEB>0.07) return -1;
       //if((*Z_Lept1_RelisolPtTrks03)[i] > 0.05) return -1;
       //if((*Z_Lept1_RelisoEm03)[i] > 0.15) return -1;
       //if((*Z_Lept1_RelisoHad03)[i] > 0.10) return -1; 

     } else{ 
	 if( (*Z_Lept1_sigmaIEtaIEta)[i] > 0.03 ) return -1;
	 if( fabs((*Z_Lept1_dEtaIn)[i])  >   0.007 ) return -1;
	 if( fabs((*Z_Lept1_dPhiIn)[i])  > 0.03 ) return -1;
	 if( (*Z_Lept1_HoverE)[i] > 0.1 ) return -1;
	 if( fabs((*Z_Lept1_dxy)[i]) > 0.02 ) return -1;
	 if( fabs((*Z_Lept1_dz)[i]) > 0.1 ) return -1;
	 if( fabs((*Z_Lept1_InvEminusInvP)[i]) > 0.05) return -1;
	 if( fabs((*Z_Lept1_mHits)[i]) > 1) return -1;

	 //# Detector based Isolation. for WP80 Variable 
         //if(RelComIsoEE>0.06) return -1;
         //if((*Z_Lept1_RelisolPtTrks03)[i] > 0.05) return -1;
         //if((*Z_Lept1_RelisoEm03)[i] > 0.1) return -1;
         //if((*Z_Lept1_RelisoHad03)[i] > 0.1) return -1;
     }

     if( (*Z_Lept1_hasConversion)[i] ) return -1;
     if( (*Z_Lept1_relIsoRho03)[i] > 0.15 ) return -1;

     return 1;
   }


   Int_t ZZ4LBase::ElectronCutSide(int i)
   {
     //RD Scale Correction
     if(Mode == "AllCorrectionsRD")
     {
       scalecorr=EleScaleRD((*Z_Lept1_etaSC)[i]);
       (*Z_Lept1_pt)[i]= scalecorr*(*Z_Lept1_pt)[i];
       PtEtaPhiMLorentzVector WeleRD_4( (*Z_Lept1_pt)[i],(*Z_Lept1_etaSC)[i],(*Z_Lept1_phi)[i],0.000511);
       if(fabs( (*Z_Lept1_pt)[i]) < 25) return -1;
     }else{
       if((*Z_Lept1_pt)[i] < 25) return -1;
     }

     //MC Smear Correction
     if(Mode == "AllCorrectionsMC" || Mode == "Unfold")
     {
       if((*Z_Lept1_pt)[i] < 25) return -1;
       smearcorr=EleSmearMC((*Z_Lept1_etaSC)[i]);
       PtEtaPhiMLorentzVector WeleMC_4( (*Z_Lept1_pt)[i],(*Z_Lept1_etaSC)[i],(*Z_Lept1_phi)[i],0.000511);
       corr1 = gRandom->Gaus(WeleMC_4.E(), smearcorr)/WeleMC_4.E();
       WeleMC_4=corr1*WeleMC_4;
     }else{
       if((*Z_Lept1_pt)[i] < 25) return -1;
     }


     if(fabs((*Z_Lept1_etaSC)[i])>2.5) return -1;
     //if(fabs((*Z_Lept1_etaSC)[i])>2.1) return -1;
     if(fabs((*Z_Lept1_etaSC)[i])>1.4442 && fabs((*Z_Lept1_etaSC)[i]) < 1.566) return -1;
     //if(fabs((*Z_Lept1_etaSC)[i])>1.47 && fabs((*Z_Lept1_etaSC)[i]) < 1.566) return -1;

     if( fabs( (*Z_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept1_etaSC)[i]) < 1.47)
     {
	 if( (*Z_Lept1_sigmaIEtaIEta)[i] > 0.01 ) return -1;
     } else{
	 if( (*Z_Lept1_sigmaIEtaIEta)[i] > 0.03 ) return -1;
     }

     if( fabs( (*Z_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs((*Z_Lept1_dEtaIn)[i]) <  0.004 ) return -1;
     } else{
	 if( fabs((*Z_Lept1_dEtaIn)[i])  <   0.007 ) return -1;
     }

     if( fabs( (*Z_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs((*Z_Lept1_dPhiIn)[i])  < 0.06 ) return -1;
     } else {
	 if( fabs((*Z_Lept1_dPhiIn)[i])  < 0.03 ) return -1;
     }

     if( fabs( (*Z_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept1_etaSC)[i]) < 1.47)
     {
	 if( (*Z_Lept1_HoverE)[i] > 0.12 ) return -1;
     } else {
	 if( (*Z_Lept1_HoverE)[i] > 0.10 ) return -1;
     }

     if( fabs( (*Z_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs((*Z_Lept1_dxy)[i]) > 0.02 ) return -1;
     } else {
	 if( fabs((*Z_Lept1_dxy)[i]) > 0.02 ) return -1;
     }

     if( fabs( (*Z_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs((*Z_Lept1_dz)[i]) > 0.1 ) return -1;
     } else{
	 if( fabs((*Z_Lept1_dz)[i]) > 0.1 ) return -1;
     }

     if( fabs( (*Z_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs((*Z_Lept1_InvEminusInvP)[i]) > 0.05 ) return -1;
     } else{
	 if( fabs((*Z_Lept1_InvEminusInvP)[i]) > 0.05) return -1;
     }

     if( fabs( (*Z_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs((*Z_Lept1_mHits)[i]) > 1 ) return -1;
     } else{
	 if( fabs((*Z_Lept1_mHits)[i]) > 1) return -1;
     }

     if( (*Z_Lept1_hasConversion)[i] ) return -1;
     //if( (*Z_Lept1_relIsoRho03)[i] > 0.15 ) return -1;

     //       if( (*W_Neut_pt)[i] < 25 ) return -1;
     //          if( (*W_Mt)[i] < 40 ) return -1;
     return 1;
   }

   Int_t ZZ4LBase::ElectronCutSideHighPU(int i)
   {
     double RelComIsoEB = (*Z_Lept1_RelisolPtTrks03)[i]+max(0.,((*Z_Lept1_RelisoEm03)[i]*(*Z_Lept1_pt)[i])-1.)+(*Z_Lept1_RelisoHad03)[i];
     double RelComIsoEE = (*Z_Lept1_RelisolPtTrks03)[i]+(*Z_Lept1_RelisoEm03)[i]+(*Z_Lept1_RelisoHad03)[i]; 
     if((*Z_Lept1_pt)[i] < 30) return -1;
     if(fabs((*Z_Lept1_etaSC)[i])>2.5) return -1;
     if(fabs((*Z_Lept1_etaSC)[i])>1.4442 && fabs((*Z_Lept1_etaSC)[i]) < 1.566) return -1;

     if( fabs( (*Z_Lept1_etaSC)[i]) < 1.4442)
     {
	 if( (*Z_Lept1_sigmaIEtaIEta)[i] > 0.01 ) return -1;
	 if( fabs((*Z_Lept1_dEtaIn)[i]) <  0.004 ) return -1;
	 if( fabs((*Z_Lept1_dPhiIn)[i])  < 0.06 ) return -1;
	 if( (*Z_Lept1_HoverE)[i] > 0.12 ) return -1;
	 if( fabs((*Z_Lept1_dxy)[i]) > 0.02 ) return -1;
	 if( fabs((*Z_Lept1_dz)[i]) > 0.1 ) return -1;
	 if( fabs((*Z_Lept1_InvEminusInvP)[i]) > 0.05 ) return -1;
	 if( fabs((*Z_Lept1_mHits)[i]) > 1 ) return -1;
         //if(RelComIsoEB<0.07) return -1;
         //if((*Z_Lept1_RelisolPtTrks03)[i] < 0.09) return -1;
         //if((*Z_Lept1_RelisoEm03)[i] < 0.07) return -1;
         //if((*Z_Lept1_RelisoHad03)[i] < 0.10) return -1;

     } else{
	 if( (*Z_Lept1_sigmaIEtaIEta)[i] > 0.03 ) return -1;
	 if( fabs((*Z_Lept1_dEtaIn)[i])  <   0.007 ) return -1;
	 if( fabs((*Z_Lept1_dPhiIn)[i])  < 0.03 ) return -1;
	 if( (*Z_Lept1_HoverE)[i] > 0.10 ) return -1;
	 if( fabs((*Z_Lept1_dxy)[i]) > 0.02 ) return -1;
	 if( fabs((*Z_Lept1_dz)[i]) > 0.1 ) return -1;
	 if( fabs((*Z_Lept1_InvEminusInvP)[i]) > 0.05) return -1;
	 if( fabs((*Z_Lept1_mHits)[i]) > 1 ) return -1;
         //if(RelComIsoEE<0.06) return -1;
         //if((*Z_Lept1_RelisolPtTrks03)[i] < 0.04) return -1;
         //if((*Z_Lept1_RelisoEm03)[i] < 0.05) return -1;
         //if((*Z_Lept1_RelisoHad03)[i] < 0.025) return -1;
     }

     if( (*Z_Lept1_hasConversion)[i] ) return -1;
     if( (*Z_Lept1_relIsoRho03)[i] > 0.15 ) return -1;

     return 1;
   }


   Int_t ZZ4LBase::AddElectronCut(int i)
   {
     
     //RD Scale Correction
     if(Mode == "AllCorrectionsRD")
     {
       scalecorr=EleScaleRD((*Z_Lept1_etaSC)[i]);
       (*Z_Lept1_pt)[i]= scalecorr*(*Z_Lept1_pt)[i];
       PtEtaPhiMLorentzVector WeleRD_4( (*Z_Lept1_pt)[i],(*Z_Lept1_etaSC)[i],(*Z_Lept1_phi)[i],0.000511);
       if(fabs( (*Z_Lept1_pt)[i]) < 20) return -1;
     }else{
       if((*Z_Lept1_pt)[i] < 20) return -1;
     }

     //MC Smear Correction
     if(Mode == "AllCorrectionsMC" || Mode == "Unfold")
     {
       if((*Z_Lept1_pt)[i] < 20) return -1;
       smearcorr=EleSmearMC((*Z_Lept1_etaSC)[i]);
       PtEtaPhiMLorentzVector WeleMC_4( (*Z_Lept1_pt)[i],(*Z_Lept1_etaSC)[i],(*Z_Lept1_phi)[i],0.000511);
       corr1 = gRandom->Gaus(WeleMC_4.E(), smearcorr)/WeleMC_4.E();
       WeleMC_4=corr1*WeleMC_4;
     }else{
       if((*Z_Lept1_pt)[i] < 20) return -1;
     }

     if(fabs((*Z_Lept1_etaSC)[i])>2.5) return -1;
     if(fabs((*Z_Lept1_etaSC)[i])>1.4442 && fabs((*Z_Lept1_etaSC)[i]) < 1.566) return -1;
     //if(fabs((*Z_Lept1_etaSC)[i])>1.47 && fabs((*Z_Lept1_etaSC)[i]) < 1.566) return -1;

     if( fabs( (*Z_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept1_etaSC)[i]) < 1.47)
     {
	 if( (*Z_Lept1_sigmaIEtaIEta)[i] > 0.01 ) return -1;
     } else{
	 if( (*Z_Lept1_sigmaIEtaIEta)[i] > 0.03 ) return -1;
     }

     if( fabs( (*Z_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs ((*Z_Lept1_dEtaIn)[i]) > 0.007 ) return -1;
     } else{
	 if( fabs((*Z_Lept1_dEtaIn)[i]) > 0.01 ) return -1;
     }

     if( fabs( (*Z_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs ((*Z_Lept1_dPhiIn)[i]) > 0.8 ) return -1;
     } else {
	 if( fabs( (*Z_Lept1_dPhiIn)[i]) > 0.7 ) return -1;
     }

     if( fabs( (*Z_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept1_etaSC)[i]) < 1.47)
     {
	 if( (*Z_Lept1_HoverE)[i] > 0.15 ) return -1;
     } //else {
	// if( (*Z_Lept1_HoverE)[i] > 0.10 ) return -1;
       //}

     if( fabs( (*Z_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs((*Z_Lept1_dxy)[i]) > 0.04 ) return -1;
     } else {
	 if( fabs((*Z_Lept1_dxy)[i]) > 0.04 ) return -1;
     }

     if( fabs( (*Z_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs((*Z_Lept1_dz)[i]) > 0.2 ) return -1;
     } else{
	 if( fabs((*Z_Lept1_dz)[i]) > 0.2 ) return -1;
     }
     
     if( (*Z_Lept1_relIsoRho03)[i] > 0.15 ) return -1;

     return 1;
   }


   Int_t ZZ4LBase::AddElectronCutHighPU(int i)
   {

     if((*Z_Lept1_pt)[i] < 25) return -1;
     if(fabs((*Z_Lept1_etaSC)[i])>2.5) return -1;
     if(fabs((*Z_Lept1_etaSC)[i])>1.4442 && fabs((*Z_Lept1_etaSC)[i]) < 1.566) return -1;
     
     if( fabs( (*Z_Lept1_etaSC)[i]) < 1.4442)
     {
	 if( (*Z_Lept1_sigmaIEtaIEta)[i] > 0.01 ) return -1;
	 if( fabs ((*Z_Lept1_dEtaIn)[i]) > 0.004 ) return -1;
	 if( fabs ((*Z_Lept1_dPhiIn)[i]) > 0.06 ) return -1;
	 if( (*Z_Lept1_HoverE)[i] > 0.12 ) return -1;
	 if( fabs((*Z_Lept1_dxy)[i]) > 0.02 ) return -1;
	 if( fabs((*Z_Lept1_dz)[i]) > 0.1 ) return -1;
     } else{
	 if( (*Z_Lept1_sigmaIEtaIEta)[i] > 0.03 ) return -1;
	 if( fabs((*Z_Lept1_dEtaIn)[i]) > 0.007 ) return -1;
	 if( fabs( (*Z_Lept1_dPhiIn)[i]) > 0.03 ) return -1;
       //          if( (*Z_Lept1_HoverE)[i] > 0.10 ) return -1;
	 if( fabs((*Z_Lept1_dxy)[i]) > 0.02 ) return -1;
	 if( fabs((*Z_Lept1_dz)[i]) > 0.1 ) return -1;
     }

     if( (*Z_Lept1_relIsoRho03)[i] > 0.15 ) return -1;

     return 1;
   }


Int_t ZZ4LBase::TauCutZ(int i)
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
   Int_t ZZ4LBase::MuonCutZ(int i)
   {
     if( (*Z_Sign)[i] != 0 ) return -1;
     if( !(*Z_Lept1_isGlobal)[i])return -1;
     if( !(*Z_Lept2_isGlobal)[i])return -1;
     if((*Z_Lept1_pt)[i] < 20) return -1;//trigger SingleMu15 but we use 25 for Wpt
     //if((*Z_Lept2_pt)[i] < 25) return -1;
     ////if((*Z_Lept2_pt)[i] < 10) return -1;
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


   Int_t ZZ4LBase::ElectronCutZ(int i)
   {
     //////////////  Ele   V5 =======================================
     if( (*Z_Sign)[i] != 0 ) return -1;
     if((*Z_Lept1_pt)[i] < 25) return -1;
     //if((*Z_Lept2_pt)[i] < 10) return -1;
     if(fabs((*Z_Lept1_etaSC)[i])>2.5) return -1;
     if(fabs((*Z_Lept2_etaSC)[i])>2.5) return -1;

     //W/Z inclusive
     if(fabs((*Z_Lept1_etaSC)[i])>1.4442 && fabs((*Z_Lept1_etaSC)[i])<1.566)return -1;
     //if(fabs((*Z_Lept1_etaSC)[i])>1.47 && fabs((*Z_Lept1_etaSC)[i])<1.566)return -1;
     if(fabs((*Z_Lept2_etaSC)[i])>1.4442 && fabs((*Z_Lept2_etaSC)[i])<1.566)return -1;
     //if(fabs((*Z_Lept2_etaSC)[i])>1.47 && fabs((*Z_Lept2_etaSC)[i])<1.566)return -1;

     if( fabs( (*Z_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept1_etaSC)[i]) < 1.47)
     {
	 if( (*Z_Lept1_sigmaIEtaIEta)[i] > 0.01 ) return -1;
     }else{
	 if( (*Z_Lept1_sigmaIEtaIEta)[i] > 0.03 ) return -1;
     }

     if( fabs( (*Z_Lept2_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept2_etaSC)[i]) < 1.47)
     {
	 if( (*Z_Lept2_sigmaIEtaIEta)[i] > 0.01 ) return -1;
     }else{
	 if( (*Z_Lept2_sigmaIEtaIEta)[i] > 0.03 ) return -1;
     }

     /***********
     if( fabs( (*Z_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs((*Z_Lept1_dEtaIn)[i]) >  0.004 ) return -1;
     }else{
	 if( fabs((*Z_Lept1_dEtaIn)[i])  >   0.007 ) return -1;
     }

     if( fabs( (*Z_Lept2_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept2_etaSC)[i]) < 1.47)
     {
	 if( fabs((*Z_Lept2_dEtaIn)[i]) >  0.004 ) return -1;
     }else{
	 if( fabs((*Z_Lept2_dEtaIn)[i])  >   0.007 ) return -1;
     }

     if( fabs( (*Z_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs((*Z_Lept1_dPhiIn)[i])  > 0.06 ) return -1;
     }else {
	 if( fabs((*Z_Lept1_dPhiIn)[i])  > 0.03 ) return -1;
     }

     if( fabs( (*Z_Lept2_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept2_etaSC)[i]) < 1.47)
     {
	 if( fabs((*Z_Lept2_dPhiIn)[i])  > 0.06 ) return -1;
     }else {
	 if( fabs((*Z_Lept2_dPhiIn)[i])  > 0.03 ) return -1;
     }

     if( fabs( (*Z_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept1_etaSC)[i]) < 1.47)
     {
	 if( (*Z_Lept1_HoverE)[i] > 0.12 ) return -1;
     }else {
	 if( (*Z_Lept1_HoverE)[i] > 0.10 ) return -1;
     } 
     
     if( fabs( (*Z_Lept2_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept2_etaSC)[i]) < 1.47)
     {
	 if( (*Z_Lept2_HoverE)[i] > 0.12 ) return -1;
     }else {
	 if( (*Z_Lept2_HoverE)[i] > 0.10 ) return -1;
     }

     if( fabs( (*Z_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs((*Z_Lept1_dxy)[i]) > 0.02 ) return -1;
     }else {
	 if( fabs((*Z_Lept1_dxy)[i]) > 0.02 ) return -1;
     }
     
     if( fabs( (*Z_Lept2_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept2_etaSC)[i]) < 1.47)
     {
	 if( fabs((*Z_Lept2_dxy)[i]) > 0.02 ) return -1;
     }else {
	 if( fabs((*Z_Lept2_dxy)[i]) > 0.02 ) return -1;
     }

     if( fabs( (*Z_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs((*Z_Lept1_dz)[i]) > 0.1 ) return -1;
     }else{
	 if( fabs((*Z_Lept1_dz)[i]) > 0.1 ) return -1;
     }

     //cout<< fabs((*Z_Lept2_dz)[i])<<endl; 
     if( fabs( (*Z_Lept2_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept2_etaSC)[i]) < 1.47)
     {
	 if( fabs((*Z_Lept2_dz)[i]) > 0.1 ) return -1;
     }else{
	 if( fabs((*Z_Lept2_dz)[i]) > 0.1 ) return -1;
     }

     if( fabs( (*Z_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs((*Z_Lept1_InvEminusInvP)[i]) > 0.05 ) return -1;
     }else{
	 if( fabs((*Z_Lept1_InvEminusInvP)[i]) > 0.05) return -1;
     }
     
     if( fabs( (*Z_Lept2_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept2_etaSC)[i]) < 1.47)
     {
	 if( fabs((*Z_Lept2_InvEminusInvP)[i]) > 0.05 ) return -1;
     }else{
	 if( fabs((*Z_Lept2_InvEminusInvP)[i]) > 0.05) return -1;
     }

     if( fabs( (*Z_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs((*Z_Lept1_mHits)[i]) > 1 ) return -1;
     }else{
	 if( fabs((*Z_Lept1_mHits)[i]) > 1) return -1;
     }

     if( fabs( (*Z_Lept2_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept2_etaSC)[i]) < 1.47)
     {
	 if( fabs((*Z_Lept2_mHits)[i]) > 1 ) return -1;
     }else{
	 if( fabs((*Z_Lept2_mHits)[i]) > 1) return -1;
     }

     if( (*Z_Lept1_hasConversion)[i] ) return -1;
     if( (*Z_Lept2_hasConversion)[i] ) return -1;
     if( (*Z_Lept1_relIsoRho03)[i] > 0.15 ) return -1;
     if( (*Z_Lept2_relIsoRho03)[i] > 0.15 ) return -1;

     //       if( (*W_Neut_pt)[i] < 25 ) return -1;
     //          if( (*W_Mt)[i] < 40 ) return -1;
   
     ***************/
     return 1;
   }


   Int_t ZZ4LBase::ElectronCutZHighPU(int i)
   {


     //////////////  Ele   V5 =======================================

     if( (*Z_Sign)[i] != 0 ) return -1;
     if((*Z_Lept1_pt)[i] < 20) return -1;
     //if((*Z_Lept2_pt)[i] < 25) return -1;
     if(fabs((*Z_Lept1_etaSC)[i])>2.5) return -1;
     if(fabs((*Z_Lept2_etaSC)[i])>2.5) return -1;
     //W/Z inclusive
     if(fabs((*Z_Lept1_etaSC)[i])>1.4442 && fabs((*Z_Lept1_etaSC)[i])<1.566)return -1;
     //if(fabs((*Z_Lept1_etaSC)[i])>1.47 && fabs((*Z_Lept1_etaSC)[i])<1.566)return -1;
     if(fabs((*Z_Lept2_etaSC)[i])>1.4442 && fabs((*Z_Lept2_etaSC)[i])<1.566)return -1;
     //if(fabs((*Z_Lept2_etaSC)[i])>1.47 && fabs((*Z_Lept2_etaSC)[i])<1.566)return -1;
     
     if( fabs( (*Z_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept1_etaSC)[i]) < 1.47)
     {
	 if( (*Z_Lept1_sigmaIEtaIEta)[i] > 0.01 ) return -1;
     }else{
	 if( (*Z_Lept1_sigmaIEtaIEta)[i] > 0.03 ) return -1;
     }

     if( fabs( (*Z_Lept2_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept2_etaSC)[i]) < 1.47)
     {
	 if( (*Z_Lept2_sigmaIEtaIEta)[i] > 0.01 ) return -1;
     }else{
	 if( (*Z_Lept2_sigmaIEtaIEta)[i] > 0.03 ) return -1;
     }

     if( fabs( (*Z_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs((*Z_Lept1_dEtaIn)[i]) >  0.004 ) return -1;
     }else{
	 if( fabs((*Z_Lept1_dEtaIn)[i])  >   0.007 ) return -1;
     }

     if( fabs( (*Z_Lept2_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept2_etaSC)[i]) < 1.47)
     {
	 if( fabs((*Z_Lept2_dEtaIn)[i]) >  0.004 ) return -1;
     }else{
	 if( fabs((*Z_Lept2_dEtaIn)[i])  >   0.007 ) return -1;
     }

     if( fabs( (*Z_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs((*Z_Lept1_dPhiIn)[i])  > 0.06 ) return -1;
     }else {
	 if( fabs((*Z_Lept1_dPhiIn)[i])  > 0.03 ) return -1;
     }

     if( fabs( (*Z_Lept2_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept2_etaSC)[i]) < 1.47)
     {
	 if( fabs((*Z_Lept2_dPhiIn)[i])  > 0.06 ) return -1;
     }else {
	 if( fabs((*Z_Lept2_dPhiIn)[i])  > 0.03 ) return -1;
     }

     if( fabs( (*Z_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept1_etaSC)[i]) < 1.47)
     {
	 if( (*Z_Lept1_HoverE)[i] > 0.04 ) return -1;
     }else {
	 if( (*Z_Lept1_HoverE)[i] > 0.025 ) return -1;
     }

     if( fabs( (*Z_Lept2_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept2_etaSC)[i]) < 1.47)
     {
	 if( (*Z_Lept2_HoverE)[i] > 0.04 ) return -1;
     }else {
	 if( (*Z_Lept2_HoverE)[i] > 0.025 ) return -1;
     }

     if( fabs( (*Z_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs((*Z_Lept1_dxy)[i]) > 0.02 ) return -1;
     }else {
	 if( fabs((*Z_Lept1_dxy)[i]) > 0.02 ) return -1;
     }
     
     if( fabs( (*Z_Lept2_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept2_etaSC)[i]) < 1.47)
     {
	 if( fabs((*Z_Lept2_dxy)[i]) > 0.02 ) return -1;
     }else {
	 if( fabs((*Z_Lept2_dxy)[i]) > 0.02 ) return -1;
     }

     if( fabs( (*Z_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs((*Z_Lept1_dz)[i]) > 0.1 ) return -1;
     }else{
	 if( fabs((*Z_Lept1_dz)[i]) > 0.1 ) return -1;
     }

     //cout<< fabs((*Z_Lept2_dz)[i])<<endl; 
     if( fabs( (*Z_Lept2_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept2_etaSC)[i]) < 1.47)
     {
	 if( fabs((*Z_Lept2_dz)[i]) > 0.1 ) return -1;
     }else{
	 if( fabs((*Z_Lept2_dz)[i]) > 0.1 ) return -1;
     }

     if( fabs( (*Z_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs((*Z_Lept1_InvEminusInvP)[i]) > 0.05 ) return -1;
     }else{
	 if( fabs((*Z_Lept1_InvEminusInvP)[i]) > 0.05) return -1;
     }

     if( fabs( (*Z_Lept2_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept2_etaSC)[i]) < 1.47)
     {
	 if( fabs((*Z_Lept2_InvEminusInvP)[i]) > 0.05 ) return -1;
     }else{
	 if( fabs((*Z_Lept2_InvEminusInvP)[i]) > 0.05) return -1;
     }

     if( fabs( (*Z_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs((*Z_Lept1_mHits)[i]) > 0 ) return -1;
     }else{
	 if( fabs((*Z_Lept1_mHits)[i]) > 0 ) return -1;
     }

     if( fabs( (*Z_Lept2_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept2_etaSC)[i]) < 1.47)
     {
	 if( fabs((*Z_Lept2_mHits)[i]) > 0 ) return -1;
     }else{
	 if( fabs((*Z_Lept2_mHits)[i]) > 0 ) return -1;
     }

     if( (*Z_Lept1_hasConversion)[i] ) return -1;
     if( (*Z_Lept2_hasConversion)[i] ) return -1;
     if( (*Z_Lept1_relIsoRho03)[i] > 0.15 ) return -1;
     if( (*Z_Lept2_relIsoRho03)[i] > 0.15 ) return -1;

     //       if( (*W_Neut_pt)[i] < 25 ) return -1;
     //          if( (*W_Mt)[i] < 40 ) return -1;

     return 1;
   }

Int_t ZZ4LBase::DoScaleSmearScan(
    double zlep1Pt,double zlep1Pz,double zlep1En,double zlep1Phi,
    double zlep2Pt,double zlep2Pz,double zlep2En,double zlep2Phi,double TTW)
{
  //TLorentzVector Z_4(
  //    zlep1Pt*cos(zlep1Phi)+zlep2Pt*cos(zlep2Phi),
  //    zlep1Pt*sin(zlep1Phi)+zlep2Pt*sin(zlep2Phi),
  //    zlep1Pz+zlep2Pz,
  //    zlep1En+zlep2En);
  //cout<<"ZmassOrg: "<<Z.mass<<"================="<<endl;
  double scale, smear;
  for(int i(0);i<=ScaleBins-1;i++)
  {
    for(int j(0);j<=ScaleBins-1;j++)
    {
      scale = ScaleL + i*(ScaleH-ScaleL)/(ScaleBins-1);
      smear = SmearL + j*(SmearH-SmearL)/(ScaleBins-1);
      newZlep1Pt = gRandom->Gaus(0,1)*smear+scale*zlep1Pt;
      //newZlep2Pt = zlep2Pt;
      newZlep2Pt = gRandom->Gaus(0,1)*smear+scale*zlep2Pt;
      TLorentzVector Z_4(
          newZlep1Pt*cos(zlep1Phi)+newZlep2Pt*cos(zlep2Phi),
          newZlep1Pt*sin(zlep1Phi)+newZlep2Pt*sin(zlep2Phi),
          zlep1Pz+zlep2Pz,
          zlep1En+zlep2En);
      //cout<<"scale smear "<<scale<<" "<<smear<<endl;
      //cout<<"old lepPt "<<zlep1Pt<<" "<<zlep2Pt<<" new Pt diff "<<newZlep1Pt-zlep1Pt<<" "<<newZlep2Pt-zlep2Pt<<" Z.mass corr- org"<<Z_4.M()-Z.mass<<endl;
      //      h1_ZmassDaughEta[i][j]->Fill(Z_4.M(),TTW);
    }
  }
  return 0;
}

Int_t ZZ4LBase::EtaRange(double lep1Eta,double lep2Eta)
{
  int lep1Range(-1);
  int lep2Range(-1);
  if( AnaChannel=="ElectronLowPU")
  {
    if( fabs(lep1Eta) >= 0.0   && fabs(lep1Eta) < 0.4)    lep1Range=0;
    if( fabs(lep1Eta) >= 0.4   && fabs(lep1Eta) < 0.8)    lep1Range=1;
    if( fabs(lep1Eta) >= 0.8   && fabs(lep1Eta) < 1.2)    lep1Range=2;
    if( fabs(lep1Eta) >= 1.2   && fabs(lep1Eta) < 1.4442) lep1Range=3;
    if( fabs(lep1Eta) >= 1.566 && fabs(lep1Eta) < 2.0)    lep1Range=4;
    if( fabs(lep1Eta) >= 2.0   && fabs(lep1Eta) < 2.5)    lep1Range=5;

    if( fabs(lep2Eta) >= 0.0   && fabs(lep2Eta) < 0.4)    lep2Range=0;
    if( fabs(lep2Eta) >= 0.4   && fabs(lep2Eta) < 0.8)    lep2Range=1;
    if( fabs(lep2Eta) >= 0.8   && fabs(lep2Eta) < 1.2)    lep2Range=2;
    if( fabs(lep2Eta) >= 1.2   && fabs(lep2Eta) < 1.4442) lep2Range=3;
    if( fabs(lep2Eta) >= 1.566 && fabs(lep2Eta) < 2.0)    lep2Range=4;
    if( fabs(lep2Eta) >= 2.0   && fabs(lep2Eta) < 2.5)    lep2Range=5;
  }

  if(AnaChannel=="ElectronHighPU")
  {
    if( fabs(lep1Eta) >= 0.0   && fabs(lep1Eta) < 0.2)    lep1Range=0;
    if( fabs(lep1Eta) >= 0.2   && fabs(lep1Eta) < 0.4)    lep1Range=1;
    if( fabs(lep1Eta) >= 0.4   && fabs(lep1Eta) < 0.6)    lep1Range=2;
    if( fabs(lep1Eta) >= 0.6   && fabs(lep1Eta) < 0.8)    lep1Range=3;
    if( fabs(lep1Eta) >= 0.8   && fabs(lep1Eta) < 1.0)    lep1Range=4;
    if( fabs(lep1Eta) >= 1.0   && fabs(lep1Eta) < 1.2)    lep1Range=5;
    if( fabs(lep1Eta) >= 1.2   && fabs(lep1Eta) < 1.4)    lep1Range=6;
    //if( fabs(lep1Eta) >= 1.4   && fabs(lep1Eta) < 1.6)    lep1Range=7;
    if( fabs(lep1Eta) >= 1.6   && fabs(lep1Eta) < 1.8)    lep1Range=7;
    if( fabs(lep1Eta) >= 1.8   && fabs(lep1Eta) < 2.0)    lep1Range=8;
    if( fabs(lep1Eta) >= 2.0   && fabs(lep1Eta) < 2.2)    lep1Range=9;
    if( fabs(lep1Eta) >= 2.2   && fabs(lep1Eta) < 2.4)    lep1Range=10;

    if( fabs(lep2Eta) >= 0.0   && fabs(lep2Eta) < 0.2)    lep2Range=0;
    if( fabs(lep2Eta) >= 0.2   && fabs(lep2Eta) < 0.4)    lep2Range=1;
    if( fabs(lep2Eta) >= 0.4   && fabs(lep2Eta) < 0.6)    lep2Range=2;
    if( fabs(lep2Eta) >= 0.6   && fabs(lep2Eta) < 0.8)    lep2Range=3;
    if( fabs(lep2Eta) >= 0.8   && fabs(lep2Eta) < 1.0)    lep2Range=4;
    if( fabs(lep2Eta) >= 1.0   && fabs(lep2Eta) < 1.2)    lep2Range=5;
    if( fabs(lep2Eta) >= 1.2   && fabs(lep2Eta) < 1.4)    lep2Range=6;
    //if( fabs(lep2Eta) >= 1.4   && fabs(lep2Eta) < 1.6)    lep2Range=7;
    if( fabs(lep2Eta) >= 1.6   && fabs(lep2Eta) < 1.8)    lep2Range=7;
    if( fabs(lep2Eta) >= 1.8   && fabs(lep2Eta) < 2.0)    lep2Range=8;
    if( fabs(lep2Eta) >= 2.0   && fabs(lep2Eta) < 2.2)    lep2Range=9;
    if( fabs(lep2Eta) >= 2.2   && fabs(lep2Eta) < 2.4)    lep2Range=10;
  }
  if( AnaChannel=="MuonLowPU" || AnaChannel=="MuonHighPU")
  {
    if( fabs(lep1Eta) >= 0.0   && fabs(lep1Eta) < 0.4)    lep1Range=0;
    if( fabs(lep1Eta) >= 0.4   && fabs(lep1Eta) < 0.8)    lep1Range=1;
    if( fabs(lep1Eta) >= 0.8   && fabs(lep1Eta) < 1.2)    lep1Range=2;
    if( fabs(lep1Eta) >= 1.2   && fabs(lep1Eta) < 1.6)    lep1Range=3;
    if( fabs(lep1Eta) >= 1.6   && fabs(lep1Eta) < 2.1)    lep1Range=4;

    if( fabs(lep2Eta) >= 0.0   && fabs(lep2Eta) < 0.4)    lep2Range=0;
    if( fabs(lep2Eta) >= 0.4   && fabs(lep2Eta) < 0.8)    lep2Range=1;
    if( fabs(lep2Eta) >= 0.8   && fabs(lep2Eta) < 1.2)    lep2Range=2;
    if( fabs(lep2Eta) >= 1.2   && fabs(lep2Eta) < 1.6)    lep2Range=3;
    if( fabs(lep2Eta) >= 1.6   && fabs(lep2Eta) < 2.1)    lep2Range=4;
  }
  
  if( lep1Range == lep2Range )return lep1Range;
  else return -1;
}
Int_t ZZ4LBase::EtaRange(double lep1Eta)
{
  int lep1Range(-1);
  if( AnaChannel=="ElectronLowPU")
  {
    if( fabs(lep1Eta) >= 0.0   && fabs(lep1Eta) < 0.4)    lep1Range=0;
    if( fabs(lep1Eta) >= 0.4   && fabs(lep1Eta) < 0.8)    lep1Range=1;
    if( fabs(lep1Eta) >= 0.8   && fabs(lep1Eta) < 1.2)    lep1Range=2;
    if( fabs(lep1Eta) >= 1.2   && fabs(lep1Eta) < 1.4442) lep1Range=3;
    if( fabs(lep1Eta) >= 1.566 && fabs(lep1Eta) < 2.0)    lep1Range=4;
    if( fabs(lep1Eta) >= 2.0   && fabs(lep1Eta) < 2.5)    lep1Range=5;
    
  }
  if(AnaChannel=="ElectronHighPU")
  {
    if( fabs(lep1Eta) >= 0.0   && fabs(lep1Eta) < 0.2)    lep1Range=0;
    if( fabs(lep1Eta) >= 0.2   && fabs(lep1Eta) < 0.4)    lep1Range=1;
    if( fabs(lep1Eta) >= 0.4   && fabs(lep1Eta) < 0.6)    lep1Range=2;
    if( fabs(lep1Eta) >= 0.6   && fabs(lep1Eta) < 0.8)    lep1Range=3;
    if( fabs(lep1Eta) >= 0.8   && fabs(lep1Eta) < 1.0)    lep1Range=4;
    if( fabs(lep1Eta) >= 1.0   && fabs(lep1Eta) < 1.2)    lep1Range=5;
    if( fabs(lep1Eta) >= 1.2   && fabs(lep1Eta) < 1.4)    lep1Range=6;
    //if( fabs(lep1Eta) >= 1.4   && fabs(lep1Eta) < 1.6)    lep1Range=7;
    if( fabs(lep1Eta) >= 1.6   && fabs(lep1Eta) < 1.8)    lep1Range=7;
    if( fabs(lep1Eta) >= 1.8   && fabs(lep1Eta) < 2.0)    lep1Range=8;
    if( fabs(lep1Eta) >= 2.0   && fabs(lep1Eta) < 2.2)    lep1Range=9;
    if( fabs(lep1Eta) >= 2.2   && fabs(lep1Eta) < 2.4)    lep1Range=10;
  }
  if( AnaChannel=="MuonLowPU" || AnaChannel=="MuonHighPU")
  {
    if( fabs(lep1Eta) >= 0.0   && fabs(lep1Eta) < 0.4)    lep1Range=0;
    if( fabs(lep1Eta) >= 0.4   && fabs(lep1Eta) < 0.8)    lep1Range=1;
    if( fabs(lep1Eta) >= 0.8   && fabs(lep1Eta) < 1.2)    lep1Range=2;
    if( fabs(lep1Eta) >= 1.2   && fabs(lep1Eta) < 1.6)    lep1Range=3;
    if( fabs(lep1Eta) >= 1.6   && fabs(lep1Eta) < 2.1)    lep1Range=4;
  }
  return lep1Range;
}
//MisChargeStudy
/*Int_t ZZ4LBase::FillMisChargeInfo()
{
  h1_Zmass_QAll->Fill(Z.mass,mTTW);
  for(int iz(0); iz<Z_size;iz++){
  ZLep1eta = (*Z_Lept1_eta)[iz];
  ZLep2eta = (*Z_Lept2_eta)[iz];
  ZLep1charge = (*Z_Lept1_charge)[iz];
  ZLep2charge = (*Z_Lept2_charge)[iz];
  ZLep1Requirement = (*Z_Lept1_GsfCtfScPixchargeConsistentcheck)[iz];
  ZLep2Requirement = (*Z_Lept2_GsfCtfScPixchargeConsistentcheck)[iz];
  for(int i=0;i<lept1eta;i++){
  for(int j=0;j<lept2eta;j++){
  if (fabs(ZLep1eta) > wqaMetMNBins[i] && fabs(ZLep1eta) < wqaMetMXBins[i] ) {
  if (fabs(ZLep2eta) > wqaMetMNBins[j] && fabs(ZLep2eta) < wqaMetMXBins[j] ) {
    h1_Zmass_QNo[i][j]->Fill(Z.mass,mTTW);
    if ( ZLep1Requirement == 1 && ZLep2Requirement == 1){
    h1_Zmass_QThree[i][j]->Fill(Z.mass,mTTW);
    }
    if(ZLep1charge*ZLep2charge==1){
    h1_Zmass_QNoSame[i][j]->Fill(Z.mass,mTTW);
    }
    if(ZLep1Requirement == 1 && ZLep2Requirement == 1 && ZLep1charge*ZLep2charge==1){
    h1_Zmass_QThreeSame[i][j]->Fill(Z.mass,mTTW);
    }
   }
   }
  }
  }
  }
  return 0;
}
*/

Int_t ZZ4LBase::FillAcceptInfo()
{
  return 0;
}
Int_t ZZ4LBase::DumpTruthGenInfo(int i)
{
  return 0;
}

Int_t ZZ4LBase::DoRecoilCorr()
{
  return 0;
}
int ZZ4LBase::DumpMETs()
{
  // MET
  pfMEtTL.SetPxPyPzE(pfMEt_x,pfMEt_y,0,toolbox::pT(pfMEt_x,pfMEt_y));
  NoPuMEtTL.SetPxPyPzE(NoPuMEt_x,NoPuMEt_y,0,toolbox::pT(NoPuMEt_x,NoPuMEt_y));
  MVaMEtTL.SetPxPyPzE(MVaMEt_x,MVaMEt_y,0,toolbox::pT(MVaMEt_x,MVaMEt_y));
  genMEtTrueTL.SetPxPyPzE(genMEtTrue_x,genMEtTrue_y,0,toolbox::pT(genMEtTrue_x,genMEtTrue_y));
  genMEtCaloTL.SetPxPyPzE(genMEtCalo_x,genMEtCalo_y,0,toolbox::pT(genMEtCalo_x,genMEtCalo_y));
  genMEtCaloAndNonPromptTL.SetPxPyPzE(genMEtCaloAndNonPrompt_x,genMEtCaloAndNonPrompt_y,0,toolbox::pT(genMEtCaloAndNonPrompt_x,genMEtCaloAndNonPrompt_y));
  return 0;
}
Int_t ZZ4LBase::InitVar4Evt()
{
  // Recoil
  mTTW = 1;
  mVtxVar.nPrim = 0;
  mVtxVar.nGood = 0;
  //cout<<"ZZ4LBase::InitVar4Evt ==========================="<<endl;
  glbMuChi2=0;
  addLepN=0;lep_pt=0;lep_pt_corr=0;corrMet=0;
  scalecorr1=0;
  corr1=0;
  corr2=0;
  scalecorr2=0;
  smearcorr1=0;
  smearcorr2=0;
  newZlep1Pt=0;
  newZlep2Pt=0;
  elemass=0.000511;
  muonmass=0.1056;
  Rcl.u1W=-999;Rcl.u2W=-999;Rcl.u3W=-999;
  Rcl.u1Z=-999;Rcl.u2Z=-999;Rcl.u3Z=-999;
  //genInfo.W_MCtruth = 0;
  genInfo.BornW_pt = 0;
  genInfo.PostW_pt = 0;
  genInfo.BornW_Nu_Cnt = 0;

  // Z boson
  Z.Pass = false;
  mZ_size = Z_Mass->size();
  return 0;
}

#endif // #ifdef ZZ4LBase_cxx


