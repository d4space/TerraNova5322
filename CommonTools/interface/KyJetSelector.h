#ifndef TerraNova_CommonTools_KyJetSelector_h
#define TerraNova_CommonTools_KyJetSelector_h

// store the position of the Z combinaison the closest to the Z mass

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Jet.h"//VertexCollection
//#include "DataFormats/PatCandidates/interface/LookupTableRecord.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "TerraNova/CommonTools/interface/JetIDSelector.h"
//#include "PFAnalyses/CommonTools/interface/PatJetSelector.h"
//#include "PFAnalyses/CommonTools/interface/PatLeptonSelector.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositDirection.h"
#include "DataFormats/RecoCandidate/interface/IsoDeposit.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositVetos.h"
#include "DataFormats/PatCandidates/interface/Isolation.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"

#include "RecoEgamma/EgammaTools/interface/ConversionTools.h"

#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"

//PUJetID
#include "DataFormats/JetReco/interface/PileupJetIdentifier.h"

class KyJetSelector : public edm::EDProducer
{
 public:

  explicit KyJetSelector(const edm::ParameterSet&);
  ~KyJetSelector();

  void beginJob();
  void produce(edm::Event&, const edm::EventSetup&);
  void endJob();

  //PUJetIDAnalysis
  bool EvtPass;
  int nIdJets;
  edm::View<reco::PFJet>::const_iterator i_jet;
  edm::InputTag PUJetIdDisc;
  edm::InputTag PUJetId;
  edm::Handle<edm::ValueMap<float> > PUJetIdMVA;
  edm::Handle<edm::ValueMap<int> >   PUJetIdFlag;

 // virtual std::vector <reco::PFCandidatePtr> getPFConstituents () const;

 private:

  edm::InputTag jetLabel_;
  //typedef pat::JetCollection::const_iterator MI;
  //edm::Handle<pat::JetCollection> jets_;//PAT Jet
  edm::Handle<edm::View<reco::PFJet> > jets_;
  unsigned int EVENT;
  unsigned int RUN;
  unsigned int LUMI;

  std::vector<double>* eta;
  std::vector<double>* pt;

  double pt_;
  double eta_;

};
#endif

