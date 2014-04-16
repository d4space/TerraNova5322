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
      errSubtr = sqrt(ratio);
      //errDiff=sqrt(errSubtr);
      errDiff=errSubtr;
    }else{
      ratio = diff/hTrue->GetBinContent(ibin);
      errSubtr = sqrt(hTrue->GetBinError(ibin)*hTrue->GetBinError(ibin)+hist->GetBinError(ibin)*hist->GetBinError(ibin));
      errTrue = hTrue->GetBinError(ibin);
      errDiff=ratio*errSubtr/diff;
      if (diff==0) errDiff = 0;
    }
    hDiff->SetBinContent(ibin,ratio);
    hDiff->SetBinError(ibin,errDiff);
  }
  //hDiff->GetYaxis()->SetRangeUser(-2,range);
  //hDiff->GetYaxis()->SetTitleOffset(0.6);
  //hDiff->GetYaxis()->SetTitleSize(0.08);
  //hDiff->GetYaxis()->SetLabelSize(0.08);
  //hDiff->GetYaxis()->CenterTitle();
  //hDiff->GetXaxis()->SetTitleOffset(1.2);
  //hDiff->GetXaxis()->SetTitleSize(0.10);
  //hDiff->GetXaxis()->SetLabelSize(0.04);
  //hDiff->GetXaxis()->SetTitle("#slash{E}_{T} [GeV]");
  //hDiff->GetYaxis()->SetTitle(YLabel);
  
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

  //lHDiff->GetYaxis()->SetRangeUser(0,2);
  //lHDiff->GetYaxis()->SetTitleOffset(0.6);
  //lHDiff->GetYaxis()->SetTitleSize(0.08);
  //lHDiff->GetYaxis()->SetLabelSize(0.08);
  //lHDiff->GetYaxis()->CenterTitle();
  //lHDiff->GetXaxis()->SetTitleOffset(1.2);
  //lHDiff->GetXaxis()->SetTitleSize(0.10);
  //lHDiff->GetXaxis()->SetLabelSize(0.08);
  //lHDiff->GetYaxis()->CenterTitle();
  //lHDiff->GetXaxis()->SetTitle("#slash{E}_{T} [GeV]");
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

void MVANoPUsrcleptComp()
{
  //InpFile = new TFile("/sc/scTTMuon/TTsemiMuon.root");
  //InpFile = new TFile("/sc/scTTElectron/TTsemiElectron.root");
  //InpFile = new TFile("/sc/scMonoJet/MonoJet.root");
  //InpFile = new TFile("/sc/scTT2Hadron/TT2Hadron.root");
  //InpFile = new TFile("/sc/scWToENu/WToENu.root");
  //InpFile = new TFile("/sc/scWToMuNu/WToMuNu.root");
  //InpFile = new TFile("/sc/scDYElEl/DYElEl.root");
  //InpFile = new TFile("/sc/scDYMuMu/DYMuMu.root");
  //InpFile = new TFile("/sc/scZZ4Mu/ZZ4Mu.root");
  //InpFile = new TFile("/sc/scZZ4El/ZZ4El.root");
  //InpFile = new TFile("/sc/scZZMuEl/ZZMuEl.root");
  //InpFile = new TFile("/sc/scWW/WW.root");
  InpFile = new TFile("/sc/scWZ/WZ.root");
  //InpFile = new TFile("/sc/scMonoPhoton/MonoPhoton.root");
  
  //InpFileall = new TFile("/all/allscTTMuon/TTsemiMuon.root");
  //InpFileall = new TFile("/all/allscTTElectron/TTsemiElectron.root");
  //InpFileall = new TFile("/all/allscMonoJet/MonoJet.root");
  //InpFileall = new TFile("/all/allscTT2Hadron/TT2Hadron.root");
  //InpFileall = new TFile("/all/allscWToENu/WToENu.root");
  //InpFileall = new TFile("/all/allscWToMuNu/WToMuNu.root");
  //InpFileall = new TFile("/all/allscDYElEl/DYElEl.root");
  //InpFileall = new TFile("/all/allscDYMuMu/DYMuMu.root");
  //InpFileall = new TFile("/all/allscZZ4Mu/ZZ4Mu.root");
  //InpFileall = new TFile("/all/allscZZ4El/ZZ4El.root");
  //InpFileall = new TFile("/all/allscZZMuEl/ZZMuEl.root");
  //InpFileall = new TFile("/all/allscWW/WW.root");
  InpFileall = new TFile("/all/allscWZ/WZ.root");
  //InpFileall = new TFile("/all/allscMonoPhoton/MonoPhoton.root");

  char ylabel[100];
  char histName[100];
  char histName_org[100];
  
  TH1D *pfMet;
  TH1D *NoPUmet;
  TH1D *MVAmet;
  TH1D *NoPUmetall;
  TH1D *MVAmetall;

    
    sprintf(histName,"pfMet");
    //sprintf(histName_org,"hp_pfMet");
    sprintf(histName_org,"pfMET");
    pfMet =(TH1D*)InpFile->Get(histName_org)->Clone(histName);pfMet->Sumw2();
    
    sprintf(histName,"NoPUmet");
    //sprintf(histName_org,"hp_NoPuMet");
    sprintf(histName_org,"NoPuMET");
    NoPUmet =(TH1D*)InpFile->Get(histName_org)->Clone(histName);NoPUmet->Sumw2();
    
    sprintf(histName,"NoPUmetall");
    sprintf(histName_org,"NoPuMET");
    NoPUmetall =(TH1D*)InpFileall->Get(histName_org)->Clone(histName);NoPUmetall->Sumw2();
    
    sprintf(histName,"MVAmet");
    //sprintf(histName_org,"hp_MVaMet");
    sprintf(histName_org,"MVaMET");
    MVAmet =(TH1D*)InpFile->Get(histName_org)->Clone(histName);MVAmet->Sumw2();

    sprintf(histName,"MVAmetall");
    sprintf(histName_org,"MVaMET");
    MVAmetall =(TH1D*)InpFileall->Get(histName_org)->Clone(histName);MVAmetall->Sumw2();

    pfMet->SetLineWidth(2);
    pfMet->SetLineColor(kBlack);
    pfMet->SetMarkerStyle(26);
    pfMet->SetMarkerColor(kBlack);
    NoPUmet->SetLineWidth(2);
    NoPUmet->SetLineColor(kRed);
    NoPUmet->SetMarkerStyle(kFullCircle);
    NoPUmet->SetMarkerColor(kRed);
    NoPUmetall->SetLineWidth(2);
    NoPUmetall->SetLineColor(kRed);
    NoPUmetall->SetMarkerStyle(kCircle);
    NoPUmetall->SetMarkerColor(kRed);
    MVAmet->SetLineWidth(2);
    MVAmet->SetLineColor(kBlue);
    MVAmet->SetMarkerStyle(kFullSquare);
    MVAmet->SetMarkerColor(kBlue);
    MVAmetall->SetLineWidth(2);
    MVAmetall->SetLineColor(kBlue);
    MVAmetall->SetMarkerStyle(25);
    MVAmetall->SetMarkerColor(kBlue);

    sprintf(ylabel,"MET-genMEtTrue",MVAmet->GetBinWidth(1));
    MVAmet->GetYaxis()->SetTitle(ylabel);
    MVAmet->GetYaxis()->SetTitleOffset(1.2);
    MVAmet->GetYaxis()->SetTitleSize(0.04);
    MVAmet->GetYaxis()->SetLabelSize(0.04);
    MVAmet->GetXaxis()->SetTitle("genMEt");
    MVAmet->GetXaxis()->SetTitleOffset(1.0);
    //MVAmet->GetXaxis()->SetTitleSize(0.13);

    //MVAmet->GetYaxis()->SetRangeUser(-15,30);//WJet TTsemi
    //MVAmet->GetYaxis()->SetRangeUser(-15,20);//WW
    MVAmet->GetYaxis()->SetRangeUser(-10,25);//WZ
    //MVAmet->GetYaxis()->SetRangeUser(-15,25);//W
    //MVAmet->GetYaxis()->SetRangeUser(-20,45);//ZZ4El
    //MVAmet->GetYaxis()->SetRangeUser(-35,35);//ZZ4Mu
    //MVAmet->GetYaxis()->SetRangeUser(-15,35);//ZZMuEl
    //MVAmet->GetYaxis()->SetRangeUser(-20,25);//DY
    //MVAmet->GetYaxis()->SetRangeUser(-10,35);//TThadron
    //MVAmet->GetYaxis()->SetRangeUser(0,900);//monoJet
    //MVAmet->GetYaxis()->SetRangeUser(0,750);//monoPhoton
    //MVAmet->GetXaxis()->SetRangeUser(0,80);//monoPhoton X

    TCanvas c1("c1","c1",800,700);
    gStyle->SetOptTitle(0);

    MVAmet->Draw("E1");
    pfMet->Draw("E1 same");
    NoPUmet->Draw("E1 same");
    MVAmetall->Draw("E1 same");
    NoPUmetall->Draw("E1 same");
    
    //TLegend *rL =new TLegend(0.55,0.70,0.90,0.85);
    TLegend *rL =new TLegend(0.45,0.75,0.90,0.95);
    //TLegend *rL =new TLegend(0.15,0.75,0.55,0.95);//MonoPhoton
    rL->SetFillColor(0); rL->SetBorderSize(0);
    rL->AddEntry(pfMet,"pfMet","PL");
    rL->AddEntry(NoPUmet,"NoPU_wSrcLept","PL");
    rL->AddEntry(NoPUmetall,"NoPU_wAllSrcLept","PL");
    rL->AddEntry(MVAmet,"MVA_wSrcLept","PL");
    rL->AddEntry(MVAmetall,"MVA_wAllSrcLept","PL");
    rL->Draw();
 
    //midile line
    //TLine line(0,0,200,0);//TTsemi
    TLine line(0,0,100,0);
    //TLine line(0,0,80,0);//ZZ4Mu ZZMuEl MonoPhoton
    line->Draw();
    

    //sprintf(histName,"NewmuonTTJetsemiLept.png");
    //sprintf(histName,"NewelectronTTJetsemiLept.png");
    //sprintf(histName,"NewmonoJet.png");
    //sprintf(histName,"NewhadronTT2hadron.png");
    //sprintf(histName,"NewelectronWToENu.png");
    //sprintf(histName,"NewmuonWToMuNu.png");
    //sprintf(histName,"NewelectronDYElEl.png");
    //sprintf(histName,"NewmuonDYMuNu.png");
    //sprintf(histName,"NewZZ4Mu.png");
    //sprintf(histName,"NewZZ4El.png");
    //sprintf(histName,"NewZZMuEl.png");
    //sprintf(histName,"NewWW.png");
    sprintf(histName,"NewWZ.png");
    //sprintf(histName,"NewmonoPhoton.png");
    c1.SaveAs(histName);
}
