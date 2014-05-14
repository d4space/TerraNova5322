#ifndef Ky_CommonTools_interface_JetIDSelector_h
#define Ky_CommonTools_interface_JetIDSelector_h

/**
   \class JetIDSelector    
   \brief    
*/
#include "FWCore/ParameterSet/interface/ProcessDesc.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/PythonParameterSet/interface/PythonProcessDesc.h"

#include "DataFormats/PatCandidates/interface/Jet.h"
#include "PhysicsTools/SelectorUtils/interface/Selector.h"
#include "DataFormats/Math/interface/Point3D.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositVetos.h"
#include "DataFormats/RecoCandidate/interface/IsoDeposit.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"

#include <vector>

using namespace std;

class JetIDSelector : public Selector<reco::Jet>  {

 public: // interface

  typedef reco::Jet ObjectType;
  typedef math::XYZPoint Point;

  JetIDSelector();
  
  void initialize( const edm::ParameterSet& ps );

void initialize(double pt,
		double eta,
		double dz,
		int EcalGapCut
		);
 
  bool operator()( const pat::Jet & jet, pat::strbitset & ret );
  bool operator()( const pat::Jet & jet, const Point& position, pat::strbitset & ret );

  bool eleIDSelection( const pat::Jet& jet, pat::strbitset & ret );

 private: // member variables
  
  bool      verbose_;
  bool      calcDispFromGlobalTrack_;
  
};

#endif
