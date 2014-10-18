#include "TStyle.h"
#include "../BaseDir/Utils/const.h"
#include "../BaseDir/Utils/CPlot.hh"
#include "../BaseDir/Utils/MitStyleRemix.hh"
#include <fstream>
#include <iostream>
#include <iomanip>
#include "TROOT.h"
#include "TSystem.h"
#include "TString.h"
#include "TH1D.h"
//#include "TFile.h"

int mRead_Yield(TString CorrName) { 
  const Int_t NumOfSamples = 500;
  //const Int_t NumOfSamples = 899;
  //const Int_t NWptBinPlus  = 14;

  cout << "Correction Name : "<< CorrName << endl;
  TH1D *hSigWMpt[NumOfSamples+1];
  double AllBins[13] = {0};

  double WptBins[NWptBinPlus]; WptBins[0] = 0; WptBins[1] = 7.5; WptBins[2] =
    12.5; WptBins[3] = 17.5; WptBins[4] = 24; WptBins[5] = 30; WptBins[6] = 40;
  WptBins[7] = 50; WptBins[8] = 70; WptBins[9] = 110; WptBins[10]= 150;
  WptBins[11]= 190; WptBins[12]= 250; WptBins[13]= 600;

  char tmpName[30]; char histName[30]; TString tmpTStr;
  
  ofstream allyields; allyields.open("mYields.txt");

  TFile *fname[NumOfSamples];

  for(int i(1);i<=NumOfSamples;i++) {
    if (CorrName == "EffCorr" || CorrName == "ScaleCorr" || CorrName == "SmearCorr" || CorrName == "RecoilCorr")
    {
      sprintf(tmpName,"../EventSelection%d/MuonFitResultsRayleighGausSimultNominal/RstMuon/SigYields_Nominal.root",i);
    }
    else
    {
      sprintf(tmpName,"../EventSelection%d/ResultWmToMuNu/Result_WmToMuNu.root",i);
    }
    fname[i] = new TFile(tmpName);
    
    sprintf(histName,"hSigWMpt_%d",i);
    if (CorrName == "EffCorr" || CorrName == "ScaleCorr" || CorrName == "SmearCorr" || CorrName == "RecoilCorr")
    {
      sprintf(tmpName,"hSigWMpt");
      TFile *f_Out = new TFile("mRecon.root","recreate");
    }
    else if (CorrName == "dUnf")
    {
      sprintf(tmpName,"DetUnf");
      TFile *f_Out = new TFile("mDetUnf.root","recreate");
    }
    else if (CorrName == "PostEffCorr")
    {
      sprintf(tmpName,"PostEffCorr");
      TFile *f_Out = new TFile("mPostEffCorr.root","recreate");
    }
    else if (CorrName == "FSRUnf")
    {
      sprintf(tmpName,"FSRUnf");
      TFile *f_Out = new TFile("mFSRUnf.root","recreate");
    }
    else if (CorrName == "BornEffCorr")
    {
      sprintf(tmpName,"BornEffCorr");
      TFile *f_Out = new TFile("mBornEffCorr.root","recreate");
    }
    hSigWMpt[i] = (TH1D*)fname[i]->Get(tmpName)->Clone(histName);
   // hSigWMpt[i]->Sumw2();
  }
  
  int i1=0;
  int i2=0;
  int i3=0;
  int i4=0;
  int i5=0;
  int i6=0;
  int i7=0;
  int i8=0;
  int i9=0;
  int i10=0;
  int i11=0;
  int i12=0;
  int i13=0;
  //  ,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13;
  double cl1  = 7541.4806*(1.-0.03); 
  double cl2  = 7884.0170*(1.-0.03);
  double cl3  = 6159.2862*(1.-0.03);
  double cl4  = 5479.4870*(1.-0.03);
  double cl5  = 3206.4435*(1.-0.03);
  double cl6  = 3094.3380*(1.-0.03);
  double cl7  = 1642.8998*(1.-0.03);
  double cl8  = 1661.4630*(1.-0.03);
  double cl9  = 1007.2194*(1.-0.03);
  double cl10 = 242.1957 *(1.-0.03); 
  double cl11 = 71.4520  *(1.-0.03); 
  double cl12 = 39.5064  *(1.-0.03); 
  double cl13 = 9.8633   *(1.-0.03); 
                         
  double ch1  = 7541.4806*(1.+0.03);
  double ch2  = 7884.0170*(1.+0.03);
  double ch3  = 6159.2862*(1.+0.03);
  double ch4  = 5479.4870*(1.+0.03);
  double ch5  = 3206.4435*(1.+0.03);
  double ch6  = 3094.3380*(1.+0.03);
  double ch7  = 1642.8998*(1.+0.03);
  double ch8  = 1661.4630*(1.+0.03);
  double ch9  = 1007.2194*(1.+0.03);
  double ch10 = 242.1957 *(1.+0.03);
  double ch11 = 71.4520  *(1.+0.03);
  double ch12 = 39.5064  *(1.+0.03);
  double ch13 = 9.8633   *(1.+0.03);

  for(int i(1);i<=NumOfSamples;i++)
  {
    allyields<<"=================== "<<i<<" ==================="<<endl;
    for(int ipt(1);ipt<NWptBinPlus;ipt++)
    {
      allyields<<ipt<<"\t"<<hSigWMpt[i]->GetBinContent(ipt)<<"\t"<<hSigWMpt[i]->GetBinError(ipt)<<endl;
      AllBins[ipt-1] += hSigWMpt[i]->GetBinContent(ipt);
    }
    if (hSigWMpt[i]->GetBinContent(1) <cl1 || hSigWMpt[i]->GetBinContent(1) >ch1 ) {i1++; cout<<"rm -f SigYields_"<<i<<".root"<<endl;} 
    if (hSigWMpt[i]->GetBinContent(2) <cl2 || hSigWMpt[i]->GetBinContent(2) >ch2 ) {i2++; cout<<"rm -f SigYields_"<<i<<".root"<<endl;}
    if (hSigWMpt[i]->GetBinContent(3) <cl3 || hSigWMpt[i]->GetBinContent(3) >ch3 ) {i3++; cout<<"rm -f SigYields_"<<i<<".root"<<endl;}
    if (hSigWMpt[i]->GetBinContent(4) <cl4 || hSigWMpt[i]->GetBinContent(4) >ch4 ) {i4++; cout<<"rm -f SigYields_"<<i<<".root"<<endl;}
    if (hSigWMpt[i]->GetBinContent(5) <cl5 || hSigWMpt[i]->GetBinContent(5) >ch5 ) {i5++; cout<<"rm -f SigYields_"<<i<<".root"<<endl;}
    if (hSigWMpt[i]->GetBinContent(6) <cl6 || hSigWMpt[i]->GetBinContent(6) >ch6 ) {i6++; cout<<"rm -f SigYields_"<<i<<".root"<<endl;}
    if (hSigWMpt[i]->GetBinContent(7) <cl7 || hSigWMpt[i]->GetBinContent(7) >ch7 ) {i7++; cout<<"rm -f SigYields_"<<i<<".root"<<endl;}
    if (hSigWMpt[i]->GetBinContent(8) <cl8 || hSigWMpt[i]->GetBinContent(8) >ch8 ) {i8++; cout<<"rm -f SigYields_"<<i<<".root"<<endl;}
    if (hSigWMpt[i]->GetBinContent(9) <cl9 || hSigWMpt[i]->GetBinContent(9) >ch9 ) {i9++; cout<<"rm -f SigYields_"<<i<<".root"<<endl;}
    if (hSigWMpt[i]->GetBinContent(10)<cl10|| hSigWMpt[i]->GetBinContent(10)>ch10) {i10++;cout<<"rm -f SigYields_"<<i<<".root"<<endl;}
    if (hSigWMpt[i]->GetBinContent(11)<cl11|| hSigWMpt[i]->GetBinContent(11)>ch11) {i11++;cout<<"rm -f SigYields_"<<i<<".root"<<endl;}
    if (hSigWMpt[i]->GetBinContent(12)<cl12|| hSigWMpt[i]->GetBinContent(12)>ch12) {i12++;cout<<"rm -f SigYields_"<<i<<".root"<<endl;}
    if (hSigWMpt[i]->GetBinContent(13)<cl13|| hSigWMpt[i]->GetBinContent(13)>ch13) {i13++;cout<<"rm -f SigYields_"<<i<<".root"<<endl;}

    hSigWMpt[i]->Write();
  }

  for(int i(1);i<NWptBinPlus;i++)
  {
    sprintf(histName,"i%d",i);
    cout<<"Bin "<<i<<" = "<<AllBins[i-1]/NumOfSamples<<endl;
  }
  cout <<i1<<"\t"<<i2<<"\t"<<i3<<"\t"<<i4<<"\t"<<i5<<"\t"<<i6<<"\t"<<i7<<"\t"<<i8<<"\t"<<i9<<"\t"<<i10<<"\t"<<i11<<"\t"<<i12<<"\t"<<i13<<endl;
  //cout <<i8<<endl;

  return 0;
}
