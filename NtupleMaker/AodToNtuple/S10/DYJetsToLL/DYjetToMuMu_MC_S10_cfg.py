import FWCore.ParameterSet.Config as cms
import os
########### Make PAT #############
process = cms.Process("TerraTuple")
process.load("TerraNova.NtupleMaker.Common_cfg")
process.load("TerraNova.NtupleMaker.Filters_cfg")

produceTaus = False
runOnMC = True
postfix = "PFlow"
jetAlgo="AK5"

produceNoPUPFMET = True
produceMVAPFMET = True

process.load("TerraNova.NtupleMaker.pf2pat_template_MC_cfg")
process.acceptedMuonsFilter.minNumber = 2

from PhysicsTools.PatAlgos.tools.pfTools import *
from TerraNova.NtupleMaker.pat_22Jan2013_MC_cfg import *
#from TerraNova.NtupleMaker.eventContent_cff import *
from TerraNova.NtupleMaker.tools import *

## Options and Output Report
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
#process.GlobalTag.globaltag = cms.string( 'START53_V18::All' )
process.GlobalTag.globaltag = myGlobaltag

## Source
from PhysicsTools.PatAlgos.tools.cmsswVersionTools import pickRelValInputFiles
#process.source = cms.Source("PoolSource",
#    fileNames = cms.untracked.vstring(
#    pickRelValInputFiles( cmsswVersion  = os.environ['CMSSW_VERSION']
#                        , relVal        = 'RelValTTbar'
#                        , globalTag     = process.GlobalTag.globaltag.value().split(':')[0]
#                        , numberOfFiles = 1
#                        )
#    )
#)
# output
## Output Module Configuration (expects a path 'p')
## Source
process.load("TerraNova.NtupleMaker.Sources.SourceTemplate_cff")

process.out = cms.OutputModule("PoolOutputModule",
    #fileName = cms.untracked.string('patTuple_skim.root'),
    ## save only events passing the full path
    #SelectEvents   = cms.untracked.PSet( SelectEvents = cms.vstring('p') ),
    ## save PAT Layer 1 output; you need a '*' to
    ## unpack the list of commands 'patEventContent'
    outputCommands = cms.untracked.vstring('drop *')
)

if runOnMC:
  usePF2PAT(process,runPF2PAT=True, jetAlgo=jetAlgo, runOnMC=runOnMC, postfix=postfix, jetCorrections=('AK5PFchs',['L1FastJet','L2Relative', 'L3Absolute'] ), typeIMetCorrections=True)
else :
  usePF2PAT(process,runPF2PAT=True, jetAlgo=jetAlgo, runOnMC=runOnMC, postfix=postfix, jetCorrections=('AK5PFchs',['L1FastJet','L2Relative', 'L3Absolute','L2L3Residual'] ), typeIMetCorrections=True)
	
### taus
process.load("RecoTauTag.Configuration.RecoPFTauTag_cff")


#from PhysicsTools.SelectorUtils.pfJetIDSelector_cfi import pfJetIDSelector
#process.tightPFJetsPFlow = cms.EDFilter("PFJetIDSelectionFunctorBasicFilter",
#    filterParams = pfJetIDSelector.clone(quality=cms.string("TIGHT")),
#    src = cms.InputTag(PFJetCollectionCorr)
#    )


### ============= NoPU and MVA MET ===============###
process.load('RecoMET.METPUSubtraction.mvaPFMET_leptons_cfi')
# No PU MET
process.load('RecoMET.METPUSubtraction.noPileUpPFMET_cff')
if runOnMC:
  process.calibratedAK5PFJetsForNoPileUpPFMEt.correctors = cms.vstring('ak5PFL1FastL2L3')
else:
  process.calibratedAK5PFJetsForNoPileUpPFMEt.correctors = cms.vstring('ak5PFL1FastL2L3Residual')

process.noPileUpPFMEt.srcLeptons = cms.VInputTag("isomuons","isoelectrons","isotaus")

### MVA MET
process.load('RecoMET.METPUSubtraction.mvaPFMET_cff')
if runOnMC:
  process.calibratedAK5PFJetsForPFMEtMVA.correctors = cms.vstring('ak5PFL1FastL2L3')
else:
  process.calibratedAK5PFJetsForPFMEtMVA.correctors = cms.vstring('ak5PFL1FastL2L3Residual')

process.pfMEtMVA.srcLeptons = cms.VInputTag( "isomuons","isoelectrons","isotaus") #selectedPatMuons

#process.pfPileUpIsoPFlow.checkClosestZVertex = cms.bool(False)
#process.pfPileUpIso.checkClosestZVertex = cms.bool(False)

#change cone size TODO
#changeConeSize(process,postfix)

#FastJet!
#applyFastJet(process,postfix)

#REMOVE ISOLATION FROM PF2PAT!!!
#addLooseLeptons(process)

# top projections in PF2PAT:
#topProjection(process,postfix)

# output

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

######### NTuple Chain ###############
process.load("TerraNova.NtupleMaker.NtupleMaker_MC_cff")


process.TFileService = cms.Service("TFileService",
    fileName = cms.string('TerraTuple.root')
)

process.p = cms.Path(
#    process.nEventsTotal*
    process.noscraping*
#    process.nEventsNoscrap*
#    process.goodOfflinePrimaryVertices*
    process.HBHENoiseFilter
#    process.nEventsHBHE
#    process.nEventsClean
#    process.patElectronIDs*
#    process.eidCiCSequence
)
if produceTaus:
  process.p += process.recoTauClassicHPSSequence
  print "Using Tau Sequence =================================="
#process.p += process.hltHighLevelMuMuRD
process.p += process.nEventsHLT
process.p += getattr(process,"patPF2PATSequence"+postfix)
#process.p += process.looseLeptonSequence
process.p += process.acceptedMuons
#process.p += process.acceptedElectrons
#process.p += process.acceptedTaus
#process.p += process.patMuEleTauFilter
process.p += process.acceptedMuonsFilter
#process.p += process.patElectronFilter
#process.p += process.patTauFilter
process.p += process.nEventsFiltered
process.p += process.isomuonseq
process.p += process.isoelectronseq
process.p += process.isotauseq
process.p += process.noPileUpPFMEtSequence
process.p += process.pfMEtMVAsequence
process.p += process.ZMuNeuAnalysisMCSequence
