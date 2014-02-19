#!/bin/tcsh -f
set DIRNAME = $1
  #set DIRNAME = '/terranova_1/W_Ntuple/Muon/V6_evtClean/WplusToMuNu'
  #set DIRNAME = '/d2/scratch/Storage_Area/Wpt-ntuple/Muon/V7_Recoil/WplusToMuNu'
  echo $DIRNAME
  #foreach fileName ( `ls  $DIRNAME/*.root | awk '{print $9}' `)
  echo 'void chain_Muon_WpToMuNu_S8_Accpt( TChain *chains)'>chain_Muon_WpToMuNu_S8_Accpt.h
  echo '{'>>chain_Muon_WpToMuNu_S8_Accpt.h
  foreach fileName ( `ls  $DIRNAME/*.root `)
    echo $fileName
    echo '  chains->Add("'$fileName'");'>>chain_Muon_WpToMuNu_S8_Accpt.h
  end
  echo '}'>>chain_Muon_WpToMuNu_S8_Accpt.h
