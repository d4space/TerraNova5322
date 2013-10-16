
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

int wPtUnfoldStudy_CovMatrix
(TString UnfoldFile,TString AcceptFile,TString DataFile, TString DataYieldFile, TString BaseName)
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
  TFile *f_DataYield   = new TFile(DataYieldFile);

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
    TH2D *BstatCov;
    TH2D *BstatCorr;
    
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
  
  double XMean[13]={0.0};
  double YMean[13];
  
  //double NumOfSamples=500.0;
  int NumOfSamples=500;
  
  //TH1D* h1_Data_Yield[500];
  TH1D* h1_Data_Yield[501];

  double Xcontent[13][500]={{0.0},{0.0}};
//  double Total[13][100]={{0.0},{0.0}};
  double Total[13][500]={0.0};
  double CovMult[13][500]={{1.0},{1.0}};

  double XMeanMinusXBinCont[500]={0.0};

  double XMeanMinusXBinContSum[169]={0.0};
  double XMeanMinusXBinContSumTwo[14][14];
  //TH1D* XMeanMinusXBinCont[100];
  TH1D* YMeanMinusYBinCont[500];



  TH1D* h1_SVD_Post_data[501];
  TH1D* h1_SVD_Born_EffCorr[501];
  TH1D* h1_SVD_Born_Gen[501];
  TH1D* h1_SVD_Post_True[501];
  TH1D* h1_SVD_Post_unfRes[501];
  TH1D* h1_SVD_Post_Gen[501];






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

  SVD_Post.BstatCov =
    new TH2D("SVD_Post.BstatCov","Covariance matrix",
  	NWptBinPlus-1,0,NWptBinPlus-1,NWptBinPlus-1,0,NWptBinPlus-1);
  //SVD_Post.BstatCov =
  //  new TH2D("SVD_Post.BstatCov","Covariance matrix",
  //	100,0,100,100,0,100);



  SVD_Post.BstatCorr =
    new TH2D("SVD_Post.BstatCorr","Corrlation matrix",
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
  CPlot *pltRecon_cov;
  CPlot *pltRecon_corr;
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




  for(int i(1); i<=NumOfSamples; i++)
  {
    if( BaseName == "WpToEleNu")
    {
      sprintf(tmpName,"hSigWPpt%d",i);
       h1_Data_Yield[i]	=(TH1D*)f_DataYield->Get(tmpName)->Clone(tmpName);
    }else if( BaseName == "WmToEleNu")
    {
      sprintf(tmpName,"hSigWMpt%d",i);
       h1_Data_Yield[i]	=(TH1D*)f_DataYield->Get(tmpName)->Clone(tmpName);
    
    }
  }



   for(int i(1);i<=h1_Data_Yield[1]->GetNbinsX();i++)
   {
     cout<<h1_Data_Yield[500]->GetBinContent(i)<<"\t"<<h1_Data_Yield[500]->GetBinError(i)<<endl;
   }


  
  ///// 500 loop for unfolding each of 500 samples
  // for(int k(1); k<=NumOfSamples; k++)
  // {

   
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
    /// 500 loop for 500 unfolding
    //SVD_Post.data->SetBinContent(i,h1_Data_Yield[k]->GetBinContent(i));
    //SVD_Post.data->  SetBinError(i,h1_Data_Yield[k]->GetBinError(i));

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
  
 



  for( int i(0); i< 13; i++)
  {
    for( int k(0); k<NumOfSamples; k++)
    {
      //Xcontent[i][k]=Xcontent[i][k] + h1_Data_Yield[k+1]->GetBinContent(i+1) ;

      Xcontent[i][k]= h1_Data_Yield[k+1]->GetBinContent(i+1) ;
      cout<<"Xcontent[i][k]:  "<<"  i =  "<<i<<" k =  "<<k<<"  "<<Xcontent[i][k]<<endl;

    }
  }
  cout<<"Xcontent[0][3]:  "<<Xcontent[0][3]<<endl;
  

  
  
  
  for( int i(0); i< 13; i++)
  {
    for( int k(0); k<NumOfSamples ; k++)
    {
      XMean[i]=XMean[i]+Xcontent[i][k]/NumOfSamples;
    }
  }
  
  
  
  for( int i(0); i< 13; i++)
  {
    cout<<"XMean[i]:  "<<i<<"  "<<XMean[i]<<endl;
  }

 



  
  for( int k(1); k<= NumOfSamples; k++)
  {


	cout<<"XMeanMinusXBin before    :  "<<"  i =0  "<<" k =  "<<k-1<<"  "<<XMeanMinusXBinContSum[0]<<endl;
	cout<<"<X0>-Xi0                 :  "<<"  i =0  "<<" k =  "<<k-1<<"  "<<(XMean[0]- Xcontent[0][k-1] )<<endl;
	cout<<"<X1>-Xi1                 :  "<<"  i =0  "<<" k =  "<<k-1<<"  "<<(XMean[0] - Xcontent[0][k-1])<<endl;
	cout<<"<Multiply                :  "<<"  i =0  "<<" k =  "<<k-1<<"  "<<(XMean[0]- Xcontent[0][k-1] )*( XMean[0] - Xcontent[0][k-1])/NumOfSamples<<endl;
	XMeanMinusXBinContSum[0]= XMeanMinusXBinContSum[0] + (XMean[0]- Xcontent[0][k-1] )*( XMean[0] - Xcontent[0][k-1])/NumOfSamples;
	cout<<"XMeanMinusXBinContSum[0] :  "<<"  i =0"<<"   k =  "<<k-1<<"  "<<XMeanMinusXBinContSum[0]<<endl;

//	cout<<"XMeanMinusXBin before    :  "<<"  i =1  "<<" k =  "<<k-1<<"  "<<XMeanMinusXBinContSum[1]<<endl;
//	cout<<"<X0>-Xi0                 :  "<<"  i =1  "<<" k =  "<<k-1<<"  "<<(XMean[0]- Xcontent[0][k-1] )<<endl;
//	cout<<"<X1>-Xi1                 :  "<<"  i =1  "<<" k =  "<<k-1<<"  "<<(XMean[1] - Xcontent[1][k-1])<<endl;
//	cout<<"<Multiply                :  "<<"  i =1  "<<" k =  "<<k-1<<"  "<<(XMean[0]- Xcontent[0][k-1] )*( XMean[1] - Xcontent[1][k-1])<<endl;
	XMeanMinusXBinContSum[1]= XMeanMinusXBinContSum[1] + (XMean[0]- Xcontent[0][k-1] )*( XMean[1] - Xcontent[1][k-1])/NumOfSamples;
//	cout<<"XMeanMinusXBinContSum[1] :  "<<"  i =1"<<"   k =  "<<k-1<<"  "<<XMeanMinusXBinContSum[1]<<endl;

	XMeanMinusXBinContSum[2]= XMeanMinusXBinContSum[2] + (XMean[0]- Xcontent[0][k-1] )*( XMean[2] - Xcontent[2][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[3]= XMeanMinusXBinContSum[3] + (XMean[0]- Xcontent[0][k-1] )*( XMean[3] - Xcontent[3][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[4]= XMeanMinusXBinContSum[4] + (XMean[0]- Xcontent[0][k-1] )*( XMean[4] - Xcontent[4][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[5]= XMeanMinusXBinContSum[5] + (XMean[0]- Xcontent[0][k-1] )*( XMean[5] - Xcontent[5][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[6]= XMeanMinusXBinContSum[6] + (XMean[0]- Xcontent[0][k-1] )*( XMean[6] - Xcontent[6][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[7]= XMeanMinusXBinContSum[7] + (XMean[0]- Xcontent[0][k-1] )*( XMean[7] - Xcontent[7][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[8]= XMeanMinusXBinContSum[8] + (XMean[0]- Xcontent[0][k-1] )*( XMean[8] - Xcontent[8][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[9]= XMeanMinusXBinContSum[9] + (XMean[0]- Xcontent[0][k-1] )*( XMean[9] - Xcontent[9][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[10]= XMeanMinusXBinContSum[10] + (XMean[0]- Xcontent[0][k-1] )*( XMean[10] - Xcontent[10][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[11]= XMeanMinusXBinContSum[11] + (XMean[0]- Xcontent[0][k-1] )*( XMean[11] - Xcontent[11][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[12]= XMeanMinusXBinContSum[12] + (XMean[0]- Xcontent[0][k-1] )*( XMean[12] - Xcontent[12][k-1])/NumOfSamples;

	XMeanMinusXBinContSum[13]= XMeanMinusXBinContSum[13] + (XMean[1]- Xcontent[1][k-1] )*( XMean[0] - Xcontent[0][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[14]= XMeanMinusXBinContSum[14] + (XMean[1]- Xcontent[1][k-1] )*( XMean[1] - Xcontent[1][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[15]= XMeanMinusXBinContSum[15] + (XMean[1]- Xcontent[1][k-1] )*( XMean[2] - Xcontent[2][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[16]= XMeanMinusXBinContSum[16] + (XMean[1]- Xcontent[1][k-1] )*( XMean[3] - Xcontent[3][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[17]= XMeanMinusXBinContSum[17] + (XMean[1]- Xcontent[1][k-1] )*( XMean[4] - Xcontent[4][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[18]= XMeanMinusXBinContSum[18] + (XMean[1]- Xcontent[1][k-1] )*( XMean[5] - Xcontent[5][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[19]= XMeanMinusXBinContSum[19] + (XMean[1]- Xcontent[1][k-1] )*( XMean[6] - Xcontent[6][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[20]= XMeanMinusXBinContSum[20] + (XMean[1]- Xcontent[1][k-1] )*( XMean[7] - Xcontent[7][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[21]= XMeanMinusXBinContSum[21] + (XMean[1]- Xcontent[1][k-1] )*( XMean[8] - Xcontent[8][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[22]= XMeanMinusXBinContSum[22] + (XMean[1]- Xcontent[1][k-1] )*( XMean[9] - Xcontent[9][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[23]= XMeanMinusXBinContSum[23] + (XMean[1]- Xcontent[1][k-1] )*( XMean[10] - Xcontent[10][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[24]= XMeanMinusXBinContSum[24] + (XMean[1]- Xcontent[1][k-1] )*( XMean[11] - Xcontent[11][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[25]= XMeanMinusXBinContSum[25] + (XMean[1]- Xcontent[1][k-1] )*( XMean[12] - Xcontent[12][k-1])/NumOfSamples;

	XMeanMinusXBinContSum[26]= XMeanMinusXBinContSum[26] + (XMean[2]- Xcontent[2][k-1] )*( XMean[0] - Xcontent[0][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[27]= XMeanMinusXBinContSum[27] + (XMean[2]- Xcontent[2][k-1] )*( XMean[1] - Xcontent[1][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[28]= XMeanMinusXBinContSum[28] + (XMean[2]- Xcontent[2][k-1] )*( XMean[2] - Xcontent[2][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[29]= XMeanMinusXBinContSum[29] + (XMean[2]- Xcontent[2][k-1] )*( XMean[3] - Xcontent[3][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[30]= XMeanMinusXBinContSum[30] + (XMean[2]- Xcontent[2][k-1] )*( XMean[4] - Xcontent[4][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[31]= XMeanMinusXBinContSum[31] + (XMean[2]- Xcontent[2][k-1] )*( XMean[5] - Xcontent[5][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[32]= XMeanMinusXBinContSum[32] + (XMean[2]- Xcontent[2][k-1] )*( XMean[6] - Xcontent[6][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[33]= XMeanMinusXBinContSum[33] + (XMean[2]- Xcontent[2][k-1] )*( XMean[7] - Xcontent[7][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[34]= XMeanMinusXBinContSum[34] + (XMean[2]- Xcontent[2][k-1] )*( XMean[8] - Xcontent[8][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[35]= XMeanMinusXBinContSum[35] + (XMean[2]- Xcontent[2][k-1] )*( XMean[9] - Xcontent[9][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[36]= XMeanMinusXBinContSum[36] + (XMean[2]- Xcontent[2][k-1] )*( XMean[10] - Xcontent[10][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[37]= XMeanMinusXBinContSum[37] + (XMean[2]- Xcontent[2][k-1] )*( XMean[11] - Xcontent[11][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[38]= XMeanMinusXBinContSum[38] + (XMean[2]- Xcontent[2][k-1] )*( XMean[12] - Xcontent[12][k-1])/NumOfSamples;

	XMeanMinusXBinContSum[39]= XMeanMinusXBinContSum[39] + (XMean[3]- Xcontent[3][k-1] )*( XMean[0] - Xcontent[0][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[40]= XMeanMinusXBinContSum[40] + (XMean[3]- Xcontent[3][k-1] )*( XMean[1] - Xcontent[1][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[41]= XMeanMinusXBinContSum[41] + (XMean[3]- Xcontent[3][k-1] )*( XMean[2] - Xcontent[2][k-1])/NumOfSamples;
	
//	cout<<"XMeanMinusXBin before    :  "<<"  i =3  "<<" k =  "<<k-1<<"  "<<XMeanMinusXBinContSum[42]<<endl;
//	cout<<"<X0>-Xi0                 :  "<<"  i =3  "<<" k =  "<<k-1<<"  "<<(XMean[3]- Xcontent[3][k-1] )<<endl;
//	cout<<"<X1>-Xi1                 :  "<<"  i =3  "<<" k =  "<<k-1<<"  "<<(XMean[3]- Xcontent[3][k-1])<<endl;
//	cout<<"<Multiply                :  "<<"  i =3  "<<" k =  "<<k-1<<"  "<<(XMean[3]- Xcontent[3][k-1] )*( XMean[3] - Xcontent[3][k-1])<<endl;
	XMeanMinusXBinContSum[42]= XMeanMinusXBinContSum[42] + (XMean[3]- Xcontent[3][k-1] )*( XMean[3] - Xcontent[3][k-1])/NumOfSamples;
//	cout<<"XMeanMinusXBinContSum[42] :  "<<"  i =3"<<"   k =  "<<k-1<<"  "<<XMeanMinusXBinContSum[42]<<endl;
	
	XMeanMinusXBinContSum[43]= XMeanMinusXBinContSum[43] + (XMean[3]- Xcontent[3][k-1] )*( XMean[4] - Xcontent[4][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[44]= XMeanMinusXBinContSum[44] + (XMean[3]- Xcontent[3][k-1] )*( XMean[5] - Xcontent[5][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[45]= XMeanMinusXBinContSum[45] + (XMean[3]- Xcontent[3][k-1] )*( XMean[6] - Xcontent[6][k-1])/NumOfSamples;

//	cout<<"XMeanMinusXBin before    :  "<<"  i =3  "<<" k =  "<<k-1<<"  "<<XMeanMinusXBinContSum[46]<<endl;
//	cout<<"<X0>-Xi0                 :  "<<"  i =3  "<<" k =  "<<k-1<<"  "<<(XMean[3]- Xcontent[3][k-1] )<<endl;
//	cout<<"<X1>-Xi1                 :  "<<"  i =3  "<<" k =  "<<k-1<<"  "<<(XMean[7]- Xcontent[7][k-1])<<endl;
//	cout<<"<Multiply                :  "<<"  i =3  "<<" k =  "<<k-1<<"  "<<(XMean[3]- Xcontent[3][k-1] )*( XMean[7] - Xcontent[7][k-1])<<endl;
	XMeanMinusXBinContSum[46]= XMeanMinusXBinContSum[46] + (XMean[3]- Xcontent[3][k-1] )*( XMean[7] - Xcontent[7][k-1])/NumOfSamples;
//	cout<<"XMeanMinusXBinContSum[46] :  "<<"  i =3"<<"   k =  "<<k-1<<"  "<<XMeanMinusXBinContSum[46]<<endl;
	
	XMeanMinusXBinContSum[47]= XMeanMinusXBinContSum[47] + (XMean[3]- Xcontent[3][k-1] )*( XMean[8] - Xcontent[8][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[48]= XMeanMinusXBinContSum[48] + (XMean[3]- Xcontent[3][k-1] )*( XMean[9] - Xcontent[9][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[49]= XMeanMinusXBinContSum[49] + (XMean[3]- Xcontent[3][k-1] )*( XMean[10] - Xcontent[10][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[50]= XMeanMinusXBinContSum[50] + (XMean[3]- Xcontent[3][k-1] )*( XMean[11] - Xcontent[11][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[51]= XMeanMinusXBinContSum[51] + (XMean[3]- Xcontent[3][k-1] )*( XMean[12] - Xcontent[12][k-1])/NumOfSamples;

	XMeanMinusXBinContSum[52]= XMeanMinusXBinContSum[52] + (XMean[4]- Xcontent[4][k-1] )*( XMean[0] - Xcontent[0][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[53]= XMeanMinusXBinContSum[53] + (XMean[4]- Xcontent[4][k-1] )*( XMean[1] - Xcontent[1][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[54]= XMeanMinusXBinContSum[54] + (XMean[4]- Xcontent[4][k-1] )*( XMean[2] - Xcontent[2][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[55]= XMeanMinusXBinContSum[55] + (XMean[4]- Xcontent[4][k-1] )*( XMean[3] - Xcontent[3][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[56]= XMeanMinusXBinContSum[56] + (XMean[4]- Xcontent[4][k-1] )*( XMean[4] - Xcontent[4][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[57]= XMeanMinusXBinContSum[57] + (XMean[4]- Xcontent[4][k-1] )*( XMean[5] - Xcontent[5][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[58]= XMeanMinusXBinContSum[58] + (XMean[4]- Xcontent[4][k-1] )*( XMean[6] - Xcontent[6][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[59]= XMeanMinusXBinContSum[59] + (XMean[4]- Xcontent[4][k-1] )*( XMean[7] - Xcontent[7][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[60]= XMeanMinusXBinContSum[60] + (XMean[4]- Xcontent[4][k-1] )*( XMean[8] - Xcontent[8][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[61]= XMeanMinusXBinContSum[61] + (XMean[4]- Xcontent[4][k-1] )*( XMean[9] - Xcontent[9][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[62]= XMeanMinusXBinContSum[62] + (XMean[4]- Xcontent[4][k-1] )*( XMean[10] - Xcontent[10][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[63]= XMeanMinusXBinContSum[63] + (XMean[4]- Xcontent[4][k-1] )*( XMean[11] - Xcontent[11][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[64]= XMeanMinusXBinContSum[64] + (XMean[4]- Xcontent[4][k-1] )*( XMean[12] - Xcontent[12][k-1])/NumOfSamples;

	XMeanMinusXBinContSum[65]= XMeanMinusXBinContSum[65] + (XMean[5]- Xcontent[5][k-1] )*( XMean[0] - Xcontent[0][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[66]= XMeanMinusXBinContSum[66] + (XMean[5]- Xcontent[5][k-1] )*( XMean[1] - Xcontent[1][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[67]= XMeanMinusXBinContSum[67] + (XMean[5]- Xcontent[5][k-1] )*( XMean[2] - Xcontent[2][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[68]= XMeanMinusXBinContSum[68] + (XMean[5]- Xcontent[5][k-1] )*( XMean[3] - Xcontent[3][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[69]= XMeanMinusXBinContSum[69] + (XMean[5]- Xcontent[5][k-1] )*( XMean[4] - Xcontent[4][k-1])/NumOfSamples;
	
//	cout<<"XMeanMinusXBin before    :  "<<"  i =5  "<<" k =  "<<k-1<<"  "<<XMeanMinusXBinContSum[70]<<endl;
//	cout<<"<X0>-Xi0                 :  "<<"  i =5  "<<" k =  "<<k-1<<"  "<<(XMean[5]- Xcontent[5][k-1] )<<endl;
//	cout<<"<X1>-Xi1                 :  "<<"  i =5  "<<" k =  "<<k-1<<"  "<<(XMean[5]- Xcontent[5][k-1])<<endl;
//	cout<<"<Multiply                :  "<<"  i =5  "<<" k =  "<<k-1<<"  "<<(XMean[5]- Xcontent[5][k-1] )*( XMean[5] - Xcontent[5][k-1])<<endl;
	XMeanMinusXBinContSum[70]= XMeanMinusXBinContSum[70] + (XMean[5]- Xcontent[5][k-1] )*( XMean[5] - Xcontent[5][k-1])/NumOfSamples;
//	cout<<"XMeanMinusXBinContSum[70] :  "<<"  i =5"<<"   k =  "<<k-1<<"  "<<XMeanMinusXBinContSum[70]<<endl;
	
	XMeanMinusXBinContSum[71]= XMeanMinusXBinContSum[71] + (XMean[5]- Xcontent[5][k-1] )*( XMean[6] - Xcontent[6][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[72]= XMeanMinusXBinContSum[72] + (XMean[5]- Xcontent[5][k-1] )*( XMean[7] - Xcontent[7][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[73]= XMeanMinusXBinContSum[73] + (XMean[5]- Xcontent[5][k-1] )*( XMean[8] - Xcontent[8][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[74]= XMeanMinusXBinContSum[74] + (XMean[5]- Xcontent[5][k-1] )*( XMean[9] - Xcontent[9][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[75]= XMeanMinusXBinContSum[75] + (XMean[5]- Xcontent[5][k-1] )*( XMean[10] - Xcontent[10][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[76]= XMeanMinusXBinContSum[76] + (XMean[5]- Xcontent[5][k-1] )*( XMean[11] - Xcontent[11][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[77]= XMeanMinusXBinContSum[77] + (XMean[5]- Xcontent[5][k-1] )*( XMean[12] - Xcontent[12][k-1])/NumOfSamples;

	XMeanMinusXBinContSum[78]= XMeanMinusXBinContSum[78] + (XMean[6]- Xcontent[6][k-1] )*( XMean[0] - Xcontent[0][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[79]= XMeanMinusXBinContSum[79] + (XMean[6]- Xcontent[6][k-1] )*( XMean[1] - Xcontent[1][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[80]= XMeanMinusXBinContSum[80] + (XMean[6]- Xcontent[6][k-1] )*( XMean[2] - Xcontent[2][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[81]= XMeanMinusXBinContSum[81] + (XMean[6]- Xcontent[6][k-1] )*( XMean[3] - Xcontent[3][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[82]= XMeanMinusXBinContSum[82] + (XMean[6]- Xcontent[6][k-1] )*( XMean[4] - Xcontent[4][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[83]= XMeanMinusXBinContSum[83] + (XMean[6]- Xcontent[6][k-1] )*( XMean[5] - Xcontent[5][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[84]= XMeanMinusXBinContSum[84] + (XMean[6]- Xcontent[6][k-1] )*( XMean[6] - Xcontent[6][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[85]= XMeanMinusXBinContSum[85] + (XMean[6]- Xcontent[6][k-1] )*( XMean[7] - Xcontent[7][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[86]= XMeanMinusXBinContSum[86] + (XMean[6]- Xcontent[6][k-1] )*( XMean[8] - Xcontent[8][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[87]= XMeanMinusXBinContSum[87] + (XMean[6]- Xcontent[6][k-1] )*( XMean[9] - Xcontent[9][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[88]= XMeanMinusXBinContSum[88] + (XMean[6]- Xcontent[6][k-1] )*( XMean[10] - Xcontent[10][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[89]= XMeanMinusXBinContSum[89] + (XMean[6]- Xcontent[6][k-1] )*( XMean[11] - Xcontent[11][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[90]= XMeanMinusXBinContSum[90] + (XMean[6]- Xcontent[6][k-1] )*( XMean[12] - Xcontent[12][k-1])/NumOfSamples;

	XMeanMinusXBinContSum[91]= XMeanMinusXBinContSum[91] + (XMean[7]- Xcontent[7][k-1] )*( XMean[0] - Xcontent[0][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[92]= XMeanMinusXBinContSum[92] + (XMean[7]- Xcontent[7][k-1] )*( XMean[1] - Xcontent[1][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[93]= XMeanMinusXBinContSum[93] + (XMean[7]- Xcontent[7][k-1] )*( XMean[2] - Xcontent[2][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[94]= XMeanMinusXBinContSum[94] + (XMean[7]- Xcontent[7][k-1] )*( XMean[3] - Xcontent[3][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[95]= XMeanMinusXBinContSum[95] + (XMean[7]- Xcontent[7][k-1] )*( XMean[4] - Xcontent[4][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[96]= XMeanMinusXBinContSum[96] + (XMean[7]- Xcontent[7][k-1] )*( XMean[5] - Xcontent[5][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[97]= XMeanMinusXBinContSum[97] + (XMean[7]- Xcontent[7][k-1] )*( XMean[6] - Xcontent[6][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[98]= XMeanMinusXBinContSum[98] + (XMean[7]- Xcontent[7][k-1] )*( XMean[7] - Xcontent[7][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[99]= XMeanMinusXBinContSum[99] + (XMean[7]- Xcontent[7][k-1] )*( XMean[8] - Xcontent[8][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[100]= XMeanMinusXBinContSum[100] + (XMean[7]- Xcontent[7][k-1] )*( XMean[9] - Xcontent[9][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[101]= XMeanMinusXBinContSum[101] + (XMean[7]- Xcontent[7][k-1] )*( XMean[10] - Xcontent[10][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[102]= XMeanMinusXBinContSum[102] + (XMean[7]- Xcontent[7][k-1] )*( XMean[11] - Xcontent[11][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[103]= XMeanMinusXBinContSum[103] + (XMean[7]- Xcontent[7][k-1] )*( XMean[12] - Xcontent[12][k-1])/NumOfSamples;

	XMeanMinusXBinContSum[104]= XMeanMinusXBinContSum[104] + (XMean[8]- Xcontent[8][k-1] )*( XMean[0] - Xcontent[0][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[105]= XMeanMinusXBinContSum[105] + (XMean[8]- Xcontent[8][k-1] )*( XMean[1] - Xcontent[1][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[106]= XMeanMinusXBinContSum[106] + (XMean[8]- Xcontent[8][k-1] )*( XMean[2] - Xcontent[2][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[107]= XMeanMinusXBinContSum[107] + (XMean[8]- Xcontent[8][k-1] )*( XMean[3] - Xcontent[3][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[108]= XMeanMinusXBinContSum[108] + (XMean[8]- Xcontent[8][k-1] )*( XMean[4] - Xcontent[4][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[109]= XMeanMinusXBinContSum[109] + (XMean[8]- Xcontent[8][k-1] )*( XMean[5] - Xcontent[5][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[110]= XMeanMinusXBinContSum[110] + (XMean[8]- Xcontent[8][k-1] )*( XMean[6] - Xcontent[6][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[111]= XMeanMinusXBinContSum[111] + (XMean[8]- Xcontent[8][k-1] )*( XMean[7] - Xcontent[7][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[112]= XMeanMinusXBinContSum[112] + (XMean[8]- Xcontent[8][k-1] )*( XMean[8] - Xcontent[8][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[113]= XMeanMinusXBinContSum[113] + (XMean[8]- Xcontent[8][k-1] )*( XMean[9] - Xcontent[9][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[114]= XMeanMinusXBinContSum[114] + (XMean[8]- Xcontent[8][k-1] )*( XMean[10] - Xcontent[10][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[115]= XMeanMinusXBinContSum[115] + (XMean[8]- Xcontent[8][k-1] )*( XMean[11] - Xcontent[11][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[116]= XMeanMinusXBinContSum[116] + (XMean[8]- Xcontent[8][k-1] )*( XMean[12] - Xcontent[12][k-1])/NumOfSamples;

	XMeanMinusXBinContSum[117]= XMeanMinusXBinContSum[117] + (XMean[9]- Xcontent[9][k-1] )*( XMean[0] - Xcontent[0][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[118]= XMeanMinusXBinContSum[118] + (XMean[9]- Xcontent[9][k-1] )*( XMean[1] - Xcontent[1][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[119]= XMeanMinusXBinContSum[119] + (XMean[9]- Xcontent[9][k-1] )*( XMean[2] - Xcontent[2][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[120]= XMeanMinusXBinContSum[120] + (XMean[9]- Xcontent[9][k-1] )*( XMean[3] - Xcontent[3][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[121]= XMeanMinusXBinContSum[121] + (XMean[9]- Xcontent[9][k-1] )*( XMean[4] - Xcontent[4][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[122]= XMeanMinusXBinContSum[122] + (XMean[9]- Xcontent[9][k-1] )*( XMean[5] - Xcontent[5][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[123]= XMeanMinusXBinContSum[123] + (XMean[9]- Xcontent[9][k-1] )*( XMean[6] - Xcontent[6][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[124]= XMeanMinusXBinContSum[124] + (XMean[9]- Xcontent[9][k-1] )*( XMean[7] - Xcontent[7][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[125]= XMeanMinusXBinContSum[125] + (XMean[9]- Xcontent[9][k-1] )*( XMean[8] - Xcontent[8][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[126]= XMeanMinusXBinContSum[126] + (XMean[9]- Xcontent[9][k-1] )*( XMean[9] - Xcontent[9][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[127]= XMeanMinusXBinContSum[127] + (XMean[9]- Xcontent[9][k-1] )*( XMean[10] - Xcontent[10][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[128]= XMeanMinusXBinContSum[128] + (XMean[9]- Xcontent[9][k-1] )*( XMean[11] - Xcontent[11][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[129]= XMeanMinusXBinContSum[129] + (XMean[9]- Xcontent[9][k-1] )*( XMean[12] - Xcontent[12][k-1])/NumOfSamples;

	XMeanMinusXBinContSum[130]= XMeanMinusXBinContSum[130] + (XMean[10]- Xcontent[10][k-1] )*( XMean[0] - Xcontent[0][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[131]= XMeanMinusXBinContSum[131] + (XMean[10]- Xcontent[10][k-1] )*( XMean[1] - Xcontent[1][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[132]= XMeanMinusXBinContSum[132] + (XMean[10]- Xcontent[10][k-1] )*( XMean[2] - Xcontent[2][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[133]= XMeanMinusXBinContSum[133] + (XMean[10]- Xcontent[10][k-1] )*( XMean[3] - Xcontent[3][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[134]= XMeanMinusXBinContSum[134] + (XMean[10]- Xcontent[10][k-1] )*( XMean[4] - Xcontent[4][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[135]= XMeanMinusXBinContSum[135] + (XMean[10]- Xcontent[10][k-1] )*( XMean[5] - Xcontent[5][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[136]= XMeanMinusXBinContSum[136] + (XMean[10]- Xcontent[10][k-1] )*( XMean[6] - Xcontent[6][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[137]= XMeanMinusXBinContSum[137] + (XMean[10]- Xcontent[10][k-1] )*( XMean[7] - Xcontent[7][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[138]= XMeanMinusXBinContSum[138] + (XMean[10]- Xcontent[10][k-1] )*( XMean[8] - Xcontent[8][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[139]= XMeanMinusXBinContSum[139] + (XMean[10]- Xcontent[10][k-1] )*( XMean[9] - Xcontent[9][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[140]= XMeanMinusXBinContSum[140] + (XMean[10]- Xcontent[10][k-1] )*( XMean[10] - Xcontent[10][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[141]= XMeanMinusXBinContSum[141] + (XMean[10]- Xcontent[10][k-1] )*( XMean[11] - Xcontent[11][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[142]= XMeanMinusXBinContSum[142] + (XMean[10]- Xcontent[10][k-1] )*( XMean[12] - Xcontent[12][k-1])/NumOfSamples;

	XMeanMinusXBinContSum[143]= XMeanMinusXBinContSum[143] + (XMean[11]- Xcontent[11][k-1] )*( XMean[0] - Xcontent[0][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[144]= XMeanMinusXBinContSum[144] + (XMean[11]- Xcontent[11][k-1] )*( XMean[1] - Xcontent[1][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[145]= XMeanMinusXBinContSum[145] + (XMean[11]- Xcontent[11][k-1] )*( XMean[2] - Xcontent[2][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[146]= XMeanMinusXBinContSum[146] + (XMean[11]- Xcontent[11][k-1] )*( XMean[3] - Xcontent[3][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[147]= XMeanMinusXBinContSum[147] + (XMean[11]- Xcontent[11][k-1] )*( XMean[4] - Xcontent[4][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[148]= XMeanMinusXBinContSum[148] + (XMean[11]- Xcontent[11][k-1] )*( XMean[5] - Xcontent[5][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[149]= XMeanMinusXBinContSum[149] + (XMean[11]- Xcontent[11][k-1] )*( XMean[6] - Xcontent[6][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[150]= XMeanMinusXBinContSum[150] + (XMean[11]- Xcontent[11][k-1] )*( XMean[7] - Xcontent[7][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[151]= XMeanMinusXBinContSum[151] + (XMean[11]- Xcontent[11][k-1] )*( XMean[8] - Xcontent[8][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[152]= XMeanMinusXBinContSum[152] + (XMean[11]- Xcontent[11][k-1] )*( XMean[9] - Xcontent[9][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[153]= XMeanMinusXBinContSum[153] + (XMean[11]- Xcontent[11][k-1] )*( XMean[10] - Xcontent[10][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[154]= XMeanMinusXBinContSum[154] + (XMean[11]- Xcontent[11][k-1] )*( XMean[11] - Xcontent[11][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[155]= XMeanMinusXBinContSum[155] + (XMean[11]- Xcontent[11][k-1] )*( XMean[12] - Xcontent[12][k-1])/NumOfSamples;

	XMeanMinusXBinContSum[156]= XMeanMinusXBinContSum[156] + (XMean[12]- Xcontent[12][k-1] )*( XMean[0] - Xcontent[0][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[157]= XMeanMinusXBinContSum[157] + (XMean[12]- Xcontent[12][k-1] )*( XMean[1] - Xcontent[1][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[158]= XMeanMinusXBinContSum[158] + (XMean[12]- Xcontent[12][k-1] )*( XMean[2] - Xcontent[2][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[159]= XMeanMinusXBinContSum[159] + (XMean[12]- Xcontent[12][k-1] )*( XMean[3] - Xcontent[3][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[160]= XMeanMinusXBinContSum[160] + (XMean[12]- Xcontent[12][k-1] )*( XMean[4] - Xcontent[4][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[161]= XMeanMinusXBinContSum[161] + (XMean[12]- Xcontent[12][k-1] )*( XMean[5] - Xcontent[5][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[162]= XMeanMinusXBinContSum[162] + (XMean[12]- Xcontent[12][k-1] )*( XMean[6] - Xcontent[6][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[163]= XMeanMinusXBinContSum[163] + (XMean[12]- Xcontent[12][k-1] )*( XMean[7] - Xcontent[7][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[164]= XMeanMinusXBinContSum[164] + (XMean[12]- Xcontent[12][k-1] )*( XMean[8] - Xcontent[8][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[165]= XMeanMinusXBinContSum[165] + (XMean[12]- Xcontent[12][k-1] )*( XMean[9] - Xcontent[9][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[166]= XMeanMinusXBinContSum[166] + (XMean[12]- Xcontent[12][k-1] )*( XMean[10] - Xcontent[10][k-1])/NumOfSamples;
	XMeanMinusXBinContSum[167]= XMeanMinusXBinContSum[167] + (XMean[12]- Xcontent[12][k-1] )*( XMean[11] - Xcontent[11][k-1])/NumOfSamples;
	
	XMeanMinusXBinContSum[168]= XMeanMinusXBinContSum[168] + (XMean[12]- Xcontent[12][k-1] )*( XMean[12] - Xcontent[12][k-1])/NumOfSamples;
	//cout<<"XMeanMinusXBinContSum[168] :  "<<"  i =168"<<"   k =  "<<k-1<<"  "<<XMeanMinusXBinContSum[168]<<endl;

	
  }


	 XMeanMinusXBinContSumTwo[1][1]= XMeanMinusXBinContSum[0];
	  cout<<"XMeanMinusXBinContSumTwo[1][1]"<<XMeanMinusXBinContSumTwo[1][1]<<endl;
	 XMeanMinusXBinContSumTwo[1][2]= XMeanMinusXBinContSum[1];
	  cout<<"XMeanMinusXBinContSumTwo[1][2]"<<XMeanMinusXBinContSumTwo[1][2]<<endl;
	 XMeanMinusXBinContSumTwo[1][3]= XMeanMinusXBinContSum[2];
	 XMeanMinusXBinContSumTwo[1][4]= XMeanMinusXBinContSum[3];
	 XMeanMinusXBinContSumTwo[1][5]= XMeanMinusXBinContSum[4];
	 XMeanMinusXBinContSumTwo[1][6]= XMeanMinusXBinContSum[5];
	 XMeanMinusXBinContSumTwo[1][7]= XMeanMinusXBinContSum[6];
	 XMeanMinusXBinContSumTwo[1][8]= XMeanMinusXBinContSum[7];
	 XMeanMinusXBinContSumTwo[1][9]= XMeanMinusXBinContSum[8];
	 XMeanMinusXBinContSumTwo[1][10]= XMeanMinusXBinContSum[9];
	 XMeanMinusXBinContSumTwo[1][11]= XMeanMinusXBinContSum[10];
	 XMeanMinusXBinContSumTwo[1][12]= XMeanMinusXBinContSum[11];
	 XMeanMinusXBinContSumTwo[1][13]= XMeanMinusXBinContSum[12];

	 XMeanMinusXBinContSumTwo[2][1]= XMeanMinusXBinContSum[13];
	 XMeanMinusXBinContSumTwo[2][2]= XMeanMinusXBinContSum[14];
	 XMeanMinusXBinContSumTwo[2][3]= XMeanMinusXBinContSum[15];
	 XMeanMinusXBinContSumTwo[2][4]= XMeanMinusXBinContSum[16];
	 XMeanMinusXBinContSumTwo[2][5]= XMeanMinusXBinContSum[17];
	 XMeanMinusXBinContSumTwo[2][6]= XMeanMinusXBinContSum[18];
	 XMeanMinusXBinContSumTwo[2][7]= XMeanMinusXBinContSum[19];
	 XMeanMinusXBinContSumTwo[2][8]= XMeanMinusXBinContSum[20];
	 XMeanMinusXBinContSumTwo[2][9]= XMeanMinusXBinContSum[21];
	 XMeanMinusXBinContSumTwo[2][10]= XMeanMinusXBinContSum[22];
	 XMeanMinusXBinContSumTwo[2][11]= XMeanMinusXBinContSum[23];
	 XMeanMinusXBinContSumTwo[2][12]= XMeanMinusXBinContSum[24];
	 XMeanMinusXBinContSumTwo[2][13]= XMeanMinusXBinContSum[25];

	 XMeanMinusXBinContSumTwo[3][1]= XMeanMinusXBinContSum[26];
	 XMeanMinusXBinContSumTwo[3][2]= XMeanMinusXBinContSum[27];
	 XMeanMinusXBinContSumTwo[3][3]= XMeanMinusXBinContSum[28];
	 XMeanMinusXBinContSumTwo[3][4]= XMeanMinusXBinContSum[29];
	 XMeanMinusXBinContSumTwo[3][5]= XMeanMinusXBinContSum[30];
	 XMeanMinusXBinContSumTwo[3][6]= XMeanMinusXBinContSum[31];
	 XMeanMinusXBinContSumTwo[3][7]= XMeanMinusXBinContSum[32];
	 XMeanMinusXBinContSumTwo[3][8]= XMeanMinusXBinContSum[33];
	 XMeanMinusXBinContSumTwo[3][9]= XMeanMinusXBinContSum[34];
	 XMeanMinusXBinContSumTwo[3][10]= XMeanMinusXBinContSum[35];
	 XMeanMinusXBinContSumTwo[3][11]= XMeanMinusXBinContSum[36];
	 XMeanMinusXBinContSumTwo[3][12]= XMeanMinusXBinContSum[37];
	 XMeanMinusXBinContSumTwo[3][13]= XMeanMinusXBinContSum[38];

	 XMeanMinusXBinContSumTwo[4][1]= XMeanMinusXBinContSum[39];
	 XMeanMinusXBinContSumTwo[4][2]= XMeanMinusXBinContSum[40];
	 XMeanMinusXBinContSumTwo[4][3]= XMeanMinusXBinContSum[41];
	 XMeanMinusXBinContSumTwo[4][4]= XMeanMinusXBinContSum[42];
	 XMeanMinusXBinContSumTwo[4][5]= XMeanMinusXBinContSum[43];
	 XMeanMinusXBinContSumTwo[4][6]= XMeanMinusXBinContSum[44];
	 XMeanMinusXBinContSumTwo[4][7]= XMeanMinusXBinContSum[45];
	 XMeanMinusXBinContSumTwo[4][8]= XMeanMinusXBinContSum[46];
	 XMeanMinusXBinContSumTwo[4][9]= XMeanMinusXBinContSum[47];
	 XMeanMinusXBinContSumTwo[4][10]= XMeanMinusXBinContSum[48];
	 XMeanMinusXBinContSumTwo[4][11]= XMeanMinusXBinContSum[49];
	 XMeanMinusXBinContSumTwo[4][12]= XMeanMinusXBinContSum[50];
	 XMeanMinusXBinContSumTwo[4][13]= XMeanMinusXBinContSum[51];

	 XMeanMinusXBinContSumTwo[5][1]= XMeanMinusXBinContSum[52];
	 XMeanMinusXBinContSumTwo[5][2]= XMeanMinusXBinContSum[53];
	 XMeanMinusXBinContSumTwo[5][3]= XMeanMinusXBinContSum[54];
	 XMeanMinusXBinContSumTwo[5][4]= XMeanMinusXBinContSum[55];
	 XMeanMinusXBinContSumTwo[5][5]= XMeanMinusXBinContSum[56];
	 XMeanMinusXBinContSumTwo[5][6]= XMeanMinusXBinContSum[57];
	 XMeanMinusXBinContSumTwo[5][7]= XMeanMinusXBinContSum[58];
	 XMeanMinusXBinContSumTwo[5][8]= XMeanMinusXBinContSum[59];
	 XMeanMinusXBinContSumTwo[5][9]= XMeanMinusXBinContSum[60];
	 XMeanMinusXBinContSumTwo[5][10]= XMeanMinusXBinContSum[61];
	 XMeanMinusXBinContSumTwo[5][11]= XMeanMinusXBinContSum[62];
	 XMeanMinusXBinContSumTwo[5][12]= XMeanMinusXBinContSum[63];
	 XMeanMinusXBinContSumTwo[5][13]= XMeanMinusXBinContSum[64];

	 XMeanMinusXBinContSumTwo[6][1]= XMeanMinusXBinContSum[65];
	 XMeanMinusXBinContSumTwo[6][2]= XMeanMinusXBinContSum[66];
	 XMeanMinusXBinContSumTwo[6][3]= XMeanMinusXBinContSum[67];
	 XMeanMinusXBinContSumTwo[6][4]= XMeanMinusXBinContSum[68];
	 XMeanMinusXBinContSumTwo[6][5]= XMeanMinusXBinContSum[69];
	 XMeanMinusXBinContSumTwo[6][6]= XMeanMinusXBinContSum[70];
	 XMeanMinusXBinContSumTwo[6][7]= XMeanMinusXBinContSum[71];
	 XMeanMinusXBinContSumTwo[6][8]= XMeanMinusXBinContSum[72];
	 XMeanMinusXBinContSumTwo[6][9]= XMeanMinusXBinContSum[73];
	 XMeanMinusXBinContSumTwo[6][10]= XMeanMinusXBinContSum[74];
	 XMeanMinusXBinContSumTwo[6][11]= XMeanMinusXBinContSum[75];
	 XMeanMinusXBinContSumTwo[6][12]= XMeanMinusXBinContSum[76];
	 XMeanMinusXBinContSumTwo[6][13]= XMeanMinusXBinContSum[77];

	 XMeanMinusXBinContSumTwo[7][1]= XMeanMinusXBinContSum[78];
	 XMeanMinusXBinContSumTwo[7][2]= XMeanMinusXBinContSum[79];
	 XMeanMinusXBinContSumTwo[7][3]= XMeanMinusXBinContSum[80];
	 XMeanMinusXBinContSumTwo[7][4]= XMeanMinusXBinContSum[81];
	 XMeanMinusXBinContSumTwo[7][5]= XMeanMinusXBinContSum[82];
	 XMeanMinusXBinContSumTwo[7][6]= XMeanMinusXBinContSum[83];
	 XMeanMinusXBinContSumTwo[7][7]= XMeanMinusXBinContSum[84];
	 XMeanMinusXBinContSumTwo[7][8]= XMeanMinusXBinContSum[85];
	 XMeanMinusXBinContSumTwo[7][9]= XMeanMinusXBinContSum[86];
	 XMeanMinusXBinContSumTwo[7][10]= XMeanMinusXBinContSum[87];
	 XMeanMinusXBinContSumTwo[7][11]= XMeanMinusXBinContSum[88];
	 XMeanMinusXBinContSumTwo[7][12]= XMeanMinusXBinContSum[89];
	 XMeanMinusXBinContSumTwo[7][13]= XMeanMinusXBinContSum[90];

	 XMeanMinusXBinContSumTwo[8][1]= XMeanMinusXBinContSum[91];
	 XMeanMinusXBinContSumTwo[8][2]= XMeanMinusXBinContSum[92];
	 XMeanMinusXBinContSumTwo[8][3]= XMeanMinusXBinContSum[93];
	 XMeanMinusXBinContSumTwo[8][4]= XMeanMinusXBinContSum[94];
	 XMeanMinusXBinContSumTwo[8][5]= XMeanMinusXBinContSum[95];
	 XMeanMinusXBinContSumTwo[8][6]= XMeanMinusXBinContSum[96];
	 XMeanMinusXBinContSumTwo[8][7]= XMeanMinusXBinContSum[97];
	 XMeanMinusXBinContSumTwo[8][8]= XMeanMinusXBinContSum[98];
	 XMeanMinusXBinContSumTwo[8][9]= XMeanMinusXBinContSum[99];
	 XMeanMinusXBinContSumTwo[8][10]= XMeanMinusXBinContSum[100];
	 XMeanMinusXBinContSumTwo[8][11]= XMeanMinusXBinContSum[101];
	 XMeanMinusXBinContSumTwo[8][12]= XMeanMinusXBinContSum[102];
	 XMeanMinusXBinContSumTwo[8][13]= XMeanMinusXBinContSum[103];

	 XMeanMinusXBinContSumTwo[9][1]= XMeanMinusXBinContSum[104];
	 XMeanMinusXBinContSumTwo[9][2]= XMeanMinusXBinContSum[105];
	 XMeanMinusXBinContSumTwo[9][3]= XMeanMinusXBinContSum[106];
	 XMeanMinusXBinContSumTwo[9][4]= XMeanMinusXBinContSum[107];
	 XMeanMinusXBinContSumTwo[9][5]= XMeanMinusXBinContSum[108];
	 XMeanMinusXBinContSumTwo[9][6]= XMeanMinusXBinContSum[109];
	 XMeanMinusXBinContSumTwo[9][7]= XMeanMinusXBinContSum[110];
	 XMeanMinusXBinContSumTwo[9][8]= XMeanMinusXBinContSum[111];
	 XMeanMinusXBinContSumTwo[9][9]= XMeanMinusXBinContSum[112];
	 XMeanMinusXBinContSumTwo[9][10]= XMeanMinusXBinContSum[113];
	 XMeanMinusXBinContSumTwo[9][11]= XMeanMinusXBinContSum[114];
	 XMeanMinusXBinContSumTwo[9][12]= XMeanMinusXBinContSum[115];
	 XMeanMinusXBinContSumTwo[9][13]= XMeanMinusXBinContSum[116];

	 XMeanMinusXBinContSumTwo[10][1]= XMeanMinusXBinContSum[117];
	 XMeanMinusXBinContSumTwo[10][2]= XMeanMinusXBinContSum[118];
	 XMeanMinusXBinContSumTwo[10][3]= XMeanMinusXBinContSum[119];
	 XMeanMinusXBinContSumTwo[10][4]= XMeanMinusXBinContSum[120];
	 XMeanMinusXBinContSumTwo[10][5]= XMeanMinusXBinContSum[121];
	 XMeanMinusXBinContSumTwo[10][6]= XMeanMinusXBinContSum[122];
	 XMeanMinusXBinContSumTwo[10][7]= XMeanMinusXBinContSum[123];
	 XMeanMinusXBinContSumTwo[10][8]= XMeanMinusXBinContSum[124];
	 XMeanMinusXBinContSumTwo[10][9]= XMeanMinusXBinContSum[125];
	 XMeanMinusXBinContSumTwo[10][10]= XMeanMinusXBinContSum[126];
	 XMeanMinusXBinContSumTwo[10][11]= XMeanMinusXBinContSum[127];
	 XMeanMinusXBinContSumTwo[10][12]= XMeanMinusXBinContSum[128];
	 XMeanMinusXBinContSumTwo[10][13]= XMeanMinusXBinContSum[129];

	 XMeanMinusXBinContSumTwo[11][1]= XMeanMinusXBinContSum[130];
	 XMeanMinusXBinContSumTwo[11][2]= XMeanMinusXBinContSum[131];
	 XMeanMinusXBinContSumTwo[11][3]= XMeanMinusXBinContSum[132];
	 XMeanMinusXBinContSumTwo[11][4]= XMeanMinusXBinContSum[133];
	 XMeanMinusXBinContSumTwo[11][5]= XMeanMinusXBinContSum[134];
	 XMeanMinusXBinContSumTwo[11][6]= XMeanMinusXBinContSum[135];
	 XMeanMinusXBinContSumTwo[11][7]= XMeanMinusXBinContSum[136];
	 XMeanMinusXBinContSumTwo[11][8]= XMeanMinusXBinContSum[137];
	 XMeanMinusXBinContSumTwo[11][9]= XMeanMinusXBinContSum[138];
	 XMeanMinusXBinContSumTwo[11][10]= XMeanMinusXBinContSum[139];
	 XMeanMinusXBinContSumTwo[11][11]= XMeanMinusXBinContSum[140];
	 XMeanMinusXBinContSumTwo[11][12]= XMeanMinusXBinContSum[141];
	 XMeanMinusXBinContSumTwo[11][13]= XMeanMinusXBinContSum[142];

	 XMeanMinusXBinContSumTwo[12][1]= XMeanMinusXBinContSum[143];
	 XMeanMinusXBinContSumTwo[12][2]= XMeanMinusXBinContSum[144];
	 XMeanMinusXBinContSumTwo[12][3]= XMeanMinusXBinContSum[145];
	 XMeanMinusXBinContSumTwo[12][4]= XMeanMinusXBinContSum[146];
	 XMeanMinusXBinContSumTwo[12][5]= XMeanMinusXBinContSum[147];
	 XMeanMinusXBinContSumTwo[12][6]= XMeanMinusXBinContSum[148];
	 XMeanMinusXBinContSumTwo[12][7]= XMeanMinusXBinContSum[149];
	 XMeanMinusXBinContSumTwo[12][8]= XMeanMinusXBinContSum[150];
	 XMeanMinusXBinContSumTwo[12][9]= XMeanMinusXBinContSum[151];
	 XMeanMinusXBinContSumTwo[12][10]= XMeanMinusXBinContSum[152];
	 XMeanMinusXBinContSumTwo[12][11]= XMeanMinusXBinContSum[153];
	 XMeanMinusXBinContSumTwo[12][12]= XMeanMinusXBinContSum[154];
	 XMeanMinusXBinContSumTwo[12][13]= XMeanMinusXBinContSum[155];

	 XMeanMinusXBinContSumTwo[13][1]= XMeanMinusXBinContSum[156];
	 XMeanMinusXBinContSumTwo[13][2]= XMeanMinusXBinContSum[157];
	 XMeanMinusXBinContSumTwo[13][3]= XMeanMinusXBinContSum[158];
	 XMeanMinusXBinContSumTwo[13][4]= XMeanMinusXBinContSum[159];
	 XMeanMinusXBinContSumTwo[13][5]= XMeanMinusXBinContSum[160];
	 XMeanMinusXBinContSumTwo[13][6]= XMeanMinusXBinContSum[161];
	 XMeanMinusXBinContSumTwo[13][7]= XMeanMinusXBinContSum[162];
	 XMeanMinusXBinContSumTwo[13][8]= XMeanMinusXBinContSum[163];
	 XMeanMinusXBinContSumTwo[13][9]= XMeanMinusXBinContSum[164];
	 XMeanMinusXBinContSumTwo[13][10]= XMeanMinusXBinContSum[165];
	 XMeanMinusXBinContSumTwo[13][11]= XMeanMinusXBinContSum[166];
	 XMeanMinusXBinContSumTwo[13][12]= XMeanMinusXBinContSum[167];
	 XMeanMinusXBinContSumTwo[13][13]= XMeanMinusXBinContSum[168];
	  cout<<"XMeanMinusXBinContSumTwo[13][13]"<<XMeanMinusXBinContSumTwo[13][13]<<endl;


  for( int i(0); i<= 168; i++)
  {
   // cout<<"XMeanMinusXBinContSum[168]"<<XMeanMinusXBinContSum[0]<<endl;
  }



  for( int i(1); i<= SVD_Post.data->GetNbinsX(); i++)
  {
    for( int j(1); j<= SVD_Post.data->GetNbinsX(); j++)
        {
	 // SVD_Post.BstatCov->SetBinContent(i,j, fabs(XMeanMinusXBinContSumTwo[i][j])  );
	  SVD_Post.BstatCov->SetBinContent(i,j, XMeanMinusXBinContSumTwo[i][j]  );
	  cout<<"XMeanMinusXBinContSumTwo[i][j]:   "<<" i = "<<i<<" j = "<<j<<"  "<<XMeanMinusXBinContSumTwo[i][j]<<endl;
	  //cout<<"XMeanMinusXBinContSumTwo[i][j]:   "<<" i = "<<i<<" j = "<<j<<"  "<<fabs(XMeanMinusXBinContSumTwo[i][j])<<endl;
	}
  }

  
  for( int i(1); i<= SVD_Post.data->GetNbinsX(); i++)
  {
    for( int j(1); j<= SVD_Post.data->GetNbinsX(); j++)
        {
	  SVD_Post.BstatCorr->SetBinContent(i,j, fabs(XMeanMinusXBinContSumTwo[i][j])/sqrt(fabs(XMeanMinusXBinContSumTwo[i][i])*fabs(XMeanMinusXBinContSumTwo[j][j]))  );
	  //SVD_Post.BstatCorr->SetBinContent(i,j, XMeanMinusXBinContSumTwo[i][j]/sqrt((XMeanMinusXBinContSumTwo[i][i])*(XMeanMinusXBinContSumTwo[j][j]))  );
	  //SVD_Post.BstatCorr->SetBinContent(i,j, SVD_Post.BstatCov->GetBinContent(i)/sqrt()  );
	  
	}
  }



  for( int i(1); i<= SVD_Post.data->GetNbinsX(); i++)
  {

   // cout<<"XMean[i-1]                      : "<<i<<" "<<XMean[i-1]<<endl;
    //cout<<"XMeanMinusXBinContSumTwo[i][i]  : "<<i<<""<<i<<"    "<<XMeanMinusXBinContSumTwo[i][i]<<endl;
    cout<<"Recon Effi CovMatrix            : "<<i<<""<<i<<"    "<<XMeanMinusXBinContSumTwo[i][i]<<endl;
    //cout<<"Syst presentage %               : "<<i<<"         "<<(XMeanMinusXBinContSumTwo[i][i])/XMean[i-1]*100<<endl;
    cout<<"Systematics                     : "<<"               "<<sqrt(XMeanMinusXBinContSumTwo[i][i])<<endl;
	  
  }








//  TSVDUnfold *tsvdData = new TSVDUnfold(
//      SVD_Post.data,SVD_Post.bini,SVD_Post.xini,SVD_Post.Adet);
  
  TSVDUnfold *tsvdData = new TSVDUnfold(
      SVD_Post.data,SVD_Post.BstatCov,SVD_Post.bini,SVD_Post.xini,SVD_Post.Adet);
  
//  SVD_Post.statCov = tsvdData->GetBCov();
  tsvdData->SetNormalize( kFALSE );
  SVD_Post.unfRes = tsvdData->Unfold(4);
  SVD_Post.dDist = tsvdData->GetD();
  SVD_Post.svDist = tsvdData->GetSV();
  
  //SVD_Post.uStatCov = tsvdData->GetUnfoldCovMatrix( SVD_Post.statCov, 100);
  SVD_Post.uStatCov = tsvdData->GetUnfoldCovMatrix( SVD_Post.BstatCov, 100);
  
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
//  pltUnfPost->AddHist1D(SVD_Post.Gen,"hist",kGreen,1,0,0,0);
//  pltUnfPost->AddHist1D(SVD_Post.EffCorr,"elp",kGreen+2,0,0,26,2.0);
  
 // pltUnfPost->SetLegend(0.68,0.57,0.93,0.8);
  pltUnfPost->SetLegend(0.55,0.55,0.9,0.8);
  pltUnfPost->GetLegend()->AddEntry(SVD_Post.unfRes,"Unfolded","p");
  pltUnfPost->GetLegend()->AddEntry(SVD_Post.data,"Recon","p");
  //pltUnfPost->GetLegend()->AddEntry(SVD_Post.True,"Truth","l");
  //pltUnfPost->GetLegend()->AddEntry(SVD_Post.True,"Powheg Truth","l");
  pltUnfPost->GetLegend()->AddEntry(SVD_Post.True,"Powheg Pythia","l");
//  pltUnfPost->GetLegend()->AddEntry(SVD_Post.Gen,"Powheg Post","l");
//  pltUnfPost->GetLegend()->AddEntry(SVD_Post.EffCorr,"EffCorr","p");
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
  




  tmpTStr = "Reco_cov_"+BaseName;
  pltRecon_cov = new CPlot(tmpTStr,"Recon Covariance matrix","","");
  pltRecon_cov->setOutDir(resultDir);
  gPad->SetLogz();
  pltRecon_cov->AddHist2D(SVD_Post.BstatCov,"COLZ",kWhite,kBlack);
  pltRecon_cov->Draw(myCan,kTRUE,"png");

  tmpTStr = "Reco_corr_"+BaseName;
  pltRecon_corr = new CPlot(tmpTStr,"Recon Correlation matrix","","");
  pltRecon_corr->setOutDir(resultDir);
  gPad->SetLogz(0);
  pltRecon_corr->AddHist2D(SVD_Post.BstatCorr,"COLZ",kWhite,kBlack);
  pltRecon_corr->Draw(myCan,kTRUE,"png");


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

  for( int i(1);i<=SVD_Born.unfRes->GetNbinsX(); i++)
  {
    cout<<"SVD_Born.uStatCov_i_i :   "<< i <<" "<<i<<"     "<<SVD_Born.uStatCov->GetBinContent(i,i)<<endl;
    cout<<"Unfold Systematics    :                      "<<TMath::Sqrt(SVD_Born.uStatCov->GetBinContent(i,i))<<endl;
  //  cout<<TMath::Sqrt(SVD_Born.uStatCov->GetBinContent(i,i))<<endl;
  }
  



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
  //pltUnfBorn->SetLegend(0.68,0.57,0.93,0.8);
  pltUnfBorn->SetLegend(0.55,0.57,0.93,0.93);
  //pltUnfBorn->GetLegend()->AddEntry(SVD_Born.unfRes,"Unfolded","p");
  pltUnfBorn->GetLegend()->AddEntry(SVD_Born.unfRes,"Unfolded to Both fiducial","p");
  pltUnfBorn->GetLegend()->AddEntry(SVD_Born.data,"Post","p");
  //pltUnfBorn->GetLegend()->AddEntry(SVD_Born.True,"Born Target","l");
  pltUnfBorn->GetLegend()->AddEntry(SVD_Born.True,"Born in the Both fiducial","l");
  //pltUnfBorn->GetLegend()->AddEntry(SVD_Born.Gen,"Born Gen","l");
  pltUnfBorn->GetLegend()->AddEntry(SVD_Born.Gen,"Born fiducial","l");
  pltUnfBorn->GetLegend()->AddEntry(SVD_Born.EffCorr,"EffCorr","l");
  pltUnfBorn->Draw(myCan,kTRUE,"png");

  tmpTStr = "Born_cov_"+BaseName;
  pltUnfBorn_cov = new CPlot(tmpTStr,"TSVDUnfold Covariance matrix","","");
  pltUnfBorn_cov->setOutDir(resultDir);
  //pltUnfBorn_cov->AddHist2D(SVD_Post.uStatCov,"COLZ",kWhite,kBlack);
  pltUnfBorn_cov->AddHist2D(SVD_Born.uStatCov,"COLZ",kWhite,kBlack);
  pltUnfBorn_cov->Draw(myCan,kTRUE,"png");

  tmpTStr = "Born_d_"+BaseName;
  pltUnfBorn_d = new CPlot(tmpTStr,"TSVDUnfold |di|","i","|d_{i}|");
  pltUnfBorn_d->setOutDir(resultDir);
  pltUnfBorn_d->AddHist1D(SVD_Post.dDist,"",kBlack,1,0,0,0);
  pltUnfBorn_d->AddLine(0,1,13,1,kBlack,1);
  pltUnfBorn_d->Draw(myCan,kTRUE,"png");


  ////Systematic in %
  for( int i(1);i<=SVD_Born.unfRes->GetNbinsX(); i++)
  {
   // cout<<SVD_Born.EffCorr->GetBinContent(i) <<endl;
    cout<<TMath::Sqrt(SVD_Born.uStatCov->GetBinContent(i,i)) /SVD_Born.EffCorr->GetBinContent(i)*100 <<endl;
  }


  // Write to root file
  SVD_Post.data->Write();
//  sprintf(tmpName,"h1_SVD_Post_data_%d",k);
//  h1_SVD_Post_data[k] = (TH1D*)SVD_Post.data->Clone(tmpName);
//  h1_SVD_Post_data[k]->Sumw2();
//  h1_SVD_Post_data[k]->Write();


  SVD_Born.EffCorr->Write();
//  sprintf(tmpName,"h1_SVD_Born_EffCorr_%d",k);
//  h1_SVD_Born_EffCorr[k] = (TH1D*)SVD_Born.EffCorr->Clone(tmpName);
//  h1_SVD_Born_EffCorr[k]->Sumw2();
//  h1_SVD_Born_EffCorr[k]->Write();


  SVD_Born.Gen->Write();
//  sprintf(tmpName,"h1_SVD_Born_Gen_%d",k);
//  h1_SVD_Born_Gen[k] = (TH1D*)SVD_Born.Gen->Clone(tmpName);
//  h1_SVD_Born_Gen[k]->Sumw2();
//  h1_SVD_Born_Gen[k]->Write();

  SVD_Post.True->Write();
//  sprintf(tmpName,"h1_SVD_Post_True_%d",k);
//  h1_SVD_Post_True[k] = (TH1D*)SVD_Post.True->Clone(tmpName);
//  h1_SVD_Post_True[k]->Sumw2();
//  h1_SVD_Post_True[k]->Write();


  SVD_Post.unfRes->Write();
//  sprintf(tmpName,"h1_SVD_Post_unfRes_%d",k);
//  h1_SVD_Post_unfRes[k] = (TH1D*)SVD_Post.unfRes->Clone(tmpName);
//  h1_SVD_Post_unfRes[k]->Sumw2();
//  h1_SVD_Post_unfRes[k]->Write();

  SVD_Post.Gen->Write();
//  sprintf(tmpName,"h1_SVD_Post_Gen_%d",k);
//  h1_SVD_Post_Gen[k] = (TH1D*)SVD_Post.Gen->Clone(tmpName);
//  h1_SVD_Post_Gen[k]->Sumw2();
//  h1_SVD_Post_Gen[k]->Write();
  

// }

   return 0;
  

}
