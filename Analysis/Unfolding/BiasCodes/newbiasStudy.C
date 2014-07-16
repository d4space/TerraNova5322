#include <iostream>
#include <fstream>
#include <TFile.h>
#include "TH1D.h"
#include <TGraphErrors.h>             // graph class
#include <TGraphAsymmErrors.h>        // graph class
#include <TLatex.h>
#include "TProfile.h"

const int nBins = 14;
double WptLogBins[nBins] = {1.0,7.5,12.5,17.5,24,30,40,50,70,110,150,190,250,600};
double WptBins[nBins] = {0.0,7.5,12.5,17.5,24,30,40,50,70,110,150,190,250,600};

double ax[13]  = {4.25,10,15,20.75,27,35,45,60,90,130,170,220,425};
double aex[13] = {3.25,2.5,2.5,3.25,3,5,5,10,20,20,20,30,175};

void drawDifference(TH1* iH0,TH1 *iH1,TH1 *iHH=0,TH1 *iHL=0) {
  std::string lName = std::string(iH0->GetName());
  TH1F *lHDiff  = new TH1F((lName+"Diff").c_str(),(lName+"Diff").c_str(),nBins-1,WptLogBins); lHDiff->Sumw2();
  TH1F *lHDiffH = new TH1F((lName+"DiffH").c_str(),(lName+"DiffH").c_str(),iH0->GetNbinsX(),iH0->GetXaxis()->GetXmin(),iH0->GetXaxis()->GetXmax()); lHDiffH->SetLineWidth(1); lHDiffH->SetLineColor(kRed);
  TH1F *lHDiffL = new TH1F((lName+"DiffL").c_str(),(lName+"DiffL").c_str(),iH0->GetNbinsX(),iH0->GetXaxis()->GetXmin(),iH0->GetXaxis()->GetXmax()); lHDiffL->SetLineWidth(1); lHDiffL->SetLineColor(kBlue);
  lHDiff->SetFillColor(kViolet); lHDiff->SetFillStyle(1001); lHDiff->SetLineWidth(1);
  TH1F *lXHDiff1 = new TH1F((lName+"XDiff1").c_str(),(lName+"XDiff1").c_str(),iH0->GetNbinsX(),iH0->GetXaxis()->GetXmin(),iH0->GetXaxis()->GetXmax());
  TH1F *lXHDiff2 = new TH1F((lName+"XDiff2").c_str(),(lName+"XDiff2").c_str(),iH0->GetNbinsX(),iH0->GetXaxis()->GetXmin(),iH0->GetXaxis()->GetXmax());
  int i1 = 0;
  lXHDiff1->SetLineWidth(2); lXHDiff1->SetLineColor(kBlack); lXHDiff1->SetLineStyle(2);
  lXHDiff2->SetLineWidth(2); lXHDiff2->SetLineColor(kRed);
  
  lHDiff->GetYaxis()->SetRangeUser(0.5,1.5);
  lHDiff->GetYaxis()->SetTitleOffset(0.6);
  lHDiff->GetYaxis()->SetTitleSize(0.08);
  lHDiff->GetYaxis()->SetLabelSize(0.08);
  lHDiff->GetYaxis()->CenterTitle();
  lHDiff->GetXaxis()->SetTitleOffset(1.2);
  lHDiff->GetXaxis()->SetTitleSize(0.10);
  lHDiff->GetXaxis()->SetLabelSize(0.08);
  lHDiff->GetXaxis()->SetTitle(" W p_{T} ");
  lHDiff->GetYaxis()->SetTitle("Data/normGen");
  gStyle->SetOptStat(0);
  
  for(int i0 = 0; i0 < lHDiff->GetNbinsX()+1; i0++) {
    double lXCenter = lHDiff->GetBinCenter(i0);
    double lXVal     = iH0   ->GetBinContent(i0);
    lXHDiff1->SetBinContent(i0, 1.0);
    lXHDiff2->SetBinContent(i0, 1.0);
    while(iH1->GetBinCenter(i1) < lXCenter) {i1++;}
    if(iH1->GetBinContent(i0) > 0) lHDiff->SetBinContent(i0,lXVal/(iH1->GetBinContent(i0)));
    if(iH1->GetBinContent(i0) > 0) lHDiff->SetBinError(i0,iH0->GetBinError(i0)/(iH1->GetBinContent(i0)));
  }
  lHDiff->SetMarkerStyle(kFullCircle); lHDiff->SetLineColor(kBlack); lHDiff->SetMarkerColor(kBlack);
  
  lHDiff->SetTitle("");
  lHDiff->Draw("E1");
  lXHDiff1->Draw("hist sames");
}

int newbiasStudy(const TString BaseName)
{

  TString tmpTStr = BaseName+"_ToyYields.txt";
  char tmpName[30],tmpName_org[30];

  TFile *fToy;

  fToy = new TFile("../Result"+BaseName+"/Result_"+BaseName+".root");

  TH1D *hPowhegLog   = new TH1D("hPowhegLog","hPowhegLog",13,WptLogBins);hPowhegLog->Sumw2();
  TH1D *hDataLog     = new TH1D("hDataLog","hDataLog",13,WptLogBins);hDataLog->Sumw2();
  
  TH1D* lPowheg;
  TH1D* lData;
  TH1D* lDet;
  TH1D* lTruthRec;
  
  TH1D* dGen;
  TH1D* fGen;
  TH1D* dUnf[500];
  TH1D* fUnf[500];
  
  ofstream Fout;
  Fout.open(tmpTStr);
  Fout <<fixed<<setprecision(6);
  
  fGen = (TH1D*)fToy->Get("hGenFSRNorm")->Clone();
  
  //Double_t wptBins[14] = {0.5,1.5,2.5,3.5,4.5,5.5,6.5,7.5,8.5,9.5,10.5,11.5,12.5,13.5};
  //TCanvas *c1 = new TCanvas("c1","Can",800,800);
  //h_dUnfProf = new TProfile("h_dUnfProf","Detector Unfolding Profile",13,wptBins);
  //h_fUnfProf = new TProfile("h_fUnfProf","FSR Unfolding Profile",13,wptBins);
  //
  //Double_t xBins[13] = {1,2,3,4,5,6,7,8,9,10,11,12,13};
  //
  //for( int ipt(0);ipt<500;ipt++)
  //{
  //  sprintf(tmpName,"SVD_Post.DetUnf_%d",ipt);
  //  dUnf[ipt] = (TH1D*)fToy->Get(tmpName)->Clone(tmpName);
  //  sprintf(tmpName,"SVD_Born.FSRUnf_%d",ipt);
  //  fUnf[ipt] = (TH1D*)fToy->Get(tmpName)->Clone(tmpName);
  //  
  //  //Fout<<"nToy: "<<ipt<<endl;
  //  //Fout<<"nBins\t dUnf\t Ratio\t\t FSRUnf\t Ratio "<<endl;
  //  //Fout<<"======================================="<<endl;
  //  for( int i(1);i<=nBins-1;i++)
  //  {
  //    h_dUnfProf->Fill(xBins[i-1],(dUnf[ipt]->GetBinContent(i)-dGen->GetBinContent(i))/dGen->GetBinContent(i));
  //    h_fUnfProf->Fill(xBins[i-1],(fUnf[ipt]->GetBinContent(i)-fGen->GetBinContent(i))/fGen->GetBinContent(i));

  //    //Fout<<i<<"\t"<<dUnf[ipt]->GetBinContent(i)<<" +/- "<<dUnf[ipt]->GetBinError(i)<<"\t"<<dUnf[ipt]->GetBinContent(i)/dGen->GetBinContent(i)<<"\t\t"<<fUnf[ipt]->GetBinContent(i)<<" +/- "<<fUnf[ipt]->GetBinError(i)<<"\t"<<fUnf[ipt]->GetBinContent(i)/fGen->GetBinContent(i)<<endl;
  //  }
  //  Fout<<ipt<<"\t"<<dUnf[ipt]->GetBinContent(1)<<"\t"<<dGen->GetBinContent(1)<<"\t"<<(dUnf[ipt]->GetBinContent(1)-dGen->GetBinContent(1))/dGen->GetBinContent(1)<<endl;
  //}
  //h_dUnfProf->Draw();
  //TString tmpTStr = BaseName+"_hProf_detUnf.png";
  //c1->SaveAs(tmpTStr);
  //
  //h_fUnfProf->Draw();
  //TString tmpTStr = BaseName+"_hProf_fsrUnf.png";
  //c1->SaveAs(tmpTStr);
  
  lPowheg = (TH1D*)fToy->Get("hGenFSRNorm")->Clone();
  lData   = (TH1D*)fToy->Get("SVD_Born.FSRUnf_0")->Clone();
  //lData   = (TH1D*)fToy->Get("SVD_Post.DetUnf_0")->Clone();
  
  for( int ipt(1);ipt<=nBins-1;ipt++)
  {
    //cout<<ipt<<"\t"<<dUnf->GetBinContent(ipt)<<"\t"<<dGen->GetBinContent(ipt)<<"\t"<<dUnf->GetBinContent(ipt)/dGen->GetBinContent(ipt)<<"\t\t"<<fUnf->GetBinContent(ipt)<<"\t"<<fGen->GetBinContent(ipt)<<"\t"<<fUnf->GetBinContent(ipt)/fGen->GetBinContent(ipt)<<endl;
    //cout<<ipt<<"\t"<<lData->GetBinContent(ipt)<<"\t"<<lPowheg->GetBinContent(ipt)<<"\t"<<lData->GetBinContent(ipt)/lPowheg->GetBinContent(ipt)<<endl;
    //cout<<ipt<<"\t"<<lDet->GetBinContent(ipt)<<"\t"<<lTruthRec->GetBinContent(ipt)<<endl;
    hPowhegLog->SetBinContent(ipt,lPowheg->GetBinContent(ipt));
    hPowhegLog->SetBinError(ipt,lPowheg->GetBinError(ipt));
    
    hDataLog->SetBinContent(ipt,lData->GetBinContent(ipt));
    hDataLog->SetBinError(ipt,lData->GetBinError(ipt));
  }

  hDataLog->SetMarkerStyle(kFullCircle); hDataLog->SetMarkerColor(kBlack); hDataLog->SetMarkerSize(1);

  hPowhegLog->SetLineColor(kRed);
  
  TLegend *lL =new TLegend(0.6,0.65,0.92,0.85); lL->SetFillColor(0); lL->SetBorderSize(0);
  lL->AddEntry(hDataLog,"Unfolded","PL");
  lL->AddEntry(hPowhegLog,"Norm. Gen.","L");
  //lL->AddEntry(hPowhegLog,"h1_Truth_Post","L");

  TPaveText *tb = new TPaveText(0.6,0.44,0.9,0.58,"NDC");
  tb->SetBorderSize(0);
  tb->SetFillStyle(0);
  //tb->AddText("18.43 pb^{-1} at #sqrt{s} = 8 TeV");
  if (BaseName=="WpToMuNu")
    tb->AddText("W^{+} #rightarrow #mu^{+} #nu");
  if (BaseName=="WmToMuNu")
    tb->AddText("W^{-} #rightarrow #mu^{-} #bar{#nu}");
  if (BaseName=="WInclToMuNu")
    tb->AddText("W #rightarrow #mu #nu");
  if (BaseName=="WpToEleNu")
    tb->AddText("W^{+} #rightarrow e^{+} #nu");
  if (BaseName=="WmToEleNu")
    tb->AddText("W^{-} #rightarrow e^{-} #bar{#nu}");
  if (BaseName=="WInclToEleNu")
    tb->AddText("W #rightarrow e #nu");

  TCanvas *lC0 = new TCanvas("Can","Can",800,800); lC0->cd(); lC0->SetLogy();
  lC0->Divide(1,2,0,0);
  lC0->cd(1)->SetPad(0,0.35,0.95,1.0);
  lC0->cd(1)->SetTopMargin(0.1);
  lC0->cd(1)->SetBottomMargin(0.01);
  lC0->cd(1)->SetLeftMargin(0.15);
  lC0->cd(1)->SetRightMargin(0.07);
  lC0->cd(1)->SetTickx(1);
  lC0->cd(1)->SetTicky(1);
  //lC0->SetLogx(1);
  gStyle->SetLineWidth(2.);
  gStyle->SetOptStat(0);
  gStyle->SetHatchesSpacing(0.75);
  gStyle->SetHatchesLineWidth(2);
  gPad->SetLogx(1);
  //gPad->SetLogy(1);

  //hPowheg->GetYaxis()->SetRangeUser(0.,1.14*resb30[0]);
  hPowhegLog->SetTitle("");
  hPowhegLog->GetYaxis()->SetTitle("Events");
  hPowhegLog->GetYaxis()->SetTitleOffset(1.2);
  //hPowheg->SetMaximum(1.1*(hResbosLog30->GetBinContent(1)));
  
  hPowhegLog->Draw("HIST");
  hDataLog->Draw("ESAME");
  lL->Draw();
  tb->Draw();

  lC0->cd(2)->SetPad(0,0,0.95,0.34);
  lC0->cd(2)->SetTopMargin(0.025);
  lC0->cd(2)->SetBottomMargin(0.3);
  lC0->cd(2)->SetLeftMargin(0.15);
  lC0->cd(2)->SetRightMargin(0.07);
  lC0->cd(2)->SetTickx(1);
  lC0->cd(2)->SetTicky(1);
  lC0->cd(2)->SetLogx(1);
  drawDifference(hDataLog,hPowhegLog);
  lC0->SaveAs(BaseName+"_combining.png");
  return 0;
}
