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

void fitWMuMetRayleighGausSimult(const TString  outputDir,   // output directory
           const TString  filetype,		// Select input root files for Nominal, Up, Down and Before Recoil Correction
           const Double_t lumi,        // integrated luminosity (/fb)
	   const Double_t nsigma=0     // vary MET corrections by n-sigmas (nsigma=0 means nominal correction)
)
{
  gBenchmark->Start("fitWMuMetRayleighGausSimult");

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
  fnamev.push_back("../EventSelection/MuonLowPU/Muon_RD_LowPU_AllCorrectionsRD.root"); typev.push_back(eData);
  fnamev.push_back("../EventSelection/MuonLowPU/Muon_DYToMuMu_S8_Analysis.root"); typev.push_back(eEWK);
  fnamev.push_back("../EventSelection/MuonLowPU/Muon_DYToTauTau_S8_Analysis.root"); typev.push_back(eEWK);
  fnamev.push_back("../EventSelection/MuonLowPU/Muon_TTJets_S8_Analysis.root"); typev.push_back(eEWK);
  fnamev.push_back("../EventSelection/MuonLowPU/Muon_WToTauNu_S8_Analysis.root"); typev.push_back(eEWK);
  if (filetype == "Nominal"){
    fnamev.push_back("../EventSelection/MuonLowPU/Muon_WpToMuNu_S8_AllCorrectionsMC.root"); typev.push_back(eWpMuNu);
    fnamev.push_back("../EventSelection/MuonLowPU/Muon_WmToMuNu_S8_AllCorrectionsMC.root"); typev.push_back(eWmMuNu);
  }else if (filetype == "Up"){
    fnamev.push_back("../EventSelection/MuonLowPU/Muon_WpToMuNu_S8_Up_RecoilCorrMC.root"); typev.push_back(eWpMuNu);
    fnamev.push_back("../EventSelection/MuonLowPU/Muon_WmToMuNu_S8_Up_RecoilCorrMC.root"); typev.push_back(eWmMuNu);
  }else if (filetype == "Down"){
    fnamev.push_back("../EventSelection/MuonLowPU/Muon_WpToMuNu_S8_Down_RecoilCorrMC.root"); typev.push_back(eWpMuNu);
    fnamev.push_back("../EventSelection/MuonLowPU/Muon_WmToMuNu_S8_Down_RecoilCorrMC.root"); typev.push_back(eWmMuNu);
  }else if (filetype == "BeforeRC"){
    fnamev.push_back("../EventSelection/MuonLowPU/Muon_WpToMuNu_S8_Analysis.root"); typev.push_back(eWpMuNu);
    fnamev.push_back("../EventSelection/MuonLowPU/Muon_WmToMuNu_S8_Analysis.root"); typev.push_back(eWmMuNu);
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

  TH1D *hQCD_Sig	= new TH1D("hQCD_Sig","hQCD_Sig",13,WptBins);hQCD_Sig->Sumw2();
  TH1D *hQCD_SigPlus	= new TH1D("hQCD_SigPlus","hQCD_SigPlus",13,WptBins);hQCD_SigPlus->Sumw2();
  TH1D *hQCD_SigMinus	= new TH1D("hQCD_SigMinus","hQCD_SigMinus",13,WptBins);hQCD_SigMinus->Sumw2();
  TH1D *hQCD_SigQCDPlus	= new TH1D("hQCD_SigQCDPlus","hQCD_SigQCDPlus",13,WptBins);hQCD_SigQCDPlus->Sumw2();
  TH1D *hQCD_SigQCDMinus= new TH1D("hQCD_SigQCDMinus","hQCD_SigQCDMinus",13,WptBins);hQCD_SigQCDMinus->Sumw2();
  
  TH1D *hAntiQCD_Sig	 = new TH1D("hAntiQCD_Sig","hAntiQCD_Sig",13,WptBins);hAntiQCD_Sig->Sumw2();
  TH1D *hAntiQCD_SigPlus = new TH1D("hAntiQCD_SigPlus","hAntiQCD_SigPlus",13,WptBins);hAntiQCD_SigPlus->Sumw2();
  TH1D *hAntiQCD_SigMinus= new TH1D("hAntiQCD_SigMinus","hAntiQCD_SigMinus",13,WptBins);hAntiQCD_SigMinus->Sumw2();
  
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

  RooFormulaVar* nHighQCD[NWptBinPlus];
  RooFormulaVar* nHighQCDp[NWptBinPlus];
  RooFormulaVar* nHighQCDm[NWptBinPlus];
  
  RooFormulaVar* nAntiHighQCD[NWptBinPlus];
  RooFormulaVar* nAntiHighQCDp[NWptBinPlus];
  RooFormulaVar* nAntiHighQCDm[NWptBinPlus];

  RooRealVar* cqcd[NWptBinPlus];
  RooRealVar* cqcdp[NWptBinPlus];
  RooRealVar* cqcdm[NWptBinPlus];
  
  RooRealVar* dqcd[NWptBinPlus];
  RooRealVar* dqcdp[NWptBinPlus];
  RooRealVar* dqcdm[NWptBinPlus];
  
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
  
  CPepeGaus* qcdGaus[NWptBinPlus];
  CPepeGaus* qcdGausp[NWptBinPlus];
  CPepeGaus* qcdGausm[NWptBinPlus];
  CPepeGaus* aqcdGaus[NWptBinPlus];
  CPepeGaus* aqcdGausp[NWptBinPlus];
  CPepeGaus* aqcdGausm[NWptBinPlus];
  
  RooRealVar* qcdmean[NWptBinPlus];
  RooRealVar* qcdPmean[NWptBinPlus];
  RooRealVar* qcdMmean[NWptBinPlus];
  
  RooRealVar* qcdsigma1[NWptBinPlus];
  RooRealVar* qcdPsigma1[NWptBinPlus];
  RooRealVar* qcdMsigma1[NWptBinPlus];
  
  RooRealVar* qcda1[NWptBinPlus];
  RooRealVar* qcdPa1[NWptBinPlus];
  RooRealVar* qcdMa1[NWptBinPlus];
  
  RooRealVar* qcdsigma2[NWptBinPlus];
  RooRealVar* qcdPsigma2[NWptBinPlus];
  RooRealVar* qcdMsigma2[NWptBinPlus];
  
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
  
  //Merge Bins 10-13
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
  {
    if ( ipt<NBIN_PT_DIVIDER_1and2 ){
      METMAX = METMAX_1;
      NBINS   = NBINS_1;
    } else if ( ipt<NBIN_PT_DIVIDER_2and3 ) {
      METMAX = METMAX_2;
      NBINS   = NBINS_2;
    } else {
      METMAX = METMAX_3;
      NBINS  = NBINS_3;
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

    //High WpT - QCD/Signal ratio
    if (ipt>9){
      sprintf(histName,"cqcd_%d",ipt);
      cqcd[ipt] = new RooRealVar(histName,histName,0.5,0.3,1);
      cqcd[ipt]->setVal(10.3749*TMath::Exp(-(WptBins[ipt-1]+WptBins[ipt])/16.2080)+0.107672);
      cqcd[ipt]->setConstant(kTRUE);
      
      sprintf(histName,"cqcdp_%d",ipt);
      cqcdp[ipt] = new RooRealVar(histName,histName,0.5,0.3,1);
      cqcdp[ipt]->setVal(9.48187*TMath::Exp(-(WptBins[ipt-1]+WptBins[ipt])/16.9649)+0.0072961);
      cqcdp[ipt]->setConstant(kTRUE);
      
      sprintf(histName,"cqcdm_%d",ipt);
      cqcdm[ipt] = new RooRealVar(histName,histName,0.5,0.3,1);
      cqcdm[ipt]->setVal(10.1269*TMath::Exp(-(WptBins[ipt-1]+WptBins[ipt])/16.1065)+0.239577);
      cqcdm[ipt]->setConstant(kTRUE);
      
      sprintf(histName,"dqcd_%d",ipt);
      dqcd[ipt] = new RooRealVar(histName,histName,9,8,10);
      dqcd[ipt]->setVal(10.3749*TMath::Exp(-(WptBins[ipt-1]+WptBins[ipt])/16.2080)+0.107672);
      dqcd[ipt]->setConstant(kTRUE);
      
      sprintf(histName,"dqcdp_%d",ipt);
      dqcdp[ipt] = new RooRealVar(histName,histName,9,8,10);
      dqcdp[ipt]->setVal(9.48187*TMath::Exp(-(WptBins[ipt-1]+WptBins[ipt])/16.9649)+0.0072961);
      dqcdp[ipt]->setConstant(kTRUE);
      
      sprintf(histName,"dqcdm_%d",ipt);
      dqcdm[ipt] = new RooRealVar(histName,histName,9,8,10);
      dqcdm[ipt]->setVal(10.1269*TMath::Exp(-(WptBins[ipt-1]+WptBins[ipt])/16.1065)+0.239577);
      dqcdm[ipt]->setConstant(kTRUE);
      
      sprintf(histName,"nHighQCD_%d",ipt);
      nHighQCD[ipt] = new RooFormulaVar(histName,histName
	  ,"@0*@1",RooArgList(*nSig[ipt],*cqcd[ipt]));
      sprintf(histName,"nHighQCDp_%d",ipt);
      nHighQCDp[ipt] = new RooFormulaVar(histName,histName
	  ,"@0*@1",RooArgList(*nSigp[ipt],*cqcdp[ipt]));
      sprintf(histName,"nHighQCDm_%d",ipt);
      nHighQCDm[ipt] = new RooFormulaVar(histName,histName
	  ,"@0*@1",RooArgList(*nSigm[ipt],*cqcdm[ipt]));
      
      sprintf(histName,"nAntiHighQCD_%d",ipt);
      nAntiHighQCD[ipt] = new RooFormulaVar(histName,histName
	  ,"@0*@1",RooArgList(*nAntiSig[ipt],*dqcd[ipt]));
      sprintf(histName,"nAntiHighQCDp_%d",ipt);
      nAntiHighQCDp[ipt] = new RooFormulaVar(histName,histName
	  ,"@0*@1",RooArgList(*nAntiSigp[ipt],*dqcdp[ipt]));
      sprintf(histName,"nAntiHighQCDm_%d",ipt);
      nAntiHighQCDm[ipt] = new RooFormulaVar(histName,histName
	  ,"@0*@1",RooArgList(*nAntiSigm[ipt],*dqcdm[ipt]));
    }

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
    
    sprintf(histName,"qcdsigma2_%d",ipt);
    qcdsigma2[ipt] = new RooRealVar(histName,histName,25,0,75);
    sprintf(histName,"qcdPsigma2_%d",ipt);
    qcdPsigma2[ipt] = new RooRealVar(histName,histName,25,0,75);
    sprintf(histName,"qcdMsigma2_%d",ipt);
    qcdMsigma2[ipt] = new RooRealVar(histName,histName,25,0,75);
    
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
      nSig[ipt]  -> setVal(93955.6);
      nSigp[ipt] -> setVal(56081.1);
      nSigm[ipt] -> setVal(37862.1);
      nQCD[ipt]  -> setVal(23959.3);
      nQCDp[ipt] -> setVal(12063.2);
      nQCDm[ipt] -> setVal(11901.8);
      nAntiSig[ipt]  -> setVal(1084.4);
      nAntiSigp[ipt] -> setVal(603.958);
      nAntiSigm[ipt] -> setVal(460.015);
      nAntiQCD[ipt]  -> setVal(73736);
      nAntiQCDp[ipt] -> setVal(37214.2);
      nAntiQCDm[ipt] -> setVal(36561.1);
      qcdmean[ipt] ->setVal(0.0433824);
      qcdPmean[ipt]->setVal(6.81479e-08);
      qcdMmean[ipt]->setVal(0.0439352);
      qcdsigma1[ipt] ->setVal(11.2314);
      qcdPsigma1[ipt]->setVal(11.2238);
      qcdMsigma1[ipt]->setVal(11.3034);
      qcda1[ipt] ->setVal(0.151692);
      qcdPa1[ipt]->setVal(0.152213);
      qcdMa1[ipt]->setVal(0.150477);
    }else if (ipt == 1){
      nSig[ipt]  -> setVal(19317.2);
      nSigp[ipt] -> setVal(11788.7);
      nSigm[ipt] -> setVal(7528.61);
      nQCD[ipt]  -> setVal(434.036);
      nQCDp[ipt] -> setVal(217.644);
      nQCDm[ipt] -> setVal(215.528);
      nAntiSig[ipt]  -> setVal(0.00390413);
      nAntiSigp[ipt] -> setVal(3.17852e-05);
      nAntiSigm[ipt] -> setVal(17.6748);
      nAntiQCD[ipt]  -> setVal(1897.98);
      nAntiQCDp[ipt] -> setVal(986.973);
      nAntiQCDm[ipt] -> setVal(890.697);
      qcdmean[ipt] ->setVal(12.4091);
      qcdPmean[ipt]->setVal(12.4233);
      qcdMmean[ipt]->setVal(12.3763);
      qcdsigma1[ipt] ->setVal(7.918);
      qcdPsigma1[ipt]->setVal(7.74745);
      qcdMsigma1[ipt]->setVal(8.59834);
      qcda1[ipt] ->setVal(0.100627);
      qcdPa1[ipt]->setVal(0.111993);
      qcdMa1[ipt]->setVal(0.0536105);
    }else if (ipt == 2){
      nSig[ipt]  -> setVal(19602.8);
      nSigp[ipt] -> setVal(11720);
      nSigm[ipt] -> setVal(7868.83);
      nQCD[ipt]  -> setVal(1200.23);
      nQCDp[ipt] -> setVal(603.226);
      nQCDm[ipt] -> setVal(609.991);
      nAntiSig[ipt]  -> setVal(193.487);
      nAntiSigp[ipt] -> setVal(115.131);
      nAntiSigm[ipt] -> setVal(43.3671);
      nAntiQCD[ipt]  -> setVal(3759.9);
      nAntiQCDp[ipt] -> setVal(1901.58);
      nAntiQCDm[ipt] -> setVal(1898.03);
      qcdmean[ipt] ->setVal(8.15422);
      qcdPmean[ipt]->setVal(8.20312);
      qcdMmean[ipt]->setVal(7.34269);
      qcdsigma1[ipt] ->setVal(5.09747);
      qcdPsigma1[ipt]->setVal(5.15214);
      qcdMsigma1[ipt]->setVal(6.16854);
      qcda1[ipt] ->setVal(0.216424);
      qcdPa1[ipt]->setVal(0.212171);
      qcdMa1[ipt]->setVal(0.199838);
    }else if (ipt == 3){
      nSig[ipt]  -> setVal(15442.9);
      nSigp[ipt] -> setVal(8948.59);
      nSigm[ipt] -> setVal(6143.12);
      nQCD[ipt]  -> setVal(2158.45);
      nQCDp[ipt] -> setVal(1387.99);
      nQCDm[ipt] -> setVal(1123.03);
      nAntiSig[ipt]  -> setVal(183.627);
      nAntiSigp[ipt] -> setVal(3157.36);
      nAntiSigm[ipt] -> setVal(73.8522);
      nAntiQCD[ipt]  -> setVal(6946.56);
      nAntiQCDp[ipt] -> setVal(14.6841);
      nAntiQCDm[ipt] -> setVal(3467.73);
      qcdmean[ipt] ->setVal(3.3687);
      qcdPmean[ipt]->setVal(3.3754);
      qcdMmean[ipt]->setVal(2.41144);
      qcdsigma1[ipt] ->setVal(5.8604);
      qcdPsigma1[ipt]->setVal(5.8529);
      qcdMsigma1[ipt]->setVal(7.55298);
      qcda1[ipt] ->setVal(0.207675);
      qcdPa1[ipt]->setVal(-0.0466868);
      qcdMa1[ipt]->setVal(0.162536);
    }else if (ipt == 4){
      nSig[ipt]  -> setVal(13372.1);
      nSigp[ipt] -> setVal(7889.11);
      nSigm[ipt] -> setVal(5470.44);
      nQCD[ipt]  -> setVal(4277.66);
      nQCDp[ipt] -> setVal(2205.9);
      nQCDm[ipt] -> setVal(2083.94);
      nAntiSig[ipt]  -> setVal(155.298);
      nAntiSigp[ipt] -> setVal(51.6536);
      nAntiSigm[ipt] -> setVal(58.95);
      nAntiQCD[ipt]  -> setVal(13005.9);
      nAntiQCDp[ipt] -> setVal(6633.95);
      nAntiQCDm[ipt] -> setVal(6423.94);
      qcdsigma1[ipt] ->setVal(7.10957);
      qcdPsigma1[ipt]->setVal(1.29358);
      qcdMsigma1[ipt]->setVal(7.59244);
      qcda1[ipt] ->setVal(0.190018);
      qcdPa1[ipt]->setVal(-0.29474);
      qcdMa1[ipt]->setVal(0.224488);
      dFrac1[ipt] ->setVal(0.416812);
      dFrac1P[ipt]->setVal(0.5);
      dFrac1M[ipt]->setVal(0.361108);
      qcdsigma2[ipt] ->setVal(2.93381);
      qcdPsigma2[ipt]->setVal(5.4574);
      qcdMsigma2[ipt]->setVal(5.16394);
      qcda2[ipt] ->setVal(0.2181);
      qcdPa2[ipt]->setVal(0.227878);
      qcdMa2[ipt]->setVal(-0.279923);
      dFrac2[ipt] ->setVal(0.499803);
      dFrac2P[ipt]->setVal(0.5);
      dFrac2M[ipt]->setVal(0.5);
    }else if (ipt == 5){
      nSig[ipt]  -> setVal(7722.92);
      nSigp[ipt] -> setVal(4521.18);
      nSigm[ipt] -> setVal(3200);
      nQCD[ipt]  -> setVal(4773.43);
      nQCDp[ipt] -> setVal(2472.24);
      nQCDm[ipt] -> setVal(2301.82);
      nAntiSig[ipt]  -> setVal(137.096);
      nAntiSigp[ipt] -> setVal(73.3176);
      nAntiSigm[ipt] -> setVal(59.58);
      nAntiQCD[ipt]  -> setVal(13540.9);
      nAntiQCDp[ipt] -> setVal(6841.07);
      nAntiQCDm[ipt] -> setVal(6704.22);
      qcdsigma1[ipt] ->setVal(10.1464);
      qcdPsigma1[ipt]->setVal(9.7071);
      qcdMsigma1[ipt]->setVal(10.6732);
      qcda1[ipt] ->setVal(0.119049);
      qcdPa1[ipt]->setVal(0.143612);
      qcdMa1[ipt]->setVal(0.0902095);
      dFrac1[ipt] ->setVal(0.328792);
      dFrac1P[ipt]->setVal(0.323323);
      dFrac1M[ipt]->setVal(0.33551);
      qcdsigma2[ipt] ->setVal(13.2184);
      qcdPsigma2[ipt]->setVal(13.2453);
      qcdMsigma2[ipt]->setVal(13.2696);
      qcda2[ipt] ->setVal(-0.420206);
      qcdPa2[ipt]->setVal(-0.424466);
      qcdMa2[ipt]->setVal(-0.424278);
      dFrac2[ipt] ->setVal(0.427621);
      dFrac2P[ipt]->setVal(0.416429);
      dFrac2M[ipt]->setVal(0.43703);
    }else if (ipt == 6){
      nSig[ipt]  -> setVal(7481.89);
      nSigp[ipt] -> setVal(4406.52);
      nSigm[ipt] -> setVal(3073.48);
      nQCD[ipt]  -> setVal(5964.87);
      nQCDp[ipt] -> setVal(3041.65);
      nQCDm[ipt] -> setVal(2925.55);
      nAntiSig[ipt]  -> setVal(100.329);
      nAntiSigp[ipt] -> setVal(57.4202);
      nAntiSigm[ipt] -> setVal(40.5866);
      nAntiQCD[ipt]  -> setVal(16240.4);
      nAntiQCDp[ipt] -> setVal(16240.4);
      nAntiQCDm[ipt] -> setVal(16240.4);
      qcdmean[ipt] ->setVal(8.98453);
      qcdPmean[ipt]->setVal(8.92934);
      qcdMmean[ipt]->setVal(8.99328);
      qcdsigma1[ipt] ->setVal(6.4416);
      qcdPsigma1[ipt]->setVal(6.48267);
      qcdMsigma1[ipt]->setVal(6.37924);
      qcda1[ipt] ->setVal(0.184879);
      qcdPa1[ipt]->setVal(0.189067);
      qcdMa1[ipt]->setVal(0.18268);
      qcdsigma2[ipt] ->setVal(22.5051);
      qcdPsigma2[ipt]->setVal(22.7254);
      qcdMsigma1[ipt]->setVal(22.3629);
      qcda2[ipt] ->setVal(-0.519982);
      qcdPa2[ipt]->setVal(-0.532535);
      qcdMa2[ipt]->setVal(-0.50799);
      Frac1[ipt] ->setVal(0.163529);
      Frac1P[ipt]->setVal(0.163529);
      Frac1M[ipt]->setVal(0.163529);
      Frac2[ipt] ->setVal(0.980017);
      Frac2P[ipt]->setVal(0.980017);
      Frac2M[ipt]->setVal(0.980017);
    }else if (ipt == 7){
      nSig[ipt]  -> setVal(3905.23);
      nSigp[ipt] -> setVal(2233.9);
      nSigm[ipt] -> setVal(1636.25);
      nQCD[ipt]  -> setVal(2958.79);
      nQCDp[ipt] -> setVal(1541.5);
      nQCDm[ipt] -> setVal(1457.48);
      nAntiSig[ipt]  -> setVal(88.0062);
      nAntiSigp[ipt] -> setVal(41.8373);
      nAntiSigm[ipt] -> setVal(31.4516);
      nAntiQCD[ipt]  -> setVal(8435.12);
      nAntiQCDp[ipt] -> setVal(8435.12);
      nAntiQCDm[ipt] -> setVal(8435.12);
      qcdmean[ipt] ->setVal(16.2651);
      qcdPmean[ipt]->setVal(16.2057);
      qcdMmean[ipt]->setVal(15.8239);
      qcdsigma1[ipt] ->setVal(8.24266);
      qcdPsigma1[ipt]->setVal(8.53546);
      qcdMsigma1[ipt]->setVal(8.61165);
      qcda1[ipt] ->setVal(0.2739469);
      qcdPa1[ipt]->setVal(0.2282345);
      qcdMa1[ipt]->setVal(0.2386164);
      qcdsigma2[ipt] ->setVal(19.2374);
      qcdPsigma2[ipt]->setVal(35.5464);
      qcdMsigma1[ipt]->setVal(38.8137);
      qcda2[ipt] ->setVal(0.0939384);
      qcdPa2[ipt]->setVal(0.672961);
      qcdMa2[ipt]->setVal(0.722998);
      Frac1[ipt] ->setVal(0.190346);
      Frac1P[ipt]->setVal(0.190346);
      Frac1M[ipt]->setVal(0.190346);
      Frac2[ipt] ->setVal(0.596845);
      Frac2P[ipt]->setVal(0.596845);
      Frac2M[ipt]->setVal(0.596845);
    }else if (ipt == 8){
      nSig[ipt]  -> setVal(4020.74);
      nSigp[ipt] -> setVal(2745.46);
      nSigm[ipt] -> setVal(1653.41);
      nQCD[ipt]  -> setVal(1615.19);
      nQCDp[ipt] -> setVal(317.363);
      nQCDm[ipt] -> setVal(843.082);
      nAntiSig[ipt]  -> setVal(32.383);
      nAntiSigp[ipt] -> setVal(1896.68);
      nAntiSigm[ipt] -> setVal(11.3459);
      nAntiQCD[ipt]  -> setVal(5746.04);
      nAntiQCDp[ipt] -> setVal(5746.04);
      nAntiQCDm[ipt] -> setVal(5746.04);
      qcdmean[ipt] ->setVal(23.0777);
      qcdPmean[ipt]->setVal(23.94626);
      qcdMmean[ipt]->setVal(24.118);
      qcdsigma1[ipt] ->setVal(12.3158);
      qcdPsigma1[ipt]->setVal(12.406042);
      qcdMsigma1[ipt]->setVal(12.3474);
      qcda1[ipt] ->setVal(0.0450212);
      qcdPa1[ipt]->setVal(-0.0356702);
      qcdMa1[ipt]->setVal(0.0158104);
      qcdsigma2[ipt] ->setVal(66.0852);
      qcdPsigma2[ipt]->setVal(61.06379);
      qcdMsigma1[ipt]->setVal(61.0685);
      qcda2[ipt] ->setVal(-1);
      qcdPa2[ipt]->setVal(-0.0478774);
      qcdMa2[ipt]->setVal(-1);
      Frac1[ipt] ->setVal(3.90974e-07);
      Frac1P[ipt]->setVal(3.90974e-07);
      Frac1M[ipt]->setVal(3.90974e-07);
      Frac2[ipt] ->setVal(0.872662);
      Frac2P[ipt]->setVal(0.872662);
      Frac2M[ipt]->setVal(0.872662);
    }else if (ipt == 9){
      nSig[ipt]  -> setVal(2559.61);
      nSigp[ipt] -> setVal(1547.48);
      nSigm[ipt] -> setVal(1005.48);
      nQCD[ipt]  -> setVal(331.375);
      nQCDp[ipt] -> setVal(72.5794);
      nQCDm[ipt] -> setVal(267.816);
      nAntiSig[ipt]  -> setVal(11.6131);
      nAntiSigp[ipt] -> setVal(34.1541);
      nAntiSigm[ipt] -> setVal(4.11246);
      nAntiQCD[ipt]  -> setVal(1201.92);
      nAntiQCDp[ipt] -> setVal(1201.92);
      nAntiQCDm[ipt] -> setVal(1201.92);
      qcdmean[ipt] ->setVal(34.5205);
      qcdPmean[ipt]->setVal(35.0876);
      qcdMmean[ipt]->setVal(36.1307);
      qcdsigma1[ipt] ->setVal(20.3448);
      qcdPsigma1[ipt]->setVal(20.3638);
      qcdMsigma1[ipt]->setVal(22.3416);
      qcda1[ipt] ->setVal(0.0508902);
      qcdPa1[ipt]->setVal(-0.339377);
      qcdMa1[ipt]->setVal(0.032724);
      qcdsigma2[ipt] ->setVal(72.9101);
      qcdPsigma2[ipt]->setVal(27.1249);
      qcdMsigma1[ipt]->setVal(70.5404);
      qcda2[ipt] ->setVal(-0.68057);
      qcdPa2[ipt]->setVal(0.0584);
      qcdMa2[ipt]->setVal(-0.657143);
      Frac1[ipt] ->setVal(0.920378);
      Frac1P[ipt]->setVal(0.920378);
      Frac1M[ipt]->setVal(0.920378);
      Frac2[ipt] ->setVal(0.12721);
      Frac2P[ipt]->setVal(0.12721);
      Frac2M[ipt]->setVal(0.12721);
    }else if (ipt == 10){
      nSig[ipt]  -> setVal(498.978);
      nSigp[ipt] -> setVal(224.77);
      nSigm[ipt] -> setVal(130.846);
      nQCD[ipt]  -> setVal(196.645);
      nQCDp[ipt] -> setVal(182.668);
      nQCDm[ipt] -> setVal(201.083);
      nAntiSig[ipt]  -> setVal(36.6372);
      nAntiSigp[ipt] -> setVal(4.50496e-05);
      nAntiSigm[ipt] -> setVal(6.7521);
      nAntiQCD[ipt]  -> setVal(12.8979);
      nAntiQCDp[ipt] -> setVal(12.8979);
      nAntiQCDm[ipt] -> setVal(12.8979);
      qcdmean[ipt] ->setVal(30.0005302);
      qcdPmean[ipt]->setVal(30);
      qcdMmean[ipt]->setVal(36.6447);
      qcdsigma1[ipt] ->setVal(65.7851);
      qcdPsigma1[ipt]->setVal(53.02015);
      qcdMsigma1[ipt]->setVal(51.41436);
      qcda1[ipt] ->setVal(-0.0564232);
      qcdPa1[ipt]->setVal(-0.15164);
      qcdMa1[ipt]->setVal(-0.0347623);
      qcdsigma2[ipt] ->setVal(0.377904);
      qcdPsigma2[ipt]->setVal(4.9994);
      qcdMsigma1[ipt]->setVal(4.42718);
      qcda2[ipt] ->setVal(0.0232243);
      qcdPa2[ipt]->setVal(-0.0246571);
      qcdMa2[ipt]->setVal(-0.0414784);
      Frac1[ipt] ->setVal(0.999999);
      Frac1P[ipt]->setVal(0.999999);
      Frac1M[ipt]->setVal(0.999999);
      Frac2[ipt] ->setVal(0.999999);
      Frac2P[ipt]->setVal(0.999999);
      Frac2M[ipt]->setVal(0.999999);
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
      aqcd[ipt] =new CPepeModelMean(histName,pfmet,qcd[ipt]->mean, qcd[ipt]->sigma, qcd[ipt]->a1);
      sprintf(histName,"aqcdp_%d",ipt);
      aqcdp[ipt]=new CPepeModelMean(histName,pfmet,qcdp[ipt]->mean,qcdp[ipt]->sigma,qcdp[ipt]->a1);
      sprintf(histName,"aqcdm_%d",ipt);
      aqcdm[ipt]=new CPepeModelMean(histName,pfmet,qcdm[ipt]->mean,qcdm[ipt]->sigma,qcdm[ipt]->a1);
      
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
    }else if (ipt > 5){
      //sprintf(histName,"qcd1_%d",ipt);
      //qcd1[ipt]  = new CPepePlusMod(histName,pfmet);
      //sprintf(histName,"qcd1p_%d",ipt);
      //qcd1p[ipt] = new CPepePlusMod(histName,pfmet);
      //sprintf(histName,"qcd1m_%d",ipt);
      //qcd1m[ipt] = new CPepePlusMod(histName,pfmet);
    
      if (ipt<10){
        sprintf(histName,"qcd1_%d",ipt);
        qcd1[ipt]  = new CPepePlusMod(histName,pfmet,qcdmean[ipt],qcdsigma1[ipt], qcda1[ipt], Frac1[ipt],qcdsigma2[ipt], qcda2[ipt], Frac2[ipt]);
        sprintf(histName,"qcd1p_%d",ipt);
        qcd1p[ipt] = new CPepePlusMod(histName,pfmet,qcdPmean[ipt],qcdPsigma1[ipt], qcdPa1[ipt], Frac1P[ipt],qcdPsigma2[ipt], qcdPa2[ipt], Frac2P[ipt]);
        sprintf(histName,"qcd1m_%d",ipt);
        qcd1m[ipt] = new CPepePlusMod(histName,pfmet,qcdMmean[ipt],qcdMsigma1[ipt], qcdMa1[ipt], Frac1M[ipt],qcdMsigma2[ipt], qcdMa2[ipt], Frac2M[ipt]);
      }else{
	qcdmean[ipt]	->setVal(4.13158);
	qcdsigma1[ipt]	->setVal(74.8178);
	qcda1[ipt]	->setVal(0.00492737);
	qcdsigma2[ipt]	->setVal(74.9993);
	qcda2[ipt]	->setVal(-0.196913);
	Frac1[ipt]	->setVal(0.942329);
	Frac2[ipt]	->setVal(0.166328);
        qcdmean[ipt]	->setConstant(kTRUE);
        qcdsigma1[ipt]	->setConstant(kTRUE);
        qcda1[ipt]	->setConstant(kTRUE);
        qcdsigma2[ipt]	->setConstant(kTRUE);
        qcda2[ipt]	->setConstant(kTRUE);
        Frac1[ipt]	->setConstant(kTRUE);
        Frac2[ipt]	->setConstant(kTRUE);

        sprintf(histName,"qcd1_%d",ipt);
        qcd1[ipt]  = new CPepePlusMod(histName,pfmet,qcdmean[ipt],qcdsigma1[ipt], qcda1[ipt], Frac1[ipt],qcdsigma2[ipt], qcda2[ipt], Frac2[ipt]);
        sprintf(histName,"qcd1p_%d",ipt);
        qcd1p[ipt] = new CPepePlusMod(histName,pfmet,qcdmean[ipt],qcdsigma1[ipt], qcda1[ipt], Frac1[ipt],qcdsigma2[ipt], qcda2[ipt], Frac2[ipt]);
        sprintf(histName,"qcd1m_%d",ipt);
        qcd1m[ipt] = new CPepePlusMod(histName,pfmet,qcdmean[ipt],qcdsigma1[ipt], qcda1[ipt], Frac1[ipt],qcdsigma2[ipt], qcda2[ipt], Frac2[ipt]);
      }
      //sprintf(histName,"aqcd1_%d",ipt);
      //aqcd1[ipt]  = new CPepePlusMod(histName,pfmet,qcdmean[ipt],qcdsigma1[ipt], qcda1[ipt], Frac1[ipt],qcdsigma2[ipt], qcda2[ipt], Frac2[ipt]);
      //sprintf(histName,"aqcd1p_%d",ipt);
      //aqcd1p[ipt] = new CPepePlusMod(histName,pfmet,qcdPmean[ipt],qcdPsigma1[ipt], qcdPa1[ipt], Frac1P[ipt],qcdPsigma2[ipt], qcdPa2[ipt], Frac2P[ipt]);
      //sprintf(histName,"aqcd1m_%d",ipt);
      //aqcd1m[ipt] = new CPepePlusMod(histName,pfmet,qcdMmean[ipt],qcdMsigma1[ipt], qcdMa1[ipt], Frac1M[ipt],qcdMsigma2[ipt], qcdMa2[ipt], Frac2M[ipt]);
      
      sprintf(histName,"aqcd1_%d",ipt);
      aqcd1[ipt] = new CPepePlusMod(histName,pfmet
          ,qcd1[ipt]->m1,qcd1[ipt]->s1,qcd1[ipt]->a1,qcd1[ipt]->f1,qcd1[ipt]->s2,qcd1[ipt]->a2,qcd1[ipt]->f2);
      sprintf(histName,"aqcd1p_%d",ipt);
      aqcd1p[ipt] = new CPepePlusMod(histName,pfmet
          ,qcd1p[ipt]->m1,qcd1p[ipt]->s1,qcd1p[ipt]->a1,qcd1p[ipt]->f1,qcd1p[ipt]->s2,qcd1p[ipt]->a2,qcd1p[ipt]->f2);
      sprintf(histName,"aqcd1m_%d",ipt);
      aqcd1m[ipt] = new CPepePlusMod(histName,pfmet
          ,qcd1m[ipt]->m1,qcd1m[ipt]->s1,qcd1m[ipt]->a1,qcd1m[ipt]->f1,qcd1m[ipt]->s2,qcd1m[ipt]->a2,qcd1m[ipt]->f2);
      
      // Signal + Background PDFs
      if (ipt<10){
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
        
        if(hAntiWmunuMet[ipt]->Integral())
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
        }else if(hAntiEWKMetm[ipt]->Integral() > 0)
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
      }else{
	sprintf(histName,"pdfMet_%d",ipt);
	pdfMet[ipt] =new RooAddPdf(histName,histName
	    ,RooArgList(*pdfWm[ipt],*pdfEWK[ipt],*(qcd1[ipt]->model))
	    ,RooArgList(*nSig[ipt],*nEWK[ipt],*nHighQCD[ipt]));
	sprintf(histName,"pdfMetp_%d",ipt);
	pdfMetp[ipt] =new RooAddPdf(histName,histName
	    ,RooArgList(*pdfWmp[ipt],*pdfEWKp[ipt],*(qcd1p[ipt]->model))
	    ,RooArgList(*nSigp[ipt],*nEWKp[ipt],*nHighQCDp[ipt]));
	sprintf(histName,"pdfMetm_%d",ipt);
	pdfMetm[ipt] =new RooAddPdf(histName,histName
	    ,RooArgList(*pdfWmm[ipt],*pdfEWKm[ipt],*(qcd1m[ipt]->model))
	    ,RooArgList(*nSigm[ipt],*nEWKm[ipt],*nHighQCDm[ipt]));
	
	if(hHighWpTAnti_EWKMet->Integral() > 0)
	{
	  sprintf(histName,"apdfMet_%d",ipt);
	  apdfMet[ipt] =new RooAddPdf(histName,histName
	      ,RooArgList(*apdfWm[ipt],*apdfEWK[ipt],*(aqcd1[ipt]->model))
	      ,RooArgList(*nAntiSig[ipt],*nAntiEWK[ipt],*nAntiHighQCD[ipt]));
	}else if(hHighWpTAnti_EWKMet->Integral() > 0)
	{
	  sprintf(histName,"apdfMet_%d",ipt);
	  apdfMet[ipt] =new RooAddPdf(histName,histName
	      ,RooArgList(*apdfEWK[ipt],*(aqcd1[ipt]->model))
	      ,RooArgList(*nAntiEWK[ipt],*nAntiHighQCD[ipt]));
	  nAntiSig[ipt]->setVal(0);
	}else{
	  printf(histName,"apdfMet_%d",ipt);
	  apdfMet[ipt] =new RooAddPdf(histName,histName
	      ,RooArgList(*(aqcd1[ipt]->model))
	      ,RooArgList(*nAntiHighQCD[ipt]));
	  nAntiSig[ipt]->setVal(0);
	}
	
	if(hHighWpTAnti_EWKMetp->Integral() > 0)
	{
	  sprintf(histName,"apdfMetp_%d",ipt);
	  apdfMetp[ipt] =new RooAddPdf(histName,histName
	      ,RooArgList(*apdfWmp[ipt],*apdfEWKp[ipt],*(aqcd1p[ipt]->model))
	      ,RooArgList(*nAntiSigp[ipt],*nAntiEWKp[ipt],*nAntiHighQCDp[ipt]));
	}else if(hHighWpTAnti_EWKMetp->Integral() > 0)
	{
	  sprintf(histName,"apdfMetp_%d",ipt);
	  apdfMetp[ipt] =new RooAddPdf(histName,histName
	      ,RooArgList(*apdfEWKp[ipt],*(aqcd1p[ipt]->model))
	      ,RooArgList(*nAntiEWKp[ipt],*nAntiHighQCDp[ipt]));
	  nAntiSigp[ipt]->setVal(0);
	}else{
	  sprintf(histName,"apdfMetp_%d",ipt);
	  apdfMetp[ipt] =new RooAddPdf(histName,histName
	      ,RooArgList(*(aqcd1p[ipt]->model))
	      ,RooArgList(*nAntiHighQCDp[ipt]));
	  nAntiSigp[ipt]->setVal(0);
	}
	
	if(hHighWpTAnti_EWKMetm->Integral() > 0)
	{
	  sprintf(histName,"apdfMetm_%d",ipt);
	  apdfMetm[ipt] =new RooAddPdf(histName,histName
	      ,RooArgList(*apdfWmm[ipt],*apdfEWKm[ipt],*(aqcd1m[ipt]->model))
	      ,RooArgList(*nAntiSigm[ipt],*nAntiEWKm[ipt],*nAntiHighQCDm[ipt]));
	}else if(hHighWpTAnti_EWKMetm->Integral() > 0)
	{
	  sprintf(histName,"apdfMetm_%d",ipt);
	  apdfMetm[ipt] =new RooAddPdf(histName,histName
	      ,RooArgList(*apdfEWKm[ipt],*(aqcd1m[ipt]->model))
	      ,RooArgList(*nAntiEWKm[ipt],*nAntiHighQCDm[ipt]));
	  nAntiSigm[ipt]->setVal(0);
	}else{
	  sprintf(histName,"apdfMetm_%d",ipt);
	  apdfMetm[ipt] =new RooAddPdf(histName,histName
	      ,RooArgList(*(aqcd1m[ipt]->model))
	      ,RooArgList(*nAntiHighQCDm[ipt]));
	  nAntiSigm[ipt]->setVal(0);
	}
      }
    }else if (ipt > 3 && ipt < 6){

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
      //sprintf(histName,"aqcd2_%d",ipt);
      //aqcd2[ipt]  = new CPepeDouble(histName,pfmet);
      //sprintf(histName,"aqcd2p_%d",ipt);
      //aqcd2p[ipt] = new CPepeDouble(histName,pfmet);
      //sprintf(histName,"aqcd2m_%d",ipt);
      //aqcd2m[ipt] = new CPepeDouble(histName,pfmet);
      
      sprintf(histName,"aqcd2_%d",ipt);
      aqcd2[ipt] = new CPepeDouble(histName,pfmet
          ,qcd2[ipt]->sigma1,qcd2[ipt]->a1,qcd2[ipt]->frac1,qcd2[ipt]->sigma2,qcd2[ipt]->a2,qcd2[ipt]->frac2);
      sprintf(histName,"aqcd2p_%d",ipt);
      aqcd2p[ipt] = new CPepeDouble(histName,pfmet
          ,qcd2p[ipt]->sigma1,qcd2p[ipt]->a1,qcd2p[ipt]->frac1,qcd2p[ipt]->sigma2,qcd2p[ipt]->a2,qcd2p[ipt]->frac2);
      sprintf(histName,"aqcd2m_%d",ipt);
      aqcd2m[ipt] = new CPepeDouble(histName,pfmet
          ,qcd2m[ipt]->sigma1,qcd2m[ipt]->a1,qcd2m[ipt]->frac1,qcd2m[ipt]->sigma2,qcd2m[ipt]->a2,qcd2m[ipt]->frac2);
      
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

      if(hAntiWmunuMet[ipt]->Integral() > 0)
      {
	sprintf(histName,"apdfMet_%d",ipt);
        apdfMet[ipt] =new RooAddPdf(histName,histName
            ,RooArgList(*apdfWm[ipt],*apdfEWK[ipt],*(aqcd2[ipt]->model))
            ,RooArgList(*nAntiSig[ipt],*nAntiEWK[ipt],*nAntiQCD[ipt]));
      }else if(hAntiEWKMet[ipt]->Integral() > 0)
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

      if(hAntiWmunuMetp[ipt]->Integral() > 0)
      {
        sprintf(histName,"apdfMetp_%d",ipt);
        apdfMetp[ipt] =new RooAddPdf(histName,histName
            ,RooArgList(*apdfWmp[ipt],*apdfEWKp[ipt],*(aqcd2p[ipt]->model))
            ,RooArgList(*nAntiSigp[ipt],*nAntiEWKp[ipt],*nAntiQCDp[ipt]));
      }else if(hAntiEWKMetp[ipt]->Integral() > 0)
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

      if(hAntiWmunuMetm[ipt]->Integral() > 0)
      {
        sprintf(histName,"apdfMetm_%d",ipt);
        apdfMetm[ipt] =new RooAddPdf(histName,histName
            ,RooArgList(*apdfWmm[ipt],*apdfEWKm[ipt],*(aqcd2m[ipt]->model))
            ,RooArgList(*nAntiSigm[ipt],*nAntiEWKm[ipt],*nAntiQCDm[ipt]));
      }else if(hAntiEWKMetm[ipt]->Integral() > 0)
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
    
    // Perform fits
    fitRes[ipt]  = pdfTotal[ipt] ->fitTo(*dataTotal[ipt],Extended(),Minos(kTRUE),Save(kTRUE));
    fitResp[ipt] = pdfTotalp[ipt]->fitTo(*dataTotalp[ipt],Extended(),Minos(kTRUE),Save(kTRUE));
    fitResm[ipt] = pdfTotalm[ipt]->fitTo(*dataTotalm[ipt],Extended(),Minos(kTRUE),Save(kTRUE));
    // Use histogram version of fitted PDFs to make ratio plots
    // (Will also use PDF histograms later for Chi^2 and KS tests)
    hPdfMet = (TH1D*)(pdfMet[ipt]->createHistogram("hPdfMet", pfmet));
    if (ipt>9)
      hPdfMet->Scale(
	  (nSig[ipt]->getVal()+nEWK[ipt]->getVal()+nHighQCD[ipt]->getVal())/hPdfMet->Integral());
    else
      hPdfMet->Scale(
	  (nSig[ipt]->getVal()+nEWK[ipt]->getVal()+nQCD[ipt]->getVal())/hPdfMet->Integral());
    hMetDiff = makeDiffHist(hDataMet[ipt],hPdfMet,"hMetDiff");
    hMetDiff->SetMarkerStyle(kFullCircle);
    hMetDiff->SetMarkerSize(0.9);
     
    hPdfMetp = (TH1D*)(pdfMetp[ipt]->createHistogram("hPdfMetp", pfmet));
    if (ipt>9)
      hPdfMetp->Scale(
	  (nSigp[ipt]->getVal()+nEWKp[ipt]->getVal()+nHighQCDp[ipt]->getVal())/hPdfMetp->Integral());
    else
      hPdfMetp->Scale(
	  (nSigp[ipt]->getVal()+nEWKp[ipt]->getVal()+nQCDp[ipt]->getVal())/hPdfMetp->Integral());
    hMetpDiff = makeDiffHist(hDataMetp[ipt],hPdfMetp,"hMetpDiff");
    hMetpDiff->SetMarkerStyle(kFullCircle);
    hMetpDiff->SetMarkerSize(0.9);
      
    hPdfMetm = (TH1D*)(pdfMetm[ipt]->createHistogram("hPdfMetm", pfmet));
    if (ipt>9)
      hPdfMetm->Scale(
	  (nSigm[ipt]->getVal()+nEWKm[ipt]->getVal()+nHighQCDm[ipt]->getVal())/hPdfMetm->Integral());
    else
      hPdfMetm->Scale(
	  (nSigm[ipt]->getVal()+nEWKm[ipt]->getVal()+nQCDm[ipt]->getVal())/hPdfMetm->Integral());
    hMetmDiff = makeDiffHist(hDataMetm[ipt],hPdfMetm,"hMetmDiff");
    hMetmDiff->SetMarkerStyle(kFullCircle); 
    hMetmDiff->SetMarkerSize(0.9);

    hPdfAntiMet = (TH1D*)(apdfMet[ipt]->createHistogram("hPdfAntiMet", pfmet));
    if (ipt>9)
      hPdfAntiMet->Scale(
	  (nAntiSig[ipt]->getVal()+nAntiEWK[ipt]->getVal()+nAntiHighQCD[ipt]->getVal())/hPdfAntiMet->Integral());
    else
      hPdfAntiMet->Scale(
	  (nAntiSig[ipt]->getVal()+nAntiEWK[ipt]->getVal()+nAntiQCD[ipt]->getVal())/hPdfAntiMet->Integral());
    if (ipt<10)
      hAntiMetDiff = makeDiffHist(hAntiDataMet[ipt],hPdfAntiMet,"hAntiMetDiff");
    else
      hAntiMetDiff = makeDiffHist(hHighWpTAnti_DataMet,hPdfAntiMet,"hAntiMetDiff");
    hAntiMetDiff->SetMarkerStyle(kFullCircle);
    hAntiMetDiff->SetMarkerSize(0.9);
     
    hPdfAntiMetp = (TH1D*)(apdfMetp[ipt]->createHistogram("hPdfAntiMetp", pfmet));
    if (ipt>9)
      hPdfAntiMetp->Scale(
	  (nAntiSigp[ipt]->getVal()+nAntiEWKp[ipt]->getVal()+nAntiHighQCDp[ipt]->getVal())/hPdfAntiMetp->Integral());
    else
      hPdfAntiMetp->Scale(
	  (nAntiSigp[ipt]->getVal()+nAntiEWKp[ipt]->getVal()+nAntiQCDp[ipt]->getVal())/hPdfAntiMetp->Integral());
    if (ipt<10)
      hAntiMetpDiff = makeDiffHist(hAntiDataMetp[ipt],hPdfAntiMetp,"hAntiMetpDiff");
    else
      hAntiMetpDiff = makeDiffHist(hHighWpTAnti_DataMetp,hPdfAntiMetp,"hAntiMetpDiff");
    hAntiMetpDiff->SetMarkerStyle(kFullCircle);
    hAntiMetpDiff->SetMarkerSize(0.9);
      
    hPdfAntiMetm = (TH1D*)(apdfMetm[ipt]->createHistogram("hPdfAntiMetm", pfmet));
    if (ipt>9)
      hPdfAntiMetm->Scale(
	  (nAntiSigm[ipt]->getVal()+nAntiEWKm[ipt]->getVal()+nAntiHighQCDm[ipt]->getVal())/hPdfAntiMetm->Integral());
    else
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
    }else if (ipt > 5){
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
    }else if (ipt > 3 && ipt < 6){
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
      }else if (ipt > 5){
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
      }else if (ipt > 3 && ipt < 6){
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
    
    sprintf(histName,"fitAntiMetLog_%d",ipt);
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
    }else if (ipt > 5){
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
    }else if (ipt > 3 && ipt < 6){
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
      }else if (ipt > 5){
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
      }else if (ipt > 3 && ipt < 6){
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
    
    sprintf(histName,"fitAntiMetPLog_%d",ipt);
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
    }else if (ipt > 5){
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
    }else if (ipt > 3 && ipt < 6){
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
    }else if (ipt > 5){
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
    }else if (ipt > 3 && ipt < 6){
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
    
    sprintf(histName,"fitAntiMetMLog_%d",ipt);
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
    if (ipt>9)
      Wmfile<<"     QCD: "<<nHighQCD[ipt]->getVal()<<" +/- "<<nHighQCD[ipt]->getPropagatedError(*fitRes[ipt])<<endl;
    else
      Wmfile<<"     QCD: "<<nQCD[ipt]->getVal()<<" +/- "<<nQCD[ipt]->getPropagatedError(*fitRes[ipt])<<endl;
    Wmfile<<"   Other: "<<nEWK[ipt]->getVal()<<" +/- "<<nEWK[ipt]->getPropagatedError(*fitRes[ipt])<<endl;
    if (ipt>9)
      Wmfile<<"   Total: "<<nSig[ipt]->getVal()+nHighQCD[ipt]->getVal()+nEWK[ipt]->getVal()<<endl;
    else
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
    if (ipt>9)
      Wmpfile<<"     QCD: "<<nHighQCDp[ipt]->getVal()<<" +/- "<<nHighQCDp[ipt]->getPropagatedError(*fitResp[ipt])<<endl;
    else
      Wmpfile<<"     QCD: "<<nQCDp[ipt]->getVal()<<" +/- "<<nQCDp[ipt]->getPropagatedError(*fitResp[ipt])<<endl;
    Wmpfile<<"   Other: "<<nEWKp[ipt]->getVal()<<" +/- "<<nEWKp[ipt]->getPropagatedError(*fitResp[ipt])<<endl;
    if (ipt>9)
      Wmpfile<<"   Total: "<<nSigp[ipt]->getVal()+nHighQCDp[ipt]->getVal()+nEWKp[ipt]->getVal()<<endl;
    else
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
    if (ipt>9)
      Wmmfile<<"     QCD: "<<nHighQCDm[ipt]->getVal()<<" +/- "<<nHighQCDm[ipt]->getPropagatedError(*fitResm[ipt])<<endl;
    else
      Wmmfile<<"     QCD: "<<nQCDm[ipt]->getVal()<<" +/- "<<nQCDm[ipt]->getPropagatedError(*fitResm[ipt])<<endl;
    Wmmfile<<"   Other: "<<nEWKm[ipt]->getVal()<<" +/- "<<nEWKm[ipt]->getPropagatedError(*fitResm[ipt])<<endl;
    if (ipt>9)
      Wmmfile<<"   Total: "<<nSigm[ipt]->getVal()+nHighQCDm[ipt]->getVal()+nEWKm[ipt]->getVal()<<endl;
    else
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
    if (ipt>9){
      qcdfile<<"Sig="<<nSig[ipt]->getValV()<<"+/-"<<nSig[ipt]->getError()<<"\t SigP="<<nSigp[ipt]->getValV()<<"+/-"<<nSigp[ipt]->getError()<<"\t SigM="<<nSigm[ipt]->getValV()<<"+/-"<<nSigm[ipt]->getError()<<"\t QCD="<<nHighQCD[ipt] ->getValV()<<"\t QCDP="<<nHighQCDp[ipt] ->getValV()<<"\t QCDM="<<nHighQCDm[ipt] ->getValV()<<endl;
      qcdfile<<"cqcd="<<cqcd[ipt]->getVal()<<"\t cqcdp="<<cqcdp[ipt]->getVal()<<"\t cqcdm="<<cqcdm[ipt]->getVal()<<endl;
      qcdfile<<"dqcd="<<dqcd[ipt]->getVal()<<"\t dqcdp="<<dqcdp[ipt]->getVal()<<"\t dqcdm="<<dqcdm[ipt]->getVal()<<endl;
    }else
      qcdfile<<"Sig="<<nSig[ipt]->getValV()<<"+/-"<<nSig[ipt]->getError()<<"\t SigP="<<nSigp[ipt]->getValV()<<"+/-"<<nSigp[ipt]->getError()<<"\t SigM="<<nSigm[ipt]->getValV()<<"+/-"<<nSigm[ipt]->getError()<<"\t QCD="<<nQCD[ipt] ->getValV()<<"+/-"<<nQCD[ipt]->getError()<<"\t QCDP="<<nQCDp[ipt] ->getValV()<<"+/-"<<nQCDp[ipt]->getError()<<"\t QCDM="<<nQCDm[ipt] ->getValV()<<"+/-"<<nQCDm[ipt]->getError()<<endl;
    qcdfile<<"cewk="<<cewk[ipt]->getVal()<<"\t cewkp="<<cewkp[ipt]->getVal()<<"\t cewkm="<<cewkm[ipt]->getVal()<<endl;
    qcdfile<<"Control region: Normalization factors"<<endl;
    if (ipt>9)
      qcdfile <<"AntiSig="<<nAntiSig[ipt]->getValV()<<"\t AntiSigP="<<nAntiSigp[ipt]->getValV()<<"\t AntiSigM="<<nAntiSigm[ipt]->getValV()<<"\t AntiQCD="<<nAntiHighQCD[ipt] ->getValV()<<"\t AntiQCDP="<<nAntiHighQCDp[ipt] ->getValV()<<"\t AntiQCDM="<<nAntiHighQCDm[ipt] ->getValV()<<endl;
    else
      qcdfile <<"AntiSig="<<nAntiSig[ipt]->getValV()<<"\t AntiSigP="<<nAntiSigp[ipt]->getValV()<<"\t AntiSigM="<<nAntiSigm[ipt]->getValV()<<"\t AntiQCD="<<nAntiQCD[ipt] ->getValV()<<"+/-"<<nAntiQCD[ipt] ->getError()<<"\t AntiQCDP="<<nAntiQCDp[ipt] ->getValV()<<"+/-"<<nAntiQCDp[ipt] ->getError()<<"\t AntiQCDM="<<nAntiQCDm[ipt] ->getValV()<<"+/-"<<nAntiQCD[ipt] ->getError()<<endl;
    qcdfile<<"dewk="<<dewk[ipt]->getVal()
     <<"\t dewkp="<<dewkp[ipt]->getVal()<<"\t dewkm="
     <<dewkm[ipt]->getVal()<<endl;

    if (ipt<4){
      qcdfile<<"Signal region: Mod. Rayleigh func. parameters"<<endl;
      qcdfile<<"Mean=" <<qcd[ipt]->mean->getValV()<<" +/- "<<qcd[ipt]->mean->getError()<<"\t Sigma=" <<qcd[ipt] ->sigma->getValV()<<" +/- "<<qcd[ipt]->sigma->getError()<<"\t Sigma1=" <<qcd[ipt]->a1->getValV()<<" +/- "<<qcd[ipt]->a1->getError()<<endl;
      qcdfile<<"MeanP="<<qcdp[ipt]->mean->getValV()<<" +/- "<<qcdp[ipt]->mean->getError()<<"\t SigmaP="<<qcdp[ipt]->sigma->getValV()<<" +/- "<<qcdp[ipt]->sigma->getError()<<"\t Sigma1P="<<qcdp[ipt]->a1->getValV()<<" +/- "<<qcdp[ipt]->a1->getError()<<endl;
      qcdfile<<"MeanM="<<qcdm[ipt]->mean->getValV()<<" +/- "<<qcdm[ipt]->mean->getError()<<"\t SigmaM="<<qcdm[ipt]->sigma->getValV()<<" +/- "<<qcdm[ipt]->sigma->getError()<<"\t Sigma1M="<<qcdm[ipt]->a1->getValV()<<" +/- "<<qcdm[ipt]->a1->getError()<<endl;
    }else if (ipt > 5){
      qcdfile<<"Signal region: Rayleigh+Gauss func. parameters"<<endl;
      qcdfile<<"qcdmean=" <<qcd1[ipt]->m1->getValV()<<" +/- "<<qcd1[ipt]->m1->getError()<<"\t qcdPmean="<<qcd1p[ipt]->m1->getValV()<<" +/- "<<qcd1p[ipt]->m1->getError()<<"\t qcdMmean="<<qcd1m[ipt]->m1->getValV()<<" +/- "<<qcd1m[ipt]->m1->getError()<<endl;
      qcdfile<<"qcdsigma1="<<qcd1[ipt]->s1->getValV()<<" +/- "<<qcd1[ipt]->s1->getError()<<"\t qcdPsigma1="<<qcd1p[ipt]->s1->getValV()<<" +/- "<<qcd1p[ipt]->s1->getError()<<"\t qcdMsigma1="<<qcd1m[ipt]->s1->getValV()<<" +/- "<<qcd1m[ipt]->s1->getError()<<endl;
      qcdfile<<"qcda1="<<qcd1[ipt]->a1->getValV()<<" +/- "<<qcd1[ipt]->a1->getError()<<"\t qcdPa1="<<qcd1p[ipt]->a1->getValV()<<" +/- "<<qcd1p[ipt]->a1->getError()<<"\t qcdMa1="<<qcd1m[ipt]->a1->getValV()<<" +/- "<<qcd1m[ipt]->a1->getError()<<endl;
      qcdfile<<"qcdsigma2="<<qcd1[ipt]->s2->getValV()<<" +/- "<<qcd1[ipt]->s2->getError()<<"\t qcdPsigma2="<<qcd1p[ipt]->s2->getValV()<<" +/- "<<qcd1p[ipt]->s2->getError()<<"\t qcdMsigma2="<<qcd1m[ipt]->s2->getValV()<<" +/- "<<qcd1m[ipt]->s2->getError()<<endl;
      qcdfile<<"qcda2="<<qcd1[ipt]->a2->getValV()<<" +/- "<<qcd1[ipt]->a2->getError()<<"\t qcdPa2="<<qcd1p[ipt]->a2->getValV()<<" +/- "<<qcd1p[ipt]->a2->getError()<<"\t qcdMa2="<<qcd1m[ipt]->a2->getValV()<<" +/- "<<qcd1m[ipt]->a2->getError()<<endl;
      qcdfile<<"Frac1="<<qcd1[ipt]->f1->getValV()<<" +/- "<<qcd1[ipt]->f1->getError()<<"\t\t\t Frac1P="   <<qcd1p[ipt]->f1->getValV()<<" +/- "<<qcd1p[ipt]->f1->getError()<<"\t\t\t Frac1M="<<qcd1m[ipt]->f1->getValV()<<" +/- "<<qcd1m[ipt]->f1->getError()<<endl;
      qcdfile<<"Frac2="<<qcd1[ipt]->f2->getValV()<<" +/- "<<qcd1[ipt]->f2->getError()<<"\t\t\t Frac2P="   <<qcd1p[ipt]->f2->getValV()<<" +/- "<<qcd1p[ipt]->f2->getError()<<"\t\t\t Frac2M="<<qcd1m[ipt]->f2->getValV()<<" +/- "<<qcd1m[ipt]->f2->getError()<<endl;
    }else if (ipt > 3 && ipt < 6){
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
    InValfile<<"nSig[ipt]  -> setVal("<<nSig[ipt] ->getValV()<<");"<<endl;
    InValfile<<"nSigp[ipt] -> setVal("<<nSigp[ipt]->getValV()<<");"<<endl;
    InValfile<<"nSigm[ipt] -> setVal("<<nSigm[ipt]->getValV()<<");"<<endl;
    InValfile<<"nAntiSig[ipt]  -> setVal("<<nAntiSig[ipt] ->getValV()<<");"<<endl;
    InValfile<<"nAntiSigp[ipt] -> setVal("<<nAntiSigp[ipt]->getValV()<<");"<<endl;
    InValfile<<"nAntiSigm[ipt] -> setVal("<<nAntiSigm[ipt]->getValV()<<");"<<endl;
    if (ipt>9){
      InValfile<<"nQCD[ipt]  -> setVal("<<nHighQCD[ipt] ->getValV()<<");"<<endl;
      InValfile<<"nQCDp[ipt] -> setVal("<<nHighQCDp[ipt] ->getValV()<<");"<<endl;
      InValfile<<"nQCDm[ipt] -> setVal("<<nHighQCDm[ipt] ->getValV()<<");"<<endl;
      InValfile<<"nAntiQCD[ipt]  -> setVal("<<nAntiHighQCD[ipt] ->getValV()<<");"<<endl;
      InValfile<<"nAntiQCDp[ipt] -> setVal("<<nAntiHighQCD[ipt] ->getValV()<<");"<<endl;
      InValfile<<"nAntiQCDm[ipt] -> setVal("<<nAntiHighQCD[ipt] ->getValV()<<");"<<endl;
    }else{
      InValfile<<"nQCD[ipt]  -> setVal("<<nQCD[ipt] ->getValV()<<");"<<endl;
      InValfile<<"nQCDp[ipt] -> setVal("<<nQCDp[ipt]->getValV()<<");"<<endl;
      InValfile<<"nQCDm[ipt] -> setVal("<<nQCDm[ipt]->getValV()<<");"<<endl;
      InValfile<<"nAntiQCD[ipt]  -> setVal("<<nAntiQCD[ipt] ->getValV()<<");"<<endl;
      InValfile<<"nAntiQCDp[ipt] -> setVal("<<nAntiQCDp[ipt]->getValV()<<");"<<endl;
      InValfile<<"nAntiQCDm[ipt] -> setVal("<<nAntiQCDm[ipt]->getValV()<<");"<<endl;
    }
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
    }else if (ipt > 5){
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
      InValfile<<"qcdMsigma1[ipt]->setVal("<<qcd1m[ipt]->s2->getValV()<<");"<<endl;
      InValfile<<"qcda2[ipt] ->setVal("<<qcd1[ipt] ->a2->getValV()<<");"<<endl;
      InValfile<<"qcdPa2[ipt]->setVal("<<qcd1p[ipt]->a2->getValV()<<");"<<endl;
      InValfile<<"qcdMa2[ipt]->setVal("<<qcd1m[ipt]->a2->getValV()<<");"<<endl;
      InValfile<<"Frac1[ipt] ->setVal("<<qcd1[ipt] ->f1->getValV()<<");"<<endl;
      InValfile<<"Frac1P[ipt]->setVal("<<qcd1p[ipt]->f1->getValV()<<");"<<endl;
      InValfile<<"Frac1M[ipt]->setVal("<<qcd1m[ipt]->f1->getValV()<<");"<<endl;
      InValfile<<"Frac2[ipt] ->setVal("<<qcd1[ipt] ->f2->getValV()<<");"<<endl;
      InValfile<<"Frac2P[ipt]->setVal("<<qcd1p[ipt]->f2->getValV()<<");"<<endl;
      InValfile<<"Frac2M[ipt]->setVal("<<qcd1m[ipt]->f2->getValV()<<");"<<endl;
      
      InValfile<<"aqcdmean[ipt] ->setVal("<<aqcd1[ipt] ->m1->getValV()<<");"<<endl;
      InValfile<<"aqcdPmean[ipt]->setVal("<<aqcd1p[ipt]->m1->getValV()<<");"<<endl;
      InValfile<<"aqcdMmean[ipt]->setVal("<<aqcd1m[ipt]->m1->getValV()<<");"<<endl;
      InValfile<<"aqcdsigma1[ipt] ->setVal("<<aqcd1[ipt] ->s1->getValV()<<");"<<endl;
      InValfile<<"aqcdPsigma1[ipt]->setVal("<<aqcd1p[ipt]->s1->getValV()<<");"<<endl;
      InValfile<<"aqcdMsigma1[ipt]->setVal("<<aqcd1m[ipt]->s1->getValV()<<");"<<endl;
      InValfile<<"aqcda1[ipt] ->setVal("<<aqcd1[ipt] ->a1->getValV()<<");"<<endl;
      InValfile<<"aqcdPa1[ipt]->setVal("<<aqcd1p[ipt]->a1->getValV()<<");"<<endl;
      InValfile<<"aqcdMa1[ipt]->setVal("<<aqcd1m[ipt]->a1->getValV()<<");"<<endl;
      InValfile<<"aqcdsigma2[ipt] ->setVal("<<aqcd1[ipt] ->s2->getValV()<<");"<<endl;
      InValfile<<"aqcdPsigma2[ipt]->setVal("<<aqcd1p[ipt]->s2->getValV()<<");"<<endl;
      InValfile<<"aqcdMsigma1[ipt]->setVal("<<aqcd1m[ipt]->s2->getValV()<<");"<<endl;
      InValfile<<"aqcda2[ipt] ->setVal("<<aqcd1[ipt] ->a2->getValV()<<");"<<endl;
      InValfile<<"aqcdPa2[ipt]->setVal("<<aqcd1p[ipt]->a2->getValV()<<");"<<endl;
      InValfile<<"aqcdMa2[ipt]->setVal("<<aqcd1m[ipt]->a2->getValV()<<");"<<endl;
      InValfile<<"aFrac1[ipt] ->setVal("<<aqcd1[ipt] ->f1->getValV()<<");"<<endl;
      InValfile<<"aFrac1P[ipt]->setVal("<<aqcd1p[ipt]->f1->getValV()<<");"<<endl;
      InValfile<<"aFrac1M[ipt]->setVal("<<aqcd1m[ipt]->f1->getValV()<<");"<<endl;
      InValfile<<"aFrac2[ipt] ->setVal("<<aqcd1[ipt] ->f2->getValV()<<");"<<endl;
      InValfile<<"aFrac2P[ipt]->setVal("<<aqcd1p[ipt]->f2->getValV()<<");"<<endl;
      InValfile<<"aFrac2M[ipt]->setVal("<<aqcd1m[ipt]->f2->getValV()<<");"<<endl;
    }else if (ipt > 3 && ipt < 6){
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
      InValfile<<"aqcda1[ipt] ->setVal("<<aqcd2[ipt] ->a1->getValV()<<");"<<endl;
      InValfile<<"aqcdPa1[ipt]->setVal("<<aqcd2p[ipt]->a1->getValV()<<");"<<endl;
      InValfile<<"aqcdMa1[ipt]->setVal("<<aqcd2m[ipt]->a1->getValV()<<");"<<endl;
      InValfile<<"adFrac1[ipt] ->setVal("<<aqcd2[ipt] ->frac1->getValV()<<");"<<endl;
      InValfile<<"adFrac1P[ipt]->setVal("<<aqcd2p[ipt]->frac1->getValV()<<");"<<endl;
      InValfile<<"adFrac1M[ipt]->setVal("<<aqcd2m[ipt]->frac1->getValV()<<");"<<endl;
      InValfile<<"aqcdsigma2[ipt] ->setVal("<<aqcd2[ipt] ->sigma2->getValV()<<");"<<endl;
      InValfile<<"aqcdPsigma2[ipt]->setVal("<<aqcd2p[ipt]->sigma2->getValV()<<");"<<endl;
      InValfile<<"aqcdMsigma2[ipt]->setVal("<<aqcd2m[ipt]->sigma2->getValV()<<");"<<endl;
      InValfile<<"aqcda2[ipt] ->setVal("<<aqcd2[ipt] ->a2->getValV()<<");"<<endl;
      InValfile<<"aqcdPa2[ipt]->setVal("<<aqcd2p[ipt]->a2->getValV()<<");"<<endl;
      InValfile<<"aqcdMa2[ipt]->setVal("<<aqcd2m[ipt]->a2->getValV()<<");"<<endl;
      InValfile<<"adFrac2[ipt] ->setVal("<<aqcd2[ipt] ->frac2->getValV()<<");"<<endl;
      InValfile<<"adFrac2P[ipt]->setVal("<<aqcd2p[ipt]->frac2->getValV()<<");"<<endl;
      InValfile<<"adFrac2M[ipt]->setVal("<<aqcd2m[ipt]->frac2->getValV()<<");"<<endl;
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
    metplotsfile<<"<td width=\"200\"><a target=\"_blank\" href=\"fitMet_"<<ipt <<".png\"><img src=\"fitMet_"<<ipt <<".png\" width=\"200\" alt=\"fitMet_"<<ipt <<".png\"></a></td>"<<endl;
    metplotsfile<<"<td width=\"200\"><a target=\"_blank\" href=\"fitMetLog_"<<ipt <<".png\"><img src=\"fitMetLog_"<<ipt <<".png\" width=\"200\" alt=\"fitMetLog_"<<ipt <<".png\"></a></td>"<<endl;
    metplotsfile<<"<td width=\"200\"><a target=\"_blank\" href=\"fitAntiMet_"<<ipt <<".png\"><img src=\"fitAntiMet_"<<ipt <<".png\" width=\"200\" alt=\"fitAntiMet_"<<ipt <<".png\"></a></td>"<<endl;
    metplotsfile<<"<td width=\"200\"><a target=\"_blank\" href=\"fitAntiMetLog_"<<ipt <<".png\"><img src=\"fitAntiMetLog_"<<ipt <<".png\" width=\"200\" alt=\"fitAntiMetLog_"<<ipt <<".png\"></a></td>"<<endl;
    metplotsfile<<"</tr>"<<endl;
    metplotsfile<<"<tr>"<<endl;
    metplotsfile<<"<td width=\"100\"><p align=\"center\" style=\"font-size:small\"> W <sup>+</sup> </p></td>"<<endl;
    metplotsfile<<"<td width=\"200\"><a target=\"_blank\" href=\"fitMetP_"<<ipt <<".png\"><img src=\"fitMetP_"<<ipt <<".png\" width=\"200\" alt=\"fitMetP_"<<ipt <<".png\"></a></td>"<<endl;
    metplotsfile<<"<td width=\"200\"><a target=\"_blank\" href=\"fitMetPLog_"<<ipt <<".png\"><img src=\"fitMetPLog_"<<ipt <<".png\" width=\"200\" alt=\"fitMetPLog_"<<ipt <<".png\"></a></td>"<<endl;
    metplotsfile<<"<td width=\"200\"><a target=\"_blank\" href=\"fitAntiMetP_"<<ipt <<".png\"><img src=\"fitAntiMetP_"<<ipt <<".png\" width=\"200\" alt=\"fitAntiMetP_"<<ipt <<".png\"></a></td>"<<endl;
    metplotsfile<<"<td width=\"200\"><a target=\"_blank\" href=\"fitAntiMetPLog_"<<ipt <<".png\"><img src=\"fitAntiMetPLog_"<<ipt <<".png\" width=\"200\" alt=\"fitAntiMetPLog_"<<ipt <<".png\"></a></td>"<<endl;
    metplotsfile<<"</tr>"<<endl;
    metplotsfile<<"<tr>"<<endl;
    metplotsfile<<"<td width=\"100\"><p align=\"center\" style=\"font-size:small\"> W <sup>-</sup></p></td>"<<endl;
    metplotsfile<<"<td width=\"200\"><a target=\"_blank\" href=\"fitMetM_"<<ipt <<".png\"><img src=\"fitMetM_"<<ipt <<".png\" width=\"200\" alt=\"fitMetM_"<<ipt <<".png\"></a></td>"<<endl;
    metplotsfile<<"<td width=\"200\"><a target=\"_blank\" href=\"fitMetMLog_"<<ipt <<".png\"><img src=\"fitMetMLog_"<<ipt <<".png\" width=\"200\" alt=\"fitMetMLog_"<<ipt <<".png\"></a></td>"<<endl;
    metplotsfile<<"<td width=\"200\"><a target=\"_blank\" href=\"fitAntiMetM_"<<ipt <<".png\"><img src=\"fitAntiMetM_"<<ipt <<".png\" width=\"200\" alt=\"fitAntiMetM_"<<ipt <<".png\"></a></td>"<<endl;
    metplotsfile<<"<td width=\"200\"><a target=\"_blank\" href=\"fitAntiMetMLog_"<<ipt <<".png\"><img src=\"fitAntiMetMLog_"<<ipt <<".png\" width=\"200\" alt=\"fitAntiMetMLog_"<<ipt <<".png\"></a></td>"<<endl;
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
    if (ipt>9)
      tablefile<<"<td width=\"180\"><p>"<< nSig[ipt]->getVal()+nHighQCD[ipt]->getVal()+nEWK[ipt]->getVal()<<" &plusmn; "<<sqrt(nSig[ipt]->getPropagatedError(*fitRes[ipt])*nSig[ipt]->getPropagatedError(*fitRes[ipt])+nHighQCD[ipt]->getPropagatedError(*fitRes[ipt])*nHighQCD[ipt]->getPropagatedError(*fitRes[ipt])+nEWK[ipt]->getPropagatedError(*fitRes[ipt])*nEWK[ipt]->getPropagatedError(*fitRes[ipt]))<<"</p></td>"<<endl;
    else
      tablefile<<"<td width=\"180\"><p>"<< nSig[ipt]->getVal()+nQCD[ipt]->getVal()+nEWK[ipt]->getVal()<<" &plusmn; "<<sqrt(nSig[ipt]->getPropagatedError(*fitRes[ipt])*nSig[ipt]->getPropagatedError(*fitRes[ipt])+nQCD[ipt]->getPropagatedError(*fitRes[ipt])*nQCD[ipt]->getPropagatedError(*fitRes[ipt])+nEWK[ipt]->getPropagatedError(*fitRes[ipt])*nEWK[ipt]->getPropagatedError(*fitRes[ipt]))<<"</p></td>"<<endl;
    tablefile<<"<td width=\"180\"><p>"<< nSig[ipt]->getVal()<<" &plusmn; "<<nSig[ipt]->getPropagatedError(*fitRes[ipt])<<"</p></td>"<<endl;
    if (ipt>9)
      tablefile<<"<td width=\"180\"><p>"<< nHighQCD[ipt]->getVal()<<" &plusmn; "<<nHighQCD[ipt]->getPropagatedError(*fitRes[ipt])<<"</p></td>"<<endl;
    else
      tablefile<<"<td width=\"180\"><p>"<< nQCD[ipt]->getVal()<<" &plusmn; "<<nQCD[ipt]->getPropagatedError(*fitRes[ipt])<<"</p></td>"<<endl;
    tablefile<<"<td width=\"180\"><p>"<< nEWK[ipt]->getVal()<<" &plusmn; "<<nEWK[ipt]->getPropagatedError(*fitRes[ipt])<<"</p></td>"<<endl;
    tablefile<<"</tr>"<<endl;
    tablefile<<"<tr>"<<endl;
    tablefile<<"<td width=\"60\"><p> W <sup>+</sup></p></td>"<<endl;
    tablefile<<"<td width=\"100\"><p>"<< hDataMetp[ipt]->Integral() <<"</p></td>"<<endl;
    if (ipt>9)
      tablefile<<"<td width=\"180\"><p>"<< nSigp[ipt]->getVal()+nHighQCDp[ipt]->getVal()+nEWKp[ipt]->getVal()<<" &plusmn; "<<sqrt(nSigp[ipt]->getPropagatedError(*fitResp[ipt])*nSigp[ipt]->getPropagatedError(*fitResp[ipt])+nHighQCDp[ipt]->getPropagatedError(*fitResp[ipt])*nHighQCDp[ipt]->getPropagatedError(*fitResp[ipt])+nEWKp[ipt]->getPropagatedError(*fitResp[ipt])*nEWKp[ipt]->getPropagatedError(*fitResp[ipt]))<<"</p></td>"<<endl;
    else
      tablefile<<"<td width=\"180\"><p>"<< nSigp[ipt]->getVal()+nQCDp[ipt]->getVal()+nEWKp[ipt]->getVal()<<" &plusmn; "<<sqrt(nSigp[ipt]->getPropagatedError(*fitResp[ipt])*nSigp[ipt]->getPropagatedError(*fitResp[ipt])+nQCDp[ipt]->getPropagatedError(*fitResp[ipt])*nQCDp[ipt]->getPropagatedError(*fitResp[ipt])+nEWKp[ipt]->getPropagatedError(*fitResp[ipt])*nEWKp[ipt]->getPropagatedError(*fitResp[ipt]))<<"</p></td>"<<endl;
    tablefile<<"<td width=\"180\"><p>"<< nSigp[ipt]->getVal()<<" &plusmn; "<<nSigp[ipt]->getPropagatedError(*fitResp[ipt])<<"</p></td>"<<endl;
    if (ipt>9)
      tablefile<<"<td width=\"180\"><p>"<< nHighQCDp[ipt]->getVal()<<" &plusmn; "<<nHighQCDp[ipt]->getPropagatedError(*fitResp[ipt])<<"</p></td>"<<endl;
    else
      tablefile<<"<td width=\"180\"><p>"<< nQCDp[ipt]->getVal()<<" &plusmn; "<<nQCDp[ipt]->getPropagatedError(*fitResp[ipt])<<"</p></td>"<<endl;
    tablefile<<"<td width=\"180\"><p>"<< nEWKp[ipt]->getVal()<<" &plusmn; "<<nEWKp[ipt]->getPropagatedError(*fitResp[ipt])<<"</p></td>"<<endl;
    tablefile<<"</tr>"<<endl;
    tablefile<<"<tr>"<<endl;
    tablefile<<"<td width=\"60\"><p> W <sup>-</sup></p></td>"<<endl;
    tablefile<<"<td width=\"100\"><p>"<< hDataMetm[ipt]->Integral() <<"</p></td>"<<endl;
    if (ipt>9)
      tablefile<<"<td width=\"180\"><p>"<< nSigm[ipt]->getVal()+nHighQCDm[ipt]->getVal()+nEWKm[ipt]->getVal()<<" &plusmn; "<<sqrt(nSigm[ipt]->getPropagatedError(*fitResm[ipt])*nSigm[ipt]->getPropagatedError(*fitResm[ipt])+nHighQCDm[ipt]->getPropagatedError(*fitResm[ipt])*nHighQCDm[ipt]->getPropagatedError(*fitResm[ipt])+nEWKm[ipt]->getPropagatedError(*fitResm[ipt])*nEWKm[ipt]->getPropagatedError(*fitResm[ipt]))<<"</p></td>"<<endl;
    else
      tablefile<<"<td width=\"180\"><p>"<< nSigm[ipt]->getVal()+nQCDm[ipt]->getVal()+nEWKm[ipt]->getVal()<<" &plusmn; "<<sqrt(nSigm[ipt]->getPropagatedError(*fitResm[ipt])*nSigm[ipt]->getPropagatedError(*fitResm[ipt])+nQCDm[ipt]->getPropagatedError(*fitResm[ipt])*nQCDm[ipt]->getPropagatedError(*fitResm[ipt])+nEWKm[ipt]->getPropagatedError(*fitResm[ipt])*nEWKm[ipt]->getPropagatedError(*fitResm[ipt]))<<"</p></td>"<<endl;
    tablefile<<"<td width=\"180\"><p>"<< nSigm[ipt]->getVal()<<" &plusmn; "<<nSigm[ipt]->getPropagatedError(*fitResm[ipt])<<"</p></td>"<<endl;
    if (ipt>9)
      tablefile<<"<td width=\"180\"><p>"<< nHighQCDm[ipt]->getVal()<<" &plusmn; "<<nHighQCDm[ipt]->getPropagatedError(*fitResm[ipt])<<"</p></td>"<<endl;
    else
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
      if (ipt>9){
	hQCDWpt -> SetBinContent(ipt, nHighQCD[ipt]->getVal());
	hQCDWpt -> SetBinError(ipt, nHighQCD[ipt]->getPropagatedError(*fitRes[ipt]));
	hQCDWPpt-> SetBinContent(ipt, nHighQCDp[ipt]->getVal());
	hQCDWPpt-> SetBinError(ipt, nHighQCDp[ipt]->getPropagatedError(*fitResp[ipt]));
	hQCDWMpt-> SetBinContent(ipt, nHighQCDm[ipt]->getVal());
	hQCDWMpt-> SetBinError(ipt, nHighQCDm[ipt]->getPropagatedError(*fitResm[ipt]));
      }else{
	hQCDWpt -> SetBinContent(ipt, nQCD[ipt]->getVal());
	hQCDWpt -> SetBinError(ipt, nQCD[ipt]->getPropagatedError(*fitRes[ipt]));
	hQCDWPpt-> SetBinContent(ipt, nQCDp[ipt]->getVal());
	hQCDWPpt -> SetBinError(ipt, nQCDp[ipt]->getPropagatedError(*fitResp[ipt]));
	hQCDWMpt-> SetBinContent(ipt, nQCDm[ipt]->getVal());
	hQCDWMpt -> SetBinError(ipt, nQCDm[ipt]->getPropagatedError(*fitResm[ipt]));
      }
      
      if (nQCD[ipt]->getVal()==0 || nSig[ipt]->getVal()==0){
	hQCD_Sig-> SetBinContent(ipt, 0);
	hQCD_Sig-> SetBinError(ipt, 0);
      }else{
	hQCD_Sig-> SetBinContent(ipt, nQCD[ipt]->getVal()/nSig[ipt]->getVal());
	double RatioErr=nQCD[ipt]->getVal()/nSig[ipt]->getVal()
	  *sqrt(nQCD[ipt]->getError()*nQCD[ipt]->getError()/(nQCD[ipt]->getVal()*nQCD[ipt]->getVal())
	      +nSig[ipt]->getError()*nSig[ipt]->getError()/(nSig[ipt]->getVal()*nSig[ipt]->getVal()));
	hQCD_Sig-> SetBinError(ipt, RatioErr);
      }

      if (nQCDp[ipt]->getVal()==0 || nSigp[ipt]->getVal()==0){
	hQCD_SigPlus-> SetBinContent(ipt, 0);
	hQCD_SigPlus-> SetBinError(ipt, 0);
      }else{
	hQCD_SigPlus-> SetBinContent(ipt, nQCDp[ipt]->getVal()/nSigp[ipt]->getVal());
	double RatioErrP=nQCDp[ipt]->getVal()/nSigp[ipt]->getVal()
	  *sqrt(nQCDp[ipt]->getError()*nQCDp[ipt]->getError()/(nQCDp[ipt]->getVal()*nQCDp[ipt]->getVal())
	      +nSigp[ipt]->getError()*nSigp[ipt]->getError()/(nSigp[ipt]->getVal()*nSigp[ipt]->getVal()));
	hQCD_SigPlus-> SetBinError(ipt, RatioErrP);
      }
      
      if (nQCDm[ipt]->getVal()==0 || nSigm[ipt]->getVal()==0){
	hQCD_SigMinus-> SetBinContent(ipt, 0);
	hQCD_SigMinus-> SetBinError(ipt, 0);
      }else{
	hQCD_SigMinus-> SetBinContent(ipt, nQCDm[ipt]->getVal()/nSigm[ipt]->getVal());
	double RatioErrM=nQCDm[ipt]->getVal()/nSigm[ipt]->getVal()
	  *sqrt(nQCDm[ipt]->getError()*nQCDm[ipt]->getError()/(nQCDm[ipt]->getVal()*nQCDm[ipt]->getVal())
	      +nSigm[ipt]->getError()*nSigm[ipt]->getError()/(nSigm[ipt]->getVal()*nSigm[ipt]->getVal()));
	hQCD_SigMinus-> SetBinError(ipt, RatioErrM);
      }

      if (nAntiQCD[ipt]->getVal() == 0 || nAntiSig[ipt]->getVal() ==0){
	hAntiQCD_Sig-> SetBinContent(ipt, 0);
	hAntiQCD_Sig-> SetBinError(ipt, 0);
      }else{
	double aRatioIncl = nAntiQCD[ipt]->getVal()/nAntiSig[ipt]->getVal();
	hAntiQCD_Sig-> SetBinContent(ipt, aRatioIncl);
	double antiRatioErr=nAntiQCD[ipt]->getVal()/nAntiSig[ipt]->getVal()
	  *sqrt(nAntiQCD[ipt]->getError()*nAntiQCD[ipt]->getError()/(nAntiQCD[ipt]->getVal()*nAntiQCD[ipt]->getVal())
	      +nAntiSig[ipt]->getError()*nAntiSig[ipt]->getError()/(nAntiSig[ipt]->getVal()*nAntiSig[ipt]->getVal()));
	if (antiRatioErr < aRatioIncl)
	  hAntiQCD_Sig-> SetBinError(ipt, antiRatioErr);
	else
	  hAntiQCD_Sig-> SetBinError(ipt, sqrt(aRatioIncl));
      }

      if (nAntiQCDp[ipt]->getVal()==0 || nAntiSigp[ipt]->getVal()==0){
	hAntiQCD_SigPlus-> SetBinContent(ipt, 0);
	hAntiQCD_SigPlus-> SetBinError(ipt, 0);
      }else{
	double aRatioP = nAntiQCDp[ipt]->getVal()/nAntiSigp[ipt]->getVal();
	hAntiQCD_SigPlus-> SetBinContent(ipt, aRatioP);
	double antiRatioErrP=nAntiQCDp[ipt]->getVal()/nAntiSigp[ipt]->getVal()
	  *sqrt(nAntiQCDp[ipt]->getError()*nAntiQCDp[ipt]->getError()/(nAntiQCDp[ipt]->getVal()*nAntiQCDp[ipt]->getVal())
	      +nAntiSigp[ipt]->getError()*nAntiSigp[ipt]->getError()/(nAntiSigp[ipt]->getVal()*nAntiSigp[ipt]->getVal()));
	if (antiRatioErrP < aRatioP)
	  hAntiQCD_SigPlus-> SetBinError(ipt, antiRatioErrP);
	else
	  hAntiQCD_SigPlus-> SetBinError(ipt, sqrt(aRatioP));
      }

      if (nAntiQCDm[ipt]->getVal()==0 || nAntiSigm[ipt]->getVal()==0){
	hAntiQCD_SigMinus-> SetBinContent(ipt, 0);
	hAntiQCD_SigMinus-> SetBinError(ipt, 0);
      }else{
	double aRatioM = nAntiQCDm[ipt]->getVal()/nAntiSigm[ipt]->getVal();
	hAntiQCD_SigMinus-> SetBinContent(ipt, aRatioM);
	double antiRatioErrM=nAntiQCDm[ipt]->getVal()/nAntiSigm[ipt]->getVal()
	  *sqrt(nAntiQCDm[ipt]->getError()*nAntiQCDm[ipt]->getError()/(nAntiQCDm[ipt]->getVal()*nAntiQCDm[ipt]->getVal())
	      +nAntiSigm[ipt]->getError()*nAntiSigm[ipt]->getError()/(nAntiSigm[ipt]->getVal()*nAntiSigm[ipt]->getVal()));
	if (antiRatioErrM < aRatioM)
	  hAntiQCD_SigMinus-> SetBinError(ipt, antiRatioErrM);
	else
	  hAntiQCD_SigMinus-> SetBinError(ipt, sqrt(aRatioM));
      }
      
      double total = nEventDYToMuMu[ipt]+nEventDYToTauTau[ipt]+nEventTTJets[ipt]+nEventWToTauNu[ipt];
      double totalp = nEventDYToMuMuP[ipt]+nEventDYToTauTauP[ipt]+nEventTTJetsP[ipt]+nEventWToTauNuP[ipt];
      double totalm = nEventDYToMuMuM[ipt]+nEventDYToTauTauM[ipt]+nEventTTJetsM[ipt]+nEventWToTauNuM[ipt];
      hDYToMuMu   -> SetBinContent(ipt,nEWK[ipt]->getVal()*nEventDYToMuMu[ipt]/total);
      hDYToMuMu   -> SetBinError(ipt,nEWK[ipt]->getPropagatedError(*fitRes[ipt])*nEventDYToMuMu[ipt]/total);
      hWToTauNu  -> SetBinContent(ipt,nEWK[ipt]->getVal()*nEventWToTauNu[ipt]/total);
      hWToTauNu  -> SetBinError(ipt,nEWK[ipt]->getPropagatedError(*fitRes[ipt])*nEventWToTauNu[ipt]/total);
      hTTJets     -> SetBinContent(ipt,nEWK[ipt]->getVal()*nEventTTJets[ipt]/total);
      hTTJets     -> SetBinError(ipt,nEWK[ipt]->getPropagatedError(*fitRes[ipt])*nEventTTJets[ipt]/total);
      hDYToTauTau -> SetBinContent(ipt,nEWK[ipt]->getVal()*nEventDYToTauTau[ipt]/total);
      hDYToTauTau -> SetBinError(ipt,nEWK[ipt]->getPropagatedError(*fitRes[ipt])*nEventDYToTauTau[ipt]/total);
      hDYToMuMuP  -> SetBinContent(ipt,nEWKp[ipt]->getVal()*nEventDYToMuMuP[ipt]/totalp);
      hDYToMuMuP  -> SetBinError(ipt,nEWKp[ipt]->getPropagatedError(*fitResp[ipt])*nEventDYToMuMuP[ipt]/totalp);
      hWToTauNuP -> SetBinContent(ipt,nEWKp[ipt]->getVal()*nEventWToTauNuP[ipt]/totalp);
      hWToTauNuP -> SetBinError(ipt,nEWKp[ipt]->getPropagatedError(*fitResp[ipt])*nEventWToTauNuP[ipt]/totalp);
      hTTJetsP    -> SetBinContent(ipt,nEWKp[ipt]->getVal()*nEventTTJetsP[ipt]/totalp);
      hTTJetsP    -> SetBinError(ipt,nEWKp[ipt]->getPropagatedError(*fitResp[ipt])*nEventTTJetsP[ipt]/totalp);
      hDYToTauTauP-> SetBinContent(ipt,nEWKp[ipt]->getVal()*nEventDYToTauTauP[ipt]/totalp);
      hDYToTauTauP-> SetBinError(ipt,nEWKp[ipt]->getPropagatedError(*fitResp[ipt])*nEventDYToTauTauP[ipt]/totalp);
      hDYToMuMuM  -> SetBinContent(ipt,nEWKm[ipt]->getVal()*nEventDYToMuMuM[ipt]/totalm);
      hDYToMuMuM  -> SetBinError(ipt,nEWKm[ipt]->getPropagatedError(*fitResm[ipt])*nEventDYToMuMuM[ipt]/totalm);
      hWToTauNuM -> SetBinContent(ipt,nEWKm[ipt]->getVal()*nEventWToTauNuM[ipt]/totalm);
      hWToTauNuM -> SetBinError(ipt,nEWKm[ipt]->getPropagatedError(*fitResm[ipt])*nEventWToTauNuM[ipt]/totalm);
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
  //gSystem->mkdir(outputDir+"/RstMuon",kTRUE);
  //TString Yields = outputDir+"/RstMuon/SigYields_"+filetype+".root";
  gSystem->mkdir("RstMuon",kTRUE);
  TString Yields = "RstMuon/SigYields_"+filetype+".root";
  TFile *nsigfile = new TFile(Yields,"RECREATE");
  hSigWpt -> Write();
  hSigWPpt-> Write();
  hSigWMpt-> Write();
  hQCD_Sig-> Write();
  hQCD_SigPlus-> Write();
  hQCD_SigMinus-> Write();
  
  hAntiQCD_Sig-> Write();
  hAntiQCD_SigPlus-> Write();
  hAntiQCD_SigMinus-> Write();
  
  //TF1 *fincl = new TF1("fincl","[0]*TMath::Exp(-x/[1])+[2]",40,110);
  //TF1 *fp = new TF1("fp","[0]*TMath::Exp(-x/[1])+[2]",40,110);
  //TF1 *fm = new TF1("fm","[0]*TMath::Exp(-x/[1])+[2]",40,110);
  ////f111->SetParameter(0,1); f111->SetParameter(1,0.3); f111->SetParameter(2,0);
  //fincl->SetParameter(0,0.1); fincl->SetParameter(1,0.3); fincl->SetParameter(2,1);
  //fincl->SetLineColor(kBlue);
  //fp->SetParameter(0,0.1); fp->SetParameter(1,0.3); fp->SetParameter(2,1);
  //fp->SetLineColor(kBlue);
  //fm->SetParameter(0,0.1); fm->SetParameter(1,2.); fm->SetParameter(2,3);
  //fm->SetLineColor(kBlue);

  //hQCD_SigFit->Fit("fincl","L","",40,110);
  //hQCD_SigFit-> Write();
  //hQCD_SigPlusFit->Fit("fp","L","",40,110);
  //hQCD_SigPlusFit-> Write();
  //hQCD_SigMinusFit->Fit("fm","L","",40,110);
  //hQCD_SigMinusFit-> Write();

  //hAntiQCD_SigFit->Fit("f222","L","",40,190);
  //hAntiQCD_SigFit-> Write();
  //hAntiQCD_SigPlusFit->Fit("f222","L","",40,190);
  //hAntiQCD_SigPlusFit-> Write();
  //hAntiQCD_SigMinusFit->Fit("f111","L","",40,110);
  //hAntiQCD_SigMinusFit-> Write();
  //hQCD_SigQCDPlusFit->Fit("f111","L","",40,90);
  //hQCD_SigQCDPlusFit-> Write();
  //hQCD_SigQCDMinusFit->Fit("f111","L","",40,90);
  //hQCD_SigQCDMinusFit-> Write();
  
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

  sprintf(histName,"WMu_pt");
  plotWpt=new CPlot(histName,"","","Events");
  plotWpt->setOutDir(CPlot::sOutDir);
  plotWpt->AddToStack(hDYToTauTau,"Z/#gamma^{*}#rightarrow#tau#tau",kSpring+5,kSpring+3);
  plotWpt->AddToStack(hTTJets,"t#bar{t}",kAzure-5,kAzure-1);
  plotWpt->AddToStack(hWToTauNu,"W#rightarrow#tau#nu",kCyan-9,kCyan-6);
  plotWpt->AddToStack(hDYToMuMu,"Z/#gamma^{*}#rightarrow #mu#mu",fillcolorEWK,linecolorEWK);
  plotWpt->AddToStack(hQCDWpt,"QCD",fillcolorQCD,linecolorQCD);
  plotWpt->AddToStack(hSigWpt,"W#rightarrow #mu#nu",fillcolorW,linecolorW);
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

  sprintf(histName,"WMu_ptLog");
  plotWpt->SetName(histName);
  plotWpt->SetYRange(5e-6*(hWptMC->GetMaximum()),1.4*(hWptMC->GetMaximum()));
  plotWpt->SetLogy();
  plotWpt->Draw(c,kTRUE,format,1);
  
  //double WptBinsLog[14]={0.1,7.5,12.5,17.5,24,30,40,50,70,110,150,190,250,600};
  //double x1,x2,x3,x4,x5,x6,x7,err;
  //TH1D *hDYToTauTauLog = new TH1D("hDYToTauTauLog","",13,WptBinsLog);
  //TH1D *hTTJetsLog = new TH1D("hTTJetsLog","",13,WptBinsLog);
  //TH1D *hWToTauNuLog = new TH1D("hWToTauNuLog","",13,WptBinsLog);
  //TH1D *hDYToMuMuLog = new TH1D("hDYToMuMuLog","",13,WptBinsLog);
  //TH1D *hQCDWptLog = new TH1D("hQCDWptLog","",13,WptBinsLog);
  //TH1D *hSigWptLog = new TH1D("hSigWptLog","",13,WptBinsLog);
  //TH1D *hdataWptLog = new TH1D("hdataWptLog","",13,WptBinsLog);
  //TAxis *xaxis = hSigWpt->GetXaxis();
  //for (int i=1; i<=hSigWpt->GetNbinsX(); i++){
  //  x1=hDYToTauTau->GetBinContent(i);
  //  x2=hTTJets->GetBinContent(i);
  //  x3=hWToTauNu->GetBinContent(i);
  //  x4=hDYToMuMu->GetBinContent(i);
  //  x5=hQCDWpt->GetBinContent(i);
  //  x6=hSigWpt->GetBinContent(i);
  //  x7=hdataWpt->GetBinContent(i);
  //  err = hdataWpt->GetBinError(i);
  //  hDYToTauTauLog->Fill(xaxis->GetBinCenter(i),x1);
  //  hTTJetsLog->Fill(xaxis->GetBinCenter(i),x2);
  //  hWToTauNuLog->Fill(xaxis->GetBinCenter(i),x3);
  //  hDYToMuMuLog->Fill(xaxis->GetBinCenter(i),x4);
  //  hQCDWptLog->Fill(xaxis->GetBinCenter(i),x5);
  //  hSigWptLog->Fill(xaxis->GetBinCenter(i),x6);
  //  hdataWptLog->Fill(xaxis->GetBinCenter(i),x7);
  //  hdataWptLog->SetBinError(i,err);
  //}
  //
  //TH1D* hWptMCLog = (TH1D*)hDYToTauTauLog->Clone("hWptMCLog");
  //hWptMCLog->Add(hTTJetsLog);
  //hWptMCLog->Add(hWToTauNuLog);
  //hWptMCLog->Add(hDYToMuMuLog);
  //hWptMCLog->Add(hQCDWptLog);
  //hWptMCLog->Add(hSigWptLog);
  //hWptDiffLog = makeDiffHistWptLog(hdataWptLog,hWptMCLog,"hWptDiffLog");
  //hWptDiffLog->SetMarkerStyle(kFullCircle);
  //hWptDiffLog->SetMarkerSize(0.9);

  //sprintf(histName,"WMu_ptLog");
  //plotWptLog=new CPlot(histName,"","","Events");
  //plotWptLog->setOutDir(CPlot::sOutDir);
  //plotWptLog->AddToStack(hDYToTauTauLog,"Z/#gamma^{*}#rightarrow#tau#tau",kSpring+5,kSpring+3);
  //plotWptLog->AddToStack(hTTJetsLog,"t#bar{t}",kAzure-5,kAzure-1);
  //plotWptLog->AddToStack(hWToTauNuLog,"W#rightarrow#tau#nu",kCyan-9,kCyan-6);
  //plotWptLog->AddToStack(hDYToMuMuLog,"Z/#gamma^{*}#rightarrow #mu#mu",fillcolorEWK,linecolorEWK);
  //plotWptLog->AddToStack(hQCDWptLog,"QCD",fillcolorQCD,linecolorQCD);
  //plotWptLog->AddToStack(hSigWptLog,"W#rightarrow #mu#nu",fillcolorW,linecolorW);
  //plotWptLog->AddHist1D(hdataWptLog,"Data","E");
  //plotWptLog->SetLegend(0.78,0.65,.98,0.88);
  //plotWptLog->SetYRange(5e-6*(hWptMC->GetMaximum()),1.4*(hWptMC->GetMaximum()));
  //plotWptLog->SetLogx();
  //plotWptLog->SetLogy();
  //plotWptLog->Draw(c,kFALSE,format,1);
  //gPad->RedrawAxis();
  //
  //plotWptDiffLog=new CPlot(histName,"","p_{T} [Gev]","#chi");
  //plotWptDiffLog->setOutDir(CPlot::sOutDir);
  //plotWptDiffLog->AddHist1D(hWptDiffLog,"EX0",ratioColor);
  //plotWptDiffLog->SetYRange(-0.1,0.1);
  //plotWptDiffLog->AddLine(0, 0,600, 0,kBlack,1);
  //plotWptDiffLog->AddLine(0, 0.05,600, 0.05,kBlack,3);
  //plotWptDiffLog->AddLine(0,-0.05,600,-0.05,kBlack,3);
  //plotWptDiffLog->SetLogx();
  //plotWptDiffLog->Draw(c,kTRUE,format,2);

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

  sprintf(histName,"WpMu_pt");
  plotWpt_p=new CPlot(histName,"","","Events");
  plotWpt_p->setOutDir(CPlot::sOutDir);
  plotWpt_p->AddToStack(hDYToTauTauP,"Z/#gamma^{*}#rightarrow#tau#tau",kSpring+5,kSpring+3);
  plotWpt_p->AddToStack(hTTJetsP,"t#bar{t}",kAzure-5,kAzure-1);
  plotWpt_p->AddToStack(hWToTauNuP,"W#rightarrow#tau#nu",kCyan-9,kCyan-6);
  plotWpt_p->AddToStack(hDYToMuMuP,"Z/#gamma^{*}#rightarrow #mu#mu",fillcolorEWK,linecolorEWK);
  plotWpt_p->AddToStack(hQCDWPpt,"QCD",fillcolorQCD,linecolorQCD);
  plotWpt_p->AddToStack(hSigWPpt,"W^{+}#rightarrow #mu^{+}#nu",fillcolorW,linecolorW);
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
  
  sprintf(histName,"WpMu_ptLog");
  plotWpt_p->SetName(histName);
  plotWpt_p->SetYRange(5e-6*(hWptMC_p->GetMaximum()),1.4*(hWptMC_p->GetMaximum()));
  plotWpt_p->SetLogy();
  plotWpt_p->Draw(c,kTRUE,format,1);
  
  //TH1D *hDYToTauTauLogP = new TH1D("hDYToTauTauLogP","",13,WptBinsLog);
  //TH1D *hTTJetsLogP = new TH1D("hTTJetsLogP","",13,WptBinsLog);
  //TH1D *hWToTauNuLogP = new TH1D("hWToTauNuLogP","",13,WptBinsLog);
  //TH1D *hDYToMuMuLogP = new TH1D("hDYToMuMuLogP","",13,WptBinsLog);
  //TH1D *hQCDWptLogP = new TH1D("hQCDWptLogP","",13,WptBinsLog);
  //TH1D *hSigWptLogP = new TH1D("hSigWptLogP","",13,WptBinsLog);
  //TH1D *hdataWptLogP = new TH1D("hdataWptLogP","",13,WptBinsLog);
  //for (int i=1; i<=hSigWPpt->GetNbinsX(); i++){
  //  x1=hDYToTauTauP->GetBinContent(i);
  //  x2=hTTJetsP->GetBinContent(i);
  //  x3=hWToTauNuP->GetBinContent(i);
  //  x4=hDYToMuMuP->GetBinContent(i);
  //  x5=hQCDWPpt->GetBinContent(i);
  //  x6=hSigWPpt->GetBinContent(i);
  //  x7=hdataWPpt->GetBinContent(i);
  //  err = hdataWPpt->GetBinError(i);
  //  hDYToTauTauLogP->Fill(xaxis->GetBinCenter(i),x1);
  //  hTTJetsLogP->Fill(xaxis->GetBinCenter(i),x2);
  //  hWToTauNuLogP->Fill(xaxis->GetBinCenter(i),x3);
  //  hDYToMuMuLogP->Fill(xaxis->GetBinCenter(i),x4);
  //  hQCDWptLogP->Fill(xaxis->GetBinCenter(i),x5);
  //  hSigWptLogP->Fill(xaxis->GetBinCenter(i),x6);
  //  hdataWptLogP->Fill(xaxis->GetBinCenter(i),x7);
  //  hdataWptLogP->SetBinError(i,err);
  //}
  //
  //TH1D* hWPptMCLog = (TH1D*)hDYToTauTauLogP->Clone("hWPptMCLog");
  //hWPptMCLog->Add(hTTJetsLogP);
  //hWPptMCLog->Add(hWToTauNuLogP);
  //hWPptMCLog->Add(hDYToMuMuLogP);
  //hWPptMCLog->Add(hQCDWptLogP);
  //hWPptMCLog->Add(hSigWptLogP);
  //hWPptDiffLog = makeDiffHistWptLog(hdataWptLogP,hWPptMCLog,"hWPptDiffLog");
  //hWPptDiffLog->SetMarkerStyle(kFullCircle);
  //hWPptDiffLog->SetMarkerSize(0.9);
  //
  //sprintf(histName,"WpMu_ptLog");
  //plotWPptLog=new CPlot(histName,"","","Events");
  //plotWPptLog->setOutDir(CPlot::sOutDir);
  //plotWPptLog->AddToStack(hDYToTauTauLogP,"Z/#gamma^{*}#rightarrow#tau#tau",kSpring+5,kSpring+3);
  //plotWPptLog->AddToStack(hTTJetsLogP,"t#bar{t}",kAzure-5,kAzure-1);
  //plotWPptLog->AddToStack(hWToTauNuLogP,"W#rightarrow#tau#nu",kCyan-9,kCyan-6);
  //plotWPptLog->AddToStack(hDYToMuMuLogP,"Z/#gamma^{*}#rightarrow #mu#mu",fillcolorEWK,linecolorEWK);
  //plotWPptLog->AddToStack(hQCDWptLogP,"QCD",fillcolorQCD,linecolorQCD);
  //plotWPptLog->AddToStack(hSigWptLogP,"W^{+}#rightarrow #mu^{+}#nu",fillcolorW,linecolorW);
  //plotWPptLog->AddHist1D(hdataWptLogP,"Data","E");
  //plotWPptLog->SetLegend(0.78,0.65,.98,0.88);
  //plotWPptLog->SetYRange(5e-6*(hWptMC_p->GetMaximum()),1.4*(hWptMC_p->GetMaximum()));
  //plotWPptLog->SetLogx();
  //plotWPptLog->SetLogy();
  //plotWPptLog->Draw(c,kFALSE,format,1);
  //gPad->RedrawAxis();
  //
  //plotWPptDiffLog=new CPlot(histName,"","p_{T} [Gev]","#chi");
  //plotWPptDiffLog->setOutDir(CPlot::sOutDir);
  //plotWPptDiffLog->AddHist1D(hWPptDiffLog,"EX0",ratioColor);
  //plotWPptDiffLog->SetYRange(-0.1,0.1);
  //plotWPptDiffLog->AddLine(0, 0,600, 0,kBlack,1);
  //plotWPptDiffLog->AddLine(0, 0.05,600, 0.05,kBlack,3);
  //plotWPptDiffLog->AddLine(0,-0.05,600,-0.05,kBlack,3);
  //plotWPptDiffLog->SetLogx();
  //plotWPptDiffLog->Draw(c,kTRUE,format,2);

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

  sprintf(histName,"WmMu_pt");
  plotWpt_m=new CPlot(histName,"","","Events");
  plotWpt_m->setOutDir(CPlot::sOutDir);
  plotWpt_m->AddToStack(hDYToTauTauM,"Z/#gamma^{*}#rightarrow#tau#tau",kSpring+5,kSpring+3);
  plotWpt_m->AddToStack(hTTJetsM,"t#bar{t}",kAzure-5,kAzure-1);
  plotWpt_m->AddToStack(hWToTauNuM,"W#rightarrow#tau#nu",kCyan-9,kCyan-6);
  plotWpt_m->AddToStack(hDYToMuMuM,"Z/#gamma^{*}#rightarrow #mu#mu",fillcolorEWK,linecolorEWK);
  plotWpt_m->AddToStack(hQCDWMpt,"QCD",fillcolorQCD,linecolorQCD);
  plotWpt_m->AddToStack(hSigWMpt,"W^{-}#rightarrow #mu^{-}#nu",fillcolorW,linecolorW);
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
  
  sprintf(histName,"WmMu_ptLog");
  plotWpt_m->SetName(histName);
  plotWpt_m->SetYRange(5e-6*(hWptMC_m->GetMaximum()),1.4*(hWptMC_m->GetMaximum()));
  plotWpt_m->SetLogy();
  plotWpt_m->Draw(c,kTRUE,format,1);

  //TH1D *hDYToTauTauLogM = new TH1D("hDYToTauTauLogM","",13,WptBinsLog);
  //TH1D *hTTJetsLogM = new TH1D("hTTJetsLogM","",13,WptBinsLog);
  //TH1D *hWToTauNuLogM = new TH1D("hWToTauNuLogM","",13,WptBinsLog);
  //TH1D *hDYToMuMuLogM = new TH1D("hDYToMuMuLogM","",13,WptBinsLog);
  //TH1D *hQCDWptLogM = new TH1D("hQCDWptLogM","",13,WptBinsLog);
  //TH1D *hSigWptLogM = new TH1D("hSigWptLogM","",13,WptBinsLog);
  //TH1D *hdataWptLogM = new TH1D("hdataWptLogM","",13,WptBinsLog);
  //for (int i=1; i<=hSigWMpt->GetNbinsX(); i++){
  //  x1=hDYToTauTauM->GetBinContent(i);
  //  x2=hTTJetsM->GetBinContent(i);
  //  x3=hWToTauNuM->GetBinContent(i);
  //  x4=hDYToMuMuM->GetBinContent(i);
  //  x5=hQCDWMpt->GetBinContent(i);
  //  x6=hSigWMpt->GetBinContent(i);
  //  x7=hdataWMpt->GetBinContent(i);
  //  err = hdataWMpt->GetBinError(i);
  //  hDYToTauTauLogM->Fill(xaxis->GetBinCenter(i),x1);
  //  hTTJetsLogM->Fill(xaxis->GetBinCenter(i),x2);
  //  hWToTauNuLogM->Fill(xaxis->GetBinCenter(i),x3);
  //  hDYToMuMuLogM->Fill(xaxis->GetBinCenter(i),x4);
  //  hQCDWptLogM->Fill(xaxis->GetBinCenter(i),x5);
  //  hSigWptLogM->Fill(xaxis->GetBinCenter(i),x6);
  //  hdataWptLogM->Fill(xaxis->GetBinCenter(i),x7);
  //  hdataWptLogM->SetBinError(i,err);
  //}
  //
  //TH1D* hWMptMCLog = (TH1D*)hDYToTauTauLogM->Clone("hWMptMCLog");
  //hWMptMCLog->Add(hTTJetsLogM);
  //hWMptMCLog->Add(hWToTauNuLogM);
  //hWMptMCLog->Add(hDYToMuMuLogM);
  //hWMptMCLog->Add(hQCDWptLogM);
  //hWMptMCLog->Add(hSigWptLogM);
  //hWMptDiffLog = makeDiffHistWptLog(hdataWptLogM,hWMptMCLog,"hWMptDiffLog");
  //hWMptDiffLog->SetMarkerStyle(kFullCircle);
  //hWMptDiffLog->SetMarkerSize(0.9);
  //
  //sprintf(histName,"WmMu_ptLog");
  //plotWMptLog=new CPlot(histName,"","","Events");
  //plotWMptLog->setOutDir(CPlot::sOutDir);
  //plotWMptLog->AddToStack(hDYToTauTauLogM,"Z/#gamma^{*}#rightarrow#tau#tau",kSpring+5,kSpring+3);
  //plotWMptLog->AddToStack(hTTJetsLogM,"t#bar{t}",kAzure-5,kAzure-1);
  //plotWMptLog->AddToStack(hWToTauNuLogM,"W#rightarrow#tau#nu",kCyan-9,kCyan-6);
  //plotWMptLog->AddToStack(hDYToMuMuLogM,"Z/#gamma^{*}#rightarrow #mu#mu",fillcolorEWK,linecolorEWK);
  //plotWMptLog->AddToStack(hQCDWptLogM,"QCD",fillcolorQCD,linecolorQCD);
  //plotWMptLog->AddToStack(hSigWptLogM,"W^{-}#rightarrow #mu^{-} #bar{#nu}",fillcolorW,linecolorW);
  //plotWMptLog->AddHist1D(hdataWptLogM,"Data","E");
  //plotWMptLog->SetLegend(0.78,0.65,.98,0.88);
  //plotWMptLog->SetYRange(5e-6*(hWptMC_m->GetMaximum()),1.4*(hWptMC_m->GetMaximum()));
  //plotWMptLog->SetLogx();
  //plotWMptLog->SetLogy();
  //plotWMptLog->Draw(c,kFALSE,format,1);
  //gPad->RedrawAxis();

  //plotWMptDiffLog=new CPlot(histName,"","p_{T} [Gev]","#chi");
  //plotWMptDiffLog->setOutDir(CPlot::sOutDir);
  //plotWMptDiffLog->AddHist1D(hWMptDiffLog,"EX0",ratioColor);
  //plotWMptDiffLog->SetYRange(-0.1,0.1);
  //plotWMptDiffLog->AddLine(0, 0,600, 0,kBlack,1);
  //plotWMptDiffLog->AddLine(0, 0.05,600, 0.05,kBlack,3);
  //plotWMptDiffLog->AddLine(0,-0.05,600,-0.05,kBlack,3);
  //plotWMptDiffLog->SetLogx();
  //plotWMptDiffLog->Draw(c,kTRUE,format,2);
		    
  makeHTML(outputDir);
  gBenchmark->Show("fitWMuMetRayleighGausSimult");
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
  double WptBins[14]={0,7.5,12.5,17.5,24,30,40,50,70,110,150,190,250,600};
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
  htmlfile << "<td width=\"25%\"><a target=\"_blank\" href=\"WMu_pt.png\"><img src=\"WMu_pt.png\" alt=\"WMu_pt.png\" width=\"100%\"></a></td>" << endl;
  htmlfile << "<td width=\"25%\"><a target=\"_blank\" href=\"WpMu_pt.png\"><img src=\"WpMu_pt.png\" alt=\"WpMu_pt.png\" width=\"100%\"></a></td>" << endl;
  htmlfile << "<td width=\"25%\"><a target=\"_blank\" href=\"WmMu_pt.png\"><img src=\"WmMu_pt.png\" alt=\"WmMu_pt.png\" width=\"100%\"></a></td>" << endl;
  htmlfile << "<td width=\"10%\"></td>" << endl;
  htmlfile << "</tr>" << endl;
  htmlfile << "<tr>" << endl;
  htmlfile << "<td width=\"15%\"></td>" << endl;
  htmlfile << "<td width=\"25%\"><a target=\"_blank\" href=\"WMu_ptLog.png\"><img src=\"WMu_ptLog.png\" alt=\"WMu_ptLog.png\" width=\"100%\"></a></td>" << endl;
  htmlfile << "<td width=\"25%\"><a target=\"_blank\" href=\"WpMu_ptLog.png\"><img src=\"WpMu_ptLog.png\" alt=\"WpMu_ptLog.png\" width=\"100%\"></a></td>" << endl;
  htmlfile << "<td width=\"25%\"><a target=\"_blank\" href=\"WmMu_ptLog.png\"><img src=\"WmMu_ptLog.png\" alt=\"WmMu_ptLog.png\" width=\"100%\"></a></td>" << endl;
  htmlfile << "<td width=\"10%\"></td>" << endl;
  htmlfile << "</tr>" << endl;
  htmlfile << "</table>" << endl;
  htmlfile << "<hr />" << endl;
  htmlfile << "</body>" << endl;
  htmlfile << "</html>" << endl;
  htmlfile.close();  
}
