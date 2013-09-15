import FWCore.ParameterSet.Config as cms
readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    fileNames = readFiles
    )
readFiles.extend([
  'file:/terranova_1/Real_Sample/eventCopy_SingleEle_PromptReco/PrmptRD_5000_copy_2_2_HVB.root',
  'file:/terranova_1/Real_Sample/eventCopy_SingleEle_PromptReco/PrmptRD_5000_copy_4_2_wpi.root',
  ]
  )
