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
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_100_1_yWS.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_101_1_h7t.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_102_1_5dh.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_103_1_qYf.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_104_1_r1h.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_105_1_wfE.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_106_1_zQZ.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_107_1_K35.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_108_1_cQ8.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_109_1_NCH.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_10_1_iXj.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_110_1_k3c.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_111_1_RAP.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_112_1_b1A.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_113_1_NAA.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_114_1_csY.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_115_1_n6b.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_116_1_X7Q.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_117_2_4Uz.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_118_1_E4A.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_119_1_1JE.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_11_1_GpU.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_120_1_6KW.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_121_1_r7S.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_122_1_1a6.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_123_1_52F.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_124_1_8Mr.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_125_2_qIi.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_126_1_SkE.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_127_1_oP0.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_128_1_4Xv.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_129_1_vc3.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_12_1_w7s.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_130_1_mz6.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_131_1_Sj5.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_132_1_0bw.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_133_1_3KA.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_134_1_eVZ.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_135_1_CSL.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_136_1_uG4.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_137_1_o0z.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_138_1_5Qu.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_139_1_O85.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_13_1_OaQ.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_140_1_5vO.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_141_1_HEO.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_142_1_Q1U.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_143_1_4Gu.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_144_1_6Po.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_145_1_rdg.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_146_1_MQG.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_147_1_B1Z.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_148_1_xaN.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_149_1_w1a.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_14_1_VMd.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_150_1_s82.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_151_1_C9f.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_152_1_QV1.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_153_1_YvW.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_154_1_omG.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_155_1_M31.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_156_1_5rE.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_157_1_vqI.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_158_1_MCH.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_159_1_aMG.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_15_1_vG9.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_160_1_IUD.root'
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

