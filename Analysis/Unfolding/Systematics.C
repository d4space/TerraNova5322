
#include "TStyle.h"
#include "../Utils/const.h"
#include "../Utils/CPlot.hh"
#include "../Utils/MitStyleRemix.hh"
#include "../Utils/Unfolder.h"
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

int Systematics()
{
  TFile *Unf_WpMuNuN = new TFile("UnfoldingNominal/ResultWpToMuNu/Result_WpToMuNu.root");
  TFile *Unf_WmMuNuN = new TFile("UnfoldingNominal/ResultWmToMuNu/Result_WmToMuNu.root");
  TFile *Unf_WpElNuN = new TFile("UnfoldingNominal/ResultWpToEleNu/Result_WpToEleNu.root");
  TFile *Unf_WmElNuN = new TFile("UnfoldingNominal/ResultWmToEleNu/Result_WmToEleNu.root");
  TFile *Unf_WpMuNuF = new TFile("UnfoldingEffPtBinning/ResultWpToMuNu/Result_WpToMuNu.root");
  TFile *Unf_WmMuNuF = new TFile("UnfoldingEffPtBinning/ResultWmToMuNu/Result_WmToMuNu.root");
  TFile *Unf_WpElNuF = new TFile("UnfoldingEffPtBinning/ResultWpToEleNu/Result_WpToEleNu.root");
  TFile *Unf_WmElNuF = new TFile("UnfoldingEffPtBinning/ResultWmToEleNu/Result_WmToEleNu.root");

  char tmpName[30];
  char tmpNameOrg[30];
  
  TH1D *h1_SigMupN;
  TH1D *h1_SigMumN;
  TH1D *h1_SigMupF;
  TH1D *h1_SigMumF;
  TH1D *h1_SigElpN;
  TH1D *h1_SigElmN;
  TH1D *h1_SigElpF;
  TH1D *h1_SigElmF;
  
  TH1D *h1_dUnfMupN;
  TH1D *h1_dUnfMumN;
  TH1D *h1_dUnfMupF;
  TH1D *h1_dUnfMumF;
  TH1D *h1_dUnfElpN;
  TH1D *h1_dUnfElmN;
  TH1D *h1_dUnfElpF;
  TH1D *h1_dUnfElmF;
  
  TH1D *h1_fUnfMupN;
  TH1D *h1_fUnfMumN;
  TH1D *h1_fUnfMupF;
  TH1D *h1_fUnfMumF;
  TH1D *h1_fUnfElpN;
  TH1D *h1_fUnfElmN;
  TH1D *h1_fUnfElpF;
  TH1D *h1_fUnfElmF;
  
  sprintf(tmpName,"data_Rec");
  h1_SigMupN = (TH1D*)Unf_WpMuNuN->Get(tmpName)->Clone("h1_SigMupN");
  h1_SigMupF = (TH1D*)Unf_WpMuNuF->Get(tmpName)->Clone("h1_SigMupF");
  h1_SigElpN = (TH1D*)Unf_WpElNuN->Get(tmpName)->Clone("h1_SigElpN");
  h1_SigElpF = (TH1D*)Unf_WpElNuF->Get(tmpName)->Clone("h1_SigElpF");
  
  h1_SigMumN = (TH1D*)Unf_WmMuNuN->Get(tmpName)->Clone("h1_SigMumN");
  h1_SigMumF = (TH1D*)Unf_WmMuNuF->Get(tmpName)->Clone("h1_SigMumF");
  h1_SigElmN = (TH1D*)Unf_WmElNuN->Get(tmpName)->Clone("h1_SigElmN");
  h1_SigElmF = (TH1D*)Unf_WmElNuF->Get(tmpName)->Clone("h1_SigElmF");
  
  sprintf(tmpName,"DetUnf");
  h1_dUnfMupN = (TH1D*)Unf_WpMuNuN->Get(tmpName)->Clone("h1_dUnfMupN");
  h1_dUnfMupF = (TH1D*)Unf_WpMuNuF->Get(tmpName)->Clone("h1_dUnfMupF");
  h1_dUnfElpN = (TH1D*)Unf_WpElNuN->Get(tmpName)->Clone("h1_dUnfElpN");
  h1_dUnfElpF = (TH1D*)Unf_WpElNuF->Get(tmpName)->Clone("h1_dUnfElpF");
  
  h1_dUnfMumN = (TH1D*)Unf_WmMuNuN->Get(tmpName)->Clone("h1_dUnfMumN");
  h1_dUnfMumF = (TH1D*)Unf_WmMuNuF->Get(tmpName)->Clone("h1_dUnfMumF");
  h1_dUnfElmN = (TH1D*)Unf_WmElNuN->Get(tmpName)->Clone("h1_dUnfElmN");
  h1_dUnfElmF = (TH1D*)Unf_WmElNuF->Get(tmpName)->Clone("h1_dUnfElmF");
  
  sprintf(tmpName,"FSRUnf");
  h1_fUnfMupN = (TH1D*)Unf_WpMuNuN->Get(tmpName)->Clone("h1_fUnfMupN");
  h1_fUnfMupF = (TH1D*)Unf_WpMuNuF->Get(tmpName)->Clone("h1_fUnfMupF");
  h1_fUnfElpN = (TH1D*)Unf_WpElNuN->Get(tmpName)->Clone("h1_fUnfElpN");
  h1_fUnfElpF = (TH1D*)Unf_WpElNuF->Get(tmpName)->Clone("h1_fUnfElpF");
  
  h1_fUnfMumN = (TH1D*)Unf_WmMuNuN->Get(tmpName)->Clone("h1_fUnfMumN");
  h1_fUnfMumF = (TH1D*)Unf_WmMuNuF->Get(tmpName)->Clone("h1_fUnfMumF");
  h1_fUnfElmN = (TH1D*)Unf_WmElNuN->Get(tmpName)->Clone("h1_fUnfElmN");
  h1_fUnfElmF = (TH1D*)Unf_WmElNuF->Get(tmpName)->Clone("h1_fUnfElmF");
  
  double RecMup[NWptBinPlus-1];
  double RecElp[NWptBinPlus-1];
  double dUnfMup[NWptBinPlus-1];
  double dUnfElp[NWptBinPlus-1];
  double fUnfMup[NWptBinPlus-1];
  double fUnfElp[NWptBinPlus-1];
  double RecMum[NWptBinPlus-1];
  double RecElm[NWptBinPlus-1];
  double dUnfMum[NWptBinPlus-1];
  double dUnfElm[NWptBinPlus-1];
  double fUnfMum[NWptBinPlus-1];
  double fUnfElm[NWptBinPlus-1];

  for(int ipt(1);ipt<=h1_SigMupN->GetNbinsX(); ipt++)
  {
    RecMup[ipt-1] = fabs(h1_SigMupF->GetBinContent(ipt)-h1_SigMupN->GetBinContent(ipt))/h1_SigMupN->GetBinContent(ipt)*100;
    RecMum[ipt-1] = fabs(h1_SigMumF->GetBinContent(ipt)-h1_SigMumN->GetBinContent(ipt))/h1_SigMumN->GetBinContent(ipt)*100;
    RecElp[ipt-1] = fabs(h1_SigElpF->GetBinContent(ipt)-h1_SigElpN->GetBinContent(ipt))/h1_SigElpN->GetBinContent(ipt)*100;
    RecElm[ipt-1] = fabs(h1_SigElmF->GetBinContent(ipt)-h1_SigElmN->GetBinContent(ipt))/h1_SigElmN->GetBinContent(ipt)*100;
    
    dUnfMup[ipt-1] = fabs(h1_dUnfMupF->GetBinContent(ipt)-h1_dUnfMupN->GetBinContent(ipt))/h1_dUnfMupN->GetBinContent(ipt)*100;
    dUnfMum[ipt-1] = fabs(h1_dUnfMumF->GetBinContent(ipt)-h1_dUnfMumN->GetBinContent(ipt))/h1_dUnfMumN->GetBinContent(ipt)*100;
    dUnfElp[ipt-1] = fabs(h1_dUnfElpF->GetBinContent(ipt)-h1_dUnfElpN->GetBinContent(ipt))/h1_dUnfElpN->GetBinContent(ipt)*100;
    dUnfElm[ipt-1] = fabs(h1_dUnfElmF->GetBinContent(ipt)-h1_dUnfElmN->GetBinContent(ipt))/h1_dUnfElmN->GetBinContent(ipt)*100;
    
    fUnfMup[ipt-1] = fabs(h1_fUnfMupF->GetBinContent(ipt)-h1_fUnfMupN->GetBinContent(ipt))/h1_fUnfMupN->GetBinContent(ipt)*100;
    fUnfMum[ipt-1] = fabs(h1_fUnfMumF->GetBinContent(ipt)-h1_fUnfMumN->GetBinContent(ipt))/h1_fUnfMumN->GetBinContent(ipt)*100;
    fUnfElp[ipt-1] = fabs(h1_fUnfElpF->GetBinContent(ipt)-h1_fUnfElpN->GetBinContent(ipt))/h1_fUnfElpN->GetBinContent(ipt)*100;
    fUnfElm[ipt-1] = fabs(h1_fUnfElmF->GetBinContent(ipt)-h1_fUnfElmN->GetBinContent(ipt))/h1_fUnfElmN->GetBinContent(ipt)*100;
  }

  cout<<fixed<<setprecision(4)<<endl;
  cout<<"WpToMuNu"<<endl;
  for(int ipt(1);ipt<=h1_SigMupN->GetNbinsX(); ipt++)
  {
    cout<<ipt<<"\t"<<RecMup[ipt-1]<<"\t"<<dUnfMup[ipt-1]<<"\t"<<fUnfMup[ipt-1]<<endl;
  }
  cout<<"WmToMuNu"<<endl;
  for(int ipt(1);ipt<=h1_SigMupN->GetNbinsX(); ipt++)
  {
    cout<<ipt<<"\t"<<RecMum[ipt-1]<<"\t"<<dUnfMum[ipt-1]<<"\t"<<fUnfMum[ipt-1]<<endl;
  }
  cout<<"WpToEleNu"<<endl;
  for(int ipt(1);ipt<=h1_SigMupN->GetNbinsX(); ipt++)
  {
    cout<<ipt<<"\t"<<RecElp[ipt-1]<<"\t"<<dUnfElp[ipt-1]<<"\t"<<fUnfElp[ipt-1]<<endl;
  }
  cout<<"WmToEleNu"<<endl;
  for(int ipt(1);ipt<=h1_SigMupN->GetNbinsX(); ipt++)
  {
    cout<<ipt<<"\t"<<RecElm[ipt-1]<<"\t"<<dUnfElm[ipt-1]<<"\t"<<fUnfElm[ipt-1]<<endl;
  }
  return 0;
}
