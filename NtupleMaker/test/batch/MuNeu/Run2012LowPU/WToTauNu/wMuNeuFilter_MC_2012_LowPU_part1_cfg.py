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
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_10_1_pZ0.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_11_1_8gA.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_1_1_9Oq.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_12_1_ImL.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_13_1_4GM.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_14_1_mVX.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_15_1_SD9.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_16_1_hzH.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_17_1_ped.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_18_1_k4Y.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_19_1_Qqs.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_20_1_CvX.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_21_1_0Ur.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_2_1_G7n.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_22_1_5zb.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_23_1_Xfa.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_24_1_nev.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_25_1_Cxm.root'
)
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('wNTuple_1.root')
)

#process.load("KoSMP.WAnalyzer.Sources.DYToMuMu_S8_Skim_cff")
#process.load("KoSMP.WAnalyzer.Sources.WplusToMuNu_S8_8TeV_AODSIM_PatSkim_local_cff")

process.p = cms.Path(
    process.WMuNeuAnalysisMCSequence
)


