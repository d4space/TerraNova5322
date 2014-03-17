{
  TChain *myChain = new TChain("ZElEl/tree");
  //TChain *myChain = new TChain("WMuNeu/tree");
  myChain->Add("/terranova_1/TestNtuple/TerraTuple.root");
  myChain->MakeClass("ZllNT");
}
