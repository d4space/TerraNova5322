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
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_587_1_CzC.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_588_1_BiK.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_589_1_1Qs.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_58_1_DmG.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_590_1_zqA.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_591_1_tck.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_592_1_W1o.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_593_1_872.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_594_1_mBB.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_595_1_FN6.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_596_1_9Qd.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_597_1_TR4.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_598_1_iPG.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_599_1_1eh.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_59_1_sVb.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_5_1_tsS.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_600_1_JHW.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_601_1_ZAm.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_602_1_0xp.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_603_1_TyM.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_604_2_fwo.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_605_1_ebm.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_606_1_wpO.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_607_1_vng.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_608_1_CJn.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_609_1_I3U.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_60_1_wZA.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_610_1_9WW.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_611_1_6DX.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_612_1_7EQ.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_613_1_wEG.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_614_1_OV3.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_615_1_Jox.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_616_1_80V.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_617_1_qAS.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_618_1_UPY.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_619_1_0lj.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_61_1_EML.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_620_1_LBZ.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_621_1_xk8.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_622_1_Q9l.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_623_1_1Mp.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_624_1_hMg.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_625_1_xyO.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_626_1_NMb.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_627_1_VGX.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_628_1_2Tt.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_629_2_VYX.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_62_1_2wG.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_630_1_Ffn.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_631_1_MRQ.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_632_1_pO2.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_633_1_q8a.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_634_1_yo8.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_635_1_uyI.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_636_1_iYP.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_637_1_4zJ.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_638_1_AvD.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_639_1_7Wf.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_63_1_Y6I.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_640_1_mbv.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_641_1_yUG.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_642_1_65F.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_643_1_aqH.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_644_1_n0N.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_645_1_lGt.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_646_1_Gqk.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_647_1_bMU.root'
)
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('wNTuple_9.root')
)

#process.load("KNUPhy.WAnalyzer.Sources.DYToMuMu_S8_Skim_cff")
#process.load("KNUPhy.WAnalyzer.Sources.WplusToMuNu_S8_8TeV_AODSIM_PatSkim_local_cff")

process.p = cms.Path(
    process.WMuNeuAnalysisMCSequence
)

