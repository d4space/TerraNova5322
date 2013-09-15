#include <iostream.h>
#define binSize	10
void sc_wptCut_P_eta()
{
  TCanvas *myCan=new TCanvas("myCan","myCan");
  myCan->SetGrid();
  /************************
  TFile *f_RD= new TFile("TnP_Z_Trigger_RDpt.root","read");
  RooDataSet *dataset = (RooDataSet*)f_RD->Get("tpTree/Track_To_TightCombRelIso_Mu15_eta2p1_pt/fit_eff");
  cout<<"ntry: "<<dataset->numEntries()<<endl;
  double X[11],XerrL[11],XerrH[11],Y[11],YerrLo[11],YerrHi[11];
  for(int i(0); i<dataset->numEntries();i++)
  {
    const RooArgSet &point=*dataset->get(i);
    RooRealVar &pt=point["pt"],&eff = point["efficiency"];
    X[i]=pt.getVal();
    XerrL[i]=-pt.getAsymErrorLo();
    XerrH[i]=pt.getAsymErrorHi();
    Y[i]=eff.getVal();
    YerrLo[i]=-eff.getAsymErrorLo();
    YerrHi[i]=eff.getAsymErrorHi();
  }
  gr=new TGraphAsymmErrors(11,X,Y,XerrL,XerrH,YerrLo,YerrHi);
  gr->Draw("AP");
***************************/
  
//*
  TFile *f_MC= new TFile("efficiency-mc-SCToPfElectron_eta_P.root","read");
//  RooDataSet *datasetMC = (RooDataSet*)f_MC->Get("SuperClusterToPFElectron/SCtoWptCut_efficiency/cnt_eff");
RooDataSet *datasetMC = (RooDataSet*)f_MC->Get("SuperClusterToPFElectron/SCtoWptCut_efficiency/fit_eff");  
//RooDataSet *datasetMC = (RooDataSet*)f_MC->Get("tpTree/Track_with_TightCombRelIso_to_Mu15_eta2p1_pt/fit_eff");
  cout<<"ntry: "<<datasetMC->numEntries()<<endl;

  double XMC[binSize],XMCerrL[binSize],XMCerrH[binSize],YMC[binSize],YMCerrLo[binSize],YMCerrHi[binSize];
  for(int i(0); i<datasetMC->numEntries();i++)
  {
    const RooArgSet &pointMC=*datasetMC->get(i);
    RooRealVar &ptMC=pointMC["probe_sc_eta"],&effMC = pointMC["efficiency"];
    XMC[i]=ptMC.getVal();
    XMCerrL[i]=-ptMC.getAsymErrorLo();
    XMCerrH[i]=ptMC.getAsymErrorHi();
    YMC[i]=effMC.getVal();
    YMCerrLo[i]=-effMC.getAsymErrorLo();
    YMCerrHi[i]=effMC.getAsymErrorHi();



cout << "MC efficiency:  " << i <<endl;
cout << "YMC:  " << effMC.getVal()<< " +/- " << - effMC.getAsymErrorLo() << endl;
cout << "YMCerrLo:  " <<- effMC.getAsymErrorLo() << endl;
cout << "YMCerrHi:  " << effMC.getAsymErrorHi() << endl;




  }
  grMC=new TGraphAsymmErrors(binSize,XMC,YMC,XMCerrL,XMCerrH,YMCerrLo,YMCerrHi);

  grMC->SetLineColor(kRed);
  grMC->SetMarkerColor(kRed);
//*///

 TFile *f_RD= new TFile("efficiency-data-SCToPfElectron_eta_P.root","read");
  RooDataSet *datasetRD = (RooDataSet*)f_RD->Get("SuperClusterToPFElectron/SCtoWptCut_efficiency/fit_eff");
  //RooDataSet *datasetMC = (RooDataSet*)f_MC->Get("tpTree/Track_with_TightCombRelIso_to_Mu15_eta2p1_pt/fit_eff");
  cout<<"ntry: "<<datasetRD->numEntries()<<endl;

  double XMC[binSize],XMCerrL[binSize],XMCerrH[binSize],YMC[binSize],YMCerrLo[binSize],YMCerrHi[binSize];
//  double XRD[binSize],XRDerrL[binSize],XRDerrH[binSize],YRD[binSize],YRDerrLo[binSize],YRDerrHi[binSize];
  for(int i(0); i<datasetRD->numEntries();i++)
  {
    const RooArgSet &pointRD=*datasetRD->get(i);
    RooRealVar &ptRD=pointRD["probe_sc_eta"],&effRD = pointRD["efficiency"];
    XMC[i]=ptRD.getVal();
    XMCerrL[i]=-ptRD.getAsymErrorLo();
    XMCerrH[i]=ptRD.getAsymErrorHi();
    YMC[i]=effRD.getVal();
    YMCerrLo[i]=-effRD.getAsymErrorLo();
    YMCerrHi[i]=effRD.getAsymErrorHi();


cout << "RD efficiency:  " << i <<endl;
cout << "YRD:  " << effRD.getVal()<< " +/- " <<- effRD.getAsymErrorLo() << endl;
cout << "YRDerrLo:  " <<- effRD.getAsymErrorLo() << endl;
cout << "YRDerrHi:  " << effRD.getAsymErrorHi() << endl;

//cout << "Scale factor: " <<i<< " = " <<YRD[i]/YMC[i] <<"+/-"<<(YRD[i]/YMC[i])*(sqrt((YRDerrLo[i]*YRDerrLo[i])/YRD[i]/YRD[i]+(YMCerrLo[i]*YMCerrLo[i])/YMC[i]/YMC[i]))<<endl;

  }
     grRD=new TGraphAsymmErrors(binSize,XMC,YMC,XMCerrL,XMCerrH,YMCerrLo,YMCerrHi);
//    grRD=new TGraphAsymmErrors(binSize,XRD,YRD,XRDerrL,XRDerrH,YRDerrLo,YRDerrHi);
  grRD->SetLineColor(kBlue);
  grRD->SetMarkerColor(kBlue);



  //myCan->SetLogx();
  grRD->Draw("AP");
  grRD->SetMinimum(0.5);
//  grRD->SetMaximum(1.0);
//  grMC->Draw("AP");
  grMC->Draw("psame");
//  grRD->Draw("psame");  

grRD->GetXaxis()->SetNdivisions(505);
//grRD->GetYaxis()->SetNdivisions(505);

//TLegend *Lgd = new TLegend(.80, .80,.95,.95);
TLegend *Lgd = new TLegend(.70, .20,.80,.30);
Lgd->AddEntry(grMC,"MC","lep");
Lgd->AddEntry(grRD,"RD","lep");
Lgd->SetFillColor(0);
Lgd->Draw();

  //grMC->Draw("psame");
//  TLine *myLine=new TLine(25,0,25,1);
//  myLine->Draw("same");
  myCan->SaveAs("sc_wptCut_P_eta.png");
  myCan->SaveAs("sc_wptCut_P_eta.eps");

}
