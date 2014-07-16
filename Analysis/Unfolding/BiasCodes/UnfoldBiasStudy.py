import os
#import sys
idx=0
BaseName="WpToMuNu"
UnfoldFile="MuonLowPU/Muon_WpToMuNu_S8_Unfold.root"
AcceptFile="../Acceptance_WpT/MuonLowPU/Muon_WpToMuNu_S8_Acceptance.root"
DataFile="../RstSelection/SigYields_Muon_Nominal.root"
#DataFile="../MetFit4Wpt/MuonFitResultsRayleighGausSimultNominal/RstMuon/SigYields_Nominal.root"

cmd_string = "root -l -b -q UnfoldBiasStudy.C+\(\\\"%s\\\",\\\"%s\\\",\\\"%s\\\",\\\"%s\\\",%d\)" %(UnfoldFile,AcceptFile,DataFile,BaseName,idx)
os.system(cmd_string)
cmd_string = "rm *.so *.d"
print "command %s is running" %cmd_string
os.system(cmd_string)

#BaseName="WpToEleNu"
#UnfoldFile="ElectronLowPU/Ele_WpToEleNu_S8_Unfold.root"
#AcceptFile="../Acceptance_WpT/ElectronLowPU/Ele_WpToEleNu_S8_Acceptance.root"
#DataFile="../RstSelection/SigYields_Electron_Nominal.root"
##DataFile="../MetFit4Wpt/ElectronFitResultsRayleighGausSimultNominal/RstElectron/SigYields_Nominal.root"
#
#cmd_string = "root -l -b -q UnfoldBiasStudy.C+\(\\\"%s\\\",\\\"%s\\\",\\\"%s\\\",\\\"%s\\\",%d\)" %(UnfoldFile,AcceptFile,DataFile,BaseName,idx)
#os.system(cmd_string)
#cmd_string = "rm *.so *.d"
#print "command %s is running" %cmd_string
#os.system(cmd_string)
#
#BaseName="WmToMuNu"
#UnfoldFile="MuonLowPU/Muon_WmToMuNu_S8_Unfold.root"
#AcceptFile="../Acceptance_WpT/MuonLowPU/Muon_WmToMuNu_S8_Acceptance.root"
#DataFile="../RstSelection/SigYields_Muon_Nominal.root"
##DataFile="../MetFit4Wpt/MuonFitResultsRayleighGausSimultNominal/RstMuon/SigYields_Nominal.root"
#
#cmd_string = "root -l -b -q UnfoldBiasStudy.C+\(\\\"%s\\\",\\\"%s\\\",\\\"%s\\\",\\\"%s\\\",%d\)" %(UnfoldFile,AcceptFile,DataFile,BaseName,idx)
#os.system(cmd_string)
#cmd_string = "rm *.so *.d"
#print "command %s is running" %cmd_string
#os.system(cmd_string)
#
#BaseName="WmToEleNu"
#UnfoldFile="ElectronLowPU/Ele_WmToEleNu_S8_Unfold.root"
#AcceptFile="../Acceptance_WpT/ElectronLowPU/Ele_WmToEleNu_S8_Acceptance.root"
#DataFile="../RstSelection/SigYields_Electron_Nominal.root"
##DataFile="../MetFit4Wpt/ElectronFitResultsRayleighGausSimultNominal/RstElectron/SigYields_Nominal.root"
#
#cmd_string = "root -l -b -q UnfoldBiasStudy.C+\(\\\"%s\\\",\\\"%s\\\",\\\"%s\\\",\\\"%s\\\",%d\)" %(UnfoldFile,AcceptFile,DataFile,BaseName,idx)
#os.system(cmd_string)
#cmd_string = "rm *.so *.d"
#print "command %s is running" %cmd_string
#os.system(cmd_string)
