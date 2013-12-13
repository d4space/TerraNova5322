#include <iostream.h>
#include <TMath.h>                  // ROOT math library


#define binSize	10
void trig_eta_P()
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

///*
  TFile *f_MC= new TFile("efficiency-mc-WCutToHLT_eta_P.root","read");
  RooDataSet *datasetMC = (RooDataSet*)f_MC->Get("WCutToHLT/efficiency/cnt_eff");
  //RooDataSet *datasetMC = (RooDataSet*)f_MC->Get("tpTree/Track_with_TightCombRelIso_to_Mu15_eta2p1_pt/fit_eff");
  cout<<"ntry: "<<datasetMC->numEntries()<<endl;

  double XMC[binSize],XMCerrL[binSize],XMCerrH[binSize],YMC[binSize],YMCerrLo[binSize],YMCerrHi[binSize];

  ofstream t_out;
  char t_outname[100];
  sprintf(t_outname,"trig_plus_MC.txt");
  t_out.open("trig_plus_MC.txt");

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
  
  grMC=new TGraphAsymmErrors(binSize,XMC,YMC,XMCerrL,XMCerrH,YMCerrLo,YMCerrHi);

cout << "MC efficiency:  " << i << endl;
t_out << i;
cout << "YMC:  " << effMC.getVal()<< " +/- " << - effMC.getAsymErrorLo() << endl;
t_out << "\t" << effMC.getVal();
cout << "YMCerrLo:  " <<- effMC.getAsymErrorLo() << endl;
t_out << "\t" <<- effMC.getAsymErrorLo();
cout << "YMCerrHi:  " << effMC.getAsymErrorHi() << endl;
t_out << "\t" << effMC.getAsymErrorHi() << endl;

}
 grMC=new TGraphAsymmErrors(binSize,XMC,YMC,XMCerrL,XMCerrH,YMCerrLo,YMCerrHi);

 t_out.close();
 

  grMC->SetLineColor(kRed);
  grMC->SetMarkerColor(kRed);
  grMC->SetMarkerStyle(22);
///**///

//*

  TFile *f_RD= new TFile("efficiency-data-WCutToHLT_eta_P.root","read");
  RooDataSet *datasetRD = (RooDataSet*)f_RD->Get("WCutToHLT/efficiency/cnt_eff");
  //RooDataSet *datasetMC = (RooDataSet*)f_MC->Get("tpTree/Track_with_TightCombRelIso_to_Mu15_eta2p1_pt/fit_eff");
  cout<<"ntry: "<<datasetRD->numEntries()<<endl;

  double XRD[binSize],XRDerrL[binSize],XRDerrH[binSize],YRD[binSize],YRDerrLo[binSize],YRDerrHi[binSize];

  ofstream t_out;
    char t_outname[100];
      sprintf(t_outname,"trig_plus_RD.txt");
        t_out.open("trig_plus_RD.txt");

  for(int i(0); i<datasetRD->numEntries();i++)
  {
    const RooArgSet &pointRD=*datasetRD->get(i);
    RooRealVar &ptRD=pointRD["probe_sc_eta"],&effRD = pointRD["efficiency"];
    XRD[i]=ptRD.getVal();
    XRDerrL[i]=-ptRD.getAsymErrorLo();
    XRDerrH[i]=ptRD.getAsymErrorHi();
    YRD[i]=effRD.getVal();
    YRDerrLo[i]=-effRD.getAsymErrorLo();
    YRDerrHi[i]=effRD.getAsymErrorHi();
  
//  grRD=new TGraphAsymmErrors(binSize,XRD,YRD,XRDerrL,XRDerrH,YRDerrLo,YRDerrHi);

cout << "RD efficiency:  " << i <<endl;
t_out << i;
cout << "YRD:  " << effRD.getVal()<< " +/- " <<- effRD.getAsymErrorLo() << endl;
t_out << "\t" << effRD.getVal();
cout << "YRDerrLo:  " <<- effRD.getAsymErrorLo() << endl;
t_out << "\t" <<- effRD.getAsymErrorLo();
cout << "YRDerrHi:  " << effRD.getAsymErrorHi() << endl;
t_out << "\t" << effRD.getAsymErrorHi() << endl;



cout << "Scale factor: " <<i<< " = " <<YRD[i]/YMC[i] <<"+/-"<<(YRD[i]/YMC[i])*(sqrt((YRDerrLo[i]*YRDerrLo[i])/YRD[i]/YRD[i]+(YMCerrLo[i]*YMCerrLo[i])/YMC[i]/YMC[i]))<<endl;

//cout << "Scale factor  " << effRD.getVal()/effMC.getVal() << endl;
//cout<<"Lo:"<<effRD.getVal()/effMC.getVal()*sqrt(effRD.getAsymErrorLo()*effRD.getAsymErrorLo()/effRD.getVal()/effRD.getVal() + effMC.getAsymErrorLo()*effMC.getAsymErrorLo()/effMC.getVal()/effMC.getVal() ) <<  endl;


//cout<<"High:"<<effRD.getVal()/effMC.getVal()*sqrt(effRD.getAsymErrorHi()*effRD.getAsymErrorHi()/effRD.getVal()/effRD.getVal() + effMC.getAsymErrorHi()*effMC.getAsymErrorHi()/effMC.getVal()/effMC.getVal() ) <<  endl;

}
 grRD=new TGraphAsymmErrors(binSize,XRD,YRD,XRDerrL,XRDerrH,YRDerrLo,YRDerrHi);

  grRD->SetLineColor(kBlue);
  grRD->SetMarkerColor(kBlue);
  grRD->SetMarkerStyle(20);
///***///

  //myCan->SetLogx();
// grMC->Draw("AP");

  grRD->Draw("AP");
  grRD->SetMinimum(0.0);
  grRD->SetMaximum(1.0);
  grRD->GetXaxis()->SetLimits(-3, 3);
  grRD->GetXaxis()->SetNdivisions(505);
//  grRD->GetXaxis()->SetTitle("|#eta|");
  grRD->GetXaxis()->SetTitle("#eta");
  grMC->Draw("psame");
  grRD->GetYaxis()->SetTitle("Efficiency");
  grMC->Draw("psame");

//TLegend *Lgd = new TLegend(.70, .30,.80,.40);
TLegend *Lgd = new TLegend(.70, .20,.90,.30);
Lgd->AddEntry(grMC,"MC(DYToEE)","lep");
Lgd->AddEntry(grRD,"RD(19.619/fb)","lep");
Lgd->SetFillColor(0);
Lgd->Draw();

 //grRD->Draw("AP");
 //grMC->Draw("psame");
  myCan->SaveAs("trig_eta_P.png");
  myCan->SaveAs("trig_eta_P.eps");

}
