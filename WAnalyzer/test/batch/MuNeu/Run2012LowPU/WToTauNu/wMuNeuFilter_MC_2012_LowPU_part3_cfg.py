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
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_42_1_TSj.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_43_1_GRw.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_44_1_Ppi.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_45_1_sUv.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_46_1_mpX.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_47_1_RTV.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_48_1_iD5.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_49_1_hAZ.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_50_1_20B.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_51_1_S6m.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_5_1_JR9.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_52_1_vbD.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_53_1_SSK.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_54_1_XSE.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_55_1_nc6.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_56_1_WCt.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_57_1_SrQ.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_58_1_1PU.root'
)
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('wNTuple_3.root')
)

#process.load("KNUPhy.WAnalyzer.Sources.DYToMuMu_S8_Skim_cff")
#process.load("KNUPhy.WAnalyzer.Sources.WplusToMuNu_S8_8TeV_AODSIM_PatSkim_local_cff")

process.p = cms.Path(
    process.WMuNeuAnalysisMCSequence
)


