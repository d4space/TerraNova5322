// $Id: TTsemiLeptAnalyzer.h,v 1.17 2013/09/13 00:09:33 salee Exp $
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
#include "DataFormats/JetReco/interface/PileupJetIdentifier.h"

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

#include "TerraNova/DataFormats/interface/Lepton.h"
#include "TerraNova/DataFormats/interface/ZCandidate.h"
#include "TerraNova/DataFormats/interface/TTbarGenEvent.h"
#include "TerraNova/DataFormats/interface/TTbarMass.h"
#include "TerraNova/DataFormats/interface/WLeptNeuCand.h"
#include "TerraNova/DataFormats/interface/METCandidate.h"
#include "TerraNova/DataFormats/interface/Maos.h"

#include "TerraNova/NtupleMaker/interface/TTsemiLeptBranchVars.h"
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
using namespace isodeposit;

//template<typename T1, typename T2>
class TTsemiLeptAnalyzer : public edm::EDAnalyzer{
 public:
  explicit TTsemiLeptAnalyzer(const edm::ParameterSet& iConfig);
  ElectronEffectiveArea::ElectronEffectiveAreaTarget EAtarget;
  ~TTsemiLeptAnalyzer()
  {
  }

//===============================================================
private:
  virtual void beginJob();
  virtual void analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup);
  virtual void endJob();

  virtual void beginRun(const edm::Run& iRun, const edm::EventSetup& iSetup);
  virtual void endRun(const edm::Run&, const edm::EventSetup&);
  virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
//===============================================================

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

//InputTag=====================
  edm::InputTag leptonLabel_;
  edm::InputTag muonLabel2_;
  edm::InputTag pfMEtLabel_;
  edm::InputTag noPuMEtLabel_;
  edm::InputTag MVAMEtLabel_;
  edm::InputTag genMEtTrueLabel_;
  edm::InputTag genMEtCaloLabel_;
  edm::InputTag genMEtCaloAndNonPromptLabel_;
  edm::InputTag jetLabel_;
  edm::InputTag PUJetIdDisc;
  edm::InputTag PUJetId;
  edm::InputTag genParticlesLabel_;
  edm::InputTag vertexLabel_;
  edm::InputTag TriggerResultsTag;
  edm::InputTag rhoIsoInputTag;
  edm::InputTag conversionsInputTag;
  edm::InputTag beamSpotInputTag;
//Handle==========================
  edm::Handle<double>rhoIso_h;
  edm::Handle<reco::ConversionCollection>conversions_h;
  edm::Handle<reco::BeamSpot> beamSpot_h;
  edm::Handle<std::vector< PileupSummaryInfo > >  PupInfo;
  edm::Handle<std::vector<pat::Muon> > mu_hand;
  edm::Handle<std::vector<pat::Electron> > ele_hand;
  edm::Handle<std::vector<pat::Tau> > tau1_hand;
  edm::Handle<std::vector<pat::Tau> > tau2_hand;
  edm::Handle<pat::METCollection> pfMET_hand;
  edm::Handle<reco::PFMETCollection> NoPuMET_hand;
  edm::Handle<reco::PFMETCollection> MVaMET_hand;
  edm::Handle<reco::GenMETCollection> genMEtTrue_hand;
  edm::Handle<reco::GenMETCollection> genMEtCalo_hand;
  edm::Handle<reco::GenMETCollection> genMEtCaloAndNonPrompt_hand;
  edm::Handle<reco::VertexCollection> recVtxs_;
  edm::Handle<edm::View<reco::Jet> > Jets;
  //edm::Handle<pat::JetCollection> Jets;
  edm::Handle<edm::ValueMap<float> > PUJetIdMVA;
  edm::Handle<edm::ValueMap<int> >   PUJetIdFlag;

  //iterator------------------------------
  //typedef pat::JetCollection::const_iterator JI;
  edm::View<reco::Jet>::const_iterator i_jet;
  //pat::JetCollection::const_iterator i_jet;
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

  double JetPtMin;
  int nIdJets; // number of good jets
  //std::string bTagAlgo_;
  //double minBTagValue_;

  edm::Service<TFileService> fs;
  TTree* tree;
  EventBranches	EventData;
  TrigBranches	HLTData;
  TTsemi	TT;
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

  void GetHLTResults(const edm::Event &iEvent, const edm::EventSetup& iSetup);
  void clear();
  bool endLuminosityBlock(edm::LuminosityBlock & lumi, const edm::EventSetup & setup);
  bool checkOverlap(const double & eta, const double & phi, const double & dRval1,const double & reliso1, const double &dRval2, const double & reliso2);
  bool MatchObjects( const reco::Candidate::LorentzVector& pasObj,
      const reco::Candidate::LorentzVector& proObj,
      bool exact );
  
  void LoopMuon(const edm::Event &iEvent, const edm::EventSetup& iSetup);
  void LoopElectron(const edm::Event &iEvent, const edm::EventSetup& iSetup);

};

TTsemiLeptAnalyzer::TTsemiLeptAnalyzer(const edm::ParameterSet& iConfig)
{
    //now do what ever initialization is needed
    Channel = iConfig.getUntrackedParameter< std::string >("Channel");
    leptonLabel_ = iConfig.getParameter<edm::InputTag>("leptonLabel");
    pfMEtLabel_ = iConfig.getParameter<edm::InputTag>("pfMEtLabel");
    noPuMEtLabel_ = iConfig.getParameter<edm::InputTag>("noPuMEtLabel");
    MVAMEtLabel_ = iConfig.getParameter<edm::InputTag>("MVAMEtLabel");
    genMEtTrueLabel_ = iConfig.getParameter<edm::InputTag>("genMEtTrueLabel");
    genMEtCaloLabel_ = iConfig.getParameter<edm::InputTag>("genMEtCaloLabel");
    genMEtCaloAndNonPromptLabel_ = iConfig.getParameter<edm::InputTag>("genMEtCaloAndNonPromptLabel");    
    jetLabel_ = iConfig.getParameter<edm::InputTag>("jetLabel");
    PUJetIdDisc = iConfig.getParameter<edm::InputTag>("PUJetDiscriminant");
    PUJetId = iConfig.getParameter<edm::InputTag>("PUJetId");
    JetPtMin = iConfig.getParameter<double>("JetPtMin");
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
    tree = fs->make<TTree>("tree", "Tree for TT Semileptonic");

    EventData.vtx_isFake = new std::vector<int>;
    EventData.vtx_ndof = new std::vector<int>;
    EventData.vtx_z = new std::vector<double>;
    EventData.vtx_Rho = new std::vector<double>;

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

    //Z = new std::vector<Ky::ZCandidate>();
    lepton1 = new std::vector<Ky::Lepton>();
    lepton2 = new std::vector<Ky::Lepton>();
    pfMet = new std::vector<Ky::METCandidate>();
//    NoPU_pfMet = new std::vector<Ky::METCandidate>();
//    MVA_pfMet = new std::vector<Ky::METCandidate>();
//    genMEtTrue_pfMet = new std::vector<Ky::METCandidate>();
//    genMEtCalo_pfMet = new std::vector<Ky::METCandidate>();
//    genMEtCaloAndNonPrompt_pfMet = new std::vector<Ky::METCandidate>();
    //WLeptNeuCand_v = new std::vector<Ky::WLeptNeuCand>();
    //W_invm = new std::vector<double>;
    met = new std::vector<math::XYZTLorentzVector>();
//    NoPU_met = new std::vector<math::XYZTLorentzVector>();
//    MVA_met = new std::vector<math::XYZTLorentzVector>();
//    genMEtTrue_met = new std::vector<math::XYZTLorentzVector>();
//    genMEtCalo_met = new std::vector<math::XYZTLorentzVector>();
//    genMEtCaloAndNonPrompt_met = new std::vector<math::XYZTLorentzVector>();
    jetspt30 = new std::vector<math::XYZTLorentzVector>();
}
void TTsemiLeptAnalyzer::beginJob()
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

  cout<<"EAtarget is : "<<EAtarget<<endl;

}
void TTsemiLeptAnalyzer::beginRun(const edm::Run& iRun, const edm::EventSetup& iSetup)
{
  cout<<"beginRun hahahhaahah========================"<<endl;
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
  return true;
}
void TTsemiLeptAnalyzer::bookTree()
{
  EventData.Register(tree);
  for(unsigned int i(0); i<HLTTriggers.size(); i++)
  {
    HLTData.TrigNames[i]=HLTTriggers[i];
    HLTData.Register(tree,i);
  }
  MEt.Register(tree);
  TT.Register(tree);
}
bool TTsemiLeptAnalyzer::L1TriggerSelection( const edm::Event& iEvent, const edm::EventSetup& iSetup )
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
void TTsemiLeptAnalyzer::GetHLTResults(const edm::Event &iEvent, const edm::EventSetup& iSetup)
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
void TTsemiLeptAnalyzer::clear()
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
  

  EventData.vtx_isFake->clear();
  EventData.vtx_ndof->clear();
  EventData.vtx_z->clear();
  EventData.vtx_Rho->clear();


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
bool TTsemiLeptAnalyzer::endLuminosityBlock(edm::LuminosityBlock & lumi, const edm::EventSetup & setup)
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
bool TTsemiLeptAnalyzer::checkOverlap(const double & eta, const double & phi, const double & dRval1,const double & reliso1, const double &dRval2, const double & reliso2)
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

bool TTsemiLeptAnalyzer::MatchObjects( const reco::Candidate::LorentzVector& pasObj,
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
void TTsemiLeptAnalyzer::LoopMuon(const edm::Event &iEvent, const edm::EventSetup& iSetup)
{
    EvtPass = false;
    //cout<<"lepton size: "<<mu_hand->size()<<endl;
    reco::isodeposit::AbsVetos vetos_ch;
    reco::isodeposit::AbsVetos vetos_nh;
    reco::isodeposit::AbsVetos vetos_ph;
    reco::isodeposit::AbsVetos vetos_pc;
    vetos_nh.push_back(new ThresholdVeto( 0.5 ));
    vetos_ph.push_back(new ThresholdVeto( 0.5 ));

    bool goodVtx=false;

    // Jet study =====================
    nIdJets = 0;
    for(i_jet = Jets->begin(); i_jet != Jets->end(); ++i_jet)
    {
      if( i_jet->pt() < JetPtMin) continue;
      if( i_jet->eta() > 2.5) continue;
      bool pIsClean(true);
      for(unsigned i(0); i< mu_hand->size(); i++)
      {
	pat::Muon it1 = mu_hand->at(i);
        it1.setP4(it1.pfCandidateRef()->p4());
	if(it1.pt() < 5.) continue;
	if(deltaR(i_jet->eta(), i_jet->phi(), it1.eta(), it1.phi() ) <0.5) pIsClean = false;
      }
      if(!pIsClean) continue;
      double jecFactor = 1.0;
      double chf = 0.0;
      double nhf = 0.0;
      double pef = 0.0;
      double eef = 0.0;
      double mef = 0;

      edm::Ptr<reco::Jet> ptrToJet = Jets->ptrAt( i_jet - Jets->begin() );
      if( ptrToJet.isNonnull() && ptrToJet.isAvailable() )
      {
	reco::PFJet const * pfJet = dynamic_cast<reco::PFJet const *>(ptrToJet.get() );
	if( pfJet != 0){
	  chf = pfJet->chargedHadronEnergyFraction();
	  nhf = pfJet->neutralHadronEnergyFraction();
	  pef = pfJet->photonEnergyFraction();
	  eef = pfJet->electronEnergy() / pfJet->energy();
	  mef = pfJet->muonEnergyFraction();
	  //if ( useJecLevels ) jecFactor = pfJet->jecFactor( jecLevels );
	}
      }
      bool passPU = true;
      float JetMva = 0;
      int JetIdFlag = 0;
      if( PUJetIdDisc.label().size() != 0 && PUJetId.label().size() != 0 )
      {
	JetMva    = (*PUJetIdMVA) [ptrToJet];
	JetIdFlag = (*PUJetIdFlag)[ptrToJet];
	if(! PileupJetIdentifier::passJetId( JetIdFlag, PileupJetIdentifier::kLoose ) ) passPU = false;
	//cout<<"passPU: "<<passPU<<endl;
      }
      if(!passPU) continue;
      //cout<<"Jet pt: "<<i_jet->pt()<<endl;
      ///// Count the jets in the event /////////////
      nIdJets ++;
    }
    TT.nIdJets = nIdJets;

    // Electron study===============
    if(nIdJets >= 4)for(unsigned i = 0; i < mu_hand->size(); i++)
    {
      EvtPass = true;
      pat::Muon it1 = mu_hand->at(i);
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
      goodVtx=false;
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
      //W recon
      ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > lept_;
      lept_.SetPxPyPzE(lep1.px(), lep1.py(), lep1.pz(), lep1.energy());
      //const Ky::WLeptNeuCand WLeptNeuCand_(lept_, *pfMEt4V,lep1.charge());
      //const Ky::WLeptNeuCand WLeptNeuCand_(lept_, met->at(0),lep1.charge());


      Lept1_chIso03 = it1.isoDeposit(pat::PfChargedHadronIso)->depositAndCountWithin(0.3, vetos_ch).first;
      Lept1_chIso04 = it1.isoDeposit(pat::PfChargedHadronIso)->depositAndCountWithin(0.4, vetos_ch).first;
      Lept1_nhIso03 = it1.isoDeposit(pat::PfNeutralHadronIso)->depositAndCountWithin(0.3, vetos_nh).first;
      Lept1_nhIso04 = it1.isoDeposit(pat::PfNeutralHadronIso)->depositAndCountWithin(0.4, vetos_nh).first;
      Lept1_phIso03 = it1.isoDeposit(pat::PfGammaIso)->depositAndCountWithin(0.3, vetos_ph).first;
      Lept1_phIso04 = it1.isoDeposit(pat::PfGammaIso)->depositAndCountWithin(0.4, vetos_ph).first;
      Lept1_pcIso03 = it1.isoDeposit(pat::PfPUChargedHadronIso)->depositAndCountWithin(0.3, vetos_pc).first;
      Lept1_pcIso04 = it1.isoDeposit(pat::PfPUChargedHadronIso)->depositAndCountWithin(0.4, vetos_pc).first;

      //if(Lept1_pcIso04_tmp != Lept1_pcIso04) cout<<"TTsemiLeptAnalyzer: pcIso04 is not the same"<<endl;

      Lept1_relIsoCom03 = (Lept1_chIso03 + Lept1_nhIso03 + Lept1_phIso03)/Lept1_pt;
      Lept1_relIsoCom04 = (Lept1_chIso04 + Lept1_nhIso04 + Lept1_phIso04)/Lept1_pt;
      Lept1_relIsoBeta03 = (Lept1_chIso03+
	  max(0.0, Lept1_nhIso03 + Lept1_phIso03 - 0.5*Lept1_pcIso03))
	  /Lept1_pt;
      Lept1_relIsoBeta04 = (Lept1_chIso04+
	  max(0.0, Lept1_nhIso04 + Lept1_phIso04 - 0.5*Lept1_pcIso04))
	  /Lept1_pt;

      //Fill tree
      TT.Lept1_genIdxMatch->push_back(idxMatch);
      TT.Lept1_genDeltaR->push_back(BestGenDeltaR1);
      TT.Lept1_genDPtRel->push_back(BesTdPtRel1);
      TT.Lept1_chIso03->push_back(Lept1_chIso03);
      TT.Lept1_chIso04->push_back(Lept1_chIso04);
      TT.Lept1_nhIso03->push_back(Lept1_nhIso03);
      TT.Lept1_nhIso04->push_back(Lept1_nhIso04);
      TT.Lept1_phIso03->push_back(Lept1_phIso03);
      TT.Lept1_phIso04->push_back(Lept1_phIso04);
      TT.Lept1_pcIso03->push_back(Lept1_pcIso03);
      TT.Lept1_pcIso04->push_back(Lept1_pcIso04);
      TT.Lept1_relIsoCom03->push_back(Lept1_relIsoCom03);
      TT.Lept1_relIsoCom04->push_back(Lept1_relIsoCom04);
      TT.Lept1_relIsoBeta03->push_back(Lept1_relIsoBeta03);
      TT.Lept1_relIsoBeta04->push_back(Lept1_relIsoBeta04);
      TT.Lept1_isGlobal->push_back(Lept1_isGlobal);
      TT.Lept1_isTrker->push_back(Lept1_isTrker);
      TT.Lept1_pt->push_back(Lept1_pt);
      TT.Lept1_et->push_back(Lept1_et);
      TT.Lept1_charge->push_back(Lept1_charge);
      TT.Lept1_eta->push_back(Lept1_eta);
      TT.Lept1_phi->push_back(Lept1_phi);
      TT.Lept1_px->push_back(Lept1_px);
      TT.Lept1_py->push_back(Lept1_py);
      TT.Lept1_pz->push_back(Lept1_pz);
      TT.Lept1_en->push_back(Lept1_en);
      TT.Lept1_matchStations->push_back(Lept1_matchStations);
      TT.Lept1_dB->push_back(Lept1_dB);

      TT.Lept1_dz->push_back(Lept1_dz);
      TT.Lept1_globalNormChi2->push_back(Lept1_globalNormChi2);
      TT.Lept1_muonHits->push_back(Lept1_muonHits);
      TT.Lept1_trkLayers->push_back(Lept1_trkLayers);
      TT.Lept1_trackerHits->push_back(Lept1_trackerHits);
      TT.Lept1_pixelHits->push_back(Lept1_pixelHits);

      TT.Lept1_pixelHits->push_back(Lept1_pixelHits);

    }//mu_hand
}
void TTsemiLeptAnalyzer::LoopElectron(const edm::Event &iEvent, const edm::EventSetup& iSetup)
{
    EvtPass = false;

    bool goodVtx=false;

    // Jet study =====================
    nIdJets = 0;
    for(i_jet = Jets->begin(); i_jet != Jets->end(); ++i_jet)
    {
      if( i_jet->pt() < JetPtMin) continue;
      if( i_jet->eta() > 2.5) continue;
      bool pIsClean(true);
      for(unsigned i(0); i< mu_hand->size(); i++)
      {
	pat::Muon it1 = mu_hand->at(i);
        it1.setP4(it1.pfCandidateRef()->p4());
	if(it1.pt() < 5.) continue;
	if(deltaR(i_jet->eta(), i_jet->phi(), it1.eta(), it1.phi() ) <0.5) pIsClean = false;
      }
      if(!pIsClean) continue;
      double jecFactor = 1.0;
      double chf = 0.0;
      double nhf = 0.0;
      double pef = 0.0;
      double eef = 0.0;
      double mef = 0;

      edm::Ptr<reco::Jet> ptrToJet = Jets->ptrAt( i_jet - Jets->begin() );
      if( ptrToJet.isNonnull() && ptrToJet.isAvailable() )
      {
	reco::PFJet const * pfJet = dynamic_cast<reco::PFJet const *>(ptrToJet.get() );
	if( pfJet != 0){
	  chf = pfJet->chargedHadronEnergyFraction();
	  nhf = pfJet->neutralHadronEnergyFraction();
	  pef = pfJet->photonEnergyFraction();
	  eef = pfJet->electronEnergy() / pfJet->energy();
	  mef = pfJet->muonEnergyFraction();
	  //if ( useJecLevels ) jecFactor = pfJet->jecFactor( jecLevels );
	}
      }
      bool passPU = true;
      float JetMva = 0;
      int JetIdFlag = 0;
      if( PUJetIdDisc.label().size() != 0 && PUJetId.label().size() != 0 )
      {
	JetMva    = (*PUJetIdMVA) [ptrToJet];
	JetIdFlag = (*PUJetIdFlag)[ptrToJet];
	if(! PileupJetIdentifier::passJetId( JetIdFlag, PileupJetIdentifier::kLoose ) ) passPU = false;
	//cout<<"passPU: "<<passPU<<endl;
      }
      if(!passPU) continue;
      //cout<<"Jet pt: "<<i_jet->pt()<<endl;
      ///// Count the jets in the event /////////////
      nIdJets ++;
    }
    TT.nIdJets = nIdJets;

    if( nIdJets >= 4)for(unsigned i = 0; i < ele_hand->size(); i++)
    {
      EvtPass = true;
      pat::Electron it1 = ele_hand->at(i);
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

      //Fill W vectors
      TT.Lept1_genIdxMatch->push_back(idxMatch);
      TT.Lept1_genDeltaR->push_back(genDeltaR1);
      TT.Lept1_genDPtRel->push_back(dPtRel1);
      TT.Lept1_pt->push_back(Lept1_pt);
      TT.Lept1_et->push_back(Lept1_et);
      TT.Lept1_charge->push_back(Lept1_charge);
      TT.Lept1_eta->push_back(Lept1_eta);
      TT.Lept1_phi->push_back(Lept1_phi);
      TT.Lept1_px->push_back(Lept1_px);
      TT.Lept1_py->push_back(Lept1_py);
      TT.Lept1_pz->push_back(Lept1_pz);
      TT.Lept1_en->push_back(Lept1_en);
      TT.Lept1_etaSC->push_back(Lept1_etaSC);
      TT.Lept1_phiSC->push_back(Lept1_phiSC);
      TT.Lept1_dEtaIn->push_back(Lept1_dEtaIn);
      TT.Lept1_dPhiIn->push_back(Lept1_dPhiIn);
      TT.Lept1_sigmaIEtaIEta->push_back(Lept1_sigmaIEtaIEta);
      TT.Lept1_HoverE->push_back(Lept1_HoverE);
      TT.Lept1_fbrem->push_back(Lept1_fbrem);
      TT.Lept1_energyEC->push_back(Lept1_energyEC);
      TT.Lept1_Pnorm->push_back(Lept1_Pnorm);
      TT.Lept1_InvEminusInvP->push_back(Lept1_InvEminusInvP);
      TT.Lept1_dxy->push_back(Lept1_dxy);
      TT.Lept1_dz->push_back(Lept1_dz);
      TT.Lept1_AEff03->push_back(Lept1_AEff03);
      TT.Lept1_chIso03->push_back(Lept1_chIso03);
      TT.Lept1_chIso04->push_back(Lept1_chIso04);
      TT.Lept1_nhIso03->push_back(Lept1_nhIso03);
      TT.Lept1_nhIso04->push_back(Lept1_nhIso04);
      TT.Lept1_phIso03->push_back(Lept1_phIso03);
      TT.Lept1_phIso04->push_back(Lept1_phIso04);
      TT.Lept1_pcIso03->push_back(Lept1_pcIso03);
      TT.Lept1_pcIso04->push_back(Lept1_pcIso04);
      TT.Lept1_relIsoCom03->push_back(Lept1_relIsoCom03);
      TT.Lept1_relIsoCom04->push_back(Lept1_relIsoCom04);
      TT.Lept1_relIsoBeta03->push_back(Lept1_relIsoBeta03);
      TT.Lept1_relIsoBeta04->push_back(Lept1_relIsoBeta04);
      TT.Lept1_relIsoRho03->push_back(Lept1_relIsoRho03);
      TT.Lept1_hasConversion->push_back(Lept1_hasConversion);
      TT.Lept1_mHits->push_back(Lept1_mHits);
      TT.Lept1_SCcharge->push_back(Lept1_SCcharge);
      TT.Lept1_TKcharge->push_back(Lept1_TKcharge);
      TT.Lept1_GSFcharge->push_back(Lept1_GSFcharge);
      TT.Lept1_GsfCtfScPixchargeConsistentcheck->push_back(Lept1_GsfCtfScPixchargeConsistentcheck);

      TT.Lept1_RelisolPtTrks03->push_back(Lept1_RelisolPtTrks03);
      TT.Lept1_RelisoEm03     ->push_back(Lept1_RelisoEm03);
      TT.Lept1_RelisoHad03    ->push_back(Lept1_RelisoHad03);

    }//ele_hand
}
void TTsemiLeptAnalyzer::endJob()
{
}
void TTsemiLeptAnalyzer::endRun(edm::Run const&, edm::EventSetup const&)
{
}
void TTsemiLeptAnalyzer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
void TTsemiLeptAnalyzer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
