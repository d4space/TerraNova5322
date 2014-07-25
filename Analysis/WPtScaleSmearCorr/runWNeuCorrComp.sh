#! /bin/bash
# Merge root files


#root -l -q WNeuCorrComp.C+\(\"Electron\",\"Minus\",\"MuonLowPU/ZmassPlots\"\)
#root -l -q WNeuCorrComp.C+\(\"Electron\",\"Plus\",\"Electron2012LoPU/ZmassPlots\"\)


root -l -q WNeuCorrComp.C+\(\"Muon\",\"NoCorrWholeZ\",\"Muon2012LoPU/ZmassPlots\"\)
root -l -q WNeuCorrComp.C+\(\"Muon\",\"CorrWholeZ\",\"Muon2012LoPU/ZmassPlots\"\)
root -l -q WNeuCorrComp.C+\(\"Muon\",\"CorrBB\",\"Muon2012LoPU/ZmassPlots\"\)
root -l -q WNeuCorrComp.C+\(\"Muon\",\"CorrBE\",\"Muon2012LoPU/ZmassPlots\"\)
root -l -q WNeuCorrComp.C+\(\"Muon\",\"CorrEE\",\"Muon2012LoPU/ZmassPlots\"\)

root -l -q WNeuCorrComp.C+\(\"Electron\",\"NoCorrWholeZ\",\"Electron2012LoPU/ZmassPlots\"\)
root -l -q WNeuCorrComp.C+\(\"Electron\",\"CorrWholeZ\",\"Electron2012LoPU/ZmassPlots\"\)
root -l -q WNeuCorrComp.C+\(\"Electron\",\"CorrBB\",\"Electron2012LoPU/ZmassPlots\"\)
root -l -q WNeuCorrComp.C+\(\"Electron\",\"CorrBE\",\"Electron2012LoPU/ZmassPlots\"\)
root -l -q WNeuCorrComp.C+\(\"Electron\",\"CorrEE\",\"Electron2012LoPU/ZmassPlots\"\)
rm *.so *.d
