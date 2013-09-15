#ifndef Ky_WLeptNeuCand_H
#define Ky_WLeptNeuCand_H

#include "DataFormats/Candidate/interface/CandidateFwd.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/PatCandidates/interface/Lepton.h"
#include "TLorentzVector.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

namespace Ky{

  class WLeptNeuCand{
  public:
    WLeptNeuCand(){}
    virtual ~WLeptNeuCand(){}

    WLeptNeuCand(const reco::Candidate::LorentzVector& lept,
	const reco::Candidate::LorentzVector& met, const double charge);

    double M() const { return M_; }
    double Mt() const { return Mt_; }
    double pt() const { return WCand_.pt();}
    double px() const { return WCand_.px();}
    double py() const { return WCand_.py();}
    double pz() const { return WCand_.pz();}
    double phi() const { return WCand_.phi();}
    double eta() const { return WCand_.eta();}
    double Acop() const{ return Acop_;}
    double charge() const{return charge_;}
  private:

    void SetM();
    void SetMt();
    void SetAcop();

    reco::Candidate::LorentzVector lept_;
    reco::Candidate::LorentzVector met_;
    reco::Candidate::LorentzVector WCand_;

    double M_;
    double Mt_;
    double Pt;
    double Acop_;
    double charge_;
    double lept_phi;
    double met_phi;
  };
}
#endif
