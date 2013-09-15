import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    #noEventSort = cms.untracked.bool(True),
    #duplicateCheckMode = cms.untracked.string("noDouplicateCheck"),
    fileNames = readFiles
    )
readFiles.extend([
   #'file:/terranova_1/Hammid/patTuple_skim_12_1_uOg.root',
   'file:/terranova_1/W_Skim/CMSSW526/MC/Muon/WplusToMuNu_S8/patTuple_skim_WpMuNu_AccptTest.root',
   #'file:/terranova_1/W_Skim/CMSSW526/MC/Muon/WplusToMuNu_S8/patTuple_skim.root',
   #'file:/terranova_1/W_Skim/MC/Wplus_LowPU_S8/patTuple_skim.root',
  ]
  )
