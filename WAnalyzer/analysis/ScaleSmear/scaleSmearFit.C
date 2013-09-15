// RooFit headers
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooArgList.h"
#include "RooDataHist.h"
#include "RooFormulaVar.h"
#include "RooHistPdf.h"
#include "RooAddPdf.h"
#include "RooCategory.h"
#include "RooSimultaneous.h"
#include "RooFitResult.h"
#include "RooLandau.h"
#include "RooCBShape.h"
#include "RooGaussian.h"
#include "RooFFTConvPdf.h"
#include <TROOT.h>                        // access to gROOT, entry point to ROOT system
#include <TSystem.h>                      // interface to OS
#include <TStyle.h>                       // class to handle ROOT plotting styles
#include <TFile.h>                        // file handle class
#include <TTree.h>                        // class to access ntuples
#include <TBenchmark.h>                   // class to track macro running statistics
#include <TH1D.h>                         // histogram class
#include <vector>                         // STL vector class
#include <iostream>                       // standard I/O
#include <iomanip>                        // functions to format standard I/O
#include <fstream>                        // functions for file I/O
#include <string>                         // C++ string class
#include <sstream>                        // class for parsing strings
#include <TRandom3.h>
#include <TGaxis.h>

#include "TStyle.h"
#include "../Utils/const.h"
#include "../Utils/CPlot.hh"
#include "../Utils/MitStyleRemix.hh"
#include "../Utils/ZBackgrounds.hh"
#include "../Utils/ZSignals.hh"

int scaleSmearFit(TString RDFile, TString MCFile, char BaseName[30])
{
  cout<<"Processing "<<BaseName<<endl;
  gStyle->SetPalette(1);
  //Data and histograms
  TFile *f_RD = new TFile(RDFile);
  TFile *f_MC = new TFile(MCFile);
  TH1D *h1_ZmassDaughEtaRD = (TH1D*)f_RD->Get("h1_ZmassDaughEtaRD")->Clone();
  TH1D *h1_ZmassDaughEtaMC[ScaleBins][ScaleBins];
  //Variables
  char histName[30];
  RooRealVar zMass("zMass","zMass",60,120);
  RooRealVar *nMC;
  RooRealVar nBRD("nBRD","nBRD",5,2000);
  RooRealVar nSRD("nSRD","nSRD",1000,0,20000);
  RooRealVar nBMC("nBMC","nBMC",5,2000);
  RooRealVar nSMC("nSMC","nSMC",1000,0,20000);
  RooPlot *zmassframe;
  RooPlot *zmassframeMC;
  CPlot *plotFit;
  CPlot *plotFitMC;
  //zMass.setBins(50);
  RooFitResult* fitRes;
  RooFitResult* fitResMC;
  TCanvas *myCan = MakeCanvas("myCan","myCan",800,600);
  RooDataHist *ZmassMC;
  //RooHistPdf *pdfMC;
  RooAddPdf *pdfMC;
  RooAddPdf* pdfRD;
  //RD fitting
  RooDataHist *ZmassRD =
    new RooDataHist("ZmassRD","ZmassRD", RooArgSet(zMass),h1_ZmassDaughEtaRD);
  //CBreitWignerConvCrystalBall ZsignalPdf("ZsigPdf",zMass);
  //pdfRD=new RooAddPdf("pdfRD","pdfRD",RooArgList(*(ZsignalPdf.model)),RooArgList(nRD));
  CVoigtian     ZsigRD("ZsigRD",zMass);
  CErfExpo ZbgRD("ZbgRD",zMass);
  //CQuadraticExp ZbgRD("ZbgRD",zMass);
  pdfRD=new RooAddPdf("pdfRD","pdfRD",RooArgList(*(ZsigRD.model),*(ZbgRD.model)),RooArgList(nSRD,nBRD));
  pdfRD=new RooAddPdf("pdfRD","pdfRD",RooArgList(*(ZsigRD.model),*(ZbgRD.model)),RooArgList(nSRD,nBRD));
  fitRes=pdfRD->fitTo(*ZmassRD,Extended(),Minos(kTRUE),Save(kTRUE));
  //fitRes=ZsignalPdf.model->fitTo(*ZmassRD,Minos(kTRUE),Save(kTRUE));
  zmassframe=zMass.frame(Bins(60));
  ZmassRD->plotOn(zmassframe,MarkerStyle(kFullCircle),MarkerSize(0.9),DrawOption("zp"));
  //ZsignalPdf.model->plotOn(zmassframe,LineColor(kBlue),DrawOption("l"));
  pdfRD->plotOn(zmassframe,LineColor(kBlack),DrawOption("l"));
  pdfRD->plotOn(zmassframe,Components(RooArgSet(*(ZsigRD.model))),LineColor(kBlue),DrawOption("l"));
  pdfRD->plotOn(zmassframe,Components(RooArgSet(*(ZbgRD.model))),LineColor(kRed),DrawOption("l"));
  sprintf(histName,"ZmassRD_%s",BaseName);
  plotFit = new CPlot(histName,zmassframe,"","","Z mass");
  plotFit->setOutDir("Plot");
  plotFit->Draw(myCan,kTRUE,"png");

  //CErfExpo *pdfZbg;
  //double nLL[41][41];

  //                                 90 0.004
  double ScaleWidth = (ScaleH-ScaleL)/(ScaleBins-1);
  double SmearWidth = (SmearH-SmearL)/(ScaleBins-1);
  sprintf(histName,"h2_NLL_%s",BaseName);
  TH2D *h2_NLL = new TH2D(histName,histName,
      ScaleBins,ScaleL-ScaleWidth/2,ScaleH+ScaleWidth/2,
      ScaleBins,SmearL-SmearWidth/2,SmearH+SmearWidth/2);
  //TH2D *h2_NLL = new TH2D("h2_NLL","NLL",41,0.97,1.05,41,0.5,1.5);
  double x,prob;
  //RooAbsReal *nll;
  double nll;
  double binContent;
  //***
  CVoigtian ZsigMC("ZsigMC",zMass);
  RooArgSet allArgset(zMass);
  RooArgSet anaVar;
  //for(int i(0);i<=0;i++)for(int j(0);j<=0;j++)
  for(int i(0);i<=ScaleBins-1;i++)for(int j(0);j<=ScaleBins-1;j++)
  {
    sprintf(histName,"h1_ZmassDaughEta_%d_%d",i,j);
    h1_ZmassDaughEtaMC[i][j] = (TH1D*)f_MC->Get(histName)->Clone(histName);
    ZmassMC =
      new RooDataHist("ZmassMC","ZmassMC",RooArgSet(zMass),h1_ZmassDaughEtaMC[i][j]);
    //                                               interpolation order
    //pdfMC =new RooHistPdf ("pdfMC", "pdfMC", zMass,*ZmassMC, 1);
    //Using fitting MC
    nSMC.setVal(285);
    ZsigMC.mass->setVal(91.37);
    ZsigMC.sigma->setVal(0.42);
    ZsigMC.width->setVal(4.4);
    pdfMC = new RooAddPdf("pdfMC","pdfMC",RooArgList(*(ZsigMC.model)),RooArgList(nSMC));
    fitResMC = pdfMC->fitTo(*ZmassMC,Extended(),Minos(kTRUE),Save(kTRUE),SumW2Error(kTRUE));//SumW2Error(kTRUE) default

    nll=0;
    //nll= h1_ZmassDaughEtaMC[i][j]->Chi2Test(h1_ZmassDaughEtaRD,"CHI2/NDF");
    // code 1000 dataHist sum
    int intCode = pdfMC->getAnalyticalIntegral(allArgset,anaVar);
    double norm = pdfMC->analyticalIntegral(intCode);
    cout<<"norm: code "<<norm<<" : "<<intCode<<"======================"<<endl;
    //double totalProb(0);
    //****
    for(int k(1);k<=60;k++)
    {
      x=h1_ZmassDaughEtaMC[i][j]->GetBinCenter(k);
    //  binContent = h1_ZmassDaughEtaRD->GetBinContent(k);
      //binContent = h1_ZmassDaughEtaMC[i][j]->GetBinContent(k);
      zMass=x;
      //prob = ZsignalPdf.model->evaluate();
      binContent = ZsigRD.model->evaluate()*(120-60)/60.*nSRD.getVal();
      prob = pdfMC->evaluate()*(120-60)/60.;
      //cout<<"binCont, prob "<<binContent<<" "<<prob<<endl;
      //totalProb +=prob;
      nll+=-binContent*log(prob);
      //cout<<" x: prob "<<x<<"  "<<prob<<endl;
    }
    h2_NLL->SetBinContent(i+1,j+1,nll);
    /***/
    //
    //
    if( j==0 || j==int(ScaleBins/2)|| j==(ScaleBins-1) )
    {
      //RD MCpdf RDpdf Plot
      zmassframe =zMass.frame(Bins(60));
      ZmassRD->plotOn(zmassframe,MarkerStyle(kFullCircle),MarkerSize(0.9),DrawOption("zp"));
      pdfRD->plotOn(zmassframe,LineColor(kBlack));
      pdfMC->plotOn(zmassframe,LineColor(kBlue));
      //pdfRD->plotOn(zmassframe,Components(RooArgSet(*(pdfZbg->model))),LineColor(kRed));
      sprintf(histName,"Zmass_%s_%d_%d",BaseName,i,j);
      plotFit = new CPlot(histName,zmassframe,"","","Z mass");
      plotFit->SetLegend(0.68,0.57,0.93,0.8);
      plotFit->GetLegend()->AddEntry(pdfRD,"RD","f");
      plotFit->GetLegend()->AddEntry(pdfMC,"MC","f");
      plotFit->setOutDir("Plot");
      plotFit->Draw(myCan,kTRUE,"png");
      //MC MCPdf Plot
      zmassframeMC = zMass.frame(Bins(60));
      ZmassMC->plotOn(zmassframeMC,LineColor(kBlue),DrawOption("p"));
      pdfMC->plotOn(zmassframeMC,LineColor(kBlue),DrawOption("l"));
      sprintf(histName,"ZmassMC_%s_%d_%d",BaseName,i,j);
      plotFitMC = new CPlot(histName,zmassframeMC,"","","Z mass MC");
      plotFitMC->setOutDir("Plot");
      plotFitMC->Draw(myCan,kTRUE,"png");
    }
  }
  //====
  //Plot
  //====
  //Zmass----------
  //CPlot *plotZmassRD=new CPlot("plotZmassRD","","zMass","Event");
  //plotZmassRD->setOutDir("Plot");
  //plotZmassRD->AddHist1D(h1_ZmassDaughEtaRD,"",kBlack);
  //plotZmassRD->SetLegend(0.68,0.57,0.93,0.8);
  //plotZmassRD->GetLegend()->AddEntry(h1_ZmassDaughEtaRD,"RD Ele","l");
  //plotZmassRD->AddTextBox("both lepton at the |Eta|<0.4",0.65,0.80,0.99,0.86,0);
  //plotZmassRD->Draw(myCan,kTRUE,"png");
  //NLL------------
  sprintf(histName,"plotNLL_%s",BaseName);
  CPlot *plotNll=new CPlot(histName,"","Scale","Smear");
  plotNll->setOutDir("Plot");
  //plotNll->AddHist2D(h2_NLL,"COLZ",kWhite,kBlack);
  plotNll->AddHist2D(h2_NLL,"SURF3",kWhite,kBlack);
  plotNll->Draw(myCan,kTRUE,"png");
  //****/
  return 0;
}
