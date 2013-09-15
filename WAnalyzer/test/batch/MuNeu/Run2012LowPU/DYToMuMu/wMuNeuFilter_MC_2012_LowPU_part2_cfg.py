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
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_138_1_An8.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_139_1_Oex.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_13_1_vl8.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_140_1_vVK.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_141_1_61H.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_142_1_AWd.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_143_1_k7D.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_144_1_hpW.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_145_1_Gr4.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_146_1_Lgn.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_147_1_hUS.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_148_1_ALO.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_149_1_XtD.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_14_1_fkx.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_150_1_rmV.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_151_1_inO.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_152_1_bEP.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_153_1_JLS.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_154_1_Gx7.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_155_1_uoa.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_156_1_2Hl.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_157_1_IOx.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_158_1_z52.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_159_1_A8q.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_15_1_D6U.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_160_1_K6G.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_161_1_MpK.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_162_1_9qB.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_163_1_dWp.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_164_1_yvg.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_165_1_zHJ.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_166_1_IyR.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_167_1_lpz.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_168_1_CEK.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_169_1_Q7Q.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_16_1_UYO.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_170_1_Ela.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_171_1_6ww.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_172_1_huI.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_173_1_jWe.root'
)
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('wNTuple_2.root')
)

#process.load("KNUPhy.WAnalyzer.Sources.DYToMuMu_S8_Skim_cff")
#process.load("KNUPhy.WAnalyzer.Sources.WplusToMuNu_S8_8TeV_AODSIM_PatSkim_local_cff")

process.p = cms.Path(
    process.WMuNeuAnalysisMCSequence
)

