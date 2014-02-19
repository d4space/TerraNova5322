import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    #noEventSort = cms.untracked.bool(True),
    #duplicateCheckMode = cms.untracked.string("noDouplicateCheck"),
    fileNames = readFiles
    )
readFiles.extend([
'file:/terranova_1/Real_Sample/SingleElectron_Run2012A_PromptV1/SingleElectron_2012A_PromptReco_copy_15_1_232.root',
'file:/terranova_1/Real_Sample/SingleElectron_Run2012A_PromptV1/SingleElectron_2012A_PromptReco_copy_16_1_Uj3.root',
'file:/terranova_1/Real_Sample/SingleElectron_Run2012A_PromptV1/SingleElectron_2012A_PromptReco_copy_18_1_Sew.root',
'file:/terranova_1/Real_Sample/SingleElectron_Run2012A_PromptV1/SingleElectron_2012A_PromptReco_copy_19_1_MdG.root',
'file:/terranova_1/Real_Sample/SingleElectron_Run2012A_PromptV1/SingleElectron_2012A_PromptReco_copy_22_1_WoW.root',
'file:/terranova_1/Real_Sample/SingleElectron_Run2012A_PromptV1/SingleElectron_2012A_PromptReco_copy_23_1_ujH.root',
'file:/terranova_1/Real_Sample/SingleElectron_Run2012A_PromptV1/SingleElectron_2012A_PromptReco_copy_2_1_8dn.root',
'file:/terranova_1/Real_Sample/SingleElectron_Run2012A_PromptV1/SingleElectron_2012A_PromptReco_copy_9_1_xIh.root',
  ]
  )
