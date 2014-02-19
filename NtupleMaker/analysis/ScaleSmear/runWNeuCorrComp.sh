#! /bin/bash
# Merge root files
#hadd -f MuonLowPU/Muon_WToMuNu_S8_Analysis.root MuonLowPU/Muon_WpToMuNu_S8_Analysis.root MuonLowPU/Muon_WmToMuNu_S8_Analysis.root
#hadd -f MuonLowPU/Muon_WToMuNu_S8_Nom_RecoilCorr.root MuonLowPU/Muon_WpToMuNu_S8_RecoilCorr.root MuonLowPU/Muon_WmToMuNu_S8_RecoilCorr.root
#hadd -f MuonLowPU/Muon_WToMuNu_S8_Up_RecoilCorr.root MuonLowPU/Muon_WpToMuNu_S8_Up_RecoilCorr.root MuonLowPU/Muon_WmToMuNu_S8_Up_RecoilCorr.root
#hadd -f MuonLowPU/Muon_WToMuNu_S8_Down_RecoilCorr.root MuonLowPU/Muon_WpToMuNu_S8_Down_RecoilCorr.root MuonLowPU/Muon_WmToMuNu_S8_Down_RecoilCorr.root
#hadd -f ElectronLowPU/Ele_WToEleNu_S8_Analysis.root ElectronLowPU/Ele_WpToEleNu_S8_Analysis.root ElectronLowPU/Ele_WmToEleNu_S8_Analysis.root
#hadd -f ElectronLowPU/Ele_WToEleNu_S8_Nom_RecoilCorr.root ElectronLowPU/Ele_WpToEleNu_S8_RecoilCorr.root ElectronLowPU/Ele_WmToEleNu_S8_RecoilCorr.root
#hadd -f ElectronLowPU/Ele_WToEleNu_S8_Up_RecoilCorr.root ElectronLowPU/Ele_WpToEleNu_S8_Up_RecoilCorr.root ElectronLowPU/Ele_WmToEleNu_S8_Up_RecoilCorr.root
#hadd -f ElectronLowPU/Ele_WToEleNu_S8_Down_RecoilCorr.root ElectronLowPU/Ele_WpToEleNu_S8_Down_RecoilCorr.root ElectronLowPU/Ele_WmToEleNu_S8_Down_RecoilCorr.root

#root -l -q WNeuCorrComp.C+\(\"Muon\"\,\"Inclusive\"\,\"MuonLowPU/PlotsNeuCorrCompInclusive\"\)
#rm *.so *.d
#root -l -q WNeuCorrComp.C+\(\"Muon\",\"Plus\",\"MuonLowPU/PlotsNeuCorrCompPlus\"\)
#rm *.so *.d
#root -l -q WNeuCorrComp.C+\(\"Muon\",\"Minus\",\"MuonLowPU/PlotsNeuCorrCompMinus\"\)
#rm *.so *.d
#root -l -q WNeuCorrComp.C+\(\"Electron\",\"Inclusive\",\"ElectronLowPU/PlotsNeuCorrCompInclusive\"\)
#rm *.so *.d
#root -l -q WNeuCorrComp.C+\(\"Electron\",\"Plus\",\"ElectronLowPU/PlotsNeuCorrCompPlus\"\)
#rm *.so *.d
root -l -q WNeuCorrComp.C+\(\"Electron\",\"Minus\",\"MuonLowPU/ZmassPlots\"\)
#root -l -q WNeuCorrComp.C+\(\"Electron\",\"Minus\",\"ElectronLowPU/ZmassPlots\"\)
rm *.so *.d
