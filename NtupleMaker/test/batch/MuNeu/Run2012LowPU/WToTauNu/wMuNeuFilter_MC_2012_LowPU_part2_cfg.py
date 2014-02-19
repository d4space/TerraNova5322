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
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_26_1_Yq5.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_27_1_FCs.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_28_1_c6s.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_29_1_e7g.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_30_1_CiL.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_31_1_wna.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_3_1_l5Y.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_32_1_XlA.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_33_1_48u.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_34_1_Nqn.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_35_1_E04.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_36_1_UfK.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_37_1_dlh.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_38_1_oBF.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_39_1_VBf.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_40_1_uXh.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_41_1_82s.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/WToTauNu/patTuple_skim_4_1_6wo.root'
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


