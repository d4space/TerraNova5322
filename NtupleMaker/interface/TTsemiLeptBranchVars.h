// $Id: wLeptNeuBranchVars.h,v 1.9 2013/09/13 00:09:32 salee Exp $
//
//
//#include <vector>
#include "TTree.h"
#include "TLorentzVector.h"

#define Triggers	(100)

using namespace std;
class TTsemi 
{
public:

  vector<bool>*		Lept1_isGlobal;
  vector<bool>*		Lept1_isTrker;
  vector<double>*	Lept1_MedComIsoDelBetCorr3Hits;
  vector<double>*	Lept1_decModFind;
  vector<double>*	Lept1_pt;
  vector<double>*       Lept1_et;
  vector<double>*       Lept1_charge;
  vector<double>*	Lept1_eta;
  vector<double>*	Lept1_phi;
  vector<double>*	Lept1_px;
  vector<double>*	Lept1_py;
  vector<double>*	Lept1_pz;
  vector<double>*	Lept1_en;
  vector<int>*		Lept1_matchStations;
  vector<double>*	Lept1_dB;
  vector<double>*	Lept1_dz;
  vector<double>*	Lept1_globalNormChi2;
  vector<double>*	Lept1_muonHits;
  vector<double>*	Lept1_trkLayers;
  vector<double>*	Lept1_trackerHits;
  vector<double>*	Lept1_pixelHits;
  vector<double>*	Lept1_etaSC;
  vector<double>*	Lept1_phiSC;
  vector<double>*	Lept1_dEtaIn;
  vector<double>*	Lept1_dPhiIn;
  vector<double>*	Lept1_sigmaIEtaIEta;
  vector<double>*	Lept1_HoverE;
  vector<double>*	Lept1_fbrem;
  vector<double>*	Lept1_energyEC;
  vector<double>*	Lept1_Pnorm;
  vector<double>*	Lept1_InvEminusInvP;
  vector<double>*	Lept1_dxy;
  vector<double>*	Lept1_AEff03;
  vector<double>*	Lept1_chIso03;
  vector<double>*	Lept1_chIso04;
  vector<double>*	Lept1_nhIso03;
  vector<double>*	Lept1_nhIso04;
  vector<double>*	Lept1_phIso03;
  vector<double>*	Lept1_phIso04;
  vector<double>*	Lept1_pcIso03;
  vector<double>*	Lept1_pcIso04;
  vector<double>*	Lept1_relIsoCom03;
  vector<double>*	Lept1_relIsoCom04;
  vector<double>*	Lept1_relIsoBeta03;
  vector<double>*	Lept1_relIsoBeta04;
  vector<double>*	Lept1_relIsoRho03;
  vector<bool>*		Lept1_hasConversion;
  vector<int>*		Lept1_mHits;
  vector<double>*       Lept1_SCcharge;
  vector<double>*       Lept1_TKcharge;
  vector<double>*       Lept1_GSFcharge;
  vector<double>*       Lept1_GsfCtfScPixchargeConsistentcheck;

  vector<double>*       Lept1_RelisolPtTrks03;
  vector<double>*       Lept1_RelisoEm03;
  vector<double>*       Lept1_RelisoHad03;

  vector<int>*		Lept1_genIdxMatch;
  vector<double>*	Lept1_genDeltaR;
  vector<double>*	Lept1_genDPtRel;

  int nIdJets;


  void Register(TTree *tree)
  {
    tree->Branch("TT_Lept1_chIso03"	,&Lept1_chIso03);
    tree->Branch("TT_Lept1_chIso04"	,&Lept1_chIso04);
    tree->Branch("TT_Lept1_nhIso03"	,&Lept1_nhIso03);
    tree->Branch("TT_Lept1_nhIso04"	,&Lept1_nhIso04);
    tree->Branch("TT_Lept1_phIso03"	,&Lept1_phIso03);
    tree->Branch("TT_Lept1_phIso04"	,&Lept1_phIso04);
    tree->Branch("TT_Lept1_pcIso03"	,&Lept1_pcIso03);
    tree->Branch("TT_Lept1_pcIso04"	,&Lept1_pcIso04);
    tree->Branch("TT_Lept1_relIsoCom03"	,&Lept1_relIsoCom03);
    tree->Branch("TT_Lept1_relIsoCom04"	,&Lept1_relIsoCom04);
    tree->Branch("TT_Lept1_relIsoBeta03"	,&Lept1_relIsoBeta03);
    tree->Branch("TT_Lept1_relIsoBeta04"	,&Lept1_relIsoBeta04);
    tree->Branch("TT_Lept1_relIsoRho03"	,&Lept1_relIsoRho03);

    tree->Branch("TT_Lept1_RelisolPtTrks03",&Lept1_RelisolPtTrks03);
    tree->Branch("TT_Lept1_RelisoEm03",&Lept1_RelisoEm03);
    tree->Branch("TT_Lept1_RelisoHad03",&Lept1_RelisoHad03);

    tree->Branch("TT_Lept1_isGlobal"	,&Lept1_isGlobal);
    tree->Branch("TT_Lept1_isTrker"	,&Lept1_isTrker);
    tree->Branch("TT_Lept1_MedComIsoDelBetCorr3Hits"	,&Lept1_MedComIsoDelBetCorr3Hits);
    tree->Branch("TT_Lept1_decModFind"	,&Lept1_decModFind);
    tree->Branch("TT_Lept1_pt"	,&Lept1_pt);
    tree->Branch("TT_Lept1_et",&Lept1_et);
    tree->Branch("TT_Lept1_charge",&Lept1_charge);
    tree->Branch("TT_Lept1_eta"	,&Lept1_eta);
    tree->Branch("TT_Lept1_phi"	,&Lept1_phi);
    tree->Branch("TT_Lept1_px"	,&Lept1_px);
    tree->Branch("TT_Lept1_py"	,&Lept1_py);
    tree->Branch("TT_Lept1_pz"	,&Lept1_pz);
    tree->Branch("TT_Lept1_en"	,&Lept1_en);
    tree->Branch("TT_Lept1_matchStations"	,&Lept1_matchStations);
    tree->Branch("TT_Lept1_dB"	,&Lept1_dB);
    tree->Branch("TT_Lept1_dz"	,&Lept1_dz);
    tree->Branch("TT_Lept1_globalNormChi2"	,&Lept1_globalNormChi2);
    tree->Branch("TT_Lept1_muonHits"	,&Lept1_muonHits);
    tree->Branch("TT_Lept1_trkLayers"	,&Lept1_trkLayers);
    tree->Branch("TT_Lept1_trackerHits"	,&Lept1_trackerHits);
    tree->Branch("TT_Lept1_pixelHits"	,&Lept1_pixelHits);

    tree->Branch("TT_Lept1_etaSC"	,&Lept1_etaSC);
    tree->Branch("TT_Lept1_phiSC"	,&Lept1_phiSC);
    tree->Branch("TT_Lept1_dEtaIn"	,&Lept1_dEtaIn);
    tree->Branch("TT_Lept1_dPhiIn"	,&Lept1_dPhiIn);
    tree->Branch("TT_Lept1_sigmaIEtaIEta",&Lept1_sigmaIEtaIEta);
    tree->Branch("TT_Lept1_HoverE"	,&Lept1_HoverE);
    tree->Branch("TT_Lept1_fbrem"	,&Lept1_fbrem);
    tree->Branch("TT_Lept1_energyEC"	,&Lept1_energyEC);
    tree->Branch("TT_Lept1_Pnorm"	,&Lept1_Pnorm);
    tree->Branch("TT_Lept1_InvEminusInvP",&Lept1_InvEminusInvP);
    tree->Branch("TT_Lept1_dxy"		,&Lept1_dxy);
    tree->Branch("TT_Lept1_AEff03"	,&Lept1_AEff03);
    tree->Branch("TT_Lept1_hasConversion",&Lept1_hasConversion);
    tree->Branch("TT_Lept1_mHits"	,&Lept1_mHits);
    tree->Branch("TT_Lept1_SCcharge"     ,&Lept1_SCcharge);
    tree->Branch("TT_Lept1_TKcharge"     ,&Lept1_TKcharge);
    tree->Branch("TT_Lept1_GSFcharge"    ,&Lept1_GSFcharge);
    tree->Branch("TT_Lept1_GsfCtfScPixchargeConsistentcheck"     ,&Lept1_GsfCtfScPixchargeConsistentcheck);

    tree->Branch("TT_Lept1_genIdxMatch"	,&Lept1_genIdxMatch);
    tree->Branch("TT_Lept1_genDeltaR"	,&Lept1_genDeltaR);
    tree->Branch("TT_Lept1_genDPtRel"	,&Lept1_genDPtRel);
    tree->Branch("TT_nIdJets"		,&nIdJets	,"nIdJets/i");
  }
};

