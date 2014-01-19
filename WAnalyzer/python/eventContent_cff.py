import FWCore.ParameterSet.Config as cms

## EventContents
from PhysicsTools.PatAlgos.patEventContent_cff import *
pf2patEventContent = cms.untracked.vstring('drop *')
pf2patEventContent += patTriggerEventContent
pf2patEventContent += patExtraAodEventContent
#pf2patEventContent += patEventContentNoCleaning
pf2patEventContent +=[
        'keep edmMergeableCounter_*_*_*',
        'keep *_goodOfflinePrimaryVertices*_*_*',
        'keep *_offlinePrimaryVertices*_*_*',
        'drop *_towerMaker_*_*',
        'keep *_particleFlow_*_*',
        'keep *_acceptedMuons_*_*',
        'keep *_acceptedElectrons_*_*',
	'keep *_acceptedTaus_*_*',
	'keep *_allConversions*_*_*',
        'keep *_selectedPatJetsPFlow_*_*',
        'keep *_patMETsPFlow_*_*',
        'keep double_*PFlow*_rho_PAT',
	'keep *_kt6PF*_rho_*',
	'keep double_kt6PFJetsForIsolation_rho_*',
        'keep *_pfJets*_*_*',
        'keep *_addPileupInfo_*_*',
	'keep *_noPileUpPFMEt_*_*',
	'keep *_pfMEtMVA_*_*',
	'keep *MET*_*_*_*',
	'keep *_*met*_*_*',
	'keep *_*Met*_*_*',
	'keep *_genMetTrue_*_*',
	'keep *_genMetCalo_*_*',
	'keep *_genMetCaloAndNonPrompt_*_*',
]

