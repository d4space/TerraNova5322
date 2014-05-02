#!/bin/tcsh -f
set dirName = "/terranova_1/TestNtuple"
#set dirName = "/d2/scratch/Storage_Area/W_Ntuple2012LowPU/Muon/V21/DYToMuMu"
set SampleName = "Test"
./chain_make.tcsh $dirName $SampleName

set dirName = "/terranova_1/W_Ntuple2012LowPU/Muon/V21/DYToMuMu"
#set dirName = "/d2/scratch/Storage_Area/W_Ntuple2012LowPU/Muon/V21/DYToMuMu"
set SampleName = "Muon_DYToMuMu_S8"
./chain_make.tcsh $dirName $SampleName
set dirName = "/terranova_1/W_Ntuple2012LowPU/Muon/V21/TTJets"
#set dirName = "/d2/scratch/Storage_Area/W_Ntuple2012LowPU/Muon/V21/TTJets"
set SampleName = "Muon_TTJets_S8"
./chain_make.tcsh $dirName $SampleName
set dirName = "/terranova_1/W_Ntuple2012LowPU/Muon/V21/DYToTauTau"
#set dirName = "/d2/scratch/Storage_Area/W_Ntuple2012LowPU/Muon/V21/DYToTauTau"
set SampleName = "Muon_DYToTauTau_S8"
./chain_make.tcsh $dirName $SampleName
set dirName = "/terranova_1/W_Ntuple2012LowPU/Muon/V21/WToTauNu"
#set dirName = "/d2/scratch/Storage_Area/W_Ntuple2012LowPU/Muon/V21/WToTauNu"
set SampleName = "Muon_WToTauNu_S8"
./chain_make.tcsh $dirName $SampleName
set dirName = "/terranova_1/W_Ntuple2012LowPU/Muon/V21/SingleMuPrompt"
#set dirName = "/d2/scratch/Storage_Area/W_Ntuple2012LowPU/Muon/V21/WToTauNu"
set SampleName = "SingleMuPrompt"
./chain_make.tcsh $dirName $SampleName
set dirName = "/terranova_1/W_Ntuple2012LowPU/Muon/V21/SingleMuReReco"
#set dirName = "/d2/scratch/Storage_Area/W_Ntuple2012LowPU/Muon/V21/SingleMuReReco"
set SampleName = "SingleMuReReco"
./chain_make.tcsh $dirName $SampleName
set dirName = "/terranova_1/W_Ntuple2012LowPU/Muon/V22/WmToMuNu"
#set dirName = "/d2/scratch/Storage_Area/W_Ntuple2012LowPU/Muon/V22/WmToMuNu"
set SampleName = "Muon_WmToMuNu_S8"
./chain_make.tcsh $dirName $SampleName
set dirName = "/terranova_1/W_Ntuple2012LowPU/Muon/V22/WpToMuNu"
#set dirName = "/d2/scratch/Storage_Area/W_Ntuple2012LowPU/Muon/V22/WpToMuNu"
set SampleName = "Muon_WpToMuNu_S8"
./chain_make.tcsh $dirName $SampleName

set dirName = "/terranova_1/W_Ntuple2012LowPU/Electron/ElectronVOct/DYToEE"
#set dirName = "/d2/scratch/Storage_Area/W_Ntuple2012LowPU/ElectronV14/DYToEE"
set SampleName = "Electron_DYToEE_S8"
./chain_make.tcsh $dirName $SampleName
set dirName = "/terranova_1/W_Ntuple2012LowPU/Electron/ElectronVOct/DYToTauTau"
#set dirName = "/d2/scratch/Storage_Area/W_Ntuple2012LowPU/ElectronV14/DYToTauTau"
set SampleName = "Electron_DYToTauTau_S8"
./chain_make.tcsh $dirName $SampleName
set dirName = "/terranova_1/W_Ntuple2012LowPU/Electron/ElectronVOct/TTJets"
#set dirName = "/d2/scratch/Storage_Area/W_Ntuple2012LowPU/ElectronV14/TTJets"
set SampleName = "Electron_TTJets_S8"
./chain_make.tcsh $dirName $SampleName
set dirName = "/terranova_1/W_Ntuple2012LowPU/Electron/ElectronVOct/WToTauNu"
#set dirName = "/d2/scratch/Storage_Area/W_Ntuple2012LowPU/ElectronV14/WToTauNu"
set SampleName = "Electron_WToTauNu_S8"
./chain_make.tcsh $dirName $SampleName
set dirName = "/terranova_1/W_Ntuple2012LowPU/Electron/ElectronV21/WminusToEleNu"
#set dirName = "/d2/scratch/Storage_Area/W_Ntuple2012LowPU/ElectronV21/WminusToEleNu"
set SampleName = "Electron_WmToEleNu_S8"
./chain_make.tcsh $dirName $SampleName
set dirName = "/terranova_1/W_Ntuple2012LowPU/Electron/ElectronV21/WplusToEleNu"
#set dirName = "/d2/scratch/Storage_Area/W_Ntuple2012LowPU/ElectronV21/WplusToEleNu"
set SampleName = "Electron_WpToEleNu_S8"
./chain_make.tcsh $dirName $SampleName
set dirName = "/terranova_1/W_Ntuple2012LowPU/Electron/ElectronVOct/SingleElePrompt"
#set dirName = "/d2/scratch/Storage_Area/W_Ntuple2012LowPU/ElectronV17/SingleElePrompt"
set SampleName = "Electron_SingleElePrompt"
./chain_make.tcsh $dirName $SampleName
set dirName = "/terranova_1/W_Ntuple2012LowPU/Electron/ElectronVOct/SingleEleReReco"
#set dirName = "/d2/scratch/Storage_Area/W_Ntuple2012LowPU/ElectronV17/SingleEleReReco"
set SampleName = "Electron_SingleEleReReco"
./chain_make.tcsh $dirName $SampleName

