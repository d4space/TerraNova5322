#! /bin/tcsh 

set CfgFile=wEleNeuFilter_MC_cfg.py
set WorkDir=/afs/cern.ch/work/s/shchang/public/MVAnoPUMET/CMSSW_5_3_9/src/KNUPhy/WAnalyzer/NoPUtest/ZG_Incl

cd $WorkDir
setenv SCRAM_ARCH slc5_amd64_gcc462
source /afs/cern.ch/cms/cmsset_default.csh
cmsenv
cmsRun $CfgFile
cd -

