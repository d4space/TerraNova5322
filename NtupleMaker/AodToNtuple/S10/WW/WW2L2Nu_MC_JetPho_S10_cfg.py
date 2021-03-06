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

UseCHS=''
#UseCHS='CHS'
JetCorrection          = "ak5PFL1FastL2L3"
PFJetCollection   = 'ak5PFJets'+UseCHS
PFJetCollectionCorr   = 'ak5PFJetsCorr'

process.ak5PFJetsCorr = cms.EDProducer('PFJetCorrectionProducer',
    src = cms.InputTag(PFJetCollection),
    correctors = cms.vstring(JetCorrection) # NOTE: use "ak5PFL1FastL2L3" for MC / "ak5PFL1FastL2L3Residual" for Data
    )

process.PFJet50 = cms.EDFilter("CandViewSelector",
    src = cms.InputTag("ak5PFJetsCorr"),
    cut = cms.string("pt > 50"),
    filter = cms.bool(True),
    )
from TerraNova.CommonTools.jetSelectorPSet_cff import jetSelectorPSet
process.acceptedJets = cms.EDProducer(
    "KyJetSelector",
    jetLabel  = cms.InputTag("ak5PFJetsCorr"),
    PUJetDiscriminant = cms.InputTag("pileupJetIdProducer","fullDiscriminant"),
    PUJetId             = cms.InputTag("pileupJetIdProducer","fullId"),
    )
from PhysicsTools.SelectorUtils.pfJetIDSelector_cfi import pfJetIDSelector
process.tightPFJetsPFlow = cms.EDFilter("PFJetIDSelectionFunctorBasicFilter",
    filterParams = pfJetIDSelector.clone(quality=cms.string("TIGHT")),
    src = cms.InputTag(PFJetCollectionCorr)
    )

process.goodPhotons = cms.EDFilter(
    "PhotonSelector",
    src = cms.InputTag("photons"),
    cut = cms.string("hadronicOverEm<0.15 && (abs(superCluster.eta)<2.5) && !(1.4442<abs(superCluster.eta)<1.566) && ((isEB && sigmaIetaIeta<0.01) || (isEE && sigmaIetaIeta<0.03)) && (superCluster.energy*sin(superCluster.position.theta)>30) && pt>30")
    )

process.load('RecoJets.JetProducers.PileupJetID_cfi')
process.pileupJetIdProducer.jets = PFJetCollectionCorr
#process.pileupJetIdProducer.jets = cms.InputTag('ak5PFJets')
#process.pileupJetIdProducer.jets = cms.InputTag('selectedPatJets')
#process.pileupJetIdProducer.jets = 'selectedPatJetsPFlow'
process.pileupJetIdProducer.vertexes = "goodOfflinePrimaryVertices"
process.pileupJetIdProducer.residualsTxt  = cms.FileInPath("RecoJets/JetProducers/data/mva_JetID_v1.weights.xml")

### ============= NoPU and MVA MET ===============###
process.load('RecoMET.METPUSubtraction.mvaPFMET_leptons_cfi')
# No PU MET
process.load('RecoMET.METPUSubtraction.noPileUpPFMET_cff')
if runOnMC:
  process.calibratedAK5PFJetsForNoPileUpPFMEt.correctors = cms.vstring('ak5PFL1FastL2L3')
else:
  process.calibratedAK5PFJetsForNoPileUpPFMEt.correctors = cms.vstring('ak5PFL1FastL2L3Residual')

process.noPileUpPFMEt.srcLeptons = cms.VInputTag("isomuons","isoelectrons","isotaus","acceptedJets","goodPhotons")
#process.noPileUpPFMEt.srcLeptons = cms.VInputTag("isomuons","isoelectrons","isotaus")

### MVA MET
process.load('RecoMET.METPUSubtraction.mvaPFMET_cff')
if runOnMC:
  process.calibratedAK5PFJetsForPFMEtMVA.correctors = cms.vstring('ak5PFL1FastL2L3')
else:
  process.calibratedAK5PFJetsForPFMEtMVA.correctors = cms.vstring('ak5PFL1FastL2L3Residual')

process.pfMEtMVA.srcLeptons = cms.VInputTag( "isomuons","isoelectrons","isotaus","acceptedJets","goodPhotons")# #selectedPatMuons
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


process.TFileService = cms.Service("TFileService",
    fileName = cms.string('TerraTuple.root')
)

process.p = cms.Path(
#    process.nEventsTotal*
    process.noscraping*
#    process.nEventsNoscrap*
    process.goodOfflinePrimaryVertices*
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
process.p += process.ak5PFJetsCorr
process.p += process.PFJet50
process.p += process.pileupJetIdProducer
process.p += process.acceptedJets
process.p += process.tightPFJetsPFlow
process.p += process.goodPhotons
#process.p += process.looseLeptonSequence
process.p += process.acceptedMuons
process.p += process.acceptedElectrons
process.p += process.acceptedTaus
#process.p += process.patMuEleTauFilter
#process.p += process.acceptedMuonsFilter
#process.p += process.patElectronFilter
#process.p += process.patTauFilter
process.p += process.nEventsFiltered
process.p += process.isomuonseq
process.p += process.isoelectronseq
process.p += process.isotauseq
process.p += process.noPileUpPFMEtSequence
process.p += process.pfMEtMVAsequence
process.p += process.WWAnalysisMCSequence
