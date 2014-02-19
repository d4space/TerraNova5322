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
  enum {eNominal, eUp, eDown};
  vector<TString> fnamev;
  vector<Int_t>   typev;
  
  TH1D *hNom;
  TH1D *hNomP;
  TH1D *hNomM;
  TH1D *hUp;
  TH1D *hUpP;
  TH1D *hUpM;
  TH1D *hDown;
  TH1D *hDownP;
  TH1D *hDownM;

  if (filetype == "Mu"){
    fnamev.push_back("RstMuon/SigYields_Nominal.root"); typev.push_back(eNominal);
    fnamev.push_back("RstMuon/SigYields_Up.root"); typev.push_back(eUp);
    fnamev.push_back("RstMuon/SigYields_Down.root"); typev.push_back(eDown);
  }else if (filetype == "Ele"){
    fnamev.push_back("RstElectron/SigYields_Nominal.root"); typev.push_back(eNominal);
    fnamev.push_back("RstElectron/SigYields_Up.root"); typev.push_back(eUp);
    fnamev.push_back("RstElectron/SigYields_Down.root"); typev.push_back(eDown);
  }
  TFile *infile=0;
  cout<<"Looping Files ------------------------"<<endl;
  char histName[30],histName_org[30];
  for(UInt_t ifile=0; ifile<fnamev.size(); ifile++) {
    cout << "Processing " << fnamev[ifile] << "..." << endl;
    infile = new TFile(fnamev[ifile]);    assert(infile);
    if(typev[ifile]==eNominal)
    {
      sprintf(histName,"hNom");
      sprintf(histName_org,"hSigWpt");
      hNom = (TH1D*)infile->Get(histName_org)->Clone(histName);
      sprintf(histName,"hNomP");
      sprintf(histName_org,"hSigWPpt");
      hNomP = (TH1D*)infile->Get(histName_org)->Clone(histName);
      sprintf(histName,"hNomM");
      sprintf(histName_org,"hSigWMpt");
      hNomM = (TH1D*)infile->Get(histName_org)->Clone(histName);
    }
    if(typev[ifile]==eUp)
    {
      sprintf(histName,"hUp");
      sprintf(histName_org,"hSigWpt");
      hUp = (TH1D*)infile->Get(histName_org)->Clone(histName);
      sprintf(histName,"hUpP");
      sprintf(histName_org,"hSigWPpt");
      hUpP = (TH1D*)infile->Get(histName_org)->Clone(histName);
      sprintf(histName,"hUpM");
      sprintf(histName_org,"hSigWMpt");
      hUpM = (TH1D*)infile->Get(histName_org)->Clone(histName);
    }
    if(typev[ifile]==eDown)
    {
      sprintf(histName,"hDown");
      sprintf(histName_org,"hSigWpt");
      hDown = (TH1D*)infile->Get(histName_org)->Clone(histName);
      sprintf(histName,"hDownP");
      sprintf(histName_org,"hSigWPpt");
      hDownP = (TH1D*)infile->Get(histName_org)->Clone(histName);
      sprintf(histName,"hDownM");
      sprintf(histName_org,"hSigWMpt");
      hDownM = (TH1D*)infile->Get(histName_org)->Clone(histName);
    }
  }
  
  double NomVal[13];
  double NomValP[13];
  double NomValM[13];
  double UpVal[13];
  double UpValP[13];
  double UpValM[13];
  double DownVal[13];
  double DownValP[13];
  double DownValM[13];

  double Err[13];
  double ErrP[13];
  double ErrM[13];

  double A[13];
  double Ap[13];
  double Am[13];
  double B[13];
  double Bp[13];
  double Bm[13];
  double SystUncer[13];
  double SystUncerP[13];
  double SystUncerM[13];
  
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
  
  char uncert[50];
  char uncertp[50];
  char uncertm[50];

  ofstream htmlfile;
  char htmlfname[100];
  sprintf(htmlfname,filetype+"_Systematics.html");
  htmlfile.open(htmlfname);
//  assert(htmlfile.is_open());
  htmlfile << "<!DOCTYPE html" << endl;
  htmlfile << "    PUBLIC \"-//W3C//DTD HTML 3.2//EN\">" << endl;
  htmlfile << "<html>" << endl;
  htmlfile << "<head><title>Systematic uncertainties</title></head>" << endl;
  htmlfile << "<body bgcolor=\"white\">" << endl;
  htmlfile << "<hr />" << endl;
  htmlfile << "<p align=\"center\"> Systematic uncertainties from Recoil Correction  </p>" << endl;
  htmlfile << "<hr />" << endl;
  htmlfile << "<table border=\"1\" style=\"border-collapse: collapse\" bordercolor=\"black\" cellspacing=\"4\" width=\"1100\" align=\"center\">" << endl;
  htmlfile << "<tr>" << endl;
  htmlfile << "<td width=\"200\"><p align=\"center\"> W p<sub>T</sub> Bin </p></td>" << endl;
  htmlfile << "<td width=\"300\"><p align=\"center\"> W Inclusive</p></td>" << endl;
  htmlfile << "<td width=\"300\"><p align=\"center\"> W <sup>+</sup></p></td>" << endl;
  htmlfile << "<td width=\"300\"><p align=\"center\"> W <sup>-</sup></p></td>" << endl;
  htmlfile << "</tr>" << endl;

  for(int ipt(1);ipt<NWptBinPlus;ipt++)
  {
    NomVal[ipt] = hNom->GetBinContent(ipt);
    NomValP[ipt] = hNomP->GetBinContent(ipt);
    NomValM[ipt] = hNomM->GetBinContent(ipt);
    UpVal[ipt] = hUp->GetBinContent(ipt);
    UpValP[ipt] = hUpP->GetBinContent(ipt);
    UpValM[ipt] = hUpM->GetBinContent(ipt);
    DownVal[ipt] = hDown->GetBinContent(ipt);
    DownValP[ipt] = hDownP->GetBinContent(ipt);
    DownValM[ipt] = hDownM->GetBinContent(ipt);
    Err[ipt] = hNom->GetBinError(ipt);
    ErrP[ipt] = hNomP->GetBinError(ipt);
    ErrM[ipt] = hNomM->GetBinError(ipt);

    A[ipt] = NomVal[ipt] - UpVal[ipt];
    Ap[ipt] = NomValP[ipt] - UpValP[ipt];
    Am[ipt] = NomValM[ipt] - UpValM[ipt];
    B[ipt] = NomVal[ipt] - DownVal[ipt];
    Bp[ipt] = NomValP[ipt] - DownValP[ipt];
    Bm[ipt] = NomValM[ipt] - DownValM[ipt];

    SystUncer[ipt] = fmax(fabs(A[ipt]),fabs(B[ipt]));
    SystUncerP[ipt] = fmax(fabs(Ap[ipt]),fabs(Bp[ipt]));
    SystUncerM[ipt] = fmax(fabs(Am[ipt]),fabs(Bm[ipt]));

    //SystUncer[ipt] = sqrt(A[ipt]*A[ipt]+B[ipt]*B[ipt]);
    //SystUncerP[ipt] = sqrt(Ap[ipt]*Ap[ipt]+Bp[ipt]*Bp[ipt]);
    //SystUncerM[ipt] = sqrt(Am[ipt]*Am[ipt]+Bm[ipt]*Bm[ipt]);
    
    sprintf(uncert,"%.1f &plusmn; %.1f &plusmn; %.1f (%.2f \%)", NomVal[ipt],Err[ipt],SystUncer[ipt],SystUncer[ipt]/NomVal[ipt]*100);
    sprintf(uncertp,"%.1f &plusmn; %.1f &plusmn; %.1f (%.2f \%)", NomValP[ipt],ErrP[ipt],SystUncerP[ipt],SystUncerP[ipt]/NomValP[ipt]*100);
    sprintf(uncertm,"%.1f &plusmn; %.1f &plusmn; %.1f (%.2f \%)", NomValM[ipt],Err[ipt],SystUncerM[ipt],SystUncerM[ipt]/NomValM[ipt]*100);
    
    htmlfile << "<tr>" << endl; 
    htmlfile << "<td width=\"200\"><p>[" << Bins[ipt-1] << ", " << Bins[ipt] << "] Bin - " << ipt << "</p></td>" << endl;
    htmlfile << "<td width=\"300\"><p>" << uncert << "</p></td>" << endl;
    htmlfile << "<td width=\"300\"><p>" << uncertp << "</p></td>" << endl;
    htmlfile << "<td width=\"300\"><p>" << uncertm << "</p></td>" << endl;
    htmlfile << "</tr>" << endl;
  }
  htmlfile << "</table>" << endl;
  htmlfile << "<hr />" << endl;
  htmlfile << "</body>" << endl;
  htmlfile << "</html>" << endl;
  htmlfile.close();
}
