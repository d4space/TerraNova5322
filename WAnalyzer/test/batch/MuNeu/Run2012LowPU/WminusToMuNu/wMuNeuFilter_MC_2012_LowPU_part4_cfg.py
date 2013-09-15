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
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WminusToMuNu/patTuple_skim_40_3_LCJ.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WminusToMuNu/patTuple_skim_41_1_8Wm.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WminusToMuNu/patTuple_skim_42_3_Nd4.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WminusToMuNu/patTuple_skim_43_1_8Dy.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WminusToMuNu/patTuple_skim_44_1_6IZ.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WminusToMuNu/patTuple_skim_45_1_8IE.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WminusToMuNu/patTuple_skim_46_1_GLh.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WminusToMuNu/patTuple_skim_47_3_jGf.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WminusToMuNu/patTuple_skim_48_2_HYL.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WminusToMuNu/patTuple_skim_49_1_yZR.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WminusToMuNu/patTuple_skim_4_1_czv.root'
)
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('wNTuple_4.root')
)

#process.load("KNUPhy.WAnalyzer.Sources.DYToMuMu_S8_Skim_cff")
#process.load("KNUPhy.WAnalyzer.Sources.WplusToMuNu_S8_8TeV_AODSIM_PatSkim_local_cff")

process.p = cms.Path(
    process.WMuNeuAnalysisMCSequence
)


