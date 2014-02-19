import FWCore.ParameterSet.Config as cms

process = cms.Process("wNTuple")

process.load("KoSMP.WAnalyzer.wAnalysis_RD_cff")

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
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/SingleMuReReco/patTuple_skim_28_1_MxU.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/SingleMuReReco/patTuple_skim_29_1_qze.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/SingleMuReReco/patTuple_skim_30_1_Ql8.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/SingleMuReReco/patTuple_skim_31_1_nHj.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/SingleMuReReco/patTuple_skim_3_2_wbo.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/SingleMuReReco/patTuple_skim_4_1_WOo.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/SingleMuReReco/patTuple_skim_5_1_TAs.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/SingleMuReReco/patTuple_skim_6_1_jIe.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/SingleMuReReco/patTuple_skim_7_1_Ao8.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/SingleMuReReco/patTuple_skim_8_1_Idt.root',
'file:/d2/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/SingleMuReReco/patTuple_skim_9_1_Z5W.root'
)
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('wNtuple_3.root')
)

#process.load("KoSMP.WAnalyzer.Sources.Run2012A_SingleMu_ReReco_AOD_PatSkim_Local_cff")

process.p = cms.Path(
    process.WMuNeuAnalysisRealDataSequence
)

