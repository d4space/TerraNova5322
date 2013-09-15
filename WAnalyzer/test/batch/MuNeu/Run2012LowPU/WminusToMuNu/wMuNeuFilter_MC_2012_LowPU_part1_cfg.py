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
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WminusToMuNu/patTuple_skim_10_3_YMo.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WminusToMuNu/patTuple_skim_11_1_bZC.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WminusToMuNu/patTuple_skim_12_4_kW2.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WminusToMuNu/patTuple_skim_13_2_x88.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WminusToMuNu/patTuple_skim_14_5_2Tx.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WminusToMuNu/patTuple_skim_15_1_CEj.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WminusToMuNu/patTuple_skim_16_1_HCi.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WminusToMuNu/patTuple_skim_17_1_avc.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WminusToMuNu/patTuple_skim_18_2_WPH.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WminusToMuNu/patTuple_skim_19_1_jqQ.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WminusToMuNu/patTuple_skim_1_1_XdI.root'
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


