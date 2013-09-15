#include "KNUPhy/DataFormats/interface/Lepton.h"

using namespace Ky; 
using namespace std;

Lepton::Lepton( const reco::Candidate::LorentzVector& p4, const int& charge  ) : LorentzVector(p4){

  charge_ = charge;
  pt_ = p4.pt(); 

}

void Lepton::setIsoDeposit( pat::IsolationKeys key, const pat::IsoDeposit *dep, reco::isodeposit::AbsVetos vetos) {
  assert( key == pat::PfChargedHadronIso ||
	  key == pat::PfNeutralHadronIso ||
	  key == pat::PfGammaIso         ||
	  key == pat::PfPUChargedHadronIso);

  if( key == pat::PfChargedHadronIso ) {
    chIso03_ = dep->depositAndCountWithin(0.3, vetos).first;//second is number of constituants
    chIso04_ = dep->depositAndCountWithin(0.4, vetos).first;
    chIso05_ = dep->depositAndCountWithin(0.5, vetos).first;
  }
  if( key == pat::PfNeutralHadronIso ) {
    nhIso03_ = dep->depositAndCountWithin(0.3, vetos).first;
    nhIso04_ = dep->depositAndCountWithin(0.4, vetos).first;
    nhIso05_ = dep->depositAndCountWithin(0.5, vetos).first;
  }
  if( key == pat::PfGammaIso ) {
    phIso03_ = dep->depositAndCountWithin(0.3, vetos).first;
    phIso04_ = dep->depositAndCountWithin(0.4, vetos).first;
    phIso05_ = dep->depositAndCountWithin(0.5, vetos).first;
  }
  if( key == pat::PfPUChargedHadronIso )
  {
    pcIso03_ = dep->depositAndCountWithin(0.3, vetos).first;
    pcIso04_ = dep->depositAndCountWithin(0.4, vetos).first;
    pcIso05_ = dep->depositAndCountWithin(0.5, vetos).first;
  }

}



