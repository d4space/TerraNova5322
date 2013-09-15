#!/bin/bash

#/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions12/8TeV
BaseDir=/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions12/8TeV

#AnalysisJSON=../JSON/json_190456_207898_analysis.txt
AnalysisJSON1=${BaseDir}/Reprocessing/Cert_190456-196531_8TeV_13Jul2012ReReco_Collisions12_JSON_v2.txt
AnalysisJSON2=${BaseDir}/Reprocessing/Cert_190782-190949_8TeV_06Aug2012ReReco_Collisions12_JSON.txt
AnalysisJSON3=${BaseDir}/Reprocessing/Cert_190456-196531_8TeV_13Jul2012ReReco_Collisions12_JSON_v2.txt
AnalysisJSON4=${BaseDir}/Reprocessing/Cert_198022-198523_8TeV_24Aug2012ReReco_Collisions12_JSON.txt
AnalysisJSON5=${BaseDir}/Prompt/Cert_190456-203002_8TeV_PromptReco_Collisions12_JSON_v2.txt
AnalysisJSON6=${BaseDir}/Reprocessing/Cert_201191-201191_8TeV_11Dec2012ReReco-recover_Collisions12_JSON.txt
#AnalysisJSON7=Cert_203768_208686_8TeV_PromptReco_Collisions12_JSON.txt

#${BaseDir}/Prompt/Cert_190456-203002_8TeV_PromptReco_Collisions12_JSON.txt
LumiJSON=${BaseDir}/PileUp/pileup_JSON_DCSONLY_190389-208686_corr.txt

#JSON file used to filter events (from DCSOnly or Prompt subdir)

pileupCalc.py \
    -i ${AnalysisJSON1} \
    --inputLumiJSON ${LumiJSON} \
    --calcMode true \
    --minBiasXsec 69300 \
    --maxPileupBin 60 \
    --numPileupBins 60  \
    DataPileupHistogram_Run2012A-13Jul2012.root

pileupCalc.py \
    -i ${AnalysisJSON2} \
    --inputLumiJSON ${LumiJSON} \
    --calcMode true \
    --minBiasXsec 69300 \
    --maxPileupBin 60 \
    --numPileupBins 60  \
    DataPileupHistogram_Run2012A-recover-06Aug2012.root

pileupCalc.py \
    -i ${AnalysisJSON3} \
    --inputLumiJSON ${LumiJSON} \
    --calcMode true \
    --minBiasXsec 69300 \
    --maxPileupBin 60 \
    --numPileupBins 60  \
    DataPileupHistogram_Run2012B-13Jul2012.root

pileupCalc.py \
    -i ${AnalysisJSON4} \
    --inputLumiJSON ${LumiJSON} \
    --calcMode true \
    --minBiasXsec 69300 \
    --maxPileupBin 60 \
    --numPileupBins 60  \
    DataPileupHistogram_Run2012C-24Aug2012.root

pileupCalc.py \
    -i ${AnalysisJSON5} \
    --inputLumiJSON ${LumiJSON} \
    --calcMode true \
    --minBiasXsec 69300 \
    --maxPileupBin 60 \
    --numPileupBins 60  \
    DataPileupHistogram_Run2012C-PromptReco-v2.root

pileupCalc.py \
    -i ${AnalysisJSON6} \
    --inputLumiJSON ${LumiJSON} \
    --calcMode true \
    --minBiasXsec 69300 \
    --maxPileupBin 60 \
    --numPileupBins 60  \
    DataPileupHistogram_Run2012C-EcalRecover_11Dec2012.root

#pileupCalc.py \
#    -i ${AnalysisJSON7} \
#    --inputLumiJSON ${LumiJSON} \
#    --calcMode true \
#    --minBiasXsec 69300 \
#    --maxPileupBin 60 \
#    --numPileupBins 60  \
#    DataPileupHistogram_Run2012D-PromptReco-v1.root

#pileupCalc.py \
#    -i ${AnalysisJSON} \
#    --inputLumiJSON ${LumiJSON} \
#    --calcMode true \
#    --minBiasXsec 73500 \
#    --maxPileupBin 60 \
#    --numPileupBins 60  \
#    DataPileupHistogram-73p5mb.root
