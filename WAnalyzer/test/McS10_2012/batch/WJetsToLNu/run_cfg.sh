#! /bin/tcsh 

#VER=3_6_3
#RUN=$1
#set CfgFile=$1

set CfgFile=wEleNeuFilter_MC_cfg.py

#set CASTORDIR=$2
#echo $CfgFile

#set WorkDir=/afs/cern.ch/work/s/salee/private/W/CMSSW_5_2_5/src/KNUPhy/WAnalyzer/test/batch/MuNeu/Run2012A_SingleMu_PromptV1
#set WorkDir=/u/user/knuhamid/PhD_work/Wp-x-section/CMSSW_5_2_5/src/KNUPhy/WAnalyzer/test/local/MuNeu/Hammid_Muon_ntuple/DYToMuMu
#set WorkDir=/d2/scratch/knuhamid/Wpt-x-section/CMSSW_5_2_5/src/KNUPhy/WAnalyzer/test/local/EleNeu/Hammid_Electron_allConversions_V4/WplusToEleNu

set WorkDir=/d1/scratch/jungmin/cms/CMSSW_5_3_7_patch4/src/KNUPhy/WAnalyzer/test/McS10_2012/batch/WJetsToLNu
#set WorkDir=/d1/scratch/jungmin/cms/CMSSW_5_2_6/src/KNUPhy/WAnalyzer/test/batch/EleNeu/DYToEE_highPU

#/d2/scratch/knuhamid/Wpt-x-section/CMSSW_5_2_5/src/KNUPhy/WAnalyzer/test/local/MuNeu/Hammid_Muon_ntuple/DYToMuMu

#if [ $# -ne 1 ]
#then
#    echo 'Error!! Please input one argument [mass] (ex. run_cfg.sh 100)'
#    exit 0
#fi
#
cd $WorkDir 

#pwd >haha.log
#source /afs/cern.ch/user/s/salee/WorkSpace/private/W/CMSSW_5_2_5/src/KNUPhy/Miscel/Env/setenv4CMSSW525.tcsh

#source /d2/scratch/knuhamid/Wpt-x-section/CMSSW_5_2_5/src/KNUPhy/Miscel/Env/setenv4CMSSW525.tcsh

source /cvmfs/cms.cern.ch/cmsset_default.csh

setenv SCRAM_ARCH slc5_amd64_gcc462

# source /u/user/knuhamid/PhD_work/Wp-x-section/CMSSW_5_2_5/src/KNUPhy/Miscel/Env/setenv4CMSSW525.tcsh
# source /mnt/user/knuhamid/PhD_work/Wp-x-section/CMSSW_5_2_5/src/KNUPhy/Miscel/Env/setenv4CMSSW525.tcsh

cmsenv
#eval `/opt/exp_soft/cms/common/scramv1 runtime -csh`
cmsRun $CfgFile
#eval `scramv1 runtime -sh`
cd -

#TODO
#set DIR=/castor/cern.ch/user/s/salee/NtConversion/$CASTORDIR/
#set DIR=/castor/cern.ch/user/s/salee/NtConversion/MultiJet_05Aug2011_v1_23Sep/
#set DIR=/castor/cern.ch/user/s/salee/NtConversion/DoubleElectron_05Aug2011_v1_23Sep/
#DIR=/castor/cern.ch/user/h/hkseo/RPC/rpcHit
#
#cp -r $WorkDir/susyKIT .
#cd susyKIT
#source setsusyKIT.sh
#make clean;make
#cd test
#make clean;make
#cd ../convert/forTL
#../../bin/myConvertRutgers4TL $CfgFile
#cp $WorkDir/UserCode/RPCPlot/bsub/run$RUN/rpcplot_cfg.py .
#cmsRun rpcplot_cfg.py
#rfcp RPCPlot.root $DIR/RPCPlot_$RUN.root
#rfcp *.root $DIR
