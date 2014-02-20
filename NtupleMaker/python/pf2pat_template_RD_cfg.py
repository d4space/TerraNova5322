import FWCore.ParameterSet.Config as cms

## MessageLogger
from FWCore.MessageLogger.MessageLogger_cfi import *
#process.load("Configuration.StandardSequences.Geometry_cff")
from Configuration.Geometry.GeometryIdeal_cff import *
from Configuration.StandardSequences.FrontierConditions_GlobalTag_cff import *
from Configuration.StandardSequences.MagneticField_cff import *


#from Configuration.PyReleaseValidation.autoCond import autoCond
#process.GlobalTag.globaltag = cms.string( autoCond[ 'startup' ] )

#PF2PAT
from PhysicsTools.PatAlgos.patSequences_cff import *

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

acceptedElectrons = cms.EDFilter("PATElectronSelector",
    src = cms.InputTag("selectedPatElectronsPFlow"),
    cut = cms.string("pt > 10 && abs(eta) < 3.0"),
    #cut = cms.string("pt > 20 && abs(eta) < 2.5"),
    #cut = cms.string("pt > 20 && abs(eta) < 2.5 && ecalDrivenSeed")
    filter = cms.bool(False),
)
allConversions = cms.EDProducer("PATConversionProducer",
    electronSource = cms.InputTag("acceptedElectrons")
    # this should be your last selected electron collection name
    )

acceptedGsfElectrons = cms.EDFilter("PATElectronSelector",
    src = cms.InputTag("selectedPatElectrons"),
    cut = cms.string("pt > 10 && abs(eta) < 3.0"),
    #cut = cms.string("pt > 20 && abs(eta) < 2.5"),
    #cut = cms.string("pt > 20 && abs(eta) < 2.5 && ecalDrivenSeed")
    filter = cms.bool(False),
)

patElectronFilter = cms.EDFilter("CandViewCountFilter",
    src = cms.InputTag('acceptedElectrons'),
    minNumber = cms.uint32(1)
)

acceptedMuons = cms.EDFilter("PATMuonSelector",
    src = cms.InputTag("selectedPatMuonsPFlow"),
    cut =cms.string("pt > 10 && abs(eta) < 2.5"),
    #cut =cms.string("pt > 15 && abs(eta) < 2.5"),
    filter = cms.bool(False),
)

patMuonFilter = cms.EDFilter("CandViewCountFilter",
  src = cms.InputTag('acceptedMuons'),
  minNumber = cms.uint32(1)
)

patLeptonFilter = cms.EDFilter("MultiLeptonCountFilter",
  leptons = cms.untracked.VInputTag('acceptedMuons','acceptedElectrons'),
  minCount = cms.untracked.uint32(0)
)

#Electron ID
#from RecoEgamma.ElectronIdentification.cutsInCategoriesElectronIdentificationV06_cfi import *
#from ElectroWeakAnalysis.WENu.simpleEleIdSequence_cff import *

#patElectrons.electronIDSources = cms.PSet(
#    #CiC
#    eidVeryLooseMC = cms.InputTag("eidVeryLooseMC"),
#    eidLooseMC = cms.InputTag("eidLooseMC"),
#    eidMediumMC = cms.InputTag("eidMediumMC"),
#    eidTightMC = cms.InputTag("eidTightMC"),
#    eidSuperTightMC = cms.InputTag("eidSuperTightMC"),
#    eidHyperTight1MC = cms.InputTag("eidHyperTight1MC"),
#    #VBTF 2010
#    simpleEleId95relIso= cms.InputTag("simpleEleId95relIso"),
#    simpleEleId90relIso= cms.InputTag("simpleEleId90relIso"),
#    simpleEleId85relIso= cms.InputTag("simpleEleId85relIso"),
#    simpleEleId80relIso= cms.InputTag("simpleEleId80relIso"),
#    simpleEleId70relIso= cms.InputTag("simpleEleId70relIso"),
#    simpleEleId60relIso= cms.InputTag("simpleEleId60relIso"),
#)

#patElectronIDs = cms.Sequence(process.simpleEleIdSequence)
#eidCiCSequence = cms.Sequence(
#    process.eidVeryLooseMC * process.eidLooseMC * process.eidMediumMC
#  * process.eidTightMC * process.eidSuperTightMC * process.eidHyperTight1MC
#)

from CommonTools.RecoAlgos.HBHENoiseFilter_cfi import *
HBHENoiseFilter.minNumIsolatedNoiseChannels = cms.int32(9999)
HBHENoiseFilter.minIsolatedNoiseSumE = cms.double(9999)
HBHENoiseFilter.minIsolatedNoiseSumEt = cms.double(9999)


##################################################################
from TerraNova.NtupleMaker.wHLTfilter_cff import *

nEventsTotal = cms.EDProducer("EventCountProducer")
nEventsNoscrap = cms.EDProducer("EventCountProducer")
nEventsHBHE = cms.EDProducer("EventCountProducer")
#EventsClean = cms.EDProducer("EventCountProducer")
nEventsHLT = cms.EDProducer("EventCountProducer")
nEventsFiltered = cms.EDProducer("EventCountProducer")



