#include "DataFormats/Common/interface/Wrapper.h"

#include "TerraNova5322/DataFormats/interface/ZCandidate.h"
#include "TerraNova5322/DataFormats/interface/Lepton.h"
#include "TerraNova5322/DataFormats/interface/METCandidate.h"
//#include "TerraNova5322/DataFormats/interface/TTbarEvent.h"
//#include "TerraNova5322/DataFormats/interface/TTbarGenEvent.h"
//#include "TerraNova5322/DataFormats/interface/TTbarMass.h"
#include "TerraNova5322/DataFormats/interface/WLeptNeuCand.h"

#include <vector>

namespace {
  struct Ky_DataFormats {

    Ky::WLeptNeuCand dummyWLeptNeuCand;
    edm::Wrapper<Ky::WLeptNeuCand> dummyWLeptNeuCandWrapper;
    std::vector<Ky::WLeptNeuCand> dummyWLeptNeuCandCollection;
    edm::Wrapper<std::vector<Ky::WLeptNeuCand> > dummyWLeptNeuCandCollectionWrapper;
    edm::Ptr<Ky::WLeptNeuCand> dummyWLeptNeuCandPtr;

    Ky::ZCandidate dummyZCandidate;
    edm::Wrapper<Ky::ZCandidate> dummyZCandidateWrapper;
    std::vector<Ky::ZCandidate> dummyZCandidateCollection;
    edm::Wrapper<std::vector<Ky::ZCandidate> > dummyZCandidateCollectionWrapper;
    edm::Ptr<Ky::ZCandidate> dummyZCandidatePtr;

    Ky::Lepton dummyLepton;
    edm::Wrapper<Ky::Lepton> dummyLeptonWrapper;
    std::vector<Ky::Lepton> dummyLeptonCollection;
    edm::Wrapper<std::vector<Ky::Lepton> > dummyLeptonCollectionWrapper;
    edm::Ptr<Ky::Lepton> dummyLeptonPtr;

    Ky::METCandidate dummyMETCandidate;
    edm::Wrapper<Ky::METCandidate> dummyMETCandidateWrapper;
    std::vector<Ky::METCandidate> dummyMETCandidateCollection;
    edm::Wrapper<std::vector<Ky::METCandidate> > dummyMETCandidateCollectionWrapper;
    edm::Ptr<Ky::METCandidate> dummyMETCandidatePtr;

    //Ky::TTbarEvent dummyTTbarEvent;
    //edm::Wrapper<Ky::TTbarEvent> dummyTTbarEventWrapper;
    //std::vector<Ky::TTbarEvent> dummyTTbarEventCollection;
    //edm::Wrapper<std::vector<Ky::TTbarEvent> > dummyTTbarEventCollectionWrapper;
    //edm::Ptr<Ky::TTbarEvent> dummyTTbarEventPtr;

    //Ky::TTbarGenEvent dummyTTbarGenEvent;
    //edm::Wrapper<Ky::TTbarGenEvent> dummyTTbarGenEventWrapper;
    //std::vector<Ky::TTbarGenEvent> dummyTTbarGenEventCollection;
    //edm::Wrapper<std::vector<Ky::TTbarGenEvent> > dummyTTbarGenEventCollectionWrapper;
    //edm::Ptr<Ky::TTbarGenEvent> dummyTTbarGenEventPtr;

    //Ky::TTbarMass dummyTTbarMass;
    //edm::Wrapper<Ky::TTbarMass> dummyTTbarMassWrapper;
    //std::vector<Ky::TTbarMass> dummyTTbarMassCollection;
    //edm::Wrapper<std::vector<Ky::TTbarMass> > dummyTTbarMassCollectionWrapper;
    //edm::Ptr<Ky::TTbarMass> dummyTTbarMassPtr;

  };

}
