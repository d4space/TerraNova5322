
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

int effStudy()
{
  TString Acc_WpMuNu = "../Acceptance_WpT/MuonLowPU/Muon_WpToMuNu_S8_Acceptance.root";
  TString Acc_WmMuNu = "../Acceptance_WpT/MuonLowPU/Muon_WmToMuNu_S8_Acceptance.root";
  TString Acc_WpElNu = "../Acceptance_WpT/ElectronLowPU/Ele_WpToEleNu_S8_Acceptance.root";
  TString Acc_WmElNu = "../Acceptance_WpT/ElectronLowPU/Ele_WmToEleNu_S8_Acceptance.root";

  TString Rec_WpMuNu = "MuonLowPU/Muon_WpToMuNu_S8_Unfold.root";
  TString Rec_WmMuNu = "MuonLowPU/Muon_WmToMuNu_S8_Unfold.root";
  TString Rec_WpElNu = "ElectronLowPU/Ele_WpToEleNu_S8_Unfold.root";
  TString Rec_WmElNu = "ElectronLowPU/Ele_WmToEleNu_S8_Unfold.root";

  double Bins[NWptBinPlus];
   // Final Bins7
   Bins[0]=     0.;
   Bins[1]=     7.5;
   Bins[2]=     12.5;
   Bins[3]=     17.5;
   Bins[4]=     24.;
   Bins[5]=     30.;
   Bins[6]=    40.;
   Bins[7]=    50.;
   Bins[8]=    70.;
   Bins[9]=    110.;
   Bins[10]=    150.;
   Bins[11]=    190.;
   Bins[12]=    250.;
   Bins[13]=    600.;

  TString BaseName = "UnfEff";
  cout<<"Processing "<<BaseName + " Study hahahahaha"<<endl;

  TString resultDir = "Result"+BaseName;
  char tmpName[30];
  TString tmpTStr;
  
  ofstream Fout;
  Fout.open(resultDir+"/FSRweightSyst.txt");

  Fout << "FSRweight Syst"<< endl;
  Fout << "=============================================================" << endl;
  //Fout <<fixed<<setprecision(4);
  Fout << "Bin" << "\t" << "Systematics" << endl;
  
  //ofstream of_Post_WpT_PostFid;

  TFile *f_Acc[4];
  TFile *f_Rec[4];
  f_Acc[0] = new TFile(Acc_WpMuNu);
  f_Acc[1] = new TFile(Acc_WmMuNu);
  f_Acc[2] = new TFile(Acc_WpElNu);
  f_Acc[3] = new TFile(Acc_WmElNu);

  f_Rec[0] = new TFile(Rec_WpMuNu);
  f_Rec[1] = new TFile(Rec_WmMuNu);
  f_Rec[2] = new TFile(Rec_WpElNu);
  f_Rec[3] = new TFile(Rec_WmElNu);

  gSystem->mkdir(resultDir,kTRUE);
  TFile f_out(resultDir+"/eff.root","recreate");

  // Unfolding to Post
  TH1D *h1_Truth_Post_EffCorr[4];
  TH1D *h1_Truth_Post_EffCorr_weightFSR[4];

  // Acceptance
  TH1D*	h1_Born_AP[4];

  TH1D*	h1_Born_BornFid[4];
  TH1D*	h1_Born_BothFid[4];

  TH1D*	h1_Post_PostFid[4];
  TH1D*	h1_Post_BothFid[4];
  TH1D*	h1_Post_BothFid_weightFSR[4];

  TH1D* h1_Post_BothOvTruth[4];
  TH1D* h1_Post_BothOvTruth_weightFSR[4];
  TH1D* h1_Post_PostOvBoth[4];
  TH1D* h1_Born_BothOvBorn[4];

  // Plot
  CPlot *pltEff;
  TCanvas *myCan = MakeCanvas("myCan","myCan",900,800);


  char legendName[30];

  //======================
  // Histo from Acceptance 
  //======================
  for(int i(0);i<4;i++)
  {
    // Get the Histograms from files
    sprintf(tmpName,"h1_Truth_Post_EffCorr");
    h1_Truth_Post_EffCorr[i] = (TH1D*)f_Rec[i]->Get(tmpName)->Clone(tmpName);
    h1_Truth_Post_EffCorr[i] -> Sumw2();

    sprintf(tmpName,"h1_Truth_Post_EffCorr_weightFSR");
    h1_Truth_Post_EffCorr_weightFSR[i] = (TH1D*)f_Rec[i]->Get(tmpName)->Clone(tmpName);
    h1_Truth_Post_EffCorr_weightFSR[i] -> Sumw2();

    sprintf(tmpName,"h1_Born_AP");
    h1_Born_AP[i]	=(TH1D*)f_Acc[i]->Get(tmpName)->Clone(tmpName);
    h1_Born_AP[i]->Sumw2();

    sprintf(tmpName,"h1_Born_BornFid");
    h1_Born_BornFid[i]	=(TH1D*)f_Acc[i]->Get(tmpName)->Clone(tmpName);
    h1_Born_BornFid[i]->Sumw2();
    
    sprintf(tmpName,"h1_Born_BothFid");
    h1_Born_BothFid[i]	=(TH1D*)f_Acc[i]->Get(tmpName)->Clone(tmpName);
    h1_Born_BothFid[i]->Sumw2();

    sprintf(tmpName,"h1_Post_PostFid");
    h1_Post_PostFid[i]	=(TH1D*)f_Acc[i]->Get(tmpName)->Clone(tmpName);
    h1_Post_PostFid[i]->Sumw2();
    
    sprintf(tmpName,"h1_Post_BothFid");
    h1_Post_BothFid[i]	=(TH1D*)f_Acc[i]->Get(tmpName)->Clone(tmpName);
    h1_Post_BothFid[i]->Sumw2();
  
    sprintf(tmpName,"h1_Post_BothFid_weightFSR");
    h1_Post_BothFid_weightFSR[i] = (TH1D*)f_Acc[i]->Get(tmpName)->Clone(tmpName);
    h1_Post_BothFid_weightFSR[i]->Sumw2();
  
    // Ratio calculation
    sprintf(tmpName,"h1_Post_BothOvTruth_%d",i);
    h1_Post_BothOvTruth[i] = (TH1D*)h1_Post_BothFid[i]->Clone(tmpName);
    h1_Post_BothOvTruth[i]->Sumw2();
    h1_Post_BothOvTruth[i]->Divide(h1_Truth_Post_EffCorr[i]);
    
    sprintf(tmpName,"h1_Post_BothOvTruth_weightFSR_%d",i);
    h1_Post_BothOvTruth_weightFSR[i] = (TH1D*)h1_Post_BothFid_weightFSR[i]->Clone(tmpName);
    h1_Post_BothOvTruth_weightFSR[i]->Sumw2();
    h1_Post_BothOvTruth_weightFSR[i]->Divide(h1_Truth_Post_EffCorr_weightFSR[i]);
    
    sprintf(tmpName,"h1_Post_PostOvBoth_%d",i);
    h1_Post_PostOvBoth[i] = (TH1D*)h1_Post_PostFid[i]->Clone(tmpName);
    h1_Post_PostOvBoth[i]->Sumw2();
    h1_Post_PostOvBoth[i]->Divide(h1_Post_BothFid[i]);

    sprintf(tmpName,"h1_Born_BothOvBorn_%d",i);
    h1_Born_BothOvBorn[i] = (TH1D*)h1_Born_BothFid[i]->Clone(tmpName);
    h1_Born_BothOvBorn[i]->Sumw2();
    h1_Born_BothOvBorn[i]->Divide(h1_Born_BornFid[i]);

    switch (i){
      case 0:
	h1_Post_BothOvTruth[0]->Write("h1_WpMu_BothOvTruth");
	h1_Post_BothOvTruth[0]->Draw();
	myCan->SaveAs(resultDir+"/h1_WpMu_BothOvTruth.png");

	h1_Post_BothOvTruth_weightFSR[0]->Write("h1_WpMu_BothOvTruth_weightFSR");
	h1_Post_BothOvTruth_weightFSR[0]->Draw();
	myCan->SaveAs(resultDir+"/h1_WpMu_BothOvTruth_weightFSR.png");

	h1_Post_PostOvBoth[0] ->Write("h1_WpMu_PostOvBoth");
	h1_Post_PostOvBoth[0]->Draw();
	myCan->SaveAs(resultDir+"/h1_WpMu_PostOvBoth.png");

	h1_Born_BothOvBorn[0] ->Write("h1_WpMu_BothOvBorn");
	h1_Born_BothOvBorn[0] ->Draw();
	myCan->SaveAs(resultDir+"/h1_WpMu_BothOvBorn.png");

	Fout << "============================ WpToMuNu =================================" << endl;
	for( int ipt(1);ipt<=h1_Post_BothOvTruth[0]->GetNbinsX(); ipt++)
	{
	  Fout <<ipt<<"\t"<<100*(h1_Post_BothOvTruth_weightFSR[0]->GetBinContent(ipt) - h1_Post_BothOvTruth[0]->GetBinContent(ipt))/h1_Post_BothOvTruth[0]->GetBinContent(ipt)<<endl;
	}

	break;
      case 1:
	h1_Post_BothOvTruth[1]->Write("h1_WmMu_BothOvTruth");
	h1_Post_BothOvTruth[1]->Draw();
	myCan->SaveAs(resultDir+"/h1_WmMu_BothOvTruth.png");

	h1_Post_BothOvTruth_weightFSR[1]->Write("h1_WmMu_BothOvTruth_weightFSR");
	h1_Post_BothOvTruth_weightFSR[1]->Draw();
	myCan->SaveAs(resultDir+"/h1_WmMu_BothOvTruth_weightFSR.png");

	h1_Post_PostOvBoth[1] ->Write("h1_WmMu_PostOvBoth");
	h1_Post_PostOvBoth[1]->Draw();
	myCan->SaveAs(resultDir+"/h1_WmMu_PostOvBoth.png");

	h1_Born_BothOvBorn[1] ->Write("h1_WmMu_BothOvBorn");
	h1_Born_BothOvBorn[1] ->Draw();
	myCan->SaveAs(resultDir+"/h1_WmMu_BothOvBorn.png");
	
	Fout << "============================ WmToMuNu =================================" << endl;
	for( int ipt(1);ipt<=h1_Post_BothOvTruth[1]->GetNbinsX(); ipt++)
	{
	  Fout <<ipt<<"\t"<<100*(h1_Post_BothOvTruth_weightFSR[1]->GetBinContent(ipt) - h1_Post_BothOvTruth[1]->GetBinContent(ipt))/h1_Post_BothOvTruth[1]->GetBinContent(ipt)<<endl;
	}

	break;
      case 2:
	h1_Post_BothOvTruth[2]->Write("h1_WpEl_BothOvTruth");
	h1_Post_BothOvTruth[2]->Draw();
	myCan->SaveAs(resultDir+"/h1_WpEl_BothOvTruth.png");

	h1_Post_BothOvTruth_weightFSR[2]->Write("h1_WpEl_BothOvTruth_weightFSR");
	h1_Post_BothOvTruth_weightFSR[2]->Draw();
	myCan->SaveAs(resultDir+"/h1_WpEl_BothOvTruth_weightFSR.png");

	h1_Post_PostOvBoth[2] ->Write("h1_WpEl_PostOvBoth");
	h1_Post_PostOvBoth[2]->Draw();
	myCan->SaveAs(resultDir+"/h1_WpEl_PostOvBoth.png");

	h1_Born_BothOvBorn[2] ->Write("h1_WpEl_BothOvBorn");
	h1_Born_BothOvBorn[2] ->Draw();
	myCan->SaveAs(resultDir+"/h1_WpEl_BothOvBorn.png");
	
	Fout << "============================ WpToEleNu =================================" << endl;
	for( int ipt(1);ipt<=h1_Post_BothOvTruth[2]->GetNbinsX(); ipt++)
	{
	  Fout <<ipt<<"\t"<<100*(h1_Post_BothOvTruth_weightFSR[2]->GetBinContent(ipt) - h1_Post_BothOvTruth[2]->GetBinContent(ipt))/h1_Post_BothOvTruth[2]->GetBinContent(ipt)<<endl;
	}
	break;
      case 3:
	h1_Post_BothOvTruth[3]->Write("h1_WmEl_BothOvTruth");
	h1_Post_BothOvTruth[3]->Draw();
	myCan->SaveAs(resultDir+"/h1_WmEl_BothOvTruth.png");

	h1_Post_BothOvTruth_weightFSR[3]->Write("h1_WmEl_BothOvTruth_weightFSR");
	h1_Post_BothOvTruth_weightFSR[3]->Draw();
	myCan->SaveAs(resultDir+"/h1_WmEl_BothOvTruth_weightFSR.png");

	h1_Post_PostOvBoth[3] ->Write("h1_WmEl_PostOvBoth");
	h1_Post_PostOvBoth[3]->Draw();
	myCan->SaveAs(resultDir+"/h1_WmEl_PostOvBoth.png");

	h1_Born_BothOvBorn[3] ->Write("h1_WmEl_BothOvBorn");
	h1_Born_BothOvBorn[3] ->Draw();
	myCan->SaveAs(resultDir+"/h1_WmEl_BothOvBorn.png");
	
	Fout << "============================ WmToEleMuNu =================================" << endl;
	for( int ipt(1);ipt<=h1_Post_BothOvTruth[3]->GetNbinsX(); ipt++)
	{
	  Fout <<ipt<<"\t"<<100*(h1_Post_BothOvTruth_weightFSR[3]->GetBinContent(ipt) - h1_Post_BothOvTruth[3]->GetBinContent(ipt))/h1_Post_BothOvTruth[3]->GetBinContent(ipt)<<endl;
	}
	break;
      default:
	cout<<"Error: which case huh?"<<endl;
	exit(-1);
    }
  }
  return 0;
}
