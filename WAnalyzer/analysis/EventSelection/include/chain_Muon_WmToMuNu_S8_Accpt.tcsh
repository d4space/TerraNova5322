#!/bin/tcsh -f
set DIRNAME = $1
  echo $DIRNAME
  #foreach fileName ( `ls  $DIRNAME/*.root | awk '{print $9}' `)
  echo 'void chain_Muon_WmToMuNu_S8_Accpt( TChain *chains)'>chain_Muon_WmToMuNu_S8_Accpt.h
  echo '{'>>chain_Muon_WmToMuNu_S8_Accpt.h
  foreach fileName ( `ls  $DIRNAME/*.root `)
    echo $fileName
    echo '  chains->Add("'$fileName'");'>>chain_Muon_WmToMuNu_S8_Accpt.h
  end
  echo '}'>>chain_Muon_WmToMuNu_S8_Accpt.h
