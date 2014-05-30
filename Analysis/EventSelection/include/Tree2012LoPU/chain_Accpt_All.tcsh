#!/bin/tcsh -f
#set dirName_base = "/terranova_1/W_Ntuple2012LowPU/AcceptanceFSR"
set dirName_base = "/terranova_1/W_Ntuple2012LowPU/AcceptanceNT"
#set dirName_base = "/d2/scratch/Storage_Area/AcceptanceFSR"
set dirName = "$dirName_base/WpToMuNu"
set SampleName = "Muon_WpToMuNu_S8_Accpt"
./chain_make.tcsh $dirName $SampleName
set dirName = "$dirName_base/WmToMuNu"
set SampleName = "Muon_WmToMuNu_S8_Accpt"
./chain_make.tcsh $dirName $SampleName
set dirName = "$dirName_base/WpToEleNu"
set SampleName = "Electron_WpToEleNu_S8_Accpt"
./chain_make.tcsh $dirName $SampleName
set dirName = "$dirName_base/WmToEleNu"
set SampleName = "Electron_WmToEleNu_S8_Accpt"
./chain_make.tcsh $dirName $SampleName
