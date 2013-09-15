
import FWCore.ParameterSet.Config as cms
process = cms.Process("PickEvent")
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.source = cms.Source("PoolSource",
	fileNames = cms.untracked.vstring (
#	    "/store/relval/CMSSW_4_1_3/RelValTTbar/GEN-SIM-RECO/START311_V2-v1/0038/12763BEE-5A52-E011-8988-003048679048.root"
'/store/relval/CMSSW_4_2_3/RelValTTbar/GEN-SIM-RECO/START42_V12-v2/0062/728877FF-717B-E011-9989-00261894395B.root'
	    )
	)
process.maxEvents = cms.untracked.PSet(
	input = cms.untracked.int32 (100)
	)
process.Out = cms.OutputModule("PoolOutputModule",
	fileName = cms.untracked.string ("reco_copy.root")
	)

process.end = cms.EndPath(process.Out)


