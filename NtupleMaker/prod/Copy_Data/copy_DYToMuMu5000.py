import FWCore.ParameterSet.Config as cms
process = cms.Process("PickEvent")
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.source = cms.Source("PoolSource",
        fileNames = cms.untracked.vstring (
'/store/mc/Summer12/DYToMuMu_M-20_CT10_TuneZ2star_8TeV-powheg-pythia6/AODSIM/PU_S8_START52_V9-v2/0000/04A8C6D7-4D98-E111-ABAD-002618943978.root'
            )
        )
process.maxEvents = cms.untracked.PSet(
        input = cms.untracked.int32 (5000)
        )
process.Out = cms.OutputModule("PoolOutputModule",
 fileName = cms.untracked.string ("DYToMuMu_5000.root")
        )
process.end = cms.EndPath(process.Out)

