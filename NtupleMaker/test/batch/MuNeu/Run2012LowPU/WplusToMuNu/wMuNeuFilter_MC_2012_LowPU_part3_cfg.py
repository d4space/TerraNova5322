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
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WplusToMuNu/patTuple_skim_25_1_9CL.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WplusToMuNu/patTuple_skim_26_1_TwO.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WplusToMuNu/patTuple_skim_27_1_nAD.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WplusToMuNu/patTuple_skim_28_1_Azf.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WplusToMuNu/patTuple_skim_29_1_4gf.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WplusToMuNu/patTuple_skim_2_1_Ofm.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WplusToMuNu/patTuple_skim_30_1_qGy.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WplusToMuNu/patTuple_skim_31_1_iXQ.root'
)
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('wNTuple_3.root')
)

#process.load("KoSMP.WAnalyzer.Sources.DYToMuMu_S8_Skim_cff")
#process.load("KoSMP.WAnalyzer.Sources.WplusToMuNu_S8_8TeV_AODSIM_PatSkim_local_cff")

process.p = cms.Path(
    process.WMuNeuAnalysisMCSequence
)

