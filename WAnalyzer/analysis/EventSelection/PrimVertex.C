#include <iostream>
#include <TH1D.h>
#include <TMath.h>
#include "../Utils/CPlot.hh"
#include "../Utils/MitStyleRemix.hh"

TH1D* makeDiffHistWpt(TH1D* hData, TH1D* hMC, const TString name);

void PrimVertex()
{
  cout << "Primary Vertex" <<endl;
  CPlot::sOutDir = "test";

  TH1D* DYToMuMu_Vtx;
  TH1D* DYToTauTau_Vtx;
  TH1D* WToTauNu_Vtx;
  TH1D* TTJets_Vtx;
//  TH1D* WpToMuNu_Vtx;
//  TH1D* WmToMuNu_Vtx;
  TH1D* RD_Vtx;
  TH1D* MC_Vtx;
  TH1D* EWK;
  TH1D* hWptDiff;

//  TCanvas *myCan = MakeCanvas("myCan","myCan",900,800);
//  TCanvas *c;
//  c = MakeCanvas("c","c",900,800);

  TCanvas *c;
  c = MakeCanvas("c","c",800,800);
  c->Divide(1,2,0,0);
  c->cd(1)->SetPad(0,0.3,1.0,1.0);
  c->cd(1)->SetTopMargin(0.1);
  c->cd(1)->SetBottomMargin(0.01);
  c->cd(1)->SetLeftMargin(0.15);
  c->cd(1)->SetRightMargin(0.07);
  c->cd(1)->SetTickx(1);
  c->cd(1)->SetTicky(1);
  c->cd(2)->SetPad(0,0,1.0,0.3);
  c->cd(2)->SetTopMargin(0.05);
  c->cd(2)->SetBottomMargin(0.45);
  c->cd(2)->SetLeftMargin(0.15);
  c->cd(2)->SetRightMargin(0.07);
  c->cd(2)->SetTickx(1);
  c->cd(2)->SetTicky(1);
//  gStyle->SetTitleOffset(1.100,"Y");
//  TGaxis::SetMaxDigits(3);


  CPlot* PrimVtx;
  CPlot* plotWptDiff;
//  CPlot::sOutDir = "test";
  TFile *DYToMuMu = new TFile("MuonLowPU/Muon_DYToMuMu_S8_Analysis.root");
  TFile *DYToTauTau = new TFile("MuonLowPU/Muon_DYToTauTau_S8_Analysis.root");
//  TFile *WToTauNu = new TFile("MuonLowPU/Muon_WToTauNu_S8_Analysis.root");
  TFile *TTJets = new TFile("MuonLowPU/Muon_TTJets_S8_Analysis.root");
//  TFile *WpToMuNu = new TFile("MuonLowPU/Muon_WpToMuNu_S8_Analysis.root");
//  TFile *WmToMuNu = new TFile("MuonLowPU/Muon_WmToMuNu_S8_Analysis.root");
  TFile *MuonRD = new TFile("MuonLowPU/Muon_RD_LowPU_Analysis.root");

//  TFile *DYToMuMu = new TFile("MuonLowPU_WZ/Muon_DYToMuMu_S8_Analysis.root");
//  TFile *DYToTauTau = new TFile("MuonLowPU_WZ/Muon_DYToTauTau_S8_Analysis.root");
//  TFile *WToTauNu = new TFile("MuonLowPU_WZ/Muon_WToTauNu_S8_Analysis.root");
//  TFile *TTJets = new TFile("MuonLowPU_WZ/Muon_TTJets_S8_Analysis.root");
//  TFile *WpToMuNu = new TFile("MuonLowPU_WZ/Muon_WpToMuNu_S8_Analysis.root");
//  TFile *WmToMuNu = new TFile("MuonLowPU_WZ/Muon_WmToMuNu_S8_Analysis.root");
//  TFile *MuonRD = new TFile("MuonLowPU_WZ/Muon_RD_LowPU_Analysis.root");

  DYToMuMu_Vtx = (TH1D*)DYToMuMu->Get("h1_Vtx_Prim_MC_Z_NumPrimVtx")->Clone("DYToMuMu_Vtx");
  DYToTauTau_Vtx = (TH1D*)DYToTauTau->Get("h1_Vtx_Prim_MC_Z_NumPrimVtx")->Clone("DYToTauTau_Vtx");
//  WToTauNu_Vtx = (TH1D*)WToTauNu->Get("h1_Vtx_Prim_MC_Z_NumPrimVtx")->Clone("WToTauNu_Vtx");
//  WpToMuNu_Vtx = (TH1D*)WpToMuNu->Get("h1_Vtx_Prim_MC_Z_NumPrimVtx")->Clone("WpToMuNu_Vtx");
//  WmToMuNu_Vtx = (TH1D*)WmToMuNu->Get("h1_Vtx_Prim_MC_Z_NumPrimVtx")->Clone("WmToMuNu_Vtx");
  TTJets_Vtx = (TH1D*)TTJets->Get("h1_Vtx_Prim_MC_Z_NumPrimVtx")->Clone("TTJets_Vtx");

  MC_Vtx = (TH1D*)DYToMuMu_Vtx->Clone("MC_Vtx");
  MC_Vtx->Add(DYToTauTau_Vtx);
//  MC_Vtx->Add(WToTauNu_Vtx);
//  MC_Vtx->Add(WpToMuNu_Vtx);
//  MC_Vtx->Add(WmToMuNu_Vtx);
  MC_Vtx->Add(TTJets_Vtx);
  RD_Vtx = (TH1D*)MuonRD->Get("h1_Vtx_Prim_RD_Z_NumPrimVtx")->Clone("RD_Vtx");

  EWK = (TH1D*)DYToTauTau_Vtx->Clone("EWK");
  EWK -> Add(TTJets_Vtx);

  hWptDiff = makeDiffHistWpt(RD_Vtx,MC_Vtx,"hWptDiff");
  hWptDiff->SetMarkerStyle(kFullCircle);
  hWptDiff->SetMarkerSize(0.9);

  PrimVtx = new CPlot("Vtx","","N_{PV}","Events");
  PrimVtx->setOutDir(CPlot::sOutDir);

  PrimVtx->AddHist1D(RD_Vtx,"Data","E");
  PrimVtx->AddToStack(EWK,"EWK",kRed,kRed+1);
  PrimVtx->AddToStack(DYToMuMu_Vtx,"Z#rightarrow#mu#mu",kYellow,kYellow+1);
//  PrimVtx->AddToStack(TTJets_Vtx,"TTJets",kGreen,kGreen+1);
//  PrimVtx->AddToStack(WmToMuNu_Vtx,"WmToMuNu",kViolet,kViolet+5);
//  PrimVtx->AddToStack(WpToMuNu_Vtx,"WpToMuNu",kCyan,kCyan+2);
//  PrimVtx->AddToStack(WToTauNu_Vtx,"WToTauNu",kBlue,kBlue+1);

  PrimVtx->SetLegend(0.55,0.55,0.9,0.9);
  PrimVtx->Draw(c,kFALSE,"png",1);

  plotWptDiff=new CPlot("NPV","","N_{PV}","#chi");
  plotWptDiff->setOutDir(CPlot::sOutDir);
  plotWptDiff->AddHist1D(hWptDiff,"EX0",kBlue);
  plotWptDiff->SetYRange(-6,6);
  plotWptDiff->AddLine(0, 0,30, 0,kBlack,1);
  plotWptDiff->AddLine(0, 5,30, 5,kBlack,3);
  plotWptDiff->AddLine(0,-5,30,-5,kBlack,3);
  plotWptDiff->Draw(c,kTRUE,"png",2);

//  c -> SaveAs("PrimVtx.png");
}

TH1D *makeDiffHistWpt(TH1D* hData, TH1D* hMC, const TString name)
{
  TH1D *hDiff = new TH1D(name,"",hData->GetNbinsX(),hData->GetXaxis()->GetXmin(),hData->GetXaxis()->GetXmax());
  for(Int_t ibin=1; ibin<=hData->GetNbinsX(); ibin++) {
    Double_t diff = (hData->GetBinContent(ibin)-hMC->GetBinContent(ibin));
    Double_t err = sqrt(hData->GetBinContent(ibin));
    if(err==0) err= sqrt(hMC->GetBinContent(ibin));
    if(err>0) hDiff->SetBinContent(ibin,diff/err);
    else      hDiff->SetBinContent(ibin,0);
    hDiff->SetBinError(ibin,1);
  }
  
  hDiff->GetYaxis()->SetTitleOffset(0.42);
  hDiff->GetYaxis()->SetTitleSize(0.13);
  hDiff->GetYaxis()->SetLabelSize(0.10);
  hDiff->GetYaxis()->SetNdivisions(104);
  hDiff->GetYaxis()->CenterTitle();
  hDiff->GetXaxis()->SetTitleOffset(1.2);
  hDiff->GetXaxis()->SetTitleSize(0.13);
  hDiff->GetXaxis()->SetLabelSize(0.12);
  hDiff->GetXaxis()->CenterTitle();
  return hDiff;
}
