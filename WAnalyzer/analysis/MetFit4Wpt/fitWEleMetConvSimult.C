//================================================
//
// Perform fit to extract W->enu signal
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
TH1D* makeDiffHistWpt(TH1D* hData, TH1D* hFit, const TString name);
// print correlations of fitted parameters
void printCorrelations(ostream& os, RooFitResult *res);

// print chi2 test and KS test results
void printChi2AndKSResults(ostream& os, 
                           const Double_t chi2prob, const Double_t chi2ndf, 
			   const Double_t ksprob, const Double_t ksprobpe);

// make webpage
void makeHTML(const TString outDir);

//=== MAIN MACRO ================================================ 

void fitWEleMetConvSimult(const TString  outputDir,   // output directory
           const TString  filetype,		// Select input root files for Nominal, Up, Down and Before Recoil Correction
           const Double_t lumi,        // integrated luminosity (/fb)
	   const Double_t nsigma=0     // vary MET corrections by n-sigmas (nsigma=0 means nominal correction)
)
{
  gBenchmark->Start("fitWEleMetConvSimult");

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
  enum { eData, eWpEleNu, eEWK, eWmEleNu };  // data type enum
  //enum { eData, eWmunu, eEWK, eAntiData, eAntiWmunu, eAntiEWK };  // data type enum
  vector<TString> fnamev;
  vector<Int_t>   typev;

  //total number of each EWK samples for ith bin
  vector <double> nEventDYToEE;
  vector <double> nEventDYToTauTau;
  vector <double> nEventTTJets;
  vector <double> nEventWToTauNu;
  vector <double> nEventDYToEEP;
  vector <double> nEventDYToTauTauP;
  vector <double> nEventTTJetsP;
  vector <double> nEventWToTauNuP;
  vector <double> nEventDYToEEM;
  vector <double> nEventDYToTauTauM;
  vector <double> nEventTTJetsM;
  vector <double> nEventWToTauNuM;

  int ewkNumber(0);

  fnamev.push_back("../EventSelection/ElectronLowPU/Ele_RD_LowPU_Analysis.root"); typev.push_back(eData);
  fnamev.push_back("../EventSelection/ElectronLowPU/Ele_DYToEE_S8_Analysis.root"); typev.push_back(eEWK);
  fnamev.push_back("../EventSelection/ElectronLowPU/Ele_DYToTauTau_S8_Analysis.root"); typev.push_back(eEWK);
  fnamev.push_back("../EventSelection/ElectronLowPU/Ele_TTJets_S8_Analysis.root"); typev.push_back(eEWK);
  fnamev.push_back("../EventSelection/ElectronLowPU/Ele_WToTauNu_S8_Analysis.root"); typev.push_back(eEWK);
  if (filetype == "Nominal"){
  fnamev.push_back("../EventSelection/ElectronLowPU/Ele_WpToEleNu_S8_RecoilCorr.root"); typev.push_back(eWpEleNu);
  fnamev.push_back("../EventSelection/ElectronLowPU/Ele_WmToEleNu_S8_RecoilCorr.root"); typev.push_back(eWmEleNu);
  }else if (filetype == "Up"){  
  fnamev.push_back("../EventSelection/ElectronLowPU/Ele_WpToEleNu_S8_Up_RecoilCorr.root"); typev.push_back(eWpEleNu);
  fnamev.push_back("../EventSelection/ElectronLowPU/Ele_WmToEleNu_S8_Up_RecoilCorr.root"); typev.push_back(eWmEleNu);
  }else if (filetype == "Down"){
  fnamev.push_back("../EventSelection/ElectronLowPU/Ele_WpToEleNu_S8_Down_RecoilCorr.root"); typev.push_back(eWpEleNu);
  fnamev.push_back("../EventSelection/ElectronLowPU/Ele_WmToEleNu_S8_Down_RecoilCorr.root"); typev.push_back(eWmEleNu);
  }else if (filetype == "BeforeRC"){
  fnamev.push_back("../EventSelection/ElectronLowPU/Ele_WpToEleNu_S8_Analysis.root"); typev.push_back(eWpEleNu);
  fnamev.push_back("../EventSelection/ElectronLowPU/Ele_WmToEleNu_S8_Analysis.root"); typev.push_back(eWmEleNu);
  }
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
  TH1D *hQCDWpt = new TH1D("hQCDWpt","hQCDWpt",11,WptBins);hQCDWpt->Sumw2();
  TH1D *hSigWPpt = new TH1D("hSigWPpt","hSigWPpt",11,WptBins);hSigWPpt->Sumw2();
  TH1D *hQCDWPpt = new TH1D("hQCDWPpt","hQCDWPpt",11,WptBins);hQCDWPpt->Sumw2();
  TH1D *hSigWMpt = new TH1D("hSigWMpt","hSigWMpt",11,WptBins);hSigWMpt->Sumw2();
  TH1D *hQCDWMpt = new TH1D("hQCDWMpt","hQCDWMpt",11,WptBins);hQCDWMpt->Sumw2();

  TH1D *hDYToEE = new TH1D("hDYToEE","hDYToEE",11,WptBins);hDYToEE->Sumw2();
  TH1D *hWToTauTau = new TH1D("hWToTauTau","hWToTauTau",11,WptBins);hWToTauTau->Sumw2();
  TH1D *hTTJets = new TH1D("hTTJets","hTTJets",11,WptBins);hTTJets->Sumw2();
  TH1D *hDYToTauTau = new TH1D("hDYToTauTau","hDYToTauTau",11,WptBins);hDYToTauTau->Sumw2();
  TH1D *hDYToEEP = new TH1D("hDYToEEP","hDYToEEP",11,WptBins);hDYToEEP->Sumw2();
  TH1D *hWToTauTauP = new TH1D("hWToTauTauP","hWToTauTauP",11,WptBins);hWToTauTauP->Sumw2();
  TH1D *hTTJetsP = new TH1D("hTTJetsP","hTTJetsP",11,WptBins);hTTJetsP->Sumw2();
  TH1D *hDYToTauTauP = new TH1D("hDYToTauTauP","hDYToTauTauP",11,WptBins);hDYToTauTauP->Sumw2();
  TH1D *hDYToEEM = new TH1D("hDYToEEM","hDYToEEM",11,WptBins);hDYToEEM->Sumw2();
  TH1D *hWToTauTauM = new TH1D("hWToTauTauM","hWToTauTauM",11,WptBins);hWToTauTauM->Sumw2();
  TH1D *hTTJetsM = new TH1D("hTTJetsM","hTTJetsM",11,WptBins);hTTJetsM->Sumw2();
  TH1D *hDYToTauTauM = new TH1D("hDYToTauTauM","hDYToTauTauM",11,WptBins);hDYToTauTauM->Sumw2();

  TH1D *hDataMet  [NWptBinPlus]  ;
  TH1D *hDataMetm [NWptBinPlus]  ;
  TH1D *hDataMetp [NWptBinPlus]  ; 
  TH1D *hWenuMet [NWptBinPlus]  ; 
  TH1D *hWenuMetp[NWptBinPlus]  ;
  TH1D *hWenuMetm[NWptBinPlus]  ;
  TH1D *hEWKMet   [NWptBinPlus]  ; 
  TH1D *hEWKMetp  [NWptBinPlus]  ; 
  TH1D *hEWKMetm  [NWptBinPlus]  ; 
                                              
  TH1D *hAntiDataMet  [NWptBinPlus]   ;
  TH1D *hAntiDataMetm [NWptBinPlus]  ;
  TH1D *hAntiDataMetp [NWptBinPlus]  ;
  TH1D *hAntiWenuMet [NWptBinPlus]  ;
  TH1D *hAntiWenuMetp[NWptBinPlus] ;
  TH1D *hAntiWenuMetm[NWptBinPlus] ;
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
    if(typev[ifile]==eWpEleNu)
    {
      for( int ipt(0);ipt<NWptBinPlus;ipt++)
      {
	sprintf(histName,"hWenuMetp_%d",ipt);
	sprintf(histName_org,"h1_Wp_Neu_pt_%d",ipt);
	hWenuMetp[ipt]=(TH1D*)infile->Get(histName_org)->Clone(histName);hWenuMetp[ipt]->Sumw2();
	sprintf(histName,"hAntiWenuMetp_%d",ipt);
	sprintf(histName_org,"h1_WpSide_Neu_pt_%d",ipt);
	hAntiWenuMetp[ipt]=(TH1D*)infile->Get(histName_org)->Clone(histName);hAntiWenuMetp[ipt]->Sumw2();
      }
    }
    if(typev[ifile]==eWmEleNu)
    {
      for( int ipt(0);ipt<NWptBinPlus;ipt++)
      {
	sprintf(histName,"hWenuMetm_%d",ipt);
	sprintf(histName_org,"h1_Wm_Neu_pt_%d",ipt);
	hWenuMetm[ipt]=(TH1D*)infile->Get(histName_org)->Clone(histName);hWenuMetm[ipt]->Sumw2();
	sprintf(histName,"hAntiWenuMetm_%d",ipt);
	sprintf(histName_org,"h1_WmSide_Neu_pt_%d",ipt);
	hAntiWenuMetm[ipt]=(TH1D*)infile->Get(histName_org)->Clone(histName);hAntiWenuMetm[ipt]->Sumw2();
      }
    }
    if(typev[ifile]==eEWK)
    {
      if(first_EWK_file){
        ewkNumber++;
	for( int ipt(0); ipt<NWptBinPlus; ipt++)
	{
	  sprintf(histName,"hEWKMet_%d",ipt);
	  sprintf(histName_org,"h1_W_Neu_pt_%d",ipt);
	  hEWKMet[ipt] =(TH1D*)infile->Get(histName_org)->Clone(histName);hEWKMet[ipt]->Sumw2();
	  nEventDYToEE.push_back(hEWKMet[ipt]->Integral());
	  sprintf(histName,"hEWKMetm_%d",ipt);
	  sprintf(histName_org,"h1_Wm_Neu_pt_%d",ipt);
	  hEWKMetm[ipt]=(TH1D*)infile->Get(histName_org)->Clone(histName);hEWKMetm[ipt]->Sumw2();
	  nEventDYToEEM.push_back(hEWKMetm[ipt]->Integral());
	  sprintf(histName,"hEWKMetp_%d",ipt);
	  sprintf(histName_org,"h1_Wp_Neu_pt_%d",ipt);
	  hEWKMetp[ipt]=(TH1D*)infile->Get(histName_org)->Clone(histName);hEWKMetp[ipt]->Sumw2();
	  nEventDYToEEP.push_back(hEWKMetp[ipt]->Integral());

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
	ewkNumber++;
	for( int ipt(0); ipt<NWptBinPlus; ipt++)
	{
	  sprintf(histName_org,"h1_W_Neu_pt_%d",ipt);
	  hEWKMet[ipt] ->Add((TH1D*)infile->Get(histName_org)->Clone(histName));
	  if(ewkNumber == 2)nEventDYToTauTau.push_back(hEWKMet[ipt]->Integral());
	  if(ewkNumber == 3)nEventTTJets.push_back(hEWKMet[ipt]->Integral());
	  if(ewkNumber == 4)nEventWToTauNu.push_back(hEWKMet[ipt]->Integral());
	  sprintf(histName_org,"h1_Wm_Neu_pt_%d",ipt);
	  hEWKMetm[ipt]->Add((TH1D*)infile->Get(histName_org)->Clone(histName));
          if(ewkNumber == 2)nEventDYToTauTauM.push_back(hEWKMetm[ipt]->Integral());
          if(ewkNumber == 3)nEventTTJetsM.push_back(hEWKMetm[ipt]->Integral());
          if(ewkNumber == 4)nEventWToTauNuM.push_back(hEWKMetm[ipt]->Integral());
	  sprintf(histName_org,"h1_Wp_Neu_pt_%d",ipt);
	  hEWKMetp[ipt]->Add((TH1D*)infile->Get(histName_org)->Clone(histName));
          if(ewkNumber == 2)nEventDYToTauTauP.push_back(hEWKMetp[ipt]->Integral());
          if(ewkNumber == 3)nEventTTJetsP.push_back(hEWKMetp[ipt]->Integral());
          if(ewkNumber == 4)nEventWToTauNuP.push_back(hEWKMetp[ipt]->Integral());

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
    sprintf(histName,"hWenuMet_%d",ipt);
    hWenuMet[ipt] = (TH1D*)hWenuMetp[ipt]->Clone(histName);
    hWenuMet[ipt]->Add(hWenuMetm[ipt]);
    sprintf(histName,"hAntiWenuMet_%d",ipt);
    hAntiWenuMet[ipt] = (TH1D*)hAntiWenuMetp[ipt]->Clone(histName);
    hAntiWenuMet[ipt]->Add(hAntiWenuMetm[ipt]);
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
  RooRealVar* gausMean;
  RooRealVar* gausMean_p;
  RooRealVar* gausMean_m;
  RooRealVar* gausSigma;
  RooRealVar* gausSigma_p;
  RooRealVar* gausSigma_m;
  RooGaussian* QCDGaus;
  RooGaussian* QCDGaus_p;
  RooGaussian* QCDGaus_m;
  RooRealVar* agausMean;
  RooRealVar* agausMean_p;
  RooRealVar* agausMean_m;
  RooRealVar* agausSigma;
  RooRealVar* agausSigma_p;
  RooRealVar* agausSigma_m;
  RooGaussian* aQCDGaus;
  RooGaussian* aQCDGaus_p;
  RooGaussian* aQCDGaus_m;
  RooRealVar* lanMean;
  RooRealVar* lanMean_p;
  RooRealVar* lanMean_m;
  RooRealVar* lanSigma;
  RooRealVar* lanSigma_p;
  RooRealVar* lanSigma_m;
  RooLandau* QCDLan;
  RooLandau* QCDLan_p;
  RooLandau* QCDLan_m;
  RooRealVar* alanMean;
  RooRealVar* alanMean_p;
  RooRealVar* alanMean_m;
  RooRealVar* alanSigma;
  RooRealVar* alanSigma_p;
  RooRealVar* alanSigma_m;
  RooLandau* aQCDLan;
  RooLandau* aQCDLan_p;
  RooLandau* aQCDLan_m;
  RooFFTConvPdf* QCDLxG;
  RooFFTConvPdf* QCDLxG_p;
  RooFFTConvPdf* QCDLxG_m;
  RooFFTConvPdf* aQCDLxG;
  RooFFTConvPdf* aQCDLxG_p;
  RooFFTConvPdf* aQCDLxG_m;
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
  RooDataHist* wenuMet ;RooHistPdf*pdfWm ;
  RooDataHist* wenuMetp;RooHistPdf*pdfWmp;
  RooDataHist* wenuMetm;RooHistPdf*pdfWmm; 
  RooDataHist* ewkMet ; RooHistPdf* pdfEWK ;
  RooDataHist* ewkMetp; RooHistPdf* pdfEWKp; 
  RooDataHist* ewkMetm; RooHistPdf* pdfEWKm; 
  RooAddPdf* pdfMet ;
  RooAddPdf* pdfMetp;
  RooAddPdf* pdfMetm;
  RooDataHist* awenuMet ; RooHistPdf* apdfWm ;
  RooDataHist* awenuMetp; RooHistPdf* apdfWmp;
  RooDataHist* awenuMetm; RooHistPdf* apdfWmm; 
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
  RooFitResult* afitRes;
  RooFitResult* afitResp;
  RooFitResult* afitResm;

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
  ofstream allyields;
  char allyieldsfname[100];    
  ofstream allyieldsp;
  char allyieldsfnamep[100];
  ofstream allyieldsm;
  char allyieldsfnamem[100];
  char txtfname[100];    
  ios_base::fmtflags flags;
  Double_t chi2prob, chi2ndf;
  Double_t ksprob, ksprobpe;

  Double_t RaySigma, RaySigma_p, RaySigma_m;
  Int_t NBINS;

  sprintf(allyieldsfname,"%s/AllYields.txt",CPlot::sOutDir.Data());
  allyields.open(allyieldsfname);
  assert(allyields.is_open());
//  allyields << " ********************** Inclusive W Yields ********************** " << endl;
//  allyields << "Bin #" << "\t" << " Signal " << "\t" << " Error " << endl;

  sprintf(allyieldsfnamep,"%s/AllYields_P.txt",CPlot::sOutDir.Data());
  allyieldsp.open(allyieldsfnamep);
  assert(allyieldsp.is_open());
//  allyieldsp << " ********************** W^{+} Yields ********************** " << endl;
//  allyieldsp << "Bin #" << "\t" << " Signal " << "\t" << " Error " << endl;

  sprintf(allyieldsfnamem,"%s/AllYields_M.txt",CPlot::sOutDir.Data());
  allyieldsm.open(allyieldsfnamem);
  assert(allyieldsm.is_open());
//  allyieldsm << " ********************** W^{-} Yields ********************** " << endl;
//  allyieldsm << "Bin #" << "\t" << " Signal " << "\t" << " Error " << endl;

//Create MET Fit Plots --> HTML file
  ofstream metplotsfile;
  char metplotsfname[100];
  sprintf(metplotsfname,"%s/fitMetPlots.html",CPlot::sOutDir.Data());
  metplotsfile.open(metplotsfname);
  metplotsfile << "<!DOCTYPE html" << endl;
  metplotsfile << "    PUBLIC \"-//W3C//DTD HTML 3.2//EN\">" << endl;
  metplotsfile << "<html>" << endl;
  metplotsfile << "<head><title>W pt All Bins MET Fit Results </title></head>" << endl;
  metplotsfile << "<body bgcolor=\"white\">" << endl;

//Create Yields Table --> HTML file
  ofstream tablefile;
  char tablefname[100];    
  sprintf(tablefname,"%s/AllYieldsTable.html",CPlot::sOutDir.Data());
  tablefile.open(tablefname);
  assert(tablefile.is_open());
  flags = tablefile.flags();
  tablefile << "<!DOCTYPE html" << endl;
  tablefile << "    PUBLIC \"-//W3C//DTD HTML 3.2//EN\">" << endl;
  tablefile << "<html>" << endl;
  tablefile << "<head><title>W pt All Bins Yields Table</title></head>" << endl;
  tablefile << "<body bgcolor=\"white\">" << endl;

//Write All Bin Yields Information to txt file
  ofstream Wmfile;
  char Wmfname[100];    
  sprintf(Wmfname,"%s/fitresWe_AllBin.txt",CPlot::sOutDir.Data());
  Wmfile.open(Wmfname);
  assert(Wmfile.is_open());
  Wmfile << " *** Inclusive W -- All Bin Yields Information *** " << endl;

  ofstream Wmpfile;
  char Wmpfname[100];    
  sprintf(Wmpfname,"%s/fitresWep_AllBin.txt",CPlot::sOutDir.Data());
  Wmpfile.open(Wmpfname);
  assert(Wmpfile.is_open());
  Wmpfile << " *** W plus -- All Bin Yields Information *** " << endl;

  ofstream Wmmfile;
  char Wmmfname[100];    
  sprintf(Wmmfname,"%s/fitresWem_AllBin.txt",CPlot::sOutDir.Data());
  Wmmfile.open(Wmmfname);
  assert(Wmmfile.is_open());
  Wmmfile << " *** W minus -- All Bin Yields Information *** " << endl;
  

  //Loop for each Wpt bins==============
  // 0 is the total
  for( int ipt(0);ipt<NWptBinPlus;ipt++)
  {
    nSig = new RooRealVar("nSig","nSig",0.7*(hDataMet[ipt]->Integral()),0,hDataMet[ipt]->Integral());
 if (ipt==1){
  nQCD = new RooRealVar("nQCD","nQCD",0.003*(hDataMet[ipt]->Integral()),0,hDataMet[ipt]->Integral());
  nQCDp = new RooRealVar("nQCDp","nQCDp",0.003*(hDataMetp[ipt]->Integral()),0,hDataMetp[ipt]->Integral());
  nQCDm = new RooRealVar("nQCDm","nQCDm",0.003*(hDataMetm[ipt]->Integral()),0,hDataMetm[ipt]->Integral());
  }else{
    nQCD = new RooRealVar("nQCD","nQCD",0.3*(hDataMet[ipt]->Integral()),0,hDataMet[ipt]->Integral());
    nQCDp = new RooRealVar("nQCDp","nQCDp",0.3*(hDataMetp[ipt]->Integral()),0,hDataMetp[ipt]->Integral());
    nQCDm = new RooRealVar("nQCDm","nQCDm",0.3*(hDataMetm[ipt]->Integral()),0,hDataMetm[ipt]->Integral());
  }
    cewk.setVal(hEWKMet[ipt]->Integral()/hWenuMet[ipt]->Integral());
    cewk.setConstant(kTRUE);
    nEWK = new RooFormulaVar("nEWK","nEWK","cewk*nSig",RooArgList(*nSig,cewk));
    nAntiSig = new RooRealVar("nAntiSig","nAntiSig",hAntiDataMet[ipt]->Integral(),0,hAntiDataMet[ipt]->Integral());
    //nAntiSig = new RooRealVar("nAntiSig","nAntiSig",0.05*(hAntiDataMet[ipt]->Integral()),0,hAntiDataMet[ipt]->Integral());
    nAntiQCD = new RooRealVar("nAntiQCD","nAntiQCD",0.9*(hAntiDataMet[ipt]->Integral()),0,hAntiDataMet[ipt]->Integral());
    //nAntiQCD = new RooRealVar("nAntiQCD","nAntiQCD",0.9*(hDataMet[ipt]->Integral()),0,hDataMet[ipt]->Integral());
    dewk.setVal(hAntiEWKMet[ipt]->Integral()/hAntiWenuMet[ipt]->Integral());
    dewk.setConstant(kTRUE);
    nAntiEWK = new RooFormulaVar("nAntiEWK","nAntiEWK","dewk*nAntiSig",RooArgList(*nAntiSig,dewk));
 
    nSigp = new RooRealVar("nSigp","nSigp",0.7*(hDataMetp[ipt]->Integral()),0,hDataMetp[ipt]->Integral());
    cewkp.setVal(hEWKMetp[ipt]->Integral()/hWenuMetp[ipt]->Integral());
    cewkp.setConstant(kTRUE);
    nEWKp = new RooFormulaVar("nEWKp","nEWKp","cewkp*nSigp",RooArgList(*nSigp,cewkp));
    nAntiSigp = new RooRealVar("nAntiSigp","nAntiSigp",hAntiDataMetp[ipt]->Integral(),0,hAntiDataMetp[ipt]->Integral());
    //nAntiSigp = new RooRealVar("nAntiSigp","nAntiSigp",0.05*(hAntiDataMetp[ipt]->Integral()),0,hAntiDataMetp[ipt]->Integral());
    nAntiQCDp = new RooRealVar("nAntiQCDp","nAntiQCDp",0.9*(hAntiDataMetp[ipt]->Integral()),0,hAntiDataMetp[ipt]->Integral());
    dewkp.setVal(hAntiEWKMetp[ipt]->Integral()/hAntiWenuMetp[ipt]->Integral());
    dewkp.setConstant(kTRUE);
    nAntiEWKp = new RooFormulaVar("nAntiEWKp","nAntiEWKp","dewkp*nAntiSigp",RooArgList(*nAntiSigp,dewkp));
  
    nSigm = new RooRealVar("nSigm","nSigm",0.7*(hDataMetm[ipt]->Integral()),0,hDataMetm[ipt]->Integral());
    cewkm.setVal(hEWKMetm[ipt]->Integral()/hWenuMetm[ipt]->Integral());
    cewkm.setConstant(kTRUE);
    nEWKm = new RooFormulaVar("nEWKm","nEWKm","cewkm*nSigm",RooArgList(*nSigm,cewkm));  
    nAntiSigm = new RooRealVar("nAntiSigm","nAntiSigm",hAntiDataMetm[ipt]->Integral(),0,hAntiDataMetm[ipt]->Integral());
    //nAntiSigm = new RooRealVar("nAntiSigm","nAntiSigm",0.05*(hAntiDataMetm[ipt]->Integral()),0,hAntiDataMetm[ipt]->Integral());
    nAntiQCDm = new RooRealVar("nAntiQCDm","nAntiQCDm",0.9*(hAntiDataMetm[ipt]->Integral()),0,hAntiDataMetm[ipt]->Integral());
    dewkm.setVal(hAntiEWKMetm[ipt]->Integral()/hAntiWenuMetm[ipt]->Integral());
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
  wenuMet  =new RooDataHist("wenuMET", "wenuMET", RooArgSet(pfmet),hWenuMet[ipt]); pdfWm =new RooHistPdf ("wm", "wm", pfmet,*wenuMet, 1);
  wenuMetp =new RooDataHist("wenuMETp","wenuMETp",RooArgSet(pfmet),hWenuMetp[ipt]);pdfWmp=new RooHistPdf ("wmp","wmp",pfmet,*wenuMetp,1);
  wenuMetm =new RooDataHist("wenuMETm","wenuMETm",RooArgSet(pfmet),hWenuMetm[ipt]);pdfWmm=new RooHistPdf ("wmm","wmm",pfmet,*wenuMetm,1); 
  // EWK+top PDFs
  ewkMet =new RooDataHist("ewkMET", "ewkMET", RooArgSet(pfmet),hEWKMet[ipt]); pdfEWK =new RooHistPdf ("ewk", "ewk", pfmet,*ewkMet, 1);
  ewkMetp=new RooDataHist("ewkMETp","ewkMETp",RooArgSet(pfmet),hEWKMetp[ipt]);pdfEWKp=new RooHistPdf ("ewkp","ewkp",pfmet,*ewkMetp,1); 
  ewkMetm=new RooDataHist("ewkMETm","ewkMETm",RooArgSet(pfmet),hEWKMetm[ipt]);pdfEWKm=new RooHistPdf ("ewkm","ewkm",pfmet,*ewkMetm,1); 
  
  // Anti-Signal PDFs
  awenuMet =new RooDataHist("awenuMET", "awenuMET", RooArgSet(pfmet),hAntiWenuMet[ipt]) ;
  awenuMetp=new RooDataHist("awenuMETp","awenuMETp",RooArgSet(pfmet),hAntiWenuMetp[ipt]);
  awenuMetm=new RooDataHist("awenuMETm","awenuMETm",RooArgSet(pfmet),hAntiWenuMetm[ipt]);
  apdfWm =new RooHistPdf("awm", "awm", pfmet,*awenuMet, 1);
  apdfWmp=new RooHistPdf("awmp","awmp",pfmet,*awenuMetp,1);
  apdfWmm=new RooHistPdf("awmm","awmm",pfmet,*awenuMetm,1); 
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
  if ( ipt <= NBIN_PT_DIVIDER_2and3) {
  // QCD Pdfs
  qcd =new CPepeModel1("qcd",pfmet);
  qcdp=new CPepeModel1("qcdp",pfmet);
  qcdm=new CPepeModel1("qcdm",pfmet);
  // Signal + Background PDFs
  pdfMet =new RooAddPdf("pdfMet", "pdfMet", RooArgList(*pdfWm, *pdfEWK, *(qcd->model)), RooArgList(*nSig, *nEWK, *nQCD));  
  pdfMetp=new RooAddPdf("pdfMetp","pdfMetp",RooArgList(*pdfWmp,*pdfEWKp,*(qcdp->model)),RooArgList(*nSigp,*nEWKp,*nQCDp));
  pdfMetm=new RooAddPdf("pdfMetm","pdfMetm",RooArgList(*pdfWmm,*pdfEWKm,*(qcdm->model)),RooArgList(*nSigm,*nEWKm,*nQCDm));

  aqcd =new CPepeModel1("aqcd",pfmet, qcd->a1);
  aqcdp=new CPepeModel1("aqcdp",pfmet,qcdp->a1);
  aqcdm=new CPepeModel1("aqcdm",pfmet,qcdm->a1);
  
  // Anti-selection PDFs
  apdfMet =new RooAddPdf("apdfMet", "apdfMet", RooArgList(*apdfWm,*apdfEWK,*(aqcd->model)),   RooArgList(*nAntiSig,*nAntiEWK,*nAntiQCD));  
  apdfMetp=new RooAddPdf("apdfMetp","apdfMetp",RooArgList(*apdfWmp,*apdfEWKp,*(aqcdp->model)),RooArgList(*nAntiSigp,*nAntiEWKp,*nAntiQCDp));
  apdfMetm=new RooAddPdf("apdfMetm","apdfMetm",RooArgList(*apdfWmm,*apdfEWKm,*(aqcdm->model)),RooArgList(*nAntiSigm,*nAntiEWKm,*nAntiQCDm));
  
  // PDF for simultaneous fit
  apdfTotal= new RooSimultaneous("apdfTotal","apdfTotal",rooCat);
  apdfTotal->addPdf(*pdfMet, "Select");
  apdfTotal->addPdf(*apdfMet,"Anti");
  
  apdfTotalp= new RooSimultaneous("apdfTotalp","apdfTotalp",rooCat);
  apdfTotalp->addPdf(*pdfMetp, "Select");
  apdfTotalp->addPdf(*apdfMetp,"Anti");
  
  apdfTotalm=new RooSimultaneous("apdfTotalm","apdfTotalm",rooCat);
  apdfTotalm->addPdf(*pdfMetm, "Select");
  apdfTotalm->addPdf(*apdfMetm,"Anti");
  //
  // Perform fits
  //
  afitRes = apdfTotal->fitTo(*dataTotal,Extended(),Minos(kTRUE),Save(kTRUE));
  afitResp = apdfTotalp->fitTo(*dataTotalp,Extended(),Minos(kTRUE),Save(kTRUE));
  afitResm = apdfTotalm->fitTo(*dataTotalm,Extended(),Minos(kTRUE),Save(kTRUE));

  RaySigma	= aqcd ->sigma->getValV();
  RaySigma_p	= aqcdp->sigma->getValV();
  RaySigma_m	= aqcdm->sigma->getValV();

// Anti-selection PDFs using Convoluted Landau and Gaussian Functions

  alanMean   = new RooRealVar("alanMean","Mean",20,0,METMAX);
  alanMean_p = new RooRealVar("alanMean_p","Mean",20,0,METMAX);
  alanMean_m = new RooRealVar("alanMean_m","Mean",20,0,METMAX);
  alanSigma  = new RooRealVar("alanSigma","Sigma",RaySigma,0,METMAX);
  alanSigma_p= new RooRealVar("alanSigma_p","Sigma",RaySigma_p,0,METMAX);
  alanSigma_m= new RooRealVar("alanSigma_m","Sigma",RaySigma_m,0,METMAX);
  agausSigma  = new RooRealVar("agausSigma","Gaussian Sigma",RaySigma,0,METMAX);
  agausSigma_p= new RooRealVar("agausSigma_p","Gaussian Sigma",RaySigma_p,0,METMAX);
  agausSigma_m= new RooRealVar("agausSigma_m","Gaussian Sigma",RaySigma_m,0,METMAX);
  }else{
  alanMean	-> setConstant(kTRUE);
  alanMean_p	-> setConstant(kTRUE);
  alanMean_m	-> setConstant(kTRUE);
  alanSigma	-> setConstant(kTRUE);
  alanSigma_p	-> setConstant(kTRUE);
  alanSigma_m	-> setConstant(kTRUE);
  agausSigma	-> setConstant(kTRUE);
  agausSigma_p	-> setConstant(kTRUE);
  agausSigma_m	-> setConstant(kTRUE);
  }
  agausMean	= new RooRealVar("agausMean","Gaussian Mean",0);
  agausMean_p	= new RooRealVar("agausMean_p","Gaussian Mean",0);
  agausMean_m	= new RooRealVar("agausMean_m","Gaussian Mean",0);
  aQCDLan	= new RooLandau ("aQCDLan","Landau PDF",pfmet,*alanMean,*alanSigma);
  aQCDLan_p	= new RooLandau ("aQCDLan_p","Landau PDF",pfmet,*alanMean_p,*alanSigma_p);
  aQCDLan_m	= new RooLandau ("aQCDLan_m","Landau PDF",pfmet,*alanMean_m,*alanSigma_m);
  aQCDGaus	= new RooGaussian ("aQCDGaus","Gaussian PDF",pfmet,*agausMean,*agausSigma);
  aQCDGaus_p	= new RooGaussian ("aQCDGaus_p","Gaussian PDF",pfmet,*agausMean_p,*agausSigma_p);
  aQCDGaus_m	= new RooGaussian ("aQCDGaus_m","Gaussian PDF",pfmet,*agausMean_m,*agausSigma_m);
  aQCDLxG	= new RooFFTConvPdf ("aQCDLxG","Landau (X) Gauss",pfmet,*aQCDLan,*aQCDGaus);
  aQCDLxG_p	= new RooFFTConvPdf ("aQCDLxG_p","Landau (X) Gauss",pfmet,*aQCDLan_p,*aQCDGaus_p);
  aQCDLxG_m	= new RooFFTConvPdf ("aQCDLxG_m","Landau (X) Gauss",pfmet,*aQCDLan_m,*aQCDGaus_m);
  apdfMet	= new RooAddPdf("apdfMet", "apdfMet", RooArgList(*apdfWm ,*apdfEWK, *aQCDLxG),  RooArgList(*nAntiSig, *nAntiEWK, *nAntiQCD));  
  apdfMetp	= new RooAddPdf("apdfMetp","apdfMetp",RooArgList(*apdfWmp,*apdfEWKp,*aQCDLxG_p),RooArgList(*nAntiSigp,*nAntiEWKp,*nAntiQCDp));
  apdfMetm	= new RooAddPdf("apdfMetm","apdfMetm",RooArgList(*apdfWmm,*apdfEWKm,*aQCDLxG_m),RooArgList(*nAntiSigm,*nAntiEWKm,*nAntiQCDm));

// QCD Pdfs using Convoluted Landau and Gaussian Functions
  lanMean   = new RooRealVar("lanMean","Mean",20,0,METMAX);
  lanMean_p = new RooRealVar("lanMean_p","Mean",20,0,METMAX);
  lanMean_m = new RooRealVar("lanMean_m","Mean",20,0,METMAX);
  lanSigma  = new RooRealVar("lanSigma","Sigma",30,0,METMAX);
  lanSigma_p= new RooRealVar("lanSigma_p","Sigma",30,0,METMAX);
  lanSigma_m= new RooRealVar("lanSigma_m","Sigma",30,0,METMAX);
  QCDLan	= new RooLandau ("QCDLan","Landau PDF",pfmet,*alanMean,*alanSigma);
  QCDLan_p	= new RooLandau ("QCDLan_p","Landau PDF",pfmet,*alanMean_p,*alanSigma_p);
  QCDLan_m	= new RooLandau ("QCDLan_m","Landau PDF",pfmet,*alanMean_m,*alanSigma_m);
//    QCDLan	= new RooLandau ("QCDLan","Landau PDF",pfmet,*lanMean,*lanSigma);
//    QCDLan_p  = new RooLandau ("QCDLan_p","Landau PDF",pfmet,*lanMean_p,*lanSigma_p);
//    QCDLan_m  = new RooLandau ("QCDLan_m","Landau PDF",pfmet,*lanMean_m,*lanSigma_m);
  gausMean	= new RooRealVar("gausMean","Gaussian Mean",0);
  gausMean_p	= new RooRealVar("gausMean_p","Gaussian Mean",0);
  gausMean_m	= new RooRealVar("gausMean_m","Gaussian Mean",0);
  gausSigma	= new RooRealVar("gausSigma","Gaussian Sigma",30,0,METMAX);
  gausSigma_p	= new RooRealVar("gausSigma_p","Gaussian Sigma",30,0,METMAX);
  gausSigma_m	= new RooRealVar("gausSigma_m","Gaussian Sigma",30,0,METMAX);
  QCDGaus	= new RooGaussian ("QCDGaus","Gaussian PDF",pfmet,*agausMean,*agausSigma);
  QCDGaus_p	= new RooGaussian ("QCDGaus_p","Gaussian PDF",pfmet,*agausMean_p,*agausSigma_p);
  QCDGaus_m	= new RooGaussian ("QCDGaus_m","Gaussian PDF",pfmet,*agausMean_m,*agausSigma_m);
//    QCDGaus    = new RooGaussian ("QCDGaus","Gaussian PDF",pfmet,*gausMean,*gausSigma);
//    QCDGaus_p  = new RooGaussian ("QCDGaus_p","Gaussian PDF",pfmet,*gausMean_p,*gausSigma_p);
//    QCDGaus_m  = new RooGaussian ("QCDGaus_m","Gaussian PDF",pfmet,*gausMean_m,*gausSigma_m);
  QCDLxG	= new RooFFTConvPdf ("QCDLxG","Landau (X) Gauss",pfmet,*QCDLan,*QCDGaus);
  QCDLxG_p	= new RooFFTConvPdf ("QCDLxG_p","Landau (X) Gauss",pfmet,*QCDLan_p,*QCDGaus_p);
  QCDLxG_m	= new RooFFTConvPdf ("QCDLxG_m","Landau (X) Gauss",pfmet,*QCDLan_m,*QCDGaus_m);
  pdfMet	= new RooAddPdf("pdfMet", "pdfMet", RooArgList(*pdfWm ,*pdfEWK, *QCDLxG),RooArgList(*nSig, *nEWK, *nQCD));  
  pdfMetp	= new RooAddPdf("pdfMetp","pdfMetp",RooArgList(*pdfWmp,*pdfEWKp,*QCDLxG_p),RooArgList(*nSigp,*nEWKp,*nQCDp));
  pdfMetm	= new RooAddPdf("pdfMetm","pdfMetm",RooArgList(*pdfWmm,*pdfEWKm,*QCDLxG_m),RooArgList(*nSigm,*nEWKm,*nQCDm));

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

  if( ipt == 0 )
  {
//Write MET Histogram to file
  char metfname[100];
  if (filetype == "BeforeRC"){
  sprintf(metfname,"%s/MET_BeforeRC.root",CPlot::sOutDir.Data());
  }else if (filetype == "Nominal"){
  sprintf(metfname,"%s/MET_AfterRC.root",CPlot::sOutDir.Data());
  }
  TFile *metfile = new TFile(metfname,"RECREATE");
  RooAddPdf* pdfWenu0Met;
  RooAddPdf* pdfWenu0Metp;
  RooAddPdf* pdfWenu0Metm;
  RooAddPdf* pdfEWK0Met;
  RooAddPdf* pdfEWK0Metp;
  RooAddPdf* pdfEWK0Metm;
  RooAddPdf* pdfQCD0Met;
  RooAddPdf* pdfQCD0Metp;
  RooAddPdf* pdfQCD0Metm;

  TH1D* hWenu0;
  TH1D* hWenu0p;
  TH1D* hWenu0m;
  TH1D* hEWK0;
  TH1D* hEWK0p;
  TH1D* hEWK0m;
  TH1D* hQCD0;
  TH1D* hQCD0p;
  TH1D* hQCD0m;

  pdfWenu0Met	= new RooAddPdf("pdfWenu0Met", "pdfWenu0Met", RooArgList(*pdfWm),RooArgList(*nSig));  
  pdfWenu0Metp	= new RooAddPdf("pdfWenu0Metp","pdfWenu0Metp",RooArgList(*pdfWmp),RooArgList(*nSigp));
  pdfWenu0Metm	= new RooAddPdf("pdfWenu0Metm","pdfWenu0Metm",RooArgList(*pdfWmm),RooArgList(*nSigm));

  pdfEWK0Met	= new RooAddPdf("pdfEWK0Met", "pdfEWK0Met", RooArgList(*pdfEWK),RooArgList(*nEWK));  
  pdfEWK0Metp	= new RooAddPdf("pdfEWK0Metp","pdfEWK0Metp",RooArgList(*pdfEWKp),RooArgList(*nEWKp));
  pdfEWK0Metm	= new RooAddPdf("pdfEWK0Metm","pdfEWK0Metm",RooArgList(*pdfEWKm),RooArgList(*nEWKm));

  pdfQCD0Met	= new RooAddPdf("pdfQCD0Met", "pdfQCD0Met", RooArgList(*QCDLxG),RooArgList(*nQCD));  
  pdfQCD0Metp	= new RooAddPdf("pdfQCD0Metp","pdfQCD0Metp",RooArgList(*QCDLxG_p),RooArgList(*nQCDp));
  pdfQCD0Metm	= new RooAddPdf("pdfQCD0Metm","pdfQCD0Metm",RooArgList(*QCDLxG_m),RooArgList(*nQCDm));

  hWenu0 = (TH1D*)(pdfWenu0Met->createHistogram("hWenu0", pfmet));
  hWenu0->Scale((nSig->getVal())/hWenu0->Integral());
  hWenu0p = (TH1D*)(pdfWenu0Metp->createHistogram("hWenu0p", pfmet));
  hWenu0p->Scale((nSigp->getVal())/hWenu0p->Integral());
  hWenu0m = (TH1D*)(pdfWenu0Metm->createHistogram("hWenu0m", pfmet));
  hWenu0m->Scale((nSigm->getVal())/hWenu0m->Integral());

  hEWK0 = (TH1D*)(pdfEWK0Met->createHistogram("hEWK0", pfmet));
  hEWK0->Scale((nEWK->getVal())/hEWK0->Integral());
  hEWK0p = (TH1D*)(pdfEWK0Metp->createHistogram("hEWK0p", pfmet));
  hEWK0p->Scale((nEWKp->getVal())/hEWK0p->Integral());
  hEWK0m = (TH1D*)(pdfEWK0Metm->createHistogram("hEWK0m", pfmet));
  hEWK0m->Scale((nEWKm->getVal())/hEWK0m->Integral());

  hQCD0 = (TH1D*)(pdfQCD0Met->createHistogram("hQCD0", pfmet));
  hQCD0->Scale((nQCD->getVal())/hQCD0->Integral());
  hQCD0p = (TH1D*)(pdfQCD0Metp->createHistogram("hQCD0p", pfmet));
  hQCD0p->Scale((nQCDp->getVal())/hQCD0p->Integral());
  hQCD0m = (TH1D*)(pdfQCD0Metm->createHistogram("hQCD0m", pfmet));
  hQCD0m->Scale((nQCDm->getVal())/hQCD0m->Integral());

  hDataMet[ipt]->Write();
  hDataMetp[ipt]->Write();
  hDataMetm[ipt]->Write();
  hWenu0->Write();
  hWenu0p->Write();
  hWenu0m->Write();
  hEWK0->Write();
  hEWK0p->Write();
  hEWK0m->Write();
  hQCD0->Write();
  hQCD0p->Write();
  hQCD0m->Write();
  metfile->Close();
  }

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

  pdfMet->plotOn(wmframe,Components(RooArgSet(*pdfEWK,*QCDLxG)),FillColor(fillcolorEWK),DrawOption("F"));
  pdfMet->plotOn(wmframe,Components(RooArgSet(*pdfEWK,*QCDLxG)),LineColor(linecolorEWK));
  pdfMet->plotOn(wmframe,Components(RooArgSet(*QCDLxG)),FillColor(fillcolorQCD),DrawOption("F"));
  pdfMet->plotOn(wmframe,Components(RooArgSet(*QCDLxG)),LineColor(linecolorQCD));
  pdfMet->plotOn(wmframe,Components(RooArgSet(*pdfWm)),LineColor(linecolorW),LineStyle(2));
  dataMet->plotOn(wmframe,MarkerStyle(kFullCircle),MarkerSize(0.9),DrawOption("ZP"));  
  
  sprintf(ylabel,"Events / %.1f GeV",hDataMet[ipt]->GetBinWidth(1));
  sprintf(histName,"fitMet_%d",ipt);
  plotMet=new CPlot(histName,wmframe,"","",ylabel);
  plotMet->setOutDir(CPlot::sOutDir);
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

  apdfMet->plotOn(awmframe,Components(RooArgSet(*apdfEWK,*aQCDLxG)),FillColor(fillcolorEWK),DrawOption("F"));
  apdfMet->plotOn(awmframe,Components(RooArgSet(*apdfEWK,*aQCDLxG)),LineColor(linecolorEWK));
  apdfMet->plotOn(awmframe,Components(RooArgSet(*aQCDLxG)),FillColor(fillcolorQCD),DrawOption("F"));
  apdfMet->plotOn(awmframe,Components(RooArgSet(*aQCDLxG)),LineColor(linecolorQCD));
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

  pdfMetp->plotOn(wmpframe,Components(RooArgSet(*pdfEWKp,*QCDLxG_p)),FillColor(fillcolorEWK),DrawOption("F"));
  pdfMetp->plotOn(wmpframe,Components(RooArgSet(*pdfEWKp,*QCDLxG_p)),LineColor(linecolorEWK));
  pdfMetp->plotOn(wmpframe,Components(RooArgSet(*QCDLxG_p)),FillColor(fillcolorQCD),DrawOption("F"));
  pdfMetp->plotOn(wmpframe,Components(RooArgSet(*QCDLxG_p)),LineColor(linecolorQCD));
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

  apdfMetp->plotOn(awmpframe,Components(RooArgSet(*apdfEWKp,*aQCDLxG_p)),FillColor(fillcolorEWK),DrawOption("F"));
  apdfMetp->plotOn(awmpframe,Components(RooArgSet(*apdfEWKp,*aQCDLxG_p)),LineColor(linecolorEWK));
  apdfMetp->plotOn(awmpframe,Components(RooArgSet(*aQCDLxG_p)),FillColor(fillcolorQCD),DrawOption("F"));
  apdfMetp->plotOn(awmpframe,Components(RooArgSet(*aQCDLxG_p)),LineColor(linecolorQCD));
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

  pdfMetm->plotOn(wmmframe,Components(RooArgSet(*pdfEWKm,*QCDLxG_m)),FillColor(fillcolorEWK),DrawOption("F"));
  pdfMetm->plotOn(wmmframe,Components(RooArgSet(*pdfEWKm,*QCDLxG_m)),LineColor(linecolorEWK));
  pdfMetm->plotOn(wmmframe,Components(RooArgSet(*QCDLxG_m)),FillColor(fillcolorQCD),DrawOption("F"));
  pdfMetm->plotOn(wmmframe,Components(RooArgSet(*QCDLxG_m)),LineColor(linecolorQCD));
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

  apdfMetm->plotOn(awmmframe,Components(RooArgSet(*apdfEWKm,*aQCDLxG_m)),FillColor(fillcolorEWK),DrawOption("F"));
  apdfMetm->plotOn(awmmframe,Components(RooArgSet(*apdfEWKm,*aQCDLxG_m)),LineColor(linecolorEWK));
  apdfMetm->plotOn(awmmframe,Components(RooArgSet(*aQCDLxG_m)),FillColor(fillcolorQCD),DrawOption("F"));
  apdfMetm->plotOn(awmmframe,Components(RooArgSet(*aQCDLxG_m)),LineColor(linecolorQCD));
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
  
  flags = allyields.flags();
  allyields << fixed << setprecision(1);
  allyields << "Bin" << "\t" << ipt << "\t" <<"Signal" << "\t" << nSig->getVal() << "\t" << "Error" << "\t" << nSig->getPropagatedError(*fitRes) << endl;
  allyields.flags(flags);

  flags = allyieldsp.flags();
  allyieldsp << fixed << setprecision(1);
  allyieldsp << "Bin" << "\t" << ipt << "\t" <<"Signal" << "\t" << nSigp->getVal() << "\t" << "Error" << "\t" << nSigp->getPropagatedError(*fitResp) << endl;
  allyieldsp.flags(flags);

  flags = allyieldsm.flags();
  allyieldsm << fixed << setprecision(1);
  allyieldsm << "Bin" << "\t" << ipt << "\t" <<"Signal" << "\t" << nSigm->getVal() << "\t" << "Error" << "\t" << nSigm->getPropagatedError(*fitResm) << endl;
  allyieldsm.flags(flags);

  chi2prob = hDataMet[ipt]->Chi2Test(hPdfMet,"PUW");
  chi2ndf  = hDataMet[ipt]->Chi2Test(hPdfMet,"CHI2/NDFUW");
  ksprob   = hDataMet[ipt]->KolmogorovTest(hPdfMet);
  ksprobpe = hDataMet[ipt]->KolmogorovTest(hPdfMet,"DX");

  flags = Wmfile.flags();
  if (ipt==0)
  Wmfile << "============================================== [0, 300] Bin - " << ipt << " ==============================================" << endl;
  else
  Wmfile << "============================================== [" << WptBins[ipt-1] << ", " << WptBins[ipt] << "] Bin - " << ipt << " ==============================================" << endl;
  Wmfile << endl;
  Wmfile << fixed << setprecision(4);
  Wmfile << "Selected: " << hDataMet[ipt]->Integral() << endl;
  Wmfile << "  Signal: " << nSig->getVal() << " +/- " << nSig->getPropagatedError(*fitRes) << endl;
  Wmfile << "     QCD: " << nQCD->getVal() << " +/- " << nQCD->getPropagatedError(*fitRes) << endl;
  Wmfile << "   Other: " << nEWK->getVal() << " +/- " << nEWK->getPropagatedError(*fitRes) << endl;
  Wmfile << "   Total: " << nSig->getVal()+nQCD->getVal()+nEWK->getVal() << endl;
  Wmfile << endl;
  Wmfile.flags(flags);
  
  fitRes->printStream(Wmfile,RooPrintable::kValue,RooPrintable::kVerbose);
  Wmfile << endl;
  printCorrelations(Wmfile, fitRes);
  Wmfile << endl;
  printChi2AndKSResults(Wmfile, chi2prob, chi2ndf, ksprob, ksprobpe);
  
  chi2prob = hDataMetp[ipt]->Chi2Test(hPdfMetp,"PUW");
  chi2ndf  = hDataMetp[ipt]->Chi2Test(hPdfMetp,"CHI2/NDFUW");
  ksprob   = hDataMetp[ipt]->KolmogorovTest(hPdfMetp);
  ksprobpe = hDataMetp[ipt]->KolmogorovTest(hPdfMetp,"DX");  
  
  flags = Wmpfile.flags();
  if (ipt==0)
  Wmpfile << "============================================== [0, 300] Bin - " << ipt << " ==============================================" << endl;
  else
  Wmpfile << "============================================== [" << WptBins[ipt-1] << ", " << WptBins[ipt] << "] Bin - " << ipt << " ==============================================" << endl;
  Wmpfile << fixed << setprecision(4);
  Wmpfile << endl;
  Wmpfile << "Selected: " << hDataMetp[ipt]->Integral() << endl;
  Wmpfile << "  Signal: " << nSigp->getVal() << " +/- " << nSigp->getPropagatedError(*fitResp) << endl;
  Wmpfile << "     QCD: " << nQCDp->getVal() << " +/- " << nQCDp->getPropagatedError(*fitResp) << endl;
  Wmpfile << "   Other: " << nEWKp->getVal() << " +/- " << nEWKp->getPropagatedError(*fitResp) << endl;
  Wmpfile << "   Total: " << nSigp->getVal()+nQCDp->getVal()+nEWKp->getVal() << endl;
  Wmpfile << endl; 
  Wmpfile.flags(flags);
  
  fitResp->printStream(Wmpfile,RooPrintable::kValue,RooPrintable::kVerbose);
  Wmpfile << endl;
  printCorrelations(Wmpfile, fitResp);
  Wmpfile << endl;
  printChi2AndKSResults(Wmpfile, chi2prob, chi2ndf, ksprob, ksprobpe);

  chi2prob = hDataMetm[ipt]->Chi2Test(hPdfMetm,"PUW");
  chi2ndf  = hDataMetm[ipt]->Chi2Test(hPdfMetm,"CHI2/NDFUW");
  ksprob   = hDataMetm[ipt]->KolmogorovTest(hPdfMetm);
  ksprobpe = hDataMetm[ipt]->KolmogorovTest(hPdfMetm,"DX");  

  flags = Wmmfile.flags();
  if (ipt==0)
  Wmmfile << "============================================== [0, 300] Bin - " << ipt << " ==============================================" << endl;
  else
  Wmmfile << "============================================== [" << WptBins[ipt-1] << ", " << WptBins[ipt] << "] Bin - " << ipt << " ==============================================" << endl;
  Wmmfile << endl;
  Wmmfile << fixed << setprecision(4);
  Wmmfile << "Selected: " << hDataMetm[ipt]->Integral() << endl;
  Wmmfile << "  Signal: " << nSigm->getVal() << " +/- " << nSigm->getPropagatedError(*fitResm) << endl;
  Wmmfile << "     QCD: " << nQCDm->getVal() << " +/- " << nQCDm->getPropagatedError(*fitResm) << endl;
  Wmmfile << "   Other: " << nEWKm->getVal() << " +/- " << nEWKm->getPropagatedError(*fitResm) << endl;
  Wmmfile << "   Total: " << nSigm->getVal()+nQCDm->getVal()+nEWKm->getVal() << endl;
  Wmmfile << endl;
  Wmmfile.flags(flags);
  
  fitResm->printStream(Wmmfile,RooPrintable::kValue,RooPrintable::kVerbose);
  Wmmfile << endl;
  printCorrelations(Wmmfile, fitResm);
  Wmmfile << endl;
  printChi2AndKSResults(Wmmfile, chi2prob, chi2ndf, ksprob, ksprobpe);

/*
  sprintf(txtfname,"%s/ShapesAntiWm_%d.txt",CPlot::sOutDir.Data(),ipt);
  txtfile.open(txtfname);
  assert(txtfile.is_open());
  
  flags = txtfile.flags();
  txtfile << fixed << setprecision(4);
  txtfile << " *** Control region Shape Parameters for the Pt Bin #"<< ipt << endl;
  txtfile << "Landau Mean is: " << alanMean->getValV() << endl;
  txtfile << "Landau Plus Mean is: " << alanMean_p->getValV() << endl;
  txtfile << "Landau Minus Mean is: " << alanMean_m->getValV() << endl;
  txtfile << "Landau Sigma is: " << alanSigma->getValV() << endl;
  txtfile << "Landau Plus Sigma is: " << alanSigma_p->getValV() << endl;
  txtfile << "Landau Minus Sigma is: " << alanSigma_m->getValV() << endl;
  txtfile << "Gaussian Sigma is: " << agausSigma->getValV() << endl;
  txtfile << "Gaussian Plus Sigma is: " << agausSigma_p->getValV() << endl;
  txtfile << "Gaussian Minus Sigma is: " << agausSigma_m->getValV() << endl;
  txtfile << endl; 
  txtfile.flags(flags);
  txtfile << endl;
  txtfile.close();
  sprintf(txtfname,"%s/ShapesWm_%d.txt",CPlot::sOutDir.Data(),ipt);
  txtfile.open(txtfname);
  assert(txtfile.is_open());
  
  flags = txtfile.flags();
  txtfile << fixed << setprecision(4);
  txtfile << " *** Signal region Shape Parameters for the Pt Bin #" << ipt << endl;
  txtfile << "Landau Mean is: " << lanMean->getValV() << endl;
  txtfile << "Landau Plus Mean is: " << lanMean_p->getValV() << endl;
  txtfile << "Landau Minus Mean is: " << lanMean_m->getValV() << endl;
  txtfile << "Landau Sigma is: " << lanSigma->getValV() << endl;
  txtfile << "Landau Plus Sigma is: " << lanSigma_p->getValV() << endl;
  txtfile << "Landau Minus Sigma is: " << lanSigma_m->getValV() << endl;
  txtfile << "Gaussian Sigma is: " << gausSigma->getValV() << endl;
  txtfile << "Gaussian Plus Sigma is: " << gausSigma_p->getValV() << endl;
  txtfile << "Gaussian Minus Sigma is: " << gausSigma_m->getValV() << endl;
  txtfile << endl; 
  txtfile.flags(flags);
  txtfile << endl;
  txtfile.close();
*/
  metplotsfile << "<hr />" << endl;
  if (ipt==0)
  metplotsfile << "<p align=\"center\"> [0, 300] Bin - " << ipt << "</p>" << endl;
  else
  metplotsfile << "<p align=\"center\"> [" << WptBins[ipt-1] << ", " << WptBins[ipt] << "] Bin - " << ipt << "</p>" << endl;
  metplotsfile << "<table border=\"0\" cellspacing=\"5\" width=\"900\" align=\"center\">" << endl; 
  metplotsfile << "<tr>" << endl;
  metplotsfile << "<td width=\"100\"></td>" << endl;
  metplotsfile << "<td width=\"400\" colspan=\"2\"><p align=\"center\" style=\"font-size:small\"> Signal </p></td>" << endl;
  metplotsfile << "<td width=\"400\" colspan=\"2\"><p align=\"center\" style=\"font-size:small\"> Side </p></td>" << endl;
  metplotsfile << "</tr>" << endl;
  metplotsfile << "<tr>" << endl;
  metplotsfile << "<td width=\"100\"><p align=\"center\" style=\"font-size:small\"> W </p></td>" << endl;
  metplotsfile << "<td width=\"200\"><a target=\"_blank\" href=\"fitMet_" << ipt <<".png\"><img src=\"fitMet_" << ipt <<".png\" width=\"200\" alt=\"fitMet_" << ipt <<".png\"></a></td>" << endl;
  metplotsfile << "<td width=\"200\"><a target=\"_blank\" href=\"fitMetLog_" << ipt <<".png\"><img src=\"fitMetLog_" << ipt <<".png\" width=\"200\" alt=\"fitMetLog_" << ipt <<".png\"></a></td>" << endl;
  metplotsfile << "<td width=\"200\"><a target=\"_blank\" href=\"fitAntiMet_" << ipt <<".png\"><img src=\"fitAntiMet_" << ipt <<".png\" width=\"200\" alt=\"fitAntiMet_" << ipt <<".png\"></a></td>" << endl;
  metplotsfile << "<td width=\"200\"><a target=\"_blank\" href=\"fitAntiMetLog_" << ipt <<".png\"><img src=\"fitAntiMetLog_" << ipt <<".png\" width=\"200\" alt=\"fitAntiMetLog_" << ipt <<".png\"></a></td>" << endl;
  metplotsfile << "</tr>" << endl;
  metplotsfile << "<tr>" << endl;
  metplotsfile << "<td width=\"100\"><p align=\"center\" style=\"font-size:small\"> W <sup>+</sup> </p></td>" << endl;
  metplotsfile << "<td width=\"200\"><a target=\"_blank\" href=\"fitMetP_" << ipt <<".png\"><img src=\"fitMetP_" << ipt <<".png\" width=\"200\" alt=\"fitMetP_" << ipt <<".png\"></a></td>" << endl;
  metplotsfile << "<td width=\"200\"><a target=\"_blank\" href=\"fitMetPLog_" << ipt <<".png\"><img src=\"fitMetPLog_" << ipt <<".png\" width=\"200\" alt=\"fitMetPLog_" << ipt <<".png\"></a></td>" << endl;
  metplotsfile << "<td width=\"200\"><a target=\"_blank\" href=\"fitAntiMetP_" << ipt <<".png\"><img src=\"fitAntiMetP_" << ipt <<".png\" width=\"200\" alt=\"fitAntiMetP_" << ipt <<".png\"></a></td>" << endl;
  metplotsfile << "<td width=\"200\"><a target=\"_blank\" href=\"fitAntiMetPLog_" << ipt <<".png\"><img src=\"fitAntiMetPLog_" << ipt <<".png\" width=\"200\" alt=\"fitAntiMetPLog_" << ipt <<".png\"></a></td>" << endl;
  metplotsfile << "</tr>" << endl;
  metplotsfile << "<tr>" << endl;
  metplotsfile << "<td width=\"100\"><p align=\"center\" style=\"font-size:small\"> W <sup>-</sup></p></td>" << endl;
  metplotsfile << "<td width=\"200\"><a target=\"_blank\" href=\"fitMetM_" << ipt <<".png\"><img src=\"fitMetM_" << ipt <<".png\" width=\"200\" alt=\"fitMetM_" << ipt <<".png\"></a></td>" << endl;
  metplotsfile << "<td width=\"200\"><a target=\"_blank\" href=\"fitMetMLog_" << ipt <<".png\"><img src=\"fitMetMLog_" << ipt <<".png\" width=\"200\" alt=\"fitMetMLog_" << ipt <<".png\"></a></td>" << endl;
  metplotsfile << "<td width=\"200\"><a target=\"_blank\" href=\"fitAntiMetM_" << ipt <<".png\"><img src=\"fitAntiMetM_" << ipt <<".png\" width=\"200\" alt=\"fitAntiMetM_" << ipt <<".png\"></a></td>" << endl;
  metplotsfile << "<td width=\"200\"><a target=\"_blank\" href=\"fitAntiMetMLog_" << ipt <<".png\"><img src=\"fitAntiMetMLog_" << ipt <<".png\" width=\"200\" alt=\"fitAntiMetMLog_" << ipt <<".png\"></a></td>" << endl;
  metplotsfile << "</tr>" << endl;
  metplotsfile << "</table>" << endl;

  if (ipt==0)
  tablefile << "<p align=\"center\">  [0, 300] Bin - "<< ipt <<" Yields </p>" << endl;
  else
  tablefile << setprecision(0) <<"<p align=\"center\"> [" << WptBins[ipt-1] << ", " << WptBins[ipt] << "] Bin - "<< ipt <<" Yields </p>" << endl;
  tablefile << "<table border=\"1\" style=\"border-collapse: collapse\" bordercolor=\"black\" cellspacing=\"6\" width=\"880\" align=\"center\">" << endl;
  tablefile << "<tr>" << endl;
  tablefile << "<td width=\"60\"></td>" << endl;
  tablefile << "<td width=\"100\"><p> Selected</p></td>" << endl;
  tablefile << "<td width=\"180\"><p> Total</p></td>" << endl;
  tablefile << "<td width=\"180\"><p> Signal</p></td>" << endl;
  tablefile << "<td width=\"180\"><p> QCD</p></td>" << endl;
  tablefile << "<td width=\"180\"><p> Others</p></td>" << endl;
  tablefile << "</tr>" << endl;
  tablefile << fixed << setprecision(1);
  tablefile << "<tr>" << endl;
  tablefile << "<td width=\"60\"><p> W</p></td>" << endl;
  tablefile << "<td width=\"100\"><p>"<< hDataMet[ipt]->Integral() <<"</p></td>" << endl;
  tablefile << "<td width=\"180\"><p>"<< nSig->getVal()+nQCD->getVal()+nEWK->getVal() << " &plusmn; " << sqrt(nSig->getPropagatedError(*fitRes)*nSig->getPropagatedError(*fitRes)+nQCD->getPropagatedError(*fitRes)*nQCD->getPropagatedError(*fitRes)+nEWK->getPropagatedError(*fitRes)*nEWK->getPropagatedError(*fitRes)) << "</p></td>" << endl;
  tablefile << "<td width=\"180\"><p>"<< nSig->getVal() << " &plusmn; " << nSig->getPropagatedError(*fitRes) << "</p></td>" << endl;
  tablefile << "<td width=\"180\"><p>"<< nQCD->getVal() << " &plusmn; " << nQCD->getPropagatedError(*fitRes) << "</p></td>" << endl;
  tablefile << "<td width=\"180\"><p>"<< nEWK->getVal() << " &plusmn; " << nEWK->getPropagatedError(*fitRes) << "</p></td>" << endl;
  tablefile << "</tr>" << endl;
  tablefile << "<tr>" << endl;
  tablefile << "<td width=\"60\"><p> W <sup>+</sup></p></td>" << endl;
  tablefile << "<td width=\"100\"><p>"<< hDataMetp[ipt]->Integral() <<"</p></td>" << endl;
  tablefile << "<td width=\"180\"><p>"<< nSigp->getVal()+nQCDp->getVal()+nEWKp->getVal() << " &plusmn; " << sqrt(nSigp->getPropagatedError(*fitResp)*nSigp->getPropagatedError(*fitResp)+nQCDp->getPropagatedError(*fitResp)*nQCDp->getPropagatedError(*fitResp)+nEWKp->getPropagatedError(*fitResp)*nEWKp->getPropagatedError(*fitResp)) << "</p></td>" << endl;
  tablefile << "<td width=\"180\"><p>"<< nSigp->getVal() << " &plusmn; " << nSigp->getPropagatedError(*fitResp) << "</p></td>" << endl;
  tablefile << "<td width=\"180\"><p>"<< nQCDp->getVal() << " &plusmn; " << nQCDp->getPropagatedError(*fitResp) << "</p></td>" << endl;
  tablefile << "<td width=\"180\"><p>"<< nEWKp->getVal() << " &plusmn; " << nEWKp->getPropagatedError(*fitResp) << "</p></td>" << endl;
  tablefile << "</tr>" << endl;
  tablefile << "<tr>" << endl;
  tablefile << "<td width=\"60\"><p> W <sup>-</sup></p></td>" << endl;
  tablefile << "<td width=\"100\"><p>"<< hDataMetm[ipt]->Integral() <<"</p></td>" << endl;
  tablefile << "<td width=\"180\"><p>"<< nSigm->getVal()+nQCDm->getVal()+nEWKm->getVal() << " &plusmn; " << sqrt(nSigm->getPropagatedError(*fitResm)*nSigm->getPropagatedError(*fitResm)+nQCDm->getPropagatedError(*fitResm)*nQCDm->getPropagatedError(*fitResm)+nEWKm->getPropagatedError(*fitResm)*nEWKm->getPropagatedError(*fitResm)) << "</p></td>" << endl;
  tablefile << "<td width=\"180\"><p>"<< nSigm->getVal() << " &plusmn; " << nSigm->getPropagatedError(*fitResm) << "</p></td>" << endl;
  tablefile << "<td width=\"180\"><p>"<< nQCDm->getVal() << " &plusmn; " << nQCDm->getPropagatedError(*fitResm) << "</p></td>" << endl;
  tablefile << "<td width=\"180\"><p>"<< nEWKm->getVal() << " &plusmn; " << nEWKm->getPropagatedError(*fitResm) << "</p></td>" << endl;
  tablefile << "</tr>" << endl;
  tablefile << "</table>" << endl;
  tablefile << "<hr />" << endl;

  cout << endl;
  cout << "  <> Output saved in " << outputDir << "/" << endl;    
  cout << endl;

  if (ipt>0)
  {
  hSigWpt     -> SetBinContent(ipt, nSig->getVal());
  hQCDWpt     -> SetBinContent(ipt, nQCD->getVal());
  hSigWPpt    -> SetBinContent(ipt, nSigp->getVal());
  hQCDWPpt    -> SetBinContent(ipt, nQCDp->getVal());
  hSigWMpt    -> SetBinContent(ipt, nSigm->getVal());
  hQCDWMpt    -> SetBinContent(ipt, nQCDm->getVal());
  double total = nEventDYToEE[ipt]+nEventDYToTauTau[ipt]+nEventTTJets[ipt]+nEventWToTauNu[ipt];
  double totalp = nEventDYToEEP[ipt]+nEventDYToTauTauP[ipt]+nEventTTJetsP[ipt]+nEventWToTauNuP[ipt];
  double totalm = nEventDYToEEM[ipt]+nEventDYToTauTauM[ipt]+nEventTTJetsM[ipt]+nEventWToTauNuM[ipt];
  hDYToEE   -> SetBinContent(ipt,nEWK->getVal()*nEventDYToEE[ipt]/total);
  hWToTauTau  -> SetBinContent(ipt,nEWK->getVal()*nEventWToTauNu[ipt]/total);
  hTTJets     -> SetBinContent(ipt,nEWK->getVal()*nEventTTJets[ipt]/total);
  hDYToTauTau -> SetBinContent(ipt,nEWK->getVal()*nEventDYToTauTau[ipt]/total);
  hDYToEEP   -> SetBinContent(ipt,nEWKp->getVal()*nEventDYToEEP[ipt]/totalp);
  hWToTauTauP  -> SetBinContent(ipt,nEWKp->getVal()*nEventWToTauNuP[ipt]/totalp);
  hTTJetsP     -> SetBinContent(ipt,nEWKp->getVal()*nEventTTJetsP[ipt]/totalp);
  hDYToTauTauP -> SetBinContent(ipt,nEWKp->getVal()*nEventDYToTauTauP[ipt]/totalp);
  hDYToEEM   -> SetBinContent(ipt,nEWKm->getVal()*nEventDYToEEM[ipt]/totalm);
  hWToTauTauM  -> SetBinContent(ipt,nEWKm->getVal()*nEventWToTauNuM[ipt]/totalm);
  hTTJetsM     -> SetBinContent(ipt,nEWKm->getVal()*nEventTTJetsM[ipt]/totalm);
  hDYToTauTauM -> SetBinContent(ipt,nEWKm->getVal()*nEventDYToTauTauM[ipt]/totalm);
  }
  }

  Wmfile.close();
  Wmpfile.close();
  Wmmfile.close();

  tablefile << "</body>" << endl;
  tablefile << "</html>" << endl;
  tablefile.close();

  metplotsfile << "</body>" << endl;
  metplotsfile << "</html>" << endl;
  metplotsfile.close();  

  allyields.close();
  allyieldsp.close();
  allyieldsm.close();

//Write W p_{T} Histogram to file
  char wptfname[100];
  if (filetype == "BeforeRC"){
  sprintf(wptfname,"%s/Wpt_BeforeRC.root",CPlot::sOutDir.Data());
  }else if (filetype == "Nominal"){
  sprintf(wptfname,"%s/Wpt_AfterRC.root",CPlot::sOutDir.Data());
  }
  TFile *wptfile = new TFile(wptfname,"RECREATE");
  hdataWpt -> Write();
  hdataWPpt -> Write();
  hdataWMpt -> Write();
  hSigWpt -> Write();
  hSigWPpt -> Write();
  hSigWMpt -> Write();
  hDYToEE -> Write();
  hDYToEEP -> Write();
  hDYToEEM -> Write();
  hWToTauTau -> Write();
  hWToTauTauP -> Write();
  hWToTauTauM -> Write();
  hTTJets -> Write();
  hTTJetsP -> Write();
  hTTJetsM -> Write();
  hDYToTauTau -> Write();
  hDYToTauTauP -> Write();
  hDYToTauTauM -> Write();
  hQCDWpt -> Write();
  hQCDWPpt -> Write();
  hQCDWMpt -> Write();
  wptfile->Close();

// Wpt distribution=========================
  TH1D* hWptDiff;
  TH1D* hWptDiff_p;
  TH1D* hWptDiff_m;

  CPlot* plotWpt;
  CPlot* plotWptDiff;
  CPlot* plotWpt_p;
  CPlot* plotWptDiff_p;
  CPlot* plotWpt_m;
  CPlot* plotWptDiff_m;

//Inclusive W pt distribution
  TH1D* hWptMC = (TH1D*)hDYToTauTau->Clone("hWptMC");
  hWptMC->Add(hTTJets);
  hWptMC->Add(hWToTauTau);
  hWptMC->Add(hDYToEE);
  hWptMC->Add(hQCDWpt);
  hWptMC->Add(hSigWpt);
  hWptDiff = makeDiffHistWpt(hdataWpt,hWptMC,"hWptDiff");
  hWptDiff->SetMarkerStyle(kFullCircle);
  hWptDiff->SetMarkerSize(0.9);

  sprintf(histName,"WEle_pt");
  plotWpt=new CPlot(histName,"","","Events");
  plotWpt->setOutDir(CPlot::sOutDir);
  plotWpt->AddToStack(hDYToTauTau,"Z/#gamma^{*}#rightarrow#tau#tau",kSpring+5,kSpring+3);
  plotWpt->AddToStack(hTTJets,"t#bar{t}",kAzure-5,kAzure-1);
  plotWpt->AddToStack(hWToTauTau,"W#rightarrow#tau#nu",kCyan-9,kCyan-6);
  plotWpt->AddToStack(hDYToEE,"Z/#gamma^{*}#rightarrow ee",fillcolorEWK,linecolorEWK);
  plotWpt->AddToStack(hQCDWpt,"QCD",fillcolorQCD,linecolorQCD);
  plotWpt->AddToStack(hSigWpt,"W#rightarrow e#nu",fillcolorW,linecolorW);
  plotWpt->AddHist1D(hdataWpt,"Data","E");
  plotWpt->SetLegend(0.78,0.65,.98,0.88);
  plotWpt->SetYRange(0.1,1.1*(hWptMC->GetMaximum()));
  plotWpt->Draw(c,kFALSE,format,1);

  plotWptDiff=new CPlot(histName,"","p_{T} [Gev]","#chi");
  plotWptDiff->setOutDir(CPlot::sOutDir);
  plotWptDiff->AddHist1D(hWptDiff,"EX0",ratioColor);
  plotWptDiff->SetYRange(-0.1,0.1);
  plotWptDiff->AddLine(0, 0,300, 0,kBlack,1);
  plotWptDiff->AddLine(0, 0.05,300, 0.05,kBlack,3);
  plotWptDiff->AddLine(0,-0.05,300,-0.05,kBlack,3);
  plotWptDiff->Draw(c,kTRUE,format,2);

  sprintf(histName,"WEle_ptLog");
  plotWpt->SetName(histName);
  plotWpt->SetYRange(5e-6*(hWptMC->GetMaximum()),1.4*(hWptMC->GetMaximum()));
  plotWpt->SetLogy();
  plotWpt->Draw(c,kTRUE,format,1);

//W plus pt distribution
  TH1D* hWptMC_p = (TH1D*)hDYToTauTauP->Clone("hWptMC_p");
  hWptMC_p->Add(hTTJetsP);
  hWptMC_p->Add(hWToTauTauP);
  hWptMC_p->Add(hDYToEEP);
  hWptMC_p->Add(hQCDWPpt);
  hWptMC_p->Add(hSigWPpt);
  hWptDiff_p = makeDiffHistWpt(hdataWPpt,hWptMC_p,"hWptDiff_p");
  hWptDiff_p->SetMarkerStyle(kFullCircle);
  hWptDiff_p->SetMarkerSize(0.9);

  sprintf(histName,"WpEle_pt");
  plotWpt_p=new CPlot(histName,"","","Events");
  plotWpt_p->setOutDir(CPlot::sOutDir);
  plotWpt_p->AddToStack(hDYToTauTauP,"Z/#gamma^{*}#rightarrow#tau#tau",kSpring+5,kSpring+3);
  plotWpt_p->AddToStack(hTTJetsP,"t#bar{t}",kAzure-5,kAzure-1);
  plotWpt_p->AddToStack(hWToTauTauP,"W#rightarrow#tau#nu",kCyan-9,kCyan-6);
  plotWpt_p->AddToStack(hDYToEEP,"Z/#gamma^{*}#rightarrow ee",fillcolorEWK,linecolorEWK);
  plotWpt_p->AddToStack(hQCDWPpt,"QCD",fillcolorQCD,linecolorQCD);
  plotWpt_p->AddToStack(hSigWPpt,"W#rightarrow e#nu",fillcolorW,linecolorW);
  plotWpt_p->AddHist1D(hdataWPpt,"Data","E");
  plotWpt_p->SetLegend(0.78,0.65,.98,0.88);
  plotWpt_p->SetYRange(0.1,1.1*(hWptMC_p->GetMaximum()));
  plotWpt_p->Draw(c,kFALSE,format,1);

  plotWptDiff_p=new CPlot(histName,"","p_{T} [Gev]","#chi");
  plotWptDiff_p->setOutDir(CPlot::sOutDir);
  plotWptDiff_p->AddHist1D(hWptDiff_p,"EX0",ratioColor);
  plotWptDiff_p->SetYRange(-0.1,0.1);
  plotWptDiff_p->AddLine(0, 0,300, 0,kBlack,1);
  plotWptDiff_p->AddLine(0, 0.05,300, 0.05,kBlack,3);
  plotWptDiff_p->AddLine(0,-0.05,300,-0.05,kBlack,3);
  plotWptDiff_p->Draw(c,kTRUE,format,2);

  sprintf(histName,"WpEle_ptLog");
  plotWpt_p->SetName(histName);
  plotWpt_p->SetYRange(5e-6*(hWptMC_p->GetMaximum()),1.4*(hWptMC_p->GetMaximum()));
  plotWpt_p->SetLogy();
  plotWpt_p->Draw(c,kTRUE,format,1);

//W minus pt distribution
  TH1D* hWptMC_m = (TH1D*)hDYToTauTauM->Clone("hWptMC_m");
  hWptMC_m->Add(hTTJetsM);
  hWptMC_m->Add(hWToTauTauM);
  hWptMC_m->Add(hDYToEEM);
  hWptMC_m->Add(hQCDWMpt);
  hWptMC_m->Add(hSigWMpt);
  hWptDiff_m = makeDiffHistWpt(hdataWMpt,hWptMC_m,"hWptDiff_m");
  hWptDiff_m->SetMarkerStyle(kFullCircle);
  hWptDiff_m->SetMarkerSize(0.9);

  sprintf(histName,"WmEle_pt");
  plotWpt_m=new CPlot(histName,"","","Events");
  plotWpt_m->setOutDir(CPlot::sOutDir);
  plotWpt_m->AddToStack(hDYToTauTauM,"Z/#gamma^{*}#rightarrow#tau#tau",kSpring+5,kSpring+3);
  plotWpt_m->AddToStack(hTTJetsM,"t#bar{t}",kAzure-5,kAzure-1);
  plotWpt_m->AddToStack(hWToTauTauM,"W#rightarrow#tau#nu",kCyan-9,kCyan-6);
  plotWpt_m->AddToStack(hDYToEEM,"Z/#gamma^{*}#rightarrow ee",fillcolorEWK,linecolorEWK);
  plotWpt_m->AddToStack(hQCDWMpt,"QCD",fillcolorQCD,linecolorQCD);
  plotWpt_m->AddToStack(hSigWMpt,"W#rightarrow e#nu",fillcolorW,linecolorW);
  plotWpt_m->AddHist1D(hdataWMpt,"Data","E");
  plotWpt_m->SetLegend(0.78,0.65,.98,0.88);
  plotWpt_m->SetYRange(0.1,1.1*(hWptMC_m->GetMaximum()));
  plotWpt_m->Draw(c,kFALSE,format,1);

  plotWptDiff_m=new CPlot(histName,"","p_{T} [Gev]","#chi");
  plotWptDiff_m->setOutDir(CPlot::sOutDir);
  plotWptDiff_m->AddHist1D(hWptDiff_m,"EX0",ratioColor);
  plotWptDiff_m->SetYRange(-0.1,0.1);
  plotWptDiff_m->AddLine(0, 0,300, 0,kBlack,1);
  plotWptDiff_m->AddLine(0, 0.05,300, 0.05,kBlack,3);
  plotWptDiff_m->AddLine(0,-0.05,300,-0.05,kBlack,3);
  plotWptDiff_m->Draw(c,kTRUE,format,2);

  sprintf(histName,"WmEle_ptLog");
  plotWpt_m->SetName(histName);
  plotWpt_m->SetYRange(5e-6*(hWptMC_m->GetMaximum()),1.4*(hWptMC_m->GetMaximum()));
  plotWpt_m->SetLogy();
  plotWpt_m->Draw(c,kTRUE,format,1);

  makeHTML(outputDir);
  gBenchmark->Show("fitWEleMetConvSimult");
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
TH1D *makeDiffHistWpt(TH1D* hData, TH1D* hFit, const TString name)
{
  double WptBins[12]={0,8,23,38,55,75,95,120,145,175,210,300};
  TH1D *hDiff = new TH1D(name,"",11,WptBins);
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
  htmlfile << "<body bgcolor=\"white\">" << endl;
  htmlfile << "<hr />" << endl;
  htmlfile << " <p> <a target=\"_blank\" href=\"fitMetPlots.html\">[Wpt All Bins MET Fit distributions]</a>" <<  "&nbsp; <a target=\"_blank\" href=\"AllYieldsTable.html\">[All Bins Yields Table]</a> </p>" << endl;
  htmlfile << "<hr />" << endl;
  htmlfile << " <p align=\"center\"> W pt plots </a>" << endl;
  htmlfile << "<hr />" << endl;
  htmlfile << "<table border=\"0\" cellspacing=\"5\" width=\"100%\">" << endl; 
  htmlfile << "<tr>" << endl;
  htmlfile << "<td width=\"15%\"></td>" << endl;
  htmlfile << "<td width=\"25%\"><p align=\"center\" style=\"font-size:small\"> W </p></td>" << endl;
  htmlfile << "<td width=\"25%\"><p align=\"center\" style=\"font-size:small\"> W <sup>+</sup> </p></td>" << endl;
  htmlfile << "<td width=\"25%\"><p align=\"center\" style=\"font-size:small\"> W <sup>-</sup> </p></td>" << endl;
  htmlfile << "<td width=\"10%\"></td>" << endl;
  htmlfile << "</tr>" << endl;
  htmlfile << "<tr>" << endl;
  htmlfile << "<td width=\"15%\"></td>" << endl;
  htmlfile << "<td width=\"25%\"><a target=\"_blank\" href=\"WEle_pt.png\"><img src=\"WEle_pt.png\" alt=\"WEle_pt.png\" width=\"100%\"></a></td>" << endl;
  htmlfile << "<td width=\"25%\"><a target=\"_blank\" href=\"WpEle_pt.png\"><img src=\"WpEle_pt.png\" alt=\"WpEle_pt.png\" width=\"100%\"></a></td>" << endl;
  htmlfile << "<td width=\"25%\"><a target=\"_blank\" href=\"WmEle_pt.png\"><img src=\"WmEle_pt.png\" alt=\"WmEle_pt.png\" width=\"100%\"></a></td>" << endl;
  htmlfile << "<td width=\"10%\"></td>" << endl;
  htmlfile << "</tr>" << endl;
  htmlfile << "<tr>" << endl;
  htmlfile << "<td width=\"15%\"></td>" << endl;
  htmlfile << "<td width=\"25%\"><a target=\"_blank\" href=\"WEle_ptLog.png\"><img src=\"WEle_ptLog.png\" alt=\"WEle_ptLog.png\" width=\"100%\"></a></td>" << endl;
  htmlfile << "<td width=\"25%\"><a target=\"_blank\" href=\"WpEle_ptLog.png\"><img src=\"WpEle_ptLog.png\" alt=\"WpEle_ptLog.png\" width=\"100%\"></a></td>" << endl;
  htmlfile << "<td width=\"25%\"><a target=\"_blank\" href=\"WmEle_ptLog.png\"><img src=\"WmEle_ptLog.png\" alt=\"WmEle_ptLog.png\" width=\"100%\"></a></td>" << endl;
  htmlfile << "<td width=\"10%\"></td>" << endl;
  htmlfile << "</tr>" << endl;
  htmlfile << "</table>" << endl;
  htmlfile << "<hr />" << endl;
  htmlfile << "</body>" << endl;
  htmlfile << "</html>" << endl;
  htmlfile.close();  
}
