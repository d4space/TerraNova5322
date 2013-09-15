import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
    )
readFiles.extend([
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_100_0_85Q.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_101_0_ObU.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_102_0_b0w.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_103_0_eqw.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_104_0_aIv.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_105_0_vDp.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_106_0_AO5.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_107_0_tQR.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_108_0_ysy.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_109_0_fhM.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_10_1_n13.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_110_0_FB6.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_111_0_cgy.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_112_0_V0W.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_113_0_9So.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_114_0_zkO.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_115_0_8J0.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_116_0_MCq.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_117_0_etp.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_118_0_POG.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_119_0_amA.root',
  ]
  )
