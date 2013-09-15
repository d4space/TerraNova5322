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

int scaleSmearTemplateFitHighPU(TString RDFile, TString MCFile, char BaseName[30])
{
  cout<<"Processing "<<BaseName<<endl;
  gStyle->SetPalette(1);
  //Output file
  TString ResultDir = "MCRDfitEle_Plot";
  ofstream Fout;
  TString FoutName=ResultDir+"/"+BaseName+"_SummaryFinal.txt";
  Fout.open(FoutName);
  //Variables
  char histName[50];
  //Data and histograms
  TFile *f_RD = new TFile(RDFile);
  TFile *f_MC = new TFile(MCFile);
  TH1D *h1_ZmassDaughEtaRD[ScElCombiBinsHighPU];
  TH1D *h1_ZmassDaughEtaMC[ScElCombiBinsHighPU];

  //Plots
  RooPlot *zmassFrameRD;
  RooPlot *zmassFrameMC;
  CPlot *plotFitRD;
  CPlot *plotFitMC;
  RooFitResult* fitResTotalMC;
  RooFitResult* fitResTotalRD;
  //RooFitResult* fitResRD;
  RooFitResult* fitResMCbw[ScElCombiBinsHighPU];
  RooFitResult* fitResMC[ScElCombiBinsHighPU];
  RooFitResult* fitResRD[ScElCombiBinsHighPU];

  TCanvas *myCan = MakeCanvas("myCan","myCan",800,600);
  //Fitting stuff
  RooRealVar *scaleMC[ScaleBinsHighPU];
  RooRealVar *scaleRD[ScaleBinsHighPU];
  RooRealVar *smearRD[ScaleBinsHighPU];
  RooRealVar *smearMC[ScaleBinsHighPU];


  RooRealVar *nSRD[ScElCombiBinsHighPU];
  RooRealVar *nBRD[ScElCombiBinsHighPU];
  RooRealVar *CBalpha[ScElCombiBinsHighPU];
  RooRealVar *CBn[ScElCombiBinsHighPU];

  RooFormulaVar *scaleScaleMC[ScElCombiBinsHighPU];
  RooFormulaVar *scaleScaleRD[ScElCombiBinsHighPU];
  RooFormulaVar *smearSmearMC[ScElCombiBinsHighPU];
  RooFormulaVar *smearSmearRD[ScElCombiBinsHighPU];

  RooRealVar zMass("zMass","zMass",60,120);
  RooCategory rooCat("rooCat","rooCat");
  RooDataHist *ZmassRD[ScElCombiBinsHighPU];

// RooDataHist *ZmassMC;
 RooDataHist *ZmassMC[ScElCombiBinsHighPU];
//  CBreitWigner *BW[ScElCombiBinsHighPU];
  CBreitWignerConvCrystalBall *BWCB[ScElCombiBinsHighPU];
  CBreitWignerConvCrystalBallScale *BWCBsCale[ScElCombiBinsHighPU];
  CBreitWignerMC  *BWMC[ScElCombiBinsHighPU];
  CBreitWignerRD  *BWRD[ScElCombiBinsHighPU];

  RooGaussian *gaus[ScElCombiBinsHighPU];
  RooCBShape *cbMC[ScElCombiBinsHighPU];
  RooCBShape *cbRD[ScElCombiBinsHighPU];

  CErfExpo *ZbgRD[ScElCombiBinsHighPU];

  CExponential *ZbgExpRD[ScElCombiBinsHighPU];

  RooAbsPdf *pdfRDsig[ScElCombiBinsHighPU];
  RooAbsPdf *pdfMCsig[ScElCombiBinsHighPU];
  //RooAddPdf *pdfRDsig[ScElCombiBinsHighPU];
  RooAbsPdf *histPdf[ScElCombiBinsHighPU];
  RooAddPdf *pdfRD[ScElCombiBinsHighPU];


  //Initialization
  for(int i(0);i<ScaleBinsHighPU;i++)
  {
    sprintf(histName,"scaleMC_%d",i);
    scaleMC[i] = new RooRealVar(histName, histName,1.01,0.001,3);
    sprintf(histName,"scaleRD_%d",i);
    scaleRD[i] = new RooRealVar(histName, histName,1.01,0.001,3);
    sprintf(histName,"smearMC_%d",i);
    smearMC[i] = new RooRealVar(histName,histName,0.5,0.01,3);
    sprintf(histName,"smearRD_%d",i);
    smearRD[i] = new RooRealVar(histName,histName,0.5,0.01,3);
  }

  for(int i(0);i<ScElCombiBinsHighPU;i++)
  {
    sprintf(histName,"nBRD_%d",i);
    nBRD[i] = new RooRealVar(histName, histName,0.1,0.01,1);
    sprintf(histName,"nSRD_%d",i);
    nSRD[i]= new RooRealVar(histName,histName,1,0,2);
    sprintf(histName,"CBalpha_%d",i); 
    CBalpha[i]= new RooRealVar(histName,histName,5,0,20);
    sprintf(histName,"CBn_%d",i);     
    CBn[i]     = new RooRealVar(histName,histName,1,0,10);

    sprintf(histName,"cat_%d",i);
    rooCat.defineType(histName);
  }

  RooSimultaneous pdfTotalMC("pdfTotalMC","pdfTotalMC",rooCat);
  map<string,TH1*>hmapMC;
  RooSimultaneous pdfTotalRD("pdfTotalRD","pdfTotalRD",rooCat);
  map<string,TH1*>hmapRD;

 
  //*
  ///scaleScale
  sprintf(histName,"scaleScaleMC_0");
  scaleScaleMC[0] = new RooFormulaVar(histName,"1/sqrt(@0*@0)",RooArgSet(*scaleMC[0],*scaleMC[0]));
  sprintf(histName,"scaleScaleMC_1");
  scaleScaleMC[1] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleMC[0],*scaleMC[1]));
  sprintf(histName,"scaleScaleMC_2");
  scaleScaleMC[2] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleMC[0],*scaleMC[2]));
  sprintf(histName,"scaleScaleMC_3");
  scaleScaleMC[3] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleMC[0],*scaleMC[3]));
  sprintf(histName,"scaleScaleMC_4");
  scaleScaleMC[4] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleMC[0],*scaleMC[4]));
  sprintf(histName,"scaleScaleMC_5");
  scaleScaleMC[5] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleMC[0],*scaleMC[5]));
  sprintf(histName,"scaleScaleMC_6");
  scaleScaleMC[6] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleMC[0],*scaleMC[6]));
  sprintf(histName,"scaleScaleMC_7");
  scaleScaleMC[7] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleMC[0],*scaleMC[7]));
  sprintf(histName,"scaleScaleMC_8");
  scaleScaleMC[8] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleMC[0],*scaleMC[8]));
  sprintf(histName,"scaleScaleMC_9");
  scaleScaleMC[9] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleMC[0],*scaleMC[9]));
  sprintf(histName,"scaleScaleMC_10");
  scaleScaleMC[10] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleMC[0],*scaleMC[10]));
  
  sprintf(histName,"scaleScaleMC_11");
  scaleScaleMC[11] = new RooFormulaVar(histName,"1/sqrt(@0*@0)",RooArgSet(*scaleMC[1],*scaleMC[1]));
  sprintf(histName,"scaleScaleMC_12");
  scaleScaleMC[12] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleMC[1],*scaleMC[2]));
  sprintf(histName,"scaleScaleMC_13");
  scaleScaleMC[13] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleMC[1],*scaleMC[3]));
  sprintf(histName,"scaleScaleMC_14");
  scaleScaleMC[14] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleMC[1],*scaleMC[4]));
  sprintf(histName,"scaleScaleMC_15");
  scaleScaleMC[15] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleMC[1],*scaleMC[5]));
  sprintf(histName,"scaleScaleMC_16");
  scaleScaleMC[16] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleMC[1],*scaleMC[6]));
  sprintf(histName,"scaleScaleMC_17");
  scaleScaleMC[17] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleMC[1],*scaleMC[7]));
  sprintf(histName,"scaleScaleMC_18");
  scaleScaleMC[18] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleMC[1],*scaleMC[8]));
  sprintf(histName,"scaleScaleMC_19");
  scaleScaleMC[19] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleMC[1],*scaleMC[9]));
  sprintf(histName,"scaleScaleMC_20");
  scaleScaleMC[20] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleMC[1],*scaleMC[10]));

  sprintf(histName,"scaleScaleMC_21");
  scaleScaleMC[21] = new RooFormulaVar(histName,"1/sqrt(@0*@0)",RooArgSet(*scaleMC[2],*scaleMC[2]));
  sprintf(histName,"scaleScaleMC_22");
  scaleScaleMC[22] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleMC[2],*scaleMC[3]));
  sprintf(histName,"scaleScaleMC_23");
  scaleScaleMC[23] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleMC[2],*scaleMC[4]));
  sprintf(histName,"scaleScaleMC_24");
  scaleScaleMC[24] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleMC[2],*scaleMC[5]));
  sprintf(histName,"scaleScaleMC_25");
  scaleScaleMC[25] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleMC[2],*scaleMC[6]));
  sprintf(histName,"scaleScaleMC_26");
  scaleScaleMC[26] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleMC[2],*scaleMC[7]));
  sprintf(histName,"scaleScaleMC_27");
  scaleScaleMC[27] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleMC[2],*scaleMC[8]));
  sprintf(histName,"scaleScaleMC_28");
  scaleScaleMC[28] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleMC[2],*scaleMC[9]));
  sprintf(histName,"scaleScaleMC_29");
  scaleScaleMC[29] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleMC[2],*scaleMC[10]));


  sprintf(histName,"scaleScaleMC_30");
  scaleScaleMC[30] = new RooFormulaVar(histName,"1/sqrt(@0*@0)",RooArgSet(*scaleMC[3],*scaleMC[3]));
  sprintf(histName,"scaleScaleMC_31");
  scaleScaleMC[31] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleMC[3],*scaleMC[4]));
  sprintf(histName,"scaleScaleMC_32");
  scaleScaleMC[32] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleMC[3],*scaleMC[5]));
  sprintf(histName,"scaleScaleMC_33");
  scaleScaleMC[33] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleMC[3],*scaleMC[6]));
  sprintf(histName,"scaleScaleMC_34");
  scaleScaleMC[34] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleMC[3],*scaleMC[7]));
  sprintf(histName,"scaleScaleMC_35");
  scaleScaleMC[35] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleMC[3],*scaleMC[8]));
  sprintf(histName,"scaleScaleMC_36");
  scaleScaleMC[36] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleMC[3],*scaleMC[9]));
  sprintf(histName,"scaleScaleMC_37");
  scaleScaleMC[37] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleMC[3],*scaleMC[10]));

  sprintf(histName,"scaleScaleMC_38");
  scaleScaleMC[38] = new RooFormulaVar(histName,"1/sqrt(@0*@0)",RooArgSet(*scaleMC[4],*scaleMC[4]));
  sprintf(histName,"scaleScaleMC_39");
  scaleScaleMC[39] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleMC[4],*scaleMC[5]));
  sprintf(histName,"scaleScaleMC_40");
  scaleScaleMC[40] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleMC[4],*scaleMC[6]));
  sprintf(histName,"scaleScaleMC_41");
  scaleScaleMC[41] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleMC[4],*scaleMC[7]));
  sprintf(histName,"scaleScaleMC_42");
  scaleScaleMC[42] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleMC[4],*scaleMC[8]));
  sprintf(histName,"scaleScaleMC_43");
  scaleScaleMC[43] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleMC[4],*scaleMC[9]));
  sprintf(histName,"scaleScaleMC_44");
  scaleScaleMC[44] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleMC[4],*scaleMC[10]));

  sprintf(histName,"scaleScaleMC_45");
  scaleScaleMC[45] = new RooFormulaVar(histName,"1/sqrt(@0*@0)",RooArgSet(*scaleMC[5],*scaleMC[5]));
  sprintf(histName,"scaleScaleMC_46");
  scaleScaleMC[46] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleMC[5],*scaleMC[6]));
  sprintf(histName,"scaleScaleMC_47");
  scaleScaleMC[47] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleMC[5],*scaleMC[7]));
  sprintf(histName,"scaleScaleMC_48");
  scaleScaleMC[48] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleMC[5],*scaleMC[8]));
  sprintf(histName,"scaleScaleMC_49");
  scaleScaleMC[49] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleMC[5],*scaleMC[9]));
  sprintf(histName,"scaleScaleMC_50");
  scaleScaleMC[50] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleMC[5],*scaleMC[10]));

  sprintf(histName,"scaleScaleMC_51");
  scaleScaleMC[51] = new RooFormulaVar(histName,"1/sqrt(@0*@0)",RooArgSet(*scaleMC[6],*scaleMC[6]));
  sprintf(histName,"scaleScaleMC_52");
  scaleScaleMC[52] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleMC[6],*scaleMC[7]));
  sprintf(histName,"scaleScaleMC_53");
  scaleScaleMC[53] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleMC[6],*scaleMC[8]));
  sprintf(histName,"scaleScaleMC_54");
  scaleScaleMC[54] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleMC[6],*scaleMC[9]));
  sprintf(histName,"scaleScaleMC_55");
  scaleScaleMC[55] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleMC[6],*scaleMC[10]));
  
  sprintf(histName,"scaleScaleMC_56");
  scaleScaleMC[56] = new RooFormulaVar(histName,"1/sqrt(@0*@0)",RooArgSet(*scaleMC[7],*scaleMC[7]));
  sprintf(histName,"scaleScaleMC_57");
  scaleScaleMC[57] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleMC[7],*scaleMC[8]));
  sprintf(histName,"scaleScaleMC_58");
  scaleScaleMC[58] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleMC[7],*scaleMC[9]));
  sprintf(histName,"scaleScaleMC_59");
  scaleScaleMC[59] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleMC[7],*scaleMC[10]));
  
  sprintf(histName,"scaleScaleMC_60");
  scaleScaleMC[60] = new RooFormulaVar(histName,"1/sqrt(@0*@0)",RooArgSet(*scaleMC[8],*scaleMC[8]));
  sprintf(histName,"scaleScaleMC_61");
  scaleScaleMC[61] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleMC[8],*scaleMC[9]));
  sprintf(histName,"scaleScaleMC_62");
  scaleScaleMC[62] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleMC[8],*scaleMC[10]));
  
  sprintf(histName,"scaleScaleMC_63");
  scaleScaleMC[63] = new RooFormulaVar(histName,"1/sqrt(@0*@0)",RooArgSet(*scaleMC[9],*scaleMC[9]));
  sprintf(histName,"scaleScaleMC_64");
  scaleScaleMC[64] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleMC[9],*scaleMC[10]));
  
  sprintf(histName,"scaleScaleMC_65");
  scaleScaleMC[65] = new RooFormulaVar(histName,"1/sqrt(@0*@0)",RooArgSet(*scaleMC[10],*scaleMC[10]));
  //*/


  //*
  ///scaleScale
  sprintf(histName,"scaleScaleRD_0");
  scaleScaleRD[0] = new RooFormulaVar(histName,"1/sqrt(@0*@0)",RooArgSet(*scaleRD[0],*scaleRD[0]));
  sprintf(histName,"scaleScaleRD_1");
  scaleScaleRD[1] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleRD[0],*scaleRD[1]));
  sprintf(histName,"scaleScaleRD_2");
  scaleScaleRD[2] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleRD[0],*scaleRD[2]));
  sprintf(histName,"scaleScaleRD_3");
  scaleScaleRD[3] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleRD[0],*scaleRD[3]));
  sprintf(histName,"scaleScaleRD_4");
  scaleScaleRD[4] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleRD[0],*scaleRD[4]));
  sprintf(histName,"scaleScaleRD_5");
  scaleScaleRD[5] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleRD[0],*scaleRD[5]));
  sprintf(histName,"scaleScaleRD_6");
  scaleScaleRD[6] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleRD[0],*scaleRD[6]));
  sprintf(histName,"scaleScaleRD_7");
  scaleScaleRD[7] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleRD[0],*scaleRD[7]));
  sprintf(histName,"scaleScaleRD_8");
  scaleScaleRD[8] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleRD[0],*scaleRD[8]));
  sprintf(histName,"scaleScaleRD_9");
  scaleScaleRD[9] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleRD[0],*scaleRD[9]));
  sprintf(histName,"scaleScaleRD_10");
  scaleScaleRD[10] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleRD[0],*scaleRD[10]));

  sprintf(histName,"scaleScaleRD_11");
  scaleScaleRD[11] = new RooFormulaVar(histName,"1/sqrt(@0*@0)",RooArgSet(*scaleRD[1],*scaleRD[1]));
  sprintf(histName,"scaleScaleRD_12");
  scaleScaleRD[12] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleRD[1],*scaleRD[2]));
  sprintf(histName,"scaleScaleRD_13");
  scaleScaleRD[13] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleRD[1],*scaleRD[3]));
  sprintf(histName,"scaleScaleRD_14");
  scaleScaleRD[14] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleRD[1],*scaleRD[4]));
  sprintf(histName,"scaleScaleRD_15");
  scaleScaleRD[15] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleRD[1],*scaleRD[5]));
  sprintf(histName,"scaleScaleRD_16");
  scaleScaleRD[16] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleRD[1],*scaleRD[6]));
  sprintf(histName,"scaleScaleRD_17");
  scaleScaleRD[17] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleRD[1],*scaleRD[7]));
  sprintf(histName,"scaleScaleRD_18");
  scaleScaleRD[18] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleRD[1],*scaleRD[8]));
  sprintf(histName,"scaleScaleRD_19");
  scaleScaleRD[19] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleRD[1],*scaleRD[9]));
  sprintf(histName,"scaleScaleRD_20");
  scaleScaleRD[20] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleRD[1],*scaleRD[10]));

  sprintf(histName,"scaleScaleRD_21");
  scaleScaleRD[21] = new RooFormulaVar(histName,"1/sqrt(@0*@0)",RooArgSet(*scaleRD[2],*scaleRD[2]));
  sprintf(histName,"scaleScaleRD_22");
  scaleScaleRD[22] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleRD[2],*scaleRD[3]));
  sprintf(histName,"scaleScaleRD_23");
  scaleScaleRD[23] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleRD[2],*scaleRD[4]));
  sprintf(histName,"scaleScaleRD_24");
  scaleScaleRD[24] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleRD[2],*scaleRD[5]));
  sprintf(histName,"scaleScaleRD_25");
  scaleScaleRD[25] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleRD[2],*scaleRD[6]));
  sprintf(histName,"scaleScaleRD_26");
  scaleScaleRD[26] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleRD[2],*scaleRD[7]));
  sprintf(histName,"scaleScaleRD_27");
  scaleScaleRD[27] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleRD[2],*scaleRD[8]));
  sprintf(histName,"scaleScaleRD_28");
  scaleScaleRD[28] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleRD[2],*scaleRD[9]));
  sprintf(histName,"scaleScaleRD_29");
  scaleScaleRD[29] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleRD[2],*scaleRD[10]));

  sprintf(histName,"scaleScaleRD_30");
  scaleScaleRD[30] = new RooFormulaVar(histName,"1/sqrt(@0*@0)",RooArgSet(*scaleRD[3],*scaleRD[3]));
  sprintf(histName,"scaleScaleRD_31");
  scaleScaleRD[31] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleRD[3],*scaleRD[4]));
  sprintf(histName,"scaleScaleRD_32");
  scaleScaleRD[32] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleRD[3],*scaleRD[5]));
  sprintf(histName,"scaleScaleRD_33");
  scaleScaleRD[33] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleRD[3],*scaleRD[6]));
  sprintf(histName,"scaleScaleRD_34");
  scaleScaleRD[34] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleRD[3],*scaleRD[7]));
  sprintf(histName,"scaleScaleRD_35");
  scaleScaleRD[35] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleRD[3],*scaleRD[8]));
  sprintf(histName,"scaleScaleRD_36");
  scaleScaleRD[36] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleRD[3],*scaleRD[9]));
  sprintf(histName,"scaleScaleRD_37");
  scaleScaleRD[37] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleRD[3],*scaleRD[10]));

  sprintf(histName,"scaleScaleRD_38");
  scaleScaleRD[38] = new RooFormulaVar(histName,"1/sqrt(@0*@0)",RooArgSet(*scaleRD[4],*scaleRD[4]));
  sprintf(histName,"scaleScaleRD_39");
  scaleScaleRD[39] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleRD[4],*scaleRD[5]));
  sprintf(histName,"scaleScaleRD_40");
  scaleScaleRD[40] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleRD[4],*scaleRD[6]));
  sprintf(histName,"scaleScaleRD_41");
  scaleScaleRD[41] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleRD[4],*scaleRD[7]));
  sprintf(histName,"scaleScaleRD_42");
  scaleScaleRD[42] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleRD[4],*scaleRD[8]));
  sprintf(histName,"scaleScaleRD_43");
  scaleScaleRD[43] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleRD[4],*scaleRD[9]));
  sprintf(histName,"scaleScaleRD_44");
  scaleScaleRD[44] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleRD[4],*scaleRD[10]));

  sprintf(histName,"scaleScaleRD_45");
  scaleScaleRD[45] = new RooFormulaVar(histName,"1/sqrt(@0*@0)",RooArgSet(*scaleRD[5],*scaleRD[5]));
  sprintf(histName,"scaleScaleRD_46");
  scaleScaleRD[46] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleRD[5],*scaleRD[6]));
  sprintf(histName,"scaleScaleRD_47");
  scaleScaleRD[47] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleRD[5],*scaleRD[7]));
  sprintf(histName,"scaleScaleRD_48");
  scaleScaleRD[48] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleRD[5],*scaleRD[8]));
  sprintf(histName,"scaleScaleRD_49");
  scaleScaleRD[49] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleRD[5],*scaleRD[9]));
  sprintf(histName,"scaleScaleRD_50");
  scaleScaleRD[50] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleRD[5],*scaleRD[10]));

  sprintf(histName,"scaleScaleRD_51");
  scaleScaleRD[51] = new RooFormulaVar(histName,"1/sqrt(@0*@0)",RooArgSet(*scaleRD[6],*scaleRD[6]));
  sprintf(histName,"scaleScaleRD_52");
  scaleScaleRD[52] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleRD[6],*scaleRD[7]));
  sprintf(histName,"scaleScaleRD_53");
  scaleScaleRD[53] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleRD[6],*scaleRD[8]));
  sprintf(histName,"scaleScaleRD_54");
  scaleScaleRD[54] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleRD[6],*scaleRD[9]));
  sprintf(histName,"scaleScaleRD_55");
  scaleScaleRD[55] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleRD[6],*scaleRD[10]));

  sprintf(histName,"scaleScaleRD_56");
  scaleScaleRD[56] = new RooFormulaVar(histName,"1/sqrt(@0*@0)",RooArgSet(*scaleRD[7],*scaleRD[7]));
  sprintf(histName,"scaleScaleRD_57");
  scaleScaleRD[57] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleRD[7],*scaleRD[8]));
  sprintf(histName,"scaleScaleRD_58");
  scaleScaleRD[58] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleRD[7],*scaleRD[9]));
  sprintf(histName,"scaleScaleRD_59");
  scaleScaleRD[59] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleRD[7],*scaleRD[10]));
  
  sprintf(histName,"scaleScaleRD_60");
  scaleScaleRD[60] = new RooFormulaVar(histName,"1/sqrt(@0*@0)",RooArgSet(*scaleRD[8],*scaleRD[8]));
  sprintf(histName,"scaleScaleRD_61");
  scaleScaleRD[61] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleRD[8],*scaleRD[9]));
  sprintf(histName,"scaleScaleRD_62");
  scaleScaleRD[62] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleRD[8],*scaleRD[10]));
  
  sprintf(histName,"scaleScaleRD_63");
  scaleScaleRD[63] = new RooFormulaVar(histName,"1/sqrt(@0*@0)",RooArgSet(*scaleRD[9],*scaleRD[9]));
  sprintf(histName,"scaleScaleRD_64");
  scaleScaleRD[64] = new RooFormulaVar(histName,"1/sqrt(@0*@1)",RooArgSet(*scaleRD[9],*scaleRD[10]));
  
  sprintf(histName,"scaleScaleRD_65");
  scaleScaleRD[65] = new RooFormulaVar(histName,"1/sqrt(@0*@0)",RooArgSet(*scaleRD[10],*scaleRD[10]));
  
  
//*/


  //*
  ///smearSmear
  sprintf(histName,"smearSmearMC_0");
  smearSmearMC[0] = new RooFormulaVar(histName,"sqrt(@0*@0+@0*@0)",RooArgSet(*smearMC[0],*smearMC[0]));
  sprintf(histName,"smearSmearMC_1");
  smearSmearMC[1] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearMC[0],*smearMC[1]));
  sprintf(histName,"smearSmearMC_2");
  smearSmearMC[2] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearMC[0],*smearMC[2]));
  sprintf(histName,"smearSmearMC_3");
  smearSmearMC[3] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearMC[0],*smearMC[3]));
  sprintf(histName,"smearSmearMC_4");
  smearSmearMC[4] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearMC[0],*smearMC[4]));
  sprintf(histName,"smearSmearMC_5");
  smearSmearMC[5] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearMC[0],*smearMC[5]));
  sprintf(histName,"smearSmearMC_6");
  smearSmearMC[6] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearMC[0],*smearMC[6]));
  sprintf(histName,"smearSmearMC_7");
  smearSmearMC[7] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearMC[0],*smearMC[7]));
  sprintf(histName,"smearSmearMC_8");
  smearSmearMC[8] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearMC[0],*smearMC[8]));
  sprintf(histName,"smearSmearMC_9");
  smearSmearMC[9] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearMC[0],*smearMC[9]));
  sprintf(histName,"smearSmearMC_10");
  smearSmearMC[10] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearMC[0],*smearMC[10]));

  
  sprintf(histName,"smearSmearMC_11");
  smearSmearMC[11] = new RooFormulaVar(histName,"sqrt(@0*@0+@0*@0)",RooArgSet(*smearMC[1],*smearMC[1]));
  sprintf(histName,"smearSmearMC_12");
  smearSmearMC[12] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearMC[1],*smearMC[2]));
  sprintf(histName,"smearSmearMC_13");
  smearSmearMC[13] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearMC[1],*smearMC[3]));
  sprintf(histName,"smearSmearMC_14");
  smearSmearMC[14] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearMC[1],*smearMC[4]));
  sprintf(histName,"smearSmearMC_15");
  smearSmearMC[15] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearMC[1],*smearMC[5]));
  sprintf(histName,"smearSmearMC_16");
  smearSmearMC[16] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearMC[1],*smearMC[6]));
  sprintf(histName,"smearSmearMC_17");
  smearSmearMC[17] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearMC[1],*smearMC[7]));
  sprintf(histName,"smearSmearMC_18");
  smearSmearMC[18] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearMC[1],*smearMC[8]));
  sprintf(histName,"smearSmearMC_19");
  smearSmearMC[19] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearMC[1],*smearMC[9]));
  sprintf(histName,"smearSmearMC_20");
  smearSmearMC[20] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearMC[1],*smearMC[10]));

  sprintf(histName,"smearSmearMC_21");
  smearSmearMC[21] = new RooFormulaVar(histName,"sqrt(@0*@0+@0*@0)",RooArgSet(*smearMC[2],*smearMC[2]));
  sprintf(histName,"smearSmearMC_22");
  smearSmearMC[22] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearMC[2],*smearMC[3]));
  sprintf(histName,"smearSmearMC_23");
  smearSmearMC[23] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearMC[2],*smearMC[4]));
  sprintf(histName,"smearSmearMC_24");
  smearSmearMC[24] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearMC[2],*smearMC[5]));
  sprintf(histName,"smearSmearMC_25");
  smearSmearMC[25] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearMC[2],*smearMC[6]));
  sprintf(histName,"smearSmearMC_26");
  smearSmearMC[26] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearMC[2],*smearMC[7]));
  sprintf(histName,"smearSmearMC_27");
  smearSmearMC[27] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearMC[2],*smearMC[8]));
  sprintf(histName,"smearSmearMC_28");
  smearSmearMC[28] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearMC[2],*smearMC[9]));
  sprintf(histName,"smearSmearMC_29");
  smearSmearMC[29] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearMC[2],*smearMC[10]));

  sprintf(histName,"smearSmearMC_30");
  smearSmearMC[30] = new RooFormulaVar(histName,"sqrt(@0*@0+@0*@0)",RooArgSet(*smearMC[3],*smearMC[3]));
  sprintf(histName,"smearSmearMC_31");
  smearSmearMC[31] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearMC[3],*smearMC[4]));
  sprintf(histName,"smearSmearMC_32");
  smearSmearMC[32] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearMC[3],*smearMC[5]));
  sprintf(histName,"smearSmearMC_33");
  smearSmearMC[33] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearMC[3],*smearMC[6]));
  sprintf(histName,"smearSmearMC_34");
  smearSmearMC[34] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearMC[3],*smearMC[7]));
  sprintf(histName,"smearSmearMC_35");
  smearSmearMC[35] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearMC[3],*smearMC[8]));
  sprintf(histName,"smearSmearMC_36");
  smearSmearMC[36] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearMC[3],*smearMC[9]));
  sprintf(histName,"smearSmearMC_37");
  smearSmearMC[37] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearMC[3],*smearMC[10]));

  sprintf(histName,"smearSmearMC_38");
  smearSmearMC[38] = new RooFormulaVar(histName,"sqrt(@0*@0+@0*@0)",RooArgSet(*smearMC[4],*smearMC[4]));
  sprintf(histName,"smearSmearMC_39");
  smearSmearMC[39] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearMC[4],*smearMC[5]));
  sprintf(histName,"smearSmearMC_40");
  smearSmearMC[40] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearMC[4],*smearMC[6]));
  sprintf(histName,"smearSmearMC_41");
  smearSmearMC[41] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearMC[4],*smearMC[7]));
  sprintf(histName,"smearSmearMC_42");
  smearSmearMC[42] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearMC[4],*smearMC[8]));
  sprintf(histName,"smearSmearMC_43");
  smearSmearMC[43] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearMC[4],*smearMC[9]));
  sprintf(histName,"smearSmearMC_44");
  smearSmearMC[44] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearMC[4],*smearMC[10]));

  sprintf(histName,"smearSmearMC_45");
  smearSmearMC[45] = new RooFormulaVar(histName,"sqrt(@0*@0+@0*@0)",RooArgSet(*smearMC[5],*smearMC[5]));
  sprintf(histName,"smearSmearMC_46");
  smearSmearMC[46] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearMC[5],*smearMC[6]));
  sprintf(histName,"smearSmearMC_47");
  smearSmearMC[47] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearMC[5],*smearMC[7]));
  sprintf(histName,"smearSmearMC_48");
  smearSmearMC[48] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearMC[5],*smearMC[8]));
  sprintf(histName,"smearSmearMC_49");
  smearSmearMC[49] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearMC[5],*smearMC[9]));
  sprintf(histName,"smearSmearMC_50");
  smearSmearMC[50] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearMC[5],*smearMC[10]));

  sprintf(histName,"smearSmearMC_51");
  smearSmearMC[51] = new RooFormulaVar(histName,"sqrt(@0*@0+@0*@0)",RooArgSet(*smearMC[6],*smearMC[6]));
  sprintf(histName,"smearSmearMC_52");
  smearSmearMC[52] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearMC[6],*smearMC[7]));
  sprintf(histName,"smearSmearMC_53");
  smearSmearMC[53] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearMC[6],*smearMC[8]));
  sprintf(histName,"smearSmearMC_54");
  smearSmearMC[54] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearMC[6],*smearMC[9]));
  sprintf(histName,"smearSmearMC_55");
  smearSmearMC[55] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearMC[6],*smearMC[10]));
  
  sprintf(histName,"smearSmearMC_56");
  smearSmearMC[56] = new RooFormulaVar(histName,"sqrt(@0*@0+@0*@0)",RooArgSet(*smearMC[7],*smearMC[7]));
  sprintf(histName,"smearSmearMC_57");
  smearSmearMC[57] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearMC[7],*smearMC[8]));
  sprintf(histName,"smearSmearMC_58");
  smearSmearMC[58] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearMC[7],*smearMC[9]));
  sprintf(histName,"smearSmearMC_59");
  smearSmearMC[59] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearMC[7],*smearMC[10]));
  
  sprintf(histName,"smearSmearMC_60");
  smearSmearMC[60] = new RooFormulaVar(histName,"sqrt(@0*@0+@0*@0)",RooArgSet(*smearMC[8],*smearMC[8]));
  sprintf(histName,"smearSmearMC_61");
  smearSmearMC[61] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearMC[8],*smearMC[9]));
  sprintf(histName,"smearSmearMC_62");
  smearSmearMC[62] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearMC[8],*smearMC[10]));
  
  sprintf(histName,"smearSmearMC_63");
  smearSmearMC[63] = new RooFormulaVar(histName,"sqrt(@0*@0+@0*@0)",RooArgSet(*smearMC[9],*smearMC[9]));
  sprintf(histName,"smearSmearMC_64");
  smearSmearMC[64] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearMC[9],*smearMC[10]));
  
  sprintf(histName,"smearSmearMC_65");
  smearSmearMC[65] = new RooFormulaVar(histName,"sqrt(@0*@0+@0*@0)",RooArgSet(*smearMC[10],*smearMC[10]));
  
  
  
//*/  


  //*
  ///smearSmear
  sprintf(histName,"smearSmearRD_0");
  smearSmearRD[0] = new RooFormulaVar(histName,"sqrt(@0*@0+@0*@0)",RooArgSet(*smearRD[0],*smearRD[0]));
  sprintf(histName,"smearSmearRD_1");
  smearSmearRD[1] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearRD[0],*smearRD[1]));
  sprintf(histName,"smearSmearRD_2");
  smearSmearRD[2] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearRD[0],*smearRD[2]));
  sprintf(histName,"smearSmearRD_3");
  smearSmearRD[3] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearRD[0],*smearRD[3]));
  sprintf(histName,"smearSmearRD_4");
  smearSmearRD[4] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearRD[0],*smearRD[4]));
  sprintf(histName,"smearSmearRD_5");
  smearSmearRD[5] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearRD[0],*smearRD[5]));
  sprintf(histName,"smearSmearRD_6");
  smearSmearRD[6] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearRD[0],*smearRD[6]));
  sprintf(histName,"smearSmearRD_7");
  smearSmearRD[7] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearRD[0],*smearRD[7]));
  sprintf(histName,"smearSmearRD_8");
  smearSmearRD[8] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearRD[0],*smearRD[8]));
  sprintf(histName,"smearSmearRD_9");
  smearSmearRD[9] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearRD[0],*smearRD[9]));
  sprintf(histName,"smearSmearRD_10");
  smearSmearRD[10] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearRD[0],*smearRD[10]));

  sprintf(histName,"smearSmearRD_11");
  smearSmearRD[11] = new RooFormulaVar(histName,"sqrt(@0*@0+@0*@0)",RooArgSet(*smearRD[1],*smearRD[1]));
  sprintf(histName,"smearSmearRD12");
  smearSmearRD[12] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearRD[1],*smearRD[2]));
  sprintf(histName,"smearSmearRD_13");
  smearSmearRD[13] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearRD[1],*smearRD[3]));
  sprintf(histName,"smearSmearRD_14");
  smearSmearRD[14] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearRD[1],*smearRD[4]));
  sprintf(histName,"smearSmearRD_15");
  smearSmearRD[15] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearRD[1],*smearRD[5]));
  sprintf(histName,"smearSmearRD_16");
  smearSmearRD[16] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearRD[1],*smearRD[6]));
  sprintf(histName,"smearSmearRD_17");
  smearSmearRD[17] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearRD[1],*smearRD[7]));
  sprintf(histName,"smearSmearRD_18");
  smearSmearRD[18] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearRD[1],*smearRD[8]));
  sprintf(histName,"smearSmearRD_19");
  smearSmearRD[19] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearRD[1],*smearRD[9]));
  sprintf(histName,"smearSmearRD_20");
  smearSmearRD[20] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearRD[1],*smearRD[10]));

  sprintf(histName,"smearSmearRD_21");
  smearSmearRD[21] = new RooFormulaVar(histName,"sqrt(@0*@0+@0*@0)",RooArgSet(*smearRD[2],*smearRD[2]));
  sprintf(histName,"smearSmearRD_22");
  smearSmearRD[22] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearRD[2],*smearRD[3]));
  sprintf(histName,"smearSmearRD_23");
  smearSmearRD[23] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearRD[2],*smearRD[4]));
  sprintf(histName,"smearSmearRD_24");
  smearSmearRD[24] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearRD[2],*smearRD[5]));
  sprintf(histName,"smearSmearRD_25");
  smearSmearRD[25] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearRD[2],*smearRD[6]));
  sprintf(histName,"smearSmearRD_26");
  smearSmearRD[26] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearRD[2],*smearRD[7]));
  sprintf(histName,"smearSmearRD_27");
  smearSmearRD[27] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearRD[2],*smearRD[8]));
  sprintf(histName,"smearSmearRD_28");
  smearSmearRD[28] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearRD[2],*smearRD[9]));
  sprintf(histName,"smearSmearRD_29");
  smearSmearRD[29] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearRD[2],*smearRD[10]));

  sprintf(histName,"smearSmearRD_30");
  smearSmearRD[30] = new RooFormulaVar(histName,"sqrt(@0*@0+@0*@0)",RooArgSet(*smearRD[3],*smearRD[3]));
  sprintf(histName,"smearSmearRD_31");
  smearSmearRD[31] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearRD[3],*smearRD[4]));
  sprintf(histName,"smearSmearRD_32");
  smearSmearRD[32] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearRD[3],*smearRD[5]));
  sprintf(histName,"smearSmearRD_33");
  smearSmearRD[33] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearRD[3],*smearRD[6]));
  sprintf(histName,"smearSmearRD_34");
  smearSmearRD[34] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearRD[3],*smearRD[7]));
  sprintf(histName,"smearSmearRD_35");
  smearSmearRD[35] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearRD[3],*smearRD[8]));
  sprintf(histName,"smearSmearRD_36");
  smearSmearRD[36] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearRD[3],*smearRD[9]));
  sprintf(histName,"smearSmearRD_37");
  smearSmearRD[37] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearRD[3],*smearRD[10]));

  sprintf(histName,"smearSmearRD_38");
  smearSmearRD[38] = new RooFormulaVar(histName,"sqrt(@0*@0+@0*@0)",RooArgSet(*smearRD[4],*smearRD[4]));
  sprintf(histName,"smearSmearRD_39");
  smearSmearRD[39] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearRD[4],*smearRD[5]));
  sprintf(histName,"smearSmearRD_40");
  smearSmearRD[40] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearRD[4],*smearRD[6]));
  sprintf(histName,"smearSmearRD_41");
  smearSmearRD[41] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearRD[4],*smearRD[7]));
  sprintf(histName,"smearSmearRD_42");
  smearSmearRD[42] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearRD[4],*smearRD[8]));
  sprintf(histName,"smearSmearRD_43");
  smearSmearRD[43] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearRD[4],*smearRD[9]));
  sprintf(histName,"smearSmearRD_44");
  smearSmearRD[44] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearRD[4],*smearRD[10]));

  sprintf(histName,"smearSmearRD_45");
  smearSmearRD[45] = new RooFormulaVar(histName,"sqrt(@0*@0+@0*@0)",RooArgSet(*smearRD[5],*smearRD[5]));
  sprintf(histName,"smearSmearRD_46");
  smearSmearRD[46] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearRD[5],*smearRD[6]));
  sprintf(histName,"smearSmearRD_47");
  smearSmearRD[47] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearRD[5],*smearRD[7]));
  sprintf(histName,"smearSmearRD_48");
  smearSmearRD[48] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearRD[5],*smearRD[8]));
  sprintf(histName,"smearSmearRD_49");
  smearSmearRD[49] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearRD[5],*smearRD[9]));
  sprintf(histName,"smearSmearRD_50");
  smearSmearRD[50] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearRD[5],*smearRD[10]));

  sprintf(histName,"smearSmearRD_51");
  smearSmearRD[51] = new RooFormulaVar(histName,"sqrt(@0*@0+@0*@0)",RooArgSet(*smearRD[6],*smearRD[6]));
  sprintf(histName,"smearSmearRD_52");
  smearSmearRD[52] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearRD[6],*smearRD[7]));
  sprintf(histName,"smearSmearRD_53");
  smearSmearRD[53] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearRD[6],*smearRD[8]));
  sprintf(histName,"smearSmearRD_54");
  smearSmearRD[54] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearRD[6],*smearRD[9]));
  sprintf(histName,"smearSmearRD_55");
  smearSmearRD[55] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearRD[6],*smearRD[10]));
  
  sprintf(histName,"smearSmearRD_56");
  smearSmearRD[56] = new RooFormulaVar(histName,"sqrt(@0*@0+@0*@0)",RooArgSet(*smearRD[7],*smearRD[7]));
  sprintf(histName,"smearSmearRD_57");
  smearSmearRD[57] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearRD[7],*smearRD[8]));
  sprintf(histName,"smearSmearRD_58");
  smearSmearRD[58] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearRD[7],*smearRD[9]));
  sprintf(histName,"smearSmearRD_59");
  smearSmearRD[59] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearRD[7],*smearRD[10]));
  
  sprintf(histName,"smearSmearRD_60");
  smearSmearRD[60] = new RooFormulaVar(histName,"sqrt(@0*@0+@0*@0)",RooArgSet(*smearRD[8],*smearRD[8]));
  sprintf(histName,"smearSmearRD_61");
  smearSmearRD[61] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearRD[8],*smearRD[9]));
  sprintf(histName,"smearSmearRD_62");
  smearSmearRD[62] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearRD[8],*smearRD[10]));
  
  sprintf(histName,"smearSmearRD_63");
  smearSmearRD[63] = new RooFormulaVar(histName,"sqrt(@0*@0+@0*@0)",RooArgSet(*smearRD[9],*smearRD[9]));
  sprintf(histName,"smearSmearRD_64");
  smearSmearRD[64] = new RooFormulaVar(histName,"sqrt(@0*@0+@1*@1)",RooArgSet(*smearRD[9],*smearRD[10]));
  
  sprintf(histName,"smearSmearRD_65");
  smearSmearRD[65] = new RooFormulaVar(histName,"sqrt(@0*@0+@0*@0)",RooArgSet(*smearRD[10],*smearRD[10]));

//*/

  RooRealVar gaussMean("gaussMean","gaussMean",0);
  gaussMean.setConstant(kTRUE);
  RooRealVar CBMean("CBMean","CBMean",0);
  CBMean.setConstant(kTRUE);
  for(int i(0);i<ScElCombiBinsHighPU;i++)
  {
    //Getting histogram from RD & MC
    sprintf(histName,"h1_ZmassDaughEta_%d",i);
    h1_ZmassDaughEtaMC[i] = (TH1D*)f_MC->Get(histName)->Clone(histName);
    h1_ZmassDaughEtaRD[i] = (TH1D*)f_RD->Get(histName)->Clone(histName);

    sprintf(histName,"ZmassRD_%d",i);
    ZmassRD[i] =
     new RooDataHist(histName,histName,RooArgSet(zMass),h1_ZmassDaughEtaRD[i]);

    sprintf(histName,"cat_%d",i);
    hmapMC[histName] = h1_ZmassDaughEtaMC[i];
    sprintf(histName,"cat_%d",i);
    hmapRD[histName] = h1_ZmassDaughEtaRD[i];

    // Making template from MC
    sprintf(histName,"ZmassMC_%d",i);
    ZmassMC[i] = new RooDataHist(histName,histName,RooArgSet(zMass),h1_ZmassDaughEtaMC[i]);
    
    sprintf(histName,"cbMC_%d",i);
    cbMC[i] = new RooCBShape(histName,histName,zMass,CBMean,*smearSmearMC[i],*CBalpha[i],*CBn[i]);
    sprintf(histName,"BWMC_%d",i);
    BWMC[i] = new CBreitWignerMC(histName,zMass, scaleScaleMC[i]);

    sprintf(histName,"pdfMCsig_%d",i);
    pdfMCsig[i] = new RooFFTConvPdf(histName,histName,zMass,*(BWMC[i]->model),*cbMC[i]);


    //Making RD pdf
//    sprintf(histName,"gaus_%d",i);
//    gaus[i] = new RooGaussian(histName,histName,zMass,gaussMean,*smearSmearRD[i]);
   
//    sprintf(histName,"BWCBsCale_%d",i);
//    BWCBsCale[i] = new CBreitWignerConvCrystalBallScale
 //     (histName,zMass, scaleScaleRD[i],
 //     BWCB[i]->mean->getVal(),BWCB[i]->sigma->getVal(),BWCB[i]->alpha->getVal(),BWCB[i]->n->getVal());

//*

    sprintf(histName,"cbRD_%d",i);
    cbRD[i] = new RooCBShape(histName,histName,zMass,CBMean,*smearSmearRD[i],*CBalpha[i],*CBn[i]);

    sprintf(histName,"BWRD_%d",i);
    BWRD[i] = new CBreitWignerRD(histName,zMass, scaleScaleRD[i]);
  sprintf(histName,"pdfRDsig_%d",i);
  //  pdfRDsig[i] = new RooFFTConvPdf(histName,histName,zMass,*(BWCBsCale[i]->model),*gaus[i]);
  pdfRDsig[i] = new RooFFTConvPdf(histName,histName,zMass,*(BWRD[i]->model),*cbRD[i]);
    

    
    sprintf(histName,"cat_%d",i);
    pdfTotalMC.addPdf(*pdfMCsig[i],histName);
 
    sprintf(histName,"cat_%d",i);
    pdfTotalRD.addPdf(*pdfRDsig[i],histName);
  
}
 RooDataHist MCTotal("MCTotal","MCTotal",zMass,rooCat,hmapMC);
 fitResTotalMC = pdfTotalMC.fitTo(MCTotal,Minos(kTRUE),Save(kTRUE),SumW2Error(kTRUE));

 RooDataHist dataTotal("dataTotal","dataTotal",zMass,rooCat,hmapRD);
 fitResTotalRD = pdfTotalRD.fitTo(dataTotal,Minos(kTRUE),Save(kTRUE),SumW2Error(kTRUE));

 Fout<<"bin range \t scale \t smear "<<endl;

  for(int i(0);i<ScaleBinsHighPU;i++)
  {
    cout<<" "<<i<<"\t"<<scaleMC[i]->getVal()<<"+"<<scaleMC[i]->getError()<<"\t"<<smearMC[i]->getVal()<<"+"<<smearMC[i]->getError()<<endl;
    Fout<<" "<<i<<"\t"<<scaleMC[i]->getVal()<<"+"<<scaleMC[i]->getError()<<"\t"<<smearMC[i]->getVal()<<"+"<<smearMC[i]->getError()<<endl;
  
    cout<<" "<<i<<"\t"<<scaleRD[i]->getVal()<<"+"<<scaleRD[i]->getError()<<"\t"<<smearRD[i]->getVal()<<"+"<<smearRD[i]->getError()<<endl;
    Fout<<" "<<i<<"\t"<<scaleRD[i]->getVal()<<"+"<<scaleRD[i]->getError()<<"\t"<<smearRD[i]->getVal()<<"+"<<smearRD[i]->getError()<<endl;
 



cout<<" "<<i<<"\t"<<scaleRD[i]->getVal()/scaleMC[i]->getVal()<<"+-"<<(scaleRD[i]->getVal()/scaleMC[i]->getVal())*sqrt((scaleRD[i]->getError()*scaleRD[i]->getError())/scaleRD[i]->getVal()/scaleRD[i]->getVal()+(scaleMC[i]->getError()*scaleMC[i]->getError())/scaleMC[i]->getVal()/scaleMC[i]->getVal())<<"\t"<<smearRD[i]->getVal()- smearMC[i]->getVal()<<"+"<<sqrt(smearRD[i]->getError()*smearRD[i]->getError()+ smearMC[i]->getError()*smearMC[i]->getError())<<endl;

  
Fout<<" "<<i<<"\t"<<scaleRD[i]->getVal()/scaleMC[i]->getVal()<<"+-"<<(scaleRD[i]->getVal()/scaleMC[i]->getVal())*sqrt((scaleRD[i]->getError()*scaleRD[i]->getError())/scaleRD[i]->getVal()/scaleRD[i]->getVal()+(scaleMC[i]->getError()*scaleMC[i]->getError())/scaleMC[i]->getVal()/scaleMC[i]->getVal())<<"\t"<<smearRD[i]->getVal()- smearMC[i]->getVal()<<"+"<<sqrt(smearRD[i]->getError()*smearRD[i]->getError()+ smearMC[i]->getError()*smearMC[i]->getError())<<endl;

  }
//*
  for(int i(0);i<ScElCombiBinsHighPU;i++)
  {
    //*
    zmassFrameMC = zMass.frame();
     ZmassMC[i]->plotOn(zmassFrameMC,DrawOption("p"));
     pdfMCsig[i]->plotOn(zmassFrameMC,DrawOption("l"));
     sprintf(histName,"ZmassMC_%s_%d",BaseName,i);

     plotFitMC = new CPlot(histName,zmassFrameMC,"","Di-Lepton M","");
     plotFitMC->setOutDir(ResultDir);
     plotFitMC->Draw(myCan,kTRUE,"png");
//*/
     zmassFrameRD = zMass.frame();
     ZmassRD[i]->plotOn(zmassFrameRD,DrawOption("p"));
     pdfRDsig[i]->plotOn(zmassFrameRD,DrawOption("l"));
     sprintf(histName,"ZmassRD_%s_%d",BaseName,i);

     plotFitRD = new CPlot(histName,zmassFrameRD,"","Di-Lepton M","");
     plotFitRD->setOutDir(ResultDir);
     plotFitRD->Draw(myCan,kTRUE,"png");
  }
//*/  
  Fout.close();
  return 0;
}
