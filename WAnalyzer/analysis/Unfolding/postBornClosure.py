import os
#import sys
AcceptFile="../Acceptance_WpT/MuonLowPU/Muon_WpToMuNu_S8_Acceptance.root"
BaseName="WpToMuNu"
#BaseName="WpToEleNu"
cmd_string = "root -l -q postBornClosure.C+\(\\\"%s\\\",\\\"%s\\\"\)" %(AcceptFile,BaseName)
os.system(cmd_string)

