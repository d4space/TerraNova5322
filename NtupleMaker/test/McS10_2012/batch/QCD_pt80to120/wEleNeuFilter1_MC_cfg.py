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

'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-80to120_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_120_1_i3M.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-80to120_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_103_1_6Na.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-80to120_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_114_1_Mln.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-80to120_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_24_1_z2m.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-80to120_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_88_1_JIE.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-80to120_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_51_1_buM.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-80to120_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_160_1_mSG.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-80to120_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_97_1_992.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-80to120_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_151_1_uuc.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-80to120_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_145_1_Zf5.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-80to120_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_84_1_3c5.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-80to120_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_183_1_pJd.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-80to120_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_111_1_LxP.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-80to120_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_122_1_EE1.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-80to120_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_15_1_nDn.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-80to120_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_13_1_iJ3.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-80to120_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_55_1_LyU.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-80to120_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_133_1_eAO.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-80to120_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_57_1_WiW.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-80to120_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_113_1_AI5.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-80to120_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_141_1_2NE.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-80to120_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_14_1_ynG.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-80to120_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_199_1_g4R.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-80to120_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_64_1_avV.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-80to120_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_136_1_RqU.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-80to120_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_1_1_La7.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-80to120_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_83_1_Zd8.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-80to120_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_21_1_KGZ.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-80to120_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_110_1_oE3.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-80to120_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_146_1_CxW.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-80to120_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_149_1_IvQ.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-80to120_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_172_1_DDl.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-80to120_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_142_1_gzl.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-80to120_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_191_1_pEt.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-80to120_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_89_1_bYI.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-80to120_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_79_1_TFF.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-80to120_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_163_1_geE.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-80to120_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_109_1_45g.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-80to120_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_170_1_61S.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-80to120_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_95_1_bz1.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-80to120_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_159_1_H1Q.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-80to120_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_123_1_QmK.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-80to120_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_171_1_YTc.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-80to120_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_118_1_mpV.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-80to120_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_68_1_opQ.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-80to120_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_143_1_iFB.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-80to120_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_140_1_Ai4.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-80to120_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_112_1_pqB.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-80to120_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_52_1_1EK.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-80to120_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_53_1_06i.root'





)
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('wNTuple1.root')
)

#process.load("TerraNova.NtupleMaker.Sources.SingleEle_MC_Local_cff")

process.p = cms.Path(
    process.WEleNeuAnalysisMCSequence
)

