#include <iostream.h>
#include <sstream>
#include <TMath.h>       /* fmax */
#include <stdlib.h>
#include <string.h>
#include <TLine.h>
#define Nbin 4
void track_pt(const int charge)
{
  if (charge==1)
  char  ch[20] = "plus"; 
  else if (charge==-1)
  char ch[20] = "minus";
  ofstream txtfile;
  char txtfname[100];
  char histfname[100];
  sprintf(txtfname,"pt_%s.txt",ch);
  sprintf(histfname,"pt_%s.png",ch);
  txtfile.open(txtfname);
  txtfile << fixed << setprecision(4);
  TCanvas *myCan=new TCanvas("myCan","myCan",800,600);
  gStyle->SetLineWidth(2.);
  gStyle->SetLabelSize(0.04,"xy");
  gStyle->SetTitleSize(0.05,"xy");
  gStyle->SetTitleOffset(1.1,"x");
  gStyle->SetTitleOffset(1.2,"y");
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadRightMargin(0.1);
  gStyle->SetPadBottomMargin(0.16);
  gStyle->SetPadLeftMargin(0.12);

  myCan->SetGrid();
  TLegend* Lgd = new TLegend(.8, .25,.9,.35);
  if (charge==1){
    TFile *f_MC= new TFile("TnP_Tracking_dr030e030_MCptplus.root","read");
    TFile *f_RD= new TFile("TnP_Tracking_dr030e030_RDptplus.root","read");
  }else if (charge==-1){
    TFile *f_MC= new TFile("TnP_Tracking_dr030e030_MCptminus.root","read");
    TFile *f_RD= new TFile("TnP_Tracking_dr030e030_RDptminus.root","read");
  }
  line = new TLine(15,1,80,1);
  line->SetLineStyle(2);
  line->SetLineWidth(3);
  
  TPaveText *title = new TPaveText(.1,1,.95,.95,"NDC");
  title->SetFillStyle(0);
  title->SetBorderSize(0);
  title->SetTextSize(0.04);
  title->AddText("CMS Preliminary, 18.9 pb^{-1} at #sqrt{s}=8 TeV");

  RooDataSet *datasetMC = (RooDataSet*)f_MC->Get("tpTreeSta/eff_pt_dr030e030/fit_eff");
  cout<<"ntry: "<<datasetMC->numEntries()<<endl;
  double XMC[Nbin],XMCerrL[Nbin],XMCerrH[Nbin],YMC[Nbin],YMCerrLo[Nbin],YMCerrHi[Nbin],ErrMC[Nbin];
  for(int i(0); i<datasetMC->numEntries();i++)
  {
    const RooArgSet &pointMC=*datasetMC->get(i);
    RooRealVar &ptMC=pointMC["pt"],&effMC = pointMC["efficiency"];
    XMC[i]=ptMC.getVal();
    XMCerrL[i]=-ptMC.getAsymErrorLo();
    XMCerrH[i]=ptMC.getAsymErrorHi();
    YMC[i]=effMC.getVal();
    YMCerrLo[i]=-effMC.getAsymErrorLo();
    YMCerrHi[i]=effMC.getAsymErrorHi();
    ErrMC[i]=TMath::Max(YMCerrLo[i],YMCerrHi[i]);
  }
  grMC=new TGraphAsymmErrors(Nbin,XMC,YMC,XMCerrL,XMCerrH,YMCerrLo,YMCerrHi);
  grMC->SetLineColor(kRed);
  grMC->SetMarkerColor(kRed);
  grMC->SetMarkerStyle(21);
  grMC->SetMinimum(0.7);
  grMC->SetMaximum(1.11);
  grMC->GetXaxis()->SetNdivisions(505);
  grMC->GetXaxis()->SetTitle("Muon p_{T} [GeV/c]");
  grMC->GetYaxis()->SetTitle("Tracking Efficiency");
  grMC->Draw("AP");

  RooDataSet *datasetRD = (RooDataSet*)f_RD->Get("tpTreeSta/eff_pt_dr030e030/fit_eff");
  double XRD[Nbin],XRDerrL[Nbin],XRDerrH[Nbin],YRD[Nbin],YRDerrLo[Nbin],YRDerrHi[Nbin],ErrRD[Nbin];
  for(int i(0); i<datasetRD->numEntries();i++)
  {
    const RooArgSet &pointRD=*datasetRD->get(i);
    RooRealVar &ptRD=pointRD["pt"],&effRD = pointRD["efficiency"];
    XRD[i]=ptRD.getVal();
    XRDerrL[i]=-ptRD.getAsymErrorLo();
    XRDerrH[i]=ptRD.getAsymErrorHi();
    YRD[i]=effRD.getVal();
    YRDerrLo[i]=-effRD.getAsymErrorLo();
    YRDerrHi[i]=effRD.getAsymErrorHi();
    ErrRD[i]=TMath::Max(YRDerrLo[i],YRDerrHi[i]);
  }

  double SF[Nbin],SFerr[Nbin],SFerrL[Nbin],SFerrH[Nbin];
  for(int i(0); i<datasetRD->numEntries();i++)
  {
    SF[i]=YRD[i]/YMC[i];
    SFerrL[i]=YRD[i]*sqrt(YMCerrLo[i]*YMCerrLo[i]/(YMC[i]*YMC[i])+YRDerrLo[i]*YRDerrLo[i]/(YRD[i]*YRD[i]))/YMC[i];
    SFerrH[i]=YRD[i]*sqrt(YMCerrHi[i]*YMCerrHi[i]/(YMC[i]*YMC[i])+YRDerrHi[i]*YRDerrHi[i]/(YRD[i]*YRD[i]))/YMC[i];
    SFerr[i]=TMath::Max(SFerrL[i],SFerrH[i]);
    txtfile << i << "\t" << YMC[i] << "\t" << ErrMC[i] << "\t" << YRD[i] << "\t" << ErrRD[i] << "\t" << SF[i] << "\t" << SFerr[i] << endl;
  }

  grRD=new TGraphAsymmErrors(Nbin,XRD,YRD,XRDerrL,XRDerrH,YRDerrLo,YRDerrHi);
  grRD->SetLineColor(kBlack);
  grRD->SetMarkerColor(kBlack);
  
  grSF=new TGraphAsymmErrors(Nbin,XRD,SF,0,0,SFerrL,SFerrH);
  grSF->SetLineColor(8);
  grSF->SetMarkerStyle(25);
  grSF->SetMarkerColor(8);
  
  Lgd->AddEntry(grMC,"MC","pl");
  Lgd->AddEntry(grRD,"RD","pl");
  Lgd->SetFillStyle(0);
  Lgd->Draw();
  grRD->Draw("PSAME");
  grSF->Draw("PSAME");
  line->Draw();
  title->Draw();

  myCan->SaveAs(histfname);
  txtfile.close();
}
