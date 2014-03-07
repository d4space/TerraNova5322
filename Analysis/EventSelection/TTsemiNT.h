//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Mar  7 15:53:36 2014 by ROOT version 5.34/14
// from TChain TTsemiLept/tree/
//////////////////////////////////////////////////////////

#ifndef TTsemiNT_h
#define TTsemiNT_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <vector>
#include <vector>
#include <vector>

// Fixed size dimensions of array or collections stored in the TTree if any.

class TTsemiNT {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   UInt_t          EVENT;
   UInt_t          RUN;
   UInt_t          LUMI;
   UInt_t          Channel;
   UInt_t          npileup;
   Double_t        weightin;
   Double_t        weight;
   Double_t        weightplus;
   Double_t        weightminus;
   Double_t        rhoIso;
   vector<int>     *vtx_isFake;
   vector<int>     *vtx_ndof;
   vector<double>  *vtx_z;
   vector<double>  *vtx_Rho;
   Int_t           HLT_Ele22_CaloIdL_CaloIsoVL_version;
   Int_t           HLT_Ele22_CaloIdL_CaloIsoVL_L1prescale;
   Int_t           HLT_Ele22_CaloIdL_CaloIsoVL_L1fired;
   Int_t           HLT_Ele22_CaloIdL_CaloIsoVL_HLTprescale;
   Int_t           HLT_Ele22_CaloIdL_CaloIsoVL_fired;
   Int_t           HLT_Ele27_WP80_version;
   Int_t           HLT_Ele27_WP80_L1prescale;
   Int_t           HLT_Ele27_WP80_L1fired;
   Int_t           HLT_Ele27_WP80_HLTprescale;
   Int_t           HLT_Ele27_WP80_fired;
   Int_t           HLT_Mu15_eta2p1_version;
   Int_t           HLT_Mu15_eta2p1_L1prescale;
   Int_t           HLT_Mu15_eta2p1_L1fired;
   Int_t           HLT_Mu15_eta2p1_HLTprescale;
   Int_t           HLT_Mu15_eta2p1_fired;
   Double_t        pfMEt_x;
   Double_t        pfMEt_y;
   Double_t        pfMEtSumEt;
   Double_t        pfMEtNeuEM;
   Double_t        pfMEtNeuHad;
   Double_t        pfMEtChHad;
   Double_t        pfMEtChEM;
   Double_t        pfMEtMu;
   Double_t        NoPuMEt_x;
   Double_t        NoPuMEt_y;
   Double_t        NoPuMEtSumEt;
   Double_t        NoPuMEtNeuEM;
   Double_t        NoPuMEtNeuHad;
   Double_t        NoPuMEtChHad;
   Double_t        NoPuMEtChEM;
   Double_t        NoPuMEtMu;
   Double_t        MVaMEt_x;
   Double_t        MVaMEt_y;
   Double_t        MVaMEtSumEt;
   Double_t        MVaMEtNeuEM;
   Double_t        MVaMEtNeuHad;
   Double_t        MVaMEtChHad;
   Double_t        MVaMEtChEM;
   Double_t        MVaMEtMu;
   Double_t        genMEtTrue_x;
   Double_t        genMEtTrue_y;
   Double_t        genMEtTrueSumEt;
   Double_t        genMEtTrueNeuEM;
   Double_t        genMEtTrueNeuHad;
   Double_t        genMEtTrueChHad;
   Double_t        genMEtTrueChEM;
   Double_t        genMEtTrueMu;
   Double_t        genMEtCalo_x;
   Double_t        genMEtCalo_y;
   Double_t        genMEtCaloSumEt;
   Double_t        genMEtCaloNeuEM;
   Double_t        genMEtCaloNeuHad;
   Double_t        genMEtCaloChHad;
   Double_t        genMEtCaloChEM;
   Double_t        genMEtCaloMu;
   Double_t        genMEtCaloAndNonPrompt_x;
   Double_t        genMEtCaloAndNonPrompt_y;
   Double_t        genMEtCaloAndNonPromptSumEt;
   Double_t        genMEtCaloAndNonPromptNeuEM;
   Double_t        genMEtCaloAndNonPromptNeuHad;
   Double_t        genMEtCaloAndNonPromptChHad;
   Double_t        genMEtCaloAndNonPromptChEM;
   Double_t        genMEtCaloAndNonPromptMu;
   vector<double>  *TT_Lept1_chIso03;
   vector<double>  *TT_Lept1_chIso04;
   vector<double>  *TT_Lept1_nhIso03;
   vector<double>  *TT_Lept1_nhIso04;
   vector<double>  *TT_Lept1_phIso03;
   vector<double>  *TT_Lept1_phIso04;
   vector<double>  *TT_Lept1_pcIso03;
   vector<double>  *TT_Lept1_pcIso04;
   vector<double>  *TT_Lept1_relIsoCom03;
   vector<double>  *TT_Lept1_relIsoCom04;
   vector<double>  *TT_Lept1_relIsoBeta03;
   vector<double>  *TT_Lept1_relIsoBeta04;
   vector<double>  *TT_Lept1_relIsoRho03;
   vector<double>  *TT_Lept1_RelisolPtTrks03;
   vector<double>  *TT_Lept1_RelisoEm03;
   vector<double>  *TT_Lept1_RelisoHad03;
   vector<bool>    *TT_Lept1_isGlobal;
   vector<bool>    *TT_Lept1_isTrker;
   vector<double>  *TT_Lept1_MedComIsoDelBetCorr3Hits;
   vector<double>  *TT_Lept1_decModFind;
   vector<double>  *TT_Lept1_pt;
   vector<double>  *TT_Lept1_et;
   vector<double>  *TT_Lept1_charge;
   vector<double>  *TT_Lept1_eta;
   vector<double>  *TT_Lept1_phi;
   vector<double>  *TT_Lept1_px;
   vector<double>  *TT_Lept1_py;
   vector<double>  *TT_Lept1_pz;
   vector<double>  *TT_Lept1_en;
   vector<int>     *TT_Lept1_matchStations;
   vector<double>  *TT_Lept1_dB;
   vector<double>  *TT_Lept1_dz;
   vector<double>  *TT_Lept1_globalNormChi2;
   vector<double>  *TT_Lept1_muonHits;
   vector<double>  *TT_Lept1_trkLayers;
   vector<double>  *TT_Lept1_trackerHits;
   vector<double>  *TT_Lept1_pixelHits;
   vector<double>  *TT_Lept1_etaSC;
   vector<double>  *TT_Lept1_phiSC;
   vector<double>  *TT_Lept1_dEtaIn;
   vector<double>  *TT_Lept1_dPhiIn;
   vector<double>  *TT_Lept1_sigmaIEtaIEta;
   vector<double>  *TT_Lept1_HoverE;
   vector<double>  *TT_Lept1_fbrem;
   vector<double>  *TT_Lept1_energyEC;
   vector<double>  *TT_Lept1_Pnorm;
   vector<double>  *TT_Lept1_InvEminusInvP;
   vector<double>  *TT_Lept1_dxy;
   vector<double>  *TT_Lept1_AEff03;
   vector<bool>    *TT_Lept1_hasConversion;
   vector<int>     *TT_Lept1_mHits;
   vector<double>  *TT_Lept1_SCcharge;
   vector<double>  *TT_Lept1_TKcharge;
   vector<double>  *TT_Lept1_GSFcharge;
   vector<double>  *TT_Lept1_GsfCtfScPixchargeConsistentcheck;
   vector<int>     *TT_Lept1_genIdxMatch;
   vector<double>  *TT_Lept1_genDeltaR;
   vector<double>  *TT_Lept1_genDPtRel;
   UInt_t          TT_nIdJets;

   // List of branches
   TBranch        *b_EVENT;   //!
   TBranch        *b_RUN;   //!
   TBranch        *b_LUMI;   //!
   TBranch        *b_Channel;   //!
   TBranch        *b_npileup;   //!
   TBranch        *b_weightin;   //!
   TBranch        *b_weight;   //!
   TBranch        *b_weightplus;   //!
   TBranch        *b_weightminus;   //!
   TBranch        *b_rhoIso;   //!
   TBranch        *b_vtx_isFake;   //!
   TBranch        *b_vtx_ndof;   //!
   TBranch        *b_vtx_z;   //!
   TBranch        *b_vtx_Rho;   //!
   TBranch        *b_HLT_Ele22_CaloIdL_CaloIsoVL;   //!
   TBranch        *b_HLT_Ele27_WP80;   //!
   TBranch        *b_HLT_Mu15_eta2p1;   //!
   TBranch        *b_pfMEt_x;   //!
   TBranch        *b_pfMEt_y;   //!
   TBranch        *b_pfMEtSumEt;   //!
   TBranch        *b_pfMEtNeuEM;   //!
   TBranch        *b_pfMEtNeuHad;   //!
   TBranch        *b_pfMEtChHad;   //!
   TBranch        *b_pfMEtChEM;   //!
   TBranch        *b_pfMEtMu;   //!
   TBranch        *b_NoPuMEt_x;   //!
   TBranch        *b_NoPuMEt_y;   //!
   TBranch        *b_NoPuMEtSumEt;   //!
   TBranch        *b_NoPuMEtNeuEM;   //!
   TBranch        *b_NoPuMEtNeuHad;   //!
   TBranch        *b_NoPuMEtChHad;   //!
   TBranch        *b_NoPuMEtChEM;   //!
   TBranch        *b_NoPuMEtMu;   //!
   TBranch        *b_MVaMEt_x;   //!
   TBranch        *b_MVaMEt_y;   //!
   TBranch        *b_MVaMEtSumEt;   //!
   TBranch        *b_MVaMEtNeuEM;   //!
   TBranch        *b_MVaMEtNeuHad;   //!
   TBranch        *b_MVaMEtChHad;   //!
   TBranch        *b_MVaMEtChEM;   //!
   TBranch        *b_MVaMEtMu;   //!
   TBranch        *b_genMEtTrue_x;   //!
   TBranch        *b_genMEtTrue_y;   //!
   TBranch        *b_genMEtTrueSumEt;   //!
   TBranch        *b_genMEtTrueNeuEM;   //!
   TBranch        *b_genMEtTrueNeuHad;   //!
   TBranch        *b_genMEtTrueChHad;   //!
   TBranch        *b_genMEtTrueChEM;   //!
   TBranch        *b_genMEtTrueMu;   //!
   TBranch        *b_genMEtCalo_x;   //!
   TBranch        *b_genMEtCalo_y;   //!
   TBranch        *b_genMEtCaloSumEt;   //!
   TBranch        *b_genMEtCaloNeuEM;   //!
   TBranch        *b_genMEtCaloNeuHad;   //!
   TBranch        *b_genMEtCaloChHad;   //!
   TBranch        *b_genMEtCaloChEM;   //!
   TBranch        *b_genMEtCaloMu;   //!
   TBranch        *b_genMEtCaloAndNonPrompt_x;   //!
   TBranch        *b_genMEtCaloAndNonPrompt_y;   //!
   TBranch        *b_genMEtCaloAndNonPromptSumEt;   //!
   TBranch        *b_genMEtCaloAndNonPromptNeuEM;   //!
   TBranch        *b_genMEtCaloAndNonPromptNeuHad;   //!
   TBranch        *b_genMEtCaloAndNonPromptChHad;   //!
   TBranch        *b_genMEtCaloAndNonPromptChEM;   //!
   TBranch        *b_genMEtCaloAndNonPromptMu;   //!
   TBranch        *b_TT_Lept1_chIso03;   //!
   TBranch        *b_TT_Lept1_chIso04;   //!
   TBranch        *b_TT_Lept1_nhIso03;   //!
   TBranch        *b_TT_Lept1_nhIso04;   //!
   TBranch        *b_TT_Lept1_phIso03;   //!
   TBranch        *b_TT_Lept1_phIso04;   //!
   TBranch        *b_TT_Lept1_pcIso03;   //!
   TBranch        *b_TT_Lept1_pcIso04;   //!
   TBranch        *b_TT_Lept1_relIsoCom03;   //!
   TBranch        *b_TT_Lept1_relIsoCom04;   //!
   TBranch        *b_TT_Lept1_relIsoBeta03;   //!
   TBranch        *b_TT_Lept1_relIsoBeta04;   //!
   TBranch        *b_TT_Lept1_relIsoRho03;   //!
   TBranch        *b_TT_Lept1_RelisolPtTrks03;   //!
   TBranch        *b_TT_Lept1_RelisoEm03;   //!
   TBranch        *b_TT_Lept1_RelisoHad03;   //!
   TBranch        *b_TT_Lept1_isGlobal;   //!
   TBranch        *b_TT_Lept1_isTrker;   //!
   TBranch        *b_TT_Lept1_MedComIsoDelBetCorr3Hits;   //!
   TBranch        *b_TT_Lept1_decModFind;   //!
   TBranch        *b_TT_Lept1_pt;   //!
   TBranch        *b_TT_Lept1_et;   //!
   TBranch        *b_TT_Lept1_charge;   //!
   TBranch        *b_TT_Lept1_eta;   //!
   TBranch        *b_TT_Lept1_phi;   //!
   TBranch        *b_TT_Lept1_px;   //!
   TBranch        *b_TT_Lept1_py;   //!
   TBranch        *b_TT_Lept1_pz;   //!
   TBranch        *b_TT_Lept1_en;   //!
   TBranch        *b_TT_Lept1_matchStations;   //!
   TBranch        *b_TT_Lept1_dB;   //!
   TBranch        *b_TT_Lept1_dz;   //!
   TBranch        *b_TT_Lept1_globalNormChi2;   //!
   TBranch        *b_TT_Lept1_muonHits;   //!
   TBranch        *b_TT_Lept1_trkLayers;   //!
   TBranch        *b_TT_Lept1_trackerHits;   //!
   TBranch        *b_TT_Lept1_pixelHits;   //!
   TBranch        *b_TT_Lept1_etaSC;   //!
   TBranch        *b_TT_Lept1_phiSC;   //!
   TBranch        *b_TT_Lept1_dEtaIn;   //!
   TBranch        *b_TT_Lept1_dPhiIn;   //!
   TBranch        *b_TT_Lept1_sigmaIEtaIEta;   //!
   TBranch        *b_TT_Lept1_HoverE;   //!
   TBranch        *b_TT_Lept1_fbrem;   //!
   TBranch        *b_TT_Lept1_energyEC;   //!
   TBranch        *b_TT_Lept1_Pnorm;   //!
   TBranch        *b_TT_Lept1_InvEminusInvP;   //!
   TBranch        *b_TT_Lept1_dxy;   //!
   TBranch        *b_TT_Lept1_AEff03;   //!
   TBranch        *b_TT_Lept1_hasConversion;   //!
   TBranch        *b_TT_Lept1_mHits;   //!
   TBranch        *b_TT_Lept1_SCcharge;   //!
   TBranch        *b_TT_Lept1_TKcharge;   //!
   TBranch        *b_TT_Lept1_GSFcharge;   //!
   TBranch        *b_TT_Lept1_GsfCtfScPixchargeConsistentcheck;   //!
   TBranch        *b_TT_Lept1_genIdxMatch;   //!
   TBranch        *b_TT_Lept1_genDeltaR;   //!
   TBranch        *b_TT_Lept1_genDPtRel;   //!
   TBranch        *b_nIdJets;   //!

   TTsemiNT(TTree *tree=0);
   virtual ~TTsemiNT();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef TTsemiNT_cxx
TTsemiNT::TTsemiNT(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {

#ifdef SINGLE_TREE
      // The following code should be used if you want this class to access
      // a single tree instead of a chain
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Memory Directory");
      if (!f || !f->IsOpen()) {
         f = new TFile("Memory Directory");
      }
      f->GetObject("TTsemiLept/tree",tree);

#else // SINGLE_TREE

      // The following code should be used if you want this class to access a chain
      // of trees.
      TChain * chain = new TChain("TTsemiLept/tree","");
      chain->Add("/terranova_1/TestNtuple/TerraTuple.root/TTsemiLept/tree");
      tree = chain;
#endif // SINGLE_TREE

   }
   Init(tree);
}

TTsemiNT::~TTsemiNT()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t TTsemiNT::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t TTsemiNT::LoadTree(Long64_t entry)
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

void TTsemiNT::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   vtx_isFake = 0;
   vtx_ndof = 0;
   vtx_z = 0;
   vtx_Rho = 0;
   TT_Lept1_chIso03 = 0;
   TT_Lept1_chIso04 = 0;
   TT_Lept1_nhIso03 = 0;
   TT_Lept1_nhIso04 = 0;
   TT_Lept1_phIso03 = 0;
   TT_Lept1_phIso04 = 0;
   TT_Lept1_pcIso03 = 0;
   TT_Lept1_pcIso04 = 0;
   TT_Lept1_relIsoCom03 = 0;
   TT_Lept1_relIsoCom04 = 0;
   TT_Lept1_relIsoBeta03 = 0;
   TT_Lept1_relIsoBeta04 = 0;
   TT_Lept1_relIsoRho03 = 0;
   TT_Lept1_RelisolPtTrks03 = 0;
   TT_Lept1_RelisoEm03 = 0;
   TT_Lept1_RelisoHad03 = 0;
   TT_Lept1_isGlobal = 0;
   TT_Lept1_isTrker = 0;
   TT_Lept1_MedComIsoDelBetCorr3Hits = 0;
   TT_Lept1_decModFind = 0;
   TT_Lept1_pt = 0;
   TT_Lept1_et = 0;
   TT_Lept1_charge = 0;
   TT_Lept1_eta = 0;
   TT_Lept1_phi = 0;
   TT_Lept1_px = 0;
   TT_Lept1_py = 0;
   TT_Lept1_pz = 0;
   TT_Lept1_en = 0;
   TT_Lept1_matchStations = 0;
   TT_Lept1_dB = 0;
   TT_Lept1_dz = 0;
   TT_Lept1_globalNormChi2 = 0;
   TT_Lept1_muonHits = 0;
   TT_Lept1_trkLayers = 0;
   TT_Lept1_trackerHits = 0;
   TT_Lept1_pixelHits = 0;
   TT_Lept1_etaSC = 0;
   TT_Lept1_phiSC = 0;
   TT_Lept1_dEtaIn = 0;
   TT_Lept1_dPhiIn = 0;
   TT_Lept1_sigmaIEtaIEta = 0;
   TT_Lept1_HoverE = 0;
   TT_Lept1_fbrem = 0;
   TT_Lept1_energyEC = 0;
   TT_Lept1_Pnorm = 0;
   TT_Lept1_InvEminusInvP = 0;
   TT_Lept1_dxy = 0;
   TT_Lept1_AEff03 = 0;
   TT_Lept1_hasConversion = 0;
   TT_Lept1_mHits = 0;
   TT_Lept1_SCcharge = 0;
   TT_Lept1_TKcharge = 0;
   TT_Lept1_GSFcharge = 0;
   TT_Lept1_GsfCtfScPixchargeConsistentcheck = 0;
   TT_Lept1_genIdxMatch = 0;
   TT_Lept1_genDeltaR = 0;
   TT_Lept1_genDPtRel = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("EVENT", &EVENT, &b_EVENT);
   fChain->SetBranchAddress("RUN", &RUN, &b_RUN);
   fChain->SetBranchAddress("LUMI", &LUMI, &b_LUMI);
   fChain->SetBranchAddress("Channel", &Channel, &b_Channel);
   fChain->SetBranchAddress("npileup", &npileup, &b_npileup);
   fChain->SetBranchAddress("weightin", &weightin, &b_weightin);
   fChain->SetBranchAddress("weight", &weight, &b_weight);
   fChain->SetBranchAddress("weightplus", &weightplus, &b_weightplus);
   fChain->SetBranchAddress("weightminus", &weightminus, &b_weightminus);
   fChain->SetBranchAddress("rhoIso", &rhoIso, &b_rhoIso);
   fChain->SetBranchAddress("vtx_isFake", &vtx_isFake, &b_vtx_isFake);
   fChain->SetBranchAddress("vtx_ndof", &vtx_ndof, &b_vtx_ndof);
   fChain->SetBranchAddress("vtx_z", &vtx_z, &b_vtx_z);
   fChain->SetBranchAddress("vtx_Rho", &vtx_Rho, &b_vtx_Rho);
   fChain->SetBranchAddress("HLT_Ele22_CaloIdL_CaloIsoVL", &HLT_Ele22_CaloIdL_CaloIsoVL_version, &b_HLT_Ele22_CaloIdL_CaloIsoVL);
   fChain->SetBranchAddress("HLT_Ele27_WP80", &HLT_Ele27_WP80_version, &b_HLT_Ele27_WP80);
   fChain->SetBranchAddress("HLT_Mu15_eta2p1", &HLT_Mu15_eta2p1_version, &b_HLT_Mu15_eta2p1);
   fChain->SetBranchAddress("pfMEt_x", &pfMEt_x, &b_pfMEt_x);
   fChain->SetBranchAddress("pfMEt_y", &pfMEt_y, &b_pfMEt_y);
   fChain->SetBranchAddress("pfMEtSumEt", &pfMEtSumEt, &b_pfMEtSumEt);
   fChain->SetBranchAddress("pfMEtNeuEM", &pfMEtNeuEM, &b_pfMEtNeuEM);
   fChain->SetBranchAddress("pfMEtNeuHad", &pfMEtNeuHad, &b_pfMEtNeuHad);
   fChain->SetBranchAddress("pfMEtChHad", &pfMEtChHad, &b_pfMEtChHad);
   fChain->SetBranchAddress("pfMEtChEM", &pfMEtChEM, &b_pfMEtChEM);
   fChain->SetBranchAddress("pfMEtMu", &pfMEtMu, &b_pfMEtMu);
   fChain->SetBranchAddress("NoPuMEt_x", &NoPuMEt_x, &b_NoPuMEt_x);
   fChain->SetBranchAddress("NoPuMEt_y", &NoPuMEt_y, &b_NoPuMEt_y);
   fChain->SetBranchAddress("NoPuMEtSumEt", &NoPuMEtSumEt, &b_NoPuMEtSumEt);
   fChain->SetBranchAddress("NoPuMEtNeuEM", &NoPuMEtNeuEM, &b_NoPuMEtNeuEM);
   fChain->SetBranchAddress("NoPuMEtNeuHad", &NoPuMEtNeuHad, &b_NoPuMEtNeuHad);
   fChain->SetBranchAddress("NoPuMEtChHad", &NoPuMEtChHad, &b_NoPuMEtChHad);
   fChain->SetBranchAddress("NoPuMEtChEM", &NoPuMEtChEM, &b_NoPuMEtChEM);
   fChain->SetBranchAddress("NoPuMEtMu", &NoPuMEtMu, &b_NoPuMEtMu);
   fChain->SetBranchAddress("MVaMEt_x", &MVaMEt_x, &b_MVaMEt_x);
   fChain->SetBranchAddress("MVaMEt_y", &MVaMEt_y, &b_MVaMEt_y);
   fChain->SetBranchAddress("MVaMEtSumEt", &MVaMEtSumEt, &b_MVaMEtSumEt);
   fChain->SetBranchAddress("MVaMEtNeuEM", &MVaMEtNeuEM, &b_MVaMEtNeuEM);
   fChain->SetBranchAddress("MVaMEtNeuHad", &MVaMEtNeuHad, &b_MVaMEtNeuHad);
   fChain->SetBranchAddress("MVaMEtChHad", &MVaMEtChHad, &b_MVaMEtChHad);
   fChain->SetBranchAddress("MVaMEtChEM", &MVaMEtChEM, &b_MVaMEtChEM);
   fChain->SetBranchAddress("MVaMEtMu", &MVaMEtMu, &b_MVaMEtMu);
   fChain->SetBranchAddress("genMEtTrue_x", &genMEtTrue_x, &b_genMEtTrue_x);
   fChain->SetBranchAddress("genMEtTrue_y", &genMEtTrue_y, &b_genMEtTrue_y);
   fChain->SetBranchAddress("genMEtTrueSumEt", &genMEtTrueSumEt, &b_genMEtTrueSumEt);
   fChain->SetBranchAddress("genMEtTrueNeuEM", &genMEtTrueNeuEM, &b_genMEtTrueNeuEM);
   fChain->SetBranchAddress("genMEtTrueNeuHad", &genMEtTrueNeuHad, &b_genMEtTrueNeuHad);
   fChain->SetBranchAddress("genMEtTrueChHad", &genMEtTrueChHad, &b_genMEtTrueChHad);
   fChain->SetBranchAddress("genMEtTrueChEM", &genMEtTrueChEM, &b_genMEtTrueChEM);
   fChain->SetBranchAddress("genMEtTrueMu", &genMEtTrueMu, &b_genMEtTrueMu);
   fChain->SetBranchAddress("genMEtCalo_x", &genMEtCalo_x, &b_genMEtCalo_x);
   fChain->SetBranchAddress("genMEtCalo_y", &genMEtCalo_y, &b_genMEtCalo_y);
   fChain->SetBranchAddress("genMEtCaloSumEt", &genMEtCaloSumEt, &b_genMEtCaloSumEt);
   fChain->SetBranchAddress("genMEtCaloNeuEM", &genMEtCaloNeuEM, &b_genMEtCaloNeuEM);
   fChain->SetBranchAddress("genMEtCaloNeuHad", &genMEtCaloNeuHad, &b_genMEtCaloNeuHad);
   fChain->SetBranchAddress("genMEtCaloChHad", &genMEtCaloChHad, &b_genMEtCaloChHad);
   fChain->SetBranchAddress("genMEtCaloChEM", &genMEtCaloChEM, &b_genMEtCaloChEM);
   fChain->SetBranchAddress("genMEtCaloMu", &genMEtCaloMu, &b_genMEtCaloMu);
   fChain->SetBranchAddress("genMEtCaloAndNonPrompt_x", &genMEtCaloAndNonPrompt_x, &b_genMEtCaloAndNonPrompt_x);
   fChain->SetBranchAddress("genMEtCaloAndNonPrompt_y", &genMEtCaloAndNonPrompt_y, &b_genMEtCaloAndNonPrompt_y);
   fChain->SetBranchAddress("genMEtCaloAndNonPromptSumEt", &genMEtCaloAndNonPromptSumEt, &b_genMEtCaloAndNonPromptSumEt);
   fChain->SetBranchAddress("genMEtCaloAndNonPromptNeuEM", &genMEtCaloAndNonPromptNeuEM, &b_genMEtCaloAndNonPromptNeuEM);
   fChain->SetBranchAddress("genMEtCaloAndNonPromptNeuHad", &genMEtCaloAndNonPromptNeuHad, &b_genMEtCaloAndNonPromptNeuHad);
   fChain->SetBranchAddress("genMEtCaloAndNonPromptChHad", &genMEtCaloAndNonPromptChHad, &b_genMEtCaloAndNonPromptChHad);
   fChain->SetBranchAddress("genMEtCaloAndNonPromptChEM", &genMEtCaloAndNonPromptChEM, &b_genMEtCaloAndNonPromptChEM);
   fChain->SetBranchAddress("genMEtCaloAndNonPromptMu", &genMEtCaloAndNonPromptMu, &b_genMEtCaloAndNonPromptMu);
   fChain->SetBranchAddress("TT_Lept1_chIso03", &TT_Lept1_chIso03, &b_TT_Lept1_chIso03);
   fChain->SetBranchAddress("TT_Lept1_chIso04", &TT_Lept1_chIso04, &b_TT_Lept1_chIso04);
   fChain->SetBranchAddress("TT_Lept1_nhIso03", &TT_Lept1_nhIso03, &b_TT_Lept1_nhIso03);
   fChain->SetBranchAddress("TT_Lept1_nhIso04", &TT_Lept1_nhIso04, &b_TT_Lept1_nhIso04);
   fChain->SetBranchAddress("TT_Lept1_phIso03", &TT_Lept1_phIso03, &b_TT_Lept1_phIso03);
   fChain->SetBranchAddress("TT_Lept1_phIso04", &TT_Lept1_phIso04, &b_TT_Lept1_phIso04);
   fChain->SetBranchAddress("TT_Lept1_pcIso03", &TT_Lept1_pcIso03, &b_TT_Lept1_pcIso03);
   fChain->SetBranchAddress("TT_Lept1_pcIso04", &TT_Lept1_pcIso04, &b_TT_Lept1_pcIso04);
   fChain->SetBranchAddress("TT_Lept1_relIsoCom03", &TT_Lept1_relIsoCom03, &b_TT_Lept1_relIsoCom03);
   fChain->SetBranchAddress("TT_Lept1_relIsoCom04", &TT_Lept1_relIsoCom04, &b_TT_Lept1_relIsoCom04);
   fChain->SetBranchAddress("TT_Lept1_relIsoBeta03", &TT_Lept1_relIsoBeta03, &b_TT_Lept1_relIsoBeta03);
   fChain->SetBranchAddress("TT_Lept1_relIsoBeta04", &TT_Lept1_relIsoBeta04, &b_TT_Lept1_relIsoBeta04);
   fChain->SetBranchAddress("TT_Lept1_relIsoRho03", &TT_Lept1_relIsoRho03, &b_TT_Lept1_relIsoRho03);
   fChain->SetBranchAddress("TT_Lept1_RelisolPtTrks03", &TT_Lept1_RelisolPtTrks03, &b_TT_Lept1_RelisolPtTrks03);
   fChain->SetBranchAddress("TT_Lept1_RelisoEm03", &TT_Lept1_RelisoEm03, &b_TT_Lept1_RelisoEm03);
   fChain->SetBranchAddress("TT_Lept1_RelisoHad03", &TT_Lept1_RelisoHad03, &b_TT_Lept1_RelisoHad03);
   fChain->SetBranchAddress("TT_Lept1_isGlobal", &TT_Lept1_isGlobal, &b_TT_Lept1_isGlobal);
   fChain->SetBranchAddress("TT_Lept1_isTrker", &TT_Lept1_isTrker, &b_TT_Lept1_isTrker);
   fChain->SetBranchAddress("TT_Lept1_MedComIsoDelBetCorr3Hits", &TT_Lept1_MedComIsoDelBetCorr3Hits, &b_TT_Lept1_MedComIsoDelBetCorr3Hits);
   fChain->SetBranchAddress("TT_Lept1_decModFind", &TT_Lept1_decModFind, &b_TT_Lept1_decModFind);
   fChain->SetBranchAddress("TT_Lept1_pt", &TT_Lept1_pt, &b_TT_Lept1_pt);
   fChain->SetBranchAddress("TT_Lept1_et", &TT_Lept1_et, &b_TT_Lept1_et);
   fChain->SetBranchAddress("TT_Lept1_charge", &TT_Lept1_charge, &b_TT_Lept1_charge);
   fChain->SetBranchAddress("TT_Lept1_eta", &TT_Lept1_eta, &b_TT_Lept1_eta);
   fChain->SetBranchAddress("TT_Lept1_phi", &TT_Lept1_phi, &b_TT_Lept1_phi);
   fChain->SetBranchAddress("TT_Lept1_px", &TT_Lept1_px, &b_TT_Lept1_px);
   fChain->SetBranchAddress("TT_Lept1_py", &TT_Lept1_py, &b_TT_Lept1_py);
   fChain->SetBranchAddress("TT_Lept1_pz", &TT_Lept1_pz, &b_TT_Lept1_pz);
   fChain->SetBranchAddress("TT_Lept1_en", &TT_Lept1_en, &b_TT_Lept1_en);
   fChain->SetBranchAddress("TT_Lept1_matchStations", &TT_Lept1_matchStations, &b_TT_Lept1_matchStations);
   fChain->SetBranchAddress("TT_Lept1_dB", &TT_Lept1_dB, &b_TT_Lept1_dB);
   fChain->SetBranchAddress("TT_Lept1_dz", &TT_Lept1_dz, &b_TT_Lept1_dz);
   fChain->SetBranchAddress("TT_Lept1_globalNormChi2", &TT_Lept1_globalNormChi2, &b_TT_Lept1_globalNormChi2);
   fChain->SetBranchAddress("TT_Lept1_muonHits", &TT_Lept1_muonHits, &b_TT_Lept1_muonHits);
   fChain->SetBranchAddress("TT_Lept1_trkLayers", &TT_Lept1_trkLayers, &b_TT_Lept1_trkLayers);
   fChain->SetBranchAddress("TT_Lept1_trackerHits", &TT_Lept1_trackerHits, &b_TT_Lept1_trackerHits);
   fChain->SetBranchAddress("TT_Lept1_pixelHits", &TT_Lept1_pixelHits, &b_TT_Lept1_pixelHits);
   fChain->SetBranchAddress("TT_Lept1_etaSC", &TT_Lept1_etaSC, &b_TT_Lept1_etaSC);
   fChain->SetBranchAddress("TT_Lept1_phiSC", &TT_Lept1_phiSC, &b_TT_Lept1_phiSC);
   fChain->SetBranchAddress("TT_Lept1_dEtaIn", &TT_Lept1_dEtaIn, &b_TT_Lept1_dEtaIn);
   fChain->SetBranchAddress("TT_Lept1_dPhiIn", &TT_Lept1_dPhiIn, &b_TT_Lept1_dPhiIn);
   fChain->SetBranchAddress("TT_Lept1_sigmaIEtaIEta", &TT_Lept1_sigmaIEtaIEta, &b_TT_Lept1_sigmaIEtaIEta);
   fChain->SetBranchAddress("TT_Lept1_HoverE", &TT_Lept1_HoverE, &b_TT_Lept1_HoverE);
   fChain->SetBranchAddress("TT_Lept1_fbrem", &TT_Lept1_fbrem, &b_TT_Lept1_fbrem);
   fChain->SetBranchAddress("TT_Lept1_energyEC", &TT_Lept1_energyEC, &b_TT_Lept1_energyEC);
   fChain->SetBranchAddress("TT_Lept1_Pnorm", &TT_Lept1_Pnorm, &b_TT_Lept1_Pnorm);
   fChain->SetBranchAddress("TT_Lept1_InvEminusInvP", &TT_Lept1_InvEminusInvP, &b_TT_Lept1_InvEminusInvP);
   fChain->SetBranchAddress("TT_Lept1_dxy", &TT_Lept1_dxy, &b_TT_Lept1_dxy);
   fChain->SetBranchAddress("TT_Lept1_AEff03", &TT_Lept1_AEff03, &b_TT_Lept1_AEff03);
   fChain->SetBranchAddress("TT_Lept1_hasConversion", &TT_Lept1_hasConversion, &b_TT_Lept1_hasConversion);
   fChain->SetBranchAddress("TT_Lept1_mHits", &TT_Lept1_mHits, &b_TT_Lept1_mHits);
   fChain->SetBranchAddress("TT_Lept1_SCcharge", &TT_Lept1_SCcharge, &b_TT_Lept1_SCcharge);
   fChain->SetBranchAddress("TT_Lept1_TKcharge", &TT_Lept1_TKcharge, &b_TT_Lept1_TKcharge);
   fChain->SetBranchAddress("TT_Lept1_GSFcharge", &TT_Lept1_GSFcharge, &b_TT_Lept1_GSFcharge);
   fChain->SetBranchAddress("TT_Lept1_GsfCtfScPixchargeConsistentcheck", &TT_Lept1_GsfCtfScPixchargeConsistentcheck, &b_TT_Lept1_GsfCtfScPixchargeConsistentcheck);
   fChain->SetBranchAddress("TT_Lept1_genIdxMatch", &TT_Lept1_genIdxMatch, &b_TT_Lept1_genIdxMatch);
   fChain->SetBranchAddress("TT_Lept1_genDeltaR", &TT_Lept1_genDeltaR, &b_TT_Lept1_genDeltaR);
   fChain->SetBranchAddress("TT_Lept1_genDPtRel", &TT_Lept1_genDPtRel, &b_TT_Lept1_genDPtRel);
   fChain->SetBranchAddress("TT_nIdJets", &TT_nIdJets, &b_nIdJets);
   Notify();
}

Bool_t TTsemiNT::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void TTsemiNT::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t TTsemiNT::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef TTsemiNT_cxx
