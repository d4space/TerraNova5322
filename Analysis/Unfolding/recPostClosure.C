
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

TH1D* makeDiffHist(TH1D* hData, TH1D* hPowheg, const TString name);

int recPostClosure
(TString UnfoldFile,TString AcceptFile,TString BaseName)
{
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

  cout<<"Processing "<<BaseName<<" RecPost Closure Test"<<endl;
  cout<<"Unfolding Inpufile: "<<UnfoldFile<<endl;
  cout<<"Acceptance Inpufile: "<<AcceptFile<<endl;

  TString resultDir = "RstRecPostClosure";
  //TString resultDir = "Result"+BaseName;
  char tmpName[30];
  TString tmpTStr;

  //ofstream of_Post_WpT_PostFid;

  TFile *f_Unfold = new TFile(UnfoldFile);
  TFile *f_Accept = new TFile(AcceptFile);
  TFile *f_Eff    = new TFile("ResultUnfEff/eff.root");

  //of_Post_WpT_PostFid.open(tmpTStr);

  //TStyle *myStyle=new TStyle("myStyle","myStyle");
  //myStyle->SetPalette(1);
  //gStyle->SetPalette(1);

  // Unfolding to Post
  TH1D *h1_Truth_Rec;
  TH1D *h1_Truth_Rec_Even;
  TH1D *h1_Truth_Rec_Odd;
  TH1D *h1_Truth_Post;
  TH1D *h1_Truth_Post_Even;
  TH1D *h1_Truth_Post_Odd;
  TH2D *h2_Truth_Rec_AP_Post;
  TH2D *h2_Truth_Rec_AP_Post_Ivs;
  TH1D *EqBin_Truth_Rec_Even;

  // Acceptance
  TH1D*	h1_Born_AP;
  TH1D*	h1_Born_BornFid;
  TH1D*	h1_Born_BornFid_Even;
  TH1D*	h1_Born_BothFid;

  TH1D*	h1_Post_PostFid;
  TH1D*	h1_Post_PostFid_Even;
  TH1D*	h1_Post_PostFid_Lumi; // Lumi weighted
  TH1D*	h1_Post_BothFid;
  TH1D* h1_Post_BothFid_Even;

  TH2D*	h2_PostBorn_BothFid;

  // Ivs Method
  TH2D*	h2_PostBorn_BothFid_Ivs;
  TH1D* h1_Unfolded_Inv;

  // Efficiency
  TH1D* h1_Post_BothOvTruth; 
  TH1D* h1_Post_PostOvBoth; 
  TH1D* h1_Born_BothOvBorn; 
  // SVD input
  struct histSVD{
    TH2D *Adet;
    TH2D *uAdetCov;
    TH1D *xini; // Post True
    TH1D *bini; // Reco Truth
    TH1D *data;
    TH1D *True;
    TH1D *Gen;
    TH1D *EffCorr;
    TH2D *statCov;
    TH1D *unfRes;
    TH1D *dDist;
    TH1D *svDist;
    TH2D *uStatCov;
    TH2D *uTauCov;
    TH2D *uInvCov;
  };
  histSVD SVD;
  // Data

  // Define Histo
  SVD.xini=new TH1D("xini","true",NWptBinPlus-1,0,NWptBinPlus-1);
  SVD.bini=new TH1D("bini","thruth" ,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD.data=new TH1D("data","data"    ,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD.True=new TH1D("True","True"    ,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD.Gen=new TH1D("True","True"    ,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD.Adet=new TH2D("Adet","detector response",
      NWptBinPlus-1,0,NWptBinPlus-1,
      NWptBinPlus-1,0,NWptBinPlus-1);

  SVD.statCov =
    new TH2D("statCov","Covariance matrix",
	NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
	//NWptBinPlus-1,Bins,NWptBinPlus-1,Bins;

  // Plot
  CPlot *pltRes;
  CPlot *pltResIvs;
  CPlot *pltUnfIvs;
  CPlot *pltWpT;
  CPlot *pltSVD_Unf;
  CPlot *pltSVD_cov;
  CPlot *pltSVD_d;

  CPlot *pltSVD_UnfDiff;


  TCanvas *myCan = MakeCanvas("myCan","myCan",900,800);

 //TCanvas *lC0 = new TCanvas("Can","Can",900,1000); lC0->cd(); lC0->SetLogy();
 TCanvas *lC0 = new TCanvas("Can","Can",900,800); lC0->cd(); lC0->SetLogy();
 lC0->Divide(1,2,0,0);
 lC0->cd(1)->SetPad(0,0.35,0.95,1.0);
 lC0->cd(1)->SetTopMargin(0.1);
 lC0->cd(1)->SetBottomMargin(0.01);
 lC0->cd(1)->SetLeftMargin(0.15);
 lC0->cd(1)->SetRightMargin(0.07);
 lC0->cd(1)->SetTickx(1);
 lC0->cd(1)->SetTicky(1);
 lC0->cd(2)->SetPad(0,0,0.95,0.345);
 lC0->cd(2)->SetTopMargin(0.025);
 lC0->cd(2)->SetBottomMargin(0.3);
 lC0->cd(2)->SetLeftMargin(0.15);
 lC0->cd(2)->SetRightMargin(0.07);
 lC0->cd(2)->SetTickx(1);
 lC0->cd(2)->SetTicky(1);
 gStyle->SetLineWidth(2.);







  char legendName[30];
    
  //=====================
  // Histo from Unfolding
  //=====================
  sprintf(tmpName,"h1_Truth_Rec");
  h1_Truth_Rec = (TH1D*)f_Unfold->Get(tmpName)->Clone(tmpName);
  h1_Truth_Rec->Sumw2();

  sprintf(tmpName,"h1_Truth_Rec_Even");
  h1_Truth_Rec_Even = (TH1D*)f_Unfold->Get(tmpName)->Clone(tmpName);
  h1_Truth_Rec_Even->Sumw2();

  sprintf(tmpName,"h1_Truth_Rec_Odd");
  h1_Truth_Rec_Odd = (TH1D*)f_Unfold->Get(tmpName)->Clone(tmpName);
  h1_Truth_Rec_Odd->Sumw2();


  sprintf(tmpName,"h1_Truth_Post");
  h1_Truth_Post = (TH1D*)f_Unfold->Get(tmpName)->Clone(tmpName);
  h1_Truth_Post->Sumw2();
  sprintf(tmpName,"h1_Truth_Post_Even");
  h1_Truth_Post_Even = (TH1D*)f_Unfold->Get(tmpName)->Clone(tmpName);
  h1_Truth_Post_Even->Sumw2();
  sprintf(tmpName,"h1_Truth_Post_Odd");
  h1_Truth_Post_Odd = (TH1D*)f_Unfold->Get(tmpName)->Clone(tmpName);
  h1_Truth_Post_Odd->Sumw2();


  sprintf(tmpName,"h2_Truth_Rec_AP_Post");
  h2_Truth_Rec_AP_Post=(TH2D*)f_Unfold->Get(tmpName)->Clone(tmpName);
  InitHist2D(h2_Truth_Rec_AP_Post);
  h2_Truth_Rec_AP_Post->Sumw2();

  //======================
  // Histo from Acceptance 
  //======================
  sprintf(tmpName,"h1_Born_AP");
  h1_Born_AP		=(TH1D*)f_Accept->Get(tmpName)->Clone(tmpName);
  sprintf(tmpName,"h1_Born_BornFid");
  h1_Born_BornFid	=(TH1D*)f_Accept->Get(tmpName)->Clone(tmpName);
  sprintf(tmpName,"h1_Born_BornFid_Even");
  h1_Born_BornFid_Even	=(TH1D*)f_Accept->Get(tmpName)->Clone(tmpName);
  sprintf(tmpName,"h1_Born_BothFid");
  h1_Born_BothFid	=(TH1D*)f_Accept->Get(tmpName)->Clone(tmpName);

  sprintf(tmpName,"h1_Post_PostFid");
  h1_Post_PostFid	=(TH1D*)f_Accept->Get(tmpName)->Clone(tmpName);
  h1_Post_PostFid_Lumi	=(TH1D*)h1_Post_PostFid->Clone("h1_Post_PostFid_Lumi");
  h1_Post_PostFid_Lumi->Sumw2();
  h1_Post_PostFid_Lumi->Scale(LumiWeight_Muon_WpToMuNu_S8);
  sprintf(tmpName,"h1_Post_PostFid_Even");
  h1_Post_PostFid_Even	=(TH1D*)f_Accept->Get(tmpName)->Clone(tmpName);
  sprintf(tmpName,"h1_Post_BothFid");
  h1_Post_BothFid	=(TH1D*)f_Accept->Get(tmpName)->Clone(tmpName);
  sprintf(tmpName,"h2_PostBorn_BothFid");
  h2_PostBorn_BothFid	=(TH2D*)f_Accept->Get(tmpName)->Clone(tmpName);

  //======================
  // Histo from Efficiency
  //======================
  if( BaseName == "WpToMuNu")
  {
    sprintf(tmpName,"h1_WpMu_BothOvTruth");
    h1_Post_BothOvTruth = (TH1D*)f_Eff->Get(tmpName)->Clone();
    sprintf(tmpName,"h1_WpMu_PostOvBoth");
    h1_Post_PostOvBoth = (TH1D*)f_Eff->Get(tmpName)->Clone();
    sprintf(tmpName,"h1_WpMu_BothOvBorn");
    h1_Born_BothOvBorn = (TH1D*)f_Eff->Get(tmpName)->Clone();
  }else if (BaseName == "WmToMuNu")
  {
    sprintf(tmpName,"h1_WmMu_BothOvTruth");
    h1_Post_BothOvTruth = (TH1D*)f_Eff->Get(tmpName)->Clone();
    sprintf(tmpName,"h1_WmMu_PostOvBoth");
    h1_Post_PostOvBoth = (TH1D*)f_Eff->Get(tmpName)->Clone();
    sprintf(tmpName,"h1_WmMu_BothOvBorn");
    h1_Born_BothOvBorn = (TH1D*)f_Eff->Get(tmpName)->Clone();
  }else if (BaseName == "WpToEleNu")
  {
    sprintf(tmpName,"h1_WpEl_BothOvTruth");
    h1_Post_BothOvTruth = (TH1D*)f_Eff->Get(tmpName)->Clone();
    sprintf(tmpName,"h1_WpEl_PostOvBoth");
    h1_Post_PostOvBoth = (TH1D*)f_Eff->Get(tmpName)->Clone();
    sprintf(tmpName,"h1_WpEl_BothOvBorn");
    h1_Born_BothOvBorn = (TH1D*)f_Eff->Get(tmpName)->Clone();
  }else if (BaseName == "WmToEleNu")
  {
    sprintf(tmpName,"h1_WmEl_BothOvTruth");
    h1_Post_BothOvTruth = (TH1D*)f_Eff->Get(tmpName)->Clone();
    sprintf(tmpName,"h1_WmEl_PostOvBoth");
    h1_Post_PostOvBoth = (TH1D*)f_Eff->Get(tmpName)->Clone();
    sprintf(tmpName,"h1_WmEl_BothOvBorn");
    h1_Born_BothOvBorn = (TH1D*)f_Eff->Get(tmpName)->Clone();
  }else{
    cout<<"Error: no this BaseName "<<BaseName<<endl;
    exit(-1);
  }
  

  h1_Post_BothFid_Even = (TH1D*)h1_Post_PostFid_Even->Clone("h1_Post_BothFid_Even");
  h1_Post_BothFid_Even->Divide(h1_Post_PostOvBoth);
  // Histo for SVD
  double checkNumber(0);
  int nbins = h1_Post_PostFid->GetNbinsX();
  for(int i(1);i<=nbins;i++)//simul idx
  {
    // xini_Post : All Post without the truth efficiency at PostFid
    SVD.xini->SetBinContent(i,h1_Truth_Post->GetBinContent(i));
    SVD.xini->  SetBinError(i,h1_Truth_Post->GetBinError(i));

    //SVD.xini->SetBinContent(i,h1_Post_PostFid->GetBinContent(i));
    //SVD.xini->  SetBinError(i,h1_Post_PostFid->GetBinError(i));

    // Detector simulation one
    SVD.bini->SetBinContent(i,h1_Truth_Rec->GetBinContent(i));
    SVD.bini->  SetBinError(i,h1_Truth_Rec->GetBinError(i));

    //TODO data from real
    //{
    //  SVD.data->SetBinContent(i,h1_Truth_Rec_Even->GetBinContent(i)+2500);
    //  SVD.data->  SetBinError(i,h1_Truth_Rec_Even->GetBinError(i));
    //}
    //else if( i == 2)
    //{
     // SVD.data->SetBinContent(i,h1_Truth_Rec_Even->GetBinContent(i)-2500);
     // SVD.data->  SetBinError(i,h1_Truth_Rec_Even->GetBinError(i));
    //}else {}

    SVD.data->SetBinContent(i,h1_Truth_Rec_Even->GetBinContent(i));
    SVD.data->  SetBinError(i,h1_Truth_Rec_Even->GetBinError(i));



    //SVD.True->SetBinContent(i,h1_Post_PostFid_Lumi->GetBinContent(i));
    SVD.True->SetBinContent(i,h1_Truth_Post_Even->GetBinContent(i));
    SVD.True->  SetBinError(i,h1_Truth_Post_Even->GetBinError(i));

    SVD.Gen->SetBinContent(i,h1_Post_BothFid_Even->GetBinContent(i));
    SVD.Gen->  SetBinError(i,h1_Post_BothFid_Even->GetBinError(i));

    //SVD.True->SetBinContent(i,h1_Post_PostFid_Even->GetBinContent(i));
    //SVD.True->  SetBinError(i,h1_Post_PostFid_Even->GetBinError(i));


    //of_Post_WpT_PostFid<<h1_Post_WpT_PostFid->GetBinContent(i)<<endl;
    for( int j(1);j<=nbins;j++)//gen idx
    {
      if(i==5) checkNumber += h2_Truth_Rec_AP_Post->GetBinContent(i,j);
      SVD.Adet->SetBinContent(i,j,h2_Truth_Rec_AP_Post->GetBinContent(i,j));
      //Adet_Post->SetBinError(i,j,h2_Truth_Rec_AP_Post->GetBinError(i,j));
    }
  }
  //SVD.data->Scale(1/LumiWeight_Muon_WpToMuNu_S8);
  cout<<"check the number 5th bin(h1,response) "<<h1_Post_BothFid->GetBinContent(5)<<" "<<checkNumber<<endl;
  //=================================================================
  //
  //============================
  // Unfolding w/ Inverse Matrix <><><><><><><><><><><><><><><><><><>
  //============================
  //
  //=================================================================
  Unfolder unfold("Post");
  unfold.setTrue(h1_Truth_Post); //dumy for set up the bin ranges
  unfold.setMeas(h1_Truth_Rec_Even);
  unfold.colNormalize(h2_Truth_Rec_AP_Post);
  unfold.setMigrationMatrix(h2_Truth_Rec_AP_Post);
  unfold.unfold();

  h2_Truth_Rec_AP_Post_Ivs = unfold.getMigHistInverse();
  h1_Unfolded_Inv = (TH1D*)unfold.getUnfolded()->Clone("h1_Unfolded_Inv");
  //Response matrix
  h2_Truth_Rec_AP_Post->GetYaxis()->SetMoreLogLabels();
  h2_Truth_Rec_AP_Post->GetYaxis()->SetNoExponent();
  h2_Truth_Rec_AP_Post->GetXaxis()->SetMoreLogLabels();
  h2_Truth_Rec_AP_Post->GetXaxis()->SetNoExponent();
  tmpTStr = "Response_"+BaseName;
  pltRes=
    new CPlot(tmpTStr,"","Rec WpT [GeV]","Post WpT [GeV]");
  pltRes->setOutDir(resultDir);//drawopt, fillcolor, linecolor
  pltRes->AddHist2D(h2_Truth_Rec_AP_Post,"COLZ",kWhite,kBlack);
  pltRes->SetLogx();
  pltRes->SetLogy();
  pltRes->Draw(myCan,kTRUE,"png");
  // Inverse Matrix
  tmpTStr = "ResponseIvs_"+BaseName;
  pltResIvs=
    new CPlot(tmpTStr,"","Post WpT [GeV]","Rec WpT [GeV]");;
  pltResIvs->setOutDir(resultDir);//drawopt, fillcolor, linecolor
  pltResIvs->AddHist2D(h2_Truth_Rec_AP_Post_Ivs,"COLZ",kWhite,kBlack);
  pltResIvs->SetLogx();
  pltResIvs->SetLogy();
  pltResIvs->Draw(myCan,kTRUE,"png");

  // Unfold histo with InverseMatrix method
  tmpTStr = "UnfIvs_"+BaseName;
  pltUnfIvs =
    new CPlot(tmpTStr,"","W pT [GeV]","Event");
  pltUnfIvs->setOutDir(resultDir);
     //AddHist1D(TH1D *h, TString drawopt="", int color=kBlack, int linesty=1, int fillsty=0, int mkerSty=20, int mkerSize=1)
  //pltUnfIvs->AddHist1D(h1_Post_WpT_PostFid_Even,"",kBlack,1,0,0,0);
  pltUnfIvs->AddHist1D(h1_Post_PostFid_Even,"e",kBlack,1,0,22,1); // Not exactly
  pltUnfIvs->AddHist1D(h1_Truth_Rec_Even,"e",kBlue,1,0,24,1);
  pltUnfIvs->AddHist1D(h1_Unfolded_Inv,"e",kRed,1,0,20,1);
  pltUnfIvs->SetLegend(0.68,0.57,0.93,0.8);
  pltUnfIvs->GetLegend()->AddEntry(h1_Post_PostFid_Even,"Post","l");
  pltUnfIvs->GetLegend()->AddEntry(h1_Truth_Rec_Even,"Rec","l");
  pltUnfIvs->GetLegend()->AddEntry(h1_Unfolded_Inv,"Unfolded","p");
  pltUnfIvs->SetLogx(1);
  //pltUnfIvs->SetLogy(1);
  pltUnfIvs->Draw(myCan,kTRUE,"png");

  //of_Post_WpT_PostFid.close();


  // Plot for GenLevel and Simulation
  // AddHist1D(TH1D *h, TString drawopt, int color, int linesty, int fillsty, int mkerSty, int mkerSize)
  // AddHist1D(TH1D *h, TString label, TString drawopt, int color, int linesty, int fillsty)
 
  InitHist(h1_Born_BornFid);
  //h1_Post_WpT_PostFid->GetXaxis()->SetLimits(0.00001,10000);
  tmpTStr = "WpT_All_"+BaseName;
  pltWpT=new CPlot(tmpTStr,"","WpT [GeV]","Events");
  pltWpT->SetLogx();
  pltWpT->setOutDir(resultDir);
  pltWpT->AddHist1D(h1_Post_PostFid,"p",kBlack,1,0,20,2.);
  pltWpT->AddHist1D(h1_Truth_Post,"p",kBlue,1,0,24,2.);
  pltWpT->AddHist1D(h1_Truth_Rec,"p",kRed,1,0,26,2.);
  pltWpT->SetLegend(0.6,0.57,0.83,0.8);
  pltWpT->GetLegend()->AddEntry(h1_Post_PostFid,"Post PostFid","lp");
  pltWpT->GetLegend()->AddEntry(h1_Truth_Post,"Post Truth","lp");
  pltWpT->GetLegend()->AddEntry(h1_Truth_Rec,"Rec Truth","lp");
  pltWpT->Draw(myCan,kTRUE,"png");

  //==============================
  // TSVD
  // =============================
  TRandom3 R;
  TSVDUnfold *tsvdUnf = new TSVDUnfold(
      SVD.data, SVD.bini, SVD.xini, SVD.Adet);
  SVD.statCov = tsvdUnf->GetBCov();
  tsvdUnf->SetNormalize(kFALSE);
  //SVD.unfRes = tsvdUnf->Unfold(6);
  SVD.unfRes = tsvdUnf->Unfold(4);
  SVD.dDist = tsvdUnf->GetD();
  SVD.svDist = tsvdUnf->GetSV();
  SVD.uStatCov = tsvdUnf->GetUnfoldCovMatrix(SVD.statCov,100);
  SVD.uAdetCov = tsvdUnf->GetAdetCovMatrix(100);
  SVD.uStatCov->Add(SVD.uAdetCov);
  SVD.uTauCov = tsvdUnf->GetXtau();
  SVD.uTauCov->Add(SVD.uAdetCov);
  SVD.uInvCov = tsvdUnf->GetXinv();


  for(int i(1); i<= SVD.unfRes->GetNbinsX();i++)
  {
    SVD.unfRes->SetBinError(i, TMath::Sqrt(SVD.uTauCov->GetBinContent(i,i)));
  }
  SVD.EffCorr = (TH1D*)SVD.unfRes->Clone("EffCorr");
  SVD.EffCorr->Sumw2();
  SVD.EffCorr->Multiply(h1_Post_BothOvTruth);

  TH1D* drawDifference;
  drawDifference = makeDiffHist(SVD.unfRes,SVD.True,"drawDifference");
  drawDifference->SetMarkerStyle(kFullCircle);
  drawDifference->SetMarkerSize(0.9);
  SVD.unfRes->GetXaxis()->SetLabelSize(0.0);



  //SVD.unfRes->GetYaxis()->SetMoreLogLabels();
  //SVD.unfRes->GetYaxis()->SetNoExponent();
  tmpTStr = "SVD_Unf_"+BaseName;
  pltSVD_Unf = new CPlot(tmpTStr,"","W pT [GeV]","Event");
  pltSVD_Unf->setOutDir(resultDir);
//AddHist1D(TH1D *h, TString drawopt, int color, int linesty, int fillsty, int mkerSty, int mkerSize)
  pltSVD_Unf->AddHist1D(SVD.unfRes,"elp",kBlue,0,0,20,2.0);
  pltSVD_Unf->AddHist1D(SVD.data,"elp",kRed,0,0,24,2.0);
  pltSVD_Unf->AddHist1D(SVD.True,"hist",kBlack,1,0,0,0);
//  pltSVD_Unf->AddHist1D(SVD.Gen,"hist",kGreen,1,0,0,0);
//  pltSVD_Unf->AddHist1D(SVD.EffCorr,"elp",kGreen+2,0,0,26,2.0);
  pltSVD_Unf->SetLegend(0.68,0.57,0.93,0.8);
  //pltSVD_Unf->SetLegend(0.55,0.55,0.9,0.8);
  pltSVD_Unf->GetLegend()->AddEntry(SVD.unfRes,"Unfolded","p");
  pltSVD_Unf->GetLegend()->AddEntry(SVD.data,"Rec","p");
//  pltSVD_Unf->GetLegend()->AddEntry(SVD.True,"Truth","l");
  pltSVD_Unf->GetLegend()->AddEntry(SVD.True,"PowhegPythia","l");
//  pltSVD_Unf->GetLegend()->AddEntry(SVD.Gen,"Post","l");
//  pltSVD_Unf->GetLegend()->AddEntry(SVD.EffCorr,"EffCorr","p");
 // pltSVD_Unf->Draw(myCan,kTRUE,"png");
  pltSVD_Unf->Draw(lC0,kFALSE,"png",1);

  tmpTStr = "DetUnf_"+BaseName;
  //pltSVD_UnfDiff = new CPlot(tmpTStr,"","W p_{T} [GeV]","Unfolded/Powheg Pythia");
  pltSVD_UnfDiff = new CPlot(tmpTStr,"","W p_{T} [Bins]","Unfolded/Powheg Pythia");
  pltSVD_UnfDiff->setOutDir(resultDir);
  pltSVD_UnfDiff->AddHist1D(drawDifference,"EX0",kBlack);
  pltSVD_UnfDiff->SetYRange(0.4,1.6);
  //pltSVD_UnfDiff->SetYRange(0.9,1.1);
  pltSVD_UnfDiff->AddLine(0,1,13, 1,kBlack,2);
  pltSVD_UnfDiff->Draw(lC0,kTRUE,"png",2);


  tmpTStr = "SVD_cov_"+BaseName;
  pltSVD_cov = new CPlot(tmpTStr,"TSVDUnfold Covariance matrix","","");
  pltSVD_cov->setOutDir(resultDir);
  pltSVD_cov->AddHist2D(SVD.uStatCov,"COLZ",kWhite,kBlack);
  pltSVD_cov->Draw(myCan,kTRUE,"png");

  tmpTStr = "SVD_d_"+BaseName;
  pltSVD_d = new CPlot(tmpTStr,"TSVDUnfold |di|","i","|d_{i}|");
  pltSVD_d->setOutDir(resultDir);
  pltSVD_d->AddHist1D(SVD.dDist,"",kBlack,1,0,0,0);
  pltSVD_d->AddLine(0,1,13,1,kBlack,1);
  pltSVD_d->Draw(myCan,kTRUE,"png");

  return 0;
}

TH1D *makeDiffHist(TH1D* hData, TH1D* hPowheg, const TString name)
{
  TH1D *hDiff = new TH1D(name,"",hData->GetNbinsX(),hData->GetXaxis()->GetXmin(),hData->GetXaxis()->GetXmax());
  for(Int_t ibin=1; ibin<=hData->GetNbinsX(); ibin++) {
    Double_t diff = (hData->GetBinContent(ibin)/hPowheg->GetBinContent(ibin));
    Double_t err = hData->GetBinError(ibin)/hPowheg->GetBinContent(ibin);
    hDiff->SetBinContent(ibin,diff);
    hDiff->SetBinError(ibin,err);
  }
  hDiff->GetYaxis()->SetTitleOffset(0.8);
  hDiff->GetYaxis()->SetTitleSize(0.07);
  hDiff->GetYaxis()->SetLabelSize(0.08);
  hDiff->GetYaxis()->CenterTitle();
  hDiff->GetXaxis()->SetTitleOffset(1.0);
  hDiff->GetXaxis()->SetTitleSize(0.08);
  hDiff->GetXaxis()->SetLabelSize(0.08);
  return hDiff;
}

