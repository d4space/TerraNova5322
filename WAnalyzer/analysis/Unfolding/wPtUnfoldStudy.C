#include "TStyle.h"
#include "../Utils/const.h"
#include "../Utils/CPlot.hh"
#include "../Utils/MitStyleRemix.hh"
#include "../Utils/Unfolder.h"
//#include <iostream>
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

#if not defined(__CINT__) || defined(__MAKECINT__)
#include "TSVDUnfold.h"
#endif
 
//#define TSVDSelfTestPost

int wPtUnfoldStudy
(TString UnfoldFile,TString AcceptFile,TString DataFile, TString DataYieldFile, TString BaseName)
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

  cout<<"Processing "<<BaseName<<endl;
  cout<<"Unfolding Inpufile: "<<UnfoldFile<<endl;
  cout<<"Acceptance Inpufile: "<<AcceptFile<<endl;
  cout<<"Data Inpufile: "<<DataFile<<endl;

  TString resultDir = "Result"+BaseName;
  gSystem->mkdir(resultDir,kTRUE);
  char tmpName[30];
  TString tmpTStr;
  
  ofstream Fout;
  Fout.open(resultDir+"/Systematics.txt");
  
  //ofstream of_Post_WpT_PostFid;

  TFile *f_Unfold    = new TFile(UnfoldFile);
  TFile *f_Accept    = new TFile(AcceptFile);
  TFile *f_Data      = new TFile(DataFile);
  TFile *f_DataYield = new TFile(DataYieldFile);

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
  TFile *f_RecoFSRCovMat;
  
  f_RecoLumiUpCovMat   = new TFile("RecoCovMatrix/SigYields_Lumi_Up.root");
  f_RecoLumiDownCovMat = new TFile("RecoCovMatrix/SigYields_Lumi_Down.root");
  f_RecoFSRCovMat      = new TFile("RecoCovMatrix/SigYields_Muon_FSR.root");
  
  TH1D* h1_SigWptLumiUp;
  TH1D* h1_SigWptLumiDown;
  TH1D* h1_SigWptFSR;
  TH1D *h1_Post_BothFidAccept;
  TH1D *h1_Post_BothFidAcceptFSR;

  TFile *f_Eff    = new TFile("ResultUnfEff/eff.root");
  tmpTStr = resultDir+"/Result_"+BaseName+".root";
  TFile *f_Out    = new TFile(tmpTStr,"recreate");

  //tmpTStr= resultDir+"/"+"Post_PostFid.txt";
  //of_Post_WpT_PostFid.open(tmpTStr);

  //TStyle *myStyle=new TStyle("myStyle","myStyle");
  //myStyle->SetPalette(1);
  //gStyle->SetPalette(1);
  // SVD input
  struct histSVD{
    TH2D *Adet;
    TH2D *uAdetCov;
    TH1D *xini; // Post True
    TH1D *bini; // Reco Truth
    TH1D *data;
    TH1D *True;
    TH1D *Gen;
    TH1D *EffCorr;
    TH2D *statCov;
    TH1D *unfRes;
    TH1D *dDist;
    TH1D *svDist;
    TH2D *uTotalCovMat;
    TH2D *uTotalSystCov;
    TH2D *uStatCov;
    TH2D *uTauCov;
    TH2D *uInvCov;

    TH2D *BstatCov;
    TH2D *BstatCorr;
    TH2D *BstatCorr_uTotal; //Total Correlation Matrix
    TH2D *AbsNormCorrErr; //Absolute Normilazed Correlated Error Matrix
    
    TH2D *RecoEffiCovMat;
    TH2D *RecoScaleCovMat;
    TH2D *RecoSmearCovMat;
    TH2D *RecoRecoilCovMat;
    TH2D *RecoLumiCovMat;
    TH2D *RecoFSRCovMat;
    TH2D *RecoStatisticCovMat;
    TH2D *RecoQCDRatioCovMat;
    TH2D *TotalRecoCovMat;

    TH2D *InputCovMat; //Input Covariance Matrix for FSR Unfolding
    TH2D *uInputCovMat;//Input Covariance Matrix after FSR Unfolding
    
    TH2D *uRecoEffiCovMat;
    TH2D *uRecoScaleCovMat;
    TH2D *uRecoSmearCovMat;
    TH2D *uRecoRecoilCovMat;
    TH2D *uRecoLumiCovMat;
    TH2D *uRecoFSRCovMat;
    TH2D *uRecoStatisticCovMat;
    TH2D *uRecoQCDRatioCovMat;
    TH2D *uRecoRespCovMat;

    TH2D *uTotalRecoCovMat;
    TH2D *AcceptFSRCovMat;
    TH2D *EffFSRCovMat; //Make FSR Covariance Matrix from MC Eff.

    TH2D *Eff_uRecoEffiCovMat;
    TH2D *Eff_uRecoScaleCovMat;
    TH2D *Eff_uRecoSmearCovMat;
    TH2D *Eff_uRecoRecoilCovMat;
    TH2D *Eff_uRecoLumiCovMat;
    TH2D *Eff_uRecoFSRCovMat;
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
  double XMean[13]={0.0};
  double YMean[13];
  
  int NumOfSamples=500;
  //TH1D* h1_Data_Yield[500];
  TH1D* h1_Data_Yield[501];
      
  double Xcontent[13][500]={{0.0},{0.0}};
  //  double Total[13][100]={{0.0},{0.0}};
  double Total[13][500]={0.0};
  double CovMult[13][500]={{1.0},{1.0}};
  
  double XMeanMinusXBinCont[500]={0.0};
  
  double XMeanMinusXBinContSum[169]={0.0};
  double XMeanMinusXBinContSumTwo[14][14];
  //TH1D* XMeanMinusXBinCont[100];
  TH1D* YMeanMinusYBinCont[500];
  
  TH1D* h1_Data_SigYild;
  TH1D* h1_SVD_Post_data[501];
  TH1D* h1_SVD_Born_EffCorr[501];
  TH1D* h1_SVD_Born_Gen[501];
  TH1D* h1_SVD_Post_True[501];
  TH1D* h1_SVD_Post_unfRes[501];
  TH1D* h1_SVD_Post_Gen[501];

  // Define Histo
  h1_Post_BothOvTruth_eqBin=
    new TH1D("h1_Post_BothOvTruth_eqBin","BothOvTruth",NWptBinPlus-1,0,NWptBinPlus-1);
  h1_Post_BothOvTruth_weightFSR_eqBin=
    new TH1D("h1_Post_BothOvTruth_weightFSR_eqBin","BothOvTruth_weightFSR",NWptBinPlus-1,0,NWptBinPlus-1);
  h1_Born_BothOvBorn_eqBin=
    new TH1D("h1_Born_BothOvBorn_eqBin","BothOvBorn",NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Post.xini = new TH1D("xini_Post","Post true",NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Post.bini = new TH1D("bini_Post","Reco thruth" ,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Post.data = new TH1D("data_Rec","data_Rec"    ,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Post.True = new TH1D("SVD_Post.True","SVD_Post.True",NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Post.Gen  = new TH1D("SVD_Post.Gen","SVD_Post.Gen",NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Post.Adet = new TH2D("Adet_Post","detector response"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Post.statCov = new TH2D("SVD_Post.statCov","Covariance matrix"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Post.BstatCov = new TH2D("SVD_Post.BstatCov","Covariance matrix"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  //SVD_Post.BstatCov =
  //  new TH2D("SVD_Post.BstatCov","Covariance matrix",
  //	100,0,100,100,0,100);
  SVD_Post.BstatCorr = new TH2D("SVD_Post.BstatCorr","Correlation matrix"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Post.BstatCorr_uTotal = new TH2D("SVD_Post.BstatCorr_uTotal","Total Correlation matrix after D_Unf"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Post.AbsNormCorrErr = new TH2D("SVD_Post.AbsNormCorrErr","Absolute Normalized Correlated Error Matrix D_Unf"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Born.AbsNormCorrErr = new TH2D("SVD_Born.AbsNormCorrErr","Absolute Normalized Correlated Error Matrix FSR_Unf"
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
  SVD_Post.RecoFSRCovMat = new TH2D("SVD_Post.RecoFSRCovMat","Reco Stage FSR Covariace matrix"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  TH2D* h2_RecoFSRCovMat = new TH2D("h2_RecoFSRCovMat","Reco Stage FSR Covariace matrix"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Post.Eff_uRecoFSRCovMat = new TH2D("SVD_Post.Eff_uRecoFSRCovMat","Eff applied FSR Covariace matrix Detector unfolding"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Post.AcceptFSRCovMat = new TH2D("SVD_Post.AcceptFSRCovMat","FSR CovMat from Acceptance h1_Post_BothFid"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Post.EffFSRCovMat = new TH2D("SVD_Post.EffFSRCovMat","FSR CovMat from MC Eff h1_Post_BothOvTruth_weightFSR"
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
  SVD_Born.data = new TH1D("data_Born","data_Rec"    ,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Born.True = new TH1D("SVD_Born.True","Born.True",NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Born.Gen  = new TH1D("SVD_Born.Gen","Born.Gen",NWptBinPlus-1,0,NWptBinPlus-1);
  //SVD_Born.Gen=new TH1D("SVD_Born.Gen","Born.Gen",NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Born.Adet = new TH2D("Adet_Born","detector response",NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Born.statCov = new TH2D("SVD_Born.statCov","Covariance matrix",NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  
  // Plot
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

  cout<<"Simulated event========================="<<endl;
  int nbins = h1_Truth_Rec->GetNbinsX();
  cout<<"Nsimul N of bins: "<<nbins<<endl;
  double Nsimul = h1_Truth_Rec->Integral();
  cout<<"Total Events: "<<setw(20)<<setprecision(7)<<Nsimul<<endl;
  double NsimulEven = h1_Truth_Rec_Even->Integral();
  cout<<"NsimulEven: "<<setw(20)<<setprecision(7)<<NsimulEven<<endl;
  double NsimulOdd = h1_Truth_Rec_Odd->Integral();
  cout<<"NsimulOdd: "<<setw(20)<<setprecision(7)<<NsimulOdd<<endl;
  double NdetectorResponse = h2_Truth_Rec_AP_Post->Integral();
  cout<<"NdetectorResponse: "<<NdetectorResponse<<endl;
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
   
  for(int i(1);i<=h1_Data_SigYild->GetNbinsX();i++)
  {
    cout<<"Nominal: "<<h1_Data_SigYild->GetBinContent(i)<<"\t"<<h1_Data_SigYild->GetBinError(i)<<endl;
  }

  for(int i(1); i<=NumOfSamples; i++)
  {
    if( BaseName == "WpToEleNu" || BaseName == "WpToMuNu")
    {
      sprintf(tmpName,"hSigWPpt%d",i);
      h1_Data_Yield[i]	=(TH1D*)f_DataYield->Get(tmpName)->Clone(tmpName);
    }else if( BaseName == "WmToEleNu" || BaseName == "WmToMuNu"){
      sprintf(tmpName,"hSigWMpt%d",i);
      h1_Data_Yield[i]	=(TH1D*)f_DataYield->Get(tmpName)->Clone(tmpName);
    }else{
      cout<<"Error: Check the HistoName in DataYieldFile !!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
      exit(-1);
    }
  }
  
  for(int i(1);i<=h1_Data_Yield[1]->GetNbinsX();i++)
  {
    cout<<h1_Data_Yield[500]->GetBinContent(i)<<"\t"<<h1_Data_Yield[500]->GetBinError(i)<<endl;
  }

   
   // Histo for SVD
  double checkNumber(0);
  for(int i(1);i<=nbins;i++)//simul idx
  {
    // xini_Post : All Post without the truth efficiency at PostFid
    SVD_Post.xini->SetBinContent(i,h1_Truth_Post->GetBinContent(i));
    SVD_Post.xini->  SetBinError(i,h1_Truth_Post->GetBinError(i));

    SVD_Born.xini->SetBinContent(i,h1_Born_BothFid->GetBinContent(i));
    SVD_Born.xini->  SetBinError(i,h1_Born_BothFid->GetBinError(i));

    // Detector simulation one
    SVD_Post.bini->SetBinContent(i,h1_Truth_Rec->GetBinContent(i));
    SVD_Post.bini->  SetBinError(i,h1_Truth_Rec->GetBinError(i));

    SVD_Born.bini->SetBinContent(i,h1_Post_BothFid->GetBinContent(i));
    SVD_Born.bini->  SetBinError(i,h1_Post_BothFid->GetBinError(i));

    //TODO data from real
    SVD_Post.data->SetBinContent(i,h1_Data_SigYild->GetBinContent(i));
    SVD_Post.data->  SetBinError(i,h1_Data_SigYild->GetBinError(i));
    /// 500 loop for 500 unfolding
    //SVD_Post.data->SetBinContent(i,h1_Data_Yield[k]->GetBinContent(i));
    //SVD_Post.data->  SetBinError(i,h1_Data_Yield[k]->GetBinError(i));

    SVD_Post.True->SetBinContent(i,h1_Truth_Post_Lumi->GetBinContent(i));
    SVD_Post.True->  SetBinError(i,h1_Truth_Post_Lumi->GetBinError(i));
    SVD_Born.True->SetBinContent(i,h1_Born_BothFid_Lumi->GetBinContent(i));
    SVD_Born.True->  SetBinError(i,h1_Born_BothFid_Lumi->GetBinError(i));

    SVD_Post.Gen->SetBinContent(i,h1_Post_BothFid_Lumi->GetBinContent(i));
    SVD_Post.Gen->  SetBinError(i,h1_Post_BothFid_Lumi->GetBinError(i));
    SVD_Born.Gen->SetBinContent(i,h1_Born_BornFid_Lumi->GetBinContent(i));
    //SVD_Born.Gen->  SetBinError(i,h1_Born_BornFid_Lumi->GetBinError(i));
    SVD_Born.Gen->  SetBinError(i,sqrt(h1_Born_BornFid_Lumi->GetBinContent(i)));

    h1_Post_BothOvTruth_eqBin -> SetBinContent(i,h1_Post_BothOvTruth->GetBinContent(i));
    h1_Post_BothOvTruth_eqBin -> SetBinError(i,h1_Post_BothOvTruth->GetBinError(i));
    h1_Post_BothOvTruth_weightFSR_eqBin -> SetBinContent(i,h1_Post_BothOvTruth_weightFSR->GetBinContent(i));
    h1_Post_BothOvTruth_weightFSR_eqBin -> SetBinError(i,h1_Post_BothOvTruth_weightFSR->GetBinError(i));
    h1_Born_BothOvBorn_eqBin->SetBinContent(i,h1_Born_BothOvBorn->GetBinContent(i));
    h1_Born_BothOvBorn_eqBin->  SetBinError(i,h1_Born_BothOvBorn->GetBinError(i));

    //of_Post_WpT_PostFid<<h1_Post_WpT_PostFid->GetBinContent(i)<<endl;
    for( int j(1);j<=nbins;j++)//gen idx
    {
      if(i==5) checkNumber += h2_Truth_Rec_AP_Post->GetBinContent(i,j);
      SVD_Post.Adet->SetBinContent(i,j,h2_Truth_Rec_AP_Post->GetBinContent(i,j));
      SVD_Born.Adet->SetBinContent(i,j,h2_PostBorn_BothFid->GetBinContent(i,j));
      //Adet_Post->SetBinError(i,j,h2_Truth_Rec_AP_Post->GetBinError(i,j));
    }
  }
  cout<<"check the number 5th bin(h1,response) "<<h1_Truth_Rec->GetBinContent(5)<<" "<<checkNumber<<endl;
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
  cout<<" Input Data Yield ==============="<<endl;
  cout<<" SignalYield           Error"<<endl;
  
  for( int i(1); i<= SVD_Post.data->GetNbinsX(); i++)
  {
    cout<<SVD_Post.data->GetBinContent(i)<<"\t"<<SVD_Post.data->GetBinError(i)<<endl;
  }
  
 



  for( int i(0); i< 13; i++)
  {
    for( int k(0); k<NumOfSamples; k++)
    {
      //Xcontent[i][k]=Xcontent[i][k] + h1_Data_Yield[k+1]->GetBinContent(i+1) ;

      Xcontent[i][k]= h1_Data_Yield[k+1]->GetBinContent(i+1) ;
      cout<<"Xcontent[i][k]:  "<<"  i =  "<<i<<" k =  "<<k<<"  "<<Xcontent[i][k]<<endl;

    }
  }
  cout<<"Xcontent[0][3]:  "<<Xcontent[0][3]<<endl;
  

  
  
  
  for( int i(0); i< 13; i++)
  {
    for( int k(0); k<NumOfSamples ; k++)
    {
    
      //XMean[i]=h1_Data_SigYild->GetBinContent(i+1);
      XMean[i]=XMean[i]+Xcontent[i][k]/NumOfSamples;
    }
  }
  
  
  
  for( int i(0); i< 13; i++)
  {
    cout<<"XMean[i]:  "<<i<<"  "<<XMean[i]<<endl;
  }

 



  
  for( int k(1); k<= NumOfSamples; k++)
  {


//	cout<<"XMeanMinusXBin before    :  "<<"  i =0  "<<" k =  "<<k-1<<"  "<<XMeanMinusXBinContSum[0]<<endl;
//	cout<<"<X0>-Xi0                 :  "<<"  i =0  "<<" k =  "<<k-1<<"  "<<(XMean[0]- Xcontent[0][k-1] )<<endl;
//	cout<<"<X1>-Xi1                 :  "<<"  i =0  "<<" k =  "<<k-1<<"  "<<(XMean[0] - Xcontent[0][k-1])<<endl;
//	cout<<"<Multiply                :  "<<"  i =0  "<<" k =  "<<k-1<<"  "<<(XMean[0]- Xcontent[0][k-1] )*( XMean[0] - Xcontent[0][k-1])/NumOfSamples<<endl;
	XMeanMinusXBinContSum[0]= XMeanMinusXBinContSum[0] + (XMean[0]- Xcontent[0][k-1] )*( XMean[0] - Xcontent[0][k-1])/NumOfSamples;
//	cout<<"XMeanMinusXBinContSum[0] :  "<<"  i =0"<<"   k =  "<<k-1<<"  "<<XMeanMinusXBinContSum[0]<<endl;

//	cout<<"XMeanMinusXBin before    :  "<<"  i =1  "<<" k =  "<<k-1<<"  "<<XMeanMinusXBinContSum[1]<<endl;
//	cout<<"<X0>-Xi0                 :  "<<"  i =1  "<<" k =  "<<k-1<<"  "<<(XMean[0]- Xcontent[0][k-1] )<<endl;
//	cout<<"<X1>-Xi1                 :  "<<"  i =1  "<<" k =  "<<k-1<<"  "<<(XMean[1] - Xcontent[1][k-1])<<endl;
//	cout<<"<Multiply                :  "<<"  i =1  "<<" k =  "<<k-1<<"  "<<(XMean[0]- Xcontent[0][k-1] )*( XMean[1] - Xcontent[1][k-1])<<endl;
	XMeanMinusXBinContSum[1]= XMeanMinusXBinContSum[1] + (XMean[0]- Xcontent[0][k-1] )*( XMean[1] - Xcontent[1][k-1])/NumOfSamples;
//	cout<<"XMeanMinusXBinContSum[1] :  "<<"  i =1"<<"   k =  "<<k-1<<"  "<<XMeanMinusXBinContSum[1]<<endl;

	XMeanMinusXBinContSum[2]= XMeanMinusXBinContSum[2] + (XMean[0]- Xcontent[0][k-1] )*( XMean[2] - Xcontent[2][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[3]= XMeanMinusXBinContSum[3] + (XMean[0]- Xcontent[0][k-1] )*( XMean[3] - Xcontent[3][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[4]= XMeanMinusXBinContSum[4] + (XMean[0]- Xcontent[0][k-1] )*( XMean[4] - Xcontent[4][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[5]= XMeanMinusXBinContSum[5] + (XMean[0]- Xcontent[0][k-1] )*( XMean[5] - Xcontent[5][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[6]= XMeanMinusXBinContSum[6] + (XMean[0]- Xcontent[0][k-1] )*( XMean[6] - Xcontent[6][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[7]= XMeanMinusXBinContSum[7] + (XMean[0]- Xcontent[0][k-1] )*( XMean[7] - Xcontent[7][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[8]= XMeanMinusXBinContSum[8] + (XMean[0]- Xcontent[0][k-1] )*( XMean[8] - Xcontent[8][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[9]= XMeanMinusXBinContSum[9] + (XMean[0]- Xcontent[0][k-1] )*( XMean[9] - Xcontent[9][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[10]= XMeanMinusXBinContSum[10] + (XMean[0]- Xcontent[0][k-1] )*( XMean[10] - Xcontent[10][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[11]= XMeanMinusXBinContSum[11] + (XMean[0]- Xcontent[0][k-1] )*( XMean[11] - Xcontent[11][k-1])/NumOfSamples;

//	cout<<"XMeanMinusXBin before    :  "<<"  i =0  "<<" k =  "<<k-1<<"  "<<XMeanMinusXBinContSum[12]<<endl;
//	cout<<"<X0>-Xi0                 :  "<<"  i =0  "<<" k =  "<<k-1<<"  "<<(XMean[0]- Xcontent[0][k-1] )<<endl;
//	cout<<"<X1>-Xi1                 :  "<<"  i =0  "<<" k =  "<<k-1<<"  "<<(XMean[12] - Xcontent[12][k-1])<<endl;
//	cout<<"<Multiply                :  "<<"  i =0  "<<" k =  "<<k-1<<"  "<<(XMean[0]- Xcontent[0][k-1] )*( XMean[12] - Xcontent[12][k-1])<<endl;
	XMeanMinusXBinContSum[12]= XMeanMinusXBinContSum[12] + (XMean[0]- Xcontent[0][k-1] )*( XMean[12] - Xcontent[12][k-1])/NumOfSamples;
//	cout<<"XMeanMinusXBinContSum[12] :  "<<"  i =0"<<"   k =  "<<k-1<<"  "<<XMeanMinusXBinContSum[12]<<endl;

	XMeanMinusXBinContSum[13]= XMeanMinusXBinContSum[13] + (XMean[1]- Xcontent[1][k-1] )*( XMean[0] - Xcontent[0][k-1])/NumOfSamples;

//	cout<<"XMeanMinusXBin before    :  "<<"  i =1  "<<" k =  "<<k-1<<"  "<<XMeanMinusXBinContSum[14]<<endl;
//	cout<<"<X0>-Xi0                 :  "<<"  i =1  "<<" k =  "<<k-1<<"  "<<(XMean[1]- Xcontent[1][k-1] )<<endl;
//	cout<<"<X1>-Xi1                 :  "<<"  i =1  "<<" k =  "<<k-1<<"  "<<(XMean[1] - Xcontent[1][k-1])<<endl;
//	cout<<"<Multiply                :  "<<"  i =1  "<<" k =  "<<k-1<<"  "<<(XMean[1]- Xcontent[1][k-1] )*( XMean[1] - Xcontent[1][k-1])<<endl;
	XMeanMinusXBinContSum[14]= XMeanMinusXBinContSum[14] + (XMean[1]- Xcontent[1][k-1] )*( XMean[1] - Xcontent[1][k-1])/NumOfSamples;
//	cout<<"XMeanMinusXBinContSum[14] :  "<<"  i =1"<<"   k =  "<<k-1<<"  "<<XMeanMinusXBinContSum[14]<<endl;
	
	XMeanMinusXBinContSum[15]= XMeanMinusXBinContSum[15] + (XMean[1]- Xcontent[1][k-1] )*( XMean[2] - Xcontent[2][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[16]= XMeanMinusXBinContSum[16] + (XMean[1]- Xcontent[1][k-1] )*( XMean[3] - Xcontent[3][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[17]= XMeanMinusXBinContSum[17] + (XMean[1]- Xcontent[1][k-1] )*( XMean[4] - Xcontent[4][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[18]= XMeanMinusXBinContSum[18] + (XMean[1]- Xcontent[1][k-1] )*( XMean[5] - Xcontent[5][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[19]= XMeanMinusXBinContSum[19] + (XMean[1]- Xcontent[1][k-1] )*( XMean[6] - Xcontent[6][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[20]= XMeanMinusXBinContSum[20] + (XMean[1]- Xcontent[1][k-1] )*( XMean[7] - Xcontent[7][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[21]= XMeanMinusXBinContSum[21] + (XMean[1]- Xcontent[1][k-1] )*( XMean[8] - Xcontent[8][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[22]= XMeanMinusXBinContSum[22] + (XMean[1]- Xcontent[1][k-1] )*( XMean[9] - Xcontent[9][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[23]= XMeanMinusXBinContSum[23] + (XMean[1]- Xcontent[1][k-1] )*( XMean[10] - Xcontent[10][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[24]= XMeanMinusXBinContSum[24] + (XMean[1]- Xcontent[1][k-1] )*( XMean[11] - Xcontent[11][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[25]= XMeanMinusXBinContSum[25] + (XMean[1]- Xcontent[1][k-1] )*( XMean[12] - Xcontent[12][k-1])/NumOfSamples;

	XMeanMinusXBinContSum[26]= XMeanMinusXBinContSum[26] + (XMean[2]- Xcontent[2][k-1] )*( XMean[0] - Xcontent[0][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[27]= XMeanMinusXBinContSum[27] + (XMean[2]- Xcontent[2][k-1] )*( XMean[1] - Xcontent[1][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[28]= XMeanMinusXBinContSum[28] + (XMean[2]- Xcontent[2][k-1] )*( XMean[2] - Xcontent[2][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[29]= XMeanMinusXBinContSum[29] + (XMean[2]- Xcontent[2][k-1] )*( XMean[3] - Xcontent[3][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[30]= XMeanMinusXBinContSum[30] + (XMean[2]- Xcontent[2][k-1] )*( XMean[4] - Xcontent[4][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[31]= XMeanMinusXBinContSum[31] + (XMean[2]- Xcontent[2][k-1] )*( XMean[5] - Xcontent[5][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[32]= XMeanMinusXBinContSum[32] + (XMean[2]- Xcontent[2][k-1] )*( XMean[6] - Xcontent[6][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[33]= XMeanMinusXBinContSum[33] + (XMean[2]- Xcontent[2][k-1] )*( XMean[7] - Xcontent[7][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[34]= XMeanMinusXBinContSum[34] + (XMean[2]- Xcontent[2][k-1] )*( XMean[8] - Xcontent[8][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[35]= XMeanMinusXBinContSum[35] + (XMean[2]- Xcontent[2][k-1] )*( XMean[9] - Xcontent[9][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[36]= XMeanMinusXBinContSum[36] + (XMean[2]- Xcontent[2][k-1] )*( XMean[10] - Xcontent[10][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[37]= XMeanMinusXBinContSum[37] + (XMean[2]- Xcontent[2][k-1] )*( XMean[11] - Xcontent[11][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[38]= XMeanMinusXBinContSum[38] + (XMean[2]- Xcontent[2][k-1] )*( XMean[12] - Xcontent[12][k-1])/NumOfSamples;

	XMeanMinusXBinContSum[39]= XMeanMinusXBinContSum[39] + (XMean[3]- Xcontent[3][k-1] )*( XMean[0] - Xcontent[0][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[40]= XMeanMinusXBinContSum[40] + (XMean[3]- Xcontent[3][k-1] )*( XMean[1] - Xcontent[1][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[41]= XMeanMinusXBinContSum[41] + (XMean[3]- Xcontent[3][k-1] )*( XMean[2] - Xcontent[2][k-1])/NumOfSamples;
	
//	cout<<"XMeanMinusXBin before    :  "<<"  i =3  "<<" k =  "<<k-1<<"  "<<XMeanMinusXBinContSum[42]<<endl;
//	cout<<"<X0>-Xi0                 :  "<<"  i =3  "<<" k =  "<<k-1<<"  "<<(XMean[3]- Xcontent[3][k-1] )<<endl;
//	cout<<"<X1>-Xi1                 :  "<<"  i =3  "<<" k =  "<<k-1<<"  "<<(XMean[3]- Xcontent[3][k-1])<<endl;
//	cout<<"<Multiply                :  "<<"  i =3  "<<" k =  "<<k-1<<"  "<<(XMean[3]- Xcontent[3][k-1] )*( XMean[3] - Xcontent[3][k-1])<<endl;
	XMeanMinusXBinContSum[42]= XMeanMinusXBinContSum[42] + (XMean[3]- Xcontent[3][k-1] )*( XMean[3] - Xcontent[3][k-1])/NumOfSamples;
//	cout<<"XMeanMinusXBinContSum[42] :  "<<"  i =3"<<"   k =  "<<k-1<<"  "<<XMeanMinusXBinContSum[42]<<endl;
	
	XMeanMinusXBinContSum[43]= XMeanMinusXBinContSum[43] + (XMean[3]- Xcontent[3][k-1] )*( XMean[4] - Xcontent[4][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[44]= XMeanMinusXBinContSum[44] + (XMean[3]- Xcontent[3][k-1] )*( XMean[5] - Xcontent[5][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[45]= XMeanMinusXBinContSum[45] + (XMean[3]- Xcontent[3][k-1] )*( XMean[6] - Xcontent[6][k-1])/NumOfSamples;

//	cout<<"XMeanMinusXBin before    :  "<<"  i =3  "<<" k =  "<<k-1<<"  "<<XMeanMinusXBinContSum[46]<<endl;
//	cout<<"<X0>-Xi0                 :  "<<"  i =3  "<<" k =  "<<k-1<<"  "<<(XMean[3]- Xcontent[3][k-1] )<<endl;
//	cout<<"<X1>-Xi1                 :  "<<"  i =3  "<<" k =  "<<k-1<<"  "<<(XMean[7]- Xcontent[7][k-1])<<endl;
//	cout<<"<Multiply                :  "<<"  i =3  "<<" k =  "<<k-1<<"  "<<(XMean[3]- Xcontent[3][k-1] )*( XMean[7] - Xcontent[7][k-1])<<endl;
	XMeanMinusXBinContSum[46]= XMeanMinusXBinContSum[46] + (XMean[3]- Xcontent[3][k-1] )*( XMean[7] - Xcontent[7][k-1])/NumOfSamples;
//	cout<<"XMeanMinusXBinContSum[46] :  "<<"  i =3"<<"   k =  "<<k-1<<"  "<<XMeanMinusXBinContSum[46]<<endl;
	
	XMeanMinusXBinContSum[47]= XMeanMinusXBinContSum[47] + (XMean[3]- Xcontent[3][k-1] )*( XMean[8] - Xcontent[8][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[48]= XMeanMinusXBinContSum[48] + (XMean[3]- Xcontent[3][k-1] )*( XMean[9] - Xcontent[9][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[49]= XMeanMinusXBinContSum[49] + (XMean[3]- Xcontent[3][k-1] )*( XMean[10] - Xcontent[10][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[50]= XMeanMinusXBinContSum[50] + (XMean[3]- Xcontent[3][k-1] )*( XMean[11] - Xcontent[11][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[51]= XMeanMinusXBinContSum[51] + (XMean[3]- Xcontent[3][k-1] )*( XMean[12] - Xcontent[12][k-1])/NumOfSamples;

	XMeanMinusXBinContSum[52]= XMeanMinusXBinContSum[52] + (XMean[4]- Xcontent[4][k-1] )*( XMean[0] - Xcontent[0][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[53]= XMeanMinusXBinContSum[53] + (XMean[4]- Xcontent[4][k-1] )*( XMean[1] - Xcontent[1][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[54]= XMeanMinusXBinContSum[54] + (XMean[4]- Xcontent[4][k-1] )*( XMean[2] - Xcontent[2][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[55]= XMeanMinusXBinContSum[55] + (XMean[4]- Xcontent[4][k-1] )*( XMean[3] - Xcontent[3][k-1])/NumOfSamples;

	cout<<"XMeanMinusXBin before    :  "<<"  i =4  "<<" k =  "<<k-1<<"  "<<XMeanMinusXBinContSum[56]<<endl;
	cout<<"<X0>-Xi0                 :  "<<"  i =4  "<<" k =  "<<k-1<<"  "<<(XMean[4]- Xcontent[4][k-1] )<<endl;
	cout<<"<X1>-Xi1                 :  "<<"  i =4  "<<" k =  "<<k-1<<"  "<<(XMean[4]- Xcontent[4][k-1])<<endl;
	cout<<"<Multiply                :  "<<"  i =4  "<<" k =  "<<k-1<<"  "<<(XMean[4]- Xcontent[4][k-1] )*( XMean[4] - Xcontent[4][k-1])<<endl;
	XMeanMinusXBinContSum[56]= XMeanMinusXBinContSum[56] + (XMean[4]- Xcontent[4][k-1] )*( XMean[4] - Xcontent[4][k-1])/NumOfSamples;
	cout<<"XMeanMinusXBinContSum[56] :  "<<"  i =4"<<"   k =  "<<k-1<<"  "<<XMeanMinusXBinContSum[56]<<endl;
	
	XMeanMinusXBinContSum[57]= XMeanMinusXBinContSum[57] + (XMean[4]- Xcontent[4][k-1] )*( XMean[5] - Xcontent[5][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[58]= XMeanMinusXBinContSum[58] + (XMean[4]- Xcontent[4][k-1] )*( XMean[6] - Xcontent[6][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[59]= XMeanMinusXBinContSum[59] + (XMean[4]- Xcontent[4][k-1] )*( XMean[7] - Xcontent[7][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[60]= XMeanMinusXBinContSum[60] + (XMean[4]- Xcontent[4][k-1] )*( XMean[8] - Xcontent[8][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[61]= XMeanMinusXBinContSum[61] + (XMean[4]- Xcontent[4][k-1] )*( XMean[9] - Xcontent[9][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[62]= XMeanMinusXBinContSum[62] + (XMean[4]- Xcontent[4][k-1] )*( XMean[10] - Xcontent[10][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[63]= XMeanMinusXBinContSum[63] + (XMean[4]- Xcontent[4][k-1] )*( XMean[11] - Xcontent[11][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[64]= XMeanMinusXBinContSum[64] + (XMean[4]- Xcontent[4][k-1] )*( XMean[12] - Xcontent[12][k-1])/NumOfSamples;

	XMeanMinusXBinContSum[65]= XMeanMinusXBinContSum[65] + (XMean[5]- Xcontent[5][k-1] )*( XMean[0] - Xcontent[0][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[66]= XMeanMinusXBinContSum[66] + (XMean[5]- Xcontent[5][k-1] )*( XMean[1] - Xcontent[1][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[67]= XMeanMinusXBinContSum[67] + (XMean[5]- Xcontent[5][k-1] )*( XMean[2] - Xcontent[2][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[68]= XMeanMinusXBinContSum[68] + (XMean[5]- Xcontent[5][k-1] )*( XMean[3] - Xcontent[3][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[69]= XMeanMinusXBinContSum[69] + (XMean[5]- Xcontent[5][k-1] )*( XMean[4] - Xcontent[4][k-1])/NumOfSamples;
	
//	cout<<"XMeanMinusXBin before    :  "<<"  i =5  "<<" k =  "<<k-1<<"  "<<XMeanMinusXBinContSum[70]<<endl;
//	cout<<"<X0>-Xi0                 :  "<<"  i =5  "<<" k =  "<<k-1<<"  "<<(XMean[5]- Xcontent[5][k-1] )<<endl;
//	cout<<"<X1>-Xi1                 :  "<<"  i =5  "<<" k =  "<<k-1<<"  "<<(XMean[5]- Xcontent[5][k-1])<<endl;
//	cout<<"<Multiply                :  "<<"  i =5  "<<" k =  "<<k-1<<"  "<<(XMean[5]- Xcontent[5][k-1] )*( XMean[5] - Xcontent[5][k-1])<<endl;
	XMeanMinusXBinContSum[70]= XMeanMinusXBinContSum[70] + (XMean[5]- Xcontent[5][k-1] )*( XMean[5] - Xcontent[5][k-1])/NumOfSamples;
//	cout<<"XMeanMinusXBinContSum[70] :  "<<"  i =5"<<"   k =  "<<k-1<<"  "<<XMeanMinusXBinContSum[70]<<endl;
	
	XMeanMinusXBinContSum[71]= XMeanMinusXBinContSum[71] + (XMean[5]- Xcontent[5][k-1] )*( XMean[6] - Xcontent[6][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[72]= XMeanMinusXBinContSum[72] + (XMean[5]- Xcontent[5][k-1] )*( XMean[7] - Xcontent[7][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[73]= XMeanMinusXBinContSum[73] + (XMean[5]- Xcontent[5][k-1] )*( XMean[8] - Xcontent[8][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[74]= XMeanMinusXBinContSum[74] + (XMean[5]- Xcontent[5][k-1] )*( XMean[9] - Xcontent[9][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[75]= XMeanMinusXBinContSum[75] + (XMean[5]- Xcontent[5][k-1] )*( XMean[10] - Xcontent[10][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[76]= XMeanMinusXBinContSum[76] + (XMean[5]- Xcontent[5][k-1] )*( XMean[11] - Xcontent[11][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[77]= XMeanMinusXBinContSum[77] + (XMean[5]- Xcontent[5][k-1] )*( XMean[12] - Xcontent[12][k-1])/NumOfSamples;

	XMeanMinusXBinContSum[78]= XMeanMinusXBinContSum[78] + (XMean[6]- Xcontent[6][k-1] )*( XMean[0] - Xcontent[0][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[79]= XMeanMinusXBinContSum[79] + (XMean[6]- Xcontent[6][k-1] )*( XMean[1] - Xcontent[1][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[80]= XMeanMinusXBinContSum[80] + (XMean[6]- Xcontent[6][k-1] )*( XMean[2] - Xcontent[2][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[81]= XMeanMinusXBinContSum[81] + (XMean[6]- Xcontent[6][k-1] )*( XMean[3] - Xcontent[3][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[82]= XMeanMinusXBinContSum[82] + (XMean[6]- Xcontent[6][k-1] )*( XMean[4] - Xcontent[4][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[83]= XMeanMinusXBinContSum[83] + (XMean[6]- Xcontent[6][k-1] )*( XMean[5] - Xcontent[5][k-1])/NumOfSamples;
	
//	cout<<"XMeanMinusXBin before    :  "<<"  i =6  "<<" k =  "<<k-1<<"  "<<XMeanMinusXBinContSum[84]<<endl;
//	cout<<"<X0>-Xi0                 :  "<<"  i =6  "<<" k =  "<<k-1<<"  "<<(XMean[6]- Xcontent[6][k-1] )<<endl;
//	cout<<"<X1>-Xi1                 :  "<<"  i =6  "<<" k =  "<<k-1<<"  "<<(XMean[6]- Xcontent[6][k-1])<<endl;
//	cout<<"<Multiply                :  "<<"  i =6  "<<" k =  "<<k-1<<"  "<<(XMean[6]- Xcontent[6][k-1] )*( XMean[6] - Xcontent[6][k-1])<<endl;
	XMeanMinusXBinContSum[84]= XMeanMinusXBinContSum[84] + (XMean[6]- Xcontent[6][k-1] )*( XMean[6] - Xcontent[6][k-1])/NumOfSamples;
//	cout<<"XMeanMinusXBinContSum[84] :  "<<"  i =6"<<"   k =  "<<k-1<<"  "<<XMeanMinusXBinContSum[84]<<endl;
	
	XMeanMinusXBinContSum[85]= XMeanMinusXBinContSum[85] + (XMean[6]- Xcontent[6][k-1] )*( XMean[7] - Xcontent[7][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[86]= XMeanMinusXBinContSum[86] + (XMean[6]- Xcontent[6][k-1] )*( XMean[8] - Xcontent[8][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[87]= XMeanMinusXBinContSum[87] + (XMean[6]- Xcontent[6][k-1] )*( XMean[9] - Xcontent[9][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[88]= XMeanMinusXBinContSum[88] + (XMean[6]- Xcontent[6][k-1] )*( XMean[10] - Xcontent[10][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[89]= XMeanMinusXBinContSum[89] + (XMean[6]- Xcontent[6][k-1] )*( XMean[11] - Xcontent[11][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[90]= XMeanMinusXBinContSum[90] + (XMean[6]- Xcontent[6][k-1] )*( XMean[12] - Xcontent[12][k-1])/NumOfSamples;

	XMeanMinusXBinContSum[91]= XMeanMinusXBinContSum[91] + (XMean[7]- Xcontent[7][k-1] )*( XMean[0] - Xcontent[0][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[92]= XMeanMinusXBinContSum[92] + (XMean[7]- Xcontent[7][k-1] )*( XMean[1] - Xcontent[1][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[93]= XMeanMinusXBinContSum[93] + (XMean[7]- Xcontent[7][k-1] )*( XMean[2] - Xcontent[2][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[94]= XMeanMinusXBinContSum[94] + (XMean[7]- Xcontent[7][k-1] )*( XMean[3] - Xcontent[3][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[95]= XMeanMinusXBinContSum[95] + (XMean[7]- Xcontent[7][k-1] )*( XMean[4] - Xcontent[4][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[96]= XMeanMinusXBinContSum[96] + (XMean[7]- Xcontent[7][k-1] )*( XMean[5] - Xcontent[5][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[97]= XMeanMinusXBinContSum[97] + (XMean[7]- Xcontent[7][k-1] )*( XMean[6] - Xcontent[6][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[98]= XMeanMinusXBinContSum[98] + (XMean[7]- Xcontent[7][k-1] )*( XMean[7] - Xcontent[7][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[99]= XMeanMinusXBinContSum[99] + (XMean[7]- Xcontent[7][k-1] )*( XMean[8] - Xcontent[8][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[100]= XMeanMinusXBinContSum[100] + (XMean[7]- Xcontent[7][k-1] )*( XMean[9] - Xcontent[9][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[101]= XMeanMinusXBinContSum[101] + (XMean[7]- Xcontent[7][k-1] )*( XMean[10] - Xcontent[10][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[102]= XMeanMinusXBinContSum[102] + (XMean[7]- Xcontent[7][k-1] )*( XMean[11] - Xcontent[11][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[103]= XMeanMinusXBinContSum[103] + (XMean[7]- Xcontent[7][k-1] )*( XMean[12] - Xcontent[12][k-1])/NumOfSamples;

	XMeanMinusXBinContSum[104]= XMeanMinusXBinContSum[104] + (XMean[8]- Xcontent[8][k-1] )*( XMean[0] - Xcontent[0][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[105]= XMeanMinusXBinContSum[105] + (XMean[8]- Xcontent[8][k-1] )*( XMean[1] - Xcontent[1][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[106]= XMeanMinusXBinContSum[106] + (XMean[8]- Xcontent[8][k-1] )*( XMean[2] - Xcontent[2][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[107]= XMeanMinusXBinContSum[107] + (XMean[8]- Xcontent[8][k-1] )*( XMean[3] - Xcontent[3][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[108]= XMeanMinusXBinContSum[108] + (XMean[8]- Xcontent[8][k-1] )*( XMean[4] - Xcontent[4][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[109]= XMeanMinusXBinContSum[109] + (XMean[8]- Xcontent[8][k-1] )*( XMean[5] - Xcontent[5][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[110]= XMeanMinusXBinContSum[110] + (XMean[8]- Xcontent[8][k-1] )*( XMean[6] - Xcontent[6][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[111]= XMeanMinusXBinContSum[111] + (XMean[8]- Xcontent[8][k-1] )*( XMean[7] - Xcontent[7][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[112]= XMeanMinusXBinContSum[112] + (XMean[8]- Xcontent[8][k-1] )*( XMean[8] - Xcontent[8][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[113]= XMeanMinusXBinContSum[113] + (XMean[8]- Xcontent[8][k-1] )*( XMean[9] - Xcontent[9][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[114]= XMeanMinusXBinContSum[114] + (XMean[8]- Xcontent[8][k-1] )*( XMean[10] - Xcontent[10][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[115]= XMeanMinusXBinContSum[115] + (XMean[8]- Xcontent[8][k-1] )*( XMean[11] - Xcontent[11][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[116]= XMeanMinusXBinContSum[116] + (XMean[8]- Xcontent[8][k-1] )*( XMean[12] - Xcontent[12][k-1])/NumOfSamples;

	XMeanMinusXBinContSum[117]= XMeanMinusXBinContSum[117] + (XMean[9]- Xcontent[9][k-1] )*( XMean[0] - Xcontent[0][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[118]= XMeanMinusXBinContSum[118] + (XMean[9]- Xcontent[9][k-1] )*( XMean[1] - Xcontent[1][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[119]= XMeanMinusXBinContSum[119] + (XMean[9]- Xcontent[9][k-1] )*( XMean[2] - Xcontent[2][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[120]= XMeanMinusXBinContSum[120] + (XMean[9]- Xcontent[9][k-1] )*( XMean[3] - Xcontent[3][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[121]= XMeanMinusXBinContSum[121] + (XMean[9]- Xcontent[9][k-1] )*( XMean[4] - Xcontent[4][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[122]= XMeanMinusXBinContSum[122] + (XMean[9]- Xcontent[9][k-1] )*( XMean[5] - Xcontent[5][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[123]= XMeanMinusXBinContSum[123] + (XMean[9]- Xcontent[9][k-1] )*( XMean[6] - Xcontent[6][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[124]= XMeanMinusXBinContSum[124] + (XMean[9]- Xcontent[9][k-1] )*( XMean[7] - Xcontent[7][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[125]= XMeanMinusXBinContSum[125] + (XMean[9]- Xcontent[9][k-1] )*( XMean[8] - Xcontent[8][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[126]= XMeanMinusXBinContSum[126] + (XMean[9]- Xcontent[9][k-1] )*( XMean[9] - Xcontent[9][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[127]= XMeanMinusXBinContSum[127] + (XMean[9]- Xcontent[9][k-1] )*( XMean[10] - Xcontent[10][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[128]= XMeanMinusXBinContSum[128] + (XMean[9]- Xcontent[9][k-1] )*( XMean[11] - Xcontent[11][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[129]= XMeanMinusXBinContSum[129] + (XMean[9]- Xcontent[9][k-1] )*( XMean[12] - Xcontent[12][k-1])/NumOfSamples;

	XMeanMinusXBinContSum[130]= XMeanMinusXBinContSum[130] + (XMean[10]- Xcontent[10][k-1] )*( XMean[0] - Xcontent[0][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[131]= XMeanMinusXBinContSum[131] + (XMean[10]- Xcontent[10][k-1] )*( XMean[1] - Xcontent[1][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[132]= XMeanMinusXBinContSum[132] + (XMean[10]- Xcontent[10][k-1] )*( XMean[2] - Xcontent[2][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[133]= XMeanMinusXBinContSum[133] + (XMean[10]- Xcontent[10][k-1] )*( XMean[3] - Xcontent[3][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[134]= XMeanMinusXBinContSum[134] + (XMean[10]- Xcontent[10][k-1] )*( XMean[4] - Xcontent[4][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[135]= XMeanMinusXBinContSum[135] + (XMean[10]- Xcontent[10][k-1] )*( XMean[5] - Xcontent[5][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[136]= XMeanMinusXBinContSum[136] + (XMean[10]- Xcontent[10][k-1] )*( XMean[6] - Xcontent[6][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[137]= XMeanMinusXBinContSum[137] + (XMean[10]- Xcontent[10][k-1] )*( XMean[7] - Xcontent[7][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[138]= XMeanMinusXBinContSum[138] + (XMean[10]- Xcontent[10][k-1] )*( XMean[8] - Xcontent[8][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[139]= XMeanMinusXBinContSum[139] + (XMean[10]- Xcontent[10][k-1] )*( XMean[9] - Xcontent[9][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[140]= XMeanMinusXBinContSum[140] + (XMean[10]- Xcontent[10][k-1] )*( XMean[10] - Xcontent[10][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[141]= XMeanMinusXBinContSum[141] + (XMean[10]- Xcontent[10][k-1] )*( XMean[11] - Xcontent[11][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[142]= XMeanMinusXBinContSum[142] + (XMean[10]- Xcontent[10][k-1] )*( XMean[12] - Xcontent[12][k-1])/NumOfSamples;

	XMeanMinusXBinContSum[143]= XMeanMinusXBinContSum[143] + (XMean[11]- Xcontent[11][k-1] )*( XMean[0] - Xcontent[0][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[144]= XMeanMinusXBinContSum[144] + (XMean[11]- Xcontent[11][k-1] )*( XMean[1] - Xcontent[1][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[145]= XMeanMinusXBinContSum[145] + (XMean[11]- Xcontent[11][k-1] )*( XMean[2] - Xcontent[2][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[146]= XMeanMinusXBinContSum[146] + (XMean[11]- Xcontent[11][k-1] )*( XMean[3] - Xcontent[3][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[147]= XMeanMinusXBinContSum[147] + (XMean[11]- Xcontent[11][k-1] )*( XMean[4] - Xcontent[4][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[148]= XMeanMinusXBinContSum[148] + (XMean[11]- Xcontent[11][k-1] )*( XMean[5] - Xcontent[5][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[149]= XMeanMinusXBinContSum[149] + (XMean[11]- Xcontent[11][k-1] )*( XMean[6] - Xcontent[6][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[150]= XMeanMinusXBinContSum[150] + (XMean[11]- Xcontent[11][k-1] )*( XMean[7] - Xcontent[7][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[151]= XMeanMinusXBinContSum[151] + (XMean[11]- Xcontent[11][k-1] )*( XMean[8] - Xcontent[8][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[152]= XMeanMinusXBinContSum[152] + (XMean[11]- Xcontent[11][k-1] )*( XMean[9] - Xcontent[9][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[153]= XMeanMinusXBinContSum[153] + (XMean[11]- Xcontent[11][k-1] )*( XMean[10] - Xcontent[10][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[154]= XMeanMinusXBinContSum[154] + (XMean[11]- Xcontent[11][k-1] )*( XMean[11] - Xcontent[11][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[155]= XMeanMinusXBinContSum[155] + (XMean[11]- Xcontent[11][k-1] )*( XMean[12] - Xcontent[12][k-1])/NumOfSamples;

	XMeanMinusXBinContSum[156]= XMeanMinusXBinContSum[156] + (XMean[12]- Xcontent[12][k-1] )*( XMean[0] - Xcontent[0][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[157]= XMeanMinusXBinContSum[157] + (XMean[12]- Xcontent[12][k-1] )*( XMean[1] - Xcontent[1][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[158]= XMeanMinusXBinContSum[158] + (XMean[12]- Xcontent[12][k-1] )*( XMean[2] - Xcontent[2][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[159]= XMeanMinusXBinContSum[159] + (XMean[12]- Xcontent[12][k-1] )*( XMean[3] - Xcontent[3][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[160]= XMeanMinusXBinContSum[160] + (XMean[12]- Xcontent[12][k-1] )*( XMean[4] - Xcontent[4][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[161]= XMeanMinusXBinContSum[161] + (XMean[12]- Xcontent[12][k-1] )*( XMean[5] - Xcontent[5][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[162]= XMeanMinusXBinContSum[162] + (XMean[12]- Xcontent[12][k-1] )*( XMean[6] - Xcontent[6][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[163]= XMeanMinusXBinContSum[163] + (XMean[12]- Xcontent[12][k-1] )*( XMean[7] - Xcontent[7][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[164]= XMeanMinusXBinContSum[164] + (XMean[12]- Xcontent[12][k-1] )*( XMean[8] - Xcontent[8][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[165]= XMeanMinusXBinContSum[165] + (XMean[12]- Xcontent[12][k-1] )*( XMean[9] - Xcontent[9][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[166]= XMeanMinusXBinContSum[166] + (XMean[12]- Xcontent[12][k-1] )*( XMean[10] - Xcontent[10][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[167]= XMeanMinusXBinContSum[167] + (XMean[12]- Xcontent[12][k-1] )*( XMean[11] - Xcontent[11][k-1])/NumOfSamples;
	
	XMeanMinusXBinContSum[168]= XMeanMinusXBinContSum[168] + (XMean[12]- Xcontent[12][k-1] )*( XMean[12] - Xcontent[12][k-1])/NumOfSamples;
	//cout<<"XMeanMinusXBinContSum[168] :  "<<"  i =168"<<"   k =  "<<k-1<<"  "<<XMeanMinusXBinContSum[168]<<endl;

	
  }


	 XMeanMinusXBinContSumTwo[1][1]= XMeanMinusXBinContSum[0];
	  cout<<"XMeanMinusXBinContSumTwo[1][1]"<<XMeanMinusXBinContSumTwo[1][1]<<endl;
	 XMeanMinusXBinContSumTwo[1][2]= XMeanMinusXBinContSum[1];
	  cout<<"XMeanMinusXBinContSumTwo[1][2]"<<XMeanMinusXBinContSumTwo[1][2]<<endl;
	 XMeanMinusXBinContSumTwo[1][3]= XMeanMinusXBinContSum[2];
	 XMeanMinusXBinContSumTwo[1][4]= XMeanMinusXBinContSum[3];
	 XMeanMinusXBinContSumTwo[1][5]= XMeanMinusXBinContSum[4];
	 XMeanMinusXBinContSumTwo[1][6]= XMeanMinusXBinContSum[5];
	 XMeanMinusXBinContSumTwo[1][7]= XMeanMinusXBinContSum[6];
	 XMeanMinusXBinContSumTwo[1][8]= XMeanMinusXBinContSum[7];
	 XMeanMinusXBinContSumTwo[1][9]= XMeanMinusXBinContSum[8];
	 XMeanMinusXBinContSumTwo[1][10]= XMeanMinusXBinContSum[9];
	 XMeanMinusXBinContSumTwo[1][11]= XMeanMinusXBinContSum[10];
	 XMeanMinusXBinContSumTwo[1][12]= XMeanMinusXBinContSum[11];
	 XMeanMinusXBinContSumTwo[1][13]= XMeanMinusXBinContSum[12];

	 XMeanMinusXBinContSumTwo[2][1]= XMeanMinusXBinContSum[13];
	 XMeanMinusXBinContSumTwo[2][2]= XMeanMinusXBinContSum[14];
	 XMeanMinusXBinContSumTwo[2][3]= XMeanMinusXBinContSum[15];
	 XMeanMinusXBinContSumTwo[2][4]= XMeanMinusXBinContSum[16];
	 XMeanMinusXBinContSumTwo[2][5]= XMeanMinusXBinContSum[17];
	 XMeanMinusXBinContSumTwo[2][6]= XMeanMinusXBinContSum[18];
	 XMeanMinusXBinContSumTwo[2][7]= XMeanMinusXBinContSum[19];
	 XMeanMinusXBinContSumTwo[2][8]= XMeanMinusXBinContSum[20];
	 XMeanMinusXBinContSumTwo[2][9]= XMeanMinusXBinContSum[21];
	 XMeanMinusXBinContSumTwo[2][10]= XMeanMinusXBinContSum[22];
	 XMeanMinusXBinContSumTwo[2][11]= XMeanMinusXBinContSum[23];
	 XMeanMinusXBinContSumTwo[2][12]= XMeanMinusXBinContSum[24];
	 XMeanMinusXBinContSumTwo[2][13]= XMeanMinusXBinContSum[25];

	 XMeanMinusXBinContSumTwo[3][1]= XMeanMinusXBinContSum[26];
	 XMeanMinusXBinContSumTwo[3][2]= XMeanMinusXBinContSum[27];
	 XMeanMinusXBinContSumTwo[3][3]= XMeanMinusXBinContSum[28];
	 XMeanMinusXBinContSumTwo[3][4]= XMeanMinusXBinContSum[29];
	 XMeanMinusXBinContSumTwo[3][5]= XMeanMinusXBinContSum[30];
	 XMeanMinusXBinContSumTwo[3][6]= XMeanMinusXBinContSum[31];
	 XMeanMinusXBinContSumTwo[3][7]= XMeanMinusXBinContSum[32];
	 XMeanMinusXBinContSumTwo[3][8]= XMeanMinusXBinContSum[33];
	 XMeanMinusXBinContSumTwo[3][9]= XMeanMinusXBinContSum[34];
	 XMeanMinusXBinContSumTwo[3][10]= XMeanMinusXBinContSum[35];
	 XMeanMinusXBinContSumTwo[3][11]= XMeanMinusXBinContSum[36];
	 XMeanMinusXBinContSumTwo[3][12]= XMeanMinusXBinContSum[37];
	 XMeanMinusXBinContSumTwo[3][13]= XMeanMinusXBinContSum[38];

	 XMeanMinusXBinContSumTwo[4][1]= XMeanMinusXBinContSum[39];
	 XMeanMinusXBinContSumTwo[4][2]= XMeanMinusXBinContSum[40];
	 XMeanMinusXBinContSumTwo[4][3]= XMeanMinusXBinContSum[41];
	 XMeanMinusXBinContSumTwo[4][4]= XMeanMinusXBinContSum[42];
	 XMeanMinusXBinContSumTwo[4][5]= XMeanMinusXBinContSum[43];
	 XMeanMinusXBinContSumTwo[4][6]= XMeanMinusXBinContSum[44];
	 XMeanMinusXBinContSumTwo[4][7]= XMeanMinusXBinContSum[45];
	 XMeanMinusXBinContSumTwo[4][8]= XMeanMinusXBinContSum[46];
	 XMeanMinusXBinContSumTwo[4][9]= XMeanMinusXBinContSum[47];
	 XMeanMinusXBinContSumTwo[4][10]= XMeanMinusXBinContSum[48];
	 XMeanMinusXBinContSumTwo[4][11]= XMeanMinusXBinContSum[49];
	 XMeanMinusXBinContSumTwo[4][12]= XMeanMinusXBinContSum[50];
	 XMeanMinusXBinContSumTwo[4][13]= XMeanMinusXBinContSum[51];

	 XMeanMinusXBinContSumTwo[5][1]= XMeanMinusXBinContSum[52];
	 XMeanMinusXBinContSumTwo[5][2]= XMeanMinusXBinContSum[53];
	 XMeanMinusXBinContSumTwo[5][3]= XMeanMinusXBinContSum[54];
	 XMeanMinusXBinContSumTwo[5][4]= XMeanMinusXBinContSum[55];
	 XMeanMinusXBinContSumTwo[5][5]= XMeanMinusXBinContSum[56];
	 XMeanMinusXBinContSumTwo[5][6]= XMeanMinusXBinContSum[57];
	 XMeanMinusXBinContSumTwo[5][7]= XMeanMinusXBinContSum[58];
	 XMeanMinusXBinContSumTwo[5][8]= XMeanMinusXBinContSum[59];
	 XMeanMinusXBinContSumTwo[5][9]= XMeanMinusXBinContSum[60];
	 XMeanMinusXBinContSumTwo[5][10]= XMeanMinusXBinContSum[61];
	 XMeanMinusXBinContSumTwo[5][11]= XMeanMinusXBinContSum[62];
	 XMeanMinusXBinContSumTwo[5][12]= XMeanMinusXBinContSum[63];
	 XMeanMinusXBinContSumTwo[5][13]= XMeanMinusXBinContSum[64];

	 XMeanMinusXBinContSumTwo[6][1]= XMeanMinusXBinContSum[65];
	 XMeanMinusXBinContSumTwo[6][2]= XMeanMinusXBinContSum[66];
	 XMeanMinusXBinContSumTwo[6][3]= XMeanMinusXBinContSum[67];
	 XMeanMinusXBinContSumTwo[6][4]= XMeanMinusXBinContSum[68];
	 XMeanMinusXBinContSumTwo[6][5]= XMeanMinusXBinContSum[69];
	 XMeanMinusXBinContSumTwo[6][6]= XMeanMinusXBinContSum[70];
	 XMeanMinusXBinContSumTwo[6][7]= XMeanMinusXBinContSum[71];
	 XMeanMinusXBinContSumTwo[6][8]= XMeanMinusXBinContSum[72];
	 XMeanMinusXBinContSumTwo[6][9]= XMeanMinusXBinContSum[73];
	 XMeanMinusXBinContSumTwo[6][10]= XMeanMinusXBinContSum[74];
	 XMeanMinusXBinContSumTwo[6][11]= XMeanMinusXBinContSum[75];
	 XMeanMinusXBinContSumTwo[6][12]= XMeanMinusXBinContSum[76];
	 XMeanMinusXBinContSumTwo[6][13]= XMeanMinusXBinContSum[77];

	 XMeanMinusXBinContSumTwo[7][1]= XMeanMinusXBinContSum[78];
	 XMeanMinusXBinContSumTwo[7][2]= XMeanMinusXBinContSum[79];
	 XMeanMinusXBinContSumTwo[7][3]= XMeanMinusXBinContSum[80];
	 XMeanMinusXBinContSumTwo[7][4]= XMeanMinusXBinContSum[81];
	 XMeanMinusXBinContSumTwo[7][5]= XMeanMinusXBinContSum[82];
	 XMeanMinusXBinContSumTwo[7][6]= XMeanMinusXBinContSum[83];
	 XMeanMinusXBinContSumTwo[7][7]= XMeanMinusXBinContSum[84];
	 XMeanMinusXBinContSumTwo[7][8]= XMeanMinusXBinContSum[85];
	 XMeanMinusXBinContSumTwo[7][9]= XMeanMinusXBinContSum[86];
	 XMeanMinusXBinContSumTwo[7][10]= XMeanMinusXBinContSum[87];
	 XMeanMinusXBinContSumTwo[7][11]= XMeanMinusXBinContSum[88];
	 XMeanMinusXBinContSumTwo[7][12]= XMeanMinusXBinContSum[89];
	 XMeanMinusXBinContSumTwo[7][13]= XMeanMinusXBinContSum[90];

	 XMeanMinusXBinContSumTwo[8][1]= XMeanMinusXBinContSum[91];
	 XMeanMinusXBinContSumTwo[8][2]= XMeanMinusXBinContSum[92];
	 XMeanMinusXBinContSumTwo[8][3]= XMeanMinusXBinContSum[93];
	 XMeanMinusXBinContSumTwo[8][4]= XMeanMinusXBinContSum[94];
	 XMeanMinusXBinContSumTwo[8][5]= XMeanMinusXBinContSum[95];
	 XMeanMinusXBinContSumTwo[8][6]= XMeanMinusXBinContSum[96];
	 XMeanMinusXBinContSumTwo[8][7]= XMeanMinusXBinContSum[97];
	 XMeanMinusXBinContSumTwo[8][8]= XMeanMinusXBinContSum[98];
	 XMeanMinusXBinContSumTwo[8][9]= XMeanMinusXBinContSum[99];
	 XMeanMinusXBinContSumTwo[8][10]= XMeanMinusXBinContSum[100];
	 XMeanMinusXBinContSumTwo[8][11]= XMeanMinusXBinContSum[101];
	 XMeanMinusXBinContSumTwo[8][12]= XMeanMinusXBinContSum[102];
	 XMeanMinusXBinContSumTwo[8][13]= XMeanMinusXBinContSum[103];

	 XMeanMinusXBinContSumTwo[9][1]= XMeanMinusXBinContSum[104];
	 XMeanMinusXBinContSumTwo[9][2]= XMeanMinusXBinContSum[105];
	 XMeanMinusXBinContSumTwo[9][3]= XMeanMinusXBinContSum[106];
	 XMeanMinusXBinContSumTwo[9][4]= XMeanMinusXBinContSum[107];
	 XMeanMinusXBinContSumTwo[9][5]= XMeanMinusXBinContSum[108];
	 XMeanMinusXBinContSumTwo[9][6]= XMeanMinusXBinContSum[109];
	 XMeanMinusXBinContSumTwo[9][7]= XMeanMinusXBinContSum[110];
	 XMeanMinusXBinContSumTwo[9][8]= XMeanMinusXBinContSum[111];
	 XMeanMinusXBinContSumTwo[9][9]= XMeanMinusXBinContSum[112];
	 XMeanMinusXBinContSumTwo[9][10]= XMeanMinusXBinContSum[113];
	 XMeanMinusXBinContSumTwo[9][11]= XMeanMinusXBinContSum[114];
	 XMeanMinusXBinContSumTwo[9][12]= XMeanMinusXBinContSum[115];
	 XMeanMinusXBinContSumTwo[9][13]= XMeanMinusXBinContSum[116];

	 XMeanMinusXBinContSumTwo[10][1]= XMeanMinusXBinContSum[117];
	 XMeanMinusXBinContSumTwo[10][2]= XMeanMinusXBinContSum[118];
	 XMeanMinusXBinContSumTwo[10][3]= XMeanMinusXBinContSum[119];
	 XMeanMinusXBinContSumTwo[10][4]= XMeanMinusXBinContSum[120];
	 XMeanMinusXBinContSumTwo[10][5]= XMeanMinusXBinContSum[121];
	 XMeanMinusXBinContSumTwo[10][6]= XMeanMinusXBinContSum[122];
	 XMeanMinusXBinContSumTwo[10][7]= XMeanMinusXBinContSum[123];
	 XMeanMinusXBinContSumTwo[10][8]= XMeanMinusXBinContSum[124];
	 XMeanMinusXBinContSumTwo[10][9]= XMeanMinusXBinContSum[125];
	 XMeanMinusXBinContSumTwo[10][10]= XMeanMinusXBinContSum[126];
	 XMeanMinusXBinContSumTwo[10][11]= XMeanMinusXBinContSum[127];
	 XMeanMinusXBinContSumTwo[10][12]= XMeanMinusXBinContSum[128];
	 XMeanMinusXBinContSumTwo[10][13]= XMeanMinusXBinContSum[129];

	 XMeanMinusXBinContSumTwo[11][1]= XMeanMinusXBinContSum[130];
	 XMeanMinusXBinContSumTwo[11][2]= XMeanMinusXBinContSum[131];
	 XMeanMinusXBinContSumTwo[11][3]= XMeanMinusXBinContSum[132];
	 XMeanMinusXBinContSumTwo[11][4]= XMeanMinusXBinContSum[133];
	 XMeanMinusXBinContSumTwo[11][5]= XMeanMinusXBinContSum[134];
	 XMeanMinusXBinContSumTwo[11][6]= XMeanMinusXBinContSum[135];
	 XMeanMinusXBinContSumTwo[11][7]= XMeanMinusXBinContSum[136];
	 XMeanMinusXBinContSumTwo[11][8]= XMeanMinusXBinContSum[137];
	 XMeanMinusXBinContSumTwo[11][9]= XMeanMinusXBinContSum[138];
	 XMeanMinusXBinContSumTwo[11][10]= XMeanMinusXBinContSum[139];
	 XMeanMinusXBinContSumTwo[11][11]= XMeanMinusXBinContSum[140];
	 XMeanMinusXBinContSumTwo[11][12]= XMeanMinusXBinContSum[141];
	 XMeanMinusXBinContSumTwo[11][13]= XMeanMinusXBinContSum[142];

	 XMeanMinusXBinContSumTwo[12][1]= XMeanMinusXBinContSum[143];
	 XMeanMinusXBinContSumTwo[12][2]= XMeanMinusXBinContSum[144];
	 XMeanMinusXBinContSumTwo[12][3]= XMeanMinusXBinContSum[145];
	 XMeanMinusXBinContSumTwo[12][4]= XMeanMinusXBinContSum[146];
	 XMeanMinusXBinContSumTwo[12][5]= XMeanMinusXBinContSum[147];
	 XMeanMinusXBinContSumTwo[12][6]= XMeanMinusXBinContSum[148];
	 XMeanMinusXBinContSumTwo[12][7]= XMeanMinusXBinContSum[149];
	 XMeanMinusXBinContSumTwo[12][8]= XMeanMinusXBinContSum[150];
	 XMeanMinusXBinContSumTwo[12][9]= XMeanMinusXBinContSum[151];
	 XMeanMinusXBinContSumTwo[12][10]= XMeanMinusXBinContSum[152];
	 XMeanMinusXBinContSumTwo[12][11]= XMeanMinusXBinContSum[153];
	 XMeanMinusXBinContSumTwo[12][12]= XMeanMinusXBinContSum[154];
	 XMeanMinusXBinContSumTwo[12][13]= XMeanMinusXBinContSum[155];

	 XMeanMinusXBinContSumTwo[13][1]= XMeanMinusXBinContSum[156];
	 XMeanMinusXBinContSumTwo[13][2]= XMeanMinusXBinContSum[157];
	 XMeanMinusXBinContSumTwo[13][3]= XMeanMinusXBinContSum[158];
	 XMeanMinusXBinContSumTwo[13][4]= XMeanMinusXBinContSum[159];
	 XMeanMinusXBinContSumTwo[13][5]= XMeanMinusXBinContSum[160];
	 XMeanMinusXBinContSumTwo[13][6]= XMeanMinusXBinContSum[161];
	 XMeanMinusXBinContSumTwo[13][7]= XMeanMinusXBinContSum[162];
	 XMeanMinusXBinContSumTwo[13][8]= XMeanMinusXBinContSum[163];
	 XMeanMinusXBinContSumTwo[13][9]= XMeanMinusXBinContSum[164];
	 XMeanMinusXBinContSumTwo[13][10]= XMeanMinusXBinContSum[165];
	 XMeanMinusXBinContSumTwo[13][11]= XMeanMinusXBinContSum[166];
	 XMeanMinusXBinContSumTwo[13][12]= XMeanMinusXBinContSum[167];
	 XMeanMinusXBinContSumTwo[13][13]= XMeanMinusXBinContSum[168];
	  cout<<"XMeanMinusXBinContSumTwo[13][13]"<<XMeanMinusXBinContSumTwo[13][13]<<endl;

   for( int i(1); i<= SVD_Post.data->GetNbinsX(); i++)
   {
     for( int j(1); j<= SVD_Post.data->GetNbinsX(); j++)
     {
       if (i==j)
	 SVD_Post.RecoStatisticCovMat->SetBinContent(i,i, h1_Data_SigYild->GetBinError(i)*h1_Data_SigYild->GetBinError(i)   );
       else
	 SVD_Post.RecoStatisticCovMat->SetBinContent(i,j, 0.,0. );
     }
   }

  for( int i(1); i<= SVD_Post.data->GetNbinsX(); i++)
  {
    for( int j(1); j<= SVD_Post.data->GetNbinsX(); j++)
        {
	  //SVD_Post.BstatCov->SetBinContent(i,j, fabs(XMeanMinusXBinContSumTwo[i][j])  );
	  
	  SVD_Post.BstatCov->SetBinContent(i,j, XMeanMinusXBinContSumTwo[i][j]  );
	  
	  
	 // h2_RecoScaleCovMat->SetBinContent(i,j, XMeanMinusXBinContSumTwo[i][j]  );
	  //h2_RecoEffiCovMat->SetBinContent(i,j, XMeanMinusXBinContSumTwo[i][j]  );
	  //h2_RecoSmearCovMat->SetBinContent(i,j, XMeanMinusXBinContSumTwo[i][j]  );
	  //h2_RecoRecoilCovMat->SetBinContent(i,j, XMeanMinusXBinContSumTwo[i][j]  );
	  //if (i<9 || j<9)
	  //{
	  //  h2_RecoQCDRatioCovMat->SetBinContent(i,j, 0.);
	  //}else
	  //{
	  //  h2_RecoQCDRatioCovMat->SetBinContent(i,j, XMeanMinusXBinContSumTwo[i][j]  );
	  //}
	 //h2_RecoFSRCovMat->SetBinContent(i,j, XMeanMinusXBinContSumTwo[i][j]  );
	  
	  
	  cout<<"XMeanMinusXBinContSumTwo[i][j]:   "<<" i = "<<i<<" j = "<<j<<"  "<<XMeanMinusXBinContSumTwo[i][j]<<endl;
	  //cout<<"XMeanMinusXBinContSumTwo[i][j]:   "<<" i = "<<i<<" j = "<<j<<"  "<<fabs(XMeanMinusXBinContSumTwo[i][j])<<endl;
	}
  }

  
  // h2_RecoScaleCovMat->Write();
   //h2_RecoEffiCovMat->Write();
   //h2_RecoSmearCovMat->Write();
   //h2_RecoRecoilCovMat->Write();
   //h2_RecoQCDRatioCovMat->Write();
   //h2_RecoFSRCovMat->Write();


  for( int i(1); i<= SVD_Post.data->GetNbinsX(); i++)
  {
    for( int j(1); j<= SVD_Post.data->GetNbinsX(); j++)
        {
	  SVD_Post.BstatCorr->SetBinContent(i,j, fabs(XMeanMinusXBinContSumTwo[i][j])/sqrt(fabs(XMeanMinusXBinContSumTwo[i][i])*fabs(XMeanMinusXBinContSumTwo[j][j]))  );
	  //SVD_Post.BstatCorr->SetBinContent(i,j, XMeanMinusXBinContSumTwo[i][j]/sqrt((XMeanMinusXBinContSumTwo[i][i])*(XMeanMinusXBinContSumTwo[j][j]))  );
	  //SVD_Post.BstatCorr->SetBinContent(i,j, SVD_Post.BstatCov->GetBinContent(i)/sqrt()  );
	  
	}
  }



  for( int i(1); i<= SVD_Post.data->GetNbinsX(); i++)
  {

    //cout<<"XMeanMinusXBinContSumTwo[i][i]  : "<<i<<""<<i<<"    "<<XMeanMinusXBinContSumTwo[i][i]<<endl;
    cout<<"Recon stage CovMatrix_i_i         : "<<i<<""<<i<<"    "<<XMeanMinusXBinContSumTwo[i][i]<<endl;
    cout<<"Square root of CovMatrix_i_i      :          "<<TMath::Sqrt(XMeanMinusXBinContSumTwo[i][i])<<endl;
   // cout<<"Syst presentage %               : "<<i<<"         "<<(XMeanMinusXBinContSumTwo[i][i])/XMean[i-1]*100<<endl;
    cout<<"Recon stage Systematics%          : "<<"              "<<TMath::Sqrt(XMeanMinusXBinContSumTwo[i][i])/h1_Data_SigYild->GetBinContent(i)*100<<"  % "<<endl;
	  
  }
  
  SVD_Post.RecoEffiCovMat =(TH2D*)f_RecoEffiCovMat->Get("h2_RecoEffiCovMat")->Clone();
  SVD_Post.RecoSmearCovMat =(TH2D*)f_RecoSmearCovMat->Get("h2_RecoSmearCovMat")->Clone();
  SVD_Post.RecoRecoilCovMat =(TH2D*)f_RecoRecoilCovMat->Get("h2_RecoRecoilCovMat")->Clone();
  cout<<"hallo I am here"<<endl; 
  if(BaseName == "WpToMuNu" || BaseName == "WmToMuNu" )
    SVD_Post.RecoQCDRatioCovMat =(TH2D*)f_RecoQCDRatioCovMat->Get("h2_RecoQCDRatioCovMat")->Clone();
  if(BaseName == "WpToEleNu" || BaseName == "WmToEleNu" )
    SVD_Post.RecoScaleCovMat =(TH2D*)f_RecoScaleCovMat->Get("h2_RecoScaleCovMat")->Clone();
  if(BaseName == "WpToEleNu" || BaseName == "WpToMuNu" )
  {
    sprintf(tmpName,"hSigWPpt");
    h1_SigWptFSR     =(TH1D*)f_RecoFSRCovMat->Get(tmpName)->Clone(tmpName);
  }else if(BaseName == "WmToEleNu"|| BaseName == "WmToMuNu" )
  {
    sprintf(tmpName,"hSigWMpt");
    h1_SigWptFSR     =(TH1D*)f_RecoFSRCovMat->Get(tmpName)->Clone(tmpName);
  }
  
  for( int i(1); i<= SVD_Post.data->GetNbinsX(); i++)
  {
    cout<<"h1_SigWptFSR:   "<<h1_SigWptFSR->GetBinContent(i)<<endl;
  }
  
  for( int i(1); i<= SVD_Post.data->GetNbinsX(); i++)
  {
    for( int j(1); j<= SVD_Post.data->GetNbinsX(); j++)
    {
      //cout<<"Nominal :    "<<h1_Data_SigYild->GetBinContent(i)<<"     FSR   "<<h1_SigWptFSR->GetBinContent(i)<<"  Deviation   "<<TMath::Abs(h1_Data_SigYild->GetBinContent(i)-h1_SigWptFSR->GetBinContent(i))<<endl;
      //SVD_Post.RecoFSRCovMat->SetBinContent(i,j, TMath::Abs(h1_Data_SigYild->GetBinContent(i)-h1_SigWptFSR->GetBinContent(i))*TMath::Abs(h1_Data_SigYild->GetBinContent(j)-h1_SigWptFSR->GetBinContent(j))   );
      SVD_Post.RecoFSRCovMat->SetBinContent(i,j, (h1_Data_SigYild->GetBinContent(i)-h1_SigWptFSR->GetBinContent(i))*(h1_Data_SigYild->GetBinContent(j)-h1_SigWptFSR->GetBinContent(j)));
    }
  }
  
//Statistic Covariance Matrix
  gStyle->SetPaintTextFormat("4.2f"); 
  tmpTStr = "RecoStatCovMat_"+BaseName;
  pltRecoStatCov = new CPlot(tmpTStr,"Recon Statistic Covariance Matrix","","");
  pltRecoStatCov -> setOutDir(resultDir);
  gPad->SetLogz(0);
  //pltRecoStatCov -> AddHist2D(SVD_Post.RecoStatisticCovMat,"COLZ",kWhite,kBlack);
  //pltRecoStatCov -> AddHist2D(SVD_Post.RecoStatisticCovMat,"TEXT",kWhite,kBlack);
  SVD_Post.RecoStatisticCovMat -> SetMarkerSize(0.8);
  pltRecoStatCov->AddHist2D(SVD_Post.RecoStatisticCovMat,"COLTEXTZ",kWhite,kBlack);
  pltRecoStatCov-> Draw(myCan,kTRUE,"png");

//Lepton Efficiency Correction Covariance Matrix
  tmpTStr = "RecoEffiCovMat_"+BaseName;
  pltRecoEffCov = new CPlot(tmpTStr,"Recon EffCorr Covariance Matrix","","");
  pltRecoEffCov -> setOutDir(resultDir);
  gPad->SetLogz(0);
  SVD_Post.RecoEffiCovMat -> SetMarkerSize(0.8);
  pltRecoEffCov->AddHist2D(SVD_Post.RecoEffiCovMat,"COLTEXTZ",kWhite,kBlack);
  //pltRecoEffCov->AddHist2D(SVD_Post.RecoEffiCovMat,"COLZ",kWhite,kBlack);
  //pltRecoEffCov->AddHist2D(SVD_Post.RecoEffiCovMat,"TEXT",kWhite,kBlack);
  pltRecoEffCov->Draw(myCan,kTRUE,"png");

//Recoil Correction Covariance Matrix
  tmpTStr = "RecoRecoilCovMat_"+BaseName;
  pltRecoRecoilCov = new CPlot(tmpTStr,"Recon RecoilCorr Covariance Matrix","","");
  pltRecoRecoilCov -> setOutDir(resultDir);
  gPad->SetLogz(0);
  SVD_Post.RecoRecoilCovMat -> SetMarkerSize(0.8);
  pltRecoRecoilCov->AddHist2D(SVD_Post.RecoRecoilCovMat,"COLTEXTZ",kWhite,kBlack);
  pltRecoRecoilCov-> Draw(myCan,kTRUE,"png");

//Smear Correction Covariance Matrix
  tmpTStr = "RecoSmearCovMat_"+BaseName;
  pltRecoSmearCov = new CPlot(tmpTStr,"Recon SmearCorr Covariance Matrix","","");
  pltRecoSmearCov -> setOutDir(resultDir);
  gPad->SetLogz(0);
  SVD_Post.RecoSmearCovMat -> SetMarkerSize(0.8);
  pltRecoSmearCov->AddHist2D(SVD_Post.RecoSmearCovMat,"COLTEXTZ",kWhite,kBlack);
  pltRecoSmearCov-> Draw(myCan,kTRUE,"png");

  if(BaseName == "WpToMuNu" || BaseName == "WmToMuNu" ){
    //QCD Signal Ratio Correction Covariance Matrix
    tmpTStr = "RecoQCDRatioCovMat_"+BaseName;
    pltRecoQCDRatioCov = new CPlot(tmpTStr,"Recon QCDSignalRatio Covariance Matrix","","");
    pltRecoQCDRatioCov -> setOutDir(resultDir);
    gPad->SetLogz(0);
    SVD_Post.RecoQCDRatioCovMat -> SetMarkerSize(0.8);
    pltRecoQCDRatioCov -> AddHist2D(SVD_Post.RecoQCDRatioCovMat,"COLTEXTZ",kWhite,kBlack);
    pltRecoQCDRatioCov -> Draw(myCan,kTRUE,"png");
  }else if(BaseName == "WpToEleNu" || BaseName == "WmToEleNu" ){
    tmpTStr = "RecoScaleCovMat_"+BaseName;
    pltRecoScaleCov = new CPlot(tmpTStr,"Recon Scale Covariance Matrix","","");
    pltRecoScaleCov->setOutDir(resultDir);
    gPad->SetLogz();
    //pltRecoScaleCov->AddHist2D(SVD_Post.BstatCov,"COLZ",kWhite,kBlack);
    pltRecoScaleCov->AddHist2D(SVD_Post.RecoScaleCovMat,"COLZ",kWhite,kBlack);
    pltRecoScaleCov->Draw(myCan,kTRUE,"png");
  }

//FSR Covariance Matrix
  //tmpTStr = "RecoFSRCovMat_"+BaseName;
  //pltRecoFSRCov = new CPlot(tmpTStr,"Recon FSR Covariance Matrix","","");
  //pltRecoFSRCov -> setOutDir(resultDir);
  //gPad->SetLogz(0);
  //SVD_Post.RecoFSRCovMat -> SetMarkerSize(0.8);
  //pltRecoFSRCov -> AddHist2D(SVD_Post.RecoFSRCovMat,"COLTEXTZ",kWhite,kBlack);
  //pltRecoFSRCov -> Draw(myCan,kTRUE,"png");

  Fout << "Effi Reco stage Syst"<< endl;
  Fout <<fixed<<setprecision(4);
  Fout << "Bin" << "\t" << "Wpt yield " << "\t" << "Cov_i_i" << "\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
  Fout << "=============================================================" << endl;
  for( int i(1);i<=h1_Data_SigYild->GetNbinsX(); i++)
  {
    Fout << i << "\t" << h1_Data_SigYild->GetBinContent(i) << "\t\t" << SVD_Post.RecoEffiCovMat->GetBinContent(i,i) << "\t\t"<< TMath::Sqrt(SVD_Post.RecoEffiCovMat->GetBinContent(i,i)) << "\t\t" << TMath::Sqrt(SVD_Post.RecoEffiCovMat->GetBinContent(i,i))/h1_Data_SigYild->GetBinContent(i)*100 << endl;
  }
  

  Fout << "Smear Reco stage Syst"<< endl;
  Fout << "Bin" << "\t" << "Wpt yield " << "\t\t" << "Cov_i_i" << "\t\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
  Fout << "" << "\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t" << "" << endl;
  for( int i(1);i<=h1_Data_SigYild->GetNbinsX(); i++)
  {
    Fout << i << "\t" << h1_Data_SigYild->GetBinContent(i) << "\t\t" << SVD_Post.RecoSmearCovMat->GetBinContent(i,i) << "\t\t"<< TMath::Sqrt(SVD_Post.RecoSmearCovMat->GetBinContent(i,i)) << "\t\t" << TMath::Sqrt(SVD_Post.RecoSmearCovMat->GetBinContent(i,i))/h1_Data_SigYild->GetBinContent(i)*100 << endl;
  }

  Fout << "Recoil Reco stage Syst"<< endl;
  Fout << "Bin" << "\t" << "Wpt yield " << "\t\t" << "Cov_i_i" << "\t\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
  Fout << "" << "\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t" << "" << endl;
  for( int i(1);i<=h1_Data_SigYild->GetNbinsX(); i++)
  {
    Fout << i << "\t" << h1_Data_SigYild->GetBinContent(i) << "\t\t" << SVD_Post.RecoRecoilCovMat->GetBinContent(i,i) << "\t\t"<< TMath::Sqrt(SVD_Post.RecoRecoilCovMat->GetBinContent(i,i)) << "\t\t" << TMath::Sqrt(SVD_Post.RecoRecoilCovMat->GetBinContent(i,i))/h1_Data_SigYild->GetBinContent(i)*100 << endl;
  }
  
//  Fout << "Lumi Reco stage Syst"<< endl;
//  Fout << "Bin" << "\t" << "Wpt yield " << "\t\t" << "Cov_i_i" << "\t\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
//  Fout << "" << "\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t" << "" << endl;
//  for( int i(1);i<=h1_Data_SigYild->GetNbinsX(); i++)
//  {
//   Fout << i << "\t" << h1_Data_SigYild->GetBinContent(i) << "\t\t" << SVD_Post.RecoLumiCovMat->GetBinContent(i,i) << "\t\t"<< TMath::Sqrt(SVD_Post.RecoLumiCovMat->GetBinContent(i,i)) << "\t\t" << TMath::Sqrt(SVD_Post.RecoLumiCovMat->GetBinContent(i,i))/h1_Data_SigYild->GetBinContent(i)*100 << endl;
//  }
  
  //Fout << "FSR Reco stage Syst"<< endl;
  //Fout << "Bin" << "\t" << "Wpt yield " << "\t\t" << "Cov_i_i" << "\t\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
  //Fout << "" << "\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t" << "" << endl;
  //for( int i(1);i<=h1_Data_SigYild->GetNbinsX(); i++)
  //{
  //  Fout << i << "\t" << h1_Data_SigYild->GetBinContent(i) << "\t\t" << SVD_Post.RecoFSRCovMat->GetBinContent(i,i) << "\t\t"<< TMath::Sqrt(SVD_Post.RecoFSRCovMat->GetBinContent(i,i)) << "\t\t" << TMath::Sqrt(SVD_Post.RecoFSRCovMat->GetBinContent(i,i))/h1_Data_SigYild->GetBinContent(i)*100 << endl;
  //}
  
  if(BaseName == "WpToMuNu" || BaseName == "WmToMuNu" ){
    Fout << "QCDRatio Reco stage"<< endl;
    Fout << "Bin" << "\t" << "Wpt yield " << "\t\t" << "Cov_i_i" << "\t\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
    Fout << "" << "\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t" << "" << endl;
    for( int i(1);i<=h1_Data_SigYild->GetNbinsX(); i++)
    {
      Fout << i << "\t" << h1_Data_SigYild->GetBinContent(i) << "\t\t" << SVD_Post.RecoQCDRatioCovMat->GetBinContent(i,i) << "\t\t"<< TMath::Sqrt(SVD_Post.RecoQCDRatioCovMat->GetBinContent(i,i)) << "\t\t" << TMath::Sqrt(SVD_Post.RecoQCDRatioCovMat->GetBinContent(i,i))/h1_Data_SigYild->GetBinContent(i)*100 << endl;
    }
  }else if (BaseName == "WpToEleNu" || BaseName == "WmToEleNu" ){
    Fout << "Scale Reco stage Syst"<< endl;
    Fout << "Bin" << "\t" << "Wpt yield " << "\t" << "Cov_i_i" << "\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
    Fout << "=============================================================" << endl;
    for( int i(1);i<=h1_Data_SigYild->GetNbinsX(); i++)
    {
      Fout << i << "\t" << h1_Data_SigYild->GetBinContent(i) << "\t" << SVD_Post.RecoScaleCovMat->GetBinContent(i,i) << "\t"<< TMath::Sqrt(SVD_Post.RecoScaleCovMat->GetBinContent(i,i)) << "\t" << TMath::Sqrt(SVD_Post.RecoScaleCovMat->GetBinContent(i,i))/h1_Data_SigYild->GetBinContent(i)*100 << endl;
    }
    
    Fout << "En.Res. Reco stage Syst"<< endl;
    Fout << "Bin" << "\t" << "Wpt yield " << "\t" << "Sqrt(Scale^2+Smear^2)" << endl;
    Fout << "=============================================================" << endl;
    for( int i(1);i<=h1_Data_SigYild->GetNbinsX(); i++)
    {
      Fout << i << "\t" << h1_Data_SigYild->GetBinContent(i) << "\t" << TMath::Sqrt(TMath::Power(TMath::Sqrt(SVD_Post.RecoScaleCovMat->GetBinContent(i,i)),2) + TMath::Power( TMath::Sqrt(SVD_Post.RecoSmearCovMat->GetBinContent(i,i)),2))/h1_Data_SigYild->GetBinContent(i)*100 <<endl;
    }
  }
  
  Fout << "Statistic Reco stage"<< endl;
  Fout << "Bin" << "\t" << "Wpt yield " << "\t\t" << "Cov_i_i" << "\t\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
  Fout << "" << "\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t" << "" << endl;
  for( int i(1);i<=h1_Data_SigYild->GetNbinsX(); i++)
  {
    Fout << i << "\t" << h1_Data_SigYild->GetBinContent(i) << "\t\t" << SVD_Post.RecoStatisticCovMat->GetBinContent(i,i) << "\t\t"<< TMath::Sqrt(SVD_Post.RecoStatisticCovMat->GetBinContent(i,i)) << "\t\t" << TMath::Sqrt(SVD_Post.RecoStatisticCovMat->GetBinContent(i,i))/h1_Data_SigYild->GetBinContent(i)*100 << endl;
  }

  Fout << ""<< endl;
  Fout << ""<< endl;
  Fout << "Systematics "<< endl;
  //Fout << "Bin" << "\t\t"<<"Statistic err"<<"\t\t" << "Lept Recon Effi Syst " << "\t\t" << "Scale Syst" << "\t\t" << "Smear Syst" << "\t\t" << "Recoil syst" << "\t\t" << "Lumi Syst" << "\t\t" <<  "FSR Syst" << "\t\t" <<endl;
  
  if(BaseName == "WpToMuNu" || BaseName == "WmToMuNu" )
    Fout << "Bin" << "\t\t"<<"Statistic err"<<"\t\t" << "Lept Recon Effi Syst " << "\t\t" <<  "Smear Syst" << "\t\t" << "Recoil syst" <<  "\t\t" <<  "FSR Syst" << "\t\t" <<  "QCDvsSignalRaio Syst" <<endl;
  else if(BaseName == "WpToEleNu" || BaseName == "WmToEleNu" )
    Fout << "Bin" << "\t\t"<<"Statistic err"<<"\t\t" << "Lept Recon Effi Syst " << "\t\t" <<  "Smear Syst" << "\t\t" << "Recoil syst" <<  "\t\t" <<  "FSR Syst" << "\t\t" <<  "Scale Syst" <<endl;
  
  Fout << "" << "\t\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t\t" << "" << "\t\t" << "" << "\t\t" << "" << "\t\t" << "" << endl;
  if(BaseName == "WpToMuNu" || BaseName == "WmToMuNu" )
    for( int i(1);i<=h1_Data_SigYild->GetNbinsX(); i++)
    {
      Fout << i << "\t\t" << TMath::Sqrt(SVD_Post.RecoStatisticCovMat->GetBinContent(i,i))/h1_Data_SigYild->GetBinContent(i)*100 << "\t\t" << TMath::Sqrt(SVD_Post.RecoEffiCovMat->GetBinContent(i,i))/h1_Data_SigYild->GetBinContent(i)*100 << "\t\t"<< TMath::Sqrt(SVD_Post.RecoSmearCovMat->GetBinContent(i,i))/h1_Data_SigYild->GetBinContent(i)*100 << "\t\t"<< TMath::Sqrt(SVD_Post.RecoRecoilCovMat->GetBinContent(i,i))/h1_Data_SigYild->GetBinContent(i)*100 << "\t\t" << "\t\t"<< "0" <<TMath::Sqrt(SVD_Post.RecoQCDRatioCovMat->GetBinContent(i,i))/h1_Data_SigYild->GetBinContent(i)*100 << endl;
    }
  else if(BaseName == "WpToEleNu" || BaseName == "WmToEleNu" )
    for( int i(1);i<=h1_Data_SigYild->GetNbinsX(); i++)
    {
      Fout << i << "\t\t" << TMath::Sqrt(SVD_Post.RecoStatisticCovMat->GetBinContent(i,i))/h1_Data_SigYild->GetBinContent(i)*100 << "\t\t" << TMath::Sqrt(SVD_Post.RecoEffiCovMat->GetBinContent(i,i))/h1_Data_SigYild->GetBinContent(i)*100 << "\t\t"<< TMath::Sqrt(SVD_Post.RecoSmearCovMat->GetBinContent(i,i))/h1_Data_SigYild->GetBinContent(i)*100 << "\t\t"<< TMath::Sqrt(SVD_Post.RecoRecoilCovMat->GetBinContent(i,i))/h1_Data_SigYild->GetBinContent(i)*100 << "\t\t" << "\t\t"<< "0" <<TMath::Sqrt(SVD_Post.RecoScaleCovMat->GetBinContent(i,i))/h1_Data_SigYild->GetBinContent(i)*100 << endl;
    }
  
  Fout << ""<< endl;
  Fout << ""<< endl;
  Fout << ""<< endl;
  Fout << "Total Systematics - Reconstruction stage"<< endl;
  //Fout <<  "\t\t"<< "Sqrt(LeptRecEff^2 + Scale^2 + Smear^2 +Recoil^2 +Lumi^2 +FSR^2) "<<endl;
  if(BaseName == "WpToMuNu" || BaseName == "WmToMuNu" )
    Fout <<  "\t\t"<< "Sqrt(LeptRecEff^2 +  Smear^2 +Recoil^2 +QCDvsSignalRatio^2) "<<endl;
  else if(BaseName == "WpToEleNu" || BaseName == "WmToEleNu" )
    Fout <<  "\t\t"<< "Sqrt(LeptRecEff^2 + Scale^2 + Smear^2 +Recoil^2) "<<endl;
  
  Fout << "" << "\t\t" << " " << "\t\t" << ""  << endl;
  if(BaseName == "WpToMuNu" || BaseName == "WmToMuNu" )
    for( int i(1);i<=h1_Data_SigYild->GetNbinsX(); i++)
    {
      Fout << TMath::Sqrt( TMath::Power(TMath::Sqrt(SVD_Post.RecoEffiCovMat->GetBinContent(i,i)),2)+ TMath::Power( TMath::Sqrt(SVD_Post.RecoSmearCovMat->GetBinContent(i,i)),2) + TMath::Power(TMath::Sqrt(SVD_Post.RecoRecoilCovMat->GetBinContent(i,i)),2)+ TMath::Power( TMath::Sqrt(SVD_Post.RecoQCDRatioCovMat->GetBinContent(i,i)),2))/h1_Data_SigYild->GetBinContent(i)*100 <<endl;
    }
  else if(BaseName == "WpToEleNu" || BaseName == "WmToEleNu" )
    for( int i(1);i<=h1_Data_SigYild->GetNbinsX(); i++)
    {
      Fout << TMath::Sqrt( TMath::Power(TMath::Sqrt(SVD_Post.RecoEffiCovMat->GetBinContent(i,i)),2)+ TMath::Power( TMath::Sqrt(SVD_Post.RecoSmearCovMat->GetBinContent(i,i)),2) + TMath::Power(TMath::Sqrt(SVD_Post.RecoRecoilCovMat->GetBinContent(i,i)),2)+ TMath::Power( TMath::Sqrt(SVD_Post.RecoScaleCovMat->GetBinContent(i,i)),2))/h1_Data_SigYild->GetBinContent(i)*100 <<endl;
    }
  
  //SVD_Post.RecoStatisticCovMat->Write();
  //SVD_Post.RecoScaleCovMat->Write();
  //SVD_Post.RecoEffiCovMat->Write();
  //SVD_Post.RecoSmearCovMat->Write();
  //SVD_Post.RecoRecoilCovMat->Write();
  //SVD_Post.RecoLumiCovMat->Write();
  //SVD_Post.RecoFSRCovMat->Write();


  SVD_Post.TotalRecoCovMat->Add(SVD_Post.RecoStatisticCovMat );
  SVD_Post.TotalRecoCovMat->Add(SVD_Post.RecoEffiCovMat );
  SVD_Post.TotalRecoCovMat->Add(SVD_Post.RecoScaleCovMat );
  SVD_Post.TotalRecoCovMat->Add(SVD_Post.RecoSmearCovMat );
  SVD_Post.TotalRecoCovMat->Add(SVD_Post.RecoRecoilCovMat );
  //SVD_Post.TotalRecoCovMat->Add(SVD_Post.RecoQCDRatioCovMat);
  
  
  //SVD_Post.TotalRecoCovMat->Add(SVD_Post.RecoFSRCovMat );

 
  SVD_Post.TotalRecoCovMat->Write();

   for( int i(1); i<= SVD_Post.data->GetNbinsX(); i++)
   {
     for( int j(1); j<= SVD_Post.data->GetNbinsX(); j++)
     {
       cout<<"RecoTotalCovMat:    "<<SVD_Post.TotalRecoCovMat->GetBinContent(i,j)<<endl;
     }
   }

  //InputCovMat to Detector Unfolding
  tmpTStr = "InputCovMatToDetUnf_"+BaseName;
  pltUnfPost_InputCov = new CPlot(tmpTStr,"Input TotalCovMat to Detector Unfolding","","");
  pltUnfPost_InputCov -> setOutDir(resultDir);
  gPad->SetLogz(0);
  SVD_Post.TotalRecoCovMat -> SetMarkerSize(0.8);
  pltUnfPost_InputCov -> AddHist2D(SVD_Post.TotalRecoCovMat,"COLTEXTZ",kWhite,kBlack);
  pltUnfPost_InputCov -> Draw(myCan,kTRUE,"png");

  //=================================================================
  //=================================================================
  // Detector Unfolding (Error propagation of Cov matrix) ===========
  //=================================================================
  //=================================================================


  //TSVDUnfold *tsvdData = new TSVDUnfold(
  //    SVD_Post.data,SVD_Post.bini,SVD_Post.xini,SVD_Post.Adet);
  
 // TSVDUnfold *tsvdData = new TSVDUnfold(
 //     SVD_Post.data,SVD_Post.RecoStatisticCovMat,SVD_Post.bini,SVD_Post.xini,SVD_Post.Adet);
  
  TSVDUnfold *tsvdData = new TSVDUnfold(
      SVD_Post.data,SVD_Post.TotalRecoCovMat,SVD_Post.bini,SVD_Post.xini,SVD_Post.Adet);

  //SVD_Post.statCov = tsvdData->GetBCov();
  tsvdData->SetNormalize( kFALSE );
  SVD_Post.unfRes = tsvdData->Unfold(4); 
  //SVD_Post.unfRes = tsvdData->Unfold(6); 
  //SVD_Post.unfRes = tsvdData->Unfold(7); 
  //SVD_Post.unfRes = tsvdData->Unfold(9); 
  SVD_Post.dDist = tsvdData->GetD();
  SVD_Post.svDist = tsvdData->GetSV();
  
  SVD_Post.uStatCov = tsvdData->GetUnfoldCovMatrix( SVD_Post.RecoStatisticCovMat, 1000);
  //SVD_Post.uTotalCovMat = tsvdData->GetUnfoldCovMatrix( SVD_Post.RecoStatisticCovMat, 100);
  SVD_Post.uTotalCovMat = (TH2D*)SVD_Post.uStatCov->Clone("uTotalCovMat");
  //SVD_Post.uStatCov = tsvdData->GetUnfoldCovMatrix( SVD_Post.BstatCov, 100);
  
  
  SVD_Post.uRecoEffiCovMat = tsvdData->GetUnfoldCovMatrix( SVD_Post.RecoEffiCovMat, 1000);
  if(BaseName == "WpToEleNu" || BaseName == "WmToEleNu" )
    SVD_Post.uRecoScaleCovMat = tsvdData->GetUnfoldCovMatrix( SVD_Post.RecoScaleCovMat, 1000);
  SVD_Post.uRecoSmearCovMat = tsvdData->GetUnfoldCovMatrix( SVD_Post.RecoSmearCovMat, 1000);
  SVD_Post.uRecoRecoilCovMat = tsvdData->GetUnfoldCovMatrix( SVD_Post.RecoRecoilCovMat, 1000);
  //SVD_Post.uRecoLumiCovMat = tsvdData->GetUnfoldCovMatrix( SVD_Post.RecoLumiCovMat, 100);
  //SVD_Post.uRecoFSRCovMat = tsvdData->GetUnfoldCovMatrix( SVD_Post.RecoFSRCovMat, 100);
  SVD_Post.uRecoStatisticCovMat = tsvdData->GetUnfoldCovMatrix( SVD_Post.RecoStatisticCovMat, 1000);
  if(BaseName == "WpToMuNu" || BaseName == "WmToMuNu" )
    SVD_Post.uRecoQCDRatioCovMat = tsvdData->GetUnfoldCovMatrix( SVD_Post.RecoQCDRatioCovMat, 1000);
  //SVD_Post.uRecoStatisticCovMat = tsvdData->GetUnfoldCovMatrix( SVD_Post.statCov, 100);
  
//Total Cov Matrix = Stat + Syst + ResponseMatrix
  SVD_Post.uTotalCovMat->Add(SVD_Post.uRecoEffiCovMat);
  if(BaseName == "WpToEleNu" || BaseName == "WmToEleNu" )
    SVD_Post.uTotalCovMat->Add(SVD_Post.uRecoScaleCovMat);
  SVD_Post.uTotalCovMat->Add(SVD_Post.uRecoSmearCovMat);
  SVD_Post.uTotalCovMat->Add(SVD_Post.uRecoRecoilCovMat);
  if(BaseName == "WpToMuNu" || BaseName == "WmToMuNu" )
    SVD_Post.uTotalCovMat->Add(SVD_Post.uRecoQCDRatioCovMat);
  
//Total Cov Matrix = Stat + Syst + ResponseMatrix
  for( int i(1); i<= SVD_Post.data->GetNbinsX(); i++)
  {
    for( int j(1); j<= SVD_Post.data->GetNbinsX(); j++)
    {
      SVD_Post.BstatCorr_uTotal->SetBinContent(i,j, fabs(SVD_Post.uTotalCovMat->GetBinContent(i,j))/sqrt(fabs(SVD_Post.uTotalCovMat->GetBinContent(i,i))*fabs(SVD_Post.uTotalCovMat->GetBinContent(j,j))));
      SVD_Post.AbsNormCorrErr->SetBinContent(i,j, 100*sqrt(fabs(SVD_Post.uTotalCovMat->GetBinContent(i,j))/(SVD_Post.unfRes->GetBinContent(i)*SVD_Post.unfRes->GetBinContent(j))));
      //SVD_Post.AbsNormCorrErr->SetBinContent(i,j, 100*sqrt(fabs(SVD_Post.uTotalSystCov->GetBinContent(i,j))/(SVD_Post.unfRes->GetBinContent(i)*SVD_Post.unfRes->GetBinContent(j))));
    }
  }

//Absolute Normalized correlated error matrix 
  tmpTStr = "uAbsNormCorrErrMat_D_Unf_"+BaseName;
  pltUnfPost_AbsNormCorrErr = new CPlot(tmpTStr,"D_Unf Absolute Normalized correlated error matrix","","");
  pltUnfPost_AbsNormCorrErr -> setOutDir(resultDir);
  gPad->SetLogz(0);
  SVD_Post.AbsNormCorrErr -> SetMarkerSize(0.8);
  pltUnfPost_AbsNormCorrErr->AddHist2D(SVD_Post.AbsNormCorrErr,"COLTEXTZ",kWhite,kBlack);
  //pltUnfPost_AbsNormCorrErr->AddHist2D(SVD_Post.AbsNormCorrErr,"COLZ",kWhite,kBlack);
  pltUnfPost_AbsNormCorrErr->Draw(myCan,kTRUE,"png");

//Total Syst Cov Matrix
  SVD_Post.uTotalSystCov = (TH2D*)SVD_Post.uRecoEffiCovMat->Clone("uTotalSystCov");
  if(BaseName == "WpToEleNu" || BaseName == "WmToEleNu" )
    SVD_Post.uTotalSystCov->Add(SVD_Post.uRecoScaleCovMat);
  SVD_Post.uTotalSystCov->Add(SVD_Post.uRecoSmearCovMat);
  SVD_Post.uTotalSystCov->Add(SVD_Post.uRecoRecoilCovMat);
  if(BaseName == "WpToMuNu" || BaseName == "WmToMuNu" )
    SVD_Post.uTotalSystCov->Add(SVD_Post.uRecoQCDRatioCovMat);
  
   //SVD_Post.uRecoStatisticCovMat->Write();
   //SVD_Post.uRecoEffiCovMat->Write();
   //SVD_Post.uRecoSmearCovMat->Write();
   //SVD_Post.uRecoRecoilCovMat->Write();
   //SVD_Post.uRecoLumiCovMat->Write();
   //SVD_Post.uRecoFSRCovMat->Write();


   for( int i(1); i<= SVD_Post.data->GetNbinsX(); i++)
   {
       cout<<"SVD_Post.uStatCov_i_i  AfterPost     :    "<<SVD_Post.uStatCov->GetBinContent(i,i)<<endl;
       cout<<"Square root ofSVD_Post.uStatCov_i_i  :           "<<TMath::Sqrt(SVD_Post.uStatCov->GetBinContent(i,i))<<endl;
       cout<<"Systematics %                               :              "<<TMath::Sqrt(SVD_Post.uStatCov->GetBinContent(i,i))/SVD_Post.unfRes->GetBinContent(i)*100<<endl;
   }


  cout<<"Check01"<<endl;
   for( int i(1); i<= SVD_Post.data->GetNbinsX(); i++)
   {
       cout<<"SVD_Post.uRecoEffiCovMat_i_i  AfterPost     :    "<<SVD_Post.uRecoEffiCovMat->GetBinContent(i,i)<<endl;
       cout<<"Square root ofSVD_Post.uRecoEffiCovMat_i_i  :           "<<TMath::Sqrt(SVD_Post.uRecoEffiCovMat->GetBinContent(i,i))<<endl;
       cout<<"Systematics %                               :              "<<TMath::Sqrt(SVD_Post.uRecoEffiCovMat->GetBinContent(i,i))/SVD_Post.unfRes->GetBinContent(i)*100<<endl;
   }
  cout<<"Check02"<<endl;
   
   
   
   for( int i(1); i<= SVD_Post.data->GetNbinsX(); i++)
   {
       cout<<"SVD_Post.unfRes->GetBinContent(i) %         :    "<<SVD_Post.unfRes->GetBinContent(i)<<endl;
       
   }
  cout<<"Check03"<<endl;

   for( int i(1); i<= SVD_Post.data->GetNbinsX(); i++)
   {
     for( int j(1); j<= SVD_Post.data->GetNbinsX(); j++)
     {
       cout<<"SVD_Post.uRecoEffiCovMat_i_j  AfterPost     :    "<<SVD_Post.uRecoEffiCovMat->GetBinContent(i,j)<<endl;
     }
   }
  cout<<"Check04"<<endl;

  Fout << "Effi Detector Unfolding stage Syst"<< endl;
  Fout << "Bin" << "\t" << "Wpt yield " << "\t\t" << "Cov_i_i" << "\t\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
  Fout << "" << "\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t" << "" << endl;
  for( int i(1);i<=SVD_Post.unfRes->GetNbinsX(); i++)
  {
    Fout << i << "\t" <<SVD_Post.unfRes->GetBinContent(i) << "\t\t" << SVD_Post.uRecoEffiCovMat->GetBinContent(i,i) << "\t\t"<< TMath::Sqrt(SVD_Post.uRecoEffiCovMat->GetBinContent(i,i)) << "\t\t" << TMath::Sqrt(SVD_Post.uRecoEffiCovMat->GetBinContent(i,i))/SVD_Post.unfRes->GetBinContent(i)*100 << endl;
  }

  cout<<"Check1"<<endl;
  if(BaseName == "WpToEleNu" || BaseName == "WmToEleNu" ){
    Fout << "Scale Detector Unfolding stage Syst"<< endl;
    Fout << "Bin" << "\t" << "Wpt yield " << "\t" << "Cov_i_i" << "\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
    Fout << "=============================================================" << endl;
    for( int i(1);i<=SVD_Post.unfRes->GetNbinsX(); i++)
    {
      Fout << i << "\t" <<SVD_Post.unfRes->GetBinContent(i) << "\t" << SVD_Post.uRecoScaleCovMat->GetBinContent(i,i) << "\t"<< TMath::Sqrt(SVD_Post.uRecoScaleCovMat->GetBinContent(i,i)) << "\t" << TMath::Sqrt(SVD_Post.uRecoScaleCovMat->GetBinContent(i,i))/SVD_Post.unfRes->GetBinContent(i)*100 << endl;
    }
  }
  cout<<"Check2"<<endl;

  Fout << "Smear Detector Unfolding stage Syst"<< endl;
  Fout << "Bin" << "\t" << "Wpt yield " << "\t\t" << "Cov_i_i" << "\t\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
  Fout << "" << "\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t" << "" << endl;
  for( int i(1);i<=SVD_Post.unfRes->GetNbinsX(); i++)
  {
    Fout << i << "\t" <<SVD_Post.unfRes->GetBinContent(i) << "\t\t" << SVD_Post.uRecoSmearCovMat->GetBinContent(i,i) << "\t\t"<< TMath::Sqrt(SVD_Post.uRecoSmearCovMat->GetBinContent(i,i)) << "\t\t" << TMath::Sqrt(SVD_Post.uRecoSmearCovMat->GetBinContent(i,i))/SVD_Post.unfRes->GetBinContent(i)*100 << endl;
  }

  cout<<"Check3"<<endl;
  Fout << "Recoil Detector Unfolding stage Syst"<< endl;
  Fout << "Bin" << "\t" << "Wpt yield " << "\t\t" << "Cov_i_i" << "\t\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
  Fout << "" << "\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t" << "" << endl;
  for( int i(1);i<=SVD_Post.unfRes->GetNbinsX(); i++)
  {
    Fout << i << "\t" <<SVD_Post.unfRes->GetBinContent(i) << "\t\t" << SVD_Post.uRecoRecoilCovMat->GetBinContent(i,i) << "\t\t"<< TMath::Sqrt(SVD_Post.uRecoRecoilCovMat->GetBinContent(i,i)) << "\t\t" << TMath::Sqrt(SVD_Post.uRecoRecoilCovMat->GetBinContent(i,i))/SVD_Post.unfRes->GetBinContent(i)*100 << endl;
  }
  
  cout<<"Check4"<<endl;
 // Fout << "Lumi Detector Unfolding stage Syst"<< endl;
 // Fout << "Bin" << "\t" << "Wpt yield " << "\t\t" << "Cov_i_i" << "\t\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
 // Fout << "" << "\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t" << "" << endl;
 // for( int i(1);i<=SVD_Post.unfRes->GetNbinsX(); i++)
 // {
 //   Fout << i << "\t" <<SVD_Post.unfRes->GetBinContent(i) << "\t\t" << SVD_Post.uRecoLumiCovMat->GetBinContent(i,i) << "\t\t"<< TMath::Sqrt(SVD_Post.uRecoLumiCovMat->GetBinContent(i,i)) << "\t\t" << TMath::Sqrt(SVD_Post.uRecoLumiCovMat->GetBinContent(i,i))/SVD_Post.unfRes->GetBinContent(i)*100 << endl;
 // }
  
  //Fout << "FSR Detector Unfolding stage Syst"<< endl;
  //Fout << "Bin" << "\t" << "Wpt yield " << "\t\t" << "Cov_i_i" << "\t\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
  //Fout << "" << "\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t" << "" << endl;
  //for( int i(1);i<=SVD_Post.unfRes->GetNbinsX(); i++)
  //{
  //  Fout << i << "\t" <<SVD_Post.unfRes->GetBinContent(i) << "\t\t" << SVD_Post.uRecoFSRCovMat->GetBinContent(i,i) << "\t\t"<< TMath::Sqrt(SVD_Post.uRecoFSRCovMat->GetBinContent(i,i)) << "\t\t" << TMath::Sqrt(SVD_Post.uRecoFSRCovMat->GetBinContent(i,i))/SVD_Post.unfRes->GetBinContent(i)*100 << endl;
  //}

  if(BaseName == "WpToMuNu" || BaseName == "WmToMuNu" ){
    Fout << "QCDRatio Detector Unfolding stage"<< endl;
    Fout << "Bin" << "\t" << "Wpt yield " << "\t\t" << "Cov_i_i" << "\t\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
    Fout << "" << "\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t" << "" << endl;
    for( int i(1);i<=h1_Data_SigYild->GetNbinsX(); i++)
    {
      Fout << i << "\t" << SVD_Post.unfRes->GetBinContent(i) << "\t\t" << SVD_Post.uRecoQCDRatioCovMat->GetBinContent(i,i) << "\t\t"<< TMath::Sqrt(SVD_Post.uRecoQCDRatioCovMat->GetBinContent(i,i)) << "\t\t" << TMath::Sqrt(SVD_Post.uRecoQCDRatioCovMat->GetBinContent(i,i))/SVD_Post.unfRes->GetBinContent(i)*100 << endl;
    }
  }
  cout<<"Check5"<<endl;
  Fout << "Statistic Detector Unfolding stage"<< endl;
  Fout << "Bin" << "\t" << "Wpt yield " << "\t\t" << "Cov_i_i" << "\t\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
  Fout << "" << "\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t" << "" << endl;
  for( int i(1);i<=h1_Data_SigYild->GetNbinsX(); i++)
  {
    Fout << i << "\t" << SVD_Post.unfRes->GetBinContent(i) << "\t\t" << SVD_Post.uRecoStatisticCovMat->GetBinContent(i,i) << "\t\t"<< TMath::Sqrt(SVD_Post.uRecoStatisticCovMat->GetBinContent(i,i)) << "\t\t" << TMath::Sqrt(SVD_Post.uRecoStatisticCovMat->GetBinContent(i,i))/SVD_Post.unfRes->GetBinContent(i)*100 << endl;
  }
   
  cout<<"Check6"<<endl;
  Fout << "Stat+Syst+RespMatErr systematic after Detector Unfolding"<< endl;
  Fout << "Bin" << "\t" << "Wpt yield " << "\t\t" << "Cov_i_i" << "\t\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
  Fout << "" << "\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t" << "" << endl;
  for( int i(1);i<=h1_Data_SigYild->GetNbinsX(); i++)
  {
    Fout << i << "\t" << SVD_Post.unfRes->GetBinContent(i) << "\t\t" << SVD_Post.uTotalCovMat->GetBinContent(i,i) << "\t\t"<< TMath::Sqrt(SVD_Post.uTotalCovMat->GetBinContent(i,i)) << "\t\t" << TMath::Sqrt(SVD_Post.uTotalCovMat->GetBinContent(i,i))/SVD_Post.unfRes->GetBinContent(i)*100 << endl;
  }
  cout<<"Check7"<<endl;
  Fout << ""<< endl;
  Fout << ""<< endl;
  Fout << ""<< endl;
  Fout << "Systematics"<< endl;
    //Fout << "Bin" << "\t\t"<<"Statistic err"<<"\t\t" << "Lept Recon Effi Syst " << "\t\t" << "Scale Syst" << "\t\t" << "Smear Syst" << "\t\t" << "Recoil syst" << "\t\t" << "Lumi Syst" << "\t\t" <<  "FSR Syst" << "\t\t" <<endl;
  if(BaseName == "WpToMuNu" || BaseName == "WmToMuNu" )
    Fout << "Bin" << "\t\t"<<"Statistic err"<<"\t\t" << "Lept Recon Effi Syst " << "\t\t" << "\t\t" << "Smear Syst" << "\t\t" << "Recoil syst" << "\t\t" <<  "FSR Syst" << "\t\t" <<  "QCDvsSignalRatio Syst" <<endl;
  else if(BaseName == "WpToEleNu" || BaseName == "WmToEleNu" )
    Fout << "Bin" << "\t\t"<<"Statistic err"<<"\t\t" << "Lept Recon Effi Syst " << "\t\t" << "\t\t" << "Smear Syst" << "\t\t" << "Recoil syst" << "\t\t" <<  "FSR Syst" << "\t\t" <<  "Scale Syst" <<endl;
  
  Fout << "" << "\t\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t\t" << "" << "\t\t" << "" << "\t\t" << "" << "\t\t" << "" << endl;
  if(BaseName == "WpToMuNu" || BaseName == "WmToMuNu" )
    for( int i(1);i<=h1_Data_SigYild->GetNbinsX(); i++)
    {
      Fout << i << "\t\t" << TMath::Sqrt(SVD_Post.uRecoStatisticCovMat->GetBinContent(i,i))/SVD_Post.unfRes->GetBinContent(i)*100 << "\t\t" << TMath::Sqrt(SVD_Post.uRecoEffiCovMat->GetBinContent(i,i))/SVD_Post.unfRes->GetBinContent(i)*100 << "\t\t"<< TMath::Sqrt(SVD_Post.uRecoSmearCovMat->GetBinContent(i,i))/SVD_Post.unfRes->GetBinContent(i)*100 << "\t\t"<< TMath::Sqrt(SVD_Post.uRecoRecoilCovMat->GetBinContent(i,i))/SVD_Post.unfRes->GetBinContent(i)*100 << "\t\t" "\t\t"<< "0" << "\t\t"<< TMath::Sqrt(SVD_Post.uRecoQCDRatioCovMat->GetBinContent(i,i))/SVD_Post.unfRes->GetBinContent(i)*100 <<endl;
    }
  cout<<"Check8"<<endl;
  if(BaseName == "WpToEleNu" || BaseName == "WmToEleNu" )
    for( int i(1);i<=h1_Data_SigYild->GetNbinsX(); i++)
    {
      Fout << i << "\t\t" << TMath::Sqrt(SVD_Post.uRecoStatisticCovMat->GetBinContent(i,i))/SVD_Post.unfRes->GetBinContent(i)*100 << "\t\t" << TMath::Sqrt(SVD_Post.uRecoEffiCovMat->GetBinContent(i,i))/SVD_Post.unfRes->GetBinContent(i)*100 << "\t\t"<< TMath::Sqrt(SVD_Post.uRecoSmearCovMat->GetBinContent(i,i))/SVD_Post.unfRes->GetBinContent(i)*100 << "\t\t"<< TMath::Sqrt(SVD_Post.uRecoRecoilCovMat->GetBinContent(i,i))/SVD_Post.unfRes->GetBinContent(i)*100 << "\t\t" "\t\t"<< "0" << "\t\t"<< TMath::Sqrt(SVD_Post.uRecoScaleCovMat->GetBinContent(i,i))/SVD_Post.unfRes->GetBinContent(i)*100 <<endl;
    }
  cout<<"Check9"<<endl;
  
  Fout << ""<< endl;
  Fout << ""<< endl;
  Fout << ""<< endl;
  Fout << "Systematics Detector Unfolding stage"<< endl;
  if(BaseName == "WpToMuNu" || BaseName == "WmToMuNu" )
    Fout <<  "\t\t"<< "Sqrt(LeptRecEff^2 +  Smear^2 +Recoil^2 +QCDvsSignalRatio^2) "<<endl;
  else if(BaseName == "WpToEleNu" || BaseName == "WmToEleNu" )
    Fout <<  "\t\t"<< "Sqrt(LeptRecEff^2 +  Smear^2 +Recoil^2 +Scale^2) "<<endl;
  
  Fout << "" << "\t\t" << " " << "\t\t" << ""  << endl;
  if(BaseName == "WpToMuNu" || BaseName == "WmToMuNu" )
    for( int i(1);i<=h1_Data_SigYild->GetNbinsX(); i++)
    {
      Fout << TMath::Sqrt( TMath::Power(TMath::Sqrt(SVD_Post.uRecoEffiCovMat->GetBinContent(i,i)),2)+TMath::Power( TMath::Sqrt(SVD_Post.uRecoSmearCovMat->GetBinContent(i,i)),2) + TMath::Power(TMath::Sqrt(SVD_Post.uRecoRecoilCovMat->GetBinContent(i,i)),2)+  TMath::Power( TMath::Sqrt(SVD_Post.uRecoQCDRatioCovMat->GetBinContent(i,i)),2))/SVD_Post.unfRes->GetBinContent(i)*100 <<endl;
    }
  else if(BaseName == "WpToEleNu" || BaseName == "WmToEleNu" )
    for( int i(1);i<=h1_Data_SigYild->GetNbinsX(); i++)
    {
      Fout << TMath::Sqrt( TMath::Power(TMath::Sqrt(SVD_Post.uRecoEffiCovMat->GetBinContent(i,i)),2)+TMath::Power( TMath::Sqrt(SVD_Post.uRecoSmearCovMat->GetBinContent(i,i)),2) + TMath::Power(TMath::Sqrt(SVD_Post.uRecoRecoilCovMat->GetBinContent(i,i)),2)+  TMath::Power( TMath::Sqrt(SVD_Post.uRecoScaleCovMat->GetBinContent(i,i)),2))/SVD_Post.unfRes->GetBinContent(i)*100 <<endl;
    }
  
  tmpTStr = "RecoEffiCovMat_cov_AfterPost"+BaseName;
  pltReconEffi_cov = new CPlot(tmpTStr,"ReconEffi Covariance matrix AfterPost","","");
  pltReconEffi_cov->setOutDir(resultDir);
  gPad->SetLogz(0);
  //pltReconEffi_cov->AddHist2D(SVD_Post.uRecoEffiCovMat,"COLZ",kWhite,kBlack);
  //gPad->SetMarkerSize(1.8);
  pltReconEffi_cov->AddHist2D(SVD_Post.uRecoEffiCovMat,"COLZ",kWhite,kBlack);
  pltReconEffi_cov->AddHist2D(SVD_Post.uRecoEffiCovMat,"TEXT",kWhite,kBlack);
  pltReconEffi_cov->Draw(myCan,kTRUE,"png");
  //SVD_Post.uRecoEffiCovMat->Write();
  
  if(BaseName == "WpToEleNu" || BaseName == "WmToEleNu" ){
    tmpTStr = "RecoScaleCovMat_cov_AfterPost"+BaseName;
    pltReconScale_cov = new CPlot(tmpTStr,"ReconScale Covariance matrix AfterPost","","");
    pltReconScale_cov->setOutDir(resultDir);
    gPad->SetLogz();
    pltReconScale_cov->AddHist2D(SVD_Post.uRecoScaleCovMat,"COLZ",kWhite,kBlack);
    pltReconScale_cov->Draw(myCan,kTRUE,"png");
  }

  tmpTStr = "RecoSmearCovMat_cov_AfterPost"+BaseName;
  pltReconSmear_cov = new CPlot(tmpTStr,"ReconSmear Covariance matrix AfterPost","","");
  pltReconSmear_cov->setOutDir(resultDir);
  gPad->SetLogz();
  pltReconSmear_cov->AddHist2D(SVD_Post.uRecoSmearCovMat,"COLZ",kWhite,kBlack);
  pltReconSmear_cov->Draw(myCan,kTRUE,"png");
  
  tmpTStr = "RecoRecoilCovMat_cov_AfterPost"+BaseName;
  pltReconRecoil_cov = new CPlot(tmpTStr,"ReconRecoil Covariance matrix AfterPost","","");
  pltReconRecoil_cov->setOutDir(resultDir);
  gPad->SetLogz();
  pltReconRecoil_cov->AddHist2D(SVD_Post.uRecoRecoilCovMat,"COLZ",kWhite,kBlack);
  pltReconRecoil_cov->Draw(myCan,kTRUE,"png");
  
 // tmpTStr = "RecoLumiCovMat_cov_AfterPost"+BaseName; 
 // pltReconLumi_cov = new CPlot(tmpTStr,"ReconLumi Covariance matrix AfterPost","","");
 // pltReconLumi_cov->setOutDir(resultDir);
 // gPad->SetLogz();
 // pltReconLumi_cov->AddHist2D(SVD_Post.uRecoLumiCovMat,"COLZ",kWhite,kBlack);
 // pltReconLumi_cov->Draw(myCan,kTRUE,"png");
 
  //tmpTStr = "RecoFSRCovMat_cov_AfterPost"+BaseName;
  //pltReconFSR_cov = new CPlot(tmpTStr,"ReconFSR Covariance matrix AfterPost","","");
  //pltReconFSR_cov->setOutDir(resultDir);
  //gPad->SetLogz();
  //pltReconFSR_cov->AddHist2D(SVD_Post.uRecoFSRCovMat,"COLZ",kWhite,kBlack);
  //pltReconFSR_cov->Draw(myCan,kTRUE,"png");

  if(BaseName == "WpToMuNu" || BaseName == "WmToMuNu" ){
    tmpTStr = "RecoQCDRatioCovMat_cov_AfterPost"+BaseName;
    pltReconQCDRatio_cov = new CPlot(tmpTStr,"ReconQCDRatio Covariance matrix AfterPost","","");
    pltReconQCDRatio_cov->setOutDir(resultDir);
    gPad->SetLogz();
    pltReconQCDRatio_cov->AddHist2D(SVD_Post.uRecoQCDRatioCovMat,"COLZ",kWhite,kBlack);
    pltReconQCDRatio_cov->Draw(myCan,kTRUE,"png");
  }

  SVD_Post.uAdetCov = tsvdData->GetAdetCovMatrix( 1000);
  SVD_Post.uTotalCovMat->Add(SVD_Post.uAdetCov);

  SVD_Post.uTauCov = tsvdData->GetXtau();

// Total, TotalSyst, ResponseMatrix Systematic
  Fout << "SVD_Post.uTotalCovMat  -  Systematics; "<< endl;
  Fout << "Bin" << "\t" << "Wpt yield " << "\t\t" << "Cov_i_i" << "\t\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
  Fout << "==================================================================================================" << endl;
  for( int i(1);i<=SVD_Post.unfRes->GetNbinsX(); i++)
  {
    Fout << i << "\t" <<SVD_Post.unfRes->GetBinContent(i) << "\t\t" << SVD_Post.uTotalCovMat->GetBinContent(i,i) << "\t\t"<< TMath::Sqrt(SVD_Post.uTotalCovMat->GetBinContent(i,i)) << "\t\t" << TMath::Sqrt(SVD_Post.uTotalCovMat->GetBinContent(i,i))/SVD_Post.unfRes->GetBinContent(i)*100 << endl;
  }

  Fout << "SVD_Post.uTotalSystCov  -  Systematics; "<< endl;
  Fout << "Bin" << "\t" << "Wpt yield " << "\t\t" << "Cov_i_i" << "\t\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
  Fout << "==================================================================================================" << endl;
  for( int i(1);i<=SVD_Post.unfRes->GetNbinsX(); i++)
  {
    Fout << i << "\t" <<SVD_Post.unfRes->GetBinContent(i) << "\t\t" << SVD_Post.uTotalSystCov->GetBinContent(i,i) << "\t\t"<< TMath::Sqrt(SVD_Post.uTotalSystCov->GetBinContent(i,i)) << "\t\t" << TMath::Sqrt(SVD_Post.uTotalSystCov->GetBinContent(i,i))/SVD_Post.unfRes->GetBinContent(i)*100 << endl;
  }

  Fout << "SVD_Post.uAdetCov  -  Response Matrix Systematics; "<< endl;
  Fout << "Bin" << "\t" << "Wpt yield " << "\t\t" << "Cov_i_i" << "\t\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
  Fout << "==================================================================================================" << endl;
  for( int i(1);i<=SVD_Post.unfRes->GetNbinsX(); i++)
  {
    Fout << i << "\t" <<SVD_Post.unfRes->GetBinContent(i) << "\t\t" << SVD_Post.uAdetCov->GetBinContent(i,i) << "\t\t"<< TMath::Sqrt(SVD_Post.uAdetCov->GetBinContent(i,i)) << "\t\t" << TMath::Sqrt(SVD_Post.uAdetCov->GetBinContent(i,i))/SVD_Post.unfRes->GetBinContent(i)*100 << endl;
  }

  Fout << "SVD_Post.uTauCov Detector Unfolding "<< endl;
  Fout << "Bin" << "\t" << "Wpt yield " << "\t\t" << "Cov_i_i" << "\t\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
  Fout << "" << "\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t" << "" << endl;
  for( int i(1);i<=SVD_Post.unfRes->GetNbinsX(); i++)
  {
    Fout << i << "\t" <<SVD_Post.unfRes->GetBinContent(i) << "\t\t" << SVD_Post.uTauCov->GetBinContent(i,i) << "\t\t"<< TMath::Sqrt(SVD_Post.uTauCov->GetBinContent(i,i)) << "\t\t" << TMath::Sqrt(SVD_Post.uTauCov->GetBinContent(i,i))/SVD_Post.unfRes->GetBinContent(i)*100 << endl;
  }
  
  SVD_Post.uTauCov->Add( SVD_Post.uAdetCov);
  SVD_Post.uTauCov->Write(); 
  
  Fout << "SVD_Post.uTauCov->Add( SVD_Post.uAdetCov); "<< endl;
  Fout << "Bin" << "\t" << "Wpt yield " << "\t\t" << "Cov_i_i" << "\t\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
  Fout << "" << "\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t" << "" << endl;
  for( int i(1);i<=SVD_Post.unfRes->GetNbinsX(); i++)
  {
    Fout << i << "\t" <<SVD_Post.unfRes->GetBinContent(i) << "\t\t" << SVD_Post.uTauCov->GetBinContent(i,i) << "\t\t"<< TMath::Sqrt(SVD_Post.uTauCov->GetBinContent(i,i)) << "\t\t" << TMath::Sqrt(SVD_Post.uTauCov->GetBinContent(i,i))/SVD_Post.unfRes->GetBinContent(i)*100 << endl;
  }
  
  //SVD_Post.uTotalRecoCovMat->Add(SVD_Post.uRecoStatisticCovMat );
  SVD_Post.uTotalRecoCovMat->Add(SVD_Post.uRecoEffiCovMat );
  if(BaseName == "WpToEleNu" || BaseName == "WmToEleNu" )
    SVD_Post.uTotalRecoCovMat->Add(SVD_Post.uRecoScaleCovMat );
  SVD_Post.uTotalRecoCovMat->Add(SVD_Post.uRecoSmearCovMat );
  SVD_Post.uTotalRecoCovMat->Add(SVD_Post.uRecoRecoilCovMat );
  if(BaseName == "WpToMuNu" || BaseName == "WmToMuNu" )
    SVD_Post.uTotalRecoCovMat->Add(SVD_Post.uRecoQCDRatioCovMat);
 // SVD_Post.uTotalRecoCovMat->Add(SVD_Post.uRecoLumiCovMat );
  //SVD_Post.uTotalRecoCovMat->Add(SVD_Post.uRecoFSRCovMat );
  SVD_Post.uTotalRecoCovMat->Add(SVD_Post.uTauCov );
  
  SVD_Post.uTotalRecoCovMat->Write();

  Fout << "SVD_Post.uTotalRecoCovMat; "<< endl;
  Fout << "Bin" << "\t" << "Wpt yield " << "\t\t" << "Cov_i_i" << "\t\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
  Fout << "" << "\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t" << "" << endl;
  for( int i(1);i<=SVD_Post.unfRes->GetNbinsX(); i++)
  {
    Fout << i << "\t" <<SVD_Post.unfRes->GetBinContent(i) << "\t\t" << SVD_Post.uTotalRecoCovMat->GetBinContent(i,i) << "\t\t"<< TMath::Sqrt(SVD_Post.uTotalRecoCovMat->GetBinContent(i,i)) << "\t\t" << TMath::Sqrt(SVD_Post.uTotalRecoCovMat->GetBinContent(i,i))/SVD_Post.unfRes->GetBinContent(i)*100 << endl;
  }


//Starting of FSR Unfolding

  for( int i(1);i<=SVD_Post.unfRes->GetNbinsX(); i++)
  {
    SVD_Post.unfRes->SetBinError(i, TMath::Sqrt(SVD_Post.uTauCov->GetBinContent(i,i)));
  }
  
  //Make FSR Covariance Matrix from MC Eff
  for( int i(1); i<= SVD_Post.data->GetNbinsX(); i++)
  {
    for( int j(1); j<= SVD_Post.data->GetNbinsX(); j++)
    {
      SVD_Post.EffFSRCovMat->SetBinContent(i,j, SVD_Post.unfRes->GetBinContent(i)*SVD_Post.unfRes->GetBinContent(j)
	  *(h1_Post_BothOvTruth_weightFSR_eqBin->GetBinContent(i) - h1_Post_BothOvTruth_eqBin->GetBinContent(i))
	  *(h1_Post_BothOvTruth_weightFSR_eqBin->GetBinContent(j) - h1_Post_BothOvTruth_eqBin->GetBinContent(j)));
    }
  }
  
  SVD_Post.EffFSRCovMat->Write();

  //FSR Covariance Matrix
  tmpTStr = "EffFSRCovMat_"+BaseName;
  pltEffFSRCov = new CPlot(tmpTStr,"FSR Covariance Matrix from Event Efficiency","","");
  pltEffFSRCov -> setOutDir(resultDir);
  gPad->SetLogz(0);
  SVD_Post.EffFSRCovMat -> SetMarkerSize(0.8);
  pltEffFSRCov -> AddHist2D(SVD_Post.EffFSRCovMat,"COLTEXTZ",kWhite,kBlack);
  pltEffFSRCov -> Draw(myCan,kTRUE,"png");

  SVD_Post.EffCorr = (TH1D*)SVD_Post.unfRes->Clone("PostEffCorr");
  SVD_Post.EffCorr->Sumw2();
  SVD_Post.EffCorr->Multiply(h1_Post_BothOvTruth_eqBin);
 
  h1_Post_BothOvTruth_eqBin->Draw();
  myCan->SaveAs(resultDir+"/h1_Post_BothOvTruth_eqBin.png");

   for( int i(1); i<= SVD_Post.data->GetNbinsX(); i++)
   {
     SVD_Post.Eff_DetectUnfStatisticCovMat->SetBinContent(i,i, SVD_Post.EffCorr->GetBinError(i)*SVD_Post.EffCorr->GetBinError(i)   );
   }

  cout<<"Hallo" <<endl;
  for( int i(1); i<= SVD_Post.data->GetNbinsX(); i++)
   {
     for( int j(1); j<= SVD_Post.data->GetNbinsX(); j++)
     {
       SVD_Post.Eff_uRecoStatisticCovMat->SetBinContent(i,j, SVD_Post.uRecoStatisticCovMat->GetBinContent(i,j)*h1_Post_BothOvTruth_eqBin->GetBinContent(i)*h1_Post_BothOvTruth_eqBin->GetBinContent(j));
       SVD_Post.Eff_uRecoEffiCovMat->SetBinContent(i,j, SVD_Post.uRecoEffiCovMat->GetBinContent(i,j)*h1_Post_BothOvTruth_eqBin->GetBinContent(i)*h1_Post_BothOvTruth_eqBin->GetBinContent(j));
       if(BaseName == "WpToEleNu" || BaseName == "WmToEleNu" )
	 SVD_Post.Eff_uRecoScaleCovMat->SetBinContent(i,j, SVD_Post.uRecoScaleCovMat->GetBinContent(i,j)*h1_Post_BothOvTruth_eqBin->GetBinContent(i)*h1_Post_BothOvTruth_eqBin->GetBinContent(j));
       SVD_Post.Eff_uRecoSmearCovMat->SetBinContent(i,j, SVD_Post.uRecoSmearCovMat->GetBinContent(i,j)*h1_Post_BothOvTruth_eqBin->GetBinContent(i)*h1_Post_BothOvTruth_eqBin->GetBinContent(j));
       SVD_Post.Eff_uRecoRecoilCovMat->SetBinContent(i,j, SVD_Post.uRecoRecoilCovMat->GetBinContent(i,j)*h1_Post_BothOvTruth_eqBin->GetBinContent(i)*h1_Post_BothOvTruth_eqBin->GetBinContent(j));
       //SVD_Post.Eff_uRecoLumiCovMat->SetBinContent(i,j, SVD_Post.uRecoLumiCovMat->GetBinContent(i,j)*h1_Post_BothOvTruth_eqBin->GetBinContent(i)*h1_Post_BothOvTruth_eqBin->GetBinContent(j));
       //SVD_Post.Eff_uRecoFSRCovMat->SetBinContent(i,j, SVD_Post.uRecoFSRCovMat->GetBinContent(i,j)*h1_Post_BothOvTruth_eqBin->GetBinContent(i)*h1_Post_BothOvTruth_eqBin->GetBinContent(j));
       if(BaseName == "WpToMuNu" || BaseName == "WmToMuNu" )
	 SVD_Post.Eff_uRecoQCDRatioCovMat->SetBinContent(i,j, SVD_Post.uRecoQCDRatioCovMat->GetBinContent(i,j)*h1_Post_BothOvTruth_eqBin->GetBinContent(i)*h1_Post_BothOvTruth_eqBin->GetBinContent(j));
       SVD_Post.Eff_uTauCov->SetBinContent(i,j, SVD_Post.uTauCov->GetBinContent(i,j)*h1_Post_BothOvTruth_eqBin->GetBinContent(i)*h1_Post_BothOvTruth_eqBin->GetBinContent(j));
     
       SVD_Post.Eff_uTotalRecoCovMatEff->SetBinContent(i,j, SVD_Post.uTotalRecoCovMat->GetBinContent(i,j)*h1_Post_BothOvTruth_eqBin->GetBinContent(i)*h1_Post_BothOvTruth_eqBin->GetBinContent(j));

       SVD_Post.Eff_uRecoRespCovMat->SetBinContent(i,j, SVD_Post.uAdetCov->GetBinContent(i,j)*h1_Post_BothOvTruth_eqBin->GetBinContent(i)*h1_Post_BothOvTruth_eqBin->GetBinContent(j));
     }
   }
  
  Fout << "SVD_Post.uTauCov->Add( SVD_Post.uAdetCov); Eff applied"<< endl;
  Fout << "Bin" << "\t" << "Wpt yield " << "\t\t" << "Cov_i_i" << "\t\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
  Fout << "" << "\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t" << "" << endl;
  for( int i(1);i<=SVD_Post.unfRes->GetNbinsX(); i++)
  {
    Fout << i << "\t" <<SVD_Post.EffCorr->GetBinContent(i) << "\t\t" << SVD_Post.Eff_uTauCov->GetBinContent(i,i) << "\t\t"<< TMath::Sqrt(SVD_Post.Eff_uTauCov->GetBinContent(i,i)) << "\t\t" << TMath::Sqrt(SVD_Post.Eff_uTauCov->GetBinContent(i,i))/SVD_Post.EffCorr->GetBinContent(i)*100 << endl;
  }
  
  for( int i(1); i<= SVD_Post.data->GetNbinsX(); i++)
   {
     for( int j(1); j<= SVD_Post.data->GetNbinsX(); j++)
     {
       cout<<"SVD_Post.uRecoEffiCovMat_i_j Detectro Unfold Eff applied      :    "<<SVD_Post.Eff_uRecoEffiCovMat->GetBinContent(i,j)<<endl;
     }
   }

   for( int i(1); i<= SVD_Post.data->GetNbinsX(); i++)
   {
       cout<<"SVD_Post.Eff_uRecoEffiCovMat_i_i Detector Unfold Effi applied  :    "<<SVD_Post.Eff_uRecoEffiCovMat->GetBinContent(i,i)<<endl;
       cout<<"Square root ofSVD_Post.Eff_uRecoEffiCovMat_i_i                 :           "<<TMath::Sqrt(SVD_Post.Eff_uRecoEffiCovMat->GetBinContent(i,i))<<endl;
       cout<<"Systematics %                                                  :              "<<TMath::Sqrt(SVD_Post.Eff_uRecoEffiCovMat->GetBinContent(i,i))/SVD_Post.EffCorr->GetBinContent(i)*100<<endl;
   }
   
   for( int i(1); i<= SVD_Post.data->GetNbinsX(); i++)
   {
       cout<<"SVD_Post.EffCorr->GetBinContent(i)     :    "<<SVD_Post.EffCorr->GetBinContent(i)<<endl;
   }
   
   cout << "Bin" << "\t" << "Wpt yield " << "\t\t" << "Cov_i_i" << "\t\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
  cout << "" << "\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t" << "" << endl;
  for( int i(1);i<=SVD_Post.data->GetNbinsX(); i++)
  {
    cout << i << "\t" << SVD_Post.EffCorr->GetBinContent(i) << "\t\t" << SVD_Post.Eff_uRecoEffiCovMat->GetBinContent(i,i) << "\t\t"<< TMath::Sqrt(SVD_Post.Eff_uRecoEffiCovMat->GetBinContent(i,i)) << "\t\t" << TMath::Sqrt(SVD_Post.Eff_uRecoEffiCovMat->GetBinContent(i,i))/SVD_Post.EffCorr->GetBinContent(i)*100 << endl;
  }
  
  Fout << "Effi Detector Unfolding MCEventEff apply stage Syst"<< endl;
  Fout << "Bin" << "\t" << "Wpt yield " << "\t\t" << "Cov_i_i" << "\t\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
  Fout << "" << "\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t" << "" << endl;
  for( int i(1);i<=SVD_Post.EffCorr->GetNbinsX(); i++)
  {
    Fout << i << "\t" <<SVD_Post.EffCorr->GetBinContent(i) << "\t\t" << SVD_Post.Eff_uRecoEffiCovMat->GetBinContent(i,i) << "\t\t"<< TMath::Sqrt(SVD_Post.Eff_uRecoEffiCovMat->GetBinContent(i,i)) << "\t\t" << TMath::Sqrt(SVD_Post.Eff_uRecoEffiCovMat->GetBinContent(i,i))/SVD_Post.EffCorr->GetBinContent(i)*100 << endl;
  }
  
  if(BaseName == "WpToEleNu" || BaseName == "WmToEleNu" ){
    Fout << "Scale Detector Unfolding MCEventEff apply stage Syst"<< endl;
    Fout << "Bin" << "\t" << "Wpt yield " << "\t\t" << "Cov_i_i" << "\t\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
    Fout << "" << "\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t" << "" << endl;
    for( int i(1);i<=SVD_Post.EffCorr->GetNbinsX(); i++)
    {
      Fout << i << "\t" <<SVD_Post.EffCorr->GetBinContent(i) << "\t\t" << SVD_Post.Eff_uRecoScaleCovMat->GetBinContent(i,i) << "\t\t"<< TMath::Sqrt(SVD_Post.Eff_uRecoScaleCovMat->GetBinContent(i,i)) << "\t\t" << TMath::Sqrt(SVD_Post.Eff_uRecoScaleCovMat->GetBinContent(i,i))/SVD_Post.EffCorr->GetBinContent(i)*100 << endl;
    }
  }
  
  Fout << "Smear Detector Unfolding MCEventEff apply stage Syst"<< endl;
  Fout << "Bin" << "\t" << "Wpt yield " << "\t\t" << "Cov_i_i" << "\t\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
  Fout << "" << "\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t" << "" << endl;
  for( int i(1);i<=SVD_Post.EffCorr->GetNbinsX(); i++)
  {
    Fout << i << "\t" <<SVD_Post.EffCorr->GetBinContent(i) << "\t\t" << SVD_Post.Eff_uRecoSmearCovMat->GetBinContent(i,i) << "\t\t"<< TMath::Sqrt(SVD_Post.Eff_uRecoSmearCovMat->GetBinContent(i,i)) << "\t\t" << TMath::Sqrt(SVD_Post.Eff_uRecoSmearCovMat->GetBinContent(i,i))/SVD_Post.EffCorr->GetBinContent(i)*100 << endl;
  }

  Fout << "Recoil Detector Unfolding MCEventEff apply stage Syst"<< endl;
  Fout << "Bin" << "\t" << "Wpt yield " << "\t\t" << "Cov_i_i" << "\t\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
  Fout << "" << "\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t" << "" << endl;
  for( int i(1);i<=SVD_Post.EffCorr->GetNbinsX(); i++)
  {
    Fout << i << "\t" <<SVD_Post.EffCorr->GetBinContent(i) << "\t\t" << SVD_Post.Eff_uRecoRecoilCovMat->GetBinContent(i,i) << "\t\t"<< TMath::Sqrt(SVD_Post.Eff_uRecoRecoilCovMat->GetBinContent(i,i)) << "\t\t" << TMath::Sqrt(SVD_Post.Eff_uRecoRecoilCovMat->GetBinContent(i,i))/SVD_Post.EffCorr->GetBinContent(i)*100 << endl;
  }
  
 // Fout << "Lumi Detector Unfolding MCEventEff apply stage Syst"<< endl;
 // Fout << "Bin" << "\t" << "Wpt yield " << "\t\t" << "Cov_i_i" << "\t\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
 // Fout << "" << "\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t" << "" << endl;
 // for( int i(1);i<=SVD_Post.EffCorr->GetNbinsX(); i++)
 // {
 //   Fout << i << "\t" <<SVD_Post.EffCorr->GetBinContent(i) << "\t\t" << SVD_Post.Eff_uRecoLumiCovMat->GetBinContent(i,i) << "\t\t"<< TMath::Sqrt(SVD_Post.Eff_uRecoLumiCovMat->GetBinContent(i,i)) << "\t\t" << TMath::Sqrt(SVD_Post.Eff_uRecoLumiCovMat->GetBinContent(i,i))/SVD_Post.EffCorr->GetBinContent(i)*100 << endl;
 // }
  
  //Fout << "FSR Detector Unfolding MCEventEff apply stage Syst"<< endl;
  //Fout << "Bin" << "\t" << "Wpt yield " << "\t\t" << "Cov_i_i" << "\t\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
  //Fout << "" << "\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t" << "" << endl;
  //for( int i(1);i<=SVD_Post.EffCorr->GetNbinsX(); i++)
  //{
  //  Fout << i << "\t" <<SVD_Post.EffCorr->GetBinContent(i) << "\t\t" << SVD_Post.Eff_uRecoFSRCovMat->GetBinContent(i,i) << "\t\t"<< TMath::Sqrt(SVD_Post.Eff_uRecoFSRCovMat->GetBinContent(i,i)) << "\t\t" << TMath::Sqrt(SVD_Post.Eff_uRecoFSRCovMat->GetBinContent(i,i))/SVD_Post.EffCorr->GetBinContent(i)*100 << endl;
  //}
  
  if(BaseName == "WpToMuNu" || BaseName == "WmToMuNu" ){
    Fout << "QCDRatio Detector Unfolding MCEventEff apply stage"<< endl;
    Fout << "Bin" << "\t" << "Wpt yield " << "\t\t" << "Cov_i_i" << "\t\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
    Fout << "" << "\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t" << "" << endl;
    for( int i(1);i<=h1_Data_SigYild->GetNbinsX(); i++)
    {
      Fout << i << "\t" << SVD_Post.EffCorr->GetBinContent(i) << "\t\t" << SVD_Post.Eff_uRecoQCDRatioCovMat->GetBinContent(i,i) << "\t\t"<< TMath::Sqrt(SVD_Post.Eff_uRecoQCDRatioCovMat->GetBinContent(i,i)) << "\t\t" << TMath::Sqrt(SVD_Post.Eff_uRecoQCDRatioCovMat->GetBinContent(i,i))/SVD_Post.EffCorr->GetBinContent(i)*100 << endl;
    }
  } 
  Fout << "Statistic Detector Unfolding MCEventEff apply stage"<< endl;
  Fout << "Bin" << "\t" << "Wpt yield " << "\t\t" << "Cov_i_i" << "\t\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
  Fout << "" << "\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t" << "" << endl;
  for( int i(1);i<=h1_Data_SigYild->GetNbinsX(); i++)
  {
    Fout << i << "\t" << SVD_Post.EffCorr->GetBinContent(i) << "\t\t" << SVD_Post.Eff_uRecoStatisticCovMat->GetBinContent(i,i) << "\t\t"<< TMath::Sqrt(SVD_Post.Eff_uRecoStatisticCovMat->GetBinContent(i,i)) << "\t\t" << TMath::Sqrt(SVD_Post.Eff_uRecoStatisticCovMat->GetBinContent(i,i))/SVD_Post.EffCorr->GetBinContent(i)*100 << endl;
  }
  
  Fout << "SVD_Post.Eff_DetectUnfStatisticCovMat statistic SVD_Post.EffCorr->GetBinError(i)"<< endl;
  Fout << "Bin" << "\t" << "Wpt yield " << "\t\t" << "Cov_i_i" << "\t\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
  Fout << "" << "\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t" << "" << endl;
  for( int i(1);i<=h1_Data_SigYild->GetNbinsX(); i++)
  {
    Fout << i << "\t" << SVD_Post.EffCorr->GetBinContent(i) << "\t\t" << SVD_Post.Eff_DetectUnfStatisticCovMat->GetBinContent(i,i) << "\t\t"<< TMath::Sqrt(SVD_Post.Eff_DetectUnfStatisticCovMat->GetBinContent(i,i)) << "\t\t" << TMath::Sqrt(SVD_Post.Eff_DetectUnfStatisticCovMat->GetBinContent(i,i))/SVD_Post.EffCorr->GetBinContent(i)*100 << endl;
  }
  
  SVD_Post.Eff_uRecoStatisticCovMat->Write();
  SVD_Post.Eff_uRecoEffiCovMat->Write();
  if(BaseName == "WpToEleNu" || BaseName == "WmToEleNu" )
    SVD_Post.Eff_uRecoScaleCovMat->Write();
  SVD_Post.Eff_uRecoSmearCovMat->Write();
  SVD_Post.Eff_uRecoRecoilCovMat->Write();
  if(BaseName == "WpToMuNu" || BaseName == "WmToMuNu" )
    SVD_Post.Eff_uRecoQCDRatioCovMat->Write();
 //  SVD_Post.Eff_uRecoLumiCovMat->Write();
  //SVD_Post.Eff_uRecoFSRCovMat->Write();
  
  SVD_Post.Eff_DetectUnfStatisticCovMat->Write();
 
 //  SVD_Post.Eff_uTotalRecoCovMat->Add(SVD_Post.Eff_uRecoStatisticCovMat );
  //SVD_Post.Eff_uTotalRecoCovMat->Add(SVD_Post.Eff_DetectUnfStatisticCovMat );
 //  SVD_Post.Eff_uTotalRecoCovMat->Add(SVD_Post.Eff_uRecoEffiCovMat );
 //  SVD_Post.Eff_uTotalRecoCovMat->Add(SVD_Post.Eff_uRecoSmearCovMat );
 //  SVD_Post.Eff_uTotalRecoCovMat->Add(SVD_Post.Eff_uRecoRecoilCovMat );
 //  SVD_Post.Eff_uTotalRecoCovMat->Add(SVD_Post.Eff_uRecoFSRCovMat );
 //  SVD_Post.Eff_uTotalRecoCovMat->Add(SVD_Post.Eff_uTauCov );
  
  // SVD_Post.Eff_uTotalRecoCovMat->Add(SVD_Post.Eff_uRecoLumiCovMat );
  SVD_Post.Eff_uTotalRecoCovMat->Write();
  
  tmpTStr = "Post_Unf_"+BaseName;
  pltUnfPost = new CPlot(tmpTStr,"Detector Unfolding with SVD","W pT [GeV]","Event");
  pltUnfPost->setOutDir(resultDir);
  pltUnfPost->AddHist1D(SVD_Post.unfRes,"elp",kBlue,1,0,20,2);
  pltUnfPost->AddHist1D(SVD_Post.data,"elp",kRed,1,0,24,2);
  pltUnfPost->AddHist1D(SVD_Post.True,"hist",kBlack,1,0,0,0);
//  pltUnfPost->AddHist1D(SVD_Post.Gen,"hist",kGreen,1,0,0,0);
//  pltUnfPost->AddHist1D(SVD_Post.EffCorr,"elp",kGreen+2,0,0,26,2.0);
  
 // pltUnfPost->SetLegend(0.68,0.57,0.93,0.8);
  pltUnfPost->SetLegend(0.55,0.55,0.9,0.8);
  pltUnfPost->GetLegend()->AddEntry(SVD_Post.unfRes,"Unfolded","p");
  pltUnfPost->GetLegend()->AddEntry(SVD_Post.data,"Recon","p");
  //pltUnfPost->GetLegend()->AddEntry(SVD_Post.True,"Truth","l");
  //pltUnfPost->GetLegend()->AddEntry(SVD_Post.True,"Powheg Truth","l");
  pltUnfPost->GetLegend()->AddEntry(SVD_Post.True,"Powheg Pythia","l");
//  pltUnfPost->GetLegend()->AddEntry(SVD_Post.Gen,"Powheg Post","l");
//  pltUnfPost->GetLegend()->AddEntry(SVD_Post.EffCorr,"EffCorr","p");
  pltUnfPost->Draw(myCan,kTRUE,"png");
  //cout<<"LumiWeight_Muon_WpToMuNu_S8: "<<LumiWeight_Muon_WpToMuNu_S8<<endl;
  
  //tmpTStr = "Post_cov_"+BaseName;
  tmpTStr = "Post_uTotalCov_"+BaseName;
  pltUnfPost_uTotalCov = new CPlot(tmpTStr,"TSVDUnfold Total Covariance matrix","","");
  pltUnfPost_uTotalCov->setOutDir(resultDir);
  pltUnfPost_uTotalCov->AddHist2D(SVD_Post.uTotalCovMat,"COLZ",kWhite,kBlack);
  pltUnfPost_uTotalCov->Draw(myCan,kTRUE,"png");

  tmpTStr = "Post_uTotalSystCov_"+BaseName;
  pltUnfPost_uTotalSystCov = new CPlot(tmpTStr,"TSVDUnfold TotalSyst Covariance matrix","","");
  pltUnfPost_uTotalSystCov->setOutDir(resultDir);
  pltUnfPost_uTotalSystCov->AddHist2D(SVD_Post.uTotalSystCov,"COLZ",kWhite,kBlack);
  pltUnfPost_uTotalSystCov->Draw(myCan,kTRUE,"png");

  tmpTStr = "Post_uRespMatrix_"+BaseName;
  pltUnfPost_uRespMatrix = new CPlot(tmpTStr,"TSVDUnfold Response matrix","","");
  pltUnfPost_uRespMatrix->setOutDir(resultDir);
  pltUnfPost_uRespMatrix->AddHist2D(SVD_Post.uAdetCov,"COLZ",kWhite,kBlack);
  pltUnfPost_uRespMatrix->Draw(myCan,kTRUE,"png");

  tmpTStr = "Post_d_"+BaseName;
  pltUnfPost_d = new CPlot(tmpTStr,"TSVDUnfold |di|","i","|d_{i}|");
  pltUnfPost_d->setOutDir(resultDir);
  //gPad->SetLogx(1);
  pltUnfPost_d->SetLogy(1);
  pltUnfPost_d->AddHist1D(SVD_Post.dDist,"",kBlack,1,0,0,0);
  //pltUnfPost_d->AddLine(0,1,13,1,kBlack,1);
  pltUnfPost_d->AddLine(0,1,13,1,kRed,2);
  pltUnfPost_d->Draw(myCan,kTRUE,"png");
  //gPad->SetLogx(0);
  
  sprintf(tmpName,"h1_Post_BothFid");
  h1_Post_BothFidAccept     =(TH1D*)f_RecoAcceptCovMat->Get(tmpName)->Clone(tmpName);
  sprintf(tmpName,"h1_Post_BothFid");
  h1_Post_BothFidAcceptFSR     =(TH1D*)f_RecoAcceptFSRCovMat->Get(tmpName)->Clone(tmpName);

  for( int i(1); i<= SVD_Post.data->GetNbinsX(); i++)
  {
    cout<<"h1_Post_BothFidAccept   "<<h1_Post_BothFidAccept->GetBinContent(i)<<"   h1_Post_BothFidAcceptFSR   "<<h1_Post_BothFidAcceptFSR->GetBinContent(i)<< "    "<< h1_Post_BothFidAccept->GetBinContent(i)-h1_Post_BothFidAcceptFSR->GetBinContent(i)<<endl; 
  }
  
  for( int i(1); i<= SVD_Post.data->GetNbinsX(); i++)
  {
    for( int j(1); j<= SVD_Post.data->GetNbinsX(); j++)
    {
      SVD_Post.AcceptFSRCovMat->SetBinContent(i,j, (h1_Post_BothFidAccept->GetBinContent(i)-h1_Post_BothFidAcceptFSR->GetBinContent(i))*(h1_Post_BothFidAccept->GetBinContent(j)-h1_Post_BothFidAcceptFSR->GetBinContent(j))   );
    }
  }
  
//Input Cov Mat for FSR Unfolding  
  for( int i(1); i<= SVD_Post.data->GetNbinsX(); i++)
  {
    for( int j(1); j<= SVD_Post.data->GetNbinsX(); j++)
    {
      if (i==j)	SVD_Born.InputCovMat->SetBinContent(i,i, sqrt(SVD_Post.unfRes->GetBinContent(i)));
      else SVD_Born.InputCovMat->SetBinContent(i,j, 0.);
    }
  }
  
  SVD_Post.AcceptFSRCovMat->Write();
  
  //SVD_Born.InputCovMat->Add(SVD_Post.uTotalCovMat );
  SVD_Born.InputCovMat->Add(SVD_Post.EffFSRCovMat );

  //InputCovMat to FSR Unfolding
  tmpTStr = "InputCovMatToFSRUnf_"+BaseName;
  pltUnfBorn_InputCov = new CPlot(tmpTStr,"Input TotalCovMat to FSR Unfolding","","");
  pltUnfBorn_InputCov -> setOutDir(resultDir);
  gPad->SetLogz(0);
  SVD_Born.InputCovMat -> SetMarkerSize(0.8);
  pltUnfBorn_InputCov -> AddHist2D(SVD_Born.InputCovMat,"COLTEXTZ",kWhite,kBlack);
  pltUnfBorn_InputCov -> Draw(myCan,kTRUE,"png");

  //=================================================================
  //=================================================================
  // Unfolding from Post to Born          ===========================
  //=================================================================
  //=================================================================

  SVD_Born.data = (TH1D*)SVD_Post.EffCorr->Clone("BornData");
  SVD_Born.data->Sumw2();

 // TSVDUnfold *svdBorn = new TSVDUnfold(
 //     SVD_Born.data, SVD_Born.bini, SVD_Born.xini,SVD_Born.Adet);
  
  //TSVDUnfold *svdBorn = new TSVDUnfold(
  //    SVD_Born.data,SVD_Post.Eff_uRecoFSRCovMat, SVD_Born.bini, SVD_Born.xini,SVD_Born.Adet);
  
  //TSVDUnfold *svdBorn = new TSVDUnfold(
  //    SVD_Born.data,SVD_Post.Eff_uTotalRecoCovMat, SVD_Born.bini, SVD_Born.xini,SVD_Born.Adet);
  
  TSVDUnfold *svdBorn = new TSVDUnfold(
      SVD_Born.data,SVD_Born.InputCovMat, SVD_Born.bini, SVD_Born.xini,SVD_Born.Adet);
  
  //TSVDUnfold *svdBorn = new TSVDUnfold(
  //    SVD_Born.data,SVD_Post.Eff_uTauCov, SVD_Born.bini, SVD_Born.xini,SVD_Born.Adet);
  
  SVD_Born.statCov = svdBorn->GetBCov();
  svdBorn->SetNormalize( kFALSE );
  SVD_Born.unfRes = svdBorn->Unfold(4);
  //SVD_Born.unfRes = svdBorn->Unfold(5); //Wplus Ele
  //SVD_Born.unfRes = svdBorn->Unfold(7); //Wminus Ele
  SVD_Born.dDist = svdBorn->GetD();
  SVD_Born.svDist = svdBorn->GetSV();
  SVD_Born.uStatCov = svdBorn->GetUnfoldCovMatrix( SVD_Born.statCov, 1000);

  SVD_Born.uInputCovMat = svdBorn->GetUnfoldCovMatrix( SVD_Born.InputCovMat, 1000);
  
  SVD_Born.uRecoEffiCovMat = svdBorn->GetUnfoldCovMatrix( SVD_Post.Eff_uRecoEffiCovMat, 1000);
  //SVD_Born.uRecoEffiCovMat->Write();
  if(BaseName == "WpToEleNu" || BaseName == "WmToEleNu" )
    SVD_Born.uRecoScaleCovMat = svdBorn->GetUnfoldCovMatrix( SVD_Post.Eff_uRecoScaleCovMat, 1000);
  SVD_Born.uRecoSmearCovMat = svdBorn->GetUnfoldCovMatrix( SVD_Post.Eff_uRecoSmearCovMat, 1000);
  SVD_Born.uRecoRecoilCovMat = svdBorn->GetUnfoldCovMatrix( SVD_Post.Eff_uRecoRecoilCovMat, 1000);
 // SVD_Born.uRecoLumiCovMat = svdBorn->GetUnfoldCovMatrix( SVD_Post.Eff_uRecoLumiCovMat, 100);
  if(BaseName == "WpToMuNu" || BaseName == "WmToMuNu" )
    SVD_Born.uRecoQCDRatioCovMat = svdBorn->GetUnfoldCovMatrix( SVD_Post.Eff_uRecoQCDRatioCovMat, 1000);
  //SVD_Born.uRecoFSRCovMat = svdBorn->GetUnfoldCovMatrix( SVD_Post.Eff_uRecoFSRCovMat, 100);
  SVD_Born.uRecoFSRCovMat = svdBorn->GetUnfoldCovMatrix( SVD_Post.AcceptFSRCovMat, 1000);
  //SVD_Born.uRecoStatisticCovMat = svdBorn->GetUnfoldCovMatrix( SVD_Post.Eff_DetectUnfStatisticCovMat, 1000);
  SVD_Born.uRecoStatisticCovMat = svdBorn->GetUnfoldCovMatrix( SVD_Post.Eff_uRecoStatisticCovMat, 1000);
  //SVD_Born.uRecoStatisticCovMat = svdBorn->GetUnfoldCovMatrix( SVD_Post.RecoStatisticCovMat, 100);
  //SVD_Born.uRecoStatisticCovMat = svdBorn->GetUnfoldCovMatrix( SVD_Born.statCov, 100);
  SVD_Born.uRecoRespCovMat = svdBorn->GetUnfoldCovMatrix( SVD_Post.Eff_uRecoRespCovMat, 1000);

  //SVD_Born.uTotalCovMat->Add(SVD_Born.uInputCovMat );
  SVD_Born.uTotalCovMat->Add(SVD_Born.uRecoStatisticCovMat );
  SVD_Born.uTotalCovMat->Add(SVD_Born.uRecoEffiCovMat );
  if(BaseName == "WpToEleNu" || BaseName == "WmToEleNu" )
    SVD_Born.uTotalCovMat->Add(SVD_Born.uRecoScaleCovMat );
  SVD_Born.uTotalCovMat->Add(SVD_Born.uRecoSmearCovMat );
  SVD_Born.uTotalCovMat->Add(SVD_Born.uRecoRecoilCovMat );
  if(BaseName == "WpToMuNu" || BaseName == "WmToMuNu" )
    SVD_Born.uTotalCovMat->Add(SVD_Born.uRecoQCDRatioCovMat);
  SVD_Born.uTotalCovMat->Add(SVD_Born.uRecoRespCovMat);
  
  //SVD_Born.uTotalCovMat->Add(SVD_Born.uRecoFSRCovMat );


  //for( int i(1);i<=SVD_Born.unfRes->GetNbinsX(); i++)
  //{
  //  cout<<"SVD_Born.uStatCov_i_i         :   "<< i <<" "<<i<<"     "<<SVD_Born.uStatCov->GetBinContent(i,i)<<endl;
  //  cout<<"Square root of CovMatrix_i_i  :              "<<TMath::Sqrt(SVD_Born.uStatCov->GetBinContent(i,i))<<endl;
  //  cout<<"Unfold stage Systematics %    :                   "<<TMath::Sqrt(SVD_Born.uStatCov->GetBinContent(i,i))/SVD_Born.unfRes->GetBinContent(i)*100<<" % "<<endl;
  //}
  
  for( int i(1);i<=SVD_Born.unfRes->GetNbinsX(); i++)
  {
    cout<<"SVD_Born.uRecoEffiCovMat_i_i  :   "<< i <<" "<<i<<"     "<<SVD_Born.uRecoEffiCovMat->GetBinContent(i,i)<<endl;
    cout<<"Square root of CovMatrix_i_i  :              "<<TMath::Sqrt(SVD_Born.uRecoEffiCovMat->GetBinContent(i,i))<<endl;
    cout<<"Unfold stage Systematics %    :                   "<<TMath::Sqrt(SVD_Born.uRecoEffiCovMat->GetBinContent(i,i))/SVD_Born.unfRes->GetBinContent(i)*100<<" % "<<endl;
  }

  Fout << "Lepton Effi"<< endl;
  Fout << "Bin" << "\t" << "Wpt yield " << "\t\t" << "Cov_i_i" << "\t\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
  Fout << "" << "\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t" << "" << endl;
  
  for( int i(1);i<=SVD_Born.unfRes->GetNbinsX(); i++)
  {
    Fout << i << "\t" << SVD_Born.unfRes->GetBinContent(i) << "\t\t" << SVD_Born.uRecoEffiCovMat->GetBinContent(i,i) << "\t\t"<< TMath::Sqrt(SVD_Born.uRecoEffiCovMat->GetBinContent(i,i)) << "\t\t" << TMath::Sqrt(SVD_Born.uRecoEffiCovMat->GetBinContent(i,i))/SVD_Born.unfRes->GetBinContent(i)*100 << endl;
  }

  for( int i(1);i<=SVD_Born.unfRes->GetNbinsX(); i++)
  {
    cout<<"SVD_Born.unfRes->GetBinContent(i)  :   "<<SVD_Born.unfRes->GetBinContent(i)<<endl;
  }
  
  if(BaseName == "WpToEleNu" || BaseName == "WmToEleNu" ){
    Fout << "Scale after FSR Unf"<< endl;
    Fout << "Bin" << "\t" << "Wpt yield " << "\t\t" << "Cov_i_i" << "\t\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
    Fout << "" << "\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t" << "" << endl;
    for( int i(1);i<=SVD_Born.unfRes->GetNbinsX(); i++)
    {
      Fout << i << "\t" << SVD_Born.unfRes->GetBinContent(i) << "\t\t" << SVD_Born.uRecoScaleCovMat->GetBinContent(i,i) << "\t\t"<< TMath::Sqrt(SVD_Born.uRecoScaleCovMat->GetBinContent(i,i)) << "\t\t" << TMath::Sqrt(SVD_Born.uRecoScaleCovMat->GetBinContent(i,i))/SVD_Born.unfRes->GetBinContent(i)*100 << endl;
    }
  }

  Fout << "Smear MC"<< endl;
  Fout << "Bin" << "\t" << "Wpt yield " << "\t\t" << "Cov_i_i" << "\t\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
  Fout << "" << "\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t" << "" << endl;
  
  for( int i(1);i<=SVD_Born.unfRes->GetNbinsX(); i++)
  {
    Fout << i << "\t" << SVD_Born.unfRes->GetBinContent(i) << "\t\t" << SVD_Born.uRecoSmearCovMat->GetBinContent(i,i) << "\t\t"<< TMath::Sqrt(SVD_Born.uRecoSmearCovMat->GetBinContent(i,i)) << "\t\t" << TMath::Sqrt(SVD_Born.uRecoSmearCovMat->GetBinContent(i,i))/SVD_Born.unfRes->GetBinContent(i)*100 << endl;
  }

  Fout << "Recoil"<< endl;
  Fout << "Bin" << "\t" << "Wpt yield " << "\t\t" << "Cov_i_i" << "\t\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
  Fout << "" << "\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t" << "" << endl;
 
  for( int i(1);i<=SVD_Born.unfRes->GetNbinsX(); i++)
  {
    Fout << i << "\t" << SVD_Born.unfRes->GetBinContent(i) << "\t\t" << SVD_Born.uRecoRecoilCovMat->GetBinContent(i,i) << "\t\t"<< TMath::Sqrt(SVD_Born.uRecoRecoilCovMat->GetBinContent(i,i)) << "\t\t" << TMath::Sqrt(SVD_Born.uRecoRecoilCovMat->GetBinContent(i,i))/SVD_Born.unfRes->GetBinContent(i)*100 << endl;
  }

//  Fout << "Lumi"<< endl;
//  Fout << "Bin" << "\t" << "Wpt yield " << "\t\t" << "Cov_i_i" << "\t\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
//  Fout << "" << "\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t" << "" << endl;
//  for( int i(1);i<=SVD_Born.unfRes->GetNbinsX(); i++)
//  {
//    Fout << i << "\t" << SVD_Born.unfRes->GetBinContent(i) << "\t\t" << SVD_Born.uRecoLumiCovMat->GetBinContent(i,i) << "\t\t"<< TMath::Sqrt(SVD_Born.uRecoLumiCovMat->GetBinContent(i,i)) << "\t\t" << TMath::Sqrt(SVD_Born.uRecoLumiCovMat->GetBinContent(i,i))/SVD_Born.unfRes->GetBinContent(i)*100 << endl;
//  }

  Fout << "FSR"<< endl;
  Fout << "Bin" << "\t" << "Wpt yield " << "\t\t" << "Cov_i_i" << "\t\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
  Fout << "" << "\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t" << "" << endl;
  for( int i(1);i<=SVD_Born.unfRes->GetNbinsX(); i++)
  {
    Fout << i << "\t" << SVD_Born.unfRes->GetBinContent(i) << "\t\t" << SVD_Born.uRecoFSRCovMat->GetBinContent(i,i) << "\t\t"<< TMath::Sqrt(SVD_Born.uRecoFSRCovMat->GetBinContent(i,i)) << "\t\t" << TMath::Sqrt(SVD_Born.uRecoFSRCovMat->GetBinContent(i,i))/SVD_Born.unfRes->GetBinContent(i)*100 << endl;
  }

  Fout << "Statistic"<< endl;
  Fout << "Bin" << "\t" << "Wpt yield " << "\t\t" << "Cov_i_i" << "\t\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
  Fout << "" << "\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t" << "" << endl;
  for( int i(1);i<=SVD_Born.unfRes->GetNbinsX(); i++)
  {
    Fout << i << "\t" << SVD_Born.unfRes->GetBinContent(i) << "\t\t" << SVD_Born.uRecoStatisticCovMat->GetBinContent(i,i) << "\t\t"<< TMath::Sqrt(SVD_Born.uRecoStatisticCovMat->GetBinContent(i,i)) << "\t\t" << TMath::Sqrt(SVD_Born.uRecoStatisticCovMat->GetBinContent(i,i))/SVD_Born.unfRes->GetBinContent(i)*100 << endl;
  }


  if(BaseName == "WpToMuNu" || BaseName == "WmToMuNu" ){
    Fout << "QCDRatio after FSR unfolsing"<< endl;
    Fout << "Bin" << "\t" << "Wpt yield " << "\t\t" << "Cov_i_i" << "\t\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
    Fout << "" << "\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t" << "" << endl;
    for( int i(1);i<=SVD_Born.unfRes->GetNbinsX(); i++)
    {
      Fout << i << "\t" << SVD_Born.unfRes->GetBinContent(i) << "\t\t" << SVD_Born.uRecoQCDRatioCovMat->GetBinContent(i,i) << "\t\t"<< TMath::Sqrt(SVD_Born.uRecoQCDRatioCovMat->GetBinContent(i,i)) << "\t\t" << TMath::Sqrt(SVD_Born.uRecoQCDRatioCovMat->GetBinContent(i,i))/SVD_Born.unfRes->GetBinContent(i)*100 << endl;
    }
  }
  Fout << ""<< endl;
  Fout << ""<< endl;
  Fout << ""<< endl;
  Fout << "Systematics"<< endl;
//  Fout<<setw(20)<<setprecision(7)<<endl;
  if(BaseName == "WpToEleNu" || BaseName == "WmToEleNu" )
    Fout << "Bin" << "\t\t"<<"Statistic err"<<"\t\t" << "Lept Recon Effi Syst " << "\t\t"  << "\t\t" << "Smear Syst" << "\t\t" << "Recoil syst" <<  "\t\t" <<  "FSR Syst" << "\t\t" <<  "Scale Syst" <<endl;
  if(BaseName == "WpToMuNu" || BaseName == "WmToMuNu" )
    Fout << "Bin" << "\t\t"<<"Statistic err"<<"\t\t" << "Lept Recon Effi Syst " << "\t\t"  << "\t\t" << "Smear Syst" << "\t\t" << "Recoil syst" <<  "\t\t" <<  "FSR Syst" << "\t\t" <<  "QCDvsSignal Ratio Syst" <<endl;

  Fout << "" << "\t\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t\t" << "" << "\t\t" << "" << "\t\t" << "" << "\t\t" << "" << endl;
  if(BaseName == "WpToEleNu" || BaseName == "WmToEleNu" )
    for( int i(1);i<=SVD_Born.unfRes->GetNbinsX(); i++)
    {
      Fout << i << "\t\t" << TMath::Sqrt(SVD_Born.uRecoStatisticCovMat->GetBinContent(i,i))/SVD_Born.unfRes->GetBinContent(i)*100 << "\t\t" << TMath::Sqrt(SVD_Born.uRecoEffiCovMat->GetBinContent(i,i))/SVD_Born.unfRes->GetBinContent(i)*100 << "\t\t"<< TMath::Sqrt(SVD_Born.uRecoSmearCovMat->GetBinContent(i,i))/SVD_Born.unfRes->GetBinContent(i)*100 << "\t\t"<< TMath::Sqrt(SVD_Born.uRecoRecoilCovMat->GetBinContent(i,i))/SVD_Born.unfRes->GetBinContent(i)*100 << "\t\t" << "\t\t"<< TMath::Sqrt(SVD_Born.uRecoFSRCovMat->GetBinContent(i,i))/SVD_Born.unfRes->GetBinContent(i)*100 << TMath::Sqrt(SVD_Born.uRecoScaleCovMat->GetBinContent(i,i))/SVD_Born.unfRes->GetBinContent(i)*100 <<endl;
    }
  if(BaseName == "WpToMuNu" || BaseName == "WmToMuNu" )
    for( int i(1);i<=SVD_Born.unfRes->GetNbinsX(); i++)
    {
      Fout << i << "\t\t" << TMath::Sqrt(SVD_Born.uRecoStatisticCovMat->GetBinContent(i,i))/SVD_Born.unfRes->GetBinContent(i)*100 << "\t\t" << TMath::Sqrt(SVD_Born.uRecoEffiCovMat->GetBinContent(i,i))/SVD_Born.unfRes->GetBinContent(i)*100 << "\t\t"<< TMath::Sqrt(SVD_Born.uRecoSmearCovMat->GetBinContent(i,i))/SVD_Born.unfRes->GetBinContent(i)*100 << "\t\t"<< TMath::Sqrt(SVD_Born.uRecoRecoilCovMat->GetBinContent(i,i))/SVD_Born.unfRes->GetBinContent(i)*100 << "\t\t" << "\t\t"<< TMath::Sqrt(SVD_Born.uRecoFSRCovMat->GetBinContent(i,i))/SVD_Born.unfRes->GetBinContent(i)*100 << TMath::Sqrt(SVD_Born.uRecoQCDRatioCovMat->GetBinContent(i,i))/SVD_Born.unfRes->GetBinContent(i)*100 <<endl;
    }

  Fout << ""<< endl;
  Fout << ""<< endl;
  Fout << ""<< endl;
  Fout << "Systematics"<< endl;
  if(BaseName == "WpToEleNu" || BaseName == "WmToEleNu" )
    Fout << "Bin" << "\t\t"<<"Statistic err"<<"\t\t" << "Sqrt(LeptRecEff^2 +  Smear^2 +Recoil^2  +FSR^2+Scale^2) "<<endl;
  if(BaseName == "WpToMuNu" || BaseName == "WmToMuNu" )
    Fout << "Bin" << "\t\t"<<"Statistic err"<<"\t\t" << "Sqrt(LeptRecEff^2 +  Smear^2 +Recoil^2  +FSR^2+QCDvsSignalRatio^2) "<<endl;

  Fout << "" << "\t\t" << " " << "\t\t" << ""  << endl;
  if(BaseName == "WpToEleNu" || BaseName == "WmToEleNu" )
    for( int i(1);i<=SVD_Born.unfRes->GetNbinsX(); i++)
    {
      Fout << i << "\t\t" << TMath::Sqrt(SVD_Born.uRecoStatisticCovMat->GetBinContent(i,i))/SVD_Born.unfRes->GetBinContent(i)*100 << "\t\t" << TMath::Sqrt( TMath::Power(TMath::Sqrt(SVD_Born.uRecoEffiCovMat->GetBinContent(i,i)),2)+ TMath::Power( TMath::Sqrt(SVD_Born.uRecoSmearCovMat->GetBinContent(i,i)),2) + TMath::Power(TMath::Sqrt(SVD_Born.uRecoRecoilCovMat->GetBinContent(i,i)),2)+ TMath::Power( TMath::Sqrt(SVD_Born.uRecoFSRCovMat->GetBinContent(i,i)),2)+ TMath::Power( TMath::Sqrt(SVD_Born.uRecoScaleCovMat->GetBinContent(i,i)),2) )/SVD_Born.unfRes->GetBinContent(i)*100 <<endl;
    }
  if(BaseName == "WpToMuNu" || BaseName == "WmToMuNu" )
    for( int i(1);i<=SVD_Born.unfRes->GetNbinsX(); i++)
    {
      Fout << i << "\t\t" << TMath::Sqrt(SVD_Born.uRecoStatisticCovMat->GetBinContent(i,i))/SVD_Born.unfRes->GetBinContent(i)*100 << "\t\t" << TMath::Sqrt( TMath::Power(TMath::Sqrt(SVD_Born.uRecoEffiCovMat->GetBinContent(i,i)),2)+ TMath::Power( TMath::Sqrt(SVD_Born.uRecoSmearCovMat->GetBinContent(i,i)),2) + TMath::Power(TMath::Sqrt(SVD_Born.uRecoRecoilCovMat->GetBinContent(i,i)),2)+ TMath::Power( TMath::Sqrt(SVD_Born.uRecoFSRCovMat->GetBinContent(i,i)),2)+ TMath::Power( TMath::Sqrt(SVD_Born.uRecoQCDRatioCovMat->GetBinContent(i,i)),2) )/SVD_Born.unfRes->GetBinContent(i)*100 <<endl;
    }

  Fout << ""<< endl;
  Fout << ""<< endl;
  Fout << ""<< endl;
  Fout << "Systematics FSR stage yields as statistics"<< endl;
  if(BaseName == "WpToEleNu" || BaseName == "WmToEleNu" )
    Fout << "Bin" << "\t\t"<<"Statistic err"<<"\t\t" << "Sqrt(LeptRecEff^2 +  Smear^2 +Recoil^2 +FSR^2+Scale^2) "<<endl;
  if(BaseName == "WpToMuNu" || BaseName == "WmToMuNu" )
    Fout << "Bin" << "\t\t"<<"Statistic err"<<"\t\t" << "Sqrt(LeptRecEff^2 +  Smear^2 +Recoil^2 +FSR^2+QCDvsSignalRatio^2) "<<endl;

  Fout << "" << "\t\t" << " " << "\t\t" << ""  << endl;
  if(BaseName == "WpToEleNu" || BaseName == "WmToEleNu" )
    for( int i(1);i<=SVD_Born.unfRes->GetNbinsX(); i++)
    {
      Fout << i << "\t\t" << TMath::Sqrt(SVD_Born.unfRes->GetBinContent(i))/SVD_Born.unfRes->GetBinContent(i)*100 << "\t\t" << TMath::Sqrt( TMath::Power(TMath::Sqrt(SVD_Born.uRecoEffiCovMat->GetBinContent(i,i)),2)+ TMath::Power( TMath::Sqrt(SVD_Born.uRecoSmearCovMat->GetBinContent(i,i)),2) + TMath::Power(TMath::Sqrt(SVD_Born.uRecoRecoilCovMat->GetBinContent(i,i)),2)+  TMath::Power( TMath::Sqrt(SVD_Born.uRecoFSRCovMat->GetBinContent(i,i)),2) +  TMath::Power( TMath::Sqrt(SVD_Born.uRecoScaleCovMat->GetBinContent(i,i)),2))/SVD_Born.unfRes->GetBinContent(i)*100 <<endl;
    }
  if(BaseName == "WpToMuNu" || BaseName == "WmToMuNu" )
    for( int i(1);i<=SVD_Born.unfRes->GetNbinsX(); i++)
    {
      Fout << i << "\t\t" << TMath::Sqrt(SVD_Born.unfRes->GetBinContent(i))/SVD_Born.unfRes->GetBinContent(i)*100 << "\t\t" << TMath::Sqrt( TMath::Power(TMath::Sqrt(SVD_Born.uRecoEffiCovMat->GetBinContent(i,i)),2)+ TMath::Power( TMath::Sqrt(SVD_Born.uRecoSmearCovMat->GetBinContent(i,i)),2) + TMath::Power(TMath::Sqrt(SVD_Born.uRecoRecoilCovMat->GetBinContent(i,i)),2)+  TMath::Power( TMath::Sqrt(SVD_Born.uRecoFSRCovMat->GetBinContent(i,i)),2) +  TMath::Power( TMath::Sqrt(SVD_Born.uRecoQCDRatioCovMat->GetBinContent(i,i)),2))/SVD_Born.unfRes->GetBinContent(i)*100 <<endl;
    }
  
  Fout << ""<< endl;
  Fout << ""<< endl;
  Fout << ""<< endl;
  Fout << "Systematics Reco stage statistics"<< endl;
  if(BaseName == "WpToEleNu" || BaseName == "WmToEleNu" )
    Fout << "Bin" << "\t\t"<<"Statistic err"<<"\t\t" << "Sqrt(LeptRecEff^2 +  Smear^2 +Recoil^2 +FSR^2+Scale^2) "<<endl;
  if(BaseName == "WpToMuNu" || BaseName == "WmToMuNu" )
    Fout << "Bin" << "\t\t"<<"Statistic err"<<"\t\t" << "Sqrt(LeptRecEff^2 +  Smear^2 +Recoil^2 +FSR^2+QCDvsSignalRatio^2) "<<endl;

  Fout << "" << "\t\t" << " " << "\t\t" << ""  << endl;
  if(BaseName == "WpToEleNu" || BaseName == "WmToEleNu" )
    for( int i(1);i<=SVD_Born.unfRes->GetNbinsX(); i++)
    {
      Fout << i << "\t\t" << TMath::Sqrt(h1_Data_SigYild->GetBinContent(i))/h1_Data_SigYild->GetBinContent(i)*100 << "\t\t" << TMath::Sqrt( TMath::Power(TMath::Sqrt(SVD_Born.uRecoEffiCovMat->GetBinContent(i,i)),2)+ TMath::Power( TMath::Sqrt(SVD_Born.uRecoSmearCovMat->GetBinContent(i,i)),2) + TMath::Power(TMath::Sqrt(SVD_Born.uRecoRecoilCovMat->GetBinContent(i,i)),2)+ TMath::Power( TMath::Sqrt(SVD_Born.uRecoFSRCovMat->GetBinContent(i,i)),2)+ TMath::Power( TMath::Sqrt(SVD_Born.uRecoScaleCovMat->GetBinContent(i,i)),2) )/SVD_Born.unfRes->GetBinContent(i)*100 <<endl;
    }
  if(BaseName == "WpToMuNu" || BaseName == "WmToMuNu" )
    for( int i(1);i<=SVD_Born.unfRes->GetNbinsX(); i++)
    {
      Fout << i << "\t\t" << TMath::Sqrt(h1_Data_SigYild->GetBinContent(i))/h1_Data_SigYild->GetBinContent(i)*100 << "\t\t" << TMath::Sqrt( TMath::Power(TMath::Sqrt(SVD_Born.uRecoEffiCovMat->GetBinContent(i,i)),2)+ TMath::Power( TMath::Sqrt(SVD_Born.uRecoSmearCovMat->GetBinContent(i,i)),2) + TMath::Power(TMath::Sqrt(SVD_Born.uRecoRecoilCovMat->GetBinContent(i,i)),2)+ TMath::Power( TMath::Sqrt(SVD_Born.uRecoFSRCovMat->GetBinContent(i,i)),2)+ TMath::Power( TMath::Sqrt(SVD_Born.uRecoQCDRatioCovMat->GetBinContent(i,i)),2) )/SVD_Born.unfRes->GetBinContent(i)*100 <<endl;
    }
  
  Fout << ""<< endl;
  Fout << ""<< endl;
  Fout << ""<< endl;
  Fout << "Systematics Reco BinError/Yield as statistics"<< endl;
  if(BaseName == "WpToEleNu" || BaseName == "WmToEleNu" )
    Fout << "Bin" << "\t\t"<<"Statistic err"<<"\t\t" << "Sqrt(LeptRecEff^2 + Smear^2 +Recoil^2 +FSR^2+Scale^2) "<<endl;
  if(BaseName == "WpToMuNu" || BaseName == "WmToMuNu" )
    Fout << "Bin" << "\t\t"<<"Statistic err"<<"\t\t" << "Sqrt(LeptRecEff^2 + Smear^2 +Recoil^2 +FSR^2+QCDvsSignalRatio^2) "<<endl;

  Fout << "" << "\t\t" << " " << "\t\t" << ""  << endl;
  if(BaseName == "WpToEleNu" || BaseName == "WmToEleNu" )
    for( int i(1);i<=SVD_Born.unfRes->GetNbinsX(); i++)
    {
      Fout << i << "\t\t" << h1_Data_SigYild->GetBinError(i)/h1_Data_SigYild->GetBinContent(i)*100 << "\t\t" << TMath::Sqrt( TMath::Power(TMath::Sqrt(SVD_Born.uRecoEffiCovMat->GetBinContent(i,i)),2)+ TMath::Power( TMath::Sqrt(SVD_Born.uRecoSmearCovMat->GetBinContent(i,i)),2) + TMath::Power(TMath::Sqrt(SVD_Born.uRecoRecoilCovMat->GetBinContent(i,i)),2)+  TMath::Power( TMath::Sqrt(SVD_Born.uRecoFSRCovMat->GetBinContent(i,i)),2) +  TMath::Power( TMath::Sqrt(SVD_Born.uRecoScaleCovMat->GetBinContent(i,i)),2))/SVD_Born.unfRes->GetBinContent(i)*100 <<endl;
    }
  if(BaseName == "WpToMuNu" || BaseName == "WmToMuNu" )
    for( int i(1);i<=SVD_Born.unfRes->GetNbinsX(); i++)
    {
      Fout << i << "\t\t" << h1_Data_SigYild->GetBinError(i)/h1_Data_SigYild->GetBinContent(i)*100 << "\t\t" << TMath::Sqrt( TMath::Power(TMath::Sqrt(SVD_Born.uRecoEffiCovMat->GetBinContent(i,i)),2)+ TMath::Power( TMath::Sqrt(SVD_Born.uRecoSmearCovMat->GetBinContent(i,i)),2) + TMath::Power(TMath::Sqrt(SVD_Born.uRecoRecoilCovMat->GetBinContent(i,i)),2)+  TMath::Power( TMath::Sqrt(SVD_Born.uRecoFSRCovMat->GetBinContent(i,i)),2) +  TMath::Power( TMath::Sqrt(SVD_Born.uRecoQCDRatioCovMat->GetBinContent(i,i)),2))/SVD_Born.unfRes->GetBinContent(i)*100 <<endl;
    }
  
  SVD_Born.uAdetCov = svdBorn->GetAdetCovMatrix( 1000);
  SVD_Born.uStatCov->Add(SVD_Born.uAdetCov);

  SVD_Born.uTotalCovMat->Add(SVD_Born.uAdetCov);

  SVD_Born.uTauCov = svdBorn->GetXtau();
  SVD_Born.uTauCov->Add( SVD_Born.uAdetCov);

  //TotalCovMat after FSR Unfolding
  tmpTStr = "uTotalAfterFSRCovMat_"+BaseName;
  pltUnfBorn_uTotalCov = new CPlot(tmpTStr,"TotalCovMat after FSR Unfolding","","");
  pltUnfBorn_uTotalCov -> setOutDir(resultDir);
  gPad->SetLogz(0);
  SVD_Born.uTotalCovMat -> SetMarkerSize(0.8);
  pltUnfBorn_uTotalCov -> AddHist2D(SVD_Born.uTotalCovMat,"COLTEXTZ",kWhite,kBlack);
  pltUnfBorn_uTotalCov -> Draw(myCan,kTRUE,"png");

  //InputCovMat after FSR Unfolding
  tmpTStr = "uInputCovMat_"+BaseName;
  plt_uInputCovMat = new CPlot(tmpTStr,"InputCovMat after FSR Unfolding","","");
  plt_uInputCovMat -> setOutDir(resultDir);
  gPad->SetLogz(0);
  SVD_Born.uInputCovMat -> SetMarkerSize(0.8);
  plt_uInputCovMat -> AddHist2D(SVD_Born.uInputCovMat,"COLTEXTZ",kWhite,kBlack);
  plt_uInputCovMat -> Draw(myCan,kTRUE,"png");

//Abs Corr Cov Matrix = Propagated (Stat + Syst + ResponseMatrix) +ResponseMatrix(FSR_Unf)
  for( int i(1); i<= SVD_Post.data->GetNbinsX(); i++)
  {
    for( int j(1); j<= SVD_Post.data->GetNbinsX(); j++)
    {
      SVD_Born.AbsNormCorrErr->SetBinContent(i,j, 100*sqrt(fabs(SVD_Born.uTotalCovMat->GetBinContent(i,j))/(SVD_Born.unfRes->GetBinContent(i)*SVD_Born.unfRes->GetBinContent(j))));
    }
  }

//Absolute Normalized correlated error matrix 
  tmpTStr = "uAbsNormCorrErrMat_FSR_Unf_"+BaseName;
  pltUnfBorn_AbsNormCorrErr = new CPlot(tmpTStr,"FSR_Unf Absolute Normalized correlated error matrix","","");
  pltUnfBorn_AbsNormCorrErr -> setOutDir(resultDir);
  gPad->SetLogz(0);
  SVD_Born.AbsNormCorrErr -> SetMarkerSize(0.8);
  pltUnfBorn_AbsNormCorrErr->AddHist2D(SVD_Born.AbsNormCorrErr,"COLTEXTZ",kWhite,kBlack);
  //pltUnfBorn_AbsNormCorrErr->AddHist2D(SVD_Born.AbsNormCorrErr,"COLZ",kWhite,kBlack);
  pltUnfBorn_AbsNormCorrErr->Draw(myCan,kTRUE,"png");

  Fout << "SVD_Born.uTotalCovMat"<< endl;
  Fout << "Bin" << "\t" << "Wpt yield " << "\t\t" << "Cov_i_i" << "\t\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
  Fout << "" << "\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t" << "" << endl;
  for( int i(1);i<=SVD_Born.unfRes->GetNbinsX(); i++)
  {
    Fout << i << "\t" << SVD_Born.unfRes->GetBinContent(i) << "\t\t" << SVD_Born.uTotalCovMat->GetBinContent(i,i) << "\t\t"<< TMath::Sqrt(SVD_Born.uTotalCovMat->GetBinContent(i,i)) << "\t\t" << TMath::Sqrt(SVD_Born.uTotalCovMat->GetBinContent(i,i))/SVD_Born.unfRes->GetBinContent(i)*100 << endl;
  }
  
  Fout << "SVD_Born.uTauCov"<< endl;
  Fout << "Bin" << "\t" << "Wpt yield " << "\t\t" << "Cov_i_i" << "\t\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
  Fout << "" << "\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t" << "" << endl;
  
  for( int i(1);i<=SVD_Born.unfRes->GetNbinsX(); i++)
  {
    Fout << i << "\t" << SVD_Born.unfRes->GetBinContent(i) << "\t\t" << SVD_Born.uTauCov->GetBinContent(i,i) << "\t\t"<< TMath::Sqrt(SVD_Born.uTauCov->GetBinContent(i,i)) << "\t\t" << TMath::Sqrt(SVD_Born.uTauCov->GetBinContent(i,i))/SVD_Born.unfRes->GetBinContent(i)*100 << endl;
  }
  
  //SVD_Born.uTotalCovMat->Add(SVD_Born.uTauCov );
  Fout << "SVD_Born.uTotalCovMat + SVD_Born.uTauCov->Add( SVD_Born.uAdetCov);"<< endl;
  Fout << "Bin" << "\t" << "Wpt yield " << "\t\t" << "Cov_i_i" << "\t\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
  Fout << "" << "\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t" << "" << endl;
  
  for( int i(1);i<=SVD_Born.unfRes->GetNbinsX(); i++)
  {
    Fout << i << "\t" << SVD_Born.unfRes->GetBinContent(i) << "\t\t" << SVD_Born.uTotalCovMat->GetBinContent(i,i) << "\t\t"<< TMath::Sqrt(SVD_Born.uTotalCovMat->GetBinContent(i,i)) << "\t\t" << TMath::Sqrt(SVD_Born.uTotalCovMat->GetBinContent(i,i))/SVD_Born.unfRes->GetBinContent(i)*100 << endl;
  }
  
  for( int i(1);i<=SVD_Born.unfRes->GetNbinsX(); i++)
  {
    SVD_Born.unfRes->SetBinError(i, TMath::Sqrt(SVD_Born.uTauCov->GetBinContent(i,i)));
  }

  SVD_Born.EffCorr = (TH1D*)SVD_Born.unfRes->Clone("BornEffCorr");
  
  for( int i(1);i<=SVD_Born.unfRes->GetNbinsX(); i++)
  {
    //SVD_Born.EffCorr->SetBinError(i, TMath::Sqrt(SVD_Born.uTotalCovMat->GetBinContent(i,i)));
  }
  //SVD_Born.EffCorr->Sumw2();
  
  h1_Born_BothOvBorn_eqBin->Sumw2();
  SVD_Born.EffCorr->Divide(h1_Born_BothOvBorn_eqBin);

  tmpTStr = "Born_Unf_"+BaseName;
  pltUnfBorn = new CPlot(tmpTStr,"Post to Born Unfolding with SVD","W pT [GeV]","Event");
  pltUnfBorn->setOutDir(resultDir);
  //pltUnfBorn->AddHist1D(SVD_Born.unfRes,"e",kBlue,1,0,20,2);
  //pltUnfBorn->AddHist1D(SVD_Born.data,"e",kRed,1,0,24,2);
  //pltUnfBorn->AddHist1D(SVD_Born.True,"hist",kBlack,1,0,0,0);
  pltUnfBorn->AddHist1D(SVD_Born.Gen,"hist",kRed,1,0,0,0);
  pltUnfBorn->AddHist1D(SVD_Born.EffCorr,"elp",kBlue,0,0,20,2);
  //pltUnfBorn->SetLegend(0.68,0.57,0.93,0.8);
  pltUnfBorn->SetLegend(0.48,0.77,0.87,0.9);
  //pltUnfBorn->GetLegend()->AddEntry(SVD_Born.unfRes,"Unfolded","p");
  //pltUnfBorn->GetLegend()->AddEntry(SVD_Born.unfRes,"Unfolded to Both fiducial","p");
  //pltUnfBorn->GetLegend()->AddEntry(SVD_Born.data,"Post","p");
  //pltUnfBorn->GetLegend()->AddEntry(SVD_Born.True,"Born Target","l");
  //pltUnfBorn->GetLegend()->AddEntry(SVD_Born.True,"Born in the Both fiducial","l");
  //pltUnfBorn->GetLegend()->AddEntry(SVD_Born.Gen,"Born Gen","l");
  pltUnfBorn->GetLegend()->AddEntry(SVD_Born.Gen,"PowHeg CT10 Pythia Z2*","l");
  pltUnfBorn->GetLegend()->AddEntry(SVD_Born.EffCorr,"Unfolded","p");
  pltUnfBorn->Draw(myCan,kTRUE,"png");

  tmpTStr = "Born_cov_"+BaseName;
  pltUnfBorn_cov = new CPlot(tmpTStr,"TSVDUnfold Covariance matrix","","");
  pltUnfBorn_cov->setOutDir(resultDir);
  //pltUnfBorn_cov->AddHist2D(SVD_Post.uStatCov,"COLZ",kWhite,kBlack);
  pltUnfBorn_cov->AddHist2D(SVD_Born.uStatCov,"COLZ",kWhite,kBlack);
  pltUnfBorn_cov->Draw(myCan,kTRUE,"png");

  tmpTStr = "Born_d_"+BaseName;
  pltUnfBorn_d = new CPlot(tmpTStr,"TSVDUnfold |di|","i","|d_{i}|");
  pltUnfBorn_d->setOutDir(resultDir);
  pltUnfBorn_d->SetLogy(1);
  pltUnfBorn_d->AddHist1D(SVD_Born.dDist,"",kBlack,1,0,0,0);
  //pltUnfBorn_d->AddLine(0,1,13,1,kBlack,1);
  pltUnfBorn_d->AddLine(0,1,13,1,kRed,2);
  pltUnfBorn_d->Draw(myCan,kTRUE,"png");

  ////Systematic in %
 // for( int i(1);i<=SVD_Born.unfRes->GetNbinsX(); i++)
 // {
   // cout<<SVD_Born.EffCorr->GetBinContent(i) <<endl;
   // cout<<TMath::Sqrt(SVD_Born.uStatCov->GetBinContent(i,i)) /SVD_Born.EffCorr->GetBinContent(i)*100 <<endl;
 // }

  // Write to root file
  SVD_Post.data->Write();
//  sprintf(tmpName,"h1_SVD_Post_data_%d",k);
//  h1_SVD_Post_data[k] = (TH1D*)SVD_Post.data->Clone(tmpName);
//  h1_SVD_Post_data[k]->Sumw2();
//  h1_SVD_Post_data[k]->Write();

  SVD_Born.EffCorr->Write();
//  sprintf(tmpName,"h1_SVD_Born_EffCorr_%d",k);
//  h1_SVD_Born_EffCorr[k] = (TH1D*)SVD_Born.EffCorr->Clone(tmpName);
//  h1_SVD_Born_EffCorr[k]->Sumw2();
//  h1_SVD_Born_EffCorr[k]->Write();

  SVD_Born.Gen->Write();
//  sprintf(tmpName,"h1_SVD_Born_Gen_%d",k);
//  h1_SVD_Born_Gen[k] = (TH1D*)SVD_Born.Gen->Clone(tmpName);
//  h1_SVD_Born_Gen[k]->Sumw2();
//  h1_SVD_Born_Gen[k]->Write();

  SVD_Post.True->Write();
//  sprintf(tmpName,"h1_SVD_Post_True_%d",k);
//  h1_SVD_Post_True[k] = (TH1D*)SVD_Post.True->Clone(tmpName);
//  h1_SVD_Post_True[k]->Sumw2();
//  h1_SVD_Post_True[k]->Write();


  SVD_Post.unfRes->Write();
//  sprintf(tmpName,"h1_SVD_Post_unfRes_%d",k);
//  h1_SVD_Post_unfRes[k] = (TH1D*)SVD_Post.unfRes->Clone(tmpName);
//  h1_SVD_Post_unfRes[k]->Sumw2();
//  h1_SVD_Post_unfRes[k]->Write();

  SVD_Post.Gen->Write();
//  sprintf(tmpName,"h1_SVD_Post_Gen_%d",k);
//  h1_SVD_Post_Gen[k] = (TH1D*)SVD_Post.Gen->Clone(tmpName);
//  h1_SVD_Post_Gen[k]->Sumw2();
//  h1_SVD_Post_Gen[k]->Write();
  return 0;
}
