#include <iostream>
#include <fstream>
#include <TFile.h>
#include "TH1D.h"
#include <TGraphErrors.h>             // graph class
#include <TGraphAsymmErrors.h>        // graph class
#include <TLatex.h>

const int nBins = 14;

int combineTheory(const TString BaseName)
{
  TString tmpTStr;
  char tmpName[30],tmpName_org[30];
  int Numb;

  TFile *f_Fewz_1;
  TFile *f_Fewz_2;
  TFile *f_Resbos_1;
  TFile *f_Resbos_2;

  if(BaseName == "Wmuon")
  {
    f_Fewz_1 = new TFile("../../../RstFEWZ/Wp_Mu_NNLO.root");
    f_Fewz_2 = new TFile("../../../RstFEWZ/Wm_Mu_NNLO.root");
    f_Resbos_1 = new TFile("../../../RstResbos/Resbos_WpToMuNu.root");
    f_Resbos_2 = new TFile("../../../RstResbos/Resbos_WmToMuNu.root");
  }
  if(BaseName == "Wele")
  {
    f_Fewz_1 = new TFile("../../../RstFEWZ/Wp_Ele_NNLO.root");
    f_Fewz_2 = new TFile("../../../RstFEWZ/Wm_Ele_NNLO.root");
    f_Resbos_1 = new TFile("../../../RstResbos/Resbos_WpToEleNu.root");
    f_Resbos_2 = new TFile("../../../RstResbos/Resbos_WmToEleNu.root");
  }

  TH1D* lFewz_1;
  TH1D* lFewz_2;
  
  TH1D* lResbos1[7];
  TH1D* lResbos2[7];
  
  for( int i(0);i<7;i++)
  {
    Numb = 29+i;
    sprintf(tmpName_org,"hResbos%d",Numb);
    sprintf(tmpName,"lResbos1_%d",i);
    lResbos1[i] = (TH1D*)f_Resbos_1->Get(tmpName_org)->Clone(tmpName);
    sprintf(tmpName,"lResbos2_%d",i);
    lResbos2[i] = (TH1D*)f_Resbos_2->Get(tmpName_org)->Clone(tmpName);
  }

  lFewz_1 = (TH1D*)f_Fewz_1->Get("hxsec")->Clone("lFewz_1");
  lFewz_2 = (TH1D*)f_Fewz_2->Get("hxsec")->Clone("lFewz_2");

  Double_t MC1[nBins-1],MC1Err[nBins-1];
  Double_t MC2[nBins-1],MC2Err[nBins-1];
  Double_t MCmean[nBins-1],MCmeanErr[nBins-1];

  Double_t Resb1[7], Resb1Err[7];
  Double_t Resb2[7], Resb2Err[7];
  Double_t Resb[7], ResbErr[7];

  TH1D* hxsec = new TH1D("hxsec","hxsec",13,0,13);hxsec->Sumw2();
  TH1D* hResbos29 = new TH1D("hResbos29","hResbos29",13,0,13);hResbos29->Sumw2();
  TH1D* hResbos30 = new TH1D("hResbos30","hResbos30",13,0,13);hResbos30->Sumw2();
  TH1D* hResbos31 = new TH1D("hResbos31","hResbos31",13,0,13);hResbos31->Sumw2();
  TH1D* hResbos32 = new TH1D("hResbos32","hResbos32",13,0,13);hResbos32->Sumw2();
  TH1D* hResbos33 = new TH1D("hResbos33","hResbos33",13,0,13);hResbos33->Sumw2();
  TH1D* hResbos34 = new TH1D("hResbos34","hResbos34",13,0,13);hResbos34->Sumw2();
  TH1D* hResbos35 = new TH1D("hResbos35","hResbos35",13,0,13);hResbos35->Sumw2();

  if(BaseName=="Wmuon")
    TFile f_out("Theory_Muon.root","recreate");
  if(BaseName=="Wele")
    TFile f_out("Theory_Ele.root","recreate");

  for( int ipt(0);ipt<nBins-1;ipt++)
  {
    MC1[ipt] = lFewz_1->GetBinContent(ipt+1);
    MC1Err[ipt] = lFewz_1->GetBinError(ipt+1);
    MC2[ipt] = lFewz_2->GetBinContent(ipt+1);
    MC2Err[ipt] = lFewz_2->GetBinError(ipt+1);
    MCmeanErr[ipt]=1.0/(MC1Err[ipt]*MC1Err[ipt])+1.0/(MC2Err[ipt]*MC2Err[ipt]);
    MCmean[ipt]=(MC1[ipt]/(MC1Err[ipt]*MC1Err[ipt])+MC2[ipt]/(MC2Err[ipt]*MC2Err[ipt]))/MCmeanErr[ipt];
    
    for( int i(0);i<7;i++)
    {
      Resb1[i] = lResbos1[i]->GetBinContent(ipt+1);
      Resb1Err[i] = lResbos1[i]->GetBinError(ipt+1);
      Resb2[i] = lResbos2[i]->GetBinContent(ipt+1);
      Resb2Err[i] = lResbos2[i]->GetBinError(ipt+1);
      ResbErr[i]=1.0/(Resb1Err[i]*Resb1Err[i])+1.0/(Resb2Err[i]*Resb2Err[i]);
      Resb[i]=(Resb1[i]/(Resb1Err[i]*Resb1Err[i])+Resb2[i]/(Resb2Err[i]*Resb2Err[i]))/ResbErr[i];
    }
    
    hResbos29 -> SetBinContent(ipt+1, Resb[0]);
    hResbos30 -> SetBinContent(ipt+1, Resb[1]);
    hResbos31 -> SetBinContent(ipt+1, Resb[2]);
    hResbos32 -> SetBinContent(ipt+1, Resb[3]);
    hResbos33 -> SetBinContent(ipt+1, Resb[4]);
    hResbos34 -> SetBinContent(ipt+1, Resb[5]);
    hResbos35 -> SetBinContent(ipt+1, Resb[6]);
    
    hResbos29 -> SetBinError(ipt+1, ResbErr[0]);
    hResbos30 -> SetBinError(ipt+1, ResbErr[1]);
    hResbos31 -> SetBinError(ipt+1, ResbErr[2]);
    hResbos32 -> SetBinError(ipt+1, ResbErr[3]);
    hResbos33 -> SetBinError(ipt+1, ResbErr[4]);
    hResbos34 -> SetBinError(ipt+1, ResbErr[5]);
    hResbos35 -> SetBinError(ipt+1, ResbErr[6]);
    
    hxsec->SetBinContent(ipt+1, MCmean[ipt]);
    hxsec->SetBinError(ipt+1, sqrt(1.0/MCmeanErr[ipt]));
  }
  hxsec->Write();
  hResbos29 -> Write();
  hResbos30 -> Write();
  hResbos31 -> Write();
  hResbos32 -> Write();
  hResbos33 -> Write();
  hResbos34 -> Write();
  hResbos35 -> Write();

  return 0;
}
