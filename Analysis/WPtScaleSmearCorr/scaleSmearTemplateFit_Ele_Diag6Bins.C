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

int scaleSmearTemplateFit_Ele_Diag6Bins(TString RDFile, TString MCFile, char BaseName[30])
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
  TH1D *h1_ZmassDaughEtaRD[ScElCombiBinsDiag];
  TH1D *h1_ZmassDaughEtaMC[ScElCombiBinsDiag];

  //Plots
  RooPlot *zmassFrameRD;
  RooPlot *zmassFrameMC;
  CPlot *plotFitRD;
  CPlot *plotFitMC;
  RooFitResult* fitResTotalMC;
  RooFitResult* fitResTotalRD;
  //RooFitResult* fitResRD;
  RooFitResult* fitResMCbw[ScElCombiBinsDiag];
  RooFitResult* fitResMC[ScElCombiBinsDiag];
  RooFitResult* fitResRD[ScElCombiBinsDiag];

  TCanvas *myCan = MakeCanvas("myCan","myCan",800,600);
  //Fitting stuff
  RooRealVar *scaleMC[ScaleBins];
  RooRealVar *scaleRD[ScaleBins];
  RooRealVar *smearRD[ScaleBins];
  RooRealVar *smearMC[ScaleBins];


  RooRealVar *nSRD[ScElCombiBinsDiag];
  RooRealVar *nBRD[ScElCombiBinsDiag];
  RooRealVar *CBalpha[ScElCombiBinsDiag];
  RooRealVar *CBalphaMC[ScElCombiBinsDiag];
  RooRealVar *CBn[ScElCombiBinsDiag];

  RooFormulaVar *scaleScaleMC[ScElCombiBinsDiag];
  RooFormulaVar *scaleScaleRD[ScElCombiBinsDiag];
  RooFormulaVar *smearSmearMC[ScElCombiBinsDiag];
  RooFormulaVar *smearSmearRD[ScElCombiBinsDiag];

  RooRealVar zMass("zMass","zMass",60,120);
  RooCategory rooCat("rooCat","rooCat");
  RooDataHist *ZmassRD[ScElCombiBinsDiag];

// RooDataHist *ZmassMC;
 RooDataHist *ZmassMC[ScElCombiBinsDiag];
//  CBreitWigner *BW[ScElCombiBinsDiag];
  CBreitWignerConvCrystalBall *BWCB[ScElCombiBinsDiag];
  CBreitWignerConvCrystalBallScale *BWCBsCale[ScElCombiBinsDiag];
  CBreitWignerMC  *BWMC[ScElCombiBinsDiag];
  CBreitWignerRD  *BWRD[ScElCombiBinsDiag];

  //RooGaussian *gaus[ScElCombiBinsDiag];
  RooCBShape *cbMC[ScElCombiBinsDiag];
  RooCBShape *cbRD[ScElCombiBinsDiag];

  //CErfExpo *ZbgRD[ScElCombiBinsDiag];
  //CExponential *ZbgExpRD[ScElCombiBinsDiag];

  RooAbsPdf *pdfRDsig[ScElCombiBinsDiag];
  RooAbsPdf *pdfMCsig[ScElCombiBinsDiag];
  //RooAddPdf *pdfRDsig[ScElCombiBinsDiag];
  RooAbsPdf *histPdf[ScElCombiBinsDiag];
  RooAddPdf *pdfRD[ScElCombiBinsDiag];


  //Initialization
  for(int i(0);i<ScaleBins;i++)
  {
    sprintf(histName,"scaleMC_%d",i);
    scaleMC[i] = new RooRealVar(histName, histName,1.01,0.001,3);
    sprintf(histName,"scaleRD_%d",i);
    scaleRD[i] = new RooRealVar(histName, histName,1.01,0.001,3);

   // sprintf(histName,"smearMC_%d",i);
    //smearMC[i] = new RooRealVar(histName,histName,0.5,0.01,3);
    //smearMC[i] = new RooRealVar(histName,histName,2.4952,0.,3.);
    //smearMC[i] = new RooRealVar(histName,histName,0.,1.);
    sprintf(histName,"smearMC_%d",0);
    smearMC[0] = new RooRealVar(histName,histName,0.,0.3);
    sprintf(histName,"smearMC_%d",1);
    smearMC[1] = new RooRealVar(histName,histName,0.5,0.01,10);
    sprintf(histName,"smearMC_%d",2);
    smearMC[2] = new RooRealVar(histName,histName,0.5,0.01,1);
    sprintf(histName,"smearMC_%d",3);
    smearMC[3] = new RooRealVar(histName,histName,0.,5);
    sprintf(histName,"smearMC_%d",4);
    smearMC[4] = new RooRealVar(histName,histName,0.5,0.01,3);
    sprintf(histName,"smearMC_%d",5);
    smearMC[5] = new RooRealVar(histName,histName,0.5,0.01,3);
    
    
    sprintf(histName,"smearRD_%d",i);
    smearRD[i] = new RooRealVar(histName,histName,0.5,0.01,3);
  }

  for(int i(0);i<ScElCombiBinsDiag;i++)
  {
    sprintf(histName,"nBRD_%d",i);
    nBRD[i] = new RooRealVar(histName, histName,0.1,0.01,1);
    sprintf(histName,"nSRD_%d",i);
    nSRD[i]= new RooRealVar(histName,histName,1,0,2);
    
    sprintf(histName,"CBalpha_%d",i); 
    CBalpha[i]= new RooRealVar(histName,histName,5,0,20);
    //CBalpha[i]= new RooRealVar(histName,histName,0.1,0,1);
   
    //sprintf(histName,"CBalphaMC_%d",0); 
    //CBalphaMC[0]= new RooRealVar(histName,histName,5,0,10);
    //sprintf(histName,"CBalphaMC_%d",1); 
    //CBalphaMC[1]= new RooRealVar(histName,histName,5,0,10);
    //sprintf(histName,"CBalphaMC_%d",2); 
    //CBalphaMC[2]= new RooRealVar(histName,histName,5,0,10);
    //sprintf(histName,"CBalphaMC_%d",3); 
    //CBalphaMC[3]= new RooRealVar(histName,histName,5,0,10);
    //sprintf(histName,"CBalphaMC_%d",4); 
    //CBalphaMC[4]= new RooRealVar(histName,histName,5,0,10);
    //sprintf(histName,"CBalphaMC_%d",5); 
    //CBalphaMC[5]= new RooRealVar(histName,histName,5,0,10);
    
    
    
    sprintf(histName,"CBn_%d",i);     
    CBn[i]     = new RooRealVar(histName,histName,1,0,10);
    //CBn[i]     = new RooRealVar(histName,histName,1,0,5);

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
  scaleScaleMC[1] = new RooFormulaVar(histName,"1/sqrt(@0*@0)",RooArgSet(*scaleMC[1],*scaleMC[1]));
  
  sprintf(histName,"scaleScaleMC_2");
  scaleScaleMC[2] = new RooFormulaVar(histName,"1/sqrt(@0*@0)",RooArgSet(*scaleMC[2],*scaleMC[2]));

  sprintf(histName,"scaleScaleMC_3");
  scaleScaleMC[3] = new RooFormulaVar(histName,"1/sqrt(@0*@0)",RooArgSet(*scaleMC[3],*scaleMC[3]));

  sprintf(histName,"scaleScaleMC_4");
  scaleScaleMC[4] = new RooFormulaVar(histName,"1/sqrt(@0*@0)",RooArgSet(*scaleMC[4],*scaleMC[4]));

  sprintf(histName,"scaleScaleMC_5");
  scaleScaleMC[5] = new RooFormulaVar(histName,"1/sqrt(@0*@0)",RooArgSet(*scaleMC[5],*scaleMC[5]));
  //*/


  //*
  ///scaleScale
  sprintf(histName,"scaleScaleRD_0");
  scaleScaleRD[0] = new RooFormulaVar(histName,"1/sqrt(@0*@0)",RooArgSet(*scaleRD[0],*scaleRD[0]));
  
  sprintf(histName,"scaleScaleRD_1");
  scaleScaleRD[1] = new RooFormulaVar(histName,"1/sqrt(@0*@0)",RooArgSet(*scaleRD[1],*scaleRD[1]));

  sprintf(histName,"scaleScaleRD_2");
  scaleScaleRD[2] = new RooFormulaVar(histName,"1/sqrt(@0*@0)",RooArgSet(*scaleRD[2],*scaleRD[2]));

  sprintf(histName,"scaleScaleRD_3");
  scaleScaleRD[3] = new RooFormulaVar(histName,"1/sqrt(@0*@0)",RooArgSet(*scaleRD[3],*scaleRD[3]));

  sprintf(histName,"scaleScaleRD_4");
  scaleScaleRD[4] = new RooFormulaVar(histName,"1/sqrt(@0*@0)",RooArgSet(*scaleRD[4],*scaleRD[4]));

  sprintf(histName,"scaleScaleRD_5");
  scaleScaleRD[5] = new RooFormulaVar(histName,"1/sqrt(@0*@0)",RooArgSet(*scaleRD[5],*scaleRD[5]));
//*/


  //*
  ///smearSmear
  sprintf(histName,"smearSmearMC_0");
  smearSmearMC[0] = new RooFormulaVar(histName,"sqrt(@0*@0+@0*@0)",RooArgSet(*smearMC[0],*smearMC[0]));
  
  sprintf(histName,"smearSmearMC_1");
  smearSmearMC[1] = new RooFormulaVar(histName,"sqrt(@0*@0+@0*@0)",RooArgSet(*smearMC[1],*smearMC[1]));

  sprintf(histName,"smearSmearMC_2");
  smearSmearMC[2] = new RooFormulaVar(histName,"sqrt(@0*@0+@0*@0)",RooArgSet(*smearMC[2],*smearMC[2]));

  sprintf(histName,"smearSmearMC_3");
  smearSmearMC[3] = new RooFormulaVar(histName,"sqrt(@0*@0+@0*@0)",RooArgSet(*smearMC[3],*smearMC[3]));

  sprintf(histName,"smearSmearMC_4");
  smearSmearMC[4] = new RooFormulaVar(histName,"sqrt(@0*@0+@0*@0)",RooArgSet(*smearMC[4],*smearMC[4]));

  sprintf(histName,"smearSmearMC_5");
  smearSmearMC[5] = new RooFormulaVar(histName,"sqrt(@0*@0+@0*@0)",RooArgSet(*smearMC[5],*smearMC[5]));
//*/  


  //*
  ///smearSmear
  sprintf(histName,"smearSmearRD_0");
  smearSmearRD[0] = new RooFormulaVar(histName,"sqrt(@0*@0+@0*@0)",RooArgSet(*smearRD[0],*smearRD[0]));
  
  sprintf(histName,"smearSmearRD_1");
  smearSmearRD[1] = new RooFormulaVar(histName,"sqrt(@0*@0+@0*@0)",RooArgSet(*smearRD[1],*smearRD[1]));

  sprintf(histName,"smearSmearRD_2");
  smearSmearRD[2] = new RooFormulaVar(histName,"sqrt(@0*@0+@0*@0)",RooArgSet(*smearRD[2],*smearRD[2]));

  sprintf(histName,"smearSmearRD_3");
  smearSmearRD[3] = new RooFormulaVar(histName,"sqrt(@0*@0+@0*@0)",RooArgSet(*smearRD[3],*smearRD[3]));

  sprintf(histName,"smearSmearRD_4");
  smearSmearRD[4] = new RooFormulaVar(histName,"sqrt(@0*@0+@0*@0)",RooArgSet(*smearRD[4],*smearRD[4]));

  sprintf(histName,"smearSmearRD_5");
  smearSmearRD[5] = new RooFormulaVar(histName,"sqrt(@0*@0+@0*@0)",RooArgSet(*smearRD[5],*smearRD[5]));
//*/

  RooRealVar gaussMean("gaussMean","gaussMean",0);
  gaussMean.setConstant(kTRUE);
  RooRealVar CBMean("CBMean","CBMean",0);
  CBMean.setConstant(kTRUE);
  for(int i(0);i<ScElCombiBinsDiag;i++)
  {
    //Getting histogram from RD & MC
    sprintf(histName,"h1_ZmassDaughEtaEleDiag_%d",i);
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

  for(int i(0);i<ScaleBins;i++)
  {
//    cout<<" "<<i<<"\t"<<scaleMC[i]->getVal()<<"+"<<scaleMC[i]->getError()<<"\t"<<smearMC[i]->getVal()<<"+"<<smearMC[i]->getError()<<endl;
//    Fout<<" "<<i<<"\t"<<scaleMC[i]->getVal()<<"+"<<scaleMC[i]->getError()<<"\t"<<smearMC[i]->getVal()<<"+"<<smearMC[i]->getError()<<endl;
  
//    cout<<" "<<i<<"\t"<<scaleRD[i]->getVal()<<"+"<<scaleRD[i]->getError()<<"\t"<<smearRD[i]->getVal()<<"+"<<smearRD[i]->getError()<<endl;
//    Fout<<" "<<i<<"\t"<<scaleRD[i]->getVal()<<"+"<<scaleRD[i]->getError()<<"\t"<<smearRD[i]->getVal()<<"+"<<smearRD[i]->getError()<<endl;
 



cout<<" "<<i<<"\t"<<scaleRD[i]->getVal()/scaleMC[i]->getVal()<<"+-"<<(scaleRD[i]->getVal()/scaleMC[i]->getVal())*sqrt((scaleRD[i]->getError()*scaleRD[i]->getError())/scaleRD[i]->getVal()/scaleRD[i]->getVal()+(scaleMC[i]->getError()*scaleMC[i]->getError())/scaleMC[i]->getVal()/scaleMC[i]->getVal())<<"\t"<<smearRD[i]->getVal()- smearMC[i]->getVal()<<"+"<<sqrt(smearRD[i]->getError()*smearRD[i]->getError()+ smearMC[i]->getError()*smearMC[i]->getError())<<endl;

  
Fout<<" "<<i<<"\t"<<scaleRD[i]->getVal()/scaleMC[i]->getVal()<<"+-"<<(scaleRD[i]->getVal()/scaleMC[i]->getVal())*sqrt((scaleRD[i]->getError()*scaleRD[i]->getError())/scaleRD[i]->getVal()/scaleRD[i]->getVal()+(scaleMC[i]->getError()*scaleMC[i]->getError())/scaleMC[i]->getVal()/scaleMC[i]->getVal())<<"\t"<<smearRD[i]->getVal()- smearMC[i]->getVal()<<"+"<<sqrt(smearRD[i]->getError()*smearRD[i]->getError()+ smearMC[i]->getError()*smearMC[i]->getError())<<endl;

  }
//*
  for(int i(0);i<ScElCombiBinsDiag;i++)
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
