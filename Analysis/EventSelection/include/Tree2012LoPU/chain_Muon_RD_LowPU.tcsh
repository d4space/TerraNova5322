#!/bin/tcsh -f
set DIRNAME_Base = $1
set DIRNAME_SMPrompt = "$DIRNAME_Base/SingleMuPrompt"
set DIRNAME_SMReReco = "$DIRNAME_Base/SingleMuReReco"
  #set DIRNAME = '/terranova_1/W_Ntuple/Muon/V6_evtClean/SingleMuPrompt'
  #set DIRNAME = '/d2/scratch/Storage_Area/Wpt-ntuple/Muon/V7_Recoil/SingleMuPrompt'
  echo $DIRNAME_SMPrompt
  #foreach fileName ( `ls  $DIRNAME/*.root | awk '{print $9}' `)
  echo 'void chain_Muon_RD_LowPU( TChain *chains)'>chain_Muon_RD_LowPU.h
  echo '{'>>chain_Muon_RD_LowPU.h
  foreach fileName ( `ls  $DIRNAME_SMPrompt/*.root `)
    echo $fileName
    echo '  chains->Add("'$fileName'");'>>chain_Muon_RD_LowPU.h
  end
  #set DIRNAME = '/terranova_1/W_Ntuple/Muon/V6_evtClean/SingleMuReReco'
  #set DIRNAME = '/d2/scratch/Storage_Area/Wpt-ntuple/Muon/V7_Recoil/SingleMuReReco'
  echo $DIRNAME_SMReReco
  foreach fileName ( `ls  $DIRNAME_SMReReco/*.root `)
    echo $fileName
    echo '  chains->Add("'$fileName'");'>>chain_Muon_RD_LowPU.h
  end
  echo '}'>>chain_Muon_RD_LowPU.h
