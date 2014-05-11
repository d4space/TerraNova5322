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
  void LoopJets    (const edm::Event &iEvent, const edm::EventSetup& iSetup);
  bool EvtPass;
  int nIdJets;
  double JetPtMin;
  edm::View<reco::PFJet>::const_iterator i_jet;
  edm::InputTag PUJetIdDisc;
  edm::InputTag PUJetId;
  edm::Handle<edm::ValueMap<float> > PUJetIdMVA;
  edm::Handle<edm::ValueMap<int> >   PUJetIdFlag;

 // virtual std::vector <reco::PFCandidatePtr> getPFConstituents () const;

 private:

  vector<std::string> cut_;
  edm::InputTag jetLabel_;
  //typedef pat::JetCollection::const_iterator MI;
  //edm::Handle<pat::JetCollection> jets_;//PAT Jet
  edm::Handle<edm::View<reco::PFJet> > jets_;
  unsigned int EVENT;
  unsigned int RUN;
  unsigned int LUMI;

  std::vector<double>* eta;
  std::vector<double>* phi;
  std::vector<double>* pt;
  std::vector<double>* dxy;
  std::vector<double>* dz;
  std::vector<double>* mHits;


  int multiplicity;



  double pt_;
  double eta_;
  double phi_;
  double dxy_;
  double dz_;
  double mHits_;
  bool isEE, isEB;

};

//PUJetID
void KyJetSelector::LoopJets(const edm::Event &iEvent, const edm::EventSetup& iSetup)
{
    EvtPass = false;
    //bool goodVtx=false;
  
    nIdJets = 0;
    for(i_jet = jets_->begin(); i_jet != jets_->end(); ++i_jet)
    {
      if( i_jet->pt() < JetPtMin) continue;
      if( i_jet->eta() > 2.5) continue;
     /* double jecFactor = 1.0;
      double chf = 0.0;
      double nhf = 0.0;
      double pef = 0.0;
      double eef = 0.0;
      double mef = 0;*/

      edm::Ptr<reco::PFJet> ptrToJet = jets_->ptrAt( i_jet - jets_->begin() );
      /*if( ptrToJet.isNonnull() && ptrToJet.isAvailable() )
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
      }*/
      bool passPU = true;
      //float JetMva = 0;
      int JetIdFlag = 0;
      if( PUJetIdDisc.label().size() != 0 && PUJetId.label().size() != 0 )
      {
	//JetMva    = (*PUJetIdMVA) [ptrToJet];
	JetIdFlag = (*PUJetIdFlag)[ptrToJet];
	if(! PileupJetIdentifier::passJetId( JetIdFlag, PileupJetIdentifier::kLoose ) ) passPU = false;
	cout<<"passPU: "<<passPU<<endl;
      }
      if(!passPU) continue;
        cout<<"Jet pt: "<<i_jet->pt()<<endl;
      nIdJets ++;
    } 
    if(nIdJets >= 6) EvtPass = true;
}

#endif

