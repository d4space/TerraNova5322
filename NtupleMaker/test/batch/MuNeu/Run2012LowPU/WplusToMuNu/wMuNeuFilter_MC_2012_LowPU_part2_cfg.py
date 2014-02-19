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
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WplusToMuNu/patTuple_skim_18_1_HAZ.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WplusToMuNu/patTuple_skim_19_1_IeF.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WplusToMuNu/patTuple_skim_1_1_brT.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WplusToMuNu/patTuple_skim_20_1_XA0.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WplusToMuNu/patTuple_skim_21_1_8iU.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WplusToMuNu/patTuple_skim_22_1_HOF.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WplusToMuNu/patTuple_skim_23_1_NC6.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WplusToMuNu/patTuple_skim_24_1_M96.root'
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

