#include "KNUPhy/CommonTools/interface/KyMuonSelector.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Common/interface/View.h"
#include "DataFormats/Common/interface/Ptr.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
//#include "DataFormats/BeamSpot/interface/BeamSpot.h"
//#include "DataFormats/Candidate/interface/VertexCompositeCandidate.h"
//#include "DataFormats/Candidate/interface/VertexCompositeCandidateFwd.h"
//#include "DataFormats/Candidate/interface/CompositeCandidate.h"
//#include "DataFormats/Candidate/interface/Candidate.h"

// #include "TauAnalysis/CandidateTools/interface/FetchCollection.h"
using namespace std;

KyMuonSelector::KyMuonSelector(const edm::ParameterSet& cfg)
{
  version_ = cfg.getUntrackedParameter<int>("version", -1);
  cut_ = cfg.getParameter< std::vector<string> >("cut");
  isocut_ = cfg.getParameter< std::vector<string> >("isocut");
  muonLabel_ = cfg.getParameter<edm::InputTag>("muonLabel");
  muonIdSelector_.initialize( cfg.getParameter<edm::ParameterSet>("muonIdSelector") );
  muonIsoSelector_.initialize( cfg.getParameter<edm::ParameterSet>("muonIsoSelector") );
  beamSpotLabel_ = cfg.getParameter<edm::InputTag>("beamSpotLabel");
  saveTree = cfg.getUntrackedParameter<bool>("saveTree", true);

  produces<std::vector<pat::Muon> >("");
  tree = 0;
  if( saveTree)
  {
    edm::Service<TFileService> fs;
    tree = fs->make<TTree>("tree", "Tree for muon study");
    //int nBins = (int) cutNames.size();
    //cutflow   = fs->make<TH1F>( "cutflow", "cutflow", nBins,-0.5,nBins-0.5);
    pt = new std::vector<double>();
    eta = new std::vector<double>();
    phi = new std::vector<double>();
    charge = new std::vector<double>();

    isGlobal = new std::vector<int>();
    muonMatchStations = new std::vector<int>();
    dB = new std::vector<double>();
    dz = new std::vector<double>();
    globalNormChi2 = new std::vector<double>();
    muonHits = new std::vector<int>();
    trkLayers = new std::vector<int>();
    trackerHits = new std::vector<int>();
    pixelHits = new std::vector<int>();

    chIso03 = new std::vector<double>();
    nhIso03 = new std::vector<double>();
    phIso03 = new std::vector<double>();
    pcIso03 = new std::vector<double>();
    chIso04 = new std::vector<double>();
    nhIso04 = new std::vector<double>();
    phIso04 = new std::vector<double>();
    pcIso04 = new std::vector<double>();

    trackIso = new std::vector<double>();
    ecalIso = new std::vector<double>();
    hcalIso = new std::vector<double>();
  }
  cutNames.push_back("pre");
  cutNames.push_back("dB");
  cutNames.push_back("isGlobal");
  cutNames.push_back("isTracker");
  cutNames.push_back("trackerHits");
  cutNames.push_back("chi2");
  cutNames.push_back("muonHits");
  cutNames.push_back("WMuNu");

}

KyMuonSelector::~KyMuonSelector()
{

}

void KyMuonSelector::produce(edm::Event& iEvent, const edm::EventSetup& es)
{
  using namespace reco;
  using namespace isodeposit;

  if (tree)
  {
    pt->clear();
    eta->clear();
    phi->clear();
    charge->clear();
    isGlobal->clear();
    muonMatchStations->clear();
    dB->clear();
    dz->clear();
    globalNormChi2->clear();
    muonHits->clear();
    trkLayers->clear();
    trackerHits->clear();
    pixelHits->clear();

    chIso03->clear();
    nhIso03->clear();
    phIso03->clear();
    pcIso03->clear();
    chIso04->clear();
    nhIso04->clear();
    phIso04->clear();
    pcIso04->clear();

    trackIso->clear();
    ecalIso->clear();
    hcalIso->clear();
  }

  IsoDeposit::AbsVetos vetos_ch;
  IsoDeposit::AbsVetos vetos_nh;
  IsoDeposit::AbsVetos vetos_ph;
  IsoDeposit::AbsVetos vetos_pc;
  vetos_nh.push_back(new ThresholdVeto(0.5));
  vetos_ph.push_back(new ThresholdVeto(0.5));


  iEvent.getByLabel(muonLabel_, muons_);
  iEvent.getByLabel(beamSpotLabel_,beamSpot_); 
  EVENT  = iEvent.id().event();
  RUN    = iEvent.id().run();
  LUMI   = iEvent.id().luminosityBlock();

  std::auto_ptr<std::vector<pat::Muon> > pos(new std::vector<pat::Muon>());

  int cut[8];
  for(int i =0 ; i < (int)cutNames.size() ; i++){
    cut[i] = 0;
  }

  //cout<<"KyMuonSelector:muon size: "<<muons_->size()<<endl;
  for (unsigned int i=0; i < muons_->size();++i){
    const pat::Muon muon = muons_->at(i);
    pat::strbitset muonIdSel = muonIdSelector_.getBitTemplate();
    pat::strbitset muonIsoSel = muonIsoSelector_.getBitTemplate();
    muonIdSelector_( muon, beamSpot_, muonIdSel );
    muonIsoSelector_( muon, muonIsoSel );

    bool C1 = muonIdSel.test("eta") && muonIdSel.test("pt");
    bool C2 = C1 && muonIdSel.test("dB");
    bool C3 = C2 && muonIdSel.test("isGlobalMuon");
    bool C4 = C3 && muonIdSel.test("isTrackerMuon");
    bool C5 = C4 && muonIdSel.test("trackerHits");
    bool C6 = C5 && muonIdSel.test("globalNormChi2");
    bool C7 = C6 && muonIdSel.test("muonHits");
    bool C8 = C2 && muonIdSel.test("WMuNu");
  
    if(C1) cut[0]++;
    if(C2) cut[1]++;
    if(C3) cut[2]++;
    if(C4) cut[3]++;
    if(C5) cut[4]++;
    if(C6) cut[5]++;    
    if(C7) cut[6]++;
    if(C8) cut[7]++;

    bool passed = false;
    edm::Handle<reco::VertexCollection> pvHandle;
    iEvent.getByLabel("offlinePrimaryVertices",pvHandle);
   
    if(version_==-1){
      passed = true;
    }
    else if(version_==0){
      bool passId = true;
      bool passIso = true;
      //cout<<"haha cut size: "<<cut_.size()<<cut_[i]<<endl;
      for(size_t i =0 ; i < cut_.size() ; i++){
        passId = muonIdSel.test(cut_[i]);
        if(!passId) break;
      }
      //cout<<"haha isocut size: "<<isocut_.size()<<endl;
      for(size_t i =0 ; i < isocut_.size() ; i++){
        passIso = muonIsoSel.test(isocut_[i]);
        if(!passIso) break;
      }
      passed = passId && passIso;
    }
    else if(version_==1) passed = C1;
    else if(version_==2) passed = C2;
    else if(version_==3) passed = muonIdSel.test("VBTF") && C2;
    else if(version_==4) passed = muonIdSel.test("WMuNu") && C2;
    else if(version_==5) passed = C2 && muonIsoSel.test("pfOptimizedRel");
    else if(version_ == 6 || version_ ==7)
    {
      passed = true;
      pt_	= muon.pt();
      eta_	= muon.eta();
      phi_	= muon.phi();
      charge_	= muon.charge();

      isGlobal_	= muon.isGlobalMuon();
      muonMatchStations_	= muon.numberOfMatchedStations();
      dB_	= muon.dB();
        //const reco::VertexCollection &vertices = *pvHandle.product();
      if(muon.isGlobalMuon() && !(pvHandle->empty()) && !(pvHandle->front().isFake()) )
      {
        const reco::Vertex &vtx = pvHandle->front();
        const reco::TrackRef& muGlobalTrk = muon.globalTrack();
          //if( muGlobalTrk) 
        try{
        dz_	= muGlobalTrk->dz(vtx.position());
        globalNormChi2_	= muGlobalTrk->normalizedChi2();
        muonHits_	= muGlobalTrk->hitPattern().numberOfValidMuonHits();
        trkLayers_	= muon.track()->hitPattern().trackerLayersWithMeasurement();
        trackerHits_	= muGlobalTrk->hitPattern().numberOfValidTrackerHits();
        }
        catch(...){
        dz_	= -9999;
        globalNormChi2_	= -9999;
        muonHits_	= -9999;
        trkLayers_	= -9999;
        trackerHits_	= -9999;
        }
        //if(muon.innerTrack())
        try{
        pixelHits_	= muon.innerTrack()->hitPattern().numberOfValidPixelHits();
        }
        catch(...){
        pixelHits_	= -9999;
        }
      }
      else
      {
        dz_	= -9999;
        globalNormChi2_	= -9999;
        muonHits_	= -9999;
        trkLayers_	= -9999;
        trackerHits_	= -9999;
        pixelHits_	= -9999;
      }

      //chIso->push_back(muon.chargedHadronIso());
      //phIso->push_back(muon.photonIso());
      //nhIso->push_back(muon.neutralHadronIso());
      chIso03_=muon.isoDeposit(pat::PfChargedHadronIso)->depositAndCountWithin(0.3, vetos_ch).first;
      chIso04_=muon.isoDeposit(pat::PfChargedHadronIso)->depositAndCountWithin(0.4, vetos_ch).first;
      //                                                                             cone veto threshold
      //nhIso->push_back(muon.isoDeposit(pat::PfNeutralHadronIso)->depositAndCountWithin(0.4, vetos_nh, 0.5).first);
      nhIso03_=muon.isoDeposit(pat::PfNeutralHadronIso)->depositAndCountWithin(0.3, vetos_nh).first;
      nhIso04_=muon.isoDeposit(pat::PfNeutralHadronIso)->depositAndCountWithin(0.4, vetos_nh).first;
      //phIso->push_back(muon.isoDeposit(pat::PfGammaIso)->depositAndCountWithin(0.4, vetos_ph, 0.5).first);
      phIso03_=muon.isoDeposit(pat::PfGammaIso)->depositAndCountWithin(0.3, vetos_ph).first;
      phIso04_=muon.isoDeposit(pat::PfGammaIso)->depositAndCountWithin(0.4, vetos_ph).first;

      pcIso03_=muon.isoDeposit(pat::PfPUChargedHadronIso)->depositAndCountWithin(0.3, vetos_pc).first;
      pcIso04_=muon.isoDeposit(pat::PfPUChargedHadronIso)->depositAndCountWithin(0.4, vetos_pc).first;

      trackIso_	=muon.trackIso();
      ecalIso_	=muon.ecalIso();
      hcalIso_	=muon.hcalIso();

      if(version_ == 6)if(pt_ < 10 ) 		passed = false;
      if(version_ == 7)if(pt_ < 27 ) 		passed = false;
      if(fabs(eta_) >= 2.1 )	passed = false;
      if( !isGlobal_ )		passed = false;
      if(globalNormChi2_ < 0 || globalNormChi2_ >= 10 )passed = false;
      if(muonHits_ < 1 )	passed = false;
      if(muonMatchStations_ < 2)passed = false;
      if(fabs(dB_) >= 0.2)	passed = false;
      if(fabs(dz_) > 0.5)	passed = false;
      if(trkLayers_ < 6)	passed = false;
      if(pixelHits_ < 1)	passed = false;
      reIsoBeta_= (chIso04_ + max(nhIso04_ + phIso04_ - 0.5*pcIso04_ , 0.0 ))/pt_;
      if( reIsoBeta_ >= 0.12 ) passed = false;
      //if(EVENT == 394919)
      //{
      //  cout<<"In KyMuonSelector EVENT:"<<EVENT<<" relIsoBeta: "<<reIsoBeta_<<endl;
      //}
    }

    if( passed) pos->push_back((*muons_)[i]);
    //if(passed)if(reIsoBeta_ >= 0.12)cout<<"hahahahhaahhahahah"<<endl;
    if( tree)
    {
      if(passed){

        pt->push_back(muon.pt());
        eta->push_back(muon.eta());
        phi->push_back(muon.phi());
        charge->push_back(muon.charge());

        isGlobal->push_back(muon.isGlobalMuon());
        muonMatchStations->push_back( muon.numberOfMatchedStations());
        dB->push_back( muon.dB());
        //const reco::VertexCollection &vertices = *pvHandle.product();
        if(muon.isGlobalMuon() && !(pvHandle->empty()) && !(pvHandle->front().isFake()) )
        {
          const reco::Vertex &vtx = pvHandle->front();
          const reco::TrackRef& muGlobalTrk = muon.globalTrack();
          //if( muGlobalTrk) 
          try{
          dz->push_back(muGlobalTrk->dz(vtx.position()));
          globalNormChi2->push_back(muGlobalTrk->normalizedChi2());
          muonHits->push_back(muGlobalTrk->hitPattern().numberOfValidMuonHits());
          trkLayers->push_back(muon.track()->hitPattern().trackerLayersWithMeasurement());
          trackerHits->push_back(muGlobalTrk->hitPattern().numberOfValidTrackerHits());
          }
          catch(...){
          dz->push_back(-9999);
          globalNormChi2->push_back(-9999);
          muonHits->push_back(-9999);
          trkLayers->push_back(-9999);
          trackerHits->push_back(-9999);
          }
          //if(muon.innerTrack())
          try{
          pixelHits->push_back(muon.innerTrack()->hitPattern().numberOfValidPixelHits());
          }
          catch(...){
          pixelHits->push_back(-9999);
          }
        }
        else
        {
          dz->push_back(-9999);
          globalNormChi2->push_back(-9999);
          muonHits->push_back(-9999);
          trkLayers->push_back(-9999);
          trackerHits->push_back(-9999);
          pixelHits->push_back(-9999);
        }

        //chIso->push_back(muon.chargedHadronIso());
        //phIso->push_back(muon.photonIso());
        //nhIso->push_back(muon.neutralHadronIso());
        chIso03->push_back(muon.isoDeposit(pat::PfChargedHadronIso)->depositAndCountWithin(0.3, vetos_ch).first);
        chIso04->push_back(muon.isoDeposit(pat::PfChargedHadronIso)->depositAndCountWithin(0.4, vetos_ch).first);
        //                                                                             cone veto threshold
        //nhIso->push_back(muon.isoDeposit(pat::PfNeutralHadronIso)->depositAndCountWithin(0.4, vetos_nh, 0.5).first);
        nhIso03->push_back(muon.isoDeposit(pat::PfNeutralHadronIso)->depositAndCountWithin(0.3, vetos_nh).first);
        nhIso04->push_back(muon.isoDeposit(pat::PfNeutralHadronIso)->depositAndCountWithin(0.4, vetos_nh).first);
        //phIso->push_back(muon.isoDeposit(pat::PfGammaIso)->depositAndCountWithin(0.4, vetos_ph, 0.5).first);
        phIso03->push_back(muon.isoDeposit(pat::PfGammaIso)->depositAndCountWithin(0.3, vetos_ph).first);
        phIso04->push_back(muon.isoDeposit(pat::PfGammaIso)->depositAndCountWithin(0.4, vetos_ph).first);

        pcIso03->push_back(muon.isoDeposit(pat::PfPUChargedHadronIso)->depositAndCountWithin(0.3, vetos_pc).first);
        pcIso04->push_back(muon.isoDeposit(pat::PfPUChargedHadronIso)->depositAndCountWithin(0.4, vetos_pc).first);

        trackIso->push_back(muon.trackIso());
        ecalIso->push_back(muon.ecalIso());
        hcalIso->push_back(muon.hcalIso());

      }//passed
    }//tree
  }//muon

  //if(saveTree){
  //for(int i=0; i < (int) cutNames.size() ; i++){
  //  cutflow->AddBinContent(i+1, cut[i]);
  //}
  //}


  multiplicity = (int) pos->size();

  iEvent.put(pos);

  if (tree)
  {
    tree->Fill(); 
  }

}

void 
KyMuonSelector::beginJob(){
  if(tree)
  {
   tree->Branch("EVENT",&EVENT,"EVENT/i");
   tree->Branch("RUN",&RUN,"RUN/i");
   tree->Branch("LUMI",&LUMI,"LUMI/i");

   tree->Branch("multiplicity",&multiplicity,"multiplicity/i");
   tree->Branch("pt","std::vector<double>",&pt);
   tree->Branch("eta","std::vector<double>",&eta);
   tree->Branch("phi","std::vector<double>",&phi);
   tree->Branch("charge","std::vector<double>",&charge);
   tree->Branch("isGlobal","std::vector<int>",&isGlobal);
   tree->Branch("muonMatchStations","std::vector<int>",&muonMatchStations);
   tree->Branch("dB","std::vector<double>",&dB);
   tree->Branch("dz","std::vector<double>",&dz);
   tree->Branch("globalNormChi2","std::vector<double>",&globalNormChi2);
   tree->Branch("muonHits","std::vector<int>",&muonHits);
   tree->Branch("trkLayers","std::vector<int>",&trkLayers);
   tree->Branch("trackerHits","std::vector<int>",&trackerHits);
   tree->Branch("pixelHits","std::vector<int>",&pixelHits);

   tree->Branch("chIso03","std::vector<double>",&chIso03);
   tree->Branch("nhIso03","std::vector<double>",&nhIso03);
   tree->Branch("phIso03","std::vector<double>",&phIso03);
   tree->Branch("pcIso03","std::vector<double>",&pcIso03);
   tree->Branch("chIso04","std::vector<double>",&chIso04);
   tree->Branch("nhIso04","std::vector<double>",&nhIso04);
   tree->Branch("phIso04","std::vector<double>",&phIso04);
   tree->Branch("pcIso04","std::vector<double>",&pcIso04);

   tree->Branch("trackIso","std::vector<double>",&trackIso);
   tree->Branch("ecalIso","std::vector<double>",&ecalIso);
   tree->Branch("hcalIso","std::vector<double>",&hcalIso);
  }
}


void
KyMuonSelector::endJob() {
  //if(saveTree){
  //for(int i=0 ; i < (int) cutNames.size(); i++){
  //  cutflow->GetXaxis()->SetBinLabel(i+1,cutNames[i].c_str());
  //}
  //}
}


#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_FWK_MODULE(KyMuonSelector);

