#include "FWCore/Framework/interface/MakerMacros.h"
#include "TerraNova/NtupleMaker/interface/mSUGRAAnalyzer.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/MET.h"
void mSUGRAAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  //cout<<"Channel: "<<Channel<<"#########################################"<<endl;
  //EvtPass = false;

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
  }

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

  //if(Channel == "Muon"){
  //iEvent.getByLabel(leptonLabel_,mu_hand);
  //}else if(Channel == "Electron"){
  //  iEvent.getByLabel(leptonLabel_,ele_hand);
  //}else{cout<<"What kind of a channel hur? "<<Channel<<endl;exit(-1);}

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

  iEvent.getByLabel(jetLabel_, Jets);
  if(PUJetIdDisc.label().size() != 0 && PUJetId.label().size() != 0)
  {
    iEvent.getByLabel(PUJetIdDisc, PUJetIdMVA);
    iEvent.getByLabel(PUJetId, PUJetIdFlag);
  }

  edm::Handle<reco::GenParticleCollection> genParticles_;
  iEvent.getByLabel(genParticlesLabel_,genParticles_);

  MEt.pfMEt_x    =pfMEt_It->px();
  MEt.pfMEt_y    =pfMEt_It->py();

  pfMEt4V    ->SetPxPyPzE(pfMEt_It->px(),pfMEt_It->py(),0,pfMEt_It->pt());


  MEt.NoPuMEt_x    =NoPuMEt_It->px();
  MEt.NoPuMEt_y    =NoPuMEt_It->py();

  MEt.MVaMEt_x     =MVaMEt_It->px();
  MEt.MVaMEt_y     =MVaMEt_It->py();

  MEt.genMEtTrue_x =genMEtTrue_It->px();
  MEt.genMEtTrue_y =genMEtTrue_It->py();
  MEt.genMEtTrueSumEt = genMEtTrue_It->sumEt();
  MEt.genMEtTrueNeuHad= genMEtTrue_It->NeutralHadEtFraction();
  MEt.genMEtTrueChHad = genMEtTrue_It->ChargedHadEtFraction();
  MEt.genMEtTrueChEM  = genMEtTrue_It->ChargedEMEtFraction();
  MEt.genMEtTrueMu    = genMEtTrue_It->MuonEtFraction();

  MEt.genMEtCalo_x =genMEtCalo_It->px();
  MEt.genMEtCalo_y =genMEtCalo_It->py();
  MEt.genMEtCaloSumEt = genMEtCalo_It->sumEt();
  MEt.genMEtCaloNeuHad= genMEtCalo_It->NeutralHadEtFraction();
  MEt.genMEtCaloChHad = genMEtCalo_It->ChargedHadEtFraction();
  MEt.genMEtCaloChEM  = genMEtCalo_It->ChargedEMEtFraction();
  MEt.genMEtCaloMu    = genMEtCalo_It->MuonEtFraction();

  MEt.genMEtCaloAndNonPrompt_x=genMEtCaloAndNonPrompt_It->px();
  MEt.genMEtCaloAndNonPrompt_y=genMEtCaloAndNonPrompt_It->py();
  MEt.genMEtCaloAndNonPromptSumEt = genMEtCaloAndNonPrompt_It->sumEt();
  MEt.genMEtCaloAndNonPromptNeuHad= genMEtCaloAndNonPrompt_It->NeutralHadEtFraction();
  MEt.genMEtCaloAndNonPromptChHad = genMEtCaloAndNonPrompt_It->ChargedHadEtFraction();
  MEt.genMEtCaloAndNonPromptChEM  = genMEtCaloAndNonPrompt_It->ChargedEMEtFraction();
  MEt.genMEtCaloAndNonPromptMu    = genMEtCaloAndNonPrompt_It->MuonEtFraction();

  h_MET->Fill(pfMEt_It->pt());
  //h_NoPU_MET->Fill(NoPuMEt_It->pt());
  //h_MVA_MET->Fill(MVaMEt_It->pt());
  //h_genMEtTrue_MET->Fill(genMEtTrue_It->pt());
  //h_genMEtCalo_MET->Fill(genMEtCalo_It->pt());
  //h_genMEtCaloAndNonPrompt_MET->Fill(genMEtCaloAndNonPrompt_It->pt());

  //cout<<"Channel: "<<Channel<<endl;

    //EventData.Channel = GenType::kMuon;
  //LoopJets(iEvent, iSetup);

  //ESHandle<SetupData> pSetup;
  //iSetup.get<SetupRecord>().get(pSetup);
  //if(EvtPass) tree->Fill();
  tree->Fill();
}
DEFINE_FWK_MODULE(mSUGRAAnalyzer);

