import os
#import sys
UnfoldFile="Muon2012LoPU/WpToMuNu_S8_Unfold.root"
AcceptFile="../WPtAcceptance/Muon2012LoPU/WpToMuNu_S8.root"
BaseName="WpToMuNu"
cmd_string = "root -l -q recPostClosure.C+\(\\\"%s\\\",\\\"%s\\\",\\\"%s\\\"\)" %(UnfoldFile,AcceptFile,BaseName)
os.system(cmd_string)
cmd_string = "rm *.so *.d"
print "command %s is running" %cmd_string
os.system(cmd_string)
UnfoldFile="Electron2012LoPU/WpToEleNu_S8_Unfold.root"
AcceptFile="../WPtAcceptance/Electron2012LoPU/WpToEleNu_S8.root"
BaseName="WpToEleNu"
cmd_string = "root -l -q recPostClosure.C+\(\\\"%s\\\",\\\"%s\\\",\\\"%s\\\"\)" %(UnfoldFile,AcceptFile,BaseName)
os.system(cmd_string)

cmd_string = "rm *.so *.d"
print "command %s is running" %cmd_string
os.system(cmd_string)
