//================================================
//
// Perform fit to extract W->munu signal
//
//  * outputs plots and fit results summary
// from ksung fitWm.C
//________________________________________________

#if !defined(__CINT__) || defined(__MAKECINT__)
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
#include "Math/LorentzVector.h"           // 4-vector class

#include "../Utils/MyTools.hh"	          // various helper functions
#include "../Utils/CPlot.hh"	          // helper class for plots
#include "../Utils/MitStyleRemix.hh"      // style settings for drawing
#include "../Utils/WModels.hh"            // definitions of PDFs for fitting
#include "../Utils/RecoilCorrector.hh"    // class to handle recoil corrections for MET

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
#endif
//From WMuNeu.h
#include "../Utils/const.h"
typedef ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiM4D<double> > LorentzVector;

//=== FUNCTION DECLARATIONS ==============================

// make data-fit difference plots
TH1D* makeDiffHist(TH1D* hData, TH1D* hFit, const TString name);

// print correlations of fitted parameters
void printCorrelations(ostream& os, RooFitResult *res);

// print chi2 test and KS test results
void printChi2AndKSResults(ostream& os, 
                           const Double_t chi2prob, const Double_t chi2ndf, 
			   const Double_t ksprob, const Double_t ksprobpe);

// make webpage
void makeHTML(const TString outDir);
void makeBinHTML(const TString outDir, Int_t i);

//=== MAIN MACRO ================================================ 

void fitWEleMetRayleighSimult(const TString  outputDir,   // output directory
           const Double_t lumi,        // integrated luminosity (/fb)
	   const Double_t nsigma=0     // vary MET corrections by n-sigmas (nsigma=0 means nominal correction)
)
{
  gBenchmark->Start("fitWEleMetRayleighSimult");

  //------------------
  // Settings 
  //==================   
  
  // MET histogram binning and range
  //const Int_t    NBINS   = 50;
  //const Double_t METMAX  = 100;
  
  const Double_t PT_CUT  = 25;
  const Double_t ETA_CUT = 2.1;

  // file format for output plots
  const TString format("png"); 
   /************************** 
  // recoil correction
  RecoilCorrector recoilCorr("../Recoil/ZmmData/fits.root");//, (!) uncomment to perform corrections to recoil from W-MC/Z-MC
                             //"../Recoil/WmpMC/fits.root",
			     //"../Recoil/WmmMC/fits.root",
			     //"../Recoil/ZmmMC/fits.root");
   
  // NNLO boson pT k-factors
  TFile nnloCorrFile("/data/blue/ksung/EWKAna/8TeV/Utils/Ratio.root");
  TH1D *hNNLOCorr = (TH1D*)nnloCorrFile.Get("RpT_B");
  ***********************/
  
  //
  // input ntuple file names
  //
  enum { eData, eWpMuNu, eEWK, eWmMuNu };  // data type enum
  //enum { eData, eWmunu, eEWK, eAntiData, eAntiWmunu, eAntiEWK };  // data type enum
  vector<TString> fnamev;
  vector<Int_t>   typev;

  fnamev.push_back("../EventSelection/ElectronLowPU/Ele_RD_LowPU_Analysis.root"); typev.push_back(eData);
  fnamev.push_back("../EventSelection/ElectronLowPU/Ele_DYToEE_S8_Analysis.root"); typev.push_back(eEWK);
  fnamev.push_back("../EventSelection/ElectronLowPU/Ele_DYToTauTau_S8_Analysis.root"); typev.push_back(eEWK);
  fnamev.push_back("../EventSelection/ElectronLowPU/Ele_TTJets_S8_Analysis.root"); typev.push_back(eEWK);
  fnamev.push_back("../EventSelection/ElectronLowPU/Ele_WToTauNu_S8_Analysis.root"); typev.push_back(eEWK);
  fnamev.push_back("../EventSelection/ElectronLowPU/Ele_WpToEleNu_S8_RecoilCorr.root"); typev.push_back(eWpMuNu);
  fnamev.push_back("../EventSelection/ElectronLowPU/Ele_WmToEleNu_S8_RecoilCorr.root"); typev.push_back(eWmMuNu);
//// Before Recoil
//  fnamev.push_back("../EventSelection/ElectronLowPU/Ele_WpToEleNu_S8_Analysis.root"); typev.push_back(eWpMuNu);
//  fnamev.push_back("../EventSelection/ElectronLowPU/Ele_WmToEleNu_S8_Analysis.root"); typev.push_back(eWmMuNu);
  

  //-------------------------
  // Main analysis code 
  //=========================  
  
  // Create output directory
  gSystem->mkdir(outputDir,kTRUE);
  CPlot::sOutDir = outputDir;  
  
  //
  // Declare MET histograms
  // 0 is for total
  double WptBins[12]={0,8,23,38,55,75,95,120,145,175,210,300};
//  double WptBins[18]={0,2.5,5,7.5,10,12.5,15,17.5,20,30,40,50,70,90,150,190,250,600};
  //double WptBins[NWptBinPlus]={0,2.5,5,7.5,10,12.5,15,17.5,20,30,40,50,70,90,150,190,250,600};
  TH1D *hdataWpt;
  TH1D *hdataWPpt;
  TH1D *hdataWMpt;
  TH1D *hSigWpt = new TH1D("hSigWpt","hSigWpt",11,WptBins);hSigWpt->Sumw2();
  TH1D *hEWKWpt = new TH1D("hEWKWpt","hEWKWpt",11,WptBins);hEWKWpt->Sumw2();
  TH1D *hQCDWpt = new TH1D("hQCDWpt","hQCDWpt",11,WptBins);hQCDWpt->Sumw2();
  TH1D *hSigWPpt = new TH1D("hSigWPpt","hSigWPpt",11,WptBins);hSigWPpt->Sumw2();
  TH1D *hEWKWPpt = new TH1D("hEWKWPpt","hEWKWPpt",11,WptBins);hEWKWPpt->Sumw2();
  TH1D *hQCDWPpt = new TH1D("hQCDWPpt","hQCDWPpt",11,WptBins);hQCDWPpt->Sumw2();
  TH1D *hSigWMpt = new TH1D("hSigWMpt","hSigWMpt",11,WptBins);hSigWMpt->Sumw2();
  TH1D *hEWKWMpt = new TH1D("hEWKWMpt","hEWKWMpt",11,WptBins);hEWKWMpt->Sumw2();
  TH1D *hQCDWMpt = new TH1D("hQCDWMpt","hQCDWMpt",11,WptBins);hQCDWMpt->Sumw2();
  TH1D *hDataMet  [NWptBinPlus]  ;
  TH1D *hDataMetm [NWptBinPlus]  ;
  TH1D *hDataMetp [NWptBinPlus]  ; 
  TH1D *hWmunuMet [NWptBinPlus]  ; 
  TH1D *hWmunuMetp[NWptBinPlus]  ;
  TH1D *hWmunuMetm[NWptBinPlus]  ;
  TH1D *hEWKMet   [NWptBinPlus]  ; 
  TH1D *hEWKMetp  [NWptBinPlus]  ; 
  TH1D *hEWKMetm  [NWptBinPlus]  ; 
                                              
  TH1D *hAntiDataMet  [NWptBinPlus]   ;
  TH1D *hAntiDataMetm [NWptBinPlus]  ;
  TH1D *hAntiDataMetp [NWptBinPlus]  ;
  TH1D *hAntiWmunuMet [NWptBinPlus]  ;
  TH1D *hAntiWmunuMetp[NWptBinPlus] ;
  TH1D *hAntiWmunuMetm[NWptBinPlus] ;
  TH1D *hAntiEWKMet   [NWptBinPlus]    ;
  TH1D *hAntiEWKMetp  [NWptBinPlus]   ;
  TH1D *hAntiEWKMetm  [NWptBinPlus]   ;
  Double_t METMAX;
  //
  // Declare variables to read in ntuple
  //
  UInt_t  runNum, lumiSec, evtNum;
  UInt_t  npv, npu;
  Float_t genVPt, genVPhi;
  Float_t scale1fb;
  Float_t met, metPhi, sumEt, mt, u1, u2;
  Int_t   q;
  LorentzVector *lep=0;
  Float_t pfChIso, pfGamIso, pfNeuIso;
    
  TFile *infile=0;
  //TTree *intree=0;

  //
  // Loop over files
  //
  cout<<"Looping Files ------------------------"<<endl;
  bool first_EWK_file(true);
  char histName[30],histName_org[30];
  for(UInt_t ifile=0; ifile<fnamev.size(); ifile++) {
    
    // Read input file and get the TTrees
    cout << "Processing " << fnamev[ifile] << "..." << endl;
    infile = new TFile(fnamev[ifile]);	  assert(infile);
    //intree = (TTree*)infile->Get("Events"); assert(intree);
    if(typev[ifile]==eData)
    {
      //hTemp =(TH1D*)infile->FindObject("h1_W_Neu_pt_all");
      //TString histoName = Form("hData_%s",name.c_str());
      sprintf(histName,"hdataWpt");
      sprintf(histName_org,"h1_W_pt");
      hdataWpt = (TH1D*)infile->Get(histName_org)->Clone(histName);
      hdataWpt->Sumw2();
      sprintf(histName,"hdataWPpt");
      sprintf(histName_org,"h1_Wp_pt");
      hdataWPpt = (TH1D*)infile->Get(histName_org)->Clone(histName);
      hdataWPpt->Sumw2();
      sprintf(histName,"hdataWMpt");
      sprintf(histName_org,"h1_Wm_pt");
      hdataWMpt = (TH1D*)infile->Get(histName_org)->Clone(histName);
      hdataWMpt->Sumw2();
      for(int ipt(0);ipt<NWptBinPlus;ipt++)
      {
	sprintf(histName,"hDataMet_%d",ipt);
	sprintf(histName_org,"h1_W_Neu_pt_%d",ipt);
	hDataMet[ipt] =(TH1D*)infile->Get(histName_org)->Clone(histName);hDataMet[ipt]->Sumw2();
	sprintf(histName,"hDataMetm_%d",ipt);
	sprintf(histName_org,"h1_Wm_Neu_pt_%d",ipt);
	hDataMetm[ipt]=(TH1D*)infile->Get(histName_org)->Clone(histName);hDataMetm[ipt]->Sumw2();
	sprintf(histName,"hDataMetp_%d",ipt);
	sprintf(histName_org,"h1_Wp_Neu_pt_%d",ipt);
	hDataMetp[ipt]=(TH1D*)infile->Get(histName_org)->Clone(histName);hDataMetp[ipt]->Sumw2();

	sprintf(histName,"hAntiDataMet_%d",ipt);
	sprintf(histName_org,"h1_WSide_Neu_pt_%d",ipt);
	hAntiDataMet[ipt] =(TH1D*)infile->Get(histName_org)->Clone(histName);hAntiDataMet[ipt]->Sumw2();
	sprintf(histName,"hAntiDataMetm_%d",ipt);
	sprintf(histName_org,"h1_WmSide_Neu_pt_%d",ipt);
	hAntiDataMetm[ipt]=(TH1D*)infile->Get(histName_org)->Clone(histName);hAntiDataMetm[ipt]->Sumw2();
	sprintf(histName,"hAntiDataMetp_%d",ipt);
	sprintf(histName_org,"h1_WpSide_Neu_pt_%d",ipt);
	hAntiDataMetp[ipt]=(TH1D*)infile->Get(histName_org)->Clone(histName);hAntiDataMetp[ipt]->Sumw2();
      }
    }
    if(typev[ifile]==eWpMuNu)
    {
      for( int ipt(0);ipt<NWptBinPlus;ipt++)
      {
	sprintf(histName,"hWmunuMetp_%d",ipt);
	sprintf(histName_org,"h1_Wp_Neu_pt_%d",ipt);
	hWmunuMetp[ipt]=(TH1D*)infile->Get(histName_org)->Clone(histName);hWmunuMetp[ipt]->Sumw2();
	sprintf(histName,"hAntiWmunuMetp_%d",ipt);
	sprintf(histName_org,"h1_WpSide_Neu_pt_%d",ipt);
	hAntiWmunuMetp[ipt]=(TH1D*)infile->Get(histName_org)->Clone(histName);hAntiWmunuMetp[ipt]->Sumw2();
      }
    }
    if(typev[ifile]==eWmMuNu)
    {
      for( int ipt(0);ipt<NWptBinPlus;ipt++)
      {
	sprintf(histName,"hWmunuMetm_%d",ipt);
	sprintf(histName_org,"h1_Wm_Neu_pt_%d",ipt);
	hWmunuMetm[ipt]=(TH1D*)infile->Get(histName_org)->Clone(histName);hWmunuMetm[ipt]->Sumw2();
	sprintf(histName,"hAntiWmunuMetm_%d",ipt);
	sprintf(histName_org,"h1_WmSide_Neu_pt_%d",ipt);
	hAntiWmunuMetm[ipt]=(TH1D*)infile->Get(histName_org)->Clone(histName);hAntiWmunuMetm[ipt]->Sumw2();
      }
    }
    if(typev[ifile]==eEWK)
    {
      if(first_EWK_file){
	for( int ipt(0); ipt<NWptBinPlus; ipt++)
	{
	  sprintf(histName,"hEWKMet_%d",ipt);
	  sprintf(histName_org,"h1_W_Neu_pt_%d",ipt);
	  hEWKMet[ipt] =(TH1D*)infile->Get(histName_org)->Clone(histName);hEWKMet[ipt]->Sumw2();
	  sprintf(histName,"hEWKMetm_%d",ipt);
	  sprintf(histName_org,"h1_Wm_Neu_pt_%d",ipt);
	  hEWKMetm[ipt]=(TH1D*)infile->Get(histName_org)->Clone(histName);hEWKMetm[ipt]->Sumw2();
	  sprintf(histName,"hEWKMetp_%d",ipt);
	  sprintf(histName_org,"h1_Wp_Neu_pt_%d",ipt);
	  hEWKMetp[ipt]=(TH1D*)infile->Get(histName_org)->Clone(histName);hEWKMetp[ipt]->Sumw2();

	  sprintf(histName,"hAntiEWKMet_%d",ipt);
	  sprintf(histName_org,"h1_WSide_Neu_pt_%d",ipt);
	  hAntiEWKMet[ipt] =(TH1D*)infile->Get(histName_org)->Clone(histName);hAntiEWKMet[ipt]->Sumw2();
	  sprintf(histName,"hAntiEWKMetm_%d",ipt);
	  sprintf(histName_org,"h1_WmSide_Neu_pt_%d",ipt);
	  hAntiEWKMetm[ipt]=(TH1D*)infile->Get(histName_org)->Clone(histName);hAntiEWKMetm[ipt]->Sumw2();
	  sprintf(histName,"hAntiEWKMetp_%d",ipt);
	  sprintf(histName_org,"h1_WpSide_Neu_pt_%d",ipt);
	  hAntiEWKMetp[ipt]=(TH1D*)infile->Get(histName_org)->Clone(histName);hAntiEWKMetp[ipt]->Sumw2();
	}
      }else{
	for( int ipt(0); ipt<NWptBinPlus; ipt++)
	{
	  sprintf(histName_org,"h1_W_Neu_pt_%d",ipt);
	  hEWKMet[ipt] ->Add((TH1D*)infile->Get(histName_org)->Clone(histName));
	  sprintf(histName_org,"h1_Wm_Neu_pt_%d",ipt);
	  hEWKMetm[ipt]->Add((TH1D*)infile->Get(histName_org)->Clone(histName));
	  sprintf(histName_org,"h1_Wp_Neu_pt_%d",ipt);
	  hEWKMetp[ipt]->Add((TH1D*)infile->Get(histName_org)->Clone(histName));

	  sprintf(histName_org,"h1_WSide_Neu_pt_%d",ipt);
	  hAntiEWKMet[ipt] ->Add((TH1D*)infile->Get(histName_org)->Clone(histName));
	  sprintf(histName_org,"h1_WmSide_Neu_pt_%d",ipt);
	  hAntiEWKMetm[ipt]->Add((TH1D*)infile->Get(histName_org)->Clone(histName));
	  sprintf(histName_org,"h1_WpSide_Neu_pt_%d",ipt);
	  hAntiEWKMetp[ipt]->Add((TH1D*)infile->Get(histName_org)->Clone(histName));
	}
      }
      first_EWK_file=false;
    }
  }
  for(int ipt(0);ipt<NWptBinPlus;ipt++)
  {
    sprintf(histName,"hWmunuMet_%d",ipt);
    hWmunuMet[ipt] = (TH1D*)hWmunuMetp[ipt]->Clone(histName);
    hWmunuMet[ipt]->Add(hWmunuMetm[ipt]);
    sprintf(histName,"hAntiWmunuMet_%d",ipt);
    hAntiWmunuMet[ipt] = (TH1D*)hAntiWmunuMetp[ipt]->Clone(histName);
    hAntiWmunuMet[ipt]->Add(hAntiWmunuMetm[ipt]);
  }

  //delete infile;
  //infile=0;// intree=0;   
  //
  // Declare fit parameters for signal and background yields
  // Note: W signal and EWK+top PDFs are constrained to the ratio described in MC
  //

  //MET fitting =====================
  RooRealVar* nSig;
  RooRealVar* nQCD;
  RooRealVar  cewk("cewk","cewk",0.1,0,5) ;
  RooFormulaVar* nEWK;
  RooRealVar* nAntiSig;
  RooRealVar* nAntiQCD;
  RooRealVar  dewk("dewk","dewk",0.1,0,5) ;
  RooFormulaVar* nAntiEWK;
  RooRealVar* nSigp;
  RooRealVar* nQCDp;
  RooRealVar  cewkp("cewkp","cewkp",0.1,0,5) ;
  RooFormulaVar* nEWKp;
  RooRealVar* nAntiSigp;
  RooRealVar* nAntiQCDp;
  RooRealVar dewkp("dewkp","dewkp",0.1,0,5) ;
  RooFormulaVar* nAntiEWKp;
  RooRealVar* nSigm;
  RooRealVar* nQCDm;
  RooRealVar cewkm("cewkm","cewkm",0.1,0,5) ;
  RooFormulaVar* nEWKm;
  RooRealVar* nAntiSigm;
  RooRealVar* nAntiQCDm;
  RooRealVar dewkm("dewkm","dewkm",0.1,0,5) ;
  RooFormulaVar* nAntiEWKm;
  RooDataHist* wmunuMet ;RooHistPdf*pdfWm ;
  RooDataHist* wmunuMetp;RooHistPdf*pdfWmp;
  RooDataHist* wmunuMetm;RooHistPdf*pdfWmm; 
  RooDataHist* ewkMet ; RooHistPdf* pdfEWK ;
  RooDataHist* ewkMetp; RooHistPdf* pdfEWKp; 
  RooDataHist* ewkMetm; RooHistPdf* pdfEWKm; 
  RooAddPdf* pdfMet ;
  RooAddPdf* pdfMetp;
  RooAddPdf* pdfMetm;
  RooDataHist* awmunuMet ; RooHistPdf* apdfWm ;
  RooDataHist* awmunuMetp; RooHistPdf* apdfWmp;
  RooDataHist* awmunuMetm; RooHistPdf* apdfWmm; 
  RooDataHist* aewkMet ; RooHistPdf* apdfEWK ;
  RooDataHist* aewkMetp; RooHistPdf* apdfEWKp; 
  RooDataHist* aewkMetm; RooHistPdf* apdfEWKm; 
  RooAddPdf* apdfMet ;
  RooAddPdf* apdfMetp;
  RooAddPdf* apdfMetm;
  RooCategory rooCat("rooCat","rooCat");
  rooCat.defineType("Select");
  rooCat.defineType("Anti");
  RooSimultaneous* pdfTotal;
  RooSimultaneous* pdfTotalp;
  RooSimultaneous* pdfTotalm;
  RooSimultaneous* apdfTotal;
  RooSimultaneous* apdfTotalp;
  RooSimultaneous* apdfTotalm;
  RooDataHist* dataMet ; 
  RooDataHist* antiMet ; 
  RooDataHist* dataTotal;
  RooFitResult *fitRes;
  RooDataHist* dataMetp  ;
  RooDataHist* antiMetp  ;
  RooDataHist* dataTotalp;
  RooFitResult *fitResp;
  RooDataHist* dataMetm;
  RooDataHist* antiMetm;
  RooDataHist* dataTotalm;
  RooFitResult *fitResm;
  TH1D *hPdfMet;TH1D *hMetDiff;
  TH1D *hPdfMetp;TH1D *hMetpDiff;
  TH1D *hPdfMetm;TH1D *hMetmDiff;
  TH1D *hPdfAntiMet;TH1D *hAntiMetDiff;
  TH1D *hPdfAntiMetp;TH1D *hAntiMetpDiff;
  TH1D *hPdfAntiMetm;TH1D *hAntiMetmDiff;
  CPepeModel1* qcd ;
  CPepeModel1* qcdp;
  CPepeModel1* qcdm;
  CPepeModel1* aqcd ;
  CPepeModel1* aqcdp;
  CPepeModel1* aqcdm;

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
  gStyle->SetTitleOffset(1.100,"Y");
  TGaxis::SetMaxDigits(3);
  char ylabel[100];  // string buffer for y-axis label
  // label for lumi
  char lumitext[100];
  if(lumi<0.1) sprintf(lumitext,"%.1f pb^{-1}  at  #sqrt{s} = 8 TeV",lumi*1000.);
  else         sprintf(lumitext,"%.2f fb^{-1}  at  #sqrt{s} = 8 TeV",lumi);
  
  // plot colors
  Int_t linecolorW   = kOrange-3;
  Int_t fillcolorW   = kOrange-2;
  Int_t linecolorEWK = kOrange+10;
  Int_t fillcolorEWK = kOrange+7;
  Int_t linecolorQCD = kViolet+2;
  Int_t fillcolorQCD = kViolet-5;
  Int_t ratioColor   = kGray+2;

  //
  // Dummy histograms for TLegend
  // (I can't figure out how to properly pass RooFit objects...)
  //
  TH1D *hDummyData = new TH1D("hDummyData","",0,0,10);
  hDummyData->SetMarkerStyle(kFullCircle);
  hDummyData->SetMarkerSize(0.9);
  
  TH1D *hDummyW = new TH1D("hDummyW","",0,0,10);
  hDummyW->SetLineColor(linecolorW);
  hDummyW->SetFillColor(fillcolorW);
  hDummyW->SetFillStyle(1001);
  
  TH1D *hDummyEWK = new TH1D("hDummyEWK","",0,0,10);
  hDummyEWK->SetLineColor(linecolorEWK);
  hDummyEWK->SetFillColor(fillcolorEWK);
  hDummyEWK->SetFillStyle(1001);
  
  TH1D *hDummyQCD = new TH1D("hDummyQCD","",0,0,10);
  hDummyQCD->SetLineColor(linecolorQCD);
  hDummyQCD->SetFillColor(fillcolorQCD);
  hDummyQCD->SetFillStyle(1001);
  //=========================
  
  RooPlot *wmframe;
  CPlot *plotMet;
  CPlot *plotMetDiff;

  RooPlot *awmframe;
  CPlot *plotAntiMet;
  CPlot *plotAntiMetDiff;

  RooPlot *wmpframe;
  CPlot *plotMetp;
  CPlot *plotMetpDiff;
  
  RooPlot *awmpframe;
  CPlot *plotAntiMetp;
  CPlot *plotAntiMetpDiff;

  RooPlot *wmmframe;
  CPlot *plotMetm;
  CPlot *plotMetmDiff;

  RooPlot *awmmframe;
  CPlot *plotAntiMetm;
  CPlot *plotAntiMetmDiff;

  ofstream txtfile;
  char txtfname[100];    
  ios_base::fmtflags flags;
  Double_t chi2prob, chi2ndf;
  Double_t ksprob, ksprobpe;

  Int_t NBINS;

  //Loop for each Wpt bins==============
  // 0 is the total
  for( int ipt(0);ipt<NWptBinPlus;ipt++)
  {
    nSig = new RooRealVar("nSig","nSig",0.7*(hDataMet[ipt]->Integral()),0,hDataMet[ipt]->Integral());
    nQCD = new RooRealVar("nQCD","nQCD",0.03*(hDataMet[ipt]->Integral()),0,hDataMet[ipt]->Integral());
    nQCDp = new RooRealVar("nQCDp","nQCDp",0.03*(hDataMetp[ipt]->Integral()),0,hDataMetp[ipt]->Integral());
    nQCDm = new RooRealVar("nQCDm","nQCDm",0.03*(hDataMetm[ipt]->Integral()),0,hDataMetm[ipt]->Integral());
//    nQCD = new RooRealVar("nQCD","nQCD",0.3*(hDataMet[ipt]->Integral()),0,hDataMet[ipt]->Integral());
//    nQCDp = new RooRealVar("nQCDp","nQCDp",0.3*(hDataMetp[ipt]->Integral()),0,hDataMetp[ipt]->Integral());
//    nQCDm = new RooRealVar("nQCDm","nQCDm",0.3*(hDataMetm[ipt]->Integral()),0,hDataMetm[ipt]->Integral());
    cewk.setVal(hEWKMet[ipt]->Integral()/hWmunuMet[ipt]->Integral());
    cewk.setConstant(kTRUE);
    nEWK = new RooFormulaVar("nEWK","nEWK","cewk*nSig",RooArgList(*nSig,cewk));
    nAntiSig = new RooRealVar("nAntiSig","nAntiSig",hAntiDataMet[ipt]->Integral(),0,hAntiDataMet[ipt]->Integral());
    //nAntiSig = new RooRealVar("nAntiSig","nAntiSig",0.05*(hAntiDataMet[ipt]->Integral()),0,hAntiDataMet[ipt]->Integral());
    nAntiQCD = new RooRealVar("nAntiQCD","nAntiQCD",0.9*(hAntiDataMet[ipt]->Integral()),0,hAntiDataMet[ipt]->Integral());
    //nAntiQCD = new RooRealVar("nAntiQCD","nAntiQCD",0.9*(hDataMet[ipt]->Integral()),0,hDataMet[ipt]->Integral());
    dewk.setVal(hAntiEWKMet[ipt]->Integral()/hAntiWmunuMet[ipt]->Integral());
    dewk.setConstant(kTRUE);
    nAntiEWK = new RooFormulaVar("nAntiEWK","nAntiEWK","dewk*nAntiSig",RooArgList(*nAntiSig,dewk));
 
    nSigp = new RooRealVar("nSigp","nSigp",0.7*(hDataMetp[ipt]->Integral()),0,hDataMetp[ipt]->Integral());
    cewkp.setVal(hEWKMetp[ipt]->Integral()/hWmunuMetp[ipt]->Integral());
    cewkp.setConstant(kTRUE);
    nEWKp = new RooFormulaVar("nEWKp","nEWKp","cewkp*nSigp",RooArgList(*nSigp,cewkp));
    nAntiSigp = new RooRealVar("nAntiSigp","nAntiSigp",hAntiDataMetp[ipt]->Integral(),0,hAntiDataMetp[ipt]->Integral());
    //nAntiSigp = new RooRealVar("nAntiSigp","nAntiSigp",0.05*(hAntiDataMetp[ipt]->Integral()),0,hAntiDataMetp[ipt]->Integral());
    nAntiQCDp = new RooRealVar("nAntiQCDp","nAntiQCDp",0.9*(hAntiDataMetp[ipt]->Integral()),0,hAntiDataMetp[ipt]->Integral());
    dewkp.setVal(hAntiEWKMetp[ipt]->Integral()/hAntiWmunuMetp[ipt]->Integral());
    dewkp.setConstant(kTRUE);
    nAntiEWKp = new RooFormulaVar("nAntiEWKp","nAntiEWKp","dewkp*nAntiSigp",RooArgList(*nAntiSigp,dewkp));
  
    nSigm = new RooRealVar("nSigm","nSigm",0.7*(hDataMetm[ipt]->Integral()),0,hDataMetm[ipt]->Integral());
    cewkm.setVal(hEWKMetm[ipt]->Integral()/hWmunuMetm[ipt]->Integral());
    cewkm.setConstant(kTRUE);
    nEWKm = new RooFormulaVar("nEWKm","nEWKm","cewkm*nSigm",RooArgList(*nSigm,cewkm));  
    nAntiSigm = new RooRealVar("nAntiSigm","nAntiSigm",hAntiDataMetm[ipt]->Integral(),0,hAntiDataMetm[ipt]->Integral());
    //nAntiSigm = new RooRealVar("nAntiSigm","nAntiSigm",0.05*(hAntiDataMetm[ipt]->Integral()),0,hAntiDataMetm[ipt]->Integral());
    nAntiQCDm = new RooRealVar("nAntiQCDm","nAntiQCDm",0.9*(hAntiDataMetm[ipt]->Integral()),0,hAntiDataMetm[ipt]->Integral());
    dewkm.setVal(hAntiEWKMetm[ipt]->Integral()/hAntiWmunuMetm[ipt]->Integral());
    dewkm.setConstant(kTRUE);
    nAntiEWKm = new RooFormulaVar("nAntiEWKm","nAntiEWKm","dewkm*nAntiSigm",RooArgList(*nAntiSigm,dewkm));
  //
  // Construct PDFs for fitting
  //

  if ( ipt < NBIN_PT_DIVIDER_1and2 ) {
  METMAX = METMAX_1;
  NBINS   = NBINS_1;
  } else if ( ipt < NBIN_PT_DIVIDER_2and3 ) {
  METMAX = METMAX_2;
  NBINS   = NBINS_2;
  } else {
  METMAX = METMAX_3;
  NBINS  = NBINS_3;
  }

  RooRealVar pfmet("pfmet","pfmet",0,METMAX);
  pfmet.setBins(NBINS);

  // Signal PDFs
  wmunuMet  =new RooDataHist("wmunuMET", "wmunuMET", RooArgSet(pfmet),hWmunuMet[ipt]); pdfWm =new RooHistPdf ("wm", "wm", pfmet,*wmunuMet, 1);
  wmunuMetp =new RooDataHist("wmunuMETp","wmunuMETp",RooArgSet(pfmet),hWmunuMetp[ipt]);pdfWmp=new RooHistPdf ("wmp","wmp",pfmet,*wmunuMetp,1);
  wmunuMetm =new RooDataHist("wmunuMETm","wmunuMETm",RooArgSet(pfmet),hWmunuMetm[ipt]);pdfWmm=new RooHistPdf ("wmm","wmm",pfmet,*wmunuMetm,1); 
  // EWK+top PDFs
  ewkMet =new RooDataHist("ewkMET", "ewkMET", RooArgSet(pfmet),hEWKMet[ipt]); pdfEWK =new RooHistPdf ("ewk", "ewk", pfmet,*ewkMet, 1);
  ewkMetp=new RooDataHist("ewkMETp","ewkMETp",RooArgSet(pfmet),hEWKMetp[ipt]);pdfEWKp=new RooHistPdf ("ewkp","ewkp",pfmet,*ewkMetp,1); 
  ewkMetm=new RooDataHist("ewkMETm","ewkMETm",RooArgSet(pfmet),hEWKMetm[ipt]);pdfEWKm=new RooHistPdf ("ewkm","ewkm",pfmet,*ewkMetm,1); 
  
  // Anti-Signal PDFs
  awmunuMet =new RooDataHist("awmunuMET", "awmunuMET", RooArgSet(pfmet),hAntiWmunuMet[ipt]) ;
  awmunuMetp=new RooDataHist("awmunuMETp","awmunuMETp",RooArgSet(pfmet),hAntiWmunuMetp[ipt]);
  awmunuMetm=new RooDataHist("awmunuMETm","awmunuMETm",RooArgSet(pfmet),hAntiWmunuMetm[ipt]);
  apdfWm =new RooHistPdf("awm", "awm", pfmet,*awmunuMet, 1);
  apdfWmp=new RooHistPdf("awmp","awmp",pfmet,*awmunuMetp,1);
  apdfWmm=new RooHistPdf("awmm","awmm",pfmet,*awmunuMetm,1); 
  // Anti-EWK+top PDFs
  aewkMet =new RooDataHist("aewkMET", "aewkMET", RooArgSet(pfmet),hAntiEWKMet[ipt]);  
  aewkMetp=new RooDataHist("aewkMETp","aewkMETp",RooArgSet(pfmet),hAntiEWKMetp[ipt]);  
  aewkMetm=new RooDataHist("aewkMETm","aewkMETm",RooArgSet(pfmet),hAntiEWKMetm[ipt]);  
  apdfEWK =new RooHistPdf("aewk", "aewk", pfmet,*aewkMet, 1);
  apdfEWKp=new RooHistPdf("aewkp","aewkp",pfmet,*aewkMetp,1);
  apdfEWKm=new RooHistPdf("aewkm","aewkm",pfmet,*aewkMetm,1);

  dataMet  =new RooDataHist("dataMet", "dataMet", RooArgSet(pfmet), hDataMet[ipt]);
  antiMet  =new RooDataHist("antiMet", "antiMet", RooArgSet(pfmet), hAntiDataMet[ipt]);
  dataTotal=new RooDataHist("dataTotal","dataTotal", RooArgList(pfmet), Index(rooCat),
                        Import("Select", *dataMet),
                        Import("Anti",   *antiMet));
  dataMetp  =new RooDataHist("dataMetp", "dataMetp", RooArgSet(pfmet), hDataMetp[ipt]);
  antiMetp  =new RooDataHist("antiMetp", "antiMetp", RooArgSet(pfmet), hAntiDataMetp[ipt]);
  dataTotalp=new RooDataHist("dataTotalp","dataTotalp", RooArgList(pfmet), Index(rooCat),
                         Import("Select", *dataMetp),
                         Import("Anti",   *antiMetp));
  dataMetm  =new RooDataHist("dataMetm", "dataMetm", RooArgSet(pfmet), hDataMetm[ipt]);
  antiMetm  =new RooDataHist("antiMetm", "antiMetm", RooArgSet(pfmet), hAntiDataMetm[ipt]);
  dataTotalm=new RooDataHist("dataTotalm","dataTotalm", RooArgList(pfmet), Index(rooCat),
                         Import("Select", *dataMetm),
                         Import("Anti",   *antiMetm));
  if ( ipt < 8) {
  // QCD Pdfs
  qcd =new CPepeModel1("qcd",pfmet);
  qcdp=new CPepeModel1("qcdp",pfmet);
  qcdm=new CPepeModel1("qcdm",pfmet);

  aqcd =new CPepeModel1("aqcd",pfmet, qcd->a1);
  aqcdp=new CPepeModel1("aqcdp",pfmet,qcdp->a1);
  aqcdm=new CPepeModel1("aqcdm",pfmet,qcdm->a1);
  }else{
  aqcd->sigma->getValV();
  aqcd->sigma->setConstant(kTRUE);
  aqcd->a1->getValV();
  aqcd->a1->setConstant(kTRUE);
  aqcdp->sigma->getValV();
  aqcdp->sigma->setConstant(kTRUE);
  aqcdp->a1->getValV();
  aqcdp->a1->setConstant(kTRUE);
  aqcdm->sigma->getValV();
  aqcdm->sigma->setConstant(kTRUE);
  aqcdm->a1->getValV();
  aqcdm->a1->setConstant(kTRUE);

  qcd =new CPepeModel1("qcd",pfmet);
  qcd->sigma->setVal(aqcd->sigma->getValV());
  qcd->sigma->setConstant(kTRUE);
  qcd->a1->setVal(aqcd->a1->getValV());
  qcd->a1->setConstant(kTRUE);
  qcdp =new CPepeModel1("qcdp",pfmet);
  qcdp->sigma->setVal(aqcdp->sigma->getValV());
  qcdp->sigma->setConstant(kTRUE);
  qcdp->a1->setVal(aqcdp->a1->getValV());
  qcdp->a1->setConstant(kTRUE);
  qcdm =new CPepeModel1("qcdm",pfmet);
  qcdm->sigma->setVal(aqcdm->sigma->getValV());
  qcdm->sigma->setConstant(kTRUE);
  qcdm->a1->setVal(aqcdm->a1->getValV());
  qcdm->a1->setConstant(kTRUE);
  }
  // Signal + Background PDFs
  pdfMet =new RooAddPdf("pdfMet", "pdfMet", RooArgList(*pdfWm, *pdfEWK, *(qcd->model)), RooArgList(*nSig, *nEWK, *nQCD));  
  pdfMetp=new RooAddPdf("pdfMetp","pdfMetp",RooArgList(*pdfWmp,*pdfEWKp,*(qcdp->model)),RooArgList(*nSigp,*nEWKp,*nQCDp));
  pdfMetm=new RooAddPdf("pdfMetm","pdfMetm",RooArgList(*pdfWmm,*pdfEWKm,*(qcdm->model)),RooArgList(*nSigm,*nEWKm,*nQCDm));

  // Anti-selection PDFs
  apdfMet =new RooAddPdf("apdfMet", "apdfMet", RooArgList(*apdfWm,*apdfEWK,*(aqcd->model)),   RooArgList(*nAntiSig,*nAntiEWK,*nAntiQCD));  
  apdfMetp=new RooAddPdf("apdfMetp","apdfMetp",RooArgList(*apdfWmp,*apdfEWKp,*(aqcdp->model)),RooArgList(*nAntiSigp,*nAntiEWKp,*nAntiQCDp));
  apdfMetm=new RooAddPdf("apdfMetm","apdfMetm",RooArgList(*apdfWmm,*apdfEWKm,*(aqcdm->model)),RooArgList(*nAntiSigm,*nAntiEWKm,*nAntiQCDm));
  
  // PDF for simultaneous fit
  pdfTotal= new RooSimultaneous("pdfTotal","pdfTotal",rooCat);
  pdfTotal->addPdf(*pdfMet, "Select");
  pdfTotal->addPdf(*apdfMet,"Anti");
  
  pdfTotalp= new RooSimultaneous("pdfTotalp","pdfTotalp",rooCat);
  pdfTotalp->addPdf(*pdfMetp, "Select");
  pdfTotalp->addPdf(*apdfMetp,"Anti");
  
  pdfTotalm=new RooSimultaneous("pdfTotalm","pdfTotalm",rooCat);
  pdfTotalm->addPdf(*pdfMetm, "Select");
  pdfTotalm->addPdf(*apdfMetm,"Anti");
  //
  // Perform fits
  //
  if ( ipt < 10 ) {
  fitRes  = pdfTotal ->fitTo(*dataTotal,Extended(),Minos(kTRUE),Save(kTRUE));
  fitResp = pdfTotalp->fitTo(*dataTotalp,Extended(),Minos(kTRUE),Save(kTRUE));
  fitResm = pdfTotalm->fitTo(*dataTotalm,Extended(),Minos(kTRUE),Save(kTRUE));
  }else{
  fitRes  = pdfMet ->fitTo(*dataMet,Extended(),Minos(kTRUE),Save(kTRUE));
  fitResp = pdfMetp->fitTo(*dataMetp,Extended(),Minos(kTRUE),Save(kTRUE));
  fitResm = pdfMetm->fitTo(*dataMetm,Extended(),Minos(kTRUE),Save(kTRUE));
  }
  //
  // Use histogram version of fitted PDFs to make ratio plots
  // (Will also use PDF histograms later for Chi^2 and KS tests)
  //
  hPdfMet = (TH1D*)(pdfMet->createHistogram("hPdfMet", pfmet));
  hPdfMet->Scale((nSig->getVal()+nEWK->getVal()+nQCD->getVal())/hPdfMet->Integral());
  hMetDiff = makeDiffHist(hDataMet[ipt],hPdfMet,"hMetDiff");
  hMetDiff->SetMarkerStyle(kFullCircle);
  hMetDiff->SetMarkerSize(0.9);
   
  hPdfMetp = (TH1D*)(pdfMetp->createHistogram("hPdfMetp", pfmet));
  hPdfMetp->Scale((nSigp->getVal()+nEWKp->getVal()+nQCDp->getVal())/hPdfMetp->Integral());
  hMetpDiff = makeDiffHist(hDataMetp[ipt],hPdfMetp,"hMetpDiff");
  hMetpDiff->SetMarkerStyle(kFullCircle);
  hMetpDiff->SetMarkerSize(0.9);
    
  hPdfMetm = (TH1D*)(pdfMetm->createHistogram("hPdfMetm", pfmet));
  hPdfMetm->Scale((nSigm->getVal()+nEWKm->getVal()+nQCDm->getVal())/hPdfMetm->Integral());
  hMetmDiff = makeDiffHist(hDataMetm[ipt],hPdfMetm,"hMetmDiff");
  hMetmDiff->SetMarkerStyle(kFullCircle); 
  hMetmDiff->SetMarkerSize(0.9);
   
  hPdfAntiMet = (TH1D*)(apdfMet->createHistogram("hPdfAntiMet", pfmet));
  hPdfAntiMet->Scale((nAntiSig->getVal()+nAntiEWK->getVal()+nAntiQCD->getVal())/hPdfAntiMet->Integral());
  hAntiMetDiff = makeDiffHist(hAntiDataMet[ipt],hPdfAntiMet,"hAntiMetDiff");
  hAntiMetDiff->SetMarkerStyle(kFullCircle);
  hAntiMetDiff->SetMarkerSize(0.9);
   
  hPdfAntiMetp = (TH1D*)(apdfMetp->createHistogram("hPdfAntiMetp", pfmet));
  hPdfAntiMetp->Scale((nAntiSigp->getVal()+nAntiEWKp->getVal()+nAntiQCDp->getVal())/hPdfAntiMetp->Integral());
  hAntiMetpDiff = makeDiffHist(hAntiDataMetp[ipt],hPdfAntiMetp,"hAntiMetpDiff");
  hAntiMetpDiff->SetMarkerStyle(kFullCircle);
  hAntiMetpDiff->SetMarkerSize(0.9);
    
  hPdfAntiMetm = (TH1D*)(apdfMetm->createHistogram("hPdfAntiMetm", pfmet));
  hPdfAntiMetm->Scale((nAntiSigm->getVal()+nAntiEWKm->getVal()+nAntiQCDm->getVal())/hPdfAntiMetm->Integral());
  hAntiMetmDiff = makeDiffHist(hAntiDataMetm[ipt],hPdfAntiMetm,"hAntiMetmDiff");
  hAntiMetmDiff->SetMarkerStyle(kFullCircle); 
  hAntiMetmDiff->SetMarkerSize(0.9);
   
  //-------------------------------------------------
  // Make plots 
  //=================================================  
  //
  // W MET plot
  //
  wmframe = pfmet.frame(Bins(NBINS)); 
  wmframe->GetYaxis()->SetNdivisions(505);
  dataMet->plotOn(wmframe,MarkerStyle(kFullCircle),MarkerSize(0.9),DrawOption("ZP"));
  pdfMet->plotOn(wmframe,FillColor(fillcolorW),DrawOption("F"));
  pdfMet->plotOn(wmframe,LineColor(linecolorW));
  pdfMet->plotOn(wmframe,Components(RooArgSet(*pdfEWK,*(qcd->model))),FillColor(fillcolorEWK),DrawOption("F"));
  pdfMet->plotOn(wmframe,Components(RooArgSet(*pdfEWK,*(qcd->model))),LineColor(linecolorEWK));
  pdfMet->plotOn(wmframe,Components(RooArgSet(*(qcd->model))),FillColor(fillcolorQCD),DrawOption("F"));
  pdfMet->plotOn(wmframe,Components(RooArgSet(*(qcd->model))),LineColor(linecolorQCD));
  pdfMet->plotOn(wmframe,Components(RooArgSet(*pdfWm)),LineColor(linecolorW),LineStyle(2));
  dataMet->plotOn(wmframe,MarkerStyle(kFullCircle),MarkerSize(0.9),DrawOption("ZP"));  

  sprintf(ylabel,"Events / %.1f GeV",hDataMet[ipt]->GetBinWidth(1));
  sprintf(histName,"fitMet_%d",ipt);
  plotMet=new CPlot(histName,wmframe,"","",ylabel);
  plotMet->setOutDir(CPlot::sOutDir);
  //plotMet=new CPlot("fitMet",wmframe,"","",ylabel);
  plotMet->SetLegend(0.68,0.57,0.93,0.77);
  plotMet->GetLegend()->AddEntry(hDummyData,"data","PL");
  plotMet->GetLegend()->AddEntry(hDummyW,"W#rightarrow e#nu","F");
  plotMet->GetLegend()->AddEntry(hDummyEWK,"EWK+t#bar{t}","F");
  plotMet->GetLegend()->AddEntry(hDummyQCD,"QCD","F");
  plotMet->AddTextBox(lumitext,0.55,0.80,0.90,0.86,0);
  plotMet->AddTextBox("CMS Preliminary",0.63,0.92,0.95,0.99,0);
  plotMet->SetYRange(0.1,1.1*(hDataMet[ipt]->GetMaximum()));
  plotMet->Draw(c,kFALSE,format,1);

  plotMetDiff=new CPlot(histName,"","#slash{E}_{T} [GeV]","#chi");
  plotMetDiff->setOutDir(CPlot::sOutDir);
  plotMetDiff->AddHist1D(hMetDiff,"EX0",ratioColor);
  plotMetDiff->SetYRange(-8,8);
  plotMetDiff->AddLine(0, 0,METMAX, 0,kBlack,1);
  plotMetDiff->AddLine(0, 5,METMAX, 5,kBlack,3);
  plotMetDiff->AddLine(0,-5,METMAX,-5,kBlack,3);
  plotMetDiff->Draw(c,kTRUE,format,2);
  
  sprintf(histName,"fitMetLog_%d",ipt);
  plotMet->SetName(histName);
  plotMet->SetLogy();
  plotMet->SetYRange(1e-3*(hDataMet[ipt]->GetMaximum()),10*(hDataMet[ipt]->GetMaximum()));
  plotMet->Draw(c,kTRUE,format,1);

  if ( ipt < 10 ){
  awmframe = pfmet.frame(Bins(NBINS));    
  antiMet->plotOn(awmframe,MarkerStyle(kFullCircle),MarkerSize(0.9),DrawOption("ZP"));
  apdfMet->plotOn(awmframe,FillColor(fillcolorW),DrawOption("F"));
  apdfMet->plotOn(awmframe,LineColor(linecolorW));
  apdfMet->plotOn(awmframe,Components(RooArgSet(*apdfEWK,*(aqcd->model))),FillColor(fillcolorEWK),DrawOption("F"));
  apdfMet->plotOn(awmframe,Components(RooArgSet(*apdfEWK,*(aqcd->model))),LineColor(linecolorEWK));
  apdfMet->plotOn(awmframe,Components(RooArgSet(*(aqcd->model))),FillColor(fillcolorQCD),DrawOption("F"));
  apdfMet->plotOn(awmframe,Components(RooArgSet(*(aqcd->model))),LineColor(linecolorQCD));
  apdfMet->plotOn(awmframe,Components(RooArgSet(*apdfWm)),LineColor(linecolorW),LineStyle(2));
  antiMet->plotOn(awmframe,MarkerStyle(kFullCircle),MarkerSize(0.9),DrawOption("ZP"));  
  
  sprintf(ylabel,"Events / %.1f GeV",hAntiDataMet[ipt]->GetBinWidth(1));
  sprintf(histName,"fitAntiMet_%d",ipt);
  plotAntiMet=new CPlot (histName,awmframe,"","",ylabel);
  plotAntiMet->setOutDir(CPlot::sOutDir);
  plotAntiMet->SetLegend(0.68,0.57,0.93,0.77);
  plotAntiMet->GetLegend()->AddEntry(hDummyData,"data","PL");
  plotAntiMet->GetLegend()->AddEntry(hDummyW,"W#rightarrow e#nu","F");
  plotAntiMet->GetLegend()->AddEntry(hDummyEWK,"EWK+t#bar{t}","F");
  plotAntiMet->GetLegend()->AddEntry(hDummyQCD,"QCD","F");
  plotAntiMet->AddTextBox(lumitext,0.55,0.80,0.90,0.86,0);
  plotAntiMet->AddTextBox("CMS Preliminary",0.63,0.92,0.95,0.99,0);
  plotAntiMet->SetYRange(0.1,1.1*(hAntiDataMet[ipt]->GetMaximum())); 
  plotAntiMet->Draw(c,kFALSE,format,1);

  plotAntiMetDiff=new CPlot(histName,"","#slash{E}_{T} [GeV]","#chi");
  plotAntiMetDiff->setOutDir(CPlot::sOutDir);
  plotAntiMetDiff->AddHist1D(hAntiMetDiff,"EX0",ratioColor);
  plotAntiMetDiff->SetYRange(-8,8);
  plotAntiMetDiff->AddLine(0, 0,METMAX, 0,kBlack,1);
  plotAntiMetDiff->AddLine(0, 5,METMAX, 5,kBlack,3);
  plotAntiMetDiff->AddLine(0,-5,METMAX,-5,kBlack,3);
  plotAntiMetDiff->Draw(c,kTRUE,format,2);
  
  sprintf(histName,"fitAntiMetLog_%d",ipt);
  plotAntiMet->SetName(histName);
  plotAntiMet->SetLogy();
  plotAntiMet->SetYRange(1e-3*(hAntiDataMet[ipt]->GetMaximum()),10*(hAntiDataMet[ipt]->GetMaximum()));
  plotAntiMet->Draw(c,kTRUE,format,1);}
  //
  // W+ MET plot
  //
  wmpframe = pfmet.frame(Bins(NBINS));
  wmpframe->GetYaxis()->SetNdivisions(505);
  dataMetp->plotOn(wmpframe,MarkerStyle(kFullCircle),MarkerSize(0.9),DrawOption("ZP"));
  pdfMetp->plotOn(wmpframe,FillColor(fillcolorW),DrawOption("F"));
  pdfMetp->plotOn(wmpframe,LineColor(linecolorW));
  pdfMetp->plotOn(wmpframe,Components(RooArgSet(*pdfEWKp,*(qcdp->model))),FillColor(fillcolorEWK),DrawOption("F"));
  pdfMetp->plotOn(wmpframe,Components(RooArgSet(*pdfEWKp,*(qcdp->model))),LineColor(linecolorEWK));
  pdfMetp->plotOn(wmpframe,Components(RooArgSet(*(qcdp->model))),FillColor(fillcolorQCD),DrawOption("F"));
  pdfMetp->plotOn(wmpframe,Components(RooArgSet(*(qcdp->model))),LineColor(linecolorQCD));
  pdfMetp->plotOn(wmpframe,Components(RooArgSet(*pdfWmp)),LineColor(linecolorW),LineStyle(2));
  dataMetp->plotOn(wmpframe,MarkerStyle(kFullCircle),MarkerSize(0.9),DrawOption("ZP"));  
  
  sprintf(ylabel,"Events / %.1f GeV",hDataMetp[ipt]->GetBinWidth(1));
  sprintf(histName,"fitMetP_%d",ipt);
  plotMetp=new CPlot (histName,wmpframe,"","",ylabel);
  plotMetp->setOutDir(CPlot::sOutDir);
  plotMetp->SetLegend(0.68,0.57,0.93,0.77);
  plotMetp->GetLegend()->AddEntry(hDummyData,"data","PL");
  plotMetp->GetLegend()->AddEntry(hDummyW,"W^{+}#rightarrow e^{+}#nu","F");
  plotMetp->GetLegend()->AddEntry(hDummyEWK,"EWK+t#bar{t}","F");
  plotMetp->GetLegend()->AddEntry(hDummyQCD,"QCD","F");
  plotMetp->AddTextBox(lumitext,0.55,0.80,0.90,0.86,0);
  plotMetp->AddTextBox("CMS Preliminary",0.63,0.92,0.95,0.99,0);
  plotMetp->SetYRange(0.1,1.1*(hDataMetp[ipt]->GetMaximum()));
  //plotMetp->SetYRange(0.1,4100);
  plotMetp->Draw(c,kFALSE,format,1);

  plotMetpDiff=new CPlot (histName,"","#slash{E}_{T} [GeV]","#chi");
  plotMetpDiff->setOutDir(CPlot::sOutDir);
  plotMetpDiff->AddHist1D(hMetpDiff,"EX0",ratioColor);
  plotMetpDiff->SetYRange(-8,8);
  plotMetpDiff->AddLine(0, 0,METMAX, 0,kBlack,1);
  plotMetpDiff->AddLine(0, 5,METMAX, 5,kBlack,3);
  plotMetpDiff->AddLine(0,-5,METMAX,-5,kBlack,3);
  plotMetpDiff->Draw(c,kTRUE,format,2);
  
  sprintf(histName,"fitMetPLog_%d",ipt);
  plotMetp->SetName(histName);
  plotMetp->SetLogy();
  plotMetp->SetYRange(1e-3*(hDataMetp[ipt]->GetMaximum()),10*(hDataMetp[ipt]->GetMaximum()));
  plotMetp->Draw(c,kTRUE,format,1);

  if ( ipt < 10 ){
  awmpframe = pfmet.frame(Bins(NBINS));    
  antiMetp->plotOn(awmpframe,MarkerStyle(kFullCircle),MarkerSize(0.9),DrawOption("ZP"));
  apdfMetp->plotOn(awmpframe,FillColor(fillcolorW),DrawOption("F"));
  apdfMetp->plotOn(awmpframe,LineColor(linecolorW));

  apdfMetp->plotOn(awmpframe,Components(RooArgSet(*apdfEWKp,*(aqcdp->model))),FillColor(fillcolorEWK),DrawOption("F"));
  apdfMetp->plotOn(awmpframe,Components(RooArgSet(*apdfEWKp,*(aqcdp->model))),LineColor(linecolorEWK));
  apdfMetp->plotOn(awmpframe,Components(RooArgSet(*(aqcdp->model))),FillColor(fillcolorQCD),DrawOption("F"));
  apdfMetp->plotOn(awmpframe,Components(RooArgSet(*(aqcdp->model))),LineColor(linecolorQCD));
  apdfMetp->plotOn(awmpframe,Components(RooArgSet(*apdfWmp)),LineColor(linecolorW),LineStyle(2));
  antiMetp->plotOn(awmpframe,MarkerStyle(kFullCircle),MarkerSize(0.9),DrawOption("ZP"));  
  
  sprintf(ylabel,"Events / %.1f GeV",hAntiDataMetp[ipt]->GetBinWidth(1));
  sprintf(histName,"fitAntiMetP_%d",ipt);
  plotAntiMetp=new CPlot (histName,awmpframe,"","",ylabel);
  plotAntiMetp->setOutDir(CPlot::sOutDir);
  plotAntiMetp->SetLegend(0.68,0.57,0.93,0.77);
  plotAntiMetp->GetLegend()->AddEntry(hDummyData,"data","PL");
  plotAntiMetp->GetLegend()->AddEntry(hDummyW,"W^{+}#rightarrow e^{+}#nu","F");
  plotAntiMetp->GetLegend()->AddEntry(hDummyEWK,"EWK+t#bar{t}","F");
  plotAntiMetp->GetLegend()->AddEntry(hDummyQCD,"QCD","F");
  plotAntiMetp->AddTextBox(lumitext,0.55,0.80,0.90,0.86,0);
  plotAntiMetp->AddTextBox("CMS Preliminary",0.63,0.92,0.95,0.99,0);
  plotAntiMetp->SetYRange(0.1,1.1*(hAntiDataMetp[ipt]->GetMaximum()));
//plotAntiMetp->SetYRange(0.1,1500);
  plotAntiMetp->Draw(c,kFALSE,format,1);

  plotAntiMetpDiff=new CPlot(histName,"","#slash{E}_{T} [GeV]","#chi");
  plotAntiMetpDiff->setOutDir(CPlot::sOutDir);
  plotAntiMetpDiff->AddHist1D(hAntiMetpDiff,"EX0",ratioColor);
  plotAntiMetpDiff->SetYRange(-8,8);
  plotAntiMetpDiff->AddLine(0, 0,METMAX, 0,kBlack,1);
  plotAntiMetpDiff->AddLine(0, 5,METMAX, 5,kBlack,3);
  plotAntiMetpDiff->AddLine(0,-5,METMAX,-5,kBlack,3);
  plotAntiMetpDiff->Draw(c,kTRUE,format,2);
  
  sprintf(histName,"fitAntiMetPLog_%d",ipt);
  plotAntiMetp->SetName(histName);
  plotAntiMetp->SetLogy();
  plotAntiMetp->SetYRange(1e-3*(hAntiDataMetp[ipt]->GetMaximum()),10*(hAntiDataMetp[ipt]->GetMaximum()));
  plotAntiMetp->Draw(c,kTRUE,format,1);}
  //
  // W- MET plot
  //

  wmmframe = pfmet.frame(Bins(NBINS));
  wmmframe->GetYaxis()->SetNdivisions(505);
  dataMetm->plotOn(wmmframe,MarkerStyle(kFullCircle),MarkerSize(0.9),DrawOption("ZP"));
  pdfMetm->plotOn(wmmframe,FillColor(fillcolorW),DrawOption("F"));
  pdfMetm->plotOn(wmmframe,LineColor(linecolorW));
  pdfMetm->plotOn(wmmframe,Components(RooArgSet(*pdfEWKm,*(qcdm->model))),FillColor(fillcolorEWK),DrawOption("F"));
  pdfMetm->plotOn(wmmframe,Components(RooArgSet(*pdfEWKm,*(qcdm->model))),LineColor(linecolorEWK));
  pdfMetm->plotOn(wmmframe,Components(RooArgSet(*(qcdm->model))),FillColor(fillcolorQCD),DrawOption("F"));
  pdfMetm->plotOn(wmmframe,Components(RooArgSet(*(qcdm->model))),LineColor(linecolorQCD));
  pdfMetm->plotOn(wmmframe,Components(RooArgSet(*pdfWmm)),LineColor(linecolorW),LineStyle(2));
  dataMetm->plotOn(wmmframe,MarkerStyle(kFullCircle),MarkerSize(0.9),DrawOption("ZP"));
  
  sprintf(ylabel,"Events / %.1f GeV",hDataMetm[ipt]->GetBinWidth(1));
  sprintf(histName,"fitMetM_%d",ipt);
  plotMetm=new CPlot(histName,wmmframe,"","",ylabel);
  plotMetm->setOutDir(CPlot::sOutDir);
  plotMetm->SetLegend(0.68,0.57,0.93,0.77);
  plotMetm->GetLegend()->AddEntry(hDummyData,"data","PL");
  plotMetm->GetLegend()->AddEntry(hDummyW,"W^{-}#rightarrow e^{-}#bar{#nu}","F");
  plotMetm->GetLegend()->AddEntry(hDummyEWK,"EWK+t#bar{t}","F");
  plotMetm->GetLegend()->AddEntry(hDummyQCD,"QCD","F");
  plotMetm->AddTextBox(lumitext,0.55,0.80,0.90,0.86,0);
  plotMetm->AddTextBox("CMS Preliminary",0.63,0.92,0.95,0.99,0);
  plotMetm->SetYRange(0.1,1.1*(hDataMetm[ipt]->GetMaximum()));
//plotMetm->SetYRange(0.1,4100);
  plotMetm->Draw(c,kFALSE,format,1);

  plotMetmDiff=new CPlot(histName,"","#slash{E}_{T} [GeV]","#chi");
  plotMetmDiff->setOutDir(CPlot::sOutDir);
  plotMetmDiff->AddHist1D(hMetmDiff,"EX0",ratioColor);
  plotMetmDiff->SetYRange(-8,8);
  plotMetmDiff->AddLine(0, 0,METMAX, 0,kBlack,1);
  plotMetmDiff->AddLine(0, 5,METMAX, 5,kBlack,3);
  plotMetmDiff->AddLine(0,-5,METMAX,-5,kBlack,3);
  plotMetmDiff->Draw(c,kTRUE,format,2);
  
  sprintf(histName,"fitMetMLog_%d",ipt);
  plotMetm->SetName(histName);
  plotMetm->SetLogy();
  plotMetm->SetYRange(1e-3*(hDataMetm[ipt]->GetMaximum()),10*(hDataMetm[ipt]->GetMaximum()));
  plotMetm->Draw(c,kTRUE,format,1);

  if ( ipt < 10 ){
  awmmframe = pfmet.frame(Bins(NBINS)); 
  antiMetm->plotOn(awmmframe,MarkerStyle(kFullCircle),MarkerSize(0.9),DrawOption("ZP"));
  apdfMetm->plotOn(awmmframe,FillColor(fillcolorW),DrawOption("F"));
  apdfMetm->plotOn(awmmframe,LineColor(linecolorW));
  apdfMetm->plotOn(awmmframe,Components(RooArgSet(*apdfEWKm,*(aqcdm->model))),FillColor(fillcolorEWK),DrawOption("F"));
  apdfMetm->plotOn(awmmframe,Components(RooArgSet(*apdfEWKm,*(aqcdm->model))),LineColor(linecolorEWK));
  apdfMetm->plotOn(awmmframe,Components(RooArgSet(*(aqcdm->model))),FillColor(fillcolorQCD),DrawOption("F"));
  apdfMetm->plotOn(awmmframe,Components(RooArgSet(*(aqcdm->model))),LineColor(linecolorQCD));
  apdfMetm->plotOn(awmmframe,Components(RooArgSet(*apdfWmm)),LineColor(linecolorW),LineStyle(2));
  antiMetm->plotOn(awmmframe,MarkerStyle(kFullCircle),MarkerSize(0.9),DrawOption("ZP"));
  
  sprintf(ylabel,"Events / %.1f GeV",hAntiDataMetm[ipt]->GetBinWidth(1));
  sprintf(histName,"fitAntiMetM_%d",ipt);
  plotAntiMetm=new CPlot(histName,awmmframe,"","",ylabel);
  plotAntiMetm->setOutDir(CPlot::sOutDir);
  plotAntiMetm->SetLegend(0.68,0.57,0.93,0.77);
  plotAntiMetm->GetLegend()->AddEntry(hDummyData,"data","PL");
  plotAntiMetm->GetLegend()->AddEntry(hDummyW,"W^{-}#rightarrow e^{-}#bar{#nu}","F");
  plotAntiMetm->GetLegend()->AddEntry(hDummyEWK,"EWK+t#bar{t}","F");
  plotAntiMetm->GetLegend()->AddEntry(hDummyQCD,"QCD","F");
  plotAntiMetm->AddTextBox(lumitext,0.55,0.80,0.90,0.86,0);
  plotAntiMetm->AddTextBox("CMS Preliminary",0.63,0.92,0.95,0.99,0);
  plotAntiMetm->SetYRange(0.1,1.1*(hAntiDataMetm[ipt]->GetMaximum()));
//plotAntiMetm->SetYRange(0.1,1500);
  plotAntiMetm->Draw(c,kFALSE,format,1);

  plotAntiMetmDiff=new CPlot(histName,"","#slash{E}_{T} [GeV]","#chi");
  plotAntiMetmDiff->setOutDir(CPlot::sOutDir);
  plotAntiMetmDiff->AddHist1D(hAntiMetmDiff,"EX0",ratioColor);
  plotAntiMetmDiff->SetYRange(-8,8);
  plotAntiMetmDiff->AddLine(0, 0,METMAX, 0,kBlack,1);
  plotAntiMetmDiff->AddLine(0, 5,METMAX, 5,kBlack,3);
  plotAntiMetmDiff->AddLine(0,-5,METMAX,-5,kBlack,3);
  plotAntiMetmDiff->Draw(c,kTRUE,format,2);
  
  sprintf(histName,"fitAntiMetMLog_%d",ipt);
  plotAntiMetm->SetName(histName);
  plotAntiMetm->SetLogy();
  plotAntiMetm->SetYRange(1e-3*(hAntiDataMetm[ipt]->GetMaximum()),10*(hAntiDataMetm[ipt]->GetMaximum()));
  plotAntiMetm->Draw(c,kTRUE,format,1);}
    
  //----------------------------
  // Output
  //============================
   
  cout << "*****************************************" << endl;
  cout << "* SUMMARY" << endl;
  cout << "*****************************************" << endl;  
  
  //
  // Write fit results
  //
  
  chi2prob = hDataMet[ipt]->Chi2Test(hPdfMet,"PUW");
  chi2ndf  = hDataMet[ipt]->Chi2Test(hPdfMet,"CHI2/NDFUW");
  ksprob   = hDataMet[ipt]->KolmogorovTest(hPdfMet);
  ksprobpe = hDataMet[ipt]->KolmogorovTest(hPdfMet,"DX");
  sprintf(txtfname,"%s/fitresWm_%d.txt",CPlot::sOutDir.Data(),ipt);
  txtfile.open(txtfname);
  assert(txtfile.is_open());
  
  flags = txtfile.flags();
  txtfile << setprecision(10);
  txtfile << " *** Yields *** " << endl;
  txtfile << "Selected: " << hDataMet[ipt]->Integral() << endl;
  txtfile << "  Signal: " << nSig->getVal() << " +/- " << nSig->getPropagatedError(*fitRes) << endl;
  txtfile << "     QCD: " << nQCD->getVal() << " +/- " << nQCD->getPropagatedError(*fitRes) << endl;
  txtfile << "   Other: " << nEWK->getVal() << " +/- " << nEWK->getPropagatedError(*fitRes) << endl;
  txtfile << "   Total: " << nSig->getVal()+nQCD->getVal()+nEWK->getVal() << endl;
  txtfile << endl;
  txtfile.flags(flags);
  
  fitRes->printStream(txtfile,RooPrintable::kValue,RooPrintable::kVerbose);
  txtfile << endl;
  printCorrelations(txtfile, fitRes);
  txtfile << endl;
  printChi2AndKSResults(txtfile, chi2prob, chi2ndf, ksprob, ksprobpe);
  txtfile.close();
  
  chi2prob = hDataMetp[ipt]->Chi2Test(hPdfMetp,"PUW");
  chi2ndf  = hDataMetp[ipt]->Chi2Test(hPdfMetp,"CHI2/NDFUW");
  ksprob   = hDataMetp[ipt]->KolmogorovTest(hPdfMetp);
  ksprobpe = hDataMetp[ipt]->KolmogorovTest(hPdfMetp,"DX");  
  sprintf(txtfname,"%s/fitresWmp_%d.txt",CPlot::sOutDir.Data(),ipt);
  txtfile.open(txtfname);
  assert(txtfile.is_open());
  
  flags = txtfile.flags();
  txtfile << setprecision(10);
  txtfile << " *** Yields *** " << endl;
  txtfile << "Selected: " << hDataMetp[ipt]->Integral() << endl;
  txtfile << "  Signal: " << nSigp->getVal() << " +/- " << nSigp->getPropagatedError(*fitResp) << endl;
  txtfile << "     QCD: " << nQCDp->getVal() << " +/- " << nQCDp->getPropagatedError(*fitResp) << endl;
  txtfile << "   Other: " << nEWKp->getVal() << " +/- " << nEWKp->getPropagatedError(*fitResp) << endl;
  txtfile << "   Total: " << nSigp->getVal()+nQCDp->getVal()+nEWKp->getVal() << endl;
  txtfile << endl; 
  txtfile.flags(flags);
  
  fitResp->printStream(txtfile,RooPrintable::kValue,RooPrintable::kVerbose);
  txtfile << endl;
  printCorrelations(txtfile, fitResp);
  txtfile << endl;
  printChi2AndKSResults(txtfile, chi2prob, chi2ndf, ksprob, ksprobpe);
  txtfile.close();
  chi2prob = hDataMetm[ipt]->Chi2Test(hPdfMetm,"PUW");
  chi2ndf  = hDataMetm[ipt]->Chi2Test(hPdfMetm,"CHI2/NDFUW");
  ksprob   = hDataMetm[ipt]->KolmogorovTest(hPdfMetm);
  ksprobpe = hDataMetm[ipt]->KolmogorovTest(hPdfMetm,"DX");  
  sprintf(txtfname,"%s/fitresWmm_%d.txt",CPlot::sOutDir.Data(),ipt);
  txtfile.open(txtfname);
  assert(txtfile.is_open());
  
  flags = txtfile.flags();
  txtfile << setprecision(10);
  txtfile << " *** Yields *** " << endl;
  txtfile << "Selected: " << hDataMetm[ipt]->Integral() << endl;
  txtfile << "  Signal: " << nSigm->getVal() << " +/- " << nSigm->getPropagatedError(*fitResm) << endl;
  txtfile << "     QCD: " << nQCDm->getVal() << " +/- " << nQCDm->getPropagatedError(*fitResm) << endl;
  txtfile << "   Other: " << nEWKm->getVal() << " +/- " << nEWKm->getPropagatedError(*fitResm) << endl;
  txtfile << "   Total: " << nSigm->getVal()+nQCDm->getVal()+nEWKm->getVal() << endl;
  txtfile << endl;
  txtfile.flags(flags);
  
  fitResm->printStream(txtfile,RooPrintable::kValue,RooPrintable::kVerbose);
  txtfile << endl;
  printCorrelations(txtfile, fitResm);
  txtfile << endl;
  printChi2AndKSResults(txtfile, chi2prob, chi2ndf, ksprob, ksprobpe);
  txtfile.close();
//*
  sprintf(txtfname,"%s/ShapesAntiWm_%d.txt",CPlot::sOutDir.Data(),ipt);
  txtfile.open(txtfname);
  assert(txtfile.is_open());
  
  flags = txtfile.flags();
  txtfile << setprecision(10);
  txtfile << " *** Control region Shape Parameters for the Pt Bin #"<< ipt << endl;
  txtfile << "Sigma_0 is: " << aqcd->sigma->getValV() << endl;
  txtfile << "Sigma_1 is: " << aqcd->a1->getValV() << endl;
  txtfile << "Plus Sigma_0 is: " << aqcdp->sigma->getValV() << endl;
  txtfile << "Plus Sigma_1 is: " << aqcdp->a1->getValV() << endl;
  txtfile << "Minus Sigma_0 is: " << aqcdm->sigma->getValV() << endl;
  txtfile << "Minus Sigma_1 is: " << aqcdm->a1->getValV() << endl;
  txtfile << endl; 
  txtfile.flags(flags);
  txtfile << endl;
  txtfile.close();
//*/
  sprintf(txtfname,"%s/ShapesWm_%d.txt",CPlot::sOutDir.Data(),ipt);
  txtfile.open(txtfname);
  assert(txtfile.is_open());
  
  flags = txtfile.flags();
  txtfile << setprecision(10);
  txtfile << " *** Signal region Shape Parameters for the Pt Bin #"<< ipt << endl;
  txtfile << "Sigma_0 is: " << qcd->sigma->getValV() << endl;
  txtfile << "Sigma_1 is: " << qcd->a1->getValV() << endl;
  txtfile << "Plus Sigma_0 is: " << qcdp->sigma->getValV() << endl;
  txtfile << "Plus Sigma_1 is: " << qcdp->a1->getValV() << endl;
  txtfile << "Minus Sigma_0 is: " << qcdm->sigma->getValV() << endl;
  txtfile << "Minus Sigma_1 is: " << qcdm->a1->getValV() << endl;
  txtfile << endl; 
  txtfile.flags(flags);
  txtfile << endl;
  txtfile.close();

  makeBinHTML(outputDir,ipt);

  sprintf(txtfname,"%s/YieldsTable_%d.html",CPlot::sOutDir.Data(),ipt);
  txtfile.open(txtfname);
  assert(txtfile.is_open());
  flags = txtfile.flags();
  txtfile << setprecision(8);
  txtfile << "<!DOCTYPE html" << endl;
  txtfile << "    PUBLIC \"-//W3C//DTD HTML 3.2//EN\">" << endl;
  txtfile << "<html>" << endl;
  txtfile << "<head><title>W pt Bin_"<< ipt <<" MET Fit</title></head>" << endl;
  txtfile << "<body bgcolor=\"white\">" << endl;
  txtfile << "<hr />" << endl;
  txtfile << "<p align=\"center\">  Bin "<< ipt <<" Yields </p>" << endl;
  txtfile << "<table border=\"1\" style=\"border-collapse: collapse\" bordercolor=\"black\" cellspacing=\"6\" width=\"1150\" align=\"center\">" << endl;
  txtfile << "<tr>" << endl;
  txtfile << "<td width=\"50\"></td>" << endl;
  txtfile << "<td width=\"100\"><p> Selected</p></td>" << endl;
  txtfile << "<td width=\"250\"><p> Total</p></td>" << endl;
  txtfile << "<td width=\"250\"><p> Signal</p></td>" << endl;
  txtfile << "<td width=\"250\"><p> QCD</p></td>" << endl;
  txtfile << "<td width=\"250\"><p> Others</p></td>" << endl;
  txtfile << "</tr>" << endl;
  txtfile << "<tr>" << endl;
  txtfile << "<td width=\"50\"><p> W</p></td>" << endl;
  txtfile << "<td width=\"100\"><p>"<< hDataMet[ipt]->Integral() <<"</p></td>" << endl;
  txtfile << "<td width=\"250\"><p>"<< nSig->getVal()+nQCD->getVal()+nEWK->getVal() << " +/- " << sqrt(nSig->getPropagatedError(*fitRes)*nSig->getPropagatedError(*fitRes)+nQCD->getPropagatedError(*fitRes)*nQCD->getPropagatedError(*fitRes)+nEWK->getPropagatedError(*fitRes)*nEWK->getPropagatedError(*fitRes)) << "</p></td>" << endl;
  txtfile << "<td width=\"250\"><p>"<< nSig->getVal() << " +/- " << nSig->getPropagatedError(*fitRes) << "</p></td>" << endl;
  txtfile << "<td width=\"250\"><p>"<< nQCD->getVal() << " +/- " << nQCD->getPropagatedError(*fitRes) << "</p></td>" << endl;
  txtfile << "<td width=\"250\"><p>"<< nEWK->getVal() << " +/- " << nEWK->getPropagatedError(*fitRes) << "</p></td>" << endl;
  txtfile << "</tr>" << endl;
  txtfile << "<tr>" << endl;
  txtfile << "<td width=\"50\"><p> W <sup>+</sup></p></td>" << endl;
  txtfile << "<td width=\"100\"><p>"<< hDataMetp[ipt]->Integral() <<"</p></td>" << endl;
  txtfile << "<td width=\"250\"><p>"<< nSigp->getVal()+nQCDp->getVal()+nEWKp->getVal() << " +/- " << sqrt(nSigp->getPropagatedError(*fitResp)*nSigp->getPropagatedError(*fitResp)+nQCDp->getPropagatedError(*fitResp)*nQCDp->getPropagatedError(*fitResp)+nEWKp->getPropagatedError(*fitResp)*nEWKp->getPropagatedError(*fitResp)) << "</p></td>" << endl;
  txtfile << "<td width=\"250\"><p>"<< nSigp->getVal() << " +/- " << nSigp->getPropagatedError(*fitResp) << "</p></td>" << endl;
  txtfile << "<td width=\"250\"><p>"<< nQCDp->getVal() << " +/- " << nQCDp->getPropagatedError(*fitResp) << "</p></td>" << endl;
  txtfile << "<td width=\"250\"><p>"<< nEWKp->getVal() << " +/- " << nEWKp->getPropagatedError(*fitResp) << "</p></td>" << endl;
  txtfile << "</tr>" << endl;
  txtfile << "<tr>" << endl;
  txtfile << "<td width=\"50\"><p> W <sup>-</sup></p></td>" << endl;
  txtfile << "<td width=\"100\"><p>"<< hDataMetm[ipt]->Integral() <<"</p></td>" << endl;
  txtfile << "<td width=\"250\"><p>"<< nSigm->getVal()+nQCDm->getVal()+nEWKm->getVal() << " +/- " << sqrt(nSigm->getPropagatedError(*fitResm)*nSigm->getPropagatedError(*fitResm)+nQCDm->getPropagatedError(*fitResm)*nQCDm->getPropagatedError(*fitResm)+nEWKm->getPropagatedError(*fitResm)*nEWKm->getPropagatedError(*fitResm)) << "</p></td>" << endl;
  txtfile << "<td width=\"250\"><p>"<< nSigm->getVal() << " +/- " << nSigm->getPropagatedError(*fitResm) << "</p></td>" << endl;
  txtfile << "<td width=\"250\"><p>"<< nQCDm->getVal() << " +/- " << nQCDm->getPropagatedError(*fitResm) << "</p></td>" << endl;
  txtfile << "<td width=\"250\"><p>"<< nEWKm->getVal() << " +/- " << nEWKm->getPropagatedError(*fitResm) << "</p></td>" << endl;
  txtfile << "</tr>" << endl;
  txtfile << "</table>" << endl;
  txtfile << "<hr />" << endl;
  txtfile << "</body>" << endl;
  txtfile << "</html>" << endl;
  txtfile.close();

  cout << endl;
  cout << "  <> Output saved in " << outputDir << "/" << endl;    
  cout << endl;
  if( 0< ipt )
  {
  hSigWpt->SetBinContent(ipt, nSig->getVal());
  hEWKWpt->SetBinContent(ipt, nEWK->getVal());
  hQCDWpt->SetBinContent(ipt, nQCD->getVal());
  hSigWPpt->SetBinContent(ipt, nSigp->getVal());
  hEWKWPpt->SetBinContent(ipt, nEWKp->getVal());
  hQCDWPpt->SetBinContent(ipt, nQCDp->getVal());
  hSigWMpt->SetBinContent(ipt, nSigm->getVal());
  hEWKWMpt->SetBinContent(ipt, nEWKm->getVal());
  hQCDWMpt->SetBinContent(ipt, nQCDm->getVal());
  }
  }
  // Wpt distribution=========================
  TCanvas *myCan=new TCanvas("myCan","myCan",800,600);
  gStyle->SetLineWidth(2.);
//  gStyle->SetTextSize(1.1);
  gStyle->SetLabelSize(0.04,"xy");
  gStyle->SetTitleSize(0.05,"xy");
  gStyle->SetTitleOffset(1.1,"x");
  gStyle->SetTitleOffset(1.2,"y");
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadRightMargin(0.1);
  gStyle->SetPadBottomMargin(0.16);
  gStyle->SetPadLeftMargin(0.12);

  TLegend *W_ptLgd = new TLegend(.75, .7,.9,.9);
  myCan->cd();
  THStack *hs_W_pt = new THStack("hs_W_pt","W");
  hEWKWpt->SetFillColor(fillcolorEWK);
  hEWKWpt->SetLineColor(linecolorEWK);
  hEWKWpt->SetFillStyle(1001);
  hEWKWpt->GetXaxis()->SetTitle("p_{T} [GeV]");
  hEWKWpt->GetYaxis()->SetTitle("Events");
  hEWKWpt->GetYaxis()->CenterTitle();
  hs_W_pt->Add(hEWKWpt);
  W_ptLgd->AddEntry(hEWKWpt,"EWK","fl");

  hQCDWpt->SetFillColor(fillcolorQCD);
  hQCDWpt->SetLineColor(linecolorQCD);
  hQCDWpt->SetFillStyle(1001);
  hs_W_pt->Add(hQCDWpt);
  W_ptLgd->AddEntry(hQCDWpt,"QCD","fl");

  hSigWpt->SetFillColor(fillcolorW);
  hSigWpt->SetLineColor(linecolorW);
  hSigWpt->SetFillStyle(1001);
  hs_W_pt->Add(hSigWpt);
  W_ptLgd->AddEntry(hSigWpt,"W#rightarrow e#nu","fl");
  hs_W_pt->SetMinimum(5e-6*(hs_W_pt->GetMaximum()));
  hs_W_pt->SetMaximum(1.1*(hs_W_pt->GetMaximum()));
  hs_W_pt->Draw();
  hs_W_pt->GetXaxis()->SetTitle("p_{T} [GeV]");
  hs_W_pt->GetYaxis()->SetTitle("Events");
  hs_W_pt->GetYaxis()->CenterTitle();

  hdataWpt->SetMarkerStyle(kFullCircle);
  hdataWpt->SetMarkerSize(0.9);
  hdataWpt->Draw("esame");
  W_ptLgd->AddEntry(hdataWpt,"RD","fl");
  W_ptLgd->SetFillColor(0);
  W_ptLgd->Draw();
  myCan->SaveAs(outputDir+"/"+"Wpt.png");
  myCan->SetLogy();
  myCan->Draw();
  myCan->SaveAs(outputDir+"/"+"WptLog.png");

  TLegend *WP_ptLgd = new TLegend(.75, .7,.9,.9);
  THStack *hs_WP_pt = new THStack("hs_WP_pt","W^{+}");
  hEWKWPpt->SetFillColor(fillcolorEWK);
  hEWKWPpt->SetLineColor(linecolorEWK);
  hEWKWPpt->SetFillStyle(1001);
  hEWKWPpt->GetXaxis()->SetTitle("p_{T} [GeV]");
  hEWKWPpt->GetYaxis()->SetTitle("Events");
  hEWKWPpt->GetYaxis()->CenterTitle();
  hs_WP_pt->Add(hEWKWPpt);
  WP_ptLgd->AddEntry(hEWKWPpt,"EWK","fl");

  hQCDWPpt->SetFillColor(fillcolorQCD);
  hQCDWPpt->SetLineColor(linecolorQCD);
  hQCDWPpt->SetFillStyle(1001);
  hs_WP_pt->Add(hQCDWPpt);
  WP_ptLgd->AddEntry(hQCDWPpt,"QCD","fl");

  hSigWPpt->SetFillColor(fillcolorW);
  hSigWPpt->SetLineColor(linecolorW);
  hSigWPpt->SetFillStyle(1001);
  hs_WP_pt->Add(hSigWPpt);
  WP_ptLgd->AddEntry(hSigWPpt,"W^{+}#rightarrow e#nu","fl");
  hs_WP_pt->SetMinimum(5e-6*(hs_WP_pt->GetMaximum()));
  hs_WP_pt->SetMaximum(1.1*(hs_WP_pt->GetMaximum()));
  hs_WP_pt->Draw();
  hs_WP_pt->GetXaxis()->SetTitle("p_{T} [GeV]");
  hs_WP_pt->GetYaxis()->SetTitle("Events");
  hs_WP_pt->GetYaxis()->CenterTitle();

  hdataWPpt->SetMarkerStyle(kFullCircle);
  hdataWPpt->SetMarkerSize(0.9);
  hdataWPpt->Draw("esame");
  WP_ptLgd->AddEntry(hdataWPpt,"RD","fl");
  WP_ptLgd->SetFillColor(0);
  myCan->SetLogy(0);
  WP_ptLgd->Draw();
  myCan->SaveAs(outputDir+"/"+"WPpt.png");
  myCan->SetLogy();
  myCan->Draw();
  myCan->SaveAs(outputDir+"/"+"WPptLog.png");

  TLegend *WM_ptLgd = new TLegend(.75, .7,.9,.9);
  THStack *hs_WM_pt = new THStack("hs_WM_pt","W^{-}");
  hEWKWMpt->SetFillColor(fillcolorEWK);
  hEWKWMpt->SetLineColor(linecolorEWK);
  hEWKWMpt->SetFillStyle(1001);
  hEWKWMpt->GetXaxis()->SetTitle("p_{T} [GeV]");
  hEWKWMpt->GetYaxis()->SetTitle("Events");
  hEWKWMpt->GetYaxis()->CenterTitle();
  hs_WM_pt->Add(hEWKWMpt);
  WM_ptLgd->AddEntry(hEWKWMpt,"EWK","fl");

  hQCDWMpt->SetFillColor(fillcolorQCD);
  hQCDWMpt->SetLineColor(linecolorQCD);
  hQCDWMpt->SetFillStyle(1001);
  hs_WM_pt->Add(hQCDWMpt);
  WM_ptLgd->AddEntry(hQCDWMpt,"QCD","fl");

  hSigWMpt->SetFillColor(fillcolorW);
  hSigWMpt->SetLineColor(linecolorW);
  hSigWMpt->SetFillStyle(1001);
  hs_WM_pt->Add(hSigWMpt);
  WM_ptLgd->AddEntry(hSigWMpt,"W^{-}#rightarrow e#nu","fl");
  hs_WM_pt->SetMinimum(5e-6*(hs_WM_pt->GetMaximum()));
  hs_WM_pt->SetMaximum(1.1*(hs_WM_pt->GetMaximum()));
  hs_WM_pt->Draw();
  hs_WM_pt->GetXaxis()->SetTitle("p_{T} [GeV]");
  hs_WM_pt->GetYaxis()->SetTitle("Events");
  hs_WM_pt->GetYaxis()->CenterTitle();

  hdataWMpt->SetMarkerStyle(kFullCircle);
  hdataWMpt->SetMarkerSize(0.9);
  hdataWMpt->Draw("esame");
  WM_ptLgd->AddEntry(hdataWMpt,"RD","fl");
  WM_ptLgd->SetFillColor(0);
  myCan->SetLogy(0);
  WM_ptLgd->Draw();
  myCan->SaveAs(outputDir+"/"+"WMpt.png");
  myCan->SetLogy();
  myCan->Draw();
  myCan->SaveAs(outputDir+"/"+"WMptLog.png");

  makeHTML(outputDir);
  
  gBenchmark->Show("fitWEleMetRayleighSimult");
}


//=== FUNCTION DEFINITIONS ======================================================================================

//--------------------------------------------------------------------------------------------------
TH1D *makeDiffHist(TH1D* hData, TH1D* hFit, const TString name)
{
  TH1D *hDiff = new TH1D(name,"",hData->GetNbinsX(),hData->GetXaxis()->GetXmin(),hData->GetXaxis()->GetXmax());
  for(Int_t ibin=1; ibin<=hData->GetNbinsX(); ibin++) {
    
    Double_t diff = (hData->GetBinContent(ibin)-hFit->GetBinContent(ibin));
    
    Double_t err = sqrt(hData->GetBinContent(ibin));
    if(err==0) err= sqrt(hFit->GetBinContent(ibin));
    
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

//--------------------------------------------------------------------------------------------------
void printCorrelations(ostream& os, RooFitResult *res)
{
  ios_base::fmtflags flags = os.flags();
  const RooArgList parlist = res->floatParsFinal();
  
  os << "  Correlation Matrix" << endl;
  os << " --------------------" << endl;
  for(Int_t i=0; i<parlist.getSize(); i++) {
    for(Int_t j=0; j<parlist.getSize(); j++) 
      os << "  " << setw(7) << setprecision(4) << fixed << res->correlationMatrix()(i,j);    
    os << endl;
  }
  os.flags(flags);
}

//--------------------------------------------------------------------------------------------------
void printChi2AndKSResults(ostream& os, 
                           const Double_t chi2prob, const Double_t chi2ndf, 
			   const Double_t ksprob, const Double_t ksprobpe)
{
  ios_base::fmtflags flags = os.flags();
  
  os << "  Chi2 Test" << endl;
  os << " -----------" << endl;
  os << "       prob = " << chi2prob << endl;
  os << "   chi2/ndf = " << chi2ndf << endl;
  os << endl;
  os << "  KS Test" << endl;
  os << " ---------" << endl;
  os << "   prob = " << ksprob << endl;
  os << "   prob = " << ksprobpe << " with 1000 pseudo-experiments" << endl;
  os << endl;
  os.flags(flags);
}

//--------------------------------------------------------------------------------------------------
void makeHTML(const TString outDir)
{
  ofstream htmlfile;
  char htmlfname[100];
  sprintf(htmlfname,"%s/WenuFitPlots.html",outDir.Data());
  htmlfile.open(htmlfname);
  htmlfile << "<!DOCTYPE html" << endl;
  htmlfile << "    PUBLIC \"-//W3C//DTD HTML 3.2//EN\">" << endl;
  htmlfile << "<html>" << endl;
  htmlfile << "<head><title>W --> e nu</title></head>" << endl;
  htmlfile << "<body bgcolor=\"EEEEEE\">" << endl;
  htmlfile << "<hr />" << endl;
  htmlfile << " <p> <a target=\"_blank\" href=\"fitMet_0.html\">[Wpt Bin 0 MET Fit results]</a>" << endl;
  htmlfile << " <p> <a target=\"_blank\" href=\"fitMet_1.html\">[Wpt Bin 1 MET Fit results]</a>" << "&nbsp; <a target=\"_blank\" href=\"YieldsTable_1.html\">[Bin 1 Yields Table]</a> </p>" << endl;
  htmlfile << " <p> <a target=\"_blank\" href=\"fitMet_2.html\">[Wpt Bin 2 MET Fit results]</a>" << "&nbsp; <a target=\"_blank\" href=\"YieldsTable_2.html\">[Bin 2 Yields Table]</a> </p>" << endl;
  htmlfile << " <p> <a target=\"_blank\" href=\"fitMet_3.html\">[Wpt Bin 3 MET Fit results]</a>" << "&nbsp; <a target=\"_blank\" href=\"YieldsTable_3.html\">[Bin 3 Yields Table]</a> </p>" << endl;
  htmlfile << " <p> <a target=\"_blank\" href=\"fitMet_4.html\">[Wpt Bin 4 MET Fit results]</a>" << "&nbsp; <a target=\"_blank\" href=\"YieldsTable_4.html\">[Bin 4 Yields Table]</a> </p>" << endl;
  htmlfile << " <p> <a target=\"_blank\" href=\"fitMet_5.html\">[Wpt Bin 5 MET Fit results]</a>" << "&nbsp; <a target=\"_blank\" href=\"YieldsTable_5.html\">[Bin 5 Yields Table]</a> </p>" << endl;
  htmlfile << " <p> <a target=\"_blank\" href=\"fitMet_6.html\">[Wpt Bin 6 MET Fit results]</a>" << "&nbsp; <a target=\"_blank\" href=\"YieldsTable_6.html\">[Bin 6 Yields Table]</a> </p>" << endl;
  htmlfile << " <p> <a target=\"_blank\" href=\"fitMet_7.html\">[Wpt Bin 7 MET Fit results]</a>" << "&nbsp; <a target=\"_blank\" href=\"YieldsTable_7.html\">[Bin 7 Yields Table]</a> </p>" << endl;
  htmlfile << " <p> <a target=\"_blank\" href=\"fitMet_8.html\">[Wpt Bin 8 MET Fit results]</a>" << "&nbsp; <a target=\"_blank\" href=\"YieldsTable_8.html\">[Bin 8 Yields Table]</a> </p>" << endl;
  htmlfile << " <p> <a target=\"_blank\" href=\"fitMet_9.html\">[Wpt Bin 9 MET Fit results]</a>" << "&nbsp; <a target=\"_blank\" href=\"YieldsTable_9.html\">[Bin 9 Yields Table]</a> </p>" << endl;
  htmlfile << " <p> <a target=\"_blank\" href=\"fitMet_10.html\">[Wpt Bin 10 MET Fit results]</a>" << "&nbsp; <a target=\"_blank\" href=\"YieldsTable_10.html\">[Bin 10 Yields Table]</a> </p>" << endl;
  htmlfile << " <p> <a target=\"_blank\" href=\"fitMet_11.html\">[Wpt Bin 11 MET Fit results]</a>" << "&nbsp; <a target=\"_blank\" href=\"YieldsTable_11.html\">[Bin 11 Yields Table]</a> </p>" << endl;
  htmlfile << " <p> <a target=\"_blank\" href=\"Wpt.html\">[Wpt plots]</a>" << endl;
  htmlfile << "<hr />" << endl;
  htmlfile << "</body>" << endl;
  htmlfile << "</html>" << endl;
  htmlfile.close();

  sprintf(htmlfname,"%s/Wpt.html",outDir.Data());
  htmlfile.open(htmlfname);
  htmlfile << "<!DOCTYPE html" << endl;
  htmlfile << "    PUBLIC \"-//W3C//DTD HTML 3.2//EN\">" << endl;
  htmlfile << "<html>" << endl;
  htmlfile << "<head><title>W pt</title></head>" << endl;
  htmlfile << "<body bgcolor=\"EEEEEE\">" << endl;
  htmlfile << "<hr />" << endl;
  htmlfile << "<table border=\"0\" cellspacing=\"5\" width=\"100%\">" << endl; 
  htmlfile << "<tr>" << endl;
  htmlfile << "<td width=\"15%\"></td>" << endl;
  htmlfile << "<td width=\"20%\"><a target=\"_blank\" href=\"Wpt.png\"><img src=\"Wpt.png\" alt=\"Wpt.png\" width=\"100%\"></a></td>" << endl;
  htmlfile << "<td width=\"20%\"><a target=\"_blank\" href=\"WptLog.png\"><img src=\"WptLog.png\" alt=\"WptLog.png\" width=\"100%\"></a></td>" << endl;
  htmlfile << "<td width=\"45%\"></td>" << endl;
  htmlfile << "</tr>" << endl;
  htmlfile << "<tr>" << endl;
  htmlfile << "<td width=\"15%\"></td>" << endl;
  htmlfile << "<td width=\"20%\"><a target=\"_blank\" href=\"WPpt.png\"><img src=\"WPpt.png\" alt=\"WPpt.png\" width=\"100%\"></a></td>" << endl;
  htmlfile << "<td width=\"20%\"><a target=\"_blank\" href=\"WPptLog.png\"><img src=\"WPptLog.png\" alt=\"WPptLog.png\" width=\"100%\"></a></td>" << endl;
  htmlfile << "<td width=\"45%\"></td>" << endl;
  htmlfile << "</tr>" << endl;
  htmlfile << "<tr>" << endl;
  htmlfile << "<td width=\"15%\"></td>" << endl;
  htmlfile << "<td width=\"20%\"><a target=\"_blank\" href=\"WMpt.png\"><img src=\"WMpt.png\" alt=\"WMpt.png\" width=\"100%\"></a></td>" << endl;
  htmlfile << "<td width=\"20%\"><a target=\"_blank\" href=\"WMptLog.png\"><img src=\"WMptLog.png\" alt=\"WMptLog.png\" width=\"100%\"></a></td>" << endl;
  htmlfile << "<td width=\"45%\"></td>" << endl;
  htmlfile << "</tr>" << endl;
  htmlfile << "</table>" << endl;
  htmlfile << "</body>" << endl;
  htmlfile << "</html>" << endl;
  htmlfile.close();  
} 
//--------------------------------------------------------------------------------------------------
void makeBinHTML(const TString outDir, Int_t i)
{
  ofstream htmlfile;
  char htmlfname[100];
  sprintf(htmlfname,"%s/fitMet_%d.html",outDir.Data(),i);
  htmlfile.open(htmlfname);
  htmlfile << setprecision(9);
  htmlfile << "<!DOCTYPE html" << endl;
  htmlfile << "    PUBLIC \"-//W3C//DTD HTML 3.2//EN\">" << endl;
  htmlfile << "<html>" << endl;
  htmlfile << "<head><title>W pt Bin_"<< i <<" MET Fit</title></head>" << endl;
  htmlfile << "<body bgcolor=\"white\">" << endl;
  htmlfile << "<hr />" << endl;
  htmlfile << "<p align=\"center\">  Bin - "<< i << "</p>" << endl;
  htmlfile << "<table border=\"0\" cellspacing=\"5\" width=\"900\" align=\"center\">" << endl; 
  htmlfile << "<tr>" << endl;
  htmlfile << "<td width=\"100\"></td>" << endl;
  htmlfile << "<td width=\"400\" colspan=\"2\"><p align=\"center\" style=\"font-size:small\"> Signal </p></td>" << endl;
  htmlfile << "<td width=\"400\" colspan=\"2\"><p align=\"center\" style=\"font-size:small\"> Side </p></td>" << endl;
  htmlfile << "</tr>" << endl;
  htmlfile << "<tr>" << endl;
  htmlfile << "<td width=\"100\"><p align=\"center\" style=\"font-size:small\"> W </p></td>" << endl;
  htmlfile << "<td width=\"200\"><a target=\"_blank\" href=\"fitMet_"<< i <<".png\"><img src=\"fitMet_"<< i <<".png\" width=\"200\" alt=\"fitMet_"<< i <<".png\"></a></td>" << endl;
  htmlfile << "<td width=\"200\"><a target=\"_blank\" href=\"fitMetLog_"<< i <<".png\"><img src=\"fitMetLog_"<< i <<".png\" width=\"200\" alt=\"fitMetLog_"<< i <<".png\"></a></td>" << endl;
  htmlfile << "<td width=\"200\"><a target=\"_blank\" href=\"fitAntiMet_"<< i <<".png\"><img src=\"fitAntiMet_"<< i <<".png\" width=\"200\" alt=\"fitAntiMet_"<< i <<".png\"></a></td>" << endl;
  htmlfile << "<td width=\"200\"><a target=\"_blank\" href=\"fitAntiMetLog_"<< i <<".png\"><img src=\"fitAntiMetLog_"<< i <<".png\" width=\"200\" alt=\"fitAntiMetLog_"<< i <<".png\"></a></td>" << endl;
  htmlfile << "</tr>" << endl;
  htmlfile << "<tr>" << endl;
  htmlfile << "<td width=\"100\"><p align=\"center\" style=\"font-size:small\"> W <sup>+</sup> </p></td>" << endl;
  htmlfile << "<td width=\"200\"><a target=\"_blank\" href=\"fitMetP_"<< i <<".png\"><img src=\"fitMetP_"<< i <<".png\" width=\"200\" alt=\"fitMetP_"<< i <<".png\"></a></td>" << endl;
  htmlfile << "<td width=\"200\"><a target=\"_blank\" href=\"fitMetPLog_"<< i <<".png\"><img src=\"fitMetPLog_"<< i <<".png\" width=\"200\" alt=\"fitMetPLog_"<< i <<".png\"></a></td>" << endl;
  htmlfile << "<td width=\"200\"><a target=\"_blank\" href=\"fitAntiMetP_"<< i <<".png\"><img src=\"fitAntiMetP_"<< i <<".png\" width=\"200\" alt=\"fitAntiMetP_"<< i <<".png\"></a></td>" << endl;
  htmlfile << "<td width=\"200\"><a target=\"_blank\" href=\"fitAntiMetPLog_"<< i <<".png\"><img src=\"fitAntiMetPLog_"<< i <<".png\" width=\"200\" alt=\"fitAntiMetPLog_"<< i <<".png\"></a></td>" << endl;
  htmlfile << "</tr>" << endl;
  htmlfile << "<tr>" << endl;
  htmlfile << "<td width=\"100\"><p align=\"center\" style=\"font-size:small\"> W <sup>-</sup></p></td>" << endl;
  htmlfile << "<td width=\"200\"><a target=\"_blank\" href=\"fitMetM_"<< i <<".png\"><img src=\"fitMetM_"<< i <<".png\" width=\"200\" alt=\"fitMetM_"<< i <<".png\"></a></td>" << endl;
  htmlfile << "<td width=\"200\"><a target=\"_blank\" href=\"fitMetMLog_"<< i <<".png\"><img src=\"fitMetMLog_"<< i <<".png\" width=\"200\" alt=\"fitMetMLog_"<< i <<".png\"></a></td>" << endl;
  htmlfile << "<td width=\"200\"><a target=\"_blank\" href=\"fitAntiMetM_"<< i <<".png\"><img src=\"fitAntiMetM_"<< i <<".png\" width=\"200\" alt=\"fitAntiMetM_"<< i <<".png\"></a></td>" << endl;
  htmlfile << "<td width=\"200\"><a target=\"_blank\" href=\"fitAntiMetMLog_"<< i <<".png\"><img src=\"fitAntiMetMLog_"<< i <<".png\" width=\"200\" alt=\"fitAntiMetMLog_"<< i <<".png\"></a></td>" << endl;
  htmlfile << "</tr>" << endl;
  htmlfile << "</table>" << endl;
  htmlfile << "<hr />" << endl;
  htmlfile << "</body>" << endl;
  htmlfile << "</html>" << endl;
  htmlfile.close();  
}
