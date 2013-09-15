import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
    )
readFiles.extend([
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_48_0_2OJ.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_49_0_b15.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_4_1_J1D.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_50_0_HKm.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_51_0_mJs.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_52_0_mQP.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_53_0_BeV.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_54_0_w9A.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_55_0_MQw.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_56_0_gqY.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_57_0_GoX.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_58_0_MgQ.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_59_0_GDB.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_5_1_X15.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_60_0_uOg.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_61_0_VC9.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_62_0_SUJ.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_63_0_5lA.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_64_0_kMu.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_65_0_5Bo.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_66_0_1yH.root',
  ]
  )
