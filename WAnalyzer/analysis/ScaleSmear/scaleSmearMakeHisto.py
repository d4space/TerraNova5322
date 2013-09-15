import os
#import sys
#Range Ele(0,,,5) Muon(0,,,4)
Range = 0
# -q (quit after execute)
cmd_string = "root -l -q scaleSmearMakeHisto.C+\(\%d\)" %(Range)
#cmd_string = "root -l -q wPtResolStudy.C+\(\%d\)" %(InFile)
#cmd_string = "root -l -q wPtResolStudy.C+\(\\%d\\,\\\"%s\\\"\)" %(InFile,BaseName)
print cmd_string
os.system(cmd_string)
