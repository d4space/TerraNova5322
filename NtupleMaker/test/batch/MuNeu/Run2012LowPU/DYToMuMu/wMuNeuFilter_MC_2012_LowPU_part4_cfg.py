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
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_2_1_90T.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_30_1_oiN.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_31_1_Oep.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_32_1_lmO.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_33_1_PRT.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_34_1_gxm.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_35_1_G9S.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_36_1_GuL.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_37_1_vfb.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_38_1_4V5.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_39_1_FUq.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_3_1_3Et.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_40_1_hKu.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_41_1_ilA.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_42_1_oaa.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_43_1_FB9.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_44_1_xqj.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_45_1_lSg.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_46_1_ybX.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_47_1_INY.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_48_1_VhR.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_49_1_LvU.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_4_1_Tsx.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_50_1_t84.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_51_1_jTv.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_52_1_azq.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_53_1_jJa.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_54_1_0t6.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_55_1_oy8.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_56_1_dk4.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_57_1_v0E.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_58_1_Rqw.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_59_1_X1f.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_5_1_DXm.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_60_1_R97.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_61_1_jXx.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_62_1_oGt.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_63_1_XFk.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_64_1_Afr.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_65_1_5G2.root'
)
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('wNTuple_4.root')
)

#process.load("KoSMP.WAnalyzer.Sources.DYToMuMu_S8_Skim_cff")
#process.load("KoSMP.WAnalyzer.Sources.WplusToMuNu_S8_8TeV_AODSIM_PatSkim_local_cff")

process.p = cms.Path(
    process.WMuNeuAnalysisMCSequence
)

