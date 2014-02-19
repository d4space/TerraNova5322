
#include "TStyle.h"
#include "../Utils/const.h"
#include "../Utils/CPlot.hh"
#include "../Utils/MitStyleRemix.hh"
#include "../Utils/Unfolder.h"
//#include <iostream>
#include <fstream>
#include <iostream>
#include <iomanip>

//From TSVDUnfoldExample.C

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

#if not defined(__CINT__) || defined(__MAKECINT__)
#endif

int wAcceptStudy(TString InFile, TString BaseName)
{
  double Bins[NWptBinPlus];
   // Final Bins7
   Bins[0]=     0.;
   Bins[1]=     7.5;
   Bins[2]=     12.5;
   Bins[3]=     17.5;
   Bins[4]=     24.;
   Bins[5]=     30.;
   Bins[6]=    40.;
   Bins[7]=    50.;
   Bins[8]=    70.;
   Bins[9]=    110.;
   Bins[10]=    150.;
   Bins[11]=    190.;
   Bins[12]=    250.;
   Bins[13]=    600.;

  cout<<"Processing "<<BaseName<<endl;
  TString resultDir = BaseName;
  char tmpName[30];

  //TStyle *myStyle=new TStyle("myStyle","myStyle");
  //myStyle->SetPalette(1);
  //
  //gStyle->SetPalette(1);
  //gStyle->SetTitleOffset(0.5,"X");
  //gStyle->SetTitleSize(0.02,"X");
  CPlot *plotWpt;
  CPlot *plotAcc;
  CPlot *plotPostBorn;
  CPlot *plotPostBorn_noNorm;
  CPlot *plotPostBorn_Inv;

  TFile *f_Acct = new TFile(InFile);

  // Histo's
  TH1D *h1_Born_WpT_AP; //All Phase
  TH1D *h1_Born_WpT_BornFid; //Fiducial
  TH1D *h1_Born_WpT_PostFid; //Fiducial
  TH1D *h1_Post_WpT_PostFid;
  TH1D *h1_Born_WpT_PostFid_Even;
  TH1D *h1_Post_WpT_PostFid_Even;
  TH1D *h1_Post_WpT_PostFid_Even_Unfold;
  TH2D *h2_PostBorn_PostFid;

  TH1D *h1_Acceptance;

  TH2D *h2_PostBorn_PostFid_Inv;

  CPlot *plotBorn_pWpT;
  TCanvas *myCan = MakeCanvas("myCan","myCan",900,800);
  char legendName[30];

  //================
  // Take histogramsB
  //================
  if(BaseName == "ResultWpToMuNu")
  {
  sprintf(tmpName,"h1_Born_pWpT_MuNu_AP");
  h1_Born_WpT_AP = (TH1D*)f_Acct->Get(tmpName)->Clone(tmpName);
  h1_Born_WpT_AP->Sumw2();
  sprintf(tmpName,"h1_Born_pWpT_MuNu_BornFid");
  h1_Born_WpT_BornFid = (TH1D*)f_Acct->Get(tmpName)->Clone(tmpName);
  h1_Born_WpT_BornFid->Sumw2();
  sprintf(tmpName,"h1_Born_pWpT_MuNu_PostFid");
  h1_Born_WpT_PostFid = (TH1D*)f_Acct->Get(tmpName)->Clone(tmpName);
  h1_Born_WpT_PostFid->Sumw2();
  sprintf(tmpName,"h1_Post_pWpT_MuNu_PostFid");
  h1_Post_WpT_PostFid = (TH1D*)f_Acct->Get(tmpName)->Clone(tmpName);
  h1_Post_WpT_PostFid->Sumw2();
  sprintf(tmpName,"h1_Born_pWpT_MuNu_PostFid_Even");
  h1_Born_WpT_PostFid_Even=(TH1D*)f_Acct->Get(tmpName)->Clone(tmpName);
  h1_Born_WpT_PostFid_Even->Sumw2();
  sprintf(tmpName,"h1_Post_pWpT_MuNu_PostFid_Even");
  h1_Post_WpT_PostFid_Even=(TH1D*)f_Acct->Get(tmpName)->Clone(tmpName);
  h1_Post_WpT_PostFid_Even->Sumw2();
  sprintf(tmpName,"h2_PostBorn_pWpT_MuNu_PostFid");
  h2_PostBorn_PostFid = (TH2D*)f_Acct->Get(tmpName)->Clone(tmpName);
  h2_PostBorn_PostFid->Sumw2();
  }
  if(BaseName == "ResultWmToMuNu")
  {
  sprintf(tmpName,"h1_Born_mWpT_MuNu_AP");
  h1_Born_WpT_AP = (TH1D*)f_Acct->Get(tmpName)->Clone(tmpName);
  h1_Born_WpT_AP->Sumw2();
  sprintf(tmpName,"h1_Born_mWpT_MuNu_BornFid");
  h1_Born_WpT_BornFid = (TH1D*)f_Acct->Get(tmpName)->Clone(tmpName);
  h1_Born_WpT_BornFid->Sumw2();
  sprintf(tmpName,"h1_Born_mWpT_MuNu_PostFid");
  h1_Born_WpT_PostFid = (TH1D*)f_Acct->Get(tmpName)->Clone(tmpName);
  h1_Born_WpT_PostFid->Sumw2();
  sprintf(tmpName,"h1_Post_mWpT_MuNu_PostFid");
  h1_Post_WpT_PostFid = (TH1D*)f_Acct->Get(tmpName)->Clone(tmpName);
  h1_Post_WpT_PostFid->Sumw2();
  sprintf(tmpName,"h1_Born_mWpT_MuNu_PostFid_Even");
  h1_Born_WpT_PostFid_Even=(TH1D*)f_Acct->Get(tmpName)->Clone(tmpName);
  h1_Born_WpT_PostFid_Even->Sumw2();
  sprintf(tmpName,"h1_Post_mWpT_MuNu_PostFid_Even");
  h1_Post_WpT_PostFid_Even=(TH1D*)f_Acct->Get(tmpName)->Clone(tmpName);
  h1_Post_WpT_PostFid_Even->Sumw2();
  sprintf(tmpName,"h2_PostBorn_mWpT_MuNu_PostFid");
  h2_PostBorn_PostFid = (TH2D*)f_Acct->Get(tmpName)->Clone(tmpName);
  h2_PostBorn_PostFid->Sumw2();
  }
  if(BaseName == "ResultWpToEleNu")
  {
  sprintf(tmpName,"h1_Born_pWpT_EleNu_AP");
  h1_Born_WpT_AP = (TH1D*)f_Acct->Get(tmpName)->Clone(tmpName);
  h1_Born_WpT_AP->Sumw2();
  sprintf(tmpName,"h1_Born_pWpT_EleNu_BornFid");
  h1_Born_WpT_BornFid = (TH1D*)f_Acct->Get(tmpName)->Clone(tmpName);
  h1_Born_WpT_BornFid->Sumw2();
  sprintf(tmpName,"h1_Born_pWpT_EleNu_PostFid");
  h1_Born_WpT_PostFid = (TH1D*)f_Acct->Get(tmpName)->Clone(tmpName);
  h1_Born_WpT_PostFid->Sumw2();
  sprintf(tmpName,"h1_Post_pWpT_EleNu_PostFid");
  h1_Post_WpT_PostFid = (TH1D*)f_Acct->Get(tmpName)->Clone(tmpName);
  h1_Post_WpT_PostFid->Sumw2();
  sprintf(tmpName,"h1_Born_pWpT_EleNu_PostFid_Even");
  h1_Born_WpT_PostFid_Even=(TH1D*)f_Acct->Get(tmpName)->Clone(tmpName);
  h1_Born_WpT_PostFid_Even->Sumw2();
  sprintf(tmpName,"h1_Post_pWpT_EleNu_PostFid_Even");
  h1_Post_WpT_PostFid_Even=(TH1D*)f_Acct->Get(tmpName)->Clone(tmpName);
  h1_Post_WpT_PostFid_Even->Sumw2();
  sprintf(tmpName,"h2_PostBorn_pWpT_EleNu_PostFid");
  h2_PostBorn_PostFid = (TH2D*)f_Acct->Get(tmpName)->Clone(tmpName);
  h2_PostBorn_PostFid->Sumw2();
  }
  if(BaseName == "ResultWmToEleNu")
  {
  sprintf(tmpName,"h1_Born_mWpT_EleNu_AP");
  h1_Born_WpT_AP = (TH1D*)f_Acct->Get(tmpName)->Clone(tmpName);
  h1_Born_WpT_AP->Sumw2();
  sprintf(tmpName,"h1_Born_mWpT_EleNu_BornFid");
  h1_Born_WpT_BornFid = (TH1D*)f_Acct->Get(tmpName)->Clone(tmpName);
  h1_Born_WpT_BornFid->Sumw2();
  sprintf(tmpName,"h1_Born_mWpT_EleNu_PostFid");
  h1_Born_WpT_PostFid = (TH1D*)f_Acct->Get(tmpName)->Clone(tmpName);
  h1_Born_WpT_PostFid->Sumw2();
  sprintf(tmpName,"h1_Post_mWpT_EleNu_PostFid");
  h1_Post_WpT_PostFid = (TH1D*)f_Acct->Get(tmpName)->Clone(tmpName);
  h1_Post_WpT_PostFid->Sumw2();
  sprintf(tmpName,"h1_Born_mWpT_EleNu_PostFid_Even");
  h1_Born_WpT_PostFid_Even=(TH1D*)f_Acct->Get(tmpName)->Clone(tmpName);
  h1_Born_WpT_PostFid_Even->Sumw2();
  sprintf(tmpName,"h1_Post_mWpT_EleNu_PostFid_Even");
  h1_Post_WpT_PostFid_Even=(TH1D*)f_Acct->Get(tmpName)->Clone(tmpName);
  h1_Post_WpT_PostFid_Even->Sumw2();
  sprintf(tmpName,"h2_PostBorn_mWpT_EleNu_PostFid");
  h2_PostBorn_PostFid = (TH2D*)f_Acct->Get(tmpName)->Clone(tmpName);
  h2_PostBorn_PostFid->Sumw2();
  }

  // Histogram Font and so on
  h2_PostBorn_PostFid->GetXaxis()->SetTitleSize(0.04);
  h2_PostBorn_PostFid->GetXaxis()->SetTitleOffset(1);
  h2_PostBorn_PostFid->GetXaxis()->SetLabelSize(0.03);
  h2_PostBorn_PostFid->GetXaxis()->SetLabelOffset(0.01);

  h2_PostBorn_PostFid->GetYaxis()->SetTitleSize(0.04);
  h2_PostBorn_PostFid->GetYaxis()->SetTitleOffset(1.);
  h2_PostBorn_PostFid->GetYaxis()->SetLabelSize(0.03);
  h2_PostBorn_PostFid->GetYaxis()->SetLabelOffset(0.01);
                 // Out file
  plotWpt=new CPlot("Born_WpT","","WpT [GeV]","Events");
  plotWpt->SetLogx(1);
  plotWpt->setOutDir(resultDir);
  plotWpt->AddHist1D(h1_Born_WpT_AP,"",kBlue,1,0,20,1.7);
  plotWpt->AddHist1D(h1_Born_WpT_BornFid,"",kRed,1,0,24,1.7);
  plotWpt->SetLegend(0.68,0.57,0.93,0.8);
  plotWpt->GetLegend()->AddEntry(h1_Born_WpT_AP, "All Phase","lp");
  plotWpt->GetLegend()->AddEntry(h1_Born_WpT_BornFid,"Fiducial","lp");
  plotWpt->Draw(myCan,kTRUE,"png");

  // Acceptance Calculation
  h1_Acceptance = (TH1D*)h1_Born_WpT_BornFid->Clone("Acceptance");
  h1_Acceptance->Sumw2();
  h1_Acceptance->Divide(h1_Born_WpT_AP);
  plotAcc=new CPlot("Acceptance","","WpT [GeV]","Acceptance");
  plotAcc->SetLogx(0);
  plotAcc->setOutDir(resultDir);
  plotAcc->AddHist1D(h1_Acceptance,"",kBlack,1,0,20,1.7);
  //plotAcc->SetLegend(0.68,0.57,0.93,0.8);
  //plotAcc->GetLegend()->AddEntry(h1_Acceptance, "Acceptance","lp");
  plotAcc->Draw(myCan,kTRUE,"png");

  //============================
  // Unfolding from Post to Born
  //============================
  // Plot un-normalized histo
  plotPostBorn_noNorm=new CPlot("PostBorn_noNorm","","Post WpT [GeV]","Born WpT [GeV]");
  plotPostBorn_noNorm->setOutDir(resultDir);
  plotPostBorn_noNorm->AddHist2D(h2_PostBorn_PostFid,"COLZ",kWhite,kBlack);
  plotPostBorn_noNorm->SetLogx();
  plotPostBorn_noNorm->SetLogy();
  plotPostBorn_noNorm->Draw(myCan,kTRUE,"png");

  // Unfolder constructor
  Unfolder unfoldPostBorn("PostBorn");
  unfoldPostBorn.setTrue(h1_Born_WpT_PostFid);
  unfoldPostBorn.setMeas(h1_Post_WpT_PostFid_Even);
  unfoldPostBorn.colNormalize(h2_PostBorn_PostFid);
  // Plot normalized histo
  plotPostBorn=new CPlot("PostBorn","","Post WpT [GeV]","Born WpT [GeV]");
  plotPostBorn->setOutDir(resultDir);
  plotPostBorn->AddHist2D(h2_PostBorn_PostFid,"COLZ",kWhite,kBlack);
  plotPostBorn->SetLogx();
  plotPostBorn->SetLogy();
  plotPostBorn->Draw(myCan,kTRUE,"png");
  // Unfolding
  unfoldPostBorn.setMigrationMatrix(h2_PostBorn_PostFid);
  unfoldPostBorn.unfold();
  // Plot Inv Histogram
  h2_PostBorn_PostFid_Inv = unfoldPostBorn.getMigHistInverse();
  plotPostBorn_Inv=new CPlot("PostBornInv","","Born WpT [GeV]","Post WpT [GeV]");
  plotPostBorn_Inv->setOutDir(resultDir);
  plotPostBorn_Inv->AddHist2D(h2_PostBorn_PostFid_Inv,"COLZ",kWhite,kBlack);
  plotPostBorn_Inv->SetLogx();
  plotPostBorn_Inv->SetLogy();
  plotPostBorn_Inv->Draw(myCan,kTRUE,"png");
  // Plot Unfolded
  h1_Post_WpT_PostFid_Even_Unfold = (TH1D*)unfoldPostBorn.getUnfolded()->Clone("h1_Post_WpT_PostFid_Even_Unfold");
  
  
  return 0;
}
