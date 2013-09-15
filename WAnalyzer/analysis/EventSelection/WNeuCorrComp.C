#include "../Utils/MyTools.hh"
#include "../Utils/CPlot.hh"
#include "../Utils/MitStyleRemix.hh"
#include "../Utils/const.h"
#include <TFile.h>
//Make MET difference plots
void WNeuCorrComp(const TString Mode,//Channel - Muon or Electron
          const TString filetype, //Inclusive, Plus, Minus files
          const TString outputDir 
)
{
  TH1D* makeDiffHist(TH1D* h1, TH1D* h2, const TString name);
  const TString format("png"); 
  TFile *f_Org;
  TFile *f_Corr;
  TFile *f_Up;
  TFile *f_Down;
  gSystem->mkdir(outputDir,kTRUE);
  CPlot::sOutDir = outputDir;  
  if (Mode=="Muon")
     {
     if (filetype=="Inclusive")
     {
     f_Org  = new TFile("MuonLowPU/Muon_WToMuNu_S8_Analysis.root");
     f_Corr = new TFile("MuonLowPU/Muon_WToMuNu_S8_Nom_RecoilCorrMC.root");
     f_Up   = new TFile("MuonLowPU/Muon_WToMuNu_S8_Up_RecoilCorrMC.root");
     f_Down = new TFile("MuonLowPU/Muon_WToMuNu_S8_Down_RecoilCorrMC.root");
     }
  else if (filetype=="Plus")
    {
    f_Org  = new TFile("MuonLowPU/Muon_WpToMuNu_S8_Analysis.root");
    f_Corr = new TFile("MuonLowPU/Muon_WpToMuNu_S8_RecoilCorrMC.root");
    }
  else if (filetype=="Minus")
    {
    f_Org  = new TFile("MuonLowPU/Muon_WmToMuNu_S8_Analysis.root");
    f_Corr = new TFile("MuonLowPU/Muon_WmToMuNu_S8_RecoilCorrMC.root");
    }
    }
  else if (Mode=="Electron")
    {
    if (filetype=="Inclusive")
    {
    f_Org  = new TFile("ElectronLowPU/Ele_WToEleNu_S8_Analysis.root");
    f_Corr = new TFile("ElectronLowPU/Ele_WToEleNu_S8_Nom_RecoilCorrMC.root");
    f_Up   = new TFile("ElectronLowPU/Ele_WToEleNu_S8_Up_RecoilCorrMC.root");
    f_Down = new TFile("ElectronLowPU/Ele_WToEleNu_S8_Down_RecoilCorrMC.root");
    }
  else if (filetype=="Plus")
    {
    f_Org  = new TFile("ElectronLowPU/Ele_WpToEleNu_S8_Analysis.root");
    f_Corr = new TFile("ElectronLowPU/Ele_WpToEleNu_S8_RecoilCorrMC.root");
    }
  else if (filetype=="Minus")
    {
    f_Org  = new TFile("ElectronLowPU/Ele_WmToEleNu_S8_Analysis.root");
    f_Corr = new TFile("ElectronLowPU/Ele_WmToEleNu_S8_RecoilCorrMC.root");
    }
    }
  TH1D *hCorrDiff;
  CPlot *plotCorrDiff;
  CPlot *plotNeuComp;
  CPlot *plotNeuCompIncl;
  CPlot *plotNeuCompAll;

  Int_t ratioColor = kGray+2;
  Double_t METMAX;
  TH1D *hGen[NWptBinPlus];
  TH1D *hOrg[NWptBinPlus];
  TH1D *hCorr[NWptBinPlus];
  TH1D *hNom[NWptBinPlus];
  TH1D *hUp[NWptBinPlus];
  TH1D *hDown[NWptBinPlus];
  char histNameGen[30],histNameGenClone[30],histNameOrg[30],histNameOrgNew[30];
  char histName[30],histNameCorrNew[30];
  char binlabel[50];
  double Bins[14];
   Bins[0]= 0.;
   Bins[1]= 7.5;
   Bins[2]= 12.5;
   Bins[3]= 17.5;
   Bins[4]= 24.;
   Bins[5]= 30.;
   Bins[6]= 40.;
   Bins[7]= 50.;
   Bins[8]= 70.;
   Bins[9]= 110.;
   Bins[10]=150.;
   Bins[11]=190.;
   Bins[12]=250.;
   Bins[13]=600.;

  TCanvas *myCan;
  myCan = MakeCanvas("myCan","myCan",800,600);

  TCanvas *c;
  c = MakeCanvas("c","c",800,600);
  c->Divide(1,2,0,0);
  c->cd(1)->SetPad(0,0.3,1.0,1.0);
  c->cd(1)->SetTopMargin(0.1);
  c->cd(1)->SetBottomMargin(0.01);
  c->cd(1)->SetLeftMargin(0.15);  
  c->cd(1)->SetRightMargin(0.07);  
  c->cd(1)->SetTickx(1);
  c->cd(1)->SetTicky(1);  
  c->cd(2)->SetPad(0,0,1.0,0.3);
  c->cd(2)->SetTopMargin(0.05);
  c->cd(2)->SetBottomMargin(0.45);
  c->cd(2)->SetLeftMargin(0.15);
  c->cd(2)->SetRightMargin(0.07);
  c->cd(2)->SetTickx(1);
  c->cd(2)->SetTicky(1);

  for( int i(0);i<NWptBinPlus;i++)
  {
  sprintf(histNameGen,"h1_GenW_Neu_pt_%d",i);
  sprintf(histNameGenClone,"h1_GenW_Neu_pt_%d_Clone",i);
  sprintf(histNameOrg,"h1_W_Neu_pt_%d",i);
  sprintf(histNameOrgNew,"h1_W_Neu_pt_%d_Org",i);
  sprintf(histNameCorrNew,"h1_W_Neu_pt_%d_Corr",i);
  if (i==0){
  sprintf(binlabel,"0 < p_{T} < 600");
  if (filetype=="Inclusive"){
   hOrg[i] =(TH1D*)f_Org->Get(histNameOrg)->Clone(histNameOrgNew);
   hCorr[i]=(TH1D*)f_Corr->Get(histNameOrg)->Clone(histNameCorrNew);
   sprintf(histName,"MetBeforeAfter");
   plotNeuCompIncl = new CPlot(histName,"","#slash{E}_{T} [GeV]","Events");
   plotNeuCompIncl->setOutDir(CPlot::sOutDir);
   plotNeuCompIncl->AddHist1D(hOrg[i],"Uncorrected","H",kRed,1);
   plotNeuCompIncl->AddHist1D(hCorr[i],"Corrected","H",kBlue,1);
   plotNeuCompIncl->SetLegend(0.68,0.57,0.93,0.8);
   plotNeuCompIncl->Draw(myCan,kTRUE,format);

  hUp[i]=(TH1D*)f_Up->Get(histNameOrg)->Clone(histNameOrgNew);
  hNom[i]=(TH1D*)f_Corr->Get(histNameOrg)->Clone(histNameOrgNew);
  hDown[i]=(TH1D*)f_Down->Get(histNameOrg)->Clone(histNameCorrNew);
  sprintf(histName,"MetUpNomDown");
  plotNeuCompAll= new CPlot(histName,"","#slash{E}_{T} [GeV]","Events");
  plotNeuCompAll->setOutDir(CPlot::sOutDir);
  plotNeuCompAll->AddHist1D(hUp[i],"Up","H",kRed,2);
  plotNeuCompAll->AddHist1D(hNom[i],"Nominal","H",kBlack,1);
  plotNeuCompAll->AddHist1D(hDown[i],"Down","H",kBlue,2);
  plotNeuCompAll->SetLegend(0.68,0.57,0.93,0.8);
  plotNeuCompAll->Draw(myCan,kTRUE,format);
  delete plotNeuCompIncl;
  delete plotNeuCompAll;
//  delete f_Org;
//  delete f_Corr;
//  delete f_Up;
//  delete f_Down;
  exit(0);}
  }
  else
  sprintf(binlabel,"%.1f < p_{T} < %.1f",Bins[i-1],Bins[i]);
  hOrg[i]=(TH1D*)f_Org->Get(histNameOrg)->Clone(histNameOrgNew);
  hOrg[i]->Sumw2();
  hCorr[i]=(TH1D*)f_Corr->Get(histNameOrg)->Clone(histNameCorrNew);
  hCorr[i]->Sumw2();
  plotNeuComp= new CPlot(histNameOrg,"","","Events");
  plotNeuComp->setOutDir(CPlot::sOutDir);
  plotNeuComp->AddHist1D(hOrg[i],"NoCorr","",kBlue);
  plotNeuComp->AddHist1D(hCorr[i],"Corr","",kRed);
  plotNeuComp->SetLegend(0.68,0.57,0.93,0.8);
  plotNeuComp->AddTextBox(binlabel,0.62,0.80,0.92,0.85,0,kBlack,-1);
  plotNeuComp->Draw(c,kFALSE,format,1);
  if ( i < NBIN_PT_DIVIDER_1and2 ) {
  METMAX = METMAX_1;
  } else if ( i < NBIN_PT_DIVIDER_2and3 ) {
  METMAX = METMAX_2;
  } else {
  METMAX = METMAX_3;
  }
  hCorrDiff = makeDiffHist(hOrg[i],hCorr[i],"hCorrDiff");
  hCorrDiff->SetMarkerStyle(kFullCircle);
  hCorrDiff->SetMarkerSize(0.9);
  plotCorrDiff=new CPlot(histNameOrg,"","#slash{E}_{T} [GeV]","#chi");
  plotCorrDiff->setOutDir(CPlot::sOutDir);
  plotCorrDiff->AddHist1D(hCorrDiff,"EX0",ratioColor);
  plotCorrDiff->SetYRange(-8,8);
  plotCorrDiff->AddLine(0, 0,METMAX, 0,kBlack,1);
  plotCorrDiff->AddLine(0, 5,METMAX, 5,kBlack,3);
  plotCorrDiff->AddLine(0,-5,METMAX,-5,kBlack,3);
  plotCorrDiff->Draw(c,kTRUE,format,2);
  delete plotNeuComp;
  delete hCorrDiff;
  delete plotCorrDiff;
  }
//  delete f_Org;
//  delete f_Corr;
//  delete f_Up;
//  delete f_Down;
  }

TH1D *makeDiffHist(TH1D* h1, TH1D* h2, const TString name)
  {
  TH1D *hDiff = new TH1D(name,"",h1->GetNbinsX(),h1->GetXaxis()->GetXmin(),h1->GetXaxis()->GetXmax());
  for(Int_t ibin=1; ibin<=h1->GetNbinsX(); ibin++) {
    
    Double_t diff = (h1->GetBinContent(ibin)-h2->GetBinContent(ibin));
    
    Double_t err = sqrt(h1->GetBinContent(ibin));
    if(err==0) err= sqrt(h2->GetBinContent(ibin));
    
    if(err>0) hDiff->SetBinContent(ibin,diff/err);
    else      hDiff->SetBinContent(ibin,0);
    hDiff->SetBinError(ibin,1);   
  }
  hDiff->GetYaxis()->SetTitleOffset(0.42);
  hDiff->GetYaxis()->SetTitleSize(0.13);
  hDiff->GetYaxis()->SetLabelSize(0.10);
  hDiff->GetYaxis()->SetNdivisions(104);
  hDiff->GetYaxis()->CenterTitle();
  hDiff->GetXaxis()->SetTitleOffset(1.2);
  hDiff->GetXaxis()->SetTitleSize(0.13);
  hDiff->GetXaxis()->SetLabelSize(0.12);
  hDiff->GetXaxis()->CenterTitle();
  return hDiff;
}
