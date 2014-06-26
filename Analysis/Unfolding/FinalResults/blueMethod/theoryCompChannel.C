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
  
  for(int i0 = 0; i0 < lHDiff->GetNbinsX()+1; i0++) {
    double lXCenter = lHDiff->GetBinCenter(i0);
    double lXVal     = iH0   ->GetBinContent(i0);
    lXHDiff1->SetBinContent(i0, 1.0);
    lXHDiff2->SetBinContent(i0, 1.0);
    while(iH1->GetBinCenter(i1) < lXCenter) {i1++;}
    if(iH1->GetBinContent(i0) > 0) lHDiff->SetBinContent(i0,lXVal/(iH1->GetBinContent(i0)));
    if(iH1->GetBinContent(i0) > 0) lHDiff->SetBinError(i0,iH0->GetBinError(i0)/(iH1->GetBinContent(i0)));
  }
  lHDiff->SetMarkerStyle(kFullCircle); lHDiff->SetLineColor(kRed); lHDiff->SetMarkerColor(kRed);
  
  Double_t ay[13];
  Double_t aeyl[13];
  Double_t aeyh[13];
  
  for( int ipt(0);ipt<13;ipt++)
  {
    ay[ipt] = 1.;
    aeyl[ipt] = iH2->GetErrorYlow(ipt)/iH1->GetBinContent(ipt+1);
    aeyh[ipt] = iH2->GetErrorYhigh(ipt)/iH1->GetBinContent(ipt+1);
    cout<<iH2->GetErrorYlow(ipt)<<"\t"<<iH2->GetErrorYhigh(ipt)<<"\t"<<iH1->GetBinContent(ipt+1)<<endl;
  }

  TGraphAsymmErrors* ErrBand = new TGraphAsymmErrors(13,ax,ay,aex,aex,aeyl,aeyh);
  ErrBand->SetFillColor(kRed);
  ErrBand->SetFillStyle(3354);
  
  lHDiff->SetTitle("");
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
  lHDiff->SetMarkerStyle(kFullCircle); lHDiff->SetLineColor(kRed); lHDiff->SetMarkerColor(kRed);
  
  Double_t ay[13];
  Double_t aeyl[13];
  Double_t aeyh[13];
  
  for( int ipt(0);ipt<13;ipt++)
  {
    ay[ipt] = 1.;
    aeyl[ipt] = iH2->GetErrorYlow(ipt)/iH1->GetBinContent(ipt+1);
    aeyh[ipt] = iH2->GetErrorYhigh(ipt)/iH1->GetBinContent(ipt+1);
    cout<<"Min= "<<aeyl[ipt]<<"\t Max = "<<aeyh[ipt]<<"\t"<<iH1->GetBinContent(ipt+1)<<endl;
  }

  TGraphAsymmErrors* ErrBand = new TGraphAsymmErrors(13,ax,ay,aex,aex,aeyl,aeyh);
  ErrBand->SetFillColor(kRed);
  ErrBand->SetFillStyle(3354);
  return ErrBand;
}

int theoryCompChannel()
{

  TString tmpTStr;
  char tmpName[30],tmpName_org[30];
  int Numb;

  TFile *f_theory_Mu;
  TFile *f_theory_Ele;
  TFile *f_Data_Mu;
  TFile *f_Data_Ele;

  f_theory_Mu  = new TFile("Theory_Muon.root");
  f_theory_Ele = new TFile("Theory_Ele.root");
  f_Data_Mu    = new TFile("Result_WinclMu.root");
  f_Data_Ele   = new TFile("Result_WinclEle.root");

  TH1D *hResbosLog30_Mu = new TH1D("hResbosLog30_Mu","hResbosLog30_Mu",13,WptLogBins);hResbosLog30_Mu->Sumw2();
  TH1D *hResbosLog30_Ele = new TH1D("hResbosLog30_Ele","hResbosLog30_Ele",13,WptLogBins);hResbosLog30_Ele->Sumw2();
  TH1D *hResbosLog31 = new TH1D("hResbosLog31","hResbosLog31",13,WptLogBins);hResbosLog31->Sumw2();
  TH1D *hResbosLog34 = new TH1D("hResbosLog34","hResbosLog34",13,WptLogBins);hResbosLog34->Sumw2();
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
  
  TH1D* lPowheg;

  for( int i(0);i<7;i++)
  {
    Numb = 29+i;
    sprintf(tmpName_org,"hResbos%d",Numb);
    sprintf(tmpName,"lResbos_Mu_%d",i);
    lResbos_Mu[i] = (TH1D*)f_theory_Mu->Get(tmpName_org)->Clone(tmpName);
    sprintf(tmpName,"lResbos_Ele_%d",i);
    lResbos_Ele[i] = (TH1D*)f_theory_Ele->Get(tmpName_org)->Clone(tmpName);
  }

  lResbos29_Mu = (TH1D*)f_theory_Mu->Get("hResbos29")->Clone("lResbos29_Mu");
  lResbos30_Mu = (TH1D*)f_theory_Mu->Get("hResbos30")->Clone("lResbos30_Mu");
  lResbos31_Mu = (TH1D*)f_theory_Mu->Get("hResbos31")->Clone("lResbos31_Mu");
  lResbos32_Mu = (TH1D*)f_theory_Mu->Get("hResbos32")->Clone("lResbos32_Mu");
  lResbos33_Mu = (TH1D*)f_theory_Mu->Get("hResbos33")->Clone("lResbos33_Mu");
  lResbos34_Mu = (TH1D*)f_theory_Mu->Get("hResbos34")->Clone("lResbos34_Mu");
  lResbos35_Mu = (TH1D*)f_theory_Mu->Get("hResbos35")->Clone("lResbos35_Mu");
               
  lResbos29_Ele = (TH1D*)f_theory_Ele->Get("hResbos29")->Clone("lResbos29_Ele");
  lResbos30_Ele = (TH1D*)f_theory_Ele->Get("hResbos30")->Clone("lResbos30_Ele");
  lResbos31_Ele = (TH1D*)f_theory_Ele->Get("hResbos31")->Clone("lResbos31_Ele");
  lResbos32_Ele = (TH1D*)f_theory_Ele->Get("hResbos32")->Clone("lResbos32_Ele");
  lResbos33_Ele = (TH1D*)f_theory_Ele->Get("hResbos33")->Clone("lResbos33_Ele");
  lResbos34_Ele = (TH1D*)f_theory_Ele->Get("hResbos34")->Clone("lResbos34_Ele");
  lResbos35_Ele = (TH1D*)f_theory_Ele->Get("hResbos35")->Clone("lResbos35_Ele");
  
  lPowheg = (TH1D*)f_Data_Mu->Get("SVD_BornGen")->Clone();
  lData_Mu  = (TH1D*)f_Data_Mu->Get("BornEffCorr")->Clone("lData_Mu");
  lData_Ele = (TH1D*)f_Data_Ele->Get("BornEffCorr")->Clone("lData_Ele");

  lPowheg->Scale(1./18.429);
  lData_Mu->Scale(1./18.429);
  lData_Ele->Scale(1./18.429);
  
  cout << "Resbos Total Xsec: " << lResbos30_Mu->Integral() << endl;
  cout << "Data Total Xsec: " << lData_Mu->Integral() << endl;

  Double_t resb30[nBins-1],resb30_errHi[nBins-1],resb30_errLo[nBins-1];
  Double_t resb30_Mu[nBins-1],resb30_Mu_errHi[nBins-1],resb30_Mu_errLo[nBins-1];
  Double_t resb30_Ele[nBins-1],resb30_Ele_errHi[nBins-1],resb30_Ele_errLo[nBins-1];
  Double_t resb[nBins-1],resb30_errHi[nBins-1],resb30_errLo[nBins-1];

  for( int ipt(0);ipt<nBins-1;ipt++)
  {
    resb30_Mu[ipt] = lResbos30_Mu->GetBinContent(ipt+1)/hDataNoLog->GetXaxis()->GetBinWidth(ipt+1);
    resb30_Mu_errHi[ipt] = lResbos31_Mu->GetBinContent(ipt+1)/hDataNoLog->GetXaxis()->GetBinWidth(ipt+1) - lResbos30_Mu->GetBinContent(ipt+1)/hDataNoLog->GetXaxis()->GetBinWidth(ipt+1);
    resb30_Mu_errLo[ipt] = lResbos30_Mu->GetBinContent(ipt+1)/hDataNoLog->GetXaxis()->GetBinWidth(ipt+1) - lResbos34_Mu->GetBinContent(ipt+1)/hDataNoLog->GetXaxis()->GetBinWidth(ipt+1);
    resb30_Ele[ipt] = lResbos30_Ele->GetBinContent(ipt+1)/hDataNoLog->GetXaxis()->GetBinWidth(ipt+1);
    resb30_Ele_errHi[ipt] = lResbos31_Ele->GetBinContent(ipt+1)/hDataNoLog->GetXaxis()->GetBinWidth(ipt+1) - lResbos30_Ele->GetBinContent(ipt+1)/hDataNoLog->GetXaxis()->GetBinWidth(ipt+1);
    resb30_Ele_errLo[ipt] = lResbos30_Ele->GetBinContent(ipt+1)/hDataNoLog->GetXaxis()->GetBinWidth(ipt+1) - lResbos34_Ele->GetBinContent(ipt+1)/hDataNoLog->GetXaxis()->GetBinWidth(ipt+1);
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
  }
  
  for( int ipt(1);ipt<=nBins-1;ipt++)
  {
    hResbosLog30_Mu->SetBinContent(ipt,lResbos30_Mu->GetBinContent(ipt)/hDataNoLog->GetXaxis()->GetBinWidth(ipt) );
    hResbosLog30_Ele->SetBinContent(ipt,lResbos30_Ele->GetBinContent(ipt)/hDataNoLog->GetXaxis()->GetBinWidth(ipt) );
    hResbosLog31->SetBinContent(ipt,lResbos31_Mu->GetBinContent(ipt));
    hResbosLog34->SetBinContent(ipt,lResbos34_Mu->GetBinContent(ipt));
    
    hPowhegLog->SetBinContent(ipt,lPowheg->GetBinContent(ipt)/hDataNoLog->GetXaxis()->GetBinWidth(ipt));
    hPowhegLog->SetBinError(ipt,sqrt(lPowheg->GetBinContent(ipt))/hDataNoLog->GetXaxis()->GetBinWidth(ipt));
    
    hDataLog_Mu->SetBinContent(ipt,lData_Mu->GetBinContent(ipt)/hDataNoLog->GetXaxis()->GetBinWidth(ipt));
    hDataLog_Mu->SetBinError(ipt,lData_Mu->GetBinError(ipt)/hDataNoLog->GetXaxis()->GetBinWidth(ipt));
    hDataLog_Ele->SetBinContent(ipt,lData_Ele->GetBinContent(ipt)/hDataNoLog->GetXaxis()->GetBinWidth(ipt));
    hDataLog_Ele->SetBinError(ipt,lData_Ele->GetBinError(ipt)/hDataNoLog->GetXaxis()->GetBinWidth(ipt));
  }

  hDataLog_Mu->SetMarkerStyle(kFullCircle); hDataLog_Mu->SetMarkerColor(kBlue); hDataLog_Mu->SetMarkerSize(1);
  hDataLog_Ele->SetMarkerStyle(kFullCircle); hDataLog_Ele->SetMarkerColor(kRed); hDataLog_Ele->SetMarkerSize(1);

  TGraphErrors *hData = new TGraphErrors(hDataLog_Mu);
  TGraphErrors *hPowheg = new TGraphErrors(hPowhegLog);
  TGraphAsymmErrors* hResbos = new TGraphAsymmErrors(nBins-1, ax, resb30_Mu, aex, aex, resb30_Mu_errLo, resb30_Mu_errHi);
  TGraphAsymmErrors* hResbos_Mu = new TGraphAsymmErrors(nBins-1, ax, resb30_Mu, aex, aex, errMin_Mu, errMax_Mu);
  TGraphAsymmErrors* hResbos_Ele = new TGraphAsymmErrors(nBins-1, ax, resb30_Ele, aex, aex, errMin_Ele, errMax_Ele);

  hPowheg->SetFillColor(kRed);
  hPowheg->SetFillStyle(3345);
  hResbos->SetFillColor(kBlue);
  hResbos->SetFillStyle(3354);
 
  TCanvas *lC0 = new TCanvas("Can","Can",800,800); //lC0->cd(); lC0->SetLogy();
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

  TH1F *RatioDataResb_Mu;
  TH1F *RatioDataResb_Ele;
  TGraphAsymmErrors* ResbBand_Mu;
  TGraphAsymmErrors* ResbBand_Ele;
  
  RatioDataResb_Mu = ratioDataRebos(hDataLog_Mu,hResbosLog30_Mu,hResbos_Mu);
  RatioDataResb_Mu->SetMarkerStyle(kFullCircle); RatioDataResb_Mu->SetLineColor(kBlue); RatioDataResb_Mu->SetMarkerColor(kBlue);
  
  RatioDataResb_Mu->GetYaxis()->SetRangeUser(0.6,1.5);
  RatioDataResb_Mu->GetYaxis()->SetTitleOffset(1.2);
  RatioDataResb_Mu->GetYaxis()->SetTitleSize(0.04);
  RatioDataResb_Mu->GetYaxis()->SetLabelSize(0.04);
  RatioDataResb_Mu->GetYaxis()->CenterTitle();
  RatioDataResb_Mu->GetXaxis()->SetTitleOffset(1.2);
  RatioDataResb_Mu->GetXaxis()->SetTitleSize(0.04);
  RatioDataResb_Mu->GetXaxis()->SetLabelSize(0.04);
  RatioDataResb_Mu->GetXaxis()->SetTitle(" W p_{T} ");
  RatioDataResb_Mu->GetYaxis()->SetTitle("Data/ResBos");
  
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
  rL->AddEntry(RatioDataResb_Mu,"W #rightarrow #mu #nu","PL");
  rL->AddEntry(RatioDataResb_Ele,"W #rightarrow e #nu","PL");
  
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

  lC0->SaveAs("dataOvResIncl.png");
  return 0;
}
