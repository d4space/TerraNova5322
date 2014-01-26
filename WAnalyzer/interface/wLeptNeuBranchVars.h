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
class Zboson
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
  vector<double>*	Lept1_dB	;
  vector<double>*	Lept1_dz		;
  vector<double>*	Lept1_globalNormChi2  ;
  vector<double>*	Lept1_muonHits	;
  vector<double>*	Lept1_trkLayers	;
  vector<double>*	Lept1_trackerHits;
  vector<double>*	Lept1_pixelHits  ;
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
  vector<bool>*		Lept1_hasConversion;
  vector<int>*		Lept1_mHits;
  vector<double>*       Lept1_SCcharge;
  vector<double>*       Lept1_TKcharge;
  vector<double>*       Lept1_GSFcharge;
  vector<double>*       Lept1_GsfCtfScPixchargeConsistentcheck;
  vector<double>* Lept1_chIso03;
  vector<double>* Lept1_chIso04;
  vector<double>* Lept1_nhIso03;
  vector<double>* Lept1_nhIso04;
  vector<double>* Lept1_phIso03;
  vector<double>* Lept1_phIso04;
  vector<double>* Lept1_pcIso03;
  vector<double>* Lept1_pcIso04;
  vector<double>* Lept1_relIsoCom03;
  vector<double>* Lept1_relIsoCom04;
  vector<double>* Lept1_relIsoBeta03;
  vector<double>* Lept1_relIsoBeta04;
  vector<double>* Lept1_relIsoRho03;

  vector<double>* Lept1_RelisolPtTrks03;
  vector<double>* Lept1_RelisoEm03;
  vector<double>* Lept1_RelisoHad03;

  vector<int>*		Lept1_genIdxMatch;
  vector<double>*	Lept1_genDeltaR;
  vector<double>*	Lept1_genDPtRel;

  vector<bool>*		Lept2_isGlobal;
  vector<bool>*		Lept2_isTrker;
  vector<double>*	Lept2_MedComIsoDelBetCorr3Hits;
  vector<double>*	Lept2_decModFind;
  vector<double>*	Lept2_pt    ;
  vector<double>*       Lept2_et;
  vector<double>*       Lept2_charge;
  vector<double>*	Lept2_eta    ;
  vector<double>*	Lept2_phi    ;
  vector<double>*	Lept2_px    ;
  vector<double>*	Lept2_py    ;
  vector<double>*	Lept2_pz    ;
  vector<double>*	Lept2_en    ;
  vector<int>*		Lept2_matchStations;
  vector<double>*	Lept2_dB	    ; 
  vector<double>*	Lept2_dz	   ;
  vector<double>*	Lept2_globalNormChi2;
  vector<double>*	Lept2_muonHits      ;
  vector<double>*	Lept2_trkLayers     ;
  vector<double>*	Lept2_trackerHits;
  vector<double>*	Lept2_pixelHits  ;
  vector<double>*	Lept2_etaSC;
  vector<double>*	Lept2_phiSC;
  vector<double>*	Lept2_dEtaIn;
  vector<double>*	Lept2_dPhiIn;
  vector<double>*	Lept2_sigmaIEtaIEta;
  vector<double>*	Lept2_HoverE;
  vector<double>*	Lept2_fbrem;
  vector<double>*	Lept2_energyEC;
  vector<double>*	Lept2_Pnorm;
  vector<double>*	Lept2_InvEminusInvP;
  vector<double>*	Lept2_dxy;
  vector<double>*	Lept2_AEff03;
  vector<bool>*		Lept2_hasConversion;
  vector<int>*		Lept2_mHits;
  vector<double>*       Lept2_SCcharge;
  vector<double>*       Lept2_TKcharge;
  vector<double>*       Lept2_GSFcharge;
  vector<double>*       Lept2_GsfCtfScPixchargeConsistentcheck;
  vector<double>* Lept2_chIso03;
  vector<double>* Lept2_chIso04;
  vector<double>* Lept2_nhIso03;
  vector<double>* Lept2_nhIso04;
  vector<double>* Lept2_phIso03;
  vector<double>* Lept2_phIso04;
  vector<double>* Lept2_pcIso03;
  vector<double>* Lept2_pcIso04;
  vector<double>* Lept2_relIsoCom03;
  vector<double>* Lept2_relIsoCom04;
  vector<double>* Lept2_relIsoBeta03;
  vector<double>* Lept2_relIsoBeta04;
  vector<double>* Lept2_relIsoRho03;

  vector<double>* Lept2_RelisolPtTrks03;
  vector<double>* Lept2_RelisoEm03;
  vector<double>* Lept2_RelisoHad03;

  vector<int>*		Lept2_genIdxMatch;
  vector<double>*	Lept2_genDeltaR;
  vector<double>*	Lept2_genDPtRel;

  vector<double>* diLeptVtxProb;
  vector<double>* ZMass;
  vector<double>* phi;
  vector<double>* eta;
  vector<double>* pt;
  vector<double>* px;
  vector<double>* py;
  vector<double>* pz;
  vector<double>* Neut_pt;
  vector<double>* Neut_phi;
  vector<double>* Neut_px;
  vector<double>* Neut_py;
  vector<double>* Sign;

  void Register(TTree *tree)
  {
    tree->Branch("Z_Lept1_chIso03",&Lept1_chIso03);
    tree->Branch("Z_Lept1_chIso04",&Lept1_chIso04);
    tree->Branch("Z_Lept1_nhIso03",&Lept1_nhIso03);
    tree->Branch("Z_Lept1_nhIso04",&Lept1_nhIso04);
    tree->Branch("Z_Lept1_phIso03",&Lept1_phIso03);
    tree->Branch("Z_Lept1_phIso04",&Lept1_phIso04);
    tree->Branch("Z_Lept1_pcIso03",&Lept1_pcIso03);
    tree->Branch("Z_Lept1_pcIso04",&Lept1_pcIso04);
    tree->Branch("Z_Lept1_relIsoCom03"	,&Lept1_relIsoCom03);
    tree->Branch("Z_Lept1_relIsoCom04"	,&Lept1_relIsoCom04);
    tree->Branch("Z_Lept1_relIsoBeta03"	,&Lept1_relIsoBeta03);
    tree->Branch("Z_Lept1_relIsoBeta04"	,&Lept1_relIsoBeta04);
    tree->Branch("Z_Lept1_relIsoRho03",&Lept1_relIsoRho03);

    tree->Branch("Z_Lept1_RelisolPtTrks03",&Lept1_RelisolPtTrks03);
    tree->Branch("Z_Lept1_RelisoEm03",&Lept1_RelisoEm03);
    tree->Branch("Z_Lept1_RelisoHad03",&Lept1_RelisoHad03);

    tree->Branch("Z_Lept2_chIso03",&Lept2_chIso03);
    tree->Branch("Z_Lept2_chIso04",&Lept2_chIso04);
    tree->Branch("Z_Lept2_nhIso03",&Lept2_nhIso03);
    tree->Branch("Z_Lept2_nhIso04",&Lept2_nhIso04);
    tree->Branch("Z_Lept2_phIso03",&Lept2_phIso03);
    tree->Branch("Z_Lept2_phIso04",&Lept2_phIso04);
    tree->Branch("Z_Lept2_pcIso03",&Lept2_pcIso03);
    tree->Branch("Z_Lept2_pcIso04",&Lept2_pcIso04);
    tree->Branch("Z_Lept2_relIsoCom03"	,&Lept2_relIsoCom03);
    tree->Branch("Z_Lept2_relIsoCom04"	,&Lept2_relIsoCom04);
    tree->Branch("Z_Lept2_relIsoBeta03"	,&Lept2_relIsoBeta03);
    tree->Branch("Z_Lept2_relIsoBeta04"	,&Lept2_relIsoBeta04);
    tree->Branch("Z_Lept2_relIsoRho03",&Lept2_relIsoRho03);

    tree->Branch("Z_Lept2_RelisolPtTrks03",&Lept2_RelisolPtTrks03);
    tree->Branch("Z_Lept2_RelisoEm03",&Lept2_RelisoEm03);
    tree->Branch("Z_Lept2_RelisoHad03",&Lept2_RelisoHad03);

    tree->Branch("Z_Lept1_isGlobal",&Lept1_isGlobal);
    tree->Branch("Z_Lept1_isTrker",&Lept1_isTrker); 
    tree->Branch("Z_Lept1_MedComIsoDelBetCorr3Hits",&Lept1_MedComIsoDelBetCorr3Hits);
    tree->Branch("Z_Lept1_decModFind",&Lept1_decModFind);
    tree->Branch("Z_Lept1_pt",&Lept1_pt);
    tree->Branch("Z_Lept1_et",&Lept1_et);
    tree->Branch("Z_Lept1_charge",&Lept1_charge);
    tree->Branch("Z_Lept1_eta",&Lept1_eta);
    tree->Branch("Z_Lept1_phi",&Lept1_phi);
    tree->Branch("Z_Lept1_px",&Lept1_px);
    tree->Branch("Z_Lept1_py",&Lept1_py);
    tree->Branch("Z_Lept1_pz",&Lept1_pz);
    tree->Branch("Z_Lept1_en",&Lept1_en);
    tree->Branch("Z_Lept1_matchStations",&Lept1_matchStations);
    tree->Branch("Z_Lept1_dB",&Lept1_dB);
    tree->Branch("Z_Lept2_isGlobal",&Lept2_isGlobal);
    tree->Branch("Z_Lept2_isTrker",&Lept2_isTrker);
    tree->Branch("Z_Lept2_MedComIsoDelBetCorr3Hits",&Lept2_MedComIsoDelBetCorr3Hits)     ;
    tree->Branch("Z_Lept2_decModFind",&Lept2_decModFind)     ;
    tree->Branch("Z_Lept2_pt",&Lept2_pt)     ;
    tree->Branch("Z_Lept2_et",&Lept2_et);
    tree->Branch("Z_Lept2_charge",&Lept2_charge);
    tree->Branch("Z_Lept2_eta",&Lept2_eta)    ;
    tree->Branch("Z_Lept2_phi",&Lept2_phi)    ;
    tree->Branch("Z_Lept2_px",&Lept2_px)    ;
    tree->Branch("Z_Lept2_py",&Lept2_py)    ;
    tree->Branch("Z_Lept2_pz",&Lept2_pz)    ;
    tree->Branch("Z_Lept2_en",&Lept2_en)    ;
    tree->Branch("Z_Lept2_matchStations",&Lept2_matchStations);
    tree->Branch("Z_Lept2_dB",&Lept2_dB);

    tree->Branch("Z_Lept1_dz",&Lept1_dz);
    tree->Branch("Z_Lept1_globalNormChi2",&Lept1_globalNormChi2);
    tree->Branch("Z_Lept1_muonHits",&Lept1_muonHits);
    tree->Branch("Z_Lept1_trkLayers",&Lept1_trkLayers);
    tree->Branch("Z_Lept1_trackerHits",&Lept1_trackerHits);
    tree->Branch("Z_Lept1_pixelHits",&Lept1_pixelHits);
    tree->Branch("Z_Lept2_dz",&Lept2_dz);
    tree->Branch("Z_Lept2_globalNormChi2",&Lept2_globalNormChi2);
    tree->Branch("Z_Lept2_muonHits",&Lept2_muonHits);
    tree->Branch("Z_Lept2_trkLayers",&Lept2_trkLayers);
    tree->Branch("Z_Lept2_trackerHits",&Lept2_trackerHits);
    tree->Branch("Z_Lept2_pixelHits",&Lept2_pixelHits);

    tree->Branch("Z_Lept1_etaSC",&Lept1_etaSC);
    tree->Branch("Z_Lept1_phiSC",&Lept1_phiSC);
    tree->Branch("Z_Lept1_dEtaIn",&Lept1_dEtaIn);
    tree->Branch("Z_Lept1_dPhiIn",&Lept1_dPhiIn);
    tree->Branch("Z_Lept1_sigmaIEtaIEta",&Lept1_sigmaIEtaIEta);
    tree->Branch("Z_Lept1_HoverE",&Lept1_HoverE);
    tree->Branch("Z_Lept1_fbrem",&Lept1_fbrem);
    tree->Branch("Z_Lept1_energyEC",&Lept1_energyEC);
    tree->Branch("Z_Lept1_Pnorm",&Lept1_Pnorm);
    tree->Branch("Z_Lept1_InvEminusInvP",&Lept1_InvEminusInvP);
    tree->Branch("Z_Lept1_dxy",&Lept1_dxy);
    tree->Branch("Z_Lept1_AEff03",&Lept1_AEff03);
    tree->Branch("Z_Lept1_hasConversion",&Lept1_hasConversion);
    tree->Branch("Z_Lept1_mHits",&Lept1_mHits);
    tree->Branch("Z_Lept1_SCcharge",&Lept1_SCcharge);
    tree->Branch("Z_Lept1_TKcharge",&Lept1_TKcharge);
    tree->Branch("Z_Lept1_GSFcharge",&Lept1_GSFcharge);
    tree->Branch("Z_Lept1_GsfCtfScPixchargeConsistentcheck",&Lept1_GsfCtfScPixchargeConsistentcheck);

    tree->Branch("Z_Lept2_etaSC",&Lept2_etaSC);
    tree->Branch("Z_Lept2_phiSC",&Lept2_phiSC);
    tree->Branch("Z_Lept2_dEtaIn",&Lept2_dEtaIn);
    tree->Branch("Z_Lept2_dPhiIn",&Lept2_dPhiIn);
    tree->Branch("Z_Lept2_sigmaIEtaIEta",&Lept2_sigmaIEtaIEta);
    tree->Branch("Z_Lept2_HoverE",&Lept2_HoverE);
    tree->Branch("Z_Lept2_fbrem",&Lept2_fbrem);
    tree->Branch("Z_Lept2_energyEC",&Lept2_energyEC);
    tree->Branch("Z_Lept2_Pnorm",&Lept2_Pnorm);
    tree->Branch("Z_Lept2_InvEminusInvP",&Lept2_InvEminusInvP);
    tree->Branch("Z_Lept2_dxy",&Lept2_dxy);
    tree->Branch("Z_Lept2_AEff03",&Lept2_AEff03);
    tree->Branch("Z_Lept2_hasConversion",&Lept2_hasConversion);
    tree->Branch("Z_Lept2_mHits",&Lept2_mHits);
    tree->Branch("Z_Lept2_SCcharge",&Lept2_SCcharge);
    tree->Branch("Z_Lept2_TKcharge",&Lept2_TKcharge);
    tree->Branch("Z_Lept2_GSFcharge",&Lept2_GSFcharge);
    tree->Branch("Z_Lept2_GsfCtfScPixchargeConsistentcheck",&Lept2_GsfCtfScPixchargeConsistentcheck);

    tree->Branch("Z_Lept1_genIdxMatch",	&Lept1_genIdxMatch);
    tree->Branch("Z_Lept1_genDeltaR",	&Lept1_genDeltaR);
    tree->Branch("Z_Lept1_genDPtRel",	&Lept1_genDPtRel);
    tree->Branch("Z_Lept2_genIdxMatch",	&Lept2_genIdxMatch);
    tree->Branch("Z_Lept2_genDeltaR",	&Lept2_genDeltaR);
    tree->Branch("Z_Lept2_genDPtRel",	&Lept2_genDPtRel);


    tree->Branch("Z_diLeptVtxProb",&diLeptVtxProb);
    tree->Branch("Z_Mass",&ZMass);
    tree->Branch("Z_phi",&phi);
    tree->Branch("Z_eta",&eta);
    tree->Branch("Z_pt",&pt);
    tree->Branch("Z_px",&px);
    tree->Branch("Z_py",&py);
    tree->Branch("Z_pz",&pz);
    tree->Branch("Z_Neut_pt",&Neut_pt);
    tree->Branch("Z_Neut_phi",&Neut_phi);
    tree->Branch("Z_Neut_px",&Neut_px);
    tree->Branch("Z_Neut_py",&Neut_py);
    tree->Branch("Z_Sign",&Sign);
  }
};
class Wboson
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
class GenZboson
{
  public:
    vector<int>*	nLepts;
    vector<int>*	id;
    vector<int>*	status;
    vector<double>*	mass;
    vector<double>*	px;
    vector<double>*	py;
    vector<double>*	pz;
    vector<double>*	pt;
    vector<double>*	eta;
    vector<double>*	phi;
    vector<int>*	Lept1_id;
    vector<int>*	Lept1_status;
    vector<double>*	Lept1_px;
    vector<double>*	Lept1_py;
    vector<double>*	Lept1_pz;
    vector<double>*	Lept1_en;
    vector<double>*	Lept1_pt;
    vector<double>*     Lept1_et;
    vector<double>*     Lept1_charge;
    vector<double>*	Lept1_eta;
    vector<double>*	Lept1_phi;
    vector<int>*	Lept2_id;
    vector<int>*	Lept2_status;
    vector<double>*	Lept2_px;
    vector<double>*	Lept2_py;
    vector<double>*	Lept2_pz;
    vector<double>*	Lept2_en;
    vector<double>*	Lept2_pt;
    vector<double>*     Lept2_et;
    vector<double>*     Lept2_charge;
    vector<double>*	Lept2_eta;
    vector<double>*	Lept2_phi;
    double		Neut_pt;
    void Register(TTree *tree)
    {
      tree->Branch("GenZ_nLepts"	,&nLepts);
      //tree->Branch("GenZ_nLepts"	,&nLepts	,"Nlepts/i");
      tree->Branch("GenZ_id",&id);
      tree->Branch("GenZ_status",&status);
      tree->Branch("GenZ_mass",&mass);
      tree->Branch("GenZ_px",&px);
      tree->Branch("GenZ_py",&py);
      tree->Branch("GenZ_pz",&pz);
      tree->Branch("GenZ_pt",&pt);
      tree->Branch("GenZ_Neut_pt",&Neut_pt);
      tree->Branch("GenZ_eta",&eta);
      tree->Branch("GenZ_phi",&phi);
      tree->Branch("GenZ_Lept1_id",&Lept1_id);
      tree->Branch("GenZ_Lept1_status",&Lept1_status);
      tree->Branch("GenZ_Lept1_px",&Lept1_px);
      tree->Branch("GenZ_Lept1_py",&Lept1_py);
      tree->Branch("GenZ_Lept1_pz",&Lept1_pz);
      tree->Branch("GenZ_Lept1_en",&Lept1_en);
      tree->Branch("GenZ_Lept1_pt",&Lept1_pt);
      tree->Branch("GenZ_Lept1_et",&Lept1_et);
      tree->Branch("GenZ_Lept1_charge",&Lept1_charge);
      tree->Branch("GenZ_Lept1_eta",&Lept1_eta);
      tree->Branch("GenZ_Lept1_phi",&Lept1_phi);
      tree->Branch("GenZ_Lept2_id",	&Lept2_id);
      tree->Branch("GenZ_Lept2_status",	&Lept2_status);
      tree->Branch("GenZ_Lept2_px",	&Lept2_px);
      tree->Branch("GenZ_Lept2_py",	&Lept2_py);
      tree->Branch("GenZ_Lept2_pz",	&Lept2_pz);
      tree->Branch("GenZ_Lept2_en",	&Lept2_en);
      tree->Branch("GenZ_Lept2_pt",	&Lept2_pt);
      tree->Branch("GenZ_Lept2_et", &Lept2_et);
      tree->Branch("GenZ_Lept2_charge", &Lept2_charge);
      tree->Branch("GenZ_Lept2_eta",	&Lept2_eta);
      tree->Branch("GenZ_Lept2_phi",	&Lept2_phi);
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

class KoMET
{
  public:
    TLorentzVector *pfMEt4V;
    TLorentzVector *NoPuMEt4V;
    TLorentzVector *MVaMEt4V;
    TLorentzVector *genMEtTrue4V;
    TLorentzVector *genMEtCalo4V;
    TLorentzVector *genMEtCaloAndNonPrompt4V;

    double pfMEtSumEt, pfMEtNeuEM, pfMEtNeuHad, pfMEtChHad, pfMEtChEM, pfMEtMu;
    double NoPuMEtSumEt,NoPuMEtNeuEM,NoPuMEtNeuHad,NoPuMEtChHad,NoPuMEtChEM,NoPuMEtMu;
    double MVaMEtSumEt,MVaMEtNeuEM,MVaMEtNeuHad,MVaMEtChHad,MVaMEtChEM,MVaMEtMu;
    double genMEtTrueSumEt,genMEtTrueNeuEM,genMEtTrueNeuHad,genMEtTrueChHad,genMEtTrueChEM,genMEtTrueMu;
    double genMEtCaloSumEt,genMEtCaloNeuEM,genMEtCaloNeuHad,genMEtCaloChHad,genMEtCaloChEM,genMEtCaloMu;
    double genMEtCaloAndNonPromptSumEt,genMEtCaloAndNonPromptNeuEM,genMEtCaloAndNonPromptNeuHad,genMEtCaloAndNonPromptChHad,genMEtCaloAndNonPromptChEM,genMEtCaloAndNonPromptMu;

    void Register(TTree *tree)
    {
      //tree->Branch("pfMEt4V", &pfMEt4V, int bufsize=3200, splitlevel=99);
      tree->Branch("pfMEt4V","TLorentzVector", &pfMEt4V);
      tree->Branch("NoPuMEt4V","TLorentzVector", &NoPuMEt4V);
      tree->Branch("MVaMEt4V","TLorentzVector", &MVaMEt4V);
      tree->Branch("genMEtTrue4V","TLorentzVector", &genMEtTrue4V);
      tree->Branch("genMEtCalo4V","TLorentzVector", &genMEtCalo4V);
      tree->Branch("genMEtCaloAndNonPrompt4V","TLorentzVector", &genMEtCaloAndNonPrompt4V);

      tree->Branch("pfMEtSumEt", &pfMEtSumEt	,"pfMEtSumEt/d");
      tree->Branch("pfMEtNeuEM", &pfMEtNeuEM	,"pfMEtNeuEM/d");
      tree->Branch("pfMEtNeuHad", &pfMEtNeuHad	,"pfMEtNeuHad/d");
      tree->Branch("pfMEtChHad", &pfMEtChHad	,"pfMEtChHad/d");
      tree->Branch("pfMEtChEM", &pfMEtChEM	,"pfMEtChEM/d");
      tree->Branch("pfMEtMu", &pfMEtMu	,"pfMEtMu/d");

      tree->Branch("NoPuMEtSumEt",	&NoPuMEtSumEt	,"NoPuMEtSumEt/d");
      tree->Branch("NoPuMEtNeuEM",	&NoPuMEtNeuEM	,"NoPuMEtNeuEM/d");
      tree->Branch("NoPuMEtNeuHad",	&NoPuMEtNeuHad	,"NoPuMEtNeuHad/d");
      tree->Branch("NoPuMEtChHad",	&NoPuMEtChHad	,"NoPuMEtChHad/d");
      tree->Branch("NoPuMEtChEM",	&NoPuMEtChEM	,"NoPuMEtChEM/d");
      tree->Branch("NoPuMEtMu",		&NoPuMEtMu	,"NoPuMEtMu/d");

      tree->Branch("MVaMEtSumEt",	&MVaMEtSumEt	,"MVaMEtSumEt/d");
      tree->Branch("MVaMEtNeuEM",	&MVaMEtNeuEM	,"MVaMEtNeuEM/d");
      tree->Branch("MVaMEtNeuHad",	&MVaMEtNeuHad	,"MVaMEtNeuHad/d");
      tree->Branch("MVaMEtChHad",	&MVaMEtChHad	,"MVaMEtChHad/d");
      tree->Branch("MVaMEtChEM",	&MVaMEtChEM	,"MVaMEtChEM/d");
      tree->Branch("MVaMEtMu",		&MVaMEtMu	,"MVaMEtMu/d");

      tree->Branch("genMEtTrueSumEt",	&genMEtTrueSumEt	,"genMEtTrueSumEt/d");
      tree->Branch("genMEtTrueNeuEM",	&genMEtTrueNeuEM	,"genMEtTrueNeuEM/d");
      tree->Branch("genMEtTrueNeuHad",	&genMEtTrueNeuHad	,"genMEtTrueNeuHad/d");
      tree->Branch("genMEtTrueChHad",	&genMEtTrueChHad	,"genMEtTrueChHad/d");
      tree->Branch("genMEtTrueChEM",	&genMEtTrueChEM		,"genMEtTrueChEM/d");
      tree->Branch("genMEtTrueMu",	&genMEtTrueMu		,"genMEtTrueMu/d");

      tree->Branch("genMEtCaloSumEt",	&genMEtCaloSumEt	,"genMEtCaloSumEt/d");
      tree->Branch("genMEtCaloNeuEM",	&genMEtCaloNeuEM	,"genMEtCaloNeuEM/d");
      tree->Branch("genMEtCaloNeuHad",	&genMEtCaloNeuHad	,"genMEtCaloNeuHad/d");
      tree->Branch("genMEtCaloChHad",	&genMEtCaloChHad	,"genMEtCaloChHad/d");
      tree->Branch("genMEtCaloChEM",	&genMEtCaloChEM		,"genMEtCaloChEM/d");
      tree->Branch("genMEtCaloMu",	&genMEtCaloMu		,"genMEtCaloMu/d");

      tree->Branch("genMEtCaloAndNonPromptSumEt",	&genMEtCaloAndNonPromptSumEt	,"genMEtCaloAndNonPromptSumEt/d");
      tree->Branch("genMEtCaloAndNonPromptNeuEM",	&genMEtCaloAndNonPromptNeuEM	,"genMEtCaloAndNonPromptNeuEM/d");
      tree->Branch("genMEtCaloAndNonPromptNeuHad",	&genMEtCaloAndNonPromptNeuHad	,"genMEtCaloAndNonPromptNeuHad/d");
      tree->Branch("genMEtCaloAndNonPromptChHad",	&genMEtCaloAndNonPromptChHad	,"genMEtCaloAndNonPromptChHad/d");
      tree->Branch("genMEtCaloAndNonPromptChEM",	&genMEtCaloAndNonPromptChEM	,"genMEtCaloAndNonPromptChEM/d");
      tree->Branch("genMEtCaloAndNonPromptMu",		&genMEtCaloAndNonPromptMu	,"genMEtCaloAndNonPromptMu/d");

    }
};
