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
    fileNames = cms.untracked.vstring(
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/SingleMuPrompt/patTuple_skim_10_1_UQ8.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/SingleMuPrompt/patTuple_skim_11_1_C4G.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/SingleMuPrompt/patTuple_skim_12_1_9cs.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/SingleMuPrompt/patTuple_skim_13_1_Bcq.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/SingleMuPrompt/patTuple_skim_14_1_SFP.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/SingleMuPrompt/patTuple_skim_15_1_WCk.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/SingleMuPrompt/patTuple_skim_16_1_uUC.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/SingleMuPrompt/patTuple_skim_17_1_GQq.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/SingleMuPrompt/patTuple_skim_18_1_kHQ.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/SingleMuPrompt/patTuple_skim_19_1_Jkn.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/SingleMuPrompt/patTuple_skim_1_1_H1v.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/SingleMuPrompt/patTuple_skim_20_1_3xw.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/SingleMuPrompt/patTuple_skim_21_1_Qbo.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/SingleMuPrompt/patTuple_skim_22_1_AcO.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/SingleMuPrompt/patTuple_skim_23_1_pGt.root'
)
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('wNTuple_1.root')
)

#process.load("KoSMP.WAnalyzer.Sources.Run2012A_SingleMu_PromptV1_AOD_PatSkim_Local_cff")

process.p = cms.Path(
    process.WMuNeuAnalysisRealDataSequence
)

