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
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_402_1_TnR.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_403_1_MEB.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_404_1_k8p.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_405_1_Ff9.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_406_1_RWH.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_407_1_Mcl.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_408_2_O5B.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_409_1_qAl.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_40_1_jeD.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_410_1_rY5.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_411_1_Qw2.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_412_1_N2q.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_413_1_3qd.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_414_1_iRL.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_415_1_4zc.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_416_1_Vae.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_417_1_NCg.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_418_1_wpE.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_419_1_ZZP.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_41_1_tkV.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_420_1_bTT.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_421_1_suZ.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_422_1_ZA6.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_423_1_FUp.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_424_1_Ell.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_425_1_oqi.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_426_1_N4P.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_427_1_8PY.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_428_1_wEO.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_429_2_7hn.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_42_1_1D5.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_430_1_Z04.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_431_1_LtH.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_432_1_BWr.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_433_1_ust.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_434_1_0dJ.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_435_1_t2i.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_436_1_YE6.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_437_1_8ZW.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_438_1_RWy.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_439_1_Uru.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_43_1_caH.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_440_1_XBs.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_441_1_iky.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_442_1_6qS.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_443_1_Vts.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_444_1_S9a.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_445_1_0HT.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_446_1_32l.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_447_1_HVj.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_448_1_aBG.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_449_1_JA5.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_44_1_kKL.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_450_1_lsW.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_451_1_DoY.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_452_1_RZV.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_453_1_KPJ.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_454_1_gj9.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_455_1_J8z.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_456_1_5Pr.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_457_1_idQ.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_458_1_g0d.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_459_1_3wm.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_45_1_ZNJ.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_460_1_TSV.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_461_1_aA1.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_462_1_3iY.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/TTJets/patTuple_skim_463_1_Zfr.root'
)
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('wNTuple_6.root')
)

#process.load("KNUPhy.WAnalyzer.Sources.DYToMuMu_S8_Skim_cff")
#process.load("KNUPhy.WAnalyzer.Sources.WplusToMuNu_S8_8TeV_AODSIM_PatSkim_local_cff")

process.p = cms.Path(
    process.WMuNeuAnalysisMCSequence
)

