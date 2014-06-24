import os
import sys

BaseName="WInclToMuNu"
cmd_string = "root -l -q theoryStudy_separate.C\(\\\"%s\\\"\)" %BaseName
os.system(cmd_string)
cmd_string = "rm -f *.d *.so"
os.system(cmd_string)

BaseName="WInclToEleNu"
cmd_string = "root -l -q theoryStudy_separate.C\(\\\"%s\\\"\)" %BaseName
os.system(cmd_string)
cmd_string = "rm -f *.d *.so"
os.system(cmd_string)
