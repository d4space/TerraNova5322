#! /bin/bash
# Merge root files


#root -l -q WNeuCorrComp.C+\(\"Electron\",\"Minus\",\"MuonLowPU/ZmassPlots\"\)
root -l -q WNeuCorrComp.C+\(\"Electron\",\"Plus\",\"Electron2012LoPU/ZmassPlots\"\)
rm *.so *.d
