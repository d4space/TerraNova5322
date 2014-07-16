#include <iostream>
#include <fstream>
#include <TFile.h>
#include "TH1D.h"
#include <TGraphErrors.h>             // graph class
#include <TGraphAsymmErrors.h>        // graph class
#include <TLatex.h>

const int nBins = 14;
double WptLogBins[nBins] = {1.0,7.5,12.5,17.5,24,30,40,50,70,110,150,190,250,600};
double WptBins[nBins] = {0.0,7.5,12.5,17.5,24,30,40,50,70,110,150,190,250,600};

double ax[13]  = {4.25,10,15,20.75,27,35,45,60,90,130,170,220,425};
double aex[13] = {3.25,2.5,2.5,3.25,3,5,5,10,20,20,20,30,175};

void drawDifference(TH1* iH0,TH1 *iH1,TH1* iH2, TGraphErrors* iH3, int chnl,TGraphErrors* iH4,TGraphAsymmErrors* iH5,TH1* StatErrBand,TGraphErrors* iH6){
  std::string lName = std::string(iH0->GetName());
  TH1F *lHDiff  = new TH1F((lName+"Diff").c_str(),(lName+"Diff").c_str(),nBins-1,WptLogBins);// lHDiff->Sumw2();
  TH1F *lXHDiff1 = new TH1F((lName+"XDiff1").c_str(),(lName+"XDiff1").c_str(),iH0->GetNbinsX(),iH0->GetXaxis()->GetXmin(),iH0->GetXaxis()->GetXmax());
  int i1 = 0;
  lXHDiff1->SetLineWidth(2); lXHDiff1->SetLineColor(kBlack); //lXHDiff1->SetLineStyle(2);
  
  StatErrBand->SetMarkerStyle(kFullCircle); StatErrBand->SetMarkerColor(kBlack);StatErrBand->SetMarkerSize(0.6);
  StatErrBand->SetLineWidth(2); StatErrBand->SetLineColor(kBlack);

  //lHDiff->GetYaxis()->SetRangeUser(0.6,1.6); //Wplus
  lHDiff->GetYaxis()->SetRangeUser(0.5,1.5); //Eleminus
  //lHDiff->GetYaxis()->SetRangeUser(0.5,1.5); //Muminus
  if(chnl==2)
    //lHDiff->GetYaxis()->SetRangeUser(0.6,1.4);//Wplus
    //lHDiff->GetYaxis()->SetRangeUser(0.5,1.5);//Muminus
    lHDiff->GetYaxis()->SetRangeUser(0.4,1.4);//Eleminus
  if(chnl==3)
    //lHDiff->GetYaxis()->SetRangeUser(0.6,1.4);//Wplus
    //lHDiff->GetYaxis()->SetRangeUser(0.5,1.5);
    lHDiff->GetYaxis()->SetRangeUser(0.4,1.4);
  lHDiff->GetYaxis()->SetTitleOffset(0.4);
  lHDiff->GetYaxis()->SetTitleSize(0.12);
  lHDiff->GetYaxis()->SetLabelSize(0.12);
  lHDiff->GetYaxis()->CenterTitle();
  lHDiff->GetXaxis()->SetTitleOffset(1.0);
  lHDiff->GetXaxis()->SetTitleSize(0.12);
  lHDiff->GetXaxis()->SetLabelSize(0);
  if(chnl==3)
    lHDiff->GetXaxis()->SetLabelSize(0.12);
  lHDiff->GetYaxis()->SetNdivisions(405);
  if(chnl==3)
    lHDiff->GetXaxis()->SetTitle(" W p_{T} ");
  lHDiff->GetYaxis()->SetTitle("Theory/Data");
  //lHDiff->GetYaxis()->SetTitle("Data/ResBos");
  gStyle->SetOptStat(0);
  
  for(int i0 = 0; i0 < lHDiff->GetNbinsX()+1; i0++) {
    double lXCenter = lHDiff->GetBinCenter(i0);
    double lXVal     = iH0   ->GetBinContent(i0);
    lXHDiff1->SetBinContent(i0, 1.0);
    while(iH1->GetBinCenter(i1) < lXCenter) {i1++;}
    if(iH1->GetBinContent(i0) > 0) lHDiff->SetBinContent(i0,lXVal/(iH1->GetBinContent(i0)));
    //if(iH1->GetBinContent(i0) > 0) lHDiff->SetBinError(i0,iH0->GetBinError(i0)/(iH1->GetBinContent(i0)));
    if(iH1->GetBinContent(i0) > 0) lHDiff->SetBinError(i0,0.00001);
  }
  
  TGraphErrors* ErrBand = new TGraphErrors(iH2);
  ErrBand->SetFillColor(kBlack);
  ErrBand->SetFillStyle(3354);
  ErrBand->SetLineWidth(1);
  
  if (chnl == 1)
  {
    lHDiff->SetMarkerStyle(kOpenCircle);
    lHDiff->SetMarkerColor(kBlue);
    lHDiff->SetLineColor(kBlue);
  }
  if (chnl == 2)
  {
    lHDiff->SetMarkerStyle(kOpenTriangleUp);
    lHDiff->SetMarkerColor(kRed);
    lHDiff->SetLineColor(kRed);
  }
  if (chnl == 3)
  {
    lHDiff->SetMarkerStyle(kOpenSquare);
    lHDiff->SetMarkerColor(kGreen+3);
    lHDiff->SetLineColor(kGreen+3);
  }
  
  lHDiff->SetMarkerSize(0.8);
  
  //lHDiff->SetLineColor(kBlack); lHDiff->SetMarkerColor(kBlack);
  
  lHDiff->SetTitle("");
  lHDiff->Draw("E");
  if (chnl == 1)
    iH5->Draw("2same");
  if (chnl == 2 || chnl == 3)
    iH4->Draw("2");
  if (chnl == 3)
    iH6->Draw("2");
  if (chnl == 2 || chnl == 3)
    iH3->Draw("2same");
  lXHDiff1->Draw("histsame");
  ErrBand->Draw("2same");
  lHDiff->Draw("Esame");
  StatErrBand->Draw("E1same");
}
int theoryStudy_separate(const TString BaseName)
{
  TString tmpTStr;
  char tmpName[30],tmpName_org[30];
  int Numb;

  TFile *f_Resbos;
  TFile *f_Fewz;
  TFile *f_Data;

  f_Resbos = new TFile("../../RstResbos/Resbos_"+BaseName+".root");
  //f_Data = new TFile("../RstUnfold/Result_"+BaseName+".root");
  f_Data = new TFile("../Result"+BaseName+"/Result_"+BaseName+".root");

//FEWZ Scale Systematics
  if (BaseName=="WpToMuNu")
  {
    f_Fewz = new TFile("../../RstFEWZ/Wp_Mu_NNLO.root");
    double fScale[14] = {0, 64.48, 1.105, 8.274, 9.716, 7.226, 8.534, 5.76, 6.4783, 4.5879, 1.3952, 0.52169, 0.2662, 0.09476};
  }
  if (BaseName=="WmToMuNu")
  {
    f_Fewz = new TFile("../../RstFEWZ/Wm_Mu_NNLO.root");
    double fScale[14] = {0, 45.388, 1.601, 4.628, 6.315, 4.866, 5.935, 4.1334, 4.6873, 3.4607, 1.0583, 0.36488, 0.18399, 0.063812};
  }
  if (BaseName=="WInclToMuNu")
    f_Fewz = new TFile("../../RstFEWZ/WIncl_Mu_NNLO.root");
  if (BaseName=="WpToEleNu")
  {
    f_Fewz = new TFile("../../RstFEWZ/Wp_Ele_NNLO.root");
    double fScale[14] = {0, 74.18, 2.079, 8.808, 10.496, 7.646, 8.934, 5.998, 6.6528, 4.7955, 1.4991, 0.4733, 0.28867, 0.09178};
  }
  if (BaseName=="WmToEleNu")
  {
    f_Fewz = new TFile("../../RstFEWZ/Wm_Ele_NNLO.root");
    double fScale[14] = {0, 48.427, 1.315, 5.692, 6.855, 5.33, 6.332, 4.3037, 4.9102, 3.7312, 1.1115, 0.38448, 0.19356, 0.062427};
  }
  if (BaseName=="WInclToEleNu")
    f_Fewz = new TFile("../../RstFEWZ/WIncl_Ele_NNLO.root");

  TH1D *hResbosLog30 = new TH1D("hResbosLog30","hResbosLog30",13,WptLogBins);hResbosLog30->Sumw2();
  TH1D *hResbosLog31 = new TH1D("hResbosLog31","hResbosLog31",13,WptLogBins);hResbosLog31->Sumw2();
  TH1D *hResbosLog34 = new TH1D("hResbosLog34","hResbosLog34",13,WptLogBins);hResbosLog34->Sumw2();
  TH1D *hFewzLog     = new TH1D("hFewzLog","hFewzLog",13,WptLogBins);hFewzLog->Sumw2();
  TH1D *hPowhegLog   = new TH1D("hPowhegLog","hPowhegLog",13,WptLogBins);hPowhegLog->Sumw2();
  TH1D *hDataLog     = new TH1D("hDataLog","hDataLog",13,WptLogBins);hDataLog->Sumw2();
  TH1D *hDataNoLog   = new TH1D("hDataNoLog","hDataNoLog",13,WptBins);hDataNoLog->Sumw2();
  TH1D *hDataErrBand = new TH1D("hDataErrBand","hDataErrBand",13,WptLogBins);hDataErrBand->Sumw2();
  TH1D *hPowhegErrBand = new TH1D("hPowhegErrBand","hPowhegErrBand",13,WptLogBins);hPowhegErrBand->Sumw2();
  TH1D *hPowhegErrBandPDF = new TH1D("hPowhegErrBandPDF","hPowhegErrBandPDF",13,WptLogBins);hPowhegErrBandPDF->Sumw2();
  TH1D *hFewzErrBand = new TH1D("hFewzErrBand","hFewzErrBand",13,WptLogBins);hFewzErrBand->Sumw2();
  TH1D *hFewzTheoryErrBand = new TH1D("hFewzTheoryErrBand","hFewzTheoryErrBand",13,WptLogBins);hFewzTheoryErrBand->Sumw2();
  //FEWZ Scale Syst
  TH1D *hFewzScale = new TH1D("hFewzScale","hFewzScale",13,WptLogBins);hFewzScale->Sumw2();
  TH1D *hFewzScaleErrBand = new TH1D("hFewzScaleErrBand","hFewzScaleErrBand",13,WptLogBins);hFewzScaleErrBand->Sumw2();
  TH1D *hStatErr = new TH1D("hStatErr","hStatErr",13,WptLogBins);hStatErr->Sumw2();
  
  TH1D* lResbos[7];
  TH1D* lResbos30;
  TH1D* lResbos31;
  TH1D* lResbos34;
  TH1D* lFEWZ;
  TH1D* lPowheg;
  TH1D* lData;
  TH1D* hRD;
  
  for( int i(0);i<7;i++)
  {
    Numb = 29+i;
    sprintf(tmpName_org,"hResbos%d",Numb);
    sprintf(tmpName,"lResbos_%d",i);
    lResbos[i] = (TH1D*)f_Resbos->Get(tmpName_org)->Clone(tmpName);
  }

  lResbos30 = (TH1D*)f_Resbos->Get("hResbos30")->Clone();
  lResbos31 = (TH1D*)f_Resbos->Get("hResbos31")->Clone();
  lResbos34 = (TH1D*)f_Resbos->Get("hResbos34")->Clone();
  
  lFEWZ   = (TH1D*)f_Fewz->Get("hxsec")->Clone();
  lPowheg = (TH1D*)f_Data->Get("SVD_Born.Gen")->Clone();
  orgPowheg = (TH1D*)f_Data->Get("SVD_Born.Gen")->Clone();
  lData   = (TH1D*)f_Data->Get("BornEffCorr")->Clone();
  hRD     = (TH1D*)f_Data->Get("data_Rec")->Clone();
  
  for( int ipt(1);ipt<nBins;ipt++)
  {
    double tmp = sqrt(hRD->GetBinContent(ipt));
    hRD->SetBinError(ipt,tmp);
    cout<<ipt<<"\t"<<hRD->GetBinContent(ipt)<<"\t"<<hRD->GetBinError(ipt)<<endl;
  }

  lPowheg->Scale(1./18.429);
  lData->Scale(1./18.429);
  hRD->Scale(1./18.429);
  
  for( int ipt(1);ipt<nBins;ipt++)
  {
    cout<<ipt<<"\t"<<hRD->GetBinError(ipt)<<"\t"<<lData->GetBinError(ipt)<<endl;
  }
  cout << "Resbos Total Xsec: " << lResbos30->Integral() << endl;
  cout << "Data Total Xsec: " << lData->Integral() << endl;

  Double_t resb30[nBins-1];
  Double_t errMax[nBins-1];
  Double_t errMin[nBins-1];
  double tmpVal,tmpDiff;

  for( int ipt(0);ipt<nBins-1;ipt++)
  {
    resb30[ipt] = lResbos30->GetBinContent(ipt+1)/hDataNoLog->GetXaxis()->GetBinWidth(ipt+1);
    double norVal  = lResbos[1]->GetBinContent(ipt+1);
    errMax[ipt] = -99999;
    errMin[ipt] = 990009;
    for (int i(0);i<7;i++)
    {
      tmpVal  = lResbos[i]->GetBinContent(ipt+1);
      tmpDiff = tmpVal - norVal;
      if( tmpDiff > errMax[ipt] ) errMax[ipt] = tmpDiff;
      if( tmpDiff < errMin[ipt] ) errMin[ipt] = tmpDiff;
    }
    
    if (errMax[ipt] < 0) errMax[ipt] = 0.;
    if (errMin[ipt] > 0) errMin[ipt] = 0.;
    if (errMin[ipt] < 0) errMin[ipt] = -errMin[ipt];
    errMax[ipt] = errMax[ipt]/hDataNoLog->GetXaxis()->GetBinWidth(ipt+1);
    errMin[ipt] = errMin[ipt]/hDataNoLog->GetXaxis()->GetBinWidth(ipt+1);
  }
 
  Double_t errFewz[nBins-1];
  Double_t vPowheg[nBins-1];
  Double_t vFewz[nBins-1];
  Double_t resbVal[nBins-1],errResbosDataLo[nBins-1],errResbosDataHi[nBins-1];

  for( int ipt(1);ipt<=nBins-1;ipt++)
  {
    hResbosLog30->SetBinContent(ipt,lResbos30->GetBinContent(ipt)/hDataNoLog->GetXaxis()->GetBinWidth(ipt) );
    hResbosLog31->SetBinContent(ipt,lResbos31->GetBinContent(ipt));
    hResbosLog34->SetBinContent(ipt,lResbos34->GetBinContent(ipt));
    
    hFewzLog->SetBinContent(ipt,lFEWZ->GetBinContent(ipt)/hDataNoLog->GetXaxis()->GetBinWidth(ipt));
    //hFewzLog->SetBinError(ipt,lFEWZ->GetBinError(ipt)/hDataNoLog->GetXaxis()->GetBinWidth(ipt));
    hFewzLog->SetBinError(ipt,sqrt((lFEWZ->GetBinError(ipt)/hDataNoLog->GetXaxis()->GetBinWidth(ipt))*(lFEWZ->GetBinError(ipt)/hDataNoLog->GetXaxis()->GetBinWidth(ipt))+(fScale[ipt]/hDataNoLog->GetXaxis()->GetBinWidth(ipt))*(fScale[ipt]/hDataNoLog->GetXaxis()->GetBinWidth(ipt))));
    
    hPowhegLog->SetBinContent(ipt,lPowheg->GetBinContent(ipt)/hDataNoLog->GetXaxis()->GetBinWidth(ipt));
    hPowhegLog->SetBinError(ipt,sqrt(lPowheg->GetBinContent(ipt))/hDataNoLog->GetXaxis()->GetBinWidth(ipt));
    
    hDataLog->SetBinContent(ipt,lData->GetBinContent(ipt)/hDataNoLog->GetXaxis()->GetBinWidth(ipt));
    hDataLog->SetBinError(ipt,lData->GetBinError(ipt)/hDataNoLog->GetXaxis()->GetBinWidth(ipt));
    hDataErrBand->SetBinContent(ipt,1.);
    hDataErrBand->SetBinError(ipt,lData->GetBinError(ipt)/lData->GetBinContent(ipt));
    hStatErr->SetBinContent(ipt,1.);
    hStatErr->SetBinError(ipt,hRD->GetBinError(ipt)/lData->GetBinContent(ipt));

    hPowhegErrBand->SetBinContent(ipt,hPowhegLog->GetBinContent(ipt)/hDataLog->GetBinContent(ipt));
    hPowhegErrBand->SetBinError(ipt,sqrt(orgPowheg->GetBinContent(ipt))/orgPowheg->GetBinContent(ipt));
    hPowhegErrBandPDF->SetBinContent(ipt,hPowhegLog->GetBinContent(ipt)/hDataLog->GetBinContent(ipt));
    //hPowhegErrBandPDF->SetBinError(ipt,lPowheg->GetBinError(ipt)/hDataLog->GetBinContent(ipt)/hDataNoLog->GetXaxis()->GetBinWidth(ipt));
    hPowhegErrBandPDF->SetBinError(ipt,sqrt(orgPowheg->GetBinContent(ipt))/orgPowheg->GetBinContent(ipt)+lPowheg->GetBinError(ipt)/hDataLog->GetBinContent(ipt)/hDataNoLog->GetXaxis()->GetBinWidth(ipt));
    cout<<hPowhegErrBandPDF->GetBinContent(ipt)<<" "<<hPowhegErrBandPDF->GetBinError(ipt)<<" "<<100*hPowhegErrBandPDF->GetBinError(ipt)/hPowhegErrBandPDF->GetBinContent(ipt)<<"  "<<100*orgPowheg->GetBinError(ipt)/orgPowheg->GetBinContent(ipt)<<endl; 
    hFewzErrBand->SetBinContent(ipt,hFewzLog->GetBinContent(ipt)/hDataLog->GetBinContent(ipt));
    hFewzErrBand->SetBinError(ipt,0.01);
    hFewzScale->SetBinContent(ipt,hFewzLog->GetBinContent(ipt)/hDataLog->GetBinContent(ipt));  
    hFewzScale->SetBinError(ipt,fScale[ipt]/hDataNoLog->GetXaxis()->GetBinWidth(ipt));
    cout << fScale[ipt] << endl;
    hFewzTheoryErrBand->SetBinContent(ipt,hFewzLog->GetBinContent(ipt)/hDataLog->GetBinContent(ipt));
    hFewzScaleErrBand->SetBinContent(ipt,hFewzLog->GetBinContent(ipt)/hDataLog->GetBinContent(ipt));
    hFewzScaleErrBand->SetBinError(ipt,0.01+hFewzScale->GetBinError(ipt)/hDataLog->GetBinContent(ipt));
    //hFewzTheoryErrBand->SetBinError(ipt,hFewzLog->GetBinError(ipt)/hDataLog->GetBinContent(ipt));
    //hFewzTheoryErrBand->SetBinError(ipt,0.01+hFewzLog->GetBinError(ipt)/hDataLog->GetBinContent(ipt));
    hFewzTheoryErrBand->SetBinError(ipt,0.01+(hFewzLog->GetBinError(ipt)+hFewzScale->GetBinError(ipt))/hDataLog->GetBinContent(ipt));
    // FEWZ SCale syst
    
    cout << "Bin " <<ipt <<" FewzTheory : " <<  hFewzTheoryErrBand->GetBinError(ipt) << "\t FewzScale : " << hFewzScale->GetBinError(ipt) << "\t FewzStat : " << hFewzErrBand->GetBinError(ipt) << endl; ;
    
    
    resbVal[ipt-1]=hResbosLog30->GetBinContent(ipt)/hDataLog->GetBinContent(ipt);
    errResbosDataLo[ipt-1]=errMin[ipt-1]/hDataLog->GetBinContent(ipt);
    errResbosDataHi[ipt-1]=errMax[ipt-1]/hDataLog->GetBinContent(ipt);
  }

  hDataLog->SetMarkerStyle(kFullCircle); hDataLog->SetMarkerColor(kBlack); hDataLog->SetMarkerSize(1);
  hStatErr->SetMarkerStyle(kFullCircle); hStatErr->SetMarkerColor(kBlack); hStatErr->SetMarkerSize(0.6);

  TGraphErrors *hData = new TGraphErrors(hDataLog);
  TGraphErrors *hPowheg = new TGraphErrors(hPowhegLog);
  TGraphErrors *hFewz = new TGraphErrors(hFewzLog);
  TGraphAsymmErrors* hResbos = new TGraphAsymmErrors(nBins-1, ax, resb30, aex, aex, errMin, errMax);
  TGraphAsymmErrors* ResbosErrBand = new TGraphAsymmErrors(nBins-1, ax, resbVal, aex, aex, errResbosDataLo, errResbosDataHi);
  TGraphErrors* pRatio = new TGraphErrors(hPowhegErrBand);
  TGraphErrors* pRatioPDF = new TGraphErrors(hPowhegErrBandPDF);
  TGraphErrors* fRatio = new TGraphErrors(hFewzErrBand);
  TGraphErrors* fTheoryRatio = new TGraphErrors(hFewzTheoryErrBand);
  TGraphErrors* fScaleRatio = new TGraphErrors(hFewzScaleErrBand);
  
  TGraphErrors* dataErrBand = new TGraphErrors(hDataErrBand);
  dataErrBand->SetFillColor(kBlack);
  dataErrBand->SetFillStyle(3354);
  
  ResbosErrBand->SetFillColor(kBlue-7);
  ResbosErrBand->SetFillStyle(3001);
  
  pRatio->SetFillColor(kRed-10);
  pRatio->SetFillStyle(3001);
  
  pRatioPDF->SetFillColor(kRed+2);
  pRatioPDF->SetFillStyle(3001);
  
  //fRatio->SetFillColor(kGreen);
  fRatio->SetFillColor(kGreen);
  fRatio->SetFillStyle(3001);
  
  fTheoryRatio->SetFillColor(kGreen+3);
  fTheoryRatio->SetFillStyle(3001);

  fScaleRatio->SetFillColor(kGreen+7);
  fScaleRatio->SetFillStyle(3001);

  hFewz->SetFillColor(kGreen);
  hFewz->SetFillStyle(3305);

  hPowheg->SetFillColor(kRed);
  hPowheg->SetFillStyle(3345);
  hResbos->SetFillColor(kBlue);
  hResbos->SetFillStyle(3354);

  //TLegend *lL =new TLegend(0.6,0.65,0.92,0.85); lL->SetFillColor(0); lL->SetBorderSize(0);
  TLegend *lL =new TLegend(0.2,0.2,0.52,0.38); lL->SetFillColor(0); lL->SetBorderSize(0);
  lL->AddEntry(hData,"Unfolded","PL");
  lL->AddEntry(hPowheg,"Powheg CT10 NLO","f");
  lL->AddEntry(hFewz,"FEWZ CT10 NNLO","f");
  lL->AddEntry(hResbos,"ResBos CT10 NNLO","f");

  //TPaveText *tb = new TPaveText(0.6,0.44,0.9,0.58,"NDC");
  TPaveText *tb = new TPaveText(0.2,0.39,0.52,0.5,"NDC");
  tb->SetBorderSize(0);
  tb->SetFillStyle(0);
  tb->AddText("18.43 pb^{-1} at #sqrt{s} = 8 TeV");
  if (BaseName=="WpToMuNu")
    tb->AddText("W^{+} #rightarrow #mu^{+} #nu");
  if (BaseName=="WmToMuNu")
    tb->AddText("W^{-} #rightarrow #mu^{-} #bar{#nu}");
  if (BaseName=="WInclToMuNu")
    tb->AddText("W #rightarrow #mu #nu");
  if (BaseName=="WpToEleNu")
    tb->AddText("W^{+} #rightarrow e^{+} #nu");
  if (BaseName=="WmToEleNu")
    tb->AddText("W^{-} #rightarrow e^{-} #bar{#nu}");
  if (BaseName=="WInclToEleNu")
    tb->AddText("W #rightarrow e #nu");

  TCanvas *lC1 = new TCanvas("Can","Can",800,840); lC1->cd(); lC1->SetLogy();
  lC1->cd(1)->SetPad(0,0.05,0.95,1.0);
  lC1->cd(1)->SetTopMargin(0.05);
  lC1->cd(1)->SetBottomMargin(0.1);
  lC1->cd(1)->SetLeftMargin(0.15);
  lC1->cd(1)->SetRightMargin(0.07);
  lC1->cd(1)->SetTickx(1);
  lC1->cd(1)->SetTicky(1);
  gStyle->SetLineWidth(2.);
  gStyle->SetOptStat(0);
  gStyle->SetHatchesSpacing(0.75);
  gStyle->SetHatchesLineWidth(2);
  gPad->SetLogx(1);
  gPad->SetLogy(1);

  hPowheg->GetYaxis()->SetRangeUser(1e-4,5*resb30[0]);
  hPowheg->SetTitle("");
  hPowheg->GetYaxis()->SetTitle("Cross-section [pb (GeV/c)^{-1}]");
  hPowheg->GetXaxis()->SetTitle("W p_{T}");
  hPowheg->GetYaxis()->SetTitleOffset(1.2);
  
  hPowheg->Draw("A2");
  hFewz->Draw("2");
  hResbos->Draw("2");
  hData->Draw("p");
  lL->Draw();
  tb->Draw();
  
  if(BaseName=="WpToMuNu")
    sprintf(tmpName,"wpmnCrossSec.png");
  if(BaseName=="WmToMuNu")
    sprintf(tmpName,"wmmnCrossSec.png");
  if(BaseName=="WpToEleNu")
    sprintf(tmpName,"wpenCrossSec.png");
  if(BaseName=="WmToEleNu")
    sprintf(tmpName,"wmenCrossSec.png");
  lC1->SaveAs(tmpName);
  
  TCanvas *lC2 = new TCanvas("Can","Can",800,800); lC2->cd(); lC2->SetLogy();
  lC2->Divide(1,3,0,0);
  lC2->cd(1)->SetPad(0,0.67,0.95,0.95);
  lC2->cd(1)->SetTopMargin(0.05);
  lC2->cd(1)->SetBottomMargin(0.01);
  lC2->cd(1)->SetLeftMargin(0.15);
  lC2->cd(1)->SetRightMargin(0.07);
  lC2->cd(1)->SetTickx(1);
  lC2->cd(1)->SetTicky(1);
  lC2->cd(1)->SetLogx(1);

  TPaveText *tb1 = new TPaveText(0.15,0.82,0.35,0.92,"NDC");
  tb1->SetBorderSize(0);
  tb1->SetFillStyle(0);
  tb1->SetTextSize(0.12);
  tb1->AddText("ResBos");
  TLegend *rL1 =new TLegend(0.2,0.05,0.86,0.15); rL1->SetFillColor(0); rL1->SetBorderSize(0);
  rL1-> SetNColumns(3);
  rL1->AddEntry(ResbosErrBand,"Theory unc. (gen)","F");
  rL1->AddEntry(hStatErr,"Statistic error (data)","PLE1");
  rL1->AddEntry(dataErrBand,"Stat. + Syst. (data)","F");
  rL1->SetTextSize(0.07);

  drawDifference(hResbosLog30,hDataLog,hDataErrBand,pRatio,1,pRatio,ResbosErrBand,hStatErr,fScaleRatio);
  rL1->Draw();
  tb1->Draw();

  lC2->cd(2)->SetPad(0,0.37,0.95,0.65);
  lC2->cd(2)->SetTopMargin(0.01);
  lC2->cd(2)->SetBottomMargin(0.01);
  lC2->cd(2)->SetLeftMargin(0.15);
  lC2->cd(2)->SetRightMargin(0.07);
  lC2->cd(2)->SetTickx(1);
  lC2->cd(2)->SetTicky(1);
  lC2->cd(2)->SetLogx(1);

  TPaveText *tb2 = new TPaveText(0.15,0.82,0.35,0.92,"NDC");
  tb2->SetBorderSize(0);
  tb2->SetFillStyle(0);
  tb2->SetTextSize(0.12);
  tb2->AddText("Powheg");
  TLegend *rL2 =new TLegend(0.2,0.05,0.68,0.30); rL2->SetFillColor(0); rL2->SetBorderSize(0);
  rL2-> SetNColumns(2);
  rL2->AddEntry(pRatioPDF,"PDF unc. (gen)","F");
  rL2->AddEntry(hStatErr,"Statistic error (data)","PLE1");
  rL2->AddEntry(pRatio,"Statistical unc. (gen)","F");
  rL2->AddEntry(dataErrBand,"Stat. + Syst. (data)","F");
  rL2->SetTextSize(0.07);

  drawDifference(hPowhegLog,hDataLog,hDataErrBand,pRatio,2,pRatioPDF,ResbosErrBand,hStatErr,fScaleRatio);
  rL2->Draw();
  tb2->Draw();

  lC2->cd(3)->SetPad(0,0.07,0.95,0.35);
  lC2->cd(3)->SetTopMargin(0.01);
  lC2->cd(3)->SetBottomMargin(0.05);
  lC2->cd(3)->SetLeftMargin(0.15);
  lC2->cd(3)->SetRightMargin(0.07);
  lC2->cd(3)->SetTickx(1);
  lC2->cd(3)->SetTicky(1);
  lC2->cd(3)->SetLogx(1);

  TPaveText *tb3 = new TPaveText(0.15,0.82,0.35,0.92,"NDC");
  tb3->SetBorderSize(0);
  tb3->SetFillStyle(0);
  tb3->SetTextSize(0.12);
  tb3->AddText("Fewz");
  TLegend *rL3 =new TLegend(0.2,0.1,0.68,0.30); rL3->SetFillColor(0); rL3->SetBorderSize(0);
  rL3-> SetNColumns(2);
  rL3->AddEntry(fTheoryRatio,"PDF unc. (gen)","F");
  rL3->AddEntry(fScaleRatio,"Scale unc. (gen)","F");
  rL3->AddEntry(hStatErr,"Statistic error (data)","PLE1");
  rL3->AddEntry(fRatio,"Statistical unc. (gen)","F");
  rL3->AddEntry(dataErrBand,"Stat. + Syst. (data)","F");
  rL3->SetTextSize(0.07);

  //drawDifferencefewz(hFewzLog,hDataLog,hDataErrBand,fRatio,3,fTheoryRatio,ResbosErrBand,hStatErr,fScaleRatio);
  //drawDifference(hFewzLog,hDataLog,hDataErrBand,fRatio,3,fTheoryRatio,ResbosErrBand,hStatErr);
  drawDifference(hFewzLog,hDataLog,hDataErrBand,fRatio,3,fTheoryRatio,ResbosErrBand,hStatErr,fScaleRatio);
  rL3->Draw();
  tb3->Draw();

  if(BaseName=="WpToMuNu")
    sprintf(tmpName,"wpmnRatioTheoData.png");
  if(BaseName=="WmToMuNu")
    sprintf(tmpName,"wmmnRatioTheoData.png");
  if(BaseName=="WpToEleNu")
    sprintf(tmpName,"wpenRatioTheoData.png");
  if(BaseName=="WmToEleNu")
    sprintf(tmpName,"wmenRatioTheoData.png");
  lC2->SaveAs(tmpName);

  return 0;
}
