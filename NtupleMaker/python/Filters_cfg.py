
goodOfflinePrimaryVertices = cms.EDFilter("VertexSelector",
   src = cms.InputTag("offlinePrimaryVertices"),
   cut = cms.string("!isFake && ndof > 4 && abs(z) < 24 && position.Rho < 2"), # tracksSize() > 3 for the older cut
   filter = cms.bool(True),   # otherwise it won't filter the events, just produce an empty vertex collection.
)

noscraping = cms.EDFilter("FilterOutScraping",
   applyfilter = cms.untracked.bool(True),
   debugOn = cms.untracked.bool(False),
   numtrack = cms.untracked.uint32(10),
   thresh = cms.untracked.double(0.25)
)

from CommonTools.RecoAlgos.HBHENoiseFilter_cfi import *
HBHENoiseFilter.minNumIsolatedNoiseChannels = cms.int32(9999)
HBHENoiseFilter.minIsolatedNoiseSumE = cms.double(9999)
HBHENoiseFilter.minIsolatedNoiseSumEt = cms.double(9999)





