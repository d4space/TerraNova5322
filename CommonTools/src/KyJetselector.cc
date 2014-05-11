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
  cut_ = cfg.getParameter<std::vector<string> >("cut");
  jetLabel_ = cfg.getParameter<edm::InputTag>("jetLabel");//input jet
  //produces<std::vector<pat::Jet> >("");//PAT Jet
  produces<std::vector<reco::PFJet> >("");

  //PIJetID
  PUJetIdDisc = cfg.getParameter<edm::InputTag>("PUJetDiscriminant");
  PUJetId = cfg.getParameter<edm::InputTag>("PUJetId");
}

KyJetSelector::~KyJetSelector()
{

}

//void KyJetSelector::produce(edm::Event& iEvent, const edm::EventSetup& es)
void KyJetSelector::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace reco;
  using namespace isodeposit;

  iEvent.getByLabel(jetLabel_, jets_);


  //std::auto_ptr<std::vector<pat::Jet> > pos(new std::vector<pat::Jet>());//PAT Jet
  std::auto_ptr<std::vector<reco::PFJet> > pos(new std::vector<reco::PFJet>());
 

  for (unsigned int i=0; i < jets_->size();++i){
    //pat::Jet jet = jets_->at(i);//PAT Jet
    reco::PFJet jet = jets_->at(i);
    pt_ = jet.pt();
    eta_ = jet.eta();
    phi_ = jet.phi();
 
    IsoDeposit::AbsVetos vetos_ch;
    IsoDeposit::AbsVetos vetos_nh;
    IsoDeposit::AbsVetos vetos_ph;

    bool passed = false;

    if( pt_ < 30 ){ passed = false;}
    else{passed = true;}
    

    if ( passed ) pos->push_back((*jets_)[i]);
  }
 
  multiplicity = (int) pos->size();

  // PU Jet ID ======
  if(PUJetIdDisc.label().size() != 0 && PUJetId.label().size() != 0)
  {
    iEvent.getByLabel(PUJetIdDisc, PUJetIdMVA);
    iEvent.getByLabel(PUJetId, PUJetIdFlag);
  }

  LoopJets(iEvent, iSetup); 

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



