//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Jun  7 20:15:57 2012 by ROOT version 5.32/00
// from TChain Muons/tree/
//////////////////////////////////////////////////////////

#ifndef WMuons_h
#define WMuons_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

// Header file for the classes stored in the TTree if any.
#include <vector>
#include <vector>

// Fixed size dimensions of array or collections stored in the TTree if any.

class WMuons {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   UInt_t          EVENT;
   UInt_t          RUN;
   UInt_t          LUMI;
   UInt_t          multiplicity;
   vector<double>  *pt;
   vector<double>  *eta;
   vector<double>  *phi;
   vector<double>  *charge;
   vector<int>     *isGlobal;
   vector<int>     *muonMatchStations;
   vector<double>  *dB;
   vector<double>  *dz;
   vector<double>  *globalNormChi2;
   vector<int>     *muonHits;
   vector<int>     *trkLayers;
   vector<int>     *trackerHits;
   vector<int>     *pixelHits;
   vector<double>  *chIso03;
   vector<double>  *nhIso03;
   vector<double>  *phIso03;
   vector<double>  *pcIso03;
   vector<double>  *chIso04;
   vector<double>  *nhIso04;
   vector<double>  *phIso04;
   vector<double>  *pcIso04;
   vector<double>  *trackIso;
   vector<double>  *ecalIso;
   vector<double>  *hcalIso;

   // List of branches
   TBranch        *b_EVENT;   //!
   TBranch        *b_RUN;   //!
   TBranch        *b_LUMI;   //!
   TBranch        *b_multiplicity;   //!
   TBranch        *b_pt;   //!
   TBranch        *b_eta;   //!
   TBranch        *b_phi;   //!
   TBranch        *b_charge;   //!
   TBranch        *b_isGlobal;   //!
   TBranch        *b_muonMatchStations;   //!
   TBranch        *b_dB;   //!
   TBranch        *b_dz;   //!
   TBranch        *b_globalNormChi2;   //!
   TBranch        *b_muonHits;   //!
   TBranch        *b_trkLayers;   //!
   TBranch        *b_trackerHits;   //!
   TBranch        *b_pixelHits;   //!
   TBranch        *b_chIso03;   //!
   TBranch        *b_nhIso03;   //!
   TBranch        *b_phIso03;   //!
   TBranch        *b_pcIso03;   //!
   TBranch        *b_chIso04;   //!
   TBranch        *b_nhIso04;   //!
   TBranch        *b_phIso04;   //!
   TBranch        *b_pcIso04;   //!
   TBranch        *b_trackIso;   //!
   TBranch        *b_ecalIso;   //!
   TBranch        *b_hcalIso;   //!

   //============================================//
   //Change upto here whenever you change leaves//
   //============================================//

   WMuons();
   //WMuons(TTree *tree=0);
   virtual ~WMuons();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#define WMuons_cxx
#ifdef WMuons_cxx


WMuons::WMuons()
//WMuons::WMuons(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
/*********************
   if (tree == 0) {

      cout<<"Usage: WMuons((TTree*) "<<endl;
   }
   else
   {
     Init(tree);
   }
   ********************/
}

WMuons::~WMuons()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t WMuons::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t WMuons::LoadTree(Long64_t entry)
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

void WMuons::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   pt = 0;
   eta = 0;
   phi = 0;
   charge = 0;
   isGlobal = 0;
   muonMatchStations = 0;
   dB = 0;
   dz = 0;
   globalNormChi2 = 0;
   muonHits = 0;
   trkLayers = 0;
   trackerHits = 0;
   pixelHits = 0;
   chIso03 = 0;
   nhIso03 = 0;
   phIso03 = 0;
   pcIso03 = 0;
   chIso04 = 0;
   nhIso04 = 0;
   phIso04 = 0;
   pcIso04 = 0;
   trackIso = 0;
   ecalIso = 0;
   hcalIso = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("EVENT", &EVENT, &b_EVENT);
   fChain->SetBranchAddress("RUN", &RUN, &b_RUN);
   fChain->SetBranchAddress("LUMI", &LUMI, &b_LUMI);
   fChain->SetBranchAddress("multiplicity", &multiplicity, &b_multiplicity);
   fChain->SetBranchAddress("pt", &pt, &b_pt);
   fChain->SetBranchAddress("eta", &eta, &b_eta);
   fChain->SetBranchAddress("phi", &phi, &b_phi);
   fChain->SetBranchAddress("charge", &charge, &b_charge);
   fChain->SetBranchAddress("isGlobal", &isGlobal, &b_isGlobal);
   fChain->SetBranchAddress("muonMatchStations", &muonMatchStations, &b_muonMatchStations);
   fChain->SetBranchAddress("dB", &dB, &b_dB);
   fChain->SetBranchAddress("dz", &dz, &b_dz);
   fChain->SetBranchAddress("globalNormChi2", &globalNormChi2, &b_globalNormChi2);
   fChain->SetBranchAddress("muonHits", &muonHits, &b_muonHits);
   fChain->SetBranchAddress("trkLayers", &trkLayers, &b_trkLayers);
   fChain->SetBranchAddress("trackerHits", &trackerHits, &b_trackerHits);
   fChain->SetBranchAddress("pixelHits", &pixelHits, &b_pixelHits);
   fChain->SetBranchAddress("chIso03", &chIso03, &b_chIso03);
   fChain->SetBranchAddress("nhIso03", &nhIso03, &b_nhIso03);
   fChain->SetBranchAddress("phIso03", &phIso03, &b_phIso03);
   fChain->SetBranchAddress("pcIso03", &pcIso03, &b_pcIso03);
   fChain->SetBranchAddress("chIso04", &chIso04, &b_chIso04);
   fChain->SetBranchAddress("nhIso04", &nhIso04, &b_nhIso04);
   fChain->SetBranchAddress("phIso04", &phIso04, &b_phIso04);
   fChain->SetBranchAddress("pcIso04", &pcIso04, &b_pcIso04);
   fChain->SetBranchAddress("trackIso", &trackIso, &b_trackIso);
   fChain->SetBranchAddress("ecalIso", &ecalIso, &b_ecalIso);
   fChain->SetBranchAddress("hcalIso", &hcalIso, &b_hcalIso);
   Notify();
}

Bool_t WMuons::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void WMuons::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t WMuons::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}

void WMuons::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L WMuons.C
//      Root > WMuons t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
   }
}

#endif // #ifdef WMuons_cxx
