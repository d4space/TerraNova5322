import os
#import sys
RDFile="MuonLowPU/Muon_RD_LowPU_ScaleMakeRD_Eta_0.root"
MCFile="MuonLowPU/Muon_DYToMuMu_S8_ScaleMakeMC_Eta_0.root"
BaseName="Muon_Eta"

cmd_string = "root -l -q scaleSmearTemplateFit_Muon.C+\(\\\"%s\\\",\\\"%s\\\",\\\"%s\\\"\)" %(RDFile,MCFile,BaseName)
os.system(cmd_string)

