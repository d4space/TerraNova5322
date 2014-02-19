/*#include <TSystem.h>                      // interface to OS
#include <TStyle.h>                       // class to handle ROOT plotting styles#include <TFile.h>                        // file handle class
#include <TTree.h>                        // class to access ntuples
#include <TBenchmark.h>                   // class to track macro running statistics
#include <TH1D.h>                         // histogram class
#include <vector>                         // STL vector class
#include <iostream>                       // standard I/O
#include <iomanip>                        // functions to format standard I/O
#include <fstream>                        // functions for file I/O
#include <string>                         // C++ string class
#include <sstream>                        // class for parsing strings
#include <TRandom3.h>
#include <TGaxis.h>
#include "Math/LorentzVector.h"           // 4-vector class

#include "../Utils/MyTools.hh"            // various helper functions
#include "../Utils/CPlot.hh"              // helper class for plots
#include "../Utils/MitStyleRemix.hh"      // style settings for drawing
#include "../Utils/WModels.hh"            // definitions of PDFs for fitting
#include "../Utils/RecoilCorrector.hh"    // class to handle recoil corrections for MET
*/
void W_MET_Ratio()
{
  TCanvas *c = new TCanvas("c","c",800,800);
  c->Divide(1,2,0,0);
  c->cd(1)->SetPad(0,0.3,1.0,1.0);
  c->cd(1)->SetTopMargin(0.1);
  c->cd(1)->SetBottomMargin(0.01);
  c->cd(1)->SetLeftMargin(0.15);
  c->cd(1)->SetRightMargin(0.07);  
  c->cd(1)->SetTickx(1);
  c->cd(1)->SetTicky(1);  
  c->cd(2)->SetPad(0,0,1.0,0.3);
  c->cd(2)->SetTopMargin(0.05);
  c->cd(2)->SetBottomMargin(0.45);
  c->cd(2)->SetLeftMargin(0.15);
  c->cd(2)->SetRightMargin(0.07);
  c->cd(2)->SetTickx(1);
  c->cd(2)->SetTicky(1);
  c->cd(2)->SetGridy();

  TLegend * lgc = new TLegend(0.59, 0.67, 0.89, 0.89);
  lgc->SetTextSize(0.03);
  lgc->SetBorderSize(0);
  lgc->SetFillColor(0);

//  TFile *file = new TFile("../ElectronHighPU/Ele_RD_HighPU_A_Analysis.root");
  TFile *file = new TFile("./ElectronHighPU_N/Ele_WToENu_S10_Analysis.root");
 
///////////////Original Plot////////////////////////
  c->cd(1);
  lgc->AddEntry(h1_W_Neut_pt1,"UnCorrected");
  h1_W_Neut_pt1->SetYTitle("Events");
  h1_W_Neut_pt1->SetFillColor(kWhite);
  h1_W_Neut_pt1->SetMarkerColor(kBlack);
  h1_W_Neut_pt1->SetMarkerStyle(1);
  h1_W_Neut_pt1->SetLineWidth(2);
  h1_W_Neut_pt1->Draw();
  lgc->AddEntry(h1_W_Neut_pt_Corr,"Corrected");
  h1_W_Neut_pt_Corr->SetLineColor(kRed);
  h1_W_Neut_pt_Corr->SetFillColor(kWhite);
  h1_W_Neut_pt_Corr->SetMarkerColor(kRed);
  h1_W_Neut_pt_Corr->SetMarkerStyle(1);
  h1_W_Neut_pt_Corr->SetLineWidth(2);
  h1_W_Neut_pt_Corr->Draw("same");
  lgc->Draw();
///////////////////////////////////////////////////////
  
  c->cd(2);

  TH1F * h1_Ori = (TH1F*)file->Get("h1_W_Neut_pt1");
  TH1F * h1_Corr = (TH1F*)file->Get("h1_W_Neut_pt_Corr");

  int Nbins = h1_Ori->GetNbinsX();
  TH1F * ratio = new TH1F("ratio","", Nbins, h1_Ori->GetXaxis()->GetXmin(), h1_Ori->GetXaxis()->GetXmax());
  ratio->Divide(h1_Ori, h1_Corr);
  ratio->SetXTitle("N_vtx");
  ratio->SetMaximum(2);
  ratio->SetMinimum(0);
  ratio->SetNdivisions(10,"X");
  ratio->SetNdivisions(4,"Y");
  ratio->SetLabelSize(0.09,"XY");
  ratio->SetTitleSize(0.12,"X"); 
  ratio->SetMarkerStyle(20);
  ratio->SetMarkerSize(0.7);
  ratio->SetMarkerColor(kBlue);
  ratio->Draw("P");

//  c->SaveAs("W_MET_Ratio_RD.png");
  c->SaveAs("W_MET_Ratio_MC.png");
}
