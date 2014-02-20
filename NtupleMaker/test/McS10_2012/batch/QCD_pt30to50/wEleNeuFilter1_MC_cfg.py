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

'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-30to50_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_280_2_fRI.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-30to50_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_111_2_VAB.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-30to50_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_261_2_T0x.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-30to50_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_260_2_a6G.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-30to50_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_11_2_TEo.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-30to50_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_489_2_ktJ.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-30to50_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_539_2_pe0.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-30to50_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_247_2_9Ey.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-30to50_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_270_2_wPW.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-30to50_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_233_2_PDo.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-30to50_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_572_2_lmv.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-30to50_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_589_2_vGJ.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-30to50_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_88_2_6VX.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-30to50_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_278_2_YaY.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-30to50_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_476_2_iXT.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-30to50_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_36_2_ZyB.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-30to50_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_135_2_OvB.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-30to50_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_534_2_S1C.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-30to50_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_55_2_ywH.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-30to50_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_92_2_K4h.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-30to50_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_491_2_mxH.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-30to50_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_561_2_JIk.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-30to50_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_600_2_Fti.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-30to50_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_264_2_hwS.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-30to50_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_85_2_yBn.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-30to50_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_250_2_Ntn.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-30to50_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_529_2_yyt.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-30to50_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_31_2_QHg.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-30to50_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_543_2_tlh.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-30to50_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_58_2_Jhq.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-30to50_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_305_2_y9x.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-30to50_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_340_2_RP6.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-30to50_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_105_2_UF7.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-30to50_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_336_2_Zhe.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-30to50_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_400_2_vS8.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-30to50_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_222_2_Y1r.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-30to50_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_497_2_3c2.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-30to50_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_585_2_4t6.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-30to50_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_258_2_Gi1.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-30to50_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_30_2_kXP.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-30to50_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_249_2_lq5.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-30to50_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_86_2_plO.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-30to50_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_295_2_itK.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-30to50_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_342_2_pEb.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-30to50_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_217_2_ZCE.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-30to50_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_160_2_UI3.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-30to50_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_27_2_k55.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-30to50_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_259_2_LWF.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-30to50_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_273_2_cLh.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-30to50_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_337_2_wZE.root'





)
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('wNTuple1.root')
)

#process.load("TerraNova.NtupleMaker.Sources.SingleEle_MC_Local_cff")

process.p = cms.Path(
    process.WEleNeuAnalysisMCSequence
)

