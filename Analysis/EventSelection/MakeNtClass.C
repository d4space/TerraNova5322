{
  TChain *myChain = new TChain("ZZ4L/tree");
  //TChain *myChain = new TChain("WMuNeu/tree");
  myChain->Add("/terranova_1/TestNtuple/TerraTuple.root");
  myChain->MakeClass("ZZ4LNT");
}
