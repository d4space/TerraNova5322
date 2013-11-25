import os
#import sys

#BaseName="WpToMuNu"
#DataFile="../RstSelection/SigYields_Muon_Nominal.root"
#CorrName="EffCorr"
#DataYieldFile="../Rst500SampleSystEffiCorrMC/AllYieldsMuonP.root"
#CorrName="RecoilCorr"
#DataYieldFile="../Rst500SampleSystRecoilCorrMC/AllYieldsMuonRecoilP.root"
#CorrName="SmearCorr"
#DataYieldFile="../Rst500SampleSystSmearMC/AllYieldsMuonP.root"
#CorrName="QCDratio"
#DataYieldFile="../Rst500SampleQCDvsSignalRatio/AllYieldsQCDratioMuonP.root"

#cmd_string = "root -l -b -q MakeCovMat.C+\(\\\"%s\\\",\\\"%s\\\",\\\"%s\\\",\\\"%s\\\"\)" %(DataFile,DataYieldFile,CorrName,BaseName)
#os.system(cmd_string)
#cmd_string = "rm *.so *.d"
#print "command %s is running" %cmd_string
#os.system(cmd_string)

#BaseName="WmToMuNu"
#DataFile="../RstSelection/SigYields_Muon_Nominal.root"
#CorrName="EffCorr"
#DataYieldFile="../Rst500SampleSystEffiCorrMC/AllYieldsMuonM.root"
#CorrName="RecoilCorr"
#DataYieldFile="../Rst500SampleSystRecoilCorrMC/AllYieldsMuonRecoilM.root"
#CorrName="SmearCorr"
#DataYieldFile="../Rst500SampleSystSmearMC/AllYieldsMuonM.root"
#CorrName="QCDratio"
#DataYieldFile="../Rst500SampleQCDvsSignalRatio/AllYieldsQCDratioMuonM.root"

#cmd_string = "root -l -b -q MakeCovMat.C+\(\\\"%s\\\",\\\"%s\\\",\\\"%s\\\",\\\"%s\\\"\)" %(DataFile,DataYieldFile,CorrName,BaseName)
#os.system(cmd_string)
#cmd_string = "rm *.so *.d"
#print "command %s is running" %cmd_string
#os.system(cmd_string)

BaseName="WpToEleNu"
DataFile="../RstSelection/SigYields_Electron_Nominal.root"
#CorrName="ScaleCorr"
#DataYieldFile="../Rst500SampleSystScaleRD/AllYieldsEleP.root"
#DataYieldFile="../Rst500SampleSystEffiCorrMC/AllYieldsEleP_QCDfloat.root"
#CorrName="SmearCorr"
#DataYieldFile="../Rst500SampleSystSmearMC/AllYieldsEleP.root"
CorrName="RecoilCorr"
DataYieldFile="../Rst500SampleSystRecoilCorrMC/AllYieldsEleP_QCDfloat.root"

cmd_string = "root -l -b -q MakeCovMat.C+\(\\\"%s\\\",\\\"%s\\\",\\\"%s\\\",\\\"%s\\\"\)" %(DataFile,DataYieldFile,CorrName,BaseName)
os.system(cmd_string)
cmd_string = "rm *.so *.d"
print "command %s is running" %cmd_string
os.system(cmd_string)

BaseName="WmToEleNu"
DataFile="../RstSelection/SigYields_Electron_Nominal.root"
#CorrName="ScaleCorr"
#DataYieldFile="../Rst500SampleSystScaleRD/AllYieldsEleM.root"
##DataYieldFile="../Rst500SampleSystEffiCorrMC/AllYieldsEleM_QCDfloat.root"
#CorrName="SmearCorr"
#DataYieldFile="../Rst500SampleSystSmearMC/AllYieldsEleM.root"
CorrName="RecoilCorr"
DataYieldFile="../Rst500SampleSystRecoilCorrMC/AllYieldsEleM_QCDfloat.root"

cmd_string = "root -l -b -q MakeCovMat.C+\(\\\"%s\\\",\\\"%s\\\",\\\"%s\\\",\\\"%s\\\"\)" %(DataFile,DataYieldFile,CorrName,BaseName)
os.system(cmd_string)
cmd_string = "rm *.so *.d"
print "command %s is running" %cmd_string
os.system(cmd_string)
