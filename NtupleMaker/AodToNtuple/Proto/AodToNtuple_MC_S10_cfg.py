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
process.load('RecoMET.METPUSubtraction.mvaPFMET_leptons_cfi')
# No PU MET
process.load('RecoMET.METPUSubtraction.noPileUpPFMET_cff')
if runOnMC:
  process.calibratedAK5PFJetsForNoPileUpPFMEt.correctors = cms.vstring('ak5PFL1FastL2L3')
else:
  process.calibratedAK5PFJetsForNoPileUpPFMEt.correctors = cms.vstring('ak5PFL1FastL2L3Residual')

process.noPileUpPFMEt.srcLeptons = cms.VInputTag("isomuons","isoelectrons","isotaus")
#process.noPileUpPFMEt.srcLeptons = cms.VInputTag(["METsrcMuons","METsrcElectrons","METsrcTaus"])

### MVA MET
process.load('RecoMET.METPUSubtraction.mvaPFMET_cff')
if runOnMC:
  process.calibratedAK5PFJetsForPFMEtMVA.correctors = cms.vstring('ak5PFL1FastL2L3')
else:
  process.calibratedAK5PFJetsForPFMEtMVA.correctors = cms.vstring('ak5PFL1FastL2L3Residual')

process.pfMEtMVA.srcLeptons = cms.VInputTag( "isomuons","isoelectrons","isotaus") #selectedPatMuons
#process.pfMEtMVA.srcLeptons = cms.VInputTag( ["METsrcMuons","METsrcElectrons","METsrcTaus"]) #selectedPatMuons

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

######### NTuple Chain ###############
process.load("TerraNova.NtupleMaker.NtupleMaker_MC_cff")
#process.TTsemiLept.Channel = cms.untracked.string("Electron")
#process.TTsemiLept.leptonLabel = cms.InputTag("Electrons")
process.TTsemiLept.Channel = cms.untracked.string("Muon")
process.TTsemiLept.leptonLabel = cms.InputTag("Muons")
process.TTsemiLept.JetPtMin = cms.double(30)

process.acceptedMuonsFilter.minNumber = 1
process.patElectronFilter.minNumber = 0


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
process.p += process.acceptedMuons
process.p += process.isomuonseq
#process.p += process.METsrcMuons
#process.p += process.acceptedElectrons
#process.p += process.METsrcElectrons
#process.p += process.acceptedTaus
#process.p += process.METsrcTaus
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
process.p += process.TTsemiLeptMuMCSequence
