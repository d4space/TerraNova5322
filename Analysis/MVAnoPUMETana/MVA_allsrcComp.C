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

void MVA_allsrcComp()
{
  //InpFile = new TFile("../srcbatch/scTTMuon/TTsemiMuon.root");
  //InpFile = new TFile("../srcbatch/scTTElectron/TTsemiElectron.root");
  //InpFile = new TFile("../srcbatch/MonoJet_MET/MonoJet.root");
  InpFile = new TFile("../srcbatch/mSUGRA_MET/mSUGRA.root");
  //InpFile = new TFile("../srcbatch/scTT2Hadron/TT2Hadron.root");
  //InpFile = new TFile("../srcbatch/scWToENu/WToENu.root");
  //InpFile = new TFile("../srcbatch/scWToMuNu/WToMuNu.root");
  //InpFile = new TFile("../srcbatch/scDYElEl/DYElEl.root");
  //InpFile = new TFile("../srcbatch/scDYMuMu/DYMuMu.root");
  //InpFile = new TFile("../srcbatch/scZZ4Mu/ZZ4Mu.root");
  //InpFile = new TFile("../srcbatch/scZZ4El/ZZ4El.root");
  //InpFile = new TFile("../srcbatch/scZZMuEl/ZZMuEl.root");
  //InpFile = new TFile("../srcbatch/ZZ2Mu2Nu_MET/ZZ2Mu2Nu.root");
  //InpFile = new TFile("../srcbatch/ZZ2El2Nu_MET/ZZ2El2Nu.root");
  //InpFile = new TFile("../srcbatch/scWW/WW.root");
  //InpFile = new TFile("../srcbatch/scWZ/WZ.root");
  //InpFile = new TFile("../srcbatch/scMonoPhoton/MonoPhoton.root");
  
  //InpFileall = new TFile("../allbatch/TTsemiMuon_MET/TTsemiMuon.root");
  //InpFileall = new TFile("../allbatch/TTsemiElectron_MET/TTsemiElectron.root");
  //InpFileall = new TFile("../allbatch/MonoJet_MET/MonoJet.root");
  InpFileall = new TFile("../allbatch/mSUGRA_MET/mSUGRA.root");
  //InpFileall = new TFile("../allbatch/TT2Hadron_MET/TT2Hadron.root");
  //InpFileall = new TFile("../allbatch/WToENu_MET/WToENu.root");
  //InpFileall = new TFile("../allbatch/WToMuNu_MET/WToMuNu.root");
  //InpFileall = new TFile("../allbatch/DYElEl_MET/DYElEl.root");
  //InpFileall = new TFile("../allbatch/DYMuMu_MET/DYMuMu.root");
  //InpFileall = new TFile("../allbatch/ZZ4Mu_MET/ZZ4Mu.root");
  //InpFileall = new TFile("../allbatch/ZZ4El_MET/ZZ4El.root");
  //InpFileall = new TFile("../allbatch/ZZMuEl_MET/ZZMuEl.root");
  //InpFileall = new TFile("../allbatch/ZZ2Mu2Nu_MET/ZZ2Mu2Nu.root");
  //InpFileall = new TFile("../allbatch/ZZ2El2Nu_MET/ZZ2El2Nu.root");
  //InpFileall = new TFile("../allbatch/WW_MET/WW.root");
  //InpFileall = new TFile("../allbatch/WZ_MET/WZ.root");
  //InpFileall = new TFile("../allbatch/MonoPhoton_MET/MonoPhoton.root");

  char ylabel[100];
  char histName[100];
  char histName_org[100];
  
  TH1D *pfMet;
  TH1D *NoPUmet;
  TH1D *MVAmet;
  TH1D *NoPUmetall;
  TH1D *MVAmetall;
 
    sprintf(histName,"pfMet");
    sprintf(histName_org,"pfMET_3");
    pfMet =(TH1D*)InpFile->Get(histName_org)->Clone(histName);pfMet->Sumw2();
    
    sprintf(histName,"NoPUmet");
    sprintf(histName_org,"NoPuMET_3");
    NoPUmet =(TH1D*)InpFile->Get(histName_org)->Clone(histName);NoPUmet->Sumw2();
    
    sprintf(histName,"NoPUmetall");
    sprintf(histName_org,"NoPuMET_3");
    NoPUmetall =(TH1D*)InpFileall->Get(histName_org)->Clone(histName);NoPUmetall->Sumw2();
    
    sprintf(histName,"MVAmet");
    sprintf(histName_org,"MVaMET_3");
    MVAmet =(TH1D*)InpFile->Get(histName_org)->Clone(histName);MVAmet->Sumw2();

    sprintf(histName,"MVAmetall");
    sprintf(histName_org,"MVaMET_3");
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
   
    //MVAmet->GetYaxis()->SetRangeUser(-15,30);//WJet TTsemiPU012
    //MVAmet->GetYaxis()->SetRangeUser(-25,30);// TTsemiPU3
    //MVAmet->GetYaxis()->SetRangeUser(-20,30);//WW
    
    //MVAmet->GetYaxis()->SetRangeUser(-5,20);//WZ   1
    //MVAmet->GetYaxis()->SetRangeUser(-15,25);//WZ  0,2
    //MVAmet->GetYaxis()->SetRangeUser(-20,35);//WZ  3
    
    //MVAmet->GetYaxis()->SetRangeUser(-15,30);//W
    //MVAmet->GetYaxis()->SetRangeUser(-20,30);//W muon3
    
    //MVAmet->GetYaxis()->SetRangeUser(-20,55);//ZZ4El
    
    //MVAmet->GetYaxis()->SetRangeUser(-25,55);//ZZ4Mu012
    //MVAmet->GetYaxis()->SetRangeUser(-25,65);//ZZ4Mu3
    
    //MVAmet->GetYaxis()->SetRangeUser(-70,70);//ZZMuEl 1
    //MVAmet->GetYaxis()->SetRangeUser(-30,40);//ZZMuEl 0 2
    //MVAmet->GetYaxis()->SetRangeUser(-50,50);//ZZMuEl 3
    
    //MVAmet->GetYaxis()->SetRangeUser(-30,30);//ZZ2El2Nu  0 2
    //MVAmet->GetYaxis()->SetRangeUser(-50,70);//ZZ2El2Nu  3
    //MVAmet->GetYaxis()->SetRangeUser(-30,60);//ZZ2El2Nu  1
    
    //MVAmet->GetYaxis()->SetRangeUser(-20,30);//DY 012
    //MVAmet->GetYaxis()->SetRangeUser(-30,60);//DYmuon1
    //MVAmet->GetYaxis()->SetRangeUser(-40,70);//DYele3
    //MVAmet->GetYaxis()->SetRangeUser(-50,85);//DYmuon3
    
    //MVAmet->GetYaxis()->SetRangeUser(-10,35);//TThadron
    //MVAmet->GetYaxis()->SetRangeUser(0,700);//monoJet
    
    //MVAmet->GetYaxis()->SetRangeUser(-230,200);//mSUGRA 0
    //MVAmet->GetYaxis()->SetRangeUser(-170,240);//mSUGRA 1
    //MVAmet->GetYaxis()->SetRangeUser(-190,190);//mSUGRA 2
    MVAmet->GetYaxis()->SetRangeUser(-170,230);//mSUGRA 3
    
    //MVAmet->GetYaxis()->SetRangeUser(-50,1000);//monoPhoton0
    //MVAmet->GetYaxis()->SetRangeUser(-50,1300);//monoPhoton2
    //MVAmet->GetYaxis()->SetRangeUser(-50,750);//monoPhoton13
    
    //MVAmet->GetXaxis()->SetRangeUser(0,75);//X-axis 80

    TCanvas c1("c1","c1",800,700);
    gStyle->SetOptTitle(0);

    MVAmet->Draw("E1");
    pfMet->Draw("E1 same");
    NoPUmet->Draw("E1 same");
    MVAmetall->Draw("E1 same");
    NoPUmetall->Draw("E1 same");
    
    TLegend *rL =new TLegend(0.55,0.68,0.99,0.95);
    rL->SetFillColor(0); rL->SetBorderSize(0);
    rL->AddEntry(pfMet,"pfMet","PL");
    rL->AddEntry(NoPUmet,"NoPU_wSrcLept","PL");
    rL->AddEntry(NoPUmetall,"NoPU_wAllSrcLept","PL");
    rL->AddEntry(MVAmet,"MVA_wSrcLept","PL");
    rL->AddEntry(MVAmetall,"MVA_wAllSrcLept","PL");
    rL->Draw();
 
    //midile line
    //TLine line(0,0,200,0);//TTsemi
    //TLine line(0,0,300,0);//ZZ2Lept2Nu
    //TLine line(0,0,100,0);
    TLine line(0,0,1500,0);//mSUGRA
    //TLine line(0,0,80,0);//ZZ4Mu ZZMuEl MonoPhoton
    line->Draw();
    
    //All 0To7 7To21 21To
    //sprintf(histName,"muonTTJetsemiLept_PURange_21to.png");
    //sprintf(histName,"electronTTJetsemiLept_PURange_21to.png");
    //sprintf(histName,"monoJet_PURange_21to.png");
    sprintf(histName,"mSUGRA_PURange_21to.png");
    //sprintf(histName,"hadronTT2hadron_PURange_21to.png");
    //sprintf(histName,"electronWToENu_PURange_21to.png");
    //sprintf(histName,"muonWToMuNu_PURange_21to.png");
    //sprintf(histName,"electronDYElEl_PURange_21to.png");
    //sprintf(histName,"muonDYMuNu_PURange_21to.png");
    //sprintf(histName,"ZZ4Mu_PURange_21to.png");
    //sprintf(histName,"ZZ4El_PURange_21to.png");
    //sprintf(histName,"ZZ2Mu2El_PURange_21to.png");
    //sprintf(histName,"ZZ2Mu2Nu_PURange_21to.png");
    //sprintf(histName,"ZZ2El2Nu_PURange_21to.png");
    //sprintf(histName,"WW_PURange_21to.png");
    //sprintf(histName,"WZ_PURange_21to.png");
    //sprintf(histName,"monoPhoton_PURange_21to.png");
    c1.SaveAs(histName);

}
