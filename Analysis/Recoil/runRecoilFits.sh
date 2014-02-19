#! /bin/bash
#Muon
#INPUTDIR=/terranova_0/W/CMSSW_5_2_6/src/KoSMP/WAnalyzer/analysis/MuNeu/W_Pt/results
INPUTDIR=/u/user/sangilpark/WorkDir/Muon/KoSMP_Nominal/WAnalyzer/analysis/EventSelection/MuonLowPU
###                           u1 model(1:single,2:double,3:triple), u2 model, signal only
root -l -q fitRecoil.C+\(\"${INPUTDIR}/RDRecoil.root\",2,2,1,\"ZmmData\",\"Z\"\)
rm *.so *.d
root -l -q fitRecoil.C+\(\"${INPUTDIR}/DYToMuMuRecoil.root\",2,2,1,\"ZmmMC\",\"Z\"\)
rm *.so *.d
root -l -q fitRecoil.C+\(\"${INPUTDIR}/WpToMuNuRecoil.root\",2,2,1,\"WmpMC\",\"W\"\)
rm *.so *.d
root -l -q fitRecoil.C+\(\"${INPUTDIR}/WmToMuNuRecoil.root\",2,2,1,\"WmmMC\",\"W\"\)
rm *.so *.d

#Electron scripts
#INPUTDIR=/d2/scratch/knuhamid/Wpt-x-section/CMSSW_5_3_4/src/KoSMP/WAnalyzer/analysis/EventSelection/ElectronLowPU
#INPUTDIR=/d2/scratch/khakim/WAnalysis/CMSSW_5_2_6/src/KoSMP/WAnalyzer/analysis/EventSelection/ElectronLowPU
###                           u1 model(1:single,2:double,3:triple), u2 model, signal only
#root -l -q fitRecoil.C+\(\"${INPUTDIR}/Ele_RD_LowPU_Recoil.root\",2,2,1,\"ZeeData\",\"Z\"\)
#rm *.so *.d
#root -l -q fitRecoil.C+\(\"${INPUTDIR}/Ele_DYToEE_S8_Recoil.root\",2,2,1,\"ZeeMC\",\"Z\"\)
#rm *.so *.d
#root -l -q fitRecoil.C+\(\"${INPUTDIR}/Ele_WpEleNu_S8_Recoil.root\",2,2,1,\"WepMC\",\"W\"\)
#rm *.so *.d
#root -l -q fitRecoil.C+\(\"${INPUTDIR}/Ele_WmEleNu_S8_Recoil.root\",2,2,1,\"WemMC\",\"W\"\)
#rm *.so *.d
