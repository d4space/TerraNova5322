import FWCore.ParameterSet.Config as cms
 
photonSelectorPSet = cms.PSet(

    # turn me to True to see the results of the muon selection:
    verbose = cms.untracked.bool( False ),

    #kinematic cuts
    pt = cms.double(10.),
    #pt = cms.double(23.),
    dz = cms.double(0.2),
    #fiducialcuts
    #eta = cms.double(2.5),
    eta = cms.double(3.0),
    EcalGapCut = cms.int32(1),

    )


