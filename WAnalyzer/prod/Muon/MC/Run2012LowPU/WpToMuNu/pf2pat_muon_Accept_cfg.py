import FWCore.ParameterSet.Config as cms

from KNUPhy.WAnalyzer.pf2pat_template_Accept_cfg import *
from KNUPhy.WAnalyzer.eventContent_cff import *
from KNUPhy.WAnalyzer.tools import *

runOnMC=True
postfix = "PFlow"
jetAlgo="AK5"
usePF2PAT(process,runPF2PAT=True, jetAlgo=jetAlgo, runOnMC=runOnMC, postfix=postfix, typeIMetCorrections=False)

#process.pfPileUpIsoPFlow.checkClosestZVertex = cms.bool(False)
#process.pfPileUpIso.checkClosestZVertex = cms.bool(False)

#change cone size TODO
#changeConeSize(process,postfix)

#FastJet!
#applyFastJet(process,postfix)

#REMOVE ISOLATION FROM PF2PAT!!!
addLooseLeptons(process)

# top projections in PF2PAT:
topProjection(process,postfix)

# output
process.out.outputCommands +=pf2patEventContent

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

#process.acceptedMuons.cut = cms.string("pt > 20 && abs(eta) < 2.5 && (chargedHadronIso + neutralHadronIso + photonIso)/pt < 0.05")

process.patMuonFilter.minNumber = 0
process.patElectronFilter.minNumber = 0

## Source
process.source = cms.Source("PoolSource",
                                fileNames = cms.untracked.vstring(
  'file:/terranova_1/MC_Sample/W_LowPU_S8/WplusToMuNu_AODSIM_1_1_2YJ.root',
  #'/store/data/Run2011B/DoubleMu/AOD/PromptReco-v1/000/180/252/085F0838-4305-E111-BDD0-003048CF94A8.root',
  #'/store/data/Run2011A/DoubleMu/RECO/PromptReco-v1/000/161/312/9CD2FBA7-E557-E011-B433-001D09F29849.root',
  #'/store/data/Run2011A/DoubleElectron/AOD/PromptReco-v1/000/161/312/0E8D9A70-E857-E011-B3DC-001D09F29321.root',
  #'/store/data/Run2011A/MuEG/AOD/PromptReco-v1/000/161/312/04850A2C-F757-E011-9A74-003048F024DC.root'
  )
)

#process.p += process.hltHighLevelMuMuRD
process.p += process.nEventsHLT
process.p += getattr(process,"patPF2PATSequence"+postfix)
#process.p += process.looseLeptonSequence
#process.p += process.acceptedElectrons
process.p += process.acceptedMuons
#process.p += process.patElectronFilter
process.p += process.patMuonFilter
process.p += process.nEventsFiltered

