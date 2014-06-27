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
  
  TH1D *h1_AllCut1; 
  TH1D *h1_FidCut1;

  //======================
  // Histo from root
  //======================
  sprintf(tmpNameOrg,"h1_PlusLepPtAllCut_4");
  if(BaseName=="WmToMuNu")
    sprintf(tmpNameOrg,"h1_MinuLepPtAllCut_4");
  sprintf(tmpName,"h1_AllCut1");
  h1_AllCut1 = (TH1D*)fName->Get(tmpNameOrg)->Clone(tmpName);
  h1_AllCut1-> Sumw2();

  sprintf(tmpNameOrg,"h1_PlusLepPtFidCut_4");
  if(BaseName=="WmToMuNu")
    sprintf(tmpNameOrg,"h1_MinuLepPtFidCut_4");
  sprintf(tmpName,"h1_FidCut1");
  h1_FidCut1 = (TH1D*)fName->Get(tmpNameOrg)->Clone(tmpName);
  h1_FidCut1-> Sumw2();
  
  for(int ipt(1);ipt<=h1_AllCut1->GetNbinsX(); ipt++)
  {
    cout<<h1_AllCut1->GetBinContent(ipt)<<" / "<<h1_FidCut1->GetBinContent(ipt)<<endl;
  }
  h1_AllCut1->Divide(h1_FidCut1);
  h1_AllCut1-> Sumw2();
    
  h1_AllCut1->SetLineColor(kBlack );
  
  h1_AllCut1->SetMarkerColor(kBlack );

  TCanvas *lC1 = new TCanvas("Can","Can",800,840);
  h1_AllCut1->Draw("E1");
  
  sprintf(tmpName,BaseName+"_Result.png");
  lC1->SaveAs(tmpName);

  Fout.close();

  return 0;
}
