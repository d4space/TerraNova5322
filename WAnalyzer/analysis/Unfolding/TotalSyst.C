#include <TROOT.h>                        // access to gROOT, entry point to ROOT system
#include <TSystem.h>                      // interface to OS
#include <TStyle.h>                       // class to handle ROOT plotting styles
#include <TFile.h>                        // file handle class
#include <TTree.h>                        // class to access ntuples
#include <TBenchmark.h>                   // class to track macro running statistics
#include <TH1D.h>                         // histogram class
#include <vector>                         // STL vector class
#include <iostream>                       // standard I/O
#include <iomanip>                        // functions to format standard I/O
#include <fstream>                        // functions for file I/O
#include <string>                         // C++ string class
#include <sstream>                        // class for parsing strings
#include <TMath.h>


void TotalSyst(const TString filetype)
{
  if(filetype == "Mu")
  {
  //Nominal value and Statistic Error read
  TFile *f1 = new TFile("./EffSyst/Mu_EffSyst.root");
  f1->ls();
  TH1F *Wp_Nominal = (TH1F*)f1->Get("Wp_Nominal");
  TH1F *Wm_Nominal = (TH1F*)f1->Get("Wm_Nominal");
  TH1F *W_Nominal = (TH1F*)f1->Get("W_Nominal");
  
  TH1F *Wp_StatErr = (TH1F*)f1->Get("Wp_StatErr");
  TH1F *Wm_StatErr = (TH1F*)f1->Get("Wm_StatErr");
  TH1F *W_StatErr = (TH1F*)f1->Get("W_StatErr");
  
// Muon Systematics read 
  TH1F *Wp_Syst_Eff = (TH1F*)f1->Get("Wp_SystErr");
  TH1F *Wm_Syst_Eff = (TH1F*)f1->Get("Wm_SystErr");
  TH1F *W_Syst_Eff = (TH1F*)f1->Get("W_SystErr");

  TFile *f2 = new TFile("./RecoilSyst/Mu_RecoilSyst.root");
  f2->ls();
  TH1F *Wp_Syst_Recoil = (TH1F*)f2->Get("Wp_SystErr");
  TH1F *Wm_Syst_Recoil = (TH1F*)f2->Get("Wm_SystErr");
  TH1F *W_Syst_Recoil = (TH1F*)f2->Get("W_SystErr");

  TFile *f3 = new TFile("./SmearSyst/Mu_SmearSyst.root");
  f3->ls();
  TH1F *Wp_Syst_Smear = (TH1F*)f3->Get("Wp_SystErr");
  TH1F *Wm_Syst_Smear = (TH1F*)f3->Get("Wm_SystErr");
  TH1F *W_Syst_Smear = (TH1F*)f3->Get("W_SystErr");

  TFile *f4 = new TFile("./LumiSyst/Mu_LumiSyst.root");
  f4->ls();
  TH1F *Wp_Syst_Lumi = (TH1F*)f4->Get("Wp_SystErr");
  TH1F *Wm_Syst_Lumi = (TH1F*)f4->Get("Wm_SystErr");
  TH1F *W_Syst_Lumi = (TH1F*)f4->Get("W_SystErr");
  
  TFile *f5 = new TFile("./FSRSyst/Mu_FSRSyst.root");
  f5->ls();
  TH1F *Wp_Syst_FSR = (TH1F*)f5->Get("Wp_SystErr");
  TH1F *Wm_Syst_FSR = (TH1F*)f5->Get("Wm_SystErr");
  TH1F *W_Syst_FSR = (TH1F*)f5->Get("W_SystErr");
  }
  else if(filetype == "Ele")
  {
  //Nominal value and Statistic Error read
  TFile *f1 = new TFile("./EffSyst/Ele_EffSyst.root");
  f1->ls();
  TH1F *Wp_Nominal = (TH1F*)f1->Get("Wp_Nominal");
  TH1F *Wm_Nominal = (TH1F*)f1->Get("Wm_Nominal");
  TH1F *W_Nominal = (TH1F*)f1->Get("W_Nominal");
        
  TH1F *Wp_StatErr = (TH1F*)f1->Get("Wp_StatErr");
  TH1F *Wm_StatErr = (TH1F*)f1->Get("Wm_StatErr");
  TH1F *W_StatErr = (TH1F*)f1->Get("W_StatErr");
  
// Electron Systematics read 
  TH1F *Wp_Syst_Eff = (TH1F*)f1->Get("Wp_SystErr");
  TH1F *Wm_Syst_Eff = (TH1F*)f1->Get("Wm_SystErr");
  TH1F *W_Syst_Eff = (TH1F*)f1->Get("W_SystErr");

  TFile *f2 = new TFile("./RecoilSyst/Ele_RecoilSyst.root");
  f2->ls();
  TH1F *Wp_Syst_Recoil = (TH1F*)f2->Get("Wp_SystErr");
  TH1F *Wm_Syst_Recoil = (TH1F*)f2->Get("Wm_SystErr");
  TH1F *W_Syst_Recoil = (TH1F*)f2->Get("W_SystErr");

  TFile *f3 = new TFile("./ScaleSyst/Ele_ScaleSyst.root");
  f3->ls();
  TH1F *Wp_Syst_Scale = (TH1F*)f3->Get("Wp_SystErr");
  TH1F *Wm_Syst_Scale = (TH1F*)f3->Get("Wm_SystErr");
  TH1F *W_Syst_Scale = (TH1F*)f3->Get("W_SystErr");

  TFile *f4 = new TFile("./SmearSyst/Ele_SmearSyst.root");
  f4->ls();
  TH1F *Wp_Syst_Smear = (TH1F*)f4->Get("Wp_SystErr");
  TH1F *Wm_Syst_Smear = (TH1F*)f4->Get("Wm_SystErr");
  TH1F *W_Syst_Smear = (TH1F*)f4->Get("W_SystErr");

  TFile *f5 = new TFile("./LumiSyst/Ele_LumiSyst.root");
  f5->ls();
  TH1F *Wp_Syst_Lumi = (TH1F*)f5->Get("Wp_SystErr");
  TH1F *Wm_Syst_Lumi = (TH1F*)f5->Get("Wm_SystErr");
  TH1F *W_Syst_Lumi = (TH1F*)f5->Get("W_SystErr");
  
  TFile *f6 = new TFile("./FSRSyst/Ele_FSRSyst.root");
  f6->ls();
  TH1F *Wp_Syst_FSR = (TH1F*)f6->Get("Wp_SystErr");
  TH1F *Wm_Syst_FSR = (TH1F*)f6->Get("Wm_SystErr");
  TH1F *W_Syst_FSR = (TH1F*)f6->Get("W_SystErr");
  }

  double WptBins[14]={0,7.5,12.5,17.5,24,30,40,50,70,110,150,190,250,600};

  double Wp_Nom[13], Wm_Nom[13], W_Nom[13];
  double Wp_Stat[13], Wm_Stat[13], W_Stat[13];
  double Wp_Stat_per[13], Wm_Stat_per[13], W_Stat_per[13];
  
  double Eff_Wp[13], Eff_Wm[13], Eff_W[13];
  double Reco_Wp[13], Reco_Wm[13], Reco_W[13];
  double Scale_Wp[13], Scale_Wm[13], Scale_W[13];
  double Smear_Wp[13], Smear_Wm[13], Smear_W[13];
  double Lumi_Wp[13], Lumi_Wm[13], Lumi_W[13];
  double FSR_Wp[13], FSR_Wm[13], FSR_W[13];
  double Total_Wp[13], Total_Wm[13], Total_W[13];
  double Total_Wp_per[13], Total_Wm_per[13], Total_W_per[13];

  double Total_Uncer_Wp[13], Total_Uncer_Wm[13], Total_Uncer_W[13];

  int i=0;
  // make root file and histogram
  TFile *f_syst = new TFile(filetype+"_TotalSyst.root","recreate");

// W+ Histogram
  TH1F *Eff_Wp_SystErr = new TH1F("Eff_Wp_SystErr","Efficiency",13,WptBins);
  TH1F *Recoil_Wp_SystErr = new TH1F("Recoil_Wp_SystErr","Recoil",13,WptBins);
  if(filetype == "Ele")
  {
  TH1F *Scale_Wp_SystErr = new TH1F("Scale_Wp_SystErr","Scale",13,WptBins);
  }
  TH1F *Smear_Wp_SystErr = new TH1F("Smear_Wp_SystErr","Smear",13,WptBins);
  TH1F *Lumi_Wp_SystErr = new TH1F("Lumi_Wp_SystErr","Luminosity",13,WptBins);
  TH1F *FSR_Wp_SystErr = new TH1F("FSR_Wp_SystErr","FSR",13,WptBins);
// W- histogram
  TH1F *Eff_Wm_SystErr = new TH1F("Eff_Wm_SystErr","Efficiency",13,WptBins);
  TH1F *Recoil_Wm_SystErr = new TH1F("Recoil_Wm_SystErr","Recoil",13,WptBins);
  if(filetype == "Ele")
  {
  TH1F *Scale_Wm_SystErr = new TH1F("Scale_Wm_SystErr","Scale",13,WptBins);
  }
  TH1F *Smear_Wm_SystErr = new TH1F("Smear_Wm_SystErr","Smear",13,WptBins);
  TH1F *Lumi_Wm_SystErr = new TH1F("Lumi_Wm_SystErr","Luminosity",13,WptBins);
  TH1F *FSR_Wm_SystErr = new TH1F("FSR_Wm_SystErr","FSR",13,WptBins);
// Inclusive W histogram
  TH1F *Eff_W_SystErr = new TH1F("Eff_W_SystErr","Efficiency",13,WptBins);
  TH1F *Recoil_W_SystErr = new TH1F("Recoil_W_SystErr","Recoil",13,WptBins);
  if (filetype =="Ele")
  {
  TH1F *Scale_W_SystErr = new TH1F("Scale_W_SystErr","Scale",13,WptBins);
  }
  TH1F *Smear_W_SystErr = new TH1F("Smear_W_SystErr","Smear",13,WptBins);
  TH1F *Lumi_W_SystErr = new TH1F("Lumi_W_SystErr","Luminosity",13,WptBins);
  TH1F *FSR_W_SystErr = new TH1F("FSR_W_SystErr","FSR",13,WptBins);

// Total W histogram
  TH1F *Total_Wp_SystErr = new TH1F("Total_Wp_SystErr","Total_Wp_Systematics",13,WptBins);
  TH1F *Total_Wm_SystErr = new TH1F("Total_Wm_SystErr","Total_Wm_Systematics",13,WptBins);
  TH1F *Total_W_SystErr = new TH1F("Total_W_SystErr","Total_W_Systematics",13,WptBins);
cout<<fixed;
cout.precision(2);

//Systematic Calculation
  cout <<"======================================================="<<endl;
  cout <<"==========="<<filetype<<" Systematics  ===================="<<endl;
  cout <<"======================================================="<<endl;
  
  cout <<"============================================================="<<endl;
  cout <<"Bin"<<"\t"<<"W_Nom"<<"\t\t"<<"Wp_Nom" <<"\t\t" <<"Wm_Nom" <<endl;
  cout <<"============================================================="<<endl;
  for (i=1; i<=13; i++)
  {
    Wp_Nom[i-1] = fabs(Wp_Nominal->GetBinContent(i));
    Wm_Nom[i-1] = fabs(Wm_Nominal->GetBinContent(i));
    W_Nom[i-1] = fabs(W_Nominal->GetBinContent(i));

    Wp_Stat[i-1] = fabs(Wp_StatErr->GetBinError(i));
    Wm_Stat[i-1] = fabs(Wm_StatErr->GetBinError(i));
    W_Stat[i-1] = fabs(W_StatErr->GetBinError(i));

    cout << i << "\t" << W_Nom[i-1] <<"+-"<<W_Stat[i-1] << "\t\t"<<Wp_Nom[i-1] << "+-"<<Wp_Stat[i-1]<<"\t\t"<<Wm_Nom[i-1]<<"+-"<<Wm_Stat[i-1] <<endl;
  }
  
  cout <<"================================================================================================================================="<<endl;
  if (filetype == "Ele")
  {
  cout << "Bin"<<"\t"<<"Eff_Wp_syst"<<"\t"<<"Recoil_Wp_Syst" <<"\t"<<"Scale_Wp_Syst"<<"\t"<<"Smear_Wp_Syst" <<"\t" <<"Lumi_Wp_Syst" <<"\t"<<"FSR_Wp_Syst"<<endl;
  }
  else
  {
  cout <<"Bin" <<"\t"<<"Eff_Wp_syst"<<"\t"<<"Recoil_Wp_Syst" <<"\t"<<"Smear_Wp_Syst" <<"\t" <<"Lumi_Wp_Syst" <<"\t"<<"FSR_Wp_Syst"<<endl;
  }
  cout <<"================================================================================================================================="<<endl;
  for (i=1; i<=13;i++)
  {
    Eff_Wp[i-1] = fabs(Wp_Syst_Eff->GetBinError(i));
    Reco_Wp[i-1] = fabs(Wp_Syst_Recoil->GetBinError(i));
    if(filetype == "Ele")
    {
    Scale_Wp[i-1] = fabs(Wp_Syst_Scale->GetBinError(i));
    }
    Smear_Wp[i-1] = fabs(Wp_Syst_Smear->GetBinError(i));
    Lumi_Wp[i-1] = fabs(Wp_Syst_Lumi->GetBinError(i));
    FSR_Wp[i-1] = fabs(Wp_Syst_FSR->GetBinError(i));
   
    if (filetype == "Ele")
    {
    cout << i<<"\t"<<Eff_Wp[i-1] <<"\t\t" << Reco_Wp[i-1] <<"\t\t"<<Scale_Wp[i-1]<<"\t\t"<<Smear_Wp[i-1] << "\t\t" << Lumi_Wp[i-1]<<"\t\t"<<FSR_Wp[i-1]<<endl;
    }
    else 
    {
    cout << i<<"\t"<< Eff_Wp[i-1] <<"\t\t" << Reco_Wp[i-1] <<"\t\t"<<Smear_Wp[i-1] << "\t\t" << Lumi_Wp[i-1]<<"\t\t"<<FSR_Wp[i-1]<<endl;
    }
  }

  cout <<"================================================================================================================================="<<endl;
  if (filetype =="Ele")
  {
  cout << "Bin"<<"\t"<<"Eff_Wm_syst"<<"\t"<<"Recoil_Wm_Syst" <<"\t"<<"Scale_Wm_Syst"<<"\t"<<"Smear_Wm_Syst" <<"\t" <<"Lumi_Wm_Syst" <<"\t"<<"FSR_Wm_Syst"<<endl;
  }
  else
  {
  cout << "Bin"<<"\t"<<"Eff_Wm_syst"<<"\t"<<"Recoil_Wm_Syst" <<"\t"<<"Smear_Wm_Syst" <<"\t" <<"Lumi_Wm_Syst" <<"\t"<<"FSR_Wm_Syst"<<endl;
  }
  cout <<"================================================================================================================================="<<endl;
  for (i=1; i<=13;i++)
  {
    Eff_Wm[i-1] = fabs(Wm_Syst_Eff->GetBinError(i));
    Reco_Wm[i-1] = fabs(Wm_Syst_Recoil->GetBinError(i));
    if (filetype == "Ele")
    {
    Scale_Wm[i-1] = fabs(Wm_Syst_Scale->GetBinError(i));
    }
    Smear_Wm[i-1] = fabs(Wm_Syst_Smear->GetBinError(i));
    Lumi_Wm[i-1] = fabs(Wm_Syst_Lumi->GetBinError(i));
    FSR_Wm[i-1] = fabs(Wm_Syst_FSR->GetBinError(i));

    if (filetype =="Ele")
    {
    cout << i<<"\t"<< Eff_Wm[i-1] <<"\t\t" << Reco_Wm[i-1] <<"\t\t"<<Scale_Wm[i-1]<<"\t\t"<<Smear_Wm[i-1] << "\t\t" << Lumi_Wm[i-1]<<"\t\t"<<FSR_Wm[i-1]<<endl;
    }
    else
    {
    cout << i<<"\t"<< Eff_Wm[i-1] <<"\t\t" << Reco_Wm[i-1] <<"\t\t"<<Smear_Wm[i-1] << "\t\t" << Lumi_Wm[i-1]<<"\t\t"<<FSR_Wm[i-1]<<endl;
    }
  }

  cout <<"================================================================================================================================="<<endl;
    if (filetype =="Ele")
    {
  cout << "Bin"<<"\t"<<"Eff_W_syst"<<"\t"<<"Recoil_W_Syst" <<"\t"<<"Scale_W_Syst"<<"\t" <<"Smear_W_Syst" <<"\t" <<"Lumi_W_Syst" <<"\t"<<"FSR_W_Syst"<<endl;
    }
    else
    {
    cout << "Bin"<<"\t"<<"Eff_W_syst"<<"\t"<<"Recoil_W_Syst" <<"\t" <<"Smear_W_Syst" <<"\t" <<"Lumi_W_Syst" <<"\t"<<"FSR_W_Syst"<<endl;
    }
  cout <<"================================================================================================================================="<<endl;
  for (i=1; i<=13;i++)
  {
    Eff_W[i-1] = fabs(W_Syst_Eff->GetBinError(i));
    Reco_W[i-1] = fabs(W_Syst_Recoil->GetBinError(i));
    if (filetype =="Ele")
    {
    Scale_W[i-1] = fabs(W_Syst_Scale->GetBinError(i));
    }
    Smear_W[i-1] = fabs(W_Syst_Smear->GetBinError(i));
    Lumi_W[i-1] = fabs(W_Syst_Lumi->GetBinError(i));
    FSR_W[i-1] = fabs(W_Syst_FSR->GetBinError(i));

    if (filetype =="Ele")
    {
    cout << i<<"\t"<< Eff_W[i-1] <<"\t\t" << Reco_W[i-1] <<"\t\t"<<Scale_W[i-1]<<"\t\t"<<Smear_W[i-1] << "\t\t" << Lumi_W[i-1]<<"\t\t"<<FSR_W[i-1]<<endl;
    }
    else
    {
    cout << i<<"\t"<< Eff_W[i-1] <<"\t\t" << Reco_W[i-1] <<"\t\t"<<Smear_W[i-1] << "\t\t" << Lumi_W[i-1]<<"\t\t"<<FSR_W[i-1]<<endl;
    }
  }


  ofstream Fout;
  Fout<<fixed;
  Fout.precision(2);
  Fout.open(filetype + "_TotalSyst.txt");

  Fout <<"======================================================================================================="<<endl;
  Fout <<"Bin"<<"\t"<< "Total_Syst_W" << "\t\t" << "Total_Syst_Wp" <<"\t\t" << "Total_Syst_Wm" <<"\t\t"<< "StatErr_W"<<"\t"<<"StatErr_Wp"<<"\t"<<"StatErr_Wm" <<endl;
  Fout <<"======================================================================================================="<<endl;
  cout <<"======================================================================================================="<<endl;
  cout <<"Bin"<<"\t"<< "Total_Syst_W" << "\t\t" << "Total_Syst_Wp" <<"\t\t" << "Total_Syst_Wm" <<"\t\t"<< "StatErr_W"<<"\t"<<"StatErr_Wp"<<"\t"<<"StatErr_Wm"  <<endl;
  cout <<"======================================================================================================="<<endl;
    for(i=1;i<=13;i++)
    {
    // calculate Total Systematics 
  //  Total_Wp[i-1] = TMath::Sqrt(Scale_Wp[i-1]*Scale_Wp[i-1]+Smear_Wp[i-1]*Smear_Wp[i-1]);
    //Total_Wp[i-1] = TMath::Sqrt(Eff_Wp[i-1]*Eff_Wp[i-1]+Reco_Wp[i-1]*Reco_Wp[i-1]+Scale_Wp[i-1]*Scale_Wp[i-1]+Smear_Wp[i-1]*Smear_Wp[i-1]+FSR_Wp[i-1]*FSR_Wp[i-1]);

      if (filetype =="Ele")
      {
      Total_Wp[i-1] = TMath::Sqrt(Eff_Wp[i-1]*Eff_Wp[i-1]+Reco_Wp[i-1]*Reco_Wp[i-1]+Scale_Wp[i-1]*Scale_Wp[i-1]+Smear_Wp[i-1]*Smear_Wp[i-1]+Lumi_Wp[i-1]*Lumi_Wp[i-1]+FSR_Wp[i-1]*FSR_Wp[i-1]);
      }
      else
      {
      Total_Wp[i-1] = TMath::Sqrt(Eff_Wp[i-1]*Eff_Wp[i-1]+Reco_Wp[i-1]*Reco_Wp[i-1]+Smear_Wp[i-1]*Smear_Wp[i-1]+Lumi_Wp[i-1]*Lumi_Wp[i-1]+FSR_Wp[i-1]*FSR_Wp[i-1]);
      }

//    Total_Wm[i-1] = TMath::Sqrt(Scale_Wm[i-1]*Scale_Wm[i-1]+Smear_Wm[i-1]*Smear_Wm[i-1]);
  //  Total_Wm[i-1] = TMath::Sqrt(Eff_Wm[i-1]*Eff_Wm[i-1]+Reco_Wm[i-1]*Reco_Wm[i-1]+Scale_Wm[i-1]*Scale_Wm[i-1]+Smear_Wm[i-1]*Smear_Wm[i-1]+FSR_Wm[i-1]*FSR_Wm[i-1]);
 
      if (filetype =="Ele")
      {
      Total_Wm[i-1] = TMath::Sqrt(Eff_Wm[i-1]*Eff_Wm[i-1]+Reco_Wm[i-1]*Reco_Wm[i-1]+Scale_Wm[i-1]*Scale_Wm[i-1]+Smear_Wm[i-1]*Smear_Wm[i-1]+Lumi_Wm[i-1]*Lumi_Wm[i-1]+FSR_Wm[i-1]*FSR_Wm[i-1]);
      }
      else
      {
      Total_Wm[i-1] = TMath::Sqrt(Eff_Wm[i-1]*Eff_Wm[i-1]+Reco_Wm[i-1]*Reco_Wm[i-1]+Smear_Wm[i-1]*Smear_Wm[i-1]+Lumi_Wm[i-1]*Lumi_Wm[i-1]+FSR_Wm[i-1]*FSR_Wm[i-1]);
      }

//    Total_W[i-1] = TMath::Sqrt(Scale_W[i-1]*Scale_W[i-1]+Smear_W[i-1]*Smear_W[i-1]);
 //   Total_W[i-1] = TMath::Sqrt(Eff_W[i-1]*Eff_W[i-1]+Reco_W[i-1]*Reco_W[i-1]+Scale_W[i-1]*Scale_W[i-1]+Smear_W[i-1]*Smear_W[i-1]+FSR_W[i-1]*FSR_W[i-1]);

      if (filetype =="Ele")
      {
      Total_W[i-1] = TMath::Sqrt(Eff_W[i-1]*Eff_W[i-1]+Reco_W[i-1]*Reco_W[i-1]+Scale_W[i-1]*Scale_W[i-1]+Smear_W[i-1]*Smear_W[i-1]+Lumi_W[i-1]*Lumi_W[i-1]+FSR_W[i-1]*FSR_W[i-1]);
      }
      else
      {
      Total_W[i-1] = TMath::Sqrt(Eff_W[i-1]*Eff_W[i-1]+Reco_W[i-1]*Reco_W[i-1]+Smear_W[i-1]*Smear_W[i-1]+Lumi_W[i-1]*Lumi_W[i-1]+FSR_W[i-1]*FSR_W[i-1]);
      }
    
    Total_Wp_per[i-1] = Total_Wp[i-1]/Wp_Nom[i-1] * 100;
    Total_Wm_per[i-1] = Total_Wm[i-1]/Wm_Nom[i-1] * 100;
    Total_W_per[i-1] = Total_W[i-1]/W_Nom[i-1] * 100;

    Wp_Stat_per[i-1] = Wp_Stat[i-1]/Wp_Nom[i-1] * 100;
    Wm_Stat_per[i-1] = Wm_Stat[i-1]/Wm_Nom[i-1] * 100;
    W_Stat_per[i-1] = W_Stat[i-1]/W_Nom[i-1] * 100;

    
    cout << i<<"\t"<< Total_W[i-1]<<"("<<Total_W_per[i-1]<<")"
      <<"\t\t" << Total_Wp[i-1] <<"("<<Total_Wp_per[i-1]<<")"
      <<"\t\t" << Total_Wm[i-1]<<"("<<Total_Wm_per[i-1]<<")"<< "\t\t"<<W_Stat_per[i-1]<<"\t\t"<<Wp_Stat_per[i-1]<<"\t\t"<<Wm_Stat_per[i-1]<< endl;
    Fout << i<<"\t"<< Total_W[i-1]<<"("<<Total_W_per[i-1]<<")"
      <<"\t\t" << Total_Wp[i-1] <<"("<<Total_Wp_per[i-1]<<")"
      <<"\t\t" << Total_Wm[i-1]<<"("<<Total_Wm_per[i-1]<<")"<< "\t\t"<<W_Stat_per[i-1]<<"\t\t"<<Wp_Stat_per[i-1]<<"\t\t"<<Wm_Stat_per[i-1] <<endl;
    

  // set histogram inclusive W
  Total_Wp_SystErr->SetBinError(i,Total_Wp[i-1]);
  Total_Wm_SystErr->SetBinError(i,Total_Wm[i-1]);
  Total_W_SystErr->SetBinError(i,Total_W[i-1]);
  }
  Fout <<"============================================================="<<endl;
  Fout <<"Bin"<<"\t"<< "Total_Uncer_W" << "\t" << "Total_Uncer_Wp" <<"\t" << "Total_Uncer_Wm" <<endl;
  Fout <<"============================================================="<<endl;
  cout <<"============================================================="<<endl;
  cout <<"Bin"<<"\t"<< "Total_Uncer_W" << "\t" << "Total_Uncer_Wp" <<"\t" << "Total_Uncer_Wm" <<endl;
  cout <<"============================================================="<<endl;
    for (i=1;i<=13;i++)
    {
      Total_Uncer_Wp[i-1] = Total_Wp_per[i-1] + Wp_Stat_per[i-1];
      Total_Uncer_Wm[i-1] = Total_Wm_per[i-1] + Wm_Stat_per[i-1];
      Total_Uncer_W[i-1] = Total_W_per[i-1] + W_Stat_per[i-1];

      cout << i <<"\t"<<Total_Uncer_W[i-1]<<"\t\t" << Total_Uncer_Wp[i-1] << "\t\t" << Total_Uncer_Wm[i-1] << endl; 
      Fout << i <<"\t"<<Total_Uncer_W[i-1]<<"\t\t" << Total_Uncer_Wp[i-1] << "\t\t" << Total_Uncer_Wm[i-1] << endl; 

    }
  Total_Wp_SystErr->Write();
  Total_Wm_SystErr->Write();
  Total_W_SystErr->Write();
  
  Fout.close();
}
