#! /bin/tcsh
#if ($#argv != 1 )then
#	echo "Usage: run_sbsub.sh DirName"
#	exit 0
#endif
#if(! -e $1 )then
#	echo "$1 is not exist"
#	exit 1
#endif

#echo "bsub for $argv[1]"
#rfmkdir /castor/cern.ch/user/s/salee/NtConversion/$argv[1]
#rfchmod 775 /castor/cern.ch/user/s/salee/NtConversion/$argv[1]

foreach CfgFile (*.py)
	echo "submitting $CfgFile"
	bsub -q 8nh run_cfg.sh $CfgFile
end

#bsub -q 8nh run_cfg.sh 143665

exit 0
