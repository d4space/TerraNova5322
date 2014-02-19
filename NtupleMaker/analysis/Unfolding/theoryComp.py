import os
#import sys
BaseName="WpToMuNu"
cmd_string = "root -l -q theoryComp.C+\(\\\"%s\\\"\)" %(BaseName)
os.system(cmd_string)

