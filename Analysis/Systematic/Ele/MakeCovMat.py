import os
#import sys

#======Choose the CorrName===============
#CorrName="EffCorr"
#CorrName="ScaleCorr"
#CorrName="SmearCorr"
#CorrName="RecoilCorr"
#CorrName="dUnf"
#CorrName="PostEffCorr"
CorrName="FSRUnf"
#CorrName="BornEffCorr"

#=======Make W+ Signal root file===========
cmd_string = "root -l -b -q pRead_Yield.C+\(\\\"%s\\\"\)" %(CorrName)
os.system(cmd_string)
cmd_string = "rm *.so *.d"
print "command %s is running" %cmd_string
os.system(cmd_string)

#========W+ Covariance matrix===============
BaseName="WpToEleNu"
#Recon.Stage
if CorrName=="EffCorr" or CorrName=="ScaleCorr" or CorrName=="SmearCorr" or CorrName=="RecoilCorr":
  DataFile="/d2/scratch/khakim/WAnalysis/InclWZ_FinalEffSF/KoSMP/WAnalyzer/analysis/RstSelection/SigYields_Electron_Nominal.root"
  DataYieldFile="pRecon.root"
#Unf.Stage
if CorrName=="dUnf" or CorrName=="PostEffCorr" or CorrName=="FSRUnf" or CorrName=="BornEffCorr":
  DataFile="/d2/scratch/khakim/WAnalysis/InclWZ_FinalEffSF/KoSMP/WAnalyzer/analysis/Unfolding/ResultWpToEleNu/Result_WpToEleNu.root"

if CorrName=="dUnf":
  DataYieldFile="pDetUnf.root"
elif CorrName=="PostEffCorr":
  DataYieldFile="pPostEffCorr.root"
elif CorrName=="FSRUnf":
  DataYieldFile="pFSRUnf.root"
elif CorrName=="BornEffCorr":
  DataYieldFile="pBornEffCorr.root"

cmd_string = "root -l -b -q MakeCovMat.C+\(\\\"%s\\\",\\\"%s\\\",\\\"%s\\\",\\\"%s\\\"\)" %(DataFile,DataYieldFile,CorrName,BaseName)
os.system(cmd_string)
cmd_string = "rm *.so *.d"
print "command %s is running" %cmd_string
os.system(cmd_string)

#=======Make W- Signal root file===========
cmd_string = "root -l -b -q mRead_Yield.C+\(\\\"%s\\\"\)" %(CorrName)
os.system(cmd_string)
cmd_string = "rm *.so *.d"
print "command %s is running" %cmd_string
os.system(cmd_string)

#========W- Covariance matrix===============
BaseName="WmToEleNu"
#Recon.Stage
if CorrName=="EffCorr" or CorrName=="ScaleCorr" or CorrName=="SmearCorr" or CorrName=="RecoilCorr":
  DataFile="/d2/scratch/khakim/WAnalysis/InclWZ_FinalEffSF/KoSMP/WAnalyzer/analysis/RstSelection/SigYields_Electron_Nominal.root"
  DataYieldFile="mRecon.root"
#Unf.Stage
if CorrName=="dUnf" or CorrName=="PostEffCorr" or CorrName=="FSRUnf" or CorrName=="BornEffCorr":
  DataFile="/d2/scratch/khakim/WAnalysis/InclWZ_FinalEffSF/KoSMP/WAnalyzer/analysis/Unfolding/ResultWmToEleNu/Result_WmToEleNu.root"

if CorrName=="dUnf":
  DataYieldFile="mDetUnf.root"
elif CorrName=="PostEffCorr":
  DataYieldFile="mPostEffCorr.root"
elif CorrName=="FSRUnf":
  DataYieldFile="mFSRUnf.root"
elif CorrName=="BornEffCorr":
  DataYieldFile="mBornEffCorr.root"

cmd_string = "root -l -b -q MakeCovMat.C+\(\\\"%s\\\",\\\"%s\\\",\\\"%s\\\",\\\"%s\\\"\)" %(DataFile,DataYieldFile,CorrName,BaseName)
os.system(cmd_string)
cmd_string = "rm *.so *.d"
print "command %s is running" %cmd_string
os.system(cmd_string)
