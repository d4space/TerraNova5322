// $Id: RemoveDuplicate.cc,v 1.1.1.1 2013/07/06 15:36:58 sangilpark Exp $
//
//
// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "TerraNova5322/DataFormats/interface/Event.h"

#include <set>
//
// class declaration
//
using namespace edm;
using namespace std;

class RemoveDuplicate : public edm::EDFilter
{
  public:
    explicit RemoveDuplicate(const edm::ParameterSet&);
    ~RemoveDuplicate() {};

  private:
    virtual void beginJob() {};
    virtual bool filter(edm::Event&, const edm::EventSetup&);
    virtual void endJob() {};

    // ----------member data ---------------------------
    bool applyFilter_;

    std::set<edm::EventID> eventSet_;
};

RemoveDuplicate::RemoveDuplicate(const edm::ParameterSet& ps)
{
  applyFilter_ = ps.getUntrackedParameter<bool>("applyFilter", true);
}

bool RemoveDuplicate::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  if ( !applyFilter_ ) return true;

  if ( eventSet_.find(iEvent.id()) == eventSet_.end() )
  {
    eventSet_.insert(iEvent.id());
    return true;
  }

  return false;
}

DEFINE_FWK_MODULE(RemoveDuplicate);

