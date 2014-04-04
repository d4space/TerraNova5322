#include <TChain.h>
//=============
//  Muon header
//=============
#include "chain_Muon_WpToMuNu_S8.h"
#include "chain_Muon_WmToMuNu_S8.h"
#include "chain_Muon_DYToMuMu_S8.h"
#include "chain_Muon_WToTauNu_S8.h"
#include "chain_Muon_DYToTauTau_S8.h"
#include "chain_Muon_TTJets_S8.h"
#include "chain_Muon_RD_LowPU.h"
#include "chain_Test.h"
//===============
// Electron header
//===============
#include "chain_Electron_WpToEleNu_S8.h"
#include "chain_Electron_WmToEleNu_S8.h"
#include "chain_Electron_DYToEE_S8.h" 
#include "chain_Electron_WToTauNu_S8.h"
#include "chain_Electron_DYToTauTau_S8.h" 
#include "chain_Electron_TTJets_S8.h"
#include "chain_Electron_RD_LowPU.h" 

void SetupTree( TString sample, TChain* chains )
{
  cout<<"SetupTree.h: "<<sample<<endl;
  //=========
  //LowPU
  //=========
  if( sample == "Muon_WpToMuNu_S8"){
    chain_Muon_WpToMuNu_S8(chains);
  }
  else if( sample == "Muon_WmToMuNu_S8"){
    chain_Muon_WmToMuNu_S8(chains);
  }
  else if( sample == "Muon_DYToMuMu_S8")
  {
    chain_Muon_DYToMuMu_S8(chains);
  }
  else if( sample == "Muon_WToTauNu_S8")
  {
    chain_Muon_WToTauNu_S8(chains);
  }
  else if(sample == "Muon_DYToTauTau_S8")
  {
    chain_Muon_DYToTauTau_S8(chains);
  }
  else if(sample == "Muon_TTJets_S8")
  {
    chain_Muon_TTJets_S8(chains);
  }
  else if(sample == "Muon_RD_LowPU")
  {
    chain_Muon_RD_LowPU(chains);
  }
//Electron Scripts
  else if( sample == "Ele_WpToEleNu_S8")
  {
    chain_Electron_WpToEleNu_S8(chains);
  }
  else if( sample == "Ele_WmToEleNu_S8")
  {
    chain_Electron_WmToEleNu_S8(chains);
  }
  else if( sample == "Ele_DYToEE_S8")
  {
    chain_Electron_DYToEE_S8(chains);
  }
  else if( sample == "Ele_WToTauNu_S8")
  {
    chain_Electron_WToTauNu_S8(chains);
  }
  else if(sample == "Ele_DYToTauTau_S8")
  {
    chain_Electron_DYToTauTau_S8(chains);
  }
  else if(sample == "Ele_TTJets_S8")
  {
    chain_Electron_TTJets_S8(chains);
  }
  else if(sample == "Ele_RD_LowPU")
  {
    chain_Electron_RD_LowPU(chains);
  }
  else if(sample == "Test")
  {
    chain_Muon_Test(chains);
  }
  else
  {
    cout<<"[SetupTree.h] Nanigorae? "<<endl;
  }
}
