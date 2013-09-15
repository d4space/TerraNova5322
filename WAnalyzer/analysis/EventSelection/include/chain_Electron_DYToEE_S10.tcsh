#!/bin/tcsh -f
#set DIRNAME = '/d2/scratch/Storage_Area/Wpt-ntuple/Electron_V6_evtClean/DYToEE'
set DIRNAME = '/d1/scratch/jungmin/cms/CMSSW_5_3_9/src/KNUPhy/WAnalyzer/test/McS10_2012/batch/DYToEE/'
echo $DIRNAME
#foreach fileName ( `ls  $DIRNAME/*.root | awk '{print $9}' `)
echo 'void chain_Electron_DYToEE_S10( TChain *chains)'>chain_Electron_DYToEE_S10.h
echo '{'>>chain_Electron_DYToEE_S10.h
foreach fileName ( `ls  $DIRNAME/*.root `)
  echo $fileName
  echo '  chains->Add("'$fileName'");'>>chain_Electron_DYToEE_S10.h
end
echo '}'>>chain_Electron_DYToEE_S10.h
