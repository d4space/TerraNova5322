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
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_464_1_g8f.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_465_1_wlL.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_466_1_lrY.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_467_1_Vu5.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_468_1_hrL.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_469_1_IXb.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_46_1_NNZ.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_470_1_Dce.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_471_1_NJY.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_472_1_DcU.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_473_1_aXz.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_474_1_ISC.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_475_1_YAf.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_476_1_k2I.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_477_1_Adz.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_478_1_c6x.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_479_2_azR.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_47_1_sk2.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_480_1_eur.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_481_1_pCu.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_482_1_BUv.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_483_1_9FC.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_484_2_eBA.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_485_1_9pY.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_486_1_89n.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_487_1_oCD.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_488_1_9Lc.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_489_1_9dm.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_48_1_4Gs.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_490_1_Xw9.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_491_1_Kr0.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_492_1_qFr.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_493_1_woa.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_494_1_hBY.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_495_1_AYf.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_496_1_tgW.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_497_1_zpw.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_498_1_5Xd.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_499_1_JrW.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_49_1_HqU.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_4_1_2H8.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_500_1_Dru.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_501_1_dNL.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_502_1_Eug.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_503_1_0Vo.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_504_1_SGt.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_505_1_07r.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_506_1_LqU.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_507_1_sdI.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_508_1_QRb.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_509_1_9Kk.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_50_1_FgG.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_510_1_tgj.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_511_1_VfL.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_512_1_USK.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_513_1_A8f.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_514_1_FNS.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_515_1_rGF.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_516_1_jjR.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_517_1_7qb.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_518_1_rGF.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_519_1_UU4.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_51_1_P68.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_520_1_NtM.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_521_1_IYl.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_522_1_KgY.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_523_1_POX.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_524_1_CJV.root'
)
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('wNTuple_7.root')
)

#process.load("KNUPhy.WAnalyzer.Sources.DYToMuMu_S8_Skim_cff")
#process.load("KNUPhy.WAnalyzer.Sources.WplusToMuNu_S8_8TeV_AODSIM_PatSkim_local_cff")

process.p = cms.Path(
    process.WMuNeuAnalysisMCSequence
)

