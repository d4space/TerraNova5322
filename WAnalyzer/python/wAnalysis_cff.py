import FWCore.ParameterSet.Config as cms

process = cms.Process("wNTuple")

from KoSMP.CommonTools.countingSequences_cfi import *
from PhysicsTools.SelectorUtils.pfJetIDSelector_cfi import pfJetIDSelector
myJetId = pfJetIDSelector.clone()

from KoSMP.WAnalyzer.wLeptonSelector_cfi import *
from KoSMP.WAnalyzer.triggerFilterByRun_cfi import *
from KoSMP.WAnalyzer.wHLTfilter_cff import *
from KoSMP.CommonTools.PileUpWeight_cff import *
from KoSMP.CommonTools.JetEnergyScale_cfi import *

VertexFilter = cms.EDFilter('VertexFilter',
    vertexLabel =  cms.InputTag('offlinePrimaryVertices'),
    min = cms.untracked.int32(1),
    max = cms.untracked.int32(999),
)

GenZmassFilter = cms.EDFilter('GenZmassFilter',
    genParticlesLabel = cms.InputTag('genParticles'),
    applyFilter = cms.untracked.bool( False ),
    decayMode = cms.untracked.vint32(11, 13, 15),
    min = cms.untracked.int32(0),
    max = cms.untracked.int32(999),
)

GenWtransversemassFilter = cms.EDFilter('GenWtransversemassFilter',
    genParticlesLabel = cms.InputTag('genParticles'),
    applyFilter = cms.untracked.bool( False ),
    decayMode = cms.untracked.vint32(11, 13, 15),
    min = cms.untracked.int32(0),
    max = cms.untracked.int32(999),
)

WLeptonGenFilter = cms.EDFilter("GenParticleDecayFilter",
    applyFilter = cms.untracked.bool( False ),
    motherPdgId = cms.untracked.uint32(6),
    pdgId = cms.untracked.uint32(24),
    daughterPdgIds = cms.untracked.vuint32(11, 13, 15),
    minCount = cms.untracked.uint32(2),
)

patMuonFilter = cms.EDFilter("CandViewCountFilter",
    src = cms.InputTag('Muons'),
    minNumber = cms.uint32(1)
)

patElectronFilter = cms.EDFilter("CandViewCountFilter",
    src = cms.InputTag('Electrons'),
    minNumber = cms.uint32(1)
)

#patMuonFilterForMuEl = patMuonFilter.clone()
#patElectronFilterForMuEl = patElectronFilter.clone()
#patMuonFilterForMuEl.minNumber = 1
#patElectronFilterForMuEl.minNumber = 1

#patMuonFilterForMuJet = patMuonFilter.clone()
#patMuonFilterForMuJet.minNumber = 1
#patElectronFilterForElJet = patElectronFilter.clone()
#patElectronFilterForElJet.minNumber = 1

#topWLeptonGenFilterForLJ = topWLeptonGenFilter.clone()
#topWLeptonGenFilterForLJ.daughterPdgIds = 11,13
#topWLeptonGenFilterForLJ.minCount = 1

DYmmFilter = cms.EDFilter("ZmmFilter",
  muonLabel1 =  cms.InputTag('acceptedMuons'),
  muonLabel2 =  cms.InputTag('acceptedMuons'),
  min = cms.double(12),
  max = cms.double(99999),
)

#correctedPatJetsPFlow = cms.EDProducer('KoCorrectJetProducer',
#    src = cms.InputTag('selectedPatJetsPFlow'),
#    correctors = cms.vstring('ak5PFL2L3')
#)


WEleNeu = cms.EDFilter('wEleNeuFilter',
    TriggerResultsTag = cms.untracked.InputTag('TriggerResults','','HLT'),
    HLTTriggers = cms.untracked.vstring('HLT_Ele22_CaloIdL_CaloIsoVL'),
    #HLTTriggers = cms.untracked.vstring('HLT_Ele22_CaloIdL_CaloIsoVL','HLT_Ele27_WP80'),
    genParticlesLabel = cms.InputTag('genParticles'),
    Channel = cms.untracked.string('Electron'),
    leptonLabel1 =  cms.InputTag('Electrons'),
    leptonLabel2 =  cms.InputTag('Electrons'),
    metLabel =  cms.InputTag('patMETsPFlow'),
    #metLabel =  cms.InputTag('JetEnergyScale','patMETsPFlow'),
    jetLabel =  cms.InputTag('selectedPatJetsPFlow'),
    #jetLabel =  cms.InputTag('JetEnergyScale','selectedPatJetsPFlow'),
    vertexLabel = cms.untracked.InputTag('offlinePrimaryVertices'),
    #vertexLabel = cms.untracked.InputTag('goodOfflinePrimaryVertices'),
    useEventCounter = cms.bool( True ),
    filters = cms.untracked.vstring(
        'nEventsTotal',
        'nEventsClean',
        'nEventsHLT',
        'nEventsFiltered',
        'nEventsPatHLT',
    ),
    relIso1 = cms.untracked.double(0.17),
    relIso2 = cms.untracked.double(0.17),
    #bTagSets = bTagSets,
    PileUpRD = PuRD2012Low,
    PileUpMC = PuMC2012Low,
)

WMuNeu = cms.EDFilter('wMuNeuFilter',
    TriggerResultsTag = cms.untracked.InputTag('TriggerResults','','HLT'),
    HLTTriggers = cms.untracked.vstring('HLT_Mu15_eta2p1','HLT_IsoMu24_eta2p1'),
    genParticlesLabel = cms.InputTag('genParticles'),
    Channel = cms.untracked.string('Muon'),
    leptonLabel1 =  cms.InputTag('Muons'),
    leptonLabel2 =  cms.InputTag('Muons'),
    metLabel =  cms.InputTag('patMETsPFlow'),
    #metLabel =  cms.InputTag('JetEnergyScale','patMETsPFlow'),
    jetLabel =  cms.InputTag('selectedPatJetsPFlow'),
    #jetLabel =  cms.InputTag('JetEnergyScale','selectedPatJetsPFlow'),
    vertexLabel = cms.untracked.InputTag('offlinePrimaryVertices'),
    #vertexLabel = cms.untracked.InputTag('goodOfflinePrimaryVertices'),
    useEventCounter = cms.bool( True ),
    filters = cms.untracked.vstring(
        'nEventsTotal',
        'nEventsClean',
        'nEventsHLT',
        'nEventsFiltered',
        'nEventsPatHLT',
    ),
    #for jet cleaning overlapping with isolated epton within 0.4
    relIso1 = cms.untracked.double(0.20),
    relIso2 = cms.untracked.double(0.20),
    #bTagSets = bTagSets,
    PileUpRD = PuRD2012Low,
    PileUpMC = PuMC2012Low,
    #PileUpRD = PileUpRD2011,
    #PileUpMC = Fall11,
    #hahahahaha,
)

removeDuplicate = cms.EDFilter("RemoveDuplicate",
    applyFilter = cms.untracked.bool( True )
)

#ElectronAna = cms.EDAnalyzer(
#    "pfElectronAnalyzer",
#    ptcut = cms.untracked.double(20),
#    electronLabel  = cms.InputTag("acceptedElectrons"),
#    beamSpotLabel = cms.InputTag("offlineBeamSpot"),
#)

nEventsPatHLT = cms.EDProducer("EventCountProducer")

WMuNeuAnalysisMCSequence = cms.Sequence(
    hltHighLevelSingleMuLoPU*
    nEventsPatHLT*
#    topWLeptonGenFilter*
#    GenZmassFilter*
#    selectedPatJetsPFlow*
#    PUweight*
#    DYmmFilter*
    Muons*
    patMuonFilter*
#    JetEnergyScale*
    WMuNeu
#    mm
)

WMuNeuAnalysisRealDataSequence = cms.Sequence(
    hltHighLevelSingleMuRD*
#    muonTriggerFilterByRun*
    nEventsPatHLT*
    removeDuplicate*
#    DYmmFilter*
#    selectedPatJetsPFlow*
    Muons*
    patMuonFilter*
#    JetEnergyScale*
    WMuNeu
#    mm
)
WEleNeuAnalysisMCSequence = cms.Sequence(
    hltHighLevelSingleEleMC*
    nEventsPatHLT*
#    removeDuplicate*
#    WLeptonGenFilter*
#    GenZmassFilter*
##    selectedPatJetsPFlow*
##    PUweight*
##    ElectronAna*
    Electrons*
    patElectronFilter*
#    JetEnergyScale*
#    ElEl
    WEleNeu
#    ee
)

WEleNeuAnalysisRealDataSequence = cms.Sequence(
    hltHighLevelSingleEleRD*
#    electronTriggerFilterByRun*
    nEventsPatHLT*
    removeDuplicate*
#    selectedPatJetsPFlow*
#    ElectronAna*
    Electrons*
    patElectronFilter*
#    JetEnergyScale*
    WEleNeu
#    ee
)
