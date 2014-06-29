#include "TStyle.h"
#include "../Utils/MyTools.hh"	          // various helper functions
#include "../Utils/CPlot.hh"	          // helper class for plots
#include "../Utils/MitStyleRemix.hh"      // style settings for drawing
//#include <iostream>
#include <fstream>
#include <iostream>
#include <iomanip>

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

int AllOvFidCut(const TString BaseName,const TString VarName)
{
  TString resultDir = "Results";
  
  gSystem->mkdir(resultDir,kTRUE);

  char tmpName[30];
  char tmpNameOrg[30];
  
  const TString format("png"); 
  
  ofstream Fout;
  Fout.open(resultDir+"/"+BaseName+"_"+VarName+"_Ratio.txt");

  Fout << "All Cut / Fiducial Cut"<< endl;
  Fout << "=============================================================" << endl;
  Fout << "Bin" << "\t" << "Ratio" << endl;
  
  TFile *fName;
  
  if(BaseName=="WpToMuNu")
    fName = new TFile("Muon2012LoPU/WpToMuNu_S8_NoCorr.root");
  if(BaseName=="WmToMuNu")
    fName = new TFile("Muon2012LoPU/WmToMuNu_S8_NoCorr.root");
  if(BaseName=="DYToMuMu")
    fName = new TFile("Muon2012LoPU/Muon_DYToMuMu_S8_NoCorr.root");

  double WptBins[4]={0,12.5,50,600};
  double TnPBins[4]={20,40,55,600};
  
  //const Int_t bin=6;
  const Int_t bin=3;
  TH1D* h1_AllCut[bin];
  TH1D* h1_FidCut[bin];
  TH1D* h1_Ratio[bin];

  TH1D* h1_pAllCut[bin];
  TH1D* h1_pFidCut[bin];
  TH1D* h1_pRatio[bin];
  TH1D* h1_mAllCut[bin];
  TH1D* h1_mFidCut[bin];
  TH1D* h1_mRatio[bin];

  TH1D* h1_pt_AllCutFullRange;
  TH1D* h1_pt_FidCutFullRange;
  TH1D* h1_pt_RatioFullRange;
  TH1D *h1_pt_FullRange = new TH1D("h1_pt_FullRange","h1_pt_FullRange",1,0,1);h1_pt_FullRange->Sumw2();

  TH1D* h1_eta_AllCutFullRange;
  TH1D* h1_eta_FidCutFullRange;
  TH1D* h1_eta_RatioFullRange;
  TH1D *h1_eta_FullRange = new TH1D("h1_eta_FullRange","h1_eta_FullRange",1,0,1);h1_eta_FullRange->Sumw2();

  // Plot
  CPlot *pltRatio;
  CPlot *pltpRatio;
  CPlot *pltmRatio;
  TCanvas *myCan;
  myCan = MakeCanvas("myCan","myCan",800,800);
  gStyle->SetEndErrorSize(10);
  gStyle->SetTextFont(132);
  gStyle->SetLegendFont(132);

  //======================
  // Histo from root
  //======================
  /*
  if(VarName=="plusFullRange"){
    h1_pt_AllCutFullRange = (TH1D*)fName->Get("h1_PlusLepPtAllCutFullRange")->Clone("h1_pt_AllCutFullRange");
    h1_pt_FidCutFullRange = (TH1D*)fName->Get("h1_PlusLepPtFidCutFullRange")->Clone("h1_pt_FidCutFullRange");
    h1_eta_AllCutFullRange = (TH1D*)fName->Get("h1_PlusLepEtaAllCutFullRange")->Clone("h1_eta_AllCutFullRange");
    h1_eta_FidCutFullRange = (TH1D*)fName->Get("h1_PlusLepEtaFidCutFullRange")->Clone("h1_eta_FidCutFullRange");
  }
  h1_pt_AllCutFullRange-> Sumw2();
  h1_pt_FidCutFullRange-> Sumw2();
  h1_eta_AllCutFullRange-> Sumw2();
  h1_eta_FidCutFullRange-> Sumw2();

  h1_pt_RatioFullRange = (TH1D*)h1_pt_AllCutFullRange->Clone("h1_pt_RatioFullRange");
  h1_pt_RatioFullRange->Sumw2();
  h1_pt_RatioFullRange->Divide(h1_pt_FidCutFullRange);

  h1_eta_RatioFullRange = (TH1D*)h1_eta_AllCutFullRange->Clone("h1_eta_RatioFullRange");
  h1_eta_RatioFullRange->Sumw2();
  h1_eta_RatioFullRange->Divide(h1_eta_FidCutFullRange);

  cout<<h1_pt_RatioFullRange->GetBinContent(1)<<"\t"<<h1_eta_RatioFullRange->GetBinContent(1)<<endl;

  h1_pt_FullRange->SetBinContent(1,h1_pt_RatioFullRange->GetBinContent(1));
  h1_pt_FullRange->SetBinError(1,h1_pt_RatioFullRange->GetBinError(1));
  h1_eta_FullRange->SetBinContent(1,h1_eta_RatioFullRange->GetBinContent(1));
  h1_eta_FullRange->SetBinError(1,h1_eta_RatioFullRange->GetBinError(1));
  h1_eta_FullRange->SetLineColor(kRed);
  h1_eta_FullRange->SetMarkerColor(kRed);

  h1_pt_FullRange->Draw("E1");
  h1_eta_FullRange->Draw("E1same");
  myCan->SaveAs("Plus_FullRange.png");
  */
  for(int i(0);i<bin;i++)
  {
    if(BaseName=="WpToMuNu"){
      sprintf(tmpNameOrg,"h1_PlusLepPtAllCut_%d",i);
      if(VarName=="lep_eta")
	sprintf(tmpNameOrg,"h1_PlusLepEtaAllCut_%d",i);
      if(VarName=="TnP_bins")
	sprintf(tmpNameOrg,"h1_PlusLepEtaAllCutTnPbins_%d",i);
      
      sprintf(tmpName,"h1_AllCut_%d",i);
      h1_AllCut[i] = (TH1D*)fName->Get(tmpNameOrg)->Clone(tmpName);
      h1_AllCut[i]-> Sumw2();
    }
    if(BaseName=="WmToMuNu"){
      sprintf(tmpNameOrg,"h1_MinuLepPtAllCut_%d",i);
      if(VarName=="lep_eta")
	sprintf(tmpNameOrg,"h1_MinuLepEtaAllCut_%d",i);
      if(VarName=="TnP_bins")
	sprintf(tmpNameOrg,"h1_MinuLepEtaAllCutTnPbins_%d",i);
      
      sprintf(tmpName,"h1_AllCut_%d",i);
      h1_AllCut[i] = (TH1D*)fName->Get(tmpNameOrg)->Clone(tmpName);
      h1_AllCut[i]-> Sumw2();
    }
    
    if(BaseName=="DYToMuMu"){
      sprintf(tmpNameOrg,"h1_PlusLepPtAllCut_%d",i);
      if(VarName=="lep_eta")
	sprintf(tmpNameOrg,"h1_PlusLepEtaAllCut_%d",i);
      if(VarName=="TnP_bins")
	sprintf(tmpNameOrg,"h1_PlusLepEtaAllCutTnPbins_%d",i);
     
      sprintf(tmpName,"h1_pAllCut_%d",i);
      h1_pAllCut[i] = (TH1D*)fName->Get(tmpNameOrg)->Clone(tmpName);
      h1_pAllCut[i]-> Sumw2();
      
      sprintf(tmpNameOrg,"h1_MinuLepPtAllCut_%d",i);
      if(VarName=="lep_eta")
	sprintf(tmpNameOrg,"h1_MinuLepEtaAllCut_%d",i);
      if(VarName=="TnP_bins")
	sprintf(tmpNameOrg,"h1_MinuLepEtaAllCutTnPbins_%d",i);
     
      sprintf(tmpName,"h1_mAllCut_%d",i);
      h1_mAllCut[i] = (TH1D*)fName->Get(tmpNameOrg)->Clone(tmpName);
      h1_mAllCut[i]-> Sumw2();
    }

    if(BaseName=="WpToMuNu"){
      sprintf(tmpNameOrg,"h1_PlusLepPtFidCut_%d",i);
      if(VarName=="lep_eta")
	sprintf(tmpNameOrg,"h1_PlusLepEtaFidCut_%d",i);
      if(VarName=="TnP_bins")
	sprintf(tmpNameOrg,"h1_PlusLepEtaFidCutTnPbins_%d",i);
      
      sprintf(tmpName,"h1_FidCut_%d",i);
      h1_FidCut[i] = (TH1D*)fName->Get(tmpNameOrg)->Clone(tmpName);
      h1_FidCut[i]-> Sumw2();

      sprintf(tmpName,"h1_Ratio_%d",i);
      h1_Ratio[i] = (TH1D*)h1_AllCut[i]->Clone(tmpName);
      h1_Ratio[i]->Sumw2();
      h1_Ratio[i]->Divide(h1_FidCut[i]);
    }
    if(BaseName=="WmToMuNu"){
      sprintf(tmpNameOrg,"h1_MinuLepPtFidCut_%d",i);
      if(VarName=="lep_eta")
	sprintf(tmpNameOrg,"h1_MinuLepEtaFidCut_%d",i);
      if(VarName=="TnP_bins")
	sprintf(tmpNameOrg,"h1_MinuLepEtaFidCutTnPbins_%d",i);
      
      sprintf(tmpName,"h1_FidCut_%d",i);
      h1_FidCut[i] = (TH1D*)fName->Get(tmpNameOrg)->Clone(tmpName);
      h1_FidCut[i]-> Sumw2();

      sprintf(tmpName,"h1_Ratio_%d",i);
      h1_Ratio[i] = (TH1D*)h1_AllCut[i]->Clone(tmpName);
      h1_Ratio[i]->Sumw2();
      h1_Ratio[i]->Divide(h1_FidCut[i]);
    }
    
    if(BaseName=="DYToMuMu"){
      sprintf(tmpNameOrg,"h1_PlusLepPtFidCut_%d",i);
      if(VarName=="lep_eta")
	sprintf(tmpNameOrg,"h1_PlusLepEtaFidCut_%d",i);
      if(VarName=="TnP_bins")
	sprintf(tmpNameOrg,"h1_PlusLepEtaFidCutTnPbins_%d",i);
      
      sprintf(tmpName,"h1_pFidCut_%d",i);
      h1_pFidCut[i] = (TH1D*)fName->Get(tmpNameOrg)->Clone(tmpName);
      h1_pFidCut[i]-> Sumw2();
      
      sprintf(tmpNameOrg,"h1_MinuLepPtFidCut_%d",i);
      if(VarName=="lep_eta")
	sprintf(tmpNameOrg,"h1_MinuLepEtaFidCut_%d",i);
      if(VarName=="TnP_bins")
	sprintf(tmpNameOrg,"h1_MinuLepEtaFidCutTnPbins_%d",i);
      
      sprintf(tmpName,"h1_mFidCut_%d",i);
      h1_mFidCut[i] = (TH1D*)fName->Get(tmpNameOrg)->Clone(tmpName);
      h1_mFidCut[i]-> Sumw2();
      
      sprintf(tmpName,"h1_pRatio_%d",i);
      h1_pRatio[i] = (TH1D*)h1_pAllCut[i]->Clone(tmpName);
      h1_pRatio[i]->Sumw2();
      h1_pRatio[i]->Divide(h1_pFidCut[i]);
      
      sprintf(tmpName,"h1_mRatio_%d",i);
      h1_mRatio[i] = (TH1D*)h1_mAllCut[i]->Clone(tmpName);
      h1_mRatio[i]->Sumw2();
      h1_mRatio[i]->Divide(h1_mFidCut[i]);
    }
    
    Fout<<""<<endl;

    if(BaseName=="DYToMuMu"){
      if(VarName=="TnP_bins")
	Fout<<"Zpt Bin: "<<TnPBins[i]<<" < ZpT < "<<TnPBins[i+1]<<endl;
      else
	Fout<<"Zpt Bin: "<<WptBins[i]<<" < ZpT < "<<WptBins[i+1]<<endl;
      
      Fout<<"Plus muon\t\t\t Minus muon"<<endl;
      Fout<<"AllCut\t FidCut\t AllCut/FidCut\t\tAllCut\t FidCut\t AllCut/FidCut"<<endl;
      for(int ipt(1);ipt<=h1_pAllCut[i]->GetNbinsX(); ipt++)
      {
	Fout<<h1_pAllCut[i]->GetBinContent(ipt)<<"\t"<<h1_pFidCut[i]->GetBinContent(ipt)<<"\t"<<h1_pRatio[i]->GetBinContent(ipt)<<"\t\t"<<h1_mAllCut[i]->GetBinContent(ipt)<<"\t"<<h1_mFidCut[i]->GetBinContent(ipt)<<"\t"<<h1_mRatio[i]->GetBinContent(ipt)<<endl;
      }
      Fout<<"Integral:"<<endl;
      Fout<<h1_pAllCut[i]->Integral()<<"\t"<<h1_pFidCut[i]->Integral()<<"\t"<<h1_pAllCut[i]->Integral()/h1_pFidCut[i]->Integral()<<"\t\t"<<h1_mAllCut[i]->Integral()<<"\t"<<h1_mFidCut[i]->Integral()<<"\t"<<h1_mAllCut[i]->Integral()/h1_mFidCut[i]->Integral()<<endl;
    }

    if(BaseName=="WpToMuNu" || BaseName=="WmToMuNu"){
      if(VarName=="TnP_bins")
	Fout<<"Wpt Bin: "<<TnPBins[i]<<" < WpT < "<<TnPBins[i+1]<<endl;
      else
	Fout<<"Wpt Bin: "<<WptBins[i]<<" < WpT < "<<WptBins[i+1]<<endl;
      
      Fout<<"AllCut\t FidCut\t AllCut/FidCut"<<endl;
      for(int ipt(1);ipt<=h1_AllCut[i]->GetNbinsX(); ipt++)
      {
	Fout<<h1_AllCut[i]->GetBinContent(ipt)<<"\t"<<h1_FidCut[i]->GetBinContent(ipt)<<"\t"<<h1_Ratio[i]->GetBinContent(ipt)<<endl;
      }
      Fout<<"Integral:"<<endl;
      Fout<<h1_AllCut[i]->Integral()<<"\t"<<h1_FidCut[i]->Integral()<<"\t"<<h1_AllCut[i]->Integral()/h1_FidCut[i]->Integral()<<endl;
    }
  }
  
  if(BaseName=="WpToMuNu" || BaseName=="WmToMuNu"){
    h1_Ratio[0]->SetMarkerColor(8);
    h1_Ratio[1]->SetMarkerColor(2);
    h1_Ratio[2]->SetMarkerColor(4);
    
    sprintf(tmpName,BaseName+"_"+VarName);
    if(VarName=="lep_pt")
      sprintf(tmpNameOrg,"Muon p_{T} [GeV/c]");
    if(VarName=="lep_eta" || VarName=="TnP_bins")
      sprintf(tmpNameOrg,"Muon #eta");
    
    pltRatio= new CPlot(tmpName,"",tmpNameOrg,"AllCut/FidCut");
    pltRatio->setOutDir(resultDir);
    pltRatio->AddHist1D(h1_Ratio[0],"E1",8,1,0,24,2);
    pltRatio->AddHist1D(h1_Ratio[1],"E1",2,1,0,25,2);
    pltRatio->AddHist1D(h1_Ratio[2],"E1",4,1,0,26,2);
    pltRatio->SetLegend(0.23,0.7,0.48,0.9);
    pltRatio->GetLegend()->SetTextSize(0.03);
    if(VarName=="TnP_bins"){
      pltRatio->GetLegend()->AddEntry(h1_Ratio[0],"20 < p_{T}^{#mu} #leq 40","lep");
      pltRatio->GetLegend()->AddEntry(h1_Ratio[1],"40 < p_{T}^{#mu} #leq 55","lep");
      pltRatio->GetLegend()->AddEntry(h1_Ratio[2],"p_{T}^{#mu} > 55","lep");
    }else{
      pltRatio->GetLegend()->AddEntry(h1_Ratio[0],"0 < p_{T}^{W} < 12.5","lep");
      pltRatio->GetLegend()->AddEntry(h1_Ratio[1],"12.5 #leq p_{T}^{W} < 50","lep");
      pltRatio->GetLegend()->AddEntry(h1_Ratio[2],"50 #leq p_{T}^{W} < 600","lep");
    }
    if(BaseName=="WpToMuNu")
      pltRatio->GetLegend()->SetHeader("W^{+}#rightarrow #mu^{+} #nu");
    if(BaseName=="WmToMuNu")
      pltRatio->GetLegend()->SetHeader("W^{-}#rightarrow #mu^{-} #bar{#nu}");
    if(VarName=="lep_pt")
      pltRatio->SetYRange(0.7,1.2);
    if(VarName=="lep_eta")
      pltRatio->SetYRange(0.88,1.02);
    if(VarName=="TnP_bins")
      pltRatio->SetYRange(0.85,1.1);
    pltRatio->Draw(myCan,kTRUE,format);
  }

  if(BaseName=="DYToMuMu"){
    h1_pRatio[0]->SetMarkerColor(8);
    h1_pRatio[1]->SetMarkerColor(2);
    h1_pRatio[2]->SetMarkerColor(4);
    
    sprintf(tmpName,BaseName+"_Plus_"+VarName);
    if(VarName=="lep_pt")
      sprintf(tmpNameOrg,"Muon p_{T} [GeV/c]");
    if(VarName=="lep_eta" || VarName=="TnP_bins")
      sprintf(tmpNameOrg,"Muon #eta");
    
    pltpRatio= new CPlot(tmpName,"",tmpNameOrg,"AllCut/FidCut");
    pltpRatio->setOutDir(resultDir);
    pltpRatio->AddHist1D(h1_pRatio[0],"E1",8,1,0,24,2);
    pltpRatio->AddHist1D(h1_pRatio[1],"E1",2,1,0,25,2);
    pltpRatio->AddHist1D(h1_pRatio[2],"E1",4,1,0,26,2);
    pltpRatio->SetLegend(0.23,0.7,0.48,0.9);
    pltpRatio->GetLegend()->SetTextSize(0.03);
    if(VarName=="TnP_bins"){
      pltpRatio->GetLegend()->AddEntry(h1_pRatio[0],"20 < p_{T}^{#mu} #leq 40","lep");
      pltpRatio->GetLegend()->AddEntry(h1_pRatio[1],"40 < p_{T}^{#mu} #leq 55","lep");
      pltpRatio->GetLegend()->AddEntry(h1_pRatio[2],"p_{T}^{#mu} > 55","lep");
    }else{
      pltpRatio->GetLegend()->AddEntry(h1_pRatio[0],"0 < p_{T}^{Z} < 12.5","lep");
      pltpRatio->GetLegend()->AddEntry(h1_pRatio[1],"12.5 #leq p_{T}^{Z} < 50","lep");
      pltpRatio->GetLegend()->AddEntry(h1_pRatio[2],"50 #leq p_{T}^{Z} < 600","lep");
    }
      pltpRatio->GetLegend()->SetHeader("#mu^{+} (Z#rightarrow #mu#mu)");
    if(VarName=="lep_pt")
      pltpRatio->SetYRange(0.7,1.2);
    if(VarName=="lep_eta")
      pltpRatio->SetYRange(0.88,1.02);
    if(VarName=="TnP_bins")
      pltpRatio->SetYRange(0.85,1.1);
    pltpRatio->Draw(myCan,kTRUE,format);

    h1_mRatio[0]->SetMarkerColor(8);
    h1_mRatio[1]->SetMarkerColor(2);
    h1_mRatio[2]->SetMarkerColor(4);
    
    sprintf(tmpName,BaseName+"_Minus_"+VarName);
    if(VarName=="lep_pt")
      sprintf(tmpNameOrg,"Muon p_{T} [GeV/c]");
    if(VarName=="lep_eta" || VarName=="TnP_bins")
      sprintf(tmpNameOrg,"Muon #eta");
    
    pltmRatio= new CPlot(tmpName,"",tmpNameOrg,"AllCut/FidCut");
    pltmRatio->setOutDir(resultDir);
    pltmRatio->AddHist1D(h1_mRatio[0],"E1",8,1,0,24,2);
    pltmRatio->AddHist1D(h1_mRatio[1],"E1",2,1,0,25,2);
    pltmRatio->AddHist1D(h1_mRatio[2],"E1",4,1,0,26,2);
    pltmRatio->SetLegend(0.23,0.7,0.48,0.9);
    pltmRatio->GetLegend()->SetTextSize(0.03);
    if(VarName=="TnP_bins"){
      pltmRatio->GetLegend()->AddEntry(h1_mRatio[0],"20 < p_{T}^{#mu} #leq 40","lep");
      pltmRatio->GetLegend()->AddEntry(h1_mRatio[1],"40 < p_{T}^{#mu} #leq 55","lep");
      pltmRatio->GetLegend()->AddEntry(h1_mRatio[2],"p_{T}^{#mu} > 55","lep");
    }else{
      pltmRatio->GetLegend()->AddEntry(h1_mRatio[0],"0 < p_{T}^{Z} < 12.5","lep");
      pltmRatio->GetLegend()->AddEntry(h1_mRatio[1],"12.5 #leq p_{T}^{Z} < 50","lep");
      pltmRatio->GetLegend()->AddEntry(h1_mRatio[2],"50 #leq p_{T}^{Z} < 600","lep");
    }
      pltmRatio->GetLegend()->SetHeader("#mu^{-} (Z#rightarrow #mu#mu)");
    if(VarName=="lep_pt")
      pltmRatio->SetYRange(0.7,1.2);
    if(VarName=="lep_eta")
      pltmRatio->SetYRange(0.88,1.02);
    if(VarName=="TnP_bins")
      pltmRatio->SetYRange(0.85,1.1);
    pltmRatio->Draw(myCan,kTRUE,format);
  }
  Fout.close();
  myCan->Clear();

  return 0;
}
