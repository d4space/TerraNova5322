import FWCore.ParameterSet.Config as cms

process = cms.Process("wAcceptance")



process.load("TerraNova.NtupleMaker.wAnalysis_MC_cff")

process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(2127666) )
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

#process.load("FWCore.MessageLogger.MessageLogger_cfi")
#process.MessageLogger = cms.Service("MessageLogger")
#process.MessageLogger.destinations = ['cout']
#process.MessageLogger.cout = cms.untracked.PSet(
#    threshold = cms.untracked.string('INFO'),
#    FwkReport = cms.untracked.PSet(reportEvery=cms.untracked.int32(1000))
#)


# Printout of generator information for the first event
process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
process.printGenParticles = cms.EDAnalyzer("ParticleListDrawer",
    maxEventsToPrint = cms.untracked.int32(10),
    printVertex = cms.untracked.bool(False),
    src = cms.InputTag("genParticles")
    )


process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
#      'dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/mc/Summer12/WminusToENu_CT10_TuneZ2star_8TeV-powheg-pythia6/AODSIM/PU_S8_START52_V9-v2/0000/02C22DEA-7F98-E111-8AF9-00304867929E.root'
      )
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('wAcceptance.root')
)

#process.load("TerraNova.NtupleMaker.Sources.DYToMuMu_S8_Skim_cff")
#process.load("TerraNova.NtupleMaker.Sources.WplusToMuNu_AODSIM_CP_local_cff")
#process.load("TerraNova.NtupleMaker.Sources.WplusToMuNu_S8_8TeV_AODSIM_PatSkim_local_cff")
process.nEventsTotal = cms.EDProducer("EventCountProducer")

process.p = cms.Path(
    process.nEventsTotal *
    process.WAcceptanceElectron
)

