import FWCore.ParameterSet.Config as cms 
#PF2PAT
from PhysicsTools.PatAlgos.patSequences_cff import *


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
from TerraNova.CommonTools.eleSelectorPSet_cff import eleSelectorPSet
METsrcElectrons = cms.EDProducer(
    "KyElectronSelector",
    version = cms.untracked.int32( 13 ),# -1(no cut), 0(check cut, isocut pset), 1(WptCut) 13(medium pt 30) 14(medium pt 15)
    cut = cms.vstring("pt","eta","EcalGapCut"),
    electronLabel  = cms.InputTag("selectedPatElectronsPFlow"),
    beamSpotLabel = cms.InputTag("offlineBeamSpot"),
    vertexLabel = cms.InputTag('offlinePrimaryVertices'),
    rhoIsoLabel = cms.InputTag('kt6PFJets','rho'),
    conversionsInputTag = cms.InputTag("allConversions"),
    eleIdSelector = eleSelectorPSet,
    saveTree = cms.untracked.bool(False),
    )
acceptedMuons = cms.EDFilter("PATMuonSelector",
    src = cms.InputTag("selectedPatMuonsPFlow"),
    cut =cms.string("pt > 10 && abs(eta) < 2.5"),
    #cut =cms.string("pt > 15 && abs(eta) < 2.5"),
    filter = cms.bool(False),
)

acceptedMuonsFilter = cms.EDFilter("CandViewCountFilter",
  src = cms.InputTag('acceptedMuons'),
  minNumber = cms.uint32(1)
)

from TerraNova.CommonTools.muonSelectorPSet_cff import muonSelectorPSet
from TerraNova.CommonTools.muonIsoSelectorPSet_cff import muonIsoSelectorPSet
METsrcMuons = cms.EDProducer("KyMuonSelector",
    # 6(pt>10, tight, for DiMu) 7(pt>27, tight for SingleMu)
    version = cms.untracked.int32( 6 ),# -1(no cut) 0(check cut, isocut pset)
    cut = cms.vstring("pt"),
    isocut = cms.vstring(),
    muonLabel  = cms.InputTag("selectedPatMuonsPFlow"),
    beamSpotLabel = cms.InputTag("offlineBeamSpot"),
    muonIdSelector = muonSelectorPSet,
    muonIsoSelector = muonIsoSelectorPSet,
    saveTree = cms.untracked.bool(False),
    )
acceptedTaus = cms.EDFilter("PATTauSelector",
    src = cms.InputTag("selectedPatTausPFlow"),
    cut = cms.string("pt > 20 && abs(eta) < 2.3 && tauID('decayModeFinding')>0.5 && tauID('byMediumCombinedIsolationDeltaBetaCorr3Hits')>0.5"),
    #cut = cms.string("pt > 10 && abs(eta) < 3.0"),
#    filter = cms.bool(False),
)
METsrcTaus = cms.EDFilter("PATTauSelector",
    src = cms.InputTag("selectedPatTausPFlow"),
    cut = cms.string("pt > 20 && abs(eta) < 2.3 && tauID('decayModeFinding')>0.5 && tauID('byMediumCombinedIsolationDeltaBetaCorr3Hits')>0.5"),
    #cut = cms.string("pt > 10 && abs(eta) < 3.0"),
#    filter = cms.bool(False),
)


patLeptonFilter = cms.EDFilter("MultiLeptonCountFilter",
  leptons = cms.untracked.VInputTag('acceptedMuons','acceptedElectrons'),
  minCount = cms.untracked.uint32(0)
)
patMuEleTauFilter = cms.EDFilter("MultiObjectCountFilter",
  leptons = cms.untracked.VInputTag('acceptedMuons','acceptedElectrons','acceptedTaus'),
  minCount = cms.untracked.uint32(1)
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


##################################################################
from TerraNova.NtupleMaker.wHLTfilter_cff import *

nEventsTotal = cms.EDProducer("EventCountProducer")
nEventsNoscrap = cms.EDProducer("EventCountProducer")
nEventsHBHE = cms.EDProducer("EventCountProducer")
#EventsClean = cms.EDProducer("EventCountProducer")
nEventsHLT = cms.EDProducer("EventCountProducer")
nEventsFiltered = cms.EDProducer("EventCountProducer")


