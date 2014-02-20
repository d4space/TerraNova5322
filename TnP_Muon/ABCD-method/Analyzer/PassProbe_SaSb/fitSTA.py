import FWCore.ParameterSet.Config as cms

import sys
if (len(sys.argv) !=3):
  #               0    1     2
  print "Usage: cmsRun %s RD(MC)all_space(eta,pt,vtx)plus(minus)" %sys.argv[1]
  sys.exit(0)

args = sys.argv[1:]
if (sys.argv[0] == "cmsRun"): args =sys.argv[2:]
scenario = "MC"
if len(args) > 0: scenario = args[0]
print "Will run scenario ", scenario 

if "plus" in scenario:
  charge_ = cms.vdouble(0,1)
elif "minus" in scenario:
  charge_ = cms.vdouble(-1,0)
else:
  print "Usage: cmsRun %s RD(MC)all_space(eta, vtx)plus(minus)" %sys.argv[1]
  sys.exit(0)

process = cms.Process("TagProbe")

process.load('FWCore.MessageService.MessageLogger_cfi')

process.source = cms.Source("EmptySource")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )

Template = cms.EDAnalyzer("TagProbeFitTreeAnalyzer",
    NumCPU = cms.uint32(1),
    SaveWorkspace = cms.bool(False),

    Variables = cms.PSet(
        mass = cms.vstring("Tag-muon Mass", "76", "125", "GeV/c^{2}"),
        pt = cms.vstring("muon p_{T}", "0", "1000", "GeV/c"),
        eta    = cms.vstring("muon #eta", "-2.5", "2.5", ""),
        abseta = cms.vstring("muon |#eta|", "0", "2.5", ""),
        charge = cms.vstring("Probe charge", "-1", "1", ""),
        isTrakerMu = cms.vstring("Probe TrackerMuon", "-1", "1", ""),
        #tag_nVertices = cms.vstring("Number of vertices", "0", "999", ""),
        #pfCombRelIso04EACorr = cms.vstring("Number of vertices", "0", "999", ""),
        #SIP = cms.vstring("Number of vertices", "0", "999", ""),
        #run = cms.vstring("Number of vertices", "-999", "999999", ""),
        #HLT_Mu8  = cms.vstring("Mu8 leg",  "-1", "2", ""),
        #HLT_Mu17 = cms.vstring("Mu17 leg", "-1", "2", ""),
    ),

    Categories = cms.PSet(
        Glb   = cms.vstring("Global", "dummy[pass=1,fail=0]"),
        PF    = cms.vstring("PF Muon", "dummy[pass=1,fail=0]"),
        TM    = cms.vstring("Tracker Muon", "dummy[pass=1,fail=0]"),
        #mvaIsoCut = cms.vstring("MC true", "dummy[pass=1,fail=0]"),
        mcTrue = cms.vstring("MC true", "dummy[true=1,false=0]"),
    ),
    Cuts = cms.PSet(),
    PDFs = cms.PSet(
        voigtPlusExpo = cms.vstring(
            "Voigtian::signal(mass, mean[90,80,100], width[2.495], sigma[3,1,20])",
            "Exponential::backgroundPass(mass, lp[0,-5,5])",
            "Exponential::backgroundFail(mass, lf[0,-5,5])",
            "efficiency[0.9,0,1]",
            "signalFractionInPassing[0.9]"
        ),
        vpvPlusExpo = cms.vstring(
            "Voigtian::signal1(mass, mean1[90,80,100], width[2.495], sigma1[2,1,3])",
            "Voigtian::signal2(mass, mean2[90,80,100], width,        sigma2[4,2,10])",
            "SUM::signal(vFrac[0.8,0,1]*signal1, signal2)",
            "Exponential::backgroundPass(mass, lp[-0.1,-1,0.1])",
            "Exponential::backgroundFail(mass, lf[-0.1,-1,0.1])",
            "efficiency[0.9,0,1]",
            "signalFractionInPassing[0.9]"
        ),
        vpvPlusExpoMin70 = cms.vstring(
            "Voigtian::signal1(mass, mean1[90,80,100], width[2.495], sigma1[2,1,3])",
            "Voigtian::signal2(mass, mean2[90,80,100], width,        sigma2[4,3,10])",
            "SUM::signal(vFrac[0.8,0.5,1]*signal1, signal2)",
            "Exponential::backgroundPass(mass, lp[-0.1,-1,0.1])",
            "Exponential::backgroundFail(mass, lf[-0.1,-1,0.1])",
            "efficiency[0.9,0.7,1]",
            "signalFractionInPassing[0.9]"
        )
    ),

    binnedFit = cms.bool(True),
    binsForFit = cms.uint32(40),
    saveDistributionsPlot = cms.bool(False),

    Efficiencies = cms.PSet(), # will be filled later
)

CONSTRAINTS = cms.PSet(
    charge = charge_,
    isTrakerMu = cms.vdouble(0,1),
)
# PT_ETA_BINS = cms.PSet(CONSTRAINTS,
#     pt     = cms.vdouble(  3, 5, 7, 10, 15, 20, 30, 40, 100 ),
#     abseta = cms.vdouble(  0.0, 1.2, 2.4)
# )
# Cris' bins
PT_ETA_BINS = cms.PSet(CONSTRAINTS,
    pt     = cms.vdouble(  10, 20, 30, 40, 60, 100 ),
    abseta = cms.vdouble(  0.0, 1.2, 2.4)
)
PT_BINS = cms.PSet(CONSTRAINTS,
    #pt     = cms.vdouble( 5, 10,13, 15, 17, 18, 20, 25, 30, 40, 100 ),
    pt     = cms.vdouble( 20,200 ),
    eta = cms.vdouble( -2.1, 2.1)
)
# ETA_BINS = cms.PSet(CONSTRAINTS,
#     pt  = cms.vdouble(20,100),
#     eta = cms.vdouble(*[x/10. for x in xrange(-24,25,1)]),    
# )
# Cris' bins
ETA_BINS = cms.PSet(CONSTRAINTS,
    #pt  = cms.vdouble(25,100),
    pt  = cms.vdouble(20,200),
    #eta = cms.vdouble(-2.1,-1.68,-1.26,-0.84,-0.42, 0,0.42,0.84, 1.26, 1.68, 2.1)
    eta = cms.vdouble(-2.1, 2.1)
    #eta = cms.vdouble(-2.4, -2.1, -1.6, -1.1, -0.6, 0, 0.6, 1.1, 1.6, 2.1, 2.4),
)
# VTX_BINS  = cms.PSet(CONSTRAINTS,
#     pt     = cms.vdouble(  20, 120 ),
#     abseta = cms.vdouble(  0.0, 2.4),
#     tag_nVertices = cms.vdouble(*[x-0.5 for x in range(21)])
# )
# Cris' bins
VTX_BINS  = cms.PSet(CONSTRAINTS,
    pt     = cms.vdouble(  20, 120 ),
    abseta = cms.vdouble(  0.0, 2.4),
    #tag_nVertices = cms.vdouble(0.5,2.5,4.5,6.5,8.5,10.5,12.5,14.5,16.5,18.5,20.5)
    tag_nVertices = cms.vdouble(0.5,2.5,4.5,6.5,8.5,10.5,12.5,16.5,20.5,25,30,40)
)

process.TnP_TrkToSTA = Template.clone(
    InputFileNames = cms.vstring(),
    InputTreeName = cms.string("fitter_tree"),
    InputDirectoryName = cms.string("tpTree"),
    OutputFileName = cms.string("TnP_TrkToSTA_%s.root" % scenario),
    Efficiencies = cms.PSet(),
)
#if "_weight" in scenario:
#    process.TnP_MuonID.WeightVariable = cms.string("weight")
#    process.TnP_MuonID.Variables.weight = cms.vstring("weight","0","10","")

#PREFIX="/terranova_1/W_TnP/Muon/V5/"


#PREFIX="/d2/scratch/knuhamid/Wpt-x-section/CMSSW_5_2_6/src/TerraNova/TnP_Muon/ABCD_Muon/crab_roots/"
PREFIX="/d2/scratch/knuhamid/Wpt-x-section/CMSSW_5_2_6/src/TerraNova/TnP_Muon/ABCD_Muon/Khakim_crab_roots/"

#PREFIX="/afs/cern.ch/work/g/gpetrucc/CMSSW_5_2_4_patch4/src/MuonAnalysis/TagAndProbe/test/zmumu/"
if "RD" in scenario:
    process.TnP_TrkToSTA.InputFileNames = cms.vstring(
        PREFIX+'tnpZ_Data_Run2011A.root',
        #PREFIX+'tnpZ_Data_Run2011B_upTo194479.root',
        #PREFIX+'tnpZ_Data_Run2011B_194480-195016.root',
    )
elif "MC" in scenario:
    process.TnP_TrkToSTA.InputFileNames = [
        PREFIX+"tnpZ_MC_DYToMuMu.root",
    ]
else:
  print "Usage: cmsRun %s RD(MC)all_space(eta,pt,vtx)plus(minus)" %sys.argv[1]
  sys.exit(0)

#IDS = [ "PF", "SIP4_from_PF", "PFIso25_from_PF_and_SIP4", "PFIso40_from_PF_and_SIP4", "mvaIsoCut_from_PF_and_SIP4" ]
IDS = [ "Glb"]

if "all_space"  in scenario:
  ALLBINS = [("pt",PT_BINS),("eta", ETA_BINS)]
elif "pt"  in scenario:
  ALLBINS = [("pt",PT_BINS)]
elif "eta"  in scenario:
  ALLBINS = [("eta", ETA_BINS)]
else:
  print "Usage: cmsRun %s RD(MC)all_space(eta,pt,vtx)plus(minus)" %sys.argv[1]
  sys.exit(0)
#ALLBINS += [ ("vtx",VTX_BINS)]

#if len(args) > 1 and args[1] not in IDS: IDS += [ args[1] ]
for ID in IDS:
    #if len(args) > 1 and ID != args[1]: continue
    for X,B in ALLBINS:
        #if len(args) > 2 and X not in args[2:]: continue
        module = process.TnP_TrkToSTA.clone(OutputFileName = cms.string("TnP_TrkToSTA_%s_%s_%s.root" % (scenario, ID, X)))
        shape = "vpvPlusExpo"
        #if "eta" in X and not "abseta" in X: shape = "voigtPlusExpo"
        #if "pt_abseta" in X: shape = "voigtPlusExpo"
        #if "Mu17" in ID and "pt_abseta" in X: B = PT_ETA_BINS_MU17
        #if "Mu8" in ID and "pt_abseta" in X: B = PT_ETA_BINS_MU8
        DEN = B.clone(); num = ID; numstate = "pass"
        #if "_from_" in ID:
        #    parts = ID.split("_from_")
        #    num = parts[0]
        #    for D in parts[1].split("_and_"):
        #        if D == "SIP4":      DEN.SIP = cms.vdouble(0,4.0)
        #        elif D == "PFIso25": DEN.pfCombRelIso04EACorr  = cms.vdouble(0,0.25)
        #        elif D == "PFIso40": DEN.pfCombRelIso04EACorr  = cms.vdouble(0,0.40)
        #        else: setattr(DEN, D, cms.vstring("pass"))
        numString = cms.vstring()
        for N in num.split("_and_"):
            if N == "SIP4":
                module.Cuts.SIP4 = cms.vstring("SIP4","SIP", "4.0") 
                numString += [N, "below"]
            elif N == "PFIso25":
                module.Cuts.PFIso25 = cms.vstring("PFIso","pfCombRelIso04EACorr", "0.25") 
                numString += [N, "below"]
            elif N == "PFIso40":
                module.Cuts.PFIso40 = cms.vstring("PFIso","pfCombRelIso04EACorr", "0.40") 
                numString += [N, "below"]
            elif N in [ "HLT_Mu17", "HLT_Mu8" ]:
                setattr(module.Cuts, N+"_Pass", cms.vstring(N+"_Pass", N, "0.5")) 
                numString += [N+"_Pass", "above"]
            else:
                numString += [N, "pass"]
        setattr(module.Efficiencies, ID+"_"+X, cms.PSet(
            EfficiencyCategoryAndState = numString,
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = DEN,
            BinToPDFmap = cms.vstring(shape)
        ))
        if scenario.find("MC") != -1:
            setattr(module.Efficiencies, ID+"_"+X+"_mcTrue", cms.PSet(
                EfficiencyCategoryAndState = numString,
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = DEN.clone(mcTrue = cms.vstring("true"))
            ))
            #if "_weight" in scenario:
            #    getattr(module.Efficiencies, ID+"_"+X          ).UnbinnedVariables.append("weight")
            #    getattr(module.Efficiencies, ID+"_"+X+"_mcTrue").UnbinnedVariables.append("weight")
        setattr(process, "TnP_TrkToSTA_"+ID+"_"+X, module)        
        setattr(process, "run_"+ID+"_"+X, cms.Path(module))

