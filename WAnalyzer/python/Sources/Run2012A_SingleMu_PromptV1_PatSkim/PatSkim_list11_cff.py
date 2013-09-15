import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
    )
readFiles.extend([
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_67_0_QRz.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_68_0_ks8.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_69_0_4Bo.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_6_1_GDj.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_70_0_ed5.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_71_0_Ynk.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_72_0_eiB.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_73_0_5Fq.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_74_0_6Ac.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_75_0_u6k.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_76_0_yQH.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_77_0_1QD.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_78_0_fnc.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_79_0_XdL.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_7_1_9YX.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_80_0_DZn.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_81_0_sxM.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_82_0_xvp.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_83_0_KrA.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_84_0_fSC.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_85_0_mLU.root',
  ]
  )
