#!/bin/tcsh -f
if (1 != 1) then
  #if ($# != 1) then
  echo "*************************************************"
  echo "*                                               *"
  echo "* Usage : ./chainFileMakeM20.tcsh <input dir_name>     *"
  echo "********************************************"
else
  set DIRNAME = '/terranova_1/W_Ntuple/SingleMuRun2012APromptRecoV1Aod'
  echo $DIRNAME
  #foreach fileName ( `ls  $DIRNAME/*.root | awk '{print $9}' `)
  #echo 'void chain_HLT_Double_DYM20( TChain *chains)'>chain_HLT_Double_DYM20.C
  #echo '{'>>chain_HLT_Double_DYM20.C
  if ( -e fileList.txt) rm -f fileList.txt
  touch fileList.txt
  set i="0"
  foreach fileName ( `ls  $DIRNAME/*.root `)
    echo $fileName
    echo '  f['$i'] = new TFile("'$fileName'");'>>fileList.txt
    set i=`expr $i + 1`
  end
  #echo '}'>>chain_HLT_Double_DYM20.C
endif
