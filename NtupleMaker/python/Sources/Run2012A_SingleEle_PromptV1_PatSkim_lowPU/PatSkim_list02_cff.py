import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
    )
readFiles.extend([

'rfio:////castor/cern.ch/user/h/hyusupov/SingleElectron_Run2012A/SingleEle_Run2012A_Prompt_v1_Low_PU/patTuple_skim_29_1_Ro7.root',
'rfio:////castor/cern.ch/user/h/hyusupov/SingleElectron_Run2012A/SingleEle_Run2012A_Prompt_v1_Low_PU/patTuple_skim_2_1_4kx.root',
'rfio:////castor/cern.ch/user/h/hyusupov/SingleElectron_Run2012A/SingleEle_Run2012A_Prompt_v1_Low_PU/patTuple_skim_30_3_XTu.root',
'rfio:////castor/cern.ch/user/h/hyusupov/SingleElectron_Run2012A/SingleEle_Run2012A_Prompt_v1_Low_PU/patTuple_skim_31_3_3w6.root',
'rfio:////castor/cern.ch/user/h/hyusupov/SingleElectron_Run2012A/SingleEle_Run2012A_Prompt_v1_Low_PU/patTuple_skim_32_3_bqg.root',
'rfio:////castor/cern.ch/user/h/hyusupov/SingleElectron_Run2012A/SingleEle_Run2012A_Prompt_v1_Low_PU/patTuple_skim_33_1_eMF.root',
'rfio:////castor/cern.ch/user/h/hyusupov/SingleElectron_Run2012A/SingleEle_Run2012A_Prompt_v1_Low_PU/patTuple_skim_34_1_NuX.root',
'rfio:////castor/cern.ch/user/h/hyusupov/SingleElectron_Run2012A/SingleEle_Run2012A_Prompt_v1_Low_PU/patTuple_skim_35_3_1XB.root',
'rfio:////castor/cern.ch/user/h/hyusupov/SingleElectron_Run2012A/SingleEle_Run2012A_Prompt_v1_Low_PU/patTuple_skim_36_3_5w3.root',
'rfio:////castor/cern.ch/user/h/hyusupov/SingleElectron_Run2012A/SingleEle_Run2012A_Prompt_v1_Low_PU/patTuple_skim_37_1_SPD.root',
'rfio:////castor/cern.ch/user/h/hyusupov/SingleElectron_Run2012A/SingleEle_Run2012A_Prompt_v1_Low_PU/patTuple_skim_38_1_cj1.root',
'rfio:////castor/cern.ch/user/h/hyusupov/SingleElectron_Run2012A/SingleEle_Run2012A_Prompt_v1_Low_PU/patTuple_skim_39_1_Yvk.root',
'rfio:////castor/cern.ch/user/h/hyusupov/SingleElectron_Run2012A/SingleEle_Run2012A_Prompt_v1_Low_PU/patTuple_skim_3_1_LTm.root',
'rfio:////castor/cern.ch/user/h/hyusupov/SingleElectron_Run2012A/SingleEle_Run2012A_Prompt_v1_Low_PU/patTuple_skim_4_1_qjV.root',
'rfio:////castor/cern.ch/user/h/hyusupov/SingleElectron_Run2012A/SingleEle_Run2012A_Prompt_v1_Low_PU/patTuple_skim_5_1_Ydr.root',
'rfio:////castor/cern.ch/user/h/hyusupov/SingleElectron_Run2012A/SingleEle_Run2012A_Prompt_v1_Low_PU/patTuple_skim_6_1_pdm.root',
'rfio:////castor/cern.ch/user/h/hyusupov/SingleElectron_Run2012A/SingleEle_Run2012A_Prompt_v1_Low_PU/patTuple_skim_7_1_2pE.root',
'rfio:////castor/cern.ch/user/h/hyusupov/SingleElectron_Run2012A/SingleEle_Run2012A_Prompt_v1_Low_PU/patTuple_skim_8_3_cUi.root',
'rfio:////castor/cern.ch/user/h/hyusupov/SingleElectron_Run2012A/SingleEle_Run2012A_Prompt_v1_Low_PU/patTuple_skim_9_1_kLv.root',

  ]
  )
