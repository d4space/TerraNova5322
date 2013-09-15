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
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToTauTau/patTuple_skim_5_1_ZZi.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToTauTau/patTuple_skim_52_1_XlS.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToTauTau/patTuple_skim_53_1_E8E.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToTauTau/patTuple_skim_54_1_cUr.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToTauTau/patTuple_skim_55_1_eId.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToTauTau/patTuple_skim_56_1_mVr.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToTauTau/patTuple_skim_57_1_B7M.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToTauTau/patTuple_skim_58_1_VWU.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToTauTau/patTuple_skim_59_1_PKR.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToTauTau/patTuple_skim_60_1_pAC.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToTauTau/patTuple_skim_61_1_EqS.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToTauTau/patTuple_skim_6_1_SsI.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToTauTau/patTuple_skim_62_1_UCa.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToTauTau/patTuple_skim_63_1_M5r.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToTauTau/patTuple_skim_64_1_He9.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToTauTau/patTuple_skim_65_1_eEN.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToTauTau/patTuple_skim_66_1_dGg.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToTauTau/patTuple_skim_67_1_ArJ.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToTauTau/patTuple_skim_7_1_OnC.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToTauTau/patTuple_skim_8_1_zNm.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToTauTau/patTuple_skim_9_1_a7d.root'
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


