import FWCore.ParameterSet.Config as cms

from KoSMP.WAnalyzer.pf2pat_template_MC_cfg import *
from KoSMP.WAnalyzer.eventContent_cff import *
from KoSMP.WAnalyzer.tools import *

runOnMC=True
postfix = "PFlow"
jetAlgo="AK5"
usePF2PAT(process,runPF2PAT=True, jetAlgo=jetAlgo, runOnMC=runOnMC, postfix=postfix, typeIMetCorrections=True)

#process.pfPileUpIsoPFlow.checkClosestZVertex = cms.bool(False)
#process.pfPileUpIso.checkClosestZVertex = cms.bool(False)

#change cone size
#changeConeSize(process,postfix)

#FastJet!
#applyFastJet(process,postfix)

#REMOVE ISOLATION FROM PF2PAT!!!
addLooseLeptons(process)

# top projections in PF2PAT:
topProjection(process,postfix)

# output
process.out.outputCommands +=pf2patEventContent

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(2000) )
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.patMuonFilter.minNumber = 1
process.patElectronFilter.minNumber = 0

## Source
process.load("KoSMP.WAnalyzer.Sources.WplusToMuNu_AODSIM_CP_local_cff")

#process.p += process.hltHighLevelMuMuRD
process.p += process.nEventsHLT
process.p += getattr(process,"patPF2PATSequence"+postfix)
#process.p += process.looseLeptonSequence
#process.p += process.acceptedElectrons
process.p += process.acceptedMuons
#process.p += process.patElectronFilter
process.p += process.patMuonFilter
process.p += process.nEventsFiltered

