// $Id: wLeptNeuBranchVars.h,v 1.9 2013/09/13 00:09:32 salee Exp $
//
//
//#include <vector>
#include "TTree.h"
#include "TLorentzVector.h"

#define Triggers	(100)

using namespace std;
class TT2Had
{
public:

  int nIdJets;


  void Register(TTree *tree)
  {
    tree->Branch("TT_nIdJets"		,&nIdJets	,"nIdJets/i");
  }
};

