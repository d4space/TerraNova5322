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

'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/QCD_Pt-120to170/jungmin/QCD_Pt-120to170_TuneZ2star_8TeV_pythia6/QCD_Pt-120to170/f782f038489df732fbcd4c59fdd75317/patTuple_skim_383_0_mSE.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/QCD_Pt-120to170/jungmin/QCD_Pt-120to170_TuneZ2star_8TeV_pythia6/QCD_Pt-120to170/f782f038489df732fbcd4c59fdd75317/patTuple_skim_354_0_YvZ.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/QCD_Pt-120to170/jungmin/QCD_Pt-120to170_TuneZ2star_8TeV_pythia6/QCD_Pt-120to170/f782f038489df732fbcd4c59fdd75317/patTuple_skim_58_1_Btc.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/QCD_Pt-120to170/jungmin/QCD_Pt-120to170_TuneZ2star_8TeV_pythia6/QCD_Pt-120to170/f782f038489df732fbcd4c59fdd75317/patTuple_skim_466_0_4bA.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/QCD_Pt-120to170/jungmin/QCD_Pt-120to170_TuneZ2star_8TeV_pythia6/QCD_Pt-120to170/f782f038489df732fbcd4c59fdd75317/patTuple_skim_335_0_QYi.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/QCD_Pt-120to170/jungmin/QCD_Pt-120to170_TuneZ2star_8TeV_pythia6/QCD_Pt-120to170/f782f038489df732fbcd4c59fdd75317/patTuple_skim_187_1_6X0.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/QCD_Pt-120to170/jungmin/QCD_Pt-120to170_TuneZ2star_8TeV_pythia6/QCD_Pt-120to170/f782f038489df732fbcd4c59fdd75317/patTuple_skim_410_0_1rD.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/QCD_Pt-120to170/jungmin/QCD_Pt-120to170_TuneZ2star_8TeV_pythia6/QCD_Pt-120to170/f782f038489df732fbcd4c59fdd75317/patTuple_skim_290_1_Cuc.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/QCD_Pt-120to170/jungmin/QCD_Pt-120to170_TuneZ2star_8TeV_pythia6/QCD_Pt-120to170/f782f038489df732fbcd4c59fdd75317/patTuple_skim_150_1_d1n.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/QCD_Pt-120to170/jungmin/QCD_Pt-120to170_TuneZ2star_8TeV_pythia6/QCD_Pt-120to170/f782f038489df732fbcd4c59fdd75317/patTuple_skim_442_0_MUt.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/QCD_Pt-120to170/jungmin/QCD_Pt-120to170_TuneZ2star_8TeV_pythia6/QCD_Pt-120to170/f782f038489df732fbcd4c59fdd75317/patTuple_skim_257_1_Zw5.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/QCD_Pt-120to170/jungmin/QCD_Pt-120to170_TuneZ2star_8TeV_pythia6/QCD_Pt-120to170/f782f038489df732fbcd4c59fdd75317/patTuple_skim_32_1_5SZ.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/QCD_Pt-120to170/jungmin/QCD_Pt-120to170_TuneZ2star_8TeV_pythia6/QCD_Pt-120to170/f782f038489df732fbcd4c59fdd75317/patTuple_skim_384_0_bgh.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/QCD_Pt-120to170/jungmin/QCD_Pt-120to170_TuneZ2star_8TeV_pythia6/QCD_Pt-120to170/f782f038489df732fbcd4c59fdd75317/patTuple_skim_413_0_KoF.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/QCD_Pt-120to170/jungmin/QCD_Pt-120to170_TuneZ2star_8TeV_pythia6/QCD_Pt-120to170/f782f038489df732fbcd4c59fdd75317/patTuple_skim_582_1_QWe.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/QCD_Pt-120to170/jungmin/QCD_Pt-120to170_TuneZ2star_8TeV_pythia6/QCD_Pt-120to170/f782f038489df732fbcd4c59fdd75317/patTuple_skim_422_0_NfC.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/QCD_Pt-120to170/jungmin/QCD_Pt-120to170_TuneZ2star_8TeV_pythia6/QCD_Pt-120to170/f782f038489df732fbcd4c59fdd75317/patTuple_skim_404_0_Y7i.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/QCD_Pt-120to170/jungmin/QCD_Pt-120to170_TuneZ2star_8TeV_pythia6/QCD_Pt-120to170/f782f038489df732fbcd4c59fdd75317/patTuple_skim_46_1_6Vu.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/QCD_Pt-120to170/jungmin/QCD_Pt-120to170_TuneZ2star_8TeV_pythia6/QCD_Pt-120to170/f782f038489df732fbcd4c59fdd75317/patTuple_skim_279_1_Km6.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/QCD_Pt-120to170/jungmin/QCD_Pt-120to170_TuneZ2star_8TeV_pythia6/QCD_Pt-120to170/f782f038489df732fbcd4c59fdd75317/patTuple_skim_546_1_zfH.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/QCD_Pt-120to170/jungmin/QCD_Pt-120to170_TuneZ2star_8TeV_pythia6/QCD_Pt-120to170/f782f038489df732fbcd4c59fdd75317/patTuple_skim_325_1_Owe.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/QCD_Pt-120to170/jungmin/QCD_Pt-120to170_TuneZ2star_8TeV_pythia6/QCD_Pt-120to170/f782f038489df732fbcd4c59fdd75317/patTuple_skim_349_0_YjD.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/QCD_Pt-120to170/jungmin/QCD_Pt-120to170_TuneZ2star_8TeV_pythia6/QCD_Pt-120to170/f782f038489df732fbcd4c59fdd75317/patTuple_skim_207_1_dRf.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/QCD_Pt-120to170/jungmin/QCD_Pt-120to170_TuneZ2star_8TeV_pythia6/QCD_Pt-120to170/f782f038489df732fbcd4c59fdd75317/patTuple_skim_105_1_8x9.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/QCD_Pt-120to170/jungmin/QCD_Pt-120to170_TuneZ2star_8TeV_pythia6/QCD_Pt-120to170/f782f038489df732fbcd4c59fdd75317/patTuple_skim_423_0_Hqd.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/QCD_Pt-120to170/jungmin/QCD_Pt-120to170_TuneZ2star_8TeV_pythia6/QCD_Pt-120to170/f782f038489df732fbcd4c59fdd75317/patTuple_skim_214_1_60v.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/QCD_Pt-120to170/jungmin/QCD_Pt-120to170_TuneZ2star_8TeV_pythia6/QCD_Pt-120to170/f782f038489df732fbcd4c59fdd75317/patTuple_skim_73_1_wbk.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/QCD_Pt-120to170/jungmin/QCD_Pt-120to170_TuneZ2star_8TeV_pythia6/QCD_Pt-120to170/f782f038489df732fbcd4c59fdd75317/patTuple_skim_493_0_udP.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/QCD_Pt-120to170/jungmin/QCD_Pt-120to170_TuneZ2star_8TeV_pythia6/QCD_Pt-120to170/f782f038489df732fbcd4c59fdd75317/patTuple_skim_163_2_fgG.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/QCD_Pt-120to170/jungmin/QCD_Pt-120to170_TuneZ2star_8TeV_pythia6/QCD_Pt-120to170/f782f038489df732fbcd4c59fdd75317/patTuple_skim_489_0_2wz.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/QCD_Pt-120to170/jungmin/QCD_Pt-120to170_TuneZ2star_8TeV_pythia6/QCD_Pt-120to170/f782f038489df732fbcd4c59fdd75317/patTuple_skim_554_1_S17.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/QCD_Pt-120to170/jungmin/QCD_Pt-120to170_TuneZ2star_8TeV_pythia6/QCD_Pt-120to170/f782f038489df732fbcd4c59fdd75317/patTuple_skim_563_1_K6p.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/QCD_Pt-120to170/jungmin/QCD_Pt-120to170_TuneZ2star_8TeV_pythia6/QCD_Pt-120to170/f782f038489df732fbcd4c59fdd75317/patTuple_skim_537_1_laN.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/QCD_Pt-120to170/jungmin/QCD_Pt-120to170_TuneZ2star_8TeV_pythia6/QCD_Pt-120to170/f782f038489df732fbcd4c59fdd75317/patTuple_skim_419_0_efh.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/QCD_Pt-120to170/jungmin/QCD_Pt-120to170_TuneZ2star_8TeV_pythia6/QCD_Pt-120to170/f782f038489df732fbcd4c59fdd75317/patTuple_skim_85_1_6LN.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/QCD_Pt-120to170/jungmin/QCD_Pt-120to170_TuneZ2star_8TeV_pythia6/QCD_Pt-120to170/f782f038489df732fbcd4c59fdd75317/patTuple_skim_463_0_364.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/QCD_Pt-120to170/jungmin/QCD_Pt-120to170_TuneZ2star_8TeV_pythia6/QCD_Pt-120to170/f782f038489df732fbcd4c59fdd75317/patTuple_skim_435_0_a92.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/QCD_Pt-120to170/jungmin/QCD_Pt-120to170_TuneZ2star_8TeV_pythia6/QCD_Pt-120to170/f782f038489df732fbcd4c59fdd75317/patTuple_skim_276_2_FIi.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/QCD_Pt-120to170/jungmin/QCD_Pt-120to170_TuneZ2star_8TeV_pythia6/QCD_Pt-120to170/f782f038489df732fbcd4c59fdd75317/patTuple_skim_388_0_LW4.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/QCD_Pt-120to170/jungmin/QCD_Pt-120to170_TuneZ2star_8TeV_pythia6/QCD_Pt-120to170/f782f038489df732fbcd4c59fdd75317/patTuple_skim_524_0_Xv0.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/QCD_Pt-120to170/jungmin/QCD_Pt-120to170_TuneZ2star_8TeV_pythia6/QCD_Pt-120to170/f782f038489df732fbcd4c59fdd75317/patTuple_skim_566_1_Uoj.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/QCD_Pt-120to170/jungmin/QCD_Pt-120to170_TuneZ2star_8TeV_pythia6/QCD_Pt-120to170/f782f038489df732fbcd4c59fdd75317/patTuple_skim_368_0_H8M.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/QCD_Pt-120to170/jungmin/QCD_Pt-120to170_TuneZ2star_8TeV_pythia6/QCD_Pt-120to170/f782f038489df732fbcd4c59fdd75317/patTuple_skim_527_1_tAA.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/QCD_Pt-120to170/jungmin/QCD_Pt-120to170_TuneZ2star_8TeV_pythia6/QCD_Pt-120to170/f782f038489df732fbcd4c59fdd75317/patTuple_skim_376_0_ol6.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/QCD_Pt-120to170/jungmin/QCD_Pt-120to170_TuneZ2star_8TeV_pythia6/QCD_Pt-120to170/f782f038489df732fbcd4c59fdd75317/patTuple_skim_38_1_CDa.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/QCD_Pt-120to170/jungmin/QCD_Pt-120to170_TuneZ2star_8TeV_pythia6/QCD_Pt-120to170/f782f038489df732fbcd4c59fdd75317/patTuple_skim_97_1_jDr.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/QCD_Pt-120to170/jungmin/QCD_Pt-120to170_TuneZ2star_8TeV_pythia6/QCD_Pt-120to170/f782f038489df732fbcd4c59fdd75317/patTuple_skim_331_0_Ujq.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/QCD_Pt-120to170/jungmin/QCD_Pt-120to170_TuneZ2star_8TeV_pythia6/QCD_Pt-120to170/f782f038489df732fbcd4c59fdd75317/patTuple_skim_487_0_UoL.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/QCD_Pt-120to170/jungmin/QCD_Pt-120to170_TuneZ2star_8TeV_pythia6/QCD_Pt-120to170/f782f038489df732fbcd4c59fdd75317/patTuple_skim_202_1_UPT.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/QCD_Pt-120to170/jungmin/QCD_Pt-120to170_TuneZ2star_8TeV_pythia6/QCD_Pt-120to170/f782f038489df732fbcd4c59fdd75317/patTuple_skim_375_0_F5M.root'





)
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('wNTuple1.root')
)

#process.load("TerraNova.NtupleMaker.Sources.SingleEle_MC_Local_cff")

process.p = cms.Path(
    process.WEleNeuAnalysisMCSequence
)

