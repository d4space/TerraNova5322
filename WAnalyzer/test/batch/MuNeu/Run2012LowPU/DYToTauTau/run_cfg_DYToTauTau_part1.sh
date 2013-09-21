#! /bin/tcsh 

#VER=3_6_3
#RUN=$1
set CfgFile=wMuNeuFilter_MC_2012_LowPU_part1_cfg.py
#set CASTORDIR=$2
#echo $CfgFile

set WorkDir=/d2/scratch/khakim/WAnalysis/CMSSW_5_2_6/src/KoSMP/WAnalyzer/test/batch/MuNeu/Run2012LowPU/DYToTauTau

#if [ $# -ne 1 ]
#then
#    echo 'Error!! Please input one argument [mass] (ex. run_cfg.sh 100)'
#    exit 0
#fi
#
cd $WorkDir
setenv SCRAM_ARCH slc5_amd64_gcc462
source /opt/exp_soft/cms/cmsset_default.csh
#source /afs/cern.ch/user/s/salee/WorkSpace/private/W/CMSSW_5_2_5/src/KoSMP/Miscel/Env/setenv4CMSSW525.tcsh
cmsenv
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
