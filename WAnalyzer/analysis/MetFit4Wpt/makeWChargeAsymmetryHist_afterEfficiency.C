#include <iostream>
#include "TFile.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TFrame.h"

void
makeWChargeAsymmetryHist_afterEfficiency(){

  TCanvas *c1 = new TCanvas("c1","W Charge Asymmetry",400,2.5,700,500);    

//  c1->SetFillColor(42);
//  c1->SetGrid();
 
  
  TH1F *hr = c1->DrawFrame(-0.4,0,1.2,12);
  hr->SetXTitle("pseudo-rapidity");
  hr->SetYTitle("Charge Asymmetry");
//  c1->GetFrame()->SetFillCollor(21);
//  c1->GetFrame()->GetBorderSize(12);

  
  
  


  const Int_t n1=11;
  Float_t y1[n1] ={106.9,112.9,112.5,125.5,130.7,144.3,159.5,186.1,191.8,206.9,203.4};
  Float_t x1[n1] ={0.1,0.3,0.5,0.7,0.9,1.1,1.3,1.7,1.9,2.1,2.3};
  Float_t ey1[n1] ={1.5,1.7,1.4,1.7,1.8,1.9,2.3,1.9,1.6,1.9,2.4};
  Float_t ex1[n1] ={0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1};
  TGraphErrors *gr1 = new TGraphErrors(n1,x1,y1,ex1,ey1);
  gr1->SetTitle("2011 pt>35GeV");
  //gr1->SetLineColor(7);
  gr1->GetXaxis()->SetTitle("pseudo-rapidity") ;
  gr1->GetYaxis()->SetTitle("Charge Asymmetry") ;
  gr1->SetMinimum(40);
  gr1->SetMaximum(280);
  gr1->SetMarkerColor(7);
  gr1->SetMarkerStyle(21);
  gr1->SetMarkerSize(0.5);
  gr1->Draw("AP");
 
  const Int_t n2=11;
  //Float_t y2[n2] ={95.1,94.6,99.2,108,117,125,135,171,186,204,216};
  Float_t y2[n2] ={95.1,94.6,99.2,108,117,125,135,171,186,204,216};
  Float_t x2[n2] ={0.1,0.3,0.5,0.7,0.9,1.1,1.3,1.7,1.9,2.1,2.3};
  Float_t ey2[n2] ={};
  Float_t ex2[n2] ={0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1};
  TGraphErrors *gr2 = new TGraphErrors(n2,x2,y2,ex2,ey2);
  gr2->SetTitle("2012 MonteCarlo pt>35GeV");
  gr2->SetMarkerColor(4);
  //gr2->SetMarkerStyle(20);
  gr2->SetMarkerStyle(20);
  gr2->SetMarkerSize(0.5);
  gr2->SetLineColor(4);
  gr2->Draw("P");

/*
  const Int_t n3=11;
  Float_t y3[n3] ={116.4,134.3,126.9,172.7,161.6,158,162.6,212.6,250.7,275.9,264.4};
  Float_t x3[n3] ={0.1,0.3,0.5,0.7,0.9,1.1,1.3,1.7,1.9,2.1,2.3};
  Float_t ey3[n3] ={2.0,2.0,2.6,2.8,2.7,3.2,3.5,3.3,3.2,4.8,5.6};
  Float_t ex3[n3] ={0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1};
  TGraphErrors *gr3 = new TGraphErrors(n3,x3,y3,ex3,ey3);
  gr3->SetTitle("2012 RD total pt>30GeV");
  gr3->SetMarkerColor(5);
  gr3->SetMarkerStyle(20);
  gr3->Draw("P");
*/
  
  const Int_t n4=11;
  //Float_t y4[n4] ={96.76,106.86,100.98,111.31,126.32,124.62,134.62,168.01,194.28,222.09,219.00};
  Float_t y4[n4] ={95.39,98.04,111.44,114.09,117.42,125.41,133.08,166.72,185.15,199.22,207.79};
  Float_t x4[n4] ={0.1,0.3,0.5,0.7,0.9,1.1,1.3,1.7,1.9,2.1,2.3};
  //Float_t ey4[n4] ={0.83,1.63,0.92,0.87,1.47,1.68,1.16,2.67,2.49,2.64,3.44};
  Float_t ey4[n4] ={1.4,1.3,2.77,1.32,1.34,1.37,1.22,1.93,1.57,1.94,2.51};
  Float_t ex4[n4] ={0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1};
  TGraphErrors *gr4 = new TGraphErrors(n4,x4,y4,ex4,ey4);
  gr4->SetTitle("2012 RD total pt>35GeV uncorrected");
  gr4->SetMarkerColor(2);
  //gr4->SetMarkerStyle(22);
  gr4->SetMarkerStyle(22);
  gr4->SetMarkerSize(0.5);
  gr4->SetLineColor(2);
  gr4->Draw("P");
			  /*
  const Int_t n5=11;
  Float_t y5[n5] ={99.0,101.9,100.5,112.0,125.2,120.3,132.0,170.5,196.5,224.0,220.0};
  Float_t x5[n5] ={0.1,0.3,0.5,0.7,0.9,1.1,1.3,1.7,1.9,2.1,2.3};
  Float_t ey5[n5] ={1.6,1.4,1.6,1.0,1.6,0.9,1.0,2.5,2.7,2.5,3.5};
  Float_t ex5[n5] ={0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1};
  TGraphErrors *gr5 = new TGraphErrors(n5,x5,y5,ex5,ey5);
  gr5->SetTitle("2012 RD total pt>35GeV corrected");
  gr5->SetMarkerColor(6);
  gr5->SetMarkerStyle(1);
  gr5->SetLineColor(6);
  gr5->Draw("P");
*/
/*
  const Int_t n6=11;
  Float_t y6[n6] ={121,117,123,131,142,150,151,192,212,223,246};
  Float_t x6[n6] ={0.1,0.3,0.5,0.7,0.9,1.1,1.3,1.7,1.9,2.1,2.3};
  Float_t ey6[n6] ={2.0,2.0,2.6,2.8,2.7,3.2,3.5,3.3,3.2,4.8,5.6};
  Float_t ex6[n6] ={0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1};
  TGraphErrors *gr6 = new TGraphErrors(n6,x6,y6,ex6,ey6);
  gr6->SetTitle("2012 RD A pt>30GeV");
  gr6->SetMarkerColor(5);
  gr6->SetMarkerStyle(20);
  gr6->Draw("P");
*/
  /*
  const Int_t n66=11;
  Float_t y66[n66] ={105.2,100,101.3,110.3,122.2,133.1,129.4,164.1,184.7,205.9,224.7};
  Float_t x66[n66] ={0.1,0.3,0.5,0.7,0.9,1.1,1.3,1.7,1.9,2.1,2.3};
  Float_t ey66[n66] ={2.0,2.0,2.6,2.8,2.7,3.2,3.5,3.3,3.2,4.8,5.6};
  Float_t ex66[n66] ={0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1};
  TGraphErrors *gr66 = new TGraphErrors(n66,x66,y66,ex66,ey66);
  gr66->SetTitle("2012 RD A pt>35GeV");
  gr66->SetMarkerColor(4);
  gr66->SetMarkerStyle(22);
  gr66->Draw("P");
*/
/*
  const Int_t n7=11;
  Float_t y7[n7] ={104,120,115,144,149,154,159,196,228,236,224};
  Float_t x7[n7] ={0.1,0.3,0.5,0.7,0.9,1.1,1.3,1.7,1.9,2.1,2.3};
  Float_t ey7[n7] ={2.0,2.0,2.6,2.8,2.7,3.2,3.5,3.3,3.2,4.8,5.6};
  Float_t ex7[n7] ={0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1};
  TGraphErrors *gr7 = new TGraphErrors(n7,x7,y7,ex7,ey7);
  gr7->SetTitle("2012 RD B pt>30GeV");
  gr7->SetMarkerColor(5);
  gr7->SetMarkerStyle(20);
  gr7->Draw("P");
*/
/*
  const Int_t n77=11;
  Float_t y77[n77] ={97,105.6,93.9,124.4,126.4,126.2,135.5,164.8,201.5,216.2,202.9};
  Float_t x77[n77] ={0.1,0.3,0.5,0.7,0.9,1.1,1.3,1.7,1.9,2.1,2.3};
  Float_t ey77[n77] ={2.0,2.0,2.6,2.8,2.7,3.2,3.5,3.3,3.2,4.8,5.6};
  Float_t ex77[n77] ={0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1};
  TGraphErrors *gr77 = new TGraphErrors(n77,x77,y77,ex77,ey77);
  gr77->SetTitle("2012 RD B pt>35GeV");
  gr77->SetMarkerColor(4);
  gr77->SetMarkerStyle(22);
  gr77->Draw("P");
*/
/*  
  const Int_t n8=11;
  Float_t y8[n8] ={111,121,122,148,150,150,156,196,229,240,242};
  Float_t x8[n8] ={0.1,0.3,0.5,0.7,0.9,1.1,1.3,1.7,1.9,2.1,2.3};
  Float_t ey8[n8] ={2.0,2.0,2.6,2.8,2.7,3.2,3.5,3.3,3.2,4.8,5.6};
  Float_t ex8[n8] ={0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1};
  TGraphErrors *gr8 = new TGraphErrors(n8,x8,y8,ex8,ey8);
  gr8->SetTitle("2012 RD C pt>30GeV");
  gr8->SetMarkerColor(5);
  gr8->SetMarkerStyle(20);
  gr8->Draw("P");
*/
/*  
  const Int_t n88=11;
  Float_t y88[n88] ={97.5,105.6,105.2,138.9,129.2,123.9,138.9,166.3,196.9,225.7,222.2};
  Float_t x88[n88] ={0.1,0.3,0.5,0.7,0.9,1.1,1.3,1.7,1.9,2.1,2.3};
  Float_t ey88[n88] ={2.0,2.0,2.6,2.8,2.7,3.2,3.5,3.3,3.2,4.8,5.6};
  Float_t ex88[n88] ={0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1};
  TGraphErrors *gr88 = new TGraphErrors(n88,x88,y88,ex88,ey88);
  gr88->SetTitle("2012 RD C pt>35GeV");
  gr88->SetMarkerColor(4);
  gr88->SetMarkerStyle(22);
  gr88->Draw("P");
*/
/*
  const Int_t n9=11;
  Float_t y9[n9] ={110,123,177,129,143,140,148,193,228,239,243};
  Float_t x9[n9] ={0.1,0.3,0.5,0.7,0.9,1.1,1.3,1.7,1.9,2.1,2.3};
  Float_t ey9[n9] ={2.0,2.0,2.6,2.8,2.7,3.2,3.5,3.3,3.2,4.8,5.6};
  Float_t ex9[n9] ={0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1};
  TGraphErrors *gr9 = new TGraphErrors(n9,x9,y9,ex9,ey9);
  gr9->SetTitle("2012 RD D pt>30GeV");
  gr9->SetMarkerColor(5);
  gr9->SetMarkerStyle(20);
  gr9->Draw("P");
*/
/*
  const Int_t n99=11;
  Float_t y99[n99] ={42.1,107,158,109.5,124.5,122.2,130.7,165.4,196.5,217.5,223};
  Float_t x99[n99] ={0.1,0.3,0.5,0.7,0.9,1.1,1.3,1.7,1.9,2.1,2.3};
  Float_t ey99[n99] ={2.0,2.0,2.6,2.8,2.7,3.2,3.5,3.3,3.2,4.8,5.6};
  Float_t ex99[n99] ={0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1};
  TGraphErrors *gr99 = new TGraphErrors(n99,x99,y99,ex99,ey99);
  gr99->SetTitle("2012 RD D pt>35GeV");
  gr99->SetMarkerColor(4);
  gr99->SetMarkerStyle(22);
  gr99->Draw("P");
*/





    TLegend * lg = new TLegend(0.15, 0.71, 0.52, 0.89);
    lg->SetTextSize(0.05);
    lg->SetBorderSize(0);
    lg->SetFillColor(0);
	    
    lg->AddEntry(gr1, "2011(7TeV), 0.84/fb", "lep");
    lg->AddEntry(gr2, "2012 MC(8TeV)", "lep");
//    lg->AddEntry(gr3, "2012 RD total pt>30GeV", "lep");
    lg->AddEntry(gr4, "2012 RD(8TeV) uncorrected, 19.619/fb", "lep");
//    lg->AddEntry(gr5, "2012 RD corrected", "lep");
//    lg->AddEntry(gr6, "2012 RD A  pt>30GeV", "lep");
//    lg->AddEntry(gr66, "2012 RD A", "lep");
//    lg->AddEntry(gr7, "2012 RD B  pt>30GeV", "lep");
//    lg->AddEntry(gr77, "2012 RD B", "lep");
//    lg->AddEntry(gr8, "2012 RD C  pt>30GeV", "lep");
//    lg->AddEntry(gr88, "2012 RD C", "lep");
//    lg->AddEntry(gr9, "2012 RD D  pt>30GeV", "lep");
//    lg->AddEntry(gr99, "2012 RD D", "lep");
    lg->Draw();
		  



 // c1->Update();

  c1->SaveAs("ChargeAsymmetry.png");
 
}


