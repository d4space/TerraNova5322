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
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WminusToMuNu/patTuple_skim_20_1_I9A.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WminusToMuNu/patTuple_skim_21_1_HNU.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WminusToMuNu/patTuple_skim_22_2_HB0.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WminusToMuNu/patTuple_skim_23_3_H84.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WminusToMuNu/patTuple_skim_24_2_NZo.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WminusToMuNu/patTuple_skim_25_2_tVT.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WminusToMuNu/patTuple_skim_26_2_bbW.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WminusToMuNu/patTuple_skim_27_1_bya.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WminusToMuNu/patTuple_skim_28_6_wCy.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WminusToMuNu/patTuple_skim_29_1_H4F.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WminusToMuNu/patTuple_skim_2_1_NdC.root'
)
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('wNTuple_2.root')
)

#process.load("KoSMP.WAnalyzer.Sources.DYToMuMu_S8_Skim_cff")
#process.load("KoSMP.WAnalyzer.Sources.WplusToMuNu_S8_8TeV_AODSIM_PatSkim_local_cff")

process.p = cms.Path(
    process.WMuNeuAnalysisMCSequence
)


