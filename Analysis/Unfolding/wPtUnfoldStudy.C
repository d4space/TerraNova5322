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

TH1D* makeDiffHist(TH1D* hData, TH1D* hPowheg, const TString name);

int wPtUnfoldStudy
(TString UnfoldFile,TString AcceptFile,TString DataFile,TString BaseName)
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
    TH1D *DetUnf;
    TH1D *FSRUnf;
    TH2D *uTotalCovMat;
    TH2D *uTotalSystCov;
    TH2D *uStatCov;
    TH2D *uTauCov;
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
    TH2D *MCEventEffFSRCovMat; //Make FSR Covariance Matrix from MC Eff.
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
  double errPowheg[NWptBinPlus]={0.};
  
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
  SVD_Post.data = new TH1D("data_Rec","data_Rec"    ,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Post.DetUnf = new TH1D("DetUnf","dUnf data",13,Bins);
  SVD_Born.FSRUnf = new TH1D("FSRUnf","FSRUnf data",13,Bins);
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
  SVD_Post.MCEventEffFSRCovMat = new TH2D("SVD_Post.MCEventEffFSRCovMat","FSR CovMat from MC Eff h1_Post_BothOvTruth_weightFSR"
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
  SVD_Born.data = new TH1D("data_Born","data_Rec"    ,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Born.True = new TH1D("SVD_Born.True","Born.True",NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Born.Gen  = new TH1D("SVD_Born.Gen","Born.Gen",NWptBinPlus-1,0,NWptBinPlus-1);
  //SVD_Born.Gen=new TH1D("SVD_Born.Gen","Born.Gen",NWptBinPlus-1,0,NWptBinPlus-1);
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
  CPlot *pltDetUnfResMtrx;
  CPlot *pltFSRUnfResMtrx;
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
  

  CPlot *pltDetUnfChi;
  CPlot *pltDetUnfChiDiff;
  CPlot *pltFSRUnfChi;
  CPlot *pltFSRUnfChiDiff;
	
  TCanvas *myCan = MakeCanvas("myCan","myCan",900,800);

 TCanvas *lC0 = new TCanvas("Can","Can",900,1000); lC0->cd(); lC0->SetLogy();
 lC0->Divide(1,2,0,0);
 lC0->cd(1)->SetPad(0,0.35,0.95,1.0);
 lC0->cd(1)->SetTopMargin(0.1);
 lC0->cd(1)->SetBottomMargin(0.01);
 lC0->cd(1)->SetLeftMargin(0.15);
 lC0->cd(1)->SetRightMargin(0.07);
 lC0->cd(1)->SetTickx(1);
 lC0->cd(1)->SetTicky(1);
 lC0->cd(2)->SetPad(0,0,0.95,0.345);
 lC0->cd(2)->SetTopMargin(0.025);
 lC0->cd(2)->SetBottomMargin(0.3);
 lC0->cd(2)->SetLeftMargin(0.15);
 lC0->cd(2)->SetRightMargin(0.07);
 lC0->cd(2)->SetTickx(1);
 lC0->cd(2)->SetTicky(1);
 gStyle->SetLineWidth(2.);





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
  
  cout<<"Simulated event========================="<<endl;
  int nbins = h1_Truth_Rec->GetNbinsX();
  cout<<"Nsimul N of bins: "<<nbins<<endl;
  Fout<<"Nsimul N of bins: "<<nbins<<endl;
  double Nsimul = h1_Truth_Rec->Integral();
  cout<<"Total Events: "<<setw(20)<<setprecision(7)<<Nsimul<<endl;
  Fout<<"Total Events: "<<setw(20)<<setprecision(7)<<Nsimul<<endl;
  double NsimulEven = h1_Truth_Rec_Even->Integral();
  cout<<"NsimulEven: "<<setw(20)<<setprecision(7)<<NsimulEven<<endl;
  Fout<<"NsimulEven: "<<setw(20)<<setprecision(7)<<NsimulEven<<endl;
  double NsimulOdd = h1_Truth_Rec_Odd->Integral();
  cout<<"NsimulOdd: "<<setw(20)<<setprecision(7)<<NsimulOdd<<endl;
  Fout<<"NsimulOdd: "<<setw(20)<<setprecision(7)<<NsimulOdd<<endl;
  double NdetectorResponse = h2_Truth_Rec_AP_Post->Integral();
  double NdetectorResponseEffCorr = h2_Truth_Rec_AP_Post->Integral();
  cout<<"NdetectorResponse: "<<NdetectorResponse<<endl;
  cout<<"NdetectorResponseEffCorr: "<<NdetectorResponseEffCorr<<endl;
  Fout<<"NdetectorResponse: "<<NdetectorResponse<<endl;
  Fout<<"NdetectorResponseEffCorr: "<<NdetectorResponseEffCorr<<endl;
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
  Fout<<"Real Data: "<<RDNumb<<endl;
  for(int i(1);i<=h1_Data_SigYild->GetNbinsX();i++)
  {
    cout<<"Nominal: "<<h1_Data_SigYild->GetBinContent(i)<<"\t"<<h1_Data_SigYild->GetBinError(i)<<endl;
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
    h1_Born_BothOvBorn_eqBin -> SetBinContent(i,h1_Born_BothOvBorn->GetBinContent(i));
    h1_Born_BothOvBorn_eqBin -> SetBinError(i,h1_Born_BothOvBorn->GetBinError(i));

    //of_Post_WpT_PostFid<<h1_Post_WpT_PostFid->GetBinContent(i)<<endl;
    for( int j(1);j<=nbins;j++)//gen idx
    {
      if(i==5) checkNumber += h2_Truth_Rec_AP_Post->GetBinContent(i,j);
      //SVD_Post.Adet->SetBinContent(i,j,h2_Truth_Rec_AP_Post->GetBinContent(i,j));
      SVD_Post.Adet->SetBinContent(i,j,h2_Truth_Rec_AP_PostEffCorr->GetBinContent(i,j));
      SVD_Born.Adet->SetBinContent(i,j,h2_PostBorn_BothFid->GetBinContent(i,j));
      //Adet_Post->SetBinError(i,j,h2_Truth_Rec_AP_Post->GetBinError(i,j));
    }
  }
  Fout<<"xini, bini in Detector Unfolding"<<endl;
  for(int i(1);i<=h1_Data_SigYild->GetNbinsX();i++)
  {
    Fout<<i<<"\t"<<SVD_Post.xini->GetBinContent(i)<<"\t"<<SVD_Post.bini->GetBinContent(i)<<endl;
  }
  
  //cout<<"check the number 5th bin(h1,response) "<<h1_Truth_Rec->GetBinContent(5)<<" "<<checkNumber<<endl;
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
    for( int j(1); j<= SVD_Post.data->GetNbinsX(); j++)
    {
      if (i==j)
	//SVD_Post.RecoStatisticCovMat->SetBinContent(i,i, h1_Data_SigYild->GetBinError(i)*h1_Data_SigYild->GetBinError(i));
	SVD_Post.RecoStatisticCovMat->SetBinContent(i,i, h1_Data_SigYild->GetBinContent(i));
      else
	SVD_Post.RecoStatisticCovMat->SetBinContent(i,j, 0.,0. );
    }
  }
  
  SVD_Post.RecoEffiCovMat =(TH2D*)f_RecoEffiCovMat->Get("h2_RecoEffiCovMat")->Clone();
  SVD_Post.RecoSmearCovMat =(TH2D*)f_RecoSmearCovMat->Get("h2_RecoSmearCovMat")->Clone();
  SVD_Post.RecoRecoilCovMat =(TH2D*)f_RecoRecoilCovMat->Get("h2_RecoRecoilCovMat")->Clone();
  cout<<"hallo I am here"<<endl; 
  if(BaseName == "WpToMuNu" || BaseName == "WmToMuNu" )
    SVD_Post.RecoQCDRatioCovMat =(TH2D*)f_RecoQCDRatioCovMat->Get("h2_RecoQCDRatioCovMat")->Clone();
  if(BaseName == "WpToEleNu" || BaseName == "WmToEleNu" )
    SVD_Post.RecoScaleCovMat =(TH2D*)f_RecoScaleCovMat->Get("h2_RecoScaleCovMat")->Clone();
  
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

//Detector Unf. Response Matrix
  Unfolder DetUnfold("Post");
  DetUnfold.setTrue(h1_Truth_Post); //dumy for set up the bin ranges
  DetUnfold.setMeas(h1_Data_SigYild);
  DetUnfold.colNormalize(h2_Truth_Rec_AP_PostEffCorr);
  DetUnfold.setMigrationMatrix(h2_Truth_Rec_AP_PostEffCorr);
  DetUnfold.unfold();

  h2_Truth_Rec_AP_PostEffCorr->GetYaxis()->SetMoreLogLabels();
  h2_Truth_Rec_AP_PostEffCorr->GetYaxis()->SetNoExponent();
  h2_Truth_Rec_AP_PostEffCorr->GetXaxis()->SetTitleSize(0.03);
  h2_Truth_Rec_AP_PostEffCorr->GetXaxis()->SetLabelSize(0.03);
  h2_Truth_Rec_AP_PostEffCorr->GetXaxis()->SetTitleOffset(1.6);
  h2_Truth_Rec_AP_PostEffCorr->GetYaxis()->SetTitleSize(0.03);
  h2_Truth_Rec_AP_PostEffCorr->GetYaxis()->SetLabelSize(0.03);
  h2_Truth_Rec_AP_PostEffCorr->GetYaxis()->SetTitleOffset(1.8);
  h2_Truth_Rec_AP_PostEffCorr->GetXaxis()->SetMoreLogLabels();
  h2_Truth_Rec_AP_PostEffCorr->GetXaxis()->SetNoExponent();

  gStyle->SetPaintTextFormat("3.2f"); 
  tmpTStr = "dUnfResponseMatrix_"+BaseName;
  pltDetUnfResMtrx = new CPlot(tmpTStr,"","Rec W p_{T} [GeV]","Post W p_{T} [GeV]");
  pltDetUnfResMtrx->setOutDir(resultDir);
  pltDetUnfResMtrx->AddHist2D(h2_Truth_Rec_AP_PostEffCorr,"COLTEXTZ",kWhite,kBlack);
  pltDetUnfResMtrx->SetLogx();
  pltDetUnfResMtrx->SetLogy();
  h2_Truth_Rec_AP_PostEffCorr->SetMarkerSize(0.8);
  pltDetUnfResMtrx-> Draw(myCan,kTRUE,"png");

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
    pltRecoScaleCov->AddHist2D(SVD_Post.RecoScaleCovMat,"COLZ",kWhite,kBlack);
    pltRecoScaleCov->Draw(myCan,kTRUE,"png");
  }

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
  
  if(BaseName == "WpToMuNu" || BaseName == "WmToMuNu" )
    Fout << "Bin" << "\t\t"<<"Statistic err"<<"\t\t" << "Lept Recon Effi Syst " << "\t\t" <<  "Smear Syst" << "\t\t" << "Recoil syst" <<  "\t\t" << "QCDvsSignalRaio Syst" <<endl;
  else if(BaseName == "WpToEleNu" || BaseName == "WmToEleNu" )
    Fout << "Bin" << "\t\t"<<"Statistic err"<<"\t\t" << "Lept Recon Effi Syst " << "\t\t" <<  "Smear Syst" << "\t\t" << "Recoil syst" <<  "\t\t" <<  "Scale Syst" <<endl;
  
  Fout << "" << "\t\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t\t" << "" << "\t\t" << "" << "\t\t" << "" << "\t\t" << "" << endl;
  if(BaseName == "WpToMuNu" || BaseName == "WmToMuNu" )
    for( int i(1);i<=h1_Data_SigYild->GetNbinsX(); i++)
    {
      Fout << i << "\t\t" << TMath::Sqrt(SVD_Post.RecoStatisticCovMat->GetBinContent(i,i))/h1_Data_SigYild->GetBinContent(i)*100 << "\t\t" << TMath::Sqrt(SVD_Post.RecoEffiCovMat->GetBinContent(i,i))/h1_Data_SigYild->GetBinContent(i)*100 << "\t\t"<< TMath::Sqrt(SVD_Post.RecoSmearCovMat->GetBinContent(i,i))/h1_Data_SigYild->GetBinContent(i)*100 << "\t\t"<< TMath::Sqrt(SVD_Post.RecoRecoilCovMat->GetBinContent(i,i))/h1_Data_SigYild->GetBinContent(i)*100 << "\t\t" << TMath::Sqrt(SVD_Post.RecoQCDRatioCovMat->GetBinContent(i,i))/h1_Data_SigYild->GetBinContent(i)*100 << endl;
    }
  else if(BaseName == "WpToEleNu" || BaseName == "WmToEleNu" )
    for( int i(1);i<=h1_Data_SigYild->GetNbinsX(); i++)
    {
      Fout << i << "\t\t" << TMath::Sqrt(SVD_Post.RecoStatisticCovMat->GetBinContent(i,i))/h1_Data_SigYild->GetBinContent(i)*100 << "\t\t" << TMath::Sqrt(SVD_Post.RecoEffiCovMat->GetBinContent(i,i))/h1_Data_SigYild->GetBinContent(i)*100 << "\t\t"<< TMath::Sqrt(SVD_Post.RecoSmearCovMat->GetBinContent(i,i))/h1_Data_SigYild->GetBinContent(i)*100 << "\t\t"<< TMath::Sqrt(SVD_Post.RecoRecoilCovMat->GetBinContent(i,i))/h1_Data_SigYild->GetBinContent(i)*100 << "\t\t" << TMath::Sqrt(SVD_Post.RecoScaleCovMat->GetBinContent(i,i))/h1_Data_SigYild->GetBinContent(i)*100 << endl;
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
      TotalStat[i]=100*TMath::Sqrt( TMath::Power(TMath::Sqrt(SVD_Post.RecoEffiCovMat->GetBinContent(i,i)),2)+ TMath::Power( TMath::Sqrt(SVD_Post.RecoSmearCovMat->GetBinContent(i,i)),2) + TMath::Power(TMath::Sqrt(SVD_Post.RecoRecoilCovMat->GetBinContent(i,i)),2)+ TMath::Power( TMath::Sqrt(SVD_Post.RecoQCDRatioCovMat->GetBinContent(i,i)),2))/h1_Data_SigYild->GetBinContent(i);
      Fout<<TotalStat[i]<<endl;
    }
  else if(BaseName == "WpToEleNu" || BaseName == "WmToEleNu" )
    for( int i(1);i<=h1_Data_SigYild->GetNbinsX(); i++)
    {
      TotalStat[i]=100*TMath::Sqrt( TMath::Power(TMath::Sqrt(SVD_Post.RecoEffiCovMat->GetBinContent(i,i)),2)+ TMath::Power( TMath::Sqrt(SVD_Post.RecoSmearCovMat->GetBinContent(i,i)),2) + TMath::Power(TMath::Sqrt(SVD_Post.RecoRecoilCovMat->GetBinContent(i,i)),2)+ TMath::Power( TMath::Sqrt(SVD_Post.RecoScaleCovMat->GetBinContent(i,i)),2))/h1_Data_SigYild->GetBinContent(i);
      Fout<<TotalStat[i]<<endl;
    }
  
  Fout <<"Unfolding response Matrices"<<endl;
  Fout <<"Bin\t dUnf\t FSR Unf"<<endl;
  for( int i(1);i<=h1_Data_SigYild->GetNbinsX(); i++)
  {
    for( int j(1);j<=h1_Data_SigYild->GetNbinsX(); j++)
    {
      Fout<<i<<" "<<j<<"\t"<<SVD_Post.Adet->GetBinContent(i,j)<<"\t"<<SVD_Born.Adet->GetBinContent(i,j)<<endl;
    }
  }
  
  Fout <<"bini and xini in Unfolding"<<endl;
  Fout <<"Bin\t dUnf bini\t dUnf xini\t FSR Unf bini\t FSR Unf xini"<<endl;
  for( int i(1);i<=h1_Data_SigYild->GetNbinsX(); i++)
  {
    Fout<<i<<"\t"<<SVD_Post.bini->GetBinContent(i)<<"\t"<<SVD_Post.xini->GetBinContent(i)<<"\t"<<SVD_Born.bini->GetBinContent(i)<<"\t"<<SVD_Born.xini->GetBinContent(i)<<endl;
  }

  //SVD_Post.RecoStatisticCovMat->Write();
  //SVD_Post.RecoScaleCovMat->Write();
  //SVD_Post.RecoEffiCovMat->Write();
  //SVD_Post.RecoSmearCovMat->Write();
  //SVD_Post.RecoRecoilCovMat->Write();
  //SVD_Post.RecoLumiCovMat->Write();


  SVD_Post.TotalRecoCovMat->Add(SVD_Post.RecoStatisticCovMat );
  SVD_Post.TotalRecoCovMat->Add(SVD_Post.RecoEffiCovMat );
  SVD_Post.TotalRecoCovMat->Add(SVD_Post.RecoSmearCovMat );
  SVD_Post.TotalRecoCovMat->Add(SVD_Post.RecoRecoilCovMat );
  //SVD_Post.TotalRecoCovMat->Add(SVD_Post.RecoQCDRatioCovMat);
  if(BaseName == "WpToEleNu" || BaseName == "WmToEleNu" )
    SVD_Post.TotalRecoCovMat->Add(SVD_Post.RecoScaleCovMat );

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


  cout<<"SVD_Post.xini:  Total Number of post distr  :   h1_Truth_Post -->   "<<SVD_Post.xini->Integral()<<endl;
  cout<<"SVD_Post.bini:  Total Number of recon distr :   h1_Truth_Rec  -->   "<<SVD_Post.bini->Integral()<<endl;

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
  //SVD_Post.unfRes = tsvdData->Unfold(3); 
  //SVD_Post.unfRes = tsvdData->Unfold(5); 
  //SVD_Post.unfRes = tsvdData->Unfold(6); 
  //SVD_Post.unfRes = tsvdData->Unfold(7); 
  //SVD_Post.unfRes = tsvdData->Unfold(8); 
  //SVD_Post.unfRes = tsvdData->Unfold(9); 
  SVD_Post.dDist = tsvdData->GetD();
  SVD_Post.svDist = tsvdData->GetSV();
  
  for(int i(1);i<=h1_Data_SigYild->GetNbinsX();i++)
  {
    SVD_Post.DetUnf -> SetBinContent(i,SVD_Post.unfRes->GetBinContent(i));
  }
  //SVD_Post.DetUnf = (TH1D*)SVD_Post.unfRes->Clone("DetUnf");
  //SVD_Post.DetUnf -> Sumw2();

  SVD_Post.uStatCov = tsvdData->GetUnfoldCovMatrix( SVD_Post.RecoStatisticCovMat, 1000);
  //SVD_Post.uTotalCovMat = tsvdData->GetUnfoldCovMatrix( SVD_Post.RecoStatisticCovMat, 100);
  SVD_Post.uTotalCovMat = (TH2D*)SVD_Post.uStatCov->Clone("uTotalCovMat");
  
  
  SVD_Post.uRecoEffiCovMat = tsvdData->GetUnfoldCovMatrix( SVD_Post.RecoEffiCovMat, 1000);
  if(BaseName == "WpToEleNu" || BaseName == "WmToEleNu" )
    SVD_Post.uRecoScaleCovMat = tsvdData->GetUnfoldCovMatrix( SVD_Post.RecoScaleCovMat, 1000);
  SVD_Post.uRecoSmearCovMat = tsvdData->GetUnfoldCovMatrix( SVD_Post.RecoSmearCovMat, 1000);
  SVD_Post.uRecoRecoilCovMat = tsvdData->GetUnfoldCovMatrix( SVD_Post.RecoRecoilCovMat, 1000);
  //SVD_Post.uRecoLumiCovMat = tsvdData->GetUnfoldCovMatrix( SVD_Post.RecoLumiCovMat, 100);
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
  pltUnfPost_AbsNormCorrErr = new CPlot(tmpTStr,"D_Unf Absolute Normalized Covariance error matrix","","");
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

   for( int i(1); i<= SVD_Post.data->GetNbinsX(); i++)
   {
       cout<<"SVD_Post.uStatCov_i_i  AfterPost     :    "<<SVD_Post.uStatCov->GetBinContent(i,i)<<endl;
       cout<<"Square root ofSVD_Post.uStatCov_i_i  :           "<<TMath::Sqrt(SVD_Post.uStatCov->GetBinContent(i,i))<<endl;
       cout<<"Systematics %                               :              "<<TMath::Sqrt(SVD_Post.uStatCov->GetBinContent(i,i))/SVD_Post.unfRes->GetBinContent(i)*100<<endl;
   }

   for( int i(1); i<= SVD_Post.data->GetNbinsX(); i++)
   {
       cout<<"SVD_Post.uRecoEffiCovMat_i_i  AfterPost     :    "<<SVD_Post.uRecoEffiCovMat->GetBinContent(i,i)<<endl;
       cout<<"Square root ofSVD_Post.uRecoEffiCovMat_i_i  :           "<<TMath::Sqrt(SVD_Post.uRecoEffiCovMat->GetBinContent(i,i))<<endl;
       cout<<"Systematics %                               :              "<<TMath::Sqrt(SVD_Post.uRecoEffiCovMat->GetBinContent(i,i))/SVD_Post.unfRes->GetBinContent(i)*100<<endl;
   }
   
   for( int i(1); i<= SVD_Post.data->GetNbinsX(); i++)
   {
       cout<<"SVD_Post.unfRes->GetBinContent(i) %         :    "<<SVD_Post.unfRes->GetBinContent(i)<<endl;
       
   }

   for( int i(1); i<= SVD_Post.data->GetNbinsX(); i++)
   {
     for( int j(1); j<= SVD_Post.data->GetNbinsX(); j++)
     {
       cout<<"SVD_Post.uRecoEffiCovMat_i_j  AfterPost     :    "<<SVD_Post.uRecoEffiCovMat->GetBinContent(i,j)<<endl;
     }
   }

  Fout << "Effi Detector Unfolding stage Syst"<< endl;
  Fout << "Bin" << "\t" << "Wpt yield " << "\t\t" << "Cov_i_i" << "\t\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
  Fout << "" << "\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t" << "" << endl;
  for( int i(1);i<=SVD_Post.unfRes->GetNbinsX(); i++)
  {
    Fout << i << "\t" <<SVD_Post.unfRes->GetBinContent(i) << "\t\t" << SVD_Post.uRecoEffiCovMat->GetBinContent(i,i) << "\t\t"<< TMath::Sqrt(SVD_Post.uRecoEffiCovMat->GetBinContent(i,i)) << "\t\t" << TMath::Sqrt(SVD_Post.uRecoEffiCovMat->GetBinContent(i,i))/SVD_Post.unfRes->GetBinContent(i)*100 << endl;
  }

  if(BaseName == "WpToEleNu" || BaseName == "WmToEleNu" ){
    Fout << "Scale Detector Unfolding stage Syst"<< endl;
    Fout << "Bin" << "\t" << "Wpt yield " << "\t" << "Cov_i_i" << "\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
    Fout << "=============================================================" << endl;
    for( int i(1);i<=SVD_Post.unfRes->GetNbinsX(); i++)
    {
      Fout << i << "\t" <<SVD_Post.unfRes->GetBinContent(i) << "\t" << SVD_Post.uRecoScaleCovMat->GetBinContent(i,i) << "\t"<< TMath::Sqrt(SVD_Post.uRecoScaleCovMat->GetBinContent(i,i)) << "\t" << TMath::Sqrt(SVD_Post.uRecoScaleCovMat->GetBinContent(i,i))/SVD_Post.unfRes->GetBinContent(i)*100 << endl;
    }
  }

  Fout << "Smear Detector Unfolding stage Syst"<< endl;
  Fout << "Bin" << "\t" << "Wpt yield " << "\t\t" << "Cov_i_i" << "\t\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
  Fout << "" << "\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t" << "" << endl;
  for( int i(1);i<=SVD_Post.unfRes->GetNbinsX(); i++)
  {
    Fout << i << "\t" <<SVD_Post.unfRes->GetBinContent(i) << "\t\t" << SVD_Post.uRecoSmearCovMat->GetBinContent(i,i) << "\t\t"<< TMath::Sqrt(SVD_Post.uRecoSmearCovMat->GetBinContent(i,i)) << "\t\t" << TMath::Sqrt(SVD_Post.uRecoSmearCovMat->GetBinContent(i,i))/SVD_Post.unfRes->GetBinContent(i)*100 << endl;
  }

  Fout << "Recoil Detector Unfolding stage Syst"<< endl;
  Fout << "Bin" << "\t" << "Wpt yield " << "\t\t" << "Cov_i_i" << "\t\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
  Fout << "" << "\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t" << "" << endl;
  for( int i(1);i<=SVD_Post.unfRes->GetNbinsX(); i++)
  {
    Fout << i << "\t" <<SVD_Post.unfRes->GetBinContent(i) << "\t\t" << SVD_Post.uRecoRecoilCovMat->GetBinContent(i,i) << "\t\t"<< TMath::Sqrt(SVD_Post.uRecoRecoilCovMat->GetBinContent(i,i)) << "\t\t" << TMath::Sqrt(SVD_Post.uRecoRecoilCovMat->GetBinContent(i,i))/SVD_Post.unfRes->GetBinContent(i)*100 << endl;
  }
  
 // Fout << "Lumi Detector Unfolding stage Syst"<< endl;
 // Fout << "Bin" << "\t" << "Wpt yield " << "\t\t" << "Cov_i_i" << "\t\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
 // Fout << "" << "\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t" << "" << endl;
 // for( int i(1);i<=SVD_Post.unfRes->GetNbinsX(); i++)
 // {
 //   Fout << i << "\t" <<SVD_Post.unfRes->GetBinContent(i) << "\t\t" << SVD_Post.uRecoLumiCovMat->GetBinContent(i,i) << "\t\t"<< TMath::Sqrt(SVD_Post.uRecoLumiCovMat->GetBinContent(i,i)) << "\t\t" << TMath::Sqrt(SVD_Post.uRecoLumiCovMat->GetBinContent(i,i))/SVD_Post.unfRes->GetBinContent(i)*100 << endl;
 // }
  
  if(BaseName == "WpToMuNu" || BaseName == "WmToMuNu" ){
    Fout << "QCDRatio Detector Unfolding stage"<< endl;
    Fout << "Bin" << "\t" << "Wpt yield " << "\t\t" << "Cov_i_i" << "\t\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
    Fout << "" << "\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t" << "" << endl;
    for( int i(1);i<=h1_Data_SigYild->GetNbinsX(); i++)
    {
      Fout << i << "\t" << SVD_Post.unfRes->GetBinContent(i) << "\t\t" << SVD_Post.uRecoQCDRatioCovMat->GetBinContent(i,i) << "\t\t"<< TMath::Sqrt(SVD_Post.uRecoQCDRatioCovMat->GetBinContent(i,i)) << "\t\t" << TMath::Sqrt(SVD_Post.uRecoQCDRatioCovMat->GetBinContent(i,i))/SVD_Post.unfRes->GetBinContent(i)*100 << endl;
    }
  }
  Fout << "Statistic Detector Unfolding stage"<< endl;
  Fout << "Bin" << "\t" << "Wpt yield " << "\t\t" << "Cov_i_i" << "\t\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
  Fout << "" << "\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t" << "" << endl;
  for( int i(1);i<=h1_Data_SigYild->GetNbinsX(); i++)
  {
    Fout << i << "\t" << SVD_Post.unfRes->GetBinContent(i) << "\t\t" << SVD_Post.uRecoStatisticCovMat->GetBinContent(i,i) << "\t\t"<< TMath::Sqrt(SVD_Post.uRecoStatisticCovMat->GetBinContent(i,i)) << "\t\t" << TMath::Sqrt(SVD_Post.uRecoStatisticCovMat->GetBinContent(i,i))/SVD_Post.unfRes->GetBinContent(i)*100 << endl;
  }
   
  Fout << "Stat+Syst+RespMatErr systematic after Detector Unfolding"<< endl;
  Fout << "Bin" << "\t" << "Wpt yield " << "\t\t" << "Cov_i_i" << "\t\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
  Fout << "" << "\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t" << "" << endl;
  for( int i(1);i<=h1_Data_SigYild->GetNbinsX(); i++)
  {
    Fout << i << "\t" << SVD_Post.unfRes->GetBinContent(i) << "\t\t" << SVD_Post.uTotalCovMat->GetBinContent(i,i) << "\t\t"<< TMath::Sqrt(SVD_Post.uTotalCovMat->GetBinContent(i,i)) << "\t\t" << TMath::Sqrt(SVD_Post.uTotalCovMat->GetBinContent(i,i))/SVD_Post.unfRes->GetBinContent(i)*100 << endl;
  }
  Fout << ""<< endl;
  Fout << ""<< endl;
  Fout << ""<< endl;
  Fout << "Systematics"<< endl;
    //Fout << "Bin" << "\t\t"<<"Statistic err"<<"\t\t" << "Lept Recon Effi Syst " << "\t\t" << "Scale Syst" << "\t\t" << "Smear Syst" << "\t\t" << "Recoil syst" << "\t\t" << "Lumi Syst" << "\t\t" << endl;
  if(BaseName == "WpToMuNu" || BaseName == "WmToMuNu" )
    Fout << "Bin" << "\t\t"<<"Statistic err"<<"\t\t" << "Lept Recon Effi Syst " << "\t\t" << "\t\t" << "Smear Syst" << "\t\t" << "Recoil syst" << "\t\t" << "QCDvsSignalRatio Syst" <<endl;
  else if(BaseName == "WpToEleNu" || BaseName == "WmToEleNu" )
    Fout << "Bin" << "\t\t"<<"Statistic err"<<"\t\t" << "Lept Recon Effi Syst " << "\t\t" << "\t\t" << "Smear Syst" << "\t\t" << "Recoil syst" << "\t\t" << "Scale Syst" <<endl;
  
  Fout << "" << "\t\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t\t" << "" << "\t\t" << "" << "\t\t" << "" << "\t\t" << "" << endl;
  if(BaseName == "WpToMuNu" || BaseName == "WmToMuNu" )
    for( int i(1);i<=h1_Data_SigYild->GetNbinsX(); i++)
    {
      Fout << i << "\t\t" << TMath::Sqrt(SVD_Post.uRecoStatisticCovMat->GetBinContent(i,i))/SVD_Post.unfRes->GetBinContent(i)*100 << "\t\t" << TMath::Sqrt(SVD_Post.uRecoEffiCovMat->GetBinContent(i,i))/SVD_Post.unfRes->GetBinContent(i)*100 << "\t\t"<< TMath::Sqrt(SVD_Post.uRecoSmearCovMat->GetBinContent(i,i))/SVD_Post.unfRes->GetBinContent(i)*100 << "\t\t"<< TMath::Sqrt(SVD_Post.uRecoRecoilCovMat->GetBinContent(i,i))/SVD_Post.unfRes->GetBinContent(i)*100 << "\t\t"<< TMath::Sqrt(SVD_Post.uRecoQCDRatioCovMat->GetBinContent(i,i))/SVD_Post.unfRes->GetBinContent(i)*100 <<endl;
    }
  if(BaseName == "WpToEleNu" || BaseName == "WmToEleNu" )
    for( int i(1);i<=h1_Data_SigYild->GetNbinsX(); i++)
    {
      Fout << i << "\t\t" << TMath::Sqrt(SVD_Post.uRecoStatisticCovMat->GetBinContent(i,i))/SVD_Post.unfRes->GetBinContent(i)*100 << "\t\t" << TMath::Sqrt(SVD_Post.uRecoEffiCovMat->GetBinContent(i,i))/SVD_Post.unfRes->GetBinContent(i)*100 << "\t\t"<< TMath::Sqrt(SVD_Post.uRecoSmearCovMat->GetBinContent(i,i))/SVD_Post.unfRes->GetBinContent(i)*100 << "\t\t"<< TMath::Sqrt(SVD_Post.uRecoRecoilCovMat->GetBinContent(i,i))/SVD_Post.unfRes->GetBinContent(i)*100 << "\t\t"<< TMath::Sqrt(SVD_Post.uRecoScaleCovMat->GetBinContent(i,i))/SVD_Post.unfRes->GetBinContent(i)*100 <<endl;
    }
  
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

  tmpTStr = "DUnf_ResponseMat_"+BaseName;
  plt_DUnf_RespCov = new CPlot(tmpTStr,"D_Unf Response CovMat Error Matrix","","");
  plt_DUnf_RespCov -> setOutDir(resultDir);
  gPad->SetLogz(0);
  SVD_Post.uAdetCov -> SetMarkerSize(0.8);
  plt_DUnf_RespCov->AddHist2D(SVD_Post.uAdetCov,"COLTEXTZ",kWhite,kBlack);
  plt_DUnf_RespCov-> Draw(myCan,kTRUE,"png");

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
    dUnf_SVD[NWptBinPlus-1]=TMath::Sqrt(SVD_Post.uAdetCov->GetBinContent(i,i))/SVD_Post.unfRes->GetBinContent(i)*100;
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
  
//  //Make FSR Covariance Matrix from MC Eff
//  for( int i(1); i<= SVD_Post.data->GetNbinsX(); i++)
//  {
//    for( int j(1); j<= SVD_Post.data->GetNbinsX(); j++)
//    {
//      SVD_Post.MCEventEffFSRCovMat->SetBinContent(i,j, SVD_Post.unfRes->GetBinContent(i)*SVD_Post.unfRes->GetBinContent(j)
//	  *(h1_Post_BothOvTruth_weightFSR_eqBin->GetBinContent(i) - h1_Post_BothOvTruth_eqBin->GetBinContent(i))
//	  *(h1_Post_BothOvTruth_weightFSR_eqBin->GetBinContent(j) - h1_Post_BothOvTruth_eqBin->GetBinContent(j)));
//    }
//  }
//  
//  SVD_Post.MCEventEffFSRCovMat->Write();
//
//  Fout << "FSR Syst "<< endl;
//  Fout << "Bin" << "\t" << "Wpt yield " << "\t\t" << "Cov_i_i" << "\t\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
//  Fout << "" << "\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t" << "" << endl;
//  for( int i(1);i<=h1_Data_SigYild->GetNbinsX(); i++)
//  {
//    Fout << i << "\t" << SVD_Post.unfRes->GetBinContent(i) << "\t\t" << SVD_Post.RecoStatisticCovMat->GetBinContent(i,i) << "\t\t"<< TMath::Sqrt(SVD_Post.unfRes->GetBinContent(i,i)) << "\t\t" << TMath::Sqrt(SVD_Post.MCEventEffFSRCovMat->GetBinContent(i,i))/SVD_Post.unfRes->GetBinContent(i)*100 << endl;
//  }
//
//  //FSR Covariance Matrix
//  tmpTStr = "EffFSRCovMat_"+BaseName;
//  pltEffFSRCov = new CPlot(tmpTStr,"FSR Covariance Matrix from Event Efficiency","","");
//  pltEffFSRCov -> setOutDir(resultDir);
//  gPad->SetLogz(0);
//  SVD_Post.MCEventEffFSRCovMat -> SetMarkerSize(0.8);
//  pltEffFSRCov -> AddHist2D(SVD_Post.MCEventEffFSRCovMat,"COLTEXTZ",kWhite,kBlack);
//  pltEffFSRCov -> Draw(myCan,kTRUE,"png");

  SVD_Post.EffCorr = (TH1D*)SVD_Post.unfRes->Clone("PostEffCorr");
  SVD_Post.EffCorr->Sumw2();
  SVD_Post.EffCorr->Multiply(h1_Post_BothOvTruth_eqBin);

  Fout<<"Yields after Detector Unfolding (dUnf, MC efficiency and MC event SF correction)"<<endl;
  for( int i(1); i<= SVD_Post.data->GetNbinsX(); i++)
  {    
    Fout<<i<<"\t"<<SVD_Post.DetUnf->GetBinContent(i)<<"\t"<<h1_Post_BothOvTruth_eqBin->GetBinContent(i)<<"\t"<<SVD_Post.EffCorr->GetBinContent(i)<<endl;
  }

  //Make FSR Covariance Matrix from MC Eff
  for( int i(1); i<= SVD_Post.data->GetNbinsX(); i++)
  {
    for( int j(1); j<= SVD_Post.data->GetNbinsX(); j++)
    {
      if (i==j) SVD_Post.MCEventEffFSRCovMat->SetBinContent(i,i, SVD_Post.EffCorr->GetBinContent(i));
      else SVD_Post.MCEventEffFSRCovMat->SetBinContent(i,j, 0.);

    }
  }
  
  SVD_Post.MCEventEffFSRCovMat->Write();

  Fout << "FSR Syst "<< endl;
  Fout << "Bin" << "\t" << "Wpt yield " << "\t\t" << "Cov_i_i" << "\t\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
  Fout << "" << "\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t" << "" << endl;
  for( int i(1);i<=h1_Data_SigYild->GetNbinsX(); i++)
  {
    Fout << i << "\t" << SVD_Post.unfRes->GetBinContent(i) << "\t\t" << SVD_Post.RecoStatisticCovMat->GetBinContent(i,i) << "\t\t"<< TMath::Sqrt(SVD_Post.unfRes->GetBinContent(i,i)) << "\t\t" << TMath::Sqrt(SVD_Post.MCEventEffFSRCovMat->GetBinContent(i,i))/SVD_Post.unfRes->GetBinContent(i)*100 << endl;
  }

  //FSR Covariance Matrix
  tmpTStr = "EffFSRCovMat_"+BaseName;
  pltEffFSRCov = new CPlot(tmpTStr,"FSR Covariance Matrix from Event Efficiency","","");
  pltEffFSRCov -> setOutDir(resultDir);
  gPad->SetLogz(0);
  SVD_Post.MCEventEffFSRCovMat -> SetMarkerSize(0.8);
  pltEffFSRCov -> AddHist2D(SVD_Post.MCEventEffFSRCovMat,"COLTEXTZ",kWhite,kBlack);
  pltEffFSRCov -> Draw(myCan,kTRUE,"png");



//Compare MC EffCorrected D_Unf Result to Post_BothFid  
  tmpTStr = "MCEffcorr_SVD_Unf_"+BaseName;
  pltSVD_EffCorr = new CPlot(tmpTStr,"","W pT [GeV]","Event");
  pltSVD_EffCorr->setOutDir(resultDir);
  pltSVD_EffCorr->AddHist1D(SVD_Post.EffCorr,"elp",kRed,0,0,20,2.0);
  //pltSVD_EffCorr->AddHist1D(SVD_Born.bini,"hist",kBlack,1,0,0,0);
  pltSVD_EffCorr->AddHist1D(SVD_Post.Gen,"hist",kBlack,1,0,0,0);
  pltSVD_EffCorr->SetLegend(0.63,0.62,0.88,0.8);
  pltSVD_EffCorr->GetLegend()->AddEntry(SVD_Post.EffCorr,"EffCorr Unfolded","p");
  //pltSVD_EffCorr->GetLegend()->AddEntry(SVD_Born.bini,"Post_BothFid","l");
  pltSVD_EffCorr->GetLegend()->AddEntry(SVD_Post.Gen,"Post_BothFid","l");
  pltSVD_EffCorr->Draw(myCan,kTRUE,"png");
	    
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
       //SVD_Post.Eff_uMCEventEffFSRCovMat->SetBinContent(i,j, SVD_Post.MCEventEffFSRCovMat->GetBinContent(i,j)*h1_Post_BothOvTruth_eqBin->GetBinContent(i)*h1_Post_BothOvTruth_eqBin->GetBinContent(j));
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
  //  Fout << i << "\t" <<SVD_Post.EffCorr->GetBinContent(i) << "\t\t" << SVD_Post.Eff_uMCEventEffFSRCovMat->GetBinContent(i,i) << "\t\t"<< TMath::Sqrt(SVD_Post.Eff_uMCEventEffFSRCovMat->GetBinContent(i,i)) << "\t\t" << TMath::Sqrt(SVD_Post.Eff_uMCEventEffFSRCovMat->GetBinContent(i,i))/SVD_Post.EffCorr->GetBinContent(i)*100 << endl;
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
  
  for( int ipt(1);ipt<=h1_Post_BothOvTruth->GetNbinsX(); ipt++)
  {
    Fout <<ipt<<"\t"<<100*(h1_Post_BothOvTruth_weightFSR->GetBinContent(ipt) - h1_Post_BothOvTruth->GetBinContent(ipt))/h1_Post_BothOvTruth->GetBinContent(ipt)<<endl;
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
  //SVD_Post.Eff_uMCEventEffFSRCovMat->Write();
  
  SVD_Post.Eff_DetectUnfStatisticCovMat->Write();
 
 //  SVD_Post.Eff_uTotalRecoCovMat->Add(SVD_Post.Eff_uRecoStatisticCovMat );
  //SVD_Post.Eff_uTotalRecoCovMat->Add(SVD_Post.Eff_DetectUnfStatisticCovMat );
 //  SVD_Post.Eff_uTotalRecoCovMat->Add(SVD_Post.Eff_uRecoEffiCovMat );
 //  SVD_Post.Eff_uTotalRecoCovMat->Add(SVD_Post.Eff_uRecoSmearCovMat );
 //  SVD_Post.Eff_uTotalRecoCovMat->Add(SVD_Post.Eff_uRecoRecoilCovMat );
 //  SVD_Post.Eff_uTotalRecoCovMat->Add(SVD_Post.Eff_uMCEventEffFSRCovMat );
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
  
  

  TH1D* drawDifferenceUnfPost;
  drawDifferenceUnfPost = makeDiffHist(SVD_Post.unfRes,SVD_Post.True,"drawDifferenceUnfPost");
  drawDifferenceUnfPost->SetMarkerStyle(kFullCircle);
  drawDifferenceUnfPost->SetMarkerSize(0.9);
  SVD_Post.unfRes->GetXaxis()->SetLabelSize(0.0);

  tmpTStr = "Det_Unf_Chi"+BaseName;
  pltDetUnfChi = new CPlot(tmpTStr,"Detector Unfolding with SVD","W pT [Bins]","Event");
  pltDetUnfChi->setOutDir(resultDir);
  pltDetUnfChi->AddHist1D(SVD_Post.unfRes,"elp",kBlue,1,0,20,2);
  pltDetUnfChi->AddHist1D(SVD_Post.data,"elp",kRed,1,0,24,2);
  pltDetUnfChi->AddHist1D(SVD_Post.True,"hist",kBlack,1,0,0,0);
 // pltDetUnfChi->AddHist1D(SVD_Post.Gen,"hist",kGreen,1,0,0,0);
 // pltDetUnfChi->AddHist1D(SVD_Post.EffCorr,"elp",kGreen+2,0,0,26,2.0);
 // pltDetUnfChi->SetLegend(0.68,0.57,0.93,0.8);
  pltDetUnfChi->SetLegend(0.55,0.55,0.9,0.8);
  pltDetUnfChi->GetLegend()->AddEntry(SVD_Post.unfRes,"Unfolded","p");
  pltDetUnfChi->GetLegend()->AddEntry(SVD_Post.data,"Recon","p");
  pltDetUnfChi->GetLegend()->AddEntry(SVD_Post.True,"Powheg Pythia","l");
 // pltDetUnfChi->GetLegend()->AddEntry(SVD_Post.Gen,"Powheg Post","l");
 // pltDetUnfChi->GetLegend()->AddEntry(SVD_Post.EffCorr,"EffCorr","p");
  pltDetUnfChi->Draw(lC0,kTRUE,"png",1);
 
  tmpTStr = "Det_Unf_Chi_Diff_"+BaseName;
  pltDetUnfChiDiff = new CPlot(tmpTStr,"","W p_{T} [Bins]","Unfolded/Powheg Pythia");
  pltDetUnfChiDiff->setOutDir(resultDir);
  pltDetUnfChiDiff->AddHist1D(drawDifferenceUnfPost,"EX0",kBlack);
  pltDetUnfChiDiff->SetYRange(0.4,1.6);
  //pltDetUnfChiDiff->SetYRange(0.9,1.1);
  pltDetUnfChiDiff->AddLine(0,1,13, 1,kBlack,2);
  pltDetUnfChiDiff->Draw(lC0,kTRUE,"png",2);
 


  //tmpTStr = "Post_cov_"+BaseName;
  //tmpTStr = "Post_uTotalCov_"+BaseName;
  tmpTStr = "uTotalAfterDetUnfCovMat__"+BaseName;
  pltUnfPost_uTotalCov = new CPlot(tmpTStr,"TSVDUnfold TotalCovMat after Det Unfolding","","");
  pltUnfPost_uTotalCov->setOutDir(resultDir);
  gPad->SetLogz(0);
  SVD_Post.uTotalCovMat->SetMarkerSize(0.8);
  //pltUnfPost_uTotalCov->AddHist2D(SVD_Post.uTotalCovMat,"COLZ",kWhite,kBlack);
  pltUnfPost_uTotalCov->AddHist2D(SVD_Post.uTotalCovMat,"COLTEXTZ",kWhite,kBlack);
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
  SVD_Born.InputCovMat->Add(SVD_Post.MCEventEffFSRCovMat );

  //InputCovMat to FSR Unfolding
  tmpTStr = "InputCovMatToFSRUnf_"+BaseName;
  pltUnfBorn_InputCov = new CPlot(tmpTStr,"Input TotalCovMat to FSR Unfolding","","");
  pltUnfBorn_InputCov -> setOutDir(resultDir);
  gPad->SetLogz(0);
  SVD_Born.InputCovMat -> SetMarkerSize(0.8);
  pltUnfBorn_InputCov -> AddHist2D(SVD_Born.InputCovMat,"COLTEXTZ",kWhite,kBlack);
  pltUnfBorn_InputCov -> Draw(myCan,kTRUE,"png");

//FSR Unf.Response Matrix
  Unfolder FSRUnfold("Born");
  FSRUnfold.setTrue(h1_Born_BothFid); //dumy for set up the bin ranges
  FSRUnfold.setMeas(SVD_Post.EffCorr);
  FSRUnfold.colNormalize(h2_PostBorn_BothFid);
  FSRUnfold.setMigrationMatrix(h2_PostBorn_BothFid);
  FSRUnfold.unfold();

  h2_PostBorn_BothFid->GetYaxis()->SetMoreLogLabels();
  h2_PostBorn_BothFid->GetYaxis()->SetNoExponent();
  h2_PostBorn_BothFid->GetXaxis()->SetMoreLogLabels();
  h2_PostBorn_BothFid->GetXaxis()->SetNoExponent();
  h2_PostBorn_BothFid->GetXaxis()->SetTitleSize(0.03);
  h2_PostBorn_BothFid->GetXaxis()->SetLabelSize(0.03);
  h2_PostBorn_BothFid->GetXaxis()->SetTitleOffset(1.6);
  h2_PostBorn_BothFid->GetYaxis()->SetTitleSize(0.03);
  h2_PostBorn_BothFid->GetYaxis()->SetLabelSize(0.03);
  h2_PostBorn_BothFid->GetYaxis()->SetTitleOffset(1.8);

  gStyle->SetPaintTextFormat("3.2f"); 
  tmpTStr = "FSRUnfResponseMatrix_"+BaseName;
  pltFSRUnfResMtrx = new CPlot(tmpTStr,"","Post W p_{T} [GeV]","Born W p_{T} [GeV]");
  pltFSRUnfResMtrx->setOutDir(resultDir);
  pltFSRUnfResMtrx->AddHist2D(h2_PostBorn_BothFid,"COLTEXTZ",kWhite,kBlack);
  pltFSRUnfResMtrx->SetLogx();
  pltFSRUnfResMtrx->SetLogy();
  h2_PostBorn_BothFid -> SetMarkerSize(0.8);
  pltFSRUnfResMtrx-> Draw(myCan,kTRUE,"png");

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
  //    SVD_Born.data,SVD_Post.Eff_uMCEventEffFSRCovMat, SVD_Born.bini, SVD_Born.xini,SVD_Born.Adet);
  
  //TSVDUnfold *svdBorn = new TSVDUnfold(
  //    SVD_Born.data,SVD_Post.Eff_uTotalRecoCovMat, SVD_Born.bini, SVD_Born.xini,SVD_Born.Adet);
  
  TSVDUnfold *svdBorn = new TSVDUnfold(
      SVD_Born.data,SVD_Post.MCEventEffFSRCovMat, SVD_Born.bini, SVD_Born.xini,SVD_Born.Adet);
      //SVD_Born.data,SVD_Born.InputCovMat, SVD_Born.bini, SVD_Born.xini,SVD_Born.Adet);
  
  //TSVDUnfold *svdBorn = new TSVDUnfold(
  //    SVD_Born.data,SVD_Post.Eff_uTauCov, SVD_Born.bini, SVD_Born.xini,SVD_Born.Adet);
  
  SVD_Born.statCov = svdBorn->GetBCov();
  svdBorn->SetNormalize( kFALSE );
  if(BaseName == "WpToEleNu" || BaseName == "WmToEleNu" )
    SVD_Born.unfRes = svdBorn->Unfold(3);
  if(BaseName == "WpToMuNu" || BaseName == "WmToMuNu" )
    SVD_Born.unfRes = svdBorn->Unfold(4);
  //SVD_Born.unfRes = svdBorn->Unfold(5);
  //SVD_Born.unfRes = svdBorn->Unfold(6);
  //SVD_Born.unfRes = svdBorn->Unfold(7);
  //SVD_Born.unfRes = svdBorn->Unfold(8);
  //SVD_Born.unfRes = svdBorn->Unfold(9);
  SVD_Born.dDist = svdBorn->GetD();
  SVD_Born.svDist = svdBorn->GetSV();
  
  for(int i(1);i<=h1_Data_SigYild->GetNbinsX();i++)
  {
    SVD_Born.FSRUnf -> SetBinContent(i,SVD_Born.unfRes->GetBinContent(i));
  }
  //SVD_Born.FSRUnf = (TH1D*)SVD_Born.unfRes->Clone("FSRUnf");
  //SVD_Born.FSRUnf -> Sumw2();
  
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
  //SVD_Born.uMCEventEffFSRCovMat = svdBorn->GetUnfoldCovMatrix( SVD_Post.Eff_uMCEventEffFSRCovMat, 100);
  //SVD_Born.uMCEventEffFSRCovMat = svdBorn->GetUnfoldCovMatrix( SVD_Post.AcceptFSRCovMat, 1000);
  SVD_Born.uMCEventEffFSRCovMat = svdBorn->GetUnfoldCovMatrix( SVD_Post.MCEventEffFSRCovMat, 1000);
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
  SVD_Born.uTotalCovMat->Add(SVD_Born.uMCEventEffFSRCovMat );

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
    Fout << i << "\t" << SVD_Born.unfRes->GetBinContent(i) << "\t\t" << SVD_Born.uMCEventEffFSRCovMat->GetBinContent(i,i) << "\t\t"<< TMath::Sqrt(SVD_Born.uMCEventEffFSRCovMat->GetBinContent(i,i)) << "\t\t" << TMath::Sqrt(SVD_Born.uMCEventEffFSRCovMat->GetBinContent(i,i))/SVD_Born.unfRes->GetBinContent(i)*100 << endl;
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
      Fout << i << "\t\t" << TMath::Sqrt(SVD_Born.uRecoStatisticCovMat->GetBinContent(i,i))/SVD_Born.unfRes->GetBinContent(i)*100 << "\t\t" << TMath::Sqrt(SVD_Born.uRecoEffiCovMat->GetBinContent(i,i))/SVD_Born.unfRes->GetBinContent(i)*100 << "\t\t"<< TMath::Sqrt(SVD_Born.uRecoSmearCovMat->GetBinContent(i,i))/SVD_Born.unfRes->GetBinContent(i)*100 << "\t\t"<< TMath::Sqrt(SVD_Born.uRecoRecoilCovMat->GetBinContent(i,i))/SVD_Born.unfRes->GetBinContent(i)*100 << "\t\t" << "\t\t"<< TMath::Sqrt(SVD_Born.uMCEventEffFSRCovMat->GetBinContent(i,i))/SVD_Born.unfRes->GetBinContent(i)*100 << TMath::Sqrt(SVD_Born.uRecoScaleCovMat->GetBinContent(i,i))/SVD_Born.unfRes->GetBinContent(i)*100 <<endl;
    }
  if(BaseName == "WpToMuNu" || BaseName == "WmToMuNu" )
    for( int i(1);i<=SVD_Born.unfRes->GetNbinsX(); i++)
    {
      Fout << i << "\t\t" << TMath::Sqrt(SVD_Born.uRecoStatisticCovMat->GetBinContent(i,i))/SVD_Born.unfRes->GetBinContent(i)*100 << "\t\t" << TMath::Sqrt(SVD_Born.uRecoEffiCovMat->GetBinContent(i,i))/SVD_Born.unfRes->GetBinContent(i)*100 << "\t\t"<< TMath::Sqrt(SVD_Born.uRecoSmearCovMat->GetBinContent(i,i))/SVD_Born.unfRes->GetBinContent(i)*100 << "\t\t"<< TMath::Sqrt(SVD_Born.uRecoRecoilCovMat->GetBinContent(i,i))/SVD_Born.unfRes->GetBinContent(i)*100 << "\t\t" << "\t\t"<< TMath::Sqrt(SVD_Born.uMCEventEffFSRCovMat->GetBinContent(i,i))/SVD_Born.unfRes->GetBinContent(i)*100 << TMath::Sqrt(SVD_Born.uRecoQCDRatioCovMat->GetBinContent(i,i))/SVD_Born.unfRes->GetBinContent(i)*100 <<endl;
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
      Fout << i << "\t\t" << TMath::Sqrt(SVD_Born.uRecoStatisticCovMat->GetBinContent(i,i))/SVD_Born.unfRes->GetBinContent(i)*100 << "\t\t" << TMath::Sqrt( TMath::Power(TMath::Sqrt(SVD_Born.uRecoEffiCovMat->GetBinContent(i,i)),2)+ TMath::Power( TMath::Sqrt(SVD_Born.uRecoSmearCovMat->GetBinContent(i,i)),2) + TMath::Power(TMath::Sqrt(SVD_Born.uRecoRecoilCovMat->GetBinContent(i,i)),2)+ TMath::Power( TMath::Sqrt(SVD_Born.uMCEventEffFSRCovMat->GetBinContent(i,i)),2)+ TMath::Power( TMath::Sqrt(SVD_Born.uRecoScaleCovMat->GetBinContent(i,i)),2) )/SVD_Born.unfRes->GetBinContent(i)*100 <<endl;
    }
  if(BaseName == "WpToMuNu" || BaseName == "WmToMuNu" )
    for( int i(1);i<=SVD_Born.unfRes->GetNbinsX(); i++)
    {
      Fout << i << "\t\t" << TMath::Sqrt(SVD_Born.uRecoStatisticCovMat->GetBinContent(i,i))/SVD_Born.unfRes->GetBinContent(i)*100 << "\t\t" << TMath::Sqrt( TMath::Power(TMath::Sqrt(SVD_Born.uRecoEffiCovMat->GetBinContent(i,i)),2)+ TMath::Power( TMath::Sqrt(SVD_Born.uRecoSmearCovMat->GetBinContent(i,i)),2) + TMath::Power(TMath::Sqrt(SVD_Born.uRecoRecoilCovMat->GetBinContent(i,i)),2)+ TMath::Power( TMath::Sqrt(SVD_Born.uMCEventEffFSRCovMat->GetBinContent(i,i)),2)+ TMath::Power( TMath::Sqrt(SVD_Born.uRecoQCDRatioCovMat->GetBinContent(i,i)),2) )/SVD_Born.unfRes->GetBinContent(i)*100 <<endl;
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
      Fout << i << "\t\t" << TMath::Sqrt(SVD_Born.unfRes->GetBinContent(i))/SVD_Born.unfRes->GetBinContent(i)*100 << "\t\t" << TMath::Sqrt( TMath::Power(TMath::Sqrt(SVD_Born.uRecoEffiCovMat->GetBinContent(i,i)),2)+ TMath::Power( TMath::Sqrt(SVD_Born.uRecoSmearCovMat->GetBinContent(i,i)),2) + TMath::Power(TMath::Sqrt(SVD_Born.uRecoRecoilCovMat->GetBinContent(i,i)),2)+  TMath::Power( TMath::Sqrt(SVD_Born.uMCEventEffFSRCovMat->GetBinContent(i,i)),2) +  TMath::Power( TMath::Sqrt(SVD_Born.uRecoScaleCovMat->GetBinContent(i,i)),2))/SVD_Born.unfRes->GetBinContent(i)*100 <<endl;
    }
  if(BaseName == "WpToMuNu" || BaseName == "WmToMuNu" )
    for( int i(1);i<=SVD_Born.unfRes->GetNbinsX(); i++)
    {
      Fout << i << "\t\t" << TMath::Sqrt(SVD_Born.unfRes->GetBinContent(i))/SVD_Born.unfRes->GetBinContent(i)*100 << "\t\t" << TMath::Sqrt( TMath::Power(TMath::Sqrt(SVD_Born.uRecoEffiCovMat->GetBinContent(i,i)),2)+ TMath::Power( TMath::Sqrt(SVD_Born.uRecoSmearCovMat->GetBinContent(i,i)),2) + TMath::Power(TMath::Sqrt(SVD_Born.uRecoRecoilCovMat->GetBinContent(i,i)),2)+  TMath::Power( TMath::Sqrt(SVD_Born.uMCEventEffFSRCovMat->GetBinContent(i,i)),2) +  TMath::Power( TMath::Sqrt(SVD_Born.uRecoQCDRatioCovMat->GetBinContent(i,i)),2))/SVD_Born.unfRes->GetBinContent(i)*100 <<endl;
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
      Fout << i << "\t\t" << TMath::Sqrt(h1_Data_SigYild->GetBinContent(i))/h1_Data_SigYild->GetBinContent(i)*100 << "\t\t" << TMath::Sqrt( TMath::Power(TMath::Sqrt(SVD_Born.uRecoEffiCovMat->GetBinContent(i,i)),2)+ TMath::Power( TMath::Sqrt(SVD_Born.uRecoSmearCovMat->GetBinContent(i,i)),2) + TMath::Power(TMath::Sqrt(SVD_Born.uRecoRecoilCovMat->GetBinContent(i,i)),2)+ TMath::Power( TMath::Sqrt(SVD_Born.uMCEventEffFSRCovMat->GetBinContent(i,i)),2)+ TMath::Power( TMath::Sqrt(SVD_Born.uRecoScaleCovMat->GetBinContent(i,i)),2) )/SVD_Born.unfRes->GetBinContent(i)*100 <<endl;
    }
  if(BaseName == "WpToMuNu" || BaseName == "WmToMuNu" )
    for( int i(1);i<=SVD_Born.unfRes->GetNbinsX(); i++)
    {
      Fout << i << "\t\t" << TMath::Sqrt(h1_Data_SigYild->GetBinContent(i))/h1_Data_SigYild->GetBinContent(i)*100 << "\t\t" << TMath::Sqrt( TMath::Power(TMath::Sqrt(SVD_Born.uRecoEffiCovMat->GetBinContent(i,i)),2)+ TMath::Power( TMath::Sqrt(SVD_Born.uRecoSmearCovMat->GetBinContent(i,i)),2) + TMath::Power(TMath::Sqrt(SVD_Born.uRecoRecoilCovMat->GetBinContent(i,i)),2)+ TMath::Power( TMath::Sqrt(SVD_Born.uMCEventEffFSRCovMat->GetBinContent(i,i)),2)+ TMath::Power( TMath::Sqrt(SVD_Born.uRecoQCDRatioCovMat->GetBinContent(i,i)),2) )/SVD_Born.unfRes->GetBinContent(i)*100 <<endl;
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
      Fout << i << "\t\t" << h1_Data_SigYild->GetBinError(i)/h1_Data_SigYild->GetBinContent(i)*100 << "\t\t" << TMath::Sqrt( TMath::Power(TMath::Sqrt(SVD_Born.uRecoEffiCovMat->GetBinContent(i,i)),2)+ TMath::Power( TMath::Sqrt(SVD_Born.uRecoSmearCovMat->GetBinContent(i,i)),2) + TMath::Power(TMath::Sqrt(SVD_Born.uRecoRecoilCovMat->GetBinContent(i,i)),2)+  TMath::Power( TMath::Sqrt(SVD_Born.uMCEventEffFSRCovMat->GetBinContent(i,i)),2) +  TMath::Power( TMath::Sqrt(SVD_Born.uRecoScaleCovMat->GetBinContent(i,i)),2))/SVD_Born.unfRes->GetBinContent(i)*100 <<endl;
    }
  if(BaseName == "WpToMuNu" || BaseName == "WmToMuNu" )
    for( int i(1);i<=SVD_Born.unfRes->GetNbinsX(); i++)
    {
      Fout << i << "\t\t" << h1_Data_SigYild->GetBinError(i)/h1_Data_SigYild->GetBinContent(i)*100 << "\t\t" << TMath::Sqrt( TMath::Power(TMath::Sqrt(SVD_Born.uRecoEffiCovMat->GetBinContent(i,i)),2)+ TMath::Power( TMath::Sqrt(SVD_Born.uRecoSmearCovMat->GetBinContent(i,i)),2) + TMath::Power(TMath::Sqrt(SVD_Born.uRecoRecoilCovMat->GetBinContent(i,i)),2)+  TMath::Power( TMath::Sqrt(SVD_Born.uMCEventEffFSRCovMat->GetBinContent(i,i)),2) +  TMath::Power( TMath::Sqrt(SVD_Born.uRecoQCDRatioCovMat->GetBinContent(i,i)),2))/SVD_Born.unfRes->GetBinContent(i)*100 <<endl;
    }
  
  SVD_Born.uAdetCov = svdBorn->GetAdetCovMatrix( 1000);
  SVD_Born.uStatCov->Add(SVD_Born.uAdetCov);

  SVD_Born.uTotalCovMat->Add(SVD_Born.uAdetCov);

  SVD_Born.uTauCov = svdBorn->GetXtau();
  SVD_Born.uTauCov->Add( SVD_Born.uAdetCov);

  //TotalCovMat after FSR Unfolding
  tmpTStr = "uTotalAfterFSRUnfCovMat_"+BaseName;
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
  pltUnfBorn_AbsNormCorrErr = new CPlot(tmpTStr,"FSR_Unf Absolute Normalized Covariance error matrix","","");
  pltUnfBorn_AbsNormCorrErr -> setOutDir(resultDir);
  gPad->SetLogz(0);
  SVD_Born.AbsNormCorrErr -> SetMarkerSize(0.8);
  pltUnfBorn_AbsNormCorrErr->AddHist2D(SVD_Born.AbsNormCorrErr,"COLTEXTZ",kWhite,kBlack);
  //pltUnfBorn_AbsNormCorrErr->AddHist2D(SVD_Born.AbsNormCorrErr,"COLZ",kWhite,kBlack);
  pltUnfBorn_AbsNormCorrErr->Draw(myCan,kTRUE,"png");

  Fout << "SVD_Born.uAdetCov  -  Response Matrix Systematics; "<< endl;
  Fout << "Bin" << "\t" << "Wpt yield " << "\t\t" << "Cov_i_i" << "\t\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
  Fout << "==================================================================================================" << endl;
  for( int i(1);i<=SVD_Born.unfRes->GetNbinsX(); i++)
  {
    Fout << i << "\t" <<SVD_Born.unfRes->GetBinContent(i) << "\t\t" << SVD_Born.uAdetCov->GetBinContent(i,i) << "\t\t"<< TMath::Sqrt(SVD_Born.uAdetCov->GetBinContent(i,i)) << "\t\t" << TMath::Sqrt(SVD_Born.uAdetCov->GetBinContent(i,i))/SVD_Born.unfRes->GetBinContent(i)*100 << endl;
    FSRUnf_SVD[i-1]=TMath::Sqrt(SVD_Born.uAdetCov->GetBinContent(i,i))/SVD_Born.unfRes->GetBinContent(i)*100;
  }

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

  Fout<<"Yields after FSR Unfolding and SF and bin-by-bin correction"<<endl;
  for( int i(1); i<= SVD_Born.unfRes->GetNbinsX(); i++)
  {    
    Fout<<i<<"\t"<<SVD_Born.FSRUnf->GetBinContent(i)<<"\t"<<h1_Born_BothOvBorn_eqBin->GetBinContent(i)<<"\t"<<SVD_Born.EffCorr->GetBinContent(i)<<endl;
  }

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

 
  TH1D* drawDifferenceFSRUnf;
  drawDifferenceFSRUnf = makeDiffHist(SVD_Born.EffCorr,SVD_Born.Gen,"drawDifferenceFSRUnf");
  drawDifferenceFSRUnf->SetMarkerStyle(kFullCircle);
  drawDifferenceFSRUnf->SetMarkerSize(0.9);
  SVD_Born.EffCorr->GetXaxis()->SetLabelSize(0.0); 

  tmpTStr = "FSR_Unf_Chi"+BaseName;
  pltFSRUnfChi = new CPlot(tmpTStr,"Post to Born Unfolding with SVD","W pT [Bins]","Event");
  pltFSRUnfChi->setOutDir(resultDir);
  pltFSRUnfChi->AddHist1D(SVD_Born.unfRes,"e",kBlue,1,0,20,2);
  pltFSRUnfChi->AddHist1D(SVD_Born.data,"e",kRed,1,0,24,2);
  pltFSRUnfChi->AddHist1D(SVD_Born.True,"hist",kBlack,1,0,0,0);
  pltFSRUnfChi->AddHist1D(SVD_Born.Gen,"hist",kGreen,1,0,0,0);
  pltFSRUnfChi->AddHist1D(SVD_Born.EffCorr,"elp",kGreen+2,0,0,26,2);
  //pltFSRUnfChi->SetLegend(0.68,0.57,0.93,0.8);
  //pltFSRUnfChi->SetLegend(0.48,0.77,0.87,0.9);
  pltFSRUnfChi->SetLegend(0.55,0.55,0.93,0.90);
  //pltFSRUnfChi->GetLegend()->AddEntry(SVD_Born.unfRes,"Unfolded","p");
  pltFSRUnfChi->GetLegend()->AddEntry(SVD_Born.unfRes,"Unfolded to Both fiducial","p");
  pltFSRUnfChi->GetLegend()->AddEntry(SVD_Born.data,"Post","p");
  //pltFSRUnfChi->GetLegend()->AddEntry(SVD_Born.True,"Born Target","l");
  pltFSRUnfChi->GetLegend()->AddEntry(SVD_Born.True,"Born in the Both fiducial","l");
  //pltFSRUnfChi->GetLegend()->AddEntry(SVD_Born.Gen,"Born Gen","l");
  //pltFSRUnfChi->GetLegend()->AddEntry(SVD_Born.Gen,"PowHeg CT10 Pythia Z2*","l");
  //pltFSRUnfChi->GetLegend()->AddEntry(SVD_Born.EffCorr,"Unfolded","p");
  pltFSRUnfChi->GetLegend()->AddEntry(SVD_Born.Gen,"Born fiducial","l");
  pltFSRUnfChi->GetLegend()->AddEntry(SVD_Born.EffCorr,"EffCorr","p");
  pltFSRUnfChi->Draw(lC0,kFALSE,"png",1);

  tmpTStr = "FSR_Unf_Chi_Diff"+BaseName;
  pltFSRUnfChiDiff = new CPlot(tmpTStr,"","W p_{T} [Bins]","EffCorr/Born fiducial");
  pltFSRUnfChiDiff->setOutDir(resultDir);
  pltFSRUnfChiDiff->AddHist1D(drawDifferenceFSRUnf,"EX0",kBlack);
  pltFSRUnfChiDiff->SetYRange(0.4,1.6);
  //pltFSRUnfChiDiff->SetYRange(0.9,1.1);
  pltFSRUnfChiDiff->AddLine(0,1,13, 1,kBlack,2);
  pltFSRUnfChiDiff->Draw(lC0,kTRUE,"png",2);



  tmpTStr = "Born_cov_"+BaseName;
  pltUnfBorn_cov = new CPlot(tmpTStr,"TSVDUnfold Covariance matrix","","");
  pltUnfBorn_cov->setOutDir(resultDir);
  //pltUnfBorn_cov->AddHist2D(SVD_Post.uStatCov,"COLZ",kWhite,kBlack);
  //tUnfBorn_cov->AddHist2D(SVD_Born.uStatCov,"COLZ",kWhite,kBlack);
  SVD_Born.uStatCov -> SetMarkerSize(0.8);
  pltUnfBorn_cov->AddHist2D(SVD_Born.uStatCov,"COLTEXTZ",kWhite,kBlack);
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

  Fout<<"SVD Unfolding Systematic = SQRT(dUnf^2+FSRUnf_SVD^2)"<<endl;
  for( int i(0);i<h1_Data_SigYild->GetNbinsX(); i++)
  {
    Unf_SVD[i]=TMath::Sqrt(dUnf_SVD[i]*dUnf_SVD[i]+FSRUnf_SVD[i]*FSRUnf_SVD[i]);
    Fout<<i+1<<"\t"<<Unf_SVD[i]<<endl;
  }
  if(BaseName == "WpToMuNu" || BaseName == "WmToMuNu" )
    for( int i(1);i<=h1_Data_SigYild->GetNbinsX(); i++)
    {
      TotalError[i]=100*TMath::Sqrt(SVD_Post.RecoStatisticCovMat->GetBinContent(i,i)+SVD_Post.RecoEffiCovMat->GetBinContent(i,i)
	  +SVD_Post.RecoSmearCovMat->GetBinContent(i,i)+SVD_Post.RecoRecoilCovMat->GetBinContent(i,i)
	  +SVD_Post.RecoQCDRatioCovMat->GetBinContent(i,i)+SVD_Post.MCEventEffFSRCovMat->GetBinContent(i,i)
	  +SVD_Post.uAdetCov->GetBinContent(i,i)+SVD_Born.uAdetCov->GetBinContent(i,i)
	  +TMath::Power(0.026*h1_Data_SigYild->GetBinContent(i),2))/h1_Data_SigYild->GetBinContent(i);
      Fout<<"TotalError = "<<TotalError[i]<<endl;
      //SVD_Born.EffCorr->SetBinError(i,0.01*TotalError[i]*SVD_Born.EffCorr->GetBinContent(i));
    }
  else if(BaseName == "WpToEleNu" || BaseName == "WmToEleNu" )
    for( int i(1);i<=h1_Data_SigYild->GetNbinsX(); i++)
    {
      TotalError[i]=100*TMath::Sqrt(SVD_Post.RecoStatisticCovMat->GetBinContent(i,i)+SVD_Post.RecoEffiCovMat->GetBinContent(i,i)
	  +SVD_Post.RecoSmearCovMat->GetBinContent(i,i)+SVD_Post.RecoRecoilCovMat->GetBinContent(i,i)
	  +SVD_Post.RecoScaleCovMat->GetBinContent(i,i)+SVD_Post.MCEventEffFSRCovMat->GetBinContent(i,i)
	  +SVD_Post.uAdetCov->GetBinContent(i,i)+SVD_Born.uAdetCov->GetBinContent(i,i)
	  +TMath::Power(0.026*h1_Data_SigYild->GetBinContent(i),2))/h1_Data_SigYild->GetBinContent(i);
      Fout<<"TotalError = "<<TotalError[i]<<endl;
      //SVD_Born.EffCorr->SetBinError(i,0.01*TotalError[i]*SVD_Born.EffCorr->GetBinContent(i));
    }

  if(BaseName == "WpToMuNu"){
    TotalUncertErr[0] = 0;
    TotalUncertErr[1] = 3.24 ; 
    TotalUncertErr[2] = 3.33 ; 
    TotalUncertErr[3] = 3.27 ; 
    TotalUncertErr[4] = 4.64 ; 
    TotalUncertErr[5] = 4.35 ; 
    TotalUncertErr[6] = 4.93 ; 
    TotalUncertErr[7] = 4.91 ; 
    TotalUncertErr[8] = 6.79 ; 
    TotalUncertErr[9] = 6.61 ; 
    TotalUncertErr[10]= 6.44 ; 
    TotalUncertErr[11]= 11.09; 
    TotalUncertErr[12]= 19.10; 
    TotalUncertErr[13]= 25.14; 
    errPowheg[0] = 0; 
    errPowheg[1] = 4.268; 
    errPowheg[2] = 4.147; 
    errPowheg[3] = 4.122; 
    errPowheg[4] = 4.123; 
    errPowheg[5] = 4.132; 
    errPowheg[6] = 4.126; 
    errPowheg[7] = 4.143; 
    errPowheg[8] = 5.279; 
    errPowheg[9] = 4.222; 
    errPowheg[10]= 4.426;
    errPowheg[11]= 4.819; 
    errPowheg[12]= 5.075; 
    errPowheg[13]= 6.084; 
  }else if(BaseName == "WmToMuNu"){
    TotalUncertErr[0] = 0;
    TotalUncertErr[1] = 3.17 ;
    TotalUncertErr[2] = 3.31 ;
    TotalUncertErr[3] = 3.28 ;
    TotalUncertErr[4] = 3.90 ;
    TotalUncertErr[5] = 4.18 ;
    TotalUncertErr[6] = 5.13 ;
    TotalUncertErr[7] = 5.02 ;
    TotalUncertErr[8] = 6.09 ;
    TotalUncertErr[9] = 5.66 ;
    TotalUncertErr[10]= 7.15 ;
    TotalUncertErr[11]= 12.76;
    TotalUncertErr[12]= 17.38;
    TotalUncertErr[13]= 34.11;
    errPowheg[0] = 0; 
    errPowheg[1] = 4.398; 
    errPowheg[2] = 4.382; 
    errPowheg[3] = 4.423; 
    errPowheg[4] = 4.443; 
    errPowheg[5] = 5.604; 
    errPowheg[6] = 4.532; 
    errPowheg[7] = 7.792; 
    errPowheg[8] = 3.349; 
    errPowheg[9] = 4.622; 
    errPowheg[10]= 19.15;
    errPowheg[11]= 4.587; 
    errPowheg[12]= 4.323; 
    errPowheg[13]= 5.229; 
  }else if(BaseName == "WpToEleNu"){
    TotalUncertErr[0] = 0; 
    TotalUncertErr[1] = 3.59 ;  
    TotalUncertErr[2] = 3.52 ; 
    TotalUncertErr[3] = 3.39 ; 
    TotalUncertErr[4] = 3.73 ; 
    TotalUncertErr[5] = 4.19 ; 
    TotalUncertErr[6] = 4.85 ; 
    TotalUncertErr[7] = 5.53 ; 
    TotalUncertErr[8] = 7.38 ; 
    TotalUncertErr[9] = 7.33 ; 
    TotalUncertErr[10]= 8.23 ; 
    TotalUncertErr[11]= 11.18; 
    TotalUncertErr[12]= 15.06; 
    TotalUncertErr[13]= 24.68;
    errPowheg[0] = 0; 
    errPowheg[1] = 4.37 ; 
    errPowheg[2] = 4.314; 
    errPowheg[3] = 4.109; 
    errPowheg[4] = 12.58; 
    errPowheg[5] = 19.8 ; 
    errPowheg[6] = 7.864; 
    errPowheg[7] = 3.68 ; 
    errPowheg[8] = 3.741; 
    errPowheg[9] = 19.27; 
    errPowheg[10]= 6.264;
    errPowheg[11]= 4.312; 
    errPowheg[12]= 4.235; 
    errPowheg[13]= 5.534; 
  }else if(BaseName == "WmToEleNu"){
    TotalUncertErr[0] = 0; 
    TotalUncertErr[1] = 3.62 ; 
    TotalUncertErr[2] = 3.46 ; 
    TotalUncertErr[3] = 3.49 ; 
    TotalUncertErr[4] = 3.93 ; 
    TotalUncertErr[5] = 4.26 ; 
    TotalUncertErr[6] = 4.80 ; 
    TotalUncertErr[7] = 5.62 ; 
    TotalUncertErr[8] = 7.21 ; 
    TotalUncertErr[9] = 7.80 ; 
    TotalUncertErr[10]= 8.92 ; 
    TotalUncertErr[11]= 13.00; 
    TotalUncertErr[12]= 18.42; 
    TotalUncertErr[13]= 25.35;
    errPowheg[0] = 0; 
    errPowheg[1] = 4.285; 
    errPowheg[2] = 4.156; 
    errPowheg[3] = 4.132; 
    errPowheg[4] = 4.129; 
    errPowheg[5] = 4.128; 
    errPowheg[6] = 7.152; 
    errPowheg[7] = 4.143; 
    errPowheg[8] = 18.56; 
    errPowheg[9] = 16.32; 
    errPowheg[10]= 4.427;
    errPowheg[11]= 4.582; 
    errPowheg[12]= 4.939; 
    errPowheg[13]= 5.144; 
  }
  
  for( int i(1);i<=h1_Data_SigYild->GetNbinsX(); i++)
  {
    SVD_Born.EffCorr->SetBinError(i,0.01*TotalUncertErr[i]*SVD_Born.EffCorr->GetBinContent(i));
    SVD_Born.Gen->SetBinError(i,0.01*errPowheg[i]*SVD_Born.Gen->GetBinContent(i));
  }
  
  // Write to root file
  SVD_Post.data->Write();
  SVD_Post.True->Write();
  SVD_Post.Gen->Write();
  
  SVD_Post.DetUnf -> Write();
  SVD_Post.unfRes->Write();
  SVD_Post.EffCorr->Write();
  
  SVD_Born.Gen->Write();
  
  SVD_Born.FSRUnf -> Write();
  SVD_Born.unfRes->Write();
  SVD_Born.EffCorr->Write();
  return 0;
}

TH1D *makeDiffHist(TH1D* hData, TH1D* hPowheg, const TString name)
{
  TH1D *hDiff = new TH1D(name,"",hData->GetNbinsX(),hData->GetXaxis()->GetXmin(),hData->GetXaxis()->GetXmax());
  for(Int_t ibin=1; ibin<=hData->GetNbinsX(); ibin++) {
    Double_t diff = (hData->GetBinContent(ibin)/hPowheg->GetBinContent(ibin));
    Double_t err = hData->GetBinError(ibin)/hPowheg->GetBinContent(ibin);
    hDiff->SetBinContent(ibin,diff);
    hDiff->SetBinError(ibin,err);
  }
  hDiff->GetYaxis()->SetTitleOffset(0.8);
  hDiff->GetYaxis()->SetTitleSize(0.07);
  hDiff->GetYaxis()->SetLabelSize(0.08);
  hDiff->GetYaxis()->CenterTitle();
  hDiff->GetXaxis()->SetTitleOffset(1.0);
  hDiff->GetXaxis()->SetTitleSize(0.08);
  hDiff->GetXaxis()->SetLabelSize(0.08);
  return hDiff;
}

