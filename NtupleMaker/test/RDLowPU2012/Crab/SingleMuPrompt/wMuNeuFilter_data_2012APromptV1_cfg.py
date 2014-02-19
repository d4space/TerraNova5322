import FWCore.ParameterSet.Config as cms

process = cms.Process("wNTuple")

process.load("KoSMP.WAnalyzer.wAnalysis_RD_cff")

process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(3000) )
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

#process.load("KoSMP.WAnalyzer.Sources.Run2012A_SingleMu_PromptV1_AOD_PatSkim_Local_cff")

process.p = cms.Path(
    process.WMuNeuAnalysisRealDataSequence
)

