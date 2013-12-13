//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed May 16 17:32:24 2012 by ROOT version 5.32/00
// from TChain WEleQ/tree/
//////////////////////////////////////////////////////////
//$Log: WEleQ.h,v $
//Revision 1.9  2013/08/19 15:11:26  jungmin
//*** empty log message ***
//
//Revision 1.7  2013/07/24 08:13:06  jungmin
//*** empty log message ***
//
//Revision 1.6  2013/07/15 07:35:06  khakim
//*** empty log message ***
//
//Revision 1.5  2013/07/13 16:44:37  khakim
//*** empty log message ***
//
//Revision 1.4  2013/07/13 14:28:40  khakim
//*** empty log message ***
//
//Revision 1.3  2013/07/10 07:03:19  hyusupov
//*** empty log message ***
//
//Revision 1.2  2013/07/08 11:57:32  sangilpark
//*** empty log message ***
//
//Revision 1.51  2013/07/04 08:19:52  jungmin
//*** empty log message ***
//
//Revision 1.50  2013/07/03 16:03:54  jungmin
//*** empty log message ***
//
//Revision 1.49  2013/07/03 15:20:00  salee
//*** empty log message ***
//
//Revision 1.48  2013/07/01 14:24:59  jungmin
//*** empty log message ***
//
//Revision 1.46  2013/06/21 08:52:39  jungmin
//*** empty log message ***
//
//Revision 1.45  2013/06/13 11:48:35  khakim
//*** empty log message ***
//
//Revision 1.44  2013/06/10 13:29:42  jungmin
//*** empty log message ***
//
//Revision 1.43  2013/06/10 12:25:46  jungmin
//*** empty log message ***
//
//Revision 1.42  2013/05/30 00:02:12  khakim
//*** empty log message ***
//
//Revision 1.41  2013/05/28 16:55:13  salee
//*** empty log message ***
//
//Revision 1.40  2013/05/28 15:12:04  salee
//*** empty log message ***
//
//Revision 1.39  2013/05/28 15:05:33  salee
//*** empty log message ***
//
//Revision 1.38  2013/05/27 16:53:53  salee
//*** empty log message ***
//
//Revision 1.37  2013/05/24 09:04:03  hyusupov
//*** empty log message ***
//
//Revision 1.36  2013/05/23 14:17:45  hyusupov
//*** empty log message ***
//
//Revision 1.35  2013/05/23 13:37:07  hyusupov
//*** empty log message ***
//
//Revision 1.34  2013/05/23 11:16:46  salee
//*** empty log message ***
//
//Revision 1.33  2013/05/23 02:50:04  salee
//*** empty log message ***
//
//Revision 1.32  2013/05/22 12:53:17  hyusupov
//*** empty log message ***
//
//Revision 1.31  2013/05/20 00:28:29  salee
//*** empty log message ***
//
//Revision 1.30  2013/05/18 15:02:45  salee
//*** empty log message ***
//
//Revision 1.29  2013/05/16 13:12:25  shchang
//*** empty log message ***
//
//Revision 1.28  2013/05/16 12:19:19  salee
//AcceptLumiWeight
//
//Revision 1.27  2013/05/15 09:30:56  shchang
//for WQA, Filling parts for MET histogram, siganl and side, are change with for loop.
//
//Revision 1.26  2013/05/15 00:06:31  salee
//AcceptanceEven
//
//Revision 1.25  2013/05/14 16:28:10  salee
//AcceptancePost
//
//Revision 1.24  2013/05/14 10:10:06  salee
//muonPt20
//
//Revision 1.23  2013/05/13 12:59:49  hyusupov
//*** empty log message ***
//
//Revision 1.22  2013/05/10 12:05:08  salee
//acceptance
//
//Revision 1.21  2013/05/07 23:50:36  salee
//Born Level
//
//Revision 1.20  2013/04/29 16:32:25  jungmin
//*** empty log message ***
//
//Revision 1.19  2013/04/26 12:29:19  jungmin
//*** empty log message ***
//
//Revision 1.18  2013/04/16 09:00:17  shchang
//lepton_eta to lepton_etaSC for ECal pidusal cut
//
//Revision 1.17  2013/04/15 16:25:54  jungmin
//*** empty log message ***
//
//Revision 1.16  2013/04/15 10:00:57  hyusupov
//*** empty log message ***
//
//Revision 1.15  2013/04/12 14:14:16  salee
//*** empty log message ***
//

#ifndef WEleQ_h
#define WEleQ_h

#include "WMuons.h"
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1D.h>
#include <TMath.h>
#include <TLorentzVector.h>
#include <TRandom.h>

// Header file for the classes stored in the TTree if any.
#include <vector>
#include <vector>

#include <iostream>
#include <fstream>
#include <iomanip>
#include "../Utils/const.h"
#include "../Utils/RecoilCorrector.hh"    // class to handle recoil corrections for MET


#include "Math/PtEtaPhiE4D.h"
#include "Math/PtEtaPhiM4D.h"
#include "Math/LorentzVector.h"

typedef ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiM4D<double> > PtEtaPhiMLorentzVectorD;
typedef PtEtaPhiMLorentzVectorD PtEtaPhiMLorentzVector;


// Fixed size dimensions of array or collections stored in the TTree if any.
class WEleQ {
public :
  //WMuons	wMuons;
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   double	LumiWeight;
   double RecoilBins[u1Bin+1]; //Recoil Study Wpt bins
   double Bins[NWptBinPlus]; //Wpt bins
   //=================================================//
   // change from here when ever you change the tree 1/2
   //=================================================//
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
   vector<double>  *Z_Lept1_chIso03;
   vector<double>  *Z_Lept1_chIso04;
   vector<double>  *Z_Lept1_nhIso03;
   vector<double>  *Z_Lept1_nhIso04;
   vector<double>  *Z_Lept1_phIso03;
   vector<double>  *Z_Lept1_phIso04;
   vector<double>  *Z_Lept1_pcIso03;
   vector<double>  *Z_Lept1_pcIso04;
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
   vector<double>  *Z_Lept2_relIsoRho03;
   vector<double>  *Z_Lept2_RelisolPtTrks03;
   vector<double>  *Z_Lept2_RelisoEm03;
   vector<double>  *Z_Lept2_RelisoHad03;
   vector<bool>    *Z_Lept1_isGlobal;
   vector<bool>    *Z_Lept1_isTrker;
   vector<double>  *Z_Lept1_pt;
   vector<double>  *Z_Lept1_et;
   vector<double>  *Z_Lept1_eta;
  // vector<double>  *Z_Lept1_charge;//MisChargeStudy
  // vector<double>  *Z_Lept1_GsfCtfScPixchargeConsistentcheck;//MisChargeStudy
   vector<double>  *Z_Lept1_phi;
   vector<double>  *Z_Lept1_px;
   vector<double>  *Z_Lept1_py;
   vector<double>  *Z_Lept1_pz;
   vector<double>  *Z_Lept1_en;
   vector<int>     *Z_Lept1_matchStations;
   vector<double>  *Z_Lept1_dB;
   vector<bool>    *Z_Lept2_isGlobal;
   vector<bool>    *Z_Lept2_isTrker;
   vector<double>  *Z_Lept2_pt;
   vector<double>  *Z_Lept2_et;
   vector<double>  *Z_Lept2_eta;
  // vector<double>  *Z_Lept2_charge;//MisChargeStudy
  // vector<double>  *Z_Lept2_GsfCtfScPixchargeConsistentcheck;//MisChargeStudy
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
   vector<double>  *W_Lept1_pt;
   vector<double>  *W_Lept1_et;
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
   vector<double>  *GenW_PostLept2_eta;
   vector<double>  *GenW_PostLept2_phi;
   vector<int>     *GenZ_nLepts;
   vector<int>     *GenZ_id;
   vector<int>     *GenZ_status;
   vector<double>  *GenZ_mass;
   vector<double>  *GenZ_px;
   vector<double>  *GenZ_py;
   vector<double>  *GenZ_pz;
   vector<double>  *GenZ_pt;
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
   vector<double>  *GenZ_Lept2_eta;
   vector<double>  *GenZ_Lept2_phi;

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
   TBranch        *b_HLT_Ele22_CaloIdL_CaloIsoVL;   //!
   TBranch        *b_HLT_Ele27_WP80;   //!
   TBranch        *b_HLT_Mu15_eta2p1;   //!
   TBranch        *b_Z_Lept1_chIso03;   //!
   TBranch        *b_Z_Lept1_chIso04;   //!
   TBranch        *b_Z_Lept1_nhIso03;   //!
   TBranch        *b_Z_Lept1_nhIso04;   //!
   TBranch        *b_Z_Lept1_phIso03;   //!
   TBranch        *b_Z_Lept1_phIso04;   //!
   TBranch        *b_Z_Lept1_pcIso03;   //!
   TBranch        *b_Z_Lept1_pcIso04;   //!
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
   TBranch        *b_Z_Lept2_relIsoRho03;   //!
   TBranch        *b_Z_Lept2_RelisolPtTrks03;   //!
   TBranch        *b_Z_Lept2_RelisoEm03;   //!
   TBranch        *b_Z_Lept2_RelisoHad03;   //!
   TBranch        *b_Z_Lept1_isGlobal;   //!
   TBranch        *b_Z_Lept1_isTrker;   //!
   TBranch        *b_Z_Lept1_pt;   //!
   TBranch        *b_Z_Lept1_et;   //!
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
   TBranch        *b_Z_Lept2_pt;   //!
   TBranch        *b_Z_Lept2_et;   //!
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
   TBranch        *b_W_Lept1_pt;   //!
   TBranch        *b_W_Lept1_et;   //!
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
   TBranch        *b_GenW_PostLept2_eta;   //!
   TBranch        *b_GenW_PostLept2_phi;   //!
   TBranch        *b_GenZ_nLepts;   //!
   TBranch        *b_GenZ_id;   //!
   TBranch        *b_GenZ_status;   //!
   TBranch        *b_GenZ_mass;   //!
   TBranch        *b_GenZ_px;   //!
   TBranch        *b_GenZ_py;   //!
   TBranch        *b_GenZ_pz;   //!
   TBranch        *b_GenZ_pt;   //!
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
   TBranch        *b_GenZ_Lept2_eta;   //!
   TBranch        *b_GenZ_Lept2_phi;   //!

   //================================================
   // change to here when ever you change the tree
   //================================================
   TH1D*	h1_Vtx_Prim;
   TH1D*	h1_Vtx_PrimPuW;
   TH1D*	h1_Vtx_Good;
   TH1D*	h1_Vtx_GoodPuW;

   TH1D*        h1_Vtx_Good1;
   TH1D*        h1_Vtx_Prim1;
   TH1D*        h1_W_Lept1_pt1;
   TH1D*        h1_W_Neut_pt1;
   TH1D*        h1_W_Neut_px_Corr;
   TH1D*        h1_W_Neut_py_Corr;
   TH1D*        h1_W_Neut_pt_Corr;
   TH1D*        h1_npileup1;
   TH1D*        h1_Z_Neut_pt;
   TH1D*        h1_Z_Neut_phi;
   TH1D*        h1_Z_Neut_px;
   TH1D*        h1_Z_Neut_py;
   TH1D*        h1_Z_Neut_pt_Corr;
   TH1D*        h1_Z_Neut_phi_Corr;
   TH1D*        h1_Z_Neut_px_Corr;
   TH1D*        h1_Z_Neut_py_Corr;
   TH2D*        h2_Z_Nvtx_px;
   TH2D*        h2_Z_Nvtx_py;
   TH2D*        h2_Z_Nvtx_px_Corr;
   TH2D*        h2_Z_Nvtx_py_Corr;

   TH1D*	h1_W_Multi;
   
   TH1D*        h1_W_Lept1_pt;
   TH1D*	h1_W_pt;
   TH1D*        h1_Wp_pt;
   TH1D*        h1_Wm_pt;
   TH2D*        h2_WpT_ReconPstFsr;

   TH2D*        h2_WpT_lepPt;
   TH2D*        h2_WpT_lepPt_Plus;
   TH2D*        h2_WpT_lepPt_Minus;

   TH2D*        h2_ZLep1_ZLep2;
   TH2D*        h2_Zmass_ZLep1;
   TH2D*        h2_Zmass_ZLep2;
   TH2D*        h2_Zpt_ZLep1;
   TH2D*        h2_Zpt_ZLep2;
   TH1D*        h1_Zpt;

   //MisChargeStudy
 //  TH1D*        h1_Zmass_QAll;
 //  TH1D*        h1_Zmass_QThree[lept1eta][lept2eta];
 //  TH1D*        h1_Zmass_QThreeSame[lept1eta][lept2eta];
 //  TH1D*        h1_Zmass_QNo[lept1eta][lept2eta];
 //  TH1D*        h1_Zmass_QNoSame[lept1eta][lept2eta];


   // Acceptance
   TH1D*	h1_Born_AP;
   TH1D*	h1_Born_BornFid;
   TH1D*	h1_Born_BornFid_Even;
   TH1D*	h1_Born_BothFid;
   TH1D*	h1_Born_BothFid_Even;

   TH1D*	h1_Post_PostFid;
   TH1D*	h1_Post_PostFid_Even;
   TH1D*	h1_Post_BothFid;
   TH1D*	h1_Post_BothFid_Even;

   TH2D*	h2_PostBorn_BothFid;


   // Unfolding
   TH1D*	h1_Truth_Rec;
   TH1D*	h1_Truth_Rec_Even;
   TH1D*	h1_Truth_Rec_Odd;
   TH1D*	h1_Truth_Post;
   TH1D*	h1_Truth_Post_Even;
   TH1D*	h1_Truth_Post_Odd;
   TH1D*	h1_Truth_Post_EffCorr;
   TH2D*	h2_Truth_Rec_AP_Post;

   TH1D*	h1_W_pt_RecoPreFsrGenRes[NWptBinPlus];
   TH1D*	h1_W_pt_RecoPstFsrGenRes[NWptBinPlus];

   TH1D*        h1_W_Lep1_eta;
   TH1D*        h1_i_ToTal[EtaBin];
   TH1D*        h1_i_All[EtaBin];
   TH1D*        h1_i_other[EtaBin];
   TH1D*        h1_i_Side[EtaBin];
   TH1D*        h1_W_Neu_All[EtaBin];
   TH1D*        h1_W_Neu_other[EtaBin];
   TH1D*        h1_W_Neu_pt_ToTal[EtaBin];
   TH1D*        h1_W_Neu_pt_ToTal_beforeTrigger[EtaBin];
   TH1D*        h1_W_Neu_AddElectron[EtaBin];
   TH1D*        h1_W_Neu_pt_Side[EtaBin];
   TH1D*        h1_W_Neu_Eta_I[EtaBin];
   TH1D*        h1_W_Neu_Eta_P[EtaBin];
   TH1D*        h1_W_Neu_Eta_M[EtaBin];
   TH1D*	h1_W_Neu_pt[NWptBinPlus];
   TH1D*	h1_GenW_Neu_pt[NWptBinPlus];
   TH1D*	h1_WSide_Neu_pt[NWptBinPlus];
   TH1D*	h1_WSide_Neu_eta[EtaBin];
   //cut values check.
   TH1D*        h1_check_iw;
   TH1D*        h1_check_side_iw;
   TH1D*        h1_check_pt;
   TH1D*        h1_check_side_pt;
   TH1D*        h1_check_sigmaIetaIeta;
   TH1D*        h1_check_side_sigmaIetaIeta;
   TH1D*        h1_check_dEtaIn;
   TH1D*        h1_check_side_dEtaIn;
   TH1D*        h1_check_dPhiin;
   TH1D*        h1_check_side_dPhiin;
   TH1D*        h1_check_HoverE;
   TH1D*        h1_check_side_HoverE;
   TH1D*        h1_check_dxy;
   TH1D*        h1_check_side_dxy;
   TH1D*        h1_check_dz;
   TH1D*        h1_check_side_dz;
   TH1D*        h1_check_InvE_InvP;
   TH1D*        h1_check_side_InvE_InvP;
   TH1D*        h1_check_mHits;
   TH1D*        h1_check_side_mHits;
   TH1D*        h1_check_lep_eta;
   TH1D*        h1_check_side_lep_eta;

   TH2D*	h2_Met_LepPt[NWptBinPlus];
   TH2D*	h2_Met_WpT[NWptBinPlus];

   TH1D*	h1_Wp_Neu_pt[NWptBinPlus];
   TH1D*	h1_GenWp_Neu_pt[NWptBinPlus];
   TH1D*	h1_WpSide_Neu_pt[NWptBinPlus];
   TH1D*	h1_WpSide_Neu_eta[EtaBin];

   TH1D*	h1_Wm_Neu_pt[NWptBinPlus];
   TH1D*	h1_GenWm_Neu_pt[NWptBinPlus];
   TH1D*	h1_WmSide_Neu_pt[NWptBinPlus];
   TH1D*	h1_WmSide_Neu_eta[EtaBin];

   //-----
   TH1D*	h1_W_Mt;
   TH1D*	h1_PuWeight;
   TH1D*	h1_W_Acop;
   TH1D*	h1_vtx_z;
   TH1D*	h1_vtx_Rho;

   TH1D*	h1_GlbMuChi2;
   TH1D*	h1_muonHits;
   TH1D*	h1_muMatchStation;
   TH1D*	h1_trkLayers;
   TH1D*	h1_pixelHits;
   TH1D*	h1_dB;
   TH1D*	h1_dz;
   TH1D*	h1_IsoCom03;
   TH1D*	h1_IsoCom04;
   TH1D*	h1_IsoHad03;
   TH1D*	h1_IsoHad04;
   TH1D*	h1_IsoBeta03;
   TH1D*	h1_IsoBeta04;

   //Z===================
   TH1D*	h1_diLeptVtxProb;
   TH1D*	h1_Zmass;
   TH1D*        h1_Zmass_BB;
   TH1D*        h1_Zmass_BE;
   TH1D*        h1_Zmass_EE;
   TH1D*        h1_ZmassCorr;
   TH1D*        h1_ZmassCorr_BB;
   TH1D*        h1_ZmassCorr_BE;
   TH1D*        h1_ZmassCorr_EE;

   TH2D*	h2_u1Zpt;
   TH2D*	h2_u2Zpt;
   TH2D*	h2_u3Zpt;
   TH1D*	h1_u1Z[u1Bin];
   TH1D*	h1_u2Z[u2Bin];
   TH1D*	h1_u3Z[u1Bin];
   TH1D*	h1_u1W[u1Bin];
   TH1D*	h1_u2W[u2Bin];
   TH1D*	h1_u3W[u1Bin];

   //                          scale, smear
   //   TH1D*	h1_ZmassDaughEta[ScaleBins][ScaleBins];
   TH1D*        h1_ZmassDaughEta[ScElCombiBinsHighPU];
   //TH1D*        h1_ZmassDaughEta[ScElCombiBins];
   TH1D*        h1_ZmassDaughEtaMu[ScMuCombiBins];

   WEleQ(TTree *tree=0,TTree *WMuonTree=0, double weight=1, TString OutFileName = "output.root",TString Mode="analysis", TString AnaChannel ="Muon",int etaRange_=-999);//Electron
   virtual ~WEleQ();
   virtual Int_t    MuonCut(int entry);
   virtual Int_t    MuonCutSide(int entry);
   virtual Int_t    AddMuonCut(int entry);
   virtual Int_t    ElectronCut(int entry);
   virtual Int_t    ElectronCutHighPU(int entry);
   virtual Int_t    ElectronCutHighPUToTal(int entry);
   virtual Int_t    ElectronCutSide(int entry);
   virtual Int_t    ElectronCutSideHighPU(int entry);
   virtual Int_t    AddElectronCut(int entry);
   virtual Int_t    AddElectronCutHighPU(int entry);
   virtual Int_t    MuonCutZ(int entry);
   virtual Int_t    ElectronCutZ(int entry);
   virtual Int_t    ElectronCutZHighPU(int entry);
   virtual Int_t    EtaRange(double lep1Eta,double lep2Eta);
   virtual Int_t    EtaRange(double lep1Eta);
  
   virtual Int_t    FillEleZmassDaughEta(int etaRange1,int etaRange2);
   virtual Int_t    FillMuZmassDaughEta(int etaRange1,int etaRange2);

   //virtual Int_t    FillWMetEtaHisto(double wCand.lep_eta);//Added by Chang

  virtual Double_t    ElePlusEffiCorrection(double elePt, double eleEtaSC);
  virtual Double_t    EleMinusEffiCorrection(double elePt, double eleEtaSC);
  virtual Double_t    MuonPlusEffiCorrection(double muonPt, double muonEta);
  virtual Double_t    MuonMinusEffiCorrection(double muonPt, double muonEta);
  
  virtual Double_t    EleScaleRD(double ele_etaSC);
  virtual Double_t    EleSmearMC(double ele_etaSC);
  virtual Double_t    MuonSmearMC(double mu_eta);
   
   virtual Int_t    FillUnfoldInfo();
   virtual Int_t    DumpUnfoldInfo(int i);
   //virtual Int_t    FillUnfoldInfo(bool ApplyRecoil =true);
   virtual Int_t    FillAcceptInfo();
 //  virtual Int_t    FillMisChargeInfo();//MisChargeStudy
   virtual Int_t    DoRecoilCorr();
   virtual Int_t    InitVar4Evt();
   virtual Int_t    DoScaleSmearScan(
    double zlep1Pt,double zlep1Pz,double zlep1En,double zlep1Phi,
    double zlep2Pt,double zlep2Pz,double zlep2En,double zlep2Phi, double TTW_);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   //   virtual void     Loop_Recoil();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
private:
  int evtCnt;
  bool TruthRecoPost;
  double SF;
  //Recoil Variables
  RecoilCorrector *recoilCorr;
  struct RecoilVar{
    TString ZRDfilename;
    TString ZMCfilename;
    TString Wpfilename;
    TString Wmfilename;
  }rcoil;

  double BosonNorm,ux,uy,u1Z,u2Z,u3Z,u1W,u2W,u3W;
  //Gen Variables
  struct GenInfo{
    //bool W_MCtruth;
    double BornW_pt;
    double PostW_pt;
    double PostW_phi;
    double BornW_phi;
    double charge;
    double genWmet;
  }genInfo;
  //W boson Variables
  struct WCand{
    double pt;
    double Mt;
    double Met;
    double Nu_px;
    double Nu_py;
    double Met_side;
    double Nu_px_Corr;
    double Nu_py_Corr;
    double Met_Corr;
    int size;
    double charge;


    int muonHit;
    int matchStation;
    int trkLayers;
    double dB,dz;
    int pixelHits;
    double chIso03, chIso04;
    double nhIso03, nhIso04;
    double phIso03, phIso04;
    double pcIso03, pcIso04;
    double lep_pt, lep_pt_corr;
    double lep_phi;
    double lep_eta, lep_etaSC;

    int genIdx;

  }wCand;
    int iw;
    double temp_elpT;
  double w_pt_side, w_acop;
  bool W_pass;

  //For filling MET histograms for WQA by chang
  double wqaMetMXBins[NWqaBins];
  double wqaMetMNBins[NWqaBins];

  //Z boson Variables
  bool Z_pass;
  double Z_size,Zmass,Zpt, ZptRecoil;//ZptRecoil==Zpt for real but gen dilep for MC
  double ZLep1Pt, ZLep1Pz,ZLep1En, ZLep1Phi, ZLep1etaSC;
  double ZLep2Pt, ZLep2Pz,ZLep2En, ZLep2Phi, ZLep2etaSC;
  double Z_MET_pt, Z_MET_phi, Z_MET_px, Z_MET_py;
  double Z_MET_pt_Corr, Z_MET_phi_Corr, Z_MET_px_Corr, Z_MET_py_Corr;

  //MisChargeStudy
 // double ZLep1eta;
 // double ZLep2eta;
 // double ZLep1Requirement;
 // double ZLep2Requirement;
 // double ZLep1charge;
 // double ZLep2charge;

  int ETARANGE;
  double diLeptVtxProb;
  //Lepton Variables
  double lep_pt,addLepN,lep_pt_corr;
  double scalecorr,scalecorr1,scalecorr2,smearcorr,smearcorr1,smearcorr2,newZlep1Pt, newZlep2Pt;
  double elemass,muonmass, corr1, corr2;
  //Muon Variables
  double glbMuChi2;
  //Electron Variables
  //Muetrino
  double corrMet,corrMetPhi;
  //Miscell.
  TString	OutFileName;
  TString	Mode;
  TString	AnaChannel;
  double vtxz,vtxRho;
  double TTW;

  struct UnfoldInfo{
    double recoPreFsrGenWptRes;
    double recoPstFsrGenWptRes;
  }unfoldInfo;
  bool isPostPassAcc;
  bool isBornPassAcc;
};

#endif

#ifdef WEleQ_cxx

void WEleQ::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

  //===============================================
   // change from here when ever you change the tree 2/2
  //===============================================
   // Set object pointer
   vtx_isFake = 0;
   vtx_ndof = 0;
   vtx_z = 0;
   vtx_Rho = 0;
   Z_Lept1_chIso03 = 0;
   Z_Lept1_chIso04 = 0;
   Z_Lept1_nhIso03 = 0;
   Z_Lept1_nhIso04 = 0;
   Z_Lept1_phIso03 = 0;
   Z_Lept1_phIso04 = 0;
   Z_Lept1_pcIso03 = 0;
   Z_Lept1_pcIso04 = 0;
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
   Z_Lept2_relIsoRho03 = 0;
   Z_Lept2_RelisolPtTrks03 = 0;
   Z_Lept2_RelisoEm03 = 0;
   Z_Lept2_RelisoHad03 = 0;
   Z_Lept1_isGlobal = 0;
   Z_Lept1_isTrker = 0;
   Z_Lept1_pt = 0;
   Z_Lept1_et = 0;
   Z_Lept1_eta = 0;
 //  Z_Lept1_charge =0;//MisChargeStudy
 //  Z_Lept1_GsfCtfScPixchargeConsistentcheck = 0;//MisChargeStudy
   Z_Lept1_phi = 0;
   Z_Lept1_px = 0;
   Z_Lept1_py = 0;
   Z_Lept1_pz = 0;
   Z_Lept1_en = 0;
   Z_Lept1_matchStations = 0;
   Z_Lept1_dB = 0;
   Z_Lept2_isGlobal = 0;
   Z_Lept2_isTrker = 0;
   Z_Lept2_pt = 0;
   Z_Lept2_et = 0;
   Z_Lept2_eta = 0;
  // Z_Lept2_charge =0;//MisChargeStudy
  // Z_Lept2_GsfCtfScPixchargeConsistentcheck = 0;//MisChargeStudy
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
   W_Lept1_pt = 0;
   W_Lept1_et = 0;
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
   GenW_PostLept2_eta = 0;
   GenW_PostLept2_phi = 0;
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
   fChain->SetBranchAddress("HLT_Ele22_CaloIdL_CaloIsoVL", &HLT_Ele22_CaloIdL_CaloIsoVL_version, &b_HLT_Ele22_CaloIdL_CaloIsoVL);
   fChain->SetBranchAddress("HLT_Ele27_WP80", &HLT_Ele27_WP80_version, &b_HLT_Ele27_WP80);
   fChain->SetBranchAddress("HLT_Mu15_eta2p1", &HLT_Mu15_eta2p1_version, &b_HLT_Mu15_eta2p1);
   fChain->SetBranchAddress("Z_Lept1_chIso03", &Z_Lept1_chIso03, &b_Z_Lept1_chIso03);
   fChain->SetBranchAddress("Z_Lept1_chIso04", &Z_Lept1_chIso04, &b_Z_Lept1_chIso04);
   fChain->SetBranchAddress("Z_Lept1_nhIso03", &Z_Lept1_nhIso03, &b_Z_Lept1_nhIso03);
   fChain->SetBranchAddress("Z_Lept1_nhIso04", &Z_Lept1_nhIso04, &b_Z_Lept1_nhIso04);
   fChain->SetBranchAddress("Z_Lept1_phIso03", &Z_Lept1_phIso03, &b_Z_Lept1_phIso03);
   fChain->SetBranchAddress("Z_Lept1_phIso04", &Z_Lept1_phIso04, &b_Z_Lept1_phIso04);
   fChain->SetBranchAddress("Z_Lept1_pcIso03", &Z_Lept1_pcIso03, &b_Z_Lept1_pcIso03);
   fChain->SetBranchAddress("Z_Lept1_pcIso04", &Z_Lept1_pcIso04, &b_Z_Lept1_pcIso04);
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
   fChain->SetBranchAddress("Z_Lept2_relIsoRho03", &Z_Lept2_relIsoRho03, &b_Z_Lept2_relIsoRho03);
   fChain->SetBranchAddress("Z_Lept2_RelisolPtTrks03", &Z_Lept2_RelisolPtTrks03, &b_Z_Lept2_RelisolPtTrks03);
   fChain->SetBranchAddress("Z_Lept2_RelisoEm03", &Z_Lept2_RelisoEm03, &b_Z_Lept2_RelisoEm03);
   fChain->SetBranchAddress("Z_Lept2_RelisoHad03", &Z_Lept2_RelisoHad03, &b_Z_Lept2_RelisoHad03);
   fChain->SetBranchAddress("Z_Lept1_isGlobal", &Z_Lept1_isGlobal, &b_Z_Lept1_isGlobal);
   fChain->SetBranchAddress("Z_Lept1_isTrker", &Z_Lept1_isTrker, &b_Z_Lept1_isTrker);
   fChain->SetBranchAddress("Z_Lept1_pt", &Z_Lept1_pt, &b_Z_Lept1_pt);
   fChain->SetBranchAddress("Z_Lept1_et", &Z_Lept1_et, &b_Z_Lept1_et);
   fChain->SetBranchAddress("Z_Lept1_eta", &Z_Lept1_eta, &b_Z_Lept1_eta);
 //  fChain->SetBranchAddress("Z_Lept1_charge", &Z_Lept1_charge);//MisChargeStudy
 //  fChain->SetBranchAddress("Z_Lept1_GsfCtfScPixchargeConsistentcheck", &Z_Lept1_GsfCtfScPixchargeConsistentcheck);//MisChargeStudy
   fChain->SetBranchAddress("Z_Lept1_phi", &Z_Lept1_phi, &b_Z_Lept1_phi);
   fChain->SetBranchAddress("Z_Lept1_px", &Z_Lept1_px, &b_Z_Lept1_px);
   fChain->SetBranchAddress("Z_Lept1_py", &Z_Lept1_py, &b_Z_Lept1_py);
   fChain->SetBranchAddress("Z_Lept1_pz", &Z_Lept1_pz, &b_Z_Lept1_pz);
   fChain->SetBranchAddress("Z_Lept1_en", &Z_Lept1_en, &b_Z_Lept1_en);
   fChain->SetBranchAddress("Z_Lept1_matchStations", &Z_Lept1_matchStations, &b_Z_Lept1_matchStations);
   fChain->SetBranchAddress("Z_Lept1_dB", &Z_Lept1_dB, &b_Z_Lept1_dB);
   fChain->SetBranchAddress("Z_Lept2_isGlobal", &Z_Lept2_isGlobal, &b_Z_Lept2_isGlobal);
   fChain->SetBranchAddress("Z_Lept2_isTrker", &Z_Lept2_isTrker, &b_Z_Lept2_isTrker);
   fChain->SetBranchAddress("Z_Lept2_pt", &Z_Lept2_pt, &b_Z_Lept2_pt);
   fChain->SetBranchAddress("Z_Lept2_et", &Z_Lept2_et, &b_Z_Lept2_et);
   fChain->SetBranchAddress("Z_Lept2_eta", &Z_Lept2_eta, &b_Z_Lept2_eta);
 //  fChain->SetBranchAddress("Z_Lept2_charge", &Z_Lept2_charge);//MisChargeStudy
 //  fChain->SetBranchAddress("Z_Lept2_GsfCtfScPixchargeConsistentcheck", &Z_Lept2_GsfCtfScPixchargeConsistentcheck);//MisChargeStudy
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
   fChain->SetBranchAddress("W_Lept1_pt", &W_Lept1_pt, &b_W_Lept1_pt);
   fChain->SetBranchAddress("W_Lept1_et", &W_Lept1_et, &b_W_Lept1_et);
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
   fChain->SetBranchAddress("GenW_PostLept2_eta", &GenW_PostLept2_eta, &b_GenW_PostLept2_eta);
   fChain->SetBranchAddress("GenW_PostLept2_phi", &GenW_PostLept2_phi, &b_GenW_PostLept2_phi);
   fChain->SetBranchAddress("GenZ_nLepts", &GenZ_nLepts, &b_GenZ_nLepts);
   fChain->SetBranchAddress("GenZ_id", &GenZ_id, &b_GenZ_id);
   fChain->SetBranchAddress("GenZ_status", &GenZ_status, &b_GenZ_status);
   fChain->SetBranchAddress("GenZ_mass", &GenZ_mass, &b_GenZ_mass);
   fChain->SetBranchAddress("GenZ_px", &GenZ_px, &b_GenZ_px);
   fChain->SetBranchAddress("GenZ_py", &GenZ_py, &b_GenZ_py);
   fChain->SetBranchAddress("GenZ_pz", &GenZ_pz, &b_GenZ_pz);
   fChain->SetBranchAddress("GenZ_pt", &GenZ_pt, &b_GenZ_pt);
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
   fChain->SetBranchAddress("GenZ_Lept2_eta", &GenZ_Lept2_eta, &b_GenZ_Lept2_eta);
   fChain->SetBranchAddress("GenZ_Lept2_phi", &GenZ_Lept2_phi, &b_GenZ_Lept2_phi);

  //===============================================
  //change to here whenever you change the tree
  //===============================================



   char histName[30];
   h1_Vtx_Prim	= new TH1D("h1_Vtx_Prim","N primary vertex",25,0,25);
   h1_Vtx_PrimPuW=new TH1D("h1_Vtx_PrimPuW","N primary vertex PU W",25,0,25);
   h1_Vtx_Good	= new TH1D("h1_Vtx_Good","N primary vertex",25,0,25);
   h1_Vtx_GoodPuW=new TH1D("h1_Vtx_GoodPuW","N primary vertex PU W",25,0,25);
   h1_W_Multi= new TH1D("h1_W_Multi","W Multiplicity",10,-0.5,9.5);

   h1_Vtx_Prim1 = new TH1D("h1_Vtx_Prim1","Vtx_Prim1",60,0,60);
   h1_Vtx_Good1 = new TH1D("h1_Vtx_Good1","Vtx_Good1",60,0,60);
   h1_W_Lept1_pt1 = new TH1D("h1_W_Lept1_pt1","W_Lept_pt1",50,0.,100);
   h1_npileup1 = new TH1D("h1_npileup1","npileup1",60,0.,60);
   h1_W_Neut_pt1 = new TH1D("h1_W_Neut_pt1","W_Neut_pt1",100,0.,100);
   h1_W_Neut_px_Corr = new TH1D("h1_W_Neut_px_Corr","W_Neut_px_Corr",100,-100,100);
   h1_W_Neut_py_Corr = new TH1D("h1_W_Neut_py_Corr","W_Neut_py_Corr",100,-100,100);
   h1_W_Neut_pt_Corr = new TH1D("h1_W_Neut_pt_Corr","W_Neut_pt_Corr",100,0.,100);
   h1_Z_Neut_pt = new TH1D("h1_Z_Neut_pt","Z_Neut_pt",100,0.,100);
   h1_Z_Neut_phi = new TH1D("h1_Z_Neut_phi","Z_Neut_phi",100,-4,4);
   h1_Z_Neut_px = new TH1D("h1_Z_Neut_px","Z_Neut_px",100,-100,100);
   h1_Z_Neut_py = new TH1D("h1_Z_Neut_py","Z_Neut_py",100,-100,100);
   h1_Z_Neut_pt_Corr = new TH1D("h1_Z_Neut_pt_Corr","Z_Neut_pt_Corr",100,0.,100);
   h1_Z_Neut_phi_Corr = new TH1D("h1_Z_Neut_phi_Corr","Z_Neut_phi_Corr",100,-4,4);
   h1_Z_Neut_px_Corr = new TH1D("h1_Z_Neut_px_Corr","Z_Neut_px_Corr",100,-100,100);
   h1_Z_Neut_py_Corr = new TH1D("h1_Z_Neut_py_Corr","Z_Neut_py_Corr",100,-100,100);

   h2_Z_Nvtx_px = new TH2D("h2_Z_Nvtx_px","Nvtx vs Nu_px",100,0,60,100,-100,100);
   h2_Z_Nvtx_py = new TH2D("h2_Z_Nvtx_py","Nvtx vs Nu_py",100,0,60,100,-100,100);
   h2_Z_Nvtx_px_Corr = new TH2D("h2_Z_Nvtx_px_Corr","Nvtx vs Nu_px",100,0,60,100,-100,100);
   h2_Z_Nvtx_py_Corr = new TH2D("h2_Z_Nvtx_py_Corr","Nvtx vs Nu_py",100,0,60,100,-100,100);

   
  if(AnaChannel == "ElectronHighPU" )
  {
   h1_W_Lep1_eta = new TH1D("h1_W_Lep1_eta","W_Lep1_eta",60,-3.,3.);
   for(int i(0);i<EtaBin;i++)
   {
   sprintf(histName,"h1_i_ToTal_%d",i);
   h1_i_ToTal[i] = new TH1D(histName,"W_i_ToTal",7000000,0.,7000000);
   sprintf(histName,"h1_i_All_%d",i);
   h1_i_All[i] = new TH1D(histName,"W_i_All",7000000,0.,7000000);
   sprintf(histName,"h1_i_other_%d",i);
   h1_i_other[i] = new TH1D(histName,"W_i_other",7000000,0.,7000000);
   sprintf(histName,"h1_i_Side_%d",i);
   h1_i_Side[i] = new TH1D(histName,"W_i_Side",7000000,0.,7000000);
   sprintf(histName,"h1_W_Neu_All_%d",i);
   h1_W_Neu_All[i] = new TH1D(histName,"W_Neu_pt_All",50,0.,100);
   sprintf(histName,"h1_W_Neu_pt_Side_%d",i);
   h1_W_Neu_pt_Side[i] = new TH1D(histName,"h1_W_Neu_pt_Side_check",50,0.,100);
   sprintf(histName,"h1_W_Neu_ToTal_beforeTrigger_%d",i);
   h1_W_Neu_pt_ToTal_beforeTrigger[i] = new TH1D(histName,"h1_W_Neu_pt_ToTal_beforeTrigger_check",50,0.,100);
   sprintf(histName,"h1_W_Neu_ToTal_%d",i);
   h1_W_Neu_pt_ToTal[i] = new TH1D(histName,"h1_W_Neu_pt_ToTal_check",50,0.,100);
   sprintf(histName,"h1_W_Neu_other_%d",i);
   h1_W_Neu_other[i] = new TH1D(histName,"h1_W_Neu_other_check",50,0.,100);
   sprintf(histName,"h1_W_Neu_AddElectron_%d",i);
   h1_W_Neu_AddElectron[i] = new TH1D(histName,"h1_W_Neu_AddElectron",50,0.,100);
     sprintf(histName,"h1_W_Neu_Eta_I_%d",i);
     h1_W_Neu_Eta_I[i] = new TH1D(histName,"h1_W_Neu_Eta_I",50,0.,100);
     sprintf(histName,"h1_W_Neu_Eta_P_%d",i);
     h1_W_Neu_Eta_P[i] = new TH1D(histName,"h1_W_Neu_Eta_P",50,0.,100);
     sprintf(histName,"h1_W_Neu_Eta_M_%d",i);
     h1_W_Neu_Eta_M[i] = new TH1D(histName,"h1_W_Neu_Eta_M",50,0.,100);
     sprintf(histName,"h1_WSide_Neu_eta_%d",i);
     h1_WSide_Neu_eta[i] = new TH1D(histName,"h1_WSide_Neu_eta",50,0.,100);
     sprintf(histName,"h1_WpSide_Neu_eta_%d",i);
     h1_WpSide_Neu_eta[i] = new TH1D(histName,"h1_WpSide_Neu_eta",50,0.,100);
     sprintf(histName,"h1_WmSide_Neu_eta_%d",i);
     h1_WmSide_Neu_eta[i] = new TH1D(histName,"h1_WmSide_Neu_eta",50,0.,100);
   }
  }
  //cut value check.
   h1_check_iw = new TH1D("h1_check_iw","h1_cutcheck_iw",10000,-2,2);
   h1_check_side_iw = new TH1D("h1_check_side_iw","h1_cutcheck_side_iw",10000,-2,2);
   h1_check_pt = new TH1D("h1_check_pt","h1_cutcheck_pt",100,0.,100);
   h1_check_side_pt = new TH1D("h1_check_side_pt","h1_cutcheck_side_pt",100,0.,100);
   h1_check_sigmaIetaIeta = new TH1D("h1_check_sigmaIetaIeta","h1_cutcheck_sigmaIetaIeta",100000,-1,1);
   h1_check_side_sigmaIetaIeta = new TH1D("h1_check_side_sigmaIetaIeta","h1_cutcheck_side_sigmaIetaIeta",100000,-1,1);
   h1_check_dEtaIn = new TH1D("h1_check_dEtaIn","h1_cutcheck_dEtaIn",100000,-1,1);
   h1_check_side_dEtaIn = new TH1D("h1_check_side_dEtaIn","h1_cutcheck_side_dEtaIn",100000,-1,1);
   h1_check_dPhiin = new TH1D("h1_check_dPhiin","h1_cutcheck_dPhiin",100000,-1,1);
   h1_check_side_dPhiin = new TH1D("h1_check_side_dPhiin","h1_cutcheck_side_dPhiin",100000,-1,1);
   h1_check_HoverE = new TH1D("h1_check_HoverE","h1_cutcheck_HoverE",100000,-1,1);
   h1_check_side_HoverE = new TH1D("h1_check_side_HoverE","h1_cutcheck_side_HoverE",100000,-1,1);
   h1_check_dxy = new TH1D("h1_check_dxy","h1_cutcheck_dxy",100000,-1,1);
   h1_check_side_dxy = new TH1D("h1_check_side_dxy","h1_cutcheck_side_dxy",100000,-1,1);
   h1_check_dz = new TH1D("h1_check_dz","h1_cutcheck_dz",100000,-1,1);
   h1_check_side_dz = new TH1D("h1_check_side_dz","h1_cutcheck_side_dz",100000,-1,1);
   h1_check_InvE_InvP = new TH1D("h1_check_InvE_InvP","h1_cutcheck_InvE_InvP",100000,-1,1);
   h1_check_side_InvE_InvP = new TH1D("h1_check_side_InvE_InvP","h1_cutcheck_side_InvE_InvP",100000,-1,1);
   h1_check_mHits = new TH1D("h1_check_mHits","h1_cutcheck_mHits",100000,-1,1);
   h1_check_side_mHits = new TH1D("h1_check_side_mHits","h1_cutcheck_side_mHits",100000,-1,1);
   h1_check_lep_eta = new TH1D("h1_check_lep_eta","h1_cutcheck_lep_eta",1000,-2.6,2.6);
   h1_check_side_lep_eta = new TH1D("h1_check_side_lep_eta","h1_cutcheck_side_lep_eta",1000,-2.6,2.6);

   h1_W_Lept1_pt = new TH1D("h1_W_Lept1_pt","W_Lept_pt",50,0.,100);
   h1_W_pt	= new TH1D("h1_W_pt","Wpt",NWptBinPlus-1,Bins);
   h2_WpT_lepPt =new TH2D("h2_WpT_lepPt","WpT_LepPt",600,0,600,600,0,600);
   h2_WpT_lepPt_Plus =new TH2D("h2_WpT_lepPt_Plus","WpT_LepPt-Plus Charge",600,0,600,600,0,600);
   h2_WpT_lepPt_Minus =new TH2D("h2_WpT_lepPt_Minus","WpT_LepPt-Minus Charge",600,0,600,600,0,600);

   h2_ZLep1_ZLep2 =new TH2D("h2_ZLep1_ZLep2","Z_LepPt1-LepPt2",600,0,600,600,0,600);
   h2_Zmass_ZLep1 =new TH2D("h2_Zmass_ZLep1","Zmass-LepPt1",600,0,600,600,0,600);
   h2_Zmass_ZLep2 =new TH2D("h2_Zmass_ZLep2","Zmass-LepPt2",600,0,600,600,0,600);

   h1_Zpt= new TH1D("h1_Zpt","Zpt",120,0,200);
   h2_Zpt_ZLep1 =new TH2D("h2_Zpt_ZLep1","Zpt-LepPt1",400,0,400,400,0,400);
   h2_Zpt_ZLep2 =new TH2D("h2_Zpt_ZLep2","Zpt-LepPt2",400,0,400,400,0,400);


   //Acceptance Histograms
   h1_Born_AP=new TH1D("h1_Born_AP","Born WpT All Phase",NWptBinPlus-1,Bins);
   h1_Born_BornFid=new TH1D("h1_Born_BornFid","Born WpT at BornFid",NWptBinPlus-1,Bins);
   h1_Born_BornFid_Even=new TH1D("h1_Born_BornFid_Even","Born WpT at BornFid",NWptBinPlus-1,Bins);
   h1_Born_BothFid=new TH1D("h1_Born_BothFid","Born WpT at BothFid",NWptBinPlus-1,Bins);
   h1_Born_BothFid_Even=new TH1D("h1_Born_BothFid_Even","Born WpT at BothFid",NWptBinPlus-1,Bins);

   h1_Post_PostFid=new TH1D("h1_Post_PostFid","Post WpT at PostFid",NWptBinPlus-1,Bins);
   h1_Post_PostFid_Even=new TH1D("h1_Post_PostFid_Even","Post WpT at PostFid",NWptBinPlus-1,Bins);
   h1_Post_BothFid=new TH1D("h1_Post_BothFid","Post WpT at BothFid",NWptBinPlus-1,Bins);
   h1_Post_BothFid_Even=new TH1D("h1_Post_BothFid_Even","Post WpT at BothFid",NWptBinPlus-1,Bins);
   h2_PostBorn_BothFid=new TH2D("h2_PostBorn_BothFid","Post vs Born at BothFid",NWptBinPlus-1,Bins, NWptBinPlus-1,Bins);

   // MisChargeStudy 
/*   if(AnaChannel == "ElectronHighPU" )
     {
      h1_Zmass_QAll = new TH1D("h1_Zmass_QAll","Invariant mass for Z",120,60,120);
      for(int i(0);i<lept1eta;i++)
       {
        for(int j=0;j<lept2eta;j++){
        sprintf(histName,"h1_Zmass_QThree_%d_%d",i,j);
        h1_Zmass_QThree[i][j] = new TH1D(histName,"Three Charge Requirement",120,60,120);
        sprintf(histName,"h1_Zmass_QThreeSame_%d_%d",i,j);
        h1_Zmass_QThreeSame[i][j] = new TH1D(histName,"Three Charge Requirement",120,60,120);
        sprintf(histName,"h1_Zmass_QNo_%d_%d",i,j);
        h1_Zmass_QNo[i][j] = new TH1D(histName,"No Charge Requirement",120,60,120);
        sprintf(histName,"h1_Zmass_QNoSame_%d_%d",i,j);
        h1_Zmass_QNoSame[i][j] = new TH1D(histName,"No Charge Requirement",120,60,120);
        }
       }
     }
*/
   // Unfold
   h1_Truth_Rec		=new TH1D("h1_Truth_Rec","Simul Wpt Truth",NWptBinPlus-1,Bins);
   h1_Truth_Rec_Even	=new TH1D("h1_Truth_Rec_Even","Simul Wpt Truth_Even",NWptBinPlus-1,Bins);
   h1_Truth_Rec_Odd	=new TH1D("h1_Truth_Rec_Odd","Simul Wpt Truth_Odd",NWptBinPlus-1,Bins);
   h1_Truth_Post	=new TH1D("h1_Truth_Post","Post Wpt Truth",NWptBinPlus-1,Bins);
   h1_Truth_Post_Even	=new TH1D("h1_Truth_Post_Even","Post Wpt Truth_Even",NWptBinPlus-1,Bins);
   h1_Truth_Post_Odd	=new TH1D("h1_Truth_Post_Odd" ,"Post Wpt Truth_Odd",NWptBinPlus-1,Bins);
   h1_Truth_Post_EffCorr=new TH1D("h1_Truth_Post_EffCorr","Post Wpt Truth EffCorr",NWptBinPlus-1,Bins);
   h2_Truth_Rec_AP_Post	=new TH2D("h2_Truth_Rec_AP_Post" ,"Truth Rec All Phase Post",NWptBinPlus-1,Bins,NWptBinPlus-1, Bins);

   h1_Wp_pt	= new TH1D("h1_Wp_pt","WplusPt",NWptBinPlus-1,Bins);
   h1_Wm_pt	= new TH1D("h1_Wm_pt","WminusPt",NWptBinPlus-1,Bins);
   //for( int i(0);i<NWptBinPlus-1;i++)
   //{
   //  sprintf(histName,"h1_pstFsr2ReconW_pt_%d",i);
   //  h1_pstFsr2ReconW_pt[i]=
   //    new TH1D(histName,"pstFsr2ReconW_pt",NWptBinPlus-1,Bins);
   //}
   sprintf(histName,"h2_WpT_ReconPstFsr");
   h2_WpT_ReconPstFsr=
       new TH2D(histName,histName,NWptBinPlus-1,Bins,NWptBinPlus-1,Bins);
   for( int i=0;i<NWptBinPlus;i++){
     if( i==1 || i==2)
     {
       sprintf(histName,"h1_W_pt_RecoPreFsrGenRes_%d",i);
       h1_W_pt_RecoPreFsrGenRes[i] = new TH1D(histName,"Reco Gen Resol",50,-1.1,3.1);
       sprintf(histName,"h1_W_pt_RecoPstFsrGenRes_%d",i);
       h1_W_pt_RecoPstFsrGenRes[i]=new TH1D(histName,"Reco Gen Resol",50,-1.1,3.1);
     }else{
       sprintf(histName,"h1_W_pt_RecoPreFsrGenRes_%d",i);
       h1_W_pt_RecoPreFsrGenRes[i] = new TH1D(histName,"Reco Gen Resol",50,-1.1,1.1);
       sprintf(histName,"h1_W_pt_RecoPstFsrGenRes_%d",i);
       h1_W_pt_RecoPstFsrGenRes[i] = new TH1D(histName,"Reco Gen Resol",50,-1.1,1.1);
     }

     if( i < NBIN_PT_DIVIDER_1and2 ){
       sprintf(histName,"h2_Met_LepPt_%d",i);
       h2_Met_LepPt[i] = new TH2D(histName,"Met_LepPt",200,0,200,200,0,200);
       sprintf(histName,"h2_Met_WpT_%d",i);
       h2_Met_WpT[i] = new TH2D(histName,"Met_WpT",200,0,200,200,0,200);
       sprintf(histName,"h1_W_Neu_pt_%d",i);
       h1_W_Neu_pt[i] = new TH1D(histName,"W_Neut_pt",NBINS_1,0,METMAX_1);
       sprintf(histName,"h1_GenW_Neu_pt_%d",i);
       h1_GenW_Neu_pt[i] = new TH1D(histName,"GenW_Neut_pt",NBINS_1,0,METMAX_1);
       sprintf(histName,"h1_WSide_Neu_pt_%d",i);
       h1_WSide_Neu_pt[i] = new TH1D(histName,"WSide_Neut_pt",NBINS_1,0,METMAX_1);
       sprintf(histName,"h1_Wp_Neu_pt_%d",i);
       h1_Wp_Neu_pt[i] = new TH1D(histName,"Wp_Neut_pt",NBINS_1,0,METMAX_1);
       sprintf(histName,"h1_GenWp_Neu_pt_%d",i);
       h1_GenWp_Neu_pt[i] = new TH1D(histName,"GenWp_Neut_pt",NBINS_1,0,METMAX_1);
       sprintf(histName,"h1_WpSide_Neu_pt_%d",i);
       h1_WpSide_Neu_pt[i] = new TH1D(histName,"WpSide_Neut_pt",NBINS_1,0,METMAX_1);
       sprintf(histName,"h1_Wm_Neu_pt_%d",i);
       h1_Wm_Neu_pt[i] = new TH1D(histName,"Wm_Neut_pt",NBINS_1,0,METMAX_1);
       sprintf(histName,"h1_GenWm_Neu_pt_%d",i);
       h1_GenWm_Neu_pt[i] = new TH1D(histName,"GenWm_Neut_pt",NBINS_1,0,METMAX_1);
       sprintf(histName,"h1_WmSide_Neu_pt_%d",i);
       h1_WmSide_Neu_pt[i] = new TH1D(histName,"WmSide_Neut_pt",NBINS_1,0,METMAX_1);
       
     } else if ( i < NBIN_PT_DIVIDER_2and3 ){
       sprintf(histName,"h2_Met_LepPt_%d",i);
       h2_Met_LepPt[i] = new TH2D(histName,"Met_LepPt",200,0,200,200,0,200);
       sprintf(histName,"h2_Met_WpT_%d",i);
       h2_Met_WpT[i] = new TH2D(histName,"Met_WpT",200,0,200,200,0,200);

       sprintf(histName,"h1_W_Neu_pt_%d",i);
       h1_W_Neu_pt[i] = new TH1D(histName,"W_Neut_pt",NBINS_2,0,METMAX_2);
       sprintf(histName,"h1_GenW_Neu_pt_%d",i);
       h1_GenW_Neu_pt[i] = new TH1D(histName,"GenW_Neut_pt",NBINS_2,0,METMAX_2);
       sprintf(histName,"h1_WSide_Neu_pt_%d",i);
       h1_WSide_Neu_pt[i] = new TH1D(histName,"WSide_Neut_pt",NBINS_2,0,METMAX_2);
       sprintf(histName,"h1_Wp_Neu_pt_%d",i);
       h1_Wp_Neu_pt[i] = new TH1D(histName,"Wp_Neut_pt",NBINS_2,0,METMAX_2);
       sprintf(histName,"h1_GenWp_Neu_pt_%d",i);
       h1_GenWp_Neu_pt[i] = new TH1D(histName,"GenWp_Neut_pt",NBINS_2,0,METMAX_2);
       sprintf(histName,"h1_WpSide_Neu_pt_%d",i);
       h1_WpSide_Neu_pt[i] = new TH1D(histName,"WpSide_Neut_pt",NBINS_2,0,METMAX_2);
       sprintf(histName,"h1_Wm_Neu_pt_%d",i);
       h1_Wm_Neu_pt[i] = new TH1D(histName,"Wm_Neut_pt",NBINS_2,0,METMAX_2);
       sprintf(histName,"h1_GenWm_Neu_pt_%d",i);
       h1_GenWm_Neu_pt[i] = new TH1D(histName,"GenWm_Neut_pt",NBINS_2,0,METMAX_2);
       sprintf(histName,"h1_WmSide_Neu_pt_%d",i);
       h1_WmSide_Neu_pt[i] = new TH1D(histName,"WmSide_Neut_pt",NBINS_2,0,METMAX_2);

     } else {
       sprintf(histName,"h2_Met_LepPt_%d",i);
       h2_Met_LepPt[i] = new TH2D(histName,"Met_LepPt",200,0,200,200,0,200);
       sprintf(histName,"h2_Met_WpT_%d",i);
       h2_Met_WpT[i] = new TH2D(histName,"Met_WpT",200,0,200,200,0,200);

       sprintf(histName,"h1_W_Neu_pt_%d",i);
       h1_W_Neu_pt[i] = new TH1D(histName,"W_Neut_pt",NBINS_3,0,METMAX_3);
       sprintf(histName,"h1_GenW_Neu_pt_%d",i);
       h1_GenW_Neu_pt[i] = new TH1D(histName,"GenW_Neut_pt",NBINS_3,0,METMAX_3);
       sprintf(histName,"h1_WSide_Neu_pt_%d",i);
       h1_WSide_Neu_pt[i] = new TH1D(histName,"WSide_Neut_pt",NBINS_3,0,METMAX_3);
       sprintf(histName,"h1_Wp_Neu_pt_%d",i);
       h1_Wp_Neu_pt[i] = new TH1D(histName,"Wp_Neut_pt",NBINS_3,0,METMAX_3);
       sprintf(histName,"h1_GenWp_Neu_pt_%d",i);
       h1_GenWp_Neu_pt[i] = new TH1D(histName,"GenWp_Neut_pt",NBINS_3,0,METMAX_3);
       sprintf(histName,"h1_WpSide_Neu_pt_%d",i);
       h1_WpSide_Neu_pt[i] = new TH1D(histName,"WpSide_Neut_pt",NBINS_3,0,METMAX_3);
       sprintf(histName,"h1_Wm_Neu_pt_%d",i);
       h1_Wm_Neu_pt[i] = new TH1D(histName,"Wm_Neut_pt",NBINS_3,0,METMAX_3);
       sprintf(histName,"h1_GenWm_Neu_pt_%d",i);
       h1_GenWm_Neu_pt[i] = new TH1D(histName,"GenWm_Neut_pt",NBINS_3,0,METMAX_3);
       sprintf(histName,"h1_WmSide_Neu_pt_%d",i);
       h1_WmSide_Neu_pt[i] = new TH1D(histName,"WmSide_Neut_pt",NBINS_3,0,METMAX_3);
     }
   }


   //---------------
   h1_W_Mt	= new TH1D("h1_W_Mt","W Mt",100,0.,100);
   h1_PuWeight	= new TH1D("h1_PuWeight","PU weight",30,0.,1.5);
   h1_W_Acop	= new TH1D("h1_W_Acop","Mu vs MET Acop",30,0.,3.14);
   h1_vtx_z	= new TH1D("h1_vtx_z","Vtx_z",60,-30,30);
   h1_vtx_Rho	= new TH1D("h1_vtx_Rho","Vtx_Rho",40,0.3,0.7);

   h1_GlbMuChi2	= new TH1D("h1_GlbMuChi2","global Mu chi2/ndof",60,0.,20);
   h1_muonHits	= new TH1D("h1_muonHits","muon chamber hits",11,0.,11);
   h1_muMatchStation= new TH1D("h1_muMatchStation","muon matched stations",5,0.,5);
   h1_trkLayers= new TH1D("h1_trkLayers","no. of trk layers",20,0.,20);
   h1_pixelHits= new TH1D("h1_pixelHits","no. of pixelHits",8,0.,8);
   h1_dB= new TH1D("h1_dB","dB",40,0.,0.14);
   h1_dz= new TH1D("h1_dz","dz",30,0.,0.7);
   h1_IsoCom03= new TH1D("h1_IsoCom03","ch nh ph",30,0.,0.3);
   h1_IsoCom04= new TH1D("h1_IsoCom04","ch nh ph",30,0.,0.3);
   h1_IsoHad03= new TH1D("h1_IsoHad03","ch nh ph",30,0.,0.3);
   h1_IsoHad04= new TH1D("h1_IsoHad04","ch nh ph",30,0.,0.3);
   h1_IsoBeta03= new TH1D("h1_IsoBeta03","ch beta",30,0.,0.3);
   h1_IsoBeta04= new TH1D("h1_IsoBeta04","ch beta",30,0.,0.3);
   //Z=============
   h1_diLeptVtxProb= new TH1D("h1_diLeptVtxProb","di-Lept vtx prob",60,0.,1);
   h1_Zmass= new TH1D("h1_Zmass","Inv Mass for dilepts",120,60,120);
   h1_Zmass_BB= new TH1D("h1_Zmass_BB","Inv Mass for dilepts BB",120,60,120);
   h1_Zmass_BE= new TH1D("h1_Zmass_BE","Inv Mass for dilepts BE",120,60,120);
   h1_Zmass_EE= new TH1D("h1_Zmass_EE","Inv Mass for dilepts EE",120,60,120);
   h1_ZmassCorr= new TH1D("h1_ZmassCorr","Inv Mass for dilepts after Scale&Smear",120,60,120);
   h1_ZmassCorr_BB= new TH1D("h1_ZmassCorr_BB","Inv Mass for dilepts after Scale&Smear BB",120,60,120);
   h1_ZmassCorr_BE= new TH1D("h1_ZmassCorr_BE","Inv Mass for dilepts after Scale&Smear BE",120,60,120);
   h1_ZmassCorr_EE= new TH1D("h1_ZmassCorr_EE","Inv Mass for dilepts after Scale&Smear EE",120,60,120);
   h2_u1Zpt= new TH2D("h2_u1Zpt","u1 vs Zpt",300,0,300,100,-150,50);
   h2_u2Zpt= new TH2D("h2_u2Zpt","u2 vs Zpt",300,0,300,80,-40,40);
   h2_u3Zpt= new TH2D("h2_u3Zpt","u3 vs Zpt",300,0,300,80,-40,40);
   //0,3,6,10,14,18,23,30,40,55,70,100
   for(int i(0);i<u1Bin;i++)
   {
     //double mean_, binCent;
     //binCent = (RecoilBins[i]+RecoilBins[i+1])/2.;
     sprintf(histName,"h1_u1Z_%d",i);
     //mean_ = 0.6-0.85*binCent;
     h1_u1Z[i]= new TH1D(histName,"h1_u1Z",150,-150-RecoilBins[i],150-RecoilBins[i]);
     //h1_u1Z[i]= new TH1D(histName,"h1_u1Z",50,mean_-80,mean_+50);
     sprintf(histName,"h1_u2Z_%d",i);
     h1_u2Z[i] = new TH1D(histName,"h1_u2Z",150,-150,150);
     sprintf(histName,"h1_u3Z_%d",i);
     h1_u3Z[i] = new TH1D(histName,"h1_u3Z",100,-100,100);
     sprintf(histName,"h1_u1W_%d",i);
     //mean_ = 0.6-0.85*binCent;
     h1_u1W[i]= new TH1D(histName,"h1_u1W",150,-150-RecoilBins[i],150-RecoilBins[i]);
     //h1_u1W[i]= new TH1D(histName,"h1_u1W",50,mean_-80,mean_+50);
     sprintf(histName,"h1_u2W_%d",i);
     h1_u2W[i] = new TH1D(histName,"h1_u2W",150,-150,150);
     sprintf(histName,"h1_u3W_%d",i);
     h1_u3W[i] = new TH1D(histName,"h1_u3W",100,-100,100);
   }

   if(Mode == "ScaleMakeMC")
   {
     cout<<"Setting Random Seed for ScaleMakeMC"<<endl;
     switch (ETARANGE)
     {
       case 0:
	 gRandom->SetSeed(0x12345);
	 break;
       case 1:
	 gRandom->SetSeed(0x12346);
	 break;
       case 2:
	 gRandom->SetSeed(0x12347);
	 break;
       case 3:
	 gRandom->SetSeed(0x12348);
	 break;
       case 4:
	 gRandom->SetSeed(0x12349);
	 break;
       case 5:
	 gRandom->SetSeed(0x12350);
	 break;
       default:
	 cout<<"ScaleMake MC: What is this Eta range?"<<endl;
	 exit(0);
     }
   }

   if(Mode == "ScaleMakeMC" || Mode == "ScaleMakeRD")
   {

     //h1_ZmassDaughEtaRD = new TH1D("h1_ZmassDaughEtaRD","h1_ZmassDaughEtaRD",60,60,120);
     //for(int i(0);i<=ScaleBins-1;i++)for(int j(0);j<=ScaleBins-1;j++)
     //  sprintf(histName,"h1_ZmassDaughEta_%d_%d",i,j);
     //  h1_ZmassDaughEta[i][j]=
     //	 new TH1D(histName,"ZmassDaughterEta",60,60,120);

     if( AnaChannel=="ElectronLowPU")
     {
       for(int i(0);i<ScElCombiBins;i++)
       {
	 sprintf(histName,"h1_ZmassDaughEta_%d",i);
	 h1_ZmassDaughEta[i]= new TH1D(histName,"ZmassDaughterEta",60,60,120);
       }
     }
     if( AnaChannel=="ElectronHighPU")
     {
       for(int i(0);i<ScElCombiBinsHighPU;i++)
       {
         sprintf(histName,"h1_ZmassDaughEta_%d",i);
         h1_ZmassDaughEta[i]= new TH1D(histName,"ZmassDaughterEta",60,60,120);
       }
     }
     if( AnaChannel=="MuonLowPU" || AnaChannel=="MuonHighPU")
     {
       for(int i(0);i<ScMuCombiBins;i++)
       {
	 sprintf(histName,"h1_ZmassDaughEtaMu_%d",i);
	 h1_ZmassDaughEtaMu[i]= new TH1D(histName,"ZmassDaughterEtaMu",60,60,120);
       }
     }
   }
   Notify();
}
   WEleQ::WEleQ(TTree *WEleQTree,TTree *WLepTree, double lumiweight,TString OutFileName_, TString mode_, TString AnaChannel_, int etaRange_) : fChain(0) 
//WEleQ::WEleQ(TTree *tree) : fChain(0) 
  {
    // if parameter tree is not specified (or zero), connect the file
    // // used to generate this class and read the Tree.
   cout<<"WEleQ constructor"<<endl;
   cout<<"initialization for bins"<<endl;
   //{0,2.5,5,7.5,10,12.5,15,17.5,20,30,40,50,70,90,150,190,250,600}; //Zpt Bins
   //0,4,8,15,23,30,38,46,55,65,75,85,95,107,120,132,145,160,175,192,210,250,300 Atlas 22 bins
   //{0,8,23,38,55,75,95,120,145,175,210,300};//Atlas Unfolding bin
   //
   //ZpT bins
  //Bins[0]=     0.;
  //Bins[1]=     2.5;
  //Bins[2]=     5;
  //Bins[3]=     7.5;
  //Bins[4]=     10;
  //Bins[5]=     12.5;
  //Bins[6]=     15;
  //Bins[7]=     17.5;
  //Bins[8]=     20.;
  //Bins[9]=     30.;
  //Bins[10]=    40.;
  //Bins[11]=    50.;
  //Bins[12]=    70.;
  //Bins[13]=    90.;
  //Bins[14]=    110.;
  //Bins[15]=    150.;
  //Bins[16]=    190.;
  //Bins[17]=    250.;
  //Bins[18]=    600.;
   // Final Bins
   Bins[0]=     0.;
   Bins[1]=     7.5;
   Bins[2]=     12.5;
   Bins[3]=     17.5;
   Bins[4]=     24.;
   Bins[5]=     30.;
   Bins[6]=    40.;
   Bins[7]=    50.;
   Bins[8]=    70.;
   Bins[9]=    110.;
   Bins[10]=    150.;
   Bins[11]=    190.;
   Bins[12]=    250.;
   Bins[13]=    600.;

   cout<<"initialization for Recoil bins"<<endl;
   RecoilBins[0]	= 0.;
   RecoilBins[1]	= 5.;
   RecoilBins[2]	= 10.;
   RecoilBins[3]	= 15.;
   RecoilBins[4]	= 20.;
   RecoilBins[5]	= 25.;
   RecoilBins[6]	= 30.;
   RecoilBins[7]	= 35.;
   RecoilBins[8]	= 40.;
   RecoilBins[9]	= 50.;
   RecoilBins[10]	= 60.;
   RecoilBins[11]	= 70.;
   RecoilBins[12]	= 80.;
   RecoilBins[13]	= 90.;
   RecoilBins[14]       = 100.;
   RecoilBins[15]       = 120.;
   RecoilBins[16]       = 150.;
/*
   wqaMetMXBins[0] = 0.1; wqaMetMXBins[1] = 0.2; wqaMetMXBins[2] = 0.3; wqaMetMXBins[3] = 0.4; wqaMetMXBins[4] = 0.5;
      wqaMetMXBins[5] = 0.6; wqaMetMXBins[6] = 0.7; wqaMetMXBins[7] = 0.8; wqaMetMXBins[8] = 0.9; wqaMetMXBins[9] = 1.0;
         wqaMetMXBins[10] = 1.1; wqaMetMXBins[11] = 1.2; wqaMetMXBins[12] = 1.3; wqaMetMXBins[13] = 1.4; wqaMetMXBins[14] = 1.5;
	    wqaMetMXBins[15] = 1.6; wqaMetMXBins[16] = 1.7; wqaMetMXBins[17] = 1.8; wqaMetMXBins[18] = 1.9; wqaMetMXBins[19] = 2.0;
	       wqaMetMXBins[20] = 2.1; wqaMetMXBins[21] = 2.2; wqaMetMXBins[22] = 2.3; wqaMetMXBins[23] = 2.4; wqaMetMXBins[24] = 2.5;

	          wqaMetMNBins[0] = 0.0; wqaMetMNBins[1] = 0.1; wqaMetMNBins[2] = 0.2; wqaMetMNBins[3] = 0.3;  wqaMetMNBins[4] = 0.4;
		     wqaMetMNBins[5] = 0.5; wqaMetMNBins[6] = 0.6; wqaMetMNBins[7] = 0.7; wqaMetMNBins[8] = 0.8;  wqaMetMNBins[9] = 0.9;
		        wqaMetMNBins[10] = 1.0; wqaMetMNBins[11] = 1.1; wqaMetMNBins[12] = 1.2; wqaMetMNBins[13] = 1.3;   wqaMetMNBins[14] = 1.4;
			   wqaMetMNBins[15] = 1.5; wqaMetMNBins[16] = 1.6; wqaMetMNBins[17] = 1.7; wqaMetMNBins[18] = 1.8;   wqaMetMNBins[19] = 1.9;
			      wqaMetMNBins[20] = 2.0; wqaMetMNBins[21] = 2.1; wqaMetMNBins[22] = 2.2; wqaMetMNBins[23] = 2.3;   wqaMetMNBins[24] = 2.4;
 */


   wqaMetMXBins[0] = 0.2; wqaMetMXBins[1] = 0.4; wqaMetMXBins[2] = 0.6; wqaMetMXBins[3] = 0.8; wqaMetMXBins[4] = 1.0;
   wqaMetMXBins[5] = 1.2; wqaMetMXBins[6] = 1.4; wqaMetMXBins[7] = 1.6; wqaMetMXBins[8] = 1.8; wqaMetMXBins[9] = 2.0;
   wqaMetMXBins[10] = 2.2; wqaMetMXBins[11] = 2.4; 

   wqaMetMNBins[0] = 0.0; wqaMetMNBins[1] = 0.2; wqaMetMNBins[2] = 0.4; wqaMetMNBins[3] = 0.6;  wqaMetMNBins[4] = 0.8;
   wqaMetMNBins[5] = 1.0; wqaMetMNBins[6] = 1.2; wqaMetMNBins[7] = 1.4; wqaMetMNBins[8] = 1.6;  wqaMetMNBins[9] = 1.8;
   wqaMetMNBins[10] = 2.0; wqaMetMNBins[11] = 2.2;

   if (WEleQTree == 0 || WLepTree == 0) {
     /****************
#ifdef SINGLE_TREE
      // The following code should be used if you want this class to access
      // a single tree instead of a chain
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Memory Directory");
      if (!f || !f->IsOpen()) {
         f = new TFile("Memory Directory");
      }
      f->GetObject("WEleQ/tree",tree);

#else // SINGLE_TREE

      // The following code should be used if you want this class to access a chain
      // of trees.
      TChain * chain = new TChain("WEleQ/tree","");
      chain->Add("/terranova_1/W_Ntuple/SingleMuRun2012APromptRecoV1Aod/wNtuple_01.root");
      tree = chain;
#endif // SINGLE_TREE

**********************/
     cout<<"Usage: WEleQ(TTree*, TTree*) "<<endl;
   }else{
     cout<<"WEleQ.h: initializing the trees"<<endl;
   LumiWeight = lumiweight;
   OutFileName = OutFileName_;
   Mode = mode_;
   AnaChannel = AnaChannel_;
   ETARANGE = etaRange_;
   Init(WEleQTree);
   //wMuons.Init(WLepTree);

   }

  }


   WEleQ::~WEleQ()
   {
     if (!fChain) return;
     delete fChain->GetCurrentFile();
   }

   Int_t WEleQ::GetEntry(Long64_t entry)
   {
     // Read contents of entry.
     if (!fChain) return 0;
     return fChain->GetEntry(entry);
   }

   Long64_t WEleQ::LoadTree(Long64_t entry)
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
   
   Bool_t WEleQ::Notify()
   {
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

     return kTRUE;
   }


   void WEleQ::Show(Long64_t entry)
   {
     // Print contents of entry.
     // If entry is not specified, print current entry
     if (!fChain) return;
     fChain->Show(entry);
   }

// Electron effi correction
Double_t WEleQ::ElePlusEffiCorrection(double elePt, double eleEtaSC)
{

  if (elePt>25. && elePt <=35.)
  {
    if (eleEtaSC >-2.5 && eleEtaSC <= -1.5 )  {return 0.9737;}
    if (eleEtaSC >-1.5 && eleEtaSC <= -0.5 )  {return 0.9114;}
    if (eleEtaSC >-0.5 && eleEtaSC <= 0.0 )   {return 1.1486;}
    if (eleEtaSC > 0.0 && eleEtaSC <= 0.5 )   {return 0.9055;}
    if (eleEtaSC > 0.5 && eleEtaSC <= 1.5 )   {return 1.0168;}
    if (eleEtaSC > 1.5 && eleEtaSC < 2.5 )   {return 0.9424;}
  }else if (elePt>35. && elePt <=50.)
  {
    if (eleEtaSC >-2.5 && eleEtaSC <= -1.5 )  {return 1.0366;}
    if (eleEtaSC >-1.5 && eleEtaSC <= -0.5 )  {return 0.9818;}
    if (eleEtaSC >-0.5 && eleEtaSC <= 0.0 )   {return 0.9518;}
    if (eleEtaSC > 0.0 && eleEtaSC <= 0.5 )   {return 0.9496;}
    if (eleEtaSC > 0.5 && eleEtaSC <= 1.5 )   {return 0.9555;}
    if (eleEtaSC > 1.5 && eleEtaSC < 2.5 )   {return 1.0110;}
  }else if (elePt>50. )
  {
    if (eleEtaSC >-2.5 && eleEtaSC <= -1.5 )  {return 1.1285;}
    if (eleEtaSC >-1.5 && eleEtaSC <= -0.5 )  {return 0.9445;}
    if (eleEtaSC >-0.5 && eleEtaSC <= 0.0 )   {return 1.0736;}
    if (eleEtaSC > 0.0 && eleEtaSC <= 0.5 )   {return 0.9981;}
    if (eleEtaSC > 0.5 && eleEtaSC <= 1.5 )   {return 0.9692;}
    if (eleEtaSC > 1.5 && eleEtaSC < 2.5 )   {return 1.0308;}
  }
}
Double_t WEleQ::EleMinusEffiCorrection(double elePt, double eleEtaSC)
{

  if (elePt>25. && elePt <=35.)
  {
    if (eleEtaSC >-2.5 && eleEtaSC <= -1.5 )  {return 0.9944;}
    if (eleEtaSC >-1.5 && eleEtaSC <= -0.5 )  {return 1.0321;}
    if (eleEtaSC >-0.5 && eleEtaSC <= 0.0 )   {return 0.9704;}
    if (eleEtaSC > 0.0 && eleEtaSC <= 0.5 )   {return 0.8589;}
    if (eleEtaSC > 0.5 && eleEtaSC <= 1.5 )   {return 0.9825;}
    if (eleEtaSC > 1.5 && eleEtaSC < 2.5 )   {return 0.9941;}
  }else if (elePt>35. && elePt <=50.)
  {
    if (eleEtaSC >-2.5 && eleEtaSC <= -1.5 )  {return 1.0041;}
    if (eleEtaSC >-1.5 && eleEtaSC <= -0.5 )  {return 0.9798;}
    if (eleEtaSC >-0.5 && eleEtaSC <= 0.0 )   {return 0.9481;}
    if (eleEtaSC > 0.0 && eleEtaSC <= 0.5 )   {return 0.9305;}
    if (eleEtaSC > 0.5 && eleEtaSC <= 1.5 )   {return 0.9816;}
    if (eleEtaSC > 1.5 && eleEtaSC < 2.5 )   {return 0.9401;}
  }else if (elePt>50. )
  {
    if (eleEtaSC >-2.5 && eleEtaSC <= -1.5 )  {return 0.9440;}
    if (eleEtaSC >-1.5 && eleEtaSC <= -0.5 )  {return 0.9553;}
    if (eleEtaSC >-0.5 && eleEtaSC <= 0.0 )   {return 0.9645;}
    if (eleEtaSC > 0.0 && eleEtaSC <= 0.5 )   {return 0.9692;}
    if (eleEtaSC > 0.5 && eleEtaSC <= 1.5 )   {return 0.9718;}
    if (eleEtaSC > 1.5 && eleEtaSC < 2.5 )   {return 0.8523;}
  }
}

// Muon effi correction
Double_t WEleQ::MuonPlusEffiCorrection(double muonPt, double muonEta)
{

  if (muonPt>20. && muonPt <=40.)
  {
    if (muonEta >-2.1 && muonEta <= -1.2 )  {return 0.9534;}
    if (muonEta >-1.2 && muonEta <= -0.8 )  {return 1.0644;}
    if (muonEta >-0.8 && muonEta <= 0.0 )   {return 0.9775;}
    if (muonEta > 0.0 && muonEta <= 0.8 )   {return 0.9822;}
    if (muonEta > 0.8 && muonEta <= 1.2 )   {return 0.9064;}
    if (muonEta > 1.2 && muonEta < 2.1 )   {return 1.0013;}
  }else if (muonPt>40. && muonPt <=55.)
  {
    if (muonEta >-2.1 && muonEta <= -1.2 )  {return 0.9639;}
    if (muonEta >-1.2 && muonEta <= -0.8 )  {return 0.9755;}
    if (muonEta >-0.8 && muonEta <= 0.0 )   {return 0.9843;}
    if (muonEta > 0.0 && muonEta <= 0.8 )   {return 0.9837;}
    if (muonEta > 0.8 && muonEta <= 1.2 )   {return 0.9741;}
    if (muonEta > 1.2 && muonEta < 2.1 )   {return 0.9893;}
  }else if (muonPt>55. )
  {
    if (muonEta >-2.1 && muonEta <= -1.2 )  {return 1.0554;}
    if (muonEta >-1.2 && muonEta <= -0.8 )  {return 0.9995;}
    if (muonEta >-0.8 && muonEta <= 0.0 )   {return 0.9845;}
    if (muonEta > 0.0 && muonEta <= 0.8 )   {return 0.9923;}
    if (muonEta > 0.8 && muonEta <= 1.2 )   {return 1.0627;}
    if (muonEta > 1.2 && muonEta < 2.1 )   {return 1.0705;}
  }
}

Double_t WEleQ::MuonMinusEffiCorrection(double muonPt, double muonEta)
{
  if (muonPt>20. && muonPt <=40.)
  {
    if (muonEta >-2.1 && muonEta <= -1.2 )  {return 0.9813;}
    if (muonEta >-1.2 && muonEta <= -0.8 )  {return 0.9363;}
    if (muonEta >-0.8 && muonEta <= 0.0 )   {return 0.9594;}
    if (muonEta > 0.0 && muonEta <= 0.8 )   {return 0.9816;}
    if (muonEta > 0.8 && muonEta <= 1.2 )   {return 0.9346;}
    if (muonEta > 1.2 && muonEta < 2.1 )   {return 1.0084;}
  }else if (muonPt>40. && muonPt <=55.)
  {
    if (muonEta >-2.1 && muonEta <= -1.2 )  {return 0.9718;}
    if (muonEta >-1.2 && muonEta <= -0.8 )  {return 0.9700;}
    if (muonEta >-0.8 && muonEta <= 0.0 )   {return 0.9803;}
    if (muonEta > 0.0 && muonEta <= 0.8 )   {return 0.9687;}
    if (muonEta > 0.8 && muonEta <= 1.2 )   {return 0.9732;}
    if (muonEta > 1.2 && muonEta < 2.1 )   {return 0.9731;}
  }else if (muonPt>55. )
  {
    if (muonEta >-2.1 && muonEta <= -1.2 )  {return 0.9412;}
    if (muonEta >-1.2 && muonEta <= -0.8 )  {return 0.9827;}
    if (muonEta >-0.8 && muonEta <= 0.0 )   {return 0.9988;}
    if (muonEta > 0.0 && muonEta <= 0.8 )   {return 0.9851;}
    if (muonEta > 0.8 && muonEta <= 1.2 )   {return 0.9435;}
    if (muonEta > 1.2 && muonEta < 2.1 )   {return 0.9206;}
  }
}

Int_t WEleQ::FillEleZmassDaughEta(int etaRange1, int etaRange2)
{
//ScaleSmear Electron 21 category Fill
if(AnaChannel=="ElectronLowPU")
{
  if( (etaRange1==0) && (etaRange2==0))
    h1_ZmassDaughEta[0]->Fill(Zmass);
  if((etaRange1==0 && etaRange2==1) || (etaRange1==1 && etaRange2==0))
    h1_ZmassDaughEta[1]->Fill(Zmass);
  if((etaRange1==0 && etaRange2==2) || (etaRange1==2 && etaRange2==0))
    h1_ZmassDaughEta[2]->Fill(Zmass);
  if((etaRange1==0 && etaRange2==3) || (etaRange1==3 && etaRange2==0))
    h1_ZmassDaughEta[3]->Fill(Zmass);
  if((etaRange1==0 && etaRange2==4) || (etaRange1==4 && etaRange2==0))
    h1_ZmassDaughEta[4]->Fill(Zmass);
  if((etaRange1==0 && etaRange2==5) || (etaRange1==5 && etaRange2==0))
    h1_ZmassDaughEta[5]->Fill(Zmass);
  if((etaRange1==1) && (etaRange2==1))
    h1_ZmassDaughEta[6]->Fill(Zmass);
  if((etaRange1==1 && etaRange2==2) || (etaRange1==2 && etaRange2==1))
    h1_ZmassDaughEta[7]->Fill(Zmass);
  if((etaRange1==1 && etaRange2==3) || (etaRange1==3 && etaRange2==1))
    h1_ZmassDaughEta[8]->Fill(Zmass);
  if((etaRange1==1 && etaRange2==4) || (etaRange1==4 && etaRange2==1))
    h1_ZmassDaughEta[9]->Fill(Zmass);
  if((etaRange1==1 && etaRange2==5) || (etaRange1==5 && etaRange2==1))
    h1_ZmassDaughEta[10]->Fill(Zmass);
  if((etaRange1==2) && (etaRange2==2))
    h1_ZmassDaughEta[11]->Fill(Zmass);
  if((etaRange1==2 && etaRange2==3) || (etaRange1==3 && etaRange2==2))
    h1_ZmassDaughEta[12]->Fill(Zmass);
  if((etaRange1==2 && etaRange2==4) || (etaRange1==4 && etaRange2==2))
    h1_ZmassDaughEta[13]->Fill(Zmass);
  if((etaRange1==2 && etaRange2==5) || (etaRange1==5 && etaRange2==2))
    h1_ZmassDaughEta[14]->Fill(Zmass);
  if((etaRange1==3) && (etaRange2==3))
    h1_ZmassDaughEta[15]->Fill(Zmass);
  if((etaRange1==3 && etaRange2==4) ||( etaRange1==4 && etaRange2==3))
    h1_ZmassDaughEta[16]->Fill(Zmass);
  if((etaRange1==3 && etaRange2==5) || ( etaRange1==5 && etaRange2==3))
    h1_ZmassDaughEta[17]->Fill(Zmass);
  if((etaRange1==4 && etaRange2==4))
    h1_ZmassDaughEta[18]->Fill(Zmass);
  if((etaRange1==4 && etaRange2==5) || (etaRange1==5 && etaRange2==4))
    h1_ZmassDaughEta[19]->Fill(Zmass);
  if((etaRange1==5 && etaRange2==5))
    h1_ZmassDaughEta[15]->Fill(Zmass);
}
//ScaleSmear Electron 66 category Fill
if(AnaChannel=="ElectronHighPU")
{
  if( (etaRange1==0) && (etaRange2==0))
    h1_ZmassDaughEta[0]->Fill(Zmass);
  if((etaRange1==0 && etaRange2==1) || (etaRange1==1 && etaRange2==0))
    h1_ZmassDaughEta[1]->Fill(Zmass);
  if((etaRange1==0 && etaRange2==2) || (etaRange1==2 && etaRange2==0))
    h1_ZmassDaughEta[2]->Fill(Zmass);
  if((etaRange1==0 && etaRange2==3) || (etaRange1==3 && etaRange2==0))
    h1_ZmassDaughEta[3]->Fill(Zmass);
  if((etaRange1==0 && etaRange2==4) || (etaRange1==4 && etaRange2==0))
    h1_ZmassDaughEta[4]->Fill(Zmass);
  if((etaRange1==0 && etaRange2==5) || (etaRange1==5 && etaRange2==0))
    h1_ZmassDaughEta[5]->Fill(Zmass);
  if((etaRange1==0 && etaRange2==6) || (etaRange1==6 && etaRange2==0))
    h1_ZmassDaughEta[6]->Fill(Zmass);
  if((etaRange1==0 && etaRange2==7) || (etaRange1==7 && etaRange2==0))
    h1_ZmassDaughEta[7]->Fill(Zmass);
  if((etaRange1==0 && etaRange2==8) || (etaRange1==8 && etaRange2==0))
    h1_ZmassDaughEta[8]->Fill(Zmass);
  if((etaRange1==0 && etaRange2==9) || (etaRange1==9 && etaRange2==0))
    h1_ZmassDaughEta[9]->Fill(Zmass);
  if((etaRange1==0 && etaRange2==10) || (etaRange1==10 && etaRange2==0))
    h1_ZmassDaughEta[10]->Fill(Zmass);


  if((etaRange1==1) && (etaRange2==1))
    h1_ZmassDaughEta[11]->Fill(Zmass);
  if((etaRange1==1 && etaRange2==2) || (etaRange1==2 && etaRange2==1))
    h1_ZmassDaughEta[12]->Fill(Zmass);
  if((etaRange1==1 && etaRange2==3) || (etaRange1==3 && etaRange2==1))
    h1_ZmassDaughEta[13]->Fill(Zmass);
  if((etaRange1==1 && etaRange2==4) || (etaRange1==4 && etaRange2==1))
    h1_ZmassDaughEta[14]->Fill(Zmass);
  if((etaRange1==1 && etaRange2==5) || (etaRange1==5 && etaRange2==1))
    h1_ZmassDaughEta[15]->Fill(Zmass);
  if((etaRange1==1 && etaRange2==6) || (etaRange1==6 && etaRange2==1))
    h1_ZmassDaughEta[16]->Fill(Zmass);
  if((etaRange1==1 && etaRange2==7) || (etaRange1==7 && etaRange2==1))
    h1_ZmassDaughEta[17]->Fill(Zmass);
  if((etaRange1==1 && etaRange2==8) || (etaRange1==8 && etaRange2==1))
    h1_ZmassDaughEta[18]->Fill(Zmass);
  if((etaRange1==1 && etaRange2==9) || (etaRange1==9 && etaRange2==1))
    h1_ZmassDaughEta[19]->Fill(Zmass);
  if((etaRange1==1 && etaRange2==10) || (etaRange1==10 && etaRange2==1))
    h1_ZmassDaughEta[20]->Fill(Zmass);

  if((etaRange1==2) && (etaRange2==2))
    h1_ZmassDaughEta[21]->Fill(Zmass);
  if((etaRange1==2 && etaRange2==3) || (etaRange1==3 && etaRange2==2))
    h1_ZmassDaughEta[22]->Fill(Zmass);
  if((etaRange1==2 && etaRange2==4) || (etaRange1==4 && etaRange2==2))
    h1_ZmassDaughEta[23]->Fill(Zmass);
  if((etaRange1==2 && etaRange2==5) || (etaRange1==5 && etaRange2==2))
    h1_ZmassDaughEta[24]->Fill(Zmass);
  if((etaRange1==2 && etaRange2==6) || (etaRange1==6 && etaRange2==2))
    h1_ZmassDaughEta[25]->Fill(Zmass);
  if((etaRange1==2 && etaRange2==7) || (etaRange1==7 && etaRange2==2))
    h1_ZmassDaughEta[26]->Fill(Zmass);
  if((etaRange1==2 && etaRange2==8) || (etaRange1==8 && etaRange2==2))
    h1_ZmassDaughEta[27]->Fill(Zmass);
  if((etaRange1==2 && etaRange2==9) || (etaRange1==9 && etaRange2==2))
    h1_ZmassDaughEta[28]->Fill(Zmass);
  if((etaRange1==2 && etaRange2==10) || (etaRange1==10 && etaRange2==2))
    h1_ZmassDaughEta[29]->Fill(Zmass);


  if((etaRange1==3) && (etaRange2==3))
    h1_ZmassDaughEta[30]->Fill(Zmass);
  if((etaRange1==3 && etaRange2==4) ||( etaRange1==4 && etaRange2==3))
    h1_ZmassDaughEta[31]->Fill(Zmass);
  if((etaRange1==3 && etaRange2==5) || ( etaRange1==5 && etaRange2==3))
    h1_ZmassDaughEta[32]->Fill(Zmass);
  if((etaRange1==3 && etaRange2==6) || ( etaRange1==6 && etaRange2==3))
    h1_ZmassDaughEta[33]->Fill(Zmass);
  if((etaRange1==3 && etaRange2==7) || ( etaRange1==7 && etaRange2==3))
    h1_ZmassDaughEta[34]->Fill(Zmass);
  if((etaRange1==3 && etaRange2==8) || ( etaRange1==8 && etaRange2==3))
    h1_ZmassDaughEta[35]->Fill(Zmass);
  if((etaRange1==3 && etaRange2==9) || ( etaRange1==9 && etaRange2==3))
    h1_ZmassDaughEta[36]->Fill(Zmass);
  if((etaRange1==3 && etaRange2==10) || ( etaRange1==10 && etaRange2==3))
    h1_ZmassDaughEta[37]->Fill(Zmass);


  if((etaRange1==4 && etaRange2==4))
    h1_ZmassDaughEta[38]->Fill(Zmass);
  if((etaRange1==4 && etaRange2==5) || (etaRange1==5 && etaRange2==4))
    h1_ZmassDaughEta[39]->Fill(Zmass);
  if((etaRange1==4 && etaRange2==6) || (etaRange1==6 && etaRange2==4))
    h1_ZmassDaughEta[40]->Fill(Zmass);
  if((etaRange1==4 && etaRange2==7) || (etaRange1==7 && etaRange2==4))
    h1_ZmassDaughEta[41]->Fill(Zmass);
  if((etaRange1==4 && etaRange2==8) || (etaRange1==8 && etaRange2==4))
    h1_ZmassDaughEta[42]->Fill(Zmass);
  if((etaRange1==4 && etaRange2==9) || (etaRange1==9 && etaRange2==4))
    h1_ZmassDaughEta[43]->Fill(Zmass);
  if((etaRange1==4 && etaRange2==10) || (etaRange1==10 && etaRange2==4))
    h1_ZmassDaughEta[44]->Fill(Zmass);


  if((etaRange1==5 && etaRange2==5))
    h1_ZmassDaughEta[45]->Fill(Zmass);	
  if((etaRange1==5 && etaRange2==6) || (etaRange1==6 && etaRange2==6))
    h1_ZmassDaughEta[46]->Fill(Zmass);	
  if((etaRange1==5 && etaRange2==7) || (etaRange1==7 && etaRange2==6))
    h1_ZmassDaughEta[47]->Fill(Zmass);	
  if((etaRange1==5 && etaRange2==8) || (etaRange1==8 && etaRange2==6))
    h1_ZmassDaughEta[48]->Fill(Zmass);	
  if((etaRange1==5 && etaRange2==9) || (etaRange1==9 && etaRange2==6))
    h1_ZmassDaughEta[49]->Fill(Zmass);	
  if((etaRange1==5 && etaRange2==10) || (etaRange1==10 && etaRange2==6))
    h1_ZmassDaughEta[50]->Fill(Zmass);	

  if((etaRange1==6 && etaRange2==6))
    h1_ZmassDaughEta[51]->Fill(Zmass);	
  if((etaRange1==6 && etaRange2==7) || (etaRange1==7 && etaRange2==6))
    h1_ZmassDaughEta[52]->Fill(Zmass);	
  if((etaRange1==6 && etaRange2==8) || (etaRange1==8 && etaRange2==6))
    h1_ZmassDaughEta[53]->Fill(Zmass);	
  if((etaRange1==6 && etaRange2==9) || (etaRange1==9 && etaRange2==6))
    h1_ZmassDaughEta[54]->Fill(Zmass);	
  if((etaRange1==6 && etaRange2==10) || (etaRange1==10 && etaRange2==6))
    h1_ZmassDaughEta[55]->Fill(Zmass);	

  if((etaRange1==7 && etaRange2==7))
    h1_ZmassDaughEta[56]->Fill(Zmass);	
  if((etaRange1==7 && etaRange2==8) || (etaRange1==8 && etaRange2==7))
    h1_ZmassDaughEta[57]->Fill(Zmass);	
  if((etaRange1==7 && etaRange2==9) || (etaRange1==9 && etaRange2==7))
    h1_ZmassDaughEta[58]->Fill(Zmass);	
  if((etaRange1==7 && etaRange2==10) || (etaRange1==10 && etaRange2==7))
    h1_ZmassDaughEta[59]->Fill(Zmass);	

  if((etaRange1==8 && etaRange2==8))
    h1_ZmassDaughEta[60]->Fill(Zmass);	
  if((etaRange1==8 && etaRange2==9) || (etaRange1==9 && etaRange2==8))
    h1_ZmassDaughEta[61]->Fill(Zmass);	
  if((etaRange1==8 && etaRange2==10) || (etaRange1==10 && etaRange2==8))
    h1_ZmassDaughEta[62]->Fill(Zmass);	

  if((etaRange1==9 && etaRange2==9))
    h1_ZmassDaughEta[63]->Fill(Zmass);	
  if((etaRange1==9 && etaRange2==10) || (etaRange1==10 && etaRange2==9))
    h1_ZmassDaughEta[64]->Fill(Zmass);	

  if((etaRange1==10 && etaRange2==10))
    h1_ZmassDaughEta[65]->Fill(Zmass);	
}
}

//ScaleSmear Muon 15 category Fill

Int_t WEleQ::FillMuZmassDaughEta(int etaRange1, int etaRange2)
{
  if((etaRange1==0) && (etaRange2==0))
    h1_ZmassDaughEtaMu[0]->Fill(Zmass);
  if((etaRange1==0 && etaRange2==1) || (etaRange1==1 && etaRange2==0))
    h1_ZmassDaughEtaMu[1]->Fill(Zmass);
  if((etaRange1==0 && etaRange2==2) || (etaRange1==2 && etaRange2==0))
    h1_ZmassDaughEtaMu[2]->Fill(Zmass);
  if((etaRange1==0 && etaRange2==3) || (etaRange1==3 && etaRange2==0))
    h1_ZmassDaughEtaMu[3]->Fill(Zmass);
  if((etaRange1==0 && etaRange2==4) || (etaRange1==4 && etaRange2==0))
    h1_ZmassDaughEtaMu[4]->Fill(Zmass);
  if((etaRange1==1) && (etaRange2==1))
    h1_ZmassDaughEtaMu[5]->Fill(Zmass);
  if((etaRange1==1 && etaRange2==2) || (etaRange1==2 && etaRange2==1))
    h1_ZmassDaughEtaMu[6]->Fill(Zmass);
  if((etaRange1==1 && etaRange2==3) || (etaRange1==3 && etaRange2==1))
    h1_ZmassDaughEtaMu[7]->Fill(Zmass);
  if((etaRange1==1 && etaRange2==4) || (etaRange1==4 && etaRange2==1))
    h1_ZmassDaughEtaMu[8]->Fill(Zmass);
  if((etaRange1==2) && (etaRange2==2))
    h1_ZmassDaughEtaMu[9]->Fill(Zmass);
  if((etaRange1==2 && etaRange2==3) || (etaRange1==3 && etaRange2==2))
    h1_ZmassDaughEtaMu[10]->Fill(Zmass);
  if((etaRange1==2 && etaRange2==4) || (etaRange1==4 && etaRange2==2))
    h1_ZmassDaughEtaMu[11]->Fill(Zmass);
  if((etaRange1==3) && (etaRange2==3))
    h1_ZmassDaughEtaMu[12]->Fill(Zmass);
  if((etaRange1==3 && etaRange2==4) || (etaRange1==4 && etaRange2==3))
    h1_ZmassDaughEtaMu[13]->Fill(Zmass);
  if((etaRange1==4) && (etaRange2==4))
    h1_ZmassDaughEtaMu[14]->Fill(Zmass);
}


   /// Scale Smear corrections
   Double_t WEleQ::EleScaleRD(double ele_etaSC)
   {
     if(fabs(ele_etaSC) >= 0.0   && fabs(ele_etaSC) < 0.4) {return 0.999005  ;}
     if(fabs(ele_etaSC) >= 0.4   && fabs(ele_etaSC) < 0.8) {return 1.00363   ;}
     if(fabs(ele_etaSC) >= 0.8   && fabs(ele_etaSC) < 1.2) {return 1.00242   ;}
     if(fabs(ele_etaSC) >= 1.2   && fabs(ele_etaSC) < 1.4442) {return 1.00177 ;}
     if(fabs(ele_etaSC) >= 1.566 && fabs(ele_etaSC) < 2.0) {return 1.00706   ; }
     if(fabs(ele_etaSC) >= 2.0   && fabs(ele_etaSC) < 2.5) {return 0.992945  ; }
   }

   Double_t WEleQ::EleSmearMC(double ele_etaSC)
   {
     if(fabs(ele_etaSC) >= 0.0   && fabs(ele_etaSC) < 0.4) {return 0.0574694   ;}
     if(fabs(ele_etaSC) >= 0.4   && fabs(ele_etaSC) < 0.8) {return 0.0673641   ;}
     if(fabs(ele_etaSC) >= 0.8   && fabs(ele_etaSC) < 1.2) {return 0.0859763   ;}
     if(fabs(ele_etaSC) >= 1.2   && fabs(ele_etaSC) < 1.4442) {return 0.01     ;}
     if(fabs(ele_etaSC) >= 1.566 && fabs(ele_etaSC) < 2.0) {return 0.256612    ;}
     if(fabs(ele_etaSC) >= 2.0   && fabs(ele_etaSC) < 2.5) {return 0.835818    ;}
   }

   Double_t WEleQ::MuonSmearMC(double mu_eta)
   {
     if(fabs(mu_eta) >= 0.0   && fabs(mu_eta) < 0.4) { return 0.00731762   ;}
     if(fabs(mu_eta) >= 0.4   && fabs(mu_eta) < 0.8) { return 0.0967567    ;}
     if(fabs(mu_eta) >= 0.8   && fabs(mu_eta) < 1.2) { return 0.260799     ;}
     if(fabs(mu_eta) >= 1.2   && fabs(mu_eta) < 1.6) { return 0.157717     ;}
     if(fabs(mu_eta) >= 1.6   && fabs(mu_eta) < 2.1) { return 0.134285     ;}
   }


   Int_t WEleQ::MuonCut(int i)
   {
     if( !(*W_Lept1_isGlobal)[i])return -1;
     if((*W_Lept1_pt)[i] < 20) return -1;

     //MC Smear Correction
     if(Mode == "AllCorrectionsMC")
     {
       smearcorr= MuonSmearMC((*W_Lept1_eta)[i]);
       PtEtaPhiMLorentzVector Wmu_4( (*W_Lept1_pt)[i],(*W_Lept1_eta)[i],(*W_Lept1_phi)[i],0.1056);
       corr1 = gRandom->Gaus(Wmu_4.E(), smearcorr)/Wmu_4.E();
       Wmu_4=corr1*Wmu_4;
     }

     if(fabs((*W_Lept1_eta)[i])>2.1) return -1;
     if( (*W_Lept1_globalNormChi2)[i]<0 || (*W_Lept1_globalNormChi2)[i] >= 10) return -1;
     if( (*W_Lept1_muonHits)[i] <1) return -1;
     if( (*W_Lept1_matchStations)[i] <2 ) return -1;
     if( (*W_Lept1_trkLayers)[i] <6 )return -1;
     if( (*W_Lept1_pixelHits)[i] <1 )return -1;
     if( fabs( (*W_Lept1_dB)[i]) >0.02 )return -1;
     if( fabs( (*W_Lept1_dz)[i]) >0.5 )return -1;
     //if( ( (*W_Lept1_nhIso04)[i]+(*W_Lept1_chIso04)[i]+(*W_Lept1_phIso04)[i])/(*W_Lept1_pt)[i] > 0.12) return -1;
     double betaCor04= max(0.0,(*W_Lept1_nhIso04)[i]+(*W_Lept1_phIso04)[i]-0.5*(*W_Lept1_pcIso04)[i]);
     if( ((*W_Lept1_chIso04)[i]+betaCor04)/(*W_Lept1_pt)[i] > 0.12) return -1; //Signal Band   // use this line to get n.of.events in AB area in  ABCD method


     // uncomment next line (Sideband)  to get n.of.events in DC area in  ABCD method
     //  if( ((*W_Lept1_chIso04)[i]+betaCor04)/(*W_Lept1_pt)[i] < 0.3 || ((*W_Lept1_chIso04)[i]+betaCor04)/(*W_Lept1_pt)[i] > 0.5) return -1; //Side Band

     
     
     //if( (*W_Neut_pt)[i] < 14 ) return -1;
     //if( (*W_Mt)[i] < 30 ) return -1;
     //if( (*W_Neut_pt)[i] < 25 ) return -1;
     //if( (*W_Mt)[i] < 40 ) return -1;

     return 1;
   }

   Int_t WEleQ::MuonCutSide(int i)
   {
     if( !(*W_Lept1_isGlobal)[i])return -1;
     if((*W_Lept1_pt)[i] < 20) return -1;

     //MC Smear Correction
     if(Mode == "AllCorrectionsMC")
     {
       smearcorr= MuonSmearMC((*W_Lept1_eta)[i]);
       PtEtaPhiMLorentzVector Wmu_4( (*W_Lept1_pt)[i],(*W_Lept1_eta)[i],(*W_Lept1_phi)[i],0.1056);
       corr1 = gRandom->Gaus(Wmu_4.E(), smearcorr)/Wmu_4.E();
       Wmu_4=corr1*Wmu_4;
     }
     
     if(fabs((*W_Lept1_eta)[i])>2.1) return -1;
     if( (*W_Lept1_globalNormChi2)[i]<0 || (*W_Lept1_globalNormChi2)[i] >= 10) return -1;
     if( (*W_Lept1_muonHits)[i] <1) return -1;
     if( (*W_Lept1_matchStations)[i] <2 ) return -1;
     if( (*W_Lept1_trkLayers)[i] <6 )return -1;
     if( (*W_Lept1_pixelHits)[i] <1 )return -1;
     if( fabs( (*W_Lept1_dB)[i]) >0.02 )return -1;
     if( fabs( (*W_Lept1_dz)[i]) >0.5 )return -1;
     double betaCor04= max(0.0,(*W_Lept1_nhIso04)[i]+(*W_Lept1_phIso04)[i]-0.5*(*W_Lept1_pcIso04)[i]);
     if( ((*W_Lept1_chIso04)[i]+betaCor04)/(*W_Lept1_pt)[i] < 0.3 || ((*W_Lept1_chIso04)[i]+betaCor04)/(*W_Lept1_pt)[i] > 0.5) return -1; //Side Band

     return 1;
   }

   Int_t WEleQ::AddMuonCut(int i)
   {
     if( !(*W_Lept1_isTrker)[i] || !(*W_Lept1_isGlobal)[i]) return -1; //Signal Band only. For Side Band comment this line.
     if((*W_Lept1_pt)[i] <= 10) return -1;

     //MC Smear Correction
     if(Mode == "AllCorrectionsMC")
     {
       smearcorr= MuonSmearMC((*W_Lept1_eta)[i]);
       PtEtaPhiMLorentzVector Wmu_4( (*W_Lept1_pt)[i],(*W_Lept1_eta)[i],(*W_Lept1_phi)[i],0.1056);
       corr1 = gRandom->Gaus(Wmu_4.E(), smearcorr)/Wmu_4.E();
       Wmu_4=corr1*Wmu_4;
     }

     if(fabs((*W_Lept1_eta)[i])>=2.4) return -1;
     double betaCor04= max(0.0,(*W_Lept1_nhIso04)[i]+(*W_Lept1_phIso04)[i]-0.5*(*W_Lept1_pcIso04)[i]);
     if( ((*W_Lept1_chIso04)[i]+betaCor04)/(*W_Lept1_pt)[i] > 0.20) return -1;
     return 1;
   }

   Int_t WEleQ::ElectronCut(int i)
   {
     //RD Scale Correction
     if(Mode == "AllCorrectionsRD")
     {
       scalecorr=EleScaleRD((*W_Lept1_etaSC)[i]);
       (*W_Lept1_pt)[i]= scalecorr*(*W_Lept1_pt)[i];
       PtEtaPhiMLorentzVector WeleRD_4( (*W_Lept1_pt)[i],(*W_Lept1_etaSC)[i],(*W_Lept1_phi)[i],0.000511);
       if(fabs( (*W_Lept1_pt)[i]) < 25) return -1;
     }else{
       if((*W_Lept1_pt)[i] < 25) return -1;
     }

     //MC Smear Correction
     if(Mode == "AllCorrectionsMC")
     {
       if((*W_Lept1_pt)[i] < 25) return -1;
       smearcorr=EleSmearMC((*W_Lept1_etaSC)[i]);
       PtEtaPhiMLorentzVector WeleMC_4( (*W_Lept1_pt)[i],(*W_Lept1_etaSC)[i],(*W_Lept1_phi)[i],0.000511);
       corr1 = gRandom->Gaus(WeleMC_4.E(), smearcorr)/WeleMC_4.E();
       WeleMC_4=corr1*WeleMC_4;
     }else{
       if((*W_Lept1_pt)[i] < 25) return -1;
     }

     
     if(fabs((*W_Lept1_etaSC)[i])>2.5) return -1;
     //W/Z
     if(fabs((*W_Lept1_etaSC)[i])>1.4442 && fabs((*W_Lept1_etaSC)[i])<1.566)return -1;
     //if(fabs((*W_Lept1_etaSC)[i])>1.47 && fabs((*W_Lept1_etaSC)[i])<1.566)return -1;
     
     if( fabs( (*W_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*W_Lept1_etaSC)[i]) < 1.47)
     {
	 if( (*W_Lept1_sigmaIEtaIEta)[i] > 0.01 ) return -1; // use this line to get n.of.events in AB area in  ABCD method
	 //if( (*W_Lept1_sigmaIEtaIEta)[i] > 0.01 ) return -1; // use this line to get n.of.events in DC area in  ABCD method
     } else{
	 if( (*W_Lept1_sigmaIEtaIEta)[i] > 0.03 ) return -1;   // use this line to get n.of.events in AB area in  ABCD method
	 //if( (*W_Lept1_sigmaIEtaIEta)[i] > 0.03 ) return -1; // use this line to get n.of.events in DC area in  ABCD method
     }

     if( fabs( (*W_Lept1_etaSC)[i]) < 1.4442)
         //if( fabs( (*W_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs((*W_Lept1_dEtaIn)[i]) >  0.004 ) return -1;
     } else{
	 if( fabs((*W_Lept1_dEtaIn)[i])  >   0.007 ) return -1;
     }
     
     if( fabs( (*W_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*W_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs((*W_Lept1_dPhiIn)[i])  > 0.06 ) return -1;
     } else{
	 if( fabs((*W_Lept1_dPhiIn)[i])  > 0.03 ) return -1;
     }

     if( fabs( (*W_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*W_Lept1_etaSC)[i]) < 1.47)
     {
	 if( (*W_Lept1_HoverE)[i] > 0.12 ) return -1;
     } else{
	 if( (*W_Lept1_HoverE)[i] > 0.10 ) return -1;
     }

     if( fabs( (*W_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*W_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs((*W_Lept1_dxy)[i]) > 0.02 ) return -1;
     } else{
	 if( fabs((*W_Lept1_dxy)[i]) > 0.02 ) return -1;
     }

     if( fabs( (*W_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*W_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs((*W_Lept1_dz)[i]) > 0.1 ) return -1;
     } else{
	 if( fabs((*W_Lept1_dz)[i]) > 0.1 ) return -1;
     }
     if( fabs( (*W_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*W_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs((*W_Lept1_InvEminusInvP)[i]) > 0.05 ) return -1;
     }else{
	 if( fabs((*W_Lept1_InvEminusInvP)[i]) > 0.05) return -1;
     }

     if( fabs( (*W_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*W_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs((*W_Lept1_mHits)[i]) > 1 ) return -1;
     } else{
	 if( fabs((*W_Lept1_mHits)[i]) > 1) return -1;
     }
 
     if( (*W_Lept1_hasConversion)[i] ) return -1;
     if( (*W_Lept1_relIsoRho03)[i] > 0.15 ) return -1;

     //       if( (*W_Neut_pt)[i] < 25 ) return -1;
     //          if( (*W_Mt)[i] < 40 ) return -1;
     return 1;
   }

   Int_t WEleQ::ElectronCutHighPUToTal(int i)
   {
     if((*W_Lept1_pt)[i] < 35) return -1;
     if(fabs((*W_Lept1_etaSC)[i])>2.5) return -1;
     if(fabs((*W_Lept1_etaSC)[i])>1.4442 && fabs((*W_Lept1_etaSC)[i])<1.566)return -1;
     if( fabs( (*W_Lept1_etaSC)[i]) < 1.4442)
     {
       if( (*W_Lept1_sigmaIEtaIEta)[i] > 0.01 ) return -1;
       if( fabs((*W_Lept1_dEtaIn)[i]) == 0.004 ) return -1;
       if( fabs((*W_Lept1_dPhiIn)[i]) == 0.06 ) return -1;
       if( (*W_Lept1_HoverE)[i] > 0.12 ) return -1;
       if( fabs((*W_Lept1_dxy)[i]) > 0.02 ) return -1;
       if( fabs((*W_Lept1_dz)[i]) > 0.1 ) return -1;
       if( fabs((*W_Lept1_InvEminusInvP)[i]) > 0.05 ) return -1;
       if( fabs((*W_Lept1_mHits)[i]) > 1) return -1;
     } else{
       if( (*W_Lept1_sigmaIEtaIEta)[i] > 0.03 ) return -1;
       if( fabs((*W_Lept1_dEtaIn)[i])  == 0.007 ) return -1;
       if( fabs((*W_Lept1_dPhiIn)[i])  == 0.03 ) return -1;
       if( (*W_Lept1_HoverE)[i] > 0.1 ) return -1;
       if( fabs((*W_Lept1_dxy)[i]) > 0.02 ) return -1;
       if( fabs((*W_Lept1_dz)[i]) > 0.1 ) return -1;
       if( fabs((*W_Lept1_InvEminusInvP)[i]) > 0.05) return -1;
       if( fabs((*W_Lept1_mHits)[i]) > 1) return -1;
     }

       if( (*W_Lept1_hasConversion)[i] ) return -1;
       if( (*W_Lept1_relIsoRho03)[i] > 0.15 ) return -1;

       return 1;
   }

   Int_t WEleQ::ElectronCutHighPU(int i)
   {
     //////////////  Ele   V5 =======================================
     //double RelComIsoEB = (*W_Lept1_RelisolPtTrks03)[i]+max(0.,((*W_Lept1_RelisoEm03)[i]*(*W_Lept1_pt)[i])-1.)+(*W_Lept1_RelisoHad03)[i];
     //double RelComIsoEE = (*W_Lept1_RelisolPtTrks03)[i]+(*W_Lept1_RelisoEm03)[i]+(*W_Lept1_RelisoHad03)[i];
     if((*W_Lept1_pt)[i] < 35) return -1;
     //if((*W_Lept1_pt)[i] < 30 || (*W_Lept1_pt)[i] > 35) return -1;
     if(fabs((*W_Lept1_etaSC)[i])>2.5) return -1;
     //W/Z
     if(fabs((*W_Lept1_etaSC)[i])>1.4442 && fabs((*W_Lept1_etaSC)[i])<1.566)return -1;

     if( fabs( (*W_Lept1_etaSC)[i]) < 1.4442)
     {
       if( (*W_Lept1_sigmaIEtaIEta)[i] > 0.01 ) return -1;
       if( fabs((*W_Lept1_dEtaIn)[i]) >  0.004 ) return -1;
       if( fabs((*W_Lept1_dPhiIn)[i])  > 0.06 ) return -1;
       if( (*W_Lept1_HoverE)[i] > 0.12 ) return -1;
       if( fabs((*W_Lept1_dxy)[i]) > 0.02 ) return -1;
       if( fabs((*W_Lept1_dz)[i]) > 0.1 ) return -1;
       if( fabs((*W_Lept1_InvEminusInvP)[i]) > 0.05 ) return -1;
       //if( fabs((*W_Lept1_mHits)[i]) > 1) return -1;
       if( fabs((*W_Lept1_mHits)[i]) > 1) return -1;

       //# Detector based Isolation. for WP80 Variable 
       //if(RelComIsoEB>0.07) return -1;
       //if((*W_Lept1_RelisolPtTrks03)[i] > 0.05) return -1;
       //if((*W_Lept1_RelisoEm03)[i] > 0.15) return -1;
       //if((*W_Lept1_RelisoHad03)[i] > 0.10) return -1; 

     } else{ 
	 if( (*W_Lept1_sigmaIEtaIEta)[i] > 0.03 ) return -1;
	 if( fabs((*W_Lept1_dEtaIn)[i])  >   0.007 ) return -1;
	 if( fabs((*W_Lept1_dPhiIn)[i])  > 0.03 ) return -1;
	 if( (*W_Lept1_HoverE)[i] > 0.1 ) return -1;
	 if( fabs((*W_Lept1_dxy)[i]) > 0.02 ) return -1;
	 if( fabs((*W_Lept1_dz)[i]) > 0.1 ) return -1;
	 if( fabs((*W_Lept1_InvEminusInvP)[i]) > 0.05) return -1;
	 //if( fabs((*W_Lept1_mHits)[i]) > 1) return -1;
	 if( fabs((*W_Lept1_mHits)[i]) > 1) return -1;

	 //# Detector based Isolation. for WP80 Variable if(RelComIsoEE>0.06)
	 //return -1;
         //if((*W_Lept1_RelisolPtTrks03)[i] > 0.05) return -1;
         //if((*W_Lept1_RelisoEm03)[i] > 0.1) return -1;
         //if((*W_Lept1_RelisoHad03)[i] > 0.1) return -1;
     }

     if( (*W_Lept1_hasConversion)[i] ) return -1;
     if( (*W_Lept1_relIsoRho03)[i] > 0.15 ) return -1;

     return 1;
   }


   Int_t WEleQ::ElectronCutSide(int i)
   {
     //RD Scale Correction
     if(Mode == "AllCorrectionsRD")
     {
       scalecorr=EleScaleRD((*W_Lept1_etaSC)[i]);
       (*W_Lept1_pt)[i]= scalecorr*(*W_Lept1_pt)[i];
       PtEtaPhiMLorentzVector WeleRD_4( (*W_Lept1_pt)[i],(*W_Lept1_etaSC)[i],(*W_Lept1_phi)[i],0.000511);
       if(fabs( (*W_Lept1_pt)[i]) < 25) return -1;
     }else{
       if((*W_Lept1_pt)[i] < 25) return -1;
     }

     //MC Smear Correction
     if(Mode == "AllCorrectionsMC")
     {
       if((*W_Lept1_pt)[i] < 25) return -1;
       smearcorr=EleSmearMC((*W_Lept1_etaSC)[i]);
       PtEtaPhiMLorentzVector WeleMC_4( (*W_Lept1_pt)[i],(*W_Lept1_etaSC)[i],(*W_Lept1_phi)[i],0.000511);
       corr1 = gRandom->Gaus(WeleMC_4.E(), smearcorr)/WeleMC_4.E();
       WeleMC_4=corr1*WeleMC_4;
     }else{
       if((*W_Lept1_pt)[i] < 25) return -1;
     }


     if(fabs((*W_Lept1_etaSC)[i])>2.5) return -1;
     if(fabs((*W_Lept1_etaSC)[i])>1.4442 && fabs((*W_Lept1_etaSC)[i]) < 1.566) return -1;
     //if(fabs((*W_Lept1_etaSC)[i])>1.47 && fabs((*W_Lept1_etaSC)[i]) < 1.566) return -1;

     if( fabs( (*W_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*W_Lept1_etaSC)[i]) < 1.47)
     {
	 if( (*W_Lept1_sigmaIEtaIEta)[i] > 0.01 ) return -1;
     } else{
	 if( (*W_Lept1_sigmaIEtaIEta)[i] > 0.03 ) return -1;
     }

     if( fabs( (*W_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*W_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs((*W_Lept1_dEtaIn)[i]) <  0.004 ) return -1;
     } else{
	 if( fabs((*W_Lept1_dEtaIn)[i])  <   0.007 ) return -1;
     }

     if( fabs( (*W_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*W_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs((*W_Lept1_dPhiIn)[i])  < 0.06 ) return -1;
     } else {
	 if( fabs((*W_Lept1_dPhiIn)[i])  < 0.03 ) return -1;
     }

     if( fabs( (*W_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*W_Lept1_etaSC)[i]) < 1.47)
     {
	 if( (*W_Lept1_HoverE)[i] > 0.12 ) return -1;
     } else {
	 if( (*W_Lept1_HoverE)[i] > 0.10 ) return -1;
     }

     if( fabs( (*W_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*W_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs((*W_Lept1_dxy)[i]) > 0.02 ) return -1;
     } else {
	 if( fabs((*W_Lept1_dxy)[i]) > 0.02 ) return -1;
     }

     if( fabs( (*W_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*W_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs((*W_Lept1_dz)[i]) > 0.1 ) return -1;
     } else{
	 if( fabs((*W_Lept1_dz)[i]) > 0.1 ) return -1;
     }

     if( fabs( (*W_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*W_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs((*W_Lept1_InvEminusInvP)[i]) > 0.05 ) return -1;
     } else{
	 if( fabs((*W_Lept1_InvEminusInvP)[i]) > 0.05) return -1;
     }

     if( fabs( (*W_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*W_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs((*W_Lept1_mHits)[i]) > 1 ) return -1;
     } else{
	 if( fabs((*W_Lept1_mHits)[i]) > 1) return -1;
     }

     if( (*W_Lept1_hasConversion)[i] ) return -1;
     if( (*W_Lept1_relIsoRho03)[i] > 0.15 ) return -1;

     //       if( (*W_Neut_pt)[i] < 25 ) return -1;
     //          if( (*W_Mt)[i] < 40 ) return -1;
     return 1;
   }

   Int_t WEleQ::ElectronCutSideHighPU(int i)
   {
     //double RelComIsoEB = (*W_Lept1_RelisolPtTrks03)[i]+max(0.,((*W_Lept1_RelisoEm03)[i]*(*W_Lept1_pt)[i])-1.)+(*W_Lept1_RelisoHad03)[i];
    // double RelComIsoEE = (*W_Lept1_RelisolPtTrks03)[i]+(*W_Lept1_RelisoEm03)[i]+(*W_Lept1_RelisoHad03)[i]; 
    if((*W_Lept1_pt)[i] < 35) return -1;
    //if((*W_Lept1_pt)[i] < 30 || (*W_Lept1_pt)[i] > 35) return -1;
     
     if(fabs((*W_Lept1_etaSC)[i])>2.5) return -1;
     if(fabs((*W_Lept1_etaSC)[i])>1.4442 && fabs((*W_Lept1_etaSC)[i]) < 1.566) return -1;

     if( fabs( (*W_Lept1_etaSC)[i]) < 1.4442)
     {
	 if( (*W_Lept1_sigmaIEtaIEta)[i] > 0.01 ) return -1;
	 if( fabs((*W_Lept1_dEtaIn)[i]) <  0.004 ) return -1;
	 if( fabs((*W_Lept1_dPhiIn)[i])  < 0.06 ) return -1;
	 if( (*W_Lept1_HoverE)[i] > 0.12 ) return -1;
	 if( fabs((*W_Lept1_dxy)[i]) > 0.02 ) return -1;
	 if( fabs((*W_Lept1_dz)[i]) > 0.1 ) return -1;
	 if( fabs((*W_Lept1_InvEminusInvP)[i]) > 0.05 ) return -1;
	 if( fabs((*W_Lept1_mHits)[i]) > 1 ) return -1;
         //if(RelComIsoEB<0.07) return -1;
         //if((*W_Lept1_RelisolPtTrks03)[i] < 0.09) return -1;
         //if((*W_Lept1_RelisoEm03)[i] < 0.07) return -1;
         //if((*W_Lept1_RelisoHad03)[i] < 0.10) return -1;

     } else{
	 if( (*W_Lept1_sigmaIEtaIEta)[i] > 0.03 ) return -1;
	 if( fabs((*W_Lept1_dEtaIn)[i])  <   0.007 ) return -1;
	 if( fabs((*W_Lept1_dPhiIn)[i])  < 0.03 ) return -1;
	 if( (*W_Lept1_HoverE)[i] > 0.10 ) return -1;
	 if( fabs((*W_Lept1_dxy)[i]) > 0.02 ) return -1;
	 if( fabs((*W_Lept1_dz)[i]) > 0.1 ) return -1;
	 if( fabs((*W_Lept1_InvEminusInvP)[i]) > 0.05) return -1;
	 if( fabs((*W_Lept1_mHits)[i]) > 1 ) return -1;
         //if(RelComIsoEE<0.06) return -1;
         //if((*W_Lept1_RelisolPtTrks03)[i] < 0.04) return -1;
         //if((*W_Lept1_RelisoEm03)[i] < 0.05) return -1;
         //if((*W_Lept1_RelisoHad03)[i] < 0.025) return -1;
     }

     if( (*W_Lept1_hasConversion)[i] ) return -1;
     if( (*W_Lept1_relIsoRho03)[i] > 0.15 ) return -1;

     return 1;
   }


   Int_t WEleQ::AddElectronCut(int i)
   {
     
     //RD Scale Correction
     if(Mode == "AllCorrectionsRD")
     {
       scalecorr=EleScaleRD((*W_Lept1_etaSC)[i]);
       (*W_Lept1_pt)[i]= scalecorr*(*W_Lept1_pt)[i];
       PtEtaPhiMLorentzVector WeleRD_4( (*W_Lept1_pt)[i],(*W_Lept1_etaSC)[i],(*W_Lept1_phi)[i],0.000511);
       if(fabs( (*W_Lept1_pt)[i]) < 20) return -1;
     }else{
       if((*W_Lept1_pt)[i] < 20) return -1;
     }

     //MC Smear Correction
     if(Mode == "AllCorrectionsMC")
     {
       if((*W_Lept1_pt)[i] < 20) return -1;
       smearcorr=EleSmearMC((*W_Lept1_etaSC)[i]);
       PtEtaPhiMLorentzVector WeleMC_4( (*W_Lept1_pt)[i],(*W_Lept1_etaSC)[i],(*W_Lept1_phi)[i],0.000511);
       corr1 = gRandom->Gaus(WeleMC_4.E(), smearcorr)/WeleMC_4.E();
       WeleMC_4=corr1*WeleMC_4;
     }else{
       if((*W_Lept1_pt)[i] < 20) return -1;
     }

     if(fabs((*W_Lept1_etaSC)[i])>2.5) return -1;
     if(fabs((*W_Lept1_etaSC)[i])>1.4442 && fabs((*W_Lept1_etaSC)[i]) < 1.566) return -1;
     //if(fabs((*W_Lept1_etaSC)[i])>1.47 && fabs((*W_Lept1_etaSC)[i]) < 1.566) return -1;

     if( fabs( (*W_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*W_Lept1_etaSC)[i]) < 1.47)
     {
	 if( (*W_Lept1_sigmaIEtaIEta)[i] > 0.01 ) return -1;
     } else{
	 if( (*W_Lept1_sigmaIEtaIEta)[i] > 0.03 ) return -1;
     }

     if( fabs( (*W_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*W_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs ((*W_Lept1_dEtaIn)[i]) > 0.007 ) return -1;
     } else{
	 if( fabs((*W_Lept1_dEtaIn)[i]) > 0.01 ) return -1;
     }

     if( fabs( (*W_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*W_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs ((*W_Lept1_dPhiIn)[i]) > 0.8 ) return -1;
     } else {
	 if( fabs( (*W_Lept1_dPhiIn)[i]) > 0.7 ) return -1;
     }

     if( fabs( (*W_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*W_Lept1_etaSC)[i]) < 1.47)
     {
	 if( (*W_Lept1_HoverE)[i] > 0.15 ) return -1;
     } //else {
	// if( (*W_Lept1_HoverE)[i] > 0.10 ) return -1;
       //}

     if( fabs( (*W_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*W_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs((*W_Lept1_dxy)[i]) > 0.04 ) return -1;
     } else {
	 if( fabs((*W_Lept1_dxy)[i]) > 0.04 ) return -1;
     }

     if( fabs( (*W_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*W_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs((*W_Lept1_dz)[i]) > 0.2 ) return -1;
     } else{
	 if( fabs((*W_Lept1_dz)[i]) > 0.2 ) return -1;
     }
     
     if( (*W_Lept1_relIsoRho03)[i] > 0.15 ) return -1;

     return 1;
   }


   Int_t WEleQ::AddElectronCutHighPU(int i)
   {

     if((*W_Lept1_pt)[i] < 20) return -1;
     if(fabs((*W_Lept1_etaSC)[i])>2.5) return -1;
     if(fabs((*W_Lept1_etaSC)[i])>1.4442 && fabs((*W_Lept1_etaSC)[i]) < 1.566) return -1;
     
     if( fabs( (*W_Lept1_etaSC)[i]) < 1.4442)
     {
	 if( (*W_Lept1_sigmaIEtaIEta)[i] > 0.01 ) return -1;
	 if( fabs ((*W_Lept1_dEtaIn)[i]) > 0.007 ) return -1;
	 if( fabs ((*W_Lept1_dPhiIn)[i]) > 0.8 ) return -1;
	 if( (*W_Lept1_HoverE)[i] > 0.15 ) return -1;
	 if( fabs((*W_Lept1_dxy)[i]) > 0.04 ) return -1;
	 if( fabs((*W_Lept1_dz)[i]) > 0.2 ) return -1;
     } else{
	 if( (*W_Lept1_sigmaIEtaIEta)[i] > 0.03 ) return -1;
	 if( fabs((*W_Lept1_dEtaIn)[i]) > 0.01 ) return -1;
	 if( fabs( (*W_Lept1_dPhiIn)[i]) > 0.7 ) return -1;
       //          if( (*W_Lept1_HoverE)[i] > 0.10 ) return -1;
	 if( fabs((*W_Lept1_dxy)[i]) > 0.04 ) return -1;
	 if( fabs((*W_Lept1_dz)[i]) > 0.2 ) return -1;
     }

     if( (*W_Lept1_relIsoRho03)[i] > 0.15 ) return -1;

     return 1;
   }


   Int_t WEleQ::MuonCutZ(int i)
   {
     if( (*Z_Sign)[i] != 0 ) return -1;
     if( !(*Z_Lept1_isGlobal)[i])return -1;
     if( !(*Z_Lept2_isGlobal)[i])return -1;
     if((*Z_Lept1_pt)[i] < 20) return -1;//trigger SingleMu15 but we use 25 for Wpt
     //if((*Z_Lept2_pt)[i] < 25) return -1;
     ////if((*Z_Lept2_pt)[i] < 10) return -1;
     if(fabs((*Z_Lept1_eta)[i])>2.1) return -1;
     if(fabs((*Z_Lept2_eta)[i])>2.1) return -1;
     if( (*Z_Lept1_globalNormChi2)[i]<0 || (*Z_Lept1_globalNormChi2)[i] >= 10) return -1;
     if( (*Z_Lept2_globalNormChi2)[i]<0 || (*Z_Lept2_globalNormChi2)[i] >= 10) return -1;
     if( (*Z_Lept1_muonHits)[i] <1) return -1;
     if( (*Z_Lept2_muonHits)[i] <1) return -1;
     if( (*Z_Lept1_matchStations)[i] <2 ) return -1;
     if( (*Z_Lept2_matchStations)[i] <2 ) return -1;
     if( (*Z_Lept1_trkLayers)[i] <6 )return -1;
     if( (*Z_Lept2_trkLayers)[i] <6 )return -1;
     if( (*Z_Lept1_pixelHits)[i] <1 )return -1;
     if( (*Z_Lept2_pixelHits)[i] <1 )return -1;
     if( fabs( (*Z_Lept1_dB)[i]) >0.02 )return -1;
     if( fabs( (*Z_Lept2_dB)[i]) >0.02 )return -1;
     if( fabs( (*Z_Lept1_dz)[i]) >0.5 )return -1;
     if( fabs( (*Z_Lept2_dz)[i]) >0.5 )return -1;
     double betaCor04= max(0.0,(*Z_Lept1_nhIso04)[i]+(*Z_Lept1_phIso04)[i]-0.5*(*Z_Lept1_pcIso04)[i]);
     if( ((*Z_Lept1_chIso04)[i]+betaCor04)/(*Z_Lept1_pt)[i] > 0.12) return -1; //Signal Band
     betaCor04= max(0.0,(*Z_Lept2_nhIso04)[i]+(*Z_Lept2_phIso04)[i]-0.5*(*Z_Lept2_pcIso04)[i]);
     if( ((*Z_Lept2_chIso04)[i]+betaCor04)/(*Z_Lept2_pt)[i] > 0.12) return -1; //Signal Band

     return 1;
   }


   Int_t WEleQ::ElectronCutZ(int i)
   {
     //////////////  Ele   V5 =======================================
     if( (*Z_Sign)[i] != 0 ) return -1;
     if((*Z_Lept1_pt)[i] < 25) return -1;
     //if((*Z_Lept2_pt)[i] < 10) return -1;
     if(fabs((*Z_Lept1_etaSC)[i])>2.5) return -1;
     if(fabs((*Z_Lept2_etaSC)[i])>2.5) return -1;

     //W/Z inclusive
     if(fabs((*Z_Lept1_etaSC)[i])>1.4442 && fabs((*Z_Lept1_etaSC)[i])<1.566)return -1;
     //if(fabs((*Z_Lept1_etaSC)[i])>1.47 && fabs((*Z_Lept1_etaSC)[i])<1.566)return -1;
     if(fabs((*Z_Lept2_etaSC)[i])>1.4442 && fabs((*Z_Lept2_etaSC)[i])<1.566)return -1;
     //if(fabs((*Z_Lept2_etaSC)[i])>1.47 && fabs((*Z_Lept2_etaSC)[i])<1.566)return -1;

     if( fabs( (*Z_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept1_etaSC)[i]) < 1.47)
     {
	 if( (*Z_Lept1_sigmaIEtaIEta)[i] > 0.01 ) return -1;
     }else{
	 if( (*Z_Lept1_sigmaIEtaIEta)[i] > 0.03 ) return -1;
     }

     if( fabs( (*Z_Lept2_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept2_etaSC)[i]) < 1.47)
     {
	 if( (*Z_Lept2_sigmaIEtaIEta)[i] > 0.01 ) return -1;
     }else{
	 if( (*Z_Lept2_sigmaIEtaIEta)[i] > 0.03 ) return -1;
     }

     if( fabs( (*Z_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs((*Z_Lept1_dEtaIn)[i]) >  0.004 ) return -1;
     }else{
	 if( fabs((*Z_Lept1_dEtaIn)[i])  >   0.007 ) return -1;
     }

     if( fabs( (*Z_Lept2_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept2_etaSC)[i]) < 1.47)
     {
	 if( fabs((*Z_Lept2_dEtaIn)[i]) >  0.004 ) return -1;
     }else{
	 if( fabs((*Z_Lept2_dEtaIn)[i])  >   0.007 ) return -1;
     }

     if( fabs( (*Z_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs((*Z_Lept1_dPhiIn)[i])  > 0.06 ) return -1;
     }else {
	 if( fabs((*Z_Lept1_dPhiIn)[i])  > 0.03 ) return -1;
     }

     if( fabs( (*Z_Lept2_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept2_etaSC)[i]) < 1.47)
     {
	 if( fabs((*Z_Lept2_dPhiIn)[i])  > 0.06 ) return -1;
     }else {
	 if( fabs((*Z_Lept2_dPhiIn)[i])  > 0.03 ) return -1;
     }

     if( fabs( (*Z_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept1_etaSC)[i]) < 1.47)
     {
	 if( (*Z_Lept1_HoverE)[i] > 0.12 ) return -1;
     }else {
	 if( (*Z_Lept1_HoverE)[i] > 0.10 ) return -1;
     } 
     
     if( fabs( (*Z_Lept2_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept2_etaSC)[i]) < 1.47)
     {
	 if( (*Z_Lept2_HoverE)[i] > 0.12 ) return -1;
     }else {
	 if( (*Z_Lept2_HoverE)[i] > 0.10 ) return -1;
     }

     if( fabs( (*Z_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs((*Z_Lept1_dxy)[i]) > 0.02 ) return -1;
     }else {
	 if( fabs((*Z_Lept1_dxy)[i]) > 0.02 ) return -1;
     }
     
     if( fabs( (*Z_Lept2_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept2_etaSC)[i]) < 1.47)
     {
	 if( fabs((*Z_Lept2_dxy)[i]) > 0.02 ) return -1;
     }else {
	 if( fabs((*Z_Lept2_dxy)[i]) > 0.02 ) return -1;
     }

     if( fabs( (*Z_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs((*Z_Lept1_dz)[i]) > 0.1 ) return -1;
     }else{
	 if( fabs((*Z_Lept1_dz)[i]) > 0.1 ) return -1;
     }

     //cout<< fabs((*Z_Lept2_dz)[i])<<endl; 
     if( fabs( (*Z_Lept2_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept2_etaSC)[i]) < 1.47)
     {
	 if( fabs((*Z_Lept2_dz)[i]) > 0.1 ) return -1;
     }else{
	 if( fabs((*Z_Lept2_dz)[i]) > 0.1 ) return -1;
     }

     if( fabs( (*Z_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs((*Z_Lept1_InvEminusInvP)[i]) > 0.05 ) return -1;
     }else{
	 if( fabs((*Z_Lept1_InvEminusInvP)[i]) > 0.05) return -1;
     }
     
     if( fabs( (*Z_Lept2_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept2_etaSC)[i]) < 1.47)
     {
	 if( fabs((*Z_Lept2_InvEminusInvP)[i]) > 0.05 ) return -1;
     }else{
	 if( fabs((*Z_Lept2_InvEminusInvP)[i]) > 0.05) return -1;
     }

     if( fabs( (*Z_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs((*Z_Lept1_mHits)[i]) > 1 ) return -1;
     }else{
	 if( fabs((*Z_Lept1_mHits)[i]) > 1) return -1;
     }

     if( fabs( (*Z_Lept2_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept2_etaSC)[i]) < 1.47)
     {
	 if( fabs((*Z_Lept2_mHits)[i]) > 1 ) return -1;
     }else{
	 if( fabs((*Z_Lept2_mHits)[i]) > 1) return -1;
     }

     if( (*Z_Lept1_hasConversion)[i] ) return -1;
     if( (*Z_Lept2_hasConversion)[i] ) return -1;
     if( (*Z_Lept1_relIsoRho03)[i] > 0.15 ) return -1;
     if( (*Z_Lept2_relIsoRho03)[i] > 0.15 ) return -1;

     //       if( (*W_Neut_pt)[i] < 25 ) return -1;
     //          if( (*W_Mt)[i] < 40 ) return -1;
    
     return 1;
   }


   Int_t WEleQ::ElectronCutZHighPU(int i)
   {


     //////////////  Ele   V5 =======================================

     if( (*Z_Sign)[i] != 0 ) return -1;
     if((*Z_Lept1_pt)[i] < 20) return -1;
     //if((*Z_Lept2_pt)[i] < 25) return -1;
     if(fabs((*Z_Lept1_etaSC)[i])>2.5) return -1;
     if(fabs((*Z_Lept2_etaSC)[i])>2.5) return -1;
     //W/Z inclusive
     if(fabs((*Z_Lept1_etaSC)[i])>1.4442 && fabs((*Z_Lept1_etaSC)[i])<1.566)return -1;
     //if(fabs((*Z_Lept1_etaSC)[i])>1.47 && fabs((*Z_Lept1_etaSC)[i])<1.566)return -1;
     if(fabs((*Z_Lept2_etaSC)[i])>1.4442 && fabs((*Z_Lept2_etaSC)[i])<1.566)return -1;
     //if(fabs((*Z_Lept2_etaSC)[i])>1.47 && fabs((*Z_Lept2_etaSC)[i])<1.566)return -1;
     
     if( fabs( (*Z_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept1_etaSC)[i]) < 1.47)
     {
	 if( (*Z_Lept1_sigmaIEtaIEta)[i] > 0.01 ) return -1;
     }else{
	 if( (*Z_Lept1_sigmaIEtaIEta)[i] > 0.03 ) return -1;
     }

     if( fabs( (*Z_Lept2_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept2_etaSC)[i]) < 1.47)
     {
	 if( (*Z_Lept2_sigmaIEtaIEta)[i] > 0.01 ) return -1;
     }else{
	 if( (*Z_Lept2_sigmaIEtaIEta)[i] > 0.03 ) return -1;
     }

     if( fabs( (*Z_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs((*Z_Lept1_dEtaIn)[i]) >  0.004 ) return -1;
     }else{
	 if( fabs((*Z_Lept1_dEtaIn)[i])  >   0.007 ) return -1;
     }

     if( fabs( (*Z_Lept2_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept2_etaSC)[i]) < 1.47)
     {
	 if( fabs((*Z_Lept2_dEtaIn)[i]) >  0.004 ) return -1;
     }else{
	 if( fabs((*Z_Lept2_dEtaIn)[i])  >   0.007 ) return -1;
     }

     if( fabs( (*Z_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs((*Z_Lept1_dPhiIn)[i])  > 0.06 ) return -1;
     }else {
	 if( fabs((*Z_Lept1_dPhiIn)[i])  > 0.03 ) return -1;
     }

     if( fabs( (*Z_Lept2_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept2_etaSC)[i]) < 1.47)
     {
	 if( fabs((*Z_Lept2_dPhiIn)[i])  > 0.06 ) return -1;
     }else {
	 if( fabs((*Z_Lept2_dPhiIn)[i])  > 0.03 ) return -1;
     }

     if( fabs( (*Z_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept1_etaSC)[i]) < 1.47)
     {
	 if( (*Z_Lept1_HoverE)[i] > 0.04 ) return -1;
     }else {
	 if( (*Z_Lept1_HoverE)[i] > 0.025 ) return -1;
     }

     if( fabs( (*Z_Lept2_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept2_etaSC)[i]) < 1.47)
     {
	 if( (*Z_Lept2_HoverE)[i] > 0.04 ) return -1;
     }else {
	 if( (*Z_Lept2_HoverE)[i] > 0.025 ) return -1;
     }

     if( fabs( (*Z_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs((*Z_Lept1_dxy)[i]) > 0.02 ) return -1;
     }else {
	 if( fabs((*Z_Lept1_dxy)[i]) > 0.02 ) return -1;
     }
     
     if( fabs( (*Z_Lept2_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept2_etaSC)[i]) < 1.47)
     {
	 if( fabs((*Z_Lept2_dxy)[i]) > 0.02 ) return -1;
     }else {
	 if( fabs((*Z_Lept2_dxy)[i]) > 0.02 ) return -1;
     }

     if( fabs( (*Z_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs((*Z_Lept1_dz)[i]) > 0.1 ) return -1;
     }else{
	 if( fabs((*Z_Lept1_dz)[i]) > 0.1 ) return -1;
     }

     //cout<< fabs((*Z_Lept2_dz)[i])<<endl; 
     if( fabs( (*Z_Lept2_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept2_etaSC)[i]) < 1.47)
     {
	 if( fabs((*Z_Lept2_dz)[i]) > 0.1 ) return -1;
     }else{
	 if( fabs((*Z_Lept2_dz)[i]) > 0.1 ) return -1;
     }

     if( fabs( (*Z_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs((*Z_Lept1_InvEminusInvP)[i]) > 0.05 ) return -1;
     }else{
	 if( fabs((*Z_Lept1_InvEminusInvP)[i]) > 0.05) return -1;
     }

     if( fabs( (*Z_Lept2_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept2_etaSC)[i]) < 1.47)
     {
	 if( fabs((*Z_Lept2_InvEminusInvP)[i]) > 0.05 ) return -1;
     }else{
	 if( fabs((*Z_Lept2_InvEminusInvP)[i]) > 0.05) return -1;
     }

     if( fabs( (*Z_Lept1_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept1_etaSC)[i]) < 1.47)
     {
	 if( fabs((*Z_Lept1_mHits)[i]) > 0 ) return -1;
     }else{
	 if( fabs((*Z_Lept1_mHits)[i]) > 0 ) return -1;
     }

     if( fabs( (*Z_Lept2_etaSC)[i]) < 1.4442)
       //if( fabs( (*Z_Lept2_etaSC)[i]) < 1.47)
     {
	 if( fabs((*Z_Lept2_mHits)[i]) > 0 ) return -1;
     }else{
	 if( fabs((*Z_Lept2_mHits)[i]) > 0 ) return -1;
     }

     if( (*Z_Lept1_hasConversion)[i] ) return -1;
     if( (*Z_Lept2_hasConversion)[i] ) return -1;
     if( (*Z_Lept1_relIsoRho03)[i] > 0.15 ) return -1;
     if( (*Z_Lept2_relIsoRho03)[i] > 0.15 ) return -1;

     //       if( (*W_Neut_pt)[i] < 25 ) return -1;
     //          if( (*W_Mt)[i] < 40 ) return -1;

     return 1;
   }

Int_t WEleQ::DoScaleSmearScan(
    double zlep1Pt,double zlep1Pz,double zlep1En,double zlep1Phi,
    double zlep2Pt,double zlep2Pz,double zlep2En,double zlep2Phi,double TTW_)
{
  //TLorentzVector Z_4(
  //    zlep1Pt*cos(zlep1Phi)+zlep2Pt*cos(zlep2Phi),
  //    zlep1Pt*sin(zlep1Phi)+zlep2Pt*sin(zlep2Phi),
  //    zlep1Pz+zlep2Pz,
  //    zlep1En+zlep2En);
  //cout<<"ZmassOrg: "<<Zmass<<"================="<<endl;
  double scale, smear, newZlep1Pt,newZlep2Pt;
  for(int i(0);i<=ScaleBins-1;i++)
  {
    for(int j(0);j<=ScaleBins-1;j++)
    {
      scale = ScaleL + i*(ScaleH-ScaleL)/(ScaleBins-1);
      smear = SmearL + j*(SmearH-SmearL)/(ScaleBins-1);
      newZlep1Pt = gRandom->Gaus(0,1)*smear+scale*zlep1Pt;
      //newZlep2Pt = zlep2Pt;
      newZlep2Pt = gRandom->Gaus(0,1)*smear+scale*zlep2Pt;
      TLorentzVector Z_4(
          newZlep1Pt*cos(zlep1Phi)+newZlep2Pt*cos(zlep2Phi),
          newZlep1Pt*sin(zlep1Phi)+newZlep2Pt*sin(zlep2Phi),
          zlep1Pz+zlep2Pz,
          zlep1En+zlep2En);
      //cout<<"scale smear "<<scale<<" "<<smear<<endl;
      //cout<<"old lepPt "<<zlep1Pt<<" "<<zlep2Pt<<" new Pt diff "<<newZlep1Pt-zlep1Pt<<" "<<newZlep2Pt-zlep2Pt<<" Zmass corr- org"<<Z_4.M()-Zmass<<endl;
      //      h1_ZmassDaughEta[i][j]->Fill(Z_4.M(),TTW_);
    }
  }
  return 0;
}

Int_t WEleQ::EtaRange(double lep1Eta,double lep2Eta)
{
  int lep1Range(-1);
  int lep2Range(-1);
  if(AnaChannel=="ElectronLowPU")
  {
    if( fabs(lep1Eta) >= 0.0   && fabs(lep1Eta) < 0.4)    lep1Range=0;
    if( fabs(lep1Eta) >= 0.4   && fabs(lep1Eta) < 0.8)    lep1Range=1;
    if( fabs(lep1Eta) >= 0.8   && fabs(lep1Eta) < 1.2)    lep1Range=2;
    if( fabs(lep1Eta) >= 1.2   && fabs(lep1Eta) < 1.4442) lep1Range=3;
    if( fabs(lep1Eta) >= 1.566 && fabs(lep1Eta) < 2.0)    lep1Range=4;
    if( fabs(lep1Eta) >= 2.0   && fabs(lep1Eta) < 2.5)    lep1Range=5;

    if( fabs(lep2Eta) >= 0.0   && fabs(lep2Eta) < 0.4)    lep2Range=0;
    if( fabs(lep2Eta) >= 0.4   && fabs(lep2Eta) < 0.8)    lep2Range=1;
    if( fabs(lep2Eta) >= 0.8   && fabs(lep2Eta) < 1.2)    lep2Range=2;
    if( fabs(lep2Eta) >= 1.2   && fabs(lep2Eta) < 1.4442) lep2Range=3;
    if( fabs(lep2Eta) >= 1.566 && fabs(lep2Eta) < 2.0)    lep2Range=4;
    if( fabs(lep2Eta) >= 2.0   && fabs(lep2Eta) < 2.5)    lep2Range=5;
  }

  if(AnaChannel=="ElectronHighPU")
  {
    if( fabs(lep1Eta) >= 0.0   && fabs(lep1Eta) < 0.2)    lep1Range=0;
    if( fabs(lep1Eta) >= 0.2   && fabs(lep1Eta) < 0.4)    lep1Range=1;
    if( fabs(lep1Eta) >= 0.4   && fabs(lep1Eta) < 0.6)    lep1Range=2;
    if( fabs(lep1Eta) >= 0.6   && fabs(lep1Eta) < 0.8)    lep1Range=3;
    if( fabs(lep1Eta) >= 0.8   && fabs(lep1Eta) < 1.0)    lep1Range=4;
    if( fabs(lep1Eta) >= 1.0   && fabs(lep1Eta) < 1.2)    lep1Range=5;
    if( fabs(lep1Eta) >= 1.2   && fabs(lep1Eta) < 1.4)    lep1Range=6;
    //if( fabs(lep1Eta) >= 1.4   && fabs(lep1Eta) < 1.6)    lep1Range=7;
    if( fabs(lep1Eta) >= 1.6   && fabs(lep1Eta) < 1.8)    lep1Range=7;
    if( fabs(lep1Eta) >= 1.8   && fabs(lep1Eta) < 2.0)    lep1Range=8;
    if( fabs(lep1Eta) >= 2.0   && fabs(lep1Eta) < 2.2)    lep1Range=9;
    if( fabs(lep1Eta) >= 2.2   && fabs(lep1Eta) < 2.4)    lep1Range=10;

    if( fabs(lep2Eta) >= 0.0   && fabs(lep2Eta) < 0.2)    lep2Range=0;
    if( fabs(lep2Eta) >= 0.2   && fabs(lep2Eta) < 0.4)    lep2Range=1;
    if( fabs(lep2Eta) >= 0.4   && fabs(lep2Eta) < 0.6)    lep2Range=2;
    if( fabs(lep2Eta) >= 0.6   && fabs(lep2Eta) < 0.8)    lep2Range=3;
    if( fabs(lep2Eta) >= 0.8   && fabs(lep2Eta) < 1.0)    lep2Range=4;
    if( fabs(lep2Eta) >= 1.0   && fabs(lep2Eta) < 1.2)    lep2Range=5;
    if( fabs(lep2Eta) >= 1.2   && fabs(lep2Eta) < 1.4)    lep2Range=6;
    //if( fabs(lep2Eta) >= 1.4   && fabs(lep2Eta) < 1.6)    lep2Range=7;
    if( fabs(lep2Eta) >= 1.6   && fabs(lep2Eta) < 1.8)    lep2Range=7;
    if( fabs(lep2Eta) >= 1.8   && fabs(lep2Eta) < 2.0)    lep2Range=8;
    if( fabs(lep2Eta) >= 2.0   && fabs(lep2Eta) < 2.2)    lep2Range=9;
    if( fabs(lep2Eta) >= 2.2   && fabs(lep2Eta) < 2.4)    lep2Range=10;
  }
  if(AnaChannel=="MuonLowPU" || AnaChannel=="MuonHighPU")
  {
    if( fabs(lep1Eta) >= 0.0   && fabs(lep1Eta) < 0.4)    lep1Range=0;
    if( fabs(lep1Eta) >= 0.4   && fabs(lep1Eta) < 0.8)    lep1Range=1;
    if( fabs(lep1Eta) >= 0.8   && fabs(lep1Eta) < 1.2)    lep1Range=2;
    if( fabs(lep1Eta) >= 1.2   && fabs(lep1Eta) < 1.6)    lep1Range=3;
    if( fabs(lep1Eta) >= 1.6   && fabs(lep1Eta) < 2.1)    lep1Range=4;

    if( fabs(lep2Eta) >= 0.0   && fabs(lep2Eta) < 0.4)    lep2Range=0;
    if( fabs(lep2Eta) >= 0.4   && fabs(lep2Eta) < 0.8)    lep2Range=1;
    if( fabs(lep2Eta) >= 0.8   && fabs(lep2Eta) < 1.2)    lep2Range=2;
    if( fabs(lep2Eta) >= 1.2   && fabs(lep2Eta) < 1.6)    lep2Range=3;
    if( fabs(lep2Eta) >= 1.6   && fabs(lep2Eta) < 2.1)    lep2Range=4;
  }
  
  if( lep1Range == lep2Range )return lep1Range;
  else return -1;
}
Int_t WEleQ::EtaRange(double lep1Eta)
{
  int lep1Range(-1);
  if(AnaChannel=="ElectronLowPU")
  {
    if( fabs(lep1Eta) >= 0.0   && fabs(lep1Eta) < 0.4)    lep1Range=0;
    if( fabs(lep1Eta) >= 0.4   && fabs(lep1Eta) < 0.8)    lep1Range=1;
    if( fabs(lep1Eta) >= 0.8   && fabs(lep1Eta) < 1.2)    lep1Range=2;
    if( fabs(lep1Eta) >= 1.2   && fabs(lep1Eta) < 1.4442) lep1Range=3;
    if( fabs(lep1Eta) >= 1.566 && fabs(lep1Eta) < 2.0)    lep1Range=4;
    if( fabs(lep1Eta) >= 2.0   && fabs(lep1Eta) < 2.5)    lep1Range=5;
    
  }
  if(AnaChannel=="ElectronHighPU")
  {
    if( fabs(lep1Eta) >= 0.0   && fabs(lep1Eta) < 0.2)    lep1Range=0;
    if( fabs(lep1Eta) >= 0.2   && fabs(lep1Eta) < 0.4)    lep1Range=1;
    if( fabs(lep1Eta) >= 0.4   && fabs(lep1Eta) < 0.6)    lep1Range=2;
    if( fabs(lep1Eta) >= 0.6   && fabs(lep1Eta) < 0.8)    lep1Range=3;
    if( fabs(lep1Eta) >= 0.8   && fabs(lep1Eta) < 1.0)    lep1Range=4;
    if( fabs(lep1Eta) >= 1.0   && fabs(lep1Eta) < 1.2)    lep1Range=5;
    if( fabs(lep1Eta) >= 1.2   && fabs(lep1Eta) < 1.4)    lep1Range=6;
    //if( fabs(lep1Eta) >= 1.4   && fabs(lep1Eta) < 1.6)    lep1Range=7;
    if( fabs(lep1Eta) >= 1.6   && fabs(lep1Eta) < 1.8)    lep1Range=7;
    if( fabs(lep1Eta) >= 1.8   && fabs(lep1Eta) < 2.0)    lep1Range=8;
    if( fabs(lep1Eta) >= 2.0   && fabs(lep1Eta) < 2.2)    lep1Range=9;
    if( fabs(lep1Eta) >= 2.2   && fabs(lep1Eta) < 2.4)    lep1Range=10;
  }
  if(AnaChannel=="MuonLowPU" || AnaChannel=="MuonHighPU")
  {
    if( fabs(lep1Eta) >= 0.0   && fabs(lep1Eta) < 0.4)    lep1Range=0;
    if( fabs(lep1Eta) >= 0.4   && fabs(lep1Eta) < 0.8)    lep1Range=1;
    if( fabs(lep1Eta) >= 0.8   && fabs(lep1Eta) < 1.2)    lep1Range=2;
    if( fabs(lep1Eta) >= 1.2   && fabs(lep1Eta) < 1.6)    lep1Range=3;
    if( fabs(lep1Eta) >= 1.6   && fabs(lep1Eta) < 2.1)    lep1Range=4;
  }
  return lep1Range;
}
//MisChargeStudy
/*Int_t WEleQ::FillMisChargeInfo()
{
  h1_Zmass_QAll->Fill(Zmass,TTW);
  for(int iz(0); iz<Z_size;iz++){
  ZLep1eta = (*Z_Lept1_eta)[iz];
  ZLep2eta = (*Z_Lept2_eta)[iz];
  ZLep1charge = (*Z_Lept1_charge)[iz];
  ZLep2charge = (*Z_Lept2_charge)[iz];
  ZLep1Requirement = (*Z_Lept1_GsfCtfScPixchargeConsistentcheck)[iz];
  ZLep2Requirement = (*Z_Lept2_GsfCtfScPixchargeConsistentcheck)[iz];
  for(int i=0;i<lept1eta;i++){
  for(int j=0;j<lept2eta;j++){
  if (fabs(ZLep1eta) > wqaMetMNBins[i] && fabs(ZLep1eta) < wqaMetMXBins[i] ) {
  if (fabs(ZLep2eta) > wqaMetMNBins[j] && fabs(ZLep2eta) < wqaMetMXBins[j] ) {
    h1_Zmass_QNo[i][j]->Fill(Zmass,TTW);
    if ( ZLep1Requirement == 1 && ZLep2Requirement == 1){
    h1_Zmass_QThree[i][j]->Fill(Zmass,TTW);
    }
    if(ZLep1charge*ZLep2charge==1){
    h1_Zmass_QNoSame[i][j]->Fill(Zmass,TTW);
    }
    if(ZLep1Requirement == 1 && ZLep2Requirement == 1 && ZLep1charge*ZLep2charge==1){
    h1_Zmass_QThreeSame[i][j]->Fill(Zmass,TTW);
    }
   }
   }
  }
  }
  }
  return 0;
}
*/

Int_t WEleQ::FillAcceptInfo()
{
  isPostPassAcc = false;
  isBornPassAcc = false;
  int NGenW = GenW_Born_pt->size();
  //Check W number and Lept1 id
  if( NGenW != 1) cout<<"Notice: Number of GenW is not 1 but "<<NGenW<<endl;
  if(AnaChannel == "MuonLowPU")if( fabs((*GenW_BornLept1_id)[0]) != GenType::kMuon)
  {
    cout<<"Error: Muon Channel but BornLept1_id is "<<(*GenW_BornLept1_id)[0]<<endl;
    exit(-1);
  }
  if(AnaChannel == "ElectronLowPU")if( fabs((*GenW_BornLept1_id)[0]) != GenType::kElectron)
  {
    cout<<"Error: Electron Channel but BornLept1_id is "<<(*GenW_BornLept1_id)[0]<<endl;
    exit(-1);
  }

  // Gen Information
  TVector2 genW_Post_2D(
	(*GenW_PostLept1_px)[0] + (*GenW_PostLept2_px)[0],
	(*GenW_PostLept1_py)[0] + (*GenW_PostLept2_py)[0]);
  genInfo.PostW_pt = genW_Post_2D.Mod();
  genInfo.BornW_pt = (*GenW_Born_pt)[0];

  // Fill Born Level
  // Acceptance
    //Full Phase Spece
  // Fiducial 
  if(AnaChannel == "MuonLowPU")
  if( (*GenW_BornLept1_pt)[0] > 20 )
  if( fabs( (*GenW_BornLept1_eta)[0]) < 2.1 )
    isBornPassAcc = true;
  if(AnaChannel == "ElectronLowPU")
  if( (*GenW_BornLept1_pt)[0] > 25 )
  if( fabs( (*GenW_BornLept1_eta)[0]) < 2.5 )
  if( (fabs((*GenW_BornLept1_eta)[0]) < 1.444) || (fabs( (*GenW_BornLept1_eta)[0]) >1.566 ) )  
    isBornPassAcc = true;

  // Fiducial of Post 
  if(AnaChannel == "MuonLowPU")
  if( (*GenW_PostLept1_pt)[0] > 20 )
  if( fabs( (*GenW_PostLept1_eta)[0]) < 2.1 )
    isPostPassAcc = true;
  if(AnaChannel == "ElectronLowPU")
  if( (*GenW_PostLept1_pt)[0] > 25 )
  if( fabs((*GenW_PostLept1_eta)[0]) < 2.5 )
  if( (fabs((*GenW_PostLept1_eta)[0]) < 1.444) || (fabs((*GenW_PostLept1_eta)[0]) >1.566 ) )  
    isPostPassAcc = true;
  // Fill Histo
  h1_Born_AP->Fill( genInfo.BornW_pt,TTW);
  if( isBornPassAcc )
  {
    h1_Born_BornFid->Fill(genInfo.BornW_pt,TTW);
    if( evtCnt % 2 == 0 )
    {
      h1_Born_BornFid_Even->Fill(genInfo.BornW_pt,TTW);
    }
  }
  if( isPostPassAcc )
  {
    h1_Post_PostFid->Fill(genInfo.PostW_pt,TTW);
    if( evtCnt % 2 == 0 )
    {
      h1_Post_PostFid_Even->Fill(genInfo.PostW_pt,TTW);
    }
  }
  if( isPostPassAcc && isBornPassAcc )
  {
    h1_Born_BothFid->Fill(genInfo.BornW_pt,TTW);
    h1_Post_BothFid->Fill(genInfo.PostW_pt,TTW);
    h2_PostBorn_BothFid
      ->Fill(genInfo.PostW_pt,genInfo.BornW_pt,TTW);
    if( evtCnt % 2 == 0 )
    {
      h1_Born_BothFid_Even->Fill(genInfo.BornW_pt,TTW);
      h1_Post_BothFid_Even->Fill(genInfo.PostW_pt,TTW);
    }
  }
  return 0;
}
Int_t WEleQ::DumpUnfoldInfo(int i)
{
  //Gen Level Study
  TruthRecoPost = true;
  if(GenW_Born_Id->size()<1)
  {
    TruthRecoPost=false;
    cout<<"Notice: No of GenW <1"<<endl;
    return -1;
  }
  int NGenW = GenW_Born_pt->size();
  if( NGenW != 1) cout<<"Notice: Number of GenW is not 1 but "<<NGenW<<endl;
  // Assuming there is only one GenW
  //Response 
    wCand.genIdx = (*W_Lept1_genIdxMatch)[i];
    // TODO use this at the moment
    if(wCand.genIdx < 0)
    {
      TruthRecoPost=false;
      //cout<<"Notice: genIdx < 0"<<endl;
      return -1;
    }
    if(wCand.genIdx != 0)
      cout<<"Warning: How come the gen Idx is not 0 ================"<<endl;
    // Only for matched one
    if( (*W_Lept1_genDeltaR)[i] > 0.025){TruthRecoPost=false;return -1;}
    //if( (*W_Lept1_genDPtRel)[i] > 0.025) continue;
    //Set wCand pt, phi
    TVector2 genPostW_2D(
      (*GenW_PostLept1_px)[wCand.genIdx]+(*GenW_PostLept2_px)[wCand.genIdx],
      (*GenW_PostLept1_py)[wCand.genIdx]+(*GenW_PostLept2_py)[wCand.genIdx]);
    genInfo.PostW_pt= genPostW_2D.Mod();
    genInfo.BornW_pt = (*GenW_Born_pt)[wCand.genIdx];
  return 0;
}

Int_t WEleQ::FillUnfoldInfo()
{
    h1_Truth_Rec->Fill(wCand.pt,TTW);
    h1_Truth_Post->Fill(genInfo.PostW_pt,TTW);
    if( evtCnt % 2 == 0 )
    {
      h1_Truth_Rec_Even->Fill(wCand.pt,TTW);
      h1_Truth_Post_Even->Fill(genInfo.PostW_pt,TTW);
    }else{              
      h1_Truth_Rec_Odd->Fill(wCand.pt,TTW);
      h1_Truth_Post_Odd->Fill(genInfo.PostW_pt,TTW);
    }
    h2_Truth_Rec_AP_Post->Fill(wCand.pt,genInfo.PostW_pt,TTW);

    unfoldInfo.recoPreFsrGenWptRes = (wCand.pt-genInfo.BornW_pt)/genInfo.BornW_pt;
    unfoldInfo.recoPstFsrGenWptRes = (wCand.pt-genInfo.PostW_pt)/genInfo.PostW_pt;
    h1_W_pt_RecoPreFsrGenRes[0]->Fill(unfoldInfo.recoPreFsrGenWptRes);
    h1_W_pt_RecoPstFsrGenRes[0]->Fill(unfoldInfo.recoPstFsrGenWptRes);
    for(int ipt(0);ipt<NWptBinPlus-1;ipt++)
    {
      if(genInfo.BornW_pt > Bins[ipt] && genInfo.BornW_pt < Bins[ipt+1])
      {
        h1_W_pt_RecoPreFsrGenRes[ipt+1]->Fill(unfoldInfo.recoPreFsrGenWptRes);
        h1_W_pt_RecoPstFsrGenRes[ipt+1]->Fill(unfoldInfo.recoPstFsrGenWptRes);
      }
      //if(genInfo.PostW_pt > Bins[ipt] && genInfo.PostW_pt < Bins[ipt+1])
      //{
      //  h1_pstFsr2ReconW_pt[ipt]->Fill(wCand.pt);
      //}
    }
    //We've found the gen match, and get out of here
    if(AnaChannel == "ElectronLowPU" )
    {
      if( wCand.charge > 0)
      {
	SF = ElePlusEffiCorrection(wCand.lep_pt,wCand.lep_etaSC);
      }
      else  if( wCand.charge < 0)
      {
	SF = EleMinusEffiCorrection(wCand.lep_pt,wCand.lep_etaSC);
      }
    }
    if(AnaChannel == "MuonLowPU")
    {
      if( wCand.charge > 0)
      {
	SF = MuonPlusEffiCorrection(wCand.lep_pt,wCand.lep_eta);
      }
      else  if( wCand.charge < 0)
      {
	SF = MuonMinusEffiCorrection(wCand.lep_pt,wCand.lep_eta);
      }
    }
    h1_Truth_Post_EffCorr->Fill(genInfo.PostW_pt,TTW*SF);
    return 0;
}
Int_t WEleQ::DoRecoilCorr()
{
  //Uncomment to apply scale/res corrections to MC
  //wCand.lep_pt_corr = gRandom->Gaus(wCand.lep_pt*lepScale,lepRes);
 
    if(AnaChannel == "ElectronLowPU")
    {
     //MC Smear Correction
     if(Mode == "AllCorrectionsMC" || Mode == "Unfold")
     {
       smearcorr=EleSmearMC(wCand.lep_etaSC);
       PtEtaPhiMLorentzVector WeleMC_4( wCand.lep_pt,wCand.lep_eta,wCand.lep_phi,0.000511);
       corr1 = gRandom->Gaus(WeleMC_4.E(), smearcorr)/WeleMC_4.E();
       WeleMC_4=corr1*WeleMC_4;
       wCand.lep_pt_corr=WeleMC_4.Pt();
     }else{
       wCand.lep_pt_corr = wCand.lep_pt;
     }
    }
    
    if(AnaChannel == "MuonLowPU")
    {
     //MC Smear Correction
     if(Mode == "AllCorrectionsMC" || Mode == "Unfold")
     {
       smearcorr= MuonSmearMC(wCand.lep_eta);
       PtEtaPhiMLorentzVector Wmu_4( wCand.lep_pt,wCand.lep_eta,wCand.lep_phi,0.1056);
       corr1 = gRandom->Gaus(Wmu_4.E(), smearcorr)/Wmu_4.E();
       Wmu_4=corr1*Wmu_4;
       wCand.lep_pt_corr=Wmu_4.Pt();
     } else{
       wCand.lep_pt_corr = wCand.lep_pt;
     }
    }
    //  wCand.lep_pt_corr = wCand.lep_pt;
  if(wCand.genIdx < 0) wCand.genIdx = 0;
  //genBeFsrW_pt = (*GenW_Born_pt)[gi];
  //genW_phi = (*GenW_phi)[gi];
  TVector2 genPost2D(
        (*GenW_PostLept1_px)[wCand.genIdx]+(*GenW_PostLept2_px)[wCand.genIdx],
        (*GenW_PostLept1_py)[wCand.genIdx]+(*GenW_PostLept2_py)[wCand.genIdx]);
  genInfo.PostW_pt= genPost2D.Mod();
  genInfo.PostW_phi= TVector2::Phi_mpi_pi(genPost2D.Phi());
  if( (*GenW_Born_Id)[wCand.genIdx] == 24 ){genInfo.charge = 1;}else{genInfo.charge = -1;}
  //TVector2 W2D_lepCorrOnly(
  //    wCand.Nu_px+wCand.lep_pt_corr*cos(wCand.lep_phi),
  //    wCand.Nu_py+wCand.lep_pt_corr*sin(wCand.lep_phi));
  //wCand.pt = W2D_lepCorrOnly.Mod();
  //if( wCand.pt < 100)
  //{
    recoilCorr->Correct(
      corrMet,corrMetPhi,
      genInfo.PostW_pt,genInfo.PostW_phi,//basedonthis,calculate correctedrecoilvectors
      //genBeFsrW_pt,genW_phi, 
      wCand.lep_pt_corr,wCand.lep_phi,
      0,genInfo.charge); //nsigma(0:nominal,1:up,-1:down), charge
    TVector2 w_p_corr(corrMet*cos(corrMetPhi)+wCand.lep_pt_corr*cos(wCand.lep_phi),
      corrMet*sin(corrMetPhi)+wCand.lep_pt_corr*sin(wCand.lep_phi));
    wCand.pt = w_p_corr.Mod();
  //}else{
  //  corrMet = wCand.Met;
  //}
  //
  //cout<<"Met:corrMet "<<Met<<":"<<corrMet<<endl;
  //TODO NNLO Correction
  //for( int ibin(1);ibin<=hNNLOCorr->GetNbinsX();ibin++)
  //{
  //  if(genBeFsrW_pt >= hNNLOCorr->GetBinLowEdge(ibin) &&
  //     genBeFsrW_pt < (hNNLOCorr->GetBinLowEdge(ibin)+hNNLOCorr->GetBinWidth(ibin))
  //     nnlocorr = hNNLOCorr->GetBinContent(ibin);
  //}
  return 0;
}
Int_t WEleQ::InitVar4Evt()
{
  wCand.size = W_pt->size();
  wCand.pt=0;w_pt_side=0;w_acop=0;
  wCand.Mt=0;
  wCand.Met=0;
  wCand.Met_side=0;
  wCand.genIdx=-999;
  wCand.charge=0;
  wCand.lep_pt = 0;
  wCand.lep_phi = 0;
  wCand.lep_eta = 0;
  wCand.lep_etaSC = 0;

  W_pass=0;
  glbMuChi2=0;
  addLepN=0;lep_pt=0;lep_pt_corr=0;corrMet=0;
  scalecorr1=0;
  corr1=0;
  corr2=0;
  scalecorr2=0;
  smearcorr1=0;
  smearcorr2=0;
  newZlep1Pt=0;
  newZlep2Pt=0;
  elemass=0.000511;
  muonmass=0.1056;
  u1W=-999;u2W=-999;u3W=-999;
  //genInfo.W_MCtruth = 0;
  genInfo.BornW_pt = 0;
  genInfo.PostW_pt = 0;
  return 0;
}

#endif // #ifdef WEleQ_cxx


