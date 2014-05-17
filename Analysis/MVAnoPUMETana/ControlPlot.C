#include <TLatex.h>
void ControlPlot()
{
  InpFile = new TFile("../allbatch_v2_bin40/TTsemiMuon_MET/TTsemiMuon.root");
  //InpFile = new TFile("../allbatch/TTsemiElectron_MET/TTsemiElectron.root");
  //InpFile = new TFile("../allbatch/MonoJet_MET/MonoJet.root");
  //InpFile = new TFile("../allbatch/TT2Hadron_MET/TT2Hadron.root");
  //InpFile = new TFile("../allbatch/WToENu_MET/WToENu.root");
  //InpFile = new TFile("../allbatch/WToMuNu_MET/WToMuNu.root");
  //InpFile = new TFile("../allbatch/DYElEl_MET/DYElEl.root");
  //InpFile = new TFile("../allbatch/DYMuMu_MET/DYMuMu.root");
  //InpFile = new TFile("../allbatch/ZZ4Mu_MET/ZZ4Mu.root");
  //InpFile = new TFile("../allbatch/ZZ4El_MET/ZZ4El.root");
  //InpFile = new TFile("../allbatch/ZZMuEl_MET/ZZMuEl.root");
  //InpFile = new TFile("../allbatch/ZZ2Mu2Nu_MET/ZZ2Mu2Nu.root");
  //InpFile = new TFile("../allbatch/ZZ2El2Nu_MET/ZZ2El2Nu.root");
  //InpFile = new TFile("../allbatch/WW_MET/WW.root");
  //InpFile = new TFile("../allbatch/WZ_MET/WZ.root");
  //InpFile = new TFile("../allbatch/MonoPhoton_MET/MonoPhoton.root");

  char ylabel[100];
  char histName[100];
  char histName_org[100];

  TH2D *NoPuMET;

  sprintf(histName,"NoPuMET");
  sprintf(histName_org,"h2_NoPuMET_pxpy");
  NoPuMET =(TH2D*)InpFile->Get(histName_org)->Clone(histName);NoPuMET->Sumw2();

  sprintf(ylabel,"py",NoPuMET->GetBinWidth(1));
  NoPuMET->GetYaxis()->SetTitle(ylabel);
  NoPuMET->GetYaxis()->SetTitleOffset(1.2);
  NoPuMET->GetYaxis()->SetTitleSize(0.04);
  NoPuMET->GetYaxis()->SetLabelSize(0.04);
  NoPuMET->GetXaxis()->SetTitle("px");
  NoPuMET->GetXaxis()->SetTitleOffset(1.0);

  //NoPuMET->GetYaxis()->SetRangeUser(-500,500);//TT2Had
  //NoPuMET->GetXaxis()->SetRangeUser(-500,500);//TT2Had
 
  //NoPuMET->GetYaxis()->SetRangeUser(-600,600);//W WW
  //NoPuMET->GetXaxis()->SetRangeUser(-600,600);//W WW
  
  //NoPuMET->GetYaxis()->SetRangeUser(-700,700);//WZ
  //NoPuMET->GetXaxis()->SetRangeUser(-700,700);//WZ
  
  //NoPuMET->GetYaxis()->SetRangeUser(-500,500);//D
  //NoPuMET->GetXaxis()->SetRangeUser(-500,500);//D

  //NoPuMET->GetYaxis()->SetRangeUser(-200,200);//ZZ
  //NoPuMET->GetXaxis()->SetRangeUser(-200,200);//ZZ
  
  
  
  TCanvas c1("c1","c1",800,700);
  gStyle->SetOptTitle(0);

   //NoPuMET->Draw("CONT3");
   gStyle->SetPalette(1);
   NoPuMET->Draw("COL");

   TLegend *rL =new TLegend(0.75,0.68,0.99,0.95);
   rL->SetFillColor(0); rL->SetBorderSize(0);
   rL->AddEntry(NoPuMET,"NoPuMET","PL");
   rL->Draw();

   sprintf(histName,"muonTTJetsemiLept_NoPuMET.png");
   //sprintf(histName,"electronTTJetsemiLept_NoPuMET.png");
   //sprintf(histName,"monoJet_NoPuMET.png");
   //sprintf(histName,"hadronTT2hadron_NoPuMET.png");
   //sprintf(histName,"electronWToENu_NoPuMET.png");
   //sprintf(histName,"muonWToMuNu_NoPuMET.png");
   //sprintf(histName,"electronDYElEl_NoPuMET.png");
   //sprintf(histName,"muonDYMuNu_NoPuMET.png");
   //sprintf(histName,"ZZ4Mu_NoPuMET.png");
   //sprintf(histName,"ZZ4El_NoPuMET.png");
   //sprintf(histName,"ZZ2Mu2El_NoPuMET.png");
   //sprintf(histName,"ZZ2Mu2Nu_NoPuMET.png");
   //sprintf(histName,"ZZ2El2Nu_NoPuMET.png");
   //sprintf(histName,"WW_NoPuMET.png");
   //sprintf(histName,"WZ_NoPuMET.png");
   //sprintf(histName,"monoPhoton_NoPuMET.png");
   
   c1.SaveAs(histName);


}
