import FWCore.ParameterSet.Config as cms

from HLTrigger.HLTfilters.hltHighLevel_cfi import *

# for SingleMu dataset
hltHighLevelSingleMuLoPU = hltHighLevel.clone()
hltHighLevelSingleMuLoPU.TriggerResultsTag = cms.InputTag("TriggerResults","","HLT")
hltHighLevelSingleMuLoPU.HLTPaths = cms.vstring('HLT_Mu15_eta2p1_v*')
hltHighLevelSingleMuLoPU.throw = cms.bool(False)
#RD
hltHighLevelSingleMuRD = hltHighLevel.clone()
hltHighLevelSingleMuRD.TriggerResultsTag = cms.InputTag("TriggerResults","","HLT")
hltHighLevelSingleMuRD.HLTPaths = cms.vstring('HLT_IsoMu24_eta2p1_v*','HLT_Mu15_eta2p1_v*')
hltHighLevelSingleMuRD.throw = cms.bool(False)
#MC
hltHighLevelSingleMuMC = hltHighLevel.clone()
hltHighLevelSingleMuMC.TriggerResultsTag = cms.InputTag("TriggerResults","","HLT")
hltHighLevelSingleMuMC.HLTPaths = cms.vstring('HLT_IsoMu24_eta2p1_v*','HLT_Mu15_eta2p1_v*')
hltHighLevelSingleMuMC.throw = cms.bool(False)
# for SingleEle dataset
hltHighLevelSingleEleRD = hltHighLevel.clone()
hltHighLevelSingleEleRD.TriggerResultsTag = cms.InputTag("TriggerResults","","HLT")
#                                                                        Low PU
hltHighLevelSingleEleRD.HLTPaths = cms.vstring('HLT_Ele27_WP80_v*','HLT_Ele22_CaloIdL_CaloIsoVL_v*')
hltHighLevelSingleEleRD.throw = cms.bool(False)
#MC
hltHighLevelSingleEleMC = hltHighLevel.clone()
hltHighLevelSingleEleMC.TriggerResultsTag = cms.InputTag("TriggerResults","","HLT")
#                                                                        Low PU
hltHighLevelSingleEleMC.HLTPaths = cms.vstring('HLT_Ele27_WP80_v*','HLT_Ele22_CaloIdL_CaloIsoVL_v*')
hltHighLevelSingleEleMC.throw = cms.bool(False)

