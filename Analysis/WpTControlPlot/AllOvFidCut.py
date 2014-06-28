import os
#import sys

cmd_string = "rm -f *.d *.so"
os.system(cmd_string)

BaseName="WpToMuNu"
VarName="lep_pt"
#VarName="lep_eta"
cmd_string = "root -l -b -q AllOvFidCut.C+\(\\\"%s\\\",\\\"%s\\\"\)" %(BaseName,VarName)
os.system(cmd_string)
cmd_string = "rm -f *.d *.so"
os.system(cmd_string)

#BaseName="WmToMuNu"
#VarName="lep_pt"
#VarName="lep_eta"
#cmd_string = "root -l -b -q AllOvFidCut.C+\(\\\"%s\\\",\\\"%s\\\"\)" %(BaseName,VarName)
#os.system(cmd_string)
#cmd_string = "rm -f *.d *.so"
#os.system(cmd_string)

