#!/bin/tcsh -f
set dirName = "/terranova_1/W_Ntuple2012LowPU/Muon/V21/DYToMuMu"
#set dirName = "/terranova_1/W_Ntuple2012LowPU/Muon/VFinal/DYToMuMu"
#set dirName = "/d2/scratch/Storage_Area/W_Ntuple2012LowPU/Muon/V21/DYToMuMu"
set SampleName = "Test"
./chain_make.tcsh $dirName $SampleName

set dirName = "/terranova_1/W_Ntuple2012LowPU/Muon/V21/DYToMuMu"
#set dirName = "/terranova_1/W_Ntuple2012LowPU/Muon/VFinal/DYToMuMu"
#set dirName = "/d2/scratch/Storage_Area/W_Ntuple2012LowPU/Muon/V21/DYToMuMu"
set SampleName = "Muon_DYToMuMu_S8"
./chain_make.tcsh $dirName $SampleName
set dirName = "/terranova_1/W_Ntuple2012LowPU/Muon/V21/TTJets"
#set dirName = "/terranova_1/W_Ntuple2012LowPU/Muon/VFinal/TTJets"
#set dirName = "/d2/scratch/Storage_Area/W_Ntuple2012LowPU/Muon/V21/TTJets"
set SampleName = "Muon_TTJets_S8"
./chain_make.tcsh $dirName $SampleName
set dirName = "/terranova_1/W_Ntuple2012LowPU/Muon/V21/DYToTauTau"
#set dirName = "/terranova_1/W_Ntuple2012LowPU/Muon/VFinal/DYToTauTau"
#set dirName = "/d2/scratch/Storage_Area/W_Ntuple2012LowPU/Muon/V21/DYToTauTau"
set SampleName = "Muon_DYToTauTau_S8"
./chain_make.tcsh $dirName $SampleName
set dirName = "/terranova_1/W_Ntuple2012LowPU/Muon/V21/WToTauNu"
#set dirName = "/terranova_1/W_Ntuple2012LowPU/Muon/VFinal/WToTauNu"
#set dirName = "/d2/scratch/Storage_Area/W_Ntuple2012LowPU/Muon/V21/WToTauNu"
set SampleName = "Muon_WToTauNu_S8"
./chain_make.tcsh $dirName $SampleName
set dirName = "/terranova_1/W_Ntuple2012LowPU/Muon/V21/SingleMuPrompt"
#set dirName = "/terranova_1/W_Ntuple2012LowPU/Muon/VFinal/SingleMuPrompt"
#set dirName = "/d2/scratch/Storage_Area/W_Ntuple2012LowPU/Muon/V21/SingleMuPrompt"
set SampleName = "SingleMuPrompt"
./chain_make.tcsh $dirName $SampleName
set dirName = "/terranova_1/W_Ntuple2012LowPU/Muon/V21/SingleMuReReco"
#set dirName = "/terranova_1/W_Ntuple2012LowPU/Muon/VFinal/SingleMuReReco"
#set dirName = "/d2/scratch/Storage_Area/W_Ntuple2012LowPU/Muon/V21/SingleMuReReco"
set SampleName = "SingleMuReReco"
./chain_make.tcsh $dirName $SampleName
set dirName = "/terranova_1/W_Ntuple2012LowPU/Muon/V22/WmToMuNu"
#set dirName = "/terranova_1/W_Ntuple2012LowPU/Muon/VFinal/WmToMuNu"
#set dirName = "/d2/scratch/Storage_Area/W_Ntuple2012LowPU/Muon/V22/WmToMuNu"
set SampleName = "Muon_WmToMuNu_S8"
./chain_make.tcsh $dirName $SampleName
set dirName = "/terranova_1/W_Ntuple2012LowPU/Muon/V22/WpToMuNu"
#set dirName = "/terranova_1/W_Ntuple2012LowPU/Muon/VFinal/WpToMuNu"
#set dirName = "/d2/scratch/Storage_Area/W_Ntuple2012LowPU/Muon/V22/WpToMuNu"
set SampleName = "Muon_WpToMuNu_S8"
./chain_make.tcsh $dirName $SampleName

set dirName = "/terranova_1/W_Ntuple2012LowPU/Electron/ElectronVOct/DYToEE"
#set dirName = "/terranova_1/W_Ntuple2012LowPU/Electron/ElectronVFinal/DYToEE"
#set dirName = "/d2/scratch/Storage_Area/W_Ntuple2012LowPU/ElectronV14/DYToEE"
set SampleName = "Electron_DYToEE_S8"
./chain_make.tcsh $dirName $SampleName
set dirName = "/terranova_1/W_Ntuple2012LowPU/Electron/ElectronVOct/DYToTauTau"
#set dirName = "/terranova_1/W_Ntuple2012LowPU/Electron/ElectronVFinal/DYToTauTau"
#set dirName = "/d2/scratch/Storage_Area/W_Ntuple2012LowPU/ElectronV14/DYToTauTau"
set SampleName = "Electron_DYToTauTau_S8"
./chain_make.tcsh $dirName $SampleName
set dirName = "/terranova_1/W_Ntuple2012LowPU/Electron/ElectronVOct/TTJets"
#set dirName = "/terranova_1/W_Ntuple2012LowPU/Electron/ElectronVFinal/TTJets"
#set dirName = "/d2/scratch/Storage_Area/W_Ntuple2012LowPU/ElectronV14/TTJets"
set SampleName = "Electron_TTJets_S8"
./chain_make.tcsh $dirName $SampleName
set dirName = "/terranova_1/W_Ntuple2012LowPU/Electron/ElectronVOct/WToTauNu"
#set dirName = "/terranova_1/W_Ntuple2012LowPU/Electron/ElectronVFinal/WToTauNu"
#set dirName = "/d2/scratch/Storage_Area/W_Ntuple2012LowPU/ElectronV14/WToTauNu"
set SampleName = "Electron_WToTauNu_S8"
./chain_make.tcsh $dirName $SampleName
set dirName = "/terranova_1/W_Ntuple2012LowPU/Electron/ElectronV21/WminusToEleNu"
#set dirName = "/terranova_1/W_Ntuple2012LowPU/Electron/ElectronVFinal/WminusToEleNu"
#set dirName = "/d2/scratch/Storage_Area/W_Ntuple2012LowPU/ElectronV21/WminusToEleNu"
set SampleName = "Electron_WmToEleNu_S8"
./chain_make.tcsh $dirName $SampleName
set dirName = "/terranova_1/W_Ntuple2012LowPU/Electron/ElectronV21/WplusToEleNu"
#set dirName = "/terranova_1/W_Ntuple2012LowPU/Electron/ElectronVFinal/WplusToEleNu"
#set dirName = "/d2/scratch/Storage_Area/W_Ntuple2012LowPU/ElectronV21/WplusToEleNu"
set SampleName = "Electron_WpToEleNu_S8"
./chain_make.tcsh $dirName $SampleName
set dirName = "/terranova_1/W_Ntuple2012LowPU/Electron/ElectronVOct/SingleElePrompt"
#set dirName = "/terranova_1/W_Ntuple2012LowPU/Electron/ElectronVFinal/SingleElePrompt"
#set dirName = "/d2/scratch/Storage_Area/W_Ntuple2012LowPU/ElectronV17/SingleElePrompt"
set SampleName = "Electron_SingleElePrompt"
./chain_make.tcsh $dirName $SampleName
set dirName = "/terranova_1/W_Ntuple2012LowPU/Electron/ElectronVOct/SingleEleReReco"
#set dirName = "/terranova_1/W_Ntuple2012LowPU/Electron/ElectronVFinal/SingleEleReReco"
#set dirName = "/d2/scratch/Storage_Area/W_Ntuple2012LowPU/ElectronV17/SingleEleReReco"
set SampleName = "Electron_SingleEleReReco"
./chain_make.tcsh $dirName $SampleName

