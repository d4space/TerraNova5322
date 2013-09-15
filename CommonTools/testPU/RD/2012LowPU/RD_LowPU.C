{
 TFile *f = new TFile("LowPUHist.root");
  f->ls();
  TH1F *LPU = (TH1F*)f->Get("pileup");
  LPU->Draw();
  c1->Print("RD_S8_PU_distribution.png");

  ofstream Fout;
  Fout.open("RD_S8_PU_distribution.txt");
  for (int i=1; i<=LPU->GetNbinsX(); i++) {
	cout << LPU->GetBinContent(i) << endl;
	Fout << LPU->GetBinContent(i) << endl;}
	//cout << LPU->GetBinContent(i)/LPU << endl;
	//Fout << LPU->GetBinContent(i)/LPU << endl;}
Fout.close();
return 0;
}
