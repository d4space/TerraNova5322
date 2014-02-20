#ifndef Ky_CommonTools_KyMuonSelector_h
#define Ky_CommonTools_KyMuonSelector_h

// store the position of the Z combination the closest to the Z mass

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
//#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "TerraNova/CommonTools/interface/MuonIDSelector.h"
//#include "PFAnalyses/CommonTools/interface/PatMuonSelector.h"
//#include "PFAnalyses/CommonTools/interface/PatLeptonSelector.h"
#include "TerraNova/CommonTools/interface/LeptonIsoSelector.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositDirection.h"
#include "DataFormats/RecoCandidate/interface/IsoDeposit.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositVetos.h"
#include "DataFormats/PatCandidates/interface/Isolation.h"


#include "TFile.h"
#include "TTree.h"
#include "TH1.h"

class KyMuonSelector : public edm::EDProducer
{
 public:

  explicit KyMuonSelector(const edm::ParameterSet&);
  ~KyMuonSelector();

  void beginJob();
  void produce(edm::Event&, const edm::EventSetup&);
  void endJob();

 private:

  // Cut version
  int version_; // 1 for PFMUON, 2 for VBTF, 3 for WMuNu , 4 for PFMUON && ISO
  bool saveTree;
  vector<std::string> cut_;
  vector<std::string> isocut_;
  edm::InputTag muonLabel_;
  //PatMuonSelector   muonIdSelector_;
  MuonIDSelector   muonIdSelector_;
  MuonIsoSelector  muonIsoSelector_;
  edm::InputTag beamSpotLabel_;
 
  typedef pat::MuonCollection::const_iterator MI;
  edm::Handle<pat::MuonCollection> muons_;
  edm::Handle<reco::BeamSpot> beamSpot_;
  TH1F * cutflow;
  vector<std::string> cutNames;

  TTree *tree;

  //add run event data
  unsigned int EVENT;
  unsigned int RUN;
  unsigned int LUMI;

  int multiplicity;
  std::vector<double>* eta;
  std::vector<double>* phi;
  std::vector<double>* pt;
  std::vector<double>* charge;

  std::vector<int>*	isGlobal;
  std::vector<int>*	muonMatchStations;
  std::vector<double>*	dB;
  std::vector<double>*	dz;
  std::vector<double>*	globalNormChi2;
  std::vector<int>*	muonHits;
  std::vector<int>*	trkLayers;
  std::vector<int>*	trackerHits;
  std::vector<int>*	pixelHits;

  std::vector<double>* chIso03;
  std::vector<double>* nhIso03;
  std::vector<double>* phIso03;
  std::vector<double>* pcIso03;

  std::vector<double>* chIso04;
  std::vector<double>* nhIso04;
  std::vector<double>* phIso04;
  std::vector<double>* pcIso04;


  std::vector<double>* trackIso;
  std::vector<double>* ecalIso;
  std::vector<double>* hcalIso;

  double eta_;
  double phi_;
  double pt_;
  double charge_;

  bool	isGlobal_;
  int	muonMatchStations_;
  double	dB_;
  double	dz_;
  double	globalNormChi2_;
  int	muonHits_;
  int	trkLayers_;
  int	trackerHits_;
  int	pixelHits_;

  double chIso03_;
  double nhIso03_;
  double phIso03_;
  double pcIso03_;

  double chIso04_;
  double nhIso04_;
  double phIso04_;
  double pcIso04_;


  double trackIso_;
  double ecalIso_;
  double hcalIso_;

  double reIsoBeta_;
};


#endif

