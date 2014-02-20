#!/bin/tcsh -f
#set DIRNAME = '/d2/scratch/Storage_Area/Wpt-ntuple/Electron_V6_evtClean/DYToEE'
set DIRNAME = '/d1/scratch/kimyn/cms/MET/CMSSW_5_3_9/src/KNUPhy/NtupleMaker/test/McS10_2012/batch/EMEnriched/Pt_20To30'
echo $DIRNAME
#foreach fileName ( `ls  $DIRNAME/*.root | awk '{print $9}' `)
echo 'void chain_Electron_QCD_EMEnriched_20to30_S10( TChain *chains)'>chain_Electron_QCD_EMEnriched_20to30_S10.h
echo '{'>>chain_Electron_QCD_EMEnriched_20to30_S10.h
foreach fileName ( `ls  $DIRNAME/*.root `)
  echo $fileName
  echo '  chains->Add("'$fileName'");'>>chain_Electron_QCD_EMEnriched_20to30_S10.h
end
echo '}'>>chain_Electron_QCD_EMEnriched_20to30_S10.h
