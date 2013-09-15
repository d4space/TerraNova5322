{
  TFile * file = new TFile("Run2012A_13Jul_190456_193621.root");
  pileup->Draw();

  Int_t nBin = pileup->GetNbinsX();

  for(Int_t i=0;i<nBin;++i){
    cout<<""<<pileup->GetBinContent(i)<<","<<endl;
  }

}
