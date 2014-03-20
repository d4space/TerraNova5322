import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    #noEventSort = cms.untracked.bool(True),
    #duplicateCheckMode = cms.untracked.string("noDouplicateCheck"),
    fileNames = readFiles
    )
readFiles.extend([
  #'file:/afs/cern.ch/work/d/dhkim/public/MC_sample/ZZTo4Mu/ZZTo4Mu.root',
  #'file:/afs/cern.ch/work/d/dhkim/public/MC_sample/ZZTo4e/ZZTo4e.root',
  #'file:/afs/cern.ch/work/d/dhkim/public/MC_sample/ZZTo2e2Mu/ZZTo2e2Mu.root',
  #'file:/afs/cern.ch/work/d/dhkim/public/MC_sample/ADDmonoJet/ADDmonoJet.root',
  #'file:/afs/cern.ch/work/d/dhkim/public/MC_sample/TTJetsToHadronic/TTJetsToHadronic.root',
  #'file:/afs/cern.ch/work/d/dhkim/public/MC_sample/TTJetsToSemiLept/TTJetsToSemiLept.root',
  'file:/afs/cern.ch/work/d/dhkim/public/MC_sample/WJetsToLNu/WJetsToLNu.root',
  #'file:/afs/cern.ch/work/s/salee/DataSample/S8/WplusToMuNu_AODSIM_1_1_2YJ.root',
  #'file:/afs/cern.ch/work/s/salee/DataSample/S10/DYToMuMu_5000_3_1_f18.root',
  #'file:/afs/cern.ch/work/s/salee/DataSample/S10/DYToEE_S10_DR53X_AOD.root',

  ##### Muon code test ##########
  #'file:/d1/scratch/jungmin/git/CMSSW_5_3_14/src/TerraNova/NtupleMaker/prod/Muon/MC/Local/data/WpToMuNu_5000_1_2_04c.root',
  #'file:/d1/scratch/jungmin/git/CMSSW_5_3_14_patch1/src/TerraNova/NtupleMaker/prod/Copy_Data/test/Muon/Rd/RD_5000_1_1_w23.root',

 
  ##### Electron code test ##########
  #'file:/d1/scratch/jungmin/git/CMSSW_5_3_14_patch1/src/TerraNova/NtupleMaker/prod/Copy_Data/test/Electron/Rd/Run2012A_5000_1_1_j4m.root',
  #'file:/d1/scratch/jungmin/git/CMSSW_5_3_14_patch1/src/TerraNova/NtupleMaker/prod/Copy_Data/test/Electron/MC/WToENu_5000_1_1_w5C.root',

 
 #  'root://eoscms//eos/cms/store/user/shchang/DYToMuMu_Summer12_S10/DYToMuMu_5000_1_1_tIc.root',
#  'file:/afs/cern.ch/work/k/kbutanov/public/DYJetsToLL/DYJetsToLL_5000_1_1_gtv.root',
  #'file:/afs/cern.ch/work/s/salee/DataSample/S10/DYToMuMu_5000_3_1_f18.root',
#  'file:/afs/cern.ch/work/t/taehoon/public/DATA/MC/DYToEE_S10.root',
#  'file:/afs/cern.ch/work/t/taehoon/public/DATA/MC/2012/WToENu_copy.root'
  #'file:/d2/scratch/Storage_Area/NoPuMET/WToENu_copy.root'
  #'file:/afs/cern.ch/work/t/taehoon/public/DATA/MC/2012/Summer12_DR53X__WToENu_TuneZ2star_8TeV_pythia6_AODSIM_PU_S10_START53_V7A-v2.root'
  ]
  )
