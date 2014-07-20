#include "TStyle.h"
#include "../Utils/const.h"
#include "../Utils/CPlot.hh"
#include "../Utils/MitStyleRemix.hh"
#include "../Utils/Unfolder.h"
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
#include "RooDataHist.h"
#include "RooAddPdf.h"
#include "RooFitResult.h"
#include "RooNLLVar.h"
#include "RooMinuit.h"
#include "RooChi2Var.h"

const int nBins = 14;
//const int nBins = 27;
double WptLogBins[nBins] = {1.0,7.5,12.5,17.5,24,30,40,50,70,110,150,190,250,600};
double WptBins[nBins] = {0.0,7.5,12.5,17.5,24,30,40,50,70,110,150,190,250,600};
//double WptBins[nBins] = {0.0,3.75,7.5,10,12.5,15,17.5,20.75,24,27,30,35,40,45,50,60,70,90,110,130,150,170,190,220,250,425,600};

void drawDifference(TH1* iH0,TH1 *iH1,TString hName) {
  std::string lName = std::string(iH0->GetName());
  //TH1F *lHDiff  = new TH1F((lName+"Diff").c_str(),(lName+"Diff").c_str(),nBins-1,WptLogBins); lHDiff->Sumw2();
  TH1F *lHDiff  = new TH1F((lName+"Diff").c_str(),(lName+"Diff").c_str(),nBins-1,0,13); lHDiff->Sumw2();
  TH1F *lHDiffH = new TH1F((lName+"DiffH").c_str(),(lName+"DiffH").c_str(),iH0->GetNbinsX(),iH0->GetXaxis()->GetXmin(),iH0->GetXaxis()->GetXmax()); lHDiffH->SetLineWidth(1); lHDiffH->SetLineColor(kRed);
  TH1F *lHDiffL = new TH1F((lName+"DiffL").c_str(),(lName+"DiffL").c_str(),iH0->GetNbinsX(),iH0->GetXaxis()->GetXmin(),iH0->GetXaxis()->GetXmax()); lHDiffL->SetLineWidth(1); lHDiffL->SetLineColor(kBlue);
  lHDiff->SetFillColor(kViolet); lHDiff->SetFillStyle(1001); lHDiff->SetLineWidth(1);
  TH1F *lXHDiff1 = new TH1F((lName+"XDiff1").c_str(),(lName+"XDiff1").c_str(),iH0->GetNbinsX(),iH0->GetXaxis()->GetXmin(),iH0->GetXaxis()->GetXmax());
  TH1F *lXHDiff2 = new TH1F((lName+"XDiff2").c_str(),(lName+"XDiff2").c_str(),iH0->GetNbinsX(),iH0->GetXaxis()->GetXmin(),iH0->GetXaxis()->GetXmax());
  int i1 = 0;
  lXHDiff1->SetLineWidth(2); lXHDiff1->SetLineColor(kBlack); lXHDiff1->SetLineStyle(2);
  lXHDiff2->SetLineWidth(2); lXHDiff2->SetLineColor(kRed);
  
  lHDiff->GetYaxis()->SetRangeUser(0,2);
  lHDiff->GetYaxis()->SetTitleOffset(0.6);
  lHDiff->GetYaxis()->SetTitleSize(0.08);
  lHDiff->GetYaxis()->SetLabelSize(0.08);
  lHDiff->GetYaxis()->CenterTitle();
  lHDiff->GetXaxis()->SetTitleOffset(1.2);
  lHDiff->GetXaxis()->SetTitleSize(0.10);
  lHDiff->GetXaxis()->SetLabelSize(0.08);
  lHDiff->GetXaxis()->SetTitle(" W p_{T} ");
  if(hName == "Det")
    //lHDiff->GetYaxis()->SetTitle("TruthPost / hFit");
    lHDiff->GetYaxis()->SetTitle("DetUnf / hFit");
  if(hName == "FSR")
    lHDiff->GetYaxis()->SetTitle("TruthBorn / hFit");
  gStyle->SetOptStat(0);
  
  for(int i0 = 0; i0 < lHDiff->GetNbinsX()+1; i0++) {
    double lXCenter = lHDiff->GetBinCenter(i0);
    double lXVal     = iH0   ->GetBinContent(i0);
    lXHDiff1->SetBinContent(i0, 1.0);
    lXHDiff2->SetBinContent(i0, 1.0);
    while(iH1->GetBinCenter(i1) < lXCenter) {i1++;}
    if(iH1->GetBinContent(i0) > 0) lHDiff->SetBinContent(i0,lXVal/(iH1->GetBinContent(i0)));
    if(iH1->GetBinContent(i0) > 0) lHDiff->SetBinError(i0,iH0->GetBinError(i0)/(iH1->GetBinContent(i0)));
  }
  lHDiff->SetMarkerStyle(kFullCircle); lHDiff->SetLineColor(kBlack); lHDiff->SetMarkerColor(kBlack);
  
  lHDiff->SetTitle("");
  lHDiff->Draw("E1");
  lXHDiff1->Draw("hist sames");
}

int test(TString BaseName,TString unfName)
{
  TFile *f_Data;
  TString resultDir = BaseName+unfName;
  gSystem->mkdir(resultDir,kTRUE);
  char tmpName[30];
  TString tmpTStr;
  
  ofstream Fout;
  Fout.open(resultDir+"/ShapePars.txt");

  cout << "check 1" << endl;
  if(unfName == "Det")
  {
    if(BaseName == "WpToMuNu")
      f_Data = new TFile("Nominal/ResultWpToMuNu/Result_WpToMuNu.root");
      //f_Data = new TFile("MuonLowPU/Muon_WpToMuNu_S8_Unfold.root");
    if(BaseName == "WmToMuNu")
      f_Data = new TFile("Nominal/ResultWmToMuNu/Result_WmToMuNu.root");
      //f_Data = new TFile("MuonLowPU/Muon_WmToMuNu_S8_Unfold.root");
    if(BaseName == "WpToEleNu")
      f_Data = new TFile("Nominal/ResultWpToEleNu/Result_WpToEleNu.root");
      //f_Data = new TFile("ElectronLowPU/Ele_WpToEleNu_S8_Unfold.root");
    if(BaseName == "WmToEleNu")
      f_Data = new TFile("Nominal/ResultWmToEleNu/Result_WmToEleNu.root");
      //f_Data = new TFile("ElectronLowPU/Ele_WmToEleNu_S8_Unfold.root");
  }
  if(unfName == "FSR")
  {
    if(BaseName == "WpToMuNu")
      f_Data = new TFile("Acceptance_WpT/MuonLowPU/Muon_WpToMuNu_S8_Acceptance.root");
    if(BaseName == "WmToMuNu")
      f_Data = new TFile("Acceptance_WpT/MuonLowPU/Muon_WmToMuNu_S8_Acceptance.root");
    if(BaseName == "WpToEleNu")
      f_Data = new TFile("Acceptance_WpT/ElectronLowPU/Ele_WpToEleNu_S8_Acceptance.root");
    if(BaseName == "WmToEleNu")
      f_Data = new TFile("Acceptance_WpT/ElectronLowPU/Ele_WmToEleNu_S8_Acceptance.root");
  }
  CPlot *pltFit;
  TH1D* lData;
  TH1D* hData = new TH1D("hData","hData",13,0,13); //hData->Sumw2();
  TH1D* h1_Org = new TH1D("h1_Org","h1_Org",13,0,13); //hData->Sumw2();
  TH1D* hdata = new TH1D("hdata","hdata",13,0,13); //hData->Sumw2();
  TH1D* hFit = new TH1D("hFit","hFit",13,0,13); //hData->Sumw2();
  //TH1D* hFit = new TH1D("hFit","hFit",26,0,26); //hData->Sumw2();
  RooDataHist* data;

  if(unfName == "Det")
    //lData   = (TH1D*)f_Data->Get("h1_Truth_Post")->Clone();
    lData   = (TH1D*)f_Data->Get("DetUnf")->Clone();
  if(unfName == "FSR")
    lData   = (TH1D*)f_Data->Get("h1_Born_BothFid")->Clone();
  
  for( int ipt(1);ipt<=13;ipt++)
  {
    h1_Org->SetBinContent(ipt,lData->GetBinContent(ipt));
    hData->SetBinContent(ipt,lData->GetBinContent(ipt));
  }
  
  TCanvas *myCan = MakeCanvas("myCan","myCan",900,800);

  //gPad->SetLogy(1);
  hData->Draw("E");
  if(unfName == "Det")
    //myCan->SaveAs(resultDir+"/TruthPostData.png");
    myCan->SaveAs(resultDir+"/DetUnftData.png");
  if(unfName == "FSR")
    myCan->SaveAs(resultDir+"/BornBothData.png");
  RooRealVar x("x","", 0,13);
  //RooRealVar x("x","", 0,26);
  x.setBins(13);
  //x.setBins(26);
  
  data = new RooDataHist("data","data",RooArgSet(x), hData);
  
  RooRealVar coef1("coef1","",-0.5,-1,1);
  RooRealVar coef2("coef2","",0.09,-1,1);
  RooRealVar coef3("coef3","",-0.007,-0.1,0.1);
  RooRealVar coef4("coef4","",-0.0001,-0.01,0.01);
  RooRealVar coef5("coef5","",0.000006,-0.0001,0.0001);
  RooRealVar coef6("coef6","",0.000001,-0.0001,0.0001);
  RooRealVar coef7("coef7","",-0.00000007,-0.00001,0.00001);
  
  RooPolynomial model("model", "", x, RooArgList(coef1,coef2,coef3,coef4,coef5,coef6,coef7));
  //model.fitTo(*data);

  //cout<<"coef1: "<<coef1.getVal()<<endl;
  //cout<<"coef2: "<<coef2.getVal()<<endl;
  //cout<<"coef3: "<<coef3.getVal()<<endl;
  //cout<<"coef4: "<<coef4.getVal()<<endl;
  //cout<<"coef5: "<<coef5.getVal()<<endl;
  //cout<<"coef6: "<<coef6.getVal()<<endl;
  //cout<<"coef7: "<<coef7.getVal()<<endl;
  //
  //RooPlot* xframe = x.frame(Bins(13));
  //data->plotOn(xframe,MarkerStyle(kFullCircle),MarkerSize(0.9),DrawOption("ZP"),DataError(RooAbsData::SumW2));
  //model.plotOn(xframe,LineColor(kRed));
  //
  //tmpTStr = "test";
  //pltFit = new CPlot(tmpTStr,xframe,"","","");
  //pltFit -> setOutDir(resultDir);
  //pltFit -> SetLogy(1);
  //pltFit->Draw(myCan,kTRUE,"png");
  
  if(unfName == "Det"){
    if(BaseName == "WpToMuNu"){
      //coef1.setVal(-4.1706e-01);
      //coef2.setVal(6.7894e-02);
      //coef3.setVal(-2.7165e-03);
      //coef4.setVal(-2.85222e-04);
      //coef5.setVal(3.50040e-06);
      //coef6.setVal(2.99883e-06);
      //coef7.setVal(-1.3911e-07);
	coef1.setVal(-0.543018);
	coef2.setVal(0.127193);
	coef3.setVal(-0.0129207);
	coef4.setVal(0.00031558);
	coef5.setVal(2.85018e-05);
	coef6.setVal(-1.33086e-06);
	coef7.setVal(-3.68072e-09);
    }else if (BaseName == "WmToMuNu" ){
      coef1.setVal(-0.518955);
      coef2.setVal(0.115148);
      coef3.setVal(-0.0103256);
      coef4.setVal(5.46364e-05);
      coef5.setVal(3.7384e-05);
      coef6.setVal(-1.05768e-06);
      coef7.setVal(-2.19119e-08);
      //coef1.setVal(-0.325226);
      //coef2.setVal(0.0146287);
      //coef3.setVal(0.00844696);
      //coef4.setVal(-0.0011372);
      ////coef5.setVal(-1.03282e-05);
      //coef5.setVal(-1.032832e-05);
      //coef6.setVal(7.83967e-06);
      //coef7.setVal(-3.08445e-07);
      //// //coef1.setVal(-4.6374e-01);
      //// coef1.setVal(-4.63768e-01);
      //// //coef2.setVal(9.7803e-02);
      //// coef2.setVal(9.79106e-02);
      //// //coef3.setVal(-9.5995e-03);
      //// coef3.setVal(-9.59820e-03);
      //// //coef4.setVal(3.9896e-04);
      //// coef4.setVal(3.98975e-04);
      //// //coef5.setVal(-1.8605e-05);//last bins!
      //// coef5.setVal(-1.8607e-05);//last bins!
      //// //coef6.setVal(2.2713e-06);
      //// coef6.setVal(2.27136e-06);
      //// //coef7.setVal(-9.3573e-08);
      //// coef7.setVal(-9.3573e-08);
      //coef1.setVal(-4.4248e-01);
      //coef2.setVal(8.7448e-02);
      //coef3.setVal(-7.1594e-03);
      //coef4.setVal(6.9337e-05);
      //coef5.setVal(6.41285e-06);
      //coef6.setVal(1.3077e-06);
      //coef7.setVal(-7.9426e-08);
    }else if (BaseName == "WpToEleNu" ){
      coef1.setVal(-0.504036);
      coef2.setVal(0.110245);
      coef3.setVal(-0.00948632);
      coef4.setVal(-3.71943e-05);
      coef5.setVal(4.30409e-05);
      coef6.setVal(-1.20676e-06);
      coef7.setVal(-2.13879e-08);
      //coef1.setVal(-4.3815e-01);
      //coef2.setVal(8.05755e-02);
      //coef3.setVal(-4.78938e-03);
      //coef4.setVal(-2.9325e-04);
      //coef5.setVal(3.5416e-05);
      //coef6.setVal(9.2214e-08);
      //coef7.setVal(-5.7839e-08);
    }else if (BaseName == "WmToEleNu" ){
      coef1.setVal(-0.488772);
      coef2.setVal(0.100056);
      coef3.setVal(-0.00787322);
      coef4.setVal(9.87969e-05);
      coef5.setVal(-1.20393e-05);
      coef6.setVal(3.49515e-06);
      coef7.setVal(-1.51345e-07);
      //coef1.setVal(-4.1232e-01);
      //coef2.setVal(7.2013e-02);
      //coef3.setVal(-4.51275e-03);
      //coef4.setVal(-1.12285e-05);
      ////coef5.setVal(-1.6691e-05);
      //coef5.setVal(-1.66915e-05);//last bins!
      //coef6.setVal(3.7033e-06);
      //coef7.setVal(-1.4767e-07);
    }
  }else  if(unfName == "FSR"){
    if(BaseName == "WpToMuNu"){
      coef1.setVal(-5.02558e-01);
      coef2.setVal(1.148785e-01);
      coef3.setVal(-1.232578e-02);
      coef4.setVal(4.896755e-04);
      coef5.setVal(2.5960e-06); 
      coef6.setVal(-2.176955e-08);
      coef7.setVal(-2.63165e-08);
      //coef1.setVal(-4.1706e-01);
      //coef2.setVal(6.7894e-02);
      //coef3.setVal(-2.7165e-03);
      //coef4.setVal(-2.85235e-04);
      //coef5.setVal(3.5007e-06);
      //coef6.setVal(2.9989e-06);
      //coef7.setVal(-1.3911e-07);
    }else if (BaseName == "WmToMuNu" ){
      coef1.setVal(-0.478203);
      coef2.setVal(0.103273);
      //coef3.setVal(-0.00982012);
      //coef3.setVal(-0.00982007);
      //coef3.setVal(-0.00982000);
      //coef3.setVal(-0.00981950);
      coef3.setVal(-0.00981935);
      //coef4.setVal(0.000215055);
      coef4.setVal(0.000215075);
      coef5.setVal(1.58682e-05);
      coef6.setVal(-1.02518e-07);
      coef7.setVal(-3.52327e-08);
      //coef1.setVal(-4.4411e-01);
      //coef2.setVal(8.7710e-02);
      //coef3.setVal(-7.1650e-03);
      //coef4.setVal(6.8833e-05);
      //coef5.setVal(6.4128e-06);
      //coef6.setVal(1.3072e-06);
      //coef7.setVal(-7.9325e-08);
    }else if (BaseName == "WpToEleNu" ){
      coef1.setVal(-5.0254e-01);
      coef2.setVal(1.1346e-01);
      coef3.setVal(-1.1593e-02);
      coef4.setVal(3.2782e-04);
      coef5.setVal(2.1126e-05); 
      coef6.setVal(-1.0940e-06);
      coef7.setVal(-1.6268e-09);
    }else if (BaseName == "WmToEleNu" ){
      coef1.setVal(-4.8415e-01);
      coef2.setVal(1.0771e-01);
      coef3.setVal(-1.1535e-02);
      coef4.setVal(5.6357e-04);
      coef5.setVal(-2.1005e-05); 
      coef6.setVal(1.8266e-06);
      coef7.setVal(-7.4698e-08);
    }
  }
  //coef1.setConstant(kTRUE);
  //coef2.setConstant(kTRUE);
  //coef3.setConstant(kTRUE);
  //coef4.setConstant(kTRUE);
  //coef5.setConstant(kTRUE);
  //coef6.setConstant(kTRUE);
  //coef7.setConstant(kTRUE);
  
  //Construct binned likelihood
  RooNLLVar nll("nll","nll",model,*data);
  
  //Start Minuit session on NLL
  RooMinuit m(nll);
  m.migrad();
  m.hesse();
  RooFitResult* r1 = m.save();
  
  RooPlot* xframe = x.frame(Bins(13));
  //RooPlot* xframe = x.frame(Bins(26));
  data->plotOn(xframe,MarkerStyle(kFullCircle),MarkerSize(0.9),DrawOption("ZP"),DataError(RooAbsData::SumW2));
  model.plotOn(xframe,LineColor(kRed));
  
  tmpTStr = "BinnedLikeliHoodFit";
  pltFit = new CPlot(tmpTStr,xframe,"","","");
  pltFit -> setOutDir(resultDir);
  //pltFit -> SetLogy(1);
  pltFit->Draw(myCan,kTRUE,"png");
  
  // Construct Chi2
  RooChi2Var chi2("chi2","chi2",model,*data);
  
  RooPlot* xxframe = x.frame(Bins(13));
  //RooPlot* xxframe = x.frame(Bins(26));
  data->plotOn(xxframe,MarkerStyle(kFullCircle),MarkerSize(0.9),DrawOption("ZP"),DataError(RooAbsData::SumW2));
  model.plotOn(xxframe,LineColor(kBlue));
  
  tmpTStr = "Chi2Fit";
  pltFit = new CPlot(tmpTStr,xxframe,"","","");
  pltFit -> setOutDir(resultDir);
  //pltFit -> SetLogy(1);
  pltFit->Draw(myCan,kTRUE,"png");
  
  //Start Minuit session on Chi2
  RooMinuit m2(chi2);
  m2.migrad();
  m2.hesse();
  RooFitResult* r2 = m2.save();
  
  // Print results 
  cout << "result of binned likelihood fit" << endl;
  r1->Print("v");
  cout << "result of chi2 fit" << endl;
  r2->Print("v") ;
  
  //Chi^2/NDF
  char ndftext[50];
  sprintf(ndftext,"#chi^{2}/ndf = %.4f",xframe->chiSquare()/(xframe->GetNbinsX()-1.0));

  tmpTStr = "Fit";
  pltFit = new CPlot(tmpTStr,xframe,"","W p_{T}[Bins]","Events");
  //pltFit = new CPlot(tmpTStr,xframe,"","","");
  pltFit->setOutDir(resultDir);
  pltFit->AddTextBox(ndftext,0.6,0.84,0.91,0.88,0,kBlack,-1);
  //pltFit -> SetLogy(1);
  //pltFit->SetLogx();
  pltFit->Draw(myCan,kTRUE,"png");

  Fout<<"coef1: "<<coef1.getVal()<<endl;
  Fout<<"coef2: "<<coef2.getVal()<<endl;
  Fout<<"coef3: "<<coef3.getVal()<<endl;
  Fout<<"coef4: "<<coef4.getVal()<<endl;
  Fout<<"coef5: "<<coef5.getVal()<<endl;
  Fout<<"coef6: "<<coef6.getVal()<<endl;
  Fout<<"coef7: "<<coef7.getVal()<<endl;
  
  cout<<"coef1.setVal("<<coef1.getVal()<<");"<<endl; 
  cout<<"coef2.setVal("<<coef2.getVal()<<");"<<endl;
  cout<<"coef3.setVal("<<coef3.getVal()<<");"<<endl;
  cout<<"coef4.setVal("<<coef4.getVal()<<");"<<endl;
  cout<<"coef5.setVal("<<coef5.getVal()<<");"<<endl;
  cout<<"coef6.setVal("<<coef6.getVal()<<");"<<endl;
  cout<<"coef7.setVal("<<coef7.getVal()<<");"<<endl;
  TH1D *h1_Fit;

  double nnBins[14]={0,1,2,3,4,5,6,7,8,9,10,11,12,13};
  //double nnBins[27]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26};
  //double nnBins[27]={0,0.5,1,1.5,2,2.5,3,3.5,4,4.5,5,5.5,6,6.5,7,7.5,8,8.5,9,9.5,10,10.5,11,11.5,12,12.5,13};
  RooBinning myBins(13,nnBins);
  //RooBinning myBins(26,nnBins);
  h1_Fit = (TH1D*)(model.createHistogram("h1_Fit",x,Binning(myBins))); //GenLevel
  //h1_Fit->Scale(hData->Integral()/h1_Fit->Integral());
  //for(int i(1);i<27;i++)
  //{
  //  cout <<"h1_Fit : " <<h1_Fit->GetBinContent(i)<<endl;
  //}
  TFile f_out(resultDir+"/Fit.root","recreate");
  h1_Fit->Write();
 
  for( int ipt(1);ipt<=13;ipt++)
  {
    cout<<h1_Fit->GetBinContent(ipt)<<endl;
  }
  cout<<"Integral h1_Org: "<<h1_Org->Integral()<<"  Integral h1_Fit: "<<h1_Fit->Integral()<<endl;
  h1_Fit->Scale(hData->Integral()/h1_Fit->Integral());
  for( int ipt(1);ipt<=13;ipt++)
  //for( int ipt(1);ipt<=26;ipt++)
  {
    cout<<hData->GetBinContent(ipt)<<endl;
    hdata->SetBinContent(ipt,hData->GetBinContent(ipt));
    hFit->SetBinContent(ipt,h1_Fit->GetBinContent(ipt));
    cout<<h1_Org->GetBinContent(ipt)<<"\t"<<hFit->GetBinContent(ipt)<<endl;
  }

  TCanvas *lC0 = new TCanvas("Can","Can",800,800); lC0->cd(); lC0->SetLogy();
  lC0->Divide(1,2,0,0);
  lC0->cd(1)->SetPad(0,0.35,0.95,1.0);
  lC0->cd(1)->SetTopMargin(0.1);
  lC0->cd(1)->SetBottomMargin(0.01);
  lC0->cd(1)->SetLeftMargin(0.15);
  lC0->cd(1)->SetRightMargin(0.07);
  lC0->cd(1)->SetTickx(1);
  lC0->cd(1)->SetTicky(1);
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
    //lL->AddEntry(h1_Org,"h1_Truth_Post","l");
    lL->AddEntry(h1_Org,"DetUnf","l");
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
  //lC0->cd(2)->SetLogy(1);
  drawDifference(h1_Org,hFit,unfName);
  lC0->SaveAs(BaseName+unfName+"/Overlap_Fit.png");

  return 0;
}
