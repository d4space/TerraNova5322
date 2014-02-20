import FWCore.ParameterSet.Config as cms

process = cms.Process("wNTuple")

process.load("TerraNova.NtupleMaker.wAnalysis_RD_cff")

process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

#process.load("FWCore.MessageLogger.MessageLogger_cfi")
#process.MessageLogger = cms.Service("MessageLogger")
#process.MessageLogger.destinations = ['cout']
#process.MessageLogger.cout = cms.untracked.PSet(
#    threshold = cms.untracked.string('INFO'),
#    FwkReport = cms.untracked.PSet(reportEvery=cms.untracked.int32(1000))
#)

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/SingleMuReReco/patTuple_skim_19_1_hiH.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/SingleMuReReco/patTuple_skim_20_1_FBN.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/SingleMuReReco/patTuple_skim_21_1_K2Z.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/SingleMuReReco/patTuple_skim_2_1_WWW.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/SingleMuReReco/patTuple_skim_22_1_ZsI.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/SingleMuReReco/patTuple_skim_23_1_1ni.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/SingleMuReReco/patTuple_skim_24_1_ILB.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/SingleMuReReco/patTuple_skim_25_1_zw5.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/SingleMuReReco/patTuple_skim_26_1_Ex7.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/SingleMuReReco/patTuple_skim_27_1_8eO.root'
)
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('wNtuple_2.root')
)

#process.load("TerraNova.NtupleMaker.Sources.Run2012A_SingleMu_ReReco_AOD_PatSkim_Local_cff")

process.p = cms.Path(
    process.WMuNeuAnalysisRealDataSequence
)

