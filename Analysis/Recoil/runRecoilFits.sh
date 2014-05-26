#! /bin/bash
#Muon
INPUTDIR=../WPtRecoilCorr/Muon2012LoPU
###                           u1 model(1:single,2:double,3:triple), u2 model, signal only
root -l -q fitRecoil.C+\(\"${INPUTDIR}/Muon_RD_LowPU_RecoilEvaRD.root\",2,2,1,\"ZmmData\",\"Z\"\)
rm *.so *.d
root -l -q fitRecoil.C+\(\"${INPUTDIR}/Muon_DYToMuMu_S8_RecoilEvaMC.root\",2,2,1,\"ZmmMC\",\"Z\"\)
rm *.so *.d
root -l -q fitRecoil.C+\(\"${INPUTDIR}/WpToMuNu_S8_RecoilEvaMC.root\",2,2,1,\"WmpMC\",\"W\"\)
rm *.so *.d
root -l -q fitRecoil.C+\(\"${INPUTDIR}/WmToMuNu_S8_RecoilEvaMC.root\",2,2,1,\"WmmMC\",\"W\"\)
rm *.so *.d

#Electron scripts
INPUTDIR=../WPtRecoilCorr/Electron2012LoPU
###                           u1 model(1:single,2:double,3:triple), u2 model, signal only
root -l -q fitRecoil.C+\(\"${INPUTDIR}/Ele_RD_LowPU_RecoilEvaRD.root\",2,2,1,\"ZeeData\",\"Z\"\)
rm *.so *.d
root -l -q fitRecoil.C+\(\"${INPUTDIR}/Ele_DYToEE_S8_RecoilEvaMC.root\",2,2,1,\"ZeeMC\",\"Z\"\)
rm *.so *.d
root -l -q fitRecoil.C+\(\"${INPUTDIR}/WpToEleNu_S8_RecoilEvaMC.root\",2,2,1,\"WepMC\",\"W\"\)
rm *.so *.d
root -l -q fitRecoil.C+\(\"${INPUTDIR}/WmToEleNu_S8_RecoilEvaMC.root\",2,2,1,\"WemMC\",\"W\"\)
rm *.so *.d
