
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
  TString Acc_WpMuNu = "../Acceptance_WpT/WpToMuNu_S8_Acceptance/WpToMuNu_S8_Acceptance.root";
  TString Acc_WmMuNu = "../Acceptance_WpT/WmToMuNu_S8_Acceptance/WmToMuNu_S8_Acceptance.root";
  TString Acc_WpElNu = "../Acceptance_WpT/WpToEleNu_S8_Acceptance/WpToEleNu_S8_Acceptance.root";
  TString Acc_WmElNu = "../Acceptance_WpT/WmToEleNu_S8_Acceptance/WmToEleNu_S8_Acceptance.root";

  TString Rec_WpMuNu = "../WPtMET/WpToMuNu_S8_AllCorrectionsMC/WpToMuNu_S8_AllCorrectionsMC.root";   
  TString Rec_WmMuNu = "../WPtMET/WmToMuNu_S8_AllCorrectionsMC/WmToMuNu_S8_AllCorrectionsMC.root";   
  TString Rec_WpElNu = "../WPtMET/WpToEleNu_S8_AllCorrectionsMC/WpToEleNu_S8_AllCorrectionsMC.root"; 
  TString Rec_WmElNu = "../WPtMET/WmToEleNu_S8_AllCorrectionsMC/WmToEleNu_S8_AllCorrectionsMC.root"; 

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
  char tmpNameOrg[30];
  TString tmpTStr;
  
  ofstream Fout;
  Fout.open(resultDir+"/FSRweightSyst.txt");

  Fout << "FSRweight Syst"<< endl;
  Fout << "=============================================================" << endl;
  //Fout <<fixed<<setprecision(4);
  Fout << "Bin" << "\t" << "Systematics" << endl;
  
  //ofstream of_Post_WpT_PostFid;
  cout << "check 1" <<endl;
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
  cout << "check 2" <<endl;

  // Unfolding to Post
  TH1D *h1_Truth_Post_EffCorr[4];
  TH1D *h1_Truth_Post_EffCorr_weightFSR[4];

  //Reconstructed Events in FidVol.
  TH1D *h1_Wpt[4];  //Without Charge selection W pt
  TH1D *h1_W_pt[4]; //Charge selected W pt

  //Unfolding RecTruth
  TH1D *h1_RecTruthOvRec[4];

  // Acceptance
  TH1D*	h1_Born_AP[4];

  TH1D*	h1_Born_BornFid[4];
  TH1D*	h1_Born_BothFid[4];

  TH1D*	h1_Post_PostFid[4];
  TH1D*	h1_Post_BothFid[4];
  TH1D*	h1_Post_BothFid_weightFSR[4];

  TH1D* h1_Post_BothOvTruth[4];
  TH1D* h1_Post_BothOvTruth_Inverse[4];
  TH1D* h1_Post_BothOvTruth_weightFSR[4];
  TH1D* h1_Post_PostOvBoth[4];
  TH1D* h1_Born_BothOvBorn[4];
  
  TH1D* h1_RecOvBorn[4];
  TH1D* h1_RecOvPostFSR[4];
  TH1D* h1_PostOvBorn[4];
  TH1D* h1_PostMultBorn[4];
  
  TH1D *h1_MCEventFSRSyst = new TH1D("h1_MCEventFSRSyst","h1_MCEventFSRSyst",13,Bins);h1_MCEventFSRSyst->Sumw2();

  cout << "check 3" <<endl;
  // Plot
  CPlot *pltEff;
  TCanvas *myCan = MakeCanvas("myCan","myCan",900,800);

  myCan->SetGrid();

  char legendName[30];

  //======================
  // Histo from Acceptance 
  //======================
  for(int i(0);i<4;i++)
  {
    // Get the Histograms from files
    sprintf(tmpNameOrg,"h1_Truth_Post_EffCorr");
    sprintf(tmpName,"h1_Truth_Post_EffCorr_%d",i);
  cout << "check 4" <<endl;
    h1_Truth_Post_EffCorr[i] = (TH1D*)f_Rec[i]->Get(tmpNameOrg)->Clone(tmpName);
    h1_Truth_Post_EffCorr[i]-> Sumw2();
  cout << "check 5" <<endl;

    sprintf(tmpNameOrg,"h1_Truth_Post_EffCorr_weightFSR");
    sprintf(tmpName,"h1_Truth_Post_EffCorr_weightFSR_%d",i);
    h1_Truth_Post_EffCorr_weightFSR[i] = (TH1D*)f_Rec[i]->Get(tmpNameOrg)->Clone(tmpName);
    h1_Truth_Post_EffCorr_weightFSR[i] -> Sumw2();

    sprintf(tmpName,"h1_W_pt");
    if (i == 0 || i == 2)
      h1_W_pt[i] = (TH1D*)f_Rec[i]->Get("h1_Wp_pt")->Clone(tmpName);
    else
      h1_W_pt[i] = (TH1D*)f_Rec[i]->Get("h1_Wm_pt")->Clone(tmpName);
    h1_W_pt[i]-> Sumw2();
    
    sprintf(tmpName,"h1_Wpt");
    h1_Wpt[i] = (TH1D*)f_Rec[i]->Get("h1_W_pt")->Clone(tmpName);
    h1_Wpt[i]-> Sumw2();

    for( int ipt(1);ipt<=h1_Wpt[i]->GetNbinsX(); ipt++)
    {
      cout<<i<<" W_pt = "<<h1_Wpt[i]->GetBinContent(ipt)<< "\t Wcharge pt = "<<h1_W_pt[i]->GetBinContent(ipt)<<"\t Mis-Q = "<<h1_Wpt[i]->GetBinContent(ipt)-h1_W_pt[i]->GetBinContent(ipt)<<"("<<100*(h1_Wpt[i]->GetBinContent(ipt)-h1_W_pt[i]->GetBinContent(ipt))/h1_W_pt[i]->GetBinContent(ipt)<<" \%)"<<endl;
    }
    h1_Wpt[i]->Divide(h1_W_pt[i]);

    sprintf(tmpNameOrg,"h1_Born_AP");
    sprintf(tmpName,"h1_Born_AP_%d",i);
    h1_Born_AP[i] = (TH1D*)f_Acc[i]->Get(tmpNameOrg)->Clone(tmpName);
    h1_Born_AP[i]-> Sumw2();

    sprintf(tmpNameOrg,"h1_Born_BornFid");
    sprintf(tmpName,"h1_Born_BornFid_%d",i);
    h1_Born_BornFid[i]	=(TH1D*)f_Acc[i]->Get(tmpNameOrg)->Clone(tmpName);
    h1_Born_BornFid[i]->Sumw2();
    
    sprintf(tmpNameOrg,"h1_Born_BothFid");
    sprintf(tmpName,"h1_Born_BothFid_%d",i);
    h1_Born_BothFid[i]	=(TH1D*)f_Acc[i]->Get(tmpNameOrg)->Clone(tmpName);
    h1_Born_BothFid[i]->Sumw2();

    sprintf(tmpNameOrg,"h1_Post_PostFid");
    sprintf(tmpName,"h1_Post_PostFid_%d",i);
    h1_Post_PostFid[i]	=(TH1D*)f_Acc[i]->Get(tmpNameOrg)->Clone(tmpName);
    h1_Post_PostFid[i]->Sumw2();
    
    sprintf(tmpNameOrg,"h1_Post_BothFid");
    sprintf(tmpName,"h1_Post_BothFid_%d",i);
    h1_Post_BothFid[i]	=(TH1D*)f_Acc[i]->Get(tmpNameOrg)->Clone(tmpName);
    h1_Post_BothFid[i]->Sumw2();
  
    sprintf(tmpNameOrg,"h1_Post_BothFid_weightFSR");
    sprintf(tmpName,"h1_Post_BothFid_weightFSR_%d",i);
    h1_Post_BothFid_weightFSR[i] = (TH1D*)f_Acc[i]->Get(tmpNameOrg)->Clone(tmpName);
    h1_Post_BothFid_weightFSR[i]->Sumw2();
  
    // Ratio calculation
    sprintf(tmpName,"h1_Post_BothOvTruth_%d",i);
    h1_Post_BothOvTruth[i] = (TH1D*)h1_Post_BothFid[i]->Clone(tmpName);
    h1_Post_BothOvTruth[i]->Sumw2();
    h1_Post_BothOvTruth[i]->Divide(h1_Truth_Post_EffCorr[i]);
    
    for(int ibin(1);ibin<14;ibin++)
    {
      cout<<ibin<<": "<<h1_Post_BothOvTruth[i]->GetBinContent(ibin)<<endl;
    }
    sprintf(tmpName,"h1_Post_BothOvTruth_Inverse_%d",i);
    h1_Post_BothOvTruth_Inverse[i] = (TH1D*)h1_Truth_Post_EffCorr[i]->Clone(tmpName);
    h1_Post_BothOvTruth_Inverse[i]->Sumw2();
    h1_Post_BothOvTruth_Inverse[i]->Divide(h1_Post_BothFid[i]);
    
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

    //Ratio Reconstucted/Born in FidVol
    sprintf(tmpName,"h1_RecOvBorn_%d",i);
    h1_RecOvBorn[i] = (TH1D*)h1_W_pt[i]->Clone(tmpName);
    h1_RecOvBorn[i]->Sumw2();
    h1_RecOvBorn[i]->Divide(h1_Born_BornFid[i]);

    //Ratio Reconstucted/PostFSR in FidVol
    sprintf(tmpName,"h1_RecOvPostFSR_%d",i);
    h1_RecOvPostFSR[i] = (TH1D*)h1_W_pt[i]->Clone(tmpName);
    h1_RecOvPostFSR[i]->Sumw2();
    h1_RecOvPostFSR[i]->Divide(h1_Post_PostFid[i]);

    //Ratio PostFSR/Born in FidVol
    sprintf(tmpName,"h1_PostOvBorn_%d",i);
    h1_PostOvBorn[i] = (TH1D*)h1_Post_PostFid[i]->Clone(tmpName);
    h1_PostOvBorn[i]->Sumw2();
    h1_PostOvBorn[i]->Divide(h1_Born_BornFid[i]);

    //Ratio RecTruth/Reconstr in FidVol
    sprintf(tmpName,"h1_RecTruthOvRec_%d",i);
    h1_RecTruthOvRec[i] = (TH1D*)f_Rec[i]->Get("h1_Truth_Rec")->Clone(tmpName);
    h1_RecTruthOvRec[i]-> Sumw2();
    h1_RecTruthOvRec[i]->Divide(h1_W_pt[i]);

    sprintf(tmpName,"h1_PostMultBorn_%d",i);
    h1_PostMultBorn[i] = (TH1D*)h1_PostOvBorn[i]->Clone(tmpName);
    h1_PostMultBorn[i]->Sumw2();
    h1_PostMultBorn[i]->Multiply(h1_RecOvPostFSR[i]);
    
    switch (i){
      case 0:
	h1_Post_BothOvTruth[0]->Write("h1_WpMu_BothOvTruth");
	h1_Post_BothOvTruth[0]->Draw();
	myCan->SaveAs(resultDir+"/h1_WpMu_BothOvTruth.png");
	
	h1_Post_BothOvTruth_Inverse[0]->Write("h1_WpMu_BothOvTruth_Inverse");
	h1_Post_BothOvTruth_Inverse[0]->Draw();
	h1_Post_BothOvTruth_Inverse[0]->SetTitle("");
	myCan->SaveAs(resultDir+"/h1_WpMu_BothOvTruth_Inverse.png");

	h1_Post_BothOvTruth_weightFSR[0]->Write("h1_WpMu_BothOvTruth_weightFSR");
	h1_Post_BothOvTruth_weightFSR[0]->Draw();
	myCan->SaveAs(resultDir+"/h1_WpMu_BothOvTruth_weightFSR.png");

	h1_Post_PostOvBoth[0] ->Write("h1_WpMu_PostOvBoth");
	h1_Post_PostOvBoth[0]->Draw();
	myCan->SaveAs(resultDir+"/h1_WpMu_PostOvBoth.png");

	h1_Born_BothOvBorn[0] ->Write("h1_WpMu_BothOvBorn");
	h1_Born_BothOvBorn[0] ->Draw();
	myCan->SaveAs(resultDir+"/h1_WpMu_BothOvBorn.png");

	h1_RecOvBorn[0] ->Write("h1_WpMu_RecOvBorn");
	h1_RecOvBorn[0] ->Draw();
	h1_RecOvBorn[0] ->SetTitle("");
	myCan->SaveAs(resultDir+"/h1_WpMu_RecOvBorn.png");

	h1_RecOvPostFSR[0] ->Write("h1_WpMu_RecOvPostFSR");
	h1_RecOvPostFSR[0] ->Draw();
	h1_RecOvPostFSR[0] ->SetTitle("");
	myCan->SaveAs(resultDir+"/h1_WpMu_RecOvPostFSR.png");

	h1_PostOvBorn[0] ->Write("h1_WpMu_PostOvBorn");
	h1_PostOvBorn[0] ->Draw();
	h1_PostOvBorn[0] ->SetTitle("");
	myCan->SaveAs(resultDir+"/h1_WpMu_PostOvBorn.png");
	
	h1_PostMultBorn[0] ->Write("h1_WpMu_PostMultBorn");
	h1_PostMultBorn[0] ->Draw();
	h1_PostMultBorn[0] ->SetTitle("");
	myCan->SaveAs(resultDir+"/h1_WpMu_PostMultBorn.png");
	
	h1_RecTruthOvRec[0] ->Write("h1_WpMu_RecTruthOvRec");
	h1_RecTruthOvRec[0]->GetYaxis()->SetRangeUser(0.99996,1.00001);
	h1_RecTruthOvRec[0] ->Draw("hist P");
	h1_RecTruthOvRec[0] ->SetTitle("");
	myCan->SaveAs(resultDir+"/h1_WpMu_RecTruthOvRec.png");
	
	h1_Wpt[0] ->Write("h1_WpMu_WptOvWcharge_pt");
	h1_Wpt[0]->GetYaxis()->SetRangeUser(0.98,1.02);
	h1_Wpt[0] ->Draw();
	h1_Wpt[0] ->SetTitle("");
	myCan->SaveAs(resultDir+"/h1_WpMu_WptOvWcharge_pt.png");
	
	Fout << "============================ WpToMuNu =================================" << endl;
	for( int ipt(1);ipt<=h1_Post_BothOvTruth[0]->GetNbinsX(); ipt++)
	{
	  //Fout <<ipt<<"\t"<<100*(h1_Post_BothOvTruth_weightFSR[0]->GetBinContent(ipt) - h1_Post_BothOvTruth[0]->GetBinContent(ipt))/h1_Post_BothOvTruth[0]->GetBinContent(ipt)<<endl;
	  double FSRsyst = 100*(h1_Post_BothOvTruth_weightFSR[0]->GetBinContent(ipt) - h1_Post_BothOvTruth[0]->GetBinContent(ipt))/h1_Post_BothOvTruth[0]->GetBinContent(ipt);
	  Fout <<ipt<<"\t"<<FSRsyst<<endl;
	  h1_MCEventFSRSyst->SetBinContent(ipt, FSRsyst);
	}
	h1_MCEventFSRSyst->Write();

	break;
      case 1:
	h1_Post_BothOvTruth[1]->Write("h1_WmMu_BothOvTruth");
	h1_Post_BothOvTruth[1]->Draw();
	h1_Post_BothOvTruth[1]->SetTitle("");
	myCan->SaveAs(resultDir+"/h1_WmMu_BothOvTruth.png");

	h1_Post_BothOvTruth_Inverse[1]->Write("h1_WmMu_BothOvTruth_Inverse");
	h1_Post_BothOvTruth_Inverse[1]->Draw();
	h1_Post_BothOvTruth_Inverse[1]->SetTitle("");
	myCan->SaveAs(resultDir+"/h1_WmMu_BothOvTruth_Inverse.png");

	h1_Post_BothOvTruth_weightFSR[1]->Write("h1_WmMu_BothOvTruth_weightFSR");
	h1_Post_BothOvTruth_weightFSR[1]->Draw();
	myCan->SaveAs(resultDir+"/h1_WmMu_BothOvTruth_weightFSR.png");

	h1_Post_PostOvBoth[1] ->Write("h1_WmMu_PostOvBoth");
	h1_Post_PostOvBoth[1]->Draw();
	h1_Post_PostOvBoth[1]->SetTitle("");
	myCan->SaveAs(resultDir+"/h1_WmMu_PostOvBoth.png");

	h1_Born_BothOvBorn[1] ->Write("h1_WmMu_BothOvBorn");
	h1_Born_BothOvBorn[1] ->Draw();
	h1_Born_BothOvBorn[1]->SetTitle("");
	myCan->SaveAs(resultDir+"/h1_WmMu_BothOvBorn.png");
	
	h1_RecOvBorn[1] ->Write("h1_WmMu_RecOvBorn");
	h1_RecOvBorn[1] ->Draw();
	h1_RecOvBorn[1] ->SetTitle("");
	myCan->SaveAs(resultDir+"/h1_WmMu_RecOvBorn.png");

	h1_RecOvPostFSR[1] ->Write("h1_WmMu_RecOvPostFSR");
	h1_RecOvPostFSR[1] ->Draw();
	h1_RecOvPostFSR[1] ->SetTitle("");
	myCan->SaveAs(resultDir+"/h1_WmMu_RecOvPostFSR.png");

	h1_PostOvBorn[1] ->Write("h1_WmMu_PostOvBorn");
	h1_PostOvBorn[1] ->Draw();
	h1_PostOvBorn[1] ->SetTitle("");
	myCan->SaveAs(resultDir+"/h1_WmMu_PostOvBorn.png");
	
	h1_PostMultBorn[1] ->Write("h1_WmMu_PostMultBorn");
	h1_PostMultBorn[1] ->Draw();
	h1_PostMultBorn[1] ->SetTitle("");
	myCan->SaveAs(resultDir+"/h1_WmMu_PostMultBorn.png");
	
	h1_RecTruthOvRec[1] ->Write("h1_WmMu_RecTruthOvRec");
	h1_RecTruthOvRec[1]->GetYaxis()->SetRangeUser(0.9999,1.00001);
	h1_RecTruthOvRec[1] ->Draw("hist P");
	h1_RecTruthOvRec[1] ->SetTitle("");
	myCan->SaveAs(resultDir+"/h1_WmMu_RecTruthOvRec.png");
	
	h1_Wpt[1] ->Write("h1_WmMu_WptOvWcharge_pt");
	h1_Wpt[1]->GetYaxis()->SetRangeUser(0.98,1.02);
	h1_Wpt[1] ->Draw();
	h1_Wpt[1] ->SetTitle("");
	myCan->SaveAs(resultDir+"/h1_WmMu_WptOvWcharge_pt.png");
	
	Fout << "============================ WmToMuNu =================================" << endl;
	for( int ipt(1);ipt<=h1_Post_BothOvTruth[1]->GetNbinsX(); ipt++)
	{
	  //Fout <<ipt<<"\t"<<100*(h1_Post_BothOvTruth_weightFSR[1]->GetBinContent(ipt) - h1_Post_BothOvTruth[1]->GetBinContent(ipt))/h1_Post_BothOvTruth[1]->GetBinContent(ipt)<<endl;
	  double FSRsyst = 100*(h1_Post_BothOvTruth_weightFSR[1]->GetBinContent(ipt) - h1_Post_BothOvTruth[1]->GetBinContent(ipt))/h1_Post_BothOvTruth[1]->GetBinContent(ipt);
	  Fout <<ipt<<"\t"<<FSRsyst<<endl;
	  h1_MCEventFSRSyst->SetBinContent(ipt, FSRsyst);
	}
	h1_MCEventFSRSyst->Write();

	break;
      case 2:
	h1_Post_BothOvTruth[2]->Write("h1_WpEl_BothOvTruth");
	h1_Post_BothOvTruth[2]->Draw();
	h1_Post_BothOvTruth[2]->SetTitle("");
	myCan->SaveAs(resultDir+"/h1_WpEl_BothOvTruth.png");
	
	h1_Post_BothOvTruth_Inverse[2]->Write("h1_WpEl_BothOvTruth_Inverse");
	h1_Post_BothOvTruth_Inverse[2]->Draw();
	h1_Post_BothOvTruth_Inverse[2]->SetTitle("");
	myCan->SaveAs(resultDir+"/h1_WpEl_BothOvTruth_Inverse.png");

	h1_Post_BothOvTruth_weightFSR[2]->Write("h1_WpEl_BothOvTruth_weightFSR");
	h1_Post_BothOvTruth_weightFSR[2]->Draw();
	myCan->SaveAs(resultDir+"/h1_WpEl_BothOvTruth_weightFSR.png");

	h1_Post_PostOvBoth[2] ->Write("h1_WpEl_PostOvBoth");
	h1_Post_PostOvBoth[2]->Draw();
	h1_Post_PostOvBoth[2]->SetTitle("");
	myCan->SaveAs(resultDir+"/h1_WpEl_PostOvBoth.png");

	h1_Born_BothOvBorn[2] ->Write("h1_WpEl_BothOvBorn");
	h1_Born_BothOvBorn[2] ->Draw();
	h1_Born_BothOvBorn[2]->SetTitle("");
	myCan->SaveAs(resultDir+"/h1_WpEl_BothOvBorn.png");
	
	h1_RecOvBorn[2] ->Write("h1_WpEle_RecOvBorn");
	h1_RecOvBorn[2] ->Draw();
	h1_RecOvBorn[2] ->SetTitle("");
	myCan->SaveAs(resultDir+"/h1_WpEle_RecOvBorn.png");

	h1_RecOvPostFSR[2] ->Write("h1_WpEle_RecOvPostFSR");
	h1_RecOvPostFSR[2] ->Draw();
	h1_RecOvPostFSR[2] ->SetTitle("");
	myCan->SaveAs(resultDir+"/h1_WpEle_RecOvPostFSR.png");

	h1_PostOvBorn[2] ->Write("h1_WpEle_PostOvBorn");
	h1_PostOvBorn[2] ->Draw();
	h1_PostOvBorn[2] ->SetTitle("");
	myCan->SaveAs(resultDir+"/h1_WpEle_PostOvBorn.png");
	
	h1_PostMultBorn[2] ->Write("h1_WpEle_PostMultBorn");
	h1_PostMultBorn[2] ->Draw();
	h1_PostMultBorn[2] ->SetTitle("");
	myCan->SaveAs(resultDir+"/h1_WpEle_PostMultBorn.png");
	
	h1_RecTruthOvRec[2] ->Write("h1_WpEle_RecTruthOvRec");
	h1_RecTruthOvRec[2]->GetYaxis()->SetRangeUser(0.99988,1.00001);
	h1_RecTruthOvRec[2] ->Draw("hist P");
	h1_RecTruthOvRec[2] ->SetTitle("");
	myCan->SaveAs(resultDir+"/h1_WpEle_RecTruthOvRec.png");
	
	h1_Wpt[2] ->Write("h1_WpEle_WptOvWcharge_pt");
	h1_Wpt[2]->GetYaxis()->SetRangeUser(0.98,1.02);
	h1_Wpt[2] ->Draw();
	h1_Wpt[2] ->SetTitle("");
	myCan->SaveAs(resultDir+"/h1_WpEle_WptOvWcharge_pt.png");
	
	Fout << "============================ WpToEleNu =================================" << endl;
	for( int ipt(1);ipt<=h1_Post_BothOvTruth[2]->GetNbinsX(); ipt++)
	{
	  //Fout <<ipt<<"\t"<<100*(h1_Post_BothOvTruth_weightFSR[2]->GetBinContent(ipt) - h1_Post_BothOvTruth[2]->GetBinContent(ipt))/h1_Post_BothOvTruth[2]->GetBinContent(ipt)<<endl;
	  double FSRsyst = 100*(h1_Post_BothOvTruth_weightFSR[2]->GetBinContent(ipt) - h1_Post_BothOvTruth[2]->GetBinContent(ipt))/h1_Post_BothOvTruth[2]->GetBinContent(ipt);
	  Fout <<ipt<<"\t"<<FSRsyst<<endl;
	  h1_MCEventFSRSyst->SetBinContent(ipt, FSRsyst);
	}
	h1_MCEventFSRSyst->Write();
	break;
      case 3:
	h1_Post_BothOvTruth[3]->Write("h1_WmEl_BothOvTruth");
	h1_Post_BothOvTruth[3]->Draw();
	h1_Post_BothOvTruth[3]->SetTitle("");
	myCan->SaveAs(resultDir+"/h1_WmEl_BothOvTruth.png");

	h1_Post_BothOvTruth_Inverse[3]->Write("h1_WmEl_BothOvTruth_Inverse");
	h1_Post_BothOvTruth_Inverse[3]->Draw();
	h1_Post_BothOvTruth_Inverse[3]->SetTitle("");
	myCan->SaveAs(resultDir+"/h1_WmEl_BothOvTruth_Inverse.png");

	h1_Post_BothOvTruth_weightFSR[3]->Write("h1_WmEl_BothOvTruth_weightFSR");
	h1_Post_BothOvTruth_weightFSR[3]->Draw();
	h1_Post_BothOvTruth_weightFSR[3]->SetTitle("");
	myCan->SaveAs(resultDir+"/h1_WmEl_BothOvTruth_weightFSR.png");

	h1_Post_PostOvBoth[3] ->Write("h1_WmEl_PostOvBoth");
	h1_Post_PostOvBoth[3]->Draw();
	h1_Post_PostOvBoth[3]->SetTitle("");
	myCan->SaveAs(resultDir+"/h1_WmEl_PostOvBoth.png");

	h1_Born_BothOvBorn[3] ->Write("h1_WmEl_BothOvBorn");
	h1_Born_BothOvBorn[3] ->Draw();
	h1_Born_BothOvBorn[3] ->SetTitle("");
	myCan->SaveAs(resultDir+"/h1_WmEl_BothOvBorn.png");
	
	h1_RecOvBorn[3] ->Write("h1_WmEle_RecOvBorn");
	h1_RecOvBorn[3] ->Draw();
	h1_RecOvBorn[3] ->SetTitle("");
	myCan->SaveAs(resultDir+"/h1_WmEle_RecOvBorn.png");

	h1_RecOvPostFSR[3] ->Write("h1_WmEle_RecOvPostFSR");
	h1_RecOvPostFSR[3] ->Draw();
	h1_RecOvPostFSR[3] ->SetTitle("");
	myCan->SaveAs(resultDir+"/h1_WmEle_RecOvPostFSR.png");

	h1_PostOvBorn[3] ->Write("h1_WmEle_PostOvBorn");
	h1_PostOvBorn[3] ->Draw();
	h1_PostOvBorn[3] ->SetTitle("");
	myCan->SaveAs(resultDir+"/h1_WmEle_PostOvBorn.png");
	
	h1_PostMultBorn[3] ->Write("h1_WmEle_PostMultBorn");
	h1_PostMultBorn[3] ->Draw();
	h1_PostMultBorn[3] ->SetTitle("");
	myCan->SaveAs(resultDir+"/h1_WmEle_PostMultBorn.png");
	
	h1_RecTruthOvRec[3] ->Write("h1_WmEle_RecTruthOvRec");
	h1_RecTruthOvRec[3]->GetYaxis()->SetRangeUser(0.9999,1.00001);
	h1_RecTruthOvRec[3] ->Draw("hist P");
	h1_RecTruthOvRec[3] ->SetTitle("");
	myCan->SaveAs(resultDir+"/h1_WmEle_RecTruthOvRec.png");
	
	h1_Wpt[3] ->Write("h1_WmEle_WptOvWcharge_pt");
	h1_Wpt[3]->GetYaxis()->SetRangeUser(0.98,1.02);
	h1_Wpt[3] ->Draw();
	h1_Wpt[3] ->SetTitle("");
	myCan->SaveAs(resultDir+"/h1_WmEle_WptOvWcharge_pt.png");
	
	Fout << "============================ WmToEleMuNu =================================" << endl;
	for( int ipt(1);ipt<=h1_Post_BothOvTruth[3]->GetNbinsX(); ipt++)
	{
	  //Fout <<ipt<<"\t"<<100*(h1_Post_BothOvTruth_weightFSR[3]->GetBinContent(ipt) - h1_Post_BothOvTruth[3]->GetBinContent(ipt))/h1_Post_BothOvTruth[3]->GetBinContent(ipt)<<endl;
	  double FSRsyst = 100*(h1_Post_BothOvTruth_weightFSR[3]->GetBinContent(ipt) - h1_Post_BothOvTruth[3]->GetBinContent(ipt))/h1_Post_BothOvTruth[3]->GetBinContent(ipt);
	  Fout <<ipt<<"\t"<<FSRsyst<<endl;
	  h1_MCEventFSRSyst->SetBinContent(ipt, FSRsyst);
	}
	h1_MCEventFSRSyst->Write();
	break;
      default:
	cout<<"Error: which case huh?"<<endl;
	exit(-1);
    }
  }
  return 0;
}
