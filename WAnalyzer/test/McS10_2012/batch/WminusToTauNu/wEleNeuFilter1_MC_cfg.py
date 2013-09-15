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
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/WminusToTauNu_CT10/jungmin/WminusToTauNu_CT10_TuneZ2star_8TeV-powheg-pythia6/WminusToTauNu_CT10/f782f038489df732fbcd4c59fdd75317/patTuple_skim_40_1_eSL.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/WminusToTauNu_CT10/jungmin/WminusToTauNu_CT10_TuneZ2star_8TeV-powheg-pythia6/WminusToTauNu_CT10/f782f038489df732fbcd4c59fdd75317/patTuple_skim_38_1_0AH.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/WminusToTauNu_CT10/jungmin/WminusToTauNu_CT10_TuneZ2star_8TeV-powheg-pythia6/WminusToTauNu_CT10/f782f038489df732fbcd4c59fdd75317/patTuple_skim_127_1_uRz.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/WminusToTauNu_CT10/jungmin/WminusToTauNu_CT10_TuneZ2star_8TeV-powheg-pythia6/WminusToTauNu_CT10/f782f038489df732fbcd4c59fdd75317/patTuple_skim_58_1_oPq.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/WminusToTauNu_CT10/jungmin/WminusToTauNu_CT10_TuneZ2star_8TeV-powheg-pythia6/WminusToTauNu_CT10/f782f038489df732fbcd4c59fdd75317/patTuple_skim_79_1_uAv.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/WminusToTauNu_CT10/jungmin/WminusToTauNu_CT10_TuneZ2star_8TeV-powheg-pythia6/WminusToTauNu_CT10/f782f038489df732fbcd4c59fdd75317/patTuple_skim_350_1_zEy.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/WminusToTauNu_CT10/jungmin/WminusToTauNu_CT10_TuneZ2star_8TeV-powheg-pythia6/WminusToTauNu_CT10/f782f038489df732fbcd4c59fdd75317/patTuple_skim_386_1_1JH.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/WminusToTauNu_CT10/jungmin/WminusToTauNu_CT10_TuneZ2star_8TeV-powheg-pythia6/WminusToTauNu_CT10/f782f038489df732fbcd4c59fdd75317/patTuple_skim_326_1_uNv.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/WminusToTauNu_CT10/jungmin/WminusToTauNu_CT10_TuneZ2star_8TeV-powheg-pythia6/WminusToTauNu_CT10/f782f038489df732fbcd4c59fdd75317/patTuple_skim_18_1_2H8.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/WminusToTauNu_CT10/jungmin/WminusToTauNu_CT10_TuneZ2star_8TeV-powheg-pythia6/WminusToTauNu_CT10/f782f038489df732fbcd4c59fdd75317/patTuple_skim_328_1_4CR.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/WminusToTauNu_CT10/jungmin/WminusToTauNu_CT10_TuneZ2star_8TeV-powheg-pythia6/WminusToTauNu_CT10/f782f038489df732fbcd4c59fdd75317/patTuple_skim_332_1_YJH.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/WminusToTauNu_CT10/jungmin/WminusToTauNu_CT10_TuneZ2star_8TeV-powheg-pythia6/WminusToTauNu_CT10/f782f038489df732fbcd4c59fdd75317/patTuple_skim_75_1_7XJ.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/WminusToTauNu_CT10/jungmin/WminusToTauNu_CT10_TuneZ2star_8TeV-powheg-pythia6/WminusToTauNu_CT10/f782f038489df732fbcd4c59fdd75317/patTuple_skim_96_1_4nJ.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/WminusToTauNu_CT10/jungmin/WminusToTauNu_CT10_TuneZ2star_8TeV-powheg-pythia6/WminusToTauNu_CT10/f782f038489df732fbcd4c59fdd75317/patTuple_skim_57_1_pnb.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/WminusToTauNu_CT10/jungmin/WminusToTauNu_CT10_TuneZ2star_8TeV-powheg-pythia6/WminusToTauNu_CT10/f782f038489df732fbcd4c59fdd75317/patTuple_skim_95_1_YFD.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/WminusToTauNu_CT10/jungmin/WminusToTauNu_CT10_TuneZ2star_8TeV-powheg-pythia6/WminusToTauNu_CT10/f782f038489df732fbcd4c59fdd75317/patTuple_skim_102_1_2bp.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/WminusToTauNu_CT10/jungmin/WminusToTauNu_CT10_TuneZ2star_8TeV-powheg-pythia6/WminusToTauNu_CT10/f782f038489df732fbcd4c59fdd75317/patTuple_skim_279_1_bqx.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/WminusToTauNu_CT10/jungmin/WminusToTauNu_CT10_TuneZ2star_8TeV-powheg-pythia6/WminusToTauNu_CT10/f782f038489df732fbcd4c59fdd75317/patTuple_skim_281_1_oZC.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/WminusToTauNu_CT10/jungmin/WminusToTauNu_CT10_TuneZ2star_8TeV-powheg-pythia6/WminusToTauNu_CT10/f782f038489df732fbcd4c59fdd75317/patTuple_skim_372_1_6L0.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/WminusToTauNu_CT10/jungmin/WminusToTauNu_CT10_TuneZ2star_8TeV-powheg-pythia6/WminusToTauNu_CT10/f782f038489df732fbcd4c59fdd75317/patTuple_skim_122_1_QyI.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/WminusToTauNu_CT10/jungmin/WminusToTauNu_CT10_TuneZ2star_8TeV-powheg-pythia6/WminusToTauNu_CT10/f782f038489df732fbcd4c59fdd75317/patTuple_skim_291_1_mi0.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/WminusToTauNu_CT10/jungmin/WminusToTauNu_CT10_TuneZ2star_8TeV-powheg-pythia6/WminusToTauNu_CT10/f782f038489df732fbcd4c59fdd75317/patTuple_skim_297_1_wCI.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/WminusToTauNu_CT10/jungmin/WminusToTauNu_CT10_TuneZ2star_8TeV-powheg-pythia6/WminusToTauNu_CT10/f782f038489df732fbcd4c59fdd75317/patTuple_skim_337_1_4ZA.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/WminusToTauNu_CT10/jungmin/WminusToTauNu_CT10_TuneZ2star_8TeV-powheg-pythia6/WminusToTauNu_CT10/f782f038489df732fbcd4c59fdd75317/patTuple_skim_201_1_DmS.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/WminusToTauNu_CT10/jungmin/WminusToTauNu_CT10_TuneZ2star_8TeV-powheg-pythia6/WminusToTauNu_CT10/f782f038489df732fbcd4c59fdd75317/patTuple_skim_97_1_KU1.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/WminusToTauNu_CT10/jungmin/WminusToTauNu_CT10_TuneZ2star_8TeV-powheg-pythia6/WminusToTauNu_CT10/f782f038489df732fbcd4c59fdd75317/patTuple_skim_209_1_c1W.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/WminusToTauNu_CT10/jungmin/WminusToTauNu_CT10_TuneZ2star_8TeV-powheg-pythia6/WminusToTauNu_CT10/f782f038489df732fbcd4c59fdd75317/patTuple_skim_88_1_HMi.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/WminusToTauNu_CT10/jungmin/WminusToTauNu_CT10_TuneZ2star_8TeV-powheg-pythia6/WminusToTauNu_CT10/f782f038489df732fbcd4c59fdd75317/patTuple_skim_27_1_6as.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/WminusToTauNu_CT10/jungmin/WminusToTauNu_CT10_TuneZ2star_8TeV-powheg-pythia6/WminusToTauNu_CT10/f782f038489df732fbcd4c59fdd75317/patTuple_skim_172_1_opK.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/WminusToTauNu_CT10/jungmin/WminusToTauNu_CT10_TuneZ2star_8TeV-powheg-pythia6/WminusToTauNu_CT10/f782f038489df732fbcd4c59fdd75317/patTuple_skim_106_1_ILL.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/WminusToTauNu_CT10/jungmin/WminusToTauNu_CT10_TuneZ2star_8TeV-powheg-pythia6/WminusToTauNu_CT10/f782f038489df732fbcd4c59fdd75317/patTuple_skim_272_1_u0N.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/WminusToTauNu_CT10/jungmin/WminusToTauNu_CT10_TuneZ2star_8TeV-powheg-pythia6/WminusToTauNu_CT10/f782f038489df732fbcd4c59fdd75317/patTuple_skim_246_1_4Yw.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/WminusToTauNu_CT10/jungmin/WminusToTauNu_CT10_TuneZ2star_8TeV-powheg-pythia6/WminusToTauNu_CT10/f782f038489df732fbcd4c59fdd75317/patTuple_skim_338_1_RK9.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/WminusToTauNu_CT10/jungmin/WminusToTauNu_CT10_TuneZ2star_8TeV-powheg-pythia6/WminusToTauNu_CT10/f782f038489df732fbcd4c59fdd75317/patTuple_skim_355_1_c7m.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/WminusToTauNu_CT10/jungmin/WminusToTauNu_CT10_TuneZ2star_8TeV-powheg-pythia6/WminusToTauNu_CT10/f782f038489df732fbcd4c59fdd75317/patTuple_skim_237_1_S9H.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/WminusToTauNu_CT10/jungmin/WminusToTauNu_CT10_TuneZ2star_8TeV-powheg-pythia6/WminusToTauNu_CT10/f782f038489df732fbcd4c59fdd75317/patTuple_skim_327_1_f5M.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/WminusToTauNu_CT10/jungmin/WminusToTauNu_CT10_TuneZ2star_8TeV-powheg-pythia6/WminusToTauNu_CT10/f782f038489df732fbcd4c59fdd75317/patTuple_skim_363_1_p8N.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/WminusToTauNu_CT10/jungmin/WminusToTauNu_CT10_TuneZ2star_8TeV-powheg-pythia6/WminusToTauNu_CT10/f782f038489df732fbcd4c59fdd75317/patTuple_skim_331_1_xYD.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/WminusToTauNu_CT10/jungmin/WminusToTauNu_CT10_TuneZ2star_8TeV-powheg-pythia6/WminusToTauNu_CT10/f782f038489df732fbcd4c59fdd75317/patTuple_skim_105_1_Fqv.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/WminusToTauNu_CT10/jungmin/WminusToTauNu_CT10_TuneZ2star_8TeV-powheg-pythia6/WminusToTauNu_CT10/f782f038489df732fbcd4c59fdd75317/patTuple_skim_254_1_CcT.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/WminusToTauNu_CT10/jungmin/WminusToTauNu_CT10_TuneZ2star_8TeV-powheg-pythia6/WminusToTauNu_CT10/f782f038489df732fbcd4c59fdd75317/patTuple_skim_255_1_ye7.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/WminusToTauNu_CT10/jungmin/WminusToTauNu_CT10_TuneZ2star_8TeV-powheg-pythia6/WminusToTauNu_CT10/f782f038489df732fbcd4c59fdd75317/patTuple_skim_334_1_j1E.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/WminusToTauNu_CT10/jungmin/WminusToTauNu_CT10_TuneZ2star_8TeV-powheg-pythia6/WminusToTauNu_CT10/f782f038489df732fbcd4c59fdd75317/patTuple_skim_349_1_kQK.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/WminusToTauNu_CT10/jungmin/WminusToTauNu_CT10_TuneZ2star_8TeV-powheg-pythia6/WminusToTauNu_CT10/f782f038489df732fbcd4c59fdd75317/patTuple_skim_360_1_Kvt.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/WminusToTauNu_CT10/jungmin/WminusToTauNu_CT10_TuneZ2star_8TeV-powheg-pythia6/WminusToTauNu_CT10/f782f038489df732fbcd4c59fdd75317/patTuple_skim_149_1_MvF.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/WminusToTauNu_CT10/jungmin/WminusToTauNu_CT10_TuneZ2star_8TeV-powheg-pythia6/WminusToTauNu_CT10/f782f038489df732fbcd4c59fdd75317/patTuple_skim_170_1_LmX.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/WminusToTauNu_CT10/jungmin/WminusToTauNu_CT10_TuneZ2star_8TeV-powheg-pythia6/WminusToTauNu_CT10/f782f038489df732fbcd4c59fdd75317/patTuple_skim_211_1_61j.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/WminusToTauNu_CT10/jungmin/WminusToTauNu_CT10_TuneZ2star_8TeV-powheg-pythia6/WminusToTauNu_CT10/f782f038489df732fbcd4c59fdd75317/patTuple_skim_42_1_BFy.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/WminusToTauNu_CT10/jungmin/WminusToTauNu_CT10_TuneZ2star_8TeV-powheg-pythia6/WminusToTauNu_CT10/f782f038489df732fbcd4c59fdd75317/patTuple_skim_333_1_uoq.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/DATA/MC/Summer12/DR53X-PU_S10_START53_V7A/7/WminusToTauNu_CT10/jungmin/WminusToTauNu_CT10_TuneZ2star_8TeV-powheg-pythia6/WminusToTauNu_CT10/f782f038489df732fbcd4c59fdd75317/patTuple_skim_397_1_xbh.root'





)
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('wNTuple1.root')
)

#process.load("KNUPhy.WAnalyzer.Sources.SingleEle_MC_Local_cff")

process.p = cms.Path(
    process.WEleNeuAnalysisMCSequence
)

