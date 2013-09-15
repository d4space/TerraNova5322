#! /bin/bash
# Merge root files
hadd -f MuonLowPU/Muon_WToMuNu_S8_Analysis.root MuonLowPU/Muon_WpToMuNu_S8_Analysis.root MuonLowPU/Muon_WmToMuNu_S8_Analysis.root
hadd -f MuonLowPU/Muon_WToMuNu_S8_Nom_RecoilCorrMC.root MuonLowPU/Muon_WpToMuNu_S8_RecoilCorrMC.root MuonLowPU/Muon_WmToMuNu_S8_RecoilCorrMC.root
hadd -f MuonLowPU/Muon_WToMuNu_S8_Up_RecoilCorrMC.root MuonLowPU/Muon_WpToMuNu_S8_Up_RecoilCorrMC.root MuonLowPU/Muon_WmToMuNu_S8_Up_RecoilCorrMC.root
hadd -f MuonLowPU/Muon_WToMuNu_S8_Down_RecoilCorrMC.root MuonLowPU/Muon_WpToMuNu_S8_Down_RecoilCorrMC.root MuonLowPU/Muon_WmToMuNu_S8_Down_RecoilCorrMC.root
hadd -f ElectronLowPU/Ele_WToEleNu_S8_Analysis.root ElectronLowPU/Ele_WpToEleNu_S8_Analysis.root ElectronLowPU/Ele_WmToEleNu_S8_Analysis.root
hadd -f ElectronLowPU/Ele_WToEleNu_S8_Nom_RecoilCorrMC.root ElectronLowPU/Ele_WpToEleNu_S8_RecoilCorrMC.root ElectronLowPU/Ele_WmToEleNu_S8_RecoilCorrMC.root
hadd -f ElectronLowPU/Ele_WToEleNu_S8_Up_RecoilCorrMC.root ElectronLowPU/Ele_WpToEleNu_S8_Up_RecoilCorrMC.root ElectronLowPU/Ele_WmToEleNu_S8_Up_RecoilCorrMC.root
hadd -f ElectronLowPU/Ele_WToEleNu_S8_Down_RecoilCorrMC.root ElectronLowPU/Ele_WpToEleNu_S8_Down_RecoilCorrMC.root ElectronLowPU/Ele_WmToEleNu_S8_Down_RecoilCorrMC.root
root -l -q WNeuCorrComp.C+\(\"Muon\"\,\"Inclusive\"\,\"MuonLowPU/PlotsNeuCorrCompInclusive\"\)
rm *.so *.d
root -l -q WNeuCorrComp.C+\(\"Muon\",\"Plus\",\"MuonLowPU/PlotsNeuCorrCompPlus\"\)
rm *.so *.d
root -l -q WNeuCorrComp.C+\(\"Muon\",\"Minus\",\"MuonLowPU/PlotsNeuCorrCompMinus\"\)
rm *.so *.d
root -l -q WNeuCorrComp.C+\(\"Electron\",\"Inclusive\",\"ElectronLowPU/PlotsNeuCorrCompInclusive\"\)
rm *.so *.d
root -l -q WNeuCorrComp.C+\(\"Electron\",\"Plus\",\"ElectronLowPU/PlotsNeuCorrCompPlus\"\)
rm *.so *.d
root -l -q WNeuCorrComp.C+\(\"Electron\",\"Minus\",\"ElectronLowPU/PlotsNeuCorrCompMinus\"\)
rm *.so *.d
