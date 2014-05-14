#include "TerraNova/CommonTools/interface/KyJetSelector.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Common/interface/View.h"
#include "DataFormats/Common/interface/Ptr.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"
#include "MagneticField/Engine/interface/MagneticField.h"

using namespace std;

KyJetSelector::KyJetSelector(const edm::ParameterSet& cfg)
{
  jetLabel_ = cfg.getParameter<edm::InputTag>("jetLabel");//input jet
  produces<std::vector<reco::PFJet> >("");

  PUJetIdDisc = cfg.getParameter<edm::InputTag>("PUJetDiscriminant");
  PUJetId = cfg.getParameter<edm::InputTag>("PUJetId");
}

KyJetSelector::~KyJetSelector()
{

}

void KyJetSelector::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace reco;
  using namespace isodeposit;

  iEvent.getByLabel(jetLabel_, jets_);

  std::auto_ptr<std::vector<reco::PFJet> > pos(new std::vector<reco::PFJet>());

  if(PUJetIdDisc.label().size() != 0 && PUJetId.label().size() != 0)
   {
     iEvent.getByLabel(PUJetIdDisc, PUJetIdMVA);
     iEvent.getByLabel(PUJetId, PUJetIdFlag);
   }

  EvtPass = false;
  nIdJets = 0;

  for(i_jet = jets_->begin(); i_jet != jets_->end(); ++i_jet)
  {
  if( i_jet->pt() < 30) continue;
  if( i_jet->eta() > 2.5) continue;

  edm::Ptr<reco::PFJet> ptrToJet = jets_->ptrAt( i_jet - jets_->begin() );
  bool passPU = true;
  int JetIdFlag = 0;
  if( PUJetIdDisc.label().size() != 0 && PUJetId.label().size() != 0 )
  {
    JetIdFlag = (*PUJetIdFlag)[ptrToJet];
    if(! PileupJetIdentifier::passJetId( JetIdFlag, PileupJetIdentifier::kLoose ) ) passPU = false;
  }
  if(!passPU) continue;
  nIdJets ++;
  pos->push_back((*jets_)[i_jet - jets_->begin()]);
  }
  EvtPass = true;


  if(EvtPass)
  {
    iEvent.put(pos);
  }
}

void 
KyJetSelector::beginJob(){
}

void
KyJetSelector::endJob() {
}

#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_FWK_MODULE(KyJetSelector);



