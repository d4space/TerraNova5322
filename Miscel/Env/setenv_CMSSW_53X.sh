#!/bin/bash
if [ -f /etc/bashrc ]; then
      . /etc/bashrc
else
echo -e " No /etc/bashrc file! So confused..."
echo -e " Reflect, repent, and try with a better script next time"
echo -e " Exiting...."
exit
fi

# Definitions
RELEASE_VERSION=CMSSW_5_3_11 # for TnP
#RELEASE_VERSION=CMSSW_5_3_7_patch4
WORKING_AREA=W_V007_5311
# end definitions

export RELEASE_VERSION WORKING_AREA

echo -e  "******************************************"
echo -e " Setting up new working area: "
echo -e $WORKING_AREA
echo -e  "******************************************"

#setup new working area
mkdir $WORKING_AREA
cd $WORKING_AREA
export SCRAM_ARCH=slc5_amd64_gcc462
scramv1 p CMSSW $RELEASE_VERSION
cd $RELEASE_VERSION/src

echo -e  "\n**************************"
echo -e  " Checking out the code..."
echo -e  "**************************"
cvs -Q  co -r V06-05-06-12 DataFormats/PatCandidates 
##cvs -Q  co -r V06-05-06-06 DataFormats/PatCandidates       
#cvs -Q  co -r V08-09-54 PhysicsTools/PatAlgos           # 52
#cvs -Q  co -r V03-09-28 PhysicsTools/PatUtils
addpkg PhysicsTools/PatAlgos
addpkg PhysicsTools/PatUtils
cvs -Q  co -r V00-02-14 DataFormats/StdDictionaries 
cvs -Q  co -r V00-00-70 FWCore/GuiBrowsers
cvs -Q  co -r V03-03-12-02 RecoMET/METProducers

cvs -Q  co -r V00-03-16 CommonTools/ParticleFlow        
cvs -Q  co -r V00-00-12 CommonTools/RecoUtils           
#cvs -Q  co -r V04-06-09 JetMETCorrections/Type1MET   
cvs -Q  co -r V15-02-06 RecoParticleFlow/PFProducer   
cvs -Q  co -r V01-08-00 RecoBTag/SecondaryVertex        
cvs -Q  co -r V02-02-00 RecoVertex/AdaptiveVertexFinder 
#cvs -Q  co -r V00-00-30 -d EGamma/EGammaAnalysisTools UserCode/EGamma/EGammaAnalysisTools
cvs co -r  SE_PhotonIsoProducer_MovedIn   EgammaAnalysis/ElectronTools
cvs -Q  co -r V01-04-14 RecoTauTag/Configuration 
cvs -Q  co -r V00-04-00 CondFormats/EgammaObjects 

#cvs -Q  co -r V04-04-00 PhysicsTools/TagAndProbe
cvs -Q  co -r V04-06-00 PhysicsTools/TagAndProbe # TnP for 538
cvs -Q  co -r V00-03-21 RecoEgamma/ElectronIdentification
cvs -Q  co -r V08-03-15 PhysicsTools/Utilities
cvs co -r V09-00-01    RecoEgamma/EgammaTools
#addpkg HLTrigger/Configuration

echo -e "\n**************************************"
echo -e " Done for add pakages. Now will compile"
echo -e "****************************************"
sleep 2

#source /afs/cern.ch/cms/cmsset_default.sh
# above lxplus 

source /cvmfs/cms.cern.ch/cmsset_default.sh

# Not sure how to make script aware of cmsenv alias...
#cmsenv
scram runtime -sh
#scram b -j 9 # (lots of output here, but nothing to worry about)

#===========================================================================
# Before compile KoSMP, maybe change headerfiles EGamma to EgammaAnalysis 
#===========================================================================
#  ./KoSMP/CommonTools/interface/KyElectronSelector.h:
#  //#include "EGamma/EGammaAnalysisTools/interface/ElectronEffectiveArea.h"
#  #include "EgammaAnalysis/ElectronTools/interface/ElectronEffectiveArea.h"

#  ./KoSMP/WAnalyzer/interface/wEleNeuFilter.h:
#  //#include "EGamma/EGammaAnalysisTools/interface/ElectronEffectiveArea.h"
#  #include "EgammaAnalysis/ElectronTools/interface/ElectronEffectiveArea.h"


#  ./KoSMP/WAnalyzer/interface/wLeptNeuFilter.h:
#  //#include "EGamma/EGammaAnalysisTools/interface/ElectronEffectiveArea.h"
#  #include "EgammaAnalysis/ElectronTools/interface/ElectronEffectiveArea.h"

#============================================================================



#setenv CVS_RSH ssh
#setenv CVSROOT :ext:sangilpark@155.230.23.122:/cern/CVS

#cvs co KoSMP

#cd KoSMP

scram b -j 9


#echo -e "\n*************************************************"
#echo -e " Done compiling KoSMP"
#echo -e " Now making symbolic link to example config file"
#echo -e "*************************************************"
#echo -e " \n"
