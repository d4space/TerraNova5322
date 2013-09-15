#! /bin/bash
#Muon
#INPUTDIR=/terranova_0/W/CMSSW_5_2_6/src/KNUPhy/WAnalyzer/analysis/MuNeu/W_Pt/results
INPUTDIR=/d2/scratch/khakim/WAnalysis/CMSSW_5_2_6/src/KNUPhy/WAnalyzer/analysis/EventSelection/MuonLowPU
###                           u1 model(1:single,2:double,3:triple), u2 model, signal only
root -l -q fitRecoil.C+\(\"${INPUTDIR}/RDRecoil.root\",2,2,1,\"ZmmData\",\"Z\"\)
root -l -q fitRecoil.C+\(\"${INPUTDIR}/DYToMuMuRecoil.root\",2,2,1,\"ZmmMC\",\"Z\"\)
root -l -q fitRecoil.C+\(\"${INPUTDIR}/WpToMuNuRecoil.root\",2,2,1,\"WmpMC\",\"W\"\)
root -l -q fitRecoil.C+\(\"${INPUTDIR}/WmToMuNuRecoil.root\",2,2,1,\"WmmMC\",\"W\"\)

#Electron scripts
#INPUTDIR=/d2/scratch/knuhamid/Wpt-x-section/CMSSW_5_3_4/src/KNUPhy/WAnalyzer/analysis/EventSelection/ElectronLowPU
#INPUTDIR=/d2/scratch/khakim/WAnalysis/CMSSW_5_2_6/src/KNUPhy/WAnalyzer/analysis/EventSelection/ElectronLowPU
###                           u1 model(1:single,2:double,3:triple), u2 model, signal only
#root -l -q fitRecoil.C+\(\"${INPUTDIR}/Ele_RD_LowPU_Recoil.root\",2,2,1,\"ZeeData\",\"Z\"\)
#root -l -q fitRecoil.C+\(\"${INPUTDIR}/Ele_DYToEE_S8_Recoil.root\",2,2,1,\"ZeeMC\",\"Z\"\)
#root -l -q fitRecoil.C+\(\"${INPUTDIR}/Ele_WpEleNu_S8_Recoil.root\",2,2,1,\"WepMC\",\"W\"\)
#root -l -q fitRecoil.C+\(\"${INPUTDIR}/Ele_WmEleNu_S8_Recoil.root\",2,2,1,\"WemMC\",\"W\"\)

rm *.so *.d
