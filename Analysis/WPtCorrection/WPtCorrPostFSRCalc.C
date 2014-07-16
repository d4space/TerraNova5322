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

int WPtCorrPostFSRCalc(const TString BaseName)
{
  TString resultDir = "ResultsPostFSRFactor";
  
  gSystem->mkdir(resultDir,kTRUE);

  char tmpName[30];
  
  double WptLogBins[14] = {1.0,7.5,12.5,17.5,24,30,40,50,70,110,150,190,250,600};
  const TString format("png"); 
  
  ofstream Fout;
  Fout.open(resultDir+"/"+BaseName+"_WpMN.txt");

  TFile *fWpMN_MCNom;
  TFile *fWmMN_MCNom;
  TFile *fWpEN_MCNom;
  TFile *fWmEN_MCNom;
  fWpMN_MCNom = new TFile("../Unfolding/Muon2012LoPU/WpToMuNu_S8_Unfold.root");
  fWmMN_MCNom = new TFile("../Unfolding/Muon2012LoPU/WmToMuNu_S8_Unfold.root");
  fWpEN_MCNom = new TFile("../Unfolding/Electron2012LoPU/WpToEleNu_S8_Unfold.root");
  fWmEN_MCNom = new TFile("../Unfolding/Electron2012LoPU/WmToEleNu_S8_Unfold.root");

  TFile *fWpMN_RDNom;
  TFile *fWmMN_RDNom;
  TFile *fWpEN_RDNom;
  TFile *fWmEN_RDNom;
  fWpMN_RDNom = new TFile("../Unfolding/ResultWpToMuNu/Result_WpToMuNu.root");
  fWmMN_RDNom = new TFile("../Unfolding/ResultWmToMuNu/Result_WmToMuNu.root");
  fWpEN_RDNom = new TFile("../Unfolding/ResultWpToEleNu/Result_WpToEleNu.root");
  fWmEN_RDNom = new TFile("../Unfolding/ResultWmToEleNu/Result_WmToEleNu.root");

  TH1D* h1_WpT_WpToMN_MCNom;
  TH1D* h1_WpT_WpToMN_MC_NormToRD;
  TH1D* h1_WpT_WpToMN_RDNom;
  TH1D* h1_WpT_WpToMN_ratio;
  TH1D* h1_WpT_WpToMN_MCNom_Log;

  TH1D* h1_WpT_WmToMN_MCNom;
  TH1D* h1_WpT_WmToMN_MC_NormToRD;
  TH1D* h1_WpT_WmToMN_RDNom;
  TH1D* h1_WpT_WmToMN_ratio;
  TH1D* h1_WpT_WmToMN_MCNom_Log;

  TH1D* h1_WpT_WpToEN_MCNom;
  TH1D* h1_WpT_WpToEN_MC_NormToRD;
  TH1D* h1_WpT_WpToEN_RDNom;
  TH1D* h1_WpT_WpToEN_ratio;
  TH1D* h1_WpT_WpToEN_MCNom_Log;

  TH1D* h1_WpT_WmToEN_MCNom;
  TH1D* h1_WpT_WmToEN_MC_NormToRD;
  TH1D* h1_WpT_WmToEN_RDNom;
  TH1D* h1_WpT_WmToEN_ratio;
  TH1D* h1_WpT_WmToEN_MCNom_Log;
  
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
cout << "check1" << endl;
  //======================
  // Histo from root
  //======================
  h1_WpT_WpToMN_MCNom = (TH1D*)fWpMN_MCNom->Get("h1_Truth_Post")->Clone("h1_WpT_WpToMN_MCNom");
  h1_WpT_WpToMN_MCNom_Log = new TH1D("h1_WpT_WpToMN_MCNom_Log","h1_WpT_WpToMN_MCNom_Log",13,WptLogBins);
  
  h1_WpT_WmToMN_MCNom = (TH1D*)fWmMN_MCNom->Get("h1_Truth_Post")->Clone("h1_WpT_WmToMN_MCNom");
  h1_WpT_WmToMN_MCNom_Log = new TH1D("h1_WpT_WmToMN_MCNom_Log","h1_WpT_WmToMN_MCNom_Log",13,WptLogBins);
  
  h1_WpT_WpToEN_MCNom = (TH1D*)fWpEN_MCNom->Get("h1_Truth_Post")->Clone("h1_WpT_WpToEN_MCNom");
  h1_WpT_WpToEN_MCNom_Log = new TH1D("h1_WpT_WpToEN_MCNom_Log","h1_WpT_WpToEN_MCNom_Log",13,WptLogBins);
  
  h1_WpT_WmToEN_MCNom = (TH1D*)fWmEN_MCNom->Get("h1_Truth_Post")->Clone("h1_WpT_WmToEN_MCNom");
  h1_WpT_WmToEN_MCNom_Log = new TH1D("h1_WpT_WmToEN_MCNom_Log","h1_WpT_WmToEN_MCNom_Log",13,WptLogBins);
  
  h1_WpT_WpToMN_MCNom->Sumw2();
  h1_WpT_WmToMN_MCNom->Sumw2();
  h1_WpT_WpToEN_MCNom->Sumw2();
  h1_WpT_WmToEN_MCNom->Sumw2();
 
  h1_WpT_WpToMN_MCNom->Scale(18.429*1*7322.0/935446);
  h1_WpT_WmToMN_MCNom->Scale(18.429*1*5181.0/1.97346e6);
  h1_WpT_WpToEN_MCNom->Scale(18.429*1*7322.0/2401905);
  h1_WpT_WmToEN_MCNom->Scale(18.429*1*5181.0/2127666);
 


  h1_WpT_WpToMN_RDNom = (TH1D*)fWpMN_RDNom->Get("DetUnf")->Clone("h1_WpT_WpToMN_RDNom");
  h1_WpT_WmToMN_RDNom= (TH1D*)fWmMN_RDNom->Get("DetUnf")->Clone("h1_WpT_WmToMN_RDNom");
  h1_WpT_WpToEN_RDNom = (TH1D*)fWpEN_RDNom->Get("DetUnf")->Clone("h1_WpT_WpToEN_RDNom");
  h1_WpT_WmToEN_RDNom = (TH1D*)fWmEN_RDNom->Get("DetUnf")->Clone("h1_WpT_WmToEN_RDNom");
  h1_WpT_WpToMN_RDNom->Sumw2();
  h1_WpT_WmToMN_RDNom->Sumw2();
  h1_WpT_WpToEN_RDNom->Sumw2();
  h1_WpT_WmToEN_RDNom->Sumw2();


  h1_WpT_WpToMN_ratio = (TH1D*)h1_WpT_WpToMN_RDNom->Clone("h1_WpT_WpToMN_ratio");
  h1_WpT_WmToMN_ratio = (TH1D*)h1_WpT_WmToMN_RDNom->Clone("h1_WpT_WmToMN_ratio");
  h1_WpT_WpToEN_ratio = (TH1D*)h1_WpT_WpToEN_RDNom->Clone("h1_WpT_WpToEN_ratio");
  h1_WpT_WmToEN_ratio = (TH1D*)h1_WpT_WmToEN_RDNom->Clone("h1_WpT_WmToEN_ratio");
  //cout<<"number h1_WpT_WpToMN_ratio: "<<h1_WpT_WpToMN_ratio->Integral()<<endl;
  h1_WpT_WpToMN_MC_NormToRD = (TH1D*)h1_WpT_WpToMN_MCNom->Clone("h1_WpT_WpToMN_MC_NormToRD");
  h1_WpT_WmToMN_MC_NormToRD = (TH1D*)h1_WpT_WmToMN_MCNom->Clone("h1_WpT_WmToMN_MC_NormToRD");
  h1_WpT_WpToEN_MC_NormToRD = (TH1D*)h1_WpT_WpToEN_MCNom->Clone("h1_WpT_WpToEN_MC_NormToRD");
  h1_WpT_WmToEN_MC_NormToRD = (TH1D*)h1_WpT_WmToEN_MCNom->Clone("h1_WpT_WmToEN_MC_NormToRD");
  //cout<<"Number h1_WpT_WpToMN_MC: "<<h1_WpT_WpToMN_MC_NormToRD->Integral()<<endl;
  h1_WpT_WpToMN_MC_NormToRD->Scale(h1_WpT_WpToMN_ratio->Integral()/h1_WpT_WpToMN_MC_NormToRD->Integral());
  h1_WpT_WmToMN_MC_NormToRD->Scale(h1_WpT_WmToMN_ratio->Integral()/h1_WpT_WmToMN_MC_NormToRD->Integral());
  h1_WpT_WpToEN_MC_NormToRD->Scale(h1_WpT_WpToEN_ratio->Integral()/h1_WpT_WpToEN_MC_NormToRD->Integral());
  h1_WpT_WmToEN_MC_NormToRD->Scale(h1_WpT_WmToEN_ratio->Integral()/h1_WpT_WmToEN_MC_NormToRD->Integral());
  cout<<"Number h1_WpT_WpToMN_MC_NormToRD: "<<h1_WpT_WpToMN_MC_NormToRD->Integral()<<endl;
  h1_WpT_WpToMN_ratio->Divide(h1_WpT_WpToMN_MC_NormToRD);
  h1_WpT_WmToMN_ratio->Divide(h1_WpT_WmToMN_MC_NormToRD);
  h1_WpT_WpToEN_ratio->Divide(h1_WpT_WpToEN_MC_NormToRD);
  h1_WpT_WmToEN_ratio->Divide(h1_WpT_WmToEN_MC_NormToRD);
  
  for(int i(1);i<=13;i++)
  {
    cout<<"Bin "<<i<<" : " <<"Mu+:  "<< h1_WpT_WpToMN_ratio->GetBinContent(i) <<"\t"<<"Mu-:  "<<h1_WpT_WmToMN_ratio->GetBinContent(i)<< endl;
  } 
  for(int i(1);i<=13;i++)
  {
    cout<<"Bin "<<i<<" : "  <<"Ele+:  "<<h1_WpT_WpToEN_ratio->GetBinContent(i)<<"\t"<<"Ele-:  "<<h1_WpT_WmToEN_ratio->GetBinContent(i)<< endl;
  } 




  for(int ipt(1);ipt<=13;ipt++)
  {
    h1_WpT_WpToMN_MCNom_Log->SetBinContent(ipt,h1_WpT_WpToMN_MCNom->GetBinContent(ipt));
    h1_WpT_WmToMN_MCNom_Log->SetBinContent(ipt,h1_WpT_WmToMN_MCNom->GetBinContent(ipt));
    h1_WpT_WpToEN_MCNom_Log->SetBinContent(ipt,h1_WpT_WpToEN_MCNom->GetBinContent(ipt));
    h1_WpT_WmToEN_MCNom_Log->SetBinContent(ipt,h1_WpT_WmToEN_MCNom->GetBinContent(ipt));
  
  }
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
  //pltWpMN->AddHist1D(h1_WpT_WpToMN_MCNom_Log,"hist",kGreen,1,0,0,0);
  //pltWmMN->AddHist1D(h1_WpT_WmToMN_MCNom_Log,"hist",kGreen,1,0,0,0);
  //pltWpMN->AddHist1D(h1_WpT_WpToMN_RDNom,"elp",kBlack,1,0,20,1);
  //pltWmMN->AddHist1D(h1_WpT_WmToMN_RDNom,"elp",kBlack,1,0,20,1);
  pltWpMN->AddHist1D(h1_WpT_WpToMN_MCNom_Log,"H",kGreen,1,1001,2,0);
  pltWmMN->AddHist1D(h1_WpT_WmToMN_MCNom_Log,"H",kGreen,1,1001,2,0);
  pltWpMN->AddHist1D(h1_WpT_WpToMN_RDNom,"elp",kBlack,1,0,21,1);
  pltWmMN->AddHist1D(h1_WpT_WmToMN_RDNom,"elp",kBlack,1,0,21,1);

  pltWpEN->AddHist1D(h1_WpT_WpToEN_MCNom_Log,"H",3,1,1001,2,0);
  pltWmEN->AddHist1D(h1_WpT_WmToEN_MCNom_Log,"H",3,1,1001,2,0);
  pltWpEN->AddHist1D(h1_WpT_WpToEN_RDNom,"E",kBlack,1,0,21,1);
  pltWmEN->AddHist1D(h1_WpT_WmToEN_RDNom,"E",kBlack,1,0,21,1);

  pltWpMN->SetLegend(0.53,0.7,0.7,0.8);
  pltWmMN->SetLegend(0.53,0.7,0.7,0.8);
  pltWpEN->SetLegend(0.53,0.7,0.7,0.8);
  pltWmEN->SetLegend(0.53,0.7,0.7,0.8);
  //cout << "check4" << endl;

  pltWpMN->GetLegend()->SetTextSize(0.03);
  pltWmMN->GetLegend()->SetTextSize(0.03);
  pltWpEN->GetLegend()->SetTextSize(0.03);
  pltWmEN->GetLegend()->SetTextSize(0.03);

  pltWpMN->GetLegend()->AddEntry(h1_WpT_WpToMN_MCNom_Log,"Nominal Truth Post","l");
  pltWmMN->GetLegend()->AddEntry(h1_WpT_WmToMN_MCNom_Log,"Nominal Truth Post","l");
  pltWpMN->GetLegend()->AddEntry(h1_WpT_WpToMN_RDNom,"Nominal PostFSR Data ","p");
  pltWmMN->GetLegend()->AddEntry(h1_WpT_WmToMN_RDNom,"Nominal PostFSR Data ","p");

  pltWpEN->GetLegend()->AddEntry(h1_WpT_WpToEN_MCNom_Log,"Nominal Truth Post","l");
  pltWmEN->GetLegend()->AddEntry(h1_WpT_WmToEN_MCNom_Log,"Nominal Truth Post","l");
  pltWpEN->GetLegend()->AddEntry(h1_WpT_WpToEN_RDNom,"Nominal PostFSR Data","p");
  pltWmEN->GetLegend()->AddEntry(h1_WpT_WmToEN_RDNom,"Nominal PostFSR Data","p");

  pltWpMN->SetLogx();
  pltWmMN->SetLogx();
  pltWpEN->SetLogx();
  pltWmEN->SetLogx();
  
  
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

  pltWpMN_ratio->GetLegend()->AddEntry(h1_WpT_WpToMN_ratio,"WpToMN PostFSR Data/MC TruthPost");
  pltWmMN_ratio->GetLegend()->AddEntry(h1_WpT_WmToMN_ratio,"WmToMN PostFSR Data/MC TruthPost");
  pltWpEN_ratio->GetLegend()->AddEntry(h1_WpT_WpToEN_ratio,"WpToEN PostFSR Data/MC TruthPost");
  pltWmEN_ratio->GetLegend()->AddEntry(h1_WpT_WmToEN_ratio,"WmToEN PostFSR Data/MC TruthPost");

  pltWpMN_ratio->Draw(myCan,kTRUE,format);
  pltWmMN_ratio->Draw(myCan,kTRUE,format);
  pltWpEN_ratio->Draw(myCan,kTRUE,format);
  pltWmEN_ratio->Draw(myCan,kTRUE,format);

  TFile *RootOut= new TFile("../RstSelection/WpT_PostFSRData_MC_ratio.root","recreate");
  h1_WpT_WpToMN_ratio->Write();
  h1_WpT_WmToMN_ratio->Write();
  h1_WpT_WpToEN_ratio->Write();
  h1_WpT_WmToEN_ratio->Write();
  RootOut->Close();
  
  Fout.close();
  myCan->Clear();

  return 0;
}
