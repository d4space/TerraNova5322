#include <iostream.h>
#include <sstream>
#include <TMath.h>       /* fmax */
#include <stdlib.h>
#include <string.h>
#define Nbin 14
void glbToId_eta()
{
  ofstream txtfile;
  char txtfname[100];
  char histfname[100];
  sprintf(txtfname,"eta_plus.txt");
  sprintf(histfname,"eta_plus.png");
  //sprintf(txtfname,"eta_minus.txt");
  //sprintf(histfname,"eta_minus.png");
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
  
  TFile *f_MCndof2= new TFile("TnP_GlbToID_MCetaplus_Wpteta_eta.root","read");
  TFile *f_MCndof4= new TFile("TnP_GlbToID_MCetaplus_ndof4_Wpteta_eta.root","read");

  //TFile *f_MCndof2= new TFile("TnP_GlbToID_MCetaminus_Wpteta_eta.root","read");
  //TFile *f_MCndof4= new TFile("TnP_GlbToID_MCetaminus_ndof4_Wpteta_eta.root","read");
  RooDataSet *datasetMC = (RooDataSet*)f_MCndof2->Get("tpTree/Wpteta_eta/fit_eff");
  cout<<"ntry: "<<datasetMC->numEntries()<<endl;
  double XMC[Nbin],XMCerrL[Nbin],XMCerrH[Nbin],YMC[Nbin],YMCerrLo[Nbin],YMCerrHi[Nbin],ErrMC[Nbin];
  for(int i(0); i<datasetMC->numEntries();i++)
  {
    const RooArgSet &pointMC=*datasetMC->get(i);
    RooRealVar &etaMC=pointMC["eta"],&effMC = pointMC["efficiency"];
    XMC[i]=etaMC.getVal();
    XMCerrL[i]=-etaMC.getAsymErrorLo();
    XMCerrH[i]=etaMC.getAsymErrorHi();
    YMC[i]=effMC.getVal();
    YMCerrLo[i]=-effMC.getAsymErrorLo();
    YMCerrHi[i]=effMC.getAsymErrorHi();
    ErrMC[i]=TMath::Max(YMCerrLo[i],YMCerrHi[i]);
  }

  grMC=new TGraphAsymmErrors(Nbin,XMC,YMC,XMCerrL,XMCerrH,YMCerrLo,YMCerrHi);
  grMC->SetLineColor(kRed);
  grMC->SetMarkerColor(kRed);
  grMC->SetMinimum(0.5);
  grMC->SetMaximum(1.1);
  grMC->GetXaxis()->SetNdivisions(505);
  grMC->GetXaxis()->SetTitle("Muon #eta");
  grMC->GetYaxis()->SetTitle("ID+ISO Efficiency");
  grMC->Draw("AP");

  RooDataSet *datasetRD = (RooDataSet*)f_MCndof4->Get("tpTree/Wpteta_eta/fit_eff");
  double XRD[Nbin],XRDerrL[Nbin],XRDerrH[Nbin],YRD[Nbin],YRDerrLo[Nbin],YRDerrHi[Nbin],ErrRD[Nbin];
  for(int i(0); i<datasetRD->numEntries();i++)
  {
    const RooArgSet &pointRD=*datasetRD->get(i);
    RooRealVar &etaRD=pointRD["eta"],&effRD = pointRD["efficiency"];
    XRD[i]=etaRD.getVal();
    XRDerrL[i]=-etaRD.getAsymErrorLo();
    XRDerrH[i]=etaRD.getAsymErrorHi();
    YRD[i]=effRD.getVal();
    YRDerrLo[i]=-effRD.getAsymErrorLo();
    YRDerrHi[i]=effRD.getAsymErrorHi();
    ErrRD[i]=TMath::Max(YRDerrLo[i],YRDerrHi[i]);
  }
  txtfile << "Bins \t MC ndof>2\t\t\t MC ndof>4 \t\t\t Scale Factor ndof4/ndof2 "  << endl;
  for(int i(0); i<datasetRD->numEntries();i++)
  {
    txtfile << i << "\t" << YMC[i] << "+/-" << ErrMC[i] << "\t\t" << YRD[i] << "+/-" << ErrRD[i] << "\t\t" << YRD[i]/YMC[i] << "+/-" << YRD[i]*sqrt(ErrMC[i]*ErrMC[i]/(YMC[i]*YMC[i])+ErrRD[i]*ErrRD[i]/(YRD[i]*YRD[i]))/YMC[i] << endl;
  }

  grRD=new TGraphAsymmErrors(Nbin,XRD,YRD,XRDerrL,XRDerrH,YRDerrLo,YRDerrHi);
  grRD->SetLineColor(kBlack);
  grRD->SetMarkerColor(kBlack);
  Lgd->AddEntry(grMC,"MC ndof>2","pl");
  Lgd->AddEntry(grRD,"MC ndof>4","pl");
  Lgd->SetFillStyle(0);
  Lgd->Draw();
  grRD->Draw("PSAME");
  
  myCan->SaveAs(histfname);
  txtfile.close();
}
