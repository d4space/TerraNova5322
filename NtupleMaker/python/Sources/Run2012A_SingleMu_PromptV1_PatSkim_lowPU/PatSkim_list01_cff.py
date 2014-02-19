import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
    )
readFiles.extend([
'rfio:////castor/cern.ch/user/k/kbutanov/SingleMu_Run2012A/DATA//patTuple_skim_1_1_qJ8.root',
'rfio:////castor/cern.ch/user/k/kbutanov/SingleMu_Run2012A/DATA//patTuple_skim_2_1_rBm.root',
'rfio:////castor/cern.ch/user/k/kbutanov/SingleMu_Run2012A/DATA//patTuple_skim_3_1_yKt.root',
'rfio:////castor/cern.ch/user/k/kbutanov/SingleMu_Run2012A/DATA//patTuple_skim_4_1_qxX.root',
'rfio:////castor/cern.ch/user/k/kbutanov/SingleMu_Run2012A/DATA//patTuple_skim_5_1_GrT.root',
'rfio:////castor/cern.ch/user/k/kbutanov/SingleMu_Run2012A/DATA//patTuple_skim_6_1_Pf5.root',
'rfio:////castor/cern.ch/user/k/kbutanov/SingleMu_Run2012A/DATA//patTuple_skim_7_1_zhv.root',
'rfio:////castor/cern.ch/user/k/kbutanov/SingleMu_Run2012A/DATA//patTuple_skim_8_1_DYb.root',
'rfio:////castor/cern.ch/user/k/kbutanov/SingleMu_Run2012A/DATA//patTuple_skim_9_1_zrG.root',
'rfio:////castor/cern.ch/user/k/kbutanov/SingleMu_Run2012A/DATA//patTuple_skim_10_1_Wrh.root',
'rfio:////castor/cern.ch/user/k/kbutanov/SingleMu_Run2012A/DATA//patTuple_skim_11_1_UrS.root',
'rfio:////castor/cern.ch/user/k/kbutanov/SingleMu_Run2012A/DATA//patTuple_skim_12_1_ILh.root',
'rfio:////castor/cern.ch/user/k/kbutanov/SingleMu_Run2012A/DATA//patTuple_skim_13_1_bxg.root',
'rfio:////castor/cern.ch/user/k/kbutanov/SingleMu_Run2012A/DATA//patTuple_skim_14_1_75i.root',
'rfio:////castor/cern.ch/user/k/kbutanov/SingleMu_Run2012A/DATA//patTuple_skim_15_1_52x.root',
'rfio:////castor/cern.ch/user/k/kbutanov/SingleMu_Run2012A/DATA//patTuple_skim_16_1_G46.root',
'rfio:////castor/cern.ch/user/k/kbutanov/SingleMu_Run2012A/DATA//patTuple_skim_17_1_O5R.root',
'rfio:////castor/cern.ch/user/k/kbutanov/SingleMu_Run2012A/DATA//patTuple_skim_18_1_XDp.root',
'rfio:////castor/cern.ch/user/k/kbutanov/SingleMu_Run2012A/DATA//patTuple_skim_19_1_6G5.root',
'rfio:////castor/cern.ch/user/k/kbutanov/SingleMu_Run2012A/DATA//patTuple_skim_20_1_AvR.root',
  ]
  )
