#include "FWCore/Framework/interface/MakerMacros.h"
#include "KoSMP/WAnalyzer/interface/wLeptNeuFilter.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/MET.h"
//#include "DataFormats/METReco/interface/GenMET.h"
//#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"
  //virtual void produce(const edm::Event& iEvent, const edm::EventSetup& iSetup)
bool wLeptNeuFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  //cout<<"Channel: "<<Channel<<"#########################################"<<endl;

  acceptFT = false;

  clear();

  EventData.EVENT  = iEvent.id().event();
  EventData.RUN    = iEvent.id().run();
  EventData.LUMI   = iEvent.id().luminosityBlock();
  isRD = iEvent.isRealData();
  //const bool isRD = iEvent.isRealData();

  GetHLTResults(iEvent, iSetup);
  if(! isRD)
  {
    GetGenInfoW(iEvent, iSetup);
    GetGenInfoZ(iEvent, iSetup);
    GetFSRInfoW(iEvent, iSetup);
  }
//    edm::Handle<double>  rho;
//    iEvent.getByLabel(edm::InputTag("kt6PFJetsPFlow","rho"), rho);

  iEvent.getByLabel(edm::InputTag("addPileupInfo"), PupInfo);
  iEvent.getByLabel(beamSpotInputTag, beamSpot_h);
  if( Channel == "Electron")
  {
    iEvent.getByLabel(rhoIsoInputTag, rhoIso_h);
    iEvent.getByLabel(conversionsInputTag, conversions_h);
    rhoIso = *(rhoIso_h.product());
    EventData.rhoIso = rhoIso;
  }
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

    if(Channel == "Muon"){
    iEvent.getByLabel(leptonLabel1_,mu1_hand);
    iEvent.getByLabel(leptonLabel2_,mu2_hand);
    }else if(Channel == "Electron"){
      iEvent.getByLabel(leptonLabel1_,ele1_hand);
      iEvent.getByLabel(leptonLabel2_,ele2_hand);
    }else if(Channel == "Tau"){
      iEvent.getByLabel(leptonLabel1_,tau1_hand);
      iEvent.getByLabel(leptonLabel2_,tau2_hand);
    }else{cout<<"What kind of a channel hur? "<<Channel<<endl;exit(-1);}

    iEvent.getByLabel(metLabel_,MET_hand);
    MetIt = MET_hand->begin();
/*
    iEvent.getByLabel(noPuMEtLabel_,NoPU_MET_hand);
    NoPU_MetIt = NoPU_MET_hand->begin();

    iEvent.getByLabel(MVAMEtLabel_,MVA_MET_hand);
    MVA_MetIt = MVA_MET_hand->begin();

    iEvent.getByLabel(genMEtTrueLabel_,genMEtTrue_hand);
    genMEtTrue_MetIt = genMEtTrue_hand->begin();
    
    iEvent.getByLabel(genMEtCaloLabel_,genMEtCalo_hand);
    genMEtCalo_MetIt = genMEtCalo_hand->begin();

    iEvent.getByLabel(genMEtCaloAndNonPromptLabel_,genMEtCaloAndNonPrompt_hand);
    genMEtCaloAndNonPrompt_MetIt = genMEtCaloAndNonPrompt_hand->begin();
*/
    edm::Handle< reco::PFCandidateCollection > pfCandidates_;
    typedef reco::PFCandidateCollection::const_iterator CI;
    iEvent.getByLabel("particleFlow",pfCandidates_);

    edm::Handle<pat::JetCollection> Jets;
    iEvent.getByLabel(jetLabel_, Jets);

    edm::Handle<reco::GenParticleCollection> genParticles_;
    iEvent.getByLabel(genParticlesLabel_,genParticles_);


    //bool selected = false;
    ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > corrmet;
    corrmet.SetPxPyPzE(MetIt->px(),MetIt->py(),0,MetIt->pt());
    pfMET = MetIt->pt();
    met->push_back(corrmet);

    if(metStudy_){
      const Ky::METCandidate pfmet(MET, MetIt->sumEt(),
	  MetIt->NeutralEMFraction(),MetIt->NeutralHadEtFraction(),
	  MetIt->ChargedHadEtFraction(),MetIt->ChargedEMEtFraction(),
	  MetIt->MuonEtFraction() );
      pfMet->push_back(pfmet);
    }

    h_MET->Fill(pfMET);
/*
    NoPU_MET = NoPU_MetIt->pt();
    ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > NoPU_corrmet;
    NoPU_corrmet.SetPxPyPzE(NoPU_MetIt->px(),NoPU_MetIt->py(),0,NoPU_MetIt->pt());
    NoPU_met->push_back(NoPU_corrmet);

    if(NoPU_metStudy_){
      const Ky::METCandidate NoPU_pfmet(NoPU_MET, NoPU_MetIt->sumEt(),
	  NoPU_MetIt->NeutralEMFraction(),NoPU_MetIt->NeutralHadEtFraction(),
	  NoPU_MetIt->ChargedHadEtFraction(),NoPU_MetIt->ChargedEMEtFraction(),
	  NoPU_MetIt->MuonEtFraction() );
      NoPU_pfMet->push_back(NoPU_pfmet);
    }
    h_NoPU_MET->Fill(NoPU_MET);

    MVA_MET = MVA_MetIt->pt();
    ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > MVA_corrmet;
    MVA_corrmet.SetPxPyPzE(MVA_MetIt->px(),MVA_MetIt->py(),0,MVA_MetIt->pt());
    MVA_met->push_back(MVA_corrmet);

    if(MVA_metStudy_){
      const Ky::METCandidate MVA_pfmet(MVA_MET, MVA_MetIt->sumEt(),
	  MVA_MetIt->NeutralEMFraction(),MVA_MetIt->NeutralHadEtFraction(),
	  MVA_MetIt->ChargedHadEtFraction(),MVA_MetIt->ChargedEMEtFraction(),
	  MVA_MetIt->MuonEtFraction() );
      MVA_pfMet->push_back(MVA_pfmet);
    }
    h_MVA_MET->Fill(MVA_MET);

    genMEtTrue_MET = genMEtTrue_MetIt->pt();
    ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > genMEtTrue_corrmet;
    genMEtTrue_corrmet.SetPxPyPzE(genMEtTrue_MetIt->px(),genMEtTrue_MetIt->py(),0,genMEtTrue_MetIt->pt());
    genMEtTrue_met->push_back(genMEtTrue_corrmet);
    
    h_genMEtTrue_MET->Fill(genMEtTrue_MET);

    genMEtCalo_MET = genMEtCalo_MetIt->pt();
    ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > genMEtCalo_corrmet;
    genMEtCalo_corrmet.SetPxPyPzE(genMEtCalo_MetIt->px(),genMEtCalo_MetIt->py(),0,genMEtCalo_MetIt->pt());
    genMEtCalo_met->push_back(genMEtCalo_corrmet);
    
    h_genMEtCalo_MET->Fill(genMEtCalo_MET);

    genMEtCaloAndNonPrompt_MET = genMEtCaloAndNonPrompt_MetIt->pt();
    ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > genMEtCaloAndNonPrompt_corrmet;
    genMEtCaloAndNonPrompt_corrmet.SetPxPyPzE(genMEtCaloAndNonPrompt_MetIt->px(),genMEtCaloAndNonPrompt_MetIt->py(),0,genMEtCaloAndNonPrompt_MetIt->pt());
    genMEtCaloAndNonPrompt_met->push_back(genMEtCaloAndNonPrompt_corrmet);
    
    h_genMEtCaloAndNonPrompt_MET->Fill(genMEtCaloAndNonPrompt_MET);
*/
    if(Channel == "Muon"){
      EventData.Channel = GenType::kMuon;
      LoopMuon(iEvent, iSetup);
    }else if(Channel == "Electron"){
      EventData.Channel = GenType::kElectron;
      LoopElectron(iEvent, iSetup);
    }else if(Channel == "Tau"){
      EventData.Channel = GenType::kTau;
      LoopTau(iEvent, iSetup);
    }else{cout<<"What kind of a channel hur? "<<Channel<<endl;exit(-1);}

    //ESHandle<SetupData> pSetup;
    //iSetup.get<SetupRecord>().get(pSetup);
    tree->Fill();

    return acceptFT;

}
DEFINE_FWK_MODULE(wLeptNeuFilter);

