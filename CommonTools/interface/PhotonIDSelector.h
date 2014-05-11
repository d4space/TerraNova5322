#ifndef Ky_CommonTools_interface_PhotonIDSelector_h
#define Ky_CommonTools_interface_PhotonIDSelector_h

/**
   \class PhotonIDSelector    
   \brief    
*/
#include "FWCore/ParameterSet/interface/ProcessDesc.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/PythonParameterSet/interface/PythonProcessDesc.h"

#include "DataFormats/PatCandidates/interface/Photon.h"
#include "PhysicsTools/SelectorUtils/interface/Selector.h"
#include "DataFormats/Math/interface/Point3D.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositVetos.h"
#include "DataFormats/RecoCandidate/interface/IsoDeposit.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"

#include <vector>

using namespace std;

class PhotonIDSelector : public Selector<pat::Photon>  {

 public: // interface

  typedef pat::Photon ObjectType;
  typedef math::XYZPoint Point;

   
  PhotonIDSelector();
  
  /// initialize all parameters and cuts from a parameter set
  void initialize( const edm::ParameterSet& ps );
  
  /// initialize all parameters and cuts 


void initialize(double pt,
		double eta,
		double dz,
		int EcalGapCut
		);
 
  // selector if no beam-spot included
  bool operator()( const pat::Photon & photon, pat::strbitset & ret );
  // selector w/ beam-spot
 // bool operator()( const pat::Photon & photon, const edm::Handle<reco::BeamSpot>& beamSpot, pat::strbitset & ret );
  bool operator()( const pat::Photon & photon, const Point& position, pat::strbitset & ret );

  // beam-spot cut
 // bool beamSpotSelection( const pat::Photon & photon, const Point& position, pat::strbitset & ret  );
  // Photon ID criteria
  bool phoIDSelection( const pat::Photon& photon, pat::strbitset & ret );

 private: // member variables
  
  bool      verbose_;
  bool      calcDispFromGlobalTrack_;
  
};

#endif
