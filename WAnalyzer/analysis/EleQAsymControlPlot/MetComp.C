//#include "/home/pharris/Analysis/W/condor/run/CMSSW_3_8_4/src/MitWlnu/NYStyle/test/NYStyle.h"
#include <TLatex.h>

//const int   nptBins  =   9;
//const int   nptBins  =   13;
//double xbins_pt[nptBins+1] = {0.0, 7.5, 12.5, 17.5, 24,30,40,50,70,110,150,190,250,600};

void drawDifference(TH1* iH0,TH1 *iH1,TH1 *iHH=0,TH1 *iHL=0) {
  std::string lName = std::string(iH0->GetName());
  TH1F *lHDiff  = new TH1F((lName+"Diff").c_str(),(lName+"Diff").c_str(),10,0,100); lHDiff->Sumw2();
//  TH1F *lHDiff  = new TH1F((lName+"Diff").c_str(),(lName+"Diff").c_str(),iH0->GetNbinsX(),iH0->GetXaxis()->GetXmin(),iH0->GetXaxis()->GetXmax()); lHDiff->Sumw2();
  TH1F *lHDiffH = new TH1F((lName+"DiffH").c_str(),(lName+"DiffH").c_str(),iH0->GetNbinsX(),iH0->GetXaxis()->GetXmin(),iH0->GetXaxis()->GetXmax()); lHDiffH->SetLineWidth(1); lHDiffH->SetLineColor(kRed);
  TH1F *lHDiffL = new TH1F((lName+"DiffL").c_str(),(lName+"DiffL").c_str(),iH0->GetNbinsX(),iH0->GetXaxis()->GetXmin(),iH0->GetXaxis()->GetXmax()); lHDiffL->SetLineWidth(1); lHDiffL->SetLineColor(kBlue);
  lHDiff->SetFillColor(kViolet); lHDiff->SetFillStyle(1001); lHDiff->SetLineWidth(1);
  TH1F *lXHDiff1 = new TH1F((lName+"XDiff1").c_str(),(lName+"XDiff1").c_str(),iH0->GetNbinsX(),iH0->GetXaxis()->GetXmin(),iH0->GetXaxis()->GetXmax());
  TH1F *lXHDiff2 = new TH1F((lName+"XDiff2").c_str(),(lName+"XDiff2").c_str(),iH0->GetNbinsX(),iH0->GetXaxis()->GetXmin(),iH0->GetXaxis()->GetXmax());
  int i1 = 0;
  lXHDiff1->SetLineWidth(2); lXHDiff1->SetLineColor(kRed);
  lXHDiff2->SetLineWidth(2); lXHDiff2->SetLineColor(kRed);

  lHDiff->GetYaxis()->SetRangeUser(0,2);
  lHDiff->GetYaxis()->SetTitleOffset(0.6);
  lHDiff->GetYaxis()->SetTitleSize(0.08);
  lHDiff->GetYaxis()->SetLabelSize(0.08);
  lHDiff->GetYaxis()->CenterTitle();
  lHDiff->GetXaxis()->SetTitleOffset(1.2);
  lHDiff->GetXaxis()->SetTitleSize(0.10);
  lHDiff->GetXaxis()->SetLabelSize(0.08);
  lHDiff->GetXaxis()->SetTitle("#slash{E}_{T} [GeV]");
//  lHDiff->GetXaxis()->CenterTitle();
//  lHDiff->GetYaxis()->SetTitle("W^{+}#rightarrow e^{+} #nu / W^{+}#rightarrow #mu^{+} #nu");
  lHDiff->GetYaxis()->SetTitle("MET/NoPU_MET");

  for(int i0 = 0; i0 < lHDiff->GetNbinsX()+1; i0++) {
    double lXCenter = lHDiff->GetBinCenter(i0);
    double lXVal     = iH0   ->GetBinContent(i0);
    //double lXValH    = iHH   ->GetBinContent(i0);
    //double lXValL    = iHL   ->GetBinContent(i0);
    lXHDiff1->SetBinContent(i0, 1.0);
    lXHDiff2->SetBinContent(i0, 1.0);
    while(iH1->GetBinCenter(i1) < lXCenter) {i1++;}
    if(iH1->GetBinContent(i0) > 0) lHDiff->SetBinContent(i0,lXVal      /(iH1->GetBinContent(i0)));
//    if(iH1->GetBinContent(i0) > 0) lHDiff->SetBinError  (i0,sqrt(lXVal)/(iH1->GetBinContent(i0)));
    if(iH1->GetBinContent(i0) > 0) lHDiff->SetBinError  (i0,iH0->GetBinError(i0)/(iH1->GetBinContent(i0)));
    //if(iH1->GetBinContent(i0) > 0) lHDiffL->SetBinContent(i0,lXValL/(iH1->GetBinContent(i0)));
    //if(iH1->GetBinContent(i0) > 0) lHDiffH->SetBinContent(i0,lXValH/(iH1->GetBinContent(i0)));
    //if(iH1->GetBinContent(i0) > 0)  cout << "unc" << lXVal << " -- " << sqrt(lXVal)/(iH1->GetBinContent(i0)) << endl;
  }
  lHDiff->SetMarkerStyle(kFullCircle); lHDiff->SetLineColor(kBlack); lHDiff->SetMarkerColor(kBlack);
//  lHDiff->Draw("EP");
  lHDiff->Draw("E1");
  lXHDiff1->SetLineColor(kRed);
  lXHDiff1->SetLineStyle(2);
  lXHDiff1->SetLineWidth(2);
  lXHDiff1->Draw("hist sames");
//  lXHDiff2->Draw("hist sames");
}

void MetComp()
{
  F_WToENu = new TFile("ElectronHighPU/Ele_WToENu_S10_Analysis.root");

//  TH1D *h1_Met = new TH1D("h1_Met","h1_Met",10,0,100); h1_Met->Sumw2();
//  TH1D *h1_NoPUMet = new TH1D("h1_NoPUMet","h1_NoPUMet",10,0,100); h1_NoPUMet->Sumw2();

  TH1D *Wmet;
  TH1D *WNoPUmet;

  Wmet =(TH1D*)F_WToENu->Get("h1_W_Met")->Clone();
  WNoPUmet =(TH1D*)F_WToENu->Get("h1_W_NoPU_Met")->Clone();

  Wmet->SetLineColor(kBlue);
  WNoPUmet->SetLineColor(kRed);
  
  WNoPUmet->GetYaxis()->SetTitle("Events");
//  Wmet->GetYaxis()->SetTitle("Events / %.1f GeV",Wmet->GetBinWidth(1));

  TLegend *lL =new TLegend(0.7,0.5,0.9,0.7);
  lL->SetFillColor(0); lL->SetBorderSize(0);
  lL->AddEntry(Wmet,"Met","L");
  lL->AddEntry(WNoPUmet,"No PU Met","L");
  TCanvas *lC0 = new TCanvas("Can","Can",800,800); lC0->cd(); lC0->SetLogy();
  lC0->Divide(1,2,0,0);
  lC0->cd(1)->SetPad(0,0.35,0.95,1.0);
  lC0->cd(1)->SetTopMargin(0.1);
  lC0->cd(1)->SetBottomMargin(0.01);
  lC0->cd(1)->SetLeftMargin(0.15);
  lC0->cd(1)->SetRightMargin(0.07);
  lC0->cd(1)->SetTickx(1);
  lC0->cd(1)->SetTicky(1);
  gStyle->SetTitleOffset(1.100,"Y");
  gStyle->SetLineWidth(2.);
  gStyle->SetTextSize(1.1);
  gStyle->SetLabelSize(0.06,"xy");
  gStyle->SetTitleSize(0.06,"xy");
  gStyle->SetTitleOffset(1.2,"x");
  gStyle->SetTitleOffset(1.0,"y");
  TGaxis::SetMaxDigits(3);

//  gPad->SetLogy(1);
  WNoPUmet->Draw("hist");
  Wmet->Draw("hist same");
  lL->Draw();
  
  lC0->cd(2)->SetPad(0,0,0.95,0.35);
  lC0->cd(2)->SetTopMargin(0.025);
  lC0->cd(2)->SetBottomMargin(0.3);
  lC0->cd(2)->SetLeftMargin(0.15);
  lC0->cd(2)->SetRightMargin(0.07);
  lC0->cd(2)->SetTickx(1);
  lC0->cd(2)->SetTicky(1);
  drawDifference(Wmet,WNoPUmet);
  lC0->SaveAs("WMetRation.png");
}
