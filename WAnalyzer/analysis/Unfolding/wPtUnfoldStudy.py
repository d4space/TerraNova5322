import os
#import sys

BaseName="WpToMuNu"
UnfoldFile="MuonLowPU/Muon_WpToMuNu_S8_Unfold.root"
AcceptFile="../Acceptance_WpT/MuonLowPU/Muon_WpToMuNu_S8_Acceptance.root"
DataFile="../RstSelection/SigYields_Muon_Nominal.root"
#DataYieldFile="../Rst500SampleSystEffiCorrMC/AllYieldsMuonP_QCDfloat.root"
DataYieldFile="../Rst500SampleSystRecoilCorrMC/AllYieldsMuonRecoilP.root"
##DataYieldFile="../Rst500SampleSystSmearMC/AllYieldsMuonP.root"
##DataYieldFile="../Rst500SampleQCDvsSignalRatio/AllYieldsQCDratioMuonP.root"
#DataYieldFile="/home/kbutanov/WAnalysis/Checking/KoSMP/WAnalyzer/analysis/SystBatchJobs/EffSyst/FitResult/pMergedEff.root"
#DataYieldFile="/home/kbutanov/WAnalysis/Checking/KoSMP/WAnalyzer/analysis/SystBatchJobs/RecoilSyst/FitResult/pMergedRecoil.root"
#DataYieldFile="/home/kbutanov/WAnalysis/Checking/KoSMP/WAnalyzer/analysis/SystBatchJobs/SmearSyst/FitResult/pMergedSmear.root"
#DataYieldFile="/home/kbutanov/WAnalysis/Checking/KoSMP/WAnalyzer/analysis/SystBatchJobs/RatioSyst/FitResult/pMergedRatio.root"

cmd_string = "root -l -b -q wPtUnfoldStudy.C+\(\\\"%s\\\",\\\"%s\\\",\\\"%s\\\",\\\"%s\\\",\\\"%s\\\"\)" %(UnfoldFile,AcceptFile,DataFile,DataYieldFile,BaseName)
os.system(cmd_string)
cmd_string = "rm *.so *.d"
print "command %s is running" %cmd_string
os.system(cmd_string)

###BaseName="WmToMuNu"
###UnfoldFile="MuonLowPU/Muon_WmToMuNu_S8_Unfold.root"
###AcceptFile="../Acceptance_WpT/MuonLowPU/Muon_WmToMuNu_S8_Acceptance.root"
###DataFile="../RstSelection/SigYields_Muon_Nominal.root"
####DataYieldFile="../Rst500SampleSystEffiCorrMC/AllYieldsMuonM_QCDfloat.root"
###DataYieldFile="../Rst500SampleSystRecoilCorrMC/AllYieldsMuonRecoilM.root"
#####DataYieldFile="../Rst500SampleSystSmearMC/AllYieldsMuonM.root"
####DataYieldFile="../Rst500SampleQCDvsSignalRatio/AllYieldsQCDratioMuonM.root"
####DataYieldFile="/home/kbutanov/WAnalysis/Checking/KoSMP/WAnalyzer/analysis/SystBatchJobs/EffSyst/FitResult/mMergedEff.root"
####DataYieldFile="/home/kbutanov/WAnalysis/Checking/KoSMP/WAnalyzer/analysis/SystBatchJobs/RecoilSyst/FitResult/mMergedRecoil.root"
####DataYieldFile="/home/kbutanov/WAnalysis/Checking/KoSMP/WAnalyzer/analysis/SystBatchJobs/SmearSyst/FitResult/mMergedSmear.root"
####DataYieldFile="/home/kbutanov/WAnalysis/Checking/KoSMP/WAnalyzer/analysis/SystBatchJobs/RatioSyst/FitResult/mMergedRatio.root"
###
###cmd_string = "root -l -b -q wPtUnfoldStudy.C+\(\\\"%s\\\",\\\"%s\\\",\\\"%s\\\",\\\"%s\\\",\\\"%s\\\"\)" %(UnfoldFile,AcceptFile,DataFile,DataYieldFile,BaseName)
###os.system(cmd_string)
###cmd_string = "rm *.so *.d"
###print "command %s is running" %cmd_string
###os.system(cmd_string)
###
###BaseName="WpToEleNu"
###UnfoldFile="ElectronLowPU/Ele_WpToEleNu_S8_Unfold.root"
###AcceptFile="../Acceptance_WpT/ElectronLowPU/Ele_WpToEleNu_S8_Acceptance.root"
###DataFile="../RstSelection/SigYields_Electron_Nominal.root"
###DataYieldFile="../Rst500SampleSystScaleRD/AllYieldsEleP.root"
####DataYieldFile="../Rst500SampleSystEffiCorrMC/AllYieldsEleP_QCDfloat.root"
#####DataYieldFile="../Rst500SampleSystSmearMC/AllYieldsEleP.root"
#####DataYieldFile="../Rst500SampleSystRecoilCorrMC/AllYieldsEleP_QCDfloat.root"
###
###cmd_string = "root -l -b -q wPtUnfoldStudy.C+\(\\\"%s\\\",\\\"%s\\\",\\\"%s\\\",\\\"%s\\\",\\\"%s\\\"\)" %(UnfoldFile,AcceptFile,DataFile,DataYieldFile,BaseName)
###os.system(cmd_string)
###cmd_string = "rm *.so *.d"
###print "command %s is running" %cmd_string
###os.system(cmd_string)
###
###BaseName="WmToEleNu"
###UnfoldFile="ElectronLowPU/Ele_WmToEleNu_S8_Unfold.root"
###AcceptFile="../Acceptance_WpT/ElectronLowPU/Ele_WmToEleNu_S8_Acceptance.root"
###DataFile="../RstSelection/SigYields_Electron_Nominal.root"
###DataYieldFile="../Rst500SampleSystScaleRD/AllYieldsEleM.root"
#####DataYieldFile="../Rst500SampleSystEffiCorrMC/AllYieldsEleM_QCDfloat.root"
#####DataYieldFile="../Rst500SampleSystSmearMC/AllYieldsEleM.root"
#####DataYieldFile="../Rst500SampleSystRecoilCorrMC/AllYieldsEleM_QCDfloat.root"
###
###cmd_string = "root -l -b -q wPtUnfoldStudy.C+\(\\\"%s\\\",\\\"%s\\\",\\\"%s\\\",\\\"%s\\\",\\\"%s\\\"\)" %(UnfoldFile,AcceptFile,DataFile,DataYieldFile,BaseName)
###os.system(cmd_string)
###cmd_string = "rm *.so *.d"
###print "command %s is running" %cmd_string
###os.system(cmd_string)
