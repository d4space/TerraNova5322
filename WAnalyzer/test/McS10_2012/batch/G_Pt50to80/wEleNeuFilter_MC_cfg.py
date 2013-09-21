import FWCore.ParameterSet.Config as cms

process = cms.Process("wNTuple")

process.load("KoSMP.WAnalyzer.wAnalysis_MC_cff")


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
#'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/WToTauNu_TuneZ2star_8TeV_pythia6_tauola_cff/S7_WToTauNu_50de11780fc6522573f7cab3fac4808eb7/patTuple_skim_459_1_ToT.root'
'file:dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/jungmin/WToTauNu_TuneZ2star_8TeV_pythia6_tauola_cff/S7_WToTauNu_50/de11780fc6522573f7cab3fac4808eb7/patTuple_skim_459_1_ToT.root'

  #  'file:/d1/scratch/jungmin/cms/CMSSW_5_2_6/src/KoSMP/WAnalyzer/test/batch/EleNeu/DYToEE_highPU/patTuple_skim_1_1_s6C.root',







)
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('wNTuple.root')
)

#process.load("KoSMP.WAnalyzer.Sources.SingleEle_MC_Local_cff")

process.p = cms.Path(
    process.WEleNeuAnalysisMCSequence
)

