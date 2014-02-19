{
  TChain *myChain = new TChain("WMuNeu/tree");
  myChain->Add("/terranova_1/TestNtuple/wNTuple_WpMuNuS8.root");
  myChain->MakeClass("NtupleAna");
}
