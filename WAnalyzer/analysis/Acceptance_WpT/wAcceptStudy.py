import os
#import sys
#InFile="MuonLowPU/Muon_WpToMuNu_S8_Acceptance.root"
#InFile="MuonLowPU/Muon_WmToMuNu_S8_Acceptance.root"
InFile="ElectronLowPU/Ele_WpToEleNu_S8_Acceptance.root"
BaseName="ResultWpToEleNu"
#BaseName="WpToMuNu"
cmd_string = "root -l -q wAcceptStudy.C+\(\\\"%s\\\",\\\"%s\\\"\)" %(InFile,BaseName)
os.system(cmd_string)

