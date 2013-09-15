import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    #noEventSort = cms.untracked.bool(True),
    #duplicateCheckMode = cms.untracked.string("noDouplicateCheck"),
    fileNames = readFiles
    )
readFiles.extend([
   'file:/terranova_1/MC_Sample/W_LowPU_S8/WplusToMuNu_AODSIM_1_1_2YJ.root',
  ]
  )
