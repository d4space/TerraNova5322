import FWCore.ParameterSet.Config as cms

### USAGE:
###    cmsRun fitTrigger_Z.py <scenario>
### scenarios:
###   - data_all:    will fit tnpJPsi_Data.root with bins suitable for the current data
###   - datalike_mc: will fit tnpJPsi_{JPsiMuMu,ppMuX}_Spring10_0.117pb.root MC but
###                  with same config as data

import sys

if (len(sys.argv) != 3):
  #               0        1           2
  print "Usage: cmsRun %s RD(MC)eta(pt,vtx)plus(minus)" %sys.argv[1]
  sys.exit(0)
#args = sys.argv[1:]
if (sys.argv[0] == "cmsRun"): args =sys.argv[2:]
scenario = "RD"
if len(args) > 0: scenario = args[0]
scenario = sys.argv[2]
print "Will run scenario", scenario 

if "plus" in scenario:
  charge_ = cms.vdouble(0,1)
elif "minus" in scenario:
  charge_ = cms.vdouble(-1,0)
else:
  print "Usage: cmsRun %s RD(MC)eta(pt,vtx)plus(minus)" %sys.argv[1]
  sys.exit(0)

#if (scenario != "RD" and scenario != "MC"):
#  print "no such scenario", scenario
#  sys.exit(0)

#if (scenario == "RD"):
#  inputFile = "tnpZ_singleMuLoPU.root"
#if (scenario == "MC"):
#  inputFile = "tnpZ_DYToMuMu.root"


process = cms.Process("TagProbe")

process.load('FWCore.MessageService.MessageLogger_cfi')

process.source = cms.Source("EmptySource")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )

process.TnP_Trigger = cms.EDAnalyzer("TagProbeFitTreeAnalyzer",
    NumCPU = cms.uint32(1),
    # the pdf object with the initial and final state snapshots
    SaveWorkspace = cms.bool(False),
    #floatShapeParameters = cms.bool(True),
    #fixVars = cms.vstring("mean"),

    InputFileNames = cms.vstring('tnpZ_Data.root'),
    InputTreeName = cms.string("fitter_tree"),
    InputDirectoryName = cms.string("tpTree"),
    OutputFileName = cms.string("TnP_WptCutToTrig_%s.root" % scenario),

    # defines all the real variables of the probes available in the input tree and intended for use in the efficiencies
    Variables = cms.PSet(
        mass = cms.vstring("Tag-Probe Mass", "50", "130", "GeV/c^{2}"),
        #mass = cms.vstring("Tag-Probe Mass", "60", "140", "GeV/c^{2}"),
        pt     = cms.vstring("Probe p_{T}", "0", "1000", "GeV/c"),
        eta    = cms.vstring("Probe |#eta|", "-2.5", "2.5", ""),
        abseta = cms.vstring("Probe |#eta|", "0", "2.5", ""),
        charge = cms.vstring("Probe charge", "-1", "1", ""),
        #tag_pt = cms.vstring("Tag p_{T}", "2.6", "1000", "GeV/c"),
        isPFMu =                 cms.vstring("PF Muon","-1","1",""),
        isGlbMu =                cms.vstring("Glb Muon","-1","1",""),
        glbChi2 =                cms.vstring("Glb Chi2","-10","1000",""),
        glbValidMuHits =         cms.vstring("Glb MuHits","0","50",""),
        numberOfMatchedStations =cms.vstring("NumOfMatchStations","-2","20",""),
        dB =                     cms.vstring("dB","0","100",""),
        tkDz =                   cms.vstring("tkDz","-100","100",""),
        tkTrackerLay =           cms.vstring("tkrLay","0","50",""),
        tkValidPixelHits =       cms.vstring("tkPixelHits","0","50",""),
        combRelIsoPF04dBeta =    cms.vstring("combIsoPF04","0","20",""),
    ),

    # defines all the discrete variables of the probes available in the input tree and intended for use in the efficiency calculations
    Categories = cms.PSet(
        #Calo = cms.vstring("POG_Glb",  "dummy[pass=1,fail=0]"),
        #Glb  = cms.vstring("POG_Glb",  "dummy[pass=1,fail=0]"),
        #VBTF = cms.vstring("VBTFLike", "dummy[pass=1,fail=0]"),
        #Isol = cms.vstring("MC true",  "dummy[pass=1,fail=0]"),
        #Mu9  = cms.vstring("MC true",  "dummy[pass=1,fail=0]"),
        #combRelIsoPF04dBeta = cms.vstring("ioslation",  "dummy[pass=1,fail=0]"),
        #Tight2012  = cms.vstring("TightCut",  "dummy[pass=1,fail=0]"),
        Mu15_eta2p1  = cms.vstring("Mu15_eta2p1",  "dummy[pass=1,fail=0]"),
    ),

    # defines all the PDFs that will be available for the efficiency calculations; uses RooFit's "factory" syntax;
    # each pdf needs to define "signal", "backgroundPass", "backgroundFail" pdfs, "efficiency[0.9,0,1]" and "signalFractionInPassing[0.9]" are used for initial values  
    PDFs = cms.PSet(
        voigtPlusExpo = cms.vstring(
            "Voigtian::signal(mass, mean[90,80,100], width[2.495], sigma[3,1,20])",
            "Exponential::backgroundPass(mass, lp[0,-5,5])",
            "Exponential::backgroundFail(mass, lf[0,-5,5])",
            "efficiency[0.9,0,1]",
            "signalFractionInPassing[0.9]"
        )
    ),
    # defines a set of efficiency calculations, what PDF to use for fitting and how to bin the data;
    # there will be a separate output directory for each calculation that includes a simultaneous fit, side band subtraction and counting. 
    Efficiencies = cms.PSet(), # will be filled later
)

CONSTRAINTS = cms.PSet(
    charge = charge_,
    abseta = cms.vdouble(0, 2.1),
    isPFMu = cms.vdouble(0, 1),
    isGlbMu = cms.vdouble(0, 1),
    glbChi2 = cms.vdouble(0, 10),
    glbValidMuHits = cms.vdouble(1, 100),
    numberOfMatchedStations = cms.vdouble( 2, 100),
    dB = cms.vdouble(-0.02, 0.02),
    tkDz = cms.vdouble( -5, 5),
    tkTrackerLay = cms.vdouble(6, 100),
    tkValidPixelHits = cms.vdouble(1, 100),
    combRelIsoPF04dBeta = cms.vdouble( 0, 0.12),
)

PT_BINS  = cms.PSet(CONSTRAINTS,
    eta = cms.vdouble(-2.1, 2.1),
    pt = cms.vdouble(0,10,15,17,19,21,23,25,35,60,100, 200),
    )
ETA_BINS = cms.PSet(CONSTRAINTS,
    pt = cms.vdouble(25, 1000),
    eta = cms.vdouble(
  -2.1,-1.8,-1.5,-1.2,-0.9,-0.6,-0.3,0
  ,0.3,0.6,0.9,1.2,1.5,1.8,2.1)
    )


PREFIX="/terranova_1/W_TnP/Muon/V5/"
if "RD" in scenario:
    process.TnP_Trigger.InputFileNames = cms.vstring(
	PREFIX+'tnpZ_Data_Run2011A.root',
	)
    #process.TnP_Trigger.binsForMassPlots = cms.uint32(20)

elif "MC" in scenario:
    process.TnP_Trigger.InputFileNames = cms.vstring(
	PREFIX+'tnpZ_MC_DYToMuMu.root',
	)
    #process.TnP_Trigger.InputFileNames = cms.vstring('tnpZ_DYToMuMu.root')
    #process.TnP_Trigger.binsForMassPlots = cms.uint32(20)
else:
  print "Usage: cmsRun %s RD(MC)eta(pt,vtx)plus(minus)" %sys.argv[1]
  sys.exit(0)

#if "all_space"  in scenario:
#  ALLBINS = [("pt",PT_BINS),("eta", ETA_BINS)]
if "pt"  in scenario:
  ALLBINS = [("pt",PT_BINS)]
elif "eta"  in scenario:
  ALLBINS = [("eta", ETA_BINS)]
else:
  print "Usage: cmsRun %s RD(MC)eta(pt,vtx)plus(minus)" %sys.argv[1]
  sys.exit(0)
#ALLBINS=[("all",ONE_BIN),("pt",PT_BINS),("eta",ETA_BINS)]
#for (T,M) in [ ("Mu15_eta2p1","Track"), ("Mu15_eta2p1","Glb"), ("Mu15_eta2p1", "VBTF"), ("Mu15_eta2p1", "VBTF_Isol")]:
#for (T,M) in [ ("Mu15_eta2p1", "Tight2012")]:
#        for BN,BV in ALLBINS:
#            BINNEDVARS = BV.clone()
#            if M == "VBTF_Isol":
#                setattr(BINNEDVARS, "VBTF", cms.vstring("pass"))
#                setattr(BINNEDVARS, "Isol", cms.vstring("pass"))
#            elif M != "Track": 
#                setattr(BINNEDVARS, M, cms.vstring("pass"))
#        #the name of the parameter set becomes the name of the directory
#            setattr(process.TnP_Trigger.Efficiencies, M+"_To_"+T+"_"+BN, cms.PSet(
#            #specifies the efficiency of which category and state to measure 
#                EfficiencyCategoryAndState = cms.vstring(T,"pass"),
#            #specifies what unbinned variables to include in the dataset
#	    #, the mass is needed for the fit
#                UnbinnedVariables = cms.vstring("mass"),
#            #specifies the binning of parameters
#                BinnedVariables = BINNEDVARS,
#            #first string is the default followed by binRegExp - PDFname pairs
#                BinToPDFmap = cms.vstring("gaussPlusExpo")
#            ))
for  X,B in ALLBINS:
    #setattr(process.TnP_Trigger.Efficiencies, "Track_To_Tight_Mu15_eta2p1_"+X, cms.PSet(
    #setattr(process.TnP_Trigger.Efficiencies, "Track_To_VBTF_Mu15_eta2p1_"+X, cms.PSet(
    #    EfficiencyCategoryAndState = cms.vstring("Tight2012","pass","Mu15_eta2p1","pass"),
        #EfficiencyCategoryAndState = cms.vstring("VBTF","pass","Mu15_eta2p1","pass"),
    #    UnbinnedVariables = cms.vstring("mass"),
    #    BinnedVariables = B,
    #    BinToPDFmap = cms.vstring("gaussPlusExpo")
    #))
    setattr(process.TnP_Trigger.Efficiencies, "Tnp_WptCut_to_Mu15_eta2p1_"+X, cms.PSet(
        EfficiencyCategoryAndState = cms.vstring("Mu15_eta2p1","pass"),
        #EfficiencyCategoryAndState = cms.vstring("Tight2012","pass","combRelIsoPF04dBeta","pass","Mu15_eta2p1","pass"),
        UnbinnedVariables = cms.vstring("mass"),
        BinnedVariables = B,
        BinToPDFmap = cms.vstring()
        #BinToPDFmap = cms.vstring("voigtPlusExpo")
    ))

process.p = cms.Path(
    process.TnP_Trigger
)
