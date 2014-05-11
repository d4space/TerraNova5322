#ifndef TerraNova_CommonTools_KyPhotonSelector_h
#define TerraNova_CommonTools_KyPhotonSelector_h

// store the position of the Z combinaison the closest to the Z mass

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/PatCandidates/interface/Jet.h"//VertexCollection
//#include "DataFormats/PatCandidates/interface/LookupTableRecord.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "TerraNova/CommonTools/interface/PhotonIDSelector.h"
//#include "PFAnalyses/CommonTools/interface/PatPhotonSelector.h"
//#include "PFAnalyses/CommonTools/interface/PatLeptonSelector.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositDirection.h"
#include "DataFormats/RecoCandidate/interface/IsoDeposit.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositVetos.h"
#include "DataFormats/PatCandidates/interface/Isolation.h"

//EGamma
//#include "EgammaAnalysis/PhotonTools/interface/PhotonEffectiveArea.h"
//#include "EgammaAnalysis/PhotonTools/interface/PhotonEffectiveArea.h"

#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"

class KyPhotonSelector : public edm::EDProducer
{
 public:

  explicit KyPhotonSelector(const edm::ParameterSet&);
  ~KyPhotonSelector();

  void beginJob();
  void produce(edm::Event&, const edm::EventSetup&);
  void endJob();

 private:

  // Cut version
  vector<std::string> cut_;
  edm::InputTag photonLabel_;
  
  typedef pat::PhotonCollection::const_iterator MI;
  //edm::Handle<pat::PhotonCollection> photons_;
  edm::Handle<edm::View<reco::Photon> > photons_;
  //edm::Handle<reco::VertexCollection> recVtxs_;

  //add run event data
  unsigned int EVENT;
  unsigned int RUN;
  unsigned int LUMI;

  std::vector<double>* eta;
  std::vector<double>* superEta;
  std::vector<double>* phi;
  std::vector<double>* pt;
  std::vector<double>* dEtaIn;
  std::vector<double>* dPhiIn;
  std::vector<double>* sigmaIEtaIEta;
  std::vector<double>* HoverE;
  std::vector<double>* fbrem;
  std::vector<double>* InvEminusInvP;


  int multiplicity;



  double pt_;
  double eta_;
  double phi_;
  double super_eta_;
  double super_phi_;
  double dEtaIn_;
  double dPhiIn_;
  double sigmaIEtaIEta_;
  double HoverE_;
  double fbrem_;
  double energy_;
  double Pnorm_;
  double InvEminusInvP_;
  bool isEE, isEB;

};


#endif

