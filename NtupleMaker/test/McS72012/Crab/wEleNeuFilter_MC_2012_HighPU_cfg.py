import FWCore.ParameterSet.Config as cms

process = cms.Process("wNTuple")
process.load("TerraNova.NtupleMaker.wAnalysis_MC_cff")

process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

#process.load("FWCore.MessageLogger.MessageLogger_cfi")
#process.MessageLogger = cms.Service("MessageLogger")
#process.MessageLogger.destinations = ['cout']
#process.MessageLogger.cout = cms.untracked.PSet(
#    threshold = cms.untracked.string('INFO'),
#    FwkReport = cms.untracked.PSet(reportEvery=cms.untracked.int32(1000))
#)

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring()
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('wNTuple.root')
)

#process.load("TerraNova.NtupleMaker.Sources.WplusToMuNu_S8_7TeV_AODSIM_PatSkim_local_cff")

process.p = cms.Path(
    process.WEleNeuAnalysisMCSequence
)

