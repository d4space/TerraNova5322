// $Id: ZNtupleMaker.h,v 1.17 2013/09/13 00:09:33 salee Exp $
//
//

// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"

#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Framework/interface/LuminosityBlock.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "CommonTools/Utils/interface/StringObjectFunction.h"
#include "DataFormats/PatCandidates/interface/LookupTableRecord.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/METReco/interface/PFMET.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/METReco/interface/PFMETCollection.h"
#include "DataFormats/METReco/interface/GenMETCollection.h"
#include "DataFormats/METReco/interface/CaloMETCollection.h"
#include "DataFormats/JetReco/interface/CaloJetCollection.h"

#include "DataFormats/Candidate/interface/VertexCompositeCandidate.h"
#include "DataFormats/Candidate/interface/VertexCompositeCandidateFwd.h"
#include "MagneticField/Engine/interface/MagneticField.h"
#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"
#include "RecoVertex/KalmanVertexFit/interface/KalmanVertexFitter.h"
#include "RecoVertex/VertexTools/interface/InvariantMassFromVertex.h"
#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"
#include "TrackingTools/Records/interface/TransientTrackRecord.h"
#include "DataFormats/RecoCandidate/interface/RecoCandidate.h"
#include "TrackingTools/TransientTrack/interface/TransientTrack.h"

#include "DataFormats/Common/interface/MergeableCounter.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositDirection.h"
#include "DataFormats/RecoCandidate/interface/IsoDeposit.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositVetos.h"
#include "DataFormats/PatCandidates/interface/Isolation.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "PhysicsTools/Utilities/interface/LumiReWeighting.h"

//EGamma
//#include "EgammaAnalysis/ElectronTools/interface/ElectronEffectiveArea.h"
#include "EgammaAnalysis/ElectronTools/interface/ElectronEffectiveArea.h"
#include "RecoEgamma/EgammaTools/interface/ConversionTools.h"

#include "DataFormats/BeamSpot/interface/BeamSpot.h"

//Triggers
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"

// L1 Trigger 
#include "CondFormats/L1TObjects/interface/L1GtTriggerMenu.h"
#include "CondFormats/DataRecord/interface/L1GtTriggerMenuRcd.h"
#include "CondFormats/DataRecord/interface/EcalIntercalibConstantsRcd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetupFwd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetup.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"

#include "CondFormats/L1TObjects/interface/L1GtAlgorithm.h" //for L1
#include <map> //L1
#include <string> // L1

#include "TerraNova5322/DataFormats/interface/Lepton.h"
#include "TerraNova5322/DataFormats/interface/ZCandidate.h"
//#include "TerraNova5322/DataFormats/interface/TTbarGenEvent.h"
//#include "TerraNova5322/DataFormats/interface/TTbarMass.h"
#include "TerraNova5322/DataFormats/interface/WLeptNeuCand.h"
#include "TerraNova5322/DataFormats/interface/METCandidate.h"
//#include "TerraNova5322/DataFormats/interface/Maos.h"

#include "TerraNova5322/NtupleMaker/interface/ZBranchVars.h"
#include "TerraNova5322/NtupleMaker/interface/BasicBranchVars.h"
#include "TerraNova5322/NtupleMaker/interface/MEtBranchVars.h"

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
using namespace isodeposit;

//template<typename T1, typename T2>
class ZNtupleMaker : public edm::EDAnalyzer{
 public:
  explicit ZNtupleMaker(const edm::ParameterSet& iConfig);
  ElectronEffectiveArea::ElectronEffectiveAreaTarget EAtarget;
  ~ZNtupleMaker()
  {
  }

//===============================================================
private:
//===============================================================
  virtual void beginJob();
  virtual void analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup);
  virtual void endJob();
  virtual void beginRun( const edm::Run& iRun, const edm::EventSetup& iSetup);
  virtual void endRun(const edm::Run&, const edm::EventSetup&);
  virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  virtual void endLuminosityBlock(const edm::LuminosityBlock & lumi, const edm::EventSetup & setup);

// Variables ==================================================
  bool EvtPass;
  bool isRD;

  struct GenInfo{
    double mass;
    int id,Lept1_id,Lept2_id;
    int status,Lept1_status,Lept2_status;
    double px,py,pz,pt,eta,phi;
    double Lept1_px,Lept1_py,Lept1_pz,Lept1_en,Lept1_pt,Lept1_eta,Lept1_phi,Lept1_et,Lept1_charge;
    double Lept2_px,Lept2_py,Lept2_pz,Lept2_en,Lept2_pt,Lept2_eta,Lept2_phi,Lept2_et,Lept2_charge;
    double Neut_pt;
  };
  double genDeltaR1, genDeltaR2;
  double BestGenDeltaR1, BestGenDeltaR2;
  double dPtRel1, dPtRel2;
  double BesTdPtRel1, BesTdPtRel2;
  int idxMatch;

  std::string Channel;
  std::string L1Select_;
  std::string mEAtargetToken;
  bool useL1Selector_;
  //    useL1Selector_ = iConfig.getParameter<bool>("useL1Selector");
  //    L1Select_      = iConfig.getUntrackedParameter< std::string >("L1Select");


  typedef pat::JetCollection::const_iterator JI;

  edm::InputTag leptonLabel1_;
  edm::InputTag leptonLabel2_;
  edm::InputTag muonLabel2_;
  edm::InputTag pfMEtLabel_;
  edm::InputTag noPuMEtLabel_;
  edm::InputTag MVAMEtLabel_;
  edm::InputTag genMEtTrueLabel_;
  edm::InputTag genMEtCaloLabel_;
  edm::InputTag genMEtCaloAndNonPromptLabel_;
  edm::InputTag jetLabel_;
  edm::InputTag genParticlesLabel_;
  edm::InputTag vertexLabel_;
  edm::InputTag TriggerResultsTag;
  edm::InputTag rhoIsoInputTag;
  edm::InputTag conversionsInputTag;
  edm::InputTag beamSpotInputTag;
  //Handle
  edm::Handle<double>rhoIso_h;
  edm::Handle<reco::ConversionCollection>conversions_h;
  edm::Handle<reco::BeamSpot> beamSpot_h;
  edm::Handle<std::vector< PileupSummaryInfo > >  PupInfo;
  edm::Handle<std::vector<pat::Muon> > mu1_hand;
  edm::Handle<std::vector<pat::Muon> > mu2_hand;
  edm::Handle<std::vector<pat::Electron> > ele1_hand;
  edm::Handle<std::vector<pat::Electron> > ele2_hand;
  edm::Handle<std::vector<pat::Tau> > tau1_hand;
  edm::Handle<std::vector<pat::Tau> > tau2_hand;
  edm::Handle<pat::METCollection> pfMET_hand;
  edm::Handle<reco::PFMETCollection> NoPuMET_hand;
  edm::Handle<reco::PFMETCollection> MVaMET_hand;
  edm::Handle<reco::GenMETCollection> genMEtTrue_hand;
  edm::Handle<reco::GenMETCollection> genMEtCalo_hand;
  edm::Handle<reco::GenMETCollection> genMEtCaloAndNonPrompt_hand;
  edm::Handle<reco::VertexCollection> recVtxs_;

  //iterator------------------------------
  pat::METCollection::const_iterator pfMEt_It;
  reco::PFMETCollection::const_iterator NoPuMEt_It;
  reco::PFMETCollection::const_iterator MVaMEt_It;
  reco::GenMETCollection::const_iterator genMEtTrue_It;
  reco::GenMETCollection::const_iterator genMEtCalo_It;
  reco::GenMETCollection::const_iterator genMEtCaloAndNonPrompt_It;

  std::vector<std::string> filters_;

  HLTConfigProvider HltConfig;
  std::vector<std::string> HLTTriggers;
  std::vector<unsigned int> TrigIndex;
  std::vector<std::string> FullHLTTriggerNames;
  std::vector<int> HLTVersions;

  bool metStudy_;
//  bool NoPU_metStudy_;
//  bool MVA_metStudy_;
//  bool genMEtTrue_Study_;
//  bool genMEtCalo_Study_;
//  bool genMEtCaloAndNonPrompt_Study_;
  bool useEventCounter_;
  
  // relIso
  double relIso1_;
  double relIso2_;
  // btag Discriminator
  std::vector<std::string> bTagAlgos_;
  std::vector<std::string> bTagNames_;
  std::vector<double> bTagCutValues_;
  std::vector<bool> bTagIsCutMin_;
  std::vector<int> nbjetsCache_;
  //std::string bTagAlgo_;
  //double minBTagValue_;

  edm::Service<TFileService> fs;
  TTree* tree;
  EventBranches	EventData;
  TrigBranches	HLTData;
  Zboson	Zs;
  GenZboson	GenZs;
  FSRphoton	FSRph;
  METs		MEt;

  TH1F * tmp;
  TH1F * h_lept1_pt;
  TH1F * h_lept2_pt;
  TH1F * h_Zmass;
  TH1F * h_MET;
//  TH1F * h_NoPU_MET;
//  TH1F * h_MVA_MET;
//  TH1F * h_genMEtTrue_MET;
//  TH1F * h_genMEtCalo_MET;
//  TH1F * h_genMEtCaloAndNonPrompt_MET;
  TH1F * h_jetpt30_multi;
  TH1F * h_npileupin;
  TH1F * h_npileup;
  TH1F * h_nvertex;

  //std::vector<Ky::ZCandidate>* Z;
  std::vector<Ky::Lepton>* lepton1;
  std::vector<Ky::Lepton>* lepton2;
  std::vector<Ky::METCandidate>* pfMet;
  std::vector<math::XYZTLorentzVector>* met;
  math::XYZTLorentzVector *pfMEt4V;
  std::vector<math::XYZTLorentzVector>* jetspt30;

  double pfMET;
//  double NoPU_MET;
//  double MVA_MET;
//  double genMEtTrue_MET;
//  double genMEtCalo_MET;
//  double genMEtCaloAndNonPrompt_MET;
  double dphimetlepton1;
  double dphimetlepton2;
  double dphimetjet1;
  double dphimetjet2;

  double discr;

  double genttbarM;


  // ----------member data ---------------------------

  edm::LumiReWeighting LumiWeights_;

  std::vector<double> PileUpRD_;
  std::vector<double> PileUpMC_;

  reweight::PoissonMeanShifter PShiftUp_;
  reweight::PoissonMeanShifter PShiftDown_;

  /// constant iterator for L1 trigger
  //  http://cmssw.cvs.cern.ch/cgi-bin/cmssw.cgi/CMSSW/L1TriggerConfig/L1GtConfigProducers/interface/L1GtTriggerMenuTester.h?revision=1.3&view=markup
  typedef std::map<std::string, const L1GtAlgorithm*>::const_iterator
    CItAlgoP;
  

  bool applyIso_;
  bool oppPair_;

  double Lept1_chIso03,Lept1_chIso04;
  double Lept2_chIso03,Lept2_chIso04;
  double Lept1_nhIso03,Lept1_nhIso04;
  double Lept2_nhIso03,Lept2_nhIso04;
  double Lept1_phIso03,Lept1_phIso04;
  double Lept2_phIso03,Lept2_phIso04;
  double Lept1_pcIso03,Lept1_pcIso04;
  double Lept2_pcIso03,Lept2_pcIso04;

  double Lept1_RelisolPtTrks03 ;
  double Lept1_RelisoEm03      ;
  double Lept1_RelisoHad03     ;

  bool Lept1_isGlobal, Lept2_isGlobal;
  bool Lept1_isTrker,  Lept2_isTrker;
  double Lept1_globalNormChi2,Lept2_globalNormChi2;
  double Lept1_muonHits,Lept2_muonHits;
  double Lept1_trackerHits,Lept2_trackerHits;
  double Lept1_dxy,Lept1_dz;
  double Lept2_dxy,Lept2_dz;
  double Lept1_trkLayers,Lept2_trkLayers;
  double Lept1_pixelHits,Lept2_pixelHits;
  int Lept1_matchStations, Lept2_matchStations;
  double Lept1_relIsoCom03,Lept1_relIsoCom04;
  double Lept2_relIsoCom03,Lept2_relIsoCom04;
  double Lept1_relIsoBeta03,Lept1_relIsoBeta04;
  double Lept2_relIsoBeta03,Lept2_relIsoBeta04;
  double Lept1_relIsoRho03;
  double Lept2_relIsoRho03;

  double Lept2_RelisolPtTrks03 ;
  double Lept2_RelisoEm03      ;
  double Lept2_RelisoHad03     ;

  double Lept1_pt, Lept1_eta,Lept1_etaSC,Lept1_phi,
  Lept1_phiSC, Lept1_dB, Lept1_px, Lept1_py,
  Lept1_pz, Lept1_en,Lept1_et,Lept1_charge,
  Lept1_MedComIsoDelBetCorr3Hits, Lept1_decModFind;


  double Lept2_pt, Lept2_eta,Lept2_etaSC,Lept2_phi,
  Lept2_phiSC, Lept2_dB, Lept2_px, Lept2_py,
  Lept2_pz,Lept2_en,Lept2_et,Lept2_charge,
  Lept2_MedComIsoDelBetCorr3Hits, Lept2_decModFind;
  
  double rhoIso;
  double Lept1_dEtaIn,Lept1_dPhiIn,Lept1_sigmaIEtaIEta;
  double Lept2_dEtaIn,Lept2_dPhiIn,Lept2_sigmaIEtaIEta;
  double Lept1_HoverE,Lept1_fbrem;
  double Lept2_HoverE,Lept2_fbrem;
  double Lept1_energyEC,Lept1_Pnorm,Lept1_InvEminusInvP;
  double Lept2_energyEC,Lept2_Pnorm,Lept2_InvEminusInvP;
  double Lept1_AEff03;
  double Lept2_AEff03;
  bool   Lept1_hasConversion;
  bool   Lept2_hasConversion;
  int    Lept1_mHits;
  int    Lept2_mHits;
  double Lept1_SCcharge,Lept1_TKcharge,Lept1_GSFcharge;
  double Lept2_SCcharge,Lept2_TKcharge,Lept2_GSFcharge;
  double Lept1_GsfCtfScPixchargeConsistentcheck;
  double Lept2_GsfCtfScPixchargeConsistentcheck;


  void bookTree();

  bool L1TriggerSelection( const edm::Event& iEvent, const edm::EventSetup& iSetup );

//  virtual bool filter(const edm::Event& iEvent, const edm::EventSetup& iSetup)
  void GetHLTResults(const edm::Event &iEvent, const edm::EventSetup& iSetup);
  void clear();
  bool checkOverlap(const double & eta, const double & phi, const double & dRval1,const double & reliso1, const double &dRval2, const double & reliso2);
  bool MatchObjects( const reco::Candidate::LorentzVector& pasObj,
      const reco::Candidate::LorentzVector& proObj,
      bool exact );
 
  bool HasDaughter(reco::GenParticleRef genPtcl, int id);
  reco::GenParticleRef FindDaughter(reco::GenParticleRef mom,int id);
  
  void GetGenInfoZ(const edm::Event &iEvent, const edm::EventSetup& iSetup);
  void GetFSRInfoW(const edm::Event &iEvent, const edm::EventSetup& iSetup);
  double alphaRatio(double pt);
  void LoopMuon(const edm::Event &iEvent, const edm::EventSetup& iSetup);
  void LoopElectron(const edm::Event &iEvent, const edm::EventSetup& iSetup);
  void LoopTau(const edm::Event &iEvent, const edm::EventSetup& iSetup);

};

ZNtupleMaker::ZNtupleMaker(const edm::ParameterSet& iConfig)
{
    //now do what ever initialization is needed
    Channel = iConfig.getUntrackedParameter< std::string >("Channel");
    leptonLabel1_ = iConfig.getParameter<edm::InputTag>("leptonLabel1");
    leptonLabel2_ = iConfig.getParameter<edm::InputTag>("leptonLabel2");
    pfMEtLabel_ = iConfig.getParameter<edm::InputTag>("pfMEtLabel");
    noPuMEtLabel_ = iConfig.getParameter<edm::InputTag>("noPuMEtLabel");
    MVAMEtLabel_ = iConfig.getParameter<edm::InputTag>("MVAMEtLabel");
    genMEtTrueLabel_ = iConfig.getParameter<edm::InputTag>("genMEtTrueLabel");
    genMEtCaloLabel_ = iConfig.getParameter<edm::InputTag>("genMEtCaloLabel");
    genMEtCaloAndNonPromptLabel_ = iConfig.getParameter<edm::InputTag>("genMEtCaloAndNonPromptLabel");    
    jetLabel_ = iConfig.getParameter<edm::InputTag>("jetLabel");
    genParticlesLabel_= iConfig.getParameter<edm::InputTag>("genParticlesLabel");
    vertexLabel_ =  iConfig.getUntrackedParameter<edm::InputTag>("vertexLabel");
    metStudy_ = iConfig.getUntrackedParameter<bool>("metStudy",false);
    useEventCounter_ = iConfig.getParameter<bool>("useEventCounter");
    filters_ = iConfig.getUntrackedParameter<std::vector<std::string> >("filters");
    relIso1_ = iConfig.getUntrackedParameter<double>("relIso1");
    relIso2_ = iConfig.getUntrackedParameter<double>("relIso2");
    applyIso_ = iConfig.getUntrackedParameter<bool>("applyIso",true);
    oppPair_ = iConfig.getUntrackedParameter<bool>("oppPair",true);
    
    PileUpRD_ = iConfig.getParameter< std::vector<double> >("PileUpRD");
    PileUpMC_ = iConfig.getParameter< std::vector<double> >("PileUpMC");

    TriggerResultsTag = iConfig.getUntrackedParameter<InputTag>		("TriggerResultsTag");
    HLTTriggers = iConfig.getUntrackedParameter< std::vector<std::string> >("HLTTriggers");
    beamSpotInputTag=iConfig.getParameter<edm::InputTag>("beamSpotInputTag");
    rhoIsoInputTag = iConfig.getParameter<edm::InputTag>("rhoIsoInputTag");
    conversionsInputTag=iConfig.getParameter<edm::InputTag>("conversionsInputTag");

    useL1Selector_ = iConfig.getParameter<bool>("useL1Selector");
    L1Select_      = iConfig.getUntrackedParameter< std::string >("L1Select");

    mEAtargetToken = iConfig.getParameter< std::string >("EAtarget");//EleEANoCorr, EleEAData2011, EleEASummer11MC,EleEAFall11MC, EleEAData2012 
    //mEAtargetToken = consumes<std:string>(iConfig.getParameter<std:string>("EAtarget", "EleEAData2012"));
    tree = fs->make<TTree>("tree", "Tree for W boson");

    EventData.vtx_isFake = new std::vector<int>;
    EventData.vtx_ndof = new std::vector<int>;
    EventData.vtx_z = new std::vector<double>;
    EventData.vtx_Rho = new std::vector<double>;

    Zs.Lept1_isGlobal= new std::vector<bool>;
    Zs.Lept1_isTrker= new std::vector<bool>;
    Zs.Lept1_MedComIsoDelBetCorr3Hits= new std::vector<double>;
    Zs.Lept1_decModFind= new std::vector<double>;
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
    Zs.Lept2_MedComIsoDelBetCorr3Hits= new std::vector<double>;
    Zs.Lept2_decModFind= new std::vector<double>;
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
    Zs.Channel=new std::vector<int>; //--(-2), +-(0), ++(2)


    GenZs.Channel	= new std::vector<int>;
    GenZs.nLepts	= new std::vector<int>;
    GenZs.id		= new std::vector<int>;
    GenZs.status	= new std::vector<int>;
    GenZs.mass		= new std::vector<double>;
    GenZs.px		= new std::vector<double>;
    GenZs.py		= new std::vector<double>;
    GenZs.pz		= new std::vector<double>;
    GenZs.pt		= new std::vector<double>;
//    GenZs.Neut_pt	= new std::vector<double>;
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

    pfMEt4V = new math::XYZTLorentzVector();

    tmp = fs->make<TH1F>("EventSummary","EventSummary",filters_.size(),0,filters_.size());

    h_lept1_pt   = fs->make<TH1F>( "h_lept1_pt"  , "p_{t}", 50,  0., 100. );
    h_lept2_pt   = fs->make<TH1F>( "h_lept2_pt"  , "p_{t}", 50,  0., 100. );
    h_Zmass      = fs->make<TH1F>( "h_Zmass", "Z Mass", 300, 0., 300. );
    h_MET       = fs->make<TH1F>( "h_MET", "MET", 40, 0, 80);
    h_jetpt30_multi = fs->make<TH1F>( "h_jetpt30_multi", "jet30pt_multi", 10, 0, 10);
    h_npileupin = fs->make<TH1F>( "h_npileupin", "npileupin", 30, 0, 30);
    h_npileup = fs->make<TH1F>( "h_npileup", "npileup", 30, 0, 30);
    h_nvertex = fs->make<TH1F>( "h_nvertex", "nvertex", 30, 0, 30);

    lepton1 = new std::vector<Ky::Lepton>();
    lepton2 = new std::vector<Ky::Lepton>();
    pfMet = new std::vector<Ky::METCandidate>();
    met = new std::vector<math::XYZTLorentzVector>();
    jetspt30 = new std::vector<math::XYZTLorentzVector>();
}
void ZNtupleMaker::beginJob()
{
  std::vector< float > PuMC ;
  std::vector< float > PuReal;
  //for( int i=0; i< 25; ++i)
  for( int i=0; i< 60; ++i) {
    PuReal.push_back((float)PileUpRD_[i]);
    PuMC.push_back((float)PileUpMC_[i]);
  }
  LumiWeights_ = edm::LumiReWeighting(PuMC, PuReal);

  PShiftDown_ = reweight::PoissonMeanShifter(-0.5);
  PShiftUp_ = reweight::PoissonMeanShifter(0.5);

  bookTree();

  if( mEAtargetToken == "EleEANoCorr")
      EAtarget	=ElectronEffectiveArea::kEleEANoCorr;
  else if( mEAtargetToken == "EleEAData2011")
      EAtarget	=ElectronEffectiveArea::kEleEAData2011;
  else if( mEAtargetToken == "EleEASummer11MC")
      EAtarget	=ElectronEffectiveArea::kEleEASummer11MC;
  else if( mEAtargetToken == "EleEAFall11MC")
      EAtarget	=ElectronEffectiveArea::kEleEAFall11MC;
  else if( mEAtargetToken == "EleEAData2012")
      EAtarget	=ElectronEffectiveArea::kEleEAData2012;
  else
      EAtarget	=ElectronEffectiveArea::kEleEAData2012;

  cout<<"EAtarget: "<<EAtarget<<endl;

}
void ZNtupleMaker::beginRun( const edm::Run& iRun, const edm::EventSetup& iSetup)
{
  //initialization
  FullHLTTriggerNames.clear();
  HLTVersions.clear();
  //Trigger information
  if(HLTTriggers.size() > 0)
  {
    bool changed(true);
    if(HltConfig.init(iRun,iSetup,TriggerResultsTag.process(),changed))
    {
      // if init returns TRUE, initialization has succeeded
      TrigIndex.clear();
      for(unsigned int i(0); i<HLTTriggers.size(); i++)
      {
        //find the full name with version number in this particular menu.
	FullHLTTriggerNames.push_back(HLTTriggers[i]);
	HLTVersions.push_back(0);
	for(unsigned int iv(1);iv<15;iv++)
	{
	  std::stringstream trigstream;
	  trigstream<<HLTTriggers[i]<<"_v"<<iv;
	  if(HltConfig.triggerIndex(trigstream.str())<HltConfig.size())
	  {
	    FullHLTTriggerNames[i] = trigstream.str();
	    HLTVersions[i] = iv;
	  }
	}
	cout<<FullHLTTriggerNames[i]<<" "<<HltConfig.triggerIndex(FullHLTTriggerNames[i])<<endl;
	TrigIndex.push_back(HltConfig.triggerIndex(FullHLTTriggerNames[i]));
	if(TrigIndex[i] == HltConfig.size())
	{
	  string errorMessage="Requested TriggerName does not exist! -- "+HLTTriggers[i]+"\n";
	}
      }
      if(changed)
      {
	std::cout<<"Run: "<<iRun.run()<<".....Changed HLTConfig"<<std::endl;
      }
    }
    else
    {
      cout<<" HLT config extraction failure with process name "<<TriggerResultsTag.process()<<std::endl;
    }
  }
}
void ZNtupleMaker::bookTree()
{
  EventData.Register(tree);
  FSRph.Register(tree);
  for(unsigned int i(0); i<HLTTriggers.size(); i++)
  {
    HLTData.TrigNames[i]=HLTTriggers[i];
    HLTData.Register(tree,i);
  }
  Zs.Register(tree);
  GenZs.Register(tree);
  MEt.Register(tree);
}
bool ZNtupleMaker::L1TriggerSelection( const edm::Event& iEvent, const edm::EventSetup& iSetup )
{
  // Get L1 Trigger menu
  ESHandle<L1GtTriggerMenu> menuRcd;
  iSetup.get<L1GtTriggerMenuRcd>().get(menuRcd) ;
  const L1GtTriggerMenu* menu = menuRcd.product();
  // Get L1 Trigger record  
  Handle< L1GlobalTriggerReadoutRecord > gtRecord;
  iEvent.getByLabel( edm::InputTag("gtDigis"), gtRecord);
  // Get dWord after masking disabled bits
  const DecisionWord dWord = gtRecord->decisionWord();
  
  const AlgorithmMap algoMap = menu->gtAlgorithmMap();
  //  CItAlgo itAlgo = algoMap.find("L1_SingleEG22");
  CItAlgo itAlgo = algoMap.find(L1Select_);

  bool algResult = false;
  if (itAlgo != algoMap.end()) {
    int bitNumber = (itAlgo->second).algoBitNumber();
    algResult = dWord.at(bitNumber);
    //    cout<<"L1_SingleEG22 bit number => "<< bitNumber<<" bool?  "<<algResult<<endl; 
  }

  //bool l1_accepted20 = menu->gtAlgorithmResult( "L1_SingleEG20" , dWord);
  //int passL1_20 =  ( l1_accepted20 ) ? 1 : 0 ; 
  
  //bool l1_accepted22 = menu->gtAlgorithmResult( "L1_SingleEG22" , dWord);
  //int passL1_22 =  ( l1_accepted22 ) ? 1 : 0 ; 
  
  return algResult;
}
void ZNtupleMaker::GetHLTResults(const edm::Event &iEvent, const edm::EventSetup& iSetup)
{
  //Trigger Information----
  Handle<TriggerResults> trgRsltsHandle;
  //cout<<"HLTTriggers size: "<<HLTTriggers.size()<<" HLTVersions size: "<<HLTVersions.size()<<endl;
  if( (HLTTriggers.size()>0) && (HLTTriggers.size() == HLTVersions.size()))
  {
    int ErrFlag(0);
    iEvent.getByLabel(TriggerResultsTag,trgRsltsHandle);
    if(!trgRsltsHandle.isValid())
    {
      cout<<"TriggerResults "<<"TriggerResultsTag"<<" not available!"<<endl;
      ErrFlag= -1;
    }
    for(unsigned int i(0); i<HLTTriggers.size(); i++)
    {
      //cout<<"HLT version : "<<HLTVersions[i]<<endl;
      HLTData.trigState[i].version = HLTVersions[i];
      HLTData.trigState[i].fired = ErrFlag;
      HLTData.trigState[i].L1prescale = -1;
      HLTData.trigState[i].HLTprescale = -1;
      bool acceptHLT=false;

      // L1 pass?
      HLTData.trigState[i].L1fired = ErrFlag;
      if(useL1Selector_){
	bool passL1 =  L1TriggerSelection(iEvent,iSetup);

	if ( passL1 ){     HLTData.trigState[i].L1fired = 1;
	} else{ HLTData.trigState[i].L1fired = -1;}
      }
      if(ErrFlag>-1)
      {
	//here we play this game of adding "v..." to the requested trigger
	//and hunt for the version number of the thing...
	//and there are a lot of try and open catches here because HLT code
	//seems to want to segfault at the slightest provocation
	string theRealTriggername;
	try{
	  unsigned int trIndex=HltConfig.triggerIndex(FullHLTTriggerNames[i]);
	  if(HltConfig.size() != trIndex)
	  {
	    acceptHLT = trgRsltsHandle->accept(trIndex);
	  }
	  else
	  {
	    acceptHLT=false;
	    HLTData.trigState[i].fired= -1;
	  }
	}
	catch(...)
	{
	  acceptHLT=false;
	  HLTData.trigState[i].fired=-1;
	}
	if(acceptHLT)
	{
	  //cout<<"HLT fired hahahahahhahahhaha"<<endl;
	  HLTData.trigState[i].fired=1;
	}
	std::pair<int,int>prescalePair;
	try
	{
	  //prescalePair=HltConfig.prescaleValues(iEvent,iSetup,FullHLTTriggerNames[i]);
	  //cout<<"L1 prescale: "<<prescalePair.first<<" HLT prescale: "<<prescalePair.second<<endl;;
	  //HLTData.trigState[i].L1prescale=prescalePair.first;
	  //HLTData.trigState[i].HLTprescale=prescalePair.second;
	}
	catch(...)
	{
	  HLTData.trigState[i].L1prescale=-1;
	  HLTData.trigState[i].HLTprescale=-1;
	}
      }//ErrFlag
    }
  }
  else
  {
    //cout<<"HLTTRiggers is 0 or HLTVersions.size is not the same"<<endl;
  }
}
void ZNtupleMaker::clear()
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
  Zs.Lept1_MedComIsoDelBetCorr3Hits->clear();
  Zs.Lept1_decModFind->clear();
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
  Zs.Lept2_MedComIsoDelBetCorr3Hits->clear();
  Zs.Lept2_decModFind->clear();
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
//  Zs.NoPU_Neut_pt->clear();
//  Zs.NoPU_Neut_phi->clear();
//  Zs.NoPU_Neut_px->clear();
//  Zs.NoPU_Neut_py->clear();
//  Zs.MVA_Neut_pt->clear();
//  Zs.MVA_Neut_phi->clear();
//  Zs.MVA_Neut_px->clear();
//  Zs.MVA_Neut_py->clear();
//  Zs.genMEtTrue_pt->clear();
//  Zs.genMEtTrue_phi->clear();
//  Zs.genMEtTrue_px->clear();
//  Zs.genMEtTrue_py->clear();
/*  Zs.genMEtCalo_pt->clear();
  Zs.genMEtCalo_phi->clear();
  Zs.genMEtCalo_px->clear();
  Zs.genMEtCalo_py->clear();
  Zs.genMEtCaloAndNonPrompt_pt->clear();
  Zs.genMEtCaloAndNonPrompt_phi->clear();
  Zs.genMEtCaloAndNonPrompt_px->clear();
  Zs.genMEtCaloAndNonPrompt_py->clear();
*/  
  Zs.Sign->clear();
  Zs.Channel->clear();


  GenZs.Channel->clear();
  GenZs.nLepts->clear();
  GenZs.id->clear();
  GenZs.status->clear();
  GenZs.mass->clear();
  GenZs.px->clear();
  GenZs.py->clear();
  GenZs.pz->clear();
  GenZs.pt->clear();
//  GenZs.Neut_pt->clear();
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


  //MEt.pfMEt4V->SetPxPyPzE(0,0,0,0);
  //MEt.NoPuMEt4V->SetPxPyPzE(0,0,0,0);
  //MEt.MVaMEt4V->SetPxPyPzE(0,0,0,0);
  //MEt.genMEtTrue4V->SetPxPyPzE(0,0,0,0);
  //MEt.genMEtCalo4V->SetPxPyPzE(0,0,0,0);
  //MEt.genMEtCaloAndNonPrompt4V->SetPxPyPzE(0,0,0,0);



  lepton1->clear();
  lepton2->clear();
  pfMet->clear();
//  NoPU_pfMet->clear();
//  MVA_pfMet->clear();
//  genMEtTrue_pfMet->clear();
//  genMEtCalo_pfMet->clear();
//  genMEtCaloAndNonPrompt_pfMet->clear();
  met->clear();
//  NoPU_met->clear();
//  MVA_met->clear();
//  genMEtTrue_met->clear();
//  genMEtCalo_met->clear();
//  genMEtCaloAndNonPrompt_met->clear();
  jetspt30->clear();

    //weight = 1.0;
    //weightin = 1.0;
    //weightplus = 1.0;
    //weightminus = 1.0;

    dphimetlepton1 = -999;  
    dphimetlepton2 = -999;  
    dphimetjet1 = -999;
    dphimetjet2 = -999;

    genttbarM = -999;
}
void ZNtupleMaker::endLuminosityBlock(const edm::LuminosityBlock & lumi, const edm::EventSetup & setup)
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
}
bool ZNtupleMaker::checkOverlap(const double & eta, const double & phi, const double & dRval1,const double & reliso1, const double &dRval2, const double & reliso2)
{
  bool overlap = false;
  if( reliso1 < relIso1_ ) {
    overlap = dRval1 < 0.4 ;
    if(overlap) return overlap;
  }

  if( reliso2 < relIso2_ ) {
    overlap = dRval2 < 0.4 ;
    if(overlap) return overlap;
  }

  return overlap;

}

bool ZNtupleMaker::MatchObjects( const reco::Candidate::LorentzVector& pasObj,
      const reco::Candidate::LorentzVector& proObj,
      bool exact )
{
  double proEta = proObj.eta();
  double proPhi = proObj.phi();
  double proPt  = proObj.pt();
  double pasEta = pasObj.eta();
  double pasPhi = pasObj.phi();
  double pasPt  = pasObj.pt();

  double dRval = deltaR(proEta, proPhi, pasEta, pasPhi);
  double dPtRel = 999.0;
  if( proPt > 0.0 ) dPtRel = fabs( pasPt - proPt )/proPt;
  // If we are comparing two objects for which the candidates should
  // be exactly the same, cut hard. Otherwise take cuts from user.
  if( exact ) return ( dRval < 1e-3 && dPtRel < 1e-3 );
  else        return ( dRval < 0.025 && dPtRel < 0.025 );
}
bool ZNtupleMaker::HasDaughter(reco::GenParticleRef genPtcl, int id)
{
  for(unsigned int i(0);i<genPtcl->numberOfDaughters(); i++)
  {
    if(genPtcl->daughterRef(i)->pdgId() == id) return true;
  }
  return false;
}
reco::GenParticleRef ZNtupleMaker::FindDaughter(reco::GenParticleRef mom,int id)
{
  reco::GenParticleRef daughter;
  for( unsigned int i(0);i<mom->numberOfDaughters();i++)
  {
    daughter = mom->daughterRef(i);
    if(daughter->pdgId() == id) return daughter;
  }
  return daughter;
}
void ZNtupleMaker::GetGenInfoZ(const edm::Event &iEvent, const edm::EventSetup& iSetup)
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
    // TODO This is wrong : it will count all the neutrinos from pileUp
    if( ((abs(boson.pdgId()) == 12) || (abs(boson.pdgId()) == 14) || (abs(boson.pdgId()) == 16)) && (boson.status() == 1))
      GenZs.Neut_pt += boson.pt();

    if( ((abs(boson.pdgId()) == 23) || (abs(boson.pdgId()) == 22)) && (boson.status() == 3))
    {
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
//	if( ((abs(daughter->pdgId()) == 12) || (abs(daughter->pdgId()) == 14) || (abs(daughter->pdgId()) == 16)) && (daughter->status() == 1))
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
          GenZinfo.Lept1_charge     =daughter->charge();
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
          GenZinfo.Lept2_charge     =daughter->charge();
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
      GenZs.Lept1_charge	->push_back(GenZinfo.Lept1_charge);
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
      GenZs.Lept2_charge	->push_back(GenZinfo.Lept2_charge);
      GenZs.Lept2_eta	->push_back(GenZinfo.Lept2_eta);
      GenZs.Lept2_phi	->push_back(GenZinfo.Lept2_phi);
    }//Drell-Yan
  }//genPtcls
}
void ZNtupleMaker::LoopMuon(const edm::Event &iEvent, const edm::EventSetup& iSetup)
{
    //cout<<"lepton size: "<<mu1_hand->size()<<endl;
    reco::isodeposit::AbsVetos vetos_ch;
    reco::isodeposit::AbsVetos vetos_nh;
    reco::isodeposit::AbsVetos vetos_ph;
    reco::isodeposit::AbsVetos vetos_pc;
    vetos_nh.push_back(new ThresholdVeto( 0.5 ));
    vetos_ph.push_back(new ThresholdVeto( 0.5 ));

    //bool goodVtx=false;
    for(unsigned i = 0; i < mu1_hand->size(); i++)
    {
      pat::Muon it1 = mu1_hand->at(i);
      it1.setP4(it1.pfCandidateRef()->p4());
      const Ky::Lepton lep1(it1.p4(), (int) it1.charge());
      lepton1->push_back(lep1);

      //Pf isolation
      lepton1->back().setIsoDeposit( pat::PfChargedHadronIso, it1.isoDeposit(pat::PfChargedHadronIso), vetos_ch );
      lepton1->back().setIsoDeposit( pat::PfNeutralHadronIso, it1.isoDeposit(pat::PfNeutralHadronIso), vetos_nh );
      lepton1->back().setIsoDeposit( pat::PfGammaIso, it1.isoDeposit(pat::PfGammaIso), vetos_ph );
      lepton1->back().setIsoDeposit( pat::PfPUChargedHadronIso, it1.isoDeposit(pat::PfPUChargedHadronIso), vetos_pc );
      //detector based isolation
      lepton1->back().setIsoDeposit( it1.trackIso(), it1.ecalIso(), it1.hcalIso());

      Lept1_isGlobal=it1.isGlobalMuon();
      Lept1_isTrker=it1.isTrackerMuon();
      Lept1_pt=it1.pt();
      Lept1_et=it1.et();
      Lept1_charge=it1.charge();
      Lept1_eta=it1.eta();
      Lept1_phi=it1.phi();
      Lept1_px =it1.px();
      Lept1_py =it1.py();
      Lept1_pz =it1.pz();
      Lept1_en =it1.energy();
      Lept1_matchStations=it1.numberOfMatchedStations();
      Lept1_dB=it1.dB();

      //GlobalMuon related
      if(it1.isGlobalMuon())
      {
	const reco::TrackRef& muGlobalTrk = it1.globalTrack();
	try{
	  Lept1_globalNormChi2=muGlobalTrk->normalizedChi2();
	  Lept1_muonHits=muGlobalTrk->hitPattern().numberOfValidMuonHits();
	  Lept1_trackerHits=muGlobalTrk->hitPattern().numberOfValidTrackerHits();
	}catch(...){
	  Lept1_globalNormChi2=-9999;
	  Lept1_muonHits=-9999;
	  Lept1_trackerHits=muGlobalTrk->hitPattern().numberOfValidTrackerHits();
	}
      }else{
	  Lept1_globalNormChi2=-9999;
	  Lept1_muonHits=-9999;
	  Lept1_trackerHits=-9999;
      }
      //Vertex realted
      //goodVtx=false;
      if( recVtxs_->size() >0)
      {
	reco::VertexRef vtx(recVtxs_,0);
	//const reco::TrackRef& muGlobalTrk = it1.globalTrack();
	try{
	  Lept1_dz=it1.innerTrack()->dz(vtx->position());
	}catch(...){
	  Lept1_dz=-9999;
	}
      }else{
	try{
	  Lept1_dz=it1.innerTrack()->dz(beamSpot_h->position());
	}catch(...){
	  Lept1_dz=-9999;
	}
      }
      //other hits
      try{
	Lept1_trkLayers=it1.track()->hitPattern().trackerLayersWithMeasurement();
	Lept1_pixelHits=it1.innerTrack()->hitPattern().numberOfValidPixelHits();
      }catch(...){
	Lept1_trkLayers=-9999;
	Lept1_pixelHits=-9999;
      }

      Lept1_chIso03 = it1.isoDeposit(pat::PfChargedHadronIso)->depositAndCountWithin(0.3, vetos_ch).first;
      Lept1_chIso04 = it1.isoDeposit(pat::PfChargedHadronIso)->depositAndCountWithin(0.4, vetos_ch).first;
      Lept1_nhIso03 = it1.isoDeposit(pat::PfNeutralHadronIso)->depositAndCountWithin(0.3, vetos_nh).first;
      Lept1_nhIso04 = it1.isoDeposit(pat::PfNeutralHadronIso)->depositAndCountWithin(0.4, vetos_nh).first;
      Lept1_phIso03 = it1.isoDeposit(pat::PfGammaIso)->depositAndCountWithin(0.3, vetos_ph).first;
      Lept1_phIso04 = it1.isoDeposit(pat::PfGammaIso)->depositAndCountWithin(0.4, vetos_ph).first;
      Lept1_pcIso03 = it1.isoDeposit(pat::PfPUChargedHadronIso)->depositAndCountWithin(0.3, vetos_pc).first;
      Lept1_pcIso04 = it1.isoDeposit(pat::PfPUChargedHadronIso)->depositAndCountWithin(0.4, vetos_pc).first;

      //if(Lept1_pcIso04_tmp != Lept1_pcIso04) cout<<"ZNtupleMaker: pcIso04 is not the same"<<endl;

      Lept1_relIsoCom03 = (Lept1_chIso03 + Lept1_nhIso03 + Lept1_phIso03)/Lept1_pt;
      Lept1_relIsoCom04 = (Lept1_chIso04 + Lept1_nhIso04 + Lept1_phIso04)/Lept1_pt;
      Lept1_relIsoBeta03 = (Lept1_chIso03+
	  max(0.0, Lept1_nhIso03 + Lept1_phIso03 - 0.5*Lept1_pcIso03))
	  /Lept1_pt;
      Lept1_relIsoBeta04 = (Lept1_chIso04+
	  max(0.0, Lept1_nhIso04 + Lept1_phIso04 - 0.5*Lept1_pcIso04))
	  /Lept1_pt;

      //if(Lept1_relIsoBeta04 > 0.12)
      //{
//	cout<<"relIsoBeta04 : "<<Lept1_relIsoBeta04<<" Event: "<<EventData.EVENT<<endl;
      //}

      for(unsigned j = i+1; j < mu2_hand->size(); j++)
      {
	pat::Muon it2 = mu2_hand->at(j);
        it2.setP4(it2.pfCandidateRef()->p4());

        const bool match = MatchObjects( it1.p4(), it2.p4(), true);
        if(match) continue;

        const Ky::Lepton lep2(it2.p4(), (int) it2.charge());
        lepton2->push_back(lep2);
        //pf isolation setup
        lepton2->back().setIsoDeposit( pat::PfChargedHadronIso, it2.isoDeposit(pat::PfChargedHadronIso), vetos_ch );
        lepton2->back().setIsoDeposit( pat::PfNeutralHadronIso, it2.isoDeposit(pat::PfNeutralHadronIso), vetos_nh );
        lepton2->back().setIsoDeposit( pat::PfGammaIso, it2.isoDeposit(pat::PfGammaIso), vetos_ph );
        lepton2->back().setIsoDeposit( pat::PfPUChargedHadronIso, it2.isoDeposit(pat::PfPUChargedHadronIso), vetos_pc );
 
        //detector based isolation
        lepton2->back().setIsoDeposit( it2.trackIso(), it2.ecalIso(), it2.hcalIso());


        Lept2_isGlobal=it2.isGlobalMuon();
        Lept2_isTrker=it2.isTrackerMuon();
        Lept2_pt=it2.pt();
        Lept2_et=it2.et();
        Lept2_charge=it2.charge();
        Lept2_eta=it2.eta();
        Lept2_phi=it2.phi();
        Lept2_px=it2.px();
        Lept2_py=it2.py();
        Lept2_pz=it2.pz();
        Lept2_en=it2.energy();
        Lept2_matchStations=it2.numberOfMatchedStations();
        Lept2_dB=it2.dB();

        //GlobalMuon related
        if(it2.isGlobalMuon())
        {
  	  const reco::TrackRef& muGlobalTrk = it2.globalTrack();
	  try{
	    Lept2_globalNormChi2=muGlobalTrk->normalizedChi2();
	    Lept2_muonHits=muGlobalTrk->hitPattern().numberOfValidMuonHits();
	    Lept2_trackerHits=muGlobalTrk->hitPattern().numberOfValidTrackerHits();
	  }catch(...){
	    Lept2_globalNormChi2=-9999;
	    Lept2_muonHits=-9999;
	    Lept2_trackerHits=muGlobalTrk->hitPattern().numberOfValidTrackerHits();
	  }
        }else{
	  Lept2_globalNormChi2=-9999;
	  Lept2_muonHits=-9999;
	  Lept2_trackerHits=-9999;
        }

        //Vertex realted
        //goodVtx=false;
	/******************************
        for( reco::VertexCollection::const_iterator v=recVtxs_->begin();v!=recVtxs_->end();++v)
        {
	  if(v->isFake()) continue;
	  if(v->ndof() <=4) continue;
	  if(v->z() >= 24) continue;
	  if(v->position().Rho() >= 2) continue;
	  if( !it2.isGlobalMuon() ) continue;
	  const reco::TrackRef& muGlobalTrk = it2.globalTrack();
	  goodVtx= true;
	  try{
	    Lept2_dz=muGlobalTrk->dz(v->position());
	  }
	  catch(...){
	    Lept2_dz=-9999;
	  }
        }//vtx
        if(!goodVtx)
        {
	  Lept2_dz=-9999;
        }
	**********************************/
        if( recVtxs_->size() >0)
        {
	  reco::VertexRef vtx(recVtxs_,0);
	  //const reco::TrackRef& muGlobalTrk = it2.globalTrack();
	  try{
	    Lept2_dz=it2.innerTrack()->dz(vtx->position());
	  }catch(...){
	    Lept2_dz=-9999;
	  }
        }else{
	  try{
	    Lept2_dz=it2.innerTrack()->dz(beamSpot_h->position());
	  }catch(...){
	    Lept2_dz=-9999;
	  }
        }
        //other hits
        try{
	  Lept2_trkLayers=it2.track()->hitPattern().trackerLayersWithMeasurement();
	  Lept2_pixelHits=it2.innerTrack()->hitPattern().numberOfValidPixelHits();
        }catch(...){
	  Lept2_trkLayers=-9999;
	  Lept2_pixelHits=-9999;
        }

	//vertexfit
        Ky::ZCandidate Dimuon(lepton1->back(), lepton2->back());
	ESHandle<TransientTrackBuilder> trackBuilder;
	iSetup.get<TransientTrackRecord>().get("TransientTrackBuilder",trackBuilder);
	reco::TrackRef trkerTrk1 = it1.track();
	reco::TrackRef trkerTrk2 = it2.track();
	if(trkerTrk1.isNonnull() && trkerTrk2.isNonnull())
	{
	  reco::TransientTrack transientTrk1 = trackBuilder->build(trkerTrk1);
	  reco::TransientTrack transientTrk2 = trackBuilder->build(trkerTrk2);
	  Dimuon.KalmanVtxFit(transientTrk1, transientTrk2);
	}
	if( !isRD && GenZs.nLepts->size() > 0 && Channel == "Muon")
	{
	  //Loop all GenZs---------------
	  for( unsigned int iGen(0);iGen<GenZs.nLepts->size();iGen++)
	  {
	    genDeltaR1 = -999;genDeltaR2 = -999;
	    dPtRel1 = -999;dPtRel2 = -999;
	    idxMatch = -999;

	    BestGenDeltaR1= 999;
	    BestGenDeltaR2= 999;
	    BesTdPtRel1= 999;
	    BesTdPtRel2= 999;

	    if( (*GenZs.nLepts)[iGen] != 2)continue;
	    if( abs((*GenZs.Lept1_id)[iGen]) != GenType::kMuon) continue;
	    if( abs((*GenZs.Lept2_id)[iGen]) != GenType::kMuon) continue;
	    genDeltaR1 = deltaR( (*GenZs.Lept1_eta)[iGen],(*GenZs.Lept1_phi)[iGen],
	                          Lept1_eta, Lept1_phi);
	    dPtRel1 = fabs(Lept1_pt-(*GenZs.Lept1_pt)[iGen])/(*GenZs.Lept1_pt)[iGen];
	    genDeltaR2 = deltaR( (*GenZs.Lept2_eta)[iGen],(*GenZs.Lept2_phi)[iGen],
		  Lept2_eta, Lept2_phi);
	    dPtRel2 = fabs(Lept2_pt-(*GenZs.Lept2_pt)[iGen])/(*GenZs.Lept2_pt)[iGen];
	    if( (genDeltaR1 < BestGenDeltaR1) && (genDeltaR2 < BestGenDeltaR2) )
	      if( (dPtRel1 < 0.5) && (dPtRel2 < 0.5) )
	      {
		BestGenDeltaR1 = genDeltaR1;
		BestGenDeltaR2 = genDeltaR2;
		BesTdPtRel1 = dPtRel1;
		BesTdPtRel2 = dPtRel2;
	        idxMatch = iGen;
	      }
	    // vice versa
	    genDeltaR1 = deltaR( (*GenZs.Lept2_eta)[iGen],(*GenZs.Lept2_phi)[iGen],
		  Lept1_eta, Lept1_phi);
	    dPtRel1 = fabs(Lept1_pt-(*GenZs.Lept2_pt)[iGen])/(*GenZs.Lept2_pt)[iGen];
	    genDeltaR2 = deltaR( (*GenZs.Lept1_eta)[iGen],(*GenZs.Lept1_phi)[iGen],
		  Lept2_eta, Lept2_phi);
	    dPtRel2 = fabs(Lept2_pt-(*GenZs.Lept1_pt)[iGen])/(*GenZs.Lept1_pt)[iGen];
	    //if( genDeltaR1 < 0.025 && genDeltaR2 < 0.025) break;
	    if( (genDeltaR1 < BestGenDeltaR1) && (genDeltaR2 < BestGenDeltaR2) )
	      if( (dPtRel1 < 0.5) && (dPtRel2 < 0.5) )
	      {
		BestGenDeltaR1 = genDeltaR1;
		BestGenDeltaR2 = genDeltaR2;
		BesTdPtRel1 = dPtRel1;
		BesTdPtRel2 = dPtRel2;
	        idxMatch = iGen;
	      }
	  }
	}
        Lept2_chIso03=lepton2->back().chIso03();
        Lept2_chIso04=lepton2->back().chIso04();
        Lept2_nhIso03=lepton2->back().nhIso03();
        Lept2_nhIso04=lepton2->back().nhIso04();
        Lept2_phIso03=lepton2->back().phIso03();
        Lept2_phIso04=lepton2->back().phIso04();
        Lept2_pcIso03=lepton2->back().pcIso03();
        Lept2_pcIso04=lepton2->back().pcIso04();

        Lept2_relIsoCom03 = (Lept2_chIso03 + Lept2_nhIso03 + Lept2_phIso03)/Lept2_pt;
        Lept2_relIsoCom04 = (Lept2_chIso04 + Lept2_nhIso04 + Lept2_phIso04)/Lept2_pt;
        Lept2_relIsoBeta03 = (Lept2_chIso03+
            max(0.0, Lept2_nhIso03 + Lept2_phIso03 - 0.5*Lept2_pcIso03))
            /Lept2_pt;
        Lept2_relIsoBeta04 = (Lept2_chIso04+
            max(0.0, Lept2_nhIso04 + Lept2_phIso04 - 0.5*Lept2_pcIso04))
            /Lept2_pt;


	//Fill tree
        Zs.Lept1_genIdxMatch->push_back(idxMatch);
        Zs.Lept1_genDeltaR->push_back(BestGenDeltaR1);
        Zs.Lept1_genDPtRel->push_back(BesTdPtRel1);
        Zs.Lept1_chIso03->push_back(Lept1_chIso03);
        Zs.Lept1_chIso04->push_back(Lept1_chIso04);
        Zs.Lept1_nhIso03->push_back(Lept1_nhIso03);
        Zs.Lept1_nhIso04->push_back(Lept1_nhIso04);
        Zs.Lept1_phIso03->push_back(Lept1_phIso03);
        Zs.Lept1_phIso04->push_back(Lept1_phIso04);
        Zs.Lept1_pcIso03->push_back(Lept1_pcIso03);
        Zs.Lept1_pcIso04->push_back(Lept1_pcIso04);
        Zs.Lept1_relIsoCom03->push_back(Lept1_relIsoCom03);
        Zs.Lept1_relIsoCom04->push_back(Lept1_relIsoCom04);
        Zs.Lept1_relIsoBeta03->push_back(Lept1_relIsoBeta03);
        Zs.Lept1_relIsoBeta04->push_back(Lept1_relIsoBeta04);

        Zs.Lept2_genIdxMatch->push_back(idxMatch);
        Zs.Lept2_genDeltaR->push_back(BestGenDeltaR2);
        Zs.Lept2_genDPtRel->push_back(BesTdPtRel2);
        Zs.Lept2_chIso03->push_back(Lept2_chIso03);
        Zs.Lept2_chIso04->push_back(Lept2_chIso04);
        Zs.Lept2_nhIso03->push_back(Lept2_nhIso03);
        Zs.Lept2_nhIso04->push_back(Lept2_nhIso04);
        Zs.Lept2_phIso03->push_back(Lept2_phIso03);
        Zs.Lept2_phIso04->push_back(Lept2_phIso04);
        Zs.Lept2_pcIso03->push_back(Lept2_pcIso03);
        Zs.Lept2_pcIso04->push_back(Lept2_pcIso04);
        Zs.Lept2_relIsoCom03->push_back(Lept2_relIsoCom03);
        Zs.Lept2_relIsoCom04->push_back(Lept2_relIsoCom04);
        Zs.Lept2_relIsoBeta03->push_back(Lept2_relIsoBeta03);
        Zs.Lept2_relIsoBeta04->push_back(Lept2_relIsoBeta04);

        Zs.Lept1_isGlobal->push_back(Lept1_isGlobal);
        Zs.Lept1_isTrker->push_back(Lept1_isTrker);
        Zs.Lept1_pt->push_back(Lept1_pt);
        Zs.Lept1_et->push_back(Lept1_et);
        Zs.Lept1_charge->push_back(Lept1_charge);
        Zs.Lept1_eta->push_back(Lept1_eta);
        Zs.Lept1_phi->push_back(Lept1_phi);
        Zs.Lept1_px->push_back(Lept1_px);
        Zs.Lept1_py->push_back(Lept1_py);
        Zs.Lept1_pz->push_back(Lept1_pz);
        Zs.Lept1_en->push_back(Lept1_en);
        Zs.Lept1_matchStations->push_back(Lept1_matchStations);
        Zs.Lept1_dB->push_back(Lept1_dB);
        Zs.Lept2_isGlobal->push_back(Lept2_isGlobal);
        Zs.Lept2_isTrker->push_back(Lept2_isTrker);
        Zs.Lept2_pt->push_back(Lept2_pt);
        Zs.Lept2_et->push_back(Lept2_et);
        Zs.Lept2_charge->push_back(Lept2_charge);
        Zs.Lept2_eta->push_back(Lept2_eta);
        Zs.Lept2_phi->push_back(Lept2_phi);
        Zs.Lept2_px->push_back(Lept2_px);
        Zs.Lept2_py->push_back(Lept2_py);
        Zs.Lept2_pz->push_back(Lept2_pz);
        Zs.Lept2_en->push_back(Lept2_en);
        Zs.Lept2_matchStations->push_back(Lept2_matchStations);
        Zs.Lept2_dB->push_back(Lept2_dB);

        Zs.Lept1_dz->push_back(Lept1_dz);
        Zs.Lept1_globalNormChi2->push_back(Lept1_globalNormChi2);
        Zs.Lept1_muonHits->push_back(Lept1_muonHits);
        Zs.Lept1_trkLayers->push_back(Lept1_trkLayers);
        Zs.Lept1_trackerHits->push_back(Lept1_trackerHits);
        Zs.Lept1_pixelHits->push_back(Lept1_pixelHits);
        Zs.Lept2_dz->push_back(Lept2_dz);
        Zs.Lept2_globalNormChi2->push_back(Lept2_globalNormChi2);
        Zs.Lept2_muonHits->push_back(Lept2_muonHits);
        Zs.Lept2_trkLayers->push_back(Lept2_trkLayers);
        Zs.Lept2_trackerHits->push_back(Lept2_trackerHits);
        Zs.Lept2_pixelHits->push_back(Lept2_pixelHits);

        //dphimetlepton1 = fabs(deltaPhi(MetIt->phi(),it1.phi()));
        //dphimetlepton2 = fabs(deltaPhi(MetIt->phi(),it2.phi()));
 
	Zs.diLeptVtxProb->push_back(Dimuon.diLeptVtxProb());
        Zs.ZMass->push_back( Dimuon.mass());
        Zs.phi->push_back( Dimuon.phi());
        Zs.eta->push_back( Dimuon.eta());
        Zs.pt->push_back( Dimuon.pt());
        Zs.px->push_back( Dimuon.px());
        Zs.py->push_back( Dimuon.py());
        Zs.pz->push_back( Dimuon.pz());
        Zs.Neut_pt->push_back( pfMEt4V->Pt());
        Zs.Neut_phi->push_back( pfMEt_It->phi());
        Zs.Neut_px->push_back( pfMEt_It->px());
        Zs.Neut_py->push_back( pfMEt_It->py());
	Zs.Sign->push_back(Dimuon.sign()); //--(-2), +-(0), ++(2)
        
        h_lept1_pt->Fill(it1.pt());
        h_lept2_pt->Fill(it2.pt());
        h_Zmass->Fill(Dimuon.mass());

        //break;
      }//mu2_hand
      //break;
    }//mu1_hand
}
void ZNtupleMaker::LoopElectron(const edm::Event &iEvent, const edm::EventSetup& iSetup)
{
    //bool goodVtx=false;
    for(unsigned i = 0; i < ele1_hand->size(); i++)
    {
      pat::Electron it1 = ele1_hand->at(i);
      it1.setP4(it1.pfCandidateRef()->p4());
      const Ky::Lepton lep1(it1.p4(), (int) it1.charge());
      lepton1->push_back(lep1);
      Lept1_pt = it1.pt();
      Lept1_et = it1.et();
      Lept1_charge = it1.charge();
      Lept1_eta = it1.eta();
      Lept1_phi = it1.phi();
      Lept1_px =it1.px();
      Lept1_py =it1.py();
      Lept1_pz =it1.pz();
      Lept1_en =it1.energy();
      Lept1_etaSC = it1.superCluster()->eta();
      Lept1_phiSC = it1.superCluster()->phi();
      Lept1_dEtaIn = it1.deltaEtaSuperClusterTrackAtVtx();
      Lept1_dPhiIn = it1.deltaPhiSuperClusterTrackAtVtx();
      Lept1_sigmaIEtaIEta = it1.sigmaIetaIeta();
      Lept1_HoverE = it1.hadronicOverEm();
      Lept1_fbrem = it1.fbrem();
      Lept1_energyEC = it1.ecalEnergy();
      Lept1_Pnorm = it1.trackMomentumAtVtx().R();
      Lept1_InvEminusInvP = 1/Lept1_energyEC - 1/Lept1_Pnorm;

      Lept1_RelisolPtTrks03 = it1.dr03TkSumPt()/Lept1_pt;
      Lept1_RelisoEm03      = it1.dr03EcalRecHitSumEt()/Lept1_pt;
      Lept1_RelisoHad03     = it1.dr03HcalTowerSumEt()/Lept1_pt;
      Lept1_SCcharge = it1.chargeInfo().scPixCharge;
      Lept1_TKcharge = it1.closestCtfTrackRef().isNonnull() ? it1.closestCtfTrackRef()->charge():-9999;
      Lept1_GSFcharge = it1.gsfTrack()->charge();
      Lept1_GsfCtfScPixchargeConsistentcheck = it1.isGsfCtfScPixChargeConsistent();


      if( recVtxs_->size() > 0)
      {
	reco::VertexRef vtx(recVtxs_,0);
	Lept1_dxy = it1.gsfTrack()->dxy(vtx->position());
	Lept1_dz = it1.gsfTrack()->dz(vtx->position());
      }else{
	Lept1_dxy = it1.gsfTrack()->dxy();
	Lept1_dz = it1.gsfTrack()->dz();
      }
      Direction Dir = Direction(Lept1_etaSC, Lept1_phiSC);
      if(isRD){
	Lept1_AEff03 = ElectronEffectiveArea::GetElectronEffectiveArea(
	    ElectronEffectiveArea::kEleGammaAndNeutralHadronIso03,
	    Lept1_etaSC,
	    ElectronEffectiveArea::kEleEAData2012);
      }else{
	Lept1_AEff03 = ElectronEffectiveArea::GetElectronEffectiveArea(
	    ElectronEffectiveArea::kEleGammaAndNeutralHadronIso03,
	    Lept1_etaSC,
	    ElectronEffectiveArea::kEleEAData2012);
      }
      //Pf isolation
      reco::isodeposit::AbsVetos vetos_ch;
      reco::isodeposit::AbsVetos vetos_nh;
      reco::isodeposit::AbsVetos vetos_ph;
      //vetos_nh.push_back(new ThresholdVeto( 0.5 ));
      //vetos_ph.push_back(new ThresholdVeto( 0.5 ));
      //PF isolation electron veto from EGM (updated the 4 April 2012)
      if(fabs(Lept1_etaSC > 1.479) )
      {
	vetos_ch.push_back(new ConeVeto(Dir, 0.015));
	vetos_ph.push_back(new ConeVeto(Dir, 0.08));
      }

      //If you want to try neutral hadron (electron leakage to Hcal) or photon (for example FSR) veto around lepton
      //reco::isodeposit::Direction Dir1 = Direction(it1.eta(),it1.phi());
      //reco::isodeposit::Direction Dir1 = Direction(it1.superCluster()->eta(),it1.superCluster()->phi());
      //vetos_nh.push_back(new RectangularEtaPhiVeto(Dir, -0.1,0.1,-0.2,0.2));
      //vetos_nh.push_back(new ConeVeto(Dir,0.1);
      //vetos_ph.push_back(new RectangularEtaPhiVeto(Dir, -0.1,0.1,-0.2,0.2));
      //vetos_ph.push_back(new ConeVeto(Dir,0.1);
      lepton1->back().setIsoDeposit( pat::PfChargedHadronIso, it1.isoDeposit(pat::PfChargedHadronIso), vetos_ch );
      lepton1->back().setIsoDeposit( pat::PfNeutralHadronIso, it1.isoDeposit(pat::PfNeutralHadronIso), vetos_nh );
      lepton1->back().setIsoDeposit( pat::PfGammaIso, it1.isoDeposit(pat::PfGammaIso), vetos_ph );
      lepton1->back().setIsoDeposit( pat::PfPUChargedHadronIso, it1.isoDeposit(pat::PfPUChargedHadronIso), vetos_ch );
      //detector based isolation
      lepton1->back().setIsoDeposit( it1.trackIso(), it1.ecalIso(), it1.hcalIso());

      Lept1_chIso03 = lepton1->back().chIso03();
      Lept1_chIso04 = lepton1->back().chIso04();
      Lept1_nhIso03 = lepton1->back().nhIso03();
      Lept1_nhIso04 = lepton1->back().nhIso04();
      Lept1_phIso03 = lepton1->back().phIso03();
      Lept1_phIso04 = lepton1->back().phIso04();
      Lept1_pcIso03 = lepton1->back().pcIso03();
      Lept1_pcIso04 = lepton1->back().pcIso04();

      Lept1_relIsoCom03 = (Lept1_chIso03 + Lept1_nhIso03 + Lept1_phIso03)/Lept1_pt;
      Lept1_relIsoCom04 = (Lept1_chIso04 + Lept1_nhIso04 + Lept1_phIso04)/Lept1_pt;
      Lept1_relIsoBeta03 = (Lept1_chIso03+
	  max(0.0, Lept1_nhIso03 + Lept1_phIso03 - 0.5*Lept1_pcIso03))
	  /Lept1_pt;
      Lept1_relIsoBeta04 = (Lept1_chIso04+
	  max(0.0, Lept1_nhIso04 + Lept1_phIso04 - 0.5*Lept1_pcIso04))
	  /Lept1_pt;
      Lept1_relIsoRho03 = (Lept1_chIso03 +
	  max(0.0, Lept1_nhIso03 + Lept1_phIso03 - rhoIso*Lept1_AEff03))
	/Lept1_pt;
      Lept1_hasConversion = ConversionTools::hasMatchedConversion(it1,conversions_h, beamSpot_h->position());
      Lept1_mHits = it1.gsfTrack()->trackerExpectedHitsInner().numberOfHits();

      for(unsigned j = i+1; j < ele2_hand->size(); j++)
      {
	pat::Electron it2 = ele2_hand->at(j);
        it2.setP4(it2.pfCandidateRef()->p4());

        //const bool match = MatchObjects( it1.p4(), it2.p4(), true);
        ////if(match) continue;

        const Ky::Lepton lep2(it2.p4(), (int) it2.charge());
        lepton2->push_back(lep2);

        Lept2_pt = it2.pt();
        Lept2_et = it2.et();
        Lept2_charge = it2.charge();
        Lept2_eta = it2.eta();
        Lept2_phi = it2.phi();
        Lept2_px=it2.px();
        Lept2_py=it2.py();
        Lept2_pz=it2.pz();
        Lept2_en=it2.energy();
        Lept2_etaSC = it2.superCluster()->eta();
        Lept2_phiSC = it2.superCluster()->phi();
        Lept2_dEtaIn = it2.deltaEtaSuperClusterTrackAtVtx();
        Lept2_dPhiIn = it2.deltaPhiSuperClusterTrackAtVtx();
        Lept2_sigmaIEtaIEta = it2.sigmaIetaIeta();
        Lept2_HoverE = it2.hadronicOverEm();
        Lept2_fbrem = it2.fbrem();
        Lept2_energyEC = it2.ecalEnergy();
        Lept2_Pnorm = it2.trackMomentumAtVtx().R();
        Lept2_InvEminusInvP = 1/Lept2_energyEC - 1/Lept2_Pnorm;

	Lept2_RelisolPtTrks03 = it2.dr03TkSumPt()/Lept2_pt;
	Lept2_RelisoEm03      = it2.dr03EcalRecHitSumEt()/Lept2_pt;
	Lept2_RelisoHad03     = it2.dr03HcalTowerSumEt()/Lept2_pt;
        Lept2_SCcharge = it2.chargeInfo().scPixCharge;
        Lept2_TKcharge = it2.closestCtfTrackRef().isNonnull() ? it2.closestCtfTrackRef()->charge():-9999;
        Lept2_GSFcharge = it2.gsfTrack()->charge();
        Lept2_GsfCtfScPixchargeConsistentcheck = it2.isGsfCtfScPixChargeConsistent();

        if( recVtxs_->size() > 0)
        {
          reco::VertexRef vtx(recVtxs_,0);
          Lept2_dxy = it2.gsfTrack()->dxy(vtx->position());
          Lept2_dz = it2.gsfTrack()->dz(vtx->position());
        }else{
          Lept2_dxy = it2.gsfTrack()->dxy();
          Lept2_dz = it2.gsfTrack()->dz();
        }
        //Direction Dir2 = Direction(Lept2_etaSC, Lept2_phiSC);
        if(isRD){
          Lept2_AEff03 = ElectronEffectiveArea::GetElectronEffectiveArea(
              ElectronEffectiveArea::kEleGammaAndNeutralHadronIso03,
              Lept2_etaSC,
              ElectronEffectiveArea::kEleEAData2011);
        }else{
          Lept2_AEff03 = ElectronEffectiveArea::GetElectronEffectiveArea(
              ElectronEffectiveArea::kEleGammaAndNeutralHadronIso03,
              Lept2_etaSC,
              ElectronEffectiveArea::kEleEAFall11MC);
        }
        //Pf isolation
        reco::isodeposit::AbsVetos vetos_ch2;
        reco::isodeposit::AbsVetos vetos_nh2;
        reco::isodeposit::AbsVetos vetos_ph2;
        //vetos_nh2.push_back(new ThresholdVeto( 0.5 ));
        //vetos_ph2.push_back(new ThresholdVeto( 0.5 ));
        //If you want to try neutral hadron (electron leakage to Hcal) or photon (for example FSR) veto around lepton
        if(fabs(Lept2_etaSC > 1.479) )
        {
	  vetos_ch2.push_back(new ConeVeto(Dir, 0.015));
	  vetos_ph2.push_back(new ConeVeto(Dir, 0.08));
        }
        lepton2->back().setIsoDeposit( pat::PfChargedHadronIso, it2.isoDeposit(pat::PfChargedHadronIso), vetos_ch2 );
        lepton2->back().setIsoDeposit( pat::PfNeutralHadronIso, it2.isoDeposit(pat::PfNeutralHadronIso), vetos_nh2 );
        lepton2->back().setIsoDeposit( pat::PfGammaIso, it2.isoDeposit(pat::PfGammaIso), vetos_ph2 );
        lepton2->back().setIsoDeposit( pat::PfPUChargedHadronIso, it2.isoDeposit(pat::PfPUChargedHadronIso), vetos_ch2 );
 
        //detector based isolation
        lepton2->back().setIsoDeposit( it2.trackIso(), it2.ecalIso(), it2.hcalIso());
        Lept2_chIso03 = lepton2->back().chIso03();
        Lept2_chIso04 = lepton2->back().chIso04();
        Lept2_nhIso03 = lepton2->back().nhIso03();
        Lept2_nhIso04 = lepton2->back().nhIso04();
        Lept2_phIso03 = lepton2->back().phIso03();
        Lept2_phIso04 = lepton2->back().phIso04();
        Lept2_pcIso03 = lepton2->back().pcIso03();
        Lept2_pcIso04 = lepton2->back().pcIso04();

        Lept2_relIsoCom03 = (Lept2_chIso03 + Lept2_nhIso03 + Lept2_phIso03)/Lept2_pt;
        Lept2_relIsoCom04 = (Lept2_chIso04 + Lept2_nhIso04 + Lept2_phIso04)/Lept2_pt;
        Lept2_relIsoBeta03 = (Lept2_chIso03+
            max(0.0, Lept2_nhIso03 + Lept2_phIso03 - 0.5*Lept2_pcIso03))
            /Lept2_pt;
        Lept2_relIsoBeta04 = (Lept2_chIso04+
            max(0.0, Lept2_nhIso04 + Lept2_phIso04 - 0.5*Lept2_pcIso04))
            /Lept2_pt;
        Lept2_relIsoRho03 = (Lept2_chIso03 +
            max(0.0, Lept2_nhIso03 + Lept2_phIso03 - rhoIso*Lept2_AEff03))
          /Lept2_pt;
        Lept2_hasConversion = ConversionTools::hasMatchedConversion(it2,conversions_h, beamSpot_h->position());
        Lept2_mHits = it2.gsfTrack()->trackerExpectedHitsInner().numberOfHits();

        //vertexfit
        Ky::ZCandidate Dimuon(lepton1->back(), lepton2->back());
	//ESHandle<MagneticField> B_h;
	//iSetup.get<IdealMagneticFieldRecord>().get(B_h);
	//const MagneticField *B = B_h.product();
	ESHandle<TransientTrackBuilder> trackBuilder;
	iSetup.get<TransientTrackRecord>().get("TransientTrackBuilder",trackBuilder);
	if(it1.gsfTrack().isNonnull() && it2.gsfTrack().isNonnull())
	{
	reco::TransientTrack transientTrk1 = trackBuilder->build(it1.gsfTrack());
	reco::TransientTrack transientTrk2 = trackBuilder->build(it2.gsfTrack());
	//reco::TransientTrack transientTrk1(it1.gsfTrack(),B);
	//reco::TransientTrack transientTrk2(it2.gsfTrack(),B);
	//reco::TransientTrack transientTrk1(it1.track(),B);
	//reco::TransientTrack transientTrk2(it2.track(),B);
	Dimuon.KalmanVtxFit(transientTrk1, transientTrk2);
	}
	if( !isRD && GenZs.nLepts->size() > 0 && Channel == "Electron")
	{
	  //Loop all GenZs-------------
	  for( unsigned int iGen(0);iGen<GenZs.nLepts->size();iGen++)
	  {
	    genDeltaR1 = -999;genDeltaR2 = -999;
	    dPtRel1 = -999;dPtRel2 = -999;
	    idxMatch = -999;
	    if( (*GenZs.nLepts)[iGen] != 2)continue;
	    if( abs((*GenZs.Lept1_id)[iGen]) != GenType::kElectron) continue;
	    if( abs((*GenZs.Lept2_id)[iGen]) != GenType::kElectron) continue;
	    genDeltaR1 = deltaR( (*GenZs.Lept1_eta)[iGen],(*GenZs.Lept1_phi)[iGen],
	                          Lept1_eta, Lept1_phi);
	    dPtRel1 = fabs(Lept1_pt-(*GenZs.Lept1_pt)[iGen])/(*GenZs.Lept1_pt)[iGen];
	    genDeltaR2 = deltaR( (*GenZs.Lept2_eta)[iGen],(*GenZs.Lept2_phi)[iGen],
		  Lept2_eta, Lept2_phi);
	    dPtRel2 = fabs(Lept2_pt-(*GenZs.Lept2_pt)[iGen])/(*GenZs.Lept2_pt)[iGen];
	    //if( genDeltaR1 < 0.025 && genDeltaR2 < 0.025) break;
	    if( genDeltaR1 < 0.03 && genDeltaR2 < 0.03)
	    //if( genDeltaR1 < 0.025 && genDeltaR2 < 0.025)
	     // if(dPtRel1 < 0.025 && dPtRel2 < 0.025)
	    {
	        idxMatch = iGen;
		break;
	    }
	    // vice versa
	    genDeltaR1 = deltaR( (*GenZs.Lept2_eta)[iGen],(*GenZs.Lept2_phi)[iGen],
		  Lept1_eta, Lept1_phi);
	    dPtRel1 = fabs(Lept1_pt-(*GenZs.Lept2_pt)[iGen])/(*GenZs.Lept2_pt)[iGen];
	    genDeltaR2 = deltaR( (*GenZs.Lept1_eta)[iGen],(*GenZs.Lept1_phi)[iGen],
		  Lept2_eta, Lept2_phi);
	    dPtRel2 = fabs(Lept2_pt-(*GenZs.Lept1_pt)[iGen])/(*GenZs.Lept1_pt)[iGen];
	    //if( genDeltaR1 < 0.025 && genDeltaR2 < 0.025) break;
	    if( genDeltaR1 < 0.03 && genDeltaR2 < 0.03)
	    {
	      idxMatch = iGen;
	      break;
	    }
	    //if( genDeltaR1 < 0.025 && genDeltaR2 < 0.025)
	    //  if(dPtRel1 < 0.025 && dPtRel2 < 0.025)break;
	  }
	}

        Zs.Lept1_genIdxMatch->push_back(idxMatch);
        Zs.Lept1_genDeltaR->push_back(genDeltaR1);
        Zs.Lept1_genDPtRel->push_back(dPtRel1);

        Zs.Lept1_pt->push_back(Lept1_pt);
        Zs.Lept1_et->push_back(Lept1_et);
        Zs.Lept1_charge->push_back(Lept1_charge);
        Zs.Lept1_eta->push_back(Lept1_eta);
        Zs.Lept1_phi->push_back(Lept1_phi);
        Zs.Lept1_px->push_back(Lept1_px);
        Zs.Lept1_py->push_back(Lept1_py);
        Zs.Lept1_pz->push_back(Lept1_pz);
        Zs.Lept1_en->push_back(Lept1_en);
        Zs.Lept1_etaSC->push_back(Lept1_etaSC);
        Zs.Lept1_phiSC->push_back(Lept1_phiSC);
        Zs.Lept1_dEtaIn->push_back(Lept1_dEtaIn);
        Zs.Lept1_dPhiIn->push_back(Lept1_dPhiIn);
        Zs.Lept1_sigmaIEtaIEta->push_back(Lept1_sigmaIEtaIEta);
        Zs.Lept1_HoverE->push_back(Lept1_HoverE);
        Zs.Lept1_fbrem->push_back(Lept1_fbrem);
        Zs.Lept1_energyEC->push_back(Lept1_energyEC);
        Zs.Lept1_Pnorm->push_back(Lept1_Pnorm);
        Zs.Lept1_InvEminusInvP->push_back(Lept1_InvEminusInvP);
        Zs.Lept1_dxy->push_back(Lept1_dxy);
        Zs.Lept1_dz->push_back(Lept1_dz);
        Zs.Lept1_AEff03->push_back(Lept1_AEff03);
        Zs.Lept1_chIso03->push_back(Lept1_chIso03);
        Zs.Lept1_chIso04->push_back(Lept1_chIso04);
        Zs.Lept1_nhIso03->push_back(Lept1_nhIso03);
        Zs.Lept1_nhIso04->push_back(Lept1_nhIso04);
        Zs.Lept1_phIso03->push_back(Lept1_phIso03);
        Zs.Lept1_phIso04->push_back(Lept1_phIso04);
        Zs.Lept1_pcIso03->push_back(Lept1_pcIso03);
        Zs.Lept1_pcIso04->push_back(Lept1_pcIso04);
        Zs.Lept1_relIsoCom03->push_back(Lept1_relIsoCom03);
        Zs.Lept1_relIsoCom04->push_back(Lept1_relIsoCom04);
        Zs.Lept1_relIsoBeta03->push_back(Lept1_relIsoBeta03);
        Zs.Lept1_relIsoBeta04->push_back(Lept1_relIsoBeta04);
        Zs.Lept1_relIsoRho03->push_back(Lept1_relIsoRho03);
        Zs.Lept1_hasConversion->push_back(Lept1_hasConversion);
        Zs.Lept1_mHits->push_back(Lept1_mHits);
        Zs.Lept1_SCcharge->push_back(Lept1_SCcharge);
        Zs.Lept1_TKcharge->push_back(Lept1_TKcharge);
        Zs.Lept1_GSFcharge->push_back(Lept1_GSFcharge);
        Zs.Lept1_GsfCtfScPixchargeConsistentcheck->push_back(Lept1_GsfCtfScPixchargeConsistentcheck);

	Zs.Lept1_RelisolPtTrks03->push_back(Lept1_RelisolPtTrks03);
	Zs.Lept1_RelisoEm03     ->push_back(Lept1_RelisoEm03);
	Zs.Lept1_RelisoHad03    ->push_back(Lept1_RelisoHad03);

        Zs.Lept2_genIdxMatch->push_back(idxMatch);
        Zs.Lept2_genDeltaR->push_back(genDeltaR2);
        Zs.Lept2_genDPtRel->push_back(dPtRel2);

        Zs.Lept2_pt->push_back(Lept2_pt);
        Zs.Lept2_et->push_back(Lept2_et);
        Zs.Lept2_charge->push_back(Lept2_charge);
        Zs.Lept2_eta->push_back(Lept2_eta);
        Zs.Lept2_phi->push_back(Lept2_phi);
        Zs.Lept2_px->push_back(Lept2_px);
        Zs.Lept2_py->push_back(Lept2_py);
        Zs.Lept2_pz->push_back(Lept2_pz);
        Zs.Lept2_en->push_back(Lept2_en);
        Zs.Lept2_etaSC->push_back(Lept2_etaSC);
        Zs.Lept2_phiSC->push_back(Lept2_phiSC);
        Zs.Lept2_dEtaIn->push_back(Lept2_dEtaIn);
        Zs.Lept2_dPhiIn->push_back(Lept2_dPhiIn);
        Zs.Lept2_sigmaIEtaIEta->push_back(Lept2_sigmaIEtaIEta);
        Zs.Lept2_HoverE->push_back(Lept2_HoverE);
        Zs.Lept2_fbrem->push_back(Lept2_fbrem);
        Zs.Lept2_energyEC->push_back(Lept2_energyEC);
        Zs.Lept2_Pnorm->push_back(Lept2_Pnorm);
        Zs.Lept2_InvEminusInvP->push_back(Lept2_InvEminusInvP);
        Zs.Lept2_dxy->push_back(Lept2_dxy);
        Zs.Lept2_dz->push_back(Lept2_dz);
        Zs.Lept2_AEff03->push_back(Lept2_AEff03);
        Zs.Lept2_chIso03->push_back(Lept2_chIso03);
        Zs.Lept2_chIso04->push_back(Lept2_chIso04);
        Zs.Lept2_nhIso03->push_back(Lept2_nhIso03);
        Zs.Lept2_nhIso04->push_back(Lept2_nhIso04);
        Zs.Lept2_phIso03->push_back(Lept2_phIso03);
        Zs.Lept2_phIso04->push_back(Lept2_phIso04);
        Zs.Lept2_pcIso03->push_back(Lept2_pcIso03);
        Zs.Lept2_pcIso04->push_back(Lept2_pcIso04);
        Zs.Lept2_relIsoCom03->push_back(Lept2_relIsoCom03);
        Zs.Lept2_relIsoCom04->push_back(Lept2_relIsoCom04);
        Zs.Lept2_relIsoBeta03->push_back(Lept2_relIsoBeta03);
        Zs.Lept2_relIsoBeta04->push_back(Lept2_relIsoBeta04);
        Zs.Lept2_relIsoRho03->push_back(Lept2_relIsoRho03);
        Zs.Lept2_hasConversion->push_back(Lept2_hasConversion);
        Zs.Lept2_mHits->push_back(Lept2_mHits);
        Zs.Lept2_SCcharge->push_back(Lept2_SCcharge);
        Zs.Lept2_TKcharge->push_back(Lept2_TKcharge);
        Zs.Lept2_GSFcharge->push_back(Lept2_GSFcharge);
        Zs.Lept2_GsfCtfScPixchargeConsistentcheck->push_back(Lept2_GsfCtfScPixchargeConsistentcheck);

	Zs.Lept2_RelisolPtTrks03->push_back(Lept2_RelisolPtTrks03);
	Zs.Lept2_RelisoEm03     ->push_back(Lept2_RelisoEm03);
	Zs.Lept2_RelisoHad03    ->push_back(Lept2_RelisoHad03);



 
	Zs.diLeptVtxProb->push_back(Dimuon.diLeptVtxProb());
        Zs.ZMass->push_back( Dimuon.mass());
        Zs.phi->push_back( Dimuon.phi());
        Zs.eta->push_back( Dimuon.eta());
        Zs.pt->push_back( Dimuon.pt());
        Zs.px->push_back( Dimuon.px());
        Zs.py->push_back( Dimuon.py());
        Zs.pz->push_back( Dimuon.pz());
        Zs.Neut_pt->push_back( pfMEt4V->Pt());
        Zs.Neut_phi->push_back( pfMEt_It->phi());
        Zs.Neut_px->push_back( pfMEt_It->px());
        Zs.Neut_py->push_back( pfMEt_It->py());
	Zs.Sign->push_back(Dimuon.sign()); //--(-2), +-(0), ++(2)
        
        h_lept1_pt->Fill(it1.pt());
        h_lept2_pt->Fill(it2.pt());
        h_Zmass->Fill(Dimuon.mass());

        //break;
      }//ele2_hand
      //break;
    }//ele1_hand
}
void ZNtupleMaker::LoopTau(const edm::Event &iEvent, const edm::EventSetup& iSetup)
{
    //bool goodVtx=false;
    for(unsigned i = 0; i < tau1_hand->size(); i++)
    {
      pat::Tau it1 = tau1_hand->at(i);
      //it1.setP4(it1.pfCandidateRef()->p4());
      const Ky::Lepton lep1(it1.p4(), (int) it1.charge());
      lepton1->push_back(lep1);
      Lept1_MedComIsoDelBetCorr3Hits = it1.tauID("byMediumCombinedIsolationDeltaBetaCorr3Hits");
      Lept1_decModFind = it1.tauID("decayModeFinding");
      //Lept1_MedComIsoDelBetCorr = it1.tauID("byMediumCombinedIsolationDeltaBetaCorr");
      //cout<<"MedComIsoDelBetCorr3Hits:"<<Lept1_MedComIsoDelBetCorr3Hits<<endl;
      Lept1_pt = it1.pt();
      Lept1_et = it1.et();
      Lept1_charge = it1.charge();
      Lept1_eta = it1.eta();
      Lept1_phi = it1.phi();
      Lept1_px =it1.px();
      Lept1_py =it1.py();
      Lept1_pz =it1.pz();
      Lept1_en =it1.energy();

      for(unsigned j = i+1; j < tau2_hand->size(); j++)
      {
	pat::Tau it2 = tau2_hand->at(j);
        //it2.setP4(it2.pfCandidateRef()->p4());

        //const bool match = MatchObjects( it1.p4(), it2.p4(), true);
        ////if(match) continue;

        const Ky::Lepton lep2(it2.p4(), (int) it2.charge());
        lepton2->push_back(lep2);

        Lept2_MedComIsoDelBetCorr3Hits = it2.tauID("byMediumCombinedIsolationDeltaBetaCorr3Hits");
        Lept2_decModFind = it2.tauID("decayModeFinding");
        Lept2_pt = it2.pt();
        Lept2_et = it2.et();
        Lept2_charge = it2.charge();
        Lept2_eta = it2.eta();
        Lept2_phi = it2.phi();
        Lept2_px=it2.px();
        Lept2_py=it2.py();
        Lept2_pz=it2.pz();
        Lept2_en=it2.energy();

        //vertexfit
        Ky::ZCandidate DiTau(lepton1->back(), lepton2->back());
	// Old =========================================
	//ESHandle<MagneticField> B_h;
	//iSetup.get<IdealMagneticFieldRecord>().get(B_h);
	//const MagneticField *B = B_h.product();
	//==============================================
	//ESHandle<TransientTrackBuilder> trackBuilder;
	//iSetup.get<TransientTrackRecord>().get("TransientTrackBuilder",trackBuilder);
	//if(it1.gsfTrack().isNonnull() && it2.gsfTrack().isNonnull())
	//{
	//reco::TransientTrack transientTrk1 = trackBuilder->build(it1.gsfTrack());
	//reco::TransientTrack transientTrk2 = trackBuilder->build(it2.gsfTrack());
	//Dimuon.KalmanVtxFit(transientTrk1, transientTrk2);
	//}
	if( !isRD && GenZs.nLepts->size() > 0 && Channel == "Tau")
	{
	  //Loop all GenZs-------------
	  for( unsigned int iGen(0);iGen<GenZs.nLepts->size();iGen++)
	  {
	    genDeltaR1 = -999;genDeltaR2 = -999;
	    dPtRel1 = -999;dPtRel2 = -999;
	    idxMatch = -999;
	    if( (*GenZs.nLepts)[iGen] != 2)continue;
//	    if( abs((*GenZs.Lept1_id)[iGen]) != GenType::kElectron) continue;
//	    if( abs((*GenZs.Lept2_id)[iGen]) != GenType::kElectron) continue;
	    if( abs((*GenZs.Lept1_id)[iGen]) != GenType::kTau) continue;
	    if( abs((*GenZs.Lept2_id)[iGen]) != GenType::kTau) continue;
	    genDeltaR1 = deltaR( (*GenZs.Lept1_eta)[iGen],(*GenZs.Lept1_phi)[iGen],
	                          Lept1_eta, Lept1_phi);
	    dPtRel1 = fabs(Lept1_pt-(*GenZs.Lept1_pt)[iGen])/(*GenZs.Lept1_pt)[iGen];
	    genDeltaR2 = deltaR( (*GenZs.Lept2_eta)[iGen],(*GenZs.Lept2_phi)[iGen],
		  Lept2_eta, Lept2_phi);
	    dPtRel2 = fabs(Lept2_pt-(*GenZs.Lept2_pt)[iGen])/(*GenZs.Lept2_pt)[iGen];
	    //if( genDeltaR1 < 0.025 && genDeltaR2 < 0.025) break;
	    if( genDeltaR1 < 0.03 && genDeltaR2 < 0.03)
	    //if( genDeltaR1 < 0.025 && genDeltaR2 < 0.025)
	     // if(dPtRel1 < 0.025 && dPtRel2 < 0.025)
	    {
	        idxMatch = iGen;
		break;
	    }
	    // vice versa
	    genDeltaR1 = deltaR( (*GenZs.Lept2_eta)[iGen],(*GenZs.Lept2_phi)[iGen],
		  Lept1_eta, Lept1_phi);
	    dPtRel1 = fabs(Lept1_pt-(*GenZs.Lept2_pt)[iGen])/(*GenZs.Lept2_pt)[iGen];
	    genDeltaR2 = deltaR( (*GenZs.Lept1_eta)[iGen],(*GenZs.Lept1_phi)[iGen],
		  Lept2_eta, Lept2_phi);
	    dPtRel2 = fabs(Lept2_pt-(*GenZs.Lept1_pt)[iGen])/(*GenZs.Lept1_pt)[iGen];
	    //if( genDeltaR1 < 0.025 && genDeltaR2 < 0.025) break;
	    if( genDeltaR1 < 0.03 && genDeltaR2 < 0.03)
	    {
	      idxMatch = iGen;
	      break;
	    }
	    //if( genDeltaR1 < 0.025 && genDeltaR2 < 0.025)
	    //  if(dPtRel1 < 0.025 && dPtRel2 < 0.025)break;
	  }
	}

        Zs.Lept1_genIdxMatch->push_back(idxMatch);
        Zs.Lept1_genDeltaR->push_back(genDeltaR1);
        Zs.Lept1_genDPtRel->push_back(dPtRel1);

        Zs.Lept1_MedComIsoDelBetCorr3Hits->push_back(Lept1_MedComIsoDelBetCorr3Hits);
        Zs.Lept1_decModFind->push_back(Lept1_decModFind);
        Zs.Lept1_pt->push_back(Lept1_pt);
        Zs.Lept1_et->push_back(Lept1_et);
        Zs.Lept1_charge->push_back(Lept1_charge);
        Zs.Lept1_eta->push_back(Lept1_eta);
        Zs.Lept1_phi->push_back(Lept1_phi);
        Zs.Lept1_px->push_back(Lept1_px);
        Zs.Lept1_py->push_back(Lept1_py);
        Zs.Lept1_pz->push_back(Lept1_pz);
        Zs.Lept1_en->push_back(Lept1_en);

        Zs.Lept2_genIdxMatch->push_back(idxMatch);
        Zs.Lept2_genDeltaR->push_back(genDeltaR2);
        Zs.Lept2_genDPtRel->push_back(dPtRel2);

        Zs.Lept2_MedComIsoDelBetCorr3Hits->push_back(Lept2_MedComIsoDelBetCorr3Hits);
        Zs.Lept2_decModFind->push_back(Lept2_decModFind);
        Zs.Lept2_pt->push_back(Lept2_pt);
        Zs.Lept2_et->push_back(Lept2_et);
        Zs.Lept2_charge->push_back(Lept2_charge);
        Zs.Lept2_eta->push_back(Lept2_eta);
        Zs.Lept2_phi->push_back(Lept2_phi);
        Zs.Lept2_px->push_back(Lept2_px);
        Zs.Lept2_py->push_back(Lept2_py);
        Zs.Lept2_pz->push_back(Lept2_pz);
        Zs.Lept2_en->push_back(Lept2_en);
        //dphimetlepton1 = fabs(deltaPhi(MetIt->phi(),it1.phi()));
        //dphimetlepton2 = fabs(deltaPhi(MetIt->phi(),it2.phi()));

 
        Zs.ZMass->push_back( DiTau.mass());
        Zs.phi->push_back( DiTau.phi());
        Zs.eta->push_back( DiTau.eta());
        Zs.pt->push_back( DiTau.pt());
        Zs.px->push_back( DiTau.px());
        Zs.py->push_back( DiTau.py());
        Zs.pz->push_back( DiTau.pz());
        Zs.Neut_pt->push_back( pfMEt4V->Pt());
        Zs.Neut_phi->push_back( pfMEt_It->phi());
        Zs.Neut_px->push_back( pfMEt_It->px());
        Zs.Neut_py->push_back( pfMEt_It->py());
	Zs.Sign->push_back(DiTau.sign()); //--(-2), +-(0), ++(2)
        
        h_lept1_pt->Fill(it1.pt());
        h_lept2_pt->Fill(it2.pt());
        h_Zmass->Fill(DiTau.mass());
        //break;
      }//ele2_hand
      //break;
    }//ele1_hand
}
void ZNtupleMaker::endJob()
{
}
void ZNtupleMaker::endRun(edm::Run const&, edm::EventSetup const&)
{
}
void ZNtupleMaker::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
