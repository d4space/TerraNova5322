import FWCore.ParameterSet.Config as cms

process = cms.Process("wNTuple")

process.load("KNUPhy.WAnalyzer.wAnalysis_MC_cff")

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
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WminusToMuNu/patTuple_skim_50_2_tVk.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WminusToMuNu/patTuple_skim_51_1_2bI.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WminusToMuNu/patTuple_skim_52_1_7gJ.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WminusToMuNu/patTuple_skim_53_3_XiF.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WminusToMuNu/patTuple_skim_54_2_doX.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WminusToMuNu/patTuple_skim_55_2_y7T.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WminusToMuNu/patTuple_skim_56_3_dnl.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WminusToMuNu/patTuple_skim_57_2_RV1.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WminusToMuNu/patTuple_skim_58_2_v0G.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WminusToMuNu/patTuple_skim_59_2_BBB.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WminusToMuNu/patTuple_skim_5_2_eG4.root'
)
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('wNTuple_5.root')
)

#process.load("KNUPhy.WAnalyzer.Sources.DYToMuMu_S8_Skim_cff")
#process.load("KNUPhy.WAnalyzer.Sources.WplusToMuNu_S8_8TeV_AODSIM_PatSkim_local_cff")

process.p = cms.Path(
    process.WMuNeuAnalysisMCSequence
)


