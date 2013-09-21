import FWCore.ParameterSet.Config as cms

process = cms.Process("wNTuple")

process.load("KoSMP.WAnalyzer.wAnalysis_MC_cff")

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
    fileNames = cms.untracked.vstring(
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WplusToMuNu/patTuple_skim_32_1_Qle.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WplusToMuNu/patTuple_skim_3_1_bms.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WplusToMuNu/patTuple_skim_4_1_Jx0.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WplusToMuNu/patTuple_skim_5_1_7r9.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WplusToMuNu/patTuple_skim_6_2_arp.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WplusToMuNu/patTuple_skim_7_1_a5U.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WplusToMuNu/patTuple_skim_8_5_mYJ.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WplusToMuNu/patTuple_skim_9_1_LOy.root'
)
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('wNTuple_4.root')
)

#process.load("KoSMP.WAnalyzer.Sources.DYToMuMu_S8_Skim_cff")
#process.load("KoSMP.WAnalyzer.Sources.WplusToMuNu_S8_8TeV_AODSIM_PatSkim_local_cff")

process.p = cms.Path(
    process.WMuNeuAnalysisMCSequence
)

