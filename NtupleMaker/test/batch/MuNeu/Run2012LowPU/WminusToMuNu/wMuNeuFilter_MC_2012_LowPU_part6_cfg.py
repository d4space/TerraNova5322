import FWCore.ParameterSet.Config as cms

process = cms.Process("wNTuple")

process.load("TerraNova.NtupleMaker.wAnalysis_MC_cff")

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
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WminusToMuNu/patTuple_skim_60_2_6Ch.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WminusToMuNu/patTuple_skim_61_2_6FO.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WminusToMuNu/patTuple_skim_62_1_fkW.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WminusToMuNu/patTuple_skim_63_1_77a.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WminusToMuNu/patTuple_skim_64_2_iPd.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WminusToMuNu/patTuple_skim_65_2_KTH.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WminusToMuNu/patTuple_skim_66_1_rM5.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WminusToMuNu/patTuple_skim_6_2_6o1.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WminusToMuNu/patTuple_skim_7_1_t08.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WminusToMuNu/patTuple_skim_8_1_R1I.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WminusToMuNu/patTuple_skim_9_1_KZ8.root'
)
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('wNTuple_6.root')
)

#process.load("TerraNova.NtupleMaker.Sources.DYToMuMu_S8_Skim_cff")
#process.load("TerraNova.NtupleMaker.Sources.WplusToMuNu_S8_8TeV_AODSIM_PatSkim_local_cff")

process.p = cms.Path(
    process.WMuNeuAnalysisMCSequence
)


