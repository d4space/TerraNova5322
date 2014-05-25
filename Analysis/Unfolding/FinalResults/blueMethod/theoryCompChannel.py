import os
import sys
cmd_string = "root -l -q theoryCompChannel.C"
os.system(cmd_string)

cmd_string = "rm -f *.d *.so"
os.system(cmd_string)
