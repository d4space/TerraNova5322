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
  TH1D* YMeanMinusYBinCont[NumOfSamples];
  
  TH1D* h1_Data_SigYild;
  TH1D* h1_Data_Yield[NumOfSamples+1];
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
  
  // Plot
  CPlot *pltRecoStatCov;
  CPlot *pltRecoEffCov;
  CPlot *pltRecoRecoilCov;
  CPlot *pltRecoScaleCov;
  CPlot *pltRecoSmearCov;
  CPlot *pltRecoQCDRatioCov;
  
  TCanvas *myCan = MakeCanvas("myCan","myCan",900,800);

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
  
  for(int i(1);i<=NWptBinPlus-1;i++)
  {
    SVD_Post.RecoStatisticCovMat -> SetBinContent(i,h1_Data_SigYild->GetBinContent(i));
    SVD_Post.RecoStatisticCovMat -> SetBinError(i,h1_Data_SigYild->GetBinError(i));
  }
  
  cout<<"Checking 1"<<endl;
  
  // Histogram from Correction
  for(int i(1); i<=NumOfSamples; i++)
  {
    if( BaseName == "WpToEleNu" || BaseName == "WpToMuNu")
    {
      //sprintf(tmpName,"hSigWPpt_%d",i);	//For Muon channel use this line
      sprintf(tmpName,"hSigWPpt%d",i);		//For Electron channel use this line
      h1_Data_Yield[i]	=(TH1D*)f_DataYield->Get(tmpName)->Clone(tmpName);
    }else if( BaseName == "WmToEleNu" || BaseName == "WmToMuNu"){
      //sprintf(tmpName,"hSigWMpt_%d",i);	//For Muon channel use this line
      sprintf(tmpName,"hSigWMpt%d",i);		//For Electron channel use this line
      h1_Data_Yield[i]	=(TH1D*)f_DataYield->Get(tmpName)->Clone(tmpName);
    }else{
      cout<<"Error: Check the HistoName in DataYieldFile !!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
      exit(-1);
    }
  }
  cout<<"Checking 2"<<endl;
  
  for( int i(0); i< NWptBinPlus-1; i++)
  {
    for( int k(0); k<NumOfSamples; k++)
    {
      Xcontent[i][k]= h1_Data_Yield[k+1]->GetBinContent(i+1) ;
      //cout<<"Xcontent[i][k]:  "<<"  i =  "<<i<<" k =  "<<k<<"  "<<Xcontent[i][k]<<endl;
      
      //XMean[i]=h1_Data_SigYild->GetBinContent(i+1);
      XMean[i]=XMean[i]+Xcontent[i][k]/NumOfSamples;
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
  
  for( int i(1); i<= h1_Data_SigYild->GetNbinsX(); i++)
  {
    for( int j(1); j<= h1_Data_SigYild->GetNbinsX(); j++)
    {
      if (i==j)
	SVD_Post.RecoStatisticCovMat->SetBinContent(i,i, h1_Data_SigYild->GetBinError(i)*h1_Data_SigYild->GetBinError(i)   );
      else
	SVD_Post.RecoStatisticCovMat->SetBinContent(i,j, 0.,0. );
      if (CorrName=="EffCorr")
	h2_RecoEffiCovMat->SetBinContent(i,j, XMeanMinusXBinContSumTwo[i][j]);
      if (CorrName=="RecoilCorr")
	h2_RecoRecoilCovMat->SetBinContent(i,j, XMeanMinusXBinContSumTwo[i][j]);
      if (CorrName=="ScaleCorr")
	h2_RecoScaleCovMat->SetBinContent(i,j, XMeanMinusXBinContSumTwo[i][j]);
      if (CorrName=="SmearCorr")
	h2_RecoSmearCovMat->SetBinContent(i,j, XMeanMinusXBinContSumTwo[i][j]);
      if (CorrName=="QCDratio")
	if (i<9 || j<9)
	  h2_RecoQCDRatioCovMat->SetBinContent(i,j, 0.);
	else
	  h2_RecoQCDRatioCovMat->SetBinContent(i,j, XMeanMinusXBinContSumTwo[i][j]);
    }
  }
  if (CorrName=="EffCorr")
    h2_RecoEffiCovMat->Write();
  if (CorrName=="RecoilCorr")
    h2_RecoRecoilCovMat->Write();
  if (CorrName=="ScaleCorr")
    h2_RecoScaleCovMat->Write();
  if (CorrName=="SmearCorr")
    h2_RecoSmearCovMat->Write();
  if (CorrName=="QCDratio")
    h2_RecoQCDRatioCovMat->Write();
  
  SVD_Post.RecoEffiCovMat     = (TH2D*)h2_RecoEffiCovMat     -> Clone();
  SVD_Post.RecoRecoilCovMat   = (TH2D*)h2_RecoRecoilCovMat   -> Clone();
  SVD_Post.RecoScaleCovMat    = (TH2D*)h2_RecoScaleCovMat    -> Clone();
  SVD_Post.RecoSmearCovMat    = (TH2D*)h2_RecoSmearCovMat    -> Clone();
  SVD_Post.RecoQCDRatioCovMat = (TH2D*)h2_RecoQCDRatioCovMat -> Clone();
  
//Statistic Covariance Matrix
  gStyle->SetPaintTextFormat("4.2f"); 
  tmpTStr = "RecoStatCovMat_"+BaseName;
  pltRecoStatCov = new CPlot(tmpTStr,"Recon Statistic Covariance Matrix","","");
  pltRecoStatCov -> setOutDir(resultDir);
  gPad->SetLogz(0);
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
    SVD_Post.RecoScaleCovMat -> SetMarkerSize(0.8);
    pltRecoScaleCov->AddHist2D(SVD_Post.RecoScaleCovMat,"COLTEXTZ",kWhite,kBlack);
    pltRecoScaleCov->Draw(myCan,kTRUE,"png");
  }

  Fout << "Recoil Reco stage Syst"<< endl;
  Fout << "Bin" << "\t" << "Wpt yield " << "\t\t" << "Cov_i_i" << "\t\t" << "Err" << "\t" << "Err/Wpt(%)" << endl;
  Fout << "" << "\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t" << "" << endl;
  for( int i(1);i<=h1_Data_SigYild->GetNbinsX(); i++)
  {
    Fout << i << "\t" << h1_Data_SigYild->GetBinContent(i) << "\t\t" << SVD_Post.RecoRecoilCovMat->GetBinContent(i,i) << "\t\t"<< TMath::Sqrt(SVD_Post.RecoRecoilCovMat->GetBinContent(i,i)) << "\t\t" << TMath::Sqrt(SVD_Post.RecoRecoilCovMat->GetBinContent(i,i))/h1_Data_SigYild->GetBinContent(i)*100 << endl;
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
    Fout << "Bin" << "\t\t"<<"Statistic err"<<"\t\t" << "Lept Recon Effi Syst " << "\t\t" <<  "Smear Syst" << "\t\t" << "Recoil syst" <<  "\t\t" << "Scale Syst" <<endl;
  
  Fout << "" << "\t\t" << " " << "\t\t" << "" << "\t\t" << "" << "\t\t" << "" << "\t\t" << "" << "\t\t" << "" << "\t\t" << "" << endl;
  if(BaseName == "WpToMuNu" || BaseName == "WmToMuNu" )
    for( int i(1);i<=h1_Data_SigYild->GetNbinsX(); i++)
    {
      Fout << i << "\t\t" << TMath::Sqrt(SVD_Post.RecoStatisticCovMat->GetBinContent(i,i))/h1_Data_SigYild->GetBinContent(i)*100 << "\t\t" << TMath::Sqrt(SVD_Post.RecoEffiCovMat->GetBinContent(i,i))/h1_Data_SigYild->GetBinContent(i)*100 << "\t\t"<< TMath::Sqrt(SVD_Post.RecoSmearCovMat->GetBinContent(i,i))/h1_Data_SigYild->GetBinContent(i)*100 << "\t\t"<< TMath::Sqrt(SVD_Post.RecoRecoilCovMat->GetBinContent(i,i))/h1_Data_SigYild->GetBinContent(i)*100 << "\t\t" << TMath::Sqrt(SVD_Post.RecoQCDRatioCovMat->GetBinContent(i,i))/h1_Data_SigYild->GetBinContent(i)*100 << endl;
    }
  else if(BaseName == "WpToEleNu" || BaseName == "WmToEleNu" )
    for( int i(1);i<=h1_Data_SigYild->GetNbinsX(); i++)
    {
      Fout << i << "\t\t" << TMath::Sqrt(SVD_Post.RecoStatisticCovMat->GetBinContent(i,i))/h1_Data_SigYild->GetBinContent(i)*100 << "\t\t" << TMath::Sqrt(SVD_Post.RecoEffiCovMat->GetBinContent(i,i))/h1_Data_SigYild->GetBinContent(i)*100 << "\t\t"<< TMath::Sqrt(SVD_Post.RecoSmearCovMat->GetBinContent(i,i))/h1_Data_SigYild->GetBinContent(i)*100 << "\t\t"<< TMath::Sqrt(SVD_Post.RecoRecoilCovMat->GetBinContent(i,i))/h1_Data_SigYild->GetBinContent(i)*100 <<TMath::Sqrt(SVD_Post.RecoScaleCovMat->GetBinContent(i,i))/h1_Data_SigYild->GetBinContent(i)*100 << endl;
    }
  
  Fout << ""<< endl;
  Fout << ""<< endl;
  Fout << ""<< endl;
  Fout << "Total Systematics - Reconstruction stage"<< endl;
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
  return 0;
}
