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

'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-50to80_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_439_1_fxY.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-50to80_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_107_1_3rT.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-50to80_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_503_1_YHh.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-50to80_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_147_1_Cpo.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-50to80_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_483_1_Aqh.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-50to80_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_194_1_fE6.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-50to80_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_87_1_XOV.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-50to80_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_528_1_abG.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-50to80_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_578_1_vRo.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-50to80_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_17_1_RvX.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-50to80_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_458_1_ku9.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-50to80_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_464_1_sJY.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-50to80_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_36_1_AKj.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-50to80_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_175_1_wp7.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-50to80_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_193_1_1Cy.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-50to80_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_581_1_0bo.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-50to80_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_114_1_Jpq.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-50to80_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_21_1_CZf.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-50to80_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_486_1_A8f.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-50to80_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_594_1_psN.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-50to80_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_513_1_Szr.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-50to80_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_532_1_xBB.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-50to80_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_56_1_nNk.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-50to80_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_506_1_3PB.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-50to80_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_505_1_Zng.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-50to80_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_61_1_KpQ.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-50to80_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_514_1_OhF.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-50to80_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_539_1_Ymj.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-50to80_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_417_1_xIS.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-50to80_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_12_1_O4h.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-50to80_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_411_1_Qhu.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-50to80_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_434_1_AaG.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-50to80_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_159_1_SCd.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-50to80_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_149_1_8M3.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-50to80_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_436_1_1ds.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-50to80_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_39_1_FMp.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-50to80_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_51_1_Gq4.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-50to80_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_409_1_xqz.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-50to80_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_122_1_NGn.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-50to80_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_151_1_rga.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-50to80_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_429_1_vWz.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-50to80_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_160_1_4xj.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-50to80_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_444_1_B13.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-50to80_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_29_1_mr6.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-50to80_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_154_1_J7B.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-50to80_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_66_1_scK.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-50to80_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_99_1_46F.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-50to80_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_580_1_8Dg.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-50to80_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_576_1_Wa5.root',
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/QCD_Pt-50to80_TuneZ2star_8TeV_pythia6/S10_START53/f782f038489df732fbcd4c59fdd75317/patTuple_skim_597_1_gOC.root'





)
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('wNTuple1.root')
)

#process.load("TerraNova.NtupleMaker.Sources.SingleEle_MC_Local_cff")

process.p = cms.Path(
    process.WEleNeuAnalysisMCSequence
)

