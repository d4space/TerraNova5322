import os
#import sys

cmd_string = "rm -f *.d *.so"
os.system(cmd_string)

BaseName="WpToMuNu"
VarName="lep_pt"
cmd_string = "root -l -b -q WPtCorrPostFSRCalc.C+\(\\\"%s\\\"\)" %(BaseName)
os.system(cmd_string)
cmd_string = "rm -f *.d *.so"
os.system(cmd_string)

