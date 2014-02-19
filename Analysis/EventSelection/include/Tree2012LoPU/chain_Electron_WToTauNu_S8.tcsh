#!/bin/tcsh -f
#set DIRNAME = '/d2/scratch/Storage_Area/Wpt-ntuple/Electron_V6_evtClean/WToTauNu'
set DIRNAME = $1
echo $DIRNAME
#foreach fileName ( `ls  $DIRNAME/*.root | awk '{print $9}' `)
echo 'void chain_Electron_WToTauNu_S8( TChain *chains)'>chain_Electron_WToTauNu_S8.h
echo '{'>>chain_Electron_WToTauNu_S8.h
foreach fileName ( `ls  $DIRNAME/*.root `)
  echo $fileName
  echo '  chains->Add("'$fileName'");'>>chain_Electron_WToTauNu_S8.h
end
echo '}'>>chain_Electron_WToTauNu_S8.h
