#include <TMath.h>
void ratiofitMu()
{
  //Input root files
  TFile* fname = new TFile("RstMuon/SigYields_Nominal.root");

  hRatioIncl  = (TH1F*)fname->Get("hQCD_Sig") ->Clone("hRatioIncl");
  hRatioPlus  = (TH1F*)fname->Get("hQCD_SigPlus")->Clone("hRatioPlus");
  hRatioMinus = (TH1F*)fname->Get("hQCD_SigMinus")->Clone("hRatioMinus");
  
  //haRatioIncl  = (TH1F*)fname->Get("hAntiQCD_Sig") ->Clone("haRatioIncl");
  //haRatioPlus  = (TH1F*)fname->Get("hAntiQCD_SigPlus")->Clone("haRatioPlus");
  //haRatioMinus = (TH1F*)fname->Get("hAntiQCD_SigMinus")->Clone("haRatioMinus");
  
  TCanvas *myCan=new TCanvas("myCan","myCan",800,800);
  gStyle->SetLineWidth(2.);
  gStyle->SetLabelSize(0.04,"xy");
  gStyle->SetTitleSize(0.05,"xy");
  gStyle->SetTitleOffset(1.1,"x");
  gStyle->SetTitleOffset(1.2,"y");
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadRightMargin(0.1);
  gStyle->SetPadBottomMargin(0.16);
  gStyle->SetPadLeftMargin(0.12);

  TF1 *fincl = new TF1("fincl","[0]*TMath::Exp(-x/[1])+[2]",40,190);
  TF1 *fp = new TF1("fp","[0]*TMath::Exp(-x/[1])+[2]",40,190);
  TF1 *fm = new TF1("fm","[0]*TMath::Exp(-x/[1])+[2]",40,110);
  
  TF1 *afincl = new TF1("afincl","[0]*TMath::Exp(-x/[1])+[2]",40,110);
  TF1 *afp = new TF1("afp","[0]*TMath::Exp(-x/[1])+[2]",40,110);
  TF1 *afm = new TF1("afm","[0]*TMath::Exp(-x/[1])+[2]",40,110);

  fincl->SetParameter(0,10); fincl->SetParameter(1,16); fincl->SetParameter(2,0.1);
  fincl->SetLineColor(kBlue);

  fp->SetParameter(0,10); fp->SetParameter(1,16); fp->SetParameter(2,0.003);
  fp->SetLineColor(kBlue);
  
  fm->SetParameter(0,10); fm->SetParameter(1,16); fm->SetParameter(2,0.01);
  fm->SetLineColor(kBlue);

  //afincl->SetParameter(0,0.1); afincl->SetParameter(1,0.1); afincl->SetParameter(2,0.5);
  //afincl->SetLineColor(kBlue);

  //afp->SetParameter(0,0.1); afp->SetParameter(1,0.3); afp->SetParameter(2,1);
  //afp->SetLineColor(kBlue);

  //afm->SetParameter(0,0.1); afm->SetParameter(1,2.); afm->SetParameter(2,3);
  //afm->SetLineColor(kBlue);

  hRatioIncl->Fit("fincl","L","",40,190);
  myCan->SaveAs("InclRatio.png");
  hRatioPlus->Fit("fp","L","",40,190);
  myCan->SaveAs("PlusRatio.png");
  hRatioMinus->Fit("fm","L","",40,110);
  myCan->SaveAs("MinusRatio.png");

  //haRatioIncl->Fit("afincl","L","",40,190);
  //myCan->SaveAs("InclRatio.png");
  //hRatioPlus->Fit("fp","L","",40,190);
  //myCan->SaveAs("PlusRatio.png");
  //hRatioMinus->Fit("fm","L","",40,110);
  //myCan->SaveAs("MinusRatio.png");
}
