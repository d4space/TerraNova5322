import FWCore.ParameterSet.Config as cms
import os
# Options
produceTaus=True

runOnMC=True
postfix = "PFlow"
jetAlgo="AK5"

produceNoPUPFMET=True
produceMVAPFMET=True

process = cms.Process("PAT")

#PF2PAT
process.load("PhysicsTools.PatAlgos.patSequences_cff")
from PhysicsTools.PatAlgos.tools.pfTools import *
from TerraNova.NtupleMaker.pat_S10_cfg import *
from TerraNova.NtupleMaker.eventContent_cff import *
process.load("TerraNova.NtupleMaker.pf2pat_template_MC_MVaNoPuMEt_cfg")
#from TerraNova.NtupleMaker.tools import *

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

#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

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


# Pre Settings ######################
# 6(pt>10, tight, for DiMu) 7(pt>27, tight for SingleMu)
# -1(no cut) 0(check cut, isocut pset)
process.acceptedMuons.version = cms.untracked.int32(7)
# -1(no cut), 0(check cut, isocut pset), 1(WptCut)
# 13(medium pt 30) 14(medium pt 15)
process.acceptedElectrons.version = cms.untracked.int32(13)
### taus
process.load("RecoTauTag.Configuration.RecoPFTauTag_cff")

#process.load('RecoJets.JetProducers.PileupJetID_cfi')
#process.pileupJetIdProducer.jets = cms.InputTag('selectedPatJetsPFlow')
#process.pileupJetIdProducer.jets = cms.InputTag('selectedPatJets')

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

process.noPileUpPFMEt.srcLeptons = cms.VInputTag(["acceptedMuons","acceptedElectrons","acceptedTaus"])

### MVA MET
process.load('JetMETCorrections.METPUSubtraction.mvaPFMET_cff')
if runOnMC:
  process.calibratedAK5PFJetsForPFMEtMVA.correctors = cms.vstring('ak5PFL1FastL2L3')
else:
  process.calibratedAK5PFJetsForPFMEtMVA.correctors = cms.vstring('ak5PFL1FastL2L3Residual')

process.pfMEtMVA.srcLeptons = cms.VInputTag( ["acceptedMuons","acceptedElectrons","acceptedTaus"]) #selectedPatMuons

### genMEtTrue + genMEtCalo + genMEtCaloAndNonPrompt
process.load("RecoMET.Configuration.GenMETParticles_cff")
process.load("RecoJets.Configuration.GenJetParticles_cff")

process.load("RecoMET.METProducers.genMetCalo_cfi")
process.load("RecoMET.METProducers.genMetCaloAndNonPrompt_cfi")
process.load("RecoMET.METProducers.genMetTrue_cfi")

process.genMetTrue.onlyFiducialParticles =cms.bool(True)
process.recoGenMET = cms.Sequence(process.genMetCalo+process.genMetCaloAndNonPrompt+process.genMetTrue)


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


#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.patMuonFilter.minNumber = 1

## Source
#process.load("TerraNova.NtupleMaker.Sources.SourceTemplate_cff")
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
      'dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/mc/Summer12_DR53X/WJetsToLNu_TuneZ2Star_8TeV-madgraph-tarball/AODSIM/PU_S10_START53_V7A-v2/0004/B0ABDF71-F9F2-E111-8B0E-0025B3E063A6.root'
      )
    )

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
#    process.recoGenMET
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
process.p += process.acceptedMuons
process.p += process.acceptedElectrons
process.p += process.acceptedTaus
process.p += process.patObjectCountFilter
#process.p += process.patMuonFilter
#process.p += process.patElectronFilter
#process.p += process.patTauFilter
process.p += process.nEventsFiltered
process.p += process.noPileUpPFMEtSequence
process.p += process.pfMEtMVAsequence
process.p += process.genMETParticles
process.p += process.genJetParticles
process.p += process.recoGenMET

