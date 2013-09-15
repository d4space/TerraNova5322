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

void Zmass_RD_MC()
{

TCanvas *myCan=new TCanvas("myCan","myCan");
myCan->SetLogy(0);
myCan->SetLogx(0);


//TFile *fDYToEE_unCorr = new TFile("ElectronLowPU/Ele_RD_LowPU_Analysis.root");
//TFile *fDYToEE_Corr = new TFile("ElectronLowPU/Ele_RD_LowPU_AllCorrectionsRD.root");
//TFile *fRD = new TFile("ElectronLowPU/Ele_WpToEleNu_S8_AllCorrectionsMC.root");


TFile *fDYToEE_unCorr = new TFile("ElectronLowPU/Ele_DYToEE_S8_ScaleMakeMC_Eta_0.root");
TFile *fDYToEE_Corr = new TFile("ElectronLowPU/Ele_DYToEE_S8_ScaleMakeMC_Eta_0.root");
TFile *fRD = new TFile("ElectronLowPU/Ele_RD_LowPU_ScaleMakeRD_Eta_0.root");

//TFile *fDYToEE_unCorr = new TFile("MuonLowPU/Muon_DYToMuMu_S8_ScaleMakeMC_Eta_0.root");
//TFile *fDYToEE_Corr = new TFile("MuonLowPU/Muon_DYToMuMu_S8_ScaleMakeMC_Eta_0.root");
//TFile *fRD = new TFile("MuonLowPU/Muon_RD_LowPU_ScaleMakeRD_Eta_0.root");




/// Zmass Whole Range
fDYToEE_unCorr->cd();
TH1D* ZmassDYToEE_unCorr = (TH1D*) h1_Zmass->Clone("ZmassDYToEE_unCorr");
ZmassDYToEE_unCorr->SetTitleSize(0.06, "x");
ZmassDYToEE_unCorr->SetTitleOffset(1., "x");
ZmassDYToEE_unCorr->SetXTitle("Z mass");
ZmassDYToEE_unCorr->SetLineColor(kRed);
ZmassDYToEE_unCorr->Draw();
TLegend *Lgd = new TLegend(.65, .70,.9,.9);
Lgd->AddEntry(ZmassDYToEE_unCorr,"MC UnCorrected","l");

fDYToEE_Corr->cd();
TH1D* ZmassDYToEE_Corr = (TH1D*)h1_ZmassCorr->Clone("ZmassDYToEE_Corr");
ZmassDYToEE_Corr->SetLineColor(kBlue);
ZmassDYToEE_Corr->Draw("same");
Lgd->AddEntry(ZmassDYToEE_Corr,"MC Corrected","l");

fRD->cd();
TH1D* ZmassRD = (TH1D*)h1_Zmass->Clone("ZmassRD");
//Lgd->AddEntry(ZmassRD,"RD","l");
Lgd->Draw();
//ZmassRD->Draw("same");
//myCan->SaveAs("Zmass-Mu-RD-MC_WholeRange.png");
myCan->SaveAs("Zmass-Ele-MC_WholeRange.png");
//myCan->SaveAs("h1_W_Lept1-RD.png");

//*
/// Zmass BB
fDYToEE_unCorr->cd();
TH1D* ZmassDYToEE_unCorr = (TH1D*)h1_Zmass_BB->Clone("ZmassDYToEE_unCorr");
ZmassDYToEE_unCorr->SetTitleSize(0.06, "x");
ZmassDYToEE_unCorr->SetTitleOffset(1., "x");
ZmassDYToEE_unCorr->SetXTitle("Z mass BB");
ZmassDYToEE_unCorr->SetLineColor(kRed);
ZmassDYToEE_unCorr->Draw();
TLegend *Lgd = new TLegend(.65, .70,.9,.9);
Lgd->AddEntry(ZmassDYToEE_unCorr,"MC UnCorrected","l");

fDYToEE_Corr->cd();
TH1D* ZmassDYToEE_Corr = (TH1D*)h1_ZmassCorr_BB->Clone("ZmassDYToEE_Corr");
ZmassDYToEE_Corr->SetLineColor(kBlue);
ZmassDYToEE_Corr->Draw("same");
Lgd->AddEntry(ZmassDYToEE_Corr,"MC Corrected","l");

fRD->cd();
TH1D* ZmassRD = (TH1D*)h1_Zmass_BB->Clone("ZmassRD");
//Lgd->AddEntry(ZmassRD,"RD","l");
Lgd->Draw();
//ZmassRD->Draw("esame");
//myCan->SaveAs("Zmass-Mu-RD-MC_BB.png");
myCan->SaveAs("Zmass-Ele-MC_BB.png");

/// Zmass BE 
//*
fDYToEE_unCorr->cd();
TH1D* ZmassDYToEE_unCorr = (TH1D*)h1_Zmass_BE->Clone("ZmassDYToEE_unCorr");
ZmassDYToEE_unCorr->SetTitleSize(0.06, "x");
ZmassDYToEE_unCorr->SetTitleOffset(1., "x");
ZmassDYToEE_unCorr->SetXTitle("Z mass BE");
ZmassDYToEE_unCorr->SetLineColor(kRed);
ZmassDYToEE_unCorr->Draw();
TLegend *Lgd = new TLegend(.65, .70,.9,.9);
Lgd->AddEntry(ZmassDYToEE_unCorr,"MC UnCorrected","l");

fDYToEE_Corr->cd();
TH1D* ZmassDYToEE_Corr = (TH1D*)h1_ZmassCorr_BE->Clone("ZmassDYToEE_Corr");
ZmassDYToEE_Corr->SetLineColor(kBlue);
ZmassDYToEE_Corr->Draw("same");
Lgd->AddEntry(ZmassDYToEE_Corr,"MC Corrected","l");

fRD->cd();
TH1D* ZmassRD = (TH1D*)h1_Zmass_BE->Clone("ZmassRD");
//Lgd->AddEntry(ZmassRD,"RD","l");
Lgd->Draw();
//ZmassRD->Draw("esame");
//myCan->SaveAs("Zmass-Mu-RD-MC_BE-EB.png");
myCan->SaveAs("Zmass-Ele-MC_BE-EB.png");



/// Zmass EE
fDYToEE_unCorr->cd();
TH1D* ZmassDYToEE_unCorr = (TH1D*)h1_Zmass_EE->Clone("ZmassDYToEE_unCorr");
ZmassDYToEE_unCorr->SetTitleSize(0.06, "x");
ZmassDYToEE_unCorr->SetTitleOffset(1., "x");
ZmassDYToEE_unCorr->SetXTitle("Z mass EE");
ZmassDYToEE_unCorr->SetLineColor(kRed);
ZmassDYToEE_unCorr->Draw();
TLegend *Lgd = new TLegend(.65, .70,.9,.9);
Lgd->AddEntry(ZmassDYToEE_unCorr,"MC UnCorrected","l");

fDYToEE_Corr->cd();
TH1D* ZmassDYToEE_Corr = (TH1D*)h1_ZmassCorr_EE->Clone("ZmassDYToEE_Corr");
ZmassDYToEE_Corr->SetLineColor(kBlue);
ZmassDYToEE_Corr->Draw("same");
Lgd->AddEntry(ZmassDYToEE_Corr,"MC Corrected","l");

fRD->cd();
TH1D* ZmassRD = (TH1D*)h1_Zmass_EE->Clone("ZmassRD");
//Lgd->AddEntry(ZmassRD,"RD","l");
Lgd->Draw();
//ZmassRD->Draw("esame");
//myCan->SaveAs("Zmass-Mu-RD-MC_EE.png");
myCan->SaveAs("Zmass-Ele-MC_EE.png");




//*/












/*
/// Zpt
fDYToEE->cd();
TH1D* ZptDYToEE = (TH1D*)h1_Zpt->Clone("ZptDYToEE");

ZptDYToEE->SetTitleSize(0.06, "x");
ZptDYToEE->SetTitleOffset(1., "x");
ZptDYToEE->SetXTitle("Z pt");


ZptDYToEE->SetLineColor(kRed);
ZptDYToEE->Draw();
      TLegend *ZptLgd = new TLegend(.65, .70,.9,.9);
      ZptLgd->AddEntry(ZptDYToEE,"MC","l");

fRD->cd();
TH1D* ZptRD = (TH1D*)h1_Zpt->Clone("ZptRD");
ZptRD->SetLineColor(kBlue);
      ZptLgd->AddEntry(ZptRD,"RD","l");
      ZptLgd->Draw();
ZptRD->Draw("same");
myCan->SaveAs("Zpt-RD-MC.png");

/// Z_LepPt1-LepPt2
fDYToEE->cd();
h2_ZLep1_ZLep2->SetTitleSize(0.06, "x");
h2_ZLep1_ZLep2->SetTitleOffset(1., "x");
h2_ZLep1_ZLep2->SetXTitle("Z LepPt1");

h2_ZLep1_ZLep2->SetTitleSize(0.06, "y");
h2_ZLep1_ZLep2->SetTitleOffset(1.2, "y");
h2_ZLep1_ZLep2->SetYTitle("Z LepPt2");

h2_ZLep1_ZLep2->SetMarkerSize(0.5);
h2_ZLep1_ZLep2->Draw();
      TLegend *ZLepPt1LepPt2Lgd = new TLegend(.75, .80,.9,.9);
      ZLepPt1LepPt2Lgd->AddEntry(h2_ZLep1_ZLep2,"MC","");
      ZLepPt1LepPt2Lgd->Draw();
myCan->SaveAs("Z_LepPt1-LepPt2DYToEE.png");

fRD->cd();
h2_ZLep1_ZLep2->SetTitleSize(0.06, "x");
h2_ZLep1_ZLep2->SetTitleOffset(1., "x");
h2_ZLep1_ZLep2->SetXTitle("Z LepPt1");

h2_ZLep1_ZLep2->SetTitleSize(0.06, "y");
h2_ZLep1_ZLep2->SetTitleOffset(1.2, "y");
h2_ZLep1_ZLep2->SetYTitle("Z LepPt2");

h2_ZLep1_ZLep2->SetMarkerSize(0.5);
h2_ZLep1_ZLep2->Draw();
        TLegend *ZLepPt1LepPt2RDLgd = new TLegend(.75, .80,.9,.9);
        ZLepPt1LepPt2RDLgd->AddEntry(h2_ZLep1_ZLep2,"RD","");
	ZLepPt1LepPt2RDLgd->Draw();
myCan->SaveAs("Z_LepPt1-LepPt2DRD.png");

/// Z_mass-LepPt1
fDYToEE->cd();
h2_Zmass_ZLep1->SetTitleSize(0.06, "x");
h2_Zmass_ZLep1->SetTitleOffset(1., "x");
h2_Zmass_ZLep1->SetXTitle("Z mass");

h2_Zmass_ZLep1->SetTitleSize(0.06, "y");
h2_Zmass_ZLep1->SetTitleOffset(1.2, "y");
h2_Zmass_ZLep1->SetYTitle("Z LepPt1");

h2_Zmass_ZLep1->SetMarkerSize(0.5);
h2_Zmass_ZLep1->Draw();
      TLegend *ZmassLepPt1Lgd = new TLegend(.75, .80,.9,.9);
      ZmassLepPt1Lgd->AddEntry(h2_Zmass_ZLep1,"MC","");
      ZmassLepPt1Lgd->Draw();
myCan->SaveAs("Zmass_ZLep1_2D-DYToEE.png");

fRD->cd();
h2_Zmass_ZLep1->SetTitleSize(0.06, "x");
h2_Zmass_ZLep1->SetTitleOffset(1., "x");
h2_Zmass_ZLep1->SetXTitle("Z mass");

h2_Zmass_ZLep1->SetTitleSize(0.06, "y");
h2_Zmass_ZLep1->SetTitleOffset(1.2, "y");
h2_Zmass_ZLep1->SetYTitle("Z LepPt1");

h2_Zmass_ZLep1->SetMarkerSize(0.5);
h2_Zmass_ZLep1->Draw();
      TLegend *ZmassLepPt1RDLgd = new TLegend(.75, .80,.9,.9);
      ZmassLepPt1RDLgd->AddEntry(h2_Zmass_ZLep1,"RD","");
      ZmassLepPt1RDLgd->Draw();
myCan->SaveAs("Zmass_ZLep1_2D-RD.png");

/// Z_mass-LepPt2
fDYToEE->cd();
h2_Zmass_ZLep2->SetTitleSize(0.06, "x");
h2_Zmass_ZLep2->SetTitleOffset(1., "x");
h2_Zmass_ZLep2->SetXTitle("Z mass");

h2_Zmass_ZLep2->SetTitleSize(0.06, "y");
h2_Zmass_ZLep2->SetTitleOffset(1.2, "y");
h2_Zmass_ZLep2->SetYTitle("Z LepPt2");

h2_Zmass_ZLep2->SetMarkerSize(0.5);
h2_Zmass_ZLep2->Draw();
      TLegend *ZmassLepPt2Lgd = new TLegend(.75, .80,.9,.9);
      ZmassLepPt2Lgd->AddEntry(h2_Zmass_ZLep2,"MC","");
      ZmassLepPt2Lgd->Draw();
myCan->SaveAs("Zmass_ZLep2_2D-DYToEE.png");

fRD->cd();
h2_Zmass_ZLep2->SetTitleSize(0.06, "x");
h2_Zmass_ZLep2->SetTitleOffset(1., "x");
h2_Zmass_ZLep2->SetXTitle("Z mass");

h2_Zmass_ZLep2->SetTitleSize(0.06, "y");
h2_Zmass_ZLep2->SetTitleOffset(1.2, "y");
h2_Zmass_ZLep2->SetYTitle("Z LepPt2");

h2_Zmass_ZLep2->SetMarkerSize(0.5);
h2_Zmass_ZLep2->Draw();
      TLegend *ZmassLepPt2RDLgd = new TLegend(.75, .80,.9,.9);
      ZmassLepPt2RDLgd->AddEntry(h2_Zmass_ZLep2,"RD","");
      ZmassLepPt2RDLgd->Draw();
myCan->SaveAs("Zmass_ZLep2_2D-RD.png");

/// Z_pt-LepPt1
fDYToEE->cd();
h2_Zpt_ZLep1->SetTitleSize(0.06, "x");
h2_Zpt_ZLep1->SetTitleOffset(1., "x");
h2_Zpt_ZLep1->SetXTitle("Z pt");

h2_Zpt_ZLep1->SetTitleSize(0.06, "y");
h2_Zpt_ZLep1->SetTitleOffset(1.2, "y");
h2_Zpt_ZLep1->SetYTitle("Z LepPt1");

h2_Zpt_ZLep1->SetMarkerSize(0.5);
h2_Zpt_ZLep1->Draw();
      TLegend *ZptLepPt1Lgd = new TLegend(.75, .80,.9,.9);
      ZptLepPt1Lgd->AddEntry(h2_Zpt_ZLep1,"MC","");
      ZptLepPt1Lgd->Draw();
myCan->SaveAs("Zpt_ZLep1_2D-DYToEE.png");

fRD->cd();
h2_Zpt_ZLep1->SetTitleSize(0.06, "x");
h2_Zpt_ZLep1->SetTitleOffset(1., "x");
h2_Zpt_ZLep1->SetXTitle("Z pt");

h2_Zpt_ZLep1->SetTitleSize(0.06, "y");
h2_Zpt_ZLep1->SetTitleOffset(1.2, "y");
h2_Zpt_ZLep1->SetYTitle("Z LepPt1");

h2_Zpt_ZLep1->SetMarkerSize(0.5);
h2_Zpt_ZLep1->Draw();
      TLegend *ZptLepPt1RDLgd = new TLegend(.75, .80,.9,.9);
      ZptLepPt1RDLgd->AddEntry(h2_Zpt_ZLep1,"RD","");
      ZptLepPt1RDLgd->Draw();
myCan->SaveAs("Zpt_ZLep1_2D-RD.png");

/// Z_pt-LepPt2
fDYToEE->cd();
h2_Zpt_ZLep2->SetTitleSize(0.06, "x");
h2_Zpt_ZLep2->SetTitleOffset(1., "x");
h2_Zpt_ZLep2->SetXTitle("Z pt");

h2_Zpt_ZLep2->SetTitleSize(0.06, "y");
h2_Zpt_ZLep2->SetTitleOffset(1.2, "y");
h2_Zpt_ZLep2->SetYTitle("Z LepPt2");

h2_Zpt_ZLep2->SetMarkerSize(0.5);
h2_Zpt_ZLep2->Draw();
      TLegend *ZptLepPt2Lgd = new TLegend(.75, .80,.9,.9);
      ZptLepPt2Lgd->AddEntry(h2_Zpt_ZLep2,"MC","");
      ZptLepPt2Lgd->Draw();
myCan->SaveAs("Zpt_ZLep2_2D-DYToEE.png");

fRD->cd();
h2_Zpt_ZLep2->SetTitleSize(0.06, "x");
h2_Zpt_ZLep2->SetTitleOffset(1., "x");
h2_Zpt_ZLep2->SetXTitle("Z pt");

h2_Zpt_ZLep2->SetTitleSize(0.06, "y");
h2_Zpt_ZLep2->SetTitleOffset(1.2, "y");
h2_Zpt_ZLep2->SetYTitle("Z LepPt2");

h2_Zpt_ZLep2->SetMarkerSize(0.5);
h2_Zpt_ZLep2->Draw();
      TLegend *ZptLepPt2RDLgd = new TLegend(.75, .80,.9,.9);
      ZptLepPt2RDLgd->AddEntry(h2_Zpt_ZLep2,"RD","");
      ZptLepPt2RDLgd->Draw();
myCan->SaveAs("Zpt_ZLep2_2D-RD.png");
*/

}

