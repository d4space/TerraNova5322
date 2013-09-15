import FWCore.ParameterSet.Config as cms
import os
process = cms.Process("TagProbe")
process.p=cms.Path()
##########################
# Include
##########################

#from KNUPhy.WAnalyzer.pf2pat_template_MC_cfg import *
from KNUPhy.WAnalyzer.eventContent_cff import *
from KNUPhy.WAnalyzer.tools import *
from KNUPhy.CommonTools.eleSelectorPSet_cff import eleSelectorPSet
## MessageLogger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
#process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.Geometry.GeometryIdeal_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")

#process.load("HLTrigger.Configuration.HLT_7E33v2_cff")

process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
from PhysicsTools.PatAlgos.patEventContent_cff import patEventContent


#PF2PAT
process.load("PhysicsTools.PatAlgos.patSequences_cff")
from PhysicsTools.PatAlgos.tools.pfTools import *


#########################
# Constant
#########################
MC_flag = False
#MC_flag = True

#for RD
#GLOBAL_TAG = 'FT53_V10A_AN3::All'
# for Run2012C-06Aug
#GLOBAL_TAG = 'FT_R_53_V18::All'
#GLOBAL_TAG = 'FT_R_53_V6::All'
#GLOBAL_TAG = 'GR_P_V42C_AN3::All'
# for 2012C-PromptReco-v2, 2012D-Prompteco-v1
#GLOBAL_TAG = 'GR_R_53_V21::All'
#GLOBAL_TAG = 'FT_P_V42_AN3::All'
#for Run2012C-EcalRecover_11Dec2012
GLOBAL_TAG = 'FT_53_V6C_AN3::All' 
#for Run2012A-13Jul2012,Run2012A-recover-06Aug2012,Run2012B-13Jul2012
#GLOBAL_TAG = 'GR_H_V29::All'
#https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideFrontierConditions#2012_A_B_C_D_datasets_re_reco_pr

#for MC
#GLOBAL_TAG = 'START53_V18::All' #/cdaq/physics/Run2012/7e33/v2.5/HLT/V1
#HLTPath = "HLT_Ele27_WP80_v9, HLT_Ele27_WP80_v10, HLT_Ele27_WP80_v11"
#HLTPath = "HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v17"

HLTPath1 = "HLT_Ele27_WP80_v8"
HLTPath2 = "HLT_Ele27_WP80_v9"
HLTPath3 = "HLT_Ele27_WP80_v10"
HLTPath4 = "HLT_Ele27_WP80_v11"
#HLTPath = "HLT_Ele22_CaloIdL_CaloIsoVL_v5"
#HLTPath = "HLT_Ele30_CaloIdVT_TrkIdT_v5"
HLTProcessName = "HLT"

if MC_flag:
    GLOBAL_TAG = 'START53_V18::All'
    #GLOBAL_TAG = 'START42_V12::All'
    HLTPath = "HLT_Ele27_WP80_v8,HLT_Ele27_WP80_v9,HLT_Ele27_WP80_v10,HLT_Ele27_WP80_v11"
    HLTProcessName = "HLT"

process.GlobalTag.globaltag = GLOBAL_TAG

#process.GlobalTag.globaltag = cms.string( 'START52_V10::All' )
OUTPUT_FILE_NAME = "testNewWrite.root"

ELECTRON_ET_CUT_MIN = 0.0
#ELECTRON_ET_CUT_MIN = 25.0
#ELECTRON_ET_CUT_MIN = 17.0
ELECTRON_COLL = "selectedPatElectronsPFlow"
#ELECTRON_COLL = "gsfElectrons"
ELECTRON_CUTS = "ecalDrivenSeed==1 && (abs(superCluster.eta)<2.5) && !(1.4442<abs(superCluster.eta)<1.566) && (ecalEnergy*sin(superClusterPosition.theta)>" + str(ELECTRON_ET_CUT_MIN) + ")"
####

PHOTON_COLL = "photons"
PHOTON_CUTS = "hadronicOverEm<0.15 && (abs(superCluster.eta)<2.5) && !(1.4442<abs(superCluster.eta)<1.566) && ((isEB && sigmaIetaIeta<0.01) || (isEE && sigmaIetaIeta<0.03)) && (superCluster.energy*sin(superCluster.position.theta)>" + str(ELECTRON_ET_CUT_MIN) + ")"
####

#SUPERCLUSTER_COLL_EB = "hybridSuperClusters"
#SUPERCLUSTER_COLL_EE = "multi5x5SuperClustersWithPreshower"
SUPERCLUSTER_COLL_EB = "correctedHybridSuperClusters"
SUPERCLUSTER_COLL_EE = "correctedMulti5x5SuperClustersWithPreshower"
if MC_flag:
    SUPERCLUSTER_COLL_EB = "correctedHybridSuperClusters"
    SUPERCLUSTER_COLL_EE = "correctedMulti5x5SuperClustersWithPreshower"
SUPERCLUSTER_CUTS = "abs(eta)<2.5 && !(1.4442< abs(eta) <1.566) && et>" + str(ELECTRON_ET_CUT_MIN)


JET_COLL = "ak5PFJets"
JET_CUTS = "abs(eta)<2.6 && chargedHadronEnergyFraction>0 && electronEnergyFraction<0.1 && nConstituents>1 && neutralHadronEnergyFraction<0.99 && neutralEmEnergyFraction<0.99" 

#############################
## Source
#############################
from PhysicsTools.PatAlgos.tools.cmsswVersionTools import pickRelValInputFiles
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
#    'file:/afs/cern.ch/user/y/ykim/public/Run2012A-13Jul2012_sample.root'
#    'file:/afs/cern.ch/work/t/taehoon/public/DATA/RD/2012/SingleElectron_Run2012B_13Jul2012-v1_AOD.root'
#'file:/afs/cern.ch/work/t/taehoon/public/DATA/MC/2012/Summer12_DR53X__WToENu_TuneZ2star_8TeV_pythia6_AODSIM_PU_S10_START53_V7A-v2.root'
#'file:/afs/cern.ch/work/s/shchang/W_V004/CMSSW_5_3_7_patch4/src/KNUPhy/WAnalyzer/prod/Electron/RD/Local/patTuple_skim_l1Filter.root'
      'file:/d1/scratch/kimtaehoon/HighPU/CMSSW_5_3_8/src/KNUPhy1/TnP_Electron/Producer/Crab/RD/HighPU2012/Run2012A-13Jul2012-v1/Run2012A-13Jul2012_sample.root'

#    pickRelValInputFiles( cmsswVersion  = os.environ['CMSSW_VERSION']
#                        , relVal        = 'RelValTTbar'
#                        , globalTag     = process.GlobalTag.globaltag.value().split(':')[0]
#                        , numberOfFiles = 1
#                        )
    )
)
#if MC_flag:
#  print "MC sample"
#  process.load("KNUPhy.WAnalyzer.Sources.DYToEE_S8_copy_cff")
#else:
#  print "RD sample"
#  process.load("KNUPhy.WAnalyzer.Sources.SingleElectron_2012A_PromptReco_copy_cff")

#process.load("KNUPhy.WAnalyzer.Sources.WplusToMuNu_AODSIM_CP_local_cff")
############################
# Output
############################
process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string('patTuple_TnP_skim.root'),
    # save only events passing the full path
    SelectEvents   = cms.untracked.PSet( SelectEvents = cms.vstring('p') ),
    # save PAT Layer 1 output; you need a '*' to
    # unpack the list of commands 'patEventContent'
    outputCommands = cms.untracked.vstring('drop *')
)
process.out.outputCommands +=pf2patEventContent

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
## Options and Output Report
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.MessageLogger.cerr.FwkReport.reportEvery = 1000


#process.MessageLogger.suppressWarning.append("HLTConfigData")
#process.MessageLogger.suppressInfo.append("HLTConfigData")
#process.MessageLogger.suppressError.append("HLTConfigData") #HLTConfigData
#process.MessageLogger.suppressError.append("HLTConfigProvider")

process.MessageLogger.suppressError = cms.untracked.vstring("HLTConfigData",
                                                            "trgMatchedGsfElectronProducer",
                                                            "HLTConfigProvider",
                                                            "TriggerCandProducer",
                                                            "PassingHLT",
                                                            "L1GtUtils",
                                                            "Tag")


#process.MessageLogger.suppressWarning.append("PassingHLT")
#process.MessageLogger.suppressInfo.append("PassingHLT")
#process.MessageLogger.suppressError.append("PassingHLT")

#process.MessageLogger.suppressWarning.append("trgMatchedGsfElectronProducer")
#process.MessageLogger.suppressInfo.append("trgMatchedGsfElectronProducer")
#process.MessageLogger.suppressError.append("trgMatchedGsfElectronProducer:Tag")#trgMatchedGsfElectronProducer:Tag 

#process.MessageLogger.suppressError.append("L1GtUtils")



process.TFileService = cms.Service(
    "TFileService", fileName = cms.string( OUTPUT_FILE_NAME )
    )

###########################
## Event Clean
##########################
process.goodOfflinePrimaryVertices = cms.EDFilter("VertexSelector",
   src = cms.InputTag("offlinePrimaryVertices"),
   cut = cms.string("!isFake && ndof > 4 && abs(z) < 24 && position.Rho < 2"), # tracksSize() > 3 for the older cut
   filter = cms.bool(True),   # otherwise it won't filter the events, just produce an empty vertex collection.
)

process.noscraping = cms.EDFilter("FilterOutScraping",
   applyfilter = cms.untracked.bool(True),
   debugOn = cms.untracked.bool(False),
   numtrack = cms.untracked.uint32(10),
   thresh = cms.untracked.double(0.25)
)
process.load('CommonTools.RecoAlgos.HBHENoiseFilter_cfi')
process.HBHENoiseFilter.minNumIsolatedNoiseChannels = cms.int32(9999)
process.HBHENoiseFilter.minIsolatedNoiseSumE = cms.double(9999)
process.HBHENoiseFilter.minIsolatedNoiseSumEt = cms.double(9999)

#####################
## PAT
######################

runOnMC=MC_flag
postfix = "PFlow"
jetAlgo="AK5"
usePF2PAT(process,runPF2PAT=True, jetAlgo=jetAlgo, runOnMC=runOnMC, postfix=postfix, typeIMetCorrections=True)

#process.pfPileUpIsoPFlow.checkClosestZVertex = cms.bool(False)
#process.pfPileUpIso.checkClosestZVertex = cms.bool(False)

#change cone size
changeConeSize(process,postfix)

#FastJet!
#applyFastJet(process,postfix)

rhoFor2012Aeff(process,postfix)

#REMOVE ISOLATION FROM PF2PAT!!!
addLooseLeptons(process)

# top projections in PF2PAT:
topProjection(process,postfix)

##############
## Filter and Producer
######################

##   ____                         ____ _           _            
##  / ___| _   _ _ __   ___ _ __ / ___| |_   _ ___| |_ ___ _ __ 
##  \___ \| | | | '_ \ / _ \ '__| |   | | | | / __| __/ _ \ '__|
##   ___) | |_| | |_) |  __/ |  | |___| | |_| \__ \ ||  __/ |   
##  |____/ \__,_| .__/ \___|_|   \____|_|\__,_|___/\__\___|_|   
##  

#  SuperClusters  ################
process.superClusters = cms.EDProducer("SuperClusterMerger",
   src = cms.VInputTag(cms.InputTag( SUPERCLUSTER_COLL_EB ,"", "RECO"),
                       cms.InputTag( SUPERCLUSTER_COLL_EE ,"", "RECO") )  
)

process.superClusterCands = cms.EDProducer("ConcreteEcalCandidateProducer",
   src = cms.InputTag("superClusters"),
   particleType = cms.int32(11),
)

#   Get the above SC's Candidates and place a cut on their Et and eta
process.goodSuperClusters = cms.EDFilter("CandViewSelector",
      src = cms.InputTag("superClusterCands"),
      cut = cms.string( SUPERCLUSTER_CUTS ),
      filter = cms.bool(True)
)                                         
                                         

#### remove real jets (with high hadronic energy fraction) from SC collection
##### this improves the purity of the probe sample without affecting efficiency

process.JetsToRemoveFromSuperCluster = cms.EDFilter("CaloJetSelector",   
    src = cms.InputTag("ak5CaloJets"),
    cut = cms.string('pt>5 && energyFractionHadronic > 0.15')
)
process.goodSuperClustersClean = cms.EDProducer("CandViewCleaner",
    srcObject = cms.InputTag("goodSuperClusters"),
    module_label = cms.string(''),
    srcObjectsToRemove = cms.VInputTag(cms.InputTag("JetsToRemoveFromSuperCluster")),
    deltaRMin = cms.double(0.1)
)

#  Photons!!! ################ 
process.goodPhotons = cms.EDFilter(
    "PhotonSelector",
    src = cms.InputTag( PHOTON_COLL ),
    cut = cms.string(PHOTON_CUTS)
    )


process.sc_sequence = cms.Sequence(
    process.superClusters +
    process.superClusterCands +
    process.goodSuperClusters +
    process.JetsToRemoveFromSuperCluster +
    process.goodSuperClustersClean +
    process.goodPhotons
    )
########################
## PF Electrons
########################

process.acceptedElectrons = cms.EDFilter("PATElectronSelector",
    src = cms.InputTag("selectedPatElectronsPFlow"),
    cut = cms.string(ELECTRON_CUTS),
    #cut = cms.string("pt > 20 && abs(eta) < 2.5"),
    #cut = cms.string("pt > 20 && abs(eta) < 2.5 && ecalDrivenSeed")
    filter = cms.bool(False),
)
process.allConversions = cms.EDProducer("PATConversionProducer",
    electronSource = cms.InputTag("acceptedElectrons")
    # this should be your last selected electron collection name
    )

process.PassingWCut = cms.EDProducer(
    "KyElectronSelector",
    version = cms.untracked.int32( 13 ),# -1(no cut), 0(check cut, isocut pset), 13(WCut=Medium Cut)
    #version = cms.untracked.int32( 5 ),# 10 = MVA, 5 = WP90?
    cut = cms.vstring("pt","eta","EcalGapCut"),
    electronLabel  = cms.InputTag("acceptedElectrons"),
    beamSpotLabel = cms.InputTag("offlineBeamSpot"),
    vertexLabel = cms.InputTag('offlinePrimaryVertices'),
    rhoIsoLabel = cms.InputTag('kt6PFJetsForIsolation','rho'),
    #conversionsInputTag = cms.InputTag("patConversions"),
    conversionsInputTag = cms.InputTag("allConversions"),
    eleIdSelector = eleSelectorPSet,
#eidHyperTight1MC eidLooseMC eidMediumMC eidSuperTightMC eidTightMC simpleEleId60relIso 70,80,85,95 pf_evspi pfevsmu
    #eidName = cms.untracked.string("eidTightMC"),
    #eidName = cms.untracked.string("eidTightMC"),
    #eidBitMask = cms.untracked.int32(5), # = 101, ID and cms.Conversion
    saveTree = cms.untracked.bool(False),
    #saveTree = cms.untracked.bool(True),
)

process.acceptedGsfElectrons = cms.EDFilter("PATElectronSelector",
    src = cms.InputTag("selectedPatElectrons"),
    cut = cms.string("pt > 20 && abs(eta) < 2.5"),
    #cut = cms.string("pt > 20 && abs(eta) < 2.5 && ecalDrivenSeed")
    filter = cms.bool(False),
)

#process.patElectronFilter = cms.EDFilter("CandViewCountFilter",
#    src = cms.InputTag('acceptedElectrons'),
#    minNumber = cms.uint32(1)
#)

############################
## Electron ID
############################
process.PassingWP95 = process.acceptedElectrons.clone()
process.PassingWP95.cut = cms.string(
    process.acceptedElectrons.cut.value() +
    " && (gsfTrack.trackerExpectedHitsInner.numberOfHits <= 1)"
    " && ((isEB"
    " && ( dr03TkSumPt/p4.Pt < 0.15 && dr03EcalRecHitSumEt/p4.Pt < 2.0 && dr03HcalTowerSumEt/p4.Pt < 0.12 )" 
    " && (sigmaIetaIeta<0.01)"
    " && ( -0.8<deltaPhiSuperClusterTrackAtVtx<0.8 )"
    " && ( -0.007<deltaEtaSuperClusterTrackAtVtx<0.007 )"
    " && (hadronicOverEm<0.15)"
    ")"
    " || (isEE"
    " && (dr03TkSumPt/p4.Pt < 0.08 && dr03EcalRecHitSumEt/p4.Pt < 0.06  && dr03HcalTowerSumEt/p4.Pt < 0.05 )"  
    " && (sigmaIetaIeta<0.03)"
    " && ( -0.7<deltaPhiSuperClusterTrackAtVtx<0.7 )"
    " && ( -0.01<deltaEtaSuperClusterTrackAtVtx<0.01 )"
    " && (hadronicOverEm<0.07) "
    "))"
    )

"""
process.PassingWCut = process.acceptedElectrons.clone()
process.PassingWCut.cut = cms.string(
    process.acceptedElectrons.cut.value() +
    " && (gsfTrack.trackerExpectedHitsInner.numberOfHits<=1 )"
    " && ((isEB"
    " && (sigmaIetaIeta<0.01)"
    " && ( -0.06<deltaPhiSuperClusterTrackAtVtx<0.06 )"
    " && ( -0.004<deltaEtaSuperClusterTrackAtVtx<0.004 )"
    " && (hadronicOverEm<0.12)"
    ")"
    " || (isEE"
    " && (sigmaIetaIeta<0.03)"
    " && ( -0.03<deltaPhiSuperClusterTrackAtVtx<0.03 )"
    " && ( -0.007<deltaEtaSuperClusterTrackAtVtx<0.007 )"
    " && (hadronicOverEm<0.10) "
    "))"
    )
"""
########################################
########################################
# Matching
########################################
########################################

############################
# Trigger Matching
############################
# trgMatchedGsfElectronProducer can deal with PF Electron

#process.MessageLogger.suppressWarning.append("myModuleName")

process.PassingHLT = cms.EDProducer("trgMatchedGsfElectronProducer",    
#process.PassingHLT = cms.EDProducer("trgMatchedPFElectronProducer",    
    InputProducer = cms.InputTag( "PassingWCut" ),                          
    #InputProducer = cms.InputTag( "PassingWP80" ),                          
    #InputProducer = cms.InputTag( ELECTRON_COLL ),
                                    
    matchUnprescaledTriggerOnly = cms.untracked.bool(False),
    #isTriggerOR = cms.untracked.bool(True),
                                    
    #hltTags = cms.VInputTag(cms.InputTag(HLTPath,"", HLTProcessName)),
    hltTags = cms.VInputTag(
    cms.InputTag(HLTPath1,"", HLTProcessName),
    cms.InputTag(HLTPath2,"", HLTProcessName),
    cms.InputTag(HLTPath3,"", HLTProcessName),
    cms.InputTag(HLTPath4,"", HLTProcessName),
    ),
    triggerEventTag = cms.untracked.InputTag("hltTriggerSummaryAOD","",HLTProcessName),
    triggerResultsTag = cms.untracked.InputTag("TriggerResults","",HLTProcessName)
)


################################
# SC PF matching
#################################
process.PfMatchedSuperClusterCands = cms.EDProducer("ElectronMatchedCandidateProducer",
   src     = cms.InputTag("goodSuperClustersClean"),
   ReferenceElectronCollection = cms.untracked.InputTag("acceptedElectrons"),
   #ReferenceElectronCollection = cms.untracked.InputTag("goodElectrons"),
   deltaR =  cms.untracked.double(0.3)
)
################################
# PF  ID matching
#################################
process.IdMatchedPfCands = cms.EDProducer("ElectronMatchedCandidateProducer",
   src     = cms.InputTag("acceptedElectrons"),
   ReferenceElectronCollection = cms.untracked.InputTag("PassingWCut"),
   #ReferenceElectronCollection = cms.untracked.InputTag("goodElectrons"),
   deltaR =  cms.untracked.double(0.3)
)


#############################
## Tag Definition
#############################

process.Tag = process.PassingHLT.clone()
#process.Tag = process.PassingWCut.clone()
process.Tag.InputProducer = cms.InputTag( "PassingWCut" )

process.TagMatchedSuperClusterCandsClean = cms.EDProducer("ElectronMatchedCandidateProducer",
   src     = cms.InputTag("goodSuperClustersClean"),
   ReferenceElectronCollection = cms.untracked.InputTag("Tag"),
   deltaR =  cms.untracked.double(0.3)
)
process.WCutMatchedSuperClusterCandsClean = process.TagMatchedSuperClusterCandsClean.clone()
process.WCutMatchedSuperClusterCandsClean.ReferenceElectronCollection = cms.untracked.InputTag("PassingWCut")

process.ele_sequence = cms.Sequence(
    process.acceptedElectrons +
    process.allConversions +
    #process.PassingWP80 +
    process.PfMatchedSuperClusterCands +
    process.PassingWCut +
    process.IdMatchedPfCands +
    process.PassingHLT +
    process.Tag +
    process.WCutMatchedSuperClusterCandsClean
    )
#############################
# MC Matches
#############################
process.McMatchTag = cms.EDProducer("MCTruthDeltaRMatcherNew",
    matchPDGId = cms.vint32(11),
    src = cms.InputTag("Tag"),
    distMin = cms.double(0.3),
    matched = cms.InputTag("genParticles"),
    checkCharge = cms.bool(True)
)
process.McMatchSC = cms.EDProducer("MCTruthDeltaRMatcherNew",
    matchPDGId = cms.vint32(11),
    src = cms.InputTag("goodSuperClustersClean"),
    distMin = cms.double(0.3),
    matched = cms.InputTag("genParticles")
)

process.McMatchWCut = process.McMatchTag.clone()
process.McMatchWCut.src = cms.InputTag("PassingWCut")

process.McMatchPf = process.McMatchTag.clone()
process.McMatchPf.src = cms.InputTag("acceptedElectrons")

process.mc_sequence = cms.Sequence(
    process.McMatchTag +
    process.McMatchSC +
    process.McMatchWCut +
    process.McMatchPf
    #process.McMatchWP80
    )
#############################
## Tag and Probe selection
#############################
process.tagSC = cms.EDProducer("CandViewShallowCloneCombiner",
    decay = cms.string("Tag goodSuperClustersClean"), # charge coniugate states are implied, charge conjugate decays are always implied (https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideCandCombiner#CandViewShallowCloneCombiner )
    checkCharge = cms.bool(False),# decay, no charge, no check 
    #checkCharge = cms.bool(True),# decay, no charge, no check 
    cut   = cms.string("60 < mass < 120"),
    #cut   = cms.string("40 < mass < 1000"),
)
process.tagPf = process.tagSC.clone()
process.tagPf.decay = cms.string("Tag acceptedElectrons")

process.tagWCut = process.tagSC.clone()
process.tagWCut.decay = cms.string("Tag PassingWCut")

process.allTagsAndProbes = cms.Sequence(
    process.tagSC +
    process.tagPf+
    process.tagWCut
    #process.tagWP80
    )
############################################################################
##    _____           _       _ ____            _            _   _  ____  ##
##   |_   _|_ _  __ _( )_ __ ( )  _ \ _ __ ___ | |__   ___  | \ | |/ ___| ##
##     | |/ _` |/ _` |/| '_ \|/| |_) | '__/ _ \| '_ \ / _ \ |  \| | |  _  ##
##     | | (_| | (_| | | | | | |  __/| | | (_) | |_) |  __/ | |\  | |_| | ##
##     |_|\__,_|\__, | |_| |_| |_|   |_|  \___/|_.__/ \___| |_| \_|\____| ##
##              |___/                                                     ##
##                                                                        ##
############################################################################
##    ____                      _     _           
##   |  _ \ ___ _   _ ___  __ _| |__ | | ___  ___ 
##   | |_) / _ \ | | / __|/ _` | '_ \| |/ _ \/ __|
##   |  _ <  __/ |_| \__ \ (_| | |_) | |  __/\__ \
##   |_| \_\___|\__,_|___/\__,_|_.__/|_|\___||___/
##
## I define some common variables for re-use later.
## This will save us repeating the same code for each efficiency category

##  offline selection --> HLT. First specify which quantities to store in the TP tree. 
if MC_flag:
    HLTmcTruthCommonStuff = cms.PSet(
        isMC = cms.bool(MC_flag),
        tagMatches = cms.InputTag("McMatchTag"),
        motherPdgId = cms.vint32(22,23),
        makeMCUnbiasTree = cms.bool(MC_flag),
        checkMotherInUnbiasEff = cms.bool(MC_flag),
        mcVariables = cms.PSet(
          probe_eta = cms.string("eta"),
          probe_phi  = cms.string("phi"),
          probe_et  = cms.string("et"),
          probe_charge = cms.string("charge"),
        ),
        mcFlags     =  cms.PSet(
          probe_flag = cms.string("pt>0")
        ),      
        )
else:
     HLTmcTruthCommonStuff = cms.PSet(
         isMC = cms.bool(False)
         )
if MC_flag:
    mcTruthCommonStuff = cms.PSet(
        isMC = cms.bool(MC_flag),
        tagMatches = cms.InputTag("McMatchTag"),
        motherPdgId = cms.vint32(22,23),
        makeMCUnbiasTree = cms.bool(MC_flag),
        checkMotherInUnbiasEff = cms.bool(MC_flag),
        mcVariables = cms.PSet(
        probe_eta = cms.string("eta"),
        probe_pt  = cms.string("pt"),
        probe_phi  = cms.string("phi"),
        probe_et  = cms.string("et"),
        probe_e  = cms.string("energy"),
        probe_p  = cms.string("p"),
        probe_px  = cms.string("px"),
        probe_py  = cms.string("py"),
        probe_pz  = cms.string("pz"),
        probe_theta  = cms.string("theta"),    
        probe_vx     = cms.string("vx"),
        probe_vy     = cms.string("vy"),
        probe_vz     = cms.string("vz"),   
        probe_charge = cms.string("charge"),
        probe_rapidity  = cms.string("rapidity"),    
        probe_mass  = cms.string("mass"),
        probe_mt  = cms.string("mt"),    
        ),
        mcFlags     =  cms.PSet(
        probe_flag = cms.string("pt>0")
        ),      
        )
else:
     mcTruthCommonStuff = cms.PSet(
         isMC = cms.bool(False)
         )
ZVariablesToStore = cms.PSet(
    eta = cms.string("eta"),
    pt  = cms.string("pt"),
    phi  = cms.string("phi"),
    et  = cms.string("et"),
    e  = cms.string("energy"),
    p  = cms.string("p"),
    px  = cms.string("px"),
    py  = cms.string("py"),
    pz  = cms.string("pz"),
    theta  = cms.string("theta"),    
    vx     = cms.string("vx"),
    vy     = cms.string("vy"),
    vz     = cms.string("vz"),
    rapidity  = cms.string("rapidity"),
    mass  = cms.string("mass"),
    mt  = cms.string("mt"),    
)   
ProbeVariablesToStore = cms.PSet(
    probe_eta = cms.string("eta"),
    probe_pt  = cms.string("pt"),
    probe_phi  = cms.string("phi"),
    probe_et  = cms.string("et"),
    probe_e  = cms.string("energy"),
    probe_p  = cms.string("p"),
    probe_px  = cms.string("px"),
    probe_py  = cms.string("py"),
    probe_pz  = cms.string("pz"),
    probe_theta  = cms.string("theta"),    
    probe_charge = cms.string("charge"),
    probe_rapidity  = cms.string("rapidity"),
    probe_missingHits = cms.string("gsfTrack.trackerExpectedHitsInner.numberOfHits"),
    probe_convDist = cms.string("convDist"),
    probe_convDcot = cms.string("convDcot"),
    probe_convRadius = cms.string("convRadius"),        
    probe_hasValidHitInFirstPixelBarrel = cms.string("gsfTrack.hitPattern.hasValidHitInFirstPixelBarrel"),
    ## super cluster quantities
    probe_sc_energy = cms.string("superCluster.energy"),
    probe_sc_et    = cms.string("superCluster.energy*sin(superClusterPosition.theta)"),    
    probe_sc_x      = cms.string("superCluster.x"),
    probe_sc_y      = cms.string("superCluster.y"),
    probe_sc_z      = cms.string("superCluster.z"),
    probe_sc_eta    = cms.string("superCluster.eta"),
    probe_sc_theta  = cms.string("superClusterPosition.theta"),   
    probe_sc_phi    = cms.string("superCluster.phi"),
    probe_sc_size   = cms.string("superCluster.size"), # number of hits
    ## track quantities
    probe_track_p      = cms.string("gsfTrack.p"),
    probe_track_pt     = cms.string("gsfTrack.pt"),    
    probe_track_px     = cms.string("gsfTrack.px"),
    probe_track_py     = cms.string("gsfTrack.py"),
    probe_track_pz     = cms.string("gsfTrack.pz"),
    probe_track_eta    = cms.string("gsfTrack.eta"),
    probe_track_theta  = cms.string("gsfTrack.theta"),   
    probe_track_phi    = cms.string("gsfTrack.phi"),
    probe_track_vx     = cms.string("gsfTrack.vx"),
    probe_track_vy     = cms.string("gsfTrack.vy"),
    probe_track_vz     = cms.string("gsfTrack.vz"),    
    probe_track_dxy    = cms.string("gsfTrack.dxy"),
    probe_track_d0     = cms.string("gsfTrack.d0"),
    probe_track_dsz    = cms.string("gsfTrack.dsz"),
    probe_track_charge = cms.string("gsfTrack.charge"),
    probe_track_qoverp = cms.string("gsfTrack.qoverp"),
    probe_track_normalizedChi2 = cms.string("gsfTrack.normalizedChi2"),
    ## isolation 
    probe_trackiso = cms.string("dr03TkSumPt"),
    probe_ecaliso  = cms.string("dr03EcalRecHitSumEt"),
    probe_hcaliso  = cms.string("dr03HcalTowerSumEt"),
    ## classification, location, etc.    
    probe_classification = cms.string("classification"),
    probe_numberOfBrems  = cms.string("numberOfBrems"),     
    probe_bremFraction   = cms.string("fbrem"),
    probe_mva            = cms.string("mva"),        
    probe_deltaEta       = cms.string("deltaEtaSuperClusterTrackAtVtx"),
    probe_deltaPhi       = cms.string("deltaPhiSuperClusterTrackAtVtx"),
    probe_deltaPhiOut    = cms.string("deltaPhiSeedClusterTrackAtCalo"),
    probe_deltaEtaOut    = cms.string("deltaEtaSeedClusterTrackAtCalo"),
    probe_isEB           = cms.string("isEB"),
    probe_isEE           = cms.string("isEE"),
    probe_isGap          = cms.string("isGap"),
    ## Hcal energy over Ecal Energy
    probe_HoverE         = cms.string("hcalOverEcal"),    
    probe_EoverP         = cms.string("eSuperClusterOverP"),
    probe_eSeedClusterOverP = cms.string("eSeedClusterOverP"),    
    ## Cluster shape information
    probe_sigmaEtaEta  = cms.string("sigmaEtaEta"),
    probe_sigmaIetaIeta = cms.string("sigmaIetaIeta"),
    probe_e1x5               = cms.string("e1x5"),
    probe_e2x5Max            = cms.string("e2x5Max"),
    probe_e5x5               = cms.string("e5x5"),
    ## is ECAL driven ? is Track driven ?
    probe_ecalDrivenSeed     = cms.string("ecalDrivenSeed"),
    probe_trackerDrivenSeed  = cms.string("trackerDrivenSeed")
)

TagVariablesToStore = cms.PSet(
    eta = cms.string("eta"),
    pt  = cms.string("pt"),
    phi  = cms.string("phi"),
    et  = cms.string("et"),
    e  = cms.string("energy"),
    p  = cms.string("p"),
    px  = cms.string("px"),
    py  = cms.string("py"),
    pz  = cms.string("pz"),
    theta  = cms.string("theta"),    
    charge = cms.string("charge"),
    rapidity  = cms.string("rapidity"),
    missingHits = cms.string("gsfTrack.trackerExpectedHitsInner.numberOfHits"),
    convDist = cms.string("convDist"),
    convDcot = cms.string("convDcot"),
    convRadius = cms.string("convRadius"),     
    hasValidHitInFirstPixelBarrel = cms.string("gsfTrack.hitPattern.hasValidHitInFirstPixelBarrel"),
    ## super cluster quantities
    sc_energy = cms.string("superCluster.energy"),
    sc_et     = cms.string("superCluster.energy*sin(superClusterPosition.theta)"),    
    sc_x      = cms.string("superCluster.x"),
    sc_y      = cms.string("superCluster.y"),
    sc_z      = cms.string("superCluster.z"),
    sc_eta    = cms.string("superCluster.eta"),
    sc_theta  = cms.string("superClusterPosition.theta"),      
    sc_phi    = cms.string("superCluster.phi"),
    sc_size   = cms.string("superCluster.size"), # number of hits
    ## track quantities
    track_p      = cms.string("gsfTrack.p"),
    track_pt     = cms.string("gsfTrack.pt"),    
    track_px     = cms.string("gsfTrack.px"),
    track_py     = cms.string("gsfTrack.py"),
    track_pz     = cms.string("gsfTrack.pz"),
    track_eta    = cms.string("gsfTrack.eta"),
    track_theta  = cms.string("gsfTrack.theta"),   
    track_phi    = cms.string("gsfTrack.phi"),
    track_vx     = cms.string("gsfTrack.vx"),
    track_vy     = cms.string("gsfTrack.vy"),
    track_vz     = cms.string("gsfTrack.vz"),    
    track_dxy    = cms.string("gsfTrack.dxy"),
    track_d0     = cms.string("gsfTrack.d0"),
    track_dsz    = cms.string("gsfTrack.dsz"),
    track_charge = cms.string("gsfTrack.charge"),
    track_qoverp = cms.string("gsfTrack.qoverp"),
    track_normalizedChi2 = cms.string("gsfTrack.normalizedChi2"),    
    ## isolation 
    trackiso = cms.string("dr03TkSumPt"),
    ecaliso  = cms.string("dr03EcalRecHitSumEt"),
    hcaliso  = cms.string("dr03HcalTowerSumEt"),
    ## classification, location, etc.    
    classification = cms.string("classification"),
    numberOfBrems  = cms.string("numberOfBrems"),     
    bremFraction   = cms.string("fbrem"),
    mva            = cms.string("mva"),        
    deltaEta       = cms.string("deltaEtaSuperClusterTrackAtVtx"),
    deltaPhi       = cms.string("deltaPhiSuperClusterTrackAtVtx"),
    deltaPhiOut    = cms.string("deltaPhiSeedClusterTrackAtCalo"),
    deltaEtaOut    = cms.string("deltaEtaSeedClusterTrackAtCalo"),
    isEB           = cms.string("isEB"),
    isEE           = cms.string("isEE"),
    isGap          = cms.string("isGap"),
    ## Hcal energy over Ecal Energy
    HoverE         = cms.string("hcalOverEcal"),    
    EoverP         = cms.string("eSuperClusterOverP"),
    eSeedClusterOverP = cms.string("eSeedClusterOverP"),  
    ## Cluster shape information
    sigmaEtaEta  = cms.string("sigmaEtaEta"),
    sigmaIetaIeta = cms.string("sigmaIetaIeta"),
    e1x5               = cms.string("e1x5"),
    e2x5Max            = cms.string("e2x5Max"),
    e5x5               = cms.string("e5x5"),
    ## is ECAL driven ? is Track driven ?
    ecalDrivenSeed     = cms.string("ecalDrivenSeed"),
    trackerDrivenSeed  = cms.string("trackerDrivenSeed")
)

CommonStuffForPfElectronProbe = cms.PSet(
    variables = cms.PSet(ProbeVariablesToStore),
    ignoreExceptions =  cms.bool (False),
    addRunLumiInfo   =  cms.bool (True),
    addEventVariablesInfo   =  cms.bool (True),
    pairVariables =  cms.PSet(ZVariablesToStore),
    pairFlags     =  cms.PSet(
          mass60to120 = cms.string("60 < mass < 120")
    ),
    tagVariables   =  cms.PSet(TagVariablesToStore),
    tagFlags     =  cms.PSet(
          passingPf = cms.InputTag("acceptedElectrons"),
          isWCut = cms.InputTag("PassingWCut"),
          passingHLT = cms.InputTag("PassingHLT")     
    ),    
)

CommonStuffForSuperClusterProbe = CommonStuffForPfElectronProbe.clone()
CommonStuffForSuperClusterProbe.variables = cms.PSet(
    probe_sc_eta = cms.string("eta"),
    probe_sc_pt  = cms.string("pt"),
    probe_sc_phi  = cms.string("phi"),
    probe_sc_et  = cms.string("et"),
    probe_sc_e  = cms.string("energy"),
    probe_sc_p  = cms.string("p"),
    probe_sc_px  = cms.string("px"),
    probe_sc_py  = cms.string("py"),
    probe_sc_pz  = cms.string("pz"),
    probe_sc_theta  = cms.string("theta"),
    )

##########################################################
##########################################################
# TagProbeFitTreeProducer
##########################################################
##########################################################

############################################
# SC -> PF
############################################
## super cluster --> PF electron
process.SuperClusterToPFElectron = cms.EDAnalyzer("TagProbeFitTreeProducer",
    ## pick the defaults
    CommonStuffForSuperClusterProbe, mcTruthCommonStuff,
    # choice of tag and probe pairs, and arbitration                 
    tagProbePairs = cms.InputTag("tagSC"),
    arbitration   = cms.string("Random2"),                      
    flags = cms.PSet(
        probe_passingPf = cms.InputTag("PfMatchedSuperClusterCands"),        
        probe_isWCut = cms.InputTag("WCutMatchedSuperClusterCandsClean"),
        #probe_passingHLT = cms.InputTag("TagMatchedSuperClusterCandsClean")
    ),
    probeMatches  = cms.InputTag("McMatchSC"),
    allProbes     = cms.InputTag("goodSuperClustersClean")
)
##################################
# PF Electron to ID
##################################
process.PfElectronToId = cms.EDAnalyzer("TagProbeFitTreeProducer",
    mcTruthCommonStuff, CommonStuffForPfElectronProbe,                        
    tagProbePairs = cms.InputTag("tagPf"),
    arbitration   = cms.string("Random2"),
    flags = cms.PSet(
        probe_isWCut = cms.InputTag("IdMatchedPfCands"),
    ),
    probeMatches  = cms.InputTag("McMatchPf"),
    allProbes     = cms.InputTag("acceptedElectrons")
)


################################
# ID -> HLT
################################
##  WCut --> HLT
################################
process.WCutToHLT = cms.EDAnalyzer("TagProbeFitTreeProducer",
    HLTmcTruthCommonStuff,                                
    variables = cms.PSet(
      probe_eta = cms.string("eta"),
      probe_phi  = cms.string("phi"),
      probe_et  = cms.string("et"),
      probe_charge = cms.string("charge"),
      probe_sc_et    = cms.string("superCluster.energy*sin(superClusterPosition.theta)"),    
      probe_sc_eta    = cms.string("superCluster.eta"), 
      probe_sc_phi    = cms.string("superCluster.phi"),
      probe_isEB           = cms.string("isEB"),
      probe_isEE           = cms.string("isEE"),
      probe_isGap          = cms.string("isGap"),
    ),
    ignoreExceptions =  cms.bool (False),
    addRunLumiInfo   =  cms.bool (False),
    addEventVariablesInfo   =  cms.bool (False),                                                        
    tagProbePairs = cms.InputTag("tagWCut"),
    arbitration   = cms.string("Random2"),
    flags = cms.PSet( 
        probe_passingHLT = cms.InputTag("PassingHLT")        
    ),
    probeMatches  = cms.InputTag("McMatchWCut"),
    allProbes     = cms.InputTag("PassingWCut")
)
#if MC_flag:
#    process.WP95ToHLT.PUWeightSrc = cms.InputTag("pileupReweightingProducer","pileupWeights")


process.tree_sequence = cms.Sequence(
    process.WCutToHLT +
    process.SuperClusterToPFElectron +
    process.PfElectronToId
    #process.WP80ToHLT
    )

####################
## Path
####################
process.nEventsTotal = cms.EDProducer("EventCountProducer")
process.nEventsNoscrap = cms.EDProducer("EventCountProducer")
process.nEventsHBHE = cms.EDProducer("EventCountProducer")
#process.nEventsClean = cms.EDProducer("EventCountProducer")
process.nEventsHLT = cms.EDProducer("EventCountProducer")
process.nEventsFiltered = cms.EDProducer("EventCountProducer")

#process.load( "L1Trigger.Configuration.L1RawToDigi_cff" )

#process.load("L1Trigger.Skimmer.l1Filter_cfi")
#process.l1Filter.algorithms = cms.vstring('L1_SingleEG22')

#process.p = cms.Path(
#process.p +=   process.l1GtRecord
process.p +=   process.nEventsTotal
process.p +=   process.noscraping
process.p +=   process.nEventsNoscrap
process.p +=   process.goodOfflinePrimaryVertices
process.p +=   process.HBHENoiseFilter 
process.p +=   process.nEventsHBHE
#    process.nEventsClean
#    process.patElectronIDs*
#    process.eidCiCSequence
#)

#process.p += process.hltHighLevelMuMuRD
process.p += process.nEventsHLT
process.p += process.sc_sequence
process.p += getattr(process,"patPF2PATSequence"+postfix)
#process.p += process.looseLeptonSequence
#process.p += process.patElectronFilter
process.p += process.ele_sequence
process.p += process.nEventsFiltered

#
#process.p += process.l1Filter

process.p += process.allTagsAndProbes
print "hahaha"
if MC_flag:
  print "hohoho"
  process.p += process.mc_sequence

process.p += process.tree_sequence

#from PhysicsTools.PatAlgos.tools.trigTools import *
#switchOnTrigger( process )

#from PhysicsTools.PatAlgos.tools.coreTools import *
#removeMCMatching(process, ['Electrons'])
#runOnData(process)
#process.patElectrons.pfElectronSource = 'particleFlow'



#if MC_flag:
  #process.p += process.eIDSequence

#else:
  #process.p += process.eIDSequence



#process.outpath = cms.EndPath(process.out)
