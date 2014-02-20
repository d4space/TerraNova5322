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
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_66_1_A7l.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_67_1_7Ug.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_68_1_M3o.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_69_1_CpY.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_6_1_inA.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_70_1_y4D.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_71_1_Yya.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_72_1_dRt.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_73_1_FxW.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_74_1_Ixp.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_75_1_nl7.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_76_1_GcK.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_77_1_KRV.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_78_1_REQ.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_79_1_scb.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_7_1_rja.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_80_1_Fmb.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_81_1_N2m.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_82_1_V4X.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_83_1_5wJ.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_84_1_1vt.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_85_1_m7B.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_86_1_WXV.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_87_1_igN.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_88_1_aNa.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_89_1_7kP.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_8_1_EeP.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_90_1_5Rr.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_91_1_nIq.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_92_1_Bwz.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_93_1_jor.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_94_1_dkw.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_95_1_oRt.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_96_1_Iw0.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_97_1_IiI.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_98_1_Lhy.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_99_1_NmV.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_9_1_cpe.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_136_1_1GV.root'
)
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('wNTuple_5.root')
)

#process.load("TerraNova.NtupleMaker.Sources.DYToMuMu_S8_Skim_cff")
#process.load("TerraNova.NtupleMaker.Sources.WplusToMuNu_S8_8TeV_AODSIM_PatSkim_local_cff")

process.p = cms.Path(
    process.WMuNeuAnalysisMCSequence
)

