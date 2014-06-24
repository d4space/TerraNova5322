#include <iostream>
#include <fstream>
#include <TFile.h>
#include "TH1D.h"
#include <TGraphErrors.h>             // graph class
#include <TGraphAsymmErrors.h>        // graph class
#include <TLatex.h>

const int nBins = 14;

int combine(const TString BaseName)
{
  TString tmpTStr;
  char tmpName[30],tmpName_org[30];
  int Numb;

  TFile *f_Data_1;
  TFile *f_Data_2;

  if (BaseName=="Wmuon"){
    f_Data_1   = new TFile("../../ResultWpToMuNu/Result_WpToMuNu.root");
    f_Data_2   = new TFile("../../ResultWmToMuNu/Result_WmToMuNu.root");
  }else if (BaseName=="Wele"){
    f_Data_1   = new TFile("../../ResultWpToEleNu/Result_WpToEleNu.root");
    f_Data_2   = new TFile("../../ResultWmToEleNu/Result_WmToEleNu.root");
  }

  TH1D* lPowheg_1;
  TH1D* lPowheg_2;
  TH1D* lData_1;
  TH1D* lData_2;
  TH1D* hRD_1;
  TH1D* hRD_2;
  
  lPowheg_1 = (TH1D*)f_Data_1->Get("SVD_Born.Gen")->Clone("lPowheg_1");
  lPowheg_2 = (TH1D*)f_Data_2->Get("SVD_Born.Gen")->Clone("lPowheg_2");
  lData_1   = (TH1D*)f_Data_1->Get("BornEffCorr")->Clone("lData_1");
  lData_2   = (TH1D*)f_Data_2->Get("BornEffCorr")->Clone("lData_2");
  hRD_1   = (TH1D*)f_Data_1->Get("data_Rec")->Clone("hRD_1");
  hRD_2   = (TH1D*)f_Data_2->Get("data_Rec")->Clone("hRD_2");

  Double_t hRD1[nBins-1],hRD1Err[nBins-1];
  Double_t hRD2[nBins-1],hRD2Err[nBins-1];
  Double_t hRDmean[nBins-1],hRDmeanErr[nBins-1];
  
  Double_t RD1[nBins-1],RD1Err[nBins-1];
  Double_t RD2[nBins-1],RD2Err[nBins-1];
  Double_t RDmean[nBins-1],RDmeanErr[nBins-1];
  
  Double_t MC1[nBins-1],MC1Err[nBins-1];
  Double_t MC2[nBins-1],MC2Err[nBins-1];
  Double_t MCmean[nBins-1],MCmeanErr[nBins-1];
  
  TH1D* SVD_BornGen = new TH1D("SVD_BornGen","SVD_BornGen",13,0,13);SVD_BornGen->Sumw2();
  TH1D* BornEffCorr = new TH1D("BornEffCorr","BornEffCorr",13,0,13);BornEffCorr->Sumw2();
  TH1D* data_Rec = new TH1D("data_Rec","data_Rec",13,0,13);data_Rec->Sumw2();

  if(BaseName=="Wmuon")
    TFile f_out("Result_WinclMu.root","recreate");
  if(BaseName=="Wele")
    TFile f_out("Result_WinclEle.root","recreate");

  for( int ipt(0);ipt<nBins-1;ipt++)
  {
    hRD1[ipt] = hRD_1->GetBinContent(ipt+1);
    hRD1Err[ipt] = hRD_1->GetBinError(ipt+1);
    hRD2[ipt] = hRD_2->GetBinContent(ipt+1);
    hRD2Err[ipt] = hRD_2->GetBinError(ipt+1);
    hRDmeanErr[ipt]=1.0/(hRD1Err[ipt]*hRD1Err[ipt])+1.0/(hRD2Err[ipt]*hRD2Err[ipt]);
    hRDmean[ipt]=(RD1[ipt]/(hRD1Err[ipt]*hRD1Err[ipt])+hRD2[ipt]/(hRD2Err[ipt]*hRD2Err[ipt]))/hRDmeanErr[ipt];
    
    RD1[ipt] = lData_1->GetBinContent(ipt+1);
    RD1Err[ipt] = lData_1->GetBinError(ipt+1);
    RD2[ipt] = lData_2->GetBinContent(ipt+1);
    RD2Err[ipt] = lData_2->GetBinError(ipt+1);
    RDmeanErr[ipt]=1.0/(RD1Err[ipt]*RD1Err[ipt])+1.0/(RD2Err[ipt]*RD2Err[ipt]);
    RDmean[ipt]=(RD1[ipt]/(RD1Err[ipt]*RD1Err[ipt])+RD2[ipt]/(RD2Err[ipt]*RD2Err[ipt]))/RDmeanErr[ipt];
    
    MC1[ipt] = lPowheg_1->GetBinContent(ipt+1);
    MC1Err[ipt] =  lPowheg_1->GetBinError(ipt+1);
    MC2[ipt] = lPowheg_2->GetBinContent(ipt+1);
    MC2Err[ipt] =  lPowheg_2->GetBinError(ipt+1);
    MCmeanErr[ipt]=1.0/(MC1Err[ipt]*MC1Err[ipt])+1.0/(MC2Err[ipt]*MC2Err[ipt]);
    MCmean[ipt]=(MC1[ipt]/(MC1Err[ipt]*MC1Err[ipt])+MC2[ipt]/(MC2Err[ipt]*MC2Err[ipt]))/MCmeanErr[ipt];
    cout<<100*MC1Err[ipt]/MC1[ipt]<<"  "<<100*MC2Err[ipt]/MC2[ipt]<<endl;
    
    //cout <<ipt+1<<"\t"<<(RD1[ipt]/(RD1Err[ipt]*RD1Err[ipt])+RD2[ipt]/(RD2Err[ipt]*RD2Err[ipt]))/(1./(RD1Err[ipt]*RD1Err[ipt])+1.0/(RD2Err[ipt]*RD2Err[ipt]))<<"\t"<<RDmean[ipt]<<"\t"<<sqrt(1.0/RDmeanErr[ipt])<<"\t"<<MCmean[ipt]<<"\t"<<sqrt(1.0/MCmeanErr[ipt])<<endl;
    
    BornEffCorr->SetBinContent(ipt+1, RDmean[ipt]);
    BornEffCorr->SetBinError(ipt+1, sqrt(1.0/RDmeanErr[ipt]));
    
    SVD_BornGen->SetBinContent(ipt+1, MCmean[ipt]);
    SVD_BornGen->SetBinError(ipt+1, sqrt(1.0/MCmeanErr[ipt]));
    
    data_Rec->SetBinContent(ipt+1, hRDmean[ipt]);
    data_Rec->SetBinError(ipt+1, sqrt(1.0/hRDmeanErr[ipt]));
  }
  BornEffCorr->Write();
  SVD_BornGen->Write();
  data_Rec->Write();

  return 0;
}
