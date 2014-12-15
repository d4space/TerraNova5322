#include "FWCore/Framework/interface/MakerMacros.h"
#include "TerraNova5322/NtupleMaker/interface/wAcceptAnalyzer.h"

  //virtual void produce(const edm::Event& iEvent, const edm::EventSetup& iSetup)
bool wAcceptAnalyzer::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  //cout<<"Channel: "<<Channel<<"#########################################"<<endl;

  EvtPass = false;

  clear();

  EventData.EVENT  = iEvent.id().event();
  EventData.RUN    = iEvent.id().run();
  EventData.LUMI   = iEvent.id().luminosityBlock();
  isRD = iEvent.isRealData();
  //const bool isRD = iEvent.isRealData();

  if(! isRD)
  {
    GetGenInfoW(iEvent, iSetup);
    GetGenInfoZ(iEvent, iSetup);
    GetFSRInfoW(iEvent, iSetup);
  }


    //ESHandle<SetupData> pSetup;
    //iSetup.get<SetupRecord>().get(pSetup);
    if( EvtPass) tree->Fill();

    return EvtPass;

}
DEFINE_FWK_MODULE(wAcceptAnalyzer);

