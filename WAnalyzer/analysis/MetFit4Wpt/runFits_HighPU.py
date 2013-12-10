import os
import glob
import subprocess
import sys
HFLUMI =0.018729
PIXLUMI=0.018479
WPTLUMI=0.018977
LUMI=WPTLUMI
ETALUMI=19.619
LUMIETA=ETALUMI

if (len(sys.argv) !=2):
  print "Usage: python %s Muon(Electron)Conv(RayleighHPU)Simult(Separate)" %sys.argv[1]
  sys.exit(0)
args = sys.argv[1:]
if (sys.argv[0] == "python"): args =sys.argv[2:]
scenario = "Electron"
if len(args) > 0: scenario = args[0]
print "Will run fit for ", scenario 
if "ElectronRayleighHPU" in scenario and "Simult" in scenario:
  print "Electron - MET fitting: Simultaneously Fit with Rayleigh function"
  cmd_string = "root -l -q fitWEleMetRayleighSimultHighPU.C+\(\\\"ElectronFitResultsRayleighSimultHighPU\\\",%f,0\)" %LUMIETA
print "command is "+cmd_string
os.system(cmd_string)
cmd_string = "rm *.so *.d"
print "command %s is running" %cmd_string
os.system(cmd_string)
