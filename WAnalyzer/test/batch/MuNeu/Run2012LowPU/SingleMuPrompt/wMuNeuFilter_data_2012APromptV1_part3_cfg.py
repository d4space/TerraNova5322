import FWCore.ParameterSet.Config as cms

process = cms.Process("wNTuple")

process.load("KNUPhy.WAnalyzer.wAnalysis_RD_cff")

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
    fileNames = cms.untracked.vstring(
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/SingleMuPrompt/patTuple_skim_38_1_oct.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/SingleMuPrompt/patTuple_skim_39_1_s71.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/SingleMuPrompt/patTuple_skim_3_1_prn.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/SingleMuPrompt/patTuple_skim_40_1_gqA.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/SingleMuPrompt/patTuple_skim_41_1_BYA.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/SingleMuPrompt/patTuple_skim_42_1_P3x.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/SingleMuPrompt/patTuple_skim_43_1_OQ9.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/SingleMuPrompt/patTuple_skim_44_1_UI5.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/SingleMuPrompt/patTuple_skim_4_1_Mav.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/SingleMuPrompt/patTuple_skim_5_1_Xho.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/SingleMuPrompt/patTuple_skim_6_1_8nH.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/SingleMuPrompt/patTuple_skim_7_1_GT7.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/SingleMuPrompt/patTuple_skim_8_1_Mxu.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/SingleMuPrompt/patTuple_skim_9_1_Q4o.root'
)
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('wNTuple_3.root')
)

#process.load("KNUPhy.WAnalyzer.Sources.Run2012A_SingleMu_PromptV1_AOD_PatSkim_Local_cff")

process.p = cms.Path(
    process.WMuNeuAnalysisRealDataSequence
)

