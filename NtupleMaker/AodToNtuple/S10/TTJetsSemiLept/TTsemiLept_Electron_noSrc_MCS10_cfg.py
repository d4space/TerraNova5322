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

from PhysicsTools.PatAlgos.tools.pfTools import * # for patPF2PATSequence
from TerraNova.NtupleMaker.pat_22Jan2013_MC_cfg import *
#from TerraNova.NtupleMaker.eventContent_cff import *
from TerraNova.NtupleMaker.tools import *

## Options and Output Report
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
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
	
# Pre Settings ######################
# 6(pt>10, tight, use for DiMu) 7(pt>27, tight, use for SingleMu)
# -1(no cut) 0(check cut, isocut pset)
#process.METsrcMuons.version = cms.untracked.int32(6)
# -1(no cut), 0(check cut, isocut pset), 1(WptCut)
# 13(medium pt 30) 14(medium pt 15)
#process.METsrcElectrons.version = cms.untracked.int32(14)
### taus
process.load("RecoTauTag.Configuration.RecoPFTauTag_cff")

UseCHS=''
#UseCHS='CHS'
JetCorrection          = "ak5PFL1FastL2L3"
PFJetCollection   = 'ak5PFJets'+UseCHS
PFJetCollectionCorr   = 'ak5PFJetsCorr'

process.ak5PFJetsCorr = cms.EDProducer('PFJetCorrectionProducer',
    src = cms.InputTag(PFJetCollection),
    correctors = cms.vstring(JetCorrection) # NOTE: use "ak5PFL1FastL2L3" for MC / "ak5PFL1FastL2L3Residual" for Data
    )

from PhysicsTools.SelectorUtils.pfJetIDSelector_cfi import pfJetIDSelector
process.tightPFJetsPFlow = cms.EDFilter("PFJetIDSelectionFunctorBasicFilter",
    filterParams = pfJetIDSelector.clone(quality=cms.string("TIGHT")),
    src = cms.InputTag(PFJetCollectionCorr)
    )

process.load('RecoJets.JetProducers.PileupJetID_cfi')
process.pileupJetIdProducer.jets = PFJetCollectionCorr
#process.pileupJetIdProducer.jets = cms.InputTag('ak5PFJets')
#process.pileupJetIdProducer.jets = cms.InputTag('selectedPatJets')
#process.pileupJetIdProducer.jets = 'selectedPatJetsPFlow'
process.pileupJetIdProducer.vertexes = "goodOfflinePrimaryVertices"
process.pileupJetIdProducer.residualsTxt  = cms.FileInPath("RecoJets/JetProducers/data/mva_JetID_v1.weights.xml")
#process.pileupJetIdProducer.jets = cms.InputTag('selectedPatJets')

### ============= NoPU and MVA MET ===============###
process.load('RecoMET.METPUSubtraction.mvaPFMET_leptons_cfi')
# No PU MET
process.load('RecoMET.METPUSubtraction.noPileUpPFMET_cff')
if runOnMC:
  process.calibratedAK5PFJetsForNoPileUpPFMEt.correctors = cms.vstring('ak5PFL1FastL2L3')
else:
  process.calibratedAK5PFJetsForNoPileUpPFMEt.correctors = cms.vstring('ak5PFL1FastL2L3Residual')

#process.noPileUpPFMEt.srcLeptons = cms.VInputTag("isomuons","isoelectrons","isotaus")

### MVA MET
process.load('RecoMET.METPUSubtraction.mvaPFMET_cff')
if runOnMC:
  process.calibratedAK5PFJetsForPFMEtMVA.correctors = cms.vstring('ak5PFL1FastL2L3')
else:
  process.calibratedAK5PFJetsForPFMEtMVA.correctors = cms.vstring('ak5PFL1FastL2L3Residual')

#process.pfMEtMVA.srcLeptons = cms.VInputTag( "isomuons","isoelectrons","isotaus") #selectedPatMuons

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
process.TTsemiLept.Channel = cms.untracked.string("Electron")
process.TTsemiLept.leptonLabel = cms.InputTag("Electrons")
process.TTsemiLept.JetPtMin = cms.double(30)

process.acceptedMuonsFilter.minNumber = 1
process.ElectronsFilter.minNumber = 1


#process.load("FWCore.MessageLogger.MessageLogger_cfi")
#process.MessageLogger = cms.Service("MessageLogger")
#process.MessageLogger.destinations = ['cout']
#process.MessageLogger.cout = cms.untracked.PSet(
#    threshold = cms.untracked.string('INFO'),
#    FwkReport = cms.untracked.PSet(reportEvery=cms.untracked.int32(1000))
#)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('TerraTuple.root')
)

process.p = cms.Path(
    process.nEventsTotal*
    process.noscraping*
    process.nEventsNoscrap*
    process.goodOfflinePrimaryVertices*
    process.HBHENoiseFilter*
    process.nEventsHBHE
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
process.p += process.ak5PFJetsCorr
#process.p += process.tightPFJetsPFlow
process.p += process.pileupJetIdProducer
#process.p += process.looseLeptonSequence
#process.p += process.acceptedMuons
#process.p += process.METsrcMuons
process.p += process.acceptedElectrons
process.p += process.nEventsFiltered
process.p += process.isomuonseq
process.p += process.isoelectronseq
process.p += process.isotauseq
process.p += process.noPileUpPFMEtSequence
process.p += process.pfMEtMVAsequence
process.p += process.TTsemiLeptEleMCSequence
