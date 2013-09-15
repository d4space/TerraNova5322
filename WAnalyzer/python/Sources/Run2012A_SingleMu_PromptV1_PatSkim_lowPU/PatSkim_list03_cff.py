import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
    )
readFiles.extend([
'rfio:////castor/cern.ch/user/k/kbutanov/SingleMu_Run2012A/DATA//patTuple_skim_40_1_we5.root',
'rfio:////castor/cern.ch/user/k/kbutanov/SingleMu_Run2012A/DATA//patTuple_skim_41_1_NZp.root',
'rfio:////castor/cern.ch/user/k/kbutanov/SingleMu_Run2012A/DATA//patTuple_skim_42_1_Fkf.root',
'rfio:////castor/cern.ch/user/k/kbutanov/SingleMu_Run2012A/DATA//patTuple_skim_43_1_uUi.root',
'rfio:////castor/cern.ch/user/k/kbutanov/SingleMu_Run2012A/DATA//patTuple_skim_44_1_8h5.root',
'rfio:////castor/cern.ch/user/k/kbutanov/SingleMu_Run2012A/DATA//patTuple_skim_45_1_Bv5.root',
'rfio:////castor/cern.ch/user/k/kbutanov/SingleMu_Run2012A/DATA//patTuple_skim_46_1_BS0.root',
'rfio:////castor/cern.ch/user/k/kbutanov/SingleMu_Run2012A/DATA//patTuple_skim_47_1_fdb.root',
'rfio:////castor/cern.ch/user/k/kbutanov/SingleMu_Run2012A/DATA//patTuple_skim_48_1_fM3.root',
'rfio:////castor/cern.ch/user/k/kbutanov/SingleMu_Run2012A/DATA//patTuple_skim_49_1_T6P.root',
'rfio:////castor/cern.ch/user/k/kbutanov/SingleMu_Run2012A/DATA//patTuple_skim_50_1_lNR.root',
'rfio:////castor/cern.ch/user/k/kbutanov/SingleMu_Run2012A/DATA//patTuple_skim_51_1_hRC.root',
'rfio:////castor/cern.ch/user/k/kbutanov/SingleMu_Run2012A/DATA//patTuple_skim_52_1_Pk2.root',
'rfio:////castor/cern.ch/user/k/kbutanov/SingleMu_Run2012A/DATA//patTuple_skim_53_1_l55.root',
'rfio:////castor/cern.ch/user/k/kbutanov/SingleMu_Run2012A/DATA//patTuple_skim_54_1_n5w.root',
'rfio:////castor/cern.ch/user/k/kbutanov/SingleMu_Run2012A/DATA//patTuple_skim_55_1_ViF.root',
'rfio:////castor/cern.ch/user/k/kbutanov/SingleMu_Run2012A/DATA//patTuple_skim_56_1_BN0.root',
'rfio:////castor/cern.ch/user/k/kbutanov/SingleMu_Run2012A/DATA//patTuple_skim_57_1_fQ8.root',
'rfio:////castor/cern.ch/user/k/kbutanov/SingleMu_Run2012A/DATA//patTuple_skim_58_1_WkP.root',
'rfio:////castor/cern.ch/user/k/kbutanov/SingleMu_Run2012A/DATA//patTuple_skim_59_1_Hig.root',
  ]
  )
