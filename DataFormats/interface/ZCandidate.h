#ifndef Ky_ZCandidate_H
#define Ky_ZCandidate_H

#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "DataFormats/Candidate/interface/CandidateFwd.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/PatCandidates/interface/Lepton.h"

#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"
#include "DataFormats/Candidate/interface/VertexCompositeCandidate.h"
#include "DataFormats/Candidate/interface/VertexCompositeCandidateFwd.h"
#include "RecoVertex/KalmanVertexFit/interface/KalmanVertexFitter.h"
#include "RecoVertex/VertexTools/interface/InvariantMassFromVertex.h"


#include "KNUPhy/DataFormats/interface/Lepton.h"
#include "TLorentzVector.h"

namespace Ky{

  class ZCandidate{
  public:
    ZCandidate(){}
    virtual ~ZCandidate(){}

    ZCandidate(const Ky::Lepton& leg1, const Ky::Lepton& leg2) {
      ZCand_ = leg1+leg2;
      leg1_ = leg1;
      leg2_ = leg2;
      mass_ = ZCand_.M(); 
      phi_ = ZCand_.phi(); 
      eta_ = ZCand_.eta(); 
      pt_ = ZCand_.pt(); 
      px_ = ZCand_.px(); 
      py_ = ZCand_.py(); 
      pz_ = ZCand_.pz(); 
      sign_ = leg1.charge()+leg2.charge();
      diLeptVtxTrkProb_= -9999;

    }

    ZCandidate(const reco::Candidate::LorentzVector& leg1, const reco::Candidate::LorentzVector& leg2, const double& sign) {
      ZCand_ = leg1+leg2;
      lv1_= leg1 ;
      lv2_= leg2 ;
      mass_ = ZCand_.M();
      phi_ = ZCand_.phi(); 
      eta_ = ZCand_.eta(); 
      pt_ = ZCand_.pt(); 
      px_ = ZCand_.px(); 
      py_ = ZCand_.py(); 
      pz_ = ZCand_.pz(); 
      sign_ = sign;
      diLeptVtxTrkProb_= -9999;
    }

    const Ky::Lepton& leg1() const { return leg1_; }
    const Ky::Lepton& leg2() const { return leg2_; }
    const reco::Candidate::LorentzVector& lv1() const { return lv1_;}
    const reco::Candidate::LorentzVector& lv2() const { return lv2_;}

    double mass() const { return mass_; }
    double phi() const { return phi_; }
    double eta() const { return eta_; }
    double pt() const { return pt_; }
    double px() const { return px_; }
    double py() const { return py_; }
    double pz() const { return pz_; }
    double sign() const { return sign_; }
    double deltaR() const; 
    double deltaPhi() const;
    int KalmanVtxFit(reco::TransientTrack leptTrk1, reco::TransientTrack leptTrk2);
    double diLeptVtxProb() {return diLeptVtxTrkProb_;}

  private:

    Ky::Lepton leg1_;
    Ky::Lepton leg2_;
    reco::Candidate::LorentzVector lv1_;
    reco::Candidate::LorentzVector lv2_;
    reco::Candidate::LorentzVector ZCand_;

    double diLeptVtxTrkProb_;
    double mass_;
    double phi_;
    double eta_;
    double pt_;
    double px_;
    double py_;
    double pz_;
    double sign_;
  };
}
#endif
