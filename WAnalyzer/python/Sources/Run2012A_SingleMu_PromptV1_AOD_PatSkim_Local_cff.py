import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
    )
readFiles.extend([
   'file:/terranova_1/W_Skim/Real/SingleMu_Run2012A_PromptReco_Test/patTuple_skim.root',
  ]
  )
