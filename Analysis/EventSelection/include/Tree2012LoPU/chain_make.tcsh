#!/bin/tcsh -f
set DirName = $1
set SampleName = $2
set OutFile = "chain_$SampleName.h"
echo "The directory is $DirName"
  #foreach fileName ( `ls  $DIRNAME/*.root | awk '{print $9}' `)
  echo "void chain_$SampleName( TChain *chains)">$OutFile
  echo '{'>>$OutFile
  foreach fileName ( `ls  $DirName/*.root `)
    echo $fileName
    echo '  chains->Add("'$fileName'");'>>$OutFile
  end
  echo '}'>>$OutFile
