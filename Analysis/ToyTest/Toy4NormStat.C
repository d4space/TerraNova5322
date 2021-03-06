#define Ntoy 50000
#define NBin 13

int Toy4NormStat()
{
 
  ofstream myTxt;
  myTxt.open("Toy4NormStat.txt");

  TFile *myF = new TFile("Toy4NormStat.root","recreate");
  TH1D *hRD = new TH1D("hRD","hRD",50, -4, 4);
  TH1D *hPull[NBin];
  char histName[50];
  for(int i(0);i<NBin;i++)
  {
    sprintf(histName,"hPull_%d",i);
    hPull[i]= new TH1D(histName,histName,50, -4, 4);
  }
  
  TRandom3 *myRandom=new TRandom3();
  //myRandom->SetSeed(0); --> Not fixing the seed
  myRandom->SetSeed(0x1347); // fixing the seed to give the same series of RN
  //myRandom->SetSeed(0x123457); // fixing the seed to give the same series of RN
  // Variables
  double RN[Ntoy];
  double YieldTot(0);
  double RNtemp;
  double ToyYield;
  double ToyYieldErr;
  double ToyYield_Total;
  double NormXsec[NBin];
  double ToyNormXsec[NBin];
  double ToyNormXsecErr[NBin];
  double SumToyNormXsec[NBin];
  double VarNormXsec[NBin][Ntoy];
  double SumVarNormXsec[NBin];
  double pull;
  double RMsNormXsec[NBin];
  double Yield_PoissonErr[NBin];



  // Fill Yield and it's statistic error from MET fit
  // W+ Muon
  //double Yield[NBin]={25651.7, 14407.5, 8136.32, 6375.47, 3751.52,3991.11, 2352.82,2384.4,1450.12, 349.623, 111.385, 57.9785, 28.7645};
  //double Yield_Error[NBin]={236.047, 133.515, 84.0563, 71.8006, 56.4416, 59.711, 49.6092, 49.0328, 39.4345, 19.0838, 11.7062, 10.5994, 6.96515};
  
//  // W- Muon
//  double Yield[NBin]={16758, 9735.23, 5624.22, 4392.25, 2687.33, 2866.47, 1709.4, 1726.86, 1048.68, 252.088, 83.7192, 39.5066, 17.8297};
//  double Yield_Error[NBin]={192.633, 108.996, 71.5906, 59.348, 47.4341, 51.7885, 42.2154, 42.5309, 32.6359, 15.8024, 10.1541, 6.47734, 5.95479};

//  // W+ Electron
//  double Yield[NBin]={24631.1, 14167.5, 8330.13, 6667.14, 3974.45, 4134.48, 2370.23, 2368.65, 1490.21, 384.512, 121.627, 61.0698, 30.1186};
//  double Yield_Error[NBin]={264.833, 149.708, 98.1539, 84.1393, 66.8583, 69.2939, 53.7141, 56.2531, 42.7481, 22.82, 12.2646, 8.73213, 7.36433};

  // W- Electron
  double Yield[NBin]={16370.5, 9598.88, 5667.44, 4496.62, 2710.76, 2880.66, 1684.13, 1759.39, 1129.6, 286.8, 88.4324, 42.8677, 17.7608};
  double Yield_Error[NBin]={214.862, 120.389, 81.3334, 67.7955, 54.8901, 59.6268, 45.3299, 46.4496, 37.862, 19.5144, 10.8293, 7.64301, 4.51305};

  
  double BinWidth[NBin] ={7.5-0, 12.5-7.5,17.5-12.5, 24.0-17.5, 30.0-24.0, 40.0-30.0, 50.0-40.0, 70.0-50.0, 110.0-70.0, 150.0-110.0, 190.0-150.0, 250.0-190.0, 600.0-250.0};

  for(int i(0);i<NBin;i++)
  {
    Yield_PoissonErr[i] = TMath::Sqrt(Yield[i]);
  }


  YieldTot = 0;
  cout<<"Yields+Error       "<<"BinWidth"<<"\t"<<"Diff X-sec"<<"\t"<<"Normalized diff+Error"<<"\t"<<"PoissonErr"<<"\t"<<"Binomial"<<endl;
  myTxt<<"Yields+Error       "<<"BinWidth"<<"\t"<<"Diff X-sec"<<"\t"<<"Normalized diff+Error"<<"\t"<<"PoissonErr"<<"\t"<<"Binomial"<<endl;
  for(int i(0);i<NBin;i++)
  {
    YieldTot +=Yield[i];
  }
  for(int i(0);i<NBin;i++)
  {
    NormXsec[i] = Yield[i]/BinWidth[i]/YieldTot;         // Norm X-sec
    cout<<Yield[i]<<"+"<<Yield_Error[i]<<"\t"<<BinWidth[i]
      <<"\t"<<Yield[i]/BinWidth[i]/18.5<<"\t\t" // diff x-sec
      <<NormXsec[i]
      <<"+"<<Yield_Error[i]/BinWidth[i]/YieldTot
      <<"\t"<<Yield_PoissonErr[i]/BinWidth[i]/YieldTot
      <<"\t"<<TMath::Sqrt( Yield[i]*(1-Yield[i]/YieldTot) )/BinWidth[i]/YieldTot
      <<endl;
    myTxt<<Yield[i]<<"+"<<Yield_Error[i]<<"\t"<<BinWidth[i]
      <<"\t"<<Yield[i]/BinWidth[i]/18.5<<"\t\t" // diff x-sec
      <<NormXsec[i]
      <<"+"<<Yield_Error[i]/BinWidth[i]/YieldTot
      <<"\t"<<Yield_PoissonErr[i]/BinWidth[i]/YieldTot
      <<"\t"<<TMath::Sqrt(Yield[i]*(1-Yield[i]/YieldTot) )/BinWidth[i]/YieldTot
      <<endl;
  }
  cout<<endl;
  myTxt<<endl;


  // Toy MC
  for(int i(0);i<NBin;i++)
  {
    SumToyNormXsec[i]=0;
    SumVarNormXsec[i]=0;
  }
  for(int i(0);i<Ntoy;i++)
  {
    ToyYield_Total = 0;
    for(int ibin(0);ibin<NBin;ibin++)
    {
      RNtemp = myRandom->Gaus(0,1);
      ToyYield = Yield[ibin] + Yield_Error[ibin]*RNtemp;
      ToyYieldErr = TMath::Sqrt(ToyYield);
      ToyYield_Total += ToyYield;
      ToyNormXsec[ibin]    = ToyYield/BinWidth[ibin];
      ToyNormXsecErr[ibin] = ToyYieldErr/BinWidth[ibin];
    }
    for(int ibin(0);ibin<NBin;ibin++)
    {
      ToyNormXsec[ibin] /= ToyYield_Total;
      ToyNormXsecErr[ibin] /= ToyYield_Total;
      SumToyNormXsec[ibin] += ToyNormXsec[ibin];
      VarNormXsec[ibin][i] = ToyNormXsec[ibin] - NormXsec[ibin];
      SumVarNormXsec[ibin] += VarNormXsec[ibin][i];
    }
    RN[i]=myRandom->Gaus(0,1);
    //cout<<"smear: randomValue "<<i<<":"<<RN<<endl;;
    hRD->Fill(RN[i]);
    
  }

  cout<<"Mean of ToyNormXsec     Mean of VarNormXsec        RMS==================="<<endl;
  myTxt<<"Mean of ToyNormXsec     Mean of VarNormXsec        RMS==================="<<endl;
  for(int i(0);i<NBin;i++)
  {
    double SumVar2NormXsec(0);
    for(int iTy(0);iTy<Ntoy;iTy++)
    {
      SumVar2NormXsec +=(VarNormXsec[i][iTy] - 0)*(VarNormXsec[i][iTy] - 0);

    }
    RMsNormXsec[i] = TMath::Sqrt(SumVar2NormXsec/Ntoy);
    for(int iTy(0);iTy<Ntoy;iTy++)
    {
      pull = VarNormXsec[i][iTy]/RMsNormXsec[i];
      hPull[i]->Fill(pull);
    }
    cout<<i<<"   "<<SumToyNormXsec[i]/Ntoy<<"\t\t"<<SumVarNormXsec[i]/Ntoy<<"\t"<<RMsNormXsec[i]<<endl;
    myTxt<<i<<"   "<<SumToyNormXsec[i]/Ntoy<<"\t\t"<<SumVarNormXsec[i]/Ntoy<<"\t"<<RMsNormXsec[i]<<endl;
  }
  // Plot of pull distributions
  for(int i(0);i<NBin;i++)
  {
    hPull[i]->Draw();
    sprintf(histName,"Plots/hPull_%d.png",i);
    c1->SaveAs(histName);
  }
  cout<<"<<<<<<<<< Toy Test >>>>>>>>>>>"<<endl;
  // Calculation of dispersion
  //
  double mean(0);
  double Ran2Tot(0);
  double Ran2Mean(0);
  double RootMeanSq(0);
  mean = TMath::Mean(Ntoy, RN);
  cout<<"Mean: "<<mean<<endl;

  for( int i(0); i<Ntoy; i++)
  {
    Ran2Tot += (RN[i] - mean)*(RN[i] - mean);

  }
  Ran2Mean = Ran2Tot/Ntoy;
  RootMeanSq = TMath::Sqrt(Ran2Mean);
  cout<<"RootMeanSq: "<<RootMeanSq<<" from standard deviation ftn: "<<TMath::RMS(Ntoy,RN)<<endl;
  myF->Write();
  delete myF;
  myTxt.close();
  return 0;
}
