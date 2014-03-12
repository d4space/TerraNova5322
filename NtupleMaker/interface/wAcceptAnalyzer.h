// $Id: wAcceptAnalyzer.h,v 1.2 2013/08/07 04:12:37 khakim Exp $
//
//

// system include files
#include <memory>

// user include files
//
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/Candidate/interface/CompositeCandidate.h"
#include "CommonTools/CandUtils/interface/AddFourMomenta.h"
#include "CommonTools/CandUtils/interface/Booster.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/Framework/interface/LuminosityBlock.h"
#include "DataFormats/Common/interface/MergeableCounter.h"

//
#include "TerraNova/NtupleMaker/interface/WNtupleBranchVars.h"
#include "TerraNova/NtupleMaker/interface/BasicBranchVars.h"
#include "TerraNova/NtupleMaker/interface/MEtBranchVars.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TLorentzVector.h"

#include "../../Analysis/Utils/const.h"

//
// class declaration
//
using namespace edm;
using namespace std;
using namespace reco;

//template<typename T1, typename T2>
class wAcceptAnalyzer : public edm::EDFilter{
 public:
  explicit wAcceptAnalyzer(const edm::ParameterSet& iConfig)
{
    //now do what ever initialization is needed
    Channel = iConfig.getUntrackedParameter< std::string >("Channel");
    genParticlesLabel_= iConfig.getParameter<edm::InputTag>("genParticlesLabel");
    useEventCounter_ = iConfig.getParameter<bool>("useEventCounter");
    filters_ = iConfig.getUntrackedParameter<std::vector<std::string> >("filters");

    tree = fs->make<TTree>("tree", "Tree for W boson");

    EventData.vtx_isFake = new std::vector<int>;
    EventData.vtx_ndof = new std::vector<int>;
    EventData.vtx_z = new std::vector<double>;
    EventData.vtx_Rho = new std::vector<double>;

    Zs.Lept1_isGlobal= new std::vector<bool>;
    Zs.Lept1_isTrker= new std::vector<bool>;
    Zs.Lept1_pt= new std::vector<double>;
    Zs.Lept1_et= new std::vector<double>;
    Zs.Lept1_charge= new std::vector<double>;
    Zs.Lept1_eta= new std::vector<double>;
    Zs.Lept1_phi= new std::vector<double>;
    Zs.Lept1_px= new std::vector<double>;
    Zs.Lept1_py= new std::vector<double>;
    Zs.Lept1_pz= new std::vector<double>;
    Zs.Lept1_en= new std::vector<double>;
    Zs.Lept1_matchStations= new std::vector<int>;
    Zs.Lept1_dB= new std::vector<double>;
    Zs.Lept1_dz= new std::vector<double>;
    Zs.Lept1_globalNormChi2= new std::vector<double>;
    Zs.Lept1_muonHits= new std::vector<double>;
    Zs.Lept1_trkLayers= new std::vector<double>;
    Zs.Lept1_trackerHits= new std::vector<double>;
    Zs.Lept1_pixelHits= new std::vector<double>;
    Zs.Lept1_etaSC= new std::vector<double>;
    Zs.Lept1_phiSC= new std::vector<double>;
    Zs.Lept1_dEtaIn= new std::vector<double>;
    Zs.Lept1_dPhiIn= new std::vector<double>;
    Zs.Lept1_sigmaIEtaIEta= new std::vector<double>;
    Zs.Lept1_HoverE= new std::vector<double>;
    Zs.Lept1_fbrem= new std::vector<double>;
    Zs.Lept1_energyEC= new std::vector<double>;
    Zs.Lept1_Pnorm= new std::vector<double>;
    Zs.Lept1_InvEminusInvP= new std::vector<double>;
    Zs.Lept1_dxy= new std::vector<double>;
    Zs.Lept1_AEff03= new std::vector<double>;
    Zs.Lept1_hasConversion= new std::vector<bool>;
    Zs.Lept1_mHits= new std::vector<int>;
    Zs.Lept1_SCcharge= new std::vector<double>;
    Zs.Lept1_TKcharge= new std::vector<double>;
    Zs.Lept1_GSFcharge= new std::vector<double>;
    Zs.Lept1_GsfCtfScPixchargeConsistentcheck= new std::vector<double>;
    Zs.Lept1_chIso03= new std::vector<double>;
    Zs.Lept1_chIso04= new std::vector<double>;
    Zs.Lept1_nhIso03= new std::vector<double>;
    Zs.Lept1_nhIso04= new std::vector<double>;
    Zs.Lept1_phIso03= new std::vector<double>;
    Zs.Lept1_phIso04= new std::vector<double>;
    Zs.Lept1_pcIso03= new std::vector<double>;
    Zs.Lept1_pcIso04= new std::vector<double>;
    Zs.Lept1_relIsoCom03= new std::vector<double>;
    Zs.Lept1_relIsoCom04= new std::vector<double>;
    Zs.Lept1_relIsoBeta03= new std::vector<double>;
    Zs.Lept1_relIsoBeta04= new std::vector<double>;
    Zs.Lept1_relIsoRho03= new std::vector<double>;

    Zs.Lept1_RelisolPtTrks03 = new std::vector<double>; 
    Zs.Lept1_RelisoEm03      = new std::vector<double>; 
    Zs.Lept1_RelisoHad03     = new std::vector<double>; 


    Zs.Lept2_isGlobal= new std::vector<bool>;
    Zs.Lept2_isTrker= new std::vector<bool>;
    Zs.Lept2_pt= new std::vector<double>;
    Zs.Lept2_et= new std::vector<double>;
    Zs.Lept2_charge= new std::vector<double>;
    Zs.Lept2_eta= new std::vector<double>;
    Zs.Lept2_phi= new std::vector<double>;
    Zs.Lept2_px= new std::vector<double>;
    Zs.Lept2_py= new std::vector<double>;
    Zs.Lept2_pz= new std::vector<double>;
    Zs.Lept2_en= new std::vector<double>;
    Zs.Lept2_matchStations= new std::vector<int>;
    Zs.Lept2_dB= new std::vector<double>;
    Zs.Lept2_dz= new std::vector<double>;
    Zs.Lept2_globalNormChi2= new std::vector<double>;
    Zs.Lept2_muonHits= new std::vector<double>;
    Zs.Lept2_trkLayers= new std::vector<double>;
    Zs.Lept2_trackerHits= new std::vector<double>;
    Zs.Lept2_pixelHits= new std::vector<double>;
    Zs.Lept2_etaSC= new std::vector<double>;
    Zs.Lept2_phiSC= new std::vector<double>;
    Zs.Lept2_dEtaIn= new std::vector<double>;
    Zs.Lept2_dPhiIn= new std::vector<double>;
    Zs.Lept2_sigmaIEtaIEta= new std::vector<double>;
    Zs.Lept2_HoverE= new std::vector<double>;
    Zs.Lept2_fbrem= new std::vector<double>;
    Zs.Lept2_energyEC= new std::vector<double>;
    Zs.Lept2_Pnorm= new std::vector<double>;
    Zs.Lept2_InvEminusInvP= new std::vector<double>;
    Zs.Lept2_dxy= new std::vector<double>;
    Zs.Lept2_AEff03= new std::vector<double>;
    Zs.Lept2_hasConversion= new std::vector<bool>;
    Zs.Lept2_mHits= new std::vector<int>;
    Zs.Lept2_SCcharge= new std::vector<double>;
    Zs.Lept2_TKcharge= new std::vector<double>;
    Zs.Lept2_GSFcharge= new std::vector<double>;
    Zs.Lept2_GsfCtfScPixchargeConsistentcheck= new std::vector<double>;
    Zs.Lept2_chIso03= new std::vector<double>;
    Zs.Lept2_chIso04= new std::vector<double>;
    Zs.Lept2_nhIso03= new std::vector<double>;
    Zs.Lept2_nhIso04= new std::vector<double>;
    Zs.Lept2_phIso03= new std::vector<double>;
    Zs.Lept2_phIso04= new std::vector<double>;
    Zs.Lept2_pcIso03= new std::vector<double>;
    Zs.Lept2_pcIso04= new std::vector<double>;
    Zs.Lept2_relIsoCom03= new std::vector<double>;
    Zs.Lept2_relIsoCom04= new std::vector<double>;
    Zs.Lept2_relIsoBeta03= new std::vector<double>;
    Zs.Lept2_relIsoBeta04= new std::vector<double>;
    Zs.Lept2_relIsoRho03= new std::vector<double>;

    Zs.Lept2_RelisolPtTrks03 = new std::vector<double>; 
    Zs.Lept2_RelisoEm03      = new std::vector<double>; 
    Zs.Lept2_RelisoHad03     = new std::vector<double>; 

    Zs.Lept1_genIdxMatch= new std::vector<int>;
    Zs.Lept1_genDeltaR= new std::vector<double>;
    Zs.Lept1_genDPtRel= new std::vector<double>;
    Zs.Lept2_genIdxMatch= new std::vector<int>;
    Zs.Lept2_genDeltaR= new std::vector<double>;
    Zs.Lept2_genDPtRel= new std::vector<double>;

    Zs.diLeptVtxProb = new std::vector<double>;
    Zs.ZMass = new std::vector<double>;
    Zs.phi = new std::vector<double>;
    Zs.eta = new std::vector<double>;
    Zs.pt = new std::vector<double>;
    Zs.px = new std::vector<double>;
    Zs.py = new std::vector<double>;
    Zs.pz = new std::vector<double>;
    Zs.pz = new std::vector<double>;
    Zs.Neut_pt = new std::vector<double>;
    Zs.Neut_phi = new std::vector<double>;
    Zs.Neut_px = new std::vector<double>;
    Zs.Neut_py = new std::vector<double>;
    Zs.Sign=new std::vector<double>; //--(-2), +-(0), ++(2)

    Ws.Lept1_isGlobal=new std::vector<bool>;
    Ws.Lept1_isTrker=new std::vector<bool>;
    Ws.Lept1_pt=new std::vector<double>;
    Ws.Lept1_et=new std::vector<double>;
    Ws.Lept1_charge=new std::vector<double>;
    Ws.Lept1_eta=new std::vector<double>;
    Ws.Lept1_phi=new std::vector<double>;
    Ws.Lept1_px=new std::vector<double>;
    Ws.Lept1_py=new std::vector<double>;
    Ws.Lept1_pz=new std::vector<double>;
    Ws.Lept1_en=new std::vector<double>;
    Ws.Lept1_matchStations=new std::vector<int>;
    Ws.Lept1_dB=new std::vector<double>;
    Ws.Lept1_dz=new std::vector<double>;
    Ws.Lept1_globalNormChi2=new std::vector<double>;
    Ws.Lept1_muonHits=new std::vector<double>;
    Ws.Lept1_trkLayers=new std::vector<double>;
    Ws.Lept1_trackerHits=new std::vector<double>;
    Ws.Lept1_pixelHits=new std::vector<double>;
    Ws.Lept1_etaSC=new std::vector<double>;
    Ws.Lept1_phiSC=new std::vector<double>;
    Ws.Lept1_dEtaIn=new std::vector<double>;
    Ws.Lept1_dPhiIn=new std::vector<double>;
    Ws.Lept1_sigmaIEtaIEta=new std::vector<double>;
    Ws.Lept1_HoverE=new std::vector<double>;
    Ws.Lept1_fbrem=new std::vector<double>;
    Ws.Lept1_energyEC=new std::vector<double>;
    Ws.Lept1_Pnorm=new std::vector<double>;
    Ws.Lept1_InvEminusInvP=new std::vector<double>;
    Ws.Lept1_dxy=new std::vector<double>;
    Ws.Lept1_AEff03=new std::vector<double>;
    Ws.Lept1_chIso03=new std::vector<double>;
    Ws.Lept1_chIso04=new std::vector<double>;
    Ws.Lept1_nhIso03=new std::vector<double>;
    Ws.Lept1_nhIso04=new std::vector<double>;
    Ws.Lept1_phIso03=new std::vector<double>;
    Ws.Lept1_phIso04=new std::vector<double>;
    Ws.Lept1_pcIso03=new std::vector<double>;
    Ws.Lept1_pcIso04=new std::vector<double>;
    Ws.Lept1_relIsoCom03=new std::vector<double>;
    Ws.Lept1_relIsoCom04=new std::vector<double>;
    Ws.Lept1_relIsoBeta03=new std::vector<double>;
    Ws.Lept1_relIsoBeta04=new std::vector<double>;
    Ws.Lept1_relIsoRho03=new std::vector<double>;
    Ws.Lept1_hasConversion=new std::vector<bool>;
    Ws.Lept1_mHits=new std::vector<int>;
    Ws.Lept1_SCcharge= new std::vector<double>;
    Ws.Lept1_TKcharge= new std::vector<double>;
    Ws.Lept1_GSFcharge= new std::vector<double>;
    Ws.Lept1_GsfCtfScPixchargeConsistentcheck= new std::vector<double>;

    Ws.Lept1_RelisolPtTrks03 = new std::vector<double>; 
    Ws.Lept1_RelisoEm03      = new std::vector<double>; 
    Ws.Lept1_RelisoHad03     = new std::vector<double>; 

    Ws.W_invm = new std::vector<double>;
    Ws.Neut_pt = new std::vector<double>;
    Ws.Neut_phi = new std::vector<double>;
    Ws.Neut_px = new std::vector<double>;
    Ws.Neut_py = new std::vector<double>;
    Ws.W_pt = new std::vector<double>;
    Ws.W_eta = new std::vector<double>;
    Ws.W_phi = new std::vector<double>;
    Ws.W_px = new std::vector<double>;
    Ws.W_py = new std::vector<double>;
    Ws.W_pz = new std::vector<double>;
    Ws.W_Mt = new std::vector<double>;
    Ws.W_Acop = new std::vector<double>;
    Ws.W_Charge = new std::vector<double>;

    GenWs.Born_nLepts	= new std::vector<int>;
    GenWs.Born_id	= new std::vector<int>;
    GenWs.Born_status	= new std::vector<int>;
    GenWs.Born_mass	= new std::vector<double>;
    GenWs.Born_px	= new std::vector<double>;
    GenWs.Born_py	= new std::vector<double>;
    GenWs.Born_pz	= new std::vector<double>;
    GenWs.Born_pt	= new std::vector<double>;
    GenWs.Born_eta	= new std::vector<double>;
    GenWs.Born_phi	= new std::vector<double>;

    GenWs.BornLept1_id	= new std::vector<int>;
    GenWs.BornLept1_status= new std::vector<int>;
    GenWs.BornLept1_px	= new std::vector<double>;
    GenWs.BornLept1_py	= new std::vector<double>;
    GenWs.BornLept1_pz	= new std::vector<double>;
    GenWs.BornLept1_en	= new std::vector<double>;
    GenWs.BornLept1_pt	= new std::vector<double>;
    GenWs.BornLept1_et  = new std::vector<double>;
    GenWs.BornLept1_charge  = new std::vector<double>;
    GenWs.BornLept1_eta	= new std::vector<double>;
    GenWs.BornLept1_phi	= new std::vector<double>;
    GenWs.BornLept2_id	= new std::vector<int>;
    GenWs.BornLept2_status= new std::vector<int>;
    GenWs.BornLept2_px	= new std::vector<double>;
    GenWs.BornLept2_py	= new std::vector<double>;
    GenWs.BornLept2_pz	= new std::vector<double>;
    GenWs.BornLept2_en	= new std::vector<double>;
    GenWs.BornLept2_pt	= new std::vector<double>;
    GenWs.BornLept2_et  = new std::vector<double>;
    GenWs.BornLept2_charge  = new std::vector<double>;
    GenWs.BornLept2_eta	= new std::vector<double>;
    GenWs.BornLept2_phi	= new std::vector<double>;

    GenWs.PostLept1_id	= new std::vector<int>;
    GenWs.PostLept1_status= new std::vector<int>;
    GenWs.PostLept1_px	= new std::vector<double>;
    GenWs.PostLept1_py	= new std::vector<double>;
    GenWs.PostLept1_pz	= new std::vector<double>;
    GenWs.PostLept1_en	= new std::vector<double>;
    GenWs.PostLept1_pt	= new std::vector<double>;
    GenWs.PostLept1_et  = new std::vector<double>;
    GenWs.PostLept1_charge  = new std::vector<double>;
    GenWs.PostLept1_eta	= new std::vector<double>;
    GenWs.PostLept1_phi	= new std::vector<double>;
    GenWs.PostLept2_id	= new std::vector<int>;
    GenWs.PostLept2_status= new std::vector<int>;
    GenWs.PostLept2_px	= new std::vector<double>;
    GenWs.PostLept2_py	= new std::vector<double>;
    GenWs.PostLept2_pz	= new std::vector<double>;
    GenWs.PostLept2_en	= new std::vector<double>;
    GenWs.PostLept2_pt	= new std::vector<double>;
    GenWs.PostLept2_et  = new std::vector<double>;
    GenWs.PostLept2_charge  = new std::vector<double>;
    GenWs.PostLept2_eta	= new std::vector<double>;
    GenWs.PostLept2_phi	= new std::vector<double>;

    GenZs.nLepts	= new std::vector<int>;
    GenZs.id		= new std::vector<int>;
    GenZs.status	= new std::vector<int>;
    GenZs.mass		= new std::vector<double>;
    GenZs.px		= new std::vector<double>;
    GenZs.py		= new std::vector<double>;
    GenZs.pz		= new std::vector<double>;
    GenZs.pt		= new std::vector<double>;
    GenZs.eta		= new std::vector<double>;
    GenZs.phi		= new std::vector<double>;
    GenZs.Lept1_id	= new std::vector<int>;
    GenZs.Lept1_status	= new std::vector<int>;
    GenZs.Lept1_px	= new std::vector<double>;
    GenZs.Lept1_py	= new std::vector<double>;
    GenZs.Lept1_pz	= new std::vector<double>;
    GenZs.Lept1_en	= new std::vector<double>;
    GenZs.Lept1_pt	= new std::vector<double>;
    GenZs.Lept1_et      = new std::vector<double>;
    GenZs.Lept1_charge      = new std::vector<double>;
    GenZs.Lept1_eta	= new std::vector<double>;
    GenZs.Lept1_phi	= new std::vector<double>;
    GenZs.Lept2_id	= new std::vector<int>;
    GenZs.Lept2_status	= new std::vector<int>;
    GenZs.Lept2_px	= new std::vector<double>;
    GenZs.Lept2_py	= new std::vector<double>;
    GenZs.Lept2_pz	= new std::vector<double>;
    GenZs.Lept2_en	= new std::vector<double>;
    GenZs.Lept2_pt	= new std::vector<double>;
    GenZs.Lept2_et      = new std::vector<double>;
    GenZs.Lept2_charge      = new std::vector<double>;
    GenZs.Lept2_eta	= new std::vector<double>;
    GenZs.Lept2_phi	= new std::vector<double>;


    Ws.Lept1_genIdxMatch= new std::vector<int>;
    Ws.Lept1_genDeltaR	= new std::vector<double>;
    Ws.Lept1_genDPtRel	= new std::vector<double>;

    tmp = fs->make<TH1F>("EventSummary","EventSummary",filters_.size(),0,filters_.size());
}
  ~wAcceptAnalyzer()
  {
  }

//===============================================================
private:
//===============================================================

// Variables ==================================================
  bool acceptFT;
  bool isRD;
  struct GenInfo{
    double mass;
    int id,Lept1_id,Lept2_id;
    int status,Lept1_status,Lept2_status;
    double px,py,pz,pt,eta,phi;
    double Lept1_px,Lept1_py,Lept1_pz,Lept1_en,Lept1_pt,Lept1_eta,Lept1_phi,Lept1_et,Lept1_charge;
    double Lept2_px,Lept2_py,Lept2_pz,Lept2_en,Lept2_pt,Lept2_eta,Lept2_phi,Lept2_et,Lept2_charge;
  };


  std::string Channel;

  edm::InputTag genParticlesLabel_;
  //Handle
  //iterator------------------------------
  std::vector<std::string> filters_;

  bool useEventCounter_;
  

  edm::Service<TFileService> fs;

  TTree* tree;
  EventBranches	EventData;
  TrigBranches	HLTData;
  Zboson	Zs;
  Wboson	Ws;
  GenWboson	GenWs;
  GenZboson	GenZs;
  FSRphoton	FSRph;

  TH1F * tmp;

  // ----------member data ---------------------------

  //add run event data
  //unsigned int EVENT;
  //unsigned int RUN;
  //unsigned int LUMI;
  //unsigned int npileup;
  //unsigned int nvertex;
  //double weightin;
  //double weight;
  //double weightplus;
  //double weightminus;

  /// constant iterator for L1 trigger
  //  http://cmssw.cvs.cern.ch/cgi-bin/cmssw.cgi/CMSSW/L1TriggerConfig/L1GtConfigProducers/interface/L1GtTriggerMenuTester.h?revision=1.3&view=markup


virtual void beginJob()
{

    bookTree();
}
  //virtual bool beginRun(const edm::Run& iRun, const edm::EventSetup& iSetup)
  virtual bool beginRun( edm::Run& iRun, const edm::EventSetup& iSetup)
{
  //initialization
  return true;
}
virtual bool endRun(const edm::Run&, const edm::EventSetup&)
{
  return true;
}

virtual void bookTree()
{
  EventData.Register(tree);
  FSRph.Register(tree);
  Zs.Register(tree);
  Ws.Register(tree);
  GenWs.Register(tree);
  GenZs.Register(tree);
}


virtual bool filter(edm::Event& iEvent, const edm::EventSetup& iSetup);

void clear()
{
  EventData.EVENT	= -999;
  EventData.RUN		= -999;
  EventData.LUMI	= -999;
  EventData.Channel	= -999;
  EventData.npileup	= -999;
  EventData.rhoIso	= -999;
  //EventData.nvertex	= -999;
  EventData.weightin	= -999;
  EventData.weight	= -999;
  EventData.weightplus	= -999;
  EventData.weightminus	= -999;

  FSRph.weightFSR = 1.;

  EventData.vtx_isFake->clear();
  EventData.vtx_ndof->clear();
  EventData.vtx_z->clear();
  EventData.vtx_Rho->clear();

  Zs.Lept1_isGlobal->clear();
  Zs.Lept1_isTrker->clear();
  Zs.Lept1_pt->clear();
  Zs.Lept1_et->clear();
  Zs.Lept1_charge->clear();
  Zs.Lept1_eta->clear();
  Zs.Lept1_phi->clear();
  Zs.Lept1_px->clear();
  Zs.Lept1_py->clear();
  Zs.Lept1_pz->clear();
  Zs.Lept1_en->clear();
  Zs.Lept1_matchStations->clear();
  Zs.Lept1_dB->clear();
  Zs.Lept1_dz->clear();
  Zs.Lept1_globalNormChi2->clear();
  Zs.Lept1_muonHits->clear();
  Zs.Lept1_trkLayers->clear();
  Zs.Lept1_trackerHits->clear();
  Zs.Lept1_pixelHits->clear();
  Zs.Lept1_etaSC->clear();
  Zs.Lept1_phiSC->clear();
  Zs.Lept1_dEtaIn->clear();
  Zs.Lept1_dPhiIn->clear();
  Zs.Lept1_sigmaIEtaIEta->clear();
  Zs.Lept1_HoverE->clear();
  Zs.Lept1_fbrem->clear();
  Zs.Lept1_energyEC->clear();
  Zs.Lept1_Pnorm->clear();
  Zs.Lept1_InvEminusInvP->clear();
  Zs.Lept1_dxy->clear();
  Zs.Lept1_AEff03->clear();
  Zs.Lept1_chIso03->clear();
  Zs.Lept1_chIso04->clear();
  Zs.Lept1_nhIso03->clear();
  Zs.Lept1_nhIso04->clear();
  Zs.Lept1_phIso03->clear();
  Zs.Lept1_phIso04->clear();
  Zs.Lept1_pcIso03->clear();
  Zs.Lept1_pcIso04->clear();
  Zs.Lept1_relIsoCom03->clear();
  Zs.Lept1_relIsoCom04->clear();
  Zs.Lept1_relIsoBeta03->clear();
  Zs.Lept1_relIsoBeta04->clear();
  Zs.Lept1_relIsoRho03->clear();
  Zs.Lept1_hasConversion->clear();
  Zs.Lept1_mHits->clear();
  Zs.Lept1_SCcharge->clear();
  Zs.Lept1_TKcharge->clear();
  Zs.Lept1_GSFcharge->clear();
  Zs.Lept1_GsfCtfScPixchargeConsistentcheck->clear();

  Zs.Lept1_RelisolPtTrks03->clear();
  Zs.Lept1_RelisoEm03->clear();
  Zs.Lept1_RelisoHad03->clear();

  Zs.Lept2_isGlobal->clear();
  Zs.Lept2_isTrker->clear();
  Zs.Lept2_pt->clear();
  Zs.Lept2_et->clear();
  Zs.Lept2_charge->clear();
  Zs.Lept2_eta->clear();
  Zs.Lept2_phi->clear();
  Zs.Lept2_px->clear();
  Zs.Lept2_py->clear();
  Zs.Lept2_pz->clear();
  Zs.Lept2_en->clear();
  Zs.Lept2_matchStations->clear();
  Zs.Lept2_dB->clear();
  Zs.Lept2_dz->clear();
  Zs.Lept2_globalNormChi2->clear();
  Zs.Lept2_muonHits->clear();
  Zs.Lept2_trkLayers->clear();
  Zs.Lept2_trackerHits->clear();
  Zs.Lept2_pixelHits->clear();
  Zs.Lept2_etaSC->clear();
  Zs.Lept2_phiSC->clear();
  Zs.Lept2_dEtaIn->clear();
  Zs.Lept2_dPhiIn->clear();
  Zs.Lept2_sigmaIEtaIEta->clear();
  Zs.Lept2_HoverE->clear();
  Zs.Lept2_fbrem->clear();
  Zs.Lept2_energyEC->clear();
  Zs.Lept2_Pnorm->clear();
  Zs.Lept2_InvEminusInvP->clear();
  Zs.Lept2_dxy->clear();
  Zs.Lept2_AEff03->clear();
  Zs.Lept2_hasConversion->clear();
  Zs.Lept2_mHits->clear();
  Zs.Lept2_SCcharge->clear();
  Zs.Lept2_TKcharge->clear();
  Zs.Lept2_GSFcharge->clear();
  Zs.Lept2_GsfCtfScPixchargeConsistentcheck->clear();
  Zs.Lept2_chIso03->clear();
  Zs.Lept2_chIso04->clear();
  Zs.Lept2_nhIso03->clear();
  Zs.Lept2_nhIso04->clear();
  Zs.Lept2_phIso03->clear();
  Zs.Lept2_phIso04->clear();
  Zs.Lept2_pcIso03->clear();
  Zs.Lept2_pcIso04->clear();
  Zs.Lept2_relIsoCom03->clear();
  Zs.Lept2_relIsoCom04->clear();
  Zs.Lept2_relIsoBeta03->clear();
  Zs.Lept2_relIsoBeta04->clear();
  Zs.Lept2_relIsoRho03->clear();

  Zs.Lept2_RelisolPtTrks03->clear();
  Zs.Lept2_RelisoEm03->clear();
  Zs.Lept2_RelisoHad03->clear();

  Zs.Lept1_genIdxMatch->clear();
  Zs.Lept1_genDeltaR->clear();
  Zs.Lept1_genDPtRel->clear();
  Zs.Lept2_genIdxMatch->clear();
  Zs.Lept2_genDeltaR->clear();
  Zs.Lept2_genDPtRel->clear();


  Zs.diLeptVtxProb->clear();
  Zs.ZMass->clear();
  Zs.phi->clear();
  Zs.eta->clear();
  Zs.pt->clear();
  Zs.px->clear();
  Zs.py->clear();
  Zs.pz->clear();
  Zs.Neut_pt->clear();
  Zs.Neut_phi->clear();
  Zs.Neut_px->clear();
  Zs.Neut_py->clear();
  Zs.Sign->clear();

  Ws.Lept1_isGlobal->clear();
  Ws.Lept1_isTrker->clear();
  Ws.Lept1_pt->clear();
  Ws.Lept1_et->clear();
  Ws.Lept1_charge->clear();
  Ws.Lept1_eta->clear();
  Ws.Lept1_phi->clear();
  Ws.Lept1_px->clear();
  Ws.Lept1_py->clear();
  Ws.Lept1_pz->clear();
  Ws.Lept1_en->clear();
  Ws.Lept1_matchStations->clear();
  Ws.Lept1_dB->clear();
  Ws.Lept1_dz->clear();
  Ws.Lept1_globalNormChi2->clear();
  Ws.Lept1_muonHits->clear();
  Ws.Lept1_trkLayers->clear();
  Ws.Lept1_trackerHits->clear();
  Ws.Lept1_pixelHits->clear();
  Ws.Lept1_etaSC->clear();
  Ws.Lept1_phiSC->clear();
  Ws.Lept1_dEtaIn->clear();
  Ws.Lept1_dPhiIn->clear();
  Ws.Lept1_sigmaIEtaIEta->clear();
  Ws.Lept1_HoverE->clear();
  Ws.Lept1_fbrem->clear();
  Ws.Lept1_energyEC->clear();
  Ws.Lept1_Pnorm->clear();
  Ws.Lept1_InvEminusInvP->clear();
  Ws.Lept1_dxy->clear();
  Ws.Lept1_AEff03->clear();
  Ws.Lept1_chIso03->clear();
  Ws.Lept1_chIso04->clear();
  Ws.Lept1_nhIso03->clear();
  Ws.Lept1_nhIso04->clear();
  Ws.Lept1_phIso03->clear();
  Ws.Lept1_phIso04->clear();
  Ws.Lept1_pcIso03->clear();
  Ws.Lept1_pcIso04->clear();
  Ws.Lept1_relIsoCom03->clear();
  Ws.Lept1_relIsoCom04->clear();
  Ws.Lept1_relIsoBeta03->clear();
  Ws.Lept1_relIsoBeta04->clear();
  Ws.Lept1_relIsoRho03->clear();
  Ws.Lept1_hasConversion->clear();
  Ws.Lept1_mHits->clear();
  Ws.Lept1_SCcharge->clear();
  Ws.Lept1_TKcharge->clear();
  Ws.Lept1_GSFcharge->clear();
  Ws.Lept1_GsfCtfScPixchargeConsistentcheck->clear();

  Ws.Lept1_RelisolPtTrks03->clear();
  Ws.Lept1_RelisoEm03->clear();
  Ws.Lept1_RelisoHad03->clear();

  Ws.W_invm->clear();
  Ws.Neut_pt->clear();
  Ws.Neut_phi->clear();
  Ws.Neut_px->clear();
  Ws.Neut_py->clear();
  Ws.W_pt->clear();
  Ws.W_eta->clear();
  Ws.W_phi->clear();
  Ws.W_px->clear();
  Ws.W_py->clear();
  Ws.W_pz->clear();
  Ws.W_Mt->clear();
  Ws.W_Acop->clear();
  Ws.W_Charge->clear();

  GenWs.Born_nLepts->clear();
  GenWs.Born_id->clear();
  GenWs.Born_status->clear();
  GenWs.Born_mass->clear();
  GenWs.Born_px->clear();
  GenWs.Born_py->clear();
  GenWs.Born_pz->clear();
  GenWs.Born_pt->clear();
  GenWs.Born_eta->clear();
  GenWs.Born_phi->clear();

  GenWs.BornLept1_id->clear();
  GenWs.BornLept1_status->clear();
  GenWs.BornLept1_px->clear();
  GenWs.BornLept1_py->clear();
  GenWs.BornLept1_pz->clear();
  GenWs.BornLept1_en->clear();
  GenWs.BornLept1_pt->clear();
  GenWs.BornLept1_et->clear();
  GenWs.BornLept1_charge->clear();
  GenWs.BornLept1_eta->clear();
  GenWs.BornLept1_phi->clear();
  GenWs.BornLept2_id->clear();
  GenWs.BornLept2_status->clear();
  GenWs.BornLept2_px->clear();
  GenWs.BornLept2_py->clear();
  GenWs.BornLept2_pz->clear();
  GenWs.BornLept2_en->clear();
  GenWs.BornLept2_pt->clear();
  GenWs.BornLept2_et->clear();
  GenWs.BornLept2_charge->clear();
  GenWs.BornLept2_eta->clear();
  GenWs.BornLept2_phi->clear();

  GenWs.PostLept1_id->clear();
  GenWs.PostLept1_status->clear();
  GenWs.PostLept1_px->clear();
  GenWs.PostLept1_py->clear();
  GenWs.PostLept1_pz->clear();
  GenWs.PostLept1_en->clear();
  GenWs.PostLept1_pt->clear();
  GenWs.PostLept1_et->clear();
  GenWs.PostLept1_charge->clear();
  GenWs.PostLept1_eta->clear();
  GenWs.PostLept1_phi->clear();
  GenWs.PostLept2_id->clear();
  GenWs.PostLept2_status->clear();
  GenWs.PostLept2_px->clear();
  GenWs.PostLept2_py->clear();
  GenWs.PostLept2_pz->clear();
  GenWs.PostLept2_en->clear();
  GenWs.PostLept2_pt->clear();
  GenWs.PostLept2_et->clear();
  GenWs.PostLept2_charge->clear();
  GenWs.PostLept2_eta->clear();
  GenWs.PostLept2_phi->clear();

  GenZs.nLepts->clear();
  GenZs.id->clear();
  GenZs.status->clear();
  GenZs.mass->clear();
  GenZs.px->clear();
  GenZs.py->clear();
  GenZs.pz->clear();
  GenZs.pt->clear();
  GenZs.eta->clear();
  GenZs.phi->clear();
  GenZs.Lept1_id->clear();
  GenZs.Lept1_status->clear();
  GenZs.Lept1_px->clear();
  GenZs.Lept1_py->clear();
  GenZs.Lept1_pz->clear();
  GenZs.Lept1_en->clear();
  GenZs.Lept1_pt->clear();
  GenZs.Lept1_et->clear();
  GenZs.Lept1_charge->clear();
  GenZs.Lept1_eta->clear();
  GenZs.Lept1_phi->clear();
  GenZs.Lept2_id->clear();
  GenZs.Lept2_status->clear();
  GenZs.Lept2_px->clear();
  GenZs.Lept2_py->clear();
  GenZs.Lept2_pz->clear();
  GenZs.Lept2_en->clear();
  GenZs.Lept2_pt->clear();
  GenZs.Lept2_et->clear();
  GenZs.Lept2_charge->clear();
  GenZs.Lept2_eta->clear();
  GenZs.Lept2_phi->clear();

  Ws.Lept1_genIdxMatch->clear();
  Ws.Lept1_genDeltaR->clear();
  Ws.Lept1_genDPtRel->clear();

}
  virtual bool endLuminosityBlock(edm::LuminosityBlock & lumi, const edm::EventSetup & setup)
{
  //cout<<"end lumi "<<endl;
    if(useEventCounter_){
      for(unsigned int i=0;i<filters_.size();++i) {
        std::string name = filters_[i];
        edm::Handle<edm::MergeableCounter> numEventsCounter;
        lumi.getByLabel(name, numEventsCounter);
        if( numEventsCounter.isValid()){
          tmp->AddBinContent(i+1, numEventsCounter->value);
          tmp->GetXaxis()->SetBinLabel(i+1,filters_[i].c_str());
        }
      }
    }
    return true;
}

 
virtual bool HasDaughter(reco::GenParticleRef genPtcl, int id)
{
  for(unsigned int i(0);i<genPtcl->numberOfDaughters(); i++)
  {
    if(genPtcl->daughterRef(i)->pdgId() == id) return true;
  }
  return false;
}

virtual reco::GenParticleRef FindDaughter(reco::GenParticleRef mom,int id)
{
  reco::GenParticleRef daughter;
  for( unsigned int i(0);i<mom->numberOfDaughters();i++)
  {
    daughter = mom->daughterRef(i);
    if(daughter->pdgId() == id) return daughter;
  }
  return daughter;
}
  

virtual void GetGenInfoW(edm::Event &iEvent, const edm::EventSetup& iSetup)
{
  if (isRD) return;
  //if (iEvent.isRealData()) return;
  GenInfo PostWinfo;
  PostWinfo.id = 0;PostWinfo.Lept1_id = 0;PostWinfo.Lept2_id=0;
  PostWinfo.status=-999;PostWinfo.Lept1_status=-999;PostWinfo.Lept2_status=-999;
  PostWinfo.mass=-999;
  PostWinfo.px=-999;PostWinfo.py=-999;PostWinfo.pz=-999;PostWinfo.pt=-999;
  PostWinfo.Lept1_px=-999;PostWinfo.Lept1_py=-999;PostWinfo.Lept1_pz=-999;PostWinfo.Lept1_en=-999;PostWinfo.Lept1_pt=-999;PostWinfo.Lept1_et=-999;PostWinfo.Lept1_charge=-999;
  PostWinfo.Lept2_px=-999;PostWinfo.Lept2_py=-999;PostWinfo.Lept2_pz=-999;PostWinfo.Lept2_en=-999;PostWinfo.Lept2_pt=-999;PostWinfo.Lept2_et=-999;PostWinfo.Lept2_charge=-999;
  PostWinfo.eta=-999;PostWinfo.phi=-999;
  PostWinfo.Lept1_eta=-999;PostWinfo.Lept1_phi=-999;
  PostWinfo.Lept2_eta=-999;PostWinfo.Lept2_phi=-999;
  
  GenInfo BornWinfo;
  BornWinfo.id = 0;BornWinfo.Lept1_id = 0;BornWinfo.Lept2_id=0;
  BornWinfo.status=-999;BornWinfo.Lept1_status=-999;BornWinfo.Lept2_status=-999;
  BornWinfo.mass=-999;
  BornWinfo.px=-999;BornWinfo.py=-999;BornWinfo.pz=-999;BornWinfo.pt=-999;
  BornWinfo.Lept1_px=-999;BornWinfo.Lept1_py=-999;BornWinfo.Lept1_pz=-999;BornWinfo.Lept1_en=-999;BornWinfo.Lept1_pt=-999;BornWinfo.Lept1_et=-999;BornWinfo.Lept1_charge=-999;
  BornWinfo.Lept2_px=-999;BornWinfo.Lept2_py=-999;BornWinfo.Lept2_pz=-999;BornWinfo.Lept2_en=-999;BornWinfo.Lept2_pt=-999;BornWinfo.Lept2_et=-999;BornWinfo.Lept2_charge=-999;
  BornWinfo.eta=-999;BornWinfo.phi=-999;
  BornWinfo.Lept1_eta=-999;BornWinfo.Lept1_phi=-999;
  BornWinfo.Lept2_eta=-999;BornWinfo.Lept2_phi=-999;

  edm::Handle<reco::GenParticleCollection> genParticles;
  iEvent.getByLabel(genParticlesLabel_, genParticles);
  unsigned int gensize = genParticles->size();
  int nLepts(0);

  for (unsigned int i = 0; i<gensize; ++i) {
    const reco::GenParticle& boson = (*genParticles)[i];
    // Pythia 0 (null entry),
    // 1 (existing entry not decayed or fragmented, represents the final state as given by the generator)
    // 2 (decayed ptcl or parton produced in shower)
    // 3 (identifies the "hard part" of the interaction,
    // i.e. the partons that are used in the matrix
    // element calculation, including immediate decays of resonances.)
    //                       W+ = 24
    if( (abs(boson.pdgId()) == 24 ) && (boson.status() == 3))
    {
      acceptFT = true;

      nLepts = 0;
      BornWinfo.id	= boson.pdgId();
      BornWinfo.status	= boson.status();
      BornWinfo.mass	= boson.mass();
      BornWinfo.px	= boson.px();
      BornWinfo.py	= boson.py();
      BornWinfo.pz 	= boson.pz();
      BornWinfo.pt 	= boson.pt();
      BornWinfo.eta 	= boson.eta();
      BornWinfo.phi 	= boson.phi();
      //cout<<"W boson number: "<<++BosonN<<endl;
      // Loop through boson's daughters and look for leptons
      for(unsigned int j=0; j<boson.numberOfDaughters(); j++)
      {
	reco::GenParticleRef daughter = boson.daughterRef(j);
	//cout<<"daughter Id: "<<daughter->pdgId()<<endl;
	if( daughter->pdgId() == boson.pdgId())continue;

	nLepts++;
	// Fill Born Level Leptons
	if(nLepts == 1){
	  BornWinfo.Lept1_id    =daughter->pdgId();
	  BornWinfo.Lept1_status=daughter->status();
	  BornWinfo.Lept1_px	=daughter->px();
	  BornWinfo.Lept1_py	=daughter->py();
	  BornWinfo.Lept1_pz	=daughter->pz();
	  BornWinfo.Lept1_en	=daughter->energy();
	  BornWinfo.Lept1_pt	=daughter->pt();
          BornWinfo.Lept1_et    =daughter->et();
          BornWinfo.Lept1_charge =daughter->charge();
	  BornWinfo.Lept1_eta	=daughter->eta();
	  BornWinfo.Lept1_phi	=daughter->phi();
	}else if(nLepts == 2)
	{
	  BornWinfo.Lept2_id	=daughter->pdgId();
	  BornWinfo.Lept2_status=daughter->status();
	  BornWinfo.Lept2_px	=daughter->px();
	  BornWinfo.Lept2_py	=daughter->py();
	  BornWinfo.Lept2_pz	=daughter->pz();
	  BornWinfo.Lept2_en	=daughter->energy();
	  BornWinfo.Lept2_pt	=daughter->pt();
          BornWinfo.Lept2_et    =daughter->et();
          BornWinfo.Lept2_charge=daughter->charge();
	  BornWinfo.Lept2_eta	=daughter->eta();
	  BornWinfo.Lept2_phi	=daughter->phi();
	}
	// traverse down the same id daughter lepton tree
	while(HasDaughter(daughter,daughter->pdgId()) && daughter->status() != 1)
	  daughter = FindDaughter(daughter,daughter->pdgId());

	if(nLepts == 1){
	  PostWinfo.Lept1_id    =daughter->pdgId();
	  PostWinfo.Lept1_status=daughter->status();
	  PostWinfo.Lept1_px	=daughter->px();
	  PostWinfo.Lept1_py	=daughter->py();
	  PostWinfo.Lept1_pz	=daughter->pz();
	  PostWinfo.Lept1_en	=daughter->energy();
	  PostWinfo.Lept1_pt	=daughter->pt();
          PostWinfo.Lept1_et    =daughter->et();
          PostWinfo.Lept1_charge=daughter->charge();
	  PostWinfo.Lept1_eta	=daughter->eta();
	  PostWinfo.Lept1_phi	=daughter->phi();
	}else if(nLepts == 2)
	{
	  PostWinfo.Lept2_id	=daughter->pdgId();
	  PostWinfo.Lept2_status=daughter->status();
	  PostWinfo.Lept2_px	=daughter->px();
	  PostWinfo.Lept2_py	=daughter->py();
	  PostWinfo.Lept2_pz	=daughter->pz();
	  PostWinfo.Lept2_en	=daughter->energy();
	  PostWinfo.Lept2_pt	=daughter->pt();
          PostWinfo.Lept2_et    =daughter->et();
          PostWinfo.Lept2_charge=daughter->charge();
	  PostWinfo.Lept2_eta	=daughter->eta();
	  PostWinfo.Lept2_phi	=daughter->phi();

	}
	//cout<<"daughter id: "<<daughter->pdgId()<<" st.: "<<daughter->status()<<endl;
      }//idx j
      //cout<<"The number of leptons from W status3 are not 2=============="<<endl;
      //Find the last step boson from a boson with status 3.
      //Then let find the leptons
      if(nLepts < 2)
      {
	reco::GenParticleRef daughter;
	for(unsigned int l(0);l<boson.numberOfDaughters();l++)
	{
	  daughter = boson.daughterRef(l);
	  if(daughter->pdgId() != boson.pdgId() )continue;
	  //The daughter boson with the same pdgId
	  while(HasDaughter(daughter,boson.pdgId()))
	      daughter = FindDaughter(daughter,daughter->pdgId());
	  nLepts = 0;
	  for( unsigned int m(0); daughter->numberOfDaughters();m++)
	  {
	    if(daughter->daughterRef(m)->pdgId() == boson.pdgId())continue;
	    //traverse down daughter lepton tree
	    nLepts++;
	    while(HasDaughter(daughter,daughter->pdgId()) && daughter->status() != 1)
		daughter = FindDaughter(daughter,daughter->pdgId());
	    if(nLepts == 1)
	    {
	      PostWinfo.Lept1_id	=daughter->pdgId();
	      PostWinfo.Lept1_status	=daughter->status();
	      PostWinfo.Lept1_px	=daughter->px();
	      PostWinfo.Lept1_py	=daughter->py();
	      PostWinfo.Lept1_pz	=daughter->pz();
	      PostWinfo.Lept1_en	=daughter->energy();
	      PostWinfo.Lept1_pt	=daughter->pt();
              PostWinfo.Lept1_et        =daughter->et();
              PostWinfo.Lept1_charge    =daughter->charge();
	      PostWinfo.Lept1_eta	=daughter->eta();
	      PostWinfo.Lept1_phi	=daughter->phi();
	    }else if(nLepts == 2)
	    {
	      PostWinfo.Lept2_id	=daughter->pdgId();
	      PostWinfo.Lept2_status	=daughter->status();
	      PostWinfo.Lept2_px	=daughter->px();
	      PostWinfo.Lept2_py	=daughter->py();
	      PostWinfo.Lept2_pz	=daughter->pz();
	      PostWinfo.Lept2_en	=daughter->energy();
	      PostWinfo.Lept2_pt	=daughter->pt();
              PostWinfo.Lept2_et        =daughter->et();
              PostWinfo.Lept2_charge    =daughter->charge();
	      PostWinfo.Lept2_eta	=daughter->eta();
	      PostWinfo.Lept2_phi	=daughter->phi();
	    }
	  }
	}
      }//if nLepts <2

      if( nLepts != 2)
        cout<<"Stange case Gen W lepton N is "<<nLepts<<endl;

      GenWs.Born_nLepts		->push_back(nLepts);
      GenWs.Born_id		->push_back(BornWinfo.id);
      GenWs.Born_status		->push_back(BornWinfo.status);
      GenWs.Born_mass		->push_back(BornWinfo.mass);
      GenWs.Born_px		->push_back(BornWinfo.px);
      GenWs.Born_py		->push_back(BornWinfo.py);
      GenWs.Born_pz		->push_back(BornWinfo.pz);
      GenWs.Born_pt		->push_back(BornWinfo.pt);
      GenWs.Born_eta		->push_back(BornWinfo.eta);
      GenWs.Born_phi		->push_back(BornWinfo.phi);

      GenWs.BornLept1_id	->push_back(BornWinfo.Lept1_id);
      GenWs.BornLept1_status	->push_back(BornWinfo.Lept1_status);
      GenWs.BornLept1_px	->push_back(BornWinfo.Lept1_px);
      GenWs.BornLept1_py	->push_back(BornWinfo.Lept1_py);
      GenWs.BornLept1_pz	->push_back(BornWinfo.Lept1_pz);
      GenWs.BornLept1_en	->push_back(BornWinfo.Lept1_en);
      GenWs.BornLept1_pt	->push_back(BornWinfo.Lept1_pt);
      GenWs.BornLept1_et    	->push_back(BornWinfo.Lept1_et);
      GenWs.BornLept1_charge   	->push_back(BornWinfo.Lept1_charge);
      GenWs.BornLept1_eta	->push_back(BornWinfo.Lept1_eta);
      GenWs.BornLept1_phi	->push_back(BornWinfo.Lept1_phi);
      GenWs.BornLept2_id	->push_back(BornWinfo.Lept2_id);
      GenWs.BornLept2_status	->push_back(BornWinfo.Lept2_status);
      GenWs.BornLept2_px	->push_back(BornWinfo.Lept2_px);
      GenWs.BornLept2_py	->push_back(BornWinfo.Lept2_py);
      GenWs.BornLept2_pz	->push_back(BornWinfo.Lept2_pz);
      GenWs.BornLept2_en	->push_back(BornWinfo.Lept2_en);
      GenWs.BornLept2_pt	->push_back(BornWinfo.Lept2_pt);
      GenWs.BornLept2_et    	->push_back(BornWinfo.Lept2_et);
      GenWs.BornLept2_charge   	->push_back(BornWinfo.Lept2_charge);
      GenWs.BornLept2_eta	->push_back(BornWinfo.Lept2_eta);
      GenWs.BornLept2_phi	->push_back(BornWinfo.Lept2_phi);

      GenWs.PostLept1_id	->push_back(PostWinfo.Lept1_id);
      GenWs.PostLept1_status	->push_back(PostWinfo.Lept1_status);
      GenWs.PostLept1_px	->push_back(PostWinfo.Lept1_px);
      GenWs.PostLept1_py	->push_back(PostWinfo.Lept1_py);
      GenWs.PostLept1_pz	->push_back(PostWinfo.Lept1_pz);
      GenWs.PostLept1_en	->push_back(PostWinfo.Lept1_en);
      GenWs.PostLept1_pt	->push_back(PostWinfo.Lept1_pt);
      GenWs.PostLept1_et    	->push_back(PostWinfo.Lept1_et);
      GenWs.PostLept1_charge   	->push_back(PostWinfo.Lept1_charge);
      GenWs.PostLept1_eta	->push_back(PostWinfo.Lept1_eta);
      GenWs.PostLept1_phi	->push_back(PostWinfo.Lept1_phi);
      GenWs.PostLept2_id	->push_back(PostWinfo.Lept2_id);
      GenWs.PostLept2_status	->push_back(PostWinfo.Lept2_status);
      GenWs.PostLept2_px	->push_back(PostWinfo.Lept2_px);
      GenWs.PostLept2_py	->push_back(PostWinfo.Lept2_py);
      GenWs.PostLept2_pz	->push_back(PostWinfo.Lept2_pz);
      GenWs.PostLept2_en	->push_back(PostWinfo.Lept2_en);
      GenWs.PostLept2_pt	->push_back(PostWinfo.Lept2_pt);
      GenWs.PostLept2_et    	->push_back(PostWinfo.Lept2_et);
      GenWs.PostLept2_charge   	->push_back(PostWinfo.Lept2_charge);
      GenWs.PostLept2_eta	->push_back(PostWinfo.Lept2_eta);
      GenWs.PostLept2_phi	->push_back(PostWinfo.Lept2_phi);
    }//W status 3
  }//GenPtcls
}
virtual void GetGenInfoZ(edm::Event &iEvent, const edm::EventSetup& iSetup)
{
  if(isRD) return;
  GenInfo GenZinfo;
  GenZinfo.id = 0;GenZinfo.Lept1_id = 0;GenZinfo.Lept2_id=0;
  GenZinfo.status=-999;GenZinfo.Lept1_status=-999;GenZinfo.Lept2_status=-999;
  GenZinfo.mass=-999;
  GenZinfo.px=-999;GenZinfo.py=-999;GenZinfo.pz=-999;GenZinfo.pt=-999;
  GenZinfo.Lept1_px=-999;GenZinfo.Lept1_py=-999;GenZinfo.Lept1_pz=-999;GenZinfo.Lept1_en=-999;GenZinfo.Lept1_pt=-999;GenZinfo.Lept1_et=-999;GenZinfo.Lept1_charge=-999;
  GenZinfo.Lept2_px=-999;GenZinfo.Lept2_py=-999;GenZinfo.Lept2_pz=-999;GenZinfo.Lept2_en=-999;GenZinfo.Lept2_pt=-999;GenZinfo.Lept2_et=-999;GenZinfo.Lept2_charge=-999;
  GenZinfo.eta=-999;GenZinfo.phi=-999;
  GenZinfo.Lept1_eta=-999;GenZinfo.Lept1_phi=-999;
  GenZinfo.Lept2_eta=-999;GenZinfo.Lept2_phi=-999;

  edm::Handle<reco::GenParticleCollection> genParticles;
  iEvent.getByLabel(genParticlesLabel_, genParticles);
  unsigned int gensize = genParticles->size();
  int nLepts(0);

  for (unsigned int i = 0; i<gensize; ++i) {
    const reco::GenParticle& boson = (*genParticles)[i];
    // Pythia 0 (null entry),
    // 1 (existing entry not decayed or fragmented, represents the final state as given by the generator)
    // 2 (decayed ptcl or parton produced in shower)
    // 3 (identifies the "hard part" of the interaction, i.e. the partons that are used in the matrix
    // element calculation, including immediate decays of resonances.)
    //                       Z0 = 23 ,Gamma = 22

    if( ((abs(boson.pdgId()) == 23) || (abs(boson.pdgId()) == 22)) && (boson.status() == 3))
    {
      acceptFT = true;
      nLepts = 0;
      GenZinfo.id	= boson.pdgId();
      GenZinfo.status	= boson.status();
      GenZinfo.mass	= boson.mass();
      GenZinfo.px	= boson.px();
      GenZinfo.py	= boson.py();
      GenZinfo.pz 	= boson.pz();
      GenZinfo.pt 	= boson.pt();
      GenZinfo.eta 	= boson.eta();
      GenZinfo.phi 	= boson.phi();
      //Loop through boson's daughters and look for leptons
      for(unsigned int j(0); j<boson.numberOfDaughters();j++)
      {
	reco::GenParticleRef daughter = boson.daughterRef(j);
	if( abs(daughter->pdgId()) != 11 &&
	    abs(daughter->pdgId()) != 12 &&
	    abs(daughter->pdgId()) != 13 &&
	    abs(daughter->pdgId()) != 14 &&
	    abs(daughter->pdgId()) != 15 &&
	    abs(daughter->pdgId()) != 16 ) continue;
	nLepts++;
	// traverse down daughter lepton tree
	while(HasDaughter(daughter,daughter->pdgId()) && daughter->status() != 1)
	    daughter=FindDaughter(daughter,daughter->pdgId());
	if(nLepts == 1){
	  GenZinfo.Lept1_id     =daughter->pdgId();
	  GenZinfo.Lept1_status =daughter->status();
	  GenZinfo.Lept1_px	=daughter->px();
	  GenZinfo.Lept1_py	=daughter->py();
	  GenZinfo.Lept1_pz	=daughter->pz();
	  GenZinfo.Lept1_en	=daughter->energy();
	  GenZinfo.Lept1_pt	=daughter->pt();
          GenZinfo.Lept1_et     =daughter->et();
          GenZinfo.Lept1_charge =daughter->charge();
	  GenZinfo.Lept1_eta	=daughter->eta();
	  GenZinfo.Lept1_phi	=daughter->phi();
	}else if(nLepts == 2)
	{
	  GenZinfo.Lept2_id	=daughter->pdgId();
	  GenZinfo.Lept2_status	=daughter->status();
	  GenZinfo.Lept2_px	=daughter->px();
	  GenZinfo.Lept2_py	=daughter->py();
	  GenZinfo.Lept2_pz	=daughter->pz();
	  GenZinfo.Lept2_en	=daughter->energy();
	  GenZinfo.Lept2_pt	=daughter->pt();
          GenZinfo.Lept2_et     =daughter->et();
          GenZinfo.Lept2_charge =daughter->charge();
	  GenZinfo.Lept2_eta	=daughter->eta();
	  GenZinfo.Lept2_phi	=daughter->phi();
	}
      }//boson daughters
      if(nLepts !=2 )
        cout<<"Stange case Gen Z lepton N is "<<nLepts<<endl;

      GenZs.nLepts	->push_back(nLepts);
      GenZs.id		->push_back(GenZinfo.id);
      GenZs.status	->push_back(GenZinfo.status);
      GenZs.mass	->push_back(GenZinfo.mass);
      GenZs.px		->push_back(GenZinfo.px);
      GenZs.py		->push_back(GenZinfo.py);
      GenZs.pz		->push_back(GenZinfo.pz);
      GenZs.pt		->push_back(GenZinfo.pt);
      GenZs.eta		->push_back(GenZinfo.eta);
      GenZs.phi		->push_back(GenZinfo.phi);

      GenZs.Lept1_id	->push_back(GenZinfo.Lept1_id);
      GenZs.Lept1_status->push_back(GenZinfo.Lept1_status);
      GenZs.Lept1_px	->push_back(GenZinfo.Lept1_px);
      GenZs.Lept1_py	->push_back(GenZinfo.Lept1_py);
      GenZs.Lept1_pz	->push_back(GenZinfo.Lept1_pz);
      GenZs.Lept1_en	->push_back(GenZinfo.Lept1_en);
      GenZs.Lept1_pt	->push_back(GenZinfo.Lept1_pt);
      GenZs.Lept1_et	->push_back(GenZinfo.Lept1_et);
      GenZs.Lept1_charge->push_back(GenZinfo.Lept1_charge);
      GenZs.Lept1_eta	->push_back(GenZinfo.Lept1_eta);
      GenZs.Lept1_phi	->push_back(GenZinfo.Lept1_phi);
      
      GenZs.Lept2_id	->push_back(GenZinfo.Lept2_id);
      GenZs.Lept2_status->push_back(GenZinfo.Lept2_status);
      GenZs.Lept2_px	->push_back(GenZinfo.Lept2_px);
      GenZs.Lept2_py	->push_back(GenZinfo.Lept2_py);
      GenZs.Lept2_pz	->push_back(GenZinfo.Lept2_pz);
      GenZs.Lept2_en	->push_back(GenZinfo.Lept2_en);
      GenZs.Lept2_pt	->push_back(GenZinfo.Lept2_pt);
      GenZs.Lept2_et	->push_back(GenZinfo.Lept2_et);
      GenZs.Lept2_charge->push_back(GenZinfo.Lept2_charge);
      GenZs.Lept2_eta	->push_back(GenZinfo.Lept2_eta);
      GenZs.Lept2_phi	->push_back(GenZinfo.Lept2_phi);
    }//Drell-Yan
  }//genPtcls
}

virtual void GetFSRInfoW(edm::Event &iEvent, const edm::EventSetup& iSetup)
{
  if(isRD) return;

  double weightWFSR = 1.;

  edm::Handle<reco::GenParticleCollection> genParticles;
  iEvent.getByLabel(genParticlesLabel_, genParticles);
  
  unsigned int gensize = genParticles->size();
  for (unsigned int i = 0; i<gensize; ++i) {
    const reco::GenParticle& lepton = (*genParticles)[i];
    if (lepton.status()!=3) continue;
    int leptonId = lepton.pdgId();
    if(Channel == "Muon")
      if (fabs(leptonId)!=13) continue;
      else if(Channel == "Electron")
	if (fabs(leptonId)!=11) continue;
    if (lepton.numberOfMothers()!=1) continue;
    const reco::Candidate *boson = lepton.mother();
    int bosonId = fabs(boson->pdgId());
    if (bosonId!=24) continue;
    acceptFT = true;
    double bosonMass = boson->mass();
    double leptonMass = lepton.mass();
    double leptonEnergy = lepton.energy();
    double cosLeptonTheta = cos(lepton.theta());
    double sinLeptonTheta = sin(lepton.theta());
    double leptonPhi = lepton.phi();
    int trueKey = i;
    if (lepton.numberOfDaughters()==0) {
      continue;
    } else if (lepton.numberOfDaughters()==1) {
      int otherleptonKey = lepton.daughterRef(0).key();
      const reco::GenParticle& otherlepton = (*genParticles)[otherleptonKey];
      if (otherlepton.pdgId()!=leptonId) continue;
      if (otherlepton.numberOfDaughters()<=1) continue;
      trueKey = otherleptonKey;
    }
    const reco::GenParticle& trueLepton = (*genParticles)[trueKey];
    unsigned int nDaughters = trueLepton.numberOfDaughters();
    
    for (unsigned int j = 0; j<nDaughters; ++j) {
      const reco::Candidate * photon = trueLepton.daughter(j);
      if (photon->pdgId()!=22) continue;
      double photonEnergy = photon->energy();
      double cosPhotonTheta = cos(photon->theta());
      double sinPhotonTheta = sin(photon->theta());
      double photonPhi = photon->phi();
      double costheta = sinLeptonTheta*sinPhotonTheta*cos(leptonPhi-photonPhi)
	+ cosLeptonTheta*cosPhotonTheta;

      if (bosonId==24) {
	double betaLepton = sqrt(1-pow(leptonMass/leptonEnergy,2));
	double delta = - 8*photonEnergy *(1-betaLepton*costheta)
	  / pow(bosonMass,3) 
	  / (1-pow(leptonMass/bosonMass,2))
	  / (4-pow(leptonMass/bosonMass,2))
	  * leptonEnergy * (pow(leptonMass,2)/bosonMass+2*photonEnergy);
	  weightWFSR *= (1 + delta);
      }
      weightWFSR *= alphaRatio(photonEnergy*sqrt(1-pow(costheta,2)));
      FSRph.weightFSR = weightWFSR;
    }
  }
}

virtual double alphaRatio(double pt) {

      double pigaga = 0.;

      // Leptonic contribution (just one loop, precise at < 0.3% level)
      const double alphapi = 1/137.036/M_PI;
      const double mass_e = 0.0005;
      const double mass_mu = 0.106;
      const double mass_tau = 1.777;
      const double mass_Z = 91.2;
      if (pt>mass_e) pigaga += alphapi * (2*log(pt/mass_e)/3.-5./9.);
      if (pt>mass_mu) pigaga += alphapi * (2*log(pt/mass_mu)/3.-5./9.);
      if (pt>mass_tau) pigaga += alphapi * (2*log(pt/mass_tau)/3.-5./9.);

      // Hadronic vaccum contribution
      // Using simple effective parametrization from Physics Letters B 513 (2001) 46.
      // Top contribution neglected
      double A = 0.; 
      double B = 0.; 
      double C = 0.; 
      if (pt<0.7) {
            A = 0.0; B = 0.0023092; C = 3.9925370;
      } else if (pt<2.0) {
            A = 0.0; B = 0.0022333; C = 4.2191779;
      } else if (pt<4.0) {
            A = 0.0; B = 0.0024402; C = 3.2496684;
      } else if (pt<10.0) {
            A = 0.0; B = 0.0027340; C = 2.0995092;
      } else if (pt<mass_Z) {
            A = 0.0010485; B = 0.0029431; C = 1.0;
      } else if (pt<10000.) {
            A = 0.0012234; B = 0.0029237; C = 1.0;
      } else {
            A = 0.0016894; B = 0.0028984; C = 1.0;
      }
      pigaga += A + B*log(1.+C*pt*pt);

      // Done
      return 1./(1.-pigaga);
}
};
