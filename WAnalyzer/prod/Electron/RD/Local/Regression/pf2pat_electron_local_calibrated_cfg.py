import FWCore.ParameterSet.Config as cms

from KNUPhy.WAnalyzer.pf2pat_template_RD_cfg import *
from KNUPhy.WAnalyzer.eventContent_cff import *
from KNUPhy.WAnalyzer.tools import *

process.RandomNumberGeneratorService = cms.Service("RandomNumberGeneratorService",
    calibratedPatElectrons = cms.PSet(
        initialSeed = cms.untracked.uint32(1),
        engineName = cms.untracked.string('TRandom3')
    ),
)

process.load("EgammaAnalysis.ElectronTools.calibratedPatElectrons_cfi")

process.calibratedPatElectrons.isMC = cms.bool(False)
#process.calibratedPatElectrons.isMC = cms.bool(True) // it gives error : unknown MC data
process.calibratedPatElectrons.inputDataset = cms.string("Moriond2013")
process.calibratedPatElectrons.updateEnergyError = cms.bool(True)
process.calibratedPatElectrons.applyCorrections = cms.int32(10)
process.calibratedPatElectrons.verbose = cms.bool(True)
process.calibratedPatElectrons.synchronization = cms.bool(True)

process.load('EgammaAnalysis.ElectronTools.electronRegressionEnergyProducer_cfi')
process.eleRegressionEnergy.inputElectronsTag = cms.InputTag('selectedPatElectronsPFlow')

acceptedElectrons = cms.InputTag("calibratedPatElectrons")

postfix = "PFlow"
jetAlgo="AK5"
usePF2PAT(process,runPF2PAT=True, jetAlgo=jetAlgo, runOnMC=False, postfix=postfix,typeIMetCorrections=True)

#process.pfPileUpIsoPFlow.checkClosestZVertex = cms.bool(False)
#process.pfPileUpIso.checkClosestZVertex = cms.bool(False)

#change cone size
changeConeSize(process,postfix)

#FastJet!
#applyFastJet(process,postfix)

#rhoFor2011Aeff(process,postfix)
rhoFor2012Aeff(process,postfix)

#useGefElectrons(process,postfix)
#REMOVE ISOLATION FROM PF2PAT!!!
addLooseLeptons(process)

# top projections in PF2PAT:
topProjection(process,postfix)

# output
process.out.outputCommands +=pf2patEventContent

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(3000) )
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.patMuonFilter.minNumber = 0
process.patElectronFilter.minNumber = 1

## Source
process.load("KNUPhy.WAnalyzer.Sources.Run2012A_SingleEle_AOD_copy_cff")

#process.p += process.hltHighLevelMuMuRD
process.p += process.nEventsHLT
process.p += getattr(process,"patPF2PATSequence"+postfix)
#process.p += process.looseLeptonSequence
process.p += process.eleRegressionEnergy*process.calibratedPatElectrons
process.p += process.acceptedElectrons
#process.p += process.acceptedMuons
process.p += process.patElectronFilter
process.p += process.allConversions
#process.p += process.patMuonFilter
process.p += process.nEventsFiltered

