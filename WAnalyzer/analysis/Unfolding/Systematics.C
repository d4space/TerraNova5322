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

#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Utils/const.h"
#include "../Utils/MyTools.hh"
#include "../Utils/CPlot.hh"
#include "../Utils/MitStyleRemix.hh"

void Systematics(const TString filetype)
{
  enum {eNomP, eUpP, eDownP,eNomM, eUpM, eDownM};
  vector<TString> fnamev;
  vector<Int_t>   typev;
  
  TH1D *hNomP;
  TH1D *hNomM;
  TH1D *hUpP;
  TH1D *hUpM;
  TH1D *hDownP;
  TH1D *hDownM;

  if (filetype == "Mu")
  {
    fnamev.push_back("./ResultWpToMuNuNom/Result_WpToMuNu.root"); typev.push_back(eNomP);
    fnamev.push_back("./ResultWpToMuNuUp/Result_WpToMuNu.root"); typev.push_back(eUpP);
//    fnamev.push_back("./ResultWpToMuNuDown/Result_WpToMuNu.root"); typev.push_back(eDownP);
    fnamev.push_back("./ResultWmToMuNuNom/Result_WmToMuNu.root"); typev.push_back(eNomM);
    fnamev.push_back("./ResultWmToMuNuUp/Result_WmToMuNu.root"); typev.push_back(eUpM);
//    fnamev.push_back("./ResultWmToMuNuDown/Result_WmToMuNu.root"); typev.push_back(eDownM);
  }
  else if (filetype == "Ele")
  {
    fnamev.push_back("./ResultWpToEleNuNom/Result_WpToEleNu.root"); typev.push_back(eNomP);
    fnamev.push_back("./ResultWpToEleNuUp/Result_WpToEleNu.root"); typev.push_back(eUpP);
//    fnamev.push_back("./ResultWpToEleNuDown/Result_WpToEleNu.root"); typev.push_back(eDownP);
    fnamev.push_back("./ResultWmToEleNuNom/Result_WmToEleNu.root"); typev.push_back(eNomM);
    fnamev.push_back("./ResultWmToEleNuUp/Result_WmToEleNu.root"); typev.push_back(eUpM);
//    fnamev.push_back("./ResultWmToEleNuDown/Result_WmToEleNu.root"); typev.push_back(eDownM);
  }
  
  TFile *infile=0;
  cout << "Looping Files ------------------------"<<endl;
  char histName[30],histName_org[30];
  for(UInt_t ifile=0; ifile<fnamev.size(); ifile++) {
    cout << "Processing " << fnamev[ifile] << "..." << endl;
    infile = new TFile(fnamev[ifile]);    assert(infile);
    if(typev[ifile]==eNomP)
    {
      sprintf(histName,"hNomP");
      sprintf(histName_org,"BornEffCorr");
      hNomP = (TH1D*)infile->Get(histName_org)->Clone(histName);
    }
    if(typev[ifile]==eUpP)
    {
      sprintf(histName,"hUpP");
      sprintf(histName_org,"BornEffCorr");
      hUpP = (TH1D*)infile->Get(histName_org)->Clone(histName);
    }
    if(typev[ifile]==eDownP)
    {
      sprintf(histName,"hDownP");
      sprintf(histName_org,"BornEffCorr");
      hDownP = (TH1D*)infile->Get(histName_org)->Clone(histName);
    }
    if(typev[ifile]==eNomM)
    {
      sprintf(histName,"hNomM");
      sprintf(histName_org,"BornEffCorr");
      hNomM = (TH1D*)infile->Get(histName_org)->Clone(histName);
    }
    if(typev[ifile]==eUpM)
    {
      sprintf(histName,"hUpM");
      sprintf(histName_org,"BornEffCorr");
      hUpM = (TH1D*)infile->Get(histName_org)->Clone(histName);
    }
    if(typev[ifile]==eDownM)
    {
      sprintf(histName,"hDownM");
      sprintf(histName_org,"BornEffCorr");
      hDownM = (TH1D*)infile->Get(histName_org)->Clone(histName);
    }
  }
  
  double NomValP[13];
  double NomValM[13];
  double NomValI[13];  // for inclusive W

  double UpValP[13];
  double UpValM[13];

  double DownValP[13];
  double DownValM[13];

  double ErrP[13];
  double ErrM[13];
  double ErrI[13]; // for inclusive W

  double Ap[13];
  double Am[13];
  double Bp[13];
  double Bm[13];

  double SystUncerP[13];
  double SystUncerM[13];
  double SystUncerI[13];  // for inclusive W
  
  double Bins[14];
  Bins[0]= 0;
  Bins[1]= 7.5;
  Bins[2]= 12.5;
  Bins[3]= 17.5;
  Bins[4]= 24;
  Bins[5]= 30;
  Bins[6]= 40;
  Bins[7]= 50;
  Bins[8]= 70;
  Bins[9]= 110;
  Bins[10]=150;
  Bins[11]=190;
  Bins[12]=250;
  Bins[13]=600;
  
  char uncertp[50];
  char uncertm[50];
  char uncerti[50]; // for inclusive W

  ofstream htmlfile;
  char htmlfname[100];
  sprintf(htmlfname,filetype+"_RecoilSyst.html");
  htmlfile.open(htmlfname);
  htmlfile << "<!DOCTYPE html" << endl;
  htmlfile << "    PUBLIC \"-//W3C//DTD HTML 3.2//EN\">" << endl;
  htmlfile << "<html>" << endl;
  htmlfile << "<head><title>Systematic uncertainties</title></head>" << endl;
  htmlfile << "<body bgcolor=\"white\">" << endl;
  htmlfile << "<hr />" << endl;
  htmlfile << "<p align=\"center\"> Systematic uncertainties from Recoil Correction  </p>" << endl;
  htmlfile << "<hr />" << endl;
  htmlfile << "<table border=\"1\" style=\"border-collapse: collapse\" bordercolor=\"black\" cellspacing=\"3\" width=\"1200\" align=\"center\">" << endl;
  htmlfile << "<tr>" << endl;
  htmlfile << "<td width=\"120\"><p align=\"center\"> W p<sub>T</sub> Bins </p></td>" << endl;
  htmlfile << "<td width=\"500\"><p align=\"center\"> W <sup>+</sup></p></td>" << endl;
  htmlfile << "<td width=\"500\"><p align=\"center\"> W <sup>-</sup></p></td>" << endl;
  htmlfile << "<td width=\"500\"><p align=\"center\"> W <sup></sup></p></td>" << endl;
  htmlfile << "</tr>" << endl;
  
  ofstream rcsyst;
  rcsyst.open(filetype+"_RecoilSyst.txt");
  rcsyst << fixed << setprecision(6);

    rcsyst << "BIN" <<"\t"<< "SystUncerP" << "\t" << "SystUncerM" << "\t" << "SystUncerI" << endl;
  for(int ipt(1);ipt<NWptBinPlus;ipt++)
  {
    NomValP[ipt] = hNomP->GetBinContent(ipt);
    NomValM[ipt] = hNomM->GetBinContent(ipt);
    NomValI[ipt] = NomValP[ipt] + NomValM[ipt];  // for inclusive W 
    UpValP[ipt] = hUpP->GetBinContent(ipt);
    UpValM[ipt] = hUpM->GetBinContent(ipt);
//    DownValP[ipt] = hDownP->GetBinContent(ipt);
//    DownValM[ipt] = hDownM->GetBinContent(ipt);
    ErrP[ipt] = hNomP->GetBinError(ipt);
    ErrM[ipt] = hNomM->GetBinError(ipt);
    ErrI[ipt] = TMath::Sqrt((ErrP[ipt]*ErrP[ipt])+(ErrM[ipt]*ErrM[ipt])); // for inclusive W

    Ap[ipt] = NomValP[ipt] - UpValP[ipt];
    Am[ipt] = NomValM[ipt] - UpValM[ipt];
//    Bp[ipt] = NomValP[ipt] - DownValP[ipt];
//    Bm[ipt] = NomValM[ipt] - DownValM[ipt];

    SystUncerP[ipt] = fabs(Ap[ipt]);
    SystUncerM[ipt] = fabs(Am[ipt]);
//    SystUncerP[ipt] = TMath::Max(fabs(Ap[ipt]),fabs(Bp[ipt]));
//    SystUncerM[ipt] = TMath::Max(fabs(Am[ipt]),fabs(Bm[ipt]));
    SystUncerI[ipt] = TMath::Sqrt((SystUncerP[ipt]*SystUncerP[ipt])+(SystUncerM[ipt]*SystUncerM[ipt])); // for inclusive W
    rcsyst <<ipt << "\t" << SystUncerP[ipt] << "\t" << SystUncerM[ipt] << "\t" << SystUncerI[ipt]<< endl;
    
    sprintf(uncertp,"%.1f &plusmn; %.1f (%.2f \%) &plusmn; %.1f (%.2f \%)", NomValP[ipt],ErrP[ipt],ErrP[ipt]/NomValP[ipt]*100,SystUncerP[ipt],SystUncerP[ipt]/NomValP[ipt]*100);
    sprintf(uncertm,"%.1f &plusmn; %.1f (%.2f \%) &plusmn; %.1f (%.2f \%)", NomValM[ipt],ErrM[ipt],ErrM[ipt]/NomValM[ipt]*100,SystUncerM[ipt],SystUncerM[ipt]/NomValM[ipt]*100);
    sprintf(uncerti,"%.1f &plusmn; %.1f (%.2f \%) &plusmn; %.1f (%.2f \%)", NomValI[ipt],ErrI[ipt],ErrI[ipt]/NomValI[ipt]*100,SystUncerI[ipt],SystUncerI[ipt]/NomValI[ipt]*100);
    
    htmlfile << "<tr>" << endl; 
    htmlfile << "<td width=\"120\"><p>[" << Bins[ipt-1] << ", " << Bins[ipt] << "] </p></td>" << endl;
    htmlfile << "<td width=\"500\"><p>" << uncertp << "</p></td>" << endl;
    htmlfile << "<td width=\"500\"><p>" << uncertm << "</p></td>" << endl;
    htmlfile << "<td width=\"500\"><p>" << uncerti << "</p></td>" << endl;
    htmlfile << "</tr>" << endl;
  }
  htmlfile << "</table>" << endl;
  htmlfile << "<hr />" << endl;
  htmlfile << "</body>" << endl;
  htmlfile << "</html>" << endl;
  htmlfile.close();
  rcsyst.close();

// create root file
  TFile *f_syst = new TFile(filetype+"_RecoilSyst.root","recreate");

// W+ histogram
  TH1D *Wp_Nominal = new TH1D("Wp_Nominal","Wp_Nominal",13,Bins);
  TH1D *Wp_StatErr = new TH1D("Wp_StatErr","Wp_StatErr",13,Bins);
  TH1D *Wp_SystErr = new TH1D("Wp_SystErr","Wp_SystErr",13,Bins);
  TH1D *Wp_SysErr_per = new TH1D("Wp_SystErr_per","Wp_SystErr_per",13,Bins);

// W+ histogram
  TH1D *Wm_Nominal = new TH1D("Wm_Nominal","Wm_Nominal",13,Bins);
  TH1D *Wm_StatErr = new TH1D("Wm_StatErr","Wm_StatErr",13,Bins);
  TH1D *Wm_SystErr = new TH1D("Wm_SystErr","Wm_SystErr",13,Bins);
  TH1D *Wm_SysErr_per = new TH1D("Wm_SystErr_per","Wm_SystErr_per",13,Bins);

// Inclusive W histogram
  TH1D *W_Nominal = new TH1D("W_Nominal","W_Nominal",13,Bins);
  TH1D *W_StatErr = new TH1D("W_StatErr","W_StatErr",13,Bins);
  TH1D *W_SystErr = new TH1D("W_SystErr","W_SystErr",13,Bins);
  TH1D *W_SysErr_per = new TH1D("W_SystErr_per","W_SystErr_per",13,Bins);

// set histogram
  for(int ipt(1);ipt<NWptBinPlus;ipt++)
  {
      Wp_Nominal->SetBinContent(ipt,NomValP[ipt]);
      Wp_StatErr->SetBinError(ipt,ErrP[ipt]);
      Wp_SystErr->SetBinError(ipt,SystUncerP[ipt]);
     // Wp_SystErr_per->SetBinContent(ipt,SystUncerP_per[ipt]);

      Wm_Nominal->SetBinContent(ipt,NomValM[ipt]);
      Wm_StatErr->SetBinError(ipt,ErrM[ipt]);
      Wm_SystErr->SetBinError(ipt,SystUncerM[ipt]);
     // Wp_SystErr_per->SetBinContent(ipt,SystUncerP_per[ipt]);
 
      W_Nominal->SetBinContent(ipt,NomValI[ipt]);
      W_StatErr->SetBinError(ipt,ErrI[ipt]);
      W_SystErr->SetBinError(ipt,SystUncerI[ipt]);
     // Wp_SystErr_per->SetBinContent(ipt,SystUncerP_per[ipt]);
  }

// Write to root file
   Wp_Nominal->Write();
   Wp_StatErr->Write();
   Wp_SystErr->Write();
  //Wp_SystErr_percentage -> Write();

   Wm_Nominal->Write();
   Wm_StatErr->Write();
   Wm_SystErr->Write();
  // Wm_SystErr_percentage -> Write();

   W_Nominal->Write();
   W_StatErr->Write();
   W_SystErr->Write();
   //W_SystErr_percentage -> Write();
}
