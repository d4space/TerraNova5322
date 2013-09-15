import FWCore.ParameterSet.Config as cms
import os
# Options
produceTaus=False

runOnMC=True
postfix = "PFlow"
jetAlgo="AK5"

produceNoPUPFMET=True
produceMVAPFMET=True

process = cms.Process("PAT")

process.load("KNUPhy.WAnalyzer.pf2pat_template_MC_MVaNoPuMEt_cfg")
#PF2PAT
process.load("PhysicsTools.PatAlgos.patSequences_cff")
from PhysicsTools.PatAlgos.tools.pfTools import *
from KNUPhy.WAnalyzer.pat_S10_cfg import *
from KNUPhy.WAnalyzer.eventContent_cff import *
from KNUPhy.WAnalyzer.tools import *

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

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

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
	
### taus
process.load("RecoTauTag.Configuration.RecoPFTauTag_cff")

#process.load('RecoJets.JetProducers.PileupJetID_cfi')
#process.pileupJetIdProducer.jets = cms.InputTag('selectedPatJetsPFlow')
#process.pileupJetIdProducer.jets = cms.InputTag('selectedPatJets')

#from KNUPhy.TnP_Muon.common_variables_cff import *
#process.acceptedMuons = cms.EDFilter("PATMuonSelector",
#    src = cms.InputTag("selectedPatMuonsPFlow"),
#    #cut =cms.string("pt > 10 && "+MuonIDFlags.PogTight12.value()), # for Double Mu
#    cut =cms.string("pt > 27 && "+MuonIDFlags.POgTight12.value()), # for W
#    #cut =cms.string("pt > 27 && abs(eta) < 2.1"),
#)
from KNUPhy.CommonTools.muonSelectorPSet_cff import muonSelectorPSet
from KNUPhy.CommonTools.muonIsoSelectorPSet_cff import muonIsoSelectorPSet
process.acceptedMuons = cms.EDProducer("KyMuonSelector",
    # 6(pt>10, tight, for DiMu) 7(pt>27, tight for SingleMu)
    version = cms.untracked.int32( 6 ),# -1(no cut) 0(check cut, isocut pset)
    cut = cms.vstring("pt"),
    isocut = cms.vstring(),
    muonLabel  = cms.InputTag("selectedPatMuonsPFlow"),
    beamSpotLabel = cms.InputTag("offlineBeamSpot"),
    muonIdSelector = muonSelectorPSet,
    muonIsoSelector = muonIsoSelectorPSet,
    saveTree = cms.untracked.bool(False),
    )


### ============= NoPU and MVA MET ===============###
#if produceMVAPFMET or produceNoPUPFMET :
  # Muon Cuts

  #electron

# No PU MET
process.load('JetMETCorrections.METPUSubtraction.noPileUpPFMET_cff')
if runOnMC:
  process.calibratedAK5PFJetsForNoPileUpPFMEt.correctors = cms.vstring('ak5PFL1FastL2L3')
else:
  process.calibratedAK5PFJetsForNoPileUpPFMEt.correctors = cms.vstring('ak5PFL1FastL2L3Residual')

#process.noPileUpPFMEt.srcLeptons = cms.VInputTag(["acceptedElectrons"])

### MVA MET
process.load('JetMETCorrections.METPUSubtraction.mvaPFMET_cff')
if runOnMC:
  process.calibratedAK5PFJetsForPFMEtMVA.correctors = cms.vstring('ak5PFL1FastL2L3')
else:
  process.calibratedAK5PFJetsForPFMEtMVA.correctors = cms.vstring('ak5PFL1FastL2L3Residual')

#process.pfMEtMVA.srcLeptons = cms.VInputTag( ["selectedPatMuons"]) #selectedPatMuons
#process.pfMEtMVA.srcLeptons = cms.VInputTag( ["acceptedElectrons"]) #selectedPatMuons





#process.pfPileUpIsoPFlow.checkClosestZVertex = cms.bool(False)
#process.pfPileUpIso.checkClosestZVertex = cms.bool(False)

#change cone size
#changeConeSize(process,postfix)

#FastJet!
#applyFastJet(process,postfix)

#REMOVE ISOLATION FROM PF2PAT!!!
#addLooseLeptons(process)

# top projections in PF2PAT:
#topProjection(process,postfix)


process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )
#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.patMuonFilter.minNumber = 1

## Source
process.load("KNUPhy.WAnalyzer.Sources.SourceTemplate_cff")

process.out.outputCommands +=pf2patEventContent

process.outpath = cms.EndPath(process.out)
#process.load("KoPFA.CommonTools.recoPFCandCountFilter_cfi")
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

#process.p += process.hltHighLevelMuMuRD
process.p += process.nEventsHLT
process.p += getattr(process,"patPF2PATSequence"+postfix)
process.p += process.acceptedMuons
process.p += process.patMuonFilter
process.p += process.nEventsFiltered
#if produceTaus:
#  process.p += process.recoTauClassicHPSSequence
process.p += process.noPileUpPFMEtSequence
process.p += process.pfMEtMVAsequence

