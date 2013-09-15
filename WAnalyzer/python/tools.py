import FWCore.ParameterSet.Config as cms
import os

from PhysicsTools.PatAlgos.tools.pfTools import *

def changeConeSize(process,postfix):
        #muons
        #applyPostfix(process,"muPFIsoValueNeutral04",postfix).deposits[0].deltaR = cms.double(0.3)
        #applyPostfix(process,"muPFIsoValueCharged04",postfix).deposits[0].deltaR = cms.double(0.3)
        #applyPostfix(process,"muPFIsoValueChargedAll04",postfix).deposits[0].deltaR = cms.double(0.3)
        #applyPostfix(process,"muPFIsoValuePU04",postfix).deposits[0].deltaR = cms.double(0.3)
        #applyPostfix(process,"muPFIsoValueGamma04",postfix).deposits[0].deltaR = cms.double(0.3)
        #electrons
        #applyPostfix(process,"elPFIsoValueNeutral04",postfix).deposits[0].deltaR = cms.double(0.3)
        #applyPostfix(process,"elPFIsoValueCharged04",postfix).deposits[0].deltaR = cms.double(0.3)
        #applyPostfix(process,"elPFIsoValueChargedAll04",postfix).deposits[0].deltaR = cms.double(0.3)
        #applyPostfix(process,"elPFIsoValuePU04",postfix).deposits[0].deltaR = cms.double(0.3)
        #applyPostfix(process,"elPFIsoValueGamma04",postfix).deposits[0].deltaR = cms.double(0.3)

	#electrons
	process.pfIsolatedElectrons.isolationValueMapsCharged = cms.VInputTag(cms.InputTag("elPFIsoValueCharged03PFId"))
	process.pfIsolatedElectrons.deltaBetaIsolationValueMap = cms.InputTag("elPFIsoValuePU03PFId")
	process.pfIsolatedElectrons.isolationValueMapsNeutral = cms.VInputTag(cms.InputTag("elPFIsoValueNeutral03PFId"),cms.InputTag("elPFIsoValueGamma03PFId"))
	process.patElectrons.isolationValues = cms.PSet(
	    pfChargedHadrons = cms.InputTag("elPFIsoValueCharged03PFId"),
	    pfChargedAll = cms.InputTag("elPFIsoValueChargedAll03PFId"),
	    pfPUChargedHadrons = cms.InputTag("elPFIsoValuePU03PFId"),
	    PfNeutralHadrons = cms.InputTag("elPFIsoValueNeutral03PFId"),
	    PfPhotons = cms.InputTag("elPFIsoValueGamma03PFId")
	    )

def rhoFor2011Aeff(process,postfix):
  from RecoJets.JetProducers.kt4PFJets_cfi import kt4PFJets
  process.kt6PFJetsForIsolation = kt4PFJets.clone( rParam = 0.6, doRhoFastjet = True)
  process.kt6PFJetsForIsolation.Rho_EtaMax = cms.double(2.5)
  process.p += process.kt6PFJetsForIsolation

def rhoFor2012Aeff(process,postfix):
 from RecoJets.Configuration.RecoPFJets_cff import kt6PFJets
 process.kt6PFJetsForIsolation = kt6PFJets.clone(doRhoFastjet = True,Rho_EtaMax = 2.5)
 process.p += process.kt6PFJetsForIsolation

#import RecoJets.Configuration.RecoPFJets_cff kt6PFJetsForRhoCorrection = RecoJets.Configuration.RecoPFJets_cff.kt6PFJets.clone(
#	doRhoFastjet = True,
#	Rho_EtaMax = 2.5
#)

def applyFastJet(process,postfix):
	process.pfPileUpPFlow.Enable = True
	process.pfPileUpPFlow.checkClosestZVertex = cms.bool(False)
	process.pfPileUpPFlow.Vertices = cms.InputTag('goodOfflinePrimaryVertices')
	process.pfJetsPFlow.doAreaFastjet = True 
	process.pfJetsPFlow.doRhoFastjet = False

	# Compute the mean pt per unit area (rho) from the
	# PFchs inputs
	from RecoJets.JetProducers.kt4PFJets_cfi import kt4PFJets
	process.kt6PFJetsPFlow = kt4PFJets.clone(
	    rParam = cms.double(0.6),
	    src = cms.InputTag('pfNoElectron'+postfix),
	    doAreaFastjet = cms.bool(True),
	    doRhoFastjet = cms.bool(True),
	    #voronoiRfact = cms.double(0.9)
	    )
        process.patJetCorrFactorsPFlow.rho = cms.InputTag("kt6PFJetsPFlow", "rho")


        # Add the PV selector and KT6 producer to the sequence
        getattr(process,"patPF2PATSequence"+postfix).replace(
           getattr(process,"pfNoElectron"+postfix),
           getattr(process,"pfNoElectron"+postfix)*process.kt6PFJetsPFlow )


def addLooseLeptons(process):
        process.patElectronsPFlow.pfElectronSource = "pfElectronsPFlow" 
        process.patMuonsPFlow.pfMuonSource = "pfMuonsPFlow" 
 
def topProjection(process, postfix=""):
	# top projections in PF2PAT:
        getattr(process,"pfNoPileUp"+postfix).enable = True
        getattr(process,"pfNoMuon"+postfix).enable = True
        getattr(process,"pfNoElectron"+postfix).enable = True
        getattr(process,"pfNoTau"+postfix).enable = False # to use tau-cleaned jet collection : True
	getattr(process,"pfNoJet"+postfix).enable = True
	#enable delta beta correction for muon selection in PF2PAT?
	getattr(process,"pfIsolatedMuons"+postfix).doDeltaBetaCorrection = True


from PhysicsTools.PatAlgos.patEventContent_cff import *
def updateEventContent(p):
    l = p.out.outputCommands[:]
    p.out.outputCommands = ['drop *']

    l.extend(patTriggerEventContent)
    l.extend(patExtraAodEventContent)
    l.extend(patEventContentNoCleaning)
    l.extend([
        'keep edmMergeableCounter_*_*_*',
        'keep *_goodOfflinePrimaryVertices*_*_*',
        'keep *_particleFlow_*_*',
        'keep *_acceptedMuons_*_*',
        'keep *_acceptedElectrons_*_*',
        'keep double_*PFlow*_rho_PAT',
    ])

    # Uniquify outputCommands
    s = set()
    for item in l:
        if item not in s:
            s.add(item)
            p.out.outputCommands.append(item)

