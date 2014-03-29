// $Id: wLeptNeuBranchVars.h,v 1.9 2013/09/13 00:09:32 salee Exp $
//
//
//#include <vector>
#include "TTree.h"
#include "TLorentzVector.h"

#define Triggers	(100)

using namespace std;

typedef struct
{
  int version;
  int L1prescale;
  int L1fired;
  int HLTprescale;
  int fired;
} TrigStruct;

class TrigBranches
{
  public:
    string TrigNames[Triggers];
    TrigStruct trigState[Triggers];
    void Register(TTree *tree, int iTrig)
    {
      const char* branchName=TrigNames[iTrig].c_str();
      //      tree->Branch(branchName, &trigState[iTrig],"version/I:L1prescale/I:HLTprescale/I:fired/I");
      tree->Branch(branchName, &trigState[iTrig],"version/I:L1prescale/I:L1fired/I:HLTprescale/I:fired/I");
    }
};
class EventBranches
{
public:
  int EVENT;
  int RUN;
  int LUMI;
  int Channel;
  int npileup;
  double weightin;
  double weight;
  double weightplus;
  double weightminus;
  vector<int>* vtx_isFake;
  vector<int>* vtx_ndof;
  vector<double>* vtx_z;
  vector<double>* vtx_Rho;
  double rhoIso;

  void Register(TTree *tree)
  {
    tree->Branch("EVENT"	,&EVENT		,"EVENT/i");
    tree->Branch("RUN"		,&RUN		,"RUN/i");
    tree->Branch("LUMI"		,&LUMI		,"LUMI/i");
    tree->Branch("Channel"	,&Channel	,"Channel/i");
    tree->Branch("npileup"	,&npileup	,"npileup/i");
    tree->Branch("weightin"	,&weightin	,"weightin/d");
    tree->Branch("weight"	,&weight	,"weight/d");
    tree->Branch("weightplus"	,&weightplus	,"weightplus/d");
    tree->Branch("weightminus"	,&weightminus	,"weightminus/d");
    tree->Branch("rhoIso"	,&rhoIso	,"rhoIso/d");

    tree->Branch("vtx_isFake"	,&vtx_isFake);
    tree->Branch("vtx_ndof"	,&vtx_ndof);
    tree->Branch("vtx_z"	,&vtx_z);
    tree->Branch("vtx_Rho"	,&vtx_Rho);
  }
};

class FSRphoton
{
  public:
    double	weightFSR;
    void Register(TTree *tree)
    {
      tree->Branch("weightFSR", &weightFSR);
    }
};



