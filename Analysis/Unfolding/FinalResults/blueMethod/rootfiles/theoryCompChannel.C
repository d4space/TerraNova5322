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
    cout<<iH2->GetErrorYlow(ipt)<<"\t"<<iH2->GetErrorYhigh(ipt)<<"\t"<<iH1->GetBinContent(ipt+1)<<endl;
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
    cout<<"Min= "<<aeyl[ipt]<<"\t Max = "<<aeyh[ipt]<<"\t"<<iH1->GetBinContent(ipt+1)<<endl;
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

int theoryCompChannel(const TString BaseName)
{

  TString tmpTStr;
  char tmpName[30],tmpName_org[30];
  int Numb;

  TFile *f_Resbos;
  TFile *f_Data;

  if (BaseName=="Wplus"){
    f_Resbos  = new TFile("../../../RstResbos/Resbos_WpToMuNu.root");
    f_Data    = new TFile("Result_WpMuEle.root");
  }else if (BaseName=="Wminus"){
    f_Resbos  = new TFile("../../../RstResbos/Resbos_WmToMuNu.root");
    f_Data    = new TFile("Result_WmMuEle.root");
  }else if (BaseName=="Wincl"){
    f_Resbos  = new TFile("../../../RstResbos/Resbos_WInclToMuNu.root");
    f_Data    = new TFile("Result_WinclMuEle.root");
  }

  TH1D *hResbosLog30 = new TH1D("hResbosLog30","hResbosLog30",13,WptLogBins);hResbosLog30->Sumw2();
  TH1D *hResbosLog31 = new TH1D("hResbosLog31","hResbosLog31",13,WptLogBins);hResbosLog31->Sumw2();
  TH1D *hResbosLog34 = new TH1D("hResbosLog34","hResbosLog34",13,WptLogBins);hResbosLog34->Sumw2();
  TH1D *hDataLog  = new TH1D("hDataLog","hDataLog",13,WptLogBins);hDataLog->Sumw2();
  
  TH1D *hDataNoLog   = new TH1D("hDataNoLog","hDataNoLog",13,WptBins);hDataNoLog->Sumw2();
  
  TH1D* lResbos[7];
  
  TH1D* lResbos29;
  TH1D* lResbos30;
  TH1D* lResbos31;
  TH1D* lResbos32;
  TH1D* lResbos33;
  TH1D* lResbos34;
  TH1D* lResbos35;
                     
  TH1D* lData;
  
  for( int i(0);i<7;i++)
  {
    Numb = 29+i;
    sprintf(tmpName_org,"hResbos%d",Numb);
    sprintf(tmpName,"lResbos_%d",i);
    lResbos[i] = (TH1D*)f_Resbos->Get(tmpName_org)->Clone(tmpName);
  }

  lResbos29 = (TH1D*)f_Resbos->Get("hResbos29")->Clone("lResbos29");
  lResbos30 = (TH1D*)f_Resbos->Get("hResbos30")->Clone("lResbos30");
  lResbos31 = (TH1D*)f_Resbos->Get("hResbos31")->Clone("lResbos31");
  lResbos32 = (TH1D*)f_Resbos->Get("hResbos32")->Clone("lResbos32");
  lResbos33 = (TH1D*)f_Resbos->Get("hResbos33")->Clone("lResbos33");
  lResbos34 = (TH1D*)f_Resbos->Get("hResbos34")->Clone("lResbos34");
  lResbos35 = (TH1D*)f_Resbos->Get("hResbos35")->Clone("lResbos35");
               
  lData   = (TH1D*)f_Data->Get("BornEffCorr")->Clone("lData");

  lData->Scale(1./18.429);
  
  cout << "Resbos Total Xsec: " << lResbos30->Integral() << endl;
  cout << "Data Total Xsec: " << lData->Integral() << endl;

  Double_t resb30[nBins-1],resb30_errHi[nBins-1],resb30_errLo[nBins-1];
  Double_t resb30[nBins-1],resb30_errHi[nBins-1],resb30_errLo[nBins-1];
  Double_t resb[nBins-1],resb30_errHi[nBins-1],resb30_errLo[nBins-1];

  for( int ipt(0);ipt<nBins-1;ipt++)
  {
    resb30[ipt] = lResbos30->GetBinContent(ipt+1)/hDataNoLog->GetXaxis()->GetBinWidth(ipt+1);
    resb30_errHi[ipt] = lResbos31->GetBinContent(ipt+1)/hDataNoLog->GetXaxis()->GetBinWidth(ipt+1) - lResbos30->GetBinContent(ipt+1)/hDataNoLog->GetXaxis()->GetBinWidth(ipt+1);
    resb30_errLo[ipt] = lResbos30->GetBinContent(ipt+1)/hDataNoLog->GetXaxis()->GetBinWidth(ipt+1) - lResbos34->GetBinContent(ipt+1)/hDataNoLog->GetXaxis()->GetBinWidth(ipt+1);
  }
//Find Error  
  Double_t errMax[nBins-1];
  Double_t errMin[nBins-1];
  double tmpVal,tmpDiff;
 
  for( int ipt(0);ipt<nBins-1;ipt++)
  {
    double norVal  = lResbos[1]->GetBinContent(ipt+1);

    errMax[ipt] = -99999;
    errMin[ipt] = 990009;
    for (int i(0);i<7;i++)
    {
      tmpVal = lResbos[i]->GetBinContent(ipt+1);
      tmpDiff = tmpVal - norVal;
      if( tmpDiff > errMax[ipt] ) errMax[ipt] = tmpDiff;
      if( tmpDiff < errMin[ipt] ) errMin[ipt] = tmpDiff;
    }
    if (errMax[ipt] < 0) errMax[ipt] = 0.;
    if (errMin[ipt] > 0) errMin[ipt] = 0.;
    if (errMin[ipt] < 0) errMin[ipt] = -errMin[ipt];
    
    errMax[ipt] = errMax[ipt]/hDataNoLog->GetXaxis()->GetBinWidth(ipt+1);
    errMin[ipt] = errMin[ipt]/hDataNoLog->GetXaxis()->GetBinWidth(ipt+1);
  }
  
  for( int ipt(1);ipt<=nBins-1;ipt++)
  {
    cout<<"Bin Width   "<<ipt<<"  "<<hDataNoLog->GetXaxis()->GetBinWidth(ipt)<<endl;

    hResbosLog30->SetBinContent(ipt,lResbos30->GetBinContent(ipt)/hDataNoLog->GetXaxis()->GetBinWidth(ipt) );
    hResbosLog31->SetBinContent(ipt,lResbos31->GetBinContent(ipt));
    hResbosLog34->SetBinContent(ipt,lResbos34->GetBinContent(ipt));
    
    hDataLog->SetBinContent(ipt,lData->GetBinContent(ipt)/hDataNoLog->GetXaxis()->GetBinWidth(ipt));
    hDataLog->SetBinError(ipt,lData->GetBinError(ipt)/hDataNoLog->GetXaxis()->GetBinWidth(ipt));
  }

  hDataLog->SetMarkerStyle(kFullCircle); hDataLog->SetMarkerColor(kBlack); hDataLog->SetMarkerSize(1);

  TGraphErrors *hData = new TGraphErrors(hDataLog);
  TGraphAsymmErrors* hResbos = new TGraphAsymmErrors(nBins-1, ax, resb30, aex, aex, resb30_errLo, resb30_errHi);
  TGraphAsymmErrors* hResbos = new TGraphAsymmErrors(nBins-1, ax, resb30, aex, aex, errMin, errMax);

  hResbos->SetFillColor(kBlack);
  hResbos->SetFillStyle(3354);
  
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

  TH1F *RatioDataResb;
  TGraphAsymmErrors* ResbBand;
  
  RatioDataResb = ratioDataRebos(hDataLog,hResbosLog30,hResbos);
  RatioDataResb->SetMarkerStyle(kFullCircle); RatioDataResb->SetLineColor(kBlack); RatioDataResb->SetMarkerColor(kBlack);
  
  RatioDataResb->GetYaxis()->SetRangeUser(0.6,1.5);
  //RatioDataResb->GetYaxis()->SetRangeUser(0.2,1.8);
  RatioDataResb->GetYaxis()->SetTitleOffset(1.2);
  RatioDataResb->GetYaxis()->SetTitleSize(0.04);
  RatioDataResb->GetYaxis()->SetLabelSize(0.04);
  RatioDataResb->GetYaxis()->CenterTitle();
  RatioDataResb->GetXaxis()->SetTitleOffset(1.2);
  RatioDataResb->GetXaxis()->SetTitleSize(0.04);
  RatioDataResb->GetXaxis()->SetLabelSize(0.04);
  RatioDataResb->GetXaxis()->SetTitle(" W p_{T} ");
  RatioDataResb->GetYaxis()->SetTitle("Data/ResBos");
  //gStyle->SetOptStat(0);
  
  ResbBand = ResbosError(hDataLog,hResbosLog30,hResbos);
  ResbBand->SetFillColor(kRed);
  ResbBand->SetFillStyle(3354);
  
  TPaveText *tb = new TPaveText(0.2,0.77,0.5,0.83,"NDC");
  tb->SetBorderSize(0);
  tb->SetFillStyle(0);
  tb->AddText("18.43 pb^{-1} at #sqrt{s} = 8 TeV");

  TLegend *rL =new TLegend(0.64,0.72,0.88,0.87); rL->SetFillColor(0); rL->SetBorderSize(0);
  if (BaseName=="Wplus"){
    rL->AddEntry(RatioDataResb,"W^{+} (combined #mu and e)","PL");
  }else if (BaseName=="Wminus"){
    rL->AddEntry(RatioDataResb,"W^{-} (combined #mu and e)","PL");
  }else if (BaseName=="Wincl"){
    rL->AddEntry(RatioDataResb,"W (combined #mu and e)","PL");
  }
  
  //for( int ipt(0);ipt<13;ipt++)
  //{
  //  cout<<"Min = "<<ResbBand->GetErrorYlow(ipt)<<"\t Max = "<<ResbBand->GetErrorYhigh(ipt)<<endl; 
  //}
  
  
  RatioDataResb -> Draw("E1");
  ResbBand -> Draw("2");
  
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
