// $Id: wLeptNeuBranchVars.h,v 1.9 2013/09/13 00:09:32 salee Exp $
//
//
//#include <vector>
#include "TTree.h"
#include "TLorentzVector.h"

#define Triggers	(100)

using namespace std;

class METs
{
  public:
    double pfMEt_x, pfMEt_y;
    double NoPuMEt_x, NoPuMEt_y;
    double MVaMEt_x, MVaMEt_y;
    double genMEtTrue_x, genMEtTrue_y;
    double genMEtCalo_x, genMEtCalo_y;
    double genMEtCaloAndNonPrompt_x, genMEtCaloAndNonPrompt_y;
    //TLorentzVector *pfMEt4V;
    //TLorentzVector *NoPuMEt4V;
    //TLorentzVector *MVaMEt4V;
    //TLorentzVector *genMEtTrue4V;
    //TLorentzVector *genMEtCalo4V;
    //TLorentzVector *genMEtCaloAndNonPrompt4V;

    double pfMEtSumEt, pfMEtNeuEM, pfMEtNeuHad, pfMEtChHad, pfMEtChEM, pfMEtMu;
    double NoPuMEtSumEt,NoPuMEtNeuEM,NoPuMEtNeuHad,NoPuMEtChHad,NoPuMEtChEM,NoPuMEtMu;
    double MVaMEtSumEt,MVaMEtNeuEM,MVaMEtNeuHad,MVaMEtChHad,MVaMEtChEM,MVaMEtMu;
    double genMEtTrueSumEt,genMEtTrueNeuEM,genMEtTrueNeuHad,genMEtTrueChHad,genMEtTrueChEM,genMEtTrueMu;
    double genMEtCaloSumEt,genMEtCaloNeuEM,genMEtCaloNeuHad,genMEtCaloChHad,genMEtCaloChEM,genMEtCaloMu;
    double genMEtCaloAndNonPromptSumEt,genMEtCaloAndNonPromptNeuEM,genMEtCaloAndNonPromptNeuHad,genMEtCaloAndNonPromptChHad,genMEtCaloAndNonPromptChEM,genMEtCaloAndNonPromptMu;

    void Register(TTree *tree)
    {
      //tree->Branch("pfMEt4V", &pfMEt4V, int bufsize=3200, splitlevel=99);
      //tree->Branch("pfMEt4V","TLorentzVector", &pfMEt4V);
      //tree->Branch("NoPuMEt4V","TLorentzVector", &NoPuMEt4V);
      //tree->Branch("MVaMEt4V","TLorentzVector", &MVaMEt4V);
      //tree->Branch("genMEtTrue4V","TLorentzVector", &genMEtTrue4V);
      //tree->Branch("genMEtCalo4V","TLorentzVector", &genMEtCalo4V);
      //tree->Branch("genMEtCaloAndNonPrompt4V","TLorentzVector", &genMEtCaloAndNonPrompt4V);
      tree->Branch("pfMEt_x", &pfMEt_x, "pfMEt_x/d");
      tree->Branch("pfMEt_y", &pfMEt_y, "pfMEt_y/d");
      tree->Branch("pfMEtSumEt", &pfMEtSumEt	,"pfMEtSumEt/d");
      tree->Branch("pfMEtNeuEM", &pfMEtNeuEM	,"pfMEtNeuEM/d");
      tree->Branch("pfMEtNeuHad", &pfMEtNeuHad	,"pfMEtNeuHad/d");
      tree->Branch("pfMEtChHad", &pfMEtChHad	,"pfMEtChHad/d");
      tree->Branch("pfMEtChEM", &pfMEtChEM	,"pfMEtChEM/d");
      tree->Branch("pfMEtMu", &pfMEtMu	,"pfMEtMu/d");

      tree->Branch("NoPuMEt_x", &NoPuMEt_x, "NoPuMEt_x/d");
      tree->Branch("NoPuMEt_y", &NoPuMEt_y, "NoPuMEt_y/d");
      tree->Branch("NoPuMEtSumEt",	&NoPuMEtSumEt	,"NoPuMEtSumEt/d");
      tree->Branch("NoPuMEtNeuEM",	&NoPuMEtNeuEM	,"NoPuMEtNeuEM/d");
      tree->Branch("NoPuMEtNeuHad",	&NoPuMEtNeuHad	,"NoPuMEtNeuHad/d");
      tree->Branch("NoPuMEtChHad",	&NoPuMEtChHad	,"NoPuMEtChHad/d");
      tree->Branch("NoPuMEtChEM",	&NoPuMEtChEM	,"NoPuMEtChEM/d");
      tree->Branch("NoPuMEtMu",		&NoPuMEtMu	,"NoPuMEtMu/d");

      tree->Branch("MVaMEt_x",		&MVaMEt_x	,"MVaMEt_x/d");
      tree->Branch("MVaMEt_y",		&MVaMEt_y	,"MVaMEt_y/d");
      tree->Branch("MVaMEtSumEt",	&MVaMEtSumEt	,"MVaMEtSumEt/d");
      tree->Branch("MVaMEtNeuEM",	&MVaMEtNeuEM	,"MVaMEtNeuEM/d");
      tree->Branch("MVaMEtNeuHad",	&MVaMEtNeuHad	,"MVaMEtNeuHad/d");
      tree->Branch("MVaMEtChHad",	&MVaMEtChHad	,"MVaMEtChHad/d");
      tree->Branch("MVaMEtChEM",	&MVaMEtChEM	,"MVaMEtChEM/d");
      tree->Branch("MVaMEtMu",		&MVaMEtMu	,"MVaMEtMu/d");

      tree->Branch("genMEtTrue_x",	&genMEtTrue_x	,"genMEtTrue_x/d");
      tree->Branch("genMEtTrue_y",	&genMEtTrue_y	,"genMEtTrue_y/d");
      tree->Branch("genMEtTrueSumEt",	&genMEtTrueSumEt	,"genMEtTrueSumEt/d");
      tree->Branch("genMEtTrueNeuEM",	&genMEtTrueNeuEM	,"genMEtTrueNeuEM/d");
      tree->Branch("genMEtTrueNeuHad",	&genMEtTrueNeuHad	,"genMEtTrueNeuHad/d");
      tree->Branch("genMEtTrueChHad",	&genMEtTrueChHad	,"genMEtTrueChHad/d");
      tree->Branch("genMEtTrueChEM",	&genMEtTrueChEM		,"genMEtTrueChEM/d");
      tree->Branch("genMEtTrueMu",	&genMEtTrueMu		,"genMEtTrueMu/d");

      tree->Branch("genMEtCalo_x",	&genMEtCalo_x	,"genMEtCalo_x/d");
      tree->Branch("genMEtCalo_y",	&genMEtCalo_y	,"genMEtCalo_y/d");
      tree->Branch("genMEtCaloSumEt",	&genMEtCaloSumEt	,"genMEtCaloSumEt/d");
      tree->Branch("genMEtCaloNeuEM",	&genMEtCaloNeuEM	,"genMEtCaloNeuEM/d");
      tree->Branch("genMEtCaloNeuHad",	&genMEtCaloNeuHad	,"genMEtCaloNeuHad/d");
      tree->Branch("genMEtCaloChHad",	&genMEtCaloChHad	,"genMEtCaloChHad/d");
      tree->Branch("genMEtCaloChEM",	&genMEtCaloChEM		,"genMEtCaloChEM/d");
      tree->Branch("genMEtCaloMu",	&genMEtCaloMu		,"genMEtCaloMu/d");

      tree->Branch("genMEtCaloAndNonPrompt_x",	&genMEtCaloAndNonPrompt_x	,"genMEtCaloAndNonPrompt_x/d");
      tree->Branch("genMEtCaloAndNonPrompt_y",	&genMEtCaloAndNonPrompt_y	,"genMEtCaloAndNonPrompt_y/d");
      tree->Branch("genMEtCaloAndNonPromptSumEt",	&genMEtCaloAndNonPromptSumEt	,"genMEtCaloAndNonPromptSumEt/d");
      tree->Branch("genMEtCaloAndNonPromptNeuEM",	&genMEtCaloAndNonPromptNeuEM	,"genMEtCaloAndNonPromptNeuEM/d");
      tree->Branch("genMEtCaloAndNonPromptNeuHad",	&genMEtCaloAndNonPromptNeuHad	,"genMEtCaloAndNonPromptNeuHad/d");
      tree->Branch("genMEtCaloAndNonPromptChHad",	&genMEtCaloAndNonPromptChHad	,"genMEtCaloAndNonPromptChHad/d");
      tree->Branch("genMEtCaloAndNonPromptChEM",	&genMEtCaloAndNonPromptChEM	,"genMEtCaloAndNonPromptChEM/d");
      tree->Branch("genMEtCaloAndNonPromptMu",		&genMEtCaloAndNonPromptMu	,"genMEtCaloAndNonPromptMu/d");

    }
};
