//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed May 16 17:32:24 2012 by ROOT version 5.32/00
// from TChain mSUGRAMET/tree/
//////////////////////////////////////////////////////////
//$Log: mSUGRAMET.h,v $
//Revision 1.9  2013/08/19 15:11:26  jungmin
//*** empty log message ***

#ifndef mSUGRAMET_h
#define mSUGRAMET_h

#include <TSystem.h>
#include "mSUGRABase.h"
#include "TProfile.h"

// Fixed size dimensions of array or collections stored in the TTree if any.
class mSUGRAMET: public mSUGRABase {
public :
   mSUGRAMET(TTree *tree=0,double weight=1, TString OutNameBase = "output.root",TString Mode="analysis", TString AnaChannel ="Muon",double WCHARGE=0, bool runOnMC=true, int etaRange_=-999);//Electron
   ~mSUGRAMET();
   virtual void     Loop();
   TH1D* h1_PF_Met[PUrangeBin];
   TH1D* h1_MVA_Met[PUrangeBin];
   TH1D* h1_NoPU_Met[PUrangeBin];
   TH1D* h1_genMEtTrue[PUrangeBin];
   TH2D* h2_pfMET[PUrangeBin];
   TH2D* h2_MVaMET[PUrangeBin];
   TH2D* h2_NoPuMET[PUrangeBin];
   TH2D* h2_pfMET_pxpy;
   TH2D* h2_MVaMET_pxpy;
   TH2D* h2_NoPuMET_pxpy;
protected:
  TFile *myFile;
  int Fill_METs();
  int Fill_METprofiles(); 
  int InitVar(); // Init for Class
   int InitVar4Evt(); // Init for every event
   int VertexCut();
   double CalcEvtWeight();
   //int TTbestSelect();
   int InitHistogram();
   // Member variables
};

#endif

#ifdef mSUGRAMET_cxx


mSUGRAMET::mSUGRAMET(TTree *mSUGRAMETTree, double lumiweight,TString OutNameBase_, TString mode_, TString AnaChannel_,double Wcharge, bool runOnMC,int etaRange_) :
mSUGRABase::mSUGRABase(mSUGRAMETTree,lumiweight,OutNameBase_, mode_, AnaChannel_,Wcharge, runOnMC, etaRange_)
{
  cout<<"Initializing mSUGRAMET variables ========="<<endl;
  // Initialize Variables
  InitVar();
  gSystem->mkdir(mResultDir);
  InitHistogram();
}

mSUGRAMET::~mSUGRAMET()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}
#endif // #ifdef mSUGRAMET_cxx
