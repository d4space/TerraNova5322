import os

unfName="Det"

BaseName="WpToMuNu"
cmd_string = "root -l -q test.C+\(\\\"%s\\\",\\\"%s\\\"\)" %(BaseName,unfName)
os.system(cmd_string)
cmd_string = "rm *.so *.d"
print "command %s is running" %cmd_string
os.system(cmd_string)

BaseName="WmToMuNu"
cmd_string = "root -l -q test.C+\(\\\"%s\\\",\\\"%s\\\"\)" %(BaseName,unfName)
os.system(cmd_string)
cmd_string = "rm *.so *.d"
print "command %s is running" %cmd_string
os.system(cmd_string)

BaseName="WpToEleNu"
cmd_string = "root -l -q test.C+\(\\\"%s\\\",\\\"%s\\\"\)" %(BaseName,unfName)
os.system(cmd_string)
cmd_string = "rm *.so *.d"
print "command %s is running" %cmd_string
os.system(cmd_string)

BaseName="WmToEleNu"
cmd_string = "root -l -q test.C+\(\\\"%s\\\",\\\"%s\\\"\)" %(BaseName,unfName)
os.system(cmd_string)
cmd_string = "rm *.so *.d"
print "command %s is running" %cmd_string
os.system(cmd_string)

#unfName="FSR"
#
#BaseName="WpToMuNu"
#cmd_string = "root -l -q test.C+\(\\\"%s\\\",\\\"%s\\\"\)" %(BaseName,unfName)
#os.system(cmd_string)
#cmd_string = "rm *.so *.d"
#print "command %s is running" %cmd_string
#os.system(cmd_string)
#
#BaseName="WmToMuNu"
#cmd_string = "root -l -q test.C+\(\\\"%s\\\",\\\"%s\\\"\)" %(BaseName,unfName)
#os.system(cmd_string)
#cmd_string = "rm *.so *.d"
#print "command %s is running" %cmd_string
#os.system(cmd_string)
#
#BaseName="WpToEleNu"
#cmd_string = "root -l -q test.C+\(\\\"%s\\\",\\\"%s\\\"\)" %(BaseName,unfName)
#os.system(cmd_string)
#cmd_string = "rm *.so *.d"
#print "command %s is running" %cmd_string
#os.system(cmd_string)
#
#BaseName="WmToEleNu"
#cmd_string = "root -l -q test.C+\(\\\"%s\\\",\\\"%s\\\"\)" %(BaseName,unfName)
#os.system(cmd_string)
#cmd_string = "rm *.so *.d"
#print "command %s is running" %cmd_string
#os.system(cmd_string)
