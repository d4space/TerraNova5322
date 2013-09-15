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
  //Float_t y1[n1] ={114.7,122.5,132.5,138.8,131.7,122.2,179.6,153.3,151.5,178.3,165.6,157.5,147.6,183.3,203.1,229.0,247.8,256.4,287.0,252.1,301.7,261.3,260.2};
  Float_t y1[n1] ={115.1,132.9,126.9,170.6,160.1,158.2,161.9,212.6,250.6,275.8,269.5};
 // Float_t x1[n1] ={0.05,0.15,0.25,0.35,0.45,0.55,0.65,0.75,0.85,0.95,1.05,1.15,1.25,1.35,,1.65,1.75,1.85,1.95,2.05,2.15,2.25,2.35,2.45};
  Float_t x1[n1] ={0.1,0.3,0.5,0.7,0.9,1.1,1.3,1.7,1.9,2.1,2.3};
  //Float_t ey1[n1] ={3.1,3,2.7,3.2,3.1,3.1,3.8,3.7,3.7,4,4.3,4.9,4.9,4.9,5,4.8,4.5,5.1,5.7,6.1,6.6,8.4,9.9};
  Float_t ey1[n1] ={2.0,2.0,2.6,2.8,2.7,3.2,3.5,3.3,3.2,4.8,5.6};
  Float_t ex1[n1] ={0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1};
  //Float_t ex1[n1] ={0.05,0.05,0.05,0.05,0.05,0.05,0.05,0.05,0.05,0.05,0.05,0.05,0.05,0.05,0.05,0.05,0.05,0.05,0.05,0.05,0.05,0.05,0.05};
  TGraphErrors *gr1 = new TGraphErrors(n1,x1,y1,ex1,ey1);
  gr1->SetTitle("2012 corrected");
  gr1->SetMarkerColor(4);
  gr1->SetMarkerStyle(20);
//  gr1->SetLegend(0.78,0.65,.98,0.88);
  gr1->Draw("AP");
 // gr1->Draw("P");



  const Int_t n2=11;
  Float_t y2[n2] ={106.9,112.9,112.5,125.5,130.7,144.3,159.5,186.1,191.8,206.9,203.4};
  Float_t x2[n2] ={0.1,0.3,0.5,0.7,0.9,1.1,1.3,1.7,1.9,2.1,2.3};
  Float_t ey2[n2] ={2.7,2.7,2.7,2.7,2.7,2.9,3.0,3.4,3.2,3.3,4.1};
  Float_t ex2[n2] ={0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1};
  TGraphErrors *gr2 = new TGraphErrors(n2,x2,y2,ex2,ey2);
  gr2->SetTitle("2011");
  gr2->SetMarkerColor(7);
  gr2->SetMarkerStyle(20);
  gr2->Draw("P");
 

  const Int_t n3=11;
  Float_t y3[n3] ={116.4,134.3,126.9,172.7,161.6,158.1,162.6,212.6,250.7,275.9,264.4};
  Float_t x3[n3] ={0.1,0.3,0.5,0.7,0.9,1.1,1.3,1.7,1.9,2.1,2.3};
  Float_t ey3[n3] ={2.0,2.0,2.6,2.8,2.7,3.2,3.5,3.3,3.2,4.8,5.6};
  Float_t ex3[n3] ={0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1};
  TGraphErrors *gr3 = new TGraphErrors(n3,x3,y3,ex3,ey3);
  gr3->SetTitle("2012 mesured");
  gr3->SetMarkerColor(13);
  gr3->SetMarkerStyle(20);
  gr3->Draw("P");

  const Int_t n4=11;
  Float_t y4[n4] ={113,116,120,129,139,149,163,198,214,231,239};
  Float_t x4[n4] ={0.1,0.3,0.5,0.7,0.9,1.1,1.3,1.7,1.9,2.1,2.3};
  Float_t ey4[n4] ={2.0,2.0,2.6,2.8,2.7,3.2,3.5,3.3,3.2,4.8,5.6};
  Float_t ex4[n4] ={0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1};
  TGraphErrors *gr4 = new TGraphErrors(n4,x4,y4,ex4,ey4);
  gr4->SetTitle("MonteCarlo");
  gr4->SetMarkerColor(2);
  gr4->SetMarkerStyle(20);
  gr4->Draw("P");


    TLegend * lg = new TLegend(0.15, 0.81, 0.52, 0.99);
    lg->SetTextSize(0.05);
    lg->SetBorderSize(0);
    lg->SetFillColor(0);
	    
    lg->AddEntry(gr1, "2012 corrected", "lep");
    lg->AddEntry(gr2, "2011", "lep");
    lg->AddEntry(gr3, "2012 measured", "lep");
    lg->AddEntry(gr4, "MonteCarlo", "lep");
    lg->Draw();
		  



 // c1->Update();

  c1->SaveAs("ChargeAsymmetry.png");
 
}


