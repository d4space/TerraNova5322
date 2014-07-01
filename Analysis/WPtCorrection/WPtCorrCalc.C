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

int WPtCorrCalc(const TString BaseName)
{
  TString resultDir = "Results";
  
  gSystem->mkdir(resultDir,kTRUE);

  char tmpName[30];
  
  const TString format("png"); 
  
  ofstream Fout;
  Fout.open(resultDir+"/"+BaseName+"_WpMN.txt");

  TFile *fWpMN_MC;
  TFile *fWmMN_MC;
  TFile *fWpEN_MC;
  TFile *fWmEN_MC;
  fWpMN_MC = new TFile("Muon2012LoPU/WpToMuNu_S8_SmeaRecEffCorr.root");
  fWmMN_MC = new TFile("Muon2012LoPU/WmToMuNu_S8_SmeaRecEffCorr.root");
  fWpEN_MC = new TFile("Electron2012LoPU/WpToEleNu_S8_SmeaRecEffCorr.root");
  fWmEN_MC = new TFile("Electron2012LoPU/WmToEleNu_S8_SmeaRecEffCorr.root");

  TFile *fWMN_RD, *fWEN_RD;
  fWMN_RD = new TFile("../RstSelection/SigYields_Mu_Norm_20140629.root");
  fWEN_RD = new TFile("../RstSelection/SigYields_El_Norm_20140629.root");

  TH1D* h1_WpT_WpToMN_MC;
  TH1D* h1_WpT_WpToMN_MC_NormToRD;
  TH1D* h1_WpT_WpToMN_RD;
  TH1D* h1_WpT_WpToMN_ratio;

  TH1D* h1_WpT_WmToMN_MC;
  TH1D* h1_WpT_WmToMN_MC_NormToRD;
  TH1D* h1_WpT_WmToMN_RD;
  TH1D* h1_WpT_WmToMN_ratio;

  TH1D* h1_WpT_WpToEN_MC;
  TH1D* h1_WpT_WpToEN_MC_NormToRD;
  TH1D* h1_WpT_WpToEN_RD;
  TH1D* h1_WpT_WpToEN_ratio;

  TH1D* h1_WpT_WmToEN_MC;
  TH1D* h1_WpT_WmToEN_MC_NormToRD;
  TH1D* h1_WpT_WmToEN_RD;
  TH1D* h1_WpT_WmToEN_ratio;
  // Plot
  CPlot *pltWpMN, *pltWpMN_ratio;
  CPlot *pltWmMN, *pltWmMN_ratio;
  CPlot *pltWpEN, *pltWpEN_ratio;
  CPlot *pltWmEN, *pltWmEN_ratio;
  TCanvas *myCan;
  myCan = MakeCanvas("myCan","myCan",800,800);
  gStyle->SetEndErrorSize(10);
  gStyle->SetTextFont(132);
  gStyle->SetLegendFont(132);

  //======================
  // Histo from root
  //======================
  h1_WpT_WpToMN_MC = (TH1D*)fWpMN_MC->Get("h1_Wp_pt")->Clone("h1_WpT_WpToMN_MC");
  h1_WpT_WmToMN_MC = (TH1D*)fWmMN_MC->Get("h1_Wm_pt")->Clone("h1_WpT_WmToMN_MC");
  h1_WpT_WpToEN_MC = (TH1D*)fWpEN_MC->Get("h1_Wp_pt")->Clone("h1_WpT_WpToEN_MC");
  h1_WpT_WmToEN_MC = (TH1D*)fWmEN_MC->Get("h1_Wm_pt")->Clone("h1_WpT_WmToEN_MC");
  h1_WpT_WpToMN_MC->Sumw2();
  h1_WpT_WmToMN_MC->Sumw2();
  h1_WpT_WpToEN_MC->Sumw2();
  h1_WpT_WmToEN_MC->Sumw2();
  h1_WpT_WpToMN_RD = (TH1D*)fWMN_RD->Get("hSigWPpt")->Clone("h1_WpT_WpToMN_RD");
  h1_WpT_WmToMN_RD = (TH1D*)fWMN_RD->Get("hSigWMpt")->Clone("h1_WpT_WmToMN_RD");
  h1_WpT_WpToEN_RD = (TH1D*)fWEN_RD->Get("hSigWPpt")->Clone("h1_WpT_WpToEN_RD");
  h1_WpT_WmToEN_RD = (TH1D*)fWEN_RD->Get("hSigWMpt")->Clone("h1_WpT_WmToEN_RD");
  h1_WpT_WpToMN_RD->Sumw2();
  h1_WpT_WmToMN_RD->Sumw2();
  h1_WpT_WpToEN_RD->Sumw2();
  h1_WpT_WmToEN_RD->Sumw2();


  h1_WpT_WpToMN_ratio = (TH1D*)h1_WpT_WpToMN_RD->Clone("h1_WpT_WpToMN_ratio");
  h1_WpT_WmToMN_ratio = (TH1D*)h1_WpT_WmToMN_RD->Clone("h1_WpT_WmToMN_ratio");
  h1_WpT_WpToEN_ratio = (TH1D*)h1_WpT_WpToEN_RD->Clone("h1_WpT_WpToEN_ratio");
  h1_WpT_WmToEN_ratio = (TH1D*)h1_WpT_WmToEN_RD->Clone("h1_WpT_WmToEN_ratio");
  //cout<<"number h1_WpT_WpToMN_ratio: "<<h1_WpT_WpToMN_ratio->Integral()<<endl;
  h1_WpT_WpToMN_MC_NormToRD = (TH1D*)h1_WpT_WpToMN_MC->Clone("h1_WpT_WpToMN_MC_NormToRD");
  h1_WpT_WmToMN_MC_NormToRD = (TH1D*)h1_WpT_WmToMN_MC->Clone("h1_WpT_WmToMN_MC_NormToRD");
  h1_WpT_WpToEN_MC_NormToRD = (TH1D*)h1_WpT_WpToEN_MC->Clone("h1_WpT_WpToEN_MC_NormToRD");
  h1_WpT_WmToEN_MC_NormToRD = (TH1D*)h1_WpT_WmToEN_MC->Clone("h1_WpT_WmToEN_MC_NormToRD");
  //cout<<"Number h1_WpT_WpToMN_MC: "<<h1_WpT_WpToMN_MC_NormToRD->Integral()<<endl;
  h1_WpT_WpToMN_MC_NormToRD->Scale(h1_WpT_WpToMN_ratio->Integral()/h1_WpT_WpToMN_MC_NormToRD->Integral());
  h1_WpT_WmToMN_MC_NormToRD->Scale(h1_WpT_WmToMN_ratio->Integral()/h1_WpT_WmToMN_MC_NormToRD->Integral());
  h1_WpT_WpToEN_MC_NormToRD->Scale(h1_WpT_WpToEN_ratio->Integral()/h1_WpT_WpToEN_MC_NormToRD->Integral());
  h1_WpT_WmToEN_MC_NormToRD->Scale(h1_WpT_WmToEN_ratio->Integral()/h1_WpT_WmToEN_MC_NormToRD->Integral());
  //cout<<"Number h1_WpT_WpToMN_MC_NormToRD: "<<h1_WpT_WpToMN_MC_NormToRD->Integral()<<endl;
  h1_WpT_WpToMN_ratio->Divide(h1_WpT_WpToMN_MC_NormToRD);
  h1_WpT_WmToMN_ratio->Divide(h1_WpT_WmToMN_MC_NormToRD);
  h1_WpT_WpToEN_ratio->Divide(h1_WpT_WpToEN_MC_NormToRD);
  h1_WpT_WmToEN_ratio->Divide(h1_WpT_WmToEN_MC_NormToRD);

  sprintf(tmpName,"WpT_WpMN");
  pltWpMN= new CPlot(tmpName,"",tmpName,"events/bin");
  sprintf(tmpName,"WpT_WmMN");
  pltWmMN= new CPlot(tmpName,"",tmpName,"events/bin");
  sprintf(tmpName,"WpT_WpEN");
  pltWpEN= new CPlot(tmpName,"",tmpName,"events/bin");
  sprintf(tmpName,"WpT_WmEN");
  pltWmEN= new CPlot(tmpName,"",tmpName,"events/bin");
  //h1_WpT_WpToMN_MC->SetFillColor(2);
  //h1_WpT_WpToMN_MC->SetMarkerStyle(2);
  //h1_WpT_WpToMN_MC->SetMarkerSize(2);
  //h1_WpT_WpToMN_MC->SetMarkerColor(0);
  //h1_WpT_WpToMN_MC->Draw("h");
  pltWpMN->setOutDir(resultDir);
  pltWmMN->setOutDir(resultDir);
  pltWpEN->setOutDir(resultDir);
  pltWmEN->setOutDir(resultDir);
  //           // hist, drawopt, color, linesty, fillsty, mkerSty, mkerSize
  pltWpMN->AddHist1D(h1_WpT_WpToMN_MC,"H",3,1,1001,2,0);
  pltWmMN->AddHist1D(h1_WpT_WmToMN_MC,"H",3,1,1001,2,0);
  pltWpMN->AddHist1D(h1_WpT_WpToMN_RD,"E",1,1,0,21,1);
  pltWmMN->AddHist1D(h1_WpT_WmToMN_RD,"E",1,1,0,21,1);

  pltWpEN->AddHist1D(h1_WpT_WpToEN_MC,"H",3,1,1001,2,0);
  pltWmEN->AddHist1D(h1_WpT_WmToEN_MC,"H",3,1,1001,2,0);
  pltWpEN->AddHist1D(h1_WpT_WpToEN_RD,"E",1,1,0,21,1);
  pltWmEN->AddHist1D(h1_WpT_WmToEN_RD,"E",1,1,0,21,1);

  pltWpMN->SetLegend(0.23,0.7,0.4,0.8);
  pltWmMN->SetLegend(0.23,0.7,0.4,0.8);
  pltWpEN->SetLegend(0.23,0.7,0.4,0.8);
  pltWmEN->SetLegend(0.23,0.7,0.4,0.8);

  pltWpMN->GetLegend()->SetTextSize(0.03);
  pltWmMN->GetLegend()->SetTextSize(0.03);
  pltWpEN->GetLegend()->SetTextSize(0.03);
  pltWmEN->GetLegend()->SetTextSize(0.03);

  pltWpMN->GetLegend()->AddEntry(h1_WpT_WpToMN_MC,"WpToMN_MC");
  pltWmMN->GetLegend()->AddEntry(h1_WpT_WmToMN_MC,"WmToMN_MC");
  pltWpMN->GetLegend()->AddEntry(h1_WpT_WpToMN_RD,"WpToMN_RD");
  pltWmMN->GetLegend()->AddEntry(h1_WpT_WmToMN_RD,"WmToMN_RD");

  pltWpEN->GetLegend()->AddEntry(h1_WpT_WpToEN_MC,"WpToEN_MC");
  pltWmEN->GetLegend()->AddEntry(h1_WpT_WmToEN_MC,"WmToEN_MC");
  pltWpEN->GetLegend()->AddEntry(h1_WpT_WpToEN_RD,"WpToEN_RD");
  pltWmEN->GetLegend()->AddEntry(h1_WpT_WmToEN_RD,"WmToEN_RD");

  pltWpMN->Draw(myCan,kTRUE,format);
  pltWmMN->Draw(myCan,kTRUE,format);
  pltWpEN->Draw(myCan,kTRUE,format);
  pltWmEN->Draw(myCan,kTRUE,format);

  sprintf(tmpName,"WpT_WpMN_ratio");
  pltWpMN_ratio= new CPlot(tmpName,"",tmpName,"ratio/bin");
  sprintf(tmpName,"WpT_WmMN_ratio");
  pltWmMN_ratio= new CPlot(tmpName,"",tmpName,"ratio/bin");

  sprintf(tmpName,"WpT_WpEN_ratio");
  pltWpEN_ratio= new CPlot(tmpName,"",tmpName,"ratio/bin");
  sprintf(tmpName,"WpT_WmEN_ratio");
  pltWmEN_ratio= new CPlot(tmpName,"",tmpName,"ratio/bin");

  pltWpMN_ratio->setOutDir(resultDir);
  pltWmMN_ratio->setOutDir(resultDir);
  pltWpEN_ratio->setOutDir(resultDir);
  pltWmEN_ratio->setOutDir(resultDir);

  pltWpMN_ratio->AddHist1D(h1_WpT_WpToMN_ratio,"E",1,1,1001,21,1);
  pltWmMN_ratio->AddHist1D(h1_WpT_WmToMN_ratio,"E",1,1,1001,21,1);
  pltWpEN_ratio->AddHist1D(h1_WpT_WpToEN_ratio,"E",1,1,1001,21,1);
  pltWmEN_ratio->AddHist1D(h1_WpT_WmToEN_ratio,"E",1,1,1001,21,1);

  pltWpMN_ratio->SetLegend(0.7,0.8,0.9,0.9);
  pltWmMN_ratio->SetLegend(0.7,0.8,0.9,0.9);
  pltWpEN_ratio->SetLegend(0.7,0.8,0.9,0.9);
  pltWmEN_ratio->SetLegend(0.7,0.8,0.9,0.9);

  pltWpMN_ratio->GetLegend()->SetTextSize(0.03);
  pltWmMN_ratio->GetLegend()->SetTextSize(0.03);
  pltWpEN_ratio->GetLegend()->SetTextSize(0.03);
  pltWmEN_ratio->GetLegend()->SetTextSize(0.03);

  pltWpMN_ratio->GetLegend()->AddEntry(h1_WpT_WpToMN_ratio,"WpToMN data/MC");
  pltWmMN_ratio->GetLegend()->AddEntry(h1_WpT_WmToMN_ratio,"WmToMN data/MC");
  pltWpEN_ratio->GetLegend()->AddEntry(h1_WpT_WpToEN_ratio,"WpToEN data/MC");
  pltWmEN_ratio->GetLegend()->AddEntry(h1_WpT_WmToEN_ratio,"WmToEN data/MC");

  pltWpMN_ratio->Draw(myCan,kTRUE,format);
  pltWmMN_ratio->Draw(myCan,kTRUE,format);
  pltWpEN_ratio->Draw(myCan,kTRUE,format);
  pltWmEN_ratio->Draw(myCan,kTRUE,format);

  TFile *RootOut= new TFile("../RstSelection/WpT_Data_MC_ratio.root","recreate");
  h1_WpT_WpToMN_ratio->Write();
  h1_WpT_WmToMN_ratio->Write();
  h1_WpT_WpToEN_ratio->Write();
  h1_WpT_WmToEN_ratio->Write();
  RootOut->Close();
  
  Fout.close();
  myCan->Clear();

  return 0;
}
