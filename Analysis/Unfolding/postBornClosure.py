import os
#import sys
AcceptFile="../WPtAcceptance/Muon2012LoPU/WpToMuNu_S8.root"
BaseName="WpToMuNu"
#BaseName="WpToEleNu"
cmd_string = "root -l -q postBornClosure.C+\(\\\"%s\\\",\\\"%s\\\"\)" %(AcceptFile,BaseName)
os.system(cmd_string)

