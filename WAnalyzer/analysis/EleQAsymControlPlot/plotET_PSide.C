{
  TString DIR = "ElectronHighPU";
  TString fileNM[] = {"RD_HighPU","WpToENu_S10","WmToENu_S10","WpToTauNu_S10","WmToTauNu_S10","DYToEE_S10","TTJets_S10","DYToTauTau_S10","G_Pt50to80_S10","TT_CT10_S10",/*"WJetsToLNu_S10",*/"DYJetsToLL_S10","QCD30to50_S10","QCD50to80_S10","QCD80to120_S10","QCD120to170_S10"};
  TString filePath[15];

  const Color_t bgdColor[15] ={kBlack,kRed,kAzure+1,kOrange,kTeal,kRed+1, kGreen, kBlue+1, kBlue+2,/* kBlue+3,*/kBlue,kTeal+2,kGray+2,kGray+2,kGray+2,kGray+2};

  TLegend * lgc = new TLegend(0.59, 0.67, 0.89, 0.89);
  lgc->SetTextSize(0.03);
  lgc->SetBorderSize(0);
  lgc->SetFillColor(0);

  THStack *hs_WSide_MET = new THStack("hs_WSide_MET","WSide_MET");


  TString str_ieta[22]={"eta_00_01","eta_01_02","eta_02_03","eta_03_04","eta_04_05",
			"eta_05_06","eta_06_07","eta_07_08","eta_08_09","eta_09_10","eta_10_11",
			"eta_11_12","eta_12_13","eta_13_14","eta_16_17","eta_17_18","eta_18_19",
			"eta_19_20","eta_20_21","eta_21_22","eta_22_23","eta_23_24"};

  TString str_etaId[22]={"0","1","2","3","4",
			 "5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20","21"};

  TH1D *h_MET;
  TH1D *h_MET_RD;
  
  THStack *hs_WSide_MET_eta[22];
  TLegend *lg[22];

    for(Int_t ieta=0;ieta<22;ieta++){
      TString nameA = "hs_WSide_MET_0_"+str_ieta[ieta];
      TString nameB = "_"+str_ieta[ieta];
      hs_WSide_MET_eta[ieta] = new THStack(nameA, nameB);

      lg[ieta] = new TLegend(0.59, 0.67, 0.89, 0.89);
      lg[ieta]->SetTextSize(0.03);   lg[ieta]->SetBorderSize(0);  lg[ieta]->SetFillColor(0);
    }
  

  for(Int_t i=14;i>-1;i--)
    {
      filePath[i]= DIR+"/Ele_"+fileNM[i]+"_Analysis.root";
      cout<<filePath[i] <<endl;

      TFile *f_file = new TFile(filePath[i]);
      h1_WpSide_Neu_eta_0->SetLineColor(bgdColor[i]);
      h1_WpSide_Neu_eta_0->SetFillColor(bgdColor[i]);
      h1_WpSide_Neu_eta_0->SetFillStyle(1001);


      if( ! (i==0 || i>10) ){  
	  for(Int_t iieta=0;iieta<22;iieta++){
	    TString histnm = "h1_WpSide_Neu_eta_"+str_etaId[iieta];
	    h_MET = 0;
	    f_file->GetObject(histnm,h_MET);
	    h_MET->SetLineColor(bgdColor[i]);
            h_MET->SetFillColor(bgdColor[i]);
            h_MET->SetFillStyle(1001);
	    hs_WSide_MET_eta[iieta]->Add(h_MET);
	    lg[iieta]->AddEntry(h_MET,fileNM[i],"F");
	  }
	
	hs_WSide_MET->Add(h1_WpSide_Neu_eta_0);   
	lgc->AddEntry(h1_WpSide_Neu_eta_0,fileNM[i],"F");
    }
  }  
  TCanvas *c1 = new TCanvas();
  TFile *f_fileRD = new TFile(filePath[0]);  

  
  lgc->AddEntry(h1_WpSide_Neu_eta_0,"2012RealData 19.619/fb", "LP");
  h1_WpSide_Neu_eta_0->SetMarkerStyle(20);  h1_WpSide_Neu_eta_0->SetMarkerSize(1); //h1_WSide_Neu_pt->SetMaximum(200000);
  h1_WpSide_Neu_eta_0->Draw("e");
  hs_WSide_MET->Draw("same");
  h1_WpSide_Neu_eta_0->Draw("same e");
  h1_WSide_Neu_eta_0->GetXaxis()->SetTitle("MET");
  h1_WSide_Neu_eta_0->GetYaxis()->SetTitle("# of event");
  lgc->Draw();
  c1->SaveAs("WpSide_Neu_eta_0.png");


  TCanvas *cvs[22];
    for(Int_t iiieta=0;iiieta<22;iiieta++){
      cvs[iiieta] = new TCanvas();

      
      TFile *f_fileRD = new TFile(filePath[0]); 
      TString histnmRD = "h1_WpSide_Neu_eta_"+str_etaId[iiieta];
      cout<<" iiieta "<<iiieta<<endl;

      h_MET_RD = 0;
      f_fileRD->GetObject(histnmRD,h_MET_RD);
      h_MET_RD->SetMarkerStyle(20); h_MET_RD->SetMarkerSize(1);
      lg[iiieta]->AddEntry(h_MET_RD,"2012RealData 19.619/fb","LP");
            
      h_MET_RD->Draw("e");
      hs_WSide_MET_eta[iiieta]->Draw("same");
      h_MET_RD->Draw("same e");
      
      lg[iiieta]->Draw();
      TString SaveName = histnmRD+".png";
      cvs[iiieta] ->SaveAs(SaveName);
    }
  }

