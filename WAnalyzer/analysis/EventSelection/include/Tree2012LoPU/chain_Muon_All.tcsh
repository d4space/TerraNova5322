#!/bin/tcsh -f
#set dirName_base = "/terranova_1/W_Ntuple2012LowPU/Muon/V9_GenTable"
#set dirName_base = "/terranova_1/W_Ntuple2012LowPU/Muon/V14"
#set dirName_base = "/d2/scratch/Storage_Area/W_Ntuple2012LowPU/Muon/V10_NoHLTFilter"
#set dirName_base = "/d2/scratch/Storage_Area/W_Ntuple2012LowPU/Muon/V14"
set dirName_base = "/terranova_1/W_Ntuple2012LowPU/Muon/V21"
# RD dir should be put at dirName_base/SingleMuPrompt, SingleMuReco
./chain_Muon_RD_LowPU.tcsh $dirName_base
set dirName = "$dirName_base/DYToMuMu"
./chain_Muon_DYToMuMu_S8.tcsh $dirName
set dirName = "$dirName_base/DYToTauTau"
./chain_Muon_DYToTauTau_S8.tcsh $dirName
#set dirName = "$dirName_base/QCD_S7"
#./chain_Muon_QCD_Mu_S7.tcsh $dirName
#./chain_Muon_QCD_Mu_S8.tcsh $dirName
set dirName = "$dirName_base/TTJets"
./chain_Muon_TTJets_S8.tcsh $dirName
set dirName = "$dirName_base/WToTauNu"
./chain_Muon_WToTauNu_S8.tcsh $dirName
set dirName_base = "/terranova_1/W_Ntuple2012LowPU/Muon/V22"
set dirName = "$dirName_base/WmToMuNu"
./chain_Muon_WmToMuNu_S8.tcsh $dirName
set dirName = "$dirName_base/WpToMuNu"
./chain_Muon_WpToMuNu_S8.tcsh $dirName
