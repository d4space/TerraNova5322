import os

BaseName="WpToMuNu"
unfName="Det"
cmd_string = "root -l -q WptCorrRatioFit.C+\(\\\"%s\\\",\\\"%s\\\"\)" %(BaseName,unfName)
os.system(cmd_string)
cmd_string = "rm *.so *.d"
print "command %s is running" %cmd_string
os.system(cmd_string)

#BaseName="WpToMuNu"
#unfName="FSR"
#cmd_string = "root -l -q test.C+\(\\\"%s\\\",\\\"%s\\\"\)" %(BaseName,unfName)
#os.system(cmd_string)
#cmd_string = "rm *.so *.d"
#print "command %s is running" %cmd_string
#os.system(cmd_string)
#
#BaseName="WmToMuNu"
#unfName="Det"
#cmd_string = "root -l -q test.C+\(\\\"%s\\\",\\\"%s\\\"\)" %(BaseName,unfName)
#os.system(cmd_string)
#cmd_string = "rm *.so *.d"
#print "command %s is running" %cmd_string
#os.system(cmd_string)
#
#BaseName="WmToMuNu"
#unfName="FSR"
#cmd_string = "root -l -q test.C+\(\\\"%s\\\",\\\"%s\\\"\)" %(BaseName,unfName)
#os.system(cmd_string)
#cmd_string = "rm *.so *.d"
#print "command %s is running" %cmd_string
#os.system(cmd_string)
#
#BaseName="WpToEleNu"
#unfName="Det"
#cmd_string = "root -l -q test.C+\(\\\"%s\\\",\\\"%s\\\"\)" %(BaseName,unfName)
#os.system(cmd_string)
#cmd_string = "rm *.so *.d"
#print "command %s is running" %cmd_string
#os.system(cmd_string)
#
#BaseName="WpToEleNu"
#unfName="FSR"
#cmd_string = "root -l -q test.C+\(\\\"%s\\\",\\\"%s\\\"\)" %(BaseName,unfName)
#os.system(cmd_string)
#cmd_string = "rm *.so *.d"
#print "command %s is running" %cmd_string
#os.system(cmd_string)
#
#BaseName="WmToEleNu"
#unfName="Det"
#cmd_string = "root -l -q test.C+\(\\\"%s\\\",\\\"%s\\\"\)" %(BaseName,unfName)
#os.system(cmd_string)
#cmd_string = "rm *.so *.d"
#print "command %s is running" %cmd_string
#os.system(cmd_string)
#
#BaseName="WmToEleNu"
#unfName="FSR"
#cmd_string = "root -l -q test.C+\(\\\"%s\\\",\\\"%s\\\"\)" %(BaseName,unfName)
#os.system(cmd_string)
#cmd_string = "rm *.so *.d"
#print "command %s is running" %cmd_string
#os.system(cmd_string)
