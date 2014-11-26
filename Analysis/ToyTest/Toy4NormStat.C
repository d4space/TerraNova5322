#define Ntoy 50000
#define NBin 13

int Toy4NormStat()
{
 
  ofstream myTxt;
  myTxt.open("Toy4NormStat.txt");

  TFile *myF = new TFile("Toy4NormStat.root","recreate");
  TH1D *hRD = new TH1D("hRD","hRD",50, -4, 4);
  TRandom3 *myRandom=new TRandom3();
  //myRandom->SetSeed(0); --> Not fixing the seed
  myRandom->SetSeed(0x1347); // fixing the seed to give the same series of RN
  //myRandom->SetSeed(0x123457); // fixing the seed to give the same series of RN
  // Variables
  double RN[Ntoy];
  double YieldTot(0);
  double RNtemp;
  double Yield_tmp;
  double Yield_Total_tmp;
  double NormXsec[NBin];
  double ToyNormXsec[NBin];
  double SumToyNormXsec[NBin];
  double VarNormXsec[NBin][Ntoy];
  double SumVarNormXsec[NBin];



  double Yield[NBin]={25651.7, 14407.5, 8136.32, 6375.47, 3751.52,3991.11, 2352.82,2384.4,1450.12, 349.623, 111.385, 57.9785, 28.7645};
  double Yield_Error[NBin]={236.047, 133.515, 84.0563, 71.8006, 56.4416, 59.711, 49.6092, 49.0328, 39.4345, 19.0838, 11.7062, 10.5994, 6.96515};
  double BinWidth[NBin] ={7.5-0, 12.5-7.5,17.5-12.5, 24.0-17.5, 30.0-24.0, 40.0-30.0, 50.0-40.0, 70.0-50.0, 110.0-70.0, 150.0-110.0, 190.0-150.0, 250.0-190.0, 600.0-250.0};


  YieldTot = 0;
  cout<<"Yields+Error       "<<"BindWidth"<<"\t"<<"Diff X-sec"<<"\t"<<"Normalized diff+Error"<<endl;
  myTxt<<"Yields+Error       "<<"BindWidth"<<"\t"<<"Diff X-sec"<<"\t"<<"Normalized diff+Error"<<endl;
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
      <<"+"<<Yield_Error[i]/BinWidth[i]/YieldTot<<endl;
    myTxt<<Yield[i]<<"+"<<Yield_Error[i]<<"\t"<<BinWidth[i]
      <<"\t"<<Yield[i]/BinWidth[i]/18.5<<"\t\t" // diff x-sec
      <<NormXsec[i]
      <<"+"<<Yield_Error[i]/BinWidth[i]/YieldTot<<endl;
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
    Yield_Total_tmp = 0;
    for(int ibin(0);ibin<NBin;ibin++)
    {
      RNtemp = myRandom->Gaus(0,1);
      Yield_tmp = Yield[ibin] + Yield_Error[ibin]*RNtemp;
      Yield_Total_tmp += Yield_tmp;
      ToyNormXsec[ibin] = Yield_tmp/BinWidth[ibin];
    }
    for(int ibin(0);ibin<NBin;ibin++)
    {
      ToyNormXsec[ibin] /= Yield_Total_tmp;
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
    double RMsNormXsec = TMath::Sqrt(SumVar2NormXsec/Ntoy);
    cout<<i<<"   "<<SumToyNormXsec[i]/Ntoy<<"\t\t"<<SumVarNormXsec[i]/Ntoy<<"\t"<<RMsNormXsec<<endl;
    myTxt<<i<<"   "<<SumToyNormXsec[i]/Ntoy<<"\t\t"<<SumVarNormXsec[i]/Ntoy<<"\t"<<RMsNormXsec<<endl;
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
