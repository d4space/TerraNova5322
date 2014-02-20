#!/bin/tcsh -f
if (1 != 1) then
  #if ($# != 1) then
  echo "*************************************************"
  echo "*                                               *"
  echo "* Usage : ./chainMuonLowPU.tcsh <input dir_name>     *"
  echo "********************************************"
else
  set DIRNAME = './'
  echo $DIRNAME
  echo "Calculating LowPU"
  pileupCalc.py -i ../../NtupleMaker/prod/JSONs/Collision12_Muon_low_PU_JSON.txt --inputLumiJSON ../../NtupleMaker/prod/JSONs/pileup_JSON_DCSONLY_190389-193575.txt --calcMode observed --minBiasXsec 69300 --maxPileupBin 25 --numPileupBins 25 LowPUHist.root
  echo "Low PU distribution root file created"
endif
