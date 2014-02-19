#!/bin/tcsh -f
if (1 != 1) then
  #if ($# != 1) then
  echo "*************************************************"
  echo "*                                               *"
  echo "* Usage : ./chainFileMakeM20.tcsh <input dir_name>     *"
  echo "********************************************"
else
  set DIRNAME = '/terranova_1/W_Skim/MC/Electron/WplusToENu'
  echo $DIRNAME
  if(-e file.List) then
  echo "removing file.List"
  rm -f file.List
  endif
  touch file.List
  foreach fileName ( `ls  $DIRNAME `)
    #foreach fileName ( `ls  $DIRNAME | awk '{print $9}' `)
    echo \'file:$DIRNAME/$fileName\', to file.List
    echo \'file:$DIRNAME/$fileName\',>>file.List
  end
endif

