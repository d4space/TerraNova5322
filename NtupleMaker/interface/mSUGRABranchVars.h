// $Id: wLeptNeuBranchVars.h,v 1.9 2013/09/13 00:09:32 salee Exp $
//
//
//#include <vector>
#include "TTree.h"
#include "TLorentzVector.h"

#define Triggers	(100)

using namespace std;
class mSUGRA
{
public:

  int nIdJets;
  vector<double>*	pt;
  vector<double>*	eta;

  void Register(TTree *tree)
  {
    tree->Branch("nIdJets"		,&nIdJets	,"nIdJets/i");
    tree->Branch("pt"	,&pt);
    tree->Branch("eta"	,&eta);
  }
};

