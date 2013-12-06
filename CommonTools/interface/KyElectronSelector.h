#ifndef KoSMP_CommonTools_KyElectronSelector_h
#define KoSMP_CommonTools_KyElectronSelector_h

// store the position of the Z combinaison the closest to the Z mass

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Jet.h"//VertexCollection
//#include "DataFormats/PatCandidates/interface/LookupTableRecord.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "KoSMP/CommonTools/interface/ElectronIDSelector.h"
//#include "PFAnalyses/CommonTools/interface/PatElectronSelector.h"
//#include "PFAnalyses/CommonTools/interface/PatLeptonSelector.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositDirection.h"
#include "DataFormats/RecoCandidate/interface/IsoDeposit.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositVetos.h"
#include "DataFormats/PatCandidates/interface/Isolation.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"

//EGamma
//#include "EgammaAnalysis/ElectronTools/interface/ElectronEffectiveArea.h"
#include "EGamma/EGammaAnalysisTools/interface/ElectronEffectiveArea.h"
#include "RecoEgamma/EgammaTools/interface/ConversionTools.h"

#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"

class KyElectronSelector : public edm::EDProducer
{
 public:

  explicit KyElectronSelector(const edm::ParameterSet&);
  ~KyElectronSelector();

  void beginJob();
  void produce(edm::Event&, const edm::EventSetup&);
  void endJob();

 private:

  // Cut version
  int version_; // 1 for PFMUON, 2 for VBTF, 3 for TOP , 4 for PFMUON && ISO
  vector<std::string> cut_;
  bool usepflow_;
  edm::InputTag electronLabel_;
  
  //std::string eidName_;
  //int eidBitMask_;
  ElectronIDSelector eleIdSelector_;
  
  edm::InputTag beamSpotLabel_;
  edm::InputTag vertexLabel_;
  edm::InputTag rhoIsoLabel_;
  edm::InputTag conversionsInputTag_;
 
  typedef pat::ElectronCollection::const_iterator MI;
  edm::Handle<pat::ElectronCollection> electrons_;
  edm::Handle<reco::BeamSpot> beamSpot_;
  edm::Handle<reco::VertexCollection> recVtxs_;
  edm::Handle<double> rhoIso_h;
  edm::Handle<reco::ConversionCollection> conversions_h;
  //TH2F * id2mva; 
  //TH2F * id2pfmva; 
  //TH2F * pfMVA2patMVA_;

  TTree *tree;

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
  std::vector<double>* dxy;
  std::vector<double>* dz;
  std::vector<double>* relIso;
  std::vector<double>* relIsodb;
  std::vector<double>* relIsoRho;
  std::vector<bool>* vtxFitConversion;
  std::vector<double>* mHits;


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
  double dxy_;
  double dz_;
  double rhoIso_;
  double AEff03_;
  bool vtxFitConversion_;
  double mHits_;
  bool isEE, isEB;

};


#endif

