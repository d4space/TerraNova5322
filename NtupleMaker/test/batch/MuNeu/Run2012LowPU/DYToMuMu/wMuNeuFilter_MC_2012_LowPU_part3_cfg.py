import FWCore.ParameterSet.Config as cms

process = cms.Process("wNTuple")

process.load("TerraNova.NtupleMaker.wAnalysis_MC_cff")

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
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_174_1_7to.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_175_1_HWR.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_176_1_mWU.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_177_1_5EL.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_178_1_4nq.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_179_1_CEA.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_17_1_XyD.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_180_1_yCE.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_181_1_5s8.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_182_1_4if.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_183_1_pdq.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_184_1_lui.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_185_1_zfq.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_186_1_bAa.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_187_1_IgJ.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_188_1_QQy.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_189_1_RpB.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_18_1_Sr1.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_190_1_1Am.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_191_1_j1c.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_192_1_ckv.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_193_1_rvW.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_194_1_kAi.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_195_1_6es.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_196_1_jSD.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_197_1_fCZ.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_198_1_lek.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_199_1_pZQ.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_19_1_WL9.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_1_1_qmL.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_20_1_saS.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_21_1_drO.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_22_1_aF5.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_23_1_zuC.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_24_1_dRZ.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_25_1_YpH.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_26_1_SBj.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_27_1_Cox.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_28_1_LUy.root',
'file:/d1/scratch/Storage_Area/Wpt-skim/Muon/RecoilCorr/DYToMuMu/patTuple_skim_29_1_UwP.root'
)
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('wNTuple_3.root')
)

#process.load("TerraNova.NtupleMaker.Sources.DYToMuMu_S8_Skim_cff")
#process.load("TerraNova.NtupleMaker.Sources.WplusToMuNu_S8_8TeV_AODSIM_PatSkim_local_cff")

process.p = cms.Path(
    process.WMuNeuAnalysisMCSequence
)

