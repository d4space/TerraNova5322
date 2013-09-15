#include <iostream.h>
#define Nbin 10
void track_eta()
{
  TCanvas *myCan=new TCanvas("myCan","myCan");
  myCan->SetGrid();
  TFile *f_MC= new TFile("TnP_Tracking_dr030e030_MCetaplus.root","read");
  RooDataSet *datasetMC = (RooDataSet*)f_MC->Get("tpTreeSta/eff_eta_dr030e030/cnt_eff");
  cout<<"ntry: "<<datasetMC->numEntries()<<endl;
  double XMC[Nbin],XMCerrL[Nbin],XMCerrH[Nbin],YMC[Nbin],YMCerrLo[Nbin],YMCerrHi[Nbin];
  for(int i(0); i<datasetMC->numEntries();i++)
  {
    const RooArgSet &pointMC=*datasetMC->get(i);
    RooRealVar &etaMC=pointMC["eta"],&effMC = pointMC["efficiency"];
    XMC[i]=etaMC.getVal();
    XMCerrL[i]=-etaMC.getAsymErrorLo();
    XMCerrH[i]=etaMC.getAsymErrorHi();
    YMC[i]=effMC.getVal();
    YMCerrLo[i]=-effMC.getAsymErrorLo();
    YMCerrHi[i]=effMC.getAsymErrorHi();
  }
  grMC=new TGraphAsymmErrors(Nbin,XMC,YMC,XMCerrL,XMCerrH,YMCerrLo,YMCerrHi);
  grMC->SetLineColor(kRed);
  grMC->SetMarkerColor(kRed);
  grMC->Draw("AP");
  //grMC->Draw("psame");
  myCan->SaveAs("track_MCPlus_eta.png");
  myCan->SaveAs("track_MCPlus_eta.eps");

}
