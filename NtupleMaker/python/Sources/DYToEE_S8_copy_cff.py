import FWCore.ParameterSet.Config as cms
readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    fileNames = readFiles
    )
readFiles.extend([
  'file:/afs/cern.ch/work/k/kbutanov/public/DYToEE_S8_1000/DYToEE_M-20_CT10_S8_AODSIM_1000_1_1_mX2.root',
  #'file:/afs/cern.ch/work/s/salee/DataSample/S8/DYToEE_5000_copy_1_1_MQr.root',
  #'file:/terranova_1/MC_Sample/DYToEE_copy_5000_events/DYToEE_5000_copy_1_1_MQr.root',
  ]
  )
