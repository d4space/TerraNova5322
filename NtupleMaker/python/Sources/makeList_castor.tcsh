#!/bin/tcsh -f
if (1 != 1) then
  #if ($# != 1) then
  echo "*************************************************"
  echo "*                                               *"
  echo "* Usage : ./chainFileMakeM20.tcsh <input dir_name>     *"
  echo "********************************************"
else
  set DIRNAME = '/castor/cern.ch/user/s/salee/W2012/Real/SingleMu_Run2012A_PromptReco_v1/'
  echo $DIRNAME
  if(-e file.List) then
  echo "removing file.List"
  rm -f file.List
  endif
  touch file.List
  foreach fileName ( `rfdir  $DIRNAME | awk '{print $9}' `)
    echo \'rfio:///$DIRNAME/$fileName\', to file.List
    echo \'rfio:///$DIRNAME/$fileName\',>>file.List
  end
endif

