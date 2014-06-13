#include <TLatex.h>

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
    sprintf(histName_org,"pfMET_0");
    pfMet =(TH1D*)InpFile->Get(histName_org)->Clone(histName);pfMet->Sumw2();
    
    sprintf(histName,"NoPUmet");
    sprintf(histName_org,"NoPuMET_0");
    NoPUmet =(TH1D*)InpFile->Get(histName_org)->Clone(histName);NoPUmet->Sumw2();
    
    sprintf(histName,"NoPUmetall");
    sprintf(histName_org,"NoPuMET_0");
    NoPUmetall =(TH1D*)InpFileall->Get(histName_org)->Clone(histName);NoPUmetall->Sumw2();
    
    sprintf(histName,"MVAmet");
    sprintf(histName_org,"MVaMET_0");
    MVAmet =(TH1D*)InpFile->Get(histName_org)->Clone(histName);MVAmet->Sumw2();

    sprintf(histName,"MVAmetall");
    sprintf(histName_org,"MVaMET_0");
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
    
    MVAmet->GetYaxis()->SetRangeUser(-90,80);//mSUGRA 0
    //MVAmet->GetYaxis()->SetRangeUser(-130,110);//mSUGRA 1
    //MVAmet->GetYaxis()->SetRangeUser(-80,80);//mSUGRA 2
    //MVAmet->GetYaxis()->SetRangeUser(-140,130);//mSUGRA 3
    
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
    //sprintf(histName,"muonTTJetsemiLept_PURange_All.png");
    //sprintf(histName,"electronTTJetsemiLept_PURange_All.png");
    //sprintf(histName,"monoJet_PURange_All.png");
    sprintf(histName,"mSUGRA_PURange_All.png");
    //sprintf(histName,"hadronTT2hadron_PURange_All.png");
    //sprintf(histName,"electronWToENu_PURange_All.png");
    //sprintf(histName,"muonWToMuNu_PURange_All.png");
    //sprintf(histName,"electronDYElEl_PURange_All.png");
    //sprintf(histName,"muonDYMuNu_PURange_All.png");
    //sprintf(histName,"ZZ4Mu_PURange_All.png");
    //sprintf(histName,"ZZ4El_PURange_All.png");
    //sprintf(histName,"ZZ2Mu2El_PURange_All.png");
    //sprintf(histName,"ZZ2Mu2Nu_PURange_All.png");
    //sprintf(histName,"ZZ2El2Nu_PURange_All.png");
    //sprintf(histName,"WW_PURange_All.png");
    //sprintf(histName,"WZ_PURange_All.png");
    //sprintf(histName,"monoPhoton_PURange_All.png");
    c1.SaveAs(histName);

}
