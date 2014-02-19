#!/bin/tcsh -f
#set dirName_base = "/terranova_1/W_Ntuple2012LowPU/Electron/ElectronV8Gentable"
set dirName_base = "/d2/scratch/Storage_Area/W_Ntuple2012LowPU/ElectronV9Gentable"
#set dirName_base = "/terranova_1/W_Ntuple2012LowPU/Electron/ElectronV9Gentable"
# RD dir should be put at dirName_base/SingleElePrompt, SingleEleReReco
./chain_Electron_RD_LowPU.tcsh $dirName_base
set dirName = "$dirName_base/DYToEE"
./chain_Electron_DYToEE_S8.tcsh $dirName
set dirName = "$dirName_base/DYToTauTau"
./chain_Electron_DYToTauTau_S8.tcsh $dirName
set dirName = "$dirName_base/TTJets"
./chain_Electron_TTJets_S8.tcsh $dirName
set dirName = "$dirName_base/WToTauNu"
./chain_Electron_WToTauNu_S8.tcsh $dirName
set dirName = "$dirName_base/WminusToEleNu"
./chain_Electron_WmToEleNu_S8.tcsh $dirName
set dirName = "$dirName_base/WplusToEleNu"
./chain_Electron_WpToEleNu_S8.tcsh $dirName
