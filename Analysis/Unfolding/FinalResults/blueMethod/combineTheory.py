import os
import sys
BaseName="Wmuon"
cmd_string = "root -l -q combineTheory.C\(\\\"%s\\\"\)" %BaseName
os.system(cmd_string)
cmd_string = "rm -f *.d *.so"
os.system(cmd_string)

BaseName="Wele"
cmd_string = "root -l -q combineTheory.C\(\\\"%s\\\"\)" %BaseName
os.system(cmd_string)
cmd_string = "rm -f *.d *.so"
os.system(cmd_string)
