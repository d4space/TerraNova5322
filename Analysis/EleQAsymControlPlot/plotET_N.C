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
void plotET_N()
{
  TString DIR = "ElectronHighPU_N";
  TString fileNM[] = {"RD_HighPU","WToENu_S10","WToTauNu_S10","DYToEE_S10","TTJets_S10","G_Pt50to80_S10","QCD80to120_S10","QCD120to170_S10","QCD50to80_S10","QCD30to50_S10"};
  TString filePath[10];

  const Color_t bgdColor[10] ={kBlack,kAzure+1,kOrange,kTeal,kRed,kGreen,kGray+2,kGray+2,kGray+2,kGray+2};

  TLegend * lgc = new TLegend(0.59, 0.67, 0.89, 0.89);
  lgc->SetTextSize(0.03);
  lgc->SetBorderSize(0);
  lgc->SetFillColor(0);

  //THStack *hs_W_Lept1_pt = new THStack("hs_W_Lept1_pt","W_Lept1_pt");
  THStack *hs_W_Lept1_pt = new THStack("hs_W_Lept1_pt","MET");
  //THStack *hs_W_Lept1_pt = new THStack("hs_W_Lept1_pt","# of Vertex");

  //TH1F * h1_MC = new TH1F("h1_MC","PT",50,0.,100);
  TH1F * h1_MC = new TH1F("h1_MC","MET",100,0.,100);
  //TH1F * h1_MC = new TH1F("h1_MC","VTX",60,0,60);

  for(Int_t i=9;i>-1;i--)
    {
      filePath[i]= DIR+"/Ele_"+fileNM[i]+"_Analysis.root";
      cout<<filePath[i] <<endl;

      TFile *f_file = new TFile(filePath[i]);
      //h1_W_Lept1_pt->SetLineColor(bgdColor[i]);      h1_W_Lept1_pt->SetFillColor(bgdColor[i]); h1_W_Lept1_pt->SetFillStyle(1001);
      h1_W_Neut_pt1->SetLineColor(bgdColor[i]);      h1_W_Neut_pt1->SetFillColor(bgdColor[i]); h1_W_Neut_pt1->SetFillStyle(1001);
      //h1_Vtx_Prim1->SetLineColor(bgdColor[i]);      h1_Vtx_Prim1->SetFillColor(bgdColor[i]); h1_Vtx_Prim1->SetFillStyle(1001);


      //      if(i>0){  
      //if( ! (i==0 || i==2 || i==3 || i>5) ){  
      if( ! (i==0) ){  
	//hs_W_Lept1_pt->Add(h1_W_Lept1_pt);   
	hs_W_Lept1_pt->Add(h1_W_Neut_pt1);  
	//hs_W_Lept1_pt->Add(h1_Vtx_Prim1);  
        //h1_MC->Add(h1_W_Lept1_pt);
        h1_MC->Add(h1_W_Neut_pt1);
        //h1_MC->Add(h1_Vtx_Prim1);
        if( i < 6){ 
	//lgc->AddEntry(h1_W_Lept1_pt,fileNM[i],"F");}
	lgc->AddEntry(h1_W_Neut_pt1,fileNM[i],"F");}
	//lgc->AddEntry(h1_Vtx_Prim1,fileNM[i],"F");}
        if( i ==6){
	//lgc->AddEntry(h1_W_Lept1_pt,"QCD","F");}
	lgc->AddEntry(h1_W_Neut_pt1,"QCD","F");}
	//lgc->AddEntry(h1_Vtx_Prim1,"QCD","F");}
      }

    }//for
  TCanvas *c1 = new TCanvas();
  TFile *f_fileRD = new TFile(filePath[0]); 

  c1->Divide(1,2,0,0);
  c1->cd(1)->SetPad(0,0.3,1.0,1.0);
  c1->cd(1)->SetTopMargin(0.1);
  c1->cd(1)->SetBottomMargin(0.01);
  c1->cd(1)->SetLeftMargin(0.15);
  c1->cd(1)->SetRightMargin(0.07);
  c1->cd(1)->SetTickx(1);
  c1->cd(1)->SetTicky(1);
  c1->cd(2)->SetPad(0,0,1.0,0.3);
  c1->cd(2)->SetTopMargin(0.05);
  c1->cd(2)->SetBottomMargin(0.45);
  c1->cd(2)->SetLeftMargin(0.15);
  c1->cd(2)->SetRightMargin(0.07);
  c1->cd(2)->SetTickx(1);
  c1->cd(2)->SetTicky(1);
  c1->cd(2)->SetGridy(); 

  c1->cd(1);
  
  //lgc->AddEntry(h1_W_Lept1_pt,"2012RealData 19.619/fb", "LP");
  lgc->AddEntry(h1_W_Neut_pt1,"2012RealData 19.619/fb", "LP");
  //lgc->AddEntry(h1_Vtx_Prim1,"2012RealData 19.619/fb", "LP");
  //h1_W_Lept1_pt->SetMarkerStyle(20);  h1_W_Lept1_pt->SetMarkerSize(1);
  h1_W_Neut_pt1->SetMarkerStyle(20);  h1_W_Neut_pt1->SetMarkerSize(1); h1_W_Neut_pt1->SetMaximum(2500000);
  //h1_Vtx_Prim1->SetMarkerStyle(20);  h1_Vtx_Prim1->SetMarkerSize(1);
  //h1_W_Lept1_pt->Draw("e");
  //h1_W_Neut_pt1->Draw("e");
  //h1_Vtx_Prim1->Draw("e");
  hs_W_Lept1_pt->Draw();
  //hs_W_Lept1_pt->Draw("same");
  //h1_W_Lept1_pt->Draw("same e");
  h1_W_Neut_pt1->Draw("same e");
  //h1_Vtx_Prim1->Draw("same e");
  lgc->Draw();

  c1->cd(2);

  //int Nbins = h1_W_Lept1_pt->GetNbinsX();
  int Nbins = h1_W_Neut_pt1->GetNbinsX();
  //int Nbins = h1_Vtx_Prim1->GetNbinsX();
  //TH1F * ratio = new TH1F("ratio","", Nbins, h1_W_Lept1_pt->GetXaxis()->GetXmin(), h1_W_Lept1_pt->GetXaxis()->GetXmax());
  TH1F * ratio = new TH1F("ratio","", Nbins, h1_W_Neut_pt1->GetXaxis()->GetXmin(), h1_W_Neut_pt1->GetXaxis()->GetXmax());
  //TH1F * ratio = new TH1F("ratio","", Nbins, h1_Vtx_Prim1->GetXaxis()->GetXmin(), h1_Vtx_Prim1->GetXaxis()->GetXmax());
  //ratio->Divide(h1_W_Lept1_pt, h1_MC);
  ratio->Divide(h1_W_Neut_pt1, h1_MC);
  //ratio->Divide(h1_Vtx_Prim1, h1_MC);
  ratio->SetMaximum(1.5);
  ratio->SetMinimum(0.5);
  ratio->SetNdivisions(10,"X");
  ratio->SetNdivisions(5,"Y");
  ratio->SetLabelSize(0.09,"XY");
  ratio->SetTitleSize(0.12,"X");
  ratio->SetMarkerStyle(20);
  ratio->SetMarkerSize(0.7);
  ratio->Draw("P");

  //c1->SaveAs("W_Lept1_pt_N.png");
  c1->SaveAs("W_Neu_All_N.png");
  //c1->SaveAs("Vtx_Prim1_N.png");
}
