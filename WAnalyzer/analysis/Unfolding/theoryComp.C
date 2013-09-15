
#include "../Utils/const.h"
#include "../Utils/CPlot.hh"
#include "../Utils/MitStyleRemix.hh"

int theoryComp(TString BaseName)
{
  cout<<"Processing "<<BaseName<<endl;
  TString resultDir = "Result"+BaseName;
  gSystem->mkdir(resultDir,kTRUE);

  TString tmpTStr;

  TFile *f_FEWZ;
  TFile *f_Born;

  TH1D* h_UnfBorn;
  TH1D* h_data_Rec;
  TH1D* h_Theory;
  
  double Syst[13];
  double TotalErr[13];

  TCanvas *myCan = MakeCanvas("myCan","myCan",900,800);
  CPlot* pltComp;

  if( BaseName == "WpToMuNu"){
    f_FEWZ = new TFile("../RstFEWZ/Wp_Mu_NLO.root");
    f_Born = new TFile("ResultWpToMuNu/Result_WpToMuNu.root");
    Syst[0] = 1512.688684;
    Syst[1] = 639.838424;
    Syst[2] = 282.376629;
    Syst[3] = 278.950850;
    Syst[4] = 165.820035;
    Syst[5] = 167.626505;
    Syst[6] = 126.456842;
    Syst[7] = 150.165279;
    Syst[8] = 98.730854;
    Syst[9] = 25.128792;
    Syst[10] = 8.083345;
    Syst[11] = 4.190595;
    Syst[12] = 2.142359;
  }else if(BaseName == "WpToElNu"){
    f_FEWZ = new TFile("../RstFEWZ/Wp_Ele_NLO.root");
    f_Born = new TFile("ResultWpToEleNu/Result_WpToEleNu.root");
    Syst[0] = 1636.3;
    Syst[1] = 597.7;
    Syst[2] = 453.5;
    Syst[3] = 534.5;
    Syst[4] = 333.7;
    Syst[5] = 302.7;
    Syst[6] = 170.5;
    Syst[7] = 182.2;
    Syst[8] = 122.7;
    Syst[9] = 32.8;
    Syst[10] = 10.6;
    Syst[11] = 5.4;
    Syst[12] = 2.6;
  }else{
    cout<<"No case for "<<BaseName<<endl;
    exit(-1);
  }
  h_UnfBorn     =(TH1D*)f_Born->Get("BornEffCorr")->Clone();
  h_data_Rec    =(TH1D*)f_Born->Get("data_Rec")->Clone();
  h_Theory	=(TH1D*)f_FEWZ->Get("hxsec")->Clone();
  h_data_Rec->Sumw2();
  for(int i(0);i<13;i++){
    TotalErr[i]=Syst[i]+h_data_Rec->GetBinError(i);
    h_data_Rec->SetBinError(i,TotalErr[i]);
  }

  h_UnfBorn->Scale(1/Lumi_LowPU);
  h_data_Rec->Scale(1/Lumi_LowPU);

  tmpTStr = "TheoryComp_"+BaseName;
  pltComp = new CPlot(tmpTStr,"","pT Bin","xsec [pb]");
  pltComp->setOutDir(resultDir);
  pltComp->AddHist1D(h_data_Rec,"elp",kRed,1,0,20,2);
  pltComp->AddHist1D(h_UnfBorn,"elp",kBlue,1,0,24,2);
  pltComp->AddHist1D(h_Theory,"elp",kGreen+2,0,0,26,2);
  pltComp->SetLegend(0.68,0.57,0.93,0.8);
  pltComp->GetLegend()->AddEntry(h_data_Rec,"data","p");
  pltComp->GetLegend()->AddEntry(h_UnfBorn,"Unf","p");
  pltComp->GetLegend()->AddEntry(h_Theory,"FEWZ NLO","p");
  pltComp->Draw(myCan,kTRUE,"png");

  return 0;
}
