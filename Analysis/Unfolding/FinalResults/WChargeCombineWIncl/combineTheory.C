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

  TString resultDir = "Result"+BaseName;
  gSystem->mkdir(resultDir,kTRUE);


  TFile *f_Fewz_1;
  TFile *f_Fewz_2;
  TFile *f_Resbos_1;
  TFile *f_Resbos_2;

  if(BaseName == "WInclToMuNu")
  {
    double fScale_Wp[14] = {0, 64.48, 1.105, 8.274, 9.716, 7.226, 8.534, 5.76, 6.4783, 4.5879, 1.3952, 0.52169, 0.2662, 0.09476};
    double fScale_Wm[14] = {0, 45.388, 1.601, 4.628, 6.315, 4.866, 5.935, 4.1334, 4.6873, 3.4607, 1.0583, 0.36488, 0.18399, 0.063812};
    f_Fewz_1 = new TFile("../../../RstFEWZ/Wp_Mu_NNLO.root");
    f_Fewz_2 = new TFile("../../../RstFEWZ/Wm_Mu_NNLO.root");
    f_Resbos_1 = new TFile("../../../RstResbos/Resbos_WpToMuNu.root");
    f_Resbos_2 = new TFile("../../../RstResbos/Resbos_WmToMuNu.root");
  }
  if(BaseName == "WInclToEleNu")
  {
    double fScale_Wp[14] = {0, 74.18, 2.079, 8.808, 10.496, 7.646, 8.934, 5.998, 6.6528, 4.7955, 1.4991, 0.4733, 0.28867, 0.09178};
    double fScale_Wm[14] = {0, 48.427, 1.315, 5.692, 6.855, 5.33, 6.332, 4.3037, 4.9102, 3.7312, 1.1115, 0.38448, 0.19356, 0.062427};
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

  //if(BaseName=="WInclToMuNu")
  //  TFile f_out("Theory_Muon.root","recreate");
  //if(BaseName=="WInclToEleNu")
  //  //TFile f_out("Theory_Ele.root","recreate");
  //  TFile f_out("ResultWInclToEleNu/Result_WInclToEleNu_Theory.root","recreate");
  
  tmpTStr = resultDir+"/Result_"+BaseName+"_Theory.root";
  TFile *f_Out    = new TFile(tmpTStr,"recreate");

  for( int ipt(0);ipt<nBins-1;ipt++)
  {
    MC1[ipt] = lFewz_1->GetBinContent(ipt+1);
    //MC1Err[ipt] = sqrt((lFewz_1->GetBinError(ipt+1))*(lFewz_1->GetBinError(ipt+1)) + (fScale_Wp[ipt+1])*(fScale_Wp[ipt+1]));
    MC1Err[ipt] = sqrt((lFewz_1->GetBinError(ipt+1))*(lFewz_1->GetBinError(ipt+1)) );
    MC2[ipt] = lFewz_2->GetBinContent(ipt+1);
    //MC2Err[ipt] = sqrt((lFewz_2->GetBinError(ipt+1))*(lFewz_2->GetBinError(ipt+1)) + (fScale_Wm[ipt+1])*(fScale_Wm[ipt+1]));
    MC2Err[ipt] = sqrt((lFewz_2->GetBinError(ipt+1))*(lFewz_2->GetBinError(ipt+1)) );
    MCmeanErr[ipt]=sqrt((MC1Err[ipt]*MC1Err[ipt])+(MC2Err[ipt]*MC2Err[ipt]));
    MCmean[ipt]=MC1[ipt]+MC2[ipt];
    
    for( int i(0);i<7;i++)
    {
      Resb1[i] = lResbos1[i]->GetBinContent(ipt+1);
      Resb1Err[i] = lResbos1[i]->GetBinError(ipt+1);
      Resb2[i] = lResbos2[i]->GetBinContent(ipt+1);
      Resb2Err[i] = lResbos2[i]->GetBinError(ipt+1);
      ResbErr[i]=sqrt((Resb1Err[i]*Resb1Err[i])+(Resb2Err[i]*Resb2Err[i]));
      Resb[i]=Resb1[i]+Resb2[i];
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
    //hxsec->SetBinError(ipt+1, sqrt(1.0/MCmeanErr[ipt]));
    hxsec->SetBinError(ipt+1, MCmeanErr[ipt]);
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
