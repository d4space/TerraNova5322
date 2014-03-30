//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun Mar 30 03:10:31 2014 by ROOT version 5.34/14
// from TChain WZ3LNu/tree/
//////////////////////////////////////////////////////////

#ifndef WZ3LNT_h
#define WZ3LNT_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <vector>
#include <vector>
#include <vector>

// Fixed size dimensions of array or collections stored in the TTree if any.

class WZ3LNT {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   UInt_t          EVENT;
   UInt_t          RUN;
   UInt_t          LUMI;
   UInt_t          Channel;
   UInt_t          npileup;
   Double_t        weightin;
   Double_t        weight;
   Double_t        weightplus;
   Double_t        weightminus;
   Double_t        rhoIso;
   vector<int>     *vtx_isFake;
   vector<int>     *vtx_ndof;
   vector<double>  *vtx_z;
   vector<double>  *vtx_Rho;
   Double_t        weightFSR;
   Int_t           HLT_Ele22_CaloIdL_CaloIsoVL_version;
   Int_t           HLT_Ele22_CaloIdL_CaloIsoVL_L1prescale;
   Int_t           HLT_Ele22_CaloIdL_CaloIsoVL_L1fired;
   Int_t           HLT_Ele22_CaloIdL_CaloIsoVL_HLTprescale;
   Int_t           HLT_Ele22_CaloIdL_CaloIsoVL_fired;
   Int_t           HLT_Ele27_WP80_version;
   Int_t           HLT_Ele27_WP80_L1prescale;
   Int_t           HLT_Ele27_WP80_L1fired;
   Int_t           HLT_Ele27_WP80_HLTprescale;
   Int_t           HLT_Ele27_WP80_fired;
   Int_t           HLT_Mu15_eta2p1_version;
   Int_t           HLT_Mu15_eta2p1_L1prescale;
   Int_t           HLT_Mu15_eta2p1_L1fired;
   Int_t           HLT_Mu15_eta2p1_HLTprescale;
   Int_t           HLT_Mu15_eta2p1_fired;
   vector<int>     *Z_Channel;
   vector<double>  *Z_Lept1_chIso03;
   vector<double>  *Z_Lept1_chIso04;
   vector<double>  *Z_Lept1_nhIso03;
   vector<double>  *Z_Lept1_nhIso04;
   vector<double>  *Z_Lept1_phIso03;
   vector<double>  *Z_Lept1_phIso04;
   vector<double>  *Z_Lept1_pcIso03;
   vector<double>  *Z_Lept1_pcIso04;
   vector<double>  *Z_Lept1_relIsoCom03;
   vector<double>  *Z_Lept1_relIsoCom04;
   vector<double>  *Z_Lept1_relIsoBeta03;
   vector<double>  *Z_Lept1_relIsoBeta04;
   vector<double>  *Z_Lept1_relIsoRho03;
   vector<double>  *Z_Lept1_RelisolPtTrks03;
   vector<double>  *Z_Lept1_RelisoEm03;
   vector<double>  *Z_Lept1_RelisoHad03;
   vector<double>  *Z_Lept2_chIso03;
   vector<double>  *Z_Lept2_chIso04;
   vector<double>  *Z_Lept2_nhIso03;
   vector<double>  *Z_Lept2_nhIso04;
   vector<double>  *Z_Lept2_phIso03;
   vector<double>  *Z_Lept2_phIso04;
   vector<double>  *Z_Lept2_pcIso03;
   vector<double>  *Z_Lept2_pcIso04;
   vector<double>  *Z_Lept2_relIsoCom03;
   vector<double>  *Z_Lept2_relIsoCom04;
   vector<double>  *Z_Lept2_relIsoBeta03;
   vector<double>  *Z_Lept2_relIsoBeta04;
   vector<double>  *Z_Lept2_relIsoRho03;
   vector<double>  *Z_Lept2_RelisolPtTrks03;
   vector<double>  *Z_Lept2_RelisoEm03;
   vector<double>  *Z_Lept2_RelisoHad03;
   vector<bool>    *Z_Lept1_isGlobal;
   vector<bool>    *Z_Lept1_isTrker;
   vector<double>  *Z_Lept1_MedComIsoDelBetCorr3Hits;
   vector<double>  *Z_Lept1_decModFind;
   vector<double>  *Z_Lept1_pt;
   vector<double>  *Z_Lept1_et;
   vector<double>  *Z_Lept1_charge;
   vector<double>  *Z_Lept1_eta;
   vector<double>  *Z_Lept1_phi;
   vector<double>  *Z_Lept1_px;
   vector<double>  *Z_Lept1_py;
   vector<double>  *Z_Lept1_pz;
   vector<double>  *Z_Lept1_en;
   vector<int>     *Z_Lept1_matchStations;
   vector<double>  *Z_Lept1_dB;
   vector<bool>    *Z_Lept2_isGlobal;
   vector<bool>    *Z_Lept2_isTrker;
   vector<double>  *Z_Lept2_MedComIsoDelBetCorr3Hits;
   vector<double>  *Z_Lept2_decModFind;
   vector<double>  *Z_Lept2_pt;
   vector<double>  *Z_Lept2_et;
   vector<double>  *Z_Lept2_charge;
   vector<double>  *Z_Lept2_eta;
   vector<double>  *Z_Lept2_phi;
   vector<double>  *Z_Lept2_px;
   vector<double>  *Z_Lept2_py;
   vector<double>  *Z_Lept2_pz;
   vector<double>  *Z_Lept2_en;
   vector<int>     *Z_Lept2_matchStations;
   vector<double>  *Z_Lept2_dB;
   vector<double>  *Z_Lept1_dz;
   vector<double>  *Z_Lept1_globalNormChi2;
   vector<double>  *Z_Lept1_muonHits;
   vector<double>  *Z_Lept1_trkLayers;
   vector<double>  *Z_Lept1_trackerHits;
   vector<double>  *Z_Lept1_pixelHits;
   vector<double>  *Z_Lept2_dz;
   vector<double>  *Z_Lept2_globalNormChi2;
   vector<double>  *Z_Lept2_muonHits;
   vector<double>  *Z_Lept2_trkLayers;
   vector<double>  *Z_Lept2_trackerHits;
   vector<double>  *Z_Lept2_pixelHits;
   vector<double>  *Z_Lept1_etaSC;
   vector<double>  *Z_Lept1_phiSC;
   vector<double>  *Z_Lept1_dEtaIn;
   vector<double>  *Z_Lept1_dPhiIn;
   vector<double>  *Z_Lept1_sigmaIEtaIEta;
   vector<double>  *Z_Lept1_HoverE;
   vector<double>  *Z_Lept1_fbrem;
   vector<double>  *Z_Lept1_energyEC;
   vector<double>  *Z_Lept1_Pnorm;
   vector<double>  *Z_Lept1_InvEminusInvP;
   vector<double>  *Z_Lept1_dxy;
   vector<double>  *Z_Lept1_AEff03;
   vector<bool>    *Z_Lept1_hasConversion;
   vector<int>     *Z_Lept1_mHits;
   vector<double>  *Z_Lept1_SCcharge;
   vector<double>  *Z_Lept1_TKcharge;
   vector<double>  *Z_Lept1_GSFcharge;
   vector<double>  *Z_Lept1_GsfCtfScPixchargeConsistentcheck;
   vector<double>  *Z_Lept2_etaSC;
   vector<double>  *Z_Lept2_phiSC;
   vector<double>  *Z_Lept2_dEtaIn;
   vector<double>  *Z_Lept2_dPhiIn;
   vector<double>  *Z_Lept2_sigmaIEtaIEta;
   vector<double>  *Z_Lept2_HoverE;
   vector<double>  *Z_Lept2_fbrem;
   vector<double>  *Z_Lept2_energyEC;
   vector<double>  *Z_Lept2_Pnorm;
   vector<double>  *Z_Lept2_InvEminusInvP;
   vector<double>  *Z_Lept2_dxy;
   vector<double>  *Z_Lept2_AEff03;
   vector<bool>    *Z_Lept2_hasConversion;
   vector<int>     *Z_Lept2_mHits;
   vector<double>  *Z_Lept2_SCcharge;
   vector<double>  *Z_Lept2_TKcharge;
   vector<double>  *Z_Lept2_GSFcharge;
   vector<double>  *Z_Lept2_GsfCtfScPixchargeConsistentcheck;
   vector<int>     *Z_Lept1_genIdxMatch;
   vector<double>  *Z_Lept1_genDeltaR;
   vector<double>  *Z_Lept1_genDPtRel;
   vector<int>     *Z_Lept2_genIdxMatch;
   vector<double>  *Z_Lept2_genDeltaR;
   vector<double>  *Z_Lept2_genDPtRel;
   vector<double>  *Z_diLeptVtxProb;
   vector<double>  *Z_Mass;
   vector<double>  *Z_phi;
   vector<double>  *Z_eta;
   vector<double>  *Z_pt;
   vector<double>  *Z_px;
   vector<double>  *Z_py;
   vector<double>  *Z_pz;
   vector<double>  *Z_Neut_pt;
   vector<double>  *Z_Neut_phi;
   vector<double>  *Z_Neut_px;
   vector<double>  *Z_Neut_py;
   vector<double>  *Z_Sign;
   vector<int>     *W_Lept1_ptcID;
   vector<double>  *W_Lept1_chIso03;
   vector<double>  *W_Lept1_chIso04;
   vector<double>  *W_Lept1_nhIso03;
   vector<double>  *W_Lept1_nhIso04;
   vector<double>  *W_Lept1_phIso03;
   vector<double>  *W_Lept1_phIso04;
   vector<double>  *W_Lept1_pcIso03;
   vector<double>  *W_Lept1_pcIso04;
   vector<double>  *W_Lept1_relIsoCom03;
   vector<double>  *W_Lept1_relIsoCom04;
   vector<double>  *W_Lept1_relIsoBeta03;
   vector<double>  *W_Lept1_relIsoBeta04;
   vector<double>  *W_Lept1_relIsoRho03;
   vector<double>  *W_Lept1_RelisolPtTrks03;
   vector<double>  *W_Lept1_RelisoEm03;
   vector<double>  *W_Lept1_RelisoHad03;
   vector<bool>    *W_Lept1_isGlobal;
   vector<bool>    *W_Lept1_isTrker;
   vector<double>  *W_Lept1_MedComIsoDelBetCorr3Hits;
   vector<double>  *W_Lept1_decModFind;
   vector<double>  *W_Lept1_pt;
   vector<double>  *W_Lept1_et;
   vector<double>  *W_Lept1_charge;
   vector<double>  *W_Lept1_eta;
   vector<double>  *W_Lept1_phi;
   vector<double>  *W_Lept1_px;
   vector<double>  *W_Lept1_py;
   vector<double>  *W_Lept1_pz;
   vector<double>  *W_Lept1_en;
   vector<int>     *W_Lept1_matchStations;
   vector<double>  *W_Lept1_dB;
   vector<double>  *W_Lept1_dz;
   vector<double>  *W_Lept1_globalNormChi2;
   vector<double>  *W_Lept1_muonHits;
   vector<double>  *W_Lept1_trkLayers;
   vector<double>  *W_Lept1_trackerHits;
   vector<double>  *W_Lept1_pixelHits;
   vector<double>  *W_Lept1_etaSC;
   vector<double>  *W_Lept1_phiSC;
   vector<double>  *W_Lept1_dEtaIn;
   vector<double>  *W_Lept1_dPhiIn;
   vector<double>  *W_Lept1_sigmaIEtaIEta;
   vector<double>  *W_Lept1_HoverE;
   vector<double>  *W_Lept1_fbrem;
   vector<double>  *W_Lept1_energyEC;
   vector<double>  *W_Lept1_Pnorm;
   vector<double>  *W_Lept1_InvEminusInvP;
   vector<double>  *W_Lept1_dxy;
   vector<double>  *W_Lept1_AEff03;
   vector<bool>    *W_Lept1_hasConversion;
   vector<int>     *W_Lept1_mHits;
   vector<double>  *W_Lept1_SCcharge;
   vector<double>  *W_Lept1_TKcharge;
   vector<double>  *W_Lept1_GSFcharge;
   vector<double>  *W_Lept1_GsfCtfScPixchargeConsistentcheck;
   vector<int>     *W_Lept1_genIdxMatch;
   vector<double>  *W_Lept1_genDeltaR;
   vector<double>  *W_Lept1_genDPtRel;
   vector<double>  *W_invm;
   vector<double>  *W_Neut_pt;
   vector<double>  *W_Neut_phi;
   vector<double>  *W_Neut_px;
   vector<double>  *W_Neut_py;
   vector<double>  *W_pt;
   vector<double>  *W_eta;
   vector<double>  *W_phi;
   vector<double>  *W_px;
   vector<double>  *W_py;
   vector<double>  *W_pz;
   vector<double>  *W_Mt;
   vector<double>  *W_Acop;
   vector<double>  *W_Charge;
   vector<int>     *GenW_Born_nLepts;
   vector<int>     *GenW_Born_Id;
   vector<int>     *GenW_Born_Status;
   vector<double>  *GenW_Born_mass;
   vector<double>  *GenW_Born_px;
   vector<double>  *GenW_Born_py;
   vector<double>  *GenW_Born_pz;
   vector<double>  *GenW_Born_pt;
   vector<double>  *GenW_Born_eta;
   vector<double>  *GenW_Born_phi;
   vector<int>     *GenW_BornLept1_id;
   vector<int>     *GenW_BornLept1_status;
   vector<double>  *GenW_BornLept1_px;
   vector<double>  *GenW_BornLept1_py;
   vector<double>  *GenW_BornLept1_pz;
   vector<double>  *GenW_BornLept1_en;
   vector<double>  *GenW_BornLept1_pt;
   vector<double>  *GenW_BornLept1_et;
   vector<double>  *GenW_BornLept1_charge;
   vector<double>  *GenW_BornLept1_eta;
   vector<double>  *GenW_BornLept1_phi;
   vector<int>     *GenW_BornLept2_id;
   vector<int>     *GenW_BornLept2_status;
   vector<double>  *GenW_BornLept2_px;
   vector<double>  *GenW_BornLept2_py;
   vector<double>  *GenW_BornLept2_pz;
   vector<double>  *GenW_BornLept2_en;
   vector<double>  *GenW_BornLept2_pt;
   vector<double>  *GenW_BornLept2_et;
   vector<double>  *GenW_BornLept2_charge;
   vector<double>  *GenW_BornLept2_eta;
   vector<double>  *GenW_BornLept2_phi;
   vector<int>     *GenW_PostLept1_id;
   vector<int>     *GenW_PostLept1_status;
   vector<double>  *GenW_PostLept1_px;
   vector<double>  *GenW_PostLept1_py;
   vector<double>  *GenW_PostLept1_pz;
   vector<double>  *GenW_PostLept1_en;
   vector<double>  *GenW_PostLept1_pt;
   vector<double>  *GenW_PostLept1_et;
   vector<double>  *GenW_PostLept1_charge;
   vector<double>  *GenW_PostLept1_eta;
   vector<double>  *GenW_PostLept1_phi;
   vector<int>     *GenW_PostLept2_id;
   vector<int>     *GenW_PostLept2_status;
   vector<double>  *GenW_PostLept2_px;
   vector<double>  *GenW_PostLept2_py;
   vector<double>  *GenW_PostLept2_pz;
   vector<double>  *GenW_PostLept2_en;
   vector<double>  *GenW_PostLept2_pt;
   vector<double>  *GenW_PostLept2_et;
   vector<double>  *GenW_PostLept2_charge;
   vector<double>  *GenW_PostLept2_eta;
   vector<double>  *GenW_PostLept2_phi;
   Double_t        GenW_Neut_pt;
   vector<int>     *GenZ_Channel;
   vector<int>     *GenZ_nLepts;
   vector<int>     *GenZ_id;
   vector<int>     *GenZ_status;
   vector<double>  *GenZ_mass;
   vector<double>  *GenZ_px;
   vector<double>  *GenZ_py;
   vector<double>  *GenZ_pz;
   vector<double>  *GenZ_pt;
   Double_t        GenZ_Neut_pt;
   vector<double>  *GenZ_eta;
   vector<double>  *GenZ_phi;
   vector<int>     *GenZ_Lept1_id;
   vector<int>     *GenZ_Lept1_status;
   vector<double>  *GenZ_Lept1_px;
   vector<double>  *GenZ_Lept1_py;
   vector<double>  *GenZ_Lept1_pz;
   vector<double>  *GenZ_Lept1_en;
   vector<double>  *GenZ_Lept1_pt;
   vector<double>  *GenZ_Lept1_et;
   vector<double>  *GenZ_Lept1_charge;
   vector<double>  *GenZ_Lept1_eta;
   vector<double>  *GenZ_Lept1_phi;
   vector<int>     *GenZ_Lept2_id;
   vector<int>     *GenZ_Lept2_status;
   vector<double>  *GenZ_Lept2_px;
   vector<double>  *GenZ_Lept2_py;
   vector<double>  *GenZ_Lept2_pz;
   vector<double>  *GenZ_Lept2_en;
   vector<double>  *GenZ_Lept2_pt;
   vector<double>  *GenZ_Lept2_et;
   vector<double>  *GenZ_Lept2_charge;
   vector<double>  *GenZ_Lept2_eta;
   vector<double>  *GenZ_Lept2_phi;
   Double_t        pfMEt_x;
   Double_t        pfMEt_y;
   Double_t        pfMEtSumEt;
   Double_t        pfMEtNeuEM;
   Double_t        pfMEtNeuHad;
   Double_t        pfMEtChHad;
   Double_t        pfMEtChEM;
   Double_t        pfMEtMu;
   Double_t        NoPuMEt_x;
   Double_t        NoPuMEt_y;
   Double_t        NoPuMEtSumEt;
   Double_t        NoPuMEtNeuEM;
   Double_t        NoPuMEtNeuHad;
   Double_t        NoPuMEtChHad;
   Double_t        NoPuMEtChEM;
   Double_t        NoPuMEtMu;
   Double_t        MVaMEt_x;
   Double_t        MVaMEt_y;
   Double_t        MVaMEtSumEt;
   Double_t        MVaMEtNeuEM;
   Double_t        MVaMEtNeuHad;
   Double_t        MVaMEtChHad;
   Double_t        MVaMEtChEM;
   Double_t        MVaMEtMu;
   Double_t        genMEtTrue_x;
   Double_t        genMEtTrue_y;
   Double_t        genMEtTrueSumEt;
   Double_t        genMEtTrueNeuEM;
   Double_t        genMEtTrueNeuHad;
   Double_t        genMEtTrueChHad;
   Double_t        genMEtTrueChEM;
   Double_t        genMEtTrueMu;
   Double_t        genMEtCalo_x;
   Double_t        genMEtCalo_y;
   Double_t        genMEtCaloSumEt;
   Double_t        genMEtCaloNeuEM;
   Double_t        genMEtCaloNeuHad;
   Double_t        genMEtCaloChHad;
   Double_t        genMEtCaloChEM;
   Double_t        genMEtCaloMu;
   Double_t        genMEtCaloAndNonPrompt_x;
   Double_t        genMEtCaloAndNonPrompt_y;
   Double_t        genMEtCaloAndNonPromptSumEt;
   Double_t        genMEtCaloAndNonPromptNeuEM;
   Double_t        genMEtCaloAndNonPromptNeuHad;
   Double_t        genMEtCaloAndNonPromptChHad;
   Double_t        genMEtCaloAndNonPromptChEM;
   Double_t        genMEtCaloAndNonPromptMu;

   // List of branches
   TBranch        *b_EVENT;   //!
   TBranch        *b_RUN;   //!
   TBranch        *b_LUMI;   //!
   TBranch        *b_Channel;   //!
   TBranch        *b_npileup;   //!
   TBranch        *b_weightin;   //!
   TBranch        *b_weight;   //!
   TBranch        *b_weightplus;   //!
   TBranch        *b_weightminus;   //!
   TBranch        *b_rhoIso;   //!
   TBranch        *b_vtx_isFake;   //!
   TBranch        *b_vtx_ndof;   //!
   TBranch        *b_vtx_z;   //!
   TBranch        *b_vtx_Rho;   //!
   TBranch        *b_weightFSR;   //!
   TBranch        *b_HLT_Ele22_CaloIdL_CaloIsoVL;   //!
   TBranch        *b_HLT_Ele27_WP80;   //!
   TBranch        *b_HLT_Mu15_eta2p1;   //!
   TBranch        *b_Z_Channel;   //!
   TBranch        *b_Z_Lept1_chIso03;   //!
   TBranch        *b_Z_Lept1_chIso04;   //!
   TBranch        *b_Z_Lept1_nhIso03;   //!
   TBranch        *b_Z_Lept1_nhIso04;   //!
   TBranch        *b_Z_Lept1_phIso03;   //!
   TBranch        *b_Z_Lept1_phIso04;   //!
   TBranch        *b_Z_Lept1_pcIso03;   //!
   TBranch        *b_Z_Lept1_pcIso04;   //!
   TBranch        *b_Z_Lept1_relIsoCom03;   //!
   TBranch        *b_Z_Lept1_relIsoCom04;   //!
   TBranch        *b_Z_Lept1_relIsoBeta03;   //!
   TBranch        *b_Z_Lept1_relIsoBeta04;   //!
   TBranch        *b_Z_Lept1_relIsoRho03;   //!
   TBranch        *b_Z_Lept1_RelisolPtTrks03;   //!
   TBranch        *b_Z_Lept1_RelisoEm03;   //!
   TBranch        *b_Z_Lept1_RelisoHad03;   //!
   TBranch        *b_Z_Lept2_chIso03;   //!
   TBranch        *b_Z_Lept2_chIso04;   //!
   TBranch        *b_Z_Lept2_nhIso03;   //!
   TBranch        *b_Z_Lept2_nhIso04;   //!
   TBranch        *b_Z_Lept2_phIso03;   //!
   TBranch        *b_Z_Lept2_phIso04;   //!
   TBranch        *b_Z_Lept2_pcIso03;   //!
   TBranch        *b_Z_Lept2_pcIso04;   //!
   TBranch        *b_Z_Lept2_relIsoCom03;   //!
   TBranch        *b_Z_Lept2_relIsoCom04;   //!
   TBranch        *b_Z_Lept2_relIsoBeta03;   //!
   TBranch        *b_Z_Lept2_relIsoBeta04;   //!
   TBranch        *b_Z_Lept2_relIsoRho03;   //!
   TBranch        *b_Z_Lept2_RelisolPtTrks03;   //!
   TBranch        *b_Z_Lept2_RelisoEm03;   //!
   TBranch        *b_Z_Lept2_RelisoHad03;   //!
   TBranch        *b_Z_Lept1_isGlobal;   //!
   TBranch        *b_Z_Lept1_isTrker;   //!
   TBranch        *b_Z_Lept1_MedComIsoDelBetCorr3Hits;   //!
   TBranch        *b_Z_Lept1_decModFind;   //!
   TBranch        *b_Z_Lept1_pt;   //!
   TBranch        *b_Z_Lept1_et;   //!
   TBranch        *b_Z_Lept1_charge;   //!
   TBranch        *b_Z_Lept1_eta;   //!
   TBranch        *b_Z_Lept1_phi;   //!
   TBranch        *b_Z_Lept1_px;   //!
   TBranch        *b_Z_Lept1_py;   //!
   TBranch        *b_Z_Lept1_pz;   //!
   TBranch        *b_Z_Lept1_en;   //!
   TBranch        *b_Z_Lept1_matchStations;   //!
   TBranch        *b_Z_Lept1_dB;   //!
   TBranch        *b_Z_Lept2_isGlobal;   //!
   TBranch        *b_Z_Lept2_isTrker;   //!
   TBranch        *b_Z_Lept2_MedComIsoDelBetCorr3Hits;   //!
   TBranch        *b_Z_Lept2_decModFind;   //!
   TBranch        *b_Z_Lept2_pt;   //!
   TBranch        *b_Z_Lept2_et;   //!
   TBranch        *b_Z_Lept2_charge;   //!
   TBranch        *b_Z_Lept2_eta;   //!
   TBranch        *b_Z_Lept2_phi;   //!
   TBranch        *b_Z_Lept2_px;   //!
   TBranch        *b_Z_Lept2_py;   //!
   TBranch        *b_Z_Lept2_pz;   //!
   TBranch        *b_Z_Lept2_en;   //!
   TBranch        *b_Z_Lept2_matchStations;   //!
   TBranch        *b_Z_Lept2_dB;   //!
   TBranch        *b_Z_Lept1_dz;   //!
   TBranch        *b_Z_Lept1_globalNormChi2;   //!
   TBranch        *b_Z_Lept1_muonHits;   //!
   TBranch        *b_Z_Lept1_trkLayers;   //!
   TBranch        *b_Z_Lept1_trackerHits;   //!
   TBranch        *b_Z_Lept1_pixelHits;   //!
   TBranch        *b_Z_Lept2_dz;   //!
   TBranch        *b_Z_Lept2_globalNormChi2;   //!
   TBranch        *b_Z_Lept2_muonHits;   //!
   TBranch        *b_Z_Lept2_trkLayers;   //!
   TBranch        *b_Z_Lept2_trackerHits;   //!
   TBranch        *b_Z_Lept2_pixelHits;   //!
   TBranch        *b_Z_Lept1_etaSC;   //!
   TBranch        *b_Z_Lept1_phiSC;   //!
   TBranch        *b_Z_Lept1_dEtaIn;   //!
   TBranch        *b_Z_Lept1_dPhiIn;   //!
   TBranch        *b_Z_Lept1_sigmaIEtaIEta;   //!
   TBranch        *b_Z_Lept1_HoverE;   //!
   TBranch        *b_Z_Lept1_fbrem;   //!
   TBranch        *b_Z_Lept1_energyEC;   //!
   TBranch        *b_Z_Lept1_Pnorm;   //!
   TBranch        *b_Z_Lept1_InvEminusInvP;   //!
   TBranch        *b_Z_Lept1_dxy;   //!
   TBranch        *b_Z_Lept1_AEff03;   //!
   TBranch        *b_Z_Lept1_hasConversion;   //!
   TBranch        *b_Z_Lept1_mHits;   //!
   TBranch        *b_Z_Lept1_SCcharge;   //!
   TBranch        *b_Z_Lept1_TKcharge;   //!
   TBranch        *b_Z_Lept1_GSFcharge;   //!
   TBranch        *b_Z_Lept1_GsfCtfScPixchargeConsistentcheck;   //!
   TBranch        *b_Z_Lept2_etaSC;   //!
   TBranch        *b_Z_Lept2_phiSC;   //!
   TBranch        *b_Z_Lept2_dEtaIn;   //!
   TBranch        *b_Z_Lept2_dPhiIn;   //!
   TBranch        *b_Z_Lept2_sigmaIEtaIEta;   //!
   TBranch        *b_Z_Lept2_HoverE;   //!
   TBranch        *b_Z_Lept2_fbrem;   //!
   TBranch        *b_Z_Lept2_energyEC;   //!
   TBranch        *b_Z_Lept2_Pnorm;   //!
   TBranch        *b_Z_Lept2_InvEminusInvP;   //!
   TBranch        *b_Z_Lept2_dxy;   //!
   TBranch        *b_Z_Lept2_AEff03;   //!
   TBranch        *b_Z_Lept2_hasConversion;   //!
   TBranch        *b_Z_Lept2_mHits;   //!
   TBranch        *b_Z_Lept2_SCcharge;   //!
   TBranch        *b_Z_Lept2_TKcharge;   //!
   TBranch        *b_Z_Lept2_GSFcharge;   //!
   TBranch        *b_Z_Lept2_GsfCtfScPixchargeConsistentcheck;   //!
   TBranch        *b_Z_Lept1_genIdxMatch;   //!
   TBranch        *b_Z_Lept1_genDeltaR;   //!
   TBranch        *b_Z_Lept1_genDPtRel;   //!
   TBranch        *b_Z_Lept2_genIdxMatch;   //!
   TBranch        *b_Z_Lept2_genDeltaR;   //!
   TBranch        *b_Z_Lept2_genDPtRel;   //!
   TBranch        *b_Z_diLeptVtxProb;   //!
   TBranch        *b_Z_Mass;   //!
   TBranch        *b_Z_phi;   //!
   TBranch        *b_Z_eta;   //!
   TBranch        *b_Z_pt;   //!
   TBranch        *b_Z_px;   //!
   TBranch        *b_Z_py;   //!
   TBranch        *b_Z_pz;   //!
   TBranch        *b_Z_Neut_pt;   //!
   TBranch        *b_Z_Neut_phi;   //!
   TBranch        *b_Z_Neut_px;   //!
   TBranch        *b_Z_Neut_py;   //!
   TBranch        *b_Z_Sign;   //!
   TBranch        *b_W_Lept1_ptcID;   //!
   TBranch        *b_W_Lept1_chIso03;   //!
   TBranch        *b_W_Lept1_chIso04;   //!
   TBranch        *b_W_Lept1_nhIso03;   //!
   TBranch        *b_W_Lept1_nhIso04;   //!
   TBranch        *b_W_Lept1_phIso03;   //!
   TBranch        *b_W_Lept1_phIso04;   //!
   TBranch        *b_W_Lept1_pcIso03;   //!
   TBranch        *b_W_Lept1_pcIso04;   //!
   TBranch        *b_W_Lept1_relIsoCom03;   //!
   TBranch        *b_W_Lept1_relIsoCom04;   //!
   TBranch        *b_W_Lept1_relIsoBeta03;   //!
   TBranch        *b_W_Lept1_relIsoBeta04;   //!
   TBranch        *b_W_Lept1_relIsoRho03;   //!
   TBranch        *b_W_Lept1_RelisolPtTrks03;   //!
   TBranch        *b_W_Lept1_RelisoEm03;   //!
   TBranch        *b_W_Lept1_RelisoHad03;   //!
   TBranch        *b_W_Lept1_isGlobal;   //!
   TBranch        *b_W_Lept1_isTrker;   //!
   TBranch        *b_W_Lept1_MedComIsoDelBetCorr3Hits;   //!
   TBranch        *b_W_Lept1_decModFind;   //!
   TBranch        *b_W_Lept1_pt;   //!
   TBranch        *b_W_Lept1_et;   //!
   TBranch        *b_W_Lept1_charge;   //!
   TBranch        *b_W_Lept1_eta;   //!
   TBranch        *b_W_Lept1_phi;   //!
   TBranch        *b_W_Lept1_px;   //!
   TBranch        *b_W_Lept1_py;   //!
   TBranch        *b_W_Lept1_pz;   //!
   TBranch        *b_W_Lept1_en;   //!
   TBranch        *b_W_Lept1_matchStations;   //!
   TBranch        *b_W_Lept1_dB;   //!
   TBranch        *b_W_Lept1_dz;   //!
   TBranch        *b_W_Lept1_globalNormChi2;   //!
   TBranch        *b_W_Lept1_muonHits;   //!
   TBranch        *b_W_Lept1_trkLayers;   //!
   TBranch        *b_W_Lept1_trackerHits;   //!
   TBranch        *b_W_Lept1_pixelHits;   //!
   TBranch        *b_W_Lept1_etaSC;   //!
   TBranch        *b_W_Lept1_phiSC;   //!
   TBranch        *b_W_Lept1_dEtaIn;   //!
   TBranch        *b_W_Lept1_dPhiIn;   //!
   TBranch        *b_W_Lept1_sigmaIEtaIEta;   //!
   TBranch        *b_W_Lept1_HoverE;   //!
   TBranch        *b_W_Lept1_fbrem;   //!
   TBranch        *b_W_Lept1_energyEC;   //!
   TBranch        *b_W_Lept1_Pnorm;   //!
   TBranch        *b_W_Lept1_InvEminusInvP;   //!
   TBranch        *b_W_Lept1_dxy;   //!
   TBranch        *b_W_Lept1_AEff03;   //!
   TBranch        *b_W_Lept1_hasConversion;   //!
   TBranch        *b_W_Lept1_mHits;   //!
   TBranch        *b_W_Lept1_SCcharge;   //!
   TBranch        *b_W_Lept1_TKcharge;   //!
   TBranch        *b_W_Lept1_GSFcharge;   //!
   TBranch        *b_W_Lept1_GsfCtfScPixchargeConsistentcheck;   //!
   TBranch        *b_W_Lept1_genIdxMatch;   //!
   TBranch        *b_W_Lept1_genDeltaR;   //!
   TBranch        *b_W_Lept1_genDPtRel;   //!
   TBranch        *b_W_invm;   //!
   TBranch        *b_W_Neut_pt;   //!
   TBranch        *b_W_Neut_phi;   //!
   TBranch        *b_W_Neut_px;   //!
   TBranch        *b_W_Neut_py;   //!
   TBranch        *b_W_pt;   //!
   TBranch        *b_W_eta;   //!
   TBranch        *b_W_phi;   //!
   TBranch        *b_W_px;   //!
   TBranch        *b_W_py;   //!
   TBranch        *b_W_pz;   //!
   TBranch        *b_W_Mt;   //!
   TBranch        *b_W_Acop;   //!
   TBranch        *b_W_Charge;   //!
   TBranch        *b_GenW_Born_nLepts;   //!
   TBranch        *b_GenW_Born_Id;   //!
   TBranch        *b_GenW_Born_Status;   //!
   TBranch        *b_GenW_Born_mass;   //!
   TBranch        *b_GenW_Born_px;   //!
   TBranch        *b_GenW_Born_py;   //!
   TBranch        *b_GenW_Born_pz;   //!
   TBranch        *b_GenW_Born_pt;   //!
   TBranch        *b_GenW_Born_eta;   //!
   TBranch        *b_GenW_Born_phi;   //!
   TBranch        *b_GenW_BornLept1_id;   //!
   TBranch        *b_GenW_BornLept1_status;   //!
   TBranch        *b_GenW_BornLept1_px;   //!
   TBranch        *b_GenW_BornLept1_py;   //!
   TBranch        *b_GenW_BornLept1_pz;   //!
   TBranch        *b_GenW_BornLept1_en;   //!
   TBranch        *b_GenW_BornLept1_pt;   //!
   TBranch        *b_GenW_BornLept1_et;   //!
   TBranch        *b_GenW_BornLept1_charge;   //!
   TBranch        *b_GenW_BornLept1_eta;   //!
   TBranch        *b_GenW_BornLept1_phi;   //!
   TBranch        *b_GenW_BornLept2_id;   //!
   TBranch        *b_GenW_BornLept2_status;   //!
   TBranch        *b_GenW_BornLept2_px;   //!
   TBranch        *b_GenW_BornLept2_py;   //!
   TBranch        *b_GenW_BornLept2_pz;   //!
   TBranch        *b_GenW_BornLept2_en;   //!
   TBranch        *b_GenW_BornLept2_pt;   //!
   TBranch        *b_GenW_BornLept2_et;   //!
   TBranch        *b_GenW_BornLept2_charge;   //!
   TBranch        *b_GenW_BornLept2_eta;   //!
   TBranch        *b_GenW_BornLept2_phi;   //!
   TBranch        *b_GenW_PostLept1_id;   //!
   TBranch        *b_GenW_PostLept1_status;   //!
   TBranch        *b_GenW_PostLept1_px;   //!
   TBranch        *b_GenW_PostLept1_py;   //!
   TBranch        *b_GenW_PostLept1_pz;   //!
   TBranch        *b_GenW_PostLept1_en;   //!
   TBranch        *b_GenW_PostLept1_pt;   //!
   TBranch        *b_GenW_PostLept1_et;   //!
   TBranch        *b_GenW_PostLept1_charge;   //!
   TBranch        *b_GenW_PostLept1_eta;   //!
   TBranch        *b_GenW_PostLept1_phi;   //!
   TBranch        *b_GenW_PostLept2_id;   //!
   TBranch        *b_GenW_PostLept2_status;   //!
   TBranch        *b_GenW_PostLept2_px;   //!
   TBranch        *b_GenW_PostLept2_py;   //!
   TBranch        *b_GenW_PostLept2_pz;   //!
   TBranch        *b_GenW_PostLept2_en;   //!
   TBranch        *b_GenW_PostLept2_pt;   //!
   TBranch        *b_GenW_PostLept2_et;   //!
   TBranch        *b_GenW_PostLept2_charge;   //!
   TBranch        *b_GenW_PostLept2_eta;   //!
   TBranch        *b_GenW_PostLept2_phi;   //!
   TBranch        *b_GenW_Neut_pt;   //!
   TBranch        *b_GenZ_Channel;   //!
   TBranch        *b_GenZ_nLepts;   //!
   TBranch        *b_GenZ_id;   //!
   TBranch        *b_GenZ_status;   //!
   TBranch        *b_GenZ_mass;   //!
   TBranch        *b_GenZ_px;   //!
   TBranch        *b_GenZ_py;   //!
   TBranch        *b_GenZ_pz;   //!
   TBranch        *b_GenZ_pt;   //!
   TBranch        *b_GenZ_Neut_pt;   //!
   TBranch        *b_GenZ_eta;   //!
   TBranch        *b_GenZ_phi;   //!
   TBranch        *b_GenZ_Lept1_id;   //!
   TBranch        *b_GenZ_Lept1_status;   //!
   TBranch        *b_GenZ_Lept1_px;   //!
   TBranch        *b_GenZ_Lept1_py;   //!
   TBranch        *b_GenZ_Lept1_pz;   //!
   TBranch        *b_GenZ_Lept1_en;   //!
   TBranch        *b_GenZ_Lept1_pt;   //!
   TBranch        *b_GenZ_Lept1_et;   //!
   TBranch        *b_GenZ_Lept1_charge;   //!
   TBranch        *b_GenZ_Lept1_eta;   //!
   TBranch        *b_GenZ_Lept1_phi;   //!
   TBranch        *b_GenZ_Lept2_id;   //!
   TBranch        *b_GenZ_Lept2_status;   //!
   TBranch        *b_GenZ_Lept2_px;   //!
   TBranch        *b_GenZ_Lept2_py;   //!
   TBranch        *b_GenZ_Lept2_pz;   //!
   TBranch        *b_GenZ_Lept2_en;   //!
   TBranch        *b_GenZ_Lept2_pt;   //!
   TBranch        *b_GenZ_Lept2_et;   //!
   TBranch        *b_GenZ_Lept2_charge;   //!
   TBranch        *b_GenZ_Lept2_eta;   //!
   TBranch        *b_GenZ_Lept2_phi;   //!
   TBranch        *b_pfMEt_x;   //!
   TBranch        *b_pfMEt_y;   //!
   TBranch        *b_pfMEtSumEt;   //!
   TBranch        *b_pfMEtNeuEM;   //!
   TBranch        *b_pfMEtNeuHad;   //!
   TBranch        *b_pfMEtChHad;   //!
   TBranch        *b_pfMEtChEM;   //!
   TBranch        *b_pfMEtMu;   //!
   TBranch        *b_NoPuMEt_x;   //!
   TBranch        *b_NoPuMEt_y;   //!
   TBranch        *b_NoPuMEtSumEt;   //!
   TBranch        *b_NoPuMEtNeuEM;   //!
   TBranch        *b_NoPuMEtNeuHad;   //!
   TBranch        *b_NoPuMEtChHad;   //!
   TBranch        *b_NoPuMEtChEM;   //!
   TBranch        *b_NoPuMEtMu;   //!
   TBranch        *b_MVaMEt_x;   //!
   TBranch        *b_MVaMEt_y;   //!
   TBranch        *b_MVaMEtSumEt;   //!
   TBranch        *b_MVaMEtNeuEM;   //!
   TBranch        *b_MVaMEtNeuHad;   //!
   TBranch        *b_MVaMEtChHad;   //!
   TBranch        *b_MVaMEtChEM;   //!
   TBranch        *b_MVaMEtMu;   //!
   TBranch        *b_genMEtTrue_x;   //!
   TBranch        *b_genMEtTrue_y;   //!
   TBranch        *b_genMEtTrueSumEt;   //!
   TBranch        *b_genMEtTrueNeuEM;   //!
   TBranch        *b_genMEtTrueNeuHad;   //!
   TBranch        *b_genMEtTrueChHad;   //!
   TBranch        *b_genMEtTrueChEM;   //!
   TBranch        *b_genMEtTrueMu;   //!
   TBranch        *b_genMEtCalo_x;   //!
   TBranch        *b_genMEtCalo_y;   //!
   TBranch        *b_genMEtCaloSumEt;   //!
   TBranch        *b_genMEtCaloNeuEM;   //!
   TBranch        *b_genMEtCaloNeuHad;   //!
   TBranch        *b_genMEtCaloChHad;   //!
   TBranch        *b_genMEtCaloChEM;   //!
   TBranch        *b_genMEtCaloMu;   //!
   TBranch        *b_genMEtCaloAndNonPrompt_x;   //!
   TBranch        *b_genMEtCaloAndNonPrompt_y;   //!
   TBranch        *b_genMEtCaloAndNonPromptSumEt;   //!
   TBranch        *b_genMEtCaloAndNonPromptNeuEM;   //!
   TBranch        *b_genMEtCaloAndNonPromptNeuHad;   //!
   TBranch        *b_genMEtCaloAndNonPromptChHad;   //!
   TBranch        *b_genMEtCaloAndNonPromptChEM;   //!
   TBranch        *b_genMEtCaloAndNonPromptMu;   //!

   WZ3LNT(TTree *tree=0);
   virtual ~WZ3LNT();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef WZ3LNT_cxx
WZ3LNT::WZ3LNT(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {

#ifdef SINGLE_TREE
      // The following code should be used if you want this class to access
      // a single tree instead of a chain
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Memory Directory");
      if (!f || !f->IsOpen()) {
         f = new TFile("Memory Directory");
      }
      f->GetObject("WZ3LNu/tree",tree);

#else // SINGLE_TREE

      // The following code should be used if you want this class to access a chain
      // of trees.
      TChain * chain = new TChain("WZ3LNu/tree","");
      chain->Add("/terranova_1/TestNtuple/TerraTuple.root/WZ3LNu/tree");
      tree = chain;
#endif // SINGLE_TREE

   }
   Init(tree);
}

WZ3LNT::~WZ3LNT()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t WZ3LNT::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t WZ3LNT::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void WZ3LNT::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   vtx_isFake = 0;
   vtx_ndof = 0;
   vtx_z = 0;
   vtx_Rho = 0;
   Z_Channel = 0;
   Z_Lept1_chIso03 = 0;
   Z_Lept1_chIso04 = 0;
   Z_Lept1_nhIso03 = 0;
   Z_Lept1_nhIso04 = 0;
   Z_Lept1_phIso03 = 0;
   Z_Lept1_phIso04 = 0;
   Z_Lept1_pcIso03 = 0;
   Z_Lept1_pcIso04 = 0;
   Z_Lept1_relIsoCom03 = 0;
   Z_Lept1_relIsoCom04 = 0;
   Z_Lept1_relIsoBeta03 = 0;
   Z_Lept1_relIsoBeta04 = 0;
   Z_Lept1_relIsoRho03 = 0;
   Z_Lept1_RelisolPtTrks03 = 0;
   Z_Lept1_RelisoEm03 = 0;
   Z_Lept1_RelisoHad03 = 0;
   Z_Lept2_chIso03 = 0;
   Z_Lept2_chIso04 = 0;
   Z_Lept2_nhIso03 = 0;
   Z_Lept2_nhIso04 = 0;
   Z_Lept2_phIso03 = 0;
   Z_Lept2_phIso04 = 0;
   Z_Lept2_pcIso03 = 0;
   Z_Lept2_pcIso04 = 0;
   Z_Lept2_relIsoCom03 = 0;
   Z_Lept2_relIsoCom04 = 0;
   Z_Lept2_relIsoBeta03 = 0;
   Z_Lept2_relIsoBeta04 = 0;
   Z_Lept2_relIsoRho03 = 0;
   Z_Lept2_RelisolPtTrks03 = 0;
   Z_Lept2_RelisoEm03 = 0;
   Z_Lept2_RelisoHad03 = 0;
   Z_Lept1_isGlobal = 0;
   Z_Lept1_isTrker = 0;
   Z_Lept1_MedComIsoDelBetCorr3Hits = 0;
   Z_Lept1_decModFind = 0;
   Z_Lept1_pt = 0;
   Z_Lept1_et = 0;
   Z_Lept1_charge = 0;
   Z_Lept1_eta = 0;
   Z_Lept1_phi = 0;
   Z_Lept1_px = 0;
   Z_Lept1_py = 0;
   Z_Lept1_pz = 0;
   Z_Lept1_en = 0;
   Z_Lept1_matchStations = 0;
   Z_Lept1_dB = 0;
   Z_Lept2_isGlobal = 0;
   Z_Lept2_isTrker = 0;
   Z_Lept2_MedComIsoDelBetCorr3Hits = 0;
   Z_Lept2_decModFind = 0;
   Z_Lept2_pt = 0;
   Z_Lept2_et = 0;
   Z_Lept2_charge = 0;
   Z_Lept2_eta = 0;
   Z_Lept2_phi = 0;
   Z_Lept2_px = 0;
   Z_Lept2_py = 0;
   Z_Lept2_pz = 0;
   Z_Lept2_en = 0;
   Z_Lept2_matchStations = 0;
   Z_Lept2_dB = 0;
   Z_Lept1_dz = 0;
   Z_Lept1_globalNormChi2 = 0;
   Z_Lept1_muonHits = 0;
   Z_Lept1_trkLayers = 0;
   Z_Lept1_trackerHits = 0;
   Z_Lept1_pixelHits = 0;
   Z_Lept2_dz = 0;
   Z_Lept2_globalNormChi2 = 0;
   Z_Lept2_muonHits = 0;
   Z_Lept2_trkLayers = 0;
   Z_Lept2_trackerHits = 0;
   Z_Lept2_pixelHits = 0;
   Z_Lept1_etaSC = 0;
   Z_Lept1_phiSC = 0;
   Z_Lept1_dEtaIn = 0;
   Z_Lept1_dPhiIn = 0;
   Z_Lept1_sigmaIEtaIEta = 0;
   Z_Lept1_HoverE = 0;
   Z_Lept1_fbrem = 0;
   Z_Lept1_energyEC = 0;
   Z_Lept1_Pnorm = 0;
   Z_Lept1_InvEminusInvP = 0;
   Z_Lept1_dxy = 0;
   Z_Lept1_AEff03 = 0;
   Z_Lept1_hasConversion = 0;
   Z_Lept1_mHits = 0;
   Z_Lept1_SCcharge = 0;
   Z_Lept1_TKcharge = 0;
   Z_Lept1_GSFcharge = 0;
   Z_Lept1_GsfCtfScPixchargeConsistentcheck = 0;
   Z_Lept2_etaSC = 0;
   Z_Lept2_phiSC = 0;
   Z_Lept2_dEtaIn = 0;
   Z_Lept2_dPhiIn = 0;
   Z_Lept2_sigmaIEtaIEta = 0;
   Z_Lept2_HoverE = 0;
   Z_Lept2_fbrem = 0;
   Z_Lept2_energyEC = 0;
   Z_Lept2_Pnorm = 0;
   Z_Lept2_InvEminusInvP = 0;
   Z_Lept2_dxy = 0;
   Z_Lept2_AEff03 = 0;
   Z_Lept2_hasConversion = 0;
   Z_Lept2_mHits = 0;
   Z_Lept2_SCcharge = 0;
   Z_Lept2_TKcharge = 0;
   Z_Lept2_GSFcharge = 0;
   Z_Lept2_GsfCtfScPixchargeConsistentcheck = 0;
   Z_Lept1_genIdxMatch = 0;
   Z_Lept1_genDeltaR = 0;
   Z_Lept1_genDPtRel = 0;
   Z_Lept2_genIdxMatch = 0;
   Z_Lept2_genDeltaR = 0;
   Z_Lept2_genDPtRel = 0;
   Z_diLeptVtxProb = 0;
   Z_Mass = 0;
   Z_phi = 0;
   Z_eta = 0;
   Z_pt = 0;
   Z_px = 0;
   Z_py = 0;
   Z_pz = 0;
   Z_Neut_pt = 0;
   Z_Neut_phi = 0;
   Z_Neut_px = 0;
   Z_Neut_py = 0;
   Z_Sign = 0;
   W_Lept1_ptcID = 0;
   W_Lept1_chIso03 = 0;
   W_Lept1_chIso04 = 0;
   W_Lept1_nhIso03 = 0;
   W_Lept1_nhIso04 = 0;
   W_Lept1_phIso03 = 0;
   W_Lept1_phIso04 = 0;
   W_Lept1_pcIso03 = 0;
   W_Lept1_pcIso04 = 0;
   W_Lept1_relIsoCom03 = 0;
   W_Lept1_relIsoCom04 = 0;
   W_Lept1_relIsoBeta03 = 0;
   W_Lept1_relIsoBeta04 = 0;
   W_Lept1_relIsoRho03 = 0;
   W_Lept1_RelisolPtTrks03 = 0;
   W_Lept1_RelisoEm03 = 0;
   W_Lept1_RelisoHad03 = 0;
   W_Lept1_isGlobal = 0;
   W_Lept1_isTrker = 0;
   W_Lept1_MedComIsoDelBetCorr3Hits = 0;
   W_Lept1_decModFind = 0;
   W_Lept1_pt = 0;
   W_Lept1_et = 0;
   W_Lept1_charge = 0;
   W_Lept1_eta = 0;
   W_Lept1_phi = 0;
   W_Lept1_px = 0;
   W_Lept1_py = 0;
   W_Lept1_pz = 0;
   W_Lept1_en = 0;
   W_Lept1_matchStations = 0;
   W_Lept1_dB = 0;
   W_Lept1_dz = 0;
   W_Lept1_globalNormChi2 = 0;
   W_Lept1_muonHits = 0;
   W_Lept1_trkLayers = 0;
   W_Lept1_trackerHits = 0;
   W_Lept1_pixelHits = 0;
   W_Lept1_etaSC = 0;
   W_Lept1_phiSC = 0;
   W_Lept1_dEtaIn = 0;
   W_Lept1_dPhiIn = 0;
   W_Lept1_sigmaIEtaIEta = 0;
   W_Lept1_HoverE = 0;
   W_Lept1_fbrem = 0;
   W_Lept1_energyEC = 0;
   W_Lept1_Pnorm = 0;
   W_Lept1_InvEminusInvP = 0;
   W_Lept1_dxy = 0;
   W_Lept1_AEff03 = 0;
   W_Lept1_hasConversion = 0;
   W_Lept1_mHits = 0;
   W_Lept1_SCcharge = 0;
   W_Lept1_TKcharge = 0;
   W_Lept1_GSFcharge = 0;
   W_Lept1_GsfCtfScPixchargeConsistentcheck = 0;
   W_Lept1_genIdxMatch = 0;
   W_Lept1_genDeltaR = 0;
   W_Lept1_genDPtRel = 0;
   W_invm = 0;
   W_Neut_pt = 0;
   W_Neut_phi = 0;
   W_Neut_px = 0;
   W_Neut_py = 0;
   W_pt = 0;
   W_eta = 0;
   W_phi = 0;
   W_px = 0;
   W_py = 0;
   W_pz = 0;
   W_Mt = 0;
   W_Acop = 0;
   W_Charge = 0;
   GenW_Born_nLepts = 0;
   GenW_Born_Id = 0;
   GenW_Born_Status = 0;
   GenW_Born_mass = 0;
   GenW_Born_px = 0;
   GenW_Born_py = 0;
   GenW_Born_pz = 0;
   GenW_Born_pt = 0;
   GenW_Born_eta = 0;
   GenW_Born_phi = 0;
   GenW_BornLept1_id = 0;
   GenW_BornLept1_status = 0;
   GenW_BornLept1_px = 0;
   GenW_BornLept1_py = 0;
   GenW_BornLept1_pz = 0;
   GenW_BornLept1_en = 0;
   GenW_BornLept1_pt = 0;
   GenW_BornLept1_et = 0;
   GenW_BornLept1_charge = 0;
   GenW_BornLept1_eta = 0;
   GenW_BornLept1_phi = 0;
   GenW_BornLept2_id = 0;
   GenW_BornLept2_status = 0;
   GenW_BornLept2_px = 0;
   GenW_BornLept2_py = 0;
   GenW_BornLept2_pz = 0;
   GenW_BornLept2_en = 0;
   GenW_BornLept2_pt = 0;
   GenW_BornLept2_et = 0;
   GenW_BornLept2_charge = 0;
   GenW_BornLept2_eta = 0;
   GenW_BornLept2_phi = 0;
   GenW_PostLept1_id = 0;
   GenW_PostLept1_status = 0;
   GenW_PostLept1_px = 0;
   GenW_PostLept1_py = 0;
   GenW_PostLept1_pz = 0;
   GenW_PostLept1_en = 0;
   GenW_PostLept1_pt = 0;
   GenW_PostLept1_et = 0;
   GenW_PostLept1_charge = 0;
   GenW_PostLept1_eta = 0;
   GenW_PostLept1_phi = 0;
   GenW_PostLept2_id = 0;
   GenW_PostLept2_status = 0;
   GenW_PostLept2_px = 0;
   GenW_PostLept2_py = 0;
   GenW_PostLept2_pz = 0;
   GenW_PostLept2_en = 0;
   GenW_PostLept2_pt = 0;
   GenW_PostLept2_et = 0;
   GenW_PostLept2_charge = 0;
   GenW_PostLept2_eta = 0;
   GenW_PostLept2_phi = 0;
   GenZ_Channel = 0;
   GenZ_nLepts = 0;
   GenZ_id = 0;
   GenZ_status = 0;
   GenZ_mass = 0;
   GenZ_px = 0;
   GenZ_py = 0;
   GenZ_pz = 0;
   GenZ_pt = 0;
   GenZ_eta = 0;
   GenZ_phi = 0;
   GenZ_Lept1_id = 0;
   GenZ_Lept1_status = 0;
   GenZ_Lept1_px = 0;
   GenZ_Lept1_py = 0;
   GenZ_Lept1_pz = 0;
   GenZ_Lept1_en = 0;
   GenZ_Lept1_pt = 0;
   GenZ_Lept1_et = 0;
   GenZ_Lept1_charge = 0;
   GenZ_Lept1_eta = 0;
   GenZ_Lept1_phi = 0;
   GenZ_Lept2_id = 0;
   GenZ_Lept2_status = 0;
   GenZ_Lept2_px = 0;
   GenZ_Lept2_py = 0;
   GenZ_Lept2_pz = 0;
   GenZ_Lept2_en = 0;
   GenZ_Lept2_pt = 0;
   GenZ_Lept2_et = 0;
   GenZ_Lept2_charge = 0;
   GenZ_Lept2_eta = 0;
   GenZ_Lept2_phi = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("EVENT", &EVENT, &b_EVENT);
   fChain->SetBranchAddress("RUN", &RUN, &b_RUN);
   fChain->SetBranchAddress("LUMI", &LUMI, &b_LUMI);
   fChain->SetBranchAddress("Channel", &Channel, &b_Channel);
   fChain->SetBranchAddress("npileup", &npileup, &b_npileup);
   fChain->SetBranchAddress("weightin", &weightin, &b_weightin);
   fChain->SetBranchAddress("weight", &weight, &b_weight);
   fChain->SetBranchAddress("weightplus", &weightplus, &b_weightplus);
   fChain->SetBranchAddress("weightminus", &weightminus, &b_weightminus);
   fChain->SetBranchAddress("rhoIso", &rhoIso, &b_rhoIso);
   fChain->SetBranchAddress("vtx_isFake", &vtx_isFake, &b_vtx_isFake);
   fChain->SetBranchAddress("vtx_ndof", &vtx_ndof, &b_vtx_ndof);
   fChain->SetBranchAddress("vtx_z", &vtx_z, &b_vtx_z);
   fChain->SetBranchAddress("vtx_Rho", &vtx_Rho, &b_vtx_Rho);
   fChain->SetBranchAddress("weightFSR", &weightFSR, &b_weightFSR);
   fChain->SetBranchAddress("HLT_Ele22_CaloIdL_CaloIsoVL", &HLT_Ele22_CaloIdL_CaloIsoVL_version, &b_HLT_Ele22_CaloIdL_CaloIsoVL);
   fChain->SetBranchAddress("HLT_Ele27_WP80", &HLT_Ele27_WP80_version, &b_HLT_Ele27_WP80);
   fChain->SetBranchAddress("HLT_Mu15_eta2p1", &HLT_Mu15_eta2p1_version, &b_HLT_Mu15_eta2p1);
   fChain->SetBranchAddress("Z_Channel", &Z_Channel, &b_Z_Channel);
   fChain->SetBranchAddress("Z_Lept1_chIso03", &Z_Lept1_chIso03, &b_Z_Lept1_chIso03);
   fChain->SetBranchAddress("Z_Lept1_chIso04", &Z_Lept1_chIso04, &b_Z_Lept1_chIso04);
   fChain->SetBranchAddress("Z_Lept1_nhIso03", &Z_Lept1_nhIso03, &b_Z_Lept1_nhIso03);
   fChain->SetBranchAddress("Z_Lept1_nhIso04", &Z_Lept1_nhIso04, &b_Z_Lept1_nhIso04);
   fChain->SetBranchAddress("Z_Lept1_phIso03", &Z_Lept1_phIso03, &b_Z_Lept1_phIso03);
   fChain->SetBranchAddress("Z_Lept1_phIso04", &Z_Lept1_phIso04, &b_Z_Lept1_phIso04);
   fChain->SetBranchAddress("Z_Lept1_pcIso03", &Z_Lept1_pcIso03, &b_Z_Lept1_pcIso03);
   fChain->SetBranchAddress("Z_Lept1_pcIso04", &Z_Lept1_pcIso04, &b_Z_Lept1_pcIso04);
   fChain->SetBranchAddress("Z_Lept1_relIsoCom03", &Z_Lept1_relIsoCom03, &b_Z_Lept1_relIsoCom03);
   fChain->SetBranchAddress("Z_Lept1_relIsoCom04", &Z_Lept1_relIsoCom04, &b_Z_Lept1_relIsoCom04);
   fChain->SetBranchAddress("Z_Lept1_relIsoBeta03", &Z_Lept1_relIsoBeta03, &b_Z_Lept1_relIsoBeta03);
   fChain->SetBranchAddress("Z_Lept1_relIsoBeta04", &Z_Lept1_relIsoBeta04, &b_Z_Lept1_relIsoBeta04);
   fChain->SetBranchAddress("Z_Lept1_relIsoRho03", &Z_Lept1_relIsoRho03, &b_Z_Lept1_relIsoRho03);
   fChain->SetBranchAddress("Z_Lept1_RelisolPtTrks03", &Z_Lept1_RelisolPtTrks03, &b_Z_Lept1_RelisolPtTrks03);
   fChain->SetBranchAddress("Z_Lept1_RelisoEm03", &Z_Lept1_RelisoEm03, &b_Z_Lept1_RelisoEm03);
   fChain->SetBranchAddress("Z_Lept1_RelisoHad03", &Z_Lept1_RelisoHad03, &b_Z_Lept1_RelisoHad03);
   fChain->SetBranchAddress("Z_Lept2_chIso03", &Z_Lept2_chIso03, &b_Z_Lept2_chIso03);
   fChain->SetBranchAddress("Z_Lept2_chIso04", &Z_Lept2_chIso04, &b_Z_Lept2_chIso04);
   fChain->SetBranchAddress("Z_Lept2_nhIso03", &Z_Lept2_nhIso03, &b_Z_Lept2_nhIso03);
   fChain->SetBranchAddress("Z_Lept2_nhIso04", &Z_Lept2_nhIso04, &b_Z_Lept2_nhIso04);
   fChain->SetBranchAddress("Z_Lept2_phIso03", &Z_Lept2_phIso03, &b_Z_Lept2_phIso03);
   fChain->SetBranchAddress("Z_Lept2_phIso04", &Z_Lept2_phIso04, &b_Z_Lept2_phIso04);
   fChain->SetBranchAddress("Z_Lept2_pcIso03", &Z_Lept2_pcIso03, &b_Z_Lept2_pcIso03);
   fChain->SetBranchAddress("Z_Lept2_pcIso04", &Z_Lept2_pcIso04, &b_Z_Lept2_pcIso04);
   fChain->SetBranchAddress("Z_Lept2_relIsoCom03", &Z_Lept2_relIsoCom03, &b_Z_Lept2_relIsoCom03);
   fChain->SetBranchAddress("Z_Lept2_relIsoCom04", &Z_Lept2_relIsoCom04, &b_Z_Lept2_relIsoCom04);
   fChain->SetBranchAddress("Z_Lept2_relIsoBeta03", &Z_Lept2_relIsoBeta03, &b_Z_Lept2_relIsoBeta03);
   fChain->SetBranchAddress("Z_Lept2_relIsoBeta04", &Z_Lept2_relIsoBeta04, &b_Z_Lept2_relIsoBeta04);
   fChain->SetBranchAddress("Z_Lept2_relIsoRho03", &Z_Lept2_relIsoRho03, &b_Z_Lept2_relIsoRho03);
   fChain->SetBranchAddress("Z_Lept2_RelisolPtTrks03", &Z_Lept2_RelisolPtTrks03, &b_Z_Lept2_RelisolPtTrks03);
   fChain->SetBranchAddress("Z_Lept2_RelisoEm03", &Z_Lept2_RelisoEm03, &b_Z_Lept2_RelisoEm03);
   fChain->SetBranchAddress("Z_Lept2_RelisoHad03", &Z_Lept2_RelisoHad03, &b_Z_Lept2_RelisoHad03);
   fChain->SetBranchAddress("Z_Lept1_isGlobal", &Z_Lept1_isGlobal, &b_Z_Lept1_isGlobal);
   fChain->SetBranchAddress("Z_Lept1_isTrker", &Z_Lept1_isTrker, &b_Z_Lept1_isTrker);
   fChain->SetBranchAddress("Z_Lept1_MedComIsoDelBetCorr3Hits", &Z_Lept1_MedComIsoDelBetCorr3Hits, &b_Z_Lept1_MedComIsoDelBetCorr3Hits);
   fChain->SetBranchAddress("Z_Lept1_decModFind", &Z_Lept1_decModFind, &b_Z_Lept1_decModFind);
   fChain->SetBranchAddress("Z_Lept1_pt", &Z_Lept1_pt, &b_Z_Lept1_pt);
   fChain->SetBranchAddress("Z_Lept1_et", &Z_Lept1_et, &b_Z_Lept1_et);
   fChain->SetBranchAddress("Z_Lept1_charge", &Z_Lept1_charge, &b_Z_Lept1_charge);
   fChain->SetBranchAddress("Z_Lept1_eta", &Z_Lept1_eta, &b_Z_Lept1_eta);
   fChain->SetBranchAddress("Z_Lept1_phi", &Z_Lept1_phi, &b_Z_Lept1_phi);
   fChain->SetBranchAddress("Z_Lept1_px", &Z_Lept1_px, &b_Z_Lept1_px);
   fChain->SetBranchAddress("Z_Lept1_py", &Z_Lept1_py, &b_Z_Lept1_py);
   fChain->SetBranchAddress("Z_Lept1_pz", &Z_Lept1_pz, &b_Z_Lept1_pz);
   fChain->SetBranchAddress("Z_Lept1_en", &Z_Lept1_en, &b_Z_Lept1_en);
   fChain->SetBranchAddress("Z_Lept1_matchStations", &Z_Lept1_matchStations, &b_Z_Lept1_matchStations);
   fChain->SetBranchAddress("Z_Lept1_dB", &Z_Lept1_dB, &b_Z_Lept1_dB);
   fChain->SetBranchAddress("Z_Lept2_isGlobal", &Z_Lept2_isGlobal, &b_Z_Lept2_isGlobal);
   fChain->SetBranchAddress("Z_Lept2_isTrker", &Z_Lept2_isTrker, &b_Z_Lept2_isTrker);
   fChain->SetBranchAddress("Z_Lept2_MedComIsoDelBetCorr3Hits", &Z_Lept2_MedComIsoDelBetCorr3Hits, &b_Z_Lept2_MedComIsoDelBetCorr3Hits);
   fChain->SetBranchAddress("Z_Lept2_decModFind", &Z_Lept2_decModFind, &b_Z_Lept2_decModFind);
   fChain->SetBranchAddress("Z_Lept2_pt", &Z_Lept2_pt, &b_Z_Lept2_pt);
   fChain->SetBranchAddress("Z_Lept2_et", &Z_Lept2_et, &b_Z_Lept2_et);
   fChain->SetBranchAddress("Z_Lept2_charge", &Z_Lept2_charge, &b_Z_Lept2_charge);
   fChain->SetBranchAddress("Z_Lept2_eta", &Z_Lept2_eta, &b_Z_Lept2_eta);
   fChain->SetBranchAddress("Z_Lept2_phi", &Z_Lept2_phi, &b_Z_Lept2_phi);
   fChain->SetBranchAddress("Z_Lept2_px", &Z_Lept2_px, &b_Z_Lept2_px);
   fChain->SetBranchAddress("Z_Lept2_py", &Z_Lept2_py, &b_Z_Lept2_py);
   fChain->SetBranchAddress("Z_Lept2_pz", &Z_Lept2_pz, &b_Z_Lept2_pz);
   fChain->SetBranchAddress("Z_Lept2_en", &Z_Lept2_en, &b_Z_Lept2_en);
   fChain->SetBranchAddress("Z_Lept2_matchStations", &Z_Lept2_matchStations, &b_Z_Lept2_matchStations);
   fChain->SetBranchAddress("Z_Lept2_dB", &Z_Lept2_dB, &b_Z_Lept2_dB);
   fChain->SetBranchAddress("Z_Lept1_dz", &Z_Lept1_dz, &b_Z_Lept1_dz);
   fChain->SetBranchAddress("Z_Lept1_globalNormChi2", &Z_Lept1_globalNormChi2, &b_Z_Lept1_globalNormChi2);
   fChain->SetBranchAddress("Z_Lept1_muonHits", &Z_Lept1_muonHits, &b_Z_Lept1_muonHits);
   fChain->SetBranchAddress("Z_Lept1_trkLayers", &Z_Lept1_trkLayers, &b_Z_Lept1_trkLayers);
   fChain->SetBranchAddress("Z_Lept1_trackerHits", &Z_Lept1_trackerHits, &b_Z_Lept1_trackerHits);
   fChain->SetBranchAddress("Z_Lept1_pixelHits", &Z_Lept1_pixelHits, &b_Z_Lept1_pixelHits);
   fChain->SetBranchAddress("Z_Lept2_dz", &Z_Lept2_dz, &b_Z_Lept2_dz);
   fChain->SetBranchAddress("Z_Lept2_globalNormChi2", &Z_Lept2_globalNormChi2, &b_Z_Lept2_globalNormChi2);
   fChain->SetBranchAddress("Z_Lept2_muonHits", &Z_Lept2_muonHits, &b_Z_Lept2_muonHits);
   fChain->SetBranchAddress("Z_Lept2_trkLayers", &Z_Lept2_trkLayers, &b_Z_Lept2_trkLayers);
   fChain->SetBranchAddress("Z_Lept2_trackerHits", &Z_Lept2_trackerHits, &b_Z_Lept2_trackerHits);
   fChain->SetBranchAddress("Z_Lept2_pixelHits", &Z_Lept2_pixelHits, &b_Z_Lept2_pixelHits);
   fChain->SetBranchAddress("Z_Lept1_etaSC", &Z_Lept1_etaSC, &b_Z_Lept1_etaSC);
   fChain->SetBranchAddress("Z_Lept1_phiSC", &Z_Lept1_phiSC, &b_Z_Lept1_phiSC);
   fChain->SetBranchAddress("Z_Lept1_dEtaIn", &Z_Lept1_dEtaIn, &b_Z_Lept1_dEtaIn);
   fChain->SetBranchAddress("Z_Lept1_dPhiIn", &Z_Lept1_dPhiIn, &b_Z_Lept1_dPhiIn);
   fChain->SetBranchAddress("Z_Lept1_sigmaIEtaIEta", &Z_Lept1_sigmaIEtaIEta, &b_Z_Lept1_sigmaIEtaIEta);
   fChain->SetBranchAddress("Z_Lept1_HoverE", &Z_Lept1_HoverE, &b_Z_Lept1_HoverE);
   fChain->SetBranchAddress("Z_Lept1_fbrem", &Z_Lept1_fbrem, &b_Z_Lept1_fbrem);
   fChain->SetBranchAddress("Z_Lept1_energyEC", &Z_Lept1_energyEC, &b_Z_Lept1_energyEC);
   fChain->SetBranchAddress("Z_Lept1_Pnorm", &Z_Lept1_Pnorm, &b_Z_Lept1_Pnorm);
   fChain->SetBranchAddress("Z_Lept1_InvEminusInvP", &Z_Lept1_InvEminusInvP, &b_Z_Lept1_InvEminusInvP);
   fChain->SetBranchAddress("Z_Lept1_dxy", &Z_Lept1_dxy, &b_Z_Lept1_dxy);
   fChain->SetBranchAddress("Z_Lept1_AEff03", &Z_Lept1_AEff03, &b_Z_Lept1_AEff03);
   fChain->SetBranchAddress("Z_Lept1_hasConversion", &Z_Lept1_hasConversion, &b_Z_Lept1_hasConversion);
   fChain->SetBranchAddress("Z_Lept1_mHits", &Z_Lept1_mHits, &b_Z_Lept1_mHits);
   fChain->SetBranchAddress("Z_Lept1_SCcharge", &Z_Lept1_SCcharge, &b_Z_Lept1_SCcharge);
   fChain->SetBranchAddress("Z_Lept1_TKcharge", &Z_Lept1_TKcharge, &b_Z_Lept1_TKcharge);
   fChain->SetBranchAddress("Z_Lept1_GSFcharge", &Z_Lept1_GSFcharge, &b_Z_Lept1_GSFcharge);
   fChain->SetBranchAddress("Z_Lept1_GsfCtfScPixchargeConsistentcheck", &Z_Lept1_GsfCtfScPixchargeConsistentcheck, &b_Z_Lept1_GsfCtfScPixchargeConsistentcheck);
   fChain->SetBranchAddress("Z_Lept2_etaSC", &Z_Lept2_etaSC, &b_Z_Lept2_etaSC);
   fChain->SetBranchAddress("Z_Lept2_phiSC", &Z_Lept2_phiSC, &b_Z_Lept2_phiSC);
   fChain->SetBranchAddress("Z_Lept2_dEtaIn", &Z_Lept2_dEtaIn, &b_Z_Lept2_dEtaIn);
   fChain->SetBranchAddress("Z_Lept2_dPhiIn", &Z_Lept2_dPhiIn, &b_Z_Lept2_dPhiIn);
   fChain->SetBranchAddress("Z_Lept2_sigmaIEtaIEta", &Z_Lept2_sigmaIEtaIEta, &b_Z_Lept2_sigmaIEtaIEta);
   fChain->SetBranchAddress("Z_Lept2_HoverE", &Z_Lept2_HoverE, &b_Z_Lept2_HoverE);
   fChain->SetBranchAddress("Z_Lept2_fbrem", &Z_Lept2_fbrem, &b_Z_Lept2_fbrem);
   fChain->SetBranchAddress("Z_Lept2_energyEC", &Z_Lept2_energyEC, &b_Z_Lept2_energyEC);
   fChain->SetBranchAddress("Z_Lept2_Pnorm", &Z_Lept2_Pnorm, &b_Z_Lept2_Pnorm);
   fChain->SetBranchAddress("Z_Lept2_InvEminusInvP", &Z_Lept2_InvEminusInvP, &b_Z_Lept2_InvEminusInvP);
   fChain->SetBranchAddress("Z_Lept2_dxy", &Z_Lept2_dxy, &b_Z_Lept2_dxy);
   fChain->SetBranchAddress("Z_Lept2_AEff03", &Z_Lept2_AEff03, &b_Z_Lept2_AEff03);
   fChain->SetBranchAddress("Z_Lept2_hasConversion", &Z_Lept2_hasConversion, &b_Z_Lept2_hasConversion);
   fChain->SetBranchAddress("Z_Lept2_mHits", &Z_Lept2_mHits, &b_Z_Lept2_mHits);
   fChain->SetBranchAddress("Z_Lept2_SCcharge", &Z_Lept2_SCcharge, &b_Z_Lept2_SCcharge);
   fChain->SetBranchAddress("Z_Lept2_TKcharge", &Z_Lept2_TKcharge, &b_Z_Lept2_TKcharge);
   fChain->SetBranchAddress("Z_Lept2_GSFcharge", &Z_Lept2_GSFcharge, &b_Z_Lept2_GSFcharge);
   fChain->SetBranchAddress("Z_Lept2_GsfCtfScPixchargeConsistentcheck", &Z_Lept2_GsfCtfScPixchargeConsistentcheck, &b_Z_Lept2_GsfCtfScPixchargeConsistentcheck);
   fChain->SetBranchAddress("Z_Lept1_genIdxMatch", &Z_Lept1_genIdxMatch, &b_Z_Lept1_genIdxMatch);
   fChain->SetBranchAddress("Z_Lept1_genDeltaR", &Z_Lept1_genDeltaR, &b_Z_Lept1_genDeltaR);
   fChain->SetBranchAddress("Z_Lept1_genDPtRel", &Z_Lept1_genDPtRel, &b_Z_Lept1_genDPtRel);
   fChain->SetBranchAddress("Z_Lept2_genIdxMatch", &Z_Lept2_genIdxMatch, &b_Z_Lept2_genIdxMatch);
   fChain->SetBranchAddress("Z_Lept2_genDeltaR", &Z_Lept2_genDeltaR, &b_Z_Lept2_genDeltaR);
   fChain->SetBranchAddress("Z_Lept2_genDPtRel", &Z_Lept2_genDPtRel, &b_Z_Lept2_genDPtRel);
   fChain->SetBranchAddress("Z_diLeptVtxProb", &Z_diLeptVtxProb, &b_Z_diLeptVtxProb);
   fChain->SetBranchAddress("Z_Mass", &Z_Mass, &b_Z_Mass);
   fChain->SetBranchAddress("Z_phi", &Z_phi, &b_Z_phi);
   fChain->SetBranchAddress("Z_eta", &Z_eta, &b_Z_eta);
   fChain->SetBranchAddress("Z_pt", &Z_pt, &b_Z_pt);
   fChain->SetBranchAddress("Z_px", &Z_px, &b_Z_px);
   fChain->SetBranchAddress("Z_py", &Z_py, &b_Z_py);
   fChain->SetBranchAddress("Z_pz", &Z_pz, &b_Z_pz);
   fChain->SetBranchAddress("Z_Neut_pt", &Z_Neut_pt, &b_Z_Neut_pt);
   fChain->SetBranchAddress("Z_Neut_phi", &Z_Neut_phi, &b_Z_Neut_phi);
   fChain->SetBranchAddress("Z_Neut_px", &Z_Neut_px, &b_Z_Neut_px);
   fChain->SetBranchAddress("Z_Neut_py", &Z_Neut_py, &b_Z_Neut_py);
   fChain->SetBranchAddress("Z_Sign", &Z_Sign, &b_Z_Sign);
   fChain->SetBranchAddress("W_Lept1_ptcID", &W_Lept1_ptcID, &b_W_Lept1_ptcID);
   fChain->SetBranchAddress("W_Lept1_chIso03", &W_Lept1_chIso03, &b_W_Lept1_chIso03);
   fChain->SetBranchAddress("W_Lept1_chIso04", &W_Lept1_chIso04, &b_W_Lept1_chIso04);
   fChain->SetBranchAddress("W_Lept1_nhIso03", &W_Lept1_nhIso03, &b_W_Lept1_nhIso03);
   fChain->SetBranchAddress("W_Lept1_nhIso04", &W_Lept1_nhIso04, &b_W_Lept1_nhIso04);
   fChain->SetBranchAddress("W_Lept1_phIso03", &W_Lept1_phIso03, &b_W_Lept1_phIso03);
   fChain->SetBranchAddress("W_Lept1_phIso04", &W_Lept1_phIso04, &b_W_Lept1_phIso04);
   fChain->SetBranchAddress("W_Lept1_pcIso03", &W_Lept1_pcIso03, &b_W_Lept1_pcIso03);
   fChain->SetBranchAddress("W_Lept1_pcIso04", &W_Lept1_pcIso04, &b_W_Lept1_pcIso04);
   fChain->SetBranchAddress("W_Lept1_relIsoCom03", &W_Lept1_relIsoCom03, &b_W_Lept1_relIsoCom03);
   fChain->SetBranchAddress("W_Lept1_relIsoCom04", &W_Lept1_relIsoCom04, &b_W_Lept1_relIsoCom04);
   fChain->SetBranchAddress("W_Lept1_relIsoBeta03", &W_Lept1_relIsoBeta03, &b_W_Lept1_relIsoBeta03);
   fChain->SetBranchAddress("W_Lept1_relIsoBeta04", &W_Lept1_relIsoBeta04, &b_W_Lept1_relIsoBeta04);
   fChain->SetBranchAddress("W_Lept1_relIsoRho03", &W_Lept1_relIsoRho03, &b_W_Lept1_relIsoRho03);
   fChain->SetBranchAddress("W_Lept1_RelisolPtTrks03", &W_Lept1_RelisolPtTrks03, &b_W_Lept1_RelisolPtTrks03);
   fChain->SetBranchAddress("W_Lept1_RelisoEm03", &W_Lept1_RelisoEm03, &b_W_Lept1_RelisoEm03);
   fChain->SetBranchAddress("W_Lept1_RelisoHad03", &W_Lept1_RelisoHad03, &b_W_Lept1_RelisoHad03);
   fChain->SetBranchAddress("W_Lept1_isGlobal", &W_Lept1_isGlobal, &b_W_Lept1_isGlobal);
   fChain->SetBranchAddress("W_Lept1_isTrker", &W_Lept1_isTrker, &b_W_Lept1_isTrker);
   fChain->SetBranchAddress("W_Lept1_MedComIsoDelBetCorr3Hits", &W_Lept1_MedComIsoDelBetCorr3Hits, &b_W_Lept1_MedComIsoDelBetCorr3Hits);
   fChain->SetBranchAddress("W_Lept1_decModFind", &W_Lept1_decModFind, &b_W_Lept1_decModFind);
   fChain->SetBranchAddress("W_Lept1_pt", &W_Lept1_pt, &b_W_Lept1_pt);
   fChain->SetBranchAddress("W_Lept1_et", &W_Lept1_et, &b_W_Lept1_et);
   fChain->SetBranchAddress("W_Lept1_charge", &W_Lept1_charge, &b_W_Lept1_charge);
   fChain->SetBranchAddress("W_Lept1_eta", &W_Lept1_eta, &b_W_Lept1_eta);
   fChain->SetBranchAddress("W_Lept1_phi", &W_Lept1_phi, &b_W_Lept1_phi);
   fChain->SetBranchAddress("W_Lept1_px", &W_Lept1_px, &b_W_Lept1_px);
   fChain->SetBranchAddress("W_Lept1_py", &W_Lept1_py, &b_W_Lept1_py);
   fChain->SetBranchAddress("W_Lept1_pz", &W_Lept1_pz, &b_W_Lept1_pz);
   fChain->SetBranchAddress("W_Lept1_en", &W_Lept1_en, &b_W_Lept1_en);
   fChain->SetBranchAddress("W_Lept1_matchStations", &W_Lept1_matchStations, &b_W_Lept1_matchStations);
   fChain->SetBranchAddress("W_Lept1_dB", &W_Lept1_dB, &b_W_Lept1_dB);
   fChain->SetBranchAddress("W_Lept1_dz", &W_Lept1_dz, &b_W_Lept1_dz);
   fChain->SetBranchAddress("W_Lept1_globalNormChi2", &W_Lept1_globalNormChi2, &b_W_Lept1_globalNormChi2);
   fChain->SetBranchAddress("W_Lept1_muonHits", &W_Lept1_muonHits, &b_W_Lept1_muonHits);
   fChain->SetBranchAddress("W_Lept1_trkLayers", &W_Lept1_trkLayers, &b_W_Lept1_trkLayers);
   fChain->SetBranchAddress("W_Lept1_trackerHits", &W_Lept1_trackerHits, &b_W_Lept1_trackerHits);
   fChain->SetBranchAddress("W_Lept1_pixelHits", &W_Lept1_pixelHits, &b_W_Lept1_pixelHits);
   fChain->SetBranchAddress("W_Lept1_etaSC", &W_Lept1_etaSC, &b_W_Lept1_etaSC);
   fChain->SetBranchAddress("W_Lept1_phiSC", &W_Lept1_phiSC, &b_W_Lept1_phiSC);
   fChain->SetBranchAddress("W_Lept1_dEtaIn", &W_Lept1_dEtaIn, &b_W_Lept1_dEtaIn);
   fChain->SetBranchAddress("W_Lept1_dPhiIn", &W_Lept1_dPhiIn, &b_W_Lept1_dPhiIn);
   fChain->SetBranchAddress("W_Lept1_sigmaIEtaIEta", &W_Lept1_sigmaIEtaIEta, &b_W_Lept1_sigmaIEtaIEta);
   fChain->SetBranchAddress("W_Lept1_HoverE", &W_Lept1_HoverE, &b_W_Lept1_HoverE);
   fChain->SetBranchAddress("W_Lept1_fbrem", &W_Lept1_fbrem, &b_W_Lept1_fbrem);
   fChain->SetBranchAddress("W_Lept1_energyEC", &W_Lept1_energyEC, &b_W_Lept1_energyEC);
   fChain->SetBranchAddress("W_Lept1_Pnorm", &W_Lept1_Pnorm, &b_W_Lept1_Pnorm);
   fChain->SetBranchAddress("W_Lept1_InvEminusInvP", &W_Lept1_InvEminusInvP, &b_W_Lept1_InvEminusInvP);
   fChain->SetBranchAddress("W_Lept1_dxy", &W_Lept1_dxy, &b_W_Lept1_dxy);
   fChain->SetBranchAddress("W_Lept1_AEff03", &W_Lept1_AEff03, &b_W_Lept1_AEff03);
   fChain->SetBranchAddress("W_Lept1_hasConversion", &W_Lept1_hasConversion, &b_W_Lept1_hasConversion);
   fChain->SetBranchAddress("W_Lept1_mHits", &W_Lept1_mHits, &b_W_Lept1_mHits);
   fChain->SetBranchAddress("W_Lept1_SCcharge", &W_Lept1_SCcharge, &b_W_Lept1_SCcharge);
   fChain->SetBranchAddress("W_Lept1_TKcharge", &W_Lept1_TKcharge, &b_W_Lept1_TKcharge);
   fChain->SetBranchAddress("W_Lept1_GSFcharge", &W_Lept1_GSFcharge, &b_W_Lept1_GSFcharge);
   fChain->SetBranchAddress("W_Lept1_GsfCtfScPixchargeConsistentcheck", &W_Lept1_GsfCtfScPixchargeConsistentcheck, &b_W_Lept1_GsfCtfScPixchargeConsistentcheck);
   fChain->SetBranchAddress("W_Lept1_genIdxMatch", &W_Lept1_genIdxMatch, &b_W_Lept1_genIdxMatch);
   fChain->SetBranchAddress("W_Lept1_genDeltaR", &W_Lept1_genDeltaR, &b_W_Lept1_genDeltaR);
   fChain->SetBranchAddress("W_Lept1_genDPtRel", &W_Lept1_genDPtRel, &b_W_Lept1_genDPtRel);
   fChain->SetBranchAddress("W_invm", &W_invm, &b_W_invm);
   fChain->SetBranchAddress("W_Neut_pt", &W_Neut_pt, &b_W_Neut_pt);
   fChain->SetBranchAddress("W_Neut_phi", &W_Neut_phi, &b_W_Neut_phi);
   fChain->SetBranchAddress("W_Neut_px", &W_Neut_px, &b_W_Neut_px);
   fChain->SetBranchAddress("W_Neut_py", &W_Neut_py, &b_W_Neut_py);
   fChain->SetBranchAddress("W_pt", &W_pt, &b_W_pt);
   fChain->SetBranchAddress("W_eta", &W_eta, &b_W_eta);
   fChain->SetBranchAddress("W_phi", &W_phi, &b_W_phi);
   fChain->SetBranchAddress("W_px", &W_px, &b_W_px);
   fChain->SetBranchAddress("W_py", &W_py, &b_W_py);
   fChain->SetBranchAddress("W_pz", &W_pz, &b_W_pz);
   fChain->SetBranchAddress("W_Mt", &W_Mt, &b_W_Mt);
   fChain->SetBranchAddress("W_Acop", &W_Acop, &b_W_Acop);
   fChain->SetBranchAddress("W_Charge", &W_Charge, &b_W_Charge);
   fChain->SetBranchAddress("GenW_Born_nLepts", &GenW_Born_nLepts, &b_GenW_Born_nLepts);
   fChain->SetBranchAddress("GenW_Born_Id", &GenW_Born_Id, &b_GenW_Born_Id);
   fChain->SetBranchAddress("GenW_Born_Status", &GenW_Born_Status, &b_GenW_Born_Status);
   fChain->SetBranchAddress("GenW_Born_mass", &GenW_Born_mass, &b_GenW_Born_mass);
   fChain->SetBranchAddress("GenW_Born_px", &GenW_Born_px, &b_GenW_Born_px);
   fChain->SetBranchAddress("GenW_Born_py", &GenW_Born_py, &b_GenW_Born_py);
   fChain->SetBranchAddress("GenW_Born_pz", &GenW_Born_pz, &b_GenW_Born_pz);
   fChain->SetBranchAddress("GenW_Born_pt", &GenW_Born_pt, &b_GenW_Born_pt);
   fChain->SetBranchAddress("GenW_Born_eta", &GenW_Born_eta, &b_GenW_Born_eta);
   fChain->SetBranchAddress("GenW_Born_phi", &GenW_Born_phi, &b_GenW_Born_phi);
   fChain->SetBranchAddress("GenW_BornLept1_id", &GenW_BornLept1_id, &b_GenW_BornLept1_id);
   fChain->SetBranchAddress("GenW_BornLept1_status", &GenW_BornLept1_status, &b_GenW_BornLept1_status);
   fChain->SetBranchAddress("GenW_BornLept1_px", &GenW_BornLept1_px, &b_GenW_BornLept1_px);
   fChain->SetBranchAddress("GenW_BornLept1_py", &GenW_BornLept1_py, &b_GenW_BornLept1_py);
   fChain->SetBranchAddress("GenW_BornLept1_pz", &GenW_BornLept1_pz, &b_GenW_BornLept1_pz);
   fChain->SetBranchAddress("GenW_BornLept1_en", &GenW_BornLept1_en, &b_GenW_BornLept1_en);
   fChain->SetBranchAddress("GenW_BornLept1_pt", &GenW_BornLept1_pt, &b_GenW_BornLept1_pt);
   fChain->SetBranchAddress("GenW_BornLept1_et", &GenW_BornLept1_et, &b_GenW_BornLept1_et);
   fChain->SetBranchAddress("GenW_BornLept1_charge", &GenW_BornLept1_charge, &b_GenW_BornLept1_charge);
   fChain->SetBranchAddress("GenW_BornLept1_eta", &GenW_BornLept1_eta, &b_GenW_BornLept1_eta);
   fChain->SetBranchAddress("GenW_BornLept1_phi", &GenW_BornLept1_phi, &b_GenW_BornLept1_phi);
   fChain->SetBranchAddress("GenW_BornLept2_id", &GenW_BornLept2_id, &b_GenW_BornLept2_id);
   fChain->SetBranchAddress("GenW_BornLept2_status", &GenW_BornLept2_status, &b_GenW_BornLept2_status);
   fChain->SetBranchAddress("GenW_BornLept2_px", &GenW_BornLept2_px, &b_GenW_BornLept2_px);
   fChain->SetBranchAddress("GenW_BornLept2_py", &GenW_BornLept2_py, &b_GenW_BornLept2_py);
   fChain->SetBranchAddress("GenW_BornLept2_pz", &GenW_BornLept2_pz, &b_GenW_BornLept2_pz);
   fChain->SetBranchAddress("GenW_BornLept2_en", &GenW_BornLept2_en, &b_GenW_BornLept2_en);
   fChain->SetBranchAddress("GenW_BornLept2_pt", &GenW_BornLept2_pt, &b_GenW_BornLept2_pt);
   fChain->SetBranchAddress("GenW_BornLept2_et", &GenW_BornLept2_et, &b_GenW_BornLept2_et);
   fChain->SetBranchAddress("GenW_BornLept2_charge", &GenW_BornLept2_charge, &b_GenW_BornLept2_charge);
   fChain->SetBranchAddress("GenW_BornLept2_eta", &GenW_BornLept2_eta, &b_GenW_BornLept2_eta);
   fChain->SetBranchAddress("GenW_BornLept2_phi", &GenW_BornLept2_phi, &b_GenW_BornLept2_phi);
   fChain->SetBranchAddress("GenW_PostLept1_id", &GenW_PostLept1_id, &b_GenW_PostLept1_id);
   fChain->SetBranchAddress("GenW_PostLept1_status", &GenW_PostLept1_status, &b_GenW_PostLept1_status);
   fChain->SetBranchAddress("GenW_PostLept1_px", &GenW_PostLept1_px, &b_GenW_PostLept1_px);
   fChain->SetBranchAddress("GenW_PostLept1_py", &GenW_PostLept1_py, &b_GenW_PostLept1_py);
   fChain->SetBranchAddress("GenW_PostLept1_pz", &GenW_PostLept1_pz, &b_GenW_PostLept1_pz);
   fChain->SetBranchAddress("GenW_PostLept1_en", &GenW_PostLept1_en, &b_GenW_PostLept1_en);
   fChain->SetBranchAddress("GenW_PostLept1_pt", &GenW_PostLept1_pt, &b_GenW_PostLept1_pt);
   fChain->SetBranchAddress("GenW_PostLept1_et", &GenW_PostLept1_et, &b_GenW_PostLept1_et);
   fChain->SetBranchAddress("GenW_PostLept1_charge", &GenW_PostLept1_charge, &b_GenW_PostLept1_charge);
   fChain->SetBranchAddress("GenW_PostLept1_eta", &GenW_PostLept1_eta, &b_GenW_PostLept1_eta);
   fChain->SetBranchAddress("GenW_PostLept1_phi", &GenW_PostLept1_phi, &b_GenW_PostLept1_phi);
   fChain->SetBranchAddress("GenW_PostLept2_id", &GenW_PostLept2_id, &b_GenW_PostLept2_id);
   fChain->SetBranchAddress("GenW_PostLept2_status", &GenW_PostLept2_status, &b_GenW_PostLept2_status);
   fChain->SetBranchAddress("GenW_PostLept2_px", &GenW_PostLept2_px, &b_GenW_PostLept2_px);
   fChain->SetBranchAddress("GenW_PostLept2_py", &GenW_PostLept2_py, &b_GenW_PostLept2_py);
   fChain->SetBranchAddress("GenW_PostLept2_pz", &GenW_PostLept2_pz, &b_GenW_PostLept2_pz);
   fChain->SetBranchAddress("GenW_PostLept2_en", &GenW_PostLept2_en, &b_GenW_PostLept2_en);
   fChain->SetBranchAddress("GenW_PostLept2_pt", &GenW_PostLept2_pt, &b_GenW_PostLept2_pt);
   fChain->SetBranchAddress("GenW_PostLept2_et", &GenW_PostLept2_et, &b_GenW_PostLept2_et);
   fChain->SetBranchAddress("GenW_PostLept2_charge", &GenW_PostLept2_charge, &b_GenW_PostLept2_charge);
   fChain->SetBranchAddress("GenW_PostLept2_eta", &GenW_PostLept2_eta, &b_GenW_PostLept2_eta);
   fChain->SetBranchAddress("GenW_PostLept2_phi", &GenW_PostLept2_phi, &b_GenW_PostLept2_phi);
   fChain->SetBranchAddress("GenW_Neut_pt", &GenW_Neut_pt, &b_GenW_Neut_pt);
   fChain->SetBranchAddress("GenZ_Channel", &GenZ_Channel, &b_GenZ_Channel);
   fChain->SetBranchAddress("GenZ_nLepts", &GenZ_nLepts, &b_GenZ_nLepts);
   fChain->SetBranchAddress("GenZ_id", &GenZ_id, &b_GenZ_id);
   fChain->SetBranchAddress("GenZ_status", &GenZ_status, &b_GenZ_status);
   fChain->SetBranchAddress("GenZ_mass", &GenZ_mass, &b_GenZ_mass);
   fChain->SetBranchAddress("GenZ_px", &GenZ_px, &b_GenZ_px);
   fChain->SetBranchAddress("GenZ_py", &GenZ_py, &b_GenZ_py);
   fChain->SetBranchAddress("GenZ_pz", &GenZ_pz, &b_GenZ_pz);
   fChain->SetBranchAddress("GenZ_pt", &GenZ_pt, &b_GenZ_pt);
   fChain->SetBranchAddress("GenZ_Neut_pt", &GenZ_Neut_pt, &b_GenZ_Neut_pt);
   fChain->SetBranchAddress("GenZ_eta", &GenZ_eta, &b_GenZ_eta);
   fChain->SetBranchAddress("GenZ_phi", &GenZ_phi, &b_GenZ_phi);
   fChain->SetBranchAddress("GenZ_Lept1_id", &GenZ_Lept1_id, &b_GenZ_Lept1_id);
   fChain->SetBranchAddress("GenZ_Lept1_status", &GenZ_Lept1_status, &b_GenZ_Lept1_status);
   fChain->SetBranchAddress("GenZ_Lept1_px", &GenZ_Lept1_px, &b_GenZ_Lept1_px);
   fChain->SetBranchAddress("GenZ_Lept1_py", &GenZ_Lept1_py, &b_GenZ_Lept1_py);
   fChain->SetBranchAddress("GenZ_Lept1_pz", &GenZ_Lept1_pz, &b_GenZ_Lept1_pz);
   fChain->SetBranchAddress("GenZ_Lept1_en", &GenZ_Lept1_en, &b_GenZ_Lept1_en);
   fChain->SetBranchAddress("GenZ_Lept1_pt", &GenZ_Lept1_pt, &b_GenZ_Lept1_pt);
   fChain->SetBranchAddress("GenZ_Lept1_et", &GenZ_Lept1_et, &b_GenZ_Lept1_et);
   fChain->SetBranchAddress("GenZ_Lept1_charge", &GenZ_Lept1_charge, &b_GenZ_Lept1_charge);
   fChain->SetBranchAddress("GenZ_Lept1_eta", &GenZ_Lept1_eta, &b_GenZ_Lept1_eta);
   fChain->SetBranchAddress("GenZ_Lept1_phi", &GenZ_Lept1_phi, &b_GenZ_Lept1_phi);
   fChain->SetBranchAddress("GenZ_Lept2_id", &GenZ_Lept2_id, &b_GenZ_Lept2_id);
   fChain->SetBranchAddress("GenZ_Lept2_status", &GenZ_Lept2_status, &b_GenZ_Lept2_status);
   fChain->SetBranchAddress("GenZ_Lept2_px", &GenZ_Lept2_px, &b_GenZ_Lept2_px);
   fChain->SetBranchAddress("GenZ_Lept2_py", &GenZ_Lept2_py, &b_GenZ_Lept2_py);
   fChain->SetBranchAddress("GenZ_Lept2_pz", &GenZ_Lept2_pz, &b_GenZ_Lept2_pz);
   fChain->SetBranchAddress("GenZ_Lept2_en", &GenZ_Lept2_en, &b_GenZ_Lept2_en);
   fChain->SetBranchAddress("GenZ_Lept2_pt", &GenZ_Lept2_pt, &b_GenZ_Lept2_pt);
   fChain->SetBranchAddress("GenZ_Lept2_et", &GenZ_Lept2_et, &b_GenZ_Lept2_et);
   fChain->SetBranchAddress("GenZ_Lept2_charge", &GenZ_Lept2_charge, &b_GenZ_Lept2_charge);
   fChain->SetBranchAddress("GenZ_Lept2_eta", &GenZ_Lept2_eta, &b_GenZ_Lept2_eta);
   fChain->SetBranchAddress("GenZ_Lept2_phi", &GenZ_Lept2_phi, &b_GenZ_Lept2_phi);
   fChain->SetBranchAddress("pfMEt_x", &pfMEt_x, &b_pfMEt_x);
   fChain->SetBranchAddress("pfMEt_y", &pfMEt_y, &b_pfMEt_y);
   fChain->SetBranchAddress("pfMEtSumEt", &pfMEtSumEt, &b_pfMEtSumEt);
   fChain->SetBranchAddress("pfMEtNeuEM", &pfMEtNeuEM, &b_pfMEtNeuEM);
   fChain->SetBranchAddress("pfMEtNeuHad", &pfMEtNeuHad, &b_pfMEtNeuHad);
   fChain->SetBranchAddress("pfMEtChHad", &pfMEtChHad, &b_pfMEtChHad);
   fChain->SetBranchAddress("pfMEtChEM", &pfMEtChEM, &b_pfMEtChEM);
   fChain->SetBranchAddress("pfMEtMu", &pfMEtMu, &b_pfMEtMu);
   fChain->SetBranchAddress("NoPuMEt_x", &NoPuMEt_x, &b_NoPuMEt_x);
   fChain->SetBranchAddress("NoPuMEt_y", &NoPuMEt_y, &b_NoPuMEt_y);
   fChain->SetBranchAddress("NoPuMEtSumEt", &NoPuMEtSumEt, &b_NoPuMEtSumEt);
   fChain->SetBranchAddress("NoPuMEtNeuEM", &NoPuMEtNeuEM, &b_NoPuMEtNeuEM);
   fChain->SetBranchAddress("NoPuMEtNeuHad", &NoPuMEtNeuHad, &b_NoPuMEtNeuHad);
   fChain->SetBranchAddress("NoPuMEtChHad", &NoPuMEtChHad, &b_NoPuMEtChHad);
   fChain->SetBranchAddress("NoPuMEtChEM", &NoPuMEtChEM, &b_NoPuMEtChEM);
   fChain->SetBranchAddress("NoPuMEtMu", &NoPuMEtMu, &b_NoPuMEtMu);
   fChain->SetBranchAddress("MVaMEt_x", &MVaMEt_x, &b_MVaMEt_x);
   fChain->SetBranchAddress("MVaMEt_y", &MVaMEt_y, &b_MVaMEt_y);
   fChain->SetBranchAddress("MVaMEtSumEt", &MVaMEtSumEt, &b_MVaMEtSumEt);
   fChain->SetBranchAddress("MVaMEtNeuEM", &MVaMEtNeuEM, &b_MVaMEtNeuEM);
   fChain->SetBranchAddress("MVaMEtNeuHad", &MVaMEtNeuHad, &b_MVaMEtNeuHad);
   fChain->SetBranchAddress("MVaMEtChHad", &MVaMEtChHad, &b_MVaMEtChHad);
   fChain->SetBranchAddress("MVaMEtChEM", &MVaMEtChEM, &b_MVaMEtChEM);
   fChain->SetBranchAddress("MVaMEtMu", &MVaMEtMu, &b_MVaMEtMu);
   fChain->SetBranchAddress("genMEtTrue_x", &genMEtTrue_x, &b_genMEtTrue_x);
   fChain->SetBranchAddress("genMEtTrue_y", &genMEtTrue_y, &b_genMEtTrue_y);
   fChain->SetBranchAddress("genMEtTrueSumEt", &genMEtTrueSumEt, &b_genMEtTrueSumEt);
   fChain->SetBranchAddress("genMEtTrueNeuEM", &genMEtTrueNeuEM, &b_genMEtTrueNeuEM);
   fChain->SetBranchAddress("genMEtTrueNeuHad", &genMEtTrueNeuHad, &b_genMEtTrueNeuHad);
   fChain->SetBranchAddress("genMEtTrueChHad", &genMEtTrueChHad, &b_genMEtTrueChHad);
   fChain->SetBranchAddress("genMEtTrueChEM", &genMEtTrueChEM, &b_genMEtTrueChEM);
   fChain->SetBranchAddress("genMEtTrueMu", &genMEtTrueMu, &b_genMEtTrueMu);
   fChain->SetBranchAddress("genMEtCalo_x", &genMEtCalo_x, &b_genMEtCalo_x);
   fChain->SetBranchAddress("genMEtCalo_y", &genMEtCalo_y, &b_genMEtCalo_y);
   fChain->SetBranchAddress("genMEtCaloSumEt", &genMEtCaloSumEt, &b_genMEtCaloSumEt);
   fChain->SetBranchAddress("genMEtCaloNeuEM", &genMEtCaloNeuEM, &b_genMEtCaloNeuEM);
   fChain->SetBranchAddress("genMEtCaloNeuHad", &genMEtCaloNeuHad, &b_genMEtCaloNeuHad);
   fChain->SetBranchAddress("genMEtCaloChHad", &genMEtCaloChHad, &b_genMEtCaloChHad);
   fChain->SetBranchAddress("genMEtCaloChEM", &genMEtCaloChEM, &b_genMEtCaloChEM);
   fChain->SetBranchAddress("genMEtCaloMu", &genMEtCaloMu, &b_genMEtCaloMu);
   fChain->SetBranchAddress("genMEtCaloAndNonPrompt_x", &genMEtCaloAndNonPrompt_x, &b_genMEtCaloAndNonPrompt_x);
   fChain->SetBranchAddress("genMEtCaloAndNonPrompt_y", &genMEtCaloAndNonPrompt_y, &b_genMEtCaloAndNonPrompt_y);
   fChain->SetBranchAddress("genMEtCaloAndNonPromptSumEt", &genMEtCaloAndNonPromptSumEt, &b_genMEtCaloAndNonPromptSumEt);
   fChain->SetBranchAddress("genMEtCaloAndNonPromptNeuEM", &genMEtCaloAndNonPromptNeuEM, &b_genMEtCaloAndNonPromptNeuEM);
   fChain->SetBranchAddress("genMEtCaloAndNonPromptNeuHad", &genMEtCaloAndNonPromptNeuHad, &b_genMEtCaloAndNonPromptNeuHad);
   fChain->SetBranchAddress("genMEtCaloAndNonPromptChHad", &genMEtCaloAndNonPromptChHad, &b_genMEtCaloAndNonPromptChHad);
   fChain->SetBranchAddress("genMEtCaloAndNonPromptChEM", &genMEtCaloAndNonPromptChEM, &b_genMEtCaloAndNonPromptChEM);
   fChain->SetBranchAddress("genMEtCaloAndNonPromptMu", &genMEtCaloAndNonPromptMu, &b_genMEtCaloAndNonPromptMu);
   Notify();
}

Bool_t WZ3LNT::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void WZ3LNT::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t WZ3LNT::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef WZ3LNT_cxx
