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
#'file:/d2/scratch/khakim/WAnalysis/NoPuMET/CMSSW_5_3_9/src/KNUPhy/WAnalyzer/NoPUtest/WToENu/patTuple_skim.root'
'file:/afs/cern.ch/work/s/salee/public/NoPuMET/CMSSW_5_3_9/src/KNUPhy/WAnalyzer/NoPUtest/WToENu/patTuple_skim.root'
#'file:/afs/cern.ch/work/k/kbutanov/public/NoPuMET/CMSSW_5_3_9/src/KNUPhy/WAnalyzer/NoPUtest/WToENu/patTuple_skim.root'
)
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('wNTuple.root')
)

#process.load("KNUPhy.WAnalyzer.Sources.SingleEle_MC_Local_cff")

process.p = cms.Path(
    process.WEleNeuAnalysisMCSequence
)

