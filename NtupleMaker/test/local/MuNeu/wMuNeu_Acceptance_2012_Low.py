import FWCore.ParameterSet.Config as cms

process = cms.Process("wAcceptance")



process.load("TerraNova5322.NtupleMaker.wAnalysis_MC_HiPU_MVAnoPU_cff")

process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100))
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

#process.load("FWCore.MessageLogger.MessageLogger_cfi")
#process.MessageLogger = cms.Service("MessageLogger")
#process.MessageLogger.destinations = ['cout']
#process.MessageLogger.cout = cms.untracked.PSet(
#    threshold = cms.untracked.string('INFO'),
#    FwkReport = cms.untracked.PSet(reportEvery=cms.untracked.int32(1000))
#)


# Printout of generator information for the first event
process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
process.printGenParticles = cms.EDAnalyzer("ParticleListDrawer",
    maxEventsToPrint = cms.untracked.int32(10),
    printVertex = cms.untracked.bool(False),
    src = cms.InputTag("genParticles")
    )


process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
      'file:/afs/cern.ch/user/s/spak/Work/public/ForDrLee/WJetsToLNu_TuneCUETP8M1_8TeV.root',
    #  'dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/mc/Summer12/WJetsToLNu_TuneCUETP8M1_8TeV-amcatnloFXFX-pythia8/GEN-SIM/START53_V7C-v5/00000/000D02E6-FC77-E411-AA38-0025905A608A.root',
      )
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('wAcceptance.root')
)

#process.load("KoSMP.WAnalyzer.Sources.DYToMuMu_S8_Skim_cff")
#process.load("KoSMP.WAnalyzer.Sources.WplusToMuNu_AODSIM_CP_local_cff")
#process.load("KoSMP.WAnalyzer.Sources.WplusToMuNu_S8_8TeV_AODSIM_PatSkim_local_cff")
process.nEventsTotal = cms.EDProducer("EventCountProducer")

process.p = cms.Path(
    process.nEventsTotal *
    process.WAcceptanceMuon
#    process.WMuNeuAcceptanceSequence
)

