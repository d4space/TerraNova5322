import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
    )
readFiles.extend([
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_194_0_XMi.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_195_0_WMS.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_196_0_9wp.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_197_0_yij.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_198_0_gn6.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_199_0_ptW.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_19_1_n9q.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_1_1_xbt.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_200_0_EEX.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_201_1_CIN.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_202_0_77L.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_203_0_cCx.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_204_0_ImP.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_205_0_gS8.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_206_0_HmM.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_207_0_DYP.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_208_0_iJl.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_209_0_4ct.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_20_1_4fv.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_210_0_CNV.root',
'rfio:////castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1//patTuple_skim_211_0_f2U.root',
  ]
  )
