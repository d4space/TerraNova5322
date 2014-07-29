import os
#import sys

#RDFile="ElectronLowPU/Ele_RD_LowPU_ScaleMakeRD_Eta_0.root"
#MCFile="ElectronLowPU/Ele_DYToEE_S8_ScaleMakeMC_Eta_0.root"

RDFile="/Electron2012LoPU/Ele_RD_LowPU.root"
MCFile="/Electron2012LoPU/Ele_DYToEE_S8.root"
BaseName="Ele_Eta"
cmd_string = "root -l -q scaleSmearTemplateFit_Ele.C+\(\\\"%s\\\",\\\"%s\\\",\\\"%s\\\"\)" %(RDFile,MCFile,BaseName)
os.system(cmd_string)

