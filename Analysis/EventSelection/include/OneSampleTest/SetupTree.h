#include <TChain.h>
//=============
//  Test Sample Header
//=============
#include "chain_Test.h"

void SetupTree( TString sample, TChain* chains )
{
  cout<<"SetupTree.h: "<<sample<<endl;
  //=========
  //LowPU
  //=========
  if( sample == "Test"){
    chain_Test(chains);
  }
  else
  {
    cout<<"[SetupTree.h] Nanigorae? "<<endl;
  }
}
