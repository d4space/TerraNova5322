#include <iostream>
#include <fstream>
#include <TFile.h>
#include "TH1D.h"
#include <TGraphErrors.h>             // graph class
#include <TGraphAsymmErrors.h>        // graph class
#include <TLatex.h>

const int nBins = 14;
double WptLogBins[nBins] = {1.0,7.5,12.5,17.5,24,30,40,50,70,110,150,190,250,600};
double WptBins[nBins] = {0.0,7.5,12.5,17.5,24,30,40,50,70,110,150,190,250,600};

double ax[13]  = {4.25,10,15,20.75,27,35,45,60,90,130,170,220,425};
double aex[13] = {3.25,2.5,2.5,3.25,3,5,5,10,20,20,20,30,175};

TH1F* ratioDataRebos(TH1* iH0,TH1 *iH1,TGraphAsymmErrors* iH2,TH1 *iHH=0,TH1 *iHL=0) {
  std::string lName = std::string(iH0->GetName());
  TH1F *lHDiff  = new TH1F((lName+"Diff").c_str(),(lName+"Diff").c_str(),nBins-1,WptLogBins); lHDiff->Sumw2();
  TH1F *lHDiffH = new TH1F((lName+"DiffH").c_str(),(lName+"DiffH").c_str(),iH0->GetNbinsX(),iH0->GetXaxis()->GetXmin(),iH0->GetXaxis()->GetXmax()); lHDiffH->SetLineWidth(1); lHDiffH->SetLineColor(kRed);
  TH1F *lHDiffL = new TH1F((lName+"DiffL").c_str(),(lName+"DiffL").c_str(),iH0->GetNbinsX(),iH0->GetXaxis()->GetXmin(),iH0->GetXaxis()->GetXmax()); lHDiffL->SetLineWidth(1); lHDiffL->SetLineColor(kBlue);
  lHDiff->SetFillColor(kViolet); lHDiff->SetFillStyle(1001); lHDiff->SetLineWidth(1);
  TH1F *lXHDiff1 = new TH1F((lName+"XDiff1").c_str(),(lName+"XDiff1").c_str(),iH0->GetNbinsX(),iH0->GetXaxis()->GetXmin(),iH0->GetXaxis()->GetXmax());
  TH1F *lXHDiff2 = new TH1F((lName+"XDiff2").c_str(),(lName+"XDiff2").c_str(),iH0->GetNbinsX(),iH0->GetXaxis()->GetXmin(),iH0->GetXaxis()->GetXmax());
  int i1 = 0;
  lXHDiff1->SetLineWidth(2); lXHDiff1->SetLineColor(kBlack); lXHDiff1->SetLineStyle(2);
  lXHDiff2->SetLineWidth(2); lXHDiff2->SetLineColor(kRed);
  
  //lHDiff->GetYaxis()->SetRangeUser(0.6,1.2);
  //lHDiff->GetYaxis()->SetTitleOffset(0.8);
  //lHDiff->GetYaxis()->SetTitleSize(0.08);
  //lHDiff->GetYaxis()->SetLabelSize(0.08);
  //lHDiff->GetYaxis()->CenterTitle();
  //lHDiff->GetXaxis()->SetTitleOffset(1.2);
  //lHDiff->GetXaxis()->SetTitleSize(0.10);
  //lHDiff->GetXaxis()->SetLabelSize(0.08);
  //lHDiff->GetXaxis()->SetTitle(" W p_{T} ");
  //lHDiff->GetYaxis()->SetTitle("Data/ResBos");
  //gStyle->SetOptStat(0);
  
  for(int i0 = 0; i0 < lHDiff->GetNbinsX()+1; i0++) {
    double lXCenter = lHDiff->GetBinCenter(i0);
    double lXVal     = iH0   ->GetBinContent(i0);
    lXHDiff1->SetBinContent(i0, 1.0);
    lXHDiff2->SetBinContent(i0, 1.0);
    while(iH1->GetBinCenter(i1) < lXCenter) {i1++;}
    if(iH1->GetBinContent(i0) > 0) lHDiff->SetBinContent(i0,lXVal/(iH1->GetBinContent(i0)));
    if(iH1->GetBinContent(i0) > 0) lHDiff->SetBinError(i0,iH0->GetBinError(i0)/(iH1->GetBinContent(i0)));
  }
  //lHDiff->SetMarkerStyle(kFullCircle); lHDiff->SetLineColor(kBlack); lHDiff->SetMarkerColor(kBlack);
  lHDiff->SetMarkerStyle(kFullCircle); lHDiff->SetLineColor(kRed); lHDiff->SetMarkerColor(kRed);
  
  Double_t ay[13];
  Double_t aeyl[13];
  Double_t aeyh[13];
  
  for( int ipt(0);ipt<13;ipt++)
  {
    ay[ipt] = 1.;
    aeyl[ipt] = iH2->GetErrorYlow(ipt)/iH1->GetBinContent(ipt+1);
    aeyh[ipt] = iH2->GetErrorYhigh(ipt)/iH1->GetBinContent(ipt+1);
    //cout<<iH2->GetErrorYlow(ipt)<<"\t"<<iH2->GetErrorYhigh(ipt)<<"\t"<<iH1->GetBinContent(ipt+1)<<endl;
  }

  TGraphAsymmErrors* ErrBand = new TGraphAsymmErrors(13,ax,ay,aex,aex,aeyl,aeyh);
  //ErrBand->SetFillColor(kBlue);
  ErrBand->SetFillColor(kRed);
  ErrBand->SetFillStyle(3354);
  
  lHDiff->SetTitle("");
  //lHDiff->Draw("E1");
  //ErrBand->Draw("2");
  //lXHDiff1->Draw("hist sames");
  return lHDiff;
}
TGraphAsymmErrors *ResbosError(TH1* iH0,TH1 *iH1,TGraphAsymmErrors* iH2,TH1 *iHH=0,TH1 *iHL=0) {
  std::string lName = std::string(iH0->GetName());
  TH1F *lHDiff  = new TH1F((lName+"Diff").c_str(),(lName+"Diff").c_str(),nBins-1,WptLogBins); lHDiff->Sumw2();
  TH1F *lHDiffH = new TH1F((lName+"DiffH").c_str(),(lName+"DiffH").c_str(),iH0->GetNbinsX(),iH0->GetXaxis()->GetXmin(),iH0->GetXaxis()->GetXmax()); lHDiffH->SetLineWidth(1); lHDiffH->SetLineColor(kRed);
  TH1F *lHDiffL = new TH1F((lName+"DiffL").c_str(),(lName+"DiffL").c_str(),iH0->GetNbinsX(),iH0->GetXaxis()->GetXmin(),iH0->GetXaxis()->GetXmax()); lHDiffL->SetLineWidth(1); lHDiffL->SetLineColor(kBlue);
  lHDiff->SetFillColor(kViolet); lHDiff->SetFillStyle(1001); lHDiff->SetLineWidth(1);
  TH1F *lXHDiff1 = new TH1F((lName+"XDiff1").c_str(),(lName+"XDiff1").c_str(),iH0->GetNbinsX(),iH0->GetXaxis()->GetXmin(),iH0->GetXaxis()->GetXmax());
  TH1F *lXHDiff2 = new TH1F((lName+"XDiff2").c_str(),(lName+"XDiff2").c_str(),iH0->GetNbinsX(),iH0->GetXaxis()->GetXmin(),iH0->GetXaxis()->GetXmax());
  int i1 = 0;
  lXHDiff1->SetLineWidth(2); lXHDiff1->SetLineColor(kBlack); lXHDiff1->SetLineStyle(2);
  lXHDiff2->SetLineWidth(2); lXHDiff2->SetLineColor(kRed);
  
  for(int i0 = 0; i0 < lHDiff->GetNbinsX()+1; i0++) {
    double lXCenter = lHDiff->GetBinCenter(i0);
    double lXVal     = iH0   ->GetBinContent(i0);
    lXHDiff1->SetBinContent(i0, 1.0);
    lXHDiff2->SetBinContent(i0, 1.0);
    while(iH1->GetBinCenter(i1) < lXCenter) {i1++;}
    if(iH1->GetBinContent(i0) > 0) lHDiff->SetBinContent(i0,lXVal/(iH1->GetBinContent(i0)));
    if(iH1->GetBinContent(i0) > 0) lHDiff->SetBinError(i0,iH0->GetBinError(i0)/(iH1->GetBinContent(i0)));
  }
  //lHDiff->SetMarkerStyle(kFullCircle); lHDiff->SetLineColor(kBlack); lHDiff->SetMarkerColor(kBlack);
  lHDiff->SetMarkerStyle(kFullCircle); lHDiff->SetLineColor(kRed); lHDiff->SetMarkerColor(kRed);
  
  Double_t ay[13];
  Double_t aeyl[13];
  Double_t aeyh[13];
  
  for( int ipt(0);ipt<13;ipt++)
  {
    ay[ipt] = 1.;
    aeyl[ipt] = iH2->GetErrorYlow(ipt)/iH1->GetBinContent(ipt+1);
    aeyh[ipt] = iH2->GetErrorYhigh(ipt)/iH1->GetBinContent(ipt+1);
    //cout<<"Min= "<<iH2->GetErrorYlow(ipt)<<"\t Max = "<<iH2->GetErrorYhigh(ipt)<<"\t"<<iH1->GetBinContent(ipt+1)<<endl;
    //cout<<"Min= "<<aeyl[ipt]<<"\t Max = "<<aeyh[ipt]<<"\t"<<iH1->GetBinContent(ipt+1)<<endl;
  }

  TGraphAsymmErrors* ErrBand = new TGraphAsymmErrors(13,ax,ay,aex,aex,aeyl,aeyh);
  //ErrBand->SetFillColor(kBlue);
  ErrBand->SetFillColor(kRed);
  ErrBand->SetFillStyle(3354);
  
  //lHDiff->SetTitle("");
  //lHDiff->Draw("E1");
  //ErrBand->Draw("2");
  //lXHDiff1->Draw("hist sames");
  return ErrBand;
}

int biasComp(const TString BaseName)
{

  TString tmpTStr;
  char tmpName[30],tmpName_org[30];
  int Numb;

  TFile *f_Resbos_Mu;
  TFile *f_Resbos_Ele;
  TFile *f_Fewz;
  TFile *f_Data_Mu;
  TFile *f_Data_Ele;

  if (BaseName=="Wplus"){
    f_Resbos_Mu  = new TFile("../../RstResbos/Resbos_WpToMuNu.root");
    f_Resbos_Ele = new TFile("../../RstResbos/Resbos_WpToEleNu.root");
    f_Data_Mu    = new TFile("../ResultWpToMuNu/Result_WpToMuNu.root");
    f_Data_Ele   = new TFile("../ResultWpToMuNu_Nom/Result_WpToMuNu.root");
    //f_Data_Ele   = new TFile("../ResultWpToEleNu/Result_WpToEleNu.root");
  }else if (BaseName=="Wminus"){
    f_Resbos_Mu  = new TFile("../../RstResbos/Resbos_WmToMuNu.root");
    f_Resbos_Ele = new TFile("../../RstResbos/Resbos_WmToEleNu.root");
    f_Data_Mu    = new TFile("../ResultWmToMuNu/Result_WmToMuNu.root");
    f_Data_Ele   = new TFile("../ResultWmToMuNu_Nom/Result_WmToMuNu.root");
    //f_Data_Ele   = new TFile("../ResultWmToEleNu/Result_WmToEleNu.root");
  }else if (BaseName=="Wincl"){
    f_Resbos_Mu  = new TFile("../../RstResbos/Resbos_WInclToMuNu.root");
    f_Resbos_Ele = new TFile("../../RstResbos/Resbos_WInclToEleNu.root");
    f_Data_Mu    = new TFile("../RstUnfold/Result_WInclToMuNu.root");
    f_Data_Ele   = new TFile("../RstUnfold/Result_WInclToEleNu.root");
  }

  if (BaseName=="Wplus")
    f_Fewz = new TFile("../../RstFEWZ/Wp_Mu_NNLO.root");
  if (BaseName=="Wminus")
    f_Fewz = new TFile("../../RstFEWZ/Wm_Mu_NNLO.root");
  if (BaseName=="Wincl")
    f_Fewz = new TFile("../../RstFEWZ/WIncl_Mu_NNLO.root");
  if (BaseName=="WpToEleNu")
    f_Fewz = new TFile("../../RstFEWZ/Wp_Ele_NNLO.root");
  if (BaseName=="WmToEleNu")
    f_Fewz = new TFile("../../RstFEWZ/Wm_Ele_NNLO.root");
  if (BaseName=="WInclToEleNu")
    f_Fewz = new TFile("../../RstFEWZ/WIncl_Ele_NNLO.root");

  TH1D *hResbosLog30_Mu = new TH1D("hResbosLog30_Mu","hResbosLog30_Mu",13,WptLogBins);hResbosLog30_Mu->Sumw2();
  TH1D *hResbosLog30_Ele = new TH1D("hResbosLog30_Ele","hResbosLog30_Ele",13,WptLogBins);hResbosLog30_Ele->Sumw2();
  TH1D *hResbosLog31 = new TH1D("hResbosLog31","hResbosLog31",13,WptLogBins);hResbosLog31->Sumw2();
  TH1D *hResbosLog34 = new TH1D("hResbosLog34","hResbosLog34",13,WptLogBins);hResbosLog34->Sumw2();
  TH1D *hFewzLog     = new TH1D("hFewzLog","hFewzLog",13,WptLogBins);hFewzLog->Sumw2();
  TH1D *hPowhegLog   = new TH1D("hPowhegLog","hPowhegLog",13,WptLogBins);hPowhegLog->Sumw2();
  TH1D *hDataLog_Mu  = new TH1D("hDataLog_Mu","hDataLog_Mu",13,WptLogBins);hDataLog_Mu->Sumw2();
  TH1D *hDataLog_Ele = new TH1D("hDataLog_Ele","hDataLog_Ele",13,WptLogBins);hDataLog_Ele->Sumw2();
  
  TH1D *hDataNoLog   = new TH1D("hDataNoLog","hDataNoLog",13,WptBins);hDataNoLog->Sumw2();
  
  TH1D* lResbos_Mu[7];
  TH1D* lResbos_Ele[7];
  
  TH1D* lResbos29_Mu;
  TH1D* lResbos30_Mu;
  TH1D* lResbos31_Mu;
  TH1D* lResbos32_Mu;
  TH1D* lResbos33_Mu;
  TH1D* lResbos34_Mu;
  TH1D* lResbos35_Mu;
                     
  TH1D* lResbos29_Ele;
  TH1D* lResbos30_Ele;
  TH1D* lResbos31_Ele;
  TH1D* lResbos32_Ele;
  TH1D* lResbos33_Ele;
  TH1D* lResbos34_Ele;
  TH1D* lResbos35_Ele;
 
  TH1D* lData_Mu;
  TH1D* lData_Ele;
  TH1D* lData0;
  TH1D* lData1;
  TH1D* lData2;
  TH1D* lData3;
  TH1D* lData4;
  
  TH1D* lFEWZ;
  TH1D* lPowheg;

  for( int i(0);i<7;i++)
  {
    Numb = 29+i;
    sprintf(tmpName_org,"hResbos%d",Numb);
    sprintf(tmpName,"lResbos_Mu_%d",i);
    lResbos_Mu[i] = (TH1D*)f_Resbos_Mu->Get(tmpName_org)->Clone(tmpName);
    sprintf(tmpName,"lResbos_Ele_%d",i);
    lResbos_Ele[i] = (TH1D*)f_Resbos_Ele->Get(tmpName_org)->Clone(tmpName);
  }

  lResbos29_Mu = (TH1D*)f_Resbos_Mu->Get("hResbos29")->Clone("lResbos29_Mu");
  lResbos30_Mu = (TH1D*)f_Resbos_Mu->Get("hResbos30")->Clone("lResbos30_Mu");
  lResbos31_Mu = (TH1D*)f_Resbos_Mu->Get("hResbos31")->Clone("lResbos31_Mu");
  lResbos32_Mu = (TH1D*)f_Resbos_Mu->Get("hResbos32")->Clone("lResbos32_Mu");
  lResbos33_Mu = (TH1D*)f_Resbos_Mu->Get("hResbos33")->Clone("lResbos33_Mu");
  lResbos34_Mu = (TH1D*)f_Resbos_Mu->Get("hResbos34")->Clone("lResbos34_Mu");
  lResbos35_Mu = (TH1D*)f_Resbos_Mu->Get("hResbos35")->Clone("lResbos35_Mu");
               
  lResbos29_Ele = (TH1D*)f_Resbos_Ele->Get("hResbos29")->Clone("lResbos29_Ele");
  lResbos30_Ele = (TH1D*)f_Resbos_Ele->Get("hResbos30")->Clone("lResbos30_Ele");
  lResbos31_Ele = (TH1D*)f_Resbos_Ele->Get("hResbos31")->Clone("lResbos31_Ele");
  lResbos32_Ele = (TH1D*)f_Resbos_Ele->Get("hResbos32")->Clone("lResbos32_Ele");
  lResbos33_Ele = (TH1D*)f_Resbos_Ele->Get("hResbos33")->Clone("lResbos33_Ele");
  lResbos34_Ele = (TH1D*)f_Resbos_Ele->Get("hResbos34")->Clone("lResbos34_Ele");
  lResbos35_Ele = (TH1D*)f_Resbos_Ele->Get("hResbos35")->Clone("lResbos35_Ele");
  
  //lResbos30 = (TH1D*)f_Resbos_Mu->Get("hResbos30")->Clone();
  //lResbos31 = (TH1D*)f_Resbos_Mu->Get("hResbos31")->Clone();
  //lResbos34 = (TH1D*)f_Resbos_Mu->Get("hResbos34")->Clone();
  
  lFEWZ   = (TH1D*)f_Fewz->Get("hxsec")->Clone();
  //lPowheg = (TH1D*)f_Data_Mu->Get("SVD_Born.Gen")->Clone();
  //lData_Mu   = (TH1D*)f_Data_Mu->Get("BornEffCorr")->Clone("lData_Mu");
  //lData_Ele   = (TH1D*)f_Data_Ele->Get("BornEffCorr")->Clone("lData_Ele");
  //lData_Mu   = (TH1D*)f_Data_Mu->Get("SVD_Born.Corr_1")->Clone("lData_Mu");
  //lData_Ele   = (TH1D*)f_Data_Ele->Get("SVD_Born.Corr_1")->Clone("lData_Ele");
  lData_Mu   = (TH1D*)f_Data_Mu->Get("SVD_Born.Corr_0")->Clone("lData_Mu");
  //lData_Ele   = (TH1D*)f_Data_Mu->Get("SVD_Post.data_1")->Clone("lData_Ele");
  lData_Ele   = (TH1D*)f_Data_Ele->Get("BornEffCorr")->Clone("lData_Ele");

  //lData0 = (TH1D*)f_Data_Ele->Get("SVD_Post.data_0")->Clone("lData_Mu0");
  //lData1 = (TH1D*)f_Data_Ele->Get("SVD_Post.data_1")->Clone("lData_Mu1");
  //lData2 = (TH1D*)f_Data_Ele->Get("SVD_Post.data_2")->Clone("lData_Mu2");
  //lData3 = (TH1D*)f_Data_Ele->Get("SVD_Post.data_3")->Clone("lData_Mu3");
  //lData4 = (TH1D*)f_Data_Ele->Get("SVD_Post.data_4")->Clone("lData_Mu4");
  
  lData0 = (TH1D*)f_Data_Mu->Get("SVD_Post.data_0")->Clone("lData_Mu0");
  //lData0 = (TH1D*)f_Data_Mu->Get("SVD_Born.Corr_0")->Clone("lData_Mu0");
  //lData1 = (TH1D*)f_Data_Mu->Get("SVD_Born.Corr_1")->Clone("lData_Mu1");
  //lData2 = (TH1D*)f_Data_Mu->Get("SVD_Born.Corr_2")->Clone("lData_Mu2");
  //lData3 = (TH1D*)f_Data_Mu->Get("SVD_Born.Corr_3")->Clone("lData_Mu3");
  //lData4 = (TH1D*)f_Data_Mu->Get("SVD_Born.Corr_4")->Clone("lData_Mu4");

  //lPowheg->Scale(1./18.429);
  lData_Mu->Scale(1./18.429);
  lData_Ele->Scale(1./18.429);
  
  //cout << "Resbos Total Xsec: " << lResbos30_Mu->Integral() << endl;
  //cout << "Data Total Xsec: " << lData_Mu->Integral() << endl;

  Double_t resb30[nBins-1],resb30_errHi[nBins-1],resb30_errLo[nBins-1];
  Double_t resb30_Mu[nBins-1],resb30_Mu_errHi[nBins-1],resb30_Mu_errLo[nBins-1];
  Double_t resb30_Ele[nBins-1],resb30_Ele_errHi[nBins-1],resb30_Ele_errLo[nBins-1];
  Double_t resb[nBins-1],resb30_errHi[nBins-1],resb30_errLo[nBins-1];

  cout << fixed << setprecision(4);
  for( int ipt(0);ipt<nBins-1;ipt++)
  {
    //cout<<lData0->GetBinContent(ipt+1)<<"\t"<<lData1->GetBinContent(ipt+1)<<"\t"<<lData2->GetBinContent(ipt+1)<<"\t"<<lData3->GetBinContent(ipt+1)<<"\t"<<lData4->GetBinContent(ipt+1)<<endl;
    cout<<lData0->GetBinContent(ipt+1)<<endl;
    //resb30[ipt] = lResbos30->GetBinContent(ipt+1);
    //resb30_errHi[ipt] = lResbos31->GetBinContent(ipt+1) - lResbos30->GetBinContent(ipt+1);
    //resb30_errLo[ipt] = lResbos30->GetBinContent(ipt+1) - lResbos34->GetBinContent(ipt+1);
    //cout <<ipt<<"\t"<<resb30[ipt]<<"\t"<<resb30_errLo[ipt]<<"\t"<<resb30_errHi[ipt]<<endl;
  
  
    resb30_Mu[ipt] = lResbos30_Mu->GetBinContent(ipt+1)/hDataNoLog->GetXaxis()->GetBinWidth(ipt+1);
    resb30_Mu_errHi[ipt] = lResbos31_Mu->GetBinContent(ipt+1)/hDataNoLog->GetXaxis()->GetBinWidth(ipt+1) - lResbos30_Mu->GetBinContent(ipt+1)/hDataNoLog->GetXaxis()->GetBinWidth(ipt+1);
    resb30_Mu_errLo[ipt] = lResbos30_Mu->GetBinContent(ipt+1)/hDataNoLog->GetXaxis()->GetBinWidth(ipt+1) - lResbos34_Mu->GetBinContent(ipt+1)/hDataNoLog->GetXaxis()->GetBinWidth(ipt+1);
    resb30_Ele[ipt] = lResbos30_Ele->GetBinContent(ipt+1)/hDataNoLog->GetXaxis()->GetBinWidth(ipt+1);
    resb30_Ele_errHi[ipt] = lResbos31_Ele->GetBinContent(ipt+1)/hDataNoLog->GetXaxis()->GetBinWidth(ipt+1) - lResbos30_Ele->GetBinContent(ipt+1)/hDataNoLog->GetXaxis()->GetBinWidth(ipt+1);
    resb30_Ele_errLo[ipt] = lResbos30_Ele->GetBinContent(ipt+1)/hDataNoLog->GetXaxis()->GetBinWidth(ipt+1) - lResbos34_Ele->GetBinContent(ipt+1)/hDataNoLog->GetXaxis()->GetBinWidth(ipt+1);
    //cout <<"Resbos errors(high,low): "<<ipt<<"\t"<<resb30_errHi[ipt]<<"\t"<<resb30_errLo[ipt]<<endl;
  }
//Find Error  
  Double_t errMax_Mu[nBins-1];
  Double_t errMin_Mu[nBins-1];
  Double_t errMax_Ele[nBins-1];
  Double_t errMin_Ele[nBins-1];
  double tmpVal_Mu,tmpDiff_Mu,tmpVal_Ele,tmpDiff_Ele;
 
  for( int ipt(0);ipt<nBins-1;ipt++)
  {
    double norVal_Mu  = lResbos_Mu[1]->GetBinContent(ipt+1);
    double norVal_Ele = lResbos_Ele[1]->GetBinContent(ipt+1);

    errMax_Mu[ipt] = -99999;
    errMin_Mu[ipt] = 990009;
    errMax_Ele[ipt]= -99999;
    errMin_Ele[ipt]= 990009;
    for (int i(0);i<7;i++)
    {
      tmpVal_Mu = lResbos_Mu[i]->GetBinContent(ipt+1);
      tmpDiff_Mu = tmpVal_Mu - norVal_Mu;
      if( tmpDiff_Mu > errMax_Mu[ipt] ) errMax_Mu[ipt] = tmpDiff_Mu;
      if( tmpDiff_Mu < errMin_Mu[ipt] ) errMin_Mu[ipt] = tmpDiff_Mu;
      //cout<<i<<"\t"<<tmpVal<<endl;
      tmpVal_Ele = lResbos_Ele[i]->GetBinContent(ipt+1);
      tmpDiff_Ele = tmpVal_Ele - norVal_Ele;
      if( tmpDiff_Ele > errMax_Ele[ipt] ) errMax_Ele[ipt] = tmpDiff_Ele;
      if( tmpDiff_Ele < errMin_Ele[ipt] ) errMin_Ele[ipt] = tmpDiff_Ele;
    }
    if (errMax_Mu[ipt] < 0) errMax_Mu[ipt] = 0.;
    if (errMin_Mu[ipt] > 0) errMin_Mu[ipt] = 0.;
    if (errMin_Mu[ipt] < 0) errMin_Mu[ipt] = -errMin_Mu[ipt];
    if (errMax_Ele[ipt] < 0) errMax_Ele[ipt] = 0.;
    if (errMin_Ele[ipt] > 0) errMin_Ele[ipt] = 0.;
    if (errMin_Ele[ipt] < 0) errMin_Ele[ipt] = -errMin_Ele[ipt];
    
    errMax_Mu[ipt] = errMax_Mu[ipt]/hDataNoLog->GetXaxis()->GetBinWidth(ipt+1);
    errMin_Mu[ipt] = errMin_Mu[ipt]/hDataNoLog->GetXaxis()->GetBinWidth(ipt+1);
    errMax_Ele[ipt] = errMax_Ele[ipt]/hDataNoLog->GetXaxis()->GetBinWidth(ipt+1);
    errMin_Ele[ipt] = errMin_Ele[ipt]/hDataNoLog->GetXaxis()->GetBinWidth(ipt+1);
    //cout<<"Min = "<<errMin_Mu[ipt]<<"  Max = "<<errMax_Mu[ipt]<<"\t BinCont = "<<norVal/hDataNoLog->GetXaxis()->GetBinWidth(ipt+1)<<endl;
  }
  
  for( int ipt(1);ipt<=nBins-1;ipt++)
  {
    //cout<<"Bin Width   "<<ipt<<"  "<<hDataNoLog->GetXaxis()->GetBinWidth(ipt)<<endl;

    hResbosLog30_Mu->SetBinContent(ipt,lResbos30_Mu->GetBinContent(ipt)/hDataNoLog->GetXaxis()->GetBinWidth(ipt) );
    hResbosLog30_Ele->SetBinContent(ipt,lResbos30_Ele->GetBinContent(ipt)/hDataNoLog->GetXaxis()->GetBinWidth(ipt) );
    hResbosLog31->SetBinContent(ipt,lResbos31_Mu->GetBinContent(ipt));
    hResbosLog34->SetBinContent(ipt,lResbos34_Mu->GetBinContent(ipt));
    
    hFewzLog->SetBinContent(ipt,lFEWZ->GetBinContent(ipt)/hDataNoLog->GetXaxis()->GetBinWidth(ipt));
    hFewzLog->SetBinError(ipt,lFEWZ->GetBinError(ipt)/hDataNoLog->GetXaxis()->GetBinWidth(ipt));
    
    //hPowhegLog->SetBinContent(ipt,lPowheg->GetBinContent(ipt)/hDataNoLog->GetXaxis()->GetBinWidth(ipt));
    //hPowhegLog->SetBinError(ipt,lPowheg->GetBinError(ipt)/hDataNoLog->GetXaxis()->GetBinWidth(ipt));
    //hPowhegLog->SetBinError(ipt,sqrt(lPowheg->GetBinContent(ipt))/hDataNoLog->GetXaxis()->GetBinWidth(ipt));
    
    //cout<<"x-axis "<<hPowhegLog->GetBinCenter()<<endl;
    
    hDataLog_Mu->SetBinContent(ipt,lData_Mu->GetBinContent(ipt)/hDataNoLog->GetXaxis()->GetBinWidth(ipt));
    hDataLog_Mu->SetBinError(ipt,lData_Mu->GetBinError(ipt)/hDataNoLog->GetXaxis()->GetBinWidth(ipt));
    hDataLog_Ele->SetBinContent(ipt,lData_Ele->GetBinContent(ipt)/hDataNoLog->GetXaxis()->GetBinWidth(ipt));
    hDataLog_Ele->SetBinError(ipt,lData_Ele->GetBinError(ipt)/hDataNoLog->GetXaxis()->GetBinWidth(ipt));

    //cout<<ipt<<"\t"<<hResbosLog30->GetBinContent(ipt)<<"\t"<<hDataLog->GetBinContent(ipt)<<"\t"<<hPowhegLog->GetBinError(ipt)<<endl;
  }

  hDataLog_Mu->SetMarkerStyle(kFullCircle); hDataLog_Mu->SetMarkerColor(kBlue); hDataLog_Mu->SetMarkerSize(1);
  hDataLog_Ele->SetMarkerStyle(kFullCircle); hDataLog_Ele->SetMarkerColor(kRed); hDataLog_Ele->SetMarkerSize(1);

  TGraphErrors *hData = new TGraphErrors(hDataLog_Mu);
  //TGraphErrors *hPowheg = new TGraphErrors(hPowhegLog);
  TGraphErrors *hFewz = new TGraphErrors(hFewzLog);
  TGraphAsymmErrors* hResbos = new TGraphAsymmErrors(nBins-1, ax, resb30_Mu, aex, aex, resb30_Mu_errLo, resb30_Mu_errHi);
  //TGraphAsymmErrors* hResbos_Mu = new TGraphAsymmErrors(nBins-1, ax, resb30_Mu, aex, aex, resb30_Mu_errLo, resb30_Mu_errHi);
  //TGraphAsymmErrors* hResbos_Ele = new TGraphAsymmErrors(nBins-1, ax, resb30_Ele, aex, aex, resb30_Ele_errLo, resb30_Ele_errHi);
  TGraphAsymmErrors* hResbos_Mu = new TGraphAsymmErrors(nBins-1, ax, resb30_Mu, aex, aex, errMin_Mu, errMax_Mu);
  TGraphAsymmErrors* hResbos_Ele = new TGraphAsymmErrors(nBins-1, ax, resb30_Ele, aex, aex, errMin_Ele, errMax_Ele);

  hFewz->SetFillColor(kGreen);
  hFewz->SetFillStyle(1001);

  //hPowheg->SetFillColor(kRed);
  //hPowheg->SetFillStyle(3345);
  hResbos->SetFillColor(kBlue);
  hResbos->SetFillStyle(3354);
 


 // hPowheg->Scale(1./18.429);
 // hData->Scale(1./18.429);
 // hFewz->Scale(1./18.429);
 // hResbos->Scale(1./18.429);
  
 // cout << "Resbos Total Differentail Xsec: " << lResbos30->Integral() << endl;
 // cout << "Data Total Differentail Xsec: " << lData->Integral() << endl;
  
  
  TLegend *lL =new TLegend(0.6,0.65,0.92,0.85); lL->SetFillColor(0); lL->SetBorderSize(0);
  lL->AddEntry(hData,"Unfolded","PL");
  //lL->AddEntry(hPowheg,"Powheg CT10 NLO","f");
 // lL->AddEntry(hFewz,"FEWZ CTEQ12 NNLO","f");
  lL->AddEntry(hResbos,"ResBos CT10 NNLO","f");

  TCanvas *lC0 = new TCanvas("Can","Can",800,800); //lC0->cd(); lC0->SetLogy();
  //lC0->Divide(1,2,0,0);
  lC0->SetPad(0,0.1,1.0,1.0);
  lC0->SetTopMargin(0.1);
  lC0->SetBottomMargin(0.15);
  lC0->SetLeftMargin(0.15);
  lC0->SetRightMargin(0.07);
  lC0->SetTickx(1);
  lC0->SetTicky(1);
  //lC0->SetLogx(1);
  gStyle->SetLineWidth(2.);
  gStyle->SetOptStat(0);
  gStyle->SetHatchesSpacing(0.75);
  //gStyle->SetHatchesLineWidth(2);
  gStyle->SetHatchesLineWidth(1);
  gPad->SetLogx(1);

  //hPowheg->GetYaxis()->SetRangeUser(0.,1.14*resb30_Mu[0]);
  //hPowheg->SetTitle("");
  //hPowheg->GetYaxis()->SetTitle("Xsec [pb]");
  //hPowheg->GetYaxis()->SetTitleOffset(1.2);
  
//  hPowheg->Draw("A2");
////  hFewz->Draw("2");
//  hResbos->Draw("2");
//  hData->Draw("p");
//  lL->Draw();
//  tb->Draw();

//  lC0->cd(2)->SetPad(0,0,0.95,0.34);
//  lC0->cd(2)->SetTopMargin(0.025);
//  lC0->cd(2)->SetBottomMargin(0.3);
//  lC0->cd(2)->SetLeftMargin(0.15);
//  lC0->cd(2)->SetRightMargin(0.07);
//  lC0->cd(2)->SetTickx(1);
//  lC0->cd(2)->SetTicky(1);
//  lC0->cd(2)->SetLogx(1);

  TH1F *RatioDataResb_Mu;
  TH1F *RatioDataResb_Ele;
  TGraphAsymmErrors* ResbBand_Mu;
  TGraphAsymmErrors* ResbBand_Ele;
  
  RatioDataResb_Mu = ratioDataRebos(hDataLog_Mu,hResbosLog30_Mu,hResbos_Mu);
  RatioDataResb_Mu->SetMarkerStyle(kFullCircle); RatioDataResb_Mu->SetLineColor(kBlue); RatioDataResb_Mu->SetMarkerColor(kBlue);
  
  //RatioDataResb_Mu->GetYaxis()->SetRangeUser(0.6,1.5);
  RatioDataResb_Mu->GetYaxis()->SetRangeUser(0,8);
  RatioDataResb_Mu->GetYaxis()->SetTitleOffset(1.2);
  RatioDataResb_Mu->GetYaxis()->SetTitleSize(0.04);
  RatioDataResb_Mu->GetYaxis()->SetLabelSize(0.04);
  RatioDataResb_Mu->GetYaxis()->CenterTitle();
  RatioDataResb_Mu->GetXaxis()->SetTitleOffset(1.2);
  RatioDataResb_Mu->GetXaxis()->SetTitleSize(0.04);
  RatioDataResb_Mu->GetXaxis()->SetLabelSize(0.04);
  RatioDataResb_Mu->GetXaxis()->SetTitle(" W p_{T} ");
  RatioDataResb_Mu->GetYaxis()->SetTitle("Data/ResBos");
  //gStyle->SetOptStat(0);
  
  RatioDataResb_Ele = ratioDataRebos(hDataLog_Ele,hResbosLog30_Ele,hResbos_Ele);
  RatioDataResb_Ele->SetMarkerStyle(kFullCircle); RatioDataResb_Ele->SetLineColor(kRed); RatioDataResb_Ele->SetMarkerColor(kRed);
  
  ResbBand_Mu = ResbosError(hDataLog_Mu,hResbosLog30_Mu,hResbos_Mu);
  ResbBand_Mu->SetFillColor(kBlue);
  ResbBand_Mu->SetFillStyle(3354);
  
  TPaveText *tb = new TPaveText(0.2,0.77,0.5,0.83,"NDC");
  tb->SetBorderSize(0);
  tb->SetFillStyle(0);
  tb->AddText("18.43 pb^{-1} at #sqrt{s} = 8 TeV");

  TLegend *rL =new TLegend(0.64,0.72,0.88,0.87); rL->SetFillColor(0); rL->SetBorderSize(0);
  if (BaseName=="Wplus"){
    rL->AddEntry(RatioDataResb_Mu,"W^{+} #rightarrow #mu^{+} #nu","PL");
    rL->AddEntry(RatioDataResb_Ele,"W^{+} #rightarrow e^{+} #nu","PL");
  }else if (BaseName=="Wminus"){
    rL->AddEntry(RatioDataResb_Mu,"W^{-} #rightarrow #mu^{-} #bar{#nu}","PL");
    rL->AddEntry(RatioDataResb_Ele,"W^{-} #rightarrow e^{-} #bar{#nu}","PL");
  }else if (BaseName=="Wincl"){
    rL->AddEntry(RatioDataResb_Mu,"W #rightarrow #mu #nu","PL");
    rL->AddEntry(RatioDataResb_Ele,"W #rightarrow e #nu","PL");
  }
  
  //for( int ipt(0);ipt<13;ipt++)
  //{
  //  cout<<"Min = "<<ResbBand_Mu->GetErrorYlow(ipt)<<"\t Max = "<<ResbBand_Mu->GetErrorYhigh(ipt)<<endl; 
  //}
  hDataLog_Mu->Draw();
  hDataLog_Ele->Draw("SAME");
  lC0->SaveAs(BaseName+"_Plot.png");

  ResbBand_Ele = ResbosError(hDataLog_Ele,hResbosLog30_Ele,hResbos_Ele);
  ResbBand_Ele->SetFillColor(kRed);
  ResbBand_Ele->SetFillStyle(3345);
  
  RatioDataResb_Mu -> Draw("E1");
  RatioDataResb_Ele-> Draw("E1 SAME");
  ResbBand_Mu -> Draw("2");
  ResbBand_Ele-> Draw("2");
  
  TLine *rLine = new TLine(0,1,600,1);
  rLine->SetLineWidth(2);
  rLine->SetLineStyle(2);
  rLine->SetLineColor(kBlack);
  rLine->Draw("same");
  tb->Draw("same");
  rL->Draw();

  lC0->SaveAs(BaseName+"_Ratio.png");
  return 0;
}
