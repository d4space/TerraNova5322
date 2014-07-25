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
     if (filetype=="NoCorrWholeZ")
     {
    f_Org  = new TFile("Muon2012LoPU/Muon_DYToMuMu_S8.root");
    f_Corr = new TFile("Muon2012LoPU/Muon_RD_LowPU.root");
     }
  else if (filetype=="CorrWholeZ")
    {
    f_Org  = new TFile("Muon2012LoPU/Muon_DYToMuMu_S8.root");
    f_Corr = new TFile("Muon2012LoPU/Muon_RD_LowPU.root");
    }
  else if (filetype=="CorrBB")
    {
    f_Org  = new TFile("Muon2012LoPU/Muon_DYToMuMu_S8.root");
    f_Corr = new TFile("Muon2012LoPU/Muon_RD_LowPU.root");
    }
  else if (filetype=="CorrBE")
    {
    f_Org  = new TFile("Muon2012LoPU/Muon_DYToMuMu_S8.root");
    f_Corr = new TFile("Muon2012LoPU/Muon_RD_LowPU.root");
    }
  else if (filetype=="CorrEE")
    {
    f_Org  = new TFile("Muon2012LoPU/Muon_DYToMuMu_S8.root");
    f_Corr = new TFile("Muon2012LoPU/Muon_RD_LowPU.root");
    }
    }
  else if (Mode=="Electron")
    {
    if (filetype=="NoCorrWholeZ")
    {
    f_Org  = new TFile("Electron2012LoPU/Ele_DYToEE_S8.root");
    f_Corr = new TFile("Electron2012LoPU/Ele_RD_LowPU.root");
    }
  else if (filetype=="CorrWholeZ")
    {
    f_Org  = new TFile("Electron2012LoPU/Ele_DYToEE_S8.root");
    f_Corr = new TFile("Electron2012LoPU/Ele_RD_LowPU.root");
    }
  else if (filetype=="CorrBB")
    {
    f_Org  = new TFile("Electron2012LoPU/Ele_DYToEE_S8.root");
    f_Corr = new TFile("Electron2012LoPU/Ele_RD_LowPU.root");
    }
  else if (filetype=="CorrBE")
    {
    f_Org  = new TFile("Electron2012LoPU/Ele_DYToEE_S8.root");
    f_Corr = new TFile("Electron2012LoPU/Ele_RD_LowPU.root");
    }
  else if (filetype=="CorrEE")
    {
    f_Org  = new TFile("Electron2012LoPU/Ele_DYToEE_S8.root");
    f_Corr = new TFile("Electron2012LoPU/Ele_RD_LowPU.root");
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
 /* 
  double Bins[12];
   Bins[0]=	0;
   Bins[1]=	8;
   Bins[2]=	23;
   Bins[3]=	38;
   Bins[4]=	55;
   Bins[5]=	75;
   Bins[6]=	95;
   Bins[7]=	120;
   Bins[8]=	145;
   Bins[9]=	175;
   Bins[10]=	210;
   Bins[11]=	300;
   */
  double Bins[17];
  Bins[0]=     0.;
  Bins[1]=     5;
  Bins[2]=     7.5;
  Bins[3]=     10;
  Bins[4]=     12.5;
  Bins[5]=     15;
  Bins[6]=     17.5;
  Bins[7]=     20.;
  Bins[8]=     30.;
  Bins[9]=     40.;
  Bins[10]=    50.;
  Bins[11]=    70.;
  Bins[12]=    90.;
  Bins[13]=    150.;
  Bins[14]=    190.;
  Bins[15]=    250.;
  Bins[16]=    600.;

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

  //for( int i(0);i<NWptBinPlus;i++)
  for( int i(0);i<1;i++)
  {
//  sprintf(histNameGen,"h1_GenW_Neu_pt_%d",i);
//  sprintf(histNameGenClone,"h1_GenW_Neu_pt_%d_Clone",i);

//  sprintf(histNameOrg,"h1_W_Neu_pt_%d",i);
//  sprintf(histNameOrgNew,"h1_W_Neu_pt_%d_Org",i);
//  sprintf(histNameCorrNew,"h1_W_Neu_pt_%d_Corr",i);
  
  //sprintf(histNameOrg,"h1_ZmassCorr_BB");
  //sprintf(histNameOrg,"h1_ZmassCorr_EE");
  //sprintf(histNameOrgNew,"h1_Zmass_Org");
  //sprintf(histNameCorrNew,"h1_Zmass_EE");
 

  if (filetype=="NoCorrWholeZ")
  {
    sprintf(histNameOrg,"h1_Zmass");
    sprintf(histNameOrgNew,"h1_Zmass_Org");
    sprintf(histNameCorrNew,"h1_Zmass");
  }
  else if (filetype=="CorrWholeZ")
  {
    sprintf(histNameOrg,"h1_ZmassCorr");
    sprintf(histNameOrgNew,"h1_Zmass_Org");
    sprintf(histNameCorrNew,"h1_Zmass");
  }
  else if (filetype=="CorrBB")
  {
    sprintf(histNameOrg,"h1_ZmassCorr_BB");
    sprintf(histNameOrgNew,"h1_Zmass_Org");
    sprintf(histNameCorrNew,"h1_Zmass_BB");
  }
  else if (filetype=="CorrBE")
  {
    sprintf(histNameOrg,"h1_ZmassCorr_BE");
    sprintf(histNameOrgNew,"h1_Zmass_Org");
    sprintf(histNameCorrNew,"h1_Zmass_BE");
  }
  else if (filetype=="CorrEE")
  {
    sprintf(histNameOrg,"h1_ZmassCorr_EE");
    sprintf(histNameOrgNew,"h1_Zmass_Org");
    sprintf(histNameCorrNew,"h1_Zmass_EE");
  }



  if (i==1){
  sprintf(binlabel,"0 < p_{T} < 300");
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
  sprintf(binlabel,"",(Int_t)Bins[i-1],(Int_t)Bins[i]);
  hOrg[i]=(TH1D*)f_Org->Get(histNameOrg)->Clone(histNameOrgNew);
  //hOrg[i]=(TH1D*)f_Org->Get(histNameOrg)->Clone(histNameOrg);
  //hOrg[i]=(TH1D*)f_Org->Get(histNameOrgNew)->Clone(histNameOrgNew);
  hOrg[i]->Sumw2();
  cout<<"MC Bin Contents: "<<hOrg[i]->Integral()<<endl;
  hOrg[i]->SetLineStyle(1);
  hOrg[i]->SetMarkerSize(0.1);
  hCorr[i]=(TH1D*)f_Corr->Get(histNameCorrNew)->Clone(histNameCorrNew);
  //hCorr[i]=(TH1D*)f_Corr->Get(histNameOrg)->Clone(histNameCorrNew);
  hCorr[i]->Sumw2();
  cout<<"RD Bin Contents: "<<hCorr[i]->Integral()<<endl;
  hCorr[i]->SetLineStyle(1);
  hCorr[i]->SetMarkerSize(0.1);
  plotNeuComp= new CPlot(histNameOrg,"","","Events");
  plotNeuComp->setOutDir(CPlot::sOutDir);
  //plotNeuComp->AddHist1D(hOrg[i],"NoCorr","",kBlue);
  //plotNeuComp->AddHist1D(hCorr[i],"Corr","",kRed);
  //plotNeuComp->AddHist1D(hOrg[i],"UnCorrected MC","H",kBlue,1);
 

  if (Mode=="Electron")
  {
    plotNeuComp->AddToStack(hOrg[i],"Z#rightarrow ee",kOrange-2,kOrange-3);
  }
  else if (Mode=="Muon")
  {
    plotNeuComp->AddToStack(hOrg[i],"Z#rightarrow #mu#mu",kOrange-2,kOrange-3);
  }
  
  plotNeuComp->AddHist1D(hCorr[i],"Data","",kBlack);
  
  plotNeuComp->SetLegend(0.68,0.57,0.9,0.8);
  plotNeuComp->AddTextBox(binlabel,0.62,0.80,0.92,0.85,0,kBlack,-1);
  plotNeuComp->Draw(c,kFALSE,format,1);
  //plotNeuComp->Draw(c,kTRUE,format,1);
  if ( i < NBIN_PT_DIVIDER_1and2 ) {
  METMAX = METMAX_1;
  } else if ( i < NBIN_PT_DIVIDER_2and3 ) {
  METMAX = METMAX_2;
  } else {
  METMAX = METMAX_3;
  }
  hCorrDiff = makeDiffHist(hOrg[i],hCorr[i],"hCorrDiff");
  hCorrDiff->SetMarkerStyle(kFullCircle);
  hCorrDiff->SetMarkerSize(0.1);
 
  if (filetype=="NoCorrWholeZ" || filetype=="CorrWholeZ")
  {
    plotCorrDiff=new CPlot(histNameOrg,"","Z mass, #eta-whole range ","#chi");
  }
  if (filetype=="CorrBB")
  {
    plotCorrDiff=new CPlot(histNameOrg,"","Z mass, Barrel-Barrel ","#chi");
  } 
  if (filetype=="CorrBE")
  {
    plotCorrDiff=new CPlot(histNameOrg,"","Z mass, Barrel-Endcap ","#chi");
  } 
  if (filetype=="CorrEE")
  {
    plotCorrDiff=new CPlot(histNameOrg,"","Z mass, Endcap-Endcap ","#chi");
  }
  plotCorrDiff->setOutDir(CPlot::sOutDir);
  plotCorrDiff->AddHist1D(hCorrDiff,"EX0",ratioColor);
  plotCorrDiff->SetYRange(-8,8);
  plotCorrDiff->AddLine(60, 0,120, 0,kBlack,1);
  plotCorrDiff->AddLine(60, 5,120, 5,kBlack,3);
  plotCorrDiff->AddLine(60,-5,120,-5,kBlack,3);
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
