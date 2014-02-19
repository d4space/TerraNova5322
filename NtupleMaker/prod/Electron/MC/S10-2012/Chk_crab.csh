#!/bin/csh -f

set nDIR=($argv[1])
set sDIR=($argv[2])
set DIR=`echo $nDIR"/"$sDIR`
#echo $DIR

#crab -status -c $crab_n > crab_status_$crab_n.tmp

#cat crab_status_$crab_n.tmp |sed -n '/Total Jobs/{p;}'
#cat crab_status_$crab_n.tmp |sed -n '/Jobs Done/{p;}'
#cat crab_status_$crab_n.tmp |sed -n '/Jobs Running/{p;}'

#cat `echo $DIR/crab_status.log` > crab_status_$nDIR.tmp
crab -status -c $DIR > crab_status_$sDIR.tmp
echo "#######################################################"

echo "         "$DIR

echo ""
cat crab_status_$sDIR.tmp |sed -n '/Total Jobs/{p;}'
cat crab_status_$sDIR.tmp |sed -n '/Jobs Done/{p;}'
cat crab_status_$sDIR.tmp |sed -n '/Jobs Running/{p;}'
cat crab_status_$sDIR.tmp |sed -n '/Jobs Scheduled/{p;}'
cat crab_status_$sDIR.tmp |sed -n '/Wrapper Exit Code/{p;}'
echo "#######################################################"

set AJs = `cat crab_status_$sDIR.tmp |sed -n '/Jobs Aborted/{p;}' | sed -e 's/[A-Za-z : >]*//g'`
echo $AJs
if ($AJs) then

echo ""
set aborted_num = `cat crab_status_$sDIR.tmp |sed -n '/Jobs Aborted/{n;n;p;}'| sed -e 's/[A-Za-z :]*//g'`
echo "Aborted Jobs Ids = " $aborted_num
echo ""
echo "crab -resubmit "$aborted_num" -c "$DIR
echo "execte resubmition "

crab -resubmit $aborted_num -c $DIR

else

echo ""
echo "No Aborted Jobs"

endif

echo ""
echo "END check "$sDIR
echo "**********************************"
~                                                                        
