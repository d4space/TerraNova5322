#!/bin/tcsh -f
set dirName = "/terranova_1/TestNtuple"
set SampleName = "Test"
./chain_make.tcsh $dirName $SampleName

set dirName = "/terranova_1/W_Ntuple2012LowPU/Muon/V21/DYToMuMu"
set SampleName = "Muon_DYToMuMu_S8"
./chain_make.tcsh $dirName $SampleName
set dirName = "/terranova_1/W_Ntuple2012LowPU/Muon/V21/TTJets"
set SampleName = "Muon_TTJets_S8"
./chain_make.tcsh $dirName $SampleName
set dirName = "/terranova_1/W_Ntuple2012LowPU/Muon/V21/DYToTauTau"
set SampleName = "Muon_DYToTauTau"
./chain_make.tcsh $dirName $SampleName
set dirName = "/terranova_1/W_Ntuple2012LowPU/Muon/V21/WToTauNu"
set SampleName = "Muon_WToTauNu"
./chain_make.tcsh $dirName $SampleName
set dirName = "/terranova_1/W_Ntuple2012LowPU/Muon/V21/WToTauNu"
set SampleName = "Muon_WToTauNu"
./chain_make.tcsh $dirName $SampleName
set dirName = "/terranova_1/W_Ntuple2012LowPU/Muon/V21/SingleMuPrompt"
set SampleName = "SingleMuPrompt"
./chain_make.tcsh $dirName $SampleName
set dirName = "/terranova_1/W_Ntuple2012LowPU/Muon/V21/SingleMuReReco"
set SampleName = "SingleMuReReco"
./chain_make.tcsh $dirName $SampleName
set dirName = "/terranova_1/W_Ntuple2012LowPU/Muon/V22/WmToMuNu"
set SampleName = "Muon_WmToMuNu"
./chain_make.tcsh $dirName $SampleName
set dirName = "/terranova_1/W_Ntuple2012LowPU/Muon/V22/WpToMuNu"
set SampleName = "Muon_WpToMuNu"
./chain_make.tcsh $dirName $SampleName

set dirName = "/terranova_1/W_Ntuple2012LowPU/Electron/ElectronVOct/DYToEE"
set SampleName = "Electron_DYToEE"
./chain_make.tcsh $dirName $SampleName
set dirName = "/terranova_1/W_Ntuple2012LowPU/Electron/ElectronVOct/DYToTauTau"
set SampleName = "Electron_DYToTauTau"
./chain_make.tcsh $dirName $SampleName
set dirName = "/terranova_1/W_Ntuple2012LowPU/Electron/ElectronVOct/TTJets"
set SampleName = "Electron_TTJets"
./chain_make.tcsh $dirName $SampleName
set dirName = "/terranova_1/W_Ntuple2012LowPU/Electron/ElectronVOct/WToTauNu"
set SampleName = "Electron_WToTauNu"
./chain_make.tcsh $dirName $SampleName
set dirName = "/terranova_1/W_Ntuple2012LowPU/Electron/ElectronV21/WminusToEleNu"
set SampleName = "Electron_WmToEleNu"
./chain_make.tcsh $dirName $SampleName
set dirName = "/terranova_1/W_Ntuple2012LowPU/Electron/ElectronV21/WplusToEleNu"
set SampleName = "Electron_WpToEleNu"
./chain_make.tcsh $dirName $SampleName
set dirName = "/terranova_1/W_Ntuple2012LowPU/Electron/ElectronVOct/SingleElePrompt"
set SampleName = "Electron_SingleElePrompt"
./chain_make.tcsh $dirName $SampleName
set dirName = "/terranova_1/W_Ntuple2012LowPU/Electron/ElectronVOct/SingleEleReReco"
set SampleName = "Electron_SingleEleReReco"
./chain_make.tcsh $dirName $SampleName

