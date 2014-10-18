#include "TStyle.h"
#include "../../SmearSyst/EventSelection1/Utils/const.h"
#include "../../SmearSyst/EventSelection1/Utils/CPlot.hh"
#include "../../SmearSyst/EventSelection1/Utils/MitStyleRemix.hh"
#include "../../SmearSyst/EventSelection1/Utils/Unfolder.h"
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

int MakeCovMat
(TString DataFile,TString DataYieldFile,TString CorrName,TString BaseName)
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
  cout<<"Data Inpufile: "<<DataFile<<endl;

  TString resultDir = "CovMat_"+BaseName;
  gSystem->mkdir(resultDir,kTRUE);
  char tmpName[30];
  TString tmpTStr;
 
  ofstream Fout;
  Fout.open(resultDir+"/Systematics_"+CorrName+".txt");
  
  TFile *f_Data      = new TFile(DataFile);
  TFile *f_DataYield = new TFile(DataYieldFile);

  tmpTStr = resultDir+"/CovMat_"+BaseName+CorrName+".root";
  TFile *f_Out    = new TFile(tmpTStr,"recreate");

  // SVD input
  struct histSVD{
    TH2D *RecoStatisticCovMat;
    TH2D *RecoEffiCovMat;
    TH2D *RecoScaleCovMat;
    TH2D *RecoSmearCovMat;
    TH2D *RecoRecoilCovMat;
    TH2D *RecoLumiCovMat;
    TH2D *RecoQCDRatioCovMat;
    TH2D *RecoBckgrCovMat;
    TH2D *dUnfCovMat;
    TH2D *PostEffCorrCovMat;
    TH2D *FSRUnfCovMat;
    TH2D *BornEffCorrCovMat;
    
    TH2D *RecoStatisticCorrMat;
    TH2D *RecoEffiCorrMat;
    TH2D *RecoScaleCorrMat;
    TH2D *RecoSmearCorrMat;
    TH2D *RecoRecoilCorrMat;
    TH2D *RecoLumiCorrMat;
    TH2D *RecoQCDRatioCorrMat;
    TH2D *RecoBckgrCorrMat;
    TH2D *dUnfCorrMat;
    TH2D *PostEffCorrCorrMat;
    TH2D *FSRUnfCorrMat;
    TH2D *BornEffCorrCorrMat;
  };
  histSVD SVD_Post;

  // Data
  double XMean[NWptBinPlus-1]={0.0};
  double YMean[NWptBinPlus-1];
  
  const Int_t NumOfSamples=500;
      
  double Xcontent[NWptBinPlus-1][NumOfSamples]={{0.0},{0.0}};
  
  double XMeanMinusXBinCont[NumOfSamples]={0.0};
  
  double XMeanMinusXBinContSum[NWptBinPlus-1][NWptBinPlus-1]={{0.0},{0.0}};
  double XMeanMinusXBinContSumTwo[NWptBinPlus][NWptBinPlus]={{0.0},{0.0}};
  
  double CorrMatrix[NWptBinPlus][NWptBinPlus]={{0.0},{0.0}};
  
  TH1D* YMeanMinusYBinCont[NumOfSamples];
  
  TH1D* h1_DataSigYield;
  TH1D* h1_ToyYield[NumOfSamples+1];
  TH1D* h1_SVD_Post_data[NumOfSamples+1];
  TH1D* h1_SVD_Born_EffCorr[NumOfSamples+1];
  TH1D* h1_SVD_Born_Gen[NumOfSamples+1];
  TH1D* h1_SVD_Post_True[NumOfSamples+1];
  TH1D* h1_SVD_Post_unfRes[NumOfSamples+1];
  TH1D* h1_SVD_Post_Gen[NumOfSamples+1];

  // Define Histo
  SVD_Post.RecoStatisticCovMat = new TH2D("SVD_Post.RecoStatisticCovMat","Reco Stage Statistic Covariace matrix"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Post.RecoEffiCovMat = new TH2D("SVD_Post.RecoEffiCovMat","Reco Stage Effi Covariace matrix"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  TH2D* h2_RecoEffiCovMat = new TH2D("h2_RecoEffiCovMat","Reco Stage Effi Covariace matrix"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Post.RecoScaleCovMat = new TH2D("SVD_Post.RecoScaleCovMat","Reco Stage Scale Covariace matrix"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  TH2D* h2_RecoScaleCovMat = new TH2D("h2_RecoScaleCovMat","Reco Stage Scale Covariace matrix"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Post.RecoSmearCovMat = new TH2D("SVD_Post.RecoSmearCovMat","Reco Stage Smear Covariace matrix"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  TH2D* h2_RecoSmearCovMat = new TH2D("h2_RecoSmearCovMat","Reco Stage Smear Covariace matrix"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Post.RecoRecoilCovMat = new TH2D("SVD_Post.RecoRecoilCovMat","Reco Stage Recoil Covariace matrix"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  TH2D* h2_RecoRecoilCovMat = new TH2D("h2_RecoRecoilCovMat","Reco Stage Recoil Covariace matrix"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Post.RecoQCDRatioCovMat = new TH2D("SVD_Post.RecoQCDRatioCovMat","Reco QCD ratio Covariace matrix "
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  TH2D* h2_RecoQCDRatioCovMat = new TH2D("h2_RecoQCDRatioCovMat","Reco Stage QCD ratio Covariace matrix"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Post.RecoBckgrCovMat = new TH2D("SVD_Post.RecoBckgrCovMat","Reco Stage Bckgr Covariace matrix"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  TH2D* h2_RecoBckgrCovMat = new TH2D("h2_RecoBckgrCovMat","Reco Stage Bckgr Covariace matrix"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  TH2D* h2_dUnfCovMat = new TH2D("h2_dUnfCovMat","Det Unf Stage Covariace matrix"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  TH2D* h2_PostEffCorrCovMat = new TH2D("h2_PostEffCorrCovMat","Post EffCorr Covariace matrix"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  TH2D* h2_FSRUnfCovMat = new TH2D("h2_FSRUnfCovMat","FSR Unf Stage Covariace matrix"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  TH2D* h2_BornEffCorrCovMat = new TH2D("h2_BornEffCorrCovMat","Born EffCorr Covariace matrix"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  
  // Define Correlation Histo
  SVD_Post.RecoStatisticCorrMat = new TH2D("SVD_Post.RecoStatisticCorrMat","Reco Stage Statistic Correlation matrix"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Post.RecoEffiCorrMat = new TH2D("SVD_Post.RecoEffiCorrMat","Reco Stage Effi Correlation matrix"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  TH2D* h2_RecoEffiCorrMat = new TH2D("h2_RecoEffiCorrMat","Reco Stage Effi Correlation matrix"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Post.RecoScaleCorrMat = new TH2D("SVD_Post.RecoScaleCorrMat","Reco Stage Scale Correlation matrix"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  TH2D* h2_RecoScaleCorrMat = new TH2D("h2_RecoScaleCorrMat","Reco Stage Scale Correlation matrix"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Post.RecoSmearCorrMat = new TH2D("SVD_Post.RecoSmearCorrMat","Reco Stage Smear Correlation matrix"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  TH2D* h2_RecoSmearCorrMat = new TH2D("h2_RecoSmearCorrMat","Reco Stage Smear Correlation matrix"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Post.RecoRecoilCorrMat = new TH2D("SVD_Post.RecoRecoilCorrMat","Reco Stage Recoil Correlation matrix"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  TH2D* h2_RecoRecoilCorrMat = new TH2D("h2_RecoRecoilCorrMat","Reco Stage Recoil Correlation matrix"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Post.RecoQCDRatioCorrMat = new TH2D("SVD_Post.RecoQCDRatioCorrMat","Reco QCD ratio Correlation matrix "
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  TH2D* h2_RecoQCDRatioCorrMat = new TH2D("h2_RecoQCDRatioCorrMat","Reco Stage QCD ratio Correlation matrix"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Post.RecoBckgrCorrMat = new TH2D("SVD_Post.RecoBckgrCorrMat","Reco Stage Bckgr Correlation matrix"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  TH2D* h2_RecoBckgrCorrMat = new TH2D("h2_RecoBckgrCorrMat","Reco Stage Bckgr Correlation matrix"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  TH2D* h2_dUnfCorrMat = new TH2D("h2_dUnfCorrMat","Det Unf Stage Correlation matrix"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  TH2D* h2_PostEffCorrCorrMat = new TH2D("h2_PostEffCorrCorrMat","Post EffCorr Correlation matrix"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  TH2D* h2_FSRUnfCorrMat = new TH2D("h2_FSRUnfCorrMat","FSR Unf Stage Correlation matrix"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  TH2D* h2_BornEffCorrCorrMat = new TH2D("h2_BornEffCorrCorrMat","Born EffCorr Correlation matrix"
      ,NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  
  // Plot
  CPlot *pltRecoStatCov;
  CPlot *pltRecoEffCov;
  CPlot *pltRecoRecoilCov;
  CPlot *pltRecoScaleCov;
  CPlot *pltRecoSmearCov;
  CPlot *pltRecoQCDRatioCov;
  CPlot *pltRecoBckgrCov;
  CPlot *pltdUnfCov;
  CPlot *pltPostEffCorrCov;
  CPlot *pltFSRUnfCov;
  CPlot *pltBornEffCorrCov;
  
  // Plot
  CPlot *pltRecoStatCorr;
  CPlot *pltRecoEffCorr;
  CPlot *pltRecoRecoilCorr;
  CPlot *pltRecoScaleCorr;
  CPlot *pltRecoSmearCorr;
  CPlot *pltRecoQCDRatioCorr;
  CPlot *pltRecoBckgrCorr;
  CPlot *pltdUnfCorr;
  CPlot *pltPostEffCorrCorr;
  CPlot *pltFSRUnfCorr;
  CPlot *pltBornEffCorrCorr;
  
  TCanvas *myCan = MakeCanvas("myCan","myCan",900,800);

  // Histogram from Data
  if(BaseName == "WpToMuNu" || BaseName == "WpToEleNu")
  {
    sprintf(tmpName,"hSigWPpt");
    if (CorrName=="dUnf")
      sprintf(tmpName,"DetUnf");
    if (CorrName=="PostEffCorr")
      sprintf(tmpName,"PostEffCorr");
    if (CorrName=="FSRUnf")
      sprintf(tmpName,"FSRUnf");
    if (CorrName=="BornEffCorr")
      sprintf(tmpName,"BornEffCorr");
    h1_DataSigYield = (TH1D*)f_Data->Get(tmpName)->Clone(tmpName);
  }else if(BaseName == "WmToMuNu" || BaseName == "WmToEleNu")
  {
    sprintf(tmpName,"hSigWMpt");
    if (CorrName=="dUnf")
      sprintf(tmpName,"DetUnf");
    if (CorrName=="PostEffCorr")
      sprintf(tmpName,"PostEffCorr");
    if (CorrName=="FSRUnf")
      sprintf(tmpName,"FSRUnf");
    if (CorrName=="BornEffCorr")
      sprintf(tmpName,"BornEffCorr");
    h1_DataSigYield = (TH1D*)f_Data->Get(tmpName)->Clone(tmpName);
  }else{
    cout<<"Error: Check the BaseName !!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
    exit(-1);
  }
  
  for(int i(1);i<=NWptBinPlus-1;i++)
  {
    SVD_Post.RecoStatisticCovMat -> SetBinContent(i,h1_DataSigYield->GetBinContent(i));
    SVD_Post.RecoStatisticCovMat -> SetBinError(i,h1_DataSigYield->GetBinError(i));
    SVD_Post.RecoStatisticCorrMat -> SetBinContent(i,h1_DataSigYield->GetBinContent(i));
    SVD_Post.RecoStatisticCorrMat -> SetBinError(i,h1_DataSigYield->GetBinError(i));
  }
   
  // Histogram from Correction
  for(int i(1); i<=NumOfSamples; i++)
  {
    if( BaseName == "WpToEleNu" || BaseName == "WpToMuNu")
    {
      sprintf(tmpName,"hSigWPpt_%d",i);	//For Muon channel use this line
      //sprintf(tmpName,"hSigWPpt%d",i);		//For Electron channel use this line
      h1_ToyYield[i]	=(TH1D*)f_DataYield->Get(tmpName)->Clone(tmpName);
    }else if( BaseName == "WmToEleNu" || BaseName == "WmToMuNu"){
      sprintf(tmpName,"hSigWMpt_%d",i);	//For Muon channel use this line
      //sprintf(tmpName,"hSigWMpt%d",i);		//For Electron channel use this line
      h1_ToyYield[i]	=(TH1D*)f_DataYield->Get(tmpName)->Clone(tmpName);
    }else{
      cout<<"Error: Check the HistoName in DataYieldFile !!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
      exit(-1);
    }
  }
  
  for( int i(0); i< NWptBinPlus-1; i++)
  {
    for( int k(0); k<NumOfSamples; k++)
    {
      Xcontent[i][k]= h1_ToyYield[k+1]->GetBinContent(i+1) ;
      //cout<<"Xcontent[i][k]:  "<<"  i =  "<<i<<" k =  "<<k<<"  "<<Xcontent[i][k]<<endl;
      
      XMean[i]=h1_DataSigYield->GetBinContent(i+1);
      //XMean[i]=XMean[i]+Xcontent[i][k]/NumOfSamples;
    }
  }
  
  for( int i(0); i< NWptBinPlus-1; i++)
  {
    for( int j(0); j< NWptBinPlus-1; j++)
    {
      for( int k(1); k<= NumOfSamples; k++)
      {
	XMeanMinusXBinContSumTwo[i+1][j+1] = XMeanMinusXBinContSumTwo[i+1][j+1] + (XMean[i]- Xcontent[i][k-1] )*( XMean[j] - Xcontent[j][k-1])/NumOfSamples;
	//cout<<i+1<<",\t"<<j+1<<",\t"<<XMeanMinusXBinContSumTwo[i+1][j+1]<<endl;
      }
    }
  }
  for( int i(0); i< NWptBinPlus-1; i++)
  {
    for( int j(0); j< NWptBinPlus-1; j++)
    {
      CorrMatrix[i+1][j+1] = XMeanMinusXBinContSumTwo[i+1][j+1]/TMath::Sqrt(XMeanMinusXBinContSumTwo[i+1][i+1]*XMeanMinusXBinContSumTwo[j+1][j+1]);
      //cout << "CorrMatrix" << i+1 << j+1 << CorrMatrix[i+1][j+1] <<endl;
    }
  }
  
  for( int i(1); i<= h1_DataSigYield->GetNbinsX(); i++)
  {
    for( int j(1); j<= h1_DataSigYield->GetNbinsX(); j++)
    {
      if (i==j)
      {
	SVD_Post.RecoStatisticCovMat->SetBinContent(i,i, h1_DataSigYield->GetBinError(i)*h1_DataSigYield->GetBinError(i)   );
	SVD_Post.RecoStatisticCorrMat->SetBinContent(i,i, h1_DataSigYield->GetBinError(i)*h1_DataSigYield->GetBinError(i)   );
      }
      else
      {
	SVD_Post.RecoStatisticCovMat->SetBinContent(i,j, 0.,0. );
	SVD_Post.RecoStatisticCorrMat->SetBinContent(i,j, 0.,0. );
      }
      if (CorrName=="EffCorr")
	h2_RecoEffiCovMat->SetBinContent(i,j, XMeanMinusXBinContSumTwo[i][j]);
	h2_RecoEffiCorrMat->SetBinContent(i,j, CorrMatrix[i][j]);
      if (CorrName=="RecoilCorr")
	h2_RecoRecoilCovMat->SetBinContent(i,j, XMeanMinusXBinContSumTwo[i][j]);
	h2_RecoRecoilCorrMat->SetBinContent(i,j, CorrMatrix[i][j]);
      if (CorrName=="ScaleCorr")
      {
	h2_RecoScaleCovMat->SetBinContent(i,j, XMeanMinusXBinContSumTwo[i][j]);
	h2_RecoScaleCorrMat->SetBinContent(i,j, CorrMatrix[i][j]);
      }
      if (CorrName=="SmearCorr")
	h2_RecoSmearCovMat->SetBinContent(i,j, XMeanMinusXBinContSumTwo[i][j]);
	h2_RecoSmearCorrMat->SetBinContent(i,j, CorrMatrix[i][j]);
      if (CorrName=="QCDratio")
	if (i<9 || j<9)
	  h2_RecoQCDRatioCovMat->SetBinContent(i,j, 0.);
	else{
	  h2_RecoQCDRatioCovMat->SetBinContent(i,j, XMeanMinusXBinContSumTwo[i][j]);
	  h2_RecoSmearCorrMat->SetBinContent(i,j, CorrMatrix[i][j]);
	};
      if (CorrName=="Bckgr")
      {
	h2_RecoBckgrCovMat->SetBinContent(i,j, XMeanMinusXBinContSumTwo[i][j]);
	h2_RecoBckgrCorrMat->SetBinContent(i,j, CorrMatrix[i][j]);
      }
      if (CorrName=="dUnf")
      {
	h2_dUnfCovMat->SetBinContent(i,j, XMeanMinusXBinContSumTwo[i][j]);
	h2_dUnfCorrMat->SetBinContent(i,j, CorrMatrix[i][j]);
      }
      if (CorrName=="PostEffCorr")
      {
	h2_PostEffCorrCovMat->SetBinContent(i,j, XMeanMinusXBinContSumTwo[i][j]);
	h2_PostEffCorrCorrMat->SetBinContent(i,j, CorrMatrix[i][j]);
      }
      if (CorrName=="FSRUnf")
      {
	h2_FSRUnfCovMat->SetBinContent(i,j, XMeanMinusXBinContSumTwo[i][j]);
	h2_FSRUnfCorrMat->SetBinContent(i,j, CorrMatrix[i][j]);
      }
      if (CorrName=="BornEffCorr")
      {
	h2_BornEffCorrCovMat->SetBinContent(i,j, XMeanMinusXBinContSumTwo[i][j]);
	h2_BornEffCorrCorrMat->SetBinContent(i,j, CorrMatrix[i][j]);
      }
    }
  }
  if (CorrName=="EffCorr")
  {
    h2_RecoEffiCovMat->Write();
    h2_RecoEffiCorrMat->Write();
  }
   if (CorrName=="RecoilCorr")
   {
    h2_RecoRecoilCovMat->Write();
    h2_RecoRecoilCorrMat->Write();
   }
  if (CorrName=="ScaleCorr")
  {
    h2_RecoScaleCovMat->Write();
    h2_RecoScaleCorrMat->Write();
  }
  if (CorrName=="SmearCorr")
  {
    h2_RecoSmearCovMat->Write();
    h2_RecoSmearCorrMat->Write();
  }
  if (CorrName=="QCDratio")
  {
    h2_RecoQCDRatioCovMat->Write();
    h2_RecoQCDRatioCorrMat->Write();
  }
  if (CorrName=="Bckgr")
  {
    h2_RecoBckgrCovMat->Write();
    h2_RecoBckgrCorrMat->Write();
  }
  if (CorrName=="dUnf")
  {
    h2_dUnfCovMat->Write();
    h2_dUnfCorrMat->Write();
  }
  if (CorrName=="PostEffCorr")
  {
    h2_PostEffCorrCovMat->Write();
    h2_PostEffCorrCorrMat->Write();
  }
  if (CorrName=="FSRUnf")
  {
    h2_FSRUnfCovMat->Write();
    h2_FSRUnfCovMat->Write();
  }
  if (CorrName=="BornEffCorr")
  {
    h2_BornEffCorrCovMat->Write();
    h2_BornEffCorrCorrMat->Write();
  }
  
  SVD_Post.RecoEffiCovMat     = (TH2D*)h2_RecoEffiCovMat     -> Clone();
  SVD_Post.RecoRecoilCovMat   = (TH2D*)h2_RecoRecoilCovMat   -> Clone();
  SVD_Post.RecoScaleCovMat    = (TH2D*)h2_RecoScaleCovMat    -> Clone();
  SVD_Post.RecoSmearCovMat    = (TH2D*)h2_RecoSmearCovMat    -> Clone();
  SVD_Post.RecoQCDRatioCovMat = (TH2D*)h2_RecoQCDRatioCovMat -> Clone();
  SVD_Post.RecoBckgrCovMat    = (TH2D*)h2_RecoBckgrCovMat    -> Clone();
  SVD_Post.dUnfCovMat	      = (TH2D*)h2_dUnfCovMat	     -> Clone();
  SVD_Post.PostEffCorrCovMat  = (TH2D*)h2_PostEffCorrCovMat  -> Clone();
  SVD_Post.FSRUnfCovMat	      = (TH2D*)h2_FSRUnfCovMat	     -> Clone();
  SVD_Post.BornEffCorrCovMat  = (TH2D*)h2_BornEffCorrCovMat  -> Clone();
  
  SVD_Post.RecoEffiCorrMat     = (TH2D*)h2_RecoEffiCorrMat     -> Clone();
  SVD_Post.RecoRecoilCorrMat   = (TH2D*)h2_RecoRecoilCorrMat   -> Clone();
  SVD_Post.RecoScaleCorrMat    = (TH2D*)h2_RecoScaleCorrMat    -> Clone();
  SVD_Post.RecoSmearCorrMat    = (TH2D*)h2_RecoSmearCorrMat    -> Clone();
  SVD_Post.RecoQCDRatioCorrMat = (TH2D*)h2_RecoQCDRatioCorrMat -> Clone();
  SVD_Post.RecoBckgrCorrMat    = (TH2D*)h2_RecoBckgrCorrMat    -> Clone();
  SVD_Post.dUnfCorrMat	      = (TH2D*)h2_dUnfCorrMat	     -> Clone();
  SVD_Post.PostEffCorrCorrMat  = (TH2D*)h2_PostEffCorrCorrMat  -> Clone();
  SVD_Post.FSRUnfCorrMat	      = (TH2D*)h2_FSRUnfCorrMat	     -> Clone();
  SVD_Post.BornEffCorrCorrMat  = (TH2D*)h2_BornEffCorrCorrMat  -> Clone();

  //Statistic Covariance Matrix
  gStyle->SetPaintTextFormat("4.2f"); 
  if (CorrName == "Recoil" || CorrName == "BornEffCorr"){
  tmpTStr = "RecoStatCovMat_"+BaseName;
  pltRecoStatCov = new CPlot(tmpTStr,"Recon Statistic Covariance Matrix","","");
  pltRecoStatCov -> setOutDir(resultDir);
  gPad->SetLogz(0);
  SVD_Post.RecoStatisticCovMat -> SetMarkerSize(0.8);
  pltRecoStatCov->AddHist2D(SVD_Post.RecoStatisticCovMat,"COLTEXTZ",kWhite,kBlack);
  pltRecoStatCov-> Draw(myCan,kTRUE,"png");
  tmpTStr = "RecoStatCorrMat_"+BaseName;
  pltRecoStatCorr = new CPlot(tmpTStr,"Recon Statistic Corelation Matrix","","");
  pltRecoStatCorr -> setOutDir(resultDir);
  SVD_Post.RecoStatisticCorrMat -> SetMarkerSize(0.8);
  pltRecoStatCorr->AddHist2D(SVD_Post.RecoStatisticCorrMat,"COLTEXTZ",kWhite,kBlack);
  pltRecoStatCorr-> Draw(myCan,kTRUE,"png");
  }
  if (CorrName == "EffCorr"){
//Lepton Efficiency Correction Covariance Matrix
  tmpTStr = "RecoEffiCovMat_"+BaseName;
  pltRecoEffCov = new CPlot(tmpTStr,"Recon EffCorr Covariance Matrix","","");
  pltRecoEffCov -> setOutDir(resultDir);
  gPad->SetLogz(0);
  SVD_Post.RecoEffiCovMat -> SetMarkerSize(0.8);
  pltRecoEffCov->AddHist2D(SVD_Post.RecoEffiCovMat,"COLTEXTZ",kWhite,kBlack);
  pltRecoEffCov->Draw(myCan,kTRUE,"png");
  tmpTStr = "RecoEffiCorrMat_"+BaseName;
  pltRecoEffCorr = new CPlot(tmpTStr,"Recon EffCorr Corelation Matrix","","");
  pltRecoEffCorr -> setOutDir(resultDir);
  SVD_Post.RecoEffiCorrMat -> SetMarkerSize(0.8);
  pltRecoEffCorr->AddHist2D(SVD_Post.RecoEffiCorrMat,"COLTEXTZ",kWhite,kBlack);
  pltRecoEffCorr->Draw(myCan,kTRUE,"png");
  }
//Recoil Correction Covariance Matrix
  if (CorrName == "RecoilCorr"){
  tmpTStr = "RecoRecoilCovMat_"+BaseName;
  pltRecoRecoilCov = new CPlot(tmpTStr,"Recon RecoilCorr Covariance Matrix","","");
  pltRecoRecoilCov -> setOutDir(resultDir);
  gPad->SetLogz(0);
  SVD_Post.RecoRecoilCovMat -> SetMarkerSize(0.8);
  pltRecoRecoilCov->AddHist2D(SVD_Post.RecoRecoilCovMat,"COLTEXTZ",kWhite,kBlack);
  pltRecoRecoilCov-> Draw(myCan,kTRUE,"png");
  tmpTStr = "RecoRecoilCorrMat_"+BaseName;
  pltRecoRecoilCorr = new CPlot(tmpTStr,"Recon RecoilCorr Corelation Matrix","","");
  pltRecoRecoilCorr -> setOutDir(resultDir);
  SVD_Post.RecoRecoilCorrMat -> SetMarkerSize(0.8);
  pltRecoRecoilCorr->AddHist2D(SVD_Post.RecoRecoilCorrMat,"COLTEXTZ",kWhite,kBlack);
  pltRecoRecoilCorr-> Draw(myCan,kTRUE,"png");
  }
  if (CorrName == "SmearCorr"){
//Smear Correction Covariance Matrix
  tmpTStr = "RecoSmearCovMat_"+BaseName;
  pltRecoSmearCov = new CPlot(tmpTStr,"Recon SmearCorr Covariance Matrix","","");
  pltRecoSmearCov -> setOutDir(resultDir);
  gPad->SetLogz(0);
  SVD_Post.RecoSmearCovMat -> SetMarkerSize(0.8);
  pltRecoSmearCov->AddHist2D(SVD_Post.RecoSmearCovMat,"COLTEXTZ",kWhite,kBlack);
  pltRecoSmearCov-> Draw(myCan,kTRUE,"png");
  tmpTStr = "RecoSmearCorrMat_"+BaseName;
  pltRecoSmearCorr = new CPlot(tmpTStr,"Recon SmearCorr Correlation Matrix","","");
  pltRecoSmearCorr -> setOutDir(resultDir);
  gPad->SetLogz(0);
  SVD_Post.RecoSmearCorrMat -> SetMarkerSize(0.8);
  pltRecoSmearCorr->AddHist2D(SVD_Post.RecoSmearCorrMat,"COLTEXTZ",kWhite,kBlack);
  pltRecoSmearCorr-> Draw(myCan,kTRUE,"png");
  }

  if(BaseName == "WpToMuNu" || BaseName == "WmToMuNu" ){
    //QCD Signal Ratio Correction Covariance Matrix
  if (CorrName == "QCDratio"){
    tmpTStr = "RecoQCDRatioCovMat_"+BaseName;
    pltRecoQCDRatioCov = new CPlot(tmpTStr,"Recon QCDSignalRatio Covariance Matrix","","");
    pltRecoQCDRatioCov -> setOutDir(resultDir);
    gPad->SetLogz(0);
    SVD_Post.RecoQCDRatioCovMat -> SetMarkerSize(0.8);
    pltRecoQCDRatioCov -> AddHist2D(SVD_Post.RecoQCDRatioCovMat,"COLTEXTZ",kWhite,kBlack);
    pltRecoQCDRatioCov -> Draw(myCan,kTRUE,"png");
    tmpTStr = "RecoQCDRatioCorrMat_"+BaseName;
    pltRecoQCDRatioCorr = new CPlot(tmpTStr,"Recon QCDSignalRatio Correlation Matrix","","");
    pltRecoQCDRatioCorr -> setOutDir(resultDir);
    SVD_Post.RecoQCDRatioCorrMat -> SetMarkerSize(0.8);
    pltRecoQCDRatioCorr -> AddHist2D(SVD_Post.RecoQCDRatioCorrMat,"COLTEXTZ",kWhite,kBlack);
    pltRecoQCDRatioCorr -> Draw(myCan,kTRUE,"png");
  }
  }else if(BaseName == "WpToEleNu" || BaseName == "WmToEleNu" ){
  if (CorrName == "ScaleCorr"){
    tmpTStr = "RecoScaleCovMat_"+BaseName;
    pltRecoScaleCov = new CPlot(tmpTStr,"Recon Scale Covariance Matrix","","");
    pltRecoScaleCov->setOutDir(resultDir);
    gPad->SetLogz();
    SVD_Post.RecoScaleCovMat -> SetMarkerSize(0.8);
    pltRecoScaleCov->AddHist2D(SVD_Post.RecoScaleCovMat,"COLTEXTZ",kWhite,kBlack);
    pltRecoScaleCov->Draw(myCan,kTRUE,"png");
    tmpTStr = "RecoScaleCorrMat_"+BaseName;
    pltRecoScaleCorr = new CPlot(tmpTStr,"Recon Scale Correlation Matrix","","");
    pltRecoScaleCorr->setOutDir(resultDir);
    SVD_Post.RecoScaleCorrMat -> SetMarkerSize(0.8);
    pltRecoScaleCorr->AddHist2D(SVD_Post.RecoScaleCorrMat,"COLTEXTZ",kWhite,kBlack);
    pltRecoScaleCorr->Draw(myCan,kTRUE,"png");
  }
  }
//QCD Bckgr Covariance Matrix
  if (CorrName == "Bckg"){
  tmpTStr = "RecoBckgrCovMat_"+BaseName;
  pltRecoBckgrCov = new CPlot(tmpTStr,"Recon Bckgr Covariance Matrix","","");
  pltRecoBckgrCov -> setOutDir(resultDir);
  gPad->SetLogz(0);
  SVD_Post.RecoBckgrCovMat -> SetMarkerSize(0.8);
  pltRecoBckgrCov->AddHist2D(SVD_Post.RecoBckgrCovMat,"COLTEXTZ",kWhite,kBlack);
  pltRecoBckgrCov->Draw(myCan,kTRUE,"png");
  tmpTStr = "RecoBckgrCovMat_"+BaseName;
  pltRecoBckgrCorr = new CPlot(tmpTStr,"Recon Bckgr Correlation Matrix","","");
  pltRecoBckgrCorr -> setOutDir(resultDir);
  SVD_Post.RecoBckgrCorrMat -> SetMarkerSize(0.8);
  pltRecoBckgrCorr->AddHist2D(SVD_Post.RecoBckgrCorrMat,"COLTEXTZ",kWhite,kBlack);
  pltRecoBckgrCorr->Draw(myCan,kTRUE,"png");
  }
  if (CorrName=="dUnf"){
//dUnf Covariance Matrix
  tmpTStr = "dUnfCovMat_"+BaseName;
  pltdUnfCov = new CPlot(tmpTStr,"Det Unf Covariance Matrix","","");
  pltdUnfCov -> setOutDir(resultDir);
  gPad->SetLogz(0);
  SVD_Post.dUnfCovMat -> SetMarkerSize(0.8);
  pltdUnfCov->AddHist2D(SVD_Post.dUnfCovMat,"COLTEXTZ",kWhite,kBlack);
  pltdUnfCov-> Draw(myCan,kTRUE,"png");
  tmpTStr = "dUnfCorrMat_"+BaseName;
  pltdUnfCorr = new CPlot(tmpTStr,"Det Unf Corelation Matrix","","");
  pltdUnfCorr -> setOutDir(resultDir);
  SVD_Post.dUnfCorrMat -> SetMarkerSize(0.8);
  pltdUnfCorr->AddHist2D(SVD_Post.dUnfCorrMat,"COLTEXTZ",kWhite,kBlack);
  pltdUnfCorr-> Draw(myCan,kTRUE,"png");
  }

  else if (CorrName=="PostEffCorr"){
//PostEffCorr Covariance Matrix
  tmpTStr = "PostEffCorrCovMat_"+BaseName;
  pltPostEffCorrCov = new CPlot(tmpTStr,"Post EffCorr Covariance Matrix","","");
  pltPostEffCorrCov -> setOutDir(resultDir);
  gPad->SetLogz(0);
  SVD_Post.PostEffCorrCovMat -> SetMarkerSize(0.8);
  pltPostEffCorrCov->AddHist2D(SVD_Post.PostEffCorrCovMat,"COLTEXTZ",kWhite,kBlack);
  pltPostEffCorrCov-> Draw(myCan,kTRUE,"png");
  tmpTStr = "PostEffCorrCovMat_"+BaseName;
  pltPostEffCorrCorr = new CPlot(tmpTStr,"Post EffCorr Corelation Matrix","","");
  pltPostEffCorrCorr -> setOutDir(resultDir);
  SVD_Post.PostEffCorrCorrMat -> SetMarkerSize(0.8);
  pltPostEffCorrCorr->AddHist2D(SVD_Post.PostEffCorrCorrMat,"COLTEXTZ",kWhite,kBlack);
  pltPostEffCorrCorr-> Draw(myCan,kTRUE,"png");
  }

//FSR Covariance Matrix
  else if (CorrName=="FSRUnf"){
  tmpTStr = "FSRUnfCovMat_"+BaseName;
  pltFSRUnfCov = new CPlot(tmpTStr,"FSR Unf Covariance Matrix","","");
  pltFSRUnfCov -> setOutDir(resultDir);
  gPad->SetLogz(0);
  SVD_Post.FSRUnfCovMat -> SetMarkerSize(0.8);
  pltFSRUnfCov->AddHist2D(SVD_Post.FSRUnfCovMat,"COLTEXTZ",kWhite,kBlack);
  pltFSRUnfCov-> Draw(myCan,kTRUE,"png");
  tmpTStr = "FSRUnfCorrMat_"+BaseName;
  pltFSRUnfCorr = new CPlot(tmpTStr,"FSR Unf Corelation Matrix","","");
  pltFSRUnfCorr -> setOutDir(resultDir);
  SVD_Post.FSRUnfCorrMat -> SetMarkerSize(0.8);
  pltFSRUnfCorr->AddHist2D(SVD_Post.FSRUnfCorrMat,"COLTEXTZ",kWhite,kBlack);
  pltFSRUnfCorr-> Draw(myCan,kTRUE,"png");
  }

//BornEffCorr Covariance Matrix
  else if (CorrName=="BornEffCorr"){
  tmpTStr = "BornEffCorrCovMat_"+BaseName;
  pltBornEffCorrCov = new CPlot(tmpTStr,"Born EffCorr Covariance Matrix","","");
  pltBornEffCorrCov -> setOutDir(resultDir);
  gPad->SetLogz(0);
  SVD_Post.BornEffCorrCovMat -> SetMarkerSize(0.8);
  pltBornEffCorrCov->AddHist2D(SVD_Post.BornEffCorrCovMat,"COLTEXTZ",kWhite,kBlack);
  pltBornEffCorrCov-> Draw(myCan,kTRUE,"png");
  tmpTStr = "BornEffCorrCovMat_"+BaseName;
  pltBornEffCorrCorr = new CPlot(tmpTStr,"Born EffCorr Correlation Matrix","","");
  pltBornEffCorrCorr -> setOutDir(resultDir);
  SVD_Post.BornEffCorrCorrMat -> SetMarkerSize(0.8);
  pltBornEffCorrCorr->AddHist2D(SVD_Post.BornEffCorrCovMat,"COLTEXTZ",kWhite,kBlack);
  pltBornEffCorrCorr-> Draw(myCan,kTRUE,"png");
  }

  Fout << "Recoil Reco stage Syst"<< endl;
  Fout << "Bin" << "\t" << "Wpt yield " << "\t\t" << "Cov_i_i" << "\t\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
  Fout << "" << "\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t" << "" << endl;
  for( int i(1);i<=h1_DataSigYield->GetNbinsX(); i++)
  {
    Fout << i << "\t" << h1_DataSigYield->GetBinContent(i) << "\t\t" << SVD_Post.RecoRecoilCovMat->GetBinContent(i,i) << "\t\t"<< TMath::Sqrt(SVD_Post.RecoRecoilCovMat->GetBinContent(i,i)) << "\t\t" << TMath::Sqrt(SVD_Post.RecoRecoilCovMat->GetBinContent(i,i))/h1_DataSigYield->GetBinContent(i)*100 << endl;
  }
  
  Fout << "Effi Reco stage Syst"<< endl;
  Fout <<fixed<<setprecision(4);
  Fout << "Bin" << "\t" << "Wpt yield " << "\t" << "Cov_i_i" << "\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
  Fout << "=============================================================" << endl;
  for( int i(1);i<=h1_DataSigYield->GetNbinsX(); i++)
  {
    Fout << i << "\t" << h1_DataSigYield->GetBinContent(i) << "\t\t" << SVD_Post.RecoEffiCovMat->GetBinContent(i,i) << "\t\t"<< TMath::Sqrt(SVD_Post.RecoEffiCovMat->GetBinContent(i,i)) << "\t\t" << TMath::Sqrt(SVD_Post.RecoEffiCovMat->GetBinContent(i,i))/h1_DataSigYield->GetBinContent(i)*100 << endl;
  }

  Fout << "Smear Reco stage Syst"<< endl;
  Fout << "Bin" << "\t" << "Wpt yield " << "\t\t" << "Cov_i_i" << "\t\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
  Fout << "" << "\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t" << "" << endl;
  for( int i(1);i<=h1_DataSigYield->GetNbinsX(); i++)
  {
    Fout << i << "\t" << h1_DataSigYield->GetBinContent(i) << "\t\t" << SVD_Post.RecoSmearCovMat->GetBinContent(i,i) << "\t\t"<< TMath::Sqrt(SVD_Post.RecoSmearCovMat->GetBinContent(i,i)) << "\t\t" << TMath::Sqrt(SVD_Post.RecoSmearCovMat->GetBinContent(i,i))/h1_DataSigYield->GetBinContent(i)*100 << endl;
  }

  Fout << "dUnf Syst"<< endl;
  Fout << "Bin" << "\t" << "Wpt yield " << "\t\t" << "Cov_i_i" << "\t\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
  Fout << "" << "\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t" << "" << endl;
  for( int i(1);i<=h1_DataSigYield->GetNbinsX(); i++)
  {
    Fout << i << "\t" << h1_DataSigYield->GetBinContent(i) << "\t\t" << SVD_Post.dUnfCovMat->GetBinContent(i,i) << "\t\t"<< TMath::Sqrt(SVD_Post.dUnfCovMat->GetBinContent(i,i)) << "\t\t" << TMath::Sqrt(SVD_Post.dUnfCovMat->GetBinContent(i,i))/h1_DataSigYield->GetBinContent(i)*100 << endl;
  }

  Fout << "Post EffCorr Syst"<< endl;
  Fout << "Bin" << "\t" << "Wpt yield " << "\t\t" << "Cov_i_i" << "\t\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
  Fout << "" << "\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t" << "" << endl;
  for( int i(1);i<=h1_DataSigYield->GetNbinsX(); i++)
  {
    Fout << i << "\t" << h1_DataSigYield->GetBinContent(i) << "\t\t" << SVD_Post.PostEffCorrCovMat->GetBinContent(i,i) << "\t\t"<< TMath::Sqrt(SVD_Post.PostEffCorrCovMat->GetBinContent(i,i)) << "\t\t" << TMath::Sqrt(SVD_Post.PostEffCorrCovMat->GetBinContent(i,i))/h1_DataSigYield->GetBinContent(i)*100 << endl;
  }

  Fout << "FSRUnf Syst"<< endl;
  Fout << "Bin" << "\t" << "Wpt yield " << "\t\t" << "Cov_i_i" << "\t\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
  Fout << "" << "\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t" << "" << endl;
  for( int i(1);i<=h1_DataSigYield->GetNbinsX(); i++)
  {
    Fout << i << "\t" << h1_DataSigYield->GetBinContent(i) << "\t\t" << SVD_Post.FSRUnfCovMat->GetBinContent(i,i) << "\t\t"<< TMath::Sqrt(SVD_Post.FSRUnfCovMat->GetBinContent(i,i)) << "\t\t" << TMath::Sqrt(SVD_Post.FSRUnfCovMat->GetBinContent(i,i))/h1_DataSigYield->GetBinContent(i)*100 << endl;
  }

  Fout << "Born EffCorr Syst"<< endl;
  Fout << "Bin" << "\t" << "Wpt yield " << "\t\t" << "Cov_i_i" << "\t\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
  Fout << "" << "\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t" << "" << endl;
  for( int i(1);i<=h1_DataSigYield->GetNbinsX(); i++)
  {
    Fout << i << "\t" << h1_DataSigYield->GetBinContent(i) << "\t\t" << SVD_Post.BornEffCorrCovMat->GetBinContent(i,i) << "\t\t"<< TMath::Sqrt(SVD_Post.BornEffCorrCovMat->GetBinContent(i,i)) << "\t\t" << TMath::Sqrt(SVD_Post.BornEffCorrCovMat->GetBinContent(i,i))/h1_DataSigYield->GetBinContent(i)*100 << endl;
  }

  if(BaseName == "WpToMuNu" || BaseName == "WmToMuNu" ){
    Fout << "QCDRatio Reco stage"<< endl;
    Fout << "Bin" << "\t" << "Wpt yield " << "\t\t" << "Cov_i_i" << "\t\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
    Fout << "" << "\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t" << "" << endl;
    for( int i(1);i<=h1_DataSigYield->GetNbinsX(); i++)
    {
      Fout << i << "\t" << h1_DataSigYield->GetBinContent(i) << "\t\t" << SVD_Post.RecoQCDRatioCovMat->GetBinContent(i,i) << "\t\t"<< TMath::Sqrt(SVD_Post.RecoQCDRatioCovMat->GetBinContent(i,i)) << "\t\t" << TMath::Sqrt(SVD_Post.RecoQCDRatioCovMat->GetBinContent(i,i))/h1_DataSigYield->GetBinContent(i)*100 << endl;
    }
  }else if (BaseName == "WpToEleNu" || BaseName == "WmToEleNu" ){
    Fout << "Scale Reco stage Syst"<< endl;
    Fout << "Bin" << "\t" << "Wpt yield " << "\t" << "Cov_i_i" << "\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
    Fout << "=============================================================" << endl;
    for( int i(1);i<=h1_DataSigYield->GetNbinsX(); i++)
    {
      Fout << i << "\t" << h1_DataSigYield->GetBinContent(i) << "\t" << SVD_Post.RecoScaleCovMat->GetBinContent(i,i) << "\t"<< TMath::Sqrt(SVD_Post.RecoScaleCovMat->GetBinContent(i,i)) << "\t" << TMath::Sqrt(SVD_Post.RecoScaleCovMat->GetBinContent(i,i))/h1_DataSigYield->GetBinContent(i)*100 << endl;
    }
    
    Fout << "En.Res. Reco stage Syst"<< endl;
    Fout << "Bin" << "\t" << "Wpt yield " << "\t" << "Sqrt(Scale^2+Smear^2)" << endl;
    Fout << "=============================================================" << endl;
    for( int i(1);i<=h1_DataSigYield->GetNbinsX(); i++)
    {
      Fout << i << "\t" << h1_DataSigYield->GetBinContent(i) << "\t" << TMath::Sqrt(TMath::Power(TMath::Sqrt(SVD_Post.RecoScaleCovMat->GetBinContent(i,i)),2) + TMath::Power( TMath::Sqrt(SVD_Post.RecoSmearCovMat->GetBinContent(i,i)),2))/h1_DataSigYield->GetBinContent(i)*100 <<endl;
    }
  }
  
  Fout << "Statistic Reco stage"<< endl;
  Fout << "Bin" << "\t" << "Wpt yield " << "\t\t" << "Cov_i_i" << "\t\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
  Fout << "" << "\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t" << "" << endl;
  for( int i(1);i<=h1_DataSigYield->GetNbinsX(); i++)
  {
    Fout << i << "\t" << h1_DataSigYield->GetBinContent(i) << "\t\t" << SVD_Post.RecoStatisticCovMat->GetBinContent(i,i) << "\t\t"<< TMath::Sqrt(SVD_Post.RecoStatisticCovMat->GetBinContent(i,i)) << "\t\t" << TMath::Sqrt(SVD_Post.RecoStatisticCovMat->GetBinContent(i,i))/h1_DataSigYield->GetBinContent(i)*100 << endl;
  }

  Fout << ""<< endl;
  Fout << ""<< endl;
  Fout << "Systematics "<< endl;
  if(BaseName == "WpToMuNu" || BaseName == "WmToMuNu" )
    Fout << "Bin" << "\t\t"<<"Statistic err"<<"\t\t" << "Lept Recon Effi Syst " << "\t\t" <<  "Smear Syst" << "\t\t" << "Recoil syst" <<  "\t\t" << "QCDvsSignalRaio Syst" <<endl;
  else if(BaseName == "WpToEleNu" || BaseName == "WmToEleNu" )
    Fout << "Bin" << "\t\t"<<"Statistic err"<<"\t\t" << "Lept Recon Effi Syst " << "\t\t" <<  "Smear Syst" << "\t\t" << "Recoil syst" <<  "\t\t" << "Scale Syst" <<endl;
  
  Fout << "" << "\t\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t\t" << "" << "\t\t" << "" << "\t\t" << "" << "\t\t" << "" << endl;
  if(BaseName == "WpToMuNu" || BaseName == "WmToMuNu" )
    for( int i(1);i<=h1_DataSigYield->GetNbinsX(); i++)
    {
      Fout << i << "\t\t" << TMath::Sqrt(SVD_Post.RecoStatisticCovMat->GetBinContent(i,i))/h1_DataSigYield->GetBinContent(i)*100 << "\t\t" << TMath::Sqrt(SVD_Post.RecoEffiCovMat->GetBinContent(i,i))/h1_DataSigYield->GetBinContent(i)*100 << "\t\t"<< TMath::Sqrt(SVD_Post.RecoSmearCovMat->GetBinContent(i,i))/h1_DataSigYield->GetBinContent(i)*100 << "\t\t"<< TMath::Sqrt(SVD_Post.RecoRecoilCovMat->GetBinContent(i,i))/h1_DataSigYield->GetBinContent(i)*100 << "\t\t" << TMath::Sqrt(SVD_Post.RecoQCDRatioCovMat->GetBinContent(i,i))/h1_DataSigYield->GetBinContent(i)*100 << endl;
    }
  else if(BaseName == "WpToEleNu" || BaseName == "WmToEleNu" )
    for( int i(1);i<=h1_DataSigYield->GetNbinsX(); i++)
    {
      Fout << i << "\t\t" << TMath::Sqrt(SVD_Post.RecoStatisticCovMat->GetBinContent(i,i))/h1_DataSigYield->GetBinContent(i)*100 << "\t\t" << TMath::Sqrt(SVD_Post.RecoEffiCovMat->GetBinContent(i,i))/h1_DataSigYield->GetBinContent(i)*100 << "\t\t"<< TMath::Sqrt(SVD_Post.RecoSmearCovMat->GetBinContent(i,i))/h1_DataSigYield->GetBinContent(i)*100 << "\t\t"<< TMath::Sqrt(SVD_Post.RecoRecoilCovMat->GetBinContent(i,i))/h1_DataSigYield->GetBinContent(i)*100 <<TMath::Sqrt(SVD_Post.RecoScaleCovMat->GetBinContent(i,i))/h1_DataSigYield->GetBinContent(i)*100 << endl;
    }
  
  Fout << ""<< endl;
  
  Fout << "QCD Bckgr Syst"<< endl;
  Fout <<fixed<<setprecision(4);
  Fout << "Bin" << "\t" << "Wpt yield " << "\t" << "Cov_i_i" << "\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
  Fout << "=============================================================" << endl;
  for( int i(1);i<=h1_DataSigYield->GetNbinsX(); i++)
  {
    Fout << i << "\t" << h1_DataSigYield->GetBinContent(i) << "\t\t" << SVD_Post.RecoBckgrCovMat->GetBinContent(i,i) << "\t\t"<< TMath::Sqrt(SVD_Post.RecoBckgrCovMat->GetBinContent(i,i)) << "\t\t" << TMath::Sqrt(SVD_Post.RecoBckgrCovMat->GetBinContent(i,i))/h1_DataSigYield->GetBinContent(i)*100 << endl;
  }

  Fout << ""<< endl;
  Fout << ""<< endl;
  Fout << "Total Systematics - Reconstruction stage"<< endl;
  if(BaseName == "WpToMuNu" || BaseName == "WmToMuNu" )
    Fout <<  "\t\t"<< "Sqrt(LeptRecEff^2 +  Smear^2 +Recoil^2 +QCDvsSignalRatio^2) "<<endl;
  else if(BaseName == "WpToEleNu" || BaseName == "WmToEleNu" )
    Fout <<  "\t\t"<< "Sqrt(LeptRecEff^2 + Scale^2 + Smear^2 +Recoil^2) "<<endl;
  
  Fout << "" << "\t\t" << " " << "\t\t" << ""  << endl;
  if(BaseName == "WpToMuNu" || BaseName == "WmToMuNu" )
    for( int i(1);i<=h1_DataSigYield->GetNbinsX(); i++)
    {
      Fout << TMath::Sqrt( TMath::Power(TMath::Sqrt(SVD_Post.RecoEffiCovMat->GetBinContent(i,i)),2)+ TMath::Power( TMath::Sqrt(SVD_Post.RecoSmearCovMat->GetBinContent(i,i)),2) + TMath::Power(TMath::Sqrt(SVD_Post.RecoRecoilCovMat->GetBinContent(i,i)),2)+ TMath::Power( TMath::Sqrt(SVD_Post.RecoQCDRatioCovMat->GetBinContent(i,i)),2))/h1_DataSigYield->GetBinContent(i)*100 <<endl;
    }
  else if(BaseName == "WpToEleNu" || BaseName == "WmToEleNu" )
    for( int i(1);i<=h1_DataSigYield->GetNbinsX(); i++)
    {
      Fout << TMath::Sqrt( TMath::Power(TMath::Sqrt(SVD_Post.RecoEffiCovMat->GetBinContent(i,i)),2)+ TMath::Power( TMath::Sqrt(SVD_Post.RecoSmearCovMat->GetBinContent(i,i)),2) + TMath::Power(TMath::Sqrt(SVD_Post.RecoRecoilCovMat->GetBinContent(i,i)),2)+ TMath::Power( TMath::Sqrt(SVD_Post.RecoScaleCovMat->GetBinContent(i,i)),2))/h1_DataSigYield->GetBinContent(i)*100 <<endl;
    }
  return 0;
}
