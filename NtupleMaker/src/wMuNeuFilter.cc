#include "FWCore/Framework/interface/MakerMacros.h"
#include "KoSMP/WAnalyzer/interface/wMuNeuFilter.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/MET.h"

  //virtual void produce(const edm::Event& iEvent, const edm::EventSetup& iSetup)
bool wMuNeuFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  bool acceptFT = false;

  clear();

  EventData.EVENT  = iEvent.id().event();
  EventData.RUN    = iEvent.id().run();
  EventData.LUMI   = iEvent.id().luminosityBlock();

  GetHLTResults(iEvent, iSetup);
  GetGenInfoW(iEvent, iSetup);


//    edm::Handle<double>  rho;
//    iEvent.getByLabel(edm::InputTag("kt6PFJetsPFlow","rho"), rho);

    iEvent.getByLabel(edm::InputTag("addPileupInfo"), PupInfo);
  iEvent.getByLabel(beamSpotInputTag, beamSpot_h);

    std::vector<PileupSummaryInfo>::const_iterator PVI;

    int npv = -1;
    int npvin = -1;
    float sum_nvtx = 0;
    float ave_nvtx = 0;

    if( PupInfo.isValid()){
      for(PVI = PupInfo->begin(); PVI != PupInfo->end(); ++PVI) {
        int tmpnpv = PVI->getPU_NumInteractions();
        sum_nvtx += float(tmpnpv);

        int BX = PVI->getBunchCrossing();

        if(BX == 0) {
          npvin = PVI->getPU_NumInteractions();
          npv = PVI->getTrueNumInteractions();
          continue;
        }

      } 

      ave_nvtx = sum_nvtx/3.;

      double win = LumiWeights_.weight( npvin );
      double w = LumiWeights_.weight( npv );
      //weight = LumiWeights_.weight3BX( ave_nvtx );
      double wplus  = PShiftUp_.ShiftWeight( npv );
      double wminus = PShiftDown_.ShiftWeight( npv );
      //double wplus  = weight*PShiftUp_.ShiftWeight( npv );
      //double wminus = weight*PShiftDown_.ShiftWeight( npv );
      EventData.weightin = win; 
      EventData.weight = w;
      EventData.weightplus = wplus;
      EventData.weightminus = wminus;
      EventData.npileup = npv;
    }

    h_npileupin->Fill(npv);
    h_npileup->Fill(ave_nvtx);


    edm::Handle<reco::VertexCollection> recVtxs_;
    iEvent.getByLabel(vertexLabel_,recVtxs_);

    //int nv = 0 ;

    for(reco::VertexCollection::const_iterator v=recVtxs_->begin();  v!=recVtxs_->end(); ++v){
      EventData.vtx_isFake->push_back(v->isFake());
      EventData.vtx_ndof->push_back(v->ndof());
      EventData.vtx_z->push_back(v->z());
      EventData.vtx_Rho->push_back(v->position().Rho());
      //if (!(v->isFake()) && (v->ndof()>4) && (fabs(v->z())<=24.0) && (v->position().Rho()<=2.0) ) {
      //  nv++;
      //}
    }
    //nvertex = nv;

    h_nvertex->Fill(recVtxs_->size());
    //h_nvertex->Fill(nv);

    //edm::Handle<double> weight_;
    //iEvent.getByLabel("PUweight", weight_);

    //if(weight_.isValid()){
    //  weight = *weight_;
    //}else{
    //  weight = 1.0;
    //}

    //Handler ------------------------
    edm::Handle<std::vector<pat::Muon> > leptons1_hand;
    edm::Handle<std::vector<pat::Muon> > leptons2_hand;
    edm::Handle<pat::METCollection> MET_hand;
    iEvent.getByLabel(leptonLabel1_,leptons1_hand);
    iEvent.getByLabel(leptonLabel2_,leptons2_hand);
    iEvent.getByLabel(metLabel_,MET_hand);

    pat::METCollection::const_iterator mi = MET_hand->begin();

    edm::Handle< reco::PFCandidateCollection > pfCandidates_;
    typedef reco::PFCandidateCollection::const_iterator CI;
    iEvent.getByLabel("particleFlow",pfCandidates_);

    edm::Handle<pat::JetCollection> Jets;
    iEvent.getByLabel(jetLabel_, Jets);

    edm::Handle<reco::GenParticleCollection> genParticles_;
    iEvent.getByLabel(genParticlesLabel_,genParticles_);


    //bool selected = false;

    ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > corrmet;
    corrmet.SetPxPyPzE(mi->px(),mi->py(),0,mi->pt());
    MET = mi->pt();
    met->push_back(corrmet);

    if(metStudy_){
      const Ky::METCandidate pfmet(MET, mi->sumEt(), mi->NeutralEMFraction(),mi->NeutralHadEtFraction(),mi->ChargedHadEtFraction(),mi->ChargedEMEtFraction(),mi->MuonEtFraction() );
      pfMet->push_back(pfmet);
    }

    h_MET->Fill(MET);

    //cout<<"lepton size: "<<leptons1_hand->size()<<endl;
    reco::isodeposit::AbsVetos vetos_ch;
    reco::isodeposit::AbsVetos vetos_nh;
    reco::isodeposit::AbsVetos vetos_ph;
    reco::isodeposit::AbsVetos vetos_pc;
    vetos_nh.push_back(new ThresholdVeto( 0.5 ));
    vetos_ph.push_back(new ThresholdVeto( 0.5 ));

    bool goodVtx=false;
    for(unsigned i = 0; i < leptons1_hand->size(); i++)
    {
      acceptFT = true;
      pat::Muon it1 = leptons1_hand->at(i);
      it1.setP4(it1.pfCandidateRef()->p4());
      const Ky::Lepton lep1(it1.p4(), (int) it1.charge());
      lepton1->push_back(lep1);
      //Pf isolation
      lepton1->back().setIsoDeposit( pat::PfChargedHadronIso, it1.isoDeposit(pat::PfChargedHadronIso), vetos_ch );
      lepton1->back().setIsoDeposit( pat::PfNeutralHadronIso, it1.isoDeposit(pat::PfNeutralHadronIso), vetos_nh );
      lepton1->back().setIsoDeposit( pat::PfGammaIso, it1.isoDeposit(pat::PfGammaIso), vetos_ph );
      lepton1->back().setIsoDeposit( pat::PfPUChargedHadronIso, it1.isoDeposit(pat::PfPUChargedHadronIso), vetos_pc );
      //detector based isolation
      lepton1->back().setIsoDeposit( it1.trackIso(), it1.ecalIso(), it1.hcalIso());
      Lept1_chIso03 = lepton1->back().chIso03();
      Lept1_chIso04 = lepton1->back().chIso04();
      Lept1_nhIso03 = lepton1->back().nhIso03();
      Lept1_nhIso04 = lepton1->back().nhIso04();
      Lept1_phIso03 = lepton1->back().phIso03();
      Lept1_phIso04 = lepton1->back().phIso04();
      Lept1_pcIso03 = lepton1->back().pcIso03();
      Lept1_pcIso04 = lepton1->back().pcIso04();

      Lept1_isGlobal=it1.isGlobalMuon();
      Lept1_isTrker=it1.isTrackerMuon();
      Lept1_pt=it1.pt();
      Lept1_eta=it1.eta();
      Lept1_phi=it1.phi();
      Lept1_px =it1.px();
      Lept1_py =it1.py();
      Lept1_pz =it1.pz();
      Lept1_matchStations=it1.numberOfMatchedStations();
      Lept1_dB=it1.dB();

      //GlobalMuon related
      if(it1.isGlobalMuon())
      {
	const reco::TrackRef& muGlobalTrk = it1.globalTrack();
	try{
	  Lept1_globalNormChi2=muGlobalTrk->normalizedChi2();
	  Lept1_muonHits=muGlobalTrk->hitPattern().numberOfValidMuonHits();
	  Lept1_trackerHits=muGlobalTrk->hitPattern().numberOfValidTrackerHits();
	}catch(...){
	  Lept1_globalNormChi2=-9999;
	  Lept1_muonHits=-9999;
	  Lept1_trackerHits=muGlobalTrk->hitPattern().numberOfValidTrackerHits();
	}
      }else{
	  Lept1_globalNormChi2=-9999;
	  Lept1_muonHits=-9999;
	  Lept1_trackerHits=-9999;
      }

      //Vertex realted
      goodVtx=false;
      /******************
      for( reco::VertexCollection::const_iterator v=recVtxs_->begin();v!=recVtxs_->end();++v)
      {
	if(v->isFake()) continue;
	if(v->ndof() <=4) continue;
	if(v->z() >= 24) continue;
	if(v->position().Rho() >= 2) continue;
	if( !it1.isGlobalMuon() ) continue;
	const reco::TrackRef& muGlobalTrk = it1.globalTrack();
	goodVtx= true;
	try{
	  Lept1_dz=muGlobalTrk->dz(v->position());
	}
	catch(...){
	  Lept1_dz=-9999;
	}
      }//vtx
      if(!goodVtx)
      {
	Lept1_dz=-9999;
      }
      *****************/
      if( recVtxs_->size() >0)
      {
	reco::VertexRef vtx(recVtxs_,0);
	//const reco::TrackRef& muGlobalTrk = it1.globalTrack();
	try{
	  Lept1_dz=it1.innerTrack()->dz(vtx->position());
	}catch(...){
	  Lept1_dz=-9999;
	}
      }else{
	try{
	  Lept1_dz=it1.innerTrack()->dz(beamSpot_h->position());
	}catch(...){
	  Lept1_dz=-9999;
	}
      }
      //other hits
      try{
	Lept1_trkLayers=it1.track()->hitPattern().trackerLayersWithMeasurement();
	Lept1_pixelHits=it1.innerTrack()->hitPattern().numberOfValidPixelHits();
      }catch(...){
	Lept1_trkLayers=-9999;
	Lept1_pixelHits=-9999;
      }
      //W recon
      ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > lept_;
      lept_.SetPxPyPzE(lep1.px(), lep1.py(), lep1.pz(), lep1.energy());
      const Ky::WLeptNeuCand WLeptNeuCand_(lept_, met->at(0),lep1.charge());

      //Fill tree
      Ws.Lept1_chIso03->push_back(Lept1_chIso03);
      Ws.Lept1_chIso04->push_back(Lept1_chIso04);
      Ws.Lept1_nhIso03->push_back(Lept1_nhIso03);
      Ws.Lept1_nhIso04->push_back(Lept1_nhIso04);
      Ws.Lept1_phIso03->push_back(Lept1_phIso03);
      Ws.Lept1_phIso04->push_back(Lept1_phIso04);
      Ws.Lept1_pcIso03->push_back(Lept1_pcIso03);
      Ws.Lept1_pcIso04->push_back(Lept1_pcIso04);
      Ws.Lept1_isGlobal->push_back(Lept1_isGlobal);
      Ws.Lept1_isTrker->push_back(Lept1_isTrker);
      Ws.Lept1_pt->push_back(Lept1_pt);
      Ws.Lept1_eta->push_back(Lept1_eta);
      Ws.Lept1_phi->push_back(Lept1_phi);
      Ws.Lept1_px->push_back(Lept1_px);
      Ws.Lept1_py->push_back(Lept1_py);
      Ws.Lept1_pz->push_back(Lept1_pz);
      Ws.Lept1_matchStations->push_back(Lept1_matchStations);
      Ws.Lept1_dB->push_back(Lept1_dB);

      Ws.Lept1_dz->push_back(Lept1_dz);
      Ws.Lept1_globalNormChi2->push_back(Lept1_globalNormChi2);
      Ws.Lept1_muonHits->push_back(Lept1_muonHits);
      Ws.Lept1_trkLayers->push_back(Lept1_trkLayers);
      Ws.Lept1_trackerHits->push_back(Lept1_trackerHits);
      Ws.Lept1_pixelHits->push_back(Lept1_pixelHits);

      Ws.W_invm->push_back(WLeptNeuCand_.M());
      Ws.Neut_pt->push_back(met->at(0).pt());
      Ws.Neut_phi->push_back(mi->phi());
      Ws.Neut_px->push_back(mi->px());
      Ws.Neut_py->push_back(mi->py());
      Ws.W_pt->push_back(WLeptNeuCand_.pt());
      Ws.W_eta->push_back(WLeptNeuCand_.eta());
      Ws.W_phi->push_back(WLeptNeuCand_.phi());
      Ws.W_px->push_back(WLeptNeuCand_.px());
      Ws.W_py->push_back(WLeptNeuCand_.py());
      Ws.W_pz->push_back(WLeptNeuCand_.pz());
      Ws.W_Mt->push_back(WLeptNeuCand_.Mt());
      Ws.W_Acop->push_back(WLeptNeuCand_.Acop());
      Ws.W_Charge->push_back(WLeptNeuCand_.charge());

      //if(Channel == "Muon"){}

      for(unsigned j = i+1; j < leptons2_hand->size(); j++)
      {
	pat::Muon it2 = leptons2_hand->at(j);
        it2.setP4(it2.pfCandidateRef()->p4());

        const bool match = MatchObjects( it1.p4(), it2.p4(), true);
        if(match) continue;

        const Ky::Lepton lep2(it2.p4(), (int) it2.charge());
        lepton2->push_back(lep2);
        //pf isolation setup
        lepton2->back().setIsoDeposit( pat::PfChargedHadronIso, it2.isoDeposit(pat::PfChargedHadronIso), vetos_ch );
        lepton2->back().setIsoDeposit( pat::PfNeutralHadronIso, it2.isoDeposit(pat::PfNeutralHadronIso), vetos_nh );
        lepton2->back().setIsoDeposit( pat::PfGammaIso, it2.isoDeposit(pat::PfGammaIso), vetos_ph );
        lepton2->back().setIsoDeposit( pat::PfPUChargedHadronIso, it2.isoDeposit(pat::PfPUChargedHadronIso), vetos_pc );
 
        //detector based isolation
        lepton2->back().setIsoDeposit( it2.trackIso(), it2.ecalIso(), it2.hcalIso());
        Lept2_chIso03=lepton2->back().chIso03();
        Lept2_chIso04=lepton2->back().chIso04();
        Lept2_nhIso03=lepton2->back().nhIso03();
        Lept2_nhIso04=lepton2->back().nhIso04();
        Lept2_phIso03=lepton2->back().phIso03();
        Lept2_phIso04=lepton2->back().phIso04();
        Lept2_pcIso03=lepton2->back().pcIso03();
        Lept2_pcIso04=lepton2->back().pcIso04();

        Lept2_isGlobal=it2.isGlobalMuon();
        Lept2_isTrker=it2.isTrackerMuon();
        Lept2_pt=it2.pt();
        Lept2_eta=it2.eta();
        Lept2_phi=it2.phi();
        Lept2_px=it2.px();
        Lept2_py=it2.py();
        Lept2_pz=it2.pz();
        Lept2_matchStations=it2.numberOfMatchedStations();
        Lept2_dB=it2.dB();

        //GlobalMuon related
        if(it2.isGlobalMuon())
        {
  	  const reco::TrackRef& muGlobalTrk = it2.globalTrack();
	  try{
	    Lept2_globalNormChi2=muGlobalTrk->normalizedChi2();
	    Lept2_muonHits=muGlobalTrk->hitPattern().numberOfValidMuonHits();
	    Lept2_trackerHits=muGlobalTrk->hitPattern().numberOfValidTrackerHits();
	  }catch(...){
	    Lept2_globalNormChi2=-9999;
	    Lept2_muonHits=-9999;
	    Lept2_trackerHits=muGlobalTrk->hitPattern().numberOfValidTrackerHits();
	  }
        }else{
	  Lept2_globalNormChi2=-9999;
	  Lept2_muonHits=-9999;
	  Lept2_trackerHits=-9999;
        }

        //Vertex realted
        goodVtx=false;
	/******************************
        for( reco::VertexCollection::const_iterator v=recVtxs_->begin();v!=recVtxs_->end();++v)
        {
	  if(v->isFake()) continue;
	  if(v->ndof() <=4) continue;
	  if(v->z() >= 24) continue;
	  if(v->position().Rho() >= 2) continue;
	  if( !it2.isGlobalMuon() ) continue;
	  const reco::TrackRef& muGlobalTrk = it2.globalTrack();
	  goodVtx= true;
	  try{
	    Lept2_dz=muGlobalTrk->dz(v->position());
	  }
	  catch(...){
	    Lept2_dz=-9999;
	  }
        }//vtx
        if(!goodVtx)
        {
	  Lept2_dz=-9999;
        }
	**********************************/
        if( recVtxs_->size() >0)
        {
	  reco::VertexRef vtx(recVtxs_,0);
	  //const reco::TrackRef& muGlobalTrk = it2.globalTrack();
	  try{
	    Lept2_dz=it2.innerTrack()->dz(vtx->position());
	  }catch(...){
	    Lept2_dz=-9999;
	  }
        }else{
	  try{
	    Lept2_dz=it2.innerTrack()->dz(beamSpot_h->position());
	  }catch(...){
	    Lept2_dz=-9999;
	  }
        }
        //other hits
        try{
	  Lept2_trkLayers=it2.track()->hitPattern().trackerLayersWithMeasurement();
	  Lept2_pixelHits=it2.innerTrack()->hitPattern().numberOfValidPixelHits();
        }catch(...){
	  Lept2_trkLayers=-9999;
	  Lept2_pixelHits=-9999;
        }

	//vertexfit
        Ky::ZCandidate Dimuon(lepton1->back(), lepton2->back());
	ESHandle<TransientTrackBuilder> trackBuilder;
	iSetup.get<TransientTrackRecord>().get("TransientTrackBuilder",trackBuilder);
	reco::TrackRef trkerTrk1 = it1.track();
	reco::TrackRef trkerTrk2 = it2.track();
	if(trkerTrk1.isNonnull() && trkerTrk2.isNonnull())
	{
	  reco::TransientTrack transientTrk1 = trackBuilder->build(trkerTrk1);
	  reco::TransientTrack transientTrk2 = trackBuilder->build(trkerTrk2);
	  Dimuon.KalmanVtxFit(transientTrk1, transientTrk2);
	}

	//Fill tree
        Zs.Lept1_chIso03->push_back(Lept1_chIso03);
        Zs.Lept1_chIso04->push_back(Lept1_chIso04);
        Zs.Lept1_nhIso03->push_back(Lept1_nhIso03);
        Zs.Lept1_nhIso04->push_back(Lept1_nhIso04);
        Zs.Lept1_phIso03->push_back(Lept1_phIso03);
        Zs.Lept1_phIso04->push_back(Lept1_phIso04);
        Zs.Lept1_pcIso03->push_back(Lept1_pcIso03);
        Zs.Lept1_pcIso04->push_back(Lept1_pcIso04);

        Zs.Lept2_chIso03->push_back(Lept2_chIso03);
        Zs.Lept2_chIso04->push_back(Lept2_chIso04);
        Zs.Lept2_nhIso03->push_back(Lept2_nhIso03);
        Zs.Lept2_nhIso04->push_back(Lept2_nhIso04);
        Zs.Lept2_phIso03->push_back(Lept2_phIso03);
        Zs.Lept2_phIso04->push_back(Lept2_phIso04);
        Zs.Lept2_pcIso03->push_back(Lept2_pcIso03);
        Zs.Lept2_pcIso04->push_back(Lept2_pcIso04);

        Zs.Lept1_isGlobal->push_back(Lept1_isGlobal);
        Zs.Lept1_isTrker->push_back(Lept1_isTrker);
        Zs.Lept1_pt->push_back(Lept1_pt);
        Zs.Lept1_eta->push_back(Lept1_eta);
        Zs.Lept1_phi->push_back(Lept1_phi);
        Zs.Lept1_px->push_back(Lept1_px);
        Zs.Lept1_py->push_back(Lept1_py);
        Zs.Lept1_pz->push_back(Lept1_pz);
        Zs.Lept1_matchStations->push_back(Lept1_matchStations);
        Zs.Lept1_dB->push_back(Lept1_dB);
        Zs.Lept2_isGlobal->push_back(Lept2_isGlobal);
        Zs.Lept2_isTrker->push_back(Lept2_isTrker);
        Zs.Lept2_pt->push_back(Lept2_pt);
        Zs.Lept2_eta->push_back(Lept2_eta);
        Zs.Lept2_phi->push_back(Lept2_phi);
        Zs.Lept2_px->push_back(Lept2_px);
        Zs.Lept2_py->push_back(Lept2_py);
        Zs.Lept2_pz->push_back(Lept2_pz);
        Zs.Lept2_matchStations->push_back(Lept2_matchStations);
        Zs.Lept2_dB->push_back(Lept2_dB);

        Zs.Lept1_dz->push_back(Lept1_dz);
        Zs.Lept1_globalNormChi2->push_back(Lept1_globalNormChi2);
        Zs.Lept1_muonHits->push_back(Lept1_muonHits);
        Zs.Lept1_trkLayers->push_back(Lept1_trkLayers);
        Zs.Lept1_trackerHits->push_back(Lept1_trackerHits);
        Zs.Lept1_pixelHits->push_back(Lept1_pixelHits);
        Zs.Lept2_dz->push_back(Lept2_dz);
        Zs.Lept2_globalNormChi2->push_back(Lept2_globalNormChi2);
        Zs.Lept2_muonHits->push_back(Lept2_muonHits);
        Zs.Lept2_trkLayers->push_back(Lept2_trkLayers);
        Zs.Lept2_trackerHits->push_back(Lept2_trackerHits);
        Zs.Lept2_pixelHits->push_back(Lept2_pixelHits);

        //dphimetlepton1 = fabs(deltaPhi(mi->phi(),it1.phi()));
        //dphimetlepton2 = fabs(deltaPhi(mi->phi(),it2.phi()));
 
	Zs.diLeptVtxProb->push_back(Dimuon.diLeptVtxProb());
        Zs.ZMass->push_back( Dimuon.mass());
        Zs.phi->push_back( Dimuon.phi());
        Zs.eta->push_back( Dimuon.eta());
        Zs.pt->push_back( Dimuon.pt());
        Zs.px->push_back( Dimuon.px());
        Zs.py->push_back( Dimuon.py());
        Zs.pz->push_back( Dimuon.pz());
        Zs.Neut_pt->push_back( met->at(0).pt());
        Zs.Neut_phi->push_back( mi->phi());
        Zs.Neut_px->push_back( mi->px());
        Zs.Neut_py->push_back( mi->py());
	Zs.Sign->push_back(Dimuon.sign()); //--(-2), +-(0), ++(2)
        
        h_lept1_pt->Fill(it1.pt());
        h_lept2_pt->Fill(it2.pt());
        h_Zmass->Fill(Dimuon.mass());

        //break;
      }//leptons2_hand
      //break;
    }//leptons1_hand

    //ESHandle<SetupData> pSetup;
    //iSetup.get<SetupRecord>().get(pSetup);
    tree->Fill();

    return acceptFT;

}
DEFINE_FWK_MODULE(wMuNeuFilter);

