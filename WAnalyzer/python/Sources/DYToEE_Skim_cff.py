import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    #noEventSort = cms.untracked.bool(True),
    #duplicateCheckMode = cms.untracked.string("noDouplicateCheck"),
    fileNames = readFiles
    )
readFiles.extend([
   #'file:/terranova_1/Hammid/patTuple_skim_12_1_uOg.root',
   'file:/terranova_1/W_Skim/MC/CMSSW_5_2_6/DYToEE/patTuple_skim.root',
  ]
  )
