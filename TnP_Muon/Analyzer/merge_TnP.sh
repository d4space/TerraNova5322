#!/bin/bash

if [ $# != 2 ]; then
	echo " ----------------------------------------------------- "
  echo "  Usage : ./merge_Ana.sh <file_name> <folder_name>     "
  echo " ----------------------------------------------------- "
else
  BASEDIR=/terranova_1/W_TnP/Muon/V4
	LINE=$(ls $BASEDIR/$2/*.root | wc -l)
  echo $0 $1 $2 '  : Merging to '$1' from all root files in '$BASEDIR/$2''
	if [ $LINE -gt 900 ]; then
		echo $LINE
		N=0
		N=`expr $LINE - 900`
		hadd -f $1 $(for file1 in `ls $BASEDIR/$2/*.root | head -n 900`; do echo "$file1"; done)
		hadd -f $1 $(for file2 in `ls $BASEDIR/$2/*.root | tail -n $N`; do echo "$file2"; done)
		#for file1 in `ls $BASEDIR/$2/$2/*.root | head -n 900`; do echo "$file1"; done
		#for file2 in `ls $BASEDIR/$2/$2/*.root | tail -n $N | `; do echo "$file2"; done
	else
	  hadd -f $1 $(for file in `ls $BASEDIR/$2/*.root`; do echo "$file"; done)
		#for file in `ls $BASEDIR/$2/$2/*.root`; do echo "$file"; done
	fi
fi

