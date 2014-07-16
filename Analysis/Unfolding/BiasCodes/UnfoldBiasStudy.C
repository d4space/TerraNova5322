#include "TStyle.h"
#include "../Utils/const.h"
#include "../Utils/CPlot.hh"
#include "../Utils/MitStyleRemix.hh"
#include "../Utils/Unfolder.h"
#include <fstream>
#include <iostream>
#include <iomanip>

//From TSVDUnfoldExample.C

#include "TROOT.h"
#include "TSystem.h"
#include "TStyle.h"
#include "TRandom3.h"
#include "TString.h"
#include "TMath.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TColor.h"
#include "TLine.h"

#include "RooRealVar.h"
#include "RooPolynomial.h"
#include "RooPoisson.h"
#include "RooLandau.h"
#include "RooPlot.h"
#include "RooBinning.h"
#include "RooExponential.h"
#include "RooAddPdf.h"
#include "RooDataHist.h"

#include "TMatrixD.h"
#include "TVectorD.h"

#if not defined(__CINT__) || defined(__MAKECINT__)
#include "TSVDUnfold.h"
#endif
 
//#define TSVDSelfTestPost

#define nToy 1
//#define idx 0

int UnfoldBiasStudy
(TString UnfoldFile,TString AcceptFile,TString DataFile,TString BaseName,int idx)
{
  double Bins[NWptBinPlus];
  // Final Bins
  Bins[0] = 0.;
  Bins[1] = 7.5;
  Bins[2] = 12.5;
  Bins[3] = 17.5;
  Bins[4] = 24.;
  Bins[5] = 30.;
  Bins[6] = 40.;
  Bins[7] = 50.;
  Bins[8] = 70.;
  Bins[9] = 110.;
  Bins[10]= 150.;
  Bins[11]= 190.;
  Bins[12]= 250.;
  Bins[13]= 600.;

  double nBins[14]={0,1,2,3,4,5,6,7,8,9,10,11,12,13};

  TString resultDir = "Result"+BaseName;
  gSystem->mkdir(resultDir,kTRUE);
  char tmpName[30];
  TString tmpTStr;
  
  //ofstream Fout;
  //Fout.open(resultDir+"/Systematics.txt");
  
  TFile *f_Unfold    = new TFile(UnfoldFile);
  TFile *f_Accept    = new TFile(AcceptFile);
  TFile *f_Data      = new TFile(DataFile);

  TFile *f_RecoScaleCovMat;
  TFile *f_RecoEffiCovMat;
  TFile *f_RecoSmearCovMat;
  TFile *f_RecoRecoilCovMat;
  TFile *f_RecoQCDRatioCovMat;
  
  TFile *f_RecoAcceptCovMat;
  TFile *f_RecoAcceptFSRCovMat;
  
  if(BaseName == "WpToEleNu" )
  {
    f_RecoScaleCovMat     = new TFile("RecoCovMatrix/Result_WpToEleNu_RecoScaleCovMat.root");
    f_RecoEffiCovMat      = new TFile("RecoCovMatrix/Result_WpToEleNu_RecoEffiCovMat.root");
    f_RecoSmearCovMat     = new TFile("RecoCovMatrix/Result_WpToEleNu_RecoSmearCovMat.root");
    f_RecoRecoilCovMat    = new TFile("RecoCovMatrix/Result_WpToEleNu_RecoRecoilCovMat.root");
    f_RecoAcceptCovMat    = new TFile("RecoCovMatrix/Ele_WpToEleNu_S8_Acceptance.root");
    f_RecoAcceptFSRCovMat = new TFile("RecoCovMatrix/Ele_WpToEleNu_S8_AcceptanceFSR.root");
  }else if(BaseName == "WmToEleNu"){
    f_RecoScaleCovMat     = new TFile("RecoCovMatrix/Result_WmToEleNu_RecoScaleCovMat.root");
    f_RecoEffiCovMat      = new TFile("RecoCovMatrix/Result_WmToEleNu_RecoEffiCovMat.root");
    f_RecoSmearCovMat     = new TFile("RecoCovMatrix/Result_WmToEleNu_RecoSmearCovMat.root");
    f_RecoRecoilCovMat    = new TFile("RecoCovMatrix/Result_WmToEleNu_RecoRecoilCovMat.root");
    f_RecoAcceptCovMat    = new TFile("RecoCovMatrix/Ele_WmToEleNu_S8_Acceptance.root");
    f_RecoAcceptFSRCovMat = new TFile("RecoCovMatrix/Ele_WmToEleNu_S8_AcceptanceFSR.root");
  }else if(BaseName == "WpToMuNu"){
    f_RecoEffiCovMat      = new TFile("RecoCovMatrix/Result_WpToMuNu_RecoEffiCovMat.root");
    f_RecoSmearCovMat     = new TFile("RecoCovMatrix/Result_WpToMuNu_RecoSmearCovMat.root");
    f_RecoRecoilCovMat    = new TFile("RecoCovMatrix/Result_WpToMuNu_RecoRecoilCovMat.root");
    f_RecoAcceptCovMat    = new TFile("RecoCovMatrix/Muon_WpToMuNu_S8_Acceptance.root");
    f_RecoAcceptFSRCovMat = new TFile("RecoCovMatrix/Muon_WpToMuNu_S8_AcceptanceFSR.root");
    f_RecoQCDRatioCovMat  = new TFile("RecoCovMatrix/Result_WpToMuNu_RecoQCDRatioCovMat.root");
  }else if(BaseName == "WmToMuNu"){
    f_RecoEffiCovMat      = new TFile("RecoCovMatrix/Result_WmToMuNu_RecoEffiCovMat.root");
    f_RecoSmearCovMat     = new TFile("RecoCovMatrix/Result_WmToMuNu_RecoSmearCovMat.root");
    f_RecoRecoilCovMat    = new TFile("RecoCovMatrix/Result_WmToMuNu_RecoRecoilCovMat.root");
    f_RecoAcceptCovMat    = new TFile("RecoCovMatrix/Muon_WmToMuNu_S8_Acceptance.root");
    f_RecoAcceptFSRCovMat = new TFile("RecoCovMatrix/Muon_WmToMuNu_S8_AcceptanceFSR.root");
    f_RecoQCDRatioCovMat  = new TFile("RecoCovMatrix/Result_WmToMuNu_RecoQCDRatioCovMat.root");
  }
  
  TFile *f_RecoLumiUpCovMat;
  TFile *f_RecoLumiDownCovMat;
  
  f_RecoLumiUpCovMat   = new TFile("RecoCovMatrix/SigYields_Lumi_Up.root");
  f_RecoLumiDownCovMat = new TFile("RecoCovMatrix/SigYields_Lumi_Down.root");
  
  TH1D* h1_SigWptLumiUp;
  TH1D* h1_SigWptLumiDown;
  TH1D *h1_Post_BothFidAccept;
  TH1D *h1_Post_BothFidAcceptFSR;

  TFile *f_Eff    = new TFile("ResultUnfEff/eff.root");
  tmpTStr = resultDir+"/Result_"+BaseName+".root";
  TFile *f_Out    = new TFile(tmpTStr,"recreate");

  // SVD input
  struct histSVD{
    TH2D *Adet;
    TH2D *uAdetCov[nToy];
    TH1D *xini; // Post True
    TH1D *bini; // Reco Truth
    TH1D *data[nToy];
    TH1D *True;
    TH1D *Gen;
    TH1D *EffCorr[nToy];
    TH2D *statCov;
    TH1D *unfRes[nToy];
    TH1D *dDist[nToy];
    TH1D *svDist[nToy];
    TH1D *DetUnf[nToy];
    TH1D *FSRUnf[nToy];
    TH1D *Corr[nToy];
    TH2D *uTotalCovMat;
    TH2D *uTotalSystCov;
    TH2D *uStatCov;
    TH2D *uTauCov[nToy];
    TH2D *uInvCov;

    TH2D *BstatCorr_uTotal; //Total Correlation Matrix
    TH2D *AbsNormCorrErr; //Absolute Normilazed Correlated Error Matrix
    
    TH2D *RecoEffiCovMat;
    TH2D *RecoScaleCovMat;
    TH2D *RecoSmearCovMat;
    TH2D *RecoRecoilCovMat;
    TH2D *RecoLumiCovMat;
    TH2D *RecoStatisticCovMat;
    TH2D *RecoQCDRatioCovMat;
    TH2D *TotalRecoCovMat;
    TH2D *ToyRecoCovMat[nToy];
    TH2D *ToyStatCovMat[nToy];

    TH2D *InputCovMat; //Input Covariance Matrix for FSR Unfolding
    TH2D *uInputCovMat;//Input Covariance Matrix after FSR Unfolding
    
    TH2D *uRecoEffiCovMat;
    TH2D *uRecoScaleCovMat;
    TH2D *uRecoSmearCovMat;
    TH2D *uRecoRecoilCovMat;
    TH2D *uRecoLumiCovMat;
    TH2D *uRecoStatisticCovMat;
    TH2D *uRecoQCDRatioCovMat;
    TH2D *uRecoRespCovMat;

    TH2D *uTotalRecoCovMat;
    TH2D *AcceptFSRCovMat;
    TH2D *MCEventEffFSRCovMat[nToy]; //Make FSR Covariance Matrix from MC Eff.
    TH2D *uMCEventEffFSRCovMat;

    TH2D *Eff_uRecoEffiCovMat;
    TH2D *Eff_uRecoScaleCovMat;
    TH2D *Eff_uRecoSmearCovMat;
    TH2D *Eff_uRecoRecoilCovMat;
    TH2D *Eff_uRecoLumiCovMat;
    TH2D *Eff_uMCEventEffFSRCovMat;
    TH2D *Eff_uRecoStatisticCovMat;
    TH2D *Eff_DetectUnfStatisticCovMat;
    TH2D *Eff_uRecoQCDRatioCovMat;
    TH2D *Eff_uRecoRespCovMat;

    TH2D *Eff_uTauCov;
    
    TH2D *Eff_uTotalRecoCovMat;
    TH2D *Eff_uTotalRecoCovMatEff;
  };
  histSVD SVD_Post;
  histSVD SVD_Born;

  // Efficiency
  TH1D* h1_Post_BothOvTruth; 
  TH1D* h1_Post_BothOvTruth_eqBin; 
  TH1D* h1_Born_BothOvBorn; 
  TH1D* h1_Born_BothOvBorn_eqBin; 
  TH1D* h1_Post_BothOvTruth_weightFSR; 
  TH1D* h1_Post_BothOvTruth_weightFSR_eqBin; 
  
  // Unfolding to Post
  TH1D *h1_Truth_Rec;
  TH1D *h1_Truth_Rec_Even;
  TH1D *h1_Truth_Rec_Odd;
  TH1D *h1_Truth_Post;
  TH1D *h1_Truth_Post_Lumi;
  TH1D *h1_Truth_Post_Even;
  TH1D *h1_Truth_Post_Odd;
  TH2D *h2_Truth_Rec_AP_Post;
  TH2D *h2_Truth_Rec_AP_Post_Ivs;
  TH2D *h2_Truth_Rec_AP_PostEffCorr;
  TH1D *h1_Unfolded_Post_InvMthd;
  TH1D *EqBin_Truth_Rec_Even;

  // Acceptance
  TH1D*	h1_Born_AP;
  TH1D*	h1_Born_BornFid;
  TH1D*	h1_Born_BornFid_Even;
  TH1D*	h1_Born_BornFid_Lumi;
  TH1D*	h1_Born_BothFid;
  TH1D*	h1_Born_BothFid_Lumi;

  TH1D*	h1_Post_PostFid;
  TH1D*	h1_Post_PostFid_Even;
  TH1D*	h1_Post_PostFid_Lumi; // Lumi weighted
  TH1D*	h1_Post_BothFid;
  TH1D*	h1_Post_BothFid_Lumi;
  TH2D*	h2_PostBorn_BothFid;
  TH1D* EqBin_Post_PostFid_Even;

  // Data
  double TotalStat[NWptBinPlus]={0.};
  double TotalError[NWptBinPlus]={0.};
  double TotalUncertErr[NWptBinPlus]={0.};
  
  double dUnf_SVD[NWptBinPlus-1]={0.};
  double FSRUnf_SVD[NWptBinPlus-1]={0.};
  double Unf_SVD[NWptBinPlus-1]={0.};
  
  TH1D* h1_Data_SigYild;
  
  // Define Histo
  h1_Post_BothOvTruth_eqBin=
    new TH1D("h1_Post_BothOvTruth_eqBin","BothOvTruth",NWptBinPlus-1,0,NWptBinPlus-1);
  h1_Post_BothOvTruth_weightFSR_eqBin=
    new TH1D("h1_Post_BothOvTruth_weightFSR_eqBin","BothOvTruth_weightFSR",NWptBinPlus-1,0,NWptBinPlus-1);
  h1_Born_BothOvBorn_eqBin=
    new TH1D("h1_Born_BothOvBorn_eqBin","BothOvBorn",NWptBinPlus-1,0,NWptBinPlus-1);
  
  SVD_Post.xini = new TH1D("xini_Post","Post true",NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Post.bini = new TH1D("bini_Post","Reco thruth" ,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Post.True = new TH1D("SVD_Post.True","SVD_Post.True",NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Post.Gen  = new TH1D("SVD_Post.Gen","SVD_Post.Gen",NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Post.Adet = new TH2D("Adet_Post","detector response"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Post.statCov = new TH2D("SVD_Post.statCov","Covariance matrix"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Post.BstatCorr_uTotal = new TH2D("SVD_Post.BstatCorr_uTotal","Total Correlation matrix after D_Unf"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Post.AbsNormCorrErr = new TH2D("SVD_Post.AbsNormCorrErr","Absolute Normalized Covariance Error Matrix D_Unf"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Born.AbsNormCorrErr = new TH2D("SVD_Born.AbsNormCorrErr","Absolute Normalized Covariance Error Matrix FSR_Unf"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Post.RecoEffiCovMat = new TH2D("SVD_Post.RecoEffiCovMat","Reco Stage Effi Covariace matrix"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  TH2D* h2_RecoEffiCovMat = new TH2D("h2_RecoEffiCovMat","Reco Stage Effi Covariace matrix"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Post.Eff_uRecoEffiCovMat = new TH2D("SVD_Post.Eff_uRecoEffiCovMat","Eff applied Effi Covariace matrix Detector unfolding"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Born.uRecoEffiCovMat = new TH2D("SVD_Born.uRecoEffiCovMat","Born Effi Covariace matrix Post to Born"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Post.RecoScaleCovMat = new TH2D("SVD_Post.RecoScaleCovMat","Reco Stage Scale Covariace matrix"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  TH2D* h2_RecoScaleCovMat = new TH2D("h2_RecoScaleCovMat","Reco Stage Scale Covariace matrix"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Post.Eff_uRecoScaleCovMat = new TH2D("SVD_Post.Eff_uRecoScaleCovMat","Eff applied Scale Covariace matrix Detector unfolding"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Post.RecoSmearCovMat = new TH2D("SVD_Post.RecoSmearCovMat","Reco Stage Smear Covariace matrix"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  TH2D* h2_RecoSmearCovMat = new TH2D("h2_RecoSmearCovMat","Reco Stage Smear Covariace matrix"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Post.Eff_uRecoSmearCovMat = new TH2D("SVD_Post.Eff_uRecoSmearCovMat","Effi applied Smear Covariace matrix Detector unfolding"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Post.RecoRecoilCovMat = new TH2D("SVD_Post.RecoRecoilCovMat","Reco Stage Recoil Covariace matrix"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  TH2D* h2_RecoRecoilCovMat = new TH2D("h2_RecoRecoilCovMat","Reco Stage Recoil Covariace matrix"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Post.Eff_uRecoRecoilCovMat = new TH2D("SVD_Post.Eff_uRecoRecoilCovMat","Eff apllied Recoil Covariace matrix Detector unfolding"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Post.RecoLumiCovMat = new TH2D("SVD_Post.RecoLumiCovMat","Reco Stage Lumi Covariace matrix"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  TH2D* h2_RecoQCDRatioCovMat = new TH2D("h2_RecoQCDRatioCovMat","Reco Stage QCD ratio Covariace matrix"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Post.RecoQCDRatioCovMat = new TH2D("SVD_Post.RecoQCDRatioCovMat","Reco QCD ratio Covariace matrix "
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Post.uRecoQCDRatioCovMat = new TH2D("SVD_Post.uRecoQCDRatioCovMat","Reco QCD ratio Covariace matrix "
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Post.Eff_uRecoQCDRatioCovMat = new TH2D("SVD_Post.Eff_uRecoQCDRatioCovMat","Eff applied QCD ratio Covariace matrix Detector unfolding"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Post.Eff_uRecoRespCovMat = new TH2D("SVD_Post.Eff_uRecoRespCovMat","Eff apllied Response Covariace matrix after Detector unfolding"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Post.Eff_uMCEventEffFSRCovMat = new TH2D("SVD_Post.Eff_uMCEventEffFSRCovMat","Eff applied FSR Covariace matrix Detector unfolding"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Post.AcceptFSRCovMat = new TH2D("SVD_Post.AcceptFSRCovMat","FSR CovMat from Acceptance h1_Post_BothFid"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Post.RecoStatisticCovMat = new TH2D("SVD_Post.RecoStatisticCovMat","Reco Stage Statistic Covariace matrix"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Post.Eff_uRecoStatisticCovMat = new TH2D("SVD_Post.Eff_uRecoStatisticCovMat","Effi applied Statistic Covariace matrix Deterctor unfolding"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Post.Eff_DetectUnfStatisticCovMat = new TH2D("SVD_Post.Eff_DetectUnfStatisticCovMat","Effi applied StatCovMat from Detector Unf"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Post.TotalRecoCovMat = new TH2D("SVD_Post.TotalRecoCovMat","Total Reco Stage Covariace matrix"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Post.uTotalRecoCovMat = new TH2D("SVD_Post.uTotalRecoCovMat","Total Covariace matrix Detector unfilding"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Post.Eff_uTotalRecoCovMat = new TH2D("SVD_Post.Eff_uTotalRecoCovMat","Effi applied Total Covariace matrix Detector ufolding"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Post.Eff_uTotalRecoCovMatEff = new TH2D("SVD_Post.Eff_uTotalRecoCovMatEff","Effi applied Total Covariace matrix Detector ufolding"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Born.uTotalCovMat = new TH2D("SVD_Born.uTotalCovMat","Total Covariace matrix after FSR unfolding"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Born.InputCovMat = new TH2D("SVD_Born.InputCovMat","Input Covariace matrix for FSR unfolding"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Born.uInputCovMat = new TH2D("SVD_Born.uInputCovMat","Input Covariace matrix after FSR unfolding"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Post.Eff_uTauCov = new TH2D("SVD_Post.Eff_uTauCov","Effi applied uTauCov Deterctor unfolding"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Born.uRecoRespCovMat =  new TH2D("SVD_Born.uRecoRespCovMat","Eff apllied Response Covariace matrix after FSR unfolding"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Born.xini = new TH1D("xini_Born","Born xini",NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Born.bini = new TH1D("bini_Born","Post" ,NWptBinPlus-1,0,NWptBinPlus-1);
  //SVD_Born.data = new TH1D("data_Born","data_Rec"    ,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Born.True = new TH1D("SVD_Born.True","Born.True",NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Born.Gen  = new TH1D("SVD_Born.Gen","Born.Gen",NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Born.Adet = new TH2D("Adet_Born","detector response",NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Born.statCov = new TH2D("SVD_Born.statCov","Covariance matrix",NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);

  // Plot
  CPlot *pltBinByBinCorr;
  CPlot *pltSVD_EffCorr;
  
  CPlot *pltUnfPost;
  CPlot *pltUnfPost_InputCov;

  CPlot *pltUnfPost_uTotalCov;
  CPlot *pltUnfPost_uTotalSystCov;
  CPlot *pltUnfPost_uRespMatrix;
  CPlot *pltUnfPost_AbsNormCorrErr;
  CPlot *pltUnfBorn_AbsNormCorrErr;
  CPlot *pltUnfBorn_uTotalCov;
  CPlot *pltUnfBorn_InputCov;
  
  CPlot *pltRecoStatCov;
  CPlot *pltRecoEffCov;
  CPlot *pltRecoRecoilCov;
  CPlot *pltRecoScaleCov;
  CPlot *pltRecoSmearCov;
  CPlot *pltRecoQCDRatioCov;
  CPlot *pltRecoFSRCov;
  CPlot *pltEffFSRCov;
  
  CPlot *plt_uInputCovMat;

  CPlot *pltReconEffi_cov;
  CPlot *pltReconScale_cov;
  CPlot *pltReconSmear_cov;
  CPlot *pltReconRecoil_cov;
  CPlot *pltReconLumi_cov;
  CPlot *pltReconFSR_cov;
  CPlot *pltReconQCDRatio_cov;
 
  CPlot *pltRecon_corr;
  CPlot *plt_DUnf_RespCov;
  
  CPlot *pltUnfPost_d;
  CPlot *pltUnfBorn;
  CPlot *pltUnfBorn_cov;
  CPlot *pltUnfBorn_d;
  TCanvas *myCan = MakeCanvas("myCan","myCan",900,800);


  char legendName[30];

  //=====================
  // Histo from Unfolding
  //=====================
  sprintf(tmpName,"h1_Truth_Rec");
  h1_Truth_Rec = (TH1D*)f_Unfold->Get(tmpName)->Clone(tmpName);
  h1_Truth_Rec->Sumw2();

  sprintf(tmpName,"h1_Truth_Rec_Even");
  h1_Truth_Rec_Even = (TH1D*)f_Unfold->Get(tmpName)->Clone(tmpName);
  h1_Truth_Rec_Even->Sumw2();

  sprintf(tmpName,"h1_Truth_Rec_Odd");
  h1_Truth_Rec_Odd = (TH1D*)f_Unfold->Get(tmpName)->Clone(tmpName);
  h1_Truth_Rec_Odd->Sumw2();

  sprintf(tmpName,"h1_Truth_Post");
  h1_Truth_Post = (TH1D*)f_Unfold->Get(tmpName)->Clone(tmpName);
  h1_Truth_Post->Sumw2();
  sprintf(tmpName,"h1_Truth_Post_Lumi");
  h1_Truth_Post_Lumi = (TH1D*)h1_Truth_Post->Clone(tmpName);
  h1_Truth_Post_Lumi->Sumw2();
  sprintf(tmpName,"h1_Truth_Post_Even");
  h1_Truth_Post_Even = (TH1D*)f_Unfold->Get(tmpName)->Clone(tmpName);
  h1_Truth_Post_Even->Sumw2();
  sprintf(tmpName,"h1_Truth_Post_Odd");
  h1_Truth_Post_Odd = (TH1D*)f_Unfold->Get(tmpName)->Clone(tmpName);
  h1_Truth_Post_Odd->Sumw2();

  sprintf(tmpName,"h2_Truth_Rec_AP_Post");
  h2_Truth_Rec_AP_Post=(TH2D*)f_Unfold->Get(tmpName)->Clone(tmpName);
  InitHist2D(h2_Truth_Rec_AP_Post);
  h2_Truth_Rec_AP_Post->Sumw2();

  sprintf(tmpName,"h2_Truth_Rec_AP_PostEffCorr");
  h2_Truth_Rec_AP_PostEffCorr=(TH2D*)f_Unfold->Get(tmpName)->Clone(tmpName);
  InitHist2D(h2_Truth_Rec_AP_PostEffCorr);
  h2_Truth_Rec_AP_PostEffCorr->Sumw2();
  
  int nbins = h1_Truth_Rec->GetNbinsX();
  //Fout<<"Nsimul N of bins: "<<nbins<<endl;
  double Nsimul = h1_Truth_Rec->Integral();
  //Fout<<"Total Events: "<<setw(20)<<setprecision(7)<<Nsimul<<endl;
  double NsimulEven = h1_Truth_Rec_Even->Integral();
  //Fout<<"NsimulEven: "<<setw(20)<<setprecision(7)<<NsimulEven<<endl;
  double NsimulOdd = h1_Truth_Rec_Odd->Integral();
  //Fout<<"NsimulOdd: "<<setw(20)<<setprecision(7)<<NsimulOdd<<endl;
  double NdetectorResponse = h2_Truth_Rec_AP_Post->Integral();
  double NdetectorResponseEffCorr = h2_Truth_Rec_AP_Post->Integral();
  //Fout<<"NdetectorResponse: "<<NdetectorResponse<<endl;
  //Fout<<"NdetectorResponseEffCorr: "<<NdetectorResponseEffCorr<<endl;
  //======================
  // Histo from Acceptance 
  //======================
  sprintf(tmpName,"h1_Born_AP");
  h1_Born_AP		=(TH1D*)f_Accept->Get(tmpName)->Clone(tmpName);
  sprintf(tmpName,"h1_Born_BornFid");
  h1_Born_BornFid	=(TH1D*)f_Accept->Get(tmpName)->Clone(tmpName);
  h1_Born_BornFid_Lumi=(TH1D*)h1_Born_BornFid->Clone("h1_Born_BornFid_Lumi");
  h1_Born_BornFid_Lumi->Sumw2();
  sprintf(tmpName,"h1_Born_BornFid_Even");
  h1_Born_BornFid_Even	=(TH1D*)f_Accept->Get(tmpName)->Clone(tmpName);
  sprintf(tmpName,"h1_Born_BothFid");
  h1_Born_BothFid	=(TH1D*)f_Accept->Get(tmpName)->Clone(tmpName);
  sprintf(tmpName,"h1_Born_BothFid_Lumi");
  h1_Born_BothFid_Lumi	=(TH1D*)h1_Born_BothFid->Clone(tmpName);

  sprintf(tmpName,"h1_Post_PostFid");
  h1_Post_PostFid	=(TH1D*)f_Accept->Get(tmpName)->Clone(tmpName);
  h1_Post_PostFid_Lumi	=(TH1D*)h1_Post_PostFid->Clone("h1_Post_PostFid_Lumi");
  h1_Post_PostFid_Lumi->Sumw2();

  sprintf(tmpName,"h1_Post_BothFid");
  h1_Post_BothFid	=(TH1D*)f_Accept->Get(tmpName)->Clone(tmpName);
  sprintf(tmpName,"h1_Post_BothFid_Lumi");
  h1_Post_BothFid_Lumi	=(TH1D*)h1_Post_BothFid->Clone(tmpName);
  h1_Post_BothFid_Lumi->Sumw2();
  sprintf(tmpName,"h2_PostBorn_BothFid");
  h2_PostBorn_BothFid	=(TH2D*)f_Accept->Get(tmpName)->Clone(tmpName);

  if(BaseName == "WpToMuNu")
  {
    h1_Truth_Post_Lumi  ->Scale(LumiWeight_Muon_WpToMuNu_S8);
    h1_Post_PostFid_Lumi->Scale(LumiWeight_Muon_WpToMuNu_S8);
    h1_Post_BothFid_Lumi->Scale(LumiWeight_Muon_WpToMuNu_S8);
    h1_Born_BornFid_Lumi->Scale(LumiWeight_Muon_WpToMuNu_S8);
    h1_Born_BothFid_Lumi->Scale(LumiWeight_Muon_WpToMuNu_S8);
    sprintf(tmpName,"h1_WpMu_BothOvTruth");
    h1_Post_BothOvTruth = (TH1D*)f_Eff->Get(tmpName)->Clone();
    sprintf(tmpName,"h1_WpMu_BothOvTruth_weightFSR");
    h1_Post_BothOvTruth_weightFSR = (TH1D*)f_Eff->Get(tmpName)->Clone();
    sprintf(tmpName,"h1_WpMu_BothOvBorn");
    h1_Born_BothOvBorn = (TH1D*)f_Eff->Get(tmpName)->Clone();
  }
  else if(BaseName == "WmToMuNu")
  {
    h1_Truth_Post_Lumi  ->Scale(LumiWeight_Muon_WmToMuNu_S8);
    h1_Post_PostFid_Lumi->Scale(LumiWeight_Muon_WmToMuNu_S8);
    h1_Post_BothFid_Lumi->Scale(LumiWeight_Muon_WmToMuNu_S8);
    h1_Born_BornFid_Lumi->Scale(LumiWeight_Muon_WmToMuNu_S8);
    h1_Born_BothFid_Lumi->Scale(LumiWeight_Muon_WmToMuNu_S8);
    sprintf(tmpName,"h1_WmMu_BothOvTruth");
    h1_Post_BothOvTruth = (TH1D*)f_Eff->Get(tmpName)->Clone();
    sprintf(tmpName,"h1_WmMu_BothOvTruth_weightFSR");
    h1_Post_BothOvTruth_weightFSR = (TH1D*)f_Eff->Get(tmpName)->Clone();
    sprintf(tmpName,"h1_WmMu_BothOvBorn");
    h1_Born_BothOvBorn = (TH1D*)f_Eff->Get(tmpName)->Clone();
  }
  else if(BaseName == "WpToEleNu")
  {
    h1_Truth_Post_Lumi->  Scale(LumiWeight_Ele_WpToEleNu_S8);
    h1_Post_PostFid_Lumi->Scale(LumiWeight_Ele_WpToEleNu_S8);
    h1_Post_BothFid_Lumi->Scale(LumiWeight_Ele_WpToEleNu_S8);
    h1_Born_BornFid_Lumi->Scale(LumiWeight_Ele_WpToEleNu_S8);
    h1_Born_BothFid_Lumi->Scale(LumiWeight_Ele_WpToEleNu_S8);
    sprintf(tmpName,"h1_WpEl_BothOvTruth");
    h1_Post_BothOvTruth = (TH1D*)f_Eff->Get(tmpName)->Clone();
    sprintf(tmpName,"h1_WpEl_BothOvTruth_weightFSR");
    h1_Post_BothOvTruth_weightFSR = (TH1D*)f_Eff->Get(tmpName)->Clone();
    sprintf(tmpName,"h1_WpEl_BothOvBorn");
    h1_Born_BothOvBorn = (TH1D*)f_Eff->Get(tmpName)->Clone();
  }
  else if(BaseName == "WmToEleNu")
  {
    h1_Truth_Post_Lumi->  Scale(LumiWeight_Ele_WmToEleNu_S8);
    h1_Post_PostFid_Lumi->Scale(LumiWeight_Ele_WmToEleNu_S8);
    h1_Post_BothFid_Lumi->Scale(LumiWeight_Ele_WmToEleNu_S8);
    h1_Born_BornFid_Lumi->Scale(LumiWeight_Ele_WmToEleNu_S8);
    h1_Born_BothFid_Lumi->Scale(LumiWeight_Ele_WmToEleNu_S8);
    sprintf(tmpName,"h1_WmEl_BothOvTruth");
    h1_Post_BothOvTruth = (TH1D*)f_Eff->Get(tmpName)->Clone();
    sprintf(tmpName,"h1_WmEl_BothOvTruth_weightFSR");
    h1_Post_BothOvTruth_weightFSR = (TH1D*)f_Eff->Get(tmpName)->Clone();
    sprintf(tmpName,"h1_WmEl_BothOvBorn");
    h1_Born_BothOvBorn = (TH1D*)f_Eff->Get(tmpName)->Clone();
  }
  else{
    cout<<"Error: there is no BaseName corresponding to "<<BaseName<<endl;
    exit(-1);
  }

  // Histogram from Data
  if(BaseName == "WpToMuNu" || BaseName == "WpToEleNu")
  {
    sprintf(tmpName,"hSigWPpt");
    h1_Data_SigYild = (TH1D*)f_Data->Get(tmpName)->Clone(tmpName);
  }else if(BaseName == "WmToMuNu" || BaseName == "WmToEleNu")
  {
    sprintf(tmpName,"hSigWMpt");
    h1_Data_SigYild = (TH1D*)f_Data->Get(tmpName)->Clone(tmpName);
  }else{
    cout<<"Error: Check the BaseName !!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
    exit(-1);
  }

  double RDNumb = h1_Data_SigYild->Integral();
  //Fout<<"Real Data: "<<RDNumb<<endl;

   // Histo for SVD
  double checkNumber(0);

  for(int i(1);i<=nbins;i++)
  {
    h1_Post_BothOvTruth_eqBin -> SetBinContent(i,h1_Post_BothOvTruth->GetBinContent(i));
    h1_Post_BothOvTruth_eqBin -> SetBinError(i,h1_Post_BothOvTruth->GetBinError(i));
    h1_Born_BothOvBorn_eqBin -> SetBinContent(i,h1_Born_BothOvBorn->GetBinContent(i));
    h1_Born_BothOvBorn_eqBin -> SetBinError(i,h1_Born_BothOvBorn->GetBinError(i));
  }

  //=================================================================
  //=================================================================
  // Unfolding from Rec to Post           ===========================
  //=================================================================
  //=================================================================
  //
  //=====================
  // TSVD
  //=====================
  TRandom3 R;
  //===============
  // Data Unfolding
  //===============
  
  SVD_Post.RecoEffiCovMat =(TH2D*)f_RecoEffiCovMat->Get("h2_RecoEffiCovMat")->Clone();
  SVD_Post.RecoSmearCovMat =(TH2D*)f_RecoSmearCovMat->Get("h2_RecoSmearCovMat")->Clone();
  SVD_Post.RecoRecoilCovMat =(TH2D*)f_RecoRecoilCovMat->Get("h2_RecoRecoilCovMat")->Clone();
  if(BaseName == "WpToMuNu" || BaseName == "WmToMuNu" )
    SVD_Post.RecoQCDRatioCovMat =(TH2D*)f_RecoQCDRatioCovMat->Get("h2_RecoQCDRatioCovMat")->Clone();
  if(BaseName == "WpToEleNu" || BaseName == "WmToEleNu" )
    SVD_Post.RecoScaleCovMat =(TH2D*)f_RecoScaleCovMat->Get("h2_RecoScaleCovMat")->Clone();
  
  SVD_Post.TotalRecoCovMat->Add(SVD_Post.RecoEffiCovMat );
  SVD_Post.TotalRecoCovMat->Add(SVD_Post.RecoSmearCovMat );
  SVD_Post.TotalRecoCovMat->Add(SVD_Post.RecoRecoilCovMat );
  if(BaseName == "WpToEleNu" || BaseName == "WmToEleNu" )
    SVD_Post.TotalRecoCovMat->Add(SVD_Post.RecoScaleCovMat );

  //=================================================================
  // Poisson distribution
  //=================================================================
  
  CPlot *pltPoisson;

  TSVDUnfold *tsvdData[nToy];
  TSVDUnfold *svdBorn[nToy];
  
  RooRealVar x("x","", 0,600);
  
  RooRealVar c1("c1","",0.1,-1,1);
  RooRealVar c2("c2","",0.1,-1,1);
  RooRealVar c3("c3","",0.1,-1,1);
  RooRealVar c4("c4","",0.1,-1,1);
  
  RooRealVar d1("d1","",0.1,-1,1);
  RooRealVar d2("d2","",0.1,-1,1);
  RooRealVar d3("d3","",0.1,-1,1);
  RooRealVar d4("d4","",0.1,-1,1);


  if(BaseName == "WpToMuNu"){
    c1.setVal(-0.364042 );
    c2.setVal(0.0572473 );
    c3.setVal(-0.0042756 );
    c4.setVal(0.000121166 );
    d1.setVal(-0.366776);
    d2.setVal(0.0578532);
    d3.setVal(-0.00432019);
    d4.setVal(0.000122256);
  }else if (BaseName == "WmToMuNu" ){
    c1.setVal(-0.350896 );
    c2.setVal(0.0540635 );
    c3.setVal(-0.00401806 );
    c4.setVal(0.000114203 );
    d1.setVal(-0.35391);
    d2.setVal(0.0547905);
    d3.setVal(-0.00407681);
    d4.setVal(0.000115792);
  }else if (BaseName == "WpToEleNu" ){
    c1.setVal(-0.351337);
    c2.setVal(0.0544906 );
    c3.setVal(-0.00408053 );
    c4.setVal(0.000116708 );
    d1.setVal(-0.370515);
    d2.setVal(0.0589071);
    d3.setVal(-0.00441764);
    d4.setVal(0.000125221);
  }else if (BaseName == "WmToEleNu" ){
    c1.setVal(-0.338061);
    c2.setVal(0.0512756 );
    c3.setVal(-0.00381884 );
    c4.setVal(0.000109534 );
    d1.setVal(-0.360669);
    d2.setVal(0.0567861);
    d3.setVal(-0.00426745);
    d4.setVal(0.000121726);
  }
  c1.setConstant(kTRUE);
  c2.setConstant(kTRUE);
  c3.setConstant(kTRUE);
  c4.setConstant(kTRUE);
  d1.setConstant(kTRUE);
  d2.setConstant(kTRUE);
  d3.setConstant(kTRUE);
  d4.setConstant(kTRUE);
  
  RooPolynomial DetPoly("DetPoly", "", x, RooArgList(c1,c2,c3,c4));
  RooPolynomial FSRPoly("FSRPoly", "", x, RooArgList(d1,d2,d3,d4));

  TH1D* hGenDet;
  TH1D* hGenDetNorm;
  TH1D* hGenFSR;
  TH1D* hGenFSRNorm;
  
  //RooBinning myBins(13,Bins);
  RooBinning myBins(13,nBins);
  hGenDet = (TH1D*)(DetPoly.createHistogram("hGenDet",x,Binning(myBins))); //GenLevel
  hGenFSR = (TH1D*)(FSRPoly.createHistogram("hGenFSR",x,Binning(myBins))); //GenLevel

  double Ndet = hGenDet->Integral();
  hGenDet->Scale(h1_Truth_Rec->Integral()/Ndet);
  hGenDet->SetTitle("");
  hGenDet->Write();
  
  double Nfsr = hGenFSR->Integral();
  hGenFSR->Scale(h1_Post_BothFid->Integral()/Nfsr);
  hGenFSR->SetTitle("");
  hGenFSR->Write();

  //Response Matrix
  TMatrixD dResponseMatrix(nbins,nbins);
  TMatrixD fsrResponseMatrix(nbins,nbins);
  double temp1[nbins];
  double temp2[nbins];

  for(int i(1);i<=nbins;i++)
  {
    for( int j(1);j<=nbins;j++)
    {
      SVD_Post.Adet->SetBinContent(i,j,h2_Truth_Rec_AP_PostEffCorr->GetBinContent(i,j));
      dResponseMatrix(i-1,j-1) = h2_Truth_Rec_AP_PostEffCorr->GetBinContent(i,j);
      
      SVD_Born.Adet->SetBinContent(i,j,h2_PostBorn_BothFid->GetBinContent(i,j));
      fsrResponseMatrix(i-1,j-1) = h2_PostBorn_BothFid->GetBinContent(i,j);
    }
  }
  
  for(int i(0);i<nbins;i++)
  {
    temp1[i] = 0.;
    temp2[i] = 0.;
    for( int j(0);j<nbins;j++)
    {
      temp1[i] += dResponseMatrix(j,i);
      temp2[i] += fsrResponseMatrix(j,i);
    }
  }

  for(int i(0);i<nbins;i++)
  {
    for( int j(0);j<nbins;j++)
    {
      dResponseMatrix(i,j) /= temp1[j];
      fsrResponseMatrix(i,j) /= temp2[j];
    }
  }

  TH1D* hDet = new TH1D("hDet","hDet",13,0,13);//Detector Distribution
  TH1D* hFSR = new TH1D("hFSR","hFSR",13,0,13);//FSR Distribution
  TH1D* hToyDet;
  TH1D* hToyFSR;
 
  double tmp1;
  double tmp2;
 
//Folding Gen. level and Make detector distribution
  for(int i(1);i<=h1_Data_SigYild->GetNbinsX();i++)
  {
    tmp1 = 0.0;
    tmp2 = 0.0;
    for(int j(1);j<=h1_Data_SigYild->GetNbinsX();j++)
    {
      tmp1 += dResponseMatrix(i-1,j-1)*hGenDet->GetBinContent(j);
      tmp2 += fsrResponseMatrix(i-1,j-1)*hGenFSR->GetBinContent(j);
    }
    hDet->SetBinContent(i,tmp1);
    hFSR->SetBinContent(i,tmp2);
    
    SVD_Post.xini->SetBinContent(i,hGenDet->GetBinContent(i));
    SVD_Post.xini->SetBinError(i,hGenDet->GetBinError(i));
    
    SVD_Post.bini->SetBinContent(i,hDet->GetBinContent(i));
    SVD_Post.bini->SetBinError(i,hDet->GetBinError(i));
    
    SVD_Born.xini->SetBinContent(i,hGenFSR->GetBinContent(i));
    SVD_Born.xini->SetBinError(i,hGenFSR->GetBinError(i));
    
    SVD_Born.bini->SetBinContent(i,hFSR->GetBinContent(i));
    SVD_Born.bini->SetBinError(i,hFSR->GetBinError(i));
  }
  hDet->Write();
  hFSR->Write();
  
  hToyDet = (TH1D*)hDet->Clone("hToyDet");
  hGenDetNorm = (TH1D*)hGenDet->Clone("hGenDetNorm");
  
  hToyFSR = (TH1D*)hFSR->Clone("hToyFSR");
  hGenFSRNorm = (TH1D*)hGenFSR->Clone("hGenFSRNorm");

  hToyDet->Scale(h1_Data_SigYild->Integral()/hToyDet->Integral());
  hGenDetNorm->Scale(h1_Data_SigYild->Integral()/hGenDetNorm->Integral());
  hGenDetNorm->Write();

  hToyFSR->Scale(h1_Data_SigYild->Integral()/hToyFSR->Integral());
  hGenFSRNorm->Scale(h1_Data_SigYild->Integral()/hGenFSRNorm->Integral());
  hGenFSRNorm->Write();
  
  TRandom3 dRandom[13];
  TRandom3 fRandom[13];

  for(int nLoop(0);nLoop<nToy;nLoop++)
  {
    double dBinContent[13] = {0.};
    double fBinContent[13] = {0.};

    dRandom[0].SetSeed(1+13*(idx*nToy+nLoop));
    dRandom[1].SetSeed(2+13*(idx*nToy+nLoop));
    dRandom[2].SetSeed(3+13*(idx*nToy+nLoop));
    dRandom[3].SetSeed(4+13*(idx*nToy+nLoop));
    dRandom[4].SetSeed(5+13*(idx*nToy+nLoop));
    dRandom[5].SetSeed(6+13*(idx*nToy+nLoop));
    dRandom[6].SetSeed(7+13*(idx*nToy+nLoop));
    dRandom[7].SetSeed(8+13*(idx*nToy+nLoop));
    dRandom[8].SetSeed(9+13*(idx*nToy+nLoop));
    dRandom[9].SetSeed(10+13*(idx*nToy+nLoop));
    dRandom[10].SetSeed(11+13*(idx*nToy+nLoop));
    dRandom[11].SetSeed(12+13*(idx*nToy+nLoop));
    dRandom[12].SetSeed(13+13*(idx*nToy+nLoop));

    fRandom[0].SetSeed(7001+13*(idx*nToy+nLoop));
    fRandom[1].SetSeed(7002+13*(idx*nToy+nLoop));
    fRandom[2].SetSeed(7003+13*(idx*nToy+nLoop));
    fRandom[3].SetSeed(7004+13*(idx*nToy+nLoop));
    fRandom[4].SetSeed(7005+13*(idx*nToy+nLoop));
    fRandom[5].SetSeed(7006+13*(idx*nToy+nLoop));
    fRandom[6].SetSeed(7007+13*(idx*nToy+nLoop));
    fRandom[7].SetSeed(7008+13*(idx*nToy+nLoop));
    fRandom[8].SetSeed(7009+13*(idx*nToy+nLoop));
    fRandom[9].SetSeed(7010+13*(idx*nToy+nLoop));
    fRandom[10].SetSeed(7011+13*(idx*nToy+nLoop));
    fRandom[11].SetSeed(7012+13*(idx*nToy+nLoop));
    fRandom[12].SetSeed(7013+13*(idx*nToy+nLoop));
    
    for(int i(1);i<=h1_Data_SigYild->GetNbinsX();i++)
    {
      for(int j(0);j<hToyDet->GetBinContent(i);j++)
      {
	dBinContent[i-1] += dRandom[i-1].Poisson(hToyDet->GetBinContent(i));
      }

      for(int j(0);j<hToyFSR->GetBinContent(i);j++)
      {
	fBinContent[i-1] += fRandom[i-1].Poisson(hToyFSR->GetBinContent(i));
      }
    }

    //TODO data from toy
    sprintf(tmpName,"SVD_Post.data_%d",nLoop);
    SVD_Post.data[nLoop] = new TH1D(tmpName,tmpName,NWptBinPlus-1,0,NWptBinPlus-1);
    
    sprintf(tmpName,"SVD_Post.ToyStatCovMat_%d",nLoop);
    SVD_Post.ToyStatCovMat[nLoop] = new TH2D(tmpName,tmpName
	,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
    
    sprintf(tmpName,"SVD_Post.ToyRecoCovMat_%d",nLoop);
    SVD_Post.ToyRecoCovMat[nLoop] = new TH2D(tmpName,"Total Reco Stage Covariace matrix"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
    
    sprintf(tmpName,"SVD_Post.DetUnf_%d",nLoop);
    SVD_Post.DetUnf[nLoop] = new TH1D(tmpName,tmpName,13,Bins);
    
    sprintf(tmpName,"SVD_Born.data_%d",nLoop);
    SVD_Born.data[nLoop] = new TH1D(tmpName,tmpName,NWptBinPlus-1,0,NWptBinPlus-1);
    
    sprintf(tmpName,"SVD_Born.ToyStatCovMat_%d",nLoop);
    SVD_Born.ToyStatCovMat[nLoop] = new TH2D(tmpName,tmpName,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);

    sprintf(tmpName,"SVD_Born.FSRUnf_%d",nLoop);
    SVD_Born.FSRUnf[nLoop] = new TH1D(tmpName,tmpName,13,Bins);
  
    for(int i(1);i<=h1_Data_SigYild->GetNbinsX();i++)
    {
      SVD_Post.data[nLoop]->SetBinContent(i,dBinContent[i-1]/hToyDet->GetBinContent(i));
      SVD_Born.data[nLoop]->SetBinContent(i,fBinContent[i-1]/hToyFSR->GetBinContent(i));

      for( int j(1); j<= h1_Data_SigYild->GetNbinsX(); j++)
      {
	if (i==j)
	{
	  SVD_Post.ToyStatCovMat[nLoop]->SetBinContent(i,i,dBinContent[i-1]/hToyDet->GetBinContent(i));
	  SVD_Born.ToyStatCovMat[nLoop]->SetBinContent(i,i,fBinContent[i-1]/hToyFSR->GetBinContent(i));
	}else{
	  SVD_Post.ToyStatCovMat[nLoop]->SetBinContent(i,j,0.);
	  SVD_Born.ToyStatCovMat[nLoop]->SetBinContent(i,j,0.);
	}
      }
    }
    
    SVD_Post.ToyRecoCovMat[nLoop]->Add(SVD_Post.TotalRecoCovMat);
    SVD_Post.ToyRecoCovMat[nLoop]->Add(SVD_Post.ToyStatCovMat[nLoop]);
  
    //=================================================================
    //=================================================================
    // Detector Unfolding (Error propagation of Cov matrix) ===========
    //=================================================================
    //=================================================================

    cout<<"Detector Unfolding"<<endl;
    tsvdData[nLoop] = new TSVDUnfold(
	SVD_Post.data[nLoop],SVD_Post.ToyRecoCovMat[nLoop],SVD_Post.bini,SVD_Post.xini,SVD_Post.Adet);

    tsvdData[nLoop]->SetNormalize( kFALSE );
    SVD_Post.unfRes[nLoop] = tsvdData[nLoop]->Unfold(3); 
    SVD_Post.dDist[nLoop] = tsvdData[nLoop]->GetD();
    SVD_Post.svDist[nLoop] = tsvdData[nLoop]->GetSV();
    
    for(int i(1);i<=h1_Data_SigYild->GetNbinsX();i++)
    {
      SVD_Post.DetUnf[nLoop] -> SetBinContent(i,SVD_Post.unfRes[nLoop]->GetBinContent(i));
    }
    
    cout<<"FSR Unfolding"<<endl;
    svdBorn[nLoop] = new TSVDUnfold(
	SVD_Born.data[nLoop],SVD_Born.ToyStatCovMat[nLoop],SVD_Born.bini,SVD_Born.xini,SVD_Born.Adet);

    svdBorn[nLoop]->SetNormalize( kFALSE );
    SVD_Born.unfRes[nLoop] = svdBorn[nLoop]->Unfold(3); 
    SVD_Born.dDist[nLoop] = svdBorn[nLoop]->GetD();
    SVD_Born.svDist[nLoop] = svdBorn[nLoop]->GetSV();
    
    for(int i(1);i<=h1_Data_SigYild->GetNbinsX();i++)
    {
      SVD_Born.FSRUnf[nLoop] -> SetBinContent(i,SVD_Born.unfRes[nLoop]->GetBinContent(i));
      cout<<SVD_Post.DetUnf[nLoop]->GetBinContent(i)<<" +/- "<<SVD_Post.DetUnf[nLoop] -> GetBinError(i)<<"\t"<<SVD_Born.FSRUnf[nLoop]->GetBinContent(i)<<" +/- "<<SVD_Born.FSRUnf[nLoop]->GetBinError(i)<<endl;
      //cout<<SVD_Post.DetUnf[nLoop]->GetBinContent(i)<<" +/- "<<SVD_Post.DetUnf[nLoop] -> GetBinError(i)<<"\t"<<SVD_Born.FSRUnf[nLoop]->GetBinContent(i)<<" +/- "<<SVD_Born.FSRUnf[nLoop]->GetBinError(i)<<endl;
    }
    
    // Write to root file
    SVD_Post.data[nLoop]->Write();	//Toy data (Input to detector Unfolding)
    SVD_Post.DetUnf[nLoop] -> Write();	//Detector Unfolded toy
    SVD_Born.data[nLoop]->Write();	//Toy data (Input to FSR Unfolding)
    SVD_Born.FSRUnf[nLoop] -> Write();	//FSR Unfolded toy
  }
  return 0;
}
