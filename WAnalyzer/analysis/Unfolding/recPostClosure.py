import os
#import sys
#UnfoldFile="MuonLowPU/Muon_WpToMuNu_S8_Unfold.root"
#AcceptFile="../Acceptance_WpT/MuonLowPU/Muon_WpToMuNu_S8_Acceptance.root"
#BaseName="WpToMuNu"
UnfoldFile="ElectronLowPU/Ele_WpToEleNu_S8_Unfold.root"
AcceptFile="../Acceptance_WpT/ElectronLowPU/Ele_WpToEleNu_S8_Acceptance.root"
BaseName="WpToEleNu"
cmd_string = "root -l -q recPostClosure.C+\(\\\"%s\\\",\\\"%s\\\",\\\"%s\\\"\)" %(UnfoldFile,AcceptFile,BaseName)
os.system(cmd_string)

