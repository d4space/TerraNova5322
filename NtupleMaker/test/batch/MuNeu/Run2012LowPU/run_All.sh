#!/bin/sh -f
echo " Submitting wNTuple making qsub jobs for DYToMuMu ... "
qsub -q cms ./DYToMuMu/run_cfg_DYMuMu_part1.sh
qsub -q cms ./DYToMuMu/run_cfg_DYMuMu_part2.sh
qsub -q cms ./DYToMuMu/run_cfg_DYMuMu_part3.sh
qsub -q cms ./DYToMuMu/run_cfg_DYMuMu_part4.sh
qsub -q cms ./DYToMuMu/run_cfg_DYMuMu_part5.sh
echo " DYToMuMu wNTuple making qsub jobs submitted "
echo " *************************************************** "
echo " Submitting wNTuple making qsub jobs for DYToTauTau ... "
qsub -q cms ./DYToTauTau/run_cfg_DYToTauTau_part1.sh
qsub -q cms ./DYToTauTau/run_cfg_DYToTauTau_part2.sh
qsub -q cms ./DYToTauTau/run_cfg_DYToTauTau_part3.sh
echo " DYToTauTau wNTuple making qsub jobs submitted "
echo " *************************************************** "
echo " Submitting wNTuple making qsub jobs for WminusToMuNu ... "
qsub -q cms ./WminusToMuNu/run_cfg_WmMuNu_part1.sh
qsub -q cms ./WminusToMuNu/run_cfg_WmMuNu_part2.sh
qsub -q cms ./WminusToMuNu/run_cfg_WmMuNu_part3.sh
qsub -q cms ./WminusToMuNu/run_cfg_WmMuNu_part4.sh
qsub -q cms ./WminusToMuNu/run_cfg_WmMuNu_part5.sh
qsub -q cms ./WminusToMuNu/run_cfg_WmMuNu_part6.sh
echo " WminusToMuNu wNTuple making qsub jobs submitted "
echo " *************************************************** "
echo " Submitting wNTuple making qsub jobs for WplusToMuNu ... "
qsub -q cms ./WplusToMuNu/run_cfg_WpMuNu_part1.sh
qsub -q cms ./WplusToMuNu/run_cfg_WpMuNu_part2.sh
qsub -q cms ./WplusToMuNu/run_cfg_WpMuNu_part3.sh
qsub -q cms ./WplusToMuNu/run_cfg_WpMuNu_part4.sh
echo " WplusToMuNu wNTuple making qsub jobs submitted "
echo " *************************************************** "
echo " Submitting wNTuple making qsub jobs for WToTauNu ... "
qsub -q cms ./WToTauNu/run_cfg_WToTauNu_part1.sh
qsub -q cms ./WToTauNu/run_cfg_WToTauNu_part2.sh
qsub -q cms ./WToTauNu/run_cfg_WToTauNu_part3.sh
qsub -q cms ./WToTauNu/run_cfg_WToTauNu_part4.sh
echo " WToTauNu wNTuple making qsub jobs submitted "
echo " *************************************************** "
echo " Submitting wNTuple making qsub jobs for SingleMuPrompt..."
qsub -q cms ./SingleMuPrompt/run_cfg_Prompt_part1.sh
qsub -q cms ./SingleMuPrompt/run_cfg_Prompt_part2.sh
qsub -q cms ./SingleMuPrompt/run_cfg_Prompt_part3.sh
echo " SingleMuPrompt wNTuple making qsub jobs submitted "
echo " *************************************************** "
echo " Submitting wNTuple making qsub jobs for SingleMuReReco..."
qsub -q cms ./SingleMuReReco/run_cfg_ReReco_part1.sh
qsub -q cms ./SingleMuReReco/run_cfg_ReReco_part2.sh
qsub -q cms ./SingleMuReReco/run_cfg_ReReco_part3.sh
echo " SingleMuReReco wNTuple making qsub jobs submitted "
echo " *************************************************** "
echo " Submitting wNTuple making qsub jobs for TTJets..."
qsub -q cms ./TTJets/run_cfg_TTJets_part1.sh
qsub -q cms ./TTJets/run_cfg_TTJets_part2.sh
qsub -q cms ./TTJets/run_cfg_TTJets_part3.sh
qsub -q cms ./TTJets/run_cfg_TTJets_part4.sh
qsub -q cms ./TTJets/run_cfg_TTJets_part5.sh
qsub -q cms ./TTJets/run_cfg_TTJets_part6.sh
qsub -q cms ./TTJets/run_cfg_TTJets_part7.sh
qsub -q cms ./TTJets/run_cfg_TTJets_part8.sh
qsub -q cms ./TTJets/run_cfg_TTJets_part9.sh
qsub -q cms ./TTJets/run_cfg_TTJets_part10.sh
echo " TTJets wNTuple making qsub jobs submitted "
echo " *************************************************** "
echo " All Jobs are submitted. Use command to check status of each jobs: # qstat -r JobID"
