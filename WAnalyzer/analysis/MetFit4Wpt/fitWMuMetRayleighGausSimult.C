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
  //fnamev.push_back("../EventSelection/MuonLowPU/Muon_RD_LowPU_Analysis.root"); typev.push_back(eData);
  fnamev.push_back("../EventSelection/MuonLowPU/Muon_RD_LowPU_AllCorrectionsRD.root"); typev.push_back(eData);
  fnamev.push_back("../EventSelection/MuonLowPU/Muon_DYToMuMu_S8_Analysis.root"); typev.push_back(eEWK);
  fnamev.push_back("../EventSelection/MuonLowPU/Muon_DYToTauTau_S8_Analysis.root"); typev.push_back(eEWK);
  fnamev.push_back("../EventSelection/MuonLowPU/Muon_TTJets_S8_Analysis.root"); typev.push_back(eEWK);
  fnamev.push_back("../EventSelection/MuonLowPU/Muon_WToTauNu_S8_Analysis.root"); typev.push_back(eEWK);
  if (filetype == "Nominal"){
    //fnamev.push_back("../EventSelection/MuonLowPU/Muon_WpToMuNu_S8_RecoilCorrMC.root"); typev.push_back(eWpMuNu);
    //fnamev.push_back("../EventSelection/MuonLowPU/Muon_WmToMuNu_S8_RecoilCorrMC.root"); typev.push_back(eWmMuNu);
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

  TH1D *hSigWpt = new TH1D("hSigWpt","hSigWpt",13,WptBins);hSigWpt->Sumw2();
  TH1D *hSigWPpt = new TH1D("hSigWPpt","hSigWPpt",13,WptBins);hSigWPpt->Sumw2();
  TH1D *hSigWMpt = new TH1D("hSigWMpt","hSigWMpt",13,WptBins);hSigWMpt->Sumw2();
  TH1D *hQCDWpt = new TH1D("hQCDWpt","hQCDWpt",13,WptBins);hQCDWpt->Sumw2();
  TH1D *hQCDWPpt = new TH1D("hQCDWPpt","hQCDWPpt",13,WptBins);hQCDWPpt->Sumw2();
  TH1D *hQCDWMpt = new TH1D("hQCDWMpt","hQCDWMpt",13,WptBins);hQCDWMpt->Sumw2();
  TH1D *hDYToMuMu = new TH1D("hDYToMuMu","hDYToMuMu",13,WptBins);hDYToMuMu->Sumw2();
  TH1D *hDYToMuMuP = new TH1D("hDYToMuMuP","hDYToMuMuP",13,WptBins);hDYToMuMuP->Sumw2();
  TH1D *hDYToMuMuM = new TH1D("hDYToMuMuM","hDYToMuMuM",13,WptBins);hDYToMuMuM->Sumw2();
  TH1D *hWToTauTau = new TH1D("hWToTauTau","hWToTauTau",13,WptBins);hWToTauTau->Sumw2();
  TH1D *hWToTauTauP = new TH1D("hWToTauTauP","hWToTauTauP",13,WptBins);hWToTauTauP->Sumw2();
  TH1D *hWToTauTauM = new TH1D("hWToTauTauM","hWToTauTauM",13,WptBins);hWToTauTauM->Sumw2();
  TH1D *hTTJets = new TH1D("hTTJets","hTTJets",13,WptBins);hTTJets->Sumw2();
  TH1D *hTTJetsP = new TH1D("hTTJetsP","hTTJetsP",13,WptBins);hTTJetsP->Sumw2();
  TH1D *hTTJetsM = new TH1D("hTTJetsM","hTTJetsM",13,WptBins);hTTJetsM->Sumw2();
  TH1D *hDYToTauTau = new TH1D("hDYToTauTau","hDYToTauTau",13,WptBins);hDYToTauTau->Sumw2();
  TH1D *hDYToTauTauP = new TH1D("hDYToTauTauP","hDYToTauTauP",13,WptBins);hDYToTauTauP->Sumw2();
  TH1D *hDYToTauTauM = new TH1D("hDYToTauTauM","hDYToTauTauM",13,WptBins);hDYToTauTauM->Sumw2();



  TH1D *hQCD_SigPlus = new TH1D("hQCD_SigPlus","hQCD_SigPlus",13,WptBins);hQCD_SigPlus->Sumw2();
  TH1D *hQCD_SigMinus = new TH1D("hQCD_SigMinus","hQCD_SigMinus",13,WptBins);hQCD_SigMinus->Sumw2();
  TH1D *hQCD_SigQCDPlus = new TH1D("hQCD_SigQCDPlus","hQCD_SigQCDPlus",13,WptBins);hQCD_SigQCDPlus->Sumw2();
  TH1D *hQCD_SigQCDMinus = new TH1D("hQCD_SigQCDMinus","hQCD_SigQCDMinus",13,WptBins);hQCD_SigQCDMinus->Sumw2();



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
  Double_t gs;
  Double_t gsp;
  Double_t gsm;
  Double_t gm;
  Double_t gmp;
  Double_t gmm;
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
  CPepeModelMean* qcd;
  CPepeModelMean* qcdp;
  CPepeModelMean* qcdm;
  CPepeModelMean* aqcd;
  CPepeModelMean* aqcdp;
  CPepeModelMean* aqcdm;
  CPepeModel1* qcd1;
  CPepeModel1* qcd1p;
  CPepeModel1* qcd1m;
  CPepeModel1* aqcd1;
  CPepeModel1* aqcd1p;
  CPepeModel1* aqcd1m;
  RooAddPdf* pdfqcd;
  RooAddPdf* pdfqcdp;
  RooAddPdf* pdfqcdm;
  RooAddPdf* apdfqcd;
  RooAddPdf* apdfqcdp;
  RooAddPdf* apdfqcdm;

  RooRealVar qcdfrac1("qcdfrac1","qcdfrac1",0.5,0.,1.);
  RooRealVar qcdsigma1("qcdsigma1","qcdsigma1",140,135,150);
  RooRealVar qcdsigma("qcdsigma","qcdsigma",20,15,40);

  RooRealVar* gausMean;
  RooRealVar* gausMean_p;
  RooRealVar* gausMean_m;
  RooRealVar* gausSigma;
  RooRealVar* gausSigma_p;
  RooRealVar* gausSigma_m;
  RooGaussian* QCDGaus;
  RooGaussian* QCDGaus_p;
  RooGaussian* QCDGaus_m;
  RooGaussian* aQCDGaus;
  RooGaussian* aQCDGaus_p;
  RooGaussian* aQCDGaus_m;

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
  qcdfile << " *** QCD Rayleigh Func. shape parameters *** " << endl;

  //Loop for each Wpt bins==============
  // 0 is the total
  for( int ipt(0);ipt<NWptBinPlus;ipt++)
  {
    nSig = new RooRealVar("nSig","nSig",0.7*(hDataMet[ipt]->Integral()),0,hDataMet[ipt]->Integral());
    if (ipt==0){
      nQCD = new RooRealVar("nQCD","nQCD",0.03*(hDataMet[ipt]->Integral()),0,hDataMet[ipt]->Integral());
      nQCDp = new RooRealVar("nQCDp","nQCDp",0.03*(hDataMetp[ipt]->Integral()),0,hDataMetp[ipt]->Integral());
      nQCDm = new RooRealVar("nQCDm","nQCDm",0.03*(hDataMetm[ipt]->Integral()),0,hDataMetm[ipt]->Integral());
    }else if (ipt>0 && ipt<5){
      nQCD = new RooRealVar("nQCD","nQCD",0.007*(hDataMet[ipt]->Integral()),0,hDataMet[ipt]->Integral());
      nQCDp = new RooRealVar("nQCDp","nQCDp",0.003*(hDataMetp[ipt]->Integral()),0,hDataMetp[ipt]->Integral());
      nQCDm = new RooRealVar("nQCDm","nQCDm",0.003*(hDataMetm[ipt]->Integral()),0,hDataMetm[ipt]->Integral());
    }else{
      nQCD = new RooRealVar("nQCD","nQCD",0.3*(hDataMet[ipt]->Integral()),0,hDataMet[ipt]->Integral());
      nQCDp = new RooRealVar("nQCDp","nQCDp",0.3*(hDataMetp[ipt]->Integral()),0,hDataMetp[ipt]->Integral());
      nQCDm = new RooRealVar("nQCDm","nQCDm",0.3*(hDataMetm[ipt]->Integral()),0,hDataMetm[ipt]->Integral());
    }
    
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

  if ( ipt < NBIN_PT_DIVIDER_1and2 ){
    METMAX = METMAX_1;
    NBINS   = NBINS_1;
  }else if ( ipt < NBIN_PT_DIVIDER_2and3 ){
    METMAX = METMAX_2;
    NBINS   = NBINS_2;
  }else{
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
//QCD PDFs Modified Rayleigh
  if (ipt<7){
    qcd =new CPepeModelMean("qcd",pfmet);
    qcdp =new CPepeModelMean("qcdp",pfmet);
    qcdm =new CPepeModelMean("qcdm",pfmet);
    
    aqcd =new CPepeModelMean("aqcd",pfmet, qcd->mean,qcd->sigma,qcd->a1);
    aqcdp=new CPepeModelMean("aqcdp",pfmet,qcdp->mean,qcdp->sigma,qcdp->a1);
    aqcdm=new CPepeModelMean("aqcdm",pfmet,qcdm->mean,qcdm->sigma,qcdm->a1);
  }else if (ipt>6 && ipt<10){
//Rayleigh+frac*Gaussian
    qcd1 =new CPepeModel1("qcd1",pfmet);
    qcd1p =new CPepeModel1("qcd1p",pfmet);
    qcd1m =new CPepeModel1("qcd1m",pfmet);

    gausSigma   = new RooRealVar("gausSigma","Gaussian Sigma",20,0,METMAX);
    gausSigma_p = new RooRealVar("gausSigma_p","Gaussian Sigma",25,0,METMAX);
    gausSigma_m = new RooRealVar("gausSigma_m","Gaussian Sigma",25,0,METMAX);
    gausMean    = new RooRealVar("gausMean","Gaussian Mean",15,0,METMAX);
    gausMean_p  = new RooRealVar("gausMean_p","Gaussian Mean",15,0,METMAX);
    gausMean_m  = new RooRealVar("gausMean_m","Gaussian Mean",15,0,METMAX);
    if (ipt==7){
      gausSigma_m = new RooRealVar("gausSigma_m","Gaussian Sigma",25,0,METMAX);
      gausMean_m  = new RooRealVar("gausMean_m","Gaussian Mean",20,0,METMAX);
      Double_t gs = gausSigma_m->getValV();
      Double_t gm = gausMean_m->getValV();
      gausSigma   = new RooRealVar("gausSigma","Gaussian Sigma",gs,0,METMAX);
      gausSigma_p = new RooRealVar("gausSigma_p","Gaussian Sigma",gs,0,METMAX);
      gausMean    = new RooRealVar("gausMean","Gaussian Mean",gm,0,METMAX);
      gausMean_p  = new RooRealVar("gausMean_p","Gaussian Mean",gm,0,METMAX);
    }else if(ipt==9){
      qcd1 =new CPepeModel1("qcd1",pfmet,&qcdsigma);
      qcd1p =new CPepeModel1("qcd1p",pfmet,&qcdsigma);
      qcd1m =new CPepeModel1("qcd1m",pfmet,&qcdsigma);
      gausSigma   = new RooRealVar("gausSigma","Gaussian Sigma",25,5,50);
      gausSigma_p = new RooRealVar("gausSigma_p","Gaussian Sigma",25,5,50);
      gausSigma_m = new RooRealVar("gausSigma_m","Gaussian Sigma",25,10,50);
      gausMean    = new RooRealVar("gausMean","Gaussian Mean",15,5,50);
      gausMean_p  = new RooRealVar("gausMean_p","Gaussian Mean",15,5,50);
      gausMean_m  = new RooRealVar("gausMean_m","Gaussian Mean",15,5,50);
    }
    aqcd1 =new CPepeModel1("aqcd1",pfmet,qcd1->sigma,qcd1->a1);
    aqcd1p=new CPepeModel1("aqcd1p",pfmet,qcd1p->sigma,qcd1p->a1);
    aqcd1m=new CPepeModel1("aqcd1m",pfmet,qcd1m->sigma,qcd1m->a1);

    QCDGaus	= new RooGaussian("QCDGaus","Gaussian PDF",pfmet,*gausMean,*gausSigma);
    QCDGaus_p	= new RooGaussian("QCDGaus_p","Gaussian PDF",pfmet,*gausMean_p,*gausSigma_p);
    QCDGaus_m	= new RooGaussian("QCDGaus_m","Gaussian PDF",pfmet,*gausMean_m,*gausSigma_m);
    
    aQCDGaus	= new RooGaussian("aQCDGaus","Gaussian PDF",pfmet,*gausMean,*gausSigma);
    aQCDGaus_p	= new RooGaussian("aQCDGaus_p","Gaussian PDF",pfmet,*gausMean_p,*gausSigma_p);
    aQCDGaus_m	= new RooGaussian("aQCDGaus_m","Gaussian PDF",pfmet,*gausMean_m,*gausSigma_m);
  }else if (ipt==10 || ipt==11){
//Rayleigh func.
    qcd1 =new CPepeModel1("qcd1",pfmet,&qcdsigma1);
    qcd1p =new CPepeModel1("qcd1p",pfmet,&qcdsigma1);
    qcd1m =new CPepeModel1("qcd1m",pfmet,&qcdsigma1);
    aqcd1 =new CPepeModel1("aqcd1",pfmet,qcd1->sigma,qcd1->a1);
    aqcd1p =new CPepeModel1("qcd1p",pfmet,qcd1p->sigma,qcd1p->a1);
    aqcd1m =new CPepeModel1("qcd1m",pfmet,qcd1m->sigma,qcd1m->a1);
  }else{
    qcd1 =new CPepeModel1("qcd1",pfmet,&qcdsigma1);
    qcd1->sigma->getValV();
    qcd1->sigma->setConstant(kTRUE);
    qcd1->a1->getValV();
    qcd1->a1->setConstant(kTRUE);
    qcd1p =new CPepeModel1("qcd1p",pfmet,&qcdsigma1);
    qcd1p->sigma->getValV();
    qcd1p->sigma->setConstant(kTRUE);
    qcd1p->a1->getValV();
    qcd1p->a1->setConstant(kTRUE);
    qcd1m =new CPepeModel1("qcd1m",pfmet,&qcdsigma1);
    qcd1m->sigma->getValV();
    qcd1m->sigma->setConstant(kTRUE);
    qcd1m->a1->getValV();
    qcd1m->a1->setConstant(kTRUE);
    aqcd1 =new CPepeModel1("aqcd1",pfmet,qcd1->sigma,qcd1->a1);
    aqcd1->sigma->setVal(qcd1->sigma->getValV());
    aqcd1->sigma->setConstant(kTRUE);
    aqcd1->a1->setVal(qcd1->a1->getValV());
    aqcd1->a1->setConstant(kTRUE);
    aqcd1p =new CPepeModel1("qcd1p",pfmet,qcd1p->sigma,qcd1p->a1);
    aqcd1p->sigma->setVal(qcd1p->sigma->getValV());
    aqcd1p->sigma->setConstant(kTRUE);
    aqcd1p->a1->setVal(qcd1p->a1->getValV());
    aqcd1p->a1->setConstant(kTRUE);
    aqcd1m =new CPepeModel1("qcd1m",pfmet,qcd1m->sigma,qcd1m->a1);
    aqcd1m->sigma->setVal(qcd1m->sigma->getValV());
    aqcd1m->sigma->setConstant(kTRUE);
    aqcd1m->a1->setVal(qcd1m->a1->getValV());
    aqcd1m->a1->setConstant(kTRUE);
  }
  // Signal + Background PDFs
  if (ipt<7){
    pdfMet =new RooAddPdf("pdfMet", "pdfMet", RooArgList(*pdfWm, *pdfEWK, *(qcd->model)), RooArgList(*nSig, *nEWK, *nQCD));
    pdfMetp=new RooAddPdf("pdfMetp","pdfMetp",RooArgList(*pdfWmp,*pdfEWKp,*(qcdp->model)),RooArgList(*nSigp,*nEWKp,*nQCDp));
    pdfMetm=new RooAddPdf("pdfMetm","pdfMetm",RooArgList(*pdfWmm,*pdfEWKm,*(qcdm->model)),RooArgList(*nSigm,*nEWKm,*nQCDm));
    
    apdfMet =new RooAddPdf("apdfMet", "apdfMet", RooArgList(*apdfWm,*apdfEWK,*(aqcd->model)),   RooArgList(*nAntiSig,*nAntiEWK,*nAntiQCD));
    apdfMetp=new RooAddPdf("apdfMetp","apdfMetp",RooArgList(*apdfWmp,*apdfEWKp,*(aqcdp->model)),RooArgList(*nAntiSigp,*nAntiEWKp,*nAntiQCDp));
    apdfMetm=new RooAddPdf("apdfMetm","apdfMetm",RooArgList(*apdfWmm,*apdfEWKm,*(aqcdm->model)),RooArgList(*nAntiSigm,*nAntiEWKm,*nAntiQCDm));
  }else if (ipt>6 && ipt<10){
    pdfqcd = new RooAddPdf("pdfqcd","pdfqcd",RooArgList(*(qcd1->model),*QCDGaus),qcdfrac1);
    pdfqcdp = new RooAddPdf("pdfqcdp","pdfqcdp",RooArgList(*(qcd1p->model),*QCDGaus_p),qcdfrac1);
    pdfqcdm = new RooAddPdf("pdfqcdm","pdfqcdm",RooArgList(*(qcd1m->model),*QCDGaus_m),qcdfrac1);

    pdfMet =new RooAddPdf("pdfMet", "pdfMet", RooArgList(*pdfWm,*pdfEWK,*pdfqcd),   RooArgList(*nSig,*nEWK,*nQCD));
    pdfMetp=new RooAddPdf("pdfMetp","pdfMetp",RooArgList(*pdfWmp,*pdfEWKp,*pdfqcdp),RooArgList(*nSigp,*nEWKp,*nQCDp));
    pdfMetm=new RooAddPdf("pdfMetm","pdfMetm",RooArgList(*pdfWmm,*pdfEWKm,*pdfqcdm),RooArgList(*nSigm,*nEWKm,*nQCDm));

    apdfqcd = new RooAddPdf("apdfqcd","apdfqcd",RooArgList(*(aqcd1->model),*aQCDGaus),qcdfrac1);
    apdfqcdp = new RooAddPdf("apdfqcdp","apdfqcdp",RooArgList(*(aqcd1p->model),*aQCDGaus_p),qcdfrac1);
    apdfqcdm = new RooAddPdf("apdfqcdm","apdfqcdm",RooArgList(*(aqcd1m->model),*aQCDGaus_m),qcdfrac1);

    apdfMet =new RooAddPdf("apdfMet", "apdfMet", RooArgList(*apdfWm,*apdfEWK,*apdfqcd),   RooArgList(*nAntiSig,*nAntiEWK,*nAntiQCD));
    apdfMetp=new RooAddPdf("apdfMetp","apdfMetp",RooArgList(*apdfWmp,*apdfEWKp,*apdfqcdp),RooArgList(*nAntiSigp,*nAntiEWKp,*nAntiQCDp));
    apdfMetm=new RooAddPdf("apdfMetm","apdfMetm",RooArgList(*apdfWmm,*apdfEWKm,*apdfqcdm),RooArgList(*nAntiSigm,*nAntiEWKm,*nAntiQCDm));
  }else{
    pdfMet =new RooAddPdf("pdfMet", "pdfMet", RooArgList(*pdfWm,*pdfEWK,*(qcd1->model)),   RooArgList(*nSig,*nEWK,*nQCD));
    pdfMetp=new RooAddPdf("pdfMetp","pdfMetp",RooArgList(*pdfWmp,*pdfEWKp,*(qcd1p->model)),RooArgList(*nSigp,*nEWKp,*nQCDp));
    pdfMetm=new RooAddPdf("pdfMetm","pdfMetm",RooArgList(*pdfWmm,*pdfEWKm,*(qcd1m->model)),RooArgList(*nSigm,*nEWKm,*nQCDm));
    apdfMet =new RooAddPdf("apdfMet", "apdfMet", RooArgList(*apdfWm,*apdfEWK,*(aqcd1->model)),   RooArgList(*nAntiSig,*nAntiEWK,*nAntiQCD));
    apdfMetp=new RooAddPdf("apdfMetp","apdfMetp",RooArgList(*apdfWmp,*apdfEWKp,*(aqcd1p->model)),RooArgList(*nAntiSigp,*nAntiEWKp,*nAntiQCDp));
    apdfMetm=new RooAddPdf("apdfMetm","apdfMetm",RooArgList(*apdfWmm,*apdfEWKm,*(aqcd1m->model)),RooArgList(*nAntiSigm,*nAntiEWKm,*nAntiQCDm));
  }
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
  if (ipt<11) {
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
      
      pdfWmunu0Met	= new RooAddPdf("pdfWmunu0Met", "pdfWmunu0Met", RooArgList(*pdfWm),RooArgList(*nSig));
      pdfWmunu0Metp	= new RooAddPdf("pdfWmunu0Metp","pdfWmunu0Metp",RooArgList(*pdfWmp),RooArgList(*nSigp));
      pdfWmunu0Metm	= new RooAddPdf("pdfWmunu0Metm","pdfWmunu0Metm",RooArgList(*pdfWmm),RooArgList(*nSigm));
      
      pdfEWK0Met	= new RooAddPdf("pdfEWK0Met", "pdfEWK0Met", RooArgList(*pdfEWK),RooArgList(*nEWK));
      pdfEWK0Metp	= new RooAddPdf("pdfEWK0Metp","pdfEWK0Metp",RooArgList(*pdfEWKp),RooArgList(*nEWKp));
      pdfEWK0Metm	= new RooAddPdf("pdfEWK0Metm","pdfEWK0Metm",RooArgList(*pdfEWKm),RooArgList(*nEWKm));
      
      pdfQCD0Met	= new RooAddPdf("pdfQCD0Met", "pdfQCD0Met", RooArgList(*(qcd->model)),RooArgList(*nQCD));
      pdfQCD0Metp	= new RooAddPdf("pdfQCD0Metp","pdfQCD0Metp",RooArgList(*(qcdp->model)),RooArgList(*nQCDp));
      pdfQCD0Metm	= new RooAddPdf("pdfQCD0Metm","pdfQCD0Metm",RooArgList(*(qcdm->model)),RooArgList(*nQCDm));
      
      hWmunu0 = (TH1D*)(pdfWmunu0Met->createHistogram("hWmunu0", pfmet));
      hWmunu0->Scale((nSig->getVal())/hWmunu0->Integral());
      hWmunu0p = (TH1D*)(pdfWmunu0Metp->createHistogram("hWmunu0p", pfmet));
      hWmunu0p->Scale((nSigp->getVal())/hWmunu0p->Integral());
      hWmunu0m = (TH1D*)(pdfWmunu0Metm->createHistogram("hWmunu0m", pfmet));
      hWmunu0m->Scale((nSigm->getVal())/hWmunu0m->Integral());
      
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
  if (ipt<7){
    pdfMet->plotOn(wmframe,Components(RooArgSet(*pdfEWK,*(qcd->model))),FillColor(fillcolorEWK),DrawOption("F"));
    pdfMet->plotOn(wmframe,Components(RooArgSet(*pdfEWK,*(qcd->model))),LineColor(linecolorEWK));
    pdfMet->plotOn(wmframe,Components(RooArgSet(*(qcd->model))),FillColor(fillcolorQCD),DrawOption("F"));
    pdfMet->plotOn(wmframe,Components(RooArgSet(*(qcd->model))),LineColor(linecolorQCD));
  }else if (ipt>6 && ipt<10){
    pdfMet->plotOn(wmframe,Components(RooArgSet(*pdfEWK,*pdfqcd)),FillColor(fillcolorEWK),DrawOption("F"));
    pdfMet->plotOn(wmframe,Components(RooArgSet(*pdfEWK,*pdfqcd)),LineColor(linecolorEWK));
    pdfMet->plotOn(wmframe,Components(RooArgSet(*pdfqcd)),FillColor(fillcolorQCD),DrawOption("F"));
    pdfMet->plotOn(wmframe,Components(RooArgSet(*pdfqcd)),LineColor(linecolorQCD));
  }else{
    pdfMet->plotOn(wmframe,Components(RooArgSet(*pdfEWK,*(qcd1->model))),FillColor(fillcolorEWK),DrawOption("F"));
    pdfMet->plotOn(wmframe,Components(RooArgSet(*pdfEWK,*(qcd1->model))),LineColor(linecolorEWK));
    pdfMet->plotOn(wmframe,Components(RooArgSet(*(qcd1->model))),FillColor(fillcolorQCD),DrawOption("F"));
    pdfMet->plotOn(wmframe,Components(RooArgSet(*(qcd1->model))),LineColor(linecolorQCD));
  }
  pdfMet->plotOn(wmframe,Components(RooArgSet(*pdfWm)),LineColor(linecolorW),LineStyle(2));
  dataMet->plotOn(wmframe,MarkerStyle(kFullCircle),MarkerSize(0.9),DrawOption("ZP"));  
  
  sprintf(ylabel,"Events / %.1f GeV",hDataMet[ipt]->GetBinWidth(1));
  sprintf(histName,"fitMet_%d",ipt);
  plotMet=new CPlot(histName,wmframe,"","",ylabel);
  plotMet->setOutDir(CPlot::sOutDir);
  plotMet->SetLegend(0.68,0.57,0.93,0.77);
  plotMet->GetLegend()->AddEntry(hDummyData,"data","PL");
  plotMet->GetLegend()->AddEntry(hDummyW,"W#rightarrow#mu#nu","F");
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

  if ( ipt < 11 ){
    awmframe = pfmet.frame(Bins(NBINS));
    antiMet->plotOn(awmframe,MarkerStyle(kFullCircle),MarkerSize(0.9),DrawOption("ZP"));
    apdfMet->plotOn(awmframe,FillColor(fillcolorW),DrawOption("F"));
    apdfMet->plotOn(awmframe,LineColor(linecolorW));
    if (ipt<7){
      apdfMet->plotOn(awmframe,Components(RooArgSet(*apdfEWK,*(aqcd->model))),FillColor(fillcolorEWK),DrawOption("F"));
      apdfMet->plotOn(awmframe,Components(RooArgSet(*apdfEWK,*(aqcd->model))),LineColor(linecolorEWK));
      apdfMet->plotOn(awmframe,Components(RooArgSet(*(aqcd->model))),FillColor(fillcolorQCD),DrawOption("F"));
      apdfMet->plotOn(awmframe,Components(RooArgSet(*(aqcd->model))),LineColor(linecolorQCD));
    }else if (ipt>6 && ipt<10){
      apdfMet->plotOn(awmframe,Components(RooArgSet(*apdfEWK,*apdfqcd)),FillColor(fillcolorEWK),DrawOption("F"));
      apdfMet->plotOn(awmframe,Components(RooArgSet(*apdfEWK,*apdfqcd)),LineColor(linecolorEWK));
      apdfMet->plotOn(awmframe,Components(RooArgSet(*apdfqcd)),FillColor(fillcolorQCD),DrawOption("F"));
      apdfMet->plotOn(awmframe,Components(RooArgSet(*apdfqcd)),LineColor(linecolorQCD));
    }else{
      apdfMet->plotOn(awmframe,Components(RooArgSet(*apdfEWK,*(aqcd1->model))),FillColor(fillcolorEWK),DrawOption("F"));
      apdfMet->plotOn(awmframe,Components(RooArgSet(*apdfEWK,*(aqcd1->model))),LineColor(linecolorEWK));
      apdfMet->plotOn(awmframe,Components(RooArgSet(*(aqcd1->model))),FillColor(fillcolorQCD),DrawOption("F"));
      apdfMet->plotOn(awmframe,Components(RooArgSet(*(aqcd1->model))),LineColor(linecolorQCD));
    }
    apdfMet->plotOn(awmframe,Components(RooArgSet(*apdfWm)),LineColor(linecolorW),LineStyle(2));
    antiMet->plotOn(awmframe,MarkerStyle(kFullCircle),MarkerSize(0.9),DrawOption("ZP"));
    
    sprintf(ylabel,"Events / %.1f GeV",hAntiDataMet[ipt]->GetBinWidth(1));
    sprintf(histName,"fitAntiMet_%d",ipt);
    plotAntiMet=new CPlot (histName,awmframe,"","",ylabel);
    plotAntiMet->setOutDir(CPlot::sOutDir);
    plotAntiMet->SetLegend(0.68,0.57,0.93,0.77);
    plotAntiMet->GetLegend()->AddEntry(hDummyData,"data","PL");
    plotAntiMet->GetLegend()->AddEntry(hDummyW,"W#rightarrow#mu#nu","F");
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
  if (ipt<7){
    pdfMetp->plotOn(wmpframe,Components(RooArgSet(*pdfEWKp,*(qcdp->model))),FillColor(fillcolorEWK),DrawOption("F"));
    pdfMetp->plotOn(wmpframe,Components(RooArgSet(*pdfEWKp,*(qcdp->model))),LineColor(linecolorEWK));
    pdfMetp->plotOn(wmpframe,Components(RooArgSet(*(qcdp->model))),FillColor(fillcolorQCD),DrawOption("F"));
    pdfMetp->plotOn(wmpframe,Components(RooArgSet(*(qcdp->model))),LineColor(linecolorQCD));
  }else if (ipt>6 && ipt<10){
    pdfMetp->plotOn(wmpframe,Components(RooArgSet(*pdfEWKp,*pdfqcdp)),FillColor(fillcolorEWK),DrawOption("F"));
    pdfMetp->plotOn(wmpframe,Components(RooArgSet(*pdfEWKp,*pdfqcdp)),LineColor(linecolorEWK));
    pdfMetp->plotOn(wmpframe,Components(RooArgSet(*pdfqcdp)),FillColor(fillcolorQCD),DrawOption("F"));
    pdfMetp->plotOn(wmpframe,Components(RooArgSet(*pdfqcdp)),LineColor(linecolorQCD));
  }else{
    pdfMetp->plotOn(wmpframe,Components(RooArgSet(*pdfEWKp,*(qcd1p->model))),FillColor(fillcolorEWK),DrawOption("F"));
    pdfMetp->plotOn(wmpframe,Components(RooArgSet(*pdfEWKp,*(qcd1p->model))),LineColor(linecolorEWK));
    pdfMetp->plotOn(wmpframe,Components(RooArgSet(*(qcd1p->model))),FillColor(fillcolorQCD),DrawOption("F"));
    pdfMetp->plotOn(wmpframe,Components(RooArgSet(*(qcd1p->model))),LineColor(linecolorQCD));
  }
  pdfMetp->plotOn(wmpframe,Components(RooArgSet(*pdfWmp)),LineColor(linecolorW),LineStyle(2));
  dataMetp->plotOn(wmpframe,MarkerStyle(kFullCircle),MarkerSize(0.9),DrawOption("ZP"));  
  
  sprintf(ylabel,"Events / %.1f GeV",hDataMetp[ipt]->GetBinWidth(1));
  sprintf(histName,"fitMetP_%d",ipt);
  plotMetp=new CPlot (histName,wmpframe,"","",ylabel);
  plotMetp->setOutDir(CPlot::sOutDir);
  plotMetp->SetLegend(0.68,0.57,0.93,0.77);
  plotMetp->GetLegend()->AddEntry(hDummyData,"data","PL");
  plotMetp->GetLegend()->AddEntry(hDummyW,"W^{+}#rightarrow#mu^{+}#nu","F");
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

  if ( ipt < 11 ){
    awmpframe = pfmet.frame(Bins(NBINS));
    antiMetp->plotOn(awmpframe,MarkerStyle(kFullCircle),MarkerSize(0.9),DrawOption("ZP"));
    apdfMetp->plotOn(awmpframe,FillColor(fillcolorW),DrawOption("F"));
    apdfMetp->plotOn(awmpframe,LineColor(linecolorW));
    if (ipt<7){
      apdfMetp->plotOn(awmpframe,Components(RooArgSet(*apdfEWKp,*(aqcdp->model))),FillColor(fillcolorEWK),DrawOption("F"));
      apdfMetp->plotOn(awmpframe,Components(RooArgSet(*apdfEWKp,*(aqcdp->model))),LineColor(linecolorEWK));
      apdfMetp->plotOn(awmpframe,Components(RooArgSet(*(aqcdp->model))),FillColor(fillcolorQCD),DrawOption("F"));
      apdfMetp->plotOn(awmpframe,Components(RooArgSet(*(aqcdp->model))),LineColor(linecolorQCD));
    }else if (ipt>6 && ipt<10){
      apdfMetp->plotOn(awmpframe,Components(RooArgSet(*apdfEWKp,*apdfqcdp)),FillColor(fillcolorEWK),DrawOption("F"));
      apdfMetp->plotOn(awmpframe,Components(RooArgSet(*apdfEWKp,*apdfqcdp)),LineColor(linecolorEWK));
      apdfMetp->plotOn(awmpframe,Components(RooArgSet(*apdfqcdp)),FillColor(fillcolorQCD),DrawOption("F"));
      apdfMetp->plotOn(awmpframe,Components(RooArgSet(*apdfqcdp)),LineColor(linecolorQCD));
    }else{
      apdfMetp->plotOn(awmpframe,Components(RooArgSet(*apdfEWKp,*(aqcd1p->model))),FillColor(fillcolorEWK),DrawOption("F"));
      apdfMetp->plotOn(awmpframe,Components(RooArgSet(*apdfEWKp,*(aqcd1p->model))),LineColor(linecolorEWK));
      apdfMetp->plotOn(awmpframe,Components(RooArgSet(*(aqcd1p->model))),FillColor(fillcolorQCD),DrawOption("F"));
      apdfMetp->plotOn(awmpframe,Components(RooArgSet(*(aqcd1p->model))),LineColor(linecolorQCD));
    }
    apdfMetp->plotOn(awmpframe,Components(RooArgSet(*apdfWmp)),LineColor(linecolorW),LineStyle(2));
    antiMetp->plotOn(awmpframe,MarkerStyle(kFullCircle),MarkerSize(0.9),DrawOption("ZP"));
    
    sprintf(ylabel,"Events / %.1f GeV",hAntiDataMetp[ipt]->GetBinWidth(1));
    sprintf(histName,"fitAntiMetP_%d",ipt);
    plotAntiMetp=new CPlot (histName,awmpframe,"","",ylabel);
    plotAntiMetp->setOutDir(CPlot::sOutDir);
    plotAntiMetp->SetLegend(0.68,0.57,0.93,0.77);
    plotAntiMetp->GetLegend()->AddEntry(hDummyData,"data","PL");
    plotAntiMetp->GetLegend()->AddEntry(hDummyW,"W^{+}#rightarrow#mu^{+}#nu","F");
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
    plotAntiMetp->Draw(c,kTRUE,format,1);
  }
  //
  // W- MET plot
  //

  wmmframe = pfmet.frame(Bins(NBINS));
  wmmframe->GetYaxis()->SetNdivisions(505);
  dataMetm->plotOn(wmmframe,MarkerStyle(kFullCircle),MarkerSize(0.9),DrawOption("ZP"));
  pdfMetm->plotOn(wmmframe,FillColor(fillcolorW),DrawOption("F"));
  pdfMetm->plotOn(wmmframe,LineColor(linecolorW));
  if (ipt<7){
    pdfMetm->plotOn(wmmframe,Components(RooArgSet(*pdfEWKm,*(qcdm->model))),FillColor(fillcolorEWK),DrawOption("F"));
    pdfMetm->plotOn(wmmframe,Components(RooArgSet(*pdfEWKm,*(qcdm->model))),LineColor(linecolorEWK));
    pdfMetm->plotOn(wmmframe,Components(RooArgSet(*(qcdm->model))),FillColor(fillcolorQCD),DrawOption("F"));
    pdfMetm->plotOn(wmmframe,Components(RooArgSet(*(qcdm->model))),LineColor(linecolorQCD));
  }else if (ipt>6 && ipt<10){
    pdfMetm->plotOn(wmmframe,Components(RooArgSet(*pdfEWKm,*pdfqcdm)),FillColor(fillcolorEWK),DrawOption("F"));
    pdfMetm->plotOn(wmmframe,Components(RooArgSet(*pdfEWKm,*pdfqcdm)),LineColor(linecolorEWK));
    pdfMetm->plotOn(wmmframe,Components(RooArgSet(*pdfqcdm)),FillColor(fillcolorQCD),DrawOption("F"));
    pdfMetm->plotOn(wmmframe,Components(RooArgSet(*pdfqcdm)),LineColor(linecolorQCD));
  }else{
    pdfMetm->plotOn(wmmframe,Components(RooArgSet(*pdfEWKm,*(qcd1m->model))),FillColor(fillcolorEWK),DrawOption("F"));
    pdfMetm->plotOn(wmmframe,Components(RooArgSet(*pdfEWKm,*(qcd1m->model))),LineColor(linecolorEWK));
    pdfMetm->plotOn(wmmframe,Components(RooArgSet(*(qcd1m->model))),FillColor(fillcolorQCD),DrawOption("F"));
    pdfMetm->plotOn(wmmframe,Components(RooArgSet(*(qcd1m->model))),LineColor(linecolorQCD));
  }
  pdfMetm->plotOn(wmmframe,Components(RooArgSet(*pdfWmm)),LineColor(linecolorW),LineStyle(2));
  dataMetm->plotOn(wmmframe,MarkerStyle(kFullCircle),MarkerSize(0.9),DrawOption("ZP"));
  
  sprintf(ylabel,"Events / %.1f GeV",hDataMetm[ipt]->GetBinWidth(1));
  sprintf(histName,"fitMetM_%d",ipt);
  plotMetm=new CPlot(histName,wmmframe,"","",ylabel);
  plotMetm->setOutDir(CPlot::sOutDir);
  plotMetm->SetLegend(0.68,0.57,0.93,0.77);
  plotMetm->GetLegend()->AddEntry(hDummyData,"data","PL");
  plotMetm->GetLegend()->AddEntry(hDummyW,"W^{-}#rightarrow#mu^{-}#bar{#nu}","F");
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

  if ( ipt < 11 ){
    awmmframe = pfmet.frame(Bins(NBINS));
    antiMetm->plotOn(awmmframe,MarkerStyle(kFullCircle),MarkerSize(0.9),DrawOption("ZP"));
    apdfMetm->plotOn(awmmframe,FillColor(fillcolorW),DrawOption("F"));
    apdfMetm->plotOn(awmmframe,LineColor(linecolorW));
    if (ipt<7){
      apdfMetm->plotOn(awmmframe,Components(RooArgSet(*apdfEWKm,*(aqcdm->model))),FillColor(fillcolorEWK),DrawOption("F"));
      apdfMetm->plotOn(awmmframe,Components(RooArgSet(*apdfEWKm,*(aqcdm->model))),LineColor(linecolorEWK));
      apdfMetm->plotOn(awmmframe,Components(RooArgSet(*(aqcdm->model))),FillColor(fillcolorQCD),DrawOption("F"));
      apdfMetm->plotOn(awmmframe,Components(RooArgSet(*(aqcdm->model))),LineColor(linecolorQCD));
    }else if (ipt>6 && ipt<10){
      apdfMetm->plotOn(awmmframe,Components(RooArgSet(*apdfEWKm,*apdfqcdm)),FillColor(fillcolorEWK),DrawOption("F"));
      apdfMetm->plotOn(awmmframe,Components(RooArgSet(*apdfEWKm,*apdfqcdm)),LineColor(linecolorEWK));
      apdfMetm->plotOn(awmmframe,Components(RooArgSet(*apdfqcdm)),FillColor(fillcolorQCD),DrawOption("F"));
      apdfMetm->plotOn(awmmframe,Components(RooArgSet(*apdfqcdm)),LineColor(linecolorQCD));
    }else{
      apdfMetm->plotOn(awmmframe,Components(RooArgSet(*apdfEWKm,*(aqcd1m->model))),FillColor(fillcolorEWK),DrawOption("F"));
      apdfMetm->plotOn(awmmframe,Components(RooArgSet(*apdfEWKm,*(aqcd1m->model))),LineColor(linecolorEWK));
      apdfMetm->plotOn(awmmframe,Components(RooArgSet(*(aqcd1m->model))),FillColor(fillcolorQCD),DrawOption("F"));
      apdfMetm->plotOn(awmmframe,Components(RooArgSet(*(aqcd1m->model))),LineColor(linecolorQCD));
    }
    apdfMetm->plotOn(awmmframe,Components(RooArgSet(*apdfWmm)),LineColor(linecolorW),LineStyle(2));
    antiMetm->plotOn(awmmframe,MarkerStyle(kFullCircle),MarkerSize(0.9),DrawOption("ZP"));
    
    sprintf(ylabel,"Events / %.1f GeV",hAntiDataMetm[ipt]->GetBinWidth(1));
    sprintf(histName,"fitAntiMetM_%d",ipt);
    plotAntiMetm=new CPlot(histName,awmmframe,"","",ylabel);
    plotAntiMetm->setOutDir(CPlot::sOutDir);
    plotAntiMetm->SetLegend(0.68,0.57,0.93,0.77);
    plotAntiMetm->GetLegend()->AddEntry(hDummyData,"data","PL");
    plotAntiMetm->GetLegend()->AddEntry(hDummyW,"W^{-}#rightarrow#mu^{-}#bar{#nu}","F");
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
    plotAntiMetm->Draw(c,kTRUE,format,1);
  }
    
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
    Wmfile << "============================================== [0, 600] Bin - " << ipt << " ==============================================" << endl;
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
    Wmpfile << "============================================== [0, 600] Bin - " << ipt << " ==============================================" << endl;
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
    Wmmfile << "============================================== [0, 600] Bin - " << ipt << " ==============================================" << endl;
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

  flags = qcdfile.flags();
  if (ipt<7){
    qcdfile << "Sigma: " << qcd->sigma->getValV() << "\t" << "Mean: " << qcd->mean->getValV() << "\t" << "Sigma1: " << qcd->a1->getValV() << "\t" << "SigmaP: " << qcdp->sigma->getValV() << "\t" << "MeanP: " << qcdp->mean->getValV() << "\t" << "Sigma1P: " << qcdp->a1->getValV() << "\t" << "SigmaM: " << qcdm->sigma->getValV() << "\t" << "MeanM: " << qcdm->mean->getValV() << "\t" << "Sigma1M: " << qcdm->a1->getValV() << endl;
  }else if(ipt>6 && ipt<10){
    qcdfile << "Gauss Sigma,Mean(Incl, + -): " << gausSigma->getValV() << "\t" << gausSigma_p->getValV() << "\t" << gausSigma_m->getValV() << "\t" << gausMean->getValV() << "\t" << gausMean_p->getValV() << "\t" << gausMean_m->getValV() << "QCD Sigma,a1(Incl, + -): " << qcd1->sigma->getValV() << "\t" << qcd1p->sigma->getValV() << "\t" << qcd1m->sigma->getValV() << "\t" << qcd1->a1->getValV() << "\t" << qcd1p->a1->getValV() << "\t" << qcd1m->a1->getValV() << "\t" << " Side Sigma,a1(Incl, + -): " << aqcd1->sigma->getValV() << "\t" << aqcd1p->sigma->getValV() << "\t" << aqcd1m->sigma->getValV() << "\t" << aqcd1->a1->getValV() << "\t" << aqcd1p->a1->getValV() << "\t" << aqcd1m->a1->getValV() << endl;
  }else{
    qcdfile << "QCD Sigma,a1(Incl, + -): " << qcd1->sigma->getValV() << "\t" << qcd1p->sigma->getValV() << "\t" << qcd1m->sigma->getValV() << "\t" << qcd1->a1->getValV() << "\t" << qcd1p->a1->getValV() << "\t" << qcd1m->a1->getValV() << "\t" << " Side Sigma,a1(Incl, + -): " << aqcd1->sigma->getValV() << "\t" << aqcd1p->sigma->getValV() << "\t" << aqcd1m->sigma->getValV() << "\t" << aqcd1->a1->getValV() << "\t" << aqcd1p->a1->getValV() << "\t" << aqcd1m->a1->getValV() << endl;
  }
  qcdfile << endl;
  qcdfile.flags(flags);

  metplotsfile << "<hr />" << endl;
  if (ipt==0)
    metplotsfile << "<p align=\"center\"> [0, 600] Bin - " << ipt << "</p>" << endl;
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
    tablefile << "<p align=\"center\">  [0, 600] Bin - "<< ipt <<" Yields </p>" << endl;
  else
    tablefile << "<p align=\"center\"> [" << WptBins[ipt-1] << ", " << WptBins[ipt] << "] Bin - "<< ipt <<" Yields </p>" << endl;
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

  if (ipt>0){
    hSigWpt -> SetBinContent(ipt, nSig->getVal());
    hSigWpt -> SetBinError(ipt, nSig->getPropagatedError(*fitRes));
    hSigWPpt-> SetBinContent(ipt, nSigp->getVal());
    hSigWPpt-> SetBinError(ipt, nSigp->getPropagatedError(*fitResp));
    hSigWMpt-> SetBinContent(ipt, nSigm->getVal());
    hSigWMpt-> SetBinError(ipt, nSigm->getPropagatedError(*fitResm));
    hQCDWpt -> SetBinContent(ipt, nQCD->getVal());
    hQCDWPpt-> SetBinContent(ipt, nQCDp->getVal());
    hQCDWMpt-> SetBinContent(ipt, nQCDm->getVal());

    hQCD_SigPlus-> SetBinContent(ipt, nQCDp->getVal()/nSigp->getVal());
    hQCD_SigMinus-> SetBinContent(ipt, nQCDm->getVal()/nSigm->getVal());
    hQCD_SigQCDPlus-> SetBinContent(ipt,  nQCDp->getVal()/(  nQCDp->getVal()+ nSigp->getVal()  )  );
    hQCD_SigQCDMinus-> SetBinContent(ipt, nQCDm->getVal()/(  nQCDm->getVal()+ nSigm->getVal()  )  );

    double total = nEventDYToMuMu[ipt]+nEventDYToTauTau[ipt]+nEventTTJets[ipt]+nEventWToTauNu[ipt];
    double totalp = nEventDYToMuMuP[ipt]+nEventDYToTauTauP[ipt]+nEventTTJetsP[ipt]+nEventWToTauNuP[ipt];
    double totalm = nEventDYToMuMuM[ipt]+nEventDYToTauTauM[ipt]+nEventTTJetsM[ipt]+nEventWToTauNuM[ipt];
    hDYToMuMu	-> SetBinContent(ipt,nEWK->getVal()*nEventDYToMuMu[ipt]/total);
    hWToTauTau	-> SetBinContent(ipt,nEWK->getVal()*nEventWToTauNu[ipt]/total);
    hTTJets	-> SetBinContent(ipt,nEWK->getVal()*nEventTTJets[ipt]/total);
    hDYToTauTau -> SetBinContent(ipt,nEWK->getVal()*nEventDYToTauTau[ipt]/total);
    hDYToMuMuP  -> SetBinContent(ipt,nEWKp->getVal()*nEventDYToMuMuP[ipt]/totalp);
    hWToTauTauP -> SetBinContent(ipt,nEWKp->getVal()*nEventWToTauNuP[ipt]/totalp);
    hTTJetsP    -> SetBinContent(ipt,nEWKp->getVal()*nEventTTJetsP[ipt]/totalp);
    hDYToTauTauP-> SetBinContent(ipt,nEWKp->getVal()*nEventDYToTauTauP[ipt]/totalp);
    hDYToMuMuM  -> SetBinContent(ipt,nEWKm->getVal()*nEventDYToMuMuM[ipt]/totalm);
    hWToTauTauM -> SetBinContent(ipt,nEWKm->getVal()*nEventWToTauNuM[ipt]/totalm);
    hTTJetsM    -> SetBinContent(ipt,nEWKm->getVal()*nEventTTJetsM[ipt]/totalm);
    hDYToTauTauM-> SetBinContent(ipt,nEWKm->getVal()*nEventDYToTauTauM[ipt]/totalm);
  }
  }

  Wmfile.close();
  Wmpfile.close();
  Wmmfile.close();
  qcdfile.close();

  tablefile << "</body>" << endl;
  tablefile << "</html>" << endl;
  tablefile.close();

  metplotsfile << "</body>" << endl;
  metplotsfile << "</html>" << endl;
  metplotsfile.close();  

  allyields.close();
  allyieldsp.close();
  allyieldsm.close();

//Write Signal numbers to file
  gSystem->mkdir("RstMuon",kTRUE);
  TString Yields = "RstMuon/SigYields_"+filetype+".root";
  TFile *nsigfile = new TFile(Yields,"RECREATE");
  hSigWpt -> Write();
  hSigWPpt-> Write();
  hSigWMpt-> Write();

  
  TF1 *f111 = new TF1("f111","[0]*TMath::Exp(-x/[1])+[2]",50.,600.);
  f111->SetParameter(0,1);
  f111->SetParameter(1,0.3);
  f111->SetParameter(2,0);
  f111->SetLineColor(kBlue);
  hQCD_SigPlus->Fit("f111","L","",50.,600.);
  hQCD_SigPlus-> Write();
  hQCD_SigMinus->Fit("f111","L","",50.,600.);
  hQCD_SigMinus-> Write();

  hQCD_SigQCDPlus->Fit("f111","L","",50.,600.);
  hQCD_SigQCDPlus-> Write();
  hQCD_SigQCDMinus->Fit("f111","L","",50.,600.);
  hQCD_SigQCDMinus-> Write();

  nsigfile-> Close();

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
  plotWpt->AddToStack(hWToTauTau,"W#rightarrow#tau#nu",kCyan-9,kCyan-6);
  plotWpt->AddToStack(hDYToMuMu,"Z/#gamma^{*}#rightarrow#mu#mu",fillcolorEWK,linecolorEWK);
  plotWpt->AddToStack(hQCDWpt,"QCD",fillcolorQCD,linecolorQCD);
  plotWpt->AddToStack(hSigWpt,"W#rightarrow#mu#nu",fillcolorW,linecolorW);
  plotWpt->AddHist1D(hdataWpt,"Data","E");
  plotWpt->SetLegend(0.78,0.65,.98,0.88);
  plotWpt->SetYRange(0.1,1.1*(hWptMC->GetMaximum()));
  plotWpt->Draw(c,kFALSE,format,1);
  gPad->RedrawAxis();

  plotWptDiff=new CPlot(histName,"","p_{T} [Gev]","#chi");
  plotWptDiff->setOutDir(CPlot::sOutDir);
  plotWptDiff->AddHist1D(hWptDiff,"EX0",ratioColor);
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

  //W plus pt distribution
  TH1D* hWptMC_p = (TH1D*)hDYToTauTauP->Clone("hWptMC_p");
  hWptMC_p->Add(hTTJetsP);
  hWptMC_p->Add(hWToTauTauP);
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
  plotWpt_p->AddToStack(hWToTauTauP,"W#rightarrow#tau#nu",kCyan-9,kCyan-6);
  plotWpt_p->AddToStack(hDYToMuMuP,"Z/#gamma^{*}#rightarrow#mu#mu",fillcolorEWK,linecolorEWK);
  plotWpt_p->AddToStack(hQCDWPpt,"QCD",fillcolorQCD,linecolorQCD);
  plotWpt_p->AddToStack(hSigWPpt,"W#rightarrow#mu#nu",fillcolorW,linecolorW);
  plotWpt_p->AddHist1D(hdataWPpt,"Data","E");
  plotWpt_p->SetLegend(0.78,0.65,.98,0.88);
  plotWpt_p->SetYRange(0.1,1.1*(hWptMC_p->GetMaximum()));
  plotWpt_p->Draw(c,kFALSE,format,1);
  gPad->RedrawAxis();

  plotWptDiff_p=new CPlot(histName,"","p_{T} [Gev]","#chi");
  plotWptDiff_p->setOutDir(CPlot::sOutDir);
  plotWptDiff_p->AddHist1D(hWptDiff_p,"EX0",ratioColor);
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

//W minus pt distribution
  TH1D* hWptMC_m = (TH1D*)hDYToTauTauM->Clone("hWptMC_m");
  hWptMC_m->Add(hTTJetsM);
  hWptMC_m->Add(hWToTauTauM);
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
  plotWpt_m->AddToStack(hWToTauTauM,"W#rightarrow#tau#nu",kCyan-9,kCyan-6);
  plotWpt_m->AddToStack(hDYToMuMuM,"Z/#gamma^{*}#rightarrow#mu#mu",fillcolorEWK,linecolorEWK);
  plotWpt_m->AddToStack(hQCDWMpt,"QCD",fillcolorQCD,linecolorQCD);
  plotWpt_m->AddToStack(hSigWMpt,"W#rightarrow#mu#nu",fillcolorW,linecolorW);
  plotWpt_m->AddHist1D(hdataWMpt,"Data","E");
  plotWpt_m->SetLegend(0.78,0.65,.98,0.88);
  plotWpt_m->SetYRange(0.1,1.1*(hWptMC_m->GetMaximum()));
  plotWpt_m->Draw(c,kFALSE,format,1);
  gPad->RedrawAxis();

  plotWptDiff_m=new CPlot(histName,"","p_{T} [Gev]","#chi");
  plotWptDiff_m->setOutDir(CPlot::sOutDir);
  plotWptDiff_m->AddHist1D(hWptDiff_m,"EX0",ratioColor);
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

  makeHTML(outputDir);
  gBenchmark->Show("fitWMuMetRayleighGausSimult");
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
  double WptBins[14]={0,7.5,12.5,17.5,24,30,40,50,70,110,150,190,250,600};
  TH1D *hDiff = new TH1D(name,"",13,WptBins);
  TAxis *xaxis = hData->GetXaxis();
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
  sprintf(htmlfname,"%s/WmunuFitPlots.html",outDir.Data());
  htmlfile.open(htmlfname);
  htmlfile << "<!DOCTYPE html" << endl;
  htmlfile << "    PUBLIC \"-//W3C//DTD HTML 3.2//EN\">" << endl;
  htmlfile << "<html>" << endl;
  htmlfile << "<head><title>W --> mu nu</title></head>" << endl;
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
