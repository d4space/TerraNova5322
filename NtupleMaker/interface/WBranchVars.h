// $Id: wLeptNeuBranchVars.h,v 1.9 2013/09/13 00:09:32 salee Exp $
//
//
//#include <vector>
#include "TTree.h"
#include "TLorentzVector.h"


using namespace std;

class Wboson
{
public:

  vector<int>*		Lept1_ptcID;
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

  vector<double>*	W_invm;
  vector<double>*	Neut_pt;
  vector<double>*	Neut_phi;
  vector<double>*	Neut_px;
  vector<double>*	Neut_py;
  vector<double>*	W_pt;
  vector<double>*	W_eta;
  vector<double>*	W_phi;
  vector<double>*	W_px;
  vector<double>*	W_py;
  vector<double>*	W_pz;
  vector<double>*	W_Mt;
  vector<double>*	W_Acop;
  vector<double>*	W_Charge;

  void Register(TTree *tree)
  {
    tree->Branch("W_Lept1_ptcID"	,&Lept1_ptcID);
    tree->Branch("W_Lept1_chIso03"	,&Lept1_chIso03);
    tree->Branch("W_Lept1_chIso04"	,&Lept1_chIso04);
    tree->Branch("W_Lept1_nhIso03"	,&Lept1_nhIso03);
    tree->Branch("W_Lept1_nhIso04"	,&Lept1_nhIso04);
    tree->Branch("W_Lept1_phIso03"	,&Lept1_phIso03);
    tree->Branch("W_Lept1_phIso04"	,&Lept1_phIso04);
    tree->Branch("W_Lept1_pcIso03"	,&Lept1_pcIso03);
    tree->Branch("W_Lept1_pcIso04"	,&Lept1_pcIso04);
    tree->Branch("W_Lept1_relIsoCom03"	,&Lept1_relIsoCom03);
    tree->Branch("W_Lept1_relIsoCom04"	,&Lept1_relIsoCom04);
    tree->Branch("W_Lept1_relIsoBeta03"	,&Lept1_relIsoBeta03);
    tree->Branch("W_Lept1_relIsoBeta04"	,&Lept1_relIsoBeta04);
    tree->Branch("W_Lept1_relIsoRho03"	,&Lept1_relIsoRho03);

    tree->Branch("W_Lept1_RelisolPtTrks03",&Lept1_RelisolPtTrks03);
    tree->Branch("W_Lept1_RelisoEm03",&Lept1_RelisoEm03);
    tree->Branch("W_Lept1_RelisoHad03",&Lept1_RelisoHad03);

    tree->Branch("W_Lept1_isGlobal"	,&Lept1_isGlobal);
    tree->Branch("W_Lept1_isTrker"	,&Lept1_isTrker);
    tree->Branch("W_Lept1_MedComIsoDelBetCorr3Hits"	,&Lept1_MedComIsoDelBetCorr3Hits);
    tree->Branch("W_Lept1_decModFind"	,&Lept1_decModFind);
    tree->Branch("W_Lept1_pt"	,&Lept1_pt);
    tree->Branch("W_Lept1_et",&Lept1_et);
    tree->Branch("W_Lept1_charge",&Lept1_charge);
    tree->Branch("W_Lept1_eta"	,&Lept1_eta);
    tree->Branch("W_Lept1_phi"	,&Lept1_phi);
    tree->Branch("W_Lept1_px"	,&Lept1_px);
    tree->Branch("W_Lept1_py"	,&Lept1_py);
    tree->Branch("W_Lept1_pz"	,&Lept1_pz);
    tree->Branch("W_Lept1_en"	,&Lept1_en);
    tree->Branch("W_Lept1_matchStations"	,&Lept1_matchStations);
    tree->Branch("W_Lept1_dB"	,&Lept1_dB);
    tree->Branch("W_Lept1_dz"	,&Lept1_dz);
    tree->Branch("W_Lept1_globalNormChi2"	,&Lept1_globalNormChi2);
    tree->Branch("W_Lept1_muonHits"	,&Lept1_muonHits);
    tree->Branch("W_Lept1_trkLayers"	,&Lept1_trkLayers);
    tree->Branch("W_Lept1_trackerHits"	,&Lept1_trackerHits);
    tree->Branch("W_Lept1_pixelHits"	,&Lept1_pixelHits);

    tree->Branch("W_Lept1_etaSC"	,&Lept1_etaSC);
    tree->Branch("W_Lept1_phiSC"	,&Lept1_phiSC);
    tree->Branch("W_Lept1_dEtaIn"	,&Lept1_dEtaIn);
    tree->Branch("W_Lept1_dPhiIn"	,&Lept1_dPhiIn);
    tree->Branch("W_Lept1_sigmaIEtaIEta",&Lept1_sigmaIEtaIEta);
    tree->Branch("W_Lept1_HoverE"	,&Lept1_HoverE);
    tree->Branch("W_Lept1_fbrem"	,&Lept1_fbrem);
    tree->Branch("W_Lept1_energyEC"	,&Lept1_energyEC);
    tree->Branch("W_Lept1_Pnorm"	,&Lept1_Pnorm);
    tree->Branch("W_Lept1_InvEminusInvP",&Lept1_InvEminusInvP);
    tree->Branch("W_Lept1_dxy"		,&Lept1_dxy);
    tree->Branch("W_Lept1_AEff03"	,&Lept1_AEff03);
    tree->Branch("W_Lept1_hasConversion",&Lept1_hasConversion);
    tree->Branch("W_Lept1_mHits"	,&Lept1_mHits);
    tree->Branch("W_Lept1_SCcharge"     ,&Lept1_SCcharge);
    tree->Branch("W_Lept1_TKcharge"     ,&Lept1_TKcharge);
    tree->Branch("W_Lept1_GSFcharge"    ,&Lept1_GSFcharge);
    tree->Branch("W_Lept1_GsfCtfScPixchargeConsistentcheck"     ,&Lept1_GsfCtfScPixchargeConsistentcheck);

    tree->Branch("W_Lept1_genIdxMatch"	,&Lept1_genIdxMatch);
    tree->Branch("W_Lept1_genDeltaR"	,&Lept1_genDeltaR);
    tree->Branch("W_Lept1_genDPtRel"	,&Lept1_genDPtRel);

    tree->Branch("W_invm"	,&W_invm);
    tree->Branch("W_Neut_pt"	,&Neut_pt);
    tree->Branch("W_Neut_phi"	,&Neut_phi);
    tree->Branch("W_Neut_px"	,&Neut_px);
    tree->Branch("W_Neut_py"	,&Neut_py);
    tree->Branch("W_pt"	,&W_pt);
    tree->Branch("W_eta"	,&W_eta);
    tree->Branch("W_phi"	,&W_phi);
    tree->Branch("W_px"	,&W_px);
    tree->Branch("W_py"	,&W_py);
    tree->Branch("W_pz"	,&W_pz);
    tree->Branch("W_Mt"	,&W_Mt);
    tree->Branch("W_Acop"	,&W_Acop);
    tree->Branch("W_Charge"	,&W_Charge);
  }
};
class GenWboson
{
  public:
    vector<int>*	Born_nLepts;
    vector<int>*	Born_id;
    vector<int>*	Born_status;
    vector<double>*	Born_mass;
    vector<double>*	Born_px;
    vector<double>*	Born_py;
    vector<double>*	Born_pz;
    vector<double>*	Born_pt;
    vector<double>*	Born_eta;
    vector<double>*	Born_phi;

    vector<int>*	BornLept1_id;
    vector<int>*	PostLept1_id;
    vector<int>*	BornLept1_status;
    vector<int>*	PostLept1_status;
    vector<double>*	BornLept1_px;
    vector<double>*	PostLept1_px;
    vector<double>*	BornLept1_py;
    vector<double>*	PostLept1_py;
    vector<double>*	BornLept1_pz;
    vector<double>*	PostLept1_pz;
    vector<double>*	BornLept1_en;
    vector<double>*	PostLept1_en;
    vector<double>*	BornLept1_pt;
    vector<double>*	PostLept1_pt;
    vector<double>*     BornLept1_et;
    vector<double>*     BornLept1_charge;
    vector<double>*     PostLept1_et;
    vector<double>*     PostLept1_charge;
    vector<double>*	BornLept1_eta;
    vector<double>*	PostLept1_eta;
    vector<double>*	BornLept1_phi;
    vector<double>*	PostLept1_phi;
    vector<int>*	BornLept2_id;
    vector<int>*	PostLept2_id;
    vector<int>*	BornLept2_status;
    vector<int>*	PostLept2_status;
    vector<double>*	BornLept2_px;
    vector<double>*	PostLept2_px;
    vector<double>*	BornLept2_py;
    vector<double>*	PostLept2_py;
    vector<double>*	BornLept2_pz;
    vector<double>*	PostLept2_pz;
    vector<double>*	BornLept2_en;
    vector<double>*	PostLept2_en;
    vector<double>*	BornLept2_pt;
    vector<double>*	PostLept2_pt;
    vector<double>*     BornLept2_et;
    vector<double>*     BornLept2_charge;
    vector<double>*     PostLept2_et;
    vector<double>*     PostLept2_charge;
    vector<double>*	BornLept2_eta;
    vector<double>*	PostLept2_eta;
    vector<double>*	BornLept2_phi;
    vector<double>*	PostLept2_phi;
    double		Neut_pt;
    void Register(TTree *tree)
    {
      //Before FSR
      tree->Branch("GenW_Born_nLepts",	&Born_nLepts);
      //tree->Branch("GenW_nLepts"	,&nLepts	,"Nlepts/i");
      tree->Branch("GenW_Born_Id",	&Born_id);
      tree->Branch("GenW_Born_Status",	&Born_status);
      tree->Branch("GenW_Born_mass",	&Born_mass);
      tree->Branch("GenW_Born_px",	&Born_px);
      tree->Branch("GenW_Born_py",	&Born_py);
      tree->Branch("GenW_Born_pz",	&Born_pz);
      tree->Branch("GenW_Born_pt",	&Born_pt);
      tree->Branch("GenW_Born_eta",	&Born_eta);
      tree->Branch("GenW_Born_phi",	&Born_phi);

      tree->Branch("GenW_BornLept1_id",		&BornLept1_id);
      tree->Branch("GenW_BornLept1_status",	&BornLept1_status);
      tree->Branch("GenW_BornLept1_px",		&BornLept1_px);
      tree->Branch("GenW_BornLept1_py",		&BornLept1_py);
      tree->Branch("GenW_BornLept1_pz",		&BornLept1_pz);
      tree->Branch("GenW_BornLept1_en",		&BornLept1_en);
      tree->Branch("GenW_BornLept1_pt",		&BornLept1_pt);
      tree->Branch("GenW_BornLept1_et",		&BornLept1_et);
      tree->Branch("GenW_BornLept1_charge",		&BornLept1_charge);
      tree->Branch("GenW_BornLept1_eta",	&BornLept1_eta);
      tree->Branch("GenW_BornLept1_phi",	&BornLept1_phi);
      tree->Branch("GenW_BornLept2_id",		&BornLept2_id);
      tree->Branch("GenW_BornLept2_status",	&BornLept2_status);
      tree->Branch("GenW_BornLept2_px",		&BornLept2_px);
      tree->Branch("GenW_BornLept2_py",		&BornLept2_py);
      tree->Branch("GenW_BornLept2_pz",		&BornLept2_pz);
      tree->Branch("GenW_BornLept2_en",		&BornLept2_en);
      tree->Branch("GenW_BornLept2_pt",		&BornLept2_pt);
      tree->Branch("GenW_BornLept2_et", 	&BornLept2_et);
      tree->Branch("GenW_BornLept2_charge", 	&BornLept2_charge);
      tree->Branch("GenW_BornLept2_eta",	&BornLept2_eta);
      tree->Branch("GenW_BornLept2_phi",	&BornLept2_phi);
      //After FSR
      tree->Branch("GenW_PostLept1_id",		&PostLept1_id);
      tree->Branch("GenW_PostLept1_status",	&PostLept1_status);
      tree->Branch("GenW_PostLept1_px",		&PostLept1_px);
      tree->Branch("GenW_PostLept1_py",		&PostLept1_py);
      tree->Branch("GenW_PostLept1_pz",		&PostLept1_pz);
      tree->Branch("GenW_PostLept1_en",		&PostLept1_en);
      tree->Branch("GenW_PostLept1_pt",		&PostLept1_pt);
      tree->Branch("GenW_PostLept1_et",		&PostLept1_et);
      tree->Branch("GenW_PostLept1_charge",		&PostLept1_charge);
      tree->Branch("GenW_PostLept1_eta",	&PostLept1_eta);
      tree->Branch("GenW_PostLept1_phi",	&PostLept1_phi);
      tree->Branch("GenW_PostLept2_id",		&PostLept2_id);
      tree->Branch("GenW_PostLept2_status",	&PostLept2_status);
      tree->Branch("GenW_PostLept2_px",		&PostLept2_px);
      tree->Branch("GenW_PostLept2_py",		&PostLept2_py);
      tree->Branch("GenW_PostLept2_pz",		&PostLept2_pz);
      tree->Branch("GenW_PostLept2_en",		&PostLept2_en);
      tree->Branch("GenW_PostLept2_pt",		&PostLept2_pt);
      tree->Branch("GenW_PostLept2_et", 	&PostLept2_et);
      tree->Branch("GenW_PostLept2_charge", 	&PostLept2_charge);
      tree->Branch("GenW_PostLept2_eta",	&PostLept2_eta);
      tree->Branch("GenW_PostLept2_phi",	&PostLept2_phi);
      tree->Branch("GenW_Neut_pt",		&Neut_pt);
    }
};
