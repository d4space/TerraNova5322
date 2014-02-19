import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
    )
readFiles.extend([
'rfio:////castor/cern.ch/user/k/kbutanov/SingleMu_Run2012A/DATA//patTuple_skim_21_1_NKM.root',
'rfio:////castor/cern.ch/user/k/kbutanov/SingleMu_Run2012A/DATA//patTuple_skim_22_1_u4L.root',
'rfio:////castor/cern.ch/user/k/kbutanov/SingleMu_Run2012A/DATA//patTuple_skim_23_1_ewU.root',
'rfio:////castor/cern.ch/user/k/kbutanov/SingleMu_Run2012A/DATA//patTuple_skim_24_1_Ftn.root',
'rfio:////castor/cern.ch/user/k/kbutanov/SingleMu_Run2012A/DATA//patTuple_skim_25_1_3au.root',
'rfio:////castor/cern.ch/user/k/kbutanov/SingleMu_Run2012A/DATA//patTuple_skim_26_1_edh.root',
'rfio:////castor/cern.ch/user/k/kbutanov/SingleMu_Run2012A/DATA//patTuple_skim_27_1_AVU.root',
'rfio:////castor/cern.ch/user/k/kbutanov/SingleMu_Run2012A/DATA//patTuple_skim_28_1_VEw.root',
'rfio:////castor/cern.ch/user/k/kbutanov/SingleMu_Run2012A/DATA//patTuple_skim_28_1_yWN.root',
'rfio:////castor/cern.ch/user/k/kbutanov/SingleMu_Run2012A/DATA//patTuple_skim_29_1_5WE.root',
'rfio:////castor/cern.ch/user/k/kbutanov/SingleMu_Run2012A/DATA//patTuple_skim_30_1_tZi.root',
'rfio:////castor/cern.ch/user/k/kbutanov/SingleMu_Run2012A/DATA//patTuple_skim_31_1_nVN.root',
'rfio:////castor/cern.ch/user/k/kbutanov/SingleMu_Run2012A/DATA//patTuple_skim_32_1_sYY.root',
'rfio:////castor/cern.ch/user/k/kbutanov/SingleMu_Run2012A/DATA//patTuple_skim_33_1_64f.root',
'rfio:////castor/cern.ch/user/k/kbutanov/SingleMu_Run2012A/DATA//patTuple_skim_34_1_VTi.root',
'rfio:////castor/cern.ch/user/k/kbutanov/SingleMu_Run2012A/DATA//patTuple_skim_35_1_iew.root',
'rfio:////castor/cern.ch/user/k/kbutanov/SingleMu_Run2012A/DATA//patTuple_skim_36_1_ABV.root',
'rfio:////castor/cern.ch/user/k/kbutanov/SingleMu_Run2012A/DATA//patTuple_skim_37_1_iPr.root',
'rfio:////castor/cern.ch/user/k/kbutanov/SingleMu_Run2012A/DATA//patTuple_skim_38_1_Fm5.root',
'rfio:////castor/cern.ch/user/k/kbutanov/SingleMu_Run2012A/DATA//patTuple_skim_39_1_fxU.root',
  ]
  )
