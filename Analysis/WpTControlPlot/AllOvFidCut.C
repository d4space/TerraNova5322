#include "TStyle.h"
#include "../Utils/MyTools.hh"	          // various helper functions
#include "../Utils/CPlot.hh"	          // helper class for plots
#include "../Utils/MitStyleRemix.hh"      // style settings for drawing
#include "../Utils/const.h"
//#include <iostream>
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

#if not defined(__CINT__) || defined(__MAKECINT__)
#include "TSVDUnfold.h"
#endif
 
//#define TSVDSelfTestPost

int AllOvFidCut(TString BaseName)
{
  TString resultDir = BaseName+"_Result";
  
  gSystem->mkdir(resultDir,kTRUE);
  CPlot::sOutDir = resultDir;

  char tmpName[30];
  char tmpNameOrg[30];
  
  const TString format("png"); 
  
  ofstream Fout;
  Fout.open(resultDir+"/Ratio.txt");

  Fout << "All Cut / Fiducial Cut"<< endl;
  Fout << "=============================================================" << endl;
  Fout << "Bin" << "\t" << "Ratio" << endl;
  
  TFile *fName;
  
  if(BaseName=="WpToMuNu")
    fName = new TFile("Muon2012LoPU/WpToMuNu_S8_NoCorr.root");
  if(BaseName=="WmToMuNu")
    fName = new TFile("Muon2012LoPU/WmToMuNu_S8_NoCorr.root");

  double WptBins[7]={0,7.5,12.5,17.5,50,110,600};
  
  //const Int_t bin=6;
  const Int_t bin=3;
  TH1D* h1_AllCut[bin];
  TH1D* h1_FidCut[bin];
  TH1D* h1_Ratio[bin];

  // Plot
  CPlot *pltRatio;
  TCanvas *myCan;
  myCan = MakeCanvas("myCan","myCan",800,800);
  gStyle->SetEndErrorSize(7);

  char legendName[30];

  //======================
  // Histo from root
  //======================
  for(int i(0);i<bin;i++)
  {
    sprintf(tmpNameOrg,"h1_PlusLepPtAllCut_%d",i);
    if(BaseName=="WmToMuNu")
      sprintf(tmpNameOrg,"h1_MinuLepPtAllCut_%d",i);
    sprintf(tmpName,"h1_AllCut_%d",i);
    h1_AllCut[i] = (TH1D*)fName->Get(tmpNameOrg)->Clone(tmpName);
    h1_AllCut[i]-> Sumw2();

    sprintf(tmpNameOrg,"h1_PlusLepPtFidCut_%d",i);
    if(BaseName=="WmToMuNu")
      sprintf(tmpNameOrg,"h1_MinuLepPtFidCut_%d",i);
    sprintf(tmpName,"h1_FidCut_%d",i);
    h1_FidCut[i] = (TH1D*)fName->Get(tmpNameOrg)->Clone(tmpName);
    h1_FidCut[i]-> Sumw2();
    
    sprintf(tmpName,"h1_Ratio_%d",i);
    h1_Ratio[i] = (TH1D*)h1_AllCut[i]->Clone(tmpName);
    h1_Ratio[i]->Sumw2();
    h1_Ratio[i]->Divide(h1_FidCut[i]);
    
    Fout<<""<<endl;
    Fout<<"Wpt Bin: "<<WptBins[i]<<" < WpT < "<<WptBins[i+1]<<endl;
    Fout<<"AllCut\t FidCut\t AllCut/FidCut"<<endl;
    for(int ipt(1);ipt<=h1_AllCut[i]->GetNbinsX(); ipt++)
    {
      Fout<<h1_AllCut[i]->GetBinContent(ipt)<<"\t"<<h1_FidCut[i]->GetBinContent(ipt)<<"\t"<<h1_Ratio[i]->GetBinContent(ipt)<<endl;
    }
  }
  
  h1_Ratio[0]->SetMarkerColor(1); 
  h1_Ratio[1]->SetMarkerColor(2);
  h1_Ratio[2]->SetMarkerColor(4);
  //h1_Ratio[3]->SetMarkerColor(3);
  //h1_Ratio[4]->SetMarkerColor(7);
  //h1_Ratio[5]->SetMarkerColor(4);

  sprintf(tmpName,BaseName+"_Ratio");
  pltRatio= new CPlot(tmpName,"","Muon p_{T} [GeV/c]","AllCut/FidCut");
  pltRatio->setOutDir(CPlot::sOutDir);
  //pltRatio->AddHist1D(h1_Ratio[0],"0<p_{T}<7.5","E1",kBlack,1);
  //pltRatio->AddHist1D(h1_Ratio[1],"7.5<p_{T}<12.5","E1",kBlue,1);
  //pltRatio->AddHist1D(h1_Ratio[2],"12.5<p_{T}<17.5","E1",kGreen,1);
  //pltRatio->AddHist1D(h1_Ratio[3],"17.5<p_{T}<50","E1",kViolet,1);
  //pltRatio->AddHist1D(h1_Ratio[4],"50<p_{T}<110","E1",kCyan,1);
  //pltRatio->AddHist1D(h1_Ratio[5],"110<p_{T}<600","E1",kRed,1);
  pltRatio->AddHist1D(h1_Ratio[0],"E1",1,1,0,24,2);
  pltRatio->AddHist1D(h1_Ratio[1],"E1",2,1,0,25,2);
  pltRatio->AddHist1D(h1_Ratio[2],"E1",4,1,0,26,2);
  //pltRatio->AddHist1D(h1_Ratio[3],"E1",3,1,0,28,2);
  //pltRatio->AddHist1D(h1_Ratio[4],"E1",7,1,0,30,2);
  //pltRatio->AddHist1D(h1_Ratio[5],"E1",4,1,0,32,2);
  pltRatio->SetLegend(0.25,0.8,0.5,0.9);
  pltRatio->GetLegend()->AddEntry(h1_Ratio[0],"0< p_{T} <12.5","PL");
  pltRatio->GetLegend()->AddEntry(h1_Ratio[1],"12.5#leq p_{T} <50","PL");
  pltRatio->GetLegend()->AddEntry(h1_Ratio[2],"50#leq p_{T} <600","PL");
  //pltRatio->GetLegend()->AddEntry(h1_Ratio[3],"17.5<p_{T}<50","PL");
  //pltRatio->GetLegend()->AddEntry(h1_Ratio[4],"50<p_{T}<110","PL");
  //pltRatio->GetLegend()->AddEntry(h1_Ratio[5],"110<p_{T}<600","PL");
  if(BaseName=="WpToMuNu")
    pltRatio->AddTextBox("W^{+}#rightarrow #mu^{+} #nu",0.68,0.83,0.8,0.9,0);
  if(BaseName=="WmToMuNu")
    pltRatio->AddTextBox("W^{-}#rightarrow #mu^{-} #bar{#nu}",0.68,0.83,0.8,0.9,0);
  pltRatio->SetYRange(0.7,1.2);
  pltRatio->Draw(myCan,kTRUE,format,1);

  Fout.close();
  myCan->Clear();

  return 0;
}
