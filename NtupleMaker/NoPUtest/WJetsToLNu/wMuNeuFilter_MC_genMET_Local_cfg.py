import FWCore.ParameterSet.Config as cms
process = cms.Process("wNTuple")
process.load("TerraNova.NtupleMaker.wAnalysis_MC_HiPU_MVAnoPU_cff")


process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.source = cms.Source("PoolSource", 
    fileNames = cms.untracked.vstring(
      'file:/afs/cern.ch/user/k/kbutanov/patTuple_skim_558_1_pZA.root',
)
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('wNTuple.root')
)

process.p = cms.Path(
    process.WMuNeuAnalysisMCSequence
)
