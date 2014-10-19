import os
import sys
BaseName="WpToMuNu"
cmd_string = "root -l -q theoryStudy_separate.C\(\\\"%s\\\"\)" %BaseName
os.system(cmd_string)

cmd_string = "rm -f *.d *.so"
os.system(cmd_string)

BaseName="WmToMuNu"
cmd_string = "root -l -q theoryStudy_separate.C\(\\\"%s\\\"\)" %BaseName
os.system(cmd_string)

cmd_string = "rm -f *.d *.so"
os.system(cmd_string)

BaseName="WpToEleNu"
cmd_string = "root -l -q theoryStudy_separate.C\(\\\"%s\\\"\)" %BaseName
os.system(cmd_string)

cmd_string = "rm -f *.d *.so"
os.system(cmd_string)

BaseName="WmToEleNu"
cmd_string = "root -l -q theoryStudy_separate.C\(\\\"%s\\\"\)" %BaseName
os.system(cmd_string)

cmd_string = "rm -f *.d *.so"
os.system(cmd_string)
