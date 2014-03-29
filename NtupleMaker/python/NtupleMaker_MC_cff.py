
from TrackingTools.TransientTrack.TransientTrackBuilder_cfi import *


from TerraNova.CommonTools.countingSequences_cfi import *
from PhysicsTools.SelectorUtils.pfJetIDSelector_cfi import pfJetIDSelector
myJetId = pfJetIDSelector.clone()

from TerraNova.NtupleMaker.wLeptonSelector_cfi import *
from TerraNova.NtupleMaker.triggerFilterByRun_cfi import *
from TerraNova.NtupleMaker.wHLTfilter_cff import *
from TerraNova.CommonTools.PileUpWeight_cff import *
from TerraNova.CommonTools.JetEnergyScale_cfi import *

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

MuonsFilter = cms.EDFilter("CandViewCountFilter",
    src = cms.InputTag('Muons'),
    minNumber = cms.uint32(1)
)

ElectronsFilter = cms.EDFilter("CandViewCountFilter",
    src = cms.InputTag('Electrons'),
    minNumber = cms.uint32(1)
)

#MuonsFilterForMuEl = patMuonFilter.clone()
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


WEleNeu = cms.EDAnalyzer('WNtupleMaker',
    TriggerResultsTag = cms.untracked.InputTag('TriggerResults','','HLT'),
    #HLTTriggers = cms.untracked.vstring('HLT_Ele22_CaloIdL_CaloIsoVL'),# To make the Ntupe tree happy
    HLTTriggers = cms.untracked.vstring('HLT_Ele22_CaloIdL_CaloIsoVL','HLT_Ele27_WP80','HLT_Mu15_eta2p1'),
    genParticlesLabel = cms.InputTag('genParticles'),
    Channel = cms.untracked.string('Electron'),
    leptonLabel1 =  cms.InputTag('Electrons'),
    leptonLabel2 =  cms.InputTag('Electrons'),
    pfMEtLabel =  cms.InputTag('patMETsPFlow'),
    #metLabel =  cms.InputTag('JetEnergyScale','patMETsPFlow'),
    noPuMEtLabel =  cms.InputTag('noPileUpPFMEt'),
    MVAMEtLabel =  cms.InputTag('pfMEtMVA'),
    genMEtTrueLabel =  cms.InputTag('genMetTrue'),
    genMEtCaloLabel =  cms.InputTag('genMetCalo'),
    genMEtCaloAndNonPromptLabel =  cms.InputTag('genMetCaloAndNonPrompt'),
    jetLabel =  cms.InputTag('selectedPatJetsPFlow'),
    #jetLabel =  cms.InputTag('JetEnergyScale','selectedPatJetsPFlow'),
    vertexLabel = cms.untracked.InputTag('offlinePrimaryVertices'),
    #vertexLabel = cms.untracked.InputTag('goodOfflinePrimaryVertices'),
    beamSpotInputTag = cms.InputTag("offlineBeamSpot"),
    rhoIsoInputTag = cms.InputTag('kt6PFJets','rho'),
    EAtarget = cms.string('EleEAData2012'), #EleEANoCorr, EleEAData2011, EleEASummer11MC,EleEAFall11MC, EleEAData2012 
    #rhoIsoInputTag = cms.InputTag('kt6PFJetsForIsolation','rho'),
    conversionsInputTag = cms.InputTag("allConversions"),
    useEventCounter = cms.bool( True ),
    filters = cms.untracked.vstring(
        'nEventsTotal',
        'nEventsNoscrap',
        'nEventsHBHE',
#        'nEventsClean',
        'nEventsHLT',
        'nEventsFiltered',
        'nEventsPatHLT',
    ),
    relIso1 = cms.untracked.double(0.17),
    relIso2 = cms.untracked.double(0.17),
    #bTagSets = bTagSets,
    #PileUpRD = PuRD2012Low,
    PileUpRD = PuRD2012HighPUBin60,
    #PileUpMC = PuMC2012S8Bin60,
    PileUpMC = PuMC2012S10Bin60,

    useL1Selector = cms.bool( True ), #for WP80
    L1Select = cms.untracked.string('L1_SingleEG22')

)
ZElEl = cms.EDAnalyzer('ZNtupleMaker',
    TriggerResultsTag = cms.untracked.InputTag('TriggerResults','','HLT'),
    #HLTTriggers = cms.untracked.vstring('HLT_Ele22_CaloIdL_CaloIsoVL'),# To make the Ntupe tree happy
    HLTTriggers = cms.untracked.vstring('HLT_Ele22_CaloIdL_CaloIsoVL','HLT_Ele27_WP80','HLT_Mu15_eta2p1'),
    genParticlesLabel = cms.InputTag('genParticles'),
    Channel = cms.untracked.string('Electron'),
    leptonLabel1 =  cms.InputTag('Electrons'),
    leptonLabel2 =  cms.InputTag('Electrons'),
    pfMEtLabel =  cms.InputTag('patMETsPFlow'),
    #metLabel =  cms.InputTag('JetEnergyScale','patMETsPFlow'),
    noPuMEtLabel =  cms.InputTag('noPileUpPFMEt'),
    MVAMEtLabel =  cms.InputTag('pfMEtMVA'),
    genMEtTrueLabel =  cms.InputTag('genMetTrue'),
    genMEtCaloLabel =  cms.InputTag('genMetCalo'),
    genMEtCaloAndNonPromptLabel =  cms.InputTag('genMetCaloAndNonPrompt'),
    jetLabel =  cms.InputTag('selectedPatJetsPFlow'),
    #jetLabel =  cms.InputTag('JetEnergyScale','selectedPatJetsPFlow'),
    vertexLabel = cms.untracked.InputTag('offlinePrimaryVertices'),
    #vertexLabel = cms.untracked.InputTag('goodOfflinePrimaryVertices'),
    beamSpotInputTag = cms.InputTag("offlineBeamSpot"),
    rhoIsoInputTag = cms.InputTag('kt6PFJets','rho'),
    EAtarget = cms.string('EleEAData2012'), #EleEANoCorr, EleEAData2011, EleEASummer11MC,EleEAFall11MC, EleEAData2012 
    #rhoIsoInputTag = cms.InputTag('kt6PFJetsForIsolation','rho'),
    conversionsInputTag = cms.InputTag("allConversions"),
    useEventCounter = cms.bool( True ),
    filters = cms.untracked.vstring(
        'nEventsTotal',
        'nEventsNoscrap',
        'nEventsHBHE',
#        'nEventsClean',
        'nEventsHLT',
        'nEventsFiltered',
        'nEventsPatHLT',
    ),
    relIso1 = cms.untracked.double(0.17),
    relIso2 = cms.untracked.double(0.17),
    #bTagSets = bTagSets,
    #PileUpRD = PuRD2012Low,
    PileUpRD = PuRD2012HighPUBin60,
    #PileUpMC = PuMC2012S8Bin60,
    PileUpMC = PuMC2012S10Bin60,

    useL1Selector = cms.bool( True ), #for WP80
    L1Select = cms.untracked.string('L1_SingleEG22')

)

WMuNeu = cms.EDAnalyzer('WNtupleMaker',
    TriggerResultsTag = cms.untracked.InputTag('TriggerResults','','HLT'),
    #HLTTriggers = cms.untracked.vstring('HLT_Mu15_eta2p1'), #To make the Ntuple tree happy
    HLTTriggers = cms.untracked.vstring('HLT_Ele22_CaloIdL_CaloIsoVL','HLT_Ele27_WP80','HLT_Mu15_eta2p1'),
    genParticlesLabel = cms.InputTag('genParticles'),
    Channel = cms.untracked.string('Muon'),
    leptonLabel1 =  cms.InputTag('Muons'),
    leptonLabel2 =  cms.InputTag('Muons'),
    pfMEtLabel =  cms.InputTag('patMETsPFlow'),
    #metLabel =  cms.InputTag('JetEnergyScale','patMETsPFlow'),
    noPuMEtLabel =  cms.InputTag('noPileUpPFMEt'),
    MVAMEtLabel =  cms.InputTag('pfMEtMVA'),
    genMEtTrueLabel =  cms.InputTag('genMetTrue'),
    genMEtCaloLabel =  cms.InputTag('genMetCalo'),
    genMEtCaloAndNonPromptLabel =  cms.InputTag('genMetCaloAndNonPrompt'),
    jetLabel =  cms.InputTag('selectedPatJetsPFlow'),
    #jetLabel =  cms.InputTag('JetEnergyScale','selectedPatJetsPFlow'),
    vertexLabel = cms.untracked.InputTag('offlinePrimaryVertices'),
    #vertexLabel = cms.untracked.InputTag('goodOfflinePrimaryVertices'),
    beamSpotInputTag = cms.InputTag("offlineBeamSpot"),
    rhoIsoInputTag = cms.InputTag('kt6PFJets','rho'),
    EAtarget = cms.string('EleEAData2012'), #EleEANoCorr, EleEAData2011, EleEASummer11MC,EleEAFall11MC, EleEAData2012 
    #rhoIsoInputTag = cms.InputTag('kt6PFJetsForIsolation','rho'),
    conversionsInputTag = cms.InputTag("allConversions"),
    useEventCounter = cms.bool( True ),
    filters = cms.untracked.vstring(
        'nEventsTotal',
        'nEventsNoscrap',
        'nEventsHBHE',
#        'nEventsClean',
        'nEventsHLT', 
        'nEventsFiltered',
        'nEventsPatHLT',
    ),
    #for jet cleaning overlapping with isolated epton within 0.4
    relIso1 = cms.untracked.double(0.20),
    relIso2 = cms.untracked.double(0.20),
    #bTagSets = bTagSets,
    #PileUpRD = PuRD2012Low,
    PileUpRD = PuRD2012LowBin60,
    PileUpMC = PuMC2012S8Bin60,
    #PileUpMC = PuMC2012S7Bin60,

    useL1Selector = cms.bool( False ), #for Electron WP80
    L1Select = cms.untracked.string('L1_SingleEG22')
)
WZ3LNu = cms.EDAnalyzer('WZNtupleMaker',
    TriggerResultsTag = cms.untracked.InputTag('TriggerResults','','HLT'),
    #HLTTriggers = cms.untracked.vstring('HLT_Mu15_eta2p1'), #To make the Ntuple tree happy
    HLTTriggers = cms.untracked.vstring('HLT_Ele22_CaloIdL_CaloIsoVL','HLT_Ele27_WP80','HLT_Mu15_eta2p1'),
    genParticlesLabel = cms.InputTag('genParticles'),
    Channel = cms.untracked.string('Muon'),
    MuonLabel =  cms.InputTag('Muons'),
    ElectronLabel =  cms.InputTag('Electrons'),
    TauLabel =  cms.InputTag('acceptedTaus'),
    pfMEtLabel =  cms.InputTag('patMETsPFlow'),
    #metLabel =  cms.InputTag('JetEnergyScale','patMETsPFlow'),
    noPuMEtLabel =  cms.InputTag('noPileUpPFMEt'),
    MVAMEtLabel =  cms.InputTag('pfMEtMVA'),
    genMEtTrueLabel =  cms.InputTag('genMetTrue'),
    genMEtCaloLabel =  cms.InputTag('genMetCalo'),
    genMEtCaloAndNonPromptLabel =  cms.InputTag('genMetCaloAndNonPrompt'),
    jetLabel =  cms.InputTag('selectedPatJetsPFlow'),
    #jetLabel =  cms.InputTag('JetEnergyScale','selectedPatJetsPFlow'),
    vertexLabel = cms.untracked.InputTag('offlinePrimaryVertices'),
    #vertexLabel = cms.untracked.InputTag('goodOfflinePrimaryVertices'),
    beamSpotInputTag = cms.InputTag("offlineBeamSpot"),
    rhoIsoInputTag = cms.InputTag('kt6PFJets','rho'),
    EAtarget = cms.string('EleEAData2012'), #EleEANoCorr, EleEAData2011, EleEASummer11MC,EleEAFall11MC, EleEAData2012 
    #rhoIsoInputTag = cms.InputTag('kt6PFJetsForIsolation','rho'),
    conversionsInputTag = cms.InputTag("allConversions"),
    useEventCounter = cms.bool( True ),
    filters = cms.untracked.vstring(
        'nEventsTotal',
        'nEventsNoscrap',
        'nEventsHBHE',
#        'nEventsClean',
        'nEventsHLT', 
        'nEventsFiltered',
        'nEventsPatHLT',
    ),
    #for jet cleaning overlapping with isolated epton within 0.4
    relIso1 = cms.untracked.double(0.20),
    relIso2 = cms.untracked.double(0.20),
    #bTagSets = bTagSets,
    #PileUpRD = PuRD2012Low,
    PileUpRD = PuRD2012LowBin60,
    PileUpMC = PuMC2012S8Bin60,
    #PileUpMC = PuMC2012S7Bin60,

    useL1Selector = cms.bool( False ), #for Electron WP80
    L1Select = cms.untracked.string('L1_SingleEG22')
)
WW = cms.EDAnalyzer('WWNtupleMaker',
    TriggerResultsTag = cms.untracked.InputTag('TriggerResults','','HLT'),
    #HLTTriggers = cms.untracked.vstring('HLT_Mu15_eta2p1'), #To make the Ntuple tree happy
    HLTTriggers = cms.untracked.vstring('HLT_Ele22_CaloIdL_CaloIsoVL','HLT_Ele27_WP80','HLT_Mu15_eta2p1'),
    genParticlesLabel = cms.InputTag('genParticles'),
    Channel = cms.untracked.string('Muon'),
    leptonLabel1 =  cms.InputTag('Muons'),
    leptonLabel2 =  cms.InputTag('Electrons'),
    leptonLabel3 =  cms.InputTag('acceptedTaus'),
    pfMEtLabel =  cms.InputTag('patMETsPFlow'),
    #metLabel =  cms.InputTag('JetEnergyScale','patMETsPFlow'),
    noPuMEtLabel =  cms.InputTag('noPileUpPFMEt'),
    MVAMEtLabel =  cms.InputTag('pfMEtMVA'),
    genMEtTrueLabel =  cms.InputTag('genMetTrue'),
    genMEtCaloLabel =  cms.InputTag('genMetCalo'),
    genMEtCaloAndNonPromptLabel =  cms.InputTag('genMetCaloAndNonPrompt'),
    jetLabel =  cms.InputTag('selectedPatJetsPFlow'),
    #jetLabel =  cms.InputTag('JetEnergyScale','selectedPatJetsPFlow'),
    vertexLabel = cms.untracked.InputTag('offlinePrimaryVertices'),
    #vertexLabel = cms.untracked.InputTag('goodOfflinePrimaryVertices'),
    beamSpotInputTag = cms.InputTag("offlineBeamSpot"),
    rhoIsoInputTag = cms.InputTag('kt6PFJets','rho'),
    EAtarget = cms.string('EleEAData2012'), #EleEANoCorr, EleEAData2011, EleEASummer11MC,EleEAFall11MC, EleEAData2012 
    #rhoIsoInputTag = cms.InputTag('kt6PFJetsForIsolation','rho'),
    conversionsInputTag = cms.InputTag("allConversions"),
    useEventCounter = cms.bool( True ),
    filters = cms.untracked.vstring(
        'nEventsTotal',
        'nEventsNoscrap',
        'nEventsHBHE',
#        'nEventsClean',
        'nEventsHLT', 
        'nEventsFiltered',
        'nEventsPatHLT',
    ),
    #for jet cleaning overlapping with isolated epton within 0.4
    relIso1 = cms.untracked.double(0.20),
    relIso2 = cms.untracked.double(0.20),
    #bTagSets = bTagSets,
    #PileUpRD = PuRD2012Low,
    PileUpRD = PuRD2012LowBin60,
    PileUpMC = PuMC2012S8Bin60,
    #PileUpMC = PuMC2012S7Bin60,

    useL1Selector = cms.bool( False ), #for Electron WP80
    L1Select = cms.untracked.string('L1_SingleEG22')
)
ZMuMu = cms.EDAnalyzer('ZNtupleMaker',
    TriggerResultsTag = cms.untracked.InputTag('TriggerResults','','HLT'),
    #HLTTriggers = cms.untracked.vstring('HLT_Mu15_eta2p1'), #To make the Ntuple tree happy
    HLTTriggers = cms.untracked.vstring('HLT_Ele22_CaloIdL_CaloIsoVL','HLT_Ele27_WP80','HLT_Mu15_eta2p1'),
    genParticlesLabel = cms.InputTag('genParticles'),
    Channel = cms.untracked.string('Muon'),
    leptonLabel1 =  cms.InputTag('Muons'),
    leptonLabel2 =  cms.InputTag('Muons'),
    pfMEtLabel =  cms.InputTag('patMETsPFlow'),
    #metLabel =  cms.InputTag('JetEnergyScale','patMETsPFlow'),
    noPuMEtLabel =  cms.InputTag('noPileUpPFMEt'),
    MVAMEtLabel =  cms.InputTag('pfMEtMVA'),
    genMEtTrueLabel =  cms.InputTag('genMetTrue'),
    genMEtCaloLabel =  cms.InputTag('genMetCalo'),
    genMEtCaloAndNonPromptLabel =  cms.InputTag('genMetCaloAndNonPrompt'),
    jetLabel =  cms.InputTag('selectedPatJetsPFlow'),
    #jetLabel =  cms.InputTag('JetEnergyScale','selectedPatJetsPFlow'),
    vertexLabel = cms.untracked.InputTag('offlinePrimaryVertices'),
    #vertexLabel = cms.untracked.InputTag('goodOfflinePrimaryVertices'),
    beamSpotInputTag = cms.InputTag("offlineBeamSpot"),
    rhoIsoInputTag = cms.InputTag('kt6PFJets','rho'),
    EAtarget = cms.string('EleEAData2012'), #EleEANoCorr, EleEAData2011, EleEASummer11MC,EleEAFall11MC, EleEAData2012 
    #rhoIsoInputTag = cms.InputTag('kt6PFJetsForIsolation','rho'),
    conversionsInputTag = cms.InputTag("allConversions"),
    useEventCounter = cms.bool( True ),
    filters = cms.untracked.vstring(
        'nEventsTotal',
        'nEventsNoscrap',
        'nEventsHBHE',
#        'nEventsClean',
        'nEventsHLT', 
        'nEventsFiltered',
        'nEventsPatHLT',
    ),
    #for jet cleaning overlapping with isolated epton within 0.4
    relIso1 = cms.untracked.double(0.20),
    relIso2 = cms.untracked.double(0.20),
    #bTagSets = bTagSets,
    #PileUpRD = PuRD2012Low,
    PileUpRD = PuRD2012LowBin60,
    PileUpMC = PuMC2012S8Bin60,
    #PileUpMC = PuMC2012S7Bin60,

    useL1Selector = cms.bool( False ), #for Electron WP80
    L1Select = cms.untracked.string('L1_SingleEG22')
)
ZZ4L = cms.EDAnalyzer('ZZNtupleMaker',
    TriggerResultsTag = cms.untracked.InputTag('TriggerResults','','HLT'),
    #HLTTriggers = cms.untracked.vstring('HLT_Mu15_eta2p1'), #To make the Ntuple tree happy
    HLTTriggers = cms.untracked.vstring('HLT_Ele22_CaloIdL_CaloIsoVL','HLT_Ele27_WP80','HLT_Mu15_eta2p1'),
    genParticlesLabel = cms.InputTag('genParticles'),
    Channel = cms.untracked.string('Muon'),
    leptonLabel1 =  cms.InputTag('Muons'),
    leptonLabel2 =  cms.InputTag('Electrons'),
    pfMEtLabel =  cms.InputTag('patMETsPFlow'),
    #metLabel =  cms.InputTag('JetEnergyScale','patMETsPFlow'),
    noPuMEtLabel =  cms.InputTag('noPileUpPFMEt'),
    MVAMEtLabel =  cms.InputTag('pfMEtMVA'),
    genMEtTrueLabel =  cms.InputTag('genMetTrue'),
    genMEtCaloLabel =  cms.InputTag('genMetCalo'),
    genMEtCaloAndNonPromptLabel =  cms.InputTag('genMetCaloAndNonPrompt'),
    jetLabel =  cms.InputTag('selectedPatJetsPFlow'),
    #jetLabel =  cms.InputTag('JetEnergyScale','selectedPatJetsPFlow'),
    vertexLabel = cms.untracked.InputTag('offlinePrimaryVertices'),
    #vertexLabel = cms.untracked.InputTag('goodOfflinePrimaryVertices'),
    beamSpotInputTag = cms.InputTag("offlineBeamSpot"),
    rhoIsoInputTag = cms.InputTag('kt6PFJets','rho'),
    EAtarget = cms.string('EleEAData2012'), #EleEANoCorr, EleEAData2011, EleEASummer11MC,EleEAFall11MC, EleEAData2012 
    #rhoIsoInputTag = cms.InputTag('kt6PFJetsForIsolation','rho'),
    conversionsInputTag = cms.InputTag("allConversions"),
    useEventCounter = cms.bool( True ),
    filters = cms.untracked.vstring(
        'nEventsTotal',
        'nEventsNoscrap',
        'nEventsHBHE',
#        'nEventsClean',
        'nEventsHLT', 
        'nEventsFiltered',
        'nEventsPatHLT',
    ),
    #for jet cleaning overlapping with isolated epton within 0.4
    relIso1 = cms.untracked.double(0.20),
    relIso2 = cms.untracked.double(0.20),
    #bTagSets = bTagSets,
    #PileUpRD = PuRD2012Low,
    PileUpRD = PuRD2012LowBin60,
    PileUpMC = PuMC2012S8Bin60,
    #PileUpMC = PuMC2012S7Bin60,

    useL1Selector = cms.bool( False ), #for Electron WP80
    L1Select = cms.untracked.string('L1_SingleEG22')
)

WTauNeu = cms.EDAnalyzer('WNtupleMaker',
    TriggerResultsTag = cms.untracked.InputTag('TriggerResults','','HLT'),
    #HLTTriggers = cms.untracked.vstring('HLT_Mu15_eta2p1'), #To make the Ntuple tree happy
    HLTTriggers = cms.untracked.vstring('HLT_Ele22_CaloIdL_CaloIsoVL','HLT_Ele27_WP80','HLT_Mu15_eta2p1'),
    genParticlesLabel = cms.InputTag('genParticles'),
    Channel = cms.untracked.string('Tau'),
    leptonLabel1 =  cms.InputTag('acceptedTaus'),
    leptonLabel2 =  cms.InputTag('acceptedTaus'),
    pfMEtLabel =  cms.InputTag('patMETsPFlow'),
    #metLabel =  cms.InputTag('JetEnergyScale','patMETsPFlow'),
    noPuMEtLabel =  cms.InputTag('noPileUpPFMEt'),
    MVAMEtLabel =  cms.InputTag('pfMEtMVA'),
    genMEtTrueLabel =  cms.InputTag('genMetTrue'),
    genMEtCaloLabel =  cms.InputTag('genMetCalo'),
    genMEtCaloAndNonPromptLabel =  cms.InputTag('genMetCaloAndNonPrompt'),
    jetLabel =  cms.InputTag('selectedPatJetsPFlow'),
    #jetLabel =  cms.InputTag('JetEnergyScale','selectedPatJetsPFlow'),
    vertexLabel = cms.untracked.InputTag('offlinePrimaryVertices'),
    #vertexLabel = cms.untracked.InputTag('goodOfflinePrimaryVertices'),
    beamSpotInputTag = cms.InputTag("offlineBeamSpot"),
    rhoIsoInputTag = cms.InputTag('kt6PFJets','rho'),
    EAtarget = cms.string('EleEAData2012'), #EleEANoCorr, EleEAData2011, EleEASummer11MC,EleEAFall11MC, EleEAData2012 
    conversionsInputTag = cms.InputTag("allConversions"),
    useEventCounter = cms.bool( True ),
    filters = cms.untracked.vstring(
        'nEventsTotal',
        'nEventsNoscrap',
        'nEventsHBHE',
#        'nEventsClean',
        'nEventsHLT', 
        'nEventsFiltered',
        'nEventsPatHLT',
    ),
    #for jet cleaning overlapping with isolated epton within 0.4
    relIso1 = cms.untracked.double(0.20),
    relIso2 = cms.untracked.double(0.20),
    #bTagSets = bTagSets,
    #PileUpRD = PuRD2012Low,
    PileUpRD = PuRD2012LowBin60,
    PileUpMC = PuMC2012S8Bin60,
    #PileUpMC = PuMC2012S7Bin60,

    useL1Selector = cms.bool( False ), #for Electron WP80
    L1Select = cms.untracked.string('L1_SingleEG22')
)


TTsemiLept = cms.EDAnalyzer('TTsemiLeptAnalyzer',
    TriggerResultsTag = cms.untracked.InputTag('TriggerResults','','HLT'),
    #HLTTriggers = cms.untracked.vstring('HLT_Mu15_eta2p1'), #To make the Ntuple tree happy
    HLTTriggers = cms.untracked.vstring('HLT_Ele22_CaloIdL_CaloIsoVL','HLT_Ele27_WP80','HLT_Mu15_eta2p1'),
    genParticlesLabel = cms.InputTag('genParticles'),
    Channel = cms.untracked.string('Tau'),
    leptonLabel =  cms.InputTag('acceptedTaus'),
    pfMEtLabel =  cms.InputTag('patMETsPFlow'),
    #metLabel =  cms.InputTag('JetEnergyScale','patMETsPFlow'),
    noPuMEtLabel =  cms.InputTag('noPileUpPFMEt'),
    MVAMEtLabel =  cms.InputTag('pfMEtMVA'),
    genMEtTrueLabel =  cms.InputTag('genMetTrue'),
    genMEtCaloLabel =  cms.InputTag('genMetCalo'),
    genMEtCaloAndNonPromptLabel =  cms.InputTag('genMetCaloAndNonPrompt'),
    jetLabel =  cms.InputTag('ak5PFJetsCorr'),
    #jetLabel =  cms.InputTag('selectedPatJetsPFlow'),
    PUJetDiscriminant = cms.InputTag("pileupJetIdProducer","fullDiscriminant"),
    PUJetId		= cms.InputTag("pileupJetIdProducer","fullId"),
    JetPtMin		= cms.double(30.),
    #jetLabel =  cms.InputTag('JetEnergyScale','selectedPatJetsPFlow'),
    vertexLabel = cms.untracked.InputTag('offlinePrimaryVertices'),
    #vertexLabel = cms.untracked.InputTag('goodOfflinePrimaryVertices'),
    beamSpotInputTag = cms.InputTag("offlineBeamSpot"),
    rhoIsoInputTag = cms.InputTag('kt6PFJets','rho'),
    EAtarget = cms.string('EleEAData2012'), #EleEANoCorr, EleEAData2011, EleEASummer11MC,EleEAFall11MC, EleEAData2012 
    conversionsInputTag = cms.InputTag("allConversions"),
    useEventCounter = cms.bool( True ),
    filters = cms.untracked.vstring(
        'nEventsTotal',
        'nEventsNoscrap',
        'nEventsHBHE',
#        'nEventsClean',
        'nEventsHLT', 
        'nEventsFiltered',
        'nEventsPatHLT',
    ),
    #for jet cleaning overlapping with isolated epton within 0.4
    relIso1 = cms.untracked.double(0.20),
    relIso2 = cms.untracked.double(0.20),
    #bTagSets = bTagSets,
    #PileUpRD = PuRD2012Low,
    PileUpRD = PuRD2012LowBin60,
    PileUpMC = PuMC2012S8Bin60,
    #PileUpMC = PuMC2012S7Bin60,

    useL1Selector = cms.bool( False ), #for Electron WP80
    L1Select = cms.untracked.string('L1_SingleEG22')
)
TT2Hadron = cms.EDAnalyzer('TT2HadronAnalyzer',
    TriggerResultsTag = cms.untracked.InputTag('TriggerResults','','HLT'),
    #HLTTriggers = cms.untracked.vstring('HLT_Mu15_eta2p1'), #To make the Ntuple tree happy
    HLTTriggers = cms.untracked.vstring('HLT_Ele22_CaloIdL_CaloIsoVL','HLT_Ele27_WP80','HLT_Mu15_eta2p1'),
    genParticlesLabel = cms.InputTag('genParticles'),
    Channel = cms.untracked.string('Tau'),
    #leptonLabel =  cms.InputTag('acceptedTaus'),
    pfMEtLabel =  cms.InputTag('patMETsPFlow'),
    #metLabel =  cms.InputTag('JetEnergyScale','patMETsPFlow'),
    noPuMEtLabel =  cms.InputTag('noPileUpPFMEt'),
    MVAMEtLabel =  cms.InputTag('pfMEtMVA'),
    genMEtTrueLabel =  cms.InputTag('genMetTrue'),
    genMEtCaloLabel =  cms.InputTag('genMetCalo'),
    genMEtCaloAndNonPromptLabel =  cms.InputTag('genMetCaloAndNonPrompt'),
    jetLabel =  cms.InputTag('ak5PFJetsCorr'),
    #jetLabel =  cms.InputTag('selectedPatJetsPFlow'),
    PUJetDiscriminant = cms.InputTag("pileupJetIdProducer","fullDiscriminant"),
    PUJetId		= cms.InputTag("pileupJetIdProducer","fullId"),
    JetPtMin		= cms.double(30.),
    #jetLabel =  cms.InputTag('JetEnergyScale','selectedPatJetsPFlow'),
    vertexLabel = cms.untracked.InputTag('offlinePrimaryVertices'),
    #vertexLabel = cms.untracked.InputTag('goodOfflinePrimaryVertices'),
    beamSpotInputTag = cms.InputTag("offlineBeamSpot"),
    rhoIsoInputTag = cms.InputTag('kt6PFJets','rho'),
    EAtarget = cms.string('EleEAData2012'), #EleEANoCorr, EleEAData2011, EleEASummer11MC,EleEAFall11MC, EleEAData2012 
    conversionsInputTag = cms.InputTag("allConversions"),
    useEventCounter = cms.bool( True ),
    filters = cms.untracked.vstring(
        'nEventsTotal',
        'nEventsNoscrap',
        'nEventsHBHE',
#        'nEventsClean',
        'nEventsHLT', 
        'nEventsFiltered',
        'nEventsPatHLT',
    ),
    #for jet cleaning overlapping with isolated epton within 0.4
    relIso1 = cms.untracked.double(0.20),
    relIso2 = cms.untracked.double(0.20),
    #bTagSets = bTagSets,
    #PileUpRD = PuRD2012Low,
    PileUpRD = PuRD2012LowBin60,
    PileUpMC = PuMC2012S8Bin60,
    #PileUpMC = PuMC2012S7Bin60,

    useL1Selector = cms.bool( False ), #for Electron WP80
    L1Select = cms.untracked.string('L1_SingleEG22')
)
MonoJet = cms.EDAnalyzer('MonoJetAnalyzer',
    TriggerResultsTag = cms.untracked.InputTag('TriggerResults','','HLT'),
    #HLTTriggers = cms.untracked.vstring('HLT_Mu15_eta2p1'), #To make the Ntuple tree happy
    HLTTriggers = cms.untracked.vstring('HLT_Ele22_CaloIdL_CaloIsoVL','HLT_Ele27_WP80','HLT_Mu15_eta2p1'),
    genParticlesLabel = cms.InputTag('genParticles'),
    Channel = cms.untracked.string('Tau'),
    #leptonLabel =  cms.InputTag('acceptedTaus'),
    pfMEtLabel =  cms.InputTag('patMETsPFlow'),
    #metLabel =  cms.InputTag('JetEnergyScale','patMETsPFlow'),
    noPuMEtLabel =  cms.InputTag('noPileUpPFMEt'),
    MVAMEtLabel =  cms.InputTag('pfMEtMVA'),
    genMEtTrueLabel =  cms.InputTag('genMetTrue'),
    genMEtCaloLabel =  cms.InputTag('genMetCalo'),
    genMEtCaloAndNonPromptLabel =  cms.InputTag('genMetCaloAndNonPrompt'),
    jetLabel =  cms.InputTag('ak5PFJetsCorr'),
    #jetLabel =  cms.InputTag('selectedPatJetsPFlow'),
    PUJetDiscriminant = cms.InputTag("pileupJetIdProducer","fullDiscriminant"),
    PUJetId		= cms.InputTag("pileupJetIdProducer","fullId"),
    JetPtMin		= cms.double(30.),
    #jetLabel =  cms.InputTag('JetEnergyScale','selectedPatJetsPFlow'),
    vertexLabel = cms.untracked.InputTag('offlinePrimaryVertices'),
    #vertexLabel = cms.untracked.InputTag('goodOfflinePrimaryVertices'),
    beamSpotInputTag = cms.InputTag("offlineBeamSpot"),
    rhoIsoInputTag = cms.InputTag('kt6PFJets','rho'),
    EAtarget = cms.string('EleEAData2012'), #EleEANoCorr, EleEAData2011, EleEASummer11MC,EleEAFall11MC, EleEAData2012 
    conversionsInputTag = cms.InputTag("allConversions"),
    useEventCounter = cms.bool( True ),
    filters = cms.untracked.vstring(
        'nEventsTotal',
        'nEventsNoscrap',
        'nEventsHBHE',
#        'nEventsClean',
        'nEventsHLT', 
        'nEventsFiltered',
        'nEventsPatHLT',
    ),
    #for jet cleaning overlapping with isolated epton within 0.4
    relIso1 = cms.untracked.double(0.20),
    relIso2 = cms.untracked.double(0.20),
    #bTagSets = bTagSets,
    #PileUpRD = PuRD2012Low,
    PileUpRD = PuRD2012LowBin60,
    PileUpMC = PuMC2012S8Bin60,
    #PileUpMC = PuMC2012S7Bin60,

    useL1Selector = cms.bool( False ), #for Electron WP80
    L1Select = cms.untracked.string('L1_SingleEG22')
)

WAcceptanceMuon = cms.EDFilter('wAcceptAnalyzer',
    genParticlesLabel = cms.InputTag('genParticles'),
    Channel = cms.untracked.string('Muon'),
    useEventCounter = cms.bool( True ),
    filters = cms.untracked.vstring(
        'nEventsTotal',
    ),
)
WAcceptanceElectron = cms.EDFilter('wAcceptAnalyzer',
    genParticlesLabel = cms.InputTag('genParticles'),
    Channel = cms.untracked.string('Electron'),
    useEventCounter = cms.bool( True ),
    filters = cms.untracked.vstring(
        'nEventsTotal',
    ),
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
nEventsNoscrap = cms.EDProducer("EventCountProducer")
nEventsHBHE = cms.EDProducer("EventCountProducer")

WMuNeuAnalysisMCSequence = cms.Sequence(
#    hltHighLevelSingleMuLoPU*
    nEventsPatHLT*
#    topWLeptonGenFilter*
#    GenZmassFilter*
#    selectedPatJetsPFlow*
#    PUweight*
#    DYmmFilter*
    Muons*
    MuonsFilter*
#    JetEnergyScale*
    WMuNeu
#    mm
)
WZ3LNuAnalysisMCSequence = cms.Sequence(
#    hltHighLevelSingleMuLoPU*
    nEventsPatHLT*
#    topWLeptonGenFilter*
#    GenZmassFilter*
#    selectedPatJetsPFlow*
#    PUweight*
#    DYmmFilter*
    Muons*
    Electrons*
#    MuonsFilter*
#    JetEnergyScale*
    WZ3LNu
#    mm
)
WWAnalysisMCSequence = cms.Sequence(
#    hltHighLevelSingleMuLoPU*
    nEventsPatHLT*
#    topWLeptonGenFilter*
#    GenZmassFilter*
#    selectedPatJetsPFlow*
#    PUweight*
#    DYmmFilter*
    Muons*
    Electrons*
#    JetEnergyScale*
    WW
#    mm
)
ZMuMuAnalysisMCSequence = cms.Sequence(
#    hltHighLevelSingleMuLoPU*
    nEventsPatHLT*
#    topWLeptonGenFilter*
#    GenZmassFilter*
#    selectedPatJetsPFlow*
#    PUweight*
#    DYmmFilter*
    Muons*
    MuonsFilter*
#    JetEnergyScale*
    ZMuMu
#    mm
)
ZZ4LAnalysisMCSequence = cms.Sequence(
#    hltHighLevelSingleMuLoPU*
    nEventsPatHLT*
#    topWLeptonGenFilter*
#    GenZmassFilter*
#    selectedPatJetsPFlow*
#    PUweight*
#    DYmmFilter*
    Muons*
    Electrons*
#    JetEnergyScale*
    ZZ4L
#    mm
)
WTauNeuAnalysisMCSequence = cms.Sequence(
    #noscraping*
    #nEventsNoscrap*
    #HBHENoiseFilter*
    #nEventsHBHE*
#    nEventsClean*
#    hltHighLevelSingleMuLoPU*
    nEventsPatHLT*
#    topWLeptonGenFilter*
#    GenZmassFilter*
#    selectedPatJetsPFlow*
#    PUweight*
#    DYmmFilter*
#    Muons*
#    MuonsFilter*
#    JetEnergyScale*
    WTauNeu
#    mm
)

WMuNeuAnalysisRealDataSequence = cms.Sequence(
#    hltHighLevelSingleMuRD*
#    muonTriggerFilterByRun*
    nEventsPatHLT*
    removeDuplicate*
#    DYmmFilter*
#    selectedPatJetsPFlow*
    Muons*
    MuonsFilter*
#    JetEnergyScale*
    WMuNeu
#    mm
)
WEleNeuAnalysisMCSequence = cms.Sequence(
    #noscraping*
    #nEventsNoscrap*
    #HBHENoiseFilter*
    #nEventsHBHE*
    # HLT Cut
#    hltHighLevelSingleEleMC*
    nEventsPatHLT*
#    removeDuplicate*
#    WLeptonGenFilter*
#    GenZmassFilter*
##    selectedPatJetsPFlow*
##    PUweight*
##    ElectronAna*
    Electrons*
    ElectronsFilter*
#    JetEnergyScale*
#    ElEl
    WEleNeu
#    ee
)
ZElElAnalysisMCSequence = cms.Sequence(
    #noscraping*
    #nEventsNoscrap*
    #HBHENoiseFilter*
    #nEventsHBHE*
    # HLT Cut
#    hltHighLevelSingleEleMC*
    nEventsPatHLT*
#    removeDuplicate*
#    WLeptonGenFilter*
#    GenZmassFilter*
##    selectedPatJetsPFlow*
##    PUweight*
##    ElectronAna*
    Electrons*
    ElectronsFilter*
#    JetEnergyScale*
#    ElEl
    ZElEl
#    ee
)

WEleNeuAnalysisRealDataSequence = cms.Sequence(
#    hltHighLevelSingleEleRD*
#    electronTriggerFilterByRun*
    nEventsPatHLT*
    removeDuplicate*
#    selectedPatJetsPFlow*
#    ElectronAna*
    Electrons*
    ElectronsFilter*
#    JetEnergyScale*
    WEleNeu
#    ee
)
TTsemiLeptEleMCSequence = cms.Sequence(
#    hltHighLevelSingleEleRD*
#    electronTriggerFilterByRun*
    nEventsPatHLT*
    removeDuplicate*
#    ElectronAna*
    Electrons*
    ElectronsFilter*
#    JetEnergyScale*
    TTsemiLept
)
TTsemiLeptMuMCSequence = cms.Sequence(
#    hltHighLevelSingleEleRD*
#    electronTriggerFilterByRun*
    nEventsPatHLT*
    removeDuplicate*
    Muons*
    MuonsFilter*
#    JetEnergyScale*
    TTsemiLept
)
TT2HadronMCSequence = cms.Sequence(
#    hltHighLevelSingleEleRD*
#    electronTriggerFilterByRun*
    nEventsPatHLT*
    removeDuplicate*
#    JetEnergyScale*
    TT2Hadron
)
MonoJetMCSequence = cms.Sequence(
#    hltHighLevelSingleEleRD*
#    electronTriggerFilterByRun*
    nEventsPatHLT*
    removeDuplicate*
#   JetEnergyScale*
    MonoJet
)
