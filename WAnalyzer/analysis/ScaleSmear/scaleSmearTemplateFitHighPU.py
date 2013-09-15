import os
#import sys

RDFile="ElectronHighPU/Ele_RD_HighPU_ScaleMakeRD_Eta_0.root"
MCFile="ElectronHighPU/Ele_DYToEE_S10_ScaleMakeMC_Eta_0.root"
BaseName="Ele_Eta"
cmd_string = "root -l -q scaleSmearTemplateFitHighPU.C+\(\\\"%s\\\",\\\"%s\\\",\\\"%s\\\"\)" %(RDFile,MCFile,BaseName)
os.system(cmd_string)

