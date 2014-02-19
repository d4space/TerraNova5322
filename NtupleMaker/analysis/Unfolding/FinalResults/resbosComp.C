#include<iostream>
#include "TH1D.h"
#include "../../../../Utils/const.h"
#include "../../../../Utils/CPlot.hh"
#include "../../../../Utils/MitStyleRemix.hh"

int resbosComp(const TString BaseName)
{
  TString tmpTStr;
  CPlot* pltComp;
  CPlot* pltCompLog;

  TFile *F_29;
  TFile *F_30;
  TFile *F_31;
  TFile *F_32;
  TFile *F_33;
  TFile *F_34;
  TFile *F_35;
  TFile *F_Data;

  F_29 = new TFile("../"+BaseName+"/29lResbos.root");
  F_30 = new TFile("../"+BaseName+"/30lResbos.root");
  F_31 = new TFile("../"+BaseName+"/31lResbos.root");
  F_32 = new TFile("../"+BaseName+"/32lResbos.root");
  F_33 = new TFile("../"+BaseName+"/33lResbos.root");
  F_34 = new TFile("../"+BaseName+"/34lResbos.root");
  F_35 = new TFile("../"+BaseName+"/35lResbos.root");
  F_Data = new TFile("../RstUnfold/Result_"+BaseName+".root");

  TString resultDir = "Result";
  gSystem->mkdir(resultDir,kTRUE);
  TFile f_out(resultDir+"/Resbos_"+BaseName+".root","recreate");

  const int nBins = 14;
  double WptBins[nBins]    = {0.0,7.5,12.5,17.5,24,30,40,50,70,110,150,190,250,600};
  double WptLogBins[nBins] = {1.0,7.5,12.5,17.5,24,30,40,50,70,110,150,190,250,600};
  
  TH1D *hResbos29 = new TH1D("hResbos29","hResbos29",nBins-1,WptBins);hResbos29->Sumw2();
  TH1D *hResbos30 = new TH1D("hResbos30","hResbos30",nBins-1,WptBins);hResbos30->Sumw2();
  TH1D *hResbos31 = new TH1D("hResbos31","hResbos31",nBins-1,WptBins);hResbos31->Sumw2();
  TH1D *hResbos32 = new TH1D("hResbos32","hResbos32",nBins-1,WptBins);hResbos32->Sumw2();
  TH1D *hResbos33 = new TH1D("hResbos33","hResbos33",nBins-1,WptBins);hResbos33->Sumw2();
  TH1D *hResbos34 = new TH1D("hResbos34","hResbos34",nBins-1,WptBins);hResbos34->Sumw2();
  TH1D *hResbos35 = new TH1D("hResbos35","hResbos35",nBins-1,WptBins);hResbos35->Sumw2();
  TH1D *hData = new TH1D("hData","hData",nBins-1,WptBins);hData->Sumw2();
  
  TH1D *hResbosLog29 = new TH1D("hResbosLog29","hResbosLog29",13,WptLogBins);hResbosLog29->Sumw2();
  TH1D *hResbosLog30 = new TH1D("hResbosLog30","hResbosLog30",13,WptLogBins);hResbosLog30->Sumw2();
  TH1D *hResbosLog31 = new TH1D("hResbosLog31","hResbosLog31",13,WptLogBins);hResbosLog31->Sumw2();
  TH1D *hResbosLog32 = new TH1D("hResbosLog32","hResbosLog32",13,WptLogBins);hResbosLog32->Sumw2();
  TH1D *hResbosLog33 = new TH1D("hResbosLog33","hResbosLog33",13,WptLogBins);hResbosLog33->Sumw2();
  TH1D *hResbosLog34 = new TH1D("hResbosLog34","hResbosLog34",13,WptLogBins);hResbosLog34->Sumw2();
  TH1D *hResbosLog35 = new TH1D("hResbosLog35","hResbosLog35",13,WptLogBins);hResbosLog35->Sumw2();
  TH1D *hDataLog = new TH1D("hDataLog","hDataLog",13,WptLogBins);hDataLog->Sumw2();
  
  TH1D* lResbos29;
  TH1D* lResbos30;
  TH1D* lResbos31;
  TH1D* lResbos32;
  TH1D* lResbos33;
  TH1D* lResbos34;
  TH1D* lResbos35;
  TH1D* lData;

  lResbos29 =(TH1D*)F_29->Get("lResbos")->Clone();
  lResbos30 =(TH1D*)F_30->Get("lResbos")->Clone();
  lResbos31 =(TH1D*)F_31->Get("lResbos")->Clone();
  lResbos32 =(TH1D*)F_32->Get("lResbos")->Clone();
  lResbos33 =(TH1D*)F_33->Get("lResbos")->Clone();
  lResbos34 =(TH1D*)F_34->Get("lResbos")->Clone();
  lResbos35 =(TH1D*)F_35->Get("lResbos")->Clone();
  lData =(TH1D*)F_Data->Get("BornEffCorr")->Clone();

  lData->Scale(1./18.429);
  
  for( int ipt(1);ipt<nBins;ipt++)
  {
    hResbos29->SetBinContent(ipt,lResbos29->GetBinContent(ipt));
    hResbos30->SetBinContent(ipt,lResbos30->GetBinContent(ipt));
    hResbos31->SetBinContent(ipt,lResbos31->GetBinContent(ipt));
    hResbos32->SetBinContent(ipt,lResbos32->GetBinContent(ipt));
    hResbos33->SetBinContent(ipt,lResbos33->GetBinContent(ipt));
    hResbos34->SetBinContent(ipt,lResbos34->GetBinContent(ipt));
    hResbos35->SetBinContent(ipt,lResbos35->GetBinContent(ipt));
    hData->SetBinContent(ipt,lData->GetBinContent(ipt));
    hData->SetBinError(ipt,lData->GetBinError(ipt));
    
    hResbos29->SetBinError(ipt,lResbos29->GetBinError(ipt));
    hResbos30->SetBinError(ipt,lResbos30->GetBinError(ipt));
    hResbos31->SetBinError(ipt,lResbos31->GetBinError(ipt));
    hResbos32->SetBinError(ipt,lResbos32->GetBinError(ipt));
    hResbos33->SetBinError(ipt,lResbos33->GetBinError(ipt));
    hResbos34->SetBinError(ipt,lResbos34->GetBinError(ipt));
    hResbos35->SetBinError(ipt,lResbos35->GetBinError(ipt));
    
    hResbosLog29->SetBinContent(ipt,lResbos29->GetBinContent(ipt));
    hResbosLog30->SetBinContent(ipt,lResbos30->GetBinContent(ipt));
    hResbosLog31->SetBinContent(ipt,lResbos31->GetBinContent(ipt));
    hResbosLog32->SetBinContent(ipt,lResbos32->GetBinContent(ipt));
    hResbosLog33->SetBinContent(ipt,lResbos33->GetBinContent(ipt));
    hResbosLog34->SetBinContent(ipt,lResbos34->GetBinContent(ipt));
    hResbosLog35->SetBinContent(ipt,lResbos35->GetBinContent(ipt));
    hDataLog->SetBinContent(ipt,lData->GetBinContent(ipt));
    hDataLog->SetBinError(ipt,lData->GetBinError(ipt));
  }
  
  hResbos29->Write();
  hResbos30->Write();
  hResbos31->Write();
  hResbos32->Write();
  hResbos33->Write();
  hResbos34->Write();
  hResbos35->Write();

  TCanvas *c1 = new TCanvas("c1","c1",800,800);

  tmpTStr = BaseName+"_ResbosComp_Lin";
  pltComp = new CPlot(tmpTStr,"","W p_{T} [Gev]","Xsec [pb]");
  pltComp->setOutDir(resultDir);
  pltComp->AddHist1D(hResbos29,"Resbos grid29","HIST",3,1,0);
  pltComp->AddHist1D(hResbos30,"Resbos grid30","HIST",2,1,0);
  pltComp->AddHist1D(hResbos31,"Resbos grid31","HIST",4,1,0);
  pltComp->AddHist1D(hResbos32,"Resbos grid32","HIST",5,1,0);
  pltComp->AddHist1D(hResbos33,"Resbos grid33","HIST",6,1,0);
  pltComp->AddHist1D(hResbos34,"Resbos grid34","HIST",9,1,0);
  pltComp->AddHist1D(hResbos35,"Resbos grid35","HIST",7,1,0);
  pltComp->AddHist1D(hData,"Unfolded","E");
  pltComp->AddTextBox(BaseName,0.7,0.6,.9,0.63,0,1,0);
  pltComp->SetLegend(0.7,0.65,.9,0.88);
  pltComp->Draw(c1,kTRUE,"png");
  
  tmpTStr = BaseName+"_ResbosComp_Log";
  pltCompLog = new CPlot(tmpTStr,"","W p_{T} [Gev]","Xsec [pb]");
  pltCompLog->setOutDir(resultDir);
  pltCompLog->AddHist1D(hResbosLog29,"Resbos grid29","HIST",3,1,0);
  pltCompLog->AddHist1D(hResbosLog30,"Resbos grid30","HIST",2,1,0);
  pltCompLog->AddHist1D(hResbosLog31,"Resbos grid31","HIST",4,1,0);
  pltCompLog->AddHist1D(hResbosLog32,"Resbos grid32","HIST",5,1,0);
  pltCompLog->AddHist1D(hResbosLog33,"Resbos grid33","HIST",6,1,0);
  pltCompLog->AddHist1D(hResbosLog34,"Resbos grid34","HIST",9,1,0);
  pltCompLog->AddHist1D(hResbosLog35,"Resbos grid35","HIST",7,1,0);
  pltCompLog->AddHist1D(hDataLog,"Unfolded","E");
  pltCompLog->AddTextBox(BaseName,0.7,0.6,.9,0.63,0,1,0);
  pltCompLog->SetLegend(0.7,0.65,.9,0.88);
  pltCompLog->SetLogx();
  pltCompLog->Draw(c1,kTRUE,"png");
  return 0;
}
