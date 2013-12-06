#!/bin/tcsh -f
#set DIRNAME = '/d2/scratch/Storage_Area/Wpt-ntuple/Electron_V6_evtClean/DYToEE'
set DIRNAME = '/d1/scratch/kimyn/cms/MET/CMSSW_5_3_9/src/KNUPhy/WAnalyzer/test/McS10_2012/batch/EMEnriched/QCD_Pt_80to170/'
echo $DIRNAME
#foreach fileName ( `ls  $DIRNAME/*.root | awk '{print $9}' `)
echo 'void chain_Electron_QCD_EMEnriched_80to170_S10( TChain *chains)'>chain_Electron_QCD_EMEnriched_80to170_S10.h
echo '{'>>chain_Electron_QCD_EMEnriched_80to170_S10.h
foreach fileName ( `ls  $DIRNAME/*.root `)
  echo $fileName
  echo '  chains->Add("'$fileName'");'>>chain_Electron_QCD_EMEnriched_80to170_S10.h
end
echo '}'>>chain_Electron_QCD_EMEnriched_80to170_S10.h
