#include "KNUPhy/DataFormats/interface/WLeptNeuCand.h"

using namespace Ky;

WLeptNeuCand::WLeptNeuCand(
    const reco::Candidate::LorentzVector& lept,
    const reco::Candidate::LorentzVector& met,
    const double charge)
{
  lept_ = lept;    
  met_ = met;
  charge_ = charge;
  WCand_ = lept_ + met_;

  SetM();
  SetMt();
  SetAcop();

}
void WLeptNeuCand::SetM(){
  M_ = (lept_ + met_).M();
}
void WLeptNeuCand::SetMt()
{
  double ptSum = lept_.pt() + met_.pt();
  double mt = ptSum*ptSum -WCand_.px()*WCand_.px() - WCand_.py()*WCand_.py();
  Mt_ = (mt>0) ? sqrt(mt) : 0;
}
void WLeptNeuCand::SetAcop()
{
  //edm::LogVerbatim("WLeptNeuCand")<<"lept phi: "<<lept_.phi()<<" met phi: "<<met_.phi()"\n";
  lept_phi = lept_.phi();
  met_phi = met_.phi();
  double del_phi = lept_.phi() - met_.phi();
  if( del_phi < 0 ) del_phi = - del_phi;
  Acop_ = M_PI - del_phi;
}
