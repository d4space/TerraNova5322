//
// root -l sgnfc.C+'("DATA","W_Lept1_dPhiIn","EB","WEleNeu/tree")'
//

#include <iostream>
#include <algorithm>

#include <cstdlib>
#include <cstdio>

#include <vector>
#include <map>

#include "TString.h"
#include "TFile.h"
#include "TTree.h"

#include "TH1F.h"
#include "TMath.h"
#include "TCut.h"
#include "THStack.h"
#include "TColor.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TBranch.h"

#include "TLegend.h"
#include "TArrow.h"
#include "TLine.h"

#include "TSystemDirectory.h"
#include "TSystemFile.h"



#define NSmp 12
#define Bins 100
#define MAXLINE 256

//#define Debug true  //1 yes, 0 No
#define Debug false  //1 yes, 0 No

using namespace std;

vector<TString>  strV_Variables;
vector<TString>  strV_Samples;

typedef map< TString, vector<TString> > AnaInputInfo;
AnaInputInfo  mVariables;

typedef map< TString, Int_t >    HistSetInfoInt;
typedef map< TString, Double_t > HistSetInfoDouble;
HistSetInfoInt      Hst_IntBin;
HistSetInfoDouble   Hst_MinMax;

void     mainSGNFC(TH1F*,TH1F* hA,TH1F* hB,TH1F* hQ, AnaInputInfo);
void     Init();

TCut     DefineCut( AnaInputInfo );
void     getHist( AnaInputInfo, TCut,TString);
TH1F*    getHistfrSample(AnaInputInfo, TString, TCut, TString);
TH1F*    getHistfrTree(TTree*, AnaInputInfo, TString, TCut, Int_t, Int_t,TString);
TList*   getFileList(AnaInputInfo ,TString );
TH1F*    getHistfrFileList(TList* , AnaInputInfo, TString, TCut,TString);

TFile*   getFile(TString,TString);
TTree*   getTree(TFile* file_,TString TrName_);
void     setBranch(TTree* Tree_, TString BrName_);

Color_t  SmpClr(TString Sname_);
void     DecoHist(TH1F* h, TString Sname_);
TH1F*    HistSQRT(TH1F* histsq, TString hname,TString htitle);
TH1F*    HistNEW(TH1F* histnw, TString hname,TString htitle);
//TH1F*    SumBGHists(Int_t imin,Int_t imax);
TH1F*    SumBGHists(TH1F* histRef_, Int_t imin_,Int_t imax_, TString);
TH1F*    SumRDHists(TH1F* histRef_, Int_t imin_,Int_t imax_);
TH1F*    HistRatio(TH1F* histA_, TH1F* histB_, TString);
TH1F*    HistDrawSame(TH1F* histA_, TH1F* histB_);
THStack* StkBGHists(Int_t imin,Int_t imax);
THStack* StkHists(TH1F*, TH1F*);
THStack* StkHists(TH1F*, TH1F*, TH1F*);
Double_t getLumiW(TString Sname_);
Double_t CnvtCutBin(Double_t, TH1F*);
Double_t getCutValue(TString Vname_,TString iEcal_);

//TString Sname[NSmp];
//TFile*  file[NSmp];
//TTree*  tr[NSmp];
//TCanvas* c1[NSmp];
TH1F*   hist[NSmp];
TH1F*   histRD[3];
TH1F*   h_ref;
TH1F*   h_sig;
TH1F*   h_bgd;
TH1F*   h_qcd;
TH1F*   h_RD;
THStack *hs_bgd;


vector<double>  *vBranch;
TBranch         *b_Branch;   //
Double_t*       treeX ;

Double_t xmin;
Double_t xmax;

Int_t iBGmin;
Int_t iBGmax;

Int_t nwBins;

Int_t nfl;


//
//W_Lept1_X
//pt, et, eta, phi,etaSC,phiSC,dEtaIn,dPhiIn,sigmaIEtaIEta,HoverE
//

//void sgnfc(TString dir,TString vname="W_Lept1_pt",TString tname="WEleNeu/tree") 
void sgnfc(TString dir,TString target="W_Lept1_dPhiIn", TString iEcal="EB", Int_t nfile=1, TString treeName="WEleNeu/tree" ) 
{
  cout<<""<<endl; 

  Init();
  if(nfile == -1){ nfl=9999;}
  else {nfl = nfile -1;}

  mVariables["BaseDIR"].push_back(dir);
  mVariables["Target"].push_back(target);
  mVariables["iEcal"].push_back(iEcal);
  mVariables["treeName"].push_back(treeName);
  mVariables["ext"].push_back(".root");
  mVariables["HistRef"].push_back("MC");

  mVariables["RD"].push_back("Run2012A_13Jul"); 
  mVariables["RD"].push_back("Run2012A_recover_06Aug"); 
  mVariables["RD"].push_back("Run2012C_EcalRecover_11Dec_v1"); 

  mVariables["MC"].push_back("WToENu"); 
  //mVariables["MC"].push_back("WminusToENu");
  //mVariables["MC"].push_back("WplusToENu");
  
  mVariables["MC"].push_back("DYToEE");
  mVariables["MC"].push_back("DYToTauTau");
  //  mVariables["MC"].push_back("DYJetsToLL");
  
  mVariables["MC"].push_back("WToTauNu");
  //mVariables["MC"].push_back("WplusToTauNu");
  //mVariables["MC"].push_back("WminusToTauNu");

  //  mVariables["MC"].push_back("TTJets_MassiveBinDECAY");

  mVariables["MC"].push_back("G_Pt50to80");
  //  mVariables["MC"].push_back("TT_CT10");
  
  //  mVariables["MC"].push_back("WJetsToLNu");

  mVariables["MC"].push_back("QCD_pt30to50");
  mVariables["MC"].push_back("QCD_pt50to80");
  mVariables["MC"].push_back("QCD_pt80to120");
  mVariables["MC"].push_back("QCD_pt120to170");


  TCut Cuts = DefineCut(mVariables);

  getHist(mVariables,Cuts,"MC");
  getHist(mVariables,Cuts,"RD");
  //  TCanvas *ctest ;//= new TCanvas("ctest","ctest",600,400);
  //  histRD[1]->Draw();


  if(Debug)cout<<"check 1"<<endl;
  if(Debug && !hist[0])cout<<"main:: histMC error"<<endl;

  //  hs_bgd = StkBGHists(iBGmin,iBGmax);
  if(Debug)cout<<"check 1-1"<<endl;

  h_ref = (TH1F*)hist[0]->Clone();

  h_bgd  = SumBGHists(h_ref,1,4,"others");
    
  if(Debug)cout<<"check 1-1-1"<<endl;
  h_qcd  = SumBGHists(h_ref,5,8,"qcd");
  //h_qcd = (TH1F*)hist[9]->Clone();
  if(Debug)cout<<"check 1-1-2"<<endl;
  DecoHist(h_bgd,"Others");
  DecoHist(h_qcd,"QCD");

  //h_bgd  = SumBGHists(hist[0],3,8,"AllBG");
  //h_qcd  = SumBGHists(hist[0],10,13,"qcd");
  h_RD  = SumRDHists(h_ref,0,2);
  if(Debug)cout<<"check 1-1-3"<<endl;
  if(Debug)cout<<"check 1-2"<<endl;
  
  Int_t k = 0;
  mainSGNFC(h_RD,hist[k],h_bgd,h_qcd, mVariables);
  //mainSGNFC(histRD[k],hist[k],h_bgd,h_qcd, mVariables);
  
}
/////////////////////////////////////////////////////////////////////////
void getHist(AnaInputInfo mVariables_,TCut Cuts_,TString SType_){
  if(Debug)cout<<"getHist:: "<<endl;

  vector<TString> vSmpNames = mVariables_[SType_];  
  for(unsigned int i=0;i<vSmpNames.size();i++){
    if(Debug)cout<<""<<endl;
    if(Debug)cout<<"getHist:: "<<vSmpNames[i]<<endl;
    if(SType_=="MC"){
      if(Debug)cout<<"getHist::SType -> "<<SType_<<endl;
      hist[i] = (TH1F*)getHistfrSample(mVariables_,vSmpNames[i],Cuts_,SType_);
      if( !hist[i])cout<<"getHist:: no hist !"<<endl;
      DecoHist(hist[i],vSmpNames[i]);
    }
    else if(SType_=="RD"){
      if(Debug)cout<<"getHist::SType -> "<<SType_<<endl;
      histRD[i] = (TH1F*)getHistfrSample(mVariables_,vSmpNames[i],Cuts_,SType_);
      if( !histRD[i])cout<<"getHist:: no hist !"<<endl;
    }

    //hist[i]->Scale(getLumiW(vSmpNames[i])); // one of Normalization Way


  }
}

TH1F* getHistfrSample(AnaInputInfo mVariables_,TString SampleName_,TCut Cuts_,TString SType_){
  if(Debug)cout<<"getHistfrSample:: "<<endl;
  TH1F* h;
  TList* fileList = getFileList(mVariables_, SampleName_);
  if(Debug && fileList) cout<<""<<endl;
  h = (TH1F*)getHistfrFileList(fileList, mVariables_, SampleName_, Cuts_,SType_);
  return h;
}

/////////////////////////////////////////////////////
//void getFileHist(const char *dirname="", const char *ext=".root"){
TList* getFileList(AnaInputInfo  mVariables_,TString SampleName_){
  if(Debug)cout<<"getFileList:: "<<endl;
  vector<TString> path = mVariables_["BaseDIR"];
  TString path_= path[0]+"/"+SampleName_;
  TString dir_ = "dir_"+SampleName_;
  if(Debug) cout<<"getFileList:: File location = "<<path_<<endl;
  TSystemDirectory directory(dir_, path_);
  TList *files_ = directory.GetListOfFiles();
  return files_;
}

/////////////////////////////////////////////////////
TH1F* getHistfrFileList(TList* filelist_, AnaInputInfo  mVariables_,TString SampleName_,TCut Cuts_,TString SType_){ 
  TH1F* h =0;
  Int_t i =0;
  Int_t idx_ =0;
  if(Debug)cout<<"getHistfrFileList:: "<<endl;

  vector<TString> path = mVariables_["BaseDIR"];
  TString path_ = path[0];  path_ += "/"+SampleName_;
  cout<<""<<endl;
  cout<<"getHistfrFileList:: path_ -> "<<path_<<endl;
  vector<TString> branchNM = mVariables_["Target"];
  TString branch = branchNM[0];

  vector<TString> treeNM = mVariables_["treeName"];
  TString trName = treeNM[0];

  vector<TString> vEcal = mVariables_["iEcal"];
  TString iEcal_ = vEcal[0];


  vector<TString> vext = mVariables_["ext"];
  TString ext_ = vext[0];

  vector<TString> SNMs = mVariables_[SType_];
  for(unsigned int isn=0;isn<SNMs.size();isn++){
    if(SNMs[isn] == SampleName_) idx_= isn;
  }
  if(Debug)cout<<"getHistfrFileList:: idx_ "<<idx_<<endl;  

  if (filelist_) {

    if(Debug)cout<<"getHistfrFileList:: inside if(fileList_) "<<endl;

    TSystemFile *sysfile_;
    TString fname_;
    TIter next_(filelist_);

    while ( (sysfile_=(TSystemFile*)next_()) ) {
      fname_ = sysfile_->GetName();
      if(i > nfl){cout<<"getHistfrFileList:: file skip i > "<<nfl<<endl; continue;}//break;}      
      if (!sysfile_->IsDirectory() && fname_.EndsWith(ext_)) {
	cout <<SampleName_<<"/"<<fname_.Data() << endl;
	TFile* file_ =0;	file_=getFile(path_,fname_);
	if(!file_){cout<<"getHistfrFileList:: no File "<<endl; continue;}// break;}
	TTree* tree_ =0;        tree_=getTree(file_,trName);
	if(!tree_){cout<<"getHistfrFileList:: no Tree "<<endl; continue;} //break;}
	setBranch(tree_,branch);
	TH1F* htmp =0;
	if(Debug)cout<<"hhh "<<i<<endl;
	htmp = getHistfrTree(tree_, mVariables_, SampleName_, Cuts_, idx_, i,SType_);
	if(!htmp){cout<<"getHistfrFileList:: no Hist "<<endl; continue;}//break;}
	if(i ==0 ) h = (TH1F*)htmp->Clone();
	else h->Add( htmp );
	i++;

      }//if
    }//while
  }//if(files_)
  else{cout<<"getHistfrFileList:: Out of fileList_ "<<endl;}
  return h;
}

/////////////////////////////////////////////////////
TH1F*  getHistfrTree(TTree* Tree_, AnaInputInfo  mVariables_, TString SmName_, TCut Cut_, Int_t idx_, Int_t i_, TString SType_){
  if(Debug)cout<<"getHistfrTree:: "<<endl;
  vector<TString> vTarget = mVariables_["Target"];
  TString VaName_ = vTarget[0];

  vector<TString> vEcal = mVariables_["iEcal"];
  TString iEcal_ = vEcal[0];

  //  mVariables["HistRef"].push_back("MC");
  //  vector<TString> vHistRef = mVariables_["HistRef"];
  //  TString href_ = vHistRef[0];

  const unsigned nentries_ = Tree_->Draw(VaName_,Cut_);
  if(Debug)cout<<"kk"<<endl;

  TString iter ="";
  iter.Form("%d",i_);
  
  TH1F* hist_ =0;
  if(nentries_) {
    if(Debug)cout<<"kk 00 "<<endl;
    treeX = Tree_->GetV1();
    
    if( idx_ == 0 && i_ ==0 && SType_ =="MC"){ //if MC WToENu
      if(Debug)cout<<"getHistfrTree:: idx_ "<<idx_<<" i_ "<<i_<<" SType_ "<<SType_<<endl;
      xmax = (*(std::max_element(treeX, treeX+nentries_))) ;
      xmin = (*(std::min_element(treeX, treeX+nentries_)));

      //for Absolute Values
      xmax = xmax > xmin ? xmax : xmin;
      xmin =0.0;

      //
      Double_t binUnit = (xmax - xmin)/Bins;
      xmax += binUnit * (Bins*0.05); 
      xmin -= binUnit * (Bins*0.05);
      nwBins = (Int_t)Bins*1.1;
    
      //Hst_IntBin["bin"].push_back(nwbins);
      //Hst_MinMax["min"].push_back(xmin);
      //Hst_MinMax["max"].push_back(xmax);
      if(Debug)cout<<"getHistfrTree:: ** Default histogram infor set **"<<endl;
      Hst_IntBin["bin"]=nwBins;
      Hst_MinMax["min"]=xmin;
      Hst_MinMax["max"]=xmax;
    }
    if(Debug)cout<<"kk 11 "<<endl;
    //    if(Debug)cout<<"getHistfrTree:: nwBins =  "<<nwBins<<" xmin = "<<xmin<<" xmax = "<<xmax<<endl;

    //  vector<TString> vEcal = mVariables_["iEcal"];
    //TString iEcal_ = vEcal[0];
    //    Int_t xbins = Hst_IntBin["bin"];
    if(Debug)cout<<"getHistfrTree:: nwBins =  " <<Hst_IntBin["bin"]
		 <<" xmin = "<<Hst_MinMax["min"]
		 <<" xmax = "<<Hst_MinMax["max"]
		 <<endl;
    TString hitname_ = "h_"+SmName_+"_"+VaName_+"_"+iEcal_+"_"+iter;
    hist_ = new TH1F(hitname_,hitname_,nwBins,xmin,xmax);
    //    if( idx_==0) //h_ref = (TH1F*)hist_->Clone("h_ref");
    if(Debug)cout<<"kk 22 "<<endl;
    if(Debug)cout<<"getHistfrTree::getLumiW = "<<SmName_<<" weight = "<<getLumiW(SmName_)<<endl;

    for(unsigned int k_=0; k_<nentries_;++k_){
      //    hist_->Fill(treeX[k_]);
      //    hist_->Fill(treeX[k_],getLumiW(SmName_)); // one of Normalization Way
      hist_->Fill(fabs(treeX[k_]),getLumiW(SmName_)); // one of Normalization Way
    }
  }
  if(Debug)cout<<"kk 33 "<<endl;
  return hist_;
}



/////////////////////////////////////////////////////
TCut DefineCut(AnaInputInfo  mVariables_){
  vector<TString> vEcal = mVariables_["iEcal"];
  TString iEcal_ = vEcal[0];
  if(Debug)cout<<"DefineCut:: iECal = "<<iEcal_<<endl;
  TCut cut1 = "HLT_Ele27_WP80.fired == 1";
  TCut cut2 = "W_Lept1_pt > 30";
  TCut cut3_EB = "W_Lept1_sigmaIEtaIEta < 0.01";
  TCut cut3_EE = "W_Lept1_sigmaIEtaIEta < 0.03";
  //TCut cut4 = "W_Lept1_etaSC < 1.4442";
  //TCut cut5 = "W_Lept1_etaSC > 1.566 && W_Lept1_etaSC < 2.5";
  //TCut cut6 = "W_Lept1_etaSC < -1.566 && W_Lept1_etaSC > -2.5";
  //TCut cut_EB = cut3&&cut4;
  //TCut cut_EE = cut5&&cut6;
  TCut cut7 = "abs(W_Lept1_etaSC) < 1.4442";
  TCut cut8 = "abs(W_Lept1_etaSC) > 1.566 && abs(W_Lept1_etaSC) < 2.5";
  TCut cut9 = "abs(W_Lep1_etaSC)<2.5";
  TCut cut0 = "";
  TCut cEcal = "";

  TCut tcuts;

  if(iEcal_ == "EB"){ cEcal = cut7;
    if(Debug)cout<<"DefineCut:: if EB"<<endl;
  }
  else if(iEcal_ == "EE"){cEcal = cut8;
    if(Debug)cout<<"DefineCut:: if EE"<<endl;
  }
  else if(iEcal_ == "EBEE"){cEcal = cut7||cut8;
    if(Debug)cout<<"DefineCut:: if EBEE"<<endl;
  }
  else if(iEcal_ == "ALL"){cEcal = cut8;
    if(Debug)cout<<"DefineCut:: if ALL(<2.5)"<<endl;
  }

  tcuts = cut1&&cut2&&cEcal;

  return tcuts;
}


/////////////////////////////////////////////////////
TH1F*  SumBGHists(TH1F* histRef_, Int_t imin_,Int_t imax_,TString Name_){
  TH1F* sumHist_ = 0;
  sumHist_ = HistNEW(histRef_,"Sum"+Name_,"Summation of "+Name_);
  //  sumHist_ = (TH1F*)hist[imin_]->Clone("Sum"+Name_);
  //sumHist_ = (TH1F*)histRef_->Clone("Sum"+Name_);
  for(Int_t ix=imin_;ix<imax_+1;ix++){
    sumHist_->Add(hist[ix]);
  }
  return sumHist_;
}

/////////////////////////////////////////////////////
TH1F*  SumRDHists(TH1F* histRef_, Int_t imin_,Int_t imax_){
  TH1F* sumHist_ = 0;
  sumHist_ = HistNEW(histRef_,"SumRD","Summation of RD");
  //sumHist_ = (TH1F*)histRef_->Clone("SumRD");
  //  sumHist_ = (TH1F*)histRD[imin_]->Clone("SumRD");
  for(Int_t ix=imin_;ix<imax_+1;ix++){
    sumHist_->Add(histRD[ix]);
  }
  return sumHist_;
}
/////////////////////////////////////////////////////
TH1F* HistNEW(TH1F* histRef_, TString hname_,TString htitle_){
  //  Int_t   nXbins_ = histRef_->GetNbinsX();
  //  Float_t xMin_ = histRef_->GetXaxis()->GetXmin();
  //  Float_t xMax_ = histRef_->GetXaxis()->GetXmax();

  TH1F* hnew_ = new TH1F(hname_, htitle_, nwBins,xmin,xmax);
  return hnew_;
}


/////////////////////////////////////////////////////
TFile*  getFile(TString dirnm_,TString SmpName_){  //getFile(path_,fname_);
  TFile* file_ =0;

  if( !(SmpName_.EndsWith(".root")) )
    file_ = new TFile(dirnm_+"/"+SmpName_+".root");    
  else
    file_ = new TFile(dirnm_+"/"+SmpName_);
  
  if( ! file_ ) cout<<"error while file loading !!!  => "<<SmpName_<<endl;
  
  return file_;
}

/////////////////////////////////////////////////////
TTree*  getTree(TFile* file_, TString TrName_){
  TTree* tree_ =0; 
  tree_ = (TTree*)file_->Get(TrName_);              
  if( ! tree_ ) {
    cout<<"error while tree loading !!!  => "<<endl;//SmpName_<<endl;
    tree_= 0;
  }
  return tree_;
}

/////////////////////////////////////////////////////
void setBranch(TTree* Tree_, TString BrName_){
  Tree_->SetBranchAddress(BrName_, &vBranch, &b_Branch);
}


/////////////////////////////////////////////////////
void Init(){

  vBranch = 0;
  
  iBGmin =3;
  iBGmax =8;
  
  xmin = 0.0;
  xmax = 0.0;
  
  h_ref = 0;
  h_bgd = 0;

  //  strV_Variables = 0; 
  //  strV_Samples =0; 
}

/////////////////////////////////////////////////////
THStack* StkBGHists(Int_t imin,Int_t imax){
  THStack* HS = new THStack("hs_bgd","BGStack");
  for(Int_t i=imin;i<imax+1;i++){
    HS->Add(hist[i]);
  }
  return HS;
}

/////////////////////////////////////////////////////
THStack* StkHists(TH1F* h1,TH1F* h2){
  THStack* HS = new THStack("hs_MC","MCStack");
  HS->Add(h2);
  HS->Add(h1);
  return HS;
}
/////////////////////////////////////////////////////
THStack* StkHists(TH1F* h1,TH1F* h2,TH1F* h3){
  THStack* HS = new THStack("hs_MC","MCStack");
  HS->Add(h3);
  HS->Add(h2);
  HS->Add(h1);
  return HS;
}

/////////////////////////////////////////////////////
void DecoHist(TH1F* h,TString Sname_){
  h->SetFillColor(SmpClr(Sname_));
  h->SetLineColor(SmpClr(Sname_));
}



/////////////////////////////////////////////////////
void mainSGNFC(TH1F* hRD_,TH1F* hA,TH1F* hB,TH1F* hQ,AnaInputInfo  mVariables_) 
{

  vector<TString> branchNM = mVariables_["Target"];
  TString branch = branchNM[0];
  vector<TString> vEcal = mVariables_["iEcal"];
  TString iEcal_ = vEcal[0];
  

  if(Debug == 1)cout<<"check 2-0"<<endl;

  TH1F* h_TotalBGqcd = new TH1F("h_TotalBGqcd","h_TotalBGqcd",nwBins,xmin,xmax);
  h_TotalBGqcd->Add(hA);
  h_TotalBGqcd->Add(hB);
  h_TotalBGqcd->Add(hQ);

  TCanvas* cv = new TCanvas("cv","Contour List",0,0,800,1200);  

  TPad *padUp = new TPad("padUp","padUp",0.02, 0.49, 0.98, 0.98);
  padUp->SetRightMargin(0);
  padUp->SetLeftMargin(0);

  padUp->Draw();
  padUp->cd();
  TPad *padUp01 = new TPad("padUp01","padUp01",0.02, 0.25, 0.98, 0.98);
  padUp01->SetRightMargin(0.04);
  padUp01->SetLeftMargin(0.04);
  padUp01->SetBottomMargin(0);
  padUp01->Draw();
  padUp01->cd();
  
  THStack* hsMCqcd = StkHists(hA,hB,hQ);
  hsMCqcd->SetTitle(branch+"  "+iEcal_);
  int binmax = h_TotalBGqcd->GetMaximumBin();
  double maxbin = h_TotalBGqcd->GetMaximum();
  double maxHist = h_TotalBGqcd->GetXaxis()->GetBinCenter(binmax);// * 1.1;
  cout<<"binmax "<<binmax<<" maxbin "<<maxbin<<" maxHist "<<maxHist<<endl;
  hsMCqcd->SetMaximum(maxbin * 1.2);//  hsMC->SetMaximum();
  // hsMCqcd->GetHistogram()->GetYaxis()->SetLabelSize(0.15);

  //hsMCqcd->SetMaximum(600000.);//  hsMC->SetMaximum();
  hsMCqcd->SetMinimum(0.1);
  hsMCqcd->Draw();
  hRD_->SetMarkerStyle(21);
  hRD_->SetMarkerSize(1);
  hRD_->Draw("epsame");

  TLegend * lg = new TLegend(0.55, 0.55, 0.82, 0.89);
  lg->SetTextSize(0.05);
  lg->SetBorderSize(0);
  lg->SetFillColor(0);

  lg->AddEntry(hA, "WToENu", "F");
  lg->AddEntry(hB, "EWK", "F");
  lg->AddEntry(hQ, "QCD", "F");
  lg->AddEntry(hRD_, "RealData ~1 fb^-1", "LP");
  lg->Draw();

  Double_t cuti = CnvtCutBin(getCutValue(branch,iEcal_),hRD_);
  cout<<cuti<<" iEcal_ "<<iEcal_<<" cutvalue "<< getCutValue(branch,iEcal_)<<endl; 
  //  TArrow ar(cuti,0.1,cuti,0.9,0.05,"<|");
  //  TArrow *ar = new TArrow(0.2,0.1,0.2,0.9,0.05,"<|");

  TArrow *ar = new TArrow(getCutValue(branch,iEcal_),maxbin,getCutValue(branch,iEcal_),1.0,0.02,"|>");
  ar->SetFillColor(kRed);
  ar->SetLineColor(kRed);
  ar->SetLineWidth(1);
  ar->Draw();

  padUp01->Update();

//  padUpL01->SetLogy();
  //hA->SetStats(0);  hB->SetStats(0);
  //hA->SetMaximum(600000.);
  //hA->SetMinimum(0.01);
  //hB->SetLineColor(kBlack);  hB->SetLineWidth(2);
  //hB->Draw(); //hRD_->Draw("same");
  //hA->Draw("same"); 

  padUp->cd();

  TPad *padUp02 = new TPad("padUp02","padUp02",0.02, 0.02, 0.98, 0.25);

  padUp02->SetTopMargin(0);
  padUp02->SetRightMargin(0.04);
  padUp02->SetLeftMargin(0.04);
  padUp02->SetBottomMargin(0.2);
  padUp02->Draw();
  padUp02->cd();


  TH1F* h_rtoMCqcd = HistRatio(hRD_, h_TotalBGqcd,"RDMCqcd");
  h_rtoMCqcd->GetYaxis()->SetLabelSize(0.15);
  h_rtoMCqcd->GetXaxis()->SetLabelSize(0.2);
  h_rtoMCqcd->SetMarkerStyle(21);
  h_rtoMCqcd->Sumw2();
  //  h_rtoMCqcd->SetMaximum(10000.0);  h_rtoMCqcd->SetMaximum(-5.0);
  h_rtoMCqcd->SetStats(0);
  h_rtoMCqcd->Draw("ep");

  //TH1F* h_ratio = HistRatio(hA,hB,"MC");
  //h_ratio->GetYaxis()->SetLabelSize(0.1);
  //h_ratio->GetXaxis()->SetLabelSize(0.1);
  //h_ratio->SetMarkerStyle(21);
  //h_ratio->Sumw2();
  ////  h_ratio->SetMaximum(10000.0);  h_ratio->SetMaximum(-5.0);
  //h_ratio->SetStats(0);
  //h_ratio->Draw("ep");


  cv->cd();   

  TPad *padDn = new TPad("padDn","padDn",0.02, 0.02, 0.98, 0.49);
  padDn->Draw();
  padDn->cd();
  TPad *padDn01 = new TPad("padDn01","padDn01",0.02, 0.25, 0.98, 0.98);
  padDn01->SetRightMargin(0.04);
  padDn01->SetLeftMargin(0.04);
  padDn01->SetBottomMargin(0);
  padDn01->Draw();
  padDn01->cd();
  padDn01->SetLogy();
  //  hsMCqcd->SetTitle(branch+"_"+iEcal_+" LOG");
  //THStack* hsMCqcd = StkHists(hA,hB,hQ);
  //hsMCqcd->SetMinimum(0.1);
  hsMCqcd->Draw();
  //hRD_->SetMarkerStyle(21);
  //hRD_->SetMarkerSize(1);
  hRD_->Draw("epsame");

  TArrow *arL = new TArrow(getCutValue(branch,iEcal_),maxbin,getCutValue(branch,iEcal_),0.05,0.02,"|>");
  arL->SetFillColor(kRed);
  arL->SetLineColor(kRed);
  arL->SetLineWidth(1);
  arL->Draw();


  //  if(iEcal_ == "EB" && iEcal_=="EE"){
  
  
  padDn->cd();

  TPad *padDn02 = new TPad("padDn02","padDn02",0.02, 0.02, 0.98, 0.25);
  padDn02->SetRightMargin(0.04);
  padDn02->SetLeftMargin(0.04);
  padDn02->SetTopMargin(0);
  padDn02->SetBottomMargin(0.2);
  padDn02->Draw();
  padDn02->cd();

  h_rtoMCqcd->Draw("ep");


  
  cv->cd();   

  
  cv->SaveAs(branch+"_"+iEcal_+".png");
} 


/////////////////////////////////////////////////////
TH1F* HistSQRT(TH1F* histsq,TString hname,TString htitle)
{
  //  hist_ = new TH1F(hitname_,hitname_,nwBins,xmin,xmax);
  TH1F* htmp = new TH1F(hname,htitle,nwBins,xmin,xmax);
  //  TH1F* htmp = new TH1F(hname,htitle,histsq->GetNbinsX(),
  //			histsq->GetXaxis()->GetXmin(),
  //			histsq->GetXaxis()->GetXmax()
  //			);
  //  Int_t min_ = histsq->GetXaxis()->GetXmin();
  //Int_t max_ = histsq->GetXaxis()->GetXmax();
  //Int_t nbin_ = histsq->GetNbinsX();
  //if(Debug) cout<<"HistSQRT min = "<<min_<<" max = "<<max_<<endl;
  
  //  for(Int_t i=min;i<max+1;i++)
  //  for(Int_t i=0;i<nbin_;i++)
  for(Int_t i=0;i<nwBins;i++)
    {
      Double_t BinCont = histsq->GetBinContent(i);
      htmp->SetBinContent(i,sqrt(BinCont));
    }
  return htmp;
}
/////////////////////////////////////////////////////
TH1F*   HistDrawSame(TH1F* histA_, TH1F* histB_){
  //  hist_ = new TH1F(hitname_,hitname_,nwBins,xmin,xmax);
  //  TH1F* hdsame = new TH1F("hdsame","drawsame",
  //			  histA_->GetNbinsX(),
  //			  histA_->GetXaxis()->GetXmin(),
  //			  histA_->GetXaxis()->GetXmax());

  TH1F* hdsame = new TH1F("hdsame","drawsame",nwBins,xmin,xmax);
			 
  hdsame->Add(histA_, histB_);
  return hdsame;
  
}

/////////////////////////////////////////////////////
TH1F*    HistRatio(TH1F* histA_, TH1F* histB_,TString name_){
  //  hist_ = new TH1F(hitname_,hitname_,nwBins,xmin,xmax);
  //  TH1F* hratio = new TH1F("hratio","ratio",
  //			  histA_->GetNbinsX(),
  //			  histA_->GetXaxis()->GetXmin(),
  //			  histA_->GetXaxis()->GetXmax());
  TH1F* hratio = new TH1F("hratio"+name_,"ratio"+name_,nwBins,xmin,xmax);
  hratio->Divide(histA_, histB_);
  return hratio;
}


Double_t CnvtCutBin(Double_t cut_,TH1F* hR){
  Int_t cutx;
  Double_t cutpoint;
  //  TH1F* hR = new TH1F("hR","test",nwBins,xmin,xmax);
  //for(unsigned int i =0; i<hR->GetXaxis()->GetMaximumBin();i++){
  //  cout<<"CnvtCutBin "<<hR->GetXaxis()->GetBinContent(i)<<endl;;
  //}
  for(Int_t i=0;i<nwBins;i++)
    {
      Double_t BinCont = hR->GetBinCenter(i);
      if(BinCont<cut_*1.1 && BinCont>cut_*0.9) cutx = i;
    }
  cutpoint = cutx/(nwBins*1.0);
  return cutpoint;
}


/////////////////////////////////////////////////////
Double_t getLumiW(TString Sname_){
  
  Double_t RealLumi = 1024.849;
  //Double_t RealLumi = 808.0;
  Double_t weight;
  
  Double_t LumiWeight_Ele_DYToEE_S10     	   = RealLumi*1*1915.08/3277040; 
  Double_t LumiWeight_Ele_DYJetsToLL_S10     = RealLumi*1*2950./28709500;
  Double_t LumiWeight_Ele_DYToTauTau_S10     = RealLumi*1*1581.419/9989370;
  Double_t LumiWeight_Ele_WToENu_S10         = RealLumi*1*12503.0/4383520;
  Double_t LumiWeight_Ele_WpToENu_S10        = RealLumi*1*7322.0/6554350;
  Double_t LumiWeight_Ele_WmToENu_S10        = RealLumi*1*5181.0/6553050;
  Double_t LumiWeight_Ele_WpToTauNu_S10      = RealLumi*1*7322.0/5880570;
  Double_t LumiWeight_Ele_WmToTauNu_S10      = RealLumi*1*5142.3/4601540;
  Double_t LumiWeight_Ele_WToTauNu_S10       = RealLumi*1*12503.0/5000740;
  Double_t LumiWeight_Ele_WJetsToLNu_S10     = RealLumi*1*30400./105000.;
  Double_t LumiWeight_Ele_TTJets_S10         = RealLumi*1*136.3/1364780.;
  Double_t LumiWeight_Ele_TT_CT10_S10        = RealLumi*1*225.197/2990940.;
  Double_t LumiWeight_Ele_QCD30to50_S10      = RealLumi*1*66285328./5800000.;
  Double_t LumiWeight_Ele_QCD50to80_S10      = RealLumi*1*8148778./5920350.;
  Double_t LumiWeight_Ele_QCD80to120_S10     = RealLumi*1*1033680./5994860.;
  Double_t LumiWeight_Ele_QCD120to170_S10    = RealLumi*1*156293.3/4744420.;
  Double_t LumiWeight_Ele_G_Pt50to80_S10     = RealLumi*1*3322.309/1995060.;
  
  if(Sname_ == "DYToEE")            { weight = LumiWeight_Ele_DYToEE_S10 ;}//
  else if(Sname_ == "DYJetsToLL")   { weight = LumiWeight_Ele_DYJetsToLL_S10  ;}
  else if(Sname_ == "DYToTauTau")   { weight = LumiWeight_Ele_DYToTauTau_S10  ;}
  else if(Sname_ == "WToENu")       { weight = LumiWeight_Ele_WToENu_S10      ;}
  else if(Sname_ == "WplusToENu")   { weight = LumiWeight_Ele_WpToENu_S10     ;}
  else if(Sname_ == "WminusToENu")  { weight = LumiWeight_Ele_WmToENu_S10     ;}
  else if(Sname_ == "WplusToTauNu") { weight = LumiWeight_Ele_WpToTauNu_S10   ;}
  else if(Sname_ == "WminusToTauNu"){ weight = LumiWeight_Ele_WmToTauNu_S10   ;}
  else if(Sname_ == "WToTauNu")     { weight = LumiWeight_Ele_WToTauNu_S10    ;}
  else if(Sname_ == "WJetsToLNu")   { weight = LumiWeight_Ele_WJetsToLNu_S10  ;}//
  else if(Sname_ == "TTJets_MassiveBinDECAY") { weight = LumiWeight_Ele_TTJets_S10      ;}
  else if(Sname_ == "TT_CT10")      { weight = LumiWeight_Ele_TT_CT10_S10     ;}
  else if(Sname_ == "QCD_pt30to50")    { weight = LumiWeight_Ele_QCD30to50_S10   ;}//
  else if(Sname_ == "QCD_pt50to80")    { weight = LumiWeight_Ele_QCD50to80_S10   ;}//
  else if(Sname_ == "QCD_pt80to120")   { weight = LumiWeight_Ele_QCD80to120_S10  ;}//
  else if(Sname_ == "QCD_pt120to170")  { weight = LumiWeight_Ele_QCD120to170_S10 ;}//
  else if(Sname_ == "G_Pt50to80")   { weight = LumiWeight_Ele_G_Pt50to80_S10  ;}
  else{ weight = 1.0;}

  return weight;

}

Color_t SmpClr(TString Sname_){

  Color_t index_color;

  if(Sname_ == "DYToEE")            { index_color = 7  ;}//
  else if(Sname_ == "DYJetsToLL")   { index_color = 7  ;}
  else if(Sname_ == "DYToTauTau")   { index_color = 7  ;}
  else if(Sname_ == "WToENu")       { index_color = 4  ;}
  else if(Sname_ == "WplusToENu")   { index_color = 2  ;}
  else if(Sname_ == "WminusToENu")  { index_color = 3  ;}
  else if(Sname_ == "WplusToTauNu") { index_color = 5  ;}
  else if(Sname_ == "WminusToTauNu"){ index_color = 5  ;}
  else if(Sname_ == "WToTauNu")     { index_color = 5  ;}
  else if(Sname_ == "WJetsToLNu")   { index_color = 5  ;}//
  else if(Sname_ == "TTJets_MassiveBinDECAY") { index_color = 28  ;}
  else if(Sname_ == "TT_CT10")      { index_color =  28 ;}
  else if(Sname_ == "QCD_pt30to50")    { index_color =  41 ;}//
  else if(Sname_ == "QCD_pt50to80")    { index_color =  41 ;}//
  else if(Sname_ == "QCD_pt80to120")   { index_color =  41 ;}//
  else if(Sname_ == "QCD_pt120to170")  { index_color =  41 ;}//
  else if(Sname_ == "G_Pt50to80")   { index_color =  8  ;}
  else if(Sname_ == "QCD")          { index_color =  41  ;}
  else if(Sname_ == "Others")       { index_color =  8  ;}
  else{ index_color = 1 ;}
  
  return index_color;
}

Double_t getCutValue(TString Vname_,TString iEcal_){
  Double_t cutvalue;
  cutvalue = 999;
  if(iEcal_=="EB"){
    if(Vname_ == "W_Lept1_pt")            { cutvalue = 30.0  ;}//
    //else if(Vname_ == "W_Lept1_et")   { cutvalue =   ;}
    //else if(Vname_ == "W_Lept1_eta")   { cutvalue =   ;}
    //else if(Vname_ == "W_Lept1_phi")   { cutvalue =   ;}
    //    else if(Vname_ == "W_Lept1_etaSC")   { cutvalue = 0.01;}
    //else if(Vname_ == "W_Lept1_phiSC")   { cutvalue =  0.06;}
    else if(Vname_ == "W_Lept1_dEtaIn")   { cutvalue = 0.004;}
    else if(Vname_ == "W_Lept1_dPhiIn")   { cutvalue = 0.06;}
    else if(Vname_ == "W_Lept1_sigmaIEtaIEta")   { cutvalue = 0.01;}
    else if(Vname_ == "W_Lept1_HoverE")   { cutvalue =  0.12;}
    //    else if(Vname_ == "W_Lept1_dxy")   { cutvalue =  0.02;}
    //    else if(Vname_ == "W_Lept1_AEff03")   { cutvalue =   ;}


  }

  else if(iEcal_=="EE"){
    if(Vname_ == "W_Lept1_pt")            { cutvalue = 30.0  ;}//
    //else if(Vname_ == "W_Lept1_et")   { cutvalue =   ;}
    //else if(Vname_ == "W_Lept1_eta")   { cutvalue =   ;}
    //else if(Vname_ == "W_Lept1_phi")   { cutvalue =   ;}
    //    else if(Vname_ == "W_Lept1_etaSC")   { cutvalue = 0.03;}
    //else if(Vname_ == "W_Lept1_phiSC")   { cutvalue =   ;}
    else if(Vname_ == "W_Lept1_dEtaIn")   { cutvalue =  0.007;}
    else if(Vname_ == "W_Lept1_dPhiIn")   { cutvalue = 0.03;}
    else if(Vname_ == "W_Lept1_sigmaIEtaIEta")   { cutvalue = 0.03;}
    else if(Vname_ == "W_Lept1_HoverE")   { cutvalue =  0.1;}
    //    else if(Vname_ == "W_Lept1_dxy")   { cutvalue =  0.02;}
    //    else if(Vname_ == "W_Lept1_AEff03")   { cutvalue =   ;}
    //    else if(Vname_ == "W_Lept1_dz")   { cutvalue =  0.1;}
    //    else if(Vname_ == "W_Lept1_InvEminusInvP")   { cutvalue =  0.05;}
  }
  else if (iEcal_=="EBEE"){
    if(Vname_ == "W_Lept1_dz")   { cutvalue = 0.1;}
    else if(Vname_ == "W_Lept1_dxy")   { cutvalue =  0.02;}
    else if(Vname_ == "W_Lept1_InvEminusInvP")   { cutvalue =  0.05;}
  }
  else{ cutvalue = 999;}

  return cutvalue;
}
