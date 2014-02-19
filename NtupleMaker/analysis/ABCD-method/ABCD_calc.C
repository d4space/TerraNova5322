#include <fstream>
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <math.h>

void ABCD_calc(const TString filetype)
{
  ofstream Fout;
  //Fout.open(filetype+"_Systematics.txt");
  Fout.open(filetype+"_ABCD-result.txt");

  if (filetype == "Mu"){
  //=================== W inclusive =============================
  // RD
  ifstream RDa_file("../EventSelection/MuonLowPU/Muon_RD_LowPU_Analysis_SummaryA.txt");
  ifstream RDb_file("../EventSelection/MuonLowPU/Muon_RD_LowPU_Analysis_SummaryB.txt");
  ifstream RDd_file("../EventSelection/MuonLowPU/Muon_RD_LowPU_Analysis_SummaryD.txt");
  ifstream RDc_file("../EventSelection/MuonLowPU/Muon_RD_LowPU_Analysis_SummaryC.txt");

  //EWK
  ifstream DYToEEa_file("../EventSelection/MuonLowPU/Muon_DYToMuMu_S8_Analysis_SummaryA.txt");
  ifstream DYToEEb_file("../EventSelection/MuonLowPU/Muon_DYToMuMu_S8_Analysis_SummaryB.txt");
  ifstream DYToEEd_file("../EventSelection/MuonLowPU/Muon_DYToMuMu_S8_Analysis_SummaryD.txt");
  ifstream DYToEEc_file("../EventSelection/MuonLowPU/Muon_DYToMuMu_S8_Analysis_SummaryC.txt");
  ifstream DYToTauTau_a_file("../EventSelection/MuonLowPU/Muon_DYToTauTau_S8_Analysis_SummaryA.txt");
  ifstream DYToTauTau_b_file("../EventSelection/MuonLowPU/Muon_DYToTauTau_S8_Analysis_SummaryB.txt");
  ifstream DYToTauTau_d_file("../EventSelection/MuonLowPU/Muon_DYToTauTau_S8_Analysis_SummaryD.txt");
  ifstream DYToTauTau_c_file("../EventSelection/MuonLowPU/Muon_DYToTauTau_S8_Analysis_SummaryC.txt");
  ifstream WToTauNu_a_file("../EventSelection/MuonLowPU/Muon_WToTauNu_S8_Analysis_SummaryA.txt");
  ifstream WToTauNu_b_file("../EventSelection/MuonLowPU/Muon_WToTauNu_S8_Analysis_SummaryB.txt");
  ifstream WToTauNu_d_file("../EventSelection/MuonLowPU/Muon_WToTauNu_S8_Analysis_SummaryD.txt");
  ifstream WToTauNu_c_file("../EventSelection/MuonLowPU/Muon_WToTauNu_S8_Analysis_SummaryC.txt");
  ifstream TTJets_a_file("../EventSelection/MuonLowPU/Muon_TTJets_S8_Analysis_SummaryA.txt");
  ifstream TTJets_b_file("../EventSelection/MuonLowPU/Muon_TTJets_S8_Analysis_SummaryB.txt");
  ifstream TTJets_d_file("../EventSelection/MuonLowPU/Muon_TTJets_S8_Analysis_SummaryD.txt");
  ifstream TTJets_c_file("../EventSelection/MuonLowPU/Muon_TTJets_S8_Analysis_SummaryC.txt");
  
  //Wplus Before and After recoil
//  ifstream WpToEleNu_a_file("../EventSelection/MuonLowPU/Muon_WpToMuNu_S8_Analysis_SummaryA.txt");
//  ifstream WpToEleNu_b_file("../EventSelection/MuonLowPU/Muon_WpToMuNu_S8_Analysis_SummaryB.txt");
//  ifstream WpToEleNu_d_file("../EventSelection/MuonLowPU/Muon_WpToMuNu_S8_Analysis_SummaryD.txt");
//  ifstream WpToEleNu_c_file("../EventSelection/MuonLowPU/Muon_WpToMuNu_S8_Analysis_SummaryC.txt");
  ifstream WpToEleNu_a_file("../EventSelection/MuonLowPU/Muon_WpToMuNu_S8_Analysis_Summary_Plus_A.txt");
  ifstream WpToEleNu_b_file("../EventSelection/MuonLowPU/Muon_WpToMuNu_S8_Analysis_Summary_Plus_B.txt");
  ifstream WpToEleNu_d_file("../EventSelection/MuonLowPU/Muon_WpToMuNu_S8_Analysis_Summary_Plus_D.txt");
  ifstream WpToEleNu_c_file("../EventSelection/MuonLowPU/Muon_WpToMuNu_S8_Analysis_Summary_Plus_C.txt");

  ifstream WpToEleNuRecoil_a_file("../EventSelection/MuonLowPU/Muon_WpToMuNu_S8_RecoilCorrMC_SummaryA.txt");
  ifstream WpToEleNuRecoil_b_file("../EventSelection/MuonLowPU/Muon_WpToMuNu_S8_RecoilCorrMC_SummaryB.txt");
  ifstream WpToEleNuRecoil_d_file("../EventSelection/MuonLowPU/Muon_WpToMuNu_S8_RecoilCorrMC_SummaryD.txt");
  ifstream WpToEleNuRecoil_c_file("../EventSelection/MuonLowPU/Muon_WpToMuNu_S8_RecoilCorrMC_SummaryC.txt");

  //Wminus Before and After recoil
//  ifstream WmToEleNu_a_file("../EventSelection/MuonLowPU/Muon_WmToMuNu_S8_Analysis_SummaryA.txt");
//  ifstream WmToEleNu_b_file("../EventSelection/MuonLowPU/Muon_WmToMuNu_S8_Analysis_SummaryB.txt");
//  ifstream WmToEleNu_d_file("../EventSelection/MuonLowPU/Muon_WmToMuNu_S8_Analysis_SummaryD.txt");
//  ifstream WmToEleNu_c_file("../EventSelection/MuonLowPU/Muon_WmToMuNu_S8_Analysis_SummaryC.txt");
  ifstream WmToEleNu_a_file("../EventSelection/MuonLowPU/Muon_WmToMuNu_S8_Analysis_Summary_Minus_A.txt");
  ifstream WmToEleNu_b_file("../EventSelection/MuonLowPU/Muon_WmToMuNu_S8_Analysis_Summary_Minus_B.txt");
  ifstream WmToEleNu_d_file("../EventSelection/MuonLowPU/Muon_WmToMuNu_S8_Analysis_Summary_Minus_D.txt");
  ifstream WmToEleNu_c_file("../EventSelection/MuonLowPU/Muon_WmToMuNu_S8_Analysis_Summary_Minus_C.txt");

  ifstream WmToEleNuRecoil_a_file("../EventSelection/MuonLowPU/Muon_WmToMuNu_S8_RecoilCorrMC_SummaryA.txt");
  ifstream WmToEleNuRecoil_b_file("../EventSelection/MuonLowPU/Muon_WmToMuNu_S8_RecoilCorrMC_SummaryB.txt");
  ifstream WmToEleNuRecoil_d_file("../EventSelection/MuonLowPU/Muon_WmToMuNu_S8_RecoilCorrMC_SummaryD.txt");
  ifstream WmToEleNuRecoil_c_file("../EventSelection/MuonLowPU/Muon_WmToMuNu_S8_RecoilCorrMC_SummaryC.txt");

  //=================== W + =============================
  // RD
  ifstream RDaPlus_file("../EventSelection/MuonLowPU/Muon_RD_LowPU_Analysis_Summary_Plus_A.txt");
  ifstream RDbPlus_file("../EventSelection/MuonLowPU/Muon_RD_LowPU_Analysis_Summary_Plus_B.txt");
  ifstream RDdPlus_file("../EventSelection/MuonLowPU/Muon_RD_LowPU_Analysis_Summary_Plus_D.txt");
  ifstream RDcPlus_file("../EventSelection/MuonLowPU/Muon_RD_LowPU_Analysis_Summary_Plus_C.txt");

  //EWK
  ifstream DYToEEaPlus_file("../EventSelection/MuonLowPU/Muon_DYToEE_S8_Analysis_Summary_Plus_A.txt");
  ifstream DYToEEbPlus_file("../EventSelection/MuonLowPU/Muon_DYToEE_S8_Analysis_Summary_Plus_B.txt");
  ifstream DYToEEdPlus_file("../EventSelection/MuonLowPU/Muon_DYToEE_S8_Analysis_Summary_Plus_D.txt");
  ifstream DYToEEcPlus_file("../EventSelection/MuonLowPU/Muon_DYToEE_S8_Analysis_Summary_Plus_C.txt");
  ifstream DYToTauTau_aPlus_file("../EventSelection/MuonLowPU/Muon_DYToTauTau_S8_Analysis_Summary_Plus_A.txt");
  ifstream DYToTauTau_bPlus_file("../EventSelection/MuonLowPU/Muon_DYToTauTau_S8_Analysis_Summary_Plus_B.txt");
  ifstream DYToTauTau_dPlus_file("../EventSelection/MuonLowPU/Muon_DYToTauTau_S8_Analysis_Summary_Plus_D.txt");
  ifstream DYToTauTau_cPlus_file("../EventSelection/MuonLowPU/Muon_DYToTauTau_S8_Analysis_Summary_Plus_C.txt");
  ifstream WToTauNu_aPlus_file("../EventSelection/MuonLowPU/Muon_WToTauNu_S8_Analysis_Summary_Plus_A.txt");
  ifstream WToTauNu_bPlus_file("../EventSelection/MuonLowPU/Muon_WToTauNu_S8_Analysis_Summary_Plus_B.txt");
  ifstream WToTauNu_dPlus_file("../EventSelection/MuonLowPU/Muon_WToTauNu_S8_Analysis_Summary_Plus_D.txt");
  ifstream WToTauNu_cPlus_file("../EventSelection/MuonLowPU/Muon_WToTauNu_S8_Analysis_Summary_Plus_C.txt");
  ifstream TTJets_aPlus_file("../EventSelection/MuonLowPU/Muon_TTJets_S8_Analysis_Summary_Plus_A.txt");
  ifstream TTJets_bPlus_file("../EventSelection/MuonLowPU/Muon_TTJets_S8_Analysis_Summary_Plus_B.txt");
  ifstream TTJets_dPlus_file("../EventSelection/MuonLowPU/Muon_TTJets_S8_Analysis_Summary_Plus_D.txt");
  ifstream TTJets_cPlus_file("../EventSelection/MuonLowPU/Muon_TTJets_S8_Analysis_Summary_Plus_C.txt");
  
  //Wplus Before and After recoil
  ifstream WpToEleNu_aPlus_file("../EventSelection/MuonLowPU/Muon_WpToMuNu_S8_Analysis_Summary_Plus_A.txt");
  ifstream WpToEleNu_bPlus_file("../EventSelection/MuonLowPU/Muon_WpToMuNu_S8_Analysis_Summary_Plus_B.txt");
  ifstream WpToEleNu_dPlus_file("../EventSelection/MuonLowPU/Muon_WpToMuNu_S8_Analysis_Summary_Plus_D.txt");
  ifstream WpToEleNu_cPlus_file("../EventSelection/MuonLowPU/Muon_WpToMuNu_S8_Analysis_Summary_Plus_C.txt");

  ifstream WpToEleNuRecoil_aPlus_file("../EventSelection/MuonLowPU/Muon_WpToMuNu_S8_RecoilCorrMC_Summary_Plus_A.txt");
  ifstream WpToEleNuRecoil_bPlus_file("../EventSelection/MuonLowPU/Muon_WpToMuNu_S8_RecoilCorrMC_Summary_Plus_B.txt");
  ifstream WpToEleNuRecoil_dPlus_file("../EventSelection/MuonLowPU/Muon_WpToMuNu_S8_RecoilCorrMC_Summary_Plus_D.txt");
  ifstream WpToEleNuRecoil_cPlus_file("../EventSelection/MuonLowPU/Muon_WpToMuNu_S8_RecoilCorrMC_Summary_Plus_C.txt");

  //=================== W - =============================
  // RD
  ifstream RDaMinus_file("../EventSelection/MuonLowPU/Muon_RD_LowPU_Analysis_Summary_Minus_A.txt");
  ifstream RDbMinus_file("../EventSelection/MuonLowPU/Muon_RD_LowPU_Analysis_Summary_Minus_B.txt");
  ifstream RDdMinus_file("../EventSelection/MuonLowPU/Muon_RD_LowPU_Analysis_Summary_Minus_D.txt");
  ifstream RDcMinus_file("../EventSelection/MuonLowPU/Muon_RD_LowPU_Analysis_Summary_Minus_C.txt");

  //EWK
  ifstream DYToEEaMinus_file("../EventSelection/MuonLowPU/Muon_DYToEE_S8_Analysis_Summary_Minus_A.txt");
  ifstream DYToEEbMinus_file("../EventSelection/MuonLowPU/Muon_DYToEE_S8_Analysis_Summary_Minus_B.txt");
  ifstream DYToEEdMinus_file("../EventSelection/MuonLowPU/Muon_DYToEE_S8_Analysis_Summary_Minus_D.txt");
  ifstream DYToEEcMinus_file("../EventSelection/MuonLowPU/Muon_DYToEE_S8_Analysis_Summary_Minus_C.txt");
  ifstream DYToTauTau_aMinus_file("../EventSelection/MuonLowPU/Muon_DYToTauTau_S8_Analysis_Summary_Minus_A.txt");
  ifstream DYToTauTau_bMinus_file("../EventSelection/MuonLowPU/Muon_DYToTauTau_S8_Analysis_Summary_Minus_B.txt");
  ifstream DYToTauTau_dMinus_file("../EventSelection/MuonLowPU/Muon_DYToTauTau_S8_Analysis_Summary_Minus_D.txt");
  ifstream DYToTauTau_cMinus_file("../EventSelection/MuonLowPU/Muon_DYToTauTau_S8_Analysis_Summary_Minus_C.txt");
  ifstream WToTauNu_aMinus_file("../EventSelection/MuonLowPU/Muon_WToTauNu_S8_Analysis_Summary_Minus_A.txt");
  ifstream WToTauNu_bMinus_file("../EventSelection/MuonLowPU/Muon_WToTauNu_S8_Analysis_Summary_Minus_B.txt");
  ifstream WToTauNu_dMinus_file("../EventSelection/MuonLowPU/Muon_WToTauNu_S8_Analysis_Summary_Minus_D.txt");
  ifstream WToTauNu_cMinus_file("../EventSelection/MuonLowPU/Muon_WToTauNu_S8_Analysis_Summary_Minus_C.txt");
  ifstream TTJets_aMinus_file("../EventSelection/MuonLowPU/Muon_TTJets_S8_Analysis_Summary_Minus_A.txt");
  ifstream TTJets_bMinus_file("../EventSelection/MuonLowPU/Muon_TTJets_S8_Analysis_Summary_Minus_B.txt");
  ifstream TTJets_dMinus_file("../EventSelection/MuonLowPU/Muon_TTJets_S8_Analysis_Summary_Minus_D.txt");
  ifstream TTJets_cMinus_file("../EventSelection/MuonLowPU/Muon_TTJets_S8_Analysis_Summary_Minus_C.txt");

  //Wminus Before and After recoil
  ifstream WmToEleNu_aMinus_file("../EventSelection/MuonLowPU/Muon_WmToMuNu_S8_Analysis_Summary_Minus_A.txt");
  ifstream WmToEleNu_bMinus_file("../EventSelection/MuonLowPU/Muon_WmToMuNu_S8_Analysis_Summary_Minus_B.txt");
  ifstream WmToEleNu_dMinus_file("../EventSelection/MuonLowPU/Muon_WmToMuNu_S8_Analysis_Summary_Minus_D.txt");
  ifstream WmToEleNu_cMinus_file("../EventSelection/MuonLowPU/Muon_WmToMuNu_S8_Analysis_Summary_Minus_C.txt");

  ifstream WmToEleNuRecoil_aMinus_file("../EventSelection/MuonLowPU/Muon_WmToMuNu_S8_RecoilCorrMC_Summary_Minus_A.txt");
  ifstream WmToEleNuRecoil_bMinus_file("../EventSelection/MuonLowPU/Muon_WmToMuNu_S8_RecoilCorrMC_Summary_Minus_B.txt");
  ifstream WmToEleNuRecoil_dMinus_file("../EventSelection/MuonLowPU/Muon_WmToMuNu_S8_RecoilCorrMC_Summary_Minus_D.txt");
  ifstream WmToEleNuRecoil_cMinus_file("../EventSelection/MuonLowPU/Muon_WmToMuNu_S8_RecoilCorrMC_Summary_Minus_C.txt");

  }else if (filetype == "Ele"){

  //=================== W inclusive =============================
  // RD
  ifstream RDa_file("../EventSelection/ElectronLowPU/Ele_RD_LowPU_Analysis_SummaryA.txt");
  ifstream RDb_file("../EventSelection/ElectronLowPU/Ele_RD_LowPU_Analysis_SummaryB.txt");
  ifstream RDd_file("../EventSelection/ElectronLowPU/Ele_RD_LowPU_Analysis_SummaryD.txt");
  ifstream RDc_file("../EventSelection/ElectronLowPU/Ele_RD_LowPU_Analysis_SummaryC.txt");

  //EWK
  ifstream DYToEEa_file("../EventSelection/ElectronLowPU/Ele_DYToEE_S8_Analysis_SummaryA.txt");
  ifstream DYToEEb_file("../EventSelection/ElectronLowPU/Ele_DYToEE_S8_Analysis_SummaryB.txt");
  ifstream DYToEEd_file("../EventSelection/ElectronLowPU/Ele_DYToEE_S8_Analysis_SummaryD.txt");
  ifstream DYToEEc_file("../EventSelection/ElectronLowPU/Ele_DYToEE_S8_Analysis_SummaryC.txt");
  ifstream DYToTauTau_a_file("../EventSelection/ElectronLowPU/Ele_DYToTauTau_S8_Analysis_SummaryA.txt");
  ifstream DYToTauTau_b_file("../EventSelection/ElectronLowPU/Ele_DYToTauTau_S8_Analysis_SummaryB.txt");
  ifstream DYToTauTau_d_file("../EventSelection/ElectronLowPU/Ele_DYToTauTau_S8_Analysis_SummaryD.txt");
  ifstream DYToTauTau_c_file("../EventSelection/ElectronLowPU/Ele_DYToTauTau_S8_Analysis_SummaryC.txt");
  ifstream WToTauNu_a_file("../EventSelection/ElectronLowPU/Ele_WToTauNu_S8_Analysis_SummaryA.txt");
  ifstream WToTauNu_b_file("../EventSelection/ElectronLowPU/Ele_WToTauNu_S8_Analysis_SummaryB.txt");
  ifstream WToTauNu_d_file("../EventSelection/ElectronLowPU/Ele_WToTauNu_S8_Analysis_SummaryD.txt");
  ifstream WToTauNu_c_file("../EventSelection/ElectronLowPU/Ele_WToTauNu_S8_Analysis_SummaryC.txt");
  ifstream TTJets_a_file("../EventSelection/ElectronLowPU/Ele_TTJets_S8_Analysis_SummaryA.txt");
  ifstream TTJets_b_file("../EventSelection/ElectronLowPU/Ele_TTJets_S8_Analysis_SummaryB.txt");
  ifstream TTJets_d_file("../EventSelection/ElectronLowPU/Ele_TTJets_S8_Analysis_SummaryD.txt");
  ifstream TTJets_c_file("../EventSelection/ElectronLowPU/Ele_TTJets_S8_Analysis_SummaryC.txt");
  
  //Wplus Before and After recoil
  ifstream WpToEleNu_a_file("../EventSelection/ElectronLowPU/Ele_WpToEleNu_S8_Analysis_SummaryA.txt");
  ifstream WpToEleNu_b_file("../EventSelection/ElectronLowPU/Ele_WpToEleNu_S8_Analysis_SummaryB.txt");
  ifstream WpToEleNu_d_file("../EventSelection/ElectronLowPU/Ele_WpToEleNu_S8_Analysis_SummaryD.txt");
  ifstream WpToEleNu_c_file("../EventSelection/ElectronLowPU/Ele_WpToEleNu_S8_Analysis_SummaryC.txt");

  ifstream WpToEleNuRecoil_a_file("../EventSelection/ElectronLowPU/Ele_WpToEleNu_S8_RecoilCorrMC_SummaryA.txt");
  ifstream WpToEleNuRecoil_b_file("../EventSelection/ElectronLowPU/Ele_WpToEleNu_S8_RecoilCorrMC_SummaryB.txt");
  ifstream WpToEleNuRecoil_d_file("../EventSelection/ElectronLowPU/Ele_WpToEleNu_S8_RecoilCorrMC_SummaryD.txt");
  ifstream WpToEleNuRecoil_c_file("../EventSelection/ElectronLowPU/Ele_WpToEleNu_S8_RecoilCorrMC_SummaryC.txt");

  //Wminus Before and After recoil
  ifstream WmToEleNu_a_file("../EventSelection/ElectronLowPU/Ele_WmToEleNu_S8_Analysis_SummaryA.txt");
  ifstream WmToEleNu_b_file("../EventSelection/ElectronLowPU/Ele_WmToEleNu_S8_Analysis_SummaryB.txt");
  ifstream WmToEleNu_d_file("../EventSelection/ElectronLowPU/Ele_WmToEleNu_S8_Analysis_SummaryD.txt");
  ifstream WmToEleNu_c_file("../EventSelection/ElectronLowPU/Ele_WmToEleNu_S8_Analysis_SummaryC.txt");

  ifstream WmToEleNuRecoil_a_file("../EventSelection/ElectronLowPU/Ele_WmToEleNu_S8_RecoilCorrMC_SummaryA.txt");
  ifstream WmToEleNuRecoil_b_file("../EventSelection/ElectronLowPU/Ele_WmToEleNu_S8_RecoilCorrMC_SummaryB.txt");
  ifstream WmToEleNuRecoil_d_file("../EventSelection/ElectronLowPU/Ele_WmToEleNu_S8_RecoilCorrMC_SummaryD.txt");
  ifstream WmToEleNuRecoil_c_file("../EventSelection/ElectronLowPU/Ele_WmToEleNu_S8_RecoilCorrMC_SummaryC.txt");

  //=================== W + =============================
  // RD
  ifstream RDaPlus_file("../EventSelection/ElectronLowPU/Ele_RD_LowPU_Analysis_Summary_Plus_A.txt");
  ifstream RDbPlus_file("../EventSelection/ElectronLowPU/Ele_RD_LowPU_Analysis_Summary_Plus_B.txt");
  ifstream RDdPlus_file("../EventSelection/ElectronLowPU/Ele_RD_LowPU_Analysis_Summary_Plus_D.txt");
  ifstream RDcPlus_file("../EventSelection/ElectronLowPU/Ele_RD_LowPU_Analysis_Summary_Plus_C.txt");

  //EWK
  ifstream DYToEEaPlus_file("../EventSelection/ElectronLowPU/Ele_DYToEE_S8_Analysis_Summary_Plus_A.txt");
  ifstream DYToEEbPlus_file("../EventSelection/ElectronLowPU/Ele_DYToEE_S8_Analysis_Summary_Plus_B.txt");
  ifstream DYToEEdPlus_file("../EventSelection/ElectronLowPU/Ele_DYToEE_S8_Analysis_Summary_Plus_D.txt");
  ifstream DYToEEcPlus_file("../EventSelection/ElectronLowPU/Ele_DYToEE_S8_Analysis_Summary_Plus_C.txt");
  ifstream DYToTauTau_aPlus_file("../EventSelection/ElectronLowPU/Ele_DYToTauTau_S8_Analysis_Summary_Plus_A.txt");
  ifstream DYToTauTau_bPlus_file("../EventSelection/ElectronLowPU/Ele_DYToTauTau_S8_Analysis_Summary_Plus_B.txt");
  ifstream DYToTauTau_dPlus_file("../EventSelection/ElectronLowPU/Ele_DYToTauTau_S8_Analysis_Summary_Plus_D.txt");
  ifstream DYToTauTau_cPlus_file("../EventSelection/ElectronLowPU/Ele_DYToTauTau_S8_Analysis_Summary_Plus_C.txt");
  ifstream WToTauNu_aPlus_file("../EventSelection/ElectronLowPU/Ele_WToTauNu_S8_Analysis_Summary_Plus_A.txt");
  ifstream WToTauNu_bPlus_file("../EventSelection/ElectronLowPU/Ele_WToTauNu_S8_Analysis_Summary_Plus_B.txt");
  ifstream WToTauNu_dPlus_file("../EventSelection/ElectronLowPU/Ele_WToTauNu_S8_Analysis_Summary_Plus_D.txt");
  ifstream WToTauNu_cPlus_file("../EventSelection/ElectronLowPU/Ele_WToTauNu_S8_Analysis_Summary_Plus_C.txt");
  ifstream TTJets_aPlus_file("../EventSelection/ElectronLowPU/Ele_TTJets_S8_Analysis_Summary_Plus_A.txt");
  ifstream TTJets_bPlus_file("../EventSelection/ElectronLowPU/Ele_TTJets_S8_Analysis_Summary_Plus_B.txt");
  ifstream TTJets_dPlus_file("../EventSelection/ElectronLowPU/Ele_TTJets_S8_Analysis_Summary_Plus_D.txt");
  ifstream TTJets_cPlus_file("../EventSelection/ElectronLowPU/Ele_TTJets_S8_Analysis_Summary_Plus_C.txt");
  
  //Wplus Before and After recoil
  ifstream WpToEleNu_aPlus_file("../EventSelection/ElectronLowPU/Ele_WpToEleNu_S8_Analysis_Summary_Plus_A.txt");
  ifstream WpToEleNu_bPlus_file("../EventSelection/ElectronLowPU/Ele_WpToEleNu_S8_Analysis_Summary_Plus_B.txt");
  ifstream WpToEleNu_dPlus_file("../EventSelection/ElectronLowPU/Ele_WpToEleNu_S8_Analysis_Summary_Plus_D.txt");
  ifstream WpToEleNu_cPlus_file("../EventSelection/ElectronLowPU/Ele_WpToEleNu_S8_Analysis_Summary_Plus_C.txt");

  ifstream WpToEleNuRecoil_aPlus_file("../EventSelection/ElectronLowPU/Ele_WpToEleNu_S8_RecoilCorrMC_Summary_Plus_A.txt");
  ifstream WpToEleNuRecoil_bPlus_file("../EventSelection/ElectronLowPU/Ele_WpToEleNu_S8_RecoilCorrMC_Summary_Plus_B.txt");
  ifstream WpToEleNuRecoil_dPlus_file("../EventSelection/ElectronLowPU/Ele_WpToEleNu_S8_RecoilCorrMC_Summary_Plus_D.txt");
  ifstream WpToEleNuRecoil_cPlus_file("../EventSelection/ElectronLowPU/Ele_WpToEleNu_S8_RecoilCorrMC_Summary_Plus_C.txt");

  //=================== W - =============================
  // RD
  ifstream RDaMinus_file("../EventSelection/ElectronLowPU/Ele_RD_LowPU_Analysis_Summary_Minus_A.txt");
  ifstream RDbMinus_file("../EventSelection/ElectronLowPU/Ele_RD_LowPU_Analysis_Summary_Minus_B.txt");
  ifstream RDdMinus_file("../EventSelection/ElectronLowPU/Ele_RD_LowPU_Analysis_Summary_Minus_D.txt");
  ifstream RDcMinus_file("../EventSelection/ElectronLowPU/Ele_RD_LowPU_Analysis_Summary_Minus_C.txt");

  //EWK
  ifstream DYToEEaMinus_file("../EventSelection/ElectronLowPU/Ele_DYToEE_S8_Analysis_Summary_Minus_A.txt");
  ifstream DYToEEbMinus_file("../EventSelection/ElectronLowPU/Ele_DYToEE_S8_Analysis_Summary_Minus_B.txt");
  ifstream DYToEEdMinus_file("../EventSelection/ElectronLowPU/Ele_DYToEE_S8_Analysis_Summary_Minus_D.txt");
  ifstream DYToEEcMinus_file("../EventSelection/ElectronLowPU/Ele_DYToEE_S8_Analysis_Summary_Minus_C.txt");
  ifstream DYToTauTau_aMinus_file("../EventSelection/ElectronLowPU/Ele_DYToTauTau_S8_Analysis_Summary_Minus_A.txt");
  ifstream DYToTauTau_bMinus_file("../EventSelection/ElectronLowPU/Ele_DYToTauTau_S8_Analysis_Summary_Minus_B.txt");
  ifstream DYToTauTau_dMinus_file("../EventSelection/ElectronLowPU/Ele_DYToTauTau_S8_Analysis_Summary_Minus_D.txt");
  ifstream DYToTauTau_cMinus_file("../EventSelection/ElectronLowPU/Ele_DYToTauTau_S8_Analysis_Summary_Minus_C.txt");
  ifstream WToTauNu_aMinus_file("../EventSelection/ElectronLowPU/Ele_WToTauNu_S8_Analysis_Summary_Minus_A.txt");
  ifstream WToTauNu_bMinus_file("../EventSelection/ElectronLowPU/Ele_WToTauNu_S8_Analysis_Summary_Minus_B.txt");
  ifstream WToTauNu_dMinus_file("../EventSelection/ElectronLowPU/Ele_WToTauNu_S8_Analysis_Summary_Minus_D.txt");
  ifstream WToTauNu_cMinus_file("../EventSelection/ElectronLowPU/Ele_WToTauNu_S8_Analysis_Summary_Minus_C.txt");
  ifstream TTJets_aMinus_file("../EventSelection/ElectronLowPU/Ele_TTJets_S8_Analysis_Summary_Minus_A.txt");
  ifstream TTJets_bMinus_file("../EventSelection/ElectronLowPU/Ele_TTJets_S8_Analysis_Summary_Minus_B.txt");
  ifstream TTJets_dMinus_file("../EventSelection/ElectronLowPU/Ele_TTJets_S8_Analysis_Summary_Minus_D.txt");
  ifstream TTJets_cMinus_file("../EventSelection/ElectronLowPU/Ele_TTJets_S8_Analysis_Summary_Minus_C.txt");

  //Wminus Before and After recoil
  ifstream WmToEleNu_aMinus_file("../EventSelection/ElectronLowPU/Ele_WmToEleNu_S8_Analysis_Summary_Minus_A.txt");
  ifstream WmToEleNu_bMinus_file("../EventSelection/ElectronLowPU/Ele_WmToEleNu_S8_Analysis_Summary_Minus_B.txt");
  ifstream WmToEleNu_dMinus_file("../EventSelection/ElectronLowPU/Ele_WmToEleNu_S8_Analysis_Summary_Minus_D.txt");
  ifstream WmToEleNu_cMinus_file("../EventSelection/ElectronLowPU/Ele_WmToEleNu_S8_Analysis_Summary_Minus_C.txt");

  ifstream WmToEleNuRecoil_aMinus_file("../EventSelection/ElectronLowPU/Ele_WmToEleNu_S8_RecoilCorrMC_Summary_Minus_A.txt");
  ifstream WmToEleNuRecoil_bMinus_file("../EventSelection/ElectronLowPU/Ele_WmToEleNu_S8_RecoilCorrMC_Summary_Minus_B.txt");
  ifstream WmToEleNuRecoil_dMinus_file("../EventSelection/ElectronLowPU/Ele_WmToEleNu_S8_RecoilCorrMC_Summary_Minus_D.txt");
  ifstream WmToEleNuRecoil_cMinus_file("../EventSelection/ElectronLowPU/Ele_WmToEleNu_S8_RecoilCorrMC_Summary_Minus_C.txt");
  
  }
  ///======= W inclusive ===
  double RDaSignal[14];
  double RDaErr[14];
  double RDbSignal[14];
  double RDbErr[14];
  double RDdSignal[14];
  double RDdErr[14];
  double RDcSignal[14];
  double RDcErr[14];

  double DYToEEaSignal[14];
  double DYToEEaErr[14];
  double DYToEEbSignal[14];
  double DYToEEbErr[14];
  double DYToEEdSignal[14];
  double DYToEEdErr[14];
  double DYToEEcSignal[14];
  double DYToEEcErr[14];

  double DYToTauTau_aSignal[14];
  double DYToTauTau_aErr[14];
  double DYToTauTau_bSignal[14];
  double DYToTauTau_bErr[14];
  double DYToTauTau_dSignal[14];
  double DYToTauTau_dErr[14];
  double DYToTauTau_cSignal[14];
  double DYToTauTau_cErr[14];

  double WToTauNu_aSignal[14];
  double WToTauNu_aErr[14];
  double WToTauNu_bSignal[14];
  double WToTauNu_bErr[14];
  double WToTauNu_dSignal[14];
  double WToTauNu_dErr[14];
  double WToTauNu_cSignal[14];
  double WToTauNu_cErr[14];
  
  double TTJets_aSignal[14];
  double TTJets_aErr[14];
  double TTJets_bSignal[14];
  double TTJets_bErr[14];
  double TTJets_dSignal[14];
  double TTJets_dErr[14];
  double TTJets_cSignal[14];
  double TTJets_cErr[14];
  
  double WpToEleNu_aSignal[14];
  double WpToEleNu_aErr[14];
  double WpToEleNu_bSignal[14];
  double WpToEleNu_bErr[14];
  double WpToEleNu_dSignal[14];
  double WpToEleNu_dErr[14];
  double WpToEleNu_cSignal[14];
  double WpToEleNu_cErr[14];
  
  double WpToEleNuRecoil_aSignal[14];
  double WpToEleNuRecoil_aErr[14];
  double WpToEleNuRecoil_bSignal[14];
  double WpToEleNuRecoil_bErr[14];
  double WpToEleNuRecoil_dSignal[14];
  double WpToEleNuRecoil_dErr[14];
  double WpToEleNuRecoil_cSignal[14];
  double WpToEleNuRecoil_cErr[14];
  
  double WmToEleNu_aSignal[14];
  double WmToEleNu_aErr[14];
  double WmToEleNu_bSignal[14];
  double WmToEleNu_bErr[14];
  double WmToEleNu_dSignal[14];
  double WmToEleNu_dErr[14];
  double WmToEleNu_cSignal[14];
  double WmToEleNu_cErr[14];
  
  double WmToEleNuRecoil_aSignal[14];
  double WmToEleNuRecoil_aErr[14];
  double WmToEleNuRecoil_bSignal[14];
  double WmToEleNuRecoil_bErr[14];
  double WmToEleNuRecoil_dSignal[14];
  double WmToEleNuRecoil_dErr[14];
  double WmToEleNuRecoil_cSignal[14];
  double WmToEleNuRecoil_cErr[14];
  

  double EWKa[14];
  double EWKaErr[14];
  double EWKb[14];
  double EWKbErr[14];
  double EWKd[14];
  double EWKdErr[14];
  double EWKc[14];
  double EWKcErr[14];


  double RDPrime_aSignal[14];
  double RDPrime_aErr[14];
  double RDPrime_bSignal[14];
  double RDPrime_bErr[14];
  double RDPrime_dSignal[14];
  double RDPrime_dErr[14];
  double RDPrime_cSignal[14];
  double RDPrime_cErr[14];

  double Bcoeff[14];
  double BcoeffRecoil[14];
  double Ccoeff[14];
  double CcoeffRecoil[14];
  double Fz[14];
  double FzRecoil[14];  
  double Sab[14];  
  double SabRecoil[14];  
  

  ///======= W Plus ===
  double RDaPlusSignal[14];
  double RDaPlusErr[14];
  double RDbPlusSignal[14];
  double RDbPlusErr[14];
  double RDdPlusSignal[14];
  double RDdPlusErr[14];
  double RDcPlusSignal[14];
  double RDcPlusErr[14];

  double DYToEEaPlusSignal[14];
  double DYToEEaPlusErr[14];
  double DYToEEbPlusSignal[14];
  double DYToEEbPlusErr[14];
  double DYToEEdPlusSignal[14];
  double DYToEEdPlusErr[14];
  double DYToEEcPlusSignal[14];
  double DYToEEcPlusErr[14];

  double DYToTauTau_aPlusSignal[14];
  double DYToTauTau_aPlusErr[14];
  double DYToTauTau_bPlusSignal[14];
  double DYToTauTau_bPlusErr[14];
  double DYToTauTau_dPlusSignal[14];
  double DYToTauTau_dPlusErr[14];
  double DYToTauTau_cPlusSignal[14];
  double DYToTauTau_cPlusErr[14];

  double WToTauNu_aPlusSignal[14];
  double WToTauNu_aPlusErr[14];
  double WToTauNu_bPlusSignal[14];
  double WToTauNu_bPlusErr[14];
  double WToTauNu_dPlusSignal[14];
  double WToTauNu_dPlusErr[14];
  double WToTauNu_cPlusSignal[14];
  double WToTauNu_cPlusErr[14];
  
  double TTJets_aPlusSignal[14];
  double TTJets_aPlusErr[14];
  double TTJets_bPlusSignal[14];
  double TTJets_bPlusErr[14];
  double TTJets_dPlusSignal[14];
  double TTJets_dPlusErr[14];
  double TTJets_cPlusSignal[14];
  double TTJets_cPlusErr[14];
 

  double WpToEleNu_aPlusSignal[14];
  double WpToEleNu_aPlusErr[14];
  double WpToEleNu_bPlusSignal[14];
  double WpToEleNu_bPlusErr[14];
  double WpToEleNu_dPlusSignal[14];
  double WpToEleNu_dPlusErr[14];
  double WpToEleNu_cPlusSignal[14];
  double WpToEleNu_cPlusErr[14];

  double WpToEleNuRecoil_aPlusSignal[14];
  double WpToEleNuRecoil_aPlusErr[14];
  double WpToEleNuRecoil_bPlusSignal[14];
  double WpToEleNuRecoil_bPlusErr[14];
  double WpToEleNuRecoil_dPlusSignal[14];
  double WpToEleNuRecoil_dPlusErr[14];
  double WpToEleNuRecoil_cPlusSignal[14];
  double WpToEleNuRecoil_cPlusErr[14];

  double EWKaPlus[14];
  double EWKaPlusErr[14];
  double EWKbPlus[14];
  double EWKbPlusErr[14];
  double EWKdPlus[14];
  double EWKdPlusErr[14];
  double EWKcPlus[14];
  double EWKcPlusErr[14];
 

  double BcoeffPlus[14];
  double BcoeffRecoilPlus[14];
  double CcoeffPlus[14];
  double CcoeffRecoilPlus[14];
  double FzPlus[14];
  double FzRecoilPlus[14];  
  double SabPlus[14];  
  double SabRecoilPlus[14];  


  ///======= W Minus ===
  double RDaMinusSignal[14];
  double RDaMinusErr[14];
  double RDbMinusSignal[14];
  double RDbMinusErr[14];
  double RDdMinusSignal[14];
  double RDdMinusErr[14];
  double RDcMinusSignal[14];
  double RDcMinusErr[14];

  double DYToEEaMinusSignal[14];
  double DYToEEaMinusErr[14];
  double DYToEEbMinusSignal[14];
  double DYToEEbMinusErr[14];
  double DYToEEdMinusSignal[14];
  double DYToEEdMinusErr[14];
  double DYToEEcMinusSignal[14];
  double DYToEEcMinusErr[14];

  double DYToTauTau_aMinusSignal[14];
  double DYToTauTau_aMinusErr[14];
  double DYToTauTau_bMinusSignal[14];
  double DYToTauTau_bMinusErr[14];
  double DYToTauTau_dMinusSignal[14];
  double DYToTauTau_dMinusErr[14];
  double DYToTauTau_cMinusSignal[14];
  double DYToTauTau_cMinusErr[14];

  double WToTauNu_aMinusSignal[14];
  double WToTauNu_aMinusErr[14];
  double WToTauNu_bMinusSignal[14];
  double WToTauNu_bMinusErr[14];
  double WToTauNu_dMinusSignal[14];
  double WToTauNu_dMinusErr[14];
  double WToTauNu_cMinusSignal[14];
  double WToTauNu_cMinusErr[14];
  
  double TTJets_aMinusSignal[14];
  double TTJets_aMinusErr[14];
  double TTJets_bMinusSignal[14];
  double TTJets_bMinusErr[14];
  double TTJets_dMinusSignal[14];
  double TTJets_dMinusErr[14];
  double TTJets_cMinusSignal[14];
  double TTJets_cMinusErr[14];
 

  double WmToEleNu_aMinusSignal[14];
  double WmToEleNu_aMinusErr[14];
  double WmToEleNu_bMinusSignal[14];
  double WmToEleNu_bMinusErr[14];
  double WmToEleNu_dMinusSignal[14];
  double WmToEleNu_dMinusErr[14];
  double WmToEleNu_cMinusSignal[14];
  double WmToEleNu_cMinusErr[14];

  double WmToEleNuRecoil_aMinusSignal[14];
  double WmToEleNuRecoil_aMinusErr[14];
  double WmToEleNuRecoil_bMinusSignal[14];
  double WmToEleNuRecoil_bMinusErr[14];
  double WmToEleNuRecoil_dMinusSignal[14];
  double WmToEleNuRecoil_dMinusErr[14];
  double WmToEleNuRecoil_cMinusSignal[14];
  double WmToEleNuRecoil_cMinusErr[14];

  double EWKaMinus[14];
  double EWKaMinusErr[14];
  double EWKbMinus[14];
  double EWKbMinusErr[14];
  double EWKdMinus[14];
  double EWKdMinusErr[14];
  double EWKcMinus[14];
  double EWKcMinusErr[14];
 

  double BcoeffMinus[14];
  double BcoeffRecoilMinus[14];
  double CcoeffMinus[14];
  double CcoeffRecoilMinus[14];
  double FzMinus[14];
  double FzRecoilMinus[14];  
  double SabMinus[14];  
  double SabRecoilMinus[14];  


  double I=0.9767;  
  double IPlus=0.9767;  
  double IMinus=0.9767;  
 // double I=0.9577;
 // double IPlus=0.9577;  
 // double IMinus=0.9577;  


  TString tmp;
  int bins;


  int bin = 0;

  
  ///////  W Inclusive  /////////

//RD
   cout << "*********RDa*********"  << endl;
  while(RDa_file >> tmp >> bins >> tmp >> RDaSignal[bin] >> tmp >> RDaErr[bin])
    {
     cout << bins << "\t" << RDaSignal[bin] << "\t" << RDaErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }

  bin = 0;
   cout << "*********RDb*********"  << endl;
  while(RDb_file >> tmp >> bins >> tmp >> RDbSignal[bin] >> tmp >> RDbErr[bin])
    {
     cout << bins << "\t" << RDbSignal[bin] << "\t" << RDbErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }
  bin = 0;
  cout << "*********RDd*********"  << endl;
  while(RDd_file >> tmp >> bins >> tmp >> RDdSignal[bin] >> tmp >> RDdErr[bin])
    {
     cout << bins << "\t" << RDdSignal[bin] << "\t" << RDdErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }
  bin = 0;
   cout << "*********RDc*********"  << endl;
  while(RDc_file >> tmp >> bins >> tmp >> RDcSignal[bin] >> tmp >> RDcErr[bin])
    {
     cout << bins << "\t" << RDcSignal[bin] << "\t" << RDcErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }


//DYToEE

  bin = 0;
  cout << "*********DYToEEa*********"  << endl;
  while(DYToEEa_file >> tmp >> bins >> tmp >> DYToEEaSignal[bin] >> tmp >> DYToEEaErr[bin])
    {
     cout << bins << "\t" << DYToEEaSignal[bin] << "\t" << DYToEEaErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }
  bin = 0;
   cout << "*********DYToEEb*********"  << endl;
  while(DYToEEb_file >> tmp >> bins >> tmp >> DYToEEbSignal[bin] >> tmp >> DYToEEbErr[bin])
    {
     cout << bins << "\t" << DYToEEbSignal[bin] << "\t" << DYToEEbErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }
  bin = 0;
   cout << "*********DYToEEd*********"  << endl;
  while(DYToEEd_file >> tmp >> bins >> tmp >> DYToEEdSignal[bin] >> tmp >> DYToEEdErr[bin])
    {
     cout << bins << "\t" << DYToEEdSignal[bin] << "\t" << DYToEEdErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }
  bin = 0;
   cout << "*********DYToEEc*********"  << endl;
  while(DYToEEc_file >> tmp >> bins >> tmp >> DYToEEcSignal[bin] >> tmp >> DYToEEcErr[bin])
    {
     cout << bins << "\t" << DYToEEcSignal[bin] << "\t" << DYToEEcErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }

//DYToTauTau

  bin = 0;
  cout << "*********DYToTauTau_a*********"  << endl;
  while(DYToTauTau_a_file >> tmp >> bins >> tmp >> DYToTauTau_aSignal[bin] >> tmp >> DYToTauTau_aErr[bin])
    {
     cout << bins << "\t" << DYToTauTau_aSignal[bin] << "\t" << DYToTauTau_aErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }
  bin = 0;
   cout << "*********DYToTauTau_b*********"  << endl;
  while(DYToTauTau_b_file >> tmp >> bins >> tmp >> DYToTauTau_bSignal[bin] >> tmp >> DYToTauTau_bErr[bin])
    {
     cout << bins << "\t" << DYToTauTau_bSignal[bin] << "\t" << DYToTauTau_bErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }
  bin = 0;
   cout << "*********DYToTauTau_d*********"  << endl;
  while(DYToTauTau_d_file >> tmp >> bins >> tmp >> DYToTauTau_dSignal[bin] >> tmp >> DYToTauTau_dErr[bin])
    {
     cout << bins << "\t" << DYToTauTau_dSignal[bin] << "\t" << DYToTauTau_dErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }
  bin = 0;
   cout << "*********DYToTauTau_c*********"  << endl;
  while(DYToTauTau_c_file >> tmp >> bins >> tmp >> DYToTauTau_cSignal[bin] >> tmp >> DYToTauTau_cErr[bin])
    {
     cout << bins << "\t" << DYToTauTau_cSignal[bin] << "\t" << DYToTauTau_cErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }

//WToTauNu

  bin = 0;
  cout << "*********WToTauNu_a*********"  << endl;
  while(WToTauNu_a_file >> tmp >> bins >> tmp >> WToTauNu_aSignal[bin] >> tmp >> WToTauNu_aErr[bin])
    {
     cout << bins << "\t" << WToTauNu_aSignal[bin] << "\t" << WToTauNu_aErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }
  bin = 0;
   cout << "*********WToTauNu_b*********"  << endl;
  while(WToTauNu_b_file >> tmp >> bins >> tmp >> WToTauNu_bSignal[bin] >> tmp >> WToTauNu_bErr[bin])
    {
     cout << bins << "\t" << WToTauNu_bSignal[bin] << "\t" << WToTauNu_bErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }
  bin = 0;
   cout << "*********WToTauNu_d*********"  << endl;
  while(WToTauNu_d_file >> tmp >> bins >> tmp >> WToTauNu_dSignal[bin] >> tmp >> WToTauNu_dErr[bin])
    {
     cout << bins << "\t" << WToTauNu_dSignal[bin] << "\t" << WToTauNu_dErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }
  bin = 0;
   cout << "*********WToTauNu_c*********"  << endl;
  while(WToTauNu_c_file >> tmp >> bins >> tmp >> WToTauNu_cSignal[bin] >> tmp >> WToTauNu_cErr[bin])
    {
     cout << bins << "\t" << WToTauNu_cSignal[bin] << "\t" << WToTauNu_cErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }

//TTJets

  bin = 0;
  cout << "*********TTJets_a*********"  << endl;
  while(TTJets_a_file >> tmp >> bins >> tmp >> TTJets_aSignal[bin] >> tmp >> TTJets_aErr[bin])
    {
     cout << bins << "\t" << TTJets_aSignal[bin] << "\t" << TTJets_aErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }
  bin = 0;
   cout << "*********TTJets_b*********"  << endl;
  while(TTJets_b_file >> tmp >> bins >> tmp >> TTJets_bSignal[bin] >> tmp >> TTJets_bErr[bin])
    {
     cout << bins << "\t" << TTJets_bSignal[bin] << "\t" << TTJets_bErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }
  bin = 0;
   cout << "*********TTJets_d*********"  << endl;
  while(TTJets_d_file >> tmp >> bins >> tmp >> TTJets_dSignal[bin] >> tmp >> TTJets_dErr[bin])
    {
     cout << bins << "\t" << TTJets_dSignal[bin] << "\t" << TTJets_dErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }
  bin = 0;
   cout << "*********TTJets_c*********"  << endl;
  while(TTJets_c_file >> tmp >> bins >> tmp >> TTJets_cSignal[bin] >> tmp >> TTJets_cErr[bin])
    {
     cout << bins << "\t" << TTJets_cSignal[bin] << "\t" << TTJets_cErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }

//WpToEleNu before recoil

  bin = 0;
  cout << "*********WpToEleNu_a*********"  << endl;
  while(WpToEleNu_a_file >> tmp >> bins >> tmp >> WpToEleNu_aSignal[bin] >> tmp >> WpToEleNu_aErr[bin])
    {
     cout << bins << "\t" << WpToEleNu_aSignal[bin] << "\t" << WpToEleNu_aErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }
  bin = 0;
   cout << "*********WpToEleNu_b*********"  << endl;
  while(WpToEleNu_b_file >> tmp >> bins >> tmp >> WpToEleNu_bSignal[bin] >> tmp >> WpToEleNu_bErr[bin])
    {
     cout << bins << "\t" << WpToEleNu_bSignal[bin] << "\t" << WpToEleNu_bErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }
  bin = 0;
   cout << "*********WpToEleNu_d*********"  << endl;
  while(WpToEleNu_d_file >> tmp >> bins >> tmp >> WpToEleNu_dSignal[bin] >> tmp >> WpToEleNu_dErr[bin])
    {
     cout << bins << "\t" << WpToEleNu_dSignal[bin] << "\t" << WpToEleNu_dErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }
  bin = 0;
   cout << "*********WpToEleNu_c*********"  << endl;
  while(WpToEleNu_c_file >> tmp >> bins >> tmp >> WpToEleNu_cSignal[bin] >> tmp >> WpToEleNu_cErr[bin])
    {
     cout << bins << "\t" << WpToEleNu_cSignal[bin] << "\t" << WpToEleNu_cErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }

//WpToEleNu after recoil
  
  bin = 0;
  cout << "*********WpToEleNuRecoil_a*********"  << endl;
  while(WpToEleNuRecoil_a_file >> tmp >> bins >> tmp >> WpToEleNuRecoil_aSignal[bin] >> tmp >> WpToEleNuRecoil_aErr[bin])
    {
     cout << bins << "\t" << WpToEleNuRecoil_aSignal[bin] << "\t" << WpToEleNuRecoil_aErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }
  bin = 0;
   cout << "*********WpToEleNuRecoil_b*********"  << endl;
  while(WpToEleNuRecoil_b_file >> tmp >> bins >> tmp >> WpToEleNuRecoil_bSignal[bin] >> tmp >> WpToEleNuRecoil_bErr[bin])
    {
     cout << bins << "\t" << WpToEleNuRecoil_bSignal[bin] << "\t" << WpToEleNuRecoil_bErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }
  bin = 0;
   cout << "*********WpToEleNuRecoil_d*********"  << endl;
  while(WpToEleNuRecoil_d_file >> tmp >> bins >> tmp >> WpToEleNuRecoil_dSignal[bin] >> tmp >> WpToEleNuRecoil_dErr[bin])
    {
     cout << bins << "\t" << WpToEleNuRecoil_dSignal[bin] << "\t" << WpToEleNuRecoil_dErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }
  bin = 0;
   cout << "*********WpToEleNuRecoil_c*********"  << endl;
  while(WpToEleNuRecoil_c_file >> tmp >> bins >> tmp >> WpToEleNuRecoil_cSignal[bin] >> tmp >> WpToEleNuRecoil_cErr[bin])
    {
     cout << bins << "\t" << WpToEleNu_cSignal[bin] << "\t" << WpToEleNu_cErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }



//WmToEleNu before recoil

  bin = 0;
  cout << "*********WmToEleNu_a*********"  << endl;
  while(WmToEleNu_a_file >> tmp >> bins >> tmp >> WmToEleNu_aSignal[bin] >> tmp >> WmToEleNu_aErr[bin])
    {
     cout << bins << "\t" << WmToEleNu_aSignal[bin] << "\t" << WmToEleNu_aErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }
  bin = 0;
   cout << "*********WmToEleNu_b*********"  << endl;
  while(WmToEleNu_b_file >> tmp >> bins >> tmp >> WmToEleNu_bSignal[bin] >> tmp >> WmToEleNu_bErr[bin])
    {
     cout << bins << "\t" << WmToEleNu_bSignal[bin] << "\t" << WmToEleNu_bErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }
  bin = 0;
   cout << "*********WmToEleNu_d*********"  << endl;
  while(WmToEleNu_d_file >> tmp >> bins >> tmp >> WmToEleNu_dSignal[bin] >> tmp >> WmToEleNu_dErr[bin])
    {
     cout << bins << "\t" << WmToEleNu_dSignal[bin] << "\t" << WmToEleNu_dErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }
  bin = 0;
   cout << "*********WmToEleNu_c*********"  << endl;
  while(WmToEleNu_c_file >> tmp >> bins >> tmp >> WmToEleNu_cSignal[bin] >> tmp >> WmToEleNu_cErr[bin])
    {
     cout << bins << "\t" << WmToEleNu_cSignal[bin] << "\t" << WmToEleNu_cErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }

//WmToEleNu after recoil
  
  bin = 0;
  cout << "*********WmToEleNuRecoil_a*********"  << endl;
  while(WmToEleNuRecoil_a_file >> tmp >> bins >> tmp >> WmToEleNuRecoil_aSignal[bin] >> tmp >> WmToEleNuRecoil_aErr[bin])
    {
     cout << bins << "\t" << WmToEleNuRecoil_aSignal[bin] << "\t" << WmToEleNuRecoil_aErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }
  bin = 0;
   cout << "*********WmToEleNuRecoil_b*********"  << endl;
  while(WmToEleNuRecoil_b_file >> tmp >> bins >> tmp >> WmToEleNuRecoil_bSignal[bin] >> tmp >> WmToEleNuRecoil_bErr[bin])
    {
     cout << bins << "\t" << WmToEleNuRecoil_bSignal[bin] << "\t" << WmToEleNuRecoil_bErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }
  bin = 0;
   cout << "*********WmToEleNuRecoil_d*********"  << endl;
  while(WmToEleNuRecoil_d_file >> tmp >> bins >> tmp >> WmToEleNuRecoil_dSignal[bin] >> tmp >> WmToEleNuRecoil_dErr[bin])
    {
     cout << bins << "\t" << WmToEleNuRecoil_dSignal[bin] << "\t" << WmToEleNuRecoil_dErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }
  bin = 0;
   cout << "*********WmToEleNuRecoil_c*********"  << endl;
  while(WmToEleNuRecoil_c_file >> tmp >> bins >> tmp >> WmToEleNuRecoil_cSignal[bin] >> tmp >> WmToEleNuRecoil_cErr[bin])
    {
     cout << bins << "\t" << WmToEleNu_cSignal[bin] << "\t" << WmToEleNu_cErr[bin] << endl;
   bin++;
   if(bin==14)break;
    }



//Signal calculations
 
  Fout << "" << "\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t" << "" << endl;
  Fout << "********* W inclusive Signal calculation *********" << endl;
  Fout << "" << "\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t" << "" << endl;
  Fout << "Bin" << "\t" << "Fz " << "\t\t" << "Sa+Sb" << "\t\t" << "Fz Recoil" << "\t" << "Sa+Sb Recoil" << endl;
  Fout << "" << "\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t" << "" << endl;
  for(int i(0); i<14; i++)
 {
         
   
   
  EWKa[i]= DYToEEaSignal[i] + DYToTauTau_aSignal[i] + WToTauNu_aSignal[i] + TTJets_aSignal[i];
  EWKaErr[i]=sqrt( DYToEEaErr[i]*DYToEEaErr[i] + DYToTauTau_aErr[i]*DYToTauTau_aErr[i] + WToTauNu_aErr[i]*WToTauNu_aErr[i] + TTJets_aErr[i]*TTJets_aErr[i] );

  EWKb[i]= DYToEEbSignal[i] + DYToTauTau_bSignal[i] + WToTauNu_bSignal[i] + TTJets_bSignal[i];
  EWKbErr[i]=sqrt( DYToEEbErr[i]*DYToEEbErr[i] + DYToTauTau_bErr[i]*DYToTauTau_bErr[i] + WToTauNu_bErr[i]*WToTauNu_bErr[i] + TTJets_bErr[i]*TTJets_bErr[i] );

  EWKd[i]= DYToEEdSignal[i] + DYToTauTau_dSignal[i] + WToTauNu_dSignal[i] + TTJets_dSignal[i];
  EWKdErr[i]=sqrt( DYToEEdErr[i]*DYToEEdErr[i] + DYToTauTau_dErr[i]*DYToTauTau_dErr[i] + WToTauNu_dErr[i]*WToTauNu_dErr[i] + TTJets_dErr[i]*TTJets_dErr[i] );
  
  EWKc[i]= DYToEEcSignal[i] + DYToTauTau_cSignal[i] + WToTauNu_cSignal[i] + TTJets_cSignal[i];
  EWKcErr[i]=sqrt( DYToEEcErr[i]*DYToEEcErr[i] + DYToTauTau_cErr[i]*DYToTauTau_cErr[i] + WToTauNu_cErr[i]*WToTauNu_cErr[i] + TTJets_cErr[i]*TTJets_cErr[i] );
   
  
  RDPrime_aSignal[i]=RDaSignal[i]-EWKa[i];
  RDPrime_aErr[i]=sqrt(RDaErr[i]*RDaErr[i] + EWKaErr[i]*EWKaErr[i]);

  RDPrime_bSignal[i]=RDbSignal[i]-EWKb[i];
  RDPrime_bErr[i]=sqrt(RDbErr[i]*RDbErr[i] + EWKbErr[i]*EWKbErr[i]);

  RDPrime_dSignal[i]=RDdSignal[i]-EWKd[i];
  RDPrime_dErr[i]=sqrt(RDdErr[i]*RDdErr[i] + EWKdErr[i]*EWKdErr[i]);

  RDPrime_cSignal[i]=RDcSignal[i]-EWKc[i];
  RDPrime_cErr[i]=sqrt(RDcErr[i]*RDcErr[i] + EWKcErr[i]*EWKcErr[i]);
  
  
  
  Fz[i]=(WpToEleNu_aSignal[i]+WmToEleNu_aSignal[i])/(WpToEleNu_bSignal[i]+WmToEleNu_bSignal[i]);
  FzRecoil[i]=(WpToEleNuRecoil_aSignal[i]+WmToEleNuRecoil_aSignal[i])/(WpToEleNuRecoil_bSignal[i]+WmToEleNuRecoil_bSignal[i]);
  
  Bcoeff[i]=I*(Fz[i]+1.0)*(Fz[i]*RDPrime_cSignal[i]-RDPrime_dSignal[i]) + (1.0+Fz[i])*(1.0-I)*(RDPrime_aSignal[i]- Fz[i]*RDPrime_bSignal[i]);
  BcoeffRecoil[i]=I*(FzRecoil[i]+1.0)*(FzRecoil[i]*RDPrime_cSignal[i]-RDPrime_dSignal[i]) + (1.0+FzRecoil[i])*(1.0-I)*(RDPrime_aSignal[i]- FzRecoil[i]*RDPrime_bSignal[i]);


  Ccoeff[i]=I*(Fz[i]+1.0)*(Fz[i]+1.0)*(RDPrime_dSignal[i]*RDPrime_bSignal[i]-RDPrime_aSignal[i]*RDPrime_cSignal[i]);
  CcoeffRecoil[i]=I*(FzRecoil[i]+1.0)*(FzRecoil[i]+1.0)*(RDPrime_dSignal[i]*RDPrime_bSignal[i]-RDPrime_aSignal[i]*RDPrime_cSignal[i]);
 
  Sab[i]=-Ccoeff[i]/Bcoeff[i];

  SabRecoil[i]=-CcoeffRecoil[i]/BcoeffRecoil[i];
 


  Fout << i << "\t" << Fz[i] << "\t\t" << Sab[i] << "\t\t"<< FzRecoil[i] << "\t\t" << SabRecoil[i] << endl;
  //Fout << "" << "\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t" << "" << endl;
 
 }



// ==========  W  Plus  /////////

//RD

  bin = 0;
  cout << "*********RDa*********"  << endl;
  while(RDaPlus_file >> tmp >> bins >> tmp >> RDaPlusSignal[bin] >> tmp >> RDaPlusErr[bin])
    {
     cout << bins << "\t" << RDaPlusSignal[bin] << "\t" << RDaPlusErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }

  bin = 0;
   cout << "*********RDb*********"  << endl;
  while(RDbPlus_file >> tmp >> bins >> tmp >> RDbPlusSignal[bin] >> tmp >> RDbPlusErr[bin])
    {
     cout << bins << "\t" << RDbPlusSignal[bin] << "\t" << RDbPlusErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }
  bin = 0;
  cout << "*********RDd*********"  << endl;
  while(RDdPlus_file >> tmp >> bins >> tmp >> RDdPlusSignal[bin] >> tmp >> RDdPlusErr[bin])
    {
     cout << bins << "\t" << RDdPlusSignal[bin] << "\t" << RDdPlusErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }
  bin = 0;
   cout << "*********RDc*********"  << endl;
  while(RDcPlus_file >> tmp >> bins >> tmp >> RDcPlusSignal[bin] >> tmp >> RDcPlusErr[bin])
    {
     cout << bins << "\t" << RDcPlusSignal[bin] << "\t" << RDcPlusErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }


//DYToEE

  bin = 0;
  cout << "*********DYToEEa*********"  << endl;
  while(DYToEEaPlus_file >> tmp >> bins >> tmp >> DYToEEaPlusSignal[bin] >> tmp >> DYToEEaPlusErr[bin])
    {
     cout << bins << "\t" << DYToEEaPlusSignal[bin] << "\t" << DYToEEaPlusErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }
  bin = 0;
   cout << "*********DYToEEb*********"  << endl;
  while(DYToEEbPlus_file >> tmp >> bins >> tmp >> DYToEEbPlusSignal[bin] >> tmp >> DYToEEbPlusErr[bin])
    {
     cout << bins << "\t" << DYToEEbPlusSignal[bin] << "\t" << DYToEEbPlusErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }
  bin = 0;
   cout << "*********DYToEEd*********"  << endl;
  while(DYToEEdPlus_file >> tmp >> bins >> tmp >> DYToEEdPlusSignal[bin] >> tmp >> DYToEEdPlusErr[bin])
    {
     cout << bins << "\t" << DYToEEdPlusSignal[bin] << "\t" << DYToEEdPlusErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }
  bin = 0;
   cout << "*********DYToEEc*********"  << endl;
  while(DYToEEcPlus_file >> tmp >> bins >> tmp >> DYToEEcPlusSignal[bin] >> tmp >> DYToEEcPlusErr[bin])
    {
     cout << bins << "\t" << DYToEEcPlusSignal[bin] << "\t" << DYToEEcPlusErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }

//DYToTauTau

  bin = 0;
  cout << "*********DYToTauTau_a*********"  << endl;
  while(DYToTauTau_aPlus_file >> tmp >> bins >> tmp >> DYToTauTau_aPlusSignal[bin] >> tmp >> DYToTauTau_aPlusErr[bin])
    {
     cout << bins << "\t" << DYToTauTau_aPlusSignal[bin] << "\t" << DYToTauTau_aPlusErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }
  bin = 0;
   cout << "*********DYToTauTau_b*********"  << endl;
  while(DYToTauTau_bPlus_file >> tmp >> bins >> tmp >> DYToTauTau_bPlusSignal[bin] >> tmp >> DYToTauTau_bPlusErr[bin])
    {
     cout << bins << "\t" << DYToTauTau_bPlusSignal[bin] << "\t" << DYToTauTau_bPlusErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }
  bin = 0;
   cout << "*********DYToTauTau_d*********"  << endl;
  while(DYToTauTau_dPlus_file >> tmp >> bins >> tmp >> DYToTauTau_dPlusSignal[bin] >> tmp >> DYToTauTau_dPlusErr[bin])
    {
     cout << bins << "\t" << DYToTauTau_dPlusSignal[bin] << "\t" << DYToTauTau_dPlusErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }
  bin = 0;
   cout << "*********DYToTauTau_c*********"  << endl;
  while(DYToTauTau_cPlus_file >> tmp >> bins >> tmp >> DYToTauTau_cPlusSignal[bin] >> tmp >> DYToTauTau_cPlusErr[bin])
    {
     cout << bins << "\t" << DYToTauTau_cPlusSignal[bin] << "\t" << DYToTauTau_cPlusErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }

//WToTauNu

  bin = 0;
  cout << "*********WToTauNu_a*********"  << endl;
  while(WToTauNu_aPlus_file >> tmp >> bins >> tmp >> WToTauNu_aPlusSignal[bin] >> tmp >> WToTauNu_aPlusErr[bin])
    {
     cout << bins << "\t" << WToTauNu_aPlusSignal[bin] << "\t" << WToTauNu_aPlusErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }
  bin = 0;
   cout << "*********WToTauNu_b*********"  << endl;
  while(WToTauNu_bPlus_file >> tmp >> bins >> tmp >> WToTauNu_bPlusSignal[bin] >> tmp >> WToTauNu_bPlusErr[bin])
    {
     cout << bins << "\t" << WToTauNu_bPlusSignal[bin] << "\t" << WToTauNu_bPlusErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }
  bin = 0;
   cout << "*********WToTauNu_d*********"  << endl;
  while(WToTauNu_dPlus_file >> tmp >> bins >> tmp >> WToTauNu_dPlusSignal[bin] >> tmp >> WToTauNu_dPlusErr[bin])
    {
     cout << bins << "\t" << WToTauNu_dPlusSignal[bin] << "\t" << WToTauNu_dPlusErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }
  bin = 0;
   cout << "*********WToTauNu_c*********"  << endl;
  while(WToTauNu_cPlus_file >> tmp >> bins >> tmp >> WToTauNu_cPlusSignal[bin] >> tmp >> WToTauNu_cPlusErr[bin])
    {
     cout << bins << "\t" << WToTauNu_cPlusSignal[bin] << "\t" << WToTauNu_cPlusErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }

//TTJets

  bin = 0;
  cout << "*********TTJets_a*********"  << endl;
  while(TTJets_aPlus_file >> tmp >> bins >> tmp >> TTJets_aPlusSignal[bin] >> tmp >> TTJets_aPlusErr[bin])
    {
     cout << bins << "\t" << TTJets_aPlusSignal[bin] << "\t" << TTJets_aPlusErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }
  bin = 0;
   cout << "*********TTJets_b*********"  << endl;
  while(TTJets_bPlus_file >> tmp >> bins >> tmp >> TTJets_bPlusSignal[bin] >> tmp >> TTJets_bPlusErr[bin])
    {
     cout << bins << "\t" << TTJets_bPlusSignal[bin] << "\t" << TTJets_bPlusErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }
  bin = 0;
   cout << "*********TTJets_d*********"  << endl;
  while(TTJets_dPlus_file >> tmp >> bins >> tmp >> TTJets_dPlusSignal[bin] >> tmp >> TTJets_dPlusErr[bin])
    {
     cout << bins << "\t" << TTJets_dPlusSignal[bin] << "\t" << TTJets_dPlusErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }
  bin = 0;
   cout << "*********TTJets_c*********"  << endl;
  while(TTJets_cPlus_file >> tmp >> bins >> tmp >> TTJets_cPlusSignal[bin] >> tmp >> TTJets_cPlusErr[bin])
    {
     cout << bins << "\t" << TTJets_cPlusSignal[bin] << "\t" << TTJets_cPlusErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }

//WpToEleNu before recoil

  bin = 0;
  cout << "*********WpToEleNu_a*********"  << endl;
  while(WpToEleNu_aPlus_file >> tmp >> bins >> tmp >> WpToEleNu_aPlusSignal[bin] >> tmp >> WpToEleNu_aPlusErr[bin])
    {
     cout << bins << "\t" << WpToEleNu_aPlusSignal[bin] << "\t" << WpToEleNu_aPlusErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }
  bin = 0;
   cout << "*********WpToEleNu_b*********"  << endl;
  while(WpToEleNu_bPlus_file >> tmp >> bins >> tmp >> WpToEleNu_bPlusSignal[bin] >> tmp >> WpToEleNu_bPlusErr[bin])
    {
     cout << bins << "\t" << WpToEleNu_bPlusSignal[bin] << "\t" << WpToEleNu_bPlusErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }
  bin = 0;
   cout << "*********WpToEleNu_d*********"  << endl;
  while(WpToEleNu_dPlus_file >> tmp >> bins >> tmp >> WpToEleNu_dPlusSignal[bin] >> tmp >> WpToEleNu_dPlusErr[bin])
    {
     cout << bins << "\t" << WpToEleNu_dPlusSignal[bin] << "\t" << WpToEleNu_dPlusErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }
  bin = 0;
   cout << "*********WpToEleNu_c*********"  << endl;
  while(WpToEleNu_cPlus_file >> tmp >> bins >> tmp >> WpToEleNu_cPlusSignal[bin] >> tmp >> WpToEleNu_cPlusErr[bin])
    {
     cout << bins << "\t" << WpToEleNu_cPlusSignal[bin] << "\t" << WpToEleNu_cPlusErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }

//WpToEleNu after recoil
  
  bin = 0;
  cout << "*********WpToEleNuRecoil_a*********"  << endl;
  while(WpToEleNuRecoil_aPlus_file >> tmp >> bins >> tmp >> WpToEleNuRecoil_aPlusSignal[bin] >> tmp >> WpToEleNuRecoil_aPlusErr[bin])
    {
     cout << bins << "\t" << WpToEleNuRecoil_aPlusSignal[bin] << "\t" << WpToEleNuRecoil_aPlusErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }
  bin = 0;
   cout << "*********WpToEleNuRecoil_b*********"  << endl;
  while(WpToEleNuRecoil_bPlus_file >> tmp >> bins >> tmp >> WpToEleNuRecoil_bPlusSignal[bin] >> tmp >> WpToEleNuRecoil_bPlusErr[bin])
    {
     cout << bins << "\t" << WpToEleNuRecoil_bPlusSignal[bin] << "\t" << WpToEleNuRecoil_bPlusErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }
  bin = 0;
   cout << "*********WpToEleNuRecoil_d*********"  << endl;
  while(WpToEleNuRecoil_dPlus_file >> tmp >> bins >> tmp >> WpToEleNuRecoil_dPlusSignal[bin] >> tmp >> WpToEleNuRecoil_dPlusErr[bin])
    {
     cout << bins << "\t" << WpToEleNuRecoil_dPlusSignal[bin] << "\t" << WpToEleNuRecoil_dPlusErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }
  bin = 0;
   cout << "*********WpToEleNuRecoil_c*********"  << endl;
  while(WpToEleNuRecoil_cPlus_file >> tmp >> bins >> tmp >> WpToEleNuRecoil_cPlusSignal[bin] >> tmp >> WpToEleNuRecoil_cPlusErr[bin])
    {
     cout << bins << "\t" << WpToEleNu_cPlusSignal[bin] << "\t" << WpToEleNu_cPlusErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }


//Signal calculations
  
 Fout << "" << "\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t" << "" << endl;
 Fout << "********* W plus Signal calculation *********" << endl;
 Fout << "" << "\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t" << "" << endl;
 Fout << "Bin" << "\t" << "FzPlus " << "\t\t" << "Sa+Sb Plus" << "\t" << "Fz Recoil Plus" << "\t" << "Sa+Sb Recoil Plus" << endl;
 Fout << "" << "\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t" << "" << endl;
  for(int i(0); i<14; i++)
 {
         
   
   
  EWKaPlus[i]= DYToEEaPlusSignal[i] + DYToTauTau_aPlusSignal[i] + WToTauNu_aPlusSignal[i] + TTJets_aPlusSignal[i];
  EWKbPlus[i]= DYToEEbPlusSignal[i] + DYToTauTau_bPlusSignal[i] + WToTauNu_bPlusSignal[i] + TTJets_bPlusSignal[i];
  EWKdPlus[i]= DYToEEdPlusSignal[i] + DYToTauTau_dPlusSignal[i] + WToTauNu_dPlusSignal[i] + TTJets_dPlusSignal[i];
  EWKcPlus[i]= DYToEEcPlusSignal[i] + DYToTauTau_cPlusSignal[i] + WToTauNu_cPlusSignal[i] + TTJets_cPlusSignal[i];
   
  FzPlus[i]=(WpToEleNu_aPlusSignal[i])/(WpToEleNu_bPlusSignal[i]);

  FzRecoilPlus[i]=(WpToEleNuRecoil_aPlusSignal[i])/(WpToEleNuRecoil_bPlusSignal[i]);

  //IPlus=0.9767; 
  
  BcoeffPlus[i]=IPlus*(FzPlus[i]+1.0)*(FzPlus[i]*(RDcPlusSignal[i]- EWKcPlus[i])-(RDdPlusSignal[i]- EWKdPlus[i])) + (1.0+FzPlus[i])*(1.0-IPlus)*((RDaPlusSignal[i]-EWKaPlus[i])- FzPlus[i]*(RDbPlusSignal[i]-EWKbPlus[i]));
  BcoeffRecoilPlus[i]=IPlus*(FzRecoilPlus[i]+1.0)*(FzRecoilPlus[i]*(RDcPlusSignal[i]-EWKcPlus[i])-(RDdPlusSignal[i]-EWKdPlus[i])) + (1.0+FzRecoilPlus[i])*(1.0-IPlus)*((RDaPlusSignal[i]-EWKaPlus[i])-FzRecoilPlus[i]*(RDbPlusSignal[i]-EWKbPlus[i]));

  CcoeffPlus[i]=IPlus*(FzPlus[i]+1.0)*(FzPlus[i]+1.0)*((RDdPlusSignal[i]-EWKdPlus[i])*(RDbPlusSignal[i]-EWKbPlus[i])-(RDaPlusSignal[i]-EWKaPlus[i])*(RDcPlusSignal[i]-EWKcPlus[i]));
  CcoeffRecoilPlus[i]=IPlus*(FzRecoilPlus[i]+1.0)*(FzRecoilPlus[i]+1.0)*( (RDdPlusSignal[i]-EWKdPlus[i])*(RDbPlusSignal[i]-EWKbPlus[i])-(RDaPlusSignal[i]-EWKaPlus[i])*(RDcPlusSignal[i]-EWKcPlus[i]));
 
  SabPlus[i]=-CcoeffPlus[i]/BcoeffPlus[i];
  
  
  SabRecoilPlus[i]=-CcoeffRecoilPlus[i]/BcoeffRecoilPlus[i];
  

  Fout << i << "\t" << FzPlus[i] << "\t\t" << SabPlus[i] << "\t\t"<< FzRecoilPlus[i] << "\t\t" << SabRecoilPlus[i] << endl;
 

 }


// ==========  W  Minus  /////////

//RD

  bin = 0;
  cout << "*********RDa*********"  << endl;
  while(RDaMinus_file >> tmp >> bins >> tmp >> RDaMinusSignal[bin] >> tmp >> RDaMinusErr[bin])
    {
     cout << bins << "\t" << RDaMinusSignal[bin] << "\t" << RDaMinusErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }

  bin = 0;
   cout << "*********RDb*********"  << endl;
  while(RDbMinus_file >> tmp >> bins >> tmp >> RDbMinusSignal[bin] >> tmp >> RDbMinusErr[bin])
    {
     cout << bins << "\t" << RDbMinusSignal[bin] << "\t" << RDbMinusErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }
  bin = 0;
  cout << "*********RDd*********"  << endl;
  while(RDdMinus_file >> tmp >> bins >> tmp >> RDdMinusSignal[bin] >> tmp >> RDdMinusErr[bin])
    {
     cout << bins << "\t" << RDdMinusSignal[bin] << "\t" << RDdMinusErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }
  bin = 0;
   cout << "*********RDc*********"  << endl;
  while(RDcMinus_file >> tmp >> bins >> tmp >> RDcMinusSignal[bin] >> tmp >> RDcMinusErr[bin])
    {
     cout << bins << "\t" << RDcMinusSignal[bin] << "\t" << RDcMinusErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }


//DYToEE

  bin = 0;
  cout << "*********DYToEEa*********"  << endl;
  while(DYToEEaMinus_file >> tmp >> bins >> tmp >> DYToEEaMinusSignal[bin] >> tmp >> DYToEEaMinusErr[bin])
    {
     cout << bins << "\t" << DYToEEaMinusSignal[bin] << "\t" << DYToEEaMinusErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }
  bin = 0;
   cout << "*********DYToEEb*********"  << endl;
  while(DYToEEbMinus_file >> tmp >> bins >> tmp >> DYToEEbMinusSignal[bin] >> tmp >> DYToEEbMinusErr[bin])
    {
     cout << bins << "\t" << DYToEEbMinusSignal[bin] << "\t" << DYToEEbMinusErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }
  bin = 0;
   cout << "*********DYToEEd*********"  << endl;
  while(DYToEEdMinus_file >> tmp >> bins >> tmp >> DYToEEdMinusSignal[bin] >> tmp >> DYToEEdMinusErr[bin])
    {
     cout << bins << "\t" << DYToEEdMinusSignal[bin] << "\t" << DYToEEdMinusErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }
  bin = 0;
   cout << "*********DYToEEc*********"  << endl;
  while(DYToEEcMinus_file >> tmp >> bins >> tmp >> DYToEEcMinusSignal[bin] >> tmp >> DYToEEcMinusErr[bin])
    {
     cout << bins << "\t" << DYToEEcMinusSignal[bin] << "\t" << DYToEEcMinusErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }

//DYToTauTau

  bin = 0;
  cout << "*********DYToTauTau_a*********"  << endl;
  while(DYToTauTau_aMinus_file >> tmp >> bins >> tmp >> DYToTauTau_aMinusSignal[bin] >> tmp >> DYToTauTau_aMinusErr[bin])
    {
     cout << bins << "\t" << DYToTauTau_aMinusSignal[bin] << "\t" << DYToTauTau_aMinusErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }
  bin = 0;
   cout << "*********DYToTauTau_b*********"  << endl;
  while(DYToTauTau_bMinus_file >> tmp >> bins >> tmp >> DYToTauTau_bMinusSignal[bin] >> tmp >> DYToTauTau_bMinusErr[bin])
    {
     cout << bins << "\t" << DYToTauTau_bMinusSignal[bin] << "\t" << DYToTauTau_bMinusErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }
  bin = 0;
   cout << "*********DYToTauTau_d*********"  << endl;
  while(DYToTauTau_dMinus_file >> tmp >> bins >> tmp >> DYToTauTau_dMinusSignal[bin] >> tmp >> DYToTauTau_dMinusErr[bin])
    {
     cout << bins << "\t" << DYToTauTau_dMinusSignal[bin] << "\t" << DYToTauTau_dMinusErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }
  bin = 0;
   cout << "*********DYToTauTau_c*********"  << endl;
  while(DYToTauTau_cMinus_file >> tmp >> bins >> tmp >> DYToTauTau_cMinusSignal[bin] >> tmp >> DYToTauTau_cMinusErr[bin])
    {
     cout << bins << "\t" << DYToTauTau_cMinusSignal[bin] << "\t" << DYToTauTau_cMinusErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }

//WToTauNu

  bin = 0;
  cout << "*********WToTauNu_a*********"  << endl;
  while(WToTauNu_aMinus_file >> tmp >> bins >> tmp >> WToTauNu_aMinusSignal[bin] >> tmp >> WToTauNu_aMinusErr[bin])
    {
     cout << bins << "\t" << WToTauNu_aMinusSignal[bin] << "\t" << WToTauNu_aMinusErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }
  bin = 0;
   cout << "*********WToTauNu_b*********"  << endl;
  while(WToTauNu_bMinus_file >> tmp >> bins >> tmp >> WToTauNu_bMinusSignal[bin] >> tmp >> WToTauNu_bMinusErr[bin])
    {
     cout << bins << "\t" << WToTauNu_bMinusSignal[bin] << "\t" << WToTauNu_bMinusErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }
  bin = 0;
   cout << "*********WToTauNu_d*********"  << endl;
  while(WToTauNu_dMinus_file >> tmp >> bins >> tmp >> WToTauNu_dMinusSignal[bin] >> tmp >> WToTauNu_dMinusErr[bin])
    {
     cout << bins << "\t" << WToTauNu_dMinusSignal[bin] << "\t" << WToTauNu_dMinusErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }
  bin = 0;
   cout << "*********WToTauNu_c*********"  << endl;
  while(WToTauNu_cMinus_file >> tmp >> bins >> tmp >> WToTauNu_cMinusSignal[bin] >> tmp >> WToTauNu_cMinusErr[bin])
    {
     cout << bins << "\t" << WToTauNu_cMinusSignal[bin] << "\t" << WToTauNu_cMinusErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }

//TTJets

  bin = 0;
  cout << "*********TTJets_a*********"  << endl;
  while(TTJets_aMinus_file >> tmp >> bins >> tmp >> TTJets_aMinusSignal[bin] >> tmp >> TTJets_aMinusErr[bin])
    {
     cout << bins << "\t" << TTJets_aMinusSignal[bin] << "\t" << TTJets_aMinusErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }
  bin = 0;
   cout << "*********TTJets_b*********"  << endl;
  while(TTJets_bMinus_file >> tmp >> bins >> tmp >> TTJets_bMinusSignal[bin] >> tmp >> TTJets_bMinusErr[bin])
    {
     cout << bins << "\t" << TTJets_bMinusSignal[bin] << "\t" << TTJets_bMinusErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }
  bin = 0;
   cout << "*********TTJets_d*********"  << endl;
  while(TTJets_dMinus_file >> tmp >> bins >> tmp >> TTJets_dMinusSignal[bin] >> tmp >> TTJets_dMinusErr[bin])
    {
     cout << bins << "\t" << TTJets_dMinusSignal[bin] << "\t" << TTJets_dMinusErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }
  bin = 0;
   cout << "*********TTJets_c*********"  << endl;
  while(TTJets_cMinus_file >> tmp >> bins >> tmp >> TTJets_cMinusSignal[bin] >> tmp >> TTJets_cMinusErr[bin])
    {
     cout << bins << "\t" << TTJets_cMinusSignal[bin] << "\t" << TTJets_cMinusErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }

//WpToEleNu before recoil

  bin = 0;
  cout << "*********WmToEleNu_a*********"  << endl;
  while(WmToEleNu_aMinus_file >> tmp >> bins >> tmp >> WmToEleNu_aMinusSignal[bin] >> tmp >> WmToEleNu_aMinusErr[bin])
    {
     cout << bins << "\t" << WmToEleNu_aMinusSignal[bin] << "\t" << WmToEleNu_aMinusErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }
  bin = 0;
   cout << "*********WmToEleNu_b*********"  << endl;
  while(WmToEleNu_bMinus_file >> tmp >> bins >> tmp >> WmToEleNu_bMinusSignal[bin] >> tmp >> WmToEleNu_bMinusErr[bin])
    {
     cout << bins << "\t" << WmToEleNu_bMinusSignal[bin] << "\t" << WmToEleNu_bMinusErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }
  bin = 0;
   cout << "*********WmToEleNu_d*********"  << endl;
  while(WmToEleNu_dMinus_file >> tmp >> bins >> tmp >> WmToEleNu_dMinusSignal[bin] >> tmp >> WmToEleNu_dMinusErr[bin])
    {
     cout << bins << "\t" << WmToEleNu_dMinusSignal[bin] << "\t" << WmToEleNu_dMinusErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }
  bin = 0;
   cout << "*********WmToEleNu_c*********"  << endl;
  while(WmToEleNu_cMinus_file >> tmp >> bins >> tmp >> WmToEleNu_cMinusSignal[bin] >> tmp >> WmToEleNu_cMinusErr[bin])
    {
     cout << bins << "\t" << WmToEleNu_cMinusSignal[bin] << "\t" << WmToEleNu_cMinusErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }

//WpToEleNu after recoil
  
  bin = 0;
  cout << "*********WmToEleNuRecoil_a*********"  << endl;
  while(WmToEleNuRecoil_aMinus_file >> tmp >> bins >> tmp >> WmToEleNuRecoil_aMinusSignal[bin] >> tmp >> WmToEleNuRecoil_aMinusErr[bin])
    {
     cout << bins << "\t" << WmToEleNuRecoil_aMinusSignal[bin] << "\t" << WmToEleNuRecoil_aMinusErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }
  bin = 0;
   cout << "*********WmToEleNuRecoil_b*********"  << endl;
  while(WmToEleNuRecoil_bMinus_file >> tmp >> bins >> tmp >> WmToEleNuRecoil_bMinusSignal[bin] >> tmp >> WmToEleNuRecoil_bMinusErr[bin])
    {
     cout << bins << "\t" << WmToEleNuRecoil_bMinusSignal[bin] << "\t" << WmToEleNuRecoil_bMinusErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }
  bin = 0;
   cout << "*********WmToEleNuRecoil_d*********"  << endl;
  while(WmToEleNuRecoil_dMinus_file >> tmp >> bins >> tmp >> WmToEleNuRecoil_dMinusSignal[bin] >> tmp >> WmToEleNuRecoil_dMinusErr[bin])
    {
     cout << bins << "\t" << WmToEleNuRecoil_dMinusSignal[bin] << "\t" << WmToEleNuRecoil_dMinusErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }
  bin = 0;
   cout << "*********WmToEleNuRecoil_c*********"  << endl;
  while(WmToEleNuRecoil_cMinus_file >> tmp >> bins >> tmp >> WmToEleNuRecoil_cMinusSignal[bin] >> tmp >> WmToEleNuRecoil_cMinusErr[bin])
    {
     cout << bins << "\t" << WmToEleNu_cMinusSignal[bin] << "\t" << WmToEleNu_cMinusErr[bin] << endl;
   bin++;
   if(bin==14)break;
   }


//Signal calculations
  
 Fout << "" << "\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t" << "" << endl;
 Fout << "********* W minus Signal calculation *********" << endl;
 Fout << "" << "\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t" << "" << endl;
 Fout << "Bin" << "\t" << "FzMinus " << "\t" << "Sa+Sb Minus" << "\t" << "Fz Recoil Minus" << "\t" << "Sa+Sb Recoil Minus" << endl;
 Fout << "" << "\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t" << "" << endl;
  for(int i(0); i<14; i++)
 {
         
   
   
  EWKaMinus[i]= DYToEEaMinusSignal[i] + DYToTauTau_aMinusSignal[i] + WToTauNu_aMinusSignal[i] + TTJets_aMinusSignal[i];
  EWKbMinus[i]= DYToEEbMinusSignal[i] + DYToTauTau_bMinusSignal[i] + WToTauNu_bMinusSignal[i] + TTJets_bMinusSignal[i];
  EWKdMinus[i]= DYToEEdMinusSignal[i] + DYToTauTau_dMinusSignal[i] + WToTauNu_dMinusSignal[i] + TTJets_dMinusSignal[i];
  EWKcMinus[i]= DYToEEcMinusSignal[i] + DYToTauTau_cMinusSignal[i] + WToTauNu_cMinusSignal[i] + TTJets_cMinusSignal[i];
   
  FzMinus[i]=(WmToEleNu_aMinusSignal[i])/(WmToEleNu_bMinusSignal[i]);

  FzRecoilMinus[i]=(WmToEleNuRecoil_aMinusSignal[i])/(WmToEleNuRecoil_bMinusSignal[i]);

  //IMinus=0.9767; 
  
  BcoeffMinus[i]=IMinus*(FzMinus[i]+1.0)*(FzMinus[i]*(RDcMinusSignal[i]- EWKcMinus[i])-(RDdMinusSignal[i]- EWKdMinus[i])) + (1.0+FzMinus[i])*(1.0-IMinus)*((RDaMinusSignal[i]-EWKaMinus[i])- FzMinus[i]*(RDbMinusSignal[i]-EWKbMinus[i]));
  BcoeffRecoilMinus[i]=IMinus*(FzRecoilMinus[i]+1.0)*(FzRecoilMinus[i]*(RDcMinusSignal[i]-EWKcMinus[i])-(RDdMinusSignal[i]-EWKdMinus[i])) + (1.0+FzRecoilMinus[i])*(1.0-IMinus)*((RDaMinusSignal[i]-EWKaMinus[i])-FzRecoilMinus[i]*(RDbMinusSignal[i]-EWKbMinus[i]));

  CcoeffMinus[i]=IMinus*(FzMinus[i]+1.0)*(FzMinus[i]+1.0)*((RDdMinusSignal[i]-EWKdMinus[i])*(RDbMinusSignal[i]-EWKbMinus[i])-(RDaMinusSignal[i]-EWKaMinus[i])*(RDcMinusSignal[i]-EWKcMinus[i]));
  CcoeffRecoilMinus[i]=IMinus*(FzRecoilMinus[i]+1.0)*(FzRecoilMinus[i]+1.0)*( (RDdMinusSignal[i]-EWKdMinus[i])*(RDbMinusSignal[i]-EWKbMinus[i])-(RDaMinusSignal[i]-EWKaMinus[i])*(RDcMinusSignal[i]-EWKcMinus[i]));
 
  SabMinus[i]=-CcoeffMinus[i]/BcoeffMinus[i];
  
  
  SabRecoilMinus[i]=-CcoeffRecoilMinus[i]/BcoeffRecoilMinus[i];
  

  Fout << i << "\t" << FzMinus[i] << "\t\t" << SabMinus[i] << "\t\t"<< FzRecoilMinus[i] << "\t\t" << SabRecoilMinus[i] << endl;
 

 }


/*
///////  W- ////////

//Nominal_M
   bin = 0;
   cout << "*********Nominal_M*********"  << endl;
  while(Nominal_M_file >> tmp >> bins >> tmp >> NomVal_M[bin] >> tmp >> Err[bin])
    {
     cout << bins << "\t" << NomVal_M[bin] << "\t" << Err[bin] << endl;
   bin++;
   if(bin==12)break;
   }
//Up
     bin = 0;
     cout << "*********Up_M*********"  << endl;
  while(Up_M_file >> tmp >> bins >> tmp >> UpVal_M[bin] >> tmp >> Err[bin])
    {
     cout << bins << "\t" << UpVal_M[bin] << "\t" << Err[bin] << endl;
   bin++;
   if(bin==12)break;
   }
//Down
   bin = 0;
   cout << "*********Down_M*********"  << endl;
  while(Down_M_file >> tmp >> bins >> tmp >> DownVal_M[bin] >> tmp >> Err[bin])
    {
     cout << bins << "\t" << DownVal_M[bin] << "\t" << Err[bin] << endl;
   bin++;
   if(bin==12)break;
   }
//BeforeRC
   bin = 0;
   cout << "*********BeforeRC_M*********"  << endl;
  while(BeforeRC_M_file >> tmp >> bins >> tmp >> BeRCVal_M[bin] >> tmp >> Err[bin])
    {
     cout << bins << "\t" << BeRCVal_M[bin] << "\t" << Err[bin] << endl;
   bin++;
   if(bin==12)break;
   }
//Systematic
   cout << "********* W minus *********" << endl;
   Fout << "********* W minus *********" << endl;
  for(int i=1; i<12; i++)
 {
         A[i] = NomVal_M[i] - UpVal_M[i];
         B[i] = NomVal_M[i] - DownVal_M[i];
        systematic[i] = sqrt((A[i]*A[i])+(B[i]*B[i]));
        cout << i << "\t" << A[i] << "\t" << B[i] << "\t"<< systematic[i] << endl;
        Fout << i << "\t" << A[i] << "\t" << B[i] << "\t"<< systematic[i] << "\t\t" << systematic[i]/NomVal_M[i]*100 << endl;
 }
*/  
   Fout.close();
//   return 0;
}
