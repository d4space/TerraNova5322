#!/bin/tcsh -f
#set DIRNAME = $1
  set DIRNAME = '/terranova_1/TestNtuple'
  #set DIRNAME = '/d2/scratch/Storage_Area/Wpt-ntuple/Muon/V7_Recoil/TTJets'
  echo $DIRNAME
  #foreach fileName ( `ls  $DIRNAME/*.root | awk '{print $9}' `)
  echo 'void chain_Test( TChain *chains)'>chain_Test.h
  echo '{'>>chain_Test.h
  foreach fileName ( `ls  $DIRNAME/*.root `)
    echo $fileName
    echo '  chains->Add("'$fileName'");'>>chain_Test.h
  end
  echo '}'>>chain_Test.h
