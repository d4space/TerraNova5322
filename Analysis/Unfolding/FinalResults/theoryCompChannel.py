import os
import sys
BaseName="Wplus"
cmd_string = "root -l -q theoryCompChannel.C\(\\\"%s\\\"\)" %BaseName
os.system(cmd_string)

cmd_string = "rm -f *.d *.so"
os.system(cmd_string)

BaseName="Wminus"
cmd_string = "root -l -q theoryCompChannel.C\(\\\"%s\\\"\)" %BaseName
os.system(cmd_string)

cmd_string = "rm -f *.d *.so"
os.system(cmd_string)
