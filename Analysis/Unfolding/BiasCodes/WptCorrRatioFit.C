#include "TStyle.h"
#include "../../Utils/const.h"
#include "../../Utils/CPlot.hh"
#include "../../Utils/MitStyleRemix.hh"
#include "../../Utils/Unfolder.h"
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

#include "RooRealVar.h"
#include "RooPoisson.h"
#include "RooPolynomial.h"
#include "RooLandau.h"
#include "RooPlot.h"
#include "RooBinning.h"
#include "RooExponential.h"
#include "RooBreitWigner.h"
#include "RooCBShape.h"
#include "RooDataHist.h"
#include "RooAddPdf.h"
#include "RooFitResult.h"
#include "RooNLLVar.h"
#include "RooMinuit.h"
#include "RooChi2Var.h"
#include "RooGenericPdf.h"
#include "RooFFTConvPdf.h"

const int nBins = 14;
double WptLogBins[nBins] = {1.0,7.5,12.5,17.5,24,30,40,50,70,110,150,190,250,600};
double WptBins[nBins] = {0.0,7.5,12.5,17.5,24,30,40,50,70,110,150,190,250,600};
double WptBinsLo[9] = {0.0,7.5,12.5,17.5,24,30,40,50,70};
double WptBinsHi[5] = {110,150,190,250,600};


int WptCorrRatioFit(TString BaseName,TString unfName)
{
  TString resultDir = "TestFit";
  gSystem->mkdir(resultDir,kTRUE);
  char tmpName[30];
  TString tmpTStr;
  TFile *f_Data;
  
  f_Data = new TFile("../../RstSelection/WpT_PostFSRData_MC_ratio.root");

  CPlot *pltFit1;
  CPlot *pltFit2;
  CPlot *pltFit3;
  CPlot *pltFit4;
  TH1D* lData1;
  TH1D* lData2;
  TH1D* lData3;
  TH1D* lData4;
  TH1D* hData1 = new TH1D("hData1","hData1",13,0,13); //hData->Sumw2();
  TH1D* hData2 = new TH1D("hData2","hData2",13,0,13); //hData->Sumw2();
  TH1D* hData3 = new TH1D("hData3","hData3",13,0,13); //hData->Sumw2();
  TH1D* hData4 = new TH1D("hData4","hData4",13,0,13); //hData->Sumw2();
  TH1D* hData41 = new TH1D("hData41","hData41",4,0,4); //hData->Sumw2();
  TH1D* hData42 = new TH1D("hData42","hData42",4,4,8); //hData->Sumw2();
  TH1D* hData43 = new TH1D("hData43","hData43",5,8,13); //hData->Sumw2();
  TH1D* hFit1  = new TH1D("hFit1","hFit1",13,WptBins);
  TH1D* hFit2  = new TH1D("hFit2","hFit2",13,WptBins);
  TH1D* hFit3  = new TH1D("hFit3","hFit3",13,WptBins);
  TH1D* hFit4  = new TH1D("hFit4","hFit4",13,WptBins);
  
  lData1   = (TH1D*)f_Data->Get("h1_WpT_WpToMN_ratio")->Clone("lData1");
  lData2   = (TH1D*)f_Data->Get("h1_WpT_WmToMN_ratio")->Clone("lData2");
  lData3   = (TH1D*)f_Data->Get("h1_WpT_WpToEN_ratio")->Clone("lData3");
  lData4   = (TH1D*)f_Data->Get("h1_WpT_WmToEN_ratio")->Clone("lData4");
  
  double tmp1;
  double tmp2;
  double tmp3;
  tmp1=0.;
  tmp2=0.;
  tmp3=0.;
  for( int ipt(1);ipt<=lData1->GetXaxis()->GetNbins();ipt++)
  {
    hData1->SetBinContent(ipt,lData1->GetBinContent(ipt));
    hData2->SetBinContent(ipt,lData2->GetBinContent(ipt));
    hData3->SetBinContent(ipt,lData3->GetBinContent(ipt));
    hData4->SetBinContent(ipt,lData4->GetBinContent(ipt));
    hData1->SetBinError(ipt,lData1->GetBinError(ipt));
    hData2->SetBinError(ipt,lData2->GetBinError(ipt));
    hData3->SetBinError(ipt,lData3->GetBinError(ipt));
    hData4->SetBinError(ipt,lData4->GetBinError(ipt));
    if(ipt<5)
      tmp1+=lData4->GetBinContent(ipt);
    if(ipt>4 && ipt<9)
      tmp2+=lData4->GetBinContent(ipt);
    if(ipt>8)
      tmp3+=lData4->GetBinContent(ipt);
  }

  //RooRealVar x("x", "x",0,600);
  RooRealVar x("x", "x",0,13);
  x.setBins(13);
  x.setRange("R0",0,4) ;
  x.setRange("R1",4,8) ;
  x.setRange("R2",8,13) ; 
  RooDataHist* dataHist1;
  RooDataHist* dataHist2;
  RooDataHist* dataHist3;
  RooDataHist* dataHist4;
  dataHist1 = new RooDataHist("dataHist1","dataHist1",RooArgSet(x), hData1);
  dataHist2 = new RooDataHist("dataHist2","dataHist2",RooArgSet(x), hData2);
  dataHist3 = new RooDataHist("dataHist3","dataHist3",RooArgSet(x), hData3);
  dataHist4 = new RooDataHist("dataHist4","dataHist4",RooArgSet(x), hData4);
  TCanvas *myCan = MakeCanvas("myCan","myCan",900,800);

  RooRealVar c1("c1","",-0.0982147,-100,100);
  RooRealVar c2("c2","",0.0201807,-100,100);
  RooRealVar c3("c3","",-0.00109382,-100,100);
  RooRealVar d1("d1","",-0.0982147,-100,100);
  RooRealVar d2("d2","",0.0201807,-100,100);
  RooRealVar d3("d3","",-0.00109382,-100,100);
  RooRealVar e1("e1","",-0.0982147,-100,100);
  RooRealVar e2("e2","",0.0201807,-100,100);
  RooRealVar e3("e3","",-0.00109382,-100,100);
  //RooRealVar f1("f1","",-0.0982147,-1,1);
  //RooRealVar f2("f2","",0.0201807,-0.1,0.1);
  //RooRealVar f3("f3","",-0.00109382,-0.01,0.01);
  
  RooRealVar h1("h1","",-0.0852536,-100,100);
  RooRealVar h2("h2","",0.0202208,-100,100);
  RooRealVar h3("h3","",-0.00112168,-100,100);
  RooRealVar h4("h4","",0.0202208,-100,100);
  RooRealVar h5("h5","",-0.00112168,-100,100);
  RooRealVar h6("h6","",0.0000112168,-100,100);
  RooRealVar h7("h7","",-0.00000112168,-100,100);
  RooRealVar h8("h8","",0.00000000112168,-100,100);
  RooRealVar f1("f1","",-0.085,-100,100);
  RooRealVar f2("f2","",0.0202208,-100,100);
  RooRealVar f3("f3","",-0.0011,-100,100);
  RooRealVar f4("f4","",0.0852536,-100,100);
  RooRealVar f5("f5","",-0.0202,-100,100);
  RooRealVar f6("f6","",0.0002208,-100,100);
  RooRealVar f7("f7","",-0.0002208,-100,100);
  RooRealVar psi("psi","psi",0,3.14159268);
  RooRealVar frac("frac","frac",1,-100,100);
  RooGenericPdf Tpsi("Tpsi","sin(2*@0)",psi);

  //RooRealVar g1("g1","",-0.5,-100,100);
  RooRealVar g1("g1","",-0.04,-10.0,10.0);
  RooRealVar g2("g2","",-0.02,-10,10);
  RooRealVar g3("g3","",-0.00112168,-100,100);

  RooPolynomial model1("model1", "", x, RooArgList(c1,c2,c3));
  RooPolynomial model2("model2", "", x, RooArgList(d1,d2,d3));
  RooPolynomial model3("model3", "", x, RooArgList(e1,e2,e3));
  //RooPolynomial model4("model4", "", x, RooArgList(h1,h2,h3,h4,h5,h6,h7));
  RooPolynomial model4("model4", "", x, RooArgList(h1,h2,h3));
  //RooPolynomial model4("model4", "", x, RooArgList(h1,h2,h3,h4,h5));
  //RooPolynomial model4("model4", "", x, RooArgList(f1,f2,f3,f4));
  RooPolynomial model4Lo("model4Lo", "", x, RooArgList(f1,f2));
  //RooPolynomial model4Lo0("model4Lo0", "", x, RooArgList(f3,f4));
  RooPolynomial model4Hi("model4Hi", "", x, RooArgList(g1));
  RooPolynomial model4Lo0("model4Lo0", "", x, RooArgList(g3));
  //RooPolynomial model4("model4", "", x, RooArgList(f1,f2,f3,f4,f5,f6));
  //RooPolynomial model4("model4", "", x, RooArgList(f1,f2,f3,f4,f5,f6,f7));
  //RooPolynomial poly4("poly4", "", x, RooArgList(f1,f2,f3,f4));
  //RooAddPdf model4("model4","",poly4,Tpsi,frac);
  
  model1.fitTo(*dataHist1);
  model2.fitTo(*dataHist2);
  model3.fitTo(*dataHist3);
  model4.fitTo(*dataHist4);
  model4Lo0.fitTo(*dataHist4,Range("R0"));
  model4Lo.fitTo(*dataHist4,Range("R1"));
  model4Hi.fitTo(*dataHist4,Range("R2"));
  RooPlot* xframe = x.frame(Bins(13));
  
  //x.setVal(12);
  //cout<<"Value: "<<model4Hi.evaluate()<<endl;
  //cout<<"Value: "<<model4Hi.getVal()<<endl;
  
  //pltFit1 = new CPlot("MuPFit",xframe,"","","");
  //pltFit1 -> setOutDir(resultDir);
  //dataHist1->plotOn(xframe,MarkerStyle(kFullCircle),MarkerSize(0.9),DrawOption("ZP"),DataError(RooAbsData::SumW2));
  //model1.plotOn(xframe,LineColor(kRed));
  //pltFit1->Draw(myCan,kTRUE,"png");
  
  //pltFit2 = new CPlot("MuMFit",xframe,"","","");
  //pltFit2 -> setOutDir(resultDir);
  //dataHist2->plotOn(xframe,MarkerStyle(kFullCircle),MarkerSize(0.9),DrawOption("ZP"),DataError(RooAbsData::SumW2));
  //model2.plotOn(xframe,LineColor(kRed));
  //pltFit2->Draw(myCan,kTRUE,"png");
  
  //pltFit3 = new CPlot("ElPFit",xframe,"","","");
  //pltFit3 -> setOutDir(resultDir);
  //dataHist3->plotOn(xframe,MarkerStyle(kFullCircle),MarkerSize(0.9),DrawOption("ZP"),DataError(RooAbsData::SumW2));
  //model3.plotOn(xframe,LineColor(kRed));
  //pltFit3->Draw(myCan,kTRUE,"png");
  
  pltFit4 = new CPlot("ElMFit",xframe,"","","");
  pltFit4 -> setOutDir(resultDir);
  dataHist4->plotOn(xframe,MarkerStyle(kFullCircle),MarkerSize(0.9),DrawOption("ZP"),DataError(RooAbsData::SumW2));
  model4.plotOn(xframe,LineColor(kRed));
  model4Lo0.plotOn(xframe,LineColor(kCyan));
  model4Lo.plotOn(xframe,LineColor(kBlue));
  model4Hi.plotOn(xframe,LineColor(kGreen));
  pltFit4->Draw(myCan,kTRUE,"png");
  
  cout<<"c1: "<<c1.getVal()<<endl;
  cout<<"c2: "<<c2.getVal()<<endl;
  cout<<"c3: "<<c3.getVal()<<endl;
  cout<<"d1: "<<d1.getVal()<<endl;
  cout<<"d2: "<<d2.getVal()<<endl;
  cout<<"d3: "<<d3.getVal()<<endl;
  cout<<"e1: "<<e1.getVal()<<endl;
  cout<<"e2: "<<e2.getVal()<<endl;
  cout<<"e3: "<<e3.getVal()<<endl;
  cout<<"f1: "<<f1.getVal()<<endl;
  cout<<"f2: "<<f2.getVal()<<endl;
  cout<<"f3: "<<f3.getVal()<<endl;
  
  c1.setConstant(kTRUE);
  c2.setConstant(kTRUE);
  c3.setConstant(kTRUE);
  d1.setConstant(kTRUE);
  d2.setConstant(kTRUE);
  d3.setConstant(kTRUE);
  e1.setConstant(kTRUE);
  e2.setConstant(kTRUE);
  e3.setConstant(kTRUE);
  f1.setConstant(kTRUE);
  f2.setConstant(kTRUE);
  f3.setConstant(kTRUE);
  f4.setConstant(kTRUE);
  f5.setConstant(kTRUE);
  g1.setConstant(kTRUE);

  TH1D *h1_Fit1;
  TH1D *h1_Fit2;
  TH1D *h1_Fit3;
  TH1D *h1_Fit4;
  TH1D *h1_Fit4Lo0;
  TH1D *h1_Fit4Lo;
  TH1D *h1_Fit4Hi;
  
  TH1D* hFit4Com = new TH1D("hFit4Com","hFit4Com",13,0,13);
  double nnBins[14]={0,1,2,3,4,5,6,7,8,9,10,11,12,13};
  RooBinning myBins(13,nnBins);
  h1_Fit1 = (TH1D*)(model1.createHistogram("h1_Fit1",x,Binning(myBins))); //GenLevel
  h1_Fit2 = (TH1D*)(model2.createHistogram("h1_Fit2",x,Binning(myBins))); //GenLevel
  h1_Fit3 = (TH1D*)(model3.createHistogram("h1_Fit3",x,Binning(myBins))); //GenLevel
  h1_Fit4 = (TH1D*)(model4.createHistogram("h1_Fit4",x,Binning(myBins))); //GenLevel
  
  h1_Fit4Lo0 = (TH1D*)(model4Lo0.createHistogram("h1_Fit4Lo0",x,Binning(myBins))); //GenLevel
  h1_Fit4Lo = (TH1D*)(model4Lo.createHistogram("h1_Fit4Lo",x,Binning(myBins))); //GenLevel
  h1_Fit4Hi = (TH1D*)(model4Hi.createHistogram("h1_Fit4Hi",x,Binning(myBins))); //GenLevel
 
  double temp1;
  double temp2;
  double temp3;
  temp1=0.;
  temp2=0.;
  temp3=0.;
  for( int ipt(1);ipt<=13;ipt++)
  {
    if(ipt<5)
      temp1+=h1_Fit4Lo0->GetBinContent(ipt);
    if(ipt>4 && ipt<9)
      temp2+=h1_Fit4Lo->GetBinContent(ipt);
    if(ipt>8)
      temp3+=h1_Fit4Hi->GetBinContent(ipt);
  }
  //cout<<temp1<<" + "<<temp2<<" + "<<temp3<<" = "<<temp1+temp2+temp3<<endl;
  h1_Fit4Lo0->Scale(tmp1/temp1);
  h1_Fit4Lo->Scale(tmp2/temp2);
  h1_Fit4Hi->Scale(tmp3/temp3);

  for( int ipt(1);ipt<=13;ipt++)
  {
    if(ipt<5)
    {
      hFit4Com->SetBinContent(ipt,h1_Fit4Lo0->GetBinContent(ipt));
      cout<<"Fitted: "<<h1_Fit4Lo0->GetBinContent(ipt)<<"\t Ratio: "<<lData4->GetBinContent(ipt)<<endl;
    }
    if(ipt>4 && ipt<9)
    {
      hFit4Com->SetBinContent(ipt,h1_Fit4Lo->GetBinContent(ipt));
      cout<<"Fitted: "<<h1_Fit4Lo->GetBinContent(ipt)<<"\t Ratio: "<<lData4->GetBinContent(ipt)<<endl;
    }
    if(ipt>8)
    {
      hFit4Com->SetBinContent(ipt,h1_Fit4Hi->GetBinContent(ipt));
      cout<<"Fitted: "<<h1_Fit4Hi->GetBinContent(ipt)<<"\t Ratio: "<<lData4->GetBinContent(ipt)<<endl;
    }
  }
  h1_Fit1->Scale(lData1->Integral()/h1_Fit1->Integral());
  h1_Fit2->Scale(lData2->Integral()/h1_Fit2->Integral());
  h1_Fit3->Scale(lData3->Integral()/h1_Fit3->Integral());
  h1_Fit4->Scale(lData4->Integral()/h1_Fit4->Integral());
  hFit4Com->Scale(lData4->Integral()/hFit4Com->Integral());

  //cout<<"Integral h1_Org: "<<lData1->Integral()<<"  Integral h1_Fit1: "<<h1_Fit1->Integral()<<endl;
  //cout<<"Integral h1_Org: "<<lData2->Integral()<<"  Integral h1_Fit2: "<<h1_Fit2->Integral()<<endl;
  //cout<<"Integral h1_Org: "<<lData3->Integral()<<"  Integral h1_Fit3: "<<h1_Fit3->Integral()<<endl;
  //cout<<"Integral h1_Org: "<<lData4->Integral()<<"  Integral h1_Fit4: "<<h1_Fit4->Integral()<<endl;
  cout<<"Integral h1_Org: "<<lData4->Integral()<<"  Integral h1_Fit4: "<<hFit4Com->Integral()<<endl;
  //cout<<tmp1<<" + "<<tmp2<<" + "<<tmp3<<" = "<<tmp1+tmp2+tmp3<<endl;
  for( int ipt(1);ipt<=13;ipt++)
  {
    //cout<<hData->GetBinContent(ipt)<<endl;
    //hdata->SetBinContent(ipt,hData->GetBinContent(ipt));
    hFit1->SetBinContent(ipt,h1_Fit1->GetBinContent(ipt));
    hFit2->SetBinContent(ipt,h1_Fit2->GetBinContent(ipt));
    hFit3->SetBinContent(ipt,h1_Fit3->GetBinContent(ipt));
    //hFit4->SetBinContent(ipt,h1_Fit4->GetBinContent(ipt));
    hFit4->SetBinContent(ipt,hFit4Com->GetBinContent(ipt));
    hFit1->SetBinError(ipt,lData1->GetBinError(ipt));
    hFit2->SetBinError(ipt,lData2->GetBinError(ipt));
    hFit3->SetBinError(ipt,lData3->GetBinError(ipt));
    hFit4->SetBinError(ipt,lData4->GetBinError(ipt));
    //cout<<lData1->GetBinContent(ipt)<<"\t"<<hFit1->GetBinContent(ipt)<<endl;
    //cout<<lData2->GetBinContent(ipt)<<"\t"<<hFit2->GetBinContent(ipt)<<endl;
    //cout<<lData3->GetBinContent(ipt)<<"\t"<<hFit3->GetBinContent(ipt)<<endl;
    cout<<"Checking: "<<lData4->GetBinContent(ipt)<<"\t"<<hFit4->GetBinContent(ipt)<<endl;
  }

  hFit1->SetLineColor(kRed);
  hFit1->SetMarkerColor(kRed);
  hFit1->Draw("E1");
  lData1->Draw("E1same");
  myCan->SaveAs(resultDir+"/hFit_MuP.png");

  hFit2->SetLineColor(kRed);
  hFit2->SetMarkerColor(kRed);
  hFit2->Draw("E1");
  lData2->Draw("E1same");
  myCan->SaveAs(resultDir+"/hFit_MuM.png");

  hFit3->SetLineColor(kRed);
  hFit3->SetMarkerColor(kRed);
  hFit3->Draw("E1");
  lData3->Draw("E1same");
  myCan->SaveAs(resultDir+"/hFit_ElP.png");
 
  hFit4->SetLineColor(kRed);
  hFit4->SetMarkerColor(kRed);
  hFit4->Draw("E1");
  lData4->Draw("E1same");
  myCan->SaveAs(resultDir+"/hFit_ElM.png");
 
  TFile f_out(resultDir+"/test.root","recreate");
  TH1D *h1_WpT_WpToMN_ratio;
  TH1D *h1_WpT_WmToMN_ratio;
  TH1D *h1_WpT_WpToEN_ratio;
  TH1D *h1_WpT_WmToEN_ratio;
  h1_WpT_WpToMN_ratio = (TH1D*)hFit1->Clone("h1_WpT_WpToMN_ratio");
  h1_WpT_WmToMN_ratio = (TH1D*)hFit2->Clone("h1_WpT_WmToMN_ratio");
  h1_WpT_WpToEN_ratio = (TH1D*)hFit3->Clone("h1_WpT_WpToEN_ratio");
  h1_WpT_WmToEN_ratio = (TH1D*)hFit4->Clone("h1_WpT_WmToEN_ratio");
  
  h1_WpT_WpToMN_ratio ->Write();
  h1_WpT_WmToMN_ratio ->Write();
  h1_WpT_WpToEN_ratio ->Write();
  h1_WpT_WmToEN_ratio ->Write();

/*
  TCanvas *lC0 = new TCanvas("Can","Can",800,800); lC0->cd(); lC0->SetLogy();
  lC0->Divide(1,2,0,0);
  lC0->cd(1)->SetPad(0,0.35,0.95,1.0);
  h1_WpT_WpToMN_ratio = (TH1D*)hFit->Clone("dUnf data");

  TCanvas *lC0 = new TCanvas("Can","Can",800,800); lC0->cd(); lC0->SetLogy();
  lC0->Divide(1,2,0,0);
  lC0->cd(1)->SetPad(0,0.35,0.95,1.0);
  lC0->cd(1)->SetTopMargin(0.1);
  lC0->cd(1)->SetBottomMargin(0.01);
  lC0->cd(1)->SetLeftMargin(0.15);
  lC0->cd(1)->SetRightMargin(0.07);
  lC0->cd(1)->SetTickx(1);
  lC0->cd(1)->SetTicky(1);
  //lC0->SetLogx(1);
  gStyle->SetLineWidth(2.);
  gStyle->SetOptStat(0);
  gStyle->SetHatchesSpacing(0.75);
  gStyle->SetHatchesLineWidth(2);
  //gPad->SetLogx(1);
  //gPad->SetLogy(1);

  hFit->SetLineColor(kRed);
  h1_Org->SetTitle("");
  h1_Org->SetMaximum(1.1*(h1_Org->GetMaximum()));
  h1_Org->Draw("HIST");
  hFit->Draw("HISTSAME");
  
  TLegend *lL =new TLegend(0.6,0.7,0.85,0.85);
  lL->SetFillColor(0); lL->SetBorderSize(0);
  if(unfName == "Det")
    lL->AddEntry(h1_Org,"h1_Truth_Post","l");
  if(unfName == "FSR")
    lL->AddEntry(h1_Org,"h1_Born_BothFid","l");
  lL->AddEntry(hFit,"hFit","l");
  lL->Draw();

  lC0->cd(2)->SetPad(0,0,0.95,0.34);
  lC0->cd(2)->SetTopMargin(0.025);
  lC0->cd(2)->SetBottomMargin(0.3);
  lC0->cd(2)->SetLeftMargin(0.15);
  lC0->cd(2)->SetRightMargin(0.07);
  lC0->cd(2)->SetTickx(1);
  lC0->cd(2)->SetTicky(1);
  //lC0->cd(2)->SetLogx(1);
  drawDifference(h1_Org,hFit,unfName);
  lC0->SaveAs(BaseName+unfName+"/Overlap_Fit.png");
*/
  return 0;
}
