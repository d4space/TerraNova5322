import os
#import sys

#BaseName="WpToMuNu"
#UnfoldFile="Muon2012LoPU/WpToMuNu_S8_Unfold.root"
#AcceptFile="../WPtAcceptance/Muon2012LoPU/WpToMuNu_S8.root"
##DataFile="../RstSelection/SigYields_Muon_Nominal.root"
#DataFile="../MetFit4Wpt/MuonFitResultsModRayleighSimultNominal/RstMuon/SigYields_Nominal.root"
#
#cmd_string = "root -l -b -q wPtUnfoldStudy.C+\(\\\"%s\\\",\\\"%s\\\",\\\"%s\\\",\\\"%s\\\"\)" %(UnfoldFile,AcceptFile,DataFile,BaseName)
#os.system(cmd_string)
#cmd_string = "rm *.so *.d"
#print "command %s is running" %cmd_string
#os.system(cmd_string)
#
#BaseName="WmToMuNu"
#UnfoldFile="Muon2012LoPU/WmToMuNu_S8_Unfold.root"
#AcceptFile="../WPtAcceptance/Muon2012LoPU/WmToMuNu_S8.root"
##DataFile="../RstSelection/SigYields_Muon_Nominal.root"
#DataFile="../MetFit4Wpt/MuonFitResultsModRayleighSimultNominal/RstMuon/SigYields_Nominal.root"
#
#cmd_string = "root -l -b -q wPtUnfoldStudy.C+\(\\\"%s\\\",\\\"%s\\\",\\\"%s\\\",\\\"%s\\\"\)" %(UnfoldFile,AcceptFile,DataFile,BaseName)
#os.system(cmd_string)
#cmd_string = "rm *.so *.d"
#print "command %s is running" %cmd_string
#os.system(cmd_string)

BaseName="WpToEleNu"
UnfoldFile="Electron2012LoPU/WpToEleNu_S8_Unfold.root"
AcceptFile="../WPtAcceptance/Electron2012LoPU/WpToEleNu_S8.root"
DataFile="../RstSelection/SigYields_Electron_Nominal.root"

cmd_string = "root -l -b -q wPtUnfoldStudy.C+\(\\\"%s\\\",\\\"%s\\\",\\\"%s\\\",\\\"%s\\\"\)" %(UnfoldFile,AcceptFile,DataFile,BaseName)
os.system(cmd_string)
cmd_string = "rm *.so *.d"
print "command %s is running" %cmd_string
os.system(cmd_string)

BaseName="WmToEleNu"
UnfoldFile="Electron2012LoPU/WmToEleNu_S8_Unfold.root"
AcceptFile="../WPtAcceptance/Electron2012LoPU/WmToEleNu_S8.root"
DataFile="../RstSelection/SigYields_Electron_Nominal.root"

cmd_string = "root -l -b -q wPtUnfoldStudy.C+\(\\\"%s\\\",\\\"%s\\\",\\\"%s\\\",\\\"%s\\\"\)" %(UnfoldFile,AcceptFile,DataFile,BaseName)
os.system(cmd_string)
cmd_string = "rm *.so *.d"
print "command %s is running" %cmd_string
os.system(cmd_string)
