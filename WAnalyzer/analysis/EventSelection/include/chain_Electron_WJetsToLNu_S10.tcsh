#!/bin/tcsh -f
#set DIRNAME = '/d2/scratch/Storage_Area/Wpt-ntuple/Electron_V6_evtClean/TTJets'
set DIRNAME = '/afs/cern.ch/work/k/kbutanov/public/NoPuMET/MVANoPUMET_nTuple/Muon/srcLept/WJetsToLNu'
echo $DIRNAME
#foreach fileName ( `ls  $DIRNAME/*.root | awk '{print $9}' `)
echo 'void chain_Electron_WJets_S10( TChain *chains)'>chain_Electron_WJets_S10.h
echo '{'>>chain_Electron_WJets_S10.h
foreach fileName ( `ls  $DIRNAME/*.root `)
  echo $fileName
  echo '  chains->Add("'$fileName'");'>>chain_Electron_WJets_S10.h
end
echo '}'>>chain_Electron_WJets_S10.h
