
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

int wPtUnfoldStudy
(TString UnfoldFile,TString AcceptFile,TString DataFile,TString BaseName)
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

  cout<<"Processing "<<BaseName<<endl;
  cout<<"Unfolding Inpufile: "<<UnfoldFile<<endl;
  cout<<"Acceptance Inpufile: "<<AcceptFile<<endl;
  cout<<"Data Inpufile: "<<DataFile<<endl;

  TString resultDir = "Result"+BaseName;
  gSystem->mkdir(resultDir,kTRUE);
  char tmpName[30];
  TString tmpTStr;

  //ofstream of_Post_WpT_PostFid;

  TFile *f_Unfold = new TFile(UnfoldFile);
  TFile *f_Accept = new TFile(AcceptFile);
  TFile *f_Data   = new TFile(DataFile);

  TFile *f_Eff    = new TFile("ResultUnfEff/eff.root");
  tmpTStr = resultDir+"/Result_"+BaseName+".root";
  TFile *f_Out    = new TFile(tmpTStr,"recreate");

  //tmpTStr= resultDir+"/"+"Post_PostFid.txt";
  //of_Post_WpT_PostFid.open(tmpTStr);

  //TStyle *myStyle=new TStyle("myStyle","myStyle");
  //myStyle->SetPalette(1);
  //gStyle->SetPalette(1);
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
  histSVD SVD_Post;
  histSVD SVD_Born;

  // Efficiency
  TH1D* h1_Post_BothOvTruth; 
  TH1D* h1_Post_BothOvTruth_eqBin; 
  TH1D* h1_Born_BothOvBorn; 
  TH1D* h1_Born_BothOvBorn_eqBin; 

  // Unfolding to Post
  TH1D *h1_Truth_Rec;
  TH1D *h1_Truth_Rec_Even;
  TH1D *h1_Truth_Rec_Odd;
  TH1D *h1_Truth_Post;
  TH1D *h1_Truth_Post_Lumi;
  TH1D *h1_Truth_Post_Even;
  TH1D *h1_Truth_Post_Odd;
  TH2D *h2_Truth_Rec_AP_Post;
  TH2D *h2_Truth_Rec_AP_Post_Ivs;
  TH1D *h1_Unfolded_Post_InvMthd;
  TH1D *EqBin_Truth_Rec_Even;


  // Acceptance
  TH1D*	h1_Born_AP;
  TH1D*	h1_Born_BornFid;
  TH1D*	h1_Born_BornFid_Even;
  TH1D*	h1_Born_BornFid_Lumi;
  TH1D*	h1_Born_BothFid;
  TH1D*	h1_Born_BothFid_Lumi;

  TH1D*	h1_Post_PostFid;
  TH1D*	h1_Post_PostFid_Even;
  TH1D*	h1_Post_PostFid_Lumi; // Lumi weighted
  TH1D*	h1_Post_BothFid;
  TH1D*	h1_Post_BothFid_Lumi;

  TH2D*	h2_PostBorn_BothFid;

  TH1D* EqBin_Post_PostFid_Even;

  // Data
  TH1D* h1_Data_SigYild;

  // Define Histo
  h1_Post_BothOvTruth_eqBin=
    new TH1D("h1_Post_BothOvTruth_eqBin","BothOvTruth",NWptBinPlus-1,0,NWptBinPlus-1);
  h1_Born_BothOvBorn_eqBin=
    new TH1D("h1_Born_BothOvBorn_eqBin","BothOvBorn",NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Post.xini=new TH1D("xini_Post","Post true",NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Post.bini=new TH1D("bini_Post","Reco thruth" ,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Post.data=new TH1D("data_Rec","data_Rec"    ,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Post.True=new TH1D("SVD_Post.True","SVD_Post.True",NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Post.Gen=new TH1D("SVD_Post.Gen","SVD_Post.Gen",NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Post.Adet=new TH2D("Adet_Post","detector response",
      NWptBinPlus-1,0,NWptBinPlus-1,
      NWptBinPlus-1,0,NWptBinPlus-1);

  SVD_Post.statCov =
    new TH2D("SVD_Post.statCov","Covariance matrix",
	NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);

  SVD_Born.xini=new TH1D("xini_Born","Born xini",NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Born.bini=new TH1D("bini_Born","Post" ,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Born.data=new TH1D("data_Born","data_Rec"    ,NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Born.True=new TH1D("SVD_Born.True","Born.True",NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Born.Gen=new TH1D("SVD_Born.Gen","Born.Gen",NWptBinPlus-1,0,NWptBinPlus-1);
  SVD_Born.Adet=new TH2D("Adet_Born","detector response",
      NWptBinPlus-1,0,NWptBinPlus-1,
      NWptBinPlus-1,0,NWptBinPlus-1);

  SVD_Born.statCov =
    new TH2D("SVD_Born.statCov","Covariance matrix",
	NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  // Plot
  CPlot *pltUnfPost;
  CPlot *pltUnfPost_cov;
  CPlot *pltUnfPost_d;
  CPlot *pltUnfBorn;
  CPlot *pltUnfBorn_cov;
  CPlot *pltUnfBorn_d;
  TCanvas *myCan = MakeCanvas("myCan","myCan",900,800);


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
  sprintf(tmpName,"h1_Truth_Post_Lumi");
  h1_Truth_Post_Lumi = (TH1D*)h1_Truth_Post->Clone(tmpName);
  h1_Truth_Post_Lumi->Sumw2();
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

  cout<<"Simulated event========================="<<endl;
  int nbins = h1_Truth_Rec->GetNbinsX();
  cout<<"Nsimul N of bins: "<<nbins<<endl;
  double Nsimul = h1_Truth_Rec->Integral();
  cout<<"Total Events: "<<setw(20)<<setprecision(7)<<Nsimul<<endl;
  double NsimulEven = h1_Truth_Rec_Even->Integral();
  cout<<"NsimulEven: "<<setw(20)<<setprecision(7)<<NsimulEven<<endl;
  double NsimulOdd = h1_Truth_Rec_Odd->Integral();
  cout<<"NsimulOdd: "<<setw(20)<<setprecision(7)<<NsimulOdd<<endl;
  double NdetectorResponse = h2_Truth_Rec_AP_Post->Integral();
  cout<<"NdetectorResponse: "<<NdetectorResponse<<endl;
  //======================
  // Histo from Acceptance 
  //======================
  sprintf(tmpName,"h1_Born_AP");
  h1_Born_AP		=(TH1D*)f_Accept->Get(tmpName)->Clone(tmpName);
  sprintf(tmpName,"h1_Born_BornFid");
  h1_Born_BornFid	=(TH1D*)f_Accept->Get(tmpName)->Clone(tmpName);
  h1_Born_BornFid_Lumi=(TH1D*)h1_Born_BornFid->Clone("h1_Born_BornFid_Lumi");
  h1_Born_BornFid_Lumi->Sumw2();
  sprintf(tmpName,"h1_Born_BornFid_Even");
  h1_Born_BornFid_Even	=(TH1D*)f_Accept->Get(tmpName)->Clone(tmpName);
  sprintf(tmpName,"h1_Born_BothFid");
  h1_Born_BothFid	=(TH1D*)f_Accept->Get(tmpName)->Clone(tmpName);
  sprintf(tmpName,"h1_Born_BothFid_Lumi");
  h1_Born_BothFid_Lumi	=(TH1D*)h1_Born_BothFid->Clone(tmpName);

  sprintf(tmpName,"h1_Post_PostFid");
  h1_Post_PostFid	=(TH1D*)f_Accept->Get(tmpName)->Clone(tmpName);
  h1_Post_PostFid_Lumi	=(TH1D*)h1_Post_PostFid->Clone("h1_Post_PostFid_Lumi");
  h1_Post_PostFid_Lumi->Sumw2();

  sprintf(tmpName,"h1_Post_BothFid");
  h1_Post_BothFid	=(TH1D*)f_Accept->Get(tmpName)->Clone(tmpName);
  sprintf(tmpName,"h1_Post_BothFid_Lumi");
  h1_Post_BothFid_Lumi	=(TH1D*)h1_Post_BothFid->Clone(tmpName);
  h1_Post_BothFid_Lumi->Sumw2();
  sprintf(tmpName,"h2_PostBorn_BothFid");
  h2_PostBorn_BothFid	=(TH2D*)f_Accept->Get(tmpName)->Clone(tmpName);

  if(BaseName == "WpToMuNu")
  {
    h1_Truth_Post_Lumi  ->Scale(LumiWeight_Muon_WpToMuNu_S8);
    h1_Post_PostFid_Lumi->Scale(LumiWeight_Muon_WpToMuNu_S8);
    h1_Post_BothFid_Lumi->Scale(LumiWeight_Muon_WpToMuNu_S8);
    h1_Born_BornFid_Lumi->Scale(LumiWeight_Muon_WpToMuNu_S8);
    h1_Born_BothFid_Lumi->Scale(LumiWeight_Muon_WpToMuNu_S8);
    sprintf(tmpName,"h1_WpMu_BothOvTruth");
    h1_Post_BothOvTruth = (TH1D*)f_Eff->Get(tmpName)->Clone();
    sprintf(tmpName,"h1_WpMu_BothOvBorn");
    h1_Born_BothOvBorn = (TH1D*)f_Eff->Get(tmpName)->Clone();
  }
  else if(BaseName == "WmToMuNu")
  {
    h1_Truth_Post_Lumi  ->Scale(LumiWeight_Muon_WmToMuNu_S8);
    h1_Post_PostFid_Lumi->Scale(LumiWeight_Muon_WmToMuNu_S8);
    h1_Post_BothFid_Lumi->Scale(LumiWeight_Muon_WmToMuNu_S8);
    h1_Born_BornFid_Lumi->Scale(LumiWeight_Muon_WmToMuNu_S8);
    h1_Born_BothFid_Lumi->Scale(LumiWeight_Muon_WmToMuNu_S8);
    sprintf(tmpName,"h1_WmMu_BothOvTruth");
    h1_Post_BothOvTruth = (TH1D*)f_Eff->Get(tmpName)->Clone();
    sprintf(tmpName,"h1_WmMu_BothOvBorn");
    h1_Born_BothOvBorn = (TH1D*)f_Eff->Get(tmpName)->Clone();
  }
  else if(BaseName == "WpToEleNu")
  {
    h1_Truth_Post_Lumi->  Scale(LumiWeight_Ele_WpToEleNu_S8);
    h1_Post_PostFid_Lumi->Scale(LumiWeight_Ele_WpToEleNu_S8);
    h1_Post_BothFid_Lumi->Scale(LumiWeight_Ele_WpToEleNu_S8);
    h1_Born_BornFid_Lumi->Scale(LumiWeight_Ele_WpToEleNu_S8);
    h1_Born_BothFid_Lumi->Scale(LumiWeight_Ele_WpToEleNu_S8);
    sprintf(tmpName,"h1_WpEl_BothOvTruth");
    h1_Post_BothOvTruth = (TH1D*)f_Eff->Get(tmpName)->Clone();
    sprintf(tmpName,"h1_WpEl_BothOvBorn");
    h1_Born_BothOvBorn = (TH1D*)f_Eff->Get(tmpName)->Clone();
  }
  else if(BaseName == "WmToEleNu")
  {
    h1_Truth_Post_Lumi->  Scale(LumiWeight_Ele_WmToEleNu_S8);
    h1_Post_PostFid_Lumi->Scale(LumiWeight_Ele_WmToEleNu_S8);
    h1_Post_BothFid_Lumi->Scale(LumiWeight_Ele_WmToEleNu_S8);
    h1_Born_BornFid_Lumi->Scale(LumiWeight_Ele_WmToEleNu_S8);
    h1_Born_BothFid_Lumi->Scale(LumiWeight_Ele_WmToEleNu_S8);
    sprintf(tmpName,"h1_WmEl_BothOvTruth");
    h1_Post_BothOvTruth = (TH1D*)f_Eff->Get(tmpName)->Clone();
    sprintf(tmpName,"h1_WmEl_BothOvBorn");
    h1_Born_BothOvBorn = (TH1D*)f_Eff->Get(tmpName)->Clone();
  }
  else{
    cout<<"Error: there is no BaseName corresponding to "<<BaseName<<endl;
    exit(-1);
  }

  // Histogram from Data
  if(BaseName == "WpToMuNu" || BaseName == "WpToEleNu")
  {
    sprintf(tmpName,"hSigWPpt");
    h1_Data_SigYild	=(TH1D*)f_Data->Get(tmpName)->Clone(tmpName);
  }else if(BaseName == "WmToMuNu" || BaseName == "WmToEleNu")
  {
    sprintf(tmpName,"hSigWMpt");
    h1_Data_SigYild	=(TH1D*)f_Data->Get(tmpName)->Clone(tmpName);
  }else{
    cout<<"Error: Check the BaseName !!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
    exit(-1);
  }
  // Histo for SVD
  double checkNumber(0);
  for(int i(1);i<=nbins;i++)//simul idx
  {
    // xini_Post : All Post without the truth efficiency at PostFid
    SVD_Post.xini->SetBinContent(i,h1_Truth_Post->GetBinContent(i));
    SVD_Post.xini->  SetBinError(i,h1_Truth_Post->GetBinError(i));

    SVD_Born.xini->SetBinContent(i,h1_Born_BothFid->GetBinContent(i));
    SVD_Born.xini->  SetBinError(i,h1_Born_BothFid->GetBinError(i));

    // Detector simulation one
    SVD_Post.bini->SetBinContent(i,h1_Truth_Rec->GetBinContent(i));
    SVD_Post.bini->  SetBinError(i,h1_Truth_Rec->GetBinError(i));

    SVD_Born.bini->SetBinContent(i,h1_Post_BothFid->GetBinContent(i));
    SVD_Born.bini->  SetBinError(i,h1_Post_BothFid->GetBinError(i));

    //TODO data from real
    SVD_Post.data->SetBinContent(i,h1_Data_SigYild->GetBinContent(i));
    SVD_Post.data->  SetBinError(i,h1_Data_SigYild->GetBinError(i));

    SVD_Post.True->SetBinContent(i,h1_Truth_Post_Lumi->GetBinContent(i));
    SVD_Post.True->  SetBinError(i,h1_Truth_Post_Lumi->GetBinError(i));
    SVD_Born.True->SetBinContent(i,h1_Born_BothFid_Lumi->GetBinContent(i));
    SVD_Born.True->  SetBinError(i,h1_Born_BothFid_Lumi->GetBinError(i));

    SVD_Post.Gen->SetBinContent(i,h1_Post_BothFid_Lumi->GetBinContent(i));
    SVD_Post.Gen->  SetBinError(i,h1_Post_BothFid_Lumi->GetBinError(i));
    SVD_Born.Gen->SetBinContent(i,h1_Born_BornFid_Lumi->GetBinContent(i));
    SVD_Born.Gen->  SetBinError(i,h1_Born_BornFid_Lumi->GetBinError(i));

    h1_Post_BothOvTruth_eqBin->SetBinContent(i,h1_Post_BothOvTruth->GetBinContent(i));
    h1_Post_BothOvTruth_eqBin->  SetBinError(i,h1_Post_BothOvTruth->GetBinError(i));
    h1_Born_BothOvBorn_eqBin->SetBinContent(i,h1_Born_BothOvBorn->GetBinContent(i));
    h1_Born_BothOvBorn_eqBin->  SetBinError(i,h1_Born_BothOvBorn->GetBinError(i));

    //of_Post_WpT_PostFid<<h1_Post_WpT_PostFid->GetBinContent(i)<<endl;
    for( int j(1);j<=nbins;j++)//gen idx
    {
      if(i==5) checkNumber += h2_Truth_Rec_AP_Post->GetBinContent(i,j);
      SVD_Post.Adet->SetBinContent(i,j,h2_Truth_Rec_AP_Post->GetBinContent(i,j));
      SVD_Born.Adet->SetBinContent(i,j,h2_PostBorn_BothFid->GetBinContent(i,j));
      //Adet_Post->SetBinError(i,j,h2_Truth_Rec_AP_Post->GetBinError(i,j));
    }
  }
  cout<<"check the number 5th bin(h1,response) "<<h1_Truth_Rec->GetBinContent(5)<<" "<<checkNumber<<endl;
  //=================================================================
  //=================================================================
  // Unfolding from Rec to Post           ===========================
  //=================================================================
  //=================================================================
  //
  //=====================
  // TSVD
  //=====================
  TRandom3 R;
  //===============
  // Data Unfolding
  //===============
  cout<<" Input Data Yield ==============="<<endl;
  cout<<" SignalYield           Error"<<endl;
  for( int i(1); i<= SVD_Post.data->GetNbinsX(); i++)
  {
    cout<<SVD_Post.data->GetBinContent(i)<<"\t"<<SVD_Post.data->GetBinError(i)<<endl;
  }
  TSVDUnfold *tsvdData = new TSVDUnfold(
      SVD_Post.data,SVD_Post.bini,SVD_Post.xini,SVD_Post.Adet);
  SVD_Post.statCov = tsvdData->GetBCov();
  tsvdData->SetNormalize( kFALSE );
  SVD_Post.unfRes = tsvdData->Unfold(4);
  SVD_Post.dDist = tsvdData->GetD();
  SVD_Post.svDist = tsvdData->GetSV();
  SVD_Post.uStatCov = tsvdData->GetUnfoldCovMatrix( SVD_Post.statCov, 100);
  SVD_Post.uAdetCov = tsvdData->GetAdetCovMatrix( 100);
  SVD_Post.uStatCov->Add(SVD_Post.uAdetCov);

  SVD_Post.uTauCov = tsvdData->GetXtau();
  SVD_Post.uTauCov->Add( SVD_Post.uAdetCov);
  for( int i(1);i<=SVD_Post.unfRes->GetNbinsX(); i++)
  {
    SVD_Post.unfRes->SetBinError(i, TMath::Sqrt(SVD_Post.uTauCov->GetBinContent(i,i)));
  }
  SVD_Post.EffCorr = (TH1D*)SVD_Post.unfRes->Clone("PostEffCorr");
  SVD_Post.EffCorr->Sumw2();
  SVD_Post.EffCorr->Multiply(h1_Post_BothOvTruth_eqBin);

  tmpTStr = "Post_Unf_"+BaseName;
  pltUnfPost = new CPlot(tmpTStr,"RecPost Unfolding with SVD","W pT [GeV]","Event");
  pltUnfPost->setOutDir(resultDir);
  pltUnfPost->AddHist1D(SVD_Post.unfRes,"elp",kBlue,1,0,20,2);
  pltUnfPost->AddHist1D(SVD_Post.data,"elp",kRed,1,0,24,2);
  pltUnfPost->AddHist1D(SVD_Post.True,"hist",kBlack,1,0,0,0);
  pltUnfPost->AddHist1D(SVD_Post.Gen,"hist",kGreen,1,0,0,0);
  pltUnfPost->AddHist1D(SVD_Post.EffCorr,"elp",kGreen+2,0,0,26,2.0);
  pltUnfPost->SetLegend(0.68,0.57,0.93,0.8);
  pltUnfPost->GetLegend()->AddEntry(SVD_Post.unfRes,"Unfolded","p");
  pltUnfPost->GetLegend()->AddEntry(SVD_Post.data,"Recon","p");
  pltUnfPost->GetLegend()->AddEntry(SVD_Post.True,"Truth","l");
  pltUnfPost->GetLegend()->AddEntry(SVD_Post.Gen,"Post","l");
  pltUnfPost->GetLegend()->AddEntry(SVD_Post.EffCorr,"EffCorr","p");
  pltUnfPost->Draw(myCan,kTRUE,"png");
  //cout<<"LumiWeight_Muon_WpToMuNu_S8: "<<LumiWeight_Muon_WpToMuNu_S8<<endl;
  tmpTStr = "Post_cov_"+BaseName;
  pltUnfPost_cov = new CPlot(tmpTStr,"TSVDUnfold Covariance matrix","","");
  pltUnfPost_cov->setOutDir(resultDir);
  pltUnfPost_cov->AddHist2D(SVD_Post.uStatCov,"COLZ",kWhite,kBlack);
  pltUnfPost_cov->Draw(myCan,kTRUE,"png");

  tmpTStr = "Post_d_"+BaseName;
  pltUnfPost_d = new CPlot(tmpTStr,"TSVDUnfold |di|","i","|d_{i}|");
  pltUnfPost_d->setOutDir(resultDir);
  pltUnfPost_d->AddHist1D(SVD_Post.dDist,"",kBlack,1,0,0,0);
  pltUnfPost_d->AddLine(0,1,13,1,kBlack,1);
  pltUnfPost_d->Draw(myCan,kTRUE,"png");
   
  //=================================================================
  //=================================================================
  // Unfolding from Post to Born          ===========================
  //=================================================================
  //=================================================================

  SVD_Born.data = (TH1D*)SVD_Post.EffCorr->Clone("BornData");
  SVD_Born.data->Sumw2();

  TSVDUnfold *svdBorn = new TSVDUnfold(
      SVD_Born.data, SVD_Born.bini, SVD_Born.xini,SVD_Born.Adet);
  SVD_Born.statCov = svdBorn->GetBCov();
  svdBorn->SetNormalize( kFALSE );
  SVD_Born.unfRes = svdBorn->Unfold(4);
  SVD_Born.dDist = svdBorn->GetD();
  SVD_Born.svDist = svdBorn->GetSV();
  SVD_Born.uStatCov = svdBorn->GetUnfoldCovMatrix( SVD_Born.statCov, 100);
  SVD_Born.uAdetCov = svdBorn->GetAdetCovMatrix( 100);
  SVD_Born.uStatCov->Add(SVD_Born.uAdetCov);

  SVD_Born.uTauCov = svdBorn->GetXtau();
  SVD_Born.uTauCov->Add( SVD_Born.uAdetCov);
  for( int i(1);i<=SVD_Born.unfRes->GetNbinsX(); i++)
  {
    SVD_Born.unfRes->SetBinError(i, TMath::Sqrt(SVD_Born.uTauCov->GetBinContent(i,i)));
  }

  SVD_Born.EffCorr = (TH1D*)SVD_Born.unfRes->Clone("BornEffCorr");
  SVD_Born.EffCorr->Sumw2();
  h1_Born_BothOvBorn_eqBin->Sumw2();
  SVD_Born.EffCorr->Divide(h1_Born_BothOvBorn_eqBin);

  tmpTStr = "Born_Unf_"+BaseName;
  pltUnfBorn = new CPlot(tmpTStr,"Post to Born Unfolding with SVD","W pT [GeV]","Event");
  pltUnfBorn->setOutDir(resultDir);
  pltUnfBorn->AddHist1D(SVD_Born.unfRes,"e",kBlue,1,0,20,2);
  pltUnfBorn->AddHist1D(SVD_Born.data,"e",kRed,1,0,24,2);
  pltUnfBorn->AddHist1D(SVD_Born.True,"hist",kBlack,1,0,0,0);
  pltUnfBorn->AddHist1D(SVD_Born.Gen,"hist",kGreen,1,0,0,0);
  pltUnfBorn->AddHist1D(SVD_Born.EffCorr,"elp",kGreen+2,0,0,26,2);
  pltUnfBorn->SetLegend(0.68,0.57,0.93,0.8);
  pltUnfBorn->GetLegend()->AddEntry(SVD_Born.unfRes,"Unfolded","p");
  pltUnfBorn->GetLegend()->AddEntry(SVD_Born.data,"Post","p");
  pltUnfBorn->GetLegend()->AddEntry(SVD_Born.True,"Born Target","l");
  pltUnfBorn->GetLegend()->AddEntry(SVD_Born.Gen,"Born Gen","l");
  pltUnfBorn->GetLegend()->AddEntry(SVD_Born.EffCorr,"EffCorr","l");
  pltUnfBorn->Draw(myCan,kTRUE,"png");

  tmpTStr = "Born_cov_"+BaseName;
  pltUnfBorn_cov = new CPlot(tmpTStr,"TSVDUnfold Covariance matrix","","");
  pltUnfBorn_cov->setOutDir(resultDir);
  pltUnfBorn_cov->AddHist2D(SVD_Post.uStatCov,"COLZ",kWhite,kBlack);
  pltUnfBorn_cov->Draw(myCan,kTRUE,"png");

  tmpTStr = "Born_d_"+BaseName;
  pltUnfBorn_d = new CPlot(tmpTStr,"TSVDUnfold |di|","i","|d_{i}|");
  pltUnfBorn_d->setOutDir(resultDir);
  pltUnfBorn_d->AddHist1D(SVD_Post.dDist,"",kBlack,1,0,0,0);
  pltUnfBorn_d->AddLine(0,1,13,1,kBlack,1);
  pltUnfBorn_d->Draw(myCan,kTRUE,"png");

  // Write to root file
  SVD_Post.data->Write();
  SVD_Born.EffCorr->Write();
  SVD_Born.Gen->Write();

  return 0;
}
