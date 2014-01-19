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

process.load("KoSMP.WAnalyzer.pf2pat_template_MC_cfg")
#PF2PAT
process.load("PhysicsTools.PatAlgos.patSequences_cff")
from PhysicsTools.PatAlgos.tools.pfTools import *
from KoSMP.WAnalyzer.pat_22Jan2013_MC_cfg import *
from KoSMP.WAnalyzer.eventContent_cff import *
from KoSMP.WAnalyzer.tools import *

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
process.load("KoSMP.WAnalyzer.Sources.SourceTemplate_cff")

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
# 6(pt>10, tight, use for DiMu) 7(pt>27, tight, use for SingleMu)
# -1(no cut) 0(check cut, isocut pset)
process.METsrcMuons.version = cms.untracked.int32(6)
# -1(no cut), 0(check cut, isocut pset), 1(WptCut)
# 13(medium pt 30) 14(medium pt 15)
process.METsrcElectrons.version = cms.untracked.int32(14)
### taus
process.load("RecoTauTag.Configuration.RecoPFTauTag_cff")

#process.load('RecoJets.JetProducers.PileupJetID_cfi')
#process.pileupJetIdProducer.jets = cms.InputTag('selectedPatJetsPFlow')
#process.pileupJetIdProducer.jets = cms.InputTag('selectedPatJets')

### ============= NoPU and MVA MET ===============###
#if produceMVAPFMET or produceNoPUPFMET :
#  # Muon Cuts
#  IN_ACCEPTANCE = '(abs(eta)<2.4 && pt>=19)'
#  TRACK_CUTS = "? track ? track.numberOfValidHits > 10 :0"
#  GLB_CUTS = "isGlobalMuon && isTrackerMuon && muonID('GlobalMuonPromptTight')"
#
#  #electron
#  Ele_ACCEPTANCE = '(pt >= 19 && abs(eta)<2.5)'
#  Ele_Id = 'abs(deltaPhiSuperClusterTrackAtVtx)<0.9 && abs(deltaEtaSuperClusterTrackAtVtx)<0.02 && scSigmaIEtaIEta<0.03 && hadronicOverEm<0.15' 
#  Else_Iso = 'dr03TkSumPt/pt < 0.30'
#    
#  process.selectedPatMuons.cut = cms.string("(abs(eta)<2.4 && pt>=15)&&isGlobalMuon && isTrackerMuon && globalTrack.normalizedChi2 < 10 && muonID(\'TrackerMuonArbitrated\') && globalTrack.hitPattern.numberOfValidMuonHits > 0 && trackIso/pt < 0.3")
#  process.selectedPatElectrons.cut = Ele_ACCEPTANCE+"&&"+Ele_Id+"&&"+Else_Iso

# No PU MET
process.load('RecoMET.METPUSubtraction.noPileUpPFMET_cff')
if runOnMC:
  process.calibratedAK5PFJetsForNoPileUpPFMEt.correctors = cms.vstring('ak5PFL1FastL2L3')
else:
  process.calibratedAK5PFJetsForNoPileUpPFMEt.correctors = cms.vstring('ak5PFL1FastL2L3Residual')

process.noPileUpPFMEt.srcLeptons = cms.VInputTag(["METsrcMuons","METsrcElectrons","METsrcTaus"])

### MVA MET
process.load('RecoMET.METPUSubtraction.mvaPFMET_cff')
if runOnMC:
  process.calibratedAK5PFJetsForPFMEtMVA.correctors = cms.vstring('ak5PFL1FastL2L3')
else:
  process.calibratedAK5PFJetsForPFMEtMVA.correctors = cms.vstring('ak5PFL1FastL2L3Residual')

process.pfMEtMVA.srcLeptons = cms.VInputTag( ["METsrcMuons","METsrcElectrons","METsrcTaus"]) #selectedPatMuons

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

#process.acceptedMuons.cut = cms.string("pt > 20 && abs(eta) < 2.5 && (chargedHadronIso + neutralHadronIso + photonIso)/pt < 0.05")

process.patMuonFilter.minNumber = 1
process.patElectronFilter.minNumber = 0


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

if produceTaus:
  process.p += process.recoTauClassicHPSSequence
  print "Using Tau Sequence =================================="
#process.p += process.hltHighLevelMuMuRD
process.p += process.nEventsHLT
process.p += getattr(process,"patPF2PATSequence"+postfix)
#process.p += process.looseLeptonSequence
process.p += process.acceptedMuons
process.p += process.METsrcMuons
#process.p += process.acceptedElectrons
process.p += process.METsrcElectrons
#process.p += process.acceptedTaus
process.p += process.METsrcTaus
#process.p += process.patMuEleTauFilter
process.p += process.patMuonFilter
#process.p += process.patElectronFilter
#process.p += process.patTauFilter
process.p += process.nEventsFiltered
process.p += process.noPileUpPFMEtSequence
process.p += process.pfMEtMVAsequence
