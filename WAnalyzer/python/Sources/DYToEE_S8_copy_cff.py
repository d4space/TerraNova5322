import FWCore.ParameterSet.Config as cms
readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    fileNames = readFiles
    )
readFiles.extend([
  'file:/terranova_1/MC_Sample/DYToEE_copy_5000_events/DYToEE_5000_copy_1_1_MQr.root',
  ]
  )
