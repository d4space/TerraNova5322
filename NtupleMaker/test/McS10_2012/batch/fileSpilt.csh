#!/bin/tcsh -f

set MC = $argv[1]
set File = $argv[2]

####################
split -l 50 $File ${MC}_

#set LN = `wc -l $File | awk '{print $1}'`
set LN = 1
#echo $LN

#set NbSpFile = 0 # = $LN / 50
#@ NbSpFile = $LN / 50 + 1

#echo  $NbSpFile


foreach Line (`ls ${MC}_*`)


echo "import FWCore.ParameterSet.Config as cms" >  wEleNeuFilter${LN}_MC_cfg.py
echo "process = cms.Process("\""wNTuple"\"")"   >>  wEleNeuFilter${LN}_MC_cfg.py
echo "process.load("\"KoSMP.WAnalyzer.wAnalysis_MC_cff\"")" >>  wEleNeuFilter${LN}_MC_cfg.py
echo "" >>  wEleNeuFilter${LN}_MC_cfg.py
echo "" >>  wEleNeuFilter${LN}_MC_cfg.py
echo "process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )" >>  wEleNeuFilter${LN}_MC_cfg.py
echo "process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )" >>  wEleNeuFilter${LN}_MC_cfg.py
echo "process.MessageLogger.cerr.FwkReport.reportEvery = 1000" >>  wEleNeuFilter${LN}_MC_cfg.py
echo "" >>  wEleNeuFilter${LN}_MC_cfg.py
echo "process.source = cms.Source("\"PoolSource\"", " >>  wEleNeuFilter${LN}_MC_cfg.py
echo "    fileNames = cms.untracked.vstring(" >>  wEleNeuFilter${LN}_MC_cfg.py
echo "" >>  wEleNeuFilter${LN}_MC_cfg.py

cat $Line >>  wEleNeuFilter${LN}_MC_cfg.py

echo ")" >>  wEleNeuFilter${LN}_MC_cfg.py
echo ")" >>  wEleNeuFilter${LN}_MC_cfg.py
echo "" >>  wEleNeuFilter${LN}_MC_cfg.py
echo "" >>  wEleNeuFilter${LN}_MC_cfg.py 
echo "process.TFileService = cms.Service("\"TFileService\""," >>  wEleNeuFilter${LN}_MC_cfg.py
echo "    fileName = cms.string("\'wNTuple5.root\'")" >>  wEleNeuFilter${LN}_MC_cfg.py
echo ")" >>  wEleNeuFilter${LN}_MC_cfg.py
echo "" >>  wEleNeuFilter${LN}_MC_cfg.py
echo "process.p = cms.Path(" >>  wEleNeuFilter${LN}_MC_cfg.py
echo "    process.WEleNeuAnalysisMCSequence" >>  wEleNeuFilter${LN}_MC_cfg.py
echo ")" >>  wEleNeuFilter${LN}_MC_cfg.py
 


@ LN = $LN + 1
end




