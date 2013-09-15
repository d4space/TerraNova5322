{
  TString DIR = "ElectronHighPU";
  TString fileNM[] = {"RD_HighPU","WpToENu_S10","WmToENu_S10","WpToTauNu_S10","WmToTauNu_S10","DYToEE_S10","TTJets_S10", "DYToTauTau_S10", "G_Pt50to80_S10", "TT_CT10_S10", /*"WJetsToLNu_S10",*/ "DYJetsToLL_S10", "QCD30to50_S10","QCD50to80_S10","QCD80to120_S10","QCD120to170_S10"};
  TString filePath[15];

  const Color_t bgdColor[15] ={kBlack,kRed,kAzure+1,kOrange,kTeal,kRed+1,kGreen, kBlue+1, kBlue+2/*, kBlue+3*/,kBlue,kTeal+2,kGray+2,kGray+2,kGray+2,kGray+2};

  TLegend * lgc = new TLegend(0.59, 0.67, 0.89, 0.89);
  lgc->SetTextSize(0.03);
  lgc->SetBorderSize(0);
  lgc->SetFillColor(0);

//  THStack *hs_W_Lept1_pt = new THStack("hs_W_Lept1_pt","W_Lept1_pt");
  THStack *hs_W_Lept1_pt = new THStack("hs_W_Lept1_pt","W_Neu_All");


  TString str_pm[3]  ={"M","P","I"};
  TString str_ieta[22]={"eta_00_01","eta_01_02","eta_02_03","eta_03_04","eta_04_05",
			"eta_05_06","eta_06_07","eta_07_08","eta_08_09","eta_09_10","eta_10_11",
			"eta_11_12","eta_12_13","eta_13_14","eta_16_17","eta_17_18","eta_18_19",
			"eta_19_20","eta_20_21","eta_21_22","eta_22_23","eta_23_24"};

  TString str_etaId[22]={"0","1","2","3","4",
			 "5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20","21"};

  TH1D *h_MET;
  TH1D *h_MET_RD;
  
  THStack *hs_MET_pm_ieta[3][22];
  TLegend *lg[3][22];

  for(Int_t ipm=0;ipm<3;ipm++){
    for(Int_t ieta=0;ieta<22;ieta++){
      TString nameA = "hs_MET_"+str_pm[ipm]+"_"+str_ieta[ieta];
      TString nameB = str_pm[ipm]+"_"+str_ieta[ieta];
      //hs_MET_pm_ieta[ipm][ieta] = new THStack("hs_MET_"+str_pm[pm]+"_"+str_ieta[ieta],str_pm[pm]+"_"+str_ieta[ieta]);
      hs_MET_pm_ieta[ipm][ieta] = new THStack(nameA, nameB);

      lg[ipm][ieta] = new TLegend(0.59, 0.67, 0.89, 0.89);
      lg[ipm][ieta]->SetTextSize(0.03);   lg[ipm][ieta]->SetBorderSize(0);  lg[ipm][ieta]->SetFillColor(0);
    }
  }

  for(Int_t i=14;i>-1;i--)
    {
      filePath[i]= DIR+"/Ele_"+fileNM[i]+"_Analysis.root";
      cout<<filePath[i] <<endl;

      TFile *f_file = new TFile(filePath[i]);
      h1_W_Lept1_pt->SetLineColor(bgdColor[i]);      h1_W_Lept1_pt->SetFillColor(bgdColor[i]); h1_W_Lept1_pt->SetFillStyle(1001);
//      h1_W_Neu_All->SetLineColor(bgdColor[i]);      h1_W_Neu_All->SetFillColor(bgdColor[i]); h1_W_Neu_All->SetFillStyle(1001);


      //      if(i>0){  
      //if( ! (i==0 || i==2 || i==3 || i>5) ){  
      if( ! (i==0 || i>10) ){  
	for(Int_t iipm=0;iipm<3;iipm++){
	  for(Int_t iieta=0;iieta<22;iieta++){
	    TString histnm = "h1_W_Neu_Eta_"+str_pm[iipm]+"_"+str_etaId[iieta];
	    //cout<<histnm<<endl;
	    h_MET = 0;
	    f_file->GetObject(histnm,h_MET);
	    //if(iipm==0 && iieta==3 && i==3) h_MET->Draw();
	    h_MET->SetLineColor(bgdColor[i]);  h_MET->SetFillColor(bgdColor[i]); h_MET->SetFillStyle(1001);
	    hs_MET_pm_ieta[iipm][iieta]->Add(h_MET);
	    lg[iipm][iieta]->AddEntry(h_MET,fileNM[i],"F");
	  }
	}
	
	hs_W_Lept1_pt->Add(h1_W_Lept1_pt);   
	//hs_W_Lept1_pt->Add(h1_W_Neu_All);   
	lgc->AddEntry(h1_W_Lept1_pt,fileNM[i],"F");
	//lgc->AddEntry(h1_W_Neu_All,fileNM[i],"F");
      }

    }//for
  TCanvas *c1 = new TCanvas();
  TFile *f_fileRD = new TFile(filePath[0]);  

  
  lgc->AddEntry(h1_W_Lept1_pt,"2012RealData 19.619/fb", "LP");
  //lgc->AddEntry(h1_W_Neu_All,"2012A_13July 808/pb", "LP");
  h1_W_Lept1_pt->SetMarkerStyle(20);  h1_W_Lept1_pt->SetMarkerSize(1);
  //h1_W_Neu_All->SetMarkerStyle(20);  h1_W_Neu_All->SetMarkerSize(1); h1_W_Neu_All->SetMaximum(200000);
//  h1_W_Lept1_pt->Draw("e");
  //h1_W_Neu_All->Draw("e");
  hs_W_Lept1_pt->Draw();
  //hs_W_Lept1_pt->Draw("same");
  h1_W_Lept1_pt->Draw("same e");
  //h1_W_Neu_All->Draw("same e");
  h1_WSide_Neu_eta_0->GetXaxis()->SetTitle("MET");
  h1_WSide_Neu_eta_0->GetYaxis()->SetTitle("# of event");
  lgc->Draw();
  c1->SaveAs("W_Lept1_pt.png");
  //c1->SaveAs("W_Neu_All.png");

  TCanvas *cvs[3][22];
  for(Int_t iiipm=0;iiipm<3;iiipm++){
    for(Int_t iiieta=0;iiieta<22;iiieta++){
      cvs[iiipm][iiieta] = new TCanvas();

      
      TFile *f_fileRD = new TFile(filePath[0]); 
      TString histnmRD = "h1_W_Neu_Eta_"+str_pm[iiipm]+"_"+str_etaId[iiieta];
      cout<<"iiipm "<<iiipm<<" iiieta "<<iiieta<<endl;

      h_MET_RD = 0;
      f_fileRD->GetObject(histnmRD,h_MET_RD);
      h_MET_RD->SetMarkerStyle(20); h_MET_RD->SetMarkerSize(1);
      lg[iiipm][iiieta]->AddEntry(h_MET_RD,"2012RealData 19.619/fb","LP");
      
      if(iiipm==1){
	//h_MET_RD->Draw("e");
        hs_MET_pm_ieta[iiipm][iiieta]->SetMaximum(9000);
	hs_MET_pm_ieta[iiipm][iiieta]->Draw();
	h_MET_RD->Draw("same e");
      }
      else if(iiipm==2){
	//h_MET_RD->Draw("e");
        hs_MET_pm_ieta[iiipm][iiieta]->SetMaximum(9000);
	hs_MET_pm_ieta[iiipm][iiieta]->Draw();
	h_MET_RD->Draw("same e");
      }
      else{
        hs_MET_pm_ieta[iiipm][iiieta]->SetMaximum(9000);
        hs_MET_pm_ieta[iiipm][iiieta]->Draw();
        h_MET_RD->Draw("same e");
      }
      
      ////////*
      h_MET_RD->Draw("e");
      hs_MET_pm_ieta[iiipm][iiieta]->Draw("same");
      h_MET_RD->Draw("same e");
      //////////////*
      lg[iiipm][iiieta]->Draw();
      TString SaveName = histnmRD+".png";
      cvs[iiipm][iiieta] ->SaveAs(SaveName);
    }
  }
}
