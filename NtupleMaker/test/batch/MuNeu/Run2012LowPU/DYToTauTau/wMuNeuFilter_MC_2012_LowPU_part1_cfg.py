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
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToTauTau/patTuple_skim_10_1_L6M.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToTauTau/patTuple_skim_11_1_cPN.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToTauTau/patTuple_skim_1_1_plb.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToTauTau/patTuple_skim_12_1_ggj.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToTauTau/patTuple_skim_13_1_mLH.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToTauTau/patTuple_skim_14_1_NIk.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToTauTau/patTuple_skim_15_1_H0j.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToTauTau/patTuple_skim_16_1_rnp.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToTauTau/patTuple_skim_17_1_0PZ.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToTauTau/patTuple_skim_18_1_QDo.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToTauTau/patTuple_skim_19_1_p4B.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToTauTau/patTuple_skim_20_1_fx1.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToTauTau/patTuple_skim_21_1_fNe.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToTauTau/patTuple_skim_2_1_cLD.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToTauTau/patTuple_skim_22_1_9VP.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToTauTau/patTuple_skim_23_1_rHU.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToTauTau/patTuple_skim_24_1_Zsj.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToTauTau/patTuple_skim_25_1_u8r.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToTauTau/patTuple_skim_26_1_LxW.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToTauTau/patTuple_skim_27_1_fZV.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToTauTau/patTuple_skim_28_1_HOb.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToTauTau/patTuple_skim_29_1_sqL.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToTauTau/patTuple_skim_30_1_VA6.root'
)
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('wNTuple_1.root')
)
#process.load("TerraNova.NtupleMaker.Sources.DYToMuMu_S8_Skim_cff")
#process.load("TerraNova.NtupleMaker.Sources.WplusToMuNu_S8_8TeV_AODSIM_PatSkim_local_cff")

process.p = cms.Path(
    process.WMuNeuAnalysisMCSequence
)


