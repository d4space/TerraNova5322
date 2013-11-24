//#include "/home/pharris/Analysis/W/condor/run/CMSSW_3_8_4/src/MitWlnu/NYStyle/test/NYStyle.h"
#include <TLatex.h>

//const int   nptBins  =   9;
const int   nptBins  =   13;
double xbins_pt[nptBins+1] = {0.0, 7.5, 12.5, 17.5, 24,30,40,50,70,110,150,190,250,600};

//void drawDifference(TH1* iH0,TH1 *iH1,TH1 *iHH=0,TH1 *iHL=0) {
void drawDifference(TH1* iH0,TH1 *iH1,TGraphAsymmErrors* iH2,TH1 *iHH=0,TH1 *iHL=0) {
  std::string lName = std::string(iH0->GetName());
//  TH1F *lHDiff  = new TH1F((lName+"Diff").c_str(),(lName+"Diff").c_str(),nptBins,xbins_pt); lHDiff->Sumw2();
  TH1F *lHDiff  = new TH1F((lName+"Diff").c_str(),(lName+"Diff").c_str(),iH0->GetNbinsX(),iH0->GetXaxis()->GetXmin(),iH0->GetXaxis()->GetXmax()); lHDiff->Sumw2();
  TH1F *lHDiffH = new TH1F((lName+"DiffH").c_str(),(lName+"DiffH").c_str(),iH0->GetNbinsX(),iH0->GetXaxis()->GetXmin(),iH0->GetXaxis()->GetXmax()); lHDiffH->SetLineWidth(1); lHDiffH->SetLineColor(kRed);
  TH1F *lHDiffL = new TH1F((lName+"DiffL").c_str(),(lName+"DiffL").c_str(),iH0->GetNbinsX(),iH0->GetXaxis()->GetXmin(),iH0->GetXaxis()->GetXmax()); lHDiffL->SetLineWidth(1); lHDiffL->SetLineColor(kBlue);
  lHDiff->SetFillColor(kViolet); lHDiff->SetFillStyle(1001); lHDiff->SetLineWidth(1);
  TH1F *lXHDiff1 = new TH1F((lName+"XDiff1").c_str(),(lName+"XDiff1").c_str(),iH0->GetNbinsX(),iH0->GetXaxis()->GetXmin(),iH0->GetXaxis()->GetXmax());
  TH1F *lXHDiff2 = new TH1F((lName+"XDiff2").c_str(),(lName+"XDiff2").c_str(),iH0->GetNbinsX(),iH0->GetXaxis()->GetXmin(),iH0->GetXaxis()->GetXmax());
  int i1 = 0;
  lXHDiff1->SetLineWidth(2); lXHDiff1->SetLineColor(kBlack); lXHDiff1->SetLineStyle(2);
  lXHDiff2->SetLineWidth(2); lXHDiff2->SetLineColor(kRed);

  lHDiff->GetYaxis()->SetRangeUser(0.6,1.2);
  lHDiff->GetYaxis()->SetTitleOffset(0.6);
  lHDiff->GetYaxis()->SetTitleSize(0.08);
  lHDiff->GetYaxis()->SetLabelSize(0.08);
  lHDiff->GetYaxis()->CenterTitle();
  lHDiff->GetXaxis()->SetTitleOffset(1.2);
  lHDiff->GetXaxis()->SetTitleSize(0.10);
  lHDiff->GetXaxis()->SetLabelSize(0.08);
  lHDiff->GetXaxis()->SetTitle("p_{T} Bin");
//  lHDiff->GetXaxis()->CenterTitle();
  lHDiff->GetYaxis()->SetTitle("Data/ResBos");
  gStyle->SetOptStat(0);

  for(int i0 = 0; i0 < lHDiff->GetNbinsX()+1; i0++) {
    double lXCenter = lHDiff->GetBinCenter(i0);
    double lXVal     = iH0   ->GetBinContent(i0);
    //double lXValH    = iHH   ->GetBinContent(i0);
    //double lXValL    = iHL   ->GetBinContent(i0);
    lXHDiff1->SetBinContent(i0, 1.0);
    lXHDiff2->SetBinContent(i0, 1.0);
    while(iH1->GetBinCenter(i1) < lXCenter) {i1++;}
    if(iH1->GetBinContent(i0) > 0) lHDiff->SetBinContent(i0,lXVal      /(iH1->GetBinContent(i0)));
//    if(iH1->GetBinContent(i0) > 0) lHDiff->SetBinError  (i0,sqrt(lXVal)/(iH1->GetBinContent(i0)));
    if(iH1->GetBinContent(i0) > 0) lHDiff->SetBinError  (i0,iH0->GetBinError(i0)/(iH1->GetBinContent(i0)));
    //if(iH1->GetBinContent(i0) > 0) lHDiffL->SetBinContent(i0,lXValL/(iH1->GetBinContent(i0)));
    //if(iH1->GetBinContent(i0) > 0) lHDiffH->SetBinContent(i0,lXValH/(iH1->GetBinContent(i0)));
    //if(iH1->GetBinContent(i0) > 0)  cout << "unc" << lXVal << " -- " << sqrt(lXVal)/(iH1->GetBinContent(i0)) << endl;
  }
//  lHDiff->SetMarkerStyle(kFullCircle); lHDiff->SetLineColor(kRed); lHDiff->SetMarkerColor(kRed);
  lHDiff->SetMarkerStyle(kFullCircle); lHDiff->SetLineColor(kBlack); lHDiff->SetMarkerColor(kBlack);
  
  Double_t ax[13] = {0.5,1.5,2.5,3.5,4.5,5.5,6.5,7.5,8.5,9.5,10.5,11.5,12.5};
  Double_t aex[13] = {0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5};
  
  Double_t ay[13];
  Double_t aeyl[13];
  Double_t aeyh[13];
  
  for( int ipt(0);ipt<13;ipt++)
  {
    ay[ipt] = 1.;
    aeyl[ipt] = iH2->GetErrorYlow(ipt)/iH1->GetBinContent(ipt+1);
    aeyh[ipt] = iH2->GetErrorYhigh(ipt)/iH1->GetBinContent(ipt+1);
    cout<<iH2->GetErrorYlow(ipt)<<"\t"<<iH2->GetErrorYhigh(ipt)<<"\t"<<iH1->GetBinContent(ipt+1)<<endl;
  }
    
  TGraphAsymmErrors* ErrBand = new TGraphAsymmErrors(13, ax, ay, aex,aex, aeyl, aeyh);
  ErrBand->SetFillColor(kGreen);
  ErrBand->SetFillStyle(3005);

  //lHDiff->Draw("EP");
  lHDiff->SetTitle("");
  lHDiff->Draw("E1");
  ErrBand->Draw("2");
  lXHDiff1->Draw("hist sames");
  //lXHDiff2->Draw("hist sames");
  //lHDiffH ->Draw("hist sames");
  //lHDiffL ->Draw("hist sames");
}

//double xbins_pt[nptBins+1] = {0.001, 2.5, 5, 7.5, 10, 12.5, 15, 17.5, 20, 30};
//double xbins_pt[nptBins+1] = {0.001, 7.5, 12.5, 17.5, 24,30,40,50,70,110,150,190,250,600};

void plotHelpComp(std::string iRVar,std::string iVar,std::string iRCut,std::string iCCut,int iNBin,double iMin,double iMax,std::string iResbosName,std::string iCName,std::string iXAxis) { 
//void plotHelpComp(std::string iRVar,std::string iVar,std::string iRCut,std::string iCCut,int nptBins,double xbins_pt,std::string iResbosName,std::string iCName,std::string iXAxis) { 
  
  f_FEWZ = new TFile("../RstFEWZ/Wm_Mu_NNLO.root");

  TH1D* h_Total_Syst;
  TH1D* h_FEWZ;

  TH1D* h_resbos34;
  f_resbos34 = new TFile("34lResbos.root");
  h_resbos34 = (TH1D*)f_resbos34->Get("lResbos")->Clone();
  TH1D* h_resbos31;
  f_resbos31 = new TFile("31lResbos.root");
  h_resbos31 = (TH1D*)f_resbos31->Get("lResbos")->Clone();

  h_FEWZ = (TH1D*)f_FEWZ->Get("hxsec")->Clone();
 // h_Total_Syst = (TH1D*)f_TotalSyst->Get("Total_Wp_Syst")->Clone();
//  h_Total_Syst = (TH1D*)f_TotalSyst->Get("Total_Wm_Syst")->Clone();

  TFile *lRFile  = new TFile(iResbosName.c_str());
  TTree *lRTree  = (TTree*) lRFile->FindObjectAny("h10");

  TFile *lCFile  = new TFile(iCName.c_str());
//  TTree *lCTree  = (TTree*) lCFile->FindObjectAny("Events");
  
  std::string lRName = "R" +iRVar;
  std::string lCName = "CB"+iRVar;
  std::stringstream lRDraw; lRDraw << iRVar << ">>" << lRName;
  std::stringstream lCDraw; lCDraw << iVar  << ">>" << lCName;
  
  TH1F *lRH = new TH1F(lRName.c_str(),lRName.c_str(),nptBins, xbins_pt);

  TH1D *h1_Powheg;
  TH1D *h1_data;
//  TH1D *lResbos=new TH1D("lResbos","lResbos",nptBins,xbins_pt);lResbos->Sumw2();
//  TH1D *lData=new TH1D("lData","lData",nptBins,xbins_pt); lData->Sumw2();
//  TH1D *lPowheg = new TH1D("lPowheg","lPowheg",nptBins,xbins_pt);lPowheg->Sumw2();
  TH1D *lResbos=new TH1D("lResbos","lResbos",nptBins,0,nptBins);lResbos->Sumw2();
  TH1D *lData=new TH1D("lData","lData",nptBins,0,nptBins); lData->Sumw2();
  TH1D *lPowheg = new TH1D("lPowheg","lPowheg",nptBins,0,nptBins);lPowheg->Sumw2();
  TH1D *lFEWZ = new TH1D("lFEWZ","lFEWZ",nptBins,0,nptBins);lPowheg->Sumw2();
  h1_Powheg =(TH1D*)lCFile->Get("SVD_Born.Gen")->Clone();
  h1_data =(TH1D*)lCFile->Get("BornEffCorr")->Clone();

  lRTree->Draw(lRDraw.str().c_str(),iRCut.c_str()); 
//  lCTree->Draw(lCDraw.str().c_str(),iCCut.c_str());
  lRH->Sumw2();
  
  Double_t ax[13] = {0.5,1.5,2.5,3.5,4.5,5.5,6.5,7.5,8.5,9.5,10.5,11.5,12.5};
  Double_t aexl[13] = {0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5};
 
  Double_t aexlLow[13] = {0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5};
  Double_t aexlHigh[13] = {0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5};

  Double_t derr[14] = {0,2.85938804641832389e+00,2.84297379516589999e+00,2.92030820291283622e+00,3.04105244939971397e+00,3.23422324523215288e+00
    ,3.36715013030307286e+00,4.28290789067427902e+00,4.61345857248117053e+00,3.76969494787045045e+00,6.19330283451406860e+00,1.02453208832129814e+01,1.31788656568006655e+01,2.55491878540199373e+01};

  Double_t ay[nptBins],aeyl[nptBins],by[nptBins],beyl[nptBins],cy[nptBins],ceyl[nptBins],dy[nptBins],deyl[nptBins];
  Double_t ay34[nptBins],aeyl34[nptBins];
  Double_t aeylLow[nptBins],aeylHigh[nptBins];
  
  for( int ipt(1);ipt<=nptBins;ipt++)
  {
    lResbos->SetBinContent(ipt,lRH->GetBinContent(ipt));
    lResbos->SetBinError(ipt,lRH->GetBinError(ipt));
    lPowheg -> SetBinContent(ipt,h1_Powheg->GetBinContent(ipt));
    lPowheg -> SetBinError(ipt,h1_Powheg->GetBinError(ipt));
    lFEWZ -> SetBinContent(ipt,h_FEWZ->GetBinContent(ipt));
    lFEWZ -> SetBinError(ipt,sqrt(h_FEWZ->GetBinContent(ipt)));
    lData -> SetBinContent(ipt,h1_data->GetBinContent(ipt));
    //lData -> SetBinError(ipt,h1_data->GetBinError(ipt)+h_Total_Syst->GetBinError(ipt));
    //lData -> SetBinError(ipt,h1_data->GetBinError(ipt));
    lData -> SetBinError(ipt,h1_data->GetBinContent(ipt)*derr[ipt]/100.);
    //cout<<ipt<<"\t"<<h1_data->GetBinContent(ipt)*derr[ipt]/100.<<"\t Data: "<<lData -> GetBinError(ipt)<<endl;
    cout<<ipt<<"\t"<<h1_data->GetBinContent(ipt)<<endl;
  }
  lData->Scale(1./18.429); 
  lPowheg->Scale(1./18.429);

  for( int ipt(0);ipt<nptBins;ipt++)
  {
    
    ay[ipt] = lRH->GetBinContent(ipt+1);
    aeyl[ipt] = lRH->GetBinError(ipt+1);
   
    aeylLow[ipt] = lRH->GetBinContent(ipt+1)-h_resbos34->GetBinContent(ipt+1);
    aeylHigh[ipt] = h_resbos31->GetBinContent(ipt+1) -lRH->GetBinContent(ipt+1);
    cout<<ipt<<"\t"<<aeylLow[ipt]<<"\t"<<aeylHigh[ipt]<<endl;
    //aeylLow[ipt] = lRH->GetBinError(ipt+1);
    //aeylHigh[ipt] = lRH->GetBinError(ipt+1);
    
    //ay34[ipt] = h_resbos34->GetBinContent(ipt+1);
    //aeyl34[ipt] = h_resbos34->GetBinError(ipt+1);
    
    by[ipt] = lPowheg->GetBinContent(ipt+1);
//    beyl[ipt] = lPowheg->GetBinError(ipt+1);
    //beyl[ipt] = sqrt(lRH->GetBinContent(ipt+1));
    beyl[ipt] = sqrt(lPowheg->GetBinContent(ipt+1));
    
    cy[ipt] = h_FEWZ->GetBinContent(ipt+1);
    ceyl[ipt] = h_FEWZ->GetBinError(ipt+1);
    //ceyl[ipt] = sqrt(h_FEWZ->GetBinContent(ipt+1));
    
    dy[ipt] = lData->GetBinContent(ipt+1);
    deyl[ipt] = lData->GetBinError(ipt+1);
  }

//  TGraphAsymmErrors* fewz = new TGraphAsymmErrors(nptBins, ax, cy, aexl, aexh, ceyl, ceyh);
  TGraphErrors* fewz = new TGraphErrors(nptBins, ax, cy, aexl, ceyl);
//  fewz->GetYaxis()->SetTitleSize(0.04);
//  fewz->GetYaxis()->SetLabelSize(0.04);
//  fewz->GetXaxis()->SetLabelSize(0.0);
//  fewz->GetYaxis()->SetTitle("xsec [pb]");
//  fewz->SetTitle("xsec [pb]");
  fewz->SetFillColor(kBlue);
  fewz->SetFillStyle(3004);

//  TGraphAsymmErrors* powheg = new TGraphAsymmErrors(nptBins, ax, by, aexl, aexh, beyl, beyh);
  TGraphErrors* powheg = new TGraphErrors(nptBins, ax, by, aexl, beyl);
  powheg->SetFillColor(kRed);
//  powheg->SetFillColor(kYellow);
  //powheg->SetFillStyle(1001);
  powheg->SetFillStyle(3003);

//  TGraphAsymmErrors* resbos = new TGraphAsymmErrors(nptBins, ax, ay, aexl, aexh, aeyl, aeyh);
  //TGraphErrors* resbos = new TGraphErrors(nptBins, ax, ay, aexl, aeyl);
  TGraphAsymmErrors* resbos = new TGraphAsymmErrors(nptBins, ax, ay, aexlLow,aexlHigh, aeylLow, aeylHigh);
  resbos->SetFillColor(kGreen);
//  resbos->SetFillColor(kRed);
  resbos->SetFillStyle(3005);
  TGraphErrors* resbos34 = new TGraphErrors(nptBins, ax, ay34, aexl, aeyl34);
  resbos34->SetFillColor(kGreen);
//  resbos->SetFillColor(kRed);
  resbos34->SetFillStyle(3005);

//  TGraphAsymmErrors* data = new TGraphAsymmErrors(nptBins, ax, dy, aexl, aexh, deyl, deyh);
  TGraphErrors* data = new TGraphErrors(nptBins, ax, dy, aexl, deyl);
//  data->SetFillColor(kRed);
//  data->SetFillStyle(3005);

//  lResbos->SetLineWidth(2); lResbos->SetLineColor(kGreen);
  lResbos->SetFillColor(kGreen); lResbos->SetFillStyle(3004);
//  lResbos->SetMarkerStyle(kFullSquare); lResbos->SetMarkerColor(kGreen); lResbos->SetMarkerSize(5.6); lResbos->SetFillStyle(3004);
//  lPowheg->SetLineWidth(2); lPowheg->SetLineColor(kRed);
  lPowheg->SetFillColor(kRed); lPowheg->SetFillStyle(1001);
//  lPowheg->SetMarkerStyle(kFullSquare); lPowheg->SetMarkerColor(kRed); lPowheg->SetMarkerSize(5.6);// lPowheg->SetFillStyle(1001); lPowheg->SetMarkerSize(4);
  lFEWZ->SetFillColor(kBlue); lFEWZ->SetFillStyle(3005);
//  lPowheg->SetLineColor(kRed); lPowheg->SetMarkerStyle(kFullSquare); lPowheg->SetMarkerColor(kRed); lPowheg->SetMarkerSize(5.6);// lPowheg->SetFillStyle(1001); lPowheg->SetMarkerSize(4);
  lData->SetMarkerStyle(kFullCircle); lData->SetMarkerColor(kBlack); lData->SetMarkerSize(1);
	
  cout << "Resbos Total Xsec: " << lResbos->Integral() << endl;
  cout << "Data Total Xsec: " << lData->Integral() << endl;

//  lData->Scale(1./lData->Integral()); 
//  lResbos->Scale(1./lResbos->Integral());
//  lPowheg->Scale(1./lPowheg->Integral());

  TLegend *lL =new TLegend(0.6,0.65,0.92,0.85); lL->SetFillColor(0); lL->SetBorderSize(0);
//  lL->AddEntry(lData,"Unfolded","PL");
//  lL->AddEntry(lFEWZ,"FEWZ CTEQ12 NNLO","p");
//  lL->AddEntry(lPowheg,"Powheg CT10 NLO","p");
//  lL->AddEntry(lResbos,"ResBos CT10 NNLO","p");
  lL->AddEntry(data,"Unfolded","PL");
  lL->AddEntry(powheg,"Powheg CT10 NLO","f");
  lL->AddEntry(fewz,"FEWZ CTEQ12 NNLO","f");
  lL->AddEntry(resbos,"ResBos CT10 NNLO","f");
  
  TCanvas *lC0 = new TCanvas("Can","Can",800,800); lC0->cd(); lC0->SetLogy();
  lC0->Divide(1,2,0,0);
  lC0->cd(1)->SetPad(0,0.35,0.95,1.0);
  lC0->cd(1)->SetTopMargin(0.1);
  lC0->cd(1)->SetBottomMargin(0.01);
  lC0->cd(1)->SetLeftMargin(0.15);
  lC0->cd(1)->SetRightMargin(0.07);
  lC0->cd(1)->SetTickx(1);
  lC0->cd(1)->SetTicky(1);
  gStyle->SetLineWidth(2.);
  gStyle->SetOptStat(0);

//  gPad->SetLogy(1);
//  lResbos->SetMinimum(2e-5*(lResbos->GetMaximum()));
//  lResbos->SetMaximum(3.0*(lResbos->GetMaximum()));
  lFEWZ->GetYaxis()->SetTitleOffset(1.2);
  lFEWZ->GetYaxis()->SetTitleSize(0.04);
  lFEWZ->GetYaxis()->SetLabelSize(0.04);
  lFEWZ->GetXaxis()->SetLabelSize(0.0);
  lFEWZ->GetYaxis()->SetTitle("xsec [pb]");
/*
  gStyle->SetErrorX();
  lFEWZ->Draw("p0");
  lPowheg->Draw("e3 same");
  lResbos->Draw("e4 same");
  lData->Draw("E1 SAME");
*/  

  powheg->GetYaxis()->SetRangeUser(0.,1000);
  powheg->SetTitle("");
  powheg->GetYaxis()->SetTitle("Xsec [pb]");
  powheg->GetYaxis()->SetTitleOffset(1.2);
  
  powheg->Draw("A2");
  fewz->Draw("2");
  resbos->Draw("2");
//  resbos34->Draw("2");
  data->Draw("p");
//  gPad->Update();
  lL->Draw();

//  TPaveText *txt = new TPaveText(0.6,0.65,1.45,0.85,"NDC");
//  gPad->GetPrimitive("txt");
//  txt->SetFillStyle(0);
//  txt->SetBorderSize(0);
//  txt->SetTextSize(0.04);
//  txt->SetTextAlign(12);
//  txt->AddText("#int Ldt #approx 18.98 pb^{-1}");
//  txt->AddText("Data 2012, #sqrt{s}=8 TeV");
//  txt->Draw();
//  gPad->Modified();
//  gPad->cd();
  
  lC0->cd(2)->SetPad(0,0,0.95,0.34);
  lC0->cd(2)->SetTopMargin(0.025);
  lC0->cd(2)->SetBottomMargin(0.3);
  lC0->cd(2)->SetLeftMargin(0.15);
  lC0->cd(2)->SetRightMargin(0.07);
  lC0->cd(2)->SetTickx(1);
  lC0->cd(2)->SetTicky(1);
  //drawDifference(lData,lResbos);
  drawDifference(lData,lResbos,resbos);
  //lC0->SaveAs("WpenPt_ResultSqrtErr.png");
  //lC0->SaveAs("WmenPt_Result.png");
  lC0->SaveAs("WmmnPt_Result.png");
  //lC0->SaveAs("WmmnPt_Result.png");
}

void theoryStudy_test() {
  //Prep();
  //std::string WPenu = "/d2/scratch/khakim/WAnalysis/CMSSW_5_2_6/src/KNUPhy/WAnalyzer/analysis/Unfolding/ResultWpToEleNuNom/Result_WpToEleNu.root";
  //std::string WMenu = "/d2/scratch/khakim/WAnalysis/CMSSW_5_2_6/src/KNUPhy/WAnalyzer/analysis/Unfolding/ResultWmToEleNuNom/Result_WmToEleNu.root";
  //std::string WPmunu = "/d2/scratch/khakim/WAnalysis/CMSSW_5_2_6/src/KNUPhy/WAnalyzer/analysis/Unfolding/ResultWpToMuNuNom/Result_WpToMuNu.root";
  //std::string WMmunu = "/d2/scratch/khakim/WAnalysis/CMSSW_5_2_6/src/KNUPhy/WAnalyzer/analysis/Unfolding/ResultWmToMuNuNom/Result_WmToMuNu.root";
  
  std::string WPenu = "../RstUnfold/Result_WpToMuNu.root";
  std::string WMenu = "../RstUnfold/Result_WmToMuNu.root";
  std::string WPmunu = "../RstUnfold/Result_WpToMuNu.root";
  std::string WMmunu = "../RstUnfold/Result_WmToMuNu.root";
  
  
  std::string WPRes = "resbosWp30.root";
  std::string WMRes = "resbosWm30.root";
  std::string lBase = "(category==1 || category==2)*(lep1->Pt()>-25 && lep2->Pt()>25 && dilep->M()>60 && dilep->M()<120)*(abs(lep1->Eta())<12.1 && abs(lep2->Eta())<12.1)";
  std::string lRBase = "(pt_1 > -25 && pt_2 > -25 && abs(eta_1) < 12.1 && abs(eta_2) < 12.1)";
  std::string lR2   = "/data/blue/pharris/Resbos/Z/convert/z_nnlo.root";

  //plotHelpComp2("npv","(runNum > 0)*"+lBase,10,-0.5,9.5,Zmumu,ZmumuMC,"npv");
 // plotHelpComp("y_B","vy","WT00*(pT_d1 > -25 && pT_d2 > -25 && abs(y_d1) < 12.1 && abs(y_d2) < 12.1)",lRBase,50,-6.,6.,ZRes,lR2,"y Boson ");
  //plotHelpComp("y_B","0.5*log((dilep.e()+dilep.pz())/(dilep.e()-dilep.pz()))","WT00*(pT_d1 > 25 && pT_d2 > 25 && abs(y_d1) < 2.1 && abs(y_d2) < 2.1)","(runNum > 0)*"+lBase,50,-3.,3.,ZRes,Zmumu,"Boson Rapidity");
  

  
  //    plotHelpComp("pT_B","BornEffCorr","WT00*(pT_d1 > 25 && abs(y_d1) < 2.5 )","(BornEffCorr>0)",600,0,600,WPRes,WPenu,"");
//    plotHelpComp("pT_B","BornEffCorr","WT00*(pT_d1 > 25 && abs(y_d1) < 2.5 )","(BornEffCorr>0)",600,0,600,WMRes,WMenu,"");
    //plotHelpComp("pT_B","BornEffCorr","WT00*(pT_d1 > 20 && abs(y_d1) < 2.1 )","(BornEffCorr>0)",600,0,600,WPRes,WPmunu,"");
    plotHelpComp("pT_B","BornEffCorr","WT00*(pT_d1 > 20 && abs(y_d1) < 2.1 )","(BornEffCorr>0)",600,0,600,WMRes,WMmunu,"");




// plotHelpComp("pT_B","genVPt","WT00*(pT_d1 > 20 && abs(y_d1) < 2.1 )","(runNum > 0 && q < 0)",50,0,250,WMRes,Wmunu,"p_{T} Boson (GeV)");

    // plotHelpComp("pT_B","genVPt","WT00*(pT_d1 > 25 && abs(y_d1) < 2.1 )","(runNum > 0 )",30,0,30,ZRes,ZmumuMC,"p_{T} Boson (GeV)");
    //    plotHelpComp("pT_B","genVPt","WT00*(pT_d1 > 20 && abs(y_d1) < 2.1 )","(runNum > 0 )",nptBins,xbins_pt,ZRes,"p_{T} Boson (GeV)");

  //plotHelpComp("y_B","genWY","WT00*(pT_d1 > 25 && abs(y_d1) < 2.1 )","(runNum > 0 && q > 0)",50,-3.,3.,WPRes,Wmunu," Boson Rapidity");
  //plotHelpComp("pT_d1","vpt_1","WT00*(pT_d1 > -25 && abs(y_d1) < 2.1 )","(runNum > 0 && q < 0)",50,0,50,WMRes,Wmunu,"p_{T} Boson (GeV)");
  
  //plotHelpComp("pT_d1","vpt_1","WT00*(pT_d1 > -25 && abs(y_d1) < 2.1 && M_B > 60 && M_B < 120 )","(abs(veta_1) < 2.1 && vmass > 60 && vmass < 120)",50,0,50,ZRes,ZEE,"p_{T} Boson (GeV)");
  //plotHelpComp("y_d1","veta_1","WT00*(pT_d1 > -25 && abs(y_d1) < 12.5 && M_B > 60 && M_B < 120 )","w*(vpt_1 > -25 && abs(veta_1) < 12.5 )",50,-7.,7.,ZRes,ZEE2,"#eta lepton");
  //plotHelpComp("pT_d2","vpt_2","WT00*(pT_d1 > 25 && abs(y_d1) < 12.5 && M_B > 60 && M_B < 120 )","w*(vpt_1 > 25 && abs(veta_1) < 12.5 )",50,0.,75.,ZRes,ZEE2,"#eta lepton");

}
