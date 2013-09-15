import FWCore.ParameterSet.Config as cms

process = cms.Process("wNTuple")

process.load("KNUPhy.WAnalyzer.wAnalysis_MC_HiPU_MVAnoPU_cff")


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
  'root://eoscms//eos/cms/store/user/shchang/MVANoPUMET_patTuple/ZG_Incl/patTuple_skim_100_1_lhx.root',
  'root://eoscms//eos/cms/store/user/shchang/MVANoPUMET_patTuple/ZG_Incl/patTuple_skim_101_1_gO1.root',
  'root://eoscms//eos/cms/store/user/shchang/MVANoPUMET_patTuple/ZG_Incl/patTuple_skim_102_1_2lT.root',
  'root://eoscms//eos/cms/store/user/shchang/MVANoPUMET_patTuple/ZG_Incl/patTuple_skim_103_1_Mt8.root',
  'root://eoscms//eos/cms/store/user/shchang/MVANoPUMET_patTuple/ZG_Incl/patTuple_skim_104_1_MFj.root',
  'root://eoscms//eos/cms/store/user/shchang/MVANoPUMET_patTuple/ZG_Incl/patTuple_skim_105_1_pGN.root',
  'root://eoscms//eos/cms/store/user/shchang/MVANoPUMET_patTuple/ZG_Incl/patTuple_skim_106_1_uSg.root',
  'root://eoscms//eos/cms/store/user/shchang/MVANoPUMET_patTuple/ZG_Incl/patTuple_skim_107_1_0Ob.root',
  'root://eoscms//eos/cms/store/user/shchang/MVANoPUMET_patTuple/ZG_Incl/patTuple_skim_108_1_0QV.root',
  'root://eoscms//eos/cms/store/user/shchang/MVANoPUMET_patTuple/ZG_Incl/patTuple_skim_109_1_yKs.root',
  'root://eoscms//eos/cms/store/user/shchang/MVANoPUMET_patTuple/ZG_Incl/patTuple_skim_10_1_U6w.root',
  'root://eoscms//eos/cms/store/user/shchang/MVANoPUMET_patTuple/ZG_Incl/patTuple_skim_110_1_hEf.root',
  'root://eoscms//eos/cms/store/user/shchang/MVANoPUMET_patTuple/ZG_Incl/patTuple_skim_111_1_jaA.root',
  'root://eoscms//eos/cms/store/user/shchang/MVANoPUMET_patTuple/ZG_Incl/patTuple_skim_112_1_FX6.root',
  'root://eoscms//eos/cms/store/user/shchang/MVANoPUMET_patTuple/ZG_Incl/patTuple_skim_113_1_B8I.root',
  'root://eoscms//eos/cms/store/user/shchang/MVANoPUMET_patTuple/ZG_Incl/patTuple_skim_114_1_BHq.root',
  'root://eoscms//eos/cms/store/user/shchang/MVANoPUMET_patTuple/ZG_Incl/patTuple_skim_115_1_VfB.root',
  'root://eoscms//eos/cms/store/user/shchang/MVANoPUMET_patTuple/ZG_Incl/patTuple_skim_116_1_uAB.root',
  'root://eoscms//eos/cms/store/user/shchang/MVANoPUMET_patTuple/ZG_Incl/patTuple_skim_117_1_5wP.root',
  'root://eoscms//eos/cms/store/user/shchang/MVANoPUMET_patTuple/ZG_Incl/patTuple_skim_118_1_R5r.root',
  'root://eoscms//eos/cms/store/user/shchang/MVANoPUMET_patTuple/ZG_Incl/patTuple_skim_119_1_SXY.root',
  'root://eoscms//eos/cms/store/user/shchang/MVANoPUMET_patTuple/ZG_Incl/patTuple_skim_11_1_ZW5.root',
  'root://eoscms//eos/cms/store/user/shchang/MVANoPUMET_patTuple/ZG_Incl/patTuple_skim_120_1_BQP.root',
  'root://eoscms//eos/cms/store/user/shchang/MVANoPUMET_patTuple/ZG_Incl/patTuple_skim_121_1_Wa5.root',
  'root://eoscms//eos/cms/store/user/shchang/MVANoPUMET_patTuple/ZG_Incl/patTuple_skim_122_1_Q82.root',
  'root://eoscms//eos/cms/store/user/shchang/MVANoPUMET_patTuple/ZG_Incl/patTuple_skim_123_1_eNw.root',
  'root://eoscms//eos/cms/store/user/shchang/MVANoPUMET_patTuple/ZG_Incl/patTuple_skim_124_1_xnf.root',
  'root://eoscms//eos/cms/store/user/shchang/MVANoPUMET_patTuple/ZG_Incl/patTuple_skim_125_1_Wrj.root',
  'root://eoscms//eos/cms/store/user/shchang/MVANoPUMET_patTuple/ZG_Incl/patTuple_skim_126_1_eyI.root'
)
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('wNTuple.root')
)

process.load("KNUPhy.WAnalyzer.Sources.ZG_Incl_cff")

process.p = cms.Path(
    process.WEleNeuAnalysisMCSequence
)

