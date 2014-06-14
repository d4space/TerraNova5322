#include <iostream>
#include <fstream>
#include <TFile.h>
#include "TH1D.h"
#include <TGraphErrors.h>             // graph class
#include <TGraphAsymmErrors.h>        // graph class
#include <TLatex.h>

const int nBins = 14;
double WptBins[nBins] = {0.0,7.5,12.5,17.5,24,30,40,50,70,110,150,190,250,600};

void drawDifference(TH1D* iH0,TH1D *iH1){
  TH1D *lXHDiff1 = new TH1D("lXHDiff1","lXHDiff1",iH0->GetNbinsX(),iH0->GetXaxis()->GetXmin(),iH0->GetXaxis()->GetXmax());
  
  lHDiff = (TH1D*)iH0->Clone("lHDiff");
  lHDiff -> Divide(iH1);
  for( int ipt(1);ipt<=nBins-1;ipt++)
  {
    lXHDiff1->SetBinContent(ipt, 1.0);
  //  lHDiff->SetBinError(ipt,iH0->GetBinError(ipt)/iH1->GetBinContent(ipt));
  }
  
  lXHDiff1->SetLineWidth(2); lXHDiff1->SetLineColor(kRed); //lXHDiff1->SetLineStyle(2);

  lHDiff->GetYaxis()->SetRangeUser(0.4,1.6);
  lHDiff->GetYaxis()->SetTitleOffset(0.6);
  lHDiff->GetYaxis()->SetTitleSize(0.06);
  lHDiff->GetYaxis()->SetLabelSize(0.06);
  lHDiff->GetYaxis()->CenterTitle();
  lHDiff->GetXaxis()->SetTitleOffset(1.2);
  lHDiff->GetXaxis()->SetTitleSize(0.06);
  lHDiff->GetXaxis()->SetLabelSize(0.06);
  lHDiff->GetXaxis()->SetTitle("W p_{T} (GeV)");
  lHDiff->GetYaxis()->SetTitle("Data/ResBos");
  gStyle->SetOptStat(0);
  
  lHDiff->SetMarkerSize(0.8);lHDiff->SetLineColor(kBlack); lHDiff->SetMarkerColor(kBlack);
  
  lHDiff->SetTitle("");
  lHDiff->Draw("E1");
  lXHDiff1->Draw("histsame");
  lHDiff->Draw("E1same");
}

int dataVSresbosNormXsec(const TString BaseName)
{
  TString tmpTStr;
  char tmpName[30];
  int Numb;

  TFile *f_Resbos;
  TFile *f_Data;

  f_Resbos = new TFile("../../RstResbos/Resbos_"+BaseName+".root");
  f_Data = new TFile("../Result"+BaseName+"/Result_"+BaseName+".root");

  TH1D *hResbos30 = new TH1D("hResbos30","hResbos30",13,WptBins);hResbos30->Sumw2();
  TH1D *hData = new TH1D("hData","hData",13,WptBins);hData->Sumw2();
  
  TH1D* lResbos30;
  TH1D* lData;

  lResbos30 = (TH1D*)f_Resbos->Get("hResbos30")->Clone();
  lData   = (TH1D*)f_Data->Get("BornEffCorr")->Clone();

  for( int ipt(1);ipt<=nBins-1;ipt++)
  {
    hResbos30->SetBinContent(ipt,lResbos30->GetBinContent(ipt));
    hData->SetBinContent(ipt,lData->GetBinContent(ipt));
    hData->SetBinError(ipt,lData->GetBinError(ipt));
  }

  hData->Scale(1./18.429);
  hData->Scale(1./hData->Integral());
  hResbos30->Scale(1./hResbos30->Integral());
  //hResbos30->GetYaxis()->SetLabelSize(0.045);
  
  hResbos30->SetLineWidth(2);hResbos30->SetLineColor(kRed);
  hData->SetLineColor(kBlack);hData->SetMarkerSize(0.8);
  hData->SetMarkerStyle(kFullCircle); hData->SetMarkerColor(kBlack); hData->SetMarkerSize(1);
  hResbos30->SetTitle("");
  hResbos30->GetYaxis()->SetTitle("Normalized Cross-section");

  TLegend *lL =new TLegend(0.2,0.1,0.6,0.3); lL->SetFillColor(0); lL->SetBorderSize(0);
  lL->AddEntry(hData,"Data","PL");
  lL->AddEntry(hResbos30,"ResBos CT10 NNLO","L");

  TCanvas *lC0 = new TCanvas("Can","Can",800,800); lC0->cd(); lC0->SetLogy();
  lC0->Divide(1,2,0,0);
  lC0->cd(1)->SetPad(0,0.35,0.95,1.0);
  lC0->cd(1)->SetTopMargin(0.1);
  lC0->cd(1)->SetBottomMargin(0.01);
  lC0->cd(1)->SetLeftMargin(0.15);
  lC0->cd(1)->SetRightMargin(0.07);
  gStyle->SetTitleOffset(1.100,"Y");
  gStyle->SetLineWidth(2.);
  gStyle->SetTextSize(1.2);
  gStyle->SetLabelSize(0.06,"xy");
  gStyle->SetTitleSize(0.06,"xy");
  gStyle->SetTitleOffset(1.2,"x");
  gStyle->SetTitleOffset(1.0,"y");
  TGaxis::SetMaxDigits(3);

  gPad->SetLogy(1);
  hResbos30->SetMinimum(2e-5*(hResbos30->GetMaximum()));
  hResbos30->SetMaximum(3.0*(hResbos30->GetMaximum()));
  hResbos30->Draw("HIST");
  hData->Draw("E1Same");
  lL->Draw();

  TPaveText *txt = new TPaveText(0.6,0.65,1.45,0.85,"NDC");
  gPad->GetPrimitive("txt");
  txt->SetFillStyle(0);
  txt->SetBorderSize(0);
  txt->SetTextSize(0.04);
  txt->SetTextAlign(12);
  txt->AddText("#int Ldt #approx 18.4 pb^{-1}");
  txt->AddText("Data 2012, #sqrt{s} = 8 TeV");
  txt->Draw();
  gPad->Modified();
  gPad->cd();
  
  lC0->cd(2)->SetPad(0,0,0.95,0.35);
  lC0->cd(2)->SetTopMargin(0.025);
  lC0->cd(2)->SetBottomMargin(0.3);
  lC0->cd(2)->SetLeftMargin(0.15);
  lC0->cd(2)->SetRightMargin(0.07);
  lC0->cd(2)->SetTickx(1);
  lC0->cd(2)->SetTicky(1);
  drawDifference(hData,hResbos30);
  if(BaseName=="WpToMuNu")
    sprintf(tmpName,"Norm_WpmnPt_Result.png");
  if(BaseName=="WmToMuNu")
    sprintf(tmpName,"Norm_WmmnPt_Result.png");
  if(BaseName=="WpToEleNu")
    sprintf(tmpName,"Norm_WpenPt_Result.png");
  if(BaseName=="WmToEleNu")
    sprintf(tmpName,"Norm_WmenPt_Result.png");
  lC0->SaveAs(tmpName);
  return 0;
}
