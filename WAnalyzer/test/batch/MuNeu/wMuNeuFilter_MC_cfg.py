import FWCore.ParameterSet.Config as cms

process = cms.Process("wNTuple")

process.load("KoSMP.WAnalyzer.wAnalysis_MC_cff")

process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring()
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('wNtupleMC.root')
)

process.load("KoSMP.WAnalyzer.Sources.SingleMu_MC_PatSkim_cff")

#process.muonTriggerFilterForMC.triggerResults = "TriggerResults::HLT"
#process.muonTriggerFilterForMC.matchTriggerPath = cms.untracked.string('HLT_Mu9')

process.p = cms.Path(
    process.WMuNeuAnalysisMCSequence
)

