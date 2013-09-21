#!/bin/tcsh -f
#set DIRNAME = '/d2/scratch/Storage_Area/Wpt-ntuple/Electron_V6_evtClean/WToTauNu'
set DIRNAME = '/d1/scratch/jungmin/cms/CMSSW_5_3_9/src/KoSMP/WAnalyzer/test/RDHighPU2012/Run2012A_13Jul'
echo $DIRNAME
#foreach fileName ( `ls  $DIRNAME/*.root | awk '{print $9}' `)
echo 'void chain_Electron_RD_HighPU( TChain *chains)'>chain_Electron_RD_HighPU.h
echo '{'>>chain_Electron_RD_HighPU.h
foreach fileName ( `ls  $DIRNAME/*.root `)
  echo $fileName
  echo '  chains->Add("'$fileName'");'>>chain_Electron_RD_HighPU.h
end
echo '}'>>chain_Electron_RD_HighPU.h
