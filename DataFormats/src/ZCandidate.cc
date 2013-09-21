#include "KoSMP/DataFormats/interface/ZCandidate.h"

using namespace Ky;
int ZCandidate::KalmanVtxFit(reco::TransientTrack tranTrk1, reco::TransientTrack tranTrk2)
{
  //reco::TransientTrack leptTransientTrk1(leptTrk1, B);
  //reco::TransientTrack leptTransientTrk2(leptTrk2, B);
  std::vector<reco::TransientTrack> diLeptTracks;
  diLeptTracks.push_back(tranTrk1);
  diLeptTracks.push_back(tranTrk2);
  KalmanVertexFitter KalmanFitterTrk(true);
  CachingVertex<5> vertexTrk;
  bool isVertexTrk(true);
  try{
    vertexTrk = KalmanFitterTrk.vertex(diLeptTracks);
  }
  catch( ... ){
  //catch( exception & err )
    //std::cout<<"KalmanFitter err"<<std::endl;
    isVertexTrk = false;
    return -1;
  }
  if( isVertexTrk && vertexTrk.isValid() )
  {
    diLeptVtxTrkProb_ = TMath::Prob(vertexTrk.totalChiSquared(),(int)vertexTrk.degreesOfFreedom());
    //std::cout<<"ZCand vtxProb: "<<vtxTrkProb_<<std::endl;
  }
  return 0;
}

double ZCandidate::deltaR() const{
 
  TLorentzVector lep1_;
  TLorentzVector lep2_;
 
  lep1_.SetPtEtaPhiM(leg1_.pt(), leg1_.eta(), leg1_.phi(), leg1_.M()); 
  lep2_.SetPtEtaPhiM(leg2_.pt(), leg2_.eta(), leg2_.phi(), leg2_.M()); 

  return lep1_.DeltaR(lep2_);

}

double ZCandidate::deltaPhi() const{

  TLorentzVector lep1_;
  TLorentzVector lep2_;

  lep1_.SetPtEtaPhiM(leg1_.pt(), leg1_.eta(), leg1_.phi(), leg1_.M());  
  lep2_.SetPtEtaPhiM(leg2_.pt(), leg2_.eta(), leg2_.phi(), leg2_.M());  

  return lep1_.DeltaPhi(lep2_);

}

