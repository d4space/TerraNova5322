import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    #noEventSort = cms.untracked.bool(True),
    #duplicateCheckMode = cms.untracked.string("noDouplicateCheck"),
    fileNames = readFiles
    )
readFiles.extend([
   #'file:/terranova_1/Hammid/patTuple_skim_12_1_uOg.root',
   'file:/terranova_1/W_Skim/CMSSW526/MC/Electron/WplusToEleNu_S8/patTuple_skim_9_1_tBs.root',
  ]
  )
