//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Apr  1 18:40:51 2014 by ROOT version 5.32/00
// from TChain MonoPhoton/tree/
//////////////////////////////////////////////////////////

#ifndef MonoPhotonNT_h
#define MonoPhotonNT_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <vector>
#include <vector>

// Fixed size dimensions of array or collections stored in the TTree if any.

class MonoPhotonNT {
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
   vector<double>  *Pho_pt;
   vector<double>  *Pho_eta;

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
   TBranch        *b_Pho_pt;   //!
   TBranch        *b_Pho_eta;   //!

   MonoPhotonNT(TTree *tree=0);
   virtual ~MonoPhotonNT();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef MonoPhotonNT_cxx
MonoPhotonNT::MonoPhotonNT(TTree *tree) : fChain(0) 
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
      f->GetObject("MonoPhoton/tree",tree);

#else // SINGLE_TREE

      // The following code should be used if you want this class to access a chain
      // of trees.
      TChain * chain = new TChain("MonoPhoton/tree","");
      chain->Add("/d1/scratch/jungmin/crab/CMSSW_5_3_14_patch1/src/TerraNova/Analysis/EventSelection/include/OneSampleTest/MonoPhoton.root/MonoPhoton/tree");
      tree = chain;
#endif // SINGLE_TREE

   }
   Init(tree);
}

MonoPhotonNT::~MonoPhotonNT()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t MonoPhotonNT::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t MonoPhotonNT::LoadTree(Long64_t entry)
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

void MonoPhotonNT::Init(TTree *tree)
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
   Pho_pt = 0;
   Pho_eta = 0;
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
   fChain->SetBranchAddress("Pho_pt", &Pho_pt, &b_Pho_pt);
   fChain->SetBranchAddress("Pho_eta", &Pho_eta, &b_Pho_eta);
   Notify();
}

Bool_t MonoPhotonNT::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void MonoPhotonNT::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t MonoPhotonNT::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef MonoPhotonNT_cxx
