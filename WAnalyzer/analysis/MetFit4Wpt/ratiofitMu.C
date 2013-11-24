#if !defined(__CINT__) || defined(__MAKECINT__)
#include <iostream>                   // standard I/O
#include <fstream>                   // standard I/O
#include <TMath.h>
#include <TFile.h>                    // file handle class
#include <TTree.h>                    // class to access ntuples
#include <TF1.h>                      // 1D function
#include <TFitResult.h>               // class to handle fit results
#include <TGraphErrors.h>             // graph class
#include <TGraphAsymmErrors.h>             // graph class
#include "Math/LorentzVector.h"       // 4-vector class

#include "../../../Utils/CPlot.hh"          // helper class for plots
#include "../../../Utils/MitStyleRemix.hh"  // style settings for drawing

#include "RooGlobalFunc.h"
#include "RooRealVar.h"
#include "RooLandau.h"
#include "RooGaussian.h"
#include "RooDataSet.h"
#include "RooAbsPdf.h"
#include "RooAddPdf.h"
#include "RooHistPdf.h"
#include "RooPlot.h"
#include "RooFitResult.h"
#include "RooDataHist.h"
#include "RooFormulaVar.h"

#endif

using namespace RooFit;
typedef ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiM4D<double> > LorentzVector;
//typedef ROOT::Math::MinimizerOptions::SetDefaultPrintLevel(1);

Double_t ExpFunc(double *x, double *par)
{
  Double_t a  = par[0];
  Double_t b  = par[1];
  Double_t c  = par[2];
  
  return a*TMath::Exp(-x[0]/b) + c;
}

Double_t df_dPar(Double_t *x, Double_t *p) {
  TF1 *fitFunc = new TF1("ExpFunc",ExpFunc,40,600,3);
  fitFunc->SetParameters(p[1],p[2],p[3]);
  Double_t grad[3];
  int ipar = int(p[0]);
  assert (ipar >=0 && ipar < 3 );
  
  assert(fitFunc);
  fitFunc->GradientPar(x, grad);
  return grad[ipar];
}

Double_t dExpFunc(const TF1 *fcn, const Double_t x, const TFitResultPtr fs) {
  Double_t df[3];
  Double_t a = fcn->GetParameter(0);
  Double_t b = fcn->GetParameter(1);
  Double_t c = fcn->GetParameter(2);
  
  TF1 *deriv_par0 = new TF1("dfdp0",df_dPar,40,600,4);
  deriv_par0->SetParameters(0,a,b,c); // This will set the derivative for the first parameter.
  TF1 *deriv_par1 = new TF1("dfdp1",df_dPar,40,600,4);
  deriv_par1->SetParameters(1,a,b,c); // This will set the derivative for the second parameter
  TF1 *deriv_par2 = new TF1("dfdp2",df_dPar,40,600,4);
  deriv_par2->SetParameters(2,a,b,c); // This will set the derivative for the 3rd parameter
  df[0] = deriv_par0->Eval(x);
  df[1] = deriv_par1->Eval(x);
  df[2] = deriv_par2->Eval(x);
  Double_t err2=0;
  for(Int_t i=0; i<3; i++) {
    err2 += df[i]*df[i]*(fs->GetCovarianceMatrix()[i][i]);
    for(Int_t j=i+1; j<3; j++) {
      err2 += 2.0*df[i]*df[j]*(fs->GetCovarianceMatrix()[i][j]);
    }
  }
  assert(err2>=0);
  return sqrt(err2);
}

void ratiofitMu()
{
  TString outputDir = "ratio";
  CPlot::sOutDir = outputDir;
  gSystem->mkdir(outputDir);

  //const Int_t nbins = 6;
  const Int_t nbins = 10;

  //double Bins[7];
  double Bins[11];
  Bins[0] = 40;
  Bins[1] = 45;
  Bins[2] = 50;
  Bins[3] = 60;
  Bins[4] = 70;
  Bins[5] = 110;
  Bins[6] = 150;
  Bins[7] = 190;
  Bins[8] = 250;
  Bins[9] = 600;
  Bins[10]= 602;
 
  TH1D *hSig;
  TH1D *hSigp;
  TH1D *hSigm;
  TH1D *hQCD;
  TH1D *hQCDp;
  TH1D *hQCDm;
  
  TFile* fname = new TFile("./SigYields_Nominal.root");
  
  hSig  = (TH1D*)fname->Get("hSigWpt") ->Clone("hSig");     hSig  -> Sumw2();
  hSigp = (TH1D*)fname->Get("hSigWPpt")->Clone("hSigp");    hSigp -> Sumw2();
  hSigm = (TH1D*)fname->Get("hSigWMpt")->Clone("hSigm");    hSigm -> Sumw2();
  hQCD  = (TH1D*)fname->Get("hQCDWpt") ->Clone("hQCD");     hQCD  -> Sumw2();
  hQCDp = (TH1D*)fname->Get("hQCDWPpt")->Clone("hQCDp");    hQCDp -> Sumw2();
  hQCDm = (TH1D*)fname->Get("hQCDWMpt")->Clone("hQCDm");    hQCDm -> Sumw2();
  
  //hQCD  -> Divide(hSig);
  //hQCDp -> Divide(hSigp);
  //hQCDm -> Divide(hSigm);
 

  TFitResultPtr fitres;  TF1 *expfunc = new TF1("expfunc",ExpFunc,40,600,3);
  TF1 *fexpfunc = new TF1("fexpfunc",ExpFunc,40,600,3);
  
  TGraphAsymmErrors *grRatio  = 0;
  
  Double_t xval[nbins];
  
  for(Int_t ibin=0; ibin<nbins; ibin++) {
    xval[ibin] = 0.5*(Bins[ibin+1]+Bins[ibin]);
    //xerr[ibin] = 0.5*(Bins[ibin+1]-Bins[ibin]);
    //yval[ibin] = rQCD->GetBinContent(ibin+6);
    //yerr[ibin] = rQCD->GetBinError(ibin+6);
    //cout <<ibin<<"\t "<<xval[ibin]<<"\t "<<xerr[ibin]<<"\t "<<yval[ibin]<<"\t "<<yerr[ibin]<<endl;
    cout <<ibin<<"\t "<<xval[ibin]<<endl;
  }

  TCanvas *c = MakeCanvas("c","c",900,900);
  TGraphErrors *errBand = new TGraphErrors(nbins);

  char fitparam[100];
  char chi2ndf[50];
  
  //grRatio = new TGraphAsymmErrors(hQCD, hSig, "n");
  //grRatio = new TGraphAsymmErrors(hQCDp, hSigp, "n");
  grRatio = new TGraphAsymmErrors(hQCDm, hSigm, "n");
  grRatio->SetName("grRatio");

  //expfunc->SetParameters(10.3748,16.208,0.107678);
  //expfunc->SetParameters(8.76357,17.4542,0.00762632);
  expfunc->SetParameters(9.92166,16.2575,0.236426);
  //expfunc->SetRange(40,190);
  expfunc->SetRange(40,110);
  
  //fitres = grRatio->Fit("expfunc","QMRN0FBSE");
  fitres = grRatio->Fit("expfunc","QRN0SE");
  //fitres = grRatio->Fit("expfunc","QRN0SE");
  fexpfunc->SetParameters(expfunc->GetParameter(0),expfunc->GetParameter(1),expfunc->GetParameter(2));
  sprintf(chi2ndf,"#chi^{2}/ndf = %.4f",(expfunc->GetChisquare())/(expfunc->GetNDF()));

  for(Int_t i=0; i<nbins; i++) {
    cout <<i<<"\t"<<xval[i]<<"\t"<<expfunc->Eval(xval[i])<<"\t"<<dExpFunc(expfunc,xval[i],fitres)<<endl;
    errBand->SetPoint(i,xval[i],expfunc->Eval(xval[i]));
    errBand->SetPointError(i,0,dExpFunc(expfunc,xval[i],fitres));
  }

  CPlot plotExpFunc("mPlotExpFunc","","W pT","QCD/Signal");
  plotExpFunc.setOutDir(CPlot::sOutDir);
  plotExpFunc.SetYRange(0,1);
  plotExpFunc.AddFcn(fexpfunc,kBlue,2);
  plotExpFunc.AddGraph(grRatio,"");
  plotExpFunc.AddGraph(errBand,"3",kAzure-9,kFullDotSmall);
  plotExpFunc.AddGraph(grRatio,"",kBlack,kFullCircle);
  plotExpFunc.AddFcn(expfunc,kRed);
  plotExpFunc.AddLine(40,0,40,1,kGreen,2);
  //plotExpFunc.AddLine(190,0,190,1,kGreen,2);
  plotExpFunc.AddLine(110,0,110,1,kGreen,2);
  
  //plotExpFunc.AddTextBox(chi2ndf,0.5,0.87,0.8,0.82,0,kBlack,-1);
  //sprintf(fitparam,"a = %.4f #pm %.4f",expfunc->GetParameter(0),expfunc->GetParError(0));
  //plotExpFunc.AddTextBox(fitparam,0.5,0.80,0.8,0.75,0,kBlack,-1);
  //sprintf(fitparam,"b = %.4f #pm %.4f",expfunc->GetParameter(1),expfunc->GetParError(1));
  //plotExpFunc.AddTextBox(fitparam,0.5,0.75,0.8,0.70,0,kBlack,-1);
  //sprintf(fitparam,"c = %.4f #pm %.4f",expfunc->GetParameter(2),expfunc->GetParError(2));
  //plotExpFunc.AddTextBox(fitparam,0.5,0.70,0.8,0.65,0,kBlack,-1);
  
  plotExpFunc.Draw(c,kTRUE,"png");

}
