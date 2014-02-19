#include "FWCore/Framework/interface/MakerMacros.h"
#include "KoSMP/WAnalyzer/interface/wEleNeuFilter.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/MET.h"

  //virtual void produce(const edm::Event& iEvent, const edm::EventSetup& iSetup)
bool wEleNeuFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  bool acceptFT = false;

  clear();

  EventData.EVENT  = iEvent.id().event();
  EventData.RUN    = iEvent.id().run();
  EventData.LUMI   = iEvent.id().luminosityBlock();
  const bool isRD = iEvent.isRealData();

  GetHLTResults(iEvent, iSetup);


//    edm::Handle<double>  rho;
//    iEvent.getByLabel(edm::InputTag("kt6PFJetsPFlow","rho"), rho);

  iEvent.getByLabel(edm::InputTag("addPileupInfo"), PupInfo);
  iEvent.getByLabel(beamSpotInputTag, beamSpot_h);
  iEvent.getByLabel(rhoIsoInputTag, rhoIso_h);
  iEvent.getByLabel(conversionsInputTag, conversions_h);
  
  rhoIso = *(rhoIso_h.product());
  EventData.rhoIso = rhoIso;

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
    edm::Handle<std::vector<pat::Electron> > leptons1_hand;
    edm::Handle<std::vector<pat::Electron> > leptons2_hand;
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

    bool goodVtx=false;
    for(unsigned i = 0; i < leptons1_hand->size(); i++)
    {
      acceptFT = true;
      pat::Electron it1 = leptons1_hand->at(i);
      it1.setP4(it1.pfCandidateRef()->p4());
      const Ky::Lepton lep1(it1.p4(), (int) it1.charge());
      lepton1->push_back(lep1);
      Lept1_pt = it1.pt();
      Lept1_eta = it1.eta();
      Lept1_phi = it1.phi();
      Lept1_px =it1.px();
      Lept1_py =it1.py();
      Lept1_pz =it1.pz();
      Lept1_etaSC = it1.superCluster()->eta();
      Lept1_phiSC = it1.superCluster()->phi();
      Lept1_dEtaIn = it1.deltaEtaSuperClusterTrackAtVtx();
      Lept1_dPhiIn = it1.deltaPhiSuperClusterTrackAtVtx();
      Lept1_sigmaIEtaIEta = it1.sigmaIetaIeta();
      Lept1_HoverE = it1.hadronicOverEm();
      Lept1_fbrem = it1.fbrem();
      Lept1_energyEC = it1.ecalEnergy();
      Lept1_Pnorm = it1.trackMomentumAtVtx().R();
      Lept1_InvEminusInvP = 1/Lept1_energyEC - 1/Lept1_Pnorm;
      if( recVtxs_->size() > 0)
      {
	reco::VertexRef vtx(recVtxs_,0);
	Lept1_dxy = it1.gsfTrack()->dxy(vtx->position());
	Lept1_dz = it1.gsfTrack()->dz(vtx->position());
      }else{
	Lept1_dxy = it1.gsfTrack()->dxy();
	Lept1_dz = it1.gsfTrack()->dz();
      }
      Direction Dir = Direction(Lept1_etaSC, Lept1_phiSC);
      if(isRD){
	Lept1_AEff03 = ElectronEffectiveArea::GetElectronEffectiveArea(
	    ElectronEffectiveArea::kEleGammaAndNeutralHadronIso03,
	    Lept1_etaSC,
	    ElectronEffectiveArea::kEleEAData2012); // kEleEAData2011 -> kEleEAData2012 for 2012 Real Data 
      }else{
	Lept1_AEff03 = ElectronEffectiveArea::GetElectronEffectiveArea(
	    ElectronEffectiveArea::kEleGammaAndNeutralHadronIso03,
	    Lept1_etaSC,
	    ElectronEffectiveArea::kEleEAData2012); //  kEleEAFall11MC -> kEleEAData2012   
      }
      //Pf isolation
      reco::isodeposit::AbsVetos vetos_ch;
      reco::isodeposit::AbsVetos vetos_nh;
      reco::isodeposit::AbsVetos vetos_ph;
      //vetos_nh.push_back(new ThresholdVeto( 0.5 ));
      //vetos_ph.push_back(new ThresholdVeto( 0.5 ));
      //PF isolation electron veto from EGM (updated the 4 April 2012)
      if(fabs(Lept1_etaSC > 1.479) )
      {
	vetos_ch.push_back(new ConeVeto(Dir, 0.015));
	vetos_ph.push_back(new ConeVeto(Dir, 0.08));
      }

      //If you want to try neutral hadron (electron leakage to Hcal) or photon (for example FSR) veto around lepton
      //reco::isodeposit::Direction Dir1 = Direction(it1.eta(),it1.phi());
      //reco::isodeposit::Direction Dir1 = Direction(it1.superCluster()->eta(),it1.superCluster()->phi());
      //vetos_nh.push_back(new RectangularEtaPhiVeto(Dir, -0.1,0.1,-0.2,0.2));
      //vetos_nh.push_back(new ConeVeto(Dir,0.1);
      //vetos_ph.push_back(new RectangularEtaPhiVeto(Dir, -0.1,0.1,-0.2,0.2));
      //vetos_ph.push_back(new ConeVeto(Dir,0.1);
      lepton1->back().setIsoDeposit( pat::PfChargedHadronIso, it1.isoDeposit(pat::PfChargedHadronIso), vetos_ch );
      lepton1->back().setIsoDeposit( pat::PfNeutralHadronIso, it1.isoDeposit(pat::PfNeutralHadronIso), vetos_nh );
      lepton1->back().setIsoDeposit( pat::PfGammaIso, it1.isoDeposit(pat::PfGammaIso), vetos_ph );
      lepton1->back().setIsoDeposit( pat::PfPUChargedHadronIso, it1.isoDeposit(pat::PfPUChargedHadronIso), vetos_ch );
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

      Lept1_relIsoCom03 = (Lept1_chIso03 + Lept1_nhIso03 + Lept1_phIso03)/Lept1_pt;
      Lept1_relIsoCom04 = (Lept1_chIso04 + Lept1_nhIso04 + Lept1_phIso04)/Lept1_pt;
      Lept1_relIsoBeta03 = (Lept1_chIso03+
	  max(0.0, Lept1_nhIso03 + Lept1_phIso03 - 0.5*Lept1_pcIso03))
	  /Lept1_pt;
      Lept1_relIsoBeta04 = (Lept1_chIso04+
	  max(0.0, Lept1_nhIso04 + Lept1_phIso04 - 0.5*Lept1_pcIso04))
	  /Lept1_pt;
      Lept1_relIsoRho03 = (Lept1_chIso03 +
	  max(0.0, Lept1_nhIso03 + Lept1_phIso03 - rhoIso*Lept1_AEff03))
	/Lept1_pt;
      Lept1_hasConversion = ConversionTools::hasMatchedConversion(it1,conversions_h, beamSpot_h->position());
      Lept1_mHits = it1.gsfTrack()->trackerExpectedHitsInner().numberOfHits();


	//W recon
      ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > lept_;
      lept_.SetPxPyPzE(lep1.px(), lep1.py(), lep1.pz(), lep1.energy());
      const Ky::WLeptNeuCand WLeptNeuCand_(lept_, met->at(0),lep1.charge());
      //Fill W vectors
      Ws.Lept1_pt->push_back(Lept1_pt);
      Ws.Lept1_eta->push_back(Lept1_eta);
      Ws.Lept1_phi->push_back(Lept1_phi);
      Ws.Lept1_px->push_back(Lept1_px);
      Ws.Lept1_py->push_back(Lept1_py);
      Ws.Lept1_pz->push_back(Lept1_pz);
      Ws.Lept1_etaSC->push_back(Lept1_etaSC);
      Ws.Lept1_phiSC->push_back(Lept1_phiSC);
      Ws.Lept1_dEtaIn->push_back(Lept1_dEtaIn);
      Ws.Lept1_dPhiIn->push_back(Lept1_dPhiIn);
      Ws.Lept1_sigmaIEtaIEta->push_back(Lept1_sigmaIEtaIEta);
      Ws.Lept1_HoverE->push_back(Lept1_HoverE);
      Ws.Lept1_fbrem->push_back(Lept1_fbrem);
      Ws.Lept1_energyEC->push_back(Lept1_energyEC);
      Ws.Lept1_Pnorm->push_back(Lept1_Pnorm);
      Ws.Lept1_InvEminusInvP->push_back(Lept1_InvEminusInvP);
      Ws.Lept1_dxy->push_back(Lept1_dxy);
      Ws.Lept1_dz->push_back(Lept1_dz);
      Ws.Lept1_AEff03->push_back(Lept1_AEff03);
      Ws.Lept1_chIso03->push_back(Lept1_chIso03);
      Ws.Lept1_chIso04->push_back(Lept1_chIso04);
      Ws.Lept1_nhIso03->push_back(Lept1_nhIso03);
      Ws.Lept1_nhIso04->push_back(Lept1_nhIso04);
      Ws.Lept1_phIso03->push_back(Lept1_phIso03);
      Ws.Lept1_phIso04->push_back(Lept1_phIso04);
      Ws.Lept1_pcIso03->push_back(Lept1_pcIso03);
      Ws.Lept1_pcIso04->push_back(Lept1_pcIso04);
      Ws.Lept1_relIsoCom03->push_back(Lept1_relIsoCom03);
      Ws.Lept1_relIsoCom04->push_back(Lept1_relIsoCom04);
      Ws.Lept1_relIsoBeta03->push_back(Lept1_relIsoBeta03);
      Ws.Lept1_relIsoBeta04->push_back(Lept1_relIsoBeta04);
      Ws.Lept1_relIsoRho03->push_back(Lept1_relIsoRho03);
      Ws.Lept1_hasConversion->push_back(Lept1_hasConversion);
      Ws.Lept1_mHits->push_back(Lept1_mHits);

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
	pat::Electron it2 = leptons2_hand->at(j);
        it2.setP4(it2.pfCandidateRef()->p4());

        const bool match = MatchObjects( it1.p4(), it2.p4(), true);
        if(match) continue;

        const Ky::Lepton lep2(it2.p4(), (int) it2.charge());
        lepton2->push_back(lep2);

        Lept2_pt = it2.pt();
        Lept2_eta = it2.eta();
        Lept2_phi = it2.phi();
        Lept2_px=it2.px();
        Lept2_py=it2.py();
        Lept2_pz=it2.pz();
        Lept2_etaSC = it2.superCluster()->eta();
        Lept2_phiSC = it2.superCluster()->phi();
        Lept2_dEtaIn = it2.deltaEtaSuperClusterTrackAtVtx();
        Lept2_dPhiIn = it2.deltaPhiSuperClusterTrackAtVtx();
        Lept2_sigmaIEtaIEta = it2.sigmaIetaIeta();
        Lept2_HoverE = it2.hadronicOverEm();
        Lept2_fbrem = it2.fbrem();
        Lept2_energyEC = it2.ecalEnergy();
        Lept2_Pnorm = it2.trackMomentumAtVtx().R();
        Lept2_InvEminusInvP = 1/Lept1_energyEC - 1/Lept1_Pnorm;
        if( recVtxs_->size() > 0)
        {
          reco::VertexRef vtx(recVtxs_,0);
          Lept1_dxy = it2.gsfTrack()->dxy(vtx->position());
          Lept1_dz = it2.gsfTrack()->dz(vtx->position());
        }else{
          Lept1_dxy = it2.gsfTrack()->dxy();
          Lept1_dz = it2.gsfTrack()->dz();
        }
        Direction Dir2 = Direction(Lept2_etaSC, Lept2_phiSC);
        if(isRD){
          Lept2_AEff03 = ElectronEffectiveArea::GetElectronEffectiveArea(
              ElectronEffectiveArea::kEleGammaAndNeutralHadronIso03,
              Lept2_etaSC,
              ElectronEffectiveArea::kEleEAData2012); // kEleEAData2011 -> kEleEAData2012 for 2012 Real Data 
        }else{
          Lept2_AEff03 = ElectronEffectiveArea::GetElectronEffectiveArea(
              ElectronEffectiveArea::kEleGammaAndNeutralHadronIso03,
              Lept2_etaSC,
              ElectronEffectiveArea::kEleEAData2012); //  kEleEAFall11MC -> kEleEAData2012   
        }
        //Pf isolation
        reco::isodeposit::AbsVetos vetos_ch2;
        reco::isodeposit::AbsVetos vetos_nh2;
        reco::isodeposit::AbsVetos vetos_ph2;
        //vetos_nh2.push_back(new ThresholdVeto( 0.5 ));
        //vetos_ph2.push_back(new ThresholdVeto( 0.5 ));
        //If you want to try neutral hadron (electron leakage to Hcal) or photon (for example FSR) veto around lepton
        if(fabs(Lept2_etaSC > 1.479) )
        {
	  vetos_ch2.push_back(new ConeVeto(Dir, 0.015));
	  vetos_ph2.push_back(new ConeVeto(Dir, 0.08));
        }
        lepton2->back().setIsoDeposit( pat::PfChargedHadronIso, it2.isoDeposit(pat::PfChargedHadronIso), vetos_ch2 );
        lepton2->back().setIsoDeposit( pat::PfNeutralHadronIso, it2.isoDeposit(pat::PfNeutralHadronIso), vetos_nh2 );
        lepton2->back().setIsoDeposit( pat::PfGammaIso, it2.isoDeposit(pat::PfGammaIso), vetos_ph2 );
        lepton2->back().setIsoDeposit( pat::PfPUChargedHadronIso, it2.isoDeposit(pat::PfPUChargedHadronIso), vetos_ch2 );
 
        //detector based isolation
        lepton2->back().setIsoDeposit( it2.trackIso(), it2.ecalIso(), it2.hcalIso());
        Lept2_chIso03 = lepton2->back().chIso03();
        Lept2_chIso04 = lepton2->back().chIso04();
        Lept2_nhIso03 = lepton2->back().nhIso03();
        Lept2_nhIso04 = lepton2->back().nhIso04();
        Lept2_phIso03 = lepton2->back().phIso03();
        Lept2_phIso04 = lepton2->back().phIso04();
        Lept2_pcIso03 = lepton2->back().pcIso03();
        Lept2_pcIso04 = lepton2->back().pcIso04();

        Lept2_relIsoCom03 = (Lept2_chIso03 + Lept2_nhIso03 + Lept2_phIso03)/Lept2_pt;
        Lept2_relIsoCom04 = (Lept2_chIso04 + Lept2_nhIso04 + Lept2_phIso04)/Lept2_pt;
        Lept2_relIsoBeta03 = (Lept2_chIso03+
            max(0.0, Lept2_nhIso03 + Lept2_phIso03 - 0.5*Lept2_pcIso03))
            /Lept2_pt;
        Lept2_relIsoBeta04 = (Lept2_chIso04+
            max(0.0, Lept2_nhIso04 + Lept2_phIso04 - 0.5*Lept2_pcIso04))
            /Lept2_pt;
        Lept2_relIsoRho03 = (Lept2_chIso03 +
            max(0.0, Lept2_nhIso03 + Lept2_phIso03 - rhoIso*Lept2_AEff03))
          /Lept2_pt;
        Lept2_hasConversion = ConversionTools::hasMatchedConversion(it2,conversions_h, beamSpot_h->position());
        Lept2_mHits = it2.gsfTrack()->trackerExpectedHitsInner().numberOfHits();

        //vertexfit
        Ky::ZCandidate Dimuon(lepton1->back(), lepton2->back());
	//ESHandle<MagneticField> B_h;
	//iSetup.get<IdealMagneticFieldRecord>().get(B_h);
	//const MagneticField *B = B_h.product();
	ESHandle<TransientTrackBuilder> trackBuilder;
	iSetup.get<TransientTrackRecord>().get("TransientTrackBuilder",trackBuilder);
	if(it1.gsfTrack().isNonnull() && it2.gsfTrack().isNonnull())
	{
	reco::TransientTrack transientTrk1 = trackBuilder->build(it1.gsfTrack());
	reco::TransientTrack transientTrk2 = trackBuilder->build(it2.gsfTrack());
	//reco::TransientTrack transientTrk1(it1.gsfTrack(),B);
	//reco::TransientTrack transientTrk2(it2.gsfTrack(),B);
	//reco::TransientTrack transientTrk1(it1.track(),B);
	//reco::TransientTrack transientTrk2(it2.track(),B);
	Dimuon.KalmanVtxFit(transientTrk1, transientTrk2);
	}

        Zs.Lept1_pt->push_back(Lept1_pt);
        Zs.Lept1_eta->push_back(Lept1_eta);
        Zs.Lept1_phi->push_back(Lept1_phi);
        Zs.Lept1_px->push_back(Lept1_px);
        Zs.Lept1_py->push_back(Lept1_py);
        Zs.Lept1_pz->push_back(Lept1_pz);
        Zs.Lept1_etaSC->push_back(Lept1_etaSC);
        Zs.Lept1_phiSC->push_back(Lept1_phiSC);
        Zs.Lept1_dEtaIn->push_back(Lept1_dEtaIn);
        Zs.Lept1_dPhiIn->push_back(Lept1_dPhiIn);
        Zs.Lept1_sigmaIEtaIEta->push_back(Lept1_sigmaIEtaIEta);
        Zs.Lept1_HoverE->push_back(Lept1_HoverE);
        Zs.Lept1_fbrem->push_back(Lept1_fbrem);
        Zs.Lept1_energyEC->push_back(Lept1_energyEC);
        Zs.Lept1_Pnorm->push_back(Lept1_Pnorm);
        Zs.Lept1_InvEminusInvP->push_back(Lept1_InvEminusInvP);
        Zs.Lept1_dxy->push_back(Lept1_dxy);
        Zs.Lept1_dz->push_back(Lept1_dz);
        Zs.Lept1_AEff03->push_back(Lept1_AEff03);
        Zs.Lept1_chIso03->push_back(Lept1_chIso03);
        Zs.Lept1_chIso04->push_back(Lept1_chIso04);
        Zs.Lept1_nhIso03->push_back(Lept1_nhIso03);
        Zs.Lept1_nhIso04->push_back(Lept1_nhIso04);
        Zs.Lept1_phIso03->push_back(Lept1_phIso03);
        Zs.Lept1_phIso04->push_back(Lept1_phIso04);
        Zs.Lept1_pcIso03->push_back(Lept1_pcIso03);
        Zs.Lept1_pcIso04->push_back(Lept1_pcIso04);
        Zs.Lept1_relIsoCom03->push_back(Lept1_relIsoCom03);
        Zs.Lept1_relIsoCom04->push_back(Lept1_relIsoCom04);
        Zs.Lept1_relIsoBeta03->push_back(Lept1_relIsoBeta03);
        Zs.Lept1_relIsoBeta04->push_back(Lept1_relIsoBeta04);
        Zs.Lept1_relIsoRho03->push_back(Lept1_relIsoRho03);
        Zs.Lept1_hasConversion->push_back(Lept1_hasConversion);
        Zs.Lept1_mHits->push_back(Lept1_mHits);

        Zs.Lept2_pt->push_back(Lept2_pt);
        Zs.Lept2_eta->push_back(Lept2_eta);
        Zs.Lept2_phi->push_back(Lept2_phi);
        Zs.Lept2_px->push_back(Lept2_px);
        Zs.Lept2_py->push_back(Lept2_py);
        Zs.Lept2_pz->push_back(Lept2_pz);
        Zs.Lept2_etaSC->push_back(Lept2_etaSC);
        Zs.Lept2_phiSC->push_back(Lept2_phiSC);
        Zs.Lept2_dEtaIn->push_back(Lept2_dEtaIn);
        Zs.Lept2_dPhiIn->push_back(Lept2_dPhiIn);
        Zs.Lept2_sigmaIEtaIEta->push_back(Lept2_sigmaIEtaIEta);
        Zs.Lept2_HoverE->push_back(Lept2_HoverE);
        Zs.Lept2_fbrem->push_back(Lept2_fbrem);
        Zs.Lept2_energyEC->push_back(Lept2_energyEC);
        Zs.Lept2_Pnorm->push_back(Lept2_Pnorm);
        Zs.Lept2_InvEminusInvP->push_back(Lept2_InvEminusInvP);
        Zs.Lept2_dxy->push_back(Lept2_dxy);
        Zs.Lept2_dz->push_back(Lept2_dz);
        Zs.Lept2_AEff03->push_back(Lept2_AEff03);
        Zs.Lept2_chIso03->push_back(Lept2_chIso03);
        Zs.Lept2_chIso04->push_back(Lept2_chIso04);
        Zs.Lept2_nhIso03->push_back(Lept2_nhIso03);
        Zs.Lept2_nhIso04->push_back(Lept2_nhIso04);
        Zs.Lept2_phIso03->push_back(Lept2_phIso03);
        Zs.Lept2_phIso04->push_back(Lept2_phIso04);
        Zs.Lept2_pcIso03->push_back(Lept2_pcIso03);
        Zs.Lept2_pcIso04->push_back(Lept2_pcIso04);
        Zs.Lept2_relIsoCom03->push_back(Lept2_relIsoCom03);
        Zs.Lept2_relIsoCom04->push_back(Lept2_relIsoCom04);
        Zs.Lept2_relIsoBeta03->push_back(Lept2_relIsoBeta03);
        Zs.Lept2_relIsoBeta04->push_back(Lept2_relIsoBeta04);
        Zs.Lept2_relIsoRho03->push_back(Lept2_relIsoRho03);
        Zs.Lept2_hasConversion->push_back(Lept2_hasConversion);
        Zs.Lept2_mHits->push_back(Lept2_mHits);


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

DEFINE_FWK_MODULE(wEleNeuFilter);

