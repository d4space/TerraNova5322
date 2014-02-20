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
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToTauTau/patTuple_skim_31_1_yRU.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToTauTau/patTuple_skim_3_1_kyX.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToTauTau/patTuple_skim_32_1_PDx.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToTauTau/patTuple_skim_33_2_Ge7.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToTauTau/patTuple_skim_34_1_LP3.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToTauTau/patTuple_skim_35_1_3bT.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToTauTau/patTuple_skim_36_1_Eds.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToTauTau/patTuple_skim_37_1_9z1.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToTauTau/patTuple_skim_38_1_Fud.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToTauTau/patTuple_skim_39_1_fC8.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToTauTau/patTuple_skim_40_1_tTv.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToTauTau/patTuple_skim_41_1_mpa.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToTauTau/patTuple_skim_4_1_dvs.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToTauTau/patTuple_skim_42_1_Mfq.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToTauTau/patTuple_skim_43_1_wqD.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToTauTau/patTuple_skim_44_1_wsh.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToTauTau/patTuple_skim_45_1_uT0.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToTauTau/patTuple_skim_46_1_Bcr.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToTauTau/patTuple_skim_47_1_deH.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToTauTau/patTuple_skim_48_1_nTh.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToTauTau/patTuple_skim_49_1_0gS.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToTauTau/patTuple_skim_50_1_AVU.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToTauTau/patTuple_skim_51_1_LZv.root'
)
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('wNTuple_2.root')
)

#process.load("TerraNova.NtupleMaker.Sources.DYToMuMu_S8_Skim_cff")
#process.load("TerraNova.NtupleMaker.Sources.WplusToMuNu_S8_8TeV_AODSIM_PatSkim_local_cff")

process.p = cms.Path(
    process.WMuNeuAnalysisMCSequence
)


