import FWCore.ParameterSet.Config as cms
import os ##

process = cms.Process("PAT") ##

runOnMC=True
postfix = "PFlow"
jetAlgo="AK5"

process.load("KoSMP.WAnalyzer.pf2pat_template_MC_cfg") ##

#PF2PAT ##
process.load("PhysicsTools.PatAlgos.patSequences_cff") ##
from PhysicsTools.PatAlgos.tools.pfTools import * ##
from KoSMP.WAnalyzer.pat_S10_cfg import * ##
from KoSMP.WAnalyzer.eventContent_cff import *
from KoSMP.WAnalyzer.tools import *

## Options and Output Report ##
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )##
process.GlobalTag.globaltag = myGlobaltag ##


# output
## Output Module Configuration (expects a path 'p')
process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string('patTuple_skim.root'),
    # save only events passing the full path
    SelectEvents   = cms.untracked.PSet( SelectEvents = cms.vstring('p') ),
    # save PAT Layer 1 output; you need a '*' to
    # unpack the list of commands 'patEventContent'
    outputCommands = cms.untracked.vstring('drop *')
)

if runOnMC: 
    usePF2PAT(process,runPF2PAT=True, jetAlgo=jetAlgo, runOnMC=runOnMC, postfix=postfix, typeIMetCorrections=True) 
else :      
    usePF2PAT(process,runPF2PAT=True, jetAlgo=jetAlgo, runOnMC=runOnMC, postfix=postfix, jetCorrections=('AK5PFchs',['L1FastJet','L2Relative', 'L3Absolute','L2L3Residual'] ), typeIMetCorrections=True)



process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

#process.acceptedMuons.cut = cms.string("pt > 20 && abs(eta) < 2.5 && (chargedHadronIso + neutralHadronIso + photonIso)/pt < 0.05")


## Source
process.source = cms.Source("PoolSource",
                                fileNames = cms.untracked.vstring(
  #'/store/data/Run2011B/DoubleMu/AOD/PromptReco-v1/000/180/252/085F0838-4305-E111-BDD0-003048CF94A8.root',
  #'/store/data/Run2011A/DoubleMu/RECO/PromptReco-v1/000/161/312/9CD2FBA7-E557-E011-B433-001D09F29849.root',
  #'/store/data/Run2011A/DoubleElectron/AOD/PromptReco-v1/000/161/312/0E8D9A70-E857-E011-B3DC-001D09F29321.root',
  #'/store/data/Run2011A/MuEG/AOD/PromptReco-v1/000/161/312/04850A2C-F757-E011-9A74-003048F024DC.root'
'file:/afs/cern.ch/work/t/taehoon/public/DATA/MC/2012/Summer12_DR53X__WToENu_TuneZ2star_8TeV_pythia6_AODSIM_PU_S10_START53_V7A-v2.root'
  )
)

# output
process.out.outputCommands +=pf2patEventContent

process.outpath = cms.EndPath(process.out)

process.p = cms.Path(
    process.nEventsTotal*
    process.noscraping*
    process.nEventsNoscrap*
#    process.goodOfflinePrimaryVertices*
    process.HBHENoiseFilter *
    process.nEventsHBHE
#    process.nEventsClean
#    process.patElectronIDs*
#    process.eidCiCSequence
)


#process.pfPileUpIsoPFlow.checkClosestZVertex = cms.bool(False)
#process.pfPileUpIso.checkClosestZVertex = cms.bool(False)

#change cone size TODO
changeConeSize(process,postfix)

#FastJet!
#applyFastJet(process,postfix)

rhoFor2012Aeff(process,postfix)

#REMOVE ISOLATION FROM PF2PAT!!!
addLooseLeptons(process)

# top projections in PF2PAT:
topProjection(process,postfix)

process.patMuonFilter.minNumber = 0
process.patElectronFilter.minNumber = 1


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

