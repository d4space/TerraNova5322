import os
#import sys
#BaseName="WpToEleNu"
cmd_string = "root -l -q effStudy.C+\(\)"
#cmd_string = "root -l -q wPtUnfoldStudy.C+\(\\\"%s\\\",\\\"%s\\\"\)" %(InFile,BaseName)
os.system(cmd_string)

