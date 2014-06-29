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

int AllOvFidCut_TnP(const TString BaseName)
{
  TString resultDir = "Results";
  
  gSystem->mkdir(resultDir,kTRUE);

  char tmpName[30];
  char tmpNameOrg[30];
  
  const TString format("png"); 
  
  ofstream Fout;
  Fout.open(resultDir+"/"+BaseName+"_Ratio.txt");

  Fout << "All Cut / Fiducial Cut"<< endl;
  Fout << "=============================================================" << endl;
  Fout << "Bin" << "\t" << "Ratio" << endl;
  
  TFile *pfName;
  TFile *mfName;
  TFile *zfName;
  
  pfName = new TFile("Muon2012LoPU/WpToMuNu_S8_NoCorr.root");
  mfName = new TFile("Muon2012LoPU/WmToMuNu_S8_NoCorr.root");
  zfName = new TFile("Muon2012LoPU/Muon_DYToMuMu_S8_NoCorr.root");

  double TnPBins[4]={20,40,55,600};
  
  const Int_t bin=3;
  
  TH1D* h1_ZpAllCut[bin];
  TH1D* h1_ZpFidCut[bin];
  TH1D* h1_ZpRatio[bin];
  TH1D* h1_ZmAllCut[bin];
  TH1D* h1_ZmFidCut[bin];
  TH1D* h1_ZmRatio[bin];
  TH1D* h1_pAllCut[bin];
  TH1D* h1_pFidCut[bin];
  TH1D* h1_pRatio[bin];
  TH1D* h1_mAllCut[bin];
  TH1D* h1_mFidCut[bin];
  TH1D* h1_mRatio[bin];

  // Plot
  CPlot *pltRatio;
  TCanvas *myCan;
  myCan = MakeCanvas("myCan","myCan",800,800);
  gStyle->SetEndErrorSize(10);
  gStyle->SetTextFont(132);
  gStyle->SetLegendFont(132);

  //======================
  // Histo from root
  //======================
  for(int i(0);i<bin;i++)
  {
    //Wboson
    sprintf(tmpName,"h1_pAllCut_%d",i);
    sprintf(tmpNameOrg,"h1_PlusLepEtaAllCutTnPbins_%d",i);
    h1_pAllCut[i] = (TH1D*)pfName->Get(tmpNameOrg)->Clone(tmpName);
    h1_pAllCut[i]-> Sumw2();

    sprintf(tmpName,"h1_mAllCut_%d",i);
    sprintf(tmpNameOrg,"h1_MinuLepEtaAllCutTnPbins_%d",i);
    h1_mAllCut[i] = (TH1D*)mfName->Get(tmpNameOrg)->Clone(tmpName);
    h1_mAllCut[i]-> Sumw2();

    sprintf(tmpName,"h1_pFidCut_%d",i);
    sprintf(tmpNameOrg,"h1_PlusLepEtaFidCutTnPbins_%d",i);
    h1_pFidCut[i] = (TH1D*)pfName->Get(tmpNameOrg)->Clone(tmpName);
    h1_pFidCut[i]-> Sumw2();

    sprintf(tmpName,"h1_mFidCut_%d",i);
    sprintf(tmpNameOrg,"h1_MinuLepEtaFidCutTnPbins_%d",i);
    h1_mFidCut[i] = (TH1D*)mfName->Get(tmpNameOrg)->Clone(tmpName);
    h1_mFidCut[i]-> Sumw2();

    sprintf(tmpName,"h1_pRatio_%d",i);
    h1_pRatio[i] = (TH1D*)h1_pAllCut[i]->Clone(tmpName);
    h1_pRatio[i]->Sumw2();
    h1_pRatio[i]->Divide(h1_pFidCut[i]);
    
    sprintf(tmpName,"h1_mRatio_%d",i);
    h1_mRatio[i] = (TH1D*)h1_mAllCut[i]->Clone(tmpName);
    h1_mRatio[i]->Sumw2();
    h1_mRatio[i]->Divide(h1_mFidCut[i]);
    
    //Zboson
    sprintf(tmpName,"h1_ZpAllCut_%d",i);
    sprintf(tmpNameOrg,"h1_PlusLepEtaAllCutTnPbins_%d",i);
    h1_ZpAllCut[i] = (TH1D*)zfName->Get(tmpNameOrg)->Clone(tmpName);
    h1_ZpAllCut[i]-> Sumw2();

    sprintf(tmpName,"h1_ZmAllCut_%d",i);
    sprintf(tmpNameOrg,"h1_MinuLepEtaAllCutTnPbins_%d",i);
    h1_ZmAllCut[i] = (TH1D*)zfName->Get(tmpNameOrg)->Clone(tmpName);
    h1_ZmAllCut[i]-> Sumw2();

    sprintf(tmpName,"h1_ZpFidCut_%d",i);
    sprintf(tmpNameOrg,"h1_PlusLepEtaFidCutTnPbins_%d",i);
    h1_ZpFidCut[i] = (TH1D*)zfName->Get(tmpNameOrg)->Clone(tmpName);
    h1_ZpFidCut[i]-> Sumw2();

    sprintf(tmpName,"h1_ZmFidCut_%d",i);
    sprintf(tmpNameOrg,"h1_MinuLepEtaFidCutTnPbins_%d",i);
    h1_ZmFidCut[i] = (TH1D*)zfName->Get(tmpNameOrg)->Clone(tmpName);
    h1_ZmFidCut[i]-> Sumw2();

    sprintf(tmpName,"h1_ZpRatio_%d",i);
    h1_ZpRatio[i] = (TH1D*)h1_ZpAllCut[i]->Clone(tmpName);
    h1_ZpRatio[i]->Sumw2();
    h1_ZpRatio[i]->Divide(h1_ZpFidCut[i]);
    
    sprintf(tmpName,"h1_ZmRatio_%d",i);
    h1_ZmRatio[i] = (TH1D*)h1_ZmAllCut[i]->Clone(tmpName);
    h1_ZmRatio[i]->Sumw2();
    h1_ZmRatio[i]->Divide(h1_ZmFidCut[i]);
    
    Fout<<""<<endl;
    Fout<<"Wpt Bin: "<<TnPBins[i]<<" < WpT < "<<TnPBins[i+1]<<endl;
    Fout<<"pAll\t pFid\t pAll/pFid\t\t mAll\t mFid\t mAll/mFid"<<endl;
    for(int ipt(1);ipt<=h1_pAllCut[i]->GetNbinsX(); ipt++)
    {
      Fout<<h1_pAllCut[i]->GetBinContent(ipt)<<"\t"<<h1_pFidCut[i]->GetBinContent(ipt)<<"\t"<<h1_pRatio[i]->GetBinContent(ipt)<<"\t\t"<<h1_mAllCut[i]->GetBinContent(ipt)<<"\t"<<h1_mFidCut[i]->GetBinContent(ipt)<<"\t"<<h1_mRatio[i]->GetBinContent(ipt)<<endl;
    }
  
    Fout<<""<<endl;
    Fout<<"Zpt Bin: "<<TnPBins[i]<<" < ZpT < "<<TnPBins[i+1]<<endl;
    Fout<<"pAll\t pFid\t pAll/pFid\t\t mAll\t mFid\t mAll/mFid"<<endl;
    for(int ipt(1);ipt<=h1_ZpAllCut[i]->GetNbinsX(); ipt++)
    {
      Fout<<h1_ZpAllCut[i]->GetBinContent(ipt)<<"\t"<<h1_ZpFidCut[i]->GetBinContent(ipt)<<"\t"<<h1_ZpRatio[i]->GetBinContent(ipt)<<"\t\t"<<h1_ZmAllCut[i]->GetBinContent(ipt)<<"\t"<<h1_ZmFidCut[i]->GetBinContent(ipt)<<"\t"<<h1_ZmRatio[i]->GetBinContent(ipt)<<endl;
    }
  
    h1_pRatio[i]->SetMarkerColor(2);
    h1_mRatio[i]->SetMarkerColor(4);
    h1_ZpRatio[i]->SetMarkerColor(kGreen+3);
    h1_ZmRatio[i]->SetMarkerColor(kMagenta+2);

    sprintf(tmpName,"Eta_LeptBin_%d",i);
    sprintf(tmpNameOrg,"Muon #eta");
    pltRatio= new CPlot(tmpName,"",tmpNameOrg,"AllCut/FidCut");
    pltRatio->setOutDir(resultDir);
    pltRatio->AddHist1D(h1_pRatio[i],"E1",2,1,0,24,2);
    pltRatio->AddHist1D(h1_mRatio[i],"E1",4,1,0,25,2);
    pltRatio->AddHist1D(h1_ZpRatio[i],"E1",kGreen+3,1,0,26,2);
    pltRatio->AddHist1D(h1_ZmRatio[i],"E1",kMagenta+2,1,0,32,2);
    pltRatio->SetLegend(0.23,0.7,0.48,0.9);
    pltRatio->GetLegend()->SetTextSize(0.03);
    pltRatio->GetLegend()->AddEntry(h1_pRatio[i],"#mu^{+} (W^{+}#rightarrow #mu^{+} #nu)","lep");
    pltRatio->GetLegend()->AddEntry(h1_mRatio[i],"#mu^{-} (W^{-}#rightarrow #mu^{-} #bar{#nu})","lep");
    pltRatio->GetLegend()->AddEntry(h1_ZpRatio[i],"#mu^{+} (Z#rightarrow #mu^{+} #mu^{-})","lep");
    pltRatio->GetLegend()->AddEntry(h1_ZmRatio[i],"#mu^{-} (Z#rightarrow #mu^{-} #mu^{+})","lep");
    sprintf(tmpName,"%.1f < p_{T}^{#mu} < %.1f",TnPBins[i],TnPBins[i+1]);
    pltRatio->GetLegend()->SetHeader(tmpName);
    pltRatio->SetYRange(0.8,1.1);
    pltRatio->Draw(myCan,kTRUE,format);
  }
  Fout.close();
  myCan->Clear();

  return 0;
}
