#include "TerraNova/CommonTools/interface/KyPhotonSelector.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Common/interface/View.h"
#include "DataFormats/Common/interface/Ptr.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"
#include "MagneticField/Engine/interface/MagneticField.h"

using namespace std;

KyPhotonSelector::KyPhotonSelector(const edm::ParameterSet& cfg)
{
  cut_ = cfg.getParameter<std::vector<string> >("cut");
  photonLabel_ = cfg.getParameter<edm::InputTag>("photonLabel");

  //produces<std::vector<pat::Photon> >("");
  produces<std::vector<reco::Photon> >("");
}

KyPhotonSelector::~KyPhotonSelector()
{

}

void KyPhotonSelector::produce(edm::Event& iEvent, const edm::EventSetup& es)
{
  using namespace reco;
  using namespace isodeposit;

  iEvent.getByLabel(photonLabel_, photons_);


  //std::auto_ptr<std::vector<pat::Photon> > pos(new std::vector<pat::Photon>());
  std::auto_ptr<std::vector<reco::Photon> > pos(new std::vector<reco::Photon>());

  for (unsigned int i=0; i < photons_->size();++i){
    //pat::Photon photon = photons_->at(i);
    reco::Photon photon = photons_->at(i);

    pt_ = photon.pt();
    eta_ = photon.eta();
    phi_ = photon.phi();

    IsoDeposit::AbsVetos vetos_ch;
    IsoDeposit::AbsVetos vetos_nh;
    IsoDeposit::AbsVetos vetos_ph;

    bool passed = false;

    if( pt_ < 30 ) passed = false;

    if ( passed ) pos->push_back((*photons_)[i]);

  }

  multiplicity = (int) pos->size();

  iEvent.put(pos);

}

void 
KyPhotonSelector::beginJob(){
}

void
KyPhotonSelector::endJob() {
}

#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_FWK_MODULE(KyPhotonSelector);



