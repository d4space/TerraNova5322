#!/bin/tcsh -f
set DIRNAME = $1
  echo $DIRNAME
  echo 'void chain_Electron_WmToEleNu_S8_Accpt( TChain *chains)'>chain_Electron_WmToEleNu_S8_Accpt.h
  echo '{'>>chain_Electron_WmToEleNu_S8_Accpt.h
  foreach fileName ( `ls  $DIRNAME/*.root `)
    echo $fileName
    echo '  chains->Add("'$fileName'");'>>chain_Electron_WmToEleNu_S8_Accpt.h
  end
  echo '}'>>chain_Electron_WmToEleNu_S8_Accpt.h
