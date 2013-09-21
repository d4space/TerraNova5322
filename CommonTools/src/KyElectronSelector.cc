#include "KoSMP/CommonTools/interface/KyElectronSelector.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Common/interface/View.h"
#include "DataFormats/Common/interface/Ptr.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "PhysicsTools/SelectorUtils/interface/SimpleCutBasedElectronIDSelectionFunctor.h"
#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"
#include "MagneticField/Engine/interface/MagneticField.h"

#include "DataFormats/BeamSpot/interface/BeamSpot.h"

// #include "TauAnalysis/CandidateTools/interface/FetchCollection.h"
using namespace std;

KyElectronSelector::KyElectronSelector(const edm::ParameterSet& cfg)
{
  version_ = cfg.getUntrackedParameter<int>("version", 13);
  //usepflow_ = cfg.getUntrackedParameter<bool>("usepflow",true);
  cut_ = cfg.getParameter<std::vector<string> >("cut");

  //eidName_ = cfg.getUntrackedParameter<string>("eidName");
  //eidBitMask_ = cfg.getUntrackedParameter<int>("eidBitMask", -1);

  electronLabel_ = cfg.getParameter<edm::InputTag>("electronLabel");
  eleIdSelector_.initialize(cfg.getParameter<edm::ParameterSet>("eleIdSelector") );
  beamSpotLabel_ = cfg.getParameter<edm::InputTag>("beamSpotLabel");
  vertexLabel_ = cfg.getParameter<edm::InputTag>("vertexLabel");
  rhoIsoLabel_ = cfg.getParameter<edm::InputTag>("rhoIsoLabel");
  conversionsInputTag_ = cfg.getParameter<edm::InputTag>("conversionsInputTag");
  bool saveTree = cfg.getUntrackedParameter<bool>("saveTree", true);

  produces<std::vector<pat::Electron> >("");

  tree = 0;
  if ( saveTree )
  {
    edm::Service<TFileService> fs;
    tree = fs->make<TTree>("tree", "Tree for electron study");

    //id2mva = fs->make<TH2F>( "id2mva","id2mva", 200, -1,1, 8,0,8);  
    //id2pfmva = fs->make<TH2F>( "id2pfmva","id2pfmva", 200, -1,1, 8,0,8);  
    //pfMVA2patMVA_ = fs->make<TH2F>("pfMVA2patMVA", "PF based e_pi MVA vs standard MVA;PF based e_pi MVA;Standard MVA", 100, -1, 1, 100, -1, 1);

    pt = new std::vector<double>();
    eta = new std::vector<double>();
    superEta = new std::vector<double>();
    phi = new std::vector<double>();
    dEtaIn = new std::vector<double>();
    dPhiIn = new std::vector<double>();
    sigmaIEtaIEta = new std::vector<double>();
    HoverE = new std::vector<double>();
    fbrem = new std::vector<double>();
    InvEminusInvP = new std::vector<double>();
    dxy = new std::vector<double>();
    dz = new std::vector<double>();
    relIso = new std::vector<double>();
    relIsodb = new std::vector<double>();
    relIsoRho = new std::vector<double>();
    vtxFitConversion = new std::vector<bool>();
    mHits = new std::vector<double>();

  }
}

KyElectronSelector::~KyElectronSelector()
{

}

void KyElectronSelector::produce(edm::Event& iEvent, const edm::EventSetup& es)
{
  using namespace reco;
  using namespace isodeposit;
  if ( tree )
  {
    pt->clear();
    eta->clear();
    superEta->clear();
    phi->clear();
    dEtaIn->clear();
    dPhiIn->clear();
    sigmaIEtaIEta->clear();
    HoverE->clear();
    fbrem->clear();
    InvEminusInvP->clear();
    dxy->clear();
    dz->clear();
    relIso->clear();
    relIsodb->clear();
    relIsoRho->clear();
    vtxFitConversion->clear();
    mHits->clear();


    EVENT  = iEvent.id().event();
    RUN    = iEvent.id().run();
    LUMI   = iEvent.id().luminosityBlock();
  }
  const bool isRD = iEvent.isRealData();


  iEvent.getByLabel(electronLabel_, electrons_);
  iEvent.getByLabel(beamSpotLabel_,beamSpot_); 
  iEvent.getByLabel(vertexLabel_,recVtxs_); 
  iEvent.getByLabel(rhoIsoLabel_,rhoIso_h);
  iEvent.getByLabel(conversionsInputTag_,conversions_h);
  rhoIso_ = *(rhoIso_h.product());


  std::auto_ptr<std::vector<pat::Electron> > pos(new std::vector<pat::Electron>());

  for (unsigned int i=0; i < electrons_->size();++i){
    pat::Electron electron = electrons_->at(i);
    pat::strbitset eleIdSel = eleIdSelector_.getBitTemplate();
    eleIdSelector_(electron,beamSpot_, eleIdSel);

    //if(usepflow_){
    electron.setP4(electron.pfCandidateRef()->p4());
    //}
    pt_ = electron.pt();
    eta_ = electron.eta();
    phi_ = electron.phi();
    super_eta_ = electron.superCluster()->eta();
    super_phi_ = electron.superCluster()->phi();
    dEtaIn_= electron.deltaEtaSuperClusterTrackAtVtx();
    dPhiIn_=-electron.deltaPhiSuperClusterTrackAtVtx();
    sigmaIEtaIEta_=electron.sigmaIetaIeta();
    HoverE_ = electron.hadronicOverEm();
    fbrem_ = electron.fbrem();
    energy_ = electron.ecalEnergy();
    Pnorm_  = electron.trackMomentumAtVtx().R();
    //energy->push_back(energy_);
    //Pnorm ->push_back(Pnorm_);
    //double EoverP = electron.eSuperClusterOverP();
    //cout<<"Pnorm: "<<Pnorm_<<" == "<<energy_/EoverP<<endl;
    InvEminusInvP_=1/energy_-1/Pnorm_;
    if( recVtxs_->size() > 0)
    {
      reco::VertexRef vtx(recVtxs_,0);
      dxy_= electron.gsfTrack()->dxy(vtx->position());
      dz_ = electron.gsfTrack()->dz(vtx->position());
    }else{
      dxy_ = electron.gsfTrack()->dxy();
      dz_ = electron.gsfTrack()->dz();
    }
    isEE = electron.isEE();
    isEB = electron.isEB();

    //cout<<"super eta: "<<super_eta<<" is EB: "<<electron.isEB()<<endl;
    Direction Dir = Direction(super_eta_, super_phi_);
    if(isRD){
      AEff03_ = ElectronEffectiveArea::GetElectronEffectiveArea(
	ElectronEffectiveArea::kEleGammaAndNeutralHadronIso03, super_eta_, ElectronEffectiveArea::kEleEAData2011);
    }else{
      AEff03_ = ElectronEffectiveArea::GetElectronEffectiveArea(
	ElectronEffectiveArea::kEleGammaAndNeutralHadronIso03, super_eta_, ElectronEffectiveArea::kEleEAFall11MC);
    }
    IsoDeposit::AbsVetos vetos_ch;
    IsoDeposit::AbsVetos vetos_nh;
    IsoDeposit::AbsVetos vetos_ph;
    //PF isolation electron veto from EGM (updated the 4 April 2012)
    if(fabs(super_eta_ > 1.479) )
    {
      vetos_ch.push_back(new ConeVeto( Dir, 0.015));
      vetos_ph.push_back(new ConeVeto( Dir, 0.08));
    }
    //threshold veto
    //vetos_nh.push_back(new ThresholdVeto(0.5));
    //vetos_ph.push_back(new ThresholdVeto(0.5));
    //nhIso03->push_back(electron.isoDeposit(pat::PfNeutralHadronIso)->depositAndCountWithin(0.3, vetos_nh, 0.5).first);

    const double chIso03=electron.isoDeposit(pat::PfChargedHadronIso)->depositAndCountWithin(0.3, vetos_ch).first;
    const double nhIso03=electron.isoDeposit(pat::PfNeutralHadronIso)->depositAndCountWithin(0.3, vetos_nh).first;
    const double phIso03=electron.isoDeposit(pat::PfGammaIso)->depositAndCountWithin(0.3, vetos_ph).first;
    const double puChIso03=electron.isoDeposit(pat::PfPUChargedHadronIso)->depositAndCountWithin(0.3, vetos_ch).first;
    const double chAllIso03=electron.isoDeposit(pat::PfChargedAllIso)->depositAndCountWithin(0.3, vetos_ch).first;

    //using access ftn
    //const double chIso03=electron.chargedHadronIso();
    //const double nhIso03=electron.neutralHadronIso();
    //const double phIso03=electron.photonIso();
    //const double puChIso03=electron.puChargedHadronIso();
    const double relIso_ = (chIso03 + nhIso03 + phIso03 ) /pt_;
    const double relIsodb_ = (chIso03 + max(0.0, nhIso03 + phIso03 - 0.5*puChIso03) )/pt_;
    const double relIsoRho_ = (chIso03 + max(0.0, nhIso03 + phIso03 - rhoIso_*AEff03_) )/pt_;

    //const reco::BeamSpot &beamSpot = *(beamSpot_h.product());
    vtxFitConversion_ = ConversionTools::hasMatchedConversion(electron,conversions_h, beamSpot_->position());
    mHits_ = electron.gsfTrack()->trackerExpectedHitsInner().numberOfHits();


    bool passed = false;
    //bool passPre = electron.pt() > ptcut_ && fabs(electron.eta()) < etacut_ && fabs(electron.gsfTrack()->dxy(beamSpot_->position())) < 0.04;
    const double eleMva = electron.mva();
    //const int eidBit = (int)electron.electronID(eidName_);

    const bool passMVA = eleMva > 0.4;
    //const bool passEId = eidBitMask_ < 0 or ((eidBit & eidBitMask_) == eidBitMask_);

    if(version_ == -1)
    {
      passed = true;
    }else if (version_ == 0 )
    {
      bool passId = true;
      bool passIso = true;
      for(size_t ic(0); ic < cut_.size(); ic++)
      {
	passId = eleIdSel.test(cut_[ic]);
	if(!passId) break;
      }
      passed = passId;
    }
    else if (version_ == 13)//Medium Cut
    {
      passed = true;
      if( !isEE && !isEB) passed = false;
      if( pt_ < 30 ) passed = false;
      if( fabs(super_eta_) > 2.5 ) passed = false;
      if( isEB )
      {
	if( sigmaIEtaIEta_ > 0.01 ) passed = false;
	if( fabs( dEtaIn_ ) > 0.004 ) passed = false;
	if( fabs( dPhiIn_ ) > 0.06 ) passed = false;
	if( HoverE_  > 0.12 ) passed = false;
	if( fabs( dxy_)  > 0.02 ) passed = false;
	if( fabs( dz_)  > 0.1 ) passed = false;
	if( fabs( InvEminusInvP_)  > 0.05 ) passed = false;
	if( fabs( mHits_)  > 1 ) passed = false;
	if( vtxFitConversion_ ) passed = false;
	if( relIsoRho_ > 0.15 ) passed = false;
      }else{
	if( sigmaIEtaIEta_ > 0.03 ) passed = false;
	if( fabs( dEtaIn_ ) > 0.007 ) passed = false;
	if( fabs( dPhiIn_ ) > 0.03 ) passed = false;
	if(  HoverE_  > 0.10 ) passed = false;
	if( fabs( dxy_)  > 0.02 ) passed = false;
	if( fabs( dz_)  > 0.1 ) passed = false;
	if( fabs( InvEminusInvP_)  > 0.05 ) passed = false;
	if( fabs( mHits_)  > 1 ) passed = false;
	if( vtxFitConversion_ ) passed = false;
	if( relIsoRho_ > 0.15 ) passed = false;
      }
    }
    else if (version_ == 14)//Medium Pt 10
    {
      passed = true;
      if( !isEE && !isEB) passed = false;
      if( pt_ < 10 ) passed = false;
      if( fabs(super_eta_) > 2.5 ) passed = false;
      if( isEB )
      {
	if( sigmaIEtaIEta_ > 0.01 ) passed = false;
	if( fabs( dEtaIn_ ) > 0.004 ) passed = false;
	if( fabs( dPhiIn_ ) > 0.06 ) passed = false;
	if( HoverE_  > 0.12 ) passed = false;
	if( fabs( dxy_)  > 0.02 ) passed = false;
	if( fabs( dz_)  > 0.1 ) passed = false;
	if( fabs( InvEminusInvP_)  > 0.05 ) passed = false;
	if( fabs( mHits_)  > 1 ) passed = false;
	if( vtxFitConversion_ ) passed = false;
	if( relIsoRho_ > 0.15 ) passed = false;
      }else{
	if( sigmaIEtaIEta_ > 0.03 ) passed = false;
	if( fabs( dEtaIn_ ) > 0.007 ) passed = false;
	if( fabs( dPhiIn_ ) > 0.03 ) passed = false;
	if(  HoverE_  > 0.10 ) passed = false;
	if( fabs( dxy_)  > 0.02 ) passed = false;
	if( fabs( dz_)  > 0.1 ) passed = false;
	if( fabs( InvEminusInvP_)  > 0.05 ) passed = false;
	if( fabs( mHits_)  > 1 ) passed = false;
	if( vtxFitConversion_ ) passed = false;
	if( pt_ > 20 ){
	  if( relIsoRho_ > 0.15 ) passed = false;
	}else{
	  if( relIsoRho_ > 0.10 ) passed = false;
	}
	
      }
    }
    else if (version_ == 1)//WptCut
    {
     passed = true;
     if( !isEE && !isEB) passed = false;
     if( pt_ < 30 ) passed = false;
     if( fabs(super_eta_) > 2.5 ) passed = false;
     if( isEB )
    {
     if( sigmaIEtaIEta_ > 0.01 ) passed = false;
     if( fabs( dEtaIn_ ) > 0.004 ) passed = false;
     if( fabs( dPhiIn_ ) > 0.06 ) passed = false;
     if( HoverE_  > 0.12 ) passed = false;
     if( fabs( dxy_)  > 0.02 ) passed = false;
     if( fabs( dz_)  > 0.1 ) passed = false;
     if( fabs( InvEminusInvP_)  > 0.05 ) passed = false;
     if( fabs( mHits_)  > 1 ) passed = false;
     if( vtxFitConversion_ ) passed = false;
     if( relIsoRho_ > 0.15 ) passed = false;
    }else{
     if( sigmaIEtaIEta_ > 0.03 ) passed = false;
     if( fabs( dEtaIn_ ) > 0.007 ) passed = false;
     if( fabs( dPhiIn_ ) > 0.03 ) passed = false;
     if(  HoverE_  > 0.10 ) passed = false;
     if( fabs( dxy_)  > 0.02 ) passed = false;
     if( fabs( dz_)  > 0.1 ) passed = false;
     if( fabs( InvEminusInvP_)  > 0.05 ) passed = false;
     if( fabs( mHits_)  > 1 ) passed = false;
     if( vtxFitConversion_ ) passed = false;
     if( relIsoRho_ > 0.15 ) passed = false;
    }
   }else if (version_ == 11)//WptCut without SigmaIetIeta cut for ABCD mtheod I ratio SaSbScSd-PassingProbe
    {
     passed = true;
     if( !isEE && !isEB) passed = false;
     if( pt_ < 30 ) passed = false;
     if( fabs(super_eta_) > 2.5 ) passed = false;
     if( isEB )
    {
     //if( sigmaIEtaIEta_ > 0.01 ) passed = false;
     if( fabs( dEtaIn_ ) > 0.004 ) passed = false;
     if( fabs( dPhiIn_ ) > 0.06 ) passed = false;
     if( HoverE_  > 0.12 ) passed = false;
     if( fabs( dxy_)  > 0.02 ) passed = false;
     if( fabs( dz_)  > 0.1 ) passed = false;
     if( fabs( InvEminusInvP_)  > 0.05 ) passed = false;
     if( fabs( mHits_)  > 1 ) passed = false;
     if( vtxFitConversion_ ) passed = false;
     if( relIsoRho_ > 0.15 ) passed = false;
    }else{
    // if( sigmaIEtaIEta_ > 0.03 ) passed = false;
     if( fabs( dEtaIn_ ) > 0.007 ) passed = false;
     if( fabs( dPhiIn_ ) > 0.03 ) passed = false;
     if(  HoverE_  > 0.10 ) passed = false;
     if( fabs( dxy_)  > 0.02 ) passed = false;
     if( fabs( dz_)  > 0.1 ) passed = false;
     if( fabs( InvEminusInvP_)  > 0.05 ) passed = false;
     if( fabs( mHits_)  > 1 ) passed = false;
     if( vtxFitConversion_ ) passed = false;
     if( relIsoRho_ > 0.15 ) passed = false;
    }
   }

    if ( passed ) pos->push_back((*electrons_)[i]);

    if ( tree )
    {
      //id2mva->Fill(eleMva, eidBit);
      //if(usepflow_){
        //id2pfmva->Fill( electron.pfCandidateRef()->mva_e_pi(), eidBit);
        //pfMVA2patMVA_->Fill(eleMva, electron.pfCandidateRef()->mva_e_pi());
      //}

      if(passed){
        pt->push_back(pt_);
        eta->push_back(eta_);
        superEta->push_back(super_eta_);
        phi->push_back(phi_);
	dEtaIn->push_back(dEtaIn_);
	dPhiIn->push_back(dPhiIn_);
	sigmaIEtaIEta->push_back(sigmaIEtaIEta_);
	HoverE->push_back(HoverE_);
	fbrem->push_back(fbrem_);
	InvEminusInvP->push_back(InvEminusInvP_);
	//cout<<"eta: "<<electron.eta()<<" isEB: "<<electron.isEB()<<endl;
	dxy->push_back(dxy_);
	dz->push_back(dz_);
	relIso->push_back(relIso_);
	relIsodb->push_back(relIsodb_);
	relIsoRho->push_back(relIsoRho_);
	vtxFitConversion->push_back(vtxFitConversion_);
	mHits->push_back(mHits_);

	//for(reco::VertexCollection::const_iterator v=recVtxs_->begin();v!=recVtxs_->end();++v)
	//{
	//  vtxFlg=true;
	//  dxy->push_back(electron.gsfTrack()->dxy(v->position()));
	//}
	//if(!vtxFlg) dxy->push_back(electron.gsfTrack()->dxy(beamSpot_->position()));
	//if(!vtxFlg) dz->push_back(electron.gsfTrack()->dz(beamSpot_->position()));

        //trackIso->push_back(electron.trackIso());
        //ecalIso->push_back(electron.ecalIso());
        //hcalIso->push_back(electron.hcalIso());
      }
    }//tree
  }

  multiplicity = (int) pos->size();

  iEvent.put(pos);
  if ( tree )
  {
    tree->Fill(); 
  }

}

void 
KyElectronSelector::beginJob(){
  if ( tree ) 
  {
    tree->Branch("EVENT",&EVENT,"EVENT/i");
    tree->Branch("RUN",&RUN,"RUN/i");
    tree->Branch("LUMI",&LUMI,"LUMI/i");

    tree->Branch("pt","std::vector<double>",&pt);
    tree->Branch("eta","std::vector<double>",&eta);
    tree->Branch("superEta","std::vector<double>",&superEta);
    tree->Branch("phi","std::vector<double>",&phi);
    tree->Branch("dEtaIn","std::vector<double>",&dEtaIn);
    tree->Branch("dPhiIn","std::vector<double>",&dPhiIn);
    tree->Branch("sigmaIEtaIEta","std::vector<double>",&sigmaIEtaIEta);
    tree->Branch("HoverE","std::vector<double>",&HoverE);
    tree->Branch("fbrem","std::vector<double>",&fbrem);
    tree->Branch("InvEminusInvP","std::vector<double>",&InvEminusInvP);
    tree->Branch("dxy","std::vector<double>",&dxy);
    tree->Branch("dz","std::vector<double>",&dz);
    tree->Branch("relIso","std::vector<double>",&relIso);
    tree->Branch("relIsodb","std::vector<double>",&relIsodb);
    tree->Branch("relIsoRho","std::vector<double>",&relIsoRho);
    tree->Branch("vtxFitConversion","std::vector<bool>",&vtxFitConversion);
    tree->Branch("mHits","std::vector<double>",&mHits);
    tree->Branch("multiplicity",&multiplicity,"multiplicity/i");

  }
}

void
KyElectronSelector::endJob() {
//  if ( tree )
 // {
    //id2mva->GetXaxis()->SetTitle("mva");
    //id2mva->GetYaxis()->SetTitle("id90");
    //id2pfmva->GetXaxis()->SetTitle("mva");
    //id2pfmva->GetYaxis()->SetTitle("id90");

    //pfMVA2patMVA_->GetXaxis()->SetTitle("mva"); 
    //pfMVA2patMVA_->GetYaxis()->SetTitle("pfCandidateRefmva"); 
  //}
}

#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_FWK_MODULE(KyElectronSelector);



