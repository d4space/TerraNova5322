import FWCore.ParameterSet.Config as cms

process = cms.Process("wNTuple")

process.load("KNUPhy.WAnalyzer.wAnalysis_RD_cff")

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
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/SingleMuReReco/patTuple_skim_10_1_cyg.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/SingleMuReReco/patTuple_skim_11_16_joH.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/SingleMuReReco/patTuple_skim_1_1_TaZ.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/SingleMuReReco/patTuple_skim_12_1_Xx0.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/SingleMuReReco/patTuple_skim_13_1_R63.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/SingleMuReReco/patTuple_skim_14_1_JkF.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/SingleMuReReco/patTuple_skim_15_4_vmc.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/SingleMuReReco/patTuple_skim_16_1_jYF.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/SingleMuReReco/patTuple_skim_17_1_Iik.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/SingleMuReReco/patTuple_skim_18_1_ap0.root'
)
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('wNtuple_1.root')
)

#process.load("KNUPhy.WAnalyzer.Sources.Run2012A_SingleMu_ReReco_AOD_PatSkim_Local_cff")

process.p = cms.Path(
    process.WMuNeuAnalysisRealDataSequence
)

