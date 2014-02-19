import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
    )
readFiles.extend([
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_211_0_f2U.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_212_0_nnE.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_213_0_Fnv.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_214_0_oYn.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_215_0_zvb.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_216_0_EFq.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_217_0_jMb.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_218_0_KwH.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_219_0_y92.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_21_1_y16.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_220_0_JJJ.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_221_0_S5s.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_222_0_Thc.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_223_0_l5m.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_224_0_WmN.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_225_0_UbH.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_226_0_eul.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_227_0_WIR.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_228_0_NAz.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_229_0_Grt.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_22_1_55i.root',
  ]
  )
