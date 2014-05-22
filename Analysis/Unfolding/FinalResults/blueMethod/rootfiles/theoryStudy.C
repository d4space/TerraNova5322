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

void drawDifference(TH1* iH0,TH1 *iH1,TGraphAsymmErrors* iH2,TH1 *iHH=0,TH1 *iHL=0) {
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
  
  lHDiff->GetYaxis()->SetRangeUser(0.6,1.2);
  lHDiff->GetYaxis()->SetTitleOffset(0.6);
  lHDiff->GetYaxis()->SetTitleSize(0.08);
  lHDiff->GetYaxis()->SetLabelSize(0.08);
  lHDiff->GetYaxis()->CenterTitle();
  lHDiff->GetXaxis()->SetTitleOffset(1.2);
  lHDiff->GetXaxis()->SetTitleSize(0.10);
  lHDiff->GetXaxis()->SetLabelSize(0.08);
  lHDiff->GetXaxis()->SetTitle(" W p_{T} ");
  lHDiff->GetYaxis()->SetTitle("Data/ResBos");
  gStyle->SetOptStat(0);
  
  for(int i0 = 0; i0 < lHDiff->GetNbinsX()+1; i0++) {
    double lXCenter = lHDiff->GetBinCenter(i0);
    double lXVal     = iH0   ->GetBinContent(i0);
    lXHDiff1->SetBinContent(i0, 1.0);
    lXHDiff2->SetBinContent(i0, 1.0);
    while(iH1->GetBinCenter(i1) < lXCenter) {i1++;}
    if(iH1->GetBinContent(i0) > 0) lHDiff->SetBinContent(i0,lXVal/(iH1->GetBinContent(i0)));
    if(iH1->GetBinContent(i0) > 0) lHDiff->SetBinError(i0,iH0->GetBinError(i0)/(iH1->GetBinContent(i0)));
  }
  lHDiff->SetMarkerStyle(kFullCircle); lHDiff->SetLineColor(kBlack); lHDiff->SetMarkerColor(kBlack);
  
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
  ErrBand->SetFillColor(kBlue);
  ErrBand->SetFillStyle(3354);
  
  lHDiff->SetTitle("");
  lHDiff->Draw("E1");
  ErrBand->Draw("2");
  lXHDiff1->Draw("hist sames");
}

int theoryStudy(const TString BaseName)
{

  TString tmpTStr;
  char tmpName[30],tmpName_org[30];
  int Numb;

  TFile *f_Resbos;
  TFile *f_Fewz;
  TFile *f_Data;

  f_Resbos = new TFile("../../RstResbos/Resbos_"+BaseName+".root");
  f_Data = new TFile("../RstUnfold/Result_"+BaseName+".root");

  if (BaseName=="WpToMuNu")
    f_Fewz = new TFile("../../RstFEWZ/Wp_Mu_NNLO.root");
  if (BaseName=="WmToMuNu")
    f_Fewz = new TFile("../../RstFEWZ/Wm_Mu_NNLO.root");
  if (BaseName=="WInclToMuNu")
    f_Fewz = new TFile("../../RstFEWZ/WIncl_Mu_NNLO.root");
  if (BaseName=="WpToEleNu")
    f_Fewz = new TFile("../../RstFEWZ/Wp_Ele_NNLO.root");
  if (BaseName=="WmToEleNu")
    f_Fewz = new TFile("../../RstFEWZ/Wm_Ele_NNLO.root");
  if (BaseName=="WInclToEleNu")
    f_Fewz = new TFile("../../RstFEWZ/WIncl_Ele_NNLO.root");

  TH1D *hResbosLog30 = new TH1D("hResbosLog30","hResbosLog30",13,WptLogBins);hResbosLog30->Sumw2();
  TH1D *hResbosLog31 = new TH1D("hResbosLog31","hResbosLog31",13,WptLogBins);hResbosLog31->Sumw2();
  TH1D *hResbosLog34 = new TH1D("hResbosLog34","hResbosLog34",13,WptLogBins);hResbosLog34->Sumw2();
  TH1D *hFewzLog     = new TH1D("hFewzLog","hFewzLog",13,WptLogBins);hFewzLog->Sumw2();
  TH1D *hPowhegLog   = new TH1D("hPowhegLog","hPowhegLog",13,WptLogBins);hPowhegLog->Sumw2();
  TH1D *hDataLog     = new TH1D("hDataLog","hDataLog",13,WptLogBins);hDataLog->Sumw2();
  
  TH1D *hDataNoLog     = new TH1D("hDataNoLog","hDataNoLog",13,WptBins);hDataNoLog->Sumw2();
  
  TH1D* lResbos[7];
  TH1D* lResbos30;
  TH1D* lResbos31;
  TH1D* lResbos34;
  TH1D* lFEWZ;
  TH1D* lPowheg;
  TH1D* lData;
  
  for( int i(0);i<7;i++)
  {
    Numb = 29+i;
    sprintf(tmpName_org,"hResbos%d",Numb);
    sprintf(tmpName,"lResbos_%d",i);
    lResbos[i] = (TH1D*)f_Resbos->Get(tmpName_org)->Clone(tmpName);
  }

  lResbos30 = (TH1D*)f_Resbos->Get("hResbos30")->Clone();
  lResbos31 = (TH1D*)f_Resbos->Get("hResbos31")->Clone();
  lResbos34 = (TH1D*)f_Resbos->Get("hResbos34")->Clone();
  
  lFEWZ   = (TH1D*)f_Fewz->Get("hxsec")->Clone();
  lPowheg = (TH1D*)f_Data->Get("SVD_Born.Gen")->Clone();
  lData   = (TH1D*)f_Data->Get("BornEffCorr")->Clone();

  lPowheg->Scale(1./18.429);
  lData->Scale(1./18.429);
  
  cout << "Resbos Total Xsec: " << lResbos30->Integral() << endl;
  cout << "Data Total Xsec: " << lData->Integral() << endl;

  Double_t resb30[nBins-1],resb30_errHi[nBins-1],resb30_errLo[nBins-1];

  for( int ipt(0);ipt<nBins-1;ipt++)
  {
    //resb30[ipt] = lResbos30->GetBinContent(ipt+1);
    //resb30_errHi[ipt] = lResbos31->GetBinContent(ipt+1) - lResbos30->GetBinContent(ipt+1);
    //resb30_errLo[ipt] = lResbos30->GetBinContent(ipt+1) - lResbos34->GetBinContent(ipt+1);
    //cout <<ipt<<"\t"<<resb30[ipt]<<"\t"<<resb30_errLo[ipt]<<"\t"<<resb30_errHi[ipt]<<endl;
  
  
    resb30[ipt] = lResbos30->GetBinContent(ipt+1)/hDataNoLog->GetXaxis()->GetBinWidth(ipt+1);
    resb30_errHi[ipt] = lResbos31->GetBinContent(ipt+1)/hDataNoLog->GetXaxis()->GetBinWidth(ipt+1) - lResbos30->GetBinContent(ipt+1)/hDataNoLog->GetXaxis()->GetBinWidth(ipt+1);
    resb30_errLo[ipt] = lResbos30->GetBinContent(ipt+1)/hDataNoLog->GetXaxis()->GetBinWidth(ipt+1) - lResbos34->GetBinContent(ipt+1)/hDataNoLog->GetXaxis()->GetBinWidth(ipt+1);
    cout <<"Resbos errors(high,low): "<<ipt<<"\t"<<resb30_errHi[ipt]<<"\t"<<resb30_errLo[ipt]<<endl;
  }

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
      tmpVal  = lResbos[i]->GetBinContent(ipt+1);
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
    
    hFewzLog->SetBinContent(ipt,lFEWZ->GetBinContent(ipt)/hDataNoLog->GetXaxis()->GetBinWidth(ipt));
    hFewzLog->SetBinError(ipt,lFEWZ->GetBinError(ipt)/hDataNoLog->GetXaxis()->GetBinWidth(ipt));
    
    hPowhegLog->SetBinContent(ipt,lPowheg->GetBinContent(ipt)/hDataNoLog->GetXaxis()->GetBinWidth(ipt));
    //hPowhegLog->SetBinError(ipt,lPowheg->GetBinError(ipt)/hDataNoLog->GetXaxis()->GetBinWidth(ipt));
    hPowhegLog->SetBinError(ipt,sqrt(lPowheg->GetBinContent(ipt))/hDataNoLog->GetXaxis()->GetBinWidth(ipt));
    
    //cout<<"x-axis "<<hPowhegLog->GetBinCenter()<<endl;
    
    hDataLog->SetBinContent(ipt,lData->GetBinContent(ipt)/hDataNoLog->GetXaxis()->GetBinWidth(ipt));
    hDataLog->SetBinError(ipt,lData->GetBinError(ipt)/hDataNoLog->GetXaxis()->GetBinWidth(ipt));

    cout<<ipt<<"\t"<<hResbosLog30->GetBinContent(ipt)<<"\t"<<hDataLog->GetBinContent(ipt)<<"\t"<<hPowhegLog->GetBinError(ipt)<<endl;
  }

  hDataLog->SetMarkerStyle(kFullCircle); hDataLog->SetMarkerColor(kBlack); hDataLog->SetMarkerSize(1);

  TGraphErrors *hData = new TGraphErrors(hDataLog);
  TGraphErrors *hPowheg = new TGraphErrors(hPowhegLog);
  TGraphErrors *hFewz = new TGraphErrors(hFewzLog);
  //TGraphAsymmErrors* hResbos = new TGraphAsymmErrors(nBins-1, ax, resb30, aex, aex, resb30_errLo, resb30_errHi);
  TGraphAsymmErrors* hResbos = new TGraphAsymmErrors(nBins-1, ax, resb30, aex, aex, errMin, errMax);

  hFewz->SetFillColor(kGreen);
  hFewz->SetFillStyle(3305);

  hPowheg->SetFillColor(kRed);
  hPowheg->SetFillStyle(3345);
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
  lL->AddEntry(hPowheg,"Powheg CT10 NLO","f");
  lL->AddEntry(hFewz,"FEWZ CTEQ12 NNLO","f");
  lL->AddEntry(hResbos,"ResBos CT10 NNLO","f");

  TPaveText *tb = new TPaveText(0.6,0.44,0.9,0.58,"NDC");
  tb->SetBorderSize(0);
  tb->SetFillStyle(0);
  tb->AddText("18.43 pb^{-1} at #sqrt{s} = 8 TeV");
  if (BaseName=="WpToMuNu")
    tb->AddText("W^{+} #rightarrow #mu^{+} #nu");
  if (BaseName=="WmToMuNu")
    tb->AddText("W^{-} #rightarrow #mu^{-} #bar{#nu}");
  if (BaseName=="WInclToMuNu")
    tb->AddText("W #rightarrow #mu #nu");
  if (BaseName=="WpToEleNu")
    tb->AddText("W^{+} #rightarrow e^{+} #nu");
  if (BaseName=="WmToEleNu")
    tb->AddText("W^{-} #rightarrow e^{-} #bar{#nu}");
  if (BaseName=="WInclToEleNu")
    tb->AddText("W #rightarrow e #nu");

  TCanvas *lC0 = new TCanvas("Can","Can",800,800); lC0->cd(); lC0->SetLogy();
  lC0->Divide(1,2,0,0);
  lC0->cd(1)->SetPad(0,0.35,0.95,1.0);
  lC0->cd(1)->SetTopMargin(0.1);
  lC0->cd(1)->SetBottomMargin(0.01);
  lC0->cd(1)->SetLeftMargin(0.15);
  lC0->cd(1)->SetRightMargin(0.07);
  lC0->cd(1)->SetTickx(1);
  lC0->cd(1)->SetTicky(1);
  //lC0->SetLogx(1);
  gStyle->SetLineWidth(2.);
  gStyle->SetOptStat(0);
  gStyle->SetHatchesSpacing(0.75);
  gStyle->SetHatchesLineWidth(2);
  gPad->SetLogx(1);
  //gPad->SetLogy(1);

  hPowheg->GetYaxis()->SetRangeUser(0.,1.14*resb30[0]);
  hPowheg->SetTitle("");
  hPowheg->GetYaxis()->SetTitle("Xsec [pb]");
  hPowheg->GetYaxis()->SetTitleOffset(1.2);
  //hPowheg->SetMaximum(1.1*(hResbosLog30->GetBinContent(1)));
  
  hPowheg->Draw("A2");
  hFewz->Draw("2");
  hResbos->Draw("2");
  hData->Draw("p");
  lL->Draw();
  tb->Draw();

  lC0->cd(2)->SetPad(0,0,0.95,0.34);
  lC0->cd(2)->SetTopMargin(0.025);
  lC0->cd(2)->SetBottomMargin(0.3);
  lC0->cd(2)->SetLeftMargin(0.15);
  lC0->cd(2)->SetRightMargin(0.07);
  lC0->cd(2)->SetTickx(1);
  lC0->cd(2)->SetTicky(1);
  lC0->cd(2)->SetLogx(1);
  drawDifference(hDataLog,hResbosLog30,hResbos);
  lC0->SaveAs(BaseName+"_Result_diffXsec.png");

  TFile f_out("Resbos_"+BaseName+".root","recreate");
  hResbos->Write();
  return 0;
}
