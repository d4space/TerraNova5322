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
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WplusToMuNu/patTuple_skim_10_2_VTW.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WplusToMuNu/patTuple_skim_11_1_eG4.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WplusToMuNu/patTuple_skim_12_1_uLQ.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WplusToMuNu/patTuple_skim_13_1_aR5.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WplusToMuNu/patTuple_skim_14_1_a1S.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WplusToMuNu/patTuple_skim_15_1_T1i.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WplusToMuNu/patTuple_skim_16_1_8NU.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WplusToMuNu/patTuple_skim_17_1_lwo.root'
)
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('wNTuple_1.root')
)

#process.load("KNUPhy.WAnalyzer.Sources.DYToMuMu_S8_Skim_cff")
#process.load("KNUPhy.WAnalyzer.Sources.WplusToMuNu_S8_8TeV_AODSIM_PatSkim_local_cff")

process.p = cms.Path(
    process.WMuNeuAnalysisMCSequence
)

