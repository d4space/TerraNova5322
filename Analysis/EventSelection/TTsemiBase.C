// $Log: TTsemiBase.C,v $
// Revision 1.8  2013/09/13 00:09:32  salee
// *** empty log message ***
//
//   In a ROOT session, you can do:
//      Root > .L TTsemiBase.C
//      Root > TTsemiBase t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

#define TTsemiBase_cxx
//#include <iostream>
//#include <TROOT.h>                        // access to gROOT, entry point to ROOT system
//#include <TSystem.h>                      // interface to OS
#include <TBenchmark.h>                   // class to track macro running statistics
#include <algorithm>
#include "TTsemiBase.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TSystem.h>
#include <TVector2.h>
#include <TLorentzVector.h>
//#include "../Utils/MyTools.hh"	          // various helper functions

#include "Math/PtEtaPhiE4D.h"
#include "Math/PtEtaPhiM4D.h"
#include "Math/LorentzVector.h"

typedef ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiM4D<double> > PtEtaPhiMLorentzVectorD;
typedef PtEtaPhiMLorentzVectorD PtEtaPhiMLorentzVector;
int TTsemiBase::InitVar()
{
  cout<<"Initialize variables at TTsemiBase Class ==================="<<endl;
  mResultDir = OutNameBase+"_"+Mode;

  return 0;
}
void TTsemiBase::Loop()
{
  gBenchmark->Start("TTsemiBase");
  gRandom->SetSeed(0);
//
  if (fChain == 0) return;
   //int Ntries = fChain->GetEntriesFast(); this gives 1234567890 kkk
  Ntries = fChain->GetEntries();
  gBenchmark->Show("TTsemiBase");
}
int TTsemiBase::CheckChannel()
{
  //cout<<"CheckChannel============"<<endl;
  //cout<<AnaChannel<<"\t"<<Channel<<endl;
  if(AnaChannel == "MuonLowPU" )if(fabs(Channel) != GenType::kMuon) return -1;
  if(AnaChannel == "MuonHighPU")if(fabs(Channel) != GenType::kMuon) return-1;
  if(AnaChannel == "ElectronLowPU")if(fabs(Channel) != GenType::kElectron) return-1;
  if(AnaChannel == "ElectronHighPU")if(fabs(Channel) != GenType::kElectron) return-1;
  if(AnaChannel == "TauHighPU")if(fabs(Channel) != GenType::kTau) return-1;
  return 0;
}
int TTsemiBase::TriggerCut()
{
    if(AnaChannel == "MuonLowPU" )if( HLT_Mu15_eta2p1_fired < 1) return -1;
    if(AnaChannel == "ElectronLowPU" )if(HLT_Ele22_CaloIdL_CaloIsoVL_fired<1) return -1;
    if(AnaChannel=="ElectronHighPU")if(HLT_Ele27_WP80_fired<1) return -1;
  return 0;
}
