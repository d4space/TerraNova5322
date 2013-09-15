{
  TString DIR = "../kk";
  TString fileNM[] = {"DYToEE_S10"};
  TString filePath[1];

  TH1D *h1_No_Charge_Requirement[144];
  TH1D *h1_No_Charge_Requirement_Same[144];
  TH1D *h1_Three_Charge_Requirement[144];
  TH1D *h1_Three_Charge_Requirement_Same[144];

  TLegend *lg1[144];
  TLegend *lg2[144];
  TLegend *lg3[144];
  TLegend *lg4[144];

  TString str_Id[144]={"_0_0","_0_1","_0_2","_0_3","_0_4","_0_5","_0_6","_0_7","_0_8","_0_9","_0_10","_0_11",
                       "_1_0","_1_1","_1_2","_1_3","_1_4","_1_5","_1_6","_1_7","_1_8","_1_9","_1_10","_1_11",
	               "_2_0","_2_1","_2_2","_2_3","_2_4","_2_5","_2_6","_2_7","_2_8","_2_9","_2_10","_2_11",
	               "_3_0","_3_1","_3_2","_3_3","_3_4","_3_5","_3_6","_3_7","_3_8","_3_9","_3_10","_3_11",
		       "_4_0","_4_1","_4_2","_4_3","_4_4","_4_5","_4_6","_4_7","_4_8","_4_9","_4_10","_4_11",
	               "_5_0","_5_1","_5_2","_5_3","_5_4","_5_5","_5_6","_5_7","_5_8","_5_9","_5_10","_5_11",
	               "_6_0","_6_1","_6_2","_6_3","_6_4","_6_5","_6_6","_6_7","_6_8","_6_9","_6_10","_6_11",
		       "_7_0","_7_1","_7_2","_7_3","_7_4","_7_5","_7_6","_7_7","_7_8","_7_9","_7_10","_7_11",
		       "_8_0","_8_1","_8_2","_8_3","_8_4","_8_5","_8_6","_8_7","_8_8","_8_9","_8_10","_8_11",
		       "_9_0","_9_1","_9_2","_9_3","_9_4","_9_5","_9_6","_9_7","_9_8","_9_9","_9_10","_9_11",
		       "_10_0","_10_1","_10_2","_10_3","_10_4","_10_5","_10_6","_10_7","_10_8","_10_9","_10_10","_10_11",
		       "_11_0","_11_1","_11_2","_11_3","_11_4","_11_5","_11_6","_11_7","_11_8","_11_9","_11_10","_11_11"}
//Input File and Histogram
  for(Int_t i=0; i<1;i++){
  filePath[i]= DIR+"/Ele_"+fileNM[]+"_Analysis.root";
  TFile *f_file = new TFile(filePath[i]);
  }

  for(Int_t iieta=0;iieta<144;iieta++){
      
      TString histnm = "h1_Zmass_QNo"+str_Id[iieta];
      f_file->GetObject(histnm,h1_No_Charge_Requirement[iieta]);
      lg1[iieta] = new TLegend(0.59, 0.67, 0.89, 0.89);
      lg2[iieta] = new TLegend(0.59, 0.47, 0.89, 0.69);
      lg1[iieta]->SetTextSize(0.03);   lg1[iieta]->SetBorderSize(0);  lg1[iieta]->SetFillColor(0);
      lg2[iieta]->SetTextSize(0.03);   lg2[iieta]->SetBorderSize(0);  lg2[iieta]->SetFillColor(0);
  }

   for(Int_t iieta=0;iieta<144;iieta++){

      TString histnm = "h1_Zmass_QNoSame"+str_Id[iieta];
      f_file->GetObject(histnm,h1_No_Charge_Requirement_Same[iieta]);
  }

  for(Int_t iieta=0;iieta<144;iieta++){

      TString histnm = "h1_Zmass_QThree"+str_Id[iieta];
      f_file->GetObject(histnm,h1_Three_Charge_Requirement[iieta]);
      h1_Three_Charge_Requirement[iieta]->SetLineColor(20);
      lg3[iieta] = new TLegend(0.59, 0.67, 0.89, 0.89);
      lg4[iieta] = new TLegend(0.59, 0.47, 0.89, 0.69);
      lg3[iieta]->SetTextSize(0.03);   lg3[iieta]->SetBorderSize(0);  lg3[iieta]->SetFillColor(0);
      lg4[iieta]->SetTextSize(0.03);   lg4[iieta]->SetBorderSize(0);  lg4[iieta]->SetFillColor(0);
  }

    for(Int_t iieta=0;iieta<144;iieta++){

      TString histnm = "h1_Zmass_QThreeSame"+str_Id[iieta];
      f_file->GetObject(histnm,h1_Three_Charge_Requirement_Same[iieta]);
      h1_Three_Charge_Requirement_Same[iieta]->SetLineColor(20);
  }


//Draw Canvas And Histograms
 TCanvas *cvs1[144];
  for(Int_t iieta=0;iieta<144;iieta++){
         cvs1[iieta] = new TCanvas();
         h1_No_Charge_Requirement[iieta]->GetXaxis()->SetTitle("Mass (GeV)");
         h1_No_Charge_Requirement[iieta]->GetYaxis()->SetTitle("# of event");
         h1_No_Charge_Requirement[iieta]->Draw();
         h1_Three_Charge_Requirement[iieta]->Draw("same");
	 lg1[iieta]->AddEntry(h1_No_Charge_Requirement[iieta],"h1_No_Charge_Requirement"+str_Id[iieta],"LP");
	 lg2[iieta]->AddEntry(h1_Three_Charge_Requirement[iieta],"h1_Three_Charge_Requirement"+str_Id[iieta],"LP");
//	 lg1[iieta]->Draw();
//	 lg2[iieta]->Draw();
//	 cvs1[iieta] ->SetName("Same sign + Opposite sign");
//         cvs1[iieta] ->SaveAs("SamePlusOpposite_"+str_Id[iieta]+".png");
 }  

  TCanvas *cvs2[144];
   for(Int_t iieta=0;iieta<144;iieta++){
           cvs2[iieta] = new TCanvas();
	   h1_No_Charge_Requirement_Same[iieta]->GetXaxis()->SetTitle("Mass (GeV)");
	   h1_No_Charge_Requirement_Same[iieta]->GetYaxis()->SetTitle("# of event");
           h1_No_Charge_Requirement_Same[iieta]->Draw();
           h1_Three_Charge_Requirement_Same[iieta]->Draw("same");
	   lg3[iieta]->AddEntry(h1_No_Charge_Requirement_Same[iieta],"h1_No_Charge_Requirement_Same"+str_Id[iieta],"LP");
	   lg4[iieta]->AddEntry(h1_Three_Charge_Requirement_Same[iieta],"h1_Three_Charge_Requirement_Same"+str_Id[iieta],"LP");
	//   lg3[iieta]->Draw();
	//   lg4[iieta]->Draw();
  //         cvs2[iieta] ->SaveAs("Same_"+str_Id[iieta]+".png");
 }
 for(Int_t iieta=0;iieta<144;iieta++){
           cout<<"eta bin"<<str_Id[iieta]<<"Rij: "<<h1_Three_Charge_Requirement_Same[iieta]->Integral()/h1_Three_Charge_Requirement[iieta]->Integral()<<endl;
 }
 for(Int_t iieta=0;iieta<144;iieta++){
           cout<<"eta bin"<<str_Id[iieta]<<endl;
	   cout<<"No_Charge_Requirement # of event, Same sign + Opposite sign: "<<h1_No_Charge_Requirement[iieta]->Integral()<<endl;
	   cout<<"Three_Charge_Requirement # of event, Same sign + Opposite sign: "<<h1_Three_Charge_Requirement[iieta]->Integral()<<endl;
	   cout<<"No_Charge_Requirement # of event, Same sign: "<<h1_No_Charge_Requirement_Same[iieta]->Integral()<<endl;
	   cout<<"Three_Charge_Requirement # of event, Same sign: "<<h1_Three_Charge_Requirement_Same[iieta]->Integral()<<endl;
	   cout<<"Rij: "<<h1_Three_Charge_Requirement_Same[iieta]->Integral()/h1_Three_Charge_Requirement[iieta]->Integral()<<endl;
        

 }

}
