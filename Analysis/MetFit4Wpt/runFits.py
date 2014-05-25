import os
import glob
import subprocess
import sys
HFLUMI =0.018729
PIXLUMI=0.018479
WPTLUMI=0.018977
LUMI=WPTLUMI

if (len(sys.argv) !=2):
  print "Usage: python %s Muon(Electron)Conv(RayleighGaus,CB)Nominal(Up,Down,BeforeRC)" %sys.argv[1]
  sys.exit(0)
args = sys.argv[1:]
if (sys.argv[0] == "python"): args =sys.argv[2:]
scenario = "Electron"
if len(args) > 0: scenario = args[0]
print "Will run fit for ", scenario 
if "MuonRayleighGaus" in scenario and "Nominal" in scenario:
  print "Muon - Nominal: Simultaneously Fit with Modified Rayleigh function"
  cmd_string = "root -l -q fitWMuMetModRayleighSimult.C+\(\\\"MuonFitResultsModRayleighSimultNominal\\\",\\\"Nominal\\\",%f,0\)" %LUMI
elif "MuonRayleighGaus" in scenario and "Up" in scenario:
  print "Muon - Up: Simultaneously Fit with Rayleigh and Gaussian function"
  cmd_string = "root -l -q fitWMuMetRayleighGausSimult.C+\(\\\"MuonFitResultsRayleighGausSimultUp\\\",\\\"Up\\\",%f,0\)" %LUMI
elif "MuonRayleighGaus" in scenario and "Down" in scenario:
  print "Muon - Down: Simultaneously Fit with Rayleigh and Gaussian function"
  cmd_string = "root -l -q fitWMuMetRayleighGausSimult.C+\(\\\"MuonFitResultsRayleighGausSimultDown\\\",\\\"Down\\\",%f,0\)" %LUMI
elif "MuonRayleighGaus" in scenario and "BeforeRC" in scenario:
  print "Muon - Before Recoil Correction: Simultaneously Fit with Rayleigh and Gaussian function"
  cmd_string = "root -l -q fitWMuMetRayleighGausSimult.C+\(\\\"MuonFitResultsRayleighGausSimultBeforeRC\\\",\\\"BeforeRC\\\",%f,0\)" %LUMI
elif "ElectronRayleighGaus" in scenario and "Nominal" in scenario:
  print "Electron - Nominal: Simultaneously Fit with Modified Rayleigh function"
  cmd_string = "root -l -q fitWEleMetModRayleighSimult.C+\(\\\"ElectronFitResultsModRayleighSimultNominal\\\",\\\"Nominal\\\",%f,0\)" %LUMI
elif "ElectronRayleighGaus" in scenario and "Up" in scenario:
  print "Electron - Up: Simultaneously Fit with Rayleigh and Gaussian function"
  cmd_string = "root -l -q fitWEleMetRayleighGausSimult.C+\(\\\"ElectronFitResultsRayleighGausSimultUp\\\",\\\"Up\\\",%f,0\)" %LUMI
elif "ElectronRayleighGaus" in scenario and "Down" in scenario:
  print "Electron - Down: Simultaneously Fit with Rayleigh and Gaussian function"
  cmd_string = "root -l -q fitWEleMetRayleighGausSimult.C+\(\\\"ElectronFitResultsRayleighGausSimultDown\\\",\\\"Down\\\",%f,0\)" %LUMI
elif "ElectronRayleighGaus" in scenario and "BeforeRC" in scenario:
  print "Electron - Before Recoil Correction: Simultaneously Fit with Rayleigh and Gaussian function"
  cmd_string = "root -l -q fitWEleMetRayleighGausSimult.C+\(\\\"ElectronFitResultsRayleighGausSimultBeforeRC\\\",\\\"BeforeRC\\\",%f,0\)" %LUMI
print "command is "+cmd_string
os.system(cmd_string)
cmd_string = "rm *.so *.d"
print "command %s is running" %cmd_string
os.system(cmd_string)
