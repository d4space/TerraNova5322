import FWCore.ParameterSet.Config as cms

from KNUPhy.WAnalyzer.pf2pat_template_RD_cfg import *
from KNUPhy.WAnalyzer.eventContent_cff import *
from KNUPhy.WAnalyzer.tools import *

postfix = "PFlow"
jetAlgo="AK5"
usePF2PAT(process,runPF2PAT=True, jetAlgo=jetAlgo, runOnMC=False, postfix=postfix, typeIMetCorrections=True)

#process.pfPileUpIsoPFlow.checkClosestZVertex = cms.bool(False)
#process.pfPileUpIso.checkClosestZVertex = cms.bool(False)

#change cone size TODO
changeConeSize(process,postfix)

#FastJet!
#applyFastJet(process,postfix)
process.GlobalTag.globaltag = cms.string('FT_53_V6C_AN3::All')

rhoFor2012Aeff(process,postfix)

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
process.patElectronFilter.minNumber = 1

## Source
process.source = cms.Source("PoolSource",
                                fileNames = cms.untracked.vstring(
 'file:/d1/scratch/jungmin/SingleElectron_Run2012B_13Jul2012-v1_AOD.root'
				  #  '/store/data/Run2011A/MuEG/AOD/PromptReco-v1/000/161/312/04850A2C-F757-E011-9A74-003048F024DC.root'
  )
)

#process.p += process.hltHighLevelMuMuRD
process.p += process.nEventsHLT
process.p += getattr(process,"patPF2PATSequence"+postfix)
#process.p += process.looseLeptonSequence
process.p += process.acceptedElectrons
#process.p += process.acceptedMuons
process.p += process.patElectronFilter
process.p += process.allConversions
#process.p += process.patMuonFilter
process.p += process.nEventsFiltered

