#include <TChain.h>
//=============
//  Muon header
//=============
#include "chain_Muon_WpToMuNu_S8_Accpt.h"
#include "chain_Muon_WmToMuNu_S8_Accpt.h"
#include "chain_Electron_WpToEleNu_S8_Accpt.h"
#include "chain_Electron_WmToEleNu_S8_Accpt.h"
//===============
// Electron header
//===============

void SetupTreeAccept( TString sample, TChain* chains )
{
  cout<<"SetupTreeAccept.h: "<<sample<<endl;
  //=========
  //LowPU
  //=========
  if( sample == "Muon_WpToMuNu_S8"){
    chain_Muon_WpToMuNu_S8_Accpt(chains);
  }
  else if( sample == "Muon_WmToMuNu_S8"){
    chain_Muon_WmToMuNu_S8_Accpt(chains);
  }
//Electron Scripts
  else if( sample == "Ele_WpToEleNu_S8")
  {
    chain_Electron_WpToEleNu_S8_Accpt(chains);
  }
  else if( sample == "Ele_WmToEleNu_S8")
  {
    chain_Electron_WmToEleNu_S8_Accpt(chains);
  }
  else
  {
    cout<<"[SetupTree.h] Nanigorae? "<<endl;
  }
}
