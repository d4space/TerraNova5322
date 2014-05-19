#include <TLatex.h>
void ControlPlot()
{
  InpFile = new TFile("../allbatch/TTsemiMuon_MET/TTsemiMuon.root");
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

  TH2D *pfMET;

  sprintf(histName,"pfMET");
  sprintf(histName_org,"h2_pfMET_pxpy");
  pfMET =(TH2D*)InpFile->Get(histName_org)->Clone(histName);pfMET->Sumw2();

  sprintf(ylabel,"py",pfMET->GetBinWidth(1));
  pfMET->GetYaxis()->SetTitle(ylabel);
  pfMET->GetYaxis()->SetTitleOffset(1.2);
  pfMET->GetYaxis()->SetTitleSize(0.04);
  pfMET->GetYaxis()->SetLabelSize(0.04);
  pfMET->GetXaxis()->SetTitle("px");
  pfMET->GetXaxis()->SetTitleOffset(1.0);

  
  TCanvas c1("c1","c1",800,700);
  gStyle->SetOptTitle(0);

   //pfMET->Draw("CONT3");
   gStyle->SetPalette(1);
   pfMET->Draw("COL");

   TLegend *rL =new TLegend(0.75,0.68,0.99,0.95);
   rL->SetFillColor(0); rL->SetBorderSize(0);
   rL->AddEntry(pfMET,"pfMET","PL");
   rL->Draw();

   sprintf(histName,"muonTTJetsemiLept_pfMET.png");
   //sprintf(histName,"electronTTJetsemiLept_pfMET.png");
   //sprintf(histName,"monoJet_pfMET.png");
   //sprintf(histName,"hadronTT2hadron_pfMET.png");
   //sprintf(histName,"electronWToENu_pfMET.png");
   //sprintf(histName,"muonWToMuNu_pfMET.png");
   //sprintf(histName,"electronDYElEl_pfMET.png");
   //sprintf(histName,"muonDYMuNu_pfMET.png");
   //sprintf(histName,"ZZ4Mu_pfMET.png");
   //sprintf(histName,"ZZ4El_pfMET.png");
   //sprintf(histName,"ZZ2Mu2El_pfMET.png");
   //sprintf(histName,"ZZ2Mu2Nu_pfMET.png");
   //sprintf(histName,"ZZ2El2Nu_pfMET.png");
   //sprintf(histName,"WW_pfMET.png");
   //sprintf(histName,"WZ_pfMET.png");
   //sprintf(histName,"monoPhoton_pfMET.png");
   
   c1.SaveAs(histName);


}
