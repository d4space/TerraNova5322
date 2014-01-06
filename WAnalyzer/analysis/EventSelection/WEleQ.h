//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed May 16 17:32:24 2012 by ROOT version 5.32/00
// from TChain WEleQ/tree/
//////////////////////////////////////////////////////////
//$Log: WEleQ.h,v $
//Revision 1.9  2013/08/19 15:11:26  jungmin
//*** empty log message ***

#ifndef WEleQ_h
#define WEleQ_h
/*
#include "WMuons.h"
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1D.h>
#include <TMath.h>
#include <TLorentzVector.h>
#include <TRandom.h>

#include <vector>
#include <vector>

#include <iostream>
#include <fstream>
#include <iomanip>
#include "../Utils/const.h"
#include "../Utils/RecoilCorrector.hh"

#include "Math/PtEtaPhiE4D.h"
#include "Math/PtEtaPhiM4D.h"
#include "Math/LorentzVector.h"
*/
#include "WLepNeu.h"
typedef ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiM4D<double> > PtEtaPhiMLorentzVectorD;
typedef PtEtaPhiMLorentzVectorD PtEtaPhiMLorentzVector;

//class WEleQ : public WLepNeu{
class WEleQ : public WLepNeu{

  public :
  
  /*   vector<double>  *W_Lept1_relIsoCom03;
   vector<double>  *W_Lept1_relIsoCom04;
   vector<double>  *W_Lept1_relIsoBeta03;
   vector<double>  *W_Lept1_relIsoBeta04;

   TBranch        *b_W_Lept1_relIsoCom03;   //!
   TBranch        *b_W_Lept1_relIsoCom04;   //!
   TBranch        *b_W_Lept1_relIsoBeta03;   //!
   TBranch        *b_W_Lept1_relIsoBeta04;   //!
*/
/*   TH1D*        h1_W_Neut_px_Corr;
   TH1D*        h1_W_Neut_py_Corr;
   TH1D*        h1_W_Neut_pt_Corr;
   TH1D*        h1_Z_Neut_pt;
   TH1D*        h1_Z_Neut_phi;
   TH1D*        h1_Z_Neut_px;
   TH1D*        h1_Z_Neut_py;
   TH1D*        h1_Z_Neut_pt_Corr;
   TH1D*        h1_Z_Neut_phi_Corr;
   TH1D*        h1_Z_Neut_px_Corr;
   TH1D*        h1_Z_Neut_py_Corr;
   TH2D*        h2_Z_Nvtx_px;
   TH2D*        h2_Z_Nvtx_py;
   TH2D*        h2_Z_Nvtx_px_Corr;
   TH2D*        h2_Z_Nvtx_py_Corr;
*/   TH1D*        h1_i_ToTal[EtaBin];
   TH1D*        h1_i_All[EtaBin];
   TH1D*        h1_i_other[EtaBin];
   TH1D*        h1_i_Side[EtaBin];
   TH1D*        h1_W_Neu_All[EtaBin];
   TH1D*        h1_W_Neu_other[EtaBin];
   TH1D*        h1_W_Neu_pt_ToTal[EtaBin];
   TH1D*        h1_W_Neu_pt_ToTal_beforeTrigger[EtaBin];
   TH1D*        h1_W_Neu_AddElectron[EtaBin];
   TH1D*        h1_W_Neu_pt_Side[EtaBin];
   //cut values check.
   TH1D*        h1_check_iw;
   TH1D*        h1_check_side_iw;
   TH1D*        h1_check_pt;
   TH1D*        h1_check_side_pt;
   TH1D*        h1_check_sigmaIetaIeta;
   TH1D*        h1_check_side_sigmaIetaIeta;
   TH1D*        h1_check_dEtaIn;
   TH1D*        h1_check_side_dEtaIn;
   TH1D*        h1_check_dPhiin;
   TH1D*        h1_check_side_dPhiin;
   TH1D*        h1_check_HoverE;
   TH1D*        h1_check_side_HoverE;
   TH1D*        h1_check_dxy;
   TH1D*        h1_check_side_dxy;
   TH1D*        h1_check_dz;
   TH1D*        h1_check_side_dz;
   TH1D*        h1_check_InvE_InvP;
   TH1D*        h1_check_side_InvE_InvP;
   TH1D*        h1_check_mHits;
   TH1D*        h1_check_side_mHits;
   TH1D*        h1_check_lep_eta;
   TH1D*        h1_check_side_lep_eta;

   WEleQ(TTree *tree=0,TTree *WMuonTree=0, double weight=1, TString OutFileName = "output.root",TString Mode="analysis", TString AnaChannel ="Muon",int etaRange_=-999);

   virtual ~WEleQ();
   virtual Int_t    ElectronCutHighPUToTal(int entry);
   virtual Int_t    ElectronCutHighPU(int entry);
   virtual Int_t    ElectronCutSideHighPU(int entry);
   virtual Int_t    AddElectronCutHighPU(int entry);

   virtual Int_t    InitVar4Evt();
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);



private:
  int evtCnt;
  bool W_pass;
  double wqaMetMXBins[NWqaBins];
  double wqaMetMNBins[NWqaBins];
  double lep_pt,addLepN,lep_pt_corr;
  TString       OutFileName;
  TString       Mode;
  TString       AnaChannel;
  double vtxz,vtxRho;
  double TTW;
  
  
  
/*  struct WCand{
    double Nu_px_Corr;
    double Nu_py_Corr;
    double Met_Corr;
  }wCand;
*/    int iw;
    double temp_elpT;

//  double Z_MET_pt, Z_MET_phi, Z_MET_px, Z_MET_py;
//  double Z_MET_pt_Corr, Z_MET_phi_Corr, Z_MET_px_Corr, Z_MET_py_Corr;



};

#endif

#ifdef WEleQ_cxx

void WEleQ::Init(TTree *tree)
{
  TTree *haha = tree;
  WLepNeu::Init(haha);



/*   W_Lept1_relIsoCom03 = 0;
   W_Lept1_relIsoCom04 = 0;
   W_Lept1_relIsoBeta03 = 0;
   W_Lept1_relIsoBeta04 = 0;
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("W_Lept1_relIsoCom03", &W_Lept1_relIsoCom03, &b_W_Lept1_relIsoCom03);
   fChain->SetBranchAddress("W_Lept1_relIsoCom04", &W_Lept1_relIsoCom04, &b_W_Lept1_relIsoCom04);
   fChain->SetBranchAddress("W_Lept1_relIsoBeta03", &W_Lept1_relIsoBeta03, &b_W_Lept1_relIsoBeta03);
   fChain->SetBranchAddress("W_Lept1_relIsoBeta04", &W_Lept1_relIsoBeta04, &b_W_Lept1_relIsoBeta04);
*/
  //===============================================
  //change to here whenever you change the tree
  //===============================================



   char histName[30];
/*   h1_W_Neut_px_Corr = new TH1D("h1_W_Neut_px_Corr","W_Neut_px_Corr",100,-100,100);
   h1_W_Neut_py_Corr = new TH1D("h1_W_Neut_py_Corr","W_Neut_py_Corr",100,-100,100);
   h1_W_Neut_pt_Corr = new TH1D("h1_W_Neut_pt_Corr","W_Neut_pt_Corr",100,0.,100);
   h1_Z_Neut_pt = new TH1D("h1_Z_Neut_pt","Z_Neut_pt",100,0.,100);
   h1_Z_Neut_phi = new TH1D("h1_Z_Neut_phi","Z_Neut_phi",100,-4,4);
   h1_Z_Neut_px = new TH1D("h1_Z_Neut_px","Z_Neut_px",100,-100,100);
   h1_Z_Neut_py = new TH1D("h1_Z_Neut_py","Z_Neut_py",100,-100,100);
   h1_Z_Neut_pt_Corr = new TH1D("h1_Z_Neut_pt_Corr","Z_Neut_pt_Corr",100,0.,100);
   h1_Z_Neut_phi_Corr = new TH1D("h1_Z_Neut_phi_Corr","Z_Neut_phi_Corr",100,-4,4);
   h1_Z_Neut_px_Corr = new TH1D("h1_Z_Neut_px_Corr","Z_Neut_px_Corr",100,-100,100);
   h1_Z_Neut_py_Corr = new TH1D("h1_Z_Neut_py_Corr","Z_Neut_py_Corr",100,-100,100);

   h2_Z_Nvtx_px = new TH2D("h2_Z_Nvtx_px","Nvtx vs Nu_px",100,0,60,100,-100,100);
   h2_Z_Nvtx_py = new TH2D("h2_Z_Nvtx_py","Nvtx vs Nu_py",100,0,60,100,-100,100);
   h2_Z_Nvtx_px_Corr = new TH2D("h2_Z_Nvtx_px_Corr","Nvtx vs Nu_px",100,0,60,100,-100,100);
   h2_Z_Nvtx_py_Corr = new TH2D("h2_Z_Nvtx_py_Corr","Nvtx vs Nu_py",100,0,60,100,-100,100);
*/
   
  if(AnaChannel == "ElectronHighPU" )
  {
   for(int i(0);i<EtaBin;i++)
   {
   sprintf(histName,"h1_i_ToTal_%d",i);
   h1_i_ToTal[i] = new TH1D(histName,"W_i_ToTal",7000000,0.,7000000);
   sprintf(histName,"h1_i_All_%d",i);
   h1_i_All[i] = new TH1D(histName,"W_i_All",7000000,0.,7000000);
   sprintf(histName,"h1_i_other_%d",i);
   h1_i_other[i] = new TH1D(histName,"W_i_other",7000000,0.,7000000);
   sprintf(histName,"h1_i_Side_%d",i);
   h1_i_Side[i] = new TH1D(histName,"W_i_Side",7000000,0.,7000000);
   sprintf(histName,"h1_W_Neu_All_%d",i);
   h1_W_Neu_All[i] = new TH1D(histName,"W_Neu_pt_All",50,0.,100);
   sprintf(histName,"h1_W_Neu_pt_Side_%d",i);
   h1_W_Neu_pt_Side[i] = new TH1D(histName,"h1_W_Neu_pt_Side_check",50,0.,100);
   sprintf(histName,"h1_W_Neu_ToTal_beforeTrigger_%d",i);
   h1_W_Neu_pt_ToTal_beforeTrigger[i] = new TH1D(histName,"h1_W_Neu_pt_ToTal_beforeTrigger_check",50,0.,100);
   sprintf(histName,"h1_W_Neu_ToTal_%d",i);
   h1_W_Neu_pt_ToTal[i] = new TH1D(histName,"h1_W_Neu_pt_ToTal_check",50,0.,100);
   sprintf(histName,"h1_W_Neu_other_%d",i);
   h1_W_Neu_other[i] = new TH1D(histName,"h1_W_Neu_other_check",50,0.,100);
   sprintf(histName,"h1_W_Neu_AddElectron_%d",i);
   h1_W_Neu_AddElectron[i] = new TH1D(histName,"h1_W_Neu_AddElectron",50,0.,100);
   }
  }
  //cut value check.
   h1_check_iw = new TH1D("h1_check_iw","h1_cutcheck_iw",10000,-2,2);
   h1_check_side_iw = new TH1D("h1_check_side_iw","h1_cutcheck_side_iw",10000,-2,2);
   h1_check_pt = new TH1D("h1_check_pt","h1_cutcheck_pt",100,0.,100);
   h1_check_side_pt = new TH1D("h1_check_side_pt","h1_cutcheck_side_pt",100,0.,100);
   h1_check_sigmaIetaIeta = new TH1D("h1_check_sigmaIetaIeta","h1_cutcheck_sigmaIetaIeta",100000,-1,1);
   h1_check_side_sigmaIetaIeta = new TH1D("h1_check_side_sigmaIetaIeta","h1_cutcheck_side_sigmaIetaIeta",100000,-1,1);
   h1_check_dEtaIn = new TH1D("h1_check_dEtaIn","h1_cutcheck_dEtaIn",100000,-1,1);
   h1_check_side_dEtaIn = new TH1D("h1_check_side_dEtaIn","h1_cutcheck_side_dEtaIn",100000,-1,1);
   h1_check_dPhiin = new TH1D("h1_check_dPhiin","h1_cutcheck_dPhiin",100000,-1,1);
   h1_check_side_dPhiin = new TH1D("h1_check_side_dPhiin","h1_cutcheck_side_dPhiin",100000,-1,1);
   h1_check_HoverE = new TH1D("h1_check_HoverE","h1_cutcheck_HoverE",100000,-1,1);
   h1_check_side_HoverE = new TH1D("h1_check_side_HoverE","h1_cutcheck_side_HoverE",100000,-1,1);
   h1_check_dxy = new TH1D("h1_check_dxy","h1_cutcheck_dxy",100000,-1,1);
   h1_check_side_dxy = new TH1D("h1_check_side_dxy","h1_cutcheck_side_dxy",100000,-1,1);
   h1_check_dz = new TH1D("h1_check_dz","h1_cutcheck_dz",100000,-1,1);
   h1_check_side_dz = new TH1D("h1_check_side_dz","h1_cutcheck_side_dz",100000,-1,1);
   h1_check_InvE_InvP = new TH1D("h1_check_InvE_InvP","h1_cutcheck_InvE_InvP",100000,-1,1);
   h1_check_side_InvE_InvP = new TH1D("h1_check_side_InvE_InvP","h1_cutcheck_side_InvE_InvP",100000,-1,1);
   h1_check_mHits = new TH1D("h1_check_mHits","h1_cutcheck_mHits",100000,-1,1);
   h1_check_side_mHits = new TH1D("h1_check_side_mHits","h1_cutcheck_side_mHits",100000,-1,1);
   h1_check_lep_eta = new TH1D("h1_check_lep_eta","h1_cutcheck_lep_eta",1000,-2.6,2.6);
   h1_check_side_lep_eta = new TH1D("h1_check_side_lep_eta","h1_cutcheck_side_lep_eta",1000,-2.6,2.6);

   Notify();
}

/*
WEleQ::WEleQ(TTree *WEleQTree,TTree *WLepTree, double lumiweight,TString OutFileName_, TString mode_, TString AnaChannel_, int etaRange_) : fChain(0)
{
  cout<<"WEleQ constructor"<<endl;
  cout<<"initialization for bins"<<endl;

  wqaMetMXBins[0] = 0.2; wqaMetMXBins[1] = 0.4; wqaMetMXBins[2] = 0.6; wqaMetMXBins[3] = 0.8; wqaMetMXBins[4] = 1.0;
     wqaMetMXBins[5] = 1.2; wqaMetMXBins[6] = 1.4; wqaMetMXBins[7] = 1.6; wqaMetMXBins[8] = 1.8; wqaMetMXBins[9] = 2.0;
        wqaMetMXBins[10] = 2.2; wqaMetMXBins[11] = 2.4;

  wqaMetMNBins[0] = 0.0; wqaMetMNBins[1] = 0.2; wqaMetMNBins[2] = 0.4; wqaMetMNBins[3] = 0.6;  wqaMetMNBins[4] = 0.8;
	      wqaMetMNBins[5] = 1.0; wqaMetMNBins[6] = 1.2; wqaMetMNBins[7] = 1.4; wqaMetMNBins[8] = 1.6;  wqaMetMNBins[9] = 1.8;
	         wqaMetMNBins[10] = 2.0; wqaMetMNBins[11] = 2.2;
 if (WEleQTree == 0 || WLepTree == 0) {
   cout<<"Usage: WEleQ(TTree*, TTree*) "<<endl;
   }else{
     cout<<"WEleQ.h: initializing the trees"<<endl;
     LumiWeight = lumiweight;
     OutFileName = OutFileName_;
     Mode = mode_;
     AnaChannel = AnaChannel_;
     ETARANGE = etaRange_;
     Init(WEleQTree);
   }
}
*/
  WEleQ::~WEleQ()
  {
    if (!fChain) return;
    delete fChain->GetCurrentFile();
  }
  
  Int_t WEleQ::GetEntry(Long64_t entry)
  {
    // Read contents of entry.
    if (!fChain) return 0;
    return fChain->GetEntry(entry);
  }

  Long64_t WEleQ::LoadTree(Long64_t entry)
  {
    if (!fChain) return -5;
    Long64_t centry = fChain->LoadTree(entry);
    if (centry < 0) return centry;
    if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
    }
    return centry;
  }

  Bool_t WEleQ::Notify()
  {
    return kTRUE;
  }

  void WEleQ::Show(Long64_t entry)
  {
    if (!fChain) return;
    fChain->Show(entry);
  }

   Int_t WEleQ::ElectronCutHighPUToTal(int i)
   {
     if((*W_Lept1_pt)[i] < 35) return -1;
     if(fabs((*W_Lept1_etaSC)[i])>2.5) return -1;
     if(fabs((*W_Lept1_etaSC)[i])>1.4442 && fabs((*W_Lept1_etaSC)[i])<1.566)return -1;
     if( fabs( (*W_Lept1_etaSC)[i]) < 1.4442)
     {
       if( (*W_Lept1_sigmaIEtaIEta)[i] > 0.01 ) return -1;
       if( fabs((*W_Lept1_dEtaIn)[i]) == 0.004 ) return -1;
       if( fabs((*W_Lept1_dPhiIn)[i]) == 0.06 ) return -1;
       if( (*W_Lept1_HoverE)[i] > 0.12 ) return -1;
       if( fabs((*W_Lept1_dxy)[i]) > 0.02 ) return -1;
       if( fabs((*W_Lept1_dz)[i]) > 0.1 ) return -1;
       if( fabs((*W_Lept1_InvEminusInvP)[i]) > 0.05 ) return -1;
       if( fabs((*W_Lept1_mHits)[i]) > 1) return -1;
     } else{
       if( (*W_Lept1_sigmaIEtaIEta)[i] > 0.03 ) return -1;
       if( fabs((*W_Lept1_dEtaIn)[i])  == 0.007 ) return -1;
       if( fabs((*W_Lept1_dPhiIn)[i])  == 0.03 ) return -1;
       if( (*W_Lept1_HoverE)[i] > 0.1 ) return -1;
       if( fabs((*W_Lept1_dxy)[i]) > 0.02 ) return -1;
       if( fabs((*W_Lept1_dz)[i]) > 0.1 ) return -1;
       if( fabs((*W_Lept1_InvEminusInvP)[i]) > 0.05) return -1;
       if( fabs((*W_Lept1_mHits)[i]) > 1) return -1;
     }

       if( (*W_Lept1_hasConversion)[i] ) return -1;
       if( (*W_Lept1_relIsoRho03)[i] > 0.15 ) return -1;

       return 1;
   }

   Int_t WEleQ::ElectronCutHighPU(int i)
   {
     //////////////  Ele   V5 =======================================
     //double RelComIsoEB = (*W_Lept1_RelisolPtTrks03)[i]+max(0.,((*W_Lept1_RelisoEm03)[i]*(*W_Lept1_pt)[i])-1.)+(*W_Lept1_RelisoHad03)[i];
     //double RelComIsoEE = (*W_Lept1_RelisolPtTrks03)[i]+(*W_Lept1_RelisoEm03)[i]+(*W_Lept1_RelisoHad03)[i];
     if((*W_Lept1_pt)[i] < 35) return -1;
     //if((*W_Lept1_pt)[i] < 30 || (*W_Lept1_pt)[i] > 35) return -1;
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
       //if( fabs((*W_Lept1_mHits)[i]) > 1) return -1;
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
	 //if( fabs((*W_Lept1_mHits)[i]) > 1) return -1;
	 if( fabs((*W_Lept1_mHits)[i]) > 1) return -1;

	 //# Detector based Isolation. for WP80 Variable if(RelComIsoEE>0.06)
	 //return -1;
         //if((*W_Lept1_RelisolPtTrks03)[i] > 0.05) return -1;
         //if((*W_Lept1_RelisoEm03)[i] > 0.1) return -1;
         //if((*W_Lept1_RelisoHad03)[i] > 0.1) return -1;
     }

     if( (*W_Lept1_hasConversion)[i] ) return -1;
     if( (*W_Lept1_relIsoRho03)[i] > 0.15 ) return -1;

     return 1;
   }


   Int_t WEleQ::ElectronCutSideHighPU(int i)
   {
     //double RelComIsoEB = (*W_Lept1_RelisolPtTrks03)[i]+max(0.,((*W_Lept1_RelisoEm03)[i]*(*W_Lept1_pt)[i])-1.)+(*W_Lept1_RelisoHad03)[i];
    // double RelComIsoEE = (*W_Lept1_RelisolPtTrks03)[i]+(*W_Lept1_RelisoEm03)[i]+(*W_Lept1_RelisoHad03)[i]; 
    if((*W_Lept1_pt)[i] < 35) return -1;
    //if((*W_Lept1_pt)[i] < 30 || (*W_Lept1_pt)[i] > 35) return -1;
     
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



   Int_t WEleQ::AddElectronCutHighPU(int i)
   {

     if((*W_Lept1_pt)[i] < 20) return -1;
     if(fabs((*W_Lept1_etaSC)[i])>2.5) return -1;
     if(fabs((*W_Lept1_etaSC)[i])>1.4442 && fabs((*W_Lept1_etaSC)[i]) < 1.566) return -1;
     
     if( fabs( (*W_Lept1_etaSC)[i]) < 1.4442)
     {
	 if( (*W_Lept1_sigmaIEtaIEta)[i] > 0.01 ) return -1;
	 if( fabs ((*W_Lept1_dEtaIn)[i]) > 0.007 ) return -1;
	 if( fabs ((*W_Lept1_dPhiIn)[i]) > 0.8 ) return -1;
	 if( (*W_Lept1_HoverE)[i] > 0.15 ) return -1;
	 if( fabs((*W_Lept1_dxy)[i]) > 0.04 ) return -1;
	 if( fabs((*W_Lept1_dz)[i]) > 0.2 ) return -1;
     } else{
	 if( (*W_Lept1_sigmaIEtaIEta)[i] > 0.03 ) return -1;
	 if( fabs((*W_Lept1_dEtaIn)[i]) > 0.01 ) return -1;
	 if( fabs( (*W_Lept1_dPhiIn)[i]) > 0.7 ) return -1;
       //          if( (*W_Lept1_HoverE)[i] > 0.10 ) return -1;
	 if( fabs((*W_Lept1_dxy)[i]) > 0.04 ) return -1;
	 if( fabs((*W_Lept1_dz)[i]) > 0.2 ) return -1;
     }

     if( (*W_Lept1_relIsoRho03)[i] > 0.15 ) return -1;

     return 1;
   }


  Int_t WEleQ::InitVar4Evt()
  {
    wCand.size = W_pt->size();
    wCand.pt=0;w_pt_side=0;w_acop=0;
    wCand.Mt=0;
    wCand.Met=0;
    wCand.Met_side=0;
    wCand.genIdx=-999;
    wCand.charge=0;
    wCand.lep_pt = 0;
    wCand.lep_phi = 0;
    wCand.lep_eta = 0;
    wCand.lep_etaSC = 0;
    W_pass=0;
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
    u1W=-999;u2W=-999;u3W=-999;
    //genInfo.W_MCtruth = 0;
    genInfo.BornW_pt = 0;
    genInfo.PostW_pt = 0;
    return 0;
  }

#endif // #ifdef WEleQ_cxx


