import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    #noEventSort = cms.untracked.bool(True),
    #duplicateCheckMode = cms.untracked.string("noDouplicateCheck"),
    fileNames = readFiles
    )
readFiles.extend([
  'file:/afs/cern.ch/work/s/salee/DataSample/S8/WplusToMuNu_AODSIM_1_1_2YJ.root',
#  'root://eoscms//eos/cms/store/user/shchang/DYToMuMu_Summer12_S10/DYToMuMu_5000_1_1_tIc.root',
#  'file:/afs/cern.ch/work/k/kbutanov/public/DYJetsToLL/DYJetsToLL_5000_1_1_gtv.root',
  #'file:/afs/cern.ch/work/s/salee/DataSample/S10/DYToMuMu_5000_3_1_f18.root',
#  'file:/afs/cern.ch/work/t/taehoon/public/DATA/MC/DYToEE_S10.root',
#  'file:/afs/cern.ch/work/t/taehoon/public/DATA/MC/2012/WToENu_copy.root'
  #'file:/d2/scratch/Storage_Area/NoPuMET/WToENu_copy.root'
  #'file:/afs/cern.ch/work/t/taehoon/public/DATA/MC/2012/Summer12_DR53X__WToENu_TuneZ2star_8TeV_pythia6_AODSIM_PU_S10_START53_V7A-v2.root'
  ]
  )
