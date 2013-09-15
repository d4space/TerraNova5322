import FWCore.ParameterSet.Config as cms

process = cms.Process("TagProbe")
process.source = cms.Source("EmptySource")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.destinations = ['cout', 'cerr']
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

##                      _              _       
##   ___ ___  _ __  ___| |_ __ _ _ __ | |_ ___ 
##  / __/ _ \| '_ \/ __| __/ _` | '_ \| __/ __|
## | (_| (_) | | | \__ \ || (_| | | | | |_\__ \
##  \___\___/|_| |_|___/\__\__,_|_| |_|\__|___/
##                                              
################################################


#isMC = True
isMC = False

InputFileName = "/d2/scratch/Storage_Area/Wpt-efficiency/Electron/TnP_root_files_full/testNewWrite_RD.root"

#InputFileName = "/terranova_1/W_TnP/Ele_skim_root/RD/ReReco/testNewWrite_RD_ReReco.root"
#InputFileName = "/terranova_1/W_TnP/Electron/mc_all_gsf.root"
#InputFileName = "testNewWrite.root"
OutputFilePrefix = "efficiency-data-"
HLTDef = "probe_passingHLT"
PDFName = "pdfSignalPlusBackground"
if isMC:

  InputFileName = "/d2/scratch/Storage_Area/Wpt-efficiency/Electron/TnP_root_files_full/testNewWrite_MC.root"

  #InputFileName = "/terranova_0/W/CMSSW_5_2_6/src/KNUPhy/TnP_Electron/Producer/Local/MC/testNewWrite.root"
  # this is not working, you need to set PDFName = "" for each line
##  PDFName =""
  PDFName = "pdfSignalPlusBackground"
  OutputFilePrefix = "efficiency-mc-"
print "PDFName is %s" %PDFName
################################################

###specifies the binning of parameters
#### for super clusters

###probe_sc_et_all = cms.vdouble( 25,100 )
#probe_sc_et_all = cms.vdouble( 0,10,15,17,19,22,25,27,30,35,60,100,200 )
#probe_sc_et_one = cms.vdouble( 25, 1000 )
#probe_sc_eta_all= cms.vdouble( -2.5,-1.5,-0.5,0.0,0.5,1.5,2.5 )
#probe_sc_eta_one= cms.vdouble( -2.5,2.5 )


probe_sc_et_all = cms.vdouble( 25,30,35,40,45,50,55,60,65,80)
probe_sc_et_one = cms.vdouble( 25, 35 )
probe_sc_eta_all= cms.vdouble( -2.5,-1.5,-0.5,0.0,0.5,1.5,2.5 )
#probe_sc_eta_all= cms.vdouble( -2.5,-2.0,-1.5,-1.0,-0.5,0.0,0.5,1.0,1.5,2.0,2.5 )
#probe_sc_eta_all= cms.vdouble( -2.5,-1.5,0.0,1.5,2.5 )
probe_sc_eta_one= cms.vdouble( -2.5,2.5 )



charge_plus     = cms.vdouble(0.5, 1   )
charge_minus    = cms.vdouble(-1,  -0.5)


EfficiencyBinsSC_et_tagP = cms.PSet(
    probe_sc_et  = probe_sc_et_all,
    probe_sc_eta = probe_sc_eta_one,
    tag_charge   = charge_plus
)
EfficiencyBinsSC_et_tagM = EfficiencyBinsSC_et_tagP.clone()
EfficiencyBinsSC_et_tagM.tag_charge = charge_minus

EfficiencyBinsSC_eta_tagP = EfficiencyBinsSC_et_tagP.clone()
EfficiencyBinsSC_eta_tagP.probe_sc_et = probe_sc_et_one
EfficiencyBinsSC_eta_tagP.probe_sc_eta = probe_sc_eta_all

EfficiencyBinsSC_eta_tagM = EfficiencyBinsSC_eta_tagP.clone()
EfficiencyBinsSC_eta_tagM.tag_charge = charge_minus

EfficiencyBinsSC_et_probeP = cms.PSet(
    probe_sc_et  = probe_sc_et_all,
    probe_sc_eta = probe_sc_eta_one,
    probe_charge = charge_plus
)
EfficiencyBinsSC_et_probeM = EfficiencyBinsSC_et_probeP.clone()
EfficiencyBinsSC_et_probeM.probe_charge = charge_minus

EfficiencyBinsSC_eta_probeP = cms.PSet(
    probe_sc_et = probe_sc_et_one,
    probe_sc_eta= probe_sc_eta_all,
    probe_charge= charge_plus
)
EfficiencyBinsSC_eta_probeM = EfficiencyBinsSC_eta_probeP.clone()
EfficiencyBinsSC_eta_probeM.probe_charge = charge_minus

#### For data: except for HLT step
#EfficiencyBinningSpecification = cms.PSet(
#    #specifies what unbinned variables to include in the dataset, the mass is needed for the fit
#    UnbinnedVariables = cms.vstring("mass"),
#    #specifies the binning of parameters
#    BinnedVariables = cms.PSet(EfficiencyBins),
#    #first string is the default followed by binRegExp - PDFname pairs
#    BinToPDFmap = cms.vstring(PDFName)
#)


#### For super clusters
print "EfficiencyBinningSpecificationSC PDFName is %s" %PDFName
EfficiencyBinningSpecificationSC_et_tagP = cms.PSet(
    UnbinnedVariables = cms.vstring("mass"),
    BinnedVariables = cms.PSet(EfficiencyBinsSC_et_tagP),
    BinToPDFmap = cms.vstring(PDFName)
)
EfficiencyBinningSpecificationSC_et_tagM = EfficiencyBinningSpecificationSC_et_tagP.clone()
EfficiencyBinningSpecificationSC_et_tagM.BinnedVariables = cms.PSet(EfficiencyBinsSC_et_tagM)

EfficiencyBinningSpecificationSC_eta_tagM = EfficiencyBinningSpecificationSC_et_tagM.clone()
EfficiencyBinningSpecificationSC_eta_tagM.BinnedVariables = cms.PSet(EfficiencyBinsSC_eta_tagM)
EfficiencyBinningSpecificationSC_eta_tagP = EfficiencyBinningSpecificationSC_et_tagM.clone()
EfficiencyBinningSpecificationSC_eta_tagP.BinnedVariables = cms.PSet(EfficiencyBinsSC_eta_tagP)

EfficiencyBinningSpecificationSC_et_probeM = EfficiencyBinningSpecificationSC_et_tagM.clone()
EfficiencyBinningSpecificationSC_et_probeM.BinnedVariables = cms.PSet(EfficiencyBinsSC_et_probeM)
EfficiencyBinningSpecificationSC_et_probeP = EfficiencyBinningSpecificationSC_et_tagM.clone()
EfficiencyBinningSpecificationSC_et_probeP.BinnedVariables = cms.PSet(EfficiencyBinsSC_et_probeP)

EfficiencyBinningSpecificationSC_eta_probeM = EfficiencyBinningSpecificationSC_et_tagM.clone()
EfficiencyBinningSpecificationSC_eta_probeM.BinnedVariables = cms.PSet(EfficiencyBinsSC_eta_probeM)
EfficiencyBinningSpecificationSC_eta_probeP = EfficiencyBinningSpecificationSC_et_tagM.clone()
EfficiencyBinningSpecificationSC_eta_probeP.BinnedVariables = cms.PSet(EfficiencyBinsSC_eta_probeP)


#if isMC:
#    EfficiencyBinningSpecificationSC_et_tagM.BinToPDFmap = cms.vstring()
#    EfficiencyBinningSpecificationSC_et_tagP.BinToPDFmap = cms.vstring()
#    EfficiencyBinningSpecificationSC_eta_tagM.BinToPDFmap = cms.vstring()
#    EfficiencyBinningSpecificationSC_eta_tagP.BinToPDFmap = cms.vstring()
#    EfficiencyBinningSpecificationSC_et_probeM.BinToPDFmap = cms.vstring()
#    EfficiencyBinningSpecificationSC_et_probeP.BinToPDFmap = cms.vstring()
#    EfficiencyBinningSpecificationSC_eta_probeM.BinToPDFmap = cms.vstring()
#    EfficiencyBinningSpecificationSC_eta_probeP.BinToPDFmap = cms.vstring()


#### For MC truth: do truth matching
EfficiencyBinningSpecificationSCMC_et_tagM = cms.PSet(
    UnbinnedVariables = cms.vstring("mass"),
    BinnedVariables = cms.PSet(EfficiencyBinsSC_et_tagM,mcTrue = cms.vstring("true")),
    BinToPDFmap = cms.vstring()  
)
EfficiencyBinningSpecificationSCMC_et_tagP = EfficiencyBinningSpecificationSCMC_et_tagM.clone()
EfficiencyBinningSpecificationSCMC_et_tagP.BinnedVariables = cms.PSet(EfficiencyBinsSC_et_tagP,mcTrue = cms.vstring("true"))
EfficiencyBinningSpecificationSCMC_eta_tagM = EfficiencyBinningSpecificationSCMC_et_tagM.clone()
EfficiencyBinningSpecificationSCMC_eta_tagM.BinnedVariables = cms.PSet(EfficiencyBinsSC_eta_tagM,mcTrue = cms.vstring("true"))
EfficiencyBinningSpecificationSCMC_eta_tagP = EfficiencyBinningSpecificationSCMC_et_tagM.clone()
EfficiencyBinningSpecificationSCMC_eta_tagP.BinnedVariables = cms.PSet(EfficiencyBinsSC_eta_tagP,mcTrue = cms.vstring("true"))

EfficiencyBinningSpecificationSCMC_et_probeM = EfficiencyBinningSpecificationSCMC_et_tagM.clone()
EfficiencyBinningSpecificationSCMC_et_probeM.BinnedVariables = cms.PSet(EfficiencyBinsSC_et_probeM,mcTrue = cms.vstring("true"))
EfficiencyBinningSpecificationSCMC_et_probeP = EfficiencyBinningSpecificationSCMC_et_tagM.clone()
EfficiencyBinningSpecificationSCMC_et_probeP.BinnedVariables = cms.PSet(EfficiencyBinsSC_et_probeP,mcTrue = cms.vstring("true"))
EfficiencyBinningSpecificationSCMC_eta_probeM = EfficiencyBinningSpecificationSCMC_et_tagM.clone()
EfficiencyBinningSpecificationSCMC_eta_probeM.BinnedVariables = cms.PSet(EfficiencyBinsSC_eta_probeM,mcTrue = cms.vstring("true"))
EfficiencyBinningSpecificationSCMC_eta_probeP = EfficiencyBinningSpecificationSCMC_et_tagM.clone()
EfficiencyBinningSpecificationSCMC_eta_probeP.BinnedVariables = cms.PSet(EfficiencyBinsSC_eta_probeP,mcTrue = cms.vstring("true"))

#### For HLT step: just do cut & count
EfficiencyBinningSpecificationHLT_SC_et_tagP = EfficiencyBinningSpecificationSC_et_tagP.clone()
EfficiencyBinningSpecificationHLT_SC_et_tagP.BinToPDFmap = cms.vstring()
EfficiencyBinningSpecificationHLT_SC_et_tagM = EfficiencyBinningSpecificationSC_et_tagM.clone()
EfficiencyBinningSpecificationHLT_SC_et_tagM.BinToPDFmap = cms.vstring()
EfficiencyBinningSpecificationHLT_SC_et_probeP = EfficiencyBinningSpecificationSC_et_probeP.clone()
EfficiencyBinningSpecificationHLT_SC_et_probeP.BinToPDFmap = cms.vstring()
EfficiencyBinningSpecificationHLT_SC_et_probeM = EfficiencyBinningSpecificationSC_et_probeM.clone()
EfficiencyBinningSpecificationHLT_SC_et_probeM.BinToPDFmap = cms.vstring()

EfficiencyBinningSpecificationHLT_SC_eta_tagP = EfficiencyBinningSpecificationSC_eta_tagP.clone()
EfficiencyBinningSpecificationHLT_SC_eta_tagP.BinToPDFmap = cms.vstring()
EfficiencyBinningSpecificationHLT_SC_eta_tagM = EfficiencyBinningSpecificationSC_eta_tagM.clone()
EfficiencyBinningSpecificationHLT_SC_eta_tagM.BinToPDFmap = cms.vstring()
EfficiencyBinningSpecificationHLT_SC_eta_probeP = EfficiencyBinningSpecificationSC_eta_probeP.clone()
EfficiencyBinningSpecificationHLT_SC_eta_probeP.BinToPDFmap = cms.vstring()
EfficiencyBinningSpecificationHLT_SC_eta_probeM = EfficiencyBinningSpecificationSC_eta_probeM.clone()
EfficiencyBinningSpecificationHLT_SC_eta_probeM.BinToPDFmap = cms.vstring()

##########################################################################################
############################################################################################
#if isMC:
#    mcTruthModules = cms.PSet(
#        MCtruth_WP80 = cms.PSet(
#        EfficiencyBinningSpecificationMC,   
#        EfficiencyCategoryAndState = cms.vstring("probe_isWptCut","pass"),
#        ),
#        )
#else:
#    mcTruthModules = cms.PSet()
##########################################################################################
##########################################################################################
        

############################################################################################
############################################################################################
####### PfElectron->Id / selection efficiency 
############################################################################################
############################################################################################

process.PfElectronToId_P = cms.EDAnalyzer("TagProbeFitTreeAnalyzer",
    # IO parameters:
    InputFileNames = cms.vstring(InputFileName),
    InputDirectoryName = cms.string("PfElectronToId"),
    InputTreeName = cms.string("fitter_tree"),
    OutputFileName = cms.string(OutputFilePrefix+"PfElectronToId_P.root"),
    #numbrer of CPUs to use for fitting
    NumCPU = cms.uint32(1),
    # specifies wether to save the RooWorkspace containing the data for each bin and
    # the pdf object with the initial and final state snapshots
    SaveWorkspace = cms.bool(True),
    floatShapeParameters = cms.bool(True),
    #fixVars = cms.vstring("mean"),
                                                 
    # defines all the real variables of the probes available in the input tree and intended for use in the efficiencies
    Variables = cms.PSet(
        mass = cms.vstring("Tag-Probe Mass", "60.0", "120.0", "GeV/c^{2}"),
        #probe_gsfEle_et = cms.vstring("Probe E_{T}", "0", "1000", "GeV/c"),
        #probe_pfEle_et = cms.vstring("Probe E_{T}", "0", "1000", "GeV/c"),
        #probe_pfEle_eta = cms.vstring("Probe #eta", "-2.5", "2.5", ""),                
        probe_sc_et = cms.vstring("Probe E_{T}", "0", "1000", "GeV/c"),
        probe_sc_eta = cms.vstring("Probe #eta", "-2.5", "2.5", ""),
	tag_charge = cms.vstring("Tag Charge","-1","1",""),
	probe_charge = cms.vstring("probe Charge","-1","1",""),
    ),

    # defines all the discrete variables of the probes available in the input tree and intended for use in the efficiency calculations
    Categories = cms.PSet(
      #TODO weight is not working
        #weight = cms.vstring("weight", "0.0", "10.0", ""),
        mcTrue = cms.vstring("MC true", "dummy[true=1,false=0]"),
        #probe_passConvRej = cms.vstring("probe_passConvRej", "dummy[pass=1,fail=0]"), 
##         probe_isWP95 = cms.vstring("probe_isWP95", "dummy[pass=1,fail=0]"),
        probe_isWptCut = cms.vstring("probe_isWptCut", "dummy[pass=1,fail=0]"),
    ),
    # defines all the PDFs that will be available for the efficiency calculations; uses RooFit's "factory" syntax;
    # each pdf needs to define "signal", "backgroundPass", "backgroundFail" pdfs, "efficiency[0.9,0,1]" and "signalFractionInPassing[0.9]" are used for initial values  
    PDFs = cms.PSet(
        pdfSignalPlusBackground = cms.vstring(

    ###### Crytal-Ball Exp Gauss
#     "CBExGaussShape::signalRes(mass,mean[2.0946e-01],sigma[8.5695e-04],alpha[3.8296e-04],n[6.7489e+00],sigma_2[2.5849e+00],frac[6.5704e-01])",## the signal function goes here
#     "CBExGaussShape::signalResPass(mass, meanP[0.], sigmaP[8.5695e-04, 0., 3.],alphaP[3.8296e-04], nP[6.7489e+00], sigmaP_2[2.5849e+00], fracP[6.5704e-01])",  ### signal resolution for "pass" sample
#     "CBExGaussShape::signalResFail(mass, meanF[2.0946e-01, -5., 5.], sigmaF[8.5695e-04, 0., 5.],alphaF[3.8296e-04], nF[6.7489e+00], sigmaF_2[2.5849e+00], fracF[6.5704e-01])",  ### signal resolution for "fail" sample     

    ###### MC
    "ZGeneratorLineShape::signalPhy(mass)", ### NLO line shape

    ##### erfc*Exp
 #   "RooCMSShape::backgroundPass(mass, alphaPass[60.,50.,70.], betaPass[0.001, 0.,0.1], betaPass, peakPass[90.0])",
    "RooCMSShape::backgroundFail(mass, alphaFail[60.,50.,70.], betaFail[0.001, 0.,0.1], betaFail, peakFail[90.0])",

 #### KSung
 #    "RooCMSShape::backgroundFail(mass, alphaFail[50.,5.,200.], betaFail[0.01, 0.,10], betaFail, peakFail[90.0])",

    ##### Convolution Function 
#    "FCONV::signalPass(mass, signalPhy, signalResPass)",
#    "FCONV::signalFail(mass, signalPhy, signalResFail)",     

    "FCONV::signalPass(mass, signalPhy, signal)",
    "FCONV::signalFail(mass, signalPhy, signal)",


    ##### Gauss 
    "Gaussian::signal(mass, mean[91.2, 89.0, 93.0], sigma[2.3, 0.5, 10.0])",

    ##### Exp 
    "RooExponential::backgroundPass(mass, cPass[-0.02,-5,0])",
#    "RooExponential::backgroundFail(mass, cFail[-0.02,-5,0])",



    "efficiency[0.9,0,1]",
    "signalFractionInPassing[1.0]"     
    #"efficiency[0.9,0,1]",
    #"signalFractionInPassing[0.9]"
        ),
    ),

    # defines a set of efficiency calculations, what PDF to use for fitting and how to bin the data;
    # there will be a separate output directory for each calculation that includes a simultaneous fit, side band subtraction and counting. 
    Efficiencies = cms.PSet(
    #mcTruthModules,
##     #the name of the parameter set becomes the name of the directory
##     WP95 = cms.PSet(
##     EfficiencyBinningSpecification,
##     #specifies the efficiency of which category and state to measure 
##     EfficiencyCategoryAndState = cms.vstring("probe_isWP95","pass"),
##     ),
      WptCut = cms.PSet(
      EfficiencyBinningSpecificationSC_et_probeP,
      EfficiencyCategoryAndState = cms.vstring("probe_isWptCut","pass"),
      ),
    )
)
#if isMC:
#    process.PfElectronToId.WeightVariable = cms.string("PUweight")


############################################################################################
############################################################################################
####### SC->PfElectron efficiency 
############################################################################################
############################################################################################
if isMC:
    SCmcTruthModules_et_tagM = cms.PSet(
        MCtruth_efficiency = cms.PSet(
        EfficiencyBinningSpecificationSCMC_et_tagM,
        EfficiencyCategoryAndState = cms.vstring( "probe_passingPf", "pass" ),
        ),
    )
    SCmcTruthModules_et_tagP = cms.PSet(
        MCtruth_efficiency = cms.PSet(
        EfficiencyBinningSpecificationSCMC_et_tagP,
        EfficiencyCategoryAndState = cms.vstring( "probe_passingPf", "pass" ),
        ),
    )
else:
    SCmcTruthModules_et_tagM = cms.PSet()
    SCmcTruthModules_et_tagP = cms.PSet()


process.SCToPfElectron_et_M = process.PfElectronToId_P.clone()
process.SCToPfElectron_et_M.InputDirectoryName = cms.string("SuperClusterToPFElectron")
process.SCToPfElectron_et_M.OutputFileName = cms.string(OutputFilePrefix+"SCToPfElectron_et_M.root")
process.SCToPfElectron_et_M.Variables = cms.PSet(
        mass = cms.vstring("Tag-Probe Mass", "60.0", "120.0", "GeV/c^{2}"),
        probe_sc_et = cms.vstring("Probe E_{T}", "0", "1000", "GeV/c"),
        probe_sc_eta = cms.vstring("Probe #eta", "-2.5", "2.5", ""),
	tag_charge = cms.vstring("Tag Charge","-1","1",""),
	)
process.SCToPfElectron_et_M.Categories = cms.PSet(
    mcTrue = cms.vstring("MC true", "dummy[true=1,false=0]"),           
    probe_passingPf = cms.vstring("probe_passingPf", "dummy[pass=1,fail=0]"),                        
    probe_isWptCut = cms.vstring("probe_isWptCut", "dummy[pass=1,fail=0]"),                        
    )
print "SCToPfElectron PDFName is %s" %PDFName
process.SCToPfElectron_et_M.Efficiencies = cms.PSet(
    #SCmcTruthModules_et_M,
    SCtoPF_efficiency = cms.PSet(
    EfficiencyBinningSpecificationSC_et_tagP,
    EfficiencyCategoryAndState = cms.vstring( "probe_passingPf", "pass" ),
    ),
    SCtoWptCut_efficiency = cms.PSet(
    EfficiencyBinningSpecificationSC_et_tagP,
    EfficiencyCategoryAndState = cms.vstring( "probe_isWptCut", "pass" ),
    ),
)
process.SCToPfElectron_et_P =process.SCToPfElectron_et_M.clone()
process.SCToPfElectron_et_P.Efficiencies = cms.PSet(
    #SCmcTruthModules,
    SCtoPF_efficiency = cms.PSet(
    EfficiencyBinningSpecificationSC_et_tagM,
    EfficiencyCategoryAndState = cms.vstring( "probe_passingPf", "pass" ),
    ),
    SCtoWptCut_efficiency = cms.PSet(
    EfficiencyBinningSpecificationSC_et_tagM,
    EfficiencyCategoryAndState = cms.vstring( "probe_isWptCut", "pass" ),
    ),
)
process.SCToPfElectron_et_P.OutputFileName = cms.string(OutputFilePrefix+"SCToPfElectron_et_P.root")

process.SCToPfElectron_eta_M =process.SCToPfElectron_et_M.clone()
process.SCToPfElectron_eta_M.Efficiencies = cms.PSet(
    #SCmcTruthModules,
    SCtoPF_efficiency = cms.PSet(
    EfficiencyBinningSpecificationSC_eta_tagP,
    EfficiencyCategoryAndState = cms.vstring( "probe_passingPf", "pass" ),
    ),
    SCtoWptCut_efficiency = cms.PSet(
    EfficiencyBinningSpecificationSC_eta_tagP,
    EfficiencyCategoryAndState = cms.vstring( "probe_isWptCut", "pass" ),
    ),
)
process.SCToPfElectron_eta_M.OutputFileName = cms.string(OutputFilePrefix+"SCToPfElectron_eta_M.root")

process.SCToPfElectron_eta_P =process.SCToPfElectron_et_M.clone()
process.SCToPfElectron_eta_P.Efficiencies = cms.PSet(
    #SCmcTruthModules,
    SCtoPF_efficiency = cms.PSet(
    EfficiencyBinningSpecificationSC_eta_tagM,
    EfficiencyCategoryAndState = cms.vstring( "probe_passingPf", "pass" ),
    ),
    SCtoWptCut_efficiency = cms.PSet(
    EfficiencyBinningSpecificationSC_eta_tagM,
    EfficiencyCategoryAndState = cms.vstring( "probe_isWptCut", "pass" ),
    ),
)
process.SCToPfElectron_eta_P.OutputFileName = cms.string(OutputFilePrefix+"SCToPfElectron_eta_P.root")
############################################################################################
############################################################################################
####### HLT efficiency 
############################################################################################
############################################################################################


if isMC:
    HLTmcTruthModules_SC_et_probeP = cms.PSet(
        MCtruth_efficiency = cms.PSet(
        EfficiencyBinningSpecificationSCMC_et_probeP,
        EfficiencyCategoryAndState = cms.vstring( HLTDef, "pass" ),
        ),    
    )
    HLTmcTruthModules_SC_et_probeM = cms.PSet(
        MCtruth_efficiency = cms.PSet(
        EfficiencyBinningSpecificationSCMC_et_probeM,
        EfficiencyCategoryAndState = cms.vstring( HLTDef, "pass" ),
        ),    
    )
    HLTmcTruthModules_SC_eta_probeP = cms.PSet(
        MCtruth_efficiency = cms.PSet(
        EfficiencyBinningSpecificationSCMC_eta_probeP,
        EfficiencyCategoryAndState = cms.vstring( HLTDef, "pass" ),
        ),    
    )
    HLTmcTruthModules_SC_eta_probeM = cms.PSet(
        MCtruth_efficiency = cms.PSet(
        EfficiencyBinningSpecificationSCMC_eta_probeM,
        EfficiencyCategoryAndState = cms.vstring( HLTDef, "pass" ),
        ),    
    )
else:
    HLTmcTruthModules_SC_et_probeP = cms.PSet()
    HLTmcTruthModules_SC_et_probeM = cms.PSet()
    HLTmcTruthModules_SC_eta_probeP = cms.PSet()
    HLTmcTruthModules_SC_eta_probeM = cms.PSet()


EfficienciesPsetHLT_SC_et_probeP = cms.PSet(
    HLTmcTruthModules_SC_et_probeP,
    efficiency = cms.PSet(
    EfficiencyBinningSpecificationHLT_SC_et_probeP,
    EfficiencyCategoryAndState = cms.vstring( HLTDef, "pass" ),
    ),
)
EfficienciesPsetHLT_SC_et_probeM = cms.PSet(
    HLTmcTruthModules_SC_et_probeM,
    efficiency = cms.PSet(
    EfficiencyBinningSpecificationHLT_SC_et_probeM,
    EfficiencyCategoryAndState = cms.vstring( HLTDef, "pass" ),
    ),
)
EfficienciesPsetHLT_SC_eta_probeP = cms.PSet(
    HLTmcTruthModules_SC_eta_probeP,
    efficiency = cms.PSet(
    EfficiencyBinningSpecificationHLT_SC_eta_probeP,
    EfficiencyCategoryAndState = cms.vstring( HLTDef, "pass" ),
    ),
)
EfficienciesPsetHLT_SC_eta_probeM = cms.PSet(
    HLTmcTruthModules_SC_eta_probeM,
    efficiency = cms.PSet(
    EfficiencyBinningSpecificationHLT_SC_eta_probeM,
    EfficiencyCategoryAndState = cms.vstring( HLTDef, "pass" ),
    ),
)

########
process.WptCutToHLT_et_P = process.PfElectronToId_P.clone()
process.WptCutToHLT_et_P.InputDirectoryName = cms.string("WptCutToHLT")
process.WptCutToHLT_et_P.OutputFileName = cms.string(OutputFilePrefix+"WptCutToHLT_et_P.root")
process.WptCutToHLT_et_P.Categories = cms.PSet(
    mcTrue = cms.vstring("MC true", "dummy[true=1,false=0]"),           
    probe_passingHLT = cms.vstring("probe_passingHLT", "dummy[pass=1,fail=0]"), 
    )
process.WptCutToHLT_et_P.Efficiencies = EfficienciesPsetHLT_SC_et_probeP
process.WptCutToHLT_et_M = process.WptCutToHLT_et_P.clone()
process.WptCutToHLT_et_M.Efficiencies = EfficienciesPsetHLT_SC_et_probeM
process.WptCutToHLT_et_M.OutputFileName = cms.string(OutputFilePrefix+"WptCutToHLT_et_M.root")
process.WptCutToHLT_eta_P = process.WptCutToHLT_et_P.clone()
process.WptCutToHLT_eta_P.Efficiencies = EfficienciesPsetHLT_SC_eta_probeP
process.WptCutToHLT_eta_P.OutputFileName = cms.string(OutputFilePrefix+"WptCutToHLT_eta_P.root")
process.WptCutToHLT_eta_M = process.WptCutToHLT_et_P.clone()
process.WptCutToHLT_eta_M.Efficiencies = EfficienciesPsetHLT_SC_eta_probeM
process.WptCutToHLT_eta_M.OutputFileName = cms.string(OutputFilePrefix+"WptCutToHLT_eta_M.root")
########  
process.fit = cms.Path(
#    process.PfElectronToId_P 
  
   process.SCToPfElectron_et_M +
   process.SCToPfElectron_et_P 
#   process.SCToPfElectron_eta_M +
#   process.SCToPfElectron_eta_P 
#    process.WptCutToHLT_et_P +
#    process.WptCutToHLT_et_M 
#    process.WptCutToHLT_eta_P +
#    process.WptCutToHLT_eta_M
    )
