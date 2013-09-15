#include "../Utils/const.h"
void WptFitCompRecoil(const TString Channel)
{
  //Input root files
  if (Channel == "Mu"){
  TFile* f_Before = new TFile("MuonFitResultsConvSimultBeforeRC/Wpt_BeforeRC.root");
  TFile* f_After  = new TFile("MuonFitResultsConvSimultNominal/Wpt_AfterRC.root");
  }else if (Channel == "Ele"){
  TFile* f_Before = new TFile("ElectronFitResultsConvSimultBeforeRC/Wpt_BeforeRC.root");
  TFile* f_After  = new TFile("ElectronFitResultsConvSimultNominal/Wpt_AfterRC.root");
  }

  TLegend* W_ptLgd = new TLegend(.65, .65,.9,.9);

  THStack* hs_B = new THStack("hs_B","");
  THStack* hs_A = new THStack("hs_A","");
  TH1D* b1;
  TH1D* b2;
  TH1D* b3;
  TH1D* b4;
  TH1D* b5;
  TH1D* b6;
  TH1D* bdata;
  TH1D* a1;
  TH1D* a2;
  TH1D* a3;
  TH1D* a4;
  TH1D* a5;
  TH1D* a6;
  TH1D* adata;

  b1 = (TH1D*)f_Before->Get("hDYToTauTau")->Clone("b1");
  b2 = (TH1D*)f_Before->Get("hTTJets")->Clone("b2");
  b3 = (TH1D*)f_Before->Get("hWToTauTau")->Clone("b3");
  if (Channel == "Mu")
  b4 = (TH1D*)f_Before->Get("hDYToMuMu")->Clone("b4");
  else if (Channel == "Ele")
  b4 = (TH1D*)f_Before->Get("hDYToEE")->Clone("b4");
  b5 = (TH1D*)f_Before->Get("hQCDWpt")->Clone("b5");
  b6 = (TH1D*)f_Before->Get("hSigWpt")->Clone("b6");
  bdata = (TH1D*)f_Before->Get("hdataWpt")->Clone("bdata");

  a1 = (TH1D*)f_After->Get("hDYToTauTau")->Clone("a1");
  a2 = (TH1D*)f_After->Get("hTTJets")->Clone("a2");
  a3 = (TH1D*)f_After->Get("hWToTauTau")->Clone("a3");
  a4 = (TH1D*)f_After->Get("hDYToMuMu")->Clone("a4");
  a5 = (TH1D*)f_After->Get("hQCDWpt")->Clone("a5");
  a6 = (TH1D*)f_After->Get("hSigWpt")->Clone("a6");
  adata = (TH1D*)f_Before->Get("hdataWpt")->Clone("adata");

//Stack histograms before Recoil Corr
  b1->SetLineColor(kSpring);
  hs_B->Add(b1);
  W_ptLgd->AddEntry(b1,"Z/#gamma^{*}#rightarrow#tau#tau Be_RC","l");

  b2->SetLineColor(kAzure-3);
  hs_B->Add(b2);
  W_ptLgd->AddEntry(b2,"t#bar t Be_RC","l");

  b3->SetLineColor(kCyan);
  hs_B->Add(b3);
  W_ptLgd->AddEntry(b3,"W#rightarrow#tau#nu Be_RC","l");

  b4->SetLineColor(kOrange);
  hs_B->Add(b4);
  if (Channel == "Mu")
  W_ptLgd->AddEntry(b4,"Z/#gamma^{*}#rightarrow#mu#mu Be_RC","l");
  else if (Channel == "Ele")
  W_ptLgd->AddEntry(b4,"Z/#gamma^{*}#rightarrow ee Be_RC","l");

  b5->SetLineColor(kViolet);
  hs_B->Add(b5);
  W_ptLgd->AddEntry(b5,"QCD Be_RC","l");

  b6->SetLineColor(kPink-9);
  hs_B->Add(b6);
  if (Channel == "Mu")
  W_ptLgd->AddEntry(b6,"W#rightarrow#mu#nu Be_RC","l");
  else if (Channel == "Ele")
  W_ptLgd->AddEntry(b6,"W#rightarrow e#nu Be_RC","l");

//Stack histograms after Recoil Corr
  a1->SetLineColor(kSpring-6);
  hs_A->Add(a1);
  W_ptLgd->AddEntry(a1,"Z/#gamma^{*}#rightarrow#tau#tau Af_RC","l");

  a2->SetLineColor(kAzure);
  hs_A->Add(a2);
  W_ptLgd->AddEntry(a2,"t#bar t Af_RC","l");

  a3->SetLineColor(kCyan-6);
  hs_A->Add(a3);
  W_ptLgd->AddEntry(a3,"W#rightarrow#tau#nu Af_RC","l");

  a4->SetLineColor(kOrange-6);
  hs_A->Add(a4);
  if (Channel == "Mu")
  W_ptLgd->AddEntry(a4,"Z/#gamma^{*}#rightarrow#mu#mu Af_RC","l");
  else if (Channel == "Ele")
  W_ptLgd->AddEntry(a4,"Z/#gamma^{*}#rightarrow ee Af_RC","l");

  a5->SetLineColor(kViolet-6);
  hs_A->Add(a5);
  W_ptLgd->AddEntry(a5,"QCD Af_RC","l");

  a6->SetLineColor(kPink+3);
  hs_A->Add(a6);
  if (Channel == "Mu")
  W_ptLgd->AddEntry(a6,"W#rightarrow#mu#nu Af_RC","l");
  else if (Channel == "Ele")
  W_ptLgd->AddEntry(a6,"W#rightarrow e#nu Af_RC","l");

// Set y range
  float Amax = hs_A->GetMaximum();
  float Bmax = hs_B->GetMaximum();
  
  float yaxismax = TMath::Max(Amax, Bmax);
  
  hs_A->SetMaximum(1.1*yaxismax);
  hs_A->SetMinimum(5e-6*yaxismax);
  hs_B->SetMaximum(1.1*yaxismax);
  hs_B->SetMinimum(5e-6*yaxismax);

  TCanvas *myCan=new TCanvas("myCan","myCan",1000,800);
  gStyle->SetLineWidth(2.);
  gStyle->SetLabelSize(0.04,"xy");
  gStyle->SetTitleSize(0.05,"xy");
  gStyle->SetTitleOffset(1.1,"x");
  gStyle->SetTitleOffset(1.2,"y");
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadRightMargin(0.1);
  gStyle->SetPadBottomMargin(0.16);
  gStyle->SetPadLeftMargin(0.12);

  hs_B->Draw();
  hs_A->Draw("same");

  bdata->SetMarkerColor(kGray);
  bdata->SetLineColor(kGray);
  bdata->SetMarkerStyle(kFullCircle);
  bdata->SetMarkerSize(0.9);
  bdata->Draw("esame");

  adata->SetMarkerStyle(kFullCircle);
  adata->SetMarkerSize(0.9);
  adata->Draw("esame");

  W_ptLgd->AddEntry(bdata,"Data Be_RC","pl");
  W_ptLgd->AddEntry(adata,"Data Af_RC","pl");

  W_ptLgd->SetFillStyle(0);
  W_ptLgd->Draw();
  if (Channel == "Mu")
  myCan->SaveAs("Muon_Wpt_Comp.png");
  else if (Channel == "Ele")
  myCan->SaveAs("Electron_Wpt_Comp.png");
  myCan->SetLogy();
  myCan->Draw();
  if (Channel == "Mu")
  myCan->SaveAs("Muon_Wpt_Comp_Log.png");
  else if (Channel == "Ele")
  myCan->SaveAs("Electron_Wpt_Comp_Log.png");
}
