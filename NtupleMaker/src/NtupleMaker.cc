#include "FWCore/Framework/interface/MakerMacros.h"
#include "TerraNova/NtupleMaker/interface/NtupleMaker.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/MET.h"
//#include "DataFormats/METReco/interface/GenMET.h"
//#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"
  //virtual void produce(const edm::Event& iEvent, const edm::EventSetup& iSetup)
void NtupleMaker::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  //cout<<"Channel: "<<Channel<<"#########################################"<<endl;

  acceptFT = false;

  clear();

  EventData.EVENT  = iEvent.id().event();
  EventData.RUN    = iEvent.id().run();
  EventData.LUMI   = iEvent.id().luminosityBlock();
  isRD = iEvent.isRealData();


//  cout<<"EAtarget: "<<EAtarget<<endl;

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

    iEvent.getByLabel(pfMEtLabel_,pfMET_hand);
    pfMEt_It = pfMET_hand->begin();

    iEvent.getByLabel(noPuMEtLabel_,NoPuMET_hand);
    NoPuMEt_It = NoPuMET_hand->begin();

    iEvent.getByLabel(MVAMEtLabel_,MVaMET_hand);
    MVaMEt_It = MVaMET_hand->begin();

    iEvent.getByLabel(genMEtTrueLabel_,genMEtTrue_hand);
    genMEtTrue_It = genMEtTrue_hand->begin();
    
    iEvent.getByLabel(genMEtCaloLabel_,genMEtCalo_hand);
    genMEtCalo_It = genMEtCalo_hand->begin();

    iEvent.getByLabel(genMEtCaloAndNonPromptLabel_,genMEtCaloAndNonPrompt_hand);
    genMEtCaloAndNonPrompt_It = genMEtCaloAndNonPrompt_hand->begin();

    edm::Handle< reco::PFCandidateCollection > pfCandidates_;
    typedef reco::PFCandidateCollection::const_iterator CI;
    iEvent.getByLabel("particleFlow",pfCandidates_);

    edm::Handle<pat::JetCollection> Jets;
    iEvent.getByLabel(jetLabel_, Jets);

    edm::Handle<reco::GenParticleCollection> genParticles_;
    iEvent.getByLabel(genParticlesLabel_,genParticles_);


    //bool selected = false;
    //
    //ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > corrmet;
    //corrmet.SetPxPyPzE(It->px(),It->py(),0,pfMEt_It->pt());
    //pfMET = pfMEt_It->pt();
    //met->push_back(corrmet);

    //if(metStudy_){
    //  const Ky::METCandidate pfmet(pfMET, pfMEt_It->sumEt(),
    //      pfMEt_It->NeutralEMFraction(),pfMEt_It->NeutralHadEtFraction(),
    //      pfMEt_It->ChargedHadEtFraction(),pfMEt_It->ChargedEMEtFraction(),
    //      pfMEt_It->MuonEtFraction() );
    //  pfMet->push_back(pfmet);
    //}

    KoMETs.pfMEt_x    =pfMEt_It->px();
    KoMETs.pfMEt_y    =pfMEt_It->py();
    pfMEt4V    ->SetPxPyPzE(pfMEt_It->px(),pfMEt_It->py(),0,pfMEt_It->pt());

//    KoMETs.pfMEt4V    ->SetPxPyPzE(pfMEt_It->px(),pfMEt_It->py(),0,pfMEt_It->pt());
    //KoMETs.pfMEtSumEt = pfMEt_It->sumEt();
    //KoMETs.pfMEtNeuEM = pfMEt_It->NeutralEMFraction();
    //KoMETs.pfMEtNeuHad= pfMEt_It->NeutralHadEtFraction();
    //KoMETs.pfMEtChHad = pfMEt_It->ChargedHadEtFraction();
    //KoMETs.pfMEtChEM  = pfMEt_It->ChargedEMEtFraction();
    //KoMETs.pfMEtMu    = pfMEt_It->MuonEtFraction();

    KoMETs.NoPuMEt_x    =NoPuMEt_It->px();
    KoMETs.NoPuMEt_y    =NoPuMEt_It->py();
    //KoMETs.NoPuMEtSumEt = NoPuMEt_It->sumEt();
    //KoMETs.NoPuMEtNeuEM = NoPuMEt_It->NeutralEMFraction();
    //KoMETs.NoPuMEtNeuHad= NoPuMEt_It->NeutralHadEtFraction();
    //KoMETs.NoPuMEtChHad = NoPuMEt_It->ChargedHadEtFraction();
    //KoMETs.NoPuMEtChEM  = NoPuMEt_It->ChargedEMEtFraction();
    //KoMETs.NoPuMEtMu    = NoPuMEt_It->MuonEtFraction();

    KoMETs.MVaMEt_x     =MVaMEt_It->px();
    KoMETs.MVaMEt_y     =MVaMEt_It->py();
    //KoMETs.MVaMEtSumEt = MVaMEt_It->sumEt();
    //KoMETs.MVaMEtNeuEM = MVaMEt_It->NeutralEMFraction();
    //KoMETs.MVaMEtNeuHad= MVaMEt_It->NeutralHadEtFraction();
    //KoMETs.MVaMEtChHad = MVaMEt_It->ChargedHadEtFraction();
    //KoMETs.MVaMEtChEM  = MVaMEt_It->ChargedEMEtFraction();
    //KoMETs.MVaMEtMu    = MVaMEt_It->MuonEtFraction();

    KoMETs.genMEtTrue_x =genMEtTrue_It->px();
    KoMETs.genMEtTrue_y =genMEtTrue_It->py();
    KoMETs.genMEtTrueSumEt = genMEtTrue_It->sumEt();
    //KoMETs.genMEtTrueNeuEM = genMEtTrue_It->NeutralEMFraction();
    KoMETs.genMEtTrueNeuHad= genMEtTrue_It->NeutralHadEtFraction();
    KoMETs.genMEtTrueChHad = genMEtTrue_It->ChargedHadEtFraction();
    KoMETs.genMEtTrueChEM  = genMEtTrue_It->ChargedEMEtFraction();
    KoMETs.genMEtTrueMu    = genMEtTrue_It->MuonEtFraction();

    KoMETs.genMEtCalo_x =genMEtCalo_It->px();
    KoMETs.genMEtCalo_y =genMEtCalo_It->py();
    KoMETs.genMEtCaloSumEt = genMEtCalo_It->sumEt();
    KoMETs.genMEtCaloNeuHad= genMEtCalo_It->NeutralHadEtFraction();
    KoMETs.genMEtCaloChHad = genMEtCalo_It->ChargedHadEtFraction();
    KoMETs.genMEtCaloChEM  = genMEtCalo_It->ChargedEMEtFraction();
    KoMETs.genMEtCaloMu    = genMEtCalo_It->MuonEtFraction();

    KoMETs.genMEtCaloAndNonPrompt_x=genMEtCaloAndNonPrompt_It->px();
    KoMETs.genMEtCaloAndNonPrompt_y=genMEtCaloAndNonPrompt_It->py();
    KoMETs.genMEtCaloAndNonPromptSumEt = genMEtCaloAndNonPrompt_It->sumEt();
    //KoMETs.genMEtCaloAndNonPromptNeuEM = genMEtCaloAndNonPrompt_It->NeutralEMFraction();
    KoMETs.genMEtCaloAndNonPromptNeuHad= genMEtCaloAndNonPrompt_It->NeutralHadEtFraction();
    KoMETs.genMEtCaloAndNonPromptChHad = genMEtCaloAndNonPrompt_It->ChargedHadEtFraction();
    KoMETs.genMEtCaloAndNonPromptChEM  = genMEtCaloAndNonPrompt_It->ChargedEMEtFraction();
    KoMETs.genMEtCaloAndNonPromptMu    = genMEtCaloAndNonPrompt_It->MuonEtFraction();

    h_MET->Fill(pfMEt_It->pt());
    //h_NoPU_MET->Fill(NoPuMEt_It->pt());
    //h_MVA_MET->Fill(MVaMEt_It->pt());
    //h_genMEtTrue_MET->Fill(genMEtTrue_It->pt());
    //h_genMEtCalo_MET->Fill(genMEtCalo_It->pt());
    //h_genMEtCaloAndNonPrompt_MET->Fill(genMEtCaloAndNonPrompt_It->pt());

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
}
DEFINE_FWK_MODULE(NtupleMaker);

