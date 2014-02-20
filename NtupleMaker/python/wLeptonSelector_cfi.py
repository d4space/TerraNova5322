import FWCore.ParameterSet.Config as cms

from TerraNova.CommonTools.muonSelectorPSet_cff import muonSelectorPSet
from TerraNova.CommonTools.eleSelectorPSet_cff import eleSelectorPSet
from TerraNova.CommonTools.muonIsoSelectorPSet_cff import muonIsoSelectorPSet
muonId = muonSelectorPSet.clone()
muonId.verbose = False 
muonId.dB = 0.2
muonId.eta = 2.4
muonId.pt = 10

Muons = cms.EDProducer(
    "KyMuonSelector",
    #
    version = cms.untracked.int32( 0 ),# -1(no cut) 0(check cut, isocut pset) 
    #version = cms.untracked.int32( 6 ),# -1(no cut) 0(check cut, isocut pset) 
    cut = cms.vstring("pt"),
    #cut = cms.vstring("pt","eta","dB","WMuNu"),
    isocut = cms.vstring(),
    muonLabel  = cms.InputTag("acceptedMuons"),
    beamSpotLabel = cms.InputTag("offlineBeamSpot"),
    muonIdSelector = muonId,
    muonIsoSelector = muonIsoSelectorPSet,

)

Electrons = cms.EDProducer(
    "KyElectronSelector",
    version = cms.untracked.int32( 0 ),# -1(no cut) 0(check cut, isocut pset)
    #version = cms.untracked.int32( 5 ),# 10 = MVA, 5 = WP90?
    cut = cms.vstring("pt","eta","EcalGapCut"),
    electronLabel  = cms.InputTag("acceptedElectrons"),
    beamSpotLabel = cms.InputTag("offlineBeamSpot"),
    vertexLabel = cms.InputTag('offlinePrimaryVertices'),
    rhoIsoLabel = cms.InputTag('kt6PFJets','rho'),
    #rhoIsoLabel = cms.InputTag('kt6PFJetsForIsolation','rho'),
    #conversionsInputTag = cms.InputTag("patConversions"),
    conversionsInputTag = cms.InputTag("allConversions"),
    eleIdSelector = eleSelectorPSet,
#eidHyperTight1MC eidLooseMC eidMediumMC eidSuperTightMC eidTightMC simpleEleId60relIso 70,80,85,95 pf_evspi pfevsmu
    #eidName = cms.untracked.string("eidTightMC"),
    #eidName = cms.untracked.string("eidTightMC"),
    #eidBitMask = cms.untracked.int32(5), # = 101, ID and cms.Conversion
    #saveTree = cms.untracked.bool(False),
    saveTree = cms.untracked.bool(True),
)

