void MetFitCompRecoil(const TString Channel)
{
  //Input root files
  if (Channel == "Mu"){
    TFile* f_Before = new TFile("MuonFitResultsRayleighGausSimultBeforeRC/MET_BeforeRC.root");
    TFile* f_After  = new TFile("MuonFitResultsRayleighGausSimultNominal/MET_Nominal.root");
  }else if (Channel == "Ele"){
    TFile* f_Before = new TFile("ElectronFitResultsRayleighGausSimultBeforeRC/MET_BeforeRC.root");
    TFile* f_After  = new TFile("ElectronFitResultsRayleighGausSimultNominal/MET_Nominal.root");
  }

  TLegend* W_ptLgd = new TLegend(.7, .7,.9,.9);
  THStack* hs_B = new THStack("hs_B","");
  THStack* hs_A = new THStack("hs_A","");
  TH1D* b1;
  TH1D* b2;
  TH1D* b3;
  TH1D* bdata;
  TH1D* a1;
  TH1D* a2;
  TH1D* a3;
  TH1D* adata;

  b1 = (TH1D*)f_Before->Get("hQCD0__pfmet")->Clone("b1");
  b2 = (TH1D*)f_Before->Get("hEWK0__pfmet")->Clone("b2");
  b3 = (TH1D*)f_Before->Get("hWmunu0__pfmet")->Clone("b3");
  bdata = (TH1D*)f_Before->Get("hDataMet_0")->Clone("bdata");

  a1 = (TH1D*)f_After->Get("hQCD0__pfmet")->Clone("a1");
  a2 = (TH1D*)f_After->Get("hEWK0__pfmet")->Clone("a2");
  a3 = (TH1D*)f_After->Get("hWmunu0__pfmet")->Clone("a3");
  adata = (TH1D*)f_After->Get("hDataMet_0")->Clone("adata");

//Stack histograms before Recoil Corr
  b1->SetLineColor(kSpring);
  hs_B->Add(b1);

  b2->SetLineColor(kOrange);
  hs_B->Add(b2);

  b3->SetLineColor(kAzure);
  hs_B->Add(b3);

//Stack histograms after Recoil Corr
  a1->SetLineColor(kTeal);
  hs_A->Add(a1);

  a2->SetLineColor(kViolet);
  hs_A->Add(a2);

  a3->SetLineColor(kPink);
  hs_A->Add(a3);

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
  if (Channel == "Mu"){
    W_ptLgd->AddEntry(b3,"W#rightarrow#mu#nu Be_RC","l");
    W_ptLgd->AddEntry(a3,"W#rightarrow#mu#nu Af_RC","l");
  }else if (Channel == "Ele"){
    W_ptLgd->AddEntry(b3,"W#rightarrow e#nu Be_RC","l");
    W_ptLgd->AddEntry(a3,"W#rightarrow e#nu Af_RC","l");
  }
  W_ptLgd->AddEntry(b2,"EWK+t#bar{t} Be_RC","l");
  W_ptLgd->AddEntry(a2,"EWK+t#bar{t} Af_RC","l");
  W_ptLgd->AddEntry(b1,"QCD Be_RC","l");
  W_ptLgd->AddEntry(a1,"QCD Af_RC","l");

  W_ptLgd->SetFillStyle(0);
  W_ptLgd->Draw();
  gPad->RedrawAxis();
  
  myCan->SaveAs(Channel+"_MET_Comp_Bin0.png");
  myCan->SetLogy();
  myCan->SaveAs(Channel+"_MET_Comp_Bin0_Log.png");
}
