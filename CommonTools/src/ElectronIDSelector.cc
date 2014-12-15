#include "TerraNova5322/CommonTools/interface/ElectronIDSelector.h"

#include "DataFormats/RecoCandidate/interface/IsoDeposit.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositVetos.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositDirection.h"

//#include "DataFormats/MuonReco/interface/MuonSelectors.h"

#include <vector>
#include <iostream>

#include "Math/VectorUtil.h"
#include "TMath.h"

using namespace std;
using namespace reco;

ElectronIDSelector::ElectronIDSelector()
  : verbose_(false){
  push_back("pt",0);
  push_back("eta",0);
  push_back("dz",0);
  push_back("EcalGapCut",0);

}


void ElectronIDSelector::initialize( const edm::ParameterSet& ps ) {

  initialize(
	     ps.getParameter< double >("pt") ,
	     ps.getParameter< double >("eta"),
	     ps.getParameter< double >("dz"),
	     ps.getParameter< int >("EcalGapCut") 
	     );

  verbose_ = ps.getUntrackedParameter<bool>("verbose", false);
  if ( ps.exists("cutsToIgnore") )
    setIgnoredCuts( ps.getParameter<std::vector<std::string> >("cutsToIgnore") );
}

void ElectronIDSelector::initialize(
				 double pt,
				 double eta,
				 double dz,
				 int EcalGapCut
				 ){
  //Selector.h object
  set("pt",pt);
  set("eta",eta);
  set("dz",eta);
  set("EcalGapCut",EcalGapCut);
}

bool ElectronIDSelector::operator()( const pat::Electron & electron, pat::strbitset & ret ) {
  return eleIDSelection(electron, ret);
}

bool ElectronIDSelector::operator()( const pat::Electron & electron, const edm::Handle<reco::BeamSpot>& beamspot, pat::strbitset & ret ) {
  return operator()(electron,beamspot->position(),ret);
}

bool ElectronIDSelector::operator()( const pat::Electron & electron, const Point& position, pat::strbitset & ret ) {

  bool passedBeamSpotSelection = beamSpotSelection( electron, position, ret);
  bool passedEleIDSelection = eleIDSelection( electron, ret ); 
  return passedEleIDSelection && passedBeamSpotSelection;
}


bool ElectronIDSelector::eleIDSelection( const pat::Electron& electron, 
				pat::strbitset & ret)  {    

  if(verbose_) 
    cout<<"Selecting Pat electron : "<<electron.pt()<<endl;
 /************** 
  try{
  trkLayers = muon.track()->hitPattern().trackerLayersWithMeasurement();
  }
  catch(...){
  }
  *******************/

/***************************************
  double sumPtR03 = muon.isolationR03().sumPt;
  double emEtR03 = muon.isolationR03().emEt;
  double hadEtR03 = muon.isolationR03().hadEt;
  
  double relIso = (sumPtR03 + emEtR03 + hadEtR03)/muon.pt();
  
  if(ignoreCut("relIso") || relIso< cut("relIso", double() ) )
    passCut( ret, "relIso");
    ********************************/

  double pt = electron.pt();
  
  if(ignoreCut("pt") || pt > cut("pt", double() ) )
    passCut( ret, "pt");

  double eta = electron.superCluster()->eta();
  
  if(ignoreCut("eta") || fabs(eta) < cut("eta", double() ) )
    passCut( ret, "eta");

  if(ignoreCut("EcalGapCut") || fabs(eta) >= 1.566 || fabs(eta) <= 1.4442  )
    passCut( ret, "EcalGapCut");

  setIgnored( ret );
  
  if(verbose_) ret.print( cout );
  
  // return value not really useful, use strbitset instead
  return (bool)ret;
}


bool ElectronIDSelector::beamSpotSelection( const pat::Electron& electron, 
				const Point& position,
				pat::strbitset & ret)  {    

   
  if(verbose_) 
    cout<<"Selecting Pat electron : "<<electron.pt()<<endl;

  double dz = 9999.;


/*****************
    const reco::TrackRef& track = muon.track();        
    if(!track.isNull() && !calcDispFromGlobalTrack_){
      dxy = track->dxy(position);
      dz = track->dz(position);
    } 
    else{
      if(muon.isGlobalMuon()){
	const reco::TrackRef& muGlobalTrk = muon.globalTrack();        
	dxy = muGlobalTrk->dxy(position);
	dz = muGlobalTrk->dz(position);
      }    
    }
    *******************/

    //cout<<"dxy from globalTrack: "<<dxy<<" from dB: "<<muon.dB()<<endl;

  

  if(ignoreCut("dz") || fabs(dz) <= cut("dz", double() ) )
    passCut( ret, "dz");

  setIgnored( ret );
  
  //if(verbose_) ret.print( cout );
  return ret.test("dz");

}
