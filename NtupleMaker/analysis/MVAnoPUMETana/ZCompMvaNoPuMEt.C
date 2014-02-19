#include <TLatex.h>

//const int   nptBins  =   9;
//double xbins_pt[nptBins+1] = {0.0, 7.5, 12.5, 17.5, 24,30,40,50,70,110,150,190,250,600};
TH1D *drawDifference(TH1D *hTrue,TH1D *hist,const TString YLabel,const Double_t range,const Int_t nMarker,const Int_t nColor);

TH1D *drawDifference(TH1D *hTrue,TH1D *hist, const TString YLabel,const Double_t range,const Int_t nMarker,const Int_t nColor)
{
  TH1D *hDiff = new TH1D(YLabel,"",20,0,100); hDiff->Sumw2();
  Double_t diff,ratio,errDiff,errSubtr,errTrue;

  TAxis *xaxis = hTrue->GetXaxis();
  for(int ibin=1; ibin<=hTrue->GetNbinsX(); ibin++) {
    diff = hist->GetBinContent(ibin)-hTrue->GetBinContent(ibin);
    if (hTrue->GetBinContent(ibin)==0){
      ratio=hist->GetBinContent(ibin);
      errSubtr = hTrue->GetBinError(ibin);
      //errDiff=sqrt(errSubtr);
      errDiff=errSubtr;
    }else{
      ratio = diff/hTrue->GetBinContent(ibin);
      errSubtr = sqrt(hTrue->GetBinError(ibin)*hTrue->GetBinError(ibin)+hist->GetBinError(ibin)*hist->GetBinError(ibin));
      errTrue = hTrue->GetBinError(ibin);
      errDiff=ratio*errSubtr/diff;
    }
    hDiff->SetBinContent(ibin,ratio);
    hDiff->SetBinError(ibin,errDiff);
  }
  hDiff->GetYaxis()->SetRangeUser(-2,range);
  hDiff->GetYaxis()->SetTitleOffset(0.6);
  hDiff->GetYaxis()->SetTitleSize(0.08);
  hDiff->GetYaxis()->SetLabelSize(0.08);
  hDiff->GetYaxis()->CenterTitle();
  hDiff->GetXaxis()->SetTitleOffset(1.2);
  hDiff->GetXaxis()->SetTitleSize(0.10);
  hDiff->GetXaxis()->SetLabelSize(0.04);
  hDiff->GetXaxis()->SetTitle("#slash{E}_{T} [GeV]");
  hDiff->GetYaxis()->SetTitle(YLabel);
  
  hDiff->SetMarkerStyle(nMarker);
  hDiff->SetMarkerColor(nColor);
  hDiff->SetLineColor(nColor);
  hDiff->SetMarkerSize(0.9);

  return hDiff;
}

void Difference(TH1* iH0,TH1 *iH1) {
  std::string lName = std::string(iH0->GetName());
  //TH1F *lHDiff  = new TH1F((lName+"Diff").c_str(),(lName+"Diff").c_str(),50,0,300); lHDiff->Sumw2();
  TH1F *lHDiff  = new TH1F((lName+"Diff").c_str(),(lName+"Diff").c_str(),iH0->GetNbinsX(),iH0->GetXaxis()->GetXmin(),iH0->GetXaxis()->GetXmax()); lHDiff->Sumw2();
  lHDiff->SetFillColor(kViolet); lHDiff->SetFillStyle(1001); lHDiff->SetLineWidth(1);
  TH1F *lXHDiff1 = new TH1F((lName+"XDiff1").c_str(),(lName+"XDiff1").c_str(),iH0->GetNbinsX(),iH0->GetXaxis()->GetXmin(),iH0->GetXaxis()->GetXmax());
  int i1 = 0;
  lXHDiff1->SetLineStyle(2); lXHDiff1->SetLineWidth(2); lXHDiff1->SetLineColor(kRed);

  lHDiff->GetYaxis()->SetRangeUser(0,2);
  lHDiff->GetYaxis()->SetTitleOffset(0.6);
  lHDiff->GetYaxis()->SetTitleSize(0.08);
  lHDiff->GetYaxis()->SetLabelSize(0.08);
  lHDiff->GetYaxis()->CenterTitle();
  lHDiff->GetXaxis()->SetTitleOffset(1.2);
  lHDiff->GetXaxis()->SetTitleSize(0.10);
  lHDiff->GetXaxis()->SetLabelSize(0.08);
  lHDiff->GetXaxis()->SetTitle("#slash{E}_{T} [GeV]");
  //lHDiff->GetXaxis()->CenterTitle();
  //lHDiff->GetYaxis()->SetTitle(YLabel);

  for(int i0 = 0; i0 < lHDiff->GetNbinsX()+1; i0++) {
    double lXCenter = lHDiff->GetBinCenter(i0);
    double lXVal     = iH0   ->GetBinContent(i0);
    lXHDiff1->SetBinContent(i0, 1.0);
    while(iH1->GetBinCenter(i1) < lXCenter) {i1++;}
    if(iH1->GetBinContent(i0) > 0) lHDiff->SetBinContent(i0,(lXVal-iH1->GetBinContent(i0))/(iH1->GetBinContent(i0)));
    if(iH1->GetBinContent(i0) > 0) lHDiff->SetBinError  (i0,iH0->GetBinError(i0)/(iH1->GetBinContent(i0)));
  }
  lHDiff->SetMarkerStyle(kFullCircle); lHDiff->SetLineColor(kBlack); lHDiff->SetMarkerColor(kBlack);
  lHDiff->Draw("E1");
  lXHDiff1->Draw("hist sames");
}

void ZCompMvaNoPuMEt()
{
  InpFile = new TFile("MuonHighPU/Muon_DYJetsToLL_S10_MVAnoPUMEt.root");
  //InpFile = new TFile("ElectronHighPU/Ele_DYJetsToLL_S10_MVAnoPUMEt.root");
  //InpFile = new TFile("TauHighPU/Tau_DYJetsToLL_S10_MVAnoPUMEt.root");

  char ylabel[100];
  char histName[100];
  char histName_org[100];
  
  TH1D *diff1[4];
  TH1D *diff2[4];
  TH1D *diff3[4];
  
  TH1D *met[4];
  TH1D *NoPUmet[4];
  TH1D *MVAmet[4];
  TH1D *GENmet[4];
  TH1D *GENmetTrue[4];

  Double_t Range;
 
  ////==============================
  ////PU distribution
  //TCanvas c1("c1","c1",800,700);
  //gStyle->SetOptTitle(0);
  //hPU =(TH1D*)InpFile->Get("h1_Vtx_Good1")->Clone();
  //
  //Double_t PURange=1.1*hPU->GetMaximum();
  //sprintf(ylabel,"Events / %.1f GeV",hPU->GetBinWidth(1));
  //hPU->GetYaxis()->SetTitle(ylabel);
  //hPU->GetYaxis()->SetTitleOffset(1.2);
  //hPU->GetYaxis()->SetTitleSize(0.04);
  //hPU->GetYaxis()->SetLabelSize(0.04);
  //hPU->GetYaxis()->SetRangeUser(0,PURange);
  //hPU->GetXaxis()->SetTitleOffset(1.1);
  //hPU->GetXaxis()->SetTitleSize(0.04);
  //hPU->GetXaxis()->SetLabelSize(0.04);
  //hPU->GetXaxis()->SetTitle("PU");
  //hPU->Draw();
  //TLine l1(7,0,7,PURange);
  //l1.SetLineColor(kRed);
  //l1.SetLineStyle(9);
  //l1.Draw();
  //TLine l2(22,0,22,PURange);
  ////TLine l2(26,0,26,PURange); //Tau channel
  //l2.SetLineColor(kRed);
  //l2.SetLineStyle(9);
  //l2.Draw();
  //c1.SaveAs("PileUpDostribution.png");
  ////==============================
  
  for(int i(0);i<4;i++)
  {
    sprintf(histName,"met_%d",i);
    sprintf(histName_org,"h1_Z_Met_%d",i);
    met[i] =(TH1D*)InpFile->Get(histName_org)->Clone(histName);met[i]->Sumw2();
    
    sprintf(histName,"NoPUmet_%d",i);
    sprintf(histName_org,"h1_Z_NoPU_Met_%d",i);
    NoPUmet[i] =(TH1D*)InpFile->Get(histName_org)->Clone(histName);NoPUmet[i]->Sumw2();
    
    sprintf(histName,"MVAmet_%d",i);
    sprintf(histName_org,"h1_Z_MVA_Met_%d",i);
    MVAmet[i] =(TH1D*)InpFile->Get(histName_org)->Clone(histName);MVAmet[i]->Sumw2();

    sprintf(histName,"GENmet_%d",i);
    sprintf(histName_org,"h1_Z_Gen_Met_%d",i);
    GENmet[i] =(TH1D*)InpFile->Get(histName_org)->Clone(histName);GENmet[i]->Sumw2();

    sprintf(histName,"GENmetTrue_%d",i);
    sprintf(histName_org,"h1_Z_genMEtTrue_%d",i);
    GENmetTrue[i] =(TH1D*)InpFile->Get(histName_org)->Clone(histName);GENmetTrue[i]->Sumw2();

    //met =(TH1D*)InpFile->Get("h1_W_Met_0")->Clone();
    //NoPUmet =(TH1D*)InpFile->Get("h1_W_NoPU_Met_0")->Clone();
    //MVAmet =(TH1D*)InpFile->Get("h1_W_MVA_Met_0")->Clone();
    //GENmet =(TH1D*)InpFile->Get("h1_W_Gen_Met_0")->Clone();
    //GENmetTrue =(TH1D*)InpFile->Get("h1_W_genMEtTrue_0")->Clone();

    //met =(TH1D*)InpFile->Get("h1_Z_Met")->Clone();
    //NoPUmet =(TH1D*)InpFile->Get("h1_Z_NoPU_Met")->Clone();
    //MVAmet =(TH1D*)InpFile->Get("h1_Z_MVA_Met")->Clone();

    met[i]->SetFillStyle(3004);
    met[i]->SetLineWidth(2);
    met[i]->SetLineColor(kYellow+1);
    met[i]->SetFillColor(kYellow);
    NoPUmet[i]->SetFillStyle(3005);
    NoPUmet[i]->SetLineWidth(2);
    NoPUmet[i]->SetLineColor(kRed+1);
    NoPUmet[i]->SetFillColor(kRed);
    MVAmet[i]->SetFillStyle(3013);
    MVAmet[i]->SetLineWidth(2);
    MVAmet[i]->SetLineColor(kBlue+3);
    MVAmet[i]->SetFillColor(kBlue);
    //GENmet->SetLineColor(kCyan);
    //GENmetTrue[i]->SetFillStyle(4050);
    GENmetTrue[i]->SetFillStyle(1001);
    GENmetTrue[i]->SetLineWidth(2);
    GENmetTrue[i]->SetLineColor(kGreen+3);
    GENmetTrue[i]->SetFillColor(kGreen);
  
    //sprintf(ylabel,"Events / %.1f GeV",NoPUmet->GetBinWidth(1));
    //NoPUmet->GetYaxis()->SetTitle(ylabel);
    //NoPUmet->GetYaxis()->SetTitleOffset(1.2);
    //NoPUmet->GetYaxis()->SetTitleSize(0.04);
    //NoPUmet->GetYaxis()->SetLabelSize(0.04);
    
    //sprintf(ylabel,"Events / %.1f GeV",MVAmet[i]->GetBinWidth(1));
    //MVAmet[i]->GetYaxis()->SetTitle(ylabel);
    //MVAmet[i]->GetYaxis()->SetTitleOffset(1.2);
    //MVAmet[i]->GetYaxis()->SetTitleSize(0.04);
    //MVAmet[i]->GetYaxis()->SetLabelSize(0.04);
    
    //sprintf(ylabel,"Events / %.1f GeV",GENmet[i]->GetBinWidth(1));
    //GENmet[i]->GetYaxis()->SetTitle(ylabel);
    //GENmet[i]->GetYaxis()->SetTitleOffset(1.2);
    //GENmet[i]->GetYaxis()->SetTitleSize(0.04);
    //GENmet[i]->GetYaxis()->SetLabelSize(0.04);
    
    sprintf(ylabel,"Events / %.1f GeV",GENmetTrue[i]->GetBinWidth(1));
    GENmetTrue[i]->GetYaxis()->SetTitle(ylabel);
    GENmetTrue[i]->GetYaxis()->SetTitleOffset(1.2);
    GENmetTrue[i]->GetYaxis()->SetTitleSize(0.04);
    GENmetTrue[i]->GetYaxis()->SetLabelSize(0.04);

    TLegend *lL =new TLegend(0.7,0.7,0.9,0.85);
    lL->SetFillColor(0); lL->SetBorderSize(0);
    lL->AddEntry(MVAmet[i],"MVA Met","F");
    //lL->AddEntry(GENmet,"Gen Met","L");
    lL->AddEntry(NoPUmet[i],"No PU Met","F");
    lL->AddEntry(met[i],"PFMet","F");
    lL->AddEntry(GENmetTrue[i],"GenMetTrue","F");
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
    gStyle->SetLabelSize(0.08,"xy");
    gStyle->SetTitleSize(0.08,"xy");
    gStyle->SetTitleOffset(1.2,"x");
    gStyle->SetTitleOffset(1.0,"y");
    gStyle->SetOptTitle(0);
    TGaxis::SetMaxDigits(3);

    //gPad->SetLogy(1);
    //GENmet->Draw("hist");
    GENmetTrue[i]->Draw("hist");
    //GENmetTrue[i]->Draw();
    //MVAmet->Draw("hist");
    //NoPUmet->Draw("hist");
    NoPUmet[i]->Draw("hist same");
    MVAmet[i]->Draw("hist same");
   //GENmet->Draw("hist same");
    met[i]->Draw("hist same");
    lL->Draw();
  
    lC0->cd(2)->SetPad(0,0,0.95,0.35);
    lC0->cd(2)->SetTopMargin(0.025);
    lC0->cd(2)->SetBottomMargin(0.3);
    lC0->cd(2)->SetLeftMargin(0.15);
    lC0->cd(2)->SetRightMargin(0.07);
    lC0->cd(2)->SetTickx(1);
    lC0->cd(2)->SetTicky(1);

    //Set maximum value of Y axis range in Resolution distribution 
    if (i==0 || i==2) Range=10;
    if (i==1) Range=10;
    if (i==3) Range=60;

    diff1[i] = drawDifference(GENmetTrue[i],NoPUmet[i],"Resolution",Range,20,2);
    diff1[i]->Draw("EX0");
    diff1[i]->Draw("SAME Lhist");
    
    diff2[i] = drawDifference(GENmetTrue[i],MVAmet[i],"",Range,21,4);
    diff2[i]->Draw("SAME EX0");
    diff2[i]->Draw("SAME Lhist");
    
    diff3[i] = drawDifference(GENmetTrue[i],met[i],"",Range,22,5);
    diff3[i]->Draw("SAME EX0");
    diff3[i]->Draw("SAME Lhist");
    
    TLegend *rL =new TLegend(0.6,0.63,0.9,0.95);
    //TLegend *rL =new TLegend(0.2,0.63,0.5,0.95);
    rL->SetFillColor(0); rL->SetBorderSize(0);
    rL->AddEntry(diff1[i],"(NoPUmet-genMEtTrue)/genMEtTrue","PL");
    rL->AddEntry(diff2[i],"(MVAmet-genMEtTrue)/genMEtTrue","PL");
    rL->AddEntry(diff3[i],"(PFmet-genMEtTrue)/genMEtTrue","PL");
    rL->Draw();

    TLine *line = new TLine(0,0,100,0);
    line->SetLineStyle(2);
    line->SetLineColor(8);
    line->Draw();
  
    sprintf(histName,"ZMetComp_DYJetsToLL_%d.png",i);
    lC0->SaveAs(histName);
  }
}
