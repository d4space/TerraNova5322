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
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_525_1_clB.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_526_1_03q.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_527_1_r7t.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_528_1_A5X.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_529_1_5PB.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_52_1_0M9.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_530_1_4nB.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_531_1_PMZ.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_532_1_zkY.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_533_1_cb7.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_534_1_7g2.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_535_1_6PN.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_536_1_tJa.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_537_1_UbU.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_538_1_SSo.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_539_1_W2g.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_53_1_R1L.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_540_1_1j9.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_541_1_UTO.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_542_1_hLS.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_543_1_Nt4.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_544_1_Q03.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_545_1_ImC.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_546_1_3Pf.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_547_1_7L8.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_548_1_sQ4.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_549_1_Xl0.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_54_1_omX.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_550_1_mgd.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_551_1_mLK.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_552_1_arg.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_553_1_1RL.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_554_1_LO5.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_555_1_Erq.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_556_1_DT4.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_557_1_1OM.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_558_1_e1a.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_559_1_SKc.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_55_1_C2l.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_560_1_Mqo.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_561_1_pGh.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_562_1_0Fh.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_563_1_TIg.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_564_1_i6z.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_565_1_6vy.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_566_1_fUt.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_567_1_RVk.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_568_1_zkb.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_569_1_MqA.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_56_1_i9R.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_570_1_q3j.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_571_1_H0f.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_572_1_YMG.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_573_1_xR3.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_574_1_K4B.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_575_1_iN6.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_576_1_ka6.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_577_1_uIP.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_578_1_KkQ.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_579_1_fpL.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_57_1_CCz.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_580_1_waB.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_581_1_4OP.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_582_1_DhS.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_583_1_dN2.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_584_1_cJD.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_585_1_ZsS.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_586_1_Mrf.root'
)
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('wNTuple_8.root')
)

#process.load("KNUPhy.WAnalyzer.Sources.DYToMuMu_S8_Skim_cff")
#process.load("KNUPhy.WAnalyzer.Sources.WplusToMuNu_S8_8TeV_AODSIM_PatSkim_local_cff")

process.p = cms.Path(
    process.WMuNeuAnalysisMCSequence
)

