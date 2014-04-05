//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed May 16 17:32:24 2012 by ROOT version 5.32/00
// from TChain WlnuBase/tree/
//////////////////////////////////////////////////////////
//$Log: WlnuBase.h,v $
//Revision 1.13  2013/09/13 00:09:32  salee
//*** empty log message ***
//
//Revision 1.12  2013/09/12 05:14:48  sangilpark
//*** empty log message ***
//
//Revision 1.10  2013/08/31 06:56:40  khakim

#ifndef WlnuBase_h
#define WlnuBase_h

#include <TSystem.h>
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
#include "WlnuNT.h"


#include "Math/PtEtaPhiE4D.h"
#include "Math/PtEtaPhiM4D.h"
#include "Math/LorentzVector.h"

typedef ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiM4D<double> > PtEtaPhiMLorentzVectorD;
typedef PtEtaPhiMLorentzVectorD PtEtaPhiMLorentzVector;


// Fixed size dimensions of array or collections stored in the TTree if any.
class WlnuBase: public WlnuNT {
public :
  //WMuons	wMuons;

   double	LumiWeight;
   double RecoilBins[U1Bin+1]; //Recoil Study Wpt bins
   double Bins[NWptBinPlus]; //Wpt bins
     
   TH1D*	h1_Vtx_Prim;
   TH1D*	h1_Vtx_Good;

   TH1D*        h1_Vtx_Good1;
   TH1D*        h1_Vtx_Prim1;
   TH1D*        h1_npileup1;


   WlnuBase(TTree *tree=0,TTree *WMuonTree=0, double weight=1,
       TString OutNameBase_ = "output.root",TString Mode="analysis",
       TString AnaChannel ="Muon",double WCHARGE=0, bool runOnMC=true, int etaRange_=-999);

   virtual ~WlnuBase();
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
  
  virtual Double_t    ElePlusEffiCorrection(double elePt, double eleEtaSC);
  virtual Double_t    EleMinusEffiCorrection(double elePt, double eleEtaSC);
  virtual Double_t    MuonPlusEffiCorrection(double muonPt, double muonEta);
  virtual Double_t    MuonMinusEffiCorrection(double muonPt, double muonEta);
  
  virtual Double_t    EleScaleRD(double ele_etaSC);
  virtual Double_t    EleSmearMC(double ele_etaSC);
  virtual Double_t    MuonSmearMC(double mu_eta);
   
   virtual Int_t    DoRecoilCorr();
   virtual Int_t    InitVar4Evt();
   virtual Int_t    DumpMETs();
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
  int DumpWbestCand(int);
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
  //W boson Variables
  struct WCand{
    int    trthIdx;
    double pt;
    double Mt;
    double Met;
    double Nu_px;
    double Nu_py;
    double Met_side;
    int size;
    double charge;

    int muonHit;
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
    int idxBest;
    TVector2 *PostT2;
    double Post_pt;
    TVector2 *RecoilT2;
  }W;
  double w_pt_side, w_acop;

  //For filling MET histograms for WQA by chang
  double wqaMetMXBins[NWqaBins];
  double wqaMetMNBins[NWqaBins];
  
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

#ifdef WlnuBase_cxx

void WlnuBase::Init(TTree *tree)
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
  WlnuNT::Init(tree);

   mEffSf = 1;


   h1_Vtx_Prim	= new TH1D("h1_Vtx_Prim","N primary vertex",25,0,25);
   h1_Vtx_Good	= new TH1D("h1_Vtx_Good","N primary vertex",25,0,25);

   h1_Vtx_Prim1 = new TH1D("h1_Vtx_Prim1","Vtx_Prim1",60,0,60);
   h1_Vtx_Good1 = new TH1D("h1_Vtx_Good1","Vtx_Good1",60,0,60);
   h1_npileup1 = new TH1D("h1_npileup1","npileup1",60,0.,60);

   //Acceptance Histograms


   // MisChargeStudy 
/*   if(AnaChannel == "ElectronHighPU" )
     {
      h1_Zmass_QAll = new TH1D("h1_Zmass_QAll","Invariant mass for Z",120,60,120);
      for(int i(0);i<lept1eta;i++)
       {
        for(int j=0;j<lept2eta;j++){
        sprintf(histName,"h1_Zmass_QThree_%d_%d",i,j);
        h1_Zmass_QThree[i][j] = new TH1D(histName,"Three Charge Requirement",120,60,120);
        sprintf(histName,"h1_Zmass_QThreeSame_%d_%d",i,j);
        h1_Zmass_QThreeSame[i][j] = new TH1D(histName,"Three Charge Requirement",120,60,120);
        sprintf(histName,"h1_Zmass_QNo_%d_%d",i,j);
        h1_Zmass_QNo[i][j] = new TH1D(histName,"No Charge Requirement",120,60,120);
        sprintf(histName,"h1_Zmass_QNoSame_%d_%d",i,j);
        h1_Zmass_QNoSame[i][j] = new TH1D(histName,"No Charge Requirement",120,60,120);
        }
       }
     }
*/
   // Unfold

   //---------------

   //Z=============
   //0,3,6,10,14,18,23,30,40,55,70,100

   if(Mode == "ScaleMakeMC")
   {
     cout<<"Setting Random Seed for ScaleMakeMC"<<endl;
     switch (ETARANGE)
     {
       case 0:
	 gRandom->SetSeed(0x12345);
	 break;
       case 1:
	 gRandom->SetSeed(0x12346);
	 break;
       case 2:
	 gRandom->SetSeed(0x12347);
	 break;
       case 3:
	 gRandom->SetSeed(0x12348);
	 break;
       case 4:
	 gRandom->SetSeed(0x12349);
	 break;
       case 5:
	 gRandom->SetSeed(0x12350);
	 break;
       default:
	 cout<<"ScaleMake MC: What is this Eta range?"<<endl;
	 exit(0);
     }
   }

   if(Mode == "ScaleMakeMC" || Mode == "ScaleMakeRD")
   {

     if( AnaChannel=="MuonLowPU" || AnaChannel=="MuonHighPU")
     {
     }
   }
   Notify();
}
WlnuBase::WlnuBase(TTree *WlnuBaseTree,TTree *WLepTree, double lumiweight,
       TString OutNameBase_, TString mode_, TString AnaChannel_,
       double Wcharge, bool runOnMC, int etaRange_)
{
  fChain=0;
    // if parameter tree is not specified (or zero), connect the file
    // // used to generate this class and read the Tree.
   cout<<"WlnuBase constructor"<<endl;
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
   // Final Bins
   Bins[0]=     0.;
   Bins[1]=     7.5;
   Bins[2]=     12.5;
   Bins[3]=     17.5;
   Bins[4]=     24.;
   Bins[5]=     30.;
   Bins[6]=    40.;
   Bins[7]=    50.;
   Bins[8]=    70.;
   Bins[9]=    110.;
   Bins[10]=    150.;
   Bins[11]=    190.;
   Bins[12]=    250.;
   Bins[13]=    600.;

   cout<<"initialization for Recoil bins"<<endl;
   RecoilBins[0]	= 0.;
   RecoilBins[1]	= 5.;
   RecoilBins[2]	= 10.;
   RecoilBins[3]	= 15.;
   RecoilBins[4]	= 20.;
   RecoilBins[5]	= 25.;
   RecoilBins[6]	= 30.;
   RecoilBins[7]	= 35.;
   RecoilBins[8]	= 40.;
   RecoilBins[9]	= 50.;
   RecoilBins[10]	= 60.;
   RecoilBins[11]	= 70.;
   RecoilBins[12]	= 80.;
   RecoilBins[13]	= 90.;
   RecoilBins[14]       = 100.;
   RecoilBins[15]       = 120.;
   RecoilBins[16]       = 150.;
/*
   wqaMetMXBins[0] = 0.1; wqaMetMXBins[1] = 0.2; wqaMetMXBins[2] = 0.3; wqaMetMXBins[3] = 0.4; wqaMetMXBins[4] = 0.5;
      wqaMetMXBins[5] = 0.6; wqaMetMXBins[6] = 0.7; wqaMetMXBins[7] = 0.8; wqaMetMXBins[8] = 0.9; wqaMetMXBins[9] = 1.0;
         wqaMetMXBins[10] = 1.1; wqaMetMXBins[11] = 1.2; wqaMetMXBins[12] = 1.3; wqaMetMXBins[13] = 1.4; wqaMetMXBins[14] = 1.5;
	    wqaMetMXBins[15] = 1.6; wqaMetMXBins[16] = 1.7; wqaMetMXBins[17] = 1.8; wqaMetMXBins[18] = 1.9; wqaMetMXBins[19] = 2.0;
	       wqaMetMXBins[20] = 2.1; wqaMetMXBins[21] = 2.2; wqaMetMXBins[22] = 2.3; wqaMetMXBins[23] = 2.4; wqaMetMXBins[24] = 2.5;

	          wqaMetMNBins[0] = 0.0; wqaMetMNBins[1] = 0.1; wqaMetMNBins[2] = 0.2; wqaMetMNBins[3] = 0.3;  wqaMetMNBins[4] = 0.4;
		     wqaMetMNBins[5] = 0.5; wqaMetMNBins[6] = 0.6; wqaMetMNBins[7] = 0.7; wqaMetMNBins[8] = 0.8;  wqaMetMNBins[9] = 0.9;
		        wqaMetMNBins[10] = 1.0; wqaMetMNBins[11] = 1.1; wqaMetMNBins[12] = 1.2; wqaMetMNBins[13] = 1.3;   wqaMetMNBins[14] = 1.4;
			   wqaMetMNBins[15] = 1.5; wqaMetMNBins[16] = 1.6; wqaMetMNBins[17] = 1.7; wqaMetMNBins[18] = 1.8;   wqaMetMNBins[19] = 1.9;
			      wqaMetMNBins[20] = 2.0; wqaMetMNBins[21] = 2.1; wqaMetMNBins[22] = 2.2; wqaMetMNBins[23] = 2.3;   wqaMetMNBins[24] = 2.4;
 */


   wqaMetMXBins[0] = 0.2; wqaMetMXBins[1] = 0.4; wqaMetMXBins[2] = 0.6; wqaMetMXBins[3] = 0.8; wqaMetMXBins[4] = 1.0;
   wqaMetMXBins[5] = 1.2; wqaMetMXBins[6] = 1.4; wqaMetMXBins[7] = 1.6; wqaMetMXBins[8] = 1.8; wqaMetMXBins[9] = 2.0;
   wqaMetMXBins[10] = 2.2; wqaMetMXBins[11] = 2.4; 

   wqaMetMNBins[0] = 0.0; wqaMetMNBins[1] = 0.2; wqaMetMNBins[2] = 0.4; wqaMetMNBins[3] = 0.6;  wqaMetMNBins[4] = 0.8;
   wqaMetMNBins[5] = 1.0; wqaMetMNBins[6] = 1.2; wqaMetMNBins[7] = 1.4; wqaMetMNBins[8] = 1.6;  wqaMetMNBins[9] = 1.8;
   wqaMetMNBins[10] = 2.0; wqaMetMNBins[11] = 2.2;

   if (WlnuBaseTree == 0 ) {
     /****************
#ifdef SINGLE_TREE
      // The following code should be used if you want this class to access
      // a single tree instead of a chain
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Memory Directory");
      if (!f || !f->IsOpen()) {
         f = new TFile("Memory Directory");
      }
      f->GetObject("WlnuBase/tree",tree);

#else // SINGLE_TREE

      // The following code should be used if you want this class to access a chain
      // of trees.
      TChain * chain = new TChain("WlnuBase/tree","");
      chain->Add("/terranova_1/W_Ntuple/SingleMuRun2012APromptRecoV1Aod/wNtuple_01.root");
      tree = chain;
#endif // SINGLE_TREE

**********************/
     cout<<"Usage: WlnuBase(TTree*... ) "<<endl;
     exit(-1);
   }else{
     cout<<"WlnuBase.h: initializing the trees"<<endl;
   LumiWeight = lumiweight;
   cout<<"Input Value of Lumiweight = "<<lumiweight<<" Initialized as = "<<LumiWeight<<endl;
   OutNameBase = OutNameBase_;
   Mode = mode_;
   AnaChannel = AnaChannel_;
   WCHARGE = Wcharge;
   RunOnMC = runOnMC;
   ETARANGE = etaRange_;
   Init(WlnuBaseTree);
   //wMuons.Init(WLepTree);
   }
   InitVar();
}


   WlnuBase::~WlnuBase()
   {
     if (!fChain) return;
     delete fChain->GetCurrentFile();
   }

   Int_t WlnuBase::GetEntry(Long64_t entry)
   {
     // Read contents of entry.
     if (!fChain) return 0;
     return fChain->GetEntry(entry);
   }

   Long64_t WlnuBase::LoadTree(Long64_t entry)
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
   
   Bool_t WlnuBase::Notify()
   {
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

     return kTRUE;
   }


   void WlnuBase::Show(Long64_t entry)
   {
     // Print contents of entry.
     // If entry is not specified, print current entry
     if (!fChain) return;
     fChain->Show(entry);
   }

// Electron effi correction
Double_t WlnuBase::ElePlusEffiCorrection(double elePt, double eleEtaSC)
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
Double_t WlnuBase::EleMinusEffiCorrection(double elePt, double eleEtaSC)
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
Double_t WlnuBase::MuonPlusEffiCorrection(double muonPt, double muonEta)
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

Double_t WlnuBase::MuonMinusEffiCorrection(double muonPt, double muonEta)
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
   Double_t WlnuBase::EleScaleRD(double ele_etaSC)
   {
     if(fabs(ele_etaSC) >= 0.0   && fabs(ele_etaSC) < 0.4) {return 0.999315  ;}
     if(fabs(ele_etaSC) >= 0.4   && fabs(ele_etaSC) < 0.8) {return 1.00358   ;}
     if(fabs(ele_etaSC) >= 0.8   && fabs(ele_etaSC) < 1.2) {return 1.00325   ;}
     if(fabs(ele_etaSC) >= 1.2   && fabs(ele_etaSC) < 1.4442) {return 1.00244 ;}
     if(fabs(ele_etaSC) >= 1.566 && fabs(ele_etaSC) < 2.0) {return 1.0067   ; }
     if(fabs(ele_etaSC) >= 2.0   && fabs(ele_etaSC) < 2.5) {return 0.992737  ; }
   }

   Double_t WlnuBase::EleSmearMC(double ele_etaSC)
   {
     if(fabs(ele_etaSC) >= 0.0   && fabs(ele_etaSC) < 0.4) {return 0.382443   ;}
     if(fabs(ele_etaSC) >= 0.4   && fabs(ele_etaSC) < 0.8) {return 0.356171   ;}
     if(fabs(ele_etaSC) >= 0.8   && fabs(ele_etaSC) < 1.2) {return 0.559123   ;}
     if(fabs(ele_etaSC) >= 1.2   && fabs(ele_etaSC) < 1.4442) {return 0.01     ;}
     if(fabs(ele_etaSC) >= 1.566 && fabs(ele_etaSC) < 2.0) {return 0.972944    ;}
     if(fabs(ele_etaSC) >= 2.0   && fabs(ele_etaSC) < 2.5) {return 1.84788    ;}
   }

   Double_t WlnuBase::MuonSmearMC(double mu_eta)
   {
     if(fabs(mu_eta) >= 0.0   && fabs(mu_eta) < 0.4) { return 0.01   ;}
     if(fabs(mu_eta) >= 0.4   && fabs(mu_eta) < 0.8) { return 0.381253    ;}
     if(fabs(mu_eta) >= 0.8   && fabs(mu_eta) < 1.2) { return 0.743902     ;}
     if(fabs(mu_eta) >= 1.2   && fabs(mu_eta) < 1.6) { return 0.637325     ;}
     if(fabs(mu_eta) >= 1.6   && fabs(mu_eta) < 2.1) { return 0.611946     ;}
   }

Int_t WlnuBase::TauCut(int i)
{
  //if( (*W_Lept1_MedComIsoDelBetCorr3Hits)[i] < 0.5 )return -1;
  //if( (*W_Lept1_decModFind)[i] < 0.5 )return -1;
  if( fabs((*W_Lept1_eta)[i]) > 2.3 )return -1;
  if( fabs((*W_Lept1_pt)[i]) < 20 )return -1;
  return 1;
}

Int_t WlnuBase::MuonCut(int i)
{
  if( !(*W_Lept1_isGlobal)[i])return -1;
  if((*W_Lept1_pt)[i] < 20) return -1;
  //if((*W_Lept1_pt)[i] < 25) return -1;

  //MC Smear Correction
  if(Mode == "AllCorrectionsMC" || Mode == "Unfold")
  {
    smearcorr= MuonSmearMC((*W_Lept1_eta)[i]);
    PtEtaPhiMLorentzVector Wmu_4( (*W_Lept1_pt)[i],(*W_Lept1_eta)[i],(*W_Lept1_phi)[i],0.1056);
    corr1 = gRandom->Gaus(Wmu_4.E(), smearcorr)/Wmu_4.E();
    Wmu_4=corr1*Wmu_4;
  }

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
  if( ((*W_Lept1_chIso04)[i]+betaCor04)/(*W_Lept1_pt)[i] > 0.12) return -1; //Signal Band   // use this line to get n.of.events in AB area in  ABCD method


  // uncomment next line (Sideband)  to get n.of.events in DC area in  ABCD method
  //  if( ((*W_Lept1_chIso04)[i]+betaCor04)/(*W_Lept1_pt)[i] < 0.3 || ((*W_Lept1_chIso04)[i]+betaCor04)/(*W_Lept1_pt)[i] > 0.5) return -1; //Side Band

  
  
  //if( (*W_Neut_pt)[i] < 14 ) return -1;
  //if( (*W_Mt)[i] < 30 ) return -1;
  //if( (*W_Neut_pt)[i] < 25 ) return -1;
  //if( (*W_Mt)[i] < 40 ) return -1;

  return 1;
}

Int_t WlnuBase::MuonCutSide(int i)
{
  if( !(*W_Lept1_isGlobal)[i])return -1;
  if((*W_Lept1_pt)[i] < 20) return -1;
  //if((*W_Lept1_pt)[i] < 25) return -1;
     
  //MC Smear Correction
  if(Mode == "AllCorrectionsMC" || Mode == "Unfold")
  {
    smearcorr= MuonSmearMC((*W_Lept1_eta)[i]);
    PtEtaPhiMLorentzVector Wmu_4( (*W_Lept1_pt)[i],(*W_Lept1_eta)[i],(*W_Lept1_phi)[i],0.1056);
    corr1 = gRandom->Gaus(Wmu_4.E(), smearcorr)/Wmu_4.E();
    Wmu_4=corr1*Wmu_4;
  }
     
  if(fabs((*W_Lept1_eta)[i])>2.1) return -1;
  if( (*W_Lept1_globalNormChi2)[i]<0 || (*W_Lept1_globalNormChi2)[i] >= 10) return -1;
  if( (*W_Lept1_muonHits)[i] <1) return -1;
  if( (*W_Lept1_matchStations)[i] <2 ) return -1;
  if( (*W_Lept1_trkLayers)[i] <6 )return -1;
  if( (*W_Lept1_pixelHits)[i] <1 )return -1;
  if( fabs( (*W_Lept1_dB)[i]) >0.02 )return -1;
  if( fabs( (*W_Lept1_dz)[i]) >0.5 )return -1;
  double betaCor04= max(0.0,(*W_Lept1_nhIso04)[i]+(*W_Lept1_phIso04)[i]-0.5*(*W_Lept1_pcIso04)[i]);
  if( ((*W_Lept1_chIso04)[i]+betaCor04)/(*W_Lept1_pt)[i] < 0.3 || ((*W_Lept1_chIso04)[i]+betaCor04)/(*W_Lept1_pt)[i] > 0.5) return -1; //Side Band

  return 1;
}

Int_t WlnuBase::AddMuonCut(int i)
{
  if( !(*W_Lept1_isTrker)[i] || !(*W_Lept1_isGlobal)[i]) return -1; //Signal Band only. For Side Band comment this line.
  if((*W_Lept1_pt)[i] <= 10) return -1;

  //MC Smear Correction
  if(Mode == "AllCorrectionsMC" || Mode == "Unfold")
  {
    smearcorr= MuonSmearMC((*W_Lept1_eta)[i]);
    PtEtaPhiMLorentzVector Wmu_4( (*W_Lept1_pt)[i],(*W_Lept1_eta)[i],(*W_Lept1_phi)[i],0.1056);
    corr1 = gRandom->Gaus(Wmu_4.E(), smearcorr)/Wmu_4.E();
    Wmu_4=corr1*Wmu_4;
  }

  if(fabs((*W_Lept1_eta)[i])>=2.4) return -1;
  double betaCor04= max(0.0,(*W_Lept1_nhIso04)[i]+(*W_Lept1_phIso04)[i]-0.5*(*W_Lept1_pcIso04)[i]);
  if( ((*W_Lept1_chIso04)[i]+betaCor04)/(*W_Lept1_pt)[i] > 0.20) return -1;
  return 1;
}

   Int_t WlnuBase::ElectronCut(int i)
   {
     //RD Scale Correction
     if(Mode == "AllCorrectionsRD")
     {
       scalecorr=EleScaleRD((*W_Lept1_etaSC)[i]);
       (*W_Lept1_pt)[i]= scalecorr*(*W_Lept1_pt)[i];
       PtEtaPhiMLorentzVector WeleRD_4( (*W_Lept1_pt)[i],(*W_Lept1_etaSC)[i],(*W_Lept1_phi)[i],0.000511);
       if(fabs( (*W_Lept1_pt)[i]) < 25) return -1;
     }else{
       if((*W_Lept1_pt)[i] < 25) return -1;
     }

     //MC Smear Correction
     if(Mode == "AllCorrectionsMC" || Mode == "Unfold")
     {
       if((*W_Lept1_pt)[i] < 25) return -1;
       smearcorr=EleSmearMC((*W_Lept1_etaSC)[i]);
       PtEtaPhiMLorentzVector WeleMC_4( (*W_Lept1_pt)[i],(*W_Lept1_etaSC)[i],(*W_Lept1_phi)[i],0.000511);
       corr1 = gRandom->Gaus(WeleMC_4.E(), smearcorr)/WeleMC_4.E();
       WeleMC_4=corr1*WeleMC_4;
     }else{
       if((*W_Lept1_pt)[i] < 25) return -1;
     }

     
     if(fabs((*W_Lept1_etaSC)[i])>2.5) return -1;
     //if(fabs((*W_Lept1_etaSC)[i])>2.1) return -1;
     //W/Z
     if(fabs((*W_Lept1_etaSC)[i])>1.4442 && fabs((*W_Lept1_etaSC)[i])<1.566)return -1;
     //if(fabs((*W_Lept1_etaSC)[i])>1.47 && fabs((*W_Lept1_etaSC)[i])<1.566)return -1;
     
     if( fabs( (*W_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*W_Lept1_etaSC)[i]) < 1.47)
     {
	 if( (*W_Lept1_sigmaIEtaIEta)[i] > 0.01 ) return -1; // use this line to get n.of.events in AB area in  ABCD method
	 //if( (*W_Lept1_sigmaIEtaIEta)[i] > 0.01 ) return -1; // use this line to get n.of.events in DC area in  ABCD method
     } else{
	 if( (*W_Lept1_sigmaIEtaIEta)[i] > 0.03 ) return -1;   // use this line to get n.of.events in AB area in  ABCD method
	 //if( (*W_Lept1_sigmaIEtaIEta)[i] > 0.03 ) return -1; // use this line to get n.of.events in DC area in  ABCD method
     }

     if( fabs( (*W_Lept1_etaSC)[i]) < 1.4442)
         //if( fabs( (*W_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs((*W_Lept1_dEtaIn)[i]) >  0.004 ) return -1;
     } else{
	 if( fabs((*W_Lept1_dEtaIn)[i])  >   0.007 ) return -1;
     }
     
     if( fabs( (*W_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*W_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs((*W_Lept1_dPhiIn)[i])  > 0.06 ) return -1;
     } else{
	 if( fabs((*W_Lept1_dPhiIn)[i])  > 0.03 ) return -1;
     }

     if( fabs( (*W_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*W_Lept1_etaSC)[i]) < 1.47)
     {
	 if( (*W_Lept1_HoverE)[i] > 0.12 ) return -1;
     } else{
	 if( (*W_Lept1_HoverE)[i] > 0.10 ) return -1;
     }

     if( fabs( (*W_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*W_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs((*W_Lept1_dxy)[i]) > 0.02 ) return -1;
     } else{
	 if( fabs((*W_Lept1_dxy)[i]) > 0.02 ) return -1;
     }

     if( fabs( (*W_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*W_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs((*W_Lept1_dz)[i]) > 0.1 ) return -1;
     } else{
	 if( fabs((*W_Lept1_dz)[i]) > 0.1 ) return -1;
     }
     if( fabs( (*W_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*W_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs((*W_Lept1_InvEminusInvP)[i]) > 0.05 ) return -1;
     }else{
	 if( fabs((*W_Lept1_InvEminusInvP)[i]) > 0.05) return -1;
     }

     if( fabs( (*W_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*W_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs((*W_Lept1_mHits)[i]) > 1 ) return -1;
     } else{
	 if( fabs((*W_Lept1_mHits)[i]) > 1) return -1;
     }
 
     if( (*W_Lept1_hasConversion)[i] ) return -1;
     if( (*W_Lept1_relIsoRho03)[i] > 0.15 ) return -1;

     //       if( (*W_Neut_pt)[i] < 25 ) return -1;
     //          if( (*W_Mt)[i] < 40 ) return -1;
     return 1;
   }

   Int_t WlnuBase::ElectronCutHighPU(int i)
   {
     //////////////  Ele   V5 =======================================
     double RelComIsoEB = (*W_Lept1_RelisolPtTrks03)[i]+max(0.,((*W_Lept1_RelisoEm03)[i]*(*W_Lept1_pt)[i])-1.)+(*W_Lept1_RelisoHad03)[i];
     double RelComIsoEE = (*W_Lept1_RelisolPtTrks03)[i]+(*W_Lept1_RelisoEm03)[i]+(*W_Lept1_RelisoHad03)[i];
     if((*W_Lept1_pt)[i] < 30) return -1;
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

     } else{ 
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


   Int_t WlnuBase::ElectronCutSide(int i)
   {
     //RD Scale Correction
     if(Mode == "AllCorrectionsRD")
     {
       scalecorr=EleScaleRD((*W_Lept1_etaSC)[i]);
       (*W_Lept1_pt)[i]= scalecorr*(*W_Lept1_pt)[i];
       PtEtaPhiMLorentzVector WeleRD_4( (*W_Lept1_pt)[i],(*W_Lept1_etaSC)[i],(*W_Lept1_phi)[i],0.000511);
       if(fabs( (*W_Lept1_pt)[i]) < 25) return -1;
     }else{
       if((*W_Lept1_pt)[i] < 25) return -1;
     }

     //MC Smear Correction
     if(Mode == "AllCorrectionsMC" || Mode == "Unfold")
     {
       if((*W_Lept1_pt)[i] < 25) return -1;
       smearcorr=EleSmearMC((*W_Lept1_etaSC)[i]);
       PtEtaPhiMLorentzVector WeleMC_4( (*W_Lept1_pt)[i],(*W_Lept1_etaSC)[i],(*W_Lept1_phi)[i],0.000511);
       corr1 = gRandom->Gaus(WeleMC_4.E(), smearcorr)/WeleMC_4.E();
       WeleMC_4=corr1*WeleMC_4;
     }else{
       if((*W_Lept1_pt)[i] < 25) return -1;
     }


     if(fabs((*W_Lept1_etaSC)[i])>2.5) return -1;
     //if(fabs((*W_Lept1_etaSC)[i])>2.1) return -1;
     if(fabs((*W_Lept1_etaSC)[i])>1.4442 && fabs((*W_Lept1_etaSC)[i]) < 1.566) return -1;
     //if(fabs((*W_Lept1_etaSC)[i])>1.47 && fabs((*W_Lept1_etaSC)[i]) < 1.566) return -1;

     if( fabs( (*W_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*W_Lept1_etaSC)[i]) < 1.47)
     {
	 if( (*W_Lept1_sigmaIEtaIEta)[i] > 0.01 ) return -1;
     } else{
	 if( (*W_Lept1_sigmaIEtaIEta)[i] > 0.03 ) return -1;
     }

     if( fabs( (*W_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*W_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs((*W_Lept1_dEtaIn)[i]) <  0.004 ) return -1;
     } else{
	 if( fabs((*W_Lept1_dEtaIn)[i])  <   0.007 ) return -1;
     }

     if( fabs( (*W_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*W_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs((*W_Lept1_dPhiIn)[i])  < 0.06 ) return -1;
     } else {
	 if( fabs((*W_Lept1_dPhiIn)[i])  < 0.03 ) return -1;
     }

     if( fabs( (*W_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*W_Lept1_etaSC)[i]) < 1.47)
     {
	 if( (*W_Lept1_HoverE)[i] > 0.12 ) return -1;
     } else {
	 if( (*W_Lept1_HoverE)[i] > 0.10 ) return -1;
     }

     if( fabs( (*W_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*W_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs((*W_Lept1_dxy)[i]) > 0.02 ) return -1;
     } else {
	 if( fabs((*W_Lept1_dxy)[i]) > 0.02 ) return -1;
     }

     if( fabs( (*W_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*W_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs((*W_Lept1_dz)[i]) > 0.1 ) return -1;
     } else{
	 if( fabs((*W_Lept1_dz)[i]) > 0.1 ) return -1;
     }

     if( fabs( (*W_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*W_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs((*W_Lept1_InvEminusInvP)[i]) > 0.05 ) return -1;
     } else{
	 if( fabs((*W_Lept1_InvEminusInvP)[i]) > 0.05) return -1;
     }

     if( fabs( (*W_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*W_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs((*W_Lept1_mHits)[i]) > 1 ) return -1;
     } else{
	 if( fabs((*W_Lept1_mHits)[i]) > 1) return -1;
     }

     if( (*W_Lept1_hasConversion)[i] ) return -1;
     //if( (*W_Lept1_relIsoRho03)[i] > 0.15 ) return -1;

     //       if( (*W_Neut_pt)[i] < 25 ) return -1;
     //          if( (*W_Mt)[i] < 40 ) return -1;
     return 1;
   }

   Int_t WlnuBase::ElectronCutSideHighPU(int i)
   {
     double RelComIsoEB = (*W_Lept1_RelisolPtTrks03)[i]+max(0.,((*W_Lept1_RelisoEm03)[i]*(*W_Lept1_pt)[i])-1.)+(*W_Lept1_RelisoHad03)[i];
     double RelComIsoEE = (*W_Lept1_RelisolPtTrks03)[i]+(*W_Lept1_RelisoEm03)[i]+(*W_Lept1_RelisoHad03)[i]; 
     if((*W_Lept1_pt)[i] < 30) return -1;
     if(fabs((*W_Lept1_etaSC)[i])>2.5) return -1;
     if(fabs((*W_Lept1_etaSC)[i])>1.4442 && fabs((*W_Lept1_etaSC)[i]) < 1.566) return -1;

     if( fabs( (*W_Lept1_etaSC)[i]) < 1.4442)
     {
	 if( (*W_Lept1_sigmaIEtaIEta)[i] > 0.01 ) return -1;
	 if( fabs((*W_Lept1_dEtaIn)[i]) <  0.004 ) return -1;
	 if( fabs((*W_Lept1_dPhiIn)[i])  < 0.06 ) return -1;
	 if( (*W_Lept1_HoverE)[i] > 0.12 ) return -1;
	 if( fabs((*W_Lept1_dxy)[i]) > 0.02 ) return -1;
	 if( fabs((*W_Lept1_dz)[i]) > 0.1 ) return -1;
	 if( fabs((*W_Lept1_InvEminusInvP)[i]) > 0.05 ) return -1;
	 if( fabs((*W_Lept1_mHits)[i]) > 1 ) return -1;
         //if(RelComIsoEB<0.07) return -1;
         //if((*W_Lept1_RelisolPtTrks03)[i] < 0.09) return -1;
         //if((*W_Lept1_RelisoEm03)[i] < 0.07) return -1;
         //if((*W_Lept1_RelisoHad03)[i] < 0.10) return -1;

     } else{
	 if( (*W_Lept1_sigmaIEtaIEta)[i] > 0.03 ) return -1;
	 if( fabs((*W_Lept1_dEtaIn)[i])  <   0.007 ) return -1;
	 if( fabs((*W_Lept1_dPhiIn)[i])  < 0.03 ) return -1;
	 if( (*W_Lept1_HoverE)[i] > 0.10 ) return -1;
	 if( fabs((*W_Lept1_dxy)[i]) > 0.02 ) return -1;
	 if( fabs((*W_Lept1_dz)[i]) > 0.1 ) return -1;
	 if( fabs((*W_Lept1_InvEminusInvP)[i]) > 0.05) return -1;
	 if( fabs((*W_Lept1_mHits)[i]) > 1 ) return -1;
         //if(RelComIsoEE<0.06) return -1;
         //if((*W_Lept1_RelisolPtTrks03)[i] < 0.04) return -1;
         //if((*W_Lept1_RelisoEm03)[i] < 0.05) return -1;
         //if((*W_Lept1_RelisoHad03)[i] < 0.025) return -1;
     }

     if( (*W_Lept1_hasConversion)[i] ) return -1;
     if( (*W_Lept1_relIsoRho03)[i] > 0.15 ) return -1;

     return 1;
   }


   Int_t WlnuBase::AddElectronCut(int i)
   {
     
     //RD Scale Correction
     if(Mode == "AllCorrectionsRD")
     {
       scalecorr=EleScaleRD((*W_Lept1_etaSC)[i]);
       (*W_Lept1_pt)[i]= scalecorr*(*W_Lept1_pt)[i];
       PtEtaPhiMLorentzVector WeleRD_4( (*W_Lept1_pt)[i],(*W_Lept1_etaSC)[i],(*W_Lept1_phi)[i],0.000511);
       if(fabs( (*W_Lept1_pt)[i]) < 20) return -1;
     }else{
       if((*W_Lept1_pt)[i] < 20) return -1;
     }

     //MC Smear Correction
     if(Mode == "AllCorrectionsMC" || Mode == "Unfold")
     {
       if((*W_Lept1_pt)[i] < 20) return -1;
       smearcorr=EleSmearMC((*W_Lept1_etaSC)[i]);
       PtEtaPhiMLorentzVector WeleMC_4( (*W_Lept1_pt)[i],(*W_Lept1_etaSC)[i],(*W_Lept1_phi)[i],0.000511);
       corr1 = gRandom->Gaus(WeleMC_4.E(), smearcorr)/WeleMC_4.E();
       WeleMC_4=corr1*WeleMC_4;
     }else{
       if((*W_Lept1_pt)[i] < 20) return -1;
     }

     if(fabs((*W_Lept1_etaSC)[i])>2.5) return -1;
     if(fabs((*W_Lept1_etaSC)[i])>1.4442 && fabs((*W_Lept1_etaSC)[i]) < 1.566) return -1;
     //if(fabs((*W_Lept1_etaSC)[i])>1.47 && fabs((*W_Lept1_etaSC)[i]) < 1.566) return -1;

     if( fabs( (*W_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*W_Lept1_etaSC)[i]) < 1.47)
     {
	 if( (*W_Lept1_sigmaIEtaIEta)[i] > 0.01 ) return -1;
     } else{
	 if( (*W_Lept1_sigmaIEtaIEta)[i] > 0.03 ) return -1;
     }

     if( fabs( (*W_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*W_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs ((*W_Lept1_dEtaIn)[i]) > 0.007 ) return -1;
     } else{
	 if( fabs((*W_Lept1_dEtaIn)[i]) > 0.01 ) return -1;
     }

     if( fabs( (*W_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*W_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs ((*W_Lept1_dPhiIn)[i]) > 0.8 ) return -1;
     } else {
	 if( fabs( (*W_Lept1_dPhiIn)[i]) > 0.7 ) return -1;
     }

     if( fabs( (*W_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*W_Lept1_etaSC)[i]) < 1.47)
     {
	 if( (*W_Lept1_HoverE)[i] > 0.15 ) return -1;
     } //else {
	// if( (*W_Lept1_HoverE)[i] > 0.10 ) return -1;
       //}

     if( fabs( (*W_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*W_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs((*W_Lept1_dxy)[i]) > 0.04 ) return -1;
     } else {
	 if( fabs((*W_Lept1_dxy)[i]) > 0.04 ) return -1;
     }

     if( fabs( (*W_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*W_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs((*W_Lept1_dz)[i]) > 0.2 ) return -1;
     } else{
	 if( fabs((*W_Lept1_dz)[i]) > 0.2 ) return -1;
     }
     
     if( (*W_Lept1_relIsoRho03)[i] > 0.15 ) return -1;

     return 1;
   }


   Int_t WlnuBase::AddElectronCutHighPU(int i)
   {

     if((*W_Lept1_pt)[i] < 25) return -1;
     if(fabs((*W_Lept1_etaSC)[i])>2.5) return -1;
     if(fabs((*W_Lept1_etaSC)[i])>1.4442 && fabs((*W_Lept1_etaSC)[i]) < 1.566) return -1;
     
     if( fabs( (*W_Lept1_etaSC)[i]) < 1.4442)
     {
	 if( (*W_Lept1_sigmaIEtaIEta)[i] > 0.01 ) return -1;
	 if( fabs ((*W_Lept1_dEtaIn)[i]) > 0.004 ) return -1;
	 if( fabs ((*W_Lept1_dPhiIn)[i]) > 0.06 ) return -1;
	 if( (*W_Lept1_HoverE)[i] > 0.12 ) return -1;
	 if( fabs((*W_Lept1_dxy)[i]) > 0.02 ) return -1;
	 if( fabs((*W_Lept1_dz)[i]) > 0.1 ) return -1;
     } else{
	 if( (*W_Lept1_sigmaIEtaIEta)[i] > 0.03 ) return -1;
	 if( fabs((*W_Lept1_dEtaIn)[i]) > 0.007 ) return -1;
	 if( fabs( (*W_Lept1_dPhiIn)[i]) > 0.03 ) return -1;
       //          if( (*W_Lept1_HoverE)[i] > 0.10 ) return -1;
	 if( fabs((*W_Lept1_dxy)[i]) > 0.02 ) return -1;
	 if( fabs((*W_Lept1_dz)[i]) > 0.1 ) return -1;
     }

     if( (*W_Lept1_relIsoRho03)[i] > 0.15 ) return -1;

     return 1;
   }


Int_t WlnuBase::TauCutZ(int i)
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
   Int_t WlnuBase::MuonCutZ(int i)
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


   Int_t WlnuBase::ElectronCutZ(int i)
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
    
     return 1;
   }


   Int_t WlnuBase::ElectronCutZHighPU(int i)
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


Int_t WlnuBase::DoRecoilCorr()
{
  //Uncomment to apply scale/res corrections to MC
  //W.lep_pt_corr = gRandom->Gaus(W.lep_pt*lepScale,lepRes);

  //if( AnaChannel=="ElectronLowPU")
  //{
  //  //MC Smear Correction
  //  if(Mode == "AllCorrectionsMC" || Mode == "Unfold")
  //  {
  //    smearcorr=EleSmearMC(W.lep_etaSC);
  //    PtEtaPhiMLorentzVector WeleMC_4( W.lep_pt,W.lep_eta,W.lep_phi,0.000511);
  //    corr1 = gRandom->Gaus(WeleMC_4.E(), smearcorr)/WeleMC_4.E();
  //    WeleMC_4=corr1*WeleMC_4;
  //    W.lep_pt_corr=WeleMC_4.Pt();
  //  }else{
  //    W.lep_pt_corr = W.lep_pt;
  //  }
  //}
  //
  //if( AnaChannel=="MuonLowPU" || AnaChannel=="MuonHighPU")
  //{
  //  //MC Smear Correction
  //  if(Mode == "AllCorrectionsMC" || Mode == "Unfold")
  //  {
  //    smearcorr= MuonSmearMC(W.lep_eta);
  //    PtEtaPhiMLorentzVector Wmu_4( W.lep_pt,W.lep_eta,W.lep_phi,0.1056);
  //    corr1 = gRandom->Gaus(Wmu_4.E(), smearcorr)/Wmu_4.E();
  //    Wmu_4=corr1*Wmu_4;
  //    W.lep_pt_corr=Wmu_4.Pt();
  //   } else{
  //     W.lep_pt_corr = W.lep_pt;
  //   }
  //}
  W.lep_pt_corr = W.lep_pt;
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
  //if( W.pt < 100)
  //{
    RecoilCorr->Correct(
      corrMet,corrMetPhi,
      genInfo.PostW_pt,genInfo.PostW_phi,//basedonthis,calculate correctedrecoilvectors
      //genBeFsrW_pt,genW_phi, 
      W.lep_pt_corr,W.lep_phi,
      0,genInfo.charge); //nsigma(0:nominal,1:up,-1:down), charge
    TVector2 w_p_corr(corrMet*cos(corrMetPhi)+W.lep_pt_corr*cos(W.lep_phi),
      corrMet*sin(corrMetPhi)+W.lep_pt_corr*sin(W.lep_phi));
    W.pt = w_p_corr.Mod();
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
int WlnuBase::DumpMETs()
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
Int_t WlnuBase::InitVar4Evt()
{
  // Recoil
  W.RecoilT2=0;
  W.PostT2 =0;
  mTTW = 1;
  mVtxVar.nPrim = 0;
  mVtxVar.nGood = 0;
  //cout<<"WlnuBase::InitVar4Evt ==========================="<<endl;
  W.size = W_pt->size();
  W.pt=0;w_pt_side=0;w_acop=0;
  W.Mt=0;
  W.Met=0;
  W.Met_side=0;
  W.genIdx=-999;
  W.charge=0;
  W.lep_pt = 0;
  W.lep_phi = 0;
  W.lep_eta = 0;
  W.lep_etaSC = 0;
  W.Pass=0;
    
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

#endif // #ifdef WlnuBase_cxx


