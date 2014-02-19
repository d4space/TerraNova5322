import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
    )
readFiles.extend([



'rfio:////castor/cern.ch/user/h/hyusupov/SingleElectron_Run2012A/SingleEle_Run2012A_Prompt_v1_Low_PU/patTuple_skim_10_1_IU9.root',
'rfio:////castor/cern.ch/user/h/hyusupov/SingleElectron_Run2012A/SingleEle_Run2012A_Prompt_v1_Low_PU/patTuple_skim_11_1_gj4.root',
'rfio:////castor/cern.ch/user/h/hyusupov/SingleElectron_Run2012A/SingleEle_Run2012A_Prompt_v1_Low_PU/patTuple_skim_12_1_ucs.root',
'rfio:////castor/cern.ch/user/h/hyusupov/SingleElectron_Run2012A/SingleEle_Run2012A_Prompt_v1_Low_PU/patTuple_skim_13_1_s76.root',
'rfio:////castor/cern.ch/user/h/hyusupov/SingleElectron_Run2012A/SingleEle_Run2012A_Prompt_v1_Low_PU/patTuple_skim_14_1_i3G.root',
'rfio:////castor/cern.ch/user/h/hyusupov/SingleElectron_Run2012A/SingleEle_Run2012A_Prompt_v1_Low_PU/patTuple_skim_15_1_Sni.root',
'rfio:////castor/cern.ch/user/h/hyusupov/SingleElectron_Run2012A/SingleEle_Run2012A_Prompt_v1_Low_PU/patTuple_skim_16_3_5Tp.root',
'rfio:////castor/cern.ch/user/h/hyusupov/SingleElectron_Run2012A/SingleEle_Run2012A_Prompt_v1_Low_PU/patTuple_skim_17_1_7bJ.root',
'rfio:////castor/cern.ch/user/h/hyusupov/SingleElectron_Run2012A/SingleEle_Run2012A_Prompt_v1_Low_PU/patTuple_skim_18_1_Owu.root',
'rfio:////castor/cern.ch/user/h/hyusupov/SingleElectron_Run2012A/SingleEle_Run2012A_Prompt_v1_Low_PU/patTuple_skim_19_1_hou.root',
'rfio:////castor/cern.ch/user/h/hyusupov/SingleElectron_Run2012A/SingleEle_Run2012A_Prompt_v1_Low_PU/patTuple_skim_1_1_m7Z.root',
'rfio:////castor/cern.ch/user/h/hyusupov/SingleElectron_Run2012A/SingleEle_Run2012A_Prompt_v1_Low_PU/patTuple_skim_20_1_oE7.root',
'rfio:////castor/cern.ch/user/h/hyusupov/SingleElectron_Run2012A/SingleEle_Run2012A_Prompt_v1_Low_PU/patTuple_skim_21_1_e0V.root',
'rfio:////castor/cern.ch/user/h/hyusupov/SingleElectron_Run2012A/SingleEle_Run2012A_Prompt_v1_Low_PU/patTuple_skim_22_1_DYo.root',
'rfio:////castor/cern.ch/user/h/hyusupov/SingleElectron_Run2012A/SingleEle_Run2012A_Prompt_v1_Low_PU/patTuple_skim_23_3_crT.root',
'rfio:////castor/cern.ch/user/h/hyusupov/SingleElectron_Run2012A/SingleEle_Run2012A_Prompt_v1_Low_PU/patTuple_skim_24_1_1Pf.root',
'rfio:////castor/cern.ch/user/h/hyusupov/SingleElectron_Run2012A/SingleEle_Run2012A_Prompt_v1_Low_PU/patTuple_skim_25_1_eOC.root',
'rfio:////castor/cern.ch/user/h/hyusupov/SingleElectron_Run2012A/SingleEle_Run2012A_Prompt_v1_Low_PU/patTuple_skim_26_1_NI0.root',
'rfio:////castor/cern.ch/user/h/hyusupov/SingleElectron_Run2012A/SingleEle_Run2012A_Prompt_v1_Low_PU/patTuple_skim_27_1_CIo.root',
'rfio:////castor/cern.ch/user/h/hyusupov/SingleElectron_Run2012A/SingleEle_Run2012A_Prompt_v1_Low_PU/patTuple_skim_28_3_asH.root',

  ]
  )
