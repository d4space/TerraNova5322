#!/bin/tcsh -f
#set dirName_base = "/terranova_1/W_Ntuple2012LowPU/Muon/V9_GenTable"
#set dirName_base = "/terranova_1/W_Ntuple2012LowPU/Muon/Acceptance"
#set dirName_base = "/d2/scratch/Storage_Area/AcceptanceFSR"
set dirName_base = "/terranova_1/W_Ntuple2012LowPU/AcceptanceFSR"
set dirName = "$dirName_base/WpToMuNu"
./chain_Muon_WpToMuNu_S8_Accpt.tcsh $dirName
set dirName = "$dirName_base/WmToMuNu"
./chain_Muon_WmToMuNu_S8_Accpt.tcsh $dirName

#set dirName_base = "/d2/scratch/Storage_Area/Acceptance_Hammid"
#set dirName_base = "/d2/scratch/Storage_Area/W_Ntuple2012LowPU/Muon/V10_NoHLTFilter"
set dirName = "$dirName_base/WpToEleNu"
./chain_Electron_WpToEleNu_S8_Accpt.tcsh $dirName
set dirName = "$dirName_base/WmToEleNu"
./chain_Electron_WmToEleNu_S8_Accpt.tcsh $dirName
