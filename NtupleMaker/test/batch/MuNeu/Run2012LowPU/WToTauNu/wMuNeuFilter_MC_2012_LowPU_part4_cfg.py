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
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_59_1_v7C.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_60_1_cs8.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_61_1_wqv.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_6_1_Z8H.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_62_1_zNd.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_63_1_4KH.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_64_1_309.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_65_1_iQn.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_66_1_TbJ.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_67_1_Zby.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_68_1_VZK.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_69_1_leY.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_70_1_Uns.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_7_1_12I.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_71_1_lfO.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_72_1_C9W.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_8_1_QKz.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_9_1_Sht.root'
)
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('wNTuple_4.root')
)

#process.load("TerraNova.NtupleMaker.Sources.DYToMuMu_S8_Skim_cff")
#process.load("TerraNova.NtupleMaker.Sources.WplusToMuNu_S8_8TeV_AODSIM_PatSkim_local_cff")

process.p = cms.Path(
    process.WMuNeuAnalysisMCSequence
)


