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
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_100_1_V8d.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_101_1_Vc4.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_102_1_5ov.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_103_3_nQs.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_104_1_Q8Y.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_105_1_PUK.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_106_1_c1u.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_107_1_rMd.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_108_1_DcB.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_109_1_062.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_10_1_nmJ.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_110_1_POk.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_111_1_TeY.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_112_4_Ea8.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_113_3_Yz1.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_114_1_aSf.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_115_1_VYa.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_116_1_Sz1.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_117_1_IFj.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_118_1_daK.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_119_1_k9D.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_11_1_EIt.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_120_1_0D7.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_121_1_0M7.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_122_1_TeV.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_123_1_g73.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_124_1_xzF.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_125_1_cFe.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_126_1_t3P.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_127_1_5XM.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_128_1_KZ8.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_129_1_Qnj.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_12_1_xPI.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_130_1_pR0.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_131_1_aTi.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_132_1_qB0.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_133_1_YTf.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_134_1_4a6.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_135_1_wJ9.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_137_2_mVW.root'
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

