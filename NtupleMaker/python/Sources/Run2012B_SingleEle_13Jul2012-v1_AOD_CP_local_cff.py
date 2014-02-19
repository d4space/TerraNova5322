import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    #noEventSort = cms.untracked.bool(True),
    #duplicateCheckMode = cms.untracked.string("noDouplicateCheck"),
    fileNames = readFiles
    )
readFiles.extend([
'file:/afs/cern.ch/work/t/taehoon/public/DATA/RD/2012/SingleElectron_Run2012B_13Jul2012-v1_AOD.root'
  ]
  )
