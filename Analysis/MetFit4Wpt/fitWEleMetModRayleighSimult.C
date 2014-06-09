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
TH1D* makeDiffHistWpt(TH1D* hData, TH1D* hFit, const TString name);
TH1D* makeDiffHistWptLog(TH1D* hData, TH1D* hFit, const TString name);
// print correlations of fitted parameters
void printCorrelations(ostream& os, RooFitResult *res);

// print chi2 test and KS test results
void printChi2AndKSResults(ostream& os, 
                           const Double_t chi2prob, const Double_t chi2ndf, 
			   const Double_t ksprob, const Double_t ksprobpe);

// make webpage
void makeHTML(const TString outDir);

//=== MAIN MACRO ================================================ 

void fitWEleMetModRayleighSimult(const TString  outputDir,   // output directory
           const TString  filetype,		// Select input root files for Nominal, Up, Down and Before Recoil Correction
           const Double_t lumi,        // integrated luminosity (/fb)
	   const Double_t nsigma=0     // vary MET corrections by n-sigmas (nsigma=0 means nominal correction)
)
{
  gBenchmark->Start("fitWEleMetModRayleighSimult");

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

  //total number of each EWK samples for ith bin
  vector <double> nEventDYToMuMu;
  vector <double> nEventDYToTauTau;
  vector <double> nEventTTJets;
  vector <double> nEventWToTauNu;
  vector <double> nEventDYToMuMuP;
  vector <double> nEventDYToTauTauP;
  vector <double> nEventTTJetsP;
  vector <double> nEventWToTauNuP;
  vector <double> nEventDYToMuMuM;
  vector <double> nEventDYToTauTauM;
  vector <double> nEventTTJetsM;
  vector <double> nEventWToTauNuM;

  int ewkNumber(0);
  fnamev.push_back("../WPtMET/Electron2012LoPU/Ele_RD_LowPU_ScaleCorr.root"); typev.push_back(eData);
  fnamev.push_back("../WPtMET/Electron2012LoPU/Ele_DYToEE_S8_SmeaEffCorr.root"); typev.push_back(eEWK);
  fnamev.push_back("../WPtMET/Electron2012LoPU/Ele_DYToTauTau_S8_SmeaEffCorr.root"); typev.push_back(eEWK);
  fnamev.push_back("../WPtMET/Electron2012LoPU/Ele_TTJets_S8_SmeaEffCorr.root"); typev.push_back(eEWK);
  fnamev.push_back("../WPtMET/Electron2012LoPU/Ele_WToTauNu_S8_SmeaEffCorr.root"); typev.push_back(eEWK);
  if (filetype == "Nominal"){
    fnamev.push_back("../WPtMET/Electron2012LoPU/WpToEleNu_S8_SmeaRecEffCorr.root"); typev.push_back(eWpMuNu);
    fnamev.push_back("../WPtMET/Electron2012LoPU/WmToEleNu_S8_SmeaRecEffCorr.root"); typev.push_back(eWmMuNu);
  }else if (filetype == "Up"){
    fnamev.push_back("../EventSelection/ElectronLowPU/Ele_WpToEleNu_S8_Up_RecoilCorrMC.root"); typev.push_back(eWpMuNu);
    fnamev.push_back("../EventSelection/ElectronLowPU/Ele_WmToEleNu_S8_Up_RecoilCorrMC.root"); typev.push_back(eWmMuNu);
  }else if (filetype == "Down"){
    fnamev.push_back("../EventSelection/ElectronLowPU/Ele_WpToEleNu_S8_Down_RecoilCorrMC.root"); typev.push_back(eWpMuNu);
    fnamev.push_back("../EventSelection/ElectronLowPU/Ele_WmToEleNu_S8_Down_RecoilCorrMC.root"); typev.push_back(eWmMuNu);
  }else if (filetype == "BeforeRC"){
    fnamev.push_back("../EventSelection/ElectronLowPU/Ele_WpToEleNu_S8_Analysis.root"); typev.push_back(eWpMuNu);
    fnamev.push_back("../EventSelection/ElectronLowPU/Ele_WmToEleNu_S8_Analysis.root"); typev.push_back(eWmMuNu);
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

  double WptBins[14]={0,7.5,12.5,17.5,24,30,40,50,70,110,150,190,250,600};
//  double WptBins[17]={0,5,7.5,10,12.5,15,17.5,20,30,40,50,70,90,150,190,250,600};
//  double WptBins[12]={0,7.5,20,40,50,70,90,110,150,190,250,600};
//  double WptBins[18]={0,2.5,5,7.5,10,12.5,15,17.5,20,30,40,50,70,90,150,190,250,600};
  //double WptBins[NWptBinPlus]={0,2.5,5,7.5,10,12.5,15,17.5,20,30,40,50,70,90,150,190,250,600};
  TH1D *hdataWpt;
  TH1D *hdataWPpt;
  TH1D *hdataWMpt;
  
  TH1D *hSigWpt		= new TH1D("hSigWpt","hSigWpt",13,WptBins);hSigWpt->Sumw2();
  TH1D *hSigWPpt	= new TH1D("hSigWPpt","hSigWPpt",13,WptBins);hSigWPpt->Sumw2();
  TH1D *hSigWMpt	= new TH1D("hSigWMpt","hSigWMpt",13,WptBins);hSigWMpt->Sumw2();
  TH1D *hQCDWpt		= new TH1D("hQCDWpt","hQCDWpt",13,WptBins);hQCDWpt->Sumw2();
  TH1D *hQCDWPpt	= new TH1D("hQCDWPpt","hQCDWPpt",13,WptBins);hQCDWPpt->Sumw2();
  TH1D *hQCDWMpt	= new TH1D("hQCDWMpt","hQCDWMpt",13,WptBins);hQCDWMpt->Sumw2();
  TH1D *hDYToMuMu	= new TH1D("hDYToMuMu","hDYToMuMu",13,WptBins);hDYToMuMu->Sumw2();
  TH1D *hDYToMuMuP	= new TH1D("hDYToMuMuP","hDYToMuMuP",13,WptBins);hDYToMuMuP->Sumw2();
  TH1D *hDYToMuMuM	= new TH1D("hDYToMuMuM","hDYToMuMuM",13,WptBins);hDYToMuMuM->Sumw2();
  TH1D *hWToTauNu	= new TH1D("hWToTauNu","hWToTauNu",13,WptBins);hWToTauNu->Sumw2();
  TH1D *hWToTauNuP	= new TH1D("hWToTauNuP","hWToTauNuP",13,WptBins);hWToTauNuP->Sumw2();
  TH1D *hWToTauNuM	= new TH1D("hWToTauNuM","hWToTauNuM",13,WptBins);hWToTauNuM->Sumw2();
  TH1D *hTTJets		= new TH1D("hTTJets","hTTJets",13,WptBins);hTTJets->Sumw2();
  TH1D *hTTJetsP	= new TH1D("hTTJetsP","hTTJetsP",13,WptBins);hTTJetsP->Sumw2();
  TH1D *hTTJetsM	= new TH1D("hTTJetsM","hTTJetsM",13,WptBins);hTTJetsM->Sumw2();
  TH1D *hDYToTauTau	= new TH1D("hDYToTauTau","hDYToTauTau",13,WptBins);hDYToTauTau->Sumw2();
  TH1D *hDYToTauTauP	= new TH1D("hDYToTauTauP","hDYToTauTauP",13,WptBins);hDYToTauTauP->Sumw2();
  TH1D *hDYToTauTauM	= new TH1D("hDYToTauTauM","hDYToTauTauM",13,WptBins);hDYToTauTauM->Sumw2();

  TH1D *hQCD_SigPlus	= new TH1D("hQCD_SigPlus","hQCD_SigPlus",13,WptBins);hQCD_SigPlus->Sumw2();
  TH1D *hQCD_SigMinus	= new TH1D("hQCD_SigMinus","hQCD_SigMinus",13,WptBins);hQCD_SigMinus->Sumw2();
  TH1D *hQCD_SigQCDPlus	= new TH1D("hQCD_SigQCDPlus","hQCD_SigQCDPlus",13,WptBins);hQCD_SigQCDPlus->Sumw2();
  TH1D *hQCD_SigQCDMinus= new TH1D("hQCD_SigQCDMinus","hQCD_SigQCDMinus",13,WptBins);hQCD_SigQCDMinus->Sumw2();

  TH1D *hDataMet[NWptBinPlus];
  TH1D *hDataMetm[NWptBinPlus];
  TH1D *hDataMetp[NWptBinPlus]; 
  TH1D *hWmunuMet[NWptBinPlus]; 
  TH1D *hWmunuMetp[NWptBinPlus];
  TH1D *hWmunuMetm[NWptBinPlus];
  TH1D *hEWKMet[NWptBinPlus]; 
  TH1D *hEWKMetp[NWptBinPlus]; 
  TH1D *hEWKMetm[NWptBinPlus]; 
                                              
  TH1D *hAntiDataMet[NWptBinPlus];
  TH1D *hAntiDataMetm[NWptBinPlus];
  TH1D *hAntiDataMetp[NWptBinPlus];
  TH1D *hAntiWmunuMet[NWptBinPlus];
  TH1D *hAntiWmunuMetp[NWptBinPlus];
  TH1D *hAntiWmunuMetm[NWptBinPlus];
  TH1D *hAntiEWKMet[NWptBinPlus];
  TH1D *hAntiEWKMetp[NWptBinPlus];
  TH1D *hAntiEWKMetm[NWptBinPlus];
  
  Double_t METMAX;
  
  bool QCDFix(false);  // For Scale Correction Systematic Calculation
  //bool QCDFix(true); // For Other Corrections Systematic Calculation
  
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
        ewkNumber++;
	for( int ipt(0); ipt<NWptBinPlus; ipt++)
	{
	  sprintf(histName,"hEWKMet_%d",ipt);
	  sprintf(histName_org,"h1_W_Neu_pt_%d",ipt);
	  hEWKMet[ipt] =(TH1D*)infile->Get(histName_org)->Clone(histName);hEWKMet[ipt]->Sumw2();
	  nEventDYToMuMu.push_back(hEWKMet[ipt]->Integral());
	  sprintf(histName,"hEWKMetm_%d",ipt);
	  sprintf(histName_org,"h1_Wm_Neu_pt_%d",ipt);
	  hEWKMetm[ipt]=(TH1D*)infile->Get(histName_org)->Clone(histName);hEWKMetm[ipt]->Sumw2();
	  nEventDYToMuMuM.push_back(hEWKMetm[ipt]->Integral());
	  sprintf(histName,"hEWKMetp_%d",ipt);
	  sprintf(histName_org,"h1_Wp_Neu_pt_%d",ipt);
	  hEWKMetp[ipt]=(TH1D*)infile->Get(histName_org)->Clone(histName);hEWKMetp[ipt]->Sumw2();
	  nEventDYToMuMuP.push_back(hEWKMetp[ipt]->Integral());

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
  RooRealVar* nSig[NWptBinPlus];
  RooRealVar* nSigp[NWptBinPlus];
  RooRealVar* nSigm[NWptBinPlus];
  
  RooRealVar* nAntiSig[NWptBinPlus];
  RooRealVar* nAntiSigp[NWptBinPlus];
  RooRealVar* nAntiSigm[NWptBinPlus];
  
  RooRealVar* nQCD[NWptBinPlus];
  RooRealVar* nQCDp[NWptBinPlus];
  RooRealVar* nQCDm[NWptBinPlus];
  
  RooRealVar* nAntiQCD[NWptBinPlus];
  RooRealVar* nAntiQCDp[NWptBinPlus];
  RooRealVar* nAntiQCDm[NWptBinPlus];
  
  RooFormulaVar* nEWK[NWptBinPlus];
  RooFormulaVar* nEWKp[NWptBinPlus];
  RooFormulaVar* nEWKm[NWptBinPlus];
  
  RooFormulaVar* nAntiEWK[NWptBinPlus];
  RooFormulaVar* nAntiEWKp[NWptBinPlus];
  RooFormulaVar* nAntiEWKm[NWptBinPlus];
  
  RooRealVar* cewk[NWptBinPlus];
  RooRealVar* cewkp[NWptBinPlus];
  RooRealVar* cewkm[NWptBinPlus];
  
  RooRealVar* dewk[NWptBinPlus];
  RooRealVar* dewkp[NWptBinPlus];
  RooRealVar* dewkm[NWptBinPlus];
 
  RooDataHist* wmunuMet[NWptBinPlus];
  RooDataHist* wmunuMetp[NWptBinPlus];
  RooDataHist* wmunuMetm[NWptBinPlus];
  RooDataHist* awmunuMet[NWptBinPlus];
  RooDataHist* awmunuMetp[NWptBinPlus];
  RooDataHist* awmunuMetm[NWptBinPlus];
  
  RooHistPdf* pdfWm[NWptBinPlus] ;
  RooHistPdf* pdfWmp[NWptBinPlus];
  RooHistPdf* pdfWmm[NWptBinPlus];
  RooHistPdf* apdfWm[NWptBinPlus] ;
  RooHistPdf* apdfWmp[NWptBinPlus];
  RooHistPdf* apdfWmm[NWptBinPlus];
 
  RooDataHist* ewkMet[NWptBinPlus] ;
  RooDataHist* ewkMetp[NWptBinPlus];
  RooDataHist* ewkMetm[NWptBinPlus];
  RooDataHist* aewkMet[NWptBinPlus] ;
  RooDataHist* aewkMetp[NWptBinPlus];
  RooDataHist* aewkMetm[NWptBinPlus];
  
  RooHistPdf* pdfEWK[NWptBinPlus] ;
  RooHistPdf* pdfEWKp[NWptBinPlus]; 
  RooHistPdf* pdfEWKm[NWptBinPlus]; 
  RooHistPdf* apdfEWK[NWptBinPlus] ;
  RooHistPdf* apdfEWKp[NWptBinPlus]; 
  RooHistPdf* apdfEWKm[NWptBinPlus]; 
  
  RooAddPdf* pdfMet[NWptBinPlus];
  RooAddPdf* pdfMetp[NWptBinPlus];
  RooAddPdf* pdfMetm[NWptBinPlus];
  RooAddPdf* apdfMet[NWptBinPlus] ;
  RooAddPdf* apdfMetp[NWptBinPlus];
  RooAddPdf* apdfMetm[NWptBinPlus];
  
  RooCategory rooCat("rooCat","rooCat");
  rooCat.defineType("Select");
  rooCat.defineType("Anti");
  
  RooSimultaneous* pdfTotal[NWptBinPlus];
  RooSimultaneous* pdfTotalp[NWptBinPlus];
  RooSimultaneous* pdfTotalm[NWptBinPlus];
  
  RooDataHist* dataMet[NWptBinPlus]; 
  RooDataHist* dataMetp[NWptBinPlus]; 
  RooDataHist* dataMetm[NWptBinPlus]; 
  
  RooDataHist* antiMet[NWptBinPlus]; 
  RooDataHist* antiMetp[NWptBinPlus]; 
  RooDataHist* antiMetm[NWptBinPlus]; 
  
  RooDataHist* dataTotal[NWptBinPlus];
  RooDataHist* dataTotalp[NWptBinPlus];
  RooDataHist* dataTotalm[NWptBinPlus];

  RooFitResult *fitRes[NWptBinPlus];
  RooFitResult *fitResp[NWptBinPlus];
  RooFitResult *fitResm[NWptBinPlus];
  
  TH1D *hPdfMet;TH1D *hMetDiff;
  TH1D *hPdfMetp;TH1D *hMetpDiff;
  TH1D *hPdfMetm;TH1D *hMetmDiff;
  TH1D *hPdfAntiMet;TH1D *hAntiMetDiff;
  TH1D *hPdfAntiMetp;TH1D *hAntiMetpDiff;
  TH1D *hPdfAntiMetm;TH1D *hAntiMetmDiff;
  
  CPepeModelMean* qcd[NWptBinPlus];
  CPepeModelMean* qcdp[NWptBinPlus];
  CPepeModelMean* qcdm[NWptBinPlus];
  CPepeModelMean* aqcd[NWptBinPlus];
  CPepeModelMean* aqcdp[NWptBinPlus];
  CPepeModelMean* aqcdm[NWptBinPlus];
  
  CPepePlusMod* qcd1[NWptBinPlus];
  CPepePlusMod* qcd1p[NWptBinPlus];
  CPepePlusMod* qcd1m[NWptBinPlus];
  CPepePlusMod* aqcd1[NWptBinPlus];
  CPepePlusMod* aqcd1p[NWptBinPlus];
  CPepePlusMod* aqcd1m[NWptBinPlus];
  
  CPepeDouble* qcd2[NWptBinPlus];
  CPepeDouble* qcd2p[NWptBinPlus];
  CPepeDouble* qcd2m[NWptBinPlus];
  CPepeDouble* aqcd2[NWptBinPlus];
  CPepeDouble* aqcd2p[NWptBinPlus];
  CPepeDouble* aqcd2m[NWptBinPlus];
  
  RooRealVar* qcdmean[NWptBinPlus];
  RooRealVar* qcdPmean[NWptBinPlus];
  RooRealVar* qcdMmean[NWptBinPlus];
  
  RooRealVar* qcdsigma1[NWptBinPlus];
  RooRealVar* qcdPsigma1[NWptBinPlus];
  RooRealVar* qcdMsigma1[NWptBinPlus];
  
  RooRealVar* aqcdsigma1[NWptBinPlus];
  RooRealVar* aqcdPsigma1[NWptBinPlus];
  RooRealVar* aqcdMsigma1[NWptBinPlus];
  
  RooRealVar* qcda1[NWptBinPlus];
  RooRealVar* qcdPa1[NWptBinPlus];
  RooRealVar* qcdMa1[NWptBinPlus];
  
  RooRealVar* qcdsigma2[NWptBinPlus];
  RooRealVar* qcdPsigma2[NWptBinPlus];
  RooRealVar* qcdMsigma2[NWptBinPlus];
  
  RooRealVar* aqcdsigma2[NWptBinPlus];
  RooRealVar* aqcdPsigma2[NWptBinPlus];
  RooRealVar* aqcdMsigma2[NWptBinPlus];
  
  RooRealVar* qcda2[NWptBinPlus];
  RooRealVar* qcdPa2[NWptBinPlus];
  RooRealVar* qcdMa2[NWptBinPlus];
  
  RooRealVar* Frac1[NWptBinPlus];
  RooRealVar* Frac1P[NWptBinPlus];
  RooRealVar* Frac1M[NWptBinPlus];
  
  RooRealVar* Frac2[NWptBinPlus];
  RooRealVar* Frac2P[NWptBinPlus];
  RooRealVar* Frac2M[NWptBinPlus];
  
  RooRealVar* dFrac1[NWptBinPlus];
  RooRealVar* dFrac1P[NWptBinPlus];
  RooRealVar* dFrac1M[NWptBinPlus];

  RooRealVar* dFrac2[NWptBinPlus];
  RooRealVar* dFrac2P[NWptBinPlus];
  RooRealVar* dFrac2M[NWptBinPlus];
  
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
  char binlabel[50];
  
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
  sprintf(Wmfname,"%s/fitresWm_AllBin.txt",CPlot::sOutDir.Data());
  Wmfile.open(Wmfname);
  assert(Wmfile.is_open());
  Wmfile << " *** Inclusive W -- All Bin Yields Information *** " << endl;

  ofstream Wmpfile;
  char Wmpfname[100];    
  sprintf(Wmpfname,"%s/fitresWmp_AllBin.txt",CPlot::sOutDir.Data());
  Wmpfile.open(Wmpfname);
  assert(Wmpfile.is_open());
  Wmpfile << " *** W plus -- All Bin Yields Information *** " << endl;

  ofstream Wmmfile;
  char Wmmfname[100];    
  sprintf(Wmmfname,"%s/fitresWmm_AllBin.txt",CPlot::sOutDir.Data());
  Wmmfile.open(Wmmfname);
  assert(Wmmfile.is_open());
  Wmmfile << " *** W minus -- All Bin Yields Information *** " << endl;
  
  ofstream qcdfile;
  char qcdfname[100];    
  sprintf(qcdfname,"%s/qcd_shapes.txt",CPlot::sOutDir.Data());
  qcdfile.open(qcdfname);
  assert(qcdfile.is_open());
  
  ofstream InValfile;
  char InValfname[100];    
  sprintf(InValfname,"%s/InVal.txt",CPlot::sOutDir.Data());
  InValfile.open(InValfname);
  assert(InValfile.is_open());
  
  //Merge Side Band Bins 10-13
  TH1D *hHighWpTAnti_DataMet ;
  TH1D *hHighWpTAnti_DataMetm;
  TH1D *hHighWpTAnti_DataMetp;
  TH1D *hHighWpTAnti_WmunuMet;
  TH1D *hHighWpTAnti_WmunuMetp;
  TH1D *hHighWpTAnti_WmunuMetm;
  TH1D *hHighWpTAnti_EWKMet;
  TH1D *hHighWpTAnti_EWKMetp;
  TH1D *hHighWpTAnti_EWKMetm;
  
  hHighWpTAnti_DataMet  = (TH1D*)hAntiDataMet[10]  ->Clone("hHighWpTAnti_DataMet");   hHighWpTAnti_DataMet->Sumw2();
  hHighWpTAnti_DataMetp = (TH1D*)hAntiDataMetp[10] ->Clone("hHighWpTAnti_DataMetp");  hHighWpTAnti_DataMetp->Sumw2();
  hHighWpTAnti_DataMetm = (TH1D*)hAntiDataMetm[10] ->Clone("hHighWpTAnti_DataMetm");  hHighWpTAnti_DataMetm->Sumw2();
  hHighWpTAnti_WmunuMet = (TH1D*)hAntiWmunuMet[10] ->Clone("hHighWpTAnti_WmunuMet");  hHighWpTAnti_WmunuMet->Sumw2();
  hHighWpTAnti_WmunuMetp= (TH1D*)hAntiWmunuMetp[10]->Clone("hHighWpTAnti_WmunuMetp"); hHighWpTAnti_WmunuMetp->Sumw2();
  hHighWpTAnti_WmunuMetm= (TH1D*)hAntiWmunuMetm[10]->Clone("hHighWpTAnti_WmunuMetm"); hHighWpTAnti_WmunuMetm->Sumw2();
  hHighWpTAnti_EWKMet   = (TH1D*)hAntiEWKMet[10]   ->Clone("hHighWpTAnti_EWKMet");    hHighWpTAnti_EWKMet->Sumw2();
  hHighWpTAnti_EWKMetp  = (TH1D*)hAntiEWKMetp[10]  ->Clone("hHighWpTAnti_EWKMetp");   hHighWpTAnti_EWKMetp->Sumw2();
  hHighWpTAnti_EWKMetm  = (TH1D*)hAntiEWKMetm[10]  ->Clone("hHighWpTAnti_EWKMetm");   hHighWpTAnti_EWKMetm->Sumw2();
  
  for( int ipt(11);ipt<NWptBinPlus;ipt++)
  {
    hHighWpTAnti_DataMet  -> Add(hAntiDataMet[ipt]);
    hHighWpTAnti_DataMetp -> Add(hAntiDataMetp[ipt]);
    hHighWpTAnti_DataMetm -> Add(hAntiDataMetm[ipt]);
    hHighWpTAnti_WmunuMet -> Add(hAntiWmunuMet[ipt]);
    hHighWpTAnti_WmunuMetp-> Add(hAntiWmunuMetp[ipt]);
    hHighWpTAnti_WmunuMetm-> Add(hAntiWmunuMetm[ipt]);
    hHighWpTAnti_EWKMet   -> Add(hAntiEWKMet[ipt]);
    hHighWpTAnti_EWKMetp  -> Add(hAntiEWKMetp[ipt]);
    hHighWpTAnti_EWKMetm  -> Add(hAntiEWKMetm[ipt]);
  }
  //Loop for each Wpt bins==============
  // 0 is the total
  for( int ipt(0);ipt<NWptBinPlus;ipt++)
  //for( int ipt(9);ipt<14;ipt++)
  {
    if ( ipt<NBIN_PT_DIVIDER_1and2 ){
      METMAX = METMAX_1;
      NBINS   = NBINS_1;
    } else if ( ipt<NBIN_PT_DIVIDER_2and3 ) {
      METMAX = METMAX_2;
      NBINS   = NBINS_2;
    } else {
      METMAX = METMAX_4;
      NBINS  = NBINS_2;
    }
    RooRealVar pfmet("pfmet","pfmet",0,METMAX);
    pfmet.setBins(NBINS);

    sprintf(histName,"nSig_%d",ipt);
    nSig[ipt] = new RooRealVar(histName,histName
	,0.7*(hDataMet[ipt]->Integral()),0,hDataMet[ipt]->Integral());
    sprintf(histName,"nSigp_%d",ipt);
    nSigp[ipt] = new RooRealVar(histName,histName
	,0.7*(hDataMetp[ipt]->Integral()),0,hDataMetp[ipt]->Integral());
    sprintf(histName,"nSigm_%d",ipt);
    nSigm[ipt] = new RooRealVar(histName,histName
	,0.7*(hDataMetm[ipt]->Integral()),0,hDataMetm[ipt]->Integral());
   
    if (ipt==13)
    {
      sprintf(histName,"nSig_%d",ipt);
      nSig[ipt] = new RooRealVar(histName,histName
	  ,0.5*(hDataMet[ipt]->Integral()),0.05*hDataMet[ipt]->Integral(),0.9*hDataMet[ipt]->Integral());
      sprintf(histName,"nSigp_%d",ipt);
      nSigp[ipt] = new RooRealVar(histName,histName
          ,0.5*(hDataMetp[ipt]->Integral()),0.05*hDataMetp[ipt]->Integral(),0.9*hDataMetp[ipt]->Integral());
      sprintf(histName,"nSigm_%d",ipt);
      nSigm[ipt] = new RooRealVar(histName,histName
  	  ,0.5*(hDataMetm[ipt]->Integral()),0.005*hDataMetm[ipt]->Integral(),0.95*hDataMetm[ipt]->Integral());
    
      sprintf(histName,"nQCD_%d",ipt);
      nQCD[ipt]  = new RooRealVar(histName,histName
          ,0.3*(hDataMet[ipt]->Integral()),0.05*hDataMet[ipt]->Integral(),0.9*hDataMet[ipt]->Integral());
      sprintf(histName,"nQCDp_%d",ipt);
      nQCDp[ipt] = new RooRealVar(histName,histName
          ,0.3*(hDataMetp[ipt]->Integral()),0.05*hDataMetp[ipt]->Integral(),0.9*hDataMetp[ipt]->Integral());
      sprintf(histName,"nQCDm_%d",ipt);
      nQCDm[ipt] = new RooRealVar(histName,histName
	,0.3*(hDataMetm[ipt]->Integral()),0.005*hDataMetm[ipt]->Integral(),0.95*hDataMetm[ipt]->Integral());
    
    }
    if (ipt<10)
    {
      sprintf(histName,"nAntiSig_%d",ipt);
      nAntiSig[ipt] = new RooRealVar(histName,histName
	  ,hAntiDataMet[ipt]->Integral(),0,hAntiDataMet[ipt]->Integral());
      sprintf(histName,"nAntiSigp_%d",ipt);
      nAntiSigp[ipt] = new RooRealVar(histName,histName
	  ,hAntiDataMetp[ipt]->Integral(),0,hAntiDataMetp[ipt]->Integral());
      sprintf(histName,"nAntiSigm_%d",ipt);
      nAntiSigm[ipt] = new RooRealVar(histName,histName
	  ,hAntiDataMetm[ipt]->Integral(),0,hAntiDataMetm[ipt]->Integral());
    
      sprintf(histName,"nAntiQCD_%d",ipt);
      nAntiQCD[ipt] = new RooRealVar(histName,histName
          ,0.9*(hAntiDataMet[ipt]->Integral()),0,hAntiDataMet[ipt]->Integral());
      sprintf(histName,"nAntiQCDp_%d",ipt);
      nAntiQCDp[ipt] = new RooRealVar(histName,histName
          ,0.9*(hAntiDataMetp[ipt]->Integral()),0,hAntiDataMetp[ipt]->Integral());
      sprintf(histName,"nAntiQCDm_%d",ipt);
      nAntiQCDm[ipt] = new RooRealVar(histName,histName
          ,0.9*(hAntiDataMetm[ipt]->Integral()),0,hAntiDataMetm[ipt]->Integral());
      
      sprintf(histName,"dewk_%d",ipt);
      dewk[ipt] = new RooRealVar(histName,histName,0.01,0,5);
      dewk[ipt]->setVal(hAntiEWKMet[ipt]->Integral()/hAntiWmunuMet[ipt]->Integral());
      dewk[ipt]->setConstant(kTRUE);
   
      sprintf(histName,"dewkp_%d",ipt);
      dewkp[ipt] = new RooRealVar(histName,histName,0.01,0,5);
      dewkp[ipt]->setVal(hAntiEWKMetp[ipt]->Integral()/hAntiWmunuMetp[ipt]->Integral());
      dewkp[ipt]->setConstant(kTRUE);
      
      sprintf(histName,"dewkm_%d",ipt);
      dewkm[ipt] = new RooRealVar(histName,histName,0.01,0,5);
      dewkm[ipt]->setVal(hAntiEWKMetm[ipt]->Integral()/hAntiWmunuMetm[ipt]->Integral());
      dewkm[ipt]->setConstant(kTRUE);
    }else{
      sprintf(histName,"nAntiSig_%d",ipt);
      nAntiSig[ipt] = new RooRealVar(histName,histName
	  ,hHighWpTAnti_DataMet->Integral(),0,hHighWpTAnti_DataMet->Integral());
      sprintf(histName,"nAntiSigp_%d",ipt);
      nAntiSigp[ipt] = new RooRealVar(histName,histName
	  ,hHighWpTAnti_DataMetp->Integral(),0,hHighWpTAnti_DataMetp->Integral());
      sprintf(histName,"nAntiSigm_%d",ipt);
      nAntiSigm[ipt] = new RooRealVar(histName,histName
	  ,hHighWpTAnti_DataMetm->Integral(),0,hHighWpTAnti_DataMetm->Integral());
    
      sprintf(histName,"nAntiQCD_%d",ipt);
      nAntiQCD[ipt] = new RooRealVar(histName,histName
          ,0.9*(hHighWpTAnti_DataMet->Integral()),0,hHighWpTAnti_DataMet->Integral());
      sprintf(histName,"nAntiQCDp_%d",ipt);
      nAntiQCDp[ipt] = new RooRealVar(histName,histName
          ,0.9*(hHighWpTAnti_DataMetp->Integral()),0,hHighWpTAnti_DataMetp->Integral());
      sprintf(histName,"nAntiQCDm_%d",ipt);
      nAntiQCDm[ipt] = new RooRealVar(histName,histName
          ,0.9*(hHighWpTAnti_DataMetm->Integral()),0,hHighWpTAnti_DataMetm->Integral());
      
      sprintf(histName,"dewk_%d",ipt);
      dewk[ipt] = new RooRealVar(histName,histName,0.01,0,5);
      dewk[ipt]->setVal(hHighWpTAnti_EWKMet->Integral()/hHighWpTAnti_WmunuMet->Integral());
      dewk[ipt]->setConstant(kTRUE);
   
      sprintf(histName,"dewkp_%d",ipt);
      dewkp[ipt] = new RooRealVar(histName,histName,0.01,0,5);
      dewkp[ipt]->setVal(hHighWpTAnti_EWKMetp->Integral()/hHighWpTAnti_WmunuMetp->Integral());
      dewkp[ipt]->setConstant(kTRUE);
      
      sprintf(histName,"dewkm_%d",ipt);
      dewkm[ipt] = new RooRealVar(histName,histName,0.01,0,5);
      dewkm[ipt]->setVal(hHighWpTAnti_EWKMetm->Integral()/hHighWpTAnti_WmunuMetm->Integral());
      dewkm[ipt]->setConstant(kTRUE);
    } 
    sprintf(histName,"nQCD_%d",ipt);
    nQCD[ipt]  = new RooRealVar(histName,histName
	,0.3*(hDataMet[ipt]->Integral()),0,hDataMet[ipt]->Integral());
    sprintf(histName,"nQCDp_%d",ipt);
    nQCDp[ipt] = new RooRealVar(histName,histName
	,0.3*(hDataMetp[ipt]->Integral()),0,hDataMetp[ipt]->Integral());
    sprintf(histName,"nQCDm_%d",ipt);
    nQCDm[ipt] = new RooRealVar(histName,histName
	,0.3*(hDataMetm[ipt]->Integral()),0,hDataMetm[ipt]->Integral());
    
    sprintf(histName,"cewk_%d",ipt);
    cewk[ipt] = new RooRealVar(histName,histName,0.01,0,5);
    cewk[ipt]->setVal(hEWKMet[ipt]->Integral()/hWmunuMet[ipt]->Integral());
    cewk[ipt]->setConstant(kTRUE);
    
    sprintf(histName,"cewkp_%d",ipt);
    cewkp[ipt] = new RooRealVar(histName,histName,0.01,0,5);
    cewkp[ipt]->setVal(hEWKMetp[ipt]->Integral()/hWmunuMetp[ipt]->Integral());
    cewkp[ipt]->setConstant(kTRUE);
    
    sprintf(histName,"cewkm_%d",ipt);
    cewkm[ipt] = new RooRealVar(histName,histName,0.01,0,5);
    cewkm[ipt]->setVal(hEWKMetm[ipt]->Integral()/hWmunuMetm[ipt]->Integral());
    cewkm[ipt]->setConstant(kTRUE);
    
    sprintf(histName,"nEWK_%d",ipt);
    nEWK[ipt] = new RooFormulaVar(histName,histName
	,"@0*@1",RooArgList(*nSig[ipt],*cewk[ipt]));
    sprintf(histName,"nEWKp_%d",ipt);
    nEWKp[ipt] = new RooFormulaVar(histName,histName
	,"@0*@1",RooArgList(*nSigp[ipt],*cewkp[ipt]));
    sprintf(histName,"nEWKm_%d",ipt);
    nEWKm[ipt] = new RooFormulaVar(histName,histName
	,"@0*@1",RooArgList(*nSigm[ipt],*cewkm[ipt]));  
    
    sprintf(histName,"nAntiEWK_%d",ipt);
    nAntiEWK[ipt] = new RooFormulaVar(histName,histName
	,"@0*@1",RooArgList(*nAntiSig[ipt],*dewk[ipt]));
    sprintf(histName,"nAntiEWKp_%d",ipt);
    nAntiEWKp[ipt] = new RooFormulaVar(histName,histName
	,"@0*@1",RooArgList(*nAntiSigp[ipt],*dewkp[ipt]));
    sprintf(histName,"nAntiEWKm_%d",ipt);
    nAntiEWKm[ipt] = new RooFormulaVar(histName,histName
	,"@0*@1",RooArgList(*nAntiSigm[ipt],*dewkm[ipt]));

    sprintf(histName,"qcdmean_%d",ipt);
    qcdmean[ipt] = new RooRealVar(histName,histName,15,0,50);
    sprintf(histName,"qcdPmean_%d",ipt);
    qcdPmean[ipt] = new RooRealVar(histName,histName,15,0,50);
    sprintf(histName,"qcdMmean_%d",ipt);
    qcdMmean[ipt] = new RooRealVar(histName,histName,15,0,50);

    sprintf(histName,"qcdsigma1_%d",ipt);
    qcdsigma1[ipt] = new RooRealVar(histName,histName,25,0,75);
    sprintf(histName,"qcdPsigma1_%d",ipt);
    qcdPsigma1[ipt] = new RooRealVar(histName,histName,25,0,75);
    sprintf(histName,"qcdMsigma1_%d",ipt);
    qcdMsigma1[ipt] = new RooRealVar(histName,histName,25,0,75);
    
    sprintf(histName,"aqcdsigma1_%d",ipt);
    aqcdsigma1[ipt] = new RooRealVar(histName,histName,25,0,75);
    sprintf(histName,"aqcdPsigma1_%d",ipt);
    aqcdPsigma1[ipt] = new RooRealVar(histName,histName,25,0,75);
    sprintf(histName,"aqcdMsigma1_%d",ipt);
    aqcdMsigma1[ipt] = new RooRealVar(histName,histName,25,0,75);
    
    sprintf(histName,"qcdsigma2_%d",ipt);
    qcdsigma2[ipt] = new RooRealVar(histName,histName,25,0,75);
    sprintf(histName,"qcdPsigma2_%d",ipt);
    qcdPsigma2[ipt] = new RooRealVar(histName,histName,25,0,75);
    sprintf(histName,"qcdMsigma2_%d",ipt);
    qcdMsigma2[ipt] = new RooRealVar(histName,histName,25,0,75);
    
    sprintf(histName,"aqcdsigma2_%d",ipt);
    aqcdsigma2[ipt] = new RooRealVar(histName,histName,25,0,75);
    sprintf(histName,"aqcdPsigma2_%d",ipt);
    aqcdPsigma2[ipt] = new RooRealVar(histName,histName,25,0,75);
    sprintf(histName,"aqcdMsigma2_%d",ipt);
    aqcdMsigma2[ipt] = new RooRealVar(histName,histName,25,0,75);
    
    sprintf(histName,"qcda1_%d",ipt);
    qcda1[ipt] = new RooRealVar(histName,histName,0.01,-1,1);
    sprintf(histName,"qcdPa1_%d",ipt);
    qcdPa1[ipt] = new RooRealVar(histName,histName,0.01,-1,1);
    sprintf(histName,"qcdMa1_%d",ipt);
    qcdMa1[ipt] = new RooRealVar(histName,histName,0.01,-1,1);

    sprintf(histName,"qcda2_%d",ipt);
    qcda2[ipt] = new RooRealVar(histName,histName,0.01,-1,1);
    sprintf(histName,"qcdPa2_%d",ipt);
    qcdPa2[ipt] = new RooRealVar(histName,histName,0.01,-1,1);
    sprintf(histName,"qcdMa2_%d",ipt);
    qcdMa2[ipt] = new RooRealVar(histName,histName,0.01,-1,1);
    
    sprintf(histName,"Frac1_%d",ipt);
    Frac1[ipt]  = new RooRealVar(histName,histName,0.3,0,1);
    sprintf(histName,"Frac1P_%d",ipt);
    Frac1P[ipt] = new RooRealVar(histName,histName,0.3,0,1);
    sprintf(histName,"Frac1M_%d",ipt);
    Frac1M[ipt] = new RooRealVar(histName,histName,0.3,0,1);
    
    sprintf(histName,"Frac2_%d",ipt);
    Frac2[ipt]  = new RooRealVar(histName,histName,0.7,0,1);
    sprintf(histName,"Frac2P_%d",ipt);
    Frac2P[ipt] = new RooRealVar(histName,histName,0.7,0,1);
    sprintf(histName,"Frac2M_%d",ipt);
    Frac2M[ipt] = new RooRealVar(histName,histName,0.7,0,1);
    
    sprintf(histName,"dFrac1_%d",ipt);
    dFrac1[ipt]  = new RooRealVar(histName,histName,0.2,0,0.5);
    sprintf(histName,"dFrac1P_%d",ipt);
    dFrac1P[ipt] = new RooRealVar(histName,histName,0.2,0,0.5);
    sprintf(histName,"dFrac1M_%d",ipt);
    dFrac1M[ipt] = new RooRealVar(histName,histName,0.2,0,0.5);
    
    sprintf(histName,"dFrac2_%d",ipt);
    dFrac2[ipt]  = new RooRealVar(histName,histName,0.2,0,0.5);
    sprintf(histName,"dFrac2P_%d",ipt);
    dFrac2P[ipt] = new RooRealVar(histName,histName,0.2,0,0.5);
    sprintf(histName,"dFrac2M_%d",ipt);
    dFrac2M[ipt] = new RooRealVar(histName,histName,0.2,0,0.5);
    
    //Initial Values
    if (ipt == 0){
      nSig[ipt] -> setVal(74801);
      nSigp[ipt]-> setVal(43934.1);
      nSigm[ipt]-> setVal(30829.5);
      nAntiSig[ipt] -> setVal(26.9267);
      nAntiSigp[ipt]-> setVal(21.1389);
      nAntiSigm[ipt]-> setVal(5.68059);
      nQCD[ipt] -> setVal(56422.5);
      nQCDp[ipt]-> setVal(28739.5);
      nQCDm[ipt]-> setVal(27718.1);
      nAntiQCD[ipt] -> setVal(42488.6);
      nAntiQCDp[ipt]-> setVal(21922.7);
      nAntiQCDm[ipt]-> setVal(20565.9);
      qcdmean[ipt] ->setVal(0.0399263);
      qcdPmean[ipt]->setVal(4.32118e-09);
      qcdMmean[ipt]->setVal(1.01264e-09);
      qcdsigma1[ipt] ->setVal(10.7756);
      qcdPsigma1[ipt]->setVal(10.7471);
      qcdMsigma1[ipt]->setVal(10.9425);
      qcda1[ipt] ->setVal(0.14601);
      qcdPa1[ipt]->setVal(0.147688);
      qcdMa1[ipt]->setVal(0.142555);
      aqcdsigma1[ipt] ->setVal(10.7756);
      aqcdPsigma1[ipt]->setVal(10.7471);
      aqcdMsigma1[ipt]->setVal(10.9425);
    }else if (ipt == 1){
      nSig[ipt] -> setVal(14499.6);
      nSigp[ipt]-> setVal(8673.77);
      nSigm[ipt]-> setVal(5796.99);
      nAntiSig[ipt] -> setVal(0.000117028);
      nAntiSigp[ipt]-> setVal(2.03924e-05);
      nAntiSigm[ipt]-> setVal(5.99258e-07);
      nQCD[ipt] -> setVal(640.252);
      nQCDp[ipt]-> setVal(331.408);
      nQCDm[ipt]-> setVal(339.359);
      nAntiQCD[ipt] -> setVal(526.652);
      nAntiQCDp[ipt]-> setVal(299.701);
      nAntiQCDm[ipt]-> setVal(226.951);
      qcdmean[ipt] ->setVal(17.1871);
      qcdPmean[ipt]->setVal(17.2592);
      qcdMmean[ipt]->setVal(17.0766);
      qcdsigma1[ipt] ->setVal(11.6833);
      qcdPsigma1[ipt]->setVal(10.5063);
      qcdMsigma1[ipt]->setVal(15.0365);
      qcda1[ipt] ->setVal(0.0437592);
      qcdPa1[ipt]->setVal(0.0690869);
      qcdMa1[ipt]->setVal(-0.0442332);
      aqcdsigma1[ipt] ->setVal(11.6833);
      aqcdPsigma1[ipt]->setVal(10.5063);
      aqcdMsigma1[ipt]->setVal(15.0365);
    }else if (ipt == 2){
      nSig[ipt] -> setVal(15375);
      nSigp[ipt]-> setVal(8987);
      nSigm[ipt]-> setVal(6377.38);
      nAntiSig[ipt] -> setVal(91.2508);
      nAntiSigp[ipt]-> setVal(58.7272);
      nAntiSigm[ipt]-> setVal(24.7976);
      nQCD[ipt] -> setVal(912.979);
      nQCDp[ipt]-> setVal(472.954);
      nQCDm[ipt]-> setVal(451.119);
      nAntiQCD[ipt] -> setVal(1101.06);
      nAntiQCDp[ipt]-> setVal(515.046);
      nAntiQCDm[ipt]-> setVal(595.818);
      qcdmean[ipt] ->setVal(12.386);
      qcdPmean[ipt]->setVal(12.3976);
      qcdMmean[ipt]->setVal(12.3967);
      qcdsigma1[ipt] ->setVal(7.116);
      qcdPsigma1[ipt]->setVal(7.31652);
      qcdMsigma1[ipt]->setVal(6.70111);
      qcda1[ipt] ->setVal(0.111568);
      qcdPa1[ipt]->setVal(0.105727);
      qcdMa1[ipt]->setVal(0.136719);
      aqcdsigma1[ipt] ->setVal(7.116);
      aqcdPsigma1[ipt]->setVal(7.31652);
      aqcdMsigma1[ipt]->setVal(6.70111);
    }else if (ipt == 3){
      nSig[ipt] -> setVal(12153);
      nSigp[ipt]-> setVal(7236.17);
      nSigm[ipt]-> setVal(4905.17);
      nAntiSig[ipt] -> setVal(56.9367);
      nAntiSigp[ipt]-> setVal(36.2514);
      nAntiSigm[ipt]-> setVal(14.3742);
      nQCD[ipt] -> setVal(2420.27);
      nQCDp[ipt]-> setVal(1216.12);
      nQCDm[ipt]-> setVal(1216.91);
      nAntiQCD[ipt] -> setVal(2290.19);
      nAntiQCDp[ipt]-> setVal(1122.03);
      nAntiQCDm[ipt]-> setVal(1176.03);
      qcdmean[ipt] ->setVal(7.38242);
      qcdPmean[ipt]->setVal(7.35278);
      qcdMmean[ipt]->setVal(7.41877);
      qcdsigma1[ipt] ->setVal(7.71841);
      qcdPsigma1[ipt]->setVal(7.62938);
      qcdMsigma1[ipt]->setVal(7.61305);
      qcda1[ipt] ->setVal(0.119073);
      qcdPa1[ipt]->setVal(0.126624);
      qcdMa1[ipt]->setVal(0.125783);
      aqcdsigma1[ipt] ->setVal(7.71841);
      aqcdPsigma1[ipt]->setVal(7.62938);
      aqcdMsigma1[ipt]->setVal(7.61305);
    }else if (ipt == 4){
      nSig[ipt] -> setVal(10753.9);
      nSigp[ipt]-> setVal(6284.88);
      nSigm[ipt]-> setVal(4435.24);
      nAntiSig[ipt] -> setVal(14.3793);
      nAntiSigp[ipt]-> setVal(6.64878);
      nAntiSigm[ipt]-> setVal(0.000100531);
      nQCD[ipt] -> setVal(6702.36);
      nQCDp[ipt]-> setVal(3428.72);
      nQCDm[ipt]-> setVal(3309.81);
      nAntiQCD[ipt] -> setVal(5515.52);
      nAntiQCDp[ipt]-> setVal(2800.99);
      nAntiQCDm[ipt]-> setVal(2658.96);
      qcdmean[ipt] ->setVal(5.46999);
      qcdMmean[ipt]->setVal(5.65277);
      qcdsigma1[ipt] ->setVal(4.4329);
      qcdMsigma1[ipt]->setVal(5.30044);
      qcda1[ipt] ->setVal(0.222467);
      qcdPa1[ipt]->setVal(0.214281);
      qcdMa1[ipt]->setVal(0.221573);
      qcdsigma2[ipt] ->setVal(8.42163);
      qcdPsigma2[ipt]->setVal(8.60402);
      qcdMsigma2[ipt]->setVal(5.55646);
      qcda2[ipt] ->setVal(0.149918);
      qcdPa2[ipt]->setVal(0.150846);
      qcdMa2[ipt]->setVal(0.140031);
      Frac1[ipt] ->setVal(0.678958);
      Frac1P[ipt]->setVal(0.0254109);
      Frac1M[ipt]->setVal(0.597756);
      Frac2[ipt] ->setVal(0.300864);
      Frac2P[ipt]->setVal(0.893735);
      Frac2M[ipt]->setVal(0.456884);
      aqcdsigma1[ipt] ->setVal(4.4329);
      aqcdPsigma1[ipt]->setVal(4.39185);
      aqcdMsigma1[ipt]->setVal(5.30044);
      aqcdsigma2[ipt] ->setVal(8.42163);
      aqcdPsigma2[ipt]->setVal(8.60402);
      aqcdMsigma2[ipt]->setVal(5.55646);
    }else if (ipt == 5){
      nSig[ipt] -> setVal(6041.33);
      nSigp[ipt]-> setVal(3537.31);
      nSigm[ipt]-> setVal(2460.31);
      nAntiSig[ipt] -> setVal(9.90583e-07);
      nAntiSigp[ipt]-> setVal(3.23376e-05);
      nAntiSigm[ipt]-> setVal(4.84586e-08);
      nQCD[ipt] -> setVal(9564.79);
      nQCDp[ipt]-> setVal(4906.26);
      nQCDm[ipt]-> setVal(4707.75);
      nAntiQCD[ipt] -> setVal(6777.96);
      nAntiQCDp[ipt]-> setVal(3386.96);
      nAntiQCDm[ipt]-> setVal(3360.94);
      qcdsigma1[ipt] ->setVal(5.48791);
      qcdPsigma1[ipt]->setVal(5.2083);
      qcdMsigma1[ipt]->setVal(5.76412);
      qcda1[ipt] ->setVal(-0.272349);
      qcdPa1[ipt]->setVal(-0.266754);
      qcdMa1[ipt]->setVal(-0.273361);
      dFrac1[ipt] ->setVal(0.479271);
      dFrac1P[ipt]->setVal(0.5);
      dFrac1M[ipt]->setVal(0.44892);
      qcdsigma2[ipt] ->setVal(7.02199);
      qcdPsigma2[ipt]->setVal(6.93642);
      qcdMsigma2[ipt]->setVal(7.11994);
      qcda2[ipt] ->setVal(0.200897);
      qcdPa2[ipt]->setVal(0.205516);
      qcdMa2[ipt]->setVal(0.198893);
      dFrac2[ipt] ->setVal(0.477855);
      dFrac2P[ipt]->setVal(0.5);
      dFrac2M[ipt]->setVal(0.5);
      aqcdsigma1[ipt] ->setVal(1.25429);
      aqcdPsigma1[ipt]->setVal(1.15983);
      aqcdMsigma1[ipt]->setVal(1.25411);
      aqcdsigma2[ipt] ->setVal(6.76098);
      aqcdPsigma2[ipt]->setVal(6.56927);
      aqcdMsigma2[ipt]->setVal(6.8319);
    }else if (ipt == 6){
      nSig[ipt] -> setVal(5965.12);
      nSigp[ipt]-> setVal(3596.2);
      nSigm[ipt]-> setVal(2359.4);
      nAntiSig[ipt] -> setVal(2.84459);
      nAntiSigp[ipt]-> setVal(1.79112);
      nAntiSigm[ipt]-> setVal(1.62222e-07);
      nQCD[ipt] -> setVal(16007.8);
      nQCDp[ipt]-> setVal(8013.9);
      nQCDm[ipt]-> setVal(8016.53);
      nAntiQCD[ipt] -> setVal(11601.33);
      nAntiQCDp[ipt]-> setVal(6069.33);
      nAntiQCDm[ipt]-> setVal(5532);
      qcdsigma1[ipt] ->setVal(16.4608);
      qcdPsigma1[ipt]->setVal(10.5678);
      qcdMsigma1[ipt]->setVal(9.79437);
      qcda1[ipt] ->setVal(-0.426312);
      qcdPa1[ipt]->setVal(0.110942);
      qcdMa1[ipt]->setVal(0.143796);
      dFrac1[ipt] ->setVal(0.5);
      dFrac1P[ipt]->setVal(0.294399);
      dFrac1M[ipt]->setVal(0.5);
      qcdsigma2[ipt] ->setVal(9.81148);
      qcdPsigma2[ipt]->setVal(15.2015);
      qcdMsigma2[ipt]->setVal(16.68);
      qcda2[ipt] ->setVal(0.130821);
      qcdPa2[ipt]->setVal(-0.324381);
      qcdMa2[ipt]->setVal(-0.463181);
      dFrac2[ipt] ->setVal(0.5);
      dFrac2P[ipt]->setVal(0.4979);
      dFrac2M[ipt]->setVal(0.499997);
      aqcdsigma1[ipt] ->setVal(16.4608);
      aqcdPsigma1[ipt]->setVal(10.5678);
      aqcdMsigma1[ipt]->setVal(9.79437);
      aqcdsigma2[ipt] ->setVal(9.81148);
      aqcdPsigma2[ipt]->setVal(15.2015);
      aqcdMsigma2[ipt]->setVal(16.68);
    }else if (ipt == 7){
      nSig[ipt] -> setVal(3373.35);
      nSigp[ipt]-> setVal(1954.85);
      nSigm[ipt]-> setVal(1389.76);
      nAntiSig[ipt] -> setVal(5.89658);
      nAntiSigp[ipt]-> setVal(2.50604);
      nAntiSigm[ipt]-> setVal(2.51128);
      nQCD[ipt] -> setVal(10266);
      nQCDp[ipt]-> setVal(5210.16);
      nQCDm[ipt]-> setVal(5097.38);
      nAntiQCD[ipt] -> setVal(7440.51);
      nAntiQCDp[ipt]-> setVal(3863.33);
      nAntiQCDm[ipt]-> setVal(3579.18);
      qcdsigma1[ipt] ->setVal(47.2335);
      qcdPsigma1[ipt]->setVal(34.411);
      qcdMsigma1[ipt]->setVal(31.8372);
      qcda1[ipt] ->setVal(-0.563342);
      qcdPa1[ipt]->setVal(-0.299181);
      qcdMa1[ipt]->setVal(-0.664296);
      dFrac1[ipt] ->setVal(0.0205096);
      dFrac1P[ipt]->setVal(0.0315425);
      dFrac1M[ipt]->setVal(0.5);
      qcdsigma2[ipt] ->setVal(31.0753);
      qcdPsigma2[ipt]->setVal(29.9725);
      qcdMsigma2[ipt]->setVal(18.562);
      qcda2[ipt] ->setVal(-0.63675);
      qcdPa2[ipt]->setVal(-0.604079);
      qcdMa2[ipt]->setVal(-0.0610386);
      dFrac2[ipt] ->setVal(0.457178);
      dFrac2P[ipt]->setVal(0.499232);
      dFrac2M[ipt]->setVal(0.5);
      aqcdsigma1[ipt] ->setVal(47.2335);
      aqcdPsigma1[ipt]->setVal(34.411);
      aqcdMsigma1[ipt]->setVal(31.8372);
      aqcdsigma2[ipt] ->setVal(31.0753);
      aqcdPsigma2[ipt]->setVal(29.9725);
      aqcdMsigma2[ipt]->setVal(18.562);
    }else if (ipt == 8){
      nSig[ipt] -> setVal(3180.01);
      nSigp[ipt]-> setVal(1764.52);
      nSigm[ipt]-> setVal(1424.64);
      nAntiSig[ipt] -> setVal(1.21884e-05);
      nAntiSigp[ipt]-> setVal(7.88715e-08);
      nAntiSigm[ipt]-> setVal(9.64654e-09);
      nQCD[ipt] -> setVal(7416.27);
      nQCDp[ipt]-> setVal(3874.62);
      nQCDm[ipt]-> setVal(3516.82);
      nAntiQCD[ipt] -> setVal(5285.99);
      nAntiQCDp[ipt]-> setVal(2763);
      nAntiQCDm[ipt]-> setVal(2523);
      qcdsigma1[ipt] ->setVal(39.3815);
      qcdPsigma1[ipt]->setVal(37.2932);
      qcdMsigma1[ipt]->setVal(43.0451);
      qcda1[ipt] ->setVal(-0.500541);
      qcdPa1[ipt]->setVal(-0.446264);
      qcdMa1[ipt]->setVal(-0.596923);
      dFrac1[ipt] ->setVal(0.5);
      dFrac1P[ipt]->setVal(0.499995);
      dFrac1M[ipt]->setVal(0.393532);
      qcdsigma2[ipt] ->setVal(12.6948);
      qcdPsigma2[ipt]->setVal(13.3255);
      qcdMsigma2[ipt]->setVal(12.0182);
      qcda2[ipt] ->setVal(0.164526);
      qcdPa2[ipt]->setVal(0.15779);
      qcdMa2[ipt]->setVal(0.166378);
      dFrac2[ipt] ->setVal(0.26639);
      dFrac2P[ipt]->setVal(0.0899833);
      dFrac2M[ipt]->setVal(0.5);
      aqcdsigma1[ipt] ->setVal(39.3815);
      aqcdPsigma1[ipt]->setVal(37.2932);
      aqcdMsigma1[ipt]->setVal(43.0451);
      aqcdsigma2[ipt] ->setVal(12.6948);
      aqcdPsigma2[ipt]->setVal(13.3255);
      aqcdMsigma2[ipt]->setVal(12.0182);
    }else if (ipt == 9){
      nSig[ipt] -> setVal(2158.18);
      nSigp[ipt]-> setVal(1233.45);
      nSigm[ipt]-> setVal(930.985);
      nAntiSig[ipt] -> setVal(2.0908e-06);
      nAntiSigp[ipt]-> setVal(1.15197e-09);
      nAntiSigm[ipt]-> setVal(1.25979e-07);
      nQCD[ipt] -> setVal(2430.82);
      nQCDp[ipt]-> setVal(1255.23);
      nQCDm[ipt]-> setVal(1164.64);
      nAntiQCD[ipt] -> setVal(1539.99);
      nAntiQCDp[ipt]-> setVal(804.999);
      nAntiQCDm[ipt]-> setVal(734.98);
      qcdsigma1[ipt] ->setVal(17.5926);
      qcdPsigma1[ipt]->setVal(2.67624);
      qcdMsigma1[ipt]->setVal(21.3831);
      qcda1[ipt] ->setVal(-0.139205);
      qcdPa1[ipt]->setVal(-0.297966);
      qcdMa1[ipt]->setVal(-0.30412);
      dFrac1[ipt] ->setVal(0.5);
      dFrac1P[ipt]->setVal(0.499956);
      dFrac1M[ipt]->setVal(0.499995);
      qcdsigma2[ipt] ->setVal(24.5268);
      qcdPsigma2[ipt]->setVal(22.4994);
      qcdMsigma2[ipt]->setVal(26.54);
      qcda2[ipt] ->setVal(0.0121803);
      qcdPa2[ipt]->setVal(0.0457006);
      qcdMa2[ipt]->setVal(-0.024091);
      dFrac2[ipt] ->setVal(0.5);
      dFrac2P[ipt]->setVal(0.499998);
      dFrac2M[ipt]->setVal(0.499995);
      aqcdsigma1[ipt] ->setVal(17.5926);
      aqcdPsigma1[ipt]->setVal(13.5481);
      aqcdMsigma1[ipt]->setVal(21.3831);
      aqcdsigma2[ipt] ->setVal(24.5268);
      aqcdPsigma2[ipt]->setVal(22.4994);
      aqcdMsigma2[ipt]->setVal(26.54);
    }else if (ipt == 10){
      nSig[ipt] -> setVal(562.134);
      nSigp[ipt]-> setVal(313.594);
      nSigm[ipt]-> setVal(232.294);
      nAntiSig[ipt] -> setVal(2.05272e-07);
      nAntiSigp[ipt]-> setVal(8.52672e-07);
      nAntiSigm[ipt]-> setVal(1.21661e-09);
      nQCD[ipt] -> setVal(386.856);
      nQCDp[ipt]-> setVal(175.406);
      nQCDm[ipt]-> setVal(232.384);
      nAntiQCD[ipt] -> setVal(208.889);
      nAntiQCDp[ipt]-> setVal(122.732);
      nAntiQCDm[ipt]-> setVal(89.9626);
      qcdsigma1[ipt] ->setVal(0.0283783);
      qcdPsigma1[ipt]->setVal(20.2699);
      qcdMsigma1[ipt]->setVal(22.6586);
      qcda1[ipt] ->setVal(0.27462);
      qcdPa1[ipt]->setVal(-0.274271);
      qcdMa1[ipt]->setVal(-0.313617);
      dFrac1[ipt] ->setVal(7.96642e-05);
      dFrac1P[ipt]->setVal(0.499999);
      dFrac1M[ipt]->setVal(0.477816);
      qcdsigma2[ipt] ->setVal(15.283);
      qcdPsigma2[ipt]->setVal(16.051);
      qcdMsigma2[ipt]->setVal(15.8383);
      qcda2[ipt] ->setVal(0.162499);
      qcdPa2[ipt]->setVal(0.118942);
      qcdMa2[ipt]->setVal(0.228386);
      dFrac2[ipt] ->setVal(0.5);
      dFrac2P[ipt]->setVal(0.5);
      dFrac2M[ipt]->setVal(0.487604);
      aqcdsigma1[ipt] ->setVal(5.69312);
      aqcdPsigma1[ipt]->setVal(5.81669);
      aqcdMsigma1[ipt]->setVal(22.6586);
      aqcdsigma2[ipt] ->setVal(15.283);
      aqcdPsigma2[ipt]->setVal(16.051);
      aqcdMsigma2[ipt]->setVal(15.8383);
    }else if (ipt == 11){
      nSig[ipt] -> setVal(178.6752);
      nSigp[ipt]-> setVal(105.287);
      nSigm[ipt]-> setVal(73.3882);
      nAntiSig[ipt] -> setVal(8.93272e-07);
      nAntiSigp[ipt]-> setVal(8.80563e-07);
      nAntiSigm[ipt]-> setVal(1.27087e-08);
      nQCD[ipt] -> setVal(80.6883);
      nQCDp[ipt]-> setVal(48.9074);
      nQCDm[ipt]-> setVal(31.7809);
      nAntiQCD[ipt] -> setVal(221.8918);
      nAntiQCDp[ipt]-> setVal(131.905);
      nAntiQCDm[ipt]-> setVal(89.9868);
      qcdsigma1[ipt] ->setVal(6.23596);
      qcdPsigma1[ipt]->setVal(5.72016);
      qcdMsigma1[ipt]->setVal(6.23647);
      qcda1[ipt] ->setVal(-0.280424);
      qcdPa1[ipt]->setVal(-0.278688);
      qcdMa1[ipt]->setVal(-0.281934);
      dFrac1[ipt] ->setVal(0.4976205);
      dFrac1P[ipt]->setVal(0.5);
      dFrac1M[ipt]->setVal(0.499999);
      qcdsigma2[ipt] ->setVal(16.0165);
      qcdPsigma2[ipt]->setVal(17.8307);
      qcdMsigma2[ipt]->setVal(15.8982);
      qcda2[ipt] ->setVal(0.248564);
      qcdPa2[ipt]->setVal(0.102558);
      qcdMa2[ipt]->setVal(0.248447);
      dFrac2[ipt] ->setVal(0.49994);
      dFrac2P[ipt]->setVal(0.5);
      dFrac2M[ipt]->setVal(0.499999);
      aqcdsigma1[ipt] ->setVal(6.23596);
      aqcdPsigma1[ipt]->setVal(5.72016);
      aqcdMsigma1[ipt]->setVal(6.23647);
      aqcdsigma2[ipt] ->setVal(16.0165);
      aqcdPsigma2[ipt]->setVal(17.8307);
      aqcdMsigma2[ipt]->setVal(15.8982);
    }else if (ipt == 12){
      nSig[ipt] -> setVal(91.424);
      nSigp[ipt]-> setVal(53.9281);
      nSigm[ipt]-> setVal(33.8688);
      nAntiSig[ipt] -> setVal(4.33193e-07);
      nAntiSigp[ipt]-> setVal(2.10445e-11);
      nAntiSigm[ipt]-> setVal(2.62932e-06);
      nQCD[ipt] -> setVal(23.7482);
      nQCDp[ipt]-> setVal(7.85523);
      nQCDm[ipt]-> setVal(20.5325);
      nAntiQCD[ipt] -> setVal(221.818);
      nAntiQCDp[ipt]-> setVal(132);
      nAntiQCDm[ipt]-> setVal(85.966);
      qcdsigma1[ipt] ->setVal(5.14769);
      qcdPsigma1[ipt]->setVal(5.99326);
      qcdMsigma1[ipt]->setVal(5.37902);
      qcda1[ipt] ->setVal(0.281856);
      qcdPa1[ipt]->setVal(0.289049);
      qcdMa1[ipt]->setVal(0.283406);
      dFrac1[ipt] ->setVal(0.433415);
      dFrac1P[ipt]->setVal(0.433415);
      dFrac1M[ipt]->setVal(0.499978);
      qcdsigma2[ipt] ->setVal(15.2418);
      qcdPsigma2[ipt]->setVal(15.9374);
      qcdMsigma2[ipt]->setVal(15.6185);
      qcda2[ipt] ->setVal(0.159594);
      qcdPa2[ipt]->setVal(0.15815);
      qcdMa2[ipt]->setVal(0.14915);
      dFrac2[ipt] ->setVal(0.499865);
      dFrac2P[ipt]->setVal(0.46938);
      dFrac2M[ipt]->setVal(0.499995);
      aqcdsigma1[ipt] ->setVal(5.14769);
      aqcdPsigma1[ipt]->setVal(5.99326);
      aqcdMsigma1[ipt]->setVal(6.83763);
      aqcdsigma2[ipt] ->setVal(15.2418);
      aqcdPsigma2[ipt]->setVal(15.9374);
      aqcdMsigma2[ipt]->setVal(15.6185);
    }else if (ipt == 13){
      nSig[ipt] -> setVal(35.2164);
      nSigp[ipt]-> setVal(16.4683);
      nSigm[ipt]-> setVal(15.0173);
      nAntiSig[ipt] -> setVal(1.00015e-06);
      nAntiSigp[ipt]-> setVal(8.68027e-11);
      nAntiSigm[ipt]-> setVal(4.95537e-12);
      nQCD[ipt] -> setVal(40.7157);
      nQCDp[ipt]-> setVal(29.2021);
      nQCDm[ipt]-> setVal(16.4112);
      nAntiQCD[ipt] -> setVal(221.768);
      nAntiQCDp[ipt]-> setVal(131.881);
      nAntiQCDm[ipt]-> setVal(89.9998);
      qcdsigma1[ipt] ->setVal(33.9061);
      qcdPsigma1[ipt]->setVal(33.9314);
      qcdMsigma1[ipt]->setVal(33.1227);
      qcda1[ipt] ->setVal(-0.314078);
      qcdPa1[ipt]->setVal(-0.278158);
      qcdMa1[ipt]->setVal(-0.386199);
      dFrac1[ipt] ->setVal(0.499997);
      dFrac1P[ipt]->setVal(0.5);
      dFrac1M[ipt]->setVal(0.048127);
      qcdsigma2[ipt] ->setVal(61.4473);
      qcdPsigma2[ipt]->setVal(74.9997);
      qcdMsigma2[ipt]->setVal(30.9997);
      qcda2[ipt] ->setVal(0.170593);
      qcdPa2[ipt]->setVal(0.132836);
      qcdMa2[ipt]->setVal(0.267273);
      dFrac2[ipt] ->setVal(0.5);
      dFrac2P[ipt]->setVal(0.499998);
      dFrac2M[ipt]->setVal(0.391545);
      aqcdsigma1[ipt] ->setVal(5.69688);
      aqcdPsigma1[ipt]->setVal(5.56539);
      aqcdMsigma1[ipt]->setVal(45.0997);
      aqcdsigma2[ipt] ->setVal(14.5731);
      aqcdPsigma2[ipt]->setVal(15.9764);
      aqcdMsigma2[ipt]->setVal(8.06314);
    }

    //  
    //   Construct PDFs for fitting
    //
    // Signal PDFs
    sprintf(histName,"wmunuMet_%d",ipt);
    wmunuMet[ipt]  =new RooDataHist(histName,histName
	,RooArgSet(pfmet),hWmunuMet[ipt]);
    sprintf(histName,"wmunuMetp_%d",ipt);
    wmunuMetp[ipt] =new RooDataHist(histName,histName
        ,RooArgSet(pfmet),hWmunuMetp[ipt]);
    sprintf(histName,"wmunuMetm_%d",ipt);
    wmunuMetm[ipt] =new RooDataHist(histName,histName
        ,RooArgSet(pfmet),hWmunuMetm[ipt]);
  
    sprintf(histName,"pdfWm_%d",ipt);
    pdfWm[ipt] =new RooHistPdf (histName,histName, pfmet,*wmunuMet[ipt], 1);
    sprintf(histName,"pdfWmp_%d",ipt);
    pdfWmp[ipt]=new RooHistPdf (histName,histName,pfmet,*wmunuMetp[ipt],1);
    sprintf(histName,"pdfWmm_%d",ipt);
    pdfWmm[ipt]=new RooHistPdf (histName,histName,pfmet,*wmunuMetm[ipt],1); 
 
    // EWK+top PDFs
    sprintf(histName,"ewkMet_%d",ipt);
    ewkMet[ipt] =new RooDataHist(histName,histName
	,RooArgSet(pfmet),hEWKMet[ipt]);
    sprintf(histName,"ewkMetp_%d",ipt);
    ewkMetp[ipt]=new RooDataHist(histName,histName
        ,RooArgSet(pfmet),hEWKMetp[ipt]);
    sprintf(histName,"ewkMetm_%d",ipt);
    ewkMetm[ipt]=new RooDataHist(histName,histName
        ,RooArgSet(pfmet),hEWKMetm[ipt]);
  
    sprintf(histName,"pdfEWK_%d",ipt);
    pdfEWK[ipt] =new RooHistPdf (histName,histName,pfmet,*ewkMet[ipt], 1);
    sprintf(histName,"pdfEWKp_%d",ipt);
    pdfEWKp[ipt]=new RooHistPdf (histName,histName,pfmet,*ewkMetp[ipt],1); 
    sprintf(histName,"pdfEWKm_%d",ipt);
    pdfEWKm[ipt]=new RooHistPdf (histName,histName,pfmet,*ewkMetm[ipt],1); 
  
    // Anti-Signal & Anti-EWK+top PDFs
    if (ipt<10){
      sprintf(histName,"awmunuMet_%d",ipt);
      awmunuMet[ipt] =new RooDataHist(histName,histName
          ,RooArgSet(pfmet),hAntiWmunuMet[ipt]) ;
      sprintf(histName,"awmunuMetp_%d",ipt);
      awmunuMetp[ipt]=new RooDataHist(histName,histName
          ,RooArgSet(pfmet),hAntiWmunuMetp[ipt]);
      sprintf(histName,"awmunuMetm_%d",ipt);
      awmunuMetm[ipt]=new RooDataHist(histName,histName
          ,RooArgSet(pfmet),hAntiWmunuMetm[ipt]);
      
      sprintf(histName,"aewkMet_%d",ipt);
      aewkMet[ipt] =new RooDataHist(histName,histName
          ,RooArgSet(pfmet),hAntiEWKMet[ipt]);  
      sprintf(histName,"aewkMetp_%d",ipt);
      aewkMetp[ipt]=new RooDataHist(histName,histName
          ,RooArgSet(pfmet),hAntiEWKMetp[ipt]);  
      sprintf(histName,"aewkMetm_%d",ipt);
      aewkMetm[ipt]=new RooDataHist(histName,histName
          ,RooArgSet(pfmet),hAntiEWKMetm[ipt]);  
    }else{
      sprintf(histName,"awmunuMet_%d",ipt);
      awmunuMet[ipt] =new RooDataHist(histName,histName
          ,RooArgSet(pfmet),hHighWpTAnti_WmunuMet) ;
      sprintf(histName,"awmunuMetp_%d",ipt);
      awmunuMetp[ipt]=new RooDataHist(histName,histName
          ,RooArgSet(pfmet),hHighWpTAnti_WmunuMetp);
      sprintf(histName,"awmunuMetm_%d",ipt);
      awmunuMetm[ipt]=new RooDataHist(histName,histName
          ,RooArgSet(pfmet),hHighWpTAnti_WmunuMetm);
      
      sprintf(histName,"aewkMet_%d",ipt);
      aewkMet[ipt] =new RooDataHist(histName,histName
          ,RooArgSet(pfmet),hHighWpTAnti_EWKMet);  
      sprintf(histName,"aewkMetp_%d",ipt);
      aewkMetp[ipt]=new RooDataHist(histName,histName
          ,RooArgSet(pfmet),hHighWpTAnti_EWKMetp);  
      sprintf(histName,"aewkMetm_%d",ipt);
      aewkMetm[ipt]=new RooDataHist(histName,histName
          ,RooArgSet(pfmet),hHighWpTAnti_EWKMetm);  
    }
    sprintf(histName,"apdfWm_%d",ipt);
    apdfWm[ipt] =new RooHistPdf("awm", "awm", pfmet,*awmunuMet[ipt], 1);
    sprintf(histName,"apdfWmp_%d",ipt);
    apdfWmp[ipt]=new RooHistPdf(histName,histName,pfmet,*awmunuMetp[ipt],1);
    sprintf(histName,"apdfWmm_%d",ipt);
    apdfWmm[ipt]=new RooHistPdf(histName,histName,pfmet,*awmunuMetm[ipt],1); 
  
    sprintf(histName,"apdfEWK_%d",ipt);
    apdfEWK[ipt] =new RooHistPdf(histName,histName,pfmet,*aewkMet[ipt], 1);
    sprintf(histName,"apdfEWKp_%d",ipt);
    apdfEWKp[ipt]=new RooHistPdf(histName,histName,pfmet,*aewkMetp[ipt],1);
    sprintf(histName,"apdfEWKm_%d",ipt);
    apdfEWKm[ipt]=new RooHistPdf(histName,histName,pfmet,*aewkMetm[ipt],1);

    sprintf(histName,"dataMet_%d",ipt);
    dataMet[ipt]  =new RooDataHist(histName,histName,  RooArgSet(pfmet), hDataMet[ipt]);
    sprintf(histName,"dataMetp_%d",ipt);
    dataMetp[ipt]  =new RooDataHist(histName,histName, RooArgSet(pfmet), hDataMetp[ipt]);
    sprintf(histName,"dataMetm_%d",ipt);
    dataMetm[ipt]  =new RooDataHist(histName,histName, RooArgSet(pfmet), hDataMetm[ipt]);
    
    if (ipt<10)
    {
      sprintf(histName,"antiMet_%d",ipt);
      antiMet[ipt]  =new RooDataHist(histName,histName,  RooArgSet(pfmet), hAntiDataMet[ipt]);
      sprintf(histName,"antiMetp_%d",ipt);
      antiMetp[ipt]  =new RooDataHist(histName,histName, RooArgSet(pfmet), hAntiDataMetp[ipt]);
      sprintf(histName,"antiMetm_%d",ipt);
      antiMetm[ipt]  =new RooDataHist(histName,histName, RooArgSet(pfmet), hAntiDataMetm[ipt]);
    }else{
      sprintf(histName,"antiMet_%d",ipt);
      antiMet[ipt]  =new RooDataHist(histName,histName, RooArgSet(pfmet),  hHighWpTAnti_DataMet);
      sprintf(histName,"antiMetp_%d",ipt);
      antiMetp[ipt]  =new RooDataHist(histName,histName, RooArgSet(pfmet), hHighWpTAnti_DataMetp);
      sprintf(histName,"antiMetm_%d",ipt);
      antiMetm[ipt]  =new RooDataHist(histName,histName, RooArgSet(pfmet), hHighWpTAnti_DataMetm);
    }

    sprintf(histName,"dataTotal_%d",ipt);
    dataTotal[ipt]=new RooDataHist(histName,histName, RooArgList(pfmet), Index(rooCat),
                          Import("Select", *dataMet[ipt]),
                          Import("Anti",   *antiMet[ipt]));
    
    sprintf(histName,"dataTotalp_%d",ipt);
    dataTotalp[ipt]=new RooDataHist(histName,histName, RooArgList(pfmet), Index(rooCat),
                           Import("Select", *dataMetp[ipt]),
                           Import("Anti",   *antiMetp[ipt]));
    
    sprintf(histName,"dataTotalm_%d",ipt);
    dataTotalm[ipt]=new RooDataHist(histName,histName, RooArgList(pfmet), Index(rooCat),
                           Import("Select", *dataMetm[ipt]),
                           Import("Anti",   *antiMetm[ipt]));
    //QCD PDFs
    if (ipt<4){
      //Modified Rayleigh Function - Bins 0-3
      
      //sprintf(histName,"qcd_%d",ipt);
      //qcd[ipt] =new CPepeModelMean(histName, pfmet);
      //sprintf(histName,"qcdp_%d",ipt);
      //qcdp[ipt] =new CPepeModelMean(histName,pfmet);
      //sprintf(histName,"qcdm_%d",ipt);
      //qcdm[ipt] =new CPepeModelMean(histName,pfmet);
      
      sprintf(histName,"qcd_%d",ipt);
      qcd[ipt] =new CPepeModelMean(histName, pfmet,qcdmean[ipt], qcdsigma1[ipt], qcda1[ipt]);
      sprintf(histName,"qcdp_%d",ipt);
      qcdp[ipt] =new CPepeModelMean(histName,pfmet,qcdPmean[ipt],qcdPsigma1[ipt],qcdPa1[ipt]);
      sprintf(histName,"qcdm_%d",ipt);
      qcdm[ipt] =new CPepeModelMean(histName,pfmet,qcdMmean[ipt],qcdMsigma1[ipt],qcdMa1[ipt]);
      
      sprintf(histName,"aqcd_%d",ipt);
      aqcd[ipt] =new CPepeModelMean(histName,pfmet,qcd[ipt]->mean, aqcdsigma1[ipt], qcd[ipt]->a1);
      sprintf(histName,"aqcdp_%d",ipt);
      aqcdp[ipt]=new CPepeModelMean(histName,pfmet,qcdp[ipt]->mean,aqcdPsigma1[ipt],qcdp[ipt]->a1);
      sprintf(histName,"aqcdm_%d",ipt);
      aqcdm[ipt]=new CPepeModelMean(histName,pfmet,qcdm[ipt]->mean,aqcdMsigma1[ipt],qcdm[ipt]->a1);
      
      // Signal + Background PDFs
      sprintf(histName,"pdfMet_%d",ipt);
      pdfMet[ipt] =new RooAddPdf(histName,histName
          ,RooArgList(*pdfWm[ipt], *pdfEWK[ipt], *(qcd[ipt]->model))
          ,RooArgList(*nSig[ipt], *nEWK[ipt], *nQCD[ipt]));
      sprintf(histName,"pdfMetp_%d",ipt);
      pdfMetp[ipt] =new RooAddPdf(histName,histName
          ,RooArgList(*pdfWmp[ipt],*pdfEWKp[ipt],*(qcdp[ipt]->model))
          ,RooArgList(*nSigp[ipt],*nEWKp[ipt],*nQCDp[ipt]));
      sprintf(histName,"pdfMetm_%d",ipt);
      pdfMetm[ipt] =new RooAddPdf(histName,histName
          ,RooArgList(*pdfWmm[ipt],*pdfEWKm[ipt],*(qcdm[ipt]->model))
          ,RooArgList(*nSigm[ipt],*nEWKm[ipt],*nQCDm[ipt]));
     
      sprintf(histName,"apdfMet_%d",ipt);
      apdfMet[ipt] =new RooAddPdf(histName,histName
          ,RooArgList(*apdfWm[ipt],*apdfEWK[ipt],*(aqcd[ipt]->model))
          ,RooArgList(*nAntiSig[ipt],*nAntiEWK[ipt],*nAntiQCD[ipt]));
      sprintf(histName,"apdfMetp_%d",ipt);
      apdfMetp[ipt] =new RooAddPdf(histName,histName
          ,RooArgList(*apdfWmp[ipt],*apdfEWKp[ipt],*(aqcdp[ipt]->model))
          ,RooArgList(*nAntiSigp[ipt],*nAntiEWKp[ipt],*nAntiQCDp[ipt]));
      sprintf(histName,"apdfMetm_%d",ipt);
      apdfMetm[ipt] =new RooAddPdf(histName,histName
          ,RooArgList(*apdfWmm[ipt],*apdfEWKm[ipt],*(aqcdm[ipt]->model))
          ,RooArgList(*nAntiSigm[ipt],*nAntiEWKm[ipt],*nAntiQCDm[ipt]));
    }else if (ipt == 4){
      //Rayleigh Plus Modified Rayleigh - Bin 4
      
      //sprintf(histName,"qcd1_%d",ipt);
      //qcd1[ipt]  = new CPepePlusMod(histName,pfmet);
      //sprintf(histName,"qcd1p_%d",ipt);
      //qcd1p[ipt] = new CPepePlusMod(histName,pfmet);
      //sprintf(histName,"qcd1m_%d",ipt);
      //qcd1m[ipt] = new CPepePlusMod(histName,pfmet);
      
      sprintf(histName,"qcd1_%d",ipt);
      qcd1[ipt]  = new CPepePlusMod(histName,pfmet,qcdmean[ipt],qcdsigma1[ipt], qcda1[ipt], Frac1[ipt],qcdsigma2[ipt], qcda2[ipt], Frac2[ipt]);
      sprintf(histName,"qcd1p_%d",ipt);
      qcd1p[ipt] = new CPepePlusMod(histName,pfmet,qcdPmean[ipt],qcdPsigma1[ipt], qcdPa1[ipt], Frac1P[ipt],qcdPsigma2[ipt], qcdPa2[ipt], Frac2P[ipt]);
      sprintf(histName,"qcd1m_%d",ipt);
      qcd1m[ipt] = new CPepePlusMod(histName,pfmet,qcdMmean[ipt],qcdMsigma1[ipt], qcdMa1[ipt], Frac1M[ipt],qcdMsigma2[ipt], qcdMa2[ipt], Frac2M[ipt]);
      
      sprintf(histName,"aqcd1_%d",ipt);
      aqcd1[ipt] = new CPepePlusMod(histName,pfmet
	  ,qcd1[ipt]->m1,aqcdsigma1[ipt],qcd1[ipt]->a1,qcd1[ipt]->f1,aqcdsigma2[ipt],qcd1[ipt]->a2,qcd1[ipt]->f2);
      sprintf(histName,"aqcd1p_%d",ipt);
      aqcd1p[ipt] = new CPepePlusMod(histName,pfmet
	  ,qcd1p[ipt]->m1,aqcdPsigma1[ipt],qcd1p[ipt]->a1,qcd1p[ipt]->f1,aqcdPsigma2[ipt],qcd1p[ipt]->a2,qcd1p[ipt]->f2);
      sprintf(histName,"aqcd1m_%d",ipt);
      aqcd1m[ipt] = new CPepePlusMod(histName,pfmet
	  ,qcd1m[ipt]->m1,aqcdMsigma1[ipt],qcd1m[ipt]->a1,qcd1m[ipt]->f1,aqcdMsigma2[ipt],qcd1m[ipt]->a2,qcd1m[ipt]->f2);
      
      // Signal + Background PDFs
      sprintf(histName,"pdfMet_%d",ipt);
      pdfMet[ipt] =new RooAddPdf(histName,histName
	  ,RooArgList(*pdfWm[ipt],*pdfEWK[ipt],*(qcd1[ipt]->model))
	  ,RooArgList(*nSig[ipt],*nEWK[ipt],*nQCD[ipt]));
      sprintf(histName,"pdfMetp_%d",ipt);
      pdfMetp[ipt] =new RooAddPdf(histName,histName
	  ,RooArgList(*pdfWmp[ipt],*pdfEWKp[ipt],*(qcd1p[ipt]->model))
	  ,RooArgList(*nSigp[ipt],*nEWKp[ipt],*nQCDp[ipt]));
      sprintf(histName,"pdfMetm_%d",ipt);
      pdfMetm[ipt] =new RooAddPdf(histName,histName
	  ,RooArgList(*pdfWmm[ipt],*pdfEWKm[ipt],*(qcd1m[ipt]->model))
	  ,RooArgList(*nSigm[ipt],*nEWKm[ipt],*nQCDm[ipt]));
      
      if(hAntiWmunuMet[ipt]->Integral() > 0)
      {
	sprintf(histName,"apdfMet_%d",ipt);
	apdfMet[ipt] =new RooAddPdf(histName,histName
	    ,RooArgList(*apdfWm[ipt],*apdfEWK[ipt],*(aqcd1[ipt]->model))
	    ,RooArgList(*nAntiSig[ipt],*nAntiEWK[ipt],*nAntiQCD[ipt]));
      }else if(hAntiEWKMet[ipt]->Integral() > 0)
      {
	sprintf(histName,"apdfMet_%d",ipt);
	apdfMet[ipt] =new RooAddPdf(histName,histName
	    ,RooArgList(*apdfEWK[ipt],*(aqcd1[ipt]->model))
	    ,RooArgList(*nAntiEWK[ipt],*nAntiQCD[ipt]));
	nAntiSig[ipt]->setVal(0);
      }else
      {
	sprintf(histName,"apdfMet_%d",ipt);
	apdfMet[ipt] =new RooAddPdf(histName,histName
	    ,RooArgList(*(aqcd1[ipt]->model))
	    ,RooArgList(*nAntiQCD[ipt]));
	nAntiSig[ipt]->setVal(0);
      }
      
      if(hAntiWmunuMetp[ipt]->Integral() > 0)
      {
	sprintf(histName,"apdfMetp_%d",ipt);
	apdfMetp[ipt] =new RooAddPdf(histName,histName
	    ,RooArgList(*apdfWmp[ipt],*apdfEWKp[ipt],*(aqcd1p[ipt]->model))
	    ,RooArgList(*nAntiSigp[ipt],*nAntiEWKp[ipt],*nAntiQCDp[ipt]));
      }else if(hAntiEWKMetp[ipt]->Integral() > 0)
      {
	sprintf(histName,"apdfMetp_%d",ipt);
	apdfMetp[ipt] =new RooAddPdf(histName,histName
	    ,RooArgList(*apdfEWKp[ipt],*(aqcd1p[ipt]->model))
	    ,RooArgList(*nAntiEWKp[ipt],*nAntiQCDp[ipt]));
	nAntiSigp[ipt]->setVal(0);
      }else{
	sprintf(histName,"apdfMetp_%d",ipt);
	apdfMetp[ipt] =new RooAddPdf(histName,histName
	    ,RooArgList(*(aqcd1p[ipt]->model))
	    ,RooArgList(*nAntiQCDp[ipt]));
	nAntiSigp[ipt]->setVal(0);
      }
      
      if(hAntiWmunuMetm[ipt]->Integral() > 0)
      {
	sprintf(histName,"apdfMetm_%d",ipt);
	apdfMetm[ipt] =new RooAddPdf(histName,histName
	    ,RooArgList(*apdfWmm[ipt],*apdfEWKm[ipt],*(aqcd1m[ipt]->model))
	    ,RooArgList(*nAntiSigm[ipt],*nAntiEWKm[ipt],*nAntiQCDm[ipt]));
      }else if(hAntiEWKMetm[ipt]->Integral() > 0 || hHighWpTAnti_EWKMetm->Integral() > 0)
      {
	sprintf(histName,"apdfMetm_%d",ipt);
	apdfMetm[ipt] =new RooAddPdf(histName,histName
	    ,RooArgList(*apdfEWKm[ipt],*(aqcd1m[ipt]->model))
	    ,RooArgList(*nAntiEWKm[ipt],*nAntiQCDm[ipt]));
	nAntiSigm[ipt]->setVal(0);
      }else{
	sprintf(histName,"apdfMetm_%d",ipt);
	apdfMetm[ipt] =new RooAddPdf(histName,histName
	    ,RooArgList(*(aqcd1m[ipt]->model))
	    ,RooArgList(*nAntiQCDm[ipt]));
	nAntiSigm[ipt]->setVal(0);
      }
    }else if (ipt > 4){
      // Double Rayleigh - Bins 5-13
 
      //sprintf(histName,"qcd2_%d",ipt);
      //qcd2[ipt]  = new CPepeDouble(histName,pfmet);
      //sprintf(histName,"qcd2p_%d",ipt);
      //qcd2p[ipt] = new CPepeDouble(histName,pfmet);
      //sprintf(histName,"qcd2m_%d",ipt);
      //qcd2m[ipt] = new CPepeDouble(histName,pfmet);
      
      sprintf(histName,"qcd2_%d",ipt);
      qcd2[ipt]  = new CPepeDouble(histName,pfmet,qcdsigma1[ipt], qcda1[ipt], dFrac1[ipt], qcdsigma2[ipt], qcda2[ipt],   dFrac2[ipt]);
      sprintf(histName,"qcd2p_%d",ipt);
      qcd2p[ipt] = new CPepeDouble(histName,pfmet,qcdPsigma1[ipt],qcdPa1[ipt],dFrac1P[ipt],qcdPsigma2[ipt], qcdPa2[ipt], dFrac2P[ipt]);
      sprintf(histName,"qcd2m_%d",ipt);
      qcd2m[ipt] = new CPepeDouble(histName,pfmet,qcdMsigma1[ipt],qcdMa1[ipt],dFrac1M[ipt],qcdMsigma2[ipt], qcdMa2[ipt], dFrac2M[ipt]);
      
      sprintf(histName,"aqcd2_%d",ipt);
      aqcd2[ipt] = new CPepeDouble(histName,pfmet
	  ,aqcdsigma1[ipt],qcd2[ipt]->a1,qcd2[ipt]->frac1,aqcdsigma2[ipt],qcd2[ipt]->a2,qcd2[ipt]->frac2);
      sprintf(histName,"aqcd2p_%d",ipt);
      aqcd2p[ipt] = new CPepeDouble(histName,pfmet
	  ,aqcdPsigma1[ipt],qcd2p[ipt]->a1,qcd2p[ipt]->frac1,aqcdPsigma2[ipt],qcd2p[ipt]->a2,qcd2p[ipt]->frac2);
      sprintf(histName,"aqcd2m_%d",ipt);
      aqcd2m[ipt] = new CPepeDouble(histName,pfmet
	  ,aqcdMsigma1[ipt],qcd2m[ipt]->a1,qcd2m[ipt]->frac1,aqcdMsigma2[ipt],qcd2m[ipt]->a2,qcd2m[ipt]->frac2);
      
      // Signal + Background PDFs
      sprintf(histName,"pdfMet_%d",ipt);
      pdfMet[ipt] =new RooAddPdf(histName,histName
          ,RooArgList(*pdfWm[ipt],*pdfEWK[ipt],*(qcd2[ipt]->model))
          ,RooArgList(*nSig[ipt],*nEWK[ipt],*nQCD[ipt]));
      sprintf(histName,"pdfMetp_%d",ipt);
      pdfMetp[ipt] =new RooAddPdf(histName,histName
          ,RooArgList(*pdfWmp[ipt],*pdfEWKp[ipt],*(qcd2p[ipt]->model))
          ,RooArgList(*nSigp[ipt],*nEWKp[ipt],*nQCDp[ipt]));
      sprintf(histName,"pdfMetm_%d",ipt);
      pdfMetm[ipt] =new RooAddPdf(histName,histName
          ,RooArgList(*pdfWmm[ipt],*pdfEWKm[ipt],*(qcd2m[ipt]->model))
          ,RooArgList(*nSigm[ipt],*nEWKm[ipt],*nQCDm[ipt]));

      if(hAntiWmunuMet[ipt]->Integral() > 0 || hHighWpTAnti_WmunuMet->Integral() > 0)
      {
	sprintf(histName,"apdfMet_%d",ipt);
        apdfMet[ipt] =new RooAddPdf(histName,histName
            ,RooArgList(*apdfWm[ipt],*apdfEWK[ipt],*(aqcd2[ipt]->model))
            ,RooArgList(*nAntiSig[ipt],*nAntiEWK[ipt],*nAntiQCD[ipt]));
      }else if(hAntiEWKMet[ipt]->Integral() > 0 || hHighWpTAnti_EWKMet->Integral() > 0)
      {
        sprintf(histName,"apdfMet_%d",ipt);
        apdfMet[ipt] =new RooAddPdf(histName,histName
            ,RooArgList(*apdfEWK[ipt],*(aqcd2[ipt]->model))
            ,RooArgList(*nAntiEWK[ipt],*nAntiQCD[ipt]));
        nAntiSig[ipt]->setVal(0);
      }else
      {
        sprintf(histName,"apdfMet_%d",ipt);
        apdfMet[ipt] =new RooAddPdf(histName,histName
            ,RooArgList(*(aqcd2[ipt]->model))
            ,RooArgList(*nAntiQCD[ipt]));
        nAntiSig[ipt]->setVal(0);
      }

      if(hAntiWmunuMetp[ipt]->Integral() > 0 || hHighWpTAnti_WmunuMetp->Integral() > 0)
      {
        sprintf(histName,"apdfMetp_%d",ipt);
        apdfMetp[ipt] =new RooAddPdf(histName,histName
            ,RooArgList(*apdfWmp[ipt],*apdfEWKp[ipt],*(aqcd2p[ipt]->model))
            ,RooArgList(*nAntiSigp[ipt],*nAntiEWKp[ipt],*nAntiQCDp[ipt]));
      }else if(hAntiEWKMetp[ipt]->Integral() > 0 || hHighWpTAnti_EWKMetp->Integral() > 0)
      {
        sprintf(histName,"apdfMetp_%d",ipt);
        apdfMetp[ipt] =new RooAddPdf(histName,histName
            ,RooArgList(*apdfEWKp[ipt],*(aqcd2p[ipt]->model))
            ,RooArgList(*nAntiEWKp[ipt],*nAntiQCDp[ipt]));
        nAntiSigp[ipt]->setVal(0);
      }else{
        sprintf(histName,"apdfMetp_%d",ipt);
        apdfMetp[ipt] =new RooAddPdf(histName,histName
            ,RooArgList(*(aqcd2p[ipt]->model))
            ,RooArgList(*nAntiQCDp[ipt]));
        nAntiSigp[ipt]->setVal(0);
      }

      if(hAntiWmunuMetm[ipt]->Integral() > 0 || hHighWpTAnti_WmunuMetm->Integral() > 0)
      {
        sprintf(histName,"apdfMetm_%d",ipt);
        apdfMetm[ipt] =new RooAddPdf(histName,histName
            ,RooArgList(*apdfWmm[ipt],*apdfEWKm[ipt],*(aqcd2m[ipt]->model))
            ,RooArgList(*nAntiSigm[ipt],*nAntiEWKm[ipt],*nAntiQCDm[ipt]));
      }else if(hAntiEWKMetm[ipt]->Integral() > 0 || hHighWpTAnti_EWKMetm->Integral() > 0)
      {
        sprintf(histName,"apdfMetm_%d",ipt);
        apdfMetm[ipt] =new RooAddPdf(histName,histName
            ,RooArgList(*apdfEWKm[ipt],*(aqcd2m[ipt]->model))
            ,RooArgList(*nAntiEWKm[ipt],*nAntiQCDm[ipt]));
        nAntiSigm[ipt]->setVal(0);
      }else{
        sprintf(histName,"apdfMetm_%d",ipt);
        apdfMetm[ipt] =new RooAddPdf(histName,histName
            ,RooArgList(*(aqcd2m[ipt]->model))
            ,RooArgList(*nAntiQCDm[ipt]));
        nAntiSigm[ipt]->setVal(0);
      }
    }
    // PDF for simultaneous fit
    sprintf(histName,"pdfTotal_%d",ipt);
    pdfTotal[ipt]= new RooSimultaneous(histName,histName,rooCat);
    pdfTotal[ipt]->addPdf(*pdfMet[ipt], "Select");
    pdfTotal[ipt]->addPdf(*apdfMet[ipt],"Anti");
    
    sprintf(histName,"pdfTotalp_%d",ipt);
    pdfTotalp[ipt]= new RooSimultaneous(histName,histName,rooCat);
    pdfTotalp[ipt]->addPdf(*pdfMetp[ipt], "Select");
    pdfTotalp[ipt]->addPdf(*apdfMetp[ipt],"Anti");
      
    sprintf(histName,"pdfTotalm_%d",ipt);
    pdfTotalm[ipt]=new RooSimultaneous(histName,histName,rooCat);
    pdfTotalm[ipt]->addPdf(*pdfMetm[ipt], "Select");
    pdfTotalm[ipt]->addPdf(*apdfMetm[ipt],"Anti");
    
    if (QCDFix)
    {
      //nQCD[ipt]	->setConstant(kTRUE);
      //nQCDp[ipt]	->setConstant(kTRUE);
      //nQCDm[ipt]	->setConstant(kTRUE);
      //nAntiQCD[ipt]	->setConstant(kTRUE);
      //nAntiQCDp[ipt]	->setConstant(kTRUE);
      //nAntiQCDm[ipt]	->setConstant(kTRUE);
      if (ipt<4){
	qcdmean[ipt]	->setConstant(kTRUE);
        qcdPmean[ipt]	->setConstant(kTRUE);
        qcdMmean[ipt]	->setConstant(kTRUE);
        qcdsigma1[ipt]	->setConstant(kTRUE);
        qcdPsigma1[ipt]	->setConstant(kTRUE);
        qcdMsigma1[ipt]	->setConstant(kTRUE);
        qcda1[ipt]	->setConstant(kTRUE);
        qcdPa1[ipt]	->setConstant(kTRUE);
        qcdMa1[ipt]	->setConstant(kTRUE);
      }else if (ipt == 4){
        qcdmean[ipt]	->setConstant(kTRUE);
        qcdPmean[ipt]	->setConstant(kTRUE);
        qcdMmean[ipt]	->setConstant(kTRUE);
        qcdsigma1[ipt]	->setConstant(kTRUE);
        qcdPsigma1[ipt]	->setConstant(kTRUE);
        qcdMsigma1[ipt]	->setConstant(kTRUE);
        qcda1[ipt]	->setConstant(kTRUE);
        qcdPa1[ipt]	->setConstant(kTRUE);
        qcdMa1[ipt]	->setConstant(kTRUE);
        qcdsigma2[ipt]	->setConstant(kTRUE);
        qcdPsigma2[ipt]	->setConstant(kTRUE);
        qcdMsigma2[ipt]	->setConstant(kTRUE);
        qcda2[ipt]	->setConstant(kTRUE);
        qcdPa2[ipt]	->setConstant(kTRUE);
        qcdMa2[ipt]	->setConstant(kTRUE);
        Frac1[ipt]	->setConstant(kTRUE);
        Frac1P[ipt]	->setConstant(kTRUE);
        Frac1M[ipt]	->setConstant(kTRUE);
        Frac2[ipt]	->setConstant(kTRUE);
        Frac2P[ipt]	->setConstant(kTRUE);
        Frac2M[ipt]	->setConstant(kTRUE);
    }else{
        qcdsigma1[ipt]	-> setConstant(kTRUE);
        qcdPsigma1[ipt]	-> setConstant(kTRUE);
        qcdMsigma1[ipt]	-> setConstant(kTRUE);
        qcda1[ipt]	-> setConstant(kTRUE);
        qcdPa1[ipt]	-> setConstant(kTRUE);
        qcdMa1[ipt]	-> setConstant(kTRUE);
        dFrac1[ipt]	-> setConstant(kTRUE);
        dFrac1P[ipt]	-> setConstant(kTRUE);
        dFrac1M[ipt]	-> setConstant(kTRUE);
        qcdsigma2[ipt]	-> setConstant(kTRUE);
        qcdPsigma2[ipt]	-> setConstant(kTRUE);
        qcdMsigma2[ipt]	-> setConstant(kTRUE);
        qcda2[ipt]	-> setConstant(kTRUE);
        qcdPa2[ipt]	-> setConstant(kTRUE);
        qcdMa2[ipt]	-> setConstant(kTRUE);
        dFrac2[ipt]	-> setConstant(kTRUE);
        dFrac2P[ipt]	-> setConstant(kTRUE);
        dFrac2M[ipt]	-> setConstant(kTRUE);
    }
    }
    // Perform fits
    fitRes[ipt]  = pdfTotal[ipt] ->fitTo(*dataTotal[ipt],Extended(),Minos(kTRUE),Save(kTRUE));
    fitResp[ipt] = pdfTotalp[ipt]->fitTo(*dataTotalp[ipt],Extended(),Minos(kTRUE),Save(kTRUE));
    fitResm[ipt] = pdfTotalm[ipt]->fitTo(*dataTotalm[ipt],Extended(),Minos(kTRUE),Save(kTRUE));
    
    // Use histogram version of fitted PDFs to make ratio plots
    // (Will also use PDF histograms later for Chi^2 and KS tests)
    hPdfMet = (TH1D*)(pdfMet[ipt]->createHistogram("hPdfMet", pfmet));
    hPdfMet->Scale(
	(nSig[ipt]->getVal()+nEWK[ipt]->getVal()+nQCD[ipt]->getVal())/hPdfMet->Integral());
    hMetDiff = makeDiffHist(hDataMet[ipt],hPdfMet,"hMetDiff");
    hMetDiff->SetMarkerStyle(kFullCircle);
    hMetDiff->SetMarkerSize(0.9);
     
    hPdfMetp = (TH1D*)(pdfMetp[ipt]->createHistogram("hPdfMetp", pfmet));
    hPdfMetp->Scale(
	(nSigp[ipt]->getVal()+nEWKp[ipt]->getVal()+nQCDp[ipt]->getVal())/hPdfMetp->Integral());
    hMetpDiff = makeDiffHist(hDataMetp[ipt],hPdfMetp,"hMetpDiff");
    hMetpDiff->SetMarkerStyle(kFullCircle);
    hMetpDiff->SetMarkerSize(0.9);
      
    hPdfMetm = (TH1D*)(pdfMetm[ipt]->createHistogram("hPdfMetm", pfmet));
    hPdfMetm->Scale(
	(nSigm[ipt]->getVal()+nEWKm[ipt]->getVal()+nQCDm[ipt]->getVal())/hPdfMetm->Integral());
    hMetmDiff = makeDiffHist(hDataMetm[ipt],hPdfMetm,"hMetmDiff");
    hMetmDiff->SetMarkerStyle(kFullCircle); 
    hMetmDiff->SetMarkerSize(0.9);

    hPdfAntiMet = (TH1D*)(apdfMet[ipt]->createHistogram("hPdfAntiMet", pfmet));
    hPdfAntiMet->Scale(
	(nAntiSig[ipt]->getVal()+nAntiEWK[ipt]->getVal()+nAntiQCD[ipt]->getVal())/hPdfAntiMet->Integral());
    if (ipt<10)
      hAntiMetDiff = makeDiffHist(hAntiDataMet[ipt],hPdfAntiMet,"hAntiMetDiff");
    else
      hAntiMetDiff = makeDiffHist(hHighWpTAnti_DataMet,hPdfAntiMet,"hAntiMetDiff");
    hAntiMetDiff->SetMarkerStyle(kFullCircle);
    hAntiMetDiff->SetMarkerSize(0.9);
     
    hPdfAntiMetp = (TH1D*)(apdfMetp[ipt]->createHistogram("hPdfAntiMetp", pfmet));
    hPdfAntiMetp->Scale(
	(nAntiSigp[ipt]->getVal()+nAntiEWKp[ipt]->getVal()+nAntiQCDp[ipt]->getVal())/hPdfAntiMetp->Integral());
    if (ipt<10)
      hAntiMetpDiff = makeDiffHist(hAntiDataMetp[ipt],hPdfAntiMetp,"hAntiMetpDiff");
    else
      hAntiMetpDiff = makeDiffHist(hHighWpTAnti_DataMetp,hPdfAntiMetp,"hAntiMetpDiff");
    hAntiMetpDiff->SetMarkerStyle(kFullCircle);
    hAntiMetpDiff->SetMarkerSize(0.9);
      
    hPdfAntiMetm = (TH1D*)(apdfMetm[ipt]->createHistogram("hPdfAntiMetm", pfmet));
    hPdfAntiMetm->Scale(
	(nAntiSigm[ipt]->getVal()+nAntiEWKm[ipt]->getVal()+nAntiQCDm[ipt]->getVal())/hPdfAntiMetm->Integral());
    if (ipt<10)
      hAntiMetmDiff = makeDiffHist(hAntiDataMetm[ipt],hPdfAntiMetm,"hAntiMetmDiff");
    else
      hAntiMetmDiff = makeDiffHist(hHighWpTAnti_DataMetm,hPdfAntiMetm,"hAntiMetmDiff");
    hAntiMetmDiff->SetMarkerStyle(kFullCircle); 
    hAntiMetmDiff->SetMarkerSize(0.9);

    //Write MET Histogram to file
    if(ipt == 0)
      if (filetype == "BeforeRC" || filetype == "Nominal")
      {
        char metfname[100];
        sprintf(metfname,"%s/MET_"+filetype+".root",CPlot::sOutDir.Data());
        TFile *metfile = new TFile(metfname,"RECREATE");
        RooAddPdf* pdfWmunu0Met;
        RooAddPdf* pdfWmunu0Metp;
        RooAddPdf* pdfWmunu0Metm;
        RooAddPdf* pdfEWK0Met;
        RooAddPdf* pdfEWK0Metp;
        RooAddPdf* pdfEWK0Metm;
        RooAddPdf* pdfQCD0Met;
        RooAddPdf* pdfQCD0Metp;
        RooAddPdf* pdfQCD0Metm;
        
        TH1D* hWmunu0;
        TH1D* hWmunu0p;
        TH1D* hWmunu0m;
        TH1D* hEWK0;
        TH1D* hEWK0p;
        TH1D* hEWK0m;
        TH1D* hQCD0;
        TH1D* hQCD0p;
        TH1D* hQCD0m;
        
        pdfWmunu0Met  = new RooAddPdf("pdfWmunu0Met", "pdfWmunu0Met"
	   		,RooArgList(*pdfWm[ipt]),RooArgList(*nSig[ipt]));
        pdfWmunu0Metp = new RooAddPdf("pdfWmunu0Metp","pdfWmunu0Metp"
	    		,RooArgList(*pdfWmp[ipt]),RooArgList(*nSigp[ipt]));
        pdfWmunu0Metm = new RooAddPdf("pdfWmunu0Metm","pdfWmunu0Metm"
	   		,RooArgList(*pdfWmm[ipt]),RooArgList(*nSigm[ipt]));
        
        pdfEWK0Met  = new RooAddPdf("pdfEWK0Met", "pdfEWK0Met"
	   		,RooArgList(*pdfEWK[ipt]),RooArgList(*nEWK[ipt]));
        pdfEWK0Metp = new RooAddPdf("pdfEWK0Metp","pdfEWK0Metp"
	   		,RooArgList(*pdfEWKp[ipt]),RooArgList(*nEWKp[ipt]));
        pdfEWK0Metm = new RooAddPdf("pdfEWK0Metm","pdfEWK0Metm"
	   		,RooArgList(*pdfEWKm[ipt]),RooArgList(*nEWKm[ipt]));
        
        pdfQCD0Met  = new RooAddPdf("pdfQCD0Met", "pdfQCD0Met"
	    		,RooArgList(*(qcd[ipt]->model)),RooArgList(*nQCD[ipt]));
        pdfQCD0Metp = new RooAddPdf("pdfQCD0Metp","pdfQCD0Metp"
	   		,RooArgList(*(qcdp[ipt]->model)),RooArgList(*nQCDp[ipt]));
        pdfQCD0Metm = new RooAddPdf("pdfQCD0Metm","pdfQCD0Metm"
	    		,RooArgList(*(qcdm[ipt]->model)),RooArgList(*nQCDm[ipt]));
        
        hWmunu0 = (TH1D*)(pdfWmunu0Met->createHistogram("hWmunu0", pfmet));
        hWmunu0->Scale((nSig[ipt]->getVal())/hWmunu0->Integral());
        hWmunu0p = (TH1D*)(pdfWmunu0Metp->createHistogram("hWmunu0p", pfmet));
        hWmunu0p->Scale((nSigp[ipt]->getVal())/hWmunu0p->Integral());
        hWmunu0m = (TH1D*)(pdfWmunu0Metm->createHistogram("hWmunu0m", pfmet));
        hWmunu0m->Scale((nSigm[ipt]->getVal())/hWmunu0m->Integral());
        
        hEWK0 = (TH1D*)(pdfEWK0Met->createHistogram("hEWK0", pfmet));
        hEWK0->Scale((nEWK[ipt]->getVal())/hEWK0->Integral());
        hEWK0p = (TH1D*)(pdfEWK0Metp->createHistogram("hEWK0p", pfmet));
        hEWK0p->Scale((nEWKp[ipt]->getVal())/hEWK0p->Integral());
        hEWK0m = (TH1D*)(pdfEWK0Metm->createHistogram("hEWK0m", pfmet));
        hEWK0m->Scale((nEWKm[ipt]->getVal())/hEWK0m->Integral());
        
        hQCD0 = (TH1D*)(pdfQCD0Met->createHistogram("hQCD0", pfmet));
        hQCD0->Scale((nQCD[ipt]->getVal())/hQCD0->Integral());
        hQCD0p = (TH1D*)(pdfQCD0Metp->createHistogram("hQCD0p", pfmet));
        hQCD0p->Scale((nQCDp[ipt]->getVal())/hQCD0p->Integral());
        hQCD0m = (TH1D*)(pdfQCD0Metm->createHistogram("hQCD0m", pfmet));
        hQCD0m->Scale((nQCDm[ipt]->getVal())/hQCD0m->Integral());
        
        hDataMet[ipt]->Write();
        hDataMetp[ipt]->Write();
        hDataMetm[ipt]->Write();
        hWmunu0->Write();
        hWmunu0p->Write();
        hWmunu0m->Write();
        hEWK0->Write();
        hEWK0p->Write();
        hEWK0m->Write();
        hQCD0->Write();
        hQCD0p->Write();
        hQCD0m->Write();
        metfile->Close();
      }

    if (ipt==0)
      sprintf(binlabel,"0 < p_{T} < 600");
    else
      sprintf(binlabel,"%.1f < p_{T} < %.1f",WptBins[ipt-1],WptBins[ipt]);

    //-------------------------------------------------
    // Make MET Fit plots 
    //=================================================  
    //
    // W Inclusive Signal region MET plot
    //
    wmframe = pfmet.frame(Bins(NBINS)); 
    wmframe->GetYaxis()->SetNdivisions(505);
    dataMet[ipt]->plotOn(wmframe,MarkerStyle(kFullCircle),MarkerSize(0.9),DrawOption("ZP"));
    pdfMet[ipt]->plotOn(wmframe,FillColor(fillcolorW),DrawOption("F"));
    pdfMet[ipt]->plotOn(wmframe,LineColor(linecolorW));
    if (ipt<4){
      pdfMet[ipt]->plotOn(wmframe
	  ,Components(RooArgSet(*pdfEWK[ipt],*(qcd[ipt]->model)))
	  ,FillColor(fillcolorEWK),DrawOption("F"));
      pdfMet[ipt]->plotOn(wmframe
	  ,Components(RooArgSet(*pdfEWK[ipt],*(qcd[ipt]->model)))
	  ,LineColor(linecolorEWK));
      pdfMet[ipt]->plotOn(wmframe
	  ,Components(RooArgSet(*(qcd[ipt]->model)))
	  ,FillColor(fillcolorQCD),DrawOption("F"));
      pdfMet[ipt]->plotOn(wmframe
	  ,Components(RooArgSet(*(qcd[ipt]->model)))
	  ,LineColor(linecolorQCD));
    }else if (ipt == 4){
      pdfMet[ipt]->plotOn(wmframe
	  ,Components(RooArgSet(*pdfEWK[ipt],*(qcd1[ipt]->model)))
	  ,FillColor(fillcolorEWK),DrawOption("F"));
      pdfMet[ipt]->plotOn(wmframe
	  ,Components(RooArgSet(*pdfEWK[ipt],*(qcd1[ipt]->model)))
	  ,LineColor(linecolorEWK));
      pdfMet[ipt]->plotOn(wmframe
	  ,Components(RooArgSet(*(qcd1[ipt]->model)))
	  ,FillColor(fillcolorQCD),DrawOption("F"));
      pdfMet[ipt]->plotOn(wmframe
	  ,Components(RooArgSet(*(qcd1[ipt]->model)))
	  ,LineColor(linecolorQCD));
    }else if (ipt > 4){
      pdfMet[ipt]->plotOn(wmframe
	  ,Components(RooArgSet(*pdfEWK[ipt],*(qcd2[ipt]->model)))
	  ,FillColor(fillcolorEWK),DrawOption("F"));
      pdfMet[ipt]->plotOn(wmframe
	  ,Components(RooArgSet(*pdfEWK[ipt],*(qcd2[ipt]->model)))
	  ,LineColor(linecolorEWK));
      pdfMet[ipt]->plotOn(wmframe
	  ,Components(RooArgSet(*(qcd2[ipt]->model)))
	  ,FillColor(fillcolorQCD),DrawOption("F"));
      pdfMet[ipt]->plotOn(wmframe
	  ,Components(RooArgSet(*(qcd2[ipt]->model)))
	  ,LineColor(linecolorQCD));
    }
    pdfMet[ipt]->plotOn(wmframe
	,Components(RooArgSet(*pdfWm[ipt])),LineColor(linecolorW),LineStyle(2));
    dataMet[ipt]->plotOn(wmframe,MarkerStyle(kFullCircle),MarkerSize(0.9),DrawOption("ZP"));  
    
    sprintf(ylabel,"Events / %.1f GeV",hDataMet[ipt]->GetBinWidth(1));
    sprintf(histName,"WMuNu_%d",ipt);
    plotMet=new CPlot(histName,wmframe,"","",ylabel);
    plotMet->setOutDir(CPlot::sOutDir);
    plotMet->SetLegend(0.68,0.55,0.93,0.73);
    plotMet->GetLegend()->AddEntry(hDummyData,"data","PL");
    plotMet->GetLegend()->AddEntry(hDummyW,"W#rightarrow e#nu","F");
    plotMet->GetLegend()->AddEntry(hDummyEWK,"EWK+t#bar{t}","F");
    plotMet->GetLegend()->AddEntry(hDummyQCD,"QCD","F");
    plotMet->AddTextBox(lumitext,0.55,0.82,0.90,0.87,0);
    plotMet->AddTextBox(binlabel,0.55,0.75,0.90,0.80,0);
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
    
    sprintf(histName,"WMuNu_%d_log",ipt);
    plotMet->SetName(histName);
    plotMet->SetLogy();
    plotMet->SetYRange(1e-3*(hDataMet[ipt]->GetMaximum()),10*(hDataMet[ipt]->GetMaximum()));
    plotMet->Draw(c,kTRUE,format,1);

    // W Inclusive Control region MET plot
    awmframe = pfmet.frame(Bins(NBINS));
    antiMet[ipt]->plotOn(awmframe,MarkerStyle(kFullCircle),MarkerSize(0.9),DrawOption("ZP"));
    apdfMet[ipt]->plotOn(awmframe,FillColor(fillcolorW),DrawOption("F"));
    apdfMet[ipt]->plotOn(awmframe,LineColor(linecolorW));
    if (ipt<4){
      apdfMet[ipt]->plotOn(awmframe
          ,Components(RooArgSet(*apdfEWK[ipt],*(aqcd[ipt]->model)))
          ,FillColor(fillcolorEWK),DrawOption("F"));
      apdfMet[ipt]->plotOn(awmframe
          ,Components(RooArgSet(*apdfEWK[ipt],*(aqcd[ipt]->model)))
          ,LineColor(linecolorEWK));
      apdfMet[ipt]->plotOn(awmframe
          ,Components(RooArgSet(*(aqcd[ipt]->model)))
          ,FillColor(fillcolorQCD),DrawOption("F"));
      apdfMet[ipt]->plotOn(awmframe
          ,Components(RooArgSet(*(aqcd[ipt]->model)))
          ,LineColor(linecolorQCD));
      }else if (ipt == 4){
	apdfMet[ipt]->plotOn(awmframe
	    ,Components(RooArgSet(*apdfEWK[ipt],*(aqcd1[ipt]->model)))
	    ,FillColor(fillcolorEWK),DrawOption("F"));
	apdfMet[ipt]->plotOn(awmframe
	    ,Components(RooArgSet(*apdfEWK[ipt],*(aqcd1[ipt]->model)))
	    ,LineColor(linecolorEWK));
	apdfMet[ipt]->plotOn(awmframe
	    ,Components(RooArgSet(*(aqcd1[ipt]->model)))
	    ,FillColor(fillcolorQCD),DrawOption("F"));
	apdfMet[ipt]->plotOn(awmframe
	    ,Components(RooArgSet(*(aqcd1[ipt]->model)))
	    ,LineColor(linecolorQCD));
      }else if (ipt > 4){
      apdfMet[ipt]->plotOn(awmframe
          ,Components(RooArgSet(*apdfEWK[ipt],*(aqcd2[ipt]->model)))
          ,FillColor(fillcolorEWK),DrawOption("F"));
      apdfMet[ipt]->plotOn(awmframe
          ,Components(RooArgSet(*apdfEWK[ipt],*(aqcd2[ipt]->model)))
          ,LineColor(linecolorEWK));
      apdfMet[ipt]->plotOn(awmframe
          ,Components(RooArgSet(*(aqcd2[ipt]->model)))
          ,FillColor(fillcolorQCD),DrawOption("F"));
      apdfMet[ipt]->plotOn(awmframe
          ,Components(RooArgSet(*(aqcd2[ipt]->model)))
          ,LineColor(linecolorQCD));
    }
    apdfMet[ipt]->plotOn(awmframe
        ,Components(RooArgSet(*apdfWm[ipt])),LineColor(linecolorW),LineStyle(2));
    antiMet[ipt]->plotOn(awmframe,MarkerStyle(kFullCircle),MarkerSize(0.9),DrawOption("ZP"));
    
    if (ipt<10)
      sprintf(ylabel,"Events / %.1f GeV",hAntiDataMet[ipt]->GetBinWidth(1));
    else
      sprintf(ylabel,"Events / %.1f GeV",hHighWpTAnti_DataMet->GetBinWidth(1));
    sprintf(histName,"WMuNu_cont_%d",ipt);
    plotAntiMet=new CPlot (histName,awmframe,"","",ylabel);
    plotAntiMet->setOutDir(CPlot::sOutDir);
    plotAntiMet->SetLegend(0.68,0.55,0.93,0.73);
    plotAntiMet->GetLegend()->AddEntry(hDummyData,"data","PL");
    plotAntiMet->GetLegend()->AddEntry(hDummyW,"W#rightarrow e#nu","F");
    plotAntiMet->GetLegend()->AddEntry(hDummyEWK,"EWK+t#bar{t}","F");
    plotAntiMet->GetLegend()->AddEntry(hDummyQCD,"QCD","F");
    plotAntiMet->AddTextBox(lumitext,0.55,0.82,0.90,0.87,0);
    plotAntiMet->AddTextBox(binlabel,0.55,0.75,0.90,0.80,0);
    plotAntiMet->AddTextBox("CMS Preliminary",0.63,0.92,0.95,0.99,0);
    if (ipt<10)
      plotAntiMet->SetYRange(0.1,1.1*(hAntiDataMet[ipt]->GetMaximum()));
    else
      plotAntiMet->SetYRange(0.1,1.5*(hHighWpTAnti_DataMet->GetMaximum()));
    plotAntiMet->Draw(c,kFALSE,format,1);
    
    plotAntiMetDiff=new CPlot(histName,"","#slash{E}_{T} [GeV]","#chi");
    plotAntiMetDiff->setOutDir(CPlot::sOutDir);
    plotAntiMetDiff->AddHist1D(hAntiMetDiff,"EX0",ratioColor);
    plotAntiMetDiff->SetYRange(-8,8);
    plotAntiMetDiff->AddLine(0, 0,METMAX, 0,kBlack,1);
    plotAntiMetDiff->AddLine(0, 5,METMAX, 5,kBlack,3);
    plotAntiMetDiff->AddLine(0,-5,METMAX,-5,kBlack,3);
    plotAntiMetDiff->Draw(c,kTRUE,format,2);
    
    sprintf(histName,"WMuNu_cont_%d_log",ipt);
    plotAntiMet->SetName(histName);
    plotAntiMet->SetLogy();
    if (ipt<10)
      plotAntiMet->SetYRange(1e-3*(hAntiDataMet[ipt]->GetMaximum()),10*(hAntiDataMet[ipt]->GetMaximum()));
    else
      plotAntiMet->SetYRange(1e-3*(hHighWpTAnti_DataMet->GetMaximum()),10*(hHighWpTAnti_DataMet->GetMaximum()));
    plotAntiMet->Draw(c,kTRUE,format,1);
    //
    // W+ MET plot Signal region
    //
    wmpframe = pfmet.frame(Bins(NBINS));
    wmpframe->GetYaxis()->SetNdivisions(505);
    dataMetp[ipt]->plotOn(wmpframe,MarkerStyle(kFullCircle),MarkerSize(0.9),DrawOption("ZP"));
    pdfMetp[ipt]->plotOn(wmpframe,FillColor(fillcolorW),DrawOption("F"));
    pdfMetp[ipt]->plotOn(wmpframe,LineColor(linecolorW));
    if (ipt<4){
      pdfMetp[ipt]->plotOn(wmpframe
	  ,Components(RooArgSet(*pdfEWKp[ipt],*(qcdp[ipt]->model)))
	  ,FillColor(fillcolorEWK),DrawOption("F"));
      pdfMetp[ipt]->plotOn(wmpframe
	  ,Components(RooArgSet(*pdfEWKp[ipt],*(qcdp[ipt]->model)))
	  ,LineColor(linecolorEWK));
      pdfMetp[ipt]->plotOn(wmpframe
	  ,Components(RooArgSet(*(qcdp[ipt]->model)))
	  ,FillColor(fillcolorQCD),DrawOption("F"));
      pdfMetp[ipt]->plotOn(wmpframe
	  ,Components(RooArgSet(*(qcdp[ipt]->model)))
	  ,LineColor(linecolorQCD));
    }else if (ipt == 4){
      pdfMetp[ipt]->plotOn(wmpframe
	  ,Components(RooArgSet(*pdfEWKp[ipt],*(qcd1p[ipt]->model)))
	  ,FillColor(fillcolorEWK),DrawOption("F"));
      pdfMetp[ipt]->plotOn(wmpframe
	  ,Components(RooArgSet(*pdfEWKp[ipt],*(qcd1p[ipt]->model)))
	  ,LineColor(linecolorEWK));
      pdfMetp[ipt]->plotOn(wmpframe
	  ,Components(RooArgSet(*(qcd1p[ipt]->model)))
	  ,FillColor(fillcolorQCD),DrawOption("F"));
      pdfMetp[ipt]->plotOn(wmpframe
	  ,Components(RooArgSet(*(qcd1p[ipt]->model)))
	  ,LineColor(linecolorQCD));
    }else if (ipt > 4){
      pdfMetp[ipt]->plotOn(wmpframe
	  ,Components(RooArgSet(*pdfEWKp[ipt],*(qcd2p[ipt]->model)))
	  ,FillColor(fillcolorEWK),DrawOption("F"));
      pdfMetp[ipt]->plotOn(wmpframe
	  ,Components(RooArgSet(*pdfEWKp[ipt],*(qcd2p[ipt]->model)))
	  ,LineColor(linecolorEWK));
      pdfMetp[ipt]->plotOn(wmpframe
	  ,Components(RooArgSet(*(qcd2p[ipt]->model)))
	  ,FillColor(fillcolorQCD),DrawOption("F"));
      pdfMetp[ipt]->plotOn(wmpframe
	  ,Components(RooArgSet(*(qcd2p[ipt]->model)))
	  ,LineColor(linecolorQCD));
    }
    pdfMetp[ipt]->plotOn(wmpframe
	,Components(RooArgSet(*pdfWmp[ipt]))
	,LineColor(linecolorW),LineStyle(2));
    dataMetp[ipt]->plotOn(wmpframe,MarkerStyle(kFullCircle),MarkerSize(0.9),DrawOption("ZP"));  
    
    sprintf(ylabel,"Events / %.1f GeV",hDataMetp[ipt]->GetBinWidth(1));
    sprintf(histName,"WpMuNu_%d",ipt);
    plotMetp=new CPlot (histName,wmpframe,"","",ylabel);
    plotMetp->setOutDir(CPlot::sOutDir);
    plotMetp->SetLegend(0.68,0.55,0.93,0.73);
    plotMetp->GetLegend()->AddEntry(hDummyData,"data","PL");
    plotMetp->GetLegend()->AddEntry(hDummyW,"W^{+}#rightarrow e^{+}#nu","F");
    plotMetp->GetLegend()->AddEntry(hDummyEWK,"EWK+t#bar{t}","F");
    plotMetp->GetLegend()->AddEntry(hDummyQCD,"QCD","F");
    plotMetp->AddTextBox(lumitext,0.55,0.82,0.90,0.87,0);
    plotMetp->AddTextBox(binlabel,0.55,0.75,0.90,0.80,0);
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
    
    sprintf(histName,"WpMuNu_%d_log",ipt);
    plotMetp->SetName(histName);
    plotMetp->SetLogy();
    plotMetp->SetYRange(1e-3*(hDataMetp[ipt]->GetMaximum()),10*(hDataMetp[ipt]->GetMaximum()));
    plotMetp->Draw(c,kTRUE,format,1);

    // W+ MET plot Control region
    awmpframe = pfmet.frame(Bins(NBINS));
    antiMetp[ipt]->plotOn(awmpframe,MarkerStyle(kFullCircle),MarkerSize(0.9),DrawOption("ZP"));
    apdfMetp[ipt]->plotOn(awmpframe,FillColor(fillcolorW),DrawOption("F"));
    apdfMetp[ipt]->plotOn(awmpframe,LineColor(linecolorW));
    if (ipt<4){
      apdfMetp[ipt]->plotOn(awmpframe
          ,Components(RooArgSet(*apdfEWKp[ipt],*(aqcdp[ipt]->model)))
          ,FillColor(fillcolorEWK),DrawOption("F"));
      apdfMetp[ipt]->plotOn(awmpframe
          ,Components(RooArgSet(*apdfEWKp[ipt],*(aqcdp[ipt]->model)))
          ,LineColor(linecolorEWK));
      apdfMetp[ipt]->plotOn(awmpframe
          ,Components(RooArgSet(*(aqcdp[ipt]->model)))
          ,FillColor(fillcolorQCD),DrawOption("F"));
      apdfMetp[ipt]->plotOn(awmpframe
          ,Components(RooArgSet(*(aqcdp[ipt]->model)))
          ,LineColor(linecolorQCD));
      }else if (ipt == 4){
	apdfMetp[ipt]->plotOn(awmpframe
	    ,Components(RooArgSet(*apdfEWKp[ipt],*(aqcd1p[ipt]->model)))
	    ,FillColor(fillcolorEWK),DrawOption("F"));
	apdfMetp[ipt]->plotOn(awmpframe
	    ,Components(RooArgSet(*apdfEWKp[ipt],*(aqcd1p[ipt]->model)))
	    ,LineColor(linecolorEWK));
	apdfMetp[ipt]->plotOn(awmpframe
	    ,Components(RooArgSet(*(aqcd1p[ipt]->model)))
	    ,FillColor(fillcolorQCD),DrawOption("F"));
	apdfMetp[ipt]->plotOn(awmpframe
	    ,Components(RooArgSet(*(aqcd1p[ipt]->model)))
	    ,LineColor(linecolorQCD));
      }else if (ipt > 4){
      apdfMetp[ipt]->plotOn(awmpframe
          ,Components(RooArgSet(*apdfEWKp[ipt],*(aqcd2p[ipt]->model)))
          ,FillColor(fillcolorEWK),DrawOption("F"));
      apdfMetp[ipt]->plotOn(awmpframe
          ,Components(RooArgSet(*apdfEWKp[ipt],*(aqcd2p[ipt]->model)))
          ,LineColor(linecolorEWK));
      apdfMetp[ipt]->plotOn(awmpframe
          ,Components(RooArgSet(*(aqcd2p[ipt]->model)))
          ,FillColor(fillcolorQCD),DrawOption("F"));
      apdfMetp[ipt]->plotOn(awmpframe
          ,Components(RooArgSet(*(aqcd2p[ipt]->model)))
          ,LineColor(linecolorQCD));
    }
    apdfMetp[ipt]->plotOn(awmpframe
        ,Components(RooArgSet(*apdfWmp[ipt]))
        ,LineColor(linecolorW),LineStyle(2));
    antiMetp[ipt]->plotOn(awmpframe,MarkerStyle(kFullCircle),MarkerSize(0.9),DrawOption("ZP"));
    
    if (ipt<10)
      sprintf(ylabel,"Events / %.1f GeV",hAntiDataMetp[ipt]->GetBinWidth(1));
    else
      sprintf(ylabel,"Events / %.1f GeV",hHighWpTAnti_DataMetp->GetBinWidth(1));
    sprintf(histName,"WpMuNu_cont_%d",ipt);
    plotAntiMetp=new CPlot (histName,awmpframe,"","",ylabel);
    plotAntiMetp->setOutDir(CPlot::sOutDir);
    plotAntiMetp->SetLegend(0.68,0.55,0.93,0.73);
    plotAntiMetp->GetLegend()->AddEntry(hDummyData,"data","PL");
    plotAntiMetp->GetLegend()->AddEntry(hDummyW,"W^{+}#rightarrow e^{+}#nu","F");
    plotAntiMetp->GetLegend()->AddEntry(hDummyEWK,"EWK+t#bar{t}","F");
    plotAntiMetp->GetLegend()->AddEntry(hDummyQCD,"QCD","F");
    plotAntiMetp->AddTextBox(lumitext,0.55,0.82,0.90,0.87,0);
    plotAntiMetp->AddTextBox(binlabel,0.55,0.75,0.90,0.80,0);
    plotAntiMetp->AddTextBox("CMS Preliminary",0.63,0.92,0.95,0.99,0);
    if (ipt<10)
      plotAntiMetp->SetYRange(0.1,1.1*(hAntiDataMetp[ipt]->GetMaximum()));
    else
      plotAntiMetp->SetYRange(0.1,1.5*(hHighWpTAnti_DataMetp->GetMaximum()));
    plotAntiMetp->Draw(c,kFALSE,format,1);
    
    plotAntiMetpDiff=new CPlot(histName,"","#slash{E}_{T} [GeV]","#chi");
    plotAntiMetpDiff->setOutDir(CPlot::sOutDir);
    plotAntiMetpDiff->AddHist1D(hAntiMetpDiff,"EX0",ratioColor);
    plotAntiMetpDiff->SetYRange(-8,8);
    plotAntiMetpDiff->AddLine(0, 0,METMAX, 0,kBlack,1);
    plotAntiMetpDiff->AddLine(0, 5,METMAX, 5,kBlack,3);
    plotAntiMetpDiff->AddLine(0,-5,METMAX,-5,kBlack,3);
    plotAntiMetpDiff->Draw(c,kTRUE,format,2);
    
    sprintf(histName,"WpMuNu_cont_%d_log",ipt);
    plotAntiMetp->SetName(histName);
    plotAntiMetp->SetLogy();
    if (ipt<10)
      plotAntiMetp->SetYRange(1e-3*(hAntiDataMetp[ipt]->GetMaximum()),10*(hAntiDataMetp[ipt]->GetMaximum()));
    else
      plotAntiMetp->SetYRange(1e-3*(hHighWpTAnti_DataMetp->GetMaximum()),10*(hHighWpTAnti_DataMetp->GetMaximum()));
    plotAntiMetp->Draw(c,kTRUE,format,1);
    //
    // W- MET plot Signal region
    //

    wmmframe = pfmet.frame(Bins(NBINS));
    wmmframe->GetYaxis()->SetNdivisions(505);
    dataMetm[ipt]->plotOn(wmmframe,MarkerStyle(kFullCircle),MarkerSize(0.9),DrawOption("ZP"));
    pdfMetm[ipt]->plotOn(wmmframe,FillColor(fillcolorW),DrawOption("F"));
    pdfMetm[ipt]->plotOn(wmmframe,LineColor(linecolorW));
    if (ipt<4){
      pdfMetm[ipt]->plotOn(wmmframe
	  ,Components(RooArgSet(*pdfEWKm[ipt],*(qcdm[ipt]->model)))
	  ,FillColor(fillcolorEWK),DrawOption("F"));
      pdfMetm[ipt]->plotOn(wmmframe
	  ,Components(RooArgSet(*pdfEWKm[ipt],*(qcdm[ipt]->model)))
	  ,LineColor(linecolorEWK));
      pdfMetm[ipt]->plotOn(wmmframe
	  ,Components(RooArgSet(*(qcdm[ipt]->model)))
	  ,FillColor(fillcolorQCD),DrawOption("F"));
      pdfMetm[ipt]->plotOn(wmmframe
	  ,Components(RooArgSet(*(qcdm[ipt]->model)))
	  ,LineColor(linecolorQCD));
    }else if (ipt == 4){
      pdfMetm[ipt]->plotOn(wmmframe
	  ,Components(RooArgSet(*pdfEWKm[ipt],*(qcd1m[ipt]->model)))
	  ,FillColor(fillcolorEWK),DrawOption("F"));
      pdfMetm[ipt]->plotOn(wmmframe
	  ,Components(RooArgSet(*pdfEWKm[ipt],*(qcd1m[ipt]->model)))
	  ,LineColor(linecolorEWK));
      pdfMetm[ipt]->plotOn(wmmframe
	  ,Components(RooArgSet(*(qcd1m[ipt]->model)))
	  ,FillColor(fillcolorQCD),DrawOption("F"));
      pdfMetm[ipt]->plotOn(wmmframe
	  ,Components(RooArgSet(*(qcd1m[ipt]->model)))
	  ,LineColor(linecolorQCD));
    }else if (ipt > 4){
      pdfMetm[ipt]->plotOn(wmmframe
	  ,Components(RooArgSet(*pdfEWKm[ipt],*(qcd2m[ipt]->model)))
	  ,FillColor(fillcolorEWK),DrawOption("F"));
      pdfMetm[ipt]->plotOn(wmmframe
	  ,Components(RooArgSet(*pdfEWKm[ipt],*(qcd2m[ipt]->model)))
	  ,LineColor(linecolorEWK));
      pdfMetm[ipt]->plotOn(wmmframe
	  ,Components(RooArgSet(*(qcd2m[ipt]->model)))
	  ,FillColor(fillcolorQCD),DrawOption("F"));
      pdfMetm[ipt]->plotOn(wmmframe
	  ,Components(RooArgSet(*(qcd2m[ipt]->model)))
	  ,LineColor(linecolorQCD));
    }
    pdfMetm[ipt]->plotOn(wmmframe
	,Components(RooArgSet(*pdfWmm[ipt]))
	,LineColor(linecolorW),LineStyle(2));
    dataMetm[ipt]->plotOn(wmmframe,MarkerStyle(kFullCircle),MarkerSize(0.9),DrawOption("ZP"));
    
    sprintf(ylabel,"Events / %.1f GeV",hDataMetm[ipt]->GetBinWidth(1));
    sprintf(histName,"WmMuNu_%d",ipt);
    plotMetm=new CPlot(histName,wmmframe,"","",ylabel);
    plotMetm->setOutDir(CPlot::sOutDir);
    plotMetm->SetLegend(0.68,0.55,0.93,0.73);
    plotMetm->GetLegend()->AddEntry(hDummyData,"data","PL");
    plotMetm->GetLegend()->AddEntry(hDummyW,"W^{-}#rightarrow e^{-}#bar{#nu}","F");
    plotMetm->GetLegend()->AddEntry(hDummyEWK,"EWK+t#bar{t}","F");
    plotMetm->GetLegend()->AddEntry(hDummyQCD,"QCD","F");
    plotMetm->AddTextBox(lumitext,0.55,0.82,0.90,0.87,0);
    plotMetm->AddTextBox(binlabel,0.55,0.75,0.90,0.80,0);
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
    
    sprintf(histName,"WmMuNu_%d_log",ipt);
    plotMetm->SetName(histName);
    plotMetm->SetLogy();
    plotMetm->SetYRange(1e-3*(hDataMetm[ipt]->GetMaximum()),10*(hDataMetm[ipt]->GetMaximum()));
    plotMetm->Draw(c,kTRUE,format,1);

    // W- MET plot Control region
    awmmframe = pfmet.frame(Bins(NBINS));
    antiMetm[ipt]->plotOn(awmmframe,MarkerStyle(kFullCircle),MarkerSize(0.9),DrawOption("ZP"));
    apdfMetm[ipt]->plotOn(awmmframe,FillColor(fillcolorW),DrawOption("F"));
    apdfMetm[ipt]->plotOn(awmmframe,LineColor(linecolorW));
    if (ipt<4){
      apdfMetm[ipt]->plotOn(awmmframe
          ,Components(RooArgSet(*apdfEWKm[ipt],*(aqcdm[ipt]->model)))
          ,FillColor(fillcolorEWK),DrawOption("F"));
      apdfMetm[ipt]->plotOn(awmmframe
          ,Components(RooArgSet(*apdfEWKm[ipt],*(aqcdm[ipt]->model)))
          ,LineColor(linecolorEWK));
      apdfMetm[ipt]->plotOn(awmmframe
          ,Components(RooArgSet(*(aqcdm[ipt]->model)))
          ,FillColor(fillcolorQCD),DrawOption("F"));
      apdfMetm[ipt]->plotOn(awmmframe
          ,Components(RooArgSet(*(aqcdm[ipt]->model)))
          ,LineColor(linecolorQCD));
    }else if ( ipt == 4){
      apdfMetm[ipt]->plotOn(awmmframe
	  ,Components(RooArgSet(*apdfEWKm[ipt],*(aqcd1m[ipt]->model)))
	  ,FillColor(fillcolorEWK),DrawOption("F"));
      apdfMetm[ipt]->plotOn(awmmframe
	  ,Components(RooArgSet(*apdfEWKm[ipt],*(aqcd1m[ipt]->model)))
	  ,LineColor(linecolorEWK));
      apdfMetm[ipt]->plotOn(awmmframe
	  ,Components(RooArgSet(*(aqcd1m[ipt]->model)))
	  ,FillColor(fillcolorQCD),DrawOption("F"));
      apdfMetm[ipt]->plotOn(awmmframe
	  ,Components(RooArgSet(*(aqcd1m[ipt]->model)))
	  ,LineColor(linecolorQCD));
    }else if (ipt > 4){
      apdfMetm[ipt]->plotOn(awmmframe
          ,Components(RooArgSet(*apdfEWKm[ipt],*(aqcd2m[ipt]->model)))
          ,FillColor(fillcolorEWK),DrawOption("F"));
      apdfMetm[ipt]->plotOn(awmmframe
          ,Components(RooArgSet(*apdfEWKm[ipt],*(aqcd2m[ipt]->model)))
          ,LineColor(linecolorEWK));
      apdfMetm[ipt]->plotOn(awmmframe
          ,Components(RooArgSet(*(aqcd2m[ipt]->model)))
          ,FillColor(fillcolorQCD),DrawOption("F"));
      apdfMetm[ipt]->plotOn(awmmframe
          ,Components(RooArgSet(*(aqcd2m[ipt]->model)))
          ,LineColor(linecolorQCD));
    }
    apdfMetm[ipt]->plotOn(awmmframe
        ,Components(RooArgSet(*apdfWmm[ipt]))
        ,LineColor(linecolorW),LineStyle(2));
    antiMetm[ipt]->plotOn(awmmframe
        ,MarkerStyle(kFullCircle),MarkerSize(0.9),DrawOption("ZP"));
    
    if (ipt<10)
      sprintf(ylabel,"Events / %.1f GeV",hAntiDataMetm[ipt]->GetBinWidth(1));
    else
      sprintf(ylabel,"Events / %.1f GeV",hHighWpTAnti_DataMetm->GetBinWidth(1));
    sprintf(histName,"WmMuNu_cont_%d",ipt);
    plotAntiMetm=new CPlot(histName,awmmframe,"","",ylabel);
    plotAntiMetm->setOutDir(CPlot::sOutDir);
    plotAntiMetm->SetLegend(0.68,0.55,0.93,0.73);
    plotAntiMetm->GetLegend()->AddEntry(hDummyData,"data","PL");
    plotAntiMetm->GetLegend()->AddEntry(hDummyW,"W^{-}#rightarrow e^{-}#bar{#nu}","F");
    plotAntiMetm->GetLegend()->AddEntry(hDummyEWK,"EWK+t#bar{t}","F");
    plotAntiMetm->GetLegend()->AddEntry(hDummyQCD,"QCD","F");
    plotAntiMetm->AddTextBox(lumitext,0.55,0.82,0.90,0.87,0);
    plotAntiMetm->AddTextBox(binlabel,0.55,0.75,0.90,0.80,0);
    plotAntiMetm->AddTextBox("CMS Preliminary",0.63,0.92,0.95,0.99,0);
    if (ipt<10)
      plotAntiMetm->SetYRange(0.1,1.1*(hAntiDataMetm[ipt]->GetMaximum()));
    else
      plotAntiMetm->SetYRange(0.1,1.5*(hHighWpTAnti_DataMetm->GetMaximum()));
    plotAntiMetm->Draw(c,kFALSE,format,1);
    
    plotAntiMetmDiff=new CPlot(histName,"","#slash{E}_{T} [GeV]","#chi");
    plotAntiMetmDiff->setOutDir(CPlot::sOutDir);
    plotAntiMetmDiff->AddHist1D(hAntiMetmDiff,"EX0",ratioColor);
    plotAntiMetmDiff->SetYRange(-8,8);
    plotAntiMetmDiff->AddLine(0, 0,METMAX, 0,kBlack,1);
    plotAntiMetmDiff->AddLine(0, 5,METMAX, 5,kBlack,3);
    plotAntiMetmDiff->AddLine(0,-5,METMAX,-5,kBlack,3);
    plotAntiMetmDiff->Draw(c,kTRUE,format,2);
    
    sprintf(histName,"WmMuNu_cont_%d_log",ipt);
    plotAntiMetm->SetName(histName);
    plotAntiMetm->SetLogy();
    if (ipt<10)
      plotAntiMetm->SetYRange(1e-3*(hAntiDataMetm[ipt]->GetMaximum()),10*(hAntiDataMetm[ipt]->GetMaximum()));
    else
      plotAntiMetm->SetYRange(1e-3*(hHighWpTAnti_DataMetm->GetMaximum()),10*(hHighWpTAnti_DataMetm->GetMaximum()));
    plotAntiMetm->Draw(c,kTRUE,format,1);
    
    
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
    allyields<<fixed<<setprecision(1);
    allyields<<"Bin\t"<<ipt<<"\t Signal\t"<<nSig[ipt]->getVal()<<"\t Error\t"<<nSig[ipt]->getPropagatedError(*fitRes[ipt])<<endl;
    allyields.flags(flags);

    flags = allyieldsp.flags();
    allyieldsp<<fixed<<setprecision(1);
    allyieldsp<<"Bin\t"<<ipt<<"\t Signal\t"<<nSigp[ipt]->getVal()<<"\t Error\t"<<nSigp[ipt]->getPropagatedError(*fitResp[ipt])<<endl;
    allyieldsp.flags(flags);

    flags = allyieldsm.flags();
    allyieldsm<<fixed<<setprecision(1);
    allyieldsm<<"Bin\t"<<ipt<<"\t Signal\t"<<nSigm[ipt]->getVal()<<"\t Error\t"<<nSigm[ipt]->getPropagatedError(*fitResm[ipt])<<endl;
    allyieldsm.flags(flags);

    chi2prob = hDataMet[ipt]->Chi2Test(hPdfMet,"PUW");
    chi2ndf  = hDataMet[ipt]->Chi2Test(hPdfMet,"CHI2/NDFUW");
    ksprob   = hDataMet[ipt]->KolmogorovTest(hPdfMet);
    ksprobpe = hDataMet[ipt]->KolmogorovTest(hPdfMet,"DX");

    flags = Wmfile.flags();
    if (ipt==0)
      Wmfile<<"==================================== [0, 600] Bin - "<<ipt<<" ================================"<<endl;
    else
      Wmfile<<"==================================== ["<<WptBins[ipt-1]<<", "<<WptBins[ipt]<<"] Bin - "<<ipt<<" =============================================="<<endl;
    Wmfile<<endl;
    Wmfile<<fixed<<setprecision(4);
    Wmfile<<"Selected: "<<hDataMet[ipt]->Integral()<<endl;
    Wmfile<<"  Signal: "<<nSig[ipt]->getVal()<<" +/- "<<nSig[ipt]->getPropagatedError(*fitRes[ipt])<<endl;
    Wmfile<<"     QCD: "<<nQCD[ipt]->getVal()<<" +/- "<<nQCD[ipt]->getPropagatedError(*fitRes[ipt])<<endl;
    Wmfile<<"   Other: "<<nEWK[ipt]->getVal()<<" +/- "<<nEWK[ipt]->getPropagatedError(*fitRes[ipt])<<endl;
    Wmfile<<"   Total: "<<nSig[ipt]->getVal()+nQCD[ipt]->getVal()+nEWK[ipt]->getVal()<<endl;
    Wmfile<<endl;
    Wmfile.flags(flags);
    
    fitRes[ipt]->printStream(Wmfile,RooPrintable::kValue,RooPrintable::kVerbose);
    Wmfile<<endl;
    printCorrelations(Wmfile, fitRes[ipt]);
    Wmfile<<endl;
    printChi2AndKSResults(Wmfile, chi2prob, chi2ndf, ksprob, ksprobpe);
    
    chi2prob = hDataMetp[ipt]->Chi2Test(hPdfMetp,"PUW");
    chi2ndf  = hDataMetp[ipt]->Chi2Test(hPdfMetp,"CHI2/NDFUW");
    ksprob   = hDataMetp[ipt]->KolmogorovTest(hPdfMetp);
    ksprobpe = hDataMetp[ipt]->KolmogorovTest(hPdfMetp,"DX");  
    
    flags = Wmpfile.flags();
    if (ipt==0)
      Wmpfile<<"================================= [0, 600] Bin - "<<ipt<<" =================================="<<endl;
    else
      Wmpfile<<"================================= ["<<WptBins[ipt-1]<<", "<<WptBins[ipt]<<"] Bin - "<<ipt<<" =============================================="<<endl;
    Wmpfile<<fixed<<setprecision(4);
    Wmpfile<<endl;
    Wmpfile<<"Selected: "<<hDataMetp[ipt]->Integral()<<endl;
    Wmpfile<<"  Signal: "<<nSigp[ipt]->getVal()<<" +/- "<<nSigp[ipt]->getPropagatedError(*fitResp[ipt])<<endl;
    Wmpfile<<"     QCD: "<<nQCDp[ipt]->getVal()<<" +/- "<<nQCDp[ipt]->getPropagatedError(*fitResp[ipt])<<endl;
    Wmpfile<<"   Other: "<<nEWKp[ipt]->getVal()<<" +/- "<<nEWKp[ipt]->getPropagatedError(*fitResp[ipt])<<endl;
    Wmpfile<<"   Total: "<<nSigp[ipt]->getVal()+nQCDp[ipt]->getVal()+nEWKp[ipt]->getVal()<<endl;
    Wmpfile<<endl; 
    Wmpfile.flags(flags);
    
    fitResp[ipt]->printStream(Wmpfile,RooPrintable::kValue,RooPrintable::kVerbose);
    Wmpfile<<endl;
    printCorrelations(Wmpfile, fitResp[ipt]);
    Wmpfile<<endl;
    printChi2AndKSResults(Wmpfile, chi2prob, chi2ndf, ksprob, ksprobpe);

    chi2prob = hDataMetm[ipt]->Chi2Test(hPdfMetm,"PUW");
    chi2ndf  = hDataMetm[ipt]->Chi2Test(hPdfMetm,"CHI2/NDFUW");
    ksprob   = hDataMetm[ipt]->KolmogorovTest(hPdfMetm);
    ksprobpe = hDataMetm[ipt]->KolmogorovTest(hPdfMetm,"DX");  

    flags = Wmmfile.flags();
    if (ipt==0)
      Wmmfile<<"================================= [0, 600] Bin - "<<ipt<<" =================================="<<endl;
    else
      Wmmfile<<"================================= ["<<WptBins[ipt-1]<<", "<<WptBins[ipt]<<"] Bin - "<<ipt<<" ========================"<<endl;
    Wmmfile<<endl;
    Wmmfile<<fixed<<setprecision(4);
    Wmmfile<<"Selected: "<<hDataMetm[ipt]->Integral()<<endl;
    Wmmfile<<"  Signal: "<<nSigm[ipt]->getVal()<<" +/- "<<nSigm[ipt]->getPropagatedError(*fitResm[ipt])<<endl;
    Wmmfile<<"     QCD: "<<nQCDm[ipt]->getVal()<<" +/- "<<nQCDm[ipt]->getPropagatedError(*fitResm[ipt])<<endl;
    Wmmfile<<"   Other: "<<nEWKm[ipt]->getVal()<<" +/- "<<nEWKm[ipt]->getPropagatedError(*fitResm[ipt])<<endl;
    Wmmfile<<"   Total: "<<nSigm[ipt]->getVal()+nQCDm[ipt]->getVal()+nEWKm[ipt]->getVal()<<endl;
    Wmmfile<<endl;
    Wmmfile.flags(flags);
    
    fitResm[ipt]->printStream(Wmmfile,RooPrintable::kValue,RooPrintable::kVerbose);
    Wmmfile<<endl;
    printCorrelations(Wmmfile, fitResm[ipt]);
    Wmmfile<<endl;
    printChi2AndKSResults(Wmmfile, chi2prob, chi2ndf, ksprob, ksprobpe);

    flags = qcdfile.flags();
    qcdfile<<"======================================================================================"<<endl;
    qcdfile<<"*** Bin "<<ipt<<"***"<<endl;
    qcdfile<<"======================================================================================"<<endl;
    qcdfile<<"Signal region: Normalization factors"<<endl;
    qcdfile<<"Sig="<<nSig[ipt]->getValV()<<"\t SigP="<<nSigp[ipt]->getValV()<<"\t SigM="<<nSigm[ipt]->getValV()<<"\t QCD="<<nQCD[ipt] ->getValV()<<"\t QCDP="<<nQCDp[ipt] ->getValV()<<"\t QCDM="<<nQCDm[ipt] ->getValV()<<endl;
    qcdfile<<"cewk="<<cewk[ipt]->getVal()<<"\t cewkp="<<cewkp[ipt]->getVal()<<"\t cewkm="<<cewkm[ipt]->getVal()<<endl;
    qcdfile<<"Control region: Normalization factors"<<endl;
    qcdfile <<"AntiSig="<<nAntiSig[ipt]->getValV()<<"\t AntiSigP="<<nAntiSigp[ipt]->getValV()<<"\t AntiSigM="<<nAntiSigm[ipt]->getValV()<<"\t AntiQCD="<<nAntiQCD[ipt] ->getValV()<<"\t AntiQCDP="<<nAntiQCDp[ipt] ->getValV()<<"\t AntiQCDM="<<nAntiQCDm[ipt] ->getValV()<<endl;
    qcdfile<<"dewk="<<dewk[ipt]->getVal()
     <<"\t dewkp="<<dewkp[ipt]->getVal()<<"\t dewkm="
     <<dewkm[ipt]->getVal()<<endl;

    if (ipt<4){
      qcdfile<<"Signal region: Mod. Rayleigh func. parameters"<<endl;
      qcdfile<<"Mean=" <<qcd[ipt]->mean->getValV()<<" +/- "<<qcd[ipt]->mean->getError()<<"\t Sigma=" <<qcd[ipt] ->sigma->getValV()<<" +/- "<<qcd[ipt]->sigma->getError()<<"\t Sigma1=" <<qcd[ipt]->a1->getValV()<<" +/- "<<qcd[ipt]->a1->getError()<<endl;
      qcdfile<<"MeanP="<<qcdp[ipt]->mean->getValV()<<" +/- "<<qcdp[ipt]->mean->getError()<<"\t SigmaP="<<qcdp[ipt]->sigma->getValV()<<" +/- "<<qcdp[ipt]->sigma->getError()<<"\t Sigma1P="<<qcdp[ipt]->a1->getValV()<<" +/- "<<qcdp[ipt]->a1->getError()<<endl;
      qcdfile<<"MeanM="<<qcdm[ipt]->mean->getValV()<<" +/- "<<qcdm[ipt]->mean->getError()<<"\t SigmaM="<<qcdm[ipt]->sigma->getValV()<<" +/- "<<qcdm[ipt]->sigma->getError()<<"\t Sigma1M="<<qcdm[ipt]->a1->getValV()<<" +/- "<<qcdm[ipt]->a1->getError()<<endl;
    }else if (ipt == 4){
      qcdfile<<"Signal region: Rayleigh+Gauss func. parameters"<<endl;
      qcdfile<<"qcdmean=" <<qcd1[ipt]->m1->getValV()<<" +/- "<<qcd1[ipt]->m1->getError()<<"\t qcdPmean="<<qcd1p[ipt]->m1->getValV()<<" +/- "<<qcd1p[ipt]->m1->getError()<<"\t qcdMmean="<<qcd1m[ipt]->m1->getValV()<<" +/- "<<qcd1m[ipt]->m1->getError()<<endl;
      qcdfile<<"qcdsigma1="<<qcd1[ipt]->s1->getValV()<<" +/- "<<qcd1[ipt]->s1->getError()<<"\t qcdPsigma1="<<qcd1p[ipt]->s1->getValV()<<" +/- "<<qcd1p[ipt]->s1->getError()<<"\t qcdMsigma1="<<qcd1m[ipt]->s1->getValV()<<" +/- "<<qcd1m[ipt]->s1->getError()<<endl;
      qcdfile<<"qcda1="<<qcd1[ipt]->a1->getValV()<<" +/- "<<qcd1[ipt]->a1->getError()<<"\t qcdPa1="<<qcd1p[ipt]->a1->getValV()<<" +/- "<<qcd1p[ipt]->a1->getError()<<"\t qcdMa1="<<qcd1m[ipt]->a1->getValV()<<" +/- "<<qcd1m[ipt]->a1->getError()<<endl;
      qcdfile<<"qcdsigma2="<<qcd1[ipt]->s2->getValV()<<" +/- "<<qcd1[ipt]->s2->getError()<<"\t qcdPsigma2="<<qcd1p[ipt]->s2->getValV()<<" +/- "<<qcd1p[ipt]->s2->getError()<<"\t qcdMsigma2="<<qcd1m[ipt]->s2->getValV()<<" +/- "<<qcd1m[ipt]->s2->getError()<<endl;
      qcdfile<<"qcda2="<<qcd1[ipt]->a2->getValV()<<" +/- "<<qcd1[ipt]->a2->getError()<<"\t qcdPa2="<<qcd1p[ipt]->a2->getValV()<<" +/- "<<qcd1p[ipt]->a2->getError()<<"\t qcdMa2="<<qcd1m[ipt]->a2->getValV()<<" +/- "<<qcd1m[ipt]->a2->getError()<<endl;
      qcdfile<<"Frac1="<<qcd1[ipt]->f1->getValV()<<" +/- "<<qcd1[ipt]->f1->getError()<<"\t\t\t Frac1P="   <<qcd1p[ipt]->f1->getValV()<<" +/- "<<qcd1p[ipt]->f1->getError()<<"\t\t\t Frac1M="<<qcd1m[ipt]->f1->getValV()<<" +/- "<<qcd1m[ipt]->f1->getError()<<endl;
      qcdfile<<"Frac2="<<qcd1[ipt]->f2->getValV()<<" +/- "<<qcd1[ipt]->f2->getError()<<"\t\t\t Frac2P="   <<qcd1p[ipt]->f2->getValV()<<" +/- "<<qcd1p[ipt]->f2->getError()<<"\t\t\t Frac2M="<<qcd1m[ipt]->f2->getValV()<<" +/- "<<qcd1m[ipt]->f2->getError()<<endl;
    }else if (ipt > 4){
      qcdfile<<"Signal region: Double Rayleigh func. parameters"<<endl;
      qcdfile<<"qcdsigma1="<<qcd2[ipt]->sigma1->getValV()<<" +/- "<<qcd2[ipt]->sigma1->getError()<<"\t qcdPsigma1="<<qcd2p[ipt]->sigma1->getValV()<<" +/- "<<qcd2p[ipt]->sigma1->getError()<<"\t qcdMsigma1="<<qcd2m[ipt]->sigma1->getValV()<<" +/- "<<qcd2m[ipt]->sigma1->getError()<<endl;
      qcdfile<<"qcda1="        <<qcd2[ipt]->a1->getValV()<<" +/- "<<qcd2[ipt]->a1->getError()<<"\t qcdPa1="        <<qcd2p[ipt]->a1->getValV()<<" +/- "<<qcd2p[ipt]->a1->getError()<<"\t qcdMa1="        <<qcd2m[ipt]->a1->getValV()<<" +/- "<<qcd2m[ipt]->a1->getError()<<endl;
      qcdfile<<"qcdsigma2="<<qcd2[ipt]->sigma2->getValV()<<" +/- "<<qcd2[ipt]->sigma2->getError()<<"\t qcdPsigma2="<<qcd2p[ipt]->sigma2->getValV()<<" +/- "<<qcd2p[ipt]->sigma2->getError()<<"\t qcdMsigma2="<<qcd2m[ipt]->sigma2->getValV()<<" +/- "<<qcd2m[ipt]->sigma2->getError()<<endl;
      qcdfile<<"qcda2="        <<qcd2[ipt]->a2->getValV()<<" +/- "<<qcd2[ipt]->a2->getError()<<"\t qcdPa2="        <<qcd2p[ipt]->a2->getValV()<<" +/- "<<qcd2p[ipt]->a2->getError()<<"\t qcdMa2="        <<qcd2m[ipt]->a2->getValV()<<" +/- "<<qcd2m[ipt]->a2->getError()<<endl;
      qcdfile<<"Frac1="     <<qcd2[ipt]->frac1->getValV()<<" +/- "<<qcd2[ipt]->frac1->getError()<<"\t\t\t Frac1P=" <<qcd2p[ipt]->frac1->getValV()<<" +/- "<<qcd2p[ipt]->frac1->getError()<<"\t\t\t Frac1M=" <<qcd2m[ipt]->frac1->getValV()<<" +/- "<<qcd2m[ipt]->frac1->getError()<<endl;
      qcdfile<<"Frac2="     <<qcd2[ipt]->frac2->getValV()<<" +/- "<<qcd2[ipt]->frac2->getError()<<"\t\t\t Frac1P=" <<qcd2p[ipt]->frac2->getValV()<<" +/- "<<qcd2p[ipt]->frac2->getError()<<"\t\t\t Frac1M=" <<qcd2m[ipt]->frac2->getValV()<<" +/- "<<qcd2m[ipt]->frac2->getError()<<endl;
    }
    qcdfile<<endl;
    qcdfile.flags(flags);

    flags = InValfile.flags();
    InValfile<<"}else if (ipt == "<<ipt<<"){"<<endl;
    InValfile<<"nSig[ipt] -> setVal("<<nSig[ipt] ->getValV()<<");"<<endl;
    InValfile<<"nSigp[ipt]-> setVal("<<nSigp[ipt]->getValV()<<");"<<endl;
    InValfile<<"nSigm[ipt]-> setVal("<<nSigm[ipt]->getValV()<<");"<<endl;
    InValfile<<"nAntiSig[ipt] -> setVal("<<nAntiSig[ipt] ->getValV()<<");"<<endl;
    InValfile<<"nAntiSigp[ipt]-> setVal("<<nAntiSigp[ipt]->getValV()<<");"<<endl;
    InValfile<<"nAntiSigm[ipt]-> setVal("<<nAntiSigm[ipt]->getValV()<<");"<<endl;
    InValfile<<"nQCD[ipt] -> setVal("<<nQCD[ipt] ->getValV()<<");"<<endl;
    InValfile<<"nQCDp[ipt]-> setVal("<<nQCDp[ipt]->getValV()<<");"<<endl;
    InValfile<<"nQCDm[ipt]-> setVal("<<nQCDm[ipt]->getValV()<<");"<<endl;
    InValfile<<"nAntiQCD[ipt] -> setVal("<<nAntiQCD[ipt] ->getValV()<<");"<<endl;
    InValfile<<"nAntiQCDp[ipt]-> setVal("<<nAntiQCDp[ipt]->getValV()<<");"<<endl;
    InValfile<<"nAntiQCDm[ipt]-> setVal("<<nAntiQCDm[ipt]->getValV()<<");"<<endl;
    if (ipt<4){
      InValfile<<"qcdmean[ipt] ->setVal("<<qcd[ipt] ->mean->getValV()<<");"<<endl;
      InValfile<<"qcdPmean[ipt]->setVal("<<qcdp[ipt]->mean->getValV()<<");"<<endl;
      InValfile<<"qcdMmean[ipt]->setVal("<<qcdm[ipt]->mean->getValV()<<");"<<endl;
      InValfile<<"qcdsigma1[ipt] ->setVal("<<qcd[ipt] ->sigma->getValV()<<");"<<endl;
      InValfile<<"qcdPsigma1[ipt]->setVal("<<qcdp[ipt]->sigma->getValV()<<");"<<endl;
      InValfile<<"qcdMsigma1[ipt]->setVal("<<qcdm[ipt]->sigma->getValV()<<");"<<endl;
      InValfile<<"qcda1[ipt] ->setVal("<<qcd[ipt] ->a1->getValV()<<");"<<endl;
      InValfile<<"qcdPa1[ipt]->setVal("<<qcdp[ipt]->a1->getValV()<<");"<<endl;
      InValfile<<"qcdMa1[ipt]->setVal("<<qcdm[ipt]->a1->getValV()<<");"<<endl;
      InValfile<<"aqcdsigma1[ipt] ->setVal("<<aqcd[ipt] ->sigma->getValV()<<");"<<endl;
      InValfile<<"aqcdPsigma1[ipt]->setVal("<<aqcdp[ipt]->sigma->getValV()<<");"<<endl;
      InValfile<<"aqcdMsigma1[ipt]->setVal("<<aqcdm[ipt]->sigma->getValV()<<");"<<endl;
    }else if (ipt == 4){
      InValfile<<"qcdmean[ipt] ->setVal("<<qcd1[ipt] ->m1->getValV()<<");"<<endl;
      InValfile<<"qcdPmean[ipt]->setVal("<<qcd1p[ipt]->m1->getValV()<<");"<<endl;
      InValfile<<"qcdMmean[ipt]->setVal("<<qcd1m[ipt]->m1->getValV()<<");"<<endl;
      InValfile<<"qcdsigma1[ipt] ->setVal("<<qcd1[ipt] ->s1->getValV()<<");"<<endl;
      InValfile<<"qcdPsigma1[ipt]->setVal("<<qcd1p[ipt]->s1->getValV()<<");"<<endl;
      InValfile<<"qcdMsigma1[ipt]->setVal("<<qcd1m[ipt]->s1->getValV()<<");"<<endl;
      InValfile<<"qcda1[ipt] ->setVal("<<qcd1[ipt] ->a1->getValV()<<");"<<endl;
      InValfile<<"qcdPa1[ipt]->setVal("<<qcd1p[ipt]->a1->getValV()<<");"<<endl;
      InValfile<<"qcdMa1[ipt]->setVal("<<qcd1m[ipt]->a1->getValV()<<");"<<endl;
      InValfile<<"qcdsigma2[ipt] ->setVal("<<qcd1[ipt] ->s2->getValV()<<");"<<endl;
      InValfile<<"qcdPsigma2[ipt]->setVal("<<qcd1p[ipt]->s2->getValV()<<");"<<endl;
      InValfile<<"qcdMsigma2[ipt]->setVal("<<qcd1m[ipt]->s2->getValV()<<");"<<endl;
      InValfile<<"qcda2[ipt] ->setVal("<<qcd1[ipt] ->a2->getValV()<<");"<<endl;
      InValfile<<"qcdPa2[ipt]->setVal("<<qcd1p[ipt]->a2->getValV()<<");"<<endl;
      InValfile<<"qcdMa2[ipt]->setVal("<<qcd1m[ipt]->a2->getValV()<<");"<<endl;
      InValfile<<"Frac1[ipt] ->setVal("<<qcd1[ipt] ->f1->getValV()<<");"<<endl;
      InValfile<<"Frac1P[ipt]->setVal("<<qcd1p[ipt]->f1->getValV()<<");"<<endl;
      InValfile<<"Frac1M[ipt]->setVal("<<qcd1m[ipt]->f1->getValV()<<");"<<endl;
      InValfile<<"Frac2[ipt] ->setVal("<<qcd1[ipt] ->f2->getValV()<<");"<<endl;
      InValfile<<"Frac2P[ipt]->setVal("<<qcd1p[ipt]->f2->getValV()<<");"<<endl;
      InValfile<<"Frac2M[ipt]->setVal("<<qcd1m[ipt]->f2->getValV()<<");"<<endl;
      InValfile<<"aqcdsigma1[ipt] ->setVal("<<aqcd1[ipt] ->s1->getValV()<<");"<<endl;
      InValfile<<"aqcdPsigma1[ipt]->setVal("<<aqcd1p[ipt]->s1->getValV()<<");"<<endl;
      InValfile<<"aqcdMsigma1[ipt]->setVal("<<aqcd1m[ipt]->s1->getValV()<<");"<<endl;
      InValfile<<"aqcdsigma2[ipt] ->setVal("<<aqcd1[ipt] ->s2->getValV()<<");"<<endl;
      InValfile<<"aqcdPsigma2[ipt]->setVal("<<aqcd1p[ipt]->s2->getValV()<<");"<<endl;
      InValfile<<"aqcdMsigma2[ipt]->setVal("<<aqcd1m[ipt]->s2->getValV()<<");"<<endl;
    }else if (ipt > 4){
      InValfile<<"qcdsigma1[ipt] ->setVal("<<qcd2[ipt] ->sigma1->getValV()<<");"<<endl;
      InValfile<<"qcdPsigma1[ipt]->setVal("<<qcd2p[ipt]->sigma1->getValV()<<");"<<endl;
      InValfile<<"qcdMsigma1[ipt]->setVal("<<qcd2m[ipt]->sigma1->getValV()<<");"<<endl;
      InValfile<<"qcda1[ipt] ->setVal("<<qcd2[ipt] ->a1->getValV()<<");"<<endl;
      InValfile<<"qcdPa1[ipt]->setVal("<<qcd2p[ipt]->a1->getValV()<<");"<<endl;
      InValfile<<"qcdMa1[ipt]->setVal("<<qcd2m[ipt]->a1->getValV()<<");"<<endl;
      InValfile<<"dFrac1[ipt] ->setVal("<<qcd2[ipt] ->frac1->getValV()<<");"<<endl;
      InValfile<<"dFrac1P[ipt]->setVal("<<qcd2p[ipt]->frac1->getValV()<<");"<<endl;
      InValfile<<"dFrac1M[ipt]->setVal("<<qcd2m[ipt]->frac1->getValV()<<");"<<endl;
      InValfile<<"qcdsigma2[ipt] ->setVal("<<qcd2[ipt] ->sigma2->getValV()<<");"<<endl;
      InValfile<<"qcdPsigma2[ipt]->setVal("<<qcd2p[ipt]->sigma2->getValV()<<");"<<endl;
      InValfile<<"qcdMsigma2[ipt]->setVal("<<qcd2m[ipt]->sigma2->getValV()<<");"<<endl;
      InValfile<<"qcda2[ipt] ->setVal("<<qcd2[ipt] ->a2->getValV()<<");"<<endl;
      InValfile<<"qcdPa2[ipt]->setVal("<<qcd2p[ipt]->a2->getValV()<<");"<<endl;
      InValfile<<"qcdMa2[ipt]->setVal("<<qcd2m[ipt]->a2->getValV()<<");"<<endl;
      InValfile<<"dFrac2[ipt] ->setVal("<<qcd2[ipt] ->frac2->getValV()<<");"<<endl;
      InValfile<<"dFrac2P[ipt]->setVal("<<qcd2p[ipt]->frac2->getValV()<<");"<<endl;
      InValfile<<"dFrac2M[ipt]->setVal("<<qcd2m[ipt]->frac2->getValV()<<");"<<endl;
      InValfile<<"aqcdsigma1[ipt] ->setVal("<<aqcd2[ipt] ->sigma1->getValV()<<");"<<endl;
      InValfile<<"aqcdPsigma1[ipt]->setVal("<<aqcd2p[ipt]->sigma1->getValV()<<");"<<endl;
      InValfile<<"aqcdMsigma1[ipt]->setVal("<<aqcd2m[ipt]->sigma1->getValV()<<");"<<endl;
      InValfile<<"aqcdsigma2[ipt] ->setVal("<<aqcd2[ipt] ->sigma2->getValV()<<");"<<endl;
      InValfile<<"aqcdPsigma2[ipt]->setVal("<<aqcd2p[ipt]->sigma2->getValV()<<");"<<endl;
      InValfile<<"aqcdMsigma2[ipt]->setVal("<<aqcd2m[ipt]->sigma2->getValV()<<");"<<endl;
    }
    InValfile<<endl;
    InValfile.flags(flags);

    metplotsfile<<"<hr />"<<endl;
    if (ipt==0)
      metplotsfile<<"<p align=\"center\"> [0, 600] Bin - "<<ipt<<"</p>"<<endl;
    else
      metplotsfile<<"<p align=\"center\"> ["<<WptBins[ipt-1]<<", "<<WptBins[ipt]<<"] Bin - "<<ipt<<"</p>"<<endl;
    metplotsfile<<"<table border=\"0\" cellspacing=\"5\" width=\"900\" align=\"center\">"<<endl; 
    metplotsfile<<"<tr>"<<endl;
    metplotsfile<<"<td width=\"100\"></td>"<<endl;
    metplotsfile<<"<td width=\"400\" colspan=\"2\"><p align=\"center\" style=\"font-size:small\"> Signal </p></td>"<<endl;
    metplotsfile<<"<td width=\"400\" colspan=\"2\"><p align=\"center\" style=\"font-size:small\"> Side </p></td>"<<endl;
    metplotsfile<<"</tr>"<<endl;
    metplotsfile<<"<tr>"<<endl;
    metplotsfile<<"<td width=\"100\"><p align=\"center\" style=\"font-size:small\"> W </p></td>"<<endl;
    metplotsfile<<"<td width=\"200\"><a target=\"_blank\" href=\"WMuNu_"<<ipt <<".png\"><img src=\"WMuNu_"<<ipt <<".png\" width=\"200\" alt=\"WMuNu_"<<ipt <<".png\"></a></td>"<<endl;
    metplotsfile<<"<td width=\"200\"><a target=\"_blank\" href=\"WMuNu_"<<ipt <<"_log.png\"><img src=\"WMuNu_"<<ipt <<"_log.png\" width=\"200\" alt=\"WMuNu_"<<ipt <<"_log.png\"></a></td>"<<endl;
    metplotsfile<<"<td width=\"200\"><a target=\"_blank\" href=\"WMuNu_cont_"<<ipt <<".png\"><img src=\"WMuNu_cont_"<<ipt <<".png\" width=\"200\" alt=\"WMuNu_cont_"<<ipt <<".png\"></a></td>"<<endl;
    metplotsfile<<"<td width=\"200\"><a target=\"_blank\" href=\"WMuNu_cont_"<<ipt <<"_log.png\"><img src=\"WMuNu_cont_"<<ipt <<"_log.png\" width=\"200\" alt=\"WMuNu_cont_"<<ipt <<"_log.png\"></a></td>"<<endl;
    metplotsfile<<"</tr>"<<endl;
    metplotsfile<<"<tr>"<<endl;
    metplotsfile<<"<td width=\"100\"><p align=\"center\" style=\"font-size:small\"> W <sup>+</sup> </p></td>"<<endl;
    metplotsfile<<"<td width=\"200\"><a target=\"_blank\" href=\"WpMuNu_"<<ipt <<".png\"><img src=\"WpMuNu_"<<ipt <<".png\" width=\"200\" alt=\"WpMuNu_"<<ipt <<".png\"></a></td>"<<endl;
    metplotsfile<<"<td width=\"200\"><a target=\"_blank\" href=\"WpMuNu_"<<ipt <<"_log.png\"><img src=\"WpMuNu_"<<ipt <<"_log.png\" width=\"200\" alt=\"WpMuNu_"<<ipt <<"_log.png\"></a></td>"<<endl;
    metplotsfile<<"<td width=\"200\"><a target=\"_blank\" href=\"WpMuNu_cont_"<<ipt <<".png\"><img src=\"WpMuNu_cont_"<<ipt <<".png\" width=\"200\" alt=\"WpMuNu_cont_"<<ipt <<".png\"></a></td>"<<endl;
    metplotsfile<<"<td width=\"200\"><a target=\"_blank\" href=\"WpMuNu_cont_"<<ipt <<"_log.png\"><img src=\"WpMuNu_cont_"<<ipt <<"_log.png\" width=\"200\" alt=\"WpMuNu_cont_"<<ipt <<"_log.png\"></a></td>"<<endl;
    metplotsfile<<"</tr>"<<endl;
    metplotsfile<<"<tr>"<<endl;
    metplotsfile<<"<td width=\"100\"><p align=\"center\" style=\"font-size:small\"> W <sup>-</sup></p></td>"<<endl;
    metplotsfile<<"<td width=\"200\"><a target=\"_blank\" href=\"WmMuNu_"<<ipt <<".png\"><img src=\"WmMuNu_"<<ipt <<".png\" width=\"200\" alt=\"WmMuNu_"<<ipt <<".png\"></a></td>"<<endl;
    metplotsfile<<"<td width=\"200\"><a target=\"_blank\" href=\"WmMuNu_"<<ipt <<"_log.png\"><img src=\"WmMuNu_"<<ipt <<"_log.png\" width=\"200\" alt=\"WmMuNu_"<<ipt <<"_log.png\"></a></td>"<<endl;
    metplotsfile<<"<td width=\"200\"><a target=\"_blank\" href=\"WmMuNu_cont_"<<ipt <<".png\"><img src=\"WmMuNu_cont_"<<ipt <<".png\" width=\"200\" alt=\"WmMuNu_cont_"<<ipt <<".png\"></a></td>"<<endl;
    metplotsfile<<"<td width=\"200\"><a target=\"_blank\" href=\"WmMuNu_cont_"<<ipt <<"_log.png\"><img src=\"WmMuNu_cont_"<<ipt <<"_log.png\" width=\"200\" alt=\"WmMuNu_cont_"<<ipt <<"_log.png\"></a></td>"<<endl;
    metplotsfile<<"</tr>"<<endl;
    metplotsfile<<"</table>"<<endl;

    if (ipt==0)
      tablefile<<"<p align=\"center\">  [0, 600] Bin - "<< ipt <<" Yields </p>"<<endl;
    else
      tablefile<<"<p align=\"center\"> ["<<WptBins[ipt-1]<<", "<<WptBins[ipt]<<"] Bin - "<< ipt <<" Yields </p>"<<endl;
    tablefile<<"<table border=\"1\" style=\"border-collapse: collapse\" bordercolor=\"black\" cellspacing=\"6\" width=\"880\" align=\"center\">"<<endl;
    tablefile<<"<tr>"<<endl;
    tablefile<<"<td width=\"60\"></td>"<<endl;
    tablefile<<"<td width=\"100\"><p> Selected</p></td>"<<endl;
    tablefile<<"<td width=\"180\"><p> Total</p></td>"<<endl;
    tablefile<<"<td width=\"180\"><p> Signal</p></td>"<<endl;
    tablefile<<"<td width=\"180\"><p> QCD</p></td>"<<endl;
    tablefile<<"<td width=\"180\"><p> Others</p></td>"<<endl;
    tablefile<<"</tr>"<<endl;
    tablefile<<fixed<<setprecision(1);
    tablefile<<"<tr>"<<endl;
    tablefile<<"<td width=\"60\"><p> W</p></td>"<<endl;
    tablefile<<"<td width=\"100\"><p>"<< hDataMet[ipt]->Integral() <<"</p></td>"<<endl;
    tablefile<<"<td width=\"180\"><p>"<< nSig[ipt]->getVal()+nQCD[ipt]->getVal()+nEWK[ipt]->getVal()<<" &plusmn; "<<sqrt(nSig[ipt]->getPropagatedError(*fitRes[ipt])*nSig[ipt]->getPropagatedError(*fitRes[ipt])+nQCD[ipt]->getPropagatedError(*fitRes[ipt])*nQCD[ipt]->getPropagatedError(*fitRes[ipt])+nEWK[ipt]->getPropagatedError(*fitRes[ipt])*nEWK[ipt]->getPropagatedError(*fitRes[ipt]))<<"</p></td>"<<endl;
    tablefile<<"<td width=\"180\"><p>"<< nSig[ipt]->getVal()<<" &plusmn; "<<nSig[ipt]->getPropagatedError(*fitRes[ipt])<<"</p></td>"<<endl;
    tablefile<<"<td width=\"180\"><p>"<< nQCD[ipt]->getVal()<<" &plusmn; "<<nQCD[ipt]->getPropagatedError(*fitRes[ipt])<<"</p></td>"<<endl;
    tablefile<<"<td width=\"180\"><p>"<< nEWK[ipt]->getVal()<<" &plusmn; "<<nEWK[ipt]->getPropagatedError(*fitRes[ipt])<<"</p></td>"<<endl;
    tablefile<<"</tr>"<<endl;
    tablefile<<"<tr>"<<endl;
    tablefile<<"<td width=\"60\"><p> W <sup>+</sup></p></td>"<<endl;
    tablefile<<"<td width=\"100\"><p>"<< hDataMetp[ipt]->Integral() <<"</p></td>"<<endl;
    tablefile<<"<td width=\"180\"><p>"<< nSigp[ipt]->getVal()+nQCDp[ipt]->getVal()+nEWKp[ipt]->getVal()<<" &plusmn; "<<sqrt(nSigp[ipt]->getPropagatedError(*fitResp[ipt])*nSigp[ipt]->getPropagatedError(*fitResp[ipt])+nQCDp[ipt]->getPropagatedError(*fitResp[ipt])*nQCDp[ipt]->getPropagatedError(*fitResp[ipt])+nEWKp[ipt]->getPropagatedError(*fitResp[ipt])*nEWKp[ipt]->getPropagatedError(*fitResp[ipt]))<<"</p></td>"<<endl;
    tablefile<<"<td width=\"180\"><p>"<< nSigp[ipt]->getVal()<<" &plusmn; "<<nSigp[ipt]->getPropagatedError(*fitResp[ipt])<<"</p></td>"<<endl;
    tablefile<<"<td width=\"180\"><p>"<< nQCDp[ipt]->getVal()<<" &plusmn; "<<nQCDp[ipt]->getPropagatedError(*fitResp[ipt])<<"</p></td>"<<endl;
    tablefile<<"<td width=\"180\"><p>"<< nEWKp[ipt]->getVal()<<" &plusmn; "<<nEWKp[ipt]->getPropagatedError(*fitResp[ipt])<<"</p></td>"<<endl;
    tablefile<<"</tr>"<<endl;
    tablefile<<"<tr>"<<endl;
    tablefile<<"<td width=\"60\"><p> W <sup>-</sup></p></td>"<<endl;
    tablefile<<"<td width=\"100\"><p>"<< hDataMetm[ipt]->Integral() <<"</p></td>"<<endl;
    tablefile<<"<td width=\"180\"><p>"<< nSigm[ipt]->getVal()+nQCDm[ipt]->getVal()+nEWKm[ipt]->getVal()<<" &plusmn; "<<sqrt(nSigm[ipt]->getPropagatedError(*fitResm[ipt])*nSigm[ipt]->getPropagatedError(*fitResm[ipt])+nQCDm[ipt]->getPropagatedError(*fitResm[ipt])*nQCDm[ipt]->getPropagatedError(*fitResm[ipt])+nEWKm[ipt]->getPropagatedError(*fitResm[ipt])*nEWKm[ipt]->getPropagatedError(*fitResm[ipt]))<<"</p></td>"<<endl;
    tablefile<<"<td width=\"180\"><p>"<< nSigm[ipt]->getVal()<<" &plusmn; "<<nSigm[ipt]->getPropagatedError(*fitResm[ipt])<<"</p></td>"<<endl;
    tablefile<<"<td width=\"180\"><p>"<< nQCDm[ipt]->getVal()<<" &plusmn; "<<nQCDm[ipt]->getPropagatedError(*fitResm[ipt])<<"</p></td>"<<endl;
    tablefile<<"<td width=\"180\"><p>"<< nEWKm[ipt]->getVal()<<" &plusmn; "<<nEWKm[ipt]->getPropagatedError(*fitResm[ipt])<<"</p></td>"<<endl;
    tablefile<<"</tr>"<<endl;
    tablefile<<"</table>"<<endl;
    tablefile<<"<hr />"<<endl;

    cout<<endl;
    cout<<"  <> Output saved in "<<outputDir<<"/"<<endl;    
    cout<<endl;

    if (ipt>0){
      hSigWpt -> SetBinContent(ipt, nSig[ipt]->getVal());
      hSigWpt -> SetBinError(ipt, nSig[ipt]->getPropagatedError(*fitRes[ipt]));
      hSigWPpt-> SetBinContent(ipt, nSigp[ipt]->getVal());
      hSigWPpt-> SetBinError(ipt, nSigp[ipt]->getPropagatedError(*fitResp[ipt]));
      hSigWMpt-> SetBinContent(ipt, nSigm[ipt]->getVal());
      hSigWMpt-> SetBinError(ipt, nSigm[ipt]->getPropagatedError(*fitResm[ipt]));
      hQCDWpt -> SetBinContent(ipt, nQCD[ipt]->getVal());
      hQCDWpt -> SetBinError(ipt, nQCD[ipt]->getPropagatedError(*fitRes[ipt]));
      hQCDWPpt-> SetBinContent(ipt, nQCDp[ipt]->getVal());
      hQCDWPpt-> SetBinError(ipt, nQCDp[ipt]->getPropagatedError(*fitResp[ipt]));
      hQCDWMpt-> SetBinContent(ipt, nQCDm[ipt]->getVal());
      hQCDWMpt-> SetBinError(ipt, nQCDm[ipt]->getPropagatedError(*fitResm[ipt]));
      
      hQCD_SigPlus    -> SetBinContent(ipt,nQCDp[ipt]->getVal()/nSigp[ipt]->getVal());
      hQCD_SigMinus   -> SetBinContent(ipt,nQCDm[ipt]->getVal()/nSigm[ipt]->getVal());
      hQCD_SigQCDPlus -> SetBinContent(ipt,nQCDp[ipt]->getVal()/(nQCDp[ipt]->getVal()+ nSigp[ipt]->getVal()));
      hQCD_SigQCDMinus-> SetBinContent(ipt,nQCDm[ipt]->getVal()/(nQCDm[ipt]->getVal()+ nSigm[ipt]->getVal()));
      
      double total = nEventDYToMuMu[ipt]+nEventDYToTauTau[ipt]+nEventTTJets[ipt]+nEventWToTauNu[ipt];
      double totalp = nEventDYToMuMuP[ipt]+nEventDYToTauTauP[ipt]+nEventTTJetsP[ipt]+nEventWToTauNuP[ipt];
      double totalm = nEventDYToMuMuM[ipt]+nEventDYToTauTauM[ipt]+nEventTTJetsM[ipt]+nEventWToTauNuM[ipt];
      hDYToMuMu   -> SetBinContent(ipt,nEWK[ipt]->getVal()*nEventDYToMuMu[ipt]/total);
      hDYToMuMu   -> SetBinError(ipt,nEWK[ipt]->getPropagatedError(*fitRes[ipt])*nEventDYToMuMu[ipt]/total);
      hWToTauNu   -> SetBinContent(ipt,nEWK[ipt]->getVal()*nEventWToTauNu[ipt]/total);
      hWToTauNu   -> SetBinError(ipt,nEWK[ipt]->getPropagatedError(*fitRes[ipt])*nEventWToTauNu[ipt]/total);
      hTTJets     -> SetBinContent(ipt,nEWK[ipt]->getVal()*nEventTTJets[ipt]/total);
      hTTJets     -> SetBinError(ipt,nEWK[ipt]->getPropagatedError(*fitRes[ipt])*nEventTTJets[ipt]/total);
      hDYToTauTau -> SetBinContent(ipt,nEWK[ipt]->getVal()*nEventDYToTauTau[ipt]/total);
      hDYToTauTau -> SetBinError(ipt,nEWK[ipt]->getPropagatedError(*fitRes[ipt])*nEventDYToTauTau[ipt]/total);
      hDYToMuMuP  -> SetBinContent(ipt,nEWKp[ipt]->getVal()*nEventDYToMuMuP[ipt]/totalp);
      hDYToMuMuP  -> SetBinError(ipt,nEWKp[ipt]->getPropagatedError(*fitResp[ipt])*nEventDYToMuMuP[ipt]/totalp);
      hWToTauNuP  -> SetBinContent(ipt,nEWKp[ipt]->getVal()*nEventWToTauNuP[ipt]/totalp);
      hWToTauNuP  -> SetBinError(ipt,nEWKp[ipt]->getPropagatedError(*fitResp[ipt])*nEventWToTauNuP[ipt]/totalp);
      hTTJetsP    -> SetBinContent(ipt,nEWKp[ipt]->getVal()*nEventTTJetsP[ipt]/totalp);
      hTTJetsP    -> SetBinError(ipt,nEWKp[ipt]->getPropagatedError(*fitResp[ipt])*nEventTTJetsP[ipt]/totalp);
      hDYToTauTauP-> SetBinContent(ipt,nEWKp[ipt]->getVal()*nEventDYToTauTauP[ipt]/totalp);
      hDYToTauTauP-> SetBinError(ipt,nEWKp[ipt]->getPropagatedError(*fitResp[ipt])*nEventDYToTauTauP[ipt]/totalp);
      hDYToMuMuM  -> SetBinContent(ipt,nEWKm[ipt]->getVal()*nEventDYToMuMuM[ipt]/totalm);
      hDYToMuMuM  -> SetBinError(ipt,nEWKm[ipt]->getPropagatedError(*fitResm[ipt])*nEventDYToMuMuM[ipt]/totalm);
      hWToTauNuM  -> SetBinContent(ipt,nEWKm[ipt]->getVal()*nEventWToTauNuM[ipt]/totalm);
      hWToTauNuM  -> SetBinError(ipt,nEWKm[ipt]->getPropagatedError(*fitResm[ipt])*nEventWToTauNuM[ipt]/totalm);
      hTTJetsM    -> SetBinContent(ipt,nEWKm[ipt]->getVal()*nEventTTJetsM[ipt]/totalm);
      hTTJetsM    -> SetBinError(ipt,nEWKm[ipt]->getPropagatedError(*fitResm[ipt])*nEventTTJetsM[ipt]/totalm);
      hDYToTauTauM-> SetBinContent(ipt,nEWKm[ipt]->getVal()*nEventDYToTauTauM[ipt]/totalm);
      hDYToTauTauM-> SetBinError(ipt,nEWKm[ipt]->getPropagatedError(*fitResm[ipt])*nEventDYToTauTauM[ipt]/totalm);
    }
  }

  Wmfile.close();
  Wmpfile.close();
  Wmmfile.close();
  qcdfile.close();
  InValfile.close();

  tablefile<<"</body>"<<endl;
  tablefile<<"</html>"<<endl;
  tablefile.close();

  metplotsfile<<"</body>"<<endl;
  metplotsfile<<"</html>"<<endl;
  metplotsfile.close();  

  allyields.close();
  allyieldsp.close();
  allyieldsm.close();
//Write Signal numbers to file
  gSystem->mkdir(outputDir+"/RstElectron",kTRUE);
  TString Yields = outputDir+"/RstElectron/SigYields_"+filetype+".root";

  TFile *nsigfile = new TFile(Yields,"RECREATE");
  hSigWpt -> Write();
  hSigWPpt-> Write();
  hSigWMpt-> Write();
  hQCDWpt -> Write();
  hQCDWPpt-> Write();
  hQCDWMpt-> Write();
  
  //TF1 *f111 = new TF1("f111","[0]*TMath::Exp(-x/[1])+[2]",50.,600.);
  //f111->SetParameter(0,1);
  //f111->SetParameter(1,0.3);
  //f111->SetParameter(2,0);
  //f111->SetLineColor(kBlue);
  //hQCD_SigPlus->Fit("f111","L","",50.,600.);
  //hQCD_SigPlus-> Write();
  //hQCD_SigMinus->Fit("f111","L","",50.,600.);
  //hQCD_SigMinus-> Write();

  //hQCD_SigQCDPlus->Fit("f111","L","",50.,600.);
  //hQCD_SigQCDPlus-> Write();
  //hQCD_SigQCDMinus->Fit("f111","L","",50.,600.);
  //hQCD_SigQCDMinus-> Write();
  
  nsigfile->Close();

// Wpt distribution=========================
  TH1D* hWptDiff;
  TH1D* hWptDiff_p;
  TH1D* hWptDiff_m;
  TH1D* hWptDiffLog;
  TH1D* hWPptDiffLog;
  TH1D* hWMptDiffLog;

  CPlot* plotWpt;
  CPlot* plotWptDiff;
  CPlot* plotWpt_p;
  CPlot* plotWptDiff_p;
  CPlot* plotWpt_m;
  CPlot* plotWptDiff_m;

  CPlot* plotWptLog;
  CPlot* plotWPptLog;
  CPlot* plotWMptLog;
  CPlot* plotWptDiffLog;
  CPlot* plotWPptDiffLog;
  CPlot* plotWMptDiffLog;

//Inclusive W pt distribution
  TH1D* hWptMC = (TH1D*)hDYToTauTau->Clone("hWptMC");
  hWptMC->Add(hTTJets);
  hWptMC->Add(hWToTauNu);
  hWptMC->Add(hDYToMuMu);
  hWptMC->Add(hQCDWpt);
  hWptMC->Add(hSigWpt);
  hWptDiff = makeDiffHistWpt(hdataWpt,hWptMC,"hWptDiff");
  hWptDiff->SetMarkerStyle(kFullCircle);
  hWptDiff->SetMarkerSize(0.9);

  sprintf(histName,"FitWDistribution_Muon");
  plotWpt=new CPlot(histName,"","","Events");
  plotWpt->setOutDir(CPlot::sOutDir);
  plotWpt->AddToStack(hDYToTauTau,"Z/#gamma^{*}#rightarrow#tau#tau",kSpring+5,kSpring+3);
  plotWpt->AddToStack(hTTJets,"t#bar{t}",kAzure-5,kAzure-1);
  plotWpt->AddToStack(hWToTauNu,"W#rightarrow#tau#nu",kCyan-9,kCyan-6);
  plotWpt->AddToStack(hDYToMuMu,"Z/#gamma^{*}#rightarrow ee",fillcolorEWK,linecolorEWK);
  plotWpt->AddToStack(hQCDWpt,"QCD",fillcolorQCD,linecolorQCD);
  plotWpt->AddToStack(hSigWpt,"W#rightarrow e#nu",fillcolorW,linecolorW);
  plotWpt->AddHist1D(hdataWpt,"Data","E");
  plotWpt->SetLegend(0.78,0.65,.98,0.88);
  plotWpt->SetYRange(0.1,1.1*(hWptMC->GetMaximum()));
  plotWpt->Draw(c,kFALSE,format,1);
  gPad->RedrawAxis();

  plotWptDiff=new CPlot(histName,"","p_{T} [Gev]","#chi");
  plotWptDiff->setOutDir(CPlot::sOutDir);
  //plotWptDiff->AddHist1D(hWptDiff,"EX0",ratioColor);
  plotWptDiff->AddHist1D(hWptDiff,"hist p",kBlack);
  plotWptDiff->SetYRange(-0.1,0.1);
  plotWptDiff->AddLine(0, 0,600, 0,kBlack,1);
  plotWptDiff->AddLine(0, 0.05,600, 0.05,kBlack,3);
  plotWptDiff->AddLine(0,-0.05,600,-0.05,kBlack,3);
  plotWptDiff->Draw(c,kTRUE,format,2);

  //sprintf(histName,"FitWDistribution_MuonLog");
  //plotWpt->SetName(histName);
  //plotWpt->SetYRange(5e-6*(hWptMC->GetMaximum()),1.4*(hWptMC->GetMaximum()));
  //plotWpt->SetLogy();
  //plotWpt->Draw(c,kTRUE,format,1);
  
  double WptBinsLog[14]={1,7.5,12.5,17.5,24,30,40,50,70,110,150,190,250,600};
  double x1,x2,x3,x4,x5,x6,x7,err;
  TH1D *hDYToTauTauLog = new TH1D("hDYToTauTauLog","",13,WptBinsLog);
  TH1D *hTTJetsLog = new TH1D("hTTJetsLog","",13,WptBinsLog);
  TH1D *hWToTauNuLog = new TH1D("hWToTauNuLog","",13,WptBinsLog);
  TH1D *hDYToMuMuLog = new TH1D("hDYToMuMuLog","",13,WptBinsLog);
  TH1D *hQCDWptLog = new TH1D("hQCDWptLog","",13,WptBinsLog);
  TH1D *hSigWptLog = new TH1D("hSigWptLog","",13,WptBinsLog);
  TH1D *hdataWptLog = new TH1D("hdataWptLog","",13,WptBinsLog);
  TAxis *xaxis = hSigWpt->GetXaxis();
  for (int i=1; i<=hSigWpt->GetNbinsX(); i++){
    x1=hDYToTauTau->GetBinContent(i);
    x2=hTTJets->GetBinContent(i);
    x3=hWToTauNu->GetBinContent(i);
    x4=hDYToMuMu->GetBinContent(i);
    x5=hQCDWpt->GetBinContent(i);
    x6=hSigWpt->GetBinContent(i);
    x7=hdataWpt->GetBinContent(i);
    err = hdataWpt->GetBinError(i);
    hDYToTauTauLog->Fill(xaxis->GetBinCenter(i),x1);
    hTTJetsLog->Fill(xaxis->GetBinCenter(i),x2);
    hWToTauNuLog->Fill(xaxis->GetBinCenter(i),x3);
    hDYToMuMuLog->Fill(xaxis->GetBinCenter(i),x4);
    hQCDWptLog->Fill(xaxis->GetBinCenter(i),x5);
    hSigWptLog->Fill(xaxis->GetBinCenter(i),x6);
    hdataWptLog->Fill(xaxis->GetBinCenter(i),x7);
    hdataWptLog->SetBinError(i,err);
  }
  
  TH1D* hWptMCLog = (TH1D*)hDYToTauTauLog->Clone("hWptMCLog");
  hWptMCLog->Add(hTTJetsLog);
  hWptMCLog->Add(hWToTauNuLog);
  hWptMCLog->Add(hDYToMuMuLog);
  hWptMCLog->Add(hQCDWptLog);
  hWptMCLog->Add(hSigWptLog);
  hWptDiffLog = makeDiffHistWptLog(hdataWptLog,hWptMCLog,"hWptDiffLog");
  hWptDiffLog->SetMarkerStyle(kFullCircle);
  hWptDiffLog->SetMarkerSize(0.9);

  sprintf(histName,"FitWDistribution_MuonLog");
  plotWptLog=new CPlot(histName,"","","Events");
  plotWptLog->setOutDir(CPlot::sOutDir);
  plotWptLog->AddToStack(hDYToTauTauLog,"Z/#gamma^{*}#rightarrow#tau#tau",kSpring+5,kSpring+3);
  plotWptLog->AddToStack(hTTJetsLog,"t#bar{t}",kAzure-5,kAzure-1);
  plotWptLog->AddToStack(hWToTauNuLog,"W#rightarrow#tau#nu",kCyan-9,kCyan-6);
  plotWptLog->AddToStack(hDYToMuMuLog,"Z/#gamma^{*}#rightarrow ee",fillcolorEWK,linecolorEWK);
  plotWptLog->AddToStack(hQCDWptLog,"QCD",fillcolorQCD,linecolorQCD);
  plotWptLog->AddToStack(hSigWptLog,"W#rightarrow e#nu",fillcolorW,linecolorW);
  plotWptLog->AddHist1D(hdataWptLog,"Data","E");
  plotWptLog->SetLegend(0.78,0.65,.98,0.88);
  plotWptLog->SetYRange(5e-6*(hWptMC->GetMaximum()),1.4*(hWptMC->GetMaximum()));
  plotWptLog->SetLogx();
  plotWptLog->SetLogy();
  plotWptLog->Draw(c,kFALSE,format,1);
  gPad->RedrawAxis();
  
  plotWptDiffLog=new CPlot(histName,"","p_{T} [Gev]","#chi");
  plotWptDiffLog->setOutDir(CPlot::sOutDir);
  //plotWptDiffLog->AddHist1D(hWptDiffLog,"EX0",ratioColor);
  plotWptDiffLog->AddHist1D(hWptDiffLog,"hist p",kBlack);
  plotWptDiffLog->SetYRange(-0.1,0.1);
  plotWptDiffLog->AddLine(0, 0,600, 0,kBlack,1);
  plotWptDiffLog->AddLine(0, 0.05,600, 0.05,kBlack,3);
  plotWptDiffLog->AddLine(0,-0.05,600,-0.05,kBlack,3);
  plotWptDiffLog->SetLogx();
  plotWptDiffLog->Draw(c,kTRUE,format,2);

//W plus pt distribution
  TH1D* hWptMC_p = (TH1D*)hDYToTauTauP->Clone("hWptMC_p");
  hWptMC_p->Add(hTTJetsP);
  hWptMC_p->Add(hWToTauNuP);
  hWptMC_p->Add(hDYToMuMuP);
  hWptMC_p->Add(hQCDWPpt);
  hWptMC_p->Add(hSigWPpt);
  hWptDiff_p = makeDiffHistWpt(hdataWPpt,hWptMC_p,"hWptDiff_p");
  hWptDiff_p->SetMarkerStyle(kFullCircle);
  hWptDiff_p->SetMarkerSize(0.9);

  sprintf(histName,"FitWDistribution_MuonP");
  plotWpt_p=new CPlot(histName,"","","Events");
  plotWpt_p->setOutDir(CPlot::sOutDir);
  plotWpt_p->AddToStack(hDYToTauTauP,"Z/#gamma^{*}#rightarrow#tau#tau",kSpring+5,kSpring+3);
  plotWpt_p->AddToStack(hTTJetsP,"t#bar{t}",kAzure-5,kAzure-1);
  plotWpt_p->AddToStack(hWToTauNuP,"W#rightarrow#tau#nu",kCyan-9,kCyan-6);
  plotWpt_p->AddToStack(hDYToMuMuP,"Z/#gamma^{*}#rightarrow ee",fillcolorEWK,linecolorEWK);
  plotWpt_p->AddToStack(hQCDWPpt,"QCD",fillcolorQCD,linecolorQCD);
  plotWpt_p->AddToStack(hSigWPpt,"W#rightarrow e#nu",fillcolorW,linecolorW);
  plotWpt_p->AddHist1D(hdataWPpt,"Data","E");
  plotWpt_p->SetLegend(0.78,0.65,.98,0.88);
  plotWpt_p->SetYRange(0.1,1.1*(hWptMC_p->GetMaximum()));
  plotWpt_p->Draw(c,kFALSE,format,1);
  gPad->RedrawAxis();

  plotWptDiff_p=new CPlot(histName,"","p_{T} [Gev]","#chi");
  plotWptDiff_p->setOutDir(CPlot::sOutDir);
  //plotWptDiff_p->AddHist1D(hWptDiff_p,"EX0",ratioColor);
  plotWptDiff_p->AddHist1D(hWptDiff_p,"hist p",kBlack);
  plotWptDiff_p->SetYRange(-0.1,0.1);
  plotWptDiff_p->AddLine(0, 0,600, 0,kBlack,1);
  plotWptDiff_p->AddLine(0, 0.05,600, 0.05,kBlack,3);
  plotWptDiff_p->AddLine(0,-0.05,600,-0.05,kBlack,3);
  plotWptDiff_p->Draw(c,kTRUE,format,2);
  
  //sprintf(histName,"FitWDistribution_MuonPLog");
  //plotWpt_p->SetName(histName);
  //plotWpt_p->SetYRange(5e-6*(hWptMC_p->GetMaximum()),1.4*(hWptMC_p->GetMaximum()));
  //plotWpt_p->SetLogy();
  //plotWpt_p->Draw(c,kTRUE,format,1);
  
  TH1D *hDYToTauTauLogP = new TH1D("hDYToTauTauLogP","",13,WptBinsLog);
  TH1D *hTTJetsLogP = new TH1D("hTTJetsLogP","",13,WptBinsLog);
  TH1D *hWToTauNuLogP = new TH1D("hWToTauNuLogP","",13,WptBinsLog);
  TH1D *hDYToMuMuLogP = new TH1D("hDYToMuMuLogP","",13,WptBinsLog);
  TH1D *hQCDWptLogP = new TH1D("hQCDWptLogP","",13,WptBinsLog);
  TH1D *hSigWptLogP = new TH1D("hSigWptLogP","",13,WptBinsLog);
  TH1D *hdataWptLogP = new TH1D("hdataWptLogP","",13,WptBinsLog);
  for (int i=1; i<=hSigWPpt->GetNbinsX(); i++){
    x1=hDYToTauTauP->GetBinContent(i);
    x2=hTTJetsP->GetBinContent(i);
    x3=hWToTauNuP->GetBinContent(i);
    x4=hDYToMuMuP->GetBinContent(i);
    x5=hQCDWPpt->GetBinContent(i);
    x6=hSigWPpt->GetBinContent(i);
    x7=hdataWPpt->GetBinContent(i);
    err = hdataWPpt->GetBinError(i);
    hDYToTauTauLogP->Fill(xaxis->GetBinCenter(i),x1);
    hTTJetsLogP->Fill(xaxis->GetBinCenter(i),x2);
    hWToTauNuLogP->Fill(xaxis->GetBinCenter(i),x3);
    hDYToMuMuLogP->Fill(xaxis->GetBinCenter(i),x4);
    hQCDWptLogP->Fill(xaxis->GetBinCenter(i),x5);
    hSigWptLogP->Fill(xaxis->GetBinCenter(i),x6);
    hdataWptLogP->Fill(xaxis->GetBinCenter(i),x7);
    hdataWptLogP->SetBinError(i,err);
  }
  
  TH1D* hWPptMCLog = (TH1D*)hDYToTauTauLogP->Clone("hWPptMCLog");
  hWPptMCLog->Add(hTTJetsLogP);
  hWPptMCLog->Add(hWToTauNuLogP);
  hWPptMCLog->Add(hDYToMuMuLogP);
  hWPptMCLog->Add(hQCDWptLogP);
  hWPptMCLog->Add(hSigWptLogP);
  hWPptDiffLog = makeDiffHistWptLog(hdataWptLogP,hWPptMCLog,"hWPptDiffLog");
  hWPptDiffLog->SetMarkerStyle(kFullCircle);
  hWPptDiffLog->SetMarkerSize(0.9);
  
  sprintf(histName,"FitWDistribution_MuonPLog");
  plotWPptLog=new CPlot(histName,"","","Events");
  plotWPptLog->setOutDir(CPlot::sOutDir);
  plotWPptLog->AddToStack(hDYToTauTauLogP,"Z/#gamma^{*}#rightarrow#tau#tau",kSpring+5,kSpring+3);
  plotWPptLog->AddToStack(hTTJetsLogP,"t#bar{t}",kAzure-5,kAzure-1);
  plotWPptLog->AddToStack(hWToTauNuLogP,"W#rightarrow#tau#nu",kCyan-9,kCyan-6);
  plotWPptLog->AddToStack(hDYToMuMuLogP,"Z/#gamma^{*}#rightarrow ee",fillcolorEWK,linecolorEWK);
  plotWPptLog->AddToStack(hQCDWptLogP,"QCD",fillcolorQCD,linecolorQCD);
  plotWPptLog->AddToStack(hSigWptLogP,"W^{+}#rightarrow e^{+}#nu",fillcolorW,linecolorW);
  plotWPptLog->AddHist1D(hdataWptLogP,"Data","E");
  plotWPptLog->SetLegend(0.78,0.65,.98,0.88);
  plotWPptLog->SetYRange(5e-6*(hWptMC_p->GetMaximum()),1.4*(hWptMC_p->GetMaximum()));
  plotWPptLog->SetLogx();
  plotWPptLog->SetLogy();
  plotWPptLog->Draw(c,kFALSE,format,1);
  gPad->RedrawAxis();
  
  plotWPptDiffLog=new CPlot(histName,"","p_{T} [Gev]","#chi");
  plotWPptDiffLog->setOutDir(CPlot::sOutDir);
  //plotWPptDiffLog->AddHist1D(hWPptDiffLog,"EX0",ratioColor);
  plotWPptDiffLog->AddHist1D(hWPptDiffLog,"hist p",kBlack);
  plotWPptDiffLog->SetYRange(-0.1,0.1);
  plotWPptDiffLog->AddLine(0, 0,600, 0,kBlack,1);
  plotWPptDiffLog->AddLine(0, 0.05,600, 0.05,kBlack,3);
  plotWPptDiffLog->AddLine(0,-0.05,600,-0.05,kBlack,3);
  plotWPptDiffLog->SetLogx();
  plotWPptDiffLog->Draw(c,kTRUE,format,2);

//W minus pt distribution
  TH1D* hWptMC_m = (TH1D*)hDYToTauTauM->Clone("hWptMC_m");
  hWptMC_m->Add(hTTJetsM);
  hWptMC_m->Add(hWToTauNuM);
  hWptMC_m->Add(hDYToMuMuM);
  hWptMC_m->Add(hQCDWMpt);
  hWptMC_m->Add(hSigWMpt);
  hWptDiff_m = makeDiffHistWpt(hdataWMpt,hWptMC_m,"hWptDiff_m");
  hWptDiff_m->SetMarkerStyle(kFullCircle);
  hWptDiff_m->SetMarkerSize(0.9);

  sprintf(histName,"FitWDistribution_MuonM");
  plotWpt_m=new CPlot(histName,"","","Events");
  plotWpt_m->setOutDir(CPlot::sOutDir);
  plotWpt_m->AddToStack(hDYToTauTauM,"Z/#gamma^{*}#rightarrow#tau#tau",kSpring+5,kSpring+3);
  plotWpt_m->AddToStack(hTTJetsM,"t#bar{t}",kAzure-5,kAzure-1);
  plotWpt_m->AddToStack(hWToTauNuM,"W#rightarrow#tau#nu",kCyan-9,kCyan-6);
  plotWpt_m->AddToStack(hDYToMuMuM,"Z/#gamma^{*}#rightarrow ee",fillcolorEWK,linecolorEWK);
  plotWpt_m->AddToStack(hQCDWMpt,"QCD",fillcolorQCD,linecolorQCD);
  plotWpt_m->AddToStack(hSigWMpt,"W#rightarrow e#nu",fillcolorW,linecolorW);
  plotWpt_m->AddHist1D(hdataWMpt,"Data","E");
  plotWpt_m->SetLegend(0.78,0.65,.98,0.88);
  plotWpt_m->SetYRange(0.1,1.1*(hWptMC_m->GetMaximum()));
  plotWpt_m->Draw(c,kFALSE,format,1);
  gPad->RedrawAxis();

  plotWptDiff_m=new CPlot(histName,"","p_{T} [Gev]","#chi");
  plotWptDiff_m->setOutDir(CPlot::sOutDir);
  //plotWptDiff_m->AddHist1D(hWptDiff_m,"EX0",ratioColor);
  plotWptDiff_m->AddHist1D(hWptDiff_m,"hist p",kBlack);
  plotWptDiff_m->SetYRange(-0.1,0.1);
  plotWptDiff_m->AddLine(0, 0,600, 0,kBlack,1);
  plotWptDiff_m->AddLine(0, 0.05,600, 0.05,kBlack,3);
  plotWptDiff_m->AddLine(0,-0.05,600,-0.05,kBlack,3);
  plotWptDiff_m->Draw(c,kTRUE,format,2);
  
  //sprintf(histName,"FitWDistribution_MuonMLog");
  //plotWpt_m->SetName(histName);
  //plotWpt_m->SetYRange(5e-6*(hWptMC_m->GetMaximum()),1.4*(hWptMC_m->GetMaximum()));
  //plotWpt_m->SetLogy();
  //plotWpt_m->Draw(c,kTRUE,format,1);

  TH1D *hDYToTauTauLogM = new TH1D("hDYToTauTauLogM","",13,WptBinsLog);
  TH1D *hTTJetsLogM = new TH1D("hTTJetsLogM","",13,WptBinsLog);
  TH1D *hWToTauNuLogM = new TH1D("hWToTauNuLogM","",13,WptBinsLog);
  TH1D *hDYToMuMuLogM = new TH1D("hDYToMuMuLogM","",13,WptBinsLog);
  TH1D *hQCDWptLogM = new TH1D("hQCDWptLogM","",13,WptBinsLog);
  TH1D *hSigWptLogM = new TH1D("hSigWptLogM","",13,WptBinsLog);
  TH1D *hdataWptLogM = new TH1D("hdataWptLogM","",13,WptBinsLog);
  for (int i=1; i<=hSigWMpt->GetNbinsX(); i++){
    x1=hDYToTauTauM->GetBinContent(i);
    x2=hTTJetsM->GetBinContent(i);
    x3=hWToTauNuM->GetBinContent(i);
    x4=hDYToMuMuM->GetBinContent(i);
    x5=hQCDWMpt->GetBinContent(i);
    x6=hSigWMpt->GetBinContent(i);
    x7=hdataWMpt->GetBinContent(i);
    err = hdataWMpt->GetBinError(i);
    hDYToTauTauLogM->Fill(xaxis->GetBinCenter(i),x1);
    hTTJetsLogM->Fill(xaxis->GetBinCenter(i),x2);
    hWToTauNuLogM->Fill(xaxis->GetBinCenter(i),x3);
    hDYToMuMuLogM->Fill(xaxis->GetBinCenter(i),x4);
    hQCDWptLogM->Fill(xaxis->GetBinCenter(i),x5);
    hSigWptLogM->Fill(xaxis->GetBinCenter(i),x6);
    hdataWptLogM->Fill(xaxis->GetBinCenter(i),x7);
    hdataWptLogM->SetBinError(i,err);
  }
  
  TH1D* hWMptMCLog = (TH1D*)hDYToTauTauLogM->Clone("hWMptMCLog");
  hWMptMCLog->Add(hTTJetsLogM);
  hWMptMCLog->Add(hWToTauNuLogM);
  hWMptMCLog->Add(hDYToMuMuLogM);
  hWMptMCLog->Add(hQCDWptLogM);
  hWMptMCLog->Add(hSigWptLogM);
  hWMptDiffLog = makeDiffHistWptLog(hdataWptLogM,hWMptMCLog,"hWMptDiffLog");
  hWMptDiffLog->SetMarkerStyle(kFullCircle);
  hWMptDiffLog->SetMarkerSize(0.9);
  
  sprintf(histName,"FitWDistribution_MuonMLog");
  plotWMptLog=new CPlot(histName,"","","Events");
  plotWMptLog->setOutDir(CPlot::sOutDir);
  plotWMptLog->AddToStack(hDYToTauTauLogM,"Z/#gamma^{*}#rightarrow#tau#tau",kSpring+5,kSpring+3);
  plotWMptLog->AddToStack(hTTJetsLogM,"t#bar{t}",kAzure-5,kAzure-1);
  plotWMptLog->AddToStack(hWToTauNuLogM,"W#rightarrow#tau#nu",kCyan-9,kCyan-6);
  plotWMptLog->AddToStack(hDYToMuMuLogM,"Z/#gamma^{*}#rightarrow ee",fillcolorEWK,linecolorEWK);
  plotWMptLog->AddToStack(hQCDWptLogM,"QCD",fillcolorQCD,linecolorQCD);
  plotWMptLog->AddToStack(hSigWptLogM,"W^{-}#rightarrow e^{-} #bar{#nu}",fillcolorW,linecolorW);
  plotWMptLog->AddHist1D(hdataWptLogM,"Data","E");
  plotWMptLog->SetLegend(0.78,0.65,.98,0.88);
  plotWMptLog->SetYRange(5e-6*(hWptMC_m->GetMaximum()),1.4*(hWptMC_m->GetMaximum()));
  plotWMptLog->SetLogx();
  plotWMptLog->SetLogy();
  plotWMptLog->Draw(c,kFALSE,format,1);
  gPad->RedrawAxis();

  plotWMptDiffLog=new CPlot(histName,"","p_{T} [Gev]","#chi");
  plotWMptDiffLog->setOutDir(CPlot::sOutDir);
  //plotWMptDiffLog->AddHist1D(hWMptDiffLog,"EX0",ratioColor);
  plotWMptDiffLog->AddHist1D(hWMptDiffLog,"hist p",kBlack);
  plotWMptDiffLog->SetYRange(-0.1,0.1);
  plotWMptDiffLog->AddLine(0, 0,600, 0,kBlack,1);
  plotWMptDiffLog->AddLine(0, 0.05,600, 0.05,kBlack,3);
  plotWMptDiffLog->AddLine(0,-0.05,600,-0.05,kBlack,3);
  plotWMptDiffLog->SetLogx();
  plotWMptDiffLog->Draw(c,kTRUE,format,2);
		    
  makeHTML(outputDir);
  gBenchmark->Show("fitWEleMetModRayleighSimult");
}


//=== FUNCTION DEFINITIONS ======================================================================================

//--------------------------------------------------------------------------------------------------
TH1D *makeDiffHist(TH1D* hData, TH1D* hFit, const TString name)
{
//  double WptBins[14]={0,7.5,12.5,17.5,24,30,40,50,70,110,150,190,250,600};
//  TH1D *hDiff = new TH1D(name,"",45,0,100);
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
  double WptBins[14]={0,7.5,12.5,17.5,24,30,40,50,70,110,150,190,250,600};
  TH1D *hDiff = new TH1D(name,"",13,WptBins);
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
TH1D *makeDiffHistWptLog(TH1D* hData, TH1D* hFit, const TString name)
{
  double WptBins[14]={1,7.5,12.5,17.5,24,30,40,50,70,110,150,190,250,600};
  TH1D *hDiff = new TH1D(name,"",13,WptBins);
  TAxis *xaxis = hData->GetXaxis();
  for(int ibin=1; ibin<=hData->GetNbinsX(); ibin++) {
    //cout << "Data: " << hData->GetBinContent(ibin) << " MC: " << hFit->GetBinContent(ibin) << endl;
    Double_t diff = (hData->GetBinContent(ibin)-hFit->GetBinContent(ibin));
    
    Double_t err = sqrt(hData->GetBinContent(ibin));
    if(err==0) err= sqrt(hFit->GetBinContent(ibin));
    
    if(err>0) hDiff->Fill(xaxis->GetBinCenter(ibin),diff/err);
    else      hDiff->Fill(xaxis->GetBinCenter(ibin),0);
    Double_t errDiff = sqrt(hData->GetBinError(ibin)*hData->GetBinError(ibin)+hFit->GetBinError(ibin)*hFit->GetBinError(ibin));
    hDiff->SetBinError(ibin,errDiff);
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
  sprintf(htmlfname,"%s/WmunuFitPlots.html",outDir.Data());
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
  htmlfile << "<td width=\"25%\"><a target=\"_blank\" href=\"FitWDistribution_Muon.png\"><img src=\"FitWDistribution_Muon.png\" alt=\"FitWDistribution_Muon.png\" width=\"100%\"></a></td>" << endl;
  htmlfile << "<td width=\"25%\"><a target=\"_blank\" href=\"FitWDistribution_MuonP.png\"><img src=\"FitWDistribution_MuonP.png\" alt=\"FitWDistribution_MuonP.png\" width=\"100%\"></a></td>" << endl;
  htmlfile << "<td width=\"25%\"><a target=\"_blank\" href=\"FitWDistribution_MuonM.png\"><img src=\"FitWDistribution_MuonM.png\" alt=\"FitWDistribution_MuonM.png\" width=\"100%\"></a></td>" << endl;
  htmlfile << "<td width=\"10%\"></td>" << endl;
  htmlfile << "</tr>" << endl;
  htmlfile << "<tr>" << endl;
  htmlfile << "<td width=\"15%\"></td>" << endl;
  htmlfile << "<td width=\"25%\"><a target=\"_blank\" href=\"FitWDistribution_MuonLog.png\"><img src=\"FitWDistribution_MuonLog.png\" alt=\"FitWDistribution_MuonLog.png\" width=\"100%\"></a></td>" << endl;
  htmlfile << "<td width=\"25%\"><a target=\"_blank\" href=\"FitWDistribution_MuonPLog.png\"><img src=\"FitWDistribution_MuonPLog.png\" alt=\"FitWDistribution_MuonPLog.png\" width=\"100%\"></a></td>" << endl;
  htmlfile << "<td width=\"25%\"><a target=\"_blank\" href=\"FitWDistribution_MuonMLog.png\"><img src=\"FitWDistribution_MuonMLog.png\" alt=\"FitWDistribution_MuonMLog.png\" width=\"100%\"></a></td>" << endl;
  htmlfile << "<td width=\"10%\"></td>" << endl;
  htmlfile << "</tr>" << endl;
  htmlfile << "</table>" << endl;
  htmlfile << "<hr />" << endl;
  htmlfile << "</body>" << endl;
  htmlfile << "</html>" << endl;
  htmlfile.close();  
}
